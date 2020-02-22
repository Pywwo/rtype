
/* Created by Romain FOUYER on 06/11/2019 at 14:01. */


#ifndef RTYPE_SPRITE_HPP
#define RTYPE_SPRITE_HPP

#include <SFML/Graphics.hpp>

#include "components/Component.hpp"
#include "types/Vector.hpp"

namespace rtype {
    namespace components {

        /*!
         * @enum SpriteState
         * @brief State of the sprite
         */
        enum SpriteState {
            SPRITE_IDLE,
            SPRITE_HOVER,
            SPRITE_CLICKED
        };

        /*!
         * @class Sprite
         * @brief Sprite component
         *
         * Create a new sprite
         */
        class Sprite : public ecs::components::Component {
        public:
            /*!
             * Create a new sprite
             *
             * @param entity parent entity
             * @param textureName name of the texture (path)
             * @param opacity opacity of the sprite [cf: OpacityChanger]
             */
            Sprite(ecs::entities::Entity &entity, const std::string &textureName, float opacity = 255);
            ~Sprite() override;

            /*!
             * Return the sprite
             *
             * @return sf::Sprite
             */
            sf::Sprite &getSprite();

            /*!
             * Set a new position to the sprite
             *
             * @param x new x position
             * @param y new y position
             */
            void setPosition(float x, float y);

            /*!
             * Get the current position of the sprite
             *
             * @return current position
             */
            rtype::commons::Vector2<float> getPosition() const;

            /*!
             * Set a new opacity to the sprite
             *
             * @param opacity new opacity
             */
            void setOpacity(float opacity);

            /*!
             * Get the opacity of the sprite
             *
             * @return opacity of the sprite
             */
            float getOpacity() const;
            /*!
             * Get the current state of the sprite
             *
             * @return current state of the sprite
             */
            SpriteState getState() const;

            /*!
             * Set a new state to the sprite
             *
             * @param newState new state
             */
            void setState(SpriteState newState);

            void setRepeated(bool repeated);
        private:
            sf::Texture *_texture; /*!< handle the texture of the sprite */
            sf::Sprite _sprite; /*!< handle the sprite in game */

            float _opacity; /*!< handle the opacity of text or sprite */

            SpriteState _state; /*!< handle the state of sprite */
        };
    }
}

#endif //RTYPE_SPRITE_HPP