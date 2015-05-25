#ifndef _SOCKETBIND_H_
#define _SOCKETBIND_H_

#include <winsock.h>

int __SocketBind(SOCKET s, const sockaddr* addr, int namelen)
{
	int errcode = bind(s, addr, namelen); 
	return errcode;
}

#endif