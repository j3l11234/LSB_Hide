
// LSBhide.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLSBhideApp: 
// �йش����ʵ�֣������ LSBhide.cpp
//

class CLSBhideApp : public CWinApp
{
public:
	CLSBhideApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLSBhideApp theApp;