#include "HubClient.hpp"

namespace LWP {

    HubClient::HubClient() {
        adapter_ = SimpleBLE::Adapter::get_adapters()[0];
        std::cout << "Używany adapter: " << adapter_.identifier() << " [" << adapter_.address() << "]\n";

        std::cout << "Skanowanie w poszukiwaniu huba SPIKE Prime...\n";
    }

    void HubClient::connect(std::optional<std::string> name_contains) {

        auto adapters = SimpleBLE::Adapter::get_adapters();
        if (adapters.empty()) throw std::runtime_error("Brak adaptera BLE");

        adapter_ = adapters.front();
        adapter_.scan_for(10000);

        auto peripherals = adapter_.scan_get_results();
        SimpleBLE::Peripheral target;

        bool found = false;
        for (auto& p : peripherals) {
            try {
		std::cout<<"identifier="<<p.identifier()<<"\n";
                auto uuids = p.services();
                bool hasLwp = false;
                for (auto& u : uuids) {
		    std::cout<<"uuid="<<u.uuid()<<"\n";
                    if (strcasecmp(u.uuid().c_str(), LWP::nusServiceUUID.c_str()) == 0) {
                        hasLwp = true;
                        break;
                    }
                }
                bool nameOk = name_contains.has_value() and (p.identifier().find(*name_contains) != std::string::npos);

                if ((hasLwp || nameOk) && p.is_connectable()) {
                    target = p;
                    found  = true;
                    break;
                }
            } catch (std::exception& e) {
		    std::cout<<"Error: "<<e.what()<<std::endl;
	    }
        }

        if (!found) throw std::runtime_error("Nie znaleziono huba SPIKE Prime (serwis LWP3).");

        std::cout << "Łączenie z: " << target.identifier() << " [" << target.address() << "]\n";
        target.connect();
        if (!target.is_connected()) throw std::runtime_error("Nie udało się połączyć z hubem.");

        peripheral_ = target;

        // Znajdź charakterystykę LWP
        bool gotWrite = false;
	bool gotNotification = false;
        for (auto& s : peripheral_.services()) {
            if (strcasecmp(s.uuid().c_str(), LWP::nusServiceUUID.c_str()) == 0) {
                for (auto& c : s.characteristics()) {
                    serviceUUID = s.uuid();
                    if (strcasecmp(c.uuid().c_str(), LWP::nusTxCharacteristicUUID.c_str()) == 0) {
                        writeUUID    = c.uuid();
                        gotWrite       = true;
                    }
		     if (strcasecmp(c.uuid().c_str(), LWP::nusRxCharacteristicUUID.c_str()) == 0) {
                        notifyUUID    = c.uuid();
                        gotNotification  = true;
                    }
                    if (gotWrite and gotNotification)
		    {
		        break;
		    }
		    
                }
            }
        }
        if (!gotWrite or !gotNotification) throw std::runtime_error("Nie znaleziono charakterystyki LWP3 w hubie.");

        std::cout << "Połączono. Service=" << serviceUUID << " write=" << writeUUID << " notif="<< notifyUUID << "\n";
    }

}
