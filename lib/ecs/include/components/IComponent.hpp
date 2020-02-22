
/* Created by Romain FOUYER on 30/11/2019 at 09:42. */


#ifndef RTYPE_ICOMPONENT_HPP
#define RTYPE_ICOMPONENT_HPP

#include "entities/IEntity.hpp"

namespace ecs {
    namespace components {
        class IComponent {
        public:
            virtual ~IComponent() = default;

            /*!
             * get the parent entity of the component
             * @return the parent entity
             */
            virtual entities::IEntity &getEntity() = 0;
        };
    }
}

#else

namespace ecs {
    namespace components {
        class IComponent;
    }
}


#endif //RTYPE_ICOMPONENT_HPP
