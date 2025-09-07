#include "libmycuda.hpp"
#include "atomic"
#include "HubClient.hpp"
#include <csignal>
#include <thread>

static std::atomic_bool g_stop{false};
void sigint_handler(int) { g_stop = true; }


// --------------------
// Example usage
// --------------------
int main() {
    Lwp::HubClient client;
    client.connect("HAL");
}
