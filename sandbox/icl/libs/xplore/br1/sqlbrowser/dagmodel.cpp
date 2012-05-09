/****************************************************************************
**
**
****************************************************************************/

#include <QtGui>
#include <QtSql>

#include "dagitem.h"
#include "dagmodel.h"
#include "StringVisitor.h"
#include "CreatorVisitor.h"

using namespace boost;

DagModel::DagModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    m_rootItem = createDagItem();
}


/* JODO
DagModel::DagModel(const QStringList &headers, const QString &data,
                     QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    foreach (QString header, headers)
        rootData << header;

    m_rootItem = new DagItem(rootData);
    setupModelData(data.split(QString("\n")), m_rootItem);
}
*/

DagItem* DagModel::createDagItem()
{
    QVector<QVariant> rootData;
    rootData.resize(dag::node::sizeOf_node);
    rootData[dag::node::posId] = QVariant(0);
    rootData[dag::node::posName] = QVariant("NIL");
    return new DagItem(rootData);
}



DagModel::~DagModel()
{
    delete m_rootItem;
}


int DagModel::columnCount(const QModelIndex & /* parent */) const
{
    return m_rootItem->columnCount();
}


QVariant DagModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    DagItem *item = getItem(index);

    return item->data(index.column());
}


Qt::ItemFlags DagModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


DagItem *DagModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        DagItem *item = static_cast<DagItem*>(index.internalPointer());
        if (item) return item;
    }
    return m_rootItem;
}


QVariant DagModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_rootItem->data(section);

    return QVariant();
}


QModelIndex DagModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    DagItem *parentItem = getItem(parent);

    DagItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

bool DagModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = m_rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

void DagModel::insertVertex(QVector<QVariant>& edgeData, const QModelIndex& index)
{
    // Insert the vretex (via edge) into the Dag
    dagInsertVertex(edgeData, index);
    // Insert the vertex into the DagModel
    modelInsertVertex(edgeData, index);
}

void DagModel::dagInsertVertex(QVector<QVariant>& edgeData, const QModelIndex& index)
{
    int source = edgeData[m_parentId].toInt();
    int target = edgeData[m_childId].toInt();
    if(!(source==0 && target==0))
    {
        boost::add_edge(source, target, m_dag);
        m_aVertexAttributes[source] = VertexAttributes(edgeData[m_parentName].toString(), source);
        m_aVertexAttributes[target] = VertexAttributes(edgeData[m_childName].toString(),  target);
    }
}

void DagModel::modelInsertVertex(QVector<QVariant>& edgeData, const QModelIndex& index)
{
    // Create a new vertex or DagItem and append it a the node inicated by 'index'
    // PRE: index is valid and points to the parent node of insertion.

    //fill node data. The target node is 'new'
    fillDummyData(edgeData, index.data().toInt());

    DagItem* parentNode = item(index);
    Q_ASSERT(parentNode != 0);

    tVariVector childData(dag::node::sizeOf_node);
    childData[dag::node::posId]         = edgeData[dag::edge::posChildId];
    childData[dag::node::posParentId]   = edgeData[dag::edge::posParentId];
    childData[dag::node::posName]       = edgeData[dag::edge::posChildName];
    childData[dag::node::posParentName] = edgeData[dag::edge::posParentName];
    DagItem* childNode = new DagItem(childData, parentNode);

    parentNode->addChild(childNode);
}

bool DagModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    DagItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, m_rootItem->columnCount());
    endInsertRows();

    return success;
}


QModelIndex DagModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    DagItem *childItem = getItem(index);
    DagItem *parentItem = childItem->parent();

    if (parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}


bool DagModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = m_rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (m_rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool DagModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    DagItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}


int DagModel::rowCount(const QModelIndex &parent) const
{
    DagItem *parentItem = getItem(parent);

    return parentItem->childCount();
}


bool DagModel::setData(const QModelIndex &index, const QVariant &value,
                        int role)
{
    if (role != Qt::EditRole)
        return false;

    DagItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

bool DagModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = m_rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

void DagModel::setupModelData(const QStringList &lines, DagItem *parent)
{
    QList<DagItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].mid(position, 1) != " ")
                break;
            position++;
        }

        QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
            QVector<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            DagItem *parent = parents.last();
            parent->insertChildren(parent->childCount(), 1, m_rootItem->columnCount());
            for (int column = 0; column < columnData.size(); ++column)
                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
        }

        number++;
    }
}

QString DagModel::setupDag()
{
    QString dagAsString; //JODO CL

    boost::depth_first_search(
        m_dag
      , boost::visitor(make_dfs_visitor(boost::make_list(
                                              CreatorVisitor::OnDiscoverVertex(m_rootItem, &dagAsString, m_aVertexAttributes)
                                            , CreatorVisitor::OnExamineEdge   (m_rootItem, &dagAsString, m_aVertexAttributes)
                                            , CreatorVisitor::OnFinishVertex  (m_rootItem, &dagAsString, m_aVertexAttributes)
                                            )
                      ))
    );

    // Here I can change the headers by altering some attributes for root.
    m_rootItem->setData(dag::node::posName, QVariant("Name"));
    //JODO It is not possible to do this:
    //m_rootItem->setData(dag::node::posId,   QVariant("Id"));
    //JODO So: Provide headers as strings before this point.

    m_rootItem->setData(dag::node::posParentId, QVariant(0));
    m_rootItem->setData(dag::node::posParentName, QVariant("Parent"));

    return dagAsString;
}

void DagModel::getEdges(QSqlQuery& query)
{
    while(query.next())
    {
        //create an edge
        QVector<QVariant> data;
        //fill node
        fillData(data, query);
        m_edges.append(data);
    }
}



//JODO Populate a DagModel from an sql-query that provides the DAG as
// (ParentId -> ChildId), ParentName, ChildName, ChildType
void DagModel::fromSql(QSqlQuery& query)
{
    if(!query.next())
        return;
    else
    {
        //We skip the first record and its NIL information.
        fromSql(query, m_rootItem, 0);
    }
}

void DagModel::makeDag()
{
    m_dag.clear();

    m_aVertexAttributes = get(Dag::vertex_attr_tag(), m_dag);

    for(tEdgeList::iterator iter = m_edges.begin(); iter != m_edges.end(); iter++)
    {
        int source = (*iter)[m_parentId].toInt();
        int target = (*iter)[m_childId].toInt();
        if(!(source==0 && target==0))
        {
            boost::add_edge(source, target, m_dag);
            m_aVertexAttributes[source] = VertexAttributes((*iter)[m_parentName].toString(), source);
            m_aVertexAttributes[target] = VertexAttributes((*iter)[m_childName].toString(),  target);
        }
    }
}

QString DagModel::dagToString()
{
    QString dagAsString;

    boost::depth_first_search(
        m_dag
      , boost::visitor(make_dfs_visitor(boost::make_list(
                                              StringVisitor::OnDiscoverVertex(&dagAsString, m_aVertexAttributes)
                                            , StringVisitor::OnExamineEdge(&dagAsString, m_aVertexAttributes, m_parentMap)
                                            , StringVisitor::OnFinishVertex(&dagAsString, m_aVertexAttributes)
                                            //, boost::record_predecessors(parentMap.begin(), boost::on_tree_edge())
                                            )
                      ))
    );

    return dagAsString;
}



// The result indicates: False: No more data. True: Data available.
DagItem* DagModel::fromSql(QSqlQuery& query, DagItem* parent, int depth)
{
    // The function assumes, that the dags "expanded tree" exists in
    // pre-order (the order, that is finally presented). This makes the
    // traversal specifically simple.
    Q_ASSERT(parent != NULL);

    // Get the next record
    if(!query.next())
        return NULL;
    else
    {
        //create a node
        QVector<QVariant> data;
        //fill node
        fillData(data, query);

        DagItem* curNode = (depth==0) ? new DagItem(data, 0) //curNode==m_rootItem
                                      : new DagItem(data, parent);
        if(depth == 0)
            m_rootItem = curNode;

        //if the new node is not a leaf, create children.
        if(!curNode->isLeaf(m_typeId))
        {
            //While records available: Read children.
            DagItem* curChild;
            while((curChild = fromSql(query, curNode, depth+1)) != NULL)
            {
                curNode->addChild(curChild);
            }
        }

        return curNode;
    }
}


//JOFA Iteration example: The container as String
QString DagModel::toString()const
{
    return nodeToString(m_rootItem, 0);
}

QString DagModel::nodeToString(DagItem* node, int depth)const
{
    if(node->childCount()==0)
        return tr("%1(%2)\n").arg(indentation(depth), depth); //Print only structure and depth.
    else
    {
        QString indent = indentation(depth);

        QVariant childNameV = node->data(m_childName);
        QString  childName  = childNameV.toString();
        QString  nodeRepr( tr("%1[%2\n").arg(indentation(depth), childName) );

        for(int idx=0; idx<node->childCount(); idx++)
            nodeRepr += nodeToString(node->child(idx), depth+1);

        nodeRepr += tr("%1]\n").arg(indentation(depth));
        return nodeRepr;
    }
}


void DagModel::fillData(QVector<QVariant>& data, QSqlQuery& query)
{
    QSqlRecord rec = query.record();
    data.resize(rec.count());

    m_parentId     = rec.indexOf("ParentId");
    m_childId      = rec.indexOf("ChildId");
    m_typeId       = rec.indexOf("TypeId");
    m_parentName   = rec.indexOf("Parent");
    m_childName    = rec.indexOf("Child");
    m_childType    = rec.indexOf("Type");

    data[m_parentId]   = query.value(m_parentId);
    data[m_childId]    = query.value(m_childId);
    data[m_typeId]     = query.value(m_typeId);
    data[m_parentName] = query.value(m_parentName);
    data[m_childName]  = query.value(m_childName);
    data[m_childType]  = query.value(m_childType);
}

void DagModel::fillDummyData(QVector<QVariant>& data, int nodeId)
{
    data[m_parentId]   = QVariant(nodeId);
    data[m_childId]    = QVariant(num_edges());
    data[m_typeId]     = QVariant(1);
    data[m_parentName] = QVariant("Parent Name");
    data[m_childName]  = QVariant("Child Name");
    data[m_childType]  = QVariant(2);
}

