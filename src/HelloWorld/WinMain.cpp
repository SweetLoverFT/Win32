#include <windows.h>
#include <stdio.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    LPCTSTR CLASS_NAME = _T("Sample Window Class");
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    // We can create additional value in any type, e.g. the initial window status.
    char *pLicense = new char[16];
    if (!pLicense)
        return EXIT_FAILURE;
    strcpy_s(pLicense, 16, "SweetLover\n");

    // Create the window.
    // The WM_NCCREATE and WM_CREATE message are sent before the window becomes visible.
    // That makes them a good place to initialize your UI for layout and so on.
    HWND hwnd = CreateWindowEx
    (
        WS_EX_LEFT,                     // Optional window styles.
        CLASS_NAME,                     // Window class
        _T("Learn to Program Windows"), // Window text
        WS_OVERLAPPEDWINDOW,            // Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr,    // Parent window    
        nullptr,    // Menu
        hInstance,  // Instance handle
        pLicense    // Additional application data, can also use SetWindowLongPtr to set
    );

    if (!hwnd)
        return FALSE;

    ::ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        ::TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}

#define UM_CLEAN_THREAD (WM_USER + 1)

void OnSize(HWND hwnd, UINT flag, int width, int height)
{
    TCHAR sInformation[MAX_PATH] = { };
    switch (flag)
    {
    case SIZE_MAXHIDE:
        _stprintf_s(sInformation, _T("SIZE_MAXHIDE: width = %d, height = %d\n"), width, height);
        break;

    case SIZE_MAXIMIZED:
        _stprintf_s(sInformation, _T("SIZE_MAXIMIZED: width = %d, height = %d\n"), width, height);
        break;

    case SIZE_MAXSHOW:
        _stprintf_s(sInformation, _T("SIZE_MAXSHOW: width = %d, height = %d\n"), width, height);
        break;

    case SIZE_MINIMIZED:
        _stprintf_s(sInformation, _T("SIZE_MINIMIZED: width = %d, height = %d\n"), width, height);
        break;

    case SIZE_RESTORED:
        _stprintf_s(sInformation, _T("SIZE_RESTORED: width = %d, height = %d\n"), width, height);
        break;

    default:
        _stprintf_s(sInformation, _T("Unknown: width = %d, height = %d\n"), width, height);
        break;
    }
    OutputDebugString(sInformation);
}

DWORD WINAPI OutputDebugInfo(LPVOID lpParameter)
{
    LPMSG pMsg = reinterpret_cast<LPMSG>(lpParameter);
    HWND hWnd = pMsg->hwnd;
    UINT flag = static_cast<UINT>(pMsg->wParam);
    int width = LOWORD(pMsg->lParam);  // Macro to get the low-order word.
    int height = HIWORD(pMsg->lParam); // Macro to get the high-order word.
    delete pMsg;
    OnSize(hWnd, flag, width, height);
    ::SendMessage(hWnd, UM_CLEAN_THREAD, 0, 0);
    return EXIT_SUCCESS;
}

// WindowProc is a UI thread and the handler for each message is synchronous operations that
// will block the WindowProc. Therefore, consider to use one of the multitasking facilities
// that are built into Windows:
//  1. Create a new thread
//  2. Use a thread pool
//  3. Use asynchronous I/O calls
//  4. Use asynchronous procedure calls
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LONG_PTR ptr = 0;
    HDC hdc = nullptr;
    PAINTSTRUCT ps = { };
    LPMSG pMsg = nullptr;
    LPCREATESTRUCT cs = nullptr;
    MSG msg = { hwnd, uMsg, wParam, lParam };
    static HANDLE hThread = INVALID_HANDLE_VALUE;
    char *pLicense = nullptr;
    switch (uMsg)
    {
        // WM_NCCREATE has higher priority than WM_CREATE, so we can pass additional user data
    case WM_NCCREATE:
        // cs->lpCreateParams is the member lpCreateParams in CreateStructure
        // We can get this user data because we set it at the last parameter in CreateWindowEx
        cs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        pLicense = reinterpret_cast<char*>(cs->lpCreateParams);
        // Pass additional user data
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pLicense));
        ::OutputDebugStringA(pLicense);
        break;

    case WM_CREATE:
        // Get user data from member lpCreateParams in CreateStructure
        ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
        pLicense = reinterpret_cast<char*>(ptr);
        ::OutputDebugStringA(pLicense);
        // ::MoveWindow, ::SetWindowPos        
        break;

    case WM_SIZE:
        // Please don't use:
        // OnSize(HWND hwnd, static_cast<UINT>(wParam), LOWORD(lParam), HIWORD(lParam));
        // Please create a new thread to respond to the message and notice the heap symbol pMsg:
        pMsg = new MSG(msg);
        hThread = ::CreateThread(nullptr, 0, OutputDebugInfo, pMsg, 0, nullptr);
        break;

    case WM_DESTROY:
        ::PostQuitMessage(EXIT_SUCCESS);
        break;

    case WM_CLOSE:
        ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
        pLicense = reinterpret_cast<char*>(ptr);
        delete[] pLicense;
        break;
        
    case WM_PAINT:
        hdc = ::BeginPaint(hwnd, &ps);
        // The current update region is given in the rcPaint member of PAINTSTRUCT
        // Even if you want to paint the entire client area, the operating system will only paint the update region
        ::FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1));
        ::EndPaint(hwnd, &ps);
        break;

    case UM_CLEAN_THREAD:
        ::CloseHandle(hThread);
        hThread = INVALID_HANDLE_VALUE;
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
