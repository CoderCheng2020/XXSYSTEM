#pragma once


// TQ_Main 对话框

class TQ_Main : public CDialogEx
{
	DECLARE_DYNAMIC(TQ_Main)

public:
	TQ_Main(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TQ_Main();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
