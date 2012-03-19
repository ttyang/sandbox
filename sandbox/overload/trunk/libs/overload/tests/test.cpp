
#include <iostream>

 

#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>
#include <boost/detail/lightweight_test.hpp>

#define BOOST_OVERLOAD_ENABLE_LAMBDA_SUPPORT
#include <boost/overload.hpp>

#include "test/functors.hpp"


namespace ovld = boost::overloads;
namespace ovdtl = boost::overloads::detail;
using boost::is_same;




#include "test/trait_by_index.hpp"
#include "test/trait_by_signature.hpp"
#include "test/trait_by_functor.hpp"
#include "test/metafunctions.hpp"
#include "test/get_signature.hpp"
#include "test/signature_deduction.hpp"
#include "test/idx_and_sig_methods.hpp"
#include "test/free_and_member_functions.hpp"
#include "test/signature_with_ptr_ref.hpp"
#include "test/set_target.hpp"
#include "test/compatible_signatures.hpp"
#include "test/function_object_with_state.hpp"
#include "test/assignment.hpp"
#include "test/contains.hpp"
#include "test/test_target.hpp"
#include "test/as_functor.hpp"
#include "test/make_overload.hpp"
#include "test/result.hpp"
#include "test/lambda_result_type_support.hpp"
#include "test/bind_and_lambda.hpp"



int main()
{

    signature_deduction_test();
    index_and_signature_methods_test();
    free_and_member_overloaded_functions_test();
    signature_with_ptr_and_ref_test();
    set_target_test();
    compatible_signature_test();
    func_object_with_state_test();
    assignment_test();
    contains_test();
    test_target_test();
    as_functor_test();
    make_overload_test();
    lambda_support_test();
    lambda_test();
    bind_test();

    return boost::report_errors();
}

