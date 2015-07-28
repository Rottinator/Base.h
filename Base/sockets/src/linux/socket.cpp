#ifndef _WIN32

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "socket.h"

namespace Base
{
	namespace Sockets
	{
		bool InitSocketLibrary()
		{
			return true;
		}

		void CleanupSocketLibrary()
		{

		}

		BaseSocket::BaseSocket(SOCKET socket, bool flag)
		{
			_socket = socket;
		}

		BaseSocket::BaseSocket(int socketType)
		{
			int protocol = 0;

			if (socketType == SOCK_STREAM)
			{
				protocol = IPPROTO_TCP;
			}
			else if (socketType == SOCK_DGRAM)
			{
				protocol = IPPROTO_UDP;
			}

			_socket = socket(AF_INET, socketType, protocol);
		}

		bool BaseSocket::Connect(char *address, unsigned short port)
		{
			sockaddr_in ipAddress = CreateIpAddress(address, port);

			int result = connect(_socket, (sockaddr*)&ipAddress, sizeof(sockaddr));

			return EvaluateResult(result);
		}

		bool BaseSocket::Bind(char* address, unsigned short port)
		{
			sockaddr_in ipAddress = CreateIpAddress(address, port);

			int result = bind(_socket, (sockaddr*)&ipAddress, sizeof(sockaddr));

			return EvaluateResult(result);
		}

		bool BaseSocket::Listen()
		{
			int result = listen(_socket, 5);

			return EvaluateResult(result);
		}

		BaseSocket* BaseSocket::Accept()
		{
			SOCKET acceptedSocket = accept(_socket, NULL, NULL);

			if (acceptedSocket == -1)
			{
				return NULL;
			}

			BaseSocket* baseSocket = new BaseSocket(acceptedSocket, true);

			return baseSocket;
		}

		bool BaseSocket::Send(char *data, int length)
		{
			int result = send(_socket, data, length, 0);

			return EvaluateResult(result);
		}

		bool BaseSocket::SendTo(char* data, int length, char* address, unsigned short port)
		{
			sockaddr_in ipAddress = CreateIpAddress(address, port);

			int result = sendto(_socket, data, length, 0, (sockaddr*)&ipAddress, sizeof(sockaddr));

			return EvaluateResult(result);
		}

		int BaseSocket::Receive(char* buffer, int readLength)
		{
			int length = recv(_socket, buffer, readLength, 0);

			return length;
		}

		int BaseSocket::ReceiveFrom(char* buffer, int readLength, char** address, unsigned short* port)
		{
			sockaddr* sockaddrFrom = new (sockaddr);
			int ipAddressLength = sizeof(sockaddr);

			int length = recvfrom(_socket, buffer, readLength, 0, sockaddrFrom, (socklen_t*)&ipAddressLength);

			sockaddr_in* sockaddrInFrom = (sockaddr_in*)sockaddrFrom;

			*address = inet_ntoa(sockaddrInFrom->sin_addr);
			*port = ntohs(sockaddrInFrom->sin_port);

			return length;
		}

		void BaseSocket::Close()
		{
			close(_socket);
		}


		sockaddr_in BaseSocket::CreateIpAddress(char* ipAddress, unsigned short port)
		{
			sockaddr_in IN_ipAddress;

			IN_ipAddress.sin_family = AF_INET;
			IN_ipAddress.sin_port = htons(port);
			inet_pton(AF_INET, ipAddress, &(IN_ipAddress.sin_addr));

			return IN_ipAddress;
		}

		bool BaseSocket::EvaluateResult(int result)
		{
			if (result < 0)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
}

#endif