#include "data/concept/TypeGraph.h"


using namespace dag::db;

bool data::makeTypeGraph(dag::db::TypeGraph& typeGraph, const QSqlDatabase& db)
{
    typedef dag::db::TypeGraph::tKey2Vertex_iterator tKey2Vertex_iterator;

    data::QSqlSelector selector;
    selector.setDatabase(db);
    if(!addEdgeData(selector, typeGraph))
        return false;

    data::KeyBinding_QSqlSelector<tKey2Vertex_iterator> keyBindingSelector;
    keyBindingSelector.setDatabase(db);
    if(!addVertexData(keyBindingSelector, typeGraph))
        return false;

    return true;
}
