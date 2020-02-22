
/* Created by Romain FOUYER on 22/11/2019 at 09:58. */


#ifndef RTYPE_CAMERA_HPP
#define RTYPE_CAMERA_HPP

#include "components/Component.hpp"

#include "types/Vector.hpp"

#include <SFML/Graphics.hpp>

namespace rtype {
    namespace components {
        /*!
         * @class Camera component
         * @brief Class who handles camera in the game
         */
        class Camera : public ecs::components::Component {
        public:
            /*!
             * Default constructor for the camera component
             *
             * @param entity parent entity
             */
            Camera(ecs::entities::Entity &entity);

            /*!
             * Constructor for the camera component
             *
             * @param entity parent entity
             * @param center center of the camera
             * @param zoom zoom of the camera
             *          <1: zoom in
             *          >1: zoom out
             */
            Camera(ecs::entities::Entity &entity, commons::Vector2<float> center, float zoom);
            ~Camera() override = default;

            /*!
             * Set the center of the camera
             *
             * @param x new x center position
             * @param y new y center position
             */
            void setCenter(float x, float y);

            /*!
             * Get the center of the camera
             *
             * @return the center position of the camera
             */
            [[nodiscard]] const commons::Vector2<float> &getCenter() const;

            /*!
             * Set zoom to the camera
             * @param newZoom new zoom of the camera
             */
            void setZoom(float newZoom);

            /*!
             * Get the current zoom of the camera
             *
             * @return current zoom of the camera
             */
            [[nodiscard]] float getZoom() const;

            /*!
             * Set the current size of the camera
             *
             * @param x new x size
             * @param y new y size
             */
            void setSize(float x, float y);

            /*!
             * Get the current size of the camera
             *
             * @return current size of the camera
             */
            [[nodiscard]] const commons::Vector2<float> &getSize() const;

            /*!
             * Move the camera
             * @param offsetX x offset to move
             * @param offsetY y offset to move
             */
            void move(float offsetX, float offsetY);

            /*!
             * Return the camera
             *
             * @return the camera
             */
            const sf::View &getCamera() const;
        private:
            sf::View _camera; /*!< current view of the camera */

            commons::Vector2<float> _center; /*!< vector for handle the position of the center camera */
            commons::Vector2<float> _size; /*!< vector for handle the size of the camera */
            float _zoom; /*!< float for handle the zoom of the camera */
        };
    }
}

#endif //RTYPE_CAMERA_HPP