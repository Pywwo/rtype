
/* Created by Romain FOUYER on 27/11/2019 at 14:06. */


#ifndef RTYPE_SETTINGSWORLD_HPP
#define RTYPE_SETTINGSWORLD_HPP

#include "World.hpp"

namespace rtype {
    namespace worlds {
        /*!
         * @class Settings world
         * @brief Class for the settings world for handle the settings
         */
        class SettingsWorld : public World {
        public:
            explicit SettingsWorld(const std::string &name);
            ~SettingsWorld() override = default;

        private:
            /*!
             * @brief function for setup the background of the settings world
             */
            void setupBackground();
            /*!
             * @brief function for setup the back button of the settings world
             */
            void setupBackButton();
            /*!
             * @brief function for setup the music volume changer of the settings world
             */
            void setupMusicVolumeChanger();
            /*!
             * @brief function for setup the effect volume changer of the settings world
             */
            void setupEffectVolumeChanger();
            /*!
             * @brief function for update the string of the settings world
             */
            void updateString();
        };
    }
}


#endif //RTYPE_SETTINGSWORLD_HPP
