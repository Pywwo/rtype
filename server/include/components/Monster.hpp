/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Monster
*/

#ifndef RTYPE_MONSTER_HPP
#define RTYPE_MONSTER_HPP

#include "components/Component.hpp"
#include "other/EnemyId.hpp"

namespace rtype {
    namespace components {
        /*!
         * @class Monster component
         * @brief component for handle all monster in rtype game
         */
        class Monster : public ecs::components::Component {
        public:
            Monster(ecs::entities::Entity &entity, const Enemy &enemyId);
            ~Monster() override = default;

            /*!
             * Get the current monster id
             * @return the current monster id
             */
            Enemy getId();

            /*!
             * Set the monster id
             * @param Enemy the enemy id to set
             */
            void setId(const Enemy &enemyId);

            /*!
             * Get the current state of the monster
             * @return true if monster is spawn, else otherwise
             */
            bool isSpawned() const;

            /*!
             * Set the spawn state
             * @param state the state to set
             */
            void setSpawnState(const bool &state);
        private:
            Enemy _enemyId; /*!< contain monster id */
            bool _isSpawn; /*!< contain the state of the monster */
        };
    }
}

#endif // RTYPE_MONSTER_HPP