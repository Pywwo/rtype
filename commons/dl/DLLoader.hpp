
/* Created by Romain FOUYER on 09/11/2019 at 17:33. */


#ifndef RTYPE_DLLOADER_HPP
#define RTYPE_DLLOADER_HPP

#include <vector>
#include <string>

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    #include <windows.h>
# else
    #include <dlfcn.h>
#include <iostream>

#endif

namespace rtype {

    namespace commons {

        /*!
         * @class DLLoader
         *
         * @brief Handle dynamic libraries
         */
        class DLLoader {
        public:
            DLLoader() = default;
            ~DLLoader();

            /*!
             * Get a function from a dynamic library
             *
             * @tparam T type of the function
             * @param libPath path to the dynamic library
             * @param functionName name of the function
             * @return the function wanted
             */
            template <typename T, typename U>
            T *fetchFunctionFromLibrary(const std::string &libPath, const std::string &functionName, U &param)
            {
                #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

                    HINSTANCE hGetProcIDDLL = LoadLibrary(libPath.c_str());

                    if (!hGetProcIDDLL) {
                        return nullptr;
                    }

                    auto *(*funci)(U) = reinterpret_cast<T *(*)(U)>(GetProcAddress(hGetProcIDDLL, functionName.c_str()));
                    if (!funci) {
                        return nullptr;
                    }
                    return funci(param);

                #else

                    void *symbol = dlopen(libPath.c_str(), RTLD_LAZY);

                    if (!symbol) {
                        return nullptr;
                    }

                    auto *(*function)(U) = reinterpret_cast<T *(*)(U)>(dlsym(symbol, functionName.c_str()));
                    if (!function) {
                        return nullptr;
                    }
                    _symbols.push_back(symbol);
                    return function(param);

                #endif
            }

            DLLoader(const DLLoader &) = delete;
            DLLoader &operator=(const DLLoader &) = delete;
        private:
            std::vector<void *> _symbols;
        };

    }

}

#endif //RTYPE_DLLOADER_HPP
