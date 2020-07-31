#pragma once
#include "soapcalcProxy.h"
#include "../../CommonFiles/ISystem.h"

class XXSystemProxy :public ISystemModule, public ILinkService
{
public:
	XXSystemProxy();
	~XXSystemProxy();

	virtual LPVOID QueryInterface(DWORD dwIID);			// 获取其他接口
	virtual void DeleteMe();

	virtual DWORD	ModuleID();							// 模块ID（含接口类别&版本)
	virtual LPCWSTR ModuleName();						// 模块名称
	virtual HICON   ModuleIcon();						// 模块图标
	virtual LPCWSTR ModuleFile();						// 模块文件名
	virtual LPCWSTR ModuleDesc();						// 任务描述

	virtual BOOL Open(LPCWSTR lpcwszSetting);			// 开启模块
	virtual void Close();								// 关闭模块

	virtual BOOL Setup();								// 设置
	virtual void PutSetting(LPCWSTR lpwszSetting);		// 赋给设置
	virtual int  GetSetting(LPWSTR lpwszSetting, int nSizeInChar);	// 读取设置

	virtual string& SendAndReceiveMessage(const string& sendMsg);
private:
	string m_serverAddr;
	calcProxy* m_proxy;
	string m_recMsgStr;
};

