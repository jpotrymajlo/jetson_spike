#include "libmycuda.hpp"
#include "atomic"
#include "HubClient.hpp"
#include <csignal>
#include <thread>
#include <future>

static std::atomic_bool g_stop{false};
void sigint_handler(int) { g_stop = true; }


// --------------------
// Example usage
// --------------------
int main() {
    Lwp::HubClient client;
    std::promise<void> connected;
    client.connect("HAL", [&connected](){connected.set_value();});
    connected.get_future().wait();
    std::cout<<"found client\n";
}
