#pragma once
#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif
#include "resource.h"		
class CFiveInARowApp : public CWinApp
{
public:
	CFiveInARowApp();
public:
	virtual BOOL InitInstance();
    DECLARE_MESSAGE_MAP()
};
extern CFiveInARowApp theApp;