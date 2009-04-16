#include "boost/tp/default_pool.hpp"

#include <boost/thread.hpp>

#include "boost/tp/poolsize.hpp"

namespace boost { namespace tp {
namespace detail
{
default_pool
static_pool::instance( poolsize( thread::hardware_concurrency() ) );
}
} }