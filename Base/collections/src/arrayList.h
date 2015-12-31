#ifndef _ARRAY_LIST_H_
#define _ARRAY_LIST_H_

#include <cstdio>

#include "../../utils/src/common/types.h"
#include "list.h"
#include "iterators/arrayIterator.h"

namespace Base
{
	namespace Collections
	{
		template <class T>
		class ArrayList : public List<T>
		{
		private:
			uint _count;
			T* _listItems;
			ArrayIterator<T>* _iterator;
			
		public:
			ArrayList()
			{
				this->_count = 0;
				this->_listItems = NULL;
				this->_iterator = NULL;
			}

			~ArrayList()
			{
				if (this->_listItems != NULL)
				{
					delete this->_listItems;
				}

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
				if (this->_listItems == NULL) 
				{
					this->_listItems = new T;
					this->_listItems[0] = item;
				}
				else
				{
					T* newListItems = new T[this->_count + 1];

					for (uint i = 0; i < this->_count; i++)
					{
						newListItems[i] = this->_listItems[i];
					}

					newListItems[this->_count] = item;
					delete this->_listItems;
					this->_listItems = newListItems;
				}

				this->_count++;
			}

			void Remove(T item)
			{
				T* newListItems = new T[this->_count - 1];
				bool itemFound = false;

				for (uint i = 0; i < this->_count; i++)
				{
					if (this->_listItems[i] == item) 
					{
						itemFound = true;
					}
					else 
					{
						uint index = itemFound ? i - 1 : i;
						newListItems[i] = this->_listItems[i];
					}
				}

				delete this->_listItems;
				this->_listItems = newListItems;
				this->_count--;
			}

			T GetItem(uint index)
			{
				return this->_listItems[index];
			}

			void Clear()
			{
				this->_count = 0;
				delete this->_listItems;
				this->_listItems = NULL;
			}

			Iterator<T>* GetIterator()
			{
				if (this->_iterator == NULL)
				{
					this->_iterator = new ArrayIterator<T>(this->_listItems, this->_count);
				}

				this->_iterator->Reset();

				return this->_iterator;
			}
		};
	}
}

#endif