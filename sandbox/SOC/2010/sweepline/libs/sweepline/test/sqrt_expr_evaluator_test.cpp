// Boost sweepline library sqrt_expr_evaluator_test.cpp file

//          Copyright Andrii Sydorchuk 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#include <ctime>

#define BOOST_TEST_MODULE sqrt_expr_evaluator_test
#include <boost/random/mersenne_twister.hpp>
#include <boost/test/test_case_template.hpp>

#include "boost/sweepline/voronoi_diagram.hpp"
using namespace boost::sweepline::detail;

template <int N>
struct test_sqrt_evaluator {
    template <typename mpz, typename mpf>
    static bool run() {
        static boost::mt19937 gen(static_cast<unsigned int>(time(NULL)));
        bool ret_val = true;
        static mpz A[N], B[N];
        double a[N], b[N];
        for (int i = 0; i < N; ++i) {
            a[i] = gen() % 1000 - 500;
            int rand_number = gen() % 1000 - 500;
            b[i] = rand_number * rand_number;
        }
        int mask = (1 << N);
        for (int i = 0; i < mask; i++) {
            double expected_val = 0.0;
            for (int j = 0; j < N; j++) {
                if (i & (1 << j)) {
                    A[j] = a[j];
                    B[j] = b[j];
                    expected_val += a[j] * sqrt(b[j]);
                } else {
                    A[j] = -a[j];
                    B[j] = b[j];
                    expected_val -= a[j] * sqrt(b[j]);
                }
            }
            mpf received_val = (sqrt_expr_evaluator<N>::template eval<mpz, mpf>(A, B));
            ret_val &= almost_equal(expected_val, received_val.get_d(), 1);
        }
        return ret_val;
    }
};

BOOST_AUTO_TEST_CASE(mpz_sqrt_evaluator_test) {
    typedef mpt_wrapper<mpz_class, 4> mpz_wrapper_type;
    typedef mpt_wrapper<mpf_class, 1> mpf_wrapper_type;
    for (int i = 0; i < 1000; i++) {
        BOOST_CHECK((test_sqrt_evaluator<1>::run<mpz_class, mpf_class>()));
        BOOST_CHECK((test_sqrt_evaluator<2>::run<mpz_class, mpf_class>()));
        BOOST_CHECK((test_sqrt_evaluator<3>::run<mpz_class, mpf_class>()));
        BOOST_CHECK((test_sqrt_evaluator<4>::run<mpz_class, mpf_class>()));
    }
    for (int i = 0; i < 1000; i++) {
        BOOST_CHECK((test_sqrt_evaluator<1>::run<mpz_wrapper_type, mpf_wrapper_type>()));
        BOOST_CHECK((test_sqrt_evaluator<2>::run<mpz_wrapper_type, mpf_wrapper_type>()));
        BOOST_CHECK((test_sqrt_evaluator<3>::run<mpz_wrapper_type, mpf_wrapper_type>()));
        BOOST_CHECK((test_sqrt_evaluator<4>::run<mpz_wrapper_type, mpf_wrapper_type>()));
    }
}

