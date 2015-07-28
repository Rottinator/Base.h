#ifndef _SOCKETBIND_H_
#define _SOCKETBIND_H_

#include <winsock.h>

namespace Base
{
	namespace Sockets
	{
		namespace __PRIVATE
		{
			int SocketBind(SOCKET s, const sockaddr* addr, int namelen);
		}
	}
}

#endif