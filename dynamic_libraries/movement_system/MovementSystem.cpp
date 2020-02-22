/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** MovementSystem
*/

#include "Controller.hpp"
#include "Transform.hpp"

#include "MovementSystem.hpp"

rtype::systems::MovementSystem::MovementSystem(const std::string &name, ecs::managers::EntityManager &entityManager)
: System(name), _entityManager(entityManager), _curElapsedTime(0)
{

}

void rtype::systems::MovementSystem::onInit()
{

}

void rtype::systems::MovementSystem::onUpdate(float elapsedTime)
{
    float elapsedTimeAsSecond = elapsedTime / 1000000000.0f;

    _curElapsedTime = elapsedTimeAsSecond;
    _entityManager.applyToEach(std::vector<std::string>({"Transform", "Controller"}), [elapsedTimeAsSecond](ecs::entities::Entity *entity) {
        auto transformComponent = dynamic_cast<rtype::components::Transform *>(entity->getComponent("Transform"));
        auto controllerComponent = dynamic_cast<rtype::components::Controller *>(entity->getComponent("Controller"));

        
        controllerComponent->setVelocity(rtype::commons::Vector2<float>(controllerComponent->getVelocity().x, controllerComponent->getVelocity().y));
        rtype::commons::Vector2<float> curVelocity = controllerComponent->getVelocity();

        transformComponent->setPosition(
                transformComponent->getPosition().x + curVelocity.x * elapsedTimeAsSecond,
                transformComponent->getPosition().y + curVelocity.y * elapsedTimeAsSecond
                );
    });
}

void rtype::systems::MovementSystem::onClose()
{

}

float rtype::systems::MovementSystem::getElapsedTime() const
{
    return _curElapsedTime;
}

extern "C"
{
    #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        __declspec(dllexport)
    #endif
    rtype::systems::MovementSystem *createSystem(ecs::managers::EntityManager &entityManager)
    {
        return new rtype::systems::MovementSystem("Movement system", entityManager);
    }
}