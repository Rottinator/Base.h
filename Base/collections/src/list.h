#ifndef _LIST_H_
#define _LIST_H_

#include "../../utils/src/common/types.h"
#include "iterable.h"

namespace Base
{
	namespace Collections
	{
		template <class T>
		class List : public Iterable<T>
		{
		protected:
			virtual T& GetRefItem(uint index) = 0;
		public:
			virtual uint Count() = 0;
			virtual void Add(T item) = 0;
			virtual void Remove(T item) = 0;
			virtual void Clear() = 0;
			Iterator<T>* GetIterator() = 0;
			
			T GetItem(uint index)
			{
				return this->GetRefItem(index);
			}

			T& operator[] (uint index)
			{
				return this->GetRefItem(index);
			}
		};
	}
}

#endif