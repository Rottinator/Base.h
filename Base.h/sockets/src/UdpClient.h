#ifndef _UDPCLIENT_H_
#define _UDPCLIENT_H_

#include "..\..\threading\threading.h"

#ifdef _WIN32

#include "windows\socket.h"

#else
	
#include "linux/socket.h"

#endif

namespace __PRIVATE_UDPCLIENT_
{
	struct __ReceiveDataParameter 
	{
		BaseSocket* Socket;
		int BufferSize;
		void (*ReceiveFunction) (char*, int, char*, unsigned short);
		void (*ConnectionLostFunction) ();
	};

	void __ReceiveData(void* parameter)
	{
		__ReceiveDataParameter* param = (__ReceiveDataParameter*)parameter;

		while(1)
		{
			char *buffer = new char[param->BufferSize]; 
			for(int i = 0; i < param->BufferSize; i++)
			{
				buffer[i] = 0;
			}
		
			char* fromAddress = new (char);
			unsigned short* port = new (unsigned short);

			int length = param->Socket->ReceiveFrom(buffer, param->BufferSize, &fromAddress, port);
		
			if(length <= 0)
			{
				if(param->ConnectionLostFunction != NULL)
				{
					param->ConnectionLostFunction();
				}
				
				break;
			}

			param->ReceiveFunction(buffer, length, fromAddress, *port);
		}
	}
}

class UdpClient
{

private:
	int _bufferSize;
	BaseSocket* _socket;

public:
	void (*ConnectionLost) ();
	
public:
	UdpClient()
	{
		Initialize();
		_socket = new BaseSocket(2); //1 Stand for SOCK_DGRAM = UDP
	}
		
	void SendTo(char *data, int length, char* address, unsigned short port)
	{
		_socket->Send(data, length);
	}
	
	void Close()
	{
		_socket->Close();
	}

	bool Bind(char* address, unsigned short port)
	{
		return _socket->Bind(address, port);
	}

	void StartReceiveData(void (*ReceiveFunction) (char*, int, char*, unsigned short))
	{
		__PRIVATE_UDPCLIENT_::__ReceiveDataParameter* parameter = new (__PRIVATE_UDPCLIENT_::__ReceiveDataParameter);
		parameter->ReceiveFunction = ReceiveFunction;
		parameter->ConnectionLostFunction = ConnectionLost;
		parameter->Socket = _socket,
		parameter->BufferSize = _bufferSize;

		Thread thread = Thread(__PRIVATE_UDPCLIENT_::__ReceiveData, parameter);
		thread.Start();
	}

private:
	void Initialize()
	{
		_bufferSize = 0xffff;
		ConnectionLost = NULL;
	}
};

#endif