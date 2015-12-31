#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <cstdio>

#include "../../utils/src/common/types.h"
#include "iterable.h"
#include "iterators/arrayIterator.h"

namespace Base
{
	namespace Collections
	{
		template <class T>
		class Array : public Iterable<T>
		{
		private:
			uint _count;
			T* _items;
			ArrayIterator<T>* _iterator;

		public:
			Array(uint size)
			{
				this->_iterator = NULL;
				this->_count = size;
				this->_items = new T[size];
			}

			~Array()
			{
				delete this->_items;

				if (this->_iterator != NULL)
				{
					delete this->_iterator;
				}
			}

			uint Count()
			{
				return this->_count;
			}

			Iterator<T>* GetIterator()
			{
				if (this->_iterator == NULL)
				{
					this->_iterator = new ArrayIterator<T>(this->_items, this->_count);
				}

				this->_iterator->Reset();

				return this->_iterator;
			}
		};
	}
}

#endif