#ifndef _HASH_MAP_ITERATOR_H_
#define _HASH_MAP_ITERATOR_H_

#include "iterator.h"
#include "../map.h"
#include <unordered_map>

namespace Base
{
	namespace Collections
	{
		template <class TKey, class TValue>
		class HashMapIterator : public Iterator<KeyValuePair<TKey, TValue>>
		{
		private:
			std::unordered_map<TKey, TValue>* _stdMap;
			typename std::unordered_map<TKey, TValue>::iterator _iterator;

		public:
			HashMapIterator(std::unordered_map<TKey, TValue>* stdMap)
			{
				this->_stdMap = stdMap;
			}

			bool HasNext()
			{
				return this->_iterator != this->_stdMap->end();
			}

			KeyValuePair<TKey, TValue> Next()
			{
				KeyValuePair<TKey, TValue> keyValuePair(this->_iterator->first, this->_iterator->second);

				this->_iterator++;

				return keyValuePair;
			}

			void Reset()
			{
				this->_iterator = _stdMap->begin();
			}
		};
	}
}

#endif