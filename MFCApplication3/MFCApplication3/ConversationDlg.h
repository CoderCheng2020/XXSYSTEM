#pragma once
#include "afxwin.h"
#include "Resource.h"
#include "FriendItem.h"
#include "DataBaseAccessor.h"
#include "CommonVariables.h"
#include <string>
#include "MaosenQueue.h"

using namespace std;

// ConversationDlg 对话框
struct ConversationContentNode
{
	ConversationContentNode()
	{
		time_t tt = time(NULL);//这句返回的只是一个时间cuo
		tm* t = localtime(&tt);
		char timeStamp[32] = {0};
		sprintf_s(timeStamp, "%d-%02d-%02d %02d:%02d:%02d\n",
			t->tm_year + 1900,
			t->tm_mon + 1,
			t->tm_mday,
			t->tm_hour,
			t->tm_min,
			t->tm_sec);
		m_time = string(timeStamp);

	}
	string m_time;
	string m_friendId;
	string m_friendName;
	string m_content;
};
class ConversationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConversationDlg)

public:
	ConversationDlg(CWnd* pParent = NULL);   // 标准构造函数
	ConversationDlg(UserLoginInfo* pUserInfo, FriendItem* pFriendItem, CWnd* pParent = NULL);
	virtual ~ConversationDlg();
	static void DealWithReceiveMessageFunc(Message& msg);
// 对话框数据
	enum { IDD = IDD_DLG_CONVERSATION };

protected:
	static bool m_bExitGetMsgFSharedQueueThread;
	thread* m_pGetMsgFromSharedQueueThread;
	queue<ConversationContentNode> m_converMsgQueue;
	mutex m_nodeMutex;
	static mutex m_mutex;
	static MaosenQueue<Message> m_receivedMsgQueue;
	MSXML2::IXMLDOMDocumentPtr m_xdDoc;
	unsigned long m_sequence;
	UserLoginInfo* m_pUserInfo;
	FriendItem m_friendItem;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	string& EncodeConversation(string& inputStr);
	static bool GetReceiveMessageFromSharedQueue(ConversationDlg* pThisDlg);
	bool JudgeIsCurrentFriendsMessage(Message& msg, string&friendId, string& contentStr);
	void PushConverNodeToQueue(ConversationContentNode& node);
	bool GetConverNodeFromQueue(ConversationContentNode& node);
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_conversationEdit;
	CEdit m_sendingAreaEdit;
	afx_msg void OnBnClickedOk();
};
