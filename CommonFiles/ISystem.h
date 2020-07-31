
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
	virtual LPVOID QueryInterface(DWORD dwIID) = 0;			// ��ȡ�����ӿ�
	virtual void DeleteMe() = 0;							// �ͷŶ���
};

class ISystem :virtual public IInterface
{
public:
	//virtual void Trace(int nLevel, ISystemModule* pModule, LPCWSTR lpwszEvent) = 0;
};

class ISystemModule :virtual public IInterface
{
public:
	virtual DWORD	ModuleID() = 0;							// ģ��ID�����ӿ����&�汾)
	virtual LPCWSTR ModuleName() = 0;						// ģ������
	virtual HICON   ModuleIcon() = 0;						// ģ��ͼ��
	virtual LPCWSTR ModuleFile() = 0;						// ģ���ļ���
	virtual LPCWSTR ModuleDesc() = 0;						// ��������

	virtual BOOL Open(LPCWSTR lpcwszSetting) = 0;			// ����ģ��
	virtual void Close() = 0;								// �ر�ģ��

	virtual BOOL Setup() = 0;								// ����
	virtual void PutSetting(LPCWSTR lpwszSetting) = 0;		// ��������
	virtual int  GetSetting(LPWSTR lpwszSetting, int nSizeInChar) = 0;	// ��ȡ����

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
