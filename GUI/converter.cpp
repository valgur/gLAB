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


// Function to hide or show the SBAS converter
void gLAB_GUI::on_groupBoxConverterSBAS_clicked(bool checked) {
    ui->groupBoxConverterSBAS->setChecked(checked);
    ui->frameConverterSBAS->setHidden(!checked);
    // Disable DGNSS
    if ( checked == true ) {
        ui->groupBoxConverterDgnss->setChecked(!checked);
        ui->frameConverterDgnss->setHidden(checked);
    }
}

// Function to hide or show the DGNSS converter
void gLAB_GUI::on_groupBoxConverterDgnss_clicked(bool checked) {
    ui->groupBoxConverterDgnss->setChecked(checked);
    ui->frameConverterDgnss->setHidden(!checked);
    // Disable SBAS
    if ( checked == true ) {
        ui->groupBoxConverterSBAS->setChecked(!checked);
        ui->frameConverterSBAS->setHidden(checked);
    }
}

//Function to show or hide Pegasus converting options
void gLAB_GUI::on_checkBox_pegasus_clicked(bool checked) {
	ui->Pegasus_frame->setHidden(!checked);
    if(checked) {
        ui->frame_holdingPegasusOptions->setFrameShape(QFrame::Box);
    } else {
        ui->frame_holdingPegasusOptions->setFrameShape(QFrame::NoFrame);
    }
}


////////////////////// Push buttons /////////////////////
void gLAB_GUI::on_pushButton_convert_sbas_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("SBAS Files (*.??b *.ems);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEdit_convert_sbas->setText(QDir::toNativeSeparators(fileName[0]));
			//Set output path for SBAS
            ui->lineEdit_outputpath_sbas->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/SBAS"));

        }
    }
}

void gLAB_GUI::on_pushButton_output_path_sbas_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEdit_outputpath_sbas->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonConverterDgnssInput_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("RTCM Files (*.??rtcm *.??rtcm2 *.??rtcm3 *.rtcm *.rtcm2 *.rtcm3 *.rcm);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditConverterDgnssInput->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonConverterDgnssOutputRinex_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("RINEX Files (*.??o);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditConverterDgnssOutputRinex->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonConverterDgnssOutputAsciiCorrections_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("ASCII Files (*.asc);;All Files (*.*)"));
    dialog.selectFile("_corrections.asc");
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditConverterDgnssOutputAsciiCorrections->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonConverterDgnssOutputAsciiAntenna_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("ASCII Files (*.asc);;All Files (*.*)"));
    dialog.selectFile("_antenna.asc");
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditConverterDgnssOutputAsciiAntenna->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}
/////////////////////////////////////////////////////////

///////////////// Start of Context menus (right-click menus) //////////////////
void gLAB_GUI::labelConvSbasFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelConvSbasFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open SBAS File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEdit_convert_sbas->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEdit_convert_sbas->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEdit_convert_sbas->text();
        #endif

        // Execute the program
        if (ui->lineEdit_convert_sbas->text() == "") {
            messageBox.warning(0, "Error","SBAS file is empty\n");
        } else if (this->fileExists(ui->lineEdit_convert_sbas->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEdit_convert_sbas->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEdit_convert_sbas->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelConvOutputPathMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelConvOutputPath->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open SBAS Output Folder");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        if (ui->lineEdit_outputpath_sbas->text()== "") {
            messageBox.warning(0, "Error","SBAS Output folder is empty\n");
        } else {
            if (this->directoryExists( ui->lineEdit_outputpath_sbas->text() ) == true ) {
                QDesktopServices::openUrl(QUrl::fromLocalFile(ui->lineEdit_outputpath_sbas->text()));
            }
        }
    }
}

void gLAB_GUI::comboBoxConverterDgnssInputMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->comboBoxConverterDgnssInput->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open RTCM Input File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QMessageBox messageBox;
        QMessageBox::StandardButton reply;

        //File is a binary file
        reply = QMessageBox::warning(this, "Binary file",
                       QString("RTCM files are binary files. Opening a binary file with a text editor will probably corrupt it.\nAre you sure you want to continue?\n"),
                       QMessageBox::Yes|QMessageBox::No);
        if ( reply == QMessageBox::No ) {
            return;
        }

        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditConverterDgnssInput->text();
        #elif defined(Q_OS_WIN32)
            //Binary files may be better opened in notepad rather than wordpad
            program = QString("notepad");
            arguments << ui->lineEditConverterDgnssInput->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditConverterDgnssInput->text();
        #endif

        // Execute the program
        if (ui->lineEditConverterDgnssInput->text() == "") {
            messageBox.warning(0, "Error","RTCM file is empty\n");
        } else if (this->fileExists(ui->lineEditConverterDgnssInput->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditConverterDgnssInput->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditConverterDgnssInput->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::comboBoxConverterDgnssOutputRinexMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->comboBoxConverterDgnssOutputRinex->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open Output RINEX File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditConverterDgnssOutputRinex->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditConverterDgnssOutputRinex->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditConverterDgnssOutputRinex->text();
        #endif

        // Execute the program
        if (ui->lineEditConverterDgnssOutputRinex->text() == "") {
            messageBox.warning(0, "Error","Output RINEX file is empty\n");
        } else if (this->fileExists(ui->lineEditConverterDgnssOutputRinex->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditConverterDgnssOutputRinex->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditConverterDgnssOutputRinex->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelConvCorrectionsFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelConvCorrectionsFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open Output Corrections Text File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditConverterDgnssOutputAsciiCorrections->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditConverterDgnssOutputAsciiCorrections->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditConverterDgnssOutputAsciiCorrections->text();
        #endif

        // Execute the program
        if (ui->lineEditConverterDgnssOutputAsciiCorrections->text() == "") {
            messageBox.warning(0, "Error","Output Corrections Text file is empty\n");
        } else if (this->fileExists(ui->lineEditConverterDgnssOutputAsciiCorrections->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditConverterDgnssOutputAsciiCorrections->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditConverterDgnssOutputAsciiCorrections->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelConvAntennaFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelConvAntennaFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open Output Antenna Text File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditConverterDgnssOutputAsciiAntenna->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditConverterDgnssOutputAsciiAntenna->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditConverterDgnssOutputAsciiAntenna->text();
        #endif

        // Execute the program
        if (ui->lineEditConverterDgnssOutputAsciiAntenna->text() == "") {
            messageBox.warning(0, "Error","Output Antenna Text file is empty\n");
        } else if (this->fileExists(ui->lineEditConverterDgnssOutputAsciiAntenna->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditConverterDgnssOutputAsciiAntenna->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditConverterDgnssOutputAsciiAntenna->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}
///////////////// End of Context menus (right-click menus) //////////////////

// Function to fill converter output(s) filename(s)
void gLAB_GUI::on_lineEditConverterDgnssInput_textChanged() {
    int i;
    QDate date;
    QString input = ui->lineEditConverterDgnssInput->text();
    QStringList outputList;
    QString output;
    char separator;

    #ifdef Q_OS_WIN32
        separator = '\\';
    #else
        separator = '/';
    #endif
    outputList = input.split(separator);

    if ( outputList.last() == "" ) {
        ui->lineEditConverterDgnssOutputRinex->setText("");
        ui->lineEditConverterDgnssOutputAsciiCorrections->setText("");
        ui->lineEditConverterDgnssOutputAsciiAntenna->setText("");
    } else {
        // Common
        output = outputList.last().mid(0, 4);
        while ( output.length() < 4 ) output += "0";
        date = ui->dateEdit4->date();
        QString doy = QString::number(date.dayOfYear()).rightJustified(3,'0');
        output = output + doy + "0." + date.toString("yy");
        // RINEX
        QString outputRinex;
        if ( outputList.length() > 1 ) {
            i = 0;
            while ( i < (outputList.length()-1) ) {
                outputRinex += outputList[i] + separator;
                i++;
            }
        }
        outputRinex += output + "o";
        ui->lineEditConverterDgnssOutputRinex->setText(outputRinex);
        // RTCM Corrections
        QString outputRtcmCorrections;
        if ( outputList.length() > 1 ) {
            i = 0;
            while ( i < (outputList.length()-1) ) {
                outputRtcmCorrections += outputList[i] + separator;
                i++;
            }
        }
        outputRtcmCorrections += output + "_corrections.asc";
        ui->lineEditConverterDgnssOutputAsciiCorrections->setText(outputRtcmCorrections);
        // RTCM Antenna
        QString outputRtcmAntenna;
        if ( outputList.length() > 1 ) {
            i = 0;
            while ( i < (outputList.length()-1) ) {
                outputRtcmAntenna += outputList[i] + separator;
                i++;
            }
        }
        outputRtcmAntenna += output + "_antenna.asc";
        ui->lineEditConverterDgnssOutputAsciiAntenna->setText(outputRtcmAntenna);
    }
}

// Function to update the date in the converter output(s) filename(s)
void gLAB_GUI::on_dateEdit4_dateChanged() {
    int i;
    QDate date;
    QString input = ui->lineEditConverterDgnssInput->text();
    QStringList outputList;
    QString output;
    char separator;

    #ifdef Q_OS_WIN32
        separator = '\\';
    #else
        separator = '/';
    #endif
    outputList = input.split(separator);

    if ( outputList.last() == "" ) {
        ui->lineEditConverterDgnssOutputRinex->setText("");
        ui->lineEditConverterDgnssOutputAsciiCorrections->setText("");
        ui->lineEditConverterDgnssOutputAsciiAntenna->setText("");
    } else {
        // Common
        output = outputList.last().mid(0, 4);
        while ( output.length() < 4 ) output += "0";
        date = ui->dateEdit4->date();
        QString doy = QString::number(date.dayOfYear()).rightJustified(3,'0');
        output = output + doy + "0." + date.toString("yy");
        // RINEX
        QString outputRinex;
        if ( outputList.length() > 1 ) {
            i = 0;
            while ( i < (outputList.length()-1) ) {
                outputRinex += outputList[i] + separator;
                i++;
            }
        }
        outputRinex += output + "o";
        ui->lineEditConverterDgnssOutputRinex->setText(outputRinex);
        // RTCM Corrections
        QString outputRtcmCorrections;
        if ( outputList.length() > 1 ) {
            i = 0;
            while ( i < (outputList.length()-1) ) {
                outputRtcmCorrections += outputList[i] + separator;
                i++;
            }
        }
        outputRtcmCorrections += output + "_corrections.asc";
        ui->lineEditConverterDgnssOutputAsciiCorrections->setText(outputRtcmCorrections);
        // RTCM Antenna
        QString outputRtcmAntenna;
        if ( outputList.length() > 1 ) {
            i = 0;
            while ( i < (outputList.length()-1) ) {
                outputRtcmAntenna += outputList[i] + separator;
                i++;
            }
        }
        outputRtcmAntenna += output + "_antenna.asc";
        ui->lineEditConverterDgnssOutputAsciiAntenna->setText(outputRtcmAntenna);
    }
}

// Function to hide or show some DGNSS components with regard to the input
void gLAB_GUI::on_comboBoxConverterDgnssInput_currentIndexChanged(int index) {
    switch ( index ) {
        case 0 : { // RTCM Auto
            ui->labelTimeEdit3->setHidden(false);
            ui->timeEdit3->setHidden(false);
            ui->frameConverterDgnssOutputRinex->setHidden(false);
            ui->frameConverterDgnssOutputAscii->setHidden(false);
            break;
        }
        case 1 : { // RTCM v2.x
            ui->labelTimeEdit3->setHidden(false);
            ui->timeEdit3->setHidden(false);
            ui->frameConverterDgnssOutputRinex->setHidden(true);
            ui->frameConverterDgnssOutputAscii->setHidden(false);
            break;
        }
        case 2 : { // RTCM v3.x
            ui->labelTimeEdit3->setHidden(true);
            ui->timeEdit3->setHidden(true);
            ui->frameConverterDgnssOutputRinex->setHidden(false);
            ui->frameConverterDgnssOutputAscii->setHidden(true);
            break;
        }
    }
}

int gLAB_GUI::getConverterOptions(int ShowCommandline, QString *errorString, QString *warningString, QString *saveString, QStringList *runString) {

    QDate date;
    QTime hour;
   // QMessageBox::StandardButton reply;
  //  QFile fileLock;
    ShowCommandline+=0;//This is to avoid no use warning while output file exist check is commented

    *errorString = "";
    *warningString="";
    *saveString = "";

    if (ui->groupBoxConverterSBAS->isChecked()==true) {
        //SBAS converter
        // Get the erros and arguments for the input
        if ( ui->lineEdit_convert_sbas->text() == "" ) {
            *errorString += "SBAS source file is not selected.\n";
        } else {
            // Source File
             if ( this->fileExists( ui->lineEdit_convert_sbas->text()  ) == false ) {
                 *errorString += "SBAS source file does not exist.\n";
             } else if (this->checknonASCIIcharacters(ui->lineEdit_convert_sbas->text())==1) {
                 *errorString += "SBAS source file has non ASCII characters\n";
             } else {
                 *saveString += "-input:sbas " + ui->lineEdit_convert_sbas->text() +"\n";
                 *runString << "-input:sbas" << ui->lineEdit_convert_sbas->text();
             }
        }

        if ( ui->lineEdit_outputpath_sbas->text() == "" ) {
            *errorString += "SBAS Output directory is not selected.\n";
        //} else if ( this->directoryExists( ui->lineEdit_outputpath_sbas->text()  ) == false ) {
        //    *errorString += "SBAS Output directory does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEdit_outputpath_sbas->text())==1) {
            *errorString += "SBAS Output directory has non ASCII characters\n";
        } else {
            *saveString += "-output:sbasdir " + ui->lineEdit_outputpath_sbas->text() +"\n";
            *runString << "-output:sbasdir" << ui->lineEdit_outputpath_sbas->text();
        }

        if ( ui->checkBox_rinexb->isChecked()==false && ui->checkBox_ems->isChecked()==false && ui->checkBox_pegasus->isChecked()==false ) {
             *errorString += "No SBAS output files selected\n";
        } else {
            if ( ui->checkBox_rinexb->isChecked()==true) {
                *saveString += "-output:rinexb\n";
                *runString << "-output:rinexb";
            }
            if ( ui->checkBox_ems->isChecked()==true) {
                *saveString += "-output:ems\n";
                *runString << "-output:ems";
            }
            if (ui->checkBox_pegasus->isChecked()==true) {
                *saveString += "-output:pegasus\n";
                *runString << "-output:pegasus";
                if (ui->checkBox_pegasus_space->isChecked()==true) {
                    *saveString += "-output:pegspace\n";
                     *runString << "-output:pegspace";
                }
                if (ui->checkBox_pegasus_align->isChecked()==true) {
                    *saveString += "-output:pegfilealign\n";
                    *runString << "-output:pegfilealign";
                }
            }
        }
        *saveString += "-onlyconvert\n";
        *runString << "-onlyconvert";
    } else if ( ui->groupBoxConverterDgnss->isChecked()==true) {
        //// RTCM Converter
        // Get the erros and arguments for the input
        if ( ui->lineEditConverterDgnssInput->text() == "" ) {
            *errorString += "DGNSS source file is not selected.\n";
        } else {
            // Source File
            if ( this->fileExists( ui->lineEditConverterDgnssInput->text() ) == false ) {
                *errorString += "DGNSS source file does not exist.\n";
            } else if (this->checknonASCIIcharacters(ui->lineEditConverterDgnssInput->text())==1) {
                *errorString += "DGNSS source file has non ASCII characters\n";
            } else {
                switch ( ui->comboBoxConverterDgnssInput->currentIndex() ) {
                    case 0 : { // RTCM Auto
                        *saveString += "-input:rtcm " + ui->lineEditConverterDgnssInput->text() +"\n";
                        *runString << "-input:rtcm" << ui->lineEditConverterDgnssInput->text();
                        break;
                    }
                    case 1 : { // RTCM v2.x
                        *saveString += "-input:rtcm2 " + ui->lineEditConverterDgnssInput->text() +"\n";
                        *runString << "-input:rtcm2" << ui->lineEditConverterDgnssInput->text();
                        break;
                    }
                    case 2 : { // RTCM v3.x
                        *saveString += "-input:rtcm3 " + ui->lineEditConverterDgnssInput->text() +"\n";
                        *runString << "-input:rtcm3" << ui->lineEditConverterDgnssInput->text();
                        break;
                    }
                }
            }
        }
        date = ui->dateEdit4->date();
        hour = ui->timeEdit3->time();
        switch ( ui->comboBoxConverterDgnssInput->currentIndex() ) {
            case 0 : { // RTCM Auto
                if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 )
                    *errorString += "Date (DD/MM/YYYY) and GPS Time (HH) are a required input if 'RTCM Auto is specified.\n";
                else {
                    *saveString += "-input:rtcm:initdate " + date.toString("yyyyMMdd") +"\n";
                    *saveString += "-input:rtcm:inithour " + hour.toString("HH") +"\n";
                    *runString << "-input:rtcm:initdate" << date.toString("yyyyMMdd");
                    *runString << "-input:rtcm:inithour" << hour.toString("HH");
                }
                break;
            }
            case 1 : { // RTCM v2.x
                if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 )
                    *errorString += "Date (DD/MM/YYYY) and GPS Time (HH) are a required input if 'RTCM v2.x is specified.\n";
                else {
                    *saveString += "-input:rtcm:initdate " + date.toString("yyyyMMdd") +"\n";
                    *saveString += "-input:rtcm:inithour " + hour.toString("HH") +"\n";
                    *runString << "-input:rtcm:initdate" << date.toString("yyyyMMdd");
                    *runString << "-input:rtcm:inithour" << hour.toString("HH");
                }
                break;
            }
            case 2 : { // RTCM v3.x
                if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 )
                    *errorString += "Date (DD/MM/YYYY) and GPS Time (HH) are a required input if 'RTCM v3.x is specified.\n";
                else {
                    *saveString += "-input:rtcm:initdate " + date.toString("yyyyMMdd") +"\n";
                    *runString << "-input:rtcm:initdate" << date.toString("yyyyMMdd");
                }
                break;
            }
        }
        // Get the errors and arguments for the input
        switch ( ui->comboBoxConverterDgnssInput->currentIndex() ) {
            case 0 : { // RTCM Auto
                if ( ui->comboBoxConverterDgnssOutputRinex->currentIndex() == 0 ) { // RINEX v2.11
                    if ( ui->lineEditConverterDgnssOutputRinex->text() == "" ) {
                        *errorString += "RINEX v2.11 file is not set.\n";
                    } else if (this->checknonASCIIcharacters(ui->lineEditConverterDgnssOutputRinex->text())==1) {
                        *errorString += "RINEX v2.11 file has non ASCII characters\n";
                    } else {
                       /* if ( this->fileExists( ui->lineEditConverterDgnssOutputRinex->text() ) == true && ShowCommandline==0 ) {
                            reply = QMessageBox::question(this, "File already exists",
                                                          QString("The file %1 already exists.\nAre you sure you want to continue?\n").arg(ui->lineEditConverterDgnssOutputRinex->text()),
                                                          QMessageBox::Yes|QMessageBox::No);
                            if ( reply == QMessageBox::Yes ) {
                                *saveString += "-output:rinex " + ui->lineEditConverterDgnssOutputRinex->text() +  "\n-output:rinexversion " + "2\n";
                                *runString << "-output:rinex" << ui->lineEditConverterDgnssOutputRinex->text() << "-output:rinexversion" << "2";
                                //Remove RINEX file
                                fileLock.remove(QDir::toNativeSeparators(ui->lineEditConverterDgnssOutputRinex->text()));
                            } else {
                                ui->pushButtonConvert->setEnabled(true);
                                ui->pushButtonConvertShowOutput->setEnabled(false);
                                return 1;
                            }
                        } else {*/
                            *saveString += "-output:rinex " + ui->lineEditConverterDgnssOutputRinex->text() + "\n-output:rinexversion " + "2\n";
                            *runString << "-output:rinex" << ui->lineEditConverterDgnssOutputRinex->text() << "-output:rinexversion" << "2";
                       // }
                    }
                } else if ( ui->comboBoxConverterDgnssOutputRinex->currentIndex() == 1 ) { // RINEX v3.00
                    if ( ui->lineEditConverterDgnssOutputRinex->text() == "" ) {
                        *errorString += "RINEX v3.00 file is not set.\n";
                    } else if (this->checknonASCIIcharacters(ui->lineEditConverterDgnssOutputRinex->text())==1) {
                        *errorString += "RINEX v3.00 file has non ASCII characters\n";
                    } else {
                       /* if ( this->fileExists( ui->lineEditConverterDgnssOutputRinex->text() ) == true && ShowCommandline==0 ) {
                            reply = QMessageBox::question(this, "File already exists",
                                                          QString("The file %1 already exists.\nAre you sure you want to continue?\n").arg(ui->lineEditConverterDgnssOutputRinex->text()),
                                                          QMessageBox::Yes|QMessageBox::No);
                            if ( reply == QMessageBox::Yes ) {
                                //Default output rinex version is 3
                                *saveString += "-output:rinex " + ui->lineEditConverterDgnssOutputRinex->text() +"\n";
                                *runString << "-output:rinex" << ui->lineEditConverterDgnssOutputRinex->text();
                                //Remove RINEX file
                                fileLock.remove(QDir::toNativeSeparators(ui->lineEditConverterDgnssOutputRinex->text()));
                            } else {
                                ui->pushButtonConvert->setEnabled(true);
                                ui->pushButtonConvertShowOutput->setEnabled(false);
                                return 1;
                            }
                        } else {*/
                             //Default output rinex version is 3
                            *saveString += "-output:rinex " + ui->lineEditConverterDgnssOutputRinex->text() +"\n";
                            *runString << "-output:rinex" << ui->lineEditConverterDgnssOutputRinex->text();
                        //}
                    }
                }
                if ( ui->lineEditConverterDgnssOutputAsciiCorrections->text() == "" ) {
                    *errorString += "Correction file is not set.\n";
                } else if (this->checknonASCIIcharacters(ui->lineEditConverterDgnssOutputAsciiCorrections->text())==1) {
                    *errorString += "Correction file has non ASCII characters\n";
                } else {
                  /*  if ( this->fileExists( ui->lineEditConverterDgnssOutputAsciiCorrections->text() ) == true && ShowCommandline==0 ) {
                        reply = QMessageBox::question(this, "File already exists",
                                                      QString("The file %1 already exists.\nAre you sure you want to continue?\n").arg(ui->lineEditConverterDgnssOutputAsciiCorrections->text()),
                                                      QMessageBox::Yes|QMessageBox::No);
                        if ( reply == QMessageBox::Yes ) {
                            *saveString += "-output:corrections " + ui->lineEditConverterDgnssOutputAsciiCorrections->text() + "\n";
                            *runString << "-output:corrections" << ui->lineEditConverterDgnssOutputAsciiCorrections->text();
                            //Remove corrections file
                            fileLock.remove(QDir::toNativeSeparators(ui->lineEditConverterDgnssOutputAsciiCorrections->text()));
                        } else {
                            ui->pushButtonConvert->setEnabled(true);
                            ui->pushButtonConvertShowOutput->setEnabled(false);
                            return 1;
                        }
                    } else {*/
                        *saveString += "-output:corrections " + ui->lineEditConverterDgnssOutputAsciiCorrections->text() + "\n";
                        *runString << "-output:corrections" << ui->lineEditConverterDgnssOutputAsciiCorrections->text();
                   // }
                }
                if ( ui->lineEditConverterDgnssOutputAsciiAntenna->text() == "" ) {
                    *errorString += "Antenna file is not set.\n";
                } else if (this->checknonASCIIcharacters(ui->lineEditConverterDgnssOutputAsciiAntenna->text())==1) {
                    *errorString += "Antenna file has non ASCII characters\n";
                } else {
                  /*  if ( this->fileExists( ui->lineEditConverterDgnssOutputAsciiAntenna->text() ) == true && ShowCommandline==0 ) {
                        reply = QMessageBox::question(this, "File already exists",
                                                      QString("The file %1 already exists.\nAre you sure you want to continue?\n").arg(ui->lineEditConverterDgnssOutputAsciiAntenna->text()),
                                                      QMessageBox::Yes|QMessageBox::No);
                        if ( reply == QMessageBox::Yes ) {
                            *saveString += "-output:antenna " + ui->lineEditConverterDgnssOutputAsciiAntenna->text() + "\n";
                            *runString << "-output:antenna" << ui->lineEditConverterDgnssOutputAsciiAntenna->text();
                            //Remove antenna file
                            fileLock.remove(QDir::toNativeSeparators(ui->lineEditConverterDgnssOutputAsciiAntenna->text()));
                        } else {
                            ui->pushButtonConvert->setEnabled(true);
                            ui->pushButtonConvertShowOutput->setEnabled(false);
                            return 1;
                        }
                    } else {*/
                        *saveString += "-output:antenna " + ui->lineEditConverterDgnssOutputAsciiAntenna->text() + "\n";
                        *runString << "-output:antenna" << ui->lineEditConverterDgnssOutputAsciiAntenna->text();
                    //}
                }
                break;
            }
            case 1 : { // RTCM v2.x
                if ( ui->lineEditConverterDgnssOutputAsciiCorrections->text() == "" ) {
                    *errorString += "Correction file is not set.\n";
                } else if (this->checknonASCIIcharacters(ui->lineEditConverterDgnssOutputAsciiCorrections->text())==1) {
                    *errorString += "Correction file has non ASCII characters\n";
                } else {
                 /*   if ( this->fileExists( ui->lineEditConverterDgnssOutputAsciiCorrections->text() ) == true && ShowCommandline==0 ) {
                        reply = QMessageBox::question(this, "File already exists",
                                                      QString("The file %1 already exists.\nAre you sure you want to continue?\n").arg(ui->lineEditConverterDgnssOutputAsciiCorrections->text()),
                                                      QMessageBox::Yes|QMessageBox::No);
                        if ( reply == QMessageBox::Yes ) {
                            *saveString += "-output:corrections " + ui->lineEditConverterDgnssOutputAsciiCorrections->text() + "\n";
                            *runString << "-output:corrections" << ui->lineEditConverterDgnssOutputAsciiCorrections->text();
                            //Remove corrections file
                            fileLock.remove(QDir::toNativeSeparators(ui->lineEditConverterDgnssOutputAsciiCorrections->text()));
                        } else {
                            ui->pushButtonConvert->setEnabled(true);
                            ui->pushButtonConvertShowOutput->setEnabled(false);
                            return 1;
                        }
                    } else {*/
                        *saveString += "-output:corrections " + ui->lineEditConverterDgnssOutputAsciiCorrections->text() + "\n";
                        *runString << "-output:corrections" << ui->lineEditConverterDgnssOutputAsciiCorrections->text();
                   // }
                }
                if ( ui->lineEditConverterDgnssOutputAsciiAntenna->text() == "" ) {
                    *errorString += "Antenna file is not set.\n";
                } else if (this->checknonASCIIcharacters(ui->lineEditConverterDgnssOutputAsciiAntenna->text())==1) {
                    *errorString += "Antenna file has non ASCII characters\n";
                } else {
                   /* if ( this->fileExists( ui->lineEditConverterDgnssOutputAsciiAntenna->text() ) == true && ShowCommandline==0 ) {
                        reply = QMessageBox::question(this, "File already exists",
                                                      QString("The file %1 already exists.\nAre you sure you want to continue?\n").arg(ui->lineEditConverterDgnssOutputAsciiAntenna->text()),
                                                      QMessageBox::Yes|QMessageBox::No);
                        if ( reply == QMessageBox::Yes ) {
                            *saveString += "-output:antenna " + ui->lineEditConverterDgnssOutputAsciiAntenna->text() + "\n";
                            *runString << "-output:antenna" << ui->lineEditConverterDgnssOutputAsciiAntenna->text();
                            //Remove antenna file
                            fileLock.remove(QDir::toNativeSeparators(ui->lineEditConverterDgnssOutputAsciiAntenna->text()));
                        } else {
                            ui->pushButtonConvert->setEnabled(true);
                            ui->pushButtonConvertShowOutput->setEnabled(false);
                            return 1;
                        }
                    } else {*/
                        *saveString += "-output:antenna " + ui->lineEditConverterDgnssOutputAsciiAntenna->text() + "\n";
                        *runString << "-output:antenna" << ui->lineEditConverterDgnssOutputAsciiAntenna->text();
                    //}
                }
                break;
            }
            case 2 : { // RTCM v3.x
                if ( ui->comboBoxConverterDgnssOutputRinex->currentIndex() == 0 ) { // RINEX v2.11
                    if ( ui->lineEditConverterDgnssOutputRinex->text() == "" ) {
                        *errorString += "RINEX v2.11 file is not set.\n";
                    } else if (this->checknonASCIIcharacters(ui->lineEditConverterDgnssOutputRinex->text())==1) {
                        *errorString += "RINEX v2.11 file has non ASCII characters\n";
                    } else {
                     /*   if ( this->fileExists( ui->lineEditConverterDgnssOutputRinex->text() ) == true && ShowCommandline==0 ) {
                            reply = QMessageBox::question(this, "File already exists",
                                                          QString("The file %1 already exists.\nAre you sure you want to continue?\n").arg(ui->lineEditConverterDgnssOutputRinex->text()),
                                                          QMessageBox::Yes|QMessageBox::No);
                            if ( reply == QMessageBox::Yes ) {
                                *saveString += "-output:rinex " + ui->lineEditConverterDgnssOutputRinex->text() + "\n-output:rinexversion " + "2\n";
                                *runString << "-output:rinex" << ui->lineEditConverterDgnssOutputRinex->text() << "-output:rinexversion" << "2";
                                //Remove RINEX file
                                fileLock.remove(QDir::toNativeSeparators(ui->lineEditConverterDgnssOutputRinex->text()));
                            } else {
                                ui->pushButtonConvert->setEnabled(true);
                                ui->pushButtonConvertShowOutput->setEnabled(false);
                                return 1;
                            }
                        } else {*/
                            *saveString += "-output:rinex " + ui->lineEditConverterDgnssOutputRinex->text() + "\n-output:rinexversion " + "2\n";
                            *runString << "-output:rinex" << ui->lineEditConverterDgnssOutputRinex->text() << "-output:rinexversion" << "2";
                        //}
                    }
                } else if ( ui->comboBoxConverterDgnssOutputRinex->currentIndex() == 1 ) { // RINEX v3.00
                    if ( ui->lineEditConverterDgnssOutputRinex->text() == "" ) {
                        *errorString += "RINEX v3.00 file is not set.\n";
                    } else if (this->checknonASCIIcharacters(ui->lineEditConverterDgnssOutputRinex->text())==1) {
                        *errorString += "RINEX v3.00 file has non ASCII characters\n";
                    } else {
                    /*    if ( this->fileExists( ui->lineEditConverterDgnssOutputRinex->text() ) == true && ShowCommandline==0 ) {
                            reply = QMessageBox::question(this, "File already exists",
                                                          QString("The file %1 already exists.\nAre you sure you want to continue?\n").arg(ui->lineEditConverterDgnssOutputRinex->text()),
                                                          QMessageBox::Yes|QMessageBox::No);
                            if ( reply == QMessageBox::Yes ) {
                                //Default output rinex version is 3
                                if (WriteAllParameters==1) {
                                    *saveString += "-output:rinex " + ui->lineEditConverterDgnssOutputRinex->text() + "\n-output:rinexversion " + "3\n";
                                    *runString << "-output:rinex" << ui->lineEditConverterDgnssOutputRinex->text() << "-output:rinexversion" << "3";
                                } else {
                                    *saveString += "-output:rinex " + ui->lineEditConverterDgnssOutputRinex->text() + "\n";
                                    *runString << "-output:rinex" << ui->lineEditConverterDgnssOutputRinex->text();
                                }
                                //Remove RINEX file
                                fileLock.remove(QDir::toNativeSeparators(ui->lineEditConverterDgnssOutputRinex->text()));
                            } else {
                                ui->pushButtonConvert->setEnabled(true);
                                ui->pushButtonConvertShowOutput->setEnabled(false);
                                return 1;
                            }
                        } else {*/
                            //Default output rinex version is 3
                            if (WriteAllParameters==1) {
                                *saveString += "-output:rinex " + ui->lineEditConverterDgnssOutputRinex->text() + "\n-output:rinexversion " + "3\n";
                                *runString << "-output:rinex" << ui->lineEditConverterDgnssOutputRinex->text() << "-output:rinexversion" << "3";
                            } else {
                                *saveString += "-output:rinex " + ui->lineEditConverterDgnssOutputRinex->text() + "\n";
                                *runString << "-output:rinex" << ui->lineEditConverterDgnssOutputRinex->text();
                            }
                        //}
                    }
                }
                break;
            }
        }
        //// End of RTCM Converter
    } else {
        //No conversion mode selected
        *errorString += "No conversion mode selected\n";
    }


    //*saveString += "-output:file " + QDir::toNativeSeparators("./gLAB_conversion.out\n");  //Output file is not saved in configuration file to avoid warning
    *runString << "-output:file" << QDir::toNativeSeparators("./gLAB_conversion.out");
    return 0;
}

void gLAB_GUI::converterLoadParameters(QFile *file) {

    QString line;
    QString option;
    QString userInput;
    QString userInputSingleSpace;
    QString errorString = "";
    QString warningString = "";
    QStringList ParametersList;
    QMessageBox messageBox;
    QTextStream InputFile(file);
    QDate date;
    QTime hour;
    InputFile.setAutoDetectUnicode(true);

    int numSBAS=0;
    int numSBASdir=0;
    int numRTCM=0;
    int numRTCM2=0;
    int numRTCM3=0;
    int numRINEX=0;
    int numAntenna=0;
    int numCorrections=0;
    int numOutputSBASTypes=0;
    int onlyconvertOption=0;
    int pegasus=0,pegasusspace=0,pegasusalign=0;
    int year, month,day;
    int mode=-1; //0 -> SBAS 1->DGNSS
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

        if ( QString::compare(option, "-input:sbas", Qt::CaseInsensitive)==0 ) {
            numSBAS++;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("SBAS", &warningString,&errorString,userInput);
            }
            mode=0;
        } else if ( QString::compare(option, "-output:sbasdir", Qt::CaseInsensitive)==0 ) {
            numSBASdir++;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("Output SBAS directory", &warningString,&errorString,userInput);
            }
            mode=0;
        } else if ( QString::compare(option, "-input:rtcm", Qt::CaseInsensitive)==0  ) {
            numRTCM++;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("RTCM", &warningString,&errorString,userInput);
            }
            mode=1;
        } else if ( QString::compare(option, "-input:rtcm2", Qt::CaseInsensitive)==0 ) {
            numRTCM2++;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("RTCM2", &warningString,&errorString,userInput);
            }
            mode=1;
        } else if ( QString::compare(option, "-input:rtcm3", Qt::CaseInsensitive)==0 ) {
            numRTCM3++;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("RTCM3", &warningString,&errorString,userInput);
            }
            mode=1;
        } else if ( QString::compare(option, "-output:rinex", Qt::CaseInsensitive)==0 ) {
            numRINEX++;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("Output RINEX", &warningString,&errorString,userInput);
            }
            mode=1;
        } else if ( QString::compare(option, "-output:corrections", Qt::CaseInsensitive)==0 ) {
            numCorrections++;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("Output Corrections", &warningString,&errorString,userInput);
            }
            mode=1;
        } else if ( QString::compare(option, "-output:antenna", Qt::CaseInsensitive)==0 ) {
            numAntenna++;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("Output Antenna", &warningString,&errorString,userInput);
            }
            mode=1;
        }
    }

    //Check for errors of type files  given
    if ( (numSBAS>0|| numSBASdir>0) && (numRTCM>0 || numRTCM2>0 || numRTCM3>0 || numRINEX>0 || numCorrections>0 || numAntenna>0) ) {
         errorString += "Cannot determine if it is a SBAS or DGNSS conversion, due to options for both modes were provided.\n";
    }
    //More than one orbit file given
    if (numSBAS>1) {
        errorString += "More than one SBAS file ('-input:sbas' option) is provided.\n";
    }
    if (numSBASdir>1) {
        errorString += "More than one SBAS output directory ('-output:sbasdir' option) is provided.\n";
    }
    if( (numRTCM + numRTCM2 + numRTCM3)>1) {
         errorString += "More than one type of RTCM type file provided.\n";
    }
    if (numRTCM>1) {
         errorString += "More than one RTCM (auto detection) file ('-input:rtcm' option) is provided.\n";
    }
    if (numRTCM2>1) {
         errorString += "More than one RTCM2 file ('-input:rtcm2' option) is provided.\n";
    }
    if (numRTCM3>1) {
         errorString += "More than one RTCM3 file ('-input:rtcm3' option) is provided.\n";
    }
    if (numRINEX>1) {
         errorString += "More than one output RINEX file ('-output:rinex' option) is provided.\n";
    }
    if (numCorrections>1) {
         errorString += "More than one output corrections file ('-output:corrections' option) is provided.\n";
    }
    if (numAntenna>1) {
         errorString += "More than one output antenna file ('-output:antenna' option) is provided.\n";
    }
    if ( numSBAS==0 && numSBASdir==0 && numRTCM==0 && numRTCM2==0 && numRTCM3==0 && numRINEX==0 && numCorrections==0 && numAntenna==0)  {
         errorString += "Cannot determine if it is a SBAS or DGNSS conversion, due to no input or output files were provided.\n";
    }

        //If errors ocurred, show them and return
    if (!errorString.isEmpty()) {
        messageBox.critical(0, "Errors found",
                            "gLAB did not load the the configuration file due to the following errors:\n\n" + errorString);
        return;
    }

    //Second loop: Load parameters
    file->seek(0); //Go back to beginning of file
    setInitialConverterValues(); //Set default values in conversion page

    //Set mode
    if(mode==0) {
        this->on_groupBoxConverterSBAS_clicked(true);
    } else {
        this->on_groupBoxConverterDgnss_clicked(true);
    }

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

        //SBAS
        if ( QString::compare(option, "-input:sbas", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                ui->lineEdit_convert_sbas->setText(userInput);
            }
        } else if ( QString::compare(option, "-output:sbasdir", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                ui->lineEdit_outputpath_sbas->setText(userInput);
            }
        } else if ( QString::compare(option, "-output:rinexb", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBox_rinexb->setChecked(true);
            numOutputSBASTypes++;
        } else if ( QString::compare(option, "-output:ems", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBox_ems->setChecked(true);
            numOutputSBASTypes++;
        } else if ( QString::compare(option, "-output:pegasus", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBox_pegasus->setChecked(true);
            this->on_checkBox_pegasus_clicked(true);
            numOutputSBASTypes++;
            pegasus=1;
        } else if ( QString::compare(option, "-output:pegspace", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBox_pegasus_space->setChecked(true);
            pegasusspace=1;
        } else if ( QString::compare(option, "-output:pegfilealign", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBox_pegasus_align->setChecked(true);
            pegasusalign=1;
        } else if ( QString::compare(option, "-onlyconvert", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            onlyconvertOption++;

        //DGNSS
        } else if ( QString::compare(option, "-input:rtcm", Qt::CaseInsensitive)==0  ) {
            if (ParametersList.count()>=1) {
                ui->lineEditConverterDgnssInput->setText(userInput);
                this->on_comboBoxConverterDgnssInput_currentIndexChanged(0);
            }
        } else if ( QString::compare(option, "-input:rtcm2", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                ui->lineEditConverterDgnssInput->setText(userInput);
                this->on_comboBoxConverterDgnssInput_currentIndexChanged(1);
            }
        } else if ( QString::compare(option, "-input:rtcm3", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                ui->lineEditConverterDgnssInput->setText(userInput);
                this->on_comboBoxConverterDgnssInput_currentIndexChanged(2);
            }
        } else if ( QString::compare(option, "-input:rtcm:initdate", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                if (userInput.length()<8 || userInput.length()>8) {
                    warningString += "RTCM input date format is incorrect. The correct format is YYYYMMDD. It was skipped.\n";
                } else {
                    year=userInputSingleSpace.section(" ", 0,0).mid(0,4).toInt();
                    month=userInputSingleSpace.section(" ", 0,0).mid(4,2).toInt();
                    day=userInputSingleSpace.section(" ", 0,0).mid(6,2).toInt();
                    if (year<1980) {
                        warningString += "RTCM input date is below 1980. It was skipped.\n";
                    } else if (!(QDate::isValid(year, month, day))) {
                        warningString += "RTCM input date is not valid. It was skipped.\n";
                    } else {
                        date.setDate(year,month,day);
                        ui->dateEdit4->setDate(date);
                    }
                }
            }
        } else if ( QString::compare(option, "-input:rtcm:inithour", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0 || userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>24) {
                   warningString += "RTCM input hour is not valid. It was skipped.\n";
                } else {
                    hour.setHMS(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt(),0,0,0);
                    ui->timeEdit3->setTime(hour);
                }
            }
        } else if ( QString::compare(option, "-output:rinex", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                ui->lineEditConverterDgnssOutputRinex->setText(userInput);
            }
        } else if ( QString::compare(option, "-output:rinexversion", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<2 || userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>3) {
                warningString += "Parameter '" + option + "' can only have values '2' or '3'. It was skipped.\n";
            } else {
                ui->comboBoxConverterDgnssOutputRinex->setCurrentIndex(userInputSingleSpace.section(" ", 0,0).toInt()-2);
            }
        } else if ( QString::compare(option, "-output:corrections", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                ui->lineEdit_outputpath_sbas->setText(userInput);
            }
        } else if ( QString::compare(option, "-output:antenna", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                ui->lineEdit_outputpath_sbas->setText(userInput);
            }
        } else if ( QString::compare(option, "-output:file", Qt::CaseInsensitive)==0 ) {
             warningString += "Parameter '" + option + "' is omitted in conversion mode\n";
        } else if ( QString::compare(option, "--output:file", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            warningString += "Parameter '" + option + "' is for setting output messages to standard output, which would be lost after execution finishes. It was skipped.\n";
        }
    }

    if(mode==0 && onlyconvertOption==0) {
         warningString += "SBAS conversion only mode requires parameter '-onlyconvert', which is missing in the configuration file.\n";
    }

    if(mode==0 && pegasusspace==1 && pegasus==0) {
         warningString +=  "Option '-output:pegspace' to set space as column delimeter in Pegasus files provided, but Pegasus output option not selected (missing '-output:pegspace' parameter).\n";
    }

    if(mode==0 && pegasusalign==1 && pegasus==0) {
         warningString += "Option '-output:pegfilealign' to align columns in Pegasus files provided, but Pegasus output option not selected (missing '-output:pegspace' parameter).\n";
    }

    if (!warningString.isEmpty()) {
        messageBox.warning(0, "Errors found",
                            "gLAB loaded the configuration file, but found the following errors:\n\n" + warningString);
    }
}
