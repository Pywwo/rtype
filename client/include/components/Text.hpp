
/* Created by Romain FOUYER on 21/11/2019 at 10:51. */


#ifndef RTYPE_TEXT_HPP
#define RTYPE_TEXT_HPP

#include "components/Component.hpp"

#include <SFML/Graphics.hpp>

namespace rtype {
    namespace components {
        /*!
         * @class Text Component
         * @brief Component for drawing text
         */
        class Text : public ecs::components::Component {
        public:
            /*!
             * Constructor for a basic text
             *
             * @param entity parent entity
             */
            explicit Text(ecs::entities::Entity &entity);

            /*!
             * Constructor for a basic text, based on character size
             *
             * @param entity parent entity
             * @param characterSize current character size
             */
            Text(ecs::entities::Entity &entity, unsigned int characterSize);

            /*!
             * Constructor for a basic text, based on character size and on a custom font
             *
             * @param entity parent entity
             * @param characterSize size of the string
             * @param fontPath path of the font
             */
            Text(ecs::entities::Entity &entity, unsigned int characterSize, const std::string &fontPath);

            ~Text() override;

            /*!
             * Set new string inside the sf::Text
             *
             * @param newString the new string
             */
            void setString(const std::string &newString);

            /*!
             * Get the current string inside the sf::Text
             *
             * @return the string inside the sf::Text
             */
            [[nodiscard]] std::string getString() const;

            /*!
             * Set a new color to the sf::Text
             *
             * @param newColor new color
             */
            void setColor(sf::Color newColor);

            /*!
             * Get the color of the text
             *
             * @return the color of the text
             */
            const sf::Color &getColor() const;

            /*!
             * Get the text who will be rendered
             *
             * @return the rendered text
             */
            [[nodiscard]] const sf::Text &getText() const;

            /*!
             * Set a new position to the input component
             *
             * @param x new x position
             * @param y new y position
             */
            void setPosition(float x, float y);

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
        private:
            sf::Text _text; /*!< handle the text for display */
            sf::Font *_font; /*!< handle the font for text */

            float _opacity; /*!< handle the opacity for text */
        };
    }
}


#endif //RTYPE_TEXT_HPP
