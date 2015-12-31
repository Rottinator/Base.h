#ifndef _HASH_MAP_H_
#define _HASH_MAP_H_

#include <unordered_map>

#include "../../utils/src/common/types.h"
#include "map.h"

namespace Base
{
	namespace Collections
	{
		template <class TKey, class TValue>
		class StandardMap : public Map<TKey, TValue>
		{
		private:
			std::unordered_map<TKey, TValue>* _stdMap;
		public:
			StandardMap()
			{
				this->_stdMap = new std::unordered_map<TKey, TValue>();
			}

			uint Count()
			{
				return this->_stdMap.size();
			}

			void Add(TKey key, TValue value)
			{
				this->_stdMap[key] = value;
			}

			void Remove(TKey key)
			{
				this->_stdMap.erase(key);
			}

			TValue GetValue(TKey key)
			{
				return this->_stdMap[key];
			}

			bool ContainsKey(TKey key)
			{
				std::map<TKey, TValue>::iterator itr = this->_stdMap.find(key);

				return itr != this->_stdMap.end();
			}

			void Clear()
			{
				this->_stdMap.clear();
			}
		};
	}
}

#endif