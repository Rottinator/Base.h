#include "structureProperty.h"

namespace Base
{
	namespace Utils
	{
		StructureDataProperty::StructureDataProperty()
		{
			PropertyType = PropertyType::DataProperty;
		}

		StructureObjectProperty::StructureObjectProperty()
		{
			PropertyType = PropertyType::ObjectProperty;
		}

		StructureDataArrayProperty::StructureDataArrayProperty()
		{
			PropertyType = PropertyType::DataArrayProperty;
		}

		StructureObjectArrayProperty::StructureObjectArrayProperty()
		{
			PropertyType = PropertyType::ObjectArrayProperty;
		}
	}
}