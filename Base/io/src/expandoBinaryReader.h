#ifndef _EXPANDO_BINARY_READER_H_
#define _EXPANDO_BINARY_READER_H_

#include <cstdio>
#include "BinaryReader.h"
#include "../../utils/utils.h"

#pragma warning(disable : 4996)

namespace Base
{
	namespace IO
	{
		class ExpandoBinaryReader : BinaryReaderBase
		{
		private:
			BinaryReader _binaryReader;
			int _sleepValue;
		public:
			ExpandoBinaryReader(int sleepValue);
			bool OpenFile(char* path);
			char ReadChar();
			unsigned char ReadUChar();
			short ReadShort();
			long ReadLong();
			int ReadInteger();
			float ReadFloat();
			double ReadDouble();
			int GetPosition();
			void SetPosition(int position);
			void SetPosition(int value, int seekValue);
			void CloseFile();
		private:
			void Read(void* buffer, size_t size);
		};
	}
}

#endif