TEMPLATE        = app
TARGET          = sqlbrowser

QT              += sql

INCLUDEPATH     += /NIBuild/3rdparty/boost-1.48.0
#INCLUDEPATH     += /cygwin/home/jofa/dev/boost/trunk

HEADERS         = browser.h connectionwidget.h qsqlconnectiondialog.h \
    exttableview.h \
    dagitem.h \
    dagmodel.h \
    dagmodel.h \
    StringVisitor.h \
    Dag.h \
    CreatorVisitor.h \
    Dag/DbType.h
SOURCES         = main.cpp browser.cpp connectionwidget.cpp qsqlconnectiondialog.cpp \
    exttableview.cpp \
    dagitem.cpp \
    dagmodel.cpp

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











