#ifndef _STRING_BUILDER_H_
#define _STRING_BUILDER_H_

#include "../../../collections/src/linkedList.h"

using namespace Base::Collections;

namespace Base
{
	namespace Utils
	{
		struct StringContainer
		{
			char* String;
			int Length;
		};
		
		class StringBuilder
		{
		private:
			LinkedList<StringContainer*>* _stringList;
			int _completeLength;
		public:
			StringBuilder();
			~StringBuilder();
			void Append(char* string);
			void Append(char* string, int length, bool copy);
			void Append(int number);
			void Append(float number);
			StringContainer* GetString();
		};
	}
}

#endif