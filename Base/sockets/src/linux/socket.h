#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef unsigned int SOCKET;

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

			BaseSocket(SOCKET socket, bool flag);

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
			sockaddr_in CreateIpAddress(char* ipAddress, unsigned short port);
			bool EvaluateResult(int result);
		};

	}
}

#endif