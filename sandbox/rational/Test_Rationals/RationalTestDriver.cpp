#include <iostream>
#include <iomanip>

//#define BOOST_DISABLE_WIN32
//#include "boost/test/unit_test.hpp"
//#include "boost/test/included/unit_test.hpp"

#include <set>
#include "../../rational.hpp"   // The new one to test

#define TEST_LL_RATIONAL  1  // Need an 128bit int to test long long rational
#if TEST_LL_RATIONAL
#include "int128.hpp"
#endif


typedef boost::rational<signed char,boost::RationalCheckforOverflow>   RatS8wCK;
typedef boost::rational<signed char,boost::RationalNoChecking>         RatS8ref;

typedef boost::rational<short,boost::RationalCheckforOverflow>         RatS16wCK;
typedef boost::rational<short,boost::RationalNoChecking>               RatRefS16;

typedef boost::rational<int,boost::RationalCheckforOverflow>           RatS32wCK;
typedef boost::rational<int,boost::RationalNoChecking>                 RatS32ref;

typedef boost::rational<long long,boost::RationalCheckforOverflow>     RatSLLwCK;
typedef boost::rational<long long,boost::RationalNoChecking>           RatSLLref;

typedef boost::rational<unsigned int,boost::RationalCheckforOverflow>  RatU32wCK;
typedef boost::rational<unsigned int,boost::RationalNoChecking>        RatU32ref;


// std:: namespace helpers
#define STD std::
#define COUT std::cout
#define ENDL std::endl
#define DEC std::dec
#define HEX std::hex
//#define STD
//#define COUT cout
//#define ENDL endl

void ReportFailure(char* filename, int lineNumber)
{
    COUT << ENDL << "Fail reported at " << DEC << lineNumber << " of " << filename << ENDL;
    throw 57;  // Cause any failure to terminate program!!!
}




void testRationalConstruction(void)
{
    unsigned long long FailCount(0);
    if(1 && (-SCHAR_MAX != SCHAR_MIN)) // Test overflow on construction of max neg denominator
    {
        bool failed;
        signed char      denChar  = SCHAR_MIN;
        signed short     denShort = SHRT_MIN;
        signed int       denInt = INT_MIN;
        signed long long denLL = LLONG_MIN;

        // ----------------------------------------------------------
        try {failed = true; RatS8wCK RA(1, denChar); }
        catch (boost::rational_overflow Exception) {failed = false;}
        if(failed) {
            FailCount++;
            ReportFailure(__FILE__,__LINE__);
        }

        try {failed = false;  RatS8wCK RA(1, denChar+1); }
        catch (boost::rational_overflow Exception) {failed = true;}
        if(failed) {
            FailCount++;
            ReportFailure(__FILE__,__LINE__);
        }

        // ----------------------------------------------------------
        try {failed = true; RatS16wCK RA(1, denShort); }
        catch (boost::rational_overflow Exception) {failed = false;}
        if(failed) {
            FailCount++;
            ReportFailure(__FILE__,__LINE__);
        }

        try {failed = false;  RatS16wCK RA(1, denShort+1); }
        catch (boost::rational_overflow Exception) {failed = true;}
        if(failed) {
            FailCount++;
            ReportFailure(__FILE__,__LINE__);
        }


        // ----------------------------------------------------------
        try {failed = true; RatS32wCK RA(1, denInt); }
        catch (boost::rational_overflow Exception) {failed = false;}
        if(failed) {
            FailCount++;
            ReportFailure(__FILE__,__LINE__);
        }

        try {failed = false;  RatS32wCK RA(1, denInt+1); }
        catch (boost::rational_overflow Exception) {failed = true;}
        if(failed) {
            FailCount++;
            ReportFailure(__FILE__,__LINE__);
        }

        // ----------------------------------------------------------
        try {failed = true; RatSLLwCK RA(1, denLL); }
        catch (boost::rational_overflow Exception) {failed = false;}
        if(failed) {
            FailCount++;
            ReportFailure(__FILE__,__LINE__);
        }

        try {failed = false;  RatSLLwCK RA(1, denLL+1); }
        catch (boost::rational_overflow Exception) {failed = true;}
        if(failed) {
            FailCount++;
            ReportFailure(__FILE__,__LINE__);
        }
    }
    else
    {
        COUT << "Test skipped." << ENDL;
    }
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
long long BinarySetTest(std::set<RatT>& valSet)
{
    long long FailureCount = 0;
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


void testS8rationals()
{
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

    BinarySetTest<RatS8true,RatRefS16>(valSet);

    COUT << ENDL;
}   // 19895 for typical signed 8 bit numbers         


void testRationalS8IncDec(void)
{
    unsigned long long FailCount(0);
    COUT << ENDL << "Starting 8 bit rational increment/decrement tests" << ENDL; 
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
    COUT << "Fail count " << DEC << FailCount << "  ";
    COUT << ENDL;
}


void testRationalS16selected(void) 
{
    unsigned long long FailCount(0);
    COUT << ENDL << "Starting 16 bit selected values rational operator tests" << ENDL; 

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

    COUT << "Fail count " << DEC << FailCount << "  ";
    COUT << ENDL;
}

void testRationalS32selected(void)
{
    unsigned long long FailCount(0);
    COUT << ENDL << "Starting 32 bit selected values rational operator tests" << ENDL; 
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

    COUT << "Fail count " << DEC << FailCount << "  ";
    COUT << ENDL;
}

void testRationalS64selected(void)  // Uses 128 bit reference 'int'
{
    unsigned long long FailCount(0);
    COUT << ENDL << "Starting 64 bit selected values rational operator tests" << ENDL; 
    typedef boost::rational<Int128,boost::RationalNoChecking>    RatInt128;
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
                COUT << DEC << *x << "   " << *y << ENDL;
                try { valSet.insert( RatSLLwCK( *x, *y )); } catch (boost::rational_overflow Exception) { bool ovfl = true; }
                try { valSet.insert( RatSLLwCK(-*x, *y )); } catch (boost::rational_overflow Exception) { bool ovfl = true; }
            }
        }
    }

#if 1
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

    //==
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
#endif

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

    COUT << "Fail count " << DEC << FailCount << "  ";
    COUT << ENDL;
}


int main(int argc, char* argv[])
{
   
    if(1) testRationalConstruction();

    if(0) testS8rationals();

    if(0) testRationalS8IncDec();

    if(0) testRationalS16selected();

    if(0) testRationalS32selected();

#if TEST_LL_RATIONAL
    if(1) testRationalS64selected();
#endif

    COUT << ENDL;

    return 0;
}

