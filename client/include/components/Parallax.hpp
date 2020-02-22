
/* Created by Romain FOUYER on 22/11/2019 at 11:08. */


#ifndef RTYPE_PARALLAX_HPP
#define RTYPE_PARALLAX_HPP

#include "components/Component.hpp"

namespace rtype {
    namespace components {
        /*!
         * @class Parallax
         * @brief Parallax component
         */
        class Parallax : public ecs::components::Component {
        public:
            /*!
             * Create a new parallax component
             *
             * @param entity parent entity
             * @param speed speed of the parallax
             */
            Parallax(ecs::entities::Entity &entity, float speed);
            ~Parallax() override = default;

            /*!
             * Get the current speed of the parallax
             *
             * @return the speed of the parallax
             */
            [[nodiscard]] float getSpeed() const;

            /*!
             * Set a new speed to the parallax component
             *
             * @param newSpeed new speed for the parallax component
             */
            void setSpeed(float newSpeed);
        private:
            float _speed; /*!< handle the current speed */
        };
    }
}

#endif // RTYPE_PARALLAX_HPP