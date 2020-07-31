#pragma once
#include "CommCtrl.h"
#include <string>

using namespace std;

class FriendItem :
	public TVINSERTSTRUCTW
{
public:
	FriendItem();
	~FriendItem();
	string m_friendId;
	string m_nickname;
	int m_gender;
	string m_telephone;
	string m_email;
	string m_mood;
	int IconType;
};

