
/* Created by Romain FOUYER on 25/11/2019 at 10:30. */


#ifndef RTYPE_LIFESYSTEM_HPP
#define RTYPE_LIFESYSTEM_HPP

#include "systems/System.hpp"

namespace rtype {
    namespace systems {
        /*!
         * @class Life System
         * @brief System to handle life of player
         */
        class LifeSystem : public ecs::systems::System {
        public:
            explicit LifeSystem(const std::string &name);
            ~LifeSystem() override = default;

            void onInit() override;
            void onUpdate(float elapsedTime) override;
            void onClose() override;
        private:
        };
    }
}


#endif //RTYPE_LIFESYSTEM_HPP
