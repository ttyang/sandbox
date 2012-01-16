/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "exttableview.h"
#include "browser.h"
#include "qsqlconnectiondialog.h"
#include "dagmodel.h"

#include <QtGui>
#include <QtSql>

Browser::Browser(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    ext_table->addAction(insertRowAction);
    ext_table->addAction(deleteRowAction);

    ext_tree->addAction(insertRowAction);
    ext_tree->addAction(deleteRowAction);

    if (QSqlDatabase::drivers().isEmpty())
        QMessageBox::information(this, tr("No database drivers found"),
                                 tr("This demo requires at least one Qt database driver. "
                                    "Please check the documentation how to build the "
                                    "Qt SQL plugins."));

    emit statusMessage(tr("Ready."));
}

Browser::~Browser()
{
}

void Browser::exec()
{
    QSqlQueryModel *model = new QSqlQueryModel(ext_table);


    QSqlQuery curQuery = QSqlQuery(sqlEdit->toPlainText(), connectionWidget->currentDatabase());

    QStringList headers;
    headers << tr("Title") << tr("Description");
    DagModel* dagmo = new DagModel(headers);

    QSqlQuery xpQuery = QSqlQuery("", connectionWidget->currentDatabase());
    QString dbg_query = QString(sqlEdit->toPlainText());
    xpQuery.exec(sqlEdit->toPlainText());
    int dbg_size = xpQuery.size();
    dagmo->fromSql(xpQuery);

    model->setQuery(curQuery);
    //REV? model->setQuery(QSqlQuery(sqlEdit->toPlainText(), connectionWidget->currentDatabase()));

    ext_table->setModel(model);
    ext_tree->setModel(model);//JOFA

    //JOFA additions ----------------------------------------------------------
    ext_table->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);

    //ext_table->setSortingEnabled(true);
    ext_table->setAlternatingRowColors(true);
    ext_table->resizeColumnsToContents();
    //JOFA additions ----------------------------------------------------------


    if (model->lastError().type() != QSqlError::NoError)
        emit statusMessage(model->lastError().text());
    else if (model->query().isSelect())
        emit statusMessage(tr("Query OK."));
    else
        emit statusMessage(tr("Query OK, number of affected rows: %1").arg(
                           model->query().numRowsAffected()));

    updateActions();
}

QSqlError Browser::addConnection(const QString &driver, const QString &dbName, const QString &host,
                            const QString &user, const QString &passwd, int port)
{
    static int cCount = 0;

    QSqlError err;
    QSqlDatabase db = QSqlDatabase::addDatabase(driver, QString("Browser%1").arg(++cCount));
    db.setDatabaseName(dbName);
    db.setHostName(host);
    db.setPort(port);
    if (!db.open(user, passwd)) {
        err = db.lastError();
        db = QSqlDatabase();
        QSqlDatabase::removeDatabase(QString("Browser%1").arg(cCount));
    }
    connectionWidget->refresh();

    return err;
}

void Browser::addConnection()
{
    QSqlConnectionDialog dialog(this);
    if (dialog.exec() != QDialog::Accepted)
        return;

    if (dialog.useInMemoryDatabase()) {
        QSqlDatabase::database("in_mem_db", false).close();
        QSqlDatabase::removeDatabase("in_mem_db");
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "in_mem_db");
        db.setDatabaseName(":memory:");
        if (!db.open())
            QMessageBox::warning(this, tr("Unable to open database")
                                     , tr("An error occurred while "
                                          "opening the connection: ") + db.lastError().text());
        QSqlQuery q("", db);
        q.exec("drop table Movies");
        q.exec("drop table Names");
        q.exec("create table Movies (id integer primary key, Title varchar, Director varchar, Rating number)");
        q.exec("insert into Movies values (0, 'Metropolis', 'Fritz Lang', '8.4')");
        q.exec("insert into Movies values (1, 'Nosferatu, eine Symphonie des Grauens', 'F.W. Murnau', '8.1')");
        q.exec("insert into Movies values (2, 'Bis ans Ende der Welt', 'Wim Wenders', '6.5')");
        q.exec("insert into Movies values (3, 'Hardware', 'Richard Stanley', '5.2')");
        q.exec("insert into Movies values (4, 'Mitchell', 'Andrew V. McLaglen', '2.1')");
        q.exec("create table Names (id integer primary key, Firstname varchar, Lastname varchar, City varchar)");
        q.exec("insert into Names values (0, 'Sala', 'Palmer', 'Morristown')");
        q.exec("insert into Names values (1, 'Christopher', 'Walker', 'Morristown')");
        q.exec("insert into Names values (2, 'Donald', 'Duck', 'Andeby')");
        q.exec("insert into Names values (3, 'Buck', 'Rogers', 'Paris')");
        q.exec("insert into Names values (4, 'Sherlock', 'Holmes', 'London')");
        connectionWidget->refresh();
    } else {
        int dlgPort = dialog.port();
        QSqlError err = addConnection(dialog.driverName(), dialog.databaseName(), dialog.hostName(),
                           dialog.userName(), dialog.password(), dialog.port());
        if (err.type() != QSqlError::NoError)
            QMessageBox::warning(this, tr("Unable to open database"), tr("An error occurred while "
                                       "opening the connection: ") + err.text());
    }
}

void Browser::openFile()
{
    QString fileName
      = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));

    QFileInfo fileInfo(fileName);
    QString file_ext = fileInfo.fileName();

    if(file_ext.endsWith(".db"))
    {
        QSqlError err = addConnection(QString("SQLITE"), file_ext, QString(""),
                                      QString(""), QString(""), -1);

        if (err.type() != QSqlError::NoError)
            QMessageBox::warning(this, tr("Unable to open database")
                                     , tr("An error occurred while "
                                          "opening the connection: ")
                                       + err.text());
        else
            emit statusMessage("open db-file");
    }
    else
    {
        QMessageBox::warning(this, tr("Unable to open database")
                                 , QString("Expected extension .db for a database-file\n"
                                           "The selected file was: '%1'").arg(file_ext));
    }
}

QSqlTableModel* Browser::showTable(const QString &t)
{
    QSqlTableModel *model = new QSqlTableModel(ext_table, connectionWidget->currentDatabase());
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->setTable(connectionWidget->currentDatabase().driver()->escapeIdentifier(t, QSqlDriver::TableName));
    model->select();
    if (model->lastError().type() != QSqlError::NoError)
        emit statusMessage(model->lastError().text());
    ext_table->setModel(model);
    ext_table->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);

    //JOFA additions ----------------------------------------------------------
    //ext_table->setSortingEnabled(true);
    ext_table->setAlternatingRowColors(true);
    ext_table->resizeColumnsToContents();
    //JOFA additions ----------------------------------------------------------

    connect(ext_table->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(currentChanged()));
    //JOFA experiment. Hiding rows
    //connect(ext_table->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(on_rowSelectChanged()));

    updateActions();
    return model;
}

void Browser::showTree(QSqlTableModel *model)
{
    ext_tree->setModel(model);
    //JODO? ext_tree->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);

    //JOFA additions ----------------------------------------------------------
    ext_tree->setItemsExpandable(true);
    //JOFA additions ----------------------------------------------------------

    //REV connect(table->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(currentChanged()));
    connect(ext_tree->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(on_rowSelectChanged()));

    updateActions();
}

void Browser::showMetaData(const QString &t)
{
    QSqlRecord rec = connectionWidget->currentDatabase().record(t);
    QStandardItemModel *model = new QStandardItemModel(ext_table);

    model->insertRows(0, rec.count());
    model->insertColumns(0, 7);

    model->setHeaderData(0, Qt::Horizontal, "Fieldname");
    model->setHeaderData(1, Qt::Horizontal, "Type");
    model->setHeaderData(2, Qt::Horizontal, "Length");
    model->setHeaderData(3, Qt::Horizontal, "Precision");
    model->setHeaderData(4, Qt::Horizontal, "Required");
    model->setHeaderData(5, Qt::Horizontal, "AutoValue");
    model->setHeaderData(6, Qt::Horizontal, "DefaultValue");


    for (int i = 0; i < rec.count(); ++i) {
        QSqlField fld = rec.field(i);
        model->setData(model->index(i, 0), fld.name());
        model->setData(model->index(i, 1), fld.typeID() == -1
                ? QString(QVariant::typeToName(fld.type()))
                : QString("%1 (%2)").arg(QVariant::typeToName(fld.type())).arg(fld.typeID()));
        model->setData(model->index(i, 2), fld.length());
        model->setData(model->index(i, 3), fld.precision());
        model->setData(model->index(i, 4), fld.requiredStatus() == -1 ? QVariant("?")
                : QVariant(bool(fld.requiredStatus())));
        model->setData(model->index(i, 5), fld.isAutoValue());
        model->setData(model->index(i, 6), fld.defaultValue());
    }

    ext_table->setModel(model);
    ext_table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    updateActions();
}

void Browser::insertRow()
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(ext_table->model());
    if (!model)
        return;

    QModelIndex insertIndex = ext_table->currentIndex();
    int row = insertIndex.row() == -1 ? 0 : insertIndex.row();
    model->insertRow(row);
    insertIndex = model->index(row, 0);
    ext_table->setCurrentIndex(insertIndex);
    ext_table->edit(insertIndex);
}

void Browser::deleteRow()
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(ext_table->model());
    if (!model)
        return;

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    QModelIndexList currentSelection = ext_table->selectionModel()->selectedIndexes();
    for (int i = 0; i < currentSelection.count(); ++i) {
        if (currentSelection.at(i).column() != 0)
            continue;
        model->removeRow(currentSelection.at(i).row());
    }

    model->submitAll();
    model->setEditStrategy(QSqlTableModel::OnRowChange);

    updateActions();
}

void Browser::updateActions()
{
    //CL emit statusMessage(tr("updateActions()"));
    bool enableIns = qobject_cast<QSqlTableModel *>(ext_table->model());
    bool enableDel = enableIns && ext_table->currentIndex().isValid();

    insertRowAction->setEnabled(enableIns);
    deleteRowAction->setEnabled(enableDel);
}

void Browser::about()
{
    QMessageBox::about(this, tr("About"), tr("The SQL Browser demonstration "
        "shows how a data browser can be used to visualize the results of SQL"
        "statements on a live database"));
}


//JOFA TMP some checks

void Browser::on_cellClicked(int row, int col)
{
    QString clickedCellInfo = QString("Row %1 Col %2 selected").arg(row).arg(col);
    emit statusMessage(clickedCellInfo);
}


void Browser::deselectFirstCell(int selectedRow)
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(ext_table->model());
    QModelIndex firstCell;
    const int firstCol = 0;
    firstCell = model->index(selectedRow, firstCol, QModelIndex());
    QItemSelection toggleSelection;
    toggleSelection.select(firstCell, firstCell);
    ext_table->selectionModel()->select(toggleSelection, QItemSelectionModel::Toggle);
}

//JOFA: Experiments on row hiding. Currently deactivated.
void Browser::on_rowSelectChanged()
{
    QModelIndexList currentSelection = ext_table->selectionModel()->selectedIndexes();
    int selCount    = currentSelection.count();
    int firstRow    = selCount > 0 ? currentSelection.at(1).row() : -1;
    int firstColumn = selCount > 0 ? currentSelection.at(1).column() : -1;

    // Alway the last selection is found, not the current one.
    QString selectedRowInfo = QString("Row %1 Col %2 of %3 selected").arg(firstRow).arg(firstColumn).arg(selCount);
    emit statusMessage(selectedRowInfo);

    int nextRow = firstRow + 1;
    if     (firstRow > -1 && firstColumn == 1 && !ext_table->isRowHidden(nextRow))
    {
        deselectFirstCell(firstRow);
        ext_table->hideRow(nextRow);
    }
    else if(firstRow > -1 && firstColumn == 1 &&  ext_table->isRowHidden(nextRow))
    {
        deselectFirstCell(firstRow);
        ext_table->showRow(nextRow);
    }
}

