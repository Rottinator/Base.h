#ifndef _LINKED_LIST_ITEM_H_
#define _LINKED_LIST_ITEM_H_

#include <cstdio>

#include "list.h"

namespace Base
{
	namespace Collections
	{
		namespace __PRIVATE_LINKED_LIST
		{
			template <class T>
			class LinkedListItem
			{
			public:
				LinkedListItem<T>* Before;
				T Value;
				LinkedListItem<T>* Next;

				LinkedListItem(T value)
				{
					this->Before = NULL;
					this->Value = value;
					this->Next = NULL;
				}
			};
		}
	}
}

#endif