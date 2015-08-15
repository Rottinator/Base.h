#include "jsonSerializer.h"
#include "../../../utils/utils.h"

using namespace Base::Utils;

namespace Base
{
	namespace IO
	{
		StringContainer* JsonSerializer::SerializeObject(char* definitionName, void* object, bool indent)
		{
			return SerializeObject(definitionName, object, indent, 0);
		}

		StringContainer* JsonSerializer::SerializeObject(char* definitionName, void* object, bool indent, int indentionLevel)
		{
			StructureDefinition* structureDefinition = StructureDefinitionStorage::Instance()->GetStructureDefinition(definitionName);
			
			StringBuilder* stringBuilder = new StringBuilder();
			char* indentions;
			if(indent) 
			{
				indentions = GetIndentions(indentionLevel);
				stringBuilder->Append(indentions);
			}
			
			stringBuilder->Append("{");

			if (indent)
			{
				stringBuilder->Append("\n");
			}

			int propertyCount = structureDefinition->Properties->Count();

			char* propertyIndentions;
			if (indent)
			{
				propertyIndentions = GetIndentions(indentionLevel + 1);
			}

			for (int i = 0; i < propertyCount; i++)
			{
				StructureProperty* property = structureDefinition->Properties->GetItem(i);

				if (indent)
				{
					stringBuilder->Append(propertyIndentions);
				}

				stringBuilder->Append("\"");
				stringBuilder->Append(property->Name);
				stringBuilder->Append("\":");

				if (indent)
				{
					stringBuilder->Append(" ");
				}
				
				if (property->PropertyType == PropertyType::DataProperty)
				{
					StructureDataProperty* dataProperty = (StructureDataProperty*)property;
					
					AddDataProperty(dataProperty, stringBuilder, object);
				}
				else if (property->PropertyType == PropertyType::ObjectProperty)
				{
					StructureObjectProperty* objectProperty = (StructureObjectProperty*)property;

					void** subObjectPointer = (void**)((long)object + objectProperty->AddressOffset);

					StringContainer* objectString = SerializeObject(objectProperty->StructureDefinitionName, *subObjectPointer, indent, indentionLevel + 1);

					stringBuilder->Append(objectString->String, objectString->Length, false);

					delete objectString;
				}
				else if (property->PropertyType == PropertyType::DataArrayProperty)
				{
					char* arrayIndentions;
					if (indent)
					{
						arrayIndentions = GetIndentions(indentionLevel + 2);
					}

					StructureDataArrayProperty* dataArrayProperty = (StructureDataArrayProperty*)property;

					stringBuilder->Append("[");

					if (indent)
					{
						stringBuilder->Append("\n");
					}

					int arrayLength = StructureDefinitionHelper::GetIntPropertyValue(object, dataArrayProperty->LengthProperty->AddressOffset);

					for (int a = 0; a < arrayLength; a++)
					{
						if (indent)
						{
							stringBuilder->Append(arrayIndentions);
						}

						AddDataArrayEntry(dataArrayProperty, a, stringBuilder, object);
						if (a + 1 < arrayLength)
						{
							stringBuilder->Append(",");
						}

						if (indent)
						{
							stringBuilder->Append("\n");
						}
					}

					if (indent)
					{
						stringBuilder->Append(propertyIndentions);
					}

					stringBuilder->Append("]");

					if (indent)
					{
						delete arrayIndentions;
					}					
				}
				else if(property->PropertyType == PropertyType::ObjectArrayProperty)
				{
					char* arrayIndentions;
					if (indent)
					{
						arrayIndentions = GetIndentions(indentionLevel + 2);
					}

					StructureObjectArrayProperty* objectArrayProperty = (StructureObjectArrayProperty*)property;

					stringBuilder->Append("[");

					if (indent)
					{
						stringBuilder->Append("\n");
					}

					int arrayLength = StructureDefinitionHelper::GetIntPropertyValue(object, objectArrayProperty->LengthProperty->AddressOffset);

					for (int a = 0; a < arrayLength; a++)
					{
						void*** subObjectPointer = (void***)((long)object + objectArrayProperty->AddressOffset);
						long subObjectArrayAddress = (long)(*subObjectPointer);
						subObjectArrayAddress += i*POINTER_SIZE;

						StringContainer* objectString = SerializeObject(objectArrayProperty->StructureDefinitionName, *((void**)subObjectArrayAddress), indent, indentionLevel + 2);

						stringBuilder->Append(objectString->String, objectString->Length, false);

						if (a + 1 < arrayLength)
						{
							stringBuilder->Append(",");
						}

						if (indent)
						{
							stringBuilder->Append("\n");
						}

						delete objectString;
					}

					if (indent)
					{
						stringBuilder->Append(propertyIndentions);
					}

					stringBuilder->Append("]");

					if (indent)
					{
						delete arrayIndentions;
					}					
				}
			
				if (i + 1 < propertyCount)
				{
					stringBuilder->Append(",");
				}

				if (indent)
				{
					stringBuilder->Append("\n");
				}
			}

			if (indent)
			{
				stringBuilder->Append(indentions);
			}

			stringBuilder->Append("}");

			StringContainer* resultString = stringBuilder->GetString();
			
			if (indent)
			{
				delete propertyIndentions;
				delete indentions;
			}

			delete stringBuilder;
			return resultString;
		}

		void JsonSerializer::AddDataProperty(StructureDataProperty* dataProperty, StringBuilder* stringBuilder, void* object)
		{
			switch (dataProperty->DataType)
			{
			case DataType::Bool:
			{
				bool boolValue = StructureDefinitionHelper::GetBoolPropertyValue(object, dataProperty->AddressOffset);
				if (boolValue)
				{
					stringBuilder->Append("true");
				}
				else
				{
					stringBuilder->Append("false");
				}
				break;
			}
			case DataType::Integer:
			{
				int intValue = StructureDefinitionHelper::GetIntPropertyValue(object, dataProperty->AddressOffset);
				stringBuilder->Append(intValue);
				break;
			}
			case DataType::Float:
			{
				float floatValue = StructureDefinitionHelper::GetFloatPropertyValue(object, dataProperty->AddressOffset);
				stringBuilder->Append(floatValue);
				break;
			}
			case DataType::String:
			{
				char* charValue = StructureDefinitionHelper::GetStringPropertyValue(object, dataProperty->AddressOffset);
				stringBuilder->Append("\"");
				stringBuilder->Append(charValue);
				stringBuilder->Append("\"");
				break;
			}
			}
		}

		void JsonSerializer::AddDataArrayEntry(StructureDataArrayProperty* dataArrayProperty, int index, StringBuilder* stringBuilder, void* object)
		{
			long address = ((long)object + dataArrayProperty->AddressOffset);

			switch (dataArrayProperty->DataType)
			{
			case DataType::Bool:
			{
				bool** boolPointer = (bool**)address;
				bool boolValue = (*boolPointer)[index];

				if (boolValue)
				{
					stringBuilder->Append("true");
				}
				else
				{
					stringBuilder->Append("false");
				}
				break;
			}
			case DataType::Integer:
			{
				int** intPointer = (int**)address;
				int intValue = (*intPointer)[index];
				stringBuilder->Append(intValue);
				break;
			}
			case DataType::Float:
			{
				float** floatPointer = (float**)address;
				float floatValue = (*floatPointer)[index];
				stringBuilder->Append(floatValue);
				break;
			}
			case DataType::String:
			{
				char*** charPointer = (char***)address;
				char* charValue = (*charPointer)[index];
				stringBuilder->Append("\"");
				stringBuilder->Append(charValue);
				stringBuilder->Append("\"");
				break;
			}
			}
		}

		char* JsonSerializer::GetIndentions(int count)
		{
			char* indentions = new char[count + 1];
			ArrayUtils::AssignWith0(indentions, count+1);

			for (int i = 0; i < count; i++)
			{
				indentions[i] = '\t';
			}

			return indentions;
		}

		void* JsonSerializer::DeserializeObject(char* definitionName, char* jsonString)
		{
			return NULL;
		}
	}
}