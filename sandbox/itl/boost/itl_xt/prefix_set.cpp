/*----------------------------------------------------------------------------+
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+-----------------------------------------------------------------------------+
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
+----------------------------------------------------------------------------*/
#include <stdafx.h>
#include "prefix_set.h"

using namespace boost::itl;


int prefix_set::compareStrings(int& comSize, const char* s1, const char* s2)
{
    int i=0;
    while(s1[i] != NULL && s2[i] != NULL)
    {
        if(s1[i] < s2[i])
        {
            comSize = i;
            return -1;
        }
        if(s1[i] > s2[i])
        {
            comSize = i;
            return 1;
        }

        // Gleichheit: weitermachen
        i++;
    }

    comSize = i;
    if(s1[i] == NULL || s2[i] == NULL)
        return 0; // Gleichheit
    if (s1[i] != NULL)
        return 1; // s1 ist gr��er 
    else
        return -1; // s2 ist gr��er
    
}


void prefix_set::insert(const std::string& val)
{
    pair<iterator, bool> insertion = m_.insert(val);
    if(!insertion.WAS_SUCCESSFUL)
    {
        if(val.size() < (*insertion.ITERATOR).size())
        {
            m_.erase(insertion.ITERATOR);
            insert(val);
        }
    }
}


