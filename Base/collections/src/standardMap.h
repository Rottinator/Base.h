#ifndef _STANDARD_MAP_H_
#define _STANDARD_MAP_H_

#include <map>

#include "../../utils/src/common/types.h"
#include "iterators/standardMapIterator.h"
#include "map.h"

namespace Base
{
	namespace Collections
	{
		template <class TKey, class TValue>
		class StandardMap : public Map<TKey, TValue>
		{
		private:
			std::map<TKey, TValue> _stdMap;
			StandardMapIterator<TKey, TValue>* _iterator;
		public:
			StandardMap()
			{
				this->_stdMap = std::map<TKey, TValue>();
				this->_iterator = NULL;
			}

			~StandardMap()
			{
				if (this->_iterator != NULL)
				{
					delete this->_iterator;
				}
			}

			Iterator<KeyValuePair<TKey, TValue>>* GetIterator()
			{
				if (this->_iterator == NULL)
				{
					this->_iterator = new StandardMapIterator<TKey, TValue>(&this->_stdMap);
				}

				this->_iterator->Reset();

				return (Iterator<KeyValuePair<TKey, TValue>>*)this->_iterator;
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
				typename std::map<TKey, TValue>::iterator itr = this->_stdMap.find(key);

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