//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2010.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/association for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/association/association.hpp>
#include <iostream>

using namespace boost;
using namespace boost::association;

class CBoy;
class CGirl;

struct boy {};
struct girl {};

typedef association::intrinsic<
    tagged<CBoy,    boy>,
    tagged<CGirl,   girl>
> Friends;

class CBoy {
public:
    CBoy() : m_girlfriend(this) {}
    void GiveGirlfriendFlowers();
    void RecvSlap() {
        std::cout << "boy: ouch!" << '\n';
        m_girlfriend.disconnect();
    }
    Friends::end_point<girl>::type m_girlfriend;
};

class CGirl {
public:
    CGirl() :  m_boyfriend(this) {
    }
    void RecvFlowers() {
        std::cout << "girl: thank you for the flowers!" << '\n';
    }
    void SlapBoyfriend() {
        std::cout << "girl: take this!" << '\n';
        if(m_boyfriend.get())
            m_boyfriend->RecvSlap();
    }
    void make_boyfriend() {
        std::cout << "girl: i have a boyfriend!" << '\n';
    }
    void break_boyfriend() {
        std::cout << "girl: we broke up." << '\n';
    }
    Friends::end_point<boy>::type m_boyfriend;
};

void CBoy::GiveGirlfriendFlowers() {
    //~ if(m_girlfriend.get())
        //~ m_girlfriend->RecvFlowers();

    if (Friends::get<girl>(*this))
        Friends::get<girl>(*this)->RecvFlowers();

}

BOOST_ASSOCIATION_DCL(Friends, m_boyfriend, m_girlfriend);


int main()
{
    CBoy Henry;
    CGirl Sally;

    //~ Henry.m_girlfriend.connect(&Sally);
    Friends::connect(Henry,Sally);
    Friends::disconnect<boy>(Henry);
    Friends::connect(Henry,Sally);
    Friends::disconnect<girl>(Sally);
    Friends::connect(Henry,Sally);
    Henry.GiveGirlfriendFlowers();
    //~ Sally.SlapBoyfriend();
    Friends::get<girl>(Henry)->SlapBoyfriend();

    return 0;
}
