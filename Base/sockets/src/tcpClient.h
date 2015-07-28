#ifndef _TCPCLIENT_H_
#define _TCPCLIENT_H_

#ifdef _WIN32

#include "windows\socket.h"

#else

#include "linux/socket.h"

#endif

namespace Base
{
	namespace Sockets
	{
		class TcpClient
		{
		private:
			int _bufferSize;
			BaseSocket* _socket;

		public:
			void(*ConnectionLost) ();

		public:
			TcpClient();
			TcpClient(BaseSocket* socket);
			bool Connect(char *ipAdress, unsigned short port);
			void Send(char *data, int length);
			void Close();
			void StartReceiveData(void(*ReceiveFunction) (char*, int));

		private:
			void Initialize();
		};
	}
}

#endif