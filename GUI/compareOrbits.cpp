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
void gLAB_GUI::on_checkBoxAntexCompareOrbitsFile2_clicked(bool checked) {
    ui->checkBoxAntexCompareOrbitsFile2->setChecked(checked);
    ui->frameAntexCompareOrbitsLineEditFile2->setHidden(!checked);
    if (checked==true && (ui->radioButtonOrbitPrecise1filesCompareFile1->isChecked()==true || ui->radioButtonOrbitPrecise2filesCompareFile1->isChecked()==true) && (ui->radioButtonOrbitPrecise1filesCompareFile2->isChecked()==true || ui->radioButtonOrbitPrecise2filesCompareFile2->isChecked()==true)) {
        ui->frameAntexWarningCompareOrbit->setHidden(false);
    } else {
        ui->frameAntexWarningCompareOrbit->setHidden(true);
    }
}

// Function for showing lineEdit for Navigation File 1
void gLAB_GUI::on_radioButtonOrbitNavCompareFile1_clicked() {
    ui->stackedWidgetOrbitAndClockCompareFile1->setCurrentIndex(0);
    ui->radioButtonOrbitNavCompareFile1->setChecked(true);
    ui->radioButtonOrbitPrecise1filesCompareFile1->setChecked(false);
    ui->radioButtonOrbitPrecise2filesCompareFile1->setChecked(false);
    if(ui->radioButtonOrbitPrecise1filesCompareFile2->isChecked()==false && ui->radioButtonOrbitPrecise2filesCompareFile2->isChecked()==false ) {
         ui->groupBoxPreciseProductsInterpolationCompare->setHidden(true);
         ui->groupBoxAntexFileCompare->setHidden(true);
    }
    ui->frameAntexWarningCompareOrbit->setHidden(true);
}

// Function for showing lineEdit for SP3 File 1
void gLAB_GUI::on_radioButtonOrbitPrecise1filesCompareFile1_clicked() {
    ui->stackedWidgetOrbitAndClockCompareFile1->setCurrentIndex(1);
    ui->radioButtonOrbitNavCompareFile1->setChecked(false);
    ui->radioButtonOrbitPrecise1filesCompareFile1->setChecked(true);
    ui->radioButtonOrbitPrecise2filesCompareFile1->setChecked(false);
    ui->groupBoxPreciseProductsInterpolationCompare->setHidden(false);
    ui->groupBoxAntexFileCompare->setHidden(false);
    if (ui->checkBoxAntexCompareOrbitsFile2->isChecked()==true) {
        if (ui->radioButtonOrbitPrecise1filesCompareFile2->isChecked()==true || ui->radioButtonOrbitPrecise2filesCompareFile2->isChecked()==true) {
            ui->frameAntexWarningCompareOrbit->setHidden(false);
        }
    }
}

// Function for showing lineEdit for SP3+CLK File 1
void gLAB_GUI::on_radioButtonOrbitPrecise2filesCompareFile1_clicked() {
    ui->stackedWidgetOrbitAndClockCompareFile1->setCurrentIndex(2);
    ui->radioButtonOrbitNavCompareFile1->setChecked(false);
    ui->radioButtonOrbitPrecise1filesCompareFile1->setChecked(false);
    ui->radioButtonOrbitPrecise2filesCompareFile1->setChecked(true);
    ui->groupBoxPreciseProductsInterpolationCompare->setHidden(false);
    ui->groupBoxAntexFileCompare->setHidden(false);
    if (ui->checkBoxAntexCompareOrbitsFile2->isChecked()==true) {
        if (ui->radioButtonOrbitPrecise1filesCompareFile2->isChecked()==true || ui->radioButtonOrbitPrecise2filesCompareFile2->isChecked()==true) {
            ui->frameAntexWarningCompareOrbit->setHidden(false);
        }
    }
}

// Function for showing lineEdit for Navigation File 2
void gLAB_GUI::on_radioButtonOrbitNavCompareFile2_clicked() {
    ui->stackedWidgetOrbitAndClockCompareFile2->setCurrentIndex(0);
    ui->radioButtonOrbitNavCompareFile2->setChecked(true);
    ui->radioButtonOrbitPrecise1filesCompareFile2->setChecked(false);
    ui->radioButtonOrbitPrecise2filesCompareFile2->setChecked(false);
    ui->frameAntexWarningCompareOrbit->setHidden(true);
    if(ui->radioButtonOrbitPrecise1filesCompareFile1->isChecked()==false && ui->radioButtonOrbitPrecise2filesCompareFile1->isChecked()==false ) {
         ui->groupBoxPreciseProductsInterpolationCompare->setHidden(true);
         ui->groupBoxAntexFileCompare->setHidden(true);
    }
}

// Function for showing lineEdit for SP3 File 2
void gLAB_GUI::on_radioButtonOrbitPrecise1filesCompareFile2_clicked() {
    ui->stackedWidgetOrbitAndClockCompareFile2->setCurrentIndex(1);
    ui->radioButtonOrbitNavCompareFile2->setChecked(false);
    ui->radioButtonOrbitPrecise1filesCompareFile2->setChecked(true);
    ui->radioButtonOrbitPrecise2filesCompareFile2->setChecked(false);
    ui->groupBoxAntexFileCompare->setHidden(false);
    ui->groupBoxPreciseProductsInterpolationCompare->setHidden(false);
    if (ui->checkBoxAntexCompareOrbitsFile2->isChecked()==true) {
        if (ui->radioButtonOrbitPrecise1filesCompareFile1->isChecked()==true || ui->radioButtonOrbitPrecise2filesCompareFile1->isChecked()==true) {
            ui->frameAntexWarningCompareOrbit->setHidden(false);
        }
    }
}

// Function for showing lineEdit for SP3+CLK File 2
void gLAB_GUI::on_radioButtonOrbitPrecise2filesCompareFile2_clicked() {
    ui->stackedWidgetOrbitAndClockCompareFile2->setCurrentIndex(2);
    ui->radioButtonOrbitNavCompareFile2->setChecked(false);
    ui->radioButtonOrbitPrecise1filesCompareFile2->setChecked(false);
    ui->radioButtonOrbitPrecise2filesCompareFile2->setChecked(true);
    ui->groupBoxAntexFileCompare->setHidden(false);
    ui->groupBoxPreciseProductsInterpolationCompare->setHidden(false);
    if (ui->checkBoxAntexCompareOrbitsFile2->isChecked()==true) {
        if (ui->radioButtonOrbitPrecise1filesCompareFile1->isChecked()==true || ui->radioButtonOrbitPrecise2filesCompareFile1->isChecked()==true) {
            ui->frameAntexWarningCompareOrbit->setHidden(false);
        }
    }
}

//Function to show or hide concatenated SP3/CLK options
void gLAB_GUI::on_groupBoxConcatenedPreciseFilesCompare_clicked(bool checked) {
    ui->groupBoxConcatenedPreciseFilesCompare->setChecked(checked);
    ui->frameConcatenedPreciseFilesCompare->setHidden(!checked);
}

////////////////////// Push buttons /////////////////////
void gLAB_GUI::on_pushButtonRinexNavCompareFile1_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.[0-9][0-9][np] *n.rnx);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditNavCompareFile1->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonPrecise1FileCompareFile1_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Precise Files (*.sp3 *.eph);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPreciseFilesCompareSP3File1->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonPrecise2FilesCompareFile1_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Precise Files (*.sp3 *.eph);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPreciseFilesCompareOrbFile1->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonPreciseClkCompareFile1_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Clock Files (*.clk *.clk_30s *.clk_05s);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPreciseFilesCompareClkFile1->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonRinexNavCompareFile2_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.[0-9][0-9][np] *n.rnx);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditNavCompareFile2->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonPrecise1FileCompareFile2_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Precise Files (*.sp3 *.eph);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPreciseFilesCompareSP3File2->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonPrecise2FilesCompareFile2_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Precise Files (*.sp3 *.eph);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPreciseFilesCompareOrbFile2->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonPreciseClkCompareFile2_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Clock Files (*.clk *.clk_30s *.clk_05s);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPreciseFilesCompareClkFile2->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonAntexCompareOrbitsFile2_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("ANTEX Files (*.atx);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditAntexCompareOrbitsFile2->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

// Open dialog to set the output filename and path
void gLAB_GUI::on_pushButtonOutputFileCompare_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    //dialog.setAcceptMode(QFileDialog::AcceptSave); //This to confirm overwriting files
    dialog.setNameFilter(tr("gLAB Output Files (*.out);;All Files (*.*)"));
    dialog.selectFile(".out");
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

//Set all output messages button
void gLAB_GUI::on_pushButtonOrbitsCompareMessagesAll_clicked() {
    ui->checkBoxPrintInfoCompare->setChecked(true);
    ui->checkBoxPrintSatdiffCompare->setChecked(true);
    ui->checkBoxPrintSatstatCompare->setChecked(true);
    ui->checkBoxPrintSatstattotCompare->setChecked(true);
}

//Unset all output messages button
void gLAB_GUI::on_pushButtonOrbitsCompareMessagesNone_clicked() {
    ui->checkBoxPrintInfoCompare->setChecked(false);
    ui->checkBoxPrintSatdiffCompare->setChecked(false);
    ui->checkBoxPrintSatstatCompare->setChecked(false);
    ui->checkBoxPrintSatstattotCompare->setChecked(false);
}

////////////////// End of Push buttons //////////////////

///////////////// Start of Context menus (right-click menus) //////////////////
void gLAB_GUI::labelCompareRinexNavFile1Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareRinexNavFile1->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open RINEX Navigation File 1");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditNavCompareFile1->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditNavCompareFile1->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditNavCompareFile1->text();
        #endif

        // Execute the program        
        if (ui->lineEditNavCompareFile1->text() == "") {
            messageBox.warning(0, "Error","RINEX Navigation file 1 is empty\n");
        } else if (this->fileExists(ui->lineEditNavCompareFile1->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditNavCompareFile1->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditNavCompareFile1->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}
void gLAB_GUI::labelCompareSP3OrbitsClocksFile1Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareSP3OrbitsClocksFile1->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open SP3 File 1");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPreciseFilesCompareSP3File1->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPreciseFilesCompareSP3File1->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPreciseFilesCompareSP3File1->text();
        #endif

        // Execute the program
        if (ui->lineEditPreciseFilesCompareSP3File1->text() == "") {
            messageBox.warning(0, "Error","SP3 file 1 is empty\n");
        } else if (this->fileExists(ui->lineEditPreciseFilesCompareSP3File1->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesCompareSP3File1->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesCompareSP3File1->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelCompareSP3OrbitsFile1Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareSP3OrbitsFile1->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open SP3 File 1");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPreciseFilesCompareOrbFile1->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPreciseFilesCompareOrbFile1->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPreciseFilesCompareOrbFile1->text();
        #endif

        // Execute the program
        if (ui->lineEditPreciseFilesCompareOrbFile1->text() == "") {
            messageBox.warning(0, "Error","SP3 file 1 is empty\n");
        } else if (this->fileExists(ui->lineEditPreciseFilesCompareOrbFile1->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesCompareOrbFile1->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesCompareOrbFile1->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelCompareClockFile1Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareClockFile1->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open Clock File 1");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPreciseFilesCompareClkFile1->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPreciseFilesCompareClkFile1->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPreciseFilesCompareClkFile1->text();
        #endif

        // Execute the program        
        if (ui->lineEditPreciseFilesCompareClkFile1->text() == "") {
            messageBox.warning(0, "Error","Clock file 1 is empty\n");
        } else if  (this->fileExists(ui->lineEditPreciseFilesCompareClkFile1->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesCompareClkFile1->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesCompareClkFile1->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelCompareRinexNavFile2Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareRinexNavFile2->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open RINEX Navigation File 2");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditNavCompareFile2->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditNavCompareFile2->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditNavCompareFile2->text();
        #endif

        // Execute the program
        if (ui->lineEditNavCompareFile2->text() == "") {
            messageBox.warning(0, "Error","RINEX Navigation file 2 is empty\n");
        } else if (this->fileExists(ui->lineEditNavCompareFile2->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditNavCompareFile2->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditNavCompareFile2->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelCompareSP3OrbitsClocksFile2Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareSP3OrbitsClocksFile2->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open SP3 File 2");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPreciseFilesCompareSP3File2->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPreciseFilesCompareSP3File2->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPreciseFilesCompareSP3File2->text();
        #endif

        // Execute the program
        if (ui->lineEditPreciseFilesCompareSP3File2->text() == "") {
            messageBox.warning(0, "Error","SP3 file 2 is empty\n");
        } else if  (this->fileExists(ui->lineEditPreciseFilesCompareSP3File2->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesCompareSP3File2->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesCompareSP3File2->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelCompareSP3OrbitsFile2Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareSP3OrbitsFile2->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open SP3 File 2");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPreciseFilesCompareOrbFile2->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPreciseFilesCompareOrbFile2->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPreciseFilesCompareOrbFile2->text();
        #endif

        // Execute the program
        if (ui->lineEditPreciseFilesCompareOrbFile2->text() == "") {
            messageBox.warning(0, "Error","SP3 file 2 is empty\n");
        } else if (this->fileExists(ui->lineEditPreciseFilesCompareOrbFile2->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesCompareOrbFile2->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesCompareOrbFile2->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelCompareClockFile2Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareClockFile2->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open Clock File 2");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPreciseFilesCompareClkFile2->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPreciseFilesCompareClkFile2->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPreciseFilesCompareClkFile2->text();
        #endif

        // Execute the program
        if (ui->lineEditPreciseFilesCompareClkFile2->text() == "") {
            messageBox.warning(0, "Error","Clock file 2 is empty\n");
        } else if  (this->fileExists(ui->lineEditPreciseFilesCompareClkFile2->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesCompareClkFile2->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditPreciseFilesCompareClkFile2->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::checkBoxAntexCompareOrbitsFile2Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->checkBoxAntexCompareOrbitsFile2->mapToGlobal(pos);
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
            arguments << ui->lineEditAntexCompareOrbitsFile2->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditAntexCompareOrbitsFile2->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditAntexCompareOrbitsFile2->text();
        #endif

        // Execute the program
        if (ui->lineEditAntexCompareOrbitsFile2->text() == "") {
            messageBox.warning(0, "Error","ANTEX file is empty\n");
        } else if (this->fileExists(ui->lineEditAntexCompareOrbitsFile2->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditAntexCompareOrbitsFile2->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditAntexCompareOrbitsFile2->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelCompareOutputFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareOutputFile->mapToGlobal(pos);
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
            arguments << ui->lineEditOutputFileCompare->text();
        #elif defined(Q_OS_WIN32)
            //QString programFilesPath(getenv("PROGRAMFILES"));
            //program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            program = QString("notepad");
            arguments << ui->lineEditOutputFileCompare->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditOutputFileCompare->text();
        #endif

        // Execute the program
        if (ui->lineEditOutputFileCompare->text() == "") {
            messageBox.warning(0, "Error","Output file is empty\n");
        } else if (this->fileExists(ui->lineEditOutputFileCompare->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputFileCompare->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputFileCompare->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}
///////////////// End of Context menus (right-click menus) //////////////////

void gLAB_GUI::getCompareOrbitOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString) {

    int NumMessages=3;
    int SP3File=0;
    *errorString = "";
    *warningString="";
    *saveString = "";

    //Check File 1
    if ( ui->radioButtonOrbitNavCompareFile1->isChecked()==true) {
        //File 1 is navigation file
        if ( ui->lineEditNavCompareFile1->text() == "" ) {
            *errorString += "File 1: Navigation source file is empty.\n";
        } else if ( this->fileExists(ui->lineEditNavCompareFile1->text())==false ) {
            *errorString += "File 1: Navigation source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditNavCompareFile1->text())==1) {
            *errorString += "File 1: Navigation source file has non ASCII characters\n";
        } else {
            *saveString += "-input:nav " + ui->lineEditNavCompareFile1->text() + "\n";
            *runString << "-input:nav" << ui->lineEditNavCompareFile1->text();
        }
    } else if ( ui->radioButtonOrbitPrecise1filesCompareFile1->isChecked()==true) {
        //File 1 is SP3
        if ( ui->lineEditPreciseFilesCompareSP3File1->text() == "" ) {
            *errorString += "File 1: SP3 source file is empty.\n";
        } else if (  this->fileExists(ui->lineEditPreciseFilesCompareSP3File1->text()) ==false) {
            *errorString += "File 1: SP3 source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPreciseFilesCompareSP3File1->text())==1) {
            *errorString += "File 1: SP3 source file has non ASCII characters\n";
        } else {
            *saveString += "-input:sp3 " +  ui->lineEditPreciseFilesCompareSP3File1->text() + "\n";
            *runString << "-input:sp3" << ui->lineEditPreciseFilesCompareSP3File1->text();
        }
        SP3File=1;
    } else if ( ui->radioButtonOrbitPrecise2filesCompareFile1->isChecked()==true ) {
        //File 1 is SP3 + CLK
        if ( ui->lineEditPreciseFilesCompareOrbFile1->text() == "" ) {
            *errorString += "File 1: Orbit SP3 source file is empty.\n";
        } else if ( this->fileExists( ui->lineEditPreciseFilesCompareOrbFile1->text() )==false) {
            *errorString += "File 1: Orbit SP3 source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPreciseFilesCompareOrbFile1->text())==1) {
            *errorString += "File 1: Orbit SP3 source file has non ASCII characters\n";
        } else {
            *saveString += "-input:orb " + ui->lineEditPreciseFilesCompareOrbFile1->text() + "\n";
            *runString << "-input:orb" << ui->lineEditPreciseFilesCompareOrbFile1->text();
        }
        if ( ui->lineEditPreciseFilesCompareClkFile1->text() == "" ) {
            *errorString += "File 1: Clock source file is empty.\n";
        } else if (  this->fileExists(ui->lineEditPreciseFilesCompareClkFile1->text())==false) {
            *errorString += "File 1: Clock source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPreciseFilesCompareClkFile1->text())==1) {
            *errorString += "File 1: Clock source file has non ASCII characters\n";
        } else {
            *saveString += "-input:clk " + ui->lineEditPreciseFilesCompareClkFile1->text() + "\n";
            *runString << "-input:clk" << ui->lineEditPreciseFilesCompareClkFile1->text();
        }
        SP3File=1;
    }
    //Check File 2
    if ( ui->radioButtonOrbitNavCompareFile2->isChecked()==true) {
        //File 2 is navigation file
        if ( ui->lineEditNavCompareFile2->text() == "" ) {
            *errorString += "File 2: Navigation source file is empty.\n";
        } else if ( this->fileExists(ui->lineEditNavCompareFile2->text())==false ) {
            *errorString += "File 2: Navigation source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditNavCompareFile2->text())==1) {
            *errorString += "File 2: Navigation source file has non ASCII characters\n";
        } else {
            *saveString +=  "-input:nav " + ui->lineEditNavCompareFile2->text() + "\n";
            *runString <<  "-input:nav" << ui->lineEditNavCompareFile2->text();
        }
    } else if ( ui->radioButtonOrbitPrecise1filesCompareFile2->isChecked()==true) {
        //File 2 is SP3
        if ( ui->lineEditPreciseFilesCompareSP3File2->text() == "" ) {
            *errorString += "File 2: SP3 source file is empty.\n";
        } else if (  this->fileExists(ui->lineEditPreciseFilesCompareSP3File2->text()) ==false) {
            *errorString += "File 2: SP3 source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPreciseFilesCompareSP3File2->text())==1) {
            *errorString += "File 2: SP3 source file has non ASCII characters\n";
        } else {
            *saveString +=  "-input:sp3 " + ui->lineEditPreciseFilesCompareSP3File2->text() + "\n";
            *runString <<  "-input:sp3" << ui->lineEditPreciseFilesCompareSP3File2->text();
        }
        SP3File=1;
        //Check ANTEX
        if ( ui->checkBoxAntexCompareOrbitsFile2->isChecked()==true) {
            if ( ui->lineEditAntexCompareOrbitsFile2->text() == "" ) {
                *errorString += "ANTEX option selected, but source file is empty.\n";
            } else if  (  this->fileExists(ui->lineEditAntexCompareOrbitsFile2->text() )==false) {
                *errorString += "ANTEX source file does not exist.\n";
            } else if (this->checknonASCIIcharacters(ui->lineEditAntexCompareOrbitsFile2->text())==1) {
                *errorString += "ANTEX source file has non ASCII characters\n";
            } else {
                *saveString +=  "-input:ant " + ui->lineEditAntexCompareOrbitsFile2->text() + "\n";
                *runString <<  "-input:ant" << ui->lineEditAntexCompareOrbitsFile2->text();
            }
        } else {
            *saveString += "--model:satphasecenter\n";
            *runString << "--model:satphasecenter";
        }
    } else if ( ui->radioButtonOrbitPrecise2filesCompareFile2->isChecked()==true ) {
        //File 2 is SP3 + CLK
        if ( ui->lineEditPreciseFilesCompareOrbFile2->text() == "" ) {
            *errorString += "File 2: Orbit SP3 source file is empty.\n";
        } else if ( this->fileExists( ui->lineEditPreciseFilesCompareOrbFile2->text() )==false) {
            *errorString += "File 2: Orbit SP3 source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPreciseFilesCompareOrbFile2->text())==1) {
            *errorString += "File 2: Orbit SP3 source file has non ASCII characters\n";
        } else {
            *saveString +=  "-input:orb " + ui->lineEditPreciseFilesCompareOrbFile2->text() + "\n";
            *runString <<  "-input:orb" << ui->lineEditPreciseFilesCompareOrbFile2->text();
        }
        SP3File=1;
        if ( ui->lineEditPreciseFilesCompareClkFile2->text() == "" ) {
            *errorString += "File 2: Clock source file is empty.\n";
        } else if (  this->fileExists(ui->lineEditPreciseFilesCompareClkFile2->text())==false) {
            *errorString += "File 2: Clock source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPreciseFilesCompareClkFile2->text())==1) {
            *errorString += "File 2: Clock source file has non ASCII characters\n";
        } else {
            *saveString +=  "-input:clk " + ui->lineEditPreciseFilesCompareClkFile2->text() + "\n";
            *runString <<  "-input:clk" << ui->lineEditPreciseFilesCompareClkFile2->text();
        }
        //Check ANTEX
        if ( ui->checkBoxAntexCompareOrbitsFile2->isChecked()==true) {
            if ( ui->lineEditAntexCompareOrbitsFile2->text() == "" ) {
                *errorString += "ANTEX option selected, but source file is empty.\n";
            } else if  (  this->fileExists(ui->lineEditAntexCompareOrbitsFile2->text() )==false) {
                *errorString += "ANTEX source file does not exist.\n";
            } else if (this->checknonASCIIcharacters(ui->lineEditAntexCompareOrbitsFile2->text())==1) {
                *errorString += "ANTEX source file has non ASCII characters\n";
            } else {
                *saveString +=  "-input:ant " + ui->lineEditAntexCompareOrbitsFile2->text() + "\n";
                *runString <<  "-input:ant" << ui->lineEditAntexCompareOrbitsFile2->text();
            }
        } else {
            *saveString += "--model:satphasecenter\n";
            *runString << "--model:satphasecenter";
        }
    }

    ///Check modeling options
    //Decimation
    if (ui->lineEditDecimationCompareOrbit->text()=="") {
        *errorString += "Data Decimation value is empty.\n";
    } else if (ui->lineEditDecimationCompareOrbit->text().toDouble()==0.) {
        *errorString += "Data Decimation can not be set to 0.\n";
    } else if (ui->lineEditDecimationCompareOrbit->text().toDouble()!= 300.) {
        //By default it is set to 300
        *saveString +=  "-pre:dec " + ui->lineEditDecimationCompareOrbit->text() + "\n";
        *runString <<  "-pre:dec" << ui->lineEditDecimationCompareOrbit->text();
    }

    //Check eclipse condition. By default disabled
    if (ui->checkBoxDiscardEclipseCompare->isChecked()==true) {
        *saveString +=  "-pre:eclipse\n";
        *runString <<  "-pre:eclipse";
    }

    //Clock correction. By default enabled
    if (ui->checkBoxSatClockOffsetCompare->isChecked()==false) {
        *saveString +=  "--model:satclocks\n";
        *runString <<  "--model:satclocks";
    }

    //Broadcast transmission time. By default enabled
    if (ui->checkBoxCheckBroadcastTransmissionTimeCompare->isChecked()==false) {
        *saveString +=  "--model:brdctranstime\n";
        *runString <<  "--model:brdctranstime";
    }


    //Check unhealthy flag. By default enabled
    if (ui->checkBoxDiscardUnhealthyCompare->isChecked()==false) {
        *saveString +=  "--model:satellitehealth\n";
        *runString <<  "--model:satellitehealth";
    }

    // Precise products interpolation data (only when a precise product is given)
    if ( SP3File==1) {
        if ( ui->lineEditOrbitInterpolationDegreeCompare->text() == "" ) {
            *errorString += "Orbit interpolation degree cannot be empty.\n";
        } else if ( ui->lineEditOrbitInterpolationDegreeCompare->text().toInt() == 0 ) {
            *errorString += "Orbit interpolation degree cannot be 0.\n";
        } else if ( ui->lineEditOrbitConsecutiveGapsCompare->text() == "" ) {
            *errorString += "Number of consecutive gaps in orbit interpolation cannot be empty.\n";
        } else if ( ui->lineEditOrbitMaxGapsCompare->text() == "" ) {
            *errorString += "Number of maximum gaps in orbit interpolation cannot be empty.\n";
        } else if ( ui->lineEditClockInterpolationDegreeCompare->text() == "" ) {
            *errorString += "Clock interpolation degree cannot be empty.\n";
        } else if ( ui->lineEditClockConsecutiveGapsCompare->text() == "" ) {
            *errorString += "Number of consecutive gaps in clock interpolation cannot be empty.\n";
        } else if ( ui->lineEditClockMaxGapsCompare->text() == "" ) {
            *errorString += "Number of maximum gaps in clock interpolation cannot be empty.\n";
        } else if ( ui->lineEditOrbitMaxGapsCompare->text().toInt()< ui->lineEditOrbitConsecutiveGapsCompare->text().toInt()) {
            *errorString += "Number of maximum gaps in orbit interpolation must be equal or greater than then number of consecutive gaps.\n";
        } else if ( ui->lineEditClockMaxGapsCompare->text().toInt()< ui->lineEditClockConsecutiveGapsCompare->text().toInt()) {
            *errorString += "Number of maximum gaps in clock interpolation must be equal or greater than then number of consecutive gaps.\n";
        } else {
            if ( ui->lineEditOrbitInterpolationDegreeCompare->text().toInt() !=10) {
                *saveString += "-model:orbit:deg " + ui->lineEditOrbitInterpolationDegreeCompare->text() + "\n";
                *runString << "-model:orbit:deg" << ui->lineEditOrbitInterpolationDegreeCompare->text();
            }
            if (ui->lineEditOrbitConsecutiveGapsCompare->text().toInt()!=8) {
                *saveString += "-model:orbmaxgaps " + ui->lineEditOrbitConsecutiveGapsCompare->text() + "\n";
                *runString << "-model:orbmaxgaps" << ui->lineEditOrbitConsecutiveGapsCompare->text();
            }
            if (ui->lineEditOrbitMaxGapsCompare->text().toInt()!=16) {
                *saveString += "-model:orbtotmaxgaps " + ui->lineEditOrbitMaxGapsCompare->text() + "\n";
                *runString << "-model:orbtotmaxgaps" << ui->lineEditOrbitMaxGapsCompare->text();
            }
            if ( ui->lineEditClockInterpolationDegreeCompare->text().toInt()!=0) {
                *saveString += "-model:clock:deg " + ui->lineEditClockInterpolationDegreeCompare->text() + "\n";
                *runString << "-model:clock:deg" << ui->lineEditClockInterpolationDegreeCompare->text();
            }
            if (ui->lineEditClockConsecutiveGapsCompare->text().toInt()!=2) {
                *saveString += "-model:clkmaxgaps " + ui->lineEditClockConsecutiveGapsCompare->text() + "\n";
                *runString << "-model:clkmaxgaps" << ui->lineEditClockConsecutiveGapsCompare->text() + "\n";
            }
            if (ui->lineEditClockMaxGapsCompare->text().toInt()!=4) {
                *saveString += "-model:clktotmaxgaps " + ui->lineEditClockMaxGapsCompare->text() + "\n";
                *runString << "-model:clktotmaxgaps" << ui->lineEditClockMaxGapsCompare->text() + "\n";
            }
        }
        //Current or Previous sample interpolation option for concatenated orbit files
        if (ui->radioButtonOrbitCurrentDayCompare->isChecked()==true) {
            //This is not the default option
            *saveString += "-model:orbprevsample\n";
            *runString << "-model:orbprevsample";
        }
        if (ui->radioButtonClockCurrentDayCompare->isChecked()==true) {
            //This is not the default option
            *saveString += "-model:clkprevsample\n";
            *runString << "-model:clkprevsample";
        }
    }

    //Check Output file
    if ( ui->lineEditOutputFileCompare->text() == "" ) {
        *errorString += "Output file is empty.\n";
    } else if (this->checknonASCIIcharacters(ui->lineEditOutputFileCompare->text())==1) {
        *errorString += "Output file has non ASCII characters\n";
    } else {
        *saveString += "-output:file " + ui->lineEditOutputFileCompare->text() + "\n";
        *runString << "-output:file" << ui->lineEditOutputFileCompare->text();
    }

    //Check output messages
    //All compare messages are by default enabled
    if (ui->checkBoxPrintInfoCompare->isChecked()==false) {
        *saveString += "--print:info\n";
        *runString << "--print:info";
    }
    if (ui->checkBoxPrintSatdiffCompare->isChecked()==false) {
       *saveString += "--print:satdiff\n";
       *runString << "--print:satdiff";
       NumMessages--;
    }
    if (ui->checkBoxPrintSatstatCompare->isChecked()==false) {
       *saveString += "--print:satstat\n";
       *runString << "--print:satstat";
       NumMessages--;
    }
    if (ui->checkBoxPrintSatstattotCompare->isChecked()==false) {
       *saveString += "--print:satstattot\n";
       *runString << "--print:satstattot";
       NumMessages--;
    }
    if (NumMessages==0) {
        *errorString += "One or more of these output messages must be selected: SATDIFF, SATSTAT or SATSTATTOT.\n";
    }
}

void gLAB_GUI::compareOrbitsLoadParameters(QFile *file) {

    QString line;
    QString option;
    QString userInput;
    QString userInputSingleSpace;
    QString errorString = "";
    QString warningString = "";
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
    int OrbitSP3first=-1;
    int numOutput=0;
    int HashPos;

    //First loop: Check for errors
    while ( !InputFile.atEnd() ) {
        line = QString(InputFile.readLine());
        if ( line == "") continue; //Do not erase this instruction or it will crash in Windows if the file has empty lines
        if ( line.at(0) == '#' || line.at(0) == '\n' || line.at(0) == '\r') continue;
        line.remove(QRegularExpression("^\\s+"));
        if ( line == "") continue; //Do not erase this instruction or it will crash in Windows if the line only contained spaces and it has been emptied
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
            if(numOrb==0) OrbitSP3first=0;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("Navigation", &warningString,&errorString,userInput);
            }
        } else if ( QString::compare(option, "-input:sp3", Qt::CaseInsensitive)==0  ) {
            numSP3++;
            numInputOrbFiles++;
            if(numOrb==0) OrbitSP3first=0;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("SP3", &warningString,&errorString,userInput);
            }
        } else if ( QString::compare(option, "-input:orb", Qt::CaseInsensitive)==0  ) {
            numOrb++;
            numInputOrbFiles++;
            if(numNav==0 && numSP3==0) OrbitSP3first=1;
            else OrbitSP3first=0;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("SP3 orbit", &warningString,&errorString,userInput);
            }
        } else if ( QString::compare(option, "-input:clk", Qt::CaseInsensitive)==0 ) {
            numClk++;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("Clock", &warningString,&errorString,userInput);
            }
        } else if ( QString::compare(option, "-input:ant", Qt::CaseInsensitive)==0 ) {
            numAnt++;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("ANTEX", &warningString,&errorString,userInput);
            }
        } else if ( QString::compare(option, "--model:satphasecenter", Qt::CaseInsensitive)==0 ) {
            noAntParameter=1;
        } else if ( QString::compare(option, "-output:file", Qt::CaseInsensitive)==0 ) {
            numOutput++;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("Output", &warningString,&errorString,userInput);
            }
        } else if ( QString::compare(option, "--model:satphasecenter", Qt::CaseInsensitive)==0 ) {
            noAntParameter=1;
        }
    }

    //Check for errors in number of files
    if (numInputOrbFiles>2) {
        //More than one orbit file given
        if (numNav>2) {
            errorString += "More than two navigation files ('-input:nav' option) are provided.\n";
        }
        if (numSP3>2) {
            errorString += "More than two SP3 file ('-input:sp3' option) are provided.\n";
        }
        if (numOrb>2) {
            errorString += "More than two orbit SP3 file ('-input:orb' option) are provided.\n";
        }
        if (numNav>0 && numSP3>0 && numOrb>0) {
            errorString += "Navigation file, SP3 file and orbit SP3 file were provided, but only two types can be given.\n";
        } else if (numNav>0 && numSP3>1) {
            errorString += "One navigation file and two SP3 files were provided, but only two files can be given.\n";
        } else if (numNav>0 && numOrb>1) {
            errorString += "One navigation file and two orbit SP3 files were provided, but only two files can be given.\n";
        } else if (numNav>1 && numSP3>0) {
            errorString += "Two navigation files and one SP3 files were provided, but only two files can be given.\n";
        } else if (numNav>1 && numOrb>0) {
            errorString += "Two navigation files and one orbit SP3 file were provided, but only two files can be given.\n";
        } else if (numSP3>0 && numOrb>1) {
            errorString += "One SP3 file and two orbit SP3 files were provided, but only two files can be given.\n";
        } else if (numSP3>1 && numOrb>0) {
            errorString += "Two SP3 files and one orbit SP3 file were provided, but only two files can be given.\n";
        }
    }

    //Check number of CLK files
    if (numClk>2) {
        errorString += "More than two CLK file ('-input:clk' option) are provided.\n";
    } else if (numClk<numOrb) {
        errorString += "There are more CLK files ('-input:clk' option) than orbit SP3 files provided.\n";
    }
    //Check if a orbit SP3 was given but not a CLK file
    if (numOrb!= numClk) {
        warningString += "Number of orbit SP3 files provided do not match the number of clock files given.\n";
    }

    //Check if more than ANTEX was given
    if (numAnt>1) {
        errorString += "More than one ANTEX file ('-input:ant' option) is provided.\n";
    }
    //Check if ANTEX file provided, but option for no ANTEX provided
    if (numAnt>0 && noAntParameter==1) {
        warningString += "ANTEX file provided, but also option to not to use ANTEX is provided. Last action read will prevail.\n";
    }
    //Check number of output files
    if (numOutput>1) {
        errorString += "More than one Output file ('-output:file' option) is provided.\n";
    }

    //If errors ocurred, show them and return
    if (!errorString.isEmpty()) {
        messageBox.critical(0, "Errors found",
                            "gLAB did not load the the configuration file due to the following errors:\n\n" + errorString);
        return;
    }
    //Second loop: Load parameters
    file->seek(0); //Go back to beginning of file
    setInitialCompareOrbitValues(); //Set default values in compare page

    numInputOrbFiles=0;

    while ( !InputFile.atEnd() ) {
        line = QString(InputFile.readLine());
        if ( line == "") continue; //Do not erase this instruction or it will crash in Windows if the file has empty lines
        if ( line.at(0) == '#' || line.at(0) == '\n' || line.at(0) == '\r') continue;
        line.remove(QRegularExpression("^\\s+"));
        if ( line == "") continue; //Do not erase this instruction or it will crash in Windows if the line only contained spaces and it has been emptied
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
                if(numInputOrbFiles==0) {
                    this->on_radioButtonOrbitNavCompareFile1_clicked();
                    ui->lineEditNavCompareFile1->setText(userInput);
                } else {
                    this->on_radioButtonOrbitNavCompareFile2_clicked();
                    ui->lineEditNavCompareFile2->setText(userInput);
                }
                numInputOrbFiles++;
            }
        } else if ( QString::compare(option, "-input:sp3", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                if(numInputOrbFiles==0) {
                    this->on_radioButtonOrbitPrecise1filesCompareFile1_clicked();
                    ui->lineEditPreciseFilesCompareSP3File1->setText(userInput);
                } else {
                    this->on_radioButtonOrbitPrecise1filesCompareFile2_clicked();
                    ui->lineEditPreciseFilesCompareSP3File2->setText(userInput);
                }
                numInputOrbFiles++;
            }
        } else if ( QString::compare(option, "-input:orb", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                if(numInputOrbFiles==0) {
                    this->on_radioButtonOrbitPrecise2filesCompareFile1_clicked();
                    ui->lineEditPreciseFilesCompareOrbFile1->setText(userInput);
                } else {
                    this->on_radioButtonOrbitPrecise2filesCompareFile2_clicked();
                    ui->lineEditPreciseFilesCompareOrbFile2->setText(userInput);
                }
                numInputOrbFiles++;
            }
        } else if ( QString::compare(option, "-input:clk", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                if(numOrb==1) {
                    if(OrbitSP3first==0) {
                        this->on_radioButtonOrbitPrecise2filesCompareFile2_clicked();
                        ui->lineEditPreciseFilesCompareClkFile2->setText(userInput);
                    } else {
                        this->on_radioButtonOrbitPrecise2filesCompareFile1_clicked();
                        ui->lineEditPreciseFilesCompareClkFile1->setText(userInput);
                    }
                } else {
                    if(numInputOrbFiles==0) {
                        this->on_radioButtonOrbitPrecise2filesCompareFile1_clicked();
                        ui->lineEditPreciseFilesCompareClkFile1->setText(userInput);
                    } else {
                        this->on_radioButtonOrbitPrecise2filesCompareFile2_clicked();
                        ui->lineEditPreciseFilesCompareClkFile2->setText(userInput);
                    }
                }
            }
        } else if ( QString::compare(option, "-input:ant", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                this->on_checkBoxAntexCompareOrbitsFile2_clicked(true);
                ui->lineEditAntexCompareOrbitsFile2->setText(userInput);
            }
        } else if ( QString::compare(option, "-pre:dec", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            }  else  if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                    warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<1E-4) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0.0001. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>86400.) {
                warningString += "Parameter '" + option + "' has to be smaller or equal than 86400. It was skipped.\n";
            } else {
                   ui->lineEditDecimationCompareOrbit->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
            }
        } else if ( QString::compare(option, "--pre:dec", Qt::CaseInsensitive)==0 ) {
            warningString += "Parameter '" + option + "' is not valid in compare orbit mode. It was skipped.\n";
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "-pre:eclipse", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxDiscardEclipseCompare->setChecked(false);
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "--pre:eclipse", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxDiscardEclipseCompare->setChecked(false);
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "-model:satclocks", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxSatClockOffsetCompare->setChecked(true);
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "--model:satclocks", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxSatClockOffsetCompare->setChecked(false);
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "-model:brdctranstime", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxCheckBroadcastTransmissionTimeCompare->setChecked(true);
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "--model:brdctranstime", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxCheckBroadcastTransmissionTimeCompare->setChecked(false);
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "-model:satellitehealth", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxDiscardUnhealthyCompare->setChecked(false);
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "--model:satellitehealth", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxDiscardUnhealthyCompare->setChecked(false);
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "-model:orbit:deg", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:orb:deg", Qt::CaseInsensitive)==0) {
            extraParametersToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
            } else {
               ui->lineEditOrbitInterpolationDegreeCompare->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "-model:orbmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditOrbitConsecutiveGapsCompare->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "--model:orbmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->lineEditOrbitConsecutiveGapsCompare->setText("0");
        } else if ( QString::compare(option, "-model:orbtotmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditOrbitMaxGapsCompare->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "--model:orbtotmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->lineEditOrbitMaxGapsCompare->setText("0");
        } else if ( (QString::compare(option, "-model:clock:deg", Qt::CaseInsensitive)==0 ) || QString::compare(option, "-model:clk:deg", Qt::CaseInsensitive)==0) {
            extraParametersToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditClockInterpolationDegreeCompare->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "-model:clkmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditClockConsecutiveGapsCompare->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "--model:clkmaxgaps", Qt::CaseInsensitive)==0 ) {
             extraParametersToWarningStr(0,&warningString,option,ParametersList);
             ui->lineEditClockConsecutiveGapsCompare->setText("0");
        } else if ( QString::compare(option, "-model:clktotmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditClockMaxGapsCompare->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "--model:clktotmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->lineEditClockMaxGapsCompare->setText("0");
        } else if ( QString::compare(option, "-model:satphasecenter", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            this->on_checkBoxAntexCompareOrbitsFile2_clicked(true);
        } else if ( QString::compare(option, "--model:satphasecenter", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            this->on_checkBoxAntexCompareOrbitsFile2_clicked(false);
        } else if ( QString::compare(option, "-model:orbprevsample", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->radioButtonOrbitCurrentDayCompare->setChecked(true);
            ui->radioButtonOrbitNextDayCompare->setChecked(false);
            this->on_groupBoxConcatenedPreciseFilesCompare_clicked(true);
        } else if ( QString::compare(option, "--model:orbprevsample", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->radioButtonOrbitCurrentDayCompare->setChecked(false);
            ui->radioButtonOrbitNextDayCompare->setChecked(true);
        } else if ( QString::compare(option, "-model:clkprevsample", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->radioButtonClockCurrentDayCompare->setChecked(true);
            ui->radioButtonClockNextDayCompare->setChecked(false);
            this->on_groupBoxConcatenedPreciseFilesCompare_clicked(true);
        } else if ( QString::compare(option, "--model:clkprevsample", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->radioButtonClockCurrentDayCompare->setChecked(false);
            ui->radioButtonClockNextDayCompare->setChecked(true);
        } else if ( QString::compare(option, "-output:file", Qt::CaseInsensitive)==0 ) {
            ui->lineEditOutputFileCompare->setText(userInput);
        } else if ( QString::compare(option, "--output:file", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            warningString += "Parameter '" + option + "' is for setting output messages to standard output, which will be lost after execution finishes. It was skipped.\n";
        } else if ( QString::compare(option, "-print:info", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintInfoCompare->setChecked(true);
        } else if ( QString::compare(option, "--print:info", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintInfoCompare->setChecked(false);
        } else if ( QString::compare(option, "-print:satdiff", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintSatdiffCompare->setChecked(true);
        } else if ( QString::compare(option, "--print:satdiff", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintSatdiffCompare->setChecked(false);
        } else if ( QString::compare(option, "-print:satstat", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintSatstatCompare->setChecked(true);
        } else if ( QString::compare(option, "--print:satstat", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintSatstatCompare->setChecked(false);
        } else if ( QString::compare(option, "-print:satstattot", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintSatstattotCompare->setChecked(true);
        } else if ( QString::compare(option, "--print:satstattot    ", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintSatstattotCompare->setChecked(false);
        } else if ( QString::compare(option, "-print:all", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxPrintInfoCompare->setChecked(true);
            ui->checkBoxPrintSatdiffCompare->setChecked(true);
            ui->checkBoxPrintSatstatCompare->setChecked(true);
            ui->checkBoxPrintSatstattotCompare->setChecked(true);
        } else if ( QString::compare(option, "-print:none", Qt::CaseInsensitive)==0 || QString::compare(option, "--print:none", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxPrintInfoCompare->setChecked(false);
            ui->checkBoxPrintSatdiffCompare->setChecked(false);
            ui->checkBoxPrintSatstatCompare->setChecked(false);
            ui->checkBoxPrintSatstattotCompare->setChecked(false);
        }
    }

    if ( ui->lineEditOrbitMaxGapsCompare->text().toInt()< ui->lineEditOrbitConsecutiveGapsCompare->text().toInt()) {
        warningString += "Number of maximum gaps in orbit interpolation must be equal or greater than then number of consecutive gaps.\n";
    } else if ( ui->lineEditClockMaxGapsCompare->text().toInt()< ui->lineEditClockConsecutiveGapsCompare->text().toInt()) {
        warningString += "Number of maximum gaps in clock interpolation must be equal or greater than then number of consecutive gaps.\n";
    }

    if (!warningString.isEmpty()) {
        messageBox.warning(0, "Errors found",
                            "gLAB loaded the configuration file, but found the following errors:\n\n" + warningString);
    }
}
