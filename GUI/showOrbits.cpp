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

#include "glab_gui.h"
#include "ui_glab_gui.h"
#include "math.h"



//Function to show or hide start time
void gLAB_GUI::on_checkBoxStartTimeShowOrbits_clicked(bool checked) {
    ui->frame_StartTimeCalendar_ShowOrbits->setHidden(!checked);
}

//Function to show or hide end time
void gLAB_GUI::on_checkBoxEndTimeShowOrbits_clicked(bool checked) {
    ui->frame_EndTimeCalendar_ShowOrbits->setHidden(!checked);
}

// Function to show or hide the ANTEX input
void gLAB_GUI::on_checkBoxAntexShowOrbitFile_clicked(bool checked) {
    ui->checkBoxAntexShowOrbitFile->setChecked(checked);
    ui->frameAntexShowOrbitLineEditFile->setHidden(!checked);
}

// Function for showing lineEdit for Navigation File
void gLAB_GUI::on_radioButtonOrbitNavShowOrbitFile_clicked() {
    ui->stackedWidgetOrbitAndClockShowOrbitFile->setCurrentIndex(0);
    ui->radioButtonOrbitNavShowOrbitFile->setChecked(true);
    ui->radioButtonOrbitPrecise1filesShowOrbitFile->setChecked(false);
    ui->radioButtonOrbitPrecise2filesShowOrbitFile->setChecked(false);
    ui->groupBoAntexFileShowOrbit->setHidden(true);
    ui->groupBoxPreciseProductsInterpolationShowOrbit->setHidden(true);
    ui->groupBoxShowNavMessageTypes->setHidden(false);
    this->on_pushButtonShowNavMessageTypesSetDefault_clicked();
}

// Function for showing lineEdit for SP3 File
void gLAB_GUI::on_radioButtonOrbitPrecise1filesShowOrbitFile_clicked() {
    ui->stackedWidgetOrbitAndClockShowOrbitFile->setCurrentIndex(1);
    ui->radioButtonOrbitNavShowOrbitFile->setChecked(false);
    ui->radioButtonOrbitPrecise1filesShowOrbitFile->setChecked(true);
    ui->radioButtonOrbitPrecise2filesShowOrbitFile->setChecked(false);
    ui->groupBoAntexFileShowOrbit->setHidden(false);
    ui->groupBoxPreciseProductsInterpolationShowOrbit->setHidden(false);
    ui->groupBoxShowNavMessageTypes->setHidden(true);
}

// Function for showing lineEdit for SP3+CLK File
void gLAB_GUI::on_radioButtonOrbitPrecise2filesShowOrbitFile_clicked() {
    ui->stackedWidgetOrbitAndClockShowOrbitFile->setCurrentIndex(2);
    ui->radioButtonOrbitNavShowOrbitFile->setChecked(false);
    ui->radioButtonOrbitPrecise1filesShowOrbitFile->setChecked(false);
    ui->radioButtonOrbitPrecise2filesShowOrbitFile->setChecked(true);
    ui->groupBoAntexFileShowOrbit->setHidden(false);
    ui->groupBoxPreciseProductsInterpolationShowOrbit->setHidden(false);
    ui->groupBoxShowNavMessageTypes->setHidden(true);
}

//Function to show or hide concatenated SP3/CLK options
void gLAB_GUI::on_groupBoxConcatenedPreciseFilesShowOrbit_clicked(bool checked) {
    ui->groupBoxConcatenedPreciseFilesShowOrbit->setChecked(checked);
    ui->frameConcatenedPreciseFilesShowOrbit->setHidden(!checked);
}


////////////////////// Push buttons /////////////////////

void gLAB_GUI::on_pushButtonRinexNavShowOrbitFile_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.??n *.??g *.??l *.??p *.??h *n.rnx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditNavShowOrbitFile->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileShowOrbit->text() == "" ) {
                ui->lineEditOutputFileShowOrbit->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/orbits.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonPrecise1FileShowOrbitFile_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Precise Files (*.sp3 *.eph);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPreciseFilesShowOrbitSP3File->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileShowOrbit->text() == "" ) {
                ui->lineEditOutputFileShowOrbit->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/orbits.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonPrecise2FilesShowOrbitFile_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Precise Files (*.sp3 *.eph);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPreciseFilesShowOrbitOrbFile->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileShowOrbit->text() == "" ) {
                ui->lineEditOutputFileShowOrbit->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/orbits.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonPreciseClkShowOrbitFile_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Clock Files (*.clk *.clk_30s *.clk_05s);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPreciseFilesShowOrbitClkFile->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileShowOrbit->text() == "" ) {
                ui->lineEditOutputFileShowOrbit->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/orbits.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonAntexShowOrbitFile_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("ANTEX Files (*.atx);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditAntexShowOrbitFile->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileShowOrbit->text() == "" ) {
                ui->lineEditOutputFileShowOrbit->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/orbits.out"));
            }
        }
    }
}

// Open dialog to set the output filename and path
void gLAB_GUI::on_pushButtonOutputFileShowOrbit_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    //dialog.setAcceptMode(QFileDialog::AcceptSave); //This to confirm overwriting files
    dialog.setNameFilter(tr("gLAB Output Files (*.out);;All Files (*.*)"));
    dialog.selectFile(".out");
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditOutputFileShowOrbit->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

//Set all output messages button
void gLAB_GUI::on_pushButtonShowOrbitMessagesAll_clicked() {
    ui->checkBoxPrintInfoShowOrbit->setChecked(true);
    ui->checkBoxPrintSatpvtShowOrbit->setChecked(true);
}

//Unset all output messages button
void gLAB_GUI::on_pushButtonShowOrbitMessagesNone_clicked() {
    ui->checkBoxPrintInfoShowOrbit->setChecked(false);
    ui->checkBoxPrintSatpvtShowOrbit->setChecked(false);
}

////////////////// End of Push buttons //////////////////

///////////////// Start of Context menus (right-click menus) //////////////////
void gLAB_GUI::labelShowOrbitRinexNavFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelShowOrbitRinexNavFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open RINEX Navigation File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditNavShowOrbitFile->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditNavShowOrbitFile->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditNavShowOrbitFile->text();
        #endif

        // Execute the program
        if (ui->lineEditNavShowOrbitFile->text() == "") {
            messageBox.warning(nullptr, "Error","RINEX Navigation file is empty\n");
        } else if (this->fileExists(ui->lineEditNavShowOrbitFile->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditNavShowOrbitFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditNavShowOrbitFile->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelShowOrbitSP3OrbitsClocksFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelShowOrbitSP3OrbitsClocksFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open SP3 File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPreciseFilesShowOrbitSP3File->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPreciseFilesShowOrbitSP3File->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPreciseFilesShowOrbitSP3File->text();
        #endif

        // Execute the program
        if (ui->lineEditPreciseFilesShowOrbitSP3File->text() == "") {
            messageBox.warning(nullptr, "Error","SP3 file is empty\n");
        } else if  (this->fileExists(ui->lineEditPreciseFilesShowOrbitSP3File->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesShowOrbitSP3File->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesShowOrbitSP3File->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelShowOrbitSP3OrbitsFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelShowOrbitSP3OrbitsFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open SP3 File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPreciseFilesShowOrbitOrbFile->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPreciseFilesShowOrbitOrbFile->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPreciseFilesShowOrbitOrbFile->text();
        #endif

        // Execute the program
        if (ui->lineEditPreciseFilesShowOrbitOrbFile->text() == "") {
            messageBox.warning(nullptr, "Error","SP3 file is empty\n");
        } else if (this->fileExists(ui->lineEditPreciseFilesShowOrbitOrbFile->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesShowOrbitOrbFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesShowOrbitOrbFile->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelShowOrbitClocksFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelShowOrbitClocksFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open Clock File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPreciseFilesShowOrbitClkFile->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPreciseFilesShowOrbitClkFile->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPreciseFilesShowOrbitClkFile->text();
        #endif

        // Execute the program
        if (ui->lineEditPreciseFilesShowOrbitClkFile->text() == "") {
            messageBox.warning(nullptr, "Error","Clock file is empty\n");
        } else if (this->fileExists(ui->lineEditPreciseFilesShowOrbitClkFile->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesShowOrbitClkFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesShowOrbitClkFile->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::checkBoxAntexShowOrbitFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->checkBoxAntexShowOrbitFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open ANTEX File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditAntexShowOrbitFile->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditAntexShowOrbitFile->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditAntexShowOrbitFile->text();
        #endif

        // Execute the program
        if (ui->lineEditAntexShowOrbitFile->text() == "") {
            messageBox.warning(nullptr, "Error","ANTEX file is empty\n");
        } else if (this->fileExists(ui->lineEditAntexShowOrbitFile->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditAntexShowOrbitFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditAntexShowOrbitFile->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelShowOrbitOutputFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelShowOrbitOutputFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open Output File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditOutputFileShowOrbit->text();
        #elif defined(Q_OS_WIN32)
            //QString programFilesPath(getenv("PROGRAMFILES"));
            //program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            program = QString("notepad");
            arguments << ui->lineEditOutputFileShowOrbit->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditOutputFileShowOrbit->text();
        #endif

        // Execute the program
        if (ui->lineEditOutputFileShowOrbit->text() == "") {
            messageBox.warning(nullptr, "Error","Output file is empty\n");
        } else if (this->fileExists(ui->lineEditOutputFileShowOrbit->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditOutputFileShowOrbit->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditOutputFileShowOrbit->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::on_groupBoxEleAziSpecify_clicked(bool checked){
    ui->groupBoxEleAziSpecify->setChecked(checked);
    ui->frameEleAziSpecify->setHidden(!checked);
}
void gLAB_GUI::on_radioButtonEleAziSpecifyUserCartesian_clicked() {
    ui->radioButtonEleAziSpecifyUserCartesian->setChecked(true);
    ui->stackedWidgetEleAziSpecifyCoordinatesType->setCurrentIndex(0);
}

void gLAB_GUI::on_radioButtonEleAziSpecifyUserGeodetic_clicked() {
    ui->radioButtonEleAziSpecifyUserGeodetic->setChecked(true);
    ui->stackedWidgetEleAziSpecifyCoordinatesType->setCurrentIndex(1);
}

void gLAB_GUI::selectGNSS_ShowNavMessageTypes(int selectFlag,int iGNSS){
    if (selectFlag>0){
        //GPS
        if (iGNSS==GPS) for (int i=0; i<ui->tableWidgetShowNavMessageTypeGPS->columnCount();i++){
            ui->tableWidgetShowNavMessageTypeGPS->item(0,i)->setText(NavMessageTypes[GPS][0][i]);
            ui->tableWidgetShowNavMessageTypeGPS->item(0,i)->setBackground(gnssSelected);
        }
        //Galileo
        if (iGNSS==Galileo) for (int i=0; i<ui->tableWidgetShowNavMessageTypeGalileo->columnCount();i++){
            ui->tableWidgetShowNavMessageTypeGalileo->item(0,i)->setText(NavMessageTypes[Galileo][0][i]);
            ui->tableWidgetShowNavMessageTypeGalileo->item(0,i)->setBackground(gnssSelected);
        }
        //GLONASS
        if (iGNSS==GLONASS) for (int i=0; i<ui->tableWidgetShowNavMessageTypeGLONASS->columnCount();i++){
            ui->tableWidgetShowNavMessageTypeGLONASS->item(0,i)->setText(NavMessageTypes[GLONASS][0][i]);
            ui->tableWidgetShowNavMessageTypeGLONASS->item(0,i)->setBackground(gnssSelected);
        }
        //GEO
        if (iGNSS==GEO) for (int i=0; i<ui->tableWidgetShowNavMessageTypeGEO->columnCount();i++){
            ui->tableWidgetShowNavMessageTypeGEO->item(0,i)->setText(NavMessageTypes[GEO][0][i]);
            ui->tableWidgetShowNavMessageTypeGEO->item(0,i)->setBackground(gnssSelected);
        }
        //BDS
        if (iGNSS==BDS) for (int i=0; i<ui->tableWidgetShowNavMessageTypeBDS->columnCount();i++){
            ui->tableWidgetShowNavMessageTypeBDS->item(0,i)->setText(NavMessageTypes[BDS][0][i]);
            ui->tableWidgetShowNavMessageTypeBDS->item(0,i)->setBackground(gnssSelected);
        }
        //QZSS
        if (iGNSS==QZSS) for (int i=0; i<ui->tableWidgetShowNavMessageTypeQZSS->columnCount();i++){
            ui->tableWidgetShowNavMessageTypeQZSS->item(0,i)->setText(NavMessageTypes[QZSS][0][i]);
            ui->tableWidgetShowNavMessageTypeQZSS->item(0,i)->setBackground(gnssSelected);
        }
        //IRNSS
        if (iGNSS==IRNSS) for (int i=0; i<ui->tableWidgetShowNavMessageTypeIRNSS->columnCount();i++){
            ui->tableWidgetShowNavMessageTypeIRNSS->item(0,i)->setText(NavMessageTypes[IRNSS][0][i]);
            ui->tableWidgetShowNavMessageTypeIRNSS->item(0,i)->setBackground(gnssSelected);
        }
    } else {
        //GPS
        if (iGNSS==GPS) for (int i=0; i<ui->tableWidgetShowNavMessageTypeGPS->columnCount();i++){
            ui->tableWidgetShowNavMessageTypeGPS->item(0,i)->setText(NavMessageTypes[GPS][0][i]);
            ui->tableWidgetShowNavMessageTypeGPS->item(0,i)->setBackground(gnssUnSelected);
        }
        //Galileo
        if (iGNSS==Galileo) for (int i=0; i<ui->tableWidgetShowNavMessageTypeGalileo->columnCount();i++){
            ui->tableWidgetShowNavMessageTypeGalileo->item(0,i)->setText(NavMessageTypes[Galileo][0][i]);
            ui->tableWidgetShowNavMessageTypeGalileo->item(0,i)->setBackground(gnssUnSelected);
        }
        //GLONASS
        if (iGNSS==GLONASS) for (int i=0; i<ui->tableWidgetShowNavMessageTypeGLONASS->columnCount();i++){
            ui->tableWidgetShowNavMessageTypeGLONASS->item(0,i)->setText(NavMessageTypes[GLONASS][0][i]);
            ui->tableWidgetShowNavMessageTypeGLONASS->item(0,i)->setBackground(gnssUnSelected);
        }
        //GEO
        if (iGNSS==GEO) for (int i=0; i<ui->tableWidgetShowNavMessageTypeGEO->columnCount();i++){
            ui->tableWidgetShowNavMessageTypeGEO->item(0,i)->setText(NavMessageTypes[GEO][0][i]);
            ui->tableWidgetShowNavMessageTypeGEO->item(0,i)->setBackground(gnssUnSelected);
        }
        //BDS
        if (iGNSS==BDS) for (int i=0; i<ui->tableWidgetShowNavMessageTypeBDS->columnCount();i++){
            ui->tableWidgetShowNavMessageTypeBDS->item(0,i)->setText(NavMessageTypes[BDS][0][i]);
            ui->tableWidgetShowNavMessageTypeBDS->item(0,i)->setBackground(gnssUnSelected);
        }
        //QZSS
        if (iGNSS==QZSS) for (int i=0; i<ui->tableWidgetShowNavMessageTypeQZSS->columnCount();i++){
            ui->tableWidgetShowNavMessageTypeQZSS->item(0,i)->setText(NavMessageTypes[QZSS][0][i]);
            ui->tableWidgetShowNavMessageTypeQZSS->item(0,i)->setBackground(gnssUnSelected);
        }
        //IRNSS
        if (iGNSS==IRNSS) for (int i=0; i<ui->tableWidgetShowNavMessageTypeIRNSS->columnCount();i++){
            ui->tableWidgetShowNavMessageTypeIRNSS->item(0,i)->setText(NavMessageTypes[IRNSS][0][i]);
            ui->tableWidgetShowNavMessageTypeIRNSS->item(0,i)->setBackground(gnssUnSelected);
        }
    }
}
void gLAB_GUI::on_pushButtonShowNavMessageTypesSetDefault_clicked(){
    //GPS
    for (int i=0; i<ui->tableWidgetShowNavMessageTypeGPS->columnCount();i++){
        ui->tableWidgetShowNavMessageTypeGPS->item(0,i)->setText(NavMessageTypes[GPS][0][i]);
        ui->tableWidgetShowNavMessageTypeGPS->item(0,i)->setBackground(gnssSelected);
    }
    //Galileo
    for (int i=0; i<ui->tableWidgetShowNavMessageTypeGalileo->columnCount();i++){
        ui->tableWidgetShowNavMessageTypeGalileo->item(0,i)->setText(NavMessageTypes[Galileo][0][i]);
        ui->tableWidgetShowNavMessageTypeGalileo->item(0,i)->setBackground(gnssSelected);
    }
    //GLONASS
    for (int i=0; i<ui->tableWidgetShowNavMessageTypeGLONASS->columnCount();i++){
        ui->tableWidgetShowNavMessageTypeGLONASS->item(0,i)->setText(NavMessageTypes[GLONASS][0][i]);
        ui->tableWidgetShowNavMessageTypeGLONASS->item(0,i)->setBackground(gnssSelected);
    }
    //GEO
    for (int i=0; i<ui->tableWidgetShowNavMessageTypeGEO->columnCount();i++){
        ui->tableWidgetShowNavMessageTypeGEO->item(0,i)->setText(NavMessageTypes[GEO][0][i]);
        ui->tableWidgetShowNavMessageTypeGEO->item(0,i)->setBackground(gnssSelected);
    }
    //BDS
    for (int i=0; i<ui->tableWidgetShowNavMessageTypeBDS->columnCount();i++){
        ui->tableWidgetShowNavMessageTypeBDS->item(0,i)->setText(NavMessageTypes[BDS][0][i]);
        ui->tableWidgetShowNavMessageTypeBDS->item(0,i)->setBackground(gnssSelected);
    }
    //QZSS
    for (int i=0; i<ui->tableWidgetShowNavMessageTypeQZSS->columnCount();i++){
        ui->tableWidgetShowNavMessageTypeQZSS->item(0,i)->setText(NavMessageTypes[QZSS][0][i]);
        ui->tableWidgetShowNavMessageTypeQZSS->item(0,i)->setBackground(gnssSelected);
    }
    //IRNSS
    for (int i=0; i<ui->tableWidgetShowNavMessageTypeIRNSS->columnCount();i++){
        ui->tableWidgetShowNavMessageTypeIRNSS->item(0,i)->setText(NavMessageTypes[IRNSS][0][i]);
        ui->tableWidgetShowNavMessageTypeIRNSS->item(0,i)->setBackground(gnssSelected);
    }

    on_checkBoxShowNavMessageTypeGPS_clicked(true);
    on_checkBoxShowNavMessageTypeGalileo_clicked(true);
    on_checkBoxShowNavMessageTypeGLONASS_clicked(true);
    on_checkBoxShowNavMessageTypeGEO_clicked(true);
    on_checkBoxShowNavMessageTypeBDS_clicked(true);
    on_checkBoxShowNavMessageTypeQZSS_clicked(true);
    on_checkBoxShowNavMessageTypeIRNSS_clicked(true);
    ui->tableWidgetShowNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeIRNSS->setCurrentItem(nullptr);
    ui->lineEditShowNavFreshTime->setText(DEFAULT_PREFERRED_NAV_TIME);
}
void gLAB_GUI::on_pushButtonShowNavMessageTypesBoost_clicked(){
    //GPS
    if (ui->tableWidgetShowNavMessageTypeGPS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetShowNavMessageTypeGPS,ui->tableWidgetShowNavMessageTypeGPS->currentColumn(),ui->tableWidgetShowNavMessageTypeGPS->currentColumn()-1,0);
    }
    //Galileo
    if (ui->tableWidgetShowNavMessageTypeGalileo->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetShowNavMessageTypeGalileo,ui->tableWidgetShowNavMessageTypeGalileo->currentColumn(),ui->tableWidgetShowNavMessageTypeGalileo->currentColumn()-1,0);
    }
    //GLONASS
    if (ui->tableWidgetShowNavMessageTypeGLONASS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetShowNavMessageTypeGLONASS,ui->tableWidgetShowNavMessageTypeGLONASS->currentColumn(),ui->tableWidgetShowNavMessageTypeGLONASS->currentColumn()-1,0);
    }
    //GEO
    if (ui->tableWidgetShowNavMessageTypeGEO->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetShowNavMessageTypeGEO,ui->tableWidgetShowNavMessageTypeGEO->currentColumn(),ui->tableWidgetShowNavMessageTypeGEO->currentColumn()-1,0);
    }
    //BDS
    if (ui->tableWidgetShowNavMessageTypeBDS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetShowNavMessageTypeBDS,ui->tableWidgetShowNavMessageTypeBDS->currentColumn(),ui->tableWidgetShowNavMessageTypeBDS->currentColumn()-1,0);
    }
    //QZSS
    if (ui->tableWidgetShowNavMessageTypeQZSS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetShowNavMessageTypeQZSS,ui->tableWidgetShowNavMessageTypeQZSS->currentColumn(),ui->tableWidgetShowNavMessageTypeQZSS->currentColumn()-1,0);
    }
    //IRNSS
    if (ui->tableWidgetShowNavMessageTypeIRNSS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetShowNavMessageTypeIRNSS,ui->tableWidgetShowNavMessageTypeIRNSS->currentColumn(),ui->tableWidgetShowNavMessageTypeIRNSS->currentColumn()-1,0);
    }
}
void gLAB_GUI::on_pushButtonShowNavMessageTypesLower_clicked(){
    //GPS
    if (ui->tableWidgetShowNavMessageTypeGPS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetShowNavMessageTypeGPS,ui->tableWidgetShowNavMessageTypeGPS->currentColumn(),ui->tableWidgetShowNavMessageTypeGPS->currentColumn()+1,0);
    }
    //Galileo
    if (ui->tableWidgetShowNavMessageTypeGalileo->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetShowNavMessageTypeGalileo,ui->tableWidgetShowNavMessageTypeGalileo->currentColumn(),ui->tableWidgetShowNavMessageTypeGalileo->currentColumn()+1,0);
    }
    //GLONASS
    if (ui->tableWidgetShowNavMessageTypeGLONASS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetShowNavMessageTypeGLONASS,ui->tableWidgetShowNavMessageTypeGLONASS->currentColumn(),ui->tableWidgetShowNavMessageTypeGLONASS->currentColumn()+1,0);
    }
    //GEO
    if (ui->tableWidgetShowNavMessageTypeGEO->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetShowNavMessageTypeGEO,ui->tableWidgetShowNavMessageTypeGEO->currentColumn(),ui->tableWidgetShowNavMessageTypeGEO->currentColumn()+1,0);
    }
    //BDS
    if (ui->tableWidgetShowNavMessageTypeBDS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetShowNavMessageTypeBDS,ui->tableWidgetShowNavMessageTypeBDS->currentColumn(),ui->tableWidgetShowNavMessageTypeBDS->currentColumn()+1,0);
    }
    //QZSS
    if (ui->tableWidgetShowNavMessageTypeQZSS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetShowNavMessageTypeQZSS,ui->tableWidgetShowNavMessageTypeQZSS->currentColumn(),ui->tableWidgetShowNavMessageTypeQZSS->currentColumn()+1,0);
    }
    //IRNSS
    if (ui->tableWidgetShowNavMessageTypeIRNSS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetShowNavMessageTypeIRNSS,ui->tableWidgetShowNavMessageTypeIRNSS->currentColumn(),ui->tableWidgetShowNavMessageTypeIRNSS->currentColumn()-1,0);
    }
}
void gLAB_GUI::on_checkBoxShowNavMessageTypeGPS_clicked(bool checked){
    ui->checkBoxShowNavMessageTypeGPS->setChecked(checked);
    if (checked==true) ui->tableWidgetShowNavMessageTypeGPS->setHidden(false);
    else ui->tableWidgetShowNavMessageTypeGPS->setHidden(true);
    ui->tableWidgetShowNavMessageTypeGPS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxShowNavMessageTypeGLONASS_clicked(bool checked){
    ui->checkBoxShowNavMessageTypeGLONASS->setChecked(checked);
    if (checked==true) ui->tableWidgetShowNavMessageTypeGLONASS->setHidden(false);
    else ui->tableWidgetShowNavMessageTypeGLONASS->setHidden(true);
    ui->tableWidgetShowNavMessageTypeGLONASS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxShowNavMessageTypeGalileo_clicked(bool checked){
    ui->checkBoxShowNavMessageTypeGalileo->setChecked(checked);
    if (checked==true) ui->tableWidgetShowNavMessageTypeGalileo->setHidden(false);
    else ui->tableWidgetShowNavMessageTypeGalileo->setHidden(true);
    ui->tableWidgetShowNavMessageTypeGalileo->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxShowNavMessageTypeGEO_clicked(bool checked){
    ui->checkBoxShowNavMessageTypeGEO->setChecked(checked);
    if (checked==true) ui->tableWidgetShowNavMessageTypeGEO->setHidden(false);
    else ui->tableWidgetShowNavMessageTypeGEO->setHidden(true);
    ui->tableWidgetShowNavMessageTypeGEO->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxShowNavMessageTypeBDS_clicked(bool checked){
    ui->checkBoxShowNavMessageTypeBDS->setChecked(checked);
    if (checked==true) ui->tableWidgetShowNavMessageTypeBDS->setHidden(false);
    else ui->tableWidgetShowNavMessageTypeBDS->setHidden(true);
    ui->tableWidgetShowNavMessageTypeBDS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxShowNavMessageTypeQZSS_clicked(bool checked){
    ui->checkBoxShowNavMessageTypeQZSS->setChecked(checked);
    if (checked==true) ui->tableWidgetShowNavMessageTypeQZSS->setHidden(false);
    else ui->tableWidgetShowNavMessageTypeQZSS->setHidden(true);
    ui->tableWidgetShowNavMessageTypeQZSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxShowNavMessageTypeIRNSS_clicked(bool checked){
    ui->checkBoxShowNavMessageTypeIRNSS->setChecked(checked);
    if (checked==true) ui->tableWidgetShowNavMessageTypeIRNSS->setHidden(false);
    else ui->tableWidgetShowNavMessageTypeIRNSS->setHidden(true);
    ui->tableWidgetShowNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetShowNavMessageTypeGPS_clicked(){
    ui->tableWidgetShowNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetShowNavMessageTypeGalileo_clicked(){
    ui->tableWidgetShowNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetShowNavMessageTypeGLONASS_clicked(){
    ui->tableWidgetShowNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetShowNavMessageTypeGEO_clicked(){
    ui->tableWidgetShowNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetShowNavMessageTypeBDS_clicked(){
    ui->tableWidgetShowNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetShowNavMessageTypeQZSS_clicked(){
    ui->tableWidgetShowNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetShowNavMessageTypeIRNSS_clicked(){
    ui->tableWidgetShowNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetShowNavMessageTypeQZSS->setCurrentItem(nullptr);
}

///////////////// End of Context menus (right-click menus) //////////////////

void gLAB_GUI::getshowOrbitOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString) {

    QDate       date;
    QTime       time;
    int         NumMessages=1;
    int         SP3File=0;
    int         badDate=0;

    *errorString = "";
    *warningString="";
    *saveString = "";

    //Check File
    if ( ui->radioButtonOrbitNavShowOrbitFile->isChecked()==true) {
        //File is navigation file
        if ( ui->lineEditNavShowOrbitFile->text() == "" ) {
            *errorString += "Navigation source file is empty.\n";
        } else if ( this->fileExists(ui->lineEditNavShowOrbitFile->text())==false ) {
            *errorString += "Navigation source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditNavShowOrbitFile->text())==1) {
            *errorString += "Navigation source file has non ASCII characters\n";
        } else {
            *saveString += "-input:nav " + ui->lineEditNavShowOrbitFile->text() + "\n";
            *runString <<  "-input:nav" << ui->lineEditNavShowOrbitFile->text();
        }
        //Navigation Message Type
        //GPS
        QString cmdNavMT="",cmdNavMT2="";
        int cmdOK=0,nOk=0;
        if (ui->checkBoxShowNavMessageTypeGPS->isChecked()) {
            for (int i=0; i<ui->tableWidgetShowNavMessageTypeGPS->columnCount();i++){
                if (ui->tableWidgetShowNavMessageTypeGPS->item(0,i)->text()!=NavMessageTypes[GPS][0][i]) cmdOK=1;
                if (ui->tableWidgetShowNavMessageTypeGPS->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetShowNavMessageTypeGPS->item(0,i)->text() + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                if ( nOk==ui->tableWidgetShowNavMessageTypeGPS->columnCount() && ui->tableWidgetShowNavMessageTypeGPS->item(0,0)->text()=="CNAV" ) {
                    *saveString += "-model:brdc:gps PreferCNAV\n";
                    *runString << "-model:brdc:gps" << "PreferCNAV";
                } else {
                    *saveString += "-model:brdc:gps " + cmdNavMT + "\n";
                    *runString << "-model:brdc:gps" << cmdNavMT;
                }
            }
            else if (WriteAllParameters){
                *saveString += "-model:brdc:gps PreferLNAV\n";
                *runString << "-model:brdc:gps" << "PreferLNAV";
            }
        }
        //Galileo
        if (ui->checkBoxShowNavMessageTypeGalileo->isChecked()) {
            cmdNavMT="";
            cmdNavMT2="";
            cmdOK=0;
            nOk=0;
            for (int i=0; i<ui->tableWidgetShowNavMessageTypeGalileo->columnCount();i++){
                if (ui->tableWidgetShowNavMessageTypeGalileo->item(0,i)->text()!=NavMessageTypes[Galileo][0][i]) cmdOK=1;
                if (ui->tableWidgetShowNavMessageTypeGalileo->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetShowNavMessageTypeGalileo->item(0,i)->text() + ",";
                if (i>0) {
                    cmdNavMT2 += ui->tableWidgetShowNavMessageTypeGalileo->item(0,i)->text() + ",";
                }
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                cmdNavMT2.chop(1);
                if ( nOk==ui->tableWidgetShowNavMessageTypeGalileo->columnCount() && ui->tableWidgetShowNavMessageTypeGalileo->item(0,0)->text()=="FNAV" && cmdNavMT2== GalINAVDefaultOrder ) {
                    *saveString += "-model:brdc:gal PreferFNAV\n";
                    *runString << "-model:brdc:gal" << "PreferFNAV";
                } else {
                    if (cmdNavMT==GalINAVDefaultOrder) {
                        *saveString += "-model:brdc:gal INAV\n";
                        *runString << "-model:brdc:gal" << "INAV";
                    } else {
                        *saveString += "-model:brdc:gal " + cmdNavMT + "\n";
                        *runString << "-model:brdc:gal" << cmdNavMT;
                    }
                }
            }
            else if (WriteAllParameters){
                *saveString += "-model:brdc:gal PreferINAV\n";
                *runString << "-model:brdc:gal" << "PreferINAV";
            }
        }
        //GLONASS
        if ( 0 ){
            cmdNavMT="";
            cmdOK=0;
            nOk=0;
            for (int i=0; i<ui->tableWidgetShowNavMessageTypeGLONASS->columnCount();i++){
                if (ui->tableWidgetShowNavMessageTypeGLONASS->item(0,i)->text()!=NavMessageTypes[GLONASS][0][i]) cmdOK=1;
                if (ui->tableWidgetShowNavMessageTypeGLONASS->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetShowNavMessageTypeGLONASS->item(0,i)->text() + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                *saveString += "-model:brdc:glo " + cmdNavMT + "\n";
                *runString << "-model:brdc:glo" << cmdNavMT;
            }
            else if (WriteAllParameters){
                *saveString += "-model:brdc:glo FDMA\n";
                *runString << "-model:brdc:glo" << "FDMA";
            }
        }
        //GEO
        if ( 0 ){
            cmdNavMT="";
            cmdOK=0;
            nOk=0;
            for (int i=0; i<ui->tableWidgetShowNavMessageTypeGEO->columnCount();i++){
                if (ui->tableWidgetShowNavMessageTypeGEO->item(0,i)->text()!=NavMessageTypes[GEO][0][i]) cmdOK=1;
                if (ui->tableWidgetShowNavMessageTypeGEO->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetShowNavMessageTypeGEO->item(0,i)->text() + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                *saveString += "-model:brdc:geo " + cmdNavMT + "\n";
                *runString << "-model:brdc:geo" << cmdNavMT;
            }
            else if (WriteAllParameters){
                *saveString += "-model:brdc:geo CNAV\n";
                *runString << "-model:brdc:geo" << "CNAV";
            }
        }
        //BDS
        if (ui->checkBoxShowNavMessageTypeBDS->isChecked()) {
            cmdNavMT="";
            cmdOK=0;
            nOk=0;
            for (int i=0; i<ui->tableWidgetShowNavMessageTypeBDS->columnCount();i++){
                if (ui->tableWidgetShowNavMessageTypeBDS->item(0,i)->text()!=NavMessageTypes[BDS][0][i]) cmdOK=1;
                if (ui->tableWidgetShowNavMessageTypeBDS->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetShowNavMessageTypeBDS->item(0,i)->text() + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                *saveString += "-model:brdc:bds " + cmdNavMT + "\n";
                *runString << "-model:brdc:bds" << cmdNavMT;
            }
            else if (WriteAllParameters){
                *saveString += "-model:brdc:bds D1\n";
                *runString << "-model:brdc:bds" << "D1";
            }
        }
        //QZSS
        if (ui->checkBoxShowNavMessageTypeQZSS->isChecked()) {
            cmdNavMT="";
            cmdOK=0;
            nOk=0;
            for (int i=0; i<ui->tableWidgetShowNavMessageTypeQZSS->columnCount();i++){
                if (ui->tableWidgetShowNavMessageTypeQZSS->item(0,i)->text()!=NavMessageTypes[QZSS][0][i]) cmdOK=1;
                if (ui->tableWidgetShowNavMessageTypeQZSS->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetShowNavMessageTypeQZSS->item(0,i)->text() + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                *saveString += "-model:brdc:qzs " + cmdNavMT + "\n";
                *runString << "-model:brdc:qzs" << cmdNavMT;
            }
            else if (WriteAllParameters){
                *saveString += "-model:brdc:qzs LNAV\n";
                *runString << "-model:brdc:qzs" << "LNAV";
            }
        }
        //IRNSS
        if ( 0 ){
            cmdNavMT="";
            cmdOK=0;
            nOk=0;
            for (int i=0; i<ui->tableWidgetShowNavMessageTypeIRNSS->columnCount();i++){
                if (ui->tableWidgetShowNavMessageTypeIRNSS->item(0,i)->text()!=NavMessageTypes[IRNSS][0][i]) cmdOK=1;
                if (ui->tableWidgetShowNavMessageTypeIRNSS->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetShowNavMessageTypeIRNSS->item(0,i)->text() + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                *saveString += "-model:brdc:irnss " + cmdNavMT + "\n";
                *runString << "-model:brdc:irnss" << cmdNavMT;
            }
            else if (WriteAllParameters){
                *saveString += "-model:brdc:irnss CNAV\n";
                *runString << "-model:brdc:irnss" << "CNAV";
            }
        }
    } else if ( ui->radioButtonOrbitPrecise1filesShowOrbitFile->isChecked()==true) {
        //File is SP3
        if ( ui->lineEditPreciseFilesShowOrbitSP3File->text() == "" ) {
            *errorString += "SP3 source file is empty.\n";
        } else if (  this->fileExists(ui->lineEditPreciseFilesShowOrbitSP3File->text()) ==false) {
            *errorString += "SP3 source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPreciseFilesShowOrbitSP3File->text())==1) {
            *errorString += "SP3 source file has non ASCII characters\n";
        } else {
            *saveString +=  "-input:sp3 " + ui->lineEditPreciseFilesShowOrbitSP3File->text() + "\n";
            *runString <<  "-input:sp3" << ui->lineEditPreciseFilesShowOrbitSP3File->text();
        }
        SP3File=1;
        //Check ANTEX
        if ( ui->checkBoxAntexShowOrbitFile->isChecked()==true) {
            if ( ui->lineEditAntexShowOrbitFile->text() == "" ) {
                *errorString += "ANTEX option selected, but source file is empty.\n";
            } else if  (  this->fileExists(ui->lineEditAntexShowOrbitFile->text() )==false) {
                *errorString += "ANTEX source file does not exist.\n";
            } else if (this->checknonASCIIcharacters(ui->lineEditAntexShowOrbitFile->text())==1) {
                *errorString += "ANTEX source file has non ASCII characters\n";
            } else {
                *saveString +=  "-input:ant " + ui->lineEditAntexShowOrbitFile->text() +"\n";
                *runString <<  "-input:ant" << ui->lineEditAntexShowOrbitFile->text();
            }
        } else {
            *saveString += "--model:satphasecenter\n";
            *runString << "--model:satphasecenter";
        }
    } else if ( ui->radioButtonOrbitPrecise2filesShowOrbitFile->isChecked()==true ) {
        //File is SP3 + CLK
        if ( ui->lineEditPreciseFilesShowOrbitOrbFile->text() == "" ) {
            *errorString += "Orbit SP3 source file is empty.\n";
        } else if ( this->fileExists( ui->lineEditPreciseFilesShowOrbitOrbFile->text() )==false) {
            *errorString += "Orbit SP3 source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPreciseFilesShowOrbitOrbFile->text())==1) {
            *errorString += "Orbit source file has non ASCII characters\n";
        } else {
            *saveString +=  "-input:orb " + ui->lineEditPreciseFilesShowOrbitOrbFile->text() + "\n";
            *runString <<  "-input:orb" << ui->lineEditPreciseFilesShowOrbitOrbFile->text();
        }
        SP3File=1;
        if ( ui->lineEditPreciseFilesShowOrbitClkFile->text() == "" ) {
            *errorString += "Clock source file is empty.\n";
        } else if (  this->fileExists(ui->lineEditPreciseFilesShowOrbitClkFile->text())==false) {
            *errorString += "Clock source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPreciseFilesShowOrbitClkFile->text())==1) {
            *errorString += "Clock source file has non ASCII characters\n";
        } else {
            *saveString +=  "-input:clk " + ui->lineEditPreciseFilesShowOrbitClkFile->text() + "\n";
            *runString <<  "-input:clk" << ui->lineEditPreciseFilesShowOrbitClkFile->text();
        }
        //Check ANTEX
        if ( ui->checkBoxAntexShowOrbitFile->isChecked()==true) {
            if ( ui->lineEditAntexShowOrbitFile->text() == "" ) {
                *errorString += "ANTEX option selected, but source file is empty.\n";
            } else if  ( this->fileExists(ui->lineEditAntexShowOrbitFile->text() )==false) {
                *errorString += "ANTEX source file does not exist.\n";
            } else if (this->checknonASCIIcharacters(ui->lineEditAntexShowOrbitFile->text())==1) {
                *errorString += "ANTEX source file has non ASCII characters\n";
            } else {
                *saveString +=  "-input:ant " + ui->lineEditAntexShowOrbitFile->text() + "\n";
                *runString <<  "-input:ant" << ui->lineEditAntexShowOrbitFile->text();
            }
        } else {
            *saveString += "--model:satphasecenter\n";
            *runString << "--model:satphasecenter";
        }
    }

    //Reference Position
    if (ui->groupBoxEleAziSpecify->isChecked()){
        if (ui->radioButtonEleAziSpecifyUserCartesian->isChecked()==true) {
            if ( ui->lineEditEleAziSpecifyX->text() == "" || ui->lineEditEleAziSpecifyY->text() == "" || ui->lineEditEleAziSpecifyZ->text() == "" ) {
                *errorString += "X Y and Z coordinates are required inputs if 'Specify - User defined' is set [In the Input Section - A Priori Receiver Position From].\n";
            } else if (ui->lineEditEleAziSpecifyX->text().toDouble() == 0. || ui->lineEditEleAziSpecifyY->text().toDouble() == 0. || ui->lineEditEleAziSpecifyZ->text().toDouble() == 0.) {
                *errorString += "X Y and Z coordinates cannot be 0,0,0.\n";
            } else {
                *saveString += "-pre:setrecpos Set " + ui->lineEditEleAziSpecifyX->text() + " " + ui->lineEditEleAziSpecifyY->text() + " " + ui->lineEditEleAziSpecifyZ->text() + "\n";
                *runString << "-pre:setrecpos" << "Set"<< ui->lineEditEleAziSpecifyX->text() << ui->lineEditEleAziSpecifyY->text() << ui->lineEditEleAziSpecifyZ->text();
            }
        } else {
            if ( ui->lineEditEleAziSpecifyLon->text() == "" || ui->lineEditEleAziSpecifyLat->text() == "" || ui->lineEditEleAziSpecifyHeight->text() == "" ) {
                *errorString += "Longitude, latitude and height coordinates are required inputs if 'Specify - User defined' is set [In the Input Section - A Priori Receiver Position From].\n";
            } else if  (ui->lineEditEleAziSpecifyLon->text().toDouble()<-180. || ui->lineEditEleAziSpecifyLon->text().toDouble()>180) {
                    *errorString += "Longitude coordinate must be in the range [-180..180] degrees.\n";
            } else if  (ui->lineEditEleAziSpecifyLat->text().toDouble()<-90. || ui->lineEditEleAziSpecifyLat->text().toDouble()>90) {
                    *errorString += "Latitude coordinate must be in the range [-90..90] degrees.\n";
            } else if ( ui->lineEditEleAziSpecifyHeight->text().toDouble() < -10000. ) {
                    *errorString += "Height coordinate cannot be lower than -10 kilometres.\n";
            } else {
                *saveString += "-pre:setrecpos SetGeod " + ui->lineEditEleAziSpecifyLon->text() + " " + ui->lineEditEleAziSpecifyLat->text() + " " + ui->lineEditEleAziSpecifyHeight->text() + "\n";
                *runString << "-pre:setrecpos" << "SetGeod" << ui->lineEditEleAziSpecifyLon->text() << ui->lineEditEleAziSpecifyLat->text() << ui->lineEditEleAziSpecifyHeight->text();
            }
        }
    }

    ///Check modeling options
    //Decimation
    if (ui->lineEditDecimationShowOrbit->text()=="") {
        *errorString += "Data Decimation value is empty.\n";
    } else if (ui->lineEditDecimationShowOrbit->text().toDouble()==0.) {
        *errorString += "Data Decimation can not be set to 0.\n";
    } else if (ui->lineEditDecimationShowOrbit->text().toDouble()!=300.) {
        //By default it is set to 300
        *saveString +=  "-pre:dec " + ui->lineEditDecimationShowOrbit->text() + "\n";
        *runString <<  "-pre:dec" << ui->lineEditDecimationShowOrbit->text();
    }

    //Check start time is greater than end time (if both are enabled)
    if ( ui->checkBoxStartTimeShowOrbits->isChecked()==true && ui->checkBoxEndTimeShowOrbits->isChecked()==true) {
        date = ui->StartTimeShowOrbits->date();
        time = ui->StartTimeShowOrbits->time();
        if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && time.hour() == 0 && time.minute()==0 && time.second()==0) {
            *errorString += "Date (DD/MM/YYYY) and GPS Time (HH:MM:SS) are a required input if 'Start Time' is set.\n";
            badDate=1;
        }
        date = ui->EndTimeShowOrbits->date();
        time = ui->EndTimeShowOrbits->time();
        if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && time.hour() == 0 && time.minute()==0 && time.second()==0) {
            *errorString += "Date (DD/MM/YYYY) and GPS Time (HH:MM:SS) are a required input if 'End Time' is set.\n";
            badDate=1;
        }
        if (badDate==0) {
            if (ui->StartTimeShowOrbits->date().operator >(ui->EndTimeShowOrbits->date()) ) {
                *errorString += "'End Time' must be greater than the 'Start Time' if both are set.\n";
                badDate=1;
            } else if (ui->StartTimeShowOrbits->date().operator ==(ui->EndTimeShowOrbits->date()) ) {
                if (ui->StartTimeShowOrbits->time().operator >(ui->EndTimeShowOrbits->time()) ) {
                    *errorString += "'End Time' must be greater than the 'Start Time' if both are set.\n";
                    badDate=1;
                }
            }
        }
    }

    //Start time
    if (ui->checkBoxStartTimeShowOrbits->isChecked()==true) {
        date = ui->StartTimeShowOrbits->date();
        time = ui->StartTimeShowOrbits->time();
        if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && time.hour() == 0 && time.minute()==0 && time.second()==0) {
            if (badDate==0) {
                *errorString += "Date (DD/MM/YYYY) and GPS Time (HH:MM:SS) are a required input if 'Start Time' is set.\n";
            }
        } else {
                *saveString += "-pre:starttime " + date.toString("yyyy/MM/dd") + " " + time.toString("HH:mm:ss") + "\n";
                *runString << "-pre:starttime" << date.toString("yyyy/MM/dd") << time.toString("HH:mm:ss");
        }
    }

    //End time
    if (ui->checkBoxEndTimeShowOrbits->isChecked()==true) {
        date = ui->EndTimeShowOrbits->date();
        time = ui->EndTimeShowOrbits->time();
        if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && time.hour() == 0 && time.minute()==0 && time.second()==0) {
            if (badDate==0) {
                *errorString += "Date (DD/MM/YYYY) and GPS Time (HH:MM:SS) are a required input if 'End time' is set.\n";
            }
        } else {
            *saveString += "-pre:endtime " + date.toString("yyyy/MM/dd") + " " + time.toString("HH:mm:ss") + "\n";
            *runString << "-pre:endtime" << date.toString("yyyy/MM/dd") << time.toString("HH:mm:ss");
        }
    }

    //Clock correction. By default enabled
    if (ui->checkBoxSatClockOffsetShowOrbit->isChecked()==false) {
        *saveString +=  "--model:satclocks\n";
        *runString <<  "--model:satclocks";
    }

    //Broadcast transmission time. By default enabled
    if (ui->checkBoxCheckBroadcastTransmissionTimeShowOrbit->isChecked()==false) {
        *saveString +=  "--model:brdctranstime\n";
        *runString <<  "--model:brdctranstime";
    }

    // Precise products interpolation data (only when a precise product is given)
    if ( SP3File==1) {
        if ( ui->lineEditOrbitInterpolationDegreeShowOrbit->text() == "" ) {
            *errorString += "Orbit interpolation degree cannot be empty.\n";
        } else if ( ui->lineEditOrbitInterpolationDegreeShowOrbit->text().toInt() == 0 ) {
            *errorString += "Orbit interpolation degree cannot be 0.\n";
        } else if ( ui->lineEditOrbitConsecutiveGapsShowOrbit->text() == "" ) {
            *errorString += "Number of consecutive gaps in orbit interpolation cannot be empty.\n";
        } else if ( ui->lineEditOrbitMaxGapsShowOrbit->text() == "" ) {
            *errorString += "Number of maximum gaps in orbit interpolation cannot be empty.\n";
        } else if ( ui->lineEditClockInterpolationDegreeShowOrbit->text() == "" ) {
            *errorString += "Clock interpolation degree cannot be empty.\n";
        } else if ( ui->lineEditClockConsecutiveGapsShowOrbit->text() == "" ) {
            *errorString += "Number of consecutive gaps in clock interpolation cannot be empty.\n";
        } else if ( ui->lineEditClockMaxGapsShowOrbit->text() == "" ) {
            *errorString += "Number of maximum gaps in clock interpolation cannot be empty.\n";
        } else if ( ui->lineEditOrbitMaxGapsShowOrbit->text().toInt()< ui->lineEditOrbitConsecutiveGapsShowOrbit->text().toInt()) {
            *errorString += "Number of maximum gaps in orbit interpolation must be equal or greater than then number of consecutive gaps.\n";
        } else if ( ui->lineEditClockMaxGapsShowOrbit->text().toInt()< ui->lineEditClockConsecutiveGapsShowOrbit->text().toInt()) {
            *errorString += "Number of maximum gaps in clock interpolation must be equal or greater than then number of consecutive gaps.\n";
        } else {
            if ( ui->lineEditOrbitInterpolationDegreeShowOrbit->text().toInt() !=10) {
                *saveString += "-model:orbit:deg " + ui->lineEditOrbitInterpolationDegreeShowOrbit->text() + "\n";
                *runString << "-model:orbit:deg" << ui->lineEditOrbitInterpolationDegreeShowOrbit->text();
            }
            if (ui->lineEditOrbitConsecutiveGapsShowOrbit->text().toInt()!=8) {
                *saveString += "-model:orbmaxgaps " + ui->lineEditOrbitConsecutiveGapsShowOrbit->text() + "\n";
                *runString << "-model:orbmaxgaps" << ui->lineEditOrbitConsecutiveGapsShowOrbit->text();
            }
            if (ui->lineEditOrbitMaxGapsShowOrbit->text().toInt()!=16) {
                *saveString += "-model:orbtotmaxgaps " + ui->lineEditOrbitMaxGapsShowOrbit->text() + "\n";
                *runString << "-model:orbtotmaxgaps" << ui->lineEditOrbitMaxGapsShowOrbit->text();
            }
            if ( ui->lineEditClockInterpolationDegreeShowOrbit->text().toInt()!=1) {
                *saveString += "-model:clock:deg " + ui->lineEditClockInterpolationDegreeShowOrbit->text() + "\n";
                *runString << "-model:clock:deg" << ui->lineEditClockInterpolationDegreeShowOrbit->text();
            }
            if (ui->lineEditClockConsecutiveGapsShowOrbit->text().toInt()!=2) {
                *saveString += "-model:clkmaxgaps " + ui->lineEditClockConsecutiveGapsShowOrbit->text() + "\n";
                *runString << "-model:clkmaxgaps" << ui->lineEditClockConsecutiveGapsShowOrbit->text();
            }
            if (ui->lineEditClockMaxGapsShowOrbit->text().toInt()!=4) {
                *saveString += "-model:clktotmaxgaps " + ui->lineEditClockMaxGapsShowOrbit->text() + "\n";
                *runString << "-model:clktotmaxgaps" << ui->lineEditClockMaxGapsShowOrbit->text();
            }
        }
        //Current or Previous sample interpolation option for concatenated orbit files
        if (ui->radioButtonOrbitCurrentDayShowOrbit->isChecked()==true) {
            //This is not the default option
            *saveString += "-model:orbprevsample\n";
            *runString << "-model:orbprevsample";
        }
        if (ui->radioButtonClockCurrentDayShowOrbit->isChecked()==true) {
            //This is not the default option
            *saveString += "-model:clkprevsample\n";
            *runString << "-model:clkprevsample";
        }
    }

    //Check Output file
    if ( ui->lineEditOutputFileShowOrbit->text() == "" ) {
        *errorString += "Output file is empty.\n";
    } else if (this->checknonASCIIcharacters(ui->lineEditOutputFileShowOrbit->text())==1) {
        *errorString += "Output file has non ASCII characters\n";
    } else {
        *saveString += "-output:file " + ui->lineEditOutputFileShowOrbit->text() + "\n";
        *runString << "-output:file" << ui->lineEditOutputFileShowOrbit->text();
    }

    //Check output messages
    //All show orbit messages are by default enabled
    if (ui->checkBoxPrintInfoShowOrbit->isChecked()==false) {
        *saveString += "--print:info\n";
        *runString << "--print:info";
    }
    if (ui->checkBoxPrintSatpvtShowOrbit->isChecked()==false) {
       *saveString += "--print:satpvt\n";
       *runString << "--print:satpvt";
       NumMessages--;
    }

    //Clock units
    if (ui->radioButtonNanosecondsUnitOutputClockSATPVT->isChecked()==true) {
        *saveString += "-print:clkns\n";
        *runString << "-print:clkns";
    } else if (WriteAllParameters==1) {
        *saveString += "--print:clkns\n";
        *runString << "--print:clkns";
    }

    //V5 messages
    if (this->v5Message>0) {
        *saveString += "-print:v5format\n";
        *runString << "-print:v5format";
    }
    if (NumMessages==0) {
        *errorString += "Output Message SATPVT must be selected.\n";
    }
}

void gLAB_GUI::showOrbitsLoadParameters(QFile *file) {

    QString line;
    QString option;
    QString userInput;
    QString errorString = "";
    QString warningString = "";
    QString userInputSingleSpace;
    QStringList ParametersList;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QTextStream InputFile(file);
    InputFile.setAutoDetectUnicode(true);
    QDate date;
    QTime hour;

    int numNav=0;
    int numSP3=0;
    int numOrb=0;
    int numClk=0;
    int numAnt=0;
    int numInputOrbFiles=0;
    int noAntParameter=0;
    int HashPos;
    int year, month,day, doy, hour2, minute, second,sod,GPSWeek,sow;
    int ValidDate, addDay, leapYear;
    int daysmonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int daysmonthLeapYear[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    //First loop: Check for errors
    while ( !InputFile.atEnd() ) {
        line = QString(InputFile.readLine());
        if ( line == "") continue; //Do not erase this instruction or it will crash in Windows if the file has empty lines
        if ( line.at(0) == '#' || line.at(0) == '\n' || line.at(0) == '\r') continue;
        line.remove(QRegularExpression("^\\s+"));
        if ( line == "") continue; //Do not erase this instruction or it will crash in Windows if the file has empty lines
        if ( line.at(0) == '#' || line.at(0) == '\n' || line.at(0) == '\r') continue;
        HashPos=line.indexOf("#");
        if (HashPos!=-1) line.remove(HashPos,line.length()-HashPos); //Remove comments from line
        if ( line.at(0) == '\n' || line.at(0) == '\r') continue;
        option = line.section(" ", 0, 0);
        option.remove(QRegularExpression("[\\n\\t\\r\"']"));
        userInput = line.section(" ", 1);
        userInput.remove(QRegularExpression("[\\n\\t\\r\"']"));
        userInput.remove(QRegularExpression("^\\s+"));
        userInput.remove(QRegularExpression("\\s+$"));
        userInputSingleSpace = userInput;
        userInputSingleSpace.replace(QRegularExpression("\\s+")," ");
        userInputSingleSpace.remove(QRegularExpression("\\s$"));
        ParametersList.clear();
        ParametersList = userInput.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);

        if ( QString::compare(option, "-input:nav", Qt::CaseInsensitive)==0 ) {
            numNav++;
            numInputOrbFiles++;
            checkConfigurationFileInputFilePaths("Navigation", &warningString,&errorString,userInput);
        } else if ( QString::compare(option, "-input:sp3", Qt::CaseInsensitive)==0  ) {
            numSP3++;
            numInputOrbFiles++;
            checkConfigurationFileInputFilePaths("SP3", &warningString,&errorString,userInput);
        } else if ( QString::compare(option, "-input:orb", Qt::CaseInsensitive)==0  ) {
            numOrb++;
            numInputOrbFiles++;
            checkConfigurationFileInputFilePaths("SP3 orbit", &warningString,&errorString,userInput);
        } else if ( QString::compare(option, "-input:clk", Qt::CaseInsensitive)==0 ) {
            numClk++;
            checkConfigurationFileInputFilePaths("Clock", &warningString,&errorString,userInput);
        } else if ( QString::compare(option, "-input:ant", Qt::CaseInsensitive)==0 ) {
            numAnt++;
            checkConfigurationFileInputFilePaths("ANTEX", &warningString,&errorString,userInput);
        } else if ( QString::compare(option, "--model:satphasecenter", Qt::CaseInsensitive)==0 ) {
            noAntParameter=1;
        } else if ( QString::compare(option, "-output:file", Qt::CaseInsensitive)==0 ) {
            numAnt++;
            checkConfigurationFileInputFilePaths("Output", &warningString,&errorString,userInput);
        } else if ( QString::compare(option, "--model:satphasecenter", Qt::CaseInsensitive)==0 ) {
            noAntParameter=1;
        }
    }

    //Check for errors in number of files
    if (numInputOrbFiles>1) {
        //More than one orbit file given
        if (numNav>1) {
            errorString += "More than one navigation file ('-input:nav' option) is provided.\n";
        }
        if (numSP3>1) {
            errorString += "More than one SP3 file ('-input:sp3' option) is provided.\n";
        }
        if (numOrb>1) {
            errorString += "More than one orbit SP3 file ('-input:orb' option) is provided.\n";
        }
        if (numNav>0 && numSP3>0 && numOrb>0) {
            errorString += "Navigation file, SP3 file and orbit SP3 file were provided, but only one type can be given.\n";
        } else if (numNav>0 && numSP3>0) {
            errorString += "Navigation file and SP3 file were provided, but only one type can be given.\n";
        } else if (numNav>0 && numOrb>0) {
            errorString += "Navigation file and orbit SP3 file were provided, but only one type can be given.\n";
        } else if (numSP3>0 && numOrb>0) {
            errorString += "Orbit & clock SP3 file and orbit SP3 file were provided, but only one type can be given.\n";
        }
    }
    //Check if a orbit SP3 was given but not a CLK file
    if (numOrb>0 && numClk==0) {
        warningString += "Orbit SP3 file provided, but no clock file given.\n";
    }
    //Check if a CLK file is provided, but no orbit file is given
    if (numOrb==0 && numClk>0) {
        warningString += "Clock file provided, but no orbit SP3 file given.\n";
    }
    //Check if more than ANTEX was given
    if (numAnt>1) {
        errorString += "More than one ANTEX file ('-input:ant' option) is provided.\n";
    }
    //Check if ANTEX file provided, but option for no ANTEX provided
    if (numAnt>0 && noAntParameter==1) {
        warningString += "ANTEX file provided, but also option to not to use ANTEX is provided. Last action read will prevail.\n";
    }

    //If errors ocurred, show them and return
    if (!errorString.isEmpty()) {
        messageBox.setWindowTitle("Errors found");
        messageBox.setText("gLAB did not load the the configuration file due to the following errors:\n\n" + errorString);
        messageBox.setIcon(QMessageBox::Critical);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBox.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        messageBox.exec();
        return;
    }
    //Second loop: Load parameters
    file->seek(0); //Go back to beginning of file
    setInitialShowOrbitValues(); //Set default values in showOrbit page

    while ( !InputFile.atEnd() ) {
        line = QString(InputFile.readLine());
        if ( line == "") continue; //Do not erase this instruction or it will crash in Windows if the file has empty lines
        if ( line.at(0) == '#' || line.at(0) == '\n' || line.at(0) == '\r') continue;
        line.remove(QRegularExpression("^\\s+"));
        if ( line == "") continue; //Do not erase this instruction or it will crash in Windows if the file has empty lines
        if ( line.at(0) == '#' || line.at(0) == '\n' || line.at(0) == '\r') continue;
        HashPos=line.indexOf("#");
        if (HashPos!=-1) line.remove(HashPos,line.length()-HashPos); //Remove comments from line
        if ( line.at(0) == '\n' || line.at(0) == '\r') continue;
        option = line.section(" ", 0, 0);
        option.remove(QRegularExpression("[\\n\\t\\r\"']"));
        userInput = line.section(" ", 1);
        userInput.remove(QRegularExpression("[\\n\\t\\r\"']"));
        userInput.remove(QRegularExpression("^\\s+"));
        userInput.remove(QRegularExpression("\\s+$"));
        userInputSingleSpace = userInput;
        userInputSingleSpace.replace(QRegularExpression("\\s+")," ");
        userInputSingleSpace.remove(QRegularExpression("\\s$"));
        ParametersList.clear();
        ParametersList = userInput.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);

        if ( QString::compare(option, "-input:nav", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                this->on_radioButtonOrbitNavShowOrbitFile_clicked();
                ui->lineEditNavShowOrbitFile->setText(userInput);
            }
        } else if ( QString::compare(option, "-input:sp3", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                this->on_radioButtonOrbitPrecise1filesShowOrbitFile_clicked();
                ui->lineEditPreciseFilesShowOrbitSP3File->setText(userInput);
            }
        } else if ( QString::compare(option, "-input:orb", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                this->on_radioButtonOrbitPrecise2filesShowOrbitFile_clicked();
                ui->lineEditPreciseFilesShowOrbitOrbFile->setText(userInput);
            }
        } else if ( QString::compare(option, "-input:clk", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                this->on_radioButtonOrbitPrecise2filesShowOrbitFile_clicked();
                ui->lineEditPreciseFilesShowOrbitClkFile->setText(userInput);
            }
        } else if ( QString::compare(option, "-input:ant", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                this->on_checkBoxAntexShowOrbitFile_clicked(true);
                ui->lineEditAntexShowOrbitFile->setText(userInput);
            }
        } else if ( QString::compare(option, "-pre:dec", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                    warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                } else {
                   ui->lineEditDecimationShowOrbit->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                }
            }
        } else if ( QString::compare(option, "--pre:dec", Qt::CaseInsensitive)==0 ) {
            warningString += "Parameter '" + option + "' is not valid in show orbit mode. It was skipped.\n";
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "-pre:setrecpos", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()<3) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            }
            double radius=0;
            if (QString::compare(ParametersList[0], "Set", Qt::CaseInsensitive)==0 ) {
                //Specify User defined Cartesian
                if (ParametersList.count()<4) {
                    warningString += "Parameter '" + option + "' Set has missing values. It was skipped.\n";
                } else {
                    extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                    radius=sqrt(pow(QString("%1").arg(ParametersList[1]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[2]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[3]).replace(",","").toDouble(),2));
                    if(radius<MIN_EARTH_RADIUS-1000.) {
                        warningString += "Parameter '" + option + " Set' cannot have a reference position below Earth surface. It was skipped.\n";
                    } else {
                        this->on_groupBoxEleAziSpecify_clicked(true);
                        this->on_radioButtonEleAziSpecifyUserCartesian_clicked();
                        ui->lineEditEleAziSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                        ui->lineEditEleAziSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                        ui->lineEditEleAziSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                    }
                }
            } else if (QString::compare(ParametersList[0], "SetGeod", Qt::CaseInsensitive)==0 ) {
                //Specify User defined Geodetic
                if (ParametersList.count()<4) {
                    warningString += "Parameter '" + option + " SetGeod' has missing values. It was skipped.\n";
                } else {
                    extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                    if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                        warningString += "Parameter '" + option + " SetGeod' must have a longitude range of [-180..180] degrees. It was skipped.\n";
                    } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                        warningString += "Parameter '" + option + " SetGeod' must have a latitude range of [-90..90] degrees. It was skipped.\n";
                    } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                        warningString += "Parameter '" + option + " SetGeod' must have a height value greater than -10 kilometres. It was skipped.\n";
                    } else {
                        this->on_groupBoxEleAziSpecify_clicked(true);
                        this->on_radioButtonEleAziSpecifyUserGeodetic_clicked();
                        ui->lineEditEleAziSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                        ui->lineEditEleAziSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                        ui->lineEditEleAziSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                    }
                }
            } else {
                //Specify User defined Cartesian
                if (ParametersList.count()<3) {
                    warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                } else {
                    extraArgumentsToWarningStr(3,&warningString,option,ParametersList);
                    radius=sqrt(pow(QString("%1").arg(ParametersList[0]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[1]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[2]).replace(",","").toDouble(),2));
                    if(radius<MIN_EARTH_RADIUS-1000.) {
                        warningString += "Parameter '" + option + "' cannot have a reference position below Earth surface. It was skipped.\n";
                    } else {
                        this->on_groupBoxEleAziSpecify_clicked(true);
                        this->on_radioButtonEleAziSpecifyUserCartesian_clicked();
                        ui->lineEditEleAziSpecifyX->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        ui->lineEditEleAziSpecifyY->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                        ui->lineEditEleAziSpecifyZ->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                    }
                }
            }
        } else if ( QString::compare(option, "-pre:starttime", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()<2) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                ValidDate=1;
                addDay=0;
                leapYear=0;
                year=0;
                month=0;
                day=0;
                hour2=-1;
                minute=-1;
                second=-1;
                extraArgumentsToWarningStr(2,&warningString,option,ParametersList);
                if(userInputSingleSpace.section(" ", 1,1).contains(":")==true) {
                    //Time has ":" symbol.
                    if(userInputSingleSpace.section(" ", 0,0).contains("/")==true) {
                        //Time is in YYYY/MM/DD HH:MM:SS format
                        if(userInputSingleSpace.section(" ", 0,0).length()!=10) {
                            //Invalid date
                            warningString += "Parameter '" + option + "' has an invalid date. It was skipped.\n";
                            ValidDate=0;
                        } else {
                             if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                                 warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                                 ValidDate=0;
                             } else {
                                 year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                                 month=userInputSingleSpace.section(" ", 0,0).mid(5,2).toInt();
                                 day=userInputSingleSpace.section(" ", 0,0).mid(8,2).toInt();
                             }
                        }
                    } else {
                        //Time is in YYYYMMDD HH:MM:SS format
                        if(userInputSingleSpace.section(" ", 0,0).length()!=8) {
                            //Invalid date
                            warningString += "Parameter '" + option + "' has an invalid date. It was skipped.\n";
                            ValidDate=0;
                        } else {
                            if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                                warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                                ValidDate=0;
                            } else {
                                year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                                month=userInputSingleSpace.section(" ", 0,0).mid(4,2).toInt();
                                day=userInputSingleSpace.section(" ", 0,0).mid(6,2).toInt();
                            }
                        }
                    }
                    if (ValidDate==1) {
                        //Check date values and time length
                        if(year<=1970) {
                            warningString += "Parameter '" + option + "' has date prior to 1970. It was skipped.\n";
                            ValidDate=0;
                        } else {
                            //Check leap year
                            if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 ) {
                                leapYear=1;
                            }
                        }
                        if(month<1||month>12) {
                            warningString += "Parameter '" + option + "' has an invalid month. It was skipped.\n";
                            ValidDate=0;
                        }
                        if (day<1||day>31|| (leapYear==1 && day>daysmonthLeapYear[month]) || (leapYear==0 && day>daysmonth[month])) {
                            warningString += "Parameter '" + option + "' has an invalid day. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                            warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                            ValidDate=0;
                        }
                    }
                    if (ValidDate==1) {
                        //Read time in HH:MM:SS format and check values
                        hour2=userInputSingleSpace.section(" ", 1,1).left(2).toInt();
                        minute=userInputSingleSpace.section(" ", 1,1).mid(3,2).toInt();
                        second=userInputSingleSpace.section(" ", 1,1).mid(6,2).toInt();
                        if(hour2<0||hour2>24) {
                            warningString += "Parameter '" + option + "' has an invalid hour. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(minute<0||minute>60) {
                            warningString += "Parameter '" + option + "' has an invalid minute. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(second<0||second>60) {
                            warningString += "Parameter '" + option + "' has an invalid second. It was skipped.\n";
                            ValidDate=0;
                        }
                    }
                     if (ValidDate==1) {
                         if(second==60) {
                             second-=60;
                             minute++;
                         }
                         if(minute==60) {
                             minute-=60;
                             hour2++;
                         }
                         if(hour2==24) {
                             hour2-=24;
                             addDay=1;
                         }
                         date=QDate(year,month,day);
                         if(addDay==1) {
                            date=date.addDays(qint64(1));
                         }
                         hour=QTime(hour2,minute,second);
                         ui->StartTimeShowOrbits->setDate(date);
                         ui->StartTimeShowOrbits->setTime(hour);
                         this->on_checkBoxStartTimeShowOrbits_clicked(true);
                     }
                } else {
                    //Time can be in YYYY/DoY or GPSWeek
                    if(userInputSingleSpace.section(" ", 0,0).contains("/")==true) {
                        //Date is in YYYY/DoY SoD format
                        year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                        doy=userInputSingleSpace.section(" ", 0,0).mid(5).toInt();
                        sod=userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt();
                        if(year<=1970) {
                            warningString += "Parameter '" + option + "' has date prior to 1970. It was skipped.\n";
                            ValidDate=0;
                        } else {
                            //Check leap year
                            if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 ) {
                                leapYear=1;
                            }
                        }
                        if(doy<0||(doy>366 && leapYear==1)|| (doy>365 && leapYear==0)) {
                            warningString += "Parameter '" + option + "' has an invalid day of year. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(sod<0||sod>86400) {
                            warningString += "Parameter '" + option + "' has an invalid second of day. It was skipped.\n";
                            ValidDate=0;
                        }
                        if (ValidDate==1) {
                            if(sod==86400) {
                                sod-=86400;
                                doy++;
                            }
                            if((doy>366 && leapYear==1)|| (doy>365 && leapYear==0)) {
                                doy=1;
                                year++;
                            }
                            doy2date(year,doy,&date);
                            SoD2time(sod,&hour);
                            ui->StartTimeShowOrbits->setDate(date);
                            ui->StartTimeShowOrbits->setTime(hour);
                            this->on_checkBoxStartTimeShowOrbits_clicked(true);
                        }
                    } else {
                        //Date is in GPSWeek SoW format
                        GPSWeek=userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt();
                        sow=userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt();
                        if(GPSWeek<1) {
                            warningString += "Parameter '" + option + "' has an invalid GPS week. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(sow<0||sow>604800) {
                            warningString += "Parameter '" + option + "' has an invalid second of week. It was skipped.\n";
                            ValidDate=0;
                        }
                        if (ValidDate==1) {
                            if(sow==604800) {
                                sow-=604800;
                                GPSWeek++;
                            }
                            GPSTime2DateTime(GPSWeek,sow,&date,&hour);
                            ui->StartTimeShowOrbits->setDate(date);
                            ui->StartTimeShowOrbits->setTime(hour);
                            this->on_checkBoxStartTimeShowOrbits_clicked(true);
                        }
                    }
                }
            }
        } else if ( QString::compare(option, "-pre:endtime", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()<2) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                ValidDate=1;
                addDay=0;
                leapYear=0;
                year=0;
                month=0;
                day=0;
                hour2=-1;
                minute=-1;
                second=-1;
                extraArgumentsToWarningStr(2,&warningString,option,ParametersList);
                if(userInputSingleSpace.section(" ", 1,1).contains(":")==true) {
                    //Time has ":" symbol.
                    if(userInputSingleSpace.section(" ", 0,0).contains("/")==true) {
                        //Time is in YYYY/MM/DD HH:MM:SS format
                        if(userInputSingleSpace.section(" ", 0,0).length()!=10) {
                            //Invalid date
                            warningString += "Parameter '" + option + "' has an invalid date. It was skipped.\n";
                            ValidDate=0;
                        } else {
                             if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                                 warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                                 ValidDate=0;
                             } else {
                                 year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                                 month=userInputSingleSpace.section(" ", 0,0).mid(5,2).toInt();
                                 day=userInputSingleSpace.section(" ", 0,0).mid(8,2).toInt();
                             }
                        }
                    } else {
                        //Time is in YYYYMMDD HH:MM:SS format
                        if(userInputSingleSpace.section(" ", 0,0).length()!=8) {
                            //Invalid date
                            warningString += "Parameter '" + option + "' has an invalid date. It was skipped.\n";
                            ValidDate=0;
                        } else {
                            if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                                warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                                ValidDate=0;
                            } else {
                                year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                                month=userInputSingleSpace.section(" ", 0,0).mid(4,2).toInt();
                                day=userInputSingleSpace.section(" ", 0,0).mid(6,2).toInt();
                            }
                        }
                    }
                    if (ValidDate==1) {
                        //Check date values and time length
                        if(year<=1970) {
                            warningString += "Parameter '" + option + "' has date prior to 1970. It was skipped.\n";
                            ValidDate=0;
                        } else {
                            //Check leap year
                            if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 ) {
                                leapYear=1;
                            }
                        }
                        if(month<1||month>12) {
                            warningString += "Parameter '" + option + "' has an invalid month. It was skipped.\n";
                            ValidDate=0;
                        }
                        if (day<1||day>31|| (leapYear==1 && day>daysmonthLeapYear[month]) || (leapYear==0 && day>daysmonth[month])) {
                            warningString += "Parameter '" + option + "' has an invalid day. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                            warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                            ValidDate=0;
                        }
                    }
                    if (ValidDate==1) {
                        //Read time in HH:MM:SS format and check values
                        hour2=userInputSingleSpace.section(" ", 1,1).left(2).toInt();
                        minute=userInputSingleSpace.section(" ", 1,1).mid(3,2).toInt();
                        second=userInputSingleSpace.section(" ", 1,1).mid(6,2).toInt();
                        if(hour2<0||hour2>24) {
                            warningString += "Parameter '" + option + "' has an invalid hour. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(minute<0||minute>60) {
                            warningString += "Parameter '" + option + "' has an invalid minute. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(second<0||second>60) {
                            warningString += "Parameter '" + option + "' has an invalid second. It was skipped.\n";
                            ValidDate=0;
                        }
                    }
                     if (ValidDate==1) {
                         if(second==60) {
                             second-=60;
                             minute++;
                         }
                         if(minute==60) {
                             minute-=60;
                             hour2++;
                         }
                         if(hour2==24) {
                             hour2-=24;
                             addDay=1;
                         }
                         date=QDate(year,month,day);
                         if(addDay==1) {
                            date=date.addDays(qint64(1));
                         }
                         hour=QTime(hour2,minute,second);
                         ui->EndTimeShowOrbits->setDate(date);
                         ui->EndTimeShowOrbits->setTime(hour);
                         this->on_checkBoxEndTimeShowOrbits_clicked(true);
                     }
                } else {
                    //Time can be in YYYY/DoY or GPSWeek
                    if(userInputSingleSpace.section(" ", 0,0).contains("/")==true) {
                        //Date is in YYYY/DoY SoD format
                        year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                        doy=userInputSingleSpace.section(" ", 0,0).mid(5).toInt();
                        sod=userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt();
                        if(year<=1970) {
                            warningString += "Parameter '" + option + "' has date prior to 1970. It was skipped.\n";
                            ValidDate=0;
                        } else {
                            //Check leap year
                            if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 ) {
                                leapYear=1;
                            }
                        }
                        if(doy<0||(doy>366 && leapYear==1)|| (doy>365 && leapYear==0)) {
                            warningString += "Parameter '" + option + "' has an invalid day of year. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(sod<0||sod>86400) {
                            warningString += "Parameter '" + option + "' has an invalid second of day. It was skipped.\n";
                            ValidDate=0;
                        }
                        if (ValidDate==1) {
                            if(sod==86400) {
                                sod-=86400;
                                doy++;
                            }
                            if((doy>366 && leapYear==1)|| (doy>365 && leapYear==0)) {
                                doy=1;
                                year++;
                            }
                            doy2date(year,doy,&date);
                            SoD2time(sod,&hour);
                            ui->EndTimeShowOrbits->setDate(date);
                            ui->EndTimeShowOrbits->setTime(hour);
                            this->on_checkBoxEndTimeShowOrbits_clicked(true);
                        }
                    } else {
                        //Date is in GPSWeek SoW format
                        GPSWeek=userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt();
                        sow=userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt();
                        if(GPSWeek<1) {
                            warningString += "Parameter '" + option + "' has an invalid GPS week. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(sow<0||sow>604800) {
                            warningString += "Parameter '" + option + "' has an invalid second of week. It was skipped.\n";
                            ValidDate=0;
                        }
                        if (ValidDate==1) {
                            if(sow==604800) {
                                sow-=604800;
                                GPSWeek++;
                            }
                            GPSTime2DateTime(GPSWeek,sow,&date,&hour);
                            ui->EndTimeShowOrbits->setDate(date);
                            ui->EndTimeShowOrbits->setTime(hour);
                            this->on_checkBoxEndTimeShowOrbits_clicked(true);
                        }
                    }
                }
            }
        } else if ( QString::compare(option, "-model:satclocks", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxSatClockOffsetShowOrbit->setChecked(true);
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "--model:satclocks", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxSatClockOffsetShowOrbit->setChecked(false);
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "-model:brdctranstime", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxCheckBroadcastTransmissionTimeShowOrbit->setChecked(true);
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "--model:brdctranstime", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxCheckBroadcastTransmissionTimeShowOrbit->setChecked(false);
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "-model:orbit:deg", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:orb:deg", Qt::CaseInsensitive)==0) {
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
            } else {
               ui->lineEditOrbitInterpolationDegreeShowOrbit->setText(QString("%1").arg(userInput.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "-model:orbmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditOrbitConsecutiveGapsShowOrbit->setText(QString("%1").arg(userInput.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "--model:orbmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->lineEditOrbitConsecutiveGapsShowOrbit->setText("0");
        } else if ( QString::compare(option, "-model:orbtotmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditOrbitMaxGapsShowOrbit->setText(QString("%1").arg(userInput.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "--model:orbtotmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->lineEditOrbitMaxGapsShowOrbit->setText("0");
        } else if ( QString::compare(option, "-model:clock:deg", Qt::CaseInsensitive)==0  || QString::compare(option, "-model:clk:deg", Qt::CaseInsensitive)==0) {
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditClockInterpolationDegreeShowOrbit->setText(QString("%1").arg(userInput.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "-model:clkmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditClockConsecutiveGapsShowOrbit->setText(QString("%1").arg(userInput.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "--model:clkmaxgaps", Qt::CaseInsensitive)==0 ) {
             extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
             ui->lineEditClockConsecutiveGapsShowOrbit->setText("0");
        } else if ( QString::compare(option, "-model:clktotmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditClockMaxGapsShowOrbit->setText(QString("%1").arg(userInput.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "--model:clktotmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->lineEditClockMaxGapsShowOrbit->setText("0");
        } else if ( QString::compare(option, "-model:satphasecenter", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            this->on_checkBoxAntexShowOrbitFile_clicked(true);
        } else if ( QString::compare(option, "--model:satphasecenter", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            this->on_checkBoxAntexShowOrbitFile_clicked(false);
        } else if ( QString::compare(option, "-model:orbprevsample", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->radioButtonOrbitCurrentDayShowOrbit->setChecked(true);
            ui->radioButtonOrbitNextDayShowOrbit->setChecked(false);
            this->on_groupBoxConcatenedPreciseFilesShowOrbit_clicked(true);
        } else if ( QString::compare(option, "--model:orbprevsample", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->radioButtonOrbitCurrentDayShowOrbit->setChecked(false);
            ui->radioButtonOrbitNextDayShowOrbit->setChecked(true);
        } else if ( QString::compare(option, "-model:clkprevsample", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->radioButtonClockCurrentDayShowOrbit->setChecked(true);
            ui->radioButtonClockNextDayShowOrbit->setChecked(false);
            this->on_groupBoxConcatenedPreciseFilesShowOrbit_clicked(true);
        } else if ( QString::compare(option, "--model:clkprevsample", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->radioButtonClockCurrentDayShowOrbit->setChecked(false);
            ui->radioButtonClockNextDayShowOrbit->setChecked(true);
        } else if ( QString::compare(option, "-model:brdc:gps", Qt::CaseInsensitive)==0 ){ //GPS Nav
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else{

            }
            if ( QString::compare(ParametersList[0], "PreferLNAV", Qt::CaseInsensitive)==0 ){
                this->selectGNSS_ShowNavMessageTypes(1,GPS);
            } else if ( QString::compare(ParametersList[0], "PreferCNAV", Qt::CaseInsensitive)==0 ){
                this->selectGNSS_ShowNavMessageTypes(1,GPS);
                ui->tableWidgetShowNavMessageTypeGPS->setCurrentItem(ui->tableWidgetShowNavMessageTypeGPS->item(0,1));
                this->moveNavMessageTypesColumn(ui->tableWidgetShowNavMessageTypeGPS,1,0,0);
                ui->tableWidgetShowNavMessageTypeGPS->clearSelection();
            } else {
                int typeOK=0;
                QStringList strNavMT=ParametersList[0].split(",", QString::SkipEmptyParts);
                this->selectGNSS_ShowNavMessageTypes(0,GPS);
                for (int i=0; i<strNavMT.count(); i++){
                    int itemTab=0;
                    for (itemTab=0; itemTab<ui->tableWidgetShowNavMessageTypeGPS->columnCount(); itemTab++){
                        if ( QString::compare(strNavMT[i], ui->tableWidgetShowNavMessageTypeGPS->item(0,itemTab)->text(), Qt::CaseInsensitive)==0 && ui->tableWidgetShowNavMessageTypeGPS->item(0,itemTab)->background().color().name()==RedColor ) {
                            //Select item to be moved (this is necessary otherwise navMessageTypesItem_doubleClicked function does not move the item)
                            ui->tableWidgetShowNavMessageTypeGPS->setCurrentItem(ui->tableWidgetShowNavMessageTypeGPS->item(0,itemTab));
                            navMessageTypesItem_doubleClicked(ui->tableWidgetShowNavMessageTypeGPS->item(0,itemTab));
                            typeOK++;
                            break;
                        }
                    }
                    if ( itemTab>=ui->tableWidgetShowNavMessageTypeGPS->columnCount() ){
                        warningString += "Parameter '-model:brdc:gps' has unknown type '" + strNavMT[i] +"'. It was skipped.\n";
                    }
                }
                if ( typeOK<1 ){
                    warningString += "Parameter '-model:brdc:gps' has no available value. It was set as Default.\n";
                    this->selectGNSS_ShowNavMessageTypes(1,GPS);
                }
            }
        }
        else if ( QString::compare(option, "-model:brdc:gal", Qt::CaseInsensitive)==0 ){ //Galileo Nav
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                if ( QString::compare(ParametersList[0], "PreferINAV", Qt::CaseInsensitive)==0 ){
                    this->selectGNSS_ShowNavMessageTypes(1,Galileo);
                } else if ( QString::compare(ParametersList[0], "PreferFNAV", Qt::CaseInsensitive)==0 ){
                    this->selectGNSS_ShowNavMessageTypes(1,Galileo);
                    ui->tableWidgetShowNavMessageTypeGalileo->setCurrentItem(ui->tableWidgetShowNavMessageTypeGalileo->item(0,3));
                    this->moveNavMessageTypesColumn(ui->tableWidgetShowNavMessageTypeGalileo,3,0,0);
                    ui->tableWidgetShowNavMessageTypeGalileo->clearSelection();
                } else if ( QString::compare(ParametersList[0], "INAV", Qt::CaseInsensitive)==0 ){
                    //INAV is INAVE1E5b, INAVE1, INAVE5b
                    this->selectGNSS_ShowNavMessageTypes(1,Galileo);
                    //Disable FNAV
                    ui->tableWidgetShowNavMessageTypeGalileo->item(0,3)->setBackgroundColor(RedColor);
                } else {
                    int typeOK=0;
                    QStringList strNavMT=ParametersList[0].split(",", QString::SkipEmptyParts);
                    this->selectGNSS_ShowNavMessageTypes(0,Galileo);
                    for (int i=0; i<strNavMT.count(); i++){
                        int itemTab=0;
                        for (itemTab=0; itemTab<ui->tableWidgetShowNavMessageTypeGalileo->columnCount(); itemTab++){
                            if ( QString::compare(strNavMT[i], ui->tableWidgetShowNavMessageTypeGalileo->item(0,itemTab)->text(), Qt::CaseInsensitive)==0 && ui->tableWidgetShowNavMessageTypeGalileo->item(0,itemTab)->background().color().name()==RedColor ) {
                                //Select item to be moved (this is necessary otherwise navMessageTypesItem_doubleClicked function does not move the item)
                                ui->tableWidgetShowNavMessageTypeGalileo->setCurrentItem(ui->tableWidgetShowNavMessageTypeGalileo->item(0,itemTab));
                                navMessageTypesItem_doubleClicked(ui->tableWidgetShowNavMessageTypeGalileo->item(0,itemTab));
                                typeOK++;
                                break;
                            }
                        }
                        if ( itemTab>=ui->tableWidgetShowNavMessageTypeGalileo->columnCount() ){
                            warningString += "Parameter '-model:brdc:gal' has unknown type '" + strNavMT[i] +"'. It was skipped.\n";
                        }
                    }
                    if ( typeOK<1 ){
                        warningString += "Parameter '-model:brdc:gal' has no available value. It was set as Default.\n";
                        this->selectGNSS_ShowNavMessageTypes(1,Galileo);
                    }
                }
            }
        }
        else if ( QString::compare(option, "-model:brdc:bds", Qt::CaseInsensitive)==0 ){ //BDS Nav
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                if ( QString::compare(ParametersList[0], "PreferD1", Qt::CaseInsensitive)==0 ){
                    this->selectGNSS_ShowNavMessageTypes(1,BDS);
                } else {
                    int typeOK=0;
                    QStringList strNavMT=ParametersList[0].split(",", QString::SkipEmptyParts);
                    this->selectGNSS_ShowNavMessageTypes(0,BDS);
                    for (int i=0; i<strNavMT.count(); i++){
                        int itemTab=0;
                        for (itemTab=0; itemTab<ui->tableWidgetShowNavMessageTypeBDS->columnCount(); itemTab++){
                            if ( QString::compare(strNavMT[i], ui->tableWidgetShowNavMessageTypeBDS->item(0,itemTab)->text(), Qt::CaseInsensitive)==0 && ui->tableWidgetShowNavMessageTypeBDS->item(0,itemTab)->background().color().name()==RedColor ) {
                                //Select item to be moved (this is necessary otherwise navMessageTypesItem_doubleClicked function does not move the item)
                                ui->tableWidgetShowNavMessageTypeBDS->setCurrentItem(ui->tableWidgetShowNavMessageTypeBDS->item(0,itemTab));
                                navMessageTypesItem_doubleClicked(ui->tableWidgetShowNavMessageTypeBDS->item(0,itemTab));
                                typeOK++;
                                break;
                            }
                        }
                        if ( itemTab>=ui->tableWidgetShowNavMessageTypeBDS->columnCount() ){
                            warningString += "Parameter '-model:brdc:bds' has unknown type '" + strNavMT[i] +"'. It was skipped.\n";
                        }
                    }
                    if ( typeOK<1 ){
                        warningString += "Parameter '-model:brdc:bds' has no available value. It was set as Default.\n";
                        this->selectGNSS_ShowNavMessageTypes(1,BDS);
                    }
                }
            }
        }
        else if ( QString::compare(option, "-model:brdc:qzss", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:brdc:qzs", Qt::CaseInsensitive)==0 ){ //QZSS Nav
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                if ( QString::compare(ParametersList[0], "PreferLNAV", Qt::CaseInsensitive)==0 ){
                    this->selectGNSS_ShowNavMessageTypes(1,QZSS);
                } else {
                    int typeOK=0;
                    QStringList strNavMT=ParametersList[0].split(",", QString::SkipEmptyParts);
                    this->selectGNSS_ShowNavMessageTypes(0,QZSS);
                    for (int i=0; i<strNavMT.count(); i++){
                        int itemTab=0;
                        for (itemTab=0; itemTab<ui->tableWidgetShowNavMessageTypeQZSS->columnCount(); itemTab++){
                            if ( QString::compare(strNavMT[i], ui->tableWidgetShowNavMessageTypeQZSS->item(0,itemTab)->text(), Qt::CaseInsensitive)==0 && ui->tableWidgetShowNavMessageTypeQZSS->item(0,itemTab)->background().color().name()==RedColor ) {
                                //Select item to be moved (this is necessary otherwise navMessageTypesItem_doubleClicked function does not move the item)
                                ui->tableWidgetShowNavMessageTypeQZSS->setCurrentItem(ui->tableWidgetShowNavMessageTypeQZSS->item(0,itemTab));
                                navMessageTypesItem_doubleClicked(ui->tableWidgetShowNavMessageTypeQZSS->item(0,itemTab));
                                typeOK++;
                                break;
                            }
                        }
                        if ( itemTab>=ui->tableWidgetShowNavMessageTypeQZSS->columnCount() ){
                            warningString += "Parameter '" + option + "' has unknown type '" + strNavMT[i] +"'. It was skipped.\n";
                        }
                    }
                    if ( typeOK<1 ){
                        warningString += "Parameter '" + option + "' has no available value. It was set as Default.\n";
                        this->selectGNSS_ShowNavMessageTypes(1,QZSS);
                    }
                }
            }
        } else if ( QString::compare(option, "-output:file", Qt::CaseInsensitive)==0 ) {
            ui->lineEditOutputFileShowOrbit->setText(userInput);
        } else if ( QString::compare(option, "--output:file", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            warningString += "Parameter '" + option + "' is for setting output messages to standard output, which will be lost after execution finishes. It was skipped.\n";
        } else if ( QString::compare(option, "-output:satvel", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            //This parameter is hidden in the GUI, due to "Inertial" velocity is not the completely in inertial coordinates
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (QString::compare(ParametersList[0], "inertial", Qt::CaseInsensitive)==0) {
                 warningString += "Parameter '" + option + "' is not used in the GUI. It was skipped.\n";
                 ui->radioButtonSatVelInertialShowOrbit->setChecked(true);
            } else if (QString::compare(ParametersList[0], "ITRF", Qt::CaseInsensitive)==0) {
                 warningString += "Parameter '" + option + "' is not used in the GUI. It was skipped.\n";
                 ui->radioButtonSatVelECEFShowOrbit->setChecked(true);
            } else {
                warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
            }
        } else if ( QString::compare(option, "-print:info", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintInfoShowOrbit->setChecked(true);
        } else if ( QString::compare(option, "--print:info", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintInfoShowOrbit->setChecked(false);
        } else if ( QString::compare(option, "-print:satpvt", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintSatpvtShowOrbit->setChecked(true);
        } else if ( QString::compare(option, "--print:satpvt", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintSatpvtShowOrbit->setChecked(false);
        } else if ( QString::compare(option, "-print:all", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxPrintInfoShowOrbit->setChecked(true);
            ui->checkBoxPrintSatpvtShowOrbit->setChecked(true);
        } else if ( QString::compare(option, "-print:none", Qt::CaseInsensitive)==0||QString::compare(option, "--print:none", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxPrintInfoShowOrbit->setChecked(false);
            ui->checkBoxPrintSatpvtShowOrbit->setChecked(false);
        } else if ( QString::compare(option, "-print:clkns", Qt::CaseInsensitive)==0 ) {
            ui->radioButtonNanosecondsUnitOutputClockSATPVT->setChecked(true);
        } else if ( QString::compare(option, "--print:clkns", Qt::CaseInsensitive)==0 ) {
            ui->radioButtonMetresUnitOutputClockSATPVT->setChecked(true);
        } else if ( QString::compare(option, "-print:v5format", Qt::CaseInsensitive)==0 ) {
            this->v5Message=1;
        }
    }

    if ( ui->lineEditOrbitMaxGapsShowOrbit->text().toInt()< ui->lineEditOrbitConsecutiveGapsShowOrbit->text().toInt()) {
        warningString += "Number of maximum gaps in orbit interpolation must be equal or greater than then number of consecutive gaps.\n";
    } else if ( ui->lineEditClockMaxGapsShowOrbit->text().toInt()< ui->lineEditClockConsecutiveGapsShowOrbit->text().toInt()) {
        warningString += "Number of maximum gaps in clock interpolation must be equal or greater than then number of consecutive gaps.\n";
    }

    if (!warningString.isEmpty()) {
        messageBox.setWindowTitle("Errors found");
        messageBox.setText("gLAB loaded the configuration file, but found the following errors:\n\n" + warningString);
        messageBox.setIcon(QMessageBox::Warning);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBox.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        messageBox.exec();
    }
}
