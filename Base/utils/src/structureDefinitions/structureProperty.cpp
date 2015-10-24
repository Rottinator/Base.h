#include "structureProperty.h"

namespace Base
{
	namespace Utils
	{
		StructureDataProperty::StructureDataProperty()
		{
			PropertyType = PropertyTypes::DataProperty;
		}

		StructureObjectProperty::StructureObjectProperty()
		{
			PropertyType = PropertyTypes::ObjectProperty;
		}

		StructureDataArrayProperty::StructureDataArrayProperty()
		{
			PropertyType = PropertyTypes::DataArrayProperty;
		}

		StructureObjectArrayProperty::StructureObjectArrayProperty()
		{
			PropertyType = PropertyTypes::ObjectArrayProperty;
		}
	}
}