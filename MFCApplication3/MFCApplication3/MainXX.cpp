// MainXX.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MainXX.h"
#include "afxdialogex.h"



// MAINXX.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MAINXX.h"
#include "afxdialogex.h"


// MAINXX 对话框

IMPLEMENT_DYNAMIC(MAINXX, CDialogEx)

MAINXX::MAINXX(CWnd* pParent /*=NULL*/)
	: CDialogEx(MAINXX::IDD, pParent)
{

}

MAINXX::~MAINXX()
{
	if (m_pFriendListDlg != NULL)
	{
		delete m_pFriendListDlg;
	}
}
BOOL MAINXX::OnInitDialog()
{
	CDialog::OnInitDialog();
#pragma region
	m_friendAndGroupTab.InsertItem(0, _T("Friends"));
	m_friendAndGroupTab.InsertItem(1, _T("Groups"));
	m_friendAndGroupTab.InsertItem(2, _T("Moment"));

	CRect friendListRect;
	GetClientRect(&friendListRect);
	m_friendAndGroupTab.GetWindowRect(&friendListRect);
	ScreenToClient(&friendListRect);
	friendListRect.left = 0;
	friendListRect.bottom -= 1;
	friendListRect.right -= 1;
	friendListRect.top = 20;
	m_pFriendListDlg->Create(FriendListDlg::IDD, GetDlgItem(IDC_TAB_FRIGRP));
	m_pFriendListDlg->MoveWindow(friendListRect);
	m_pFriendListDlg->ShowWindow(SW_SHOW);
#pragma endregion
	return TRUE;
}
void MAINXX::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ED_MOOD, m_userMood);
	DDX_Control(pDX, IDC_CB_ONLINESTATUS, m_CB_userOnlineStatus);
	DDX_Control(pDX, IDC_BT_USERICON, m_userIcon);
	DDX_Control(pDX, IDC_TAB_FRIGRP, m_friendAndGroupTab);
}


BEGIN_MESSAGE_MAP(MAINXX, CDialogEx)
	ON_BN_CLICKED(IDC_BT_USERICON, &MAINXX::OnBnClickedBtUsericon)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_FRIGRP, &MAINXX::OnTcnSelchangeTabFrigrp)
END_MESSAGE_MAP()


// MAINXX 消息处理程序


void MAINXX::OnBnClickedBtUsericon()
{
	// TODO:  在此添加控件通知处理程序代码
	CString filePath;
	char szFilter[] = { "All Files(*.*)|*.*||" };
	CString filterStr(_T("All Files(*.*)|*.*||"));
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filterStr, NULL);

	if (dlg.DoModal() == IDOK)
	{
		filePath = dlg.GetPathName();
		HBITMAP userIcon = (HBITMAP)LoadImage(AfxGetInstanceHandle(), filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		//CBitmap bitmap;
		//bitmap.Attach(userIcon);
		m_userIcon.SetBitmap(userIcon);
		m_userIcon.UpdateData();
		//lpszFileName = (LPCTSTR)filePath;  //lpszFileName是一个全局变量
	}
	else
	{

	}
	
}


void MAINXX::OnTcnSelchangeTabFrigrp(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	int curSelect = 0;// m_friendAndGroupTab.GetCurSel();
	if (curSelect == FRIENDS_PAGE)
	{
		if (m_pFriendListDlg == NULL)
		{
			/*m_pFriendListDlg = new FriendListDlg(this, m_userInfo);
			CRect friendListRect;
			m_friendAndGroupTab.GetWindowRect(friendListRect);
			m_pFriendListDlg->MoveWindow(friendListRect);
			m_pFriendListDlg->ShowWindow(SW_SHOW);*/
		}
		//m_pFriendListDlg->ShowWindow(SW_SHOW);
	}
	else if (curSelect == GROUP_PAGE)
	{

	}
	*pResult = 0;
}
