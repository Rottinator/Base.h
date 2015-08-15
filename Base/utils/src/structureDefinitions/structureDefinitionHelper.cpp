#include "structureDefinitionHelper.h"

namespace Base
{
	namespace Utils
	{
		int StructureDefinitionHelper::GetIntPropertyValue(void* object, int addressOffset)
		{
			long address = (long)object;
			address += addressOffset;

			int* valuePointer = (int*)address;

			return *valuePointer;
		}

		float StructureDefinitionHelper::GetFloatPropertyValue(void* object, int addressOffset)
		{
			long address = (long)object;
			address += addressOffset;

			float* valuePointer = (float*)address;

			return *valuePointer;
		}

		char* StructureDefinitionHelper::GetStringPropertyValue(void* object, int addressOffset)
		{
			long address = (long)object;
			address += addressOffset;

			char** valuePointer = (char**)address;

			return *valuePointer;
		}

		bool StructureDefinitionHelper::GetBoolPropertyValue(void* object, int addressOffset)
		{
			long address = (long)object;
			address += addressOffset;

			bool* valuePointer = (bool*)address;

			return *valuePointer;
		}
	}
}