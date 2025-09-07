#include <simplebluez/Bluez.h>
#include <simplebluez/Exceptions.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <stdexcept>
#include <string>
#include <memory>


namespace Lwp
{


static constexpr const char* nusServiceUUID = "6e400001-b5a3-f393-e0a9-e50e24dcca9e";
static constexpr const char* rxCharacteristicUUID = "6e400002-b5a3-f393-e0a9-e50e24dcca9e";
static constexpr const char* txCharacteristicUUID = "6e400003-b5a3-f393-e0a9-e50e24dcca9e";

class HubClient
{

    public:
        HubClient();
        ~HubClient();
        
        void connect(const std::string& name, std::function<void()> onConnected);
        void connect(const std::string& name);
        void disconnect();

        void sendCommand(const std::string& command);
        std::string receiveData();

    private:

        SimpleBluez::Bluez bluez;
        std::atomic_bool bluezThreadActive = true;
        std::unique_ptr<std::thread> bluezThread = nullptr;
        void bluezThreadFunction();
        std::shared_ptr<SimpleBluez::Device> device = nullptr;
        std::shared_ptr<SimpleBluez::Characteristic> rxCharacteristic;
        std::shared_ptr<SimpleBluez::Characteristic> txCharacteristic;
};

}