#ifndef _ITERATOR_H_
#define _ITERATOR_H_

namespace Base
{
	namespace Collections
	{
		template <class T>
		class Iterator
		{
		public:
			virtual bool HasNext() = 0;
			virtual T Next() = 0;
			virtual void Reset() = 0;
		};
	}
}

#endif