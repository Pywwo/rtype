
/* Created by Romain FOUYER on 23/11/2019 at 11:54. */


#include "Timer.hpp"

rtype::components::Timer::Timer(ecs::entities::Entity &entity, float timeToLive)
: Component(entity), _timeToLive(timeToLive), _currentTime(0)
{}

float rtype::components::Timer::getTimeToLive() const
{
    return _timeToLive;
}

void rtype::components::Timer::setTimeToLive(float newTimeToLive)
{
    _timeToLive = newTimeToLive;
}

float rtype::components::Timer::getCurrentTime() const
{
    return _currentTime;
}

void rtype::components::Timer::setCurrentTime(float newCurrentTime)
{
    _currentTime = newCurrentTime;
}