#ifndef _STRUCTURE_DEFINITION_STORAGE_H_
#define _STRUCTURE_DEFINITION_STORAGE_H_

#include "../../../collections/src/linkedList.h"
#include "structureDefinition.h"

namespace Base
{
	namespace Utils
	{
		class StructureDefinitionStorage
		{
		private:
			static StructureDefinitionStorage* _instance;
			LinkedList<StructureDefinition*>* _structureDefinitions;
			StructureDefinitionStorage();
		public:
			static StructureDefinitionStorage* Instance();
			void StoreStructureDefinition(StructureDefinition* definition);
			StructureDefinition* GetStructureDefinition(char* name);
		};
	}
}

#endif