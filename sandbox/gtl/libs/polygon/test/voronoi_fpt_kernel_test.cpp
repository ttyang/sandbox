// Boost.Polygon library voronoi_fpt_kernel_test.cpp file

//          Copyright Andrii Sydorchuk 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#include <cmath>
#include <ctime>
#include <vector>

#define BOOST_TEST_MODULE voronoi_fpt_kernel_test
#include <boost/mpl/list.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/test/test_case_template.hpp>

#include "boost/polygon/detail/voronoi_fpt_kernel.hpp"
#include "boost/polygon/detail/voronoi_calc_kernel.hpp"
using namespace boost::polygon::detail;

typedef boost::mpl::list<double, mpf_class, mpt_wrapper<mpf_class, 8> > test_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(robust_fpt_constructors_test1, T, test_types) {
    typedef robust_fpt<T> rfpt_type;
    rfpt_type a = rfpt_type();
    BOOST_CHECK_EQUAL(a.fpv() == static_cast<T>(0), true);
    BOOST_CHECK_EQUAL(a.re() == 0.0, true);
    BOOST_CHECK_EQUAL(a.ulp() == 0, true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(robust_fpt_constructors_test2, T, test_types) {
    typedef robust_fpt<T> rfpt_type;
    rfpt_type a(static_cast<T>(10));
    BOOST_CHECK_EQUAL(a.fpv() == static_cast<T>(10), true);
    BOOST_CHECK_EQUAL(a.re() == 1.0, true);
    BOOST_CHECK_EQUAL(a.ulp() == 1.0, true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(robust_fpt_constructors_test3, T, test_types) {
    typedef robust_fpt<T> rfpt_type;
    rfpt_type a(static_cast<T>(10), false);
    BOOST_CHECK_EQUAL(a.fpv() == static_cast<T>(10), true);
    BOOST_CHECK_EQUAL(a.re() == 0.0, true);
    BOOST_CHECK_EQUAL(a.ulp() == 0.0, true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(robust_fpt_constructors_test4, T, test_types) {
    typedef robust_fpt<T> rfpt_type;
    rfpt_type a(static_cast<T>(10), 3.0);
    BOOST_CHECK_EQUAL(a.fpv() == static_cast<T>(10), true);
    BOOST_CHECK_EQUAL(a.re() == 3.0, true);
    BOOST_CHECK_EQUAL(a.ulp() == 3.0, true);

    rfpt_type b(static_cast<T>(10), 2.75);
    BOOST_CHECK_EQUAL(b.fpv() == static_cast<T>(10), true);
    BOOST_CHECK_EQUAL(b.re() == 2.75, true);
    BOOST_CHECK_EQUAL(b.ulp() == 2.75, true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(robust_fpt_sum_test1, T, test_types) {
    typedef robust_fpt<T> rfpt_type;
    rfpt_type a(static_cast<T>(2), 5.0);
    rfpt_type b(static_cast<T>(3), 4.0);
    rfpt_type c = a + b;
    BOOST_CHECK_EQUAL(c.fpv() == static_cast<T>(5), true);
    BOOST_CHECK_EQUAL(c.re() == 6.0, true);
    BOOST_CHECK_EQUAL(c.ulp() == 6.0, true);

    c += b;
    BOOST_CHECK_EQUAL(c.fpv() == static_cast<T>(8), true);
    BOOST_CHECK_EQUAL(c.re() == 7.0, true);
    BOOST_CHECK_EQUAL(c.ulp() == 7.0, true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(robust_fpt_sum_test2, T, test_types) {
    typedef robust_fpt<T> rfpt_type;
    rfpt_type a(static_cast<T>(3), 2.0);
    rfpt_type b(static_cast<T>(-2), 3.0);
    rfpt_type c = a + b;
    BOOST_CHECK_EQUAL(c.fpv() == static_cast<T>(1), true);
    BOOST_CHECK_EQUAL(c.re() == 13.0, true);
    BOOST_CHECK_EQUAL(c.ulp() == 13.0, true);

    c += b;
    BOOST_CHECK_EQUAL(c.fpv() == static_cast<T>(-1), true);
    BOOST_CHECK_EQUAL(c.re() == 20.0, true);
    BOOST_CHECK_EQUAL(c.ulp() == 20.0, true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(robust_fpt_dif_test1, T, test_types) {
    typedef robust_fpt<T> rfpt_type;
    rfpt_type a(static_cast<T>(2), 5.0);
    rfpt_type b(static_cast<T>(-3), 4.0);
    rfpt_type c = a - b;
    BOOST_CHECK_EQUAL(c.fpv() == static_cast<T>(5), true);
    BOOST_CHECK_EQUAL(c.re() == 6.0, true);
    BOOST_CHECK_EQUAL(c.ulp() == 6.0, true);

    c -= b;
    BOOST_CHECK_EQUAL(c.fpv() == static_cast<T>(8), true);
    BOOST_CHECK_EQUAL(c.re() == 7.0, true);
    BOOST_CHECK_EQUAL(c.ulp() == 7.0, true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(robust_fpt_dif_test2, T, test_types) {
    typedef robust_fpt<T> rfpt_type;
    rfpt_type a(static_cast<T>(3), 2.0);
    rfpt_type b(static_cast<T>(2), 3.0);
    rfpt_type c = a - b;
    BOOST_CHECK_EQUAL(c.fpv() == static_cast<T>(1), true);
    BOOST_CHECK_EQUAL(c.re() == 13.0, true);
    BOOST_CHECK_EQUAL(c.ulp() == 13.0, true);

    c -= b;
    BOOST_CHECK_EQUAL(c.fpv() == static_cast<T>(-1), true);
    BOOST_CHECK_EQUAL(c.re() == 20.0, true);
    BOOST_CHECK_EQUAL(c.ulp() == 20.0, true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(robust_fpt_mult_test3, T, test_types) {
    typedef robust_fpt<T> rfpt_type;
    rfpt_type a(static_cast<T>(2), 3.0);
    rfpt_type b(static_cast<T>(4));
    rfpt_type c = a * b;
    BOOST_CHECK_EQUAL(c.fpv() == static_cast<T>(8), true);
    BOOST_CHECK_EQUAL(c.re() == 5.0, true);
    BOOST_CHECK_EQUAL(c.ulp() == 5.0, true);

    c *= b;
    BOOST_CHECK_EQUAL(c.fpv() == static_cast<T>(32), true);
    BOOST_CHECK_EQUAL(c.re() == 7.0, true);
    BOOST_CHECK_EQUAL(c.ulp() == 7.0, true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(robust_fpt_div_test1, T, test_types) {
    typedef robust_fpt<T> rfpt_type;
    rfpt_type a(static_cast<T>(2), 3.0);
    rfpt_type b(static_cast<T>(4));
    rfpt_type c = a / b;
    BOOST_CHECK_EQUAL(c.fpv() == static_cast<T>(0.5), true);
    BOOST_CHECK_EQUAL(c.re() == 5.0, true);
    BOOST_CHECK_EQUAL(c.ulp() == 5.0, true);

    c /= b;
    BOOST_CHECK_EQUAL(c.fpv() == static_cast<T>(0.125), true);
    BOOST_CHECK_EQUAL(c.re() == 7.0, true);
    BOOST_CHECK_EQUAL(c.ulp() == 7.0, true);
}

BOOST_AUTO_TEST_CASE(robust_dif_constructors_test) {
    robust_dif<int> rd1;
    BOOST_CHECK_EQUAL(rd1.pos(), 0);
    BOOST_CHECK_EQUAL(rd1.neg(), 0);
    BOOST_CHECK_EQUAL(rd1.dif(), 0);

    robust_dif<int> rd2(1);
    BOOST_CHECK_EQUAL(rd2.pos(), 1);
    BOOST_CHECK_EQUAL(rd2.neg(), 0);
    BOOST_CHECK_EQUAL(rd2.dif(), 1);

    robust_dif<int> rd3(-1);
    BOOST_CHECK_EQUAL(rd3.pos(), 0);
    BOOST_CHECK_EQUAL(rd3.neg(), 1);
    BOOST_CHECK_EQUAL(rd3.dif(), -1);

    robust_dif<int> rd4(1, 2);
    BOOST_CHECK_EQUAL(rd4.pos(), 1);
    BOOST_CHECK_EQUAL(rd4.neg(), 2);
    BOOST_CHECK_EQUAL(rd4.dif(), -1);
}

BOOST_AUTO_TEST_CASE(robust_dif_operators_test1) {
    robust_dif<int> a(5, 2), b(1, 10);
    int dif_a = a.dif();
    int dif_b = b.dif();
    robust_dif<int> sum = a + b;
    robust_dif<int> dif = a - b;
    robust_dif<int> mult = a * b;
    robust_dif<int> umin = -a;
    BOOST_CHECK_EQUAL(sum.dif(), dif_a + dif_b);
    BOOST_CHECK_EQUAL(dif.dif(), dif_a - dif_b);
    BOOST_CHECK_EQUAL(mult.dif(), dif_a * dif_b);
    BOOST_CHECK_EQUAL(umin.dif(), -dif_a);
}

BOOST_AUTO_TEST_CASE(robust_dif_operators_test2) {
    robust_dif<int> a(5, 2);
    for (int b = -3; b <= 3; b += 6) {
        int dif_a = a.dif();
        int dif_b = b;
        robust_dif<int> sum = a + b;
        robust_dif<int> dif = a - b;
        robust_dif<int> mult = a * b;
        robust_dif<int> div = a / b;
        BOOST_CHECK_EQUAL(sum.dif(), dif_a + dif_b);
        BOOST_CHECK_EQUAL(dif.dif(), dif_a - dif_b);
        BOOST_CHECK_EQUAL(mult.dif(), dif_a * dif_b);
        BOOST_CHECK_EQUAL(div.dif(), dif_a / dif_b);
    }
}

BOOST_AUTO_TEST_CASE(robust_dif_operators_test3) {
    robust_dif<int> b(5, 2);
    for (int a = -3; a <= 3; a += 6) {
        int dif_a = a;
        int dif_b = b.dif();
        robust_dif<int> sum = a + b;
        robust_dif<int> dif = a - b;
        robust_dif<int> mult = a * b;
        BOOST_CHECK_EQUAL(sum.dif(), dif_a + dif_b);
        BOOST_CHECK_EQUAL(dif.dif(), dif_a - dif_b);
        BOOST_CHECK_EQUAL(mult.dif(), dif_a * dif_b);
    }
}

BOOST_AUTO_TEST_CASE(robust_dif_operators_test4) {
    std::vector< robust_dif<int> > a4(4, robust_dif<int>(5, 2));
    std::vector< robust_dif<int> > b4(4, robust_dif<int>(1, 2));
    std::vector< robust_dif<int> > c4 = a4;
    c4[0] += b4[0];
    c4[1] -= b4[1];
    c4[2] *= b4[2];
    BOOST_CHECK_EQUAL(c4[0].dif(), a4[0].dif() + b4[0].dif());
    BOOST_CHECK_EQUAL(c4[1].dif(), a4[1].dif() - b4[1].dif());
    BOOST_CHECK_EQUAL(c4[2].dif(), a4[2].dif() * b4[2].dif());
    a4[0] += b4[0].dif();
    a4[1] -= b4[1].dif();
    a4[2] *= b4[2].dif();
    a4[3] /= b4[3].dif();
    BOOST_CHECK_EQUAL(c4[0].dif(), a4[0].dif());
    BOOST_CHECK_EQUAL(c4[1].dif(), a4[1].dif());
    BOOST_CHECK_EQUAL(c4[2].dif(), a4[2].dif());
    BOOST_CHECK_EQUAL(c4[3].dif() / b4[3].dif(), a4[3].dif());
}

template <typename mpz, typename mpf>
class sqrt_expr_tester {
public:
    bool run() {
        static boost::mt19937 gen(static_cast<unsigned int>(time(NULL)));
        bool ret_val = true;
        for (int i = 0; i < MX_SQRTS; ++i) {
            a[i] = gen() % 1000000;
            double random_int = gen() % 1000000;
            b[i] = random_int * random_int;
        }
        int mask = (1 << MX_SQRTS);
        for (int i = 0; i < mask; i++) {
            double expected_val = 0.0;
            for (int j = 0; j < MX_SQRTS; j++) {
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
            mpf received_val = (sqrt_expr_.eval4(A, B));
            ret_val &= almost_equal(expected_val, received_val.get_d(), 1);
        }
        return ret_val;
    }
private:
    static const int MX_SQRTS = 4;
    robust_sqrt_expr<mpz, mpf> sqrt_expr_;
    mpz A[MX_SQRTS];
    mpz B[MX_SQRTS];
    double a[MX_SQRTS];
    double b[MX_SQRTS];
};

BOOST_AUTO_TEST_CASE(mpz_sqrt_evaluator_test) {
    typedef mpt_wrapper<mpz_class, 8> mpz_wrapper_type;
    typedef mpt_wrapper<mpf_class, 2> mpf_wrapper_type;
    sqrt_expr_tester<mpz_class, mpf_class> tester1;
    sqrt_expr_tester<mpz_wrapper_type, mpf_wrapper_type> tester2;
    for (int i = 0; i < 2000; ++i) {
        BOOST_CHECK(tester1.run());
        BOOST_CHECK(tester2.run());
    }
}
