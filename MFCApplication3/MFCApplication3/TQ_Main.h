#pragma once


// TQ_Main �Ի���

class TQ_Main : public CDialogEx
{
	DECLARE_DYNAMIC(TQ_Main)

public:
	TQ_Main(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TQ_Main();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
