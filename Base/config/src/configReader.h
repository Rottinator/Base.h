#ifndef _CONFIG_READER_H_
#define _CONFIG_READER_H_

#include "../../utils/utils.h"
#include "../../io/io.h"

using namespace Base::Utils;
using namespace Base::IO;

namespace Base
{
	namespace Config
	{
		struct ConfigEntry
		{
			char* EntryName;
			DataType DataType;
			int DataTypeSize;
			long ConfigObjectStartAddress;
		};

		class ConfigReader
		{
		private:
			long _currentConfigAddress;
			int _configObjectBlockSize;
			List<ConfigEntry> _configEntries;
		public:
			ConfigReader(void* configObject);
			void AddConfigEntry(char* entryName, DataType dataType);
			bool ReadConfig(char* configPath);
		private:
			void CalculateConfigEntriesAddresses();
			int ConfigReader::GetSizeOfDataType(DataType dataType);
			ConfigEntry* GetConfigEntryByName(char* name);
			bool ReadConfigEntryValue(TextReader* reader, ConfigEntry* configEntry);
		};
	}
}

#endif