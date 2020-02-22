
/* Created by Romain FOUYER on 05/11/2019 at 10:57. */


#ifndef RTYPE_SFMLSYSTEM_HPP
#define RTYPE_SFMLSYSTEM_HPP

#include "systems/System.hpp"

#include <SFML/Graphics.hpp>

namespace rtype {

    namespace systems {

        /*!
         * @class SFMLSystem
         * @brief System who handles everything based on SFML library
         */
        class SFMLSystem : public ecs::systems::System {
        public:
            SFMLSystem(const std::string &name, unsigned int width, unsigned int height);

            void onInit() override;

            void onUpdate(float elapsedTime) override;

            void onClose() override;

            /*!
             * Get the main window
             * @return the main window
             */
            sf::RenderWindow &getWindow();
            /*!
             * Function called inside the render just after the update
             */
            void render();

            /*!
             * Function where all entities would be updated
             *
             * @param elapsedTime current elapsedTime in second
             */
            void update(float elapsedTime);

            /*!
             * Function to handle all sfml events
             */
            void events();
        private:
            /*!
             * Function to handle the input of the user
             */
            void movementInput();

            /*!
             * Caught signal
             * @param signal signal caught
             */
            static void signalHandler(int signal);

            /*!
             * @brief handle the disconnection of a client
             */
            void handleDisconnection();

        private:
            sf::RenderWindow _window; /*!< rendering window for the rtype game */
            sf::Event _event; /*!< handle all event in rtype game */

            static bool sigintCaught; /*!< true if sigint caught false otherwise */
        };
    }
}

#endif //RTYPE_SFMLSYSTEM_HPP