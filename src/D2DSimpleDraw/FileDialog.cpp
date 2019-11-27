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
