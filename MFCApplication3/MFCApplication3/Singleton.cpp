#include "stdafx.h"
#include "Singleton.h"

template<class T>
T* Singleton<T>::m_Instance = NULL;

template<class T>
T* Singleton<T>::Instance()
{
	if (m_Instance == NULL)
	{
		m_Instance = new T();
	}
	return m_Instance;
}

template<class T>
Singleton<T>::Singleton()
{

}

template<class T>
Singleton<T>::~Singleton()
{
	delete m_Instance;
}
