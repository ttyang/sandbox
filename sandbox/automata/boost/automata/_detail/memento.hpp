// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA__DETAIL_MEMENTO_HPP_INCLUDED
#define BOOST_AUTOMATA__DETAIL_MEMENTO_HPP_INCLUDED

#include <deque>

namespace boost { namespace automata { namespace _detail {

    template <typename Snapshot>
    class memento
    {
        typedef ::std::deque<Snapshot*> Snapshots;

     public:
        typedef typename Snapshots::size_type size_type;

     private:
        Snapshots _snapshots;
        size_type _limit;

     public:
        explicit memento(size_type const limit);

        memento(memento const& copy);

        memento& operator=(memento const& copy);

        ~memento();

        void clear();

        size_type get_save_limit() const;

        void save(Snapshot const& snapshot);

        bool can_restore() const;

        void restore(Snapshot& snapshot);

     private:
        void _clone(memento const& copy);
    };

    template <typename Snapshot>
    memento<Snapshot>::memento(size_type const limit)
      : _snapshots(), _limit(limit)
    {
    }

    template <typename Snapshot>
    memento<Snapshot>::memento(memento const& copy)
      : _snapshots(), _limit(copy._limit)
    {
        _clone(copy);
    }

    template <typename Snapshot>
    memento<Snapshot>& memento<Snapshot>::operator=(memento const& copy)
    {
        if (this != &copy)
        {
            clear();
            _clone(copy);
            _limit = copy._limit;
        }

        return *this;
    }

    template <typename Snapshot>
    memento<Snapshot>::~memento()
    {
        clear();
    }

    template <typename Snapshot>
    void memento<Snapshot>::clear()
    {
        for (
            typename Snapshots::iterator itr = _snapshots.begin();
            itr != _snapshots.end();
            ++itr
        )
        {
            delete *itr;
        }

        _snapshots.clear();
    }

    template <typename Snapshot>
    void memento<Snapshot>::_clone(memento const& copy)
    {
        typename Snapshots::const_iterator copy_end = copy._snapshots.end();

        for (
            typename Snapshots::const_iterator
                copy_itr = copy._snapshots.begin();
            copy_itr != copy_end;
            ++copy_itr
        )
        {
            _snapshots.push_back(new Snapshot(*(*copy_itr)));
        }
    }

    template <typename Snapshot>
    inline typename memento<Snapshot>::size_type
        memento<Snapshot>::get_save_limit() const
    {
        return _limit;
    }

    template <typename Snapshot>
    void memento<Snapshot>::save(Snapshot const& snapshot)
    {
        switch (_limit)
        {
            case 0:
                _snapshots.push_back(new Snapshot(snapshot));
                break;

            case 1:
                if (_snapshots.empty())
                {
                    _snapshots.push_back(new Snapshot(snapshot));
                }
                else
                {
                    *(_snapshots.back()) = snapshot;
                }
                break;

            default:
                _snapshots.push_back(new Snapshot(snapshot));

                if (_limit < _snapshots.size())
                {
                    delete _snapshots.front();
                    _snapshots.pop_front();
                }
                break;
        }
    }

    template <typename Snapshot>
    inline bool memento<Snapshot>::can_restore() const
    {
        return !_snapshots.empty();
    }

    template <typename Snapshot>
    void memento<Snapshot>::restore(Snapshot& snapshot)
    {
        snapshot = *(_snapshots.back());
        delete _snapshots.back();
        _snapshots.pop_back();
    }
}}}  // namespace boost::automata::_detail

#endif  // BOOST_AUTOMATA__DETAIL_MEMENTO_HPP_INCLUDED

