
/* Created by Romain FOUYER on 05/11/2019 at 10:15. */


#ifndef RTYPE_ENTITY_HPP
#define RTYPE_ENTITY_HPP

#include "components/IComponent.hpp"
#include "IEntity.hpp"

#include <vector>

namespace ecs {

    namespace entities {
        /*!
         * @class Entity
         *
         * @brief Entity class
         *
         * Created on: 05/11/2019 at 10:49
         */
        class Entity : public IEntity {
        public:
            /*!
             * Constructor of the entity
             *
             * @param id id of the entity
             * @param name name of the entity
             */
            Entity(unsigned int id, const std::string &name);
            /*!
             * Destructor of the Entity
             *
             * @brief destruct an entity
             */
            ~Entity() override;

            void assignComponent(const std::string &componentName, components::IComponent *newComponent) override;


            void removeComponent(const std::string &componentName) override;

            [[nodiscard]] components::IComponent *getComponent(const std::string &componentName) override;

            [[nodiscard]] std::vector<components::IComponent *> getComponents(std::vector<std::string> componentsName) override;

            [[nodiscard]] bool hasComponent(const std::string &component) const override;
            [[nodiscard]] bool hasComponents(std::vector<std::string> components) const override;

            [[nodiscard]] const unsigned int &getId() const override;
            [[nodiscard]] const std::string &getName() const override;

            [[nodiscard]] const std::unordered_map<std::string, components::IComponent *> &getAllComponents() const override;

            void disable() override;
            void enable() override;

            [[nodiscard]] bool isEnabled() const override;
        protected:
            unsigned int _id;
            std::string _name;

            std::unordered_map<std::string, components::IComponent *> _components;

            bool _enable;
        };

    }

}

#else

namespace ecs {
    namespace entities {
        class Entity;
    }
}

#endif //RTYPE_ENTITY_HPP
