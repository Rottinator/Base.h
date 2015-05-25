#ifndef _SOCKETS_H_
#define _SOCKETS_H_

#include "src/TcpClient.h"
#include "src/TcpListener.h"
#include "src/UdpClient.h"

struct addressContainer
{
	char* Any;
	char* Broadcast;
	char* Localhost;
} IpAddress = { "0.0.0.0", "255.255.255.255", "127.0.0.1" };

#endif