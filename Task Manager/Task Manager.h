
// Task Manager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTaskManagerApp: 
// �йش����ʵ�֣������ Task Manager.cpp
//

class CTaskManagerApp : public CWinApp
{
public:
	CTaskManagerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTaskManagerApp theApp;