#include <libs/assign/v2/test/anon/anon.h>

#include <libs/assign/v2/test/chain/chain.h>
#include <libs/assign/v2/test/chain/convert.h>

#include <libs/assign/v2/test/detail/functor.h>

#include <libs/assign/v2/test/put/modulo_op.h>
#include <libs/assign/v2/test/put/ptr.h>
#include <libs/assign/v2/test/put/modifier.h>
#include <libs/assign/v2/test/put/tuple_refs.h>
#include <libs/assign/v2/test/put/static.h>
#include <libs/assign/v2/test/put/stl.h>

#include <libs/assign/v2/test/put_range/convert.h>

#include <libs/assign/v2/test/type_traits/has_push.h>
#include <libs/assign/v2/test/type_traits/has_value_type.h>
#include <libs/assign/v2/test/type_traits/has_static_size.h>

#include <libs/assign/v2/test/ref/anon.h>
#include <libs/assign/v2/test/ref/convert_traits.h>
#include <libs/assign/v2/test/ref/csv_anon.h>
#include <libs/assign/v2/test/ref/fusion_list.h>
#include <libs/assign/v2/test/ref/generic_anon.h>
#include <libs/assign/v2/test/ref/wrapper.h>

#include <libs/assign/v2/example/tutorial.h>
#include <libs/assign/v2/example/experimental.h>

int main (int argc, char * const argv[]) {

	using namespace test_assign_v2;
    xxx_anon::xxx_anon::test();

    xxx_chain::xxx_chain::test();
    xxx_chain::xxx_convert::test();

    xxx_detail::xxx_functor::test();

    xxx_put::xxx_modulo_op::test();
    xxx_put::xxx_ptr::test();
    xxx_put::xxx_static::test();
    xxx_put::xxx_stl::test();
    xxx_put::xxx_tuple_refs::test();

    xxx_put_range::xxx_convert::test();

    xxx_ref::xxx_anon::test();
    xxx_ref::xxx_convert_traits::test();
    xxx_ref::xxx_csv_anon::test();
    xxx_ref::xxx_fusion_list::test();
    xxx_ref::xxx_generic_anon::test();
    xxx_ref::xxx_wrapper::test();

    xxx_type_traits::xxx_has_push::test();
    xxx_type_traits::xxx_has_value_type::test();
    xxx_type_traits::xxx_has_static_size::test();
	
    {
	    using namespace example_assign_v2;
	    xxx_tutorial::run();
	    xxx_experimental::run();
    }
    return 0;

}
