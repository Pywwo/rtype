
/* Created by Romain FOUYER on 06/11/2019 at 13:41. */


#ifndef RTYPE_WORLDMANAGER_HPP
#define RTYPE_WORLDMANAGER_HPP

#include <map>

#include "World.hpp"

namespace rtype {
    namespace worlds {
        /*!
         * @class WorldManager
         *
         * @brief Class to handle Worlds(scenes) on the game
         */
        class WorldManager {
        public:
            /*!
             * @brief Get instance
             *
             * @return the instance of the world manager
             */
            static WorldManager &getInstance();

            /*!
             * @brief Delete all worlds inside the World Manager
             */
            ~WorldManager();

            /*!
             * @brief Change current world
             * @param worldName next current world
             */
            void changeWorld(const std::string &worldName);

            /*!
             * @brief Add a new world
             * @param world world to be add
             */
            void addWorld(World *world);

            /*!
             * @brief Get the current world
             * @return the current world
             */
            [[nodiscard]] World *getCurrentWorld();

            /*!
             * @brief get world by a name
             * @param worldName name of the world you want
             * @return the world get
             */
            [[nodiscard]] World *getWorldByName(const std::string &worldName);
            # if UNIX
            WorldManager(const WorldManager &other) = delete;
            WorldManager(WorldManager &other) = delete;
            # endif
        private:
            WorldManager() = default;
        private:
            std::map<std::string, World *> _worlds; /*!< map for handle all world */
            std::string currentWorldName; /*!< handle current world */
        };
    }
}

#endif //RTYPE_WORLDMANAGER_HPP