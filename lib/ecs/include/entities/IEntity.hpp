
/* Created by Romain FOUYER on 30/11/2019 at 09:44. */


#ifndef RTYPE_IENTITY_HPP
#define RTYPE_IENTITY_HPP

#include "components/IComponent.hpp"

#include <string>
#include <vector>
#include <unordered_map>

namespace ecs {
    namespace entities {
        class IEntity {
        public:
            virtual ~IEntity() = default;

            /*!
             * Assign a component to the entity
             *
             * @param componentName name of the component
             * @param newComponent pointer of the component
             */
            virtual void assignComponent(const std::string &componentName, components::IComponent *newComponent) = 0;
            /*!
             * Remove a component from the entity
             *
             * @param componentName name of the component
             */
            virtual void removeComponent(const std::string &componentName) = 0;

            /*!
             * Get a component inside an entity
             *
             * @param componentName name of the component
             * @return the component
             */
            [[nodiscard]] virtual components::IComponent *getComponent(const std::string &componentName) = 0;
            /*!
             * Get all components wanted in the parameter inside the Entity
             *
             * @param componentsName list of components name
             * @return list of components
             */
            [[nodiscard]] virtual std::vector<components::IComponent *> getComponents(std::vector<std::string> componentsName) = 0;
            /*!
             * Fetch all the components inside the entity
             *
             * @return all components
             */
            [[nodiscard]] virtual const std::unordered_map<std::string, components::IComponent *> &getAllComponents() const = 0;

            /*!
             * Know if an entity has a specific component
             *
             * @param component name of the component
             * @return true if the component exists, false if not
             */
            [[nodiscard]] virtual bool hasComponent(const std::string &componentName) const = 0;
            /*!
             * Know if an entity has several components
             *
             * @param components list with the name of the components
             * @return true if the components exist, false if not
             */
            [[nodiscard]] virtual bool hasComponents(std::vector<std::string> components) const = 0;
            /*!
             * Get the id of the entity
             *
             * @return the entity id
             */
            [[nodiscard]] virtual const unsigned int &getId() const = 0;
            /*!
             * Get the name of the entity
             *
             * @return the entity name
             */
            [[nodiscard]] virtual const std::string &getName() const = 0;
            /*!
             * Check if an entity is enabled
             * @return true if enabled false if disabled
             */
            [[nodiscard]] virtual bool isEnabled() const = 0;
            /*!
             * Enable an entity, an entity is enabled by default
             */
            virtual void enable() = 0;
            /*!
             * Disable the entity, it is not returned by the applyToEach anymore
             */
            virtual void disable() = 0;
        };
    }
}

#else

namespace ecs {
    namespace entities {
        class IEntity;
    }
}

#endif //RTYPE_IENTITY_HPP
