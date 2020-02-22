
/* Created by Romain FOUYER on 23/11/2019 at 11:54. */


#ifndef RTYPE_TIMER_HPP
#define RTYPE_TIMER_HPP

#include "components/Component.hpp"

namespace rtype {
    namespace components {
        /*!
         * @class Timer
         * @brief Timer component to handle the living time of an entity
         */
        class Timer : public ecs::components::Component {
        public:
            /*!
             * Create a new timer component
             *
             * @param entity parent entity
             * @param timeToLive time to live of the entity
             */
            Timer(ecs::entities::Entity &entity, float timeToLive);
            ~Timer() override = default;

            /*!
             * Get the time to live of the  entity
             *
             * @return time to live
             */
            [[nodiscard]] float getTimeToLive() const;

            /*!
             * Set a new time to live to the entity
             *
             * @param newTimeToLive new time to live
             */
            void setTimeToLive(float newTimeToLive);

            /*!
             * Get the current time of the component
             *
             * @return the current time
             */
            [[nodiscard]] float getCurrentTime() const;

            /*!
             * Set a new current time on the component
             *
             * @param newCurrentTime new current time
             */
            void setCurrentTime(float newCurrentTime);
        private:
            float _timeToLive; /*!< handle the time to live kill the entity after this time */
            float _currentTime; /*!< current time of the timer */
        };
    }
}

#endif //RTYPE_TIMER_HPP