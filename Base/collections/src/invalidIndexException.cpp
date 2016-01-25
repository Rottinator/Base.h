#include "invalidIndexException.h"

namespace Base
{
	namespace Collections
	{
		InvalidIndexException::InvalidIndexException(uint maxIndex, uint accessedIndex)
		{
			this->MaxIndex = maxIndex;
			this->AccessedIndex = accessedIndex;
		}
	}
}