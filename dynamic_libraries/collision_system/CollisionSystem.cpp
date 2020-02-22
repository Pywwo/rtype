
/* Created by Romain FOUYER on 28/11/2019 at 10:50. */

#include "CollisionSystem.hpp"

#include "Transform.hpp"
#include "components/BoxCollider.hpp"
#include "components/Damager.hpp"
#include "Status.hpp"

rtype::systems::CollisionSystem::CollisionSystem(const std::string &name,ecs::managers::EntityManager &entityManager)
: System(name), _entityManager(entityManager)
{
}

void rtype::systems::CollisionSystem::onInit()
{
    auto vectorForColliderPosition = std::vector<std::string>({"Transform", "BoxCollider"});

    _entityManager.applyToEach(vectorForColliderPosition, [](ecs::entities::Entity *entity) {
        auto boxCollider = dynamic_cast<rtype::components::BoxCollider *>(entity->getComponent("BoxCollider"));
        auto transform = dynamic_cast<rtype::components::Transform *>(entity->getComponent("Transform"));

        boxCollider->setPosition(rtype::commons::Vector2<float>(
                transform->getPosition().x - (boxCollider->getSize().x / 2),
                transform->getPosition().y - (boxCollider->getSize().y / 2)
        ));
    });
}

void rtype::systems::CollisionSystem::onUpdate(float elapsedTime)
{
    auto vectorForColliderPosition = std::vector<std::string>({"Transform", "BoxCollider"});

    _entityManager.applyToEach(vectorForColliderPosition, [](ecs::entities::Entity *entity) {
        auto boxCollider = dynamic_cast<rtype::components::BoxCollider *>(entity->getComponent("BoxCollider"));
        auto transform = dynamic_cast<rtype::components::Transform *>(entity->getComponent("Transform"));

        boxCollider->setPosition(rtype::commons::Vector2<float>(
                transform->getPosition().x - (boxCollider->getSize().x / 2),
                transform->getPosition().y - (boxCollider->getSize().y / 2)
        ));
    });
    tick(elapsedTime);
}

void rtype::systems::CollisionSystem::onClose()
{
}

void rtype::systems::CollisionSystem::tick(float elapsedTime)
{
    static float deltaTime = 0;

    if (deltaTime > 2) {
        collisionLogic();
        deltaTime = 0;
    }
    deltaTime += (elapsedTime / 1000000);
}

void rtype::systems::CollisionSystem::collisionLogic()
{
    auto damagerEntities = _entityManager.getEntitiesWithComponents(std::vector<std::string>({"Damager", "BoxCollider"}));
    auto colliderEntities = _entityManager.getEntitiesWithComponents(std::vector<std::string>({"Status", "BoxCollider"}));

    for (auto &dEntity : damagerEntities) {
        for (auto &cEntity : colliderEntities) {
            if (dEntity == cEntity || (dEntity->getName().find("enemy") != std::string::npos && cEntity->getName().find("enemy") != std::string::npos))
                continue;

            auto status = dynamic_cast<rtype::components::Status *>(cEntity->getComponent("Status"));
            auto damager = dynamic_cast<rtype::components::Damager *>(dEntity->getComponent("Damager"));

            auto colliderA = dynamic_cast<rtype::components::BoxCollider *>(cEntity->getComponent("BoxCollider"));
            auto colliderB = dynamic_cast<rtype::components::BoxCollider *>(dEntity->getComponent("BoxCollider"));

            if (isColliding(colliderA->getPosition(), colliderA->getSize(), colliderB->getPosition(), colliderB->getSize())) {
                if (damager->shouldDestroyOnCollide())
                    status->setAlive(false);
            }

        }
    }
}

bool rtype::systems::CollisionSystem::isColliding(rtype::commons::Vector2<float> compPositionA,
                                                  rtype::commons::Vector2<float> compSizeA,
                                                  rtype::commons::Vector2<float> compPositionB,
                                                  rtype::commons::Vector2<float> compSizeB)
{
    return !((compPositionB.x >= compPositionA.x + compSizeA.x) || (compPositionB.x + compSizeB.x <= compPositionA.x)
             || (compPositionB.y >= compPositionA.y + compSizeA.y) || (compPositionB.y + compSizeB.y <= compPositionA.y));
}

extern "C"
{
    #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        __declspec(dllexport)
    #endif
    rtype::systems::CollisionSystem *createSystem(ecs::managers::EntityManager &entityManager)
    {
        return new rtype::systems::CollisionSystem("Collision system", entityManager);
    }
}