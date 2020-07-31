#include "stdafx.h"
#include "DealWithReceiveMessage.h"
#include "MFCApplication3Dlg.h"
#include "FriendListDlg.h"

DealWithReceiveMessage* DealWithReceiveMessage::m_instance = NULL;
bool DealWithReceiveMessage::m_abort = false;
DealWithReceiveMessage::DealWithReceiveMessage()
{
	m_DealThread = new thread(DealWithMessageThread, (PVOID)NULL);
}


DealWithReceiveMessage::~DealWithReceiveMessage()
{
	m_abort = true;
	Sleep(200);
	if (m_DealThread != NULL)
	{
		delete m_DealThread;
	}
}

void DealWithReceiveMessage::PushMessageToQueue(Message& msg)
{
	std::lock_guard<std::mutex> guard(m_someMutex);
	m_messageQueue.push(msg);
}

bool DealWithReceiveMessage::GetMessageFromQueue(Message& msg)
{
	std::lock_guard<std::mutex> guard(m_someMutex);
	if (m_messageQueue.empty())
	{
		return false;
	}
	else
	{
		msg = m_messageQueue.front();
		m_messageQueue.pop();
		return true;
	}
}

void DealWithReceiveMessage::DealWithMessageThread(PVOID param)
{
	while (1)
	{
		if (m_abort)
		{
			break;
		}
		Message msg;
		bool ret = DealWithReceiveMessage::GetInstance()->GetMessageFromQueue(msg);
		if (ret)
		{
			switch(msg.sessionType)
			{
			case LOGIN:
				if (msg.sessionChildType == STC_LOGIN_REPLY)
				{
					CMFCApplication3Dlg::DealWithReceiveMessageFunc(msg);
				}
				else if (msg.sessionChildType == STC_LOGIN_REQUIRE_FRIEND_LIST_REPLY)
				{
					FriendListDlg::DealWithReceiveMessageFunc(msg);
				}
				break;
			//case 	
			}
		}
	}
	

}