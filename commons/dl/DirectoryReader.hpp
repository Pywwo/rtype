/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** DirectoryReader.hpp
*/

/* Created the 30/11/2019 at 20:01 by jbulteau */

#ifndef RTYPE_DIRECTORYREADER_HPP
#define RTYPE_DIRECTORYREADER_HPP

#include <string>
#include <vector>

namespace rtype {

    namespace commons {

        class DirectoryReader {
        public:
            DirectoryReader() = default;
            ~DirectoryReader() = default;

            static std::vector<std::string> fetchFilesFromDirectory(const std::string &path);
        };
    }
}

#endif //RTYPE_DIRECTORYREADER_HPP
