#ifndef _BINARY_READER_H_
#define _BINARY_READER_H_

#include <cstdio>

#include "BinaryReaderBase.h"

namespace Base
{
	namespace IO
	{
		class BinaryReader : public BinaryReaderBase
		{
		private:
			FILE* _file;

		public:
			size_t LastReadedCount;

		public:
			BinaryReader();
			bool OpenFile(char* path);
			char ReadChar();
			unsigned char ReadUChar();
			short ReadShort();
			long ReadLong();
			int ReadInteger();
			float ReadFloat();
			double ReadDouble();
			void Read(void* buffer, size_t size);
			void CloseFile();
			int GetPosition();
			void SetPosition(int position);
			void SetPosition(int value, int seekValue);
		};
	}
}

#endif