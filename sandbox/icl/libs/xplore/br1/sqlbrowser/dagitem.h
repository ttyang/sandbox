/****************************************************************************
**
**
****************************************************************************/

#ifndef DAGITEM_H
#define DAGITEM_H

#include <QList>
#include <QVariant>
#include <QVector>


class DagItem
{
public:
    DagItem(const QVector<QVariant> &data, DagItem *parent = 0);
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

private:
    QList<DagItem*> childItems;
    QVector<QVariant> itemData;
    DagItem *parentItem;
    // int m_selectedParent;
    // QList<DagItem*> m_parentItems;
};

#endif
