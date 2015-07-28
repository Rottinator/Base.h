#include <cstdio>
#include <string>
#include <cstdlib>

#define MINIZ_HEADER_FILE_ONLY
#include "miniz.c"
#include "inflate.h"

#pragma warning(disable : 4996)

namespace Base
{
	namespace Compression
	{
		int FileInflate::getMin(int a, int b)
		{
			return a < b ? a : b;
		}

		void FileInflate::setCompressionModeFlat(unsigned char* buffer)
		{
			if (CompressionMode == DeflateCompressionMode::None)
			{
				buffer[0] = 0x78;
				buffer[1] = 0x01;
			}
			else if (CompressionMode == DeflateCompressionMode::Default)
			{
				buffer[0] = 0x78;
				buffer[1] = 0x9C;
			}
			else if (CompressionMode == DeflateCompressionMode::None)
			{
				buffer[0] = 0x78;
				buffer[1] = 0xDA;
			}
		}

		int FileInflate::exit(int exitCode, unsigned char* inputBuffer, unsigned char* outputBuffer)
		{
			free(inputBuffer);
			free(outputBuffer);

			return exitCode;
		}


		FileInflate::FileInflate()
		{
			bufferSize = 1024 * 1024; //1 MB
			CompressionMode = DeflateCompressionMode::AutoDetect;
		}

		int FileInflate::Decompress()
		{
			unsigned char* inputBuffer = (unsigned char*)malloc(bufferSize);
			unsigned char* outputBuffer = (unsigned char*)malloc(bufferSize);

			z_stream stream;

			memset(&stream, 0, sizeof(stream));
			stream.next_in = inputBuffer;
			stream.next_out = outputBuffer;
			stream.avail_in = 0;
			stream.avail_out = bufferSize;

			unsigned int remainingRead = Size;

			if (inflateInit(&stream) != Z_OK)
			{
				return exit(INFLATE_ERROR, inputBuffer, outputBuffer);
			}

			while (true)
			{
				int status;

				if (stream.avail_in == 0 && remainingRead > 0)
				{
					unsigned int nextBlockSize = getMin(bufferSize, remainingRead);

					if (CompressionMode == DeflateCompressionMode::AutoDetect)
					{
						fread(inputBuffer, 1, nextBlockSize, Input);
					}
					else
					{
						if (nextBlockSize + 2 <= bufferSize)
						{
							nextBlockSize += 2;
						}

						setCompressionModeFlat(inputBuffer);

						fread(inputBuffer + 2, 1, nextBlockSize - 2, Input);
					}

					stream.next_in = inputBuffer;
					stream.avail_in = nextBlockSize;

					if (nextBlockSize > remainingRead)
					{
						remainingRead = 0;
					}
					else
					{
						remainingRead -= nextBlockSize;
					}
				}

				status = inflate(&stream, Z_SYNC_FLUSH);

				if (stream.avail_out >= 0)
				{
					unsigned int blockSize = bufferSize - stream.avail_out;
					fwrite(outputBuffer, 1, blockSize, Output);

					stream.next_out = outputBuffer;
					stream.avail_out = bufferSize;
				}

				//Nichts mehr zu dekomprimieren und nichts mehr zum auslesen
				if (stream.avail_in == 0 && remainingRead == 0 || status == Z_STREAM_END)
				{
					break;
				}

				if (status != Z_OK)
				{
					return exit(INFLATE_ERROR, inputBuffer, outputBuffer);
				}
			}

			if (inflateEnd(&stream) != Z_OK)
			{
				return exit(INFLATE_ERROR, inputBuffer, outputBuffer);
			}

			return exit(INFLATE_SUCCESS, inputBuffer, outputBuffer);
		}
	}
}