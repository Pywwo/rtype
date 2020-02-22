
/* Created by Romain FOUYER on 20/11/2019 at 23:18. */


#ifndef RTYPE_MOVEMENTSYSTEM_HPP
#define RTYPE_MOVEMENTSYSTEM_HPP

#include "systems/System.hpp"

namespace rtype {
    namespace systems {
        /*!
         * @class MovementSystem
         * @brief System to handle the movement of the Controller
         */
        class MovementSystem : public ecs::systems::System {
        public:
            /*!
             * Create a new movement system
             *
             * @param name name of the system
             */
            explicit MovementSystem(const std::string &name);
            ~MovementSystem() override = default;

            void onInit() override;
            void onUpdate(float elapsedTime) override;
            void onClose() override;
        };
    }
}


#endif //RTYPE_MOVEMENTSYSTEM_HPP
