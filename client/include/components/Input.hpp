
/* Created by Romain FOUYER on 20/11/2019 at 17:08. */


#ifndef RTYPE_INPUT_HPP
#define RTYPE_INPUT_HPP

#include "components/Component.hpp"
#include <functional>
#include <SFML/Graphics.hpp>

namespace rtype {
    namespace components {
        /*!
         * @class Input
         * @brief Component input
         */
        class Input : public ecs::components::Component {
        public:
            /*!
             * Constructor for the Input Component
             *
             * @param entity parent entity
             */
            explicit Input(ecs::entities::Entity &entity);
            ~Input() override = default;

            /*!
             * Append the new character to the _playerInput
             *
             * @param c new character to be add
             */
            void newInput(char c);
            /*!
             * Delete the last character, on backspace key
             */
            void deleteLastCharacter();

            [[nodiscard]] const sf::String &getCurrentInput() const;
            /*!
             * Set a callback to the input called on Enter key press
             *
             * @param callback callback function (lambda, or whatever...)
             */
            void setCallback(std::function<void(void)> callback);

            /*!
             * Get the callback of the input
             *
             * @return the callback function
             */
            std::function<void(void)> &getCallback();
        private:
            sf::String _playerInput; /*!< handle name of the player input */

            std::function<void(void)> _callback; /*!< std function for callback */
        };
    }
}


#endif //RTYPE_INPUT_HPP
