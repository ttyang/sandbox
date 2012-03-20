/****************************************************************************
**
**
****************************************************************************/

#ifndef DAGITEM_H
#define DAGITEM_H

#include <QList>
#include <QVariant>
#include <QVector>


typedef QVector<QVariant> tVariVector;

class DagItem
{
public:

    static const int NodeType_Object = 2;

    DagItem(const tVariVector &data, DagItem *parent = 0);
    ~DagItem();

    DagItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    DagItem *parent();
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);

    void addChild(DagItem* child);
    bool isLeaf(int TypeId)const { return itemData[TypeId] == NodeType_Object; }

private:
    QList<DagItem*> childItems;
    tVariVector     itemData;
    DagItem         *parentItem;
};

#endif
