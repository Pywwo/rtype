/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** MonsterSystem
*/

#ifndef RTYPE_MONSTERSYSTEM_HPP
#define RTYPE_MONSTERSYSTEM_HPP

#include "entities/EntityManager.hpp"

#include "systems/System.hpp"
#include "components/Transform.hpp"
#include "components/Controller.hpp"
#include "components/Status.hpp"
#include "components/Monster.hpp"
#include "components/BoxCollider.hpp"
#include "other/EnemyId.hpp"
#include "ThreadSafeQueue.hpp"
#include "Datagram.hpp"
#include "HostInfos.hpp"
#include "other/Lobby.hpp"
#include "other/ComponentInfos.hpp"
#include <cstring>
#include "components/Timer.hpp"
#include "components/Damager.hpp"
#include <random>

namespace rtype {
    namespace systems {
        /*!
         * @class Monster System
         * @brief System to handle monster creation and movement
         */
        class MonsterSystem : public ecs::systems::System {
        public:
            MonsterSystem(const std::string &name, ecs::managers::EntityManager &entityManager, const int windowWidth = 427, const int windowHeight = 240);
            ~MonsterSystem() override = default;

            void onInit() override;
            void onUpdate(float elapsedTime) override;
            void onClose() override;

            /*!
             * create a monster entity with given parameters
             *
             * @param intervalPos offset position in x
             * @param posY position in Y
             * @param id EnemyId of the monster
             * @param velocityX velocity in x of the monster
             * @param velocityY velocity in y of the monster
             * @param speed speed of the monster
             */
            void createMonster(float intervalPos, float posY, const Enemy &id, float velocityX, float velocityY, float speed);

            /*!
             * create a wave of random monsters
             *
             * @param elapsedTimeAsSecond second elapsed since the beginning of the game
             */
            void createRandomMonster(const float &elapsedTimeAsSecond);

        private:
            ecs::managers::EntityManager &_entityManager; /*!< reference to the entity manager */
            unsigned long _nbEnemy; /*!< number of ennemies since the beginning of the game */
            int _windowWidth; /*!< width of the window */
            int _windowHeight; /*!< height of the window */
            std::random_device _rd; /*!< used to generate a random sequence */
            std::mt19937 _gen; /*!< used to generate a random sequence */
            std::uniform_int_distribution<> _dis; /*!< used to generate a random sequence */
            float _elapsedTimeAsSecondSinceBegin;
        };
    }
}

#endif // RTYPE_MONSTERSYSTEM_HPP
