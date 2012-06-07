TEMPLATE        = app
TARGET          = sqlbrowser

QT              += sql

#INCLUDEPATH     += /cygwin/home/jofa/dev/boost/branches/release
INCLUDEPATH     += C:\NIBuild\3rdparty\boost-1.48.0

HEADERS         = browser.h connectionwidget.h qsqlconnectiondialog.h \
    exttableview.h \
    dagitem.h \
    dagmodel.h \
    dagmodel.h \
    StringVisitor.h \
    Dag.h \
    CreatorVisitor.h \
    Dag/DbType.h \
    Dag/DbType.cpp \
    Dag/TypeGraph.h \
    Dag/Decoration.h \
    Dag/DecoratedGraph.h \
    data/concept/SelectorTraits.h \
    data/concept/Selector.h \
    data/concept/IsQuerySelector.h \
    data/concept/CreatorTraits.h \
    data/qsql/QSqlSelector.h \
    data/qsql/QSqlCreator.h \
    data/concept/GetCreator.h \
    gen/NameGenerator.h \
    gen/NumberGenerator.h \
    gen/DbGenerator.h \
    data/concept/Creator.h \
    data/concept/TypeGraphMaker.h
SOURCES         = main.cpp browser.cpp connectionwidget.cpp qsqlconnectiondialog.cpp \
    exttableview.cpp \
    dagitem.cpp \
    dagmodel.cpp \
    Dag/TypeGraph.cpp \
    Dag/TypeGraph.cpp \
    gen/NameGenerator.cpp \
    gen/NumberGenerator.cpp \
    gen/DbGenerator.cpp

FORMS           = browserwidget.ui qsqlconnectiondialog.ui
build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

# install
target.path = $$[QT_INSTALL_DEMOS]/sqlbrowser
sources.files = $$SOURCES $$HEADERS $$FORMS *.pro
sources.path = $$[QT_INSTALL_DEMOS]/sqlbrowser
INSTALLS += target sources

symbian: include($$QT_SOURCE_TREE/demos/symbianpkgrules.pri)

wince*: {
    DEPLOYMENT_PLUGIN += qsqlite
}












