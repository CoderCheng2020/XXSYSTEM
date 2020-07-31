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


LPVOID XXSystemProxy::QueryInterface(DWORD dwIID)			// 获取其他接口
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


DWORD	XXSystemProxy::ModuleID()							// 模块ID（含接口类别&版本)
{
	return 0;
}
LPCWSTR XXSystemProxy::ModuleName()						// 模块名称
{
	return _T("XXSystemProxy");
}
HICON   XXSystemProxy::ModuleIcon()						// 模块图标
{
	return NULL;
}
LPCWSTR XXSystemProxy::ModuleFile()						// 模块文件名
{
	return _T("WebServiceClient.dll");
}
LPCWSTR XXSystemProxy::ModuleDesc()						// 任务描述
{
	return _T("This is the web service transport module.");
}

BOOL XXSystemProxy::Open(LPCWSTR lpcwszSetting)			// 开启模块
{
	return TRUE;
}
void XXSystemProxy::Close()								// 关闭模块
{

}

BOOL XXSystemProxy::Setup()								// 设置
{
	return TRUE;
}

void XXSystemProxy::PutSetting(LPCWSTR lpwszSetting)		// 赋给设置
{

}

int  XXSystemProxy::GetSetting(LPWSTR lpwszSetting, int nSizeInChar)	// 读取设置
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


