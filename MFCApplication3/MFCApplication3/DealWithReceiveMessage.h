#pragma once
#include <queue>
#include <mutex>
#include <thread>
#include "CommonVariables.h"
using namespace std;

class DealWithReceiveMessage
{
public:
	static DealWithReceiveMessage* GetInstance()
	{
		if (m_instance == NULL)
		{
			m_instance = new DealWithReceiveMessage();
		}
		return m_instance;
	}
	static void DealWithMessageThread(PVOID param);
	virtual ~DealWithReceiveMessage();
	void PushMessageToQueue(Message& msg);
	bool GetMessageFromQueue(Message& msg);
protected:
	static bool m_abort;
	thread* m_DealThread;
	mutex m_someMutex;
	queue<Message> m_messageQueue;
	DealWithReceiveMessage();
	static DealWithReceiveMessage* m_instance;
};

