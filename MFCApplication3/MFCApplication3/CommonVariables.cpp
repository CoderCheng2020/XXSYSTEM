#include "stdafx.h"
#include <stdio.h>
#include "CommonVariables.h"
#include <string>
using namespace std;

const int SERVER_PORT = 4399;
string SERVER_IPV4 = "192.168.43.121";

const int Get_ServerPort()
{
	return SERVER_PORT;
}

string& Get_Server_Ipv4()
{
	return SERVER_IPV4;
}
bool Message::ParseRawString(string& rawStr)
{
	try
	{
		CoInitialize(NULL);
		MSXML2::IXMLDOMDocumentPtr pDoc(__uuidof(MSXML2::DOMDocument));
		if (pDoc->loadXML(rawStr.c_str()) == VARIANT_TRUE)
		{
			MSXML2::IXMLDOMNodePtr messageNode;
			messageNode = pDoc->selectSingleNode(L"//Message");
			if (messageNode != NULL)
			{
				MSXML2::IXMLDOMNodePtr infoNode = messageNode->selectSingleNode(L"Sequence");
				if (infoNode != NULL)
				{
					Sequence = _ttoi((LPCTSTR)infoNode->Gettext());
				}
				else
				{
					AfxMessageBox(_T("Miss Sequence node!"));
					return false;
				}
				infoNode = messageNode->selectSingleNode(L"SessionType");
				if (infoNode != NULL)
				{
					sessionType = (Session_Type)_ttoi((LPCTSTR)infoNode->Gettext());
				}
				else
				{
					AfxMessageBox(_T("Miss Session_Type node!"));
					return false;
				}
				infoNode = messageNode->selectSingleNode(L"SessionChildType");
				if (infoNode != NULL)
				{
					sessionChildType = (Session_Child_Type)_ttoi((LPCTSTR)infoNode->Gettext());
				}
				else
				{
					AfxMessageBox(_T("Miss Session_Child_Type node!"));
					return false;
				}
				infoNode = messageNode->selectSingleNode(L"MessageData");
				if (infoNode != NULL)
				{
					messageData = CommonFunctions::GetInstance()->CStringToSTLstring((LPCTSTR)infoNode->Gettext());
				}
			}
			else
			{
				AfxMessageBox(_T("Miss messageNode node!"));
				return false;
			}
		}
		else
		{
			CString errorInfo;
			errorInfo.Format(_T("Error: Fail to parse rawstring:%s"), rawStr);
			AfxMessageBox(errorInfo);
			return false;
		}
	}
	catch (_com_error &e)
	{
		CString tempStr;
		tempStr.Format(_T("Error:e is %s"), e.ErrorMessage());
		AfxMessageBox(tempStr);
	}
	
	return true;
}

string& Message::ToString()
{
	MSXML2::IXMLDOMDocumentPtr xdDoc(__uuidof(MSXML2::DOMDocument));
	if (messageData != "")
	{

		if (xdDoc != NULL)
		{
			MSXML2::IXMLDOMNodePtr xnRoot;
			xnRoot = xdDoc->appendChild(xdDoc->createElement(_T("Message")));
			if (xnRoot != NULL)
			{
				CString valueStr;
				valueStr.Format(_T("%d"), Sequence);
				xnRoot->appendChild(xdDoc->createElement(_T("Sequence")))->Puttext((LPCTSTR)valueStr);
				valueStr.Format(_T("%d"), sessionType);
				xnRoot->appendChild(xdDoc->createElement(_T("SessionType")))->Puttext((LPCTSTR)valueStr);
				valueStr.Format(_T("%d"), sessionChildType);
				xnRoot->appendChild(xdDoc->createElement(_T("SessionChildType")))->Puttext((LPCTSTR)valueStr);
				valueStr = CommonFunctions::GetInstance()->stringToLPCWSTR(messageData);
				//valueStr.Format(_T("%s"), messageData.c_str());
				xnRoot->appendChild(xdDoc->createElement(_T("MessageData")))->Puttext((LPCTSTR)valueStr);
			}
		}
		/*
		USES_CONVERSION;
		memset(TempStr, 0, sizeof(TempStr));
		sprintf_s(TempStr, "%d,%d,%d,%s#", Sequence, sessionType, sessionChildType, T2A(messageData));*/

	}
	else
	{
		/*
		memset(TempStr, 0, sizeof(TempStr));
		sprintf_s(TempStr, "%d,%d,%d#", Sequence, sessionType, sessionChildType);*/

		MSXML2::IXMLDOMNodePtr xnRoot;
		xnRoot = xdDoc->appendChild(xdDoc->createElement(_T("Message")));
		if (xnRoot != NULL)
		{
			CString valueStr;
			valueStr.Format(_T("%d"), Sequence);
			xnRoot->appendChild(xdDoc->createElement(_T("Sequenct")))->Puttext((LPCTSTR)valueStr);
			valueStr.Format(_T("%d"), sessionType);
			xnRoot->appendChild(xdDoc->createElement(_T("SessionType")))->Puttext((LPCTSTR)valueStr);
			valueStr.Format(_T("%d"), sessionChildType);
			xnRoot->appendChild(xdDoc->createElement(_T("SessionChildType")))->Puttext((LPCTSTR)valueStr);
		}

	}

	return CommonFunctions::GetInstance()->WCharToMByte((LPCWSTR)xdDoc->xml);
}

string& Message::GetMessageDataToSTLString()
{
	return messageData;
}