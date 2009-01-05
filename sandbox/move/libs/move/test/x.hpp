// Copyright David Abrahams 2004. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef X_DWA2004410_HPP
# define X_DWA2004410_HPP

# include <boost/move/move.hpp>
# include <boost/assert.hpp>
# include "say.hpp"

//
// A sample movable class.
//
class X
{
 public: // "Ordinary" stuff
    X() : resource(++cnt)
    {
        SAY("X() #" << resource);
    }

    X(X const& rhs) : resource(++cnt)
    {
        copy(rhs);
    }

    ~X()
    {
        release();
    }

    // Assign is declared in the move stuff
    
 public: // Move stuff
    // move constructor
    X(boost::move_from<X> rhs)
      : resource(rhs.source.resource)
    {
        BOOST_ASSERT(rhs.source.resource <= cnt); // check for garbage
        SAY("MOVE #" << resource);
        BOOST_ASSERT(move_expected);
        rhs.source.resource = 0;
        BOOST_ASSERT(resource);
    }

    // move assignment
    X& operator=(X rhs)
    {
        BOOST_ASSERT(rhs.resource <= cnt); // check for garbage
        release();
        resource = rhs.resource;
        SAY("MOVE #" << resource);
        BOOST_ASSERT(move_expected);
        rhs.resource = 0;
        BOOST_ASSERT(resource);
        return *this;
    }
    
    static int copies;  // count the number of copies
    static int suboptimal_copies; // count the number of copies that should've been avoidable
    
    static void expect_copy() { copy_expected = true; move_expected = false; }
    static void expect_move() { copy_expected = false; move_expected = true; }
    
    operator boost::move_from<X>() { return *this; }
    
 private: // helper functions
    void release()
    {
        BOOST_ASSERT(resource <= cnt); // check for garbage
        if (!resource)
            SAY("destroy empty");
        else
            SAY("destroy #" << resource);
        resource = 0;
    }

    void copy(X const& rhs)
    {
        BOOST_ASSERT(rhs.resource <= cnt); // check for garbage
        SAY("copy #" << this->resource << " <- #" << rhs.resource);
        if (!copy_expected)
        {
            SAY("***** SUBOPTIMAL COPY ******");
            ++suboptimal_copies;
        }
        else
        {
            move_expected = true; // OK to move now
        }
        ++copies;
    }
    
 private:   // Data members
    int resource;
    
    static int cnt;  // count the number of resources
    static bool copy_expected;
    static bool move_expected;
};

int X::cnt;
int X::copies;
int X::suboptimal_copies;
bool X::copy_expected;
bool X::move_expected;

#endif // X_DWA2004410_HPP
