
/* Created by Romain FOUYER on 28/11/2019 at 10:27. */


#ifndef RTYPE_BOXCOLLIDER_HPP
#define RTYPE_BOXCOLLIDER_HPP

#include "components/Component.hpp"

#include "types/Vector.hpp"

namespace rtype {
    namespace components {
        /*!
         * @class box Collider
         * @brief Class for handle collision in rtype game
         */
        class BoxCollider : public ecs::components::Component {
        public:
            BoxCollider(ecs::entities::Entity &entity, rtype::commons::Vector2<float> size);
            ~BoxCollider() override = default;

            /*!
             * @brief get the current size of the box collider
             * @return vector x & y of the collider size
             */
            [[nodiscard]] const rtype::commons::Vector2<float> &getSize() const;

            /*!
             * @brief function for set the size of a box collider
             * @param newSize vector x & y of collider size
             */
            void setSize(rtype::commons::Vector2<float> newSize);

            /*!
             * @brief function for get the position of the collider
             * @return vector x & y of the collider position
             */
            [[nodiscard]] const rtype::commons::Vector2<float> &getPosition() const;

            /*!
             * @brief function for set position of the collider
             * @param newPosition vector x & y of collider position
             */
            void setPosition(rtype::commons::Vector2<float> newPosition);
        private:
            rtype::commons::Vector2<float> _size; /*!< current size of the box collider */
            rtype::commons::Vector2<float> _position; /*!< current position of the box collider */
        };
    }
}

#endif //RTYPE_BOXCOLLIDER_HPP