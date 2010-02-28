//////////////////////////////////////////////////////////////////////////////
// assign::ref_rebind_list_of_csv.hpp                                       //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_AUTO_SIZE_REF_REBIND_LIST_OF_CSV_ER_2010_HPP
#define BOOST_ASSIGN_AUTO_SIZE_REF_REBIND_LIST_OF_CSV_ER_2010_HPP

// Usage:
// cref_rebind_list_of_csv(a,b,c);
//
// See ref_list_of.hpp

#define BOOST_ASSIGN_CSV_ref boost::assign::detail::auto_size::ref_rebind
#include <boost/assign/auto_size/detail/csv.hpp>
BOOST_ASSIGN_CSV(ref_rebind_list_of_csv)
#undef BOOST_ASSIGN_CSV_ref

#endif
