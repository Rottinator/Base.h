#include "arrayUtils.h"

namespace Base
{
	namespace Utils
	{
		void ArrayUtils::AssignWith0(int* array, int arrayLength)
		{
			for (int i = 0; i < arrayLength; i++)
			{
				array[i] = 0;
			}
		}

		void ArrayUtils::AssignWith0(char* array, int arrayLength)
		{
			for (int i = 0; i < arrayLength; i++)
			{
				array[i] = 0;
			}
		}

		void ArrayUtils::AssignWith0(short* array, int arrayLength)
		{
			for (int i = 0; i < arrayLength; i++)
			{
				array[i] = 0;
			}
		}

		void ArrayUtils::AssignWith0(long* array, int arrayLength)
		{
			for (int i = 0; i < arrayLength; i++)
			{
				array[i] = 0;
			}
		}

		void ArrayUtils::AssignWith0(float* array, int arrayLength)
		{
			for (int i = 0; i < arrayLength; i++)
			{
				array[i] = 0;
			}
		}

		void ArrayUtils::AssignWith0(double* array, int arrayLength)
		{
			for (int i = 0; i < arrayLength; i++)
			{
				array[i] = 0;
			}
		}

		bool ArrayUtils::CompareByteArrays(byte* byteArray1, byte* byteArray2, int length)
		{
			for (int i = 0; i < length; i++)
			{
				if (byteArray1[i] != byteArray2[i])
				{
					return false;
				}
			}

			return true;
		}
	}
}