#ifndef _WIN32

#include <unistd.h>

namespace Base
{
	namespace Utils
	{
		void SleepMilliseconds(unsigned int milliseconds)
		{
			sleep(milliseconds);
		}
	}
}

#endif