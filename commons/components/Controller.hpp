
/* Created by Romain FOUYER on 20/11/2019 at 21:20. */


#ifndef RTYPE_CONTROLLER_HPP
#define RTYPE_CONTROLLER_HPP

#include "types/Vector.hpp"

#include "components/Component.hpp"

namespace rtype {
    namespace components {
        /*!
         * @class Controller
         * @brief Component who handles movement based on input
         */
        class Controller : public ecs::components::Component {
        public:
            /*!
             * Constructor for the Controller Component
             *
             * @param entity parent entity
             * @param speed speed of the controller
             */
            Controller(ecs::entities::Entity &entity, float speed);
            ~Controller() override = default;

            /*!
             * Get the current speed of the controller
             *
             * @return the current speed;
             */
            [[nodiscard]] float getSpeed() const;

            /*!
             * Set a new speed to the controller
             *
             * @param speed new speed
             */
            void setSpeed(float speed);

            /*!
             * Get the current velocity of the controller
             *
             * @return the current velocity
             */
            [[nodiscard]] const commons::Vector2<float> &getVelocity() const;

            /*!
             * Set a new velocity to the controller
             *
             * @param velocity new velocity for the client
             */
            void setVelocity(const commons::Vector2<float> &velocity);

        private:
            float _speed; /*!< handle the speed of the controller */
            rtype::commons::Vector2<float> _velocity; /*!< vector for handle all velocity */
        };
    }
}

#endif //RTYPE_CONTROLLER_HPP