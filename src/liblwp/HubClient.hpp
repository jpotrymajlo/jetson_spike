#pragma once

#include "simpleble/SimpleBLE.h"

namespace LWP {
    const char* serviceUUID = "00001623-1212-efde-1623-785feabcd123";
    const char* characteristicsUUID    = "00001624-1212-efde-1623-785feabcd123";

//    const uint8_t kHubImuPort     = 1;
//    const uint8_t kImuMode        = 0;      // Accelerometer + Gyro
//    const uint16_t kImuIntervalMs = 20;     // 50 Hz
class HubClient {
public:
    HubClient() = default;
    ~HubClient() = default; 


    void connect(std::optional<std::string> name_contains = std::nullopt);
    void disconnect() {
        if (peripheral_.initialized() && peripheral_.is_connected()) {
            peripheral_.unsubscribe(service_uuid_, char_uuid_);
            peripheral_.disconnect();
        }
    }

    // Observer: rejestracja callbacku notyfikacji
    void subscribe_notifications(std::shared_ptr<INotificationObserver> obs) {
        observer_ = obs;
        peripheral_.notify(service_uuid_, char_uuid_, [this](SimpleBLE::ByteArray bytes) {
            std::vector<uint8_t> data(bytes.begin(), bytes.end());
            if (observer_) observer_->on_raw_notification(data);
        });
    }

    // Włączenie cyklicznych raportów z IMU
    void enable_imu_stream() {
        auto pkt = encoder_->make_enable_port_notification(
            LWP::kHubImuPort, LWP::kImuMode, LWP::kImuIntervalMs, /*enable=*/true
        );
        write(pkt);
    }

    // Wyłączenie strumienia (opcjonalnie)
    void disable_imu_stream() {
        auto pkt = encoder_->make_enable_port_notification(
            LWP::kHubImuPort, LWP::kImuMode, LWP::kImuIntervalMs, /*enable=*/false
        );
        write(pkt);
    }

    // Uruchomienie komendy silnika
    void run_motor_command(IMotorCommand& cmd) {
        auto pkt = cmd.encode(*encoder_);
        write(pkt);
    }

private:
    void write(const std::vector<uint8_t>& data) {
        if (!peripheral_.is_connected()) throw std::runtime_error("Brak połączenia z hubem.");
        peripheral_.write_request(service_uuid_, char_uuid_, SimpleBLE::ByteArray(data.begin(), data.end()));
    }

    SimpleBLE::Adapter adapter_;
    SimpleBLE::Peripheral peripheral_;
    std::string service_uuid_, char_uuid_;
    std::shared_ptr<INotificationObserver> observer_;
    std::unique_ptr<ILwpEncoder> encoder_;
};

}