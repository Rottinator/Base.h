#ifndef _STRUCTURE_PROPERTY_H_
#define _STRUCTURE_PROPERTY_H_

#include "../common/list.h"

namespace Base
{
	namespace Utils
	{
		enum DataType { Integer = 0, Bool = 1, Float = 2, String = 3 };

		enum PropertyType { DataProperty = 0, ObjectProperty = 1, DataArrayProperty = 2, ObjectArrayProperty = 3 };

		class StructureProperty
		{
		public:
			char* Name;
			PropertyType PropertyType;
			int AddressOffset;
		};

		class StructureDataProperty : public StructureProperty
		{
		public:
			StructureDataProperty();
			DataType DataType;
		};

		class StructureObjectProperty : public StructureProperty
		{
		public:
			StructureObjectProperty();
			char* StructureDefinitionName;
		};

		class StructureDataArrayProperty : public StructureProperty
		{
		public:
			StructureDataArrayProperty();
			DataType DataType;
			StructureDataProperty* LengthProperty;
		};

		class StructureObjectArrayProperty : public StructureProperty
		{
		public:
			StructureObjectArrayProperty();
			char* StructureDefinitionName;
			StructureDataProperty* LengthProperty;
		};
	}
}

#endif