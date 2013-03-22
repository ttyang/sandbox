#include <iostream>
#include <iomanip>

//#define BOOST_DISABLE_WIN32
//#include "boost/test/unit_test.hpp"
//#include "boost/test/included/unit_test.hpp"

#include <set>
#include <boost/rational.hpp>  // The new version

#define TEST_LL_RATIONAL  1  // Need an 128bit int to test long long rational
#if TEST_LL_RATIONAL
#include "int128.hpp"
#endif


typedef boost::rational<signed char,boost::rational_check_for_overflow>  RatS8wCK;
typedef boost::rational<signed char,boost::rational_no_checking>         RatS8ref;

typedef boost::rational<short,boost::rational_check_for_overflow>        RatS16wCK;
typedef boost::rational<short,boost::rational_no_checking>               RatRefS16;

typedef boost::rational<int,boost::rational_check_for_overflow>          RatS32wCK;
typedef boost::rational<int,boost::rational_no_checking>                 RatS32ref;

typedef boost::rational<long long,boost::rational_check_for_overflow>    RatSLLwCK;
typedef boost::rational<long long,boost::rational_no_checking>           RatSLLref;


// std:: namespace helpers
#define STD std::
#define COUT std::cout
#define ENDL std::endl
#define DEC std::dec
#define HEX std::hex
//#define STD
//#define COUT cout
//#define ENDL endl

#define VERIFY_RAT_VAL(var, num, dem) \
        if ( var.numerator() != (num)  || var.denominator() != (dem)) { \
            FailCount++; ReportFailure(__FILE__,__LINE__); }

#define SHOULD_OVERFLOW_EXCEPTION(stmt) {\
        bool exceptioned = false; \
        try {  stmt; }\
        catch (boost::rational_overflow Exception) {exceptioned = true;}\
        if(!exceptioned) {\
        { FailCount++;\
          ReportFailure(__FILE__,__LINE__);\
        } } }

#define SHOULD_ZERO_DIVIDE_EXCEPTION(stmt) {\
        bool exceptioned = false; \
        try {  stmt; }\
        catch (boost::bad_rational Exception) {exceptioned = true;}\
        if(!exceptioned) {\
        { FailCount++;\
          ReportFailure(__FILE__,__LINE__);\
        } } }

#define SHOULD_NOT_EXCEPTION(stmt) {\
        bool exceptioned = false; \
        try {  stmt; }\
        catch (boost::rational_overflow Exception) {exceptioned = true;}\
        if(exceptioned) {\
        { FailCount++;\
          ReportFailure(__FILE__,__LINE__);\
        } } }


void ReportFailure(char* filename, int lineNumber)
{
    COUT << ENDL << "Fail reported at " << DEC << lineNumber << " of " << filename << ENDL;
    throw 57;  // Cause any failure to terminate program!!!
    // Comment out the 'throw' to allow test to run through failures.
}




unsigned long long testRationalConstruction(void)
{
    COUT << ENDL << "Starting rational construction tests" << ENDL; 
    unsigned long long FailCount(0);

    {  // No parameter constructor
        RatS8wCK  ratValA;  VERIFY_RAT_VAL(ratValA, 0, 1);
        RatS8ref  ratValB;  VERIFY_RAT_VAL(ratValB, 0, 1);
        RatS16wCK ratValC;  VERIFY_RAT_VAL(ratValC, 0, 1);
        RatRefS16 ratValD;  VERIFY_RAT_VAL(ratValD, 0, 1);
        RatS32wCK ratValE;  VERIFY_RAT_VAL(ratValE, 0, 1);
        RatS32ref ratValF;  VERIFY_RAT_VAL(ratValF, 0, 1);
        RatSLLwCK ratValG;  VERIFY_RAT_VAL(ratValG, 0, 1);
        RatSLLref ratValH;  VERIFY_RAT_VAL(ratValH, 0, 1);
    }

    {  // One parameter constructor
        RatS8wCK  ratValA(57);  VERIFY_RAT_VAL(ratValA, 57, 1);
        RatS8ref  ratValB(57);  VERIFY_RAT_VAL(ratValB, 57, 1);
        RatS16wCK ratValC(57);  VERIFY_RAT_VAL(ratValC, 57, 1);
        RatRefS16 ratValD(57);  VERIFY_RAT_VAL(ratValD, 57, 1);
        RatS32wCK ratValE(57);  VERIFY_RAT_VAL(ratValE, 57, 1);
        RatS32ref ratValF(57);  VERIFY_RAT_VAL(ratValF, 57, 1);
        RatSLLwCK ratValG(57);  VERIFY_RAT_VAL(ratValG, 57, 1);
        RatSLLref ratValH(57);  VERIFY_RAT_VAL(ratValH, 57, 1);
    }

    {  // Two parameter constructor
        RatS8wCK  ratValA(7,99);  VERIFY_RAT_VAL(ratValA, 7, 99);   COUT << ratValA << ENDL;
        RatS8ref  ratValB(7,99);  VERIFY_RAT_VAL(ratValB, 7, 99);   COUT << ratValB << ENDL;
        RatS16wCK ratValC(7,99);  VERIFY_RAT_VAL(ratValC, 7, 99);   COUT << ratValC << ENDL;
        RatRefS16 ratValD(7,99);  VERIFY_RAT_VAL(ratValD, 7, 99);   COUT << ratValD << ENDL;
        RatS32wCK ratValE(7,99);  VERIFY_RAT_VAL(ratValE, 7, 99);   COUT << ratValE << ENDL;
        RatS32ref ratValF(7,99);  VERIFY_RAT_VAL(ratValF, 7, 99);   COUT << ratValF << ENDL;
        RatSLLwCK ratValG(7,99);  VERIFY_RAT_VAL(ratValG, 7, 99);   COUT << ratValG << ENDL;
        RatSLLref ratValH(7,99);  VERIFY_RAT_VAL(ratValH, 7, 99);   COUT << ratValH << ENDL;
    }

    // Test overflow on construction of max neg denominator
    if(1 && (-SCHAR_MAX != SCHAR_MIN)) // Only test if negative, positive numbers not symetric
    {
        signed char      denChar  = SCHAR_MIN;
        signed short     denShort = SHRT_MIN;
        signed int       denInt = INT_MIN;
        signed long long denLL = LLONG_MIN;

        SHOULD_OVERFLOW_EXCEPTION( RatS8wCK RA(1, denChar) );
        SHOULD_NOT_EXCEPTION( RatS8wCK RA(1, denChar+1) );
        SHOULD_OVERFLOW_EXCEPTION( RatS16wCK RA(1, denShort) );
        SHOULD_NOT_EXCEPTION( RatS16wCK RA(1, denShort+1) );
        SHOULD_OVERFLOW_EXCEPTION( RatS32wCK RA(1, denInt) );
        SHOULD_NOT_EXCEPTION( RatS32wCK RA(1, denInt+1) );
        SHOULD_OVERFLOW_EXCEPTION( RatSLLwCK RA(1, denLL) );
        SHOULD_NOT_EXCEPTION( RatSLLwCK RA(1, denLL+1) );
    }
    else
    {
        COUT << "Max negative denominator test skipped, negative and positive numbers are symetric!" << ENDL;
    }

    COUT << ENDL;
    if(FailCount) COUT << "Fail count " << DEC << FailCount << "  " << ENDL;
    else          COUT << "All Passed" << ENDL;
    COUT << ENDL;

    return FailCount;
}

template <typename RefT, typename TstT>
int TestRationalPair( RefT& RefA, RefT& RefB, TstT& TstA, TstT& TstB)
{
    RefT RefVal;
    TstT TstVal;
    bool ovfl,refLT,tstLT;
    int FailCount=0;

    refLT = RefA < RefB;
    tstLT = TstA < TstB;
    //COUT << DEC << refLT << ": " << RefA << " "  <<  RefB << ENDL;
    //COUT << DEC << tstLT << ": " << TstA << " "  <<  TstB << ENDL;
    if (refLT != tstLT)
    { 
        FailCount++; ReportFailure(__FILE__,__LINE__);
    }

    refLT = RefA <= RefB;
    tstLT = TstA <= TstB;
    //COUT << DEC << refLT << ": " << RefA << " "  <<  RefB << ENDL;
    //COUT << DEC << tstLT << ": " << TstA << " "  <<  TstB << ENDL;
    if (refLT != tstLT)
    { 
        FailCount++; ReportFailure(__FILE__,__LINE__);
    }

    refLT = RefA == RefB;
    tstLT = TstA == TstB;
    if (refLT != tstLT)
    { 
        FailCount++; ReportFailure(__FILE__,__LINE__);
    }

    // '+' tests
    RefVal = RefA + RefB;
    try {ovfl = false; TstVal = TstA + TstB; }
    catch (boost::rational_overflow Exception) {ovfl = true; }

    if((RefVal.numerator() == TstVal.numerator()) && (RefVal.denominator() == TstVal.denominator()))
    {
        if(ovfl) { FailCount++; ReportFailure(__FILE__,__LINE__); }
    }
    else
    {
        if(!ovfl) { FailCount++; ReportFailure(__FILE__,__LINE__); }
    }

    // '-' tests
    RefVal = RefA - RefB;
    try {ovfl = false; TstVal = TstA - TstB; }
    catch (boost::rational_overflow Exception) {ovfl = true; }

    if((RefVal.numerator() == TstVal.numerator()) && (RefVal.denominator() == TstVal.denominator()))
    {
        if(ovfl) { FailCount++; ReportFailure(__FILE__,__LINE__); }
    }
    else
    {
        if(!ovfl) { FailCount++; ReportFailure(__FILE__,__LINE__); }
    }

    // '*' tests
    RefVal = RefA * RefB;
    try {ovfl = false; TstVal = TstA * TstB; }
    catch (boost::rational_overflow Exception) {ovfl = true; }

    if((RefVal.numerator() == TstVal.numerator()) && (RefVal.denominator() == TstVal.denominator()))
    {
        if(ovfl) { FailCount++; ReportFailure(__FILE__,__LINE__); }
    }
    else
    {
        if(!ovfl) { FailCount++; ReportFailure(__FILE__,__LINE__); }
    }

    // '/' tests
    if(RefB.numerator() != 0)
    { // Skip divide by zero cases

        RefVal = RefA / RefB;
        try {ovfl = false; TstVal = TstA / TstB; }
        catch (boost::rational_overflow Exception) {ovfl = true; }

        if((RefVal.numerator() == TstVal.numerator()) && (RefVal.denominator() == TstVal.denominator()))
        {
            if(ovfl) { FailCount++; ReportFailure(__FILE__,__LINE__); }
        }
        else
        {
            if(!ovfl) { FailCount++; ReportFailure(__FILE__,__LINE__); }
        }
    }

    return FailCount;
}



template <typename RatT, typename RatRefT>
unsigned long long BinarySetTest(std::set<RatT>& valSet)
{
    unsigned long long FailureCount = 0;
    RatT A,B;
    RatRefT RefA,RefB;
    std::set<RatT>::iterator x;
    std::set<RatT>::iterator y;

    COUT << DEC << valSet.size() << " values in set" << ENDL;
    long long X=0,XX=valSet.size();
    for (x=valSet.begin(); x!=valSet.end(); x++)
    {
        COUT << "%" << DEC << (X*100)/XX << ": Pass " << X << " of " << XX << "    \r"; 
        X++;
        for (y=valSet.begin(); y!=valSet.end(); y++)
        {
            A = *x;
            B = *y;
            RefB.assign(B.numerator(), B.denominator());
            RefA.assign(A.numerator(), A.denominator());
// Visual C++ bug?? If RefA and RefB reversed, RefA gets wrong val (in release, not debug)
////COUT << DEC << A.numerator() << " "  <<  A.denominator() << ENDL;
//COUT << RefA << " "  <<  RefB << ENDL;
//COUT << A << " "  <<  B << ENDL;

            // =========================================
            // Test operators
            // =========================================
            FailureCount += TestRationalPair(RefA,RefB,A,B);
        }
    }
    return FailureCount;
}



unsigned long long testS8rationalsQuick()
{
    COUT << ENDL << "Starting quick S8 rational tests" << ENDL; 
    unsigned long long FailCount = 0;
    typedef RatS8wCK  RatS8true;
    std::set<RatS8wCK> valSet;

    std::set<signed char> valCompSet;
    valCompSet.insert(    0 );
    valCompSet.insert(    1 );
    valCompSet.insert(    2 );
    valCompSet.insert(    3 );
    valCompSet.insert(    4 );
    valCompSet.insert(    5 );
    valCompSet.insert(    6 );
    valCompSet.insert(    7 );
    valCompSet.insert(    8 );
    valCompSet.insert(    9 );
    valCompSet.insert(   -1 );
    valCompSet.insert(   -2 );
    valCompSet.insert(   -3 );
    valCompSet.insert(   -4 );
    valCompSet.insert(   -5 );
    valCompSet.insert(   -6 );
    valCompSet.insert(   -7 );
    valCompSet.insert(  126 );
    valCompSet.insert(  127 );
    valCompSet.insert( -128 );
    valCompSet.insert( -127 );
    valCompSet.insert( -126 );

    std::set<signed char>::iterator x;
    std::set<signed char>::iterator y;

    COUT << DEC << valCompSet.size() << " values in valCompSet set" << ENDL;
    for (x=valCompSet.begin(); x!=valCompSet.end(); x++)
    {
        for (y=valCompSet.begin(); y!=valCompSet.end(); y++)
        {         
            if(*y != 0)        
            {
                //COUT << DEC << *x << "   " << *y << ENDL;
                try { valSet.insert( RatS8wCK( *x, *y )); } catch (boost::rational_overflow Exception) { bool ovfl = true; }
                try { valSet.insert( RatS8wCK(-*x, *y )); } catch (boost::rational_overflow Exception) { bool ovfl = true; }
            }
        }
    }

    // Assure specific values
    valSet.insert( RatS8wCK((signed char)       0, (signed char)1) );

    FailCount += BinarySetTest<RatS8wCK, RatRefS16>(valSet);

    COUT << ENDL;
    if(FailCount) COUT << "Fail count " << DEC << FailCount << "  " << ENDL;
    else          COUT << "All Passed" << ENDL; 
    COUT << ENDL;

    return FailCount;
}


unsigned long long testS8rationals()
{
    COUT << ENDL << "Starting S8 rational tests" << ENDL; 
    long long FailCount = 0;
    typedef RatS8wCK  RatS8true;
    std::set<RatS8true> valSet;
    signed char a,b;
    int Count = 1; // One for the "zero" value. Zero value(s) normalize to denominator == 1.

    a=0;
    while(1) // For all values of a (numerator)...
    {
        COUT << DEC << (int)a << "     \r";
        b=0;
        while(++b > 0) // Only want 1 to max positive for denominator
        {
            RatS8true RA(a, b);
            valSet.insert(RA);
            if(a!=RA.numerator())
                continue; // Just want unique rational values.

            if(RA.numerator()==0)
                continue; // Don't count zeros..., there's only one after normalization.

            Count++;
        }
        if(++a == 0)
            break;
    }
    COUT << "Number of unique 8bit rationals: " << DEC << Count << ENDL;
    COUT << "Number of unique 8bit rationals: " << DEC << valSet.size() << ENDL;

    FailCount += BinarySetTest<RatS8true,RatRefS16>(valSet);

    COUT << ENDL;
    if(FailCount) COUT << "Fail count " << DEC << FailCount << "  " << ENDL;
    else          COUT << "All Passed" << ENDL; 
    COUT << ENDL;

    return FailCount;
}   // 19895 for typical signed 8 bit numbers         


unsigned long long testRationalS8IncDec(void)
{
    COUT << ENDL << "Starting 8 bit rational increment/decrement tests" << ENDL; 
    unsigned long long FailCount(0);
    bool ovfl;
    signed char numA,denA,n;
    RatRefS16 RefA;
    RatS8wCK A;

    numA=0;
    while(1) // For all values of numA (numerator)...
    {
        denA=0;
        while(++denA > 0) // Only want 1 to max positive for denominator
        {
            A.assign(numA, denA);
            if(numA!=A.numerator())
                continue; // Just want unique rational values.

            COUT << DEC << (int)numA << " " << (int)denA << "    \r";

            A.assign(numA, denA);
            RefA.assign(numA, denA);

            // =========================================
            // Test increment
            // =========================================
            RefA++;
            try {ovfl = false; A++; }
            catch (boost::rational_overflow Exception) {ovfl = true; }

            if((A.numerator() == RefA.numerator()) && (A.denominator() == RefA.denominator()))
            {
                if(ovfl) { FailCount++; ReportFailure(__FILE__,__LINE__); }
            }
            else
            {
                if(!ovfl) { FailCount++; ReportFailure(__FILE__,__LINE__); }
            }


            // =========================================
            // Test decrement
            // =========================================
            A.assign(numA, denA);
            RefA.assign(numA, denA);
            RefA--;
            try {ovfl = false; A--; }
            catch (boost::rational_overflow Exception) {ovfl = true; }

            if((A.numerator() == RefA.numerator()) && (A.denominator() == RefA.denominator()))
            {
                if(ovfl) { FailCount++; ReportFailure(__FILE__,__LINE__); }
            }
            else
            {
                if(!ovfl) { FailCount++; ReportFailure(__FILE__,__LINE__); }
            }

            n=0;
            while(1) // For all values of n...
            {
                A.assign(numA, denA);
                RefA.assign(numA, denA);

                // =========================================
                // Test + n
                // =========================================
                RefA += n;
                try {ovfl = false; A+=n; }
                catch (boost::rational_overflow Exception) {ovfl = true; }

                if((A.numerator() == RefA.numerator()) && (A.denominator() == RefA.denominator()))
                {
                    if(ovfl) { FailCount++; ReportFailure(__FILE__,__LINE__); }
                }
                else
                {
                    if(!ovfl) { FailCount++; ReportFailure(__FILE__,__LINE__); }
                }


                // =========================================
                // Test - n
                // =========================================
                A.assign(numA, denA);
                RefA.assign(numA, denA);
                RefA -= n;
                try {ovfl = false; A -= n; }
                catch (boost::rational_overflow Exception) {ovfl = true; }

                if((A.numerator() == RefA.numerator()) && (A.denominator() == RefA.denominator()))
                {
                    if(ovfl) { FailCount++; ReportFailure(__FILE__,__LINE__); }
                }
                else
                {
                    if(!ovfl) { FailCount++; ReportFailure(__FILE__,__LINE__); }
                }

                // =========================================
                // Test < n
                // =========================================
                A.assign(numA, denA);
                RefA.assign(numA, denA);
                bool refLT = A < n;
                bool tstLT = RefA < n;
                if (refLT != tstLT) { FailCount++; ReportFailure(__FILE__,__LINE__); }

                if(++n == 0)
                    break;
            }
        }
        if(++numA == 0)
            break;
    }

    COUT << ENDL;
    if(FailCount) COUT << "Fail count " << DEC << FailCount << "  " << ENDL;
    else          COUT << "All Passed" << ENDL; 
    COUT << ENDL;

    return FailCount;
}

unsigned long long testRationalS16Quick()
{
    COUT << ENDL << "Starting quick S16 rational tests" << ENDL; 
    typedef signed short ComponentType;
    unsigned long long FailCount = 0;
    std::set<RatS16wCK> valSet;

    std::set<ComponentType> valCompSet;
    valCompSet.insert(      0 );
    valCompSet.insert(      1 );
    valCompSet.insert(      2 );
    valCompSet.insert(      3 );
    valCompSet.insert(      4 );
    valCompSet.insert(      5 );
    valCompSet.insert(      6 );
    valCompSet.insert(      7 );
    valCompSet.insert(      8 );
    valCompSet.insert(      9 );
    valCompSet.insert(     -1 );
    valCompSet.insert(     -2 );
    valCompSet.insert(     -3 );
    valCompSet.insert(     -4 );
    valCompSet.insert(     -5 );
    valCompSet.insert(     -6 );
    valCompSet.insert(     -7 );
    valCompSet.insert(  16383 );
    valCompSet.insert(  16384 );
    valCompSet.insert(  16385 );
    valCompSet.insert( -16383 );
    valCompSet.insert( -16384 );
    valCompSet.insert( -16385 );
    valCompSet.insert(  32766 );
    valCompSet.insert(  32767 );
    valCompSet.insert( -32768 );
    valCompSet.insert( -32767 );
    valCompSet.insert( -32766 );
    valCompSet.insert(  2*3*5*7 );
    valCompSet.insert( -2*3*5*7 );
    valCompSet.insert(  2*3*5*7*11 );
    valCompSet.insert( -2*3*5*7*11 );
    valCompSet.insert(  2*3*5*7*11*13 );
    valCompSet.insert( -2*3*5*7*11*13 );

    std::set<ComponentType>::iterator x;
    std::set<ComponentType>::iterator y;

    COUT << DEC << valCompSet.size() << " values in valCompSet set" << ENDL;
    for (x=valCompSet.begin(); x!=valCompSet.end(); x++)
    {
        for (y=valCompSet.begin(); y!=valCompSet.end(); y++)
        {         
            if(*y != 0)        
            {
                //COUT << DEC << *x << "   " << *y << ENDL;
                try { valSet.insert( RatS16wCK( *x, *y )); } catch (boost::rational_overflow Exception) { bool ovfl = true; }
                try { valSet.insert( RatS16wCK(-*x, *y )); } catch (boost::rational_overflow Exception) { bool ovfl = true; }
            }
        }
    }

    // Assure specific values
    valSet.insert( RatS16wCK((ComponentType)       0, (ComponentType)1) );

    FailCount += BinarySetTest<RatS16wCK, RatS32ref>(valSet);

    COUT << ENDL;
    if(FailCount) COUT << "Fail count " << DEC << FailCount << "  " << ENDL;
    else          COUT << "All Passed" << ENDL; 
    COUT << ENDL;

    return FailCount;
}



unsigned long long testRationalS16selected(void) 
{
    COUT << ENDL << "Starting 16 bit selected values rational operator tests" << ENDL; 
    unsigned long long FailCount(0);

    const short smax = std::numeric_limits<short>::max BOOST_PREVENT_MACRO_SUBSTITUTION ();
    const short smin = std::numeric_limits<short>::min BOOST_PREVENT_MACRO_SUBSTITUTION ();
    std::set<RatS16wCK> valSet;
    valSet.insert( RatS16wCK((short)0,  (short)1) );
    valSet.insert( RatS16wCK((short)-1, (short)1) );
    valSet.insert( RatS16wCK((short)-1, smax) );
    valSet.insert( RatS16wCK(smax, (short)1) );
    valSet.insert( RatS16wCK((short)1, smax) );
    valSet.insert( RatS16wCK(smin, smax) );

    for (int i=0; i<16; i++) {
    for (int j=0; j<16; j++) {
    for (int m=0; m<16; m++) {
    for (int n=0; n<16; n++)
    {
        try { RatS16wCK ratVal( ((1<<i)|(1<<j)),(1<<m)|(1<<n));  valSet.insert( ratVal ); } catch (boost::rational_overflow Exception) { bool ovfl = true; }
        try { RatS16wCK ratVal(-((1<<i)|(1<<j)),(1<<m)|(1<<n));  valSet.insert( ratVal ); } catch (boost::rational_overflow Exception) { bool ovfl = true; }
    } } } }

    FailCount += BinarySetTest<RatS16wCK,RatS32ref>(valSet);

    COUT << ENDL;
    if(FailCount) COUT << "Fail count " << DEC << FailCount << "  " << ENDL;
    else          COUT << "All Passed" << ENDL; 
    COUT << ENDL;

    return FailCount;
}

unsigned long long testRationalS32selected(void)
{
    COUT << ENDL << "Starting 32 bit selected values rational operator tests" << ENDL; 
    unsigned long long FailCount(0);
    std::set<RatS32wCK> valSet;

    std::set<int> valCompSet;
    valCompSet.insert( 0x00000000 );
    valCompSet.insert( 0x00000001 );
    valCompSet.insert( 0x00000002 );
    valCompSet.insert( 0x00000003 );
    valCompSet.insert( 0x00000004 );
    valCompSet.insert( 0x00000005 );
    valCompSet.insert( 0x00000006 );
    valCompSet.insert( 0x00000007 );
    valCompSet.insert( 0x00000008 );
    valCompSet.insert( 0x00000009 );
    valCompSet.insert( 0x000007FF );
    valCompSet.insert( 0x00007FFF );
    valCompSet.insert( 0x0007FFFF );
    valCompSet.insert( 0x007FFFFF );
    valCompSet.insert( 0x07FFFFFF );
    valCompSet.insert( 0x000007FE );
    valCompSet.insert( 0x00007FFE );
    valCompSet.insert( 0x0007FFFE );
    valCompSet.insert( 0x007FFFFE );
    valCompSet.insert( 0x07FFFFFE );
    valCompSet.insert( 0x00000800 );
    valCompSet.insert( 0x00008000 );
    valCompSet.insert( 0x00080000 );
    valCompSet.insert( 0x00800000 );
    valCompSet.insert( 0x08000000 );
    valCompSet.insert( 0x00000801 );
    valCompSet.insert( 0x00008001 );
    valCompSet.insert( 0x00080001 );
    valCompSet.insert( 0x00800001 );
    valCompSet.insert( 0x08000001 );
    valCompSet.insert( 0x7ffffffe );
    valCompSet.insert( 0x7fffffff );
    valCompSet.insert( 0x80000000 );
    valCompSet.insert( 0x80000001 );
    valCompSet.insert( 0xfffffffe );
    valCompSet.insert( 0xffffffff );
    valCompSet.insert( 0x00010000 );
    valCompSet.insert( 0x00010001 );
    valCompSet.insert( 0x3ffffffe );
    valCompSet.insert( 0x3fffffff );
    valCompSet.insert( 0x40000000 );
    valCompSet.insert( 0x40000001 );
    valCompSet.insert( 0x7ffffffe );
    valCompSet.insert( 0x7fffffff );
    valCompSet.insert( 0x80000000 );
    valCompSet.insert( 0x80000001 );
    valCompSet.insert( 0x80000002 );
    valCompSet.insert( 0x80000003 );
    valCompSet.insert( 0x80000004 );
    valCompSet.insert( 0x80000005 );
    valCompSet.insert( 0x80000006 );
    valCompSet.insert( 0x80000007 );
    valCompSet.insert( 0x80000008 );
    valCompSet.insert( 0x80000009 );
    valCompSet.insert( 0x87fffffe );
    valCompSet.insert( 0x87ffffff );
    valCompSet.insert( 0x80800000 );
    valCompSet.insert( 0x80800001 );
    valCompSet.insert( 0x8ffffffe );
    valCompSet.insert( 0x8fffffff );
    valCompSet.insert( 0x80010000 );
    valCompSet.insert( 0x80010001 );
    valCompSet.insert( 0xa0000000 );
    valCompSet.insert( 0xbffffffe );
    valCompSet.insert( 0xbfffffff );
    valCompSet.insert( 0xffffffff );
    valCompSet.insert( 0xfffffffe );
    valCompSet.insert( 0xfff7fffe );
    valCompSet.insert( 0xffe7fffe );
    valCompSet.insert( 0xffd7fffe );
    valCompSet.insert( 0xffdcfffe );
    valCompSet.insert( INT_MIN );
    valCompSet.insert( INT_MAX );
    valCompSet.insert( INT_MAX>>13 );
    valCompSet.insert( INT_MAX>>14 );
    valCompSet.insert( INT_MAX>>15 );
    valCompSet.insert( INT_MAX>>16 );
    valCompSet.insert( INT_MAX>>17 );
    valCompSet.insert( (INT_MAX>>13)+1 );
    valCompSet.insert( (INT_MAX>>14)+1 );
    valCompSet.insert( (INT_MAX>>15)+1 );
    valCompSet.insert( (INT_MAX>>16)+1 );
    valCompSet.insert( (INT_MAX>>17)+1 );
    valCompSet.insert( (INT_MAX>>13)-1 );
    valCompSet.insert( (INT_MAX>>14)-1 );
    valCompSet.insert( (INT_MAX>>15)-1 );
    valCompSet.insert( (INT_MAX>>16)-1 );
    valCompSet.insert( (INT_MAX>>17)-1 );
    valCompSet.insert( 2*3*5*7*11*13*17 );
    valCompSet.insert( 2*3*5*7*11*11*17 );
    valCompSet.insert( 2*3*5*7*13*13*17 );
    valCompSet.insert( 2*3*5*7*13*13*17*19 );

    std::set<int>::iterator x;
    std::set<int>::iterator y;

    COUT << DEC << valCompSet.size() << " values in valCompSet set" << ENDL;
    for (x=valCompSet.begin(); x!=valCompSet.end(); x++)
    {
        for (y=valCompSet.begin(); y!=valCompSet.end(); y++)
        {         
            if(*y != 0)        
            {
                //COUT << DEC << *x << "   " << *y << ENDL;
                try { valSet.insert( RatS32wCK( *x, *y )); } catch (boost::rational_overflow Exception) { bool ovfl = true; }
                try { valSet.insert( RatS32wCK(-*x, *y )); } catch (boost::rational_overflow Exception) { bool ovfl = true; }
            }
        }
    }

    valSet.insert( RatS32wCK((int)       0, (int)1) );

    RatS32wCK ratVal;
    for (int p=0; p<16; p++)
    {
        try {ratVal.assign( (1<<(p*2))-1, 1 ); valSet.insert( ratVal );     } catch (boost::rational_overflow Exception) { bool ovfl = true; }
        try {ratVal.assign( (1<<(p*2)),   1 ); valSet.insert( ratVal );     } catch (boost::rational_overflow Exception) { bool ovfl = true; }
        try {ratVal.assign( (1<<(p*2))+1, 1 ); valSet.insert( ratVal );     } catch (boost::rational_overflow Exception) { bool ovfl = true; }

        try {ratVal.assign(-(1<<(p*2))-1, 1 ); valSet.insert( ratVal );     } catch (boost::rational_overflow Exception) { bool ovfl = true; }
        try {ratVal.assign(-(1<<(p*2)),   1 ); valSet.insert( ratVal );     } catch (boost::rational_overflow Exception) { bool ovfl = true; }
        try {ratVal.assign(-(1<<(p*2))+1, 1 ); valSet.insert( ratVal );     } catch (boost::rational_overflow Exception) { bool ovfl = true; }

        try {if(p){ratVal.assign(  1, (1<<(p*2))-1); valSet.insert( ratVal ); }   } catch (boost::rational_overflow Exception) { bool ovfl = true; }
        try {ratVal.assign(  1, (1<<(p*2))  ); valSet.insert( ratVal );     } catch (boost::rational_overflow Exception) { bool ovfl = true; }
        try {ratVal.assign(  1, (1<<(p*2))+1); valSet.insert( ratVal );     } catch (boost::rational_overflow Exception) { bool ovfl = true; }

        try {if(p){ratVal.assign( -1, (1<<(p*2))-1); valSet.insert( ratVal ); }   } catch (boost::rational_overflow Exception) { bool ovfl = true; }            
        try {ratVal.assign( -1, (1<<(p*2))  ); valSet.insert( ratVal );     } catch (boost::rational_overflow Exception) { bool ovfl = true; }           
        try {ratVal.assign( -1, (1<<(p*2))+1); valSet.insert( ratVal );     } catch (boost::rational_overflow Exception) { bool ovfl = true; }        
    }

    FailCount += BinarySetTest<RatS32wCK, RatSLLref>(valSet);

    COUT << ENDL;
    if(FailCount) COUT << "Fail count " << DEC << FailCount << "  " << ENDL;
    else          COUT << "All Passed" << ENDL; 
    COUT << ENDL;

    return FailCount;
}

#if TEST_LL_RATIONAL
unsigned long long testRationalS64selected(void)  // Uses 128 bit reference 'int'
{
    COUT << ENDL << "Starting 64 bit selected values rational operator tests" << ENDL; 
    unsigned long long FailCount(0);
    typedef boost::rational<Int128,boost::rational_no_checking>    RatInt128;
    std::set<RatSLLwCK> valSet;

    std::set<long long> valCompSet;
    valCompSet.insert( 0x0000000000000000i64 );
    valCompSet.insert( 0x0000000000000001i64 );
    valCompSet.insert( 0x0000000000000002i64 );
    valCompSet.insert( 0x0000000000000003i64 );
    valCompSet.insert( 0x0000000000000004i64 );
    valCompSet.insert( 0x0000000000000005i64 );
    valCompSet.insert( 0x0000000000000006i64 );
    valCompSet.insert( 0x0000000000000007i64 );
    valCompSet.insert( 0x0000000000000008i64 );
    valCompSet.insert( 0x0000000000000009i64 );
    valCompSet.insert( 0x000000007ffffffei64 );
    valCompSet.insert( 0x000000007fffffffi64 );
    valCompSet.insert( 0x0000000080000000i64 );
    valCompSet.insert( 0x0000000080000001i64 );
    valCompSet.insert( 0x00000000fffffffei64 );
    valCompSet.insert( 0x00000000ffffffffi64 );
    valCompSet.insert( 0x0000000100000000i64 );
    valCompSet.insert( 0x0000000100000001i64 );
    valCompSet.insert( 0x3ffffffffffffffei64 );
    valCompSet.insert( 0x3fffffffffffffffi64 );
    valCompSet.insert( 0x4000000000000000i64 );
    valCompSet.insert( 0x4000000000000001i64 );
    valCompSet.insert( 0x7ffffffffffffffei64 );
    valCompSet.insert( 0x7fffffffffffffffi64 );
    valCompSet.insert( 0x8000000000000000i64 );
    valCompSet.insert( 0x8000000000000001i64 );
    valCompSet.insert( 0x8000000000000002i64 );
    valCompSet.insert( 0x8000000000000003i64 );
    valCompSet.insert( 0x8000000000000004i64 );
    valCompSet.insert( 0x8000000000000005i64 );
    valCompSet.insert( 0x8000000000000006i64 );
    valCompSet.insert( 0x8000000000000007i64 );
    valCompSet.insert( 0x8000000000000008i64 );
    valCompSet.insert( 0x8000000000000009i64 );
    valCompSet.insert( 0x800000007ffffffei64 );
    valCompSet.insert( 0x800000007fffffffi64 );
    valCompSet.insert( 0x8000000080000000i64 );
    valCompSet.insert( 0x8000000080000001i64 );
    valCompSet.insert( 0x80000000fffffffei64 );
    valCompSet.insert( 0x80000000ffffffffi64 );
    valCompSet.insert( 0x8000000100000000i64 );
    valCompSet.insert( 0x8000000100000001i64 );
    valCompSet.insert( 0xa000000000000000i64 );
    valCompSet.insert( 0xbffffffffffffffei64 );
    valCompSet.insert( 0xbfffffffffffffffi64 );
    valCompSet.insert( 0xffffffffffffffffi64 );
    valCompSet.insert( 0xfffffffffffffffei64 );
    valCompSet.insert( 0xfffffff7fffffffei64 );
    valCompSet.insert( 0xffffffe7fffffffei64 );
    valCompSet.insert( 0xffffffd7fffffffei64 );
    valCompSet.insert( 0xffffffdcfffffffei64 );
    valCompSet.insert( LLONG_MAX );
    valCompSet.insert( LLONG_MIN );

    std::set<long long>::iterator x;
    std::set<long long>::iterator y;

    COUT << DEC << valCompSet.size() << " values in valCompSet set" << ENDL;
    for (x=valCompSet.begin(); x!=valCompSet.end(); x++)
    {
        for (y=valCompSet.begin(); y!=valCompSet.end(); y++)
        {         
            if(*y != 0)        
            {
                //COUT << DEC << *x << "   " << *y << ENDL;
                try { valSet.insert( RatSLLwCK( *x, *y )); } catch (boost::rational_overflow Exception) { bool ovfl = true; }
                try { valSet.insert( RatSLLwCK(-*x, *y )); } catch (boost::rational_overflow Exception) { bool ovfl = true; }
            }
        }
    }

    // Make sure specific values are in the test set.
    valSet.insert( RatSLLwCK((long long)         0, (long long)1) );
    valSet.insert( RatSLLwCK((long long)         1, (long long)1) );
    valSet.insert( RatSLLwCK((long long)         2, (long long)1) );
    valSet.insert( RatSLLwCK((long long)        -1, (long long)1) );
    valSet.insert( RatSLLwCK((long long)        -2, (long long)1) );
    valSet.insert( RatSLLwCK((long long) LLONG_MAX, (long long)1) );
    valSet.insert( RatSLLwCK((long long) LLONG_MAX-1, (long long)1) );
    valSet.insert( RatSLLwCK((long long)-LLONG_MAX,   (long long)1) );
    valSet.insert( RatSLLwCK((long long) LLONG_MIN,   (long long)1) );
    valSet.insert( RatSLLwCK((long long) LLONG_MIN+1, (long long)1) );
    valSet.insert( RatSLLwCK((long long)         1, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long)         3, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long)        -1, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long)        -3, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long)         1, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long)         3, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long)        -1, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long)        -3, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long) LLONG_MIN, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long) LLONG_MIN, (long long)LLONG_MAX>>32) );

    valSet.insert( RatSLLwCK((long long) 0x07f000000i64, (long long)1) );
    valSet.insert( RatSLLwCK((long long) 0x07fffffffi64, (long long)1) );
    valSet.insert( RatSLLwCK((long long) 0x080000000i64, (long long)1) );
    valSet.insert( RatSLLwCK((long long) 0x080000001i64, (long long)1) );
    valSet.insert( RatSLLwCK((long long) 0x0FFFFFFFFi64, (long long)1) );
    valSet.insert( RatSLLwCK((long long) 0x100000000i64, (long long)1) );
    valSet.insert( RatSLLwCK((long long) 0x100000001i64, (long long)1) );
    valSet.insert( RatSLLwCK((long long) 0x1ffffffffi64, (long long)1) );
    valSet.insert( RatSLLwCK((long long) 0x200000000i64, (long long)1) );

    valSet.insert( RatSLLwCK((long long) 0x07f000000i64, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long) 0x07fffffffi64, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long) 0x080000000i64, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long) 0x080000001i64, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long) 0x0FFFFFFFFi64, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long) 0x100000000i64, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long) 0x100000001i64, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long) 0x1ffffffffi64, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long) 0x200000000i64, (long long)LLONG_MAX) );

    valSet.insert( RatSLLwCK((long long) 0x07f000000i64, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long) 0x07fffffffi64, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long) 0x080000000i64, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long) 0x080000001i64, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long) 0x0FFFFFFFFi64, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long) 0x100000000i64, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long) 0x100000001i64, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long) 0x1ffffffffi64, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long) 0x200000000i64, (long long)LLONG_MAX>>32) );

    valSet.insert( RatSLLwCK((long long) 0x07f000000i64, (long long)LLONG_MAX>>33) );
    valSet.insert( RatSLLwCK((long long) 0x07fffffffi64, (long long)LLONG_MAX>>33) );
    valSet.insert( RatSLLwCK((long long) 0x080000000i64, (long long)LLONG_MAX>>33) );
    valSet.insert( RatSLLwCK((long long) 0x080000001i64, (long long)LLONG_MAX>>33) );
    valSet.insert( RatSLLwCK((long long) 0x0FFFFFFFFi64, (long long)LLONG_MAX>>33) );
    valSet.insert( RatSLLwCK((long long) 0x100000000i64, (long long)LLONG_MAX>>33) );
    valSet.insert( RatSLLwCK((long long) 0x100000001i64, (long long)LLONG_MAX>>33) );
    valSet.insert( RatSLLwCK((long long) 0x1ffffffffi64, (long long)LLONG_MAX>>33) );
    valSet.insert( RatSLLwCK((long long) 0x200000000i64, (long long)LLONG_MAX>>33) );

    valSet.insert( RatSLLwCK((long long) 0x07f000000i64, (long long)LLONG_MAX>>31) );
    valSet.insert( RatSLLwCK((long long) 0x07fffffffi64, (long long)LLONG_MAX>>31) );
    valSet.insert( RatSLLwCK((long long) 0x080000000i64, (long long)LLONG_MAX>>31) );
    valSet.insert( RatSLLwCK((long long) 0x080000001i64, (long long)LLONG_MAX>>31) );
    valSet.insert( RatSLLwCK((long long) 0x0FFFFFFFFi64, (long long)LLONG_MAX>>31) );
    valSet.insert( RatSLLwCK((long long) 0x100000000i64, (long long)LLONG_MAX>>31) );
    valSet.insert( RatSLLwCK((long long) 0x100000001i64, (long long)LLONG_MAX>>31) );
    valSet.insert( RatSLLwCK((long long) 0x1ffffffffi64, (long long)LLONG_MAX>>31) );
    valSet.insert( RatSLLwCK((long long) 0x200000000i64, (long long)LLONG_MAX>>31) );

    valSet.insert( RatSLLwCK((long long) 0x07f0000000010011i64, (long long)1) );
    valSet.insert( RatSLLwCK((long long) 0x07fffffff0010011i64, (long long)1) );
    valSet.insert( RatSLLwCK((long long) 0x0800000000010011i64, (long long)1) );
    valSet.insert( RatSLLwCK((long long) 0x0800000010010011i64, (long long)1) );
    valSet.insert( RatSLLwCK((long long) 0x0FFFFFFFF0010011i64, (long long)1) );
    valSet.insert( RatSLLwCK((long long) 0x1000000000010011i64, (long long)1) );
    valSet.insert( RatSLLwCK((long long) 0x100000001i64, (long long)1) );
    valSet.insert( RatSLLwCK((long long) 0x1ffffffffi64, (long long)1) );
    valSet.insert( RatSLLwCK((long long) 0x200000000i64, (long long)1) );

    valSet.insert( RatSLLwCK((long long) 0x07f000000i64, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long) 0x07fffffffi64, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long) 0x080000000i64, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long) 0x080000001i64, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long) 0x0FFFFFFFFi64, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long) 0x100000000i64, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long) 0x100000001i64, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long) 0x1ffffffffi64, (long long)LLONG_MAX) );
    valSet.insert( RatSLLwCK((long long) 0x200000000i64, (long long)LLONG_MAX) );

    valSet.insert( RatSLLwCK((long long) 0x07f000000i64, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long) 0x07fffffffi64, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long) 0x080000000i64, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long) 0x080000001i64, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long) 0x0FFFFFFFFi64, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long) 0x100000000i64, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long) 0x100000001i64, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long) 0x1ffffffffi64, (long long)LLONG_MAX>>32) );
    valSet.insert( RatSLLwCK((long long) 0x200000000i64, (long long)LLONG_MAX>>32) );

    valSet.insert( RatSLLwCK((long long) 0x07f000000i64, (long long)LLONG_MAX>>33) );
    valSet.insert( RatSLLwCK((long long) 0x07fffffffi64, (long long)LLONG_MAX>>33) );
    valSet.insert( RatSLLwCK((long long) 0x080000000i64, (long long)LLONG_MAX>>33) );
    valSet.insert( RatSLLwCK((long long) 0x080000001i64, (long long)LLONG_MAX>>33) );
    valSet.insert( RatSLLwCK((long long) 0x0FFFFFFFFi64, (long long)LLONG_MAX>>33) );
    valSet.insert( RatSLLwCK((long long) 0x100000000i64, (long long)LLONG_MAX>>33) );
    valSet.insert( RatSLLwCK((long long) 0x100000001i64, (long long)LLONG_MAX>>33) );
    valSet.insert( RatSLLwCK((long long) 0x1ffffffffi64, (long long)LLONG_MAX>>33) );
    valSet.insert( RatSLLwCK((long long) 0x200000000i64, (long long)LLONG_MAX>>33) );

    valSet.insert( RatSLLwCK((long long) 0x07f000000i64, (long long)LLONG_MAX>>31) );
    valSet.insert( RatSLLwCK((long long) 0x07fffffffi64, (long long)LLONG_MAX>>31) );
    valSet.insert( RatSLLwCK((long long) 0x080000000i64, (long long)LLONG_MAX>>31) );
    valSet.insert( RatSLLwCK((long long) 0x080000001i64, (long long)LLONG_MAX>>31) );
    valSet.insert( RatSLLwCK((long long) 0x0FFFFFFFFi64, (long long)LLONG_MAX>>31) );
    valSet.insert( RatSLLwCK((long long) 0x100000000i64, (long long)LLONG_MAX>>31) );
    valSet.insert( RatSLLwCK((long long) 0x100000001i64, (long long)LLONG_MAX>>31) );
    valSet.insert( RatSLLwCK((long long) 0x1ffffffffi64, (long long)LLONG_MAX>>31) );
    valSet.insert( RatSLLwCK((long long) 0x200000000i64, (long long)LLONG_MAX>>31) );

    RatSLLwCK ratVal;
    for (int p=0; p<16; p++)
    {       
        try {ratVal.assign( ((long long)1<<(p*4))-1, 1 ); valSet.insert( ratVal );           } catch (boost::rational_overflow Exception) { bool ovfl = true;}
        try {ratVal.assign( ((long long)1<<(p*4)),   1 ); valSet.insert( ratVal );           } catch (boost::rational_overflow Exception) { bool ovfl = true;}
        try {ratVal.assign( ((long long)1<<(p*4))+1, 1 ); valSet.insert( ratVal );           } catch (boost::rational_overflow Exception) { bool ovfl = true;}

        try {ratVal.assign(-((long long)1<<(p*4))-1, 1 ); valSet.insert( ratVal );           } catch (boost::rational_overflow Exception) { bool ovfl = true;}
        try {ratVal.assign(-((long long)1<<(p*4)),   1 ); valSet.insert( ratVal );           } catch (boost::rational_overflow Exception) { bool ovfl = true;}
        try {ratVal.assign(-((long long)1<<(p*4))+1, 1 ); valSet.insert( ratVal );           } catch (boost::rational_overflow Exception) { bool ovfl = true;}

        try {if(p){ratVal.assign(  1, ((long long)1<<(p*4))-1); valSet.insert( ratVal ); }   } catch (boost::rational_overflow Exception) { bool ovfl = true;}
        try {ratVal.assign(  1, ((long long)1<<(p*4))  ); valSet.insert( ratVal );           } catch (boost::rational_overflow Exception) { bool ovfl = true;}
        try {ratVal.assign(  1, ((long long)1<<(p*4))+1); valSet.insert( ratVal );           } catch (boost::rational_overflow Exception) { bool ovfl = true;}

        try {if(p){ratVal.assign( -1, ((long long)1<<(p*4))-1); valSet.insert( ratVal ); }   } catch (boost::rational_overflow Exception) { bool ovfl = true;}
        try {ratVal.assign( -1, ((long long)1<<(p*4))  ); valSet.insert( ratVal );           } catch (boost::rational_overflow Exception) { bool ovfl = true;}     
        try {ratVal.assign( -1, ((long long)1<<(p*4))+1); valSet.insert( ratVal );           } catch (boost::rational_overflow Exception) { bool ovfl = true;}             
    }

    FailCount += BinarySetTest<RatSLLwCK, RatInt128>(valSet);

    COUT << ENDL;
    if(FailCount) COUT << "Fail count " << DEC << FailCount << "  " << ENDL;
    else          COUT << "All Passed" << ENDL; 
    COUT << ENDL;

    return FailCount;
}
#endif

unsigned long long testSimpleAndQuick(void)
{
    unsigned long long FailCount(0);
    COUT << ENDL << "Starting Quick and Simple tests..." << ENDL;

    {  // Unary +
        RatS32ref ratVala(11*3,9*3), ratValb;
        ratValb = +ratVala;   VERIFY_RAT_VAL(ratValb,  11, 9);
        RatS32wCK ratValA(11*3,9*3), ratValB;
        ratValB = +ratValA;   VERIFY_RAT_VAL(ratValB,  11, 9);
    }
    {  // Unary -
        RatS32ref ratVala(11*3,9*3), ratValb;
        ratValb = -ratVala;   VERIFY_RAT_VAL(ratValb, -11, 9);
        RatS32wCK ratValA(11*3,9*3), ratValB;
        ratValB = -ratValA;   VERIFY_RAT_VAL(ratValB, -11, 9);
    }
    {  // Integer assignment
        RatS32ref ratVala(11*3,9*3);
        ratVala = 19;   VERIFY_RAT_VAL(ratVala,  19, 1);
        RatS32wCK ratValA(11*3,9*3);
        ratValA = 19;   VERIFY_RAT_VAL(ratValA,  19, 1);
    }
    {  // assign()
        RatS32ref ratVala(11*3,9*3);
        ratVala.assign(23,5);   VERIFY_RAT_VAL(ratVala,  23, 5);
        RatS32wCK ratValA(11*3,9*3);
        ratValA.assign(23,5);   VERIFY_RAT_VAL(ratValA,  23, 5);
    }
    {  // += 
        RatS32ref ratVala(11*3,9*3), ratValb(7*7,11*7);
        ratValb += ratVala;   VERIFY_RAT_VAL(ratValb,  184, 99);
        RatS32wCK ratValA(11*3,9*3), ratValB(7*7,11*7);
        ratValB += ratValA;   VERIFY_RAT_VAL(ratValB,  184, 99);
    }
    {  // -=
        RatS32ref ratVala(11*3,9*3), ratValb(7*7,11*7);
        ratValb -= ratVala;   VERIFY_RAT_VAL(ratValb,  -58, 99);
        RatS32wCK ratValA(11*3,9*3), ratValB(7*7,11*7);
        ratValB -= ratValA;   VERIFY_RAT_VAL(ratValB,  -58, 99);
    }
    {  // *=
        RatS32ref ratVala(11*3,9*3), ratValb(7*7,11*7);
        ratValb *= ratVala;   VERIFY_RAT_VAL(ratValb,  7, 9);
        RatS32wCK ratValA(11*3,9*3), ratValB(7*7,11*7);
        ratValB *= ratValA;   VERIFY_RAT_VAL(ratValB,  7, 9);
    }
    {  // /=
        RatS32ref ratVala(11*3,9*3), ratValb(7*7,11*7);
        ratValb /= ratVala;   VERIFY_RAT_VAL(ratValb,  63, 121);
        RatS32wCK ratValA(11*3,9*3), ratValB(7*7,11*7);
        ratValB /= ratValA;   VERIFY_RAT_VAL(ratValB,  63, 121);
    }
    {  // += (integer)
        RatS32ref ratVala(11*3,9*3);
        ratVala += 19;   VERIFY_RAT_VAL(ratVala,  182, 9);
        RatS32wCK ratValA(11*3,9*3);
        ratValA += 19;   VERIFY_RAT_VAL(ratValA,  182, 9);
    }
    {  // -= (integer)
        RatS32ref ratVala(11*3,9*3);
        ratVala -= 19;   VERIFY_RAT_VAL(ratVala,  -160, 9);
        RatS32wCK ratValA(11*3,9*3);
        ratValA -= 19;   VERIFY_RAT_VAL(ratValA,  -160, 9);
    }
    {  // *= (integer)
        RatS32ref ratVala(11*3,9*3);
        ratVala *= 19;   VERIFY_RAT_VAL(ratVala,  209, 9);
        RatS32wCK ratValA(11*3,9*3);
        ratValA *= 19;   VERIFY_RAT_VAL(ratValA,  209, 9);
    }
    {  // /= (integer)
        RatS32ref ratVala(11*3,9*3);
        ratVala /= 19;   VERIFY_RAT_VAL(ratVala,  11, 171);
        RatS32wCK ratValA(11*3,9*3);
        ratValA /= 19;   VERIFY_RAT_VAL(ratValA,  11, 171);
    }
    { // Unary minus, and abs()
        RatS32wCK ratValB(11*3,9*3), ratValC;       ratValC = -ratValB;         VERIFY_RAT_VAL(ratValC, -11, 9);
                                                    ratValC = abs(ratValC);     VERIFY_RAT_VAL(ratValC,  11, 9);
        RatS32ref ratVal0(5,19);                    ratVal0 = -ratVal0;         VERIFY_RAT_VAL(ratVal0, -5, 19);
                                                    ratVal0 = abs(ratVal0);     VERIFY_RAT_VAL(ratVal0,  5, 19);
    }
    { // Post increment/decrement
        RatS32wCK ratValA(11*3,9*3);
        ratValA++;   VERIFY_RAT_VAL(ratValA,  20, 9);
        ratValA--;   VERIFY_RAT_VAL(ratValA,  11, 9);
        RatS32ref ratVala(11*3,9*3);
        ratVala++;   VERIFY_RAT_VAL(ratVala,  20, 9);
        ratVala--;   VERIFY_RAT_VAL(ratVala,  11, 9);
    }
    { // Pre increment/decrement
        RatS32wCK ratValA(11*3,9*3);
        ++ratValA;   VERIFY_RAT_VAL(ratValA,  20, 9);
        --ratValA;   VERIFY_RAT_VAL(ratValA,  11, 9);
        RatS32ref ratVala(11*3,9*3);
        ++ratVala;   VERIFY_RAT_VAL(ratVala,  20, 9);
        --ratVala;   VERIFY_RAT_VAL(ratVala,  11, 9);
    }
    { // Conversion to bool
        RatS32ref ratVala(11*3,9*3), ratValb(0);
        if(ratVala){ }
        else { FailCount++; ReportFailure(__FILE__,__LINE__); }
        if(ratValb) { FailCount++; ReportFailure(__FILE__,__LINE__); }
        else { }

        RatS32wCK ratValA(11*3,9*3), ratValB(0);
        if(ratValA){ }
        else { FailCount++; ReportFailure(__FILE__,__LINE__); }
        if(ratValB) { FailCount++; ReportFailure(__FILE__,__LINE__); }
        else { }
    }
    { // '!' operator
        RatS32ref ratVala(11*3,9*3), ratValb(0);
        if(!ratVala){ FailCount++; ReportFailure(__FILE__,__LINE__); }
        else { }
        if(!ratValb) { }
        else { FailCount++; ReportFailure(__FILE__,__LINE__); }

        RatS32wCK ratValA(11*3,9*3), ratValB(0);
        if(!ratValA){ FailCount++; ReportFailure(__FILE__,__LINE__); }
        else { }
        if(!ratValB) { }
        else { FailCount++; ReportFailure(__FILE__,__LINE__); }
    }
    {  // '!='
        RatS32ref ratVala(11*3,9*3), ratValb=ratVala;
        if(ratValb != ratVala)
        {
            FailCount++; ReportFailure(__FILE__,__LINE__);
        }

        RatS32wCK ratValA(11*3,9*3), ratValB=ratValA;
        if(ratValB != ratValA)
        {
            FailCount++; ReportFailure(__FILE__,__LINE__);
        }
    }
    {  // '<'
        RatS32ref ratVala(11*3,9*3), ratValb(12*3,9*3);
        if(ratValb < ratVala)
        {
            FailCount++; ReportFailure(__FILE__,__LINE__);
        }

        RatS32wCK ratValA(11*3,9*3), ratValB(12*3,9*3);
        if(ratValB < ratValA)
        {
            FailCount++; ReportFailure(__FILE__,__LINE__);
        }
    }
    { // '<' (integer)
        RatS32ref ratVala(5,2);
        if(ratVala < 2)
        {
            FailCount++; ReportFailure(__FILE__,__LINE__);
        }

        RatS32wCK ratValA(5,2);
        if(ratValA < 2)
        {
            FailCount++; ReportFailure(__FILE__,__LINE__);
        }
    }
    {  // '>' (integer)
        RatS32ref ratVala(5,2);
        if(ratVala > 3)
        {
            FailCount++; ReportFailure(__FILE__,__LINE__);
        }

        RatS32wCK ratValA(5,2);
        if(ratValA > 3)
        {
            FailCount++; ReportFailure(__FILE__,__LINE__);
        }
    }
    {  // '==' (integer)
        RatS32ref ratVala(6,1);
        if(ratVala == 6)
        {}
        else
        {
            FailCount++; ReportFailure(__FILE__,__LINE__);
        }

        RatS32wCK ratValA(6,1);
        if(ratValA == 6)
        {}
        else
        {
            FailCount++; ReportFailure(__FILE__,__LINE__);
        }
    }

    // Rely on 32 bit ints:
    if(((INT_MAX) == 2147483647) && ((INT_MIN) == (-2147483647 - 1)))
    {
        RatS32ref ratVal_1(-2147483647 - 1,-1); // Non-overflow checked overflows.
        
        SHOULD_OVERFLOW_EXCEPTION( RatS32wCK ratValD(-2147483647 - 1,-1) );
        SHOULD_NOT_EXCEPTION( RatS32wCK ratValD(-2147483647 - 1, 1) );

        SHOULD_NOT_EXCEPTION( RatS32wCK ratValE(-2147483647 - 1,1) ); 
        SHOULD_OVERFLOW_EXCEPTION( RatS32wCK ratValE(-2147483647 - 1,1); RatS32wCK ratValD = -ratValE );
        SHOULD_NOT_EXCEPTION( RatS32wCK ratValE(-2147483647 - 1,1); RatS32wCK ratValF = +ratValE );  // Unary '+'

        SHOULD_ZERO_DIVIDE_EXCEPTION(     RatS32wCK ratValA(57,13); RatS32wCK ratValZ(0); RatS32wCK ratValB = ratValA/ratValZ ); // Divide by zero

        SHOULD_OVERFLOW_EXCEPTION( RatS32wCK ratValA(2147483647,1); ratValA++ );
        SHOULD_OVERFLOW_EXCEPTION( RatS32wCK ratValA(-2147483647 - 1,1); ratValA-- );
        SHOULD_OVERFLOW_EXCEPTION( RatS32wCK ratValA(-2147483647 - 1,1); abs(ratValA) );
    }

    {  // Type conversion template
        RatS32ref A(19,4);
        double fA = boost::rational_cast<double>(A);
        RatS32wCK B(19,4);
        double fB = boost::rational_cast<double>(B);
        COUT << fA << "  " << fB << ENDL;
    }

    COUT << ENDL;
    if(FailCount) COUT << "Fail count " << DEC << FailCount << "  " << ENDL;
    else          COUT << "All Passed" << ENDL; 
    COUT << ENDL;

    return FailCount;
}

int main(int argc, char* argv[])
{
    unsigned long long FailCount(0);

    if(1) FailCount += testRationalConstruction();

    if(1) FailCount += testSimpleAndQuick();
   
    if(1) FailCount += testS8rationalsQuick();

    if(1) FailCount += testRationalS16Quick();


    if(1) FailCount += testS8rationals();

    if(1) FailCount += testRationalS8IncDec();

    if(1) FailCount += testRationalS16selected();

    if(1) FailCount += testRationalS32selected();

#if TEST_LL_RATIONAL
    if(1) FailCount += testRationalS64selected();
#endif

    COUT << ENDL;
    COUT << ENDL;

    COUT << "Over ALL Fail count: " << DEC << FailCount << ENDL;

    return 0;
}

