
/* Created by Romain FOUYER on 06/11/2019 at 13:33. */


#ifndef RTYPE_WORLD_HPP
#define RTYPE_WORLD_HPP

#include <string>
#include <SFML/Graphics.hpp>

#include "entities/EntityManager.hpp"

namespace rtype {
    namespace worlds {

        /*!
         * @class Worlds
         *
         * @brief Class who handles World object
         */
        class World {
        public:
            /*!
             * @brief Create a new world
             * @param name name of the new world
             */
            explicit World(const std::string &name);
            virtual ~World() = default;

            /*!
             * @brief Get the entity manager of the world
             *
             * @return the entity manager
             */
            [[nodiscard]] ecs::managers::EntityManager &getEntityManager();

            /*!
             * @brief Get the world name
             * @return the world name
             */
            [[nodiscard]] const std::string &getWorldName() const;
        protected:
            std::string _worldName; /*!< handle the world name */
            ecs::managers::EntityManager _entityManager; /*!< handle entity manager */
        };
    }
}

#else

namespace rtype {
    namespace worlds {
        class World;
    }
}

#endif //RTYPE_WORLD_HPP
