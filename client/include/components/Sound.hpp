
/* Created by Romain FOUYER on 19/11/2019 at 12:22. */


#ifndef RTYPE_SOUND_HPP
#define RTYPE_SOUND_HPP

#include "components/Component.hpp"

#include <SFML/Audio.hpp>

namespace rtype {
    namespace components {

        /*!
         * @enum SoundState
         * @brief State of the sound (Playing and Stopped)
         */
        enum SoundState {
            PLAYING,
            STOPPED
        };

        /*!
         * @enum SoundType
         * @brief useful for the sound system to set the volume based on user settings
         */
        enum SoundType {
            EFFECT,
            MUSIC
        };

        /*!
         * @class Sound
         * @brief Basic sound component
         */
        class Sound : public ecs::components::Component {
        public:
            /*!
             * Constructor for sound component
             *
             * @param entity parent entity
             * @param path path of the sound
             * @param type MUSIC if music, EFFECT if sound effect
             */
            Sound(ecs::entities::Entity &entity, const std::string &path, SoundType type);
            ~Sound() override;

            /*!
             * Start a sound if it's stop
             */
            void play();

            /*!
             * Stop a sound if it's started
             */
            void stop();

            /*!
             * Pause a sound
             */
            void pause();

            /*!
             * Restart a sound
             */
            void restart();

            /*!
             * Set volume to the sound
             *
             * @param volume new voluume
             */
            void setVolume(float volume);

            /*!
             * Getter for the type of the sound
             *
             * @return type of the sound
             */
            [[nodiscard]] SoundType getType() const;
        private:
            SoundState _state; /*!< handle the state of the sound */
            SoundType _type; /*!< handdle the type of the sound Effect or Music */

            sf::Music _music; /*!< handle the music to play in rtype game */
        };
    }
}

#endif //RTYPE_SOUND_HPP