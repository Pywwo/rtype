
/* Created by Romain FOUYER on 05/11/2019 at 10:33. */


#ifndef RTYPE_SYSTEM_HPP
#define RTYPE_SYSTEM_HPP

#include <string>

#include "ISystem.hpp"

namespace ecs {

    namespace systems {

        /*!
         * @class System
         *
         * @brief System class
         *
         * Created on 05/11/2019 at 10:33
         */
        class System : public ISystem {
        public:
            /*!
             * Constructor of the system
             *
             * @param name name of the system
             */
            explicit System(const std::string &name);

            /*!
             * Destructor of the system
             *
             * @brief destruct a system
             */
            ~System() override = default;

            void onInit() override {};
            void onUpdate([[maybe_unused]] float elapsedTime) override {};
            void onClose() override {};

            /*!
             * Get name of the system
             *
             * @return the name of the system
             */
            [[nodiscard]] const std::string &getName() const override;
            /*!
             * Get the state of a system
             *
             * 
             * @return a SystemState, the state of the system
             */
            [[nodiscard]] SystemState getState() const override;
            /*!
             * set the state of the system
             *
             * @param newState the updating state
             */
            void setState(SystemState newState) override;

        protected:
            std::string _name;
            SystemState _state;
        };
    }
}

#else

namespace ecs {
    namespace systems {
        class System;
    }
}

#endif //RTYPE_SYSTEM_HPP
