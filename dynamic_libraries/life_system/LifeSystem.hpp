/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** LifeSystem
*/

#ifndef RTYPE_LIFESYSTEM_HPP
#define RTYPE_LIFESYSTEM_HPP

#include "entities/EntityManager.hpp"

#include "systems/System.hpp"

namespace rtype {
    namespace systems {
        /*!
         * @class Life system
         * @brief System to handle life and death in the game
         */
        class LifeSystem : public ecs::systems::System {
        public:
            LifeSystem(const std::string &name, ecs::managers::EntityManager &entityManager);
            ~LifeSystem() override = default;

            void onInit() override;
            void onUpdate(float elapsedTime) override;
            void onClose() override;
        private:
            ecs::managers::EntityManager &_entityManager;
        };
    }
}

#endif // RTYPE_LIFESYSTEM_HPP