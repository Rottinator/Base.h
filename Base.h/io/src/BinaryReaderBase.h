#ifndef _BINARY_READER_BASE_H_
#define _BINARY_READER_BASE_H_

class BinaryReaderBase
{
public:
	virtual bool OpenFile(char* path) = 0;

	virtual char ReadChar() = 0;

	virtual unsigned char ReadUChar() = 0;

	virtual short ReadShort() = 0;

	virtual long ReadLong() = 0;

	virtual int ReadInteger() = 0;

	virtual float ReadFloat() = 0;

	virtual double ReadDouble() = 0;

	virtual void CloseFile() = 0;

	virtual int GetPosition() = 0;

	virtual void SetPosition(int position) = 0;
};

#endif