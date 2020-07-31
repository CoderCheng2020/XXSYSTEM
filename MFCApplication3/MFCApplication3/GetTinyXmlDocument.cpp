#include "stdafx.h"
#include "GetTinyXmlDocument.h"

GetTinyXmlDocument* GetTinyXmlDocument::m_instance = NULL;

GetTinyXmlDocument::GetTinyXmlDocument()
{
	m_pDoc = CreateTiXmlDocumentFromDLL(_T("TinyXml.dll"));
}


GetTinyXmlDocument::~GetTinyXmlDocument()
{
}

TiXmlDocument* GetTinyXmlDocument::CreateTiXmlDocumentFromDLL(LPCTSTR lpszDll)
{
	TiXmlDocument* pModule = NULL;
	HMODULE hModule = LoadLibrary(CT2W(lpszDll));
	if (hModule != NULL)
	{
		LPFNCREATEMODULE2 CreateModule = (LPFNCREATEMODULE2)GetProcAddress(hModule, CREATEMODULE2);
		if (CreateModule != NULL)
		{
			pModule = CreateModule();
		}
		FreeLibrary(hModule);
	}

	return pModule;
}