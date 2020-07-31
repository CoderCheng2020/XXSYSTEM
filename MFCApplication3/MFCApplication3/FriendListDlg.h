#pragma once
#include "afxcmn.h"
#include "CommonVariables.h"
#include "DataBaseAccessor.h"
#include "FriendItem.h"
#include "ViewTree.h"
#include "IXXSystem.h"

// FriendListDlg 对话框

class FriendListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FriendListDlg)

public:
	FriendListDlg(CWnd* pParent = NULL);   // 标准构造函数
	FriendListDlg(CWnd* pParent, UserLoginInfo& loginInfo);
	virtual ~FriendListDlg();
	static void DealWithReceiveMessageFunc(Message& msg);

// 对话框数据
	enum { IDD = IDD_DLG_FRIEND };

protected:
	static Message m_receivedMsg;
	UserLoginInfo* m_pUserInfo;
	CImageList m_imgList;
	static std::mutex m_mutex;
	static std::condition_variable m_cv;
	static bool m_ready;
	static bool m_processed;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	vector<FriendItem*> m_friendItemVect;
	CViewTree m_friendListTree;
	UserLoginInfo m_userLoginInfo;
};
