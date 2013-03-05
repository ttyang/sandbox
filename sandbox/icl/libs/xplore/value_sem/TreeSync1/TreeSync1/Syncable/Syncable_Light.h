#pragma once

//#include <boost/utility/enable_if.hpp>
//#include "Syncable/Syncable_ModeledBy.h"
typedef int tUuid;
typedef int tTime;

template<class Model>
tUuid uuid(Model const& object)
{
    return object.uuid();
}

template<class Model>
tTime time(Model const& object)
{
    return object.time();
}

template<class Model>
bool less_for_time(Model const& lhs, Model const& rhs)
{
    return lhs.time() < rhs.time();
}

template<class Model>
bool less_for_uuid(Model const& lhs, Model const& rhs)
{
    return lhs.uuid() < rhs.uuid();
}

template<class Syncable>
struct LessForUuid : std::binary_function<Syncable, Syncable, bool>
{
    bool operator()(Syncable const& lhs, Syncable const& rhs)
    { 
        return less_for_uuid(lhs, rhs); 
    }
};

template<class Syncable>
struct LessForTime : std::binary_function<Syncable, Syncable, bool>
{
    typedef Syncable first_argument_type; 
    typedef Syncable second_argument_type; 

    bool operator()(Syncable const& lhs, Syncable const& rhs)
    { 
        return less_for_time(lhs, rhs); 
    }
};


