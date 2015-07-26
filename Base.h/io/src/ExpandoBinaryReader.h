#ifndef _EXPANDO_BINARY_READER_H_
#define _EXPANDO_BINARY_READER_H_

#include <cstdio>
#include "BinaryReader.h"
#include "../../utils/utils.h"

#pragma warning(disable : 4996)

class ExpandoBinaryReader : BinaryReaderBase
{
private:
	BinaryReader _binaryReader;
	int _sleepValue;

public: 
	ExpandoBinaryReader(int sleepValue)
	{
		_binaryReader = BinaryReader();
		_sleepValue = sleepValue;
	}

	bool OpenFile(char* path)
	{
		return _binaryReader.OpenFile(path);
	}

	char ReadChar()
	{
		char readValue = 0;

		Read(&readValue, sizeof(char));

		return readValue;
	}

	unsigned char ReadUChar()
	{
		unsigned char readValue = 0;

		Read(&readValue, sizeof(unsigned char));

		return readValue;
	}

	short ReadShort()
	{
		short readValue = 0;

		Read(&readValue, sizeof(short));

		return readValue;
	}

	long ReadLong()
	{
		long readValue = 0;

		Read(&readValue, sizeof(long));

		return readValue;
	}

	int ReadInteger()
	{
		int readValue = 0;

		Read(&readValue, sizeof(int));

		return readValue;
	}

	float ReadFloat()
	{
		float readValue = 0;

		Read(&readValue, sizeof(float));

		return readValue;
	}

	double ReadDouble()
	{
		double readValue = 0;

		Read(&readValue, sizeof(double));
		
		return readValue;
	}

	int GetPosition()
	{
		return _binaryReader.GetPosition();
	}

	void SetPosition(int position)
	{
		_binaryReader.SetPosition(position);
	}

	void SetPosition(int value, int seekValue)
	{
		_binaryReader.SetPosition(value, seekValue);
	}

	void CloseFile()
	{
		_binaryReader.CloseFile();
	}

private: 
	
	void Read(void* buffer, size_t size)
	{
		do
		{
			int position = _binaryReader.GetPosition();

			_binaryReader.Read(buffer, size);

			if (_binaryReader.LastReadedCount < 1)
			{
				_binaryReader.SetPosition(position);

				SleepMilliseconds(_sleepValue);
			}

		} while (_binaryReader.LastReadedCount < 1);
	}
};


#endif