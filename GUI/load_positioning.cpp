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

// Function to load a gLAB configuration file
void gLAB_GUI::on_actionLoad_triggered() {
    // Open dialog to select the gLAB configuration file
    QString line;
    QFileDialog dialog(this);
    QString option;
    QString userInput;
    QString errorString = "";
    QString warningString = "";
    QString userInputSingleSpace;
    QStringList ParametersList;

    QDate date;
    QTime hour;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");

    int i;
    int numNav=0,numSP3=0,numOrb=0,numClk=0, numSatAnt=0, numRecAnt=0, numBlockAnt=0, numInputOrbFiles=0;
    int recAntParameter=0, noSatAntParameter=0, noRecAntParameter=0, numRefPos=0;
    int numSBAS=0, numDGNSS=0, numRTCM=0, numRTCM2=0, numRTCM3=0, numOutput=0;
    int numSigmaMultipath=0, numUserError=0, numSinex=0, numDCB=0, numRecTypes=0;
    int numSBASiono=0, numKlob=0, numNeq=0, numBDS=0, numIONEX=0, numStfdESA=0, numStfdESALOI=0;
    int numKML=0, numKML0=0, numOutputSP3=0, numObs=0, numOutRefPos=0;
    int numDCBType[6]= {0,0,0,0,0,0}; //0-> P1-C1 DCB 1-> P1-P2 DCB 2-> P2-C2 DCB 3-> Rinex Nav 4-> MGEX DCB 5-> IONEX
    //int CodeSingleFreq=0, PhaseDualFreq=0, CodeDualFreq=0, PhaseSingleFreq=0;
    int DualFrequencyUsed=0;
    int year, month,day, doy, hour2, minute, second,sod,GPSWeek,sow;
    int mode=-1; //0 ->SPP 1->PPP 2->SBAS 1F 3->SBAS DFMC 4->DGNSS
    int L1Avail=1, L2Avail=1, L5Avail=1;
    int PhaseFreq1Used=0, CodeFreq2Used=0, PhaseFreq2Used=0;
    int DCBfiletype, BackwardFiltering=0, numKMLRanges=0;
    int DCBGNSS[MAX_GNSS]={0};
    //int SmoothNoL1P=0;
    int ValidDate, addDay, leapYear;
    int daysmonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int daysmonthLeapYear[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int RefFileFirst=-1; //-1->Unknown 0->First '-pre:setrecpos' 1->First input file  2->Only input:ref file
    int RefFileInterpDegree=-1;
    int StartPRN,EndPRN,HashPos;
    int PRN,ValidRange;
    int smoothMeasParam=0,smoothAutoParam=0,filterCombTypeParam=0;
    int filterSelectParamProvided=0;
    int IGFFreqProvided=0,IGFMeasProvided=0;
    int MeasPrintParamProvided=0;
    //int ValidSNR;
    int fixedWeightProvided=0,elevWeightProvided=0,elevSinWeightProvided=0,snrWeightProvided=0,snrElevWeightProvided=0;
    int minSNRSelProvided=0,maxSNRSelProvided=0;
    double radius;
    //double SNR;
    QString RefFilePath;
    QString ParameterName;
    QString GPSLetter="G", GLONASSLetter="R", GalileoLetter="E", BDSLetter="C", GEOLetter="S", QZSSLetter="J", IRNSSLetter="I";
    QString Sign;
    QString CoordPhi="",CoordQ="",CoordP0="";
    QString ClkPhi="",ClkQ="",ClkP0="";
    QString ISCBPhi="",ISCBQ="",ISCBP0="";
    QStringList PRNlist;
    QStringList fixedWeightParam,elevWeightParam,elevSinWeightParam,snrWeightParam,snrElevWeightParam;
    QStringList filterSelectParam, smoothMeasParamList;
    QStringList IGFFreqParamList, IGFMeasParamList;
    QStringList MeasPrintParamList;
    enum GNSSystem System;


    GNSSFreqCMDMode=GNSSMeasCMDMode=GNSSSmoothFlag=0;
    for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
        GNSSMeasInAll[iGNSS][0][0]=GNSSMeasInAll[iGNSS][0][1]=GNSSMeasInAll[iGNSS][1][0]=GNSSMeasInAll[iGNSS][1][1]=GNSSMeasInAll[iGNSS][2][0]=GNSSMeasInAll[iGNSS][2][1]="";
        GNSSMeasCMD[iGNSS][0]=GNSSMeasCMD[iGNSS][1]=GNSSMeasCMD[iGNSS][2]=0;
        GNSSMeasNoiseCMD[iGNSS][0]=GNSSMeasNoiseCMD[iGNSS][1]=0;
    }

    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("gLAB Configuration Files (*.cfg);;All Files (*.*)"));
    if(ui->stackedWidgetMainWindow->currentIndex()==0) {
        if (configFileName[ui->stackedWidgetMainWindow->currentIndex()]!="") {
            dialog.selectFile(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
        } else {
            dialog.selectFile("gLAB.cfg");
        }
    } else if (ui->stackedWidgetMainWindow->currentIndex()==1) {
        return;
    } else if (ui->stackedWidgetMainWindow->currentIndex()==2) {
        if (configFileName[ui->stackedWidgetMainWindow->currentIndex()]!="") {
            dialog.selectFile(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
        } else {
            dialog.selectFile("gLAB_convert.cfg");
        }
    } else if (ui->stackedWidgetMainWindow->currentIndex()==3) {
        if (configFileName[ui->stackedWidgetMainWindow->currentIndex()]!="") {
            dialog.selectFile(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
        } else {
            dialog.selectFile("gLAB_compare.cfg");
        }
    } else if (ui->stackedWidgetMainWindow->currentIndex()==4) {
        if (configFileName[ui->stackedWidgetMainWindow->currentIndex()]!="") {
            dialog.selectFile(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
        } else {
            dialog.selectFile("gLAB_show.cfg");
        }
    } else if (ui->stackedWidgetMainWindow->currentIndex()==5) {
        if (configFileName[ui->stackedWidgetMainWindow->currentIndex()]!="") {
            dialog.selectFile(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
        } else {
            dialog.selectFile("gLAB_adderror.cfg");
        }
    } else {
        return;
    }
    if ( dialog.exec() ) {
        configFileName[ui->stackedWidgetMainWindow->currentIndex()] = dialog.selectedFiles().at(0);
        if ( !configFileName[ui->stackedWidgetMainWindow->currentIndex()].isEmpty() ) {
            QFile file(configFileName[ui->stackedWidgetMainWindow->currentIndex()]);
            if ( !file.open(QIODevice::ReadOnly) ) {
                messageBox.setWindowTitle("Errors found");
                messageBox.setText("gLAB could not open the Configuration File.\n");
                messageBox.setIcon(QMessageBox::Critical);
                messageBox.exec();
                return;
             } else {
                // Enable the show action
                ui->actionShow->setEnabled(true);

                if(ui->stackedWidgetMainWindow->currentIndex()==0) {
                    //Code below
                } else if (ui->stackedWidgetMainWindow->currentIndex()==1) {
                    file.close();
                    return;
                } else if (ui->stackedWidgetMainWindow->currentIndex()==2) {
                    converterLoadParameters(&file);
                    file.close();
                    return;
                } else if (ui->stackedWidgetMainWindow->currentIndex()==3) {
                    compareOrbitsLoadParameters(&file);
                    file.close();
                    return;
                } else if (ui->stackedWidgetMainWindow->currentIndex()==4) {
                    showOrbitsLoadParameters(&file);
                    file.close();
                    return;
                } else if (ui->stackedWidgetMainWindow->currentIndex()==5) {
                    AddErrorLoadParameters(&file);
                    file.close();
                    return;
                } else {
                    file.close();
                    return;
                }

                QTextStream InputFile(&file);
                InputFile.setAutoDetectUnicode(true);


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

                    if (QString::compare(option, "-help", Qt::CaseInsensitive)==0 || QString::compare(option, "--help", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show the parameter help message and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-messages", Qt::CaseInsensitive)==0 || QString::compare(option, "--messages", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show the fields of each output message and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-messagesv5", Qt::CaseInsensitive)==0 || QString::compare(option, "--messagesv5", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show the fields of each output message (in legacy version 5 format) and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-examples", Qt::CaseInsensitive)==0 || QString::compare(option, "--examples", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show examples for calling the program and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-faq", Qt::CaseInsensitive)==0 || QString::compare(option, "--faq", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to show the FAQ (Frequently Asked Questions).\n";
                    } else if (QString::compare(option, "-autofillscript", Qt::CaseInsensitive)==0 || QString::compare(option, "--autofillscript", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to print a script for bash to enable gLAB parameter autocompletion in bash (see script header for installation details).\n";
                    } else if (QString::compare(option, "-config", Qt::CaseInsensitive)==0 || QString::compare(option, "--config", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show info of the configuration file and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-usererrorfile", Qt::CaseInsensitive)==0 || QString::compare(option, "--usererrorfile", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show a detailed description and examples of the user-defined error configuration file and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-sigmamultipathfile", Qt::CaseInsensitive)==0 || QString::compare(option, "--sigmamultipathfile", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show a detailed description and examples of the user multipath model configuration file and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-rtcmv2conversioninfo", Qt::CaseInsensitive)==0 || QString::compare(option, "--rtcmv2conversioninfo", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show a detailed description of output files generated from RTCM v2.X conversion and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-referenceposfile", Qt::CaseInsensitive)==0 || QString::compare(option, "--referenceposfile", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show a detailed description of the reference position file and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-sbasplotsinfo", Qt::CaseInsensitive)==0 || QString::compare(option, "--sbasplotsinfo", Qt::CaseInsensitive)==0 ||
                               QString::compare(option, "-sbasmapsinfo", Qt::CaseInsensitive)==0 || QString::compare(option, "--sbasmapsinfo", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is to make gLAB show a detailed description about how to generate SBAS maps and exit. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-onlyconvert", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is for changing gLAB mode to SBAS conversion only. It is not valid for positioning mode.\n";
                    } else if (QString::compare(option, "-dateconv:calendar", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(6,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is for converting date formats. To convert date format in the GUI, go to menu 'Help->GNSS Date Converter'.\n";
                    } else if (QString::compare(option, "-dateconv:doy", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(3,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is for converting date formats. To convert date format in the GUI, go to menu 'Help->GNSS Date Converter'.\n";
                    } else if (QString::compare(option, "-dateconv:gpsweek", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(2,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is for converting date formats. To convert date format in the GUI, go to menu 'Help->GNSS Date Converter'.\n";
                    } else if (QString::compare(option, "-dateconv:mjdn", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(2,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is for converting date formats. To convert date format in the GUI, go to menu 'Help->GNSS Date Converter'.\n";
                    } else if (QString::compare(option, "-coordconv:cartesian", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(3,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is for converting coordinate systems. To convert coordinate systems in the GUI, go to menu 'Help->GNSS Coordinate Converter'.\n";
                    } else if (QString::compare(option, "-coordconv:geodetic", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(3,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is for converting coordinate systems. To convert coordinate systems in the GUI, go to menu 'Help->GNSS Coordinate Converter'.\n";
                    } else if ( QString::compare(option, "-coordconv:spherical", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(3,&warningString,option,ParametersList);
                        errorString += warningString; //This is to add to error message extra parameters given
                        warningString = "";
                        errorString += "Parameter '" + option + "' is for converting coordinate systems. To convert coordinate systems in the GUI, go to menu 'Help->GNSS Coordinate Converter'.\n";
                    } else if ( QString::compare(option, "-input:obs", Qt::CaseInsensitive)==0 ) {
                        numObs++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Observation", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-input:nav", Qt::CaseInsensitive)==0 ) {
                        numNav++;
                        numInputOrbFiles++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Navigation", &warningString,&errorString,userInput);
                        }
                        if(mode==-1)mode=0;
                    } else if ( QString::compare(option, "-input:navglo", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("GLONASS navigation", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-input:navhealth", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Health flags navigation", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-input:sp3", Qt::CaseInsensitive)==0  ) {
                        numSP3++;
                        numInputOrbFiles++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SP3", &warningString,&errorString,userInput);
                        }
                        mode=1;
                    } else if ( QString::compare(option, "-input:orb", Qt::CaseInsensitive)==0  ) {
                        numOrb++;
                        numInputOrbFiles++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SP3 orbit only", &warningString,&errorString,userInput);
                        }
                        mode=1;
                    } else if ( QString::compare(option, "-input:clk", Qt::CaseInsensitive)==0 ) {
                        numClk++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Clock", &warningString,&errorString,userInput);
                        }
                        mode=1;
                    } else if ( QString::compare(option, "-input:ant", Qt::CaseInsensitive)==0 ) {
                        numSatAnt++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Sat. ANTEX", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-input:antrec", Qt::CaseInsensitive)==0 ) {
                        numRecAnt++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (ParametersList.count()==2) {
                            warningString += "Parameter '" + option + "' has two files. In the GUI only one file can be loaded (the second file will be skipped).\n";
                            checkConfigurationFileInputFilePaths("Rec. ANTEX", &warningString,&errorString,userInput);
                        } else {
                            checkConfigurationFileInputFilePaths("Rec. ANTEX", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-input:antsatblock", Qt::CaseInsensitive)==0 ) {
                        numBlockAnt++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Sat. Block ANTEX", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-input:sbas1f", Qt::CaseInsensitive)==0 || QString::compare(option, "-input:sbas", Qt::CaseInsensitive)==0 ) {
                        numSBAS++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS", &warningString,&errorString,userInput);
                        }
                        mode=2;
                    } else if ( QString::compare(option, "-input:sbasdfmc", Qt::CaseInsensitive)==0 ) {
                        numSBAS++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS", &warningString,&errorString,userInput);
                        }
                        mode=3;
                    } else if ( QString::compare(option, "-input:dgnss", Qt::CaseInsensitive)==0  ) {
                        numDGNSS++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("DGNSS", &warningString,&errorString,userInput);
                        }
                        mode=4;
                    } else if ( QString::compare(option, "-input:rtcm", Qt::CaseInsensitive)==0  ) {
                        numRTCM++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("RTCM", &warningString,&errorString,userInput);
                        }
                        mode=4;
                    } else if ( QString::compare(option, "-input:rtcm2", Qt::CaseInsensitive)==0 ) {
                        numRTCM2++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("RTCM2", &warningString,&errorString,userInput);
                        }
                        mode=4;
                    } else if ( QString::compare(option, "-input:rtcm3", Qt::CaseInsensitive)==0 ) {
                        numRTCM3++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("RTCM3", &warningString,&errorString,userInput);
                        }
                        mode=4;
                    } else if ( QString::compare(option, "-input:snx", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SINEX", &warningString,&errorString,userInput);
                        }
                        numSinex++;
                    } else if ( QString::compare(option, "-input:klb", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Klobuchar Navigation", &warningString,&errorString,userInput);
                            this->on_groupBoxIonoSource_clicked(true);
                            this->on_radioButtonIonoSourceBrdc_clicked();
                            this->on_comboBoxIonoSourceBrdc_currentIndexChanged(1);
                            ui->lineEditIonoSourceRinexNav->setText(userInput);
                            ui->comboBoxIonoCorrection->setCurrentIndex(0);
                        }
                        numKlob++;
                    } else if ( QString::compare(option, "-input:neq", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("NeQuick Navigation", &warningString,&errorString,userInput);
                            this->on_groupBoxIonoSource_clicked(true);
                            this->on_radioButtonIonoSourceBrdc_clicked();
                            this->on_comboBoxIonoSourceBrdc_currentIndexChanged(1);
                            ui->lineEditIonoSourceRinexNav->setText(userInput);
                            ui->comboBoxIonoCorrection->setCurrentIndex(1);
                        }
                        numNeq++;
                    } else if ( QString::compare(option, "-input:bei", Qt::CaseInsensitive)==0 || QString::compare(option, "-input:bds", Qt::CaseInsensitive)==0) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("BeiDou Navigation", &warningString,&errorString,userInput);
                            this->on_groupBoxIonoSource_clicked(true);
                            this->on_radioButtonIonoSourceBrdc_clicked();
                            this->on_comboBoxIonoSourceBrdc_currentIndexChanged(1);
                            ui->lineEditIonoSourceRinexNav->setText(userInput);
                            ui->comboBoxIonoCorrection->setCurrentIndex(3);
                        }
                        numBDS++;
                    } else if ( QString::compare(option, "-input:inx", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("IONEX", &warningString,&errorString,userInput);
                            this->on_groupBoxIonoSource_clicked(true);
                            this->on_radioButtonIonoSourceIonex_clicked();
                            ui->lineEditIonoSourceIonex->setText(userInput);
                        }
                        numIONEX++;
                    } else if ( QString::compare(option, "-input:sbasiono", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS iono", &warningString,&errorString,userInput);
                            this->on_groupBoxIonoSource_clicked(true);
                            this->on_radioButtonIonoSourceSbas_clicked();
                            ui->lineEditSbas->setText(userInput);
                        }
                        numSBASiono++;
                    } else if ( QString::compare(option, "-input:dcb", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("DCB", &warningString,&errorString,userInput);
                            DCBfiletype=checkDCBFileType(userInput);
                            if (DCBfiletype==-1) {
                                errorString += "Unknown DCB file type '" + userInput + "'.\n";
                            } else {
                                numDCBType[DCBfiletype]++;
                            }
                        }
                        numDCB++;
                    } else if ( QString::compare(option, "-input:rec", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("GPS Receiver Types", &warningString,&errorString,userInput);
                        }
                        numRecTypes++;
                    } else if ( QString::compare(option, "-input:usererror", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("User error", &warningString,&errorString,userInput);
                        }
                        numUserError++;
                    } else if ( QString::compare(option, "-input:sigmpath", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS Sigma multipath", &warningString,&errorString,userInput);
                        }
                        numSigmaMultipath++;
                    } else if ( QString::compare(option, "-input:refpos", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Reference position", &warningString,&errorString,userInput);
                            RefFilePath=userInput;
                        }
                        numRefPos++;
                        if(RefFileFirst==-1) {
                            RefFileFirst=2;
                        }
                    } else if ( QString::compare(option, "-pre:refpos:deg", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            //warning will be issued in the second reading loop
                        } else {
                            if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                                //warning will be issued in the second reading loop
                            } else {
                                RefFileInterpDegree=userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt();
                            }
                        }
                    } else if ( QString::compare(option, "-pre:setrecpos", Qt::CaseInsensitive)==0 ) {
                        if(RefFileFirst==-1) {
                            RefFileFirst=0;
                        } else if (RefFileFirst==2) {
                            RefFileFirst=1;
                        }
                    } else if ( QString::compare(option, "-pre:availf", Qt::CaseInsensitive)==0 ) {
                        //Read this option to know which frequencies are available
                        if (ParametersList.count()<1) {
                            //warning will be issued in the second reading loop
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GLONASSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==GalileoLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==BDSLetter
                                   ||userInputSingleSpace.section(" ", 0,0).at(0)==GEOLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==QZSSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==IRNSSLetter ) {
                            //warning will be issued in the second reading loop
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GPSLetter) {
                            if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).length()==1) {
                              //warning will be issued in the second reading loop
                            } else {
                                L1Avail=L2Avail=L5Avail=0;
                                for(i=1;i<userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).length();i++) {
                                    if(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).mid(i,i).toInt()==1) {
                                        L1Avail=1;
                                    } else if(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).mid(i,i).toInt()==2) {
                                        L2Avail=1;
                                    } else if(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).mid(i,i).toInt()==5) {
                                        L5Avail=1;
                                    }
                                }
                            }
                        }
                    } else if ( QString::compare(option, "-pre:smoothauto", Qt::CaseInsensitive)==0 ) {
                        smoothAutoParam=1;
                    } else if ( QString::compare(option, "--pre:smoothauto", Qt::CaseInsensitive)==0 ) {
                        smoothAutoParam=0;
                    } else if ( QString::compare(option, "-pre:smoothmeas", Qt::CaseInsensitive)==0 ) {
                        smoothMeasParam=1;
                    } else if ( QString::compare(option, "--model:satphasecenter", Qt::CaseInsensitive)==0 ) {
                        noSatAntParameter=1;
                    } else if ( QString::compare(option, "-model:recphasecenter", Qt::CaseInsensitive)==0 ) {
                        recAntParameter=1;
                    } else if ( QString::compare(option, "--model:recphasecenter", Qt::CaseInsensitive)==0 ) {
                        noRecAntParameter=1;
                        recAntParameter=0;
                    } else if ( QString::compare(option, "-filter:combtype", Qt::CaseInsensitive)==0 ) {
                        filterCombTypeParam=1;
                    } else if ( QString::compare(option, "-filter:select", Qt::CaseInsensitive)==0 || QString::compare(option, "-filter:selectlist", Qt::CaseInsensitive)==0 ) {
                        filterSelectParamProvided=1;
                    } else if ( QString::compare(option, "-filter:backward", Qt::CaseInsensitive)==0 ) {
                        BackwardFiltering=1;
                    } else if ( QString::compare(option, "-output:rinex", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:corrections", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Output Corrections", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:antenna", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbasdir", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbasavailplots", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS availability plot", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbasriskplots", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS continuity risk plot", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbasriskmarplots", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS maritime continuity risk plot", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbasriskdisc", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS discontinuity risk data", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbasionoplots", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS iono availability plot", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbashdopplots", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS HDOP plot", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbaspdopplots", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS PDOP plot", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbasgdopplots", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS GDOP plot", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:sbascombdopplots", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SBAS Combined DOP plot", &warningString,&errorString,userInput);
                        }
                        warningString += "Parameter '" + option + "' is for SBAS plots mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:file", Qt::CaseInsensitive)==0 ) {
                        numOutput++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Output", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-output:kml", Qt::CaseInsensitive)==0 ) {
                        numKML++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("KML", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-output:kml0", Qt::CaseInsensitive)==0 ) {
                        numKML0++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("KML0", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-output:sp3", Qt::CaseInsensitive)==0 ) {
                        numOutputSP3++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("SP3 output", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-output:refpos", Qt::CaseInsensitive)==0 ) {
                        numOutRefPos++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Reference Position output", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-output:stfdesa", Qt::CaseInsensitive)==0 ) {
                        numStfdESA++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Stanford-ESA output", &warningString,&errorString,userInput);
                        }
                    } else if ( QString::compare(option, "-output:stfdesaloi", Qt::CaseInsensitive)==0 ) {
                        numStfdESALOI++;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            checkConfigurationFileInputFilePaths("Stanford-ESA all geometries", &warningString,&errorString,userInput);
                        }
                    }
                }


                //Check for errors in number of files
                if (numInputOrbFiles>1) {
                    //More than one orbit file given
                    if (numNav>1) {
                        //warningString += "More than one navigation file ('-input:nav' option) is provided.\n";
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
                //Check if more than Satellite ANTEX was given
                if (numSatAnt>1) {
                    errorString += "More than one Satellite ANTEX file ('-input:ant' option) is provided.\n";
                }
                //Check if '-model:recphasecenter' was provided but no ANTEX provided
                if (recAntParameter==1 && numSatAnt==0) {
                    errorString += "Receiver antenna phase center correction enabled ('-model:recphasecenter' option), but no ANTEX provided. Provide it with option '-input:ant'.\n";
                }
                //Check if Satellite ANTEX file provided, but option for no ANTEX provided
                if (numSatAnt>0 && noSatAntParameter==1) {
                    warningString += "Satellite ANTEX file provided, but also option to not to use ANTEX is provided. Last action read will prevail.\n";
                }
                //Check if more than Receiver ANTEX was given
                if (numRecAnt>1) {
                    errorString += "More than one receiver ANTEX file ('-input:antrec' option) is provided.\n";
                }
                //Check if Receiver ANTEX file provided, but option for no ANTEX provided
                if (numRecAnt>0 && noRecAntParameter==1) {
                    warningString += "Receiver ANTEX file provided, but also option to not to use ANTEX is provided. Last action read will prevail.\n";
                }
                //Check if more than Rec. ANTEX was given
                if (numBlockAnt>1) {
                    errorString += "More than one satellite Block file ('-input:antsatblock' option) is provided.\n";
                }
                //More than one orbit file given
                if (numSBAS>1) {
                    errorString += "More than one SBAS file ('-input:sbas' or '-input:sbas1f' or '-input:sbasdfmc' option option) is provided.\n";
                }
                if( (numRTCM + numRTCM2 + numRTCM3 + numDGNSS)>1) {
                     errorString += "More than one type of DGNSS/RTCM type file provided.\n";
                }
                if (numDGNSS>1) {
                     errorString += "More than one RINEX DGNSS file ('-input:dgnss' option) is provided.\n";
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
                if (numSinex>1) {
                     errorString += "More than one SINEX file ('-input:snx' option) is provided.\n";
                }
                if (numKlob>1) {
                     errorString += "More than one Klobuchar iono navigation file ('-input:klb' option) is provided.\n";
                }
                if (numNeq>1) {
                     errorString += "More than one NeQuick iono navigation file ('-input:neq' option) is provided.\n";
                }
                if (numBDS>1) {
                     errorString += "More than one BDS iono navigation file ('-input:bds' option) is provided.\n";
                }
                if (numIONEX>1) {
                     errorString += "More than one IONEX file ('-input:inx' option) is provided.\n";
                }
                if ((numKlob+numNeq+numBDS)>1) {
                     errorString += "Iono navigation files can only be entered for one iono model.\n";
                }
                if (numSBASiono>1) {
                     errorString += "More than one SBAS iono file ('-input:sbasiono' option) is provided.\n";
                }
                if (numDCB>2) {
                     errorString += "More than two DCB files ('-input:dcb' option) are provided.\n";
                }
                if(numDCBType[0]>1) {
                    errorString += "More than two P1-C1 DCB files ('-input:dcb' option) are provided.\n";
                }
                if(numDCBType[1]>1) {
                    errorString += "More than two P1-P2 DCB files ('-input:dcb' option) are provided.\n";
                }
                if(numDCBType[2]>1) {
                    errorString += "More than two P2-C2 DCB files ('-input:dcb' option) are provided.\n";
                }
                if(numDCBType[3]>1) {
                    errorString += "More than two DCB RINEX Navigation files ('-input:dcb' option) are provided.\n";
                }
                if(numDCBType[4]>1) {
                    errorString += "More than two MGEX DCB files ('-input:dcb' option) are provided.\n";
                }
                if(numDCBType[5]>1) {
                    errorString += "More than two IONEX DCB files ('-input:dcb' option) are provided.\n";
                }
                if (numRecTypes>1) {
                     errorString += "More than one GPS receiver types file ('-input:rec' option) is provided.\n";
                }
                if (numSigmaMultipath>1) {
                     errorString += "More than one SBAS sigma multipath file ('-input:sigmpath' option) is provided.\n";
                }
                if (numRefPos>1) {
                     errorString += "More than one Reference Position file ('-input:refpos' option) is provided.\n";
                }
                if (numUserError>1) {
                     errorString += "More than one User added error file ('-input:usererror' option) is provided.\n";
                }
                if ( (numSP3>0 || numOrb>0 || numClk>0) && numSBAS>0) {
                    errorString += "Cannot determine positioning mode (PPP or SBAS) due to precise product and SBAS files provided.\n";
                }
                if ( (numSP3>0 || numOrb>0 || numClk>0) && ( numRTCM>0 || numRTCM2>0 || numRTCM3>0 || numDGNSS>0)) {
                    errorString += "Cannot determine positioning mode (PPP or DGNSS) due to precise product and DGNSS files provided.\n";
                }
                if ( numSBAS>0  &&  (numRTCM>0 || numRTCM2>0 || numRTCM3>0 || numDGNSS>0)) {
                    errorString += "Cannot determine positioning mode (SBAS or DGNSS) due to SBAS and DGNSS files provided.\n";
                }
                if ( numNav>0 && (numSP3>0 || numOrb>0 || numClk>0) ) {
                    errorString += "Cannot determine positioning mode (SPP or PPP) due to navigation file and precise product files provided.\n";
                }

                //Check observation file
                if (numObs>1) {
                    errorString += "More than one observation file ('-input:obs' option) is provided.\n";
                }
                //Check number of output files
                if (numOutput>1) {
                    errorString += "More than one output file ('-output:file' option) is provided.\n";
                }
                if (numKML>1) {
                    errorString += "More than one output KML file ('-output:kml' option) is provided.\n";
                }
                if (numKML0>1) {
                    errorString += "More than one output KML0 file ('-output:kml0' option) is provided.\n";
                }
                if (numOutputSP3>1) {
                    errorString += "More than one output SP3 file ('-output:sp3' option) is provided.\n";
                }
                if (numOutRefPos>1) {
                    errorString += "More than one output Reference position file ('-output:refpos' option) is provided.\n";
                }
                if (numStfdESA>1) {
                    errorString += "More than one output Stanford-ESA file ('-output:stfdesa' option) is provided.\n";
                }
                if (numStfdESALOI>1) {
                    errorString += "More than one output Stanford-ESA (all geometries) file ('-output:stfdesaloi' option) is provided.\n";
                }

                //Check mode is set to any value
                if(mode==-1) {
                    errorString += "No RINEX navigation, SP3, SBAS or DGNSS file provided. Cannot determine positioning mode (SPP, PPP, SBAS, DGNSS).\n";
                }

                //Check that we are not using  measurements from disabled frequencies
                if (mode>=2 && L1Avail==0) {
                    errorString += "Frequency 1 cannot be disabled in SBAS or DGNSS modes.\n";
                }
                if (mode==3 && L5Avail==0) {
                    errorString += "Frequency 5 cannot be disabled in SBAS DFMC mode.\n";
                }
                if (mode>=2  && DualFrequencyUsed==1) {
                     errorString += "Dual frequency measurements cannot be selected in the filter in SBAS or DGNSS modes.\n";
                }
                if (mode>=2 && (PhaseFreq1Used==1 ||  PhaseFreq2Used==1)) {
                    errorString += "Carrier phase measurements  cannot be selected in the filter in SBAS or DGNSS modes.\n";
                }
                if (mode>=2 && (CodeFreq2Used==1 || PhaseFreq2Used==1)  )  {
                    errorString += "Frequency 2 code or carrier phase measurements cannot be selected in the filter in SBAS or DGNSS modes.\n";
                }
                /*if (mode==2 && SmoothNoL1P==1) {
                    errorString += "Only L1P smoothing can be selected in SBAS mode.\n";
                }*/

                //Check that backward filtering is not enabled in SBAS or DGNSS modes
                if (mode>=2 && BackwardFiltering==1) {
                    errorString += "Backward filtering cannot be enabled in SBAS or DGNSS modes.\n";
                }
                if (smoothMeasParam==1 && smoothAutoParam==1) {
                    errorString += "Parameters '-pre:smoothauto' and '-pre:smoothmeas' cannot be both provided.\n";
                }

                //Check parameter '-filter:combtype' is not provided in SBAS or DGNSS modes
                if (mode>=2 && filterCombTypeParam==1) {
                    errorString += "Parameter '-filter:combtype' cannot be provided in SBAS or DGNSS modes.\n";
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
                file.seek(0); //Go back to beginning of file
                setInitialPositioningValues(); //Set initial default values in Positioning page

                //Set defaults for selected mode
                if (mode==0) {
                    on_actionSPP_triggered();
                } else if (mode==1) {
                    on_actionPPP_triggered();
                } else if (mode==2) {
                    on_actionSBAS_1F_triggered();
                } else if (mode==3) {
                    on_actionSBAS_DFMC_triggered();
                } else { //mode==4
                    on_actionDGNSS_triggered();
                }
                int indexNAV=0;
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


                    ////////////////////
                    // Multi-Threading
                    if ( QString::compare(option, "-numthreads", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<1) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 1. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>1000) {
                            warningString += "Parameter '" + option + "' has to be smaller or equal than 1000. It was skipped.\n";
                        } else {
                           MultiThread->nThreads=userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt();
                            if (MultiThread->nThreads>1) {
                                MultiThread->setThreadNumber(MultiThread->nThreads);
                            }
                        }
                    }
                    // INPUT SECTION
                    // Rover
                    else if ( QString::compare(option, "-input:obs", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            ui->lineEditRinexObs->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:nav", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {                            
                            indexNAV++;
                            if (indexNAV>1 && indexNAV<=7) this->on_pushButtonAddRinexNav_clicked();
                            //if (indexNAV==7) ui->pushButtonAddRinexNav->setEnabled(false);
                            //else if (indexNAV>1) ui->pushButtonDelRinexNav->setEnabled(true);
                            switch (indexNAV){
                                case 1: ui->lineEditRinexNav1->setText(userInput);  break;
                                case 2: ui->lineEditRinexNav2->setText(userInput);  break;
                                case 3: ui->lineEditRinexNav3->setText(userInput);  break;
                                case 4: ui->lineEditRinexNav4->setText(userInput);  break;
                                case 5: ui->lineEditRinexNav5->setText(userInput);  break;
                                case 6: ui->lineEditRinexNav6->setText(userInput);  break;
                                case 7: ui->lineEditRinexNav7->setText(userInput);  break;
                                default: break;
                            }
                        }
                    } else if ( QString::compare(option, "-input:ant", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_checkBoxSatAntex_clicked(true);
                            ui->lineEditSatAntex->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:antrec", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_checkBoxRecAntex_clicked(true);
                            ui->lineEditRecAntex->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:antsatblock", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            //Check if Satellite Block ANTEX is provided along with satellite and receiver ANTEX, as the GUI only has slot for two ANTEX files
                            if (numSatAnt==0) {
                                //No satellite ANTEX provided. Set there the ANTEX file in the satellite ANTEX slot
                                this->on_checkBoxSatAntex_clicked(true);
                                ui->lineEditSatAntex->setText(userInput);
                            } else if (numRecAnt==0) {
                                //Satellite ANTEX provided, but receiver ANTEX not provided. Set it there
                                this->on_checkBoxRecAntex_clicked(true);
                                ui->lineEditRecAntex->setText(userInput);
                            } else {
                                //Both slots are occupied. Show a warning message and skip the file
                                warningString += "The GUI only supports up to two ANTEX files. ANTEX file provided in '-input:antsatblock' option has been skipped.\n";
                            }
                        }

                    // Rover -> Orbit and Clock Source
                    } else if ( QString::compare(option, "-input:sp3", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxIonoSource_clicked(false);
                            this->on_radioButtonOrbitPrecise1file_clicked();
                            ui->lineEditPrecise1File->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:orb", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxIonoSource_clicked(false);
                            this->on_radioButtonOrbitPrecise2files_clicked();
                            ui->lineEditPrecise2Files->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:clk", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxIonoSource_clicked(false);
                            this->on_radioButtonOrbitPrecise2files_clicked();
                            ui->lineEditPreciseClk->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:navglo", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_checkBoxRinexNavFileGLO1_clicked(true);
                            this->on_checkBoxRinexNavFileGLO2_clicked(true);
                            ui->lineEditRinexNavFileGLO1->setText(userInput);
                            ui->lineEditRinexNavFileGLO2->setText(userInput);
                        }
                    }  else if ( QString::compare(option, "-input:navhealth", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_checkBoxRinexNavFileHealth1_clicked(true);
                            this->on_checkBoxRinexNavFileHealth2_clicked(true);
                            ui->lineEditRinexNavFileHealth1->setText(userInput);
                            ui->lineEditRinexNavFileHealth2->setText(userInput);
                        }
                    // A priori Receiver Position From -> SINEX
                    } else if ( QString::compare(option, "-input:snx", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_radioButtonSinex_clicked();
                            ui->lineEditSinex->setText(userInput);
                        }
                    // SBAS 1F
                    } else if ( QString::compare(option, "-input:sbas1f", Qt::CaseInsensitive)==0 || QString::compare(option, "-input:sbas", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            ui->radioButtonIonoSourceSbas->setChecked(true);
                            ui->comboBoxSbasInput->setCurrentIndex(0);
                            ui->lineEditSbas->setText(userInput);
                        }
                    // SBAS DFMC
                    } else if ( QString::compare(option, "-input:sbasdfmc", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            ui->radioButtonIonoSourceSbas->setChecked(true);
                            ui->comboBoxSbasInput->setCurrentIndex(1);
                            ui->lineEditSbas->setText(userInput);
                        }
                    // Reference Station (DGNSS)
                    } else if ( QString::compare(option, "-input:dgnss", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            ui->lineEditRefStaRinex->setText(userInput);
                            this->on_comboBoxRefStation_currentIndexChanged(0);
                            ui->comboBoxRefStation->setCurrentIndex(0);
                        }
                    } else if ( QString::compare(option, "-input:rtcm", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            ui->lineEditRefStaRtcmAuto->setText(userInput);
                            this->on_comboBoxRefStation_currentIndexChanged(1);
                            ui->comboBoxRefStation->setCurrentIndex(1);
                        }
                    } else if ( QString::compare(option, "-input:rtcm2", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            ui->lineEditRefStaRtcm2->setText(userInput);
                            this->on_comboBoxRefStation_currentIndexChanged(2);
                            ui->comboBoxRefStation->setCurrentIndex(2);
                        }
                    } else if ( QString::compare(option, "-input:rtcm3", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            ui->lineEditRefStaRtcm3->setText(userInput);
                            this->on_comboBoxRefStation_currentIndexChanged(3);
                            ui->comboBoxRefStation->setCurrentIndex(3);
                        }
                    } else if ( QString::compare(option, "-input:rtcm:initdate", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            if (userInputSingleSpace.length()<8 || userInputSingleSpace.length()>8) {
                                warningString += "RTCM input date format is incorrect. The correct format is YYYYMMDD. It was skipped.\n";
                            } else {
                                year = userInputSingleSpace.mid(0, 4).toInt();
                                month = userInputSingleSpace.mid(4, 2).toInt();
                                day = userInputSingleSpace.mid(6, 2).toInt();
                                if (year<1980) {
                                    warningString += "RTCM input date is below 1980. It was skipped.\n";
                                } else if (!(QDate::isValid(year, month, day))) {
                                    warningString += "RTCM input date is not valid. It was skipped.\n";
                                } else {
                                    date = QDate(year, month, day);
                                    ui->dateEdit1->setDate(date);
                                    ui->dateEdit2->setDate(date);
                                    ui->dateEdit3->setDate(date);
                                }
                            }
                        }
                    } else if ( QString::compare(option, "-input:rtcm:inithour", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0 || userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>24) {
                               warningString += "RTCM input hour is not valid. It was skipped.\n";
                            } else {
                                hour = QTime(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt(), 0);
                                ui->timeEdit1->setTime(hour);
                                ui->timeEdit2->setTime(hour);
                            }
                        }
                    } else if ( QString::compare(option, "-input:dcb", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            //Check what type of DCB file is
                            DCBfiletype=checkDCBFileType(userInput);
                            //We have previously checked that we have a valid DCB file
                            if (DCBfiletype==0) {
                                //P1-C1 DCB
                                this->on_groupBoxAuxFiles_clicked(true);
                                this->on_groupBoxP1C1correction_clicked(true);
                                ui->lineEditDcbFile->setText(userInput);
                            } else if (DCBfiletype==1) {
                                //P1-P2 DCB
                                this->on_groupBoxAuxFiles_clicked(true);
                                this->on_groupBoxP1P2correction_clicked(true);
                                this->on_comboBoxDcbSource_currentIndexChanged(2);
                                this->on_comboBoxDcbSourcePPP_currentIndexChanged(1);
                                ui->lineEditDcbSourceDcb->setText(userInput);
                            } else if (DCBfiletype==2) {
                                //P2-C2 DCB
                                warningString += "File '" + userInput + "' is a P2-C2 DCB file, which is not used in gLAB. File skipped.\n";
                            } else if (DCBfiletype==3) {
                                //RINEX Navigation
                                this->on_groupBoxAuxFiles_clicked(true);
                                this->on_groupBoxP1P2correction_clicked(true);
                                this->on_comboBoxDcbSource_currentIndexChanged(1);
                                this->on_comboBoxDcbSourcePPP_currentIndexChanged(0);
                                ui->lineEditDcbSourceRinexNav->setText(userInput);
                            } else if (DCBfiletype==4) {
                                //MGEX DCB
                                warningString += "File '" + userInput + "' is a MGEX DCB file, which is not used in gLAB. File skipped.\n";
                            } else if (DCBfiletype==5) {
                                //IONEX file
                                this->on_groupBoxAuxFiles_clicked(true);
                                this->on_groupBoxP1P2correction_clicked(true);
                                this->on_comboBoxDcbSource_currentIndexChanged(4);
                                this->on_comboBoxDcbSourcePPP_currentIndexChanged(3);
                                ui->lineEditDcbSourceIonex->setText(userInput);
                            }
                        }
                    } else if ( QString::compare(option, "-input:rec", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxAuxFiles_clicked(true);
                            this->on_groupBoxP1C1correction_clicked(true);
                            ui->lineEditGPSRecType->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:klb", Qt::CaseInsensitive)==0 || QString::compare(option, "-input:neq", Qt::CaseInsensitive)==0 ||
                                QString::compare(option, "-input:bei", Qt::CaseInsensitive)==0 || QString::compare(option, "-input:bds", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxIonoSource_clicked(true);
                            this->on_radioButtonIonoSourceBrdc_clicked();
                            this->on_comboBoxIonoSourceBrdc_currentIndexChanged(1);
                            ui->lineEditIonoSourceRinexNav->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:inx", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxIonoSource_clicked(true);
                            this->on_radioButtonIonoSourceIonex_clicked();
                            ui->lineEditIonoSourceIonex->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:sbasiono", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxIonoSource_clicked(true);
                            this->on_radioButtonIonoSourceSbas_clicked();
                            ui->lineEditSbas->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:usererror", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxAuxFiles_clicked(true);
                            this->on_groupBoxUserAddedError_clicked(true);
                            ui->lineEditUserAddedError->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:sigmpath", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_groupBoxAuxFiles_clicked(true);
                            this->on_groupBoxUserDefinedSbasSigmaMultipath_clicked(true);
                            ui->lineEditSigmaMultipath->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-input:refpos", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            if (RefFileFirst==2) {
                                //No '-pre:setrecpos' parameter set. Therefore the default mode will be calculateRef
                                this->on_radioButtonCalculate_clicked();
                                this->on_radioButtonCalculateEarthCentre_clicked();
                                this->on_checkBoxReferencePositionFileCalculate_clicked(true);
                                ui->lineEditReferencePositionFileCalculate->setText(RefFilePath);
                                if (RefFileInterpDegree!=-1) {
                                    ui->lineEditInterpolationDegreeRefFileCalculate->setText(QString("%1").arg(RefFileInterpDegree));
                                }
                            }
                        }
                    } else if ( QString::compare(option, "-input:con", Qt::CaseInsensitive)==0 ) {
                        //As this parameter is not used, we do not check if file has a correct path
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is not used in the GUI. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-input:cfg", Qt::CaseInsensitive)==0 ) {
                        //As this parameter is not used, we do not check if file has a correct path
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is not used in the GUI. It was skipped.\n";
                        }


                    ////////////////////
                    // PREPROCESS SECTION

                    } else if ( QString::compare(option, "-pre:setrecpos", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0 ) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonRinex_clicked();
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "SINEX", Qt::CaseInsensitive)==0 ) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonSinex_clicked();
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "calculate", Qt::CaseInsensitive)==0 ) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonCalculate_clicked();
                            this->on_radioButtonCalculateEarthCentre_clicked();
                            this->on_checkBoxReferencePositionFileCalculate_clicked(false);
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "calculateRINEX", Qt::CaseInsensitive)==0 ) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonCalculate_clicked();
                            this->on_radioButtonCalculateRinex_clicked();
                            this->on_checkBoxReferencePositionFileCalculate_clicked(false);
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "calculateUSER", Qt::CaseInsensitive)==0 ) {
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " calculateUSER' has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()==0. && QString("%1").arg(ParametersList[2]).replace(",","").toDouble()==0. && QString("%1").arg(ParametersList[3]).replace(",","").toDouble()==0.) {
                                    warningString += "Parameter '" + option + " calculateUSER' cannot have a initial position of (0,0,0). It was skipped.\n";
                                } else {
                                    this->on_radioButtonCalculate_clicked();
                                    this->on_radioButtonCalculateSpecify_clicked();
                                    this->on_radioButtonCalculateSpecifyCartesian_clicked();
                                    ui->lineEditCalculateSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditCalculateSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditCalculateSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            this->on_checkBoxReferencePositionFileCalculate_clicked(false);
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "calculateUSERGeod", Qt::CaseInsensitive)==0 ) {
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " calculateUSERGeod' has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                                    warningString += "Parameter '" + option + " calculateUSERGeod' must have a longitude range of [-180..180] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                                    warningString += "Parameter '" + option + " calculateUSERGeod' must have a latitude range of [-90..90] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                                    warningString += "Parameter '" + option + " calculateUSERGeod' must have a height value greater than -10 kilometres. It was skipped.\n";
                                } else {
                                    this->on_radioButtonCalculate_clicked();
                                    this->on_radioButtonCalculateSpecify_clicked();
                                    this->on_radioButtonCalculateSpecifyGeodetic_clicked();
                                    ui->lineEditCalculateSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditCalculateSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditCalculateSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            this->on_checkBoxReferencePositionFileCalculate_clicked(false);
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "calculateRef", Qt::CaseInsensitive)==0 ) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonCalculate_clicked();
                            this->on_radioButtonCalculateEarthCentre_clicked();
                            this->on_checkBoxReferencePositionFileCalculate_clicked(true);
                            if (RefFilePath!="") {
                                ui->lineEditReferencePositionFileCalculate->setText(RefFilePath);
                            }
                            if (RefFileInterpDegree!=-1) {
                                ui->lineEditInterpolationDegreeRefFileCalculate->setText(QString("%1").arg(RefFileInterpDegree));
                            }
                        } else if (QString::compare(ParametersList[0], "calculateRINEXRef", Qt::CaseInsensitive)==0 ) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonCalculate_clicked();
                            this->on_radioButtonCalculateRinex_clicked();
                            this->on_checkBoxReferencePositionFileCalculate_clicked(true);
                            if (RefFilePath!="") {
                                ui->lineEditReferencePositionFileCalculate->setText(RefFilePath);
                            }
                            if (RefFileInterpDegree!=-1) {
                                ui->lineEditInterpolationDegreeRefFileCalculate->setText(QString("%1").arg(RefFileInterpDegree));
                            }
                        } else if (QString::compare(ParametersList[0], "calculateUSERRef", Qt::CaseInsensitive)==0 ) {
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " calculateUSERRef' has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()==0. && QString("%1").arg(ParametersList[2]).replace(",","").toDouble()==0. && QString("%1").arg(ParametersList[3]).replace(",","").toDouble()==0.) {
                                    warningString += "Parameter '" + option + " calculateUSERRef' cannot have a initial position of (0,0,0). It was skipped.\n";
                                } else {
                                    this->on_radioButtonCalculate_clicked();
                                    this->on_radioButtonCalculateSpecify_clicked();
                                    this->on_radioButtonCalculateSpecifyCartesian_clicked();
                                    ui->lineEditCalculateSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditCalculateSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditCalculateSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            this->on_checkBoxReferencePositionFileCalculate_clicked(true);
                            if (RefFilePath!="") {
                                ui->lineEditReferencePositionFileCalculate->setText(RefFilePath);
                            }
                            if (RefFileInterpDegree!=-1) {
                                ui->lineEditInterpolationDegreeRefFileCalculate->setText(QString("%1").arg(RefFileInterpDegree));
                            }
                        } else if (QString::compare(ParametersList[0], "calculateUSERGeodRef", Qt::CaseInsensitive)==0 ) {
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " calculateUSERGeodRef' has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                                    warningString += "Parameter '" + option + " calculateUSERGeodRef' must have a longitude range of [-180..180] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                                    warningString += "Parameter '" + option + " calculateUSERGeodRef' must have a latitude range of [-90..90] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                                    warningString += "Parameter '" + option + " calculateUSERGeodRef' must have a height value greater than -10 kilometres. It was skipped.\n";
                                } else {
                                    this->on_radioButtonCalculate_clicked();
                                    this->on_radioButtonCalculateSpecify_clicked();
                                    this->on_radioButtonCalculateSpecifyGeodetic_clicked();
                                    ui->lineEditCalculateSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditCalculateSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditCalculateSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            this->on_checkBoxReferencePositionFileCalculate_clicked(true);
                            if (RefFilePath!="") {
                                ui->lineEditReferencePositionFileCalculate->setText(RefFilePath);
                            }
                            if (RefFileInterpDegree!=-1) {
                                ui->lineEditInterpolationDegreeRefFileCalculate->setText(QString("%1").arg(RefFileInterpDegree));
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMbaseline", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSbaseline", Qt::CaseInsensitive)==0 ) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonRtcm_clicked();
                            this->on_radioButtonRtcmBaseline_clicked();
                        } else if (QString::compare(ParametersList[0], "RTCMUserbaseline", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserbaseline", Qt::CaseInsensitive)==0
                                   || QString::compare(ParametersList[0], "RTCMUserCarbaseline", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserCarbaseline", Qt::CaseInsensitive)==0) {
                            if (QString::compare(ParametersList[0], "RTCMUserbaseline", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMUserbaseline";
                            } else if (QString::compare(ParametersList[0], "RTCMUserCarbaseline", Qt::CaseInsensitive)==0 ) {
                                 ParameterName="RTCMUserCarbaseline";
                            } else if (QString::compare(ParametersList[0], "DGNSSUserCarbaseline", Qt::CaseInsensitive)==0 ) {
                                 ParameterName="DGNSSUserCarbaseline";
                            } else {
                                ParameterName="DGNSSUserbaseline";
                            }
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                                radius=sqrt(pow(QString("%1").arg(ParametersList[1]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[2]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[3]).replace(",","").toDouble(),2));
                                if(radius<MIN_EARTH_RADIUS-1000.) {
                                    warningString += "Parameter '" + option + " " + ParameterName + "' cannot have a user position below Earth surface. It was skipped.\n";
                                } else {
                                    this->on_radioButtonRtcm_clicked();
                                    this->on_radioButtonRtcmUserBaseline_clicked();
                                    this->on_radioButtonRtcmRefCartesian_clicked();
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMUserGeodbaseline", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserGeodbaseline", Qt::CaseInsensitive)==0 ) {
                            if (QString::compare(ParametersList[0], "RTCMUserGeodbaseline", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMUserGeodbaseline";
                            } else {
                                ParameterName="DGNSSUserGeodbaseline";
                            }
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a longitude range of [-180..180] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a latitude range of [-90..90] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a height value greater than -10 kilometres. It was skipped.\n";
                                } else {
                                    this->on_radioButtonRtcm_clicked();
                                    this->on_radioButtonRtcmUserBaseline_clicked();
                                    this->on_radioButtonRtcmRefGeodetic_clicked();
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMRinexRover", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSRinexRover", Qt::CaseInsensitive)==0 ) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonRtcm_clicked();
                            this->on_radioButtonRtcmRinexRover_clicked();
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMUserRinexRover", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserRinexRover", Qt::CaseInsensitive)==0 ||
                                   QString::compare(ParametersList[0], "RTCMUserCarRinexRover", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserCarRinexRover", Qt::CaseInsensitive)==0) {
                            if (QString::compare(ParametersList[0], "RTCMUserRinexRover", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMUserRinexRover";
                            } else if (QString::compare(ParametersList[0], "RTCMUserCarRinexRover", Qt::CaseInsensitive)==0 ) {
                                    ParameterName="RTCMUserCarRinexRover";
                            } else  if (QString::compare(ParametersList[0], "DGNSSUserCarRinexRover", Qt::CaseInsensitive)==0 ) {
                                ParameterName="DGNSSUserCarRinexRover";
                            } else {
                                ParameterName="DGNSSUserRinexRover";
                            }
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                                radius=sqrt(pow(QString("%1").arg(ParametersList[1]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[2]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[3]).replace(",","").toDouble(),2));
                                if(radius<MIN_EARTH_RADIUS-1000.) {
                                    warningString += "Parameter '" + option + " " + ParameterName + "' cannot have a reference station position below Earth surface. It was skipped.\n";
                                } else {
                                    this->on_radioButtonRtcm_clicked();
                                    this->on_radioButtonRtcmUserRinexRover_clicked();
                                    this->on_radioButtonRtcmRefCartesian_clicked();
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMUserGeodRinexRover", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserGeodRinexRover", Qt::CaseInsensitive)==0 ) {
                            if (QString::compare(ParametersList[0], "RTCMUserGeodRinexRover", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMUserGeodRinexRover";
                            } else {
                                ParameterName="DGNSSUserGeodRinexRover";
                            }
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a longitude range of [-180..180] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a latitude range of [-90..90] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a height value greater than -10 kilometres. It was skipped.\n";
                                } else {
                                    this->on_radioButtonRtcm_clicked();
                                    this->on_radioButtonRtcmUserRinexRover_clicked();
                                    this->on_radioButtonRtcmRefGeodetic_clicked();
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMRoverUSER", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSRoverUSER", Qt::CaseInsensitive)==0 ||
                                 QString::compare(ParametersList[0], "RTCMRoverUSERCar", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSRoverUSERCar", Qt::CaseInsensitive)==0  ) {
                            if (QString::compare(ParametersList[0], "RTCMRoverUSER", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMRoverUSER";
                            } else if (QString::compare(ParametersList[0], "RTCMRoverUSERCar", Qt::CaseInsensitive)==0 ) {
                                    ParameterName="RTCMRoverUSERCar";
                            } else if (QString::compare(ParametersList[0], "DGNSSRoverUSERCar", Qt::CaseInsensitive)==0 ) {
                                    ParameterName="DGNSSRoverUSERCar";
                            } else {
                                ParameterName="DGNSSRoverUSER";
                            }
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                                radius=sqrt(pow(QString("%1").arg(ParametersList[1]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[2]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[3]).replace(",","").toDouble(),2));
                                if(radius<MIN_EARTH_RADIUS-1000.) {
                                    warningString += "Parameter '" + option + " " + ParameterName + "' cannot have a user position below Earth surface. It was skipped.\n";
                                } else {
                                    this->on_radioButtonRtcm_clicked();
                                    this->on_radioButtonRtcmSpecify_clicked();
                                    this->on_radioButtonRtcmUserDefined_clicked();
                                    this->on_radioButtonRtcmRecCartesian_clicked();
                                    ui->lineEditAprioriRecPosRtcmSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAprioriRecPosRtcmSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAprioriRecPosRtcmSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMRoverUSERGeod", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSRoverUSERGeod", Qt::CaseInsensitive)==0 ) {
                            if (QString::compare(ParametersList[0], "RTCMRoverUSERGeod", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMRoverUSERGeod";
                            } else {
                                ParameterName="DGNSSRoverUSERGeod";
                            }
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a longitude range of [-180..180] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a latitude range of [-90..90] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a height value greater than -10 kilometres. It was skipped.\n";
                                } else {
                                    this->on_radioButtonRtcm_clicked();
                                    this->on_radioButtonRtcmSpecify_clicked();
                                    this->on_radioButtonRtcmUserDefined_clicked();
                                    this->on_radioButtonRtcmRecGeodeticCoord_clicked();
                                    ui->lineEditAprioriRecPosRtcmSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAprioriRecPosRtcmSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAprioriRecPosRtcmSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMRoverUSERRef", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSRoverUSERRef", Qt::CaseInsensitive)==0 ) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonRtcm_clicked();
                            this->on_radioButtonRtcmSpecify_clicked();
                            this->on_radioButtonRtcmReferenceFile_clicked();
                            if (RefFilePath!="") {
                                ui->lineEditReferenceFileRtcm->setText(RefFilePath);
                            }
                            if (RefFileInterpDegree!=-1) {
                                ui->lineEditInterpolationDegreeRefFileRtcm->setText(QString("%1").arg(RefFileInterpDegree));
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMUserRoverRef", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserRoverRef", Qt::CaseInsensitive)==0 ||
                                  QString::compare(ParametersList[0], "RTCMUserCarRoverRef", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserCarRoverRef", Qt::CaseInsensitive)==0 ) {
                            if (QString::compare(ParametersList[0], "RTCMUserRoverRef", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMUserRoverRef";
                            } else if (QString::compare(ParametersList[0], "RTCMUserCarRoverRef", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMUserCarRoverRef";
                            } else if (QString::compare(ParametersList[0], "DGNSSUserCarRoverRef", Qt::CaseInsensitive)==0 ) {
                                ParameterName="DGNSSUserCarRoverRef";
                            } else {
                                ParameterName="DGNSSUserRoverRef";
                            }
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                                radius=sqrt(pow(QString("%1").arg(ParametersList[1]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[2]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[3]).replace(",","").toDouble(),2));
                                if(radius<MIN_EARTH_RADIUS-1000.) {
                                    warningString += "Parameter '" + option + " " + ParameterName + "' cannot have a user position below Earth surface. It was skipped.\n";
                                } else {
                                    this->on_radioButtonRtcm_clicked();
                                    this->on_radioButtonRtcmUserSpecify_clicked();
                                    this->on_radioButtonRtcmRefCartesian_clicked();
                                    this->on_radioButtonRtcmReferenceFile_clicked();
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFilePath!="") {
                                ui->lineEditReferenceFileRtcm->setText(RefFilePath);
                            }
                            if (RefFileInterpDegree!=-1) {
                                ui->lineEditInterpolationDegreeRefFileRtcm->setText(QString("%1").arg(RefFileInterpDegree));
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMUserGeodRoverRef", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "DGNSSUserGeodRoverRef", Qt::CaseInsensitive)==0 ) {
                            if (QString::compare(ParametersList[0], "RTCMUserGeodRoverRef", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMUserGeodRoverRef";
                            } else {
                                ParameterName="DGNSSUserGeodRoverRef";
                            }
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a longitude range of [-180..180] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a latitude range of [-90..90] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a height value greater than -10 kilometres. It was skipped.\n";
                                } else {
                                    this->on_radioButtonRtcm_clicked();
                                    this->on_radioButtonRtcmUserSpecify_clicked();
                                    this->on_radioButtonRtcmRefGeodetic_clicked();
                                    this->on_radioButtonRtcmReferenceFile_clicked();
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFilePath!="") {
                                ui->lineEditReferenceFileRtcm->setText(RefFilePath);
                            }
                            if (RefFileInterpDegree!=-1) {
                                ui->lineEditInterpolationDegreeRefFileRtcm->setText(QString("%1").arg(RefFileInterpDegree));
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMRefRoverUSER", Qt::CaseInsensitive)==0 ||  QString::compare(ParametersList[0], "DGNSSRefRoverUSER", Qt::CaseInsensitive)==0
                                   || QString::compare(ParametersList[0], "RTCMRefCarRoverUSERCar", Qt::CaseInsensitive)==0 ||  QString::compare(ParametersList[0], "DGNSSRefCarRoverUSERCar", Qt::CaseInsensitive)==0) {
                            if (QString::compare(ParametersList[0], "RTCMRefRoverUSER", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMRefRoverUSER";
                            } else if (QString::compare(ParametersList[0], "RTCMRefCarRoverUSERCar", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMRefCarRoverUSERCar";
                            } else if (QString::compare(ParametersList[0], "DGNSSRefCarRoverUSERCar", Qt::CaseInsensitive)==0 ) {
                                ParameterName="DGNSSRefCarRoverUSERCar";
                            } else {
                                ParameterName="DGNSSRefRoverUSER";
                            }
                            if (ParametersList.count()<7) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(7,&warningString,option,ParametersList);
                                radius=sqrt(pow(QString("%1").arg(ParametersList[1]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[2]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[3]).replace(",","").toDouble(),2));
                                if(radius<MIN_EARTH_RADIUS-1000.) {
                                    warningString += "Parameter '" + option + " " + ParameterName + "' cannot have a reference station position below Earth surface. It was skipped.\n";
                                } else {
                                    radius=sqrt(pow(QString("%1").arg(ParametersList[4]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[5]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[6]).replace(",","").toDouble(),2));
                                    if(radius<MIN_EARTH_RADIUS-1000.) {
                                        warningString += "Parameter '" + option + " " + ParameterName + "' cannot have a user position below Earth surface. It was skipped.\n";
                                    } else {
                                        this->on_radioButtonRtcm_clicked();
                                        this->on_radioButtonRtcmUserSpecify_clicked();
                                        this->on_radioButtonRtcmUserDefined_clicked();
                                        this->on_radioButtonRtcmRecCartesian_clicked();
                                        this->on_radioButtonRtcmRefCartesian_clicked();
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyX->setText(QString("%1").arg(ParametersList[4]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyY->setText(QString("%1").arg(ParametersList[5]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyZ->setText(QString("%1").arg(ParametersList[6]).replace(",",""));
                                    }
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMRefGeodRoverUSERGeod", Qt::CaseInsensitive)==0 ||  QString::compare(ParametersList[0], "DGNSSRefGeodRoverUSERGeod", Qt::CaseInsensitive)==0) {
                            if (QString::compare(ParametersList[0], "RTCMRefGeodRoverUSERGeod", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMRefGeodRoverUSERGeod";
                            } else {
                                ParameterName="DGNSSRefGeodRoverUSERGeod";
                            }
                            if (ParametersList.count()<7) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(7,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a reference longitude range of [-180..180] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a reference latitude range of [-90..90] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a reference height value greater than -10 kilometres. It was skipped.\n";
                                } else {
                                    if (QString("%1").arg(ParametersList[4]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[4]).replace(",","").toDouble()>180) {
                                        warningString += "Parameter '" + option + " " + ParameterName + " must have a rover longitude range of [-180..180] degrees. It was skipped.\n";
                                    } else if (QString("%1").arg(ParametersList[5]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[5]).replace(",","").toDouble()>90) {
                                        warningString += "Parameter '" + option + " " + ParameterName + " must have a rover latitude range of [-90..90] degrees. It was skipped.\n";
                                    } else if (QString("%1").arg(ParametersList[6]).replace(",","").toDouble()<-10000) {
                                        warningString += "Parameter '" + option + " " + ParameterName + " must have a rover height value greater than -10 kilometres. It was skipped.\n";
                                    } else {
                                        this->on_radioButtonRtcm_clicked();
                                        this->on_radioButtonRtcmUserSpecify_clicked();
                                        this->on_radioButtonRtcmUserDefined_clicked();
                                        this->on_radioButtonRtcmRecGeodeticCoord_clicked();
                                        this->on_radioButtonRtcmRefGeodetic_clicked();
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyLon->setText(QString("%1").arg(ParametersList[4]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyLat->setText(QString("%1").arg(ParametersList[5]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyHeight->setText(QString("%1").arg(ParametersList[6]).replace(",",""));
                                    }
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMRefCarRoverUSERGeod", Qt::CaseInsensitive)==0 ||  QString::compare(ParametersList[0], "DGNSSRefCarRoverUSERGeod", Qt::CaseInsensitive)==0) {
                            if (QString::compare(ParametersList[0], "RTCMRefCarRoverUSERGeod", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMRefCarRoverUSERGeod";
                            } else {
                                ParameterName="DGNSSRefCarRoverUSERGeod";
                            }
                            if (ParametersList.count()<7) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(7,&warningString,option,ParametersList);
                                radius=sqrt(pow(QString("%1").arg(ParametersList[1]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[2]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[3]).replace(",","").toDouble(),2));
                                if(radius<MIN_EARTH_RADIUS-1000.) {
                                    warningString += "Parameter '" + option + " " + ParameterName + "' cannot have a reference station position below Earth surface. It was skipped.\n";
                                } else {
                                    if (QString("%1").arg(ParametersList[4]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[4]).replace(",","").toDouble()>180) {
                                        warningString += "Parameter '" + option + " " + ParameterName + " must have a rover longitude range of [-180..180] degrees. It was skipped.\n";
                                    } else if (QString("%1").arg(ParametersList[5]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[5]).replace(",","").toDouble()>90) {
                                        warningString += "Parameter '" + option + " " + ParameterName + " must have a rover latitude range of [-90..90] degrees. It was skipped.\n";
                                    } else if (QString("%1").arg(ParametersList[6]).replace(",","").toDouble()<-10000) {
                                        warningString += "Parameter '" + option + " " + ParameterName + " must have a rover height value greater than -10 kilometres. It was skipped.\n";
                                    } else {
                                        this->on_radioButtonRtcm_clicked();
                                        this->on_radioButtonRtcmUserSpecify_clicked();
                                        this->on_radioButtonRtcmUserDefined_clicked();
                                        this->on_radioButtonRtcmRecGeodeticCoord_clicked();
                                        this->on_radioButtonRtcmRefCartesian_clicked();
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyLon->setText(QString("%1").arg(ParametersList[4]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyLat->setText(QString("%1").arg(ParametersList[5]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyHeight->setText(QString("%1").arg(ParametersList[6]).replace(",",""));
                                    }
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "RTCMRefGeodRoverUSERCar", Qt::CaseInsensitive)==0 ||  QString::compare(ParametersList[0], "DGNSSRefGeodRoverUSERCar", Qt::CaseInsensitive)==0) {
                            if (QString::compare(ParametersList[0], "RTCMRefGeodRoverUSERCar", Qt::CaseInsensitive)==0 ) {
                                ParameterName="RTCMRefGeodRoverUSERCar";
                            } else {
                                ParameterName="DGNSSRefGeodRoverUSERCar";
                            }
                            if (ParametersList.count()<7) {
                                warningString += "Parameter '" + option + " " + ParameterName + "' has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(7,&warningString,option,ParametersList);
                                if (QString("%1").arg(ParametersList[1]).replace(",","").toDouble()<-180||QString("%1").arg(ParametersList[1]).replace(",","").toDouble()>180) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a reference longitude range of [-180..180] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[2]).replace(",","").toDouble()<-90||QString("%1").arg(ParametersList[2]).replace(",","").toDouble()>90) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a reference latitude range of [-90..90] degrees. It was skipped.\n";
                                } else if (QString("%1").arg(ParametersList[3]).replace(",","").toDouble()<-10000) {
                                    warningString += "Parameter '" + option + " " + ParameterName + " must have a reference height value greater than -10 kilometres. It was skipped.\n";
                                } else {
                                    radius=sqrt(pow(QString("%1").arg(ParametersList[4]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[5]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[6]).replace(",","").toDouble(),2));
                                    if(radius<MIN_EARTH_RADIUS-1000.) {
                                        warningString += "Parameter '" + option + " " + ParameterName + "' cannot have a user position below Earth surface. It was skipped.\n";
                                    } else {
                                        this->on_radioButtonRtcm_clicked();
                                        this->on_radioButtonRtcmUserSpecify_clicked();
                                        this->on_radioButtonRtcmUserDefined_clicked();
                                        this->on_radioButtonRtcmRecCartesian_clicked();
                                        this->on_radioButtonRtcmRefGeodetic_clicked();
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                        ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyX->setText(QString("%1").arg(ParametersList[4]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyY->setText(QString("%1").arg(ParametersList[5]).replace(",",""));
                                        ui->lineEditAprioriRecPosRtcmSpecifyZ->setText(QString("%1").arg(ParametersList[6]).replace(",",""));
                                    }
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        } else if (QString::compare(ParametersList[0], "SetRef", Qt::CaseInsensitive)==0 ) {
                            //Specify Reference file
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            this->on_radioButtonSpecify_clicked();
                            this->on_radioButtonSpecifyReferenceFile_clicked();
                            if (RefFilePath!="") {
                                ui->lineEditReferenceFileSpecify->setText(RefFilePath);
                            }
                            if (RefFileInterpDegree!=-1) {
                                ui->lineEditInterpolationDegreeRefFileSpecify->setText(QString("%1").arg(RefFileInterpDegree));
                            }
                        } else if (QString::compare(ParametersList[0], "Set", Qt::CaseInsensitive)==0 ) {
                            //Specify User defined Cartesian
                            if (ParametersList.count()<4) {
                                warningString += "Parameter '" + option + "' Set has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                                radius=sqrt(pow(QString("%1").arg(ParametersList[1]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[2]).replace(",","").toDouble(),2)+pow(QString("%1").arg(ParametersList[3]).replace(",","").toDouble(),2));
                                if(radius<MIN_EARTH_RADIUS-1000.) {
                                    warningString += "Parameter '" + option + " Set' cannot have a reference position below Earth surface. It was skipped.\n";
                                } else {
                                    this->on_radioButtonSpecify_clicked();
                                    this->on_radioButtonSpecifyUserDefined_clicked();
                                    this->on_radioButtonSpecifyUserCartesian_clicked();
                                    ui->lineEditSpecifyX->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditSpecifyY->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditSpecifyZ->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
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
                                    this->on_radioButtonSpecify_clicked();
                                    this->on_radioButtonSpecifyUserDefined_clicked();
                                    this->on_radioButtonSpecifyUserGeodetic_clicked();
                                    ui->lineEditSpecifyLon->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditSpecifyLat->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                    ui->lineEditSpecifyHeight->setText(QString("%1").arg(ParametersList[3]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
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
                                    this->on_radioButtonSpecify_clicked();
                                    this->on_radioButtonSpecifyUserDefined_clicked();
                                    this->on_radioButtonSpecifyUserCartesian_clicked();
                                    ui->lineEditSpecifyX->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                                    ui->lineEditSpecifyY->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                    ui->lineEditSpecifyZ->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                                }
                            }
                            if (RefFileInterpDegree!=-1) {
                                 warningString += "Parameter '-pre:refpos:deg' has been ignored as there is no a priori reference position mode that uses a reference position file\n";
                            }
                        }
                    } else if ( QString::compare(option, "-pre:refpos:deg", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                                warningString += "Parameter '" + option + "' has an invalid interpolation degree. It was skipped.\n";
                            }
                            //Value is saved in the first reading loop and applied with '-input:refpos' or '-pre:setrecpos' parameters
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
                                     ui->dateTimeEditStartTime->setDate(date);
                                     ui->dateTimeEditStartTime->setTime(hour);
                                     this->on_checkBoxStartTime_clicked(true);
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
                                        ui->dateTimeEditStartTime->setDate(date);
                                        ui->dateTimeEditStartTime->setTime(hour);
                                        this->on_checkBoxStartTime_clicked(true);
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
                                        ui->dateTimeEditStartTime->setDate(date);
                                        ui->dateTimeEditStartTime->setTime(hour);
                                        this->on_checkBoxStartTime_clicked(true);
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
                                     ui->dateTimeEditEndTime->setDate(date);
                                     ui->dateTimeEditEndTime->setTime(hour);
                                     this->on_checkBoxEndTime_clicked(true);
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
                                        ui->dateTimeEditEndTime->setDate(date);
                                        ui->dateTimeEditEndTime->setTime(hour);
                                        this->on_checkBoxEndTime_clicked(true);
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
                                        ui->dateTimeEditEndTime->setDate(date);
                                        ui->dateTimeEditEndTime->setTime(hour);
                                        this->on_checkBoxEndTime_clicked(true);
                                    }
                                }
                            }
                        }
                    } else if ( QString::compare(option, "-pre:usererrorafter", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxAuxFiles_clicked(true);
                        this->on_groupBoxUserAddedError_clicked(true);
                        ui->checkBoxUserAddedErrorAfterPrepocessing->setChecked(true);
                    } else if ( QString::compare(option, "--pre:usererrorafter", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxUserAddedErrorAfterPrepocessing->setChecked(false);
                    } else if ( QString::compare(option, "-pre:elevation", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>90.) {
                            warningString += "Parameter '" + option + "' has to be smaller or equal than 90. It was skipped.\n";
                        } else {
                           ui->lineEditElevMask->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:eclipse", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDiscardEclipse->setChecked(true);
                    } else if ( QString::compare(option, "--pre:eclipse", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDiscardEclipse->setChecked(false);
                    } else if ( QString::compare(option, "-pre:dec", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>0. && userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<1E-4 ) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0.0001. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>86400.) {
                            warningString += "Parameter '" + option + "' has to be smaller or equal than 86400. It was skipped.\n";
                        } else {
                           this->on_checkBoxDataDecimator_clicked(true);
                           ui->lineEditDataDecimator->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:prealign", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrealignPhase->setChecked(true);
                    } else if ( QString::compare(option, "--pre:prealign", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrealignPhase->setChecked(false);
                    } else if ( QString::compare(option, "-pre:checkcodejumps", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxReceiverCodeJumps->setChecked(true);
                    } else if ( QString::compare(option, "--pre:checkcodejumps", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxReceiverCodeJumps->setChecked(false);
                    //} else if ( QString::compare(option, "-pre:flexibleC1P1", Qt::CaseInsensitive)==0 ) {  //It is also commented in gLAB
                    //} else if ( QString::compare(option, "--pre:flexibleC1P1", Qt::CaseInsensitive)==0 ) { //It is also commented in gLAB
                    } else if ( QString::compare(option, "-pre:cs:datagap", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>0. && userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<1E-4) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0.0001. It was skipped.\n";
                        } else {
                            ui->lineEditDataGap->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:lli", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxLLI->setChecked(true);
                    } else if ( QString::compare(option, "--pre:cs:lli", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxLLI->setChecked(false);
                    } else if ( QString::compare(option, "-pre:cs:ncon", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxNcon_clicked(true);
                    } else if ( QString::compare(option, "--pre:cs:ncon", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxNcon_clicked(false);
                    } else if ( QString::compare(option, "-pre:cs:ncon:min", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxNcon_clicked(true);
                            ui->lineEditNcon->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-pre:cs:li", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxLI->setChecked(true);
                    } else if ( QString::compare(option, "-pre:cs:li:freq", Qt::CaseInsensitive)==0 || QString::compare(option, "-pre:cs:li:freqlist", Qt::CaseInsensitive)==0 ) {
                        ui->checkBoxLI->setChecked(true);
                        this->on_radioButtonLIManualSelection_clicked();
                        QStringList ParamAux;
                        if (QString::compare(option, "-pre:cs:li:freqlist", Qt::CaseInsensitive)==0) {
                            ParamAux=ParametersList[0].split(",", QString::SkipEmptyParts);
                        } else {
                            ParamAux=ParametersList;
                        }
                        CSAdvancedLI->loadgLABOptions(&warningString,&ParamAux,1);
                    } else if ( QString::compare(option, "-pre:cs:li:meas", Qt::CaseInsensitive)==0 || QString::compare(option, "-pre:cs:li:measlist", Qt::CaseInsensitive)==0 ) {
                        ui->checkBoxLI->setChecked(true);
                        this->on_radioButtonLIManualSelection_clicked();
                        CSAdvancedLI->loadgLABOptions(&warningString,&ParametersList,2);
                    } else if ( QString::compare(option, "--pre:cs:li", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxLI->setChecked(false);
                    } else if ( QString::compare(option, "-pre:cs:li:min", Qt::CaseInsensitive)==0 ) { //Deprecated parameter
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is deprecated. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:li:maxjump", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxLI->setChecked(true);
                            ui->lineEditLImaxJumpThreshold->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:li:max", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxLI->setChecked(true);
                            ui->lineEditLImaxThreshold->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:li:t0", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxLI->setChecked(true);
                            ui->lineEditLItimeConstant->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:li:samples", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxLI->setChecked(true);
                            ui->lineEditLInSamples->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                        }
                    } else if ( QString::compare(option, "-pre:cs:li:nooutliers", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxLI->setChecked(true);
                        ui->checkBoxLINoOutliers->setChecked(true);
                    } else if ( QString::compare(option, "--pre:cs:li:nooutliers", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxLI->setChecked(true);
                        ui->checkBoxLINoOutliers->setChecked(false);

                    } else if ( QString::compare(option, "-pre:cs:igf", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxIGF->setChecked(true);
                    } else if ( QString::compare(option, "-pre:cs:igf:freq", Qt::CaseInsensitive)==0 || QString::compare(option, "-pre:cs:igf:freqlist", Qt::CaseInsensitive)==0 ) {
                        ui->checkBoxIGF->setChecked(true);
                        this->on_radioButtonIGFManualSelection_clicked();
                        QStringList ParamAux;
                        if (QString::compare(option, "-pre:cs:igf:freqlist", Qt::CaseInsensitive)==0) {
                            IGFFreqParamList.append(ParametersList[0].split(",", QString::SkipEmptyParts));
                        } else {
                            IGFFreqParamList.append(ParametersList);
                        }
                        //Parameters will be parsed at the end, after '-pre:cs:igf:minnoise' has been parsed (if provided)
                        IGFFreqProvided=1;
                    } else if ( QString::compare(option, "-pre:cs:igf:meas", Qt::CaseInsensitive)==0 || QString::compare(option, "-pre:cs:igf:measlist", Qt::CaseInsensitive)==0 ) {
                        ui->checkBoxIGF->setChecked(true);
                        this->on_radioButtonIGFManualSelection_clicked();
                        QStringList ParamAux;
                        if (QString::compare(option, "-pre:cs:igf:measlist", Qt::CaseInsensitive)==0) {
                            IGFMeasParamList.append(ParametersList[0].split(",", QString::SkipEmptyParts));
                        } else {
                            IGFMeasParamList.append(ParametersList);
                        }
                        //Parameters will be parsed at the end, after '-pre:cs:igf:minnoise' has been parsed (if provided)
                        IGFMeasProvided=1;
                    } else if ( QString::compare(option, "--pre:cs:igf", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxIGF->setChecked(false);
                    } else if ( QString::compare(option, "-pre:cs:igf:maxjump", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxIGF->setChecked(true);
                            ui->lineEditIGFmaxJumpThreshold->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:igf:max", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxIGF->setChecked(true);
                            ui->lineEditIGFmaxThreshold->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:igf:t0", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxIGF->setChecked(true);
                            ui->lineEditIGFtimeConstant->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:igf:samples", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxIGF->setChecked(true);
                            ui->lineEditIGFnSamples->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                        }
                    } else if ( QString::compare(option, "-pre:cs:igf:nooutliers", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxIGF->setChecked(true);
                        ui->checkBoxIGFNoOutliers->setChecked(true);
                    } else if ( QString::compare(option, "--pre:cs:igf:nooutliers", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxIGF->setChecked(true);
                        ui->checkBoxIGFNoOutliers->setChecked(false);
                    } else if ( QString::compare(option, "-pre:cs:igf:minnoise", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxIGF->setChecked(true);
                        this->on_radioButtonIGFMinimumNoise_clicked();
                    } else if ( QString::compare(option, "--pre:cs:igf:minnoise", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxIGF->setChecked(true);
                        this->on_radioButtonIGFTwoIonoFree_clicked();

                    } else if ( QString::compare(option, "-pre:cs:mw", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxMW->setChecked(true);
                    } else if ( QString::compare(option, "-pre:cs:mw:freq", Qt::CaseInsensitive)==0 || QString::compare(option, "-pre:cs:mw:freqlist", Qt::CaseInsensitive)==0 ) {
                        ui->checkBoxMW->setChecked(true);
                        this->on_radioButtonMWManualSelection_clicked();
                        QStringList ParamAux;
                        if (QString::compare(option, "-pre:cs:mw:freqlist", Qt::CaseInsensitive)==0) {
                            ParamAux=ParametersList[0].split(",", QString::SkipEmptyParts);
                        } else {
                            ParamAux=ParametersList;
                        }
                        CSAdvancedMW->loadgLABOptions(&warningString,&ParamAux,1);
                    } else if ( QString::compare(option, "-pre:cs:mw:meas", Qt::CaseInsensitive)==0 || QString::compare(option, "-pre:cs:mw:measlist", Qt::CaseInsensitive)==0 ) {
                        ui->checkBoxMW->setChecked(true);
                        this->on_radioButtonMWManualSelection_clicked();
                        QStringList ParamAux;
                        if (QString::compare(option, "-pre:cs:mw:measlist", Qt::CaseInsensitive)==0) {
                            ParamAux=ParametersList[0].split(",", QString::SkipEmptyParts);
                        } else {
                            ParamAux=ParametersList;
                        }
                        CSAdvancedMW->loadgLABOptions(&warningString,&ParamAux,2);
                    } else if ( QString::compare(option, "--pre:cs:mw", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxMW->setChecked(false);
                    } else if ( QString::compare(option, "-pre:cs:mw:min", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is deprecated. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:mw:max", Qt::CaseInsensitive)==0 ) { //Deprecated parameter
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is deprecated. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:mw:siginit", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxMW->setChecked(true);
                            ui->lineEditIntialStdDevMW->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:mw:sigmin", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxMW->setChecked(true);
                            ui->lineEditMWminStd->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:mw:timewindow", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxMW->setChecked(true);
                            ui->lineEditMWwindow->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                        }
                    } else if ( QString::compare(option, "-pre:cs:mw:kfactor", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxMW->setChecked(true);
                            ui->lineEditMWkFactor->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:mw:slope", Qt::CaseInsensitive)==0 ) { //Deprecated parameter
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is deprecated. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:mw:samples", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxMW->setChecked(true);
                            ui->lineEditMWnSample->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                        }
                    } else if ( QString::compare(option, "-pre:cs:mw:nooutliers", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxMW->setChecked(true);
                        ui->checkBoxMWNoOutliers->setChecked(true);
                    } else if ( QString::compare(option, "--pre:cs:mw:nooutliers", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxMW->setChecked(true);
                        ui->checkBoxMWNoOutliers->setChecked(false);
                    } else if ( QString::compare(option, "-pre:cs:nooutliers", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxMW->setChecked(true);
                        ui->checkBoxLI->setChecked(true);
                        ui->checkBoxIGF->setChecked(true);
                        ui->checkBoxMWNoOutliers->setChecked(true);
                        ui->checkBoxLINoOutliers->setChecked(true);
                        ui->checkBoxIGFNoOutliers->setChecked(true);
                    } else if ( QString::compare(option, "--pre:cs:nooutliers", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxMW->setChecked(true);
                        ui->checkBoxLI->setChecked(true);
                        ui->checkBoxIGF->setChecked(true);
                        ui->checkBoxMWNoOutliers->setChecked(false);
                        ui->checkBoxLINoOutliers->setChecked(false);
                        ui->checkBoxIGFNoOutliers->setChecked(false);
                    } else if ( QString::compare(option, "-pre:cs:sf", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSF->setChecked(true);
                    } else if ( QString::compare(option, "-pre:cs:sf:freq", Qt::CaseInsensitive)==0 || QString::compare(option, "-pre:cs:sf:freqlist", Qt::CaseInsensitive)==0 ) {
                        ui->checkBoxSF->setChecked(true);
                        this->on_radioButtonSFManualSelection_clicked();
                        QStringList ParamAux;
                        if (QString::compare(option, "-pre:cs:sf:freqlist", Qt::CaseInsensitive)==0) {
                            ParamAux=ParametersList[0].split(",", QString::SkipEmptyParts);
                        } else {
                            ParamAux=ParametersList;
                        }
                        CSAdvancedSF->loadgLABOptions(&warningString,&ParamAux,1);
                    } else if ( QString::compare(option, "-pre:cs:sf:meas", Qt::CaseInsensitive)==0 || QString::compare(option, "-pre:cs:sf:measlist", Qt::CaseInsensitive)==0 ) {
                        ui->checkBoxSF->setChecked(true);
                        this->on_radioButtonSFManualSelection_clicked();
                        QStringList ParamAux;
                        if (QString::compare(option, "-pre:cs:sf:measlist", Qt::CaseInsensitive)==0) {
                            ParamAux=ParametersList[0].split(",", QString::SkipEmptyParts);
                        } else {
                            ParamAux=ParametersList;
                        }
                        CSAdvancedSF->loadgLABOptions(&warningString,&ParamAux,2);
                    } else if ( QString::compare(option, "--pre:cs:sf", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSF->setChecked(false);
                    } else if ( QString::compare(option, "-pre:cs:sf:unconcheck", Qt::CaseInsensitive)==0 ) {
                        ui->checkBoxSF->setChecked(true);
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxSFConsistencyCheck_clicked(true);
                    } else if ( QString::compare(option, "--pre:cs:sf:unconcheck", Qt::CaseInsensitive)==0 ) {
                        ui->checkBoxSF->setChecked(true);
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxSFConsistencyCheck_clicked(false);
                    } else if ( QString::compare(option, "-pre:cs:sf:unconcheck:th", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxSF->setChecked(true);
                            this->on_checkBoxSFConsistencyCheck_clicked(true);
                            ui->lineEditSFConsCheckValue->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:sf:kfactor", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxSF->setChecked(true);
                            ui->lineEditSFkFactor->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:sf:slope", Qt::CaseInsensitive)==0 ) {  //Deprecate parameter
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is deprecated. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:sf:window", Qt::CaseInsensitive)==0 ) {  //Deprecated parameter
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is deprecated. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:sf:max", Qt::CaseInsensitive)==0 ) {      //Deprecated parameter
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is deprecated. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:sf:timewindow", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxSF->setChecked(true);
                            ui->lineEditSFwindow->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                        }
                    } else if ( QString::compare(option, "-pre:cs:sf:init", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxSF->setChecked(true);
                            ui->lineEditSFiniStd->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-pre:cs:sf:samples", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->checkBoxSF->setChecked(true);
                            ui->lineEditSFnSample->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                        }
                    } else if ( QString::compare(option, "-pre:cs:sf:noautofill", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "--pre:cs:sf:noautofill", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:mw:noautofill", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "--pre:cs:mw:noautofill", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:li:noautofill", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "--pre:cs:li:noautofill", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:igf:noautofill", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "--pre:cs:igf:noautofill", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:cs:noautofill", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "--pre:cs:noautofill", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:allcson", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSF->setChecked(true);
                        ui->checkBoxMW->setChecked(true);
                        ui->checkBoxLI->setChecked(true);
                        ui->checkBoxIGF->setChecked(true);
                    } else if ( QString::compare(option, "--pre:allcson", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSF->setChecked(false);
                        ui->checkBoxMW->setChecked(false);
                        ui->checkBoxLI->setChecked(false);
                        ui->checkBoxIGF->setChecked(false);
                    } else if ( QString::compare(option, "-pre:allcsoff", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSF->setChecked(false);
                        ui->checkBoxMW->setChecked(false);
                        ui->checkBoxLI->setChecked(false);
                        ui->checkBoxIGF->setChecked(false);
                    } else if ( QString::compare(option, "--pre:allcsoff", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSF->setChecked(true);
                        ui->checkBoxMW->setChecked(true);
                        ui->checkBoxLI->setChecked(true);
                        ui->checkBoxIGF->setChecked(true);
                    } else if ( QString::compare(option, "-pre:setrectype", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==0) {
                            //Unknown receiver.
                            this->on_groupBoxAuxFiles_clicked(true);
                            this->on_groupBoxP1C1correction_clicked(true);
                            this->on_radioButtonGPSReceiverTypeUserSelection_clicked();
                            ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(0);
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==1) {
                            //Cross correlated receiver
                            this->on_groupBoxAuxFiles_clicked(true);
                            this->on_groupBoxP1C1correction_clicked(true);
                            this->on_radioButtonGPSReceiverTypeUserSelection_clicked();
                            ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(1);
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==2) {
                            //No P1 receiver
                            this->on_groupBoxAuxFiles_clicked(true);
                            this->on_groupBoxP1C1correction_clicked(true);
                            this->on_radioButtonGPSReceiverTypeUserSelection_clicked();
                            ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(2);
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==3) {
                            //Nominal receiver
                            this->on_groupBoxAuxFiles_clicked(true);
                            this->on_groupBoxP1C1correction_clicked(true);
                            this->on_radioButtonGPSReceiverTypeUserSelection_clicked();
                            ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(3);
                        } else if (QString::compare(ParametersList[0], "gpsrt", Qt::CaseInsensitive)==0) {
                            //Use the same as the GPS receiver type file
                            this->on_groupBoxAuxFiles_clicked(true);
                            this->on_groupBoxP1C1correction_clicked(true);
                            this->on_radioButtonGPSReceiverTypeFile_clicked();
                        } else {
                            warningString += "Parameter '" + option + "' does not admit value '" + userInputSingleSpace.section(" ", 0,0) +"'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-pre:sat", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            loadgLABSatelliteList(option,&warningString,&ParametersList);
                        }
                    } else if ( QString::compare(option, "-pre:GEOexclude", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            PRNlist=userInputSingleSpace.section(" ", 0,0).split(",");
                            for(i=0;i<PRNlist.size();i++) {
                                PRN=QString("%1").arg(PRNlist.at(i)).section(".",0,0).toInt();
                                if (PRN<120 || PRN>210) {
                                    if (PRNlist.size()==1) {
                                        warningString += "Parameter '" + option + "' has to be equal or greater than 120 and lower or equal than 210. It was skipped.\n";
                                    } else {
                                        warningString += "PRN in position " + QString("%1").arg(i+1) + " for parameter '" + option + "' has to be equal or greater than 120 and lower or equal than 210. It was skipped.\n";
                                    }
                                } else {
                                    if (ui->checkBoxGEOexclusion->isChecked()==false) {
                                        //GEO exclusion disabled. Put GEO excluded in first position
                                        this->on_checkBoxGEOexclusion_clicked(true);
                                        this->on_comboBoxGEOexclusion_currentIndexChanged(0);
                                        ui->lineEditGEOexclusion1->setText(QString("%1").arg(PRN));
                                    } else {
                                        //GEO exclusion enabled
                                        if ( (ui->lineEditGEOexclusion1->text()!="" && QString::compare(ui->lineEditGEOexclusion1->text(),QString("%1").arg(PRN))==0) ||
                                             (ui->lineEditGEOexclusion2->text()!="" && QString::compare(ui->lineEditGEOexclusion2->text(),QString("%1").arg(PRN))==0) ||
                                             (ui->lineEditGEOexclusion3->text()!="" && QString::compare(ui->lineEditGEOexclusion3->text(),QString("%1").arg(PRN))==0) ) {
                                            //PRN already saved. Don't do nothing
                                        } else if (ui->lineEditGEOexclusion1->text()=="") {
                                            //First GEO exclusion text line is empy. Put the GEO excluded here
                                            this->on_comboBoxGEOexclusion_currentIndexChanged(0);
                                            ui->lineEditGEOexclusion1->setText(QString("%1").arg(PRN));
                                        } else  if (ui->lineEditGEOexclusion2->text()=="") {
                                            //Second GEO exclusion text line is empy. Put the GEO excluded here
                                            this->on_comboBoxGEOexclusion_currentIndexChanged(1);
                                            ui->lineEditGEOexclusion2->setText(QString("%1").arg(PRN));
                                        } else  if (ui->lineEditGEOexclusion3->text()=="") {
                                            //Third GEO exclusion text line is empy. Put the GEO excluded here
                                            this->on_comboBoxGEOexclusion_currentIndexChanged(2);
                                            ui->lineEditGEOexclusion3->setText(QString("%1").arg(PRN));
                                        } else {
                                            //Maximum of three SBAS GEO excluded with the GUI. Skip them
                                            warningString += "A maximum of 3 SBAS GEO can be excluded in the GUI with parameter '-pre:GEOexclude' (but there is no limit through command line).\n";
                                        }
                                    }
                                }
                            }
                        }
                    } else if ( QString::compare(option, "-pre:GEOsel", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if ( ( userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>2 && userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<120) ||userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>210 ) {
                            warningString += "Parameter '" + option + "' has to be with values 0, 1, 2 or equal or greater than 120 and lower or equal than 210. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==0) {
                            //Use mixed data from all GEO
                            this->on_comboBoxGEOselection_currentIndexChanged(1);
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==1) {
                            //Select first GEO read in SBAS file
                            this->on_comboBoxGEOselection_currentIndexChanged(0);
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==2) {
                            //Select GEO with maximum elevation
                            this->on_comboBoxGEOselection_currentIndexChanged(2);
                        } else {
                            //Use GEO with the given PRN
                            this->on_comboBoxGEOselection_currentIndexChanged(3);
                            ui->lineEditGEOselection->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                        }
                    } else if ( QString::compare(option, "-pre:SmoothMin", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            ui->lineEditSmoothMinSbas->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                        }
                    } else if ( QString::compare(option, "-pre:dgnss:smoothMin", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            ui->lineEditSmoothMinDgnss->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                        }
                    } else if ( QString::compare(option, "-pre:minsnr", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxSNRThresholdMin_clicked(true);
                        minSNRSelProvided=1;
                    } else if ( QString::compare(option, "--pre:minsnr", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxSNRThresholdMin_clicked(false);
                        minSNRSelProvided=0;
                    } else if ( QString::compare(option, "-pre:minsnrsel", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (ParametersList.count()==2 && (ParametersList.at(0)=="0" || ParametersList.at(0)=="+0")) {
                            //Value for all constellations, set the default value in the preprocess slot
                            minSNRSelProvided=1;
                            this->on_checkBoxSNRThresholdMin_clicked(true);
                            this->loadSNRvalue(&warningString,&ParametersList,MINSNRTYPE);
                        } else {
                            //Something else provided, load the data in the "Advanced mode" window
                            minSNRSelProvided=1;
                            this->on_checkBoxSNRThresholdMin_clicked(true);
                            this->on_checkBoxSNRMinAdvancedMode_clicked(true);
                            SnrAdvancedMinWin->loadgLABOptions(&warningString,&ParametersList);
                        }
                    } else if ( QString::compare(option, "-pre:maxsnr", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxSNRThresholdMax_clicked(true);
                        maxSNRSelProvided=1;
                    } else if ( QString::compare(option, "--pre:maxsnr", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxSNRThresholdMax_clicked(false);
                        maxSNRSelProvided=0;
                    } else if ( QString::compare(option, "-pre:maxsnrsel", Qt::CaseInsensitive)==0 ) {
                        //extraArgumentsToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (ParametersList.count()==2 && (ParametersList.at(0)=="0" || ParametersList.at(0)=="+0")) {
                            //Value for all constellations, set the default value in the preprocess slot
                            maxSNRSelProvided=1;
                            this->on_checkBoxSNRThresholdMax_clicked(true);
                            this->loadSNRvalue(&warningString,&ParametersList,MAXSNRTYPE);
                        } else {
                            maxSNRSelProvided=1;
                            this->on_checkBoxSNRThresholdMax_clicked(true);
                            this->on_checkBoxSNRMaxAdvancedMode_clicked(true);
                            SnrAdvancedMaxWin->loadgLABOptions(&warningString,&ParametersList);
                        }
                    } else if ( QString::compare(option, "-pre:availf", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GLONASSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==GalileoLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==BDSLetter
                                   ||userInputSingleSpace.section(" ", 0,0).at(0)==GEOLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==QZSSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==IRNSSLetter ) {
                            warningString += "Parameter '" + option + "' only admits GPS satellites. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GPSLetter) {
                            if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).length()==1) {
                              warningString += "Parameter '" + option + "' needs a constellation and a frequency number, but only a constellation was given. It was skipped.\n";
                            }
                        } else {
                            warningString += "Parameter '" + option + "does not have a valid constellation. It was skipped.\n";
                        }
                        warningString += "Parameter '" + option + "' is not used in the GUI. It was skipped.\n";
                    } else if ( QString::compare(option, "-pre:smooth", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==0) {
                                ui->lineEditSmoothing->setText("0");
                                this->on_radioButtonSelectionPseudorange_clicked();
                            } else {
                                if(ui->radioButtonSelectionPseudorangeCarrierPhase->isChecked()==true) {
                                    GNSSSmoothFlag=1;
                                    this->on_radioButtonSmoothing_clicked();
                                    ui->lineEditSmoothing->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                                    //Put back option of Pseudorange and carrier phase (when smoothing is enabled it is unchecked)
                                    this->on_radioButtonSelectionPseudorangeCarrierPhase_clicked();
                                } else {
                                    GNSSSmoothFlag=1;
                                    this->on_radioButtonSmoothing_clicked();
                                    ui->lineEditSmoothing->setText(QString("%1").arg(ParametersList[0]).replace(",","").section(".",0,0));
                                }
                            }
                        }
                    } else if ( QString::compare(option, "-pre:smoothauto", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_radioButtonSmoothing_clicked();
                    } else if ( QString::compare(option, "--pre:smoothauto", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_radioButtonSelectionPseudorange_clicked();
                    } else if ( QString::compare(option, "-pre:smoothMeas", Qt::CaseInsensitive)==0 ) {
                        smoothMeasParamList.append(ParametersList);
                        //Smooth meas will be parsed after the file, so it is always parsed before 'filter:select'
                    } else if ( QString::compare(option, "-pre:freqorder", Qt::CaseInsensitive)==0 ) {
                        this->on_checkBoxSetFreqMeasOrderGNSS_clicked(true);
                        FreqMeasGNSS->loadgLABOptions(&warningString,&ParametersList,1);
                    } else if ( QString::compare(option, "-pre:measorder", Qt::CaseInsensitive)==0 || QString::compare(option, "-pre:measorderlist", Qt::CaseInsensitive)==0 ) {
                        this->on_checkBoxSetFreqMeasOrderGNSS_clicked(true);
                        QStringList ParamAux;
                        if (QString::compare(option, "-pre:measorderlist", Qt::CaseInsensitive)==0) {
                            ParamAux=ParametersList[0].split(",", QString::SkipEmptyParts);
                        } else {
                            ParamAux=ParametersList;
                        }
                        FreqMeasGNSS->loadgLABOptions(&warningString,&ParamAux,2);
                    } else if ( QString::compare(option, "-pre:dgnss:excludeSmoothingConvergenceUser", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxExcludeDuringSmoothingConvergenceUser_clicked(true);
                    } else if ( QString::compare(option, "--pre:dgnss:excludeSmoothingConvergenceUser", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxExcludeDuringSmoothingConvergenceUser_clicked(false);
                    } else if ( QString::compare(option, "-pre:dgnss:excludeSmoothingConvergenceRef", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxExcludeDuringSmoothingConvergenceRef_clicked(true);
                    } else if ( QString::compare(option, "--pre:dgnss:excludeSmoothingConvergenceRef", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxExcludeDuringSmoothingConvergenceRef_clicked(false);


                    ////////////////////
                    // MODEL SECTION

                    } else if ( QString::compare(option, "-model:iono", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxIonoCorrection_clicked(false);
                        } else if (QString::compare(ParametersList[0], "Klobuchar", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxIonoCorrection_clicked(true);
                            this->on_comboBoxIonoCorrection_currentIndexChanged(0);
                        } else if (QString::compare(ParametersList[0], "NeQuick", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxIonoCorrection_clicked(true);
                            this->on_comboBoxIonoCorrection_currentIndexChanged(1);
                        } else if (QString::compare(ParametersList[0], "BeiDou", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxIonoCorrection_clicked(true);
                            this->on_comboBoxIonoCorrection_currentIndexChanged(2);
                        } else if (QString::compare(ParametersList[0], "IONEX", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxIonoCorrection_clicked(true);
                            this->on_comboBoxIonoCorrection_currentIndexChanged(3);
                        } else if (QString::compare(ParametersList[0], "SBAS", Qt::CaseInsensitive)==0) {
                            this->on_checkBoxIonoCorrection_clicked(true);
                            this->on_comboBoxIonoCorrection_currentIndexChanged(4);
                        } else if (userInputSingleSpace.section(" ", 0,0)=="FPPP") {
                            warningString += "'F-PPP' ionosphere model in parameter '" + option + "' is not used in the GUI. It was skipped.\n";
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "--model:iono", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxIonoCorrection_clicked(false);
                    } else if ( QString::compare(option, "-model:ionoRMS", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        //Only used in the core for F-PPP, but the option is not present in the help.
                        //Leave it here to avoid error message
                    } else if ( QString::compare(option, "-model:trop", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:tropo", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxTropoCorrection_clicked(true);
                    } else if ( QString::compare(option, "--model:trop", Qt::CaseInsensitive)==0 || QString::compare(option, "--model:tropo", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxTropoCorrection_clicked(false);
                    } else if ( QString::compare(option, "-model:trop:nominal", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "UNB3", Qt::CaseInsensitive)==0) {
                            this->on_comboBoxTropoCorrection_currentIndexChanged(0);
                        } else if (QString::compare(ParametersList[0], "Simple", Qt::CaseInsensitive)==0) {
                            this->on_comboBoxTropoCorrection_currentIndexChanged(1);
                        } else if (QString::compare(ParametersList[0], "TropoGal", Qt::CaseInsensitive)==0) {
                            warningString += "'TropoGal' troposphere model in parameter '" + option + "' is not available. It was skipped.\n";
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-model:trop:mapping", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "Simple", Qt::CaseInsensitive)==0) {
                            ui->comboBoxTropoCorrectionMapping->setCurrentIndex(0);
                        } else if (QString::compare(ParametersList[0], "Niell", Qt::CaseInsensitive)==0) {
                            ui->comboBoxTropoCorrectionMapping->setCurrentIndex(1);
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-model:satclocks", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSatClockOffset->setChecked(true);
                    } else if ( QString::compare(option, "--model:satclocks", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSatClockOffset->setChecked(false);
                    } else if ( QString::compare(option, "-model:relclock", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxRelativisticClock->setChecked(true);
                    } else if ( QString::compare(option, "--model:relclock", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxRelativisticClock->setChecked(false);
                    } else if ( QString::compare(option, "-model:satmovinflight", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSatMovement->setChecked(true);
                    } else if ( QString::compare(option, "--model:satmovinflight", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSatMovement->setChecked(false);
                    } else if ( QString::compare(option, "-model:earthrotinflight", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxEarthRotation->setChecked(true);
                    } else if ( QString::compare(option, "--model:earthrotinflight", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxEarthRotation->setChecked(false);
                    } else if ( QString::compare(option, "-model:satphasecenter", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxSatMassCentre_clicked(true);
                    } else if ( QString::compare(option, "--model:satphasecenter", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxSatMassCentre_clicked(false);
                    } else if ( QString::compare(option, "-model:satphasevar", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSatelliteAntennaPhaseCentreVariation->setChecked(true);
                    } else if ( QString::compare(option, "--model:satphasevar", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSatelliteAntennaPhaseCentreVariation->setChecked(false);
                    } else if ( QString::compare(option, "-model:recphasecenter", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            this->on_checkBoxAntennaPhase_clicked(false);
                        } else if (QString::compare(ParametersList[0], "ANTEX", Qt::CaseInsensitive)==0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            this->on_checkBoxAntennaPhase_clicked(true);
                            this->on_radioButtonAPCread_clicked();
                        } else {
                            if (ParametersList.count()<2) {
                                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                            } else {
                                this->on_checkBoxAntennaPhase_clicked(true);
                                this->on_radioButtonAPCspecify_clicked();
                                APCAdvanced->loadgLABOptions(&warningString,&ParametersList);
                            }
                        }
                    } else if ( QString::compare(option, "--model:recphasecenter", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxAntennaPhase_clicked(false);
                    } else if ( QString::compare(option, "-model:recphasevar", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxReceiverAntennaPhaseCentreVariation->setChecked(true);
                    } else if ( QString::compare(option, "--model:recphasevar", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxReceiverAntennaPhaseCentreVariation->setChecked(false);
                    } else if ( QString::compare(option, "-model:strictradome", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:radomestrict", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxStrictRadome->setChecked(true);
                    } else if ( QString::compare(option, "--model:strictradome", Qt::CaseInsensitive)==0 || QString::compare(option, "--model:radomestrict", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxStrictRadome->setChecked(false);
                    } else if ( QString::compare(option, "-model:arp", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            this->on_checkBoxAntennaReference_clicked(false);
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            this->on_checkBoxAntennaReference_clicked(true);
                            this->on_radioButtonARPread_clicked();
                        } else {
                            if (ParametersList.count()<3) {
                                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                            } else {
                                extraArgumentsToWarningStr(3,&warningString,option,ParametersList);
                                this->on_checkBoxAntennaReference_clicked(true);
                                this->on_radioButtonARPspecify_clicked();
                                ui->lineEditARPnorth->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
                                ui->lineEditARPeast->setText(QString("%1").arg(ParametersList[1]).replace(",",""));
                                ui->lineEditARPup->setText(QString("%1").arg(ParametersList[2]).replace(",",""));
                            }
                        }
                    } else if ( QString::compare(option, "--model:arp", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxAntennaReference_clicked(false);
                    } else if ( QString::compare(option, "-model:dcb:sf:all", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        int iDCB=-1;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            iDCB=0;
                            DCBGNSS[GPS]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            iDCB=1;
                            DCBGNSS[GPS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++){
                                DCBGNSS[iGNSS]++;
                                for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                    if (!(iGNSS==GPS && iType==0)) {
                                        //Set all except GPS P1-C1
                                        if (ComboBoxGNSSDCB[iGNSS][iType]!=nullptr) ComboBoxGNSSDCB[iGNSS][iType]->setCurrentIndex(iDCB);
                                    }
                                    if (ComboBoxGNSSISC[iGNSS][iType]!=nullptr) ComboBoxGNSSISC[iGNSS][iType]->setCurrentIndex(iDCB);
                                }
                            }
                        }
                    } else if ( QString::compare(option, "--model:dcb:sf:all", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++){
                            DCBGNSS[iGNSS]++;
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if (!(iGNSS==GPS && iType==0)) {
                                    //unset all except GPS P1-C1
                                    if (ComboBoxGNSSDCB[iGNSS][iType]!=nullptr) ComboBoxGNSSDCB[iGNSS][iType]->setCurrentIndex(0);
                                }
                                if (ComboBoxGNSSISC[iGNSS][iType]!=nullptr) ComboBoxGNSSISC[iGNSS][iType]->setCurrentIndex(0);
                            }
                        }
                    } else if ( QString::compare(option, "--model:dcb:sf:isc:all", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++){
                            DCBGNSS[iGNSS]++;
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if (ComboBoxGNSSISC[iGNSS][iType]!=nullptr) ComboBoxGNSSISC[iGNSS][iType]->setCurrentIndex(0);
                            }
                        }
                    } else if ( QString::compare(option, "-model:dcb:sf:gps:all", Qt::CaseInsensitive)==0 ) {
                        int iDCB=-1;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            iDCB=0;
                            DCBGNSS[GPS]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            iDCB=1;
                            DCBGNSS[GPS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if ( ComboBoxGNSSDCB[GPS][iType]!=nullptr && iType!=0 ) //Except GPS P1-C1
                                    ComboBoxGNSSDCB[GPS][iType]->setCurrentIndex(iDCB);
                                if (ComboBoxGNSSISC[GPS][iType]!=nullptr) ComboBoxGNSSISC[GPS][iType]->setCurrentIndex(iDCB);
                            }
                        }
                    } else if ( QString::compare(option, "--model:dcb:sf:gps:all", Qt::CaseInsensitive)==0 ) {
                        DCBGNSS[GPS]++;
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                            if (ComboBoxGNSSDCB[GPS][iType]!=nullptr && iType!=0) ComboBoxGNSSDCB[GPS][iType]->setCurrentIndex(0); //Except GPS P1-C1
                            if (ComboBoxGNSSISC[GPS][iType]!=nullptr) ComboBoxGNSSISC[GPS][iType]->setCurrentIndex(0);
                        }
                    } else if ( QString::compare(option, "-model:dcb:sf:gps:isc:all", Qt::CaseInsensitive)==0 ) {
                        int iDCB=-1;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            iDCB=0;
                            DCBGNSS[GPS]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            iDCB=1;
                            DCBGNSS[GPS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if (ComboBoxGNSSISC[GPS][iType]!=nullptr) ComboBoxGNSSISC[GPS][iType]->setCurrentIndex(iDCB);
                            }
                        }
                    } else if ( QString::compare(option, "--model:dcb:sf:gps:isc:all", Qt::CaseInsensitive)==0 ) {
                        DCBGNSS[GPS]++;
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                            if (ComboBoxGNSSISC[GPS][iType]!=nullptr) ComboBoxGNSSISC[GPS][iType]->setCurrentIndex(0);
                        }
                    } else if ( QString::compare(option.left(22), "-model:dcb:sf:gps:isc:", Qt::CaseInsensitive)==0 ) {
                        int iDCB=-1,numMatch=0;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            iDCB=0;
                            DCBGNSS[GPS]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            iDCB=1;
                            DCBGNSS[GPS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if ( QString::compare(option, CommandGNSSISC[GPS][iType], Qt::CaseInsensitive)==0 ) {
                                    ComboBoxGNSSISC[GPS][iType]->setCurrentIndex(iDCB);
                                    numMatch++;
                                }
                            }
                            if(numMatch==0) {
                                warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option.left(23), "--model:dcb:sf:gps:isc:", Qt::CaseInsensitive)==0 ) {
                        int numMatch=0;
                        QString optionModified=option;
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        DCBGNSS[GPS]++;
                        optionModified.remove(0,1);
                        for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                            if ( QString::compare(optionModified, CommandGNSSISC[GPS][iType], Qt::CaseInsensitive)==0 ) {
                                ComboBoxGNSSISC[GPS][iType]->setCurrentIndex(0);
                                numMatch++;
                            }
                        }
                        if(numMatch==0) {
                            warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                        }
                    } else if ( QString::compare(option.left(18), "-model:dcb:sf:gps:", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:dcb:p1c1", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:dcb:p1p2", Qt::CaseInsensitive)==0 ) {
                        int iDCB=-1,numMatch=0;
                        QString optionModified=option;
                        if (option=="-model:dcb:p1c1") {
                            optionModified="-model:dcb:sf:gps:p1c1";
                        } else if (option=="-model:dcb:p1p2") {
                            optionModified="-model:dcb:sf:gps:p1p2";
                        }
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0 ||
                                   QString::compare(ParametersList[0], "flexible", Qt::CaseInsensitive)==0 ) {
                            iDCB=0;
                            DCBGNSS[GPS]++;
                        } else if ( QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0
                                   || QString::compare(ParametersList[0], "strict", Qt::CaseInsensitive)==0 ) {
                            iDCB=1;
                            DCBGNSS[GPS]++;
                        } else if (QString::compare(ParametersList[0], "DCBFILE", Qt::CaseInsensitive)==0) {
                            iDCB=2;
                            DCBGNSS[GPS]++;
                        } else if (QString::compare(ParametersList[0], "IONEX", Qt::CaseInsensitive)==0) {
                            iDCB=3;
                            DCBGNSS[GPS]++;
                        } else if (QString::compare(ParametersList[0], "FPPP", Qt::CaseInsensitive)==0) {
                            iDCB=4;
                            DCBGNSS[GPS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if ( QString::compare(optionModified, CommandGNSSDCB[GPS][iType], Qt::CaseInsensitive)==0 ){
                                    numMatch++;
                                    if ( (iType==0 && QString::compare(ParametersList[0], "strict", Qt::CaseInsensitive)!=0 && QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)!=0 && QString::compare(ParametersList[0], "flexible", Qt::CaseInsensitive)!=0 ) ||
                                         (iType>0 && (QString::compare(ParametersList[0], "strict", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "flexible", Qt::CaseInsensitive)==0) ) ||
                                         (iType>1 && (QString::compare(ParametersList[0], "DCBFILE", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "IONEX", Qt::CaseInsensitive)==0 || QString::compare(ParametersList[0], "FPPP", Qt::CaseInsensitive)==0 ) )  ){
                                        warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                                    } else {
                                        ComboBoxGNSSDCB[GPS][iType]->setCurrentIndex(iDCB);
                                    }
                                }
                            }
                            if(numMatch==0) {
                                warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option.left(19), "--model:dcb:sf:gps:", Qt::CaseInsensitive)==0 || QString::compare(option, "--model:dcb:p1c1", Qt::CaseInsensitive)==0 || QString::compare(option, "--model:dcb:p1p2", Qt::CaseInsensitive)==0 ) {
                        int numMatch=0;
                        QString optionModified=option;
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        DCBGNSS[GPS]++;
                        optionModified.remove(0,1);
                        if (optionModified=="-model:dcb:p1c1") {
                            optionModified="-model:dcb:sf:gps:p1c1";
                        } else if (optionModified=="-model:dcb:p1p2") {
                            optionModified="-model:dcb:sf:gps:p1p2";
                        }
                        for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                            if ( QString::compare(optionModified, CommandGNSSDCB[GPS][iType], Qt::CaseInsensitive)==0 ) {
                                ComboBoxGNSSDCB[GPS][iType]->setCurrentIndex(0);
                                numMatch++;
                            }
                        }
                        if(numMatch==0) {
                            warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-model:dcb:sf:glo:all", Qt::CaseInsensitive)==0 ) {
                        int iDCB=-1;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            iDCB=0;
                            DCBGNSS[GLONASS]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            iDCB=1;
                            DCBGNSS[GLONASS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if (ComboBoxGNSSDCB[GLONASS][iType]!=nullptr) ComboBoxGNSSDCB[GLONASS][iType]->setCurrentIndex(iDCB);
                            }
                        }
                    } else if ( QString::compare(option, "--model:dcb:sf:glo:all", Qt::CaseInsensitive)==0 ) {
                        DCBGNSS[GLONASS]++;
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                            if (ComboBoxGNSSDCB[GLONASS][iType]!=nullptr) ComboBoxGNSSDCB[GLONASS][iType]->setCurrentIndex(0);
                            if (ComboBoxGNSSISC[GLONASS][iType]!=nullptr) ComboBoxGNSSISC[GLONASS][iType]->setCurrentIndex(0);
                        }
                    } else if ( QString::compare(option.left(18), "-model:dcb:sf:glo:", Qt::CaseInsensitive)==0 ) {
                        int iDCB=-1,numMatch=0;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            iDCB=0;
                            DCBGNSS[GLONASS]++;
                        } else if ( QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0
                                   || QString::compare(ParametersList[0], "strict", Qt::CaseInsensitive)==0 ) {
                            iDCB=1;
                            DCBGNSS[GLONASS]++;
                        } else if (QString::compare(ParametersList[0], "DCBFILE", Qt::CaseInsensitive)==0) {
                            iDCB=2;
                            DCBGNSS[GLONASS]++;
                        } else if (QString::compare(ParametersList[0], "IONEX", Qt::CaseInsensitive)==0) {
                            iDCB=3;
                            DCBGNSS[GLONASS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if ( QString::compare(option, CommandGNSSDCB[GLONASS][iType], Qt::CaseInsensitive)==0 ){
                                    numMatch++;
                                    ComboBoxGNSSDCB[GLONASS][iType]->setCurrentIndex(iDCB);
                                }
                            }
                            if(numMatch==0) {
                                warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option.left(19), "--model:dcb:sf:glo:", Qt::CaseInsensitive)==0 ) {
                        int numMatch=0;
                        QString optionModified=option;
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        DCBGNSS[GLONASS]++;
                        optionModified.remove(0,1);
                        for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                            if ( QString::compare(optionModified, CommandGNSSDCB[GLONASS][iType], Qt::CaseInsensitive)==0 ) {
                                ComboBoxGNSSDCB[GLONASS][iType]->setCurrentIndex(0);
                                numMatch++;
                            }
                        }
                        if(numMatch==0) {
                            warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-model:dcb:sf:gal:all", Qt::CaseInsensitive)==0 ) {
                        int iDCB=-1;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            iDCB=0;
                            DCBGNSS[Galileo]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            iDCB=1;
                            DCBGNSS[Galileo]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if (ComboBoxGNSSDCB[Galileo][iType]!=nullptr) ComboBoxGNSSDCB[Galileo][iType]->setCurrentIndex(iDCB);
                            }
                        }
                    } else if ( QString::compare(option, "--model:dcb:sf:gal:all", Qt::CaseInsensitive)==0 ) {
                        DCBGNSS[Galileo]++;
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                            if (ComboBoxGNSSDCB[Galileo][iType]!=nullptr) ComboBoxGNSSDCB[Galileo][iType]->setCurrentIndex(0);
                            if (ComboBoxGNSSISC[Galileo][iType]!=nullptr) ComboBoxGNSSISC[Galileo][iType]->setCurrentIndex(0);
                        }
                    } else if ( QString::compare(option.left(18), "-model:dcb:sf:gal:", Qt::CaseInsensitive)==0 ) {
                        int iDCB=-1,numMatch=0;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            iDCB=0;
                            DCBGNSS[Galileo]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            iDCB=1;
                            DCBGNSS[Galileo]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if ( QString::compare(option, CommandGNSSDCB[Galileo][iType], Qt::CaseInsensitive)==0 ){
                                    numMatch++;
                                    ComboBoxGNSSDCB[Galileo][iType]->setCurrentIndex(iDCB);
                                }
                            }
                            if(numMatch==0) {
                                warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option.left(19), "--model:dcb:sf:gal:", Qt::CaseInsensitive)==0 ) {
                        int numMatch=0;
                        QString optionModified=option;
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        DCBGNSS[Galileo]++;
                        optionModified.remove(0,1);
                        for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                            if ( QString::compare(optionModified, CommandGNSSDCB[Galileo][iType], Qt::CaseInsensitive)==0 ) {
                                ComboBoxGNSSDCB[Galileo][iType]->setCurrentIndex(0);
                                numMatch++;
                            }
                        }
                        if(numMatch==0) {
                            warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-model:dcb:sf:bds:all", Qt::CaseInsensitive)==0 ) {
                        int iDCB=-1;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            iDCB=0;
                            DCBGNSS[BDS]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            iDCB=1;
                            DCBGNSS[BDS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if (ComboBoxGNSSDCB[BDS][iType]!=nullptr) ComboBoxGNSSDCB[BDS][iType]->setCurrentIndex(iDCB);
                            }
                        }
                    } else if ( QString::compare(option, "--model:dcb:sf:bds:all", Qt::CaseInsensitive)==0 ) {
                        DCBGNSS[BDS]++;
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                            if (ComboBoxGNSSDCB[BDS][iType]!=nullptr) ComboBoxGNSSDCB[BDS][iType]->setCurrentIndex(0);
                            if (ComboBoxGNSSISC[BDS][iType]!=nullptr) ComboBoxGNSSISC[BDS][iType]->setCurrentIndex(0);
                        }
                    } else if ( QString::compare(option.left(18), "-model:dcb:sf:bds:", Qt::CaseInsensitive)==0 ) {
                        int iDCB=-1,numMatch=0;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            iDCB=0;
                            DCBGNSS[BDS]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            iDCB=1;
                            DCBGNSS[BDS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if ( QString::compare(option, CommandGNSSDCB[BDS][iType], Qt::CaseInsensitive)==0 ){
                                    numMatch++;
                                    ComboBoxGNSSDCB[BDS][iType]->setCurrentIndex(iDCB);
                                }
                            }
                            if(numMatch==0) {
                                warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option.left(19), "--model:dcb:sf:bds:", Qt::CaseInsensitive)==0 ) {
                        int numMatch=0;
                        QString optionModified=option;
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        DCBGNSS[BDS]++;
                        optionModified.remove(0,1);
                        for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                            if ( QString::compare(optionModified, CommandGNSSDCB[BDS][iType], Qt::CaseInsensitive)==0 ) {
                                ComboBoxGNSSDCB[BDS][iType]->setCurrentIndex(0);
                                numMatch++;
                            }
                        }
                        if(numMatch==0) {
                            warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-model:dcb:sf:qzs:all", Qt::CaseInsensitive)==0 ) {
                        int iDCB=-1;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            iDCB=0;
                            DCBGNSS[QZSS]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            iDCB=1;
                            DCBGNSS[QZSS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if (ComboBoxGNSSDCB[QZSS][iType]!=nullptr) ComboBoxGNSSDCB[QZSS][iType]->setCurrentIndex(iDCB);
                                if (ComboBoxGNSSISC[QZSS][iType]!=nullptr) ComboBoxGNSSISC[QZSS][iType]->setCurrentIndex(iDCB);
                            }
                        }
                    } else if ( QString::compare(option, "--model:dcb:sf:qzs:all", Qt::CaseInsensitive)==0 ) {
                        DCBGNSS[QZSS]++;
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                            if (ComboBoxGNSSDCB[QZSS][iType]!=nullptr) ComboBoxGNSSDCB[QZSS][iType]->setCurrentIndex(0);
                            if (ComboBoxGNSSISC[QZSS][iType]!=nullptr) ComboBoxGNSSISC[QZSS][iType]->setCurrentIndex(0);
                        }
                    } else if ( QString::compare(option, "-model:dcb:sf:qzs:isc:all", Qt::CaseInsensitive)==0 ) {
                        int iDCB=-1;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            iDCB=0;
                            DCBGNSS[QZSS]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            iDCB=1;
                            DCBGNSS[QZSS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if (ComboBoxGNSSISC[QZSS][iType]!=nullptr) ComboBoxGNSSISC[QZSS][iType]->setCurrentIndex(iDCB);
                            }
                        }
                    } else if ( QString::compare(option, "--model:dcb:sf:qzs:isc:all", Qt::CaseInsensitive)==0 ) {
                        DCBGNSS[QZSS]++;
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                            if (ComboBoxGNSSISC[QZSS][iType]!=nullptr) ComboBoxGNSSISC[QZSS][iType]->setCurrentIndex(0);
                        }
                    } else if ( QString::compare(option.left(22), "-model:dcb:sf:qzs:isc:", Qt::CaseInsensitive)==0 ) {
                        int iDCB=-1,numMatch=0;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            iDCB=0;
                            DCBGNSS[QZSS]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            iDCB=1;
                            DCBGNSS[QZSS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if ( QString::compare(option, CommandGNSSISC[QZSS][iType], Qt::CaseInsensitive)==0 ) {
                                    numMatch++;
                                    ComboBoxGNSSISC[QZSS][iType]->setCurrentIndex(iDCB);
                                }
                            }
                            if(numMatch==0) {
                                warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option.left(23), "--model:dcb:sf:qzs:isc:", Qt::CaseInsensitive)==0 ) {
                        int numMatch=0;
                        QString optionModified=option;
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        DCBGNSS[QZSS]++;
                        optionModified.remove(0,1);
                        for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                            if ( QString::compare(optionModified, CommandGNSSISC[QZSS][iType], Qt::CaseInsensitive)==0 ) {
                                ComboBoxGNSSISC[QZSS][iType]->setCurrentIndex(0);
                                numMatch++;
                            }
                        }
                        if(numMatch==0) {
                            warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                        }
                    } else if ( QString::compare(option.left(18), "-model:dcb:sf:qzs:", Qt::CaseInsensitive)==0 ) {
                        int iDCB=-1,numMatch=0;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            iDCB=0;
                            DCBGNSS[QZSS]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            iDCB=1;
                            DCBGNSS[QZSS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if ( QString::compare(option, CommandGNSSDCB[QZSS][iType], Qt::CaseInsensitive)==0 ) {
                                    numMatch++;
                                    ComboBoxGNSSDCB[QZSS][iType]->setCurrentIndex(iDCB);
                                }
                            }
                            if(numMatch==0) {
                                warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option.left(19), "--model:dcb:sf:qzs:", Qt::CaseInsensitive)==0 ) {
                        int numMatch=0;
                        QString optionModified=option;
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        DCBGNSS[QZSS]++;
                        optionModified.remove(0,1);
                        for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                            if ( QString::compare(optionModified, CommandGNSSDCB[QZSS][iType], Qt::CaseInsensitive)==0 ) {
                                ComboBoxGNSSDCB[QZSS][iType]->setCurrentIndex(0);
                                numMatch++;
                            }
                        }
                        if(numMatch==0) {
                            warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-model:dcb:sf:irn:all", Qt::CaseInsensitive)==0 ) {
                        int iDCB=-1;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            iDCB=0;
                            DCBGNSS[IRNSS]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            iDCB=1;
                            DCBGNSS[IRNSS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if (ComboBoxGNSSDCB[IRNSS][iType]!=nullptr) ComboBoxGNSSDCB[IRNSS][iType]->setCurrentIndex(iDCB);
                            }
                        }
                    } else if ( QString::compare(option, "--model:dcb:sf:irn:all", Qt::CaseInsensitive)==0 ) {
                        DCBGNSS[IRNSS]++;
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                            if (ComboBoxGNSSDCB[IRNSS][iType]!=nullptr) ComboBoxGNSSDCB[IRNSS][iType]->setCurrentIndex(0);
                            if (ComboBoxGNSSISC[IRNSS][iType]!=nullptr) ComboBoxGNSSISC[IRNSS][iType]->setCurrentIndex(0);
                        }
                    } else if ( QString::compare(option.left(18), "-model:dcb:sf:irn:", Qt::CaseInsensitive)==0 ) {
                        int iDCB=-1,numMatch=0;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            iDCB=0;
                            DCBGNSS[IRNSS]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            iDCB=1;
                            DCBGNSS[IRNSS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                                if ( QString::compare(option, CommandGNSSDCB[IRNSS][iType], Qt::CaseInsensitive)==0 ){
                                    numMatch++;
                                    ComboBoxGNSSDCB[IRNSS][iType]->setCurrentIndex(iDCB);
                                }
                            }
                            if(numMatch==0) {
                                warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option.left(19), "--model:dcb:sf:irn:", Qt::CaseInsensitive)==0 ) {
                        int numMatch=0;
                        QString optionModified=option;
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        DCBGNSS[IRNSS]++;
                        optionModified.remove(0,1);
                        for (int iType=0; iType<MAX_GNSS_FREQ; iType++){
                            if ( QString::compare(optionModified, CommandGNSSDCB[IRNSS][iType], Qt::CaseInsensitive)==0 ) {
                                ComboBoxGNSSDCB[IRNSS][iType]->setCurrentIndex(0);
                                numMatch++;
                            }
                        }
                        if(numMatch==0) {
                            warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-model:dcb:df:all", Qt::CaseInsensitive)==0 ) {
                        int iDCB=-1;
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            iDCB=0;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            iDCB=1;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (iDCB>=0) {
                            DCBGNSS[GPS]++;
                            DCBGNSS[BDS]++;
                            DCBGNSS[QZSS]++;
                            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                            ui->comboBoxDCBdfGPS->setCurrentIndex(iDCB);
                            ui->comboBoxDCBdfBDS->setCurrentIndex(iDCB);
                            ui->comboBoxDCBdfQZSS->setCurrentIndex(iDCB);
                        }
                    } else if ( QString::compare(option, "--model:dcb:df:all", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        DCBGNSS[GPS]++;
                        DCBGNSS[BDS]++;
                        DCBGNSS[QZSS]++;
                        ui->comboBoxDCBdfGPS->setCurrentIndex(0);
                        ui->comboBoxDCBdfBDS->setCurrentIndex(0);
                        ui->comboBoxDCBdfQZSS->setCurrentIndex(0);
                    } else if ( QString::compare(option, "-model:dcb:df:gps", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            ui->comboBoxDCBdfGPS->setCurrentIndex(0);
                            DCBGNSS[GPS]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            ui->comboBoxDCBdfGPS->setCurrentIndex(1);
                            DCBGNSS[GPS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                    } else if ( QString::compare(option, "-model:dcb:df:bds", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            ui->comboBoxDCBdfBDS->setCurrentIndex(0);
                            DCBGNSS[BDS]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            ui->comboBoxDCBdfBDS->setCurrentIndex(1);
                            DCBGNSS[BDS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                    } else if ( QString::compare(option, "-model:dcb:df:qzs", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:dcb:df:qzss", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "no", Qt::CaseInsensitive)==0) {
                            ui->comboBoxDCBdfQZSS->setCurrentIndex(0);
                            DCBGNSS[QZSS]++;
                        } else if (QString::compare(ParametersList[0], "RINEX", Qt::CaseInsensitive)==0) {
                            ui->comboBoxDCBdfQZSS->setCurrentIndex(1);
                            DCBGNSS[QZSS]++;
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                    } else if ( option.left(12).contains("-model:brdc:", Qt::CaseInsensitive)==true ){
                        this->command_2_UserNavMessageTypes(&option,&ParametersList[0],&warningString,1);
                    } else if ( QString::compare(option, "-model:brdcpreferagetime", Qt::CaseInsensitive)==0 ){
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                           ui->lineEditNavFreshTime->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:windup", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxWindUp->setChecked(true);
                    } else if ( QString::compare(option, "--model:windup", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxWindUp->setChecked(false);
                    } else if ( QString::compare(option, "-model:solidtides", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxTides->setChecked(true);
                    } else if ( QString::compare(option, "--model:solidtides", Qt::CaseInsensitive)==0 ) {
                        ui->checkBoxTides->setChecked(false);
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                    } else if ( QString::compare(option, "-model:relpath", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxRelativisticPath->setChecked(true);
                    } else if ( QString::compare(option, "--model:relpath", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxRelativisticPath->setChecked(false);
                    } else if ( QString::compare(option, "-model:orbit:deg", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:orb:deg", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                           ui->lineEditOrbitInterpolationDegree->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:clock:deg", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:clk:deg", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                           ui->lineEditClockInterpolationDegree->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:orbmaxgaps", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                           ui->lineEditOrbitConsecutiveGaps->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "--model:orbmaxgaps", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->lineEditOrbitConsecutiveGaps->setText("0");
                    } else if ( QString::compare(option, "-model:clkmaxgaps", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                           ui->lineEditClockConsecutiveGaps->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "--model:clkmaxgaps", Qt::CaseInsensitive)==0 ) {
                         extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                         ui->lineEditClockConsecutiveGaps->setText("0");
                    } else if ( QString::compare(option, "-model:orbtotmaxgaps", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                           ui->lineEditOrbitMaxGaps->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "--model:orbtotmaxgaps", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->lineEditOrbitMaxGaps->setText("0");
                    } else if ( QString::compare(option, "-model:clktotmaxgaps", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                           ui->lineEditClockMaxGaps->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "--model:clktotmaxgaps", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->lineEditClockMaxGaps->setText("0");
                    } else if ( QString::compare(option, "-model:orbprevsample", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxConcatenedPreciseFiles_clicked(true);
                        ui->radioButtonOrbitCurrentDay->setChecked(true);
                    } else if ( QString::compare(option, "--model:orbprevsample", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->radioButtonOrbitNextDay->setChecked(true);
                    } else if ( QString::compare(option, "-model:clkprevsample", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->radioButtonClockCurrentDay->setChecked(true);
                    } else if ( QString::compare(option, "--model:clkprevsample", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->radioButtonClockNextDay->setChecked(true);
                    } else if ( QString::compare(option, "-model:satellitehealth", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:sathealth", Qt::CaseInsensitive)==0  ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxDiscardUnhealthy_clicked(true);
                    } else if ( QString::compare(option, "--model:satellitehealth", Qt::CaseInsensitive)==0 || QString::compare(option, "--model:sathealth", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxDiscardUnhealthy_clicked(false);
                    } else if ( QString::compare(option, "-model:allowmarginal", Qt::CaseInsensitive)==0   ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxDiscardMarginal_clicked(false);
                    } else if ( QString::compare(option, "--model:allowmarginal", Qt::CaseInsensitive)==0   ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxDiscardMarginal_clicked(true);
                    } else if ( QString::compare(option, "-model:skipunhealthymarg", Qt::CaseInsensitive)==0   ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "--model:skipunhealthymarg", Qt::CaseInsensitive)==0   ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-model:skipunhealthy", Qt::CaseInsensitive)==0   ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "--model:skipunhealthy", Qt::CaseInsensitive)==0   ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-model:brdctranstime", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxCheckBroadcastTransmissionTime->setChecked(true);
                    } else if ( QString::compare(option, "--model:brdctranstime", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxCheckBroadcastTransmissionTime->setChecked(false);
                    } else if ( QString::compare(option, "-model:maxurabrdc", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                             warningString += "Value for parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-model:globrdcintstep", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                             warningString += "Value for parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-model:brdcpreferagetime", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toInt()<=0) {
                             warningString += "Value for parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditNavFreshTime->setText(userInputSingleSpace.section(" ", 0,0).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-model:allfilemeas", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "--model:allfilemeas", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "--model:skipunhealthy", Qt::CaseInsensitive)==0   ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-model:sbasmaritime", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_comboBoxSBASApplication_currentIndexChanged(1);
                    } else if ( QString::compare(option, "-model:alarmmsgtype2", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:usealarmmsgcorr", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        ui->checkBoxParseAlarmSBAS1F->setChecked(true);
                        ui->checkBoxParseAlarmSBASDFMC->setChecked(true);
                    } else if ( QString::compare(option, "--model:alarmmsgtype2", Qt::CaseInsensitive)==0 || QString::compare(option, "--model:usealarmmsgcorr", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxParseAlarmSBAS1F->setChecked(false);
                        ui->checkBoxParseAlarmSBASDFMC->setChecked(false);
                    } else if ( QString::compare(option, "-model:ignoretype0", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        ui->checkBoxIgnoreAllAlarm->setChecked(true);
                    } else if ( QString::compare(option, "--model:ignoretype0", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxIgnoreAllAlarm->setChecked(false);
                    } else if ( QString::compare(option, "-model:SBASmode", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "PA", Qt::CaseInsensitive)==0) {
                            this->on_comboBoxSbasNavigationMode_currentIndexChanged(0);
                        } else if (QString::compare(ParametersList[0], "NPA", Qt::CaseInsensitive)==0) {
                            this->on_comboBoxSbasNavigationMode_currentIndexChanged(1);
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-model:maintainGEO", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        ui->checkBoxMaintainCurrentGEOafterGEOswitch->setChecked(true);
                    } else if ( QString::compare(option, "--model:maintainGEO", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxMaintainCurrentGEOafterGEOswitch->setChecked(false);
                    } else if ( QString::compare(option, "-model:GEOswitch", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxGEOswitching_clicked(true);
                    } else if ( QString::compare(option, "--model:GEOswitch", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxGEOswitching_clicked(false);
                    } else if ( QString::compare(option, "-model:selectbestgeo", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxSelectBestGEO_clicked(true);
                    } else if ( QString::compare(option, "--model:selectbestgeo", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxSelectBestGEO_clicked(false);
                    } else if ( QString::compare(option, "-model:SBASmodeswitch", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxNavigationModeSwitching_clicked(true);
                    } else if ( QString::compare(option, "--model:SBASmodeswitch", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxNavigationModeSwitching_clicked(false);
                    } else if ( QString::compare(option, "-model:GEOfallback", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        ui->checkBoxReturnToInitialGEO->setChecked(true);
                    } else if ( QString::compare(option, "--model:GEOfallback", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxReturnToInitialGEO->setChecked(false);
                    } else if ( QString::compare(option, "-model:GEOacqtime", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:GEOadqtime", Qt::CaseInsensitive)==0  ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSbasAdvancedOptions_clicked(true);
                            ui->lineEditGEOadquisitionTime->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:switchtime", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSbasAdvancedOptions_clicked(true);
                            ui->lineEditSwitchinCooltime->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:SBAStmoutPA", Qt::CaseInsensitive)==0 ) {
                        if (mode!=2) continue;
                        extraArgumentsToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            readSBASM1FTandTimeout(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt(), userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt(), 0,option, &warningString);
                        }
                    } else if ( QString::compare(option, "-model:SBAStmoutNPA", Qt::CaseInsensitive)==0 ) {
                        if (mode!=2) continue;
                        extraArgumentsToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            readSBASM1FTandTimeout(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt(), userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt(), 1,option, &warningString);
                        }
                    } else if ( QString::compare(option, "-model:SBAStmout", Qt::CaseInsensitive)==0 ) {
                        if (mode!=2) continue;
                        extraArgumentsToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            readSBASM1FTandTimeout(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt(), userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt(), 2,option, &warningString);
                        }
                    } else if ( QString::compare(option, "-model:SBAStmoutFCPA", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>9999999) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be below 9999999, or 9999999 for no timeout. It was skipped.\n";
                        } else {
                            this->on_groupBoxMessageTimeOuts_clicked(true);
                            ui->lineEditFastCorrectionsPA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:SBAStmoutFCNPA", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>9999999) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be below 9999999, or 9999999 for no timeout. It was skipped.\n";
                        } else {
                            this->on_groupBoxMessageTimeOuts_clicked(true);
                            ui->lineEditFastCorrectionsNPA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:SBAStmoutFC", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>9999999) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be below 9999999, or 9999999 for no timeout. It was skipped.\n";
                        } else {
                            this->on_groupBoxMessageTimeOuts_clicked(true);
                            ui->lineEditFastCorrectionsPA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                            ui->lineEditFastCorrectionsNPA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:SBAStmoutRRCPA", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>9999999) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be below 9999999, or 9999999 for no timeout. It was skipped.\n";
                        } else {
                            this->on_groupBoxMessageTimeOuts_clicked(true);
                            ui->lineEditRRCcorrectionsPA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:SBAStmoutRRCNPA", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>9999999) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be below 9999999, or 9999999 for no timeout. It was skipped.\n";
                        } else {
                            this->on_groupBoxMessageTimeOuts_clicked(true);
                            ui->lineEditRRCcorrectionsNPA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:SBAStmoutRRC", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>9999999) {
                            warningString += "SBAS message timeout in parameter '" + option + "' must be below 9999999, or 9999999 for no timeout. It was skipped.\n";
                        } else {
                            this->on_groupBoxMessageTimeOuts_clicked(true);
                            ui->lineEditRRCcorrectionsPA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                            ui->lineEditRRCcorrectionsNPA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-model:mixedGEO", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxAllowMixedGEOdata->setChecked(true);
                    } else if ( QString::compare(option, "--model:mixedGEO", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxAllowMixedGEOdata->setChecked(false);
                    } else if ( QString::compare(option, "-model:initcoordNPA", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        ui->checkBoxAllowKlobucharIono->setChecked(true);
                    } else if ( QString::compare(option, "--model:initcoordNPA", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxAllowKlobucharIono->setChecked(false);
                    } else if ( QString::compare(option, "-model:udreithreshold", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<1||userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>13) {
                             warningString += "Value for parameter '" + option + "' have to be between 1 and 13. It was skipped.\n";
                        } else {
                            this->on_checkBoxDiscardUDREIThreshold_clicked(true);
                            ui->comboBoxUDREIThresholds->setCurrentIndex(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()-1);
                        }
                    } else if ( QString::compare(option, "--model:udreithreshold", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxDiscardUDREIThreshold_clicked(false);
                    } else if ( QString::compare(option, "-model:sigfltnomt10offset", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0) {
                             warningString += "Value for parameter '" + option + "' have equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditOffsetFastCorrNoMT10->setText(userInputSingleSpace.section(" ", 0,0).replace(",",""));
                        }
                    } else if ( QString::compare(option, "-model:SBASreceiver", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==0) {
                            this->on_comboBoxAirboneReceiverType_currentIndexChanged(0);
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==1) {
                            this->on_comboBoxAirboneReceiverType_currentIndexChanged(1);
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()==2) {
                            this->on_comboBoxAirboneReceiverType_currentIndexChanged(2);
                        } else {
                            warningString += "SBAS receiver type '" + userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0) + "' in parameter '" + option + "' is not valid. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-model:sigmpath", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(3,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (ParametersList.count()==2) {
                            if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0. || userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()<0.) {
                                warningString += "Values for parameter '" + option + "' have to be greater or equal than 0. It was skipped.\n";
                            } else {
                                this->on_comboBoxAirboneReceiverType_currentIndexChanged(0);
                                this->on_checkBoxUserDefinedReceiverSigmaMultipath_clicked(true);
                                ui->lineEditSbasSigmaMultipathA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                                ui->lineEditSbasSigmaMultipathB->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                            }
                        } else {
                            if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0. || userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()<0.) {
                                warningString += "First two values for parameter '" + option + "' have to be greater or equal than 0. It was skipped.\n";
                            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                                warningString += "Third value for parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                            } else {
                                this->on_comboBoxAirboneReceiverType_currentIndexChanged(0);
                                this->on_checkBoxUserDefinedReceiverSigmaMultipath_clicked(true);
                                ui->lineEditSbasSigmaMultipathA->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                                ui->lineEditSbasSigmaMultipathB->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                                ui->lineEditSbasSigmaMultipathC->setText(QString("%1").arg(userInputSingleSpace.section(" ", 2,2).replace(",","")));
                            }
                        }
                    } else if ( QString::compare(option, "-model:sigdiv", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_comboBoxAirboneReceiverType_currentIndexChanged(0);
                            this->on_checkBoxUserDefinedReceiverSigmaDivergence_clicked(true);
                            ui->lineEditSbasSigmaDivergence->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-model:signoise", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_comboBoxAirboneReceiverType_currentIndexChanged(0);
                            this->on_checkBoxUserDefinedReceiverSigmaNoise_clicked(true);
                            ui->lineEditSbasSigmaNoise->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-model:khpa", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSbasAdvancedOptions_clicked(true);
                            this->on_groupBoxSBASKFactor_clicked(true);
                            ui->lineEditkhpa->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-model:kvpa", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSbasAdvancedOptions_clicked(true);
                            this->on_groupBoxSBASKFactor_clicked(true);
                            ui->lineEditkvpa->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-model:khnpa", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSbasAdvancedOptions_clicked(true);
                            this->on_groupBoxSBASKFactor_clicked(true);
                            ui->lineEditkhnpa->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-model:kvnpa", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSbasAdvancedOptions_clicked(true);
                            this->on_groupBoxSBASKFactor_clicked(true);
                            ui->lineEditkvnpa->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-model:nofastcor", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificCorrections_clicked(true);
                        ui->checkBoxDisableFastCorrections->setChecked(true);
                    } else if ( QString::compare(option, "--model:nofastcor", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableFastCorrections->setChecked(false);
                    } else if ( QString::compare(option, "-model:norrccor", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificCorrections_clicked(true);
                        ui->checkBoxDisableRRCcorrections->setChecked(true);
                    } else if ( QString::compare(option, "--model:norrccor", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableRRCcorrections->setChecked(false);
                    } else if ( QString::compare(option, "-model:noslowcor", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificCorrections_clicked(true);
                        ui->checkBoxDisableSlowCorrections->setChecked(true);
                    } else if ( QString::compare(option, "--model:noslowcor", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableSlowCorrections->setChecked(false);
                    } else if ( QString::compare(option, "-model:noionocor", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificCorrections_clicked(true);
                        ui->checkBoxDisableIonosphereCorrections->setChecked(true);
                    } else if ( QString::compare(option, "--model:noionocor", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableIonosphereCorrections->setChecked(false);
                    } else if ( QString::compare(option, "-model:nofastsigma", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificSigmas_clicked(true);
                        ui->checkBoxDisableFastCorrectionsSigma->setChecked(true);
                    } else if ( QString::compare(option, "--model:nofastsigma", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableFastCorrectionsSigma->setChecked(false);
                    } else if ( QString::compare(option, "-model:nofastdeg", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificSigmas_clicked(true);
                        ui->checkBoxDisableFastCorrectionsSigma->setChecked(true);
                    } else if ( QString::compare(option, "--model:nofastdeg", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableFastCorrectionsSigma->setChecked(false);
                    } else if ( QString::compare(option, "-model:norrcsigma", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificSigmas_clicked(true);
                        ui->checkBoxDisableRRCsigma->setChecked(true);
                    } else if ( QString::compare(option, "--model:norrcsigma", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableRRCsigma->setChecked(false);
                    } else if ( QString::compare(option, "-model:noslowsigma", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificSigmas_clicked(true);
                        ui->checkBoxDisableSlowCorrectionsSigma->setChecked(true);
                    } else if ( QString::compare(option, "--model:noslowsigma", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableSlowCorrectionsSigma->setChecked(false);
                    } else if ( QString::compare(option, "-model:noionosigma", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificSigmas_clicked(true);
                        ui->checkBoxDisableIonosphereSigma->setChecked(true);
                    } else if ( QString::compare(option, "--model:noionosigma", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableIonosphereSigma->setChecked(false);
                    } else if ( QString::compare(option, "-model:notroposigma", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificSigmas_clicked(true);
                        ui->checkBoxDisableTroposphereSigma->setChecked(true);
                    } else if ( QString::compare(option, "--model:notroposigma", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableTroposphereSigma->setChecked(false);
                    } else if ( QString::compare(option, "-model:noenroutesigma", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSpecificSigmas_clicked(true);
                        ui->checkBoxDisableEnRoute->setChecked(true);
                    } else if ( QString::compare(option, "--model:noenroutesigma", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableEnRoute->setChecked(false);
                    } else if ( QString::compare(option, "-model:nomt10", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSBASMessages_clicked(true);
                        ui->checkBoxDisableMT10->setChecked(true);
                    } else if ( QString::compare(option, "--model:nomt10", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableMT10->setChecked(false);
                    } else if ( QString::compare(option, "-model:nomt2728", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:nodeltaudre", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxSbasAdvancedOptions_clicked(true);
                        this->on_groupBoxDisableSBASMessages_clicked(true);
                        ui->checkBoxDisableMT2728->setChecked(true);
                    } else if ( QString::compare(option, "--model:nomt2728", Qt::CaseInsensitive)==0 || QString::compare(option, "--model:nodeltaudre", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDisableMT2728->setChecked(false);
                    }

                    //New SBAS option
                    else if (QString::compare(option, "-model:sbassignalflighttime", Qt::CaseInsensitive)==0){
                        if ( ParametersList[0].toDouble()<0. || ParametersList[0].toDouble()>0.3 ){
                            warningString += "Values for parameter '" + option + "' have to be greater or equal than 0. and less than 0.3 It was skipped.\n";
                        } else {
                            ui->lineEditSBASSignalFlightTime->setText(ParametersList[0]);
                        }
                    }
                    //MODEL for SBAS DFMC
                    else if ( QString::compare(option, "-model:SBAStmoutPA", Qt::CaseInsensitive)==0 ) {
                        if (mode!=3) continue;
                        extraArgumentsToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            readSBASDFMCMTandTimeout(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt(), userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt(), 0,option, &warningString);
                        }
                    } else if ( QString::compare(option, "-model:SBAStmoutNPA", Qt::CaseInsensitive)==0 ) {
                        if (mode!=3) continue;
                        extraArgumentsToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            readSBASDFMCMTandTimeout(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt(), userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt(), 1,option, &warningString);
                        }
                    } else if ( QString::compare(option, "-model:SBAStmout", Qt::CaseInsensitive)==0 ) {
                        if (mode!=3) continue;
                        extraArgumentsToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            readSBASDFMCMTandTimeout(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt(), userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt(), 2,option, &warningString);
                        }
                    }
                    else if ( QString::compare(option, "-model:sbasdfmc:mt37v04", Qt::CaseInsensitive)==0 ) {
                        if (mode!=3) continue;
                        this->on_checkBoxDecodeMT37_clicked(true);
                    } else if ( QString::compare(option, "-model:sbasdfmc:mt3940v04", Qt::CaseInsensitive)==0 ) {
                        if (mode!=3) continue;
                        this->on_checkBoxDecodeMT3940_clicked(true);
                    } else if ( QString::compare(option, "-model:sbasdfmc:mt42v07", Qt::CaseInsensitive)==0 ) {
                        if (mode!=3) continue;
                        this->on_checkBoxDecodeMT42_clicked(true);
                    } else if ( QString::compare(option, "-model:sbasdfmc:mt47v04", Qt::CaseInsensitive)==0 ) {
                        if (mode!=3) continue;
                        this->on_checkBoxDecodeMT47_clicked(true);
                    } else if ( QString::compare(option, "-model:sbasdfmc:cer", Qt::CaseInsensitive)==0 ){
                        if (mode!=3) continue;
                        if ( ParametersList[0].toDouble()<0. ){
                            warningString += "Values for parameter '" + option + "' have to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSetOBADParameters_clicked(true);
                            this->on_checkBoxSetCerOBADParameterMT37_clicked(true);
                            ui->lineEditCerOBADParameterMT37->setText(ParametersList[0]);
                        }
                    } else if ( QString::compare(option, "-model:sbasdfmc:ccovariance", Qt::CaseInsensitive)==0 ){
                        if (mode!=3) continue;
                        if ( ParametersList[0].toDouble()<0. ){
                            warningString += "Values for parameter '" + option + "' have to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSetOBADParameters_clicked(true);
                            this->on_checkBoxSetCcovarianceOBADParameterMT37_clicked(true);
                            ui->lineEditCcovarianceOBADParameterMT37->setText(ParametersList[0]);
                        }
                    } else if ( QString::compare(option, "-model:sbasdfmc:icorr", Qt::CaseInsensitive)==0 ){
                        if (mode!=3) continue;
                        if (ParametersList[0].mid(0,1)=="0") {
                            QStringList valueList = ParametersList[0].split("-", QString::SkipEmptyParts);
                            if (valueList.count()!=2) continue;
                            bool OBADOK=false;
                            valueList[1].toDouble(&OBADOK);
                            if (!OBADOK) warningString += "Values for parameter '" + option + "' have to be a double value. It was skipped.\n";
                            else {
                                this->on_checkBoxSetIcorrOBADParameterMT37_clicked(true);
                                this->on_checkBoxSetIcorrOBADParameterMT37Advanced_clicked(false);
                                ui->lineEditSetIcorrOBADParameterMT37->setText(valueList[1]);
                            }
                        }
                        else {
                            this->on_checkBoxSetIcorrOBADParameterMT37_clicked(true);
                            this->on_checkBoxSetIcorrOBADParameterMT37Advanced_clicked(true);
                            SBASOBADSet->loadgLABOptions(0,&warningString,&ParametersList);
                        }
                    } else if ( QString::compare(option, "-model:sbasdfmc:ccorr", Qt::CaseInsensitive)==0 ){
                        if (mode!=3) continue;
                        if (ParametersList[0].mid(0,1)=="0") {
                            QStringList valueList = ParametersList[0].split("-", QString::SkipEmptyParts);
                            if (valueList.count()!=2) continue;
                            bool OBADOK=false;
                            valueList[1].toDouble(&OBADOK);
                            if (!OBADOK) warningString += "Values for parameter '" + option + "' have to be a double value. It was skipped.\n";
                            else {
                                this->on_checkBoxSetCcorrOBADParameterMT37_clicked(true);
                                this->on_checkBoxSetCcorrOBADParameterMT37Advanced_clicked(false);
                                ui->lineEditSetCcorrOBADParameterMT37->setText(valueList[1]);
                            }
                        }
                        else {
                            this->on_checkBoxSetCcorrOBADParameterMT37_clicked(true);
                            this->on_checkBoxSetCcorrOBADParameterMT37Advanced_clicked(true);
                            SBASOBADSet->loadgLABOptions(1,&warningString,&ParametersList);
                        }
                    } else if ( QString::compare(option, "-model:sbasdfmc:rcorr", Qt::CaseInsensitive)==0 ){
                        if (mode!=3) continue;
                        if (ParametersList[0].mid(0,1)=="0") {
                            QStringList valueList = ParametersList[0].split("-", QString::SkipEmptyParts);
                            if (valueList.count()!=2) continue;
                            bool OBADOK=false;
                            valueList[1].toDouble(&OBADOK);
                            if (!OBADOK) warningString += "Values for parameter '" + option + "' have to be a double value. It was skipped.\n";
                            else {
                                this->on_checkBoxSetRcorrOBADParameterMT37_clicked(true);
                                this->on_checkBoxSetRcorrOBADParameterMT37Advanced_clicked(false);
                                ui->lineEditSetRcorrOBADParameterMT37->setText(valueList[1]);
                            }
                        }
                        else {
                            this->on_checkBoxSetRcorrOBADParameterMT37_clicked(true);
                            this->on_checkBoxSetRcorrOBADParameterMT37Advanced_clicked(true);
                            SBASOBADSet->loadgLABOptions(2,&warningString,&ParametersList);
                        }
                    } else if ( QString::compare(option, "-model:sbasdfmc:dfrei", Qt::CaseInsensitive)==0 ){
                        if (mode!=3) continue;
                        bool dfrei=false;
                        int dfreiValue;
                        dfreiValue=ParametersList[0].toInt(&dfrei);
                        if ( !dfrei || dfreiValue<0 || dfreiValue>14 ) {
                            warningString += "First value for parameter '" + option + "' has to be selected from 0 to 14. It was skipped.\n";
                        }
                        else if ( ParametersList[1].toDouble()<0. ) {
                            warningString += "Second value for parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSetDFREICorrections_clicked(true);
                            this->on_checkBoxSetOneDFREISigmaConversionValue_clicked(true);
                            ui->comboBoxSetDFREIN->setCurrentIndex(dfreiValue);
                            ui->lineEditSetDFREIValue->setText(ParametersList[1]);
                        }
                    } else if ( QString::compare(option, "-model:sbasdfmc:dfreilist", Qt::CaseInsensitive)==0 ){
                        if (mode!=3) continue;
                        QStringList valueList = ParametersList[0].split(",", QString::SkipEmptyParts);
                        if (valueList.count()!=15) {
                            warningString += "Number of values for parameter '" + option + "' have to be 14. It was skipped.\n";
                        } else {
                            int iDfrei;
                            for ( iDfrei=0; iDfrei<15; iDfrei++ ){
                                if ( valueList[iDfrei].toDouble()<0. ) {
                                    warningString += "Values for parameter '" + option + "' have to be greater or equal than 0. It was skipped.\n";
                                    break;
                                }
                            }
                            if (iDfrei>=15){
                                this->on_groupBoxSetDFREICorrections_clicked(true);
                                this->on_checkBoxSetAllDFREIConversionValues_clicked(true);
                                ui->lineEditSetValueDFREI0->setText(valueList[0]);
                                ui->lineEditSetValueDFREI1->setText(valueList[1]);
                                ui->lineEditSetValueDFREI2->setText(valueList[2]);
                                ui->lineEditSetValueDFREI3->setText(valueList[3]);
                                ui->lineEditSetValueDFREI4->setText(valueList[4]);
                                ui->lineEditSetValueDFREI5->setText(valueList[5]);
                                ui->lineEditSetValueDFREI6->setText(valueList[6]);
                                ui->lineEditSetValueDFREI7->setText(valueList[7]);
                                ui->lineEditSetValueDFREI8->setText(valueList[8]);
                                ui->lineEditSetValueDFREI9->setText(valueList[9]);
                                ui->lineEditSetValueDFREI10->setText(valueList[10]);
                                ui->lineEditSetValueDFREI11->setText(valueList[11]);
                                ui->lineEditSetValueDFREI12->setText(valueList[12]);
                                ui->lineEditSetValueDFREI13->setText(valueList[13]);
                                ui->lineEditSetValueDFREI14->setText(valueList[14]);
                            }
                        }
                    } else if ( QString::compare(option, "-model:sbasdfmc:deltarcorr", Qt::CaseInsensitive)==0 ){
                        if (mode!=3) continue;
                        if ( ParametersList[0].toDouble()<0. ){
                            warningString += "Values for parameter '" + option + "' have to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSetSepcificSigmas_clicked(true);
                            this->on_checkBoxSetDeltaRcorrParameter_clicked(true);
                            ui->lineEditSetDeltaRcorrParameter->setText(ParametersList[0]);
                        }
                    } else if ( QString::compare(option, "-model:sbasdfmc:deltadfre", Qt::CaseInsensitive)==0 ){
                        if (mode!=3) continue;
                        if ( ParametersList[0].toDouble()<0. ){
                            warningString += "Values for parameter '" + option + "' have to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSetSepcificSigmas_clicked(true);
                            this->on_checkBoxSetDeltaDFREFactor_clicked(true);
                            ui->lineEditSetDeltaDFREFactor->setText(ParametersList[0]);
                        }
                    } else if ( QString::compare(option, "-model:sbasdfmc:sigmauire", Qt::CaseInsensitive)==0 ){
                        if (mode!=3) continue;
                        if ( ParametersList[0].toDouble()<0. ){
                            warningString += "Values for parameter '" + option + "' have to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSetSepcificSigmas_clicked(true);
                            this->on_checkBoxSetUIRESigmaValue_clicked(true);
                            ui->lineEditSetUIRESigmaValue->setText(ParametersList[0]);
                        }
                    } else if ( QString::compare(option, "-model:sbasdfmc:sigmatropo", Qt::CaseInsensitive)==0 ){
                        if (mode!=3) continue;
                        if ( ParametersList[0].toDouble()<0. ){
                            warningString += "Values for parameter '" + option + "' have to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_groupBoxSetSepcificSigmas_clicked(true);
                            this->on_checkBoxSetTroposphericSigma_clicked(true);
                            ui->lineEditSetTroposphericSigma->setText(ParametersList[0]);
                        }
                    } else if ( QString::compare(option, "-model:sbasdfmc:sigmpathfactor", Qt::CaseInsensitive)==0 ){
                        if (ui->comboBoxAirboneReceiverType->currentIndex() != 0) continue;
                        if (mode!=3) continue;
                        if ( ParametersList[0].toDouble()<0. ){
                            warningString += "Values for parameter '" + option + "' have to be greater or equal than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxSigmaMultiPathFactor_clicked(true);
                            ui->lineEditSigmaMultiPathFactor->setText(ParametersList[0]);
                        }
                    } else if ( QString::compare(option, "-model:sbasdfmc:anymeas", Qt::CaseInsensitive)==0 ) {
                        if (mode!=3) continue;
                        ui->checkBoxAllowUseNoneMOPSMeas->setChecked(true);
                    } else if ( QString::compare(option, "-model:sbasdfmc:austestbed", Qt::CaseInsensitive)==0 ) {
                        if (mode!=3) continue;
                        this->on_groupBoxShowOldMessages_clicked(true);
                        this->on_checkBoxProcessAustralianTestBedMessages_clicked(true);
                    }

                    //model for DGNSS
                    else if ( QString::compare(option, "-model:dgnss:sigmainflation", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDgnssInflateSigma->setChecked(true);
                    } else if ( QString::compare(option, "--model:dgnss:sigmainflation", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxDgnssInflateSigma->setChecked(false);
                    } else if ( QString::compare(option, "-model:dgnss:maxage", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            ui->lineEditMaxAgeDgnss->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-model:dgnss:maxcorrval", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
                        } else {
                            ui->lineEditMaxValueDGNSS->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }


                    ////////////////////
                    // FILTER SECTION

                    } else if ( QString::compare(option, "-filter:nav", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "static", Qt::CaseInsensitive)==0) {
                           this->on_radioButtonStatic_clicked();
                        } else if (QString::compare(ParametersList[0], "kinematic", Qt::CaseInsensitive)==0) {
                            this->on_radioButtonKinematic_clicked();
                        } else if (QString::compare(ParametersList[0], "randomwalk", Qt::CaseInsensitive)==0) {
                            this->on_radioButtonRandomwalkCoordinates_clicked();
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                        if (CoordPhi!="") {
                            ui->lineEditPhiCoordinates->setText(CoordPhi);
                        }
                        if (CoordQ!="") {
                            ui->lineEditQcoordinates->setText(CoordQ);
                        }
                        if (CoordP0!="") {
                            ui->lineEditPoCoordinates->setText(CoordP0);
                        }
                    } else if ( QString::compare(option, "-filter:combtype", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "auto", Qt::CaseInsensitive)==0) {
                            //Do nothing, as is default mode
                        } else if (QString::compare(ParametersList[0], "singlefreq", Qt::CaseInsensitive)==0) {
                            if (filterSelectParamProvided==0) {
                                //Only set the radiobutton if '-filter:select' is not provided
                                this->on_radioButtonSingleFreq_clicked();
                            }
                        } else if (QString::compare(ParametersList[0], "dualfreq", Qt::CaseInsensitive)==0) {
                            if (filterSelectParamProvided==0) {
                                //Only set the radiobutton if '-filter:select' is not provided
                                this->on_radioButtonDualFreq_clicked();
                            }
                        } else if (QString::compare(ParametersList[0], "graphic", Qt::CaseInsensitive)==0) {
                            if (filterSelectParamProvided==0) {
                                //Only set the radiobutton if '-filter:select' is not provided
                                this->on_radioButtonSingleFreq_clicked();
                                this->on_radioButtonSelectionGraphic_clicked();
                            }
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:meas", Qt::CaseInsensitive)==0 || QString::compare(option, "-filter:meastype", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if(mode>=2) {
                            //In SBAS or DGNSS mode this has no effect
                            warningString += "Parameter '" + option + "' has no effect in SBAS or DGNSS modes. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "pseudorange", Qt::CaseInsensitive)==0) {
                           this->on_radioButtonSelectionPseudorange_clicked();
                        } else if (QString::compare(ParametersList[0], "carrierphase", Qt::CaseInsensitive)==0) {
                            this->on_radioButtonSelectionPseudorangeCarrierPhase_clicked();
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:select", Qt::CaseInsensitive)==0 || QString::compare(option, "-filter:selectlist", Qt::CaseInsensitive)==0) {
                        QStringList ParamAux;
                        if (QString::compare(option, "-filter:selectlist", Qt::CaseInsensitive)==0) {
                            filterSelectParam.append(ParametersList[0].split(",", QString::SkipEmptyParts));
                        } else {
                            filterSelectParam.append(ParametersList);
                        }
                        //Filter select option will be processed after reading all parameters, so it is processed after '-pre:smoothmeas'
                    } else if ( QString::compare(option, "-filter:trop", Qt::CaseInsensitive)==0 || QString::compare(option, "-filter:tropo", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxEstimateTroposphere_clicked(true);
                    } else if ( QString::compare(option, "--filter:trop", Qt::CaseInsensitive)==0 || QString::compare(option, "--filter:tropo", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxEstimateTroposphere_clicked(false);


                    } else if ( QString::compare(option, "-filter:noambiguities", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "--filter:noambiguities", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";

                    } else if ( QString::compare(option, "-filter:gloifb", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "--filter:gloifb", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-filter:recwindup", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "--filter:recwindup", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-filter:refclkonlyorder", Qt::CaseInsensitive)==0 || QString::compare(option, "-filter:refclkorder", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        QString userRefGNSSClockOrder[MAX_GNSS]={""};
                        int nRefGNSSClockCount;
                        int clkOnlyOrder=0;
                        if (QString::compare(option, "-filter:refclkonlyorder", Qt::CaseInsensitive)==0) clkOnlyOrder=1;
                        this->command_2_UserRefGNSSClock(&ParametersList[0],userRefGNSSClockOrder,&nRefGNSSClockCount, &warningString);
                        if (nRefGNSSClockCount>0) {
                            //Valid constellation found
                            this->on_groupBoxRefGNSSClock_clicked(true);
                            for (int i=1; i<=MAX_GNSS; i++){
                                ui->tableWidgetRefGNSSClock->item(1,i)->setText(userRefGNSSClockOrder[i-1]);
                                if ( i-1 < nRefGNSSClockCount ) ui->tableWidgetRefGNSSClock->item(1,i)->setBackground(gnssSelected);
                                else if (clkOnlyOrder==1) {
                                    ui->tableWidgetRefGNSSClock->item(1,i)->setBackground(gnssUnSelected);
                                } else {
                                    ui->tableWidgetRefGNSSClock->item(1,i)->setBackground(gnssSelected);
                                }
                            }
                        }
                    } else if ( QString::compare(option, "-filter:iscb", Qt::CaseInsensitive)==0 ){
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        }
                        else {
                            this->on_groupBoxISCB_clicked(true);
                            int unitsUsed[3]={0}; // 0-> metres 1 -> seconds 2 -> nanoseconds
                            QString ISCBUnit="m";
                            QString ISCBOption[3]={""};
                            for (int iscbi=0; iscbi<ParametersList.count(); iscbi++) {
                                ISCBOption[0]=ParametersList[iscbi].section('-',0,0);
                                ISCBOption[1]=ParametersList[iscbi].section('-',1,1);
                                ISCBOption[2]=ParametersList[iscbi].section('-',2,-1);
                                double ISCBValue=0;
                                bool ISCBOK;
                                int iRef=0,iDes=0;
                                //Reference GNSS iRef=row index of TableISCB
                                for (iRef=0; iRef<MAX_GNSS; iRef++){
                                    if (ISCBOption[0].mid(0,1)==ISCBGNSSOrder[iRef]) break;
                                }
                                //Destination GNSS iDes=column index of TableISCB
                                for (iDes=0; iDes<MAX_GNSS; iDes++){
                                    if (ISCBOption[0].mid(1,1)==ISCBGNSSOrder[iDes]) break;
                                }
                                //continue if Reference & Destination are regonized and Constellations are selected
                                if ( iRef<MAX_GNSS && iDes<MAX_GNSS && iRef!=iDes ){
                                    iRef++; iDes++;
                                    QTableWidgetItem *pitem=ui->tableWidgetISCB->item(iRef,iDes);
                                    //check if Constellations are selected
                                    if (pitem->background().color().name()!=RedColor) {
                                        //Type: GR-1.11
                                        if ( ISCBOption[2].size()<=0 ){
                                            ISCBValue=ISCBOption[1].toDouble(&ISCBOK);
                                            if (ISCBOK) {
                                                pitem->setText(QString::number(ISCBValue));
                                                ui->comboBoxISCBUnit->setCurrentIndex(0);
                                                ISCBUnit="m";
                                                unitsUsed[0]=1;
                                            }
                                        }
                                        //Type: GR-m-1.11 or GR-s-1.11e-1
                                        else if ( ISCBOption[2].size()>0 && ( ISCBOption[1]=="m" || ISCBOption[1]=="s" || ISCBOption[1]=="n" ) ){
                                            ISCBValue=ISCBOption[2].toDouble(&ISCBOK);
                                            if (ISCBOK) {
                                                pitem->setText(QString::number(ISCBValue));
                                                if (ISCBOption[1]=="m"){
                                                    ui->comboBoxISCBUnit->setCurrentIndex(0);
                                                    ISCBUnit="m";
                                                    unitsUsed[0]=1;
                                                } else if (ISCBOption[1]=="s"){
                                                    ui->comboBoxISCBUnit->setCurrentIndex(1);
                                                    ISCBUnit="s";
                                                    unitsUsed[1]=1;
                                                } else if (ISCBOption[1]=="n"){
                                                    ui->comboBoxISCBUnit->setCurrentIndex(2);
                                                    ISCBUnit="n";
                                                    unitsUsed[2]=1;
                                                }
                                            }
                                        }
                                        //Type: GR-1.11e-1
                                        else if ( ISCBOption[2].size()>0 && ISCBOption[1]!="m" && ISCBOption[1]!="s" && ISCBOption[1]!="n" ){
                                            QString ISCBStr = ISCBOption[1] + "-" + ISCBOption[2];
                                            ISCBValue=ISCBStr.toDouble(&ISCBOK);
                                            if (ISCBOK) {
                                                pitem->setText(QString::number(ISCBValue));
                                                ui->comboBoxISCBUnit->setCurrentIndex(0);
                                                ISCBUnit="m";
                                                unitsUsed[0]=1;
                                            }
                                        }
                                    }
                                }
                            }
                            if ( (unitsUsed[0]+unitsUsed[1]+unitsUsed[2])>1) {
                                QString unitsUsedStr = "";
                                if (unitsUsed[0]>0) {
                                    unitsUsedStr += "m,";
                                }
                                if (unitsUsed[1]>0) {
                                    unitsUsedStr += "s,";
                                }
                                if (unitsUsed[2]>0) {
                                    unitsUsedStr += "ns,";
                                }
                                unitsUsedStr.chop(1);
                                //Multiple units provided. In command line is correct but the GUI can only handle one unit. Skip parameters and set back the defaults
                                warningString += QStringLiteral("Arguments provided to parameter '-filter:iscb' contain multiple units (%1). The GUI can only handle one unit at at time (but the command line does not have this limitation). It was skipped.\n").arg(unitsUsedStr);
                                //Set back the defaults in the table
                                ui->comboBoxISCBUnit->setCurrentIndex(0);
                                this->on_pushButtonISCBEstimateAll_clicked();
                                this->on_groupBoxISCB_clicked(false);
                            }
                        }
                    } else if ( QString::compare(option, "-filter:fixedweight", Qt::CaseInsensitive)==0 ) {
                        //Weight will be processed after reading all parameters, so they are processed after '-filter:select' or '-pre:smoothmeas'
                        fixedWeightProvided=1;
                        fixedWeightParam.append(ParametersList);
                    } else if ( QString::compare(option, "-filter:elevweight", Qt::CaseInsensitive)==0 ) {
                        //Weight will be processed after reading all parameters, so they are processed after '-filter:select' or '-pre:smoothmeas'
                        elevWeightProvided=1;
                        elevWeightParam.append(ParametersList);
                    } else if ( QString::compare(option, "-filter:sinelevweight", Qt::CaseInsensitive)==0 ) {
                        //Weight will be processed after reading all parameters, so they are processed after '-filter:select' or '-pre:smoothmeas'
                        elevSinWeightProvided=1;
                        elevSinWeightParam.append(ParametersList);
                    } else if ( QString::compare(option, "-filter:snrweight", Qt::CaseInsensitive)==0 ) {
                        //Weight will be processed after reading all parameters, so they are processed after '-filter:select' or '-pre:smoothmeas'
                        snrWeightProvided=1;
                        snrWeightParam.append(ParametersList);
                    } else if ( QString::compare(option, "-filter:snrelevweight", Qt::CaseInsensitive)==0 ) {
                        //Weight will be processed after reading all parameters, so they are processed after '-filter:select' or '-pre:smoothmeas'
                        snrElevWeightProvided=1;
                        snrElevWeightParam.append(ParametersList);
                    } else if ( QString::compare(option, "-filter:snrweight:comb", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Measurement number for parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>4 ) {
                            warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                        /*} else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>2 ) {
                            warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";*/
                        } else if (QString::compare(userInputSingleSpace.section(" ", 1,1),"SNRi", Qt::CaseInsensitive)!=0 && QString::compare(userInputSingleSpace.section(" ", 1,1),"SNRj", Qt::CaseInsensitive)!=0
                                   && QString::compare(userInputSingleSpace.section(" ", 1,1),"MaxSNR", Qt::CaseInsensitive)!=0 && QString::compare(userInputSingleSpace.section(" ", 1,1),"MinSNR", Qt::CaseInsensitive)!=0
                                   && QString::compare(userInputSingleSpace.section(" ", 1,1),"MeanSNR", Qt::CaseInsensitive)!=0) {
                            if (userInputSingleSpace.section(" ", 1,1).contains("[a-zA-Z]")==true || userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()<0
                                                || userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()>1) {
                                warningString += "Value '" + userInputSingleSpace.section(" ", 1,1) + "' for parameter '" + option + "' is invalid. It was skipped.\n";
                            } else {
                                warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                            }
                        } else {
                            warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:sbasdgnssweightmode", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                            warningString += "Measurement number for parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>4 ) {
                            warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                        /*} else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>2 ) {
                            warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";*/
                        } else if (QString::compare(userInputSingleSpace.section(" ", 1,1),"ComputedOnly", Qt::CaseInsensitive)!=0 && QString::compare(userInputSingleSpace.section(" ", 1,1),"ComputedPlusUser", Qt::CaseInsensitive)!=0
                                   && QString::compare(userInputSingleSpace.section(" ", 1,1),"Computed+User", Qt::CaseInsensitive)!=0 && QString::compare(userInputSingleSpace.section(" ", 1,1),"UserOnly", Qt::CaseInsensitive)!=0) {
                            warningString += "Value '" + userInputSingleSpace.section(" ", 1,1) + "' for parameter '" + option + "' is invalid. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:sbasdgnssweightmodesat", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(3,&warningString,option,ParametersList);
                        if (ParametersList.count()<3) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GLONASSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==GalileoLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==BDSLetter
                                   ||userInputSingleSpace.section(" ", 0,0).at(0)==GEOLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==QZSSLetter ||userInputSingleSpace.section(" ", 0,0).at(0)==IRNSSLetter ) {
                            warningString += "Parameter '" + option + "' only admits GPS satellites. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).at(0)==GPSLetter) {
                            ValidRange=GetPRNRangeParam(&userInputSingleSpace, &option, &System, &StartPRN, &EndPRN, &warningString);
                            if (ValidRange==1) {
                                if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()>4 ) {
                                    warningString += "Maximum measurements for the filter is 4 (for '" + option + "' parameter). It was skipped.\n";
                                /*} else if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()>2 ) {
                                    warningString += "In the GUI, maximum measurements for the filter is 2 (for '" + option + "' parameter). It was skipped.\n";*/
                                } else if (userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt()<0) {
                                    warningString += "Measurement number for parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                                } else if (userInputSingleSpace.section(" ", 2,2).replace(",","").toDouble()<0.) {
                                    warningString += "Constant in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
                                } else if (QString::compare(userInputSingleSpace.section(" ", 2,2),"ComputedOnly", Qt::CaseInsensitive)!=0 && QString::compare(userInputSingleSpace.section(" ", 2,2),"ComputedPlusUser", Qt::CaseInsensitive)!=0
                                           && QString::compare(userInputSingleSpace.section(" ", 2,2),"Computed+User", Qt::CaseInsensitive)!=0 && QString::compare(userInputSingleSpace.section(" ", 2,2),"UserOnly", Qt::CaseInsensitive)!=0) {
                                    warningString += "Value '" + userInputSingleSpace.section(" ", 2,2) + "' for parameter '" + option + "' is invalid. It was skipped.\n";
                                } else {
                                    warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                                }
                             }
                        } else {
                            warningString += "Parameter '" + option + "does not have a valid constellation. It was skipped.\n";
                        }
                    } else if (QString::compare(option, "-filter:dr:randomwalk", Qt::CaseInsensitive)==0){
                        this->on_radioButtonRandomwalkCoordinates_clicked();
                        if (CoordPhi!="") {
                            ui->lineEditPhiCoordinates->setText(CoordPhi);
                        }
                        if (CoordQ!="") {
                            ui->lineEditQcoordinates->setText(CoordQ);
                        }
                        if (CoordP0!="") {
                            ui->lineEditPoCoordinates->setText(CoordP0);
                        }
                    } else if (QString::compare(option, "-filter:clk:randomwalk", Qt::CaseInsensitive)==0){
                        this->on_radioButtonRandomwalkClock_clicked();
                        if (ClkPhi!="") {
                            ui->lineEditPhiClock->setText(ClkPhi);
                        }
                        if (ClkQ!="") {
                            ui->lineEditQclock->setText(ClkQ);
                        }
                        if (ClkP0!="") {
                            ui->lineEditPoClock->setText(ClkP0);
                        }
                    } else if (QString::compare(option, "-filter:iscb:randomwalk", Qt::CaseInsensitive)==0){
                        this->on_radioButtonRandomwalkISCB_clicked();
                        if (ISCBPhi!="") {
                            ui->lineEditPhiISCB->setText(ISCBPhi);
                        }
                        if (ISCBQ!="") {
                            ui->lineEditQISCB->setText(ISCBQ);
                        }
                        if (ISCBP0!="") {
                            ui->lineEditPoISCB->setText(ISCBP0);
                        }
                    } else if ( QString::compare(option, "-filter:iono:randomwalk", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-filter:satdcb:randomwalk", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-filter:recdcb:randomwalk", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-filter:phi:dr", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditPhiCoordinates->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            CoordPhi=ui->lineEditPhiCoordinates->text();
                        }
                    } else if ( QString::compare(option, "-filter:phi:clk", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditPhiClock->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ClkPhi=ui->lineEditPhiClock->text();
                        }
                    } else if ( QString::compare(option, "-filter:phi:iscb", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditPhiISCB->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ISCBPhi=ui->lineEditPhiISCB->text();
                        }
                    } else if ( QString::compare(option, "-filter:phi:trop", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditPhiTropo->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-filter:phi:amb", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditPhiPhaseAmbiguities->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }

                    } else if ( QString::compare(option, "-filter:phi:gloifb", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:phi:recwindup", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:q:dr", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditQcoordinates->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            CoordQ=ui->lineEditQcoordinates->text();
                            if (CoordQ=="0") {
                                ui->radioButtonStatic->setChecked(true);
                                ui->labelQcoordinatesUnit->setText("(m²)");
                            }
                        }
                    } else if ( QString::compare(option, "-filter:q:clk", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            if (ui->radioButtonRandomwalkClock->isChecked()){//Randomwalk
                                ui->stackedWidgetQClockUnit->setCurrentIndex(1);
                                this->on_comboBoxQClockUnitRandom_currentIndexChanged(0);
                            } else { //Normal
                                ui->stackedWidgetQClockUnit->setCurrentIndex(0);
                                this->on_comboBoxQClockUnitNormal_currentIndexChanged(0);
                            }
                            ui->lineEditQclock->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ClkQ=ui->lineEditQclock->text();
                            if (ClkQ=="0") {
                                ui->radioButtonConstantClock->setChecked(true);
                            }
                        }
                    } else if ( QString::compare(option, "-filter:q:iscb", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            if (ui->radioButtonRandomwalkISCB->isChecked()){//Randomwalk
                                ui->stackedWidgetQISCBUnit->setCurrentIndex(1);
                                this->on_comboBoxQISCBUnitRandom_currentIndexChanged(0);
                            } else { //Normal
                                ui->stackedWidgetQISCBUnit->setCurrentIndex(0);
                                this->on_comboBoxQISCBUnitNormal_currentIndexChanged(0);
                            }
                            ui->lineEditQISCB->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ISCBQ=ui->lineEditQISCB->text();
                        }
                    } else if ( QString::compare(option, "-filter:q:clk:ns", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            if (ui->radioButtonRandomwalkClock->isChecked()){//Randomwalk
                                ui->stackedWidgetQClockUnit->setCurrentIndex(1);
                                this->on_comboBoxQClockUnitRandom_currentIndexChanged(1);
                            } else { //Normal
                                ui->stackedWidgetQClockUnit->setCurrentIndex(0);
                                this->on_comboBoxQClockUnitNormal_currentIndexChanged(1);
                            }
                            ui->lineEditQclock->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ClkQ=ui->lineEditQclock->text();
                        }
                    } else if ( QString::compare(option, "-filter:q:iscb:ns", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            if (ui->radioButtonRandomwalkISCB->isChecked()){//Randomwalk
                                ui->stackedWidgetQISCBUnit->setCurrentIndex(1);
                                this->on_comboBoxQISCBUnitRandom_currentIndexChanged(1);
                            } else { //Normal
                                ui->stackedWidgetQISCBUnit->setCurrentIndex(0);
                                this->on_comboBoxQISCBUnitNormal_currentIndexChanged(1);
                            }
                            ui->lineEditQISCB->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ISCBQ=ui->lineEditQISCB->text();
                        }
                    } else if ( QString::compare(option, "-filter:q:trop", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditQtropo->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-filter:q:amb", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditQphaseAmbiguities->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }

                    } else if ( QString::compare(option, "-filter:q:gloifb", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:q:recwindup", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:p0:dr", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditPoCoordinates->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            CoordP0=ui->lineEditPoCoordinates->text();
                        }
                    } else if ( QString::compare(option, "-filter:p0:clk", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->comboBoxPoClockUnit->setCurrentIndex(0);
                            ui->lineEditPoClock->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ClkP0=ui->lineEditPoClock->text();
                        }
                    }  else if ( QString::compare(option, "-filter:p0:iscb", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->comboBoxPoISCBUnit->setCurrentIndex(0);
                            ui->lineEditPoISCB->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ISCBP0=ui->lineEditPoISCB->text();
                        }
                    } else if ( QString::compare(option, "-filter:p0:clk:ns", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->comboBoxPoClockUnit->setCurrentIndex(1);
                            ui->lineEditPoClock->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ClkP0=ui->lineEditPoClock->text();
                        }
                    }  else if ( QString::compare(option, "-filter:p0:iscb:ns", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->comboBoxPoISCBUnit->setCurrentIndex(1);
                            ui->lineEditPoISCB->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ISCBP0=ui->lineEditPoISCB->text();
                        }
                    } else if ( QString::compare(option, "-filter:p0:trop", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditPoTropo->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-filter:p0:amb", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditPoPhaseAmbiguities->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }

                    } else if ( QString::compare(option, "-filter:p0:gloifb", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:p0:recwindup", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.) {
                            warningString += "Parameter '" + option + "' has to be equal or greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-filter:backward", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxBackwardFiltering->setChecked(true);
                    } else if ( QString::compare(option, "--filter:backward", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxBackwardFiltering->setChecked(false);
                    } else if ( QString::compare(option, "-filter:stfdesa", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        if ( mode==2 || mode==3 ) {
                            //Stanford-ESA is only for SBAS mode
                            this->on_groupBoxStanfordESA_clicked(true);
                            this->on_checkBoxStanfordESAallGeometries_clicked(true);
                        } else {
                            warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "--filter:stfdesa", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_groupBoxStanfordESA_clicked(false);
                    } else if ( QString::compare(option, "-filter:stfdesaLOI", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        if ( mode==2 || mode==3 ) {
                            //Stanford-ESA is only for SBAS mode
                            this->on_groupBoxStanfordESA_clicked(true);
                            this->on_checkBoxStanfordESAallGeometries_clicked(true);
                        } else {
                            warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "--filter:stfdesaLOI", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxStanfordESAallGeometries_clicked(false);
                    } else if ( QString::compare(option, "-filter:stfdesa:hwir", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            if ( mode==2 || mode==3 ) {
                                //Stanford-ESA is only for SBAS mode
                                this->on_groupBoxStanfordESA_clicked(true);
                                this->on_checkBoxStanfordESAallGeometries_clicked(true);
                                ui->lineEditHorizontalIntegrityRatio->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            } else {
                                warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-filter:stfdesa:vwir", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            if ( mode==2 || mode==3 ) {
                                //Stanford-ESA is only for SBAS mode
                                this->on_groupBoxStanfordESA_clicked(true);
                                this->on_checkBoxStanfordESAallGeometries_clicked(true);
                                ui->lineEditVerticalIntegrityRatio->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            } else {
                                warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-filter:stfdesa:xmax", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            if ( mode==2 || mode==3 ) {
                                //Stanford-ESA is only for SBAS mode
                                this->on_groupBoxStanfordESA_clicked(true);
                                ui->lineEditStanfordEsaXmax->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            } else {
                                warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-filter:stfdesa:ymax", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            if ( mode==2 || mode==3 ) {
                                //Stanford-ESA is only for SBAS mode
                                this->on_groupBoxStanfordESA_clicked(true);
                                ui->lineEditStanfordEsaYmax->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            } else {
                                warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-filter:stfdesa:xres", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            if ( mode==2 || mode==3 ) {
                                //Stanford-ESA is only for SBAS mode
                                this->on_groupBoxStanfordESA_clicked(true);
                                ui->lineEditStanfordEsaXres->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            } else {
                                warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-filter:stfdesa:yres", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            if ( mode==2 || mode==3 ) {
                                //Stanford-ESA is only for SBAS mode
                                this->on_groupBoxStanfordESA_clicked(true);
                                ui->lineEditStanfordEsaYres->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            } else {
                                warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-filter:stfdesa:maxsat", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toInt()<=0) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            if ( mode==2 || mode==3 ) {
                                //Stanford-ESA is only for SBAS mode
                                this->on_groupBoxStanfordESA_clicked(true);
                                ui->lineEditStfdESAMaxSatCombinations->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            } else {
                                warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-filter:maxhdop", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxMaxHDOP_clicked(true);
                            ui->lineEditMaxHDOP->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "--filter:maxhdop", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxMaxHDOP_clicked(false);
                    } else if ( QString::compare(option, "-filter:maxpdop", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxMaxPDOP_clicked(true);
                            ui->lineEditMaxPDOP->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "--filter:maxpdop", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxMaxHDOP_clicked(false);
                    } else if ( QString::compare(option, "-filter:maxgdop", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxMaxGDOP_clicked(true);
                            ui->lineEditMaxGDOP->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "--filter:maxgdop", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxMaxGDOP_clicked(false);
                    } else if ( QString::compare(option, "-filter:hdoporpdop", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxHDOPorPDOP->setChecked(true);
                    } else if ( QString::compare(option, "--filter:hdoporpdop", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxHDOPorPDOP->setChecked(false);
                    } else if ( QString::compare(option, "-filter:SigmaIono", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxUseSigmaIonosphere->setChecked(true);
                    } else if ( QString::compare(option, "--filter:SigmaIono", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxUseSigmaIonosphere->setChecked(false);
                    } else if ( QString::compare(option, "-filter:StepDetector", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        if( mode==2 || mode==3 ) {
                            //Step detector is only used in SBAS mode
                            ui->checkBoxStepDetector->setChecked(true);
                        } else {
                            warningString += "Step detector (parameter '" + option + "' only takes effect in SBAS mode. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "--filter:StepDetector", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxStepDetector->setChecked(false);
                    } else if ( QString::compare(option, "-filter:prefitOutliers:Abs", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "--filter:prefitOutliers:Abs", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-filter:prefitOutliers:Median", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrefitOutliers_clicked(true);
                            ui->lineEditPrefitOutliers->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "--filter:prefitOutliers:Median", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxPrefitOutliers_clicked(false);

                    ////////////////////
                    // OUTPUT SECTION

                    } else if ( QString::compare(option, "-output:file", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            ui->lineEditOutputDestination->setText(userInput);
                        }
                    } else if ( QString::compare(option, "--output:file", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for setting output messages to standard output, which will be lost after execution finishes. It was skipped.\n";
                    } else if ( QString::compare(option, "-output:kml", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_checkBoxKML_clicked(true);
                            ui->lineEditKML->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-output:kml0", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_checkBoxKML0_clicked(true);
                            ui->lineEditKML0->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-output:kml:refsta", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        if(mode!=3) {
                            //This option only has effect in DGNSS mode
                            warningString += "Parameter '" + option + "' only takes effect in DGNSS mode. It was skipped.\n";
                        } else {
                            ui->checkBoxKMLRefStations->setChecked(true);
                        }
                    } else if ( QString::compare(option, "--output:kml:refsta", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxKMLRefStations->setChecked(false);
                    } else if ( QString::compare(option, "-output:kml:egm96geoid", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxKMLGeoid->setChecked(true);
                    } else if ( QString::compare(option, "--output:kml:egm96geoid", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxKMLGeoid->setChecked(false);
                    } else if ( QString::compare(option, "-output:kml:tstamp", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBox_KML_TimeStamps_clicked(true);
                    } else if ( QString::compare(option, "--output:kml:tstamp", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBox_KML_TimeStamps_clicked(false);
                    } else if ( QString::compare(option, "-output:kml:tstampdec", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBox_KML_TimeStamps_clicked(true);
                            ui->lineEditKML_Dec->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-output:kml:tstamprange", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(2,&warningString,option,ParametersList);
                        if (ParametersList.count()<2) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if ( (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0. && userInputSingleSpace.section(" ", 0,0)!="-") ||
                              (userInputSingleSpace.section(" ", 1,1).replace(",","").toDouble()<0. && userInputSingleSpace.section(" ", 1,1)!="-") ) {
                            warningString += "Timestamp ranges in parameter '" + option + "' have to be equal or greater than 0. It was skipped.\n";
                        } else {
                            numKMLRanges++;
                            if(numKMLRanges==1) {
                                this->on_checkBox_KML_TimeStamps_clicked(true);
                                this->on_checkBox_KML_Range_clicked(true);
                                ui->lineEditKML_From->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                                ui->lineEditKML_To->setText(QString("%1").arg(userInputSingleSpace.section(" ", 1,1).replace(",","")));
                            } else {
                                warningString += "Only one timestamp range can be set in the GUI (in command line there is no limit). It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-output:sp3", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_checkBoxOutputSP3_clicked(true);
                            ui->lineEditOutputSP3->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-output:sp3:letter", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).length()>1) {
                            warningString += "Parameter '" + option + "' only admits one character for the satellite constellation. It was skipped.\n";
                        } else if (!userInputSingleSpace.section(" ", 0,0).contains("[A-Z]")) {
                            warningString += "Parameter '" + option + "' only admits capital letters for satellite constellation. It was skipped.\n";
                        } else {
                            ui->lineEditSP3Letter->setText(userInputSingleSpace.section(" ", 0,0));
                        }
                    } else if ( QString::compare(option, "-output:sp3:prn", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0 || userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>99) {
                            warningString += "PRN number for parameter '" + option + "' has to be greater than 0 and less than 100. It was skipped.\n";
                        } else {
                            ui->lineEditSP3PRN->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()));
                        }
                    } else if ( QString::compare(option, "-output:sp3:dgnssonly", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSP3OutFileWriteSPPSolutions->setChecked(true);
                    } else if ( QString::compare(option, "--output:sp3:dgnssonly", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxSP3OutFileWriteSPPSolutions->setChecked(false);
                    } else if ( QString::compare(option, "-output:refpos", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            this->on_checkBoxOutRefFile_clicked(true);
                            ui->lineEditOutRefFile->setText(userInput);
                        }
                    } else if ( QString::compare(option, "-output:refpos:doy", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->radioButtonOutRefFileYearDoYSoD->setChecked(true);
                    } else if ( QString::compare(option, "-output:refpos:gpsweek", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->radioButtonOutRefFileGPSWeek->setChecked(true);
                    } else if ( QString::compare(option, "-output:refpos:caltime", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->radioButtonOutRefFileCalendar->setChecked(true);
                    } else if ( QString::compare(option, "-output:refpos:dgnssonly", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxRefOutFileWriteSPPSolutions->setChecked(true);
                    } else if ( QString::compare(option, "--output:refpos:dgnssonly", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxRefOutFileWriteSPPSolutions->setChecked(false);
                    } else if ( QString::compare(option, "-output:refpos:geodetic", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->radioButtonOutRefFileGeod->setChecked(true);
                    } else if ( QString::compare(option, "--output:refpos:geodetic", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->radioButtonOutRefFileCartesian->setChecked(false);
                    } else if ( QString::compare(option, "-output:satvel", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        //This parameter is hidden in the GUI, due to "Inertial" velocity is not the completely in inertial coordinates
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (QString::compare(ParametersList[0], "inertial", Qt::CaseInsensitive)==0) {
                             if (ui->frameOutputSatVel->isHidden()==true) {
                                warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                             }
                             ui->radioButtonSatVelInertial->setChecked(true);
                        } else if (QString::compare(ParametersList[0], "ITRF", Qt::CaseInsensitive)==0) {
                            if (ui->frameOutputSatVel->isHidden()==true) {
                                warningString += "Parameter '" + option + "' is only available in command line. It was skipped.\n";
                            }
                             ui->radioButtonSatVelECEF->setChecked(true);
                        } else {
                            warningString += "'" + ParametersList[0] + "' is not a valid argument for parameter '" + option + "'. It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-output:stfdesa", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            if ( mode==2 || mode==3 ) {
                                //Stanford-ESA is only for SBAS mode
                                this->on_groupBoxStanfordESA_clicked(true);
                                ui->lineEditOutputStanfordEsaPlot->setText(userInput);
                            } else {
                                warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-output:stfdesaLOI", Qt::CaseInsensitive)==0 ) {
                        if (ParametersList.count()>=1) {
                            if ( mode==2 || mode==3 ) {
                                //Stanford-ESA is only for SBAS mode
                                this->on_groupBoxStanfordESA_clicked(true);
                                this->on_checkBoxStanfordESAallGeometries_clicked(true);
                                ui->lineEditOutputframeStanfordESAallGeometries->setText(userInput);
                            } else {
                                warningString += "Stanford-ESA can only be enabled in SBAS mode in the GUI. It was skipped.\n";
                            }
                        }



                    ////////////////////
                    // PRINT SECTION

                    } else if ( QString::compare(option, "-print:info", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintInfo->setChecked(true);
                    } else if ( QString::compare(option, "--print:info", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintInfo->setChecked(false);
                    } else if ( QString::compare(option, "-print:model", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintModel->setChecked(true);
                    } else if ( QString::compare(option, "--print:model", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintModel->setChecked(false);
                    } else if ( QString::compare(option, "-print:prefit", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintPrefit->setChecked(true);
                    } else if ( QString::compare(option, "--print:prefit", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintPrefit->setChecked(false);
                    } else if ( QString::compare(option, "-print:postfit", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintPostfit->setChecked(true);
                    } else if ( QString::compare(option, "--print:postfit", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintPostfit->setChecked(false);
                    } else if ( QString::compare(option, "-print:filter", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintFilter->setChecked(true);
                    } else if ( QString::compare(option, "--print:filter", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintFilter->setChecked(false);
                    } else if ( QString::compare(option, "-print:cycleslips", Qt::CaseInsensitive)==0 || QString::compare(option, "-print:cs", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintCS->setChecked(true);
                    } else if ( QString::compare(option, "--print:cycleslips", Qt::CaseInsensitive)==0 || QString::compare(option, "--print:cs", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintCS->setChecked(false);
                    } else if ( QString::compare(option, "-print:sfcsdata", Qt::CaseInsensitive)==0 || QString::compare(option, "-print:cs", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSFCS->setChecked(true);
                    } else if ( QString::compare(option, "--print:sfcsdata", Qt::CaseInsensitive)==0 || QString::compare(option, "--print:cs", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSFCS->setChecked(false);
                    } else if ( QString::compare(option, "-print:mwcsdata", Qt::CaseInsensitive)==0 || QString::compare(option, "-print:cs", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintMWCS->setChecked(true);
                    } else if ( QString::compare(option, "--print:mwcsdata", Qt::CaseInsensitive)==0 || QString::compare(option, "--print:cs", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintMWCS->setChecked(false);
                    } else if ( QString::compare(option, "-print:licsdata", Qt::CaseInsensitive)==0 || QString::compare(option, "-print:cs", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintLICS->setChecked(true);
                    } else if ( QString::compare(option, "--print:licsdata", Qt::CaseInsensitive)==0 || QString::compare(option, "--print:cs", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintLICS->setChecked(false);
                    } else if ( QString::compare(option, "-print:igfcsdata", Qt::CaseInsensitive)==0 || QString::compare(option, "-print:cs", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintIGFCS->setChecked(true);
                    } else if ( QString::compare(option, "--print:igfcsdata", Qt::CaseInsensitive)==0 || QString::compare(option, "--print:cs", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintIGFCS->setChecked(false);
                    } else if ( QString::compare(option, "-print:satellites", Qt::CaseInsensitive)==0 || QString::compare(option, "-print:epochsat", Qt::CaseInsensitive)==0 || QString::compare(option, "-print:sat", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintEpochsat->setChecked(true);
                    } else if ( QString::compare(option, "--print:satellites", Qt::CaseInsensitive)==0 || QString::compare(option, "--print:epochsat", Qt::CaseInsensitive)==0 || QString::compare(option, "--print:sat", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintEpochsat->setChecked(false);
                    } else if ( QString::compare(option, "-print:input", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintInput->setChecked(true);
                    } else if ( QString::compare(option, "--print:input", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintInput->setChecked(false);
                    } else if ( QString::compare(option, "-print:meas", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxPrintMeas_clicked(true);
                    } else if ( QString::compare(option, "--print:meas", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxPrintMeas_clicked(false);
                    } else if ( QString::compare(option, "-print:meas:select", Qt::CaseInsensitive)==0 || QString::compare(option, "-print:meas:selectlist", Qt::CaseInsensitive)==0 ) {
                        QStringList ParamAux;
                        if (QString::compare(option, "-print:meas:selectlist", Qt::CaseInsensitive)==0) {
                            MeasPrintParamList.append(ParametersList[0].split(",", QString::SkipEmptyParts));
                        } else {
                            MeasPrintParamList.append(ParametersList);
                        }
                        MeasPrintParamProvided=1;
                        //It will be parsed at the end, so all arguemnts are parsed toguether
                    } else if ( QString::compare(option, "-print:output", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintOutput->setChecked(true);
                    } else if ( QString::compare(option, "--print:output", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintOutput->setChecked(false);
                    } else if ( QString::compare(option, "-print:satsel", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSatsel->setChecked(true);
                    } else if ( QString::compare(option, "--print:satsel", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSatsel->setChecked(false);
                    } else if ( QString::compare(option, "-print:satdiff", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for orbit comparison mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "--print:satdiff", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for orbit comparison mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-print:satstat", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for orbit comparison mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "--print:satstat", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for orbit comparison mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-print:satstattot", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for orbit comparison mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "--print:satstattot", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for orbit comparison mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-print:satpvt", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for show orbits mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "--print:satpvt", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for show orbits mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-print:sbasout", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasout->setChecked(true);
                    } else if ( QString::compare(option, "--print:sbasout", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasout->setChecked(false);
                    } else if ( QString::compare(option, "-print:sbascor", Qt::CaseInsensitive)==0 || QString::compare(option, "-print:sbascorr", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbascor->setChecked(true);
                    } else if ( QString::compare(option, "--print:sbascor", Qt::CaseInsensitive)==0 || QString::compare(option, "--print:sbascorr", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbascor->setChecked(false);
                    } else if ( QString::compare(option, "-print:sbasvar", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasvar->setChecked(true);
                    } else if ( QString::compare(option, "--print:sbasvar", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasvar->setChecked(false);
                    } else if ( QString::compare(option, "-print:sbasiono", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasiono->setChecked(true);
                    } else if ( QString::compare(option, "--print:sbasiono", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasiono->setChecked(false);
                    } else if ( QString::compare(option, "-print:sbasunsel", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasunsel->setChecked(true);
                    } else if ( QString::compare(option, "--print:sbasunsel", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasunsel->setChecked(false);
                    } else if ( QString::compare(option, "-print:sbasunused", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasunused->setChecked(true);
                    } else if ( QString::compare(option, "--print:sbasunused", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasunused->setChecked(false);
                    } else if ( QString::compare(option, "-print:sbasdfmccor", Qt::CaseInsensitive)==0 || QString::compare(option, "-print:sbasdfmccorr", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasDFMCCor->setChecked(true);
                    } else if ( QString::compare(option, "--print:sbasdfmccor", Qt::CaseInsensitive)==0 || QString::compare(option, "--print:sbasdfmccorr", Qt::CaseInsensitive)==0) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasDFMCCor->setChecked(false);
                    } else if ( QString::compare(option, "-print:sbasvar", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasDFMCVar->setChecked(true);
                    } else if ( QString::compare(option, "--print:sbasdfmcvar", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasDFMCVar->setChecked(false);
                    } else if ( QString::compare(option, "-print:sbasdfmcvar", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasDFMCUnsel->setChecked(true);
                    } else if ( QString::compare(option, "--print:sbasdfmcunsel", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintSbasDFMCUnsel->setChecked(false);
                    } else if ( QString::compare(option, "-print:sbasdfmcunsel", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintUsererror->setChecked(true);
                    } else if ( QString::compare(option, "-print:usererror", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintUsererror->setChecked(true);
                    } else if ( QString::compare(option, "--print:usererror", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintUsererror->setChecked(false);
                    } else if ( QString::compare(option, "-print:dgnss", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintDgnss->setChecked(true);
                    } else if ( QString::compare(option, "--print:dgnss", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintDgnss->setChecked(false);
                    } else if ( QString::compare(option, "-print:dgnssunused", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintDgnssunused->setChecked(true);
                    } else if ( QString::compare(option, "--print:dgnssunused", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintDgnssunused->setChecked(false);
                    } else if ( QString::compare(option, "-print:summary", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxPrintSummary_clicked(true);
                    } else if ( QString::compare(option, "--print:summary", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxPrintSummary_clicked(false);
                    } else if ( QString::compare(option, "-print:all", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintInfo->setChecked(true);
                        ui->checkBoxPrintUsererror->setChecked(true);
                        ui->checkBoxPrintInput->setChecked(true);
                        ui->checkBoxPrintCS->setChecked(true);
                        ui->checkBoxPrintSFCS->setChecked(true);
                        ui->checkBoxPrintMWCS->setChecked(true);
                        ui->checkBoxPrintLICS->setChecked(true);
                        ui->checkBoxPrintIGFCS->setChecked(true);
                        ui->checkBoxPrintMeas->setChecked(true);
                        ui->checkBoxPrintModel->setChecked(true);
                        ui->checkBoxPrintSatsel->setChecked(true);
                        ui->checkBoxPrintPrefit->setChecked(true);
                        ui->checkBoxPrintEpochsat->setChecked(true);
                        ui->checkBoxPrintPostfit->setChecked(true);
                        ui->checkBoxPrintFilter->setChecked(true);
                        ui->checkBoxPrintOutput->setChecked(true);                        
                        ui->checkBoxPrintSbascor->setChecked(true);
                        ui->checkBoxPrintSbasvar->setChecked(true);
                        ui->checkBoxPrintSbasiono->setChecked(true);
                        ui->checkBoxPrintSbasunsel->setChecked(true);
                        ui->checkBoxPrintSbasout->setChecked(true);
                        ui->checkBoxPrintSbasunused->setChecked(true);
                        ui->checkBoxPrintSbasDFMCCor->setChecked(true);
                        ui->checkBoxPrintSbasDFMCVar->setChecked(true);
                        ui->checkBoxPrintSbasDFMCUnsel->setChecked(true);
                        ui->checkBoxPrintDgnss->setChecked(true);
                        ui->checkBoxPrintDgnssunused->setChecked(true);
                        this->on_checkBoxPrintSummary_clicked(true);
                    } else if ( QString::compare(option, "-print:none", Qt::CaseInsensitive)==0|| QString::compare(option, "--print:none", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        ui->checkBoxPrintInfo->setChecked(false);
                        ui->checkBoxPrintUsererror->setChecked(false);
                        ui->checkBoxPrintInput->setChecked(false);
                        ui->checkBoxPrintCS->setChecked(false);
                        ui->checkBoxPrintSFCS->setChecked(false);
                        ui->checkBoxPrintMWCS->setChecked(false);
                        ui->checkBoxPrintLICS->setChecked(false);
                        ui->checkBoxPrintIGFCS->setChecked(false);
                        ui->checkBoxPrintMeas->setChecked(false);
                        ui->checkBoxPrintModel->setChecked(false);
                        ui->checkBoxPrintSatsel->setChecked(false);
                        ui->checkBoxPrintPrefit->setChecked(false);
                        ui->checkBoxPrintEpochsat->setChecked(false);
                        ui->checkBoxPrintPostfit->setChecked(false);
                        ui->checkBoxPrintFilter->setChecked(false);
                        ui->checkBoxPrintOutput->setChecked(false);
                        ui->checkBoxPrintSbascor->setChecked(false);
                        ui->checkBoxPrintSbasvar->setChecked(false);
                        ui->checkBoxPrintSbasiono->setChecked(false);
                        ui->checkBoxPrintSbasunsel->setChecked(false);
                        ui->checkBoxPrintSbasout->setChecked(false);
                        ui->checkBoxPrintSbasunused->setChecked(false);
                        ui->checkBoxPrintSbasDFMCCor->setChecked(false);
                        ui->checkBoxPrintSbasDFMCVar->setChecked(false);
                        ui->checkBoxPrintSbasDFMCUnsel->setChecked(false);
                        ui->checkBoxPrintDgnss->setChecked(false);
                        ui->checkBoxPrintDgnssunused->setChecked(false);
                        this->on_checkBoxPrintSummary_clicked(false);
                    } else if ( QString::compare(option, "-print:progress", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for showing progress in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "--print:progress", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for not showing progress in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-print:progressalways", Qt::CaseInsensitive)==0 || QString::compare(option, "-print:pa", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for forcing to show the progress in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "--print:progressalways", Qt::CaseInsensitive)==0 || QString::compare(option, "--print:pa", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for forcing to show the progress in command line. It was skipped.\n";
                    } else if ( QString::compare(option, "-print:guiprogress", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is an internal parameter for printing the progress in a format readable by the GUI. It was skipped.\n";
                    } else if ( QString::compare(option, "-print:v5format", Qt::CaseInsensitive)==0 ) {
                        this->v5Message=1;
                    } else if ( QString::compare(option, "--print:v5format", Qt::CaseInsensitive)==0 ) {
                        this->v5Message=0;
                    } else if ( QString::compare(option, "-print:clkns", Qt::CaseInsensitive)==0 ) {
                        ui->radioButtonNanosecondsUnitOutputClock->setChecked(true);
                    } else if ( QString::compare(option, "--print:clkns", Qt::CaseInsensitive)==0 ) {
                        ui->radioButtonMetresUnitOutputClock->setChecked(true);

                    ////////////////////
                    // SUMMARY SECTION

                    } else if ( QString::compare(option, "-sbassummary:VAL", Qt::CaseInsensitive)==0 || QString::compare(option, "-summary:VAL", Qt::CaseInsensitive)==0  ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditHorizontalAlarmLimitSBAS->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-sbassummary:HAL", Qt::CaseInsensitive)==0 || QString::compare(option, "-summary:HAL", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditVerticalAlarmLimitSBAS->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-sbassummary:percentile", Qt::CaseInsensitive)==0 || QString::compare(option, "-summary:percentile", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0 || userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()>100 ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0 and less or equal to 100. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditPercentileValue->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-sbassummary:windowsize", Qt::CaseInsensitive)==0 || QString::compare(option, "-summary:windowsize", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0 ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSlidingWindowSBAS->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-sbassummary:windowsizemar", Qt::CaseInsensitive)==0 || QString::compare(option, "-summary:windowsizemar", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0 ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditMaritimeWindowSBAS->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
                        }
                    } else if ( QString::compare(option, "-sbassummary:waitfordaystart", Qt::CaseInsensitive)==0 || QString::compare(option, "-summary:waitfordaystart", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxPrintSummary_clicked(true);
                        this->on_checkBoxWaitforDayStart_clicked(true);
                    } else if ( QString::compare(option, "--sbassummary:waitfordaystart", Qt::CaseInsensitive)==0 || QString::compare(option, "--summary:waitfordaystart", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        this->on_checkBoxWaitforDayStart_clicked(false);
                    } else if ( QString::compare(option, "-sbassummary:stationnetworkname", Qt::CaseInsensitive)==0 || QString::compare(option, "-summary:stationnetworkname", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbassummary:starttime", Qt::CaseInsensitive)==0 || QString::compare(option, "-summary:starttime", Qt::CaseInsensitive)==0 ) {
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
                                     ui->dateTimeEditStartTimeSummary->setDate(date);
                                     ui->dateTimeEditStartTimeSummary->setTime(hour);
                                     this->on_checkBoxPrintSummary_clicked(true);
                                     this->on_checkBoxStartTimeSummary_clicked(true);
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
                                        ui->dateTimeEditStartTimeSummary->setDate(date);
                                        ui->dateTimeEditStartTimeSummary->setTime(hour);
                                        this->on_checkBoxPrintSummary_clicked(true);
                                        this->on_checkBoxStartTimeSummary_clicked(true);
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
                                        ui->dateTimeEditStartTimeSummary->setDate(date);
                                        ui->dateTimeEditStartTimeSummary->setTime(hour);
                                        this->on_checkBoxPrintSummary_clicked(true);
                                        this->on_checkBoxStartTimeSummary_clicked(true);
                                    }
                                }
                            }
                        }
                    } else if ( QString::compare(option, "-summary:errorhor", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergenceFormalThresHor->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ui->lineEditSummaryConvergencePositionThresHor->setText(ui->lineEditSummaryConvergenceFormalThresHor->text());
                        }
                    } else if ( QString::compare(option, "-summary:errorver", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergenceFormalThresVer->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ui->lineEditSummaryConvergencePositionThresVer->setText(ui->lineEditSummaryConvergenceFormalThresVer->text());
                        }
                    } else if ( QString::compare(option, "-summary:error3d", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergenceFormalThres3D->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ui->lineEditSummaryConvergencePositionThres3D->setText(ui->lineEditSummaryConvergenceFormalThres3D->text());
                        }
                    } else if ( QString::compare(option, "-summary:errorhv3d", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergenceFormalThresHor->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ui->lineEditSummaryConvergencePositionThresHor->setText(ui->lineEditSummaryConvergenceFormalThresHor->text());
                            ui->lineEditSummaryConvergenceFormalThresVer->setText(ui->lineEditSummaryConvergenceFormalThresHor->text());
                            ui->lineEditSummaryConvergencePositionThresVer->setText(ui->lineEditSummaryConvergenceFormalThresHor->text());
                            ui->lineEditSummaryConvergenceFormalThres3D->setText(ui->lineEditSummaryConvergenceFormalThresHor->text());
                            ui->lineEditSummaryConvergencePositionThres3D->setText(ui->lineEditSummaryConvergenceFormalThresHor->text());
                        }
                    } else if ( QString::compare(option, "-summary:errorperiodhor", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergenceFormalTimeThresHor->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ui->lineEditSummaryConvergencePositionTimeThresHor->setText(ui->lineEditSummaryConvergenceFormalTimeThresHor->text());
                        }
                    } else if ( QString::compare(option, "-summary:errorperiodver", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergenceFormalTimeThresVer->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ui->lineEditSummaryConvergencePositionTimeThresVer->setText(ui->lineEditSummaryConvergenceFormalTimeThresVer->text());
                        }
                    } else if ( QString::compare(option, "-summary:errorperiod3d", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergenceFormalTimeThres3D->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ui->lineEditSummaryConvergencePositionTimeThres3D->setText(ui->lineEditSummaryConvergenceFormalTimeThres3D->text());
                        }
                    } else if ( QString::compare(option, "-summary:errorperiodhv3d", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergenceFormalTimeThresHor->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                            ui->lineEditSummaryConvergencePositionTimeThresHor->setText(ui->lineEditSummaryConvergenceFormalTimeThresHor->text());
                            ui->lineEditSummaryConvergenceFormalTimeThresVer->setText(ui->lineEditSummaryConvergenceFormalTimeThresHor->text());
                            ui->lineEditSummaryConvergencePositionTimeThresVer->setText(ui->lineEditSummaryConvergenceFormalTimeThresHor->text());
                            ui->lineEditSummaryConvergenceFormalTimeThres3D->setText(ui->lineEditSummaryConvergenceFormalTimeThresHor->text());
                            ui->lineEditSummaryConvergencePositionTimeThres3D->setText(ui->lineEditSummaryConvergenceFormalTimeThresHor->text());
                        }

                    } else if ( QString::compare(option, "-summary:formalerrorhor", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergenceFormalThresHor->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-summary:formalerrorver", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergenceFormalThresVer->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-summary:formalerror3d", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergenceFormalThres3D->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-summary:formalerrorperiodhor", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergenceFormalTimeThresHor->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-summary:formalerrorperiodver", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergenceFormalTimeThresVer->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-summary:formalerrorperiod3d", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergenceFormalTimeThres3D->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }

                    } else if ( QString::compare(option, "-summary:poserrorhor", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            ui->lineEditSummaryConvergencePositionThresHor->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-summary:poserrorver", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergencePositionThresVer->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-summary:poserror3d", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergencePositionThres3D->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-summary:poserrorperiodhor", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergencePositionTimeThresHor->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-summary:poserrorperiodver", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergencePositionTimeThresVer->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }
                    } else if ( QString::compare(option, "-summary:poserrorperiod3d", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            this->on_checkBoxPrintSummary_clicked(true);
                            ui->lineEditSummaryConvergencePositionTimeThres3D->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","")));
                        }

                    ////////////////////
                    // FILE CONVERSION SECTION

                    } else if ( QString::compare(option, "-output:sbasdir", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:rinexb", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:ems", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:pegasus", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:pegspace", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:pegstrictrinex", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:pegfilealign", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                    } else if ( QString::compare(option, "-output:rinex", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:antenna", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:corrections", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:rinexversion", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for file conversion mode. It has no effect in positioning mode.\n";
                        }

                    ////////////////////
                    // SBAS PLOTS SECTION

                    } else if ( QString::compare(option, "-sbasplots:minlat", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<-90. || userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>90. ) {
                            warningString += "Parameter '" + option + "' has to be between -90 and 90 degrees. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:maxlat", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<-90. || userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>90. ) {
                            warningString += "Parameter '" + option + "' has to be between -90 and 90 degrees. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:minlon", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<-180. || userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>180. ) {
                            warningString += "Parameter '" + option + "' has to be between -180 and 180 degrees. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:maxlon", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<-180. || userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>180. ) {
                            warningString += "Parameter '" + option + "' has to be between -180 and 180 degrees. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:recheight", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:VAL", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0. ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:HAL", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0. ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:AvailStep", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.01 ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0 with a minimum resolution of 0.01 degrees. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:IonoStep", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<0.01 ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0 with a minimum resolution of 0.01 degrees. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:ionotimestep", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0. ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:windowsize", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
                        if (ParametersList.count()<1) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0. ) {
                            warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
                        } else {
                            warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                        }
                    } else if ( QString::compare(option, "-sbasplots:plotarea", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                        if (ParametersList.count()<4) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            if (ParametersList[0].replace(",","").toDouble()<-180. || ParametersList[0].replace(",","").toDouble()>180.) {
                                warningString += "Minimum longitude in parameter '" + option + "' has to be between -180 and 180 degrees. It was skipped.\n";
                            } else if (ParametersList[1].replace(",","").toDouble()<-180. || ParametersList[1].replace(",","").toDouble()>180.) {
                                warningString += "Maximum longitude in parameter '" + option + "' has to be between -180 and 180 degrees. It was skipped.\n";
                            } else if (ParametersList[0].replace(",","").toDouble()>=ParametersList[1].replace(",","").toDouble()) {
                                warningString += "Maximum longitude in parameter '" + option + "' must be greater than the minimum longitude.\n";
                            } else if (ParametersList[2].replace(",","").toDouble()<-90. || ParametersList[2].replace(",","").toDouble()>90.) {
                                warningString += "Minimum latitude in parameter '" + option + "' has to be between -90 and 90 degrees. It was skipped.\n";
                            } else if (ParametersList[3].replace(",","").toDouble()<-90. || ParametersList[3].replace(",","").toDouble()>90.) {
                                warningString += "Maximum latitude in parameter '" + option + "' has to be between -90 and 90 degrees. It was skipped.\n";
                            } else if (ParametersList[2].replace(",","").toDouble()>=ParametersList[3].replace(",","").toDouble()) {
                                warningString += "Maximum latitude in parameter '" + option + "' must be greater than the minimum latitude.\n";
                            } else {
                                warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-sbasplots:exclusionarea", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                        if (ParametersList.count()<4) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            if (ParametersList[0].replace(",","").toDouble()<-180. || ParametersList[0].replace(",","").toDouble()>180.) {
                                warningString += "Minimum longitude in parameter '" + option + "' has to be between -180 and 180 degrees. It was skipped.\n";
                            } else if (ParametersList[1].replace(",","").toDouble()<-180. || ParametersList[1].replace(",","").toDouble()>180.) {
                                warningString += "Maximum longitude in parameter '" + option + "' has to be between -180 and 180 degrees. It was skipped.\n";
                            } else if (ParametersList[0].replace(",","").toDouble()>=ParametersList[1].replace(",","").toDouble()) {
                                warningString += "Maximum longitude in parameter '" + option + "' must be greater than the minimum longitude.\n";
                            } else if (ParametersList[2].replace(",","").toDouble()<-90. || ParametersList[2].replace(",","").toDouble()>90.) {
                                warningString += "Minimum latitude in parameter '" + option + "' has to be between -90 and 90 degrees. It was skipped.\n";
                            } else if (ParametersList[3].replace(",","").toDouble()<-90. || ParametersList[3].replace(",","").toDouble()>90.) {
                                warningString += "Maximum latitude in parameter '" + option + "' has to be between -90 and 90 degrees. It was skipped.\n";
                            } else if (ParametersList[2].replace(",","").toDouble()>=ParametersList[3].replace(",","").toDouble()) {
                                warningString += "Maximum latitude in parameter '" + option + "' must be greater than the minimum latitude.\n";
                            } else {
                                warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-sbasplots:inclusionarea", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(4,&warningString,option,ParametersList);
                        if (ParametersList.count()<4) {
                            warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
                        } else {
                            if (ParametersList[0].replace(",","").toDouble()<-180. || ParametersList[0].replace(",","").toDouble()>180.) {
                                warningString += "Minimum longitude in parameter '" + option + "' has to be between -180 and 180 degrees. It was skipped.\n";
                            } else if (ParametersList[1].replace(",","").toDouble()<-180. || ParametersList[1].replace(",","").toDouble()>180.) {
                                warningString += "Maximum longitude in parameter '" + option + "' has to be between -180 and 180 degrees. It was skipped.\n";
                            } else if (ParametersList[0].replace(",","").toDouble()>=ParametersList[1].replace(",","").toDouble()) {
                                warningString += "Maximum longitude in parameter '" + option + "' must be greater than the minimum longitude.\n";
                            } else if (ParametersList[2].replace(",","").toDouble()<-90. || ParametersList[2].replace(",","").toDouble()>90.) {
                                warningString += "Minimum latitude in parameter '" + option + "' has to be between -90 and 90 degrees. It was skipped.\n";
                            } else if (ParametersList[3].replace(",","").toDouble()<-90. || ParametersList[3].replace(",","").toDouble()>90.) {
                                warningString += "Maximum latitude in parameter '" + option + "' has to be between -90 and 90 degrees. It was skipped.\n";
                            } else if (ParametersList[2].replace(",","").toDouble()>=ParametersList[3].replace(",","").toDouble()) {
                                warningString += "Maximum latitude in parameter '" + option + "' must be greater than the minimum latitude.\n";
                            } else {
                                warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                            }
                        }
                    } else if ( QString::compare(option, "-sbasplots:hourlymaps", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:hourlymaps", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbasplots:noAvailPlot", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:noAvailPlot", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbasplots:noRiskPlot", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:noRiskPlot", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbasplots:noIonoPlot", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:noIonoPlot", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:noIonoModel", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbasplots:hdopplot", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:hdopplot", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbasplots:pdopplot", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:pdopplot", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbasplots:gdopplot", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:gdopplot", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbasplots:combdopplot", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:combdopplot", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-sbasplots:doppercentile", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "--sbasplots:doppercentile", Qt::CaseInsensitive)==0 ) {
                        extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
                        warningString += "Parameter '" + option + "' is for SBAS plots mode (which is not available in the GUI). It was skipped.\n";
                    } else if ( QString::compare(option, "-output:sbasavailplots", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:sbasriskmarplots", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:sbasriskplots", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:sbasriskdisc", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:sbasionoplots", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:sbashdopplots", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:sbaspdopplots", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:sbasgdopplots", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else if ( QString::compare(option, "-output:sbascombdopplots", Qt::CaseInsensitive)==0 ) {
                        //Warning already set in the first loop
                    } else {
                        warningString += "Parameter '" + option + "' is not recognized. It was skipped.\n";
                    }
                }
                file.close();
                //:dcb groupbox
                for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++){
                    if ( DCBGNSS[iGNSS]>0 && GroupBoxGNSSDCB[iGNSS]!=nullptr ) {
                        this->on_groupBoxShowDCBOptions_clicked(true);
                        (this->*GroupBoxGNSSDCB[iGNSS])(true);
                    } else if ( DCBGNSS[iGNSS]<=0 && GroupBoxGNSSDCB[iGNSS]!=nullptr ) (this->*GroupBoxGNSSDCB[iGNSS])(false);
                }

                //Parse '-pre:smoothMeas' before '-filter:select'
                if (smoothMeasParam==1) {
                    this->readGNSSSmoothFreqMeas(&warningString,&smoothMeasParamList);
                }
                //Parse '-filter:select' after '-pre:smoothMeas'
                if (filterSelectParamProvided==1) {
                    this->readGNSSFreqMeas(&warningString,&filterSelectParam);
                    //If '-pre:smoothmeas' is provided, check '-pre:smoothmeas' code measurements are provided also in '-filter:select'
                    if ( GNSSMeasCMDMode==MEAS_MODE_SMOOTH ) {
                        this->checkSmoothFilterMeasInFilterMeas(&warningString,&filterSelectParam);
                    }
                }
                //Read the weight parameters at the end, so they are always processed after reading '-filter:select' or '-pre:smoothmeas'
                if (fixedWeightProvided==1) {
                    this->readGNSSStdDev(&warningString,&fixedWeightParam,0);
                }
                if (elevWeightProvided==1) {
                    this->readGNSSStdDev(&warningString,&elevWeightParam,1);
                }
                if (elevSinWeightProvided==1) {
                    this->readGNSSStdDev(&warningString,&elevSinWeightParam,2);
                }
                if (snrWeightProvided==1) {
                    this->readGNSSStdDev(&warningString,&snrWeightParam,3);
                }
                if (snrElevWeightProvided==1) {
                    this->readGNSSStdDev(&warningString,&snrElevWeightParam,4);
                }
                //Change constellation to Galileo and then back to GPS
                //This is to make sure the "+" and "-" buttons to add or remove measurements get correctly updated according to the number of measurements
                this->on_pushButtonGalileoMeasurements_clicked();
                this->on_pushButtonGPSMeasurements_clicked();
                //Parse IGF frequencies and measurements after option '-pre:cs:igf:minnoise'
                if ( IGFFreqProvided==1 ) {
                    CSAdvancedIGF->loadgLABOptions(&warningString,&IGFFreqParamList,1,ui->radioButtonIGFMinimumNoise);
                }
                if ( IGFMeasProvided==1 ) {
                    CSAdvancedIGF->loadgLABOptions(&warningString,&IGFMeasParamList,2,ui->radioButtonIGFMinimumNoise);
                }
                //Parse MEAS print measurements
                if (MeasPrintParamProvided==1) {
                    this->on_checkBoxPrintMeas_clicked(true);
                    this->on_radioButtonMeasSelectSpecify_clicked();
                    MeasSelectGNSS->loadgLABOptions(&warningString,&MeasPrintParamList);
                }

                //If both min and max SNR are provided, check that these values are consistent
                if (minSNRSelProvided==1 && maxSNRSelProvided==1) {
                    this->checkMinMaxSNRThresholds(&warningString);
                }


                if ( !warningString.isEmpty() ) {
                    messageBox.setWindowTitle("Errors found");
                    messageBox.setText("gLAB loaded the configuration file, but found the following errors:\n\n" + warningString);
                    messageBox.setIcon(QMessageBox::Warning);
                    QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
                    QGridLayout* layout = static_cast<QGridLayout*>(messageBox.layout());
                    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
                    messageBox.exec();
                }
            }
        }
    }
}
