/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ITL_ELEMENT_COMPARER_HPP_JOFA_090202
#define BOOST_ITL_ELEMENT_COMPARER_HPP_JOFA_090202

#include <boost/itl/type_traits/is_map.hpp>
#include <boost/itl/detail/notate.hpp>
#include <boost/itl/type_traits/neutron.hpp>
#include <boost/itl/interval.hpp>

namespace boost{namespace itl
{

namespace Interval_Set
{

template<class LeftT, class RightT>
class element_comparer
{
public:
    typedef typename LeftT::const_iterator  LeftIterT;
    typedef typename RightT::const_iterator RightIterT;

    element_comparer(const LeftT&      left,
                     const RightT&     right,
                     const LeftIterT&  left_end,
                     const RightIterT& right_end)
        : _left(left), _right(right),
          _left_end(left_end), _right_end(right_end), 
          _compare_codomain(false), _result(equal)
    {}

    enum{nextboth, nextleft, nextright, stop};

    enum
    {
        less    = comparison::less, 
        equal   = comparison::equal, 
        greater = comparison::greater
    };

    void set_compare_codomain(bool truth=true)
    { _compare_codomain = truth; }

    bool compare_codomain()const { return _compare_codomain; }

    int result()const{ return _result; }

    bool covalues_are_equal(LeftIterT& left, RightIterT& right)
    {
        if(LeftT::codomain_value(left) < RightT::codomain_value(right))
            _result = less;
        if(RightT::codomain_value(right) < LeftT::codomain_value(left))
            _result = greater;
        return _result == equal;
    }

    int proceed(LeftIterT& left, RightIterT& right)
    {
        if(LeftT::key_value(left).upper_less(RightT::key_value(right)))
        {
            _prior_left = left;
            ++left;
            return nextleft;
        }
        else if(RightT::key_value(right).upper_less(LeftT::key_value(left)))
        {
            _prior_right = right;
            ++right;
            return nextright;
        }
        else
        {
            ++left; 
            ++right;    
            return nextboth;
        }
    }

    int next_both(LeftIterT& left, RightIterT& right)
    {
        if(left == _left_end)
        {
            _result = (right == _right_end) ? equal : less;
            return stop;
        }

        // left != _left_end
        if(right == _right_end)
        {
            _result = greater;
            return stop;
        }

        // The starting intervals have to begin equally
        if(LeftT::key_value(left).lower_less(RightT::key_value(right)))
        {   // left: same A... = sameA...
            // right:same  B.. = sameB...
            _result = less;
            return stop;
        }

        if(LeftT::key_value(right).lower_less(RightT::key_value(left)))
        {   // left: same  B.. = sameB...
            // right:same A... = sameA...
            _result = greater;
            return stop;
        }

        if(compare_codomain() && !covalues_are_equal(left, right))
            return stop;

        return proceed(left, right);
    }

    int next_left(LeftIterT& left, RightIterT& right)
    {
        if(left == _left_end)
        {   // left: same
            // right:sameA...
            _result = less;
            return stop;
        }

        if(!LeftT::key_value(_prior_left).touches(LeftT::key_value(left)))
        {   // left: same B = sameB...
            // right:sameA  = sameA...
            _result = greater;
            return stop;
        }

        if(compare_codomain() && !covalues_are_equal(left, right))
            return stop;

        return proceed(left, right);
    }

    int next_right(LeftIterT& left, RightIterT& right)
    {
        if(right == _right_end)
        {   // left: sameA...
            // right:same
            _result = greater;
            return stop;
        }

        if(!RightT::key_value(_prior_right).touches(RightT::key_value(right)))
        {
            // left: sameA... = sameA...
            // right:same B.. = sameB...
            _result = less;
            return stop;
        }

        if(compare_codomain() && !covalues_are_equal(left, right))
            return stop;

        return proceed(left, right);
    }

private:
    const LeftT&  _left;
    const RightT& _right;
    LeftIterT     _left_end;
    RightIterT    _right_end;
    bool          _compare_codomain;
    LeftIterT     _prior_left;
    RightIterT    _prior_right;
    int           _result;
};



template<class LeftT, class RightT>
int element_compare
(
    const LeftT& left,   //sub
    const RightT& right, //super
    typename LeftT::const_iterator  left_begin,   
    typename LeftT::const_iterator  left_end,
    typename RightT::const_iterator right_begin, 
    typename RightT::const_iterator right_end
)
{
    typedef element_comparer<LeftT,RightT> Step;
    Step step(left, right, left_end, right_end);
    step.set_compare_codomain(is_map<LeftT>::value && is_map<RightT>::value);

    typename LeftT::const_iterator  left_  = left_begin;
    typename RightT::const_iterator right_ = right_begin;

    int state = Step::nextboth;
    while(state != Step::stop)
    {
        switch(state){
        case Step::nextboth:  state = step.next_both (left_, right_); break;
        case Step::nextleft:  state = step.next_left (left_, right_); break;
        case Step::nextright: state = step.next_right(left_, right_); break;
        }
    }
    return step.result();
}


} // namespace Interval_Set
    
}} // namespace itl boost

#endif 

