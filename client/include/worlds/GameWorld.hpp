
/* Created by Romain FOUYER on 06/11/2019 at 13:38. */


#ifndef RTYPE_GAMEWORLD_HPP
#define RTYPE_GAMEWORLD_HPP

#include "World.hpp"

#include "components/Effect.hpp"
#include "types/Vector.hpp"
#include "ComponentInfos.hpp"

namespace rtype {

    namespace worlds {

        /*!
         * @class GameWorld
         * @brief In game world
         */
        class GameWorld : public World {
        public:
            /*!
             * Construct a new Game World
             * @param name name of the world
             */
            explicit GameWorld(const std::string &name);
            ~GameWorld() override;

            /*!
             * Init a new game
             */
            void initGame();

            /*!
             * End a game
             */
            void endGame();
            /*!
             * Initialize a game's entity
             * @param componentInfos component info of an entity
             */
            void initEntity(rtype::ComponentInfos &componentInfos);

            /*!
             * Method to initialize the event inside the game world
             * eg:
             *      -> UP KEY - Send Packet
             */
            void initEvents();

            /*!
             * Add an effect to the world
             *
             * @param type type of the effect (LIGHTNING_EXPLOSION for example)
             * @param position position of the effect
             */
            void addEffect(rtype::components::Effect::EffectType type, rtype::commons::Vector2<float> position);

            /*!
             * Create a shoot entity
             *
             * @param name name of the entity
             */
            void shooting(const std::string &name);
        };

    }

}


#endif //RTYPE_GAMEWORLD_HPP
