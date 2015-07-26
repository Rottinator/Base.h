#ifndef _BINARY_READER_H_
#define _BINARY_READER_H_

#include <cstdio>

#include "BinaryReaderBase.h"

#pragma warning(disable : 4996)

class BinaryReader : public BinaryReaderBase
{

private:
	FILE* _file;

public:
	size_t LastReadedCount;

public:
	BinaryReader() 
	{
		_file = NULL;
	}

	bool OpenFile(char* path)
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

	char ReadChar()
	{
		char readValue = 0;

		LastReadedCount = fread(&readValue, sizeof(char), 1, _file);

		return readValue;
	}

	unsigned char ReadUChar()
	{
		unsigned char readValue = 0;

		LastReadedCount = fread(&readValue, sizeof(unsigned char), 1, _file);

		return readValue;
	}

	short ReadShort()
	{
		short readValue = 0;

		LastReadedCount = fread(&readValue, sizeof(short), 1, _file);

		return readValue;
	}

	long ReadLong()
	{
		long readValue = 0;

		LastReadedCount = fread(&readValue, sizeof(long), 1, _file);

		return readValue;
	}

	int ReadInteger()
	{
		int readValue = 0;

		LastReadedCount = fread(&readValue, sizeof(int), 1, _file);

		return readValue;
	}

	float ReadFloat()
	{
		float readValue = 0;

		LastReadedCount = fread(&readValue, sizeof(float), 1, _file);

		return readValue;
	}

	double ReadDouble()
	{
		double readValue = 0;

		LastReadedCount = fread(&readValue, sizeof(double), 1, _file);
		
		return readValue;
	}

	void Read(void* buffer, size_t size)
	{
		LastReadedCount = fread(buffer, size, 1, _file);
	}

	void CloseFile()
	{
		fclose(_file);
	}

	int GetPosition()
	{
		return ftell(_file);
	}

	void SetPosition(int position)
	{
		fseek(_file, position, SEEK_SET);
	}

	void SetPosition(int value, int seekValue)
	{
		fseek(_file, value, seekValue);
	}

};

#endif