
// MFCDrawer.h: основной файл заголовка для приложения MFCDrawer
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CMFCDrawerApp:
// Сведения о реализации этого класса: MFCDrawer.cpp
//

class CMFCDrawerApp : public CWinApp
{
public:
	CMFCDrawerApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCDrawerApp theApp;
