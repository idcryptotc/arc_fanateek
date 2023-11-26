#pragma once

#include <Windows.h>
#include <vector>

struct Brick
{
    int x;
    int y;
    COLORREF color;
};

struct Level
{
    std::vector<std::vector<Brick>> level;
};

struct Levels
{
    std::vector<Level> levels;
    Levels();
};
