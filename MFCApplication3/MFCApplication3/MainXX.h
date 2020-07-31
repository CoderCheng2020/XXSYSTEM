#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "FriendListDlg.h"
#include "CommonVariables.h"

// MainXX 对话框
#define IDI_ICON1 130
#define IDI_ICON2 131

enum TAB_FRIANDGRP
{
	FRIENDS_PAGE = 0,
	GROUP_PAGE
};

// MAINXX 对话框

class MAINXX : public CDialogEx
{
	DECLARE_DYNAMIC(MAINXX)

public:
	MAINXX(CWnd* pParent = NULL);   // 标准构造函数
	MAINXX(UserLoginInfo* pUserInfo, CWnd* pParent = NULL) :CDialogEx(MAINXX::IDD, pParent), m_userInfo(*pUserInfo), m_pFriendListDlg(NULL)
	{
		m_pFriendListDlg = new FriendListDlg(this, m_userInfo);
		
	}
	virtual ~MAINXX();

// 对话框数据
	enum { IDD = IDD_MAINXX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	UserLoginInfo m_userInfo;
	CEdit m_userMood;
	CComboBox m_CB_userOnlineStatus;
	CButton m_userIcon;
	afx_msg void OnBnClickedBtUsericon();
	CTabCtrl m_friendAndGroupTab;
	afx_msg void OnTcnSelchangeTabFrigrp(NMHDR *pNMHDR, LRESULT *pResult);
	FriendListDlg* m_pFriendListDlg;
	//FriendListDlg m_friendListDlg;
};
