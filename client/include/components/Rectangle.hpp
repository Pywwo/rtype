
/* Created by Romain FOUYER on 19/11/2019 at 09:55. */


#ifndef RTYPE_RECTANGLE_HPP
#define RTYPE_RECTANGLE_HPP

#include "components/Component.hpp"

namespace rtype {
    namespace components {
        /*!
         * @class Rectangle Component
         * @brief Components to handle spritesheets
         */
        class Rectangle : public ecs::components::Component {
        public:
            /*!
             * Constructor for Rectangle Component
             *
             * @param entity parent entity
             * @param left left offset
             * @param top top offset
             * @param width width of the rectangle
             * @param height height of the rectangle
             */
            Rectangle(ecs::entities::Entity &entity, int left, int top, int width, int height);
            /*!
             * @brief destructor of the component Rectangle
             */
            ~Rectangle() override = default;

            /* Setter */

            /*!
             * Basic setter for left parameter
             * @param left new left offset
             */
            void setLeft(int left);

            /*!
             * Basic setter for top parameter
             * @param top new top offset
             */
            void setTop(int top);

            /*!
             * Basic setter for width parameter
             * @param width new width of the rectangle
             */
            void setWidth(int width);

            /*!
             * Basic setter for height parameter
             * @param height new height of the rectangle
             */
            void setHeight(int height);

            /* Getter */

            /*!
             * Getter for left parameter
             * @return left offset
             */
            [[nodiscard]] int getLeft() const;

            /*!
             * Getter for top parameter
             * @return top offset
             */
            [[nodiscard]] int getTop() const;

            /*!
             * Getter for width parameter
             * @return width of the rectangle
             */
            [[nodiscard]] int getWidth() const;

            /*!
             * Getter for height parameter
             * @return height of the rectangle
             */
            [[nodiscard]] int getHeight() const;
        private:
            int _left; /*!< left size of the rectangle */
            int _top; /*!< top size of the rectangle */
            int _width; /*!< width size of the rectangle */
            int _height; /*!< height size of the rectangle */
        };
    }
}

#endif //RTYPE_RECTANGLE_HPP