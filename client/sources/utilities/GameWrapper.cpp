
/* Created by Romain FOUYER on 27/11/2019 at 15:18. */


#include "utilities/GameWrapper.hpp"

rtype::utils::GameWrapper::GameWrapper()
: systemManager()
{
}

rtype::utils::GameWrapper &rtype::utils::GameWrapper::getInstance()
{
    static rtype::utils::GameWrapper gw;

    return gw;
}

ecs::managers::SystemManager &rtype::utils::GameWrapper::getSystemManager()
{
    return systemManager;
}