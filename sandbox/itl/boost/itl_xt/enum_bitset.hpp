/*-----------------------------------------------------------------------------+    
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ITL_ENUM_BITSET_HPP_JOFA_021204
#define BOOST_ITL_ENUM_BITSET_HPP_JOFA_021204

#include <bitset>
#include <boost/itl/detail/notate.hpp>
namespace boost{namespace icl
{

    
    template <class EnumT, size_t EnumSize>
    class enum_bitset: public std::bitset<EnumSize>
    {
    public:
        /// Default Ctor
        enum_bitset() : std::bitset<EnumSize>(){}
        
        /// Copy Ctor
        enum_bitset(const enum_bitset& src): std::bitset<EnumSize>(src){}

        /// Construct from unsigned
        enum_bitset(unsigned long val): std::bitset<EnumSize>(val){}

        /** Add the bit 'bit' to the set. This enables shorthand notation
            myBitSet.add(bit_1).add(bit_2). ... .add(bit_n); */
        enum_bitset& add(int bit){this->set(bit); return *this;}
    };

}} // namespace icl boost


#endif // BOOST_ITL_ENUM_BITSET_HPP_JOFA_021204

