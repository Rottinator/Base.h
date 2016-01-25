#ifndef _MAP_H_
#define _MAP_H_

#include <cstdio>
#include "iterable.h"

#include "../../utils/src/common/types.h"

namespace Base
{
	namespace Collections
	{
		template <class TKey, class TValue>
		class KeyValuePair
		{
		public:
			KeyValuePair(TKey key, TValue value)
			{
				this->Key = key;
				this->Value = value;
			}

			TKey Key;
			TValue Value;
		};

		template <class TKey, class TValue>
		class Map : public Iterable<KeyValuePair<TKey, TValue>>
		{
		public:
			virtual void Add(TKey key, TValue value) = 0;
			virtual void Remove(TKey key) = 0;
			virtual TValue GetValue(TKey key) = 0;
			virtual bool ContainsKey(TKey key) = 0;
			virtual uint Count() = 0;
			virtual void Clear() = 0;
			Iterator<KeyValuePair<TKey, TValue>>* GetIterator() = 0;
		};
	}
}

#endif