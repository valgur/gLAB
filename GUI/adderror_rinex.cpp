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


////////////////////// Push buttons /////////////////////
// Open dialog to set the input RINEX Observation filename and path
void gLAB_GUI::on_pushButtonRinexObsAddError_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("RINEX Files (*.??o);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRinexObsAddError->setText(QDir::toNativeSeparators(fileName[0]));
            //Set path for output RINEX observation file
            ui->lineEditRinexOutputFileAddError->setText(QDir::toNativeSeparators(fileName[0]+"_usererror"));
            //Set path for output file
            ui->lineEditOutputFileAddError->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/gLAB_usererror.out"));
        }
    }
}

// Open dialog to set the input User Added Error filename and path
void gLAB_GUI::on_pushButtonUserAddedErrorAddError_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("User Added Error Files (*.txt);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditUserAddedErrorAddError->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

// Open dialog to set the output RINEX observation filename and path
void gLAB_GUI::on_pushButtonRinexOutputFileAddError_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("RINEX Files (*.??o *o.rnx);;All Files (*.*)"));
    //dialog.selectFile("");
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRinexOutputFileAddError->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

// Open dialog to set the output filename and path
void gLAB_GUI::on_pushButtonOutputFileAddError_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("gLAB Output Files (*.out);;All Files (*.*)"));
    dialog.selectFile(".out");
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditOutputFileAddError->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

//Set all output messages button
void gLAB_GUI::on_pushButtonAddErrorMessagesAll_clicked() {
    ui->checkBoxPrintInfoAddError->setChecked(true);
    ui->checkBoxPrintUserErrorAddError->setChecked(true);
}

//Unset all output messages button
void gLAB_GUI::on_pushButtonAddErrorMessagesNone_clicked() {
    ui->checkBoxPrintInfoAddError->setChecked(false);
    ui->checkBoxPrintUserErrorAddError->setChecked(false);
}
////////////////// End of Push buttons //////////////////


///////////////// Start of Context menus (right-click menus) //////////////////
void gLAB_GUI::labelAddErrorObservationFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelAddErrorObservationFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open RINEX Observation File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditRinexObsAddError->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditRinexObsAddError->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditRinexObsAddError->text();
        #endif

        // Execute the program
        if (ui->lineEditRinexObsAddError->text() == "") {
            messageBox.warning(0, "Error","RINEX Observation file is empty\n");
        } else if (this->fileExists(ui->lineEditRinexObsAddError->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditRinexObsAddError->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditRinexObsAddError->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelAddErrorUserAddedErrorFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelAddErrorUserAddedErrorFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open User Added Error File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditUserAddedErrorAddError->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditUserAddedErrorAddError->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditUserAddedErrorAddError->text();
        #endif

        // Execute the program
        if (ui->lineEditUserAddedErrorAddError->text() == "") {
            messageBox.warning(0, "Error","User Added Error file is empty\n");
        } else if (this->fileExists(ui->lineEditUserAddedErrorAddError->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditUserAddedErrorAddError->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditUserAddedErrorAddError->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelAddErrorRinexOutputFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelAddErrorRinexOutputFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open Output RINEX Observation File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditRinexOutputFileAddError->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditRinexOutputFileAddError->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditRinexOutputFileAddError->text();
        #endif

        // Execute the program
        if (ui->lineEditRinexOutputFileAddError->text() == "") {
            messageBox.warning(0, "Error","Output RINEX Observation file is empty\n");
        } else if (this->fileExists(ui->lineEditRinexOutputFileAddError->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditRinexOutputFileAddError->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditRinexOutputFileAddError->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelAddErrorOutputFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelAddErrorOutputFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open Output Messages File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditOutputFileAddError->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditOutputFileAddError->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditOutputFileAddError->text();
        #endif

        // Execute the program
        if (ui->lineEditOutputFileAddError->text() == "") {
            messageBox.warning(0, "Error","Output Messages file is empty\n");
        } else if (this->fileExists(ui->lineEditOutputFileAddError->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputFileAddError->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditOutputFileAddError->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}
///////////////// End of Context menus (right-click menus) //////////////////

void gLAB_GUI::getAddErrorOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString) {

    *errorString = "";
    *warningString="";
    *saveString = "";


    //Check input RINEX observation file
    if ( ui->lineEditRinexObsAddError->text() == "" ) {
        *errorString += "RINEX Observation source file is empty.\n";
    } else if ( this->fileExists(ui->lineEditRinexObsAddError->text())==false ) {
        *errorString += "RINEX Observation source file does not exist.\n";
    } else if (this->checknonASCIIcharacters(ui->lineEditRinexObsAddError->text())==1) {
        *errorString += "RINEX Observation source file has non ASCII characters\n";
    } else {
        *saveString += "-input:obs " + ui->lineEditRinexObsAddError->text()+ "\n";
        *runString <<  "-input:obs" << ui->lineEditRinexObsAddError->text();
    }

    //Check input user added error file
    if ( ui->lineEditUserAddedErrorAddError->text() == "" ) {
        *errorString += "User Added Error source file is empty.\n";
    } else if ( this->fileExists(ui->lineEditUserAddedErrorAddError->text())==false ) {
        *errorString += "User Added Error source file does not exist.\n";
    } else if (this->checknonASCIIcharacters(ui->lineEditUserAddedErrorAddError->text())==1) {
        *errorString += "User Added Error source file has non ASCII characters\n";
    } else {
        *saveString += "-input:usererror " + ui->lineEditUserAddedErrorAddError->text()+ "\n";
        *runString <<  "-input:usererror" << ui->lineEditUserAddedErrorAddError->text();
    }

    //Check output Rinex observation file
    if ( ui->lineEditRinexOutputFileAddError->text() == "" ) {
        *errorString += "Output RINEX Observation file is empty.\n";
    } else if ( ui->lineEditRinexOutputFileAddError->text() == ui->lineEditRinexObsAddError->text() ) {
        *errorString += "Output RINEX Observation file can not have the same filename as the input observation file.\n";
    } else if (this->checknonASCIIcharacters(ui->lineEditRinexOutputFileAddError->text())==1) {
        *errorString += "Output RINEX Observation file has non ASCII characters\n";
    } else {
        *saveString += "-output:rinex " + ui->lineEditRinexOutputFileAddError->text()+ "\n";
        *runString <<  "-output:rinex" << ui->lineEditRinexOutputFileAddError->text();
    }

    //Check output messages file
    if ( ui->lineEditOutputFileAddError->text() == "" ) {
        if (ui->checkBoxPrintInfoAddError->isChecked()==true || ui->checkBoxPrintUserErrorAddError->isChecked()==true) {
            //Only show error if any of the output messages is enabled
            *errorString += "Output messages file is empty.\n";
        }
    } else if (this->checknonASCIIcharacters(ui->lineEditOutputFileAddError->text())==1) {
        *errorString += "Output RINEX Observation file has non ASCII characters\n";
    } else {
        *saveString += "-output:file " + ui->lineEditOutputFileAddError->text()+ "\n";
        *runString <<  "-output:file" << ui->lineEditOutputFileAddError->text();
    }

    //Check messages to print
    if (ui->checkBoxPrintInfoAddError->isChecked()==false && ui->checkBoxPrintUserErrorAddError->isChecked()==false) {
        *saveString += "-print:none\n";
        *runString <<  "-print:none";
    } else {
        if (ui->checkBoxPrintInfoAddError->isChecked()==true) {
            if(WriteAllParameters==1) {
                *saveString += "-print:info\n";
                *runString <<  "-print:info";
            }
        } else {
            *saveString += "--print:info\n";
            *runString <<  "--print:info";
        }
        if (ui->checkBoxPrintUserErrorAddError->isChecked()==true) {
            if(WriteAllParameters==1) {
                *saveString += "-print:usererror\n";
                *runString <<  "-print:usererror";
            }
        } else {
            *saveString += "--print:usererror\n";
            *runString <<  "--print:usererror";
        }
    }
}

void gLAB_GUI::AddErrorLoadParameters(QFile *file) {

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

    int numObs=0;
    int numNav=0;
    int numSP3=0;
    int numOrb=0;
    int numSBAS=0;
    int numDGNSS=0;
    int numRTCM=0;
    int numRTCM2=0;
    int numRTCM3=0;
    int numUserError=0;
    int numOutput=0;
    int numOutputRinex=0;
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

        if ( QString::compare(option, "-input:obs", Qt::CaseInsensitive)==0 ) {
            numObs++;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("Observation", &warningString,&errorString,userInput);
            }
        } else if ( QString::compare(option, "-input:usererror", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("User error", &warningString,&errorString,userInput);
            }
            numUserError++;
        } else if ( QString::compare(option, "-input:nav", Qt::CaseInsensitive)==0 ) {
            numNav++;
        } else if ( QString::compare(option, "-input:sp3", Qt::CaseInsensitive)==0  ) {
            numSP3++;
        } else if ( QString::compare(option, "-input:orb", Qt::CaseInsensitive)==0  ) {
            numOrb++;
        } else if ( QString::compare(option, "-input:sbas", Qt::CaseInsensitive)==0 ) {
            numSBAS++;
        } else if ( QString::compare(option, "-input:dgnss", Qt::CaseInsensitive)==0  ) {
            numDGNSS++;
        } else if ( QString::compare(option, "-input:rtcm", Qt::CaseInsensitive)==0  ) {
            numRTCM++;
        } else if ( QString::compare(option, "-input:rtcm2", Qt::CaseInsensitive)==0 ) {
            numRTCM2++;
        } else if ( QString::compare(option, "-input:rtcm3", Qt::CaseInsensitive)==0 ) {
            numRTCM3++;
        } else if ( QString::compare(option, "-output:file", Qt::CaseInsensitive)==0 ) {
            numOutput++;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("Output", &warningString,&errorString,userInput);
            }
        } else if ( QString::compare(option, "-output:rinex", Qt::CaseInsensitive)==0 ) {
            numOutputRinex++;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("Output RINEX", &warningString,&errorString,userInput);
            }
        }
    }

    //Check for invalid input files in this mode
    if (numObs>1) {
        errorString += "More than one observation file ('-input:obs' option) is provided.\n";
    }
    if (numUserError>1) {
        errorString += "More than one user added error file ('-input:usererror' option) is provided.\n";
    }
    if (numOutputRinex>1) {
        errorString += "More than one output RINEX file ('-output:rinex' option) is provided.\n";
    }
    if (numOutput>1) {
        errorString += "More than one output file ('-output:file' option) is provided.\n";
    }
    if (numNav>0) {
        errorString += "A navigation file ('-input:nav' option) is provided, which is forbidden in this processing mode.\n";
    }
    if (numSP3>0) {
        errorString += "A SP3 file ('-input:sp3' option) is provided, which is forbidden in this processing mode.\n";
    }
    if (numOrb>0) {
        errorString += "A orbit SP3 file ('-input:orb' option) is provided, which is forbidden in this processing mode.\n";
    }
    if (numSBAS>0) {
        errorString +="A SBAS file ('-input:sbas' option) is provided, which is forbidden in this processing mode.\n";
    }
    if (numDGNSS>0) {
        errorString +="A DGNSS file ('-input:dgnss' option) is provided, which is forbidden in this processing mode.\n";
    }
    if (numRTCM>0) {
        errorString +="A RTCM file ('-input:rtcm' option) is provided, which is forbidden in this processing mode.\n";
    }
    if (numRTCM2>0) {
        errorString +="A RTCM2 file ('-input:rtcm2' option) is provided, which is forbidden in this processing mode.\n";
    }
    if (numRTCM3>0) {
        errorString +="A RTCM3 file ('-input:rtcm3' option) is provided, which is forbidden in this processing mode.\n";
    }


    //If errors ocurred, show them and return
    if (!errorString.isEmpty()) {
        messageBox.critical(0, "Errors found",
                            "gLAB did not load the the configuration file due to the following errors:\n\n" + errorString);
        return;
    }
    //Second loop: Load parameters
    file->seek(0); //Go back to beginning of file
    setInitialAddUserErrorValues(); //Set default values in Add User error to RINEX page

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

        if ( QString::compare(option, "-input:obs", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                ui->lineEditRinexObsAddError->setText(userInput);
            }
        } else if ( QString::compare(option, "-input:usererror", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                ui->lineEditUserAddedErrorAddError->setText(userInput);
            }
        } else if ( QString::compare(option, "-output:file", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                ui->lineEditOutputFileAddError->setText(userInput);
            }
        } else if ( QString::compare(option, "--output:file", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            warningString += "Parameter '" + option + "' is for setting output messages to standard output, which will be lost after execution finishes. It was skipped.\n";
        } else if ( QString::compare(option, "-output:rinex", Qt::CaseInsensitive)==0 ) {
            ui->lineEditRinexOutputFileAddError->setText(userInput);
        } else if ( QString::compare(option, "-print:info", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintInfoAddError->setChecked(true);
        } else if ( QString::compare(option, "--print:info", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintInfoAddError->setChecked(false);
        } else if ( QString::compare(option, "-print:usererror", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintUserErrorAddError->setChecked(true);
        } else if ( QString::compare(option, "--print:usererror", Qt::CaseInsensitive)==0 ) {
            extraParametersToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintUserErrorAddError->setChecked(false);
        } else if ( QString::compare(option, "-print:all", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxPrintInfoAddError->setChecked(true);
            ui->checkBoxPrintUserErrorAddError->setChecked(true);
        } else if ( QString::compare(option, "-print:none", Qt::CaseInsensitive)==0||QString::compare(option, "--print:none", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxPrintInfoAddError->setChecked(false);
            ui->checkBoxPrintUserErrorAddError->setChecked(false);
        }
    }

    if (!warningString.isEmpty()) {
        messageBox.warning(0, "Errors found",
                            "gLAB loaded the configuration file, but found the following errors:\n\n" + warningString);
    }
}
