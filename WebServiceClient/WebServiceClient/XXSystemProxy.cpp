#include "stdafx.h"
#include "XXSystemProxy.h"

#define SERVER_IP "192.168.3.14"
#define SERVER_PORT "10010"

XXSystemProxy::XXSystemProxy() :m_proxy(NULL)
{
	m_serverAddr = "http://" + string(SERVER_IP) + ":" + SERVER_PORT;
	
	m_proxy = new calcProxy();
	m_proxy->soap_endpoint = m_serverAddr.c_str();
	
}


XXSystemProxy::~XXSystemProxy()
{
	if (m_proxy != NULL)
	{
		delete m_proxy;
	}
}


LPVOID XXSystemProxy::QueryInterface(DWORD dwIID)			// ��ȡ�����ӿ�
{
	if (dwIID == ILINKSERVICE)
	{
		return static_cast<ILinkService*>(this);
	}
	return NULL;
}

void XXSystemProxy::DeleteMe()
{
	return;
}


DWORD	XXSystemProxy::ModuleID()							// ģ��ID�����ӿ����&�汾)
{
	return 0;
}
LPCWSTR XXSystemProxy::ModuleName()						// ģ������
{
	return _T("XXSystemProxy");
}
HICON   XXSystemProxy::ModuleIcon()						// ģ��ͼ��
{
	return NULL;
}
LPCWSTR XXSystemProxy::ModuleFile()						// ģ���ļ���
{
	return _T("WebServiceClient.dll");
}
LPCWSTR XXSystemProxy::ModuleDesc()						// ��������
{
	return _T("This is the web service transport module.");
}

BOOL XXSystemProxy::Open(LPCWSTR lpcwszSetting)			// ����ģ��
{
	return TRUE;
}
void XXSystemProxy::Close()								// �ر�ģ��
{

}

BOOL XXSystemProxy::Setup()								// ����
{
	return TRUE;
}

void XXSystemProxy::PutSetting(LPCWSTR lpwszSetting)		// ��������
{

}

int  XXSystemProxy::GetSetting(LPWSTR lpwszSetting, int nSizeInChar)	// ��ȡ����
{
	return 0;
}

string& XXSystemProxy::SendAndReceiveMessage(const string& sendMsg)
{
	char* pRece = NULL;
	ASSERT(m_proxy != NULL);

	m_proxy->SendAndReceiveMessage(const_cast<char*>(sendMsg.c_str()), &pRece);
	if (pRece != NULL)
	{
		m_recMsgStr = string(pRece);
	}
	
	return m_recMsgStr;
}


