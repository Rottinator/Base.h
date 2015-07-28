#include "..\..\threading\threading.h"

using namespace Base::Threading;

#ifdef _WIN32

#include "windows\socket.h"

#else

#include "linux/socket.h"

#endif

#include "udpClient.h"

namespace Base
{
	namespace Sockets
	{
		namespace __PRIVATE_UDPCLIENT
		{
			struct ReceiveDataParameter
			{
				Sockets::BaseSocket* Socket;
				int BufferSize;
				void(*ReceiveFunction) (char*, int, char*, unsigned short);
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

					char* fromAddress = new (char);
					unsigned short* port = new (unsigned short);

					int length = param->Socket->ReceiveFrom(buffer, param->BufferSize, &fromAddress, port);

					if (length <= 0)
					{
						if (param->ConnectionLostFunction != NULL)
						{
							param->ConnectionLostFunction();
						}

						break;
					}

					param->ReceiveFunction(buffer, length, fromAddress, *port);
				}
			}
		}


		UdpClient::UdpClient()
		{
			Initialize();
			_socket = new BaseSocket(2); //1 Stand for SOCK_DGRAM = UDP
		}

		void UdpClient::SendTo(char *data, int length, char* address, unsigned short port)
		{
			_socket->Send(data, length);
		}

		void UdpClient::Close()
		{
			_socket->Close();
		}

		bool UdpClient::Bind(char* address, unsigned short port)
		{
			return _socket->Bind(address, port);
		}

		void UdpClient::StartReceiveData(void(*ReceiveFunction) (char*, int, char*, unsigned short))
		{
			__PRIVATE_UDPCLIENT::ReceiveDataParameter* parameter = new (__PRIVATE_UDPCLIENT::ReceiveDataParameter);
			parameter->ReceiveFunction = ReceiveFunction;
			parameter->ConnectionLostFunction = ConnectionLost;
			parameter->Socket = _socket,
				parameter->BufferSize = _bufferSize;

			Thread thread = Thread(__PRIVATE_UDPCLIENT::ReceiveData, parameter);
			thread.Start();
		}

		void UdpClient::Initialize()
		{
			_bufferSize = 0xffff;
			ConnectionLost = NULL;
		}
	}
}



