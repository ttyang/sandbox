//////////////////////////////////////////////////////////////////////////////
// example::ref_list_of.cpp                                                 //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#include <ostream>
#include <vector>
#include <algorithm>
#include <boost/typeof/typeof.hpp>
#include <boost/assign/auto_size/detail/has_static_size.hpp> // temporary
#include <boost/assign/auto_size/ref_list_of.hpp> // temporary
#include <boost/assign/auto_size/ref_list_of_csv.hpp>
#include <boost/assign/auto_size/ref_rebind_list_of_csv.hpp>

#include <boost/assign/list_of.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <libs/assign/example/ref_list_of.h>

void example_ref_list_of(std::ostream& os)
{
    os << "-> example_ref_listof : ";
    using namespace boost::assign;
    using namespace boost::assign::detail::auto_size;
    typedef std::vector<int> ints_;
    typedef boost::array<int,3> array_;
    array_ array;

    // Since the conversion operator calls begin() and end(), no need to test 
    // these separately

    ints_ ints;
    {    
        // cref_list_of_csv

    	int a=1, b=2, c=3;

		{
			// debugging cref_list_of().range()
			// BUG for K > 1
        	ints_ ints(3);
            ints[0] =  a; ints[1] = b; ints[2] = c;
            typedef tag::no_policy tag;
            typedef boost::mpl::int_<3> K_;
    		BOOST_AUTO(tmp,
            	next_impl<K_::value>(
                	cref_list_of<tag>(a)(b)(3)
            		,boost::begin(ints)
                )
            );
			describe(os,tmp);

            //BOOST_ASSERT(tmp[0] == a);    
            //BOOST_ASSERT(tmp[1] == b);    
            //BOOST_ASSERT(tmp[2] == c);    

		}
/*
        {
    		ints.clear();

            ints = cref_list_of(a)(b)(3);
            BOOST_ASSERT(boost::size(ints) == 3);
            BOOST_ASSERT(ints[0] == a);    
            BOOST_ASSERT(ints[1] == b);    
            BOOST_ASSERT(ints[2] == c);    
            
        }
        {
            array.assign(-1);
            array = cref_list_of_csv(a,b,3);
            BOOST_ASSERT(array[0] == a);    
            BOOST_ASSERT(array[1] == b);    
            BOOST_ASSERT(array[2] == c);    
        }
        {
            BOOST_AUTO(tmp,ref_list_of_csv(a,b,c));
            tmp.assign(0);
            BOOST_ASSERT(a == 0);    
            BOOST_ASSERT(b == 0);    
            BOOST_ASSERT(c == 0);    
        }
*/
    }
/*
    {
        // ref_rebind_list_of_csv
        {
            int a=1, b=2, c=3; 
            
            {
            	int d = 4;
            
            	BOOST_AUTO(
                	max, 
            		*boost::max_element(
            			ref_rebind_list_of_csv(a,b,c)
            		)
                );
                max = d;
                d = 5;
                BOOST_ASSERT(max == 5);
            }
            
            ints.clear();
            BOOST_AUTO(tmp,cref_rebind_list_of_csv(a,b,c));
            {
                ints = tmp; 
                BOOST_ASSERT(ints[0] == a);    
                BOOST_ASSERT(ints[1] == b);    
                BOOST_ASSERT(ints[2] == c);    
            }
            int d = 4;             
            tmp.assign(d);
            d = 5;
            {
                ints = tmp;
                BOOST_ASSERT(ints[0] == d);    
                BOOST_ASSERT(ints[1] == d);    
                BOOST_ASSERT(ints[2] == d);    
            }
        }
    }
*/

    os << "<- " << std::endl;
    
}
