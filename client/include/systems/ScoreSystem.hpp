
/* Created by Romain FOUYER on 29/11/2019 at 15:41. */


#ifndef RTYPE_SCORESYSTEM_HPP
#define RTYPE_SCORESYSTEM_HPP

#include "systems/System.hpp"

namespace rtype {
    namespace systems {
        /*!
         * @class score Sytem
         * @brief Class for handle the score of the game
         */
        class ScoreSystem : public ecs::systems::System {
        public:
            ScoreSystem(const std::string &name);
            ~ScoreSystem() override = default;

            void onInit() override;
            void onUpdate(float elapsedTime) override;
            void onClose() override;

        };
    }
}


#endif //RTYPE_SCORESYSTEM_HPP
