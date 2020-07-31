#ifndef __COMMONVARIABLE_H__
#define __COMMONVARIABLE_H__

#define MESSAGE_DATA_LENGTH 256
#include <string>
#include "CommonFunctions.h"



#import "msxml4.dll"

using namespace MSXML2;

using namespace std;

const int Get_ServerPort();
string& Get_Server_Ipv4();

using namespace std;

typedef enum
{
	LOGIN=1,
	SEARCH,
	CONVERSATION
}Session_Type;

typedef enum
{
/*************************************************/
/*for login module*/
	CTS_LOGIN = 1,
	STC_LOGIN_REPLY = 2,
	CTS_LOGIN_REQUIRE_FRIEND_LIST = 3,
	STC_LOGIN_REQUIRE_FRIEND_LIST_REPLY = 4,
/*************************************************/

/*************************************************/
/*for search module*/
	CTS_SEARCH_USER_ACCOUNT = 1,
	STC_SEARCH_USER_ACCOUNT_REPLY = 2,
/*************************************************/

/*************************************************/
/*for conversation*/
	CTS_START_CONVERSATION = 1,
	STC_START_CONVERSATION = 2,
/*************************************************/
}Session_Child_Type;

class Message
{
public:
	Message() :Sequence(0), sessionType(LOGIN), sessionChildType(CTS_LOGIN)
	{
		
	}
	Message(int seq, Session_Type sessType, Session_Child_Type sessChildType, string& msgData) :Sequence(seq), sessionType(sessType), sessionChildType(sessChildType), messageData(msgData)
	{

	}
	bool ParseRawString(string& rawStr);
	string& ToString();
	string& GetMessageDataToSTLString();
	int Sequence;
	Session_Type sessionType;
	Session_Child_Type sessionChildType;
	string messageData;
	string m_toStr;
	//MSXML2::IXMLDOMDocumentPtr m_xdDoc;
	string m_msgDataToSTLString;
};

class UserLoginInfo
{
public:
	UserLoginInfo():m_id("1001"){}
	UserLoginInfo(UserLoginInfo* pInfo)
	{
		if (pInfo != NULL)
		{
			m_id = pInfo->m_id;
		}
	}
	string m_id;
};

#endif
