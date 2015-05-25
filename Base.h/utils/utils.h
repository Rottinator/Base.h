#ifndef _UTILS_H_
#define _UTILS_H_

#ifdef _WIN32

#include "src\windows\sleep.h"

#else

#include "src/linux/sleep.h"

#endif

#endif