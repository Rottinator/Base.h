#ifndef _SLEEP_H_
#define _SLEEP_H_

#include <unistd.h>

void SleepMilliseconds(unsigned int milliseconds)
{
	sleep(milliseconds);
}

#endif