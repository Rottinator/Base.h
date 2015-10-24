#ifndef _TCPLISTENER_H_
#define _TCPLISTENER_H_

#ifdef _WIN32

#include "windows\socket.h"

#else

#include "linux/socket.h"

#endif

#include "tcpClient.h"

namespace Base
{
	namespace Sockets
	{
		class TcpListener
		{
		private:
			BaseSocket* _socket;
		public:
			TcpListener();
			bool Bind(char* address, unsigned short port);
			bool StartListening(void(*clientConnected) (TcpClient*));
			void Close();
		};
	}
}

#endif