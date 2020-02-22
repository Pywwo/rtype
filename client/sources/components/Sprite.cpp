
/* Created by Romain FOUYER on 06/11/2019 at 14:01. */


#include "exception/RtypeException.hpp"
#include "components/Sprite.hpp"

rtype::components::Sprite::Sprite(ecs::entities::Entity &entity, const std::string &textureName, float opacity)
: ecs::components::Component(entity), _texture(new sf::Texture), _opacity(opacity), _state(SPRITE_IDLE)
{
    if (!_texture->loadFromFile(textureName))
        throw rtype::ComponentException("Failed to load: " + textureName);

    _sprite.setTexture(*_texture); // Set the texture
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2); // Set origin to the center of the sprite
    _sprite.setColor(sf::Color(_sprite.getColor().r, _sprite.getColor().g, _sprite.getColor().b, _opacity));
}

rtype::components::Sprite::~Sprite()
{
    delete _texture;
}

sf::Sprite &rtype::components::Sprite::getSprite()
{
    return _sprite;
}

void rtype::components::Sprite::setPosition(float x, float y)
{
    _sprite.setPosition(x, y);
}

rtype::commons::Vector2<float> rtype::components::Sprite::getPosition() const
{
    return rtype::commons::Vector2<float>(_sprite.getPosition().x, _sprite.getPosition().y);
}

void rtype::components::Sprite::setOpacity(float opacity)
{
    _opacity = opacity;
    _sprite.setColor(sf::Color(_sprite.getColor().r, _sprite.getColor().g, _sprite.getColor().b, _opacity));
}

float rtype::components::Sprite::getOpacity() const
{
    return _opacity;
}

rtype::components::SpriteState rtype::components::Sprite::getState() const
{
    return _state;
}

void rtype::components::Sprite::setState(rtype::components::SpriteState newState)
{
    _state = newState;
}

void rtype::components::Sprite::setRepeated(bool repeated)
{
    _texture->setRepeated(repeated);
}