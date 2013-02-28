#pragma once

#include <boost/utility/enable_if.hpp>
#include "Syncable/Syncable_ModeledBy.h"


template<class Model>
typename boost::enable_if<Syncable_ModeledBy<Model>,
typename Syncable_ModeledBy<Model>::Uuid>::type uuid(Model const& object)
{
    return Syncable_ModeledBy<Model>::uuid(object);
}

template<class Model>
typename boost::enable_if<Syncable_ModeledBy<Model>,
typename Syncable_ModeledBy<Model>::Time>::type time(Model const& object)
{
    return Syncable_ModeledBy<Model>::time(object);
}

template<class Model>
typename boost::enable_if<Syncable_ModeledBy<Model>,
bool>::type less_for_time(Model const& lhs, Model const& rhs)
{
    return time(lhs) < time(rhs);
}

template<class Model>
typename boost::enable_if<Syncable_ModeledBy<Model>,
bool>::type less_for_uuid(Model const& lhs, Model const& rhs)
{
    return uuid(lhs) < uuid(rhs);
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


