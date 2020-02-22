/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** CameraSystem
*/

#include "CameraSystem.hpp"
#include "components/Camera.hpp"

rtype::systems::CameraSystem::CameraSystem(const std::string &name, ecs::managers::EntityManager &entityManager)
    : System(name), _entityManager(entityManager)
{

}

void rtype::systems::CameraSystem::onInit()
{

}

void rtype::systems::CameraSystem::onUpdate(float elapsedTime)
{
    float elapsedTimeAsSecond = elapsedTime / 1000000000.0f;

    _entityManager.applyToEach(std::vector<std::string>({"Camera"}), [elapsedTimeAsSecond](ecs::entities::Entity *entity) {
        auto camera = dynamic_cast<rtype::components::Camera *>(entity->getComponent("Camera"));

        camera->move(10.0f * elapsedTimeAsSecond, 0);
    });
}

void rtype::systems::CameraSystem::onClose()
{

}

extern "C"
{
    #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        __declspec(dllexport)
    #endif
    rtype::systems::CameraSystem *createSystem(ecs::managers::EntityManager &entityManager)
    {
        return new rtype::systems::CameraSystem("Camera system", entityManager);
    }
}