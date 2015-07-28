#ifdef _WIN32

#include <winsock.h>
#include "bind.h"

namespace Base
{
	namespace Sockets
	{
		namespace __PRIVATE
		{
			int SocketBind(SOCKET s, const sockaddr* addr, int namelen)
			{
				int errcode = bind(s, addr, namelen);
				return errcode;
			}
		}
	}
}

#endif