#ifndef _SLEEP_H_
#define _SLEEP_H_

#include <Windows.h>

void SleepMilliseconds(unsigned int milliseconds)
{
	Sleep(milliseconds);
}

#endif