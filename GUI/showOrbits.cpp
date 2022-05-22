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
}

// Function for showing lineEdit for SP3 File
void gLAB_GUI::on_radioButtonOrbitPrecise1filesShowOrbitFile_clicked() {
    ui->stackedWidgetOrbitAndClockShowOrbitFile->setCurrentIndex(1);
    ui->radioButtonOrbitNavShowOrbitFile->setChecked(false);
    ui->radioButtonOrbitPrecise1filesShowOrbitFile->setChecked(true);
    ui->radioButtonOrbitPrecise2filesShowOrbitFile->setChecked(false);
    ui->groupBoAntexFileShowOrbit->setHidden(false);
    ui->groupBoxPreciseProductsInterpolationShowOrbit->setHidden(false);
}

// Function for showing lineEdit for SP3+CLK File
void gLAB_GUI::on_radioButtonOrbitPrecise2filesShowOrbitFile_clicked() {
    ui->stackedWidgetOrbitAndClockShowOrbitFile->setCurrentIndex(2);
    ui->radioButtonOrbitNavShowOrbitFile->setChecked(false);
    ui->radioButtonOrbitPrecise1filesShowOrbitFile->setChecked(false);
    ui->radioButtonOrbitPrecise2filesShowOrbitFile->setChecked(true);
    ui->groupBoAntexFileShowOrbit->setHidden(false);
    ui->groupBoxPreciseProductsInterpolationShowOrbit->setHidden(false);
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
    dialog.setNameFilter(tr("Broadcast Files (*.[0-9][0-9][np] *n.rnx);;All Files (*.*)"));
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
            messageBox.warning(0, "Error","RINEX Navigation file is empty\n");
        } else if (this->fileExists(ui->lineEditNavShowOrbitFile->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditNavShowOrbitFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditNavShowOrbitFile->text() + "' could not be opened with default text editor.\n");
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
            messageBox.warning(0, "Error","SP3 file is empty\n");
        } else if  (this->fileExists(ui->lineEditPreciseFilesShowOrbitSP3File->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesShowOrbitSP3File->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesShowOrbitSP3File->text() + "' could not be opened with default text editor.\n");
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
            messageBox.warning(0, "Error","SP3 file is empty\n");
        } else if (this->fileExists(ui->lineEditPreciseFilesShowOrbitOrbFile->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesShowOrbitOrbFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesShowOrbitOrbFile->text() + "' could not be opened with default text editor.\n");
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
            messageBox.warning(0, "Error","Clock file is empty\n");
        } else if (this->fileExists(ui->lineEditPreciseFilesShowOrbitClkFile->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesShowOrbitClkFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesShowOrbitClkFile->text() + "' could not be opened with default text editor.\n");
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
            messageBox.warning(0, "Error","ANTEX file is empty\n");
        } else if (this->fileExists(ui->lineEditAntexShowOrbitFile->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditAntexShowOrbitFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditAntexShowOrbitFile->text() + "' could not be opened with default text editor.\n");
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
            messageBox.warning(0, "Error","Output file is empty\n");
        } else if (this->fileExists(ui->lineEditOutputFileShowOrbit->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputFileShowOrbit->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputFileShowOrbit->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}
///////////////// End of Context menus (right-click menus) //////////////////

void gLAB_GUI::getshowOrbitOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString) {

    int NumMessages=1;
    int SP3File=0;
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
            *saveString += "-input:nav " + ui->lineEditNavShowOrbitFile->text()+ "\n";
            *runString <<  "-input:nav" << ui->lineEditNavShowOrbitFile->text();
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

    //Check unhealthy flag. By default enabled
    if (ui->checkBoxDiscardUnhealthyShowOrbit->isChecked()==false) {
        *saveString +=  "--model:satellitehealth\n";
        *runString <<  "--model:satellitehealth";
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
            if ( ui->lineEditClockInterpolationDegreeShowOrbit->text().toInt()!=0) {
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
    QTextStream InputFile(file);
    InputFile.setAutoDetectUnicode(true);

    int numNav=0;
    int numSP3=0;
    int numOrb=0;
    int numClk=0;
    int numAnt=0;
    int numInputOrbFiles=0;
    int noAntParameter=0;
    int HashPos;

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
        messageBox.critical(0, "Errors found",
                            "gLAB did not load the the configuration file due to the following errors:\n\n" + errorString);
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
                extraParametersToWarningStr(1,&warningString,option,ParametersList);
                if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                    warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                } else {
                   ui->lineEditDecimationShowOrbit->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                }
            }
        } else if ( QString::compare(option, "--pre:dec", Qt::CaseInsensitive)==0 ) {
            warningString += "Parameter '" + option + "' is not valid in show orbit mode. It was skipped.\n";
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "-model:satclocks", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxSatClockOffsetShowOrbit->setChecked(true);
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "--model:satclocks", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxSatClockOffsetShowOrbit->setChecked(false);
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "-model:brdctranstime", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxCheckBroadcastTransmissionTimeShowOrbit->setChecked(true);
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "--model:brdctranstime", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxCheckBroadcastTransmissionTimeShowOrbit->setChecked(false);
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "-model:satellitehealth", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxDiscardUnhealthyShowOrbit->setChecked(false);
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "--model:satellitehealth", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxDiscardUnhealthyShowOrbit->setChecked(false);
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "-model:orbit:deg", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:orb:deg", Qt::CaseInsensitive)==0) {
            extraParametersToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
            } else {
               ui->lineEditOrbitInterpolationDegreeShowOrbit->setText(QString("%1").arg(userInput.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "-model:orbmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditOrbitConsecutiveGapsShowOrbit->setText(QString("%1").arg(userInput.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "--model:orbmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->lineEditOrbitConsecutiveGapsShowOrbit->setText("0");
        } else if ( QString::compare(option, "-model:orbtotmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditOrbitMaxGapsShowOrbit->setText(QString("%1").arg(userInput.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "--model:orbtotmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->lineEditOrbitMaxGapsShowOrbit->setText("0");
        } else if ( QString::compare(option, "-model:clock:deg", Qt::CaseInsensitive)==0  || QString::compare(option, "-model:clk:deg", Qt::CaseInsensitive)==0) {
            extraParametersToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditClockInterpolationDegreeShowOrbit->setText(QString("%1").arg(userInput.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "-model:clkmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditClockConsecutiveGapsShowOrbit->setText(QString("%1").arg(userInput.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "--model:clkmaxgaps", Qt::CaseInsensitive)==0 ) {
             extraParametersToWarningStr(0,&warningString,option,ParametersList);
             ui->lineEditClockConsecutiveGapsShowOrbit->setText("0");
        } else if ( QString::compare(option, "-model:clktotmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditClockMaxGapsShowOrbit->setText(QString("%1").arg(userInput.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "--model:clktotmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->lineEditClockMaxGapsShowOrbit->setText("0");
        } else if ( QString::compare(option, "-model:satphasecenter", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            this->on_checkBoxAntexShowOrbitFile_clicked(true);
        } else if ( QString::compare(option, "--model:satphasecenter", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            this->on_checkBoxAntexShowOrbitFile_clicked(false);
        } else if ( QString::compare(option, "-model:orbprevsample", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->radioButtonOrbitCurrentDayShowOrbit->setChecked(true);
            ui->radioButtonOrbitNextDayShowOrbit->setChecked(false);
            this->on_groupBoxConcatenedPreciseFilesShowOrbit_clicked(true);
        } else if ( QString::compare(option, "--model:orbprevsample", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->radioButtonOrbitCurrentDayShowOrbit->setChecked(false);
            ui->radioButtonOrbitNextDayShowOrbit->setChecked(true);
        } else if ( QString::compare(option, "-model:clkprevsample", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->radioButtonClockCurrentDayShowOrbit->setChecked(true);
            ui->radioButtonClockNextDayShowOrbit->setChecked(false);
            this->on_groupBoxConcatenedPreciseFilesShowOrbit_clicked(true);
        } else if ( QString::compare(option, "--model:clkprevsample", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->radioButtonClockCurrentDayShowOrbit->setChecked(false);
            ui->radioButtonClockNextDayShowOrbit->setChecked(true);
        } else if ( QString::compare(option, "-output:file", Qt::CaseInsensitive)==0 ) {
            ui->lineEditOutputFileShowOrbit->setText(userInput);
        } else if ( QString::compare(option, "--output:file", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            warningString += "Parameter '" + option + "' is for setting output messages to standard output, which will be lost after execution finishes. It was skipped.\n";
        } else if ( QString::compare(option, "-output:satvel", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(1,&warningString,option,ParametersList);
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
                warningString += "'" + ParametersList[0] + "' is not a valid option for parameter '" + option + "'. It was skipped.\n";
            }
        } else if ( QString::compare(option, "-print:info", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintInfoShowOrbit->setChecked(true);
        } else if ( QString::compare(option, "--print:info", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintInfoShowOrbit->setChecked(false);
        } else if ( QString::compare(option, "-print:satpvt", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintSatpvtShowOrbit->setChecked(true);
        } else if ( QString::compare(option, "--print:satpvt", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintSatpvtShowOrbit->setChecked(false);
        } else if ( QString::compare(option, "-print:all", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxPrintInfoShowOrbit->setChecked(true);
            ui->checkBoxPrintSatpvtShowOrbit->setChecked(true);
        } else if ( QString::compare(option, "-print:none", Qt::CaseInsensitive)==0||QString::compare(option, "--print:none", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxPrintInfoShowOrbit->setChecked(false);
            ui->checkBoxPrintSatpvtShowOrbit->setChecked(false);
        }
    }

    if ( ui->lineEditOrbitMaxGapsShowOrbit->text().toInt()< ui->lineEditOrbitConsecutiveGapsShowOrbit->text().toInt()) {
        warningString += "Number of maximum gaps in orbit interpolation must be equal or greater than then number of consecutive gaps.\n";
    } else if ( ui->lineEditClockMaxGapsShowOrbit->text().toInt()< ui->lineEditClockConsecutiveGapsShowOrbit->text().toInt()) {
        warningString += "Number of maximum gaps in clock interpolation must be equal or greater than then number of consecutive gaps.\n";
    }

    if (!warningString.isEmpty()) {
        messageBox.warning(0, "Errors found",
                            "gLAB loaded the configuration file, but found the following errors:\n\n" + warningString);
    }
}
