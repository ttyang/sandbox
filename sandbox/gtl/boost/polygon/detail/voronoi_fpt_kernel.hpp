// Boost.Polygon library detail/voronoi_fpt_kernel.hpp header file

//          Copyright Andrii Sydorchuk 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.    

#ifndef BOOST_POLYGON_VORONOI_FPT_KERNEL
#define BOOST_POLYGON_VORONOI_FPT_KERNEL

// Geometry predicates with floating-point variables usually require
// high-precision predicates to retrieve the correct result.
// Epsilon robust predicates give the result within some epsilon relative
// error, but are a lot faster than high-precision predicates.
// To make algorithm robust and efficient epsilon robust predicates are
// used at the first step. In case of the undefined result high-precision
// arithmetic is used to produce required robustness. This approach
// requires exact computation of epsilon intervals within which epsilon
// robust predicates have undefined value.
// There are two ways to measure an error of floating-point calculations:
// relative error and ULPs (units in the last place).
// Let EPS be machine epsilon, then next inequalities have place:
// 1 EPS <= 1 ULP <= 2 EPS (1), 0.5 ULP <= 1 EPS <= 1 ULP (2).
// ULPs are good for measuring rounding errors and comparing values.
// Relative erros are good for computation of general relative
// errors of formulas or expressions. So to calculate epsilon
// intervals within which epsilon robust predicates have undefined result
// next schema is used:
//     1) Compute rounding errors of initial variables using ULPs;
//     2) Transform ULPs to epsilons using upper bound of the (1);
//     3) Compute relative error of the formula using epsilon arithmetic;
//     4) Transform epsilon to ULPs using upper bound of the (2);
// In case two values are inside undefined ULP range use high-precision
// arithmetic to produce the correct result, else output the result.
// Look at almost_equal function to see how two floating-point variables
// are checked to fit in the ULP range.
// If A has relative error of r(A) and B has relative error of r(B) then:
//     1) r(A + B) <= max(r(A), r(B)), for A * B >= 0;
//     2) r(A - B) <= B*r(A)+A*r(B)/(A-B), for A * B >= 0;
//     2) r(A * B) <= r(A) + r(B);
//     3) r(A / B) <= r(A) + r(B);
// In addition rounding error should be added, that is always equal to
// 0.5 ULP or atmost 1 epsilon. As you might see from the above formulas
// substraction relative error may be extremely large, that's why
// epsilon robust comparator class is used to store floating point values
// and avoid substraction.
// For further information about relative errors and ULPs try this link:
// http://docs.sun.com/source/806-3568/ncg_goldberg.html

namespace boost {
namespace polygon {
namespace detail {

    // Represents the result of the epsilon robust predicate.
    // If the result is undefined some further processing is usually required.
    enum kPredicateResult {
        LESS = -1,
        UNDEFINED = 0,
        MORE = 1,
    };

    // If two floating-point numbers in the same format are ordered (x < y),
    // then they are ordered the same way when their bits are reinterpreted as
    // sign-magnitude integers. Values are considered to be almost equal if
    // their integer reinterpretations differ in not more than maxUlps units.
    template <typename T>
    bool almost_equal(T a, T b, unsigned int ulps);

    template<>
    bool almost_equal<float>(float a, float b, unsigned int maxUlps) {
	    unsigned int ll_a, ll_b;

        // Reinterpret double bits as 32-bit signed integer.
        memcpy(&ll_a, &a, sizeof(float));
        memcpy(&ll_b, &b, sizeof(float));

        if (ll_a < 0x80000000)
            ll_a = 0x80000000 - ll_a;
        if (ll_b < 0x80000000)
            ll_b = 0x80000000 - ll_b;

	    if (ll_a > ll_b)
            return ll_a - ll_b <= maxUlps;
        return ll_b - ll_a <= maxUlps;
    }

    template<>
    bool almost_equal<double>(double a, double b, unsigned int maxUlps) {
        unsigned long long ll_a, ll_b;

        // Reinterpret double bits as 64-bit signed integer.
        memcpy(&ll_a, &a, sizeof(double));
        memcpy(&ll_b, &b, sizeof(double));

        // Positive 0.0 is integer zero. Negative 0.0 is 0x8000000000000000.
        // Map negative zero to an integer zero representation - making it
        // identical to positive zero - the smallest negative number is
        // represented by negative one, and downwards from there.
        if (ll_a < 0x8000000000000000ULL)
            ll_a = 0x8000000000000000ULL - ll_a;
        if (ll_b < 0x8000000000000000ULL)
            ll_b = 0x8000000000000000ULL - ll_b;

        // Compare 64-bit signed integer representations of input values.
        // Difference in 1 Ulp is equivalent to a relative error of between
        // 1/4,000,000,000,000,000 and 1/8,000,000,000,000,000.
        if (ll_a > ll_b)
            return ll_a - ll_b <= maxUlps;
        return ll_b - ll_a <= maxUlps;
    }

    template <typename T>
    double get_d(const T& value) {
        return value.get_d();
    }

    template <>
    double get_d(const float& value) {
        return value;
    }

    template <>
    double get_d(const double& value) {
        return value;
    }

    template <>
    double get_d(const long double& value) {
        return static_cast<double>(value);
    }

    template <typename FPT>
    class robust_fpt {
    public:
        typedef FPT floating_point_type;
        typedef FPT relative_error_type;

        // Rounding error is at most 1 EPS.
        static const relative_error_type ROUNDING_ERROR;

        robust_fpt() : fpv_(0.0), re_(0) {}
        explicit robust_fpt(int fpv) : fpv_(fpv), re_(0) {}
        explicit robust_fpt(floating_point_type fpv,
                            bool rounded = true) : fpv_(fpv) {
            re_ = rounded ? ROUNDING_ERROR : 0;
        }
        robust_fpt(floating_point_type fpv, relative_error_type error) :
            fpv_(fpv), re_(error) {}

        floating_point_type fpv() const { return fpv_; }
        relative_error_type re() const { return re_; }
        relative_error_type ulp() const { return re_; }

        template <typename T>
        bool operator==(T that) const {
            floating_point_type value = static_cast<floating_point_type>(that);
            return almost_equal(this->fpv_,
                                value,
                                static_cast<unsigned int>(this->ulp()));
        }

        template <typename T>
        bool operator!=(T that) const {
            return !(*this == that);
        }

        template <typename T>
        bool operator<(T that) const {
            if (*this == that) return false;
            return this->fpv_ < static_cast<floating_point_type>(that);
        }

        template <typename T>
        bool operator<=(T that) const {
            if (*this == that) return true;
            return this->fpv_ < static_cast<floating_point_type>(that);
        }

        template <typename T>
        bool operator>(T that) const {
            if (*this == that) return false;
            return this->fpv_ > static_cast<floating_point_type>(that);
        }

        template <typename T>
        bool operator>=(T that) const {
            if (*this == that) return true;
            return this->fpv_ > static_cast<floating_point_type>(that);
        }

        bool operator==(const robust_fpt &that) const {
    	    unsigned int ulp = static_cast<unsigned int>(this->re_ + that.re_);
    	    return almost_equal(this->fpv_, that.fpv_, ulp);	
        }

        bool operator!=(const robust_fpt &that) const {
    	    return !(*this == that);
        }

        bool operator<(const robust_fpt &that) const {
    	    if (*this == that)
    		    return false;
    	    return this->fpv_ < that.fpv_;
        }

        bool operator>(const robust_fpt &that) const {
    	    return that < *this;
        }

        bool operator<=(const robust_fpt &that) const {
    	    return !(that < *this);
        }

        bool operator>=(const robust_fpt &that) const {
    	    return !(*this < that);
        }

        robust_fpt operator-() const {
    	    return robust_fpt(-fpv_, re_);
        }

        robust_fpt& operator=(const robust_fpt &that) {
    	    this->fpv_ = that.fpv_;
    	    this->re_ = that.re_;
    	    return *this;
        }

        robust_fpt& operator+=(const robust_fpt &that) {
            floating_point_type fpv = this->fpv_ + that.fpv_;
            if ((this->fpv_ >= 0 && that.fpv_ >= 0) ||
                (this->fpv_ <= 0 && that.fpv_ <= 0))
                this->re_ = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
            else {            
                floating_point_type temp =
                    (this->fpv_ * this->re_ - that.fpv_ * that.re_) / fpv;
                this->re_ = std::fabs(temp) + ROUNDING_ERROR;
            }
            this->fpv_ = fpv;
    	    return *this;
        }

        robust_fpt& operator-=(const robust_fpt &that) {
            floating_point_type fpv = this->fpv_ - that.fpv_;
            if ((this->fpv_ >= 0 && that.fpv_ <= 0) ||
                (this->fpv_ <= 0 && that.fpv_ >= 0))
                this->re_ = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
            else {
                floating_point_type temp =
                    (this->fpv_ * this->re_ + that.fpv_ * that.re_) / fpv;
                this->re_ = std::fabs(temp) + ROUNDING_ERROR;
            }
            this->fpv_ = fpv;
    	    return *this;
        }

        robust_fpt& operator*=(const robust_fpt &that) {
    	    this->re_ += that.re_ + ROUNDING_ERROR;
    	    this->fpv_ *= that.fpv_;
            return *this;
        }

        robust_fpt& operator/=(const robust_fpt &that) {
            this->re_ += that.re_ + ROUNDING_ERROR;
    	    this->fpv_ /= that.fpv_;
            return *this;
        }

        robust_fpt operator+(const robust_fpt &that) const {
            floating_point_type fpv = this->fpv_ + that.fpv_;
            relative_error_type re;
            if ((this->fpv_ >= 0 && that.fpv_ >= 0) ||
                (this->fpv_ <= 0 && that.fpv_ <= 0))
                re = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
            else {
                floating_point_type temp =
                    (this->fpv_ * this->re_ - that.fpv_ * that.re_) / fpv;
                re = std::fabs(temp) + ROUNDING_ERROR;
            }
            return robust_fpt(fpv, re);
        }

        robust_fpt operator-(const robust_fpt &that) const {
            floating_point_type fpv = this->fpv_ - that.fpv_;
            relative_error_type re;
            if ((this->fpv_ >= 0 && that.fpv_ <= 0) ||
                (this->fpv_ <= 0 && that.fpv_ >= 0))
                re = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
            else {
                floating_point_type temp =
                    (this->fpv_ * this->re_ + that.fpv_ * that.re_) / fpv;
                re = std::fabs(temp) + ROUNDING_ERROR;
            }
            return robust_fpt(fpv, re);
        }

        robust_fpt operator*(const robust_fpt &that) const {
            floating_point_type fpv = this->fpv_ * that.fpv_;
            relative_error_type re = this->re_ + that.re_ + ROUNDING_ERROR;
            return robust_fpt(fpv, re);
        }

        robust_fpt operator/(const robust_fpt &that) const {
            floating_point_type fpv = this->fpv_ / that.fpv_;
            relative_error_type re = this->re_ + that.re_ + ROUNDING_ERROR;
            return robust_fpt(fpv, re);
        }

        robust_fpt sqrt() const {
            return robust_fpt(std::sqrt(fpv_), re_ * 0.5 + ROUNDING_ERROR);
        }

        robust_fpt fabs() const {
            return (fpv_ >= 0) ? *this : -(*this);
        }

    private:
        floating_point_type fpv_;
        relative_error_type re_;
    };

    template <typename T>
    const typename robust_fpt<T>::relative_error_type
        robust_fpt<T>::ROUNDING_ERROR = 1;

    // robust_dif consists of two not negative values: value1 and value2.
    // The resulting expression is equal to the value1 - value2.
    // Substraction of a positive value is equivalent to the addition to value2
    // and substraction of a negative value is equivalent to the addition to
    // value1. The structure implicitly avoids difference computation.
    template <typename T>
    class robust_dif {
    public:
        robust_dif() :
          positive_sum_(0),
          negative_sum_(0) {}

        robust_dif(const T &value) :
          positive_sum_((value>0)?value:0),
          negative_sum_((value<0)?-value:0) {}

        robust_dif(const T &pos, const T &neg) :
          positive_sum_(pos),
          negative_sum_(neg) {}

        T dif() const {
            return positive_sum_ - negative_sum_;
        }

        T pos() const {
            return positive_sum_;
        }

        T neg() const {
            return negative_sum_;
        }

        // Equivalent to the unary minus.
        void swap() {
            (std::swap)(positive_sum_, negative_sum_);
        }

        bool abs() {
            if (positive_sum_ < negative_sum_) {
                swap();
                return true;
            }
            return false;
        }

        robust_dif<T> operator-() const {
            return robust_dif(negative_sum_, positive_sum_);
        }

        robust_dif<T> &operator+=(const T &val) {
            if (val >= 0)
                positive_sum_ += val;
            else
                negative_sum_ -= val;
            return *this;
        }

        robust_dif<T> &operator+=(const robust_dif<T> &that) {
            positive_sum_ += that.positive_sum_;
            negative_sum_ += that.negative_sum_;
            return *this;
        }

        robust_dif<T> &operator-=(const T &val) {
            if (val >= 0)
                negative_sum_ += val;
            else
                positive_sum_ -= val;
            return *this;
        }

        robust_dif<T> &operator-=(const robust_dif<T> &that) {
            positive_sum_ += that.negative_sum_;
            negative_sum_ += that.positive_sum_;
            return *this;
        }

        robust_dif<T> &operator*=(const T &val) {
            if (val >= 0) {
                positive_sum_ *= val;
                negative_sum_ *= val;
            } else {
                positive_sum_ *= -val;
                negative_sum_ *= -val;
                swap();
            }
            return *this;
        }

        robust_dif<T> &operator*=(const robust_dif<T> &that) {
            T positive_sum = this->positive_sum_ * that.positive_sum_ +
                             this->negative_sum_ * that.negative_sum_;
            T negative_sum = this->positive_sum_ * that.negative_sum_ +
                             this->negative_sum_ * that.positive_sum_;
            positive_sum_ = positive_sum;
            negative_sum_ = negative_sum;
            return *this;
        }

        robust_dif<T> &operator/=(const T &val) {
            if (val >= 0) {
                positive_sum_ /= val;
                negative_sum_ /= val;
            } else {
                positive_sum_ /= -val;
                negative_sum_ /= -val;
                swap();
            }
            return *this;
        }

    private:
        T positive_sum_;
        T negative_sum_;
    };

    template<typename T>
    robust_dif<T> operator+(const robust_dif<T>& lhs,
                            const robust_dif<T>& rhs) {
        return robust_dif<T>(lhs.pos() + rhs.pos(),
                             lhs.neg() + rhs.neg());
    }

    template<typename T>
    robust_dif<T> operator+(const robust_dif<T>& lhs, const T& rhs) {
        if (rhs >= 0) {
            return robust_dif<T>(lhs.pos() + rhs, lhs.neg());
        } else {
            return robust_dif<T>(lhs.pos(), lhs.neg() - rhs);
        }
    }

    template<typename T>
    robust_dif<T> operator+(const T& lhs, const robust_dif<T>& rhs) {
        if (lhs >= 0) { 
            return robust_dif<T>(lhs + rhs.pos(), rhs.neg());
        } else {
            return robust_dif<T>(rhs.pos(), rhs.neg() - lhs);
        }
    }

    template<typename T>
    robust_dif<T> operator-(const robust_dif<T>& lhs,
                            const robust_dif<T>& rhs) {
        return robust_dif<T>(lhs.pos() + rhs.neg(), lhs.neg() + rhs.pos());
    }

    template<typename T>
    robust_dif<T> operator-(const robust_dif<T>& lhs, const T& rhs) {
        if (rhs >= 0) {
            return robust_dif<T>(lhs.pos(), lhs.neg() + rhs);
        } else {
            return robust_dif<T>(lhs.pos() - rhs, lhs.neg());
        }
    }

    template<typename T>
    robust_dif<T> operator-(const T& lhs, const robust_dif<T>& rhs) {
        if (lhs >= 0) { 
            return robust_dif<T>(lhs + rhs.neg(), rhs.pos());
        } else {
            return robust_dif<T>(rhs.neg(), rhs.pos() - lhs);
        }
    }

    template<typename T>
    robust_dif<T> operator*(const robust_dif<T>& lhs,
                            const robust_dif<T>& rhs) {
        T res_pos = lhs.pos() * rhs.pos() + lhs.neg() * rhs.neg();
        T res_neg = lhs.pos() * rhs.neg() + lhs.neg() * rhs.pos();
        return robust_dif<T>(res_pos, res_neg);
    }

    template<typename T>
    robust_dif<T> operator*(const robust_dif<T>& lhs, const T& val) {
        if (val >= 0) {
            return robust_dif<T>(lhs.pos() * val, lhs.neg() * val);
        } else {
            return robust_dif<T>(-lhs.neg() * val, -lhs.pos() * val);
        }
    }

    template<typename T>
    robust_dif<T> operator*(const T& val, const robust_dif<T>& rhs) {
        if (val >= 0) {
            return robust_dif<T>(val * rhs.pos(), val * rhs.neg());
        } else {
            return robust_dif<T>(-val * rhs.neg(), -val * rhs.pos());
        }
    }

    template<typename T>
    robust_dif<T> operator/(const robust_dif<T>& lhs, const T& val) {
        if (val >= 0) {
            return robust_dif<T>(lhs.pos() / val, lhs.neg() / val);
        } else {
            return robust_dif<T>(-lhs.neg() / val, -lhs.pos() / val);
        }
    }
    
    // Used to compute expressions that operate with sqrts with predefined
    // relative error. Evaluates expressions of the next type:
    // sum(i = 1 .. n)(A[i] * sqrt(B[i])), 1 <= n <= 4.
    template <typename mpt, typename mpf>
    class robust_sqrt_expr {
    public:
        // Evaluates expression (re = 4 EPS):
        // A[0] * sqrt(B[0]).
        mpf& eval1(mpt *A, mpt *B) {
            a[0] = A[0];
            b[0] = B[0];
            b[0] = sqrt(b[0]);
            return b[0] *= a[0];
        }

        // Evaluates expression (re = 7 EPS):
        // A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]).
        mpf& eval2(mpt *A, mpt *B) {
            a[1] = eval1(A, B);
            b[1] = eval1(A + 1, B + 1);
            if ((a[1] >= 0 && b[1] >= 0) || (a[1] <= 0 && b[1] <= 0))
                return b[1] += a[1];
            for (int i = 0; i < 2; ++i) {
                temp[i] = A[i] * A[i];
                temp[i] *= B[i];
            }
            a[1] -= b[1];
            b[1] = temp[0] - temp[1];
            return b[1] /= a[1];
        }

        // Evaluates expression (re = 16 EPS):
        // A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]) + A[2] * sqrt(B[2]).
        mpf& eval3(mpt *A, mpt *B) {
            a[2] = eval2(A, B);
            b[2] = eval1(A + 2, B + 2);
            if ((a[2] >= 0 && b[2] >= 0) || (a[2] <= 0 && b[2] <= 0))
                return b[2] += a[2];
            for (int i = 0; i < 3; ++i) {
                temp[i] = A[i] * A[i];
                temp[i] *= B[i];
            }
            cA[0] = temp[0] + temp[1];
            cA[0] -= temp[2];
            cB[0] = 1;
            cA[1] = A[0] * A[1];
            cA[1] += cA[1];
            cB[1] = B[0] * B[1];
            a[2] -= b[2];
            b[2] = eval2(cA, cB);
            return b[2] /= a[2];
        }

        
        // Evaluates expression (re = 25 EPS):
        // A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]) +
        // A[2] * sqrt(B[2]) + A[3] * sqrt(B[3]).
        mpf& eval4(mpt *A, mpt *B) {
            a[3] = eval2(A, B);
            b[3] = eval2(A + 2, B + 2);
            if ((a[3] >= 0 && b[3] >= 0) || (a[3] <= 0 && b[3] <= 0))
                return b[3] += a[3];
            for (int i = 0; i < 4; ++i) {
                temp[i] = A[i] * A[i];
                temp[i] *= B[i];
            }
            dA[0] = temp[0] + temp[1];
            dA[0] -= temp[2];
            dA[0] -= temp[3];
            dB[0] = 1;
            dA[1] = A[0] * A[1];
            dA[1] += dA[1];
            dB[1] = B[0] * B[1];
            dA[2] = A[2] * A[3];
            dA[2] = -dA[2];
            dA[2] += dA[2];
            dB[2] = B[2] * B[3];
            a[3] -= b[3];
            b[3] = eval3(dA, dB);
            return b[3] /= a[3];
        }

    private:
        mpf a[4];
        mpf b[4];
        mpt cA[2];
        mpt cB[2];
        mpt dA[3];
        mpt dB[3];
        mpt temp[4];
    };

} // detail
} // polygon
} // boost

#endif
