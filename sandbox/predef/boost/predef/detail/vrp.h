/*
Copyright Redshift Software, Inc. 2008-2010
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_DETAIL_VRP_H
#define BOOST_PREDEF_DETAIL_VRP_H

/* Shorthands for the common version number formats used by vendors... */

/* Hexadecimal... */
#define BOOST_PREDEF_VRP_F_F_F(V) BOOST_VERSION_NUMBER((V&0xF00)>>8,(V&0xF0)>>4,(V&0xF))
#define BOOST_PREDEF_VRP_FF_F_F(V) BOOST_VERSION_NUMBER((V&0xFF00)>>8,(V&0xF0)>>4,(V&0xF))
#define BOOST_PREDEF_VRP_F_F_FF(V) BOOST_VERSION_NUMBER((V&0xF000)>>12,(V&0xF00)>>8,(V&0xFF))
#define BOOST_PREDEF_VRP_FF_FF(V) BOOST_VERSION_NUMBER((V&0xFF00)>>8,(V&0xFF),0)
#define BOOST_PREDEF_VRP_F_FF_FFFF(V) BOOST_VERSION_NUMBER((V&0xF000000)>>24,(V&0xFF0000)>>16,(V&0xFFFF))
#define BOOST_PREDEF_VRP_FF_FF_F(V) BOOST_VERSION_NUMBER((V&0xFF000)>>12,(V&0xFF0)>>4,(V&0xF))
#define BOOST_PREDEF_VRP_F_FF_FF_000(V) BOOST_VERSION_NUMBER((V&0xF0000000)>>28,(V&0xFF00000)>>20,(V&0xFF000)>>12)

/* Decimal... */
#define BOOST_PREDEF_VRP_N_N_N(V) BOOST_VERSION_NUMBER((V)/100,(V%100)/10,(V%10))
#define BOOST_PREDEF_VRP_NN_NN_NN(V) BOOST_VERSION_NUMBER((V)/10000,(V%10000)/100,(V%100))
#define BOOST_PREDEF_VRP_NN_NN(V) BOOST_VERSION_NUMBER((V%10000)/100,(V%100),0)
#define BOOST_PREDEF_VRP_N_N_NN(V) BOOST_VERSION_NUMBER((V)/1000,(V%1000)/100,(V%100))
#define BOOST_PREDEF_VRP_N_NN_NN(V) BOOST_VERSION_NUMBER((V)/10000,(V%10000)/100,(V%100))
#define BOOST_PREDEF_VRP_N_N_N_000(V) BOOST_VERSION_NUMBER((V%100000)/100000,(V%10000)/10000,(V%1000)/1000)
#define BOOST_PREDEF_VRP_N_NN_000(V) BOOST_VERSION_NUMBER((V%100000)/100000,(V%10000)/1000,0)
#define BOOST_PREDEF_VRP_NN_NN_00_NN_00(V) BOOST_VERSION_NUMBER((V)/100000000,(V%100000000)/1000000,(V%10000)/100)

#endif
