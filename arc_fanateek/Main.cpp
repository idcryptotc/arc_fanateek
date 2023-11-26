// arc_fanateek.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Main.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

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
};

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

HPEN hPenRed, hPenBlue;
HBRUSH hBrushRed, hBrushBlue;
COLORREF Red, Blue;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ARCFANATEEK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ARCFANATEEK));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ARCFANATEEK));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(15, 63, 31));
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ARCFANATEEK);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    RECT windowRect = { 0, 0, 320 * Consts::GLOBAL_SCALE, 200 * Consts::GLOBAL_SCALE };

    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, TRUE);

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

// Функция инициализации
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

// Функция отрисовки экрана
void DrawFrame(const HDC& hdc)
{
    DrawLevel(hdc);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
        {
            Init();
            break;
        }
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);

            switch (wmId)
            {
                case IDM_ABOUT:
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    break;
                case IDM_EXIT:
                    DestroyWindow(hWnd);
                    break;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            DrawFrame(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
        case WM_DESTROY:
            DeleteObject(hPenRed);
            DeleteObject(hBrushRed);
            DeleteObject(hPenBlue);
            DeleteObject(hBrushBlue);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
        case WM_INITDIALOG:
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
    }
    return (INT_PTR)FALSE;
}
