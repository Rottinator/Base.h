#ifndef _ARRAY_ITERATOR_H_
#define _ARRAY_ITERATOR_H_

#include "../../../utils/src/common/types.h"
#include "iterator.h"

namespace Base
{
	namespace Collections
	{
		template <class T>
		class ArrayIterator : public Iterator<T>
		{
		private:
			uint _currentIndex;
			uint _count;
			T* _items;

		public:
			ArrayIterator(T* items, uint count)
			{
				this->_currentIndex = 0;
				this->_count = count;
				this->_items = items;
			}

			bool HasNext()
			{
				return this->_currentIndex < count;
			}

			T Next()
			{
				T item = this->_items[this->_currentIndex];

				this->_currentIndex++;

				return item;
			}
			
			void Reset()
			{
				this->_currentIndex = 0;
			}
		};
	}
}

#endif