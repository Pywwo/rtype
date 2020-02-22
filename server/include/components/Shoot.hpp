/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Shoot
*/

#ifndef RTYPE_SHOOT_HPP
#define RTYPE_SHOOT_HPP

#include "components/Component.hpp"

namespace rtype {
    namespace components {
        /*!
         * @class Shoot component
         * @brief component for handle the shoot
         */
        class Shoot : public ecs::components::Component {
        public:
            Shoot(ecs::entities::Entity &entity);
            ~Shoot() override = default;
        };
    }
}

#endif // RTYPE_SHOOT_HPP