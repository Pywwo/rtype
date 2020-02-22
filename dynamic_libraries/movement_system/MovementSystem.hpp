/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** MovementSystem
*/

#ifndef RTYPE_MOVEMENTSYSTEM_HPP
#define RTYPE_MOVEMENTSYSTEM_HPP

#include "entities/EntityManager.hpp"

#include "systems/System.hpp"

namespace rtype {
    namespace systems {
        /*!
         * @class MovementSystem
         * @brief System to handle the movement of the Controller
         */
        class MovementSystem : public ecs::systems::System {
        public:
            /*!
             * @brief Create a new movement system
             * 
             * @param name name of the system to create
             */
            MovementSystem(const std::string &name, ecs::managers::EntityManager &entityManager);
            ~MovementSystem() override = default;

            void onInit() override;
            void onUpdate(float elapsedTime) override;
            void onClose() override;

            [[nodiscard]] float getElapsedTime() const;
        private:
            ecs::managers::EntityManager &_entityManager; /*!< handle all entity */

            float _curElapsedTime; /*!< current elapsed time in MovementSystem */
        };
    }
}

#endif // RTYPE_MOVEMENTSYSTEM_HPP