/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** DLLSystem.hpp
*/

/* Created the 28/11/2019 at 16:07 by jbulteau */

#ifndef RTYPE_DLLSYSTEM_HPP
#define RTYPE_DLLSYSTEM_HPP

#include <dl/DLLoader.hpp>
#include "systems/SystemManager.hpp"
#include "systems/System.hpp"

#include "entities/EntityManager.hpp"

namespace rtype {

    namespace systems {

        class DLLSystem : public ecs::systems::System {
        public:
            explicit DLLSystem(const std::string &name, ecs::managers::SystemManager &systemManager, ecs::managers::EntityManager &entityManager);
            DLLSystem(const DLLSystem &other) = delete;
            DLLSystem &operator=(const DLLSystem &rhs) = delete;

            void onInit() override;
            void onUpdate(float elapsedTime) override;
            void onClose() override;

        private:
            ecs::managers::SystemManager &_systemManager;
            ecs::managers::EntityManager &_entityManager;
            commons::DLLoader _dlLoader;
            std::vector<std::string> _systems;
        };
    }
}

#endif //RTYPE_DLLSYSTEM_HPP
