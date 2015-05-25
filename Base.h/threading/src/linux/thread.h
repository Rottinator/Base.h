#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>

namespace __PRIVATE_THREAD_
{
	struct __ThreadExecutionParameter 
	{
		void (*threadFunction) (void*);
		void* parameter;
	};

	void* threadExecutionFunction (void* parameter)
	{
		__ThreadExecutionParameter* param = (__ThreadExecutionParameter*)parameter;

		param->threadFunction(param->parameter);
	}
}

class Thread
{
private:

	pthread_t _pthread;

public:

	Thread(void (*threadFunction) (void*), void* parameter) 
	{
		__PRIVATE_THREAD_::__ThreadExecutionParameter* param = new(__PRIVATE_THREAD_::__ThreadExecutionParameter);
		param->threadFunction = threadFunction;
		param->parameter = parameter;

		pthread_create(&_pthread, NULL, __PRIVATE_THREAD_::threadExecutionFunction, param);
	}

	void Start()
	{
		pthread_detach(_pthread);
	}
};

#endif