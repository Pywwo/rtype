
/* Created by Romain FOUYER on 04/11/2019 at 17:28. */

#include "Game.hpp"
#include "RtypeServer.hpp"

int main([[maybe_unused]] int ac, [[maybe_unused]] char **av)
{
    rtype::network::RtypeServer server;

    try {
        server.run(6969);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
