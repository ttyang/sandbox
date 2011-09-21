// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA__DETAIL_EXTENSIBLE_MEMENTO_HPP_INCLUDED
#define BOOST_AUTOMATA__DETAIL_EXTENSIBLE_MEMENTO_HPP_INCLUDED

#include <deque>

namespace boost { namespace automata { namespace _detail {

    template <typename Base, typename Observers>
    class extensible_memento
    {
        typedef ::std::deque<Base*> BaseSnapshots;
        typedef ::std::deque<Observers*> ObserverSnapshots;

     public:
        typedef ::std::size_t size_type;

     private:
        BaseSnapshots _base_snapshots;
        ObserverSnapshots _observer_snapshots;
        size_type _limit;

     public:
        explicit extensible_memento(size_type const limit);

        extensible_memento(extensible_memento const& copy);

        extensible_memento& operator=(extensible_memento const& copy);

        ~extensible_memento();

        void clear();

        size_type get_save_limit() const;

        void save(Base const& base, Observers const& observers);

        bool can_restore() const;

        void restore(Base& base, Observers& observers);

     private:
        void _clone(extensible_memento const& copy);
    };

    template <typename Base, typename Observers>
    extensible_memento<Base,Observers>::extensible_memento(
        size_type const limit
    ) : _base_snapshots(), _observer_snapshots(), _limit(limit)
    {
    }

    template <typename Base, typename Observers>
    extensible_memento<Base,Observers>::extensible_memento(
        extensible_memento const& copy
    ) : _base_snapshots(), _observer_snapshots(), _limit(copy._limit)
    {
        _clone(copy);
    }

    template <typename Base, typename Observers>
    extensible_memento<Base,Observers>&
        extensible_memento<Base,Observers>::operator=(
            extensible_memento const& copy
        )
    {
        if (this != &copy)
        {
            clear();
            _clone(copy);
            _limit = copy._limit;
        }

        return *this;
    }

    template <typename Base, typename Observers>
    extensible_memento<Base,Observers>::~extensible_memento()
    {
        clear();
    }

    template <typename Base, typename Observers>
    void extensible_memento<Base,Observers>::clear()
    {
        for (
            typename ObserverSnapshots::iterator
                itr = _observer_snapshots.begin();
            itr != _observer_snapshots.end();
            ++itr
        )
        {
            delete *itr;
        }

        _observer_snapshots.clear();

        for (
            typename BaseSnapshots::iterator itr = _base_snapshots.begin();
            itr != _base_snapshots.end();
            ++itr
        )
        {
            delete *itr;
        }

        _base_snapshots.clear();
    }

    template <typename Base, typename Observers>
    void
        extensible_memento<Base,Observers>::_clone(
            extensible_memento const& copy
        )
    {
        typename BaseSnapshots::const_iterator
            base_end = copy._base_snapshots.end();

        for (
            typename BaseSnapshots::const_iterator
                base_itr = copy._base_snapshots.begin();
            base_itr != base_end;
            ++base_itr
        )
        {
            _base_snapshots.push_back(new Base(*(*base_itr)));
        }

        typename ObserverSnapshots::const_iterator
            observer_end = copy._observer_snapshots.end();

        for (
            typename ObserverSnapshots::const_iterator
                observer_itr = copy._observer_snapshots.begin();
            observer_itr != observer_end;
            ++observer_itr
        )
        {
            _observer_snapshots.push_back(new Observers(*(*observer_itr)));
        }
    }

    template <typename Base, typename Observers>
    inline typename extensible_memento<Base,Observers>::size_type
        extensible_memento<Base,Observers>::get_save_limit() const
    {
        return _limit;
    }

    template <typename Base, typename Observers>
    inline void
        extensible_memento<Base,Observers>::save(
            Base const& base
          , Observers const& observers
        )
    {
        switch (_limit)
        {
            case 0:
                _base_snapshots.push_back(new Base(base));
                _observer_snapshots.push_back(new Observers(observers));
                break;

            case 1:
                if (_base_snapshots.empty())
                {
                    _base_snapshots.push_back(new Base(base));
                    _observer_snapshots.push_back(new Observers(observers));
                }
                else
                {
                    *(_base_snapshots.back()) = base;
                    *(_observer_snapshots.back()) = observers;
                }

                break;

            default:
                _base_snapshots.push_back(new Base(base));
                _observer_snapshots.push_back(new Observers(observers));

                if (_limit < _base_snapshots.size())
                {
                    delete _base_snapshots.front();
                    _base_snapshots.pop_front();
                    delete _observer_snapshots.front();
                    _observer_snapshots.pop_front();
                }

                break;
        }
    }

    template <typename Base, typename Observers>
    inline bool extensible_memento<Base,Observers>::can_restore() const
    {
        return !_base_snapshots.empty();
    }

    template <typename Base, typename Observers>
    inline void
        extensible_memento<Base,Observers>::restore(
            Base& base
          , Observers& observers
        )
    {
        base = *(_base_snapshots.back());
        observers = *(_observer_snapshots.back());
        delete _base_snapshots.front();
        _base_snapshots.pop_front();
        delete _observer_snapshots.front();
        _observer_snapshots.pop_front();
    }
}}}  // namespace boost::automata::_detail

#endif  // BOOST_AUTOMATA__DETAIL_EXTENSIBLE_MEMENTO_HPP_INCLUDED

