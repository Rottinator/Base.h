#include <cstdio>
#include "binaryReader.h"

#pragma warning(disable : 4996)

namespace Base
{
	namespace IO
	{
		BinaryReader::BinaryReader()
		{
			_file = NULL;
		}

		bool BinaryReader::OpenFile(char* path)
		{
			_file = fopen(path, "r+b");

			if (_file == NULL)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		char BinaryReader::ReadChar()
		{
			char readValue = 0;

			LastReadedCount = fread(&readValue, sizeof(char), 1, _file);

			return readValue;
		}

		unsigned char BinaryReader::ReadUChar()
		{
			unsigned char readValue = 0;

			LastReadedCount = fread(&readValue, sizeof(unsigned char), 1, _file);

			return readValue;
		}

		short BinaryReader::ReadShort()
		{
			short readValue = 0;

			LastReadedCount = fread(&readValue, sizeof(short), 1, _file);

			return readValue;
		}

		long BinaryReader::ReadLong()
		{
			long readValue = 0;

			LastReadedCount = fread(&readValue, sizeof(long), 1, _file);

			return readValue;
		}

		int BinaryReader::ReadInteger()
		{
			int readValue = 0;

			LastReadedCount = fread(&readValue, sizeof(int), 1, _file);

			return readValue;
		}

		float BinaryReader::ReadFloat()
		{
			float readValue = 0;

			LastReadedCount = fread(&readValue, sizeof(float), 1, _file);

			return readValue;
		}

		double BinaryReader::ReadDouble()
		{
			double readValue = 0;

			LastReadedCount = fread(&readValue, sizeof(double), 1, _file);

			return readValue;
		}

		void BinaryReader::Read(void* buffer, size_t size)
		{
			LastReadedCount = fread(buffer, size, 1, _file);
		}

		void BinaryReader::CloseFile()
		{
			fclose(_file);
		}

		int BinaryReader::GetPosition()
		{
			return ftell(_file);
		}

		void BinaryReader::SetPosition(int position)
		{
			fseek(_file, position, SEEK_SET);
		}

		void BinaryReader::SetPosition(int value, int seekValue)
		{
			fseek(_file, value, seekValue);
		}
	}
}