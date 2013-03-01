#pragma once


//-----------------------------------------------------------------
// Concept Syncable something that is universally identifiable
// and has a timestamp, so it can be synchronized
template<class ModelT> struct Syncable_ModeledBy
{
    static const bool value = false;
    typedef ModelT Model;
    typedef typename Model::Uuid Uuid;
    typedef typename Model::Time Time;
    static Uuid uuid(Model const&);
    static Time time(Model const&);
};

