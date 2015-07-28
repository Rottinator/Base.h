#ifndef _UDPCLIENT_H_
#define _UDPCLIENT_H_

#ifdef _WIN32

#include "windows\socket.h"

#else

#include "linux/socket.h"

#endif

namespace Base
{
	namespace Sockets
	{
		class UdpClient
		{
		private:
			int _bufferSize;
			BaseSocket* _socket;
		public:
			void(*ConnectionLost) ();
		public:
			UdpClient();
			void SendTo(char *data, int length, char* address, unsigned short port);
			void Close();
			bool Bind(char* address, unsigned short port);
			void StartReceiveData(void(*ReceiveFunction) (char*, int, char*, unsigned short));
		private:
			void Initialize();
		};
	}
}

#endif