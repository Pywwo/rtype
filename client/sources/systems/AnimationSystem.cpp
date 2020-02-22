
/* Created by Romain FOUYER on 21/11/2019 at 17:46. */

#include "AnimationSystem.hpp"

#include "worlds/WorldManager.hpp"

#include "components/Rectangle.hpp"
#include "components/Animator.hpp"
#include "components/Parallax.hpp"

rtype::systems::AnimationSystem::AnimationSystem(const std::string &name)
: System(name)
{}

void rtype::systems::AnimationSystem::onInit()
{
}

void rtype::systems::AnimationSystem::onUpdate(float elapsedTime)
{
    float elapsedTimeAsSecond = elapsedTime / 1000000000.0f;
    auto &worldManager = rtype::worlds::WorldManager::getInstance();
    auto vectorForAnimation = std::vector<std::string>({"Rectangle", "Animator"});

    worldManager.getCurrentWorld()->getEntityManager().applyToEach(vectorForAnimation, [elapsedTimeAsSecond](ecs::entities::Entity *entity) {
        auto rectangleComponent = dynamic_cast<rtype::components::Rectangle *>(entity->getComponent("Rectangle"));
        auto animatorComponent = dynamic_cast<rtype::components::Animator *>(entity->getComponent("Animator"));

        auto currentAnimation = animatorComponent->getCurrentAnimation();

        if (animatorComponent->getCurrentAnimationIndex() == currentAnimation._endIndex && currentAnimation._isLooping)
            animatorComponent->setCurrentAnimation(animatorComponent->getCurrentAnimationName());
        if (currentAnimation._startIndex != currentAnimation._endIndex) {
            if (animatorComponent->deltaTime > currentAnimation._speed && currentAnimation._endIndex > animatorComponent->getCurrentAnimationIndex()) {
                animatorComponent->setCurrentAnimationIndex(animatorComponent->getCurrentAnimationIndex() + 1);
                animatorComponent->deltaTime = 0;
            } else if (animatorComponent->deltaTime > currentAnimation._speed && currentAnimation._endIndex < animatorComponent->getCurrentAnimationIndex()) {
                animatorComponent->setCurrentAnimationIndex(animatorComponent->getCurrentAnimationIndex() - 1);
                animatorComponent->deltaTime = 0;
            }
            animatorComponent->deltaTime += elapsedTimeAsSecond;
        } else {
            animatorComponent->deltaTime = 0;
        }
        rectangleComponent->setLeft(animatorComponent->getCurrentAnimationIndex() * rectangleComponent->getWidth());
    });

    worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Parallax", "Rectangle"}), [elapsedTimeAsSecond](ecs::entities::Entity *entity) {
        auto rectangle = dynamic_cast<rtype::components::Rectangle *>(entity->getComponent("Rectangle"));
        auto parallax = dynamic_cast<rtype::components::Parallax *>(entity->getComponent("Parallax"));

        rectangle->setLeft(rectangle->getLeft() + (parallax->getSpeed() * elapsedTimeAsSecond));
    });
}

void rtype::systems::AnimationSystem::onClose()
{
}