
/* Created by Romain FOUYER on 25/11/2019 at 10:30. */


#include <components/Controller.hpp>
#include "LifeSystem.hpp"

#include "worlds/WorldManager.hpp"
#include "worlds/GameWorld.hpp"

#include "components/Status.hpp"
#include "components/Timer.hpp"
#include "components/Transform.hpp"


rtype::systems::LifeSystem::LifeSystem(const std::string &name)
: System(name)
{
}

void rtype::systems::LifeSystem::onInit() {}

void rtype::systems::LifeSystem::onUpdate([[maybe_unused]] float elapsedTime)
{
    auto &worldManager = rtype::worlds::WorldManager::getInstance();
    auto curWorld = worldManager.getCurrentWorld();

    curWorld->getEntityManager().applyToEach(std::vector<std::string>({"Status", "Transform"}), [&worldManager](ecs::entities::Entity *entity) {

        auto statusComponent = dynamic_cast<rtype::components::Status *>(entity->getComponent("Status"));
        auto transformComponent = dynamic_cast<rtype::components::Transform *>(entity->getComponent("Transform"));

        if (!statusComponent->isAlive()) {
            if (!entity->hasComponent("Timer")) {
                entity->assignComponent("Timer", new rtype::components::Timer(*entity, 1));
                dynamic_cast<rtype::worlds::GameWorld *>(worldManager.getCurrentWorld())->addEffect(
                        rtype::components::Effect::EffectType::FIRE_EXPLOSION,
                        transformComponent->getPosition()
                );
            }
        }
    });
}

void rtype::systems::LifeSystem::onClose() {}