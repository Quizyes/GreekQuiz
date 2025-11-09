#pragma once

#include <string>

typedef struct dbEntry
{
    int id{0}, lesson{0};
    std::string head{""}, inflected{""}, parse{""};
    void clear()
    {
        head.clear();
        inflected.clear();
        parse.clear();
        id = 0;
        lesson = 0;
    }
} dbEntry;