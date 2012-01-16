/****************************************************************************
**
**
****************************************************************************/

/*
    dagitem.cpp

    A container for items of data supplied by a simple dag model.
*/

#include <QStringList>

#include "dagitem.h"

DagItem::DagItem(const QVector<QVariant> &data, DagItem *parent)
{
    parentItem = parent;
    itemData = data;
}

/*JODO First step: Treat the dag like a tree. Introduce multiple parents later.
DagItem::DagItem(const QVector<QVariant> &data, QList<DagItem*>& parents, int parentIdx)
{
    Q_ASSERT(0 < parents.size())
    Q_ASSERT(0 <= parentIdx && parentIdx < parents.size());
    m_parentItems = parents;
    m_selectedParent = parentIdx;
    itemData = data;
}
*/

DagItem::~DagItem()
{
    qDeleteAll(childItems);
}


DagItem *DagItem::child(int number)
{
    return childItems.value(number);
}


int DagItem::childCount() const
{
    return childItems.count();
}


int DagItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<DagItem*>(this));

    return 0;
}


int DagItem::columnCount() const
{
    return itemData.count();
}


QVariant DagItem::data(int column) const
{
    return itemData.value(column);
}


bool DagItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        DagItem *item = new DagItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}

void DagItem::addChild(DagItem* child)
{
    childItems.push_back(child);
}


bool DagItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    foreach (DagItem *child, childItems)
        child->insertColumns(position, columns);

    return true;
}


DagItem *DagItem::parent()
{
    return parentItem;
}


bool DagItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}


bool DagItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.remove(position);

    foreach (DagItem *child, childItems)
        child->removeColumns(position, columns);

    return true;
}


bool DagItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}

