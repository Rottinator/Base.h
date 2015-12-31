#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <cstdio>

#include "../../utils/src/common/types.h"
#include "linkedListItem.h"
#include "list.h"
#include "iterators/linkedListIterator.h"

namespace Base
{
	namespace Collections
	{
		template <class T>
		class LinkedList : public List<T>
		{
		private:
			uint _count;
		    __PRIVATE_LINKED_LIST::LinkedListItem<T>* _first;
			__PRIVATE_LINKED_LIST::LinkedListItem<T>* _last;
			LinkedListIterator<T>* _iterator;

		public:
			LinkedList()
			{
				this->_count = 0;
				this->_first = NULL;
				this->_last = NULL;
				this->_iterator = NULL;
			}

			~LinkedList()
			{
				this->Clear();

				if (this->_iterator != NULL)
				{
					delete this->_iterator;
				}
			}

			uint Count()
			{
				return this->_count;
			}

			void Add(T item)
			{
				__PRIVATE_LINKED_LIST::LinkedListItem<T>* newListItem = new __PRIVATE_LINKED_LIST::LinkedListItem<T>(item);
				
				if (this->_first == NULL)
				{
					this->_first = newListItem;
					this->_last = newListItem;
				}
				else
				{
					newListItem->Before = this->_last;
					this->_last->Next = newListItem;
					this->_last = newListItem;
				}

				this->_count++;
			}

			void Remove(T item)
			{
				if (this->_first != NULL)
				{
					__PRIVATE_LINKED_LIST::LinkedListItem<T>* listItem = this->_first;

					while (listItem->Next != NULL)
					{
						if (listItem->Value == item)
						{
							if (listItem->Before != NULL)
							{
								listItem->Before->Next = listItem->Next;
							}
							
							if (listItem->Next != NULL)
							{
								listItem->Next->Before = listItem->Before;
							}
							
							if (listItem == this->_first)
							{
								this->_first = listItem->Next;
							}

							if (listItem == this->_last)
							{
								this->_last = listItem->Before;
							}

							delete listItem;
							this->_count--;
							return;
						}
						else
						{
							listItem = listItem->Next;
						}
					}
				}
			}

			T GetItem(int index)
			{
				if (this->_first == NULL)
				{
					return NULL;
				}

				int indexToLast = this->_count - index;

				__PRIVATE_LINKED_LIST::LinkedListItem<T>* listItem;

				if (index < indexToLast)
				{
					listItem = this->_first;

					for (int i = 0; i < index; i++)
					{
						if (listItem->Next == NULL)
						{
							return NULL;
						}
						else
						{
							listItem = listItem->Next;
						}
					}
				}
				else
				{
					listItem = this->_last;

					for (int i = this->_count; i > indexToLast; i--)
					{
						if (listItem->Before == NULL)
						{
							return NULL;
						}
						else
						{
							listItem = listItem->Before;
						}
					}
				}
				
				if (listItem == NULL)
				{
					return NULL;
				}
				else
				{
					return listItem->Value;
				}
			}

			void Clear()
			{
				__PRIVATE_LINKED_LIST::LinkedListItem<T>* current = this->_first;

				while (current != NULL)
				{
					__PRIVATE_LINKED_LIST::LinkedListItem<T>* next = current->Next;
					delete current;
					current = next;
				}

				this->_first = NULL;
				this->_last = NULL;
				this->_count = 0;
			}
		
			Iterator<T>* GetIterator()
			{
				if (this->_iterator == NULL)
				{
					this->_iterator = new LinkedListIterator<T>(this->_first);
				}

				this->_iterator->Reset();

				return this->_iterator;
			}
		};
	}
}

#endif