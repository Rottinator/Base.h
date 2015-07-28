#include "..\..\threading\threading.h"

using namespace Base::Threading;

#ifdef _WIN32

#include "windows\socket.h"

#else

#include "linux/socket.h"

#endif

#include "tcpClient.h"
#include "tcpListener.h"

namespace Base
{
	namespace Sockets
	{
		namespace __PRIVATE_TCPLISTENER
		{
			struct AcceptSocketParameter
			{
				Sockets::BaseSocket* Socket;
				void(*ClientConnectedFunction) (Sockets::TcpClient*);
			};

			void AcceptSockets(void* parameter)
			{
				AcceptSocketParameter* param = (AcceptSocketParameter*)parameter;

				while (1)
				{
					Sockets::BaseSocket* baseSocket = param->Socket->Accept();

					//Socket is closed now
					if (baseSocket == NULL)
					{
						break;
					}

					Sockets::TcpClient* tcpClient = new Sockets::TcpClient(baseSocket);

					param->ClientConnectedFunction(tcpClient);
				}
			}
		}

		TcpListener::TcpListener()
		{
			_socket = new BaseSocket(1);
		}

		bool TcpListener::Bind(char* address, unsigned short port)
		{
			return _socket->Bind(address, port);
		}

		bool TcpListener::StartListening(void(*clientConnected) (TcpClient*))
		{
			bool result = _socket->Listen();

			if (result == false)
			{
				return false;
			}

			__PRIVATE_TCPLISTENER::AcceptSocketParameter* parameter = new (__PRIVATE_TCPLISTENER::AcceptSocketParameter);
			parameter->Socket = _socket;
			parameter->ClientConnectedFunction = clientConnected;

			Thread thread = Thread(__PRIVATE_TCPLISTENER::AcceptSockets, parameter);
			thread.Start();

			return true;
		}

		void TcpListener::Close()
		{
			_socket->Close();
		}
	}
}
