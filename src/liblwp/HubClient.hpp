#pragma once

#include "simpleble/SimpleBLE.h"

namespace LWP {
    //constexpr const char* serviceUUID = "00001623-1212-efde-1623-785feabcd123";
    //constexpr const char* characteristicsUUID    = "00001624-1212-efde-1623-785feabcd123";

const std::string nusServiceUUID = "6e400001-b5a3-f393-e0a9-e50e24dcca9e";
const std::string nusTxCharacteristicUUID = "6e400002-b5a3-f393-e0a9-e50e24dcca9e"; // write
const std::string nusRxCharacteristicUUID = "6e400003-b5a3-f393-e0a9-e50e24dcca9e"; // notify
										    //
class HubClient {
public:
    HubClient();
    ~HubClient() = default; 


    void connect(std::optional<std::string> name_contains = std::nullopt);
    void disconnect() {
        if (peripheral_.initialized() && peripheral_.is_connected()) {
            peripheral_.unsubscribe(serviceUUID, notifyUUID);
            peripheral_.disconnect();
        }
    }

    // Observer: rejestracja callbacku notyfikacji
    //void subscribe_notifications(std::shared_ptr<INotificationObserver> obs) {
    void subscribe_notifications() {
        //observer_ = obs;
        peripheral_.notify(serviceUUID, notifyUUID, [this](SimpleBLE::ByteArray bytes) {
	            std::string response(bytes.begin(), bytes.end());
            std::cout << "RX raw: " << response << std::endl;
//            std::vector<uint8_t> data(bytes.begin(), bytes.end());
//            if (observer_) observer_->on_raw_notification(data);
        });
    }

private:
    void write(const std::vector<uint8_t>& data) {
        if (!peripheral_.is_connected()) throw std::runtime_error("Brak połączenia z hubem.");
        peripheral_.write_request(serviceUUID, writeUUID, SimpleBLE::ByteArray(data.begin(), data.end()));
    }

    SimpleBLE::Adapter adapter_;
    SimpleBLE::Peripheral peripheral_;
    std::string serviceUUID, writeUUID, notifyUUID;
//    std::shared_ptr<INotificationObserver> observer_;
//    std::unique_ptr<ILwpEncoder> encoder_;
};

}
