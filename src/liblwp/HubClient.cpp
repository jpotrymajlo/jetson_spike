#include "HubClient.hpp"

#include <atomic>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <thread>
#include <future>

namespace Lwp
{
HubClient::HubClient()
    
{
    bluez.init();
    bluezThread = std::make_unique<std::thread>([this](){bluezThreadFunction();});
}
HubClient::~HubClient()
{
    disconnect(); 
    bluezThreadActive = false;
    if (bluezThread->joinable()) {
        bluezThread->join();
    }
}
void HubClient::connect(const std::string &name)
{
    auto adapters = bluez.get_adapters();

    for (unsigned int i = 0; i < adapters.size(); i++) {
        std::cout << "[" << i << "] " << adapters[i]->identifier() << " [" << adapters[i]->address() << "]"
                  << std::endl;
    }

    auto adapter = adapters[0];
    SimpleBluez::Adapter::DiscoveryFilter filter;
    filter.Transport = SimpleBluez::Adapter::DiscoveryFilter::TransportType::LE;

    adapter->discovery_filter(filter);
    std::promise<void> deviceFoundPromise;
    std::promise<void> servicesResolvedPromise;
    adapter->set_on_device_updated([this, name, &adapter, &deviceFoundPromise, 
        &servicesResolvedPromise](std::shared_ptr<SimpleBluez::Device> updatedDevice) {
        if (not device and updatedDevice->name() == name and not updatedDevice->connected())
        {
            device = updatedDevice;
            device->set_on_services_resolved([this, &servicesResolvedPromise]() {

                if (device->services_resolved()) {
                    rxCharacteristic = device->get_characteristic(nusServiceUUID, rxCharacteristicUUID);
                    txCharacteristic = device->get_characteristic(nusServiceUUID, txCharacteristicUUID);
                    servicesResolvedPromise.set_value();
                } else {
                    std::cout << "Failed to resolve services for device: " << device->name() << " [" << device->address() << "]" << std::endl;
                }});
            adapter->set_on_device_updated(nullptr); 
            deviceFoundPromise.set_value();
        }
    });
    adapter->discovery_start();
    auto deviceFoundFuture = deviceFoundPromise.get_future();
    deviceFoundFuture.get();

    adapter->discovery_stop();
    device->connect();
    auto servicesResolvedFuture = servicesResolvedPromise.get_future();
    servicesResolvedFuture.get();

}

void HubClient::connect(const std::string &name, std::function<void()> onConnected)
{
    std::thread([this, name, onConnected=std::move(onConnected)]() {
        connect(name);
        onConnected();
    }).detach();
}

void HubClient::disconnect()
{
    device->disconnect();

}

void HubClient::sendCommand(const std::string &)
{
}

std::string HubClient::receiveData()
{
  return std::string();
}

void HubClient::bluezThreadFunction() //przerobić na timer
{
    while (bluezThreadActive) {
        bluez.run_async();
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
}
}
