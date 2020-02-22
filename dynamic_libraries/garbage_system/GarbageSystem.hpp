
/* Created by Romain FOUYER on 01/12/2019 at 19:55. */


#ifndef RTYPE_GARBAGESYSTEM_HPP
#define RTYPE_GARBAGESYSTEM_HPP

#include "systems/System.hpp"

#include "entities/EntityManager.hpp"

namespace rtype {
    namespace systems {
        /*!
         * @class Garbage System
         * @brief System to handle the deletion of entities
         */
        class GarbageSystem : public ecs::systems::System {
        public:
            GarbageSystem(const std::string &name, ecs::managers::EntityManager &entityManager);
            ~GarbageSystem() override = default;

            void onInit() override;
            void onUpdate(float elapsedTime) override;
            void onClose() override;
        private:
            ecs::managers::EntityManager &_entityManager;
        };
    }
}


#endif //RTYPE_GARBAGESYSTEM_HPP
