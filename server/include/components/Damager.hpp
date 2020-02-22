
/* Created by Romain FOUYER on 28/11/2019 at 10:43. */


#ifndef RTYPE_DAMAGER_HPP
#define RTYPE_DAMAGER_HPP

#include "components/Component.hpp"

namespace rtype {
    namespace components {
        /*!
         * @class Damager Component
         * @brief Component to handle entities who make damages
         */
        class Damager : public ecs::components::Component {
        public:
            /*!
             * Construct a new damager
             * @param entity parent entity
             * @param damagerEntity parent entity
             * @param shouldDestroyOnCollide if on collide destroy the entity collided
             */
            Damager(ecs::entities::Entity &entity, ecs::entities::Entity &damagerEntity, bool shouldDestroyOnCollide);
            ~Damager() override = default;

            /*!
             * Set the damager entity
             * @param newDamagerEntity
             */
            void setDamagerEntity(ecs::entities::Entity &newDamagerEntity);
            /*!
             * Get the damager entity
             * @return the damager entity
             */
            [[nodiscard]] const ecs::entities::Entity &getDamagerEntity() const;

            /*!
             * Function who said if the damager destroy on collide or make damages
             * @return should destroy on collide
             */
            [[nodiscard]] bool shouldDestroyOnCollide() const;

            /*!
             * Set if the damager destroy on collide or not
             * @param shouldDestroy
             */
            void setShouldDestroyOnCollide(bool shouldDestroy);
        private:
            ecs::entities::Entity &_damagerEntity; /*< Parent entity who sends the damager like the shoot */

            bool _shouldDestroyOnCollide; /*< Boolean who said if the damager destroys on collide */
        };
    }
}


#endif //RTYPE_DAMAGER_HPP
