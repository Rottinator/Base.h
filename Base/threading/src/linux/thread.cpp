#ifndef _WIN32

#include <pthread.h>
#include "thread.h"

namespace Base
{
	namespace Threading
	{
		namespace __PRIVATE
		{
			struct ThreadExecutionParameter
			{
				void(*threadFunction) (void*);
				void* parameter;
			};

			void* threadExecutionFunction(void* parameter)
			{
				ThreadExecutionParameter* param = (ThreadExecutionParameter*)parameter;

				param->threadFunction(param->parameter);
			}
		}

		Thread::Thread(void(*threadFunction) (void*), void* parameter)
		{
			__PRIVATE::ThreadExecutionParameter* param = new(__PRIVATE::ThreadExecutionParameter);
			param->threadFunction = threadFunction;
			param->parameter = parameter;

			pthread_create(&_pthread, NULL, __PRIVATE::threadExecutionFunction, param);
		}

		void Thread::Start()
		{
			pthread_detach(_pthread);
		}
	}
}

#endif