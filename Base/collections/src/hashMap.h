#ifndef _HASH_MAP_H_
#define _HASH_MAP_H_

#include <unordered_map>

#include "../../utils/src/common/types.h"
#include "iterators/hashMapIterator.h"
#include "map.h"

namespace Base
{
	namespace Collections
	{
		template <class TKey, class TValue>
		class HashMap : public Map<TKey, TValue>
		{
		private:
			std::unordered_map<TKey, TValue> _stdMap;
			HashMapIterator<TKey, TValue>* _iterator;
		public:
			HashMap()
			{
				this->_stdMap = std::unordered_map<TKey, TValue>();
				this->_iterator = NULL;
			}

			~HashMap()
			{
				delete _stdMap;

				if (this->_iterator != NULL)
				{
					delete this->_iterator;
				}
			}

			Iterator<KeyValuePair<TKey, TValue>>* GetIterator()
			{
				if (this->_iterator == NULL)
				{
					this->_iterator = new HashMapIterator<TKey, TValue>(&this->_stdMap);
				}

				this->_iterator->Reset();

				return (Iterator<KeyValuePair<TKey, TValue>>*) this->_iterator;
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
				typename std::unordered_map<TKey, TValue>::iterator itr = this->_stdMap.find(key);

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