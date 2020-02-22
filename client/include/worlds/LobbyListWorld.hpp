
/* Created by Romain FOUYER on 25/11/2019 at 11:39. */

#ifndef RTYPE_LOBBYLISTWORLD_HPP
#define RTYPE_LOBBYLISTWORLD_HPP

#include "World.hpp"

#include "Lobby.hpp"

namespace rtype {
    namespace worlds {
        /*!
         * @class Lobby List World
         * @brief World for the list of lobbies
         */
        class LobbyListWorld : public World {
        public:
            explicit LobbyListWorld(const std::string &name);
            ~LobbyListWorld() override = default;

            /*!
             * Set the new lobbies received by the server
             *
             * @param newLobbies vector of lobby, see: Lobby.hpp
             */
            void setNewLobbies(std::vector<Lobby> &newLobbies);
        private:
            /*!
             * Setup the UI of the world, like the back button or the create lobby button
             */
            void setupUI();

            /*!
             * Setup the lobby components to display them easily
             *
             * @param lobbyIndex index of the lobby
             * @param lobby lobby data structure
             */
            void setupLobbyComponents(unsigned long lobbyIndex, const Lobby &lobby);
        private:
            std::vector<Lobby> _lobbies;
        };
    }
}


#endif //RTYPE_LOBBYLISTWORLD_HPP
