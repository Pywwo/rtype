
/* Created by Romain FOUYER on 11/11/2019 at 14:36. */


#ifndef RTYPE_ENTITYLOADER_HPP
#define RTYPE_ENTITYLOADER_HPP

#include "worlds/World.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

namespace rtype {

    namespace utils {
        /*!
         * @enum ComponentsHandled
         *
         * @brief Enum with all the components type to identify Components
         */
        enum ComponentsHandled {
            SPRITE
        };

        /*!
         * @class Entity Loader
         * @brief Entity Loader class, who parses JSON file to entity with components
         * Created on 11/11/2019 at 14:36
         */
        class EntityLoader {
        public:
            /*!
             * Map of ComponentHandled Enum to identification, name of the component as a string, and a vector of
             * wanted arguments
             */
            typedef std::vector<std::tuple<ComponentsHandled, std::string, std::vector<std::string>>> EntitiesArguments;
            static EntitiesArguments entitiesArguments;

            /*!
             * Destructor of the entity
             *
             * @brief destruct the entity loader
             */
            ~EntityLoader() = default;

            /*!
             * Get an instance of the Entity Loader
             *
             * @return an instance of the entity loader
             */
            static EntityLoader &getInstance();

            /*!
             * Load an entity from a json string to the world
             *
             * @param world world where the entity will be loaded
             * @param jsonData json string with information about the entity
             */
            void loadEntityToWorld(rtype::worlds::World &world, const std::string &jsonData);

            EntityLoader(const EntityLoader &) = delete;
            EntityLoader &operator=(const EntityLoader &) = delete;
        private:
            /*!
             * Fetch all arguments about the following component
             *
             * @param componentName name of the component
             * @param arguments json object with all arguments
             * @return map with name of the arguments and his value
             */
            std::map<std::string, std::string> getArguments(const std::string &componentName, boost::property_tree::ptree &arguments) const;

            /*!
             * Add the component to the entity with all his arguments setted
             *
             * @param entity entity where the component will be added
             * @param componentName name of the component
             * @param arguments arguments of the component
             */
            void addComponent(ecs::entities::Entity *entity, const std::string &componentName, std::map<std::string, std::string> arguments);

            EntityLoader() = default;
        };

    }
}

#else

namespace rtype {
    namespace commons {
        class EntityLoader;
    }
}

#endif //RTYPE_ENTITYLOADER_HPP
