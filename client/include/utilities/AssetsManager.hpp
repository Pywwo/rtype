
/* Created by Romain FOUYER on 19/11/2019 at 16:52. */


#ifndef RTYPE_ASSETSMANAGER_HPP
#define RTYPE_ASSETSMANAGER_HPP

#include <map>
#include <string>

namespace rtype {
    namespace utils {
        /*!
         * @class assets manager
         * @brief Class for the assets who handle all assets in the rtype game
         */
        class AssetsManager {
        public:
            static AssetsManager &getInstance();

        private:
            AssetsManager();
            AssetsManager(const AssetsManager &other) = delete;
            AssetsManager(AssetsManager &&other) = delete;

        public:
            /*!
             * @brief Get all registered assets
             *
             * @return a map with all the assets
             */
            [[nodiscard]] std::map<std::string, std::string> getAssets() const;

            /*!
             * @brief Get a single asset
             *
             * @param asset name of the asset
             * @return the path to the asset
             */
            static std::string getAsset(const std::string &asset);

        private:
            std::map<std::string, std::string> _assets; /*!< handle all assets in the rtype game */

        public:
            /*!
             * @brief Get a single asset
             *
             * @param asset name of the asset
             * @return the path to the asset
             */
            const std::string &operator[](const std::string &asset);
        };

    }
}


#endif //RTYPE_ASSETSMANAGER_HPP
