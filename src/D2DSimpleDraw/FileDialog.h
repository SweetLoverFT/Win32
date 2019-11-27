#pragma once

class FileDialog
{
public:
    explicit FileDialog
    (
        bool bOpenFileDialog,
        LPCTSTR lpszDefExt = nullptr,
        LPCTSTR lpszFileName = nullptr,
        LPCTSTR lpszFilterDesc = nullptr,
        LPCTSTR lpszFilterExt = nullptr,
        HWND hWndParent = nullptr
    );
    ~FileDialog();
public:
    LPCTSTR GetFilePath() const;
private:
    bool m_bValid;
    HRESULT m_hr;
    TCHAR m_szFilePath[MAX_PATH];
};

