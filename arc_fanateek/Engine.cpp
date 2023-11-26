#include "Engine.h"

HPEN hPenRed, hPenBlue;
HBRUSH hBrushRed, hBrushBlue;

char Level_01[Consts::LEVEL_Y_SIZE][Consts::LEVEL_X_SIZE] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

enum class BrickType
{
    None,
    Red,
    Blue
};

COLORREF Red, Blue;

void Init()
{
    Red = RGB(255, 85, 85);
    Blue = RGB(85, 255, 255);
    hPenRed = CreatePen(PS_SOLID, 0, Red);
    hPenBlue = CreatePen(PS_SOLID, 0, Blue);
    hBrushRed = CreateSolidBrush(Red);
    hBrushBlue = CreateSolidBrush(Blue);
}

// Функция отрисовки кирпича
void DrawBrick(const HDC& hdc, int x, int y, BrickType brickType)
{
    HPEN hPen;
    HBRUSH hBrush;

    switch (brickType)
    {
        case BrickType::None:
            return;
        case BrickType::Red:
            hPen = hPenRed;
            hBrush = hBrushRed;
            break;
        case BrickType::Blue:
            hPen = hPenBlue;
            hBrush = hBrushBlue;
            break;
        default:
            return;
    }

    SelectObject(hdc, hPen);
    SelectObject(hdc, hBrush);
    RoundRect(hdc, x * Consts::GLOBAL_SCALE, y * Consts::GLOBAL_SCALE
        , (x + Consts::BRICK_WIDTH) * Consts::GLOBAL_SCALE
        , (y + Consts::BRICK_HEIGHT) * Consts::GLOBAL_SCALE
        , 2 * Consts::GLOBAL_SCALE, 2 * Consts::GLOBAL_SCALE);
}

// Функция отрисовки уровня
void DrawLevel(const HDC& hdc)
{
    for (int i = 0; i < Consts::LEVEL_Y_SIZE; ++i)
    {
        for (int j = 0; j < Consts::LEVEL_X_SIZE; ++j)
        {
            DrawBrick(hdc, Consts::LEVEL_X_OFFSET + j * Consts::CELL_WIDTH, Consts::LEVEL_Y_OFFSET + i * Consts::CELL_HEIGHT, (BrickType)Level_01[i][j]);
        }
    }
}

void DrawFrame(const HDC& hdc)
{
    DrawLevel(hdc);
}

void DeleteObjects()
{
    DeleteObject(hPenRed);
    DeleteObject(hBrushRed);
    DeleteObject(hPenBlue);
    DeleteObject(hBrushBlue);
}
