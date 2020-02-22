
/* Created by Romain FOUYER on 05/11/2019 at 10:41. */


#ifndef RTYPE_SYSTEMMANAGER_HPP
#define RTYPE_SYSTEMMANAGER_HPP

#include "System.hpp"

#include <unordered_map>
#include <chrono>

namespace ecs {

    namespace managers {
        /*!
         * @class SystemManager
         *
         * @brief System Manager class
         *
         * Created on: 05/11/2019 at 10:49
         */
        class SystemManager {
        public:
            SystemManager();
            /*!
             * Destructor of the system manager
             *
             * @brief destruct an system manager
             */
            ~SystemManager();

            /*!
             * @brief Get a system by his name
             * @param systemName the name of the system you want to get
             * @return a System
             */
            systems::System *getSystem(const std::string &systemName);
            /*!
             * @brief add a new system in te system manager
             * @param systemName the name of the system you want to set in the system manager
             * @param newSystem a pointer to the system you want to set in the system manager
             */
            void newSystem(const std::string &systemName, systems::System *newSystem);

            /*!
             * @brief start a system by his name
             * @param systemName the name of the system you want to start
             */
            void startSystem(const std::string &systemName);
            /*!
             * @brief stop a system by his name
             * @param systemName the name of the system you want to stop
             */
            void stopSystem(const std::string &systemName);

            /*!
             * @brief get the time elapsed and send it to the update function of all systems
             */
            void runningTime();

            /*!
             * @brief return the time scale of the system manager
             * @return the time scale
             */
            [[nodiscard]] float getTimeScale() const;
            /*!
             * @brief set the time scale of the system manager
             * @param newTimeScale the timeScale you want to set to the system manager
             */
            void setTimeScale(float newTimeScale);
            /*!
             * @brief function for get the current elapsed Time
             * @return the elapsedTime in float
             */
            [[nodiscard]] float getElapsedTime() const;
        private:
            std::unordered_map<std::string, systems::System *> _systems; /*!< map for handle all systems */
            float _timeScale; /*!< current time scale of the systemManager */
            std::chrono::steady_clock::time_point _last; /*!< last chrono time point */
            float _elapsedTime; /*!< current elapsedTime of the systemManager */
        };

    }

}


#endif //RTYPE_SYSTEMMANAGER_HPP
