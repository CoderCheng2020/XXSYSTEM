#include "stdafx.h"
#include "CommonFunctions.h"

CommonFunctions* CommonFunctions::m_instance = NULL;

CommonFunctions* CommonFunctions::GetInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new CommonFunctions();
	}
	return m_instance;
}

CommonFunctions::CommonFunctions() :m_wcstring(NULL)
{
}


CommonFunctions::~CommonFunctions()
{
	if (m_instance != NULL)
	{
		delete m_instance;
	}

	if (m_wcstring != NULL)
	{
		delete m_wcstring;
	}
}

string& CommonFunctions::WCharToMByte(LPCWSTR lpcwszStr)
{
	static string str;
	DWORD dwMinSize = 0;
	LPSTR lpszStr = NULL;
	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, NULL, 0, NULL, FALSE);
	if (0 == dwMinSize)
	{
		return string("ERROR");
	}
	lpszStr = new char[dwMinSize];
	WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, lpszStr, dwMinSize, NULL, FALSE);
	str = lpszStr;
	delete[] lpszStr;
	return str;
}

LPCWSTR CommonFunctions::stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	if (m_wcstring != NULL)
	{
		delete[] m_wcstring;
		m_wcstring = NULL;
	}
	m_wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(origsize+1));
	mbstowcs_s(&convertedChars, m_wcstring, origsize, orig.c_str(), _TRUNCATE);

	return m_wcstring;
}

LPWSTR CommonFunctions::stringToLPWSTR(string& orig)
{
	static wstring widstr;

	widstr = std::wstring(orig.begin(), orig.end());

	return (LPWSTR)widstr.c_str();
}


void CommonFunctions::SplitString(const string& s, const string& c, vector<string>& v)
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

string& CommonFunctions::CStringToSTLstring(const CString& CStr)
{
	if (CStr == _T(""))
	{
		m_string = "";
	}
	m_string = CT2A(CStr);
	return m_string;
}