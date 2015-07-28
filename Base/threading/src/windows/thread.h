#include <thread>

namespace Base
{
	namespace Threading
	{
		class Thread
		{
		private:
			std::thread _threadObj;
		public:
			Thread(void(*threadFunction) (void*), void* parameter);
			void Start();
		};
	}
}