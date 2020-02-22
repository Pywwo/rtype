
/* Created by Romain FOUYER on 18/11/2019 at 13:23. */


#ifndef RTYPE_MENUWORLD_HPP
#define RTYPE_MENUWORLD_HPP

#include "World.hpp"

namespace rtype {
    namespace worlds {
        /*!
         * @class Menu World
         * @brief Class for the menu world who handle the rtype menu
         */
        class MenuWorld : public World {
        public:
            explicit MenuWorld(const std::string &name);
            ~MenuWorld() override;
        private:
            /*!
             * @brief function for setup the background of the Menu world
             */
            void setupBackground();
            /*!
             * @brief function for setup the logo of the Menu world
             */
            void setupLogo();
            /*!
             * @brief function for setup the exit button of the Menu world
             */
            void setupExitButton();
            /*!
             * @brief function for setup the play button of the Menu world
             */
            void setupPlayButton();
            /*!
             * @brief function for setup the settings button of the Menu world
             */
            void setupSettingsButton();
            /*!
             * @brief function for setup the input of the Menu world
             */
            void setupInput();
            /*!
             * @brief function for setup the credits of the Menu world
             */
            void setupCredits();
        };
    }
}


#endif //RTYPE_MENUWORLD_HPP
