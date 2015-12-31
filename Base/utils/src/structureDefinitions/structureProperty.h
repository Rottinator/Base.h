#ifndef _STRUCTURE_PROPERTY_H_
#define _STRUCTURE_PROPERTY_H_

namespace Base
{
	namespace Utils
	{
		enum class DataTypes { Integer = 0, Bool = 1, Float = 2, String = 3 };

		enum class PropertyTypes { DataProperty = 0, ObjectProperty = 1, DataArrayProperty = 2, ObjectArrayProperty = 3 };

		class StructureProperty
		{
		public:
			char* Name;
			PropertyTypes PropertyType;
			int AddressOffset;
		};

		class StructureDataProperty : public StructureProperty
		{
		public:
			StructureDataProperty();
			DataTypes DataType;
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
			DataTypes DataType;
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