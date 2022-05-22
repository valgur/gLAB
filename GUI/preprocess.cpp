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

//Function to initialize pointers to pushButton "clicked function" pointers
void gLAB_GUI::InitPushButtonsFuncPointers() {
    PushButtonSatFunctions[GPS][1]=&gLAB_GUI::on_pushButtonG1_clicked;
    PushButtonSatFunctions[GPS][2]=&gLAB_GUI::on_pushButtonG2_clicked;
    PushButtonSatFunctions[GPS][3]=&gLAB_GUI::on_pushButtonG3_clicked;
    PushButtonSatFunctions[GPS][4]=&gLAB_GUI::on_pushButtonG4_clicked;
    PushButtonSatFunctions[GPS][5]=&gLAB_GUI::on_pushButtonG5_clicked;
    PushButtonSatFunctions[GPS][6]=&gLAB_GUI::on_pushButtonG6_clicked;
    PushButtonSatFunctions[GPS][7]=&gLAB_GUI::on_pushButtonG7_clicked;
    PushButtonSatFunctions[GPS][8]=&gLAB_GUI::on_pushButtonG8_clicked;
    PushButtonSatFunctions[GPS][9]=&gLAB_GUI::on_pushButtonG9_clicked;
    PushButtonSatFunctions[GPS][10]=&gLAB_GUI::on_pushButtonG10_clicked;
    PushButtonSatFunctions[GPS][11]=&gLAB_GUI::on_pushButtonG11_clicked;
    PushButtonSatFunctions[GPS][12]=&gLAB_GUI::on_pushButtonG12_clicked;
    PushButtonSatFunctions[GPS][13]=&gLAB_GUI::on_pushButtonG13_clicked;
    PushButtonSatFunctions[GPS][14]=&gLAB_GUI::on_pushButtonG14_clicked;
    PushButtonSatFunctions[GPS][15]=&gLAB_GUI::on_pushButtonG15_clicked;
    PushButtonSatFunctions[GPS][16]=&gLAB_GUI::on_pushButtonG16_clicked;
    PushButtonSatFunctions[GPS][17]=&gLAB_GUI::on_pushButtonG17_clicked;
    PushButtonSatFunctions[GPS][18]=&gLAB_GUI::on_pushButtonG18_clicked;
    PushButtonSatFunctions[GPS][19]=&gLAB_GUI::on_pushButtonG19_clicked;
    PushButtonSatFunctions[GPS][20]=&gLAB_GUI::on_pushButtonG20_clicked;
    PushButtonSatFunctions[GPS][21]=&gLAB_GUI::on_pushButtonG21_clicked;
    PushButtonSatFunctions[GPS][22]=&gLAB_GUI::on_pushButtonG22_clicked;
    PushButtonSatFunctions[GPS][23]=&gLAB_GUI::on_pushButtonG23_clicked;
    PushButtonSatFunctions[GPS][24]=&gLAB_GUI::on_pushButtonG24_clicked;
    PushButtonSatFunctions[GPS][25]=&gLAB_GUI::on_pushButtonG25_clicked;
    PushButtonSatFunctions[GPS][26]=&gLAB_GUI::on_pushButtonG26_clicked;
    PushButtonSatFunctions[GPS][27]=&gLAB_GUI::on_pushButtonG27_clicked;
    PushButtonSatFunctions[GPS][28]=&gLAB_GUI::on_pushButtonG28_clicked;
    PushButtonSatFunctions[GPS][29]=&gLAB_GUI::on_pushButtonG29_clicked;
    PushButtonSatFunctions[GPS][30]=&gLAB_GUI::on_pushButtonG30_clicked;
    PushButtonSatFunctions[GPS][31]=&gLAB_GUI::on_pushButtonG31_clicked;
    PushButtonSatFunctions[GPS][32]=&gLAB_GUI::on_pushButtonG32_clicked;

    //To be completed with further constellations
}

//Function to initialize pointers to pushButton widget pointers
void gLAB_GUI::InitPushButtonsWidgetPointers() {
    PushButtonSatWidgets[GPS][1] = ui->pushButtonG1;
    PushButtonSatWidgets[GPS][2] = ui->pushButtonG2;
    PushButtonSatWidgets[GPS][3] = ui->pushButtonG3;
    PushButtonSatWidgets[GPS][4] = ui->pushButtonG4;
    PushButtonSatWidgets[GPS][5] = ui->pushButtonG5;
    PushButtonSatWidgets[GPS][6] = ui->pushButtonG6;
    PushButtonSatWidgets[GPS][7] = ui->pushButtonG7;
    PushButtonSatWidgets[GPS][8] = ui->pushButtonG8;
    PushButtonSatWidgets[GPS][9] = ui->pushButtonG9;
    PushButtonSatWidgets[GPS][10] = ui->pushButtonG10;
    PushButtonSatWidgets[GPS][11] = ui->pushButtonG11;
    PushButtonSatWidgets[GPS][12] = ui->pushButtonG12;
    PushButtonSatWidgets[GPS][13] = ui->pushButtonG13;
    PushButtonSatWidgets[GPS][14] = ui->pushButtonG14;
    PushButtonSatWidgets[GPS][15] = ui->pushButtonG15;
    PushButtonSatWidgets[GPS][16] = ui->pushButtonG16;
    PushButtonSatWidgets[GPS][17] = ui->pushButtonG17;
    PushButtonSatWidgets[GPS][18] = ui->pushButtonG18;
    PushButtonSatWidgets[GPS][19] = ui->pushButtonG19;
    PushButtonSatWidgets[GPS][20] = ui->pushButtonG20;
    PushButtonSatWidgets[GPS][21] = ui->pushButtonG21;
    PushButtonSatWidgets[GPS][22] = ui->pushButtonG22;
    PushButtonSatWidgets[GPS][23] = ui->pushButtonG23;
    PushButtonSatWidgets[GPS][24] = ui->pushButtonG24;
    PushButtonSatWidgets[GPS][25] = ui->pushButtonG25;
    PushButtonSatWidgets[GPS][26] = ui->pushButtonG26;
    PushButtonSatWidgets[GPS][27] = ui->pushButtonG27;
    PushButtonSatWidgets[GPS][28] = ui->pushButtonG28;
    PushButtonSatWidgets[GPS][29] = ui->pushButtonG29;
    PushButtonSatWidgets[GPS][30] = ui->pushButtonG30;
    PushButtonSatWidgets[GPS][31] = ui->pushButtonG31;
    PushButtonSatWidgets[GPS][32] = ui->pushButtonG32;

    //To be completed with further constellations

}

// Function to show or hide the line edit for data decimator
void gLAB_GUI::on_checkBoxDataDecimator_clicked(bool checked) {
    ui->checkBoxDataDecimator->setChecked(checked);
    ui->frameDataDecimator->setHidden(!checked);
}


// Function to set all GPS satellites available
void gLAB_GUI::on_pushButtonGPSSatSelAll_clicked() {
    int i;
    for(i=1;i<=MAX_SAT_GPS;i++) {
        PushButtonSatWidgets[GPS][i]->setStyleSheet(QString("background-color:%1; color:black;").arg(GreenColor));
    }
}

// Function to set all GPS satellites unavailable
void gLAB_GUI::on_pushButtonGPSSatSelNone_clicked() {
    int i;
    for(i=1;i<=MAX_SAT_GPS;i++) {
        PushButtonSatWidgets[GPS][i]->setStyleSheet(QString("background-color:%1; color:black;").arg(RedColor));
    }
}

// Button for GPS PRN 1
void gLAB_GUI::on_pushButtonG1_clicked() {
    QColor col = ui->pushButtonG1->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG1->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG1->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 2
void gLAB_GUI::on_pushButtonG2_clicked() {
    QColor col = ui->pushButtonG2->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG2->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG2->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 3
void gLAB_GUI::on_pushButtonG3_clicked() {
    QColor col = ui->pushButtonG3->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG3->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG3->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 4
void gLAB_GUI::on_pushButtonG4_clicked() {
    QColor col = ui->pushButtonG4->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG4->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG4->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 5
void gLAB_GUI::on_pushButtonG5_clicked() {
    QColor col = ui->pushButtonG5->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG5->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG5->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 6
void gLAB_GUI::on_pushButtonG6_clicked() {
    QColor col = ui->pushButtonG6->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG6->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG6->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 7
void gLAB_GUI::on_pushButtonG7_clicked() {
    QColor col = ui->pushButtonG7->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG7->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG7->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 8
void gLAB_GUI::on_pushButtonG8_clicked() {
    QColor col = ui->pushButtonG8->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG8->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG8->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 9
void gLAB_GUI::on_pushButtonG9_clicked() {
    QColor col = ui->pushButtonG9->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG9->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG9->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 10
void gLAB_GUI::on_pushButtonG10_clicked() {
    QColor col = ui->pushButtonG10->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG10->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG10->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 11
void gLAB_GUI::on_pushButtonG11_clicked() {
    QColor col = ui->pushButtonG11->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG11->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG11->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 12
void gLAB_GUI::on_pushButtonG12_clicked() {
    QColor col = ui->pushButtonG12->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG12->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG12->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 13
void gLAB_GUI::on_pushButtonG13_clicked() {
    QColor col = ui->pushButtonG13->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG13->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG13->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 14
void gLAB_GUI::on_pushButtonG14_clicked() {
    QColor col = ui->pushButtonG14->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG14->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG14->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 15
void gLAB_GUI::on_pushButtonG15_clicked() {
    QColor col = ui->pushButtonG15->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG15->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG15->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 16
void gLAB_GUI::on_pushButtonG16_clicked() {
    QColor col = ui->pushButtonG16->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG16->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG16->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 17
void gLAB_GUI::on_pushButtonG17_clicked() {
    QColor col = ui->pushButtonG17->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG17->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG17->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 18
void gLAB_GUI::on_pushButtonG18_clicked() {
    QColor col = ui->pushButtonG18->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG18->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG18->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 19
void gLAB_GUI::on_pushButtonG19_clicked() {
    QColor col = ui->pushButtonG19->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG19->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG19->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 20
void gLAB_GUI::on_pushButtonG20_clicked() {
    QColor col = ui->pushButtonG20->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG20->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG20->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 21
void gLAB_GUI::on_pushButtonG21_clicked() {
    QColor col = ui->pushButtonG21->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG21->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG21->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 22
void gLAB_GUI::on_pushButtonG22_clicked() {
    QColor col = ui->pushButtonG22->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG22->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG22->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 23
void gLAB_GUI::on_pushButtonG23_clicked() {
    QColor col = ui->pushButtonG23->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG23->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG23->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 24
void gLAB_GUI::on_pushButtonG24_clicked() {
    QColor col = ui->pushButtonG24->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG24->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG24->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 25
void gLAB_GUI::on_pushButtonG25_clicked() {
    QColor col = ui->pushButtonG25->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG25->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG25->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 26
void gLAB_GUI::on_pushButtonG26_clicked() {
    QColor col = ui->pushButtonG26->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG26->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG26->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 27
void gLAB_GUI::on_pushButtonG27_clicked() {
    QColor col = ui->pushButtonG27->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG27->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG27->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 28
void gLAB_GUI::on_pushButtonG28_clicked() {
    QColor col = ui->pushButtonG28->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG28->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG28->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 29
void gLAB_GUI::on_pushButtonG29_clicked() {
    QColor col = ui->pushButtonG29->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG29->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG29->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 30
void gLAB_GUI::on_pushButtonG30_clicked() {
    QColor col = ui->pushButtonG30->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG30->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG30->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 31
void gLAB_GUI::on_pushButtonG31_clicked() {
    QColor col = ui->pushButtonG31->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG31->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG31->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

// Button for GPS PRN 32
void gLAB_GUI::on_pushButtonG32_clicked() {
    QColor col = ui->pushButtonG32->palette().background().color();
    if ( col.name() == GreenColor ) ui->pushButtonG32->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG32->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
}

//Given satellite PRN and constellation, function to call its corresponding pushbutton function
void gLAB_GUI::callSatellitePushButtonFunction(enum GNSSystem System, int PRN, QString Sign) {
    if (PushButtonSatWidgets[System][PRN]->palette().background().color().name()!=Sign) {
        //Only change colour if is not in the correct colour
        (this->*PushButtonSatFunctions[System][PRN])();
    }
}

// Function to show or hide Ncon number of samples
void gLAB_GUI::on_checkBoxNcon_clicked(bool checked) {
    ui->checkBoxNcon->setChecked(checked);
    ui->frameNcon->setHidden(!checked);
}

// Function to show or hide SNR threshold
void gLAB_GUI::on_checkBoxDiscardSNRThreshold_clicked(bool checked) {
    ui->checkBoxDiscardSNRThreshold->setChecked(checked);
    ui->framecomboBoxSNRThreshold->setHidden(!checked);
}

//Function to show or hide text box for user defined SNR threshold when SNR combo box changes
void gLAB_GUI::on_comboBoxSNRThresholds_currentIndexChanged(int index) {
    ui->comboBoxSNRThresholds->setCurrentIndex(index);
    if(ui->comboBoxSNRThresholds->currentText()=="Specify") {
        ui->lineEditUserDefinedSNR->setHidden(false);
    } else {
        ui->lineEditUserDefinedSNR->setHidden(true);
    }
}

// Function to configure the L1-C1 cycle-slip detector parameters
void gLAB_GUI::on_pushButtonConfigureL1C1_clicked() {
    if (ui->stackedWidgetCSdetectionParameters->currentIndex() == 1) ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
    else ui->stackedWidgetCSdetectionParameters->setCurrentIndex(1);
}

// Function to show L1-C1 Consistency check threshold
void gLAB_GUI::on_checkBoxL1C1ConsistencyCheck_clicked(bool checked) {
    ui->checkBoxL1C1ConsistencyCheck->setChecked(checked);
    ui->frameL1C1ConsCheckValue->setHidden(!checked);
}


// Function to configure the Melbourne-Wübbena cycle-slip detector parameters
void gLAB_GUI::on_pushButtonConfigureMW_clicked() {
    if (ui->stackedWidgetCSdetectionParameters->currentIndex() == 2) ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
    else ui->stackedWidgetCSdetectionParameters->setCurrentIndex(2);
}

// Function to configure the Geometry-free cycle-slip detector parameters
void gLAB_GUI::on_pushButtonConfigureLI_clicked() {
    if (ui->stackedWidgetCSdetectionParameters->currentIndex() == 3) ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
    else ui->stackedWidgetCSdetectionParameters->setCurrentIndex(3);
}


// Function to set the cycle-slip defaults
void gLAB_GUI::setCSdefaults() {
    //N-con
    ui->lineEditNcon->setText("3");
    // L1-C1
    this->on_checkBoxL1C1ConsistencyCheck_clicked(true);
    ui->lineEditL1C1ConsCheckValue->setText("20");
    ui->lineEditL1C1iniStd->setText("3");
    ui->lineEditL1C1window->setText("300");
    ui->lineEditL1C1kFactor->setText("5");
    ui->lineEditL1C1nSample->setText("2");    
    // Melbourne-Wübbena
    ui->lineEditIntialStdDevBW->setText("2");
    ui->lineEditMWminStd->setText("0.8");
    ui->lineEditMWwindow->setText("300");
    ui->lineEditMWkFactor->setText("5");
    ui->lineEditMWnSample->setText("2");
    // Geometry-free
    ui->lineEditLImaxJumpThreshold->setText("1");
    ui->lineEditLImaxThreshold->setText("0.08");
    ui->lineEditLItimeConstant->setText("60");
    ui->lineEditLInSamples->setText("7");
}

// Function to get the PREPROCESS options and errors
void gLAB_GUI::getPreprocessOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString) {
    int         i,j;
    int         conditionsmet;
    int         badDate=0;
    int         FirstSat,StartedGroup;
    QDate       date;
    QTime       time;
    QString     RtcmNavMode;
    const int   listMaxSatGNSS[MAX_GNSS]={MAX_SAT_GPS,MAX_SAT_GAL,MAX_SAT_GLO,MAX_SAT_GEO,MAX_SAT_BDS,MAX_SAT_QZS,MAX_SAT_IRN};

    *warningString = *warningString + ""; //This is to avoid the unused parameter warning
    // Header of the Preprocess section
    *saveString += "\n";
    *saveString += "###################################################\n";
    *saveString += "#     PREPROCESS section\n";
    *saveString += "###################################################\n\n";
    // A priori Receiver Position From:
    if ( ui->radioButtonRinex->isChecked() == true ) {
        //RINEX position is the default in gLAB, no need to set the argument
        if (WriteAllParameters==1) {
            *saveString += "-pre:setrecpos RINEX\n";
            *runString << "-pre:setrecpos" << "RINEX";
        }
    } else if ( ui->radioButtonCalculate->isChecked() == true ) {
        if (ui->checkBoxReferencePositionFileCalculate->isChecked()==true) {
            if (ui->lineEditInterpolationDegreeRefFileCalculate->text()=="") {
                *errorString += "INPUT: Reference position interpolation degree is a required input if 'Reference Position File:' is set in 'Calculate' mode [In the Input Section - A Priori Receiver Position From] .\n";
            } else {
                if (ui->lineEditInterpolationDegreeRefFileCalculate->text().toInt()==0) {
                    //Default interpolation value is 0
                    if (WriteAllParameters==1) {
                        *saveString += "-pre:refpos:deg " + ui->lineEditInterpolationDegreeRefFileCalculate->text() + "\n";
                        *runString << "-pre:refpos:deg" << ui->lineEditInterpolationDegreeRefFileCalculate->text();
                    }
                } else {
                    *saveString += "-pre:refpos:deg " + ui->lineEditInterpolationDegreeRefFileCalculate->text() + "\n";
                    *runString << "-pre:refpos:deg" << ui->lineEditInterpolationDegreeRefFileCalculate->text();
                }
            }
        }
        if ( ui->radioButtonCalculateEarthCentre->isChecked() == true ) {
            if (ui->checkBoxReferencePositionFileCalculate->isChecked()==true) {
                if (WriteAllParameters==1) {
                    //calculateRef mode is the default when an input ref file is set
                    *saveString += "-pre:setrecpos calculateRef\n";
                    *runString << "-pre:setrecpos" << "calculateRef";
                }
            } else {
                *saveString += "-pre:setrecpos calculate\n";
                *runString << "-pre:setrecpos" << "calculate";
            }

        } else if ( ui->radioButtonCalculateRinex->isChecked() == true ) {
            if (ui->checkBoxReferencePositionFileCalculate->isChecked()==true) {
                *saveString += "-pre:setrecpos calculateRINEXRef\n";
                *runString << "-pre:setrecpos" << "calculateRINEXRef";
            } else {
                *saveString += "-pre:setrecpos calculateRINEX\n";
                *runString << "-pre:setrecpos" << "calculateRINEX";
            }
        } else if ( ui->radioButtonCalculateSpecify->isChecked() == true ) {
            if (ui->radioButtonCalculateSpecifyCartesian->isChecked()==true) {
                if ( ui->lineEditCalculateSpecifyX->text() == "" || ui->lineEditCalculateSpecifyY->text() == "" || ui->lineEditCalculateSpecifyZ->text() == "" ) {
                    *errorString += "INPUT: X Y and Z coordinates are required inputs if 'Calculate - User defined' is set [In the Input Section - A Priori Receiver Position From].\n";
                } else if ( ui->lineEditCalculateSpecifyX->text().toDouble() == 0. || ui->lineEditCalculateSpecifyY->text().toDouble() == 0. || ui->lineEditCalculateSpecifyZ->text().toDouble() == 0. ) {
                        *errorString += "INPUT: X Y and Z coordinates cannot be 0,0,0.\n";
                } else {
                    if (ui->checkBoxReferencePositionFileCalculate->isChecked()==true) {
                        *saveString += "-pre:setrecpos calculateUSERRef " + ui->lineEditCalculateSpecifyX->text() + " " + ui->lineEditCalculateSpecifyY->text() + " " + ui->lineEditCalculateSpecifyZ->text() + "\n";
                        *runString << "-pre:setrecpos" << "calculateUSERRef" << ui->lineEditCalculateSpecifyX->text() << ui->lineEditCalculateSpecifyY->text() << ui->lineEditCalculateSpecifyZ->text();
                    } else {
                        *saveString += "-pre:setrecpos calculateUSER " + ui->lineEditCalculateSpecifyX->text() + " " + ui->lineEditCalculateSpecifyY->text() + " " + ui->lineEditCalculateSpecifyZ->text() + "\n";
                        *runString << "-pre:setrecpos" << "calculateUSER" << ui->lineEditCalculateSpecifyX->text() << ui->lineEditCalculateSpecifyY->text() << ui->lineEditCalculateSpecifyZ->text();
                    }
                }
            } else {
                if ( ui->lineEditCalculateSpecifyLon->text() == "" || ui->lineEditCalculateSpecifyLat->text() == "" || ui->lineEditCalculateSpecifyHeight->text() == "" ) {
                    *errorString += "INPUT: Longitude, latitude and height coordinates are required inputs if 'Calculate - User defined' is set [In the Input Section - A Priori Receiver Position From].\n";
                } else if  (ui->lineEditCalculateSpecifyLon->text().toDouble()<-180. || ui->lineEditCalculateSpecifyLon->text().toDouble()>180) {
                        *errorString += "INPUT: Longitude coordinate must be in the range [-180..180] degrees.\n";
                } else if  (ui->lineEditCalculateSpecifyLat->text().toDouble()<-90. || ui->lineEditCalculateSpecifyLat->text().toDouble()>90) {
                        *errorString += "INPUT: Latitude coordinate must be in the range [-90..90] degrees.\n";
                } else if ( ui->lineEditCalculateSpecifyHeight->text().toDouble() < -10000. ) {
                        *errorString += "INPUT: Height coordinate cannot be lower than -10 kilometres.\n";
                } else {
                    if (ui->checkBoxReferencePositionFileCalculate->isChecked()==true) {
                        *saveString += "-pre:setrecpos calculateUSERGeodRef " + ui->lineEditCalculateSpecifyLon->text() + " " + ui->lineEditCalculateSpecifyLat->text() + " " + ui->lineEditCalculateSpecifyHeight->text() + "\n";
                        *runString << "-pre:setrecpos" << "calculateUSERGeodRef" << ui->lineEditCalculateSpecifyLon->text() << ui->lineEditCalculateSpecifyLat->text() << ui->lineEditCalculateSpecifyHeight->text();
                    } else {
                        *saveString += "-pre:setrecpos calculateUSERGeod " + ui->lineEditCalculateSpecifyLon->text() + " " + ui->lineEditCalculateSpecifyLat->text() + " " + ui->lineEditCalculateSpecifyHeight->text() + "\n";
                        *runString << "-pre:setrecpos" << "calculateUSERGeod" << ui->lineEditCalculateSpecifyLon->text() << ui->lineEditCalculateSpecifyLat->text() << ui->lineEditCalculateSpecifyHeight->text();
                    }
                }
            }
        }
    } else if ( ui->radioButtonSinex->isChecked() == true ) {
        *saveString += "-pre:setrecpos SINEX\n";
        *runString << "-pre:setrecpos" << "SINEX";
    } else if ( ui->radioButtonRtcm->isChecked() == true ) {
        if ((ui->radioButtonRtcmSpecify->isChecked()==true || ui->radioButtonRtcmUserSpecify->isChecked()==true) && ui->radioButtonRtcmReferenceFile->isChecked()==true) {
            if (ui->radioButtonRtcmSpecify->isChecked()==true) {
                RtcmNavMode="Specify Rover";
            } else {
                RtcmNavMode="User Ref. & Rover";
            }
            if (ui->lineEditInterpolationDegreeRefFileRtcm->text()=="") {
                *errorString += "INPUT: Reference position interpolation degree is a required input if 'Reference file:' is set in '" + RtcmNavMode + "' mode [In the Input Section - A Priori Receiver Position From] .\n";
            } else {
                if (ui->lineEditInterpolationDegreeRefFileRtcm->text().toInt()==0) {
                    //Default interpolation value is 0
                    if (WriteAllParameters==1) {
                        *saveString += "-pre:refpos:deg " + ui->lineEditInterpolationDegreeRefFileRtcm->text() + "\n";
                        *runString << "-pre:refpos:deg" << ui->lineEditInterpolationDegreeRefFileRtcm->text();
                    }
                } else {
                    *saveString += "-pre:refpos:deg " + ui->lineEditInterpolationDegreeRefFileRtcm->text() + "\n";
                    *runString << "-pre:refpos:deg" << ui->lineEditInterpolationDegreeRefFileRtcm->text();
                }
            }
        }
        if ( ui->radioButtonRtcmBaseline->isChecked() == true ) {
            //DGNSS Baseline is the default for DGNSS, no need to set the argument
             if (WriteAllParameters==1) {
                *saveString += "-pre:setrecpos DGNSSbaseline\n";
                *runString << "-pre:setrecpos" << "DGNSSbaseline";
             }
        } else if ( ui->radioButtonRtcmRinexRover->isChecked() == true ) {
            *saveString += "-pre:setrecpos DGNSSRinexRover\n";
            *runString << "-pre:setrecpos" << "DGNSSRinexRover";
        } else if ( ui->radioButtonRtcmSpecify->isChecked() == true ) {
                if ( ui->radioButtonRtcmUserDefined->isChecked()==true ) {
                    if (ui->radioButtonRtcmRecCartesian->isChecked()==true) {
                        if ( ui->lineEditAprioriRecPosRtcmSpecifyX->text() == "" || ui->lineEditAprioriRecPosRtcmSpecifyY->text() == "" || ui->lineEditAprioriRecPosRtcmSpecifyZ->text() == "" ) {
                            *errorString += "INPUT: Rover X Y and Z coordinates are required inputs if 'DGNSS - Specify Rover - User defined' is set [In the Input Section - A Priori Receiver Position From].\n";
                        } else if ( ui->lineEditAprioriRecPosRtcmSpecifyX->text().toDouble() == 0. || ui->lineEditAprioriRecPosRtcmSpecifyY->text().toDouble() == 0. || ui->lineEditAprioriRecPosRtcmSpecifyZ->text().toDouble() == 0. ) {
                            *errorString += "INPUT: Rover X Y and Z coordinates cannot be 0,0,0.\n";
                        } else {
                            *saveString += "-pre:setrecpos DGNSSRoverUSER " + ui->lineEditAprioriRecPosRtcmSpecifyX->text() + " " + ui->lineEditAprioriRecPosRtcmSpecifyY->text() + " " + ui->lineEditAprioriRecPosRtcmSpecifyZ->text() + "\n";
                            *runString << "-pre:setrecpos" << "DGNSSRoverUSER" << ui->lineEditAprioriRecPosRtcmSpecifyX->text() << ui->lineEditAprioriRecPosRtcmSpecifyY->text() << ui->lineEditAprioriRecPosRtcmSpecifyZ->text();
                        }
                    } else {
                        if ( ui->lineEditAprioriRecPosRtcmSpecifyLon->text() == "" || ui->lineEditAprioriRecPosRtcmSpecifyLat->text() == "" || ui->lineEditAprioriRecPosRtcmSpecifyHeight->text() == "" ) {
                            *errorString += "INPUT: Longitude, latitude and height coordinates are required inputs if 'DGNSS - Specify Rover - User defined' is set [In the Input Section - A Priori Receiver Position From].\n";
                        } else if  (ui->lineEditAprioriRecPosRtcmSpecifyLon->text().toDouble()<-180. || ui->lineEditAprioriRecPosRtcmSpecifyLon->text().toDouble()>180) {
                                *errorString += "INPUT: Longitude coordinate must be in the range [-180..180] degrees.\n";
                        } else if  (ui->lineEditAprioriRecPosRtcmSpecifyLat->text().toDouble()<-90. || ui->lineEditAprioriRecPosRtcmSpecifyLat->text().toDouble()>90) {
                                *errorString += "INPUT: Latitude coordinate must be in the range [-90..90] degrees.\n";
                        } else if ( ui->lineEditAprioriRecPosRtcmSpecifyHeight->text().toDouble() < -10000. ) {
                                *errorString += "INPUT: Height coordinate cannot be lower than -10 kilometres.\n";
                        } else {
                                *saveString += "-pre:setrecpos DGNSSRoverUSERGeod " + ui->lineEditAprioriRecPosRtcmSpecifyLon->text() + " " + ui->lineEditAprioriRecPosRtcmSpecifyLat->text() + " " + ui->lineEditAprioriRecPosRtcmSpecifyHeight->text() + "\n";
                                *runString << "-pre:setrecpos" << "DGNSSRoverUSERGeod" << ui->lineEditAprioriRecPosRtcmSpecifyLon->text() << ui->lineEditAprioriRecPosRtcmSpecifyLat->text() << ui->lineEditCalculateSpecifyHeight->text();
                        }
                    }
                } else {
                    *saveString += "-pre:setrecpos DGNSSRoverUSERRef\n";
                    *runString << "-pre:setrecpos" << "DGNSSRoverUSERRef";
                }
        } else if ( ui->radioButtonRtcmUserBaseline->isChecked() == true ) {
            if (ui->radioButtonRtcmRefCartesian->isChecked()==true) {
                if ( ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() == "" ) {
                    *errorString += "INPUT: Reference Station X Y and Z coordinates are required inputs if 'DGNSS - User Baseline' is set [In the Input Section - A Priori Receiver Position From].\n";
                } else if (ui->lineEditAprioriRefRecPosRtcmSpecifyX->text().toDouble() == 0. || ui->lineEditAprioriRefRecPosRtcmSpecifyY->text().toDouble() == 0. || ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text().toDouble() == 0.) {
                    *errorString += "INPUT: Reference Station X Y and Z coordinates cannot be 0,0,0.\n";
                } else {
                    *saveString += "-pre:setrecpos DGNSSUserbaseline " + ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() + "\n";
                    *runString << "-pre:setrecpos" << "DGNSSUserbaseline" << ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text();
                }
            } else {
                if ( ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() == "" ) {
                    *errorString += "INPUT: Longitude, latitude and height coordinates are required inputs if 'DGNSS - User Baseline' is set [In the Input Section - A Priori Receiver Position From].\n";
                } else if  (ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text().toDouble()<-180. || ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text().toDouble()>180) {
                        *errorString += "INPUT: Longitude coordinate must be in the range [-180..180] degrees.\n";
                } else if  (ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text().toDouble()<-90. || ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text().toDouble()>90) {
                        *errorString += "INPUT: Latitude coordinate must be in the range [-90..90] degrees.\n";
                } else if ( ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text().toDouble() < -10000. ) {
                        *errorString += "INPUT: Height coordinate cannot be lower than -10 kilometres.\n";
                } else {
                        *saveString += "-pre:setrecpos DGNSSUserGeodbaseline " + ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() + "\n";
                        *runString << "-pre:setrecpos" << "DGNSSUserGeodbaseline" << ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text();
                }
            }
        } else if ( ui->radioButtonRtcmUserRinexRover->isChecked() == true ) {
            if (ui->radioButtonRtcmRefCartesian->isChecked()==true) {
                if ( ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() == "" ) {
                    *errorString += "INPUT: Reference Station X Y and Z coordinates are required inputs if 'DGNSS - User RINEX Rover' is set [In the Input Section - A Priori Receiver Position From].\n";
                } else if (ui->lineEditAprioriRefRecPosRtcmSpecifyX->text().toDouble() == 0. || ui->lineEditAprioriRefRecPosRtcmSpecifyY->text().toDouble() == 0. || ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text().toDouble() == 0.) {
                    *errorString += "INPUT: Reference Station X Y and Z coordinates cannot be 0,0,0.\n";
                } else {
                    *saveString += "-pre:setrecpos DGNSSUserRinexRover " + ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() + "\n";
                    *runString << "-pre:setrecpos" << "DGNSSUserRinexRover" << ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text();
                }
            } else {
                if ( ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() == "" ) {
                    *errorString += "INPUT: Longitude, latitude and height coordinates are required inputs if 'DGNSS - User RINEX Rover' is set [In the Input Section - A Priori Receiver Position From].\n";
                } else if  (ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text().toDouble()<-180. || ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text().toDouble()>180) {
                        *errorString += "INPUT: Longitude coordinate must be in the range [-180..180] degrees.\n";
                } else if  (ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text().toDouble()<-90. || ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text().toDouble()>90) {
                        *errorString += "INPUT: Latitude coordinate must be in the range [-90..90] degrees.\n";
                } else if ( ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text().toDouble() < -10000. ) {
                        *errorString += "INPUT: Height coordinate cannot be lower than -10 kilometres.\n";
                } else {
                        *saveString += "-pre:setrecpos DGNSSUserGeodRinexRover " + ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() + "\n";
                        *runString << "-pre:setrecpos" << "DGNSSUserGeodRinexRover" << ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text();
                }
            }
        } else if ( ui->radioButtonRtcmUserSpecify->isChecked() == true ) {
            conditionsmet=1;
            if (ui->radioButtonRtcmRefCartesian->isChecked()==true) {
                if ( ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() == "" ) {
                    *errorString += "INPUT: Reference Station X Y and Z coordinates are required inputs if 'DGNSS - User Ref. & Rover' is set [In the Input Section - A Priori Receiver Position From].\n";
                    conditionsmet=0;
                } else if (ui->lineEditAprioriRefRecPosRtcmSpecifyX->text().toDouble() == 0. || ui->lineEditAprioriRefRecPosRtcmSpecifyY->text().toDouble() == 0. || ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text().toDouble() == 0.) {
                    *errorString += "INPUT: Reference Station X Y and Z coordinates cannot be 0,0,0.\n";
                    conditionsmet=0;
                }
            } else {
                if ( ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() == "" ) {
                    *errorString += "INPUT: Longitude, latitude and height coordinates are required inputs if 'DGNSS - User Ref. & Rover' is set [In the Input Section - A Priori Receiver Position From].\n";
                    conditionsmet=0;
                } else if  (ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text().toDouble()<-180. || ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text().toDouble()>180) {
                    *errorString += "INPUT: Longitude coordinate must be in the range [-180..180] degrees.\n";
                    conditionsmet=0;
                } else if  (ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text().toDouble()<-90. || ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text().toDouble()>90) {
                    *errorString += "INPUT: Latitude coordinate must be in the range [-90..90] degrees.\n";
                    conditionsmet=0;
                } else if ( ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text().toDouble() < -10000. ) {
                    *errorString += "INPUT: Height coordinate cannot be lower than -10 kilometres.\n";
                    conditionsmet=0;
                }
            }
            if (ui->radioButtonRtcmUserDefined->isChecked()==true ) {
                if (ui->radioButtonRtcmRecCartesian->isChecked()==true) {
                    if ( ui->lineEditAprioriRecPosRtcmSpecifyX->text() == "" || ui->lineEditAprioriRecPosRtcmSpecifyY->text() == "" || ui->lineEditAprioriRecPosRtcmSpecifyZ->text() == "" ) {
                        *errorString += "INPUT: Rover X Y and Z coordinates are required inputs if 'DGNSS - User Ref. & Rover' is set [In the Input Section - A Priori Receiver Position From].\n";
                        conditionsmet=0;
                    } else if ( ui->lineEditAprioriRecPosRtcmSpecifyX->text().toDouble() == 0. || ui->lineEditAprioriRecPosRtcmSpecifyY->text().toDouble() == 0. || ui->lineEditAprioriRecPosRtcmSpecifyZ->text().toDouble() == 0. ) {
                        *errorString += "INPUT: Rover X Y and Z coordinates cannot be 0,0,0.\n";
                        conditionsmet=0;
                    }
                } else {
                    if ( ui->lineEditAprioriRecPosRtcmSpecifyLon->text() == "" || ui->lineEditAprioriRecPosRtcmSpecifyLat->text() == "" || ui->lineEditAprioriRecPosRtcmSpecifyHeight->text() == "" ) {
                        *errorString += "INPUT: Longitude, latitude and height coordinates are required inputs if 'DGNSS - User Ref. & Rover' is set [In the Input Section - A Priori Receiver Position From].\n";
                        conditionsmet=0;
                    } else if  (ui->lineEditAprioriRecPosRtcmSpecifyLon->text().toDouble()<-180. || ui->lineEditAprioriRecPosRtcmSpecifyLon->text().toDouble()>180) {
                        *errorString += "INPUT: Longitude coordinate must be in the range [-180..180] degrees.\n";
                        conditionsmet=0;
                    } else if  (ui->lineEditAprioriRecPosRtcmSpecifyLat->text().toDouble()<-90. || ui->lineEditAprioriRecPosRtcmSpecifyLat->text().toDouble()>90) {
                        *errorString += "INPUT: Latitude coordinate must be in the range [-90..90] degrees.\n";
                        conditionsmet=0;
                    } else if ( ui->lineEditAprioriRecPosRtcmSpecifyHeight->text().toDouble() < -10000. ) {
                        *errorString += "INPUT: Height coordinate cannot be lower than -10 kilometres.\n";
                        conditionsmet=0;
                    }
                }
            }
            if (conditionsmet==1) {
                if (ui->radioButtonRtcmUserDefined->isChecked()==true ) {
                    if (ui->radioButtonRtcmRefCartesian->isChecked()==true) {
                        if(ui->radioButtonRtcmRecCartesian->isChecked()==true) {
                            //Both in cartesian format
                            *saveString += "-pre:setrecpos DGNSSRefRoverUSER " + ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyX->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyY->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyZ->text() +"\n";
                            *runString << "-pre:setrecpos" << "DGNSSRefRoverUSER" << ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() << ui->lineEditAprioriRecPosRtcmSpecifyX->text() <<  ui->lineEditAprioriRecPosRtcmSpecifyY->text() <<  ui->lineEditAprioriRecPosRtcmSpecifyZ->text();
                        } else {
                            //Reference in cartesian, Rover in Geodetic
                            *saveString += "-pre:setrecpos DGNSSRefCarRoverUSERGeod " + ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyLon->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyLat->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyHeight->text() +"\n";
                            *runString << "-pre:setrecpos" << "DGNSSRefCarRoverUSERGeod" << ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() << ui->lineEditAprioriRecPosRtcmSpecifyLon->text() <<  ui->lineEditAprioriRecPosRtcmSpecifyLat->text() <<  ui->lineEditAprioriRecPosRtcmSpecifyHeight->text();
                        }
                    } else {
                        if(ui->radioButtonRtcmRecCartesian->isChecked()==true) {
                            //Reference in geodetic, Rover in cartesian
                            *saveString += "-pre:setrecpos DGNSSRefGeodRoverUSERCar " + ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyX->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyY->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyZ->text() +"\n";
                            *runString << "-pre:setrecpos" << "DGNSSRefGeodRoverUSERCar" << ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() << ui->lineEditAprioriRecPosRtcmSpecifyX->text() <<  ui->lineEditAprioriRecPosRtcmSpecifyY->text() <<  ui->lineEditAprioriRecPosRtcmSpecifyZ->text();
                        } else {
                            //Both in Geodetic
                            *saveString += "-pre:setrecpos DGNSSRefGeodRoverUSERGeod " + ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyLon->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyLat->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyHeight->text() +"\n";
                            *runString << "-pre:setrecpos" << "DGNSSRefGeodRoverUSERGeod" << ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() << ui->lineEditAprioriRecPosRtcmSpecifyLon->text() <<  ui->lineEditAprioriRecPosRtcmSpecifyLat->text() <<  ui->lineEditAprioriRecPosRtcmSpecifyHeight->text();
                        }

                    }
                } else {
                    if(ui->radioButtonRtcmRefCartesian->isChecked()==true) {
                        *saveString += "-pre:setrecpos DGNSSUserRoverRef " + ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() + "\n";
                        *runString << "-pre:setrecpos" << "DGNSSUserRoverRef" << ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text();
                    } else {
                        *saveString += "-pre:setrecpos DGNSSUserGeodRoverRef " + ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() + "\n";
                        *runString << "-pre:setrecpos" << "DGNSSUserGeodRoverRef" << ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text();
                    }
                }
            }
        }
    } else if ( ui->radioButtonSpecify->isChecked() == true ) {
        if (ui->radioButtonSpecifyReferenceFile->isChecked()==true) {
            if (ui->lineEditInterpolationDegreeRefFileSpecify->text()=="") {
                *errorString += "INPUT: Reference position interpolation degree is a required input if 'Reference file:' is set in 'Specify' mode [In the Input Section - A Priori Receiver Position From] .\n";
            } else {
                if (ui->lineEditInterpolationDegreeRefFileSpecify->text().toInt()==0) {
                    //Default interpolation value is 0
                    if (WriteAllParameters==1) {
                        *saveString += "-pre:refpos:deg " + ui->lineEditInterpolationDegreeRefFileSpecify->text() + "\n";
                        *runString << "-pre:refpos:deg" << ui->lineEditInterpolationDegreeRefFileSpecify->text();
                    }
                } else {
                    *saveString += "-pre:refpos:deg " + ui->lineEditInterpolationDegreeRefFileSpecify->text() + "\n";
                    *runString << "-pre:refpos:deg" << ui->lineEditInterpolationDegreeRefFileSpecify->text();
                }
            }
            *saveString += "-pre:setrecpos SetRef\n";
            *runString << "-pre:setrecpos" << "SetRef";
        } else {
            if (ui->radioButtonSpecifyUserCartesian->isChecked()==true) {
                if ( ui->lineEditSpecifyX->text() == "" || ui->lineEditSpecifyY->text() == "" || ui->lineEditSpecifyZ->text() == "" ) {
                    *errorString += "INPUT: X Y and Z coordinates are required inputs if 'Specify - User defined' is set [In the Input Section - A Priori Receiver Position From].\n";
                } else if (ui->lineEditSpecifyX->text().toDouble() == 0. || ui->lineEditSpecifyY->text().toDouble() == 0. || ui->lineEditSpecifyZ->text().toDouble() == 0.) {
                    *errorString += "INPUT: X Y and Z coordinates cannot be 0,0,0.\n";
                } else {
                    *saveString += "-pre:setrecpos Set " + ui->lineEditSpecifyX->text() + " " + ui->lineEditSpecifyY->text() + " " + ui->lineEditSpecifyZ->text() + "\n";
                    *runString << "-pre:setrecpos" << "Set"<< ui->lineEditSpecifyX->text() << ui->lineEditSpecifyY->text() << ui->lineEditSpecifyZ->text();
                }
            } else {
                if ( ui->lineEditSpecifyLon->text() == "" || ui->lineEditSpecifyLat->text() == "" || ui->lineEditSpecifyHeight->text() == "" ) {
                    *errorString += "INPUT: Longitude, latitude and height coordinates are required inputs if 'Specify - User defined' is set [In the Input Section - A Priori Receiver Position From].\n";
                } else if  (ui->lineEditSpecifyLon->text().toDouble()<-180. || ui->lineEditSpecifyLon->text().toDouble()>180) {
                        *errorString += "INPUT: Longitude coordinate must be in the range [-180..180] degrees.\n";
                } else if  (ui->lineEditSpecifyLat->text().toDouble()<-90. || ui->lineEditSpecifyLat->text().toDouble()>90) {
                        *errorString += "INPUT: Latitude coordinate must be in the range [-90..90] degrees.\n";
                } else if ( ui->lineEditSpecifyHeight->text().toDouble() < -10000. ) {
                        *errorString += "INPUT: Height coordinate cannot be lower than -10 kilometres.\n";
                } else {
                    if (ui->checkBoxReferencePositionFileCalculate->isChecked()==true) {
                        *saveString += "-pre:setrecpos SetGeod " + ui->lineEditSpecifyLon->text() + " " + ui->lineEditSpecifyLat->text() + " " + ui->lineEditSpecifyHeight->text() + "\n";
                        *runString << "-pre:setrecpos" << "SetGeod" << ui->lineEditSpecifyLon->text() << ui->lineEditSpecifyLat->text() << ui->lineEditSpecifyHeight->text();
                    } else {
                        *saveString += "-pre:setrecpos SetGeod " + ui->lineEditSpecifyLon->text() + " " + ui->lineEditSpecifyLat->text() + " " + ui->lineEditSpecifyHeight->text() + "\n";
                        *runString << "-pre:setrecpos" << "SetGeod" << ui->lineEditSpecifyLon->text() << ui->lineEditSpecifyLat->text() << ui->lineEditSpecifyHeight->text();
                    }
                }
            }
        }
    }

    if ( ui->checkBoxStartTime->isChecked()==true && ui->checkBoxEndTime->isChecked()==true) {
        date = ui->dateTimeEditStartTime->date();
        time = ui->dateTimeEditStartTime->time();
        if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && time.hour() == 0 && time.minute()==0 && time.second()==0) {
            *errorString += "INPUT: Date (DD/MM/YYYY) and GPS Time (HH:MM:SS) are a required input if 'Start Time' is set [In the Input Section - Rover].\n";
            badDate=1;
        }
        date = ui->dateTimeEditEndTime->date();
        time = ui->dateTimeEditEndTime->time();
        if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && time.hour() == 0 && time.minute()==0 && time.second()==0) {
            *errorString += "INPUT: Date (DD/MM/YYYY) and GPS Time (HH:MM:SS) are a required input if 'End Time' is set [In the Input Section - Rover].\n";
            badDate=1;
        }
        if (badDate==0) {
            if (ui->dateTimeEditStartTime->date().operator >(ui->dateTimeEditEndTime->date()) ) {
                *errorString += "INPUT: 'End Time' must be greater than the 'Start Time' if both are set [In the Input Section - Rover].\n";
                badDate=1;
            } else if (ui->dateTimeEditStartTime->date().operator ==(ui->dateTimeEditEndTime->date()) ) {
                if (ui->dateTimeEditStartTime->time().operator >(ui->dateTimeEditEndTime->time()) ) {
                    *errorString += "INPUT: 'End Time' must be greater than the 'Start Time' if both are set [In the Input Section - Rover].\n";
                    badDate=1;
                }
            }
        }
    }

    //Start time
    if (ui->checkBoxStartTime->isChecked()==true) {
        date = ui->dateTimeEditStartTime->date();
        time = ui->dateTimeEditStartTime->time();
        if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && time.hour() == 0 && time.minute()==0 && time.second()==0) {
            if (badDate==0) {
                *errorString += "INPUT: Date (DD/MM/YYYY) and GPS Time (HH:MM:SS) are a required input if 'Start Time' is set [In the Input Section - Rover].\n";
            }
        } else {
                *saveString += "-pre:starttime " + date.toString("yyyy/MM/dd") + " " + time.toString("HH:mm:ss") + "\n";
                *runString << "-pre:starttime" << date.toString("yyyy/MM/dd") << time.toString("HH:mm:ss");
        }
    }

    //End time
    if (ui->checkBoxEndTime->isChecked()==true) {
        date = ui->dateTimeEditEndTime->date();
        time = ui->dateTimeEditEndTime->time();
        if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && time.hour() == 0 && time.minute()==0 && time.second()==0) {
            if (badDate==0) {
                *errorString += "INPUT: Date (DD/MM/YYYY) and GPS Time (HH:MM:SS) are a required input if 'End time' is set [In the Input Section - Rover].\n";
            }
        } else {
            *saveString += "-pre:endtime " + date.toString("yyyy/MM/dd") + " " + time.toString("HH:mm:ss") + "\n";
            *runString << "-pre:endtime" << date.toString("yyyy/MM/dd") << time.toString("HH:mm:ss");
        }
    }

    ////Receiver type
    if ( ui->groupBoxAuxFiles->isChecked() == true ) {
        if ( ui->groupBoxP1C1correction->isChecked() == true ) {
            if (ui->radioButtonGPSReceiverTypeFile->isChecked()==true ) {
                //We have selected a GPS Receiver type file
                if (WriteAllParameters==1) {
                    if (ui->lineEditGPSRecType->text()=="") {
                        //This is the default receiver type when no GPS receiver type file is given
                        *saveString += "-pre:setrectype 0\n";
                        *runString << "-pre:setrectype" << "0";
                    } else {
                        //This is the default option when a GPS receiver type file is given
                        *saveString += "-pre:setrectype gpsrt\n";
                        *runString << "-pre:setrectype" << "gpsrt";
                    }
                }
            } else if (ui->radioButtonGPSReceiverTypeUserSelection->isChecked()==true) {
                if (ui->comboBoxGPSReceiverTypeSelection->currentIndex()==0) {
                    //This is the default receiver type when no GPS receiver type file is given
                    if (WriteAllParameters==1) {
                        *saveString += "-pre:setrectype 0\n";
                        *runString << "-pre:setrectype" << "0";
                    }
                } else if (ui->comboBoxGPSReceiverTypeSelection->currentIndex()==1) {
                    *saveString += "-pre:setrectype 1\n";
                    *runString << "-pre:setrectype" << "1";
                } else if (ui->comboBoxGPSReceiverTypeSelection->currentIndex()==2) {
                    *saveString += "-pre:setrectype 2\n";
                    *runString << "-pre:setrectype" << "2";
                } else if (ui->comboBoxGPSReceiverTypeSelection->currentIndex()==3) {
                    *saveString += "-pre:setrectype 3\n";
                    *runString << "-pre:setrectype" << "3";
                }
            }
        } else {
            //No P1-C1 correction and no GPS receiver type file given. Default receiver type is 0 (Unknown type)
            if (WriteAllParameters==1) {
                *saveString += "-pre:setrectype 0\n";
                *runString << "-pre:setrectype" << "0";
            }
        }
    } else {
        //No P1-C1 correction and no GPS receiver type file given (Auxiliary groupbox disabled). Default receiver type is 0 (Unknown type)
        if (WriteAllParameters==1) {
            *saveString += "-pre:setrectype 0\n";
            *runString << "-pre:setrectype" << "0";
        }
    }

    //// Station Data
    //Decimation
    if ( ui->checkBoxDataDecimator->isChecked() == true ) {
        if ( ui->lineEditDataDecimator->text() == "" )
            *errorString += "PREPROCESS: Some numeric value is required if 'Data Decimation' is set [In the Preprocess Section - Station Data].\n";
        else {
            if (ui->groupBoxSbas->isChecked()==true) {
                if ( ui->lineEditDataDecimator->text().toDouble() != 1.|| WriteAllParameters==1 ) {
                    //For SBAS set decimation if is different than 1
                    *saveString += "-pre:dec " + ui->lineEditDataDecimator->text() + "\n";
                    *runString << "-pre:dec" << ui->lineEditDataDecimator->text();
                }
            } else if ( ui->lineEditDataDecimator->text().toDouble() != 300. || ui->groupBoxReferenceStation->isChecked()==true || WriteAllParameters==1 ) {
                //For SPP,PPP, set decimation if is different than 300 or we are in DGNSS mode
                *saveString += "-pre:dec " + ui->lineEditDataDecimator->text() + "\n";
                *runString << "-pre:dec" << ui->lineEditDataDecimator->text();
            }
        }
    } else if (ui->groupBoxReferenceStation->isChecked()==false || WriteAllParameters==1){
        //Only add decimation 0 if DGNSS is not set
        *saveString += "-pre:dec 0\n";
        *runString << "-pre:dec" << "0";
    }
    //Code jumps. Enabled by default in all modes
    if (ui->checkBoxReceiverCodeJumps->isChecked()==true) {
        if (WriteAllParameters==1) {
            *saveString += "-pre:checkcodejumps\n";
            *runString << "-pre:checkcodejumps";
        }
    } else  if (ui->checkBoxReceiverCodeJumps->isChecked()==false) {
        *saveString += "--pre:checkcodejumps\n";
        *runString << "--pre:checkcodejumps";
    }


    // Satellite Options
    if ( ui->lineEditElevMask->text() == "" )
        *errorString += "PREPROCESS: Some numeric value is required for Elevation Mask [In the Preprocess Section - Satellite Options].\n";
    else if ( ui->lineEditElevMask->text().toDouble() != 5. || WriteAllParameters==1 ) {
        //Default mask for all modes is 5º
        *saveString += "-pre:elevation " + ui->lineEditElevMask->text() + "\n";
        *runString << "-pre:elevation" << ui->lineEditElevMask->text();
    }
    if ( ui->checkBoxDiscardEclipse->isChecked() == true ) {
        if (mode==0 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true || WriteAllParameters==1 ) {
            //Discard satellites on eclipse is only set by default in PPP
            *saveString += "-pre:eclipse\n";
            *runString << "-pre:eclipse";
        }
    } else if ( (mode==1 && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) || WriteAllParameters==1 ) {
        //No SBAS or DGNSS and we are in PPP
        *saveString += "--pre:eclipse\n";
        *runString << "--pre:eclipse";
    }

    //Carrier phase alignment is enabled by default on all modes
    if ( ui->checkBoxPrealignPhase->isChecked()==true) {
        if (WriteAllParameters==1 ) {
            *saveString += "-pre:prealign\n";
            *runString << "-pre:prealign";
        }
    } else  if ( ui->checkBoxPrealignPhase->isChecked()==false) {
        *saveString += "--pre:prealign\n";
        *runString << "--pre:prealign";
    }

    //SNR is disabled by default in all modes
    if ( ui->checkBoxDiscardSNRThreshold->isChecked()==true) {
        switch(ui->comboBoxSNRThresholds->currentIndex()) {
            case 0:
                *saveString += "-pre:snrsel G0 12\n";
                *runString << "-pre:snrsel" << "G0" << "12";
                break;
            case 1:
                *saveString += "-pre:snrsel G0 18\n";
                *runString << "-pre:snrsel" << "G0" << "18";
                break;
            case 2:
                *saveString += "-pre:snrsel G0 24\n";
                *runString << "-pre:snrsel" << "G0" << "24";
                break;
            case 3:                                
                *saveString += "-pre:snrsel G0 30\n";
                *runString << "-pre:snrsel" << "G0" << "30";
                break;
            case 4:
                //Default threshold in gLAB is 33
                if(WriteAllParameters==1) {
                    *saveString += "-pre:snrsel G0 33\n";
                    *runString << "-pre:snrsel" << "G0" << "33";
                } else {
                    if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
                        //In SPP or PPP SNR is disabled by default
                        *saveString += " -pre:snr\n";
                        *runString << "-pre:snr";
                    }
                }
                break;
            case 5:
                *saveString += "-pre:snrsel G0 36\n";
                *runString << "-pre:snrsel" << "G0" << "36";
                break;
            case 6:
                *saveString += "-pre:snrsel G0 42\n";
                *runString << "-pre:snrsel" << "G0" << "42";
                break;
            case 7:
                *saveString += "-pre:snrsel G0 48\n";
                *runString << "-pre:snrsel" << "G0" << "48";
                break;
            case 8:
                *saveString += "-pre:snrsel G0 54\n";
                *runString << "-pre:snrsel" << "G0" << "54";
                break;
            case 9:
                if(ui->lineEditUserDefinedSNR->text()=="") {
                    *errorString += "PREPROCESS: Some numeric value is required for SNR Mask [In the Preprocess Section - Satellite Options].\n";
                } else if (ui->lineEditUserDefinedSNR->text().toDouble()<=0) {
                    *errorString += "PREPROCESS: SNR Mask must be greater than 0 [In the Preprocess Section - Satellite Options].\n";
                } else {
                    if (ui->lineEditUserDefinedSNR->text().toDouble()==33) {
                        if(WriteAllParameters==1) {
                            *saveString += "-pre:snrsel G0 " + ui->lineEditUserDefinedSNR->text() +"\n";
                            *runString << "-pre:snrsel" << "G0" << ui->lineEditUserDefinedSNR->text();
                        } else {
                            if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
                                //In SPP or PPP SNR is disabled by default
                                *saveString += " -pre:snr\n";
                                *runString << "-pre:snr";
                            }
                        }
                    } else {
                        *saveString += "-pre:snrsel G0 " + ui->lineEditUserDefinedSNR->text() +"\n";
                        *runString << "-pre:snrsel" << "G0" << ui->lineEditUserDefinedSNR->text();
                    }
                }
                break;
        }
    } else {
        if (WriteAllParameters==1|| (ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true)) {
            //SNR is enabled by default in SBAS and DGNSS
            *saveString += "--pre:snr\n";
            *runString << "--pre:snr";
        }
    }


    // Cycle-slip Detection
    if ( ui->lineEditDataGap->text() == "" ) {
        *errorString += "PREPROCESS: Some numeric value is required for Data Gap [In the Preprocess Section - Cycle-slip Detection].\n";
    } else if (WriteAllParameters==1) {
        *saveString += "-pre:cs:datagap " + ui->lineEditDataGap->text() + "\n";
        *runString << "-pre:cs:datagap" << ui->lineEditDataGap->text();
    } else {
        if (ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true) {
            //In SBAS and DGNSS default data gap is 10
            if ( ui->lineEditDataGap->text().toInt() != 10 ) {
                *saveString += "-pre:cs:datagap " + ui->lineEditDataGap->text() + "\n";
                *runString << "-pre:cs:datagap" << ui->lineEditDataGap->text();
            }
        } else {
            //In SPP and PPP default data gap is 40
            if ( ui->lineEditDataGap->text().toInt() != 40 ) {
                *saveString += "-pre:cs:datagap " + ui->lineEditDataGap->text() + "\n";
                *runString << "-pre:cs:datagap" << ui->lineEditDataGap->text();
            }
        }
    }
    if ( ui->checkBoxLLI->isChecked() == true ) {
        //Only in PPP LLI is active by default
        if (mode==0 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true || WriteAllParameters==1 ) {
             *saveString += "-pre:cs:lli\n";
             *runString << "-pre:cs:lli";
        }
    } else {
        if ( (mode==1 && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) || WriteAllParameters==1 ) {
            *saveString += "--pre:cs:lli\n";
            *runString << "--pre:cs:lli";
        }
    }
    if (ui->checkBoxNcon->isChecked() == true ) {
        if (ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true || WriteAllParameters==1) {
             //N-con is enabled by default only on SPP or PPP
            *saveString += "-pre:cs:ncon:min " + ui->lineEditNcon->text() + "\n";
            *runString << "-pre:cs:ncon:min" << ui->lineEditNcon->text();
        } else {
            if (ui->lineEditNcon->text()!="3") {
                *saveString += "-pre:cs:ncon:min " + ui->lineEditNcon->text() + "\n";
                *runString << "-pre:cs:ncon:min" << ui->lineEditNcon->text();
            }
        }
    } else {
        if ((ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) || WriteAllParameters==1) {
            *saveString += "--pre:cs:ncon\n";
            *runString << "--pre:cs:ncon" ;
        }
    }
    if ( ui->checkBoxL1C1->isChecked() == true ) {
        //L1-C1 is enabled by default only in SBAS and DGNSS
        if  ((ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) || WriteAllParameters==1)  {
            *saveString += "-pre:cs:l1c1\n";
            *runString << "-pre:cs:l1c1";
        }
        //Consistency check is by default enabled in all modes
        if (ui->checkBoxL1C1ConsistencyCheck->isChecked()==true) {
            if (WriteAllParameters==1 ) {
                *saveString += "-pre:cs:l1c1:unconcheck\n";
                *runString << "-pre:cs:l1c1:unconcheck";
            }
            if (ui->lineEditL1C1ConsCheckValue->text()=="") {
               *errorString += "PREPROCESS: Some numeric value is required for Consistency Check Threshold [In the Preprocess Section - L1-C1 Cycle-slip Detection].\n";
            } else if (ui->lineEditL1C1ConsCheckValue->text().toDouble()==0.) {
                *errorString += "PREPROCESS: Consistency Check Threshold cannot be 0 [In the Preprocess Section - L1-C1 Cycle-slip Detection].\n";
            } else if (ui->lineEditL1C1ConsCheckValue->text().toDouble()!= 20. || WriteAllParameters==1) {
                *saveString += "-pre:cs:l1c1:unconcheck:th " + ui->lineEditL1C1ConsCheckValue->text() + "\n";
                *runString << "-pre:cs:l1c1:unconcheck:th" << ui->lineEditL1C1ConsCheckValue->text();
            }
        } else  if (ui->checkBoxL1C1ConsistencyCheck->isChecked()==false) {
            *saveString += "--pre:cs:l1c1:unconcheck\n";
            *runString << "--pre:cs:l1c1:unconcheck";
        }
        if ( ui->lineEditL1C1iniStd->text() == "" ) {
            *errorString += "PREPROCESS: Some numeric value is required for Initial stdDev [In the Preprocess Section - L1-C1 Cycle-slip Detection].\n";
        } else if ( ui->lineEditL1C1iniStd->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: Initial stdDev cannot be 0 [In the Preprocess Section - L1-C1 Cycle-slip Detection].\n";
        } else if (ui->lineEditL1C1iniStd->text().toDouble() != 3. || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:l1c1:init " + ui->lineEditL1C1iniStd->text() + "\n";
            *runString << "-pre:cs:l1c1:init" << ui->lineEditL1C1iniStd->text();
        }
        if ( ui->lineEditL1C1window->text() == "" ) {
            *errorString += "PREPROCESS: Some numeric value is required for Window [In the Preprocess Section - L1-C1 Cycle-slip Detection].\n";
        } else if ( ui->lineEditL1C1window->text().toInt() == 0 ) {
            *errorString += "PREPROCESS: Window cannot be 0 [In the Preprocess Section - L1-C1 Cycle-slip Detection].\n";
        } else if ( ui->lineEditL1C1window->text().toInt() >= 600 ) {
            *errorString += "PREPROCESS: Window size must be under 600 [In the Preprocess Section - L1-C1 Cycle-slip Detection].\n";
        } else if ( ui->lineEditL1C1window->text().toInt() != 300 || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:l1c1:timewindow " + ui->lineEditL1C1window->text() + "\n";
            *runString << "-pre:cs:l1c1:timewindow" << ui->lineEditL1C1window->text();
        }
        if ( ui->lineEditL1C1kFactor->text() == "" ) {
            *errorString += "PREPROCESS: Some numeric value is required for k-factor [In the Preprocess Section - L1-C1 Cycle-slip Detection].\n";
        } else if ( ui->lineEditL1C1kFactor->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: K-factor cannot be 0 [In the Preprocess Section - L1-C1 Cycle-slip Detection].\n";
        } else if ( ui->lineEditL1C1kFactor->text().toDouble() != 5.|| WriteAllParameters==1 ) {
            *saveString += "-pre:cs:l1c1:kfactor " + ui->lineEditL1C1kFactor->text() + "\n";
            *runString << "-pre:cs:l1c1:kfactor" << ui->lineEditL1C1kFactor->text();
        }
        if ( ui->lineEditL1C1nSample->text() == "" ) {
            *errorString += "PREPROCESS: Some numeric value is required for N-sample [In the Preprocess Section - L1-C1 Cycle-slip Detection].\n";
        } else if ( ui->lineEditL1C1nSample->text().toInt() == 0 ) {
            *errorString += "PREPROCESS: N-sample cannot be 0 [In the Preprocess Section - L1-C1 Cycle-slip Detection].\n";
        } else if ( ui->lineEditL1C1nSample->text().toInt() < 2 ) {
            *errorString += "PREPROCESS: N-sample cannot be less than 2 [In the Preprocess Section - L1-C1 Cycle-slip Detection].\n";
        } else if ( ui->lineEditL1C1nSample->text().toInt() != 2 || WriteAllParameters==1) {
            *saveString += "-pre:cs:l1c1:samples " + ui->lineEditL1C1nSample->text() + "\n";
            *runString << "-pre:cs:l1c1:samples" << ui->lineEditL1C1nSample->text();
        }
    } else if (ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true|| WriteAllParameters==1){
        *saveString += "--pre:cs:l1c1\n";
        *runString << "--pre:cs:l1c1";
    }
    if ( ui->checkBoxMW->isChecked() == true ) {
        if (ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true || mode==0 || WriteAllParameters==1){
            //MW detector is enabled by default only in PPP
            *saveString += "-pre:cs:bw\n";
            *runString << "-pre:cs:bw";
        }

        if ( ui->lineEditIntialStdDevBW->text() == "" ) {
            *errorString += "PREPROCESS: Some numeric value is required for Initial stdDev [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
         } else if ( ui->lineEditIntialStdDevBW->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: Initial stdDev cannot be 0 [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
         } else if ( ui->lineEditIntialStdDevBW->text().toDouble() != 2. || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:bw:siginit " + ui->lineEditIntialStdDevBW->text() + "\n";
            *runString << "-pre:cs:bw:siginit" << ui->lineEditIntialStdDevBW->text();
        }
        if ( ui->lineEditMWminStd->text() == "" ) {
            *errorString += "PREPROCESS: Some numeric value is required for Minimum stdDev [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
         } else if ( ui->lineEditMWminStd->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: Minimum stdDev cannot be 0 [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
         } else if ( ui->lineEditMWminStd->text().toDouble() != 0.8 || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:bw:sigmin " + ui->lineEditMWminStd->text() + "\n";
            *runString << "-pre:cs:bw:sigmin" << ui->lineEditMWminStd->text();
        }
        if ( ui->lineEditMWwindow->text() == "" ) {
            *errorString += "PREPROCESS: Some numeric value is required for Window [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
        } else if ( ui->lineEditMWwindow->text().toInt() == 0 ) {
            *errorString += "PREPROCESS: Window cannot be 0 [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
        } else if ( ui->lineEditMWwindow->text().toInt() >= 600 ) {
            *errorString += "PREPROCESS: Window size must be under 600 [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
        } else if ( ui->lineEditMWwindow->text().toInt() != 300 || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:bw:timewindow " + ui->lineEditMWwindow->text() + "\n";
            *runString << "-pre:cs:bw:timewindow" << ui->lineEditMWwindow->text();
        }
        if ( ui->lineEditMWkFactor->text() == "" ) {
            *errorString += "PREPROCESS: Some numeric value is required for k-factor [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
        } else if ( ui->lineEditMWkFactor->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: K-factor cannot be 0 [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
        } else if ( ui->lineEditMWkFactor->text().toDouble() != 5. || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:bw:kfactor " + ui->lineEditMWkFactor->text() + "\n";
            *runString << "-pre:cs:bw:kfactor" << ui->lineEditMWkFactor->text();
        }
        if ( ui->lineEditMWnSample->text() == "" ) {
            *errorString += "PREPROCESS: Some numeric value is required for N-sample [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
        } else if ( ui->lineEditMWnSample->text().toInt() == 0 ) {
            *errorString += "PREPROCESS: N-sample cannot be 0 [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
        } else if ( ui->lineEditMWnSample->text().toInt() < 2 ) {
            *errorString += "PREPROCESS: N-sample cannot be less than 2 [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
        } else if ( ui->lineEditMWnSample->text().toInt() != 2 || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:bw:samples " + ui->lineEditMWnSample->text() + "\n";
            *runString << "-pre:cs:bw:samples" << ui->lineEditMWnSample->text();
        }
    } else if ((mode==1 && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) || WriteAllParameters==1){
        *saveString += "--pre:cs:bw\n";
        *runString << "--pre:cs:bw";
    }
    if ( ui->checkBoxLI->isChecked() == true ) {
        if (ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true || mode==0 || WriteAllParameters==1){
            //MW detector is enabled by default only in PPP
            *saveString += "-pre:cs:li\n";
            *runString << "-pre:cs:li";
        }
        if ( ui->lineEditLImaxJumpThreshold->text() == "" ) {
            *errorString += "PREPROCESS: Some numeric value is required for Maximum Jump Threshold [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLImaxJumpThreshold->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: Maximum Jump Threshold cannot be 0 [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLImaxJumpThreshold->text().toDouble() != 1. || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:li:maxjump " + ui->lineEditLImaxJumpThreshold->text() + "\n";
            *runString << "-pre:cs:li:maxjump" << ui->lineEditLImaxJumpThreshold->text();
        }
        if ( ui->lineEditLImaxThreshold->text() == "" ) {
            *errorString += "PREPROCESS: Some numeric value is required for Maximum Threshold [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLImaxThreshold->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: Maximum Threshold cannot be 0 [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLImaxThreshold->text().toDouble() != 0.08 || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:li:max " + ui->lineEditLImaxThreshold->text() + "\n";
            *runString << "-pre:cs:li:max" << ui->lineEditLImaxThreshold->text();
        }
        if ( ui->lineEditLItimeConstant->text() == "" ) {
            *errorString += "PREPROCESS: Some numeric value is required for Time Constant [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLItimeConstant->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: Time Constant cannot be 0 [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLItimeConstant->text().toDouble() != 60. || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:li:t0 " + ui->lineEditLItimeConstant->text() + "\n";
            *runString << "-pre:cs:li:t0" << ui->lineEditLItimeConstant->text();
        }
        if ( ui->lineEditLInSamples->text() == "" ) {
            *errorString += "PREPROCESS: Some numeric value is required for N-sample [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLInSamples->text().toInt() == 0 ) {
            *errorString += "PREPROCESS:N-sample cannot be 0 [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLInSamples->text().toInt() < 2 ) {
            *errorString += "PREPROCESS:N-sample cannot be less than 2 [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLInSamples->text().toInt() != 7 || WriteAllParameters==1) {
            *saveString += "-pre:cs:li:samples " + ui->lineEditLInSamples->text() + "\n";
            *runString << "-pre:cs:li:samples" << ui->lineEditLInSamples->text();
        }
    } else if ((mode==1 && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) || WriteAllParameters==1){
        *saveString += "--pre:cs:li\n";
        *runString << "--pre:cs:li";
    }
    // GNSS Satellite Selection
    StartedGroup=0;
    FirstSat=0;
    for(i=0;i<Galileo;i++) { //To be expanded for multiconstellation
        for(j=1;j<=listMaxSatGNSS[i];j++) {
            if(PushButtonSatWidgets[i][j]->palette().background().color().name()==RedColor) {
                if (j==listMaxSatGNSS[i]) {
                    if(StartedGroup==1) {
                        *saveString += "-pre:sat -G" + QString("%1").arg(FirstSat) + "-" + QString("%1").arg(j) + "\n";
                        *runString << "-pre:sat" << "-G" + QString("%1").arg(FirstSat) + "-" + QString("%1").arg(j);
                    } else {
                        if (StartedGroup==0) {
                            FirstSat=listMaxSatGNSS[i];
                        }
                        *saveString += "-pre:sat -G" + QString("%1").arg(FirstSat) + "\n";
                        *runString << "-pre:sat" << "-G" + QString("%1").arg(FirstSat);
                    }
                    StartedGroup=0;
                } else if (StartedGroup==0) {
                    FirstSat=j;
                    StartedGroup=1;
                }
            } else {
                if (StartedGroup==1) {
                    if(j-1==FirstSat) {
                        //Group of a single satellite
                        *saveString += "-pre:sat -G" + QString("%1").arg(FirstSat) + "\n";
                        *runString << "-pre:sat" << "-G" + QString("%1").arg(FirstSat);
                    } else {
                        *saveString += "-pre:sat -G" + QString("%1").arg(FirstSat) + "-" + QString("%1").arg(j-1) + "\n";
                        *runString << "-pre:sat" << "-G" + QString("%1").arg(FirstSat) + "-" + QString("%1").arg(j-1);
                    }
                    StartedGroup=0;
                }
            }
        }
    }

    // Smoothing
    if ( ui->checkBoxSmoothing->isChecked() == true ) {
        if ( ui->lineEditSmoothing->text() == "" ) {
            *errorString += "FILTER: Some numeric value is required for Pseudorange Smoothing (epochs) [In the Filter Section - Measurements - Selection].\n";
        } else if (ui->lineEditSmoothing->text().toInt() == 0 ) {
            *errorString += "FILTER: Pseudorange Smoothing (epochs) cannot be 0 [In the Filter Section - Measurements - Selection].\n";
        } else {
            if ( (( (ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true) && ui->lineEditSmoothing->text().toInt() !=100) ||
                    (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) ) || WriteAllParameters==1) {
                *saveString += "-pre:smooth " + ui->lineEditSmoothing->text() + "\n";
                *runString << "-pre:smooth" << ui->lineEditSmoothing->text();
            }
        }
        if (ui->groupBoxSbas->isChecked()==false) {
            //In SBAS smoothed is only allowed with L1P, so we only need to set the other modes
            if (ui->stackedWidgetSmoothWith->currentIndex()==0) {
                //SPP page
                switch (ui->comboBoxSmoothWithSPP->currentIndex()) {
                    case 0:
                        if (ui->groupBoxReferenceStation->isChecked()==false || WriteAllParameters==1) {
                            //DGNSS has smoothing with L1P by default
                            *saveString += "-pre:smoothMeas 1 L1P\n";
                            *runString << "-pre:smoothMeas" << "1" << "L1P";
                        }
                        break;
                    case 1:
                        *saveString += "-pre:smoothMeas 1 L2P\n";
                        *runString << "-pre:smoothMeas" << "1" << "L2P";
                        break;
                    case 2:
                        *saveString += "-pre:smoothMeas 1 LC\n";
                        *runString << "-pre:smoothMeas" << "1" << "LC";
                        break;
                    case 3:
                        *saveString += "-pre:smoothMeas 1 DF\n";
                        *runString << "-pre:smoothMeas" << "1" << "DF";
                        break;
                    case 4:
                        *saveString += "-pre:smoothMeas 1 G1C\n";
                        *runString << "-pre:smoothMeas" << "1" << "G1C";
                        break;
                    case 5:
                        *saveString += "-pre:smoothMeas 1 G1P\n";
                        *runString << "-pre:smoothMeas" << "1" << "G1P";
                        break;
                    case 6:
                        *saveString += "-pre:smoothMeas 1 G2C\n";
                        *runString << "-pre:smoothMeas" << "1" << "G2C";
                        break;
                    case 7:
                        *saveString += "-pre:smoothMeas 1 G2P\n";
                        *runString << "-pre:smoothMeas" << "1" << "G2P";
                        break;
                    default:
                        break;
                }
            } else if (ui->stackedWidgetSmoothWith->currentIndex()==1) {
                //PPP page
                switch (ui->comboBoxSmoothWithSPP->currentIndex()) {
                    case 0:
                        *saveString += "-pre:smoothMeas 1 LC\n";
                        *runString << "-pre:smoothMeas" << "1" << "LC";
                        break;
                    case 1:
                        *saveString += "-pre:smoothMeas 1 DF\n";
                        *runString << "-pre:smoothMeas" << "1" << "DF";
                        break;
                    default:
                        break;
                }
            }
        } else if (ui->groupBoxSbas->isChecked()==true) {
            if (WriteAllParameters==1) {
                *saveString += "-pre:smoothMeas 1 L1P\n";
                *runString << "-pre:smoothMeas" << "1" << "L1P";
            }
        }
    } else if (ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true || WriteAllParameters==1) {
        //Smoothing is enabled by default only in SBAS and DGNSS
        *saveString += "-pre:smooth 0\n";
        *runString << "-pre:smooth" << "0";
    }
    // SBAS Options
    if ( ui->labelCurrentTemplate->text() == "SBAS" || ui->groupBoxSbas->isChecked()==true ) {
        // GEO selection
        switch ( ui->comboBoxGEOselection->currentIndex() ) {
            case 0 : {                
                *saveString += "-pre:geosel 1\n";
                *runString << "-pre:geosel" << "1";
                break;
            }
            case 1 : {
                *saveString += "-pre:geosel 0\n";
                *runString << "-pre:geosel" << "0";
                break;
            }
            case 2 : {
                //Default in SBAS, no need to set the option
                if (WriteAllParameters==1) {
                    *saveString += "-pre:geosel 2\n";
                    *runString << "-pre:geosel" << "2";
                }
                break;
            }
            case 3 : {
                if ( ui->lineEditGEOselection->text() == "" ) {
                    *errorString += "MODEL: Selected PRN for GEO selection in [SBAS Options] cannot be empty.\n";
                } else if ( ui->lineEditGEOselection->text().toInt() < 120 ) {
                    *errorString += "MODEL: Selected PRN for GEO selection in [SBAS Options] must be between 120 and 210.\n";
                } else {
                    *saveString += "-pre:geosel " + ui->lineEditGEOselection->text() + "\n";
                    *runString << "-pre:geosel" << ui->lineEditGEOselection->text();
                }
                break;
            }
        }
        // GEO exclude
        if ( ui->checkBoxGEOexclusion->isChecked() == true ) {
            switch ( ui->comboBoxGEOexclusion->currentIndex() ) {
                case 0 : {
                    if ( ui->lineEditGEOexclusion1->text() == "" ) {
                         *errorString += "MODEL: GEO exclusion in [SBAS Options] cannot be empty.\n";
                     } else if ( ui->lineEditGEOexclusion1->text().toInt() < 120 ) {
                        *errorString += "MODEL: GEO exclusion in [SBAS Options] must be between 120 and 210.\n";
                    } else {
                        *saveString += "-pre:geoexclude " + ui->lineEditGEOexclusion1->text() + "\n";
                        *runString << "-pre:geoexclude" << ui->lineEditGEOexclusion1->text();
                    }
                    if(ui->comboBoxGEOselection->currentIndex()==3) {
                        //Check that GEO unselected is not the GEO selected
                        if (ui->lineEditGEOselection->text()==ui->lineEditGEOexclusion1->text()) {
                            *errorString += "MODEL: GEO " + ui->lineEditGEOselection->text() + " selected for processing cannot be excluded\n";
                        }
                    }
                    break;
                }
                case 1 : {
                    if ( ui->lineEditGEOexclusion1->text() == "" || ui->lineEditGEOexclusion2->text() == "" ) {
                        *errorString += "MODEL: GEO exclusion in [SBAS Options] cannot be empty.\n";
                    } else if ( ui->lineEditGEOexclusion1->text().toInt() < 120 || ui->lineEditGEOexclusion2->text().toInt() < 120 ) {
                        *errorString += "MODEL: GEO exclusion in [SBAS Options] must be between 120 and 210.\n";
                    } else {
                        *saveString += "-pre:geoexclude " + ui->lineEditGEOexclusion1->text() + "," + ui->lineEditGEOexclusion2->text() + "\n";
                        *runString << "-pre:geoexclude" << ui->lineEditGEOexclusion1->text() + "," + ui->lineEditGEOexclusion2->text();
                    }
                    if(ui->comboBoxGEOselection->currentIndex()==3) {
                        //Check that GEO unselected is not the GEO selected
                        if ( (ui->lineEditGEOselection->text()==ui->lineEditGEOexclusion1->text()) || (ui->lineEditGEOselection->text()==ui->lineEditGEOexclusion2->text())) {
                            *errorString += "MODEL: GEO " + ui->lineEditGEOselection->text() + " selected for processing cannot be excluded\n";
                        }
                    }
                    break;
                }
                case 2 : {
                    if ( ui->lineEditGEOexclusion1->text() == "" || ui->lineEditGEOexclusion2->text() == "" || ui->lineEditGEOexclusion3->text() == "" ) {
                        *errorString += "MODEL: GEO exclusion in [SBAS Options] cannot be empty.\n";
                    } else if ( ui->lineEditGEOexclusion1->text().toInt() < 120 || ui->lineEditGEOexclusion2->text().toInt() < 120 || ui->lineEditGEOexclusion3->text().toInt() < 120 ) {
                        *errorString += "MODEL: GEO exclusion in [SBAS Options] must be between 120 and 210.\n";
                    } else {
                        *saveString += "-pre:geoexclude " + ui->lineEditGEOexclusion1->text() + "," + ui->lineEditGEOexclusion2->text() + "," + ui->lineEditGEOexclusion3->text() + "\n";
                        *runString << "-pre:geoexclude" << ui->lineEditGEOexclusion1->text() + "," + ui->lineEditGEOexclusion2->text() + "," + ui->lineEditGEOexclusion3->text();
                    }
                    if(ui->comboBoxGEOselection->currentIndex()==3) {
                        //Check that GEO unselected is not the GEO selected
                        if ( (ui->lineEditGEOselection->text()==ui->lineEditGEOexclusion1->text()) || (ui->lineEditGEOselection->text()==ui->lineEditGEOexclusion2->text()) || (ui->lineEditGEOselection->text()==ui->lineEditGEOexclusion3->text())) {
                            *errorString += "MODEL: GEO " + ui->lineEditGEOselection->text() + " selected for processing cannot be excluded\n";
                        }
                    }
                    break;
                }
            }

        }
        // Smoothmin
        if ( ui->checkBoxSmoothing->isChecked() == true ) {
            if ( ui->lineEditSmoothMinSbas->text() == "" ) {
                *errorString += "FILTER: Continuous code smoothing before steady-state operation cannot be empty.\n";
            } else {
                if ( ui->lineEditSmoothMinSbas->text().toInt() != 360 || WriteAllParameters==1 ) {
                    *saveString += "-pre:smoothmin " + ui->lineEditSmoothMinSbas->text() + "\n";
                    *runString << "-pre:smoothmin" << ui->lineEditSmoothMinSbas->text();
                }
            }
        } else {
            //Smoothin is enabled by default in SBAS
            *saveString += "-pre:smoothmin 0\n";
            *runString << "-pre:smoothmin" << "0";
        }
    }
    // DGNSS Options (within filter tab)
    if ( ui->labelCurrentTemplate->text() == "DGNSS" || ui->groupBoxReferenceStation->isChecked()==true ) {
        if ( ui->checkBoxExcludeDuringSmoothingConvergenceUser->isChecked() == true ) {
            *saveString += "-pre:dgnss:excludeSmoothingConvergenceUser\n";
            *runString << "-pre:dgnss:excludeSmoothingConvergenceUser";
        } else if ( ui->checkBoxExcludeDuringSmoothingConvergenceUser->isChecked() == false ) {
            if (WriteAllParameters==1 ) {
                *saveString += "-pre:dgnss:excludeSmoothingConvergenceUser\n";
                *runString << "-pre:dgnss:excludeSmoothingConvergenceUser";
            }
        }
        if ( ui->checkBoxExcludeDuringSmoothingConvergenceRef->isChecked() == true) {
            if (WriteAllParameters==1 ) {
                *saveString += "-pre:dgnss:excludeSmoothingConvergenceRef\n";
                *runString << "-pre:dgnss:excludeSmoothingConvergenceRef";
            }
        } else  if ( ui->checkBoxExcludeDuringSmoothingConvergenceRef->isChecked() == false ) {
            *saveString += "--pre:dgnss:excludeSmoothingConvergenceRef\n";
            *runString << "--pre:dgnss:excludeSmoothingConvergenceRef";
        }
        if ( ui->checkBoxSmoothing->isChecked() == true ) {
            if ( ui->checkBoxExcludeDuringSmoothingConvergenceRef->isChecked() == true || ui->checkBoxExcludeDuringSmoothingConvergenceUser->isChecked() == true ) {
                if ( ui->lineEditSmoothMinDgnss->text() == "" )
                    *errorString += "FILTER: Continuous code smoothing before steady-state operation cannot be empty.\n";
                else {
                    if ( ui->lineEditSmoothMinDgnss->text().toInt() != 360 || WriteAllParameters==1 ) {
                        *saveString += "-pre:dgnss:smoothmin " + ui->lineEditSmoothMinDgnss->text() + "\n";
                        *runString << "-pre:dgnss:smoothmin" << ui->lineEditSmoothMinDgnss->text();
                    }
                }
            }
        } else {
            //No smoothmin
            *saveString += "-pre:dgnss:smoothmin 0\n";
            *runString << "-pre:dgnss:smoothmin" << "0";
        }
    }
}
