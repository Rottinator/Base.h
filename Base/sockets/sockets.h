#ifndef _SOCKETS_H_
#define _SOCKETS_H_

#include "src/tcpClient.h"
#include "src/tcpListener.h"
#include "src/udpClient.h"

namespace Base
{
	namespace Sockets
	{
		struct addressContainer
		{
			char* Any;
			char* Broadcast;
			char* Localhost;
		} IpAddress = { "0.0.0.0", "255.255.255.255", "127.0.0.1" };
	}
}

#endif