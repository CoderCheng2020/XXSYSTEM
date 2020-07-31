#pragma once
#include "resource.h"		// Ö÷·ûºÅ
#include "Singleton.h"
#include "CommonVariables.h"
#include "ThreadPool.h"
#include "DealWithReceiveMessage.h"
#include <string>

using namespace std;

class DataBaseAccessor
{
public:
	static DataBaseAccessor* GetInstance();
	DataBaseAccessor() :m_serverPort(Get_ServerPort())
	{
		memset(m_serverIPv4, 0, sizeof(m_serverIPv4));
		string& Server_IPv4Str = Get_Server_Ipv4();
		memcpy(m_serverIPv4, Server_IPv4Str.c_str(), strlen(Server_IPv4Str.c_str()));
	}

	DataBaseAccessor(const char* serverIP, int port) :m_serverPort(port)
	{
		if (serverIP == NULL)
		{
			printf("serverIP is NULL in %s", __FUNCTION__);
			return;
		}
		memset(m_serverIPv4, 0, m_SERVER_IPV4_STR_LENGTH);
		memcpy(m_serverIPv4, serverIP, strlen(serverIP));
	}

	virtual ~DataBaseAccessor()
	{
		
	};
	char* GetUserPassword(char* userAccount);
	int ConnectServer();
	int ConnectServer(char* serverIPv4, int port);
	int SendMessageStr(string& message);
	void CreateReceiveMessageThread();
	int ReceiveMessage(string& receStr);
	//void ReceiveMessageImplement(void* params);
	static int ReceiveMessageCallback(PVOID data);
	friend void ReceiveMessageImplement(void* params);
private:
	DataBaseAccessor(DataBaseAccessor& dataBaseAccessor);
	int ConnectServerImple(char* serverIPv4, int port);
private:
	char* m_serverIP;
	const int m_SERVER_IPV4_STR_LENGTH = 16;
	char m_serverIPv4[16];
	int m_serverPort;
	static DataBaseAccessor* m_Instance;
	SOCKET m_ClientSocket;
	
};

