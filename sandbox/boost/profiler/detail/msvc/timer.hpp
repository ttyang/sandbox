// ----------------------------------------------------------------------------
// Copyright (C) 2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROFILER_DETAIL_MSVC_TIMER_HPP_INCLUDED
#define BOOST_PROFILER_DETAIL_MSVC_TIMER_HPP_INCLUDED

#ifndef _WINDOWS_
    #define WIN32_LEAN_AND_MEAN
    #define VC_EXTRALEAN
    #define NOGDICAPMASKS     
    #define NOVIRTUALKEYCODES 
    #define NOWINMESSAGES     
    #define NOWINSTYLES       
    #define NOSYSMETRICS      
    #define NOMENUS           
    #define NOICONS           
    #define NOKEYSTATES       
    #define NOSYSCOMMANDS     
    #define NORASTEROPS       
    #define NOSHOWWINDOW      
    #define OEMRESOURCE       
    #define NOATOM            
    #define NOCLIPBOARD       
    #define NOCOLOR           
    #define NOCTLMGR          
    #define NODRAWTEXT        
    #define NOGDI             
    #define NOKERNEL          
    #define NOUSER            
    #define NONLS             
    #define NOMB              
    #define NOMEMMGR          
    #define NOMETAFILE        
    #undef NOMINMAX         // for mingw
    #define NOMINMAX          
    #define NOMSG             
    #define NOOPENFILE        
    #define NOSCROLL          
    #define NOSERVICE         
    #define NOSOUND           
    #define NOTEXTMETRIC      
    #define NOWH              
    #define NOWINOFFSETS      
    #define NOCOMM            
    #define NOKANJI           
    #define NOHELP            
    #define NOPROFILER        
    #define NODEFERWINDOWPOS  
    #define NOMCX             
    #include <windows.h>
#endif

namespace boost { namespace profiler { namespace detail 
{

    typedef __int64 tick_t;
    
    inline tick_t ticks()
    {
        __asm __emit 0fh __asm __emit 031h   // RDTSC
    }

    inline tick_t ticks_per_second()
    {
        static tick_t result;
        if (result == 0)
        {
            LARGE_INTEGER counter1, counter2, frequency;
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&counter1);
            tick_t ticks1 = ticks();
            __int64 time1 = counter1.QuadPart;
            Sleep(100);
            QueryPerformanceCounter(&counter2);
            tick_t ticks2 = ticks();
            __int64 time2 = counter2.QuadPart;
            result = (ticks2 - ticks1) * frequency.QuadPart / (time2 - time1);
        }
        return result;
    }

} } }

#endif

