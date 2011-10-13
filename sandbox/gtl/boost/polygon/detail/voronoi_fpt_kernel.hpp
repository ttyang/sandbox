// Boost polygon/detail/voronoi_fpt_kernel.hpp header file

//          Copyright Andrii Sydorchuk 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.    

#ifndef BOOST_POLYGON_VORONOI_FPT_KERNEL
#define BOOST_POLYGON_VORONOI_FPT_KERNEL

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
    // their integer reinterpretatoins differ in not more than maxUlps units.
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
        typedef double relative_error_type;

        // Rounding error is at most 1 EPS.
        static const relative_error_type ROUNDING_ERROR;

        // Constructors.
        robust_fpt() : fpv_(0.0), re_(0) {}
        explicit robust_fpt(int fpv) : fpv_(fpv), re_(0) {}
        explicit robust_fpt(floating_point_type fpv, bool rounded = true) : fpv_(fpv) {
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
            return almost_equal(this->fpv_, value, static_cast<unsigned int>(this->ulp()));
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
    	    unsigned int ulp = static_cast<unsigned int>(ceil(this->re_ + that.re_));
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
                floating_point_type temp = (this->fpv_ * this->re_ - that.fpv_ * that.re_) / fpv;
                this->re_ = std::fabs(get_d(temp)) + ROUNDING_ERROR;
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
                floating_point_type temp = (this->fpv_ * this->re_ + that.fpv_ * that.re_) / fpv;
                this->re_ = std::fabs(get_d(temp)) + ROUNDING_ERROR;
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
                floating_point_type temp = (this->fpv_ * this->re_ - that.fpv_ * that.re_) / fpv;
                re = std::fabs(get_d(temp)) + ROUNDING_ERROR;
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
                floating_point_type temp = (this->fpv_ * this->re_ + that.fpv_ * that.re_) / fpv;
                re = std::fabs(get_d(temp)) + ROUNDING_ERROR;
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
    const typename robust_fpt<T>::relative_error_type robust_fpt<T>::ROUNDING_ERROR = 1;

    // Class used to make computations with epsilon relative error.
    // ERC consists of two values: value1 and value2, both positive.
    // The resulting expression is equal to the value1 - value2.
    // The main idea is to represent any expression that consists of
    // addition, substraction, multiplication and division operations
    // to avoid using substraction. Substraction of a positive value
    // is equivalent to the addition to value2 and substraction of
    // a negative value is equivalent to the addition to value1.
    // Cons: ERC gives error relative not to the resulting value,
    //       but relative to some expression instead. Example:
    //       center_x = 100, ERC's value1 = 10^20, value2 = 10^20,
    //       center_x = 1000, ERC's value3 = 10^21, value4 = 10^21,
    //       such two centers are considered equal(
    //       value1 + value4 = value2 + value3), while they are not.
    // Pros: ERC is much faster then approaches based on the use
    //       of high-precision libraries. However this will give correct
    //       answer for the previous example.
    // Solution: Use ERCs in case of defined comparison results and use
    //           high-precision libraries for undefined results.
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

        robust_dif<T> &operator+=(
            const robust_dif<T> &that) {
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

        robust_dif<T> &operator-=(
            const robust_dif<T> &that) {
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

        robust_dif<T> &operator*=(
            const robust_dif<T> &that) {
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
    robust_dif<T> operator+(
        const robust_dif<T>& lhs,
        const robust_dif<T>& rhs) {
        return robust_dif<T>(lhs.pos() + rhs.pos(),
                             lhs.neg() + rhs.neg());
    }

    template<typename T>
    robust_dif<T> operator+(
        const robust_dif<T>& lhs, const T& rhs) {
        if (rhs >= 0) {
            return robust_dif<T>(lhs.pos() + rhs, lhs.neg());
        } else {
            return robust_dif<T>(lhs.pos(), lhs.neg() - rhs);
        }
    }

    template<typename T>
    robust_dif<T> operator+(
        const T& lhs, const robust_dif<T>& rhs) {
        if (lhs >= 0) { 
            return robust_dif<T>(lhs + rhs.pos(), rhs.neg());
        } else {
            return robust_dif<T>(rhs.pos(), rhs.neg() - lhs);
        }
    }

    template<typename T>
    robust_dif<T> operator-(
        const robust_dif<T>& lhs,
        const robust_dif<T>& rhs) {
        return robust_dif<T>(lhs.pos() + rhs.neg(), lhs.neg() + rhs.pos());
    }

    template<typename T>
    robust_dif<T> operator-(
        const robust_dif<T>& lhs, const T& rhs) {
        if (rhs >= 0) {
            return robust_dif<T>(lhs.pos(), lhs.neg() + rhs);
        } else {
            return robust_dif<T>(lhs.pos() - rhs, lhs.neg());
        }
    }

    template<typename T>
    robust_dif<T> operator-(
        const T& lhs, const robust_dif<T>& rhs) {
        if (lhs >= 0) { 
            return robust_dif<T>(lhs + rhs.neg(), rhs.pos());
        } else {
            return robust_dif<T>(rhs.neg(), rhs.pos() - lhs);
        }
    }

    template<typename T>
    robust_dif<T> operator*(
        const robust_dif<T>& lhs,
        const robust_dif<T>& rhs) {
        T res_pos = lhs.pos() * rhs.pos() + lhs.neg() * rhs.neg();
        T res_neg = lhs.pos() * rhs.neg() + lhs.neg() * rhs.pos();
        return robust_dif<T>(res_pos, res_neg);
    }

    template<typename T>
    robust_dif<T> operator*(
        const robust_dif<T>& lhs, const T& val) {
        if (val >= 0) {
            return robust_dif<T>(lhs.pos() * val, lhs.neg() * val);
        } else {
            return robust_dif<T>(-lhs.neg() * val, -lhs.pos() * val);
        }
    }

    template<typename T>
    robust_dif<T> operator*(
        const T& val, const robust_dif<T>& rhs) {
        if (val >= 0) {
            return robust_dif<T>(val * rhs.pos(), val * rhs.neg());
        } else {
            return robust_dif<T>(-val * rhs.neg(), -val * rhs.pos());
        }
    }

    template<typename T>
    robust_dif<T> operator/(
        const robust_dif<T>& lhs, const T& val) {
        if (val >= 0) {
            return robust_dif<T>(lhs.pos() / val, lhs.neg() / val);
        } else {
            return robust_dif<T>(-lhs.neg() / val, -lhs.pos() / val);
        }
    }

    
    ///////////////////////////////////////////////////////////////////////////
    // VORONOI ROBUST SQRT EXPRESSION  ////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    template <typename mpt, typename mpf>
    class robust_sqrt_expr {
    public:
        // Evaluates expression:
        // A[0] * sqrt(B[0]).
        mpf eval1(mpt *A, mpt *B) {
#ifndef THREAD_SAFETY
            static
#endif
            mpf lhs, rhs, numer;
            lhs = A[0];
            rhs = B[0];
            numer = lhs * sqrt(rhs);
            return numer;            
        }

        // Evaluates expression:
        // A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]) with
        // 7 * EPS relative error in the worst case.
        mpf eval2(mpt *A, mpt *B) {
#ifndef THREAD_SAFETY
            static
#endif
            mpf lhs, rhs, numer;
            lhs = eval1(A, B);
            rhs = eval1(A + 1, B + 1);
            if ((lhs >= 0 && rhs >= 0) || (lhs <= 0 && rhs <= 0))
                return lhs + rhs;
            numer = A[0] * A[0] * B[0] - A[1] * A[1] * B[1];
            return numer / (lhs - rhs);
        }

        // Evaluates expression:
        // A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]) + A[2] * sqrt(B[2])
        // with 16 * EPS relative error in the worst case.
        mpf eval3(mpt *A, mpt *B) {
#ifndef THREAD_SAFETY
            static
#endif
            mpt cA[2], cB[2];
#ifndef THREAD_SAFETY
            static
#endif
            mpf lhs, rhs, numer;
            lhs = eval2(A, B);
            rhs = eval1(A + 2, B + 2);
            if ((lhs >= 0 && rhs >= 0) || (lhs <= 0 && rhs <= 0))
                return lhs + rhs;
            cA[0] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1];
            cA[0] -= A[2] * A[2] * B[2];
            cB[0] = 1;
            cA[1] = A[0] * A[1] * 2;
            cB[1] = B[0] * B[1];
            numer = eval2(cA, cB);
            return numer / (lhs - rhs);
        }

        
        // Evaluates expression:
        // A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]) + A[2] * sqrt(B[2]) + A[3] * sqrt(B[3])
        // with 25 * EPS relative error in the worst case.
        mpf eval4(mpt *A, mpt *B) {
#ifndef THREAD_SAFETY
            static
#endif
            mpt cA[3], cB[3];
#ifndef THREAD_SAFETY
            static
#endif
            mpf lhs, rhs, numer;
            lhs = eval2(A, B);
            rhs = eval2(A + 2, B + 2);
            if ((lhs >= 0 && rhs >= 0) || (lhs <= 0 && rhs <= 0))
                return lhs + rhs;
            cA[0] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1];
            cA[0] -= A[2] * A[2] * B[2] + A[3] * A[3] * B[3];
            cB[0] = 1;
            cA[1] = A[0] * A[1] * 2;
            cB[1] = B[0] * B[1];
            cA[2] = A[2] * A[3] * -2;
            cB[2] = B[2] * B[3];
            numer = eval3(cA, cB);
            return numer / (lhs - rhs);
        }

    private:
    };

} // detail
} // polygon
} // boost

#endif
