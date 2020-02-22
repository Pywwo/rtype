
/* Created by Romain FOUYER on 29/11/2019 at 15:43. */


#include "Score.hpp"

rtype::components::Score::Score(ecs::entities::Entity &entity)
: Component(entity), _score(0)
{}

uint64_t rtype::components::Score::getScore() const
{
    return _score;
}

void rtype::components::Score::setScore(uint64_t newScore)
{
    _score = newScore;
}