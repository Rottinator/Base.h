#include <cstring>
#include "structureDefinitionStorage.h"
#include "../../../collections/src/linkedList.h"

using namespace Base::Collections;

namespace Base
{
	namespace Utils
	{
		StructureDefinitionStorage* StructureDefinitionStorage::_instance = NULL;

		StructureDefinitionStorage::StructureDefinitionStorage()
		{
			_structureDefinitions = new LinkedList<StructureDefinition*>();
		}

		StructureDefinitionStorage* StructureDefinitionStorage::Instance()
		{
			if (_instance == NULL)
			{
				_instance = new StructureDefinitionStorage();
			}

			return _instance;
		}

		void StructureDefinitionStorage::StoreStructureDefinition(StructureDefinition* definition)
		{
			_structureDefinitions->Add(definition);
		}

		StructureDefinition* StructureDefinitionStorage::GetStructureDefinition(char* name)
		{
			int count = _structureDefinitions->Count();

			for (int i = 0; i < count; i++)
			{
				StructureDefinition* structureDefinition = _structureDefinitions->GetItem(i);

				if (strcmp(structureDefinition->Name, name) == 0)
				{
					return structureDefinition;
				}
			}

			return NULL;
		}
	}
}