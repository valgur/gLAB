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


// Function to show or hide the line edit for the KML path
void gLAB_GUI::on_checkBoxKML_clicked(bool checked) {
    ui->frameKML->setHidden(!checked);
    ui->checkBoxKML->setChecked(checked);
	if(ui->checkBoxKML->isChecked() == true || ui->checkBoxKML0->isChecked() == true ) {
		ui->KMLOptionsFrame->setHidden(false);
        if (ui->groupBoxReferenceStation->isChecked()==true) {
            ui->checkBoxKMLRefStations->setHidden(false);
        } else {
            ui->checkBoxKMLRefStations->setHidden(true);
        }
	} else {
		ui->KMLOptionsFrame->setHidden(true);
	}
}

// Function to show or hide the line edit for the KML0 path
void gLAB_GUI::on_checkBoxKML0_clicked(bool checked) {
    ui->frameKML0->setHidden(!checked);
    ui->checkBoxKML0->setChecked(checked);
	if(ui->checkBoxKML->isChecked() == true || ui->checkBoxKML0->isChecked() == true ) {
		ui->KMLOptionsFrame->setHidden(false);
        if (ui->groupBoxReferenceStation->isChecked()==true) {
            ui->checkBoxKMLRefStations->setHidden(false);
        } else {
            ui->checkBoxKMLRefStations->setHidden(true);
        }
	} else {
        ui->KMLOptionsFrame->setHidden(true);
	}
}

// Function to show or hide the KML timestamps options when timestamps are activated
void gLAB_GUI::on_checkBox_KML_TimeStamps_clicked(bool checked) {
    ui->checkBox_KML_TimeStamps->setChecked(checked);
    //label_KML_Decimation is changed before unhiding it so there is no flickering in the screen
    if (ui->groupBoxStanfordESA->isChecked() == true && ui->checkBox_KML_TimeStamps->isChecked()==true && ui->checkBox_KML_Range->isChecked()==true ) {
        #ifndef Q_OS_WIN32
            if (this->width()<KMLOPTIONSREDUCETHRESHOLD) {
                //Only reduce names if they don't fit in the screen
                ui->label_KML_Decimation->setText("Dec");
                ui->checkBoxKMLGeoid->setText("Geoid H");
            }
        #endif
    } else {
        if (ui->label_KML_Decimation->text()=="Dec") {
            ui->label_KML_Decimation->setText("Decimation");
        }
        if (ui->checkBoxKMLGeoid->text()=="Geoid H") {
            ui->checkBoxKMLGeoid->setText("Geoid Height");
        }
    }
	ui->KMLTimeStampsFrame->setHidden(!checked);

}

// Function to show or hide the KML timestamps range when range for timestamps are activated
void gLAB_GUI::on_checkBox_KML_Range_clicked(bool checked) {
    ui->checkBox_KML_Range->setChecked(checked);
	ui->KMLTimeStampsRangeSubFrame->setHidden(!checked);
    if (ui->groupBoxStanfordESA->isChecked() == true && ui->checkBox_KML_TimeStamps->isChecked()==true && ui->checkBox_KML_Range->isChecked()==true ) {
        #ifndef Q_OS_WIN32
            if (this->width()<KMLOPTIONSREDUCETHRESHOLD) {
                //Only reduce names if they don't fit in the screen
                ui->label_KML_Decimation->setText("Dec");
                ui->checkBoxKMLGeoid->setText("Geoid H");
            }
        #endif
    } else {
        if (ui->label_KML_Decimation->text()=="Dec") {
            ui->label_KML_Decimation->setText("Decimation");
        }
        if (ui->checkBoxKMLGeoid->text()=="Geoid H") {
            ui->checkBoxKMLGeoid->setText("Geoid Height");
        }
    }
}

// Function to show or hide the line edit for the SP3 path and options
void gLAB_GUI::on_checkBoxOutputSP3_clicked(bool checked) {
    ui->checkBoxOutputSP3->setChecked(checked);
    ui->frameOutputSP3->setHidden(!checked);
    ui->frameOutputSP3Options->setHidden(!checked);
    if (ui->groupBoxReferenceStation->isChecked()==true) {
        ui->checkBoxSP3OutFileWriteSPPSolutions->setHidden(false);
    } else {
        ui->checkBoxSP3OutFileWriteSPPSolutions->setHidden(true);
    }
}

// Function to show or hide the line edit for the Ref file path and options
void gLAB_GUI::on_checkBoxOutRefFile_clicked(bool checked) {
    ui->checkBoxOutRefFile->setChecked(checked);
    ui->frameOutRefFile->setHidden(!checked);
    ui->frameOutRefFileOptions->setHidden(!checked);
    if (ui->groupBoxReferenceStation->isChecked()==true) {
        ui->frameOutReffileWriteSPPsolution->setHidden(false);
    } else {
        ui->frameOutReffileWriteSPPsolution->setHidden(true);
    }
}

////////////////////// Push buttons /////////////////////
// Open dialog to set the output filename and path
void gLAB_GUI::on_pushButtonOutputDestination_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    //dialog.setAcceptMode(QFileDialog::AcceptSave); //This to confirm overwriting files
    dialog.setNameFilter(tr("gLAB Output Files (*.out);;All Files (*)"));
    dialog.selectFile(".out");
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditOutputDestination->setText(QDir::toNativeSeparators(fileName[0]));
            //Set path for KML, KML0, SP3 and Stanford-ESA
            ui->lineEditKML->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/gLAB.kml"));
            ui->lineEditKML0->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/gLAB0.kml"));
            ui->lineEditOutputSP3->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/gLAB.sp3"));
            ui->lineEditOutRefFile->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/gLAB_ref.txt"));
            ui->lineEditOutputStanfordEsaPlot->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/gLAB_stfd-ESA_plot.txt"));
            ui->lineEditOutputframeStanfordESAallGeometries->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/gLAB_stfd-ESA_data.txt"));
        }
    }
}

// Open dialog to set the KML output filename and path
void gLAB_GUI::on_pushButtonOutputKML_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("KML Files (*.kml);;All Files (*)"));
    dialog.selectFile(".kml");
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditKML->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

// Open dialog to set the KML0 output filename and path
void gLAB_GUI::on_pushButtonOutputKML0_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("KML Files (*.kml);;All Files (*)"));
    dialog.selectFile(".kml");
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditKML0->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

// Open dialog to set the SP3 output filename and path
void gLAB_GUI::on_pushButtonOutputSP3_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("SP3 Files (*.sp3);;All Files (*)"));
    dialog.selectFile(".sp3");
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditOutputSP3->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

// Open dialog to set the Ref file output filename and path
void gLAB_GUI::on_pushButtonOutRefFile_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("Text Files (*.txt);;SP3 Files (*.sp3);;All Files (*)"));
    dialog.selectFile(".txt");
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditOutRefFile->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}


// Open dialog to set the Stanford-ESA plot output filename and path
void gLAB_GUI::on_pushButtonOutputStanfordEsaPlot_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("Stanford-ESA Plot Files (*.txt);;All Files (*)"));
    dialog.selectFile(".txt");
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditOutputStanfordEsaPlot->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

// Open dialog to set the Stanford-ESA data output filename and path
void gLAB_GUI::on_pushButtonOutputframeStanfordESAallGeometries_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("Stanford-ESA Data Files (*.txt);;All Files (*)"));
    dialog.selectFile(".txt");
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditOutputframeStanfordESAallGeometries->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}
////////////////// End of Push buttons //////////////////

///////////////// Start of Context menus (right-click menus) //////////////////
//Right-click menu in Output File label
void gLAB_GUI::labelOutputFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelOutputFile->mapToGlobal(pos);
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
            arguments << ui->lineEditOutputDestination->text();
        #elif defined(Q_OS_WIN32)
            program = QString("notepad");
            arguments << ui->lineEditOutputDestination->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditOutputDestination->text();
        #endif

        // Execute the program
        if (ui->lineEditOutputDestination->text() == "") {
            messageBox.warning(0, "Error","Output file is empty\n");
        } else if (this->fileExists(ui->lineEditOutputDestination->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputDestination->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputDestination->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

//Right-click menu in checkBoxKML
void gLAB_GUI::checkBoxKMLMenu(const QPoint& pos) {// this is a slot

    // for most widgets
    QPoint globalPos = ui->checkBoxKML->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open KML File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        if (ui->lineEditKML->text() == "") {
            messageBox.warning(0, "Error","KML file is empty\n");
        } else if (this->fileExists( ui->lineEditKML->text() ) == false ) {
            messageBox.critical(0, "Error","File '" + ui->lineEditKML->text() + "' does not exist.\n");
        } else {
            #ifdef Q_OS_LINUX
                if ( !QDesktopServices::openUrl(QUrl::fromLocalFile(ui->lineEditKML->text()))) {
                    messageBox.critical(0, "Errors found", "Google Earth could not be executed for opening '" + ui->lineEditKML->text() + "' file.\n");
                }
            #elif defined(Q_OS_WIN32)
                QString str = ui->lineEditKML->text().replace("\\","/");
                if ( !QDesktopServices::openUrl(QUrl::fromLocalFile(str)) ) {
                    messageBox.critical(0, "Errors found", "Google Earth could not be executed for opening '" + ui->lineEditKML->text() + "' file.\n");
                }
            #elif defined(Q_OS_MAC)
                // Execute the program

                QProcess *processUserManual = new QProcess(this);
                QStringList arguments;
                arguments << ui->lineEditKML->text();
                QString program = QString("open");
                // Execute the program
                processUserManual->start(program,arguments);
                if (processUserManual->state()==QProcess::NotRunning) {
                   messageBox.critical(0, "Errors found", "Google Earth could not be executed for opening '" + ui->lineEditKML->text() + "' file.\n");
                }
            #endif
        }
    }
}

//Right-click menu in checkBoxKML0
void gLAB_GUI::checkBoxKML0Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->checkBoxKML0->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open KML0 File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        if (ui->lineEditKML0->text() == "") {
            messageBox.warning(0, "Error","KML0 file is empty\n");
        } else if (this->fileExists( ui->lineEditKML0->text() ) == false ) {
            messageBox.critical(0, "Error","File '" + ui->lineEditKML0->text() + "' does not exist.\n");
        } else {
            // Based on the OS open the text editor
            #ifdef Q_OS_LINUX
                if ( !QDesktopServices::openUrl(QUrl::fromLocalFile(ui->lineEditKML0->text()))) {
                    messageBox.critical(0, "Errors found", "Google Earth could not be executed for opening '" + ui->lineEditKML0->text() + "' file.\n");
                }
            #elif defined(Q_OS_WIN32)
                QString str = ui->lineEditKML0->text().replace("\\","/");
                if ( !QDesktopServices::openUrl(QUrl::fromLocalFile(str)) ) {
                    messageBox.critical(0, "Errors found", "Google Earth could not be executed for opening '" + ui->lineEditKML0->text() + "' file.\n");
                }
            #elif defined(Q_OS_MAC)
                // Execute the program

                QProcess *processUserManual = new QProcess(this);
                QStringList arguments;
                arguments << ui->lineEditKML0->text();
                QString program = QString("open");
                // Execute the program
                processUserManual->start(program,arguments);
                if (processUserManual->state()==QProcess::NotRunning) {
                   messageBox.critical(0, "Errors found", "Google Earth could not be executed for opening '" + ui->lineEditKML0->text() + "' file.\n");
                }
            #endif
        }
    }
}

//Right-click menu in SP3 checkbox
void gLAB_GUI::checkBoxOutputSP3Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->checkBoxOutputSP3->mapToGlobal(pos);
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
            arguments << ui->lineEditOutputSP3->text();
        #elif defined(Q_OS_WIN32)
            program = QString("notepad");
            arguments << ui->lineEditOutputSP3->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditOutputSP3->text();
        #endif

        // Execute the program
        if (ui->lineEditOutputSP3->text() == "") {
            messageBox.warning(0, "Error","SP3 file is empty\n");
        } else if (this->fileExists(ui->lineEditOutputSP3->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputSP3->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputSP3->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

//Right-click menu in Ref file checkbox
void gLAB_GUI::checkBoxOutRefFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->checkBoxOutRefFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open Reference File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditOutRefFile->text();
        #elif defined(Q_OS_WIN32)
            program = QString("notepad");
            arguments << ui->lineEditOutRefFile->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditOutRefFile->text();
        #endif

        // Execute the program
        if (ui->lineEditOutRefFile->text() == "") {
            messageBox.warning(0, "Error","Reference file is empty\n");
        } else if (this->fileExists(ui->lineEditOutRefFile->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutRefFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutRefFile->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}


//Right-click menu in Stanford ESA plot label
void gLAB_GUI::labelStfdESAPlotFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelStfdESAPlotFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open Stanford-ESA Plot File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditOutputStanfordEsaPlot->text();
        #elif defined(Q_OS_WIN32)
            program = QString("notepad");
            arguments << ui->lineEditOutputStanfordEsaPlot->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditOutputStanfordEsaPlot->text();
        #endif

        // Execute the program
        if (ui->lineEditOutputStanfordEsaPlot->text() == "") {
            messageBox.warning(0, "Error","Stanford-ESA Plot file is empty\n");
        } else if (this->fileExists(ui->lineEditOutputStanfordEsaPlot->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputStanfordEsaPlot->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputStanfordEsaPlot->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

//Right-click menu in Stanford ESA data file label
void gLAB_GUI::labelStfdESADataFileMenu(const QPoint& pos) {  // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelStfdESADataFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open Stanford-ESA Data File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditOutputframeStanfordESAallGeometries->text();
        #elif defined(Q_OS_WIN32)
            program = QString("notepad");
            arguments << ui->lineEditOutputframeStanfordESAallGeometries->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditOutputframeStanfordESAallGeometries->text();
        #endif

        // Execute the program
        if (ui->lineEditOutputframeStanfordESAallGeometries->text() == "") {
            messageBox.warning(0, "Error","Stanford-ESA Data file is empty\n");
        } else if (this->fileExists(ui->lineEditOutputframeStanfordESAallGeometries->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputframeStanfordESAallGeometries->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputframeStanfordESAallGeometries->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}
///////////////// End of Context menus (right-click menus) //////////////////

// Function to set on all prints for Common Navigation Messages
void gLAB_GUI::on_pushButtonCommonNavigationMessagesAll_clicked() {
    ui->checkBoxPrintInfo->setChecked(true);
    ui->checkBoxPrintCS->setChecked(true);
    ui->checkBoxPrintInput->setChecked(true);
    ui->checkBoxPrintMeas->setChecked(true);
    ui->checkBoxPrintModel->setChecked(true);
    ui->checkBoxPrintEpochsat->setChecked(true);
    ui->checkBoxPrintSatsel->setChecked(true);
    ui->checkBoxPrintPrefit->setChecked(true);
    ui->checkBoxPrintPostfit->setChecked(true);
    ui->checkBoxPrintFilter->setChecked(true);
    ui->checkBoxPrintOutput->setChecked(true);
    ui->checkBoxPrintUsererror->setChecked(true);
}

// Function to set off all prints for Common Navigation Messages
void gLAB_GUI::on_pushButtonCommonNavigationMessagesNone_clicked() {
    ui->checkBoxPrintInfo->setChecked(false);
    ui->checkBoxPrintCS->setChecked(false);
    ui->checkBoxPrintInput->setChecked(false);
    ui->checkBoxPrintMeas->setChecked(false);
    ui->checkBoxPrintModel->setChecked(false);
    ui->checkBoxPrintEpochsat->setChecked(false);
    ui->checkBoxPrintSatsel->setChecked(false);
    ui->checkBoxPrintPrefit->setChecked(false);
    ui->checkBoxPrintPostfit->setChecked(false);
    ui->checkBoxPrintFilter->setChecked(false);
    ui->checkBoxPrintOutput->setChecked(false);
    ui->checkBoxPrintUsererror->setChecked(false);
}

// Function to set on all prints for Orbit Comparison Messages
void gLAB_GUI::on_pushButtonOrbitsComparisonMessagesAll_clicked() {
    ui->checkBoxPrintSatdiff->setChecked(true);
    ui->checkBoxPrintSatstat->setChecked(true);
    ui->checkBoxPrintSatstattot->setChecked(true);
    ui->checkBoxPrintSatpvt->setChecked(true);
}

// Function to set off all prints for Orbit Comparison Messages
void gLAB_GUI::on_pushButtonOrbitsComparisonMessagesNone_clicked() {
    ui->checkBoxPrintSatdiff->setChecked(false);
    ui->checkBoxPrintSatstat->setChecked(false);
    ui->checkBoxPrintSatstattot->setChecked(false);
    ui->checkBoxPrintSatpvt->setChecked(false);
}

// Function to set on all prints for SBAS Messages
void gLAB_GUI::on_pushButtonSbasMessagesAll_clicked() {
    ui->checkBoxPrintSbasout->setChecked(true);
    ui->checkBoxPrintSbasvar->setChecked(true);
    ui->checkBoxPrintSbascor->setChecked(true);
    ui->checkBoxPrintSbasiono->setChecked(true);
    ui->checkBoxPrintSbasunsel->setChecked(true);
    ui->checkBoxPrintSbasunused->setChecked(true);
}

// Function to set off all prints for SBAS Messages
void gLAB_GUI::on_pushButtonSbasMessagesNone_clicked() {
    ui->checkBoxPrintSbasout->setChecked(false);
    ui->checkBoxPrintSbasvar->setChecked(false);
    ui->checkBoxPrintSbascor->setChecked(false);
    ui->checkBoxPrintSbasiono->setChecked(false);
    ui->checkBoxPrintSbasunsel->setChecked(false);
    ui->checkBoxPrintSbasunused->setChecked(false);
}

// Function to set on all prints for DGNSS Messages
void gLAB_GUI::on_pushButtonDgnssMessagesAll_clicked() {
    ui->checkBoxPrintDgnss->setChecked(true);
    ui->checkBoxPrintDgnssunused->setChecked(true);
}


// Function to set off all prints for DGNSS Messages
void gLAB_GUI::on_pushButtonDgnssMessagesNone_clicked() {
    ui->checkBoxPrintDgnss->setChecked(false);
    ui->checkBoxPrintDgnssunused->setChecked(false);
}

// Function to show or hide the Stanford-ESA options
void gLAB_GUI::on_groupBoxStanfordESA_clicked(bool checked) {

    //Change first the KML text before enabling the groupBoxStanfordESA so the groupbox only resizes once
    if (checked == true && ui->checkBox_KML_TimeStamps->isChecked()==true && ui->checkBox_KML_Range->isChecked()==true ) {
        #ifndef Q_OS_WIN32
            if (this->width()<KMLOPTIONSREDUCETHRESHOLD) {
                ui->label_KML_Decimation->setText("Dec");
                ui->checkBoxKMLGeoid->setText("Geoid H");
            }
        #endif
    } else {
        if (ui->label_KML_Decimation->text()=="Dec") {
            ui->label_KML_Decimation->setText("Decimation");
        }
        if (ui->checkBoxKMLGeoid->text()=="Geoid H") {
            ui->checkBoxKMLGeoid->setText("Geoid Height");
        }
    }
    ui->groupBoxStanfordESA->setChecked(checked);
    ui->frameStanfordESA->setHidden(!checked);
    ui->frameOutputStanfordEsaPlot->setHidden(!checked);
    if ( checked == false ) ui->frameOutputframeStanfordESAallGeometries->setHidden(true);
    else if ( ui->checkBoxStanfordESAallGeometries->isChecked() == true )
        ui->frameOutputframeStanfordESAallGeometries->setHidden(false);
}

//  Function to show or hide the Stanford-ESA all geometries options
void gLAB_GUI::on_checkBoxStanfordESAallGeometries_clicked(bool checked) {
    ui->checkBoxStanfordESAallGeometries->setChecked(checked);
    if ( ui->groupBoxStanfordESA->isChecked() == true )
        ui->frameOutputframeStanfordESAallGeometries->setHidden(!checked);
    ui->frameStanfordESAallGeometries->setHidden(!checked);
}

// Function to show or hide the content of the summary options when printSummary is checked
void gLAB_GUI::on_checkBoxPrintSummary_clicked(bool checked) {
    ui->checkBoxPrintSummary->setChecked(checked);
    ui->frameSummaryOptions->setHidden(!checked);
}

// Function to disable "Start time summary" when "wait for day start" is clicked
void gLAB_GUI::on_checkBoxWaitforDayStart_clicked(bool checked) {
    ui->checkBoxWaitforDayStart->setChecked(checked);
    if (checked==true) {
        this->on_checkBoxStartTimeSummary_clicked(false);
    }
}

// Function to disable "wait for day start" when "Start time of summary" is clicked
void gLAB_GUI::on_checkBoxStartTimeSummary_clicked(bool checked) {
    ui->checkBoxStartTimeSummary->setChecked(checked);
    if (checked==true) {
        ui->checkBoxWaitforDayStart->setChecked(false);
    }
    ui->dateTimeEditStartTimeSummary->setHidden(!checked);
}

// Function to get the OUTPUT options and errors
void gLAB_GUI::getOutputOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString) {
    int printAll=0, printNone=0;
    QDate date;
    QTime time;
    *warningString = *warningString + ""; //This is to avoid the unused parameter warning
    // Header of the output section
    *saveString += "\n";
    *saveString += "###################################################\n";
    *saveString += "#     OUTPUT section\n";
    *saveString += "###################################################\n\n";
    // Output Destination
    if ( ui->lineEditOutputDestination->text() == "" ) {
        *errorString += "OUTPUT: Output file in cannot be empty.\n";
    } else if (this->checknonASCIIcharacters(ui->lineEditOutputDestination->text())==1) {
        *errorString += "OUTPUT: Output file has non ASCII characters\n";
    } else {
        *saveString += "-output:file " + ui->lineEditOutputDestination->text() + "\n";
        *runString << "-output:file" << ui->lineEditOutputDestination->text();
    }
    // KML
    if ( ui->checkBoxKML->isChecked() == true ) {
        if ( ui->lineEditKML->text() == "" ) {
            *errorString += "OUTPUT: KML file cannot be empty.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditKML->text())==1) {
            *errorString += "OUTPUT: KML file has non ASCII characters\n";
        } else {
            *saveString += "-output:kml " + ui->lineEditKML->text() + "\n";
            *runString << "-output:kml" << ui->lineEditKML->text();
        }
    }
    // KML0
    if ( ui->checkBoxKML0->isChecked() == true ) {
        if ( ui->lineEditKML0->text() == "" ) {
            *errorString += "OUTPUT: KML0 file cannot be empty.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditKML0->text())==1) {
            *errorString += "OUTPUT: KML0 file has non ASCII characters\n";
        } else {
            *saveString += "-output:kml0 " + ui->lineEditKML0->text() + "\n";
            *runString << "-output:kml0" << ui->lineEditKML0->text();
        }
    }
    // KML options
    if ( ui->checkBoxKML->isChecked() == true || ui->checkBoxKML0->isChecked() == true ) {
        //Reference station in DGNSS
        if (ui->groupBoxReferenceStation->isChecked()==true && ui->checkBoxKMLRefStations->isChecked()==true) {
            if (WriteAllParameters==1) {
                *saveString += "-output:kml:refsta\n";
                *runString << "-output:kml:refsta";
            }
        } else if (ui->groupBoxReferenceStation->isChecked()==true && ui->checkBoxKMLRefStations->isChecked()==false) {
            //In DGNSS, reference stations are enabled by default
            *saveString += "--output:kml:refsta\n";
            *runString << "--output:kml:refsta";
        }
        //Geoid Height
        if (ui->checkBoxKMLGeoid->isChecked()==true) {
            //Geoid height enabled by default in all modes
            if (WriteAllParameters==1) {
                *saveString += "-output:kml:egm96geoid\n";
                *runString << "-output:kml:egm96geoid";
            }
        } else {
            *saveString += "--output:kml:egm96geoid\n";
            *runString << "--output:kml:egm96geoid";
        }
        //TimeStamps
        if (ui->checkBox_KML_TimeStamps->isChecked()==true) {
            //Timestamp Decimation
            if (ui->lineEditKML_Dec->text()=="") {
                *errorString += "OUTPUT: KML timeStamp decimation cannot be empty.\n";
            } else if (ui->lineEditKML_Dec->text().toDouble() == 0.) {
                *errorString += "OUTPUT: KML timeStamp decimation cannot be 0.\n";
            } else if (ui->lineEditKML_Dec->text().toDouble() != 30.) {
                //Non default decimation
                *saveString += "-output:kml:tstampdec " + ui->lineEditKML_Dec->text() + "\n";
                *runString << "-output:kml:tstampdec" << ui->lineEditKML_Dec->text();
            } else {
                //Default decimation
                *saveString += "-output:kml:tstamp\n";
                *runString << "-output:kml:tstamp";
                 if (WriteAllParameters==1) {
                     *saveString += "-output:kml:tstampdec 30\n";
                     *runString << "-output:kml:tstampdec" <<" 30";
                 }
            }
            //TimeStamp Range
            if (ui->checkBox_KML_TimeStamps->isChecked()==true) {
                //Set range
                if (ui->lineEditKML_From->text()=="" || ui->lineEditKML_To->text()=="") {
                    *errorString += "OUTPUT: KML timeStamp range values cannot be empty.\n";
                } else if (ui->lineEditKML_From->text()=="-" && ui->lineEditKML_To->text()=="-") {
                    //Values are '-' and '-'. This is equivalent of a range for the whole file, or no range at all
                } else if ( (ui->lineEditKML_From->text().toDouble()<0.) || (ui->lineEditKML_To->text().toDouble()<0.) ) {
                    *errorString += "OUTPUT: KML timeStamp range values must be positive.\n";
                } else if ((ui->lineEditKML_From->text()!="-" && ui->lineEditKML_To->text()!="-") && (ui->lineEditKML_From->text().toDouble()<ui->lineEditKML_To->text().toDouble()) ) {
                    *errorString += "OUTPUT: KML timeStamp range values must have a ending epoch greater than the initial epoch.\n";
                } else {
                    //Only set the range if values are different from "-" and "-", as this is a range for all the file, equivalent as no range
                    *saveString += "-output:kml:tstamprange " + ui->lineEditKML_From->text() + " " + ui->lineEditKML_To->text() +"\n";
                    *runString << "-output:kml:tstamprange" << ui->lineEditKML_From->text() << ui->lineEditKML_To->text();
                }
            }
        }
    }
    // SP3
    if ( ui->checkBoxOutputSP3->isChecked() == true ) {
        if ( ui->lineEditOutputSP3->text() == "" ) {
            *errorString += "OUTPUT: SP3 file cannot be empty.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditOutputSP3->text())==1) {
            *errorString += "OUTPUT: SP3 file has non ASCII characters\n";
        } else {
            *saveString += "-output:sp3 " + ui->lineEditOutputSP3->text() + "\n";
            *runString << "-output:sp3" << ui->lineEditOutputSP3->text();
        }
        //Check constellation letter
        if (ui->lineEditSP3Letter->text()=="") {
            *errorString += "OUTPUT: SP3 constellation letter cannot be empty.\n";
        } else if( ui->lineEditSP3Letter->text()!="L" || WriteAllParameters==1) {
            //Default constellation letter is "L"
            *saveString += "-output:sp3:letter " + ui->lineEditSP3Letter->text() + "\n";
            *runString << "-output:sp3:letter" << ui->lineEditSP3Letter->text();
        }
        //Check PRN Number
        if (ui->lineEditSP3PRN->text()=="") {
            *errorString += "OUTPUT: SP3 PRN number cannot be empty.\n";
        } else if (ui->lineEditSP3PRN->text().toInt() == 0) {
            *errorString += "OUTPUT: SP3 PRN number cannot be 0.\n";
        } else if( ui->lineEditSP3PRN->text().toInt() != 9  || WriteAllParameters==1) {
            //Default PRN is 9
            *saveString += "-output:sp3:prn " + ui->lineEditSP3PRN->text() + "\n";
            *runString << "-output:sp3:prn" << ui->lineEditSP3PRN->text();
        }
        //Write SPP solution in DGNSS
        if (ui->groupBoxReferenceStation->isChecked()==true && ui->checkBoxSP3OutFileWriteSPPSolutions->isChecked()==false) {
            *saveString += "--output:sp3:dgnssonly\n";
            *runString << "--output:sp3:dgnssonly";
        } else if (ui->groupBoxReferenceStation->isChecked()==true && ui->checkBoxSP3OutFileWriteSPPSolutions->isChecked()==true) {
            //Not writing SPP solution is the default
            if (WriteAllParameters==1) {
                *saveString += "-output:sp3:dgnssonly\n";
                *runString << "-output:sp3:dgnssonly";
            }
        }
    }
    // Reference file
    if ( ui->checkBoxOutRefFile->isChecked() == true ) {
        if ( ui->lineEditOutRefFile->text() == "" ) {
            *errorString += "OUTPUT: Reference file cannot be empty.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditOutRefFile->text())==1) {
            *errorString += "OUTPUT: Reference file has non ASCII characters\n";
        } else {
            *saveString += "-output:refpos " + ui->lineEditOutRefFile->text() + "\n";
            *runString << "-output:refpos" << ui->lineEditOutRefFile->text();
        }
        //Check date format
        if ( ui->radioButtonOutRefFileYearDoYSoD->isChecked() == true ) {
            //Writing in Year/DoY/SoD format is the default
            if (WriteAllParameters==1) {
                *saveString += "-output:refpos:doy\n";
                *runString << "-output:refpos:doy";
            }
        } else if (ui->radioButtonOutRefFileCalendar->isChecked() == true ) {
            *saveString += "-output:refpos:caltime\n";
            *runString << "-output:refpos:caltime";
        } else {
            *saveString += "-output:refpos:gpsweek\n";
            *runString << "-output:refpos:gpsweek";
        }
        //Check coordinates format
        if ( ui->radioButtonOutRefFileCartesian->isChecked() == true ) {
            //Writing in cartesian coordinates is the default
            if (WriteAllParameters==1) {
                *saveString += "--output:refpos:geodetic\n";
                *runString << "--output:refpos:geodetic";
            }
        } else {
            *saveString += "-output:refpos:geodetic\n";
            *runString << "-output:refpos:geodetic";
        }
        //Write SPP solution in DGNSS
        if (ui->groupBoxReferenceStation->isChecked()==true && ui->checkBoxRefOutFileWriteSPPSolutions->isChecked()==false) {
            *saveString += "--output:refpos:dgnssonly\n";
            *runString << "--output:refpos:dgnssonly";
        } else if (ui->groupBoxReferenceStation->isChecked()==true && ui->checkBoxRefOutFileWriteSPPSolutions->isChecked()==true) {
            //Not writing SPP solution is the default
            if (WriteAllParameters==1) {
                *saveString += "-output:refpos:dgnssonly\n";
                *runString << "-output:refpos:dgnssonly";
            }
        }
    }
    // Stanford-ESA
    if ( ui->labelCurrentTemplate->text() == "SBAS" || ui->groupBoxSbas->isChecked()==true ) {
        // Plot
        if ( ui->groupBoxStanfordESA->isChecked() == true ) {
            if ( ui->lineEditOutputStanfordEsaPlot->text() == "" ) {
                *errorString += "OUTPUT: Stanford-ESA plot file cannot be empty.\n";
            } else if (this->checknonASCIIcharacters(ui->lineEditOutputStanfordEsaPlot->text())==1) {
                *errorString += "OUTPUT: Stanford-ESA plot file has non ASCII characters\n";
            } else {
                *saveString += "-output:stfdesa " + ui->lineEditOutputStanfordEsaPlot->text() + "\n";
                *runString << "-output:stfdesa" << ui->lineEditOutputStanfordEsaPlot->text();
            }
        }
        // Data
        if ( ui->groupBoxStanfordESA->isChecked() == true && ui->checkBoxStanfordESAallGeometries->isChecked() == true ) {
            if ( ui->lineEditOutputframeStanfordESAallGeometries->text() == "" ) {
                *errorString += "OUTPUT: Stanford-ESA data file cannot be empty.\n";
            } else if (this->checknonASCIIcharacters(ui->lineEditOutputframeStanfordESAallGeometries->text())==1) {
                *errorString += "OUTPUT: Stanford-ESA data file has non ASCII characters\n";
            } else {
                *saveString += "-output:stfdesaloi " + ui->lineEditOutputframeStanfordESAallGeometries->text() + "\n";
                *runString << "-output:stfdesaloi" << ui->lineEditOutputframeStanfordESAallGeometries->text();
            }
        }
    }

    //Satellite output velocity (only set it if velocity groupbox is not hidden)
    if (ui->frameOutputSatVel->isHidden()==false) {
        //Default output is ECEF
        if (ui->radioButtonSatVelECEF->isChecked()==true) {
            if (WriteAllParameters==1) {
                *saveString += "-output:satvel ITRF\n";
                *runString << "-output:satvel" << "ITRF";
            }
        } else if (ui->radioButtonSatVelInertial->isChecked()==true) {
            *saveString += "-output:satvel inertial\n";
            *runString << "-output:satvel" << "inertial";
        }
    }

    // Messages

    if (ui->checkBoxPrintInfo->isChecked() == true && ui->checkBoxPrintCS->isChecked() == true && ui->checkBoxPrintInput->isChecked() == true && ui->checkBoxPrintMeas->isChecked() == true
            && ui->checkBoxPrintModel->isChecked() == true && ui->checkBoxPrintEpochsat->isChecked() == true && ui->checkBoxPrintPrefit->isChecked() == true
            &&  ui->checkBoxPrintPostfit->isChecked() == true && ui->checkBoxPrintSatsel->isChecked() == true && ui->checkBoxPrintFilter->isChecked() == true
            && ui->checkBoxPrintOutput->isChecked() == true && ui->checkBoxPrintUsererror->isChecked() == true && ui->checkBoxPrintSummary->isChecked() == true ) {
        if ( ui->groupBoxSbas->isChecked()==true || ui->labelCurrentTemplate->text() == "SBAS" ) {
            if (ui->checkBoxPrintSbasout->isChecked() == true && ui->checkBoxPrintSbasvar->isChecked() == true && ui->checkBoxPrintSbascor->isChecked() == true
                    && ui->checkBoxPrintSbasiono->isChecked() == true && ui->checkBoxPrintSbasunsel->isChecked() == true && ui->checkBoxPrintSbasunused->isChecked() == true) {
                printAll=1;
            }
        } else if (ui->groupBoxReferenceStation->isChecked()==true || ui->labelCurrentTemplate->text() == "DGNSS") {
            if ( ui->checkBoxPrintDgnss->isChecked() == true && ui->checkBoxPrintDgnssunused->isChecked() == true ) {
                printAll=1;
            }
        } else {
            printAll=1;
        }
    } else if (ui->checkBoxPrintInfo->isChecked() == false && ui->checkBoxPrintCS->isChecked() == false && ui->checkBoxPrintInput->isChecked() == false && ui->checkBoxPrintMeas->isChecked() == false
               && ui->checkBoxPrintModel->isChecked() == false && ui->checkBoxPrintEpochsat->isChecked() == false && ui->checkBoxPrintPrefit->isChecked() == false
               &&  ui->checkBoxPrintPostfit->isChecked() == false && ui->checkBoxPrintSatsel->isChecked() == false && ui->checkBoxPrintFilter->isChecked() == false
               && ui->checkBoxPrintOutput->isChecked() == false && ui->checkBoxPrintUsererror->isChecked() == false && ui->checkBoxPrintSummary->isChecked() == false ) {
       if ( ui->groupBoxSbas->isChecked()==true || ui->labelCurrentTemplate->text() == "SBAS" ) {
           if (ui->checkBoxPrintSbasout->isChecked() == false && ui->checkBoxPrintSbasvar->isChecked() == false && ui->checkBoxPrintSbascor->isChecked() == false
                   && ui->checkBoxPrintSbasiono->isChecked() == false && ui->checkBoxPrintSbasunsel->isChecked() == false && ui->checkBoxPrintSbasunused->isChecked() == false) {
               printNone=1;
           }
       } else if (ui->groupBoxReferenceStation->isChecked()==true || ui->labelCurrentTemplate->text() == "DGNSS") {
           if ( ui->checkBoxPrintDgnss->isChecked() == false && ui->checkBoxPrintDgnssunused->isChecked() == false ) {
               printNone=1;
           }
       } else {
           printNone=1;
       }
    }
    if (printAll==1  && WriteAllParameters==0) {
        *saveString += "-print:all\n";
        *runString << "-print:all";
    } else if (printNone==1 && WriteAllParameters==0) {
        *saveString += "-print:none\n";
        *runString << "-print:none";
    } else {
        // INFO
        if ( ui->checkBoxPrintInfo->isChecked() == true ) {
            //Enabled in all modes by default. No need to set the option
            if (WriteAllParameters==1) {
                *saveString += "-print:info\n";
                *runString << "-print:info";
            }
        } else {
            *saveString += "--print:info\n";
            *runString << "--print:info";
        }
        // CS
        if ( ui->checkBoxPrintCS->isChecked() == true ) {
            //Enabled in all modes by default. No need to set the option
             if (WriteAllParameters==1) {
                *saveString += "-print:cycleslips\n";
                *runString << "-print:cycleslips";
             }
        } else {
            *saveString += "--print:cycleslips\n";
            *runString << "--print:cycleslips";
        }
        // INPUT
        if ( ui->checkBoxPrintInput->isChecked() == true ) {
            //Enabled in SPP, PPP and DGNSS, but not in SBAS
            if (ui->groupBoxSbas->isChecked()==true||WriteAllParameters==1) {
                *saveString += "-print:input\n";
                *runString << "-print:input";
            }
        } else {
            if (ui->groupBoxSbas->isChecked()==false || WriteAllParameters==1) {
                *saveString += "--print:input\n";
                *runString << "--print:input";
            }
        }
        // MEAS
        if ( ui->checkBoxPrintMeas->isChecked() == true ) {
            //Disabled in all modes by default
            *saveString += "-print:meas\n";
            *runString << "-print:meas";
        } else {
            //Disabled in all modes by default. No need to unset the option
            if (WriteAllParameters==1) {
                *saveString += "--print:meas\n";
                *runString << "--print:meas";
            }
        }
        // MODEL
        if ( ui->checkBoxPrintModel->isChecked() == true ) {
            //Enabled in SPP, PPP and DGNSS, but not in SBAS
            if (ui->groupBoxSbas->isChecked()==true  || WriteAllParameters==1) {
                *saveString += "-print:model\n";
                *runString << "-print:model";
            }
        } else {
            if (ui->groupBoxSbas->isChecked()==false  || WriteAllParameters==1) {
                *saveString += "--print:model\n";
                *runString << "--print:model";
            }
        }
        // EPOCHSAT
        if ( ui->checkBoxPrintEpochsat->isChecked() == true ) {
            //Enabled in SPP, PPP and DGNSS, but not in SBAS
            if (ui->groupBoxSbas->isChecked()==true  || WriteAllParameters==1) {
                *saveString += "-print:satellites\n";
                *runString << "-print:satellites";
            }
        } else {
            if (ui->groupBoxSbas->isChecked()==false  || WriteAllParameters==1) {
                *saveString += "--print:satellites\n";
                *runString << "--print:satellites";
            }
        }
        // PREFIT
        if ( ui->checkBoxPrintPrefit->isChecked() == true ) {
            //Enabled in SPP, PPP and DGNSS, but not in SBAS
            if (ui->groupBoxSbas->isChecked()==true  || WriteAllParameters==1) {
                *saveString += "-print:prefit\n";
                *runString << "-print:prefit";
            }
        } else {
            if (ui->groupBoxSbas->isChecked()==false  || WriteAllParameters==1) {
                *saveString += "--print:prefit\n";
                *runString << "--print:prefit";
            }
        }
        // POSTFIT
        if ( ui->checkBoxPrintPostfit->isChecked() == true ) {
            //Enabled in SPP, PPP and DGNSS, but not in SBAS
            if (ui->groupBoxSbas->isChecked()==true  || WriteAllParameters==1) {
                *saveString += "-print:postfit\n";
                *runString << "-print:postfit";
            }
        } else {
            if (ui->groupBoxSbas->isChecked()==false  || WriteAllParameters==1) {
                *saveString += "--print:postfit\n";
                *runString << "--print:postfit";
            }
        }
        // SATSEL
        if ( ui->checkBoxPrintSatsel->isChecked() == true ) {
            //Enabled in SBAS, but not in SPP, PPP and DGNSS
            if (ui->groupBoxSbas->isChecked()==false  || WriteAllParameters==1) {
                *saveString += "-print:satsel\n";
                *runString << "-print:satsel";
            }
        } else {
            if (ui->groupBoxSbas->isChecked()==true  || WriteAllParameters==1) {
                *saveString += "--print:satsel\n";
                *runString << "--print:satsel";
            }
        }
        // FILTER
        if ( ui->checkBoxPrintFilter->isChecked() == true ) {
            //Enabled in SPP, PPP and DGNSS, but not in SBAS
            if (ui->groupBoxSbas->isChecked()==true  || WriteAllParameters==1) {
                *saveString += "-print:filter\n";
                *runString << "-print:filter";
            }
        } else {
            if (ui->groupBoxSbas->isChecked()==false  || WriteAllParameters==1) {
                *saveString += "--print:filter\n";
                *runString << "--print:filter";
            }
        }
        // OUTPUT
        if ( ui->checkBoxPrintOutput->isChecked() == true ) {
            //Enabled in all modes by default. No need to set the option
             if (WriteAllParameters==1) {
                *saveString += "-print:output\n";
                *runString << "-print:output";
             }
        } else {
            *saveString += "--print:output\n";
            *runString << "--print:output";
        }
        // USERERROR
        if ( ui->checkBoxPrintUsererror->isChecked() == true ) {
            //Enabled in all modes by default. No need to set the option
             if (WriteAllParameters==1) {
                *saveString += "-print:usererror\n";
                *runString << "-print:usererror";
             }
        } else {
            *saveString += "--print:usererror\n";
            *runString << "--print:usererror";
        }
        // SBAS Messages
        if ( ui->labelCurrentTemplate->text() == "SBAS" || ui->groupBoxSbas->isChecked()==true  ) {
            // SBASOUT
            if ( ui->checkBoxPrintSbasout->isChecked() == true ) {
                 if (WriteAllParameters==1) {
                    *saveString += "-print:sbasout\n";
                    *runString << "-print:sbasout";
                 }
            } else if ( ui->checkBoxPrintSbasout->isChecked() == false  ) {
                //Enabled by default in SBAS
                *saveString += "--print:sbasout\n";
                *runString << "--print:sbasout";
            }
            // SBASVAR
            if ( ui->checkBoxPrintSbasvar->isChecked() == true ) {
                //Disabled by default in SBAS
                *saveString += "-print:sbasvar\n";
                *runString << "-print:sbasvar";
            } else if ( ui->checkBoxPrintSbasvar->isChecked() == false ) {
                if (WriteAllParameters==1) {
                    *saveString += "--print:sbasvar\n";
                    *runString << "--print:sbasvar";
                }
            }
            // SBASCOR
            if ( ui->checkBoxPrintSbascor->isChecked() == true ) {
                //Disabled by default in SBAS
                *saveString += "-print:sbascor\n";
                *runString << "-print:sbascor";
            } else if ( ui->checkBoxPrintSbascor->isChecked() == false ) {
                 if (WriteAllParameters==1) {
                    *saveString += "--print:sbascor\n";
                    *runString << "--print:sbascor";
                 }
            }
            // SBASIONO
            if ( ui->checkBoxPrintSbasiono->isChecked() == true ) {
                //Disabled by default in SBAS
                *saveString += "-print:sbasiono\n";
                *runString << "-print:sbasiono";
            } else if ( ui->checkBoxPrintSbasiono->isChecked() == false ) {
                if (WriteAllParameters==1) {
                    *saveString += "--print:sbasiono\n";
                    *runString << "--print:sbasiono";
                }
            }
            // SBASUNSEL
            if ( ui->checkBoxPrintSbasunsel->isChecked() == true ) {
                //Disabled by default in SBAS
                *saveString += "-print:sbasunsel\n";
                *runString << "-print:sbasunsel";
            } else if ( ui->checkBoxPrintSbasunsel->isChecked() == false ) {
                 if (WriteAllParameters==1) {
                    *saveString += "--print:sbasunsel\n";
                    *runString << "--print:sbasunsel";
                 }
            }
            // SBASUNUSED
            if ( ui->checkBoxPrintSbasunused->isChecked() == true ) {
                //Disabled by default in SBAS
                *saveString += "-print:sbasunused\n";
                *runString << "-print:sbasunused";
            } else if ( ui->checkBoxPrintSbasunused->isChecked() == false ) {
                //Disabled by default in SBAS
                 if (WriteAllParameters==1) {
                    *saveString += "--print:sbasunused\n";
                    *runString << "--print:sbasunused";
                 }
            }
        }
        // DGNSS Messages
        if ( ui->labelCurrentTemplate->text() == "DGNSS" || ui->groupBoxReferenceStation->isChecked()==true ) {
            // DGNSS
            if ( ui->checkBoxPrintDgnss->isChecked() == true ) {
                //Enabled by default in DGNSS
                if (WriteAllParameters==1) {
                    *saveString += "-print:dgnss\n";
                    *runString << "-print:dgnss";
                }
            } else if ( ui->checkBoxPrintDgnss->isChecked() == false ) {
                //Enabled by default in DGNSS
                *saveString += "--print:dgnss\n";
                *runString << "--print:dgnss";
            }
            // DGNSSUNUSED
            if ( ui->checkBoxPrintDgnssunused->isChecked() == true ) {
                //Disabled by default in DGNSS
                *saveString += "-print:dgnssunused\n";
                *runString << "-print:dgnssunused";
            } else if ( ui->checkBoxPrintDgnssunused->isChecked() == false ) {
                //Disabled by default in DGNSS
                if (WriteAllParameters==1) {
                    *saveString += "--print:dgnssunused\n";
                    *runString << "--print:dgnssunused";
                }
            }
        }

        //Summary
        if (ui->checkBoxPrintSummary->isChecked() == true) {
            //Enabled by default in all modes
            if (WriteAllParameters==1) {
                *saveString += "-print:summary\n";
                *runString << "-print:summary";
            }
        } else {
            *saveString += "--print:summary\n";
            *runString << "--print:summary";
        }
    }

    //Summary options
    if (ui->checkBoxPrintSummary->isChecked() == true) {
        if (SBASmaritime==0) {
            if (ui->groupBoxSbas->isChecked()==true) {
                if (ui->lineEditHorizontalAlarmLimitSBAS->text() == "") {
                    *errorString += "OUTPUT: Horizontal Alarm Limit in [Summary Options] cannot be empty.\n";
                } else if (ui->lineEditHorizontalAlarmLimitSBAS->text().toInt()==0) {
                    *errorString += "OUTPUT: Horizontal Alarm Limit in [Summary Options] cannot be 0.\n";
                } else if (ui->lineEditHorizontalAlarmLimitSBAS->text().toInt()!=40 || WriteAllParameters==1) {
                    *saveString += "-summary:hal " + ui->lineEditHorizontalAlarmLimitSBAS->text() + "\n";
                    *runString << "-summary:hal" << ui->lineEditHorizontalAlarmLimitSBAS->text();
                }
                if (ui->lineEditVerticalAlarmLimitSBAS->text() == "") {
                    *errorString += "OUTPUT: Vertical Alarm Limit in [Summary Options] cannot be empty.\n";
                } else if (ui->lineEditVerticalAlarmLimitSBAS->text().toInt() == 0) {
                    *errorString += "OUTPUT: Horizontal Alarm Limit in [Summary Options] cannot be 0.\n";
                } else if (ui->lineEditVerticalAlarmLimitSBAS->text().toInt()!=50 || WriteAllParameters==1) {
                    *saveString += "-summary:val " + ui->lineEditVerticalAlarmLimitSBAS->text() + "\n";
                    *runString << "-summary:val" << ui->lineEditVerticalAlarmLimitSBAS->text();
                }
            }
        }

        if (ui->lineEditPercentileValue->isHidden()==false) {
            if (ui->lineEditPercentileValue->text() == "") {
                *errorString += "OUTPUT: Percentile value in [Summary Options] cannot be empty.\n";
            } else if (ui->lineEditPercentileValue->text().toInt() == 0) {
                *errorString += "OUTPUT: Percentile value in [Summary Options] cannot be 0.\n";
            } else if (ui->lineEditPercentileValue->text().toInt()!=95 || WriteAllParameters==1) {
                *saveString += "-summary:percentile " + ui->lineEditPercentileValue->text() + "\n";
                *runString << "-summary:percentile" << ui->lineEditPercentileValue->text();
            }
        }

        if (SBASmaritime==0) {
            if (ui->groupBoxSbas->isChecked()==true) {
                if (ui->lineEditSlidingWindowSBAS->text() == "") {
                    *errorString += "OUTPUT: Sliding Window in [Summary Options] cannot be empty.\n";
                } else if (ui->lineEditSlidingWindowSBAS->text().toInt() == 0) {
                    *errorString += "OUTPUT: Sliding Window in [Summary Options] cannot be 0.\n";
                } else if (ui->lineEditSlidingWindowSBAS->text().toInt()!=15 || WriteAllParameters==1) {
                    *saveString += "-summary:windowsize " + ui->lineEditSlidingWindowSBAS->text() + "\n";
                    *runString << "-summary:windowsize" << ui->lineEditSlidingWindowSBAS->text();
                }

                if (ui->lineEditMaritimeWindowSBAS->text() == "") {
                    *errorString += "OUTPUT: Fixed Window in [Summary Options] cannot be empty.\n";
                } else if (ui->lineEditMaritimeWindowSBAS->text().toInt() == 0) {
                    *errorString += "OUTPUT: Fixed Window in [Summary Options] cannot be 0.\n";
                } else if (ui->lineEditMaritimeWindowSBAS->text().toInt()!=15 || WriteAllParameters==1) {
                    *saveString += "-summary:windowsizemar " + ui->lineEditMaritimeWindowSBAS->text() + "\n";
                    *runString << "-summary:windowsizemar" << ui->lineEditMaritimeWindowSBAS->text();
                }
            }
        }

        if (ui->checkBoxWaitforDayStart->isChecked()==true) {
            //This is the default
            if (WriteAllParameters==1) {
                *saveString += "-summary:waitfordaystart\n";
                *runString << "-summary:waitfordaystart";
            }
        } else if (ui->checkBoxWaitforDayStart->isChecked()==false) {
            if (ui->checkBoxStartTimeSummary->isChecked()==true) {
                if (WriteAllParameters==1) {
                    //If start time is set, waitfordaystart is ignored
                    *saveString += "--summary:waitfordaystart\n";
                    *runString << "--summary:waitfordaystart";
                }

                date = ui->dateTimeEditStartTimeSummary->date();
                time = ui->dateTimeEditStartTimeSummary->time();
                if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && time.hour() == 0 && time.minute()==0 && time.second()==0) {
                    *errorString += "OUTPUT: Date (DD/MM/YYYY) and GPS Time (HH:MM:SS) are a required input if 'Set start time of summary' is set [In Summary Options].\n";
                } else {
                    if (ui->checkBoxEndTime->isChecked()==true) {
                        if (ui->dateTimeEditStartTimeSummary->date().operator >(ui->dateTimeEditEndTime->date()) ) {
                            *errorString += "OUTPUT: 'Summary start time' must be smaller than the 'End Time' (in the INPUT section) if both are set [In Summary options].\n";
                        } else if (ui->dateTimeEditStartTimeSummary->date().operator ==(ui->dateTimeEditEndTime->date()) ) {
                            if (ui->dateTimeEditStartTimeSummary->time().operator >(ui->dateTimeEditEndTime->time()) ) {
                                *errorString += "OUTPUT: 'Summary start time' must be smaller than the 'End Time' (in the INPUT section) if both are set [In Summary options].\n";
                            }
                        }
                    }
                    *saveString += "-summary:starttime " + date.toString("yyyy/MM/dd") + " " + time.toString("HH:mm:ss") + "\n";
                    *runString << "-summary:starttime" << date.toString("yyyy/MM/dd") << time.toString("HH:mm:ss");
                }
            } else {
                *saveString += "--summary:waitfordaystart\n";
                *runString << "--summary:waitfordaystart";
            }
        }
    }

    // Footer of the file
    *saveString += "\n";
    *saveString += "###################################################\n";
    *saveString += "#     End of self-generated parameters\n";
    *saveString += "###################################################\n";
}
