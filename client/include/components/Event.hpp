
/* Created by Romain FOUYER on 24/11/2019 at 15:33. */


#ifndef RTYPE_EVENT_HPP
#define RTYPE_EVENT_HPP

#include "components/Component.hpp"

#include <functional>
#include <map>

namespace rtype {
    namespace components {
        /*!
         * @class Event
         * @brief Event class
         */
        class Event : public ecs::components::Component {
        public:
            explicit Event(ecs::entities::Entity &entity);
            ~Event() override = default;

            /*!
             * Add an event to the entity
             *
             * @param name name of the event
             * @param callback callback of the event
             */
            void addEvent(const std::string &name, std::function<void(void)> callback);

            /*!
             * Get a specific callback
             *
             * @param name name of the event wanted
             * @return a callback
             */
            std::function<void(void)> getSpecificCallback(const std::string &name);
        private:
            std::map<std::string, std::function<void(void)>> _callbacks;
        };
    }
}

#endif //RTYPE_EVENT_HPP
