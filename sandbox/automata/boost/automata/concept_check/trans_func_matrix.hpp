// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_CONCEPT_CHECK_TRANS_FUNC_MATRIX_HPP_INCLUDED
#define BOOST_AUTOMATA_CONCEPT_CHECK_TRANS_FUNC_MATRIX_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/concept/detail/concept_def.hpp>

//[concept__transition_function_matrix
namespace boost { namespace automata {

    BOOST_concept(TransitionFunctionMatrix, (Matrix))
    //]
    //[concept__transition_function_matrix__refinement_of
      : DefaultConstructible<Matrix>
    {
    //]
        //[concept__transition_function_matrix__types_and_variables
     public:
        typedef typename Matrix::value_type
                value_type;
        typedef typename Matrix::size_type
                size_type;

     private:
        BOOST_STATIC_ASSERT((is_same<value_type,size_type>::value));

        Matrix     matrix;
        value_type element;
        size_type  row;
        size_type  column;
        size_type  row_count;
        size_type  column_count;
        //]

        //[concept__transition_function_matrix__expressions
     public:
        BOOST_CONCEPT_USAGE(TransitionFunctionMatrix)
        {
            matrix.resize(row_count, column_count);
            matrix(row, column) = element;
            const_constraints(matrix);
        }

     private:
        void const_constraints(Matrix const& const_matrix)
        {
            element = const_matrix(row, column);
        }
    };
}}  // namespace boost::automata
//]

#include <boost/concept/detail/concept_undef.hpp>

#endif  // BOOST_AUTOMATA_CONCEPT_CHECK_TRANS_FUNC_MATRIX_HPP_INCLUDED

