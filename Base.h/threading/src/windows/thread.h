#ifndef _THREAD_H_
#define _THREAD_H_

#include <thread>

using namespace std;

class Thread
{
private:

	thread _threadObj;

public:

	Thread(void (*threadFunction) (void*), void* parameter) 
	{
		_threadObj = thread(threadFunction, parameter);
	}

	void Start() 
	{
		_threadObj.detach();
	}
};

#endif