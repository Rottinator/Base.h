#ifndef _TCPLISTENER_H_
#define _TCPLISTENER_H_

#include "..\..\threading\threading.h"

#ifdef _WIN32

#include "windows\socket.h"

#else
	
#include "linux/socket.h"

#endif

#include "TcpClient.h"

namespace __PRIVATE_TCPLISTENER_
{
	struct __AcceptSocketParameter  
	{
		BaseSocket* Socket;
		void (*ClientConnectedFunction) (TcpClient*);
	};

	void __AcceptSockets(void* parameter)
	{
		__AcceptSocketParameter* param = (__AcceptSocketParameter*)parameter;

		while(1)
		{
			BaseSocket* baseSocket = param->Socket->Accept();

			//Socket is closed now
			if(baseSocket == NULL)
			{
				break;
			}

			TcpClient* tcpClient = new TcpClient(baseSocket);

			param->ClientConnectedFunction(tcpClient);
		}
	}
}

class TcpListener
{
private:
	BaseSocket* _socket;
	
public:
	
	TcpListener()
	{
		_socket = new BaseSocket(1);
	}

	bool Bind(char* address, unsigned short port)
	{
		return _socket->Bind(address, port);
	}

	bool StartListening(void (*clientConnected) (TcpClient*))
	{
		bool result = _socket->Listen();

		if(result == false) 
		{
			return false;
		}

		__PRIVATE_TCPLISTENER_::__AcceptSocketParameter* parameter = new (__PRIVATE_TCPLISTENER_::__AcceptSocketParameter);
		parameter->Socket = _socket;
		parameter->ClientConnectedFunction = clientConnected;

		Thread thread = Thread(__PRIVATE_TCPLISTENER_::__AcceptSockets, parameter);
		thread.Start();

		return true;
	}

	void Close()
	{
		_socket->Close();
	}
};


#endif