#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include "DataBaseAccessor.h"
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

DataBaseAccessor* DataBaseAccessor::m_Instance = NULL;

DataBaseAccessor* DataBaseAccessor::GetInstance()
{
	if (m_Instance == NULL)
	{
		m_Instance = new DataBaseAccessor();
		
	}
	return m_Instance;
}

int DataBaseAccessor::ConnectServer()
{
	return ConnectServerImple(m_serverIPv4, m_serverPort);
}
int DataBaseAccessor::ConnectServer(char* serverIPv4, int port)
{
	return ConnectServerImple(serverIPv4, port);
}

int DataBaseAccessor::ConnectServerImple(char* serverIPv4, int port)
{
	if (serverIPv4 == NULL)
	{
		printf("serverIP4 is NULL in %s\n", __FUNCTION__);
		return -1;
	}
	WSADATA Ws;
	
	struct sockaddr_in ClientAddr;
	int Ret = 0;
	//char SendBuffer[MAX_PATH];

	if (WSAStartup(MAKEWORD(2, 2), &Ws) != 0)
	{
		printf("Init Windows socket failed:%d\n", GetLastError());
		return -1;
	}

	m_ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	BOOL bDontLinger = FALSE;
	setsockopt(m_ClientSocket, SOL_SOCKET, SO_DONTLINGER, (const char*)&bDontLinger, sizeof(BOOL));

	if (m_ClientSocket == INVALID_SOCKET)
	{
		printf("Create Socket failed:%d\n", GetLastError());
		return -1;
	}
	struct in_addr s;
	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_addr.S_un.S_addr = inet_addr(serverIPv4);//设置远程计算机的IP地址
	//ClientAddr.sin_addr.s_addr = inet_pton(AF_INET, serverIPv4, (void *)&s);// inet_addr(serverIPv4);
	ClientAddr.sin_port = htons(port);
	memset(ClientAddr.sin_zero, 0, 8);

	Ret = connect(m_ClientSocket, (sockaddr*)&ClientAddr, sizeof(ClientAddr));

	if (Ret == SOCKET_ERROR)
	{
		CString socketErrorStr;
		socketErrorStr.Format(_T("Connect Error:%d"), GetLastError());
		AfxMessageBox(socketErrorStr);
		return -1;
	}
	else
	{
		printf("Connect successed!\n");
	}
	return 0;
}

int DataBaseAccessor::SendMessageStr(string& message)
{
	if (message == "")
	{
		return -1;
	}
	int ret = 0;
	ret = send(m_ClientSocket, message.c_str(), strlen(message.c_str()), 0);
	return ret;
}

int DataBaseAccessor::ReceiveMessage(string& receStr)
{
	int length = 4096;
	char receiveData[4096] = {0};
	//int ret = recv(m_ClientSocket, receiveData, length, MSG_WAITALL);
	int ret = recv(m_ClientSocket, receiveData, length, 0);
	if (ret == 0)
	{
		AfxMessageBox(_T("服务器端已经断开连接！"));
	}
	receStr = string(receiveData);
	return ret;
}

void DataBaseAccessor::CreateReceiveMessageThread()
{
	_beginthread(ReceiveMessageImplement, 0,NULL);
}

void ReceiveMessageImplement(void* params)
{
	const int length = 4096;
	int recvCout = 0;
	//static char receiveData[4096] = {0};
	char* pReceiveData = NULL;
	ThreadPool threadPool(2,10);
	DataBaseAccessor* pABAccessor = DataBaseAccessor::GetInstance();
	while (1)
	{
		//memset(receiveData, 0, sizeof(receiveData));
		pReceiveData = new char[length];
		memset(pReceiveData, 0, length);
		int ret = recv(pABAccessor->m_ClientSocket, pReceiveData, length, 0);
		if (ret <= 0)
		{
			break;
		}
		threadPool.QueueTaskItem(pABAccessor->ReceiveMessageCallback, pReceiveData);
	}
}

int DataBaseAccessor::ReceiveMessageCallback(PVOID data)
{
	string rawDataStr = (char*)data;
	delete[] data;
	Message message;
	message.ParseRawString(rawDataStr);
	DealWithReceiveMessage::GetInstance()->PushMessageToQueue(message);
	return 0;
}