#include "libmycuda.hpp"
#include "atomic"
#include "HubClient.hpp"
#include <csignal>

static std::atomic_bool g_stop{false};
void sigint_handler(int) { g_stop = true; }

int main(int, char** ) {
    try {
        std::signal(SIGINT, sigint_handler);
        std::optional<std::string> nameFilter;
        LWP::HubClient client;
        client.connect(nameFilter);
        client.subscribe_notifications();
    } catch (...) {
        std::cerr << "Nie udało się zarejestrować handlera SIGINT.\n";
        return 1;
    }
}
