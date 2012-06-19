/****************************************************************************
**
**
****************************************************************************/

#pragma once


#include "TestBoxes.h"

void util::launchMsgBox(const QString& text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}
