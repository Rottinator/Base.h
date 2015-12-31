#ifndef _STRUCTURE_DEFINITION_H_
#define _STRUCTURE_DEFINITION_H_

#include "../../../collections/src/linkedList.h"
#include "structureProperty.h"

using namespace Base::Collections;

namespace Base
{
	namespace Utils
	{
		class StructureDefinition
		{
		public:
			LinkedList<StructureProperty*>* Properties;
			char* Name;
			int Size;
			StructureDefinition(char* name);
			void AddDataProperty(char* propertyName, DataTypes dataType);
			void AddObjectProperty(char* propertyName, char* definitionName);
			void AddDataArrayProperty(char* propertyName, DataTypes dataType);
			void AddObjectArrayProperty(char* propertyName, char* definitionName);
			void CalculatePropertyAddresses();
		private:
			int GetSizeOfDataType(DataTypes dataType);
			int GetStructureBlockSize();
			void CalculateProperty(StructureProperty* property, int structureBlockSize, int dataSize, int* currentBlock, int* completeOffset);
		};
	}
}

#endif