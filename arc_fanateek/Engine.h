#pragma once

#include <Windows.h>

enum Consts : int
{
    GLOBAL_SCALE = 4,
    BRICK_WIDTH = 15,
    BRICK_HEIGHT = 7,
    CELL_WIDTH = 16,
    CELL_HEIGHT = 8,
    LEVEL_X_OFFSET = 8,
    LEVEL_Y_OFFSET = 6,
    LEVEL_X_SIZE = 12,
    LEVEL_Y_SIZE = 14,
    CIRCLE_SIZE = 7
};

// Функция инициализации
void Init();

// Функция отрисовки экрана
void DrawFrame(const HDC& hdc);

// Освобождение ресурсов
void DeleteObjects();