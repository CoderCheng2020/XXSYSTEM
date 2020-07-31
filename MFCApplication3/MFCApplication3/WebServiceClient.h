#pragma once
#include "../../CommonFiles/ISystem.h"
#include <winbase.h>

class WebServiceClient : public ISystem, public ILinkService
{
public:
	WebServiceClient();
	~WebServiceClient();
	virtual LPVOID QueryInterface(DWORD dwIID);			// ��ȡ�����ӿ�
	virtual void DeleteMe();							// �ͷŶ���
	string& SendAndReceiveMessage(const string& sendMsg);
	static WebServiceClient* GetInstance();

private:
	static WebServiceClient* m_instance;
	ISystemModule* m_pModule;
	ILinkService* m_pLinkService;

private:
	static ISystemModule* CreateModuleFromDLL(LPCTSTR lpszDll, ISystem* pSystem, DWORD dwModuleID);	// ��DLL�ļ�����ģ��

};

