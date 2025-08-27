#include "liba/liba.h"
#include "libmycuda/libmycuda.hpp"
#include "atomic"
#include "liblwp/HubClient.hpp"

static std::atomic_bool g_stop{false};
void sigint_handler(int) { g_stop = true; }

int main(int argc, char** argv) {
    try {
        std::signal(SIGINT, sigint_handler);
        std::optional<std::string> nameFilter;
        HubClient client;
        client.connect(nameFilter);
        client.subscribe_notifications(obs);
    } catch (...) {
        std::cerr << "Nie udało się zarejestrować handlera SIGINT.\n";
        return 1;
    }
}
