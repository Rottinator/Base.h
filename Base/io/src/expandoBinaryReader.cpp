#include "expandoBinaryReader.h"
#include "../../utils/utils.h"

namespace Base
{
	namespace IO
	{
		ExpandoBinaryReader::ExpandoBinaryReader(int sleepValue)
		{
			_binaryReader = BinaryReader();
			_sleepValue = sleepValue;
		}

		bool ExpandoBinaryReader::OpenFile(char* path)
		{
			return _binaryReader.OpenFile(path);
		}

		char ExpandoBinaryReader::ReadChar()
		{
			char readValue = 0;

			Read(&readValue, sizeof(char));

			return readValue;
		}

		unsigned char ExpandoBinaryReader::ReadUChar()
		{
			unsigned char readValue = 0;

			Read(&readValue, sizeof(unsigned char));

			return readValue;
		}

		short ExpandoBinaryReader::ReadShort()
		{
			short readValue = 0;

			Read(&readValue, sizeof(short));

			return readValue;
		}

		long ExpandoBinaryReader::ReadLong()
		{
			long readValue = 0;

			Read(&readValue, sizeof(long));

			return readValue;
		}

		int ExpandoBinaryReader::ReadInteger()
		{
			int readValue = 0;

			Read(&readValue, sizeof(int));

			return readValue;
		}

		float ExpandoBinaryReader::ReadFloat()
		{
			float readValue = 0;

			Read(&readValue, sizeof(float));

			return readValue;
		}

		double ExpandoBinaryReader::ReadDouble()
		{
			double readValue = 0;

			Read(&readValue, sizeof(double));

			return readValue;
		}

		int ExpandoBinaryReader::GetPosition()
		{
			return _binaryReader.GetPosition();
		}

		void ExpandoBinaryReader::SetPosition(int position)
		{
			_binaryReader.SetPosition(position);
		}

		void ExpandoBinaryReader::SetPosition(int value, int seekValue)
		{
			_binaryReader.SetPosition(value, seekValue);
		}

		void ExpandoBinaryReader::CloseFile()
		{
			_binaryReader.CloseFile();
		}

		void ExpandoBinaryReader::Read(void* buffer, size_t size)
		{
			do
			{
				int position = _binaryReader.GetPosition();

				_binaryReader.Read(buffer, size);

				if (_binaryReader.LastReadedCount < 1)
				{
					_binaryReader.SetPosition(position);

					Utils::SleepMilliseconds(_sleepValue);
				}

			} while (_binaryReader.LastReadedCount < 1);
		}
	}
}