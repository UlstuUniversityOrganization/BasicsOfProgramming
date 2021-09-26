// Lab3.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab3.h"
#include <iostream>

#define MAX_LOADSTRING 100

// Глобальные переменные:
#define PI 3.14f
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

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
    LoadStringW(hInstance, IDC_LAB3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3));

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

    return (int) msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

struct float2
{
public:
    int x;
    int y;
};

void DrawStar(HDC hdc, int centerX, int centerY, int minorRadius, int majorRadius, int picksCount)
{
    float verticesCount = picksCount * 2;
    float2* pos = new float2[verticesCount];

    for (int i = 0; i < verticesCount; i++)
    {
        float alpha = ((float)i / verticesCount) * 2.0f * PI;
        pos[i].x = centerX + cos(alpha) * (i % 2 == 0 ? minorRadius : majorRadius);
        pos[i].y = centerY + sin(alpha) * (i % 2 == 0 ? minorRadius : majorRadius);
    }

    MoveToEx(hdc, pos[0].x, pos[0].y, NULL);
    for (int i = 1; i < verticesCount; i++)
    {
        LineTo(hdc, pos[i].x, pos[i].y);
    }
    LineTo(hdc, pos[0].x, pos[0].y);
}

void DrawStar(HDC hdc, int centerX, int centerY, int minorRadius, int majorRadius, int picksCount, int generationsCount)
{
    DrawStar(hdc, centerX, centerY, minorRadius, majorRadius, picksCount);

    if (generationsCount > 0)
    {
        float verticesCount = picksCount * 2;
        float2* pos = new float2[verticesCount];

        for (int i = 0; i < verticesCount; i++)
        {
            if (i % 2 == 1)
            {
                float alpha = ((float)i / verticesCount) * 2.0f * PI;
                pos[i].x = centerX + cos(alpha) * majorRadius;
                pos[i].y = centerY + sin(alpha) * majorRadius;
            }
        }
        for (int i = 1; i < verticesCount; i += 2)
            DrawStar(hdc, pos[i].x, pos[i].y, minorRadius * 0.3f, majorRadius * 0.3f, picksCount, generationsCount - 1);
    }
}

void DrawStarInderectRecursion1(HDC hdc, int centerX, int centerY, int minorRadius, int majorRadius, int picksCount, float decreaseCoefficient, int generationsCount);
void DrawStarInderectRecursion2(HDC hdc, int centerX, int centerY, int minorRadius, int majorRadius, int picksCount, float decreaseCoefficient, int generationsCount);


void DrawStarInderectRecursion1(HDC hdc, int centerX, int centerY, int minorRadius, int majorRadius, int picksCount, float decreaseCoefficient, int generationsCount)
{
    DrawStar(hdc, centerX, centerY, minorRadius, majorRadius, picksCount);

    if (generationsCount > 0)
    {
        float verticesCount = picksCount * 2;
        float2* pos = new float2[verticesCount];

        for (int i = 0; i < verticesCount; i++)
        {
            if (i % 2 == 1)
            {
                float alpha = ((float)i / verticesCount) * 2.0f * PI;
                pos[i].x = centerX + cos(alpha) * majorRadius;
                pos[i].y = centerY + sin(alpha) * majorRadius;
            }

        }
        for (int i = 1; i < verticesCount; i += 2)
            DrawStarInderectRecursion2(hdc, pos[i].x, pos[i].y, minorRadius * decreaseCoefficient, majorRadius * decreaseCoefficient, picksCount - 1, decreaseCoefficient, generationsCount - 1);
    }
}

void DrawStarInderectRecursion2(HDC hdc, int centerX, int centerY, int minorRadius, int majorRadius, int picksCount, float decreaseCoefficient, int generationsCount)
{
    DrawStar(hdc, centerX, centerY, minorRadius, majorRadius, picksCount);

    if (generationsCount > 0)
    {
        float verticesCount = picksCount * 2;
        float2* pos = new float2[verticesCount];

        for (int i = 0; i < verticesCount; i++)
        {
            if (i % 2 == 1)
            {
                float alpha = ((float)i / verticesCount) * 2.0f * PI;
                pos[i].x = centerX + cos(alpha) * majorRadius;
                pos[i].y = centerY + sin(alpha) * majorRadius;
            }

        }
        for (int i = 1; i < verticesCount; i += 2)
            DrawStarInderectRecursion1(hdc, pos[i].x, pos[i].y, minorRadius * decreaseCoefficient, majorRadius * decreaseCoefficient, picksCount + 1, decreaseCoefficient, generationsCount - 1);
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
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

            RECT clientRect;
            GetClientRect(hWnd, &clientRect);
            int width = clientRect.right - clientRect.left;
            int height = clientRect.bottom - clientRect.top;


            DrawStarInderectRecursion1(hdc, width / 2.0, height / 2.0f, 100, 200, 5, 0.3f, 4);

            //DrawStar(hdc, width / 2.0, height / 2.0f, 100, 200, 7);

            //int picksCount[] = {5, 4};
            //DrawStar(hdc, width / 2.0, height / 2.0f, 100, 200, picksCount, 5, sizeof(picksCount) / sizeof(int), 0);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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
