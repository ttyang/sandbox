///////////////////////////////////////////////////////////////////////////////
// statistics::kernel::joint::crtp.hpp                                       //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
/////////////////////////////////////////////////////////////////////////////// 
#ifndef BOOST_STATISTICS_KERNEL_JOINT_CRTP_H_ER_2009
#define BOOST_STATISTICS_KERNEL_JOINT_CRTP_H_ER_2009

namespace boost{
namespace statistics{
namespace kernel{
namespace joint{

    // This has no purpose other signifying that the derived class is 
    // a kernel, and it is currently not in use, but this may change. 
    template<typename D> struct crtp{};

}
}
}
}

#endif
