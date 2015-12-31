#include <cstdio>
#include <cstring>

#include "stringBuilder.h"
#include "arrayUtils.h"
#include "../../../collections/src/linkedList.h"

#pragma warning(disable : 4996)

using namespace Base::Collections;

namespace Base
{
	namespace Utils
	{
		StringBuilder::StringBuilder()
		{
			this->_stringList = new LinkedList<StringContainer*>();
			this->_completeLength = 0;
		}

		StringBuilder::~StringBuilder()
		{
			int stringCount = this->_stringList->Count();

			for (int i = 0; i < stringCount; i++)
			{
				StringContainer* stringContainer = this->_stringList->GetItem(i);

				delete stringContainer->String;
				delete stringContainer;
			}

			delete this->_stringList;
		}

		void StringBuilder::Append(char* string)
		{
			int stringLength = strlen(string);
			char* copy = new char[stringLength+1];
			copy[stringLength] = 0; //Stringende

			strcpy(copy, string);

			StringContainer* container = new StringContainer();
			container->String = copy;
			container->Length = stringLength;

			this->_stringList->Add(container);
			this->_completeLength += stringLength;
		}

		void StringBuilder::Append(char* string, int length, bool copy)
		{
			StringContainer* container = new StringContainer();
			container->Length = length;

			if (copy)
			{
				char* copy = new char[length + 1];
				copy[length] = 0; //Stringende

				strcpy(copy, string);
				container->String = copy;
			}
			else
			{
				container->String = string;
			}

			this->_stringList->Add(container);
			this->_completeLength += length;
		}

		void StringBuilder::Append(int number)
		{
			char numberString[10];
			ArrayUtils::AssignWith0(numberString, 10);

			sprintf(numberString, "%d", number);

			this->Append(numberString);
		}

		void StringBuilder::Append(float number)
		{
			char numberString[10];
			ArrayUtils::AssignWith0(numberString, 10);

			sprintf(numberString, "%f", number);

			this->Append(numberString);
		}
		
		StringContainer* StringBuilder::GetString()
		{
			char* resultString = new char[this->_completeLength+1];
			int stringCount = this->_stringList->Count();
			int offset = 0;

			for (int i = 0; i < stringCount; i++)
			{
				StringContainer* stringContainer = this->_stringList->GetItem(i);
				
				for (int s = 0; s < stringContainer->Length; s++)
				{
					resultString[offset + s] = stringContainer->String[s];
				}

				offset += stringContainer->Length;
			}

			resultString[this->_completeLength] = 0; //Stringende markieren

			StringContainer* stringContainer = new StringContainer();
			stringContainer->String = resultString;
			stringContainer->Length = this->_completeLength;

			return stringContainer;
		}
	}
}