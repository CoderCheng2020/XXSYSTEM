// WebServiceClient.h : WebServiceClient DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWebServiceClientApp
// �йش���ʵ�ֵ���Ϣ������� WebServiceClient.cpp
//

class CWebServiceClientApp : public CWinApp
{
public:
	CWebServiceClientApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
