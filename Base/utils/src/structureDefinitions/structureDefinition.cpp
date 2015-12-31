#include "structureDefinition.h"
#include "../common/constants.h"
#include "../../../collections/src/linkedList.h"

namespace Base
{
	namespace Utils
	{
		StructureDefinition::StructureDefinition(char* name)
		{
			Name = name;
			Properties = new LinkedList<StructureProperty*>();
		}

		void StructureDefinition::AddDataProperty(char* propertyName, DataTypes dataType)
		{
			StructureDataProperty* property = new StructureDataProperty();
			property->Name = propertyName;
			property->DataType = dataType;

			Properties->Add(property);
		}

		void StructureDefinition::AddObjectProperty(char* propertyName, char* definitionName)
		{
			StructureObjectProperty* property = new StructureObjectProperty();
			property->Name = propertyName;
			property->StructureDefinitionName = definitionName;

			Properties->Add(property);
		}

		void StructureDefinition::AddDataArrayProperty(char* propertyName, DataTypes dataType)
		{
			StructureDataArrayProperty* property = new StructureDataArrayProperty();
			property->Name = propertyName;
			property->DataType = dataType;
			
			StructureDataProperty* lengthProperty = new StructureDataProperty();
			lengthProperty->DataType = DataTypes::Integer;

			property->LengthProperty = lengthProperty;

			Properties->Add(property);
		}

		void StructureDefinition::AddObjectArrayProperty(char* propertyName, char* definitionName)
		{
			StructureObjectArrayProperty* property = new StructureObjectArrayProperty();
			property->Name = propertyName;
			property->StructureDefinitionName = definitionName;

			StructureDataProperty* lengthProperty = new StructureDataProperty();
			lengthProperty->DataType = DataTypes::Integer;

			property->LengthProperty = lengthProperty;

			Properties->Add(property);
		}

		void StructureDefinition::CalculatePropertyAddresses()
		{
			int propertiesCount = Properties->Count();
			int structureBlockSize = GetStructureBlockSize();			
			
			int currentBlock = 0;
			int completeOffset = 0;

			for (int i = 0; i < propertiesCount; i++)
			{
				StructureProperty* property = Properties->GetItem(i);

				int dataSize;
				
				if (property->PropertyType == PropertyTypes::DataArrayProperty || property->PropertyType == PropertyTypes::ObjectProperty || property->PropertyType == PropertyTypes::ObjectArrayProperty)
				{
					dataSize = POINTER_SIZE;
				}
				else if (property->PropertyType == PropertyTypes::DataProperty)
				{
					StructureDataProperty* dataProperty = (StructureDataProperty*)property;
					dataSize = GetSizeOfDataType(dataProperty->DataType);
				}

				CalculateProperty(property, structureBlockSize, dataSize, &currentBlock, &completeOffset);

				if (property->PropertyType == PropertyTypes::DataArrayProperty)
				{
					StructureDataArrayProperty* dataArrayProperty = (StructureDataArrayProperty*)property;
					dataSize = GetSizeOfDataType(dataArrayProperty->LengthProperty->DataType);
					CalculateProperty(dataArrayProperty->LengthProperty, structureBlockSize, dataSize, &currentBlock, &completeOffset);
				}
				else if (property->PropertyType == PropertyTypes::ObjectArrayProperty)
				{
					StructureObjectArrayProperty* objectArrayProperty = (StructureObjectArrayProperty*)property;
					dataSize = GetSizeOfDataType(objectArrayProperty->LengthProperty->DataType);
					CalculateProperty(objectArrayProperty->LengthProperty, structureBlockSize, dataSize, &currentBlock, &completeOffset);
				}
			}

			Size = completeOffset + (structureBlockSize - currentBlock);
		}

		void StructureDefinition::CalculateProperty(StructureProperty* property, int structureBlockSize, int dataSize, int* currentBlock, int* completeOffset)
		{
			if (dataSize + *currentBlock > structureBlockSize)
			{
				*completeOffset += structureBlockSize - *currentBlock;
				*currentBlock = 0;
			}

			property->AddressOffset = *completeOffset;
			*completeOffset += dataSize;
			*currentBlock += dataSize;
		}

		int StructureDefinition::GetSizeOfDataType(DataTypes dataType)
		{
			switch (dataType)
			{
			case DataTypes::Bool:
				return sizeof(bool);
				break;
			case DataTypes::Integer:
				return sizeof(int);
				break;
			case DataTypes::Float:
				return sizeof(float);
				break;
			case DataTypes::String:
				return sizeof(char*);
				break;
			}

			return 0;
		}

		int StructureDefinition::GetStructureBlockSize()
		{
			int propertiesCount = Properties->Count();
			int structureBlockSize = 0;

			for (int i = 0; i < propertiesCount; i++)
			{
				StructureProperty* property = Properties->GetItem(i);

				if (property->PropertyType == PropertyTypes::DataProperty)
				{
					StructureDataProperty* dataProperty = (StructureDataProperty*)property;
					int dataSize = GetSizeOfDataType(dataProperty->DataType);

					if (dataSize > structureBlockSize)
					{
						structureBlockSize = dataSize;
					}
				}
				else if (property->PropertyType == PropertyTypes::DataArrayProperty)
				{
					StructureDataArrayProperty* dataArrayProperty = (StructureDataArrayProperty*)property;

					if (POINTER_SIZE > structureBlockSize)
					{
						structureBlockSize = POINTER_SIZE;
					}

					int lengthDataTypeSize = GetSizeOfDataType(dataArrayProperty->LengthProperty->DataType);

					if (lengthDataTypeSize > structureBlockSize)
					{
						structureBlockSize = lengthDataTypeSize;
					}
				}
				else if (property->PropertyType == PropertyTypes::ObjectProperty)
				{
					StructureObjectProperty* objectProperty = (StructureObjectProperty*)property;

					if (POINTER_SIZE > structureBlockSize)
					{
						structureBlockSize = POINTER_SIZE;
					}
				}
				else if (property->PropertyType == PropertyTypes::ObjectArrayProperty)
				{
					StructureObjectArrayProperty* objectArrayProperty = (StructureObjectArrayProperty*)property;

					if (POINTER_SIZE > structureBlockSize)
					{
						structureBlockSize = POINTER_SIZE;
					}

					int lengthDataTypeSize = GetSizeOfDataType(objectArrayProperty->LengthProperty->DataType);

					if (lengthDataTypeSize > structureBlockSize)
					{
						structureBlockSize = lengthDataTypeSize;
					}
				}
			}
		
			return structureBlockSize;
		}
	}
}