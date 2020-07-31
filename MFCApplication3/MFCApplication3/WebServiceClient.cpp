#include "stdafx.h"
#include "WebServiceClient.h"

WebServiceClient* WebServiceClient::m_instance = NULL;

WebServiceClient::WebServiceClient()
{
	m_pModule = CreateModuleFromDLL(_T("WebServiceClient.dll"), this, 0);
	if (m_pModule != NULL)
	{
		m_pLinkService = (ILinkService*)m_pModule->QueryInterface(ILINKSERVICE);
	}
}
string& WebServiceClient::SendAndReceiveMessage(const string& sendMsg)
{
	
	return m_recMsg = m_pLinkService->SendAndReceiveMessage(sendMsg);
	
}

WebServiceClient::~WebServiceClient()
{
	if (m_instance != NULL)
	{
		delete m_instance;
	}
}

WebServiceClient* WebServiceClient::GetInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new WebServiceClient();
	}
	return m_instance;
}

LPVOID WebServiceClient::QueryInterface(DWORD dwIID)			// 获取其他接口
{
	return NULL;
}
void WebServiceClient::DeleteMe()							// 释放对象
{
	delete this;
}


ISystemModule* WebServiceClient::CreateModuleFromDLL(LPCTSTR lpszDll, ISystem* pSystem, DWORD dwModuleID)
{
	ISystemModule* pModule = NULL;

	HMODULE hModule = LoadLibrary(CT2W(lpszDll));
	if (hModule != NULL)
	{
		LPFNCREATEMODULE CreateModule = (LPFNCREATEMODULE)GetProcAddress(hModule, CREATEMODULE);
		if (CreateModule != NULL)
		{
			pModule = CreateModule(pSystem, dwModuleID);
		}

		//FreeLibrary(hModule);
	}

	return pModule;
}