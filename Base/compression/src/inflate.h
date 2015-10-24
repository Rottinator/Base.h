#ifndef _FILE_INFLATE_H_
#define _FILE_INFLATE_H_

#define INFLATE_SUCCESS 0
#define INFLATE_ERROR 1

#include <cstdio>

namespace Base
{
	namespace Compression
	{
		enum class DeflateCompressionMode { AutoDetect = 0, None = 1, Default = 2, Best = 3 };

		class FileInflate
		{
		private:
			unsigned int bufferSize;

			int getMin(int a, int b);
			void setCompressionModeFlat(unsigned char* buffer);
			int exit(int exitCode, unsigned char* inputBuffer, unsigned char* outputBuffer);

		public:
			FileInflate();

			FILE* Input;
			FILE* Output;
			unsigned int Size;
			DeflateCompressionMode CompressionMode;

			int Decompress();
		};
	}
}

#endif