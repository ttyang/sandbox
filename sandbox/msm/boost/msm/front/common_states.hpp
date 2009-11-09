// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_COMMON_STATES_H
#define BOOST_MSM_FRONT_COMMON_STATES_H

#include <boost/mpl/int.hpp>

#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/at_c.hpp>

#include <boost/type_traits/add_const.hpp>

namespace boost { namespace msm { namespace front
{
// default base: non-polymorphic, not visitable
struct default_base_state 
{
    ~default_base_state(){}
};
// default polymorphic base state. Derive all states from it to get polymorphic behavior
struct polymorphic_state
{
    virtual ~polymorphic_state() {}
};

template <class Attributes= ::boost::fusion::vector<> >
struct inherit_attributes
{
	// on the fly attribute creation capability
	typedef Attributes		attributes_type;
    template <int Index>
    typename ::boost::fusion::result_of::at<attributes_type, 
                                            ::boost::mpl::int_<Index> >::type
    get_attribute() 
    {
        return ::boost::fusion::at_c<Index>(m_attributes);
    }
    
    template <int Index>
    typename ::boost::add_const<
        typename ::boost::fusion::result_of::at<attributes_type,
                                                ::boost::mpl::int_<Index> >::type>::type
	get_attribute()const 
    {
        return const_cast< 
            typename ::boost::add_const< 
                typename ::boost::fusion::result_of::at< attributes_type,
                                                ::boost::mpl::int_<Index> >::type>::type>
                                (::boost::fusion::at_c<Index>(m_attributes));
    }

private:
	// attributes
	Attributes m_attributes;
};

// the interface for all states. Defines entry and exit functions. Overwrite to implement for any state needing it.
template<class USERBASE,class Attributes= ::boost::fusion::vector<> >
struct state_base : public inherit_attributes<Attributes>, USERBASE
{
    typedef USERBASE		user_state_base;
	typedef Attributes		attributes_type;

    // empty implementation for the states not wishing to define an entry condition
    // will not be called polymorphic way
    template <class Event,class FSM>
    void on_entry(Event const& ,FSM&){}
    template <class Event,class FSM>
    void on_exit(Event const&,FSM& ){}
};

}}}

#endif //BOOST_MSM_FRONT_COMMON_STATES_H

