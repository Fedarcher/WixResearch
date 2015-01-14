//***********************************************************
//** This source code is provided "AS IS" with no warranties, 
//** and confers no rights.
//***********************************************************

#include <tchar.h>
#include <windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include "msiquery.h"
#include "strsafe.h"

// Функция для поиска дочернего окна по классу окна.
BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
 TCHAR szBuffer[100] = {0};

 GetClassName(hWnd, (LPTSTR)&szBuffer, _countof(szBuffer));

 if(_wcsicmp(szBuffer, (_T("RichEdit20W"))) == 0)
 {  
  // Вернуть хэндл на окно и остановить перебор дочерних окон.
  *(HWND*)lParam = hWnd;

  return FALSE;
 }

 return TRUE;
}

UINT __stdcall BrowseForFile(MSIHANDLE hInstall)
{
 long lErrMsg = 0;

 TCHAR szOriginalPath[MAX_PATH] = {0};
 TCHAR szDialogFilter[MAX_PATH] = {0};
 TCHAR szIndex[8] = {0};

 DWORD cchValue;

 // Получить значение BFF_PATH_TO_FILE
 cchValue = _countof(szOriginalPath);
 MsiGetProperty(hInstall, TEXT("BFF_PATH_TO_FILE"), szOriginalPath, &cchValue);

 // Получить значение BFF_FILE_DIALOG_FILTER
 cchValue = _countof(szDialogFilter);
 MsiGetProperty(hInstall, TEXT("BFF_FILE_DIALOG_FILTER"), szDialogFilter, &cchValue);

 size_t nFilterLength = wcslen(szDialogFilter);

 for(size_t i = 0; i < nFilterLength; ++i)
 {
  if(szDialogFilter[i] == '|')
  {
   szDialogFilter[i] = '\0';
  }
 }

 OPENFILENAME ofn = {0};

 // Инициализация структуры OPENFILENAME.
 ofn.lStructSize = sizeof(ofn);
 ofn.hwndOwner = GetForegroundWindow();
 ofn.lpstrFile = szOriginalPath;
 ofn.nMaxFile = _countof(szOriginalPath);
 ofn.lpstrFilter = szDialogFilter;
 ofn.nFilterIndex = 0;
 ofn.lpstrFileTitle = NULL;
 ofn.nMaxFileTitle = 0;
 ofn.lpstrInitialDir = NULL;

 if (GetOpenFileName(&ofn))
 {
  // Установить значение переменной.
  MsiSetProperty(hInstall, TEXT("BFF_PATH_TO_FILE"), szOriginalPath);

	HWND hInstallerWnd = FindWindow(_T("MsiDialogCloseClass"), NULL);

	if(hInstallerWnd != NULL)
	{
		HWND hWndChild = NULL;

		EnumChildWindows(hInstallerWnd, EnumChildProc, (LPARAM)&hWndChild);

		if(hWndChild != NULL) 
		{
			SendMessage(hWndChild, WM_SETTEXT, 0, (LPARAM)szOriginalPath);
		}
	}
 }

 return ERROR_SUCCESS;
}
