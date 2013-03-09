//=======================================================================
// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CONTAINER_GEN_PUSH_RANGE_FUNCTION_GEN_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_PUSH_RANGE_FUNCTION_GEN_HPP_INCLUDED

#include <deque>
#include <utility>
#include <boost/range.hpp>

namespace boost { namespace detail {

    template <typename F, typename C>
    class push_range_function_proxy
    {
        C& _container;

     public:
        explicit push_range_function_proxy(C& c);

        template <typename Itr>
        push_range_function_proxy& operator()(Itr itr, Itr itr_end);

        template <typename InputRange>
        push_range_function_proxy& operator()(InputRange const& r);
    };

    template <typename F, typename C>
    push_range_function_proxy<F,C>::push_range_function_proxy(C& c)
      : _container(c)
    {
    }

    template <typename F, typename C>
    template <typename Itr>
    inline push_range_function_proxy<F,C>&
        push_range_function_proxy<F,C>::operator()(Itr itr, Itr itr_end)
    {
        F::evaluate(this->_container, itr, itr_end);
        return *this;
    }

    template <typename F, typename C>
    template <typename InputRange>
    inline push_range_function_proxy<F,C>&
        push_range_function_proxy<F,C>::operator()(InputRange const& r)
    {
        F::evaluate(this->_container, ::boost::begin(r), ::boost::end(r));
        return *this;
    }

    struct fis_push_range_function
    {
        template <typename C>
        push_range_function_proxy<fis_push_range_function,C>
            operator[](C& _container) const;

        template <typename C, typename InputRange>
        ::std::pair<typename C::iterator,typename C::iterator>
            operator()(C& _container, InputRange const& r) const;

        template <typename C, typename Itr>
        ::std::pair<typename C::iterator,typename C::iterator>
            operator()(C& _container, Itr itr, Itr itr_end) const;

        template <typename C, typename Itr>
        static void evaluate(C& _container, Itr itr, Itr itr_end);
    };

    template <typename C>
    inline push_range_function_proxy<fis_push_range_function,C>
        fis_push_range_function::operator[](C& _container) const
    {
        return push_range_function_proxy<fis_push_range_function,C>(
            _container
        );
    }

    template <typename C, typename InputRange>
    inline ::std::pair<typename C::iterator,typename C::iterator>
        fis_push_range_function::operator()(
            C& _container
          , InputRange const& r
        ) const
    {
        return this->operator()(
            _container
          , ::boost::begin(r)
          , ::boost::end(r)
        );
    }

    template <typename C, typename Itr>
    inline ::std::pair<typename C::iterator,typename C::iterator>
        fis_push_range_function::operator()(
            C& _container
          , Itr itr
          , Itr itr_end
        ) const
    {
        typename C::iterator const range_end = _container.begin();
        fis_push_range_function::evaluate(_container, itr, itr_end);
        return ::std::pair<typename C::iterator,typename C::iterator>(
            _container.begin()
          , range_end
        );
    }

    template <typename C, typename Itr>
    inline void
        fis_push_range_function::evaluate(C& _container, Itr itr, Itr itr_end)
    {
        _container.insert(_container.begin(), itr, itr_end);
    }

    struct ras_push_range_function
    {
        template <typename C>
        push_range_function_proxy<ras_push_range_function,C>
            operator[](C& _container) const;

        template <typename C, typename InputRange>
        ::std::pair<typename C::iterator,typename C::iterator>
            operator()(C& _container, InputRange const& r) const;

        template <typename C, typename Itr>
        ::std::pair<typename C::iterator,typename C::iterator>
            operator()(C& _container, Itr itr, Itr itr_end) const;

        template <typename C, typename Itr>
        static void evaluate(C& _container, Itr itr, Itr itr_end);
    };

    template <typename C>
    inline push_range_function_proxy<ras_push_range_function,C>
        ras_push_range_function::operator[](C& _container) const
    {
        return push_range_function_proxy<ras_push_range_function,C>(
            _container
        );
    }

    template <typename C, typename InputRange>
    inline ::std::pair<typename C::iterator,typename C::iterator>
        ras_push_range_function::operator()(
            C& _container
          , InputRange const& r
        ) const
    {
        return this->operator()(
            _container
          , ::boost::begin(r)
          , ::boost::end(r)
        );
    }

    template <typename C, typename Itr>
    ::std::pair<typename C::iterator,typename C::iterator>
        ras_push_range_function::operator()(
            C& _container
          , Itr itr
          , Itr itr_end
        ) const
    {
        if (_container.empty())
        {
            ras_push_range_function::evaluate(_container, itr, itr_end);
            return ::std::pair<typename C::iterator,typename C::iterator>(
                _container.begin()
              , _container.end()
            );
        }
        else
        {
            typename C::size_type const old_size = _container.size();
            ras_push_range_function::evaluate(_container, itr, itr_end);
            return ::std::pair<typename C::iterator,typename C::iterator>(
                _container.begin() + old_size
              , _container.end()
            );
        }
    }

    template <typename C, typename Itr>
    inline void
        ras_push_range_function::evaluate(C& _container, Itr itr, Itr itr_end)
    {
        _container.insert(_container.end(), itr, itr_end);
    }

    struct bis_push_range_function
    {
        template <typename C>
        push_range_function_proxy<bis_push_range_function,C>
            operator[](C& _container) const;

        template <typename C, typename InputRange>
        ::std::pair<typename C::iterator,typename C::iterator>
            operator()(C& _container, InputRange const& r) const;

        template <typename C, typename Itr>
        ::std::pair<typename C::iterator,typename C::iterator>
            operator()(C& _container, Itr itr, Itr itr_end) const;

        template <typename C, typename Itr>
        static void evaluate(C& _container, Itr itr, Itr itr_end);
    };

    template <typename C>
    inline push_range_function_proxy<bis_push_range_function,C>
        bis_push_range_function::operator[](C& _container) const
    {
        return push_range_function_proxy<bis_push_range_function,C>(
            _container
        );
    }

    template <typename C, typename InputRange>
    inline ::std::pair<typename C::iterator,typename C::iterator>
        bis_push_range_function::operator()(
            C& _container
          , InputRange const& r
        ) const
    {
        return this->operator()(
            _container
          , ::boost::begin(r)
          , ::boost::end(r)
        );
    }

    template <typename C, typename Itr>
    ::std::pair<typename C::iterator,typename C::iterator>
        bis_push_range_function::operator()(
            C& _container
          , Itr itr
          , Itr itr_end
        ) const
    {
        if (_container.empty())
        {
            bis_push_range_function::evaluate(_container, itr, itr_end);
            return ::std::pair<typename C::iterator,typename C::iterator>(
                _container.begin()
              , _container.end()
            );
        }
        else
        {
            typename C::iterator pos = _container.end();
            --pos;
            bis_push_range_function::evaluate(_container, itr, itr_end);
            return ::std::pair<typename C::iterator,typename C::iterator>(
                ++pos
              , _container.end()
            );
        }
    }

    template <typename C, typename Itr>
    inline void
        bis_push_range_function::evaluate(C& _container, Itr itr, Itr itr_end)
    {
        _container.insert(_container.end(), itr, itr_end);
    }

    struct uac_push_range_function
    {
        template <typename C>
        push_range_function_proxy<uac_push_range_function,C>
            operator[](C& _container) const;

        template <typename C, typename InputRange>
        ::std::deque<typename C::iterator>
            operator()(C& _container, InputRange const& r) const;

        template <typename C, typename Itr>
        ::std::deque<typename C::iterator>
            operator()(C& _container, Itr itr, Itr itr_end) const;

        template <typename C, typename Itr>
        static void evaluate(C& _container, Itr itr, Itr itr_end);
    };

    template <typename C>
    inline push_range_function_proxy<uac_push_range_function,C>
        uac_push_range_function::operator[](C& _container) const
    {
        return push_range_function_proxy<uac_push_range_function,C>(
            _container
        );
    }

    template <typename C, typename InputRange>
    inline ::std::deque<typename C::iterator>
        uac_push_range_function::operator()(
            C& _container
          , InputRange const& r
        ) const
    {
        return this->operator()(
            _container
          , ::boost::begin(r)
          , ::boost::end(r)
        );
    }

    template <typename C, typename Itr>
    ::std::deque<typename C::iterator>
        uac_push_range_function::operator()(
            C& _container
          , Itr itr
          , Itr itr_end
        ) const
    {
        ::std::deque<typename C::iterator> result;

        for (
            ::std::pair<typename C::iterator,bool> insert_result;
            itr != itr_end;
            ++itr
        )
        {
            insert_result = _container.insert(*itr);

            if (insert_result.second)
            {
                result.push_back(insert_result.first);
            }
        }

        return result;
    }

    template <typename C, typename Itr>
    inline void
        uac_push_range_function::evaluate(C& _container, Itr itr, Itr itr_end)
    {
        _container.insert(itr, itr_end);
    }

    struct mac_push_range_function
    {
        template <typename C>
        push_range_function_proxy<mac_push_range_function,C>
            operator[](C& _container) const;

        template <typename C, typename InputRange>
        ::std::deque<typename C::iterator>
            operator()(C& _container, InputRange const& r) const;

        template <typename C, typename Itr>
        ::std::deque<typename C::iterator>
            operator()(C& _container, Itr itr, Itr itr_end) const;

        template <typename C, typename Itr>
        static void evaluate(C& _container, Itr itr, Itr itr_end);
    };

    template <typename C>
    inline push_range_function_proxy<mac_push_range_function,C>
        mac_push_range_function::operator[](C& _container) const
    {
        return push_range_function_proxy<mac_push_range_function,C>(
            _container
        );
    }

    template <typename C, typename InputRange>
    inline ::std::deque<typename C::iterator>
        mac_push_range_function::operator()(
            C& _container
          , InputRange const& r
        ) const
    {
        return this->operator()(
            _container
          , ::boost::begin(r)
          , ::boost::end(r)
        );
    }

    template <typename C, typename Itr>
    ::std::deque<typename C::iterator>
        mac_push_range_function::operator()(
            C& _container
          , Itr itr
          , Itr itr_end
        ) const
    {
        ::std::deque<typename C::iterator> result;

        for (; itr != itr_end; ++itr)
        {
            result.push_back(_container.insert(*itr));
        }

        return result;
    }

    template <typename C, typename Itr>
    inline void
        mac_push_range_function::evaluate(C& _container, Itr itr, Itr itr_end)
    {
        _container.insert(itr, itr_end);
    }

    struct ptr_uac_push_range_function
    {
        template <typename C>
        push_range_function_proxy<ptr_uac_push_range_function,C>
            operator[](C& _container) const;

        template <typename C, typename InputRange>
        ::std::deque<typename C::iterator>
            operator()(C& _container, InputRange const& r) const;

        template <typename C, typename Itr>
        ::std::deque<typename C::iterator>
            operator()(C& _container, Itr itr, Itr itr_end) const;

        template <typename C, typename Itr>
        static void
            evaluate(C& _container, Itr itr, Itr itr_end);
    };

    template <typename C>
    inline push_range_function_proxy<ptr_uac_push_range_function,C>
        ptr_uac_push_range_function::operator[](C& _container) const
    {
        return push_range_function_proxy<ptr_uac_push_range_function,C>(
            _container
        );
    }

    template <typename C, typename InputRange>
    inline ::std::deque<typename C::iterator>
        ptr_uac_push_range_function::operator()(
            C& _container
          , InputRange const& r
        ) const
    {
        return this->operator()(
            _container
          , ::boost::begin(r)
          , ::boost::end(r)
        );
    }

    template <typename C, typename Itr>
    ::std::deque<typename C::iterator>
        ptr_uac_push_range_function::operator()(
            C& _container
          , Itr itr
          , Itr itr_end
        ) const
    {
        ::std::deque<typename C::iterator> result;

        for (
            ::std::pair<typename C::iterator,bool> insert_result;
            itr != itr_end;
            ++itr
        )
        {
            insert_result = _container.insert(new typename C::key_type(*itr));

            if (insert_result.second)
            {
                result.push_back(insert_result.first);
            }
        }

        return result;
    }

    template <typename C, typename Itr>
    inline void
        ptr_uac_push_range_function::evaluate(
            C& _container
          , Itr itr
          , Itr itr_end
        )
    {
        _container.insert(itr, itr_end);
    }

    struct ptr_mac_push_range_function
    {
        template <typename C>
        push_range_function_proxy<ptr_mac_push_range_function,C>
            operator[](C& _container) const;

        template <typename C, typename InputRange>
        ::std::deque<typename C::iterator>
            operator()(C& _container, InputRange const& r) const;

        template <typename C, typename Itr>
        ::std::deque<typename C::iterator>
            operator()(C& _container, Itr itr, Itr itr_end) const;

        template <typename C, typename Itr>
        static void
            evaluate(C& _container, Itr itr, Itr itr_end);
    };

    template <typename C>
    inline push_range_function_proxy<ptr_mac_push_range_function,C>
        ptr_mac_push_range_function::operator[](C& _container) const
    {
        return push_range_function_proxy<ptr_mac_push_range_function,C>(
            _container
        );
    }

    template <typename C, typename InputRange>
    inline ::std::deque<typename C::iterator>
        ptr_mac_push_range_function::operator()(
            C& _container
          , InputRange const& r
        ) const
    {
        return this->operator()(
            _container
          , ::boost::begin(r)
          , ::boost::end(r)
        );
    }

    template <typename C, typename Itr>
    ::std::deque<typename C::iterator>
        ptr_mac_push_range_function::operator()(
            C& _container
          , Itr itr
          , Itr itr_end
        ) const
    {
        ::std::deque<typename C::iterator> result;

        for (; itr != itr_end; ++itr)
        {
            result.push_back(
                _container.insert(new typename C::key_type(*itr))
            );
        }

        return result;
    }

    template <typename C, typename Itr>
    inline void
        ptr_mac_push_range_function::evaluate(
            C& _container
          , Itr itr
          , Itr itr_end
        )
    {
        _container.insert(itr, itr_end);
    }

    struct uns_ac_push_range_function
    {
        template <typename C>
        push_range_function_proxy<uns_ac_push_range_function,C>
            operator[](C& _container) const;

        template <typename C, typename InputRange>
        void operator()(C& _container, InputRange const& r) const;

        template <typename C, typename Itr>
        void operator()(C& _container, Itr itr, Itr itr_end) const;

        template <typename C, typename Itr>
        static void
            evaluate(C& _container, Itr itr, Itr itr_end);
    };

    template <typename C>
    inline push_range_function_proxy<uns_ac_push_range_function,C>
        uns_ac_push_range_function::operator[](C& _container) const
    {
        return push_range_function_proxy<uns_ac_push_range_function,C>(
            _container
        );
    }

    template <typename C, typename InputRange>
    inline void
        uns_ac_push_range_function::operator()(
            C& _container
          , InputRange const& r
        ) const
    {
        this->operator()(_container, ::boost::begin(r), ::boost::end(r));
    }

    template <typename C, typename Itr>
    inline void
        uns_ac_push_range_function::operator()(
            C& _container
          , Itr itr
          , Itr itr_end
        ) const
    {
        uns_ac_push_range_function::evaluate(_container, itr, itr_end);
    }

    template <typename C, typename Itr>
    inline void
        uns_ac_push_range_function::evaluate(
            C& _container
          , Itr itr
          , Itr itr_end
        )
    {
        _container.insert(itr, itr_end);
    }
}}  // namespace boost::detail

#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/container_gen/has_stable_iters_selector.hpp>
#include <boost/container_gen/is_associative_selector.hpp>
#include <boost/container_gen/is_unique_assoc_selector.hpp>
#include <boost/container_gen/is_multiple_assoc_selector.hpp>
#include <boost/container_gen/is_ptr_selector.hpp>
#include <boost/container_gen/is_random_access_selector.hpp>

//[reference__push_range_function_gen
namespace boost {

    template <typename Selector>
    struct push_range_function_gen
        //<-
      : ::boost::mpl::eval_if<
            is_associative_selector<Selector>
          , ::boost::mpl::eval_if<
                has_stable_iterators_selector<Selector>
              , ::boost::mpl::eval_if<
                    is_ptr_selector<Selector>
                  , ::boost::mpl::if_<
                        is_unique_associative_selector<Selector>
                      , detail::ptr_uac_push_range_function
                      , detail::ptr_mac_push_range_function
                    >
                  , ::boost::mpl::if_<
                        is_multiple_associative_selector<Selector>
                      , detail::mac_push_range_function
                      , detail::uac_push_range_function
                    >
                >
              , ::boost::mpl::identity<detail::uns_ac_push_range_function>
            >
          , ::boost::mpl::if_<
                is_random_access_selector<Selector>
              , detail::ras_push_range_function
              , detail::bis_push_range_function
            >
        >
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1, push_range_function_gen, (Selector))
        //->
    };
}  // namespace boost
//]

#include <boost/config.hpp>
#include <boost/container_gen/selectors.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

    template <typename AllocatorSelector>
    struct push_range_function_gen<slist_selector<AllocatorSelector> >
    {
        typedef detail::fis_push_range_function type;
    };
}  // namespace boost

#elif !defined BOOST_NO_SLIST

namespace boost {

    template <>
    struct push_range_function_gen<slist_selector_base>
    {
        typedef detail::fis_push_range_function type;
    };
}  // namespace boost

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION, BOOST_NO_SLIST

#endif  // BOOST_CONTAINER_GEN_PUSH_RANGE_FUNCTION_GEN_HPP_INCLUDED

