#pragma once
#include "../TinyXml/tinyxmlImpliment.h"

class GetTinyXmlDocument
{
public:
	static GetTinyXmlDocument* GetInstance()
	{
		if (m_instance == NULL)
		{
			m_instance = new GetTinyXmlDocument();
		}
		return m_instance;
	}
	
	~GetTinyXmlDocument();
	TiXmlDocument* CreateTiXmlDocumentFromDLL(LPCTSTR lpszDll);
	TiXmlDocument* m_pDoc;
private:
	GetTinyXmlDocument();
	static GetTinyXmlDocument* m_instance;
	
};
#define CREATEMODULE2	"CreateTiXmlDocument"
typedef TiXmlDocument* (*LPFNCREATEMODULE2)();