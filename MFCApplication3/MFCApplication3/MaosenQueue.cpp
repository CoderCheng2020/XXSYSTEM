#include "stdafx.h"
#include "MaosenQueue.h"
/*
template <typename T>
MaosenQueue<T>::MaosenQueue()
{
}

template <typename T>
MaosenQueue<T>::~MaosenQueue()
{
}
template <typename T>
queue<T>* MaosenQueue<T>::SelectQueue()
{
	if (m_queueTwo.size() > 0)
	{
		return &m_queueTwo;
	}
	else
	{
		return &m_queueOne;
	}
}

template <typename T>
queue<T>* MaosenQueue<T>::SelectZeroQueue()
{
	if (m_queueTwo.size() > 0)
	{
		return &m_queueOne;
	}
	else
	{
		return &m_queueTwo;
	}
}

template <typename T>
void MaosenQueue<T>::push(T element)
{
	m_pCurrQueue = SelectQueue();
	m_pCurrQueue->push(element);
}

template <typename T>
T MaosenQueue<T>::pop()
{
	m_pCurrQueue = SelectQueue();
	return m_pCurrQueue->pop();
}

template <typename T>
int MaosenQueue<T>::size()
{
	m_pCurrQueue = SelectQueue();
	return m_pCurrQueue->size();

}

template <typename T>
T& MaosenQueue<T>::front()
{
	m_pCurrQueue = SelectQueue();
	return m_pCurrQueue->front();
}

template <typename T>
T* MaosenQueue<T>::begin()
{
	m_pCurrQueue = SelectQueue();
	return &m_pCurrQueue->front();
}
template <typename T>
T* MaosenQueue<T>::end()
{
	return (T*)NULL;
}

template <typename T>
T& MaosenQueue<T>::operator[](int position)
{
	T* pObjT;
	m_pCurrQueue = SelectQueue();
	m_pCurrZeroQueue = SelectZeroQueue();
	for (int i = 0; i < m_pCurrQueue->size(); i++)
	{
		
		T tempT = m_pCurrQueue->front();
		m_pCurrQueue->pop();
		m_pCurrZeroQueue->push(tempT);
		if (i == position)
		{
			pObjT = &m_pCurrZeroQueue->back();
		}
	}
	return *pObjT;
}

template <typename T>
bool MaosenQueue<T>::empty()
{
	m_pCurrQueue = SelectQueue();
	return m_pCurrQueue->empty();
}





template <typename T>
T& MaosenQueue<T>::operator++()
{
	m_pCurrQueue = SelectQueue();
	if (++m_currItem < m_pCurrQueue->size())
	{
		return operator[](m_currItem);
	}
	else
	{
		return operator[](m_pCurrQueue->size()-1);
	}
}

template <typename T>
T& MaosenQueue<T>::operator--()
{
	m_pCurrQueue = SelectQueue();
	if (--m_currItem > 0)
	{
		return operator[](m_currItem);
	}
	else
	{
		return operator[](0);
	}
}
*/


