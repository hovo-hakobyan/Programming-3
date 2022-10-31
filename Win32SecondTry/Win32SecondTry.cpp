// Win32SecondTry.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Win32SecondTry.h"
#include <sstream>
#include <windowsx.h>
#include <vector>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
std::vector<POINT> g_Points;


// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32SECONDTRY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32SECONDTRY));

    MSG msg;
   
    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32SECONDTRY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32SECONDTRY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

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

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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
        //Les
    case WM_LBUTTONUP:
        {
#ifdef _UNICODE
        std::wstringstream buffer;
#else
        std::stringstream buffer;
#endif // _UNICODE

        
        g_Points.push_back(POINT{ GET_X_LPARAM(lParam) ,GET_Y_LPARAM(lParam) });
        InvalidateRect(hWnd, NULL, true);  
       /* buffer << g_Points.size() << ' ';
        MessageBox(NULL, buffer.str().c_str(), _T("Title goes here"), MB_OK);*/
        }
        break;
    case WM_RBUTTONUP:
        g_Points.clear();
        InvalidateRect(hWnd, NULL, true);
        break;
    case WM_ACTIVATE:
    {
        if (wParam == WA_ACTIVE)
        {
            SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)_T("Active"));
        }
        else
        {
            SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)_T("Inactive"));
        }
        //MessageBox(NULL, _T("Window activated"), _T("Title"), MB_OK);

    }
        break;
    break;
    case WM_PAINT:
    {
        //PAINTSTRUCT ps; //We hardly use this, it just needs to be here

        ////Returns the number of the Device Context of our Window
        ////Makes sure that there cannot be drawn outside of the window
        ////The background of the window is redrawn
        //HDC hdc = BeginPaint(hWnd, &ps); 

        //HPEN blackPen = CreatePen(PS_SOLID, 1, RGB(80, 80, 50)); //Create pen
        //HPEN oldPen = (HPEN)SelectObject(hdc, blackPen); //replace old pen by the newly created one

        //HBRUSH blackBrush = CreateSolidBrush(RGB(80, 80, 50));
        //HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blackBrush);

        //if (g_Points.size() > 0)
        //{
        //    MoveToEx(hdc, g_Points[0].x, g_Points[0].y, 0);
        //    Ellipse(hdc, g_Points[0].x - 2, g_Points[0].y - 2, g_Points[0].x + 2, g_Points[0].y + 2);

        //    for (int count = 1; count < (int)g_Points.size(); ++count)
        //    {
        //        LineTo(hdc, g_Points[count].x, g_Points[count].y);
        //        Ellipse(hdc, g_Points[count].x - 2, g_Points[count].y - 2, g_Points[count].x + 2, g_Points[count].y + 2);
        //    }
        //}

        //SelectObject(hdc, oldBrush);
        //DeleteObject(blackBrush);

        //SelectObject(hdc, oldPen);  //put old pen back into the Device Context
        //DeleteObject(blackPen);     //delte the black pen
  
        //EndPaint(hWnd, &ps); //Clean up the Device Context


        if (g_Points.size() <= 0)
            return 0;

        PAINTSTRUCT ps;

        HDC hdc = BeginPaint(hWnd, &ps);

        
        HPEN redPen = CreatePen(PS_DASHDOTDOT, 10, RGB(255, 0, 0));
        HPEN oldPen = (HPEN)SelectObject(hdc, redPen);

        HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blueBrush);

        const int ellipseSize = 2;
        MoveToEx(hdc, g_Points[0].x, g_Points[0].y,0);
        Ellipse(hdc, g_Points[0].x - ellipseSize, g_Points[0].y + ellipseSize, g_Points[0].x + ellipseSize, g_Points[0].y - ellipseSize);
        
        BOOL shouldConnect = false;
        
        for (int count = 1; count < (int)g_Points.size(); ++count)
        {
            if (shouldConnect)
            {
                MoveToEx(hdc, g_Points[count].x, g_Points[count ].y, 0);
                shouldConnect = false;
                
            }

            LineTo(hdc, g_Points[count].x, g_Points[count].y);
            Ellipse(hdc, g_Points[count].x - 2, g_Points[count].y - 2, g_Points[count].x + 2, g_Points[count].y + 2);

            if ((count - 2) % 3 ==0 )
            {
                shouldConnect = true;
            }

            if (shouldConnect)
            {
                LineTo(hdc, g_Points[count - 2].x, g_Points[count - 2].y);
            }
        }

        SelectObject(hdc, oldBrush);
        DeleteObject(blueBrush);

        SelectObject(hdc, oldPen);
        DeleteObject(redPen);

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

// Message handler for about box.
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
