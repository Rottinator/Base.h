#ifndef _BINARY_READER_H_
#define _BINARY_READER_H_

#include <cstdio>
#pragma warning(disable : 4996)

class BinaryReader
{

private:
	FILE* _file = NULL;

public:
	size_t LastReadedCount;

public:
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
};

#endif