# Win32/C++

Create this solution to study Windows development

## Branches

1. **master** branch: Used as a **release** branch
2. **feature-beginner** branch: Used to learn Win32/C++ for each published stable projects
   - [HelloWorld](https://docs.microsoft.com/zh-cn/windows/desktop/LearnWin32/your-first-windows-program): This sample application shows how to create a minimal Windows program
   - [BaseWindow Sample](https://docs.microsoft.com/zh-cn/windows/win32/learnwin32/managing-application-state-): This sample application shows how to pass application state data in the **<code>[WM_NCCREATE](https://docs.microsoft.com/zh-cn/windows/desktop/winmsg/wm-nccreate)</code>** message with C++ **CRTP** (curiously recurring template pattern)
   - [LearnCom](https://docs.microsoft.com/zh-cn/windows/desktop/LearnWin32/module-2--using-com-in-your-windows-program): This sample application shows how to use COM with **<code>__uuidof</code>** operator and **ATL** (Active Template Library) to open a dialog to pick a file and display its filename
   - [D2DCircle](https://docs.microsoft.com/zh-cn/windows/win32/learnwin32/drawing-with-direct2d): This sample application shows how to use Direct2D to draw a circle and the **Direct2D's render loop**