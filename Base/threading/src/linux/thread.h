#include <pthread.h>

namespace Base
{
	namespace Threading
	{
		class Thread
		{
		private:
			pthread_t _pthread;
		public:
			Thread(void(*threadFunction) (void*), void* parameter);
			void Start();
		};
	}
}