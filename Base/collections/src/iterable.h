#ifndef _ITERABLE_H_
#define _ITERABLE_H_

#include "iterators/iterator.h"

namespace Base
{
	namespace Collections
	{
		template <class T>
		class Iterable
		{
		public:
			virtual Iterator<T>* GetIterator() = 0;
		};
	}
}

#endif