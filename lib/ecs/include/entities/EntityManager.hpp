
/* Created by Romain FOUYER on 05/11/2019 at 10:49. */


#ifndef RTYPE_ENTITYMANAGER_HPP
#define RTYPE_ENTITYMANAGER_HPP

#include "Entity.hpp"
#include <vector>
#include <map>
#include <functional>

namespace ecs {

    namespace managers {
        /*!
         * @class EntityManager
         *
         * @brief Entity Manager class
         *
         * Created on: 05/11/2019 at 10:49
         */
        class EntityManager {
        public:
            /*!
             * Constructor of the entity manager
             *
             * @brief create an entity manager
             */
            EntityManager();
            /*!
             * Destructor of the entity manager
             *
             * @brief destruct an entity manager
             */
            ~EntityManager();

            /*!
             * @brief Create a new entity
             * @param name name of the new entity
             */
            void createEntity(const std::string &name);

            /*!
             * @brief Delete an entity
             * @param name name of the entity to be deleted
             */
            void deleteEntity(const std::string &name);
            /*!
             * @brief Apply a function to all entities who have components in parameters
             * @param components components searched
             * @param func callback function
             */
            void applyToEach(std::vector<std::string> components, typename std::common_type<std::function<void(entities::Entity *)>>::type func);

            /*!
             * @brief Fetch an entity by his id
             * @param id id of the entity
             * @return an entity
             */
            entities::Entity *getEntityById(int id);
            /*!
             * @brief Fetch an entity by his name
             * @param name name of the entity
             * @return an entity
             */
            entities::Entity *getEntityByName(const std::string &name);
            /*!
             * @brief Fetch all entities with this name
             * @param name name of the entities
             * @return a list of entities
             */
            std::vector<entities::Entity *> getEntitiesByName(const std::string &name);

            /*!
             * Get all entities with specified components
             * @param components components inside the entity
             * @return entity with all specified components
             */
            std::vector<entities::Entity *> getEntitiesWithComponents(std::vector<std::string> components);

            /*!
             * Delete all entities
             */
            void deleteAllEntities();
        private:
            int _maxId; /*< Entities Max Id*/
            std::map<int, entities::Entity *> _entities; /*< All entities inside Entity Manager */
        };
    }
}


#endif //RTYPE_ENTITYMANAGER_HPP
