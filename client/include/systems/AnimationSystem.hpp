
/* Created by Romain FOUYER on 21/11/2019 at 17:46. */


#ifndef RTYPE_ANIMATIONSYSTEM_HPP
#define RTYPE_ANIMATIONSYSTEM_HPP

#include "systems/System.hpp"

namespace rtype {
    namespace systems {
        /*!
         * @class Animation System
         * @brief System who handles animation like parallax, or entity with Animator
         */
        class AnimationSystem : public ecs::systems::System {
        public:
            explicit AnimationSystem(const std::string &name);
            ~AnimationSystem() override = default;

            void onInit() override;
            void onUpdate(float elapsedTime) override;
            void onClose() override;
        private:
        };
    }
}


#endif //RTYPE_ANIMATIONSYSTEM_HPP
