
/* Created by Romain FOUYER on 20/11/2019 at 23:18. */


#include "MovementSystem.hpp"

#include "worlds/WorldManager.hpp"

#include "components/Controller.hpp"
#include "components/Transform.hpp"
#include "components/Animator.hpp"
#include "components/Camera.hpp"

rtype::systems::MovementSystem::MovementSystem(const std::string &name)
: System(name)
{
}

void rtype::systems::MovementSystem::onInit()
{

}

void rtype::systems::MovementSystem::onUpdate(float elapsedTime)
{
    float elapsedTimeAsSecond = elapsedTime / 1000000000.0f;
    auto &worldManager = rtype::worlds::WorldManager::getInstance();

    worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Animator", "Controller"}), [](ecs::entities::Entity *entity) {
        auto animatorComponent = dynamic_cast<rtype::components::Animator *>(entity->getComponent("Animator"));
        auto controllerComponent = dynamic_cast<rtype::components::Controller *>(entity->getComponent("Controller"));

        if (controllerComponent->getVelocity().y > 0 && animatorComponent->getCurrentAnimationName() != "DOWN" && (entity->getName().find("player") != std::string::npos || entity->getName().find("enemy") != std::string::npos))
            animatorComponent->setCurrentAnimation("DOWN");
        else if (controllerComponent->getVelocity().y < 0 && animatorComponent->getCurrentAnimationName() != "UP" && (entity->getName().find("player") != std::string::npos || entity->getName().find("enemy") != std::string::npos))
            animatorComponent->setCurrentAnimation("UP");
        else if (controllerComponent->getVelocity().y == 0 && animatorComponent->getCurrentAnimationName() != "IDLE" && (entity->getName().find("player") != std::string::npos || entity->getName().find("enemy") != std::string::npos))
            animatorComponent->setCurrentAnimation("IDLE");
    });

    if (worldManager.getCurrentWorld()->getEntityManager().getEntityByName("camera")) {
        worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Transform", "Controller"}), [elapsedTimeAsSecond](ecs::entities::Entity *entity) {

            auto transformComponent = dynamic_cast<rtype::components::Transform *>(entity->getComponent("Transform"));
            auto controllerComponent = dynamic_cast<rtype::components::Controller *>(entity->getComponent("Controller"));

            rtype::commons::Vector2<float> curVelocity = controllerComponent->getVelocity();

            transformComponent->setPosition(
                    transformComponent->getPosition().x + (curVelocity.x * elapsedTimeAsSecond),
                    transformComponent->getPosition().y + (curVelocity.y * elapsedTimeAsSecond)
                    );
        });
    }

}

void rtype::systems::MovementSystem::onClose()
{

}