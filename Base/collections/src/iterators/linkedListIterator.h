#ifndef _LINKED_LIST_ITERATOR_H_
#define _LINKED_LIST_ITERATOR_H_

#include "iterator.h"
#include "../linkedListItem.h"

namespace Base
{
	namespace Collections
	{
		template <class T>
		class LinkedListIterator : public Iterator<T>
		{
		private:
			__PRIVATE_LINKED_LIST::LinkedListItem<T>* _current;
			__PRIVATE_LINKED_LIST::LinkedListItem<T>* _first;

		public:
			LinkedListIterator(__PRIVATE_LINKED_LIST::LinkedListItem<T>* first)
			{
				this->_current = first;
				this->_first = first;
			}

			bool HasNext()
			{
				return this->_current != NULL;
			}

			T Next()
			{
				T item = this->_current->Value;

				this->_current = this->_current->Next;

				return item;
			}

			void Reset()
			{
				this->_current = this->_first;
			}
		};
	}
}

#endif