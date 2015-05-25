#ifndef _TCPCLIENT_H_
#define _TCPCLIENT_H_

#include "..\..\threading\threading.h"

#ifdef _WIN32

#include "windows\socket.h"

#else
	
#include "linux/socket.h"

#endif

namespace __PRIVATE_TCPCLIENT_
{
	
	struct __ReceiveDataParameter 
	{
		BaseSocket* Socket;
		int BufferSize;
		void (*ReceiveFunction) (char*, int);
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
		
			int length = param->Socket->Receive(buffer, param->BufferSize);
		
			if(length <= 0)
			{
				if(param->ConnectionLostFunction != NULL)
				{
					param->ConnectionLostFunction();
				}
				
				break;
			}

			param->ReceiveFunction(buffer, length);
		}
	}

}

class TcpClient
{

private:
	int _bufferSize;
	BaseSocket* _socket;

public:
	void (*ConnectionLost) ();
	
public:
	TcpClient()
	{
		Initialize();
		_socket = new BaseSocket(1); //1 Stand for SOCK_STREAM = TCPs
	}

	TcpClient(BaseSocket* socket)
	{
		Initialize();
		_socket = socket;
	}
		
	bool Connect(char *ipAdress, unsigned short port)
	{
		return _socket->Connect(ipAdress, port);
	}

	void Send(char *data, int length)
	{
		_socket->Send(data, length);
	}
	
	void Close()
	{
		_socket->Close();
	}

	void StartReceiveData(void (*ReceiveFunction) (char*, int))
	{
		__PRIVATE_TCPCLIENT_::__ReceiveDataParameter* parameter = new (__PRIVATE_TCPCLIENT_::__ReceiveDataParameter);
		parameter->ReceiveFunction = ReceiveFunction;
		parameter->ConnectionLostFunction = ConnectionLost;
		parameter->Socket = _socket,
		parameter->BufferSize = _bufferSize;

		Thread thread = Thread(__PRIVATE_TCPCLIENT_::__ReceiveData, parameter);
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