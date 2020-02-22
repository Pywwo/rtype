
/* Created by Romain FOUYER on 23/11/2019 at 17:35. */


#include "Effect.hpp"
#include "utilities/AssetsManager.hpp"

rtype::components::Effect::Effect(ecs::entities::Entity &entity, rtype::components::Effect::EffectType type)
: Component(entity), _type(type)
{
}

const std::string &rtype::components::Effect::getAsset() const
{
    auto &assetManager = rtype::utils::AssetsManager::getInstance();
    switch (_type) {
        case FIRE_EXPLOSION:
            return assetManager["fire_explosion"];
        case LIGHTNING_EXPLOSION:
            return assetManager["lightning_explosion"];
    }
}

const rtype::components::Effect::EffectType &rtype::components::Effect::getType() const
{
    return _type;
}

void rtype::components::Effect::setType(rtype::components::Effect::EffectType newType)
{
    _type = newType;
}

int rtype::components::Effect::getAnimationNumber() const
{
    switch (_type) {
        case LIGHTNING_EXPLOSION:
            return 7;
        case FIRE_EXPLOSION:
            return 5;
    }
}

const std::string &rtype::components::Effect::getSoundEffect() const
{
    auto &assetManager = rtype::utils::AssetsManager::getInstance();

    switch (_type) {
        case LIGHTNING_EXPLOSION:
            return assetManager["lightning_explosion_sound"];
        case FIRE_EXPLOSION:
            return assetManager["fire_explosion_sound"];
    }
}
