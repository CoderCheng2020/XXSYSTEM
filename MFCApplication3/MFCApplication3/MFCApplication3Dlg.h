
// MFCApplication3Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "Resource.h"
#include "CommonVariables.h"
#include <mutex>
#include <condition_variable>
#include "IXXSystem.h"



// CMFCApplication3Dlg 对话框
class CMFCApplication3Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication3Dlg(CWnd* pParent = NULL);	// 标准构造函数
	static void DealWithReceiveMessageFunc(Message& msg);
// 对话框数据
	enum { IDD = IDD_MFCAPPLICATION3_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	static std::mutex m_mutex;
	static std::condition_variable m_cv;
	static bool m_ready;
	static bool m_processed;
	

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CEdit m_EditAccount;
	CEdit m_EditPwd;
public:
	afx_msg void OnBnClickedOk();
	static CString m_EditAccountStr;

protected:
	static bool m_bShutdownDialog;
	CString m_EditPWDStr;

};
