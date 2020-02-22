
/* Created by Romain FOUYER on 01/12/2019 at 19:55. */


#include "GarbageSystem.hpp"

#include "components/Transform.hpp"
#include "components/Status.hpp"

rtype::systems::GarbageSystem::GarbageSystem(const std::string &name, ecs::managers::EntityManager &entityManager)
: System(name), _entityManager(entityManager)
{

}

void rtype::systems::GarbageSystem::onInit()
{
}

void rtype::systems::GarbageSystem::onUpdate([[maybe_unused]] float elapsedTime)
{
    std::pair<float, float> farPosition(5000000, 5000000);

    _entityManager.applyToEach(std::vector<std::string>({"Transform", "Controller"}), [&farPosition](ecs::entities::Entity *entity) {
        if (entity->getName().find("player") != std::string::npos) {
            auto transform = dynamic_cast<rtype::components::Transform *>(entity->getComponent("Transform"));
            if (farPosition.first > transform->getPosition().x) {
                farPosition.first = transform->getPosition().x;
            }
        }
    });

    std::vector<std::string> nameToDelete;

    _entityManager.applyToEach(std::vector<std::string>({"Transform", "Status", "Monster"}), [&farPosition, &nameToDelete](ecs::entities::Entity *entity) {
        auto transform = dynamic_cast<rtype::components::Transform *>(entity->getComponent("Transform"));
        auto status = dynamic_cast<rtype::components::Status *>(entity->getComponent("Status"));

        if (transform->getPosition().x < farPosition.first - 700)
            status->setAlive(false);
    });
}

void rtype::systems::GarbageSystem::onClose()
{

}

extern "C"
{
    #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    __declspec(dllexport)
    #endif
    rtype::systems::GarbageSystem *createSystem(ecs::managers::EntityManager &entityManager)
    {
        return new rtype::systems::GarbageSystem("Garbage system", entityManager);
    }
}