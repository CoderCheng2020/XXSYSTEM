// TQ_Main.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "TQ_Main.h"
#include "afxdialogex.h"


// TQ_Main �Ի���

IMPLEMENT_DYNAMIC(TQ_Main, CDialogEx)

TQ_Main::TQ_Main(CWnd* pParent /*=NULL*/)
	: CDialogEx(TQ_Main::IDD, pParent)
{

	EnableAutomation();

}

TQ_Main::~TQ_Main()
{
}

void TQ_Main::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void TQ_Main::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TQ_Main, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(TQ_Main, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_ITQ_Main ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {3DBC1CB8-2618-4BFF-AFD5-096F807BBCD2}
static const IID IID_ITQ_Main =
{ 0x3DBC1CB8, 0x2618, 0x4BFF, { 0xAF, 0xD5, 0x9, 0x6F, 0x80, 0x7B, 0xBC, 0xD2 } };

BEGIN_INTERFACE_MAP(TQ_Main, CDialogEx)
	INTERFACE_PART(TQ_Main, IID_ITQ_Main, Dispatch)
END_INTERFACE_MAP()


// TQ_Main ��Ϣ�������
