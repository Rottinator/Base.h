#ifndef _MAP_H_
#define _MAP_H_

#include <cstdio>

#include "../../utils/src/common/types.h"

namespace Base
{
	namespace Collections
	{
		template <class TKey, class TValue>
		class Map
		{
		public:
			virtual void Add(TKey key, TValue value) = 0;
			virtual void Remove(TKey key) = 0;
			virtual TValue GetValue(TKey key) = 0;
			virtual bool ContainsKey(TKey key) = 0;
			virtual uint Count() = 0;
			virtual void Clear() = 0;
		};
	}
}

#endif