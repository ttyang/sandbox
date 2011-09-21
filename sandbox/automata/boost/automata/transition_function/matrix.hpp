// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_TRANSITION_FUNCTION_MATRIX_HPP_INCLUDED
#define BOOST_AUTOMATA_TRANSITION_FUNCTION_MATRIX_HPP_INCLUDED

#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/concept_check.hpp>
#include <boost/assert.hpp>

//[reference__matrix_transition_function
namespace boost { namespace automata {

    template <typename StateInputMatrix>
    class matrix_transition_function
    {
        BOOST_CONCEPT_ASSERT((TransitionFunctionMatrix<StateInputMatrix>));

     public:
        typedef tabular_transition_function_tag       tag;
        typedef typename StateInputMatrix::value_type state;
        typedef state                                 result_type;
        typedef state                                 first_argument_type;
        typedef state                                 second_argument_type;

     private:
        // typedef implementation_defined Setter;
        //<-
        class Setter
        {
            matrix_transition_function& _function;
            first_argument_type const   _current_state;
            second_argument_type const  _i;

         public:
            Setter(
                matrix_transition_function& f
              , first_argument_type current_state
              , second_argument_type i
            );

            void operator=(result_type next_state);
        };

        StateInputMatrix _transition_matrix;

        // The TransitionFunctionMatrix concept does not require the presence
        // of size accessors, so the matrix_transition_function class template
        // must keep track of the dimensions itself.
        ::std::size_t _state_count;
        ::std::size_t _input_count;
        //->

     public:
        matrix_transition_function();

        matrix_transition_function(matrix_transition_function const& copy);

        matrix_transition_function&
            operator=(matrix_transition_function const& copy);

        bool recognizes_input(second_argument_type i) const;

        bool recognizes_state(first_argument_type s) const;

        ::std::size_t const& get_state_count() const;

        result_type
            operator()(
                first_argument_type current_state
              , second_argument_type i
            ) const;

        template <typename Iterator>
        void
            make_nontrivial_inputs(
                first_argument_type current_state
              , Iterator itr
            ) const;

        void
            set_transition(
                first_argument_type current_state
              , second_argument_type i
              , result_type next_state
            );

        Setter
            operator()(
                first_argument_type current_state
              , second_argument_type i
            );

        void reset(::std::size_t state_count, ::std::size_t input_count);

        //<-
        template <typename T0, typename T1>
        friend bool
            operator==(
                matrix_transition_function<T0> const& lhs
              , matrix_transition_function<T1> const& rhs
            );
        //->
    };

    //<-
    template <typename StateInputMatrix>
    matrix_transition_function<StateInputMatrix>::matrix_transition_function()
      : _transition_matrix(), _state_count(), _input_count()
    {
    }

    template <typename StateInputMatrix>
    matrix_transition_function<StateInputMatrix>::matrix_transition_function(
        matrix_transition_function const& copy
    ) : _transition_matrix(_state_count, _input_count)
      , _state_count(copy._state_count)
      , _input_count(copy._input_count)
    {
        std::size_t s = _state_count;
        std::size_t i;

        while (s)
        {
            --s;
            i = _input_count;

            while (i)
            {
                --i;
                _transition_matrix(s, i) = copy._transition_matrix(s, i);
            }
        }
    }

    template <typename StateInputMatrix>
    matrix_transition_function<StateInputMatrix>&
        matrix_transition_function<StateInputMatrix>::operator=(
            matrix_transition_function const& copy
        )
    {
        if (this != &copy)
        {
            _state_count = copy._state_count;
            _input_count = copy._input_count;
            _transition_matrix.resize(_state_count, _input_count);

            ::std::size_t s = _state_count;
            ::std::size_t i;

            while (s)
            {
                --s;
                i = _input_count;

                while (i)
                {
                    --i;
                    _transition_matrix(s, i) = copy._transition_matrix(s, i);
                }
            }
        }

        return *this;
    }

    template <typename StateInputMatrix>
    inline bool
        matrix_transition_function<StateInputMatrix>::recognizes_input(
            second_argument_type const i
        ) const
    {
        return i < _input_count;
    }

    template <typename StateInputMatrix>
    inline bool
        matrix_transition_function<StateInputMatrix>::recognizes_state(
            first_argument_type const s
        ) const
    {
        return s < _state_count;
    }

    template <typename StateInputMatrix>
    inline ::std::size_t const&
        matrix_transition_function<StateInputMatrix>::get_state_count() const
    {
        return _state_count;
    }

    template <typename StateInputMatrix>
    inline typename matrix_transition_function<StateInputMatrix>::result_type
        matrix_transition_function<StateInputMatrix>::operator()(
            first_argument_type const current_state
          , second_argument_type const i
        ) const
    {
        BOOST_ASSERT(recognizes_state(current_state));
        BOOST_ASSERT(recognizes_input(i));

        return _transition_matrix(current_state, i);
    }

    template <typename StateInputMatrix>
    template <typename Iterator>
    void
        matrix_transition_function<StateInputMatrix>::make_nontrivial_inputs(
            first_argument_type const current_state
          , Iterator itr
        ) const
    {
        BOOST_ASSERT(recognizes_state(current_state));

        for (::std::size_t i = ::std::size_t(); i < _input_count; ++i)
        {
            if (current_state != _transition_matrix(current_state, i))
            {
                *itr = i;
                ++itr;
            }
        }
    }

    template <typename StateInputMatrix>
    inline void
        matrix_transition_function<StateInputMatrix>::set_transition(
            first_argument_type const current_state
          , second_argument_type const i
          , result_type const next_state
        )
    {
        BOOST_ASSERT(recognizes_state(current_state));
        BOOST_ASSERT(recognizes_input(i));
        BOOST_ASSERT(recognizes_state(next_state));

        _transition_matrix(current_state, i) = next_state;
    }

    template <typename StateInputMatrix>
    matrix_transition_function<StateInputMatrix>::Setter::Setter(
        matrix_transition_function& f
      , first_argument_type const current_state
      , second_argument_type const i
    ) : _function(f), _current_state(current_state), _i(i)
    {
    }

    template <typename StateInputMatrix>
    inline void
        matrix_transition_function<StateInputMatrix>::Setter::operator=(
            result_type const next_state
        )
    {
        _function.set_transition(_current_state, _i, next_state);
    }

    template <typename StateInputMatrix>
    typename matrix_transition_function<StateInputMatrix>::Setter
        matrix_transition_function<StateInputMatrix>::operator()(
            first_argument_type const current_state
          , second_argument_type const i
        )
    {
        return Setter(*this, current_state, i);
    }

    template <typename StateInputMatrix>
    void
        matrix_transition_function<StateInputMatrix>::reset(
            ::std::size_t state_count
          , ::std::size_t input_count
        )
    {
        _state_count = state_count;
        _input_count = input_count;
        _transition_matrix.resize(state_count, input_count);

        while (state_count)
        {
            --state_count;
            input_count = _input_count;

            while (input_count)
            {
                _transition_matrix(state_count, --input_count) = state_count;
            }
        }
    }
    //->

    template <typename StateInputMatrix, typename OtherStateInputMatrix>
    bool
        operator==(
            matrix_transition_function<StateInputMatrix> const& lhs
          , matrix_transition_function<OtherStateInputMatrix> const& rhs
        );

    //<-
    template <typename StateInputMatrix, typename OtherStateInputMatrix>
    bool
        operator==(
            matrix_transition_function<StateInputMatrix> const& lhs
          , matrix_transition_function<OtherStateInputMatrix> const& rhs
        )
    {
        if (
            !(lhs._state_count == rhs._state_count)
         || !(lhs._input_count == rhs._input_count)
        )
        {
            return false;
        }

        ::std::size_t i = lhs._state_count;
        ::std::size_t j;

        while (i)
        {
            --i;
            j = lhs._input_count;

            while (j)
            {
                --j;

                if (
                    lhs._transition_matrix(i, j)
                 != rhs._transition_matrix(i, j)
                )
                {
                    return false;
                }
            }
        }

        return true;
    }
    //->

    template <typename StateInputMatrix, typename OtherStateInputMatrix>
    bool
        operator!=(
            matrix_transition_function<StateInputMatrix> const& lhs
          , matrix_transition_function<OtherStateInputMatrix> const& rhs
        );

    //<-
    template <typename StateInputMatrix, typename OtherStateInputMatrix>
    inline bool
        operator!=(
            matrix_transition_function<StateInputMatrix> const& lhs
          , matrix_transition_function<OtherStateInputMatrix> const& rhs
        )
    {
        return !(lhs == rhs);
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_TRANSITION_FUNCTION_MATRIX_HPP_INCLUDED

