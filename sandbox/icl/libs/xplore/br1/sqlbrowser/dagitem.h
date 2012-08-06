/****************************************************************************
**
**
****************************************************************************/

#ifndef DAGITEM_H
#define DAGITEM_H

#include <boost/shared_ptr.hpp>
#include <QList>
#include <QVariant>
#include <QVector>

#include "util/SharedPtr.h"


typedef QVector<QVariant> tVariVector;
typedef boost::shared_ptr<tVariVector> tSharedData;


class DagItem
{
public:

    static const int NodeType_Object = 2;

    DagItem(const tSharedData& data, DagItem *parent = 0);
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
    bool isLeaf(int TypeId)const { return (*itemData)[TypeId] == NodeType_Object; }
    DagItem* clone(DagItem* parent);

    tSharedData data()const { return itemData; }

    QString toString(); //DBG CL

private:
    QString toString(int depth); //DBG CL


private:
    QList<DagItem*> childItems;
    tSharedData     itemData;
    DagItem         *parentItem;
};

#endif
