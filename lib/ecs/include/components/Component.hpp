
/* Created by Romain FOUYER on 05/11/2019 at 10:14. */


#ifndef RTYPE_COMPONENT_HPP
#define RTYPE_COMPONENT_HPP

#include "entities/Entity.hpp"

namespace ecs {

    namespace components {
        /*!
         * @class Component
         *
         * @brief Component class
         *
         * Created on: 05/11/2019 at 10:14
         */
        class Component : public IComponent {
        public:
            /*!
             * construct a new component with his parent entity
             *
             * @param entity parent entity
             */
            explicit Component(entities::Entity &entity);
            /*!
             * destruct a component
             */
            ~Component() override = default;

            entities::IEntity &getEntity() override;
        private:
            entities::IEntity &_entity;
        };

    }
}

#else

namespace ecs {
    namespace components {
        class Component;
    }
}

#endif //RTYPE_COMPONENT_HPP
