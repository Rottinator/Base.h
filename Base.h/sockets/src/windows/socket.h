#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <winsock.h>
#include "bind.h"

bool InitSocketLibrary()
{
	int errcode;
	WSAData wsadat;
	errcode = WSAStartup(MAKEWORD(2, 0), & wsadat);

	if(errcode != 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void CleanupSocketLibrary()
{
	WSACleanup();
}

class BaseSocket
{
private:
	SOCKET _socket;

	BaseSocket(SOCKET socket)
	{
		_socket = socket;
	}

public:
	BaseSocket(int socketType)
	{
		int protocol = 0;

		if(socketType == SOCK_STREAM)
		{
			protocol = IPPROTO_TCP;
		}
		else if(socketType == SOCK_DGRAM)
		{
			protocol = IPPROTO_UDP;
		}

		_socket = socket(AF_INET, socketType, protocol);
	}

	bool Connect(char *address, unsigned short port)
	{
		SOCKADDR_IN ipAddress = CreateIpAddress(address, port);
		
		int result = connect(_socket, (SOCKADDR*)&ipAddress, sizeof(ipAddress));
		
		return EvaluateResult(result);
	}

	bool Bind(char* address, unsigned short port)
	{
		SOCKADDR_IN ipAddress = CreateIpAddress(address, port);
		
		int result = __SocketBind(_socket, (SOCKADDR*)&ipAddress, sizeof(ipAddress));

		return EvaluateResult(result);
	}

	bool Listen()
	{
		int result = listen(_socket, SOMAXCONN);

		return EvaluateResult(result);
	}

	BaseSocket* Accept()
	{
		SOCKET acceptedSocket = accept(_socket, NULL, NULL);

		if(acceptedSocket == INVALID_SOCKET)
		{
			return NULL;
		}

		BaseSocket* baseSocket = new BaseSocket(acceptedSocket);

		return baseSocket;
	}

	bool Send(char *data, int length)
	{
		int result = send(_socket, data, length, 0);

		return EvaluateResult(result);
	}

	bool SendTo(char* data, int length, char* address, unsigned short port)
	{
		SOCKADDR_IN ipAddress = CreateIpAddress(address, port);

		int result = sendto(_socket, data, length, 0, (SOCKADDR*) &ipAddress, sizeof(SOCKADDR));
	
		return EvaluateResult(result);
	}

	int Receive(char* buffer, int readLength)
	{
		int length = recv(_socket, buffer, readLength, 0);

		return length;
	}

	int ReceiveFrom(char* buffer, int readLength, char** address, unsigned short* port)
	{
		SOCKADDR_IN sockaddrFrom;
		int ipAddressLength = sizeof(sockaddrFrom);

		int length = recvfrom(_socket, buffer, readLength, 0, (SOCKADDR*)&sockaddrFrom, &ipAddressLength);

		*address = inet_ntoa(sockaddrFrom.sin_addr);
		*port = ntohs(sockaddrFrom.sin_port);
		
		return length;
	}

	void Close()
	{
		closesocket(_socket);
	}

private:

	SOCKADDR_IN CreateIpAddress(char *ipAddress, unsigned short port)
	{
		SOCKADDR_IN IN_ipAddress;
		IN_ipAddress.sin_family=AF_INET;
		IN_ipAddress.sin_port=htons(port);
		IN_ipAddress.sin_addr.s_addr=inet_addr(ipAddress);
		
		return IN_ipAddress;
	}

	bool EvaluateResult(int result)
	{
		if(result == SOCKET_ERROR)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

};

#endif