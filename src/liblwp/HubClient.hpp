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

class HubClient
{
    public:
        HubClient();
        ~HubClient();
        
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
};

}