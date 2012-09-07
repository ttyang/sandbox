

// This is an incomplete 128 bit integer class...
// Current purpose is just to support the 'long long' rational class test.


template <typename HHalf, typename LHalf>
class IntNum //: boost::operators<IntNum>
{
public:
    HHalf valH;           // Public, so no friending needed
    LHalf valL;           // Should always be unsigned of same size as HHalf.

    IntNum(long long n = 0) : valL((LHalf)n),valH((HHalf)((n>>(sizeof(LHalf)*8-1))>>1) )  {}
    IntNum(long long _valH, unsigned long long _valL) : valL((LHalf)_valL),valH((HHalf)_valH)  {}

    IntNum& operator+= (const IntNum& rhs) { valL +=  rhs.valL; valH +=  rhs.valH + (valL< rhs.valL);   return *this; }
    IntNum& operator-= (const IntNum& rhs) { 
        valH += ~rhs.valH + (valL>=rhs.valL); 
        valL -=  rhs.valL; 
        return *this; }
    IntNum& operator*= (const IntNum& rhs);
    IntNum& operator/= (const IntNum& rhs);
    IntNum& operator%= (const IntNum& rhs);
    IntNum& operator|= (const IntNum& rhs) { valL |= rhs.valL; valH |= rhs.valH; return *this; }
    IntNum& operator&= (const IntNum& rhs) { valL &= rhs.valL; valH &= rhs.valH; return *this; }
    IntNum& operator^= (const IntNum& rhs) { valL ^= rhs.valL; valH ^= rhs.valH; return *this; }
    IntNum& operator<<=(int shiftAmt) {
        const LHalf numB = sizeof(LHalf)*CHAR_BIT;
        if(shiftAmt < numB)
        {
            this->valH = (this->valH<<shiftAmt) | (this->valL>>(numB-shiftAmt));
            this->valL <<= shiftAmt;
        }
        else
        {
            this->valH = (this->valL<<(shiftAmt-numB));
            this->valL = 0;
        }
        return *this;
    }
    IntNum& operator>>=(int shiftAmt) {
        const LHalf numB = sizeof(LHalf)*CHAR_BIT;
        if(shiftAmt < numB)
        {
            this->valL = (this->valL>>shiftAmt) | (this->valH<<(numB-shiftAmt));
            this->valH >>= shiftAmt;
        }
        else if(shiftAmt <= numB*2)
        {
            this->valL = (this->valH>>(shiftAmt-numB));
            this->valH >>= numB;
        }
        else
        {
            this->valH >>= numB;
            this->valL = this->valH;
        }
        return *this;
    }

    const IntNum& operator++()    { valH += (++valL?0:1); return *this; }    // prefix
    const IntNum& operator--()    { valH -= (valL--?0:1); return *this; }    // prefix
    const IntNum  operator++(int) {  IntNum cResult(valH,valL); ++(*this); return cResult; } // postfix
    const IntNum  operator--(int) {  IntNum cResult(valH,valL); --(*this); return cResult; } // postfix


    bool operator! () const { return !valH && !valL; }

private:
    void some_function () {}

public:
    typedef void (IntNum:: * safe_bool_type) ();
    operator safe_bool_type () const  { return (valH|valL) ? &IntNum::some_function : 0; }

};

template <typename HHalf, typename LHalf>   // <long long, unsigned long long>
inline IntNum<HHalf, LHalf> operator+(const IntNum<HHalf, LHalf>& rhs) { return rhs; }  // unary +

template <typename HHalf, typename LHalf>
inline IntNum<HHalf, LHalf> operator-(const IntNum<HHalf, LHalf>& rhs) { IntNum<HHalf, LHalf> tmp(~rhs.valH, ~rhs.valL+1); if(tmp.valL==0) ++tmp.valH; return tmp; } // Unary -

template <typename HHalf, typename LHalf>
inline std::ostream& operator<<(std::ostream& os, const IntNum<HHalf, LHalf>& i) { os << std::hex << std::setfill(' ') << std::setw(16) << i.valH << ":" << std::setfill('0') << std::setw(16) << i.valL; return os; }

//template <typename HHalf, typename LHalf>
//inline std::istream& operator>>(std::istream& is, IntNum<HHalf, LHalf>& i) { is >> i.val; return is; }

template <typename HHalf, typename LHalf>
bool operator == (const IntNum<HHalf, LHalf> & p_oLeft, const IntNum<HHalf, LHalf> & p_oRight) // A == B
{ return (p_oLeft.valL == p_oRight.valL) && (p_oLeft.valH == p_oRight.valH);}

template <typename HHalf, typename LHalf>
bool operator != (const IntNum<HHalf, LHalf> & p_oLeft, const IntNum<HHalf, LHalf> & p_oRight) // A != B
{ return (p_oLeft.valL != p_oRight.valL) || (p_oLeft.valH != p_oRight.valH);}

template <typename HHalf, typename LHalf>
bool operator == (const IntNum<HHalf, LHalf> & p_oLeft, const __int64 & p_oRight) // A == B
{ return ((__int64)p_oLeft.valL == p_oRight) && ((__int64)p_oLeft.valH == (p_oRight>>63));}

//template <typename HHalf, typename LHalf>
//bool operator == (const IntNum<HHalf, LHalf> & p_oLeft, const int & p_oRight) // A == B
//{ return (p_oLeft.valL == (__int64)p_oRight) && (p_oLeft.valH == (((__int64)p_oRight)>>31));}

template <typename HHalf, typename LHalf>
bool operator < (const IntNum<HHalf, LHalf> & p_oLeft, const IntNum<HHalf, LHalf> & p_oRight) // A < B
{
   return (p_oLeft.valH < p_oRight.valH ? true : p_oLeft.valH > p_oRight.valH ? false : 
        /*  p_oLeft.valH < 0 ? p_oRight.valL > p_oLeft.valL : */ p_oLeft.valL < p_oRight.valL);
}

template <typename HHalf, typename LHalf>
bool operator<= (const IntNum<HHalf, LHalf>& lhs, const IntNum<HHalf, LHalf>& rhs)  { return (lhs < rhs) || (lhs == rhs); }

template <typename HHalf, typename LHalf>
bool operator>  (const IntNum<HHalf, LHalf>& lhs, const IntNum<HHalf, LHalf>& rhs)  { return !(lhs <= rhs); }

template <typename HHalf, typename LHalf>
bool operator>= (const IntNum<HHalf, LHalf>& lhs, const IntNum<HHalf, LHalf>& rhs)  { return !(lhs < rhs) || (lhs == rhs); }

template <typename HHalf, typename LHalf>
inline IntNum<HHalf, LHalf> abs(IntNum<HHalf, LHalf> rhs) { if (rhs < IntNum<HHalf, LHalf>()) rhs = -rhs; return rhs; }

#if 1
template <typename HHalf, typename LHalf>
inline IntNum<HHalf, LHalf> operator<<(const IntNum<HHalf, LHalf>& lhs, int shiftAmt)
{
    const LHalf numB = sizeof(LHalf)*CHAR_BIT;
    IntNum<HHalf, LHalf> result(lhs.valH,lhs.valL);
    if(shiftAmt > 0)
    {
        if(shiftAmt < numB)
        {
            result.valH = (result.valH<<shiftAmt) | (result.valL>>(numB-shiftAmt));
            result.valL <<= shiftAmt;
        }
        else
        {
            result.valH = (result.valL<<(shiftAmt-numB));
            result.valL = 0;
        }
    }
    return result;
}

template <typename HHalf, typename LHalf>
inline IntNum<HHalf, LHalf> operator>>(const IntNum<HHalf, LHalf>& lhs, int shiftAmt)
{
    const LHalf numB = sizeof(LHalf)*CHAR_BIT;
    IntNum<HHalf, LHalf> result(lhs.valH,lhs.valL);
    if(shiftAmt > 0)
    {
        if(shiftAmt < numB)
        {
            result.valL = (result.valL>>shiftAmt) | (result.valH<<(numB-shiftAmt));
            result.valH >>= shiftAmt;
        }
        else if(shiftAmt <= numB*2)
        {
            result.valL = (result.valH>>(shiftAmt-numB));
            result.valH >>= numB;
        }
        else
        {
            result.valH >>= numB;
            result.valL = result.valH;
        }
    }
    return result;
}
#else
IntNum IntNum::operator<<(int shiftAmt)
{
    IntNum result(this->valH,this->valL);
    if(shiftAmt > 0)
    {
        if(shiftAmt < 64)
        {
            result.valH = (result.valH<<shiftAmt) | (result.valL>>(64-shiftAmt));
            result.valL <<= shiftAmt;
        }
        else
        {
            result.valH = (result.valL<<(shiftAmt-64));
            result.valL = 0;
        }
    }
    return result;
}
IntNum IntNum::operator>>(int shiftAmt)
{
    IntNum result(this->valH,this->valL);
    if(shiftAmt > 0)
    {
        if(shiftAmt < 64)
        {
            result.valL = (result.valL>>shiftAmt) | (result.valH<<(64-shiftAmt));
            result.valH >>= shiftAmt;
        }
        else if(shiftAmt <= 128)
        {
            result.valL = (result.valH>>(shiftAmt-64));
            result.valH >>= 64;
        }
        else
        {
            result.valH >>= 64;
            result.valL = result.valH;
        }
    }
    return result;
}
#endif

template <typename HHalf, typename LHalf>
IntNum<HHalf, LHalf> operator- (const IntNum<HHalf, LHalf> & p_oLeft, const IntNum<HHalf, LHalf> & p_oRight) // A - B
{
   IntNum<HHalf, LHalf> oResult(~p_oRight.valH, ~p_oRight.valL+1);
   if(oResult.valL==0) ++oResult.valH;
   oResult.valL += p_oLeft.valL;
   oResult.valH += p_oLeft.valH;
   if(oResult.valL < p_oLeft.valL) ++oResult.valH;
   return oResult;
}

//IntNum operator- (const IntNum & rhs) {IntNum tmp(rhs.valH - (rhs.valL==0), rhs.valL-1); return tmp;}
//IntNum& operator-= (IntNum& lhs, const IntNum& rhs) { lhs = lhs - rhs; return lhs; }


template <typename HHalf, typename LHalf>
IntNum<HHalf, LHalf> operator~ (const IntNum<HHalf, LHalf> & p_oRight) //~A
{
   IntNum<HHalf, LHalf> oResult(~p_oRight.valH, ~p_oRight.valL);
   return oResult;
}

template <typename HHalf, typename LHalf>
IntNum<HHalf, LHalf> operator/ (const IntNum<HHalf, LHalf> & p_oLeft, const IntNum<HHalf, LHalf> & p_oRight) // A / B
{
   IntNum<HHalf, LHalf> oResult(p_oLeft.valH, p_oLeft.valL);

   oResult /= p_oRight;

   return oResult;
}

template <typename HHalf, typename LHalf>
IntNum<HHalf, LHalf> operator% (const IntNum<HHalf, LHalf> & p_oLeft, const IntNum<HHalf, LHalf> & p_oRight) // A % B
{
   IntNum<HHalf, LHalf> oResult(p_oLeft.valH, p_oLeft.valL);

   oResult %= p_oRight;

   return oResult;
}

template <typename HHalf, typename LHalf>
IntNum<HHalf, LHalf>& IntNum<HHalf, LHalf>::operator*= (const IntNum<HHalf, LHalf>& rhs)
{
    const IntNum<HHalf, LHalf> Zero(0,0);
    IntNum<HHalf, LHalf> F1(this->valH,this->valL);
    IntNum<HHalf, LHalf> F2(rhs.valH,rhs.valL);

    LHalf  X,Acc;
    const LHalf halfnumB = sizeof(LHalf)*CHAR_BIT/2;
    const LHalf LoHalfMask = (((LHalf)(1))<<halfnumB)-1;
    LHalf  a1 = (F1.valL>>halfnumB), a0 = F1.valL&LoHalfMask,
           a3 = (F1.valH>>halfnumB), a2 = F1.valH&LoHalfMask;
    LHalf  b1 = (F2.valL>>halfnumB), b0 = F2.valL&LoHalfMask,
           b3 = (F2.valH>>halfnumB), b2 = F2.valH&LoHalfMask;

    this->valH = 0;
    this->valL = a0 * b0;
    Acc = this->valL >> halfnumB;

    X   = a0*b1;
    Acc += X;  if(Acc < X) ++this->valH;  // Shift up later

    X   = a1*b0;
    Acc += X;  if(Acc < X) ++this->valH;  // Shift up later

    this->valL <<= halfnumB;
    this->valL = (this->valL>>halfnumB) + (Acc<<halfnumB);

    this->valH = (Acc>>halfnumB) + (this->valH <<halfnumB);

    this->valH +=  a2*b0;
    this->valH +=  a0*b2;
    this->valH +=  a1*b1;

    Acc  = (a3*b0) << halfnumB;
    Acc += (a0*b3) << halfnumB;
    Acc += (a2*b1) << halfnumB;
    this->valH +=  Acc + ((a1*b2) << halfnumB);

    return *this;
}

template <typename HHalf, typename LHalf>
IntNum<HHalf, LHalf>& IntNum<HHalf, LHalf>::operator/= (const IntNum<HHalf, LHalf>& rhs)
{
    const IntNum<HHalf, LHalf> Zero(0,0);
    IntNum<HHalf, LHalf> F1(this->valH,this->valL);   // Numerator
    IntNum<HHalf, LHalf> F2(rhs.valH,rhs.valL);       // Denominator

    if(F2 == Zero)   // Divide by zero
    {
      //  throw div_by_zero;
        F2.valL = F2.valL / F2.valL;
    }
    else if(F1 == F2)
    {
        this->valH = 0;
        this->valL = 1;
    }
    else if(F1 == 0)
    {
        this->valH = 0;
        this->valL = 0;
    }
    else
    {
        bool bNegate = false;
        if(F1 < Zero)
        {
            if(F2 > Zero)
            {
                F1 = -F1;
                bNegate = true;
            }
            else  // F1<0 and F2<0
            {
                if((F2.valL == 0) && ((HHalf)(F2.valH << 1) == 0))
                {
                    this->valL = 0;
                    this->valH = 0;
                    return *this;
                }
                F1 = -F1;
                F2 = -F2;
            }
        }
        else // (F1 > 0)
        {
            if(F2 < Zero)
            {
                if((F2.valL == 0) && ((HHalf)(F2.valH << 1) == 0))
                {
                    this->valL = 0;
                    this->valH = 0;
                    return *this;
                }
                F2 = -F2;
                bNegate = true;
            }
        }

        const LHalf numB = sizeof(LHalf)*CHAR_BIT;
        IntNum<HHalf, LHalf>  Quo(0,0), Rem(0,0), Dnd(0,0);
        int x=0;

#if 1  // Optional optimization
        if (F1.valH == 0)  
        {
            F1.valH = F1.valL;
            x=numB;
        }
#endif
        for(; x<numB*2; ++x)
        {
            Dnd <<= 1;
            if(F1.valH < 0) ++Dnd;
            F1 <<= 1;
            Quo <<= 1;
            if(((LHalf)Dnd.valH > (LHalf)F2.valH) ||
                     ( Dnd.valH == F2.valH && (LHalf)Dnd.valL >= (LHalf)F2.valL))
            {
                ++Quo;  Dnd-=F2;
            }
        }

        this->valL = Quo.valL;
        this->valH = Quo.valH;

        if(bNegate)
        {
            *this = -*this;
        }
    }

    return *this;
}

template <typename HHalf, typename LHalf>
IntNum<HHalf, LHalf> operator* (const IntNum<HHalf, LHalf>& lhs, const IntNum<HHalf, LHalf>& rhs)
{
    IntNum<HHalf, LHalf> tmp(lhs);
    tmp *= rhs;
    return tmp;
}

template <typename HHalf, typename LHalf>
IntNum<HHalf, LHalf>& IntNum<HHalf, LHalf>::operator%= (const IntNum<HHalf, LHalf>& rhs)
{
    IntNum<HHalf, LHalf> div = *this / rhs;    // Capture remainder??
    *this = *this - (div * rhs);
    return *this;
}

template <typename HHalf, typename LHalf>
IntNum<HHalf, LHalf> operator+ (const IntNum<HHalf, LHalf>& lhs, const IntNum<HHalf, LHalf>& rhs)
{
    IntNum<HHalf, LHalf> tmp(lhs);
    tmp += rhs;
    return tmp;
}

template <typename HHalf, typename LHalf>
IntNum<HHalf, LHalf> operator& (const IntNum<HHalf, LHalf> & A, const IntNum<HHalf, LHalf> & B)
{
    IntNum<HHalf, LHalf> tmp(B);
    tmp &= A;
    return tmp;
}

template <typename HHalf, typename LHalf>
IntNum<HHalf, LHalf> operator| (const IntNum<HHalf, LHalf> & A, const IntNum<HHalf, LHalf> & B)
{
    IntNum<HHalf, LHalf> tmp(B);
    tmp |= A;
    return tmp;
}

template <typename HHalf, typename LHalf>
IntNum<HHalf, LHalf> operator^ (const IntNum<HHalf, LHalf> & A, const IntNum<HHalf, LHalf> & B)
{
    IntNum<HHalf, LHalf> tmp(B);
    tmp ^= A;
    return tmp;
}

typedef IntNum<long long, unsigned long long>  Int128;
typedef IntNum<signed char, unsigned char>  Int16;


namespace std
{

template < >
class numeric_limits< Int128 >
{
    // Get some numeric limits from type 'int'
    typedef numeric_limits<int>  limits_type;

public:
    static const bool is_specialized = true;

    static Int128 min BOOST_PREVENT_MACRO_SUBSTITUTION () throw()
    { return Int128(0x8000000000000000,0x0000000000000000); }
    static Int128 max BOOST_PREVENT_MACRO_SUBSTITUTION () throw()
    { return Int128(0x7fffffffffffffff,0xffffffffffffffff); }

    static const int digits      = 127;
    static const int digits10    = 127 * 301L / 1000;
    static const bool is_signed  = true;
    static const bool is_integer = true;
    static const bool is_exact   = true;
    static const int radix       = 2;
    static Int128 epsilon() throw()      { return limits_type::epsilon(); }
    static Int128 round_error() throw()  { return limits_type::round_error(); }

    static const int min_exponent   = limits_type::min_exponent;
    static const int min_exponent10 = limits_type::min_exponent10;
    static const int max_exponent   = limits_type::max_exponent;
    static const int max_exponent10 = limits_type::max_exponent10;

    static const bool has_infinity             = limits_type::has_infinity;
    static const bool has_quiet_NaN            = limits_type::has_quiet_NaN;
    static const bool has_signaling_NaN        = limits_type::has_signaling_NaN;
    static const float_denorm_style has_denorm = limits_type::has_denorm;
    static const bool has_denorm_loss          = limits_type::has_denorm_loss;

    static Int128 infinity() throw()      { return limits_type::infinity(); }
    static Int128 quiet_NaN() throw()     { return limits_type::quiet_NaN(); }
    static Int128 signaling_NaN() throw() {return limits_type::signaling_NaN();}
    static Int128 denorm_min() throw()    { return limits_type::denorm_min(); }

    static const bool is_iec559  = limits_type::is_iec559;
    static const bool is_bounded = limits_type::is_bounded;
    static const bool is_modulo  = limits_type::is_modulo;

    static const bool traps                    = limits_type::traps;
    static const bool tinyness_before          = limits_type::tinyness_before;
    static const float_round_style round_style = limits_type::round_style;

};  // std::numeric_limits<Int128>
}