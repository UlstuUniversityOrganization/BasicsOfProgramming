// Lab2(BasicsOfProgramming).cpp : Определяет точку входа для приложения.
//
#include "framework.h"
#include "Lab2(BasicsOfProgramming).h"
#include <iostream>


#define WIDTH 1280
#define HEIGHT 720
#define e 2.7182818284590452353
#define MAX_LOADSTRING 100
#define PI 3.14f

// Глобальные переменные:
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
    LoadStringW(hInstance, IDC_LAB2BASICSOFPROGRAMMING, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;

    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2BASICSOFPROGRAMMING));

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



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2BASICSOFPROGRAMMING));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB2BASICSOFPROGRAMMING);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, WIDTH, HEIGHT, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}




float Func(float x)
{
   // return 1 / (1 + pow(e, -x)); //// sigmoid
    return sin(x);
}

void PlotGraph(HDC& hdc, HWND hWnd, float lineWidth, float scale, COLORREF color = RGB(0, 0, 0), bool axes = true)
{
    RECT winRect;
    GetClientRect(hWnd, &winRect);

    if (axes)
    {
        MoveToEx(hdc, 0, winRect.bottom / 2.0f, NULL);
        LineTo(hdc, winRect.right, winRect.bottom / 2.0f);

        MoveToEx(hdc, winRect.right / 2.0f, 0, NULL);
        LineTo(hdc, winRect.right / 2.0f, winRect.bottom);
    }

    for (float x = 0; x < winRect.right; x++)
        for (float y = 0; y < winRect.bottom; y++)
        {
            float X = (x - winRect.right / 2.0f) / scale;
            float Y = ((winRect.bottom - y) - winRect.bottom / 2.0f) / scale;
            if (Y <= Func(X) + lineWidth / scale && Y >= Func(X) - lineWidth / scale)
                SetPixel(hdc, x, y, color);
        }
}

struct double2
{
    double long x;
    double long y;
};

struct float3
{
    float long x;
    float long y;
    float long z;

    float3 operator / (float k)
    {
        float3 v;
        v.x = x / k;
        v.y = y / k;
        v.z = z / k;
        return v;
    }
    float3 operator * (float k)
    {
        float3 v;
        v.x = x * k;
        v.y = y * k;
        v.z = z * k;
        return v;
    }
    float3 operator + (float3 k)
    {
        float3 v;
        v.x = x + k.x;
        v.y = y + k.y;
        v.z = z + k.z;
        return v;
    }
    float3 operator - (float3 k)
    {
        float3 v;
        v.x = x - k.x;
        v.y = y - k.y;
        v.z = z - k.z;
        return v;
    }
};

double long BasieCurve(double2 P, double2 A, double2 B, double2 C)
{
    double long nan = -99999;
    double long a = (C.x - (2 * B.x) - A.x);

    if (a == 0)
        return nan;

    double long  b = 2 * B.x;
    double long c = (A.x - P.x);

    double long D = pow(b, 2) - (4 * a * c);

    if (D >= 0)
    {
        double long t1 = (-b - sqrt(D)) / (2.0f * a);
        double long t2 = (-b + sqrt(D)) / (2.0f * a);

        return t2;
    }
    return nan;
}

POINT GetBasieCurvePoint(double2 A, double2 B, double2 C, float t)
{
    POINT result;

    result.x = (B.x - A.x) * t + A.x + (((C.x - B.x) * t + B.x) - ((B.x - A.x) * t + A.x)) * t;
    result.y = (B.y - A.y) * t + A.y + (((C.y - B.y) * t + B.y) - ((B.y - A.y) * t + A.y)) * t;

    return result;
}


class Pen
{
public:

    HBRUSH brush;
    HPEN pen;
    HDC hdc;

    Pen(HDC &hdc) : hdc(hdc) {}
    ~Pen()
    {
        if (brush)
            DeleteObject(brush);
        if (pen)
            DeleteObject(pen);
    }

    void ChangeHDC(HDC &newHDC)
    {
        this->hdc = newHDC;
    }
    void SetBrush(COLORREF color)
    {
        if (brush)
            DeleteObject(brush);
        brush = CreateSolidBrush(color);
        SelectObject(hdc, brush);
    }

    void SetPen(COLORREF color, int Width)
    {
        if (pen)
            DeleteObject(pen);
        pen = CreatePen(PS_SOLID, Width, color);
        SelectObject(hdc, pen);
    }

};

struct BasieCurve
{
    POINT A;
    POINT B;
    POINT C;
};

POINT* GetBasieCurvePoints(POINT A, POINT B, POINT C, int pointsCount)
{
    double2 Ad = { A.x, A.y };
    double2 Bd = { B.x, B.y };
    double2 Cd = { C.x, C.y };
    POINT* point = new POINT[pointsCount];
    for (int i = 0; i < pointsCount; i++)
    {
        if (i == 0)
            int k = 0;
        if (i == pointsCount - 1)
            int k = 5;
        point[i] = GetBasieCurvePoint(Ad, Bd, Cd, (float)i / (float)pointsCount);
    }
    return point;
}

void DrawBasiePolygon(HDC hdc, POINT* basieCurvePolygon, int basiePointsCount, int accuracyCount)
{
    float count = accuracyCount * basiePointsCount;
    POINT* pPoints = new POINT[count];

    long long pointer = 0;
    for (int x = 0; x < basiePointsCount * 3; x += 3)
    {
        POINT* tempPoints = GetBasieCurvePoints(basieCurvePolygon[x], basieCurvePolygon[x + 1], basieCurvePolygon[x + 2], accuracyCount);
        for (int y = 0; y < accuracyCount; y++)
        {
            if (y == accuracyCount - 1)
                float k = 0;
            pPoints[pointer] = tempPoints[y];
            pointer++;
        }
        delete[accuracyCount] tempPoints;

        if (x == 0)
            x == 2;
    }
    Polygon(hdc, pPoints, count);
}

void DrawTeslaLogo(HDC &hdc, Pen &pen, COLORREF logoColor)
{
    pen.SetBrush(logoColor);

    POINT basieCurvePolygonHAT[] =
    {
        475.05, 213.95,
        658, 134.4,
        836.8, 213.3,

        836.8, 213.3,
        831.4, 224,
        825.9, 234,

        825.9, 234,
        658, 156,
        485.2, 233.5,

        485.2, 233.5,
        480, 224.2,
        475.05, 213.95

    };

    POINT basieCurvePolygonBODY[] =
    {
        821, 242,
        804, 280,
        770, 280.7,

        770, 280.7,
        799.7, 258.2,
        705.8, 253,

        705.8, 253,
        683, 382,
        655.4, 536,

        655.4, 536,
        625.6, 377.5,
        603.2, 252,

        603.2, 252,
        519.3, 252.5,
        538.7, 279.5,

        538.7, 279.5,
        500.6, 267.9,
        489.5, 242.3,

        489.5, 242.3,
        549.3, 207.3,
        617, 211.9,

        617, 211.9,
        639, 238.5,
        654, 256.2,

        654, 256.2,
        674.3, 233.5,
        691.3, 212.8,

        691.3, 212.8,
        761.8, 211.5,
        821, 242
    };

    POINT basieCurvePolygonHOLE[] =
    {
        617, 211.9,
        639, 238.5,
        654, 256.2,

        654, 256.2,
        674.3, 233.5,
        691.3, 212.8,

        691.3, 212.8,
        652.2, 203,
        617, 211.9,


    };
    DrawBasiePolygon(hdc, basieCurvePolygonHAT, sizeof(basieCurvePolygonHAT) / (sizeof(POINT) * 3), 80);
    DrawBasiePolygon(hdc, basieCurvePolygonBODY, sizeof(basieCurvePolygonBODY) / (sizeof(POINT) * 3), 80);
}

void DrawHeadLogo(HDC& hdc, Pen& pen, COLORREF logoColor)
{
    pen.SetBrush(logoColor);

    POINT body[] =
    {
        611.4, 600,
        483, 573,
        457, 459,

        457, 459,
        447, 430,
        408.1, 433,

        408.1, 433,
        425.5, 399.6,
        461, 395,

        461, 395,
        467, 349,
        486, 326,

        486, 326,
        487.5, 294.4,
        458.7, 292.3,

        458.7, 292.3,
        491.4, 260.6,
        531, 269.6,

        531, 269.6,
        564.8, 203.8,
        489.5, 163.6,

        489.5, 163.6,
        571.4, 105.5,
        635.6, 207.6,

        635.6, 207.6,
        677, 191,
        715.4, 219.5,

        715.4, 219.5,
        675, 247.2,
        703.3, 273.5,

        703.3, 273.5,
        703.2, 269.8,
        703.2, 266.4,

        703.2, 266.4,
        775.3, 307.2,
        766.5, 393,

        766.5, 393,
        797.2, 406,
        813.6, 431.4,

        813.6, 431.4,
        773.7, 436.6,
        758, 477.3,

        758, 477.3,
        735.3, 572.7,
        611.4, 600
    };

    POINT eye1[] =
    {
        522.2, 476.3,
        523.7, 503.3,
        544.7, 526.6,

        544.7, 526.6,
        568.7, 538,
        593.4, 536,

        593.4, 536,
        598.85, 535.24,
        600.8, 531.8,

        600.8, 531.8,
        553, 512.4,
        522.2, 476.3
    };

    POINT eye2[] =
    {
        620.4, 530.6,
        623.3, 535.9,
        641.2, 535.2,
        
        641.2, 535.2,
        654, 535,
        660, 532.5,

        660, 532.5,
        661.2, 538.7,
        657.7, 545.7,

        657.7, 545.7,
        667, 537.5,
        669.8, 529.8,

        669.8,529.8,
        680.4, 523.5,
        688.1, 509.5,

        688.1, 509.5,
        696.2, 496.3,
        699.2, 475.7,

        699.2, 475.7,
        684, 490.3,
        669.3, 504.72,

        669.3, 504.72,
        663.05, 492.5,
        658.6, 488,

        658.6, 488,
        653.6, 479.7,
        651.7, 469.3,

        651.7, 469.3,
        649.9, 475.7,
        650.8, 482.05,

        650.8, 482.05,
        653.5, 492.9,
        657.5, 499.5,

        657.5, 499.5,
        660.1, 504.7,
        659.84, 510.4,

        659.84, 510.4,
        642.8, 519.3,
        620.4, 530.6

    };

   
    DrawBasiePolygon(hdc, body, sizeof(body) / (sizeof(POINT) * 3), 80);
    pen.SetBrush(RGB(53, 53, 53));
    DrawBasiePolygon(hdc, eye1, sizeof(eye1) / (sizeof(POINT) * 3), 80);
    DrawBasiePolygon(hdc, eye2, sizeof(eye2) / (sizeof(POINT) * 3), 80);


}

float3 NormalizeCoords(float3 coord, float screenWidth, float screenHeight)
{
    float3 newCoords = { (coord.x / screenWidth) * 2 - 1, (coord.y / screenHeight) * 2 - 1, coord.z };
    return newCoords;
}

float3 UnNormalizeCoords(float3 coord, float screenWidth, float screenHeight)
{
    float3 newCoords = { ((coord.x + 1) * screenWidth) / 2, ((coord.y + 1) * screenHeight) / 2, coord.z };
    return newCoords;
}

float lenght(float3 v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
float3 normalize(float3 v)
{
    return v / lenght(v);
}

float dot(float3 v1, float3 v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z) / (lenght(v1) * lenght(v2));
}

struct Ray
{

    float t;
    float3 direction;
    float3 origin;
    float3 energy;
};

struct Hit
{
    float t = 99999999999;
    float3 direction;
    float3 position;
    float3 normal;
    float3 albedo;
};

void IntersectSphere(Ray ray, Hit &bestHit, float3 spherePos, float radius, float3 albedo)
{

    float3 d = ray.origin - spherePos;
    float p1 = -dot(ray.direction, d);
    float p2sqr = p1 * p1 - dot(d, d) + radius * radius;
    if (p2sqr < 0)
        return;
    float p2 = sqrt(p2sqr);
    float t = p1 - p2 > 0 ? p1 - p2 : p1 + p2;
    if (t > 0 & t < bestHit.t)
    {
        bestHit.t = t;
        bestHit.position = (ray.direction * t) + ray.origin;
        //float3 normal = normalize(bestHit.position - spherePos);
        //float inorout = dot(normal, ray.direction);
        //if (inorout < 0)
        //{
        //    bestHit.normal = normal;
        //}
        //else if (inorout > 0)
        //    bestHit.normal = normal * -1;
        bestHit.albedo = albedo / (t / 4);
        return;
    }
    else
    {
        bestHit.albedo = {0, 0, 0.25f};
    }
}

Hit Trace(Ray ray)
{
    Hit hit{};
    float3 spherePos = { 0, 0, 100};
    float3 albedo = { 0, 1, 1 };
    IntersectSphere(ray, hit, spherePos, 0.1f, albedo);

    return hit;
}

float3 RayTracing(HDC hdc, float x, float y, RECT clientRect)
{
    float3 pixelPosUnnormalized = {x, y , 0};
    float3 pixelPos = NormalizeCoords(pixelPosUnnormalized, clientRect.right, clientRect.bottom);
    
    pixelPos.z = 1;


    Ray ray;
    ray.origin = { 0, 0, 0 };
    ray.direction = ray.origin + normalize(pixelPos);


    //for (int i = 0; i < 2; i++)
    //{
      Hit hit = Trace(ray);
  //  }
    
    float3 color = hit.albedo;
    return color;
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


            Pen pen(hdc);
            pen.SetBrush(RGB(0, 0, 0));

            RECT clientRect;
            GetClientRect(hWnd, &clientRect);
            int width = clientRect.right - clientRect.left;
            int height = clientRect.bottom - clientRect.top;
            
            //Rectangle(hdc, clientRect.left, clientRect.top, clientRect.right, clientRect.bottom);    

            //------------------------background--------------------------------               
            //for(float x = 0; x < clientRect.right; x++)  
            //    for (float y = 0; y < clientRect.right; y++)
            //    {
            //        SetPixel(hdc, x, y, RGB(0, (float)(60 - (y / clientRect.right) * 60), (float)(60 - (x / clientRect.right) * 60)));
            //    }
            //------------------------background--------------------------------
            
            //DrawHeadLogo(hdc, pen, RGB(13, 196, 210));
            
            
            
            //  
            DrawTeslaLogo(hdc, pen, RGB(0, 0, 0));
            DrawStarInderectRecursion1(hdc, (width / 2.0) + 25, height / 2.0f - 220, 100 / 5, 200 / 5, 5, 0.3f, 4);

            //DrawTeslaLogo(hdc, pen, RGB(255, 255, 255));
            //DrawHeadLogo(hdc, pen, RGB(13, 196, 210)); // lighter
            //DrawHeadLogo(hdc, pen, RGB(13, 196 - 25, 210 - 25)); // darker
            
            // -----------------------Ray tracing-----------------------------
        
            //for(float x = 0; x < 1280; x++)  
            //    for (float y = 0; y < 720; y++)
            //    {
            //        float3 color = RayTracing(hdc, x, y, clientRect);
            //        if (color.x < 0)
            //            color.x = 0;
            //        if (color.y < 0)
            //            color.y = 0;
            //        if (color.z < 0)
            //            color.z = 0;
            //        SetPixel(hdc, x, y, RGB(color.x * 255, color.y * 255, color.z * 255));
            //    }
            // -----------------------Ray tracing-----------------------------

            //PlotGraph(hdc, hWnd,2, 200, RGB(0, 0, 0), true);

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
