//=======================================================================
// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CONTAINER_GEN_SPLICE_FUNCTION_GEN_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_SPLICE_FUNCTION_GEN_HPP_INCLUDED

#include <deque>
#include <utility>
#include <boost/config.hpp>
#include <algorithm>
#include <boost/mpl/bool.hpp>
#include <boost/range.hpp>
#include <boost/assert.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/move/move.hpp>
#endif

namespace boost { namespace detail {

    template <typename F, typename C>
    class splice_function_proxy
    {
        C& _container;

     public:
        explicit splice_function_proxy(C& c);

        splice_function_proxy&
            operator()(
                typename C::iterator pos
              , C& c
              , typename C::iterator itr
            );

        splice_function_proxy&
            operator()(
                typename C::iterator pos
              , C& c
              , typename C::iterator itr
              , typename C::iterator itr_end
            );
    };

    template <typename F, typename C>
    splice_function_proxy<F,C>::splice_function_proxy(C& c)
      : _container(c)
    {
    }

    template <typename F, typename C>
    inline splice_function_proxy<F,C>&
        splice_function_proxy<F,C>::operator()(
            typename C::iterator pos
          , C& c
          , typename C::iterator itr
        )
    {
        F::evaluate(this->_container, pos, c, itr);
        return *this;
    }

    template <typename F, typename C>
    inline splice_function_proxy<F,C>&
        splice_function_proxy<F,C>::operator()(
            typename C::iterator pos
          , C& c
          , typename C::iterator itr
          , typename C::iterator itr_end
        )
    {
        F::evaluate(this->_container, pos, c, itr, itr_end);
        return *this;
    }

    struct fis_splice_function
    {
        template <typename C>
        splice_function_proxy<fis_splice_function,C>
            operator[](C& _container) const;

        template <typename C>
        typename C::iterator
            operator()(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
            ) const;

        template <typename C>
        ::std::pair<typename C::iterator,typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
              , typename C::iterator itr_end
            ) const;

        template <typename C>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
            );

        template <typename C>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
              , typename C::iterator itr_end
            );
    };

    template <typename C>
    inline splice_function_proxy<fis_splice_function,C>
        fis_splice_function::operator[](C& _container) const
    {
        return splice_function_proxy<fis_splice_function,C>(_container);
    }

    template <typename C>
    inline typename C::iterator
        fis_splice_function::operator()(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
        ) const
    {
        typename C::iterator result_begin = _container.previous(pos);
        fis_splice_function::evaluate(
            _container
          , pos
          , c
          , itr
        );
        return ++result_begin;
    }

    template <typename C>
    inline ::std::pair<typename C::iterator,typename C::iterator>
        fis_splice_function::operator()(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
          , typename C::iterator itr_end
        ) const
    {
        typename C::iterator result_begin = _container.previous(pos);
        fis_splice_function::evaluate(
            _container
          , pos
          , c
          , itr
          , itr_end
        );
        return ::std::pair<typename C::iterator,typename C::iterator>(
            ++result_begin
          , pos
        );
    }

    template <typename C>
    inline void
        fis_splice_function::evaluate(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
        )
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        _container.insert(pos, *itr);
#else
        _container.insert(pos, ::boost::move(*itr));
#endif
        c.erase(itr);
    }

    template <typename C>
    inline void
        fis_splice_function::evaluate(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
          , typename C::iterator itr_end
        )
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        _container.insert(pos, itr, itr_end);
#else
        _container.insert(
            pos
          , ::boost::move_iterator<typename C::iterator>(itr)
          , ::boost::move_iterator<typename C::iterator>(itr_end)
        );
#endif
        c.erase(itr, itr_end);
    }

    struct ras_splice_function
    {
        template <typename C>
        splice_function_proxy<ras_splice_function,C>
            operator[](C& _container) const;

        template <typename C>
        typename C::iterator
            operator()(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
            ) const;

        template <typename C>
        ::std::pair<typename C::iterator,typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
              , typename C::iterator itr_end
            ) const;

        template <typename C>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
            );

        template <typename C>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
              , typename C::iterator itr_end
            );
    };

    template <typename C>
    inline splice_function_proxy<ras_splice_function,C>
        ras_splice_function::operator[](C& _container) const
    {
        return splice_function_proxy<ras_splice_function,C>(_container);
    }

    template <typename C>
    inline typename C::iterator
        ras_splice_function::operator()(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
        ) const
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typename C::iterator result = _container.insert(pos, *itr);
#else
        typename C::iterator result = _container.insert(
            pos
          , ::boost::move(*itr)
        );
#endif
        c.erase(itr);
        return result;
    }

    template <typename C>
    inline ::std::pair<typename C::iterator,typename C::iterator>
        ras_splice_function::operator()(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
          , typename C::iterator itr_end
        ) const
    {
        typename C::size_type const range_size = (
            ::std::distance(itr, itr_end)
        );
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typename C::iterator result_itr = _container.insert(pos, itr, itr_end);
#else
        typename C::iterator result_itr = _container.insert(
            pos
          , ::boost::move_iterator<typename C::iterator>(itr)
          , ::boost::move_iterator<typename C::iterator>(itr_end)
        );
#endif
        c.erase(itr, itr_end);
        return ::std::pair<typename C::iterator,typename C::iterator>(
            result_itr
          , result_itr + range_size
        );
    }

    template <typename C>
    inline void
        ras_splice_function::evaluate(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
        )
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        _container.insert(pos, *itr);
#else
        _container.insert(pos, ::boost::move(*itr));
#endif
        c.erase(itr);
    }

    template <typename C>
    inline void
        ras_splice_function::evaluate(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
          , typename C::iterator itr_end
        )
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        _container.insert(pos, itr, itr_end);
#else
        _container.insert(
            pos
          , ::boost::move_iterator<typename C::iterator>(itr)
          , ::boost::move_iterator<typename C::iterator>(itr_end)
        );
#endif
        c.erase(itr, itr_end);
    }

    struct ptr_ras_splice_function
    {
        template <typename C>
        splice_function_proxy<ptr_ras_splice_function,C>
            operator[](C& _container) const;

        template <typename C>
        typename C::iterator
            operator()(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
            ) const;

        template <typename C>
        ::std::pair<typename C::iterator,typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
              , typename C::iterator itr_end
            ) const;

        template <typename C>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
            );

        template <typename C>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
              , typename C::iterator itr_end
            );
    };

    template <typename C>
    inline splice_function_proxy<ptr_ras_splice_function,C>
        ptr_ras_splice_function::operator[](C& _container) const
    {
        return splice_function_proxy<ptr_ras_splice_function,C>(_container);
    }

    template <typename C>
    inline typename C::iterator
        ptr_ras_splice_function::operator()(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
        ) const
    {
        typename C::size_type const index = (
            ::std::distance(_container.begin(), pos)
        );
        ptr_ras_splice_function::evaluate(
            _container
          , pos
          , c
          , itr
        );
        return _container.begin() + index;
    }

    template <typename C>
    inline ::std::pair<typename C::iterator,typename C::iterator>
        ptr_ras_splice_function::operator()(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
          , typename C::iterator itr_end
        ) const
    {
        typename C::size_type const begin_index = (
            ::std::distance(_container.begin(), pos)
        );
        typename C::size_type const end_index = (
            begin_index + ::std::distance(itr, itr_end)
        );
        ptr_ras_splice_function::evaluate(
            _container
          , pos
          , c
          , itr
          , itr_end
        );
        return ::std::pair<typename C::iterator,typename C::iterator>(
            _container.begin() + begin_index
          , _container.begin() + end_index
        );
    }

    template <typename C>
    inline void
        ptr_ras_splice_function::evaluate(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
        )
    {
        _container.transfer(pos, itr, itr + 1, c);
    }

    template <typename C>
    inline void
        ptr_ras_splice_function::evaluate(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
          , typename C::iterator itr_end
        )
    {
        _container.transfer(pos, itr, itr_end, c);
    }

    struct bis_splice_function
    {
        template <typename C>
        splice_function_proxy<bis_splice_function,C>
            operator[](C& _container) const;

        template <typename C>
        typename C::iterator
            operator()(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
            ) const;

        template <typename C>
        ::std::pair<typename C::iterator,typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
              , typename C::iterator itr_end
            ) const;

        template <typename C>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
            );

        template <typename C>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
              , typename C::iterator itr_end
            );
    };

    template <typename C>
    inline splice_function_proxy<bis_splice_function,C>
        bis_splice_function::operator[](C& _container) const
    {
        return splice_function_proxy<bis_splice_function,C>(_container);
    }

    template <typename C>
    inline typename C::iterator
        bis_splice_function::operator()(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
        ) const
    {
        if (_container.empty())
        {
            BOOST_ASSERT(pos == _container.end());
            bis_splice_function::evaluate(
                _container
              , pos
              , c
              , itr
            );
            return _container.begin();
        }
        else
        {
            typename C::iterator start = pos;
            --start;
            bis_splice_function::evaluate(
                _container
              , pos
              , c
              , itr
            );
            return ++start;
        }
    }

    template <typename C>
    inline ::std::pair<typename C::iterator,typename C::iterator>
        bis_splice_function::operator()(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
          , typename C::iterator itr_end
        ) const
    {
        if (_container.empty())
        {
            BOOST_ASSERT(pos == _container.end());
            bis_splice_function::evaluate(
                _container
              , pos
              , c
              , itr
              , itr_end
            );
            return ::std::pair<typename C::iterator,typename C::iterator>(
                _container.begin()
              , _container.end()
            );
        }
        else
        {
            typename C::iterator start = pos;
            --start;
            bis_splice_function::evaluate(
                _container
              , pos
              , c
              , itr
              , itr_end
            );
            return ::std::pair<typename C::iterator,typename C::iterator>(
                ++start
              , pos
            );
        }
    }

    template <typename C>
    inline void
        bis_splice_function::evaluate(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
        )
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        _container.insert(pos, *itr);
#else
        _container.insert(pos, ::boost::move(*itr));
#endif
        c.erase(itr);
    }

    template <typename C>
    inline void
        bis_splice_function::evaluate(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
          , typename C::iterator itr_end
        )
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        _container.insert(pos, itr, itr_end);
#else
        _container.insert(
            pos
          , ::boost::move_iterator<typename C::iterator>(itr)
          , ::boost::move_iterator<typename C::iterator>(itr_end)
        );
#endif
        c.erase(itr, itr_end);
    }

    struct ptr_bis_splice_function
    {
        template <typename C>
        splice_function_proxy<ptr_bis_splice_function,C>
            operator[](C& _container) const;

        template <typename C>
        typename C::iterator
            operator()(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
            ) const;

        template <typename C>
        ::std::pair<typename C::iterator,typename C::iterator>
            operator()(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
              , typename C::iterator itr_end
            ) const;

        template <typename C>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
            );

        template <typename C>
        static void
            evaluate(
                C& _container
              , typename C::iterator pos
              , C& c
              , typename C::iterator itr
              , typename C::iterator itr_end
            );
    };

    template <typename C>
    inline splice_function_proxy<ptr_bis_splice_function,C>
        ptr_bis_splice_function::operator[](C& _container) const
    {
        return splice_function_proxy<ptr_bis_splice_function,C>(_container);
    }

    template <typename C>
    inline typename C::iterator
        ptr_bis_splice_function::operator()(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
        ) const
    {
        if (_container.empty())
        {
            BOOST_ASSERT(pos == _container.end());
            ptr_bis_splice_function::evaluate(
                _container
              , pos
              , c
              , itr
            );
            return _container.begin();
        }
        else
        {
            typename C::iterator start = pos;
            --start;
            ptr_bis_splice_function::evaluate(
                _container
              , pos
              , c
              , itr
            );
            return ++start;
        }
    }

    template <typename C>
    inline ::std::pair<typename C::iterator,typename C::iterator>
        ptr_bis_splice_function::operator()(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
          , typename C::iterator itr_end
        ) const
    {
        if (_container.empty())
        {
            BOOST_ASSERT(pos == _container.end());
            ptr_bis_splice_function::evaluate(
                _container
              , pos
              , c
              , itr
              , itr_end
            );
            return ::std::pair<typename C::iterator,typename C::iterator>(
                _container.begin()
              , _container.end()
            );
        }
        else
        {
            typename C::iterator start = pos;
            --start;
            ptr_bis_splice_function::evaluate(
                _container
              , pos
              , c
              , itr
              , itr_end
            );
            return ::std::pair<typename C::iterator,typename C::iterator>(
                ++start
              , pos
            );
        }
    }

    template <typename C>
    inline void
        ptr_bis_splice_function::evaluate(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
        )
    {
        _container.transfer(pos, itr, c);
    }

    template <typename C>
    inline void
        ptr_bis_splice_function::evaluate(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
          , typename C::iterator itr_end
        )
    {
        _container.transfer(pos, itr, itr_end, c);
    }
}}  // namespace boost::detail

#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/container_gen/is_ptr_selector.hpp>
#include <boost/container_gen/is_random_access_selector.hpp>
#include <boost/container_gen/is_reversible_selector.hpp>

//[reference__splice_function_gen
namespace boost {

    template <typename Selector>
    struct splice_function_gen
        //<-
      : ::boost::mpl::eval_if<
            is_ptr_selector<Selector>
          , ::boost::mpl::if_<
                is_random_access_selector<Selector>
              , detail::ptr_ras_splice_function
              , detail::ptr_bis_splice_function
            >
          , ::boost::mpl::eval_if<
                is_random_access_selector<Selector>
              , ::boost::mpl::identity<detail::ras_splice_function>
              , ::boost::mpl::if_<
                    is_reversible_selector<Selector>
                  , detail::bis_splice_function
                  , detail::fis_splice_function
                >
            >
        >
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1, splice_function_gen, (Selector))
        //->
    };

}  // namespace boost
//]

#endif  // BOOST_CONTAINER_GEN_SPLICE_FUNCTION_GEN_HPP_INCLUDED

