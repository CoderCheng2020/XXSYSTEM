#pragma once
#include "afxcmn.h"
#include "FriendItem.h"
#include "ConversationDlg.h"

#include <map>
using namespace std;

class CViewTree :
	public CTreeCtrl
{
public:
	CViewTree();
	virtual ~CViewTree();
	FriendItem* InsertItem(FriendItem* pItem);
	void SetUserLoginInfo(UserLoginInfo* pUserInfo)
	{
		m_pUserInfo = pUserInfo;
	}
	afx_msg void OnDblClkTree(NMHDR* pNMHDR, LRESULT* pResult);//双击事件
	afx_msg void OnClkTree(NMHDR* pNMHDR, LRESULT* pResult);//单击事件
	// 重写
protected:
	UserLoginInfo* m_pUserInfo;
	map<HTREEITEM, FriendItem*> m_internalMap;
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
protected:
	DECLARE_MESSAGE_MAP()
};

