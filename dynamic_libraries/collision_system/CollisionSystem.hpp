
/* Created by Romain FOUYER on 28/11/2019 at 10:50. */


#ifndef RTYPE_COLLISIONSYSTEM_HPP
#define RTYPE_COLLISIONSYSTEM_HPP

#include "types/Vector.hpp"
#include "systems/System.hpp"
#include "entities/EntityManager.hpp"

namespace rtype {
    namespace systems {
        /*!
         * @class Collision System
         * @brief System who handles collision in game
         */
        class CollisionSystem : public ecs::systems::System {
        public:
            CollisionSystem(const std::string &name, ecs::managers::EntityManager &entityManager);
            ~CollisionSystem() override = default;

            /*!
             * Function to handle a little elapsed time to recompute collisions
             * @param elapsedTime current elapsed time as second
             */
            void tick(float elapsedTime);

            void onInit() override;
            void onUpdate(float elapsedTime) override;
            void onClose() override;

            /*!
             * Method with the logic of the collision system
             * it is called inside the tick method
             */
            void collisionLogic();

            /*!
             * Method to compute the collision of two entity
             *
             * @param compPositionA position of the first component
             * @param compSizeA size of the first component
             * @param compPositionB position of the second component
             * @param compSizeB size of the second component
             * @return true if the two entities collide, false if not
             */
            static bool isColliding(
                    rtype::commons::Vector2<float> compPositionA,
                    rtype::commons::Vector2<float> compSizeA,
                    rtype::commons::Vector2<float> compPositionB,
                    rtype::commons::Vector2<float> compSizeB);
        private:
            ecs::managers::EntityManager &_entityManager;
        };
    }
}


#endif //RTYPE_COLLISIONSYSTEM_HPP
