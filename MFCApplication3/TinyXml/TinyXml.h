// TinyXml.h : TinyXml DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTinyXmlApp
// �йش���ʵ�ֵ���Ϣ������� TinyXml.cpp
//

class CTinyXmlApp : public CWinApp
{
public:
	CTinyXmlApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
