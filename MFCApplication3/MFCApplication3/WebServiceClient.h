#pragma once
#include "../../CommonFiles/ISystem.h"
#include <winbase.h>

class WebServiceClient : public ISystem, public ILinkService
{
public:
	WebServiceClient();
	~WebServiceClient();
	virtual LPVOID QueryInterface(DWORD dwIID);			// 获取其他接口
	virtual void DeleteMe();							// 释放对象
	string& SendAndReceiveMessage(const string& sendMsg);
	static WebServiceClient* GetInstance();

private:
	static WebServiceClient* m_instance;
	ISystemModule* m_pModule;
	ILinkService* m_pLinkService;

private:
	static ISystemModule* CreateModuleFromDLL(LPCTSTR lpszDll, ISystem* pSystem, DWORD dwModuleID);	// 从DLL文件创建模块

};

