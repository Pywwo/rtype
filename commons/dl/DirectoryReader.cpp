/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** DirectoryReader.cpp
*/

/* Created the 30/11/2019 at 20:01 by jbulteau */

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    #include <windows.h>
#else
    #include <dirent.h>
#endif

#include "DirectoryReader.hpp"


std::vector<std::string> rtype::commons::DirectoryReader::fetchFilesFromDirectory(const std::string &path)
{
    std::vector<std::string> files;

    #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

        WIN32_FIND_DATA data;

        HANDLE hFind = FindFirstFile("./lib/*", &data);

        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                files.emplace_back(std::string(data.cFileName));
            } while (FindNextFile(hFind, &data));
            FindClose(hFind);
        }

    #else

        struct dirent *entry;
        DIR *dir  = opendir(path.c_str());

        if (!dir)
            return files;
        while ((entry = readdir(dir)))
            files.emplace_back(std::string(entry->d_name));
        closedir(dir);

    #endif

    return files;
}