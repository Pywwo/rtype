/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** CameraSystem
*/

#ifndef RTYPE_CAMERASYSTEM_HPP
#define RTYPE_CAMERASYSTEM_HPP

#include "entities/EntityManager.hpp"

#include "systems/System.hpp"

namespace rtype {
    namespace systems {
        /*!
         * @class Camera System
         * @brief System to handle the camera
         */
        class CameraSystem : public ecs::systems::System {
        public:
            CameraSystem(const std::string &name, ecs::managers::EntityManager &entityManager);
            ~CameraSystem() override = default;

            void onInit() override;
            void onUpdate(float elapsedTime) override;
            void onClose() override;
        private:
            ecs::managers::EntityManager &_entityManager;
        };
    }
}

#endif // RTYPE_CAMERASYSTEM_HPP