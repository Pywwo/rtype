/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** TimerSystem
*/

#ifndef RTYPE_TIMERSYSTEM_HPP
#define RTYPE_TIMERSYSTEM_HPP

#include "entities/EntityManager.hpp"

#include "systems/System.hpp"

namespace rtype {
    namespace systems {
        /*!
         * @class TimerSystem
         * @brief Class for handle the time
         */
        class TimerSystem : public ecs::systems::System {
        public:
            /*!
             * @brief Create a new timer system
             * 
             * @param name name of the system to create
             */
            TimerSystem(const std::string &name, ecs::managers::EntityManager &entityManager);
            ~TimerSystem() override = default;

            void onInit() override;
            void onUpdate(float elapsedTime) override;
            void onClose() override;
        private:
            ecs::managers::EntityManager &_entityManager; /*!< handle all entity */
        };
    }
}

#endif // RTYPE_TIMERSYSTEM_HPP