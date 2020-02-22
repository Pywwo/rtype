/* Created by Antoine CARLIER on 25/11/2019 at 12:16. */

#ifndef RTYPE_INLOBBYWORLD_HPP
#define RTYPE_INLOBBYWORLD_HPP

#include "World.hpp"
#include "Lobby.hpp"

namespace rtype {
    namespace worlds {
        /*!
         * @class In lobby world
         * @brief Class for the in lobby world who handle the lobby world for all player in
         */
        class InLobbyWorld : public World {
        public:
            explicit InLobbyWorld(const std::string &name);
            ~InLobbyWorld() override = default;

            /*!
             * @brief function for set a lobby to the world
             * @param lobby to set for the world
             */
            void setLobby(const Lobby &lobby);
        private:

            /*!
             * @brief function for setup the background of the lobby world
             */
            void setupBackground();
            /*!
             * @brief function for setup the lobby text of the lobby world
             */
            void setupLobbyText();
            /*!
             * @brief function for setup the player text of the lobby world
             */
            void setupPlayerText();
            /*!
             * @brief function for setup the list player text of the lobby world
             */
            void setupListPlayerText();
            /*!
             * @brief function for setup the start button of the lobby world
             */
            void setupStartButton();
            /*!
             * @brief function for setup the back button of the lobby world
             */
            void setupBackButton();
        private:
            Lobby _lobby; /*!< Handle the actual lobby */
        };
    }
}

#endif // RTYPE_INLOBBYWORLD_HPP