// ConversationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ConversationDlg.h"
#include "afxdialogex.h"


// ConversationDlg 对话框
mutex ConversationDlg::m_mutex;
MaosenQueue<Message> ConversationDlg::m_receivedMsgQueue;
bool ConversationDlg::m_bExitGetMsgFSharedQueueThread = false;

IMPLEMENT_DYNAMIC(ConversationDlg, CDialogEx)

ConversationDlg::ConversationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ConversationDlg::IDD, pParent)
{

}

ConversationDlg::ConversationDlg(UserLoginInfo* pUserInfo, FriendItem* pFriendItem, CWnd* pParent) : CDialogEx(ConversationDlg::IDD, pParent), m_pUserInfo(pUserInfo), m_friendItem(*pFriendItem), m_sequence(0)
{
	m_pGetMsgFromSharedQueueThread = new thread(GetReceiveMessageFromSharedQueue, this);
}


ConversationDlg::~ConversationDlg()
{
	m_bExitGetMsgFSharedQueueThread = true;
	Sleep(1000);
	if (m_pGetMsgFromSharedQueueThread != NULL)
	{
		//delete m_pGetMsgFromSharedQueueThread;
	}
}

void ConversationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ED_CONVERSATION, m_conversationEdit);
	DDX_Control(pDX, IDC_ED_SENDINGAREA, m_sendingAreaEdit);
}


BEGIN_MESSAGE_MAP(ConversationDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ConversationDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ConversationDlg 消息处理程序


void ConversationDlg::OnBnClickedOk()
{
	UpdateData();
	CString inputStr;
	m_sendingAreaEdit.GetWindowTextW(inputStr);
	Message message;
	message.Sequence = m_sequence+1;
	message.sessionType = CONVERSATION;
	message.sessionChildType = CTS_START_CONVERSATION;
	message.messageData = EncodeConversation(CommonFunctions::GetInstance()->CStringToSTLstring(inputStr));
	DataBaseAccessor::GetInstance()->SendMessageStr(message.ToString());
	//CDialogEx::OnOK()
}

string& ConversationDlg::EncodeConversation(string& inputStr)
{
	MSXML2::IXMLDOMDocumentPtr xdDoc(__uuidof(MSXML2::DOMDocument));
	if (inputStr != "")
	{
		if (xdDoc != NULL)
		{
			MSXML2::IXMLDOMNodePtr xnRoot;
			xnRoot = xdDoc->appendChild(xdDoc->createElement(_T("Conversation")));
			if (xnRoot != NULL)
			{
				CString valueStr;
				valueStr = CommonFunctions::GetInstance()->stringToLPWSTR(m_pUserInfo->m_id);
				xnRoot->appendChild(xdDoc->createElement(_T("HostId")))->Puttext((LPCTSTR)valueStr);
				valueStr = CommonFunctions::GetInstance()->stringToLPWSTR(m_friendItem.m_friendId);
				xnRoot->appendChild(xdDoc->createElement(_T("FriendId")))->Puttext((LPCTSTR)valueStr);
				valueStr = CommonFunctions::GetInstance()->stringToLPWSTR(inputStr);
				xnRoot->appendChild(xdDoc->createElement(_T("MessagePayload")))->Puttext((LPCTSTR)valueStr);
			}
		}
		return CommonFunctions::GetInstance()->WCharToMByte((LPCWSTR)xdDoc->xml);
	}
}

bool ConversationDlg::JudgeIsCurrentFriendsMessage(Message& msg, string&friendId, string& contentStr)
{
	bool bCurr = false;
	MSXML2::IXMLDOMDocumentPtr xdDoc(__uuidof(MSXML2::DOMDocument));
	if (xdDoc != NULL)
	{
		if (xdDoc->loadXML(msg.messageData.c_str()) == VARIANT_TRUE)
		{
			MSXML2::IXMLDOMNodePtr conversationNode;
			conversationNode = xdDoc->selectSingleNode(L"//Conversation");
			if (conversationNode != NULL)
			{
				MSXML2::IXMLDOMNodePtr infoNode = conversationNode->selectSingleNode(L"FriendId");
				if (infoNode != NULL)
				{
					string friendIdStr = CommonFunctions::GetInstance()->WCharToMByte((LPCTSTR)infoNode->Gettext());
					if (friendIdStr == m_pUserInfo->m_id)
					{
						bCurr = true;
						//return true;
					}
				}
				if (bCurr)
				{
					infoNode = conversationNode->selectSingleNode(L"HostId");
					if (infoNode != NULL)
					{
						friendId = CommonFunctions::GetInstance()->WCharToMByte((LPCTSTR)infoNode->Gettext());
					}

					infoNode = conversationNode->selectSingleNode(L"Content");
					if (infoNode != NULL)
					{
						contentStr = CommonFunctions::GetInstance()->WCharToMByte((LPCTSTR)infoNode->Gettext());
					}
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
}

void ConversationDlg::PushConverNodeToQueue(ConversationContentNode& node)
{
	lock_guard<mutex> lk(m_nodeMutex);
	m_converMsgQueue.push(node);
}
	
bool ConversationDlg::GetConverNodeFromQueue(ConversationContentNode& node)
{
	
	if (m_converMsgQueue.empty())
	{
		return false;
	}
	lock_guard<mutex> lk(m_nodeMutex);
	node = m_converMsgQueue.front();
	m_converMsgQueue.pop();
	return true;
}

bool ConversationDlg::GetReceiveMessageFromSharedQueue( ConversationDlg* pThisDlg)
{
	while (1)
	{
		if (m_bExitGetMsgFSharedQueueThread)
		{
			break;
		}
		if (m_receivedMsgQueue.empty())
		{
			continue;
		}
		lock_guard<mutex> lk(m_mutex);
		MaosenQueue<Message>::iterator it = m_receivedMsgQueue.begin();
		for (; it != m_receivedMsgQueue.end(); ++it)
		{
			Message tempMsg = *it;
			ConversationContentNode node;
			bool ret = pThisDlg->JudgeIsCurrentFriendsMessage(tempMsg, node.m_friendId, node.m_content);
			if (ret)
			{
				m_receivedMsgQueue.pop();
				node.m_friendName = pThisDlg->m_friendItem.m_nickname;
				pThisDlg->PushConverNodeToQueue(node);
			}
		}
	}
	return true;
}

void ConversationDlg::DealWithReceiveMessageFunc(Message& msg)
{
	lock_guard<mutex> lk(m_mutex);
	m_receivedMsgQueue.push(msg);

}