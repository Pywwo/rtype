
/* Created by Romain FOUYER on 18/11/2019 at 19:19. */


#ifndef RTYPE_OPACITYCHANGER_HPP
#define RTYPE_OPACITYCHANGER_HPP

#include "components/Component.hpp"

namespace rtype {
    namespace components {
        /*!
         * @class OpacityChanger
         * @brief Component to change opacity of a sprite
         */
        class OpacityChanger : public ecs::components::Component {
        public:
            /*!
             * Constructor of the component Opacity Changer
             *
             * Opacity index : [0;255]
             *
             * @param entity parent entity
             * @param begin opacity value at the beginning of changes
             * @param end opacity value at the end of changes
             * @param speed value of the speed for changes
             */
            explicit OpacityChanger(ecs::entities::Entity &entity, float begin = 0, float end = 255, float speed = 50);

            ~OpacityChanger() override = default;

            /*!
             * Getter for the begin value
             *
             * @return begin value
             */
            [[nodiscard]] float getBegin() const;

            /*!
             * Getter for the end value
             *
             * @return end value
             */
            [[nodiscard]] float getEnd() const;

            /*!
             * Getter for the speed value
             *
             * @return speed value
             */
            [[nodiscard]] float getSpeed() const;

            /*!
             * Set a new begin index
             *
             * @param begin new begin index
             */
            void setBegin(float begin);

            /*!
             * Set a new end index
             *
             * @param end new end index
             */
            void setEnd(float end);

            /*!
             * Set a new speed
             *
             * @param speed new speed
             */
            void setSpeed(float speed);
        private:
            float _begin; /*!< handle the begin of the speed */
            float _end; /*!< handle the end of the speed */
            float _speed; /*!< handle the current speed */
        };
    }
}

#endif //RTYPE_OPACITYCHANGER_HPP