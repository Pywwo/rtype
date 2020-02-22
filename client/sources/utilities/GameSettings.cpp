
/* Created by Romain FOUYER on 19/11/2019 at 16:07. */


#include "utilities/GameSettings.hpp"

rtype::utils::GameSettings::GameSettings()
: _width(1280), _height(720)
{
}

rtype::utils::GameSettings &rtype::utils::GameSettings::getInstance()
{
    static rtype::utils::GameSettings gs;

    return gs;
}

float rtype::utils::GameSettings::getWidth() const
{
    return _width;
}

float rtype::utils::GameSettings::getHeight() const
{
    return _height;
}