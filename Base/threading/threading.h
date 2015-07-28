#ifndef _THREADING_H_
#define _THREADING_H_

#ifdef _WIN32

#include "src\windows\thread.h"

#else

#include "src/linux/thread.h"

#endif

#endif