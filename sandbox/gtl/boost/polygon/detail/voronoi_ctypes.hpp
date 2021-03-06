// Boost.Polygon library detail/voronoi_ctypes.hpp header file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_DETAIL_VORONOI_CTYPES
#define BOOST_POLYGON_DETAIL_VORONOI_CTYPES

#include <cmath>
#include <cstring>

#include <boost/cstdint.hpp>

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
// their integer bits reinterpretations differ in not more than maxUlps units.
template <typename _fpt>
struct ulp_comparison;

template <>
struct ulp_comparison<fpt64> {
  enum Result {
    LESS = -1,
    EQUAL = 0,
    MORE = 1
  };

  Result operator()(fpt64 a, fpt64 b, unsigned int maxUlps) const {
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
    if (exp == exponent)
      return exp;
    bits = (bits & kSignedMantissaMask) | ((exponent + 1023) << 52);
    memcpy(&value, &bits, sizeof(fpt64));
    return exp;
  }
};

const int64 fpt_exponent_accessor<fpt64>::kExponentMask =
  0x7ff0000000000000LL;
const int64 fpt_exponent_accessor<fpt64>::kSignedMantissaMask =
  0x800fffffffffffffLL;
const int64 fpt_exponent_accessor<fpt64>::kMinExponent = -1023LL;
const int64 fpt_exponent_accessor<fpt64>::kMaxExponent = 1024LL;
const int64 fpt_exponent_accessor<fpt64>::kMaxSignificantExpDif = 54;

// Floating point type wrapper. Allows to extend exponent boundaries to the
// 64 bit integer range. This class does not handle division by zero, subnormal
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
    return extended_exponent_fpt(std::sqrt(val), exp >> 1);
  }

  fpt_type d() const {
    fpt_type ret_val = value_;
    exp_type exp = exponent_;
    if (ret_val == 0.0)
      return ret_val;
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

// Very efficient stack allocated big integer class.
// Supports next set of arithmetic operations: +, -, *.
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
      this->count_ = 0;
    }
  }

  extended_int(int64 that) {
    if (that > 0) {
      this->chunks_[0] = static_cast<uint32>(that & kUInt64LowMask);
      this->chunks_[1] = that >> 32;
      this->count_ = this->chunks_[1] ? 2 : 1;
    } else if (that < 0) {
      that = -that;
      this->chunks_[0] = static_cast<uint32>(that & kUInt64LowMask);
      this->chunks_[1] = that >> 32;
      this->count_ = this->chunks_[1] ? -2 : -1;
    } else {
      this->count_ = 0;
    }
  }

  extended_int(const std::vector<uint32>& chunks, bool plus = true) {
    this->count_ = static_cast<int32>((std::min)(N, chunks.size()));
    for (int i = 0; i < this->count_; ++i)
      this->chunks_[i] = chunks[chunks.size() - i - 1];
    if (!plus)
      this->count_ = -this->count_;
  }

  template <size_t M>
  extended_int(const extended_int<M>& that) {
    if (that.size() > N) return;
    this->count_ = that.count();
    memcpy(this->chunks_, that.chunks(), that.size() * sizeof(uint32));
  }

  extended_int& operator=(int32 that) {
    if (that > 0) {
      this->chunks_[0] = that;
      this->count_ = 1;
    } else if (that < 0) {
      this->chunks_[0] = -that;
      this->count_ = -1;
    } else {
      this->count_ = 0;
    }
    return *this;
  }

  extended_int& operator=(int64 that) {
    if (that > 0) {
      this->chunks_[0] = static_cast<uint32>(that & kUInt64LowMask);
      this->chunks_[1] = that >> 32;
      this->count_ = this->chunks_[1] ? 2 : 1;
    } else if (that < 0) {
      that = -that;
      this->chunks_[0] = static_cast<uint32>(that & kUInt64LowMask);
      this->chunks_[1] = that >> 32;
      this->count_ = this->chunks_[1] ? -2 : -1;
    } else {
      this->count_ = 0;
    }
    return *this;
  }

  template <size_t M>
  extended_int& operator=(const extended_int<M>& that) {
    size_t mx = (std::max)(N, that.size());
    this->count_ = that.count();
    memcpy(this->chunks_, that.chunks(), mx * sizeof(uint32));
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
    if (this->count_ != that.count())
      return false;
    for (size_t i = 0; i < this->size(); ++i)
      if (this->chunks_[i] != that.chunks()[i])
        return false;
    return true;
  }

  template <size_t M>
  bool operator!=(const extended_int<M>& that) const {
    return !(*this == that);
  }

  template <size_t M>
  bool operator<(const extended_int<M>& that) const {
    if (this->count_ != that.count())
      return this->count_ < that.count();
    size_t i = this->size();
    if (!i)
      return false;
    do {
      --i;
      if (this->chunks_[i] != that.chunks()[i])
        return (this->chunks_[i] < that.chunks()[i]) ^ (this->count_ < 0);
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

  extended_int operator-() const {
    extended_int ret_val = *this;
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
    if (e1.count() < 0)
      this->count_ = -this->count_;
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
    if (e1.count() < 0)
      this->count_ = -this->count_;
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
      this->count_ = 0;
      return;
    }
    mul(e1.chunks(), e1.size(), e2.chunks(), e2.size());
    if ((e1.count() > 0) ^ (e2.count() > 0))
      this->count_ = -this->count_;
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
      } else if (sz == 2) {
        ret_val.first = static_cast<fpt64>(this->chunks_[1]) *
                        static_cast<fpt64>(0x100000000LL) +
                        static_cast<fpt64>(this->chunks_[0]);
      } else {
        for (size_t i = 1; i <= 3; ++i) {
          ret_val.first *= static_cast<fpt64>(0x100000000LL);
          ret_val.first += static_cast<fpt64>(this->chunks_[sz - i]);
        }
        ret_val.second = (sz - 3) << 5;
      }
    }
    if (this->count_ < 0)
      ret_val.first = -ret_val.first;
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
      temp += static_cast<uint64>(c1[i]) + static_cast<uint64>(c2[i]);
      this->chunks_[i] = static_cast<uint32>(temp & kUInt64LowMask);
      temp >>= 32;
    }
    for (size_t i = sz2; i < sz1; ++i) {
      temp += static_cast<uint64>(c1[i]);
      this->chunks_[i] = static_cast<uint32>(temp & kUInt64LowMask);
      temp >>= 32;
    }
    if (temp && (this->count_ != N)) {
      this->chunks_[this->count_] = static_cast<uint32>(temp & kUInt64LowMask);
      ++this->count_;
    }
  }

  void dif(const uint32* c1, size_t sz1,
           const uint32* c2, size_t sz2, bool rec = false) {
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
        }
      } while (sz1);
      if (!sz1) {
        this->count_ = 0;
        return;
      }
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
    if (this->chunks_[this->count_])
      ++this->count_;
  }

  void mul(const uint32* c1, size_t sz1, const uint32* c2, size_t sz2) {
    uint64 cur = 0, nxt, tmp;
    this->count_ = static_cast<int32>((std::min)(N, sz1 + sz2 - 1));
    for (size_t shift = 0; shift < static_cast<size_t>(this->count_);
         ++shift) {
      nxt = 0;
      for (size_t first = 0; first <= shift; ++first) {
        if (first >= sz1)
          break;
        size_t second = shift - first;
        if (second >= sz2)
          continue;
        tmp = static_cast<uint64>(c1[first]) * static_cast<uint64>(c2[second]);
        cur += tmp & kUInt64LowMask;
        nxt += tmp >> 32;
      }
      this->chunks_[shift] = static_cast<uint32>(cur & kUInt64LowMask);
      cur = nxt + (cur >> 32);
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

  fpt64 operator()(const extended_exponent_fpt<fpt64>& that) const {
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

// Voronoi coordinate type traits make it possible to extend algorithm
// input coordinate range to any user provided integer type and algorithm
// output coordinate range to any ieee-754 like floating point type.
template <typename T>
struct voronoi_ctype_traits;

template <>
struct voronoi_ctype_traits<int32> {
  typedef int32 int_type;
  typedef int64 int_x2_type;
  typedef uint64 uint_x2_type;
  typedef extended_int<64> big_int_type;
  typedef fpt64 fpt_type;
  typedef extended_exponent_fpt<fpt_type> efpt_type;
  typedef ulp_comparison<fpt_type> ulp_cmp_type;
  typedef type_converter_fpt to_fpt_converter_type;
  typedef type_converter_efpt to_efpt_converter_type;
};
}  // detail
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_DETAIL_VORONOI_CTYPES
