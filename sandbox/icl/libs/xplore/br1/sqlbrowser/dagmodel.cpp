/****************************************************************************
**
**
****************************************************************************/

#include <QtGui>
#include <QtSql>

#include "dagitem.h"
#include "dagmodel.h"


DagModel::DagModel(const QStringList &headers, const QString &data,
                     QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    foreach (QString header, headers)
        rootData << header;

    rootItem = new DagItem(rootData);
    setupModelData(data.split(QString("\n")), rootItem);
}


DagModel::~DagModel()
{
    delete rootItem;
}


int DagModel::columnCount(const QModelIndex & /* parent */) const
{
    return rootItem->columnCount();
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
    return rootItem;
}


QVariant DagModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

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
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool DagModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    DagItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}


QModelIndex DagModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    DagItem *childItem = getItem(index);
    DagItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}


bool DagModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
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

    bool result = rootItem->setData(section, value);

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
            parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
            for (int column = 0; column < columnData.size(); ++column)
                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
        }

        number++;
    }
}

/*
//JODO Populate a DagModel from an sql-query that provides the DAG as
// (ParentId -> ChildId), ParentName, ChildName, ChildType
void DagModel::fromSql(const QSqlQuery& query)
{
    //JODO create root node
    if(!query.next())
        return;
    else
    {
        //JODO fill root with info
        fromSql(query, rootItem, 0);
    }
}

void DagModel::fromSql(const QSqlQuery& query, DagItem* parent, int depth)
{
    Q_ASSERT(node != NULL);

    if(!query.next())
        return;
    else if(query.value(0).toInt() == parent->nodeId())
    {   //Same node as before. Add a child. Recursing down
        DagItem* newChild = addChild(parent, query); //Fill Data
        //Ok, wont work. Building the DAG and traversing order of
        //the representing order of the db-data must match.
    }
    else
    {   //Next

    }
}
*/

/*
void DagModel::fromSql(const QSqlQuery& query, DagItem* parent, int depth)
{
    Q_ASSERT(node != NULL);

    if(!query.next())
        return;
    else
    {
        create a node
        if(! the new node is terminal)
            addChildren(query, newNode, depth+1);
    }
}
*/


//JOFA Iteration example: The container as String
QString DagModel::toString()const
{
    return nodeToString(rootItem, 0);
}

QString DagModel::nodeToString(DagItem* node, int depth)const
{
    if(node->childCount()==0)
        return tr("(%1)").arg(depth); //Print only structure and depth.
        //return tr("(%1)").arg(node->data(0));
    else
    {
        QString nodeRepr(tr("["));
        for(int idx=0; idx<node->childCount(); idx++)
            nodeRepr += nodeToString(node->child(idx), depth+1);

        nodeRepr += tr("]");
        return nodeRepr;
    }
}


