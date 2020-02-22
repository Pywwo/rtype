
/* Created by Romain FOUYER on 09/11/2019 at 17:33. */


#include "DLLoader.hpp"

rtype::commons::DLLoader::~DLLoader()
{
    # if UNIX
    for (auto &_it : _symbols) {
        dlclose(_it);
    }
    # endif
}