#pragma once

using namespace std;

template<class T>
class Singleton
{
public:
	static T* Instance();
protected:
	Singleton();
	static T* m_Instance;
public:
	virtual ~Singleton();
	
};

