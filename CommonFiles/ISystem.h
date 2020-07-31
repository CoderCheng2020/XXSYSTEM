
#ifndef	 _ISYSTEM_H_
#define  _ISYSTEM_H_
#include <string>
using namespace std;

enum INTERFACE_TYPE
{
	ILINKSERVICE=0,
};


class IInterface
{
public:
	virtual LPVOID QueryInterface(DWORD dwIID) = 0;			// 获取其他接口
	virtual void DeleteMe() = 0;							// 释放对象
};

class ISystem :virtual public IInterface
{
public:
	//virtual void Trace(int nLevel, ISystemModule* pModule, LPCWSTR lpwszEvent) = 0;
};

class ISystemModule :virtual public IInterface
{
public:
	virtual DWORD	ModuleID() = 0;							// 模块ID（含接口类别&版本)
	virtual LPCWSTR ModuleName() = 0;						// 模块名称
	virtual HICON   ModuleIcon() = 0;						// 模块图标
	virtual LPCWSTR ModuleFile() = 0;						// 模块文件名
	virtual LPCWSTR ModuleDesc() = 0;						// 任务描述

	virtual BOOL Open(LPCWSTR lpcwszSetting) = 0;			// 开启模块
	virtual void Close() = 0;								// 关闭模块

	virtual BOOL Setup() = 0;								// 设置
	virtual void PutSetting(LPCWSTR lpwszSetting) = 0;		// 赋给设置
	virtual int  GetSetting(LPWSTR lpwszSetting, int nSizeInChar) = 0;	// 读取设置

};

class ILinkService :virtual public IInterface
{
public:
	virtual string& SendAndReceiveMessage(const string& sendMsg) = 0;
	string m_recMsg;
};

#define CREATEMODULE	"CreateModule"

typedef ISystemModule* WINAPI FNCREATEMODULE(ISystem*, DWORD);
typedef FNCREATEMODULE* LPFNCREATEMODULE;

#endif
