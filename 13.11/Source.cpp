#include "framework.h"
#include <stdafx.h>
#include "windef.h"
#include "resource.h"

#define MAX_LOADSTRING 100


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: разместите код здесь.
    MSG msg;
    HACCEL hAccelTable;

    // Инициализация глобальных строк
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

    // Цикл основного сообщения:
    while (GetMessage(&msg, NULL, 0, 0))
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
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
//  КОММЕНТАРИИ:
//
//    Эта функция и ее использование необходимы только в случае, если нужно, чтобы данный код
//    был совместим с системами Win32, не имеющими функции RegisterClassEx'
//    которая была добавлена в Windows 95. Вызов этой функции важен для того,
//    чтобы приложение получило "качественные" мелкие значки и установило связь
//    с ними.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCE(IDC_MY);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;

    hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

    hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработка меню приложения
//  WM_PAINT    -Закрасить главное окно
//  WM_DESTROY   - ввести сообщение о выходе и вернуться.
//
//

//HWND WINAPI CreateWindowExW(DWORD dwExStyle,LPCWSTR lpClassName,LPCWSTR lpWindowName,DWORD dwStyle,int X,int Y,int nWidth,int nHeight,HWND hWndParent,HMENU hMenu,HINSTANCE hInstance,LPVOID lpParam);


LRESULT CALLBACK ChildProc(HWND UINT, WPARAM, LPARAM);
TCHAR ChildClassName[MAX_LOADSTRING] = _T("WinChild");
ATOM MyRegisterChildClass()
{
    WNDCLASSEX wcex = { 0 };
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.lpfnWndProc = ChildProc;
    wcex.hInstance = hInst;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = ChildClassName;
    return RegisterClassEx(&wcex);
}
static HFONT newFont;
static HWND hChild[9];
unsigned char k[9] = { 0 };
char text[] = { ' ','x','0' };
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int i;
    static int sx, sy;
    switch (message)
    {
    case WM_CREATE:
        MyRegisterChildClass();
        for (i = 0; i < 9; i++)
            hChild[i] = CreateWindow(ChildClassName, NULL, WS_CHILD | WS_DLGFRAME | WS_VISIBLE, 0, 0, 0, 0, hWnd, NULL, hInst, NULL);

        break;
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)break;//Кнопка свертвывания окна
        sx = LOWORD(lParam) / 3; // ширина дочернего окна
        sy = HIWORD(lParam) / 3; //Высота дочернего окна
        if (newFont)DeleteObject(newFont);
        newFont = CreateFont(min(sx, sy), 0, 0, 0, FW_NORMAL, 0, 0, 0,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
        for (i = 0; i < 9; i++)
        {
            MoveWindow(hChild[i], (i % 3) * sx, (i / 3) * sy, sx, sy, TRUE);
            UpdateWindow(hChild[i]);
        }
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_NEW:
            for (i = 0; i < 9; i++)
            {
                k[i] = 0;
                InvalidateRect(hChild[i], NULL, 1);
                UpdateWindow(hChild[i]);
            }

            break;
        case IDM_EXIT:DestroyWindow(hWnd);
            break;
        default:return DefWindowProc(hWnd, message, wParam, lParam);
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
////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rt;
    int i, s;
    char* ch;
    switch (message)
    {
    case WM_LBUTTONDOWN:
        for (i = 0; hWnd != hChild[i]; i++);
        if (k[i])break; else k[i] = 1;
        InvalidateRect(hWnd, NULL, 1);
        UpdateWindow(hWnd);
        srand(lParam);
        for (i = s = 0; i < 9; i++) if (k[i])s++;
        if (s == 9)MessageBox(hWnd, _T("Для следущего сенса выбирайте\New"), _T("Конец игры"), MB_OK | MB_ICONQUESTION);
        else
        {
            while (true)
            {
                s = rand() * 9 / (RAND_MAX + 1);
                if (k[s])continue;
                k[s] = 2;
                InvalidateRect(hChild[s], NULL, 1);
                UpdateWindow(hChild[s]);
                break;
            }
        }
        break;
    case WM_PAINT:
        for (i = 0; hWnd != hChild[i]; i++);
        if (k[i])
        {
            ch = text + k[i];
            hdc = BeginPaint(hWnd, &ps);
            GetClientRect(hWnd, &rt);
            SelectObject(hdc, newFont);
            DrawTextA(hdc, ch, 1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            EndPaint(hWnd, &ps);
        }//фоновая закраска
        else DefWindowProc(hWnd, message, wParam, lParam);
        break;
    default:return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}