#pragma once
#include <string>
#include <vector>

using namespace std;

class CommonFunctions
{
public:
	string& CStringToSTLstring(const CString& CStr);
	void SplitString(const string& s, const string& c, vector<string>& v);//split the string
	LPCWSTR stringToLPCWSTR(std::string orig);//from string to LPCWSTR
	string& WCharToMByte(LPCWSTR lpcwszStr);// from LPCWSTR to string
	LPWSTR stringToLPWSTR(string& orig);
	~CommonFunctions();
	static CommonFunctions* GetInstance();
private:
	CommonFunctions();
	static CommonFunctions* m_instance;
	wchar_t *m_wcstring;
	string m_string;
};

