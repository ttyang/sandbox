/****************************************************************************
**
**
****************************************************************************/

#pragma once

//boost
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>


namespace dag
{

//JODO Decoration is only a transient pair. Consider std::pair<shared_ptr<T>, shared_ptr<S> >

//! Decoration is an object that holds information associated to dag objects
//! which can be vertexes or edges. Decoration is not much more than a tuple.
//! We distinguish between
//! \item Object, that holds content associted to vertexes or edges and
//! \item Synth,  that holds sythesized attributes that can be computed on
//! graph traversal.
//!
//! Sythesized attributes like e.g. traversal depth are independent of content.
template<class Object, class Synth>
class Decoration
{
public:
    typedef boost::shared_ptr<Object> tObjectSharedPtr;
    typedef                   Object* tObjectRawPtr;
    typedef             const Object* tObjectConstRawPtr;

    typedef boost::shared_ptr<Synth>  tSynthSharedPtr;
    typedef                   Synth*  tSynthRawPtr;
    typedef             const Synth*  tSynthConstRawPtr;

public:
    Decoration(): m_pObject(), m_pSynth(){}
    Decoration(const Object& object, const Synth& synth);

    tObjectSharedPtr object(){ return m_pObject; }
    tSynthSharedPtr  synth() { return m_pSynth;  }

private:
    tObjectSharedPtr m_pObject;
    tSynthSharedPtr  m_pSynth;

};

template<class Object, class Synth>
Decoration<Object,Synth>::Decoration(const Object& object, const Synth& synth)
    : boost::make_shared<Object>(object)
    , boost::make_shared<Synth>(synth)
{}

} // dag

