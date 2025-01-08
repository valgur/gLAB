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

//this parameter indicate whether smoothed-with freq1 and freq2 to be the same when change the comboBox of comboBoxSmoothPhase1/2
static int smoothWithFreqNoSame=1;

//Function to initialize filter weights to fixed weight values
void gLAB_GUI::InitFilterWeights() {

    for (int isys=0;isys<MAX_GNSS;isys++) { //constellation
        for (int icomb=0; icomb<MAXMEASTOFILTER; icomb++) { //combination
            for(int measType=0;measType<MAXMEASTYPE;measType++) {
                if ( ui->radioButtonDualFreq->isChecked()==true ) {
                    LineEditstdDevValue[isys][icomb][measType][0]->setText(DualFreqDefaultFixedWeight[measType]);
                } else {
                    LineEditstdDevValue[isys][icomb][measType][0]->setText(SingleFreqDefaultFixedWeight[measType]);
                }
                LineEditstdDevValue[isys][icomb][measType][1]->setText(WeightTypeDefaultBandCValues[0][0]);
                LineEditstdDevValue[isys][icomb][measType][2]->setText(WeightTypeDefaultBandCValues[0][1]);
                //Set cursor to position 0 so text is aligned to the right
                LineEditstdDevValue[isys][icomb][measType][0]->setCursorPosition(0);
                LineEditstdDevValue[isys][icomb][measType][1]->setCursorPosition(0);
                LineEditstdDevValue[isys][icomb][measType][2]->setCursorPosition(0);
            }
        }
    }
}

//Function to set filter weights depending on the weight type selected
void gLAB_GUI::setWeightTypeValues(enum GNSSystem GNSS, int comb, int measType, int index) {

    if ( ui->radioButtonDualFreq->isChecked()==true ) {
        if (index<2) {
            LineEditstdDevValue[GNSS][comb][measType][0]->setText(DualFreqDefaultFixedWeight[measType]);
        } else {
            LineEditstdDevValue[GNSS][comb][measType][0]->setText(DualFreqDefaultFixedWeightSquared[measType]);
        }
    } else {
        if (index<2) {
            LineEditstdDevValue[GNSS][comb][measType][0]->setText(SingleFreqDefaultFixedWeight[measType]);
        } else {
            LineEditstdDevValue[GNSS][comb][measType][0]->setText(SingleFreqDefaultFixedWeightSquared[measType]);
        }
    }
    LineEditstdDevValue[GNSS][comb][measType][1]->setText(WeightTypeDefaultBandCValues[index][0]);
    LineEditstdDevValue[GNSS][comb][measType][2]->setText(WeightTypeDefaultBandCValues[index][1]);
    //Set cursor to position 0 so text is aligned to the right
    LineEditstdDevValue[GNSS][comb][measType][0]->setCursorPosition(0);
    LineEditstdDevValue[GNSS][comb][measType][1]->setCursorPosition(0);
    LineEditstdDevValue[GNSS][comb][measType][2]->setCursorPosition(0);

    //Manually set the size of LineEditsStdev in Linux to fit the space available (in Linux fonts are larger)
    #ifdef Q_OS_LINUX
        if (index==1) { //Elevation (only weight with three values)
            if (measType==GCARRAYPOS) {
                LineEditstdDevValue[GNSS][comb][measType][0]->setMaximumWidth(57);
                LineEditstdDevValue[GNSS][comb][measType][1]->setMaximumWidth(60);
                LineEditstdDevValue[GNSS][comb][measType][2]->setMaximumWidth(48);
            } else {
                LineEditstdDevValue[GNSS][comb][measType][0]->setMaximumWidth(66);
                LineEditstdDevValue[GNSS][comb][measType][1]->setMaximumWidth(66);
                LineEditstdDevValue[GNSS][comb][measType][2]->setMaximumWidth(48);
            }
        } else {
            LineEditstdDevValue[GNSS][comb][measType][0]->setMaximumWidth(66);
            LineEditstdDevValue[GNSS][comb][measType][1]->setMaximumWidth(75);
            LineEditstdDevValue[GNSS][comb][measType][2]->setMaximumWidth(55);
        }
    #elif defined(Q_OS_MAC)
        if (index==1) { //Elevation (only weight with three values)
            if (measType==GCARRAYPOS) {
                LineEditstdDevValue[GNSS][comb][measType][0]->setMaximumWidth(52);
                LineEditstdDevValue[GNSS][comb][measType][1]->setMaximumWidth(56);
                LineEditstdDevValue[GNSS][comb][measType][2]->setMaximumWidth(43);
            } else {
                LineEditstdDevValue[GNSS][comb][measType][0]->setMaximumWidth(56);
                LineEditstdDevValue[GNSS][comb][measType][1]->setMaximumWidth(56);
                LineEditstdDevValue[GNSS][comb][measType][2]->setMaximumWidth(44);
            }
        } else {
            LineEditstdDevValue[GNSS][comb][measType][0]->setMaximumWidth(60);
            LineEditstdDevValue[GNSS][comb][measType][1]->setMaximumWidth(70);
            LineEditstdDevValue[GNSS][comb][measType][2]->setMaximumWidth(55);
        }
    #endif
}

//Function to initialize reference clock
void gLAB_GUI::InitRefGNSSClock() {
    this->on_pushButtonRefGNSSClockSetDefault_clicked();
    this->on_pushButtonRefGNSSClockUnselectAll_clicked();
    for (int i=0; i<MAX_GNSS; i++){
        if (CheckBoxGNSS4RefClock[i]->isChecked()) {
            this->doubleClick_RefGNSSClock(1,RefGNSSClockPriority[i]);
        }
    }
}

//Function to initialize pointers to pushButton GNSS Measurements _clicked() functions
void gLAB_GUI::InitPushButtonGNSSMeasurementFuncPointers() {
    PushButtonGNSSMeasurementFunctions[GPS]=&gLAB_GUI::on_pushButtonGPSMeasurements_clicked;
    PushButtonGNSSMeasurementFunctions[Galileo]=&gLAB_GUI::on_pushButtonGalileoMeasurements_clicked;
    PushButtonGNSSMeasurementFunctions[GLONASS]=&gLAB_GUI::on_pushButtonGLONASSMeasurements_clicked;
    PushButtonGNSSMeasurementFunctions[GEO]=&gLAB_GUI::on_pushButtonGEOMeasurements_clicked;
    PushButtonGNSSMeasurementFunctions[BDS]=&gLAB_GUI::on_pushButtonBDSMeasurements_clicked;
    PushButtonGNSSMeasurementFunctions[QZSS]=&gLAB_GUI::on_pushButtonQZSSMeasurements_clicked;
    PushButtonGNSSMeasurementFunctions[IRNSS]=&gLAB_GUI::on_pushButtonIRNSSMeasurements_clicked;
}

//Funciton to initialize pointer to code and phase labels
void gLAB_GUI::InitGNSSFreqLabels() {
    //GPS
    LabelCodePhaseFreq[GPS][0][0]=ui->labelCodeGPS_1;
    LabelCodePhaseFreq[GPS][0][1]=ui->labelPhaseGPS_1;
    LabelCodePhaseFreq[GPS][1][0]=ui->labelCodeGPS_2;
    LabelCodePhaseFreq[GPS][1][1]=ui->labelPhaseGPS_2;
    LabelCodePhaseFreq[GPS][2][0]=ui->labelCodeGPS_3;
    LabelCodePhaseFreq[GPS][2][1]=ui->labelPhaseGPS_3;
    //Galileo
    LabelCodePhaseFreq[Galileo][0][0]=ui->labelCodeGalileo_1;
    LabelCodePhaseFreq[Galileo][0][1]=ui->labelPhaseGalileo_1;
    LabelCodePhaseFreq[Galileo][1][0]=ui->labelCodeGalileo_2;
    LabelCodePhaseFreq[Galileo][1][1]=ui->labelPhaseGalileo_2;
    LabelCodePhaseFreq[Galileo][2][0]=ui->labelCodeGalileo_3;
    LabelCodePhaseFreq[Galileo][2][1]=ui->labelPhaseGalileo_3;
    //GLONASS
    LabelCodePhaseFreq[GLONASS][0][0]=ui->labelCodeGLONASS_1;
    LabelCodePhaseFreq[GLONASS][0][1]=ui->labelPhaseGLONASS_1;
    LabelCodePhaseFreq[GLONASS][1][0]=ui->labelCodeGLONASS_2;
    LabelCodePhaseFreq[GLONASS][1][1]=ui->labelPhaseGLONASS_2;
    LabelCodePhaseFreq[GLONASS][2][0]=ui->labelCodeGLONASS_3;
    LabelCodePhaseFreq[GLONASS][2][1]=ui->labelPhaseGLONASS_3;
    //GEO
    LabelCodePhaseFreq[GEO][0][0]=ui->labelCodeGEO_1;
    LabelCodePhaseFreq[GEO][0][1]=ui->labelPhaseGEO_1;
    LabelCodePhaseFreq[GEO][1][0]=ui->labelCodeGEO_2;
    LabelCodePhaseFreq[GEO][1][1]=ui->labelPhaseGEO_2;
    LabelCodePhaseFreq[GEO][2][0]=ui->labelCodeGEO_3;
    LabelCodePhaseFreq[GEO][2][1]=ui->labelPhaseGEO_3;
    //BDS
    LabelCodePhaseFreq[BDS][0][0]=ui->labelCodeBDS_1;
    LabelCodePhaseFreq[BDS][0][1]=ui->labelPhaseBDS_1;
    LabelCodePhaseFreq[BDS][1][0]=ui->labelCodeBDS_2;
    LabelCodePhaseFreq[BDS][1][1]=ui->labelPhaseBDS_2;
    LabelCodePhaseFreq[BDS][2][0]=ui->labelCodeBDS_3;
    LabelCodePhaseFreq[BDS][2][1]=ui->labelPhaseBDS_3;
    //QZSS
    LabelCodePhaseFreq[QZSS][0][0]=ui->labelCodeQZSS_1;
    LabelCodePhaseFreq[QZSS][0][1]=ui->labelPhaseQZSS_1;
    LabelCodePhaseFreq[QZSS][1][0]=ui->labelCodeQZSS_2;
    LabelCodePhaseFreq[QZSS][1][1]=ui->labelPhaseQZSS_2;
    LabelCodePhaseFreq[QZSS][2][0]=ui->labelCodeQZSS_3;
    LabelCodePhaseFreq[QZSS][2][1]=ui->labelPhaseQZSS_3;
    //IRNSS
    LabelCodePhaseFreq[IRNSS][0][0]=ui->labelCodeIRNSS_1;
    LabelCodePhaseFreq[IRNSS][0][1]=ui->labelPhaseIRNSS_1;
    LabelCodePhaseFreq[IRNSS][1][0]=ui->labelCodeIRNSS_2;
    LabelCodePhaseFreq[IRNSS][1][1]=ui->labelPhaseIRNSS_2;
    LabelCodePhaseFreq[IRNSS][2][0]=ui->labelCodeIRNSS_3;
    LabelCodePhaseFreq[IRNSS][2][1]=ui->labelPhaseIRNSS_3;
}

//Function to initialize pointers to GNSS frequency & measurement comboBox
void gLAB_GUI::InitGNSSFreqMeasComboBoxPointers() {
    //GPS
    //frame
    FrameGNSSMeasComb[GPS][0]=ui->frameMeasGPS_1;
    FrameGNSSMeasComb[GPS][1]=ui->frameMeasGPS_2;
    FrameGNSSMeasComb[GPS][2]=ui->frameMeasGPS_3;
    FrameGNSSMeasFreq[GPS][0][0]=ui->frameCodeGPS_1;
    FrameGNSSMeasFreq[GPS][0][1]=ui->framePhaseGPS_1;
    FrameGNSSMeasFreq[GPS][0][2]=ui->frameGCGPS_1;
    FrameGNSSMeasFreq[GPS][1][0]=ui->frameCodeGPS_2;
    FrameGNSSMeasFreq[GPS][1][1]=ui->framePhaseGPS_2;
    FrameGNSSMeasFreq[GPS][1][2]=ui->frameGCGPS_2;
    FrameGNSSMeasFreq[GPS][2][0]=ui->frameCodeGPS_3;
    FrameGNSSMeasFreq[GPS][2][1]=ui->framePhaseGPS_3;
    FrameGNSSMeasFreq[GPS][2][2]=ui->frameGCGPS_3;
    FrameGNSSSmoothWith[GPS][0]=ui->frameSmoothGPS_1;
    FrameGNSSSmoothWith[GPS][1]=ui->frameSmoothGPS_2;
    FrameGNSSSmoothWith[GPS][2]=ui->frameSmoothGPS_3;
    //freq
    ComboBoxGNSSFreq[GPS][0][0]=ui->comboBoxFreqCodeGPS_1;
    ComboBoxGNSSFreq[GPS][0][1]=ui->comboBoxFreqPhaseGPS_1;
    ComboBoxGNSSFreq[GPS][0][2]=ui->comboBoxFreqGCGPS_1;
    ComboBoxGNSSFreq[GPS][1][0]=ui->comboBoxFreqCodeGPS_2;
    ComboBoxGNSSFreq[GPS][1][1]=ui->comboBoxFreqPhaseGPS_2;
    ComboBoxGNSSFreq[GPS][1][2]=ui->comboBoxFreqGCGPS_2;
    ComboBoxGNSSFreq[GPS][2][0]=ui->comboBoxFreqCodeGPS_3;
    ComboBoxGNSSFreq[GPS][2][1]=ui->comboBoxFreqPhaseGPS_3;
    ComboBoxGNSSFreq[GPS][2][2]=ui->comboBoxFreqGCGPS_3;
    //meas
    ComboBoxGNSSMeas[GPS][0][0][0]=ui->comboBoxMeasCodeFreq1GPS_1;
    ComboBoxGNSSMeas[GPS][0][0][1]=ui->comboBoxMeasCodeFreq2GPS_1;
    ComboBoxGNSSMeas[GPS][0][1][0]=ui->comboBoxMeasPhaseFreq1GPS_1;
    ComboBoxGNSSMeas[GPS][0][1][1]=ui->comboBoxMeasPhaseFreq2GPS_1;
    ComboBoxGNSSMeas[GPS][0][2][0]=ui->comboBoxMeasGCCodeGPS_1;
    ComboBoxGNSSMeas[GPS][0][2][1]=ui->comboBoxMeasGCPhaseGPS_1;
    ComboBoxGNSSMeas[GPS][1][0][0]=ui->comboBoxMeasCodeFreq1GPS_2;
    ComboBoxGNSSMeas[GPS][1][0][1]=ui->comboBoxMeasCodeFreq2GPS_2;
    ComboBoxGNSSMeas[GPS][1][1][0]=ui->comboBoxMeasPhaseFreq1GPS_2;
    ComboBoxGNSSMeas[GPS][1][1][1]=ui->comboBoxMeasPhaseFreq2GPS_2;
    ComboBoxGNSSMeas[GPS][1][2][0]=ui->comboBoxMeasGCCodeGPS_2;
    ComboBoxGNSSMeas[GPS][1][2][1]=ui->comboBoxMeasGCPhaseGPS_2;
    ComboBoxGNSSMeas[GPS][2][0][0]=ui->comboBoxMeasCodeFreq1GPS_3;
    ComboBoxGNSSMeas[GPS][2][0][1]=ui->comboBoxMeasCodeFreq2GPS_3;
    ComboBoxGNSSMeas[GPS][2][1][0]=ui->comboBoxMeasPhaseFreq1GPS_3;
    ComboBoxGNSSMeas[GPS][2][1][1]=ui->comboBoxMeasPhaseFreq2GPS_3;
    ComboBoxGNSSMeas[GPS][2][2][0]=ui->comboBoxMeasGCCodeGPS_3;
    ComboBoxGNSSMeas[GPS][2][2][1]=ui->comboBoxMeasGCPhaseGPS_3;

    //Galileo
    //frame
    FrameGNSSMeasComb[Galileo][0]=ui->frameMeasGalileo_1;
    FrameGNSSMeasComb[Galileo][1]=ui->frameMeasGalileo_2;
    FrameGNSSMeasComb[Galileo][2]=ui->frameMeasGalileo_3;
    FrameGNSSMeasFreq[Galileo][0][0]=ui->frameCodeGalileo_1;
    FrameGNSSMeasFreq[Galileo][0][1]=ui->framePhaseGalileo_1;
    FrameGNSSMeasFreq[Galileo][0][2]=ui->frameGCGalileo_1;
    FrameGNSSMeasFreq[Galileo][1][0]=ui->frameCodeGalileo_2;
    FrameGNSSMeasFreq[Galileo][1][1]=ui->framePhaseGalileo_2;
    FrameGNSSMeasFreq[Galileo][1][2]=ui->frameGCGalileo_2;
    FrameGNSSMeasFreq[Galileo][2][0]=ui->frameCodeGalileo_3;
    FrameGNSSMeasFreq[Galileo][2][1]=ui->framePhaseGalileo_3;
    FrameGNSSMeasFreq[Galileo][2][2]=ui->frameGCGalileo_3;
    FrameGNSSSmoothWith[Galileo][0]=ui->frameSmoothGalileo_1;
    FrameGNSSSmoothWith[Galileo][1]=ui->frameSmoothGalileo_2;
    FrameGNSSSmoothWith[Galileo][2]=ui->frameSmoothGalileo_3;
    //freq
    ComboBoxGNSSFreq[Galileo][0][0]=ui->comboBoxFreqCodeGalileo_1;
    ComboBoxGNSSFreq[Galileo][0][1]=ui->comboBoxFreqPhaseGalileo_1;
    ComboBoxGNSSFreq[Galileo][0][2]=ui->comboBoxFreqGCGalileo_1;
    ComboBoxGNSSFreq[Galileo][1][0]=ui->comboBoxFreqCodeGalileo_2;
    ComboBoxGNSSFreq[Galileo][1][1]=ui->comboBoxFreqPhaseGalileo_2;
    ComboBoxGNSSFreq[Galileo][1][2]=ui->comboBoxFreqGCGalileo_2;
    ComboBoxGNSSFreq[Galileo][2][0]=ui->comboBoxFreqCodeGalileo_3;
    ComboBoxGNSSFreq[Galileo][2][1]=ui->comboBoxFreqPhaseGalileo_3;
    ComboBoxGNSSFreq[Galileo][2][2]=ui->comboBoxFreqGCGalileo_3;
    //meas
    ComboBoxGNSSMeas[Galileo][0][0][0]=ui->comboBoxMeasCodeFreq1Galileo_1;
    ComboBoxGNSSMeas[Galileo][0][0][1]=ui->comboBoxMeasCodeFreq2Galileo_1;
    ComboBoxGNSSMeas[Galileo][0][1][0]=ui->comboBoxMeasPhaseFreq1Galileo_1;
    ComboBoxGNSSMeas[Galileo][0][1][1]=ui->comboBoxMeasPhaseFreq2Galileo_1;
    ComboBoxGNSSMeas[Galileo][0][2][0]=ui->comboBoxMeasGCCodeGalileo_1;
    ComboBoxGNSSMeas[Galileo][0][2][1]=ui->comboBoxMeasGCPhaseGalileo_1;
    ComboBoxGNSSMeas[Galileo][1][0][0]=ui->comboBoxMeasCodeFreq1Galileo_2;
    ComboBoxGNSSMeas[Galileo][1][0][1]=ui->comboBoxMeasCodeFreq2Galileo_2;
    ComboBoxGNSSMeas[Galileo][1][1][0]=ui->comboBoxMeasPhaseFreq1Galileo_2;
    ComboBoxGNSSMeas[Galileo][1][1][1]=ui->comboBoxMeasPhaseFreq2Galileo_2;
    ComboBoxGNSSMeas[Galileo][1][2][0]=ui->comboBoxMeasGCCodeGalileo_2;
    ComboBoxGNSSMeas[Galileo][1][2][1]=ui->comboBoxMeasGCPhaseGalileo_2;
    ComboBoxGNSSMeas[Galileo][2][0][0]=ui->comboBoxMeasCodeFreq1Galileo_3;
    ComboBoxGNSSMeas[Galileo][2][0][1]=ui->comboBoxMeasCodeFreq2Galileo_3;
    ComboBoxGNSSMeas[Galileo][2][1][0]=ui->comboBoxMeasPhaseFreq1Galileo_3;
    ComboBoxGNSSMeas[Galileo][2][1][1]=ui->comboBoxMeasPhaseFreq2Galileo_3;
    ComboBoxGNSSMeas[Galileo][2][2][0]=ui->comboBoxMeasGCCodeGalileo_3;
    ComboBoxGNSSMeas[Galileo][2][2][1]=ui->comboBoxMeasGCPhaseGalileo_3;

    //GLONASS
    //frame
    FrameGNSSMeasComb[GLONASS][0]=ui->frameMeasGLONASS_1;
    FrameGNSSMeasComb[GLONASS][1]=ui->frameMeasGLONASS_2;
    FrameGNSSMeasComb[GLONASS][2]=ui->frameMeasGLONASS_3;
    FrameGNSSMeasFreq[GLONASS][0][0]=ui->frameCodeGLONASS_1;
    FrameGNSSMeasFreq[GLONASS][0][1]=ui->framePhaseGLONASS_1;
    FrameGNSSMeasFreq[GLONASS][0][2]=ui->frameGCGLONASS_1;
    FrameGNSSMeasFreq[GLONASS][1][0]=ui->frameCodeGLONASS_2;
    FrameGNSSMeasFreq[GLONASS][1][1]=ui->framePhaseGLONASS_2;
    FrameGNSSMeasFreq[GLONASS][1][2]=ui->frameGCGLONASS_2;
    FrameGNSSMeasFreq[GLONASS][2][0]=ui->frameCodeGLONASS_3;
    FrameGNSSMeasFreq[GLONASS][2][1]=ui->framePhaseGLONASS_3;
    FrameGNSSMeasFreq[GLONASS][2][2]=ui->frameGCGLONASS_3;
    FrameGNSSSmoothWith[GLONASS][0]=ui->frameSmoothGLONASS_1;
    FrameGNSSSmoothWith[GLONASS][1]=ui->frameSmoothGLONASS_2;
    FrameGNSSSmoothWith[GLONASS][2]=ui->frameSmoothGLONASS_3;
    //freq
    ComboBoxGNSSFreq[GLONASS][0][0]=ui->comboBoxFreqCodeGLONASS_1;
    ComboBoxGNSSFreq[GLONASS][0][1]=ui->comboBoxFreqPhaseGLONASS_1;
    ComboBoxGNSSFreq[GLONASS][0][2]=ui->comboBoxFreqGCGLONASS_1;
    ComboBoxGNSSFreq[GLONASS][1][0]=ui->comboBoxFreqCodeGLONASS_2;
    ComboBoxGNSSFreq[GLONASS][1][1]=ui->comboBoxFreqPhaseGLONASS_2;
    ComboBoxGNSSFreq[GLONASS][1][2]=ui->comboBoxFreqGCGLONASS_2;
    ComboBoxGNSSFreq[GLONASS][2][0]=ui->comboBoxFreqCodeGLONASS_3;
    ComboBoxGNSSFreq[GLONASS][2][1]=ui->comboBoxFreqPhaseGLONASS_3;
    ComboBoxGNSSFreq[GLONASS][2][2]=ui->comboBoxFreqGCGLONASS_3;
    //meas
    ComboBoxGNSSMeas[GLONASS][0][0][0]=ui->comboBoxMeasCodeFreq1GLONASS_1;
    ComboBoxGNSSMeas[GLONASS][0][0][1]=ui->comboBoxMeasCodeFreq2GLONASS_1;
    ComboBoxGNSSMeas[GLONASS][0][1][0]=ui->comboBoxMeasPhaseFreq1GLONASS_1;
    ComboBoxGNSSMeas[GLONASS][0][1][1]=ui->comboBoxMeasPhaseFreq2GLONASS_1;
    ComboBoxGNSSMeas[GLONASS][0][2][0]=ui->comboBoxMeasGCCodeGLONASS_1;
    ComboBoxGNSSMeas[GLONASS][0][2][1]=ui->comboBoxMeasGCPhaseGLONASS_1;
    ComboBoxGNSSMeas[GLONASS][1][0][0]=ui->comboBoxMeasCodeFreq1GLONASS_2;
    ComboBoxGNSSMeas[GLONASS][1][0][1]=ui->comboBoxMeasCodeFreq2GLONASS_2;
    ComboBoxGNSSMeas[GLONASS][1][1][0]=ui->comboBoxMeasPhaseFreq1GLONASS_2;
    ComboBoxGNSSMeas[GLONASS][1][1][1]=ui->comboBoxMeasPhaseFreq2GLONASS_2;
    ComboBoxGNSSMeas[GLONASS][1][2][0]=ui->comboBoxMeasGCCodeGLONASS_2;
    ComboBoxGNSSMeas[GLONASS][1][2][1]=ui->comboBoxMeasGCPhaseGLONASS_2;
    ComboBoxGNSSMeas[GLONASS][2][0][0]=ui->comboBoxMeasCodeFreq1GLONASS_3;
    ComboBoxGNSSMeas[GLONASS][2][0][1]=ui->comboBoxMeasCodeFreq2GLONASS_3;
    ComboBoxGNSSMeas[GLONASS][2][1][0]=ui->comboBoxMeasPhaseFreq1GLONASS_3;
    ComboBoxGNSSMeas[GLONASS][2][1][1]=ui->comboBoxMeasPhaseFreq2GLONASS_3;
    ComboBoxGNSSMeas[GLONASS][2][2][0]=ui->comboBoxMeasGCCodeGLONASS_3;
    ComboBoxGNSSMeas[GLONASS][2][2][1]=ui->comboBoxMeasGCPhaseGLONASS_3;

    //GEO
    //frame
    FrameGNSSMeasComb[GEO][0]=ui->frameMeasGEO_1;
    FrameGNSSMeasComb[GEO][1]=ui->frameMeasGEO_2;
    FrameGNSSMeasComb[GEO][2]=ui->frameMeasGEO_3;
    FrameGNSSMeasFreq[GEO][0][0]=ui->frameCodeGEO_1;
    FrameGNSSMeasFreq[GEO][0][1]=ui->framePhaseGEO_1;
    FrameGNSSMeasFreq[GEO][0][2]=ui->frameGCGEO_1;
    FrameGNSSMeasFreq[GEO][1][0]=ui->frameCodeGEO_2;
    FrameGNSSMeasFreq[GEO][1][1]=ui->framePhaseGEO_2;
    FrameGNSSMeasFreq[GEO][1][2]=ui->frameGCGEO_2;
    FrameGNSSMeasFreq[GEO][2][0]=ui->frameCodeGEO_3;
    FrameGNSSMeasFreq[GEO][2][1]=ui->framePhaseGEO_3;
    FrameGNSSMeasFreq[GEO][2][2]=ui->frameGCGEO_3;
    FrameGNSSSmoothWith[GEO][0]=ui->frameSmoothGEO_1;
    FrameGNSSSmoothWith[GEO][1]=ui->frameSmoothGEO_2;
    FrameGNSSSmoothWith[GEO][2]=ui->frameSmoothGEO_3;
    //freq
    ComboBoxGNSSFreq[GEO][0][0]=ui->comboBoxFreqCodeGEO_1;
    ComboBoxGNSSFreq[GEO][0][1]=ui->comboBoxFreqPhaseGEO_1;
    ComboBoxGNSSFreq[GEO][0][2]=ui->comboBoxFreqGCGEO_1;
    ComboBoxGNSSFreq[GEO][1][0]=ui->comboBoxFreqCodeGEO_2;
    ComboBoxGNSSFreq[GEO][1][1]=ui->comboBoxFreqPhaseGEO_2;
    ComboBoxGNSSFreq[GEO][1][2]=ui->comboBoxFreqGCGEO_2;
    ComboBoxGNSSFreq[GEO][2][0]=ui->comboBoxFreqCodeGEO_3;
    ComboBoxGNSSFreq[GEO][2][1]=ui->comboBoxFreqPhaseGEO_3;
    ComboBoxGNSSFreq[GEO][2][2]=ui->comboBoxFreqGCGEO_3;
    //meas
    ComboBoxGNSSMeas[GEO][0][0][0]=ui->comboBoxMeasCodeFreq1GEO_1;
    ComboBoxGNSSMeas[GEO][0][0][1]=ui->comboBoxMeasCodeFreq2GEO_1;
    ComboBoxGNSSMeas[GEO][0][1][0]=ui->comboBoxMeasPhaseFreq1GEO_1;
    ComboBoxGNSSMeas[GEO][0][1][1]=ui->comboBoxMeasPhaseFreq2GEO_1;
    ComboBoxGNSSMeas[GEO][0][2][0]=ui->comboBoxMeasGCCodeGEO_1;
    ComboBoxGNSSMeas[GEO][0][2][1]=ui->comboBoxMeasGCPhaseGEO_1;
    ComboBoxGNSSMeas[GEO][1][0][0]=ui->comboBoxMeasCodeFreq1GEO_2;
    ComboBoxGNSSMeas[GEO][1][0][1]=ui->comboBoxMeasCodeFreq2GEO_2;
    ComboBoxGNSSMeas[GEO][1][1][0]=ui->comboBoxMeasPhaseFreq1GEO_2;
    ComboBoxGNSSMeas[GEO][1][1][1]=ui->comboBoxMeasPhaseFreq2GEO_2;
    ComboBoxGNSSMeas[GEO][1][2][0]=ui->comboBoxMeasGCCodeGEO_2;
    ComboBoxGNSSMeas[GEO][1][2][1]=ui->comboBoxMeasGCPhaseGEO_2;
    ComboBoxGNSSMeas[GEO][2][0][0]=ui->comboBoxMeasCodeFreq1GEO_3;
    ComboBoxGNSSMeas[GEO][2][0][1]=ui->comboBoxMeasCodeFreq2GEO_3;
    ComboBoxGNSSMeas[GEO][2][1][0]=ui->comboBoxMeasPhaseFreq1GEO_3;
    ComboBoxGNSSMeas[GEO][2][1][1]=ui->comboBoxMeasPhaseFreq2GEO_3;
    ComboBoxGNSSMeas[GEO][2][2][0]=ui->comboBoxMeasGCCodeGEO_3;
    ComboBoxGNSSMeas[GEO][2][2][1]=ui->comboBoxMeasGCPhaseGEO_3;

    //BDS
    //frame
    FrameGNSSMeasComb[BDS][0]=ui->frameMeasBDS_1;
    FrameGNSSMeasComb[BDS][1]=ui->frameMeasBDS_2;
    FrameGNSSMeasComb[BDS][2]=ui->frameMeasBDS_3;
    FrameGNSSMeasFreq[BDS][0][0]=ui->frameCodeBDS_1;
    FrameGNSSMeasFreq[BDS][0][1]=ui->framePhaseBDS_1;
    FrameGNSSMeasFreq[BDS][0][2]=ui->frameGCBDS_1;
    FrameGNSSMeasFreq[BDS][1][0]=ui->frameCodeBDS_2;
    FrameGNSSMeasFreq[BDS][1][1]=ui->framePhaseBDS_2;
    FrameGNSSMeasFreq[BDS][1][2]=ui->frameGCBDS_2;
    FrameGNSSMeasFreq[BDS][2][0]=ui->frameCodeBDS_3;
    FrameGNSSMeasFreq[BDS][2][1]=ui->framePhaseBDS_3;
    FrameGNSSMeasFreq[BDS][2][2]=ui->frameGCBDS_3;
    FrameGNSSSmoothWith[BDS][0]=ui->frameSmoothBDS_1;
    FrameGNSSSmoothWith[BDS][1]=ui->frameSmoothBDS_2;
    FrameGNSSSmoothWith[BDS][2]=ui->frameSmoothBDS_3;
    //freq
    ComboBoxGNSSFreq[BDS][0][0]=ui->comboBoxFreqCodeBDS_1;
    ComboBoxGNSSFreq[BDS][0][1]=ui->comboBoxFreqPhaseBDS_1;
    ComboBoxGNSSFreq[BDS][0][2]=ui->comboBoxFreqGCBDS_1;
    ComboBoxGNSSFreq[BDS][1][0]=ui->comboBoxFreqCodeBDS_2;
    ComboBoxGNSSFreq[BDS][1][1]=ui->comboBoxFreqPhaseBDS_2;
    ComboBoxGNSSFreq[BDS][1][2]=ui->comboBoxFreqGCBDS_2;
    ComboBoxGNSSFreq[BDS][2][0]=ui->comboBoxFreqCodeBDS_3;
    ComboBoxGNSSFreq[BDS][2][1]=ui->comboBoxFreqPhaseBDS_3;
    ComboBoxGNSSFreq[BDS][2][2]=ui->comboBoxFreqGCBDS_3;
    //meas
    ComboBoxGNSSMeas[BDS][0][0][0]=ui->comboBoxMeasCodeFreq1BDS_1;
    ComboBoxGNSSMeas[BDS][0][0][1]=ui->comboBoxMeasCodeFreq2BDS_1;
    ComboBoxGNSSMeas[BDS][0][1][0]=ui->comboBoxMeasPhaseFreq1BDS_1;
    ComboBoxGNSSMeas[BDS][0][1][1]=ui->comboBoxMeasPhaseFreq2BDS_1;
    ComboBoxGNSSMeas[BDS][0][2][0]=ui->comboBoxMeasGCCodeBDS_1;
    ComboBoxGNSSMeas[BDS][0][2][1]=ui->comboBoxMeasGCPhaseBDS_1;
    ComboBoxGNSSMeas[BDS][1][0][0]=ui->comboBoxMeasCodeFreq1BDS_2;
    ComboBoxGNSSMeas[BDS][1][0][1]=ui->comboBoxMeasCodeFreq2BDS_2;
    ComboBoxGNSSMeas[BDS][1][1][0]=ui->comboBoxMeasPhaseFreq1BDS_2;
    ComboBoxGNSSMeas[BDS][1][1][1]=ui->comboBoxMeasPhaseFreq2BDS_2;
    ComboBoxGNSSMeas[BDS][1][2][0]=ui->comboBoxMeasGCCodeBDS_2;
    ComboBoxGNSSMeas[BDS][1][2][1]=ui->comboBoxMeasGCPhaseBDS_2;
    ComboBoxGNSSMeas[BDS][2][0][0]=ui->comboBoxMeasCodeFreq1BDS_3;
    ComboBoxGNSSMeas[BDS][2][0][1]=ui->comboBoxMeasCodeFreq2BDS_3;
    ComboBoxGNSSMeas[BDS][2][1][0]=ui->comboBoxMeasPhaseFreq1BDS_3;
    ComboBoxGNSSMeas[BDS][2][1][1]=ui->comboBoxMeasPhaseFreq2BDS_3;
    ComboBoxGNSSMeas[BDS][2][2][0]=ui->comboBoxMeasGCCodeBDS_3;
    ComboBoxGNSSMeas[BDS][2][2][1]=ui->comboBoxMeasGCPhaseBDS_3;

    //QZSS
    //frame
    FrameGNSSMeasComb[QZSS][0]=ui->frameMeasQZSS_1;
    FrameGNSSMeasComb[QZSS][1]=ui->frameMeasQZSS_2;
    FrameGNSSMeasComb[QZSS][2]=ui->frameMeasQZSS_3;
    FrameGNSSMeasFreq[QZSS][0][0]=ui->frameCodeQZSS_1;
    FrameGNSSMeasFreq[QZSS][0][1]=ui->framePhaseQZSS_1;
    FrameGNSSMeasFreq[QZSS][0][2]=ui->frameGCQZSS_1;
    FrameGNSSMeasFreq[QZSS][1][0]=ui->frameCodeQZSS_2;
    FrameGNSSMeasFreq[QZSS][1][1]=ui->framePhaseQZSS_2;
    FrameGNSSMeasFreq[QZSS][1][2]=ui->frameGCQZSS_2;
    FrameGNSSMeasFreq[QZSS][2][0]=ui->frameCodeQZSS_3;
    FrameGNSSMeasFreq[QZSS][2][1]=ui->framePhaseQZSS_3;
    FrameGNSSMeasFreq[QZSS][2][2]=ui->frameGCQZSS_3;
    FrameGNSSSmoothWith[QZSS][0]=ui->frameSmoothQZSS_1;
    FrameGNSSSmoothWith[QZSS][1]=ui->frameSmoothQZSS_2;
    FrameGNSSSmoothWith[QZSS][2]=ui->frameSmoothQZSS_3;
    //freq
    ComboBoxGNSSFreq[QZSS][0][0]=ui->comboBoxFreqCodeQZSS_1;
    ComboBoxGNSSFreq[QZSS][0][1]=ui->comboBoxFreqPhaseQZSS_1;
    ComboBoxGNSSFreq[QZSS][0][2]=ui->comboBoxFreqGCQZSS_1;
    ComboBoxGNSSFreq[QZSS][1][0]=ui->comboBoxFreqCodeQZSS_2;
    ComboBoxGNSSFreq[QZSS][1][1]=ui->comboBoxFreqPhaseQZSS_2;
    ComboBoxGNSSFreq[QZSS][1][2]=ui->comboBoxFreqGCQZSS_2;
    ComboBoxGNSSFreq[QZSS][2][0]=ui->comboBoxFreqCodeQZSS_3;
    ComboBoxGNSSFreq[QZSS][2][1]=ui->comboBoxFreqPhaseQZSS_3;
    ComboBoxGNSSFreq[QZSS][2][2]=ui->comboBoxFreqGCQZSS_3;
    //meas
    ComboBoxGNSSMeas[QZSS][0][0][0]=ui->comboBoxMeasCodeFreq1QZSS_1;
    ComboBoxGNSSMeas[QZSS][0][0][1]=ui->comboBoxMeasCodeFreq2QZSS_1;
    ComboBoxGNSSMeas[QZSS][0][1][0]=ui->comboBoxMeasPhaseFreq1QZSS_1;
    ComboBoxGNSSMeas[QZSS][0][1][1]=ui->comboBoxMeasPhaseFreq2QZSS_1;
    ComboBoxGNSSMeas[QZSS][0][2][0]=ui->comboBoxMeasGCCodeQZSS_1;
    ComboBoxGNSSMeas[QZSS][0][2][1]=ui->comboBoxMeasGCPhaseQZSS_1;
    ComboBoxGNSSMeas[QZSS][1][0][0]=ui->comboBoxMeasCodeFreq1QZSS_2;
    ComboBoxGNSSMeas[QZSS][1][0][1]=ui->comboBoxMeasCodeFreq2QZSS_2;
    ComboBoxGNSSMeas[QZSS][1][1][0]=ui->comboBoxMeasPhaseFreq1QZSS_2;
    ComboBoxGNSSMeas[QZSS][1][1][1]=ui->comboBoxMeasPhaseFreq2QZSS_2;
    ComboBoxGNSSMeas[QZSS][1][2][0]=ui->comboBoxMeasGCCodeQZSS_2;
    ComboBoxGNSSMeas[QZSS][1][2][1]=ui->comboBoxMeasGCPhaseQZSS_2;
    ComboBoxGNSSMeas[QZSS][2][0][0]=ui->comboBoxMeasCodeFreq1QZSS_3;
    ComboBoxGNSSMeas[QZSS][2][0][1]=ui->comboBoxMeasCodeFreq2QZSS_3;
    ComboBoxGNSSMeas[QZSS][2][1][0]=ui->comboBoxMeasPhaseFreq1QZSS_3;
    ComboBoxGNSSMeas[QZSS][2][1][1]=ui->comboBoxMeasPhaseFreq2QZSS_3;
    ComboBoxGNSSMeas[QZSS][2][2][0]=ui->comboBoxMeasGCCodeQZSS_3;
    ComboBoxGNSSMeas[QZSS][2][2][1]=ui->comboBoxMeasGCPhaseQZSS_3;

    //IRNSS
    //frame
    FrameGNSSMeasComb[IRNSS][0]=ui->frameMeasIRNSS_1;
    FrameGNSSMeasComb[IRNSS][1]=ui->frameMeasIRNSS_2;
    FrameGNSSMeasComb[IRNSS][2]=ui->frameMeasIRNSS_3;
    FrameGNSSMeasFreq[IRNSS][0][0]=ui->frameCodeIRNSS_1;
    FrameGNSSMeasFreq[IRNSS][0][1]=ui->framePhaseIRNSS_1;
    FrameGNSSMeasFreq[IRNSS][0][2]=ui->frameGCIRNSS_1;
    FrameGNSSMeasFreq[IRNSS][1][0]=ui->frameCodeIRNSS_2;
    FrameGNSSMeasFreq[IRNSS][1][1]=ui->framePhaseIRNSS_2;
    FrameGNSSMeasFreq[IRNSS][1][2]=ui->frameGCIRNSS_2;
    FrameGNSSMeasFreq[IRNSS][2][0]=ui->frameCodeIRNSS_3;
    FrameGNSSMeasFreq[IRNSS][2][1]=ui->framePhaseIRNSS_3;
    FrameGNSSMeasFreq[IRNSS][2][2]=ui->frameGCIRNSS_3;
    FrameGNSSSmoothWith[IRNSS][0]=ui->frameSmoothIRNSS_1;
    FrameGNSSSmoothWith[IRNSS][1]=ui->frameSmoothIRNSS_2;
    FrameGNSSSmoothWith[IRNSS][2]=ui->frameSmoothIRNSS_3;
    //freq
    ComboBoxGNSSFreq[IRNSS][0][0]=ui->comboBoxFreqCodeIRNSS_1;
    ComboBoxGNSSFreq[IRNSS][0][1]=ui->comboBoxFreqPhaseIRNSS_1;
    ComboBoxGNSSFreq[IRNSS][0][2]=ui->comboBoxFreqGCIRNSS_1;
    ComboBoxGNSSFreq[IRNSS][1][0]=ui->comboBoxFreqCodeIRNSS_2;
    ComboBoxGNSSFreq[IRNSS][1][1]=ui->comboBoxFreqPhaseIRNSS_2;
    ComboBoxGNSSFreq[IRNSS][1][2]=ui->comboBoxFreqGCIRNSS_2;
    ComboBoxGNSSFreq[IRNSS][2][0]=ui->comboBoxFreqCodeIRNSS_3;
    ComboBoxGNSSFreq[IRNSS][2][1]=ui->comboBoxFreqPhaseIRNSS_3;
    ComboBoxGNSSFreq[IRNSS][2][2]=ui->comboBoxFreqGCIRNSS_3;
    //meas
    ComboBoxGNSSMeas[IRNSS][0][0][0]=ui->comboBoxMeasCodeFreq1IRNSS_1;
    ComboBoxGNSSMeas[IRNSS][0][0][1]=ui->comboBoxMeasCodeFreq2IRNSS_1;
    ComboBoxGNSSMeas[IRNSS][0][1][0]=ui->comboBoxMeasPhaseFreq1IRNSS_1;
    ComboBoxGNSSMeas[IRNSS][0][1][1]=ui->comboBoxMeasPhaseFreq2IRNSS_1;
    ComboBoxGNSSMeas[IRNSS][0][2][0]=ui->comboBoxMeasGCCodeIRNSS_1;
    ComboBoxGNSSMeas[IRNSS][0][2][1]=ui->comboBoxMeasGCPhaseIRNSS_1;
    ComboBoxGNSSMeas[IRNSS][1][0][0]=ui->comboBoxMeasCodeFreq1IRNSS_2;
    ComboBoxGNSSMeas[IRNSS][1][0][1]=ui->comboBoxMeasCodeFreq2IRNSS_2;
    ComboBoxGNSSMeas[IRNSS][1][1][0]=ui->comboBoxMeasPhaseFreq1IRNSS_2;
    ComboBoxGNSSMeas[IRNSS][1][1][1]=ui->comboBoxMeasPhaseFreq2IRNSS_2;
    ComboBoxGNSSMeas[IRNSS][1][2][0]=ui->comboBoxMeasGCCodeIRNSS_2;
    ComboBoxGNSSMeas[IRNSS][1][2][1]=ui->comboBoxMeasGCPhaseIRNSS_2;
    ComboBoxGNSSMeas[IRNSS][2][0][0]=ui->comboBoxMeasCodeFreq1IRNSS_3;
    ComboBoxGNSSMeas[IRNSS][2][0][1]=ui->comboBoxMeasCodeFreq2IRNSS_3;
    ComboBoxGNSSMeas[IRNSS][2][1][0]=ui->comboBoxMeasPhaseFreq1IRNSS_3;
    ComboBoxGNSSMeas[IRNSS][2][1][1]=ui->comboBoxMeasPhaseFreq2IRNSS_3;
    ComboBoxGNSSMeas[IRNSS][2][2][0]=ui->comboBoxMeasGCCodeIRNSS_3;
    ComboBoxGNSSMeas[IRNSS][2][2][1]=ui->comboBoxMeasGCPhaseIRNSS_3;
}
//Function to initialize pointers to GNSS smooth frequency comboBox
void gLAB_GUI::InitSmoothComboBoxPointers() {
    //GPS
    ComboBoxSmoothWithTypeAll[GPS][0]=ui->comboBoxSmoothWithGPS_1;
    ComboBoxSmoothWithTypeAll[GPS][1]=ui->comboBoxSmoothWithGPS_2;
    ComboBoxSmoothWithTypeAll[GPS][2]=ui->comboBoxSmoothWithGPS_3;
    ComboBoxSmoothWithFreqAll[GPS][0][0]=ui->comboBoxSmoothFreq1GPS_1;
    ComboBoxSmoothWithFreqAll[GPS][0][1]=ui->comboBoxSmoothFreq2GPS_1;
    ComboBoxSmoothWithFreqAll[GPS][1][0]=ui->comboBoxSmoothFreq1GPS_2;
    ComboBoxSmoothWithFreqAll[GPS][1][1]=ui->comboBoxSmoothFreq2GPS_2;
    ComboBoxSmoothWithFreqAll[GPS][2][0]=ui->comboBoxSmoothFreq1GPS_3;
    ComboBoxSmoothWithFreqAll[GPS][2][1]=ui->comboBoxSmoothFreq2GPS_3;
    ComboBoxSmoothWithMeasAll[GPS][0][0]=ui->comboBoxSmoothCode1GPS_1;
    ComboBoxSmoothWithMeasAll[GPS][0][1]=ui->comboBoxSmoothPhase1GPS_1;
    ComboBoxSmoothWithMeasAll[GPS][0][2]=ui->comboBoxSmoothPhase2GPS_1;
    ComboBoxSmoothWithMeasAll[GPS][1][0]=ui->comboBoxSmoothCode1GPS_2;
    ComboBoxSmoothWithMeasAll[GPS][1][1]=ui->comboBoxSmoothPhase1GPS_2;
    ComboBoxSmoothWithMeasAll[GPS][1][2]=ui->comboBoxSmoothPhase2GPS_2;
    ComboBoxSmoothWithMeasAll[GPS][2][0]=ui->comboBoxSmoothCode1GPS_3;
    ComboBoxSmoothWithMeasAll[GPS][2][1]=ui->comboBoxSmoothPhase1GPS_3;
    ComboBoxSmoothWithMeasAll[GPS][2][2]=ui->comboBoxSmoothPhase2GPS_3;
    smoothWithFreqIndexAll[GPS][0][0]=-1;
    smoothWithFreqIndexAll[GPS][0][1]=-1;
    smoothWithFreqIndexAll[GPS][1][0]=-1;
    smoothWithFreqIndexAll[GPS][1][1]=-1;
    smoothWithFreqIndexAll[GPS][2][0]=-1;
    smoothWithFreqIndexAll[GPS][2][1]=-1;
    //Galileo
    ComboBoxSmoothWithTypeAll[Galileo][0]=ui->comboBoxSmoothWithGalileo_1;
    ComboBoxSmoothWithTypeAll[Galileo][1]=ui->comboBoxSmoothWithGalileo_2;
    ComboBoxSmoothWithTypeAll[Galileo][2]=ui->comboBoxSmoothWithGalileo_3;
    ComboBoxSmoothWithFreqAll[Galileo][0][0]=ui->comboBoxSmoothFreq1Galileo_1;
    ComboBoxSmoothWithFreqAll[Galileo][0][1]=ui->comboBoxSmoothFreq2Galileo_1;
    ComboBoxSmoothWithFreqAll[Galileo][1][0]=ui->comboBoxSmoothFreq1Galileo_2;
    ComboBoxSmoothWithFreqAll[Galileo][1][1]=ui->comboBoxSmoothFreq2Galileo_2;
    ComboBoxSmoothWithFreqAll[Galileo][2][0]=ui->comboBoxSmoothFreq1Galileo_3;
    ComboBoxSmoothWithFreqAll[Galileo][2][1]=ui->comboBoxSmoothFreq2Galileo_3;
    ComboBoxSmoothWithMeasAll[Galileo][0][0]=ui->comboBoxSmoothCode1Galileo_1;
    ComboBoxSmoothWithMeasAll[Galileo][0][1]=ui->comboBoxSmoothPhase1Galileo_1;
    ComboBoxSmoothWithMeasAll[Galileo][0][2]=ui->comboBoxSmoothPhase2Galileo_1;
    ComboBoxSmoothWithMeasAll[Galileo][1][0]=ui->comboBoxSmoothCode1Galileo_2;
    ComboBoxSmoothWithMeasAll[Galileo][1][1]=ui->comboBoxSmoothPhase1Galileo_2;
    ComboBoxSmoothWithMeasAll[Galileo][1][2]=ui->comboBoxSmoothPhase2Galileo_2;
    ComboBoxSmoothWithMeasAll[Galileo][2][0]=ui->comboBoxSmoothCode1Galileo_3;
    ComboBoxSmoothWithMeasAll[Galileo][2][1]=ui->comboBoxSmoothPhase1Galileo_3;
    ComboBoxSmoothWithMeasAll[Galileo][2][2]=ui->comboBoxSmoothPhase2Galileo_3;
    smoothWithFreqIndexAll[Galileo][0][0]=-1;
    smoothWithFreqIndexAll[Galileo][0][1]=-1;
    smoothWithFreqIndexAll[Galileo][1][0]=-1;
    smoothWithFreqIndexAll[Galileo][1][1]=-1;
    smoothWithFreqIndexAll[Galileo][2][0]=-1;
    smoothWithFreqIndexAll[Galileo][2][1]=-1;
    //GLONASS
    ComboBoxSmoothWithTypeAll[GLONASS][0]=ui->comboBoxSmoothWithGLONASS_1;
    ComboBoxSmoothWithTypeAll[GLONASS][1]=ui->comboBoxSmoothWithGLONASS_2;
    ComboBoxSmoothWithTypeAll[GLONASS][2]=ui->comboBoxSmoothWithGLONASS_3;
    ComboBoxSmoothWithFreqAll[GLONASS][0][0]=ui->comboBoxSmoothFreq1GLONASS_1;
    ComboBoxSmoothWithFreqAll[GLONASS][0][1]=ui->comboBoxSmoothFreq2GLONASS_1;
    ComboBoxSmoothWithFreqAll[GLONASS][1][0]=ui->comboBoxSmoothFreq1GLONASS_2;
    ComboBoxSmoothWithFreqAll[GLONASS][1][1]=ui->comboBoxSmoothFreq2GLONASS_2;
    ComboBoxSmoothWithFreqAll[GLONASS][2][0]=ui->comboBoxSmoothFreq1GLONASS_3;
    ComboBoxSmoothWithFreqAll[GLONASS][2][1]=ui->comboBoxSmoothFreq2GLONASS_3;
    ComboBoxSmoothWithMeasAll[GLONASS][0][0]=ui->comboBoxSmoothCode1GLONASS_1;
    ComboBoxSmoothWithMeasAll[GLONASS][0][1]=ui->comboBoxSmoothPhase1GLONASS_1;
    ComboBoxSmoothWithMeasAll[GLONASS][0][2]=ui->comboBoxSmoothPhase2GLONASS_1;
    ComboBoxSmoothWithMeasAll[GLONASS][1][0]=ui->comboBoxSmoothCode1GLONASS_2;
    ComboBoxSmoothWithMeasAll[GLONASS][1][1]=ui->comboBoxSmoothPhase1GLONASS_2;
    ComboBoxSmoothWithMeasAll[GLONASS][1][2]=ui->comboBoxSmoothPhase2GLONASS_2;
    ComboBoxSmoothWithMeasAll[GLONASS][2][0]=ui->comboBoxSmoothCode1GLONASS_3;
    ComboBoxSmoothWithMeasAll[GLONASS][2][1]=ui->comboBoxSmoothPhase1GLONASS_3;
    ComboBoxSmoothWithMeasAll[GLONASS][2][2]=ui->comboBoxSmoothPhase2GLONASS_3;
    smoothWithFreqIndexAll[GLONASS][0][0]=-1;
    smoothWithFreqIndexAll[GLONASS][0][1]=-1;
    smoothWithFreqIndexAll[GLONASS][1][0]=-1;
    smoothWithFreqIndexAll[GLONASS][1][1]=-1;
    smoothWithFreqIndexAll[GLONASS][2][0]=-1;
    smoothWithFreqIndexAll[GLONASS][2][1]=-1;
    //GEO
    ComboBoxSmoothWithTypeAll[GEO][0]=ui->comboBoxSmoothWithGEO_1;
    ComboBoxSmoothWithTypeAll[GEO][1]=ui->comboBoxSmoothWithGEO_2;
    ComboBoxSmoothWithTypeAll[GEO][2]=ui->comboBoxSmoothWithGEO_3;
    ComboBoxSmoothWithFreqAll[GEO][0][0]=ui->comboBoxSmoothFreq1GEO_1;
    ComboBoxSmoothWithFreqAll[GEO][0][1]=ui->comboBoxSmoothFreq2GEO_1;
    ComboBoxSmoothWithFreqAll[GEO][1][0]=ui->comboBoxSmoothFreq1GEO_2;
    ComboBoxSmoothWithFreqAll[GEO][1][1]=ui->comboBoxSmoothFreq2GEO_2;
    ComboBoxSmoothWithFreqAll[GEO][2][0]=ui->comboBoxSmoothFreq1GEO_3;
    ComboBoxSmoothWithFreqAll[GEO][2][1]=ui->comboBoxSmoothFreq2GEO_3;
    ComboBoxSmoothWithMeasAll[GEO][0][0]=ui->comboBoxSmoothCode1GEO_1;
    ComboBoxSmoothWithMeasAll[GEO][0][1]=ui->comboBoxSmoothPhase1GEO_1;
    ComboBoxSmoothWithMeasAll[GEO][0][2]=ui->comboBoxSmoothPhase2GEO_1;
    ComboBoxSmoothWithMeasAll[GEO][1][0]=ui->comboBoxSmoothCode1GEO_2;
    ComboBoxSmoothWithMeasAll[GEO][1][1]=ui->comboBoxSmoothPhase1GEO_2;
    ComboBoxSmoothWithMeasAll[GEO][1][2]=ui->comboBoxSmoothPhase2GEO_2;
    ComboBoxSmoothWithMeasAll[GEO][2][0]=ui->comboBoxSmoothCode1GEO_3;
    ComboBoxSmoothWithMeasAll[GEO][2][1]=ui->comboBoxSmoothPhase1GEO_3;
    ComboBoxSmoothWithMeasAll[GEO][2][2]=ui->comboBoxSmoothPhase2GEO_3;
    smoothWithFreqIndexAll[GEO][0][0]=-1;
    smoothWithFreqIndexAll[GEO][0][1]=-1;
    smoothWithFreqIndexAll[GEO][1][0]=-1;
    smoothWithFreqIndexAll[GEO][1][1]=-1;
    smoothWithFreqIndexAll[GEO][2][0]=-1;
    smoothWithFreqIndexAll[GEO][2][1]=-1;
    //BDS
    ComboBoxSmoothWithTypeAll[BDS][0]=ui->comboBoxSmoothWithBDS_1;
    ComboBoxSmoothWithTypeAll[BDS][1]=ui->comboBoxSmoothWithBDS_2;
    ComboBoxSmoothWithTypeAll[BDS][2]=ui->comboBoxSmoothWithBDS_3;
    ComboBoxSmoothWithFreqAll[BDS][0][0]=ui->comboBoxSmoothFreq1BDS_1;
    ComboBoxSmoothWithFreqAll[BDS][0][1]=ui->comboBoxSmoothFreq2BDS_1;
    ComboBoxSmoothWithFreqAll[BDS][1][0]=ui->comboBoxSmoothFreq1BDS_2;
    ComboBoxSmoothWithFreqAll[BDS][1][1]=ui->comboBoxSmoothFreq2BDS_2;
    ComboBoxSmoothWithFreqAll[BDS][2][0]=ui->comboBoxSmoothFreq1BDS_3;
    ComboBoxSmoothWithFreqAll[BDS][2][1]=ui->comboBoxSmoothFreq2BDS_3;
    ComboBoxSmoothWithMeasAll[BDS][0][0]=ui->comboBoxSmoothCode1BDS_1;
    ComboBoxSmoothWithMeasAll[BDS][0][1]=ui->comboBoxSmoothPhase1BDS_1;
    ComboBoxSmoothWithMeasAll[BDS][0][2]=ui->comboBoxSmoothPhase2BDS_1;
    ComboBoxSmoothWithMeasAll[BDS][1][0]=ui->comboBoxSmoothCode1BDS_2;
    ComboBoxSmoothWithMeasAll[BDS][1][1]=ui->comboBoxSmoothPhase1BDS_2;
    ComboBoxSmoothWithMeasAll[BDS][1][2]=ui->comboBoxSmoothPhase2BDS_2;
    ComboBoxSmoothWithMeasAll[BDS][2][0]=ui->comboBoxSmoothCode1BDS_3;
    ComboBoxSmoothWithMeasAll[BDS][2][1]=ui->comboBoxSmoothPhase1BDS_3;
    ComboBoxSmoothWithMeasAll[BDS][2][2]=ui->comboBoxSmoothPhase2BDS_3;
    smoothWithFreqIndexAll[BDS][0][0]=-1;
    smoothWithFreqIndexAll[BDS][0][1]=-1;
    smoothWithFreqIndexAll[BDS][1][0]=-1;
    smoothWithFreqIndexAll[BDS][1][1]=-1;
    smoothWithFreqIndexAll[BDS][2][0]=-1;
    smoothWithFreqIndexAll[BDS][2][1]=-1;
    //QZSS
    ComboBoxSmoothWithTypeAll[QZSS][0]=ui->comboBoxSmoothWithQZSS_1;
    ComboBoxSmoothWithTypeAll[QZSS][1]=ui->comboBoxSmoothWithQZSS_2;
    ComboBoxSmoothWithTypeAll[QZSS][2]=ui->comboBoxSmoothWithQZSS_3;
    ComboBoxSmoothWithFreqAll[QZSS][0][0]=ui->comboBoxSmoothFreq1QZSS_1;
    ComboBoxSmoothWithFreqAll[QZSS][0][1]=ui->comboBoxSmoothFreq2QZSS_1;
    ComboBoxSmoothWithFreqAll[QZSS][1][0]=ui->comboBoxSmoothFreq1QZSS_2;
    ComboBoxSmoothWithFreqAll[QZSS][1][1]=ui->comboBoxSmoothFreq2QZSS_2;
    ComboBoxSmoothWithFreqAll[QZSS][2][0]=ui->comboBoxSmoothFreq1QZSS_3;
    ComboBoxSmoothWithFreqAll[QZSS][2][1]=ui->comboBoxSmoothFreq2QZSS_3;
    ComboBoxSmoothWithMeasAll[QZSS][0][0]=ui->comboBoxSmoothCode1QZSS_1;
    ComboBoxSmoothWithMeasAll[QZSS][0][1]=ui->comboBoxSmoothPhase1QZSS_1;
    ComboBoxSmoothWithMeasAll[QZSS][0][2]=ui->comboBoxSmoothPhase2QZSS_1;
    ComboBoxSmoothWithMeasAll[QZSS][1][0]=ui->comboBoxSmoothCode1QZSS_2;
    ComboBoxSmoothWithMeasAll[QZSS][1][1]=ui->comboBoxSmoothPhase1QZSS_2;
    ComboBoxSmoothWithMeasAll[QZSS][1][2]=ui->comboBoxSmoothPhase2QZSS_2;
    ComboBoxSmoothWithMeasAll[QZSS][2][0]=ui->comboBoxSmoothCode1QZSS_3;
    ComboBoxSmoothWithMeasAll[QZSS][2][1]=ui->comboBoxSmoothPhase1QZSS_3;
    ComboBoxSmoothWithMeasAll[QZSS][2][2]=ui->comboBoxSmoothPhase2QZSS_3;
    smoothWithFreqIndexAll[QZSS][0][0]=-1;
    smoothWithFreqIndexAll[QZSS][0][1]=-1;
    smoothWithFreqIndexAll[QZSS][1][0]=-1;
    smoothWithFreqIndexAll[QZSS][1][1]=-1;
    smoothWithFreqIndexAll[QZSS][2][0]=-1;
    smoothWithFreqIndexAll[QZSS][2][1]=-1;
    //IRNSS
    ComboBoxSmoothWithTypeAll[IRNSS][0]=ui->comboBoxSmoothWithIRNSS_1;
    ComboBoxSmoothWithTypeAll[IRNSS][1]=ui->comboBoxSmoothWithIRNSS_2;
    ComboBoxSmoothWithTypeAll[IRNSS][2]=ui->comboBoxSmoothWithIRNSS_3;
    ComboBoxSmoothWithFreqAll[IRNSS][0][0]=ui->comboBoxSmoothFreq1IRNSS_1;
    ComboBoxSmoothWithFreqAll[IRNSS][0][1]=ui->comboBoxSmoothFreq2IRNSS_1;
    ComboBoxSmoothWithFreqAll[IRNSS][1][0]=ui->comboBoxSmoothFreq1IRNSS_2;
    ComboBoxSmoothWithFreqAll[IRNSS][1][1]=ui->comboBoxSmoothFreq2IRNSS_2;
    ComboBoxSmoothWithFreqAll[IRNSS][2][0]=ui->comboBoxSmoothFreq1IRNSS_3;
    ComboBoxSmoothWithFreqAll[IRNSS][2][1]=ui->comboBoxSmoothFreq2IRNSS_3;
    ComboBoxSmoothWithMeasAll[IRNSS][0][0]=ui->comboBoxSmoothCode1IRNSS_1;
    ComboBoxSmoothWithMeasAll[IRNSS][0][1]=ui->comboBoxSmoothPhase1IRNSS_1;
    ComboBoxSmoothWithMeasAll[IRNSS][0][2]=ui->comboBoxSmoothPhase2IRNSS_1;
    ComboBoxSmoothWithMeasAll[IRNSS][1][0]=ui->comboBoxSmoothCode1IRNSS_2;
    ComboBoxSmoothWithMeasAll[IRNSS][1][1]=ui->comboBoxSmoothPhase1IRNSS_2;
    ComboBoxSmoothWithMeasAll[IRNSS][1][2]=ui->comboBoxSmoothPhase2IRNSS_2;
    ComboBoxSmoothWithMeasAll[IRNSS][2][0]=ui->comboBoxSmoothCode1IRNSS_3;
    ComboBoxSmoothWithMeasAll[IRNSS][2][1]=ui->comboBoxSmoothPhase1IRNSS_3;
    ComboBoxSmoothWithMeasAll[IRNSS][2][2]=ui->comboBoxSmoothPhase2IRNSS_3;
    smoothWithFreqIndexAll[IRNSS][0][0]=-1;
    smoothWithFreqIndexAll[IRNSS][0][1]=-1;
    smoothWithFreqIndexAll[IRNSS][1][0]=-1;
    smoothWithFreqIndexAll[IRNSS][1][1]=-1;
    smoothWithFreqIndexAll[IRNSS][2][0]=-1;
    smoothWithFreqIndexAll[IRNSS][2][1]=-1;
}

//Function to initialize pointers to GNSS stdDev comboBox and lineEdit
void gLAB_GUI::InitGNSSStdDevPointers(){
    //GPS
    //Type
    ComboBoxstdDevType[GPS][0][0]=ui->comboBoxStdDevModeCodeGPS_1;
    ComboBoxstdDevType[GPS][0][1]=ui->comboBoxStdDevModePhaseGPS_1;
    ComboBoxstdDevType[GPS][0][2]=ui->comboBoxStdDevModeGCGPS_1;
    ComboBoxstdDevType[GPS][1][0]=ui->comboBoxStdDevModeCodeGPS_2;
    ComboBoxstdDevType[GPS][1][1]=ui->comboBoxStdDevModePhaseGPS_2;
    ComboBoxstdDevType[GPS][1][2]=ui->comboBoxStdDevModeGCGPS_2;
    ComboBoxstdDevType[GPS][2][0]=ui->comboBoxStdDevModeCodeGPS_3;
    ComboBoxstdDevType[GPS][2][1]=ui->comboBoxStdDevModePhaseGPS_3;
    ComboBoxstdDevType[GPS][2][2]=ui->comboBoxStdDevModeGCGPS_3;
    //Value
    LineEditstdDevValue[GPS][0][0][0]=ui->lineEditStdDevCodeAGPS_1;
    LineEditstdDevValue[GPS][0][0][1]=ui->lineEditStdDevCodeBGPS_1;
    LineEditstdDevValue[GPS][0][0][2]=ui->lineEditStdDevCodeCGPS_1;
    LineEditstdDevValue[GPS][0][1][0]=ui->lineEditStdDevPhaseAGPS_1;
    LineEditstdDevValue[GPS][0][1][1]=ui->lineEditStdDevPhaseBGPS_1;
    LineEditstdDevValue[GPS][0][1][2]=ui->lineEditStdDevPhaseCGPS_1;
    LineEditstdDevValue[GPS][0][2][0]=ui->lineEditStdDevGCAGPS_1;
    LineEditstdDevValue[GPS][0][2][1]=ui->lineEditStdDevGCBGPS_1;
    LineEditstdDevValue[GPS][0][2][2]=ui->lineEditStdDevGCCGPS_1;
    LineEditstdDevValue[GPS][1][0][0]=ui->lineEditStdDevCodeAGPS_2;
    LineEditstdDevValue[GPS][1][0][1]=ui->lineEditStdDevCodeBGPS_2;
    LineEditstdDevValue[GPS][1][0][2]=ui->lineEditStdDevCodeCGPS_2;
    LineEditstdDevValue[GPS][1][1][0]=ui->lineEditStdDevPhaseAGPS_2;
    LineEditstdDevValue[GPS][1][1][1]=ui->lineEditStdDevPhaseBGPS_2;
    LineEditstdDevValue[GPS][1][1][2]=ui->lineEditStdDevPhaseCGPS_2;
    LineEditstdDevValue[GPS][1][2][0]=ui->lineEditStdDevGCAGPS_2;
    LineEditstdDevValue[GPS][1][2][1]=ui->lineEditStdDevGCBGPS_2;
    LineEditstdDevValue[GPS][1][2][2]=ui->lineEditStdDevGCCGPS_2;
    LineEditstdDevValue[GPS][2][0][0]=ui->lineEditStdDevCodeAGPS_3;
    LineEditstdDevValue[GPS][2][0][1]=ui->lineEditStdDevCodeBGPS_3;
    LineEditstdDevValue[GPS][2][0][2]=ui->lineEditStdDevCodeCGPS_3;
    LineEditstdDevValue[GPS][2][1][0]=ui->lineEditStdDevPhaseAGPS_3;
    LineEditstdDevValue[GPS][2][1][1]=ui->lineEditStdDevPhaseBGPS_3;
    LineEditstdDevValue[GPS][2][1][2]=ui->lineEditStdDevPhaseCGPS_3;
    LineEditstdDevValue[GPS][2][2][0]=ui->lineEditStdDevGCAGPS_3;
    LineEditstdDevValue[GPS][2][2][1]=ui->lineEditStdDevGCBGPS_3;
    LineEditstdDevValue[GPS][2][2][2]=ui->lineEditStdDevGCCGPS_3;

    //Galileo
    //Type
    ComboBoxstdDevType[Galileo][0][0]=ui->comboBoxStdDevModeCodeGalileo_1;
    ComboBoxstdDevType[Galileo][0][1]=ui->comboBoxStdDevModePhaseGalileo_1;
    ComboBoxstdDevType[Galileo][0][2]=ui->comboBoxStdDevModeGCGalileo_1;
    ComboBoxstdDevType[Galileo][1][0]=ui->comboBoxStdDevModeCodeGalileo_2;
    ComboBoxstdDevType[Galileo][1][1]=ui->comboBoxStdDevModePhaseGalileo_2;
    ComboBoxstdDevType[Galileo][1][2]=ui->comboBoxStdDevModeGCGalileo_2;
    ComboBoxstdDevType[Galileo][2][0]=ui->comboBoxStdDevModeCodeGalileo_3;
    ComboBoxstdDevType[Galileo][2][1]=ui->comboBoxStdDevModePhaseGalileo_3;
    ComboBoxstdDevType[Galileo][2][2]=ui->comboBoxStdDevModeGCGalileo_3;
    //Value
    LineEditstdDevValue[Galileo][0][0][0]=ui->lineEditStdDevCodeAGalileo_1;
    LineEditstdDevValue[Galileo][0][0][1]=ui->lineEditStdDevCodeBGalileo_1;
    LineEditstdDevValue[Galileo][0][0][2]=ui->lineEditStdDevCodeCGalileo_1;
    LineEditstdDevValue[Galileo][0][1][0]=ui->lineEditStdDevPhaseAGalileo_1;
    LineEditstdDevValue[Galileo][0][1][1]=ui->lineEditStdDevPhaseBGalileo_1;
    LineEditstdDevValue[Galileo][0][1][2]=ui->lineEditStdDevPhaseCGalileo_1;
    LineEditstdDevValue[Galileo][0][2][0]=ui->lineEditStdDevGCAGalileo_1;
    LineEditstdDevValue[Galileo][0][2][1]=ui->lineEditStdDevGCBGalileo_1;
    LineEditstdDevValue[Galileo][0][2][2]=ui->lineEditStdDevGCCGalileo_1;
    LineEditstdDevValue[Galileo][1][0][0]=ui->lineEditStdDevCodeAGalileo_2;
    LineEditstdDevValue[Galileo][1][0][1]=ui->lineEditStdDevCodeBGalileo_2;
    LineEditstdDevValue[Galileo][1][0][2]=ui->lineEditStdDevCodeCGalileo_2;
    LineEditstdDevValue[Galileo][1][1][0]=ui->lineEditStdDevPhaseAGalileo_2;
    LineEditstdDevValue[Galileo][1][1][1]=ui->lineEditStdDevPhaseBGalileo_2;
    LineEditstdDevValue[Galileo][1][1][2]=ui->lineEditStdDevPhaseCGalileo_2;
    LineEditstdDevValue[Galileo][1][2][0]=ui->lineEditStdDevGCAGalileo_2;
    LineEditstdDevValue[Galileo][1][2][1]=ui->lineEditStdDevGCBGalileo_2;
    LineEditstdDevValue[Galileo][1][2][2]=ui->lineEditStdDevGCCGalileo_2;
    LineEditstdDevValue[Galileo][2][0][0]=ui->lineEditStdDevCodeAGalileo_3;
    LineEditstdDevValue[Galileo][2][0][1]=ui->lineEditStdDevCodeBGalileo_3;
    LineEditstdDevValue[Galileo][2][0][2]=ui->lineEditStdDevCodeCGalileo_3;
    LineEditstdDevValue[Galileo][2][1][0]=ui->lineEditStdDevPhaseAGalileo_3;
    LineEditstdDevValue[Galileo][2][1][1]=ui->lineEditStdDevPhaseBGalileo_3;
    LineEditstdDevValue[Galileo][2][1][2]=ui->lineEditStdDevPhaseCGalileo_3;
    LineEditstdDevValue[Galileo][2][2][0]=ui->lineEditStdDevGCAGalileo_3;
    LineEditstdDevValue[Galileo][2][2][1]=ui->lineEditStdDevGCBGalileo_3;
    LineEditstdDevValue[Galileo][2][2][2]=ui->lineEditStdDevGCCGalileo_3;

    //GLONASS
    //Type
    ComboBoxstdDevType[GLONASS][0][0]=ui->comboBoxStdDevModeCodeGLONASS_1;
    ComboBoxstdDevType[GLONASS][0][1]=ui->comboBoxStdDevModePhaseGLONASS_1;
    ComboBoxstdDevType[GLONASS][0][2]=ui->comboBoxStdDevModeGCGLONASS_1;
    ComboBoxstdDevType[GLONASS][1][0]=ui->comboBoxStdDevModeCodeGLONASS_2;
    ComboBoxstdDevType[GLONASS][1][1]=ui->comboBoxStdDevModePhaseGLONASS_2;
    ComboBoxstdDevType[GLONASS][1][2]=ui->comboBoxStdDevModeGCGLONASS_2;
    ComboBoxstdDevType[GLONASS][2][0]=ui->comboBoxStdDevModeCodeGLONASS_3;
    ComboBoxstdDevType[GLONASS][2][1]=ui->comboBoxStdDevModePhaseGLONASS_3;
    ComboBoxstdDevType[GLONASS][2][2]=ui->comboBoxStdDevModeGCGLONASS_3;
    //Value
    LineEditstdDevValue[GLONASS][0][0][0]=ui->lineEditStdDevCodeAGLONASS_1;
    LineEditstdDevValue[GLONASS][0][0][1]=ui->lineEditStdDevCodeBGLONASS_1;
    LineEditstdDevValue[GLONASS][0][0][2]=ui->lineEditStdDevCodeCGLONASS_1;
    LineEditstdDevValue[GLONASS][0][1][0]=ui->lineEditStdDevPhaseAGLONASS_1;
    LineEditstdDevValue[GLONASS][0][1][1]=ui->lineEditStdDevPhaseBGLONASS_1;
    LineEditstdDevValue[GLONASS][0][1][2]=ui->lineEditStdDevPhaseCGLONASS_1;
    LineEditstdDevValue[GLONASS][0][2][0]=ui->lineEditStdDevGCAGLONASS_1;
    LineEditstdDevValue[GLONASS][0][2][1]=ui->lineEditStdDevGCBGLONASS_1;
    LineEditstdDevValue[GLONASS][0][2][2]=ui->lineEditStdDevGCCGLONASS_1;
    LineEditstdDevValue[GLONASS][1][0][0]=ui->lineEditStdDevCodeAGLONASS_2;
    LineEditstdDevValue[GLONASS][1][0][1]=ui->lineEditStdDevCodeBGLONASS_2;
    LineEditstdDevValue[GLONASS][1][0][2]=ui->lineEditStdDevCodeCGLONASS_2;
    LineEditstdDevValue[GLONASS][1][1][0]=ui->lineEditStdDevPhaseAGLONASS_2;
    LineEditstdDevValue[GLONASS][1][1][1]=ui->lineEditStdDevPhaseBGLONASS_2;
    LineEditstdDevValue[GLONASS][1][1][2]=ui->lineEditStdDevPhaseCGLONASS_2;
    LineEditstdDevValue[GLONASS][1][2][0]=ui->lineEditStdDevGCAGLONASS_2;
    LineEditstdDevValue[GLONASS][1][2][1]=ui->lineEditStdDevGCBGLONASS_2;
    LineEditstdDevValue[GLONASS][1][2][2]=ui->lineEditStdDevGCCGLONASS_2;
    LineEditstdDevValue[GLONASS][2][0][0]=ui->lineEditStdDevCodeAGLONASS_3;
    LineEditstdDevValue[GLONASS][2][0][1]=ui->lineEditStdDevCodeBGLONASS_3;
    LineEditstdDevValue[GLONASS][2][0][2]=ui->lineEditStdDevCodeCGLONASS_3;
    LineEditstdDevValue[GLONASS][2][1][0]=ui->lineEditStdDevPhaseAGLONASS_3;
    LineEditstdDevValue[GLONASS][2][1][1]=ui->lineEditStdDevPhaseBGLONASS_3;
    LineEditstdDevValue[GLONASS][2][1][2]=ui->lineEditStdDevPhaseCGLONASS_3;
    LineEditstdDevValue[GLONASS][2][2][0]=ui->lineEditStdDevGCAGLONASS_3;
    LineEditstdDevValue[GLONASS][2][2][1]=ui->lineEditStdDevGCBGLONASS_3;
    LineEditstdDevValue[GLONASS][2][2][2]=ui->lineEditStdDevGCCGLONASS_3;

    //GEO
    //Type
    ComboBoxstdDevType[GEO][0][0]=ui->comboBoxStdDevModeCodeGEO_1;
    ComboBoxstdDevType[GEO][0][1]=ui->comboBoxStdDevModePhaseGEO_1;
    ComboBoxstdDevType[GEO][0][2]=ui->comboBoxStdDevModeGCGEO_1;
    ComboBoxstdDevType[GEO][1][0]=ui->comboBoxStdDevModeCodeGEO_2;
    ComboBoxstdDevType[GEO][1][1]=ui->comboBoxStdDevModePhaseGEO_2;
    ComboBoxstdDevType[GEO][1][2]=ui->comboBoxStdDevModeGCGEO_2;
    ComboBoxstdDevType[GEO][2][0]=ui->comboBoxStdDevModeCodeGEO_3;
    ComboBoxstdDevType[GEO][2][1]=ui->comboBoxStdDevModePhaseGEO_3;
    ComboBoxstdDevType[GEO][2][2]=ui->comboBoxStdDevModeGCGEO_3;
    //Value
    LineEditstdDevValue[GEO][0][0][0]=ui->lineEditStdDevCodeAGEO_1;
    LineEditstdDevValue[GEO][0][0][1]=ui->lineEditStdDevCodeBGEO_1;
    LineEditstdDevValue[GEO][0][0][2]=ui->lineEditStdDevCodeCGEO_1;
    LineEditstdDevValue[GEO][0][1][0]=ui->lineEditStdDevPhaseAGEO_1;
    LineEditstdDevValue[GEO][0][1][1]=ui->lineEditStdDevPhaseBGEO_1;
    LineEditstdDevValue[GEO][0][1][2]=ui->lineEditStdDevPhaseCGEO_1;
    LineEditstdDevValue[GEO][0][2][0]=ui->lineEditStdDevGCAGEO_1;
    LineEditstdDevValue[GEO][0][2][1]=ui->lineEditStdDevGCBGEO_1;
    LineEditstdDevValue[GEO][0][2][2]=ui->lineEditStdDevGCCGEO_1;
    LineEditstdDevValue[GEO][1][0][0]=ui->lineEditStdDevCodeAGEO_2;
    LineEditstdDevValue[GEO][1][0][1]=ui->lineEditStdDevCodeBGEO_2;
    LineEditstdDevValue[GEO][1][0][2]=ui->lineEditStdDevCodeCGEO_2;
    LineEditstdDevValue[GEO][1][1][0]=ui->lineEditStdDevPhaseAGEO_2;
    LineEditstdDevValue[GEO][1][1][1]=ui->lineEditStdDevPhaseBGEO_2;
    LineEditstdDevValue[GEO][1][1][2]=ui->lineEditStdDevPhaseCGEO_2;
    LineEditstdDevValue[GEO][1][2][0]=ui->lineEditStdDevGCAGEO_2;
    LineEditstdDevValue[GEO][1][2][1]=ui->lineEditStdDevGCBGEO_2;
    LineEditstdDevValue[GEO][1][2][2]=ui->lineEditStdDevGCCGEO_2;
    LineEditstdDevValue[GEO][2][0][0]=ui->lineEditStdDevCodeAGEO_3;
    LineEditstdDevValue[GEO][2][0][1]=ui->lineEditStdDevCodeBGEO_3;
    LineEditstdDevValue[GEO][2][0][2]=ui->lineEditStdDevCodeCGEO_3;
    LineEditstdDevValue[GEO][2][1][0]=ui->lineEditStdDevPhaseAGEO_3;
    LineEditstdDevValue[GEO][2][1][1]=ui->lineEditStdDevPhaseBGEO_3;
    LineEditstdDevValue[GEO][2][1][2]=ui->lineEditStdDevPhaseCGEO_3;
    LineEditstdDevValue[GEO][2][2][0]=ui->lineEditStdDevGCAGEO_3;
    LineEditstdDevValue[GEO][2][2][1]=ui->lineEditStdDevGCBGEO_3;
    LineEditstdDevValue[GEO][2][2][2]=ui->lineEditStdDevGCCGEO_3;

    //BDS
    //Type
    ComboBoxstdDevType[BDS][0][0]=ui->comboBoxStdDevModeCodeBDS_1;
    ComboBoxstdDevType[BDS][0][1]=ui->comboBoxStdDevModePhaseBDS_1;
    ComboBoxstdDevType[BDS][0][2]=ui->comboBoxStdDevModeGCBDS_1;
    ComboBoxstdDevType[BDS][1][0]=ui->comboBoxStdDevModeCodeBDS_2;
    ComboBoxstdDevType[BDS][1][1]=ui->comboBoxStdDevModePhaseBDS_2;
    ComboBoxstdDevType[BDS][1][2]=ui->comboBoxStdDevModeGCBDS_2;
    ComboBoxstdDevType[BDS][2][0]=ui->comboBoxStdDevModeCodeBDS_3;
    ComboBoxstdDevType[BDS][2][1]=ui->comboBoxStdDevModePhaseBDS_3;
    ComboBoxstdDevType[BDS][2][2]=ui->comboBoxStdDevModeGCBDS_3;
    //Value
    LineEditstdDevValue[BDS][0][0][0]=ui->lineEditStdDevCodeABDS_1;
    LineEditstdDevValue[BDS][0][0][1]=ui->lineEditStdDevCodeBBDS_1;
    LineEditstdDevValue[BDS][0][0][2]=ui->lineEditStdDevCodeCBDS_1;
    LineEditstdDevValue[BDS][0][1][0]=ui->lineEditStdDevPhaseABDS_1;
    LineEditstdDevValue[BDS][0][1][1]=ui->lineEditStdDevPhaseBBDS_1;
    LineEditstdDevValue[BDS][0][1][2]=ui->lineEditStdDevPhaseCBDS_1;
    LineEditstdDevValue[BDS][0][2][0]=ui->lineEditStdDevGCABDS_1;
    LineEditstdDevValue[BDS][0][2][1]=ui->lineEditStdDevGCBBDS_1;
    LineEditstdDevValue[BDS][0][2][2]=ui->lineEditStdDevGCCBDS_1;
    LineEditstdDevValue[BDS][1][0][0]=ui->lineEditStdDevCodeABDS_2;
    LineEditstdDevValue[BDS][1][0][1]=ui->lineEditStdDevCodeBBDS_2;
    LineEditstdDevValue[BDS][1][0][2]=ui->lineEditStdDevCodeCBDS_2;
    LineEditstdDevValue[BDS][1][1][0]=ui->lineEditStdDevPhaseABDS_2;
    LineEditstdDevValue[BDS][1][1][1]=ui->lineEditStdDevPhaseBBDS_2;
    LineEditstdDevValue[BDS][1][1][2]=ui->lineEditStdDevPhaseCBDS_2;
    LineEditstdDevValue[BDS][1][2][0]=ui->lineEditStdDevGCABDS_2;
    LineEditstdDevValue[BDS][1][2][1]=ui->lineEditStdDevGCBBDS_2;
    LineEditstdDevValue[BDS][1][2][2]=ui->lineEditStdDevGCCBDS_2;
    LineEditstdDevValue[BDS][2][0][0]=ui->lineEditStdDevCodeABDS_3;
    LineEditstdDevValue[BDS][2][0][1]=ui->lineEditStdDevCodeBBDS_3;
    LineEditstdDevValue[BDS][2][0][2]=ui->lineEditStdDevCodeCBDS_3;
    LineEditstdDevValue[BDS][2][1][0]=ui->lineEditStdDevPhaseABDS_3;
    LineEditstdDevValue[BDS][2][1][1]=ui->lineEditStdDevPhaseBBDS_3;
    LineEditstdDevValue[BDS][2][1][2]=ui->lineEditStdDevPhaseCBDS_3;
    LineEditstdDevValue[BDS][2][2][0]=ui->lineEditStdDevGCABDS_3;
    LineEditstdDevValue[BDS][2][2][1]=ui->lineEditStdDevGCBBDS_3;
    LineEditstdDevValue[BDS][2][2][2]=ui->lineEditStdDevGCCBDS_3;

    //QZSS
    //Type
    ComboBoxstdDevType[QZSS][0][0]=ui->comboBoxStdDevModeCodeQZSS_1;
    ComboBoxstdDevType[QZSS][0][1]=ui->comboBoxStdDevModePhaseQZSS_1;
    ComboBoxstdDevType[QZSS][0][2]=ui->comboBoxStdDevModeGCQZSS_1;
    ComboBoxstdDevType[QZSS][1][0]=ui->comboBoxStdDevModeCodeQZSS_2;
    ComboBoxstdDevType[QZSS][1][1]=ui->comboBoxStdDevModePhaseQZSS_2;
    ComboBoxstdDevType[QZSS][1][2]=ui->comboBoxStdDevModeGCQZSS_2;
    ComboBoxstdDevType[QZSS][2][0]=ui->comboBoxStdDevModeCodeQZSS_3;
    ComboBoxstdDevType[QZSS][2][1]=ui->comboBoxStdDevModePhaseQZSS_3;
    ComboBoxstdDevType[QZSS][2][2]=ui->comboBoxStdDevModeGCQZSS_3;
    //Value
    LineEditstdDevValue[QZSS][0][0][0]=ui->lineEditStdDevCodeAQZSS_1;
    LineEditstdDevValue[QZSS][0][0][1]=ui->lineEditStdDevCodeBQZSS_1;
    LineEditstdDevValue[QZSS][0][0][2]=ui->lineEditStdDevCodeCQZSS_1;
    LineEditstdDevValue[QZSS][0][1][0]=ui->lineEditStdDevPhaseAQZSS_1;
    LineEditstdDevValue[QZSS][0][1][1]=ui->lineEditStdDevPhaseBQZSS_1;
    LineEditstdDevValue[QZSS][0][1][2]=ui->lineEditStdDevPhaseCQZSS_1;
    LineEditstdDevValue[QZSS][0][2][0]=ui->lineEditStdDevGCAQZSS_1;
    LineEditstdDevValue[QZSS][0][2][1]=ui->lineEditStdDevGCBQZSS_1;
    LineEditstdDevValue[QZSS][0][2][2]=ui->lineEditStdDevGCCQZSS_1;
    LineEditstdDevValue[QZSS][1][0][0]=ui->lineEditStdDevCodeAQZSS_2;
    LineEditstdDevValue[QZSS][1][0][1]=ui->lineEditStdDevCodeBQZSS_2;
    LineEditstdDevValue[QZSS][1][0][2]=ui->lineEditStdDevCodeCQZSS_2;
    LineEditstdDevValue[QZSS][1][1][0]=ui->lineEditStdDevPhaseAQZSS_2;
    LineEditstdDevValue[QZSS][1][1][1]=ui->lineEditStdDevPhaseBQZSS_2;
    LineEditstdDevValue[QZSS][1][1][2]=ui->lineEditStdDevPhaseCQZSS_2;
    LineEditstdDevValue[QZSS][1][2][0]=ui->lineEditStdDevGCAQZSS_2;
    LineEditstdDevValue[QZSS][1][2][1]=ui->lineEditStdDevGCBQZSS_2;
    LineEditstdDevValue[QZSS][1][2][2]=ui->lineEditStdDevGCCQZSS_2;
    LineEditstdDevValue[QZSS][2][0][0]=ui->lineEditStdDevCodeAQZSS_3;
    LineEditstdDevValue[QZSS][2][0][1]=ui->lineEditStdDevCodeBQZSS_3;
    LineEditstdDevValue[QZSS][2][0][2]=ui->lineEditStdDevCodeCQZSS_3;
    LineEditstdDevValue[QZSS][2][1][0]=ui->lineEditStdDevPhaseAQZSS_3;
    LineEditstdDevValue[QZSS][2][1][1]=ui->lineEditStdDevPhaseBQZSS_3;
    LineEditstdDevValue[QZSS][2][1][2]=ui->lineEditStdDevPhaseCQZSS_3;
    LineEditstdDevValue[QZSS][2][2][0]=ui->lineEditStdDevGCAQZSS_3;
    LineEditstdDevValue[QZSS][2][2][1]=ui->lineEditStdDevGCBQZSS_3;
    LineEditstdDevValue[QZSS][2][2][2]=ui->lineEditStdDevGCCQZSS_3;

    //IRNSS
    //Type
    ComboBoxstdDevType[IRNSS][0][0]=ui->comboBoxStdDevModeCodeIRNSS_1;
    ComboBoxstdDevType[IRNSS][0][1]=ui->comboBoxStdDevModePhaseIRNSS_1;
    ComboBoxstdDevType[IRNSS][0][2]=ui->comboBoxStdDevModeGCIRNSS_1;
    ComboBoxstdDevType[IRNSS][1][0]=ui->comboBoxStdDevModeCodeIRNSS_2;
    ComboBoxstdDevType[IRNSS][1][1]=ui->comboBoxStdDevModePhaseIRNSS_2;
    ComboBoxstdDevType[IRNSS][1][2]=ui->comboBoxStdDevModeGCIRNSS_2;
    ComboBoxstdDevType[IRNSS][2][0]=ui->comboBoxStdDevModeCodeIRNSS_3;
    ComboBoxstdDevType[IRNSS][2][1]=ui->comboBoxStdDevModePhaseIRNSS_3;
    ComboBoxstdDevType[IRNSS][2][2]=ui->comboBoxStdDevModeGCIRNSS_3;
    //Value
    LineEditstdDevValue[IRNSS][0][0][0]=ui->lineEditStdDevCodeAIRNSS_1;
    LineEditstdDevValue[IRNSS][0][0][1]=ui->lineEditStdDevCodeBIRNSS_1;
    LineEditstdDevValue[IRNSS][0][0][2]=ui->lineEditStdDevCodeCIRNSS_1;
    LineEditstdDevValue[IRNSS][0][1][0]=ui->lineEditStdDevPhaseAIRNSS_1;
    LineEditstdDevValue[IRNSS][0][1][1]=ui->lineEditStdDevPhaseBIRNSS_1;
    LineEditstdDevValue[IRNSS][0][1][2]=ui->lineEditStdDevPhaseCIRNSS_1;
    LineEditstdDevValue[IRNSS][0][2][0]=ui->lineEditStdDevGCAIRNSS_1;
    LineEditstdDevValue[IRNSS][0][2][1]=ui->lineEditStdDevGCBIRNSS_1;
    LineEditstdDevValue[IRNSS][0][2][2]=ui->lineEditStdDevGCCIRNSS_1;
    LineEditstdDevValue[IRNSS][1][0][0]=ui->lineEditStdDevCodeAIRNSS_2;
    LineEditstdDevValue[IRNSS][1][0][1]=ui->lineEditStdDevCodeBIRNSS_2;
    LineEditstdDevValue[IRNSS][1][0][2]=ui->lineEditStdDevCodeCIRNSS_2;
    LineEditstdDevValue[IRNSS][1][1][0]=ui->lineEditStdDevPhaseAIRNSS_2;
    LineEditstdDevValue[IRNSS][1][1][1]=ui->lineEditStdDevPhaseBIRNSS_2;
    LineEditstdDevValue[IRNSS][1][1][2]=ui->lineEditStdDevPhaseCIRNSS_2;
    LineEditstdDevValue[IRNSS][1][2][0]=ui->lineEditStdDevGCAIRNSS_2;
    LineEditstdDevValue[IRNSS][1][2][1]=ui->lineEditStdDevGCBIRNSS_2;
    LineEditstdDevValue[IRNSS][1][2][2]=ui->lineEditStdDevGCCIRNSS_2;
    LineEditstdDevValue[IRNSS][2][0][0]=ui->lineEditStdDevCodeAIRNSS_3;
    LineEditstdDevValue[IRNSS][2][0][1]=ui->lineEditStdDevCodeBIRNSS_3;
    LineEditstdDevValue[IRNSS][2][0][2]=ui->lineEditStdDevCodeCIRNSS_3;
    LineEditstdDevValue[IRNSS][2][1][0]=ui->lineEditStdDevPhaseAIRNSS_3;
    LineEditstdDevValue[IRNSS][2][1][1]=ui->lineEditStdDevPhaseBIRNSS_3;
    LineEditstdDevValue[IRNSS][2][1][2]=ui->lineEditStdDevPhaseCIRNSS_3;
    LineEditstdDevValue[IRNSS][2][2][0]=ui->lineEditStdDevGCAIRNSS_3;
    LineEditstdDevValue[IRNSS][2][2][1]=ui->lineEditStdDevGCBIRNSS_3;
    LineEditstdDevValue[IRNSS][2][2][2]=ui->lineEditStdDevGCCIRNSS_3;
}

// Function to set smoothed pseudorange measurements
void gLAB_GUI::on_radioButtonSmoothing_clicked() {
    ui->radioButtonSmoothing->setChecked(true);
    ui->radioButtonSelectionPseudorange->setChecked(false);
    ui->radioButtonSelectionPseudorangeCarrierPhase->setChecked(false);
    ui->radioButtonSelectionGraphic->setChecked(false);
    ui->groupBoxSmoothing->setHidden(false);

    if ( (ui->labelCurrentTemplate->text() == "SBAS 1F" || ui->labelCurrentTemplate->text() == "SBAS DFMC" || ui->groupBoxSbas->isChecked()==true)) {
        ui->stackedWidgetSmoothing->setCurrentIndex(1);
    } else if ( (ui->labelCurrentTemplate->text() == "DGNSS" || ui->groupBoxReferenceStation->isChecked()==true)) {
        ui->stackedWidgetSmoothing->setCurrentIndex(2);
    } else {
        ui->stackedWidgetSmoothing->setCurrentIndex(0);
    }
    if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
        this->initGNSSMeasAll();
    } else {
        //In SBAS or DGNSS, show the smoothing option but without unblocking or resetting measurements
        for (int isys=0; isys<MAX_GNSS; isys++){
            for (int icomb=0; icomb<3; icomb++) {
                FrameGNSSMeasFreq[isys][icomb][1]->setHidden(true);
                FrameGNSSSmoothWith[isys][icomb]->setHidden(false);
                ComboBoxSmoothWithTypeAll[isys][icomb]->currentIndexChanged(0);
            }
        }
    }

    ui->framePhaseAmbiguitiesParameters->setHidden(true);

    //Code to set correct status of "+" and "-" buttons according to each constellation
    int isys=ui->stackedWidgetMeasurementGNSS->currentIndex();
    if (FrameGNSSMeasComb[isys][1]->isHidden()==true) {
        ui->pushButtonMeasGNSSAdd->setEnabled(true);
        ui->pushButtonMeasGNSSDelete->setEnabled(false);
    } else if (FrameGNSSMeasComb[isys][2]->isHidden()==false) {
        ui->pushButtonMeasGNSSAdd->setEnabled(false);
        ui->pushButtonMeasGNSSDelete->setEnabled(true);
    } else {
        ui->pushButtonMeasGNSSAdd->setEnabled(true);
        ui->pushButtonMeasGNSSDelete->setEnabled(true);
    }
}

// Function to set pseudorange only measurements
void gLAB_GUI::on_radioButtonSelectionPseudorange_clicked() {
    ui->radioButtonSelectionPseudorange->setChecked(true);
    ui->radioButtonSmoothing->setChecked(false);
    ui->radioButtonSelectionPseudorangeCarrierPhase->setChecked(false);
    ui->radioButtonSelectionGraphic->setChecked(false);
    ui->groupBoxSmoothing->setHidden(true);

    if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
        this->initGNSSMeasAll();
    } else {
        //In SBAS or DGNSS, hide the smoothing option but without unblocking or resetting measurements
        for (int isys=0; isys<MAX_GNSS; isys++){
            for (int icomb=0; icomb<3; icomb++) {
                FrameGNSSMeasFreq[isys][icomb][1]->setHidden(true);
                FrameGNSSSmoothWith[isys][icomb]->setHidden(true);
            }
        }
    }

    ui->framePhaseAmbiguitiesParameters->setHidden(true);

    //Code to set correct status of "+" and "-" buttons according to each constellation
    int isys=ui->stackedWidgetMeasurementGNSS->currentIndex();
    if (FrameGNSSMeasComb[isys][1]->isHidden()==true) {
        ui->pushButtonMeasGNSSAdd->setEnabled(true);
        ui->pushButtonMeasGNSSDelete->setEnabled(false);
    } else if (FrameGNSSMeasComb[isys][2]->isHidden()==false) {
        ui->pushButtonMeasGNSSAdd->setEnabled(false);
        ui->pushButtonMeasGNSSDelete->setEnabled(true);
    } else {
        ui->pushButtonMeasGNSSAdd->setEnabled(true);
        ui->pushButtonMeasGNSSDelete->setEnabled(true);
    }
}

// Function to set pseudoranges and carrier phase measurements
void gLAB_GUI::on_radioButtonSelectionPseudorangeCarrierPhase_clicked() {
    ui->radioButtonSelectionPseudorangeCarrierPhase->setChecked(true);
    ui->radioButtonSelectionPseudorange->setChecked(false);
    ui->radioButtonSmoothing->setChecked(false);
    ui->radioButtonSelectionGraphic->setChecked(false);
    ui->groupBoxSmoothing->setHidden(true);

    this->initGNSSMeasAll();

    ui->framePhaseAmbiguitiesParameters->setHidden(false);

    //Code to set correct status of "+" and "-" buttons according to each constellation
    int isys=ui->stackedWidgetMeasurementGNSS->currentIndex();
    if (FrameGNSSMeasComb[isys][1]->isHidden()==true) {
        ui->pushButtonMeasGNSSAdd->setEnabled(true);
        ui->pushButtonMeasGNSSDelete->setEnabled(false);
    } else if (FrameGNSSMeasComb[isys][2]->isHidden()==false) {
        ui->pushButtonMeasGNSSAdd->setEnabled(false);
        ui->pushButtonMeasGNSSDelete->setEnabled(true);
    } else {
        ui->pushButtonMeasGNSSAdd->setEnabled(true);
        ui->pushButtonMeasGNSSDelete->setEnabled(true);
    }
}

// Function to set Graphical combination only measurements
void gLAB_GUI::on_radioButtonSelectionGraphic_clicked() {
    ui->radioButtonSelectionPseudorange->setChecked(false);
    ui->radioButtonSmoothing->setChecked(false);
    ui->radioButtonSelectionPseudorangeCarrierPhase->setChecked(false);
    ui->radioButtonSelectionGraphic->setChecked(true);
    ui->groupBoxSmoothing->setHidden(true);

    if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
        this->initGNSSMeasAll();
    } else {
        //In SBAS or DGNSS, hide the smoothing option but without unblocking or resetting measurements
        for (int isys=0; isys<MAX_GNSS; isys++){
            for (int icomb=0; icomb<3; icomb++) {
                FrameGNSSMeasFreq[isys][icomb][1]->setHidden(true);
                FrameGNSSSmoothWith[isys][icomb]->setHidden(true);
            }
        }
    }

    ui->framePhaseAmbiguitiesParameters->setHidden(false);

    //Code to set correct status of "+" and "-" buttons according to each constellation
    int isys=ui->stackedWidgetMeasurementGNSS->currentIndex();
    if (FrameGNSSMeasComb[isys][1]->isHidden()==true) {
        ui->pushButtonMeasGNSSAdd->setEnabled(true);
        ui->pushButtonMeasGNSSDelete->setEnabled(false);
    } else if (FrameGNSSMeasComb[isys][2]->isHidden()==false) {
        ui->pushButtonMeasGNSSAdd->setEnabled(false);
        ui->pushButtonMeasGNSSDelete->setEnabled(true);
    } else {
        ui->pushButtonMeasGNSSAdd->setEnabled(true);
        ui->pushButtonMeasGNSSDelete->setEnabled(true);
    }
}


// Function to show or hide the smoothmin
void gLAB_GUI::on_checkBoxExcludeDuringSmoothingConvergenceUser_clicked(bool checked) {
    ui->checkBoxExcludeDuringSmoothingConvergenceUser->setChecked(checked);
    if ( ui->checkBoxExcludeDuringSmoothingConvergenceRef->isChecked() == true || ui->checkBoxExcludeDuringSmoothingConvergenceUser->isChecked() == true )
        ui->frameExcludeDuringSmoothingDgnss->setHidden(false);
    else
        ui->frameExcludeDuringSmoothingDgnss->setHidden(true);
}

// Function to show or hide the smoothmin
void gLAB_GUI::on_checkBoxExcludeDuringSmoothingConvergenceRef_clicked(bool checked) {
    ui->checkBoxExcludeDuringSmoothingConvergenceRef->setChecked(checked);
    if ( ui->checkBoxExcludeDuringSmoothingConvergenceRef->isChecked() == true || ui->checkBoxExcludeDuringSmoothingConvergenceUser->isChecked() == true )
        ui->frameExcludeDuringSmoothingDgnss->setHidden(false);
    else
        ui->frameExcludeDuringSmoothingDgnss->setHidden(true);
}

// Function to set the correct stacked widget in Measurement Configuration and Noise
void gLAB_GUI::on_radioButtonSingleFreq_clicked() {
    ui->radioButtonSingleFreq->setChecked(true);
    ui->radioButtonSelectionGraphic->setHidden(false);

    this->initGNSSMeasAll();


    if (ui->groupBoxSbas->isChecked()==false) {
        for (int i=0; i<MAX_GNSS; i++){
            if (CheckBoxGNSS[i]->isChecked()){
                (this->*PushButtonGNSSMeasurementFunctions[i])();
                break;
            }
        }
    }

    //Set P1-P2 DCB if non set
    if (ui->labelCurrentTemplate->text()=="PPP") ui->comboBoxDCBsfSP3BDS->setCurrentIndex(1);
}

// Function to set the correct stacked widget in Measurement Configuration and Noise
void gLAB_GUI::on_radioButtonDualFreq_clicked() {
    ui->radioButtonDualFreq->setChecked(true);
    if (ui->radioButtonSelectionGraphic->isChecked()==true) {
        //If Graphic combination, select pseudorange as dual frequency does not have graphic combination
        this->on_radioButtonSelectionPseudorange_clicked();
    }
    ui->radioButtonSelectionGraphic->setHidden(true);

    this->initGNSSMeasAll();


    for (int i=0; i<MAX_GNSS; i++){
        if (CheckBoxGNSS[i]->isChecked()){
            (this->*PushButtonGNSSMeasurementFunctions[i])();
            break;
        }
    }
}

void gLAB_GUI::on_pushButtonMeasGNSSAdd_clicked(){
    if ( ui->labelCurrentTemplate->text()!="SPP" && ui->labelCurrentTemplate->text()!="PPP" ) return;
    int isys=ui->stackedWidgetMeasurementGNSS->currentIndex();
    if (FrameGNSSMeasComb[isys][1]->isHidden()==true) {
        FrameGNSSMeasComb[isys][1]->setHidden(false);
        ui->pushButtonMeasGNSSDelete->setEnabled(true);
    } else if (FrameGNSSMeasComb[isys][2]->isHidden()==true) {
        FrameGNSSMeasComb[isys][2]->setHidden(false);
        ui->pushButtonMeasGNSSAdd->setEnabled(false);
    }
    return ;
}
void gLAB_GUI::on_pushButtonMeasGNSSDelete_clicked(){
    if ( ui->labelCurrentTemplate->text()!="SPP" && ui->labelCurrentTemplate->text()!="PPP" ) return;
    int isys=ui->stackedWidgetMeasurementGNSS->currentIndex();
    if (FrameGNSSMeasComb[isys][2]->isHidden()==false) {
        FrameGNSSMeasComb[isys][2]->setHidden(true);
        ui->pushButtonMeasGNSSAdd->setEnabled(true);
    } else if (FrameGNSSMeasComb[isys][1]->isHidden()==false) {
        FrameGNSSMeasComb[isys][1]->setHidden(true);
        ui->pushButtonMeasGNSSDelete->setEnabled(false);
    }
    return ;
}
//Function to configure GPS measurements
void gLAB_GUI::on_pushButtonGPSMeasurements_clicked(){
    ui->stackedWidgetMeasurementGNSS->setCurrentIndex(GPS);
    ui->labelMeasurementsGNSS->setText("GPS:");
    ui->pushButtonGPSMeasurements->setChecked(true);
    ui->pushButtonGalileoMeasurements->setChecked(false);
    ui->pushButtonGLONASSMeasurements->setChecked(false);
    ui->pushButtonGEOMeasurements->setChecked(false);
    ui->pushButtonBDSMeasurements->setChecked(false);
    ui->pushButtonQZSSMeasurements->setChecked(false);
    ui->pushButtonIRNSSMeasurements->setChecked(false);

    if (FrameGNSSMeasComb[GPS][2]->isHidden()==true) {
        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
            //Only enable button if we are not in SBAS or DGNSS modes
            ui->pushButtonMeasGNSSAdd->setEnabled(true);
        }
    } else {
        ui->pushButtonMeasGNSSAdd->setEnabled(false);
    }
    if (FrameGNSSMeasComb[GPS][1]->isHidden()==false) {
        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
            //Only enable button if we are not in SBAS or DGNSS modes
            ui->pushButtonMeasGNSSDelete->setEnabled(true);
        }
    } else {
        ui->pushButtonMeasGNSSDelete->setEnabled(false);
    }
}
//Function to configure Galileo measurements
void gLAB_GUI::on_pushButtonGalileoMeasurements_clicked(){
    ui->stackedWidgetMeasurementGNSS->setCurrentIndex(Galileo);
    ui->labelMeasurementsGNSS->setText("Galileo:");
    ui->pushButtonGPSMeasurements->setChecked(false);
    ui->pushButtonGalileoMeasurements->setChecked(true);
    ui->pushButtonGLONASSMeasurements->setChecked(false);
    ui->pushButtonGEOMeasurements->setChecked(false);
    ui->pushButtonBDSMeasurements->setChecked(false);
    ui->pushButtonQZSSMeasurements->setChecked(false);
    ui->pushButtonIRNSSMeasurements->setChecked(false);

    if (FrameGNSSMeasComb[Galileo][2]->isHidden()==true) {
        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
            //Only enable button if we are not in SBAS or DGNSS modes
            ui->pushButtonMeasGNSSAdd->setEnabled(true);
        }
    } else {
        ui->pushButtonMeasGNSSAdd->setEnabled(false);
    }
    if (FrameGNSSMeasComb[Galileo][1]->isHidden()==false) {
        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
            //Only enable button if we are not in SBAS or DGNSS modes
            ui->pushButtonMeasGNSSDelete->setEnabled(true);
        }
    } else {
        ui->pushButtonMeasGNSSDelete->setEnabled(false);
    }
}
//Function to configure GLONASS measurements
void gLAB_GUI::on_pushButtonGLONASSMeasurements_clicked(){
    ui->stackedWidgetMeasurementGNSS->setCurrentIndex(GLONASS);
    ui->labelMeasurementsGNSS->setText("GLONASS:");
    ui->pushButtonGPSMeasurements->setChecked(false);
    ui->pushButtonGalileoMeasurements->setChecked(false);
    ui->pushButtonGLONASSMeasurements->setChecked(true);
    ui->pushButtonGEOMeasurements->setChecked(false);
    ui->pushButtonBDSMeasurements->setChecked(false);
    ui->pushButtonQZSSMeasurements->setChecked(false);
    ui->pushButtonIRNSSMeasurements->setChecked(false);

    if (FrameGNSSMeasComb[GLONASS][2]->isHidden()==true) {
        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
            //Only enable button if we are not in SBAS or DGNSS modes
            ui->pushButtonMeasGNSSAdd->setEnabled(true);
        }
    } else {
        ui->pushButtonMeasGNSSAdd->setEnabled(false);
    }
    if (FrameGNSSMeasComb[GLONASS][1]->isHidden()==false) {
        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
            //Only enable button if we are not in SBAS or DGNSS modes
            ui->pushButtonMeasGNSSDelete->setEnabled(true);
        }
    } else {
        ui->pushButtonMeasGNSSDelete->setEnabled(false);
    }
}
//Function to configure GEO measurements
void gLAB_GUI::on_pushButtonGEOMeasurements_clicked(){
    ui->stackedWidgetMeasurementGNSS->setCurrentIndex(GEO);
    ui->labelMeasurementsGNSS->setText("GEO:");
    ui->pushButtonGPSMeasurements->setChecked(false);
    ui->pushButtonGalileoMeasurements->setChecked(false);
    ui->pushButtonGLONASSMeasurements->setChecked(false);
    ui->pushButtonGEOMeasurements->setChecked(true);
    ui->pushButtonBDSMeasurements->setChecked(false);
    ui->pushButtonQZSSMeasurements->setChecked(false);
    ui->pushButtonIRNSSMeasurements->setChecked(false);

    if (FrameGNSSMeasComb[GEO][2]->isHidden()==true) {
        ui->pushButtonMeasGNSSAdd->setEnabled(true);
    } else {
        ui->pushButtonMeasGNSSAdd->setEnabled(false);
    }
    if (FrameGNSSMeasComb[GEO][1]->isHidden()==false) {
        ui->pushButtonMeasGNSSDelete->setEnabled(true);
    } else {
        ui->pushButtonMeasGNSSDelete->setEnabled(false);
    }
}
//Function to configure BDS measurements
void gLAB_GUI::on_pushButtonBDSMeasurements_clicked(){
    ui->stackedWidgetMeasurementGNSS->setCurrentIndex(BDS);
    ui->labelMeasurementsGNSS->setText("BDS:");
    ui->pushButtonGPSMeasurements->setChecked(false);
    ui->pushButtonGalileoMeasurements->setChecked(false);
    ui->pushButtonGLONASSMeasurements->setChecked(false);
    ui->pushButtonGEOMeasurements->setChecked(false);
    ui->pushButtonBDSMeasurements->setChecked(true);
    ui->pushButtonQZSSMeasurements->setChecked(false);
    ui->pushButtonIRNSSMeasurements->setChecked(false);

    if (FrameGNSSMeasComb[BDS][2]->isHidden()==true) {
        ui->pushButtonMeasGNSSAdd->setEnabled(true);
    } else {
        ui->pushButtonMeasGNSSAdd->setEnabled(false);
    }
    if (FrameGNSSMeasComb[BDS][1]->isHidden()==false) {
        ui->pushButtonMeasGNSSDelete->setEnabled(true);
    } else {
        ui->pushButtonMeasGNSSDelete->setEnabled(false);
    }
}
//Function to configure QZSS measurements
void gLAB_GUI::on_pushButtonQZSSMeasurements_clicked(){
    ui->stackedWidgetMeasurementGNSS->setCurrentIndex(QZSS);
    ui->labelMeasurementsGNSS->setText("QZSS:");
    ui->pushButtonGPSMeasurements->setChecked(false);
    ui->pushButtonGalileoMeasurements->setChecked(false);
    ui->pushButtonGLONASSMeasurements->setChecked(false);
    ui->pushButtonGEOMeasurements->setChecked(false);
    ui->pushButtonBDSMeasurements->setChecked(false);
    ui->pushButtonQZSSMeasurements->setChecked(true);
    ui->pushButtonIRNSSMeasurements->setChecked(false);

    if (FrameGNSSMeasComb[QZSS][2]->isHidden()==true) {
        ui->pushButtonMeasGNSSAdd->setEnabled(true);
    } else {
        ui->pushButtonMeasGNSSAdd->setEnabled(false);
    }
    if (FrameGNSSMeasComb[QZSS][1]->isHidden()==false) {
        ui->pushButtonMeasGNSSDelete->setEnabled(true);
    } else {
        ui->pushButtonMeasGNSSDelete->setEnabled(false);
    }
}
//Function to configure IRNSS measurements
void gLAB_GUI::on_pushButtonIRNSSMeasurements_clicked(){
    ui->stackedWidgetMeasurementGNSS->setCurrentIndex(IRNSS);
    ui->labelMeasurementsGNSS->setText("IRNSS:");
    ui->pushButtonGPSMeasurements->setChecked(false);
    ui->pushButtonGalileoMeasurements->setChecked(false);
    ui->pushButtonGLONASSMeasurements->setChecked(false);
    ui->pushButtonGEOMeasurements->setChecked(false);
    ui->pushButtonBDSMeasurements->setChecked(false);
    ui->pushButtonQZSSMeasurements->setChecked(false);
    ui->pushButtonIRNSSMeasurements->setChecked(true);

    if (FrameGNSSMeasComb[IRNSS][2]->isHidden()==true) {
        ui->pushButtonMeasGNSSAdd->setEnabled(true);
    } else {
        ui->pushButtonMeasGNSSAdd->setEnabled(false);
    }
    if (FrameGNSSMeasComb[IRNSS][1]->isHidden()==false) {
        ui->pushButtonMeasGNSSDelete->setEnabled(true);
    } else {
        ui->pushButtonMeasGNSSDelete->setEnabled(false);
    }
}

// Function to enable the configuration of GNSS frequencies/measurements priority
void gLAB_GUI::on_checkBoxSetFreqMeasOrderGNSS_clicked(bool checked){
    ui->checkBoxSetFreqMeasOrderGNSS->setChecked(checked);
    if (checked) {
        ui->pushButtonSetFreqMeasOrderGNSS->setEnabled(true);
    }
    else {
        ui->pushButtonSetFreqMeasOrderGNSS->setEnabled(false);
    }
}
void gLAB_GUI::on_pushButtonSetFreqMeasOrderGNSS_clicked(){
    FreqMeasGNSS->setModal(true);
    FreqMeasGNSS->show();
}

//Function to initialize GNSS Measurement for all constellations
void gLAB_GUI::initGNSSMeasAll() {
    for (int isys=0; isys<MAX_GNSS; isys++){
        for (int icomb=0; icomb<3; icomb++) {
            ComboBoxGNSSFreq[isys][icomb][CODEARRAYPOS]->setEnabled(true);
            ComboBoxGNSSFreq[isys][icomb][PHASEARRAYPOS]->setEnabled(true);
            ComboBoxGNSSFreq[isys][icomb][GCARRAYPOS]->setEnabled(true);
            ComboBoxGNSSMeas[isys][icomb][CODEARRAYPOS][COMBMEAS1ARRAYPOS]->setEnabled(true);
            if (ui->radioButtonDualFreq->isChecked()) {
                ComboBoxGNSSMeas[isys][icomb][CODEARRAYPOS][COMBMEAS2ARRAYPOS]->setEnabled(true);
                ComboBoxGNSSMeas[isys][icomb][CODEARRAYPOS][COMBMEAS2ARRAYPOS]->setHidden(false);
            }
            else if (ui->radioButtonSingleFreq->isChecked()) {
                if (ui->radioButtonSelectionGraphic->isChecked()) {
                    ComboBoxGNSSMeas[isys][icomb][GCARRAYPOS][COMBMEAS1ARRAYPOS]->setEnabled(true);
                } else {
                    ComboBoxGNSSMeas[isys][icomb][CODEARRAYPOS][COMBMEAS2ARRAYPOS]->setEnabled(false);
                    ComboBoxGNSSMeas[isys][icomb][CODEARRAYPOS][COMBMEAS2ARRAYPOS]->setHidden(true);
                }
            }
            ComboBoxGNSSMeas[isys][icomb][PHASEARRAYPOS][COMBMEAS1ARRAYPOS]->setEnabled(true);
            if (ui->radioButtonDualFreq->isChecked()) {
                ComboBoxGNSSMeas[isys][icomb][PHASEARRAYPOS][COMBMEAS2ARRAYPOS]->setEnabled(true);
                ComboBoxGNSSMeas[isys][icomb][PHASEARRAYPOS][COMBMEAS2ARRAYPOS]->setHidden(false);
            } else if (ui->radioButtonSingleFreq->isChecked()) {
                ComboBoxGNSSMeas[isys][icomb][PHASEARRAYPOS][COMBMEAS2ARRAYPOS]->setEnabled(false);
                ComboBoxGNSSMeas[isys][icomb][PHASEARRAYPOS][COMBMEAS2ARRAYPOS]->setHidden(true);
            }
            FrameGNSSSmoothWith[isys][icomb]->setEnabled(true);
            this->setGNSSMeasurementFreqAll(isys,icomb,0);
            ComboBoxstdDevType[isys][icomb][CODEARRAYPOS]->currentIndexChanged(0);
            ComboBoxstdDevType[isys][icomb][PHASEARRAYPOS]->currentIndexChanged(0);
            ComboBoxstdDevType[isys][icomb][GCARRAYPOS]->currentIndexChanged(0);
            if (ui->radioButtonSelectionGraphic->isChecked()) {
                FrameGNSSMeasFreq[isys][icomb][CODEARRAYPOS]->setHidden(true);
                FrameGNSSMeasFreq[isys][icomb][GCARRAYPOS]->setHidden(false);
            } else {
                FrameGNSSMeasFreq[isys][icomb][CODEARRAYPOS]->setHidden(false);
                FrameGNSSMeasFreq[isys][icomb][GCARRAYPOS]->setHidden(true);
            }
            if (ui->radioButtonSmoothing->isChecked()) {
                FrameGNSSMeasFreq[isys][icomb][PHASEARRAYPOS]->setHidden(true);
                FrameGNSSSmoothWith[isys][icomb]->setHidden(false);
                ComboBoxstdDevType[isys][icomb][CODEARRAYPOS]->setEnabled(true);
                LineEditstdDevValue[isys][icomb][CODEARRAYPOS][COMBMEAS1ARRAYPOS]->setEnabled(true);
                ComboBoxSmoothWithTypeAll[isys][icomb]->currentIndexChanged(0);
            } else {
                if (ui->radioButtonSelectionPseudorangeCarrierPhase->isChecked()) FrameGNSSMeasFreq[isys][icomb][PHASEARRAYPOS]->setHidden(false);
                else FrameGNSSMeasFreq[isys][icomb][PHASEARRAYPOS]->setHidden(true);
                FrameGNSSSmoothWith[isys][icomb]->setHidden(true);
                ComboBoxstdDevType[isys][icomb][CODEARRAYPOS]->setEnabled(false);
                LineEditstdDevValue[isys][icomb][CODEARRAYPOS][CONSTWEIGHTARRAYPOS]->setEnabled(false);
                ComboBoxstdDevType[isys][icomb][PHASEARRAYPOS]->setEnabled(false);
                LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][CONSTWEIGHTARRAYPOS]->setEnabled(false);
            }
        }
        FrameGNSSMeasComb[isys][SECONDMEASARRAYPOS]->setHidden(true);
        FrameGNSSMeasComb[isys][THIRDMEASARRAYPOS]->setHidden(true);
    }
}

//Function to set frequency for GNSS Measurement
void gLAB_GUI::setGNSSMeasurementFreqAll(int iGNSS,int icomb,int ifreq){
    //single frequency
    if (ui->radioButtonSingleFreq->isChecked()) {
        if (ui->radioButtonSelectionGraphic->isChecked()) {
            //freq
            for (int i=ComboBoxGNSSFreq[iGNSS][icomb][GCARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSFreq[iGNSS][icomb][GCARRAYPOS]->removeItem(i);
            ComboBoxGNSSFreq[iGNSS][icomb][GCARRAYPOS]->addItem("Auto");
            for (int i=0; i<FreqNameGNSSList[iGNSS].size(); i++) ComboBoxGNSSFreq[iGNSS][icomb][GCARRAYPOS]->addItem(FreqNameGNSSList[iGNSS][i]);
            //meas
            for (int i=ComboBoxGNSSMeas[iGNSS][icomb][GCARRAYPOS][COMBMEAS1ARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][GCARRAYPOS][COMBMEAS1ARRAYPOS]->removeItem(i);
            for (int i=ComboBoxGNSSMeas[iGNSS][icomb][GCARRAYPOS][COMBMEAS2ARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][GCARRAYPOS][COMBMEAS2ARRAYPOS]->removeItem(i);
            ComboBoxGNSSMeas[iGNSS][icomb][GCARRAYPOS][COMBMEAS1ARRAYPOS]->addItem("Auto");
            ComboBoxGNSSMeas[iGNSS][icomb][GCARRAYPOS][COMBMEAS2ARRAYPOS]->addItem("Auto");
            ComboBoxGNSSFreq[iGNSS][icomb][GCARRAYPOS]->currentIndexChanged(0);
            ComboBoxGNSSMeas[iGNSS][icomb][GCARRAYPOS][COMBMEAS1ARRAYPOS]->currentIndexChanged(0);
            ComboBoxGNSSMeas[iGNSS][icomb][GCARRAYPOS][COMBMEAS2ARRAYPOS]->currentIndexChanged(0);
        } else {
            //freq
            //code
            for (int i=ComboBoxGNSSFreq[iGNSS][icomb][CODEARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSFreq[iGNSS][icomb][CODEARRAYPOS]->removeItem(i);
            if (!ui->radioButtonSmoothing->isChecked()) ComboBoxGNSSFreq[iGNSS][icomb][CODEARRAYPOS]->addItem("Auto"); //no smoothing
            for (int i=0; i<FreqNameGNSSList[iGNSS].size(); i++) ComboBoxGNSSFreq[iGNSS][icomb][CODEARRAYPOS]->addItem(FreqNameGNSSList[iGNSS][i]);
            //phase
            for (int i=ComboBoxGNSSFreq[iGNSS][icomb][PHASEARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSFreq[iGNSS][icomb][PHASEARRAYPOS]->removeItem(i);
            ComboBoxGNSSFreq[iGNSS][icomb][PHASEARRAYPOS]->addItem("Auto");
            for (int i=0; i<FreqNameGNSSList[iGNSS].size(); i++) ComboBoxGNSSFreq[iGNSS][icomb][PHASEARRAYPOS]->addItem(FreqNameGNSSList[iGNSS][i]);
            //meas
            for (int i=ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS1ARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS1ARRAYPOS]->removeItem(i);
            for (int i=ComboBoxGNSSMeas[iGNSS][icomb][PHASEARRAYPOS][COMBMEAS1ARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][PHASEARRAYPOS][COMBMEAS1ARRAYPOS]->removeItem(i);
            ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS1ARRAYPOS]->addItem("Auto");
            ComboBoxGNSSMeas[iGNSS][icomb][PHASEARRAYPOS][COMBMEAS1ARRAYPOS]->addItem("Auto");
            //smooth
            if ( ui->radioButtonSmoothing->isChecked() && ifreq>=0 && ifreq<nFreqGNSS[iGNSS] ) {
                ComboBoxGNSSFreq[iGNSS][icomb][CODEARRAYPOS]->currentIndexChanged(ifreq);
                for (int i=0; i<MeasCodeGNSSOrder[iGNSS][ifreq].size(); i++) ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS1ARRAYPOS]->addItem("C"+FreqGNSSList[iGNSS][ifreq]+MeasCodeGNSSOrder[iGNSS][ifreq][i]);
            }
            else {
                ComboBoxGNSSFreq[iGNSS][icomb][CODEARRAYPOS]->currentIndexChanged(0);
                ComboBoxGNSSFreq[iGNSS][icomb][PHASEARRAYPOS]->currentIndexChanged(0);
            }
            ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS1ARRAYPOS]->currentIndexChanged(0);
            ComboBoxGNSSMeas[iGNSS][icomb][PHASEARRAYPOS][COMBMEAS1ARRAYPOS]->currentIndexChanged(0);
        }
    }
    //dual frequency
    else if (ui->radioButtonDualFreq->isChecked()) {
        //freq
        //code
        for (int i=ComboBoxGNSSFreq[iGNSS][icomb][CODEARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSFreq[iGNSS][icomb][CODEARRAYPOS]->removeItem(i);
        if (!ui->radioButtonSmoothing->isChecked()) ComboBoxGNSSFreq[iGNSS][icomb][CODEARRAYPOS]->addItem("Auto"); //no smoothing
        for (int i=0; i<FreqCodeDualGNSSList[iGNSS].size(); i++) ComboBoxGNSSFreq[iGNSS][icomb][CODEARRAYPOS]->addItem(FreqCodeDualGNSSList[iGNSS][i]);
        //phase
        for (int i=ComboBoxGNSSFreq[iGNSS][icomb][PHASEARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSFreq[iGNSS][icomb][PHASEARRAYPOS]->removeItem(i);
        ComboBoxGNSSFreq[iGNSS][icomb][PHASEARRAYPOS]->addItem("Auto");
        for (int i=0; i<FreqPhaseDualGNSSList[iGNSS].size(); i++) ComboBoxGNSSFreq[iGNSS][icomb][PHASEARRAYPOS]->addItem(FreqPhaseDualGNSSList[iGNSS][i]);
        //meas
        for (int i=ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS1ARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS1ARRAYPOS]->removeItem(i);
        for (int i=ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS2ARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS2ARRAYPOS]->removeItem(i);
        for (int i=ComboBoxGNSSMeas[iGNSS][icomb][PHASEARRAYPOS][COMBMEAS1ARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][PHASEARRAYPOS][COMBMEAS1ARRAYPOS]->removeItem(i);
        for (int i=ComboBoxGNSSMeas[iGNSS][icomb][PHASEARRAYPOS][COMBMEAS2ARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][PHASEARRAYPOS][COMBMEAS2ARRAYPOS]->removeItem(i);
        ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS1ARRAYPOS]->addItem("Auto");
        ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS2ARRAYPOS]->addItem("Auto");
        ComboBoxGNSSMeas[iGNSS][icomb][PHASEARRAYPOS][COMBMEAS1ARRAYPOS]->addItem("Auto");
        ComboBoxGNSSMeas[iGNSS][icomb][PHASEARRAYPOS][COMBMEAS2ARRAYPOS]->addItem("Auto");
        //smooth
        if ( ui->radioButtonSmoothing->isChecked() && ifreq>=0 && ifreq<nDualFreqGNSS[iGNSS] ) {
            ComboBoxGNSSFreq[iGNSS][icomb][CODEARRAYPOS]->currentIndexChanged(ifreq);
            int freq1=iFreqDualGNSS[iGNSS][ifreq][COMBMEAS1ARRAYPOS],freq2=iFreqDualGNSS[iGNSS][ifreq][1];
            for (int i=0; i<MeasCodeGNSSOrder[iGNSS][freq1].size(); i++) ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS1ARRAYPOS]->addItem("C"+FreqGNSSList[iGNSS][freq1]+MeasCodeGNSSOrder[iGNSS][freq1][i]);
            for (int i=0; i<MeasCodeGNSSOrder[iGNSS][freq2].size(); i++) ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS2ARRAYPOS]->addItem("C"+FreqGNSSList[iGNSS][freq2]+MeasCodeGNSSOrder[iGNSS][freq2][i]);
            if (iGNSS==BDS) {
                ComboBoxGNSSFreq[iGNSS][icomb][CODEARRAYPOS]->currentIndexChanged(6); //BDS default combination is 26
                ComboBoxGNSSFreq[iGNSS][icomb][PHASEARRAYPOS]->currentIndexChanged(6); //BDS default combination is 26
            }
        }
        else {
            ComboBoxGNSSFreq[iGNSS][icomb][CODEARRAYPOS]->currentIndexChanged(0);
            ComboBoxGNSSFreq[iGNSS][icomb][PHASEARRAYPOS]->currentIndexChanged(0);
        }
        ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS1ARRAYPOS]->currentIndexChanged(0);
        ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS2ARRAYPOS]->currentIndexChanged(0);
        ComboBoxGNSSMeas[iGNSS][icomb][PHASEARRAYPOS][COMBMEAS1ARRAYPOS]->currentIndexChanged(0);
        ComboBoxGNSSMeas[iGNSS][icomb][PHASEARRAYPOS][COMBMEAS2ARRAYPOS]->currentIndexChanged(0);
    }
    this->InitFilterWeights();
}
//Function to set frequency for GNSS code or phase Measurement
void gLAB_GUI::setGNSSMeasurementFreqCP(int iGNSS,int icomb,int iCP,int ifreq){
    if ( iCP<CODEARRAYPOS || iCP>GCARRAYPOS ) return;
    //single frequency
    if (ui->radioButtonSingleFreq->isChecked()) {
        if (ui->radioButtonSelectionGraphic->isChecked()) {
            if (iCP<GCARRAYPOS ) return;
            //freq
            for (int i=ComboBoxGNSSFreq[iGNSS][icomb][iCP]->count()-1; i>=0; i--) ComboBoxGNSSFreq[iGNSS][icomb][iCP]->removeItem(i);
            ComboBoxGNSSFreq[iGNSS][icomb][iCP]->addItem("Auto");
            for (int i=0; i<FreqNameGNSSList[iGNSS].size(); i++) ComboBoxGNSSFreq[iGNSS][icomb][iCP]->addItem(FreqNameGNSSList[iGNSS][i]);
            //meas
            for (int i=ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->removeItem(i);
            for (int i=ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS2ARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS2ARRAYPOS]->removeItem(i);
            ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->addItem("Auto");
            ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS2ARRAYPOS]->addItem("Auto");
            ComboBoxGNSSFreq[iGNSS][icomb][iCP]->currentIndexChanged(0);
            ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->currentIndexChanged(0);
        } else {
            //code or phase
            if (iCP>PHASEARRAYPOS ) return;
            //freq
            for (int i=ComboBoxGNSSFreq[iGNSS][icomb][iCP]->count()-1; i>=0; i--) ComboBoxGNSSFreq[iGNSS][icomb][iCP]->removeItem(i);
            if (!ui->radioButtonSmoothing->isChecked()) ComboBoxGNSSFreq[iGNSS][icomb][iCP]->addItem("Auto"); //no smoothing
            for (int i=0; i<FreqNameGNSSList[iGNSS].size(); i++) ComboBoxGNSSFreq[iGNSS][icomb][iCP]->addItem(FreqNameGNSSList[iGNSS][i]);
            //meas
            for (int i=ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->removeItem(i);
            ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->addItem("Auto");
            //smooth
            if (  iCP==0 && ui->radioButtonSmoothing->isChecked() && ifreq>=0 && ifreq<nFreqGNSS[iGNSS]) {
                ComboBoxGNSSFreq[iGNSS][icomb][CODEARRAYPOS]->currentIndexChanged(ifreq);
                for (int i=0; i<MeasCodeGNSSOrder[iGNSS][ifreq].size(); i++) ComboBoxGNSSMeas[iGNSS][icomb][0][COMBMEAS1ARRAYPOS]->addItem("C"+FreqGNSSList[iGNSS][ifreq]+MeasCodeGNSSOrder[iGNSS][ifreq][i]);            
            } else {
                ComboBoxGNSSFreq[iGNSS][icomb][iCP]->currentIndexChanged(0);
            }
            ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->currentIndexChanged(0);
        }

    //dual frequency
    } else if (ui->radioButtonDualFreq->isChecked()) {
        if (iCP>PHASEARRAYPOS ) return;
        //freq
        //code or phase
        for (int i=ComboBoxGNSSFreq[iGNSS][icomb][iCP]->count()-1; i>=0; i--) ComboBoxGNSSFreq[iGNSS][icomb][iCP]->removeItem(i);
        if (!ui->radioButtonSmoothing->isChecked()) ComboBoxGNSSFreq[iGNSS][icomb][iCP]->addItem("Auto"); //no smoothing
        if (iCP==CODEARRAYPOS) for (int i=0; i<FreqCodeDualGNSSList[iGNSS].size(); i++) ComboBoxGNSSFreq[iGNSS][icomb][CODEARRAYPOS]->addItem(FreqCodeDualGNSSList[iGNSS][i]);
        else if (iCP==PHASEARRAYPOS) for (int i=0; i<FreqPhaseDualGNSSList[iGNSS].size(); i++) ComboBoxGNSSFreq[iGNSS][icomb][PHASEARRAYPOS]->addItem(FreqPhaseDualGNSSList[iGNSS][i]);
        //meas
        for (int i=ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->removeItem(i);
        for (int i=ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS2ARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS2ARRAYPOS]->removeItem(i);
        ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->addItem("Auto");
        ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS2ARRAYPOS]->addItem("Auto");
        //smooth
        if ( iCP==0 && ui->radioButtonSmoothing->isChecked() && ifreq>=0 && ifreq<nDualFreqGNSS[iGNSS] ) {
            ComboBoxGNSSFreq[iGNSS][icomb][CODEARRAYPOS]->currentIndexChanged(ifreq);
            int freq1=iFreqDualGNSS[iGNSS][ifreq][CODEARRAYPOS],freq2=iFreqDualGNSS[iGNSS][ifreq][1];
            for (int i=0; i<MeasCodeGNSSOrder[iGNSS][freq1].size(); i++) ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS1ARRAYPOS]->addItem("C"+FreqGNSSList[iGNSS][freq1]+MeasCodeGNSSOrder[iGNSS][freq1][i]);
            for (int i=0; i<MeasCodeGNSSOrder[iGNSS][freq2].size(); i++) ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS2ARRAYPOS]->addItem("C"+FreqGNSSList[iGNSS][freq2]+MeasCodeGNSSOrder[iGNSS][freq2][i]);        
        } else {
            ComboBoxGNSSFreq[iGNSS][icomb][iCP]->currentIndexChanged(0);
        }
        ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->currentIndexChanged(0);
        ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS2ARRAYPOS]->currentIndexChanged(0);
    }
}
//Function to set measurement of frequency for GNSS Measurement
void gLAB_GUI::setGNSSMeasurementMeasAll(int iGNSS,int icomb,int iCP,int ifreq){
    if ( iCP<CODEARRAYPOS || iCP>GCARRAYPOS ) return;
    //single frequency
    if (ui->radioButtonSingleFreq->isChecked()) {
        if (ui->radioButtonSelectionGraphic->isChecked()) {
            if (iCP<GCARRAYPOS) return;
            //meas
            for (int i=ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->removeItem(i);
            for (int i=ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS2ARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS2ARRAYPOS]->removeItem(i);
            ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->addItem("Auto");
            ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS2ARRAYPOS]->addItem("Auto");
            //item
            if ( ifreq>=0 && ifreq<nFreqGNSS[iGNSS] ) {
                for (int i=0; i<MeasCodeGNSSOrder[iGNSS][ifreq].size(); i++) ComboBoxGNSSMeas[iGNSS][icomb][GCARRAYPOS][COMBMEAS1ARRAYPOS]->addItem("C"+FreqGNSSList[iGNSS][ifreq]+MeasCodeGNSSOrder[iGNSS][ifreq][i]);

                for (int i=0; i<MeasGNSSOrder[iGNSS][ifreq].size(); i++) ComboBoxGNSSMeas[iGNSS][icomb][GCARRAYPOS][COMBMEAS2ARRAYPOS]->addItem("L"+FreqGNSSList[iGNSS][ifreq]+MeasGNSSOrder[iGNSS][ifreq][i]);

            }
            ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->currentIndexChanged(0);
        } else {
            if (iCP>PHASEARRAYPOS) return;
            //meas
            for (int i=ComboBoxGNSSMeas[iGNSS][icomb][iCP][0]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->removeItem(i);
            ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->addItem("Auto");
            //item
            if ( ifreq>=0 && ifreq<nFreqGNSS[iGNSS] ) {
                if (iCP==CODEARRAYPOS) {
                    for (int i=0; i<MeasCodeGNSSOrder[iGNSS][ifreq].size(); i++) ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS1ARRAYPOS]->addItem("C"+FreqGNSSList[iGNSS][ifreq]+MeasCodeGNSSOrder[iGNSS][ifreq][i]);
                } else {
                    for (int i=0; i<MeasGNSSOrder[iGNSS][ifreq].size(); i++) ComboBoxGNSSMeas[iGNSS][icomb][PHASEARRAYPOS][COMBMEAS1ARRAYPOS]->addItem("L"+FreqGNSSList[iGNSS][ifreq]+MeasGNSSOrder[iGNSS][ifreq][i]);
                }
            }
            ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->currentIndexChanged(0);
        }

    //dual frequency
    } else if (ui->radioButtonDualFreq->isChecked()) {
        if (iCP>PHASEARRAYPOS) return;
        for (int i=ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->removeItem(i);
        for (int i=ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS2ARRAYPOS]->count()-1; i>=0; i--) ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS2ARRAYPOS]->removeItem(i);
        ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->addItem("Auto");
        ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS2ARRAYPOS]->addItem("Auto");
        //item
        if ( ifreq>=0 && ifreq<nDualFreqGNSS[iGNSS] ) {
            int freq1=iFreqDualGNSS[iGNSS][ifreq][0],freq2=iFreqDualGNSS[iGNSS][ifreq][1];
            if (iCP==0){
                for (int i=0; i<MeasCodeGNSSOrder[iGNSS][freq1].size(); i++) ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS1ARRAYPOS]->addItem("C"+FreqGNSSList[iGNSS][freq1]+MeasCodeGNSSOrder[iGNSS][freq1][i]);
                for (int i=0; i<MeasCodeGNSSOrder[iGNSS][freq2].size(); i++) ComboBoxGNSSMeas[iGNSS][icomb][CODEARRAYPOS][COMBMEAS2ARRAYPOS]->addItem("C"+FreqGNSSList[iGNSS][freq2]+MeasCodeGNSSOrder[iGNSS][freq2][i]);

            } else {
                for (int i=0; i<MeasGNSSOrder[iGNSS][freq1].size(); i++) ComboBoxGNSSMeas[iGNSS][icomb][PHASEARRAYPOS][COMBMEAS1ARRAYPOS]->addItem("L"+FreqGNSSList[iGNSS][freq1]+MeasGNSSOrder[iGNSS][freq1][i]);
                for (int i=0; i<MeasGNSSOrder[iGNSS][freq2].size(); i++) ComboBoxGNSSMeas[iGNSS][icomb][PHASEARRAYPOS][COMBMEAS2ARRAYPOS]->addItem("L"+FreqGNSSList[iGNSS][freq2]+MeasGNSSOrder[iGNSS][freq2][i]);
            }
        }
        ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS1ARRAYPOS]->currentIndexChanged(0);
        ComboBoxGNSSMeas[iGNSS][icomb][iCP][COMBMEAS2ARRAYPOS]->currentIndexChanged(0);
    }
}
//Function to set values for the comboBoxes of smoothed-with freq
void gLAB_GUI::setSmoothWithFreqComboBoxValue(int iGNSS,int icomb,int ifreq1,int ifreq2){
    if ( ifreq1!=-1 && ifreq1==ifreq2 ) return;
    if ( ifreq1>=0 && ifreq1<nFreqGNSS[iGNSS] ) {
        //freq
        for (int i=ComboBoxSmoothWithFreqAll[iGNSS][icomb][0]->count()-1; i>=0; i--) ComboBoxSmoothWithFreqAll[iGNSS][icomb][0]->removeItem(i);
        for (int i=0; i<FreqNameGNSSList[iGNSS].size(); i++) ComboBoxSmoothWithFreqAll[iGNSS][icomb][0]->addItem(FreqNameGNSSList[iGNSS][i]);
        ComboBoxSmoothWithFreqAll[iGNSS][icomb][0]->currentIndexChanged(ifreq1);
        smoothWithFreqIndexAll[BDS][icomb][0]=ifreq1;
        //meas
        for (int i=ComboBoxSmoothWithMeasAll[iGNSS][icomb][0]->count()-1; i>=0; i--) ComboBoxSmoothWithMeasAll[iGNSS][icomb][0]->removeItem(i);
        for (int i=ComboBoxSmoothWithMeasAll[iGNSS][icomb][1]->count()-1; i>=0; i--) ComboBoxSmoothWithMeasAll[iGNSS][icomb][1]->removeItem(i);
        ComboBoxSmoothWithMeasAll[iGNSS][icomb][0]->addItem("Auto");
        for (int i=0; i<MeasCodeGNSSOrder[iGNSS][ifreq1].size(); i++) ComboBoxSmoothWithMeasAll[iGNSS][icomb][0]->addItem("C"+FreqGNSSList[iGNSS][ifreq1]+MeasCodeGNSSOrder[iGNSS][ifreq1][i]);
        ComboBoxSmoothWithMeasAll[iGNSS][icomb][1]->addItem("Auto");
        for (int i=0; i<MeasGNSSOrder[iGNSS][ifreq1].size(); i++) ComboBoxSmoothWithMeasAll[iGNSS][icomb][1]->addItem("L"+FreqGNSSList[iGNSS][ifreq1]+MeasGNSSOrder[iGNSS][ifreq1][i]);    
    } else {
        for (int i=ComboBoxSmoothWithFreqAll[iGNSS][icomb][0]->count()-1; i>=0; i--) ComboBoxSmoothWithFreqAll[iGNSS][icomb][0]->removeItem(i);
        for (int i=ComboBoxSmoothWithMeasAll[iGNSS][icomb][0]->count()-1; i>=0; i--) ComboBoxSmoothWithMeasAll[iGNSS][icomb][0]->removeItem(i);
        for (int i=ComboBoxSmoothWithMeasAll[iGNSS][icomb][1]->count()-1; i>=0; i--) ComboBoxSmoothWithMeasAll[iGNSS][icomb][1]->removeItem(i);
    }
    if ( ifreq2>=0 && ifreq2<nFreqGNSS[iGNSS] ) {
        //freq
        for (int i=ComboBoxSmoothWithFreqAll[iGNSS][icomb][1]->count()-1; i>=0; i--) ComboBoxSmoothWithFreqAll[iGNSS][icomb][1]->removeItem(i);
        for (int i=0; i<FreqNameGNSSList[iGNSS].size(); i++) ComboBoxSmoothWithFreqAll[iGNSS][icomb][1]->addItem(FreqNameGNSSList[iGNSS][i]);
        ComboBoxSmoothWithFreqAll[iGNSS][icomb][0]->currentIndexChanged(ifreq1);
        smoothWithFreqIndexAll[BDS][icomb][1]=ifreq1;
        //meas
        for (int i=ComboBoxSmoothWithMeasAll[iGNSS][icomb][2]->count()-1; i>=0; i--) ComboBoxSmoothWithMeasAll[iGNSS][icomb][2]->removeItem(i);
        ComboBoxSmoothWithMeasAll[iGNSS][icomb][2]->addItem("Auto");
        for (int i=0; i<MeasGNSSOrder[iGNSS][ifreq2].size(); i++) ComboBoxSmoothWithMeasAll[iGNSS][icomb][2]->addItem("L"+FreqGNSSList[iGNSS][ifreq2]+MeasGNSSOrder[iGNSS][ifreq2][i]);

    } else {
        for (int i=ComboBoxSmoothWithFreqAll[iGNSS][icomb][1]->count()-1; i>=0; i--) ComboBoxSmoothWithFreqAll[iGNSS][icomb][1]->removeItem(i);
        for (int i=ComboBoxSmoothWithMeasAll[iGNSS][icomb][2]->count()-1; i>=0; i--) ComboBoxSmoothWithMeasAll[iGNSS][icomb][2]->removeItem(i);
    }
}
//Function to set values for the comboBoxes of smoothed-with meas
void gLAB_GUI::setSmoothWithMeasComboBoxValue(int iGNSS,int icomb,int ifreq1,int ifreq2){
    if ( ifreq1!=-1 && ifreq1==ifreq2 ) return;
    if ( ifreq1>=0 && ifreq1<nFreqGNSS[iGNSS] ) {
        //meas
        for (int i=ComboBoxSmoothWithMeasAll[iGNSS][icomb][0]->count()-1; i>=0; i--) ComboBoxSmoothWithMeasAll[iGNSS][icomb][0]->removeItem(i);
        for (int i=ComboBoxSmoothWithMeasAll[iGNSS][icomb][1]->count()-1; i>=0; i--) ComboBoxSmoothWithMeasAll[iGNSS][icomb][1]->removeItem(i);
        ComboBoxSmoothWithMeasAll[iGNSS][icomb][0]->addItem("Auto");
        for (int i=0; i<MeasCodeGNSSOrder[iGNSS][ifreq1].size(); i++) ComboBoxSmoothWithMeasAll[iGNSS][icomb][0]->addItem("C"+FreqGNSSList[iGNSS][ifreq1]+MeasCodeGNSSOrder[iGNSS][ifreq1][i]);
        ComboBoxSmoothWithMeasAll[iGNSS][icomb][1]->addItem("Auto");
        for (int i=0; i<MeasGNSSOrder[iGNSS][ifreq1].size(); i++) ComboBoxSmoothWithMeasAll[iGNSS][icomb][1]->addItem("L"+FreqGNSSList[iGNSS][ifreq1]+MeasGNSSOrder[iGNSS][ifreq1][i]);

    } else if (ifreq1<-1) {
        for (int i=ComboBoxSmoothWithMeasAll[iGNSS][icomb][0]->count()-1; i>=0; i--) ComboBoxSmoothWithMeasAll[iGNSS][icomb][0]->removeItem(i);
        for (int i=ComboBoxSmoothWithMeasAll[iGNSS][icomb][1]->count()-1; i>=0; i--) ComboBoxSmoothWithMeasAll[iGNSS][icomb][1]->removeItem(i);
    }
    if ( ifreq2>=0 && ifreq2<nFreqGNSS[iGNSS] ) {
        //meas
        for (int i=ComboBoxSmoothWithMeasAll[iGNSS][icomb][2]->count()-1; i>=0; i--) ComboBoxSmoothWithMeasAll[iGNSS][icomb][2]->removeItem(i);
        ComboBoxSmoothWithMeasAll[iGNSS][icomb][2]->addItem("Auto");
        for (int i=0; i<MeasGNSSOrder[iGNSS][ifreq2].size(); i++) ComboBoxSmoothWithMeasAll[iGNSS][icomb][2]->addItem("L"+FreqGNSSList[iGNSS][ifreq2]+MeasGNSSOrder[iGNSS][ifreq2][i]);

    } else if (ifreq2<-1) {
        for (int i=ComboBoxSmoothWithMeasAll[iGNSS][icomb][2]->count()-1; i>=0; i--) ComboBoxSmoothWithMeasAll[iGNSS][icomb][2]->removeItem(i);
    }
}
//Function to set default smoothed-with frequency according to smoothed frequency and smooth type
void gLAB_GUI::setSmoothWithFreqAll(int iGNSS,int icomb,int SmoothType){
    //single frequency
    if (ui->radioButtonSingleFreq->isChecked()) {
        int freq1=ComboBoxGNSSFreq[iGNSS][icomb][0]->currentIndex();
        //for single frequency smoothed-with type
        if (SmoothType<3){
            smoothWithFreqNoSame=0;
            this->setSmoothWithFreqComboBoxValue(iGNSS,icomb,freq1,-1);
            ComboBoxSmoothWithFreqAll[iGNSS][icomb][0]->setCurrentIndex(freq1);
            smoothWithFreqNoSame=1;

        //for dual frequency smoothed-with type
        } else {
            //set second frequency
            int freq2=1;
            if (freq1!=0){
                freq2=freq1;
                freq1=0;
            }
            smoothWithFreqNoSame=0;
            this->setSmoothWithFreqComboBoxValue(iGNSS,icomb,freq1,freq2);
            ComboBoxSmoothWithFreqAll[iGNSS][icomb][0]->setCurrentIndex(freq1);
            ComboBoxSmoothWithFreqAll[iGNSS][icomb][1]->setCurrentIndex(freq2);
            smoothWithFreqNoSame=1;
        }

    //dual frequency
    } else if (ui->radioButtonDualFreq->isChecked()) {
        smoothWithFreqNoSame=0;
        //get smoothed dual frequency
        int ipc12=ComboBoxGNSSFreq[iGNSS][icomb][0]->currentIndex();
        if ( ipc12>=0 && ipc12<nDualFreqGNSS[iGNSS] ){
            int freq1=iFreqDualGNSS[iGNSS][ipc12][0],freq2=iFreqDualGNSS[iGNSS][ipc12][1];
            this->setSmoothWithFreqComboBoxValue(iGNSS,icomb,freq1,freq2);
            ComboBoxSmoothWithFreqAll[iGNSS][icomb][0]->setCurrentIndex(freq1);
            ComboBoxSmoothWithFreqAll[iGNSS][icomb][1]->setCurrentIndex(freq2);
        }
        smoothWithFreqNoSame=1;
    }
}

//Check if measurement has code (returns 1 if code measurement is found)
int gLAB_GUI::meas_has_code(QString meas) {

    QString measUpper=meas.toUpper();
    if (meas.contains("code",Qt::CaseInsensitive) || meas.contains("pc",Qt::CaseInsensitive) ||
        measUpper.contains(QRegularExpression("P[1-9]")) || measUpper.contains(QRegularExpression("C[1-9][A-Z]")) ||
        measUpper.contains(QRegularExpression("^[PC][1-9]$")) ) {
            //Do not count the code measurement for the graphic combination as a code measurement, as it is part of the graphic combination (which is carrier phase)
            if (measUpper.contains(QRegularExpression("G[1-9]-C[1-9][A-Z]-L[1-9][A-Z]$"))) {
                return 0;
            }
            return 1;
    }
    return 0;
}

//This function only runs if '-pre:smoothmeas' is provided, and checks that all code measurements provided in '-pre:smoothmeas' are provided in '-filter:meas'
void gLAB_GUI::checkSmoothFilterMeasInFilterMeas(QString *warningString, QStringList *ParametersList) {

    int badParam;
    int nOpt=ParametersList->count();
    QStringList paramOK;
    //Loop to check filter measurements against smoothing measurements
    for (int iOpt=0; iOpt<nOpt; iOpt++) {
        //Check parameter
        badParam=this->checkUserInputFilterMeasurement(warningString,ParametersList->at(iOpt),MeasTargetFilter);
        if (badParam) {
            paramOK.append("0");
            continue;
        }
        paramOK.append("1");
        //get constellation and freq/meas option
        QString gnssMeasStr=ParametersList->at(iOpt);
        QStringList FilterMeasToBeMatchedOpt=ParametersList->at(iOpt).split("-", QString::SkipEmptyParts);
        int nOptMeas=FilterMeasToBeMatchedOpt.count();
        if (nOptMeas<2) continue;
        //loop constellation
        QString wrongConst="";
        for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
            bool measOK=false;
            int icomb=-1,iCP=-1;
            if ( FilterMeasToBeMatchedOpt[0].contains(indentifierGNSS[iGNSS],Qt::CaseInsensitive)==false && FilterMeasToBeMatchedOpt[0]!="0"  ) continue;
            for (icomb=0; icomb<3; icomb++) {
                for (iCP=0; iCP<2; iCP++) {
                    if ( GNSSMeasInAll[iGNSS][icomb][iCP].size()>0) {
                        QStringList FilterSelectMeasOpt = GNSSMeasInAll[iGNSS][icomb][iCP].split("-", QString::SkipEmptyParts);
                        int nOptFilter=FilterSelectMeasOpt.count();
                        if (nOptFilter==2 && nOptMeas==2 ) {
                            if (QString::compare(FilterMeasToBeMatchedOpt[1], FilterSelectMeasOpt[1], Qt::CaseInsensitive)==0 && QString::compare(FilterMeasToBeMatchedOpt[1], "auto", Qt::CaseInsensitive)!=0) {
                                measOK=true;
                                break;
                            }
                        } else if (nOptFilter==3 && nOptMeas==3 ) {
                            if ( (FilterMeasToBeMatchedOpt[1].contains("code",Qt::CaseInsensitive) && FilterSelectMeasOpt[1].contains("code",Qt::CaseInsensitive)) ||
                                  (FilterMeasToBeMatchedOpt[1].contains("phase",Qt::CaseInsensitive) && FilterSelectMeasOpt[1].contains("phase",Qt::CaseInsensitive)) ) {
                                if (QString::compare(FilterMeasToBeMatchedOpt[2], FilterSelectMeasOpt[2], Qt::CaseInsensitive)==0) {
                                    measOK=true;
                                }
                            } else if (QString::compare(FilterMeasToBeMatchedOpt[1], FilterSelectMeasOpt[1], Qt::CaseInsensitive)==0) {
                                if ( (FilterMeasToBeMatchedOpt[2].contains("code",Qt::CaseInsensitive) && FilterSelectMeasOpt[2].contains("code",Qt::CaseInsensitive)) ||
                                      (FilterMeasToBeMatchedOpt[2].contains("phase",Qt::CaseInsensitive) && FilterSelectMeasOpt[2].contains("phase",Qt::CaseInsensitive)) ) {
                                    measOK=true;
                                }
                            }
                        } else if (nOptFilter==4 && nOptMeas==4) {
                            if (QString::compare(FilterMeasToBeMatchedOpt[1], FilterSelectMeasOpt[1], Qt::CaseInsensitive)==0
                                    && QString::compare(FilterMeasToBeMatchedOpt[2], FilterSelectMeasOpt[2], Qt::CaseInsensitive)==0
                                    && QString::compare(FilterMeasToBeMatchedOpt[3], FilterSelectMeasOpt[3], Qt::CaseInsensitive)==0) {
                                measOK=true;
                                break;
                            }
                        }
                    }
                }
                if (measOK==true) break;
            }
            if ( measOK==false ) {
                wrongConst+=", " + GNSSName[iGNSS];
                continue;
            }
        }
        if ( wrongConst!="" ) {
            wrongConst=wrongConst.mid(2); //To remove leading comma and space
            QString pluralAttrib=wrongConst.length()>1?"ies":"y";
            QString pluralDoes=wrongConst.length()>1?"":"es";
            int lastCommaIndex=wrongConst.lastIndexOf(",");
            if (lastCommaIndex>=0) {
                wrongConst.replace(lastCommaIndex,1," and ");
            }
            *warningString += "FILTER: Measurement '" +  gnssMeasStr + "' provided with parameter '-filter:select' cannot be matched with any code measurement provided in '-pre:smoothmeas' option for " + wrongConst + ". Measurement will not be used in the filter.\n";
            continue;
        }
    }

    //Loop to check smoothing measurements against filter measurements
    for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
        int icomb=-1,iCP=-1;
        for (icomb=0; icomb<3; icomb++) {
            for (iCP=0; iCP<2; iCP++) {
                bool measOK=false;
                if ( GNSSMeasInAll[iGNSS][icomb][iCP].size()>0) {
                    for (int iOpt=0; iOpt<nOpt; iOpt++) {
                        if (paramOK.at(iOpt)=="0") continue;
                        QString gnssMeasStr=ParametersList->at(iOpt);
                        QStringList FilterMeasToBeMatchedOpt=ParametersList->at(iOpt).split("-", QString::SkipEmptyParts);
                        int nOptMeas=FilterMeasToBeMatchedOpt.count();
                        if ( FilterMeasToBeMatchedOpt[0].contains(indentifierGNSS[iGNSS],Qt::CaseInsensitive)==false && FilterMeasToBeMatchedOpt[0]!="0"  ) continue;
                        if (nOptMeas<2) continue;
                        QStringList FilterSelectMeasOpt = GNSSMeasInAll[iGNSS][icomb][iCP].split("-", QString::SkipEmptyParts);
                        int nOptFilter=FilterSelectMeasOpt.count();
                        if (nOptFilter==2 && nOptMeas==2 ) {
                            if (QString::compare(FilterMeasToBeMatchedOpt[1], FilterSelectMeasOpt[1], Qt::CaseInsensitive)==0 && QString::compare(FilterMeasToBeMatchedOpt[1], "auto", Qt::CaseInsensitive)!=0) {
                                measOK=true;
                                break;
                            }
                        } else if (nOptFilter==3 && nOptMeas==3 ) {
                            if ( (FilterMeasToBeMatchedOpt[1].contains("code",Qt::CaseInsensitive) && FilterSelectMeasOpt[1].contains("code",Qt::CaseInsensitive)) ||
                                  (FilterMeasToBeMatchedOpt[1].contains("phase",Qt::CaseInsensitive) && FilterSelectMeasOpt[1].contains("phase",Qt::CaseInsensitive)) ) {
                                if (QString::compare(FilterMeasToBeMatchedOpt[2], FilterSelectMeasOpt[2], Qt::CaseInsensitive)==0) {
                                    measOK=true;
                                }
                            } else if (QString::compare(FilterMeasToBeMatchedOpt[1], FilterSelectMeasOpt[1], Qt::CaseInsensitive)==0) {
                                if ( (FilterMeasToBeMatchedOpt[2].contains("code",Qt::CaseInsensitive) && FilterSelectMeasOpt[2].contains("code",Qt::CaseInsensitive)) ||
                                      (FilterMeasToBeMatchedOpt[2].contains("phase",Qt::CaseInsensitive) && FilterSelectMeasOpt[2].contains("phase",Qt::CaseInsensitive)) ) {
                                    measOK=true;
                                }
                            }
                        } else if (nOptFilter==4 && nOptMeas==4) {
                            if (QString::compare(FilterMeasToBeMatchedOpt[1], FilterSelectMeasOpt[1], Qt::CaseInsensitive)==0
                                    && QString::compare(FilterMeasToBeMatchedOpt[2], FilterSelectMeasOpt[2], Qt::CaseInsensitive)==0
                                    && QString::compare(FilterMeasToBeMatchedOpt[3], FilterSelectMeasOpt[3], Qt::CaseInsensitive)==0) {
                                measOK=true;
                                break;
                            }
                        }
                    }
                    if (measOK==false) {
                        *warningString += "FILTER: Code measurement '" +  GNSSMeasInAll[iGNSS][icomb][iCP] + "' provided with parameter '-pre:smoothmeas' cannot be matched with any measurement provided in '-filter:select' option for " + GNSSName[iGNSS] + ". All codes measurements must be also in '-filter:select' to work in command line.\n";
                    }
                }
            }
        }
    }
}

//Check if filter measurement is valid. Returns 0 if valid, 1 if invalid.
int gLAB_GUI::checkUserInputFilterMeasurement (QString *warningString, QString param, enum MeasTargetUsage type) {

    QString     measTypeStr[2]={"filter","smoothing"};
    QStringList ParamOpt=param.split("-", QString::SkipEmptyParts);
    int nOpt=ParamOpt.count();
    int posFirstData=0;
    int FreqNum;
    bool resToInt;


   if (type==MeasTargetFilter) {
       posFirstData=1;
        bool ParamSatRanges=param.contains(QRegularExpression(regExpSatWithRanges));
        bool ParamSatNoRanges=ParamOpt[0].contains(QRegularExpression(regExpSatNoRanges));
        if(!ParamSatNoRanges && !ParamSatRanges ) {
           *warningString += "FILTER: Invalid filter measurement '" + param + "'. It was skipped.\n";
           return 1;
        } else if (ParamSatRanges) {
           *warningString += "FILTER: The GUI cannot read arguments with satellite ranges (except '-pre:sat'), as options are constellations wise. Measurement '" + param + "' was skipped and not validated (it must be validated in command line).\n";
           return 1;
        }
   }
   QString currPartLower=ParamOpt[posFirstData].toLower();
   QString currPartUpper=ParamOpt[posFirstData].toUpper();
   if (currPartLower=="auto") {
       if (nOpt!=(2-type)) {
           *warningString += "FILTER: " + measTypeStr[type] + " measurement '" + param + "' cannot have more data after the '" + currPartLower + "'. It was skipped.\n";
           return 1;
       }
   } else if (currPartLower=="code" || currPartLower=="phase" || currPartLower=="codephase" || currPartLower=="phasecode" || currPartLower=="phco" || currPartLower=="coph") {
       if (nOpt!=(3-type)) {
           *warningString += "FILTER: Invalid " + measTypeStr[type] + " measurement '" + param + "'. When using 'code' or 'phase' in single frequency, only the frequency has to be provided after. It was skipped.\n";
           return 1;
       }
       FreqNum=ParamOpt[posFirstData+1].toInt(&resToInt);
       if (!resToInt || FreqNum<1 || FreqNum>9 ) {
           *warningString += "FILTER: " + measTypeStr[type] + " measurement '" + param + " has invalid frequency'. It was skipped.\n";
           return 1;
       }
   } else if (currPartUpper.contains(QRegularExpression("^IF[1-9][1-9]$"))) {
       if (nOpt!=(3-type) && nOpt!=(4-type) ) {
           *warningString += "FILTER: Invalid " + measTypeStr[type] + " measurement '" + param + "' When using IF measurements, either 'code' or 'phase' or the two measurements must be provided. It was skipped.\n";
           return 1;
       }
       if (nOpt==(3-type)) {
           currPartLower=ParamOpt[posFirstData+1].toLower();
           if (!(currPartLower=="code" || currPartLower=="phase" || currPartLower=="codephase" || currPartLower=="phasecode" || currPartLower=="phco" || currPartLower=="coph")) {
               *warningString += "FILTER: Invalid " + measTypeStr[type] + " measurement '" + param + "'. When using IF measurements, 'code' or 'phase' or 'codephase' or only the two frequencies have to be provided after. It was skipped.\n";
               return 1;
           }
       } else if (nOpt==(4-type)) {
           int numCodes=0,numPhases=0,error=0;
           for(int i=0;i<2;i++) {
               currPartUpper=ParamOpt[posFirstData+1+i].toUpper();
               if (!currPartUpper.contains(QRegularExpression("^[CL]" + ParamOpt[posFirstData].mid(2+i,1) + regExpValidAttributes + "$"))) {
                   error=1;
               }
               if (currPartUpper.mid(0,1)=="C") numCodes++;
               else if (currPartUpper.mid(0,1)=="L") numPhases++;
           }
           if (error==1) {
               numCodes=numPhases=0;
               for(int i=0;i<2;i++) {
                   currPartUpper=ParamOpt[posFirstData+1+i].toUpper();
                   if (!currPartUpper.contains(QRegularExpression("^[CL]" + ParamOpt[posFirstData].mid(3-i,1) + regExpValidAttributes + "$"))) {
                       *warningString += "FILTER: " + measTypeStr[type] + " measurement '" + param + "' has invalid code or phase measurements or frequencies do not match. It was skipped.\n";
                       return 1;
                   }
                   if (currPartUpper.mid(0,1)=="C") numCodes++;
                   else if (currPartUpper.mid(0,1)=="L") numPhases++;
               }
           }
           if (!(numCodes==2 ||numPhases==2) ) {
               *warningString += "FILTER: " + measTypeStr[type] + " measurement '" + param + "' does not have either two codes or two carrier phases. It was skipped.\n";
               return 1;
           }
       }
   } else if (currPartUpper.contains(QRegularExpression("^PC[1-9][1-9]$"))) {
       if (nOpt!=(2-type) && nOpt!=(4-type)) {
           *warningString += "FILTER: Invalid " + measTypeStr[type] + " measurement '" + param + "'. When using PC measurement, no codes or two codes must be provided. It was skipped.\n";
           return 1;
       }
       if (nOpt==(4-type)) {
           int error=0;
           for(int i=0;i<2;i++) {
               currPartUpper=ParamOpt[posFirstData+1+i].toUpper();
               if (!currPartUpper.contains(QRegularExpression("^C" + ParamOpt[posFirstData].mid(2+i,1) + regExpValidAttributes+"$"))) {
                   error=1;
               }
           }
           if (error==1) {
               for(int i=0;i<2;i++) {
                   currPartUpper=ParamOpt[posFirstData+1+i].toUpper();
                   if (!currPartUpper.contains(QRegularExpression("^C" + ParamOpt[posFirstData].mid(3-i,1) + regExpValidAttributes+"$"))) {
                       *warningString += "FILTER: Invalid " + measTypeStr[type] + " measurement '" + param + "'. It does not contain valid codes or frequencies do not match. It was skipped.\n";
                       return 1;
                   }
               }
           }
       }
   } else if (currPartUpper.contains(QRegularExpression("^LC[1-9][1-9]$"))) {
       if (nOpt!=(2-type) && nOpt!=(4-type)) {
           *warningString += "FILTER: Invalid " + measTypeStr[type] + " measurement '" + param + "'. When using LC measurement, no phases or two phases must be provided. It was skipped.\n";
           return 1;
       }
       if (nOpt==(4-type)) {
           int error=0;
           for(int i=0;i<2;i++) {
               currPartUpper=ParamOpt[posFirstData+1+i].toUpper();
               if (!currPartUpper.contains(QRegularExpression("^L" + ParamOpt[posFirstData].mid(2+i,1) + regExpValidAttributes+"$"))) {
                   error=1;
               }
           }
           if (error==1) {
               for(int i=0;i<2;i++) {
                   currPartUpper=ParamOpt[posFirstData+1+i].toUpper();
                   if (!currPartUpper.contains(QRegularExpression("^L" + ParamOpt[posFirstData].mid(3-i,1) + regExpValidAttributes+"$"))) {
                       *warningString += "FILTER: Invalid " + measTypeStr[type] + " measurement '" + param + "'. It does not contain valid carrier phases or frequencies do not match. It was skipped.\n";
                       return 1;
                   }
               }
           }
       }
   } else if (currPartUpper.contains(QRegularExpression("^G[1-9]$"))) {
       if (nOpt!=(2-type) && nOpt!=(4-type)) {
           *warningString += "FILTER: Invalid " + measTypeStr[type] + " measurement '" + param + "'. When using graphical combination, either no measurements or one code and one carrier phase must be provided. It was skipped.\n";
           return 1;
       }

       if (nOpt==(4-type)) {
           int error=0;
           QString typeMeas[2]={"C","L"};
           for(int i=0;i<2;i++) {
               currPartUpper=ParamOpt[posFirstData+1+i].toUpper();
               if (!currPartUpper.contains(QRegularExpression("^" + typeMeas[i] + ParamOpt[posFirstData].mid(1,1) +regExpValidAttributes+"$"))) {
                   error=1;
               }
           }
           if (error==1) {
               QString typeMeas[2]={"L","C"};
               for(int i=0;i<2;i++) {
                   currPartUpper=ParamOpt[posFirstData+1+i].toUpper();
                   if (!currPartUpper.contains(QRegularExpression("^" + typeMeas[i] + ParamOpt[posFirstData].mid(1,1) +regExpValidAttributes+"$"))) {
                       *warningString += "FILTER: Invalid " + measTypeStr[type] + " measurement '" + param + "'. When using graphic combination, either no measurements or one code and one carrier phase from the same frequency must be provided. It was skipped.\n";
                       return 1;
                   }
               }
           }
       }
   } else if (currPartUpper.contains(QRegularExpression("^DF[1-9][1-9]$"))) {
       if (nOpt!=(2-type) && nOpt!=(3-type) && nOpt!=(4-type)) {
           *warningString += "FILTER: Invalid " + measTypeStr[type] + " measurement '" + param + "'. When using DF measurement, no measurements or words 'code' or 'phase' or two codes or two carrier phases from different frequencies must be provided. It was skipped.\n";
           return 1;
       }
       int numCodes=0,numPhases=0;
       if (nOpt!=(3-type)) {
           currPartUpper=ParamOpt[posFirstData+1].toUpper();
           if (currPartUpper!="code" && currPartUpper!="phase") {
               *warningString += "FILTER: Invalid " + measTypeStr[type] + " measurement '" + param + "'. When using DF measurement, no measurements or words 'code' or 'phase' or two codes or two carrier phases from different frequencies must be provided. It was skipped.\n";
               return 1;
           }
       } else if (nOpt==(4-type)) {
           int error=0;
           for(int i=0;i<2;i++) {
               currPartUpper=ParamOpt[posFirstData+1+i].toUpper();
               if (!currPartUpper.contains(QRegularExpression("^[CL]" + ParamOpt[posFirstData].mid(2+i,1) + regExpValidAttributes+"$"))) {
                   error=1;
               }
               if (currPartUpper.mid(0,1)=="C") numCodes++;
               else if (currPartUpper.mid(0,1)=="L") numPhases++;
           }
           if (error==1) {
               numCodes=numPhases=0;
               for(int i=0;i<2;i++) {
                   currPartUpper=ParamOpt[posFirstData+1+i].toUpper();
                   if (!currPartUpper.contains(QRegularExpression("^[CL]" + ParamOpt[posFirstData].mid(3-i,1) + regExpValidAttributes+"$"))) {
                       *warningString += "FILTER: Invalid " + measTypeStr[type] + " measurement '" + param + "' When using DF measurement, no measurements or words 'code' or 'phase' or two codes or two carrier phases from different frequencies must be provided.. It was skipped.\n";
                       return 1;
                   }
                   if (currPartUpper.mid(0,1)=="C") numCodes++;
                   else if (currPartUpper.mid(0,1)=="L") numPhases++;
               }
           }
           if (!(numCodes==2 ||numPhases==2) ) {
               *warningString += "FILTER: " + measTypeStr[type] + " measurement '" + param + "' does not have either two codes or two carrier phases. It was skipped.\n";
               return 1;
           }
       }
       if (type==0) {
           *warningString += "FILTER: Divergence-free combination can only be used in the GUI for smoothing, not as a filter measurement (but is possible in command line). Parameter '" + param + "' was skipped.\n";
           return 1;
       } else if (numCodes==2 && type==1) {
           *warningString += "FILTER: Divergence-free with codes cannot be used for smoothing. Parameter '" + param + "' was skipped.\n";
           return 1;
       }
   } else if (currPartUpper.contains(QRegularExpression("^[CL][1-9]"+ regExpValidAttributes + "$"))) {
       if (nOpt!=(2-type)) {
           *warningString += "FILTER: Invalid " + measTypeStr[type] + " measurement '" + param + "'. When using single frequency measurement, no more measurements can be provided. It was skipped.\n";
           return 1;
       }
   } else {
       *warningString += "FILTER: Invalid " + measTypeStr[type] + " measurement '" + param + "'. It was skipped.\n";
       return 1;
   }


    return 0;
}

//Load GNSS smoothed frequency and measurement options
void gLAB_GUI::readGNSSSmoothFreqMeas(QString *warningString, QStringList *ParametersList){

    int badParam=0;
    if ( GNSSMeasCMDMode!=0 && GNSSMeasCMDMode!=MEAS_MODE_SMOOTH ) return;

    if ( ParametersList->count()%2!=0 ){
        *warningString += "FILTER: Parameter '-pre:smoothMeas' has missing values (it must have pairs of code and phase measurements). It was skipped.\n";
        return;
    } else if (ui->radioButtonSelectionGraphic->isChecked()) {
        *warningString += "FILTER: Smoothing measurements cannot be loaded if graphic combination is set with option '-filter:combtype graphic'. Parameter '-pre:smoothMeas' was skipped.\n";
        return;
    }
    int lastiSMCode=-1,lastiSMPhase=-1;
    int setSingleFreq=0, setDualFreq=0;
    int nSM=ParametersList->count()/2;

    for (int iSM=0; iSM<nSM; iSM++) {
        int skipMeas=0;
        ///////////////////////////////////////////////////////////////////////////////////////////////
        //get selected freq & meas
        QStringList FreqMeasOpt=ParametersList->at(2*iSM).split("-", QString::SkipEmptyParts);
        int nFMOpt=FreqMeasOpt.count();
        bool freqMeasOK=false;
        int currentParamGNSSUsed[MAX_GNSS]={0};

        badParam=this->checkUserInputFilterMeasurement(warningString,ParametersList->at(2*iSM),MeasTargetFilter);
        if (badParam) continue;
        badParam=this->checkUserInputFilterMeasurement(warningString,ParametersList->at(2*iSM+1),MeasTargetSmooth);
        if (badParam) continue;

        if (meas_has_code(ParametersList->at(2*iSM))==0) {
            *warningString +="FILTER: Parameter '-pre:smoothMeas' has invalid argument '" + ParametersList->at(2*iSM) + "'. The parameter was skipped as it is not a code measurement.\n";
            continue;
        }
        if (meas_has_code(ParametersList->at(2*iSM+1))==1) {
            *warningString +="FILTER: Parameter '-pre:smoothMeas' has invalid argument '" + ParametersList->at(2*iSM+1) + "'. The parameter was skipped as it is not a carrier phase measurement.\n";
            continue;
        }

        if (ParametersList->at(2*iSM).mid(0,1)=="-") continue;
        //loop constellation
        int validArgument=0;
        for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++){
            if ( ( FreqMeasOpt[0].contains(indentifierGNSS[iGNSS],Qt::CaseInsensitive)==false && FreqMeasOpt[0]!="0" ) || nFMOpt<2) continue;

            //Auto for code or phase combination
            if (FreqMeasOpt[1].contains("auto",Qt::CaseInsensitive)) {
                //Auto cannot be set for pseudorange measurement in smoothing, as you cannot match it with a filter measurement
                if (lastiSMCode!=iSM) {
                    *warningString += "FILTER: 'Auto' option cannot be set for pseudorange measurement to smooth with (as it cannot be matched to any specific measurement). Measurement " + ParametersList->at(2*iSM) + "' was skipped.\n";
                    lastiSMCode=iSM;
                }
                skipMeas=1;
               continue;
            //single code frequency
            } else if (FreqMeasOpt[1].contains("Code",Qt::CaseInsensitive) && !FreqMeasOpt[1].contains("phase",Qt::CaseInsensitive)) {
                if (nFMOpt<3) continue;
                if ( GNSSFreqCMDMode!=0 && GNSSFreqCMDMode!=MEAS_MODE_SINGLE ) {
                    if (setDualFreq==1) {
                        if (lastiSMCode!=iSM) {
                            *warningString += "FILTER: The GUI does not support loading both single and dual frequency combinations at the same time (command line does). Measurement '" + ParametersList->at(2*iSM) + "' was skipped.\n";
                            lastiSMCode=iSM;
                        }
                        skipMeas=1;
                    }
                    continue;
                }
                if (GNSSMeasCMD[iGNSS][0]>2) {
                    *warningString += "FILTER: Maximum number of measurements for " + GNSSName[iGNSS] + " in the filter is 3. Argument '" + ParametersList->at(2*iSM) + "' was skipped for " + GNSSName[iGNSS] + " as limit has been surpassed.\n";
                    skipMeas=1;
                    continue;
                }
                int ifreq=-1;
                for (ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                    if (FreqMeasOpt[2]==FreqGNSSList[iGNSS][ifreq]) break;
                }
                if (ifreq>=nFreqGNSS[iGNSS]) {
                    *warningString += "FILTER: Frequency '" + FreqMeasOpt[2] + "' in measurement '" + ParametersList->at(2*iSM) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                    continue;
                }
                if (GNSSFreqCMDMode==0) {
                    GNSSFreqCMDMode=MEAS_MODE_SINGLE;
                    this->on_radioButtonSingleFreq_clicked();
                    setSingleFreq=1;
                }
                if (GNSSMeasCMDMode==0) {
                    GNSSMeasCMDMode=MEAS_MODE_SMOOTH;
                    if ( GNSSSmoothFlag==0 ) this->on_radioButtonSmoothing_clicked();
                }
                if (FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]]->isHidden()) FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]]->setHidden(false);
                setGNSSMeasurementFreqCP(iGNSS,GNSSMeasCMD[iGNSS][CODEARRAYPOS],CODEARRAYPOS,ifreq);
                ComboBoxGNSSFreq[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]][CODEARRAYPOS]->currentIndexChanged(ifreq);
                GNSSMeasInAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]][CODEARRAYPOS]=ParametersList->at(2*iSM);
                GNSSMeasCMD[iGNSS][CODEARRAYPOS]++;
                currentParamGNSSUsed[iGNSS]=1;
                freqMeasOK=true;
                validArgument=1;

            //dual code frequency
            } else if ( FreqMeasOpt[1].mid(0,2).contains("IF",Qt::CaseInsensitive) || FreqMeasOpt[1].mid(0,2).contains("PC",Qt::CaseInsensitive) ) {
                QString dualFreqStr="PC";
                if(FreqMeasOpt[1].size()!=4) continue;
                if ( GNSSFreqCMDMode!=0 && GNSSFreqCMDMode!=MEAS_MODE_DUAL ) {
                    if (setSingleFreq==1) {
                        if (lastiSMCode!=iSM) {
                            *warningString += "FILTER: The GUI does not support loading both single and dual frequency combinations at the same time (command line does). Measurement '" + ParametersList->at(2*iSM) + "' was skipped.\n";
                            lastiSMCode=iSM;
                        }
                        skipMeas=1;
                    }
                    continue;
                }
                if (GNSSMeasCMD[iGNSS][0]>2) {
                    *warningString += "FILTER: Maximum number of measurements for " + GNSSName[iGNSS] + " in the filter is 3. Argument '" + ParametersList->at(2*iSM) + "' was skipped for " + GNSSName[iGNSS] + " as limit has been surpassed.\n";
                    skipMeas=1;
                    continue;
                }
                if (nFMOpt>=3) {
                    if (FreqMeasOpt[1].contains("phase",Qt::CaseInsensitive) || FreqMeasOpt[1].contains("coph",Qt::CaseInsensitive) || FreqMeasOpt[1].contains("phco",Qt::CaseInsensitive) ||
                      ParametersList->at(2*iSM).toUpper().contains(QRegularExpression("-L[1-9][A-Z]-L[1-9][A-Z]$")) ||
                      ParametersList->at(2*iSM).toUpper().contains(QRegularExpression("-C[1-9][A-Z]-L[1-9][A-Z]$")) ||
                      ParametersList->at(2*iSM).toUpper().contains(QRegularExpression("-L[1-9][A-Z]-C[1-9][A-Z]$"))  ) {
                        if (lastiSMCode!=iSM) {
                            *warningString += "FILTER: Measurement to be smoothed '" + ParametersList->at(2*iSM) + "' is invalid as it cannot contain carrier phases. It was skipped.\n";
                            lastiSMCode=iSM;
                        }
                        skipMeas=1;
                        continue;
                    }
                }
                //reset frequency order
                if (FreqMeasOpt[1][2]>FreqMeasOpt[1][3]){
                    dualFreqStr += FreqMeasOpt[1].mid(3,1) + FreqMeasOpt[1].mid(2,1);
                } else {
                    dualFreqStr += FreqMeasOpt[1].mid(2,1) + FreqMeasOpt[1].mid(3,1);
                }
                //get frequency conbination
                int iDual=-1;
                for (iDual=0; iDual<nDualFreqGNSS[iGNSS]; iDual++){
                    if (dualFreqStr==FreqCodeDualGNSSList[iGNSS][iDual]) break;
                }
                if (iDual>=nDualFreqGNSS[iGNSS]) {
                    *warningString += "FILTER: Invalid frequencies in '" + ParametersList->at(2*iSM) + "' for " + GNSSName[iGNSS] + " constellation. It was skipped.\n";
                    continue;
                }
                //set frequency
                if (nFMOpt==2){
                    if (GNSSFreqCMDMode==0) {
                        GNSSFreqCMDMode=MEAS_MODE_DUAL;
                        this->on_radioButtonDualFreq_clicked();
                        setDualFreq=1;
                    }
                    if (GNSSMeasCMDMode==0) {
                        GNSSMeasCMDMode=MEAS_MODE_SMOOTH;
                        if ( GNSSSmoothFlag==0 ) this->on_radioButtonSmoothing_clicked();
                    }
                    if (FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]]->isHidden()) FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]]->setHidden(false);
                    setGNSSMeasurementFreqCP(iGNSS,GNSSMeasCMD[iGNSS][CODEARRAYPOS],CODEARRAYPOS,iDual);
                    ComboBoxGNSSFreq[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]][CODEARRAYPOS]->currentIndexChanged(iDual);
                    GNSSMeasInAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]][CODEARRAYPOS]=ParametersList->at(2*iSM);
                    GNSSMeasCMD[iGNSS][CODEARRAYPOS]++;
                    currentParamGNSSUsed[iGNSS]=1;
                    freqMeasOK=true;
                    validArgument=1;

                //set measurement
                } else if (nFMOpt==4){
                    if( FreqMeasOpt[2].size()!=3 || FreqMeasOpt[3].size()!=3 ) continue;
                    //get frequency
                    int ifreq1=-1,ifreq2=-1;
                    for (int ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                        if (FreqMeasOpt[2].mid(1,1)==FreqGNSSList[iGNSS][ifreq]) ifreq1=ifreq;
                        if (FreqMeasOpt[3].mid(1,1)==FreqGNSSList[iGNSS][ifreq]) ifreq2=ifreq;
                    }
                    if (ifreq1<0 ) {
                        *warningString += "FILTER: Frequency '" + FreqMeasOpt[2].mid(1,1) + "' in measurement '" + FreqMeasOpt[2] + "' in argument '" + ParametersList->at(2*iSM) + "' for the filter does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if (ifreq2<0 ) {
                        *warningString += "FILTER: Frequency '" + FreqMeasOpt[3].mid(1,1) + "' in measurement '" + FreqMeasOpt[3] + "' in argument '" + ParametersList->at(2*iSM) + "' for the filter does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if ( ifreq1==ifreq2) {
                        if (lastiSMCode!=iSM) {
                            *warningString += "FILTER: Frequencies '" + FreqMeasOpt[2].mid(1,1) + "' and '" + FreqMeasOpt[3].mid(1,1) + "' in measurements in argument '" + ParametersList->at(2*iSM) + "' for the filter are repeated. It was skipped.\n";
                            lastiSMCode=iSM;
                        }
                        continue;
                    }
                    //get measurement
                    int imeas1=-1,imeas2=-1;
                    for (imeas1=0;imeas1<MeasCodeGNSSOrder[iGNSS][ifreq1].size();imeas1++){
                        if (FreqMeasOpt[2].toUpper().mid(2,1)==MeasCodeGNSSOrder[iGNSS][ifreq1].mid(imeas1,1)){
                            break;
                        }
                    }
                    for (imeas2=0;imeas2<MeasCodeGNSSOrder[iGNSS][ifreq2].size();imeas2++){
                        if (FreqMeasOpt[3].toUpper().mid(2,1)==MeasCodeGNSSOrder[iGNSS][ifreq2].mid(imeas2,1)){
                            break;
                        }
                    }
                    if (imeas1>=MeasCodeGNSSOrder[iGNSS][ifreq1].size() && imeas2>=MeasCodeGNSSOrder[iGNSS][ifreq2].size()) {
                        *warningString += "FILTER: Measurements '" + FreqMeasOpt[2] + "' and '" + FreqMeasOpt[3] + "' in argument '" + ParametersList->at(2*iSM) + "' for the filter do not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if (imeas1>=MeasCodeGNSSOrder[iGNSS][ifreq1].size() ) {
                        *warningString += "FILTER: Measurement '" + FreqMeasOpt[2] + "' in argument '" + ParametersList->at(2*iSM) + "' for the filter does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if (imeas2>=MeasCodeGNSSOrder[iGNSS][ifreq2].size() ) {
                        *warningString += "FILTER: Measurement '" + FreqMeasOpt[3] + "' in argument '" + ParametersList->at(2*iSM) + "' for the filter does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    }

                    //reset order
                    if ( ifreq1 > ifreq2 ){
                        int measBuff=imeas1;
                        imeas1=imeas2;
                        imeas2=measBuff;
                    }
                    if (GNSSFreqCMDMode==0) {
                        GNSSFreqCMDMode=MEAS_MODE_DUAL;
                        this->on_radioButtonDualFreq_clicked();
                        setDualFreq=1;
                    }
                    if (GNSSMeasCMDMode==0) {
                        GNSSMeasCMDMode=MEAS_MODE_SMOOTH;
                        if ( GNSSSmoothFlag==0 ) this->on_radioButtonSmoothing_clicked();
                    }
                    if (FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]]->isHidden()) FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]]->setHidden(false);
                    setGNSSMeasurementFreqCP(iGNSS,GNSSMeasCMD[iGNSS][CODEARRAYPOS],CODEARRAYPOS,iDual);
                    ComboBoxGNSSFreq[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]][CODEARRAYPOS]->currentIndexChanged(iDual);
                    ComboBoxGNSSMeas[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]][CODEARRAYPOS][COMBMEAS1ARRAYPOS]->currentIndexChanged(imeas1+1);
                    ComboBoxGNSSMeas[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]][CODEARRAYPOS][COMBMEAS2ARRAYPOS]->currentIndexChanged(imeas2+1);
                    //GNSSMeasInAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]][CODEARRAYPOS]=FreqMeasOpt[0]+"-"+dualFreqStr;
                    GNSSMeasInAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]][CODEARRAYPOS]=ParametersList->at(2*iSM);
                    GNSSMeasCMD[iGNSS][CODEARRAYPOS]++;
                    currentParamGNSSUsed[iGNSS]=1;
                    freqMeasOK=true;
                    validArgument=1;
                }

            // single code measurement
            } else if (FreqMeasOpt[1].mid(0,1).contains("C",Qt::CaseInsensitive)) {
                if (FreqMeasOpt[1].size()!=3) continue;
                if ( GNSSFreqCMDMode!=0 && GNSSFreqCMDMode!=MEAS_MODE_SINGLE ) {
                    if (setDualFreq==1) {
                        if (lastiSMCode!=iSM) {
                            *warningString += "FILTER: The GUI does not support loading both single and dual frequency combinations at the same time (command line does). Measurement '" + ParametersList->at(2*iSM) + "' was skipped.\n";
                            lastiSMCode=iSM;
                        }
                        skipMeas=1;
                    }
                    continue;
                }
                if (GNSSMeasCMD[iGNSS][0]>2) {
                    *warningString += "FILTER: Maximum number of measurements for " + GNSSName[iGNSS] + " in the filter is 3. Argument '" + ParametersList->at(2*iSM) + "' was skipped for " + GNSSName[iGNSS] + " as limit has been surpassed.\n";
                    skipMeas=1;
                    continue;
                }
                int ifreq;
                for (ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                    if (FreqMeasOpt[1].mid(1,1)==FreqGNSSList[iGNSS][ifreq]) break;
                }
                if (ifreq>=nFreqGNSS[iGNSS]) {
                    *warningString += "FILTER: Frequency '" + FreqMeasOpt[1].mid(1,1) + "' in measurement '" + ParametersList->at(2*iSM) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                    skipMeas=1;
                    continue;
                }
                int imeas;
                for (imeas=0;imeas<MeasCodeGNSSOrder[iGNSS][ifreq].size();imeas++){
                    if (FreqMeasOpt[1].toUpper().mid(2,1)==MeasCodeGNSSOrder[iGNSS][ifreq].mid(imeas,1)){
                        if (GNSSFreqCMDMode==0) {
                            GNSSFreqCMDMode=MEAS_MODE_SINGLE;
                            this->on_radioButtonSingleFreq_clicked();
                            setSingleFreq=1;
                        }
                        if (GNSSMeasCMDMode==0) {
                            GNSSMeasCMDMode=MEAS_MODE_SMOOTH;
                            if ( GNSSSmoothFlag==0 ) this->on_radioButtonSmoothing_clicked();
                        }
                        if ( FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]]->isHidden() ) FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]]->setHidden(false);
                        setGNSSMeasurementFreqCP(iGNSS,GNSSMeasCMD[iGNSS][CODEARRAYPOS],CODEARRAYPOS,ifreq);
                        ComboBoxGNSSFreq[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]][CODEARRAYPOS]->currentIndexChanged(ifreq);
                        ComboBoxGNSSMeas[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]][CODEARRAYPOS][COMBMEAS1ARRAYPOS]->currentIndexChanged(imeas+1);
                        GNSSMeasInAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]][CODEARRAYPOS]=ParametersList->at(2*iSM);
                        GNSSMeasCMD[iGNSS][CODEARRAYPOS]++;
                        currentParamGNSSUsed[iGNSS]=1;
                        freqMeasOK=true;
                        validArgument=1;
                        break;
                    }
                }
                if (imeas>=MeasCodeGNSSOrder[iGNSS][ifreq].size())  {
                    *warningString += "FILTER: Invalid measurement '" + FreqMeasOpt[1] + "' in argument '" + ParametersList->at(2*iSM) + "' for " + GNSSName[iGNSS] + " constellation. It was skipped.\n";
                    continue;
                }
            //Phase measurement
            } else if (FreqMeasOpt[1].contains("Phase",Qt::CaseInsensitive) || FreqMeasOpt[1].mid(0,1).contains("L",Qt::CaseInsensitive) ) {
                if (lastiSMCode!=iSM) {
                    *warningString += "FILTER: Measurement to smooth must be a pseudorange, but carrier phase provided. Measurement '" + ParametersList->at(2*iSM) + "' was skipped.\n";
                    lastiSMCode=iSM;
                }
                skipMeas=1;
                continue;
            // graphic combination
            } else if (FreqMeasOpt[1].mid(0,1).contains("G",Qt::CaseInsensitive)) {
                if (lastiSMCode!=iSM) {
                    *warningString += "FILTER: Graphic combination already contains carrier phase data, so it cannot be smoothed. Measurement '" + ParametersList->at(2*iSM) + "' was skipped.\n";
                    lastiSMCode=iSM;
                }
                skipMeas=1;
                continue;
            //Divergence-free
            } else if ( FreqMeasOpt[1].mid(0,2).contains("DF",Qt::CaseInsensitive) ) {
                if (ParametersList->at(2*iSM).toUpper().contains("phase") || ParametersList->at(2*iSM).toUpper().contains("L[0-9][A-Z]")) {
                    if (lastiSMCode!=iSM) {
                        *warningString += "FILTER: Measurement to smooth must be a pseudorange, but carrier phase provided. Measurement '" + ParametersList->at(2*iSM) + "' was skipped.\n";
                        lastiSMCode=iSM;
                    }
                } else {
                    if (lastiSMCode!=iSM) {
                        *warningString += "FILTER: Divergence-Free measurement cannot be used as a code measurement in the GUI (but is possible in command line). Measurement '" + ParametersList->at(2*iSM) + "' was skipped.\n";
                        lastiSMCode=iSM;
                    }
                }
                skipMeas=1;
                continue;
            } else {
                if (lastiSMCode!=iSM) {
                    *warningString += "FILTER: Invalid filter measurement '" + ParametersList->at(2*iSM) + "'. It was skipped.\n";
                    lastiSMCode=iSM;
                }
                skipMeas=1;
                continue;
            }
        }

        if (skipMeas==1 || validArgument==0) {
            continue;
        }

        //////////////////////////////////////////////////////////////////////////////////////
        //get smoothed with freq & meas
        QStringList SmoothWithOpt=ParametersList->at(2*iSM+1).split("-", QString::SkipEmptyParts);
        int nSMOpt=SmoothWithOpt.count();
        //loop constellation
        for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
            if (currentParamGNSSUsed[iGNSS]==0) continue;
            if ( !freqMeasOK || nSMOpt<1) continue;
            if (SmoothWithOpt[0].contains("auto",Qt::CaseInsensitive)) {
                //Nothing to set, as it is all automatic (default)
            //SF: single phase frequency
            } else if (SmoothWithOpt[0].contains("Phase",Qt::CaseInsensitive)){
                if (nSMOpt!=2) continue;
                int ifreq=-1;
                for (ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                    if (SmoothWithOpt[1]==FreqGNSSList[iGNSS][ifreq]) break;
                }
                if (ifreq>=nFreqGNSS[iGNSS]) {
                    *warningString += "FILTER: Frequency '" + SmoothWithOpt[1] + "' in smoothing measurement '" + ParametersList->at(2*iSM+1) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                    continue;
                }
                if (GNSSMeasCMD[iGNSS][CODEARRAYPOS]>0) {
                    ComboBoxSmoothWithTypeAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1]->currentIndexChanged(1);
                    ComboBoxSmoothWithFreqAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][0]->currentIndexChanged(ifreq);
                    ComboBoxSmoothWithMeasAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][1]->currentIndexChanged(0);
                } else {
                    *warningString += "FILTER: Single frequency smoothing measurement '" + ParametersList->at(2*iSM+1) + "' set for " + GNSSName[iGNSS] + ", but there are no available codes to smooth with. It was skipped.\n";
                }

            //G or GRAPHIC
            } else if ( SmoothWithOpt[0].mid(0,1).contains("G",Qt::CaseInsensitive) ) {
                int ifreq1=-1;
                for (ifreq1=0; ifreq1<nFreqGNSS[iGNSS]; ifreq1++){
                    if (SmoothWithOpt[0].contains(FreqGNSSList[iGNSS][ifreq1])) break;
                }
                if ( ifreq1>=nFreqGNSS[iGNSS] ) {
                    *warningString += "FILTER: Frequency '" + SmoothWithOpt[0].mid(1,1) + "' in smoothing measurement '" + ParametersList->at(2*iSM+1) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                    continue;
                }
                //set frequency
                if (nSMOpt!=3){
                    if (GNSSMeasCMD[iGNSS][CODEARRAYPOS]>0) {
                        ComboBoxSmoothWithTypeAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1]->currentIndexChanged(2);
                        ComboBoxSmoothWithFreqAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][0]->currentIndexChanged(ifreq1);
                        ComboBoxSmoothWithMeasAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][0]->currentIndexChanged(0);
                        ComboBoxSmoothWithMeasAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][1]->currentIndexChanged(0);
                    } else {
                        *warningString += "FILTER: Graphic smoothing measurement '" + ParametersList->at(2*iSM+1) + "' set for " + GNSSName[iGNSS] + ", but there are no available codes to smooth with. It was skipped.\n";
                        continue;
                    }

                //set measurement
                } else {
                    if( SmoothWithOpt[1].size()!=3 || SmoothWithOpt[2].size()!=3
                         || ( !SmoothWithOpt[1].mid(0,1).contains("L",Qt::CaseInsensitive) && !SmoothWithOpt[1].mid(0,1).contains("C",Qt::CaseInsensitive) )
                         || ( !SmoothWithOpt[2].mid(0,1).contains("L",Qt::CaseInsensitive) && !SmoothWithOpt[2].mid(0,1).contains("C",Qt::CaseInsensitive) )
                         || SmoothWithOpt[1].mid(0,1) == SmoothWithOpt[2].mid(0,1) ) {
                        if (lastiSMPhase!=iSM) {
                            *warningString += "FILTER: Smoothing measurement must be a carrier phase, but pseudorange provided. Measurement '" + ParametersList->at(2*iSM+1) + "' was skipped.\n";
                            lastiSMPhase=iSM;
                        }
                        continue;
                    }
                    //get frequency
                    int iMfreq1=-1,iMfreq2=-1;
                    for (int ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                        if (SmoothWithOpt[1].mid(1,1)==FreqGNSSList[iGNSS][ifreq]) iMfreq1=ifreq;
                        if (SmoothWithOpt[2].mid(1,1)==FreqGNSSList[iGNSS][ifreq]) iMfreq2=ifreq;
                    }
                    //continue if freq & meas are not accordant
                    if (iMfreq1<0) {
                        *warningString += "FILTER: Frequency '" + SmoothWithOpt[1].mid(1,1) + "' in smoothing measurement '" + ParametersList->at(2*iSM+1) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if (iMfreq2<0) {
                        *warningString += "FILTER: Frequency '" + SmoothWithOpt[2].mid(1,1) + "' in smoothing measurement '" + ParametersList->at(2*iSM+1) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if (iMfreq1!=ifreq1) {
                        if (lastiSMPhase!=iSM) {
                            *warningString += "FILTER: Frequency '" + SmoothWithOpt[1].mid(1,1) + "' in smoothing measurement '" + ParametersList->at(2*iSM+1) + "' does not match with the graphic frequency '" + SmoothWithOpt[0].mid(1,1) + "'. It was skipped.\n";
                            lastiSMPhase=iSM;
                        }
                        continue;
                    } else if (iMfreq2!=ifreq1) {
                        if (lastiSMPhase!=iSM) {
                            *warningString += "FILTER: Frequency '" + SmoothWithOpt[2].mid(1,1) + "' in smoothing measurement '" + ParametersList->at(2*iSM+1) + "' does not match with the graphic frequency '" + SmoothWithOpt[0].mid(1,1) + "'. It was skipped.\n";
                             lastiSMPhase=iSM;
                        }
                        continue;
                    }
                    //get measurement
                    int imeas1=-1,imeas2=-1;
                    for (imeas1=0;imeas1<MeasGNSSOrder[iGNSS][iMfreq1].size();imeas1++){
                        if (SmoothWithOpt[1].toUpper().mid(2,1)==MeasGNSSOrder[iGNSS][iMfreq1].mid(imeas1,1)){
                            break;
                        }
                    }
                    for (imeas2=0;imeas2<MeasGNSSOrder[iGNSS][iMfreq2].size();imeas2++){
                        if (SmoothWithOpt[2].toUpper().mid(2,1)==MeasGNSSOrder[iGNSS][iMfreq2].mid(imeas2,1)){
                            break;
                        }
                    }
                    //reset order if first meas is code
                    if ( SmoothWithOpt[1].mid(0,1).contains("C",Qt::CaseInsensitive) ){
                        int measBuff=imeas1;
                        imeas1=imeas2;
                        imeas2=measBuff;
                    }
                    if (imeas1>=MeasCodeGNSSOrder[iGNSS][iMfreq1].size() && imeas2>=MeasCodeGNSSOrder[iGNSS][iMfreq2].size()) {
                        *warningString += "FILTER: Smoothing measurements '" + SmoothWithOpt[1] + "' and '" + SmoothWithOpt[2] + "' in argument '" + ParametersList->at(2*iSM+1) + "' do not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if (imeas1>=MeasCodeGNSSOrder[iGNSS][iMfreq1].size() ) {
                        *warningString += "FILTER: Smoothing measurement '" + SmoothWithOpt[1] + "' in argument '" + ParametersList->at(2*iSM+1) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if (imeas2>=MeasCodeGNSSOrder[iGNSS][iMfreq2].size() ) {
                        *warningString += "FILTER: Smoothing measurement '" + SmoothWithOpt[2] + "' in argument '" + ParametersList->at(2*iSM+1) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    }
                    if (GNSSMeasCMD[iGNSS][CODEARRAYPOS]>0) {
                        ComboBoxSmoothWithTypeAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1]->currentIndexChanged(2);
                        ComboBoxSmoothWithFreqAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][0]->currentIndexChanged(ifreq1);
                        ComboBoxSmoothWithMeasAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][0]->currentIndexChanged(imeas2+1);
                        ComboBoxSmoothWithMeasAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][1]->currentIndexChanged(imeas1+1);
                    } else {
                        *warningString += "FILTER: Graphic smoothing measurement '" + ParametersList->at(2*iSM+1) + "' set for " + GNSSName[iGNSS] + ", but there are no available codes to smooth with. It was skipped.\n";
                    }
                }

            //dual code frequency for IF and DF
            } else if ( SmoothWithOpt[0].mid(0,2).contains("IF",Qt::CaseInsensitive) || SmoothWithOpt[0].mid(0,2).contains("DF",Qt::CaseInsensitive)
                      || SmoothWithOpt[0].mid(0,2).contains("LC",Qt::CaseInsensitive)) {
                if ( SmoothWithOpt[0].size()!=4 ) continue;
                int SMType=3;
                QString measTypeText="ionosphere-free";
                if (SmoothWithOpt[0].contains("DF",Qt::CaseInsensitive)) {
                    measTypeText="divergence-free";
                    SMType=4;
                }
                if (nSMOpt>=2) {
                    if (SmoothWithOpt[1].contains("code",Qt::CaseInsensitive) || SmoothWithOpt[1].contains("coph",Qt::CaseInsensitive) || SmoothWithOpt[1].contains("phco",Qt::CaseInsensitive) ||
                      ParametersList->at(2*iSM+1).toUpper().contains(QRegularExpression("-C[1-9][A-Z]-C[1-9][A-Z]$")) ||
                      ParametersList->at(2*iSM+1).toUpper().contains(QRegularExpression("-C[1-9][A-Z]-L[1-9][A-Z]$")) ||
                      ParametersList->at(2*iSM+1).toUpper().contains(QRegularExpression("-L[1-9][A-Z]-C[1-9][A-Z]$")) ) {
                        if (lastiSMPhase!=iSM) {
                            *warningString += "FILTER: Smoothing measurement '" + ParametersList->at(2*iSM+1) + "' cannot contain code measurements. It was skipped.\n";
                            lastiSMPhase=iSM;
                        }
                        continue;
                    }
                }
                //get frequency set
                int ifreq1=-1,ifreq2=-1;
                for (int ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                    if (SmoothWithOpt[0].mid(2,1)==FreqGNSSList[iGNSS][ifreq]) ifreq1=ifreq;
                    if (SmoothWithOpt[0].mid(3,1)==FreqGNSSList[iGNSS][ifreq]) ifreq2=ifreq;
                }
                if (ifreq1<0 ) {
                    *warningString += "FILTER: Frequency '" + SmoothWithOpt[0].mid(2,1) + "' in smoothing measurement '" + SmoothWithOpt[0] + "' in argument '" + ParametersList->at(2*iSM+1) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                    continue;
                } else if (ifreq2<0 ) {
                    *warningString += "FILTER: Frequency '" + SmoothWithOpt[0].mid(3,1) + "' in smoothing measurement '" + SmoothWithOpt[0] + "' in argument '" + ParametersList->at(2*iSM+1) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                    continue;
                } else if ( ifreq1==ifreq2) {
                    if (lastiSMPhase!=iSM) {
                        *warningString += "FILTER: Frequencies '" + SmoothWithOpt[0].mid(2,1) + "' and '" + SmoothWithOpt[0].mid(3,1) + "' in smoothing measurements in argument '" + ParametersList->at(2*iSM+1) + "' are repeated. It was skipped.\n";
                        lastiSMPhase=iSM;
                    }
                    continue;
                }
                //set frequency
                if (nSMOpt!=3){
                    //set smoothed-with type
                    ComboBoxSmoothWithTypeAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1]->currentIndexChanged(SMType);
                    smoothWithFreqNoSame=0;
                    if (GNSSMeasCMD[iGNSS][CODEARRAYPOS]>0) {
                        ComboBoxSmoothWithFreqAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][0]->currentIndexChanged(ifreq1);
                        ComboBoxSmoothWithFreqAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][1]->currentIndexChanged(ifreq2);
                        ComboBoxSmoothWithMeasAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][1]->currentIndexChanged(0);
                        ComboBoxSmoothWithMeasAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][2]->currentIndexChanged(0);
                    } else {
                        *warningString += "FILTER: " + measTypeText + " smoothing measurement '" + ParametersList->at(2*iSM+1) + "' set for " + GNSSName[iGNSS] + ", but there are no available codes to smooth with. It was skipped.\n";
                    }
                    smoothWithFreqNoSame=1;

                //set measurement
                } else {
                    if( SmoothWithOpt[1].size()!=3 || SmoothWithOpt[2].size()!=3 ) continue;
                    //get frequency
                    int iMfreq1=-1,iMfreq2=-1;
                    for (int ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                        if (SmoothWithOpt[1].mid(1,1)==FreqGNSSList[iGNSS][ifreq]) iMfreq1=ifreq;
                        if (SmoothWithOpt[2].mid(1,1)==FreqGNSSList[iGNSS][ifreq]) iMfreq2=ifreq;
                    }
                    if (iMfreq1<0) {
                        *warningString += "FILTER: Frequency '" + SmoothWithOpt[1].mid(1,1) + "' in smoothing measurement '" + ParametersList->at(2*iSM+1) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if (iMfreq2<0) {
                        *warningString += "FILTER: Frequency '" + SmoothWithOpt[2].mid(1,1) + "' in smoothing measurement '" + ParametersList->at(2*iSM+1) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if (iMfreq1==iMfreq2) {
                        if (lastiSMPhase!=iSM) {
                            *warningString += "FILTER: Frequencies in smoothing measurement '" + ParametersList->at(2*iSM+1) + "' are repeated. It was skipped.\n";
                            lastiSMPhase=iSM;
                        }
                        continue;
                    }
                    //continue if freq & meas are not accordant
                    if ( !(iMfreq1==ifreq1 && iMfreq2==ifreq2) && !(iMfreq1==ifreq2 && iMfreq2==ifreq1) ) {
                        *warningString += "FILTER: Frequencies in smoothing measurements '" + ParametersList->at(2*iSM+1) + "' do not match with frequencies in '" + SmoothWithOpt[0] + "'. It was skipped.\n";
                        continue;
                    }
                    //get measurement
                    int imeas1=-1,imeas2=-1;
                    for (imeas1=0;imeas1<MeasGNSSOrder[iGNSS][iMfreq1].size();imeas1++){
                        if (SmoothWithOpt[1].toUpper().mid(2,1)==MeasGNSSOrder[iGNSS][iMfreq1].mid(imeas1,1)){
                            break;
                        }
                    }
                    for (imeas2=0;imeas2<MeasGNSSOrder[iGNSS][iMfreq2].size();imeas2++){
                        if (SmoothWithOpt[2].toUpper().mid(2,1)==MeasGNSSOrder[iGNSS][iMfreq2].mid(imeas2,1)){
                            break;
                        }
                    }
                    if (imeas1>=MeasCodeGNSSOrder[iGNSS][iMfreq1].size() && imeas2>=MeasCodeGNSSOrder[iGNSS][iMfreq2].size()) {
                        *warningString += "FILTER: Measurements '" + SmoothWithOpt[1] + "' and '" + SmoothWithOpt[2] + "' in argument '" + ParametersList->at(2*iSM+1) + "' do not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if (imeas1>=MeasCodeGNSSOrder[iGNSS][iMfreq1].size() ) {
                        *warningString += "FILTER: Measurement '" + SmoothWithOpt[1] + "' in argument '" + ParametersList->at(2*iSM+1) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if (imeas2>=MeasCodeGNSSOrder[iGNSS][iMfreq2].size() ) {
                        *warningString += "FILTER: Measurement '" + SmoothWithOpt[2] + "' in argument '" + ParametersList->at(2*iSM+1) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    }
                    //align freq and meas
                    if ( iMfreq1==ifreq2 && iMfreq2==ifreq1 ){
                        int measBuff=imeas1;
                        iMfreq1=ifreq1;
                        iMfreq2=ifreq2;
                        imeas1=imeas2;
                        imeas2=measBuff;
                    }
                    //set smoothed-with type
                    if (GNSSMeasCMD[iGNSS][CODEARRAYPOS]>0) {
                        ComboBoxSmoothWithTypeAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1]->currentIndexChanged(SMType);
                        smoothWithFreqNoSame=0;
                        ComboBoxSmoothWithFreqAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][0]->currentIndexChanged(ifreq1);
                        ComboBoxSmoothWithFreqAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][1]->currentIndexChanged(ifreq2);
                        ComboBoxSmoothWithMeasAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][1]->currentIndexChanged(imeas1+1);
                        ComboBoxSmoothWithMeasAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][2]->currentIndexChanged(imeas2+1);
                        smoothWithFreqNoSame=1;
                    } else {
                        *warningString += "FILTER: " + measTypeText + " smoothing measurement '" + ParametersList->at(2*iSM+1) + "' set for " + GNSSName[iGNSS] + ", but there are no available codes to smooth with. It was skipped.\n";
                    }
                }

            // SF: single phase measurement
            } else if (SmoothWithOpt[0].mid(0,1).contains("L",Qt::CaseInsensitive)) {
                if (SmoothWithOpt[0].size()!=3) continue;
                int ifreq;
                for (ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                    if (SmoothWithOpt[0].mid(1,1)==FreqGNSSList[iGNSS][ifreq]) break;
                }
                if (ifreq>=nFreqGNSS[iGNSS]) {
                    *warningString += "FILTER: Frequency '" + SmoothWithOpt[0].mid(1,1) + "' in smoothing measurement '" + ParametersList->at(2*iSM+1) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                    continue;
                }
                int imeas;
                for (imeas=0;imeas<MeasGNSSOrder[iGNSS][ifreq].size();imeas++){
                    if (SmoothWithOpt[0].toUpper().mid(2,1)==MeasGNSSOrder[iGNSS][ifreq].mid(imeas,1)){
                        if (GNSSMeasCMD[iGNSS][CODEARRAYPOS]>0) {
                            ComboBoxSmoothWithTypeAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1]->currentIndexChanged(1);
                            ComboBoxSmoothWithFreqAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][0]->currentIndexChanged(ifreq);
                            ComboBoxSmoothWithMeasAll[iGNSS][GNSSMeasCMD[iGNSS][CODEARRAYPOS]-1][1]->currentIndexChanged(imeas+1);
                            break;
                        } else {
                            *warningString += "FILTER: Single frequency smoothing measurement '" + ParametersList->at(2*iSM+1) + "' set for " + GNSSName[iGNSS] + ", but there are no available codes to smooth with. It was skipped.\n";
                        }

                    }
                }
                if (imeas>=MeasGNSSOrder[iGNSS][ifreq].size()) {
                    *warningString += "FILTER: Invalid smoothing measurement '" + SmoothWithOpt[0] + "' in argument '" + ParametersList->at(2*iSM+1) + "' for " + GNSSName[iGNSS] + " constellation. It was skipped.\n";
                    continue;
                }

            } else if (SmoothWithOpt[0].contains("Code",Qt::CaseInsensitive) || SmoothWithOpt[0].mid(0,1).contains("C",Qt::CaseInsensitive)
                     || SmoothWithOpt[0].contains("Coph",Qt::CaseInsensitive) || SmoothWithOpt[0].contains("phco",Qt::CaseInsensitive) ) {
                if (lastiSMPhase!=iSM) {
                    *warningString += "FILTER: Smoothing measurement must be a carrier phase type, but pseudorange provided. Measurement '" + ParametersList->at(2*iSM+1) + "' was skipped.\n";
                    lastiSMPhase=iSM;
                }
                continue;
            } else {
                if (lastiSMPhase!=iSM) {
                    *warningString += "FILTER: Invalid smoothing measurement '" + ParametersList->at(2*iSM+1) + "'. It was skipped.\n";
                    lastiSMPhase=iSM;
                }
                continue;
            }
        }
    }
}
//Load GNSS frequency and measurement options
void gLAB_GUI::readGNSSFreqMeas(QString *warningString, QStringList *ParametersList){
    int noSmoothOffset=1;
    int setSingleFreq=0, setDualFreq=0;
    int lastiPar=-1;
    int badParam=0;
    int singleFreqNonGCProvided=0,singleFreqGCProvided=0;
    if ( GNSSMeasCMDMode==MEAS_MODE_SMOOTH ) return;
    if (warningString->length()<0) *warningString=""; //only to avoid the warning of unused "warningString"
    if (ui->radioButtonSmoothing->isChecked()) noSmoothOffset=0;
    //Look for carrier phase measurements
    for (int iPar=0; iPar<ParametersList->count(); iPar++){
        if (ParametersList->at(iPar).toUpper().contains(QRegularExpression("(-LC[1-9][1-9]|PHASE|COPH|PHCO|-L[1-9][A-Z])"))) {
            if (!ui->radioButtonSelectionGraphic->isChecked()) {
                this->on_radioButtonSelectionPseudorangeCarrierPhase_clicked();
                break;
            }
        }
    }
    for (int iPar=0; iPar<ParametersList->count(); iPar++){
        QStringList FreqMeasOpt=ParametersList->at(iPar).split("-", QString::SkipEmptyParts);
        int nOpt=FreqMeasOpt.count();
        badParam=this->checkUserInputFilterMeasurement(warningString,ParametersList->at(iPar),MeasTargetFilter);
        if (badParam) continue;
        //ignore unselect option
        if (ParametersList->at(iPar).mid(0,1)=="-") {
            *warningString += "Arguments starting with a '-' are ignored in the GUI. Parameter '" + ParametersList->at(iPar) + "' was skipped.\n";
            continue;
        }
        //loop constellation
        for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++){

            if ( ( FreqMeasOpt[0].contains(indentifierGNSS[iGNSS],Qt::CaseInsensitive)==false && FreqMeasOpt[0]!="0" ) || nOpt<2) continue;
            if ( FreqMeasOpt[1].contains("auto",Qt::CaseInsensitive)) {
                //Nothing to set, as it is all automatic (default)
            //dual code frequency
            } else if (FreqMeasOpt[1].contains("PC",Qt::CaseInsensitive) || FreqMeasOpt[1].contains("LC",Qt::CaseInsensitive)) {
                int measType=0; //0 -> Code 1 -> Phase

                if (FreqMeasOpt[1].contains("LC",Qt::CaseInsensitive)) measType=1;

                QString dualFreqStr=FreqMeasOpt[1].toUpper();
                if ( GNSSFreqCMDMode!=0 && GNSSFreqCMDMode!=MEAS_MODE_DUAL ) {
                    if (setSingleFreq==1) {
                        if (lastiPar!=iPar) {
                            *warningString += "FILTER: The GUI does not support loading both single and dual frequency combinations at the same time (command line does). Measurement ' " + ParametersList->at(iPar) + "' was skipped.\n";
                            lastiPar=iPar;
                        }
                    }
                    continue;
                } else if (ui->radioButtonSelectionGraphic->isChecked() || singleFreqGCProvided==1) {
                    if (lastiPar!=iPar) {
                        *warningString += "FILTER: The GUI does not support loading both graphical and non-graphical combinations at the same time (command line does). Measurement ' " + ParametersList->at(iPar) + "' was skipped.\n";
                        lastiPar=iPar;
                    }
                    continue;
                }
                if(FreqMeasOpt[1].size()!=4) continue;
                if (GNSSMeasCMD[iGNSS][measType]>2) {
                    *warningString += "FILTER: Maximum number of measurements for " + GNSSName[iGNSS] + " in the filter is 3. Argument '" + ParametersList->at(iPar) + "' was skipped for " + GNSSName[iGNSS] + " as limit has been surpassed.\n";
                    continue;
                }
                //reset frequency order
                if (FreqMeasOpt[1][2]>FreqMeasOpt[1][3]){
                    dualFreqStr = FreqMeasOpt[1].mid(0,2).toUpper() + FreqMeasOpt[1].mid(3,1) + FreqMeasOpt[1].mid(2,1);
                }
                //get frequency conbination
                int iDual=-1;
                if (measType==0) {
                    for (iDual=0; iDual<nDualFreqGNSS[iGNSS]; iDual++){
                        if (dualFreqStr==FreqCodeDualGNSSList[iGNSS][iDual]) break;
                    }
                } else {
                    for (iDual=0; iDual<nDualFreqGNSS[iGNSS]; iDual++){
                        if (dualFreqStr==FreqPhaseDualGNSSList[iGNSS][iDual]) break;
                    }
                }
                if (iDual>=nDualFreqGNSS[iGNSS]) {
                    *warningString += "FILTER: Invalid frequencies in argument '" + ParametersList->at(iPar) + "' for " + GNSSName[iGNSS] + " constellation. It was skipped.\n";
                    continue;
                }
                //set frequency
                if (nOpt==2) {
                    if (GNSSFreqCMDMode==0) {
                        GNSSFreqCMDMode=MEAS_MODE_DUAL;
                        this->on_radioButtonDualFreq_clicked();
                        setDualFreq=1;
                    }
                    if ( FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][measType]]->isHidden() || GNSSMeasCMD[iGNSS][measType]>=GNSSMeasCMD[iGNSS][1-measType] ) {
                        setGNSSMeasurementFreqAll(iGNSS,GNSSMeasCMD[iGNSS][measType],0);
                        FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][measType]]->setHidden(false);
                    } else {
                        setGNSSMeasurementFreqCP(iGNSS,GNSSMeasCMD[iGNSS][measType],measType,iDual);
                    }
                    ComboBoxGNSSFreq[iGNSS][GNSSMeasCMD[iGNSS][measType]][measType]->currentIndexChanged(iDual+noSmoothOffset);
                    GNSSMeasInAll[iGNSS][GNSSMeasCMD[iGNSS][measType]][measType]=ParametersList->at(iPar);
                    GNSSMeasCMD[iGNSS][measType]++;

                //set measurement
                } else if (nOpt==4) {
                    if( FreqMeasOpt[2].size()!=3 || FreqMeasOpt[3].size()!=3 ) continue;
                    //get frequency
                    int ifreq1=-1,ifreq2=-1;
                    for (int ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                        if (FreqMeasOpt[2].mid(1,1)==FreqGNSSList[iGNSS][ifreq]) ifreq1=ifreq;
                        if (FreqMeasOpt[3].mid(1,1)==FreqGNSSList[iGNSS][ifreq]) ifreq2=ifreq;
                    }
                    if (ifreq1<0 ) {
                        *warningString += "FILTER: Frequency '" + FreqMeasOpt[2].mid(1,1) + "' in measurement '" + FreqMeasOpt[2] + "' in argument '" + ParametersList->at(iPar) + "' for the filter does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if (ifreq2<0 ) {
                        *warningString += "FILTER: Frequency '" + FreqMeasOpt[3].mid(1,1) + "' in measurement '" + FreqMeasOpt[3] + "' in argument '" + ParametersList->at(iPar) + "' for the filter does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if ( ifreq1==ifreq2) {
                        if (lastiPar!=iPar) {
                            *warningString += "FILTER: Frequencies '" + FreqMeasOpt[2].mid(1,1) + "' and '" + FreqMeasOpt[3].mid(1,1) + "' in measurements in argument '" + ParametersList->at(iPar) + "' for the filter are repeated. It was skipped.\n";
                            lastiPar=iPar;
                        }
                        continue;
                    }
                    //get measurement
                    int imeas1=-1,imeas2=-1;
                    for (imeas1=0;imeas1<MeasCodeGNSSOrder[iGNSS][ifreq1].size();imeas1++){
                        if (FreqMeasOpt[2].toUpper().mid(2,1)==MeasCodeGNSSOrder[iGNSS][ifreq1].mid(imeas1,1)){
                            break;
                        }
                    }
                    for (imeas2=0;imeas2<MeasCodeGNSSOrder[iGNSS][ifreq2].size();imeas2++){
                        if (FreqMeasOpt[3].toUpper().mid(2,1)==MeasCodeGNSSOrder[iGNSS][ifreq2].mid(imeas2,1)){
                            break;
                        }
                    }
                    if (imeas1>=MeasCodeGNSSOrder[iGNSS][ifreq1].size() && imeas2>=MeasCodeGNSSOrder[iGNSS][ifreq2].size()) {
                        *warningString += "FILTER: Measurements '" + FreqMeasOpt[2] + "' and '" + FreqMeasOpt[3] + "' in argument '" + ParametersList->at(iPar) + "' for the filter do not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if (imeas1>=MeasCodeGNSSOrder[iGNSS][ifreq1].size() ) {
                        *warningString += "FILTER: Measurement '" + FreqMeasOpt[2] + "' in argument '" + ParametersList->at(iPar) + "' for the filter does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if (imeas2>=MeasCodeGNSSOrder[iGNSS][ifreq2].size() ) {
                        *warningString += "FILTER: Measurement '" + FreqMeasOpt[3] + "' in argument '" + ParametersList->at(iPar) + "' for the filter does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    }


                    //reset order
                    if ( ifreq1 > ifreq2 ){
                        int measBuff=imeas1;
                        imeas1=imeas2;
                        imeas2=measBuff;
                    }
                    if (GNSSFreqCMDMode==0) {
                        GNSSFreqCMDMode=MEAS_MODE_DUAL;
                        this->on_radioButtonDualFreq_clicked();
                        setDualFreq=1;
                    }
                    if ( FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][measType]]->isHidden() || GNSSMeasCMD[iGNSS][measType]>=GNSSMeasCMD[iGNSS][1-measType] ) {
                        setGNSSMeasurementFreqAll(iGNSS,GNSSMeasCMD[iGNSS][measType],0);
                        FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][measType]]->setHidden(false);

                    } else {
                        setGNSSMeasurementFreqCP(iGNSS,GNSSMeasCMD[iGNSS][measType],measType,iDual);
                    }
                    ComboBoxGNSSFreq[iGNSS][GNSSMeasCMD[iGNSS][measType]][measType]->currentIndexChanged(iDual+noSmoothOffset);
                    ComboBoxGNSSMeas[iGNSS][GNSSMeasCMD[iGNSS][measType]][measType][0]->currentIndexChanged(imeas1+noSmoothOffset);
                    ComboBoxGNSSMeas[iGNSS][GNSSMeasCMD[iGNSS][measType]][measType][1]->currentIndexChanged(imeas2+noSmoothOffset);
                    GNSSMeasInAll[iGNSS][GNSSMeasCMD[iGNSS][measType]][measType]=ParametersList->at(iPar);
                    GNSSMeasCMD[iGNSS][measType]++;
                }
            //dual code or phase (IF) frequency
            } else if ( FreqMeasOpt[1].contains("IF",Qt::CaseInsensitive) && FreqMeasOpt[1].size()==4 ) {
                int measType=0; //0 -> Code 1 -> Phase
                int BothTypes=0;
                QString dualFreqStr=FreqMeasOpt[1].toUpper();
                if ( GNSSFreqCMDMode!=0 && GNSSFreqCMDMode!=MEAS_MODE_DUAL ) {
                    if (setSingleFreq==1) {
                        if (lastiPar!=iPar) {
                            *warningString += "FILTER: The GUI does not support loading both single and dual frequency combinations at the same time (command line does). Measurement '" + ParametersList->at(iPar) + "' was skipped.\n";
                            lastiPar=iPar;
                        }
                    }
                    continue;
                } else if (ui->radioButtonSelectionGraphic->isChecked() || singleFreqGCProvided==1) {
                    if (lastiPar!=iPar) {
                        *warningString += "FILTER: The GUI does not support loading both graphical and non-graphical combinations at the same time (command line does). Measurement ' " + ParametersList->at(iPar) + "' was skipped.\n";
                        lastiPar=iPar;
                    }
                    continue;
                }
                if(FreqMeasOpt[1].size()!=4) continue;
                //reset frequency order
                if (FreqMeasOpt[1][2]>FreqMeasOpt[1][3]){
                    dualFreqStr = FreqMeasOpt[1].mid(0,2).toUpper() + FreqMeasOpt[1].mid(3,1) + FreqMeasOpt[1].mid(2,1);
                }
                //get frequency conbination
                int iDual=-1;
                for (iDual=0; iDual<nDualFreqGNSS[iGNSS]; iDual++){
                    if (dualFreqStr==FreqIFDualGNSSList[iGNSS][iDual]) break;
                }
                if (iDual>=nDualFreqGNSS[iGNSS])  {
                    *warningString += "FILTER: Invalid frequencies in argument '" + ParametersList->at(iPar) + "' for " + GNSSName[iGNSS] + " constellation. It was skipped.\n";
                    continue;
                }
                //Check if "code" or "phase" were provided
               if (nOpt>=2) {
                    if (ParametersList->at(iPar).toUpper().contains(QRegularExpression("-CODE$"))) {
                        measType=0;
                    } else if (ParametersList->at(iPar).toUpper().contains(QRegularExpression("-PHASE$"))) {
                        measType=1;
                    } else if (ParametersList->at(iPar).toUpper().contains(QRegularExpression("-CODEPHASE$"))
                             || ParametersList->at(iPar).toUpper().contains(QRegularExpression("-PHASECODE$"))
                               || ParametersList->at(iPar).toUpper().contains(QRegularExpression("-COPH$"))
                               || ParametersList->at(iPar).toUpper().contains(QRegularExpression("-PHCO$")) ) {
                        BothTypes=1;
                    } else if (ParametersList->at(iPar).toUpper().contains(QRegularExpression("-L[1-9][A-Z]-L[1-9]"+regExpValidAttributes+"$"))) {
                        measType=1;
                    } else if (ParametersList->at(iPar).toUpper().contains(QRegularExpression("-C[1-9][A-Z]-C[1-9]"+regExpValidAttributes+"$"))) {
                        measType=0;
                    } else {
                        if (lastiPar!=iPar) {
                            *warningString += "FILTER: Invalid measurement '" + ParametersList->at(iPar) + "'. It was skipped.\n";
                            lastiPar=iPar;
                        }
                        continue;
                    }
                } else {
                    if (lastiPar!=iPar) {
                        *warningString += "FILTER: Invalid measurement '" + ParametersList->at(iPar) + "'. It was skipped.\n";
                        lastiPar=iPar;
                    }
                    continue;
                }
                if (BothTypes==1) {
                    if (GNSSMeasCMD[iGNSS][CODEARRAYPOS]>GNSSMeasCMD[iGNSS][PHASEARRAYPOS]) {
                        GNSSMeasCMD[iGNSS][PHASEARRAYPOS]=GNSSMeasCMD[iGNSS][CODEARRAYPOS];
                    } else if (GNSSMeasCMD[iGNSS][PHASEARRAYPOS]>GNSSMeasCMD[iGNSS][CODEARRAYPOS]) {
                        GNSSMeasCMD[iGNSS][CODEARRAYPOS]=GNSSMeasCMD[iGNSS][PHASEARRAYPOS];
                    }
                    if (GNSSMeasCMD[iGNSS][CODEARRAYPOS]>2) {
                        *warningString += "FILTER: Maximum number of measurements for " + GNSSName[iGNSS] + " in the filter is 3. Argument '" + ParametersList->at(iPar) + "' was skipped for " + GNSSName[iGNSS] + " as limit has been surpassed.\n";
                        continue;
                    }
                    if (GNSSMeasCMD[iGNSS][PHASEARRAYPOS]>2) {
                        *warningString += "FILTER: Maximum number of measurements for " + GNSSName[iGNSS] + " in the filter is 3. Argument '" + ParametersList->at(iPar) + "' was skipped for " + GNSSName[iGNSS] + " as limit has been surpassed.\n";
                        continue;
                    }
                } else {
                    if (GNSSMeasCMD[iGNSS][measType]>2) {
                        *warningString += "FILTER: Maximum number of measurements for " + GNSSName[iGNSS] + " in the filter is 3. Argument '" + ParametersList->at(iPar) + "' was skipped for " + GNSSName[iGNSS] + " as limit has been surpassed.\n";
                        continue;
                    }
                }
                for(int iType=0;iType<=BothTypes;iType++) {
                    if (BothTypes==1) {
                        measType=iType;
                    }
                    //set frequency
                    if (nOpt==3){
                        if (GNSSFreqCMDMode==0) {
                            GNSSFreqCMDMode=MEAS_MODE_DUAL;
                            this->on_radioButtonDualFreq_clicked();
                            setDualFreq=1;
                        }
                        if ( FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][measType]]->isHidden() || GNSSMeasCMD[iGNSS][measType]>=GNSSMeasCMD[iGNSS][1-measType] ) {
                            setGNSSMeasurementFreqAll(iGNSS,GNSSMeasCMD[iGNSS][measType],0);
                            FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][measType]]->setHidden(false);
                        }
                        else setGNSSMeasurementFreqCP(iGNSS,GNSSMeasCMD[iGNSS][measType],measType,iDual);
                        ComboBoxGNSSFreq[iGNSS][GNSSMeasCMD[iGNSS][measType]][measType]->currentIndexChanged(iDual+noSmoothOffset);
                        GNSSMeasInAll[iGNSS][GNSSMeasCMD[iGNSS][measType]][measType]=ParametersList->at(iPar);
                        GNSSMeasCMD[iGNSS][measType]++;

                    //set measurement
                    } else if (nOpt==4){
                        if( FreqMeasOpt[2].size()!=3 || FreqMeasOpt[3].size()!=3 ) continue;
                        //get frequency
                        int ifreq1=-1,ifreq2=-1;
                        for (int ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                            if (FreqMeasOpt[2].mid(1,1)==FreqGNSSList[iGNSS][ifreq]) ifreq1=ifreq;
                            if (FreqMeasOpt[3].mid(1,1)==FreqGNSSList[iGNSS][ifreq]) ifreq2=ifreq;
                        }
                        if (ifreq1<0 ) {
                            *warningString += "FILTER: Frequency '" + FreqMeasOpt[2].mid(1,1) + "' in measurement '" + FreqMeasOpt[2] + "' in argument '" + ParametersList->at(iPar) + "' for the filter does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                            continue;
                        } else if (ifreq2<0 ) {
                            *warningString += "FILTER: Frequency '" + FreqMeasOpt[3].mid(1,1) + "' in measurement '" + FreqMeasOpt[3] + "' in argument '" + ParametersList->at(iPar) + "' for the filter does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                            continue;
                        } else if ( ifreq1==ifreq2) {
                            if (lastiPar!=iPar) {
                                *warningString += "FILTER: Frequencies '" + FreqMeasOpt[2].mid(1,1) + "' and '" + FreqMeasOpt[3].mid(1,1) + "' in measurements in argument '" + ParametersList->at(iPar) + "' for the filter are repeated. It was skipped.\n";
                                lastiPar=iPar;
                            }
                            continue;
                        }
                        //get measurement
                        int imeas1=-1,imeas2=-1;
                        for (imeas1=0;imeas1<MeasGNSSOrder[iGNSS][ifreq1].size();imeas1++){
                            if (FreqMeasOpt[2].toUpper().mid(2,1)==MeasGNSSOrder[iGNSS][ifreq1].mid(imeas1,1)){
                                break;
                            }
                        }
                        for (imeas2=0;imeas2<MeasGNSSOrder[iGNSS][ifreq2].size();imeas2++){
                            if (FreqMeasOpt[3].toUpper().mid(2,1)==MeasGNSSOrder[iGNSS][ifreq2].mid(imeas2,1)){
                                break;
                            }
                        }
                        if (imeas1>=MeasCodeGNSSOrder[iGNSS][ifreq1].size() && imeas2>=MeasCodeGNSSOrder[iGNSS][ifreq2].size()) {
                            *warningString += "FILTER: Measurements '" + FreqMeasOpt[2] + "' and '" + FreqMeasOpt[3] + "' in argument '" + ParametersList->at(iPar) + "' for the filter do not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                            continue;
                        } else if (imeas1>=MeasCodeGNSSOrder[iGNSS][ifreq1].size() ) {
                            *warningString += "FILTER: Measurement '" + FreqMeasOpt[2] + "' in argument '" + ParametersList->at(iPar) + "' for the filter does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                            continue;
                        } else if (imeas2>=MeasCodeGNSSOrder[iGNSS][ifreq2].size() ) {
                            *warningString += "FILTER: Measurement '" + FreqMeasOpt[3] + "' in argument '" + ParametersList->at(iPar) + "' for the filter does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                            continue;
                        }
                        //reset order
                        if ( ifreq1 > ifreq2 ){
                            int measBuff=imeas1;
                            imeas1=imeas2;
                            imeas2=measBuff;
                        }
                        if (GNSSFreqCMDMode==0) {
                            GNSSFreqCMDMode=MEAS_MODE_DUAL;
                            this->on_radioButtonDualFreq_clicked();
                            setDualFreq=1;
                        }
                        if ( FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][measType]]->isHidden() || GNSSMeasCMD[iGNSS][measType]>=GNSSMeasCMD[iGNSS][1-measType] ) {
                            setGNSSMeasurementFreqAll(iGNSS,GNSSMeasCMD[iGNSS][measType],0);
                            FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][measType]]->setHidden(false);

                        } else {
                            setGNSSMeasurementFreqCP(iGNSS,GNSSMeasCMD[iGNSS][measType],measType,iDual);
                        }
                        ComboBoxGNSSFreq[iGNSS][GNSSMeasCMD[iGNSS][measType]][measType]->currentIndexChanged(iDual+noSmoothOffset);
                        ComboBoxGNSSMeas[iGNSS][GNSSMeasCMD[iGNSS][measType]][measType][COMBMEAS1ARRAYPOS]->currentIndexChanged(imeas1+noSmoothOffset);
                        ComboBoxGNSSMeas[iGNSS][GNSSMeasCMD[iGNSS][measType]][measType][COMBMEAS2ARRAYPOS]->currentIndexChanged(imeas2+noSmoothOffset);
                        GNSSMeasInAll[iGNSS][GNSSMeasCMD[iGNSS][measType]][measType]=ParametersList->at(iPar);
                        GNSSMeasCMD[iGNSS][measType]++;
                    }
                }

            //single code frequency
            } else if (FreqMeasOpt[1].contains("Code",Qt::CaseInsensitive) || FreqMeasOpt[1].contains("Phase",Qt::CaseInsensitive)
                       || FreqMeasOpt[1].contains("CoPh",Qt::CaseInsensitive) || FreqMeasOpt[1].contains("PhCo",Qt::CaseInsensitive)) {

                int measType=0; //0 -> Code 1 -> Phase
                int BothTypes=0;

                singleFreqNonGCProvided=1;

                if (nOpt>=3) {
                    if (ParametersList->at(iPar).toUpper().contains(QRegularExpression("-CODE-"))) {
                        measType=0;
                    } else if (ParametersList->at(iPar).toUpper().contains(QRegularExpression("-PHASE-"))) {
                        measType=1;
                    } else if (ParametersList->at(iPar).toUpper().contains(QRegularExpression("-CODEPHASE$"))
                             || ParametersList->at(iPar).toUpper().contains(QRegularExpression("-PHASECODE$"))
                               || ParametersList->at(iPar).toUpper().contains(QRegularExpression("-COPH$"))
                               || ParametersList->at(iPar).toUpper().contains(QRegularExpression("-PHCO$")) ) {
                        BothTypes=1;
                    } else {
                        if (lastiPar!=iPar) {
                            *warningString += "FILTER: Invalid measurement '" + ParametersList->at(iPar) + "'. It was skipped.\n";
                            lastiPar=iPar;
                        }
                        continue;
                    }
                } else {
                    if (lastiPar!=iPar) {
                        *warningString += "FILTER: Invalid measurement '" + ParametersList->at(iPar) + "'. It was skipped.\n";
                        lastiPar=iPar;
                    }
                    continue;
                }

                if ( GNSSFreqCMDMode!=0 && GNSSFreqCMDMode!=MEAS_MODE_SINGLE ) {
                    if (setDualFreq==1) {
                        if (lastiPar!=iPar) {
                            *warningString += "FILTER: The GUI does not support loading both single and dual frequency combinations at the same time (command line does). Measurement ' " + ParametersList->at(iPar) + "' was skipped.\n";
                            lastiPar=iPar;
                        }
                    }
                    continue;
                } else if (ui->radioButtonSelectionGraphic->isChecked() || singleFreqGCProvided==1) {
                    if (lastiPar!=iPar) {
                        *warningString += "FILTER: The GUI does not support loading both graphical and non-graphical combinations at the same time (command line does). Measurement ' " + ParametersList->at(iPar) + "' was skipped.\n";
                        lastiPar=iPar;
                    }
                    continue;
                }
                if (nOpt<3) continue;
                if (BothTypes==1) {
                    if (GNSSMeasCMD[iGNSS][CODEARRAYPOS]>GNSSMeasCMD[iGNSS][PHASEARRAYPOS]) {
                        GNSSMeasCMD[iGNSS][PHASEARRAYPOS]=GNSSMeasCMD[iGNSS][CODEARRAYPOS];
                    } else if (GNSSMeasCMD[iGNSS][PHASEARRAYPOS]>GNSSMeasCMD[iGNSS][CODEARRAYPOS]) {
                        GNSSMeasCMD[iGNSS][CODEARRAYPOS]=GNSSMeasCMD[iGNSS][PHASEARRAYPOS];
                    }
                    if (GNSSMeasCMD[iGNSS][CODEARRAYPOS]>2) {
                        *warningString += "FILTER: Maximum number of measurements for " + GNSSName[iGNSS] + " in the filter is 3. Argument '" + ParametersList->at(iPar) + "' was skipped for " + GNSSName[iGNSS] + " as limit has been surpassed.\n";
                        continue;
                    }
                    if (GNSSMeasCMD[iGNSS][PHASEARRAYPOS]>2) {
                        *warningString += "FILTER: Maximum number of measurements for " + GNSSName[iGNSS] + " in the filter is 3. Argument '" + ParametersList->at(iPar) + "' was skipped for " + GNSSName[iGNSS] + " as limit has been surpassed.\n";
                        continue;
                    }
                } else {
                    if (GNSSMeasCMD[iGNSS][measType]>2) {
                        *warningString += "FILTER: Maximum number of measurements for " + GNSSName[iGNSS] + " in the filter is 3. Argument '" + ParametersList->at(iPar) + "' was skipped for " + GNSSName[iGNSS] + " as limit has been surpassed.\n";
                        continue;
                    }
                }
                for(int iType=0;iType<=BothTypes;iType++) {
                    if (BothTypes==1) {
                        measType=iType;
                    }
                    int ifreq=-1;
                    for (ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                        if (FreqMeasOpt[2]==FreqGNSSList[iGNSS][ifreq]) break;
                    }
                    if (ifreq>=nFreqGNSS[iGNSS]) {
                        *warningString += "FILTER: Invalid frequency in argument '" + ParametersList->at(iPar) + "' for " + GNSSName[iGNSS] + " constellation. It was skipped.\n";
                        continue;
                    }
                    if (GNSSFreqCMDMode==0) {
                        GNSSFreqCMDMode=MEAS_MODE_SINGLE;
                        this->on_radioButtonSingleFreq_clicked();
                        setSingleFreq=1;
                    }
                    if ( FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][measType]]->isHidden() || GNSSMeasCMD[iGNSS][measType]>=GNSSMeasCMD[iGNSS][1-measType] ) {
                        setGNSSMeasurementFreqAll(iGNSS,GNSSMeasCMD[iGNSS][measType],0);
                        FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][measType]]->setHidden(false);

                    } else {
                        setGNSSMeasurementFreqCP(iGNSS,GNSSMeasCMD[iGNSS][measType],measType,ifreq);
                    }
                    ComboBoxGNSSFreq[iGNSS][GNSSMeasCMD[iGNSS][measType]][measType]->currentIndexChanged(ifreq+noSmoothOffset);
                    GNSSMeasInAll[iGNSS][GNSSMeasCMD[iGNSS][measType]][measType]=ParametersList->at(iPar);
                    GNSSMeasCMD[iGNSS][measType]++;
                }

            // Graphic combination
            } else if (FreqMeasOpt[1].mid(0,1).contains("G",Qt::CaseInsensitive)) {
                int firstPhase=0;
                singleFreqGCProvided=1;
                if ( GNSSFreqCMDMode!=0 && GNSSFreqCMDMode!=MEAS_MODE_SINGLE ) {
                    if (setDualFreq==1) {
                        if (lastiPar!=iPar) {
                            *warningString += "FILTER: The GUI does not support loading both single and dual frequency combinations at the same time (command line does). Measurement ' " + ParametersList->at(iPar) + "' was skipped.\n";
                            lastiPar=iPar;
                        }
                    }
                    continue;
                } else if (singleFreqNonGCProvided==1) {
                    if (lastiPar!=iPar) {
                        *warningString += "FILTER: The GUI does not support loading both graphical and non-graphical combinations at the same time (command line does). Measurement ' " + ParametersList->at(iPar) + "' was skipped.\n";
                        lastiPar=iPar;
                    }
                    continue;
                }
                //These checks are redundant as they have already been checked by checkUserInputFilterMeasurement function
                if (nOpt==4) {
                    if (ParametersList->at(iPar).toUpper().contains(QRegularExpression("-G[1-9]-C[1-9]"+regExpValidAttributes+"-L[1-9]"+regExpValidAttributes+"$"))) {
                        firstPhase=0;
                    } else if (ParametersList->at(iPar).toUpper().contains(QRegularExpression("-G[1-9]-L[1-9]"+regExpValidAttributes+"-C[1-9]"+regExpValidAttributes+"$"))) {
                        firstPhase=1;
                    } else {
                        if (lastiPar!=iPar) {
                            *warningString += "FILTER: Invalid measurement '" + ParametersList->at(iPar) + "'. It was skipped.\n";
                            lastiPar=iPar;
                        }
                        continue;
                    }
                } else if (nOpt==2) {
                    if (!(ParametersList->at(iPar).toUpper().contains(QRegularExpression("-G[1-9]$")))) {
                        if (lastiPar!=iPar) {
                            *warningString += "FILTER: Invalid measurement '" + ParametersList->at(iPar) + "'. It was skipped.\n";
                            lastiPar=iPar;
                        }
                        continue;
                    }
                } else {
                    if (lastiPar!=iPar) {
                        *warningString += "FILTER: Invalid measurement '" + ParametersList->at(iPar) + "'. It was skipped.\n";
                        lastiPar=iPar;
                    }
                    continue;
                }

                if (GNSSMeasCMD[iGNSS][GCARRAYPOS]>2) {
                    *warningString += "FILTER: Maximum number of measurements for " + GNSSName[iGNSS] + " in the filter is 3. Argument '" + ParametersList->at(iPar) + "' was skipped for " + GNSSName[iGNSS] + " as limit has been surpassed.\n";
                    continue;
                }
                int ifreq;
                for (ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                    if (FreqMeasOpt[1].mid(1,1)==FreqGNSSList[iGNSS][ifreq]) break;
                }
                if (ifreq>=nFreqGNSS[iGNSS]) {
                    *warningString += "FILTER: Invalid frequency in argument '" + ParametersList->at(iPar) + "' for " + GNSSName[iGNSS] + " constellation. It was skipped.\n";
                    continue;
                }
                int imeas;
                if (nOpt==4) {
                    //Get code measurement
                    for (imeas=0;imeas<MeasCodeGNSSOrder[iGNSS][ifreq].size();imeas++) {
                        if (FreqMeasOpt[2+firstPhase].toUpper().mid(2,1)==MeasCodeGNSSOrder[iGNSS][ifreq].mid(imeas,1)){
                            if (GNSSFreqCMDMode==0) {
                                GNSSFreqCMDMode=MEAS_MODE_SINGLE;
                                this->on_radioButtonSingleFreq_clicked();
                                this->on_radioButtonSelectionGraphic_clicked();
                                setSingleFreq=1;
                            }
                            if ( FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][GCARRAYPOS]]->isHidden()) {
                                setGNSSMeasurementFreqAll(iGNSS,GNSSMeasCMD[iGNSS][GCARRAYPOS],0);
                                FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][GCARRAYPOS]]->setHidden(false);
                            } else {
                                setGNSSMeasurementFreqCP(iGNSS,GNSSMeasCMD[iGNSS][GCARRAYPOS],GCARRAYPOS,ifreq);
                            }
                            ComboBoxGNSSFreq[iGNSS][GNSSMeasCMD[iGNSS][GCARRAYPOS]][GCARRAYPOS]->currentIndexChanged(ifreq+1);
                            ComboBoxGNSSMeas[iGNSS][GNSSMeasCMD[iGNSS][GCARRAYPOS]][GCARRAYPOS][0]->currentIndexChanged(imeas+1);
                            break;
                        }
                    }
                    if (imeas>=MeasCodeGNSSOrder[iGNSS][ifreq].size()) {
                        *warningString += "FILTER: Invalid code measurement '" + FreqMeasOpt[2+firstPhase] + "' in argument '" + ParametersList->at(iPar) + "' for " + GNSSName[iGNSS] + " constellation. It was skipped.\n";
                        continue;
                    }
                    //Get phase measurement
                    for (imeas=0;imeas<MeasGNSSOrder[iGNSS][ifreq].size();imeas++) {
                        if (FreqMeasOpt[3-firstPhase].toUpper().mid(2,1)==MeasGNSSOrder[iGNSS][ifreq].mid(imeas,1)){
                            ComboBoxGNSSMeas[iGNSS][GNSSMeasCMD[iGNSS][GCARRAYPOS]][GCARRAYPOS][1]->currentIndexChanged(imeas+1);
                            GNSSMeasInAll[iGNSS][GNSSMeasCMD[iGNSS][GCARRAYPOS]][GCARRAYPOS]=ParametersList->at(iPar);
                            GNSSMeasCMD[iGNSS][GCARRAYPOS]++;
                            break;
                        }
                    }
                    if (imeas>=MeasGNSSOrder[iGNSS][ifreq].size()) {
                        *warningString += "FILTER: Invalid carrier phase measurement '" + FreqMeasOpt[3-firstPhase] + "' in argument '" + ParametersList->at(iPar) + "' for " + GNSSName[iGNSS] + " constellation. It was skipped.\n";
                        continue;
                    }
                } else {
                    if (GNSSFreqCMDMode==0) {
                        GNSSFreqCMDMode=MEAS_MODE_SINGLE;
                        this->on_radioButtonSingleFreq_clicked();
                        this->on_radioButtonSelectionGraphic_clicked();
                        setSingleFreq=1;
                    }
                    if ( FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][GCARRAYPOS]]->isHidden()) {
                        setGNSSMeasurementFreqAll(iGNSS,GNSSMeasCMD[iGNSS][GCARRAYPOS],0);
                        FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][GCARRAYPOS]]->setHidden(false);
                    } else {
                        setGNSSMeasurementFreqCP(iGNSS,GNSSMeasCMD[iGNSS][GCARRAYPOS],GCARRAYPOS,ifreq);
                    }
                    ComboBoxGNSSFreq[iGNSS][GNSSMeasCMD[iGNSS][GCARRAYPOS]][GCARRAYPOS]->currentIndexChanged(ifreq+1);
                    GNSSMeasInAll[iGNSS][GNSSMeasCMD[iGNSS][GCARRAYPOS]][GCARRAYPOS]=ParametersList->at(iPar);
                    GNSSMeasCMD[iGNSS][GCARRAYPOS]++;
                }
            // single code measurement
            } else if (FreqMeasOpt[1].mid(0,1).contains("C",Qt::CaseInsensitive) || FreqMeasOpt[1].mid(0,1).contains("L",Qt::CaseInsensitive)) {
                int measType=0; //0 -> Code 1 -> Phase
                singleFreqNonGCProvided=1;
                if ( GNSSFreqCMDMode!=0 && GNSSFreqCMDMode!=MEAS_MODE_SINGLE ) {
                    if (setDualFreq==1) {
                        if (lastiPar!=iPar) {
                            *warningString += "FILTER: The GUI does not support loading both single and dual frequency combinations at the same time (command line does). Measurement ' " + ParametersList->at(iPar) + "' was skipped.\n";
                            lastiPar=iPar;
                        }
                    }
                    continue;
                } else if (ui->radioButtonSelectionGraphic->isChecked() || singleFreqGCProvided==1) {
                    if (lastiPar!=iPar) {
                        *warningString += "FILTER: The GUI does not support loading both graphical and non-graphical combinations at the same time (command line does). Measurement ' " + ParametersList->at(iPar) + "' was skipped.\n";
                        lastiPar=iPar;
                    }
                    continue;
                }
                if (FreqMeasOpt[1].mid(0,1).contains("L",Qt::CaseInsensitive) ) measType=1;
                if (nOpt>=2) {
                    if (ParametersList->at(iPar).toUpper().contains(QRegularExpression("-C[1-9]"+regExpValidAttributes+"$")) && measType==0) {
                        measType=0;
                    } else if (ParametersList->at(iPar).toUpper().contains(QRegularExpression("-L[1-9]"+regExpValidAttributes+"$")) && measType==1) {
                        measType=1;
                    } else {
                        if (lastiPar!=iPar) {
                            *warningString += "FILTER: Invalid measurement '" + ParametersList->at(iPar) + "'. It was skipped.\n";
                            lastiPar=iPar;
                        }
                        continue;
                    }
                } else {
                    if (lastiPar!=iPar) {
                        *warningString += "FILTER: Invalid measurement '" + ParametersList->at(iPar) + "'. It was skipped.\n";
                        lastiPar=iPar;
                    }
                    continue;
                }

                if (FreqMeasOpt[1].size()!=3) continue;
                if (GNSSMeasCMD[iGNSS][measType]>2) {
                    *warningString += "FILTER: Maximum number of measurements for " + GNSSName[iGNSS] + " in the filter is 3. Argument '" + ParametersList->at(iPar) + "' was skipped for " + GNSSName[iGNSS] + " as limit has been surpassed.\n";
                    continue;
                }
                int ifreq;
                for (ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                    if (FreqMeasOpt[1].mid(1,1)==FreqGNSSList[iGNSS][ifreq]) break;
                }
                if (ifreq>=nFreqGNSS[iGNSS]) {
                    *warningString += "FILTER: Invalid frequency in argument '" + ParametersList->at(iPar) + "' for " + GNSSName[iGNSS] + " constellation. It was skipped.\n";
                    continue;
                }
                int imeas;
                for (imeas=0;imeas<MeasCodeGNSSOrder[iGNSS][ifreq].size();imeas++) {
                    if (FreqMeasOpt[1].toUpper().mid(2,1)==MeasCodeGNSSOrder[iGNSS][ifreq].mid(imeas,1)){
                        if (GNSSFreqCMDMode==0) {
                            GNSSFreqCMDMode=MEAS_MODE_SINGLE;
                            this->on_radioButtonSingleFreq_clicked();
                            setSingleFreq=1;
                        }
                        if ( FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][measType]]->isHidden() || GNSSMeasCMD[iGNSS][measType]>=GNSSMeasCMD[iGNSS][1-measType] ) {
                            setGNSSMeasurementFreqAll(iGNSS,GNSSMeasCMD[iGNSS][measType],0);
                            FrameGNSSMeasComb[iGNSS][GNSSMeasCMD[iGNSS][measType]]->setHidden(false);

                        } else {
                            setGNSSMeasurementFreqCP(iGNSS,GNSSMeasCMD[iGNSS][measType],measType,ifreq);
                        }
                        ComboBoxGNSSFreq[iGNSS][GNSSMeasCMD[iGNSS][measType]][measType]->currentIndexChanged(ifreq+noSmoothOffset);
                        ComboBoxGNSSMeas[iGNSS][GNSSMeasCMD[iGNSS][measType]][measType][COMBMEAS1ARRAYPOS]->currentIndexChanged(imeas+noSmoothOffset);
                        GNSSMeasInAll[iGNSS][GNSSMeasCMD[iGNSS][measType]][measType]=ParametersList->at(iPar);
                        GNSSMeasCMD[iGNSS][measType]++;
                        break;
                    }
                }
                if (imeas>=MeasCodeGNSSOrder[iGNSS][ifreq].size()) {
                    *warningString += "FILTER: Invalid measurement '" + FreqMeasOpt[1] + "' in argument '" + ParametersList->at(iPar) + "' for " + GNSSName[iGNSS] + " constellation. It was skipped.\n";
                    continue;
                }
            } else {
                if (lastiPar!=iPar) {
                    *warningString += "FILTER: Invalid filter measurement '" + ParametersList->at(iPar) + "'. It was skipped.\n";
                    lastiPar=iPar;
                }
                continue;
            }
        }
    }
}
//Function to read GNSS stdDev options
void gLAB_GUI::readGNSSStdDev(QString *warningString, QStringList *ParametersList, const int stdDevType){
    QString optionStr[5] = { "-filter:fixedweight", "-filter:elevweight", "-filter:sinelevweight", "-filter:snrweight", "-filter:snrelevweight" };
    int stdNum[5]={2,4,3,3,3};
    //stdDevType -> 0: fixedweight, 1: elevweight, 2: sinelevweight, 3: snrweight, 4: snrelevweight
    int nPar=ParametersList->count();
    //parameter number
    if ( ( stdDevType==0 && nPar%2!=0 ) || ( stdDevType==1 && nPar%4!=0 ) || ( stdDevType>1 && nPar%3!=0 ) ){
        *warningString += "FILTER: Parameter '" + optionStr[stdDevType] + "' does not have the right number of arguments. It was skipped.\n";
        return ;
    }
    //get number of options for different constellations
    int nOpt=nPar/stdNum[stdDevType];
    int badParam;
    for (int iOpt=0; iOpt<nOpt; iOpt++){
        //Check parameter
        badParam=this->checkUserInputFilterMeasurement(warningString,ParametersList->at(stdNum[stdDevType]*iOpt),MeasTargetFilter);
        if (badParam) continue;
        //stdDev ABC value
        double stdDevABC[3]={0};
        bool ABCOK=false;
        QString weightValuesParam="";
        for (int iABC=1; iABC<stdNum[stdDevType]; iABC++){
            weightValuesParam+=ParametersList->at(stdNum[stdDevType]*iOpt+iABC);
            if (iABC<(stdNum[stdDevType]-1)) {
                weightValuesParam+=" ";
            }
        }
        for (int iABC=1; iABC<stdNum[stdDevType]; iABC++){
            stdDevABC[iABC-1]=ParametersList->at(stdNum[stdDevType]*iOpt+iABC).toDouble(&ABCOK);
            if ( stdDevABC[iABC-1]<.0 || !ABCOK ){
                *warningString += "FILTER: Values in parameter '" + optionStr[stdDevType] + "' have to be equal or greater than 0, but values provided are '" + weightValuesParam + "'. It was skipped.\n";
                ABCOK=false;
                break;
            }
        }
        if (!ABCOK) continue;
        //get constellation and freq/meas option
        QString gnssMeasStr=ParametersList->at(stdNum[stdDevType]*iOpt);
        QStringList WeightMeasOpt=ParametersList->at(stdNum[stdDevType]*iOpt).split("-", QString::SkipEmptyParts);
        int nOptMeas=WeightMeasOpt.count();
        if (nOptMeas<2) continue;
        //loop constellation
        for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++){
            bool measOK=false;
            int icomb=-1,iCP=-1;
            int  phaseOffset=0;
            int  BothTypes=0;
            if ( WeightMeasOpt[0].contains(indentifierGNSS[iGNSS],Qt::CaseInsensitive)==false && WeightMeasOpt[0]!="0"  ) continue;
            for (icomb=0; icomb<MAXMEASTOFILTER; icomb++) {
                if (ui->radioButtonSelectionGraphic->isChecked()) {
                    iCP=GCARRAYPOS;
                    if ( GNSSMeasInAll[iGNSS][icomb][iCP].size()>0) {
                        QStringList FilterSelectMeasOpt = GNSSMeasInAll[iGNSS][icomb][iCP].split("-", QString::SkipEmptyParts);
                        int nOptFilter=FilterSelectMeasOpt.count();
                        if (nOptFilter==2 && nOptMeas==2 ) {
                            if (QString::compare(WeightMeasOpt[1], FilterSelectMeasOpt[1], Qt::CaseInsensitive)==0 && QString::compare(WeightMeasOpt[1], "auto", Qt::CaseInsensitive)!=0) {
                                measOK=true;
                                break;
                            }
                        } else if (nOptFilter==4 && nOptMeas==4) {
                            if (QString::compare(WeightMeasOpt[1], FilterSelectMeasOpt[1], Qt::CaseInsensitive)==0
                                    && QString::compare(WeightMeasOpt[2], FilterSelectMeasOpt[2], Qt::CaseInsensitive)==0
                                    && QString::compare(WeightMeasOpt[3], FilterSelectMeasOpt[3], Qt::CaseInsensitive)==0) {
                                measOK=true;
                                break;
                            }
                        }
                    }
                } else {
                    for (iCP=CODEARRAYPOS; iCP<=PHASEARRAYPOS; iCP++) {
                        if ( GNSSMeasInAll[iGNSS][icomb][iCP].size()>0) {
                            QStringList FilterSelectMeasOpt = GNSSMeasInAll[iGNSS][icomb][iCP].split("-", QString::SkipEmptyParts);
                            int nOptFilter=FilterSelectMeasOpt.count();
                            if (nOptFilter==2 && nOptMeas==2 ) {
                                if (QString::compare(WeightMeasOpt[1], FilterSelectMeasOpt[1], Qt::CaseInsensitive)==0 && QString::compare(WeightMeasOpt[1], "auto", Qt::CaseInsensitive)!=0) {
                                    measOK=true;
                                    break;
                                }
                            } else if (nOptFilter==3 && nOptMeas==3 ) {
                                if ( (WeightMeasOpt[1].contains("code",Qt::CaseInsensitive) && FilterSelectMeasOpt[1].contains("code",Qt::CaseInsensitive)) ||
                                      (WeightMeasOpt[1].contains("phase",Qt::CaseInsensitive) && FilterSelectMeasOpt[1].contains("phase",Qt::CaseInsensitive)) ) {
                                    if (QString::compare(WeightMeasOpt[2], FilterSelectMeasOpt[2], Qt::CaseInsensitive)==0) {
                                        measOK=true;
                                        if (WeightMeasOpt[1].contains("codephase",Qt::CaseInsensitive) || WeightMeasOpt[1].contains("phasecode",Qt::CaseInsensitive)) BothTypes=1;
                                        else if (iCP==0 && WeightMeasOpt[1].contains("phase",Qt::CaseInsensitive)) phaseOffset=1;
                                        break;
                                    }
                                } else if (QString::compare(WeightMeasOpt[1], FilterSelectMeasOpt[1], Qt::CaseInsensitive)==0) {
                                    if ( (WeightMeasOpt[2].contains("code",Qt::CaseInsensitive) && FilterSelectMeasOpt[2].contains("code",Qt::CaseInsensitive)) ||
                                          (WeightMeasOpt[2].contains("phase",Qt::CaseInsensitive) && FilterSelectMeasOpt[2].contains("phase",Qt::CaseInsensitive)) ) {
                                        measOK=true;
                                        if (WeightMeasOpt[1].contains("codephase",Qt::CaseInsensitive) || WeightMeasOpt[1].contains("phasecode",Qt::CaseInsensitive)) BothTypes=1;
                                        else if (iCP==0 && WeightMeasOpt[2].contains("phase",Qt::CaseInsensitive)) phaseOffset=1;
                                        break;
                                    }
                                }
                            } else if (nOptFilter==4 && nOptMeas==4) {
                                if (QString::compare(WeightMeasOpt[1], FilterSelectMeasOpt[1], Qt::CaseInsensitive)==0
                                        && QString::compare(WeightMeasOpt[2], FilterSelectMeasOpt[2], Qt::CaseInsensitive)==0
                                        && QString::compare(WeightMeasOpt[3], FilterSelectMeasOpt[3], Qt::CaseInsensitive)==0) {
                                    measOK=true;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (measOK==true) break;
            }
            if ( measOK==false ) {
                *warningString += "FILTER: Measurement '" +  gnssMeasStr + "' provided with parameter '" + optionStr[stdDevType] + "' cannot be matched with any measurement provided in '-filter:select' option for " + GNSSName[iGNSS] + ". It was skipped.\n";
                continue;
            } else {
                if (BothTypes==1) {
                    GNSSMeasNoiseCMD[iGNSS][0]++;
                    GNSSMeasNoiseCMD[iGNSS][1]++;
                } else {
                    GNSSMeasNoiseCMD[iGNSS][iCP+phaseOffset]++;
                }
            }
            if (BothTypes==1) {
                ComboBoxstdDevType[iGNSS][icomb][0]->setCurrentIndex(stdDevType);
                ComboBoxstdDevType[iGNSS][icomb][1]->setCurrentIndex(stdDevType);
                for (int iABC=1; iABC<stdNum[stdDevType]; iABC++){
                    LineEditstdDevValue[iGNSS][icomb][0][iABC-1]->setText(ParametersList->at(stdNum[stdDevType]*iOpt+iABC));
                    LineEditstdDevValue[iGNSS][icomb][1][iABC-1]->setText(ParametersList->at(stdNum[stdDevType]*iOpt+iABC));
                }
            } else {
                ComboBoxstdDevType[iGNSS][icomb][iCP+phaseOffset]->setCurrentIndex(stdDevType);
                for (int iABC=1; iABC<stdNum[stdDevType]; iABC++){
                    LineEditstdDevValue[iGNSS][icomb][iCP+phaseOffset][iABC-1]->setText(ParametersList->at(stdNum[stdDevType]*iOpt+iABC));
                }
            }
        }
    }
}

// For GPS
void gLAB_GUI::on_comboBoxFreqCodeGPS_1_currentIndexChanged(int index){
    ui->comboBoxFreqCodeGPS_1->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GPS,FIRSTMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeGPS_1->setEnabled(false);
            ui->lineEditStdDevCodeAGPS_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GPS,FIRSTMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeGPS_1->setEnabled(true);
            ui->lineEditStdDevCodeAGPS_1->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1GPS_1->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseGPS_1_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseGPS_1->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GPS,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseGPS_1->setEnabled(false);
            ui->lineEditStdDevPhaseAGPS_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GPS,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseGPS_1->setEnabled(true);
            ui->lineEditStdDevPhaseAGPS_1->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1GPS_1->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCGPS_1_currentIndexChanged(int index){
    ui->comboBoxFreqGCGPS_1->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCGPS_1->setEnabled(false);
            ui->lineEditStdDevGCAGPS_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GPS,FIRSTMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCGPS_1->setEnabled(true);
            ui->lineEditStdDevGCAGPS_1->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeGPS_1->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1GPS_1_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1GPS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2GPS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2GPS_1->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2GPS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2GPS_1_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2GPS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1GPS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1GPS_1->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1GPS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1GPS_1_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1GPS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2GPS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2GPS_1->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2GPS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2GPS_1_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2GPS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1GPS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1GPS_1->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1GPS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeGPS_1_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeGPS_1->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseGPS_1->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseGPS_1->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseGPS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseGPS_1_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseGPS_1->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeGPS_1->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeGPS_1->currentIndex()==0) {
        ui->comboBoxMeasGCCodeGPS_1->setCurrentIndex(1);
    }
}

void gLAB_GUI::on_comboBoxStdDevModeCodeGPS_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeGPS_1->setCurrentIndex(index);
    this->setWeightTypeValues(GPS,FIRSTMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBGPS_1->setHidden(true);
        ui->frameCodeCGPS_1->setHidden(true);
        ui->labelStdDevCodeAUnitGPS_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitGPS_1->setText("(m)");
        ui->labelStdDevCodeBUnitGPS_1->setText("(m)");
        ui->frameCodeBGPS_1->setHidden(false);
        ui->frameCodeCGPS_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCGPS_1->setHidden(true);
        ui->frameCodeBGPS_1->setHidden(false);
        ui->labelStdDevCodeAUnitGPS_1->setText("(m²)");
        ui->labelStdDevCodeBUnitGPS_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCGPS_1->setHidden(true);
        ui->frameCodeBGPS_1->setHidden(false);
        ui->labelStdDevCodeAUnitGPS_1->setText("(m²)");
        ui->labelStdDevCodeBUnitGPS_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseGPS_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseGPS_1->setCurrentIndex(index);
    this->setWeightTypeValues(GPS,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBGPS_1->setHidden(true);
        ui->framePhaseCGPS_1->setHidden(true);
        ui->labelStdDevPhaseAUnitGPS_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitGPS_1->setText("(m)");
        ui->labelStdDevPhaseBUnitGPS_1->setText("(m)");
        ui->framePhaseBGPS_1->setHidden(false);
        ui->framePhaseCGPS_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCGPS_1->setHidden(true);
        ui->framePhaseBGPS_1->setHidden(false);
        ui->labelStdDevPhaseAUnitGPS_1->setText("(m²)");
        ui->labelStdDevPhaseBUnitGPS_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCGPS_1->setHidden(true);
        ui->framePhaseBGPS_1->setHidden(false);
        ui->labelStdDevPhaseAUnitGPS_1->setText("(m²)");
        ui->labelStdDevPhaseBUnitGPS_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCGPS_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCGPS_1->setCurrentIndex(index);
    this->setWeightTypeValues(GPS,FIRSTMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBGPS_1->setHidden(true);
        ui->frameGCCGPS_1->setHidden(true);
        ui->labelStdDevGCAUnitGPS_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitGPS_1->setText("(m)");
        ui->labelStdDevGCBUnitGPS_1->setText("(m)");
        ui->frameGCBGPS_1->setHidden(false);
        ui->frameGCCGPS_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCGPS_1->setHidden(true);
        ui->frameGCBGPS_1->setHidden(false);
        ui->labelStdDevGCAUnitGPS_1->setText("(m²)");
        ui->labelStdDevGCBUnitGPS_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCGPS_1->setHidden(true);
        ui->frameGCBGPS_1->setHidden(false);
        ui->labelStdDevGCAUnitGPS_1->setText("(m²)");
        ui->labelStdDevGCBUnitGPS_1->setText("(m²·Hz)");
    }
}

void gLAB_GUI::on_comboBoxFreqCodeGPS_2_currentIndexChanged(int index){
    ui->comboBoxFreqCodeGPS_2->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GPS,SECONDMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeGPS_2->setEnabled(false);
            ui->lineEditStdDevCodeAGPS_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GPS,SECONDMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeGPS_2->setEnabled(true);
            ui->lineEditStdDevCodeAGPS_2->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1GPS_2->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqPhaseGPS_2_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseGPS_2->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GPS,SECONDMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseGPS_2->setEnabled(false);
            ui->lineEditStdDevPhaseAGPS_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GPS,SECONDMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseGPS_2->setEnabled(true);
            ui->lineEditStdDevPhaseAGPS_2->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1GPS_2->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCGPS_2_currentIndexChanged(int index){
    ui->comboBoxFreqGCGPS_2->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCGPS_2->setEnabled(false);
            ui->lineEditStdDevGCAGPS_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GPS,SECONDMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCGPS_2->setEnabled(true);
            ui->lineEditStdDevGCAGPS_2->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeGPS_2->setCurrentIndex(0);
}

void gLAB_GUI::on_comboBoxMeasCodeFreq1GPS_2_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1GPS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2GPS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2GPS_2->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2GPS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2GPS_2_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2GPS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1GPS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1GPS_2->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1GPS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1GPS_2_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1GPS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2GPS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2GPS_2->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2GPS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2GPS_2_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2GPS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1GPS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1GPS_2->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1GPS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeGPS_2_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeGPS_2->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseGPS_2->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseGPS_2->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseGPS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseGPS_2_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseGPS_2->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeGPS_2->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeGPS_2->currentIndex()==0) {
        ui->comboBoxMeasGCCodeGPS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeGPS_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeGPS_2->setCurrentIndex(index);
    this->setWeightTypeValues(GPS,SECONDMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBGPS_2->setHidden(true);
        ui->frameCodeCGPS_2->setHidden(true);
        ui->labelStdDevCodeAUnitGPS_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitGPS_2->setText("(m)");
        ui->labelStdDevCodeBUnitGPS_2->setText("(m)");
        ui->frameCodeBGPS_2->setHidden(false);
        ui->frameCodeCGPS_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCGPS_2->setHidden(true);
        ui->frameCodeBGPS_2->setHidden(false);
        ui->labelStdDevCodeAUnitGPS_2->setText("(m²)");
        ui->labelStdDevCodeBUnitGPS_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCGPS_2->setHidden(true);
        ui->frameCodeBGPS_2->setHidden(false);
        ui->labelStdDevCodeAUnitGPS_2->setText("(m²)");
        ui->labelStdDevCodeBUnitGPS_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseGPS_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseGPS_2->setCurrentIndex(index);
    this->setWeightTypeValues(GPS,SECONDMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBGPS_2->setHidden(true);
        ui->framePhaseCGPS_2->setHidden(true);
        ui->labelStdDevPhaseAUnitGPS_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitGPS_2->setText("(m)");
        ui->labelStdDevPhaseBUnitGPS_2->setText("(m)");
        ui->framePhaseBGPS_2->setHidden(false);
        ui->framePhaseCGPS_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCGPS_2->setHidden(true);
        ui->framePhaseBGPS_2->setHidden(false);
        ui->labelStdDevPhaseAUnitGPS_2->setText("(m²)");
        ui->labelStdDevPhaseBUnitGPS_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCGPS_2->setHidden(true);
        ui->framePhaseBGPS_2->setHidden(false);
        ui->labelStdDevPhaseAUnitGPS_2->setText("(m²)");
        ui->labelStdDevPhaseBUnitGPS_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCGPS_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCGPS_2->setCurrentIndex(index);
    this->setWeightTypeValues(GPS,SECONDMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBGPS_2->setHidden(true);
        ui->frameGCCGPS_2->setHidden(true);
        ui->labelStdDevGCAUnitGPS_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitGPS_2->setText("(m)");
        ui->labelStdDevGCBUnitGPS_2->setText("(m)");
        ui->frameGCBGPS_2->setHidden(false);
        ui->frameGCCGPS_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCGPS_2->setHidden(true);
        ui->frameGCBGPS_2->setHidden(false);
        ui->labelStdDevGCAUnitGPS_2->setText("(m²)");
        ui->labelStdDevGCBUnitGPS_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCGPS_2->setHidden(true);
        ui->frameGCBGPS_2->setHidden(false);
        ui->labelStdDevGCAUnitGPS_2->setText("(m²)");
        ui->labelStdDevGCBUnitGPS_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxFreqCodeGPS_3_currentIndexChanged(int index){
    ui->comboBoxFreqCodeGPS_3->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GPS,THIRDMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeGPS_3->setEnabled(false);
            ui->lineEditStdDevCodeAGPS_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GPS,THIRDMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeGPS_3->setEnabled(true);
            ui->lineEditStdDevCodeAGPS_3->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1GPS_3->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseGPS_3_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseGPS_3->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GPS,THIRDMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseGPS_3->setEnabled(false);
            ui->lineEditStdDevPhaseAGPS_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GPS,THIRDMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseGPS_3->setEnabled(true);
            ui->lineEditStdDevPhaseAGPS_3->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1GPS_3->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCGPS_3_currentIndexChanged(int index){
    ui->comboBoxFreqGCGPS_3->setCurrentIndex(index);

        if (index==0){//auto
            ui->comboBoxStdDevModeGCGPS_3->setEnabled(false);
            ui->lineEditStdDevGCAGPS_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GPS,THIRDMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCGPS_3->setEnabled(true);
            ui->lineEditStdDevGCAGPS_3->setEnabled(true);
        }

    ui->comboBoxMeasGCCodeGPS_3->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1GPS_3_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1GPS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2GPS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2GPS_3->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2GPS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2GPS_3_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2GPS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1GPS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1GPS_3->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1GPS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1GPS_3_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1GPS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2GPS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2GPS_3->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2GPS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2GPS_3_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2GPS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1GPS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1GPS_3->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1GPS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeGPS_3_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeGPS_3->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseGPS_3->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseGPS_3->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseGPS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseGPS_3_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseGPS_3->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeGPS_3->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeGPS_3->currentIndex()==0) {
        ui->comboBoxMeasGCCodeGPS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeGPS_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeGPS_3->setCurrentIndex(index);
    this->setWeightTypeValues(GPS,THIRDMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBGPS_3->setHidden(true);
        ui->frameCodeCGPS_3->setHidden(true);
        ui->labelStdDevCodeAUnitGPS_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitGPS_3->setText("(m)");
        ui->labelStdDevCodeBUnitGPS_3->setText("(m)");
        ui->frameCodeBGPS_3->setHidden(false);
        ui->frameCodeCGPS_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCGPS_3->setHidden(true);
        ui->frameCodeBGPS_3->setHidden(false);
        ui->labelStdDevCodeAUnitGPS_3->setText("(m²)");
        ui->labelStdDevCodeBUnitGPS_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCGPS_3->setHidden(true);
        ui->frameCodeBGPS_3->setHidden(false);
        ui->labelStdDevCodeAUnitGPS_3->setText("(m²)");
        ui->labelStdDevCodeBUnitGPS_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseGPS_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseGPS_3->setCurrentIndex(index);
    this->setWeightTypeValues(GPS,THIRDMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBGPS_3->setHidden(true);
        ui->framePhaseCGPS_3->setHidden(true);
        ui->labelStdDevPhaseAUnitGPS_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitGPS_3->setText("(m)");
        ui->labelStdDevPhaseBUnitGPS_3->setText("(m)");
        ui->framePhaseBGPS_3->setHidden(false);
        ui->framePhaseCGPS_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCGPS_3->setHidden(true);
        ui->framePhaseBGPS_3->setHidden(false);
        ui->labelStdDevPhaseAUnitGPS_3->setText("(m²)");
        ui->labelStdDevPhaseBUnitGPS_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCGPS_3->setHidden(true);
        ui->framePhaseBGPS_3->setHidden(false);
        ui->labelStdDevPhaseAUnitGPS_3->setText("(m²)");
        ui->labelStdDevPhaseBUnitGPS_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCGPS_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCGPS_3->setCurrentIndex(index);
    this->setWeightTypeValues(GPS,THIRDMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBGPS_3->setHidden(true);
        ui->frameGCCGPS_3->setHidden(true);
        ui->labelStdDevGCAUnitGPS_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitGPS_3->setText("(m)");
        ui->labelStdDevGCBUnitGPS_3->setText("(m)");
        ui->frameGCBGPS_3->setHidden(false);
        ui->frameGCCGPS_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCGPS_3->setHidden(true);
        ui->frameGCBGPS_3->setHidden(false);
        ui->labelStdDevGCAUnitGPS_3->setText("(m²)");
        ui->labelStdDevGCBUnitGPS_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCGPS_3->setHidden(true);
        ui->frameGCBGPS_3->setHidden(false);
        ui->labelStdDevGCAUnitGPS_3->setText("(m²)");
        ui->labelStdDevGCBUnitGPS_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxSmoothWithGPS_1_currentIndexChanged(int index){
    ui->comboBoxSmoothWithGPS_1->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithGPS_1->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(GPS,FIRSTMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithGPS_1->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2GPS_1->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2GPS_1->setHidden(false);

    this->setSmoothWithFreqAll(GPS,FIRSTMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1GPS_1->setHidden(false); //GC
    else ui->frameSmoothCode1GPS_1->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1GPS_1_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GPS][FIRSTMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1GPS_1->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(GPS,FIRSTMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1GPS_1->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1GPS_1->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGPS_1->currentIndex()>2 && ui->comboBoxSmoothFreq2GPS_1->currentIndex()==index){
        ui->comboBoxSmoothFreq2GPS_1->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[GPS][FIRSTMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2GPS_1_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GPS][FIRSTMEASARRAYPOS][1];

        ui->comboBoxSmoothFreq2GPS_1->setCurrentIndex(index);
        this->setSmoothWithMeasComboBoxValue(GPS,FIRSTMEASARRAYPOS,-1,index);
        ui->comboBoxSmoothPhase2GPS_1->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGPS_1->currentIndex()>2 && ui->comboBoxSmoothFreq1GPS_1->currentIndex()==index){
        ui->comboBoxSmoothFreq1GPS_1->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[GPS][FIRSTMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1GPS_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GPS_1->count()>0) ui->comboBoxSmoothCode1GPS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GPS_1->count()>0) ui->comboBoxSmoothPhase1GPS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GPS_1->count()>0) ui->comboBoxSmoothPhase2GPS_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1GPS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1GPS_1->count()>0 && ui->comboBoxSmoothPhase1GPS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase1GPS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2GPS_1->count()>0 && ui->comboBoxSmoothPhase2GPS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase2GPS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1GPS_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GPS_1->count()>0) ui->comboBoxSmoothCode1GPS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GPS_1->count()>0) ui->comboBoxSmoothPhase1GPS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GPS_1->count()>0) ui->comboBoxSmoothPhase2GPS_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1GPS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GPS_1->count()>0 && ui->comboBoxSmoothCode1GPS_1->currentIndex()==0 ) ui->comboBoxSmoothCode1GPS_1->setCurrentIndex(index>=ui->comboBoxSmoothCode1GPS_1->count()?1:index);
        if ( ui->comboBoxSmoothPhase2GPS_1->count()>0 && ui->comboBoxSmoothPhase2GPS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase2GPS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2GPS_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GPS_1->count()>0) ui->comboBoxSmoothCode1GPS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GPS_1->count()>0) ui->comboBoxSmoothPhase1GPS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GPS_1->count()>0) ui->comboBoxSmoothPhase2GPS_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2GPS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GPS_1->count()>0 && ui->comboBoxSmoothCode1GPS_1->currentIndex()==0 ) ui->comboBoxSmoothCode1GPS_1->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1GPS_1->count()>0 && ui->comboBoxSmoothPhase1GPS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase1GPS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothWithGPS_2_currentIndexChanged(int index){
    ui->comboBoxSmoothWithGPS_2->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithGPS_2->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(GPS,SECONDMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithGPS_2->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2GPS_2->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2GPS_2->setHidden(false);

    this->setSmoothWithFreqAll(GPS,SECONDMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1GPS_2->setHidden(false); //GC
    else ui->frameSmoothCode1GPS_2->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1GPS_2_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GPS][SECONDMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1GPS_2->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(GPS,SECONDMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1GPS_2->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1GPS_2->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGPS_2->currentIndex()>2 && ui->comboBoxSmoothFreq2GPS_2->currentIndex()==index){
        ui->comboBoxSmoothFreq2GPS_2->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[GPS][SECONDMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2GPS_2_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GPS][SECONDMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2GPS_2->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(GPS,SECONDMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2GPS_2->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGPS_2->currentIndex()>2 && ui->comboBoxSmoothFreq1GPS_2->currentIndex()==index){
        ui->comboBoxSmoothFreq1GPS_2->setCurrentIndex(last_index);
    }

    smoothWithFreqIndexAll[GPS][SECONDMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1GPS_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GPS_2->count()>0) ui->comboBoxSmoothCode1GPS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GPS_2->count()>0) ui->comboBoxSmoothPhase1GPS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GPS_2->count()>0) ui->comboBoxSmoothPhase2GPS_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1GPS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1GPS_2->count()>0 && ui->comboBoxSmoothPhase1GPS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase1GPS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2GPS_2->count()>0 && ui->comboBoxSmoothPhase2GPS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase2GPS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1GPS_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GPS_2->count()>0) ui->comboBoxSmoothCode1GPS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GPS_2->count()>0) ui->comboBoxSmoothPhase1GPS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GPS_2->count()>0) ui->comboBoxSmoothPhase2GPS_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1GPS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GPS_2->count()>0 && ui->comboBoxSmoothCode1GPS_2->currentIndex()==0 ) ui->comboBoxSmoothCode1GPS_2->setCurrentIndex(index>=ui->comboBoxSmoothCode1GPS_2->count()?1:index);
        if ( ui->comboBoxSmoothPhase2GPS_2->count()>0 && ui->comboBoxSmoothPhase2GPS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase2GPS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2GPS_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GPS_2->count()>0) ui->comboBoxSmoothCode1GPS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GPS_2->count()>0) ui->comboBoxSmoothPhase1GPS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GPS_2->count()>0) ui->comboBoxSmoothPhase2GPS_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2GPS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GPS_2->count()>0 && ui->comboBoxSmoothCode1GPS_2->currentIndex()==0 ) ui->comboBoxSmoothCode1GPS_2->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1GPS_2->count()>0 && ui->comboBoxSmoothPhase1GPS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase1GPS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothWithGPS_3_currentIndexChanged(int index){
    ui->comboBoxSmoothWithGPS_3->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithGPS_3->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(GPS,THIRDMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithGPS_3->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2GPS_3->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2GPS_3->setHidden(false);

    this->setSmoothWithFreqAll(GPS,THIRDMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1GPS_3->setHidden(false); //GC
    else ui->frameSmoothCode1GPS_3->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1GPS_3_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GPS][THIRDMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1GPS_3->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(GPS,THIRDMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1GPS_3->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1GPS_3->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGPS_3->currentIndex()>2 && ui->comboBoxSmoothFreq2GPS_3->currentIndex()==index){
        ui->comboBoxSmoothFreq2GPS_3->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[GPS][THIRDMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2GPS_3_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GPS][THIRDMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2GPS_3->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(GPS,THIRDMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2GPS_3->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGPS_3->currentIndex()>2 && ui->comboBoxSmoothFreq1GPS_3->currentIndex()==index){
        ui->comboBoxSmoothFreq1GPS_3->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[GPS][THIRDMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1GPS_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GPS_3->count()>0) ui->comboBoxSmoothCode1GPS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GPS_3->count()>0) ui->comboBoxSmoothPhase1GPS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GPS_3->count()>0) ui->comboBoxSmoothPhase2GPS_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1GPS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1GPS_3->count()>0 && ui->comboBoxSmoothPhase1GPS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase1GPS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2GPS_3->count()>0 && ui->comboBoxSmoothPhase2GPS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase2GPS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1GPS_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GPS_3->count()>0) ui->comboBoxSmoothCode1GPS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GPS_3->count()>0) ui->comboBoxSmoothPhase1GPS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GPS_3->count()>0) ui->comboBoxSmoothPhase2GPS_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1GPS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GPS_3->count()>0 && ui->comboBoxSmoothCode1GPS_3->currentIndex()==0 ) ui->comboBoxSmoothCode1GPS_3->setCurrentIndex(index>=ui->comboBoxSmoothCode1GPS_3->count()?1:index);
        if ( ui->comboBoxSmoothPhase2GPS_3->count()>0 && ui->comboBoxSmoothPhase2GPS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase2GPS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2GPS_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GPS_3->count()>0) ui->comboBoxSmoothCode1GPS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GPS_3->count()>0) ui->comboBoxSmoothPhase1GPS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GPS_3->count()>0) ui->comboBoxSmoothPhase2GPS_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2GPS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GPS_3->count()>0 && ui->comboBoxSmoothCode1GPS_3->currentIndex()==0 ) ui->comboBoxSmoothCode1GPS_3->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1GPS_3->count()>0 && ui->comboBoxSmoothPhase1GPS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase1GPS_3->setCurrentIndex(1);
    }
}

// For Galileo
void gLAB_GUI::on_comboBoxFreqCodeGalileo_1_currentIndexChanged(int index){
    ui->comboBoxFreqCodeGalileo_1->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(Galileo,FIRSTMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeGalileo_1->setEnabled(false);
            ui->lineEditStdDevCodeAGalileo_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(Galileo,FIRSTMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeGalileo_1->setEnabled(true);
            ui->lineEditStdDevCodeAGalileo_1->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1Galileo_1->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseGalileo_1_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseGalileo_1->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(Galileo,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseGalileo_1->setEnabled(false);
            ui->lineEditStdDevPhaseAGalileo_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(Galileo,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseGalileo_1->setEnabled(true);
            ui->lineEditStdDevPhaseAGalileo_1->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1Galileo_1->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCGalileo_1_currentIndexChanged(int index){
    ui->comboBoxFreqGCGalileo_1->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCGalileo_1->setEnabled(false);
            ui->lineEditStdDevGCAGalileo_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(Galileo,FIRSTMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCGalileo_1->setEnabled(true);
            ui->lineEditStdDevGCAGalileo_1->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeGalileo_1->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1Galileo_1_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1Galileo_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2Galileo_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2Galileo_1->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2Galileo_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2Galileo_1_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2Galileo_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1Galileo_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1Galileo_1->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1Galileo_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1Galileo_1_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1Galileo_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2Galileo_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2Galileo_1->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2Galileo_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2Galileo_1_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2Galileo_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1Galileo_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1Galileo_1->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1Galileo_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeGalileo_1_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeGalileo_1->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseGalileo_1->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseGalileo_1->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseGalileo_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseGalileo_1_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseGalileo_1->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeGalileo_1->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeGalileo_1->currentIndex()==0) {
        ui->comboBoxMeasGCCodeGalileo_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeGalileo_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeGalileo_1->setCurrentIndex(index);
    this->setWeightTypeValues(Galileo,FIRSTMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBGalileo_1->setHidden(true);
        ui->frameCodeCGalileo_1->setHidden(true);
        ui->labelStdDevCodeAUnitGalileo_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitGalileo_1->setText("(m)");
        ui->labelStdDevCodeBUnitGalileo_1->setText("(m)");
        ui->frameCodeBGalileo_1->setHidden(false);
        ui->frameCodeCGalileo_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCGalileo_1->setHidden(true);
        ui->frameCodeBGalileo_1->setHidden(false);
        ui->labelStdDevCodeAUnitGalileo_1->setText("(m²)");
        ui->labelStdDevCodeBUnitGalileo_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCGalileo_1->setHidden(true);
        ui->frameCodeBGalileo_1->setHidden(false);
        ui->labelStdDevCodeAUnitGalileo_1->setText("(m²)");
        ui->labelStdDevCodeBUnitGalileo_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseGalileo_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseGalileo_1->setCurrentIndex(index);
    this->setWeightTypeValues(Galileo,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBGalileo_1->setHidden(true);
        ui->framePhaseCGalileo_1->setHidden(true);
        ui->labelStdDevPhaseAUnitGalileo_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitGalileo_1->setText("(m)");
        ui->labelStdDevPhaseBUnitGalileo_1->setText("(m)");
        ui->framePhaseBGalileo_1->setHidden(false);
        ui->framePhaseCGalileo_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCGalileo_1->setHidden(true);
        ui->framePhaseBGalileo_1->setHidden(false);
        ui->labelStdDevPhaseAUnitGalileo_1->setText("(m²)");
        ui->labelStdDevPhaseBUnitGalileo_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCGalileo_1->setHidden(true);
        ui->framePhaseBGalileo_1->setHidden(false);
        ui->labelStdDevPhaseAUnitGalileo_1->setText("(m²)");
        ui->labelStdDevPhaseBUnitGalileo_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCGalileo_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCGalileo_1->setCurrentIndex(index);
    this->setWeightTypeValues(Galileo,FIRSTMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBGalileo_1->setHidden(true);
        ui->frameGCCGalileo_1->setHidden(true);
        ui->labelStdDevGCAUnitGalileo_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitGalileo_1->setText("(m)");
        ui->labelStdDevGCBUnitGalileo_1->setText("(m)");
        ui->frameGCBGalileo_1->setHidden(false);
        ui->frameGCCGalileo_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCGalileo_1->setHidden(true);
        ui->frameGCBGalileo_1->setHidden(false);
        ui->labelStdDevGCAUnitGalileo_1->setText("(m²)");
        ui->labelStdDevGCBUnitGalileo_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCGalileo_1->setHidden(true);
        ui->frameGCBGalileo_1->setHidden(false);
        ui->labelStdDevGCAUnitGalileo_1->setText("(m²)");
        ui->labelStdDevGCBUnitGalileo_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxFreqCodeGalileo_2_currentIndexChanged(int index){
    ui->comboBoxFreqCodeGalileo_2->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(Galileo,SECONDMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeGalileo_2->setEnabled(false);
            ui->lineEditStdDevCodeAGalileo_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(Galileo,SECONDMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeGalileo_2->setEnabled(true);
            ui->lineEditStdDevCodeAGalileo_2->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1Galileo_2->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseGalileo_2_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseGalileo_2->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(Galileo,SECONDMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseGalileo_2->setEnabled(false);
            ui->lineEditStdDevPhaseAGalileo_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(Galileo,SECONDMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseGalileo_2->setEnabled(true);
            ui->lineEditStdDevPhaseAGalileo_2->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1Galileo_2->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCGalileo_2_currentIndexChanged(int index){
    ui->comboBoxFreqGCGalileo_2->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCGalileo_2->setEnabled(false);
            ui->lineEditStdDevGCAGalileo_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(Galileo,SECONDMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCGalileo_2->setEnabled(true);
            ui->lineEditStdDevGCAGalileo_2->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeGalileo_2->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1Galileo_2_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1Galileo_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2Galileo_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2Galileo_2->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2Galileo_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2Galileo_2_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2Galileo_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1Galileo_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1Galileo_2->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1Galileo_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1Galileo_2_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1Galileo_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2Galileo_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2Galileo_2->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2Galileo_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2Galileo_2_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2Galileo_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1Galileo_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1Galileo_2->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1Galileo_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeGalileo_2_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeGalileo_2->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseGalileo_2->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseGalileo_2->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseGalileo_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseGalileo_2_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseGalileo_2->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeGalileo_2->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeGalileo_2->currentIndex()==0) {
        ui->comboBoxMeasGCCodeGalileo_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeGalileo_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeGalileo_2->setCurrentIndex(index);
    this->setWeightTypeValues(Galileo,SECONDMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBGalileo_2->setHidden(true);
        ui->frameCodeCGalileo_2->setHidden(true);
        ui->labelStdDevCodeAUnitGalileo_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitGalileo_2->setText("(m)");
        ui->labelStdDevCodeBUnitGalileo_2->setText("(m)");
        ui->frameCodeBGalileo_2->setHidden(false);
        ui->frameCodeCGalileo_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCGalileo_2->setHidden(true);
        ui->frameCodeBGalileo_2->setHidden(false);
        ui->labelStdDevCodeAUnitGalileo_2->setText("(m²)");
        ui->labelStdDevCodeBUnitGalileo_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCGalileo_2->setHidden(true);
        ui->frameCodeBGalileo_2->setHidden(false);
        ui->labelStdDevCodeAUnitGalileo_2->setText("(m²)");
        ui->labelStdDevCodeBUnitGalileo_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseGalileo_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseGalileo_2->setCurrentIndex(index);
    this->setWeightTypeValues(Galileo,SECONDMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBGalileo_2->setHidden(true);
        ui->framePhaseCGalileo_2->setHidden(true);
        ui->labelStdDevPhaseAUnitGalileo_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitGalileo_2->setText("(m)");
        ui->labelStdDevPhaseBUnitGalileo_2->setText("(m)");
        ui->framePhaseBGalileo_2->setHidden(false);
        ui->framePhaseCGalileo_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCGalileo_2->setHidden(true);
        ui->framePhaseBGalileo_2->setHidden(false);
        ui->labelStdDevPhaseAUnitGalileo_2->setText("(m²)");
        ui->labelStdDevPhaseBUnitGalileo_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCGalileo_2->setHidden(true);
        ui->framePhaseBGalileo_2->setHidden(false);
        ui->labelStdDevPhaseAUnitGalileo_2->setText("(m²)");
        ui->labelStdDevPhaseBUnitGalileo_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCGalileo_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCGalileo_2->setCurrentIndex(index);
    this->setWeightTypeValues(Galileo,SECONDMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBGalileo_2->setHidden(true);
        ui->frameGCCGalileo_2->setHidden(true);
        ui->labelStdDevGCAUnitGalileo_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitGalileo_2->setText("(m)");
        ui->labelStdDevGCBUnitGalileo_2->setText("(m)");
        ui->frameGCBGalileo_2->setHidden(false);
        ui->frameGCCGalileo_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCGalileo_2->setHidden(true);
        ui->frameGCBGalileo_2->setHidden(false);
        ui->labelStdDevGCAUnitGalileo_2->setText("(m²)");
        ui->labelStdDevGCBUnitGalileo_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCGalileo_2->setHidden(true);
        ui->frameGCBGalileo_2->setHidden(false);
        ui->labelStdDevGCAUnitGalileo_2->setText("(m²)");
        ui->labelStdDevGCBUnitGalileo_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxFreqCodeGalileo_3_currentIndexChanged(int index){
    ui->comboBoxFreqCodeGalileo_3->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(Galileo,THIRDMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeGalileo_3->setEnabled(false);
            ui->lineEditStdDevCodeAGalileo_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(Galileo,THIRDMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeGalileo_3->setEnabled(true);
            ui->lineEditStdDevCodeAGalileo_3->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1Galileo_3->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseGalileo_3_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseGalileo_3->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(Galileo,THIRDMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseGalileo_3->setEnabled(false);
            ui->lineEditStdDevPhaseAGalileo_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(Galileo,THIRDMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseGalileo_3->setEnabled(true);
            ui->lineEditStdDevPhaseAGalileo_3->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1Galileo_3->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCGalileo_3_currentIndexChanged(int index){
    ui->comboBoxFreqGCGalileo_3->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCGalileo_3->setEnabled(false);
            ui->lineEditStdDevGCAGalileo_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(Galileo,THIRDMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCGalileo_3->setEnabled(true);
            ui->lineEditStdDevGCAGalileo_3->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeGalileo_3->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1Galileo_3_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1Galileo_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2Galileo_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2Galileo_3->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2Galileo_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2Galileo_3_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2Galileo_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1Galileo_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1Galileo_3->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1Galileo_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1Galileo_3_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1Galileo_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2Galileo_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2Galileo_3->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2Galileo_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2Galileo_3_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2Galileo_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1Galileo_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1Galileo_3->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1Galileo_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeGalileo_3_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeGalileo_3->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseGalileo_3->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseGalileo_3->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseGalileo_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseGalileo_3_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseGalileo_3->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeGalileo_3->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeGalileo_3->currentIndex()==0) {
        ui->comboBoxMeasGCCodeGalileo_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeGalileo_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeGalileo_3->setCurrentIndex(index);
    this->setWeightTypeValues(Galileo,THIRDMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBGalileo_3->setHidden(true);
        ui->frameCodeCGalileo_3->setHidden(true);
        ui->labelStdDevCodeAUnitGalileo_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitGalileo_3->setText("(m)");
        ui->labelStdDevCodeBUnitGalileo_3->setText("(m)");
        ui->frameCodeBGalileo_3->setHidden(false);
        ui->frameCodeCGalileo_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCGalileo_3->setHidden(true);
        ui->frameCodeBGalileo_3->setHidden(false);
        ui->labelStdDevCodeAUnitGalileo_3->setText("(m²)");
        ui->labelStdDevCodeBUnitGalileo_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCGalileo_3->setHidden(true);
        ui->frameCodeBGalileo_3->setHidden(false);
        ui->labelStdDevCodeAUnitGalileo_3->setText("(m²)");
        ui->labelStdDevCodeBUnitGalileo_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseGalileo_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseGalileo_3->setCurrentIndex(index);
    this->setWeightTypeValues(Galileo,THIRDMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBGalileo_3->setHidden(true);
        ui->framePhaseCGalileo_3->setHidden(true);
        ui->labelStdDevPhaseAUnitGalileo_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitGalileo_3->setText("(m)");
        ui->labelStdDevPhaseBUnitGalileo_3->setText("(m)");
        ui->framePhaseBGalileo_3->setHidden(false);
        ui->framePhaseCGalileo_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCGalileo_3->setHidden(true);
        ui->framePhaseBGalileo_3->setHidden(false);
        ui->labelStdDevPhaseAUnitGalileo_3->setText("(m²)");
        ui->labelStdDevPhaseBUnitGalileo_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCGalileo_3->setHidden(true);
        ui->framePhaseBGalileo_3->setHidden(false);
        ui->labelStdDevPhaseAUnitGalileo_3->setText("(m²)");
        ui->labelStdDevPhaseBUnitGalileo_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCGalileo_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCGalileo_3->setCurrentIndex(index);
    this->setWeightTypeValues(Galileo,THIRDMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBGalileo_3->setHidden(true);
        ui->frameGCCGalileo_3->setHidden(true);
        ui->labelStdDevGCAUnitGalileo_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitGalileo_3->setText("(m)");
        ui->labelStdDevGCBUnitGalileo_3->setText("(m)");
        ui->frameGCBGalileo_3->setHidden(false);
        ui->frameGCCGalileo_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCGalileo_3->setHidden(true);
        ui->frameGCBGalileo_3->setHidden(false);
        ui->labelStdDevGCAUnitGalileo_3->setText("(m²)");
        ui->labelStdDevGCBUnitGalileo_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCGalileo_3->setHidden(true);
        ui->frameGCBGalileo_3->setHidden(false);
        ui->labelStdDevGCAUnitGalileo_3->setText("(m²)");
        ui->labelStdDevGCBUnitGalileo_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxSmoothWithGalileo_1_currentIndexChanged(int index){
    ui->comboBoxSmoothWithGalileo_1->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithGalileo_1->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(Galileo,FIRSTMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithGalileo_1->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2Galileo_1->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2Galileo_1->setHidden(false);

    this->setSmoothWithFreqAll(Galileo,FIRSTMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1Galileo_1->setHidden(false); //GC
    else ui->frameSmoothCode1Galileo_1->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1Galileo_1_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[Galileo][FIRSTMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1Galileo_1->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(Galileo,FIRSTMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1Galileo_1->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1Galileo_1->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGalileo_1->currentIndex()>2 && ui->comboBoxSmoothFreq2Galileo_1->currentIndex()==index){
        ui->comboBoxSmoothFreq2Galileo_1->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[Galileo][FIRSTMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2Galileo_1_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[Galileo][FIRSTMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2Galileo_1->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(Galileo,FIRSTMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2Galileo_1->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGalileo_1->currentIndex()>2 && ui->comboBoxSmoothFreq1Galileo_1->currentIndex()==index){
        ui->comboBoxSmoothFreq1Galileo_1->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[Galileo][FIRSTMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1Galileo_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1Galileo_1->count()>0) ui->comboBoxSmoothCode1Galileo_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1Galileo_1->count()>0) ui->comboBoxSmoothPhase1Galileo_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2Galileo_1->count()>0) ui->comboBoxSmoothPhase2Galileo_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1Galileo_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1Galileo_1->count()>0 && ui->comboBoxSmoothPhase1Galileo_1->currentIndex()==0 ) ui->comboBoxSmoothPhase1Galileo_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2Galileo_1->count()>0 && ui->comboBoxSmoothPhase2Galileo_1->currentIndex()==0 ) ui->comboBoxSmoothPhase2Galileo_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1Galileo_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1Galileo_1->count()>0) ui->comboBoxSmoothCode1Galileo_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1Galileo_1->count()>0) ui->comboBoxSmoothPhase1Galileo_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2Galileo_1->count()>0) ui->comboBoxSmoothPhase2Galileo_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1Galileo_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1Galileo_1->count()>0 && ui->comboBoxSmoothCode1Galileo_1->currentIndex()==0 ) ui->comboBoxSmoothCode1Galileo_1->setCurrentIndex(index>=ui->comboBoxSmoothCode1Galileo_1->count()?1:index);
        if ( ui->comboBoxSmoothPhase2Galileo_1->count()>0 && ui->comboBoxSmoothPhase2Galileo_1->currentIndex()==0 ) ui->comboBoxSmoothPhase2Galileo_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2Galileo_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1Galileo_1->count()>0) ui->comboBoxSmoothCode1Galileo_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1Galileo_1->count()>0) ui->comboBoxSmoothPhase1Galileo_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2Galileo_1->count()>0) ui->comboBoxSmoothPhase2Galileo_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2Galileo_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1Galileo_1->count()>0 && ui->comboBoxSmoothCode1Galileo_1->currentIndex()==0 ) ui->comboBoxSmoothCode1Galileo_1->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1Galileo_1->count()>0 && ui->comboBoxSmoothPhase1Galileo_1->currentIndex()==0 ) ui->comboBoxSmoothPhase1Galileo_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothWithGalileo_2_currentIndexChanged(int index){
    ui->comboBoxSmoothWithGalileo_2->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithGalileo_2->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(Galileo,SECONDMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithGalileo_2->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2Galileo_2->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2Galileo_2->setHidden(false);

    this->setSmoothWithFreqAll(Galileo,SECONDMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1Galileo_2->setHidden(false); //GC
    else ui->frameSmoothCode1Galileo_2->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1Galileo_2_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[Galileo][SECONDMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1Galileo_2->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(Galileo,SECONDMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1Galileo_2->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1Galileo_2->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGalileo_2->currentIndex()>2 && ui->comboBoxSmoothFreq2Galileo_2->currentIndex()==index){
        ui->comboBoxSmoothFreq2Galileo_2->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[Galileo][SECONDMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2Galileo_2_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[Galileo][SECONDMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2Galileo_2->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(Galileo,SECONDMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2Galileo_2->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGalileo_2->currentIndex()>2 && ui->comboBoxSmoothFreq1Galileo_2->currentIndex()==index){
        ui->comboBoxSmoothFreq1Galileo_2->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[Galileo][SECONDMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1Galileo_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1Galileo_2->count()>0) ui->comboBoxSmoothCode1Galileo_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1Galileo_2->count()>0) ui->comboBoxSmoothPhase1Galileo_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2Galileo_2->count()>0) ui->comboBoxSmoothPhase2Galileo_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1Galileo_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1Galileo_2->count()>0 && ui->comboBoxSmoothPhase1Galileo_2->currentIndex()==0 ) ui->comboBoxSmoothPhase1Galileo_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2Galileo_2->count()>0 && ui->comboBoxSmoothPhase2Galileo_2->currentIndex()==0 ) ui->comboBoxSmoothPhase2Galileo_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1Galileo_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1Galileo_2->count()>0) ui->comboBoxSmoothCode1Galileo_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1Galileo_2->count()>0) ui->comboBoxSmoothPhase1Galileo_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2Galileo_2->count()>0) ui->comboBoxSmoothPhase2Galileo_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1Galileo_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1Galileo_2->count()>0 && ui->comboBoxSmoothCode1Galileo_2->currentIndex()==0 ) ui->comboBoxSmoothCode1Galileo_2->setCurrentIndex(index>=ui->comboBoxSmoothCode1Galileo_2->count()?1:index);
        if ( ui->comboBoxSmoothPhase2Galileo_2->count()>0 && ui->comboBoxSmoothPhase2Galileo_2->currentIndex()==0 ) ui->comboBoxSmoothPhase2Galileo_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2Galileo_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1Galileo_2->count()>0) ui->comboBoxSmoothCode1Galileo_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1Galileo_2->count()>0) ui->comboBoxSmoothPhase1Galileo_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2Galileo_2->count()>0) ui->comboBoxSmoothPhase2Galileo_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2Galileo_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1Galileo_2->count()>0 && ui->comboBoxSmoothCode1Galileo_2->currentIndex()==0 ) ui->comboBoxSmoothCode1Galileo_2->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1Galileo_2->count()>0 && ui->comboBoxSmoothPhase1Galileo_2->currentIndex()==0 ) ui->comboBoxSmoothPhase1Galileo_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothWithGalileo_3_currentIndexChanged(int index){
    ui->comboBoxSmoothWithGalileo_3->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithGalileo_3->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(Galileo,THIRDMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithGalileo_3->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2Galileo_3->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2Galileo_3->setHidden(false);

    this->setSmoothWithFreqAll(Galileo,THIRDMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1Galileo_3->setHidden(false); //GC
    else ui->frameSmoothCode1Galileo_3->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1Galileo_3_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[Galileo][THIRDMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1Galileo_3->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(Galileo,THIRDMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1Galileo_3->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1Galileo_3->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGalileo_3->currentIndex()>2 && ui->comboBoxSmoothFreq2Galileo_3->currentIndex()==index){
        ui->comboBoxSmoothFreq2Galileo_3->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[Galileo][THIRDMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2Galileo_3_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[Galileo][THIRDMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2Galileo_3->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(Galileo,THIRDMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2Galileo_3->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGalileo_3->currentIndex()>2 && ui->comboBoxSmoothFreq1Galileo_3->currentIndex()==index){
        ui->comboBoxSmoothFreq1Galileo_3->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[Galileo][THIRDMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1Galileo_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1Galileo_3->count()>0) ui->comboBoxSmoothCode1Galileo_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1Galileo_3->count()>0) ui->comboBoxSmoothPhase1Galileo_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2Galileo_3->count()>0) ui->comboBoxSmoothPhase2Galileo_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1Galileo_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1Galileo_3->count()>0 && ui->comboBoxSmoothPhase1Galileo_3->currentIndex()==0 ) ui->comboBoxSmoothPhase1Galileo_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2Galileo_3->count()>0 && ui->comboBoxSmoothPhase2Galileo_3->currentIndex()==0 ) ui->comboBoxSmoothPhase2Galileo_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1Galileo_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1Galileo_3->count()>0) ui->comboBoxSmoothCode1Galileo_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1Galileo_3->count()>0) ui->comboBoxSmoothPhase1Galileo_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2Galileo_3->count()>0) ui->comboBoxSmoothPhase2Galileo_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1Galileo_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1Galileo_3->count()>0 && ui->comboBoxSmoothCode1Galileo_3->currentIndex()==0 ) ui->comboBoxSmoothCode1Galileo_3->setCurrentIndex(index>=ui->comboBoxSmoothCode1Galileo_3->count()?1:index);
        if ( ui->comboBoxSmoothPhase2Galileo_3->count()>0 && ui->comboBoxSmoothPhase2Galileo_3->currentIndex()==0 ) ui->comboBoxSmoothPhase2Galileo_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2Galileo_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1Galileo_3->count()>0) ui->comboBoxSmoothCode1Galileo_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1Galileo_3->count()>0) ui->comboBoxSmoothPhase1Galileo_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2Galileo_3->count()>0) ui->comboBoxSmoothPhase2Galileo_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2Galileo_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1Galileo_3->count()>0 && ui->comboBoxSmoothCode1Galileo_3->currentIndex()==0 ) ui->comboBoxSmoothCode1Galileo_3->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1Galileo_3->count()>0 && ui->comboBoxSmoothPhase1Galileo_3->currentIndex()==0 ) ui->comboBoxSmoothPhase1Galileo_3->setCurrentIndex(1);
    }
}

// For GLONASS
void gLAB_GUI::on_comboBoxFreqCodeGLONASS_1_currentIndexChanged(int index){
    ui->comboBoxFreqCodeGLONASS_1->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GLONASS,FIRSTMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeGLONASS_1->setEnabled(false);
            ui->lineEditStdDevCodeAGLONASS_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GLONASS,FIRSTMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeGLONASS_1->setEnabled(true);
            ui->lineEditStdDevCodeAGLONASS_1->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1GLONASS_1->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseGLONASS_1_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseGLONASS_1->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GLONASS,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseGLONASS_1->setEnabled(false);
            ui->lineEditStdDevPhaseAGLONASS_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GLONASS,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseGLONASS_1->setEnabled(true);
            ui->lineEditStdDevPhaseAGLONASS_1->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1GLONASS_1->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCGLONASS_1_currentIndexChanged(int index){
    ui->comboBoxFreqGCGLONASS_1->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCGLONASS_1->setEnabled(false);
            ui->lineEditStdDevGCAGLONASS_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GLONASS,FIRSTMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCGLONASS_1->setEnabled(true);
            ui->lineEditStdDevGCAGLONASS_1->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeGLONASS_1->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1GLONASS_1_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1GLONASS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2GLONASS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2GLONASS_1->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2GLONASS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2GLONASS_1_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2GLONASS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1GLONASS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1GLONASS_1->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1GLONASS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1GLONASS_1_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1GLONASS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2GLONASS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2GLONASS_1->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2GLONASS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2GLONASS_1_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2GLONASS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1GLONASS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1GLONASS_1->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1GLONASS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeGLONASS_1_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeGLONASS_1->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseGLONASS_1->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseGLONASS_1->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseGLONASS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseGLONASS_1_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseGLONASS_1->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeGLONASS_1->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeGLONASS_1->currentIndex()==0) {
        ui->comboBoxMeasGCCodeGLONASS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeGLONASS_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeGLONASS_1->setCurrentIndex(index);
    this->setWeightTypeValues(GLONASS,FIRSTMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBGLONASS_1->setHidden(true);
        ui->frameCodeCGLONASS_1->setHidden(true);
        ui->labelStdDevCodeAUnitGLONASS_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitGLONASS_1->setText("(m)");
        ui->labelStdDevCodeBUnitGLONASS_1->setText("(m)");
        ui->frameCodeBGLONASS_1->setHidden(false);
        ui->frameCodeCGLONASS_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCGLONASS_1->setHidden(true);
        ui->frameCodeBGLONASS_1->setHidden(false);
        ui->labelStdDevCodeAUnitGLONASS_1->setText("(m²)");
        ui->labelStdDevCodeBUnitGLONASS_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCGLONASS_1->setHidden(true);
        ui->frameCodeBGLONASS_1->setHidden(false);
        ui->labelStdDevCodeAUnitGLONASS_1->setText("(m²)");
        ui->labelStdDevCodeBUnitGLONASS_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseGLONASS_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseGLONASS_1->setCurrentIndex(index);
    this->setWeightTypeValues(GLONASS,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBGLONASS_1->setHidden(true);
        ui->framePhaseCGLONASS_1->setHidden(true);
        ui->labelStdDevPhaseAUnitGLONASS_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitGLONASS_1->setText("(m)");
        ui->labelStdDevPhaseBUnitGLONASS_1->setText("(m)");
        ui->framePhaseBGLONASS_1->setHidden(false);
        ui->framePhaseCGLONASS_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCGLONASS_1->setHidden(true);
        ui->framePhaseBGLONASS_1->setHidden(false);
        ui->labelStdDevPhaseAUnitGLONASS_1->setText("(m²)");
        ui->labelStdDevPhaseBUnitGLONASS_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCGLONASS_1->setHidden(true);
        ui->framePhaseBGLONASS_1->setHidden(false);
        ui->labelStdDevPhaseAUnitGLONASS_1->setText("(m²)");
        ui->labelStdDevPhaseBUnitGLONASS_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCGLONASS_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCGLONASS_1->setCurrentIndex(index);
    this->setWeightTypeValues(GLONASS,FIRSTMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBGLONASS_1->setHidden(true);
        ui->frameGCCGLONASS_1->setHidden(true);
        ui->labelStdDevGCAUnitGLONASS_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitGLONASS_1->setText("(m)");
        ui->labelStdDevGCBUnitGLONASS_1->setText("(m)");
        ui->frameGCBGLONASS_1->setHidden(false);
        ui->frameGCCGLONASS_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCGLONASS_1->setHidden(true);
        ui->frameGCBGLONASS_1->setHidden(false);
        ui->labelStdDevGCAUnitGLONASS_1->setText("(m²)");
        ui->labelStdDevGCBUnitGLONASS_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCGLONASS_1->setHidden(true);
        ui->frameGCBGLONASS_1->setHidden(false);
        ui->labelStdDevGCAUnitGLONASS_1->setText("(m²)");
        ui->labelStdDevGCBUnitGLONASS_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxFreqCodeGLONASS_2_currentIndexChanged(int index){
    ui->comboBoxFreqCodeGLONASS_2->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GLONASS,SECONDMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeGLONASS_2->setEnabled(false);
            ui->lineEditStdDevCodeAGLONASS_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GLONASS,SECONDMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeGLONASS_2->setEnabled(true);
            ui->lineEditStdDevCodeAGLONASS_2->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1GLONASS_2->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseGLONASS_2_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseGLONASS_2->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GLONASS,SECONDMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseGLONASS_2->setEnabled(false);
            ui->lineEditStdDevPhaseAGLONASS_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GLONASS,SECONDMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseGLONASS_2->setEnabled(true);
            ui->lineEditStdDevPhaseAGLONASS_2->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1GLONASS_2->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCGLONASS_2_currentIndexChanged(int index){
    ui->comboBoxFreqGCGLONASS_2->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCGLONASS_2->setEnabled(false);
            ui->lineEditStdDevGCAGLONASS_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GLONASS,SECONDMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCGLONASS_2->setEnabled(true);
            ui->lineEditStdDevGCAGLONASS_2->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeGLONASS_1->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1GLONASS_2_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1GLONASS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2GLONASS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2GLONASS_2->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2GLONASS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2GLONASS_2_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2GLONASS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1GLONASS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1GLONASS_2->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1GLONASS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1GLONASS_2_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1GLONASS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2GLONASS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2GLONASS_2->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2GLONASS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2GLONASS_2_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2GLONASS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1GLONASS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1GLONASS_2->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1GLONASS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeGLONASS_2_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeGLONASS_2->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseGLONASS_2->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseGLONASS_2->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseGLONASS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseGLONASS_2_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseGLONASS_2->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeGLONASS_2->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeGLONASS_2->currentIndex()==0) {
        ui->comboBoxMeasGCCodeGLONASS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeGLONASS_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeGLONASS_2->setCurrentIndex(index);
    this->setWeightTypeValues(GLONASS,SECONDMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBGLONASS_2->setHidden(true);
        ui->frameCodeCGLONASS_2->setHidden(true);
        ui->labelStdDevCodeAUnitGLONASS_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitGLONASS_2->setText("(m)");
        ui->labelStdDevCodeBUnitGLONASS_2->setText("(m)");
        ui->frameCodeBGLONASS_2->setHidden(false);
        ui->frameCodeCGLONASS_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCGLONASS_2->setHidden(true);
        ui->frameCodeBGLONASS_2->setHidden(false);
        ui->labelStdDevCodeAUnitGLONASS_2->setText("(m²)");
        ui->labelStdDevCodeBUnitGLONASS_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCGLONASS_2->setHidden(true);
        ui->frameCodeBGLONASS_2->setHidden(false);
        ui->labelStdDevCodeAUnitGLONASS_2->setText("(m²)");
        ui->labelStdDevCodeBUnitGLONASS_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseGLONASS_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseGLONASS_2->setCurrentIndex(index);
    this->setWeightTypeValues(GLONASS,SECONDMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBGLONASS_2->setHidden(true);
        ui->framePhaseCGLONASS_2->setHidden(true);
        ui->labelStdDevPhaseAUnitGLONASS_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitGLONASS_2->setText("(m)");
        ui->labelStdDevPhaseBUnitGLONASS_2->setText("(m)");
        ui->framePhaseBGLONASS_2->setHidden(false);
        ui->framePhaseCGLONASS_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCGLONASS_2->setHidden(true);
        ui->framePhaseBGLONASS_2->setHidden(false);
        ui->labelStdDevPhaseAUnitGLONASS_2->setText("(m²)");
        ui->labelStdDevPhaseBUnitGLONASS_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCGLONASS_2->setHidden(true);
        ui->framePhaseBGLONASS_2->setHidden(false);
        ui->labelStdDevPhaseAUnitGLONASS_2->setText("(m²)");
        ui->labelStdDevPhaseBUnitGLONASS_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCGLONASS_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCGLONASS_2->setCurrentIndex(index);
    this->setWeightTypeValues(GLONASS,SECONDMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBGLONASS_2->setHidden(true);
        ui->frameGCCGLONASS_2->setHidden(true);
        ui->labelStdDevGCAUnitGLONASS_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitGLONASS_2->setText("(m)");
        ui->labelStdDevGCBUnitGLONASS_2->setText("(m)");
        ui->frameGCBGLONASS_2->setHidden(false);
        ui->frameGCCGLONASS_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCGLONASS_2->setHidden(true);
        ui->frameGCBGLONASS_2->setHidden(false);
        ui->labelStdDevGCAUnitGLONASS_2->setText("(m²)");
        ui->labelStdDevGCBUnitGLONASS_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCGLONASS_2->setHidden(true);
        ui->frameGCBGLONASS_2->setHidden(false);
        ui->labelStdDevGCAUnitGLONASS_2->setText("(m²)");
        ui->labelStdDevGCBUnitGLONASS_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxFreqCodeGLONASS_3_currentIndexChanged(int index){
    ui->comboBoxFreqCodeGLONASS_3->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GLONASS,THIRDMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeGLONASS_3->setEnabled(false);
            ui->lineEditStdDevCodeAGLONASS_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GLONASS,THIRDMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeGLONASS_3->setEnabled(true);
            ui->lineEditStdDevCodeAGLONASS_3->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1GLONASS_3->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseGLONASS_3_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseGLONASS_3->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GLONASS,THIRDMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseGLONASS_3->setEnabled(false);
            ui->lineEditStdDevPhaseAGLONASS_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GLONASS,THIRDMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseGLONASS_3->setEnabled(true);
            ui->lineEditStdDevPhaseAGLONASS_3->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1GLONASS_3->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCGLONASS_3_currentIndexChanged(int index){
    ui->comboBoxFreqGCGLONASS_3->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCGLONASS_3->setEnabled(false);
            ui->lineEditStdDevGCAGLONASS_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GLONASS,THIRDMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCGLONASS_3->setEnabled(true);
            ui->lineEditStdDevGCAGLONASS_3->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeGLONASS_3->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1GLONASS_3_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1GLONASS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2GLONASS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2GLONASS_3->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2GLONASS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2GLONASS_3_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2GLONASS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1GLONASS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1GLONASS_3->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1GLONASS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1GLONASS_3_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1GLONASS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2GLONASS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2GLONASS_3->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2GLONASS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2GLONASS_3_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2GLONASS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1GLONASS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1GLONASS_3->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1GLONASS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeGLONASS_3_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeGLONASS_3->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseGLONASS_3->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseGLONASS_3->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseGLONASS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseGLONASS_3_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseGLONASS_3->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeGLONASS_3->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeGLONASS_3->currentIndex()==0) {
        ui->comboBoxMeasGCCodeGLONASS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeGLONASS_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeGLONASS_3->setCurrentIndex(index);
    this->setWeightTypeValues(GLONASS,THIRDMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBGLONASS_3->setHidden(true);
        ui->frameCodeCGLONASS_3->setHidden(true);
        ui->labelStdDevCodeAUnitGLONASS_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitGLONASS_3->setText("(m)");
        ui->labelStdDevCodeBUnitGLONASS_3->setText("(m)");
        ui->frameCodeBGLONASS_3->setHidden(false);
        ui->frameCodeCGLONASS_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCGLONASS_3->setHidden(true);
        ui->frameCodeBGLONASS_3->setHidden(false);
        ui->labelStdDevCodeAUnitGLONASS_3->setText("(m²)");
        ui->labelStdDevCodeBUnitGLONASS_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCGLONASS_3->setHidden(true);
        ui->frameCodeBGLONASS_3->setHidden(false);
        ui->labelStdDevCodeAUnitGLONASS_3->setText("(m²)");
        ui->labelStdDevCodeBUnitGLONASS_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseGLONASS_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseGLONASS_3->setCurrentIndex(index);
    this->setWeightTypeValues(GLONASS,THIRDMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBGLONASS_3->setHidden(true);
        ui->framePhaseCGLONASS_3->setHidden(true);
        ui->labelStdDevPhaseAUnitGLONASS_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitGLONASS_3->setText("(m)");
        ui->labelStdDevPhaseBUnitGLONASS_3->setText("(m)");
        ui->framePhaseBGLONASS_3->setHidden(false);
        ui->framePhaseCGLONASS_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCGLONASS_3->setHidden(true);
        ui->framePhaseBGLONASS_3->setHidden(false);
        ui->labelStdDevPhaseAUnitGLONASS_3->setText("(m²)");
        ui->labelStdDevPhaseBUnitGLONASS_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCGLONASS_3->setHidden(true);
        ui->framePhaseBGLONASS_3->setHidden(false);
        ui->labelStdDevPhaseAUnitGLONASS_3->setText("(m²)");
        ui->labelStdDevPhaseBUnitGLONASS_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCGLONASS_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCGLONASS_3->setCurrentIndex(index);
    this->setWeightTypeValues(GLONASS,THIRDMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBGLONASS_3->setHidden(true);
        ui->frameGCCGLONASS_3->setHidden(true);
        ui->labelStdDevGCAUnitGLONASS_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitGLONASS_3->setText("(m)");
        ui->labelStdDevGCBUnitGLONASS_3->setText("(m)");
        ui->frameGCBGLONASS_3->setHidden(false);
        ui->frameGCCGLONASS_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCGLONASS_3->setHidden(true);
        ui->frameGCBGLONASS_3->setHidden(false);
        ui->labelStdDevGCAUnitGLONASS_3->setText("(m²)");
        ui->labelStdDevGCBUnitGLONASS_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCGLONASS_3->setHidden(true);
        ui->frameGCBGLONASS_3->setHidden(false);
        ui->labelStdDevGCAUnitGLONASS_3->setText("(m²)");
        ui->labelStdDevGCBUnitGLONASS_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxSmoothWithGLONASS_1_currentIndexChanged(int index){
    ui->comboBoxSmoothWithGLONASS_1->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithGLONASS_1->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(GLONASS,FIRSTMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithGLONASS_1->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2GLONASS_1->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2GLONASS_1->setHidden(false);

    this->setSmoothWithFreqAll(GLONASS,FIRSTMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1GLONASS_1->setHidden(false); //GC
    else ui->frameSmoothCode1GLONASS_1->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1GLONASS_1_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GLONASS][FIRSTMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1GLONASS_1->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(GLONASS,FIRSTMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1GLONASS_1->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1GLONASS_1->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGLONASS_1->currentIndex()>2 && ui->comboBoxSmoothFreq2GLONASS_1->currentIndex()==index){
        ui->comboBoxSmoothFreq2GLONASS_1->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[GLONASS][FIRSTMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2GLONASS_1_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GLONASS][FIRSTMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2GLONASS_1->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(GLONASS,FIRSTMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2GLONASS_1->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGLONASS_1->currentIndex()>2 && ui->comboBoxSmoothFreq1GLONASS_1->currentIndex()==index){
        ui->comboBoxSmoothFreq1GLONASS_1->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[GLONASS][FIRSTMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1GLONASS_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GLONASS_1->count()>0) ui->comboBoxSmoothCode1GLONASS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GLONASS_1->count()>0) ui->comboBoxSmoothPhase1GLONASS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GLONASS_1->count()>0) ui->comboBoxSmoothPhase2GLONASS_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1GLONASS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1GLONASS_1->count()>0 && ui->comboBoxSmoothPhase1GLONASS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase1GLONASS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2GLONASS_1->count()>0 && ui->comboBoxSmoothPhase2GLONASS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase2GLONASS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1GLONASS_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GLONASS_1->count()>0) ui->comboBoxSmoothCode1GLONASS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GLONASS_1->count()>0) ui->comboBoxSmoothPhase1GLONASS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GLONASS_1->count()>0) ui->comboBoxSmoothPhase2GLONASS_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1GLONASS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GLONASS_1->count()>0 && ui->comboBoxSmoothCode1GLONASS_1->currentIndex()==0 ) ui->comboBoxSmoothCode1GLONASS_1->setCurrentIndex(index>=ui->comboBoxSmoothCode1GLONASS_1->count()?1:index);
        if ( ui->comboBoxSmoothPhase2GLONASS_1->count()>0 && ui->comboBoxSmoothPhase2GLONASS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase2GLONASS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2GLONASS_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GLONASS_1->count()>0) ui->comboBoxSmoothCode1GLONASS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GLONASS_1->count()>0) ui->comboBoxSmoothPhase1GLONASS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GLONASS_1->count()>0) ui->comboBoxSmoothPhase2GLONASS_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2GLONASS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GLONASS_1->count()>0 && ui->comboBoxSmoothCode1GLONASS_1->currentIndex()==0 ) ui->comboBoxSmoothCode1GLONASS_1->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1GLONASS_1->count()>0 && ui->comboBoxSmoothPhase1GLONASS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase1GLONASS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothWithGLONASS_2_currentIndexChanged(int index){
    ui->comboBoxSmoothWithGLONASS_2->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithGLONASS_2->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(GLONASS,SECONDMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithGLONASS_2->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2GLONASS_2->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2GLONASS_2->setHidden(false);

    this->setSmoothWithFreqAll(GLONASS,SECONDMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1GLONASS_2->setHidden(false); //GC
    else ui->frameSmoothCode1GLONASS_2->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1GLONASS_2_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GLONASS][SECONDMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1GLONASS_2->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(GLONASS,SECONDMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1GLONASS_2->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1GLONASS_2->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGLONASS_2->currentIndex()>2 && ui->comboBoxSmoothFreq2GLONASS_2->currentIndex()==index){
        ui->comboBoxSmoothFreq2GLONASS_2->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[GLONASS][SECONDMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2GLONASS_2_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GLONASS][SECONDMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2GLONASS_2->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(GLONASS,SECONDMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2GLONASS_2->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGLONASS_2->currentIndex()>2 && ui->comboBoxSmoothFreq1GLONASS_2->currentIndex()==index){
        ui->comboBoxSmoothFreq1GLONASS_2->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[GLONASS][SECONDMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1GLONASS_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GLONASS_2->count()>0) ui->comboBoxSmoothCode1GLONASS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GLONASS_2->count()>0) ui->comboBoxSmoothPhase1GLONASS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GLONASS_2->count()>0) ui->comboBoxSmoothPhase2GLONASS_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1GLONASS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1GLONASS_2->count()>0 && ui->comboBoxSmoothPhase1GLONASS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase1GLONASS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2GLONASS_2->count()>0 && ui->comboBoxSmoothPhase2GLONASS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase2GLONASS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1GLONASS_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GLONASS_2->count()>0) ui->comboBoxSmoothCode1GLONASS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GLONASS_2->count()>0) ui->comboBoxSmoothPhase1GLONASS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GLONASS_2->count()>0) ui->comboBoxSmoothPhase2GLONASS_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1GLONASS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GLONASS_2->count()>0 && ui->comboBoxSmoothCode1GLONASS_2->currentIndex()==0 ) ui->comboBoxSmoothCode1GLONASS_2->setCurrentIndex(index>=ui->comboBoxSmoothCode1GLONASS_2->count()?1:index);
        if ( ui->comboBoxSmoothPhase2GLONASS_2->count()>0 && ui->comboBoxSmoothPhase2GLONASS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase2GLONASS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2GLONASS_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GLONASS_2->count()>0) ui->comboBoxSmoothCode1GLONASS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GLONASS_2->count()>0) ui->comboBoxSmoothPhase1GLONASS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GLONASS_2->count()>0) ui->comboBoxSmoothPhase2GLONASS_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2GLONASS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GLONASS_2->count()>0 && ui->comboBoxSmoothCode1GLONASS_2->currentIndex()==0 ) ui->comboBoxSmoothCode1GLONASS_2->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1GLONASS_2->count()>0 && ui->comboBoxSmoothPhase1GLONASS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase1GLONASS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothWithGLONASS_3_currentIndexChanged(int index){
    ui->comboBoxSmoothWithGLONASS_3->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithGLONASS_3->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(GLONASS,THIRDMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithGLONASS_3->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2GLONASS_3->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2GLONASS_3->setHidden(false);

    this->setSmoothWithFreqAll(GLONASS,THIRDMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1GLONASS_3->setHidden(false); //GC
    else ui->frameSmoothCode1GLONASS_3->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1GLONASS_3_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GLONASS][THIRDMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1GLONASS_3->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(GLONASS,THIRDMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1GLONASS_3->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1GLONASS_3->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGLONASS_3->currentIndex()>2 && ui->comboBoxSmoothFreq2GLONASS_3->currentIndex()==index){
        ui->comboBoxSmoothFreq2GLONASS_3->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[GLONASS][THIRDMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2GLONASS_3_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GLONASS][THIRDMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2GLONASS_3->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(GLONASS,THIRDMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2GLONASS_3->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGLONASS_3->currentIndex()>2 && ui->comboBoxSmoothFreq1GLONASS_3->currentIndex()==index){
        ui->comboBoxSmoothFreq1GLONASS_3->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[GLONASS][THIRDMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1GLONASS_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GLONASS_3->count()>0) ui->comboBoxSmoothCode1GLONASS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GLONASS_3->count()>0) ui->comboBoxSmoothPhase1GLONASS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GLONASS_3->count()>0) ui->comboBoxSmoothPhase2GLONASS_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1GLONASS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1GLONASS_3->count()>0 && ui->comboBoxSmoothPhase1GLONASS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase1GLONASS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2GLONASS_3->count()>0 && ui->comboBoxSmoothPhase2GLONASS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase2GLONASS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1GLONASS_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GLONASS_3->count()>0) ui->comboBoxSmoothCode1GLONASS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GLONASS_3->count()>0) ui->comboBoxSmoothPhase1GLONASS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GLONASS_3->count()>0) ui->comboBoxSmoothPhase2GLONASS_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1GLONASS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GLONASS_3->count()>0 && ui->comboBoxSmoothCode1GLONASS_3->currentIndex()==0 ) ui->comboBoxSmoothCode1GLONASS_3->setCurrentIndex(index>=ui->comboBoxSmoothCode1GLONASS_3->count()?1:index);
        if ( ui->comboBoxSmoothPhase2GLONASS_3->count()>0 && ui->comboBoxSmoothPhase2GLONASS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase2GLONASS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2GLONASS_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GLONASS_3->count()>0) ui->comboBoxSmoothCode1GLONASS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GLONASS_3->count()>0) ui->comboBoxSmoothPhase1GLONASS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GLONASS_3->count()>0) ui->comboBoxSmoothPhase2GLONASS_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2GLONASS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GLONASS_3->count()>0 && ui->comboBoxSmoothCode1GLONASS_3->currentIndex()==0 ) ui->comboBoxSmoothCode1GLONASS_3->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1GLONASS_3->count()>0 && ui->comboBoxSmoothPhase1GLONASS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase1GLONASS_3->setCurrentIndex(1);
    }
}

// For GEO
void gLAB_GUI::on_comboBoxFreqCodeGEO_1_currentIndexChanged(int index){
    ui->comboBoxFreqCodeGEO_1->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GEO,FIRSTMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeGEO_1->setEnabled(false);
            ui->lineEditStdDevCodeAGEO_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GEO,FIRSTMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeGEO_1->setEnabled(true);
            ui->lineEditStdDevCodeAGEO_1->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1GEO_1->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseGEO_1_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseGEO_1->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GEO,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseGEO_1->setEnabled(false);
            ui->lineEditStdDevPhaseAGEO_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GEO,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseGEO_1->setEnabled(true);
            ui->lineEditStdDevPhaseAGEO_1->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1GEO_1->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCGEO_1_currentIndexChanged(int index){
    ui->comboBoxFreqGCGEO_1->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCGEO_1->setEnabled(false);
            ui->lineEditStdDevGCAGEO_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GEO,FIRSTMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCGEO_1->setEnabled(true);
            ui->lineEditStdDevGCAGEO_1->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeGEO_1->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1GEO_1_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1GEO_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2GEO_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2GEO_1->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2GEO_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2GEO_1_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2GEO_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1GEO_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1GEO_1->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1GEO_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1GEO_1_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1GEO_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2GEO_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2GEO_1->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2GEO_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2GEO_1_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2GEO_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1GEO_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1GEO_1->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1GEO_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeGEO_1_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeGEO_1->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseGEO_1->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseGEO_1->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseGEO_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseGEO_1_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseGEO_1->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeGEO_1->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeGEO_1->currentIndex()==0) {
        ui->comboBoxMeasGCCodeGEO_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeGEO_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeGEO_1->setCurrentIndex(index);
    this->setWeightTypeValues(GEO,FIRSTMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBGEO_1->setHidden(true);
        ui->frameCodeCGEO_1->setHidden(true);
        ui->labelStdDevCodeAUnitGEO_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitGEO_1->setText("(m)");
        ui->labelStdDevCodeBUnitGEO_1->setText("(m)");
        ui->frameCodeBGEO_1->setHidden(false);
        ui->frameCodeCGEO_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCGEO_1->setHidden(true);
        ui->frameCodeBGEO_1->setHidden(false);
        ui->labelStdDevCodeAUnitGEO_1->setText("(m²)");
        ui->labelStdDevCodeBUnitGEO_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCGEO_1->setHidden(true);
        ui->frameCodeBGEO_1->setHidden(false);
        ui->labelStdDevCodeAUnitGEO_1->setText("(m²)");
        ui->labelStdDevCodeBUnitGEO_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseGEO_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseGEO_1->setCurrentIndex(index);
    this->setWeightTypeValues(GEO,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBGEO_1->setHidden(true);
        ui->framePhaseCGEO_1->setHidden(true);
        ui->labelStdDevPhaseAUnitGEO_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitGEO_1->setText("(m)");
        ui->labelStdDevPhaseBUnitGEO_1->setText("(m)");
        ui->framePhaseBGEO_1->setHidden(false);
        ui->framePhaseCGEO_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCGEO_1->setHidden(true);
        ui->framePhaseBGEO_1->setHidden(false);
        ui->labelStdDevPhaseAUnitGEO_1->setText("(m²)");
        ui->labelStdDevPhaseBUnitGEO_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCGEO_1->setHidden(true);
        ui->framePhaseBGEO_1->setHidden(false);
        ui->labelStdDevPhaseAUnitGEO_1->setText("(m²)");
        ui->labelStdDevPhaseBUnitGEO_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCGEO_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCGEO_1->setCurrentIndex(index);
    this->setWeightTypeValues(GEO,FIRSTMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBGEO_1->setHidden(true);
        ui->frameGCCGEO_1->setHidden(true);
        ui->labelStdDevGCAUnitGEO_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitGEO_1->setText("(m)");
        ui->labelStdDevGCBUnitGEO_1->setText("(m)");
        ui->frameGCBGEO_1->setHidden(false);
        ui->frameGCCGEO_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCGEO_1->setHidden(true);
        ui->frameGCBGEO_1->setHidden(false);
        ui->labelStdDevGCAUnitGEO_1->setText("(m²)");
        ui->labelStdDevGCBUnitGEO_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCGEO_1->setHidden(true);
        ui->frameGCBGEO_1->setHidden(false);
        ui->labelStdDevGCAUnitGEO_1->setText("(m²)");
        ui->labelStdDevGCBUnitGEO_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxFreqCodeGEO_2_currentIndexChanged(int index){
    ui->comboBoxFreqCodeGEO_2->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GEO,SECONDMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeGEO_2->setEnabled(false);
            ui->lineEditStdDevCodeAGEO_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GEO,SECONDMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeGEO_2->setEnabled(true);
            ui->lineEditStdDevCodeAGEO_2->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1GEO_2->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseGEO_2_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseGEO_2->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GEO,SECONDMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseGEO_2->setEnabled(false);
            ui->lineEditStdDevPhaseAGEO_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GEO,SECONDMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseGEO_2->setEnabled(true);
            ui->lineEditStdDevPhaseAGEO_2->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1GEO_2->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCGEO_2_currentIndexChanged(int index){
    ui->comboBoxFreqGCGEO_2->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCGEO_2->setEnabled(false);
            ui->lineEditStdDevGCAGEO_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GEO,SECONDMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCGEO_2->setEnabled(true);
            ui->lineEditStdDevGCAGEO_2->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeGEO_2->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1GEO_2_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1GEO_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2GEO_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2GEO_2->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2GEO_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2GEO_2_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2GEO_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1GEO_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1GEO_2->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1GEO_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1GEO_2_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1GEO_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2GEO_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2GEO_2->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2GEO_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2GEO_2_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2GEO_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1GEO_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1GEO_2->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1GEO_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeGEO_2_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeGEO_2->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseGEO_2->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseGEO_2->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseGEO_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseGEO_2_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseGEO_2->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeGEO_2->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeGEO_2->currentIndex()==0) {
        ui->comboBoxMeasGCCodeGEO_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeGEO_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeGEO_2->setCurrentIndex(index);
    this->setWeightTypeValues(GEO,SECONDMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBGEO_2->setHidden(true);
        ui->frameCodeCGEO_2->setHidden(true);
        ui->labelStdDevCodeAUnitGEO_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitGEO_2->setText("(m)");
        ui->labelStdDevCodeBUnitGEO_2->setText("(m)");
        ui->frameCodeBGEO_2->setHidden(false);
        ui->frameCodeCGEO_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCGEO_2->setHidden(true);
        ui->frameCodeBGEO_2->setHidden(false);
        ui->labelStdDevCodeAUnitGEO_2->setText("(m²)");
        ui->labelStdDevCodeBUnitGEO_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCGEO_2->setHidden(true);
        ui->frameCodeBGEO_2->setHidden(false);
        ui->labelStdDevCodeAUnitGEO_2->setText("(m²)");
        ui->labelStdDevCodeBUnitGEO_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseGEO_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseGEO_2->setCurrentIndex(index);
    this->setWeightTypeValues(GEO,SECONDMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBGEO_2->setHidden(true);
        ui->framePhaseCGEO_2->setHidden(true);
        ui->labelStdDevPhaseAUnitGEO_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitGEO_2->setText("(m)");
        ui->labelStdDevPhaseBUnitGEO_2->setText("(m)");
        ui->framePhaseBGEO_2->setHidden(false);
        ui->framePhaseCGEO_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCGEO_2->setHidden(true);
        ui->framePhaseBGEO_2->setHidden(false);
        ui->labelStdDevPhaseAUnitGEO_2->setText("(m²)");
        ui->labelStdDevPhaseBUnitGEO_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCGEO_2->setHidden(true);
        ui->framePhaseBGEO_2->setHidden(false);
        ui->labelStdDevPhaseAUnitGEO_2->setText("(m²)");
        ui->labelStdDevPhaseBUnitGEO_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCGEO_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCGEO_2->setCurrentIndex(index);
    this->setWeightTypeValues(GEO,SECONDMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBGEO_2->setHidden(true);
        ui->frameGCCGEO_2->setHidden(true);
        ui->labelStdDevGCAUnitGEO_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitGEO_2->setText("(m)");
        ui->labelStdDevGCBUnitGEO_2->setText("(m)");
        ui->frameGCBGEO_2->setHidden(false);
        ui->frameGCCGEO_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCGEO_2->setHidden(true);
        ui->frameGCBGEO_2->setHidden(false);
        ui->labelStdDevGCAUnitGEO_2->setText("(m²)");
        ui->labelStdDevGCBUnitGEO_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCGEO_2->setHidden(true);
        ui->frameGCBGEO_2->setHidden(false);
        ui->labelStdDevGCAUnitGEO_2->setText("(m²)");
        ui->labelStdDevGCBUnitGEO_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxFreqCodeGEO_3_currentIndexChanged(int index){
    ui->comboBoxFreqCodeGEO_3->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GEO,THIRDMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeGEO_3->setEnabled(false);
            ui->lineEditStdDevCodeAGEO_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GEO,THIRDMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeGEO_3->setEnabled(true);
            ui->lineEditStdDevCodeAGEO_3->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1GEO_3->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseGEO_3_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseGEO_3->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(GEO,THIRDMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseGEO_3->setEnabled(false);
            ui->lineEditStdDevPhaseAGEO_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GEO,THIRDMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseGEO_3->setEnabled(true);
            ui->lineEditStdDevPhaseAGEO_3->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1GEO_3->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCGEO_3_currentIndexChanged(int index){
    ui->comboBoxFreqGCGEO_3->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCGEO_3->setEnabled(false);
            ui->lineEditStdDevGCAGEO_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(GEO,THIRDMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCGEO_3->setEnabled(true);
            ui->lineEditStdDevGCAGEO_3->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeGEO_3->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1GEO_3_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1GEO_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2GEO_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2GEO_3->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2GEO_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2GEO_3_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2GEO_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1GEO_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1GEO_3->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1GEO_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1GEO_3_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1GEO_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2GEO_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2GEO_3->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2GEO_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2GEO_3_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2GEO_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1GEO_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1GEO_3->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1GEO_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeGEO_3_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeGEO_3->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseGEO_3->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseGEO_3->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseGEO_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseGEO_3_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseGEO_3->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeGEO_3->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeGEO_3->currentIndex()==0) {
        ui->comboBoxMeasGCCodeGEO_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeGEO_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeGEO_3->setCurrentIndex(index);
    this->setWeightTypeValues(GEO,THIRDMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBGEO_3->setHidden(true);
        ui->frameCodeCGEO_3->setHidden(true);
        ui->labelStdDevCodeAUnitGEO_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitGEO_3->setText("(m)");
        ui->labelStdDevCodeBUnitGEO_3->setText("(m)");
        ui->frameCodeBGEO_3->setHidden(false);
        ui->frameCodeCGEO_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCGEO_3->setHidden(true);
        ui->frameCodeBGEO_3->setHidden(false);
        ui->labelStdDevCodeAUnitGEO_3->setText("(m²)");
        ui->labelStdDevCodeBUnitGEO_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCGEO_3->setHidden(true);
        ui->frameCodeBGEO_3->setHidden(false);
        ui->labelStdDevCodeAUnitGEO_3->setText("(m²)");
        ui->labelStdDevCodeBUnitGEO_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseGEO_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseGEO_3->setCurrentIndex(index);
    this->setWeightTypeValues(GEO,THIRDMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBGEO_3->setHidden(true);
        ui->framePhaseCGEO_3->setHidden(true);
        ui->labelStdDevPhaseAUnitGEO_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitGEO_3->setText("(m)");
        ui->labelStdDevPhaseBUnitGEO_3->setText("(m)");
        ui->framePhaseBGEO_3->setHidden(false);
        ui->framePhaseCGEO_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCGEO_3->setHidden(true);
        ui->framePhaseBGEO_3->setHidden(false);
        ui->labelStdDevPhaseAUnitGEO_3->setText("(m²)");
        ui->labelStdDevPhaseBUnitGEO_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCGEO_3->setHidden(true);
        ui->framePhaseBGEO_3->setHidden(false);
        ui->labelStdDevPhaseAUnitGEO_3->setText("(m²)");
        ui->labelStdDevPhaseBUnitGEO_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCGEO_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCGEO_3->setCurrentIndex(index);
    this->setWeightTypeValues(GEO,THIRDMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBGEO_3->setHidden(true);
        ui->frameGCCGEO_3->setHidden(true);
        ui->labelStdDevGCAUnitGEO_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitGEO_3->setText("(m)");
        ui->labelStdDevGCBUnitGEO_3->setText("(m)");
        ui->frameGCBGEO_3->setHidden(false);
        ui->frameGCCGEO_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCGEO_3->setHidden(true);
        ui->frameGCBGEO_3->setHidden(false);
        ui->labelStdDevGCAUnitGEO_3->setText("(m²)");
        ui->labelStdDevGCBUnitGEO_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCGEO_3->setHidden(true);
        ui->frameGCBGEO_3->setHidden(false);
        ui->labelStdDevGCAUnitGEO_3->setText("(m²)");
        ui->labelStdDevGCBUnitGEO_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxSmoothWithGEO_1_currentIndexChanged(int index){
    ui->comboBoxSmoothWithGEO_1->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithGEO_1->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(GEO,FIRSTMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithGEO_1->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2GEO_1->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2GEO_1->setHidden(false);

    this->setSmoothWithFreqAll(GEO,FIRSTMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1GEO_1->setHidden(false); //GC
    else ui->frameSmoothCode1GEO_1->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1GEO_1_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GEO][FIRSTMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1GEO_1->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(GEO,FIRSTMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1GEO_1->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1GEO_1->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGEO_1->currentIndex()>2 && ui->comboBoxSmoothFreq2GEO_1->currentIndex()==index){
        ui->comboBoxSmoothFreq2GEO_1->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[GEO][FIRSTMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2GEO_1_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GEO][FIRSTMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2GEO_1->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(GEO,FIRSTMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2GEO_1->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGEO_1->currentIndex()>2 && ui->comboBoxSmoothFreq1GEO_1->currentIndex()==index){
        ui->comboBoxSmoothFreq1GEO_1->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[GEO][FIRSTMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1GEO_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GEO_1->count()>0) ui->comboBoxSmoothCode1GEO_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GEO_1->count()>0) ui->comboBoxSmoothPhase1GEO_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GEO_1->count()>0) ui->comboBoxSmoothPhase2GEO_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1GEO_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1GEO_1->count()>0 && ui->comboBoxSmoothPhase1GEO_1->currentIndex()==0 ) ui->comboBoxSmoothPhase1GEO_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2GEO_1->count()>0 && ui->comboBoxSmoothPhase2GEO_1->currentIndex()==0 ) ui->comboBoxSmoothPhase2GEO_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1GEO_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GEO_1->count()>0) ui->comboBoxSmoothCode1GEO_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GEO_1->count()>0) ui->comboBoxSmoothPhase1GEO_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GEO_1->count()>0) ui->comboBoxSmoothPhase2GEO_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1GEO_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GEO_1->count()>0 && ui->comboBoxSmoothCode1GEO_1->currentIndex()==0 ) ui->comboBoxSmoothCode1GEO_1->setCurrentIndex(index>=ui->comboBoxSmoothCode1GEO_1->count()?1:index);
        if ( ui->comboBoxSmoothPhase2GEO_1->count()>0 && ui->comboBoxSmoothPhase2GEO_1->currentIndex()==0 ) ui->comboBoxSmoothPhase2GEO_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2GEO_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GEO_1->count()>0) ui->comboBoxSmoothCode1GEO_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GEO_1->count()>0) ui->comboBoxSmoothPhase1GEO_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GEO_1->count()>0) ui->comboBoxSmoothPhase2GEO_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2GEO_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GEO_1->count()>0 && ui->comboBoxSmoothCode1GEO_1->currentIndex()==0 ) ui->comboBoxSmoothCode1GEO_1->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1GEO_1->count()>0 && ui->comboBoxSmoothPhase1GEO_1->currentIndex()==0 ) ui->comboBoxSmoothPhase1GEO_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothWithGEO_2_currentIndexChanged(int index){
    ui->comboBoxSmoothWithGEO_2->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithGEO_2->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(GEO,SECONDMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithGEO_2->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2GEO_2->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2GEO_2->setHidden(false);

    this->setSmoothWithFreqAll(GEO,SECONDMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1GEO_2->setHidden(false); //GC
    else ui->frameSmoothCode1GEO_2->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1GEO_2_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GEO][SECONDMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1GEO_2->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(GEO,SECONDMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1GEO_2->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1GEO_2->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGEO_2->currentIndex()>2 && ui->comboBoxSmoothFreq2GEO_2->currentIndex()==index){
        ui->comboBoxSmoothFreq2GEO_2->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[GEO][SECONDMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2GEO_2_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GEO][SECONDMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2GEO_2->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(GEO,SECONDMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2GEO_2->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGEO_2->currentIndex()>2 && ui->comboBoxSmoothFreq1GEO_2->currentIndex()==index){
        ui->comboBoxSmoothFreq1GEO_2->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[GEO][SECONDMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1GEO_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GEO_2->count()>0) ui->comboBoxSmoothCode1GEO_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GEO_2->count()>0) ui->comboBoxSmoothPhase1GEO_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GEO_2->count()>0) ui->comboBoxSmoothPhase2GEO_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1GEO_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1GEO_2->count()>0 && ui->comboBoxSmoothPhase1GEO_2->currentIndex()==0 ) ui->comboBoxSmoothPhase1GEO_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2GEO_2->count()>0 && ui->comboBoxSmoothPhase2GEO_2->currentIndex()==0 ) ui->comboBoxSmoothPhase2GEO_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1GEO_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GEO_2->count()>0) ui->comboBoxSmoothCode1GEO_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GEO_2->count()>0) ui->comboBoxSmoothPhase1GEO_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GEO_2->count()>0) ui->comboBoxSmoothPhase2GEO_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1GEO_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GEO_2->count()>0 && ui->comboBoxSmoothCode1GEO_2->currentIndex()==0 ) ui->comboBoxSmoothCode1GEO_2->setCurrentIndex(index>=ui->comboBoxSmoothCode1GEO_2->count()?1:index);
        if ( ui->comboBoxSmoothPhase2GEO_2->count()>0 && ui->comboBoxSmoothPhase2GEO_2->currentIndex()==0 ) ui->comboBoxSmoothPhase2GEO_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2GEO_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GEO_2->count()>0) ui->comboBoxSmoothCode1GEO_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GEO_2->count()>0) ui->comboBoxSmoothPhase1GEO_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GEO_2->count()>0) ui->comboBoxSmoothPhase2GEO_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2GEO_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GEO_2->count()>0 && ui->comboBoxSmoothCode1GEO_2->currentIndex()==0 ) ui->comboBoxSmoothCode1GEO_2->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1GEO_2->count()>0 && ui->comboBoxSmoothPhase1GEO_2->currentIndex()==0 ) ui->comboBoxSmoothPhase1GEO_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothWithGEO_3_currentIndexChanged(int index){
    ui->comboBoxSmoothWithGEO_3->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithGEO_3->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(GEO,2,-1,-1);
    }
    else ui->frameSmoothWithGEO_3->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2GEO_3->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2GEO_3->setHidden(false);

    this->setSmoothWithFreqAll(GEO,THIRDMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1GEO_3->setHidden(false); //GC
    else ui->frameSmoothCode1GEO_3->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1GEO_3_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GEO][THIRDMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1GEO_3->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(GEO,THIRDMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1GEO_3->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1GEO_3->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGEO_3->currentIndex()>2 && ui->comboBoxSmoothFreq2GEO_3->currentIndex()==index){
        ui->comboBoxSmoothFreq2GEO_3->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[GEO][THIRDMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2GEO_3_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[GEO][THIRDMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2GEO_3->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(GEO,THIRDMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2GEO_3->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithGEO_3->currentIndex()>2 && ui->comboBoxSmoothFreq1GEO_3->currentIndex()==index){
        ui->comboBoxSmoothFreq1GEO_3->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[GEO][THIRDMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1GEO_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GEO_3->count()>0) ui->comboBoxSmoothCode1GEO_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GEO_3->count()>0) ui->comboBoxSmoothPhase1GEO_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GEO_3->count()>0) ui->comboBoxSmoothPhase2GEO_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1GEO_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1GEO_3->count()>0 && ui->comboBoxSmoothPhase1GEO_3->currentIndex()==0 ) ui->comboBoxSmoothPhase1GEO_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2GEO_3->count()>0 && ui->comboBoxSmoothPhase2GEO_3->currentIndex()==0 ) ui->comboBoxSmoothPhase2GEO_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1GEO_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GEO_3->count()>0) ui->comboBoxSmoothCode1GEO_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GEO_3->count()>0) ui->comboBoxSmoothPhase1GEO_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GEO_3->count()>0) ui->comboBoxSmoothPhase2GEO_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1GEO_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GEO_3->count()>0 && ui->comboBoxSmoothCode1GEO_3->currentIndex()==0 ) ui->comboBoxSmoothCode1GEO_3->setCurrentIndex(index>=ui->comboBoxSmoothCode1GEO_3->count()?1:index);
        if ( ui->comboBoxSmoothPhase2GEO_3->count()>0 && ui->comboBoxSmoothPhase2GEO_3->currentIndex()==0 ) ui->comboBoxSmoothPhase2GEO_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2GEO_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1GEO_3->count()>0) ui->comboBoxSmoothCode1GEO_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1GEO_3->count()>0) ui->comboBoxSmoothPhase1GEO_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2GEO_3->count()>0) ui->comboBoxSmoothPhase2GEO_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2GEO_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1GEO_3->count()>0 && ui->comboBoxSmoothCode1GEO_3->currentIndex()==0 ) ui->comboBoxSmoothCode1GEO_3->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1GEO_3->count()>0 && ui->comboBoxSmoothPhase1GEO_3->currentIndex()==0 ) ui->comboBoxSmoothPhase1GEO_3->setCurrentIndex(1);
    }
}

// For BDS
void gLAB_GUI::on_comboBoxFreqCodeBDS_1_currentIndexChanged(int index){
    ui->comboBoxFreqCodeBDS_1->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(BDS,FIRSTMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeBDS_1->setEnabled(false);
            ui->lineEditStdDevCodeABDS_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(BDS,FIRSTMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeBDS_1->setEnabled(true);
            ui->lineEditStdDevCodeABDS_1->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1BDS_1->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseBDS_1_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseBDS_1->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(BDS,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseBDS_1->setEnabled(false);
            ui->lineEditStdDevPhaseABDS_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(BDS,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseBDS_1->setEnabled(true);
            ui->lineEditStdDevPhaseABDS_1->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1BDS_1->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCBDS_1_currentIndexChanged(int index){
    ui->comboBoxFreqGCBDS_1->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCBDS_1->setEnabled(false);
            ui->lineEditStdDevGCABDS_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(BDS,FIRSTMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCBDS_1->setEnabled(true);
            ui->lineEditStdDevGCABDS_1->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeBDS_1->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1BDS_1_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1BDS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2BDS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2BDS_1->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2BDS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2BDS_1_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2BDS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1BDS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1BDS_1->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1BDS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1BDS_1_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1BDS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2BDS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2BDS_1->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2BDS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2BDS_1_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2BDS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1BDS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1BDS_1->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1BDS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeBDS_1_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeBDS_1->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseBDS_1->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseBDS_1->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseBDS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseBDS_1_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseBDS_1->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeBDS_1->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeBDS_1->currentIndex()==0) {
        ui->comboBoxMeasGCCodeBDS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeBDS_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeBDS_1->setCurrentIndex(index);
    this->setWeightTypeValues(BDS,FIRSTMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBBDS_1->setHidden(true);
        ui->frameCodeCBDS_1->setHidden(true);
        ui->labelStdDevCodeAUnitBDS_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitBDS_1->setText("(m)");
        ui->labelStdDevCodeBUnitBDS_1->setText("(m)");
        ui->frameCodeBBDS_1->setHidden(false);
        ui->frameCodeCBDS_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCBDS_1->setHidden(true);
        ui->frameCodeBBDS_1->setHidden(false);
        ui->labelStdDevCodeAUnitBDS_1->setText("(m²)");
        ui->labelStdDevCodeBUnitBDS_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCBDS_1->setHidden(true);
        ui->frameCodeBBDS_1->setHidden(false);
        ui->labelStdDevCodeAUnitBDS_1->setText("(m²)");
        ui->labelStdDevCodeBUnitBDS_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseBDS_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseBDS_1->setCurrentIndex(index);
    this->setWeightTypeValues(BDS,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBBDS_1->setHidden(true);
        ui->framePhaseCBDS_1->setHidden(true);
        ui->labelStdDevPhaseAUnitBDS_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitBDS_1->setText("(m)");
        ui->labelStdDevPhaseBUnitBDS_1->setText("(m)");
        ui->framePhaseBBDS_1->setHidden(false);
        ui->framePhaseCBDS_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCBDS_1->setHidden(true);
        ui->framePhaseBBDS_1->setHidden(false);
        ui->labelStdDevPhaseAUnitBDS_1->setText("(m²)");
        ui->labelStdDevPhaseBUnitBDS_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCBDS_1->setHidden(true);
        ui->framePhaseBBDS_1->setHidden(false);
        ui->labelStdDevPhaseAUnitBDS_1->setText("(m²)");
        ui->labelStdDevPhaseBUnitBDS_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCBDS_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCBDS_1->setCurrentIndex(index);
    this->setWeightTypeValues(BDS,FIRSTMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBBDS_1->setHidden(true);
        ui->frameGCCBDS_1->setHidden(true);
        ui->labelStdDevGCAUnitBDS_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitBDS_1->setText("(m)");
        ui->labelStdDevGCBUnitBDS_1->setText("(m)");
        ui->frameGCBBDS_1->setHidden(false);
        ui->frameGCCBDS_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCBDS_1->setHidden(true);
        ui->frameGCBBDS_1->setHidden(false);
        ui->labelStdDevGCAUnitBDS_1->setText("(m²)");
        ui->labelStdDevGCBUnitBDS_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCBDS_1->setHidden(true);
        ui->frameGCBBDS_1->setHidden(false);
        ui->labelStdDevGCAUnitBDS_1->setText("(m²)");
        ui->labelStdDevGCBUnitBDS_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxFreqCodeBDS_2_currentIndexChanged(int index){
    ui->comboBoxFreqCodeBDS_2->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(BDS,SECONDMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeBDS_2->setEnabled(false);
            ui->lineEditStdDevCodeABDS_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(BDS,SECONDMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeBDS_2->setEnabled(true);
            ui->lineEditStdDevCodeABDS_2->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1BDS_2->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseBDS_2_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseBDS_2->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(BDS,SECONDMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseBDS_2->setEnabled(false);
            ui->lineEditStdDevPhaseABDS_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(BDS,SECONDMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseBDS_2->setEnabled(true);
            ui->lineEditStdDevPhaseABDS_2->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1BDS_2->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCBDS_2_currentIndexChanged(int index){
    ui->comboBoxFreqGCBDS_2->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCBDS_2->setEnabled(false);
            ui->lineEditStdDevGCABDS_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(BDS,SECONDMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCBDS_2->setEnabled(true);
            ui->lineEditStdDevGCABDS_2->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeBDS_2->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1BDS_2_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1BDS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2BDS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2BDS_2->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2BDS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2BDS_2_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2BDS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1BDS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1BDS_2->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1BDS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1BDS_2_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1BDS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2BDS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2BDS_2->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2BDS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2BDS_2_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2BDS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1BDS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1BDS_2->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1BDS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeBDS_2_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeBDS_2->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseBDS_2->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseBDS_2->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseBDS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseBDS_2_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseBDS_2->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeBDS_2->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeBDS_2->currentIndex()==0) {
        ui->comboBoxMeasGCCodeBDS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeBDS_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeBDS_2->setCurrentIndex(index);
    this->setWeightTypeValues(BDS,SECONDMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBBDS_2->setHidden(true);
        ui->frameCodeCBDS_2->setHidden(true);
        ui->labelStdDevCodeAUnitBDS_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitBDS_2->setText("(m)");
        ui->labelStdDevCodeBUnitBDS_2->setText("(m)");
        ui->frameCodeBBDS_2->setHidden(false);
        ui->frameCodeCBDS_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCBDS_2->setHidden(true);
        ui->frameCodeBBDS_2->setHidden(false);
        ui->labelStdDevCodeAUnitBDS_2->setText("(m²)");
        ui->labelStdDevCodeBUnitBDS_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCBDS_2->setHidden(true);
        ui->frameCodeBBDS_2->setHidden(false);
        ui->labelStdDevCodeAUnitBDS_2->setText("(m²)");
        ui->labelStdDevCodeBUnitBDS_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseBDS_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseBDS_2->setCurrentIndex(index);
    this->setWeightTypeValues(BDS,SECONDMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBBDS_2->setHidden(true);
        ui->framePhaseCBDS_2->setHidden(true);
        ui->labelStdDevPhaseAUnitBDS_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitBDS_2->setText("(m)");
        ui->labelStdDevPhaseBUnitBDS_2->setText("(m)");
        ui->framePhaseBBDS_2->setHidden(false);
        ui->framePhaseCBDS_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCBDS_2->setHidden(true);
        ui->framePhaseBBDS_2->setHidden(false);
        ui->labelStdDevPhaseAUnitBDS_2->setText("(m²)");
        ui->labelStdDevPhaseBUnitBDS_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCBDS_2->setHidden(true);
        ui->framePhaseBBDS_2->setHidden(false);
        ui->labelStdDevPhaseAUnitBDS_2->setText("(m²)");
        ui->labelStdDevPhaseBUnitBDS_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCBDS_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCBDS_2->setCurrentIndex(index);
    this->setWeightTypeValues(BDS,SECONDMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBBDS_2->setHidden(true);
        ui->frameGCCBDS_2->setHidden(true);
        ui->labelStdDevGCAUnitBDS_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitBDS_2->setText("(m)");
        ui->labelStdDevGCBUnitBDS_2->setText("(m)");
        ui->frameGCBBDS_2->setHidden(false);
        ui->frameGCCBDS_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCBDS_2->setHidden(true);
        ui->frameGCBBDS_2->setHidden(false);
        ui->labelStdDevGCAUnitBDS_2->setText("(m²)");
        ui->labelStdDevGCBUnitBDS_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCBDS_2->setHidden(true);
        ui->frameGCBBDS_2->setHidden(false);
        ui->labelStdDevGCAUnitBDS_2->setText("(m²)");
        ui->labelStdDevGCBUnitBDS_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxFreqCodeBDS_3_currentIndexChanged(int index){
    ui->comboBoxFreqCodeBDS_3->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(BDS,THIRDMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeBDS_3->setEnabled(false);
            ui->lineEditStdDevCodeABDS_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(BDS,THIRDMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeBDS_3->setEnabled(true);
            ui->lineEditStdDevCodeABDS_3->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1BDS_3->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseBDS_3_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseBDS_3->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(BDS,THIRDMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseBDS_3->setEnabled(false);
            ui->lineEditStdDevPhaseABDS_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(BDS,THIRDMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseBDS_3->setEnabled(true);
            ui->lineEditStdDevPhaseABDS_3->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1BDS_3->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCBDS_3_currentIndexChanged(int index){
    ui->comboBoxFreqGCBDS_3->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCBDS_3->setEnabled(false);
            ui->lineEditStdDevGCABDS_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(BDS,THIRDMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCBDS_3->setEnabled(true);
            ui->lineEditStdDevGCABDS_3->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeBDS_3->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1BDS_3_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1BDS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2BDS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2BDS_3->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2BDS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2BDS_3_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2BDS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1BDS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1BDS_3->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1BDS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1BDS_3_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1BDS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2BDS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2BDS_3->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2BDS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2BDS_3_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2BDS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1BDS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1BDS_3->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1BDS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeBDS_3_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeBDS_3->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseBDS_3->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseBDS_3->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseBDS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseBDS_3_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseBDS_3->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeBDS_3->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeBDS_3->currentIndex()==0) {
        ui->comboBoxMeasGCCodeBDS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeBDS_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeBDS_3->setCurrentIndex(index);
    this->setWeightTypeValues(BDS,THIRDMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBBDS_3->setHidden(true);
        ui->frameCodeCBDS_3->setHidden(true);
        ui->labelStdDevCodeAUnitBDS_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitBDS_3->setText("(m)");
        ui->labelStdDevCodeBUnitBDS_3->setText("(m)");
        ui->frameCodeBBDS_3->setHidden(false);
        ui->frameCodeCBDS_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCBDS_3->setHidden(true);
        ui->frameCodeBBDS_3->setHidden(false);
        ui->labelStdDevCodeAUnitBDS_3->setText("(m²)");
        ui->labelStdDevCodeBUnitBDS_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCBDS_3->setHidden(true);
        ui->frameCodeBBDS_3->setHidden(false);
        ui->labelStdDevCodeAUnitBDS_3->setText("(m²)");
        ui->labelStdDevCodeBUnitBDS_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseBDS_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseBDS_3->setCurrentIndex(index);
    this->setWeightTypeValues(BDS,THIRDMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBBDS_3->setHidden(true);
        ui->framePhaseCBDS_3->setHidden(true);
        ui->labelStdDevPhaseAUnitBDS_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitBDS_3->setText("(m)");
        ui->labelStdDevPhaseBUnitBDS_3->setText("(m)");
        ui->framePhaseBBDS_3->setHidden(false);
        ui->framePhaseCBDS_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCBDS_3->setHidden(true);
        ui->framePhaseBBDS_3->setHidden(false);
        ui->labelStdDevPhaseAUnitBDS_3->setText("(m²)");
        ui->labelStdDevPhaseBUnitBDS_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCBDS_3->setHidden(true);
        ui->framePhaseBBDS_3->setHidden(false);
        ui->labelStdDevPhaseAUnitBDS_3->setText("(m²)");
        ui->labelStdDevPhaseBUnitBDS_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCBDS_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCBDS_3->setCurrentIndex(index);
    this->setWeightTypeValues(BDS,THIRDMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBBDS_3->setHidden(true);
        ui->frameGCCBDS_3->setHidden(true);
        ui->labelStdDevGCAUnitBDS_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitBDS_3->setText("(m)");
        ui->labelStdDevGCBUnitBDS_3->setText("(m)");
        ui->frameGCBBDS_3->setHidden(false);
        ui->frameGCCBDS_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCBDS_3->setHidden(true);
        ui->frameGCBBDS_3->setHidden(false);
        ui->labelStdDevGCAUnitBDS_3->setText("(m²)");
        ui->labelStdDevGCBUnitBDS_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCBDS_3->setHidden(true);
        ui->frameGCBBDS_3->setHidden(false);
        ui->labelStdDevGCAUnitBDS_3->setText("(m²)");
        ui->labelStdDevGCBUnitBDS_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxSmoothWithBDS_1_currentIndexChanged(int index){
    ui->comboBoxSmoothWithBDS_1->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithBDS_1->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(BDS,FIRSTMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithBDS_1->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2BDS_1->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2BDS_1->setHidden(false);

    this->setSmoothWithFreqAll(BDS,FIRSTMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1BDS_1->setHidden(false); //GC
    else ui->frameSmoothCode1BDS_1->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1BDS_1_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[BDS][FIRSTMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1BDS_1->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(BDS,FIRSTMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1BDS_1->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1BDS_1->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithBDS_1->currentIndex()>2 && ui->comboBoxSmoothFreq2BDS_1->currentIndex()==index){
        ui->comboBoxSmoothFreq2BDS_1->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[BDS][FIRSTMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2BDS_1_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[BDS][FIRSTMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2BDS_1->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(BDS,FIRSTMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2BDS_1->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithBDS_1->currentIndex()>2 && ui->comboBoxSmoothFreq1BDS_1->currentIndex()==index){
        ui->comboBoxSmoothFreq1BDS_1->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[BDS][FIRSTMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1BDS_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1BDS_1->count()>0) ui->comboBoxSmoothCode1BDS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1BDS_1->count()>0) ui->comboBoxSmoothPhase1BDS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2BDS_1->count()>0) ui->comboBoxSmoothPhase2BDS_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1BDS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1BDS_1->count()>0 && ui->comboBoxSmoothPhase1BDS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase1BDS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2BDS_1->count()>0 && ui->comboBoxSmoothPhase2BDS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase2BDS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1BDS_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1BDS_1->count()>0) ui->comboBoxSmoothCode1BDS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1BDS_1->count()>0) ui->comboBoxSmoothPhase1BDS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2BDS_1->count()>0) ui->comboBoxSmoothPhase2BDS_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1BDS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1BDS_1->count()>0 && ui->comboBoxSmoothCode1BDS_1->currentIndex()==0 ) ui->comboBoxSmoothCode1BDS_1->setCurrentIndex(index>=ui->comboBoxSmoothCode1BDS_1->count()?1:index);
        if ( ui->comboBoxSmoothPhase2BDS_1->count()>0 && ui->comboBoxSmoothPhase2BDS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase2BDS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2BDS_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1BDS_1->count()>0) ui->comboBoxSmoothCode1BDS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1BDS_1->count()>0) ui->comboBoxSmoothPhase1BDS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2BDS_1->count()>0) ui->comboBoxSmoothPhase2BDS_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2BDS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1BDS_1->count()>0 && ui->comboBoxSmoothCode1BDS_1->currentIndex()==0 ) ui->comboBoxSmoothCode1BDS_1->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1BDS_1->count()>0 && ui->comboBoxSmoothPhase1BDS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase1BDS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothWithBDS_2_currentIndexChanged(int index){
    ui->comboBoxSmoothWithBDS_2->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithBDS_2->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(BDS,SECONDMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithBDS_2->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2BDS_2->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2BDS_2->setHidden(false);

    this->setSmoothWithFreqAll(BDS,SECONDMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1BDS_2->setHidden(false); //GC
    else ui->frameSmoothCode1BDS_2->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1BDS_2_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[BDS][SECONDMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1BDS_2->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(BDS,SECONDMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1BDS_2->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1BDS_2->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithBDS_2->currentIndex()>2 && ui->comboBoxSmoothFreq2BDS_2->currentIndex()==index){
        ui->comboBoxSmoothFreq2BDS_2->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[BDS][SECONDMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2BDS_2_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[BDS][SECONDMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2BDS_2->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(BDS,SECONDMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2BDS_2->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithBDS_2->currentIndex()>2 && ui->comboBoxSmoothFreq1BDS_2->currentIndex()==index){
        ui->comboBoxSmoothFreq1BDS_2->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[BDS][SECONDMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1BDS_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1BDS_2->count()>0) ui->comboBoxSmoothCode1BDS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1BDS_2->count()>0) ui->comboBoxSmoothPhase1BDS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2BDS_2->count()>0) ui->comboBoxSmoothPhase2BDS_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1BDS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1BDS_2->count()>0 && ui->comboBoxSmoothPhase1BDS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase1BDS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2BDS_2->count()>0 && ui->comboBoxSmoothPhase2BDS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase2BDS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1BDS_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1BDS_2->count()>0) ui->comboBoxSmoothCode1BDS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1BDS_2->count()>0) ui->comboBoxSmoothPhase1BDS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2BDS_2->count()>0) ui->comboBoxSmoothPhase2BDS_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1BDS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1BDS_2->count()>0 && ui->comboBoxSmoothCode1BDS_2->currentIndex()==0 ) ui->comboBoxSmoothCode1BDS_2->setCurrentIndex(index>=ui->comboBoxSmoothCode1BDS_2->count()?1:index);
        if ( ui->comboBoxSmoothPhase2BDS_2->count()>0 && ui->comboBoxSmoothPhase2BDS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase2BDS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2BDS_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1BDS_2->count()>0) ui->comboBoxSmoothCode1BDS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1BDS_2->count()>0) ui->comboBoxSmoothPhase1BDS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2BDS_2->count()>0) ui->comboBoxSmoothPhase2BDS_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2BDS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1BDS_2->count()>0 && ui->comboBoxSmoothCode1BDS_2->currentIndex()==0 ) ui->comboBoxSmoothCode1BDS_2->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1BDS_2->count()>0 && ui->comboBoxSmoothPhase1BDS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase1BDS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothWithBDS_3_currentIndexChanged(int index){
    ui->comboBoxSmoothWithBDS_3->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithBDS_3->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(BDS,THIRDMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithBDS_3->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2BDS_3->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2BDS_3->setHidden(false);

    this->setSmoothWithFreqAll(BDS,THIRDMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1BDS_3->setHidden(false); //GC
    else ui->frameSmoothCode1BDS_3->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1BDS_3_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[BDS][THIRDMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1BDS_3->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(BDS,THIRDMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1BDS_3->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1BDS_3->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithBDS_3->currentIndex()>2 && ui->comboBoxSmoothFreq2BDS_3->currentIndex()==index){
        ui->comboBoxSmoothFreq2BDS_3->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[BDS][THIRDMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2BDS_3_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[BDS][THIRDMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2BDS_3->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(BDS,THIRDMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2BDS_3->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithBDS_3->currentIndex()>2 && ui->comboBoxSmoothFreq1BDS_3->currentIndex()==index){
        ui->comboBoxSmoothFreq1BDS_3->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[BDS][THIRDMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1BDS_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1BDS_3->count()>0) ui->comboBoxSmoothCode1BDS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1BDS_3->count()>0) ui->comboBoxSmoothPhase1BDS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2BDS_3->count()>0) ui->comboBoxSmoothPhase2BDS_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1BDS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1BDS_3->count()>0 && ui->comboBoxSmoothPhase1BDS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase1BDS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2BDS_3->count()>0 && ui->comboBoxSmoothPhase2BDS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase2BDS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1BDS_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1BDS_3->count()>0) ui->comboBoxSmoothCode1BDS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1BDS_3->count()>0) ui->comboBoxSmoothPhase1BDS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2BDS_3->count()>0) ui->comboBoxSmoothPhase2BDS_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1BDS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1BDS_3->count()>0 && ui->comboBoxSmoothCode1BDS_3->currentIndex()==0 ) ui->comboBoxSmoothCode1BDS_3->setCurrentIndex(index>=ui->comboBoxSmoothCode1BDS_3->count()?1:index);
        if ( ui->comboBoxSmoothPhase2BDS_3->count()>0 && ui->comboBoxSmoothPhase2BDS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase2BDS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2BDS_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1BDS_3->count()>0) ui->comboBoxSmoothCode1BDS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1BDS_3->count()>0) ui->comboBoxSmoothPhase1BDS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2BDS_3->count()>0) ui->comboBoxSmoothPhase2BDS_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2BDS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1BDS_3->count()>0 && ui->comboBoxSmoothCode1BDS_3->currentIndex()==0 ) ui->comboBoxSmoothCode1BDS_3->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1BDS_3->count()>0 && ui->comboBoxSmoothPhase1BDS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase1BDS_3->setCurrentIndex(1);
    }
}

// For QZSS
void gLAB_GUI::on_comboBoxFreqCodeQZSS_1_currentIndexChanged(int index){
    ui->comboBoxFreqCodeQZSS_1->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(QZSS,FIRSTMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeQZSS_1->setEnabled(false);
            ui->lineEditStdDevCodeAQZSS_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(QZSS,FIRSTMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeQZSS_1->setEnabled(true);
            ui->lineEditStdDevCodeAQZSS_1->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1QZSS_1->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseQZSS_1_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseQZSS_1->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(QZSS,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseQZSS_1->setEnabled(false);
            ui->lineEditStdDevPhaseAQZSS_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(QZSS,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseQZSS_1->setEnabled(true);
            ui->lineEditStdDevPhaseAQZSS_1->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1QZSS_1->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCQZSS_1_currentIndexChanged(int index){
    ui->comboBoxFreqGCQZSS_1->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCQZSS_1->setEnabled(false);
            ui->lineEditStdDevGCAQZSS_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(QZSS,FIRSTMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCQZSS_1->setEnabled(true);
            ui->lineEditStdDevGCAQZSS_1->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeQZSS_1->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1QZSS_1_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1QZSS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2QZSS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2QZSS_1->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2QZSS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2QZSS_1_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2QZSS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1QZSS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1QZSS_1->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1QZSS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1QZSS_1_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1QZSS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2QZSS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2QZSS_1->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2QZSS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2QZSS_1_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2QZSS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1QZSS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1QZSS_1->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1QZSS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeQZSS_1_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeQZSS_1->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseQZSS_1->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseQZSS_1->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseQZSS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseQZSS_1_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseQZSS_1->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeQZSS_1->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeQZSS_1->currentIndex()==0) {
        ui->comboBoxMeasGCCodeQZSS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeQZSS_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeQZSS_1->setCurrentIndex(index);
    this->setWeightTypeValues(QZSS,FIRSTMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBQZSS_1->setHidden(true);
        ui->frameCodeCQZSS_1->setHidden(true);
        ui->labelStdDevCodeAUnitQZSS_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitQZSS_1->setText("(m)");
        ui->labelStdDevCodeBUnitQZSS_1->setText("(m)");
        ui->frameCodeBQZSS_1->setHidden(false);
        ui->frameCodeCQZSS_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCQZSS_1->setHidden(true);
        ui->frameCodeBQZSS_1->setHidden(false);
        ui->labelStdDevCodeAUnitQZSS_1->setText("(m²)");
        ui->labelStdDevCodeBUnitQZSS_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCQZSS_1->setHidden(true);
        ui->frameCodeBQZSS_1->setHidden(false);
        ui->labelStdDevCodeAUnitQZSS_1->setText("(m²)");
        ui->labelStdDevCodeBUnitQZSS_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseQZSS_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseQZSS_1->setCurrentIndex(index);
    this->setWeightTypeValues(QZSS,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBQZSS_1->setHidden(true);
        ui->framePhaseCQZSS_1->setHidden(true);
        ui->labelStdDevPhaseAUnitQZSS_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitQZSS_1->setText("(m)");
        ui->labelStdDevPhaseBUnitQZSS_1->setText("(m)");
        ui->framePhaseBQZSS_1->setHidden(false);
        ui->framePhaseCQZSS_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCQZSS_1->setHidden(true);
        ui->framePhaseBQZSS_1->setHidden(false);
        ui->labelStdDevPhaseAUnitQZSS_1->setText("(m²)");
        ui->labelStdDevPhaseBUnitQZSS_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCQZSS_1->setHidden(true);
        ui->framePhaseBQZSS_1->setHidden(false);
        ui->labelStdDevPhaseAUnitQZSS_1->setText("(m²)");
        ui->labelStdDevPhaseBUnitQZSS_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCQZSS_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCQZSS_1->setCurrentIndex(index);
    this->setWeightTypeValues(QZSS,FIRSTMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBQZSS_1->setHidden(true);
        ui->frameGCCQZSS_1->setHidden(true);
        ui->labelStdDevGCAUnitQZSS_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitQZSS_1->setText("(m)");
        ui->labelStdDevGCBUnitQZSS_1->setText("(m)");
        ui->frameGCBQZSS_1->setHidden(false);
        ui->frameGCCQZSS_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCQZSS_1->setHidden(true);
        ui->frameGCBQZSS_1->setHidden(false);
        ui->labelStdDevGCAUnitQZSS_1->setText("(m²)");
        ui->labelStdDevGCBUnitQZSS_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCQZSS_1->setHidden(true);
        ui->frameGCBQZSS_1->setHidden(false);
        ui->labelStdDevGCAUnitQZSS_1->setText("(m²)");
        ui->labelStdDevGCBUnitQZSS_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxFreqCodeQZSS_2_currentIndexChanged(int index){
    ui->comboBoxFreqCodeQZSS_2->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(QZSS,SECONDMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeQZSS_2->setEnabled(false);
            ui->lineEditStdDevCodeAQZSS_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(QZSS,SECONDMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeQZSS_2->setEnabled(true);
            ui->lineEditStdDevCodeAQZSS_2->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1QZSS_2->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseQZSS_2_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseQZSS_2->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(QZSS,SECONDMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseQZSS_2->setEnabled(false);
            ui->lineEditStdDevPhaseAQZSS_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(QZSS,SECONDMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseQZSS_2->setEnabled(true);
            ui->lineEditStdDevPhaseAQZSS_2->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1QZSS_2->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCQZSS_2_currentIndexChanged(int index){
    ui->comboBoxFreqGCQZSS_2->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCQZSS_2->setEnabled(false);
            ui->lineEditStdDevGCAQZSS_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(QZSS,SECONDMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCQZSS_2->setEnabled(true);
            ui->lineEditStdDevGCAQZSS_2->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeQZSS_2->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1QZSS_2_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1QZSS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2QZSS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2QZSS_2->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2QZSS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2QZSS_2_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2QZSS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1QZSS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1QZSS_2->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1QZSS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1QZSS_2_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1QZSS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2QZSS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2QZSS_2->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2QZSS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2QZSS_2_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2QZSS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1QZSS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1QZSS_2->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1QZSS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeQZSS_2_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeQZSS_2->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseQZSS_2->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseQZSS_2->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseQZSS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseQZSS_2_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseQZSS_2->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeQZSS_2->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeQZSS_2->currentIndex()==0) {
        ui->comboBoxMeasGCCodeQZSS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeQZSS_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeQZSS_2->setCurrentIndex(index);
    this->setWeightTypeValues(QZSS,SECONDMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBQZSS_2->setHidden(true);
        ui->frameCodeCQZSS_2->setHidden(true);
        ui->labelStdDevCodeAUnitQZSS_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitQZSS_2->setText("(m)");
        ui->labelStdDevCodeBUnitQZSS_2->setText("(m)");
        ui->frameCodeBQZSS_2->setHidden(false);
        ui->frameCodeCQZSS_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCQZSS_2->setHidden(true);
        ui->frameCodeBQZSS_2->setHidden(false);
        ui->labelStdDevCodeAUnitQZSS_2->setText("(m²)");
        ui->labelStdDevCodeBUnitQZSS_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCQZSS_2->setHidden(true);
        ui->frameCodeBQZSS_2->setHidden(false);
        ui->labelStdDevCodeAUnitQZSS_2->setText("(m²)");
        ui->labelStdDevCodeBUnitQZSS_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseQZSS_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseQZSS_2->setCurrentIndex(index);
    this->setWeightTypeValues(QZSS,SECONDMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBQZSS_2->setHidden(true);
        ui->framePhaseCQZSS_2->setHidden(true);
        ui->labelStdDevPhaseAUnitQZSS_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitQZSS_2->setText("(m)");
        ui->labelStdDevPhaseBUnitQZSS_2->setText("(m)");
        ui->framePhaseBQZSS_2->setHidden(false);
        ui->framePhaseCQZSS_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCQZSS_2->setHidden(true);
        ui->framePhaseBQZSS_2->setHidden(false);
        ui->labelStdDevPhaseAUnitQZSS_2->setText("(m²)");
        ui->labelStdDevPhaseBUnitQZSS_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCQZSS_2->setHidden(true);
        ui->framePhaseBQZSS_2->setHidden(false);
        ui->labelStdDevPhaseAUnitQZSS_2->setText("(m²)");
        ui->labelStdDevPhaseBUnitQZSS_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCQZSS_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCQZSS_2->setCurrentIndex(index);
    this->setWeightTypeValues(QZSS,SECONDMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBQZSS_2->setHidden(true);
        ui->frameGCCQZSS_2->setHidden(true);
        ui->labelStdDevGCAUnitQZSS_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitQZSS_2->setText("(m)");
        ui->labelStdDevGCBUnitQZSS_2->setText("(m)");
        ui->frameGCBQZSS_2->setHidden(false);
        ui->frameGCCQZSS_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCQZSS_2->setHidden(true);
        ui->frameGCBQZSS_2->setHidden(false);
        ui->labelStdDevGCAUnitQZSS_2->setText("(m²)");
        ui->labelStdDevGCBUnitQZSS_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCQZSS_2->setHidden(true);
        ui->frameGCBQZSS_2->setHidden(false);
        ui->labelStdDevGCAUnitQZSS_2->setText("(m²)");
        ui->labelStdDevGCBUnitQZSS_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxFreqCodeQZSS_3_currentIndexChanged(int index){
    ui->comboBoxFreqCodeQZSS_3->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(QZSS,THIRDMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeQZSS_3->setEnabled(false);
            ui->lineEditStdDevCodeAQZSS_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(QZSS,THIRDMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeQZSS_3->setEnabled(true);
            ui->lineEditStdDevCodeAQZSS_3->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1QZSS_3->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseQZSS_3_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseQZSS_3->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(QZSS,THIRDMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseQZSS_3->setEnabled(false);
            ui->lineEditStdDevPhaseAQZSS_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(QZSS,THIRDMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseQZSS_3->setEnabled(true);
            ui->lineEditStdDevPhaseAQZSS_3->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1QZSS_3->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCQZSS_3_currentIndexChanged(int index){
    ui->comboBoxFreqGCQZSS_3->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCQZSS_3->setEnabled(false);
            ui->lineEditStdDevGCAQZSS_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(QZSS,THIRDMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCQZSS_3->setEnabled(true);
            ui->lineEditStdDevGCAQZSS_3->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeQZSS_3->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1QZSS_3_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1QZSS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2QZSS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2QZSS_3->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2QZSS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2QZSS_3_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2QZSS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1QZSS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1QZSS_3->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1QZSS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1QZSS_3_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1QZSS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2QZSS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2QZSS_3->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2QZSS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2QZSS_3_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2QZSS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1QZSS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1QZSS_3->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1QZSS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeQZSS_3_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeQZSS_3->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseQZSS_3->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseQZSS_3->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseQZSS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseQZSS_3_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseQZSS_3->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeQZSS_3->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeQZSS_3->currentIndex()==0) {
        ui->comboBoxMeasGCCodeQZSS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeQZSS_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeQZSS_3->setCurrentIndex(index);
    this->setWeightTypeValues(QZSS,THIRDMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBQZSS_3->setHidden(true);
        ui->frameCodeCQZSS_3->setHidden(true);
        ui->labelStdDevCodeAUnitQZSS_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitQZSS_3->setText("(m)");
        ui->labelStdDevCodeBUnitQZSS_3->setText("(m)");
        ui->frameCodeBQZSS_3->setHidden(false);
        ui->frameCodeCQZSS_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCQZSS_3->setHidden(true);
        ui->frameCodeBQZSS_3->setHidden(false);
        ui->labelStdDevCodeAUnitQZSS_3->setText("(m²)");
        ui->labelStdDevCodeBUnitQZSS_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCQZSS_3->setHidden(true);
        ui->frameCodeBQZSS_3->setHidden(false);
        ui->labelStdDevCodeAUnitQZSS_3->setText("(m²)");
        ui->labelStdDevCodeBUnitQZSS_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseQZSS_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseQZSS_3->setCurrentIndex(index);
    this->setWeightTypeValues(QZSS,THIRDMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBQZSS_3->setHidden(true);
        ui->framePhaseCQZSS_3->setHidden(true);
        ui->labelStdDevPhaseAUnitQZSS_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitQZSS_3->setText("(m)");
        ui->labelStdDevPhaseBUnitQZSS_3->setText("(m)");
        ui->framePhaseBQZSS_3->setHidden(false);
        ui->framePhaseCQZSS_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCQZSS_3->setHidden(true);
        ui->framePhaseBQZSS_3->setHidden(false);
        ui->labelStdDevPhaseAUnitQZSS_3->setText("(m²)");
        ui->labelStdDevPhaseBUnitQZSS_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCQZSS_3->setHidden(true);
        ui->framePhaseBQZSS_3->setHidden(false);
        ui->labelStdDevPhaseAUnitQZSS_3->setText("(m²)");
        ui->labelStdDevPhaseBUnitQZSS_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCQZSS_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCQZSS_3->setCurrentIndex(index);
    this->setWeightTypeValues(QZSS,THIRDMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBQZSS_3->setHidden(true);
        ui->frameGCCQZSS_3->setHidden(true);
        ui->labelStdDevGCAUnitQZSS_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitQZSS_3->setText("(m)");
        ui->labelStdDevGCBUnitQZSS_3->setText("(m)");
        ui->frameGCBQZSS_3->setHidden(false);
        ui->frameGCCQZSS_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCQZSS_3->setHidden(true);
        ui->frameGCBQZSS_3->setHidden(false);
        ui->labelStdDevGCAUnitQZSS_3->setText("(m²)");
        ui->labelStdDevGCBUnitQZSS_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCQZSS_3->setHidden(true);
        ui->frameGCBQZSS_3->setHidden(false);
        ui->labelStdDevGCAUnitQZSS_3->setText("(m²)");
        ui->labelStdDevGCBUnitQZSS_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxSmoothWithQZSS_1_currentIndexChanged(int index){
    ui->comboBoxSmoothWithQZSS_1->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithQZSS_1->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(QZSS,FIRSTMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithQZSS_1->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2QZSS_1->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2QZSS_1->setHidden(false);

    this->setSmoothWithFreqAll(QZSS,FIRSTMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1QZSS_1->setHidden(false); //GC
    else ui->frameSmoothCode1QZSS_1->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1QZSS_1_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[QZSS][FIRSTMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1QZSS_1->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(QZSS,FIRSTMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1QZSS_1->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1QZSS_1->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithQZSS_1->currentIndex()>2 && ui->comboBoxSmoothFreq2QZSS_1->currentIndex()==index){
        ui->comboBoxSmoothFreq2QZSS_1->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[QZSS][FIRSTMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2QZSS_1_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[QZSS][FIRSTMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2QZSS_1->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(QZSS,FIRSTMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2QZSS_1->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithQZSS_1->currentIndex()>2 && ui->comboBoxSmoothFreq1QZSS_1->currentIndex()==index){
        ui->comboBoxSmoothFreq1QZSS_1->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[QZSS][FIRSTMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1QZSS_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1QZSS_1->count()>0) ui->comboBoxSmoothCode1QZSS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1QZSS_1->count()>0) ui->comboBoxSmoothPhase1QZSS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2QZSS_1->count()>0) ui->comboBoxSmoothPhase2QZSS_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1QZSS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1QZSS_1->count()>0 && ui->comboBoxSmoothPhase1QZSS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase1QZSS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2QZSS_1->count()>0 && ui->comboBoxSmoothPhase2QZSS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase2QZSS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1QZSS_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1QZSS_1->count()>0) ui->comboBoxSmoothCode1QZSS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1QZSS_1->count()>0) ui->comboBoxSmoothPhase1QZSS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2QZSS_1->count()>0) ui->comboBoxSmoothPhase2QZSS_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1QZSS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1QZSS_1->count()>0 && ui->comboBoxSmoothCode1QZSS_1->currentIndex()==0 ) ui->comboBoxSmoothCode1QZSS_1->setCurrentIndex(index>=ui->comboBoxSmoothCode1QZSS_1->count()?1:index);
        if ( ui->comboBoxSmoothPhase2QZSS_1->count()>0 && ui->comboBoxSmoothPhase2QZSS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase2QZSS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2QZSS_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1QZSS_1->count()>0) ui->comboBoxSmoothCode1QZSS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1QZSS_1->count()>0) ui->comboBoxSmoothPhase1QZSS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2QZSS_1->count()>0) ui->comboBoxSmoothPhase2QZSS_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2QZSS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1QZSS_1->count()>0 && ui->comboBoxSmoothCode1QZSS_1->currentIndex()==0 ) ui->comboBoxSmoothCode1QZSS_1->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1QZSS_1->count()>0 && ui->comboBoxSmoothPhase1QZSS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase1QZSS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothWithQZSS_2_currentIndexChanged(int index){
    ui->comboBoxSmoothWithQZSS_2->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithQZSS_2->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(QZSS,SECONDMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithQZSS_2->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2QZSS_2->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2QZSS_2->setHidden(false);

    this->setSmoothWithFreqAll(QZSS,SECONDMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1QZSS_2->setHidden(false); //GC
    else ui->frameSmoothCode1QZSS_2->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1QZSS_2_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[QZSS][SECONDMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1QZSS_2->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(QZSS,SECONDMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1QZSS_2->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1QZSS_2->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithQZSS_2->currentIndex()>2 && ui->comboBoxSmoothFreq2QZSS_2->currentIndex()==index){
        ui->comboBoxSmoothFreq2QZSS_2->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[QZSS][SECONDMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2QZSS_2_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[QZSS][SECONDMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2QZSS_2->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(QZSS,SECONDMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2QZSS_2->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithQZSS_2->currentIndex()>2 && ui->comboBoxSmoothFreq1QZSS_2->currentIndex()==index){
        ui->comboBoxSmoothFreq1QZSS_2->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[QZSS][SECONDMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1QZSS_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1QZSS_2->count()>0) ui->comboBoxSmoothCode1QZSS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1QZSS_2->count()>0) ui->comboBoxSmoothPhase1QZSS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2QZSS_2->count()>0) ui->comboBoxSmoothPhase2QZSS_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1QZSS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1QZSS_2->count()>0 && ui->comboBoxSmoothPhase1QZSS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase1QZSS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2QZSS_2->count()>0 && ui->comboBoxSmoothPhase2QZSS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase2QZSS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1QZSS_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1QZSS_2->count()>0) ui->comboBoxSmoothCode1QZSS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1QZSS_2->count()>0) ui->comboBoxSmoothPhase1QZSS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2QZSS_2->count()>0) ui->comboBoxSmoothPhase2QZSS_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1QZSS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1QZSS_2->count()>0 && ui->comboBoxSmoothCode1QZSS_2->currentIndex()==0 ) ui->comboBoxSmoothCode1QZSS_2->setCurrentIndex(index>=ui->comboBoxSmoothCode1QZSS_2->count()?1:index);
        if ( ui->comboBoxSmoothPhase2QZSS_2->count()>0 && ui->comboBoxSmoothPhase2QZSS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase2QZSS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2QZSS_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1QZSS_2->count()>0) ui->comboBoxSmoothCode1QZSS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1QZSS_2->count()>0) ui->comboBoxSmoothPhase1QZSS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2QZSS_2->count()>0) ui->comboBoxSmoothPhase2QZSS_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2QZSS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1QZSS_2->count()>0 && ui->comboBoxSmoothCode1QZSS_2->currentIndex()==0 ) ui->comboBoxSmoothCode1QZSS_2->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1QZSS_2->count()>0 && ui->comboBoxSmoothPhase1QZSS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase1QZSS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothWithQZSS_3_currentIndexChanged(int index){
    ui->comboBoxSmoothWithQZSS_3->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithQZSS_3->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(QZSS,THIRDMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithQZSS_3->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2QZSS_3->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2QZSS_3->setHidden(false);

    this->setSmoothWithFreqAll(QZSS,THIRDMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1QZSS_3->setHidden(false); //GC
    else ui->frameSmoothCode1QZSS_3->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1QZSS_3_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[QZSS][THIRDMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1QZSS_3->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(QZSS,THIRDMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1QZSS_3->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1QZSS_3->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithQZSS_3->currentIndex()>2 && ui->comboBoxSmoothFreq2QZSS_3->currentIndex()==index){
        ui->comboBoxSmoothFreq2QZSS_3->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[QZSS][THIRDMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2QZSS_3_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[QZSS][THIRDMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2QZSS_3->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(QZSS,THIRDMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2QZSS_3->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithQZSS_3->currentIndex()>2 && ui->comboBoxSmoothFreq1QZSS_3->currentIndex()==index){
        ui->comboBoxSmoothFreq1QZSS_3->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[QZSS][THIRDMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1QZSS_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1QZSS_3->count()>0) ui->comboBoxSmoothCode1QZSS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1QZSS_3->count()>0) ui->comboBoxSmoothPhase1QZSS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2QZSS_3->count()>0) ui->comboBoxSmoothPhase2QZSS_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1QZSS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1QZSS_3->count()>0 && ui->comboBoxSmoothPhase1QZSS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase1QZSS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2QZSS_3->count()>0 && ui->comboBoxSmoothPhase2QZSS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase2QZSS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1QZSS_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1QZSS_3->count()>0) ui->comboBoxSmoothCode1QZSS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1QZSS_3->count()>0) ui->comboBoxSmoothPhase1QZSS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2QZSS_3->count()>0) ui->comboBoxSmoothPhase2QZSS_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1QZSS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1QZSS_3->count()>0 && ui->comboBoxSmoothCode1QZSS_3->currentIndex()==0 ) ui->comboBoxSmoothCode1QZSS_3->setCurrentIndex(index>=ui->comboBoxSmoothCode1QZSS_3->count()?1:index);
        if ( ui->comboBoxSmoothPhase2QZSS_3->count()>0 && ui->comboBoxSmoothPhase2QZSS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase2QZSS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2QZSS_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1QZSS_3->count()>0) ui->comboBoxSmoothCode1QZSS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1QZSS_3->count()>0) ui->comboBoxSmoothPhase1QZSS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2QZSS_3->count()>0) ui->comboBoxSmoothPhase2QZSS_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2QZSS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1QZSS_3->count()>0 && ui->comboBoxSmoothCode1QZSS_3->currentIndex()==0 ) ui->comboBoxSmoothCode1QZSS_3->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1QZSS_3->count()>0 && ui->comboBoxSmoothPhase1QZSS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase1QZSS_3->setCurrentIndex(1);
    }
}

// For IRNSS
void gLAB_GUI::on_comboBoxFreqCodeIRNSS_1_currentIndexChanged(int index){
    ui->comboBoxFreqCodeIRNSS_1->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(IRNSS,FIRSTMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeIRNSS_1->setEnabled(false);
            ui->lineEditStdDevCodeAIRNSS_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(IRNSS,FIRSTMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeIRNSS_1->setEnabled(true);
            ui->lineEditStdDevCodeAIRNSS_1->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1IRNSS_1->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseIRNSS_1_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseIRNSS_1->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(IRNSS,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseIRNSS_1->setEnabled(false);
            ui->lineEditStdDevPhaseAIRNSS_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(IRNSS,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseIRNSS_1->setEnabled(true);
            ui->lineEditStdDevPhaseAIRNSS_1->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1IRNSS_1->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCIRNSS_1_currentIndexChanged(int index){
    ui->comboBoxFreqGCIRNSS_1->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCIRNSS_1->setEnabled(false);
            ui->lineEditStdDevGCAIRNSS_1->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(IRNSS,FIRSTMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCIRNSS_1->setEnabled(true);
            ui->lineEditStdDevGCAIRNSS_1->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeIRNSS_1->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1IRNSS_1_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1IRNSS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2IRNSS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2IRNSS_1->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2IRNSS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2IRNSS_1_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2IRNSS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1IRNSS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1IRNSS_1->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1IRNSS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1IRNSS_1_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1IRNSS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2IRNSS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2IRNSS_1->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2IRNSS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2IRNSS_1_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2IRNSS_1->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1IRNSS_1->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1IRNSS_1->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1IRNSS_1->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeIRNSS_1_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeIRNSS_1->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseIRNSS_1->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseIRNSS_1->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseIRNSS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseIRNSS_1_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseIRNSS_1->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeIRNSS_1->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeIRNSS_1->currentIndex()==0) {
        ui->comboBoxMeasGCCodeIRNSS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeIRNSS_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeIRNSS_1->setCurrentIndex(index);
    this->setWeightTypeValues(IRNSS,FIRSTMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBIRNSS_1->setHidden(true);
        ui->frameCodeCIRNSS_1->setHidden(true);
        ui->labelStdDevCodeAUnitIRNSS_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitIRNSS_1->setText("(m)");
        ui->labelStdDevCodeBUnitIRNSS_1->setText("(m)");
        ui->frameCodeBIRNSS_1->setHidden(false);
        ui->frameCodeCIRNSS_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCIRNSS_1->setHidden(true);
        ui->frameCodeBIRNSS_1->setHidden(false);
        ui->labelStdDevCodeAUnitIRNSS_1->setText("(m²)");
        ui->labelStdDevCodeBUnitIRNSS_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCIRNSS_1->setHidden(true);
        ui->frameCodeBIRNSS_1->setHidden(false);
        ui->labelStdDevCodeAUnitIRNSS_1->setText("(m²)");
        ui->labelStdDevCodeBUnitIRNSS_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseIRNSS_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseIRNSS_1->setCurrentIndex(index);
    this->setWeightTypeValues(IRNSS,FIRSTMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBIRNSS_1->setHidden(true);
        ui->framePhaseCIRNSS_1->setHidden(true);
        ui->labelStdDevPhaseAUnitIRNSS_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitIRNSS_1->setText("(m)");
        ui->labelStdDevPhaseBUnitIRNSS_1->setText("(m)");
        ui->framePhaseBIRNSS_1->setHidden(false);
        ui->framePhaseCIRNSS_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCIRNSS_1->setHidden(true);
        ui->framePhaseBIRNSS_1->setHidden(false);
        ui->labelStdDevPhaseAUnitIRNSS_1->setText("(m²)");
        ui->labelStdDevPhaseBUnitIRNSS_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCIRNSS_1->setHidden(true);
        ui->framePhaseBIRNSS_1->setHidden(false);
        ui->labelStdDevPhaseAUnitIRNSS_1->setText("(m²)");
        ui->labelStdDevPhaseBUnitIRNSS_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCIRNSS_1_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCIRNSS_1->setCurrentIndex(index);
    this->setWeightTypeValues(IRNSS,FIRSTMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBIRNSS_1->setHidden(true);
        ui->frameGCCIRNSS_1->setHidden(true);
        ui->labelStdDevGCAUnitIRNSS_1->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitIRNSS_1->setText("(m)");
        ui->labelStdDevGCBUnitIRNSS_1->setText("(m)");
        ui->frameGCBIRNSS_1->setHidden(false);
        ui->frameGCCIRNSS_1->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCIRNSS_1->setHidden(true);
        ui->frameGCIRNSS_1->setHidden(false);
        ui->labelStdDevGCAUnitIRNSS_1->setText("(m²)");
        ui->labelStdDevGCBUnitIRNSS_1->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCIRNSS_1->setHidden(true);
        ui->frameGCBIRNSS_1->setHidden(false);
        ui->labelStdDevGCAUnitIRNSS_1->setText("(m²)");
        ui->labelStdDevGCBUnitIRNSS_1->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxFreqCodeIRNSS_2_currentIndexChanged(int index){
    ui->comboBoxFreqCodeIRNSS_2->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(IRNSS,SECONDMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeIRNSS_2->setEnabled(false);
            ui->lineEditStdDevCodeAIRNSS_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(IRNSS,SECONDMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeIRNSS_2->setEnabled(true);
            ui->lineEditStdDevCodeAIRNSS_2->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1IRNSS_2->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseIRNSS_2_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseIRNSS_2->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(IRNSS,SECONDMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseIRNSS_2->setEnabled(false);
            ui->lineEditStdDevPhaseAIRNSS_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(IRNSS,SECONDMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseIRNSS_2->setEnabled(true);
            ui->lineEditStdDevPhaseAIRNSS_2->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1IRNSS_2->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCIRNSS_2_currentIndexChanged(int index){
    ui->comboBoxFreqGCIRNSS_2->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCIRNSS_2->setEnabled(false);
            ui->lineEditStdDevGCAIRNSS_2->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(IRNSS,SECONDMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCIRNSS_2->setEnabled(true);
            ui->lineEditStdDevGCAIRNSS_2->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeIRNSS_2->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1IRNSS_2_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1IRNSS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2IRNSS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2IRNSS_2->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2IRNSS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2IRNSS_2_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2IRNSS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1IRNSS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1IRNSS_2->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1IRNSS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1IRNSS_2_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1IRNSS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2IRNSS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2IRNSS_2->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2IRNSS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2IRNSS_2_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2IRNSS_2->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1IRNSS_2->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1IRNSS_2->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1IRNSS_2->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeIRNSS_2_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeIRNSS_2->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseIRNSS_2->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseIRNSS_2->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseIRNSS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseIRNSS_2_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseIRNSS_2->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeIRNSS_2->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeIRNSS_2->currentIndex()==0) {
        ui->comboBoxMeasGCCodeIRNSS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeIRNSS_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeIRNSS_2->setCurrentIndex(index);
    this->setWeightTypeValues(IRNSS,SECONDMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBIRNSS_2->setHidden(true);
        ui->frameCodeCIRNSS_2->setHidden(true);
        ui->labelStdDevCodeAUnitIRNSS_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitIRNSS_2->setText("(m)");
        ui->labelStdDevCodeBUnitIRNSS_2->setText("(m)");
        ui->frameCodeBIRNSS_2->setHidden(false);
        ui->frameCodeCIRNSS_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCIRNSS_2->setHidden(true);
        ui->frameCodeBIRNSS_2->setHidden(false);
        ui->labelStdDevCodeAUnitIRNSS_2->setText("(m²)");
        ui->labelStdDevCodeBUnitIRNSS_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCIRNSS_2->setHidden(true);
        ui->frameCodeBIRNSS_2->setHidden(false);
        ui->labelStdDevCodeAUnitIRNSS_2->setText("(m²)");
        ui->labelStdDevCodeBUnitIRNSS_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseIRNSS_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseIRNSS_2->setCurrentIndex(index);
    this->setWeightTypeValues(IRNSS,SECONDMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBIRNSS_2->setHidden(true);
        ui->framePhaseCIRNSS_2->setHidden(true);
        ui->labelStdDevPhaseAUnitIRNSS_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitIRNSS_2->setText("(m)");
        ui->labelStdDevPhaseBUnitIRNSS_2->setText("(m)");
        ui->framePhaseBIRNSS_2->setHidden(false);
        ui->framePhaseCIRNSS_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCIRNSS_2->setHidden(true);
        ui->framePhaseBIRNSS_2->setHidden(false);
        ui->labelStdDevPhaseAUnitIRNSS_2->setText("(m²)");
        ui->labelStdDevPhaseBUnitIRNSS_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCIRNSS_2->setHidden(true);
        ui->framePhaseBIRNSS_2->setHidden(false);
        ui->labelStdDevPhaseAUnitIRNSS_2->setText("(m²)");
        ui->labelStdDevPhaseBUnitIRNSS_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCIRNSS_2_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCIRNSS_2->setCurrentIndex(index);
    this->setWeightTypeValues(IRNSS,SECONDMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBIRNSS_2->setHidden(true);
        ui->frameGCCIRNSS_2->setHidden(true);
        ui->labelStdDevGCAUnitIRNSS_2->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitIRNSS_2->setText("(m)");
        ui->labelStdDevGCBUnitIRNSS_2->setText("(m)");
        ui->frameGCBIRNSS_2->setHidden(false);
        ui->frameGCCIRNSS_2->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCIRNSS_2->setHidden(true);
        ui->frameGCIRNSS_2->setHidden(false);
        ui->labelStdDevGCAUnitIRNSS_2->setText("(m²)");
        ui->labelStdDevGCBUnitIRNSS_2->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCIRNSS_2->setHidden(true);
        ui->frameGCBIRNSS_2->setHidden(false);
        ui->labelStdDevGCAUnitIRNSS_2->setText("(m²)");
        ui->labelStdDevGCBUnitIRNSS_2->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxFreqCodeIRNSS_3_currentIndexChanged(int index){
    ui->comboBoxFreqCodeIRNSS_3->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(IRNSS,THIRDMEASARRAYPOS,CODEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModeCodeIRNSS_3->setEnabled(false);
            ui->lineEditStdDevCodeAIRNSS_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(IRNSS,THIRDMEASARRAYPOS,CODEARRAYPOS,index-1);
            ui->comboBoxStdDevModeCodeIRNSS_3->setEnabled(true);
            ui->lineEditStdDevCodeAIRNSS_3->setEnabled(true);
        }
    }
    ui->comboBoxMeasCodeFreq1IRNSS_3->setCurrentIndex(0);

}
void gLAB_GUI::on_comboBoxFreqPhaseIRNSS_3_currentIndexChanged(int index){
    ui->comboBoxFreqPhaseIRNSS_3->setCurrentIndex(index);
    if (ui->radioButtonSmoothing->isChecked()){
        this->setGNSSMeasurementMeasAll(IRNSS,THIRDMEASARRAYPOS,PHASEARRAYPOS,index);
    }
    else {
        if (index==0){//as order
            ui->comboBoxStdDevModePhaseIRNSS_3->setEnabled(false);
            ui->lineEditStdDevPhaseAIRNSS_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(IRNSS,THIRDMEASARRAYPOS,PHASEARRAYPOS,index-1);
            ui->comboBoxStdDevModePhaseIRNSS_3->setEnabled(true);
            ui->lineEditStdDevPhaseAIRNSS_3->setEnabled(true);
        }
    }
    ui->comboBoxMeasPhaseFreq1IRNSS_3->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxFreqGCIRNSS_3_currentIndexChanged(int index){
    ui->comboBoxFreqGCIRNSS_3->setCurrentIndex(index);
        if (index==0){//auto
            ui->comboBoxStdDevModeGCIRNSS_3->setEnabled(false);
            ui->lineEditStdDevGCAIRNSS_3->setEnabled(false);
        } else {//specify
            this->setGNSSMeasurementMeasAll(IRNSS,THIRDMEASARRAYPOS,GCARRAYPOS,index-1);
            ui->comboBoxStdDevModeGCIRNSS_3->setEnabled(true);
            ui->lineEditStdDevGCAIRNSS_3->setEnabled(true);
        }
    ui->comboBoxMeasGCCodeIRNSS_3->setCurrentIndex(0);
}
void gLAB_GUI::on_comboBoxMeasCodeFreq1IRNSS_3_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq1IRNSS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq2IRNSS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq2IRNSS_3->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq2IRNSS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasCodeFreq2IRNSS_3_currentIndexChanged(int index){
    ui->comboBoxMeasCodeFreq2IRNSS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasCodeFreq1IRNSS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasCodeFreq1IRNSS_3->currentIndex()==0) {
            ui->comboBoxMeasCodeFreq1IRNSS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq1IRNSS_3_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq1IRNSS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq2IRNSS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq2IRNSS_3->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq2IRNSS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasPhaseFreq2IRNSS_3_currentIndexChanged(int index){
    ui->comboBoxMeasPhaseFreq2IRNSS_3->setCurrentIndex(index);
    if (ui->radioButtonDualFreq->isChecked()){
        if (index==0){ //Auto
            ui->comboBoxMeasPhaseFreq1IRNSS_3->setCurrentIndex(index);
        } else if (ui->comboBoxMeasPhaseFreq1IRNSS_3->currentIndex()==0) {
            ui->comboBoxMeasPhaseFreq1IRNSS_3->setCurrentIndex(1);
        }
    }
}
void gLAB_GUI::on_comboBoxMeasGCCodeIRNSS_3_currentIndexChanged(int index){
    ui->comboBoxMeasGCCodeIRNSS_3->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCPhaseIRNSS_3->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCPhaseIRNSS_3->currentIndex()==0) {
        ui->comboBoxMeasGCPhaseIRNSS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxMeasGCPhaseIRNSS_3_currentIndexChanged(int index){
    ui->comboBoxMeasGCPhaseIRNSS_3->setCurrentIndex(index);
    if (index==0){ //Auto
        ui->comboBoxMeasGCCodeIRNSS_3->setCurrentIndex(index);
    } else if (ui->comboBoxMeasGCCodeIRNSS_3->currentIndex()==0) {
        ui->comboBoxMeasGCCodeIRNSS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxStdDevModeCodeIRNSS_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModeCodeIRNSS_3->setCurrentIndex(index);
    this->setWeightTypeValues(IRNSS,THIRDMEASARRAYPOS,CODEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameCodeBIRNSS_3->setHidden(true);
        ui->frameCodeCIRNSS_3->setHidden(true);
        ui->labelStdDevCodeAUnitIRNSS_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevCodeAUnitIRNSS_3->setText("(m)");
        ui->labelStdDevCodeBUnitIRNSS_3->setText("(m)");
        ui->frameCodeBIRNSS_3->setHidden(false);
        ui->frameCodeCIRNSS_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameCodeCIRNSS_3->setHidden(true);
        ui->frameCodeBIRNSS_3->setHidden(false);
        ui->labelStdDevCodeAUnitIRNSS_3->setText("(m²)");
        ui->labelStdDevCodeBUnitIRNSS_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameCodeCIRNSS_3->setHidden(true);
        ui->frameCodeBIRNSS_3->setHidden(false);
        ui->labelStdDevCodeAUnitIRNSS_3->setText("(m²)");
        ui->labelStdDevCodeBUnitIRNSS_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModePhaseIRNSS_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModePhaseIRNSS_3->setCurrentIndex(index);
    this->setWeightTypeValues(IRNSS,THIRDMEASARRAYPOS,PHASEARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->framePhaseBIRNSS_3->setHidden(true);
        ui->framePhaseCIRNSS_3->setHidden(true);
        ui->labelStdDevPhaseAUnitIRNSS_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevPhaseAUnitIRNSS_3->setText("(m)");
        ui->labelStdDevPhaseBUnitIRNSS_3->setText("(m)");
        ui->framePhaseBIRNSS_3->setHidden(false);
        ui->framePhaseCIRNSS_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->framePhaseCIRNSS_3->setHidden(true);
        ui->framePhaseBIRNSS_3->setHidden(false);
        ui->labelStdDevPhaseAUnitIRNSS_3->setText("(m²)");
        ui->labelStdDevPhaseBUnitIRNSS_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->framePhaseCIRNSS_3->setHidden(true);
        ui->framePhaseBIRNSS_3->setHidden(false);
        ui->labelStdDevPhaseAUnitIRNSS_3->setText("(m²)");
        ui->labelStdDevPhaseBUnitIRNSS_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxStdDevModeGCIRNSS_3_currentIndexChanged(int index){
    ui->comboBoxStdDevModeGCIRNSS_3->setCurrentIndex(index);
    this->setWeightTypeValues(IRNSS,THIRDMEASARRAYPOS,GCARRAYPOS,index);
    if (index==0) { //fixed mode
        ui->frameGCBIRNSS_3->setHidden(true);
        ui->frameGCCIRNSS_3->setHidden(true);
        ui->labelStdDevGCAUnitIRNSS_3->setText("(m)");
    } else if (index==1){ //elevation mode
        ui->labelStdDevGCAUnitIRNSS_3->setText("(m)");
        ui->labelStdDevGCBUnitIRNSS_3->setText("(m)");
        ui->frameGCBIRNSS_3->setHidden(false);
        ui->frameGCCIRNSS_3->setHidden(false);
    } else if (index==2){ //sin(elevation)
        ui->frameGCCIRNSS_3->setHidden(true);
        ui->frameGCIRNSS_3->setHidden(false);
        ui->labelStdDevGCAUnitIRNSS_3->setText("(m²)");
        ui->labelStdDevGCBUnitIRNSS_3->setText("(m²)");
    } else if (index>2){ //SNR, SNR+elevation mode
        ui->frameGCCIRNSS_3->setHidden(true);
        ui->frameGCBIRNSS_3->setHidden(false);
        ui->labelStdDevGCAUnitIRNSS_3->setText("(m²)");
        ui->labelStdDevGCBUnitIRNSS_3->setText("(m²·Hz)");
    }
}
void gLAB_GUI::on_comboBoxSmoothWithIRNSS_1_currentIndexChanged(int index){
    ui->comboBoxSmoothWithIRNSS_1->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithIRNSS_1->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(IRNSS,FIRSTMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithIRNSS_1->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2IRNSS_1->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2IRNSS_1->setHidden(false);

    this->setSmoothWithFreqAll(IRNSS,FIRSTMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1IRNSS_1->setHidden(false); //GC
    else ui->frameSmoothCode1IRNSS_1->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1IRNSS_1_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[IRNSS][FIRSTMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1IRNSS_1->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(IRNSS,FIRSTMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1IRNSS_1->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1IRNSS_1->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithIRNSS_1->currentIndex()>2 && ui->comboBoxSmoothFreq2IRNSS_1->currentIndex()==index){
        ui->comboBoxSmoothFreq2IRNSS_1->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[IRNSS][FIRSTMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2IRNSS_1_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[IRNSS][FIRSTMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2IRNSS_1->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(IRNSS,FIRSTMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2IRNSS_1->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithIRNSS_1->currentIndex()>2 && ui->comboBoxSmoothFreq1IRNSS_1->currentIndex()==index){
        ui->comboBoxSmoothFreq1IRNSS_1->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[IRNSS][FIRSTMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1IRNSS_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1IRNSS_1->count()>0) ui->comboBoxSmoothCode1IRNSS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1IRNSS_1->count()>0) ui->comboBoxSmoothPhase1IRNSS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2IRNSS_1->count()>0) ui->comboBoxSmoothPhase2IRNSS_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1IRNSS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1IRNSS_1->count()>0 && ui->comboBoxSmoothPhase1IRNSS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase1IRNSS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2IRNSS_1->count()>0 && ui->comboBoxSmoothPhase2IRNSS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase2IRNSS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1IRNSS_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1IRNSS_1->count()>0) ui->comboBoxSmoothCode1IRNSS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1IRNSS_1->count()>0) ui->comboBoxSmoothPhase1IRNSS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2IRNSS_1->count()>0) ui->comboBoxSmoothPhase2IRNSS_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1IRNSS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1IRNSS_1->count()>0 && ui->comboBoxSmoothCode1IRNSS_1->currentIndex()==0 ) ui->comboBoxSmoothCode1IRNSS_1->setCurrentIndex(index>=ui->comboBoxSmoothCode1IRNSS_1->count()?1:index);
        if ( ui->comboBoxSmoothPhase2IRNSS_1->count()>0 && ui->comboBoxSmoothPhase2IRNSS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase2IRNSS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2IRNSS_1_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1IRNSS_1->count()>0) ui->comboBoxSmoothCode1IRNSS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1IRNSS_1->count()>0) ui->comboBoxSmoothPhase1IRNSS_1->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2IRNSS_1->count()>0) ui->comboBoxSmoothPhase2IRNSS_1->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2IRNSS_1->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1IRNSS_1->count()>0 && ui->comboBoxSmoothCode1IRNSS_1->currentIndex()==0 ) ui->comboBoxSmoothCode1IRNSS_1->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1IRNSS_1->count()>0 && ui->comboBoxSmoothPhase1IRNSS_1->currentIndex()==0 ) ui->comboBoxSmoothPhase1IRNSS_1->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothWithIRNSS_2_currentIndexChanged(int index){
    ui->comboBoxSmoothWithIRNSS_2->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithIRNSS_2->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(IRNSS,SECONDMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithIRNSS_2->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2IRNSS_2->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2IRNSS_2->setHidden(false);

    this->setSmoothWithFreqAll(IRNSS,SECONDMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1IRNSS_2->setHidden(false); //GC
    else ui->frameSmoothCode1IRNSS_2->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1IRNSS_2_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[IRNSS][SECONDMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1IRNSS_2->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(IRNSS,SECONDMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1IRNSS_2->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1IRNSS_2->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithIRNSS_2->currentIndex()>2 && ui->comboBoxSmoothFreq2IRNSS_2->currentIndex()==index){
        ui->comboBoxSmoothFreq2IRNSS_2->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[IRNSS][SECONDMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2IRNSS_2_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[IRNSS][SECONDMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2IRNSS_2->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(IRNSS,SECONDMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2IRNSS_2->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithIRNSS_2->currentIndex()>2 && ui->comboBoxSmoothFreq1IRNSS_2->currentIndex()==index){
        ui->comboBoxSmoothFreq1IRNSS_2->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[IRNSS][SECONDMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1IRNSS_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1IRNSS_2->count()>0) ui->comboBoxSmoothCode1IRNSS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1IRNSS_2->count()>0) ui->comboBoxSmoothPhase1IRNSS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2IRNSS_2->count()>0) ui->comboBoxSmoothPhase2IRNSS_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1IRNSS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1IRNSS_2->count()>0 && ui->comboBoxSmoothPhase1IRNSS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase1IRNSS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2IRNSS_2->count()>0 && ui->comboBoxSmoothPhase2IRNSS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase2IRNSS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1IRNSS_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1IRNSS_2->count()>0) ui->comboBoxSmoothCode1IRNSS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1IRNSS_2->count()>0) ui->comboBoxSmoothPhase1IRNSS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2IRNSS_2->count()>0) ui->comboBoxSmoothPhase2IRNSS_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1IRNSS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1IRNSS_2->count()>0 && ui->comboBoxSmoothCode1IRNSS_2->currentIndex()==0 ) ui->comboBoxSmoothCode1IRNSS_2->setCurrentIndex(index>=ui->comboBoxSmoothCode1IRNSS_2->count()?1:index);
        if ( ui->comboBoxSmoothPhase2IRNSS_2->count()>0 && ui->comboBoxSmoothPhase2IRNSS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase2IRNSS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2IRNSS_2_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1IRNSS_2->count()>0) ui->comboBoxSmoothCode1IRNSS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1IRNSS_2->count()>0) ui->comboBoxSmoothPhase1IRNSS_2->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2IRNSS_2->count()>0) ui->comboBoxSmoothPhase2IRNSS_2->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2IRNSS_2->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1IRNSS_2->count()>0 && ui->comboBoxSmoothCode1IRNSS_2->currentIndex()==0 ) ui->comboBoxSmoothCode1IRNSS_2->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1IRNSS_2->count()>0 && ui->comboBoxSmoothPhase1IRNSS_2->currentIndex()==0 ) ui->comboBoxSmoothPhase1IRNSS_2->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothWithIRNSS_3_currentIndexChanged(int index){
    ui->comboBoxSmoothWithIRNSS_3->setCurrentIndex(index);

    //Auto
    if (index<=0) {
        ui->frameSmoothWithIRNSS_3->setHidden(true);
        this->setSmoothWithFreqComboBoxValue(IRNSS,THIRDMEASARRAYPOS,-1,-1);
    }
    else ui->frameSmoothWithIRNSS_3->setHidden(false);
    //single frequency
    if (index<3) ui->frameSmoothFreq2IRNSS_3->setHidden(true);
    //dual frequency
    else ui->frameSmoothFreq2IRNSS_3->setHidden(false);

    this->setSmoothWithFreqAll(IRNSS,THIRDMEASARRAYPOS,index);

    if (index==2) ui->frameSmoothCode1IRNSS_3->setHidden(false); //GC
    else ui->frameSmoothCode1IRNSS_3->setHidden(true); //not GC
}
void gLAB_GUI::on_comboBoxSmoothFreq1IRNSS_3_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[IRNSS][THIRDMEASARRAYPOS][0];

    ui->comboBoxSmoothFreq1IRNSS_3->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(IRNSS,THIRDMEASARRAYPOS,index,-1);
    ui->comboBoxSmoothCode1IRNSS_3->setCurrentIndex(0);
    ui->comboBoxSmoothPhase1IRNSS_3->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithIRNSS_3->currentIndex()>2 && ui->comboBoxSmoothFreq2IRNSS_3->currentIndex()==index){
        ui->comboBoxSmoothFreq2IRNSS_3->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[IRNSS][THIRDMEASARRAYPOS][0]=index;
}
void gLAB_GUI::on_comboBoxSmoothFreq2IRNSS_3_currentIndexChanged(int index) {
    int last_index=smoothWithFreqIndexAll[IRNSS][THIRDMEASARRAYPOS][1];

    ui->comboBoxSmoothFreq2IRNSS_3->setCurrentIndex(index);
    this->setSmoothWithMeasComboBoxValue(IRNSS,THIRDMEASARRAYPOS,-1,index);
    ui->comboBoxSmoothPhase2IRNSS_3->setCurrentIndex(0);

    if (smoothWithFreqNoSame && ui->comboBoxSmoothWithIRNSS_3->currentIndex()>2 && ui->comboBoxSmoothFreq1IRNSS_3->currentIndex()==index){
        ui->comboBoxSmoothFreq1IRNSS_3->setCurrentIndex(last_index);
    }
    smoothWithFreqIndexAll[IRNSS][THIRDMEASARRAYPOS][1]=index;
}
void gLAB_GUI::on_comboBoxSmoothCode1IRNSS_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1IRNSS_3->count()>0) ui->comboBoxSmoothCode1IRNSS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1IRNSS_3->count()>0) ui->comboBoxSmoothPhase1IRNSS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2IRNSS_3->count()>0) ui->comboBoxSmoothPhase2IRNSS_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothCode1IRNSS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase1IRNSS_3->count()>0 && ui->comboBoxSmoothPhase1IRNSS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase1IRNSS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothPhase2IRNSS_3->count()>0 && ui->comboBoxSmoothPhase2IRNSS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase2IRNSS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase1IRNSS_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1IRNSS_3->count()>0) ui->comboBoxSmoothCode1IRNSS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1IRNSS_3->count()>0) ui->comboBoxSmoothPhase1IRNSS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2IRNSS_3->count()>0) ui->comboBoxSmoothPhase2IRNSS_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase1IRNSS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1IRNSS_3->count()>0 && ui->comboBoxSmoothCode1IRNSS_3->currentIndex()==0 ) ui->comboBoxSmoothCode1IRNSS_3->setCurrentIndex(index>=ui->comboBoxSmoothCode1IRNSS_3->count()?1:index);
        if ( ui->comboBoxSmoothPhase2IRNSS_3->count()>0 && ui->comboBoxSmoothPhase2IRNSS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase2IRNSS_3->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_comboBoxSmoothPhase2IRNSS_3_currentIndexChanged(int index){
    if (index==0){
        if (ui->comboBoxSmoothCode1IRNSS_3->count()>0) ui->comboBoxSmoothCode1IRNSS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase1IRNSS_3->count()>0) ui->comboBoxSmoothPhase1IRNSS_3->setCurrentIndex(0);
        if (ui->comboBoxSmoothPhase2IRNSS_3->count()>0) ui->comboBoxSmoothPhase2IRNSS_3->setCurrentIndex(0);
    }
    else {
        ui->comboBoxSmoothPhase2IRNSS_3->setCurrentIndex(index);
        if ( ui->comboBoxSmoothCode1IRNSS_3->count()>0 && ui->comboBoxSmoothCode1IRNSS_3->currentIndex()==0 ) ui->comboBoxSmoothCode1IRNSS_3->setCurrentIndex(1);
        if ( ui->comboBoxSmoothPhase1IRNSS_3->count()>0 && ui->comboBoxSmoothPhase1IRNSS_3->currentIndex()==0 ) ui->comboBoxSmoothPhase1IRNSS_3->setCurrentIndex(1);
    }
}

// Function to show or hide the troposphere parameters
void gLAB_GUI::on_checkBoxEstimateTroposphere_clicked(bool checked) {
    ui->checkBoxEstimateTroposphere->setChecked(checked);
    ui->frameTroposphereParameters->setHidden(!checked);
}

// Function to show or hide the line edit to enter the maximum HDOP
void gLAB_GUI::on_checkBoxMaxHDOP_clicked(bool checked) {
    ui->checkBoxMaxHDOP->setChecked(checked);
    ui->lineEditMaxHDOP->setHidden(!checked);
    if (ui->checkBoxMaxHDOP->isChecked()==true && ui->checkBoxMaxPDOP->isChecked()==true ) {
        ui->frameHDOPorPDOP->setHidden(false);
    } else {
        ui->frameHDOPorPDOP->setHidden(true);
    }
}

// Function to show or hide the line edit to enter the maximum PDOP
void gLAB_GUI::on_checkBoxMaxPDOP_clicked(bool checked) {
    ui->checkBoxMaxPDOP->setChecked(checked);
    ui->lineEditMaxPDOP->setHidden(!checked);
    if (ui->checkBoxMaxHDOP->isChecked()==true && ui->checkBoxMaxPDOP->isChecked()==true ) {
        ui->frameHDOPorPDOP->setHidden(false);
    } else {
        ui->frameHDOPorPDOP->setHidden(true);
    }
}

// Function to show or hide the line edit to enter the maximum GDOP
void gLAB_GUI::on_checkBoxMaxGDOP_clicked(bool checked) {
    ui->checkBoxMaxGDOP->setChecked(checked);
    ui->lineEditMaxGDOP->setHidden(!checked);
}

// Function to show or hide the line edit to enter the prefit outlier threshold
void gLAB_GUI::on_checkBoxPrefitOutliers_clicked(bool checked) {
    ui->checkBoxPrefitOutliers->setChecked(checked);
    ui->lineEditPrefitOutliers->setHidden(!checked);
}

// Function to set the filter parameters for static positioning
void gLAB_GUI::on_radioButtonStatic_clicked() {
    ui->radioButtonStatic->setChecked(true);
    ui->lineEditPhiCoordinates->setText("1"); // Phi
    ui->lineEditQcoordinates->setText("0"); // Q
    ui->labelQcoordinatesUnit->setText("(m²)");
}

// Function to set the filter parameters for kinematic positioning
void gLAB_GUI::on_radioButtonKinematic_clicked() {
    ui->radioButtonKinematic->setChecked(true);
    ui->lineEditPhiCoordinates->setText("0"); // Phi
    ui->lineEditQcoordinates->setText("1e8"); // Q
    ui->labelQcoordinatesUnit->setText("(m²)");
}
void gLAB_GUI::on_radioButtonRandomwalkCoordinates_clicked(){
    ui->radioButtonRandomwalkCoordinates->setChecked(true);
    ui->lineEditPhiCoordinates->setText("1");
    ui->lineEditQcoordinates->setText("70");
    ui->labelQcoordinatesUnit->setText("(m²/s)");
}
void gLAB_GUI::on_radioButtonConstantClock_clicked(){
    ui->radioButtonConstantClock->setChecked(true);
    //this->on_comboBoxPoClockUnit_currentIndexChanged(0);
    if (ui->comboBoxPoClockUnit->currentIndex()==0){//m²
        ui->lineEditPoClock->setText("9e10");
    }
    else if (ui->comboBoxPoClockUnit->currentIndex()==1){//ns²
        ui->lineEditPoClock->setText("1e12");
    }
    ui->lineEditPhiClock->setText("1");
    ui->stackedWidgetQClockUnit->setCurrentIndex(0);
    ui->lineEditQclock->setText("0");
    if (lastRadioButtonClkFilterRandom==1) {
        ui->comboBoxQClockUnitNormal->setCurrentIndex(ui->comboBoxQClockUnitRandom->currentIndex());
    }
    lastRadioButtonClkFilterRandom=0;
}
void gLAB_GUI::on_radioButtonWhiteNoiseClock_clicked(){
    ui->radioButtonWhiteNoiseClock->setChecked(true);
    //this->on_comboBoxPoClockUnit_currentIndexChanged(0);
    if (ui->comboBoxPoClockUnit->currentIndex()==0){//m²
        ui->lineEditPoClock->setText("9e10");
    }
    else if (ui->comboBoxPoClockUnit->currentIndex()==1){//ns²
        ui->lineEditPoClock->setText("1e12");
    }
    ui->lineEditPhiClock->setText("0");
    ui->stackedWidgetQClockUnit->setCurrentIndex(0);
    if (ui->comboBoxQClockUnitNormal->currentIndex()==0){//m²
        ui->lineEditQclock->setText("9e10");
    }
    else if (ui->comboBoxQClockUnitNormal->currentIndex()==1) {//ns²
        ui->lineEditQclock->setText("1e12");
    }
    if (lastRadioButtonClkFilterRandom==1) {
        ui->comboBoxQClockUnitNormal->setCurrentIndex(ui->comboBoxQClockUnitRandom->currentIndex());
    }
    lastRadioButtonClkFilterRandom=0;
}
void gLAB_GUI::on_radioButtonRandomwalkClock_clicked(){
    ui->radioButtonRandomwalkClock->setChecked(true);
    //this->on_comboBoxPoClockUnit_currentIndexChanged(0);
    if (ui->comboBoxPoClockUnit->currentIndex()==0){//m²
        ui->lineEditPoClock->setText("9e10");
    }
    else if (ui->comboBoxPoClockUnit->currentIndex()==1){//ns²
        ui->lineEditPoClock->setText("1e12");
    }
    ui->lineEditPhiClock->setText("1");
    ui->stackedWidgetQClockUnit->setCurrentIndex(1);
    ui->comboBoxQClockUnitRandom->setCurrentIndex(ui->comboBoxQClockUnitNormal->currentIndex());
    if (ui->comboBoxQClockUnitRandom->currentIndex()==0){//m²
        ui->lineEditQclock->setText("9");
    }
    else if (ui->comboBoxQClockUnitRandom->currentIndex()==1) {//ns²
        ui->lineEditQclock->setText("100");
    }
    lastRadioButtonClkFilterRandom=1;
}
void gLAB_GUI::on_radioButtonConstantISCB_clicked(){
    ui->radioButtonConstantISCB->setChecked(true);
    //this->on_comboBoxPoISCBUnit_currentIndexChanged(0);
    if (ui->comboBoxPoISCBUnit->currentIndex()==0){//m²
        ui->lineEditPoISCB->setText("9e10");
    }
    else if (ui->comboBoxPoISCBUnit->currentIndex()==1){//ns²
        ui->lineEditPoISCB->setText("1e12");
    }
    ui->lineEditPhiISCB->setText("1");
    ui->stackedWidgetQISCBUnit->setCurrentIndex(0);
    ui->lineEditQISCB->setText("0");
    if (lastRadioButtonISCFilterRandom==1) {
        ui->comboBoxQISCBUnitNormal->setCurrentIndex(ui->comboBoxQISCBUnitRandom->currentIndex());
    }
    lastRadioButtonISCFilterRandom=0;
}
void gLAB_GUI::on_radioButtonWhiteNoiseISCB_clicked(){
    ui->radioButtonWhiteNoiseISCB->setChecked(true);
    //this->on_comboBoxPoISCBUnit_currentIndexChanged(0);
    if (ui->comboBoxPoISCBUnit->currentIndex()==0){//m²
        ui->lineEditPoISCB->setText("9e10");
    }
    else if (ui->comboBoxPoISCBUnit->currentIndex()==1){//ns²
        ui->lineEditPoISCB->setText("1e12");
    }
    ui->lineEditPhiISCB->setText("0");
    ui->stackedWidgetQISCBUnit->setCurrentIndex(0);
    if (ui->comboBoxQISCBUnitRandom->currentIndex()==0){//m²
        ui->lineEditQISCB->setText("9e10");
    }
    else if (ui->comboBoxQISCBUnitRandom->currentIndex()==1){//ns²
        ui->lineEditQISCB->setText("1e12");
    }
    if (lastRadioButtonISCFilterRandom==1) {
        ui->comboBoxQISCBUnitNormal->setCurrentIndex(ui->comboBoxQISCBUnitRandom->currentIndex());
    }
    lastRadioButtonISCFilterRandom=0;
}
void gLAB_GUI::on_radioButtonRandomwalkISCB_clicked(){
    ui->radioButtonRandomwalkISCB->setChecked(true);
    if (ui->comboBoxPoISCBUnit->currentIndex()==0){//m²
        ui->lineEditPoISCB->setText("9e10");
    }
    else if (ui->comboBoxPoISCBUnit->currentIndex()==1){//ns²
        ui->lineEditPoISCB->setText("1e12");
    }
    ui->lineEditPhiISCB->setText("1");
    ui->stackedWidgetQISCBUnit->setCurrentIndex(1);
    ui->comboBoxQISCBUnitRandom->setCurrentIndex(ui->comboBoxQISCBUnitNormal->currentIndex());
    if (ui->comboBoxQISCBUnitRandom->currentIndex()==0){//m²
        ui->lineEditQISCB->setText("9");
    }
    else if (ui->comboBoxQISCBUnitRandom->currentIndex()==1){//ns²
        ui->lineEditQISCB->setText("100");
    }
    lastRadioButtonISCFilterRandom=1;
}

//This function currently has no use after being modified. Left here in case in the future is useful
void gLAB_GUI::on_comboBoxPoClockUnit_currentIndexChanged(int index){
    ui->comboBoxPoClockUnit->setCurrentIndex(index);
}

//This function currently has no use after being modified. Left here in case in the future is useful
void gLAB_GUI::on_comboBoxPoISCBUnit_currentIndexChanged(int index){
    ui->comboBoxPoISCBUnit->setCurrentIndex(index);
}

//This function currently has no use after being modified. Left here in case in the future is useful
void gLAB_GUI::on_comboBoxQClockUnitNormal_currentIndexChanged(int index){
    ui->comboBoxQClockUnitNormal->setCurrentIndex(index);
}

//This function currently has no use after being modified. Left here in case in the future is useful
void gLAB_GUI::on_comboBoxQISCBUnitNormal_currentIndexChanged(int index){
    ui->comboBoxQISCBUnitNormal->setCurrentIndex(index);
}

//This function currently has no use after being modified. Left here in case in the future is useful
void gLAB_GUI::on_comboBoxQClockUnitRandom_currentIndexChanged(int index){
    ui->comboBoxQClockUnitRandom->setCurrentIndex(index);
}

//This function currently has no use after being modified. Left here in case in the future is useful
void gLAB_GUI::on_comboBoxQISCBUnitRandom_currentIndexChanged(int index){
    ui->comboBoxQISCBUnitRandom->setCurrentIndex(index);
}

void gLAB_GUI::on_groupBoxRefGNSSClock_clicked(bool checked){
    ui->groupBoxRefGNSSClock->setChecked(checked);
    ui->frameRefGNSSClock->setHidden(!checked);
}

void gLAB_GUI::userRefGNSSClock_2_Command(QString const *userRefGNSSClock,QString *refGNSSClockCmd){
    *refGNSSClockCmd="";
    for (int i=0; i<MAX_GNSS; i++){
        if (userRefGNSSClock[i].length()<3) break;
        else if (userRefGNSSClock[i]=="GPS") *refGNSSClockCmd+="G";
        else if (userRefGNSSClock[i]=="Galileo") *refGNSSClockCmd+="E";
        else if (userRefGNSSClock[i]=="GLONASS") *refGNSSClockCmd+="R";
        else if (userRefGNSSClock[i]=="BDS") *refGNSSClockCmd+="C";
        else if (userRefGNSSClock[i]=="QZSS") *refGNSSClockCmd+="J";
        else if (userRefGNSSClock[i]=="IRNSS") *refGNSSClockCmd+="I";
        else if (userRefGNSSClock[i]=="GEO") *refGNSSClockCmd+="S";
    }
}

void gLAB_GUI::command_2_UserRefGNSSClock(QString const *refGNSSClockCmd,QString *userRefGNSSClock,int *nRefGNSSClockCount, QString *warningString){
    QString GNSSList[MAX_GNSS];
    int     GNSSused[MAX_GNSS]={0};
    int     duplicatedConstellations=0;
    *nRefGNSSClockCount=0;
    for (int i=0; i<MAX_GNSS; i++){
        userRefGNSSClock[i]="";
        GNSSList[i]=RefGNSSClockPriority[i]; //Copy the order from the global constant
    }
    for (int i=0; i<refGNSSClockCmd->length(); i++){
        if ( refGNSSClockCmd[0][i]=='G' || refGNSSClockCmd[0][i]=='g' ) {
            userRefGNSSClock[i]="GPS";
            GNSSList[0]="";
            GNSSused[GPS]++;
            (*nRefGNSSClockCount)++;
        }
        else if ( refGNSSClockCmd[0][i]=='E' || refGNSSClockCmd[0][i]=='e' ) {
            userRefGNSSClock[i]="Galileo";
            GNSSList[1]="";
            GNSSused[Galileo]++;
            (*nRefGNSSClockCount)++;
        }
        else if ( refGNSSClockCmd[0][i]=='R' || refGNSSClockCmd[0][i]=='r' ) {
            userRefGNSSClock[i]="GLONASS";
            GNSSList[2]="";
            GNSSused[GLONASS]++;
            (*nRefGNSSClockCount)++;
        }
        else if ( refGNSSClockCmd[0][i]=='C' || refGNSSClockCmd[0][i]=='c' ) {
            userRefGNSSClock[i]="BDS";
            GNSSList[3]="";
            GNSSused[BDS]++;
            (*nRefGNSSClockCount)++;
        }
        else if ( refGNSSClockCmd[0][i]=='J' || refGNSSClockCmd[0][i]=='j' ) {
            userRefGNSSClock[i]="QZSS";
            GNSSList[4]="";
            GNSSused[QZSS]++;
            (*nRefGNSSClockCount)++;
        }
        else if ( refGNSSClockCmd[0][i]=='I' || refGNSSClockCmd[0][i]=='i' ) {
            userRefGNSSClock[i]="IRNSS";
            GNSSList[5]="";
            GNSSused[IRNSS]++;
            (*nRefGNSSClockCount)++;
        }
        else if ( refGNSSClockCmd[0][i]=='S' || refGNSSClockCmd[0][i]=='s' ) {
            userRefGNSSClock[i]="GEO";
            GNSSList[6]="";
            GNSSused[GEO]++;
            (*nRefGNSSClockCount)++;
        } else {
            *warningString += QStringLiteral("Invalid constellation letter '%1' in argument '%2' for parameter '-filter:refclkonlyorder'. It was skipped.\n").arg(refGNSSClockCmd[0][i]).arg(refGNSSClockCmd[0]);
            *nRefGNSSClockCount=0;
            return;
        }
    }
    //Check for duplicated constellations
    for (int i=0; i<MAX_GNSS; i++) {
        if (GNSSused[i]>1) {
            *warningString += QStringLiteral("%1 constellation is provided %2 times in '-filter:refclkonlyorder' parameter, but it only can be provided once. It was skipped.\n").arg(GNSSName[i]).arg(GNSSused[i]);
            duplicatedConstellations=1;
        }
    }
    if (duplicatedConstellations>0) {
        *nRefGNSSClockCount=0; //Set it to zero to indicate error
        return;
    } else if (*nRefGNSSClockCount==0) {
        *warningString += QStringLiteral("No valid constellation found in argument '%1' for parameter '-filter:refclkonlyorder'. It was skipped.\n").arg(refGNSSClockCmd[0]);
        return;
    }

    //complement userRefGNSSClock
    int iRefGNSSClock=*nRefGNSSClockCount;
    for (int i=0; i<MAX_GNSS && iRefGNSSClock<MAX_GNSS; i++) {
        if (GNSSList[i].length()<3) continue;
        userRefGNSSClock[iRefGNSSClock++]=GNSSList[i];
    }
}
//select/unselect reference GNSS clock
void gLAB_GUI::doubleClick_RefGNSSClock(int selectFlag,QString sGNSS){
    for (int i=1; i<ui->tableWidgetRefGNSSClock->columnCount();i++){
        if (ui->tableWidgetRefGNSSClock->item(1,i)->text()==sGNSS){
            //select
            if ( ui->groupBoxRefGNSSClock->isChecked() && selectFlag==1 && ui->tableWidgetRefGNSSClock->item(1,i)->background().color().name()==RedColor){
                ui->tableWidgetRefGNSSClock->setCurrentCell(1,i);
                this->refClockItem_doubleClicked(ui->tableWidgetRefGNSSClock->item(1,i));
            }
            //unselect
            else if ( ui->groupBoxRefGNSSClock->isChecked() && selectFlag==0 && ui->tableWidgetRefGNSSClock->item(1,i)->background().color().name()==GreenColor){
                ui->tableWidgetRefGNSSClock->setCurrentCell(1,i);
                this->refClockItem_doubleClicked(ui->tableWidgetRefGNSSClock->item(1,i));
            }
            break;
        }
    }
}
//set Reference Constellation as selected/unselected by double-clicked
void gLAB_GUI::refClockItem_doubleClicked(QTableWidgetItem *tableItem){
    if (tableItem->text()=="") return;
    QTableWidget *pTable=tableItem->tableWidget();
    int irow=tableItem->row(), icolumn=tableItem->column(), nColumnCount=pTable->columnCount();
    //reference constellation item
    if (irow>0&&icolumn>0){
        //unselected to selected
        if (tableItem->background().color().name()==RedColor){
            for (int i=1; i<nColumnCount; i++){
                if (pTable->item(irow,i)->background().color().name()==RedColor){
                    this->moveReferenceGNSSColumn(pTable,icolumn,i,1);
                    pTable->item(irow,i)->setBackground(gnssSelected);
                    pTable->clearSelection();
                    break;
                }
            }
        } else {//selected to unselected
            for (int i=nColumnCount-1; i>0; i--){
                if ((pTable->item(irow,i)->background().color().name()!=RedColor&&pTable->item(irow,i)->text()!="")){
                    this->moveReferenceGNSSColumn(pTable,icolumn,i,1);
                    pTable->item(irow,i)->setBackground(gnssUnSelected);
                    break;
                }
            }
            pTable->clearSelection();
        }
    }
}
//exchange between two Reference Constellation Columns
void gLAB_GUI::moveReferenceGNSSColumn(QTableWidget *pTable, int currentColumn, int toColumn, int doubleClickFlag)
{
    int iRow=pTable->currentRow();
    int nColumnCount = pTable->columnCount();

    if (currentColumn<1 || toColumn <1 || currentColumn>=nColumnCount || toColumn>=nColumnCount) return;
    //return if it's not the reference constellation
    if (iRow!=1) return;
    //return if currentRow reference constellation or toRow reference constellation is unselected
    if (!doubleClickFlag&&(pTable->item(iRow,currentColumn)->background().color().name()==RedColor||pTable->item(iRow,toColumn)->background().color().name()==RedColor)) return;
    if (pTable == nullptr)
        return;

    if (currentColumn == toColumn) return;

    if (pTable->item(iRow,currentColumn)->text()==""||pTable->item(iRow,toColumn)->text()=="") return;

    QString Meas1,Meas2;
    int moveStep=currentColumn<toColumn?1:-1;
    for (int i=0; abs(i)<abs(currentColumn-toColumn); i+=moveStep){
        Meas1=pTable->item(iRow,currentColumn+i)->text();
        Meas2=pTable->item(iRow,currentColumn+i+moveStep)->text();
        pTable->item(iRow,currentColumn+i)->setText(Meas2);
        pTable->item(iRow,currentColumn+i+moveStep)->setText(Meas1);
    }

    pTable->setCurrentCell(iRow,toColumn);
}
void gLAB_GUI::on_pushButtonRefGNSSClockSetDefault_clicked(){
    for (int i=1; i<ui->tableWidgetRefGNSSClock->columnCount();i++){
        ui->tableWidgetRefGNSSClock->item(1,i)->setText(RefGNSSClockPriority[i-1]);
        if (i!=ui->tableWidgetRefGNSSClock->columnCount()-1) ui->tableWidgetRefGNSSClock->item(1,i)->setBackground(gnssSelected);
        else ui->tableWidgetRefGNSSClock->item(1,i)->setBackground(gnssUnSelected);
    }
}
void gLAB_GUI::on_pushButtonRefGNSSClockBoost_clicked(){
    this->moveReferenceGNSSColumn(ui->tableWidgetRefGNSSClock,ui->tableWidgetRefGNSSClock->currentColumn(),ui->tableWidgetRefGNSSClock->currentColumn()-1,0);
}
void gLAB_GUI::on_pushButtonRefGNSSClockLower_clicked(){
    this->moveReferenceGNSSColumn(ui->tableWidgetRefGNSSClock,ui->tableWidgetRefGNSSClock->currentColumn(),ui->tableWidgetRefGNSSClock->currentColumn()+1,0);
}
void gLAB_GUI::on_pushButtonRefGNSSClockSelectAll_clicked(){
    for (int i=1; i<ui->tableWidgetRefGNSSClock->columnCount();i++){
        ui->tableWidgetRefGNSSClock->item(1,i)->setBackground(gnssSelected);
    }
}
void gLAB_GUI::on_pushButtonRefGNSSClockUnselectAll_clicked(){
    for (int i=1; i<ui->tableWidgetRefGNSSClock->columnCount();i++){
        ui->tableWidgetRefGNSSClock->item(1,i)->setBackground(gnssUnSelected);
    }
}
void gLAB_GUI::on_groupBoxISCB_clicked(bool checked){
    ui->groupBoxISCB->setChecked(checked);
    ui->frameISCB->setHidden(!checked);
    if (checked){
        for (int i=0; i<MAX_GNSS; i++){
            if (CheckBoxGNSS4RefClock[i]->isChecked()) {
                this->select_ISCBGNSS(1,RefGNSSClockPriority[i]);
            } else {
                this->select_ISCBGNSS(0,RefGNSSClockPriority[i]);
            }
        }
    }
}
void gLAB_GUI::ISCBItem_textChanged(QTableWidgetItem *tableItem){
    if (tableItem->background().color().name()!=RedColor&&tableItem->column()!=0&&tableItem->row()!=0){
        QString ISCBStr=tableItem->text();
        if (ISCBStr!="0"){
            double ISCBvalue = ISCBStr.toDouble();
            if (ISCBvalue==0){
                tableItem->setText("Estimate");
            }
        }
    }
}
void gLAB_GUI::on_pushButtonISCBEstimateSelected_clicked(){
    QTableWidgetItem *pItem=ui->tableWidgetISCB->currentItem();
    if (!pItem || pItem->row()<=0 || pItem->column()<=0) return;
    if (pItem->background().color().name()!=RedColor) pItem->setText("Estimate");
}
void gLAB_GUI::on_pushButtonISCBEstimateAll_clicked(){
    for (int i=2; i<ui->tableWidgetISCB->columnCount(); i++){
        for (int j=1; j<i; j++){
            QTableWidgetItem *pItem=ui->tableWidgetISCB->item(j,i);
            if (pItem->background().color().name()!=RedColor) pItem->setText("Estimate");
        }
    }
}
void gLAB_GUI::select_ISCBGNSS(int selectFlag,QString sGNSS){
    for (int i=1; i<ui->tableWidgetISCB->columnCount();i++){
        if (ui->tableWidgetISCB->item(0,i)->text()==sGNSS){
            //select
            if ( ui->groupBoxISCB->isChecked() && selectFlag==1 && ui->tableWidgetISCB->item(0,i)->background().color().name() == ISCBTrickColor){
                // Column i
                ui->tableWidgetISCB->item(0,i)->setBackground(ISCBTitleSelected);
                for (int j=1; j<i; j++){
                    if (ui->tableWidgetISCB->item(j,0)->background().color().name() != ISCBTrickColor){
                        ui->tableWidgetISCB->item(j,i)->setBackground(ISCBGNSSSelected);
                        ui->tableWidgetISCB->item(j,i)->setText("Estimate");
                        ui->tableWidgetISCB->item(j,i)->setFlags(ui->tableWidgetISCB->item(j,i)->flags()|Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                    }
                }
                // row i
                ui->tableWidgetISCB->item(i,0)->setBackground(ISCBTitleSelected);
                for (int j=i+1; j<ui->tableWidgetISCB->columnCount(); j++){
                    if (ui->tableWidgetISCB->item(0,j)->background().color().name() != ISCBTrickColor){
                        ui->tableWidgetISCB->item(i,j)->setBackground(ISCBGNSSSelected);
                        ui->tableWidgetISCB->item(i,j)->setText("Estimate");
                        ui->tableWidgetISCB->item(i,j)->setFlags(ui->tableWidgetISCB->item(j,i)->flags()|Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                    }
                }
            }
            //unselect
            else if ( ui->groupBoxISCB->isChecked() && selectFlag==0 && ui->tableWidgetISCB->item(0,i)->background().color().name() != ISCBTrickColor){
                // Column i
                ui->tableWidgetISCB->item(0,i)->setBackground(ISCBTitleTrick);
                for (int j=1; j<i; j++){
                    if (ui->tableWidgetISCB->item(j,i)->background().color().name() != RedColor){
                        ui->tableWidgetISCB->item(j,i)->setBackground(gnssUnSelected);
                        ui->tableWidgetISCB->item(j,i)->setText("");
                        ui->tableWidgetISCB->item(j,i)->setFlags(ui->tableWidgetISCB->item(j,i)->flags()&~Qt::ItemIsEnabled);
                    }
                }
                // row i
                ui->tableWidgetISCB->item(i,0)->setBackground(ISCBTitleTrick);
                for (int j=i+1; j<ui->tableWidgetISCB->columnCount(); j++){
                    if (ui->tableWidgetISCB->item(i,j)->background().color().name() != RedColor){
                        ui->tableWidgetISCB->item(i,j)->setBackground(gnssUnSelected);
                        ui->tableWidgetISCB->item(i,j)->setText("");
                        ui->tableWidgetISCB->item(i,j)->setFlags(ui->tableWidgetISCB->item(j,i)->flags()&~Qt::ItemIsEnabled);
                    }
                }
            }
            break;
        }
    }
}

// Function to get the FILTER options and errors
void gLAB_GUI::getFilterOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString) {
    // Header of the filter section
    *saveString += "\n";
    *saveString += "###################################################\n";
    *saveString += "#     FILTER section\n";
    *saveString += "###################################################\n\n";
    // Selection
    if ( ui->radioButtonSelectionPseudorange->isChecked() == true ) {
        //No printing here when write WriteAllParameters==1 because when  loading a configuration file, this parameter shows a warning that has no effect
        if (mode==1  && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false ) {
            //Pseudorange measurement only is the default in all modes except PPP
            *saveString += "-filter:meas pseudorange\n";
            *runString << "-filter:meas" << "pseudorange";

        }
    } else if (ui->radioButtonSmoothing->isChecked()==true) {
            //Show warnings if cycle-slip detectors are not enabled due to smoothing
            if (ui->checkBoxSF->isChecked()==false && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false && ui->checkBoxIGF->isChecked()==false && ui->checkBoxLLI->isChecked()==false) {
                *warningString += "PREPROCESS/FILTER: Single frequency carrier phase measurement is used for smoothing, but no cycle-slip detectors are enabled.\n";
            } else if (ui->checkBoxSF->isChecked()==false && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false && ui->checkBoxIGF->isChecked()==false) {
                *warningString += "PREPROCESS/FILTER: Single frequency carrier phase measurement is used for smoothing, but only LLI cycle-slip detector is enabled, which is not very reliable.\n";
            }

    } else if ( ui->radioButtonSelectionPseudorangeCarrierPhase->isChecked() == true ) {
        //No printing here when write WriteAllParameters==1 because when  loading a configuration file, this parameter shows a warning that has no effect
        if (mode==0 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true) {
            //Carrierphase measurement is only the default in PPP
            *saveString += "-filter:meas carrierphase\n";
            *runString << "-filter:meas" << "carrierphase";
        }
        //Show warnings if cycle-slip detectors are not enabled
        if ( ui->radioButtonSingleFreq->isChecked() == true ) {
            if (ui->checkBoxSF->isChecked()==false && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false
                    && ui->checkBoxIGF->isChecked()==false && ui->checkBoxLLI->isChecked()==false ) {
                *warningString += "PREPROCESS/FILTER: Carrier phase measurements are used, but no cycle-slip detectors are enabled.\n";
            } else if (ui->checkBoxSF->isChecked()==false && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false && ui->checkBoxIGF->isChecked()==false) {
                *warningString += "PREPROCESS/FILTER: Carrier phase measurements are used, but only LLI cycle-slip detector is enabled, which is not very reliable.\n";
            } else {
                if (ui->checkBoxSF->isChecked()==false) {
                    *warningString += "PREPROCESS/FILTER: Single frequency carrier phase measurements are used, but Phase-Code cycle slip detector is not enabled.\n";
                }
                if (ui->checkBoxMW->isChecked()==true) {
                    *warningString += "PREPROCESS/FILTER: Single frequency carrier phase measurements are used, but Melbourne-Wübbena cycle-slip detector is enabled, which uses dual frequency measurements.\n";
                }
                if (ui->checkBoxLI->isChecked()==true) {
                    *warningString += "PREPROCESS/FILTER: Single frequency carrier phase measurements are used, but Geometry-free cycle-slip detector is enabled, which uses dual frequency measurements.\n";
                }
                if (ui->checkBoxIGF->isChecked()==true) {
                    *warningString += "PREPROCESS/FILTER: Single frequency carrier phase measurements are used, but Iono-Geometry-Free cycle-slip detector is enabled, which uses triple frequency measurements.\n";
                }
            }
        } else if (ui->radioButtonDualFreq->isChecked() == true ) {
            if (ui->checkBoxSF->isChecked()==false && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false && ui->checkBoxIGF->isChecked()==false && ui->checkBoxLLI->isChecked()==false ) {
                *warningString += "PREPROCESS/FILTER: Carrier phase measurements are used, but no cycle-slip detectors are enabled.\n";
            } else if (ui->checkBoxSF->isChecked()==false && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false && ui->checkBoxIGF->isChecked()==false) {
                *warningString += "PREPROCESS/FILTER: Carrier phase measurements are used, but only LLI cycle-slip detector is enabled, which is not very reliable.\n";
            }
        }
    }
    // Ionosphere
    if ( ui->checkBoxUseSigmaIonosphere->isChecked() == true)  {
        *saveString += "-filter:sigmaiono\n";
        *runString << "-filter:sigmaiono";
    }
    // Troposphere
    if ( ui->checkBoxEstimateTroposphere->isChecked() == true ) {
        if ((mode==0 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true) || WriteAllParameters==1) {
            //Estimate troposphere in only enabled by default on PPP
            *saveString += "-filter:trop\n";
            *runString << "-filter:trop";
        }
    } else {
        if ((mode==1  && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false)|| WriteAllParameters==1) {
            //Estimate troposphere in only enabled by default on PPP
            *saveString += "--filter:trop\n";
            *runString << "--filter:trop";
        }
    }
    // Inter-System Clock Bias
    if (ui->groupBoxISCB->isChecked()){
        QString ISCBOption="",ISCBUnit="";
        switch(ui->comboBoxISCBUnit->currentIndex()){
            case 0: if (WriteAllParameters==1) ISCBUnit="m-"; break;
            case 1: ISCBUnit="s-"; break;
            case 2: ISCBUnit="n-"; break;
        }
        //row: Reference constellation, column: Destination constellation
        for (int i=1; i<ui->tableWidgetISCB->rowCount(); i++){
            for (int j=i+1; j<ui->tableWidgetISCB->columnCount(); j++){
                if ( ui->tableWidgetISCB->item(i,j)->background().color().name() != RedColor ){
                    if ( ui->tableWidgetISCB->item(i,j)->text() == "Estimate" ) {
                        if (WriteAllParameters==1) ISCBOption += " " + ISCBGNSSOrder[i-1] + ISCBGNSSOrder[j-1] + "-estimate";
                    } else {
                        ISCBOption += " " + ISCBGNSSOrder[i-1] + ISCBGNSSOrder[j-1] + "-" + ISCBUnit + ui->tableWidgetISCB->item(i,j)->text();
                    }
                }
            }
        }
        if (ISCBOption.size()>0){
            ISCBOption = "-filter:iscb" + ISCBOption;
            *saveString += ISCBOption + "\n";
            *runString << ISCBOption;
        }
    }
    // Receiver kinematics
    if ( ui->radioButtonStatic->isChecked() == true ) {
        if ((mode==0 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true) || WriteAllParameters==1) {
            //Static navigation is only set by default in PPP
            *saveString += "-filter:nav static\n";
            *runString << "-filter:nav" << "static";
        }
    } else if ( ui->radioButtonKinematic->isChecked() == true ) {
        if ((mode==1  && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) || WriteAllParameters==1) {
            //Kinematic navigation is the default in all modes except PPP
            *saveString += "-filter:nav kinematic\n";
            *runString << "-filter:nav" << "kinematic";
        }
    }
    // Backward filtering
    if ( ui->checkBoxBackwardFiltering->isChecked() == true ) {
        //Disabled by default in all modes
        *saveString += "-filter:backward\n";
        *runString << "-filter:backward";
    }
    // Parameters - Coordinates
    if (ui->radioButtonRandomwalkCoordinates->isChecked()){
        *saveString += "-filter:dr:randomwalk\n";
        *runString << "-filter:dr:randomwalk";
    }
    if ( ui->lineEditPhiCoordinates->text() == "" )
        *errorString += "FILTER: Filter Parameters: Coordinates Phi must be >= 0.\n";
    else {
        if (ui->radioButtonStatic->isChecked() == true || ui->radioButtonRandomwalkCoordinates->isChecked()){
            if ( ui->lineEditPhiCoordinates->text().toDouble() != 1. || WriteAllParameters==1) {
                *saveString += "-filter:phi:dr " + ui->lineEditPhiCoordinates->text() + "\n";
                *runString << "-filter:phi:dr" << ui->lineEditPhiCoordinates->text();
            }
        } else {
            if ( ui->lineEditPhiCoordinates->text().toDouble() != 0. || WriteAllParameters==1) {
                *saveString += "-filter:phi:dr " + ui->lineEditPhiCoordinates->text() + "\n";
                *runString << "-filter:phi:dr" << ui->lineEditPhiCoordinates->text();
            }
        }
    }
    if ( ui->lineEditQcoordinates->text() == "" )
        *errorString += "FILTER: Filter Parameters: Coordinates Noise must be >= 0.\n";
    else {
        if ( ui->radioButtonKinematic->isChecked() == true && !ui->radioButtonRandomwalkCoordinates->isChecked() ) {
            if ( ui->lineEditQcoordinates->text().toDouble() != 1e8 || WriteAllParameters==1) {
                *saveString += "-filter:q:dr " + ui->lineEditQcoordinates->text() + "\n";
                *runString << "-filter:q:dr" << ui->lineEditQcoordinates->text();
            }
        }
        else if ( ui->radioButtonStatic->isChecked() == true && !ui->radioButtonRandomwalkCoordinates->isChecked() ){
            if ( ui->lineEditQcoordinates->text().toDouble() != 0. || WriteAllParameters==1) {
                *saveString += "-filter:q:dr " + ui->lineEditQcoordinates->text() + "\n";
                *runString << "-filter:q:dr" << ui->lineEditQcoordinates->text();
            }
        } else if (ui->radioButtonRandomwalkCoordinates->isChecked()){
            if ( ui->lineEditQcoordinates->text().toDouble() != 70 || WriteAllParameters==1) {
                *saveString += "-filter:q:dr " + ui->lineEditQcoordinates->text() + "\n";
                *runString << "-filter:q:dr" << ui->lineEditQcoordinates->text();
            }
        }
    }
    if ( ui->lineEditPoCoordinates->text() == "" )
        *errorString += "FILTER: Filter Parameters: Coordinates Po must be >= 0.\n";
    else {
        if ( ui->lineEditPoCoordinates->text().toDouble() != 1e8 || WriteAllParameters==1) {
            *saveString += "-filter:p0:dr " + ui->lineEditPoCoordinates->text() + "\n";
            *runString << "-filter:p0:dr" << ui->lineEditPoCoordinates->text();
        }
    }
    // Parameters - Clock
    if (ui->radioButtonRandomwalkClock->isChecked()){
        *saveString += "-filter:clk:randomwalk\n";
        *runString << "-filter:clk:randomwalk";
    }
    if ( ui->lineEditPhiClock->text() == "" )
        *errorString += "FILTER: Filter Parameters: Receiver Clock Phi must be >= 0.\n";
    else {
        if (ui->radioButtonRandomwalkClock->isChecked()){
            if ( ui->lineEditPhiClock->text().toDouble() != 1. || WriteAllParameters==1 ) {
                *saveString += "-filter:phi:clk " + ui->lineEditPhiClock->text() + "\n";
                *runString << "-filter:phi:clk" << ui->lineEditPhiClock->text();
            }
        } else {
            if ( ui->lineEditPhiClock->text().toDouble() != 0. || WriteAllParameters==1 ) {
                *saveString += "-filter:phi:clk " + ui->lineEditPhiClock->text() + "\n";
                *runString << "-filter:phi:clk" << ui->lineEditPhiClock->text();
            }
        }
    }
    if ( ui->lineEditQclock->text() == "" )
        *errorString += "FILTER: Filter Parameters: Receiver Clock Noise must be >= 0.\n";
    else {
        if (!ui->radioButtonRandomwalkClock->isChecked() && ui->comboBoxQClockUnitNormal->currentIndex()==0){ //normal m²/d
            if ( ui->lineEditQclock->text().toDouble() != 9e10 || WriteAllParameters==1 ) {
                *saveString += "-filter:q:clk " + ui->lineEditQclock->text() + "\n";
                *runString << "-filter:q:clk" << ui->lineEditQclock->text();
            }
        } else if (!ui->radioButtonRandomwalkClock->isChecked() && ui->comboBoxQClockUnitNormal->currentIndex()==1){ //normal ns²/d
            if ( ui->lineEditQclock->text().toDouble() != 9. || WriteAllParameters==1 ) {
                *saveString += "-filter:q:clk:ns " + ui->lineEditQclock->text() + "\n";
                *runString << "-filter:q:clk:ns" << ui->lineEditQclock->text();
            }
        } else if (ui->radioButtonRandomwalkClock->isChecked() && ui->comboBoxQClockUnitRandom->currentIndex()==0){ //randomwalk m²/d
            if ( ui->lineEditQclock->text().toDouble() != 1e12 || WriteAllParameters==1 ) {
                *saveString += "-filter:q:clk " + ui->lineEditQclock->text() + "\n";
                *runString << "-filter:q:clk" << ui->lineEditQclock->text();
            }
        } else if (ui->radioButtonRandomwalkClock->isChecked() && ui->comboBoxQClockUnitRandom->currentIndex()==1){ //randomwalk ns²/d
            if ( ui->lineEditQclock->text().toDouble() != 100. || WriteAllParameters==1 ) {
                *saveString += "-filter:q:clk:ns " + ui->lineEditQclock->text() + "\n";
                *runString << "-filter:q:clk:ns" << ui->lineEditQclock->text();
            }
        }
    }
    if ( ui->lineEditPoClock->text() == "" )
        *errorString += "FILTER: Filter Parameters: Receiver Clock Po must be >= 0.\n";
    else {
        if (ui->comboBoxPoClockUnit->currentIndex()==0){ //normal m²/d
            if ( ui->lineEditPoClock->text().toDouble() != 9e10 || WriteAllParameters==1 ) {
                *saveString += "-filter:p0:clk " + ui->lineEditPoClock->text() + "\n";
                *runString << "-filter:p0:clk" << ui->lineEditPoClock->text();
            }
        } else if (ui->comboBoxPoClockUnit->currentIndex()==1){ //normal ns²/d
            if ( ui->lineEditPoClock->text().toDouble() != 9. || WriteAllParameters==1 ) {
                *saveString += "-filter:p0:clk:ns " + ui->lineEditPoClock->text() + "\n";
                *runString << "-filter:p0:clk:ns" << ui->lineEditPoClock->text();
            }
        }
    }
    // Parameters - ISCB
    if (ui->radioButtonRandomwalkISCB->isChecked()){
        *saveString += "-filter:iscb:randomwalk\n";
        *runString << "-filter:iscb:randomwalk";
    }
    if ( ui->lineEditPhiISCB->text() == "" )
        *errorString += "FILTER: Filter Parameters: Receiver Inter-Constellation Clock Bias Phi must be >= 0.\n";
    else {
        if ( mode==1 || ui->radioButtonRandomwalkISCB->isChecked() ){
            if ( ui->lineEditPhiISCB->text().toDouble() != 1. || WriteAllParameters==1 ) {
                *saveString += "-filter:phi:iscb " + ui->lineEditPhiISCB->text() + "\n";
                *runString << "-filter:phi:iscb" << ui->lineEditPhiISCB->text();
            }
        } else {
            if ( ui->lineEditPhiISCB->text().toDouble() != 0. || WriteAllParameters==1 ) {
                *saveString += "-filter:phi:iscb " + ui->lineEditPhiISCB->text() + "\n";
                *runString << "-filter:phi:iscb" << ui->lineEditPhiISCB->text();
            }
        }
    }
    if ( ui->lineEditQISCB->text() == "" )
        *errorString += "FILTER: Filter Parameters: Receiver ISCB Noise must be >= 0.\n";
    else {
        if (!ui->radioButtonRandomwalkISCB->isChecked() && ui->comboBoxQISCBUnitNormal->currentIndex()==0){ //normal m²/d
            if ( (ui->lineEditQISCB->text().toDouble() != 9e10 && mode!=1) || (ui->lineEditQISCB->text().toDouble() != 0. && mode==1) || WriteAllParameters==1 ) {
                *saveString += "-filter:q:iscb " + ui->lineEditQISCB->text() + "\n";
                *runString << "-filter:q:iscb" << ui->lineEditQISCB->text();
            }
        } else if (!ui->radioButtonRandomwalkISCB->isChecked() && ui->comboBoxQISCBUnitNormal->currentIndex()==1){ //normal ns²/d
            if ( (ui->lineEditQISCB->text().toDouble() != 9. && mode!=1) || (ui->lineEditQISCB->text().toDouble() != 0. && mode==1) || WriteAllParameters==1 ) {
                *saveString += "-filter:q:iscb:ns " + ui->lineEditQISCB->text() + "\n";
                *runString << "-filter:q:iscb:ns" << ui->lineEditQISCB->text();
            }
        } else if (ui->radioButtonRandomwalkISCB->isChecked() && ui->comboBoxQISCBUnitRandom->currentIndex()==0){ //randomwalk m²/d
            if ( ui->lineEditQISCB->text().toDouble() != 1e12 || WriteAllParameters==1 ) {
                *saveString += "-filter:q:iscb " + ui->lineEditQISCB->text() + "\n";
                *runString << "-filter:q:iscb" << ui->lineEditQISCB->text();
            }
        } else if (ui->radioButtonRandomwalkISCB->isChecked() && ui->comboBoxQISCBUnitRandom->currentIndex()==1){ //randomwalk ns²/d
            if ( ui->lineEditQISCB->text().toDouble() != 100. || WriteAllParameters==1 ) {
                *saveString += "-filter:q:iscb:ns " + ui->lineEditQISCB->text() + "\n";
                *runString << "-filter:q:iscb:ns" << ui->lineEditQISCB->text();
            }
        }
    }
    if ( ui->lineEditPoISCB->text() == "" )
        *errorString += "FILTER: Filter Parameters: Receiver ISCB Po must be >= 0.\n";
    else {
        if (ui->comboBoxPoISCBUnit->currentIndex()==0){ //normal m²/d
            if ( ui->lineEditPoISCB->text().toDouble() != 9e10 || WriteAllParameters==1 ) {
                *saveString += "-filter:p0:iscb " + ui->lineEditPoISCB->text() + "\n";
                *runString << "-filter:p0:iscb" << ui->lineEditPoISCB->text();
            }
        } else if (ui->comboBoxPoISCBUnit->currentIndex()==1){ //normal ns²/d
            if ( ui->lineEditPoISCB->text().toDouble() != 9. || WriteAllParameters==1 ) {
                *saveString += "-filter:p0:iscb:ns " + ui->lineEditPoISCB->text() + "\n";
                *runString << "-filter:p0:iscb:ns" << ui->lineEditPoISCB->text();
            }
        }
    }
    // Parameters - Troposphere
    if ( ui->checkBoxEstimateTroposphere->isChecked() == true ) {
        if ( ui->lineEditPhiTropo->text() == "" )
            *errorString += "FILTER: Filter Parameters: Troposphere Phi must be >= 0.\n";
        else {
            if ( ui->lineEditPhiTropo->text().toDouble() != 1. || WriteAllParameters==1 ) {
                *saveString += "-filter:phi:trop " + ui->lineEditPhiTropo->text() + "\n";
                *runString << "-filter:phi:trop" << ui->lineEditPhiTropo->text();
            }
        }
        if ( ui->lineEditQtropo->text() == "" )
            *errorString += "FILTER: Filter Parameters: Troposphere Noise must be >= 0.\n";
        else {
            if ( ui->lineEditQtropo->text().toDouble() != 1e-4 || WriteAllParameters==1 ) {
                *saveString += "-filter:q:trop " + ui->lineEditQtropo->text() + "\n";
                *runString << "-filter:q:trop" << ui->lineEditQtropo->text();
            }
        }
        if ( ui->lineEditPoTropo->text() == "" )
            *errorString += "FILTER: Filter Parameters: Troposphere Po must be >= 0.\n";
        else {
            if ( ui->lineEditPoTropo->text().toDouble() != 0.25 || WriteAllParameters==1 ) {
                *saveString += "-filter:p0:trop " + ui->lineEditPoTropo->text() + "\n";
                *runString << "-filter:p0:trop" << ui->lineEditPoTropo->text();
            }
        }
    }
    // Parameters - Phase Ambiguities
    if ( ui->radioButtonSelectionPseudorangeCarrierPhase->isChecked() == true ) {
        if ( ui->lineEditPhiPhaseAmbiguities->text() == "" )
            *errorString += "FILTER: Filter Parameters: Phase Ambiguities Phi must be >= 0.\n";
        else {
            if ( ui->lineEditPhiPhaseAmbiguities->text().toDouble() != 1. || WriteAllParameters==1 ) {
                *saveString += "-filter:phi:amb " + ui->lineEditPhiPhaseAmbiguities->text() + "\n";
                *runString << "-filter:phi:amb" << ui->lineEditPhiPhaseAmbiguities->text();
            }
        }
        if ( ui->lineEditQphaseAmbiguities->text() == "" )
            *errorString += "FILTER: Filter Parameters: Phase Ambiguities Noise must be >= 0.\n";
        else {
            if ( ui->lineEditQphaseAmbiguities->text().toDouble() != 0. || WriteAllParameters==1 ) {
                *saveString += "-filter:q:amb " + ui->lineEditQphaseAmbiguities->text() + "\n";
                *runString << "-filter:q:amb" << ui->lineEditQphaseAmbiguities->text();
            }
        }
        if ( ui->lineEditPoPhaseAmbiguities->text() == "" )
            *errorString += "FILTER: Filter Parameters: Phase Ambiguities Po must be >= 0.\n";
        else {
            if ( ui->lineEditPoPhaseAmbiguities->text().toDouble() != 400. || WriteAllParameters==1 ) {
                *saveString += "-filter:p0:amb " + ui->lineEditPoPhaseAmbiguities->text() + "\n";
                *runString << "-filter:p0:amb" << ui->lineEditPoPhaseAmbiguities->text();
            }
        }
    }

    // frequency and measurement order
    if (ui->checkBoxSetFreqMeasOrderGNSS->isChecked()) {
        FreqMeasGNSS->getgLABOptions(errorString,warningString,saveString,runString);
    }

    // measurement selection for SPP and PPP mode
    if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
        //-filter:select commands
        QString autoGNSS="";
        QString MeasType[2]={"Code","Phase"};
        QString satString[MAX_GNSS][6]={{""}};
        int     numSatString[MAX_GNSS]={0};
        int     endMeasTypeLoopPos=MEASANDPHASENUMSLOTS;

        if (ui->radioButtonSelectionGraphic->isChecked()) {
            //When Graphic combination is selected, data is saved in Code position to reuse code
            endMeasTypeLoopPos=PHASEARRAYPOS;
        }

        //Check navigation message types selected according to frequencies in the filter (only for frequencies 1, 5, 7, as INAV/FNAV usge varies)
        //It is only for the case all measurements are from the same frequency or frequency combination
        if (CheckBoxGNSS[Galileo]->isChecked() && ui->radioButtonOrbitBrdc->isChecked()) {
            int numF1signals=0, numF5signals=0, numF7signals=0, numF1F5signals=0, numF1F7signals=0, numSignals=0;
            for (int icomb=0; icomb<MAXMEASTOFILTER; icomb++) {
                for (int iCP=0; iCP<endMeasTypeLoopPos; iCP++) {
                    if ( GNSSMeasAll[Galileo][icomb][iCP].size()>0 ) {
                        numSignals++;
                        if (GNSSMeasAll[Galileo][icomb][iCP].toUpper().contains(QRegularExpression("[IPL][FC]15")) ) {
                            numF1F5signals++;
                        } else if (GNSSMeasAll[Galileo][icomb][iCP].toUpper().contains(QRegularExpression("[IPL][FC]17")) ) {
                            numF1F7signals++;
                        } else if (GNSSMeasAll[Galileo][icomb][iCP].toUpper().contains(QRegularExpression("-1$")) || GNSSMeasAll[Galileo][icomb][iCP].toUpper().contains(QRegularExpression("-[CL]1[A-Z]$")) || GNSSMeasAll[Galileo][icomb][iCP].toUpper().contains(QRegularExpression("[0-9]-G1"))) {
                            numF1signals++;
                        } else if (GNSSMeasAll[Galileo][icomb][iCP].toUpper().contains(QRegularExpression("-5$")) || GNSSMeasAll[Galileo][icomb][iCP].toUpper().contains(QRegularExpression("-[CL]5[A-Z]$")) || GNSSMeasAll[Galileo][icomb][iCP].toUpper().contains(QRegularExpression("[0-9]-G5"))) {
                            numF5signals++;
                        } else if (GNSSMeasAll[Galileo][icomb][iCP].toUpper().contains(QRegularExpression("-7$")) || GNSSMeasAll[Galileo][icomb][iCP].toUpper().contains(QRegularExpression("-[CL]7[A-Z]$")) || GNSSMeasAll[Galileo][icomb][iCP].toUpper().contains(QRegularExpression("[0-9]-G7"))) {
                            numF7signals++;
                        }
                    }
                }
            }
            if (numSignals>0) {
                if (numF1signals==numSignals || numF7signals==numSignals || (numF1signals+numF7signals)==numSignals || numF1F7signals==numSignals ) {
                    QString FreqText="",Freq2Text="";
                    if (numF1signals==numSignals) {
                        FreqText="frequency 1";
                        Freq2Text="this frequency";
                    } else if (numF7signals==numSignals) {
                        FreqText="frequency 7";
                        Freq2Text="this frequency";
                    } else if ((numF1signals+numF7signals)==numSignals) {
                        FreqText="frequencies 1 and 7";
                        Freq2Text="these frequencies";
                    } else if (numF1F7signals==numSignals) {
                        FreqText="frequencies 17";
                        Freq2Text="these frequencies";
                    }
                    if (ui->tableWidgetNavMessageTypeGalileo->item(0,0)->text()=="FNAV") {
                        *warningString += "MODELLING: Galileo filter measurements are from " + FreqText + ", but first navigation message type in list is FNAV. It is recommended to use INAV first, as Galileo ICD indicates to use INAV for " + Freq2Text + ".\n";
                    }
                } else if (numF5signals==numSignals || numF1F5signals==numSignals ) {
                    QString FreqText="",Freq2Text="";
                    if (numF5signals==numSignals) {
                        FreqText="frequency 5";
                        Freq2Text="this frequency";
                    } else if (numF1F5signals==numSignals) {
                        FreqText="frequencies 15";
                        Freq2Text="these frequencies";
                    }
                    if (ui->tableWidgetNavMessageTypeGalileo->item(0,0)->text()!="FNAV") {
                        *warningString += "MODELLING: Galileo filter measurements are from " + FreqText + ", but first navigation message type in list is " + ui->tableWidgetNavMessageTypeGalileo->item(0,0)->text() + ". It is recommended to use FNAV first, as Galileo ICD indicates to use FNAV for " + Freq2Text + ".\n";
                    }
                }
            }
        }

        if (MeasOK>0) {

            if (ui->radioButtonSelectionGraphic->isChecked()) {
                *saveString += "-filter:combtype graphic\n";
                *runString << "-filter:combtype" << "graphic";
            }

            *saveString += "-filter:select";
            *runString << "-filter:select";
            for (int isys=0;isys<MAX_GNSS;isys++) { //constellation
                QString argString[3][2]={{""}};
                int numAutoTotalGNSS=0;
                int numAutoCodePhaseGNSS[2]={0}; //0 -> code  1 -> Phase
                int numFrameHidden=0;
                if (!CheckBoxGNSS[isys]->isChecked()) continue;
                for (int icomb=0; icomb<MAXMEASTOFILTER; icomb++) { //combination
                    for (int iCP=0; iCP<endMeasTypeLoopPos; iCP++) {
                        if ( GNSSMeasAll[isys][icomb][iCP].size()>0 ) {
                            argString[icomb][iCP] = GNSSMeasAll[isys][icomb][iCP];
                        } else {
                            numAutoTotalGNSS++;
                            numAutoCodePhaseGNSS[iCP]++;
                        }
                    }
                    if (FrameGNSSMeasComb[isys][icomb]->isHidden()) numFrameHidden++;
                }

                //Check for repeated measurements
                for (int iCP=0; iCP<endMeasTypeLoopPos; iCP++) {
                    if (GNSSMeasAll[isys][SECONDMEASARRAYPOS][iCP].size()>0 ) {
                        if (QString::compare(GNSSMeasAll[isys][SECONDMEASARRAYPOS][iCP], GNSSMeasAll[isys][FIRSTMEASARRAYPOS][iCP], Qt::CaseInsensitive)==0) {
                            *warningString += "FILTER: " + MeasType[iCP] + " measurements in positions 1 and 2 for constellation " + GNSSName[isys] + " are repeated. They will be used only once.\n";
                            argString[SECONDMEASARRAYPOS][iCP]="";

                        }
                        if (QString::compare(GNSSMeasAll[isys][SECONDMEASARRAYPOS][iCP], GNSSMeasAll[isys][THIRDMEASARRAYPOS][iCP], Qt::CaseInsensitive)==0) {
                            *warningString += "FILTER: " + MeasType[iCP] + " measurements in positions 2 and 3 for constellation " + GNSSName[isys] + " are repeated. They will be used only once.\n";
                            argString[SECONDMEASARRAYPOS][iCP]="";
                        }
                    }
                    if (GNSSMeasAll[isys][THIRDMEASARRAYPOS][iCP].size()>0 ) {
                        if (QString::compare(GNSSMeasAll[isys][2][iCP], GNSSMeasAll[isys][FIRSTMEASARRAYPOS][iCP], Qt::CaseInsensitive)==0) {
                            *warningString += "FILTER: " + MeasType[iCP] + " measurements in positions 1 and 3 for constellation " + GNSSName[isys] + " are repeated. They will be used only once.\n";
                            argString[THIRDMEASARRAYPOS][iCP]="";

                        }
                        if (QString::compare(GNSSMeasAll[isys][2][iCP], GNSSMeasAll[isys][SECONDMEASARRAYPOS][iCP], Qt::CaseInsensitive)==0) {
                            *warningString += "FILTER: " + MeasType[iCP] + " measurements in positions 2 and 3 for constellation " + GNSSName[isys] + " are repeated. They will be used only once.\n";
                            argString[THIRDMEASARRAYPOS][iCP]="";
                        }
                    }
                }
                for (int icomb=0; icomb<MAXMEASTOFILTER; icomb++) { //combination
                    for (int iCP=0; iCP<endMeasTypeLoopPos; iCP++) {

                        if (argString[icomb][iCP]!="") {
                            satString[isys][numSatString[isys]]=argString[icomb][iCP];
                            numSatString[isys]++;
                        } else {
                            GNSSMeasAll[isys][icomb][iCP]="";
                        }
                    }
                }



                if (ui->radioButtonSelectionGraphic->isChecked()) {
                        if (numAutoTotalGNSS==3 ) {
                            //All Graphic combinatios are in auto mode
                            autoGNSS += indentifierGNSS[isys];
                            if (numFrameHidden<2 ) {
                                 *warningString += "FILTER: " + GNSSName[isys] + " constellation has multiple 'Auto' frequencies for graphic combinations, but only one will be applied in the filter. Set only one 'Auto' graphic combination.\n";
                            }
                        } else {
                            if (numAutoCodePhaseGNSS[0]<3 && numFrameHidden!=numAutoCodePhaseGNSS[0]) {
                                *warningString += "FILTER: " + GNSSName[isys] + " constellation has manually set and 'Auto' frequencies for graphic combinations. When a frequency is manually selected, the other frequencies in 'Auto' mode will be ignored. Remove the 'Auto' graphic combinations or set all frequencies.\n";
                            }
                        }
                } else {
                    if (numAutoTotalGNSS==6) {
                        //All codes and phases are in auto mode
                        autoGNSS += indentifierGNSS[isys];
                        if (ui->radioButtonSelectionPseudorange->isChecked()==true) {
                            if (numAutoCodePhaseGNSS[0]==3 && numFrameHidden<2 ) {
                                 *warningString += "FILTER: " + GNSSName[isys] + " constellation has multiple 'Auto' frequencies for pseudoranges, but only one will be applied in the filter. Set only one 'Auto' measurement.\n";
                            }
                        } else if (ui->radioButtonSelectionPseudorangeCarrierPhase->isChecked()==true) {
                            if (numAutoCodePhaseGNSS[0]==3 && numFrameHidden<2 ) {
                                 *warningString += "FILTER: " + GNSSName[isys] + " constellation has multiple 'Auto' frequencies for pseudoranges and carrier phases, but only one pseudorange and carrier phase will be applied in the filter. Set only one 'Auto' measurement per meas type.\n";
                            }
                        }
                    } else if (ui->radioButtonSelectionPseudorange->isChecked()==true) {
                        if (numAutoCodePhaseGNSS[0]<3 && numFrameHidden!=numAutoCodePhaseGNSS[0]) {
                            *warningString += "FILTER: " + GNSSName[isys] + " constellation has manually set and 'Auto' frequencies for pseudoranges. When a frequency is manually selected, the other frequencies in 'Auto' mode will be ignored. Remove the 'Auto' measurements or set all frequencies.\n";
                        }
                    } else if (ui->radioButtonSelectionPseudorangeCarrierPhase->isChecked()==true) {
                        if ( (numAutoCodePhaseGNSS[0]<3 && numFrameHidden!=numAutoCodePhaseGNSS[0]) || (numAutoCodePhaseGNSS[1]<3 && numFrameHidden!=numAutoCodePhaseGNSS[1]) || numAutoTotalGNSS==5 ) {
                            *warningString += "FILTER: " + GNSSName[isys] + " constellation has manually set and 'Auto' frequencies for pseudoranges and carrier phases. When a frequency is manually selected, the other frequencies in 'Auto' mode will be ignored (for both pseudoranges and carrier phases). Remove the 'Auto' measurements or set all frequencies.\n";
                        }
                    }
                }
            }
            if (autoGNSS!="") {
                *saveString += " " + autoGNSS + "0-auto";
                *runString << autoGNSS + "0-auto";
            }
            //Loop to join same measurements from different constellations
            for (int isys=0;isys<MAX_GNSS;isys++) {
                for (int istr=0; istr<numSatString[isys]; istr++) {
                    for (int isys2=0;isys2<MAX_GNSS;isys2++) {
                        for (int istr2=0; istr2<numSatString[isys2]; istr2++) {
                            if (isys==isys2 && istr==istr2) continue;
                            if (satString[isys][istr]=="" || satString[isys2][istr2]=="") continue;
                            int pos1,pos2;
                            pos1=satString[isys][istr].indexOf("-")+1;
                            pos2=satString[isys2][istr2].indexOf("-")+1;

                            if (QString::compare(satString[isys][istr].mid(pos1),satString[isys2][istr2].mid(pos2))==0 ) {
                                satString[isys][istr].insert(pos1-2,indentifierGNSS[isys2]);
                                satString[isys2][istr2]="";
                            }
                        }
                    }
                }
            }
            //Loop again to join 'code' and 'phase' common meas to 'codephase'
            for (int isys=0;isys<MAX_GNSS;isys++) {
                for (int istr=0; istr<numSatString[isys]; istr++) {
                    for (int isys2=0;isys2<MAX_GNSS;isys2++) {
                        for (int istr2=0; istr2<numSatString[isys2]; istr2++) {
                            if (isys==isys2 && istr==istr2) continue;
                            if (satString[isys][istr]=="" || satString[isys2][istr2]=="") continue;
                            int pos1,pos11,pos2,pos22;
                            pos1=satString[isys][istr].indexOf("-")-1;
                            pos11=satString[isys][istr].indexOf("-",pos1+2)+1;
                            pos2=satString[isys2][istr2].indexOf("-")-1;
                            pos22=satString[isys2][istr2].indexOf("-",pos2+2)+1;
                            if (( satString[isys][istr].contains("code",Qt::CaseInsensitive)==0 && satString[isys2][istr2].contains("phase",Qt::CaseInsensitive)==0 ) || ( satString[isys][istr].contains("phase",Qt::CaseInsensitive)==0 && satString[isys2][istr2].contains("code",Qt::CaseInsensitive)==0 ) ) {
                                if (QString::compare(satString[isys][istr].left(pos1),satString[isys2][istr2].left(pos2))==0 &&
                                      QString::compare(satString[isys][istr].mid(pos11),satString[isys2][istr2].mid(pos22))==0  ) {
                                    satString[isys][istr].insert(pos11-1,"Phase");
                                    satString[isys2][istr2]="";
                                }
                            }
                        }
                    }
                }
            }

            for (int isys=0;isys<MAX_GNSS;isys++) {
                for (int istr=0; istr<numSatString[isys]; istr++) {
                    if (satString[isys][istr]!="") {
                        *saveString += " " + satString[isys][istr];
                        QStringList tmpString = satString[isys][istr].split(QRegularExpression("\\s+"));
                        for(int k=0;k<tmpString.size();k++) {
                            *runString << tmpString[k];
                        }
                    }
                }
            }
            *saveString += "\n";

            //Add noise mode options

            //Loop to join weights by weights type
            QString satWeightString[5][MAX_GNSS][6]={{{""}}};
            QString satWeightMeasString[5][MAX_GNSS][6]={{{""}}};
            int     numSatWeightString[5][MAX_GNSS]={{0}};
            for (int isys=0;isys<MAX_GNSS;isys++) {
                if (!CheckBoxGNSS[isys]->isChecked()) continue;
                for (int icomb=0; icomb<3; icomb++) {
                    for (int iCP=0; iCP<2; iCP++) {
                        if ( GNSSMeasAll[isys][icomb][iCP].size()>0 && GNSSNoiseAll[isys][icomb][iCP].size()>0 ) {
                            for( int iweight=0;iweight<5;iweight++) {
                                if (QString::compare(GNSSNoiseModeAll[isys][icomb][iCP],GNSSNoiseMode[iweight])==0) {
                                    satWeightString[iweight][isys][numSatWeightString[iweight][isys]]=GNSSNoiseAll[isys][icomb][iCP];
                                    satWeightMeasString[iweight][isys][numSatWeightString[iweight][isys]]=GNSSMeasAll[isys][icomb][iCP];
                                    numSatWeightString[iweight][isys]++;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            //Merge different weight types by constellation
            for( int iweight=0;iweight<5;iweight++) {
                //Loop to merge
                for (int isys=0;isys<MAX_GNSS;isys++) {
                    for (int istr=0; istr<numSatWeightString[iweight][isys]; istr++) {
                        for (int isys2=0;isys2<MAX_GNSS;isys2++) {
                            if (isys==isys2) continue;
                            for (int istr2=0; istr2<numSatWeightString[iweight][isys2]; istr2++) {
                                if (satWeightMeasString[iweight][isys][istr]=="" || satWeightMeasString[iweight][isys2][istr2]=="") continue;
                                int pos1,pos2;
                                pos1=satWeightMeasString[iweight][isys][istr].indexOf("-")+1;
                                pos2=satWeightMeasString[iweight][isys2][istr2].indexOf("-")+1;

                                if (QString::compare(satWeightMeasString[iweight][isys][istr].mid(pos1),satWeightMeasString[iweight][isys2][istr2].mid(pos2))==0 && QString::compare(satWeightString[iweight][isys][istr],satWeightString[iweight][isys2][istr2])==0 ) {
                                    satWeightMeasString[iweight][isys][istr].insert(pos1-2,indentifierGNSS[isys2]);
                                    satWeightMeasString[iweight][isys2][istr2]="";
                                    satWeightString[iweight][isys2][istr2]="";
                                }
                            }
                        }
                    }
                }
                //Loop again to join 'code' and 'phase' common meas to 'codephase'
                for (int isys=0;isys<MAX_GNSS;isys++) {
                    for (int istr=0; istr<numSatWeightString[iweight][isys]; istr++) {
                        for (int isys2=0;isys2<MAX_GNSS;isys2++) {
                            for (int istr2=0; istr2<numSatWeightString[iweight][isys2]; istr2++) {
                                if (isys==isys2 && istr==istr2) continue;
                                if (satWeightMeasString[iweight][isys][istr]=="" || satWeightMeasString[iweight][isys2][istr2]=="") continue;
                                int pos1,pos11,pos2,pos22;
                                pos1=satWeightMeasString[iweight][isys][istr].indexOf("-")-1;
                                pos11=satWeightMeasString[iweight][isys][istr].indexOf("-",pos1+2)+1;
                                pos2=satWeightMeasString[iweight][isys2][istr2].indexOf("-")-1;
                                pos22=satWeightMeasString[iweight][isys2][istr2].indexOf("-",pos2+2)+1;
                                if ( ( ( satWeightMeasString[iweight][isys][istr].contains("code",Qt::CaseInsensitive)==0 && satWeightMeasString[iweight][isys2][istr2].contains("phase",Qt::CaseInsensitive)==0 )
                                        || ( satWeightMeasString[iweight][isys][istr].contains("phase",Qt::CaseInsensitive)==0 && satWeightMeasString[iweight][isys2][istr2].contains("code",Qt::CaseInsensitive)==0 ) )
                                     && QString::compare(satWeightString[iweight][isys][istr],satWeightString[iweight][isys2][istr2])==0 ) {
                                    if (QString::compare(satWeightMeasString[iweight][isys][istr].left(pos1),satWeightMeasString[iweight][isys2][istr2].left(pos2))==0 &&
                                          QString::compare(satWeightMeasString[iweight][isys][istr].mid(pos11),satWeightMeasString[iweight][isys2][istr2].mid(pos22))==0  ) {
                                        satWeightMeasString[iweight][isys][istr].insert(pos11-1,"Phase");
                                        satWeightMeasString[iweight][isys2][istr2]="";
                                        satWeightString[iweight][isys2][istr2]="";
                                    }
                                }
                            }
                        }
                    }
                }
                //Loop for creating the weight parameter list
                int firstweightTypeProvided=0;
                for (int isys=0;isys<MAX_GNSS;isys++) {
                    for (int istr=0; istr<numSatWeightString[iweight][isys]; istr++) {
                        if (satWeightString[iweight][isys][istr]!="") {
                            if (firstweightTypeProvided==0) {
                                *saveString += GNSSNoiseMode[iweight];
                                *runString << GNSSNoiseMode[iweight];
                                firstweightTypeProvided=1;
                            }
                            *saveString += " " + satWeightMeasString[iweight][isys][istr] + " " + satWeightString[iweight][isys][istr];
                            *runString << satWeightMeasString[iweight][isys][istr];
                            QStringList tmpString = satWeightString[iweight][isys][istr].split(QRegularExpression("\\s+"));
                            for(int k=0;k<tmpString.size();k++) {
                                *runString << tmpString[k];
                            }
                        }
                    }
                }
                if (firstweightTypeProvided==1) {
                    *saveString += "\n";
                }
            }

        } else {
            for (int isys=0;isys<MAX_GNSS;isys++) {
                int numFrameHidden=0;
                for (int icomb=0; icomb<3; icomb++) {
                    if (FrameGNSSMeasComb[isys][icomb]->isHidden()) numFrameHidden++;
                }
                if (numFrameHidden!=2) {
                    if (ui->radioButtonSelectionPseudorange->isChecked()==true) {
                        *warningString += "FILTER: " + GNSSName[isys] + " constellation has multiple 'Auto' frequencies for pseudoranges, but only one will be applied in the filter. Set only one 'Auto' measurement.\n";
                    } else if (ui->radioButtonSelectionPseudorangeCarrierPhase->isChecked()==true) {
                        *warningString += "FILTER: " + GNSSName[isys] + " constellation has multiple 'Auto' frequencies for pseudoranges and carrier phases, but only one pseudorange and carrier phase will be applied in the filter. Set only one 'Auto' measurement per meas type.\n";
                    } else if (ui->radioButtonSelectionGraphic->isChecked()) {
                        *warningString += "FILTER: " + GNSSName[isys] + " constellation has multiple 'Auto' frequencies for graphic combinations, but only one will be applied in the filter. Set only one 'Auto' graphic combination.\n";
                    }
                }
            }
            if (ui->radioButtonSelectionGraphic->isChecked()) {
                *saveString += "-filter:combtype graphic";
                *runString << "-filter:combtype" << "graphic";
            } else {
                if (ui->radioButtonOrbitBrdc->isChecked()==true) {
                    if (ui->radioButtonDualFreq->isChecked()==true) {
                        *saveString += "-filter:combtype dualfreq\n";
                        *runString << "-filter:combtype" << "dualfreq";
                    } else if (WriteAllParameters==1) {
                        *saveString += "-filter:combtype auto\n";
                        *runString << "-filter:combtype" << "auto";
                    }
                } else {
                    if (ui->radioButtonSingleFreq->isChecked()==true) {
                        *saveString += "-filter:combtype singlefreq\n";
                        *runString << "-filter:combtype" << "singlefreq";
                    } else if (WriteAllParameters==1) {
                        *saveString += "-filter:combtype auto\n";
                        *runString << "-filter:combtype" << "auto";
                    }
                }
            }
        }
    }
    else if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==true && 0){ //measurement selection for DGNSS mode (forbidden in the current version)
        //-filter:select commands
        if (MeasOK>0){
            *saveString += "-filter:select";
            *runString << "-filter:select";
            for (int isys=0;isys<MAX_GNSS;isys++) { //constellation
                if (!CheckBoxGNSS[isys]->isChecked()) continue;
                for (int icomb=0; icomb<3; icomb++) { //combination
                    if ( GNSSMeasAll[isys][icomb][0].size()>0 ) {
                        *saveString += " "+GNSSMeasAll[isys][icomb][0];
                        QStringList tmpString = GNSSMeasAll[isys][icomb][0].split(QRegularExpression("\\s+"));
                        for(int k=0;k<tmpString.size();k++) {
                            *runString << tmpString[k];
                        }
                    }
                }
            }
            *saveString += "\n";
        }
    }
    else if (ui->groupBoxSbas->isChecked()==true && ui->groupBoxReferenceStation->isChecked()==false && 0){ //measurement selection for SBAS mode (forbidden in the current version)
        //-filter:select commands
        if (MeasOK>0){
            *saveString += "-filter:select";
            *runString << "-filter:select";
            for (int isys=0;isys<MAX_GNSS;isys++) { //constellation
                if (!CheckBoxGNSS[isys]->isChecked()) continue;
                for (int icomb=0; icomb<3; icomb++) { //combination
                    if ( GNSSMeasAll[isys][icomb][0].size()>0 ) {
                        *saveString += " "+GNSSMeasAll[isys][icomb][0];
                        QStringList tmpString = GNSSMeasAll[isys][icomb][0].split(QRegularExpression("\\s+"));
                        for(int k=0;k<tmpString.size();k++) {
                            *runString << tmpString[k];
                        }
                    }
                }
            }
            *saveString += "\n";
        }
    }

    //Reference Constellation Clock
    if (ui->groupBoxSbas->isChecked()==false){
        QString userRefGNSSClockOrder[MAX_GNSS]={""},refGNSSClockCmd;
        //get user-defined order
        for (int i=0;i<ui->tableWidgetRefGNSSClock->columnCount();i++){ //BORRAR
        } //BORRARR
        for (int i=1;i<ui->tableWidgetRefGNSSClock->columnCount();i++){
            if (ui->tableWidgetRefGNSSClock->item(1,i)->background().color().name()==RedColor) break;
            userRefGNSSClockOrder[i-1]=ui->tableWidgetRefGNSSClock->item(1,i)->text();
        }
        this->userRefGNSSClock_2_Command(userRefGNSSClockOrder,&refGNSSClockCmd);
        //if checkBoxOnlyRefGNSSClock checked
        if (refGNSSClockCmd.length()>0){
            if (refGNSSClockCmd!="GERCJI"||WriteAllParameters){
                *saveString += "-filter:refclkonlyorder " + refGNSSClockCmd + "\n";
                *runString << "-filter:refclkonlyorder" << refGNSSClockCmd;
            }
        } else {
            *errorString += "FILTER: At least one reference clock constellation should be selected.\n";
        }
    }

    if (SBASmaritime==0) {
        // Maximum PDOP
        if ( ui->checkBoxMaxHDOP->isChecked() == true ) {
            if ( ui->lineEditMaxHDOP->text() == "" ) {
                *errorString += "FILTER: Maximum HDOP in [DOP Filter] cannot be empty.\n";
            } else if ( ui->lineEditMaxHDOP->text().toDouble() == 0. ) {
                *errorString += "FILTER: Maximum HDOP in [DOP Filter] cannot be empty.\n";
            } else {
                //Disabled by default in all modes
                *saveString += "-filter:maxhdop " + ui->lineEditMaxHDOP->text() + "\n";
                *runString << "-filter:maxhdop" << ui->lineEditMaxHDOP->text();
            }
        } else {
            //Max HDOP is disabled by default in all modes
            if (WriteAllParameters==1) {
                *saveString += "--filter:maxhdop\n";
                *runString << "--filter:maxhdop";
            }
        }

        // Maximum PDOP
        if ( ui->checkBoxMaxPDOP->isChecked() == true ) {
            if ( ui->lineEditMaxPDOP->text() == "" ) {
                *errorString += "FILTER: Maximum PDOP in [DOP Filter] cannot be empty.\n";
            } else if ( ui->lineEditMaxPDOP->text().toDouble() == 0. ) {
                *errorString += "FILTER: Maximum PDOP in [DOP Filter] cannot be empty.\n";
            } else {
                //Disabled by default in all modes
                *saveString += "-filter:maxpdop " + ui->lineEditMaxPDOP->text() + "\n";
                *runString << "-filter:maxpdop" << ui->lineEditMaxPDOP->text();
            }
        } else {
            //Max PDOP is disabled by default in all modes
            if (WriteAllParameters==1) {
                *saveString += "--filter:maxpdop\n";
                *runString << "--filter:maxpdop";
            }
        }
        //PDOP or GDOP
        if ( ui->checkBoxMaxHDOP->isChecked() == true && ui->checkBoxMaxPDOP->isChecked() == true ) {
            if ( ui->checkBoxHDOPorPDOP->isChecked() == true ) {
                //Disabled by default in all modes
                *saveString += "-filter:hdoporpdop\n";
                *runString << "-filter:hdoporpdop";
            } else {
                //Disabled by default in all modes
                if (WriteAllParameters==1) {
                    *saveString += "--filter:hdoporpdop\n";
                    *runString << "--filter:hdoporpdop";
                }
            }
        } else {
            //Disabled by default in all modes
            if (WriteAllParameters==1) {
                *saveString += "--filter:hdoporpdop\n";
                *runString << "--filter:hdoporpdop";
            }
        }
    }
    // Maximum GDOP
    if ( ui->checkBoxMaxGDOP->isChecked() == true ) {
        if ( ui->lineEditMaxGDOP->text() == "" ) {
            *errorString += "FILTER: Maximum GDOP in [DOP Filter] cannot be empty.\n";
        } else if ( ui->lineEditMaxGDOP->text().toDouble() == 0. ) {
            *errorString += "FILTER: Maximum GDOP in [DOP Filter] cannot be empty.\n";
        } else {
            if ( ui->groupBoxSbas->isChecked()==false && ( ui->groupBoxReferenceStation->isChecked()==true || mode==1) ) {
                //In PPP and DGNSS Max GDOP is enabled by default with a threshold of 30
                if ( ui->lineEditMaxGDOP->text().toDouble() != 30 || WriteAllParameters==1) {
                    *saveString += "-filter:maxgdop " + ui->lineEditMaxGDOP->text() + "\n";
                    *runString << "-filter:maxgdop" << ui->lineEditMaxGDOP->text();
                }
            } else {
                //SBAS or SPP modes. Max GDOP is disabled by default
                *saveString += "-filter:maxgdop " + ui->lineEditMaxGDOP->text() + "\n";
                *runString << "-filter:maxgdop" << ui->lineEditMaxGDOP->text();
            }
        }
    } else {
        if ( ui->groupBoxSbas->isChecked()==false && ( ui->groupBoxReferenceStation->isChecked()==true || mode==1|| WriteAllParameters==1) ) {
            //In PPP and DGNSS Max GDOP is enabled by default with a threshold of 30
            *saveString += "--filter:maxgdop\n";
            *runString << "--filter:maxgdop";
        }
    }

    //Prefit outlier detector
    if (ui->checkBoxPrefitOutliers->isChecked()==true) {
        if ( ui->lineEditPrefitOutliers->text() == "" ) {
            *errorString += "FILTER: Prefit Outlier detector threshold in [Other Options] cannot be empty.\n";
        } else if ( ui->lineEditPrefitOutliers->text().toDouble() == 0. ) {
            *errorString += "FILTER: Prefit Outlier detector threshold in [Other Options] cannot be empty.\n";
        } else {
            if (WriteAllParameters==1) {
                //It is enabled by default in all modes
                *saveString += "-filter:prefitoutliers:median " + ui->lineEditPrefitOutliers->text() + "\n";
                *runString << "-filter:prefitoutliers:median" << ui->lineEditPrefitOutliers->text();
            } else if (ui->lineEditPrefitOutliers->text().toDouble()!=40.){
                *saveString += "-filter:prefitoutliers:median " + ui->lineEditPrefitOutliers->text() + "\n";
                *runString << "-filter:prefitoutliers:median" << ui->lineEditPrefitOutliers->text();
            }
        }
    } else {
        //It is enabled by default in all modes
        *saveString += "--filter:prefitoutliers:median\n";
        *runString << "--filter:prefitoutliers:median";
    }

    //Step detector
    if (ui->groupBoxSbas->isChecked()==true && ui->checkBoxStepDetector->isChecked()==true) {
        //Step detector only available for SBAS and by default disabled
        *saveString += "-filter:stepdetector\n";
        *runString << "-filter:stepdetector";
    }

    // Stanford-ESA Options (within Output tab)
    if ( ui->groupBoxStanfordESA->isChecked() == true ) {
        *saveString += "-filter:stfdesa\n";
        *runString << "-filter:stfdesa";
        if ( ui->lineEditStanfordEsaXmax->text() == "" ) {
            *errorString += "OUTPUT: Maximum X in [Stanford-ESA] cannot be empty.\n";
        } else if (ui->lineEditStanfordEsaXmax->text().toDouble() <= 0. ) {
            *errorString += "OUTPUT: Maximum X in [Stanford-ESA] must be greater than 0.\n";
        }
        if ( ui->lineEditStanfordEsaYmax->text() == "" ) {
            *errorString += "OUTPUT: Maximum Y in [Stanford-ESA] cannot be empty.\n";
        } else if (ui->lineEditStanfordEsaYmax->text().toDouble() <= 0. ) {
            *errorString += "OUTPUT: Maximum Y in [Stanford-ESA] must be greater than 0.\n";
        }
        if ( ui->lineEditStanfordEsaXres->text() == "" ) {
            *errorString += "OUTPUT: Resolution X in [Stanford-ESA] cannot be empty.\n";
        } else if (ui->lineEditStanfordEsaXres->text().toDouble() <= 0. ) {
            *errorString += "OUTPUT: Resolution X in [Stanford-ESA] must be greater than 0.\n";
        }
        if ( ui->lineEditStanfordEsaYres->text() == "" ) {
            *errorString += "OUTPUT: Resolution Y in [Stanford-ESA] cannot be empty.\n";
        } else if (ui->lineEditStanfordEsaYres->text().toDouble() <= 0. ) {
            *errorString += "OUTPUT: Resolution Y in [Stanford-ESA] must be greater than 0.\n";
        }
        if ( ui->lineEditStanfordEsaXmax->text() != "" && ui->lineEditStanfordEsaYmax->text() != "" && ui->lineEditStanfordEsaXres->text() != "" && ui->lineEditStanfordEsaYres->text() != "" ) {
            if ( ui->lineEditStanfordEsaXmax->text().toDouble() != 50. || WriteAllParameters==1 ) {
                *saveString += "-filter:stfdesa:xmax " + ui->lineEditStanfordEsaXmax->text() + "\n";
                *runString << "-filter:stfdesa:xmax" << ui->lineEditStanfordEsaXmax->text();
            }
            if ( ui->lineEditStanfordEsaYmax->text().toDouble() != 50. || WriteAllParameters==1 ) {
                *saveString += "-filter:stfdesa:ymax " + ui->lineEditStanfordEsaYmax->text() + "\n";
                *runString << "-filter:stfdesa:ymax" << ui->lineEditStanfordEsaYmax->text();
            }
            if ( ui->lineEditStanfordEsaXres->text().toDouble() != 0.1 || WriteAllParameters==1) {
                *saveString += "-filter:stfdesa:xres " + ui->lineEditStanfordEsaXres->text() + "\n";
                *runString << "-filter:stfdesa:xres" << ui->lineEditStanfordEsaXres->text();
            }
            if ( ui->lineEditStanfordEsaYres->text().toDouble() != 0.1|| WriteAllParameters==1 ) {
                *saveString += "-filter:stfdesa:yres " + ui->lineEditStanfordEsaYres->text() + "\n";
                *runString << "-filter:stfdesa:yres" << ui->lineEditStanfordEsaYres->text();
            }
        }
        if ( ui->lineEditStfdESAMaxSatCombinations->text() == "" ) {
            *errorString += "OUTPUT: Maximum Satellite Combinations in [Stanford-ESA] cannot be empty.\n";
        } else if (ui->lineEditStfdESAMaxSatCombinations->text().toInt() < 4 ) {
            *errorString += "OUTPUT: Maximum Satellite Combinations in [Stanford-ESA] must be equal or greater than 4.\n";
        } else if (ui->lineEditStfdESAMaxSatCombinations->text().toInt() != 999999 || WriteAllParameters==1 ) {
            *saveString += "-filter:stfdesa:maxsat " + ui->lineEditStfdESAMaxSatCombinations->text() + "\n";
            *runString << "-filter:stfdesa:maxsat" << ui->lineEditStfdESAMaxSatCombinations->text();
        }
        // Write Stanford-ESA Data File
        if ( ui->checkBoxStanfordESAallGeometries->isChecked() == true ) {
            //When enabling Stanford-ESA, by default the file will LOIs is enabled
            //*saveString += "-filter:stfdesaloi\n";
            //*runString << "-filter:stfdesaloi";
            if ( ui->lineEditHorizontalIntegrityRatio->text() == "" ) {
                *errorString += "OUTPUT: Horizontal integrity ratio threshold in [Stanford-ESA] cannot be empty.\n";
            } else if ( ui->lineEditHorizontalIntegrityRatio->text().toDouble() == 0. ) {
                *errorString += "OUTPUT: Horizontal integrity ratio threshold in [Stanford-ESA] cannot be 0.\n";
            } else {
                if ( ui->lineEditHorizontalIntegrityRatio->text().toDouble() != 0.7 || WriteAllParameters==1) {
                    *saveString += "-filter:stfdesa:hwir " + ui->lineEditHorizontalIntegrityRatio->text() + "\n";
                    *runString << "-filter:stfdesa:hwir" << ui->lineEditHorizontalIntegrityRatio->text();
                }
            }
            if ( ui->lineEditVerticalIntegrityRatio->text() == "" ) {
                *errorString += "OUTPUT: Vertical integrity ratio threshold in [Stanford-ESA] cannot be empty.\n";
            } else if ( ui->lineEditVerticalIntegrityRatio->text().toDouble() == 0. ) {
                *errorString += "OUTPUT: Vertical integrity ratio threshold in [Stanford-ESA] cannot be 0.\n";
            } else {
                if ( ui->lineEditVerticalIntegrityRatio->text().toDouble() != 0.7 || WriteAllParameters==1) {
                    *saveString += "-filter:stfdesa:vwir " + ui->lineEditVerticalIntegrityRatio->text() + "\n";
                    *runString << "-filter:stfdesa:vwir" << ui->lineEditVerticalIntegrityRatio->text();
                }
            }
        }
    }
}
