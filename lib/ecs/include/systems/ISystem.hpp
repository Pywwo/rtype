
/* Created by Romain FOUYER on 30/11/2019 at 10:30. */


#ifndef RTYPE_ISYSTEM_HPP
#define RTYPE_ISYSTEM_HPP

namespace ecs {
    namespace systems {
        /*!
         * @enum SystemState
         *
         * @brief enum to know the current state of the system
        */
        enum SystemState
        {
            STARTED,
            STOPPED
        };
        class ISystem {
        public:
            virtual ~ISystem() = default;

            /*!
             * Initialization function of a system
             */
            virtual void onInit() = 0;
            /*!
             * Update entities and components of the system
             *
             * @param elapsedTime elapsed time
             */
            virtual void onUpdate(float elapsedTime) = 0;
            /*!
             * System function to do things when closed
             */
            virtual void onClose() = 0;
            /*!
             * Get name of the system
             *
             * @return the name of the system
             */
            [[nodiscard]] virtual const std::string &getName() const = 0;
            /*!
             * Get the state of a system
             *
             *
             * @return a SystemState, the state of the system
             */
            [[nodiscard]] virtual SystemState getState() const = 0;
            /*!
             * set the state of the system
             *
             * @param newState the updating state
             */
            virtual void setState(SystemState newState) = 0;
        };
    }
}

#endif //RTYPE_ISYSTEM_HPP
