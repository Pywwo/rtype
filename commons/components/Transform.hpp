
/* Created by Romain FOUYER on 18/11/2019 at 18:03. */


#ifndef RTYPE_TRANSFORM_HPP
#define RTYPE_TRANSFORM_HPP

#include "components/Component.hpp"
#include "types/Vector.hpp"

namespace rtype {
    namespace components {
        /*!
         * @class Transform
         * @brief Transform component
         *
         * Handle the position, the rotation and the scale of an entity
         */
        class Transform : public ecs::components::Component {
        public:
            /*!
             * Create a new transform component
             *
             * @param entity parent entity
             */
            explicit Transform(ecs::entities::Entity &entity);
            ~Transform() override = default;

            /*!
             * Set a new position
             *
             * @param x new x position
             * @param y new y position
             */
            void setPosition(float x, float y);

            /*!
             * Set a new scale
             *
             * @param x new x scale
             * @param y new y scale
             */
            void setScale(float x, float y);

            /*!
             * Set a new rotation
             *
             * @param x new x rotation
             * @param y new y rotation
             */
            void setRotation(float x, float y);

            /*!
             * Get the current position
             *
             * @return current position
             */
            [[nodiscard]] commons::Vector2<float> getPosition() const;

            /*!
             * Get the current rotation
             *
             * @return current rotation
             */
            [[nodiscard]] commons::Vector2<float> getRotation() const;

            /*!
             * Get the current scale
             *
             * @return current scale
             */
            [[nodiscard]] commons::Vector2<float> getScale() const;
        private:
            commons::Vector2<float> _position; /*!< handle transform position x & y */
            commons::Vector2<float> _rotation; /*!< handle the transform rotation x & y */
            commons::Vector2<float> _scale; /*!< handle the transform scale x & y */
        };
    }
}

#endif //RTYPE_TRANSFORM_HPP