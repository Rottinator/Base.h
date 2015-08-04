#include <cstdio>
#include <cstring>
#include "textReader.h"

#include "../../../utils/utils.h"

using namespace Base::Utils;

#pragma warning(disable : 4996)

namespace Base
{
	namespace IO
	{
		TextReader::TextReader()
		{
			BufferSize = 512;
			_eof = false;
		}

		bool TextReader::OpenFile(char* filePath)
		{
			_file = fopen(filePath, "r");
			
			if (_file == NULL)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		char* TextReader::ReadLine()
		{
			char* buffer = new char[BufferSize];
			ArrayUtils::AssignWith0(buffer, BufferSize);

			if (fgets(buffer, BufferSize, _file))
			{
				int length = strlen(buffer);
				if (buffer[length - 1] == '\n')
				{
					buffer[length - 1] = '\0';
				}

				return buffer;
			}
			else
			{
				_eof = true;
			}

			return NULL;
		}

		int TextReader::ReadInteger()
		{
			int value;
			if (fscanf(_file, "%d", &value) != EOF)
			{
				return value;
			}
			else
			{
				_eof = true;
			}

			return 0;
		}

		float TextReader::ReadFloat()
		{
			float value;
			if (fscanf(_file, "%f", &value) != EOF)
			{
				return value;
			}
			else
			{
				_eof = true;
			}

			return 0;
		}

		bool TextReader::IsEOF()
		{
			return _eof;
		}

		void TextReader::CloseFile()
		{
			fclose(_file);
		}
	}
}