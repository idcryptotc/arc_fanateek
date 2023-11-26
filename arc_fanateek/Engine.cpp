#include "Engine.h"

HPEN hPenRed, hPenBlue, hPenPlatformRed, hPenPlatformBlue, hPenWhite;
HBRUSH hBrushRed, hBrushBlue, hBrushPlatformRed, hBrushPlatformBlue;
COLORREF Red, Blue, PlatformRed, PlatformBlue, White;
int InnerWidth = 21;

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

// Создание цветов
void CreateColors()
{
    White = RGB(213, 213, 213);
    Red = RGB(255, 85, 85);
    Blue = RGB(85, 255, 255);
    PlatformRed = RGB(151, 0, 0);
    PlatformBlue = RGB(0, 128, 192);
}

// Создание пера и кисти
void CreatePenAndBrush(const COLORREF& color, HPEN& pen, HBRUSH& brush)
{
    pen = CreatePen(PS_SOLID, 0, color);
    brush = CreateSolidBrush(color);
}

void Init()
{
    CreateColors();
    CreatePenAndBrush(Red, hPenRed, hBrushRed);
    CreatePenAndBrush(Blue, hPenBlue, hBrushBlue);
    CreatePenAndBrush(PlatformRed, hPenPlatformRed, hBrushPlatformRed);
    CreatePenAndBrush(PlatformBlue, hPenPlatformBlue, hBrushPlatformBlue);
    hPenWhite = CreatePen(PS_SOLID, Consts::GLOBAL_SCALE, White);
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

// Функция отрисовки платформы
void DrawPlatform(const HDC& hdc, int x, int y = 100)
{
    // Боковые шарики
    SelectObject(hdc, hPenPlatformRed);
    SelectObject(hdc, hBrushPlatformRed);

    Ellipse(hdc, x * Consts::GLOBAL_SCALE, y * Consts::GLOBAL_SCALE
        , (x + Consts::CIRCLE_SIZE) * Consts::GLOBAL_SCALE, (y + Consts::CIRCLE_SIZE) * Consts::GLOBAL_SCALE);
    Ellipse(hdc, (x + InnerWidth) * Consts::GLOBAL_SCALE, y * Consts::GLOBAL_SCALE
        , (x + Consts::CIRCLE_SIZE + InnerWidth) * Consts::GLOBAL_SCALE, (y + Consts::CIRCLE_SIZE) * Consts::GLOBAL_SCALE);

    // Блик
    SelectObject(hdc, hPenWhite);

    Arc(hdc
        , (x + 1) * Consts::GLOBAL_SCALE
        , (y + 1) * Consts::GLOBAL_SCALE
        , (x + Consts::CIRCLE_SIZE - 1) * Consts::GLOBAL_SCALE
        , (y + Consts::CIRCLE_SIZE - 1) * Consts::GLOBAL_SCALE
        , (x + 1 + 1) * Consts::GLOBAL_SCALE
        , (y + 1) * Consts::GLOBAL_SCALE
        , (x + 1) * Consts::GLOBAL_SCALE
        , (y + 1 + 2) * Consts::GLOBAL_SCALE);

    // Средняя часть
    SelectObject(hdc, hPenPlatformBlue);
    SelectObject(hdc, hBrushPlatformBlue);

    RoundRect(hdc, (x + 4) * Consts::GLOBAL_SCALE, (y + 1) * Consts::GLOBAL_SCALE
        , (x + 4 + InnerWidth - 1) * Consts::GLOBAL_SCALE, (y + 1 + 5) * Consts::GLOBAL_SCALE
        , 3 * Consts::GLOBAL_SCALE, 3 * Consts::GLOBAL_SCALE);
}

void DrawFrame(const HDC& hdc)
{
    DrawLevel(hdc);
    DrawPlatform(hdc, 50);
}

void DeleteObjects()
{
    DeleteObject(hPenRed);
    DeleteObject(hBrushRed);
    DeleteObject(hPenBlue);
    DeleteObject(hBrushBlue);
    DeleteObject(hPenPlatformRed);
    DeleteObject(hBrushPlatformRed);
    DeleteObject(hPenPlatformBlue);
    DeleteObject(hBrushPlatformBlue);
    DeleteObject(hPenWhite);
}
