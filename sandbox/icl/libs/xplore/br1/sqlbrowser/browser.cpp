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

//---- First Accessor tests ----------------
#include "data/qsql/QSqlSelector.h"
#include "data/concept/DbBasedGraph.h"
#include "Dag/ObjectGraph.h"
#include "Dag/TypeGraph.h"

#include "gen/NumberGenerator.h"
#include "gen/NameGenerator.h"
#include "gen/DbGenerator.h"

#include "util/TestBoxes.h"

Browser::Browser(QWidget *parent)
    : QWidget(parent)
{
    //JOFA: This seems to execute the generated code
    setupUi(this);

    //JOFA: Hancoded initialization follows here.
    ext_table->addAction(insertRowAction);
    ext_table->addAction(deleteRowAction);

    ext_tree->setContextMenuPolicy(Qt::ActionsContextMenu);
    ext_tree->addAction(insertNodeAction);

    if (QSqlDatabase::drivers().isEmpty())
        QMessageBox::information(this, tr("No database drivers found"),
                                 tr("This demo requires at least one Qt database driver. "
                                    "Please check the documentation how to build the "
                                    "Qt SQL plugins."));

    connect(insertNodeAction, SIGNAL(triggered()), this, SLOT(insertNode()));

    emit statusMessage(tr("Ready."));
}

Browser::~Browser()
{
}


void Browser::insertNode()
{
    QModelIndex idx = ext_tree->currentIndex();
    if(!idx.isValid())
        return;

    //QTreeWidgetItem* curItem = ext_tree->model()->item(idx);
    QAbstractItemModel* absmo = ext_tree->model();
    DagModel*           dagmo = dynamic_cast<DagModel*>(ext_tree->model());

    QVariant variDat = absmo->data(idx);

    //TMP Insert a fixed vertex.
    // 1. Get the object id of the current
    //(2. Insert a new object (vertex))
    // 3. Insert a new edge. [Erst mal nur in den Graph.]
    // 4. Refresh the dag model: Reload it from db.



    QMessageBox msgBox;
    QString msg = "Insertion. ";
    msg += variDat.toString();
    msgBox.setText(msg);
    msgBox.exec();

    insertNewVertex(dagmo, idx);
}


// Insert a new Vertex and Edge at node refered by index in the boost::graph.
// Then update the DagModel.
void Browser::insertNewVertex(DagModel* pDagModel, const QModelIndex& index)
{
    Q_ASSERT(index.isValid());
    // Get the id.
    QModelIndex idIndex = index.sibling(index.row(), dag::node::posId);

    //create an edge, fill as dummy and append.
    QVector<QVariant> edgeData(dag::edge::sizeOf_edge);
    pDagModel->fillDummyData(edgeData, idIndex.data().toInt());

    //Insert the dummy edge into DagModel (keeping the Dag consistent also)
    //CL.. pDagModel->appendEdge(data);
    pDagModel->insertVertex(edgeData, idIndex);
}


void Browser::exec()
{
    /*JODO REV
    if(sqlEdit->toPlainText().isEmpty())
    {
        rexec();
        return;
    }
    */

    QSqlQueryModel *model = new QSqlQueryModel(ext_table);

    model->setQuery(QSqlQuery(sqlEdit->toPlainText(), connectionWidget->currentDatabase()));
    ext_table->setModel(model);

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

bool Browser::runScript()
{
    //return execScript(); // Execute a script containing of multiple sql-statements
    //return casualTests();
    //return testTypeSelector();
    return testObjectSelector();
    //emit statusMessage(tr("Generating DB ..."));
    //return generateDb();
}


bool Browser::execScript()
{
    QString   curSql   = sqlEdit->toPlainText();
    QSqlQuery curQuery = QSqlQuery(connectionWidget->currentDatabase());

    bool success = execMulti(curQuery, curSql);

    if(success)
        emit statusMessage(tr("Script executed successfully."));
    else
        emit statusMessage(tr("Error(s), Script aborted."));

    return success;
}


//------------------------------------------------------------------------------
//JODO CL. Make a better GUI for different funcitons.
//Experimental space
bool Browser::generateDb()
{
    using namespace gen;
    DbGenerator aDbGentor = DbGenerator(connectionWidget->currentDatabase());
    bool success = aDbGentor.generate();

    if(success)
        emit statusMessage(tr("Db generated successfully."));
    else
        emit statusMessage(tr("Error(s), in Db generation."));

    return success;
}

bool Browser::testTypeSelector()
{
    bool success = false;
    data::QSqlSelector selector;
    dag::db::TypeGraph tygra;

    selector.setDatabase(connectionWidget->currentDatabase());

    success = data::makeDbGraph(tygra, connectionWidget->currentDatabase());

    util::launchMsgBox(tygra.toString());
    util::launchMsgBox(tygra.depthFirstString());

    if(success)
        emit statusMessage(tr("Test executed successfully."));
    else
        emit statusMessage(tr("Error(s), Test aborted."));

    return success;
}

bool Browser::testObjectSelector()
{
    bool success = false;
    data::QSqlSelector selector;
    dag::db::ObjectGraph ogra;

    selector.setDatabase(connectionWidget->currentDatabase());

    success = data::makeDbGraph(ogra, connectionWidget->currentDatabase());

    util::launchMsgBox(ogra.toString());
    util::launchMsgBox(ogra.depthFirstString());

    //--------------------------------------------------------------------------
    DagModel* dagmo = new DagModel(); // Dag-Model
    QString dbg_dagString = ogra.makeDagModel(dagmo);
    util::launchMsgBox(dbg_dagString);
    dagmo->setHeaderData(0, Qt::Horizontal, "");
    dagmo->setHeaderData(1, Qt::Horizontal, "Object");
    dagmo->setHeaderData(2, Qt::Horizontal, "Type");
    ext_tree->setModel(dagmo);
    ext_tree->resizeColumnToContents(0);
    ext_tree->resizeColumnToContents(1);
    ext_tree->resizeColumnToContents(2);
    //--------------------------------------------------------------------------

    if(success)
        emit statusMessage(tr("Test executed successfully."));
    else
        emit statusMessage(tr("Error(s), Test aborted."));

    return success;
}

bool Browser::casualTests()
{
    QString   curSql   = "select * from EdgeType";
    QSqlQuery curQuery = QSqlQuery(connectionWidget->currentDatabase());

    //JODO Testcode
    gen::tString some;
    gen::NameGenerator makeSome(2,5);

    int trials = gen::IntGenerator(2,10)();
    for(int i=0; i<trials ; i++)
    {
        double dbg_dbl = gen::DoubleGenerator(0.1, 0.9)();
        some += makeSome();
        some += "\n";
    }

    bool success = false;
    data::QSqlSelector selector;
    dag::db::TypeGraph tygra;

    selector.setDatabase(connectionWidget->currentDatabase());
    success = addEdgeData(selector, tygra);

    if(success)
        emit statusMessage(tr("Test executed successfully."));
    else
        emit statusMessage(tr("Error(s), Test aborted."));

    return success;
}


bool Browser::execMulti(QSqlQuery& query, const QString& script)
{
    bool success = true;
    QStringList scriptQueries = script.split('\n');

    foreach(QString queryTxt, scriptQueries)
    {
        if (queryTxt.trimmed().isEmpty()) {
            continue;
        }
        if (!query.exec(queryTxt))
        {
            qFatal(QString("One of the query failed to execute."
                           " Error detail: " + query.lastError().text() + "\n" +
                           " Q:'" + queryTxt + "'").toLocal8Bit());
            success = false;
        }
        query.finish();
    }
    return success;
}

/*CL after refa
void Browser::rexec()
{
    QSqlQueryModel *model = new QSqlQueryModel(ext_table);


    QString dagSql;
    dagSql += "select Dag.Parent as ParentId, Dag.Child as ChildId, Types.Id as TypeId, \n";
    dagSql += "  (select Objects.name from Objects where Objects.id = Dag.Parent) as Parent, \n";
    dagSql += "  Objects.name as Child, Types.name as Type  \n";
    dagSql += "  from Dag \n";
    dagSql += "  inner join Objects on      Dag.Child = Objects.id \n";
    dagSql += "  inner join Types   on Objects.TypeOf = Types.id ";

    QSqlQuery curQuery = QSqlQuery(dagSql, connectionWidget->currentDatabase());

    QStringList headers; //JODO handle headers
    headers << tr("Title") << tr("Description");
    DagModel* dagmo = new DagModel(); // Dag-Model

    QSqlQuery xpQuery = QSqlQuery("", connectionWidget->currentDatabase());
    xpQuery.exec(dagSql);

    // Populate the Dag Model from an sql-Query
    dagmo->getEdges(xpQuery);  //Read edges from database
    dagmo->makeDag();          //Make a boost::graph internally

    QString dagStr  = dagmo->setupDag(); //Build a tree representation from the boost::dag

    model->setQuery(curQuery);
    //REV? model->setQuery(QSqlQuery(sqlEdit->toPlainText(), connectionWidget->currentDatabase()));

    ext_table->setModel(model);
    ext_tree->setModel(dagmo);//JOFA

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
*/

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
        //int dlgPort = dialog.port();
        QSqlError err = addConnection(dialog.driverName(), dialog.databaseName(), dialog.hostName(),
                           dialog.userName(), dialog.password(), dialog.port());
        if (err.type() != QSqlError::NoError)
            QMessageBox::warning(this, tr("Unable to open database"), tr("An error occurred while "
                                       "opening the connection: ") + err.text());
        else//Execute an initial setup of the Dag
            ;//JODO REV rexec();
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

