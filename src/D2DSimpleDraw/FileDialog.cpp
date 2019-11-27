#include "stdafx.h"
#include <CommCtrl.h>
#include <ShObjIdl.h>
#include <atlbase.h>        // Contains the declaration of CComPtr
#include "FileDialog.h"

FileDialog::FileDialog
(
    bool bOpenFileDialog,
    LPCTSTR lpszDefExt/* = nullptr*/,
    LPCTSTR lpszFileName/* = nullptr*/,
    LPCTSTR lpszFilterDesc/* = nullptr*/,
    LPCTSTR lpszFilterExt/* = nullptr*/,
    HWND hWndParent/* = nullptr*/
)
    : m_bValid(false)
{
    HRESULT hr = m_hr = ::CoInitializeEx
    (
        nullptr,
        COINIT_APARTMENTTHREADED
    );

    if (SUCCEEDED(hr))
    {
        CComPtr<IFileDialog> pFileDlg;
        // IFileDialog *pFileDlg = nullptr;
        if (bOpenFileDialog)
            hr = pFileDlg.CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL);
        else
            hr = pFileDlg.CoCreateInstance(CLSID_FileSaveDialog, nullptr, CLSCTX_ALL);

        if (SUCCEEDED(hr))
        {
            hr = pFileDlg->SetTitle(bOpenFileDialog ? L"Open" : L"Save as");
            if (SUCCEEDED(hr))
            {
                DWORD dwFlags;
                hr = pFileDlg->GetOptions(&dwFlags);
                if (SUCCEEDED(hr))
                {
                    hr = pFileDlg->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);
                    if (lpszDefExt && SUCCEEDED(hr))
                    {
#ifdef _UNICODE
                        hr = pFileDlg->SetDefaultExtension(lpszDefExt);
#else
                        // Warning: A2W will call _alloca to request memory allocated on a stack,
                        //      and automatically released outside the scope, this leads to an
                        //      incompatible risk, so it will be better to use variable-length arrays
                        //      in C99 instead especially for Linux-like system
                        hr = pFileDlg->SetDefaultExtension(A2W(lpszDefExt));
#endif
                    }
                    if (!bOpenFileDialog && lpszFileName && SUCCEEDED(hr))
                    {
#ifdef _UNICODE
                        hr = pFileDlg->SetFileName(lpszFileName);
#else
                        hr = pFileDlg->SetFileName(A2W(lpszFileName));
#endif
                    }
                    if (lpszFilterDesc && lpszFilterExt && SUCCEEDED(hr))
                    {
                        const COMDLG_FILTERSPEC rgFilterSpec[] =
                        {
#ifdef _UNICODE
                            { lpszFilterDesc, lpszFilterExt }
#else
                            { A2W(lpszFilterDesc), A2W(lpszFilterExt) }
#endif
                        };
                        hr = pFileDlg->SetFileTypes(1, rgFilterSpec);
                    }
                }
            }

            hr = pFileDlg->Show(hWndParent);
            if (SUCCEEDED(hr))
            {
                CComPtr<IShellItem> pItem;
                hr = pFileDlg->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    // ::CoTaskMemAlloc happened inside IFileDialog::GetDisplayName
                    LPWSTR lpszFilePath = nullptr;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &lpszFilePath);
                    if (SUCCEEDED(hr))
                    {
                        m_bValid = true;
                        ZeroMemory(m_szFilePath, sizeof(m_szFilePath));
#ifdef _UNICODE
                        if (NULL != ::wcscpy_s(m_szFilePath, lpszFilePath))
#else
                        if (NULL != ::strcpy_s(m_szFilePath, W2A(lpszFilePath)))
#endif
                        {
                            m_bValid = false;
                            MessageBox
                            (
                                hWndParent,
                                _T("Error: Can't obtain the full file path!"),
                                bOpenFileDialog ? _T("Open") : _T("Save as"),
                                MB_OK | MB_ICONERROR
                            );
                        }
                        ::CoTaskMemFree(lpszFilePath);
                    }
                }
            }
        }
    }
}

FileDialog::~FileDialog()
{
    if (m_hr)
        ::CoUninitialize();
}

LPCTSTR FileDialog::GetFilePath() const
{
    if (m_bValid)
        return m_szFilePath;

    return nullptr;
}

void FileDialog::OpenBitmap(HWND hWnd)
{
    HANDLE hFile = CreateFile
    (
        m_szFilePath,
        GENERIC_READ,
        NULL,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );
    if (INVALID_HANDLE_VALUE != hFile)
    {
        DWORD dwCount = 0;
        BITMAPFILEHEADER bfh = { };
        BITMAPINFOHEADER bih = { };
        if (FALSE != ::ReadFile(hFile, &bfh, sizeof(BITMAPFILEHEADER), &dwCount, nullptr)
            && FALSE != ::ReadFile(hFile, &bih, sizeof(BITMAPINFOHEADER), &dwCount, nullptr))
        {
            LPBYTE pData = new BYTE[bih.biSizeImage];
            if (pData)
            {
                if (FALSE != ::ReadFile(hFile, pData, bih.biSizeImage, &dwCount, nullptr))
                {
                    HBITMAP hBitmap = ::CreateBitmap
                    (
                        bih.biWidth,
                        bih.biHeight,
                        bih.biPlanes,
                        bih.biBitCount,
                        pData
                    );
                    if (hBitmap)
                    {
                        HDC hDC = ::GetDC(hWnd);
                        if (hDC)
                        {
                            HDC hMemDC = ::CreateCompatibleDC(hDC);
                            if (hMemDC)
                            {
                                HBITMAP hOldBitmap = reinterpret_cast<HBITMAP>(::SelectObject(hMemDC, hBitmap));
                                BOOL bRet = ::BitBlt(hDC, 0, 0, bih.biWidth, bih.biHeight, hMemDC, 0, 0, SRCCOPY);
                                if (hOldBitmap)
                                    hBitmap = reinterpret_cast<HBITMAP>(::SelectObject(hMemDC, hOldBitmap));
                                bRet = ::DeleteDC(hMemDC);
                            }
                            int ret = ::ReleaseDC(hWnd, hDC);
                        }
                        BOOL bRet = ::DeleteObject(hBitmap);
                    }
                }
                delete[] pData;
            }
        }
        ::CloseHandle(hFile);
    }
}

void FileDialog::SaveBitmap(HWND hWnd)
{
    HDC hDC = ::GetDC(hWnd);
    if (hDC)
    {
        HBITMAP hBitmap = reinterpret_cast<HBITMAP>(::GetCurrentObject(hDC, OBJ_BITMAP));
        if (hBitmap)
        {
            BITMAP bitmap = { };
            if (NULL != GetObject(hBitmap, sizeof(BITMAP), &bitmap))
            {
                BITMAPINFOHEADER bih = { };
                bih.biSize = sizeof(BITMAPINFOHEADER);
                bih.biBitCount = bitmap.bmBitsPixel;
                bih.biCompression = BI_RGB;
                bih.biPlanes = bitmap.bmPlanes;
                bih.biWidth = bitmap.bmWidth;
                bih.biHeight = bitmap.bmHeight;
                // In the past, the width per line was aligned on 4 bytes
                // because of SIMD hardware acceleration by CPU for game engine
                bih.biSizeImage = (((bih.biWidth * bih.biBitCount >> 3) + 3) >> 2 << 2) * bih.biHeight;

                LPBYTE pData = new BYTE[bih.biSizeImage];
                if (pData)
                {
                    if (NULL != ::GetBitmapBits(hBitmap, bih.biSizeImage, pData))
                    {
                        BITMAPFILEHEADER bfh = { };
                        bfh.bfType = 0x4D42;
                        bfh.bfSize = bih.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
                        bfh.bfReserved1 = 0;
                        bfh.bfReserved2 = 0;
                        bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

                        HANDLE hFile = CreateFile
                        (
                            m_szFilePath,
                            GENERIC_WRITE,
                            NULL,
                            nullptr,
                            CREATE_ALWAYS,
                            FILE_ATTRIBUTE_NORMAL,
                            nullptr
                        );
                        if (INVALID_HANDLE_VALUE != hFile)
                        {
                            DWORD dwCount = 0;
                            if (FALSE != ::WriteFile(hFile, &bfh, sizeof(BITMAPFILEHEADER), &dwCount, nullptr)
                                && FALSE != ::WriteFile(hFile, &bih, sizeof(BITMAPINFOHEADER), &dwCount, nullptr)
                                && FALSE != ::WriteFile(hFile, pData, bih.biSizeImage, &dwCount, nullptr)
                                && FALSE != ::CloseHandle(hFile))
                            {
                                int nAnswer = MessageBox
                                (
                                    hWnd,
                                    _T("Successfully saved!"),
                                    _T("Save as"),
                                    MB_OK | MB_ICONINFORMATION
                                );
                            }
                        }
                    }
                    delete[] pData;
                }
            }
        }
        int ret = ::ReleaseDC(hWnd, hDC);
    }
}
