
/* Created by Romain FOUYER on 25/11/2019 at 10:25. */


#ifndef RTYPE_STATUS_HPP
#define RTYPE_STATUS_HPP

#include "components/Component.hpp"

namespace rtype {
    namespace components {
        /*!
         * @class Status component
         * @brief status of components
         */
        class Status : public ecs::components::Component {
        public:
            Status(ecs::entities::Entity &entity);
            ~Status() override = default;

            /*!
             * Method to know if an entity is alive
             * @return true if alive, false if dead
             */
            [[nodiscard]] bool isAlive() const;
            /*!
             * Method to set an entity alive or dead
             * @param alive true if alive, false if dead
             */
            void setAlive(bool alive);
        private:
            bool _isAlive; /*!< true if is alive false otherwise */
        };
    }
}


#endif //RTYPE_STATUS_HPP
