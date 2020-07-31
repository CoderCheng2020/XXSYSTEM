#pragma once
#include <queue>
using namespace std;

template <typename T>
class MaosenQueue
{
public:
	MaosenQueue()
	{
	
	};
	~MaosenQueue()
	{
	};
	T* begin()
	{
		m_pCurrQueue = SelectQueue();
		return &m_pCurrQueue->front();
	};
	T* end()
	{
		return (T*)NULL;
	};
	void push(T element)
	{
		m_pCurrQueue = SelectQueue();
		m_pCurrQueue->push(element);
	};
	void pop()
	{
		m_pCurrQueue = SelectQueue();
		m_pCurrQueue->pop();
	};
	int size()
	{
		m_pCurrQueue = SelectQueue();
		return m_pCurrQueue->size();
	};
	T& front()
	{
		m_pCurrQueue = SelectQueue();
		return m_pCurrQueue->front();
	};
	bool empty()
	{
		m_pCurrQueue = SelectQueue();
		return m_pCurrQueue->empty();
	};
	T* operator ++ ()
	{
		m_pCurrQueue = SelectQueue();
		if (++m_currItem < m_pCurrQueue->size())
		{
			return &operator[](m_currItem);
		}
		else
		{
			return NULL;
		}
	};
	T* operator -- ()
	{
		m_pCurrQueue = SelectQueue();
		if (--m_currItem >= 0)
		{
			return &operator[](m_currItem);
		}
		else
		{
			return NULL;
		}
	};
	
	T& operator[](int i)
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
	};
public:
	
	class iterator
	{
	public:
		iterator(T* rightElem)
		{
			this->m_ptr = rightElem;
		}
		~iterator()
		{

		}
		iterator& operator = (T* pRightElem)
		{
			delete this;
			this = new iterator(pRightElem);
			return *this;
		}
		T* operator++()
		{
			++m_ptr;
			return m_ptr;
		}
		bool operator !=(T* pRightElem)
		{
			return m_ptr != pRightElem;
		}
		T& operator *()
		{
			return *m_ptr;
		}
	protected:
		T* m_ptr;
	};
protected:
	int m_currItem;
	queue<T>* m_pCurrZeroQueue;
	queue<T>* m_pCurrQueue;
	queue<T> m_queueOne;
	queue<T> m_queueTwo;
	queue<T>* SelectQueue()
	{
		if (m_queueTwo.size() > 0)
		{
			return &m_queueTwo;
		}
		else
		{
			return &m_queueOne;
		}
	};
	queue<T>* SelectZeroQueue()
	{
		if (m_queueTwo.size() > 0)
		{
			return &m_queueOne;
		}
		else
		{
			return &m_queueTwo;
		}
	};
};

