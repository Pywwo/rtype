
/* Created by Romain FOUYER on 21/11/2019 at 17:22. */


#ifndef RTYPE_ANIMATOR_HPP
#define RTYPE_ANIMATOR_HPP

#include <map>

#include "components/Component.hpp"

namespace rtype {
    namespace components {
        /*!
         * @class Animator Component
         * @brief Class for the component Animator who handles animations with spritesheets
         */
        class Animator : public ecs::components::Component {
        public:
            /*!
             * @struct Animation
             * @brief Struct for a simple animation
             */
            struct Animation {
                Animation(int startIndex, int endIndex, bool isLooping = false, float speed = 1)
                : _startIndex(startIndex), _endIndex(endIndex), _isLooping(isLooping), _speed(speed) {};

                int _startIndex;
                int _endIndex;
                bool _isLooping;
                float _speed;
            };

            /*!
             * Constructor for the Animator component
             *
             * @param entity parent entity
             */
            explicit Animator(ecs::entities::Entity &entity);
            ~Animator() override = default;

            /*!
             * Verify if an animation exists
             *
             * @param name name of the animation
             * @return true if exist, false if not
             */
            [[nodiscard]] bool animationExist(const std::string &name) const;

            /*!
             * Add a new animation to the entity
             *
             * @param name name of the animation
             * @param animation animation structure
             */
            void addAnimation(const std::string &name, const Animation &animation);

            /*!
             * Set the current animation of the entity
             *
             * @param name name of the chosen animation
             */
            void setCurrentAnimation(const std::string &name);

            /*!
             * Get the current animation data
             *
             * @return current animation data
             */
            [[nodiscard]] const Animation &getCurrentAnimation() const;

            /*!
             * Get the current animation name
             *
             * @return current animation name
             */
            [[nodiscard]] const std::string &getCurrentAnimationName() const;

            /*!
             * Get the current animation index
             *
             * @return the current animation index
             */
            [[nodiscard]] int getCurrentAnimationIndex() const;

            /*!
             * Set the current animation index
             *
             * @param newIndex new current animation index
             */
            void setCurrentAnimationIndex(int newIndex);

            /*!
             * Variable used to handle animation time
             */
            float deltaTime;
        private:
            std::string _currentAnimation; /*!< name of the current animation */

            std::map<std::string, Animation> _animations; /*!< map for handle all animation */

            int _currentAnimationIndex; /*!< the current animation index */
        };
    }
}

#endif //RTYPE_ANIMATOR_HPP