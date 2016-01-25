#ifndef _INVALID_INDEX_EXCEPTION_H_
#define _INVALID_INDEX_EXCEPTION_H_

#include "../../utils/src/common/types.h"

namespace Base
{
	namespace Collections
	{
		class InvalidIndexException
		{
		public:
			InvalidIndexException(uint maxIndex, uint accessedIndex);
			uint MaxIndex;
			uint AccessedIndex;
		};
	}
}

#endif