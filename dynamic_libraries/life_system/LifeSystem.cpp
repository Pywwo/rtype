/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** LifeSystem
*/

#include "Status.hpp"
#include "Controller.hpp"
#include "Timer.hpp"

#include "LifeSystem.hpp"

rtype::systems::LifeSystem::LifeSystem(const std::string &name, ecs::managers::EntityManager &entityManager)
    : System(name), _entityManager(entityManager)
{

}

void rtype::systems::LifeSystem::onInit()
{

}

void rtype::systems::LifeSystem::onUpdate([[maybe_unused]] float elapsedTime)
{
    _entityManager.applyToEach(std::vector<std::string>({"Status", "Controller", "Transform"}), [](ecs::entities::Entity *entity) {
        auto statusComponent = dynamic_cast<rtype::components::Status *>(entity->getComponent("Status"));
        auto controllerComponent = dynamic_cast<rtype::components::Controller *>(entity->getComponent("Controller"));

        if (!statusComponent->isAlive()) {
            if (!entity->hasComponent("Timer"))
                entity->assignComponent("Timer", new rtype::components::Timer(*entity, 1));
            controllerComponent->setVelocity(rtype::commons::Vector2<float>(0, 10));
        }
    });
}

void rtype::systems::LifeSystem::onClose()
{

}

extern "C"
{
    #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        __declspec(dllexport)
    #endif
    rtype::systems::LifeSystem *createSystem(ecs::managers::EntityManager &entityManager)
    {
        return new rtype::systems::LifeSystem("Life system", entityManager);
    }
}