#ifdef _WIN32

#include <thread>
#include "thread.h"

namespace Base
{
	namespace Threading
	{
		Thread::Thread(void(*threadFunction) (void*), void* parameter)
		{
			_threadObj = std::thread(threadFunction, parameter);
		}

		void Thread::Start()
		{
			_threadObj.detach();
		}
	}
}

#endif