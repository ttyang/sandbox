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

    template <typename C>
    inline typename C::iterator
        random_access_splice(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
        )
    {
        if (pos == itr)
        {
            BOOST_ASSERT(&_container == &c);
            return pos;
        }
        else
        {
            typename C::size_type insert_index = (
                ::std::distance(_container.begin(), pos)
            );

            if ((&_container == &c) && (itr < pos))
            {
                --insert_index;
            }

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            typename C::value_type datum(*itr);

            c.erase(itr);
            return _container.insert(_container.begin() + insert_index, datum);
#else
            typename C::value_type datum(::boost::move(*itr));

            c.erase(itr);
            return _container.insert(
                _container.begin() + insert_index
              , ::boost::move(datum)
            );
#endif
        }
    }

    template <typename C>
    inline typename C::iterator
        stable_splice(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
        )
    {
        if (pos == itr)
        {
            BOOST_ASSERT(&_container == &c);
            return pos;
        }
        else
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            typename C::value_type datum(*itr);

            c.erase(itr);
            return _container.insert(pos, datum);
#else
            typename C::value_type datum(::boost::move(*itr));

            c.erase(itr);
            return _container.insert(pos, ::boost::move(datum));
#endif
        }
    }

    template <typename C>
    inline ::std::pair<typename C::iterator,typename C::iterator>
        stable_splice(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
          , typename C::iterator itr_end
        )
    {
        if (_container.empty())
        {
            BOOST_ASSERT(pos == _container.end());
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            _container.insert(
                _container.begin()
              , itr
              , itr_end
            );
#else
            _container.insert(
                _container.begin()
              , ::boost::move_iterator<typename C::iterator>(itr)
              , ::boost::move_iterator<typename C::iterator>(itr_end)
            );
#endif
            return ::std::pair<typename C::iterator,typename C::iterator>(
                _container.begin()
              , _container.end()
            );
        }
        else if ((pos == itr) || (pos == itr_end))
        {
            BOOST_ASSERT(&_container == &c);
            return ::std::pair<typename C::iterator,typename C::iterator>(
                itr
              , itr_end
            );
        }
        else
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            C splice_buf(itr, itr_end);

            c.erase(itr, itr_end);
            return ::std::pair<typename C::iterator,typename C::iterator>(
                _container.insert(
                    pos
                  , splice_buf.begin()
                  , splice_buf.end()
                )
              , pos
            );
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            typedef ::boost::move_iterator<typename C::iterator> MoveItr;

            MoveItr _itr(itr);
            MoveItr _itr_end(itr_end);
            C splice_buf(_itr, _itr_end);

            c.erase(itr, itr_end);
            return ::std::pair<typename C::iterator,typename C::iterator>(
                _container.insert(
                    pos
                  , MoveItr(splice_buf.begin())
                  , MoveItr(splice_buf.end())
                )
              , pos
            );
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        }
    }

    template <typename C>
    inline void
        stable_splice_void_return(
            C& _container
          , typename C::iterator pos
          , C& c
          , typename C::iterator itr
          , typename C::iterator itr_end
        )
    {
        if (_container.empty())
        {
            BOOST_ASSERT(pos == _container.end());
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            _container.insert(
                _container.begin()
              , itr
              , itr_end
            );
#else
            _container.insert(
                _container.begin()
              , ::boost::move_iterator<typename C::iterator>(itr)
              , ::boost::move_iterator<typename C::iterator>(itr_end)
            );
#endif
        }
        else if ((pos == itr) || (pos == itr_end))
        {
            BOOST_ASSERT(&_container == &c);
        }
        else
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            C splice_buf(itr, itr_end);

            c.erase(itr, itr_end);
            _container.insert(
                pos
              , splice_buf.begin()
              , splice_buf.end()
            );
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            typedef ::boost::move_iterator<typename C::iterator> MoveItr;

            MoveItr _itr(itr);
            MoveItr _itr_end(itr_end);
            C splice_buf(_itr, _itr_end);

            c.erase(itr, itr_end);
            _container.insert(
                pos
              , MoveItr(splice_buf.begin())
              , MoveItr(splice_buf.end())
            );
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        }
    }

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
        stable_splice(_container, pos, c, itr);
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
        stable_splice_void_return(_container, pos, c, itr, itr_end);
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
        return random_access_splice(_container, pos, c, itr);
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
        if (_container.empty())
        {
            BOOST_ASSERT(pos == _container.end());
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            _container.insert(
                _container.begin()
              , itr
              , itr_end
            );
#else
            _container.insert(
                _container.begin()
              , ::boost::move_iterator<typename C::iterator>(itr)
              , ::boost::move_iterator<typename C::iterator>(itr_end)
            );
#endif
            return ::std::pair<typename C::iterator,typename C::iterator>(
                _container.begin()
              , _container.end()
            );
        }
        else if ((pos == itr) || (pos == itr_end))
        {
            BOOST_ASSERT(&_container == &c);
            return ::std::pair<typename C::iterator,typename C::iterator>(
                itr
              , itr_end
            );
        }
        else
        {
            typename C::size_type insert_index = (
                ::std::distance(_container.begin(), pos)
            );

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            C splice_buf(itr, itr_end);
            typename C::size_type const range_size = splice_buf.size();

            if ((&_container == &c) && (itr < pos))
            {
                BOOST_ASSERT_MSG(
                    !(pos < itr_end)
                  , "Insertion point lies inside subrange to splice."
                );
                insert_index -= range_size;
            }

            c.erase(itr, itr_end);

            typename C::iterator result_itr = _container.insert(
                _container.begin() + insert_index
              , splice_buf.begin()
              , splice_buf.end()
            );
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            typedef ::boost::move_iterator<typename C::iterator> MoveItr;

            MoveItr _itr(itr);
            MoveItr _itr_end(itr_end);
            C splice_buf(_itr, _itr_end);
            typename C::size_type const range_size = splice_buf.size();

            if ((&_container == &c) && (itr < pos))
            {
                BOOST_ASSERT_MSG(
                    !(pos < itr_end)
                  , "Insertion point lies inside subrange to splice."
                );
                insert_index -= range_size;
            }

            c.erase(itr, itr_end);

            typename C::iterator result_itr = _container.insert(
                _container.begin() + insert_index
              , MoveItr(splice_buf.begin())
              , MoveItr(splice_buf.end())
            );
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            return ::std::pair<typename C::iterator,typename C::iterator>(
                result_itr
              , result_itr + range_size
            );
        }
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
        random_access_splice(_container, pos, c, itr);
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
        if (_container.empty())
        {
            BOOST_ASSERT(pos == _container.end());
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            _container.insert(
                _container.begin()
              , itr
              , itr_end
            );
#else
            _container.insert(
                _container.begin()
              , ::boost::move_iterator<typename C::iterator>(itr)
              , ::boost::move_iterator<typename C::iterator>(itr_end)
            );
#endif
        }
        else if ((pos == itr) || (pos == itr_end))
        {
            BOOST_ASSERT(&_container == &c);
        }
        else
        {
            typename C::size_type insert_index = (
                ::std::distance(_container.begin(), pos)
            );

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            C splice_buf(itr, itr_end);

            if ((&_container == &c) && (itr < pos))
            {
                BOOST_ASSERT_MSG(
                    !(pos < itr_end)
                  , "Insertion point lies inside subrange to splice."
                );
                insert_index -= splice_buf.size();
            }

            c.erase(itr, itr_end);
            _container.insert(
                _container.begin() + insert_index
              , splice_buf.begin()
              , splice_buf.end()
            );
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            typedef ::boost::move_iterator<typename C::iterator> MoveItr;

            MoveItr _itr(itr);
            MoveItr _itr_end(itr_end);
            C splice_buf(_itr, _itr_end);

            if ((&_container == &c) && (itr < pos))
            {
                BOOST_ASSERT_MSG(
                    !(pos < itr_end)
                  , "Insertion point lies inside subrange to splice."
                );
                insert_index -= splice_buf.size();
            }

            c.erase(itr, itr_end);
            _container.insert(
                _container.begin() + insert_index
              , MoveItr(splice_buf.begin())
              , MoveItr(splice_buf.end())
            );
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        }
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
        if (pos != itr)
        {
            typename C::size_type insert_index = (
                ::std::distance(_container.begin(), pos)
            );
            C splice_buf;

            if ((&_container == &c) && (itr < pos))
            {
                --insert_index;
            }

            splice_buf.transfer(splice_buf.begin(), itr, c);
            pos = _container.begin() + insert_index;
            _container.transfer(pos, splice_buf);
        }

        return pos;
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
        typename C::size_type const r_size = ::std::distance(itr, itr_end);

        if ((pos == itr) || (pos == itr_end))
        {
            return ::std::pair<typename C::iterator,typename C::iterator>(
                pos
              , pos + r_size
            );
        }
        else
        {
            typename C::size_type insert_index = (
                ::std::distance(_container.begin(), pos)
            );
            C splice_buf;

            if ((&_container == &c) && (itr < pos))
            {
                BOOST_ASSERT_MSG(
                    !(pos < itr_end)
                  , "Insertion point lies inside subrange to splice."
                );
                insert_index -= r_size;
            }

            splice_buf.transfer(splice_buf.begin(), itr, itr_end, c);
            _container.transfer(_container.begin() + insert_index, splice_buf);
            return ::std::pair<typename C::iterator,typename C::iterator>(
                _container.begin() + insert_index
              , _container.begin() + insert_index + r_size
            );
        }
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
        if (pos != itr)
        {
            typename C::size_type insert_index = (
                ::std::distance(_container.begin(), pos)
            );
            C splice_buf;

            if ((&_container == &c) && (itr < pos))
            {
                --insert_index;
            }

            splice_buf.transfer(splice_buf.begin(), itr, c);
            _container.transfer(_container.begin() + insert_index, splice_buf);
        }
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
        if ((pos != itr) && (pos != itr_end))
        {
            typename C::size_type insert_index = (
                ::std::distance(_container.begin(), pos)
            );
            C splice_buf;

            if ((&_container == &c) && (itr < pos))
            {
                BOOST_ASSERT_MSG(
                    !(pos < itr_end)
                  , "Insertion point lies inside subrange to splice."
                );
                insert_index -= ::std::distance(itr, itr_end);
            }

            splice_buf.transfer(splice_buf.begin(), itr, itr_end, c);
            _container.transfer(_container.begin() + insert_index, splice_buf);
        }
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
        return stable_splice(_container, pos, c, itr);
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
        return stable_splice(_container, pos, c, itr, itr_end);
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
        stable_splice(_container, pos, c, itr);
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
        stable_splice_void_return(_container, pos, c, itr, itr_end);
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
        C splice_buf;

        splice_buf.transfer(splice_buf.begin(), itr, c);
        _container.transfer(pos, splice_buf);
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
        C splice_buf;

        splice_buf.transfer(splice_buf.begin(), itr, itr_end, c);
        _container.transfer(pos, splice_buf);
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

