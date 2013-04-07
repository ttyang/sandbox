//=======================================================================
// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CONTAINER_GEN_INSERT_RANGE_FUNCTION_GEN_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_INSERT_RANGE_FUNCTION_GEN_HPP_INCLUDED

#include <deque>
#include <utility>
#include <algorithm>
#include <boost/mpl/bool.hpp>
#include <boost/range.hpp>
#include <boost/assert.hpp>

namespace boost { namespace detail {

    template <typename F, typename C>
    class insert_range_function_proxy
    {
        C& _container;

     public:
        explicit insert_range_function_proxy(C& c);

        template <typename Itr>
        insert_range_function_proxy&
            operator()(typename C::iterator pos, Itr itr, Itr itr_end);

        template <typename InputRange>
        insert_range_function_proxy&
            operator()(typename C::iterator pos, InputRange const& r);
    };

    template <typename F, typename C>
    insert_range_function_proxy<F,C>::insert_range_function_proxy(C& c)
      : _container(c)
    {
    }

    template <typename F, typename C>
    template <typename Itr>
    inline insert_range_function_proxy<F,C>&
        insert_range_function_proxy<F,C>::operator()(
            typename C::iterator pos
          , Itr itr
          , Itr itr_end
        )
    {
        F::evaluate(this->_container, pos, itr, itr_end);
        return *this;
    }

    template <typename F, typename C>
    template <typename InputRange>
    inline insert_range_function_proxy<F,C>&
        insert_range_function_proxy<F,C>::operator()(
            typename C::iterator pos
          , InputRange const& r
        )
    {
        F::evaluate(this->_container, pos, ::boost::begin(r), ::boost::end(r));
        return *this;
    }

    struct fis_insert_range_function
    {
        template <typename C>
        insert_range_function_proxy<fis_insert_range_function,C>
            operator[](C& _container) const;

        template <typename C, typename InputRange>
        ::std::pair<typename C::iterator,typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , InputRange const& r
            ) const;

        template <typename C, typename Itr>
        ::std::pair<typename C::iterator,typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , Itr itr
              , Itr itr_end
            ) const;

        template <typename C, typename Itr>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , Itr itr
              , Itr itr_end
            );
    };

    template <typename C>
    inline insert_range_function_proxy<fis_insert_range_function,C>
        fis_insert_range_function::operator[](C& _container) const
    {
        return insert_range_function_proxy<fis_insert_range_function,C>(
            _container
        );
    }

    template <typename C, typename InputRange>
    inline ::std::pair<typename C::iterator,typename C::iterator>
        fis_insert_range_function::operator()(
            C& _container
          , typename C::iterator pos
          , InputRange const& r
        ) const
    {
        return this->operator()(
            _container
          , pos
          , ::boost::begin(r)
          , ::boost::end(r)
        );
    }

    template <typename C, typename Itr>
    inline ::std::pair<typename C::iterator,typename C::iterator>
        fis_insert_range_function::operator()(
            C& _container
          , typename C::iterator pos
          , Itr itr
          , Itr itr_end
        ) const
    {
        typename C::iterator result_begin = _container.previous(pos);
        fis_insert_range_function::evaluate(_container, pos, itr, itr_end);
        return ::std::pair<typename C::iterator,typename C::iterator>(
            ++result_begin
          , pos
        );
    }

    template <typename C, typename Itr>
    inline void
        fis_insert_range_function::evaluate(
            C& _container
          , typename C::iterator pos
          , Itr itr
          , Itr itr_end
        )
    {
        _container.insert(pos, itr, itr_end);
    }

    struct ras_insert_range_function
    {
        template <typename C>
        insert_range_function_proxy<ras_insert_range_function,C>
            operator[](C& _container) const;

        template <typename C, typename InputRange>
        ::std::pair<typename C::iterator,typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , InputRange const& r
            ) const;

        template <typename C, typename Itr>
        ::std::pair<typename C::iterator,typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , Itr itr
              , Itr itr_end
            ) const;

        template <typename C, typename Itr>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , Itr itr
              , Itr itr_end
            );
    };

    template <typename C>
    inline insert_range_function_proxy<ras_insert_range_function,C>
        ras_insert_range_function::operator[](C& _container) const
    {
        return insert_range_function_proxy<ras_insert_range_function,C>(
            _container
        );
    }

    template <typename C, typename InputRange>
    inline ::std::pair<typename C::iterator,typename C::iterator>
        ras_insert_range_function::operator()(
            C& _container
          , typename C::iterator pos
          , InputRange const& r
        ) const
    {
        return this->operator()(
            _container
          , pos
          , ::boost::begin(r)
          , ::boost::end(r)
        );
    }

    template <typename C, typename Itr>
    inline ::std::pair<typename C::iterator,typename C::iterator>
        ras_insert_range_function::operator()(
            C& _container
          , typename C::iterator pos
          , Itr itr
          , Itr itr_end
        ) const
    {
        typename C::size_type const begin_index = (
            ::std::distance(_container.begin(), pos)
        );
        ras_insert_range_function::evaluate(_container, pos, itr, itr_end);
        return ::std::pair<typename C::iterator,typename C::iterator>(
            _container.begin() + begin_index
          , _container.begin() + begin_index + ::std::distance(itr, itr_end)
        );
    }

    template <typename C, typename Itr>
    inline void
        ras_insert_range_function::evaluate(
            C& _container
          , typename C::iterator pos
          , Itr itr
          , Itr itr_end
        )
    {
        _container.insert(pos, itr, itr_end);
    }

    struct bis_insert_range_function
    {
        template <typename C>
        insert_range_function_proxy<bis_insert_range_function,C>
            operator[](C& _container) const;

        template <typename C, typename InputRange>
        ::std::pair<typename C::iterator,typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , InputRange const& r
            ) const;

        template <typename C, typename Itr>
        ::std::pair<typename C::iterator,typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , Itr itr
              , Itr itr_end
            ) const;

        template <typename C, typename Itr>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , Itr itr
              , Itr itr_end
            );
    };

    template <typename C>
    inline insert_range_function_proxy<bis_insert_range_function,C>
        bis_insert_range_function::operator[](C& _container) const
    {
        return insert_range_function_proxy<bis_insert_range_function,C>(
            _container
        );
    }

    template <typename C, typename InputRange>
    inline ::std::pair<typename C::iterator,typename C::iterator>
        bis_insert_range_function::operator()(
            C& _container
          , typename C::iterator pos
          , InputRange const& r
        ) const
    {
        return this->operator()(
            _container
          , pos
          , ::boost::begin(r)
          , ::boost::end(r)
        );
    }

    template <typename C, typename Itr>
    inline ::std::pair<typename C::iterator,typename C::iterator>
        bis_insert_range_function::operator()(
            C& _container
          , typename C::iterator pos
          , Itr itr
          , Itr itr_end
        ) const
    {
        if (_container.empty())
        {
            BOOST_ASSERT(pos == _container.end());
            bis_insert_range_function::evaluate(_container, pos, itr, itr_end);
            return ::std::pair<typename C::iterator,typename C::iterator>(
                _container.begin()
              , _container.end()
            );
        }
        else
        {
            typename C::iterator start = pos;
            --start;
            bis_insert_range_function::evaluate(_container, pos, itr, itr_end);
            return ::std::pair<typename C::iterator,typename C::iterator>(
                ++start
              , pos
            );
        }
    }

    template <typename C, typename Itr>
    inline void
        bis_insert_range_function::evaluate(
            C& _container
          , typename C::iterator pos
          , Itr itr
          , Itr itr_end
        )
    {
        _container.insert(pos, itr, itr_end);
    }

    struct uac_insert_range_function
    {
        template <typename C>
        insert_range_function_proxy<uac_insert_range_function,C>
            operator[](C& _container) const;

        template <typename C, typename InputRange>
        ::std::deque<typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , InputRange const& r
            ) const;

        template <typename C, typename Itr>
        ::std::deque<typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , Itr itr
              , Itr itr_end
            ) const;

        template <typename C, typename Itr>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , Itr itr
              , Itr itr_end
            );
    };

    template <typename C>
    inline insert_range_function_proxy<uac_insert_range_function,C>
        uac_insert_range_function::operator[](C& _container) const
    {
        return insert_range_function_proxy<uac_insert_range_function,C>(
            _container
        );
    }

    template <typename C, typename InputRange>
    inline ::std::deque<typename C::iterator>
        uac_insert_range_function::operator()(
            C& _container
          , typename C::iterator pos
          , InputRange const& r
        ) const
    {
        return this->operator()(
            _container
          , pos
          , ::boost::begin(r)
          , ::boost::end(r)
        );
    }

    template <typename C, typename Itr>
    ::std::deque<typename C::iterator>
        uac_insert_range_function::operator()(
            C& _container
          , typename C::iterator pos
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
        uac_insert_range_function::evaluate(
            C& _container
          , typename C::iterator pos
          , Itr itr
          , Itr itr_end
        )
    {
        _container.insert(itr, itr_end);
    }

    struct mac_insert_range_function
    {
        template <typename C>
        insert_range_function_proxy<mac_insert_range_function,C>
            operator[](C& _container) const;

        template <typename C, typename InputRange>
        ::std::deque<typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , InputRange const& r
            ) const;

        template <typename C, typename Itr>
        ::std::deque<typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , Itr itr
              , Itr itr_end
            ) const;

        template <typename C, typename Itr>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , Itr itr
              , Itr itr_end
            );
    };

    template <typename C>
    inline insert_range_function_proxy<mac_insert_range_function,C>
        mac_insert_range_function::operator[](C& _container) const
    {
        return insert_range_function_proxy<mac_insert_range_function,C>(
            _container
        );
    }

    template <typename C, typename InputRange>
    inline ::std::deque<typename C::iterator>
        mac_insert_range_function::operator()(
            C& _container
          , typename C::iterator pos
          , InputRange const& r
        ) const
    {
        return this->operator()(
            _container
          , pos
          , ::boost::begin(r)
          , ::boost::end(r)
        );
    }

    template <typename C, typename Itr>
    ::std::deque<typename C::iterator>
        mac_insert_range_function::operator()(
            C& _container
          , typename C::iterator pos
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
        mac_insert_range_function::evaluate(
            C& _container
          , typename C::iterator pos
          , Itr itr
          , Itr itr_end
        )
    {
        _container.insert(itr, itr_end);
    }

    struct ptr_uac_insert_range_function
    {
        template <typename C>
        insert_range_function_proxy<ptr_uac_insert_range_function,C>
            operator[](C& _container) const;

        template <typename C, typename InputRange>
        ::std::deque<typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , InputRange const& r
            ) const;

        template <typename C, typename Itr>
        ::std::deque<typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , Itr itr
              , Itr itr_end
            ) const;

        template <typename C, typename Itr>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , Itr itr
              , Itr itr_end
            );
    };

    template <typename C>
    inline insert_range_function_proxy<ptr_uac_insert_range_function,C>
        ptr_uac_insert_range_function::operator[](C& _container) const
    {
        return insert_range_function_proxy<ptr_uac_insert_range_function,C>(
            _container
        );
    }

    template <typename C, typename InputRange>
    inline ::std::deque<typename C::iterator>
        ptr_uac_insert_range_function::operator()(
            C& _container
          , typename C::iterator pos
          , InputRange const& r
        ) const
    {
        return this->operator()(
            _container
          , pos
          , ::boost::begin(r)
          , ::boost::end(r)
        );
    }

    template <typename C, typename Itr>
    ::std::deque<typename C::iterator>
        ptr_uac_insert_range_function::operator()(
            C& _container
          , typename C::iterator pos
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
        ptr_uac_insert_range_function::evaluate(
            C& _container
          , typename C::iterator pos
          , Itr itr
          , Itr itr_end
        )
    {
        _container.insert(itr, itr_end);
    }

    struct ptr_mac_insert_range_function
    {
        template <typename C>
        insert_range_function_proxy<ptr_mac_insert_range_function,C>
            operator[](C& _container) const;

        template <typename C, typename InputRange>
        ::std::deque<typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , InputRange const& r
            ) const;

        template <typename C, typename Itr>
        ::std::deque<typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , Itr itr
              , Itr itr_end
            ) const;

        template <typename C, typename Itr>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , Itr itr
              , Itr itr_end
            );
    };

    template <typename C>
    inline insert_range_function_proxy<ptr_mac_insert_range_function,C>
        ptr_mac_insert_range_function::operator[](C& _container) const
    {
        return insert_range_function_proxy<ptr_mac_insert_range_function,C>(
            _container
        );
    }

    template <typename C, typename InputRange>
    inline ::std::deque<typename C::iterator>
        ptr_mac_insert_range_function::operator()(
            C& _container
          , typename C::iterator pos
          , InputRange const& r
        ) const
    {
        return this->operator()(
            _container
          , pos
          , ::boost::begin(r)
          , ::boost::end(r)
        );
    }

    template <typename C, typename Itr>
    ::std::deque<typename C::iterator>
        ptr_mac_insert_range_function::operator()(
            C& _container
          , typename C::iterator pos
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
        ptr_mac_insert_range_function::evaluate(
            C& _container
          , typename C::iterator pos
          , Itr itr
          , Itr itr_end
        )
    {
        _container.insert(itr, itr_end);
    }

    struct uns_ac_insert_range_function
    {
        template <typename C>
        insert_range_function_proxy<uns_ac_insert_range_function,C>
            operator[](C& _container) const;

        template <typename C, typename InputRange>
        void
            operator()(
                C& _container
              , typename C::iterator pos
              , InputRange const& r
            ) const;

        template <typename C, typename Itr>
        void
            operator()(
                C& _container
              , typename C::iterator pos
              , Itr itr
              , Itr itr_end
            ) const;

        template <typename C, typename Itr>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , Itr itr
              , Itr itr_end
            );
    };

    template <typename C>
    inline insert_range_function_proxy<uns_ac_insert_range_function,C>
        uns_ac_insert_range_function::operator[](C& _container) const
    {
        return insert_range_function_proxy<uns_ac_insert_range_function,C>(
            _container
        );
    }

    template <typename C, typename InputRange>
    inline void
        uns_ac_insert_range_function::operator()(
            C& _container
          , typename C::iterator pos
          , InputRange const& r
        ) const
    {
        this->operator()(_container, pos, ::boost::begin(r), ::boost::end(r));
    }

    template <typename C, typename Itr>
    inline void
        uns_ac_insert_range_function::operator()(
            C& _container
          , typename C::iterator pos
          , Itr itr
          , Itr itr_end
        ) const
    {
        uns_ac_insert_range_function::evaluate(_container, pos, itr, itr_end);
    }

    template <typename C, typename Itr>
    inline void
        uns_ac_insert_range_function::evaluate(
            C& _container
          , typename C::iterator pos
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

//[reference__insert_range_function_gen
namespace boost {

    template <typename Selector>
    struct insert_range_function_gen
        //<-
      : ::boost::mpl::eval_if<
            is_associative_selector<Selector>
          , ::boost::mpl::eval_if<
                has_stable_iterators_selector<Selector>
              , ::boost::mpl::eval_if<
                    is_ptr_selector<Selector>
                  , ::boost::mpl::if_<
                        is_unique_associative_selector<Selector>
                      , detail::ptr_uac_insert_range_function
                      , detail::ptr_mac_insert_range_function
                    >
                  , ::boost::mpl::if_<
                        is_multiple_associative_selector<Selector>
                      , detail::mac_insert_range_function
                      , detail::uac_insert_range_function
                    >
                >
              , ::boost::mpl::identity<detail::uns_ac_insert_range_function>
            >
          , ::boost::mpl::if_<
                is_random_access_selector<Selector>
              , detail::ras_insert_range_function
              , detail::bis_insert_range_function
            >
        >
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1, insert_range_function_gen, (Selector))
        //->
    };
}  // namespace boost
//]

#include <boost/config.hpp>
#include <boost/container_gen/selectors.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

    template <typename AllocatorSelector>
    struct insert_range_function_gen<slist_selector<AllocatorSelector> >
    {
        typedef detail::fis_insert_range_function type;
    };
}  // namespace boost

#elif !defined BOOST_NO_SLIST

namespace boost {

    template <>
    struct insert_range_function_gen<slist_selector_base>
    {
        typedef detail::fis_insert_range_function type;
    };
}  // namespace boost

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION, BOOST_NO_SLIST

#endif  // BOOST_CONTAINER_GEN_INSERT_RANGE_FUNCTION_GEN_HPP_INCLUDED

