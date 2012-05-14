#include "Dag/TypeGraph.h"

#include <QSqlQuery.h>


using namespace dag::db;

void dag::db::getTypeGraph(TypeGraph& tygr, TypeGraphAccessor& accessor)
{
    accessor.prepareGet();

    while(accessor.next())
        tygr.add(accessor.record());
}

//!
void dag::db::getTypeGraph(TypeGraph& tygr, Persistor<TypeEdge>& persitor)
{
    RecIterator it = persitor.prepareGet();

    while(it != persitor.end())
        tygr.add(Creator<Persistor<TypeEdge> >::create(it++));
}

//!
void dag::db::getTypeGraph(TypeGraph& tygr, Persistor<TypeEdge>& persitor)
{
    persitor.prepareGet();

    while(it != persitor.end())
        tygr.add(Creator<Persistor<TypeEdge> >::create(it++));
}


template<class Object, class Access>
class Persistor
{
public:
    iterator prepareGet()
    {
        // Make a query
        return Access::makeQuery(m_resultSet);
    }

    iterator begin()
    {
        return m_resultSet.begin();
    }

    iterator end()
    {
        return m_resultSet.end();
    }

    Object create(iterator it)
    {
        return Access::create(it);
    }

private:
    Access::ResultSet m_resultSet;
};



struct SqlAccess
{
    template<class Object> //Iterierbarere Container
    static inline iterator makeQuery(SqlAccess::Set resultSet)
    {
        tString sql = SqlAccess<Object>::makeSql();
        // Query abschicken.
        // Results
    };

    template<class Object>
    static Object create(iterator it)
    {
        ;
    }
};
