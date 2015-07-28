#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <winsock.h>

namespace Base
{
	namespace Sockets
	{
		bool InitSocketLibrary();
		void CleanupSocketLibrary();

		class BaseSocket
		{
		private:
			SOCKET _socket;

			BaseSocket(SOCKET socket);
		public:
			BaseSocket(int socketType);
			bool Connect(char *address, unsigned short port);
			bool Bind(char* address, unsigned short port);
			bool Listen();
			BaseSocket* Accept();
			bool Send(char *data, int length);
			bool SendTo(char* data, int length, char* address, unsigned short port);
			int Receive(char* buffer, int readLength);
			int ReceiveFrom(char* buffer, int readLength, char** address, unsigned short* port);
			void Close();

		private:
			SOCKADDR_IN CreateIpAddress(char *ipAddress, unsigned short port);
			bool EvaluateResult(int result);
		};
	}
}

#endif