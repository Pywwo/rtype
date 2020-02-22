
/* Created by Romain FOUYER on 23/11/2019 at 11:59. */


#ifndef RTYPE_TIMERSYSTEM_HPP
#define RTYPE_TIMERSYSTEM_HPP

#include "systems/System.hpp"

namespace rtype {
    namespace systems {
        /*!
         * @class Timer System
         * @brief Timer system to handle the timer of the entity
         */
        class TimerSystem : public ecs::systems::System {
        public:
            TimerSystem(const std::string &name);

            void onInit() override;
            void onUpdate(float elapsedTime) override;
            void onClose() override;
        };
    }
}


#endif //RTYPE_TIMERSYSTEM_HPP
