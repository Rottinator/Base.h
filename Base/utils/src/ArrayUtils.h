#ifndef _ARRAY_UTILS_H_
#define _ARRAY_UTILS_H_

namespace Base
{
	namespace Utils
	{
		class ArrayUtils
		{
		public:
			static void AssignWith0(int* array, int arrayLength);
			static void AssignWith0(char* array, int arrayLength);
			static void AssignWith0(short* array, int arrayLength);
			static void AssignWith0(long* array, int arrayLength);
			static void AssignWith0(float* array, int arrayLength);
			static void AssignWith0(double* array, int arrayLength);
		};
	}
}

#endif