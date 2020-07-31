#pragma once
#include "soapcalcProxy.h"
#include "../../CommonFiles/ISystem.h"

class XXSystemProxy :public ISystemModule, public ILinkService
{
public:
	XXSystemProxy();
	~XXSystemProxy();

	virtual LPVOID QueryInterface(DWORD dwIID);			// ��ȡ�����ӿ�
	virtual void DeleteMe();

	virtual DWORD	ModuleID();							// ģ��ID�����ӿ����&�汾)
	virtual LPCWSTR ModuleName();						// ģ������
	virtual HICON   ModuleIcon();						// ģ��ͼ��
	virtual LPCWSTR ModuleFile();						// ģ���ļ���
	virtual LPCWSTR ModuleDesc();						// ��������

	virtual BOOL Open(LPCWSTR lpcwszSetting);			// ����ģ��
	virtual void Close();								// �ر�ģ��

	virtual BOOL Setup();								// ����
	virtual void PutSetting(LPCWSTR lpwszSetting);		// ��������
	virtual int  GetSetting(LPWSTR lpwszSetting, int nSizeInChar);	// ��ȡ����

	virtual string& SendAndReceiveMessage(const string& sendMsg);
private:
	string m_serverAddr;
	calcProxy* m_proxy;
	string m_recMsgStr;
};

