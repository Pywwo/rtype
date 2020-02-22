
/* Created by Romain FOUYER on 04/11/2019 at 17:29. */

#include <iostream>

#include "SFMLSystem.hpp"
#include "SoundSystem.hpp"
#include "NetworkSystem.hpp"
#include "MovementSystem.hpp"
#include "AnimationSystem.hpp"
#include "systems/TimerSystem.hpp"
#include "LifeSystem.hpp"
#include "ScoreSystem.hpp"

#include "exception/RtypeException.hpp"

#include "utilities/GameSettings.hpp"

#include "utilities/GameWrapper.hpp"

int main([[maybe_unused]]int ac, [[maybe_unused]]char **av) {
    try {
        auto &gameSettings = rtype::utils::GameSettings::getInstance();
        auto &gameWrapper = rtype::utils::GameWrapper::getInstance();
        auto &systemManager = gameWrapper.getSystemManager();

        systemManager.newSystem("SFML System", new rtype::systems::SFMLSystem("R-TYPE", gameSettings.getWidth(), gameSettings.getHeight()));
        systemManager.newSystem("Sound System", new rtype::systems::SoundSystem("Sound System"));
        systemManager.newSystem("Network System", new rtype::systems::NetworkSystem("Network System"));
        systemManager.newSystem("Movement System", new rtype::systems::MovementSystem("Movement System"));
        systemManager.newSystem("Animation System", new rtype::systems::AnimationSystem("Animation System"));
        systemManager.newSystem("Timer System", new rtype::systems::TimerSystem("Timer System"));
        systemManager.newSystem("Life System", new rtype::systems::LifeSystem("Life System"));
        systemManager.newSystem("Score System", new rtype::systems::ScoreSystem("Score System"));
        systemManager.startSystem("SFML System");
        systemManager.startSystem("Sound System");
        systemManager.startSystem("Network System");
        systemManager.startSystem("Movement System");
        systemManager.startSystem("Animation System");
        systemManager.startSystem("Timer System");
        systemManager.startSystem("Life System");
        systemManager.startSystem("Score System");

        while (systemManager.getSystem("SFML System")->getState() == ecs::systems::STARTED)
            systemManager.runningTime();
        systemManager.stopSystem("Sound System");
        systemManager.stopSystem("Network System");
        systemManager.stopSystem("Movement System");
    } catch (rtype::ComponentException &e) {
        std::cerr << "[FATAL ERROR] " << std::string(e.what()) << std::endl;
    } catch (rtype::NetworkException &e) {
        std::cerr << "[FATAL ERROR] " << std::string(e.what()) << std::endl;
    } catch (...) {
        std::cerr << "Unknown Fatal Error" << std::endl;
    }
}