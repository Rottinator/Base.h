#ifndef _STRUCTURE_DEFINITION_HELPER_H_
#define _STRUCTURE_DEFINITION_HELPER_H_

namespace Base
{
	namespace Utils
	{
		class StructureDefinitionHelper
		{
		public:
			
			static int GetIntPropertyValue(void* object, int addressOffset);
			static float GetFloatPropertyValue(void* object, int addressOffset);
			static char* GetStringPropertyValue(void* object, int addressOffset);
			static bool GetBoolPropertyValue(void* object, int addressOffset);
		};
	}
}

#endif