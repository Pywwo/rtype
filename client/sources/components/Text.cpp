
/* Created by Romain FOUYER on 21/11/2019 at 10:51. */


#include "Text.hpp"

#include "utilities/AssetsManager.hpp"

#include "RtypeException.hpp"

rtype::components::Text::Text(ecs::entities::Entity &entity)
: Component(entity), _text(), _font(new sf::Font), _opacity(255)
{
    auto &assetManager = rtype::utils::AssetsManager::getInstance();

    if (!_font->loadFromFile(assetManager["default_font"]))
        throw rtype::ComponentException("Failed to load the font: " + assetManager["default_font"]);

    sf::FloatRect textRect = _text.getLocalBounds();
    _text.setFont(*_font);
    _text.setCharacterSize(42);
    _text.setFillColor(sf::Color::Black);
    _text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
}


rtype::components::Text::Text(ecs::entities::Entity &entity, unsigned int characterSize)
: Component(entity), _text(), _font(new sf::Font), _opacity(255)
{
    auto &assetManager = rtype::utils::AssetsManager::getInstance();

    if (!_font->loadFromFile(assetManager["default_font"]))
        throw rtype::ComponentException("Failed to load the font: " + assetManager["default_font"]);
    _text.setFont(*_font);
    _text.setCharacterSize(characterSize);
    _text.setFillColor(sf::Color::Black);
}

rtype::components::Text::Text(ecs::entities::Entity &entity, unsigned int characterSize, const std::string &fontPath)
: Component(entity), _text(), _font(new sf::Font), _opacity(255)
{
    if (!_font->loadFromFile(fontPath))
        throw rtype::ComponentException("Failed to load the font: " + fontPath);
    _text.setFont(*_font);
    _text.setCharacterSize(characterSize);
    _text.setFillColor(sf::Color::Black);
}

rtype::components::Text::~Text()
{
    delete _font;
}

void rtype::components::Text::setString(const std::string &newString)
{
    _text.setString(newString);
}

std::string rtype::components::Text::getString() const
{
    return _text.getString();
}

const sf::Color& rtype::components::Text::getColor() const
{
    return _text.getFillColor();
}

void rtype::components::Text::setColor(sf::Color newColor)
{
    _text.setFillColor(newColor);
}

void rtype::components::Text::setPosition(float x, float y)
{
    _text.setPosition(x, y);
}

const sf::Text &rtype::components::Text::getText() const
{
    return _text;
}

void rtype::components::Text::setOpacity(float opacity)
{
    _opacity = opacity;
    _text.setFillColor(sf::Color(_text.getFillColor().r, _text.getFillColor().g, _text.getFillColor().b, _opacity));
}

float rtype::components::Text::getOpacity() const
{
    return _opacity;
}