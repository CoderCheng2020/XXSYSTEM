// TinyXml.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "TinyXml.h"
#include "tinyxmlImpliment.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif




extern "C" TiXmlDocument* WINAPI CreateTiXmlDocument()
{
	return new TiXmlDocument();
}

//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CTinyXmlApp

BEGIN_MESSAGE_MAP(CTinyXmlApp, CWinApp)
END_MESSAGE_MAP()


// CTinyXmlApp ����

CTinyXmlApp::CTinyXmlApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CTinyXmlApp ����

CTinyXmlApp theApp;


// CTinyXmlApp ��ʼ��

BOOL CTinyXmlApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
