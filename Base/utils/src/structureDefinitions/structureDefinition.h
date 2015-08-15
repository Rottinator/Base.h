#ifndef _STRUCTURE_DEFINITION_H_
#define _STRUCTURE_DEFINITION_H_

#include "../common/list.h"
#include "structureProperty.h"

namespace Base
{
	namespace Utils
	{
		class StructureDefinition
		{
		public:
			List<StructureProperty>* Properties;
			char* Name;
			int Size;
			StructureDefinition(char* name);
			void AddDataProperty(char* propertyName, DataType dataType);
			void AddObjectProperty(char* propertyName, char* definitionName);
			void AddDataArrayProperty(char* propertyName, DataType dataType);
			void AddObjectArrayProperty(char* propertyName, char* definitionName);
			void CalculatePropertyAddresses();
		private:
			int GetSizeOfDataType(DataType dataType);
			int GetStructureBlockSize();
			void CalculateProperty(StructureProperty* property, int structureBlockSize, int dataSize, int* currentBlock, int* completeOffset);
		};
	}
}

#endif