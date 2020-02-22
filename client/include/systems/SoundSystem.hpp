
/* Created by Romain FOUYER on 19/11/2019 at 15:38. */


#ifndef RTYPE_SOUNDSYSTEM_HPP
#define RTYPE_SOUNDSYSTEM_HPP

#include "systems/System.hpp"

namespace rtype {
    namespace systems {
        /*!
         * @class SoundSystem
         * @brief System who handles all sounds logic
         */
        class SoundSystem : public ecs::systems::System {
        public:
            explicit SoundSystem(const std::string &name);

            void onInit() override;
            void onUpdate(float elapsedTime) override;
            void onClose() override;

            /*!
             * Get the current volume effect
             *
             * @return current effect volume
             */
            [[nodiscard]] float getEffectVolume() const;

            /*!
             * Set a new effect volume
             *
             * @param effectVolume new effect volume
             */
            void setEffectVolume(float effectVolume);

            /*!
             * Get the current music volume
             *
             * @return the current music volume
             */
            [[nodiscard]] float getMusicVolume() const;

            /*!
             * Set a new music volume
             *
             * @param musicVolume new music volume
             */
            void setMusicVolume(float musicVolume);

        private:
            float _effectVolume;
            float _musicVolume;

            std::string _currentWorld; /* Used to stop all sounds on world changing */
        };
    }
}


#endif //RTYPE_SOUNDSYSTEM_HPP
