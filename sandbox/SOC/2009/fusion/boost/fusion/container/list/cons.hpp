/*=============================================================================
    Copyright (c) 2005 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_LIST_CONS_HPP
#define BOOST_FUSION_CONTAINER_LIST_CONS_HPP

#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/front.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/ref.hpp>
#include <boost/fusion/support/assign_tags.hpp>
#include <boost/fusion/support/sequence_assign.hpp>

#include <boost/fusion/container/list/cons_iterator.hpp>
#include <boost/fusion/container/list/detail/cons/begin_impl.hpp>
#include <boost/fusion/container/list/detail/cons/end_impl.hpp>
#include <boost/fusion/container/list/detail/cons/at_impl.hpp>
#include <boost/fusion/container/list/detail/cons/value_at_impl.hpp>
#include <boost/fusion/container/list/detail/cons/empty_impl.hpp>

#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>

namespace boost { namespace fusion
{
    struct void_;
    struct cons_tag;
    struct forward_traversal_tag;
    struct fusion_sequence_tag;

    struct nil
      : sequence_base<nil>
    {
        typedef mpl::int_<0> size;
        typedef cons_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;
        typedef forward_traversal_tag category;
        typedef void_ car_type;
        typedef void_ cdr_type;

        nil()
        {}

        nil(const nil&)
        {
        }

        template<typename Sequence>
        nil(detail::sequence_assign_type<Sequence> const volatile&)
        {
            //TODO cschmidt: assert!
        }

        template<typename Sequence>
        nil(detail::sequence_assign_type<Sequence> const volatile&&)
        {
            //TODO cschmidt: assert!
        }

        template<typename Iterator>
        nil(detail::assign_by_deref,Iterator const&)
        {
        }

        template<typename Sequence>
        nil&
        operator=(BOOST_FUSION_R_ELSE_CLREF(Sequence))
        {
            //TODO cschmidt: assert!
            return *this;
        }

        template<typename Iterator>
        void
        assign(Iterator const&)
        {
        }
    };

    template <typename Car, typename Cdr = nil>
    struct cons : sequence_base<cons<Car, Cdr> >
    {
        typedef mpl::int_<Cdr::size::value+1> size;
        typedef cons_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;
        typedef forward_traversal_tag category;
        typedef Car car_type;
        typedef Cdr cdr_type;

        cons()
          : car()
          , cdr()
        {}

        template<typename Cons>
        cons(BOOST_FUSION_R_ELSE_CLREF(Cons) cons_,
               typename enable_if<is_convertible<
                   typename detail::remove_reference<Cons>::type*
                 , cons const volatile*> >::type* =NULL)
          //cschmidt: iterators so we do not have to deal with the cv-ness
          //of cons_.car/cons_.cdr explicitly
          : car(fusion::front(BOOST_FUSION_FORWARD(Cons,cons_)))
          , cdr(detail::assign_by_deref(),
                  fusion::next(
                          fusion::begin(BOOST_FUSION_FORWARD(Cons,cons_))))
        {
        }

        template<typename SequenceAssign>
        cons(BOOST_FUSION_R_ELSE_CLREF(SequenceAssign) seq,
             typename enable_if<
                 is_sequence_assign<SequenceAssign> >::type* =NULL)
          : car(fusion::front(seq.get()))
          , cdr(detail::assign_by_deref(),
                  fusion::next(fusion::begin(seq.get())))
        {
        }

        //cschmidt: rvalue ref if possible, so this does not collide with
        //cons(OtherCar&&,OtherCdr&&)
        template<typename Iterator>
        cons(detail::assign_by_deref,
             BOOST_FUSION_R_ELSE_CLREF(Iterator) iterator)
          : car(fusion::deref(iterator))
          , cdr(detail::assign_by_deref(),fusion::next(iterator))
        {
        }

        /*
        template<typename Sequence>
        vector(typename enable_if_c<sizeof...(Elements)!=1,
                                BOOST_FUSION_R_ELSE_CLREF(Sequence)>::type seq)
          : base(detail::assign_by_deref(),
                 fusion::begin(BOOST_FUSION_FORWARD(Sequence,seq)))
        {
        }
        */

#ifdef BOOST_NO_RVALUE_REFERENCES
        explicit cons(typename detail::call_param<Car>::type car)
          : car(car), cdr()
        {}

        cons(typename detail::call_param<Car>::type car
           , typename detail::call_param<Cdr>::type cdr)
          : car(car), cdr(cdr)
        {}
#else
        template<typename OtherCar>
        explicit cons(OtherCar&& other_car,
                typename disable_if<is_convertible<
                    typename detail::remove_reference<OtherCar>::type*
                  , cons const volatile*> >::type* =NULL)
          : car(std::forward<OtherCar>(other_car))
          , cdr()
        {}

        template<typename OtherCar,typename OtherCdr>
        cons(OtherCar&& other_car,OtherCdr&& other_cdr)
          : car(std::forward<OtherCar>(other_car))
          , cdr(std::forward<OtherCdr>(other_cdr))
        {}
#endif

        template<typename Sequence>
        cons&
        operator=(BOOST_FUSION_R_ELSE_CLREF(Sequence) sequence)
        {
            assign(fusion::begin(BOOST_FUSION_FORWARD(Sequence,sequence)));
            return *this;
        }

        template<typename Iterator>
        void
        assign(Iterator const& iterator)
        {
            car=fusion::deref(iterator);
            cdr.assign(fusion::next(iterator));
        }

        car_type car;
        cdr_type cdr;
    };
}}

#endif
