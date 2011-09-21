// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_TRANSITION_FUNCTION_TOTALISTIC_BOOLEAN_CELL_HPP_INC
#define BOOST_AUTOMATA_TRANSITION_FUNCTION_TOTALISTIC_BOOLEAN_CELL_HPP_INC

#include <boost/mpl/apply_wrap.hpp>
#include <boost/range/algorithm/count.hpp>
#include <boost/detail/metafunction/class/associative_container_gen.hpp>
#include <boost/automata/tags/transition_function.hpp>

//[reference__totalistic_boolean_cell_transition_function
namespace boost { namespace automata {

    template <typename AssociativeContainerSelector = setS>
    class totalistic_boolean_cell_transition_function
    {
        //typedef implementation_defined Inserter;
        //<-
        typedef typename ::boost::mpl::apply_wrap1<
                    ::boost::detail::associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , ::std::size_t
                >::type
                CountSet;

        class Inserter
        {
            CountSet& _set;

         public:
            explicit Inserter(CountSet& set);

            Inserter& operator,(::std::size_t count);
        };
        //->

     public:
        typedef transition_function_tag tag;
        typedef bool state;
        typedef state result_type;

        //<-
     private:
        CountSet _birth_set;
        CountSet _stay_alive_set;

     public:
        //->
        totalistic_boolean_cell_transition_function();

        totalistic_boolean_cell_transition_function(
            totalistic_boolean_cell_transition_function const& copy
        );

        totalistic_boolean_cell_transition_function&
            operator=(totalistic_boolean_cell_transition_function const& copy);

        template <typename Input>
        result_type operator()(state current_state, Input const& i) const;

        Inserter operator|=(::std::size_t count);

        Inserter operator&=(::std::size_t count);

        void reset();
    };

    //<-
    template <typename AssociativeContainerSelector>
    totalistic_boolean_cell_transition_function<
        AssociativeContainerSelector
    >::Inserter::Inserter(CountSet& set) : _set(set)
    {
    }

    template <typename AssociativeContainerSelector>
    inline typename totalistic_boolean_cell_transition_function<
        AssociativeContainerSelector
    >::Inserter&
        totalistic_boolean_cell_transition_function<
            AssociativeContainerSelector
        >::Inserter::operator,(::std::size_t count)
    {
        _set.insert(count);
        return *this;
    }

    template <typename AssociativeContainerSelector>
    totalistic_boolean_cell_transition_function<
        AssociativeContainerSelector
    >::totalistic_boolean_cell_transition_function()
      : _birth_set(), _stay_alive_set()
    {
    }

    template <typename AssociativeContainerSelector>
    totalistic_boolean_cell_transition_function<
        AssociativeContainerSelector
    >::totalistic_boolean_cell_transition_function(
        totalistic_boolean_cell_transition_function const& copy
    ) : _birth_set(copy._birth_set), _stay_alive_set(copy._stay_alive_set)
    {
    }

    template <typename AssociativeContainerSelector>
    inline totalistic_boolean_cell_transition_function<
        AssociativeContainerSelector
    >&
        totalistic_boolean_cell_transition_function<
            AssociativeContainerSelector
        >::operator=(totalistic_boolean_cell_transition_function const& copy)
    {
        if (this != &copy)
        {
            _birth_set = copy._birth_set;
            _stay_alive_set = copy._stay_alive_set;
        }

        return *this;
    }

    template <typename AssociativeContainerSelector>
    template <typename Input>
    inline typename totalistic_boolean_cell_transition_function<
        AssociativeContainerSelector
    >::result_type
        totalistic_boolean_cell_transition_function<
            AssociativeContainerSelector
        >::operator()(state current_state, Input const& i) const
    {
        return (
            current_state
          ? (
                _stay_alive_set.find(::boost::range::count(i, true))
             != _stay_alive_set.end()
            )
          : (
                _birth_set.find(::boost::range::count(i, true))
             != _birth_set.end()
            )
        );
    }

    template <typename AssociativeContainerSelector>
    inline typename totalistic_boolean_cell_transition_function<
        AssociativeContainerSelector
    >::Inserter
        totalistic_boolean_cell_transition_function<
            AssociativeContainerSelector
        >::operator|=(::std::size_t count)
    {
        _birth_set.insert(count);
        return Inserter(_birth_set);
    }

    template <typename AssociativeContainerSelector>
    inline typename totalistic_boolean_cell_transition_function<
        AssociativeContainerSelector
    >::Inserter
        totalistic_boolean_cell_transition_function<
            AssociativeContainerSelector
        >::operator&=(::std::size_t count)
    {
        _stay_alive_set.insert(count);
        return Inserter(_stay_alive_set);
    }

    template <typename AssociativeContainerSelector>
    void
        totalistic_boolean_cell_transition_function<
            AssociativeContainerSelector
        >::reset()
    {
        _birth_set.clear();
        _stay_alive_set.clear();
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_TRANSITION_FUNCTION_TOTALISTIC_BOOLEAN_CELL_HPP_INC

