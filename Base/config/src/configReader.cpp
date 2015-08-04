#include <cstdio>
#include <cstring>

#include "configReader.h"
#include "../../utils/utils.h"
#include "../../io/io.h"

using namespace Base::Utils;
using namespace Base::IO;

namespace Base
{
	namespace Config
	{		
		const int ConfigReaderPufferSize = 512;

		ConfigReader::ConfigReader(void* configObject)
		{
			_configEntries = List<ConfigEntry>();
			_currentConfigAddress = (long)configObject;
			_configObjectBlockSize = 0;
		}

		void ConfigReader::AddConfigEntry(char* entryName, DataType dataType)
		{
			ConfigEntry* configEntry = new ConfigEntry();
			configEntry->DataType = dataType;
			configEntry->DataTypeSize = GetSizeOfDataType(dataType);
			configEntry->EntryName = entryName;
			
			if (configEntry->DataTypeSize > _configObjectBlockSize)
			{
				_configObjectBlockSize = configEntry->DataTypeSize;
			}

			_configEntries.Add(configEntry);
		}

		bool ConfigReader::ReadConfig(char* configPath)
		{
			CalculateConfigEntriesAddresses();

			TextReader* textReader = new TextReader();
			
			if (textReader->OpenFile(configPath) == false)
			{
				return false;
			}

			bool success = true;
			while (textReader->IsEOF() == false)
			{
				char* line = textReader->ReadLine();
				if (line != NULL)
				{
					strtrim(line);

					if (strlen(line) > 0)
					{
						ConfigEntry* configEntry = GetConfigEntryByName(line);

						if (configEntry == NULL)
						{
							printf("ConfigReader: Unknown ConfigEntry: \"%s\" found\n", line);
							delete line;
						}
						else
						{
							delete line;
							if (ReadConfigEntryValue(textReader, configEntry) == false)
							{
								success = false;
								break;
							}
						}
					}
				}
			}

			textReader->CloseFile();
			delete textReader;
			return success;
		}

		void ConfigReader::CalculateConfigEntriesAddresses()
		{
			int configEntriesCount = _configEntries.Count();
			int currentBlock = 0;

			for (int i = 0; i < configEntriesCount; i++)
			{
				ConfigEntry* configEntry = _configEntries.GetItem(i);
				
				if (configEntry->DataTypeSize + currentBlock > _configObjectBlockSize)
				{
					_currentConfigAddress += _configObjectBlockSize - currentBlock;
					currentBlock = 0;
				}

				configEntry->ConfigObjectStartAddress = _currentConfigAddress;
				_currentConfigAddress += configEntry->DataTypeSize;
				currentBlock += configEntry->DataTypeSize;
			}
		}

		ConfigEntry* ConfigReader::GetConfigEntryByName(char* name)
		{
			int configEntriesCount = _configEntries.Count();
			for (int i = 0; i < configEntriesCount; i++)
			{
				ConfigEntry* configEntry = _configEntries.GetItem(i);
				if (strcmp(name, configEntry->EntryName) == 0)
				{
					return configEntry;
				}
			}

			return NULL;
		}

		bool ConfigReader::ReadConfigEntryValue(TextReader* reader, ConfigEntry* configEntry)
		{
			switch (configEntry->DataType)
			{
			case DataType::Bool:
			{
				char* value = reader->ReadLine();
				if (reader->IsEOF() == false)
				{
					bool configValue = false;
					strlower(value);
					if (strcmp(value, "true") == 0 || strcmp(value, "yes") == 0 || strcmp(value, "on") == 0 || strcmp(value, "1") == 0)
					{
						configValue = true;
					}

					bool* valuePointer = (bool*)configEntry->ConfigObjectStartAddress;
					*valuePointer = configValue;
					delete value;
				}
			}
				break;
			case DataType::Integer:
			{
				int configValue = reader->ReadInteger();
				if (reader->IsEOF() == false)
				{
					int* valuePointer = (int*)configEntry->ConfigObjectStartAddress;
					*valuePointer = configValue;
				}
			}
				break;
			case DataType::Float:
			{
				float configValue = reader->ReadFloat();
				if (reader->IsEOF() == false)
				{
					float* valuePointer = (float*)configEntry->ConfigObjectStartAddress;
					*valuePointer = configValue;
				}
			}
				break;
			case DataType::String:
			{
				char* value = reader->ReadLine();
				if (reader->IsEOF() == false)
				{
					char** valuePointer = (char**)configEntry->ConfigObjectStartAddress;
					*valuePointer = value;
				}
			}
				break;
			}

			if (reader->IsEOF() == true)
			{
				printf("ConfigReader: No Value Possible for %s\n", configEntry->EntryName);
				return false;
			}

			return true;
		}
		
		int ConfigReader::GetSizeOfDataType(DataType dataType)
		{
			switch (dataType)
			{
			case DataType::Bool:
				return sizeof(bool);
				break;
			case DataType::Integer:
				return sizeof(int);
				break;
			case DataType::Float:
				return sizeof(float);
				break;
			case DataType::String:
				return sizeof(char*);
				break;
			}

			return 0;
		}
	}
}