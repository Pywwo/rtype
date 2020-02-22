
/* Created by Romain FOUYER on 29/11/2019 at 15:41. */

#include "ScoreSystem.hpp"

#include "worlds/WorldManager.hpp"

#include "components/Score.hpp"
#include "components/Text.hpp"
#include "components/Transform.hpp"
#include "components/Camera.hpp"

rtype::systems::ScoreSystem::ScoreSystem(const std::string &name)
: System(name)
{
}

void rtype::systems::ScoreSystem::onInit() {}

void rtype::systems::ScoreSystem::onUpdate(float elapsedTime)
{
    auto &worldManager = rtype::worlds::WorldManager::getInstance();

    worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Score", "Text", "Transform", "Camera"}), [](ecs::entities::Entity *entity) {
        auto scoreComponent = dynamic_cast<rtype::components::Score *>(entity->getComponent("Score"));
        auto textComponent = dynamic_cast<rtype::components::Text *>(entity->getComponent("Text"));
        auto cameraComponent = dynamic_cast<rtype::components::Camera *>(entity->getComponent("Camera"));
        auto transformComponent = dynamic_cast<rtype::components::Transform *>(entity->getComponent("Transform"));

        scoreComponent->setScore(scoreComponent->getScore() + 1);
        textComponent->setString("SCORE: " + std::to_string(scoreComponent->getScore()));
        transformComponent->setPosition(cameraComponent->getCenter().x - 200, cameraComponent->getCenter().y + (cameraComponent->getSize().y / 2) - 25);
    });
}

void rtype::systems::ScoreSystem::onClose() {}