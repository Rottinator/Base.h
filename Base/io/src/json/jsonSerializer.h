#ifndef _JSON_SERIALIZER_H_
#define _JSON_SERIALIZER_H_

#include "../../../utils/utils.h"

using namespace Base::Utils;

namespace Base
{
	namespace IO
	{
		class JsonSerializer
		{
		public:
			static StringContainer* SerializeObject(char* definitionName, void* object, bool indent);
			static void* DeserializeObject(char* definitionName, char* jsonString);

		private:
			static StringContainer* SerializeObject(char* definitionName, void* object, bool indent, int indentionLevel);
			static char* GetIndentions(int count);
			static void AddDataArrayEntry(StructureDataArrayProperty* dataArrayProperty, int index, StringBuilder* stringBuilder, void* object);
			static void AddDataProperty(StructureDataProperty* dataProperty, StringBuilder* stringBuilder, void* object);
		};
	}
}

#endif