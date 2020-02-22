
/* Created by Romain FOUYER on 23/11/2019 at 17:35. */


#ifndef RTYPE_EFFECT_HPP
#define RTYPE_EFFECT_HPP

#include "components/Component.hpp"

namespace rtype {
    namespace components {
        /*!
         * @class Effect component
         * @brief Component to handle visual effects
         */
        class Effect : public ecs::components::Component {
        public:

            /*!
             * @enum EffectType
             * @brief Describe the type of the effect
             */
            enum EffectType {
                FIRE_EXPLOSION,
                LIGHTNING_EXPLOSION
            };

            /*!
             * Constructor of the Effect component
             *
             * @param entity parent entity
             * @param type type of the effect, watch EffectType enum for more information
             */
            Effect(ecs::entities::Entity &entity, EffectType type);
            ~Effect() override = default;

            /*!
             * Fetch the type of the effect
             *
             * @return the effect type
             */
            [[nodiscard]] const EffectType &getType() const;

            /*!
             * Set a new type to the effect
             *
             * @param newType new type for the effect
             */
            void setType(EffectType newType);

            /*!
             * Get asset corresponding on the effect type
             *
             * @example type: LIGHTNING_EXPLOSION -> assetManager["lightning_explosion"]
             * @return the asset corresponding on the effect type
             */
            [[nodiscard]] const std::string &getAsset() const;

            /*!
             * Get the number of animation of the effect
             *
             * @return number of animation
             */
            [[nodiscard]] int getAnimationNumber() const;

            /*!
             * Get the sound effect linked to the type of the effect
             *
             * @return a sound path
             */
            [[nodiscard]] const std::string &getSoundEffect() const;

        private:
            EffectType _type; /*!< handle the effect type */
        };
    }
}

#endif //RTYPE_EFFECT_HPP