
/* Created by Romain FOUYER on 19/11/2019 at 11:57. */


#ifndef RTYPE_BUTTON_HPP
#define RTYPE_BUTTON_HPP

#include "components/Component.hpp"

#include <functional>

namespace rtype {
    namespace components {
        /*!
         * @class Button
         * @brief Button component, composed of a callback function
         */
        class Button : public ecs::components::Component {
        public:
            /*!
             * Button component constructor
             *
             * @param entity parent entity
             * @param callback callback called on button click
             */
            Button(ecs::entities::Entity &entity, std::function<void(void)> callback);

            ~Button() override = default;

            /*!
             * Return the callback function
             *
             * @return the callback function, when button is clicked
             */
            std::function<void(void)> &getCallback();

        private:
            std::function<void(void)> _callback; /*!< std function for handle callback */
        };
    }
}

#endif //RTYPE_BUTTON_HPP