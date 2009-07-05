// Copyright Christopher Schmidt 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FUSION_VIEW_DETAIL_VIEW_STORAGE_HPP
#define BOOST_FUSION_VIEW_DETAIL_VIEW_STORAGE_HPP

#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/ref.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion { namespace detail
{
    template<typename T>
    struct view_storage
    {
    private:
        template<typename OtherT>
        static typename
            enable_if<
                traits::is_view<T>
              , BOOST_FUSION_R_ELSE_LREF(OtherT)
            >::type
        get_init_type(BOOST_FUSION_R_ELSE_LREF(OtherT) other_t)
        {
            return other_t;
        }

        template<typename OtherT>
        static typename
            disable_if<
                traits::is_view<T>
              , typename detail::remove_reference<OtherT>::type*
            >::type
        get_init_type(BOOST_FUSION_R_ELSE_LREF(OtherT) other_t)
        {
            return &other_t;
        }

    public:
        typedef typename
            mpl::if_<
                traits::is_view<T>
              , typename detail::remove_reference<T>::type
              , typename detail::add_lref<T>::type
            >::type
        type;

#define VIEW_STORAGE_CTOR(COMBINATION)\
        template<typename OtherT>\
        view_storage(view_storage<OtherT> COMBINATION storage)\
          : t(get_init_type(storage.get()))\
        {}

        BOOST_FUSION_ALL_CV_REF_COMBINATIONS(VIEW_STORAGE_CTOR)

#undef VIEW_STORAGE_CTOR

        template<typename OtherT>
        view_storage(BOOST_FUSION_R_ELSE_LREF(OtherT) other_t)
          : t(get_init_type(BOOST_FUSION_FORWARD(OtherT,other_t)))
        {}

        template<typename OtherViewStorage>
        view_storage&
        operator=(BOOST_FUSION_R_ELSE_LREF(OtherViewStorage) other_storage)
        {
            t=BOOST_FUSION_FORWARD(OtherViewStorage,other_storage).t;
            return *this;
        }

        //TODO cschmidt: volatile?
        //typename detail::add_lref<type>::type
        //get()
        //{
        //    return get(typename traits::is_view<T>::type());
        //}

        typename mpl::if_<traits::is_view<T>, type&, type>::type
        get() const
        {
            return get(typename traits::is_view<T>::type());
        }

    private:
        //type&
        //get(mpl::true_ /*is_view*/)
        //{
        //    return t;
        //}

        //type
        //get(mpl::false_ /*is_view*/)
        //{
        //    return *t;
        //}

        type&
        get(mpl::true_ /*is_view*/)const
        {
            return t;
        }

        type
        get(mpl::false_ /*is_view*/)const
        {
            return *t;
        }

        typedef typename detail::remove_reference<T>::type non_ref_t;
        mutable typename
            mpl::if_<traits::is_view<T>, non_ref_t, non_ref_t*>::type
        t;
    };
}}}

#endif
