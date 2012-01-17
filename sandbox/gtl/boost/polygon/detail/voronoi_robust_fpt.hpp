// Boost.Polygon library detail/voronoi_robust_fpt.hpp header file

//          Copyright Andrii Sydorchuk 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_VORONOI_ROBUST_FPT
#define BOOST_POLYGON_VORONOI_ROBUST_FPT

#include <cmath>

#include <boost/cstdint.hpp>

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
// error of formulas or expressions. So to calculate epsilon
// interval within which epsilon robust predicates have undefined result
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
// and compute substraction as the final step of the evaluation.
// For further information about relative errors and ULPs try this link:
// http://docs.sun.com/source/806-3568/ncg_goldberg.html

namespace boost {
namespace polygon {
namespace detail {
    typedef boost::int32_t int32;
    typedef boost::int64_t int64;
    typedef boost::uint32_t uint32;
    typedef boost::uint64_t uint64;
    typedef double fpt64;

    // If two floating-point numbers in the same format are ordered (x < y),
    // then they are ordered the same way when their bits are reinterpreted as
    // sign-magnitude integers. Values are considered to be almost equal if
    // their integer reinterpretations differ in not more than maxUlps units.
    template <typename _fpt>
    struct ulp_comparison;

    template <>
    struct ulp_comparison<fpt64> {
        enum kResult {
            LESS = -1,
            EQUAL = 0,
            MORE = 1
        };

        kResult operator()(fpt64 a, fpt64 b, unsigned int maxUlps) const {
            uint64 ll_a, ll_b;

            // Reinterpret double bits as 64-bit signed integer.
            memcpy(&ll_a, &a, sizeof(fpt64));
            memcpy(&ll_b, &b, sizeof(fpt64));

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
                return (ll_a - ll_b <= maxUlps) ? EQUAL : LESS;
            return (ll_b - ll_a <= maxUlps) ? EQUAL : MORE;
        }
    };

    template <typename T>
    T get_sqrt(const T& that) {
        return (std::sqrt)(that);
    }

    template <typename T>
    bool is_pos(const T& that) {
        return that > 0;
    }

    template <typename T>
    bool is_neg(const T& that) {
        return that < 0;
    }

    template <typename T>
    bool is_zero(const T& that) {
        return that == 0;
    }

    template <typename _fpt>
    class robust_fpt {
    public:
        typedef _fpt floating_point_type;
        typedef _fpt relative_error_type;

        // Rounding error is at most 1 EPS.
        static const relative_error_type ROUNDING_ERROR;

        robust_fpt() : fpv_(0.0), re_(0.0) {}
        explicit robust_fpt(floating_point_type fpv,
                            bool rounded = true) : fpv_(fpv) {
            re_ = rounded ? ROUNDING_ERROR : 0;
        }
        robust_fpt(floating_point_type fpv, relative_error_type error) :
            fpv_(fpv), re_(error) {}

        floating_point_type fpv() const { return fpv_; }
        relative_error_type re() const { return re_; }
        relative_error_type ulp() const { return re_; }

        robust_fpt& operator=(const robust_fpt &that) {
    	    this->fpv_ = that.fpv_;
    	    this->re_ = that.re_;
    	    return *this;
        }

        bool has_pos_value() const {
            return is_pos(fpv_);
        }

        bool has_neg_value() const {
            return is_neg(fpv_);
        }

        bool has_zero_value() const {
            return is_zero(fpv_);
        }

        robust_fpt operator-() const {
    	    return robust_fpt(-fpv_, re_);
        }

        robust_fpt& operator+=(const robust_fpt &that) {
            floating_point_type fpv = this->fpv_ + that.fpv_;
            if ((!is_neg(this->fpv_) && !is_neg(that.fpv_)) ||
                (!is_pos(this->fpv_) && !is_pos(that.fpv_)))
                this->re_ = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
            else {
                floating_point_type temp =
                    (this->fpv_ * this->re_ - that.fpv_ * that.re_) / fpv;
                if (is_neg(temp)) {
                    temp = -temp;
                }
                this->re_ = temp + ROUNDING_ERROR;
            }
            this->fpv_ = fpv;
    	    return *this;
        }

        robust_fpt& operator-=(const robust_fpt &that) {
            floating_point_type fpv = this->fpv_ - that.fpv_;
            if ((!is_neg(this->fpv_) && !is_pos(that.fpv_)) ||
                (!is_pos(this->fpv_) && !is_neg(that.fpv_)))
                this->re_ = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
            else {
                floating_point_type temp =
                    (this->fpv_ * this->re_ + that.fpv_ * that.re_) / fpv;
                if (is_neg(temp)) {
                    temp = -temp;
                }
                this->re_ = temp + ROUNDING_ERROR;
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
            if ((!is_neg(this->fpv_) && !is_neg(that.fpv_)) ||
                (!is_pos(this->fpv_) && !is_pos(that.fpv_)))
                re = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
            else {
                floating_point_type temp =
                    (this->fpv_ * this->re_ - that.fpv_ * that.re_) / fpv;
                if (is_neg(temp)) {
                    temp = -temp;
                }
                re = temp + ROUNDING_ERROR;
            }
            return robust_fpt(fpv, re);
        }

        robust_fpt operator-(const robust_fpt &that) const {
            floating_point_type fpv = this->fpv_ - that.fpv_;
            relative_error_type re;
            if ((!is_neg(this->fpv_) && !is_pos(that.fpv_)) ||
                (!is_pos(this->fpv_) && !is_neg(that.fpv_)))
                re = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
            else {
                floating_point_type temp =
                    (this->fpv_ * this->re_ + that.fpv_ * that.re_) / fpv;
                if (is_neg(temp)) {
                    temp = -temp;
                }
                re = temp + ROUNDING_ERROR;
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
            return robust_fpt(get_sqrt(fpv_),
                              re_ * static_cast<relative_error_type>(0.5) +
                              ROUNDING_ERROR);
        }

    private:
        floating_point_type fpv_;
        relative_error_type re_;
    };

    template <typename T>
    const typename robust_fpt<T>::relative_error_type
        robust_fpt<T>::ROUNDING_ERROR = 1;

    template <typename T>
    robust_fpt<T> get_sqrt(const robust_fpt<T>& that) {
        return that.sqrt();
    }

    template <typename T>
    bool is_pos(const robust_fpt<T>& that) {
        return that.has_pos_value();
    }

    template <typename T>
    bool is_neg(const robust_fpt<T>& that) {
        return that.has_neg_value();
    }

    template <typename T>
    bool is_zero(const robust_fpt<T>& that) {
        return that.has_zero_value();
    }

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

        robust_dif<T> operator-() const {
            return robust_dif(negative_sum_, positive_sum_);
        }

        robust_dif<T> &operator+=(const T &val) {
            if (!is_neg(val))
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
            if (!is_neg(val))
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
            if (!is_neg(val)) {
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
            if (!is_neg(val)) {
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
        void swap() {
            (std::swap)(positive_sum_, negative_sum_);
        }

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
        if (!is_neg(rhs)) {
            return robust_dif<T>(lhs.pos() + rhs, lhs.neg());
        } else {
            return robust_dif<T>(lhs.pos(), lhs.neg() - rhs);
        }
    }

    template<typename T>
    robust_dif<T> operator+(const T& lhs, const robust_dif<T>& rhs) {
        if (!is_neg(lhs)) {
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
        if (!is_neg(rhs)) {
            return robust_dif<T>(lhs.pos(), lhs.neg() + rhs);
        } else {
            return robust_dif<T>(lhs.pos() - rhs, lhs.neg());
        }
    }

    template<typename T>
    robust_dif<T> operator-(const T& lhs, const robust_dif<T>& rhs) {
        if (!is_neg(lhs)) {
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
        if (!is_neg(val)) {
            return robust_dif<T>(lhs.pos() * val, lhs.neg() * val);
        } else {
            return robust_dif<T>(-lhs.neg() * val, -lhs.pos() * val);
        }
    }

    template<typename T>
    robust_dif<T> operator*(const T& val, const robust_dif<T>& rhs) {
        if (!is_neg(val)) {
            return robust_dif<T>(val * rhs.pos(), val * rhs.neg());
        } else {
            return robust_dif<T>(-val * rhs.neg(), -val * rhs.pos());
        }
    }

    template<typename T>
    robust_dif<T> operator/(const robust_dif<T>& lhs, const T& val) {
        if (!is_neg(val)) {
            return robust_dif<T>(lhs.pos() / val, lhs.neg() / val);
        } else {
            return robust_dif<T>(-lhs.neg() / val, -lhs.pos() / val);
        }
    }

    // Manages exponent of the floating-point value.
    template <typename _fpt>
    struct fpt_exponent_accessor;

    template <>
    class fpt_exponent_accessor<fpt64> {
    public:
        static const int64 kExponentMask;
        static const int64 kSignedMantissaMask;
        static const int64 kMinExponent;
        static const int64 kMaxExponent;
        static const int64 kMaxSignificantExpDif;

        static int64 set_exponent(fpt64& value, int64 exponent) {
            int64 bits;
            memcpy(&bits, &value, sizeof(fpt64));
            int64 exp = ((bits & kExponentMask) >> 52) - 1023;
            if (exp == exponent) {
                return exp;
            }
            bits = (bits & kSignedMantissaMask) | ((exponent + 1023) << 52);
            memcpy(&value, &bits, sizeof(fpt64));
            return exp;
        }
    };

    const int64 fpt_exponent_accessor<fpt64>::kExponentMask = 0x7ff0000000000000LL;
    const int64 fpt_exponent_accessor<fpt64>::kSignedMantissaMask = 0x800fffffffffffffLL;
    const int64 fpt_exponent_accessor<fpt64>::kMinExponent = -1023LL;
    const int64 fpt_exponent_accessor<fpt64>::kMaxExponent = 1024LL;
    const int64 fpt_exponent_accessor<fpt64>::kMaxSignificantExpDif = 54;

    // Allows to extend floating-point type exponent boundaries to the 64 bit
    // integer range. This class does not handle division by zero, subnormal
    // numbers or NaNs.
    template <typename _fpt>
    class extended_exponent_fpt {
    public:
        typedef _fpt fpt_type;
        typedef int64 exp_type;
        typedef fpt_exponent_accessor<fpt_type> fea;

        explicit extended_exponent_fpt(fpt_type value) {
            if (value == 0.0) {
                exponent_ = 0;
                value_ = 0.0;
            } else {
                exponent_ = fea::set_exponent(value, 0);
                value_ = value;
            }
        }

        extended_exponent_fpt(fpt_type value, exp_type exponent) {
            if (value == 0.0) {
                exponent_ = 0;
                value_ = 0.0;
            } else {
                exponent_ = fea::set_exponent(value, 0) + exponent;
                value_ = value;
            }
        }

        bool is_pos() const {
            return value_ > 0;
        }

        bool is_neg() const {
            return value_ < 0;
        }

        bool is_zero() const {
            return value_ == 0;
        }

        extended_exponent_fpt operator-() const {
            return extended_exponent_fpt(-value_, exponent_);
        }

        extended_exponent_fpt operator+(const extended_exponent_fpt& that) const {
            if (this->value_ == 0.0 ||
                that.exponent_ > this->exponent_ + fea::kMaxSignificantExpDif) {
                return that;
            }
            if (that.value_ == 0.0 ||
                this->exponent_ > that.exponent_ + fea::kMaxSignificantExpDif) {
                return *this;
            }
            if (this->exponent_ >= that.exponent_) {
                exp_type exp_dif = this->exponent_ - that.exponent_;
                fpt_type value = this->value_;
                fea::set_exponent(value, exp_dif);
                value += that.value_;
                return extended_exponent_fpt(value, that.exponent_);
            } else {
                exp_type exp_dif = that.exponent_ - this->exponent_;
                fpt_type value = that.value_;
                fea::set_exponent(value, exp_dif);
                value += this->value_;
                return extended_exponent_fpt(value, this->exponent_);
            }
        }

        extended_exponent_fpt operator-(const extended_exponent_fpt& that) const {
            if (this->value_ == 0.0 ||
                that.exponent_ > this->exponent_ + fea::kMaxSignificantExpDif) {
                return extended_exponent_fpt(-that.value_, that.exponent_);
            }
            if (that.value_ == 0.0 ||
                this->exponent_ > that.exponent_ + fea::kMaxSignificantExpDif) {
                return *this;
            }
            if (this->exponent_ >= that.exponent_) {
                exp_type exp_dif = this->exponent_ - that.exponent_;
                fpt_type value = this->value_;
                fea::set_exponent(value, exp_dif);
                value -= that.value_;
                return extended_exponent_fpt(value, that.exponent_);
            } else {
                exp_type exp_dif = that.exponent_ - this->exponent_;
                fpt_type value = -that.value_;
                fea::set_exponent(value, exp_dif);
                value += this->value_;
                return extended_exponent_fpt(value, this->exponent_);
            }
        }

        extended_exponent_fpt operator*(const extended_exponent_fpt& that) const {
            fpt_type value = this->value_ * that.value_;
            exp_type exponent = this->exponent_ + that.exponent_;
            return extended_exponent_fpt(value, exponent);
        }

        extended_exponent_fpt operator/(const extended_exponent_fpt& that) const {
            fpt_type value = this->value_ / that.value_;
            exp_type exponent = this->exponent_ - that.exponent_;
            return extended_exponent_fpt(value, exponent);
        }

        extended_exponent_fpt& operator+=(const extended_exponent_fpt& that) {
            return *this = *this + that;
        }

        extended_exponent_fpt& operator-=(const extended_exponent_fpt& that) {
            return *this = *this - that;
        }

        extended_exponent_fpt& operator*=(const extended_exponent_fpt& that) {
            return *this = *this * that;
        }

        extended_exponent_fpt& operator/=(const extended_exponent_fpt& that) {
            return *this = *this / that;
        }

        extended_exponent_fpt sqrt() const {
            fpt_type val = value_;
            exp_type exp = exponent_;
            if (exp & 1) {
                val *= 2.0;
                --exp;
            }
            return extended_exponent_fpt(get_sqrt(val), exp >> 1);
        }

        fpt_type d() const {
            fpt_type ret_val = value_;
            exp_type exp = exponent_;
            if (ret_val == 0.0) {
                return ret_val;
            }
            if (exp >= fea::kMaxExponent) {
                ret_val = 1.0;
                exp = fea::kMaxExponent;
            } else if (exp <= fea::kMinExponent) {
                ret_val = 1.0;
                exp = fea::kMinExponent;
            }
            fea::set_exponent(ret_val, exp);
            return ret_val;
        }

    private:
        fpt_type value_;
        exp_type exponent_;
    };
    typedef extended_exponent_fpt<double> efpt64;

    template <typename _fpt>
    extended_exponent_fpt<_fpt> get_sqrt(const extended_exponent_fpt<_fpt>& that) {
        return that.sqrt();
    }

    template <typename _fpt>
    bool is_pos(const extended_exponent_fpt<_fpt>& that) {
        return that.is_pos();
    }

    template <typename _fpt>
    bool is_neg(const extended_exponent_fpt<_fpt>& that) {
        return that.is_neg();
    }

    template <typename _fpt>
    bool is_zero(const extended_exponent_fpt<_fpt>& that) {
        return that.is_zero();
    }

    template<size_t N>
    class extended_int {
    public:
        static const uint64 kUInt64LowMask;
        static const uint64 kUInt64HighMask;

        extended_int() {}

        extended_int(int32 that) {
            if (that > 0) {
                this->chunks_[0] = that;
                this->count_ = 1;
            } else if (that < 0) {
                this->chunks_[0] = -that;
                this->count_ = -1;
            } else {
                this->chunks_[0] = this->count_ = 0;
            }
        }

        extended_int(int64 that) {
            if (that > 0) {
                this->chunks_[0] = static_cast<uint32>(that & kUInt64LowMask);
                uint32 high = (that & kUInt64HighMask) >> 32;
                if (high) {
                    this->chunks_[1] = high;
                    this->count_ = 2;
                } else {
                    this->count_ = 1;
                }
            } else if (that < 0) {
                that = -that;
                this->chunks_[0] = static_cast<uint32>(that & kUInt64LowMask);
                uint32 high = (that & kUInt64HighMask) >> 32;
                if (high) {
                    this->chunks_[1] = high;
                    this->count_ = -2;
                } else {
                    this->count_ = -1;
                }
            } else {
                this->chunks_[0] = this->count_ = 0;
            }
        }

        extended_int(const std::vector<uint32>& chunks, bool plus = true) {
            this->count_ = static_cast<int32>(chunks.size());
            for (size_t i = 0; i < chunks.size(); ++i) {
                this->chunks_[i] = chunks[chunks.size() - i - 1];
            }
            if (!plus) {
                this->count_ = -this->count_;
            }
        }

        template <size_t M>
        extended_int(const extended_int<M>& that) {
            this->count_ = that.count();
            memcpy(this->chunks_, that.chunks(), that.size() * sizeof(uint32));
        }

        extended_int<N>& operator=(int32 that) {
            if (that > 0) {
                this->chunks_[0] = that;
                this->count_ = 1;
            } else if (that < 0) {
                this->chunks_[0] = -that;
                this->count_ = -1;
            } else {
                this->chunks_[0] = this->count_ = 0;
            }
            return *this;
        }

        extended_int<N>& operator=(int64 that) {
            if (that > 0) {
                this->chunks_[0] = static_cast<uint32>(that & kUInt64LowMask);
                uint32 high = (that & kUInt64HighMask) >> 32;
                if (high) {
                    this->chunks_[1] = high;
                    this->count_ = 2;
                } else {
                    this->count_ = 1;
                }
            } else if (that < 0) {
                that = -that;
                this->chunks_[0] = static_cast<uint32>(that & kUInt64LowMask);
                uint32 high = (that & kUInt64HighMask) >> 32;
                if (high) {
                    this->chunks_[1] = high;
                    this->count_ = -2;
                } else {
                    this->count_ = -1;
                }
            } else {
                this->chunks_[0] = this->count_ = 0;
            }
            return *this;
        }

        template <size_t M>
        extended_int<N>& operator=(const extended_int<M>& that) {
            this->count_ = that.count();
            size_t sz = (std::min)(N, that.size());
            memcpy(this->chunks_, that.chunks(), sz * sizeof(uint32));
            return *this;
        }

        bool is_pos() const {
            return this->count_ > 0;
        }

        bool is_neg() const {
            return this->count_ < 0;
        }

        bool is_zero() const {
            return this->count_ == 0;
        }

        template <size_t M>
        bool operator==(const extended_int<M>& that) const {
            if (this->count_ != that.count()) {
                return false;
            }
            for (size_t i = 0; i < this->size(); ++i) {
                if (this->chunks_[i] != that.chunks()[i]) {
                    return false;
                }
            }
            return true;
        }

        template <size_t M>
        bool operator!=(const extended_int<M>& that) const {
            return !(*this == that);
        }

        template <size_t M>
        bool operator<(const extended_int<M>& that) const {
            if (this->count_ != that.count()) {
                return this->count_ < that.count();
            }
            size_t i = this->size();
            if (!i) {
                return false;
            }
            do {
                --i;
                if (this->chunks_[i] != that.chunks()[i]) {
                    return (this->chunks_[i] < that.chunks()[i]) ^ (this->count_ < 0);
                }
            } while (i);
            return false;
        }

        template <size_t M>
        bool operator>(const extended_int<M>& that) const {
            return that < *this;
        }

        template <size_t M>
        bool operator<=(const extended_int<M>& that) const {
            return !(that < *this);
        }

        template <size_t M>
        bool operator>=(const extended_int<M>& that) const {
            return !(*this < that);
        }

        extended_int<N> operator-() const {
            extended_int<N> ret_val = *this;
            ret_val.neg();
            return ret_val;
        }

        void neg() {
            this->count_ = -this->count_;
        }

        template <size_t M>
        extended_int<(N>M?N:M)> operator+(const extended_int<M>& that) const {
            extended_int<(N>M?N:M)> ret_val;
            ret_val.add(*this, that);
            return ret_val;
        }

        template <size_t N1, size_t N2>
        void add(const extended_int<N1>& e1, const extended_int<N2>& e2) {
            if (!e1.count()) {
                *this = e2;
                return;
            }
            if (!e2.count()) {
                *this = e1;
                return;
            }
            if ((e1.count() > 0) ^ (e2.count() > 0)) {
                dif(e1.chunks(), e1.size(), e2.chunks(), e2.size());    
            } else {
                add(e1.chunks(), e1.size(), e2.chunks(), e2.size());
            }
            if (e1.count() < 0) {
                this->count_ = -this->count_;
            }
        }

        template <size_t M>
        extended_int<(N>M?N:M)> operator-(const extended_int<M>& that) const {
            extended_int<(N>M?N:M)> ret_val;
            ret_val.dif(*this, that);
            return ret_val;
        }

        template <size_t N1, size_t N2>
        void dif(const extended_int<N1>& e1, const extended_int<N2> &e2) {
            if (!e1.count()) {
                *this = e2;
                this->count_ = -this->count_;
                return;
            }
            if (!e2.count()) {
                *this = e1;
                return;
            }
            if ((e1.count() > 0) ^ (e2.count() > 0)) {
                add(e1.chunks(), e1.size(), e2.chunks(), e2.size());
            } else {
                dif(e1.chunks(), e1.size(), e2.chunks(), e2.size());
            }
            if (e1.count() < 0) {
                this->count_ = -this->count_;               
            }
        }

        extended_int<N> operator*(int32 that) const {
            extended_int<N> temp(that);
            return (*this) * temp;
        }

        extended_int<N> operator*(int64 that) const {
            extended_int<N> temp(that);
            return (*this) * temp;
        }

        template <size_t M>
        extended_int<(N>M?N:M)> operator*(const extended_int<M>& that) const {
            extended_int<(N>M?N:M)> ret_val;
            ret_val.mul(*this, that);
            return ret_val;
        }

        template <size_t N1, size_t N2>
        void mul(const extended_int<N1>& e1, const extended_int<N2>& e2) {
            if (!e1.count() || !e2.count()) {
                this->chunks_[0] = this->count_ = 0;
                return;
            }
            mul(e1.chunks(), e1.size(), e2.chunks(), e2.size());
            if ((e1.count() > 0) ^ (e2.count() > 0)) {
                this->count_ = -this->count_;
            }
        }

        const uint32* chunks() const {
            return chunks_;
        }

        int32 count() const {
            return count_;
        }

        size_t size() const {
            return (std::abs)(count_);
        }

        std::pair<fpt64, int64> p() const {
            std::pair<fpt64, int64> ret_val(0, 0);
            size_t sz = this->size();
            if (!sz) {
                return ret_val;
            } else {
                if (sz == 1) {
                    ret_val.first = static_cast<fpt64>(this->chunks_[0]);
                    ret_val.second = 0;
                } else if (sz == 2) {
                    ret_val.first = static_cast<fpt64>(this->chunks_[1]) *
                                    static_cast<fpt64>(0x100000000LL) +
                                    static_cast<fpt64>(this->chunks_[0]);
                    ret_val.second = 0;
                } else {
                    for (size_t i = 1; i <= 3; ++i) {
                        ret_val.first *= static_cast<fpt64>(0x100000000LL);
                        ret_val.first += static_cast<fpt64>(this->chunks_[sz - i]);
                    }
                    ret_val.second = (sz - 3) << 5;
                }
            }
            if (this->count_ < 0) {
                ret_val.first = -ret_val.first;
            }
            return ret_val;
        }

        fpt64 d() const {
            std::pair<fpt64, int64> p = this->p();
            extended_exponent_fpt<fpt64> efpt(p.first, p.second);
            return efpt.d();
        }

    private:
        void add(const uint32* c1, size_t sz1, const uint32* c2, size_t sz2) {
            if (sz1 < sz2) {
                add(c2, sz2, c1, sz1);
                return;
            }
            this->count_ = sz1;
            uint64 temp = 0;
            for (size_t i = 0; i < sz2; ++i) {
                temp += static_cast<uint64>(c1[i]) +
                        static_cast<uint64>(c2[i]);
                this->chunks_[i] = static_cast<uint32>(temp & kUInt64LowMask);
                temp = (temp & kUInt64HighMask) >> 32;
            }
            for (size_t i = sz2; i < sz1; ++i) {
                temp += static_cast<uint64>(c1[i]);
                this->chunks_[i] = static_cast<uint32>(temp & kUInt64LowMask);
                temp = (temp & kUInt64HighMask) >> 32;
            }
            if (temp && (this->count_ != N)) {
                this->chunks_[this->count_] = static_cast<uint32>(temp & kUInt64LowMask);
                ++this->count_;
            }
        }

        void dif(const uint32* c1, size_t sz1, const uint32* c2, size_t sz2, bool rec = false) {
            if (sz1 < sz2) {
                dif(c2, sz2, c1, sz1, true);
                this->count_ = -this->count_;
                return;
            } else if ((sz1 == sz2) && !rec) {
                do {
                    --sz1;
                    if (c1[sz1] < c2[sz1]) {
                        ++sz1;
                        dif(c2, sz1, c1, sz1, true);
                        this->count_ = -this->count_;
                        return;
                    } else if (c1[sz1] > c2[sz1]) {
                        ++sz1;
                        break;
                    } else if (!sz1) {
                        this->chunks_[0] = this->count_ = 0;
                        return;
                    }
                } while (sz1);
                sz2 = sz1;
            }
            this->count_ = sz1-1;
            bool flag = false;
            for (size_t i = 0; i < sz2; ++i) {
                this->chunks_[i] = c1[i] - c2[i] - (flag?1:0);
                flag = (c1[i] < c2[i]) || ((c1[i] == c2[i]) && flag);
            }
            for (size_t i = sz2; i < sz1; ++i) {
                this->chunks_[i] = c1[i] - (flag?1:0);
                flag = !c1[i] && flag;
            }
            if (this->chunks_[this->count_]) {
                ++this->count_;
            }
        }

        void mul(const uint32* c1, size_t sz1, const uint32* c2, size_t sz2) {
            uint64 cur = 0, nxt, tmp;
            this->count_ = static_cast<int32>((std::min)(N, sz1 + sz2 - 1));
            for (size_t shift = 0; shift < static_cast<size_t>(this->count_); ++shift) {
                nxt = 0;
                for (size_t first = 0; first <= shift; ++first) {
                    if (first >= sz1) {
                        break;
                    }
                    size_t second = shift - first;
                    if (second >= sz2) {
                        continue;
                    }
                    tmp = static_cast<uint64>(c1[first]) *
                          static_cast<uint64>(c2[second]);
                    cur += tmp & kUInt64LowMask;
                    nxt += (tmp & kUInt64HighMask) >> 32;
                }
                this->chunks_[shift] = static_cast<uint32>(cur & kUInt64LowMask);
                cur = nxt + ((cur & kUInt64HighMask) >> 32);
            }
            if (cur && (this->count_ != N)) {
                this->chunks_[this->count_] = static_cast<uint32>(cur & kUInt64LowMask);
                ++this->count_;
            }
        }

        uint32 chunks_[N];
        int32 count_;
    };

    template <size_t N>
    const uint64 extended_int<N>::kUInt64LowMask = 0x00000000ffffffffULL;
    template <size_t N>
    const uint64 extended_int<N>::kUInt64HighMask = 0xffffffff00000000ULL;

    typedef extended_int<1> eint32;
    typedef extended_int<2> eint64;
    typedef extended_int<4> eint128;
    typedef extended_int<8> eint256;
    typedef extended_int<16> eint512;
    typedef extended_int<32> eint1024;
    typedef extended_int<64> eint2048;
    typedef extended_int<128> eint4096;
    typedef extended_int<256> eint8192;
    typedef extended_int<512> eint16384;
    typedef extended_int<1024> eint32768;

    template <size_t N>
    bool is_pos(const extended_int<N>& that) {
        return that.count() > 0;
    }

    template <size_t N>
    bool is_neg(const extended_int<N>& that) {
        return that.count() < 0;
    }

    template <size_t N>
    bool is_zero(const extended_int<N>& that) {
        return !that.count();
    }

    struct type_converter_fpt {
        template <typename T>
        fpt64 operator()(const T& that) const {
            return static_cast<fpt64>(that);
        }

        template <size_t N>
        fpt64 operator()(const extended_int<N>& that) const {
            return that.d();
        }

        template <>
        fpt64 operator()< extended_exponent_fpt<fpt64> >(const extended_exponent_fpt<fpt64>& that) const {
            return that.d();
        }
    };

    struct type_converter_efpt {
        template <size_t N>
        extended_exponent_fpt<fpt64> operator()(const extended_int<N>& that) const {
            std::pair<fpt64, int64> p = that.p();
            return extended_exponent_fpt<fpt64>(p.first, p.second);
        }
    };

    // Used to compute expressions that operate with sqrts with predefined
    // relative error. Evaluates expressions of the next type:
    // sum(i = 1 .. n)(A[i] * sqrt(B[i])), 1 <= n <= 4.
    template <typename _int, typename _fpt, typename _converter>
    class robust_sqrt_expr {
    public:
        static const unsigned int EVAL1_MAX_RELATIVE_ERROR;
        static const unsigned int EVAL2_MAX_RELATIVE_ERROR;
        static const unsigned int EVAL3_MAX_RELATIVE_ERROR;
        static const unsigned int EVAL4_MAX_RELATIVE_ERROR;

        // Evaluates expression (re = 4 EPS):
        // A[0] * sqrt(B[0]).
        _fpt eval1(_int *A, _int *B) {
            _fpt a = convert(A[0]);
            _fpt b = convert(B[0]);
            return a * get_sqrt(b);
        }

        // Evaluates expression (re = 7 EPS):
        // A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]).
        _fpt eval2(_int *A, _int *B) {
            _fpt a = eval1(A, B);
            _fpt b = eval1(A + 1, B + 1);
            if ((!is_neg(a) && !is_neg(b)) ||
                (!is_pos(a) && !is_pos(b)))
                return a + b;
            return convert(A[0] * A[0] * B[0] - A[1] * A[1] * B[1]) / (a - b);
        }

        // Evaluates expression (re = 16 EPS):
        // A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]) + A[2] * sqrt(B[2]).
        _fpt eval3(_int *A, _int *B) {
            _fpt a = eval2(A, B);
            _fpt b = eval1(A + 2, B + 2);
            if ((!is_neg(a) && !is_neg(b)) ||
                (!is_pos(a) && !is_pos(b)))
                return a + b;
            tA[3] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1] - A[2] * A[2] * B[2];
            tB[3] = 1;
            tA[4] = A[0] * A[1] * 2;
            tB[4] = B[0] * B[1];
            return eval2(tA + 3, tB + 3) / (a - b);
        }


        // Evaluates expression (re = 25 EPS):
        // A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]) +
        // A[2] * sqrt(B[2]) + A[3] * sqrt(B[3]).
        _fpt eval4(_int *A, _int *B) {
            _fpt a = eval2(A, B);
            _fpt b = eval2(A + 2, B + 2);
            if ((!is_neg(a) && !is_neg(b)) ||
                (!is_pos(a) && !is_pos(b)))
                return a + b;
            tA[0] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1] -
                    A[2] * A[2] * B[2] - A[3] * A[3] * B[3];
            tB[0] = 1;
            tA[1] = A[0] * A[1] * 2;
            tB[1] = B[0] * B[1];
            tA[2] = A[2] * A[3] * -2;
            tB[2] = B[2] * B[3];
            return eval3(tA, tB) / (a - b);
        }

    private:
        _int tA[5];
        _int tB[5];
        _converter convert;
    };

    template <typename _int, typename _fpt, typename _converter>
    const unsigned int robust_sqrt_expr<_int, _fpt, _converter>::EVAL1_MAX_RELATIVE_ERROR = 4;
    template <typename _int, typename _fpt, typename _converter>
    const unsigned int robust_sqrt_expr<_int, _fpt, _converter>::EVAL2_MAX_RELATIVE_ERROR = 7;
    template <typename _int, typename _fpt, typename _converter>
    const unsigned int robust_sqrt_expr<_int, _fpt, _converter>::EVAL3_MAX_RELATIVE_ERROR = 16;
    template <typename _int, typename _fpt, typename _converter>
    const unsigned int robust_sqrt_expr<_int, _fpt, _converter>::EVAL4_MAX_RELATIVE_ERROR = 25;
} // detail
} // polygon
} // boost

#endif
