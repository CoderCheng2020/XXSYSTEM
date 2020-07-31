
// MFCApplication3Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "Resource.h"
#include "CommonVariables.h"
#include <mutex>
#include <condition_variable>
#include "IXXSystem.h"



// CMFCApplication3Dlg �Ի���
class CMFCApplication3Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication3Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	static void DealWithReceiveMessageFunc(Message& msg);
// �Ի�������
	enum { IDD = IDD_MFCAPPLICATION3_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	static std::mutex m_mutex;
	static std::condition_variable m_cv;
	static bool m_ready;
	static bool m_processed;
	

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
