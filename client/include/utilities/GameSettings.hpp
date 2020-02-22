
/* Created by Romain FOUYER on 19/11/2019 at 16:07. */


#ifndef RTYPE_GAMESETTINGS_HPP
#define RTYPE_GAMESETTINGS_HPP

namespace rtype {
    namespace utils {
        /*!
         * @class GameSettings
         * @brief Singleton class with all games settings
         */
        class GameSettings {
        public:
            static GameSettings &getInstance();

            /*!
             * @brief Get the width of the window
             *
             * @return width of the window
             */
            [[nodiscard]] float getWidth() const;

            /*!
             * @brief Get the height of the window
             *
             * @return the height of the window
             */
            [[nodiscard]] float getHeight() const;
        # if UNIX
            GameSettings(const GameSettings &other) = delete;
            GameSettings(GameSettings &other) = delete;
        # endif
        private:
            GameSettings();
        private:
            float _width; /*!< handle width of the game window */
            float _height; /*!< handle height of the game window */
        };
    }
}


#endif //RTYPE_GAMESETTINGS_HPP
