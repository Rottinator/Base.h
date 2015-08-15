#ifdef _WIN32

#include <Windows.h>

namespace Base
{
	namespace Utils
	{
		void SleepMilliseconds(unsigned int milliseconds)
		{
			Sleep(milliseconds);
		}
	}
}

#endif