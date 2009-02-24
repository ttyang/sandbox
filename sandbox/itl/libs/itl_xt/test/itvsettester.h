/*-----------------------------------------------------------------------------+    
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
+-----------------------------------------------------------------------------*/

/* ------------------------------------------------------------------
class ItvSetTesterT
--------------------------------------------------------------------*/
#ifndef __ITVSETTESTER_H_JOFA_990230__
#define __ITVSETTESTER_H_JOFA_990230__

#include <boost/itl_xt/setgentor.hpp>

namespace boost{namespace itl
{

template <class ItvSetTV>
class ItvSetTesterT
{
public:
    typedef typename ItvSetTV::value_type  value_type;
    typedef typename ItvSetTV::domain_type domain_type;
    typedef ItvGentorT<domain_type>        domain_generator_type;

    void set_domain_generator(domain_generator_type* gentor)
    { m_ContainerGentor.setDomainGentor(gentor); }

    //void setDomainRange(domain_type lwb, domain_type upb, domain_type itvLen) 
    //{ m_DomainGentor.setValueRange(lwb,upb); m_DomainGentor.setMaxIntervalLength(itvLen); }

    void setRangeOfSampleSize(int lwb, int upb)
    { m_ContainerGentor.setRangeOfSampleSize(lwb,upb); }

    //void init() { 
    //    m_ContainerGentor.setDomainGentor(&m_DomainGentor);
    //}

    // The value of a Set is independent of the insertion sequence
    bool valueIsInsertionIndependent(ItvSetTV& y, ItvSetTV& y_perm);
    bool testInsertionIndependence(int nTries);

    // The value of a Map is invariant wrt. join-normalization
    bool valueIsJoinIndependent(ItvSetTV& y, ItvSetTV& y_join);
    bool testJoinIndependence(int nTries);

    // The value of a Map is invariant wrt. join-normalization after insert-permutation
    bool valueIsInsertAndJoinIndependent(ItvSetTV& y, ItvSetTV& y_perm, ItvSetTV& y_permJoin);
    bool testInsertAndJoinIndependence(int nTries);

    // x + y - join(perm(y)) == x - y;
    bool isInsertReversible
        (ItvSetTV& x, ItvSetTV& y, ItvSetTV& y_perm, ItvSetTV& y_permJoin, 
        ItvSetTV& x_plus_y, ItvSetTV& lhs, ItvSetTV& rhs); 
    bool testInsertReversibility(int nTries, char* errFile);

    // x + y - join(perm(y)) == x;
    bool isInsertReversible1
        (ItvSetTV& x, ItvSetTV& y, ItvSetTV& y_perm, ItvSetTV& y_permJoin, 
        ItvSetTV& x_plus_y, ItvSetTV& x2); 
    bool testInsertReversibility1(int nTries, char* errFile);
    
    void debugInsertReversibility1(const ItvSetTV& x, const ItvSetTV& y, const ItvSetTV y_perm);

    /*
    // x + join(perm(y)) - y == x;
    bool isInsertReversible2
        (ItvSetTV& x, ItvSetTV& y, ItvSetTV& y_perm, ItvSetTV& y_permJoin, 
         ItvSetTV& x_plus_y_pj, ItvSetTV& x2); 
    bool testInsertReversibility2(int nTries, char* errFile);

    void debugInsertReversibility2(const ItvSetTV& x, const ItvSetTV& y, const ItvSetTV y_perm);
    */

    bool hasSymmetricDifference
        ( ItvSetTV& x, ItvSetTV& y, 
          ItvSetTV& x_uni_y, ItvSetTV& x_sec_y, 
          ItvSetTV& x_sub_y, ItvSetTV& y_sub_x );

    bool testSymmetricDifference(int nTries, char* errFile);


private:
    ItvGentorT<domain_type>        m_DomainGentor;
    SetGentorT<ItvSetTV>        m_ContainerGentor;

};


// ----------------------------------------------------------------------------
// LAW: InsertionIndependency<ItvSetTV>
// LAW: x == perm(x)

template <class ItvSetTV>
bool ItvSetTesterT<ItvSetTV>::valueIsInsertionIndependent(ItvSetTV& y, ItvSetTV& y_perm)
{
    ItvSetTV x, x_perm;
    m_ContainerGentor.some(x);
    m_ContainerGentor.last_permuted(x_perm);

    if(!(x == x_perm) ) {
        y = x; y_perm = x_perm;
        return false;
    } 
    else return true;
}



template <class ItvSetTV>
bool ItvSetTesterT<ItvSetTV>::testInsertionIndependence(int nTries)
{
    bool correct=true;
    ItvSetTV y, y_perm;
    ItvSetTV min_y, min_y_perm;

    for(int i=0; i<nTries; i++)
        if(!valueIsInsertionIndependent(y, y_perm))
        {
            if(true==correct) { min_y = y; min_y_perm = y_perm; correct=false; }
            else if( y.interval_count() < min_y.interval_count() ) {
                min_y = y; min_y_perm = y_perm;
            }
        }

    if(!correct) {
        std::cout << "InsertionIndependence violated" << std::endl;
    }

    return correct;
}


// ----------------------------------------------------------------------------
// LAW: JoinIndependency<ItvSetTV>
// LAW: x == join(x)

template <class ItvSetTV>
bool ItvSetTesterT<ItvSetTV>::valueIsJoinIndependent(ItvSetTV& y, ItvSetTV& y_join)
{
    ItvSetTV x, x_perm, x_join;
    m_ContainerGentor.some(x);
    x_join = x;
    x_join.join();
    
    if(!(x == x_join) ) { y = x; y_join = x_join; return false; } 
    else return true;
}



template <class ItvSetTV>
bool ItvSetTesterT<ItvSetTV>::testJoinIndependence(int nTries)
{
    bool correct=true;
    ItvSetTV y, y_join;
    ItvSetTV min_y, min_y_join;

    for(int i=0; i<nTries; i++)
        if(!valueIsJoinIndependent(y, y_join))
        {
            if(true==correct) { 
                min_y = y; min_y_join = y_join;
                correct=false;
                std::cout << "y.sz=" << static_cast<unsigned int>(y.interval_count()) << "  try=" << i << std::endl;
            }
            else if( y.interval_count() < min_y.interval_count() ) {
                min_y = y; min_y_join = y_join;
                std::cout << "y.sz=" << static_cast<unsigned int>(y.interval_count()) << "  try=" << i << std::endl;
            }
        }

    if(!correct) {
        std::cout << "JoinIndependence violated ---------------------------" << std::endl;
        std::cout << "y     :" << min_y.as_string().c_str() << std::endl;
        std::cout << "y_join:" << min_y_join.as_string().c_str() << std::endl;
    }

    return correct;
}

// ----------------------------------------------------------------------------
// LAW: InsertAndJoinIndependency<IntSetTV>
// LAW: x == join(perm(x))
template <class ItvSetTV>
bool ItvSetTesterT<ItvSetTV>::valueIsInsertAndJoinIndependent(ItvSetTV& y, ItvSetTV& y_perm, ItvSetTV& y_permJoin)
{
    ItvSetTV x, x_perm, x_permJoin;
    m_ContainerGentor.some(x);
    m_ContainerGentor.last_permuted(x_perm);
    x_permJoin = x_perm;
    x_permJoin.join();
    
    if(! x.isEqual(x_permJoin) ) {
        y = x; y_perm = x_perm; y_permJoin = x_permJoin;
        return false;
    } 
    else return true;
}



template <class ItvSetTV>
bool ItvSetTesterT<ItvSetTV>::testInsertAndJoinIndependence(int nTries)
{
    bool correct=true;
    ItvSetTV y, y_perm, y_permJoin;
    ItvSetTV min_y, min_y_perm, min_y_permJoin;

    for(int i=0; i<nTries; i++) 
    {
        if(!valueIsInsertAndJoinIndependent(y, y_perm, y_permJoin))
        {
            if(true==correct) { 
                min_y = y; min_y_perm = y_perm; min_y_permJoin = y_permJoin;
                correct=false;
                std::cout << "y.sz=" << y.interval_count() << "  try=" << i << std::endl;
            }
            else if( y.interval_count() < min_y.interval_count() ) {
                min_y = y; min_y_perm = y_perm; min_y_permJoin = y_permJoin;
                std::cout << "y.sz=" << y.interval_count() << "  try=" << i << std::endl;
            }
        }
    }

    if(!correct) {
        std::cout << "InsertAndJoinIndependence violated ---------------------------" << std::endl;
        std::cout << "y      :" << min_y.as_string().c_str() << std::endl;
        std::cout << "y_perm :" << min_y_perm.as_string().c_str() << std::endl;
        std::cout << "y_pjoin:" << min_y_permJoin.as_string().c_str() << std::endl;
    }

    return correct;
}




// ----------------------------------------------------------------------------
// LAW: InsertReversability<ItvSetTV>
// LAW: x + y - perm(join(y)) = x - y
template <class ItvSetTV>
bool ItvSetTesterT<ItvSetTV>::isInsertReversible
(
    ItvSetTV& x, ItvSetTV& y, 
    ItvSetTV& y_perm, ItvSetTV& y_permJoin, 
    ItvSetTV& x_plus_y, ItvSetTV& ls, ItvSetTV& rs
)
{    
    ItvSetTV xx, yy, yy_perm, yy_permJoin, xx_plus_yy, lhs, rhs;

    m_ContainerGentor.some(xx);
    m_ContainerGentor.some(yy);
    m_ContainerGentor.last_permuted(yy_perm);
    yy_permJoin = yy_perm;
    yy_permJoin.join();

    lhs = xx;
    lhs += yy;
    xx_plus_yy = lhs;
    lhs -= yy_permJoin; // left hand side
    
    rhs = xx;
    rhs -= yy; // right hand side
    
    if( !(lhs == rhs) ) {
        x = xx; y = yy; y_perm = yy_perm; y_permJoin = yy_permJoin;
        x_plus_y = xx_plus_yy; ls = lhs ; rs = rhs;
        return false;
    } 
    else return true;
}    


template <class ItvSetTV>
bool ItvSetTesterT<ItvSetTV>::testInsertReversibility(int nTries, char* errFile)
{
    bool correct=true;
    ItvSetTV x, y, y_perm, y_permJoin, x_plus_y, lhs, rhs;
    ItvSetTV min_x, min_y, min_y_perm, min_y_permJoin, min_x_plus_y, min_lhs, min_rhs;
    int caseSize, min_caseSize;

    for(int i=0; i<nTries; i++) 
    {
        if(!isInsertReversible(x, y, y_perm, y_permJoin, x_plus_y, lhs, rhs))
        {
            caseSize = static_cast<unsigned int>(x.interval_count() + y.interval_count());
            if(true==correct) { 
                min_x = x; min_y = y; min_y_perm = y_perm; 
                min_y_permJoin = y_permJoin; min_x_plus_y = x_plus_y; 
                min_lhs = lhs; min_rhs = rhs;
                min_caseSize = caseSize;
                std::cout << "x.sz="  << static_cast<unsigned int>(x.interval_count()) 
                     << " y.sz=" << static_cast<unsigned int>(y.interval_count()) 
                     << "  try=" << i << std::endl;
                correct=false;
            }
            else if ( caseSize < min_caseSize )
            {
                min_x = x; min_y = y; min_y_perm = y_perm;
                min_y_permJoin = y_permJoin; min_x_plus_y = x_plus_y;
                min_lhs = lhs; min_rhs = rhs;
                min_caseSize = caseSize;
                std::cout << "x.sz="  << static_cast<unsigned int>(x.interval_count()) 
                     << " y.sz=" << static_cast<unsigned int>(y.interval_count()) 
                     << "  try=" << i << std::endl;
            }
        }
    }

    if(!correct) {
        std::cout << "InsertReversibility: x + y - join(perm(y)) == x - y  violated --------" << std::endl;
        std::cout << "x       :" << min_x.as_string().c_str() << std::endl;
        std::cout << "y       :" << min_y.as_string().c_str() << std::endl;
        std::cout << "y_perm  :" << min_y_perm.as_string().c_str() << std::endl;
        std::cout << "y_pJnt  :" << min_y_permJoin.as_string().c_str() << std::endl;
        std::cout << "x+y     :" << min_x_plus_y.as_string().c_str() << std::endl;
        std::cout << "lhs     :" << min_lhs.as_string().c_str() << std::endl;
        std::cout << "rhs     :" << min_rhs.as_string().c_str() << std::endl;
        
        FILE* fp;
        fp = fopen(errFile,"w");
        //fopen_s(&fp,errFile,"w");
        fprintf(fp, "x: %s\n",      min_x.as_string().c_str());
        fprintf(fp, "y: %s\n",      min_y.as_string().c_str());
        fprintf(fp, "y_perm: %s\n", min_y_perm.as_string().c_str());
        fprintf(fp, "y_pJnt: %s\n", min_y_permJoin.as_string().c_str());
        fprintf(fp, "x+y: %s\n",    min_x_plus_y.as_string().c_str());
        fprintf(fp, "lhs: %s\n",    min_lhs.as_string().c_str());
        fprintf(fp, "rhs: %s\n",    min_rhs.as_string().c_str());
        
        // min_lhs.isEqual(min_rhs);
        // debugInsertReversibility1(min_x, min_y, min_y_perm);
    }
    else
    {
        std::cout << "InsertReversibility("<<nTries<<") OK " 
             << " x + y - join(perm(y)) == x - y" << std::endl;
    }

    return correct;
}




// ----------------------------------------------------------------------------
// Modify testconditions.     x + y - perm(join(y)) != x  !!
//                    only    y - perm(join(y)) = {} can be tested

// LAW: InsertReversability<ItvSetTV>
// LAW: y - perm(join(y)) = {}
template <class ItvSetTV>
bool ItvSetTesterT<ItvSetTV>::isInsertReversible1
(
    ItvSetTV& x, ItvSetTV& y, 
    ItvSetTV& y_perm, ItvSetTV& y_permJoin, 
    ItvSetTV& x_plus_y, ItvSetTV& x2
)
{
    // x + y - join(perm(y)) == x;
    
    ItvSetTV xx, yy, yy_perm, yy_permJoin, xx_plus_yy, xx2;

    m_ContainerGentor.some(xx);
    m_ContainerGentor.some(yy);
    m_ContainerGentor.last_permuted(yy_perm);
    yy_permJoin = yy_perm;
    yy_permJoin.join();

    xx2 = xx;
    xx2 += yy;
    xx_plus_yy = xx2;
    xx2 -= yy_permJoin;
    
    if(! xx.isEqual(xx2) ) {
        x = xx; y = yy; y_perm = yy_perm; y_permJoin = yy_permJoin;
        x_plus_y = xx_plus_yy; x2 = xx2 ;
        return false;
    } 
    else return true;
}    


template <class ItvSetTV>
bool ItvSetTesterT<ItvSetTV>::testInsertReversibility1(int nTries, char* errFile)
{
    // x + join(perm(y)) - y == x;

    bool correct=true;
    ItvSetTV x, y, y_perm, y_permJoin, x_plus_y, x2;
    ItvSetTV min_x, min_y, min_y_perm, min_y_permJoin, min_x_plus_y, min_x2;
    int caseSize, min_caseSize;

    for(int i=0; i<nTries; i++) 
    {
        if(!isInsertReversible1(x, y, y_perm, y_permJoin, x_plus_y, x2))
        {
            caseSize = x.interval_count() + y.interval_count();
            if(true==correct) { 
                min_x = x; min_y = y; min_y_perm = y_perm; 
                min_y_permJoin = y_permJoin; min_x_plus_y = x_plus_y; min_x2 = x2;
                min_caseSize = caseSize;
                std::cout << "x.sz=" << x.interval_count() << " y.sz=" << y.interval_count() 
                     << "  try=" << i << std::endl;
                correct=false;
            }
            else if ( caseSize < min_caseSize )
            {
                min_x = x; min_y = y; min_y_perm = y_perm;
                min_y_permJoin = y_permJoin; min_x_plus_y = x_plus_y; min_x2 = x2;
                min_caseSize = caseSize;
                std::cout << "x.sz=" << x.interval_count() << " y.sz=" << y.interval_count() 
                     << "  try=" << i << std::endl;
            }
        }
    }

    if(!correct) {
        std::cout << "InsertReversibility1: x + y - join(perm(y)) == x =: x2  violated --------" << std::endl;
        std::cout << "x       :" << min_x.as_string().c_str() << std::endl;
        std::cout << "y       :" << min_y.as_string().c_str() << std::endl;
        std::cout << "y_perm  :" << min_y_perm.as_string().c_str() << std::endl;
        std::cout << "y_pJnt  :" << min_y_permJoin.as_string().c_str() << std::endl;
        std::cout << "x+y     :" << min_x_plus_y.as_string().c_str() << std::endl;
        std::cout << "x2      :" << min_x2.as_string().c_str() << std::endl;

        FILE* fp;
        fp = fopen(errFile,"w");
        fprintf(fp, "x: %s\n",      min_x.as_string().c_str());
        fprintf(fp, "y: %s\n",      min_y.as_string().c_str());
        fprintf(fp, "y_perm: %s\n", min_y_perm.as_string().c_str());
        fprintf(fp, "y_pJnt: %s\n", min_y_permJoin.as_string().c_str());
        fprintf(fp, "x+y: %s\n",    min_x_plus_y.as_string().c_str());
        fprintf(fp, "x2: %s\n",     min_x2.as_string().c_str());

        min_x.isEqual(min_x2);
        debugInsertReversibility1(min_x, min_y, min_y_perm);
    }
    else
    {
        std::cout << "InsertReversibility1("<<nTries<<") OK " 
             << " x + y - join(perm(y)) == x =: x2" << std::endl;
    }

    return correct;
}


template <class ItvSetTV>
void ItvSetTesterT<ItvSetTV>::debugInsertReversibility1
    (const ItvSetTV& x, const ItvSetTV& y, const ItvSetTV y_perm)
{
    ItvSetTV x2 = x, y_pj = y_perm;
    y_pj.join();

    x2 += y_pj;
    x2 -= y;
}




// ------------------------------------------------------------------------------
// Test symmetric difference:

// LAW: SymmetricDifference<IntSetTV>
// LAW: (x + y) - (x * y) == (x - y) + (y - x)

template <class ItvSetTV>
bool ItvSetTesterT<ItvSetTV>::hasSymmetricDifference
(
    ItvSetTV& x, ItvSetTV& y, 
    ItvSetTV& x_uni_y, ItvSetTV& x_sec_y, 
    ItvSetTV& x_sub_y, ItvSetTV& y_sub_x
)
{
    // (x + y) - (x * y) == (x - y) + (y - x)
    
    ItvSetTV xx, yy, xx_uni_yy, xx_sec_yy, xx_sub_yy, yy_sub_xx, lhs, rhs;

    m_ContainerGentor.some(xx);
    m_ContainerGentor.some(yy);

    // lefthand side -------------------
    xx_uni_yy = xx;
    xx_uni_yy += yy;

    xx_sec_yy = xx;
    xx_sec_yy &= yy;

    lhs = xx_uni_yy;
    lhs -= xx_sec_yy;

    // right hand side -----------------
    xx_sub_yy = xx;
    xx_sub_yy -= yy;

    yy_sub_xx = yy;
    yy_sub_xx -= xx;

    rhs = xx_sub_yy;
    rhs += yy_sub_xx;
    // ---------------------------------

    if(! (lhs==rhs) ) {
        x = xx; y = yy; x_uni_y = xx_uni_yy; x_sec_y = xx_sec_yy;
        x_sub_y = xx_sub_yy; y_sub_x = yy_sub_xx ;
        return false;
    } 
    else return true;
}    


template <class ItvSetTV>
bool ItvSetTesterT<ItvSetTV>::testSymmetricDifference(int nTries, char* errFile)
{
    // (x + y) - (x * y) == (x - y) + (y - x)

    bool correct=true;
    ItvSetTV x, y, x_uni_y, x_sec_y, x_sub_y, y_sub_x;
    ItvSetTV min_x, min_y, min_x_uni_y, min_x_sec_y, min_x_sub_y, min_y_sub_x;

    int caseSize, min_caseSize;

    for(int i=0; i<nTries; i++) 
    {
        if(!hasSymmetricDifference(x, y, x_uni_y, x_sec_y, x_sub_y, y_sub_x))
        {
            // collect results to find the smallest invalid case
            caseSize = static_cast<unsigned int>(x.interval_count() + y.interval_count());
            if(true==correct) { 
                min_x = x; min_y = y; 
                /*
                more results
                */
                min_caseSize = caseSize;
                std::cout << "x.sz="  << static_cast<unsigned int>(x.interval_count()) 
                     << " y.sz=" << static_cast<unsigned int>(y.interval_count()) 
                     << "  try=" << i << std::endl;
                correct=false;
            }
            else if ( caseSize < min_caseSize )
            {
                min_x = x; min_y = y;
                /*
                more results
                */
                min_caseSize = caseSize;
                std::cout << "x.sz="  << static_cast<unsigned int>(x.interval_count()) 
                     << " y.sz=" << static_cast<unsigned int>(y.interval_count()) 
                     << "  try=" << i << std::endl;
            }
        }
    }

    if(!correct) {
        std::cout << "SymmetricDifference: (x + y) - (x * y) == (x - y) + (y - x)  violated --------" << std::endl;
        std::cout << "x       :" << min_x.as_string().c_str() << std::endl;
        std::cout << "y       :" << min_y.as_string().c_str() << std::endl;
        /*
        std::cout << "y_perm  :" << min_y_perm.as_string().c_str() << std::endl;
        std::cout << "y_pJnt  :" << min_y_permJoin.as_string().c_str() << std::endl;
        std::cout << "x+y     :" << min_x_plus_y.as_string().c_str() << std::endl;
        std::cout << "x2      :" << min_x2.as_string().c_str() << std::endl;
        */

        FILE* fp;
        fp = fopen(errFile,"w");
        //fopen_s(&fp,errFile,"w");
        fprintf(fp, "x: %s\n",      min_x.as_string().c_str());
        fprintf(fp, "y: %s\n",      min_y.as_string().c_str());
        /*
        fprintf(fp, "y_perm: %s\n", min_y_perm.as_string().c_str());
        fprintf(fp, "y_pJnt: %s\n", min_y_permJoin.as_string().c_str());
        fprintf(fp, "x+y: %s\n",    min_x_plus_y.as_string().c_str());
        fprintf(fp, "x2: %s\n",     min_x2.as_string().c_str());

        min_x.isEqual(min_x2);
        debugInsertReversibility1(min_x, min_y, min_y_perm);
        */
    }
    else
    {
        std::cout << "SymmetricDifference("<<nTries<<") OK " 
             << "  (x + y) - (x * y) == (x - y) + (y - x)" << std::endl;
    }

    return correct;
}

}} // namespace itl boost

#endif


