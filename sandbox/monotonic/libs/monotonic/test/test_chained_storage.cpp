
#include <boost/monotonic/chained_storage.h>

void test_chained_storage()
{
	monotonic::chained_storage<10> store;
	{
		std::vector<char, monotonic::allocator<char> > vec(store);
		vec.resize(5);
		vec.resize(500);
	}
}

//EOF
