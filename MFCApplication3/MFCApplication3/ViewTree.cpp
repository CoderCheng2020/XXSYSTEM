#include "stdafx.h"
#include "ViewTree.h"


CViewTree::CViewTree()
{
}


CViewTree::~CViewTree()
{
}
BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CViewTree::OnDblClkTree)
	ON_NOTIFY_REFLECT(NM_CLICK, &CViewTree::OnClkTree)
END_MESSAGE_MAP()

FriendItem* CViewTree::InsertItem(FriendItem* pItem)
{
	HTREEITEM hItem = __super::InsertItem((TVINSERTSTRUCTW*)pItem);
	m_internalMap[hItem] = pItem;
	return pItem;
}

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}

void CViewTree::OnDblClkTree(NMHDR* pNMHDR, LRESULT* pResult)
{

	HTREEITEM hTreeItem = GetSelectedItem();
	
	FriendItem* pItem = m_internalMap[hTreeItem];

	ConversationDlg converDlg(m_pUserInfo, pItem);
	converDlg.DoModal();

	//FriendItem* pFriendItem = dynamic_cast<FriendItem*>(pData);
	//以GetItemText()函数为例： 
	/*CString S1 = GetItemText(hTreeItem);
	S1.Format(_T("You have selected %d"), pData);
	AfxMessageBox(S1);*/

	*pResult = 0;

}

void CViewTree::OnClkTree(NMHDR* pNMHDR, LRESULT* pResult)
{

	//HTREEITEM hTreeItem = GetSelectedItem();
	//以GetItemText()函数为例： 
	//CString S1 = GetItemText(hTreeItem);
	//AfxMessageBox(_T("You have selected ") + S1);

	*pResult = 0;

}
