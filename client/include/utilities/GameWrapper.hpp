
/* Created by Romain FOUYER on 27/11/2019 at 15:18. */


#ifndef RTYPE_GAMEWRAPPER_HPP
#define RTYPE_GAMEWRAPPER_HPP

#include "systems/SystemManager.hpp"

namespace rtype {
    namespace utils {
        class GameWrapper {
        public:
            static GameWrapper &getInstance();

            [[nodiscard]] ecs::managers::SystemManager &getSystemManager();

            ~GameWrapper() = default;
        private:
            GameWrapper();

            ecs::managers::SystemManager systemManager;
        };
    }
}


#endif //RTYPE_GAMEWRAPPER_HPP
