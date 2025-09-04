#include "libmycuda.hpp"
#include "atomic"
#include "HubClient.hpp"
#include <csignal>
#include <thread>

static std::atomic_bool g_stop{false};
void sigint_handler(int) { g_stop = true; }

int main(int, char** ) {
    try {
        std::signal(SIGINT, sigint_handler);
        std::optional<std::string> nameFilter;
        LWP::HubClient client;
        client.connect(nameFilter);
        client.subscribe_notifications();
        while (!g_stop.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    } catch (std::exception& e) {
        std::cerr << "Error :"<<e.what()<<std::endl;
        return 1;
    }
}
