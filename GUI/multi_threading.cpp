/*This file is part of gLAB's GUI.

    gLAB's GUI is free software: you can redistribute it and/or modify
    it under the terms of the Lesser GNU General Public License as published by
    the Free Software Foundation, either version 3.

    gLAB's GUI is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    Lesser GNU General Public License for more details.

    You should have received a copy of the Lesser GNU General Public License
    along with gLAB's GUI.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "multi_threading.h"
#include "ui_multi_threading.h"
#include <QFile>
#include <QEvent>

GNSS_Multi_Threading::GNSS_Multi_Threading(QWidget *parent) :
    QDialog(parent),
    uiMThread(new Ui::GNSS_Multi_Threading)
{
    uiMThread->setupUi(this);

    // Set StyleSheet
    #if (defined Q_OS_WIN32)
        QFile qss(":/data/WinStyle.qss");
        qss.open(QFile::ReadOnly);
        this->setStyleSheet("QPushButton{border-radius: 2px; padding: 3px; width: 70px;}\
                             QPushButton:enabled{background-color:rgb(235,235,245); color:black;border: 1px solid rgb(124,124,124);}\
                             QPushButton:disabled{background-color:rgb(203,203,203); color:rgb(156,156,156);border: 1px solid rgb(185,185,185);}\
                             QPushButton:checked{background-color:rgb(173,216,230); color:black;border: 1px solid rgb(124,124,124);}"+qss.readAll());
        qss.close();
    #elif (defined Q_OS_MAC)
        QFile qss(":/data/MacStyle.qss");
        qss.open(QFile::ReadOnly);
        this->setStyleSheet(qss.readAll());
        qss.close();
    #else
        QFile qss(":/data/LinuxStyle.qss");
        qss.open(QFile::ReadOnly);
        this->setStyleSheet(qss.readAll());
        qss.close();
    #endif

    nThreads=1;

    this->setWindowTitle("Set Multi-threading options");

    uiMThread->spinBoxNumberThreads->setRange(1,1000);
    uiMThread->spinBoxNumberThreads->setValue(1);

    uiMThread->pushButtonNumberThreadsCancel->setHidden(true); //Remove when Cancel buttons undo all changes made by the user

    uiMThread->pushButtonNumberThreadsOk->setFocus();
}
GNSS_Multi_Threading::~GNSS_Multi_Threading()
{
    delete uiMThread;
}

void GNSS_Multi_Threading::on_spinBoxNumberThreads_valueChanged(int iValue) {
    nThreads=iValue;
    uiMThread->spinBoxNumberThreads->setValue(iValue);
}
void GNSS_Multi_Threading::on_pushButtonNumberThreadsDefault_clicked(){
    uiMThread->spinBoxNumberThreads->setValue(1);
    nThreads=1;
}
void GNSS_Multi_Threading::on_pushButtonNumberThreadsOk_clicked(){
    nThreads=uiMThread->spinBoxNumberThreads->value();
    this->close();
}
void GNSS_Multi_Threading::on_pushButtonNumberThreadsCancel_clicked(){
    this->close();
}
void GNSS_Multi_Threading::setThreadNumber(int numT){
    if ( numT>0 && numT<1001 ) {
        this->on_spinBoxNumberThreads_valueChanged(numT);
    }
}
