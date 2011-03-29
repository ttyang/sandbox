/*==============================================================================
    Copyright (c) 2005 Joel de Guzman
    Copyright (c) 2005 Eric Niebler
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_LIST_CONS_HPP
#define BOOST_FUSION_CONTAINER_LIST_CONS_HPP

#include <boost/fusion/support/internal/base.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/front.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/support/internal/sequence_base.hpp>
#include <boost/fusion/support/internal/is_explicitly_convertible.hpp>
#include <boost/fusion/support/internal/assign_tags.hpp>
#include <boost/fusion/support/internal/sequence_assign.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>
#ifdef BOOST_FUSION_NO_RVALUE_REFERENCES
#   include <boost/call_traits.hpp>
#endif
#include <boost/utility/enable_if.hpp>

#include <boost/fusion/container/list/detail/cons_fwd.hpp>
#include <boost/fusion/container/list/detail/cons_iterator.hpp>
#include <boost/fusion/container/list/detail/value_at_impl.hpp>
#include <boost/fusion/container/list/detail/at_impl.hpp>
#include <boost/fusion/container/list/detail/begin_impl.hpp>
#include <boost/fusion/container/list/detail/end_impl.hpp>
#include <boost/fusion/container/list/detail/deref_impl.hpp>
#include <boost/fusion/container/list/detail/next_impl.hpp>
#include <boost/fusion/container/list/detail/value_of_impl.hpp>
#include <boost/fusion/container/list/detail/equal_to_impl.hpp>

BOOST_FUSION_DEFINE_IS_SEQUENCE_IS_VIEW_IMPL(cons_tag, 0)

namespace boost { namespace fusion
{
    struct void_;
    struct fusion_sequence_tag;

#ifdef BOOST_MSVC
#   pragma warning(push)
    //'class' : multiple copy constructors specified
#   pragma warning(disable:4521)
#endif

    struct nil
    {
        typedef void_ car_type;
        typedef void_ cdr_type;

        typedef mpl::int_<0> size;
        typedef cons_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef forward_traversal_tag category;

        nil()
        {}

#define BOOST_FUSION_NIL_CTOR(MODIFIER,_)\
        nil(nil MODIFIER)\
        {}

        BOOST_FUSION_ALL_CTOR_COMBINATIONS(BOOST_FUSION_NIL_CTOR,_);

#undef BOOST_FUSION_CONS_CTOR

        template<typename SeqAssign>
        nil(BOOST_FUSION_R_ELSE_CLREF(SeqAssign))
        {
#ifdef BOOST_FUSION_NO_RVALUE_REFERENCES
            BOOST_FUSION_MPL_ASSERT((
                result_of::empty<typename SeqAssign::seq_type>));
#else
            BOOST_FUSION_MPL_ASSERT((
                result_of::empty<
                    typename detail::remove_reference<SeqAssign>::type::seq_type
                >));
#endif
        }

        template<typename It>
        nil(detail::assign_by_deref,It const&)
        {}

        template<typename Seq>
        nil&
        operator=(BOOST_FUSION_R_ELSE_CLREF(Seq))
        {
            BOOST_FUSION_MPL_ASSERT((result_of::empty<Seq>))
            return *this;
        }

        template<typename It>
        void
        assign(It const&)
        {}
    };

    template<typename Car, typename Cdr = nil>
    struct cons
    {
        typedef Car car_type;
        typedef Cdr cdr_type;

        typedef mpl::int_<Cdr::size::value+1> size;
        typedef cons_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef forward_traversal_tag category;

        cons()
          : car()
          , cdr()
        {}

        //cschmidt: use iterators so we do not have to deal with the cv-ness
        //of cons_.car/cons_.cdr explicitly
#define BOOST_FUSION_CONS_CTOR(MODIFIER,_)\
        cons(cons MODIFIER cons_)\
          : car(fusion::front(static_cast<cons MODIFIER>(cons_)))\
          , cdr(detail::assign_by_deref(),\
                fusion::next(fusion::begin(\
                    static_cast<cons MODIFIER>(cons_))))\
        {}

        BOOST_FUSION_ALL_CTOR_COMBINATIONS(BOOST_FUSION_CONS_CTOR,_);

#undef BOOST_FUSION_CONS_CTOR

        //cschmidt: rvalue ref if possible, so this does not collide with
        //cons(OtherCar&&,OtherCdr&&)
        template<typename It>
        cons(detail::assign_by_deref,BOOST_FUSION_R_ELSE_CLREF(It) it)
          : car(fusion::deref(it))
          , cdr(detail::assign_by_deref(),fusion::next(it))
        {}

#ifdef BOOST_NO_VARIADIC_TEMPLATES
//cschmidt: https://svn.boost.org/trac/boost/ticket/4530#comment:1
#   if defined(BOOST_FUSION_NO_RVALUE_REFERENCES) || defined(BOOST_MSVC)
        explicit
        cons(typename call_traits<Car>::param_type car)
          : car(car)
        {}

        cons(typename call_traits<Car>::param_type car,Cdr const& cdr)
          : car(car)
          , cdr(cdr)
        {}
#   else
        template<typename OtherCar>
        explicit
        cons(OtherCar&& car,
            typename enable_if<
                detail::is_explicitly_convertible<
                    BOOST_FUSION_R_ELSE_CLREF(OtherCar)
                  , car_type
                >
            >::type* =0)
          : car(std::forward<OtherCar>(car))
        {}

        template<typename OtherCar,typename OtherCdr>
        cons(BOOST_FUSION_R_ELSE_CLREF(OtherCar) car,
             BOOST_FUSION_R_ELSE_CLREF(OtherCdr) cdr)
          : car(BOOST_FUSION_FORWARD(OtherCar,car))
          , cdr(BOOST_FUSION_FORWARD(OtherCdr,cdr))
        {}
#   endif
#else
#   ifdef BOOST_FUSION_NO_RVALUE_REFERENCES
        template<typename... CdrArgs>
        explicit
        cons(typename call_traits<Car>::param_type car,
             CdrArgs const&... cdr_args)
          : car(car)
          , cdr(cdr_args)
        {}
#   else
        template<typename OtherCar,typename... CdrArgs>
        explicit
        cons(OtherCar&& other_car,CdrArgs&&... cdr_args)
          : car(std::forward<OtherCar>(other_car))
          , cdr(std::forward<CdrArgs>(cdr_args)...)
        {}
#   endif
#endif

        template<typename Seq>
        cons(
            BOOST_FUSION_R_ELSE_CLREF(Seq) seq,
            typename disable_if<
                detail::is_explicitly_convertible<
                    BOOST_FUSION_R_ELSE_CLREF(Seq)
                  , car_type
                >
            >::type* =0)
          : car(fusion::front(BOOST_FUSION_FORWARD(Seq,seq)))
          , cdr(detail::assign_by_deref(),
                  fusion::next(fusion::begin(BOOST_FUSION_FORWARD(Seq,seq))))
        {
            BOOST_FUSION_MPL_ASSERT((
                    mpl::equal_to<size,result_of::size<Seq> >))
        }

#define BOOST_FUSION_CONS_ASSIGN_CTOR(MODIFIER,_)\
        template<typename SeqRef>\
        cons(detail::sequence_assign_type<SeqRef> MODIFIER seq_assign)\
          : car(fusion::front(seq_assign.get()))\
          , cdr(detail::assign_by_deref(),\
                  fusion::next(fusion::begin(seq_assign.get())))\
        {\
            BOOST_FUSION_MPL_ASSERT((\
                mpl::equal_to<size,result_of::size<SeqRef> >))\
        }

        BOOST_FUSION_ALL_CTOR_COMBINATIONS(BOOST_FUSION_CONS_ASSIGN_CTOR,_)

#undef BOOST_FUSION_CONS_ASSIGN_CTOR

        template<typename Seq>
        cons&
        operator=(BOOST_FUSION_R_ELSE_CLREF(Seq) seq)
        {
            BOOST_FUSION_MPL_ASSERT_NOT((result_of::empty<Seq>))

            assign(fusion::begin(BOOST_FUSION_FORWARD(Seq,seq)));
            return *this;
        }

        cons&
        operator=(cons const& cons_)
        {
#ifdef BOOST_FUSION_NO_RVALUE_REFERENCES
            return this->operator=<cons<Car,Cdr> >(cons_);
#else
            return this->operator=<cons<Car,Cdr> const&>(cons_);
#endif
        }

        template<typename It>
        void
        assign(It const& it)
        {
            car=fusion::deref(it);
            cdr.assign(fusion::next(it));
        }

        car_type car;
        cdr_type cdr;
    };

#ifdef BOOST_MSVC
#   pragma warning(pop)
#endif
}}

#endif