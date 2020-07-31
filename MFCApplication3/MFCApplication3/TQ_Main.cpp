// TQ_Main.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "TQ_Main.h"
#include "afxdialogex.h"


// TQ_Main 对话框

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
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

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

// 注意: 我们添加 IID_ITQ_Main 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {3DBC1CB8-2618-4BFF-AFD5-096F807BBCD2}
static const IID IID_ITQ_Main =
{ 0x3DBC1CB8, 0x2618, 0x4BFF, { 0xAF, 0xD5, 0x9, 0x6F, 0x80, 0x7B, 0xBC, 0xD2 } };

BEGIN_INTERFACE_MAP(TQ_Main, CDialogEx)
	INTERFACE_PART(TQ_Main, IID_ITQ_Main, Dispatch)
END_INTERFACE_MAP()


// TQ_Main 消息处理程序
