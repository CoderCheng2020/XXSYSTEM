#pragma once
#include "CommonVariables.h"
#include <mutex>
#include <condition_variable>

class IXXSystem
{
public:
	virtual void DealWithReceiveMessageFunc(Message& msg) = 0;
protected:
	
};