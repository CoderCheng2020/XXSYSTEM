// FriendListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FriendListDlg.h"
#include "afxdialogex.h"

Message FriendListDlg::m_receivedMsg;
std::mutex FriendListDlg::m_mutex;
std::condition_variable FriendListDlg::m_cv;
bool FriendListDlg::m_ready = false;
bool FriendListDlg::m_processed = false;

// FriendListDlg 对话框

IMPLEMENT_DYNAMIC(FriendListDlg, CDialogEx)

FriendListDlg::FriendListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(FriendListDlg::IDD, pParent)
{

}

FriendListDlg::FriendListDlg(CWnd* pParent, UserLoginInfo& loginInfo)
	: CDialogEx(FriendListDlg::IDD, pParent), m_userLoginInfo(loginInfo)
{
	
	m_imgList.Create(16, 16, ILC_MASK, 1, 1);
	m_friendListTree.SetUserLoginInfo(&m_userLoginInfo);
}


FriendListDlg::~FriendListDlg()
{
	for (int i = 0; i < m_friendItemVect.size(); i++)
	{
		delete m_friendItemVect[i];
	}
}

void FriendListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_FRIENDLIST, m_friendListTree);
}


BEGIN_MESSAGE_MAP(FriendListDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL FriendListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	Message message(3, LOGIN, CTS_LOGIN_REQUIRE_FRIEND_LIST, m_userLoginInfo.m_id);
	DataBaseAccessor::GetInstance()->SendMessageStr(message.ToString());
	string userFriendsString;
	//DataBaseAccessor::GetInstance()->ReceiveMessage(userFriendsString);
	
	//receMsg.ParseRawString(userFriendsString);
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		m_cv.wait(lk, []{return m_processed; });
	}

	if (m_receivedMsg.Sequence == 4 && m_receivedMsg.sessionType == LOGIN && m_receivedMsg.sessionChildType == STC_LOGIN_REQUIRE_FRIEND_LIST_REPLY)
	{
		string& friendListString = m_receivedMsg.messageData;
		MSXML2::IXMLDOMDocumentPtr xdDoc(__uuidof(MSXML2::DOMDocument));
		if (xdDoc->loadXML(friendListString.c_str()) == VARIANT_TRUE)
		{
			MSXML2::IXMLDOMNodePtr friendInfoNode;
			friendInfoNode = xdDoc->selectSingleNode(L"//FriendInfo");
			if (friendInfoNode != NULL)
			{
				MSXML2::IXMLDOMNodePtr rowNumberNode = friendInfoNode->selectSingleNode("RowNumber");
				if (rowNumberNode != NULL)
				{
					int rowNumber = _ttoi((LPCTSTR)rowNumberNode->Gettext());
					for (int i = 0; i < rowNumber; i++)
					{
						char numStr[10] = { 0 };
						sprintf_s(numStr, "Row%d", i);
						MSXML2::IXMLDOMNodePtr rowNumberNode = friendInfoNode->selectSingleNode(numStr);
						if (rowNumberNode != NULL)
						{
							FriendItem* pItem = new FriendItem();
							MSXML2::IXMLDOMNodePtr tempFriendInfoNode = rowNumberNode->selectSingleNode("FriendId");
							pItem->m_friendId = tempFriendInfoNode->Gettext();
							tempFriendInfoNode = rowNumberNode->selectSingleNode("NickName");
							pItem->m_nickname = tempFriendInfoNode->Gettext();
							tempFriendInfoNode = rowNumberNode->selectSingleNode("Gender");
							pItem->m_gender = atoi(tempFriendInfoNode->Gettext());
							tempFriendInfoNode = rowNumberNode->selectSingleNode("TelephoneId");
							pItem->m_telephone = tempFriendInfoNode->Gettext();
							tempFriendInfoNode = rowNumberNode->selectSingleNode("Email");
							pItem->m_email = tempFriendInfoNode->Gettext();
							tempFriendInfoNode = rowNumberNode->selectSingleNode("Mood");
							pItem->m_mood = tempFriendInfoNode->Gettext();
							pItem->hParent = NULL;
							pItem->hInsertAfter = NULL;
							pItem->item.mask = TVIF_TEXT;
							pItem->item.pszText = CommonFunctions::GetInstance()->stringToLPWSTR(pItem->m_nickname);//from char* to wchar*,need to be delete manually
							
							//pItem->Create(pItem->item.pszText, 0, CRect(0, 0, 200, 100), GetDlgItem(IDC_TREE_FRIENDLIST), 0x11);
							
							CBitmap     bitmap;
							
							bitmap.LoadBitmap(IDB_FRIENDITEM);
							m_imgList.Add(&bitmap, (COLORREF)0xFFFFFF);
							//bitmap.DeleteObject();
							m_friendListTree.SetImageList(&m_imgList, TVSIL_NORMAL);
							m_friendItemVect.push_back(pItem);
							//HTREEITEM hFriendItem = m_friendListTree.InsertItem(pItem);
							m_friendListTree.InsertItem(pItem);
							m_friendListTree.SetItemHeight(50);
							//m_friendListTree.SetItemImage(hFriendItem, IDB_FRIENDITEM,IDB_FRIENDITEMSELECTED);

							/*
							LPTVINSERTSTRUCTW pItem = new TVINSERTSTRUCTW();
							pItem->hParent = NULL;
							pItem->hInsertAfter = NULL;
							pItem->item.mask = TVIF_TEXT;
							pItem->item.pszText = _T("节点一");
							*/
							//m_friendListTree.InsertItem(pItem);
						}
					}
				}
				else
				{
					AfxMessageBox(_T("Miss rowNumber node!"));

				}
			}
		}
	}


/*	for (int i = 0; i < m_friendItemVect.size(); i++)
	{
		//
		HTREEITEM hCountry = m_friendListTree.InsertItem(m_friendItemVect[i]);
	}
*/
	CImageList m_imgList;
	CImageList m_imgState;

	/*
	//m_imgList.Create(IDB_BITMAP_LIST, 16, 1, RGB(255, 255, 255));//创建图标列表 为连续的16*16图标
	//m_imgState.Create(IDB_BITMAP_STATE,16, 1, RGB(255,255,255));//创建状态图标
	m_friendListTree.SetImageList(&m_imgList, TVSIL_NORMAL);//选择与非选择
	//m_friendListTree.SetImageList(&m_imgState,TVSIL_STATE);//用户定义

	HTREEITEM hItem1A = m_friendListTree.InsertItem(_T("根部"), 0, 0);

	HTREEITEM hItem2_1B = m_friendListTree.InsertItem(_T("根上一"), 1, 2, hItem1A, TVI_LAST);
	m_friendListTree.InsertItem(_T("根上二"), 1, 2, hItem2_1B);
	m_friendListTree.InsertItem(_T("根上二"), 1, 2, hItem2_1B);

	HTREEITEM hItem2_2B = m_friendListTree.InsertItem(_T("根上一"), 1, 2, hItem1A, TVI_LAST);
	m_friendListTree.InsertItem(_T("根上一"), 1, 2, hItem2_2B);
	m_friendListTree.InsertItem(_T("根上一"), 1, 2, hItem2_2B);

	m_friendListTree.InsertItem(_T("根上一"), 1, 2, hItem1A, TVI_LAST);
	m_friendListTree.InsertItem(_T("根上一"), 1, 2, hItem1A, TVI_LAST);

	//设置显示风格
	m_friendListTree.SetBkColor(RGB(220, 200, 220));//背景颜色
	m_friendListTree.Expand(hItem1A, TVE_EXPAND);//根部展开
	DWORD dwStyle = GetWindowLong(m_friendListTree.m_hWnd, GWL_STYLE);//获得树的信息
	dwStyle |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;//设置风格
	::SetWindowLong(m_friendListTree.m_hWnd, GWL_STYLE, dwStyle);
	m_friendListTree.ShowWindow(SW_SHOW);
	*/

	m_friendListTree.SetBkColor(RGB(220, 200, 220));//背景颜色
	//m_friendListTree.Expand(hItem1A, TVE_EXPAND);//根部展开
	DWORD dwStyle = GetWindowLong(m_friendListTree.m_hWnd, GWL_STYLE);//获得树的信息
	dwStyle |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;//设置风格
	::SetWindowLong(m_friendListTree.m_hWnd, GWL_STYLE, dwStyle);
	m_friendListTree.ShowWindow(SW_SHOW);
	return TRUE;
}

// FriendListDlg 消息处理程序
void  FriendListDlg::DealWithReceiveMessageFunc(Message& msg)
{
	std::unique_lock<std::mutex> lk(m_mutex);
	m_receivedMsg = msg;
	m_processed = true;
	lk.unlock();
	m_cv.notify_one();
}