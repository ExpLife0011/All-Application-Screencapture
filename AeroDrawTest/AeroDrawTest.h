
// AeroDrawTest.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CAeroDrawTestApp:
// �� Ŭ������ ������ ���ؼ��� AeroDrawTest.cpp�� �����Ͻʽÿ�.
//

class CAeroDrawTestApp : public CWinAppEx
{
public:
	CAeroDrawTestApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CAeroDrawTestApp theApp;