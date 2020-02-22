
/* Created by Romain FOUYER on 29/11/2019 at 15:43. */


#ifndef RTYPE_SCORE_HPP
#define RTYPE_SCORE_HPP

#include "components/Component.hpp"

namespace rtype {
    namespace components {
        /*!
         * @class Score Component
         * @brief Component who handles the score
         */
        class Score : public ecs::components::Component{
        public:
            /*!
             * Create a new score component
             * @param entity parent entity
             */
            explicit Score(ecs::entities::Entity &entity);
            ~Score() override = default;

            /*!
             * Get the current score
             * @return the current score
             */
            [[nodiscard]] uint64_t getScore() const;

            /*!
             * Set the current score
             * @param newScore new current score
             */
            void setScore(uint64_t newScore);

        private:
            uint64_t _score; /*< Current score */
        };
    }
}


#endif //RTYPE_SCORE_HPP
