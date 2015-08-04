#ifndef _TEXT_READER_H_
#define _TEXT_READER_H_

namespace Base
{
	namespace IO
	{
		class TextReader
		{
		private:
			FILE* _file;
			bool _eof;
		public:
			int BufferSize;
		public:
			TextReader();
			bool OpenFile(char* filePath);
			char* ReadLine();
			int ReadInteger();
			float ReadFloat();
			bool IsEOF();
			void CloseFile();
		};
	}
}

#endif