#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tchar.h>
#include <ShObjIdl.h>
#include <atlbase.h>        // Contains the declaration of CComPtr

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
    HRESULT hr = ::CoInitializeEx
    (
        nullptr,
        // A thread that creates a window should use the COINIT_APARTMENTTHREADED
        COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE
    );
    if (SUCCEEDED(hr))
    {
/*
        IFileOpenDialog *pFileOpen = nullptr;
        // Create the FileOpenDialog object
        hr = ::CoCreateInstance
        (
            CLSID_FileOpenDialog,                   // class id
            nullptr,                                // pointer to the aggregate object's IUnknown interface
            CLSCTX_ALL,                             // automatically select the most efficient way
            IID_IFileOpenDialog,                    // interface id
            reinterpret_cast<void**>(&pFileOpen)    // some risk that caused mismatch
        );
        // use __uuidof to avoid to link a static library
        hr = ::CoCreateInstance
        (
            __uuidof(FileOpenDialog),
            nullptr,
            CLSCTX_ALL,
            IID_PPV_ARGS(&pFileOpen)                // We can use IID_PPV_ARGS in QueryInterface
        );
*/
        CComPtr<IFileOpenDialog> pFileOpen;
        // Create the FileOpenDialog object
        hr = pFileOpen.CoCreateInstance(__uuidof(FileOpenDialog));
        if (SUCCEEDED(hr))
        {
            // Show the open dialog box
            hr = pFileOpen->Show(nullptr);
            if (SUCCEEDED(hr))
            {
                // IShellItem *pItem = nullptr;
                // ::CoTaskMemAlloc happened inside IFileDialog::GetResult
                CComPtr<IShellItem> pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    // Get the file name from the dialog box
                    LPWSTR lpszFilePath = nullptr;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &lpszFilePath);

                    if (SUCCEEDED(hr))
                    {
                        // Display the file name to the user
                        ::MessageBeep(MB_OK);
                        MessageBox(nullptr, lpszFilePath, _T("File path"), MB_OK | MB_ICONINFORMATION);
                        ::CoTaskMemFree(lpszFilePath);
                    }
                    // pItem->Release();
                }
            }
            // pFileOpen->Release();
        }
        ::CoUninitialize();
    }
    return EXIT_SUCCESS;
}
