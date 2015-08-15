#ifndef _LIST_H_
#define _LIST_H_

#include <cstdio>

namespace Base
{
	namespace Utils
	{
		template <class T>
		class List
		{
		private:
			int _count;
			T** _listItems;
			
		public:
			void Add(T* item)
			{
				if (_listItems == NULL) {
					_listItems = new T*;
					_listItems[0] = item;
				}
				else
				{
					T** newListItems = new T*[_count + 1];

					for (int i = 0; i < _count; i++)
					{
						newListItems[i] = _listItems[i];
					}

					newListItems[_count] = item;
					delete _listItems;
					_listItems = newListItems;
				}

				_count++;
			}

			void Remove(T* item)
			{
				T** newListItems = new T*[_count - 1];
				bool itemFound = false;

				for (int i = 0; i < _count; i++)
				{
					if (_listItems[i] == item) {
						itemFound = true;
					}
					else {
						int index = itemFound ? i - 1 : i;
						newListItems[i] = _listItems[i];
					}
				}
			}

			T* GetItem(int index)
			{
				return _listItems[index];
			}

			int Count()
			{
				return _count;
			}
		};
	}
}

#endif