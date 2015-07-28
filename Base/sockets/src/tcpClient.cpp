#include "../../threading/threading.h"

using namespace Base::Threading;

#ifdef _WIN32

#include "windows\socket.h"

#else

#include "linux/socket.h"

#endif

#include "tcpClient.h"

namespace Base
{
	namespace Sockets
	{
		namespace __PRIVATE_TCPCLIENT
		{
			struct ReceiveDataParameter
			{
				Sockets::BaseSocket* Socket;
				int BufferSize;
				void(*ReceiveFunction) (char*, int);
				void(*ConnectionLostFunction) ();
			};

			void ReceiveData(void* parameter)
			{
				ReceiveDataParameter* param = (ReceiveDataParameter*)parameter;

				while (1)
				{
					char *buffer = new char[param->BufferSize];
					for (int i = 0; i < param->BufferSize; i++)
					{
						buffer[i] = 0;
					}

					int length = param->Socket->Receive(buffer, param->BufferSize);

					if (length <= 0)
					{
						if (param->ConnectionLostFunction != NULL)
						{
							param->ConnectionLostFunction();
						}

						break;
					}

					param->ReceiveFunction(buffer, length);
				}
			}
		}

		TcpClient::TcpClient()
		{
			Initialize();
			_socket = new BaseSocket(1); //1 Stand for SOCK_STREAM = TCPs
		}

		TcpClient::TcpClient(BaseSocket* socket)
		{
			Initialize();
			_socket = socket;
		}

		bool TcpClient::Connect(char *ipAdress, unsigned short port)
		{
			return _socket->Connect(ipAdress, port);
		}

		void TcpClient::Send(char *data, int length)
		{
			_socket->Send(data, length);
		}

		void TcpClient::Close()
		{
			_socket->Close();
		}

		void TcpClient::StartReceiveData(void(*ReceiveFunction) (char*, int))
		{
			__PRIVATE_TCPCLIENT::ReceiveDataParameter* parameter = new (__PRIVATE_TCPCLIENT::ReceiveDataParameter);
			parameter->ReceiveFunction = ReceiveFunction;
			parameter->ConnectionLostFunction = ConnectionLost;
			parameter->Socket = _socket,
				parameter->BufferSize = _bufferSize;

			Thread thread = Thread(__PRIVATE_TCPCLIENT::ReceiveData, parameter);
			thread.Start();
		}

		void TcpClient::Initialize()
		{
			_bufferSize = 0xffff;
			ConnectionLost = NULL;
		}
	}
}