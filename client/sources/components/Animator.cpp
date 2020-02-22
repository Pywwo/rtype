
/* Created by Romain FOUYER on 21/11/2019 at 17:22. */

#include "Animator.hpp"

#include "exception/RtypeException.hpp"

rtype::components::Animator::Animator(ecs::entities::Entity &entity)
: Component(entity), deltaTime(0), _currentAnimation(""), _animations(), _currentAnimationIndex(0)
{
}

bool rtype::components::Animator::animationExist(const std::string &name) const
{
    return _animations.find(name) != _animations.end();
}

void rtype::components::Animator::addAnimation(const std::string &name, const rtype::components::Animator::Animation &animation)
{
    _animations.insert(std::make_pair(name, animation));
}

void rtype::components::Animator::setCurrentAnimation(const std::string &name)
{
    _currentAnimation = name;
    _currentAnimationIndex = _animations.at(_currentAnimation)._startIndex;
    deltaTime = 0;
}

const rtype::components::Animator::Animation &rtype::components::Animator::getCurrentAnimation() const
{
    if (!animationExist(_currentAnimation))
        throw rtype::ComponentException("Animation: " + _currentAnimation + " doesn't exist.");
    return _animations.at(_currentAnimation);
}

int rtype::components::Animator::getCurrentAnimationIndex() const
{
    return _currentAnimationIndex;
}

void rtype::components::Animator::setCurrentAnimationIndex(int newIndex)
{
    _currentAnimationIndex = newIndex;
}

const std::string &rtype::components::Animator::getCurrentAnimationName() const
{
    return _currentAnimation;
}