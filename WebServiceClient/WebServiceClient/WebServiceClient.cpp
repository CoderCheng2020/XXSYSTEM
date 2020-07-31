// WebServiceClient.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "WebServiceClient.h"
#include "soapcalcProxy.h"
#include "../../CommonFiles/ISystem.h"
#include "XXSystemProxy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


extern "C" ISystemModule* WINAPI CreateModule(ISystem* pSystem, DWORD dwModuleID)
{
	
	//ISystem* pSystem = (ISystem*)pSystem->QueryInterface(IID_IEMSSystem);
	if (pSystem != NULL)
	{
		return new XXSystemProxy();
	}
	

	return NULL;
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

// CWebServiceClientApp

BEGIN_MESSAGE_MAP(CWebServiceClientApp, CWinApp)
END_MESSAGE_MAP()


// CWebServiceClientApp ����

CWebServiceClientApp::CWebServiceClientApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CWebServiceClientApp ����

CWebServiceClientApp theApp;


// CWebServiceClientApp ��ʼ��

BOOL CWebServiceClientApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
