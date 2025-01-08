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


void gLAB_GUI::setInitialDCBISC(){
    //Initialize to nullptr
    for(int i=0;i<MAX_GNSS;i++) {
        for(int j=0; j<MAX_GNSS_FREQ;j++) {
            ComboBoxGNSSDCB[i][j]=nullptr;
            ComboBoxGNSSISC[i][j]=nullptr;
        }
    }
    //GPS
    GroupBoxGNSSDCB[GPS]=&gLAB_GUI::on_groupBoxShowDCBOptionsGPS_clicked;
    ComboBoxGNSSDCB[GPS][0]=ui->comboBoxDCBsfP1C1GPS;
    ComboBoxGNSSDCB[GPS][1]=ui->comboBoxDCBsfP1P2GPS;
    ComboBoxGNSSISC[GPS][0]=ui->comboBoxISCsfL1CAGPS;
    ComboBoxGNSSISC[GPS][1]=ui->comboBoxISCsfL2CGPS;
    ComboBoxGNSSISC[GPS][2]=ui->comboBoxISCsfL5I5GPS;
    ComboBoxGNSSISC[GPS][3]=ui->comboBoxISCsfL5Q5GPS;
    CommandGNSSDCB[GPS][0]="-model:dcb:sf:gps:p1c1";
    CommandGNSSDCB[GPS][1]="-model:dcb:sf:gps:p1p2";
    CommandGNSSISC[GPS][0]="-model:dcb:sf:gps:isc:l1ca";
    CommandGNSSISC[GPS][1]="-model:dcb:sf:gps:isc:l2c";
    CommandGNSSISC[GPS][2]="-model:dcb:sf:gps:isc:l5i5";
    CommandGNSSISC[GPS][3]="-model:dcb:sf:gps:isc:l5q5";
    //Galileo
    GroupBoxGNSSDCB[Galileo]=&gLAB_GUI::on_groupBoxShowDCBOptionsGalileo_clicked;
    ComboBoxGNSSDCB[Galileo][0]=ui->comboBoxDCBsfE1E5aGalileo;
    ComboBoxGNSSDCB[Galileo][1]=ui->comboBoxDCBsfE1E5bGalileo;
    CommandGNSSDCB[Galileo][0]="-model:dcb:sf:gal:e1e5a";
    CommandGNSSDCB[Galileo][1]="-model:dcb:sf:gal:e1e5b";
    //GLONASS
    GroupBoxGNSSDCB[GLONASS]=&gLAB_GUI::on_groupBoxShowDCBOptionsGLONASS_clicked;
    ComboBoxGNSSDCB[GLONASS][0]=ui->comboBoxDCBsfP1P2GLONASS;
    CommandGNSSDCB[GLONASS][0]="-model:dcb:sf:glo:p1p2";
    //SBAS
    GroupBoxGNSSDCB[GEO]=nullptr;
    //BDS
    GroupBoxGNSSDCB[BDS]=&gLAB_GUI::on_groupBoxShowDCBOptionsBDS_clicked;
    ComboBoxGNSSDCB[BDS][0]=ui->comboBoxDCBsfB2B6BDS;
    ComboBoxGNSSDCB[BDS][1]=ui->comboBoxDCBsfB7B6BDS;
    ComboBoxGNSSDCB[BDS][2]=ui->comboBoxDCBsfSP3BDS;
    CommandGNSSDCB[BDS][0]="-model:dcb:sf:bds:b2b6";
    CommandGNSSDCB[BDS][1]="-model:dcb:sf:bds:b7b6";
    CommandGNSSDCB[BDS][2]="-model:dcb:sf:bds:sp3";
    //QZSS
    GroupBoxGNSSDCB[QZSS]=&gLAB_GUI::on_groupBoxShowDCBOptionsQZSS_clicked;
    ComboBoxGNSSDCB[QZSS][0]=ui->comboBoxDCBsfC1CQZSS;
    ComboBoxGNSSISC[QZSS][0]=ui->comboBoxISCsfL2CQZSS;
    ComboBoxGNSSISC[QZSS][1]=ui->comboBoxISCsfL5I5QZSS;
    ComboBoxGNSSISC[QZSS][2]=ui->comboBoxISCsfL5Q5QZSS;
    CommandGNSSDCB[QZSS][0]="-model:dcb:sf:qzs:c1c";
    CommandGNSSISC[QZSS][0]="-model:dcb:sf:qzs:isc:l2c";
    CommandGNSSISC[QZSS][1]="-model:dcb:sf:qzs:isc:l5i5";
    CommandGNSSISC[QZSS][2]="-model:dcb:sf:qzs:isc:l5q5";
    //IRNSS
    GroupBoxGNSSDCB[IRNSS]=&gLAB_GUI::on_groupBoxShowDCBOptionsIRNSS_clicked;
    ComboBoxGNSSDCB[IRNSS][0]=ui->comboBoxDCBsfC9C5IRNSS;
    CommandGNSSDCB[IRNSS][0]="-model:dcb:sf:irn:c9c5";
}

// Function to hide or show the ionosphere correction combo box
void gLAB_GUI::on_checkBoxIonoCorrection_clicked(bool checked) {
    ui->checkBoxIonoCorrection->setChecked(checked);
    ui->frameIonoCorrection->setHidden(!checked);
}

// Function to hide or show the troposphere correction combo box
void gLAB_GUI::on_checkBoxTropoCorrection_clicked(bool checked) {
    ui->checkBoxTropoCorrection->setChecked(checked);
    ui->frameTropoCorrection->setHidden(!checked);
    //If troposphere is disabled, also disable in the filter the estimation of troposphere residual
    if (checked==false) {
        ui->checkBoxEstimateTroposphere->setChecked(false);
    }
}

// Function to hide or show the Receiver Antenna Phase Centre Correction box
void gLAB_GUI::on_checkBoxAntennaPhase_clicked(bool checked) {
    if (ui->checkBoxSatAntex->isChecked()==false && checked==true) {
        this->on_checkBoxSatAntex_clicked(true);
    }
    ui->checkBoxAntennaPhase->setChecked(checked);
    ui->groupBoxReceiverAntennaPhaseCentreCorrection->setHidden(!checked);
    this->on_radioButtonAPCread_clicked();
    ui->checkBoxReceiverAntennaPhaseCentreVariation->setChecked(checked);
    if (checked==false && ui->checkBoxSatMassCentre->isChecked()==false ) {
        this->on_checkBoxRecAntex_clicked(false);
        this->on_checkBoxSatAntex_clicked(false);
    }
}

// Function to hide or show the satellite Antenna Phase Centre Correction box
void gLAB_GUI::on_checkBoxSatMassCentre_clicked(bool checked) {
    ui->checkBoxSatMassCentre->setChecked(checked);
    ui->frameSatellitePhaseCenterVariation->setHidden(!checked);
    ui->checkBoxSatelliteAntennaPhaseCentreVariation->setChecked(checked);
    if (checked==true) {
            this->on_checkBoxSatAntex_clicked(true);
    } else if (checked==false && ui->checkBoxAntennaPhase->isChecked()==false ) {
        this->on_checkBoxSatAntex_clicked(false);
        this->on_checkBoxRecAntex_clicked(false);
    }
}

// Function to hide or show the Receiver Antenna Reference Point Correction box
void gLAB_GUI::on_checkBoxAntennaReference_clicked(bool checked) {
    ui->checkBoxAntennaReference->setChecked(checked);
    ui->groupBoxReceiverAntennaReferencePointCorrection->setHidden(!checked);
    this->on_radioButtonARPread_clicked();
}

//Function to show or hide the concatenated precise orbit and clock options
void gLAB_GUI::on_groupBoxConcatenedPreciseFiles_clicked(bool checked) {
    ui->groupBoxConcatenedPreciseFiles->setChecked(checked);
    ui->frameConcatenedPreciseFiles->setHidden(!checked);
}

// Function to set the correct stacked in APC
void gLAB_GUI::on_radioButtonAPCread_clicked() {
    ui->radioButtonAPCread->setChecked(true);
    ui->radioButtonAPCspecify->setChecked(false);
    ui->pushButtonAPCAdvanced->setEnabled(false);
}

// Function to set the correct stacked in APC
void gLAB_GUI::on_radioButtonAPCspecify_clicked() {
    ui->radioButtonAPCread->setChecked(false);
    ui->radioButtonAPCspecify->setChecked(true);
    ui->pushButtonAPCAdvanced->setEnabled(true);
}

// Function to set the APC Advanced
void gLAB_GUI::on_pushButtonAPCAdvanced_clicked(){
    APCAdvanced->setModal(true);
    APCAdvanced->show();
}
// Function to set the correct stacked in ARP
void gLAB_GUI::on_radioButtonARPread_clicked() {
    ui->radioButtonARPread->setChecked(true);
    ui->radioButtonARPspecify->setChecked(false);
    ui->frameARPcorrection->setHidden(true);
}

// Function to set the correct stacked in ARP
void gLAB_GUI::on_radioButtonARPspecify_clicked() {
    ui->radioButtonARPread->setChecked(false);
    ui->radioButtonARPspecify->setChecked(true);
    ui->frameARPcorrection->setHidden(false);
}

// Function to modify the Input tab based on the modification done in Modelling tab
void gLAB_GUI::on_comboBoxDCBsfP1P2GPS_currentIndexChanged(int index) {
    openP1P2=0;
    ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(index);
    if (index>0){
        this->on_checkBoxProcessAustralianTestBedMessages_clicked(false);
    }
    if (index>0 && (ui->stackedWidgetComboBoxDcbSource->currentIndex()==1 || index>1)) {
        if (ui->groupBoxAuxFiles->isChecked()==false) {
            this->on_groupBoxAuxFiles_clicked(true);
        }
        if (ui->groupBoxP1P2correction->isChecked()==false) {
            this->on_groupBoxP1P2correction_clicked(true);
        }
    } else if (index<=0) {
        this->on_groupBoxP1P2correction_clicked(false);
    }
    if (index==1) {
        ui->checkBoxDiscardUnhealthy->setHidden(false);
    } else if (index<=0 && (ui->radioButtonOrbitBrdc->isChecked()==false)) {
        //ui->checkBoxDiscardUnhealthy->setHidden(true);
    }

    if ( index == 1 ) { // Broadcast
        if (ui->tabWidget->currentIndex()!=0 && ui->stackedWidgetComboBoxDcbSource->currentIndex()==0) {
            this->on_groupBoxP1P2correction_clicked(false);
        }
        if ( ui->groupBoxP1P2correction->isChecked() == false && ui->groupBoxP1C1correction->isChecked() == false && ui->groupBoxUserAddedError->isChecked() == false && ui->groupBoxUserDefinedSbasSigmaMultipath->isChecked() == false ) {
            if (ui->tabWidget->currentIndex()!=0) {
                this->on_groupBoxAuxFiles_clicked(false);
            }
        }
        //if (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0) {
            ui->comboBoxDcbSource->setCurrentIndex(0);
        //} else {
            ui->comboBoxDcbSourcePPP->setCurrentIndex(0);
        //
        ui->checkBoxDiscardUnhealthy->setHidden(false);
    } else if ( index == 2 ) { // DCB file
        if (ui->groupBoxAuxFiles->isChecked()==false) {
            this->on_groupBoxAuxFiles_clicked(true);
        }
        if (ui->groupBoxP1P2correction->isChecked()==false) {
            this->on_groupBoxP1P2correction_clicked(true);
        }
        if (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0) {
            ui->comboBoxDcbSource->setCurrentIndex(2);
        } else {
            ui->comboBoxDcbSourcePPP->setCurrentIndex(1);
            //ui->checkBoxDiscardUnhealthy->setHidden(true);
        }
    } else if ( index == 3 ) { // IONEX
        if ( ui->groupBoxIonoSource->isChecked() == true && ui->radioButtonIonoSourceIonex->isChecked() == true ) {
            if (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0) {
                if (ui->comboBoxDcbSource->currentIndex() < 3 ) {
                    ui->comboBoxDcbSource->setCurrentIndex(3);
                }
            } else {
                if (ui->comboBoxDcbSourcePPP->currentIndex() < 2) {
                    ui->comboBoxDcbSourcePPP->setCurrentIndex(2);
                }
                //ui->checkBoxDiscardUnhealthy->setHidden(true);
            }
        } else {
            if (ui->groupBoxAuxFiles->isChecked()==false) {
                this->on_groupBoxAuxFiles_clicked(true);
            }
            if (ui->groupBoxP1P2correction->isChecked()==false) {
                this->on_groupBoxP1P2correction_clicked(true);
            }
            if (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0) {
                if (ui->comboBoxDcbSource->currentIndex() < 4 ) {
                    ui->comboBoxDcbSource->setCurrentIndex(4);
                }
            } else {
                if (ui->comboBoxDcbSourcePPP->currentIndex() < 3) {
                    ui->comboBoxDcbSourcePPP->setCurrentIndex(3);
                }
                //ui->checkBoxDiscardUnhealthy->setHidden(true);
            }
        }
    }
    openP1P2=1;
}

// Function to modify the Input tab based on the modification done in Modelling tab
void gLAB_GUI::on_comboBoxDCBsfP1C1GPS_currentIndexChanged(int index) {
    ui->comboBoxDCBsfP1C1GPS->setCurrentIndex(index);
    if ( index == 0 ) {
        if (ui->groupBoxP1C1correction->isChecked()==true) {
            //If P1-C1 is set to flexible and P1-C1 correction is enabled, change to manual GPS Receiver type, type 2 (No P1)
            this->on_radioButtonGPSReceiverTypeUserSelection_clicked();
            ui->comboBoxGPSReceiverTypeSelection->setCurrentIndex(1);
        }
    } else if ( index == 1 ) {
        this->on_groupBoxAuxFiles_clicked(true);
        this->on_groupBoxP1C1correction_clicked(true);
    }
}

// Function to modify the Input tab based on the modification done in Modelling tab
void gLAB_GUI::on_comboBoxIonoCorrection_currentIndexChanged(int index) {
    ui->comboBoxIonoCorrection->setCurrentIndex(index);
    if ( index == 3 ) { // IONEX
        if (ui->groupBoxIonoSource->isChecked()==false) this->on_groupBoxIonoSource_clicked(true);
        this->on_radioButtonIonoSourceIonex_clicked();
    } else if ( index == 4 ) { // SBAS
        ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(1);
        this->on_groupBoxIonoSource_clicked(true);
        this->on_radioButtonIonoSourceSbas_clicked();
    } else { // Broadcast (Klobuchar or IONEX)
        ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(1);
        if ( ui->comboBoxIonoSourceBrdc->currentIndex() == 1 ) {
            this->on_groupBoxIonoSource_clicked(true);
        } else if ( ui->comboBoxIonoSourceBrdc->currentIndex() == 0 ) {
            this->on_radioButtonIonoSourceBrdc_clicked();
            //this->on_groupBoxIonoSource_clicked(false);
        }
    }
}

//Function to config DCB options
//Function to show all DCB
void gLAB_GUI::on_groupBoxShowDCBOptions_clicked(bool checked){
    ui->groupBoxShowDCBOptions->setChecked(checked);
    ui->frameShowDCBOptions->setHidden(!checked);
}
//Function to config GPS DCB
void gLAB_GUI::on_groupBoxShowDCBOptionsGPS_clicked(bool checked){
    ui->groupBoxShowDCBOptionsGPS->setChecked(checked);
    ui->frameShowDCBOptionsGPS->setHidden(!checked);
}
//Function to config Galileo DCB
void gLAB_GUI::on_groupBoxShowDCBOptionsGalileo_clicked(bool checked){
    ui->groupBoxShowDCBOptionsGalileo->setChecked(checked);
    ui->frameShowDCBOptionsGalileo->setHidden(!checked);
}
//Function to config GLONASS DCB
void gLAB_GUI::on_groupBoxShowDCBOptionsGLONASS_clicked(bool checked){
    ui->groupBoxShowDCBOptionsGLONASS->setChecked(checked);
    ui->frameShowDCBOptionsGLONASS->setHidden(!checked);
}
//Function to config BDS DCB
void gLAB_GUI::on_groupBoxShowDCBOptionsBDS_clicked(bool checked){
    ui->groupBoxShowDCBOptionsBDS->setChecked(checked);
    ui->frameShowDCBOptionsBDS->setHidden(!checked);
}
//Function to config QZSS DCB
void gLAB_GUI::on_groupBoxShowDCBOptionsQZSS_clicked(bool checked){
    ui->groupBoxShowDCBOptionsQZSS->setChecked(checked);
    ui->frameShowDCBOptionsQZSS->setHidden(!checked);
}
//Function to config IRNSS DCB
void gLAB_GUI::on_groupBoxShowDCBOptionsIRNSS_clicked(bool checked){
    ui->groupBoxShowDCBOptionsIRNSS->setChecked(checked);
    ui->frameShowDCBOptionsIRNSS->setHidden(!checked);
}

//Nav message types functions
void gLAB_GUI::userNavMessageTypes_2_Command(QString *saveString, QStringList *runString, QString *errorString){
    //GPS
    if (ui->checkBoxGPS->isChecked()){
        QString cmdNavMT="";
        int cmdOK=0,nOk=0,numRed=0;
        //Check for SBAS and DGNSS, as in SBAS and DGNSS navigation messages types are fixed
        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeGPS->columnCount();i++){
                if (ui->tableWidgetNavMessageTypeGPS->item(0,i)->background().color().name()==RedColor) numRed++;
            }
            if (numRed==ui->tableWidgetNavMessageTypeGPS->columnCount()) {
                *errorString+= "MODEL: GPS constellation is selected, but all its navigation message types are disabled. Enable a navigation message type or disable GPS constellation.\n";
            } else {
                for (int i=0; i<ui->tableWidgetNavMessageTypeGPS->columnCount();i++){
                    if (ui->tableWidgetNavMessageTypeGPS->item(0,i)->text()!=NavMessageTypes[GPS][0][i]) {
                        cmdOK=1;                        ;
                    }
                    if (ui->tableWidgetNavMessageTypeGPS->item(0,i)->background().color().name()==RedColor) {
                        if (i>0) cmdOK=1;
                        break;
                    }
                    cmdNavMT += ui->tableWidgetNavMessageTypeGPS->item(0,i)->text() + ",";
                    nOk++;
                }
                if (cmdOK==1){
                    cmdNavMT.chop(1);
                    if ( nOk==ui->tableWidgetNavMessageTypeGPS->columnCount() && ui->tableWidgetNavMessageTypeGPS->item(0,0)->text()=="CNAV") {
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
        } else if (WriteAllParameters==1) {
            *saveString += "-model:brdc:gps LNAV\n";
            *runString << "-model:brdc:gps" << "LNAV";
        }
    }
    //Galileo
    if (ui->checkBoxGalileo->isChecked()){
        QString cmdNavMT="",cmdNavMT2="";
        int cmdOK=0, nOk=0,numRed=0;
        //Check for SBAS and DGNSS, as in SBAS and DGNSS navigation messages types are fixed
        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeGalileo->columnCount();i++){
                if (ui->tableWidgetNavMessageTypeGalileo->item(0,i)->background().color().name()==RedColor) numRed++;
            }
            if (numRed==ui->tableWidgetNavMessageTypeGalileo->columnCount()) {
                *errorString+= "MODEL: Galileo constellation is selected, but all its navigation message types are disabled. Enable a navigation message type or disable Galileo constellation.\n";
            } else {
                for (int i=0; i<ui->tableWidgetNavMessageTypeGalileo->columnCount();i++){
                    if (ui->tableWidgetNavMessageTypeGalileo->item(0,i)->text()!=NavMessageTypes[Galileo][0][i]) {
                        cmdOK=1;
                    }
                    if (ui->tableWidgetNavMessageTypeGalileo->item(0,i)->background().color().name()==RedColor) {
                        if (i>0) cmdOK=1;
                        break;
                    }
                    cmdNavMT += ui->tableWidgetNavMessageTypeGalileo->item(0,i)->text() + ",";
                    if (i>0) {
                        cmdNavMT2 += ui->tableWidgetNavMessageTypeGalileo->item(0,i)->text() + ",";
                    }
                    nOk++;
                }
                if (cmdOK==1) {
                    cmdNavMT.chop(1);
                    cmdNavMT2.chop(1);
                    if ( nOk==ui->tableWidgetNavMessageTypeGalileo->columnCount() && ui->tableWidgetNavMessageTypeGalileo->item(0,0)->text()=="FNAV" && cmdNavMT2== GalINAVDefaultOrder ) {
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
                } else if (WriteAllParameters){
                    *saveString += "-model:brdc:gal PreferINAV\n";
                    *runString << "-model:brdc:gal" << "PreferINAV";
                }
            }
        } else if (WriteAllParameters==1 && ui->labelCurrentTemplate->text()=="SBAS DFMC") {
            *saveString += "-model:brdc:gal FNAV\n";
            *runString << "-model:brdc:gal" << "FNAV";
        }
    }
    //GLONASS
    if ( ui->checkBoxGLONASS->isChecked()){
        QString cmdNavMT="";
        //int cmdOK=0,nOk=0,outOfOrder=0;
        int numRed=0;
        //Check for SBAS and DGNSS, as in SBAS and DGNSS navigation messages types are fixed
        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeGLONASS->columnCount();i++){
                if (ui->tableWidgetNavMessageTypeGLONASS->item(0,i)->background().color().name()==RedColor) numRed++;
            }
            if (numRed==ui->tableWidgetNavMessageTypeGLONASS->columnCount()) {
                *errorString+= "MODEL: GLONASS constellation is selected, but all its navigation message types are disabled. Enable a navigation message type or disable GLONASS constellation.\n";
            } else {
                //Code commented due to there is no option -model:brdc:glo in the command line
                /*for (int i=0; i<ui->tableWidgetNavMessageTypeGLONASS->columnCount();i++){
                    if (ui->tableWidgetNavMessageTypeGLONASS->item(0,i)->text()!=NavMessageTypes[GLONASS][0][i]) {
                        cmdOK=1;
                        outOfOrder=1;
                    }
                    if (ui->tableWidgetNavMessageTypeGLONASS->item(0,i)->background().color().name()==RedColor) {
                        if (i>0) cmdOK=1;
                        break;
                    }
                    cmdNavMT += ui->tableWidgetNavMessageTypeGLONASS->item(0,i)->text() + ",";
                    nOk++;
                }
                if (cmdOK==1){
                    cmdNavMT.chop(1);
                    *saveString += "-model:brdc:glo " + cmdNavMT + "\n";
                    *runString << "-model:brdc:glo" << cmdNavMT;
                } else if (WriteAllParameters){
                    *saveString += "-model:brdc:glo FDMA\n";
                    *runString << "-model:brdc:glo" << "FDMA";
                }*/
            }
        } else if (WriteAllParameters==1 && ui->labelCurrentTemplate->text()=="SBAS 1F") {
            //Code commented due to there is no option -model:brdc:glo in the command line
            /**saveString += "-model:brdc:glo FDMA\n";
            *runString << "-model:brdc:glo" << "FDMA";*/
        }
    }
    //GEO
    //NOTE: -model:brdc:geo not implemented in gLAB
    if ( ui->checkBoxGEO->isChecked() ){
        QString cmdNavMT="";
        //int cmdOK=0,nOk=0,outOfOrder=0;
        int numRed=0;
        //Check for SBAS and DGNSS, as in SBAS and DGNSS navigation messages types are fixed
        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeGEO->columnCount();i++){
                if (ui->tableWidgetNavMessageTypeGEO->item(0,i)->background().color().name()==RedColor) numRed++;
            }
            if (numRed==ui->tableWidgetNavMessageTypeGEO->columnCount()) {
                *errorString+= "MODEL: GEO constellation is selected, but all its navigation message types are disabled. Enable a navigation message type or disable GEO constellation.\n";
            } else {
                //Code commented due to there is no option -model:brdc:geo in the command line
                /*for (int i=0; i<ui->tableWidgetNavMessageTypeGEO->columnCount();i++){
                    if (ui->tableWidgetNavMessageTypeGEO->item(0,i)->text()!=NavMessageTypes[GEO][0][i]) {
                        cmdOK=1;
                        outOfOrder=1;
                    }
                    if (ui->tableWidgetNavMessageTypeGEO->item(0,i)->background().color().name()==RedColor) {
                        if (i>0) cmdOK=1;
                        break;
                    }
                    cmdNavMT += ui->tableWidgetNavMessageTypeGEO->item(0,i)->text() + ",";
                    nOk++;
                }
                if (cmdOK==1){
                    cmdNavMT.chop(1);
                    *saveString += "-model:brdc:geo " + cmdNavMT + "\n";
                    *runString << "-model:brdc:geo" << cmdNavMT;
                } else if (WriteAllParameters){
                    *saveString += "-model:brdc:geo CNAV\n";
                    *runString << "-model:brdc:geo" << "CNAV";
                }*/
            }
        } else if (WriteAllParameters==1) {
            //Code commented due to there is no option -model:brdc:geo in the command line
           /* *saveString += "-model:brdc:geo CNAV\n";
            *runString << "-model:brdc:geo" << "CNAV";*/
        }
    }
    //BDS
    if (ui->checkBoxBDS->isChecked()){
        QString cmdNavMT="";
        int cmdOK=0,nOk=0,numRed=0;
        //Check for SBAS and DGNSS, as in SBAS and DGNSS navigation messages types are fixed
        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeBDS->columnCount();i++){
                if (ui->tableWidgetNavMessageTypeBDS->item(0,i)->background().color().name()==RedColor) numRed++;
            }
            if (numRed==ui->tableWidgetNavMessageTypeBDS->columnCount()) {
                *errorString+= "MODEL: BeiDou constellation is selected, but all its navigation message types are disabled. Enable a navigation message type or disable BeiDou constellation.\n";
            } else {
                for (int i=0; i<ui->tableWidgetNavMessageTypeBDS->columnCount();i++){
                    if (ui->tableWidgetNavMessageTypeBDS->item(0,i)->text()!=NavMessageTypes[BDS][0][i]) {
                        cmdOK=1;
                    }
                    if (ui->tableWidgetNavMessageTypeBDS->item(0,i)->background().color().name()==RedColor) {
                        if (i>0) cmdOK=1;
                        break;
                    }
                    cmdNavMT += ui->tableWidgetNavMessageTypeBDS->item(0,i)->text() + ",";
                    nOk++;
                }
                if (cmdOK==1){
                    cmdNavMT.chop(1);
                    *saveString += "-model:brdc:bds " + cmdNavMT + "\n";
                    *runString << "-model:brdc:bds" << cmdNavMT;
                } else if (WriteAllParameters){
                    *saveString += "-model:brdc:bds D1\n";
                    *runString << "-model:brdc:bds" << "D1";
                }
            }
        } else if (WriteAllParameters==1 && ui->labelCurrentTemplate->text()=="SBAS DFMC") {
            *saveString += "-model:brdc:bds D1\n";
            *runString << "-model:brdc:bds" << "D1";
        }
    }
    //QZSS
    if (ui->checkBoxQZSS->isChecked()){
        QString cmdNavMT="";
        int cmdOK=0,nOk=0,numRed=0;
        //Check for SBAS and DGNSS, as in SBAS and DGNSS navigation messages types are fixed
        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeQZSS->columnCount();i++){
                if (ui->tableWidgetNavMessageTypeQZSS->item(0,i)->background().color().name()==RedColor) numRed++;
            }
            if (numRed==ui->tableWidgetNavMessageTypeQZSS->columnCount()) {
                *errorString+= "MODEL: QZSS constellation is selected, but all its navigation message types are disabled. Enable a navigation message type or disable QZSS constellation.\n";
            } else {
                for (int i=0; i<ui->tableWidgetNavMessageTypeQZSS->columnCount();i++){
                    if (ui->tableWidgetNavMessageTypeQZSS->item(0,i)->text()!=NavMessageTypes[QZSS][0][i]) {
                        cmdOK=1;
                    }
                    if (ui->tableWidgetNavMessageTypeQZSS->item(0,i)->background().color().name()==RedColor) {
                        if (i>0) cmdOK=1;
                        break;
                    }
                    cmdNavMT += ui->tableWidgetNavMessageTypeQZSS->item(0,i)->text() + ",";
                    nOk++;
                }
                if (cmdOK==1){
                    cmdNavMT.chop(1);
                    *saveString += "-model:brdc:qzs " + cmdNavMT + "\n";
                    *runString << "-model:brdc:qzs" << cmdNavMT;
                } else if (WriteAllParameters){
                    *saveString += "-model:brdc:qzs LNAV\n";
                    *runString << "-model:brdc:qzs" << "LNAV";
                }
            }
        } else if (WriteAllParameters==1 && ui->labelCurrentTemplate->text()=="SBAS DFMC") {
            *saveString += "-model:brdc:qzs LNAV\n";
            *runString << "-model:brdc:qzs" << "LNAV";
        }
    }
    //IRNSS
    if ( ui->checkBoxIRNSS->isChecked()){
        QString cmdNavMT="";
        //int cmdOK=0,nOk=0,outOfOrder=0;
        int numRed=0;
        //Check for SBAS and DGNSS, as in SBAS and DGNSS navigation messages types are fixed
        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeIRNSS->columnCount();i++){
                if (ui->tableWidgetNavMessageTypeIRNSS->item(0,i)->background().color().name()==RedColor) numRed++;
            }
            if (numRed==ui->tableWidgetNavMessageTypeIRNSS->columnCount()) {
                *errorString+= "MODEL: IRNSS constellation is selected, but all its navigation message types are disabled. Enable a navigation message type or disable IRNSS constellation.\n";
            } else {
                //Code commented due to there is no option -model:brdc:irn in the command line
                /*for (int i=0; i<ui->tableWidgetNavMessageTypeIRNSS->columnCount();i++){
                    if (ui->tableWidgetNavMessageTypeIRNSS->item(0,i)->text()!=NavMessageTypes[IRNSS][0][i]) {
                        cmdOK=1;
                        outOfOrder=1;
                    }
                    if (ui->tableWidgetNavMessageTypeIRNSS->item(0,i)->background().color().name()==RedColor) {
                        if (i>0) cmdOK=1;
                        break;
                    }
                    cmdNavMT += ui->tableWidgetNavMessageTypeIRNSS->item(0,i)->text() + ",";
                    nOk++;
                }
                if (cmdOK==1){
                    cmdNavMT.chop(1);
                    *saveString += "-model:brdc:irnss " + cmdNavMT + "\n";
                    *runString << "-model:brdc:irnss" << cmdNavMT;
                } else if (WriteAllParameters){
                    *saveString += "-model:brdc:irnss CNAV\n";
                    *runString << "-model:brdc:irnss" << "CNAV";
                }*/
            }
        } else if (WriteAllParameters==1) {
            //Code commented due to there is no option -model:brdc:irnss in the command line
           /* *saveString += "-model:brdc:irnss CNAV\n";
            *runString << "-model:brdc:irnss" << "CNAV";*/
        }
    }
}
void gLAB_GUI::command_2_UserNavMessageTypes(QString const *navMessageTypesCmd,QString const *navMessageTypesOption,QString *warningString, int userCommand) {

    if (userCommand==1 && (ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true)) {
        *warningString += "MODELLING: Changing navigation message types or order is not allowed in SBAS or DGNSS modes. Parameter '" + *navMessageTypesCmd + "' was skipped.\n";
        return;
    }

    //GPS
    if (QString::compare(*navMessageTypesCmd, "-model:brdc:gps", Qt::CaseInsensitive)==0 ){
        if ( QString::compare(*navMessageTypesOption, "PreferLNAV", Qt::CaseInsensitive)==0 ){
            this->selectGNSS_NavMessageTypes(1,GPS);
        } else if ( QString::compare(*navMessageTypesOption, "PreferCNAV", Qt::CaseInsensitive)==0 ){
            this->selectGNSS_NavMessageTypes(1,GPS);
            ui->tableWidgetNavMessageTypeGPS->setCurrentItem(ui->tableWidgetNavMessageTypeGPS->item(0,1));
            this->moveNavMessageTypesColumn(ui->tableWidgetNavMessageTypeGPS,1,0,0);
            ui->tableWidgetNavMessageTypeGPS->clearSelection();
        } else {
            int typeOK=0;
            QStringList strNavMT=navMessageTypesOption->split(",", QString::SkipEmptyParts);
            this->selectGNSS_NavMessageTypes(0,GPS);
            for (int i=0; i<strNavMT.count(); i++){
                int itemTab=0;
                for (itemTab=0; itemTab<ui->tableWidgetNavMessageTypeGPS->columnCount(); itemTab++){
                    if ( QString::compare(strNavMT[i], ui->tableWidgetNavMessageTypeGPS->item(0,itemTab)->text(), Qt::CaseInsensitive)==0 && ui->tableWidgetNavMessageTypeGPS->item(0,itemTab)->background().color().name()==RedColor ) {
                        //Select item to be moved (this is necessary otherwise navMessageTypesItem_doubleClicked function does not move the item)
                        ui->tableWidgetNavMessageTypeGPS->setCurrentItem(ui->tableWidgetNavMessageTypeGPS->item(0,itemTab));
                        navMessageTypesItem_doubleClicked(ui->tableWidgetNavMessageTypeGPS->item(0,itemTab));
                        typeOK++;
                        break;
                    }
                }
                if ( itemTab>=ui->tableWidgetNavMessageTypeGPS->columnCount() ){
                    *warningString += "Parameter '-model:brdc:gps' has unknown type '" + strNavMT[i] +"'. It was skipped.\n";
                }
            }
            if ( typeOK<1 ){
                *warningString += "Parameter '-model:brdc:gps' has no available value. It was set as Default.\n";
                this->selectGNSS_NavMessageTypes(1,GPS);
            }
        }

    //Galileo
    } else if (QString::compare(*navMessageTypesCmd, "-model:brdc:gal", Qt::CaseInsensitive)==0 ){
        if ( QString::compare(*navMessageTypesOption, "PreferINAV", Qt::CaseInsensitive)==0 ){
            this->selectGNSS_NavMessageTypes(1,Galileo);
        } else if ( QString::compare(*navMessageTypesOption, "PreferFNAV", Qt::CaseInsensitive)==0 ){
            this->selectGNSS_NavMessageTypes(1,Galileo);
            ui->tableWidgetNavMessageTypeGalileo->setCurrentItem(ui->tableWidgetNavMessageTypeGalileo->item(0,3));
            this->moveNavMessageTypesColumn(ui->tableWidgetNavMessageTypeGalileo,3,0,0);
            ui->tableWidgetNavMessageTypeGalileo->clearSelection();
        } else if ( QString::compare(*navMessageTypesOption, "INAV", Qt::CaseInsensitive)==0 ){
            //INAV is INAVE1E5b, INAVE1, INAVE5b
            this->selectGNSS_NavMessageTypes(1,Galileo);
            //Disable FNAV
            ui->tableWidgetNavMessageTypeGalileo->item(0,3)->setBackgroundColor(RedColor);
        } else {
            int typeOK=0;
            QStringList strNavMT=navMessageTypesOption->split(",", QString::SkipEmptyParts);
            this->selectGNSS_NavMessageTypes(0,Galileo);
            for (int i=0; i<strNavMT.count(); i++){
                int itemTab=0;

                for (itemTab=0; itemTab<ui->tableWidgetNavMessageTypeGalileo->columnCount(); itemTab++){
                    if ( QString::compare(strNavMT[i], ui->tableWidgetNavMessageTypeGalileo->item(0,itemTab)->text(), Qt::CaseInsensitive)==0 && ui->tableWidgetNavMessageTypeGalileo->item(0,itemTab)->background().color().name()==RedColor ) {
                        //Select item to be moved (this is necessary otherwise navMessageTypesItem_doubleClicked function does not move the item)
                        ui->tableWidgetNavMessageTypeGalileo->setCurrentItem(ui->tableWidgetNavMessageTypeGalileo->item(0,itemTab));
                        navMessageTypesItem_doubleClicked(ui->tableWidgetNavMessageTypeGalileo->item(0,itemTab));
                        typeOK++;
                        break;
                    }
                }
                if ( itemTab>=ui->tableWidgetNavMessageTypeGalileo->columnCount() ){
                    *warningString += "Parameter '-model:brdc:gal' has unknown type '" + strNavMT[i] +"'. It was skipped.\n";
                }
            }
            if ( typeOK<1 ){
                *warningString += "Parameter '-model:brdc:gal' has no available value. It was set as Default.\n";
                this->selectGNSS_NavMessageTypes(1,Galileo);
            }
        }

    //BDS
    } else if (QString::compare(*navMessageTypesCmd, "-model:brdc:bds", Qt::CaseInsensitive)==0 ){
        if ( QString::compare(*navMessageTypesOption, "PreferD1", Qt::CaseInsensitive)==0 ){
            this->selectGNSS_NavMessageTypes(1,BDS);
        } else {
            int typeOK=0;
            QStringList strNavMT=navMessageTypesOption->split(",", QString::SkipEmptyParts);
            this->selectGNSS_NavMessageTypes(0,BDS);
            for (int i=0; i<strNavMT.count(); i++){
                int itemTab=0;
                for (itemTab=0; itemTab<ui->tableWidgetNavMessageTypeBDS->columnCount(); itemTab++){
                    if ( QString::compare(strNavMT[i], ui->tableWidgetNavMessageTypeBDS->item(0,itemTab)->text(), Qt::CaseInsensitive)==0 && ui->tableWidgetNavMessageTypeBDS->item(0,itemTab)->background().color().name()==RedColor ) {
                        //Select item to be moved (this is necessary otherwise navMessageTypesItem_doubleClicked function does not move the item)
                        ui->tableWidgetNavMessageTypeBDS->setCurrentItem(ui->tableWidgetNavMessageTypeBDS->item(0,itemTab));
                        navMessageTypesItem_doubleClicked(ui->tableWidgetNavMessageTypeBDS->item(0,itemTab));
                        typeOK++;
                        break;
                    }
                }
                if ( itemTab>=ui->tableWidgetNavMessageTypeBDS->columnCount() ){
                    *warningString += "Parameter '-model:brdc:bds' has unknown type '" + strNavMT[i] +"'. It was skipped.\n";
                }
            }
            if ( typeOK<1 ){
                *warningString += "Parameter '-model:brdc:bds' has no available value. It was set as Default.\n";
                this->selectGNSS_NavMessageTypes(1,BDS);
            }
        }

    //QZSS
    } else if (QString::compare(*navMessageTypesCmd, "-model:brdc:qzss", Qt::CaseInsensitive)==0 || QString::compare(*navMessageTypesCmd, "-model:brdc:qzs", Qt::CaseInsensitive)==0 ){
        if ( QString::compare(*navMessageTypesOption, "PreferLNAV", Qt::CaseInsensitive)==0 ){
            this->selectGNSS_NavMessageTypes(1,QZSS);
        } else {
            int typeOK=0;
            QStringList strNavMT=navMessageTypesOption->split(",", QString::SkipEmptyParts);
            this->selectGNSS_NavMessageTypes(0,QZSS);
            for (int i=0; i<strNavMT.count(); i++){
                int itemTab=0;
                for (itemTab=0; itemTab<ui->tableWidgetNavMessageTypeQZSS->columnCount(); itemTab++){
                    if ( QString::compare(strNavMT[i], ui->tableWidgetNavMessageTypeQZSS->item(0,itemTab)->text(), Qt::CaseInsensitive)==0 && ui->tableWidgetNavMessageTypeQZSS->item(0,itemTab)->background().color().name()==RedColor ) {
                        //Select item to be moved (this is necessary otherwise navMessageTypesItem_doubleClicked function does not move the item)
                        ui->tableWidgetNavMessageTypeQZSS->setCurrentItem(ui->tableWidgetNavMessageTypeQZSS->item(0,itemTab));
                        navMessageTypesItem_doubleClicked(ui->tableWidgetNavMessageTypeQZSS->item(0,itemTab));
                        typeOK++;
                        break;
                    }
                }
                if ( itemTab>=ui->tableWidgetNavMessageTypeQZSS->columnCount() ){
                    *warningString += "Parameter '" + *navMessageTypesCmd + " has unknown type '" + strNavMT[i] +"'. It was skipped.\n";
                }
            }
            if ( typeOK<1 ){
                *warningString += "Parameter '" + *navMessageTypesCmd + " has no available value. It was set as Default.\n";
                this->selectGNSS_NavMessageTypes(1,QZSS);
            }
        }
    } else {
        *warningString += "Parameter '" + *navMessageTypesCmd + "' is not recognized. It was skipped.\n";
    }
}
void gLAB_GUI::selectGNSS_NavMessageTypes(int selectFlag,int iGNSS){
    if (selectFlag>0){
        //GPS
        if (iGNSS==GPS) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeGPS->columnCount();i++){
                ui->tableWidgetNavMessageTypeGPS->item(0,i)->setText(NavMessageTypes[GPS][0][i]);
                ui->tableWidgetNavMessageTypeGPS->item(0,i)->setBackground(gnssSelected);
            }
        }
        //Galileo
        if (iGNSS==Galileo) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeGalileo->columnCount();i++){
                ui->tableWidgetNavMessageTypeGalileo->item(0,i)->setText(NavMessageTypes[Galileo][0][i]);
                ui->tableWidgetNavMessageTypeGalileo->item(0,i)->setBackground(gnssSelected);
            }
        }
        //GLONASS
        if (iGNSS==GLONASS) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeGLONASS->columnCount();i++){
                ui->tableWidgetNavMessageTypeGLONASS->item(0,i)->setText(NavMessageTypes[GLONASS][0][i]);
                ui->tableWidgetNavMessageTypeGLONASS->item(0,i)->setBackground(gnssSelected);
            }
        }
        //GEO
        if (iGNSS==GEO) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeGEO->columnCount();i++){
                ui->tableWidgetNavMessageTypeGEO->item(0,i)->setText(NavMessageTypes[GEO][0][i]);
                ui->tableWidgetNavMessageTypeGEO->item(0,i)->setBackground(gnssSelected);
            }
        }
        //BDS
        if (iGNSS==BDS) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeBDS->columnCount();i++){
                ui->tableWidgetNavMessageTypeBDS->item(0,i)->setText(NavMessageTypes[BDS][0][i]);
                ui->tableWidgetNavMessageTypeBDS->item(0,i)->setBackground(gnssSelected);
            }
        }
        //QZSS
        if (iGNSS==QZSS) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeQZSS->columnCount();i++){
                ui->tableWidgetNavMessageTypeQZSS->item(0,i)->setText(NavMessageTypes[QZSS][0][i]);
                ui->tableWidgetNavMessageTypeQZSS->item(0,i)->setBackground(gnssSelected);
            }
        }
        //IRNSS
        if (iGNSS==IRNSS) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeIRNSS->columnCount();i++){
                ui->tableWidgetNavMessageTypeIRNSS->item(0,i)->setText(NavMessageTypes[IRNSS][0][i]);
                ui->tableWidgetNavMessageTypeIRNSS->item(0,i)->setBackground(gnssSelected);
            }
        }
    } else {
        //GPS
        if (iGNSS==GPS) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeGPS->columnCount();i++){
                ui->tableWidgetNavMessageTypeGPS->item(0,i)->setText(NavMessageTypes[GPS][0][i]);
                ui->tableWidgetNavMessageTypeGPS->item(0,i)->setBackground(gnssUnSelected);
            }
        }
        //Galileo
        if (iGNSS==Galileo) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeGalileo->columnCount();i++){
                ui->tableWidgetNavMessageTypeGalileo->item(0,i)->setText(NavMessageTypes[Galileo][0][i]);
                ui->tableWidgetNavMessageTypeGalileo->item(0,i)->setBackground(gnssUnSelected);
            }
        }
        //GLONASS
        if (iGNSS==GLONASS) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeGLONASS->columnCount();i++){
                ui->tableWidgetNavMessageTypeGLONASS->item(0,i)->setText(NavMessageTypes[GLONASS][0][i]);
                ui->tableWidgetNavMessageTypeGLONASS->item(0,i)->setBackground(gnssUnSelected);
            }
        }
        //GEO
        if (iGNSS==GEO) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeGEO->columnCount();i++){
                ui->tableWidgetNavMessageTypeGEO->item(0,i)->setText(NavMessageTypes[GEO][0][i]);
                ui->tableWidgetNavMessageTypeGEO->item(0,i)->setBackground(gnssUnSelected);
            }
        }
        //BDS
        if (iGNSS==BDS) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeBDS->columnCount();i++){
                ui->tableWidgetNavMessageTypeBDS->item(0,i)->setText(NavMessageTypes[BDS][0][i]);
                ui->tableWidgetNavMessageTypeBDS->item(0,i)->setBackground(gnssUnSelected);
            }
        }
        //QZSS
        if (iGNSS==QZSS) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeQZSS->columnCount();i++){
                ui->tableWidgetNavMessageTypeQZSS->item(0,i)->setText(NavMessageTypes[QZSS][0][i]);
                ui->tableWidgetNavMessageTypeQZSS->item(0,i)->setBackground(gnssUnSelected);
            }
        }
        //IRNSS
        if (iGNSS==IRNSS) {
            for (int i=0; i<ui->tableWidgetNavMessageTypeIRNSS->columnCount();i++){
                ui->tableWidgetNavMessageTypeIRNSS->item(0,i)->setText(NavMessageTypes[IRNSS][0][i]);
                ui->tableWidgetNavMessageTypeIRNSS->item(0,i)->setBackground(gnssUnSelected);
            }
        }
    }
}
void gLAB_GUI::navMessageTypesItem_doubleClicked(QTableWidgetItem *tableItem){
    if (tableItem->text()=="") return;
    QTableWidget *pTable=tableItem->tableWidget();
    int irow=tableItem->row(), icolumn=tableItem->column(), nColumnCount=pTable->columnCount();
    int i,finalPos=icolumn;
    //Nav message types item
    if (irow==0 && icolumn>=0){
        //unselected to selected
        if (tableItem->background().color().name()==RedColor){
            //unselect the "vs" item if the user select one of the others
            for (i=0; i<nColumnCount; i++){
                if ( pTable->item(irow,i)->background().color().name()!=RedColor && pTable->item(irow,i)->text().contains("vs", Qt::CaseSensitive) ){
                    pTable->item(irow,i)->setBackground(gnssUnSelected);
                }
            }
            //unselect all the other if the user select the "vs" one
            if (tableItem->text().contains("vs", Qt::CaseSensitive)) {
                for (i=0; i<nColumnCount; i++){
                    if (pTable->item(irow,i)->background().color().name()!=RedColor){
                        pTable->item(irow,i)->setBackground(gnssUnSelected);
                    }
                }
            }
            //Move it to the left until first green block is found
            for (i=icolumn-1; i>=0; i--){
                if (pTable->item(irow,i)->background().color().name()==RedColor){
                    this->moveNavMessageTypesColumn(pTable,i+1,i,1);
                    finalPos=i;
                } else {
                    pTable->item(irow,i+1)->setBackground(gnssSelected);

                    break;
                }
            }
            if (finalPos==0) {
                pTable->item(irow,0)->setBackground(gnssSelected);
            }
            pTable->clearSelection();
        } else {//selected to unselected
            for (i=nColumnCount-1; i>=0; i--){
                if ((pTable->item(irow,i)->background().color().name()!=RedColor&&pTable->item(irow,i)->text()!="")){
                    this->moveNavMessageTypesColumn(pTable,icolumn,i,1);
                    pTable->item(irow,i)->setBackground(gnssUnSelected);
                    pTable->clearSelection();
                    break;
                }
            }
            pTable->clearSelection();
        }
    }
    pTable->clearSelection();
}
void gLAB_GUI::moveNavMessageTypesColumn(QTableWidget *pTable, int currentColumn, int toColumn, int doubleClickFlag){
    int iRow=pTable->currentRow();
    int nColumnCount = pTable->columnCount();

    if (currentColumn<0 || toColumn <0 || currentColumn>=nColumnCount || toColumn>=nColumnCount) return;
    //return if it's not the reference constellation
    if (iRow!=0) return;
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
void gLAB_GUI::on_pushButtonNavMessageTypesSetDefault_clicked(){
    //GPS
    for (int i=0; i<ui->tableWidgetNavMessageTypeGPS->columnCount();i++){
        ui->tableWidgetNavMessageTypeGPS->item(0,i)->setText(NavMessageTypes[GPS][0][i]);
        ui->tableWidgetNavMessageTypeGPS->item(0,i)->setBackground(gnssSelected);
    }
    //Galileo
    for (int i=0; i<ui->tableWidgetNavMessageTypeGalileo->columnCount();i++){
        ui->tableWidgetNavMessageTypeGalileo->item(0,i)->setText(NavMessageTypes[Galileo][0][i]);
        ui->tableWidgetNavMessageTypeGalileo->item(0,i)->setBackground(gnssSelected);
    }
    //GLONASS
    for (int i=0; i<ui->tableWidgetNavMessageTypeGLONASS->columnCount();i++){
        ui->tableWidgetNavMessageTypeGLONASS->item(0,i)->setText(NavMessageTypes[GLONASS][0][i]);
        ui->tableWidgetNavMessageTypeGLONASS->item(0,i)->setBackground(gnssSelected);
    }
    //GEO
    for (int i=0; i<ui->tableWidgetNavMessageTypeGEO->columnCount();i++){
        ui->tableWidgetNavMessageTypeGEO->item(0,i)->setText(NavMessageTypes[GEO][0][i]);
        ui->tableWidgetNavMessageTypeGEO->item(0,i)->setBackground(gnssSelected);
    }
    //BDS
    for (int i=0; i<ui->tableWidgetNavMessageTypeBDS->columnCount();i++){
        ui->tableWidgetNavMessageTypeBDS->item(0,i)->setText(NavMessageTypes[BDS][0][i]);
        ui->tableWidgetNavMessageTypeBDS->item(0,i)->setBackground(gnssSelected);
    }
    //QZSS
    for (int i=0; i<ui->tableWidgetNavMessageTypeQZSS->columnCount();i++){
        ui->tableWidgetNavMessageTypeQZSS->item(0,i)->setText(NavMessageTypes[QZSS][0][i]);
        ui->tableWidgetNavMessageTypeQZSS->item(0,i)->setBackground(gnssSelected);
    }
    //IRNSS
    for (int i=0; i<ui->tableWidgetNavMessageTypeIRNSS->columnCount();i++){
        ui->tableWidgetNavMessageTypeIRNSS->item(0,i)->setText(NavMessageTypes[IRNSS][0][i]);
        ui->tableWidgetNavMessageTypeIRNSS->item(0,i)->setBackground(gnssSelected);
    }
    ui->tableWidgetNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeIRNSS->setCurrentItem(nullptr);
    ui->lineEditNavFreshTime->setText(DEFAULT_PREFERRED_NAV_TIME);
}
void gLAB_GUI::on_pushButtonNavMessageTypesBoost_clicked(){
    //GPS
    if (ui->tableWidgetNavMessageTypeGPS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetNavMessageTypeGPS,ui->tableWidgetNavMessageTypeGPS->currentColumn(),ui->tableWidgetNavMessageTypeGPS->currentColumn()-1,0);
    }
    //Galileo
    if (ui->tableWidgetNavMessageTypeGalileo->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetNavMessageTypeGalileo,ui->tableWidgetNavMessageTypeGalileo->currentColumn(),ui->tableWidgetNavMessageTypeGalileo->currentColumn()-1,0);
    }
    //GLONASS
    if (ui->tableWidgetNavMessageTypeGLONASS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetNavMessageTypeGLONASS,ui->tableWidgetNavMessageTypeGLONASS->currentColumn(),ui->tableWidgetNavMessageTypeGLONASS->currentColumn()-1,0);
    }
    //GEO
    if (ui->tableWidgetNavMessageTypeGEO->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetNavMessageTypeGEO,ui->tableWidgetNavMessageTypeGEO->currentColumn(),ui->tableWidgetNavMessageTypeGEO->currentColumn()-1,0);
    }
    //BDS
    if (ui->tableWidgetNavMessageTypeBDS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetNavMessageTypeBDS,ui->tableWidgetNavMessageTypeBDS->currentColumn(),ui->tableWidgetNavMessageTypeBDS->currentColumn()-1,0);
    }
    //QZSS
    if (ui->tableWidgetNavMessageTypeQZSS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetNavMessageTypeQZSS,ui->tableWidgetNavMessageTypeQZSS->currentColumn(),ui->tableWidgetNavMessageTypeQZSS->currentColumn()-1,0);
    }
    //IRNSS
    if (ui->tableWidgetNavMessageTypeIRNSS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetNavMessageTypeIRNSS,ui->tableWidgetNavMessageTypeIRNSS->currentColumn(),ui->tableWidgetNavMessageTypeIRNSS->currentColumn()-1,0);
    }
}
void gLAB_GUI::on_pushButtonNavMessageTypesLower_clicked(){
    //GPS
    if (ui->tableWidgetNavMessageTypeGPS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetNavMessageTypeGPS,ui->tableWidgetNavMessageTypeGPS->currentColumn(),ui->tableWidgetNavMessageTypeGPS->currentColumn()+1,0);
    }
    //Galileo
    if (ui->tableWidgetNavMessageTypeGalileo->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetNavMessageTypeGalileo,ui->tableWidgetNavMessageTypeGalileo->currentColumn(),ui->tableWidgetNavMessageTypeGalileo->currentColumn()+1,0);
    }
    //GLONASS
    if (ui->tableWidgetNavMessageTypeGLONASS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetNavMessageTypeGLONASS,ui->tableWidgetNavMessageTypeGLONASS->currentColumn(),ui->tableWidgetNavMessageTypeGLONASS->currentColumn()+1,0);
    }
    //GEO
    if (ui->tableWidgetNavMessageTypeGEO->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetNavMessageTypeGEO,ui->tableWidgetNavMessageTypeGEO->currentColumn(),ui->tableWidgetNavMessageTypeGEO->currentColumn()+1,0);
    }
    //BDS
    if (ui->tableWidgetNavMessageTypeBDS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetNavMessageTypeBDS,ui->tableWidgetNavMessageTypeBDS->currentColumn(),ui->tableWidgetNavMessageTypeBDS->currentColumn()+1,0);
    }
    //QZSS
    if (ui->tableWidgetNavMessageTypeQZSS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetNavMessageTypeQZSS,ui->tableWidgetNavMessageTypeQZSS->currentColumn(),ui->tableWidgetNavMessageTypeQZSS->currentColumn()+1,0);
    }
    //IRNSS
    if (ui->tableWidgetNavMessageTypeIRNSS->currentColumn()>=0){
        this->moveNavMessageTypesColumn(ui->tableWidgetNavMessageTypeIRNSS,ui->tableWidgetNavMessageTypeIRNSS->currentColumn(),ui->tableWidgetNavMessageTypeIRNSS->currentColumn()-1,0);
    }
}
void gLAB_GUI::on_tableWidgetNavMessageTypeGPS_clicked(){
    ui->tableWidgetNavMessageTypeGalileo->clearSelection();
    ui->tableWidgetNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetNavMessageTypeGalileo_clicked(){
    ui->tableWidgetNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetNavMessageTypeGLONASS_clicked(){
    ui->tableWidgetNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetNavMessageTypeGEO_clicked(){
    ui->tableWidgetNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetNavMessageTypeBDS_clicked(){
    ui->tableWidgetNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetNavMessageTypeQZSS_clicked(){
    ui->tableWidgetNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetNavMessageTypeIRNSS_clicked(){
    ui->tableWidgetNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetNavMessageTypeQZSS->setCurrentItem(nullptr);
}

//Function to change comboBoxSBASApplication when switch between SBAS 1F and DFMC
void gLAB_GUI::change_comboBoxSBASApplication(int SBASFlag){
    if (SBASFlag==0 && ui->comboBoxSBASApplication->count()==1){ //if SBAS 1F mode
        ui->comboBoxSBASApplication->addItem("Maritime");
    } else if (SBASFlag==1 && ui->comboBoxSBASApplication->count()==2){
        ui->comboBoxSBASApplication->setCurrentIndex(0);
        ui->comboBoxSBASApplication->removeItem(1);
    }
}
//Function to change to SBAS application
void gLAB_GUI::on_comboBoxSBASApplication_currentIndexChanged(int index) {
    ui->comboBoxSBASApplication->setCurrentIndex(index);
    if(index==0) {
        //Airborne application. Set the defaults that disable all the maritime application changes
        ui->checkBoxDisableMT10->setChecked(false);
        ui->checkBoxDisableMT2728->setChecked(false);
        this->on_groupBoxDisableSBASMessages_clicked(false);
        ui->checkBoxGEOswitching->setChecked(false);
        this->on_checkBoxMaxHDOP_clicked(false);
        this->on_checkBoxMaxPDOP_clicked(false);
        ui->checkBoxHDOPorPDOP->setChecked(false);
        ui->lineEditSlidingWindowSBAS->setText("15");
        ui->lineEditMaritimeWindowSBAS->setText("15");
        ui->lineEditHorizontalAlarmLimitSBAS->setText("40");
        ui->lineEditVerticalAlarmLimitSBAS->setText("50");
    } else {
        //Maritime application (Disable MT10, MT28, enable GEO switching,
        //set HDOP to 4, PDOP to 6 and HDOPorPDOP
        //set Window size to 900 seconds (15 minutes) to both modes
        //set alarm limits to 100000)
        ui->checkBoxDisableMT10->setChecked(true);
        ui->checkBoxDisableMT2728->setChecked(true);
        this->on_groupBoxDisableSBASMessages_clicked(true);
        ui->checkBoxGEOswitching->setChecked(true);
        this->on_checkBoxMaxHDOP_clicked(true);
        this->on_checkBoxMaxPDOP_clicked(true);
        ui->lineEditMaxHDOP->setText("4");
        ui->lineEditMaxPDOP->setText("6");
        ui->checkBoxHDOPorPDOP->setChecked(true);
        ui->lineEditSlidingWindowSBAS->setText("900");
        ui->lineEditMaritimeWindowSBAS->setText("900");
        ui->lineEditHorizontalAlarmLimitSBAS->setText("100000");
        ui->lineEditVerticalAlarmLimitSBAS->setText("100000");
    }
}

//Function to show or hide timeouts according to navigation mode selected
void gLAB_GUI::on_comboBoxSbasNavigationMode_currentIndexChanged(int index) {
    ui->comboBoxSbasNavigationMode->setCurrentIndex(index);
    if (ui->checkBoxNavigationModeSwitching->isChecked()==true) {
        //Navigation mode switch enabled. Show timeouts for PA and NPA
        showHidePAtimeouts(false);
        showHideNPAtimeouts(false);
    } else if (index==0) {
        //PA mode selected. Hide NPA timeouts
        showHidePAtimeouts(false);
        showHideNPAtimeouts(true);
    } else if (index==1) {
        //NPA mode selected. Hide PA timeouts
        showHidePAtimeouts(true);
        showHideNPAtimeouts(false);
    }
}

//Function to show or hide timeouts when navigation mode switching is enabled or disabled
void gLAB_GUI::on_checkBoxNavigationModeSwitching_clicked(bool checked) {
    ui->checkBoxNavigationModeSwitching->setChecked(checked);
    this->on_comboBoxSbasNavigationMode_currentIndexChanged(ui->comboBoxSbasNavigationMode->currentIndex());
}

// Function to show or hide the line edit for SBAS GEO selection
void gLAB_GUI::on_comboBoxGEOselection_currentIndexChanged(int index) {
    ui->comboBoxGEOselection->setCurrentIndex(index);
    if ( index == 3 ) ui->frameGEOselection->setHidden(false);
    else ui->frameGEOselection->setHidden(true);
    if ( index == 1 ) {
        ui->checkBoxAllowMixedGEOdata->setChecked(true);
        this->on_checkBoxSelectBestGEO_clicked(false);
    }
    else ui->checkBoxAllowMixedGEOdata->setChecked(false);
}

// Function to show or hide the content of the SBAS advanced options
void gLAB_GUI::on_groupBoxSbasAdvancedOptions_clicked(bool checked) {
    ui->groupBoxSbasAdvancedOptions->setChecked(checked);
    ui->frameSbasAdvancedOptions->setHidden(!checked);
}

// Function to check checkBox of parse alarm messages correction in SBAS 1F
void gLAB_GUI::on_checkBoxParseAlarmSBAS1F_clicked(bool checked){
    ui->checkBoxParseAlarmSBAS1F->setChecked(checked);
}

// Function to check checkBox of parse alarm messages correction in SBAS DFMC
void gLAB_GUI::on_checkBoxParseAlarmSBASDFMC_clicked(bool checked){
    ui->checkBoxParseAlarmSBASDFMC->setChecked(checked);
    if (!checked) this->on_checkBoxProcessAustralianTestBedMessages_clicked(false);
}

// Function to show or hide the GEO exclusion options
void gLAB_GUI::on_checkBoxGEOexclusion_clicked(bool checked) {
    ui->checkBoxGEOexclusion->setChecked(checked);
    ui->frameGEOexclusion->setHidden(!checked);
}

// Function to show or hide the corresponding line edit
void gLAB_GUI::on_comboBoxGEOexclusion_currentIndexChanged(int index) {
    ui->comboBoxGEOexclusion->setCurrentIndex(index);
    if ( index == 0 ) {
        ui->lineEditGEOexclusion2->setHidden(true);
        ui->lineEditGEOexclusion3->setHidden(true);
    } else if ( index == 1 ) {
        ui->lineEditGEOexclusion2->setHidden(false);
        ui->lineEditGEOexclusion3->setHidden(true);
    } else {
        ui->lineEditGEOexclusion2->setHidden(false);
        ui->lineEditGEOexclusion3->setHidden(false);
    }
}

// Function to disable select best GEO when switch GEO is disabled
void gLAB_GUI::on_checkBoxGEOswitching_clicked(bool checked) {
    ui->checkBoxGEOswitching->setChecked(checked);
    if(checked==false) {
        this->on_checkBoxSelectBestGEO_clicked(false);
    }
}

// Function to enable mixed GEO and set minimum switching time to 0 when select best GEO is enabled
void gLAB_GUI::on_checkBoxSelectBestGEO_clicked(bool checked) {
    ui->checkBoxSelectBestGEO->setChecked(checked);
    if(checked==true) {
        ui->checkBoxGEOswitching->setChecked(true);
        ui->checkBoxAllowMixedGEOdata->setChecked(false);
        ui->lineEditSwitchinCooltime->setText("0");
        if(ui->comboBoxGEOselection->currentIndex()==1) {
            this->on_comboBoxGEOselection_currentIndexChanged(0);
        }
    }
}

// Function to show or hide the the user defined receiver sigmas
void gLAB_GUI::on_groupBoxUserDefinedReceiverSigma_clicked(bool checked) {
    ui->groupBoxUserDefinedReceiverSigma->setChecked(checked);
    ui->frameUserDefinedReceiverSigma->setHidden(!checked);
    if ( checked == true ) {
        ui->comboBoxAirboneReceiverType->setCurrentIndex(0);
        if ( ui->checkBoxUserDefinedReceiverSigmaMultipathModel->isChecked()==true) {
             this->on_groupBoxUserDefinedSbasSigmaMultipath_clicked(true);
        }
    } else {
            if (ui->comboBoxAirboneReceiverType->currentIndex()==0) {
                ui->comboBoxAirboneReceiverType->setCurrentIndex(2);
            }
            if ( ui->checkBoxUserDefinedReceiverSigmaMultipathModel->isChecked()==true) {
                 this->on_groupBoxUserDefinedSbasSigmaMultipath_clicked(false);
            }
            if (ui->groupBoxUserAddedError->isChecked()==false && ui->groupBoxP1P2correction->isChecked()==false && ui->groupBoxUserDefinedSbasSigmaMultipath->isChecked()==false) {
                this->on_groupBoxAuxFiles_clicked(false);
            }
    }
}

//Function to show or hide user defined receiver sigma multipath model
void gLAB_GUI::on_checkBoxUserDefinedReceiverSigmaMultipathModel_clicked(bool checked) {
    ui->checkBoxUserDefinedReceiverSigmaMultipathModel->setChecked(checked);
    if (checked==true) {
        this->on_checkBoxUserDefinedReceiverSigmaMultipath_clicked(false);
        if (ui->groupBoxUserDefinedSbasSigmaMultipath->isChecked()==false) {
            this->on_groupBoxUserDefinedSbasSigmaMultipath_clicked(true);
        }
    } else {
        if (ui->groupBoxUserDefinedSbasSigmaMultipath->isChecked()==true) {
            this->on_groupBoxUserDefinedSbasSigmaMultipath_clicked(false);
        }
    }
}

//Function to show or hide user defined receiver sigma multipath
void gLAB_GUI::on_checkBoxUserDefinedReceiverSigmaMultipath_clicked(bool checked) {
    ui->checkBoxUserDefinedReceiverSigmaMultipath->setChecked(checked);
    ui->frameUserDefinedReceiverSigmaMultipath->setHidden(!checked);
    if (checked==true && ui->checkBoxUserDefinedReceiverSigmaMultipathModel->isChecked()==true ) {
        this->on_checkBoxUserDefinedReceiverSigmaMultipathModel_clicked(false);
    }
    if (ui->groupBoxUserAddedError->isChecked()==false && ui->groupBoxP1P2correction->isChecked()==false && ui->groupBoxUserDefinedSbasSigmaMultipath->isChecked()==false) {
        this->on_groupBoxAuxFiles_clicked(false);
    }
}

//Function to show or hide sigma multipath factor
void gLAB_GUI::on_checkBoxSigmaMultiPathFactor_clicked(bool checked){
    ui->checkBoxSigmaMultiPathFactor->setChecked(checked);
    ui->lineEditSigmaMultiPathFactor->setHidden(!checked);
    ui->labelSigmaMultiPathFactor->setHidden(!checked);
}

//Function to show or hide user defined receiver sigma divergence
void gLAB_GUI::on_checkBoxUserDefinedReceiverSigmaDivergence_clicked(bool checked) {
    ui->checkBoxUserDefinedReceiverSigmaDivergence->setChecked(checked);
    ui->frameUserDefinedReceiverSigmaDivergence->setHidden(!checked);
}

//Function to show or hide user defined receiver sigma noise
void gLAB_GUI::on_checkBoxUserDefinedReceiverSigmaNoise_clicked(bool checked) {
    ui->checkBoxUserDefinedReceiverSigmaNoise->setChecked(checked);
    ui->frameUserDefinedReceiverSigmaNoise->setHidden(!checked);
}

// Function to set the default geo selection based on the SBAS navigation mode
void gLAB_GUI::on_comboBoxAirboneReceiverType_currentIndexChanged(int index) {
    ui->comboBoxAirboneReceiverType->setCurrentIndex(index);
    if ( index == 0 ) this->on_groupBoxUserDefinedReceiverSigma_clicked(true);
    else {
        ui->frameUserDefinedReceiverSigma->setHidden(true);
        ui->comboBoxAirboneReceiverType->setCurrentIndex(index);
        this->on_groupBoxUserDefinedReceiverSigma_clicked(false);
    }
}

// Function to enable/disable comboBox with UDREI threshold when option "Discard Satellites with UDREI equal or greater than:" is clicked
void gLAB_GUI::on_checkBoxDiscardUDREIThreshold_clicked(bool checked) {
    ui->checkBoxDiscardUDREIThreshold->setChecked(checked);
    ui->comboBoxUDREIThresholds->setHidden(!checked);

}
// Function to unselect Return to "Initial GEO" when "After GEO Switch, Maintain the New Selected GEO" is selected
void gLAB_GUI::on_checkBoxMaintainCurrentGEOafterGEOswitch_clicked(bool checked) {
    ui->checkBoxMaintainCurrentGEOafterGEOswitch->setChecked(checked);
    ui->checkBoxReturnToInitialGEO->setChecked(!checked);
}

// Function to unselect Return to "After GEO Switch, Maintain the New Selected GEO" when "Initial GEO is selected
void gLAB_GUI::on_checkBoxReturnToInitialGEO_clicked(bool checked) {
    ui->checkBoxMaintainCurrentGEOafterGEOswitch->setChecked(!checked);
    ui->checkBoxReturnToInitialGEO->setChecked(checked);
}

// Function to show or hide the message time-outs options
void gLAB_GUI::on_groupBoxMessageTimeOuts_clicked(bool checked) {
    ui->groupBoxMessageTimeOuts->setChecked(checked);
    ui->stackedWidgetSBASMessages->setHidden(!checked);
}

// Function to show or hide the k factor values
void gLAB_GUI::on_groupBoxSBASKFactor_clicked(bool checked) {
    ui->groupBoxSBASKFactor->setChecked(checked);
    ui->frameSBASKfactor->setHidden(!checked);
}

// Function to show or hide the disable specific messages options
void gLAB_GUI::on_groupBoxDisableSBASMessages_clicked(bool checked) {
    ui->groupBoxDisableSBASMessages->setChecked(checked);
    ui->frameDisableSBASMessages->setHidden(!checked);
}

// Function to show or hide the disable specific corrections options
void gLAB_GUI::on_groupBoxDisableSpecificCorrections_clicked(bool checked) {
    ui->groupBoxDisableSpecificCorrections->setChecked(checked);
    ui->frameDisableSpecificCorrections->setHidden(!checked);
}

// Function to show or hide the disable specific sigmas options
void gLAB_GUI::on_groupBoxDisableSpecificSigmas_clicked(bool checked) {
    ui->groupBoxDisableSpecificSigmas->setChecked(checked);
    ui->frameDisableSpecificSigmas->setHidden(!checked);
}

// Function to show or hide the set OBAD parameters options
void gLAB_GUI::on_groupBoxSetOBADParameters_clicked(bool checked){
    ui->groupBoxSetOBADParameters->setChecked(checked);
    ui->frameSetOBADParameters->setHidden(!checked);
}

// Function to show or hide the set DFREI corrections options
void gLAB_GUI::on_groupBoxSetDFREICorrections_clicked(bool checked){
    ui->groupBoxSetDFREICorrections->setChecked(checked);
    ui->frameSetDFREICorrections->setHidden(!checked);
}

// Function to show or hide the set specific sigmas options
void gLAB_GUI::on_groupBoxSetSepcificSigmas_clicked(bool checked){
    ui->groupBoxSetSepcificSigmas->setChecked(checked);
    ui->frameSetSepcificSigmas->setHidden(!checked);
}

// Function to show or hide the show old messages options
void gLAB_GUI::on_groupBoxShowOldMessages_clicked(bool checked){
    ui->groupBoxShowOldMessages->setChecked(checked);
    ui->frameShowOldMessages->setHidden(!checked);
}

// Function to set the Niell mapping when Galileo tropospheric correction
void gLAB_GUI::on_comboBoxTropoCorrection_currentIndexChanged(int index) {
    ui->comboBoxTropoCorrection->setCurrentIndex(index);
    if ( index == 2 ) ui->comboBoxTropoCorrectionMapping->setCurrentIndex(1);
}

// Function to disable RRC corrections if PRC corrections are disabled
void gLAB_GUI::on_checkBoxDisableFastCorrections_clicked(bool checked) {
    ui->checkBoxDisableFastCorrections->setChecked(checked);
    ui->checkBoxDisableRRCcorrections->setChecked(checked);
}

// Function to disable RRC simga if PRC sigma is disabled
void gLAB_GUI::on_checkBoxDisableFastCorrectionsSigma_clicked(bool checked) {
    ui->checkBoxDisableFastCorrectionsSigma->setChecked(checked);
    ui->checkBoxDisableRRCsigma->setChecked(checked);
}

//Function to set SBAS OBAD Parameters
void gLAB_GUI::on_checkBoxSetCerOBADParameterMT37_clicked(bool checked){
    ui->checkBoxSetCerOBADParameterMT37->setChecked(checked);
    ui->frameCerOBADParameterMT37->setHidden(!checked);
}
void gLAB_GUI::on_checkBoxSetCcovarianceOBADParameterMT37_clicked(bool checked){
    ui->checkBoxSetCcovarianceOBADParameterMT37->setChecked(checked);
    ui->frameCcovarianceOBADParameterMT37->setHidden(!checked);
}
void gLAB_GUI::on_checkBoxSetIcorrOBADParameterMT37_clicked(bool checked){
    ui->checkBoxSetIcorrOBADParameterMT37->setChecked(checked);
    ui->frameSetIcorrOBADParameterMT37->setHidden(!checked);
}
void gLAB_GUI::on_checkBoxSetIcorrOBADParameterMT37Advanced_clicked(bool checked){
    ui->checkBoxSetIcorrOBADParameterMT37Advanced->setChecked(checked);
    ui->lineEditSetIcorrOBADParameterMT37->setEnabled(!checked);
    ui->pushButtonSetIcorrOBADParameterMT37Advanced->setEnabled(checked);
}
void gLAB_GUI::on_checkBoxSetCcorrOBADParameterMT37_clicked(bool checked){
    ui->checkBoxSetCcorrOBADParameterMT37->setChecked(checked);
    ui->frameSetCcorrOBADParameterMT37->setHidden(!checked);
}
void gLAB_GUI::on_checkBoxSetCcorrOBADParameterMT37Advanced_clicked(bool checked){
    ui->checkBoxSetCcorrOBADParameterMT37Advanced->setChecked(checked);
    ui->lineEditSetCcorrOBADParameterMT37->setEnabled(!checked);
    ui->pushButtonSetCcorrOBADParameterMT37Advanced->setEnabled(checked);
}
void gLAB_GUI::on_checkBoxSetRcorrOBADParameterMT37_clicked(bool checked){
    ui->checkBoxSetRcorrOBADParameterMT37->setChecked(checked);
    ui->frameSetRcorrOBADParameterMT37->setHidden(!checked);
}
void gLAB_GUI::on_checkBoxSetRcorrOBADParameterMT37Advanced_clicked(bool checked){
    ui->checkBoxSetRcorrOBADParameterMT37Advanced->setChecked(checked);
    ui->lineEditSetRcorrOBADParameterMT37->setEnabled(!checked);
    ui->pushButtonSetRcorrOBADParameterMT37Advanced->setEnabled(checked);
}
void gLAB_GUI::on_checkBoxSetOneDFREISigmaConversionValue_clicked(bool checked){
    ui->checkBoxSetOneDFREISigmaConversionValue->setChecked(checked);
    if (checked) this->on_checkBoxSetAllDFREIConversionValues_clicked(false);
    ui->frameSetOneDFREIConversionValue->setHidden(!checked);
}
void gLAB_GUI::on_checkBoxSetAllDFREIConversionValues_clicked(bool checked){
    ui->checkBoxSetAllDFREIConversionValues->setChecked(checked);
    if (checked) this->on_checkBoxSetOneDFREISigmaConversionValue_clicked(false);
    ui->frameSetAllDFREIConversionValues->setHidden(!checked);
}
void gLAB_GUI::on_checkBoxSetDeltaRcorrParameter_clicked(bool checked){
    ui->checkBoxSetDeltaRcorrParameter->setChecked(checked);
    ui->lineEditSetDeltaRcorrParameter->setHidden(!checked);
    ui->labelSetDeltaRcorrParameter->setHidden(!checked);
}
void gLAB_GUI::on_checkBoxSetDeltaDFREFactor_clicked(bool checked){
    ui->checkBoxSetDeltaDFREFactor->setChecked(checked);
    ui->lineEditSetDeltaDFREFactor->setHidden(!checked);
    ui->labelSetDeltaDFREFactor->setHidden(!checked);
}
void gLAB_GUI::on_checkBoxSetUIRESigmaValue_clicked(bool checked){
    ui->checkBoxSetUIRESigmaValue->setChecked(checked);
    ui->lineEditSetUIRESigmaValue->setHidden(!checked);
    ui->labelSetUIRESigmaValueUnit->setHidden(!checked);
}
void gLAB_GUI::on_checkBoxSetTroposphericSigma_clicked(bool checked){
    ui->checkBoxSetTroposphericSigma->setChecked(checked);
    ui->lineEditSetTroposphericSigma->setHidden(!checked);
    ui->labelSetTroposphericSigmaUnit->setHidden(!checked);
}

// Function to open Icorr OBAD configuration window
void gLAB_GUI::on_pushButtonSetIcorrOBADParameterMT37Advanced_clicked(){
    SBASOBADSet->changePage(0);
    SBASOBADSet->setModal(true);
    SBASOBADSet->show();
}
// Function to open Icorr OBAD configuration window
void gLAB_GUI::on_pushButtonSetCcorrOBADParameterMT37Advanced_clicked(){
    SBASOBADSet->changePage(1);
    SBASOBADSet->setModal(true);
    SBASOBADSet->show();
}
// Function to open Icorr OBAD configuration window
void gLAB_GUI::on_pushButtonSetRcorrOBADParameterMT37Advanced_clicked(){
    SBASOBADSet->changePage(2);
    SBASOBADSet->setModal(true);
    SBASOBADSet->show();
}
void gLAB_GUI::on_checkBoxDecodeMT37_clicked(bool checked){
    ui->checkBoxDecodeMT37->setChecked(checked);
    if (!checked) this->on_checkBoxProcessAustralianTestBedMessages_clicked(false);
}
void gLAB_GUI::on_checkBoxDecodeMT3940_clicked(bool checked){
    ui->checkBoxDecodeMT3940->setChecked(checked);
    if (!checked) this->on_checkBoxProcessAustralianTestBedMessages_clicked(false);
}
void gLAB_GUI::on_checkBoxDecodeMT42_clicked(bool checked){
    ui->checkBoxDecodeMT42->setChecked(checked);
    if (!checked) this->on_checkBoxProcessAustralianTestBedMessages_clicked(false);
}
void gLAB_GUI::on_checkBoxDecodeMT47_clicked(bool checked){
    ui->checkBoxDecodeMT47->setChecked(checked);
    if (!checked) this->on_checkBoxProcessAustralianTestBedMessages_clicked(false);
}
// Function to process Australian SBAS DFMC test bed messages
void gLAB_GUI::on_checkBoxProcessAustralianTestBedMessages_clicked(bool checked){
    ui->checkBoxProcessAustralianTestBedMessages->setChecked(checked);
    if (checked){
        ui->checkBoxParseAlarmSBASDFMC->setChecked(checked);
        ui->checkBoxDecodeMT37->setChecked(checked);
        ui->checkBoxDecodeMT3940->setChecked(checked);
        ui->checkBoxDecodeMT42->setChecked(checked);
        ui->checkBoxDecodeMT47->setChecked(checked);
        this->on_groupBoxShowDCBOptions_clicked(checked);
        this->on_groupBoxShowDCBOptionsGPS_clicked(checked);
        ui->comboBoxDCBdfGPS->setCurrentIndex(0);
    } else {
        ui->comboBoxDCBdfGPS->setCurrentIndex(1);
    }
}

//Function to show or hide PA timeouts
void gLAB_GUI::showHidePAtimeouts(bool hide) {
    //SBAS 1F
    ui->label_SBAS_PA_timeouts->setHidden(hide);
    ui->lineEditDoNotUseForSafetyAppPA->setHidden(hide);
    ui->lineEditPRNmaskPA->setHidden(hide);
    ui->lineEditFastCorrectionsPA->setHidden(hide);
    ui->lineEditRRCcorrectionsPA->setHidden(hide);
    ui->lineEditIntegrityInfoPA->setHidden(hide);
    ui->lineEditFastCorrectionDegradationFactorPA->setHidden(hide);
    ui->lineEditGeoNavigationMessagePA->setHidden(hide);
    ui->lineEditDegradationParametersPA->setHidden(hide);
    ui->lineEditNetworkTimeParametersPA->setHidden(hide);
    ui->lineEditGeoSatelliteAlmanacsPA->setHidden(hide);
    ui->lineEditIonosphericGridPointsMaskPA->setHidden(hide);
    ui->lineEditLongTermSatelliteCorrectionsPA->setHidden(hide);
    ui->lineEditIonosphericDelayCorrectionsPA->setHidden(hide);
    ui->lineEditServiceMessagePA->setHidden(hide);
    ui->lineEditClockEphemerisCovarianceMatrixPA->setHidden(hide);
    //SBAS DFMC
    ui->label_SBAS_PA_timeouts_DFMC->setHidden(hide);
    ui->lineEditDoNotUseForSafetyAppPA_DFMC->setHidden(hide);
    ui->lineEditSatMaskPA_DFMC->setHidden(hide);
    ui->lineEditClkCovarianceMatrixPA_DFMC->setHidden(hide);
    ui->lineEditIntegrityPA_DFMC->setHidden(hide);
    ui->lineEditOBADParDFREITablePA_DFMC->setHidden(hide);
    ui->lineEditSatCovarianceMatrixPA_DFMC->setHidden(hide);
    ui->lineEditTimeOffsetsPA_DFMC->setHidden(hide);
    ui->lineEditSBASSatAlmanacsPA_DFMC->setHidden(hide);

}

//Function to show or hide NPA timeouts
void gLAB_GUI::showHideNPAtimeouts(bool hide) {
    //SBAS 1F
    ui->label_SBAS_NPA_timeouts->setHidden(hide);
    ui->lineEditDoNotUseForSafetyAppNPA->setHidden(hide);
    ui->lineEditPRNmaskNPA->setHidden(hide);
    ui->lineEditFastCorrectionsNPA->setHidden(hide);
    ui->lineEditRRCcorrectionsNPA->setHidden(hide);
    ui->lineEditIntegrityInfoNPA->setHidden(hide);
    ui->lineEditFastCorrectionDegradationFactorNPA->setHidden(hide);
    ui->lineEditGeoNavigationMessageNPA->setHidden(hide);
    ui->lineEditDegradationParametersNPA->setHidden(hide);
    ui->lineEditNetworkTimeParametersNPA->setHidden(hide);
    ui->lineEditGeoSatelliteAlmanacsNPA->setHidden(hide);
    ui->lineEditIonosphericGridPointsMaskNPA->setHidden(hide);
    ui->lineEditLongTermSatelliteCorrectionsNPA->setHidden(hide);
    ui->lineEditIonosphericDelayCorrectionsNPA->setHidden(hide);
    ui->lineEditServiceMessageNPA->setHidden(hide);
    ui->lineEditClockEphemerisCovarianceMatrixNPA->setHidden(hide);
    //SBAS DFMC
    ui->label_SBAS_NPA_timeouts_DFMC->setHidden(hide);
    ui->lineEditDoNotUseForSafetyAppNPA_DFMC->setHidden(hide);
    ui->lineEditSatMaskNPA_DFMC->setHidden(hide);
    ui->lineEditClkCovarianceMatrixNPA_DFMC->setHidden(hide);
    ui->lineEditIntegrityNPA_DFMC->setHidden(hide);
    ui->lineEditOBADParDFREITableNPA_DFMC->setHidden(hide);
    ui->lineEditSatCovarianceMatrixNPA_DFMC->setHidden(hide);
    ui->lineEditTimeOffsetsNPA_DFMC->setHidden(hide);
    ui->lineEditSBASSatAlmanacsNPA_DFMC->setHidden(hide);
}

//Function to read message type and timeout value and apply it in the GUI
void gLAB_GUI::readSBASM1FTandTimeout(int MessageType, int timeout, int type, QString option, QString *warningString) {
    //NOTE: type: 0-> Applies to PA messages 1->Applies to NPA messages 2->Applies to PA and NPA messages
    //Fast corrections and RRC corrections timeout are not applied here
    if (MessageType<0 || MessageType>63 || (MessageType>28 && MessageType<62 )) {
        *warningString += "'" + QString("%1").arg(MessageType) + "' is not a valid SBAS message type number for parameter '" + option + "'. It was skipped.\n";
    } else if (MessageType==8 || MessageType==11 ||MessageType==13 ||MessageType==14 ||MessageType==15 ||MessageType==16 ||MessageType==19 ||MessageType==20 || MessageType==21 ||MessageType==22 ||MessageType==23 ) {
        *warningString += "'" + QString("%1").arg(MessageType) + "' is a reserved SBAS message type (in parameter '" + option + "'). It was skipped.\n";
    } else if (MessageType==62 || MessageType==63) {
        *warningString += "'" + QString("%1").arg(MessageType) + "' is a internal test SBAS message type (in parameter '" + option + "'). It was skipped.\n";
    } else if (MessageType==2 || MessageType==3 || MessageType==4 || MessageType==5) {
        if (type==0) {
            *warningString += "Message type '" + QString("%1").arg(MessageType) + "' (in parameter '" + option + "') are fast correction messages. Use parameters '-model:sbastmoutfcpa' and '-model:sbastmoutrrcpa' for these corrections.\n";
        } else if (type==1) {
            *warningString += "Message type '" + QString("%1").arg(MessageType) + "' (in parameter '" + option + "') are fast correction messages. Use parameters '-model:sbastmoutfcnpa' and '-model:sbastmoutrrcnpa' for these corrections.\n";
        } else {
            *warningString += "Message type '" + QString("%1").arg(MessageType) + "' (in parameter '" + option + "') are fast correction messages. Use parameters '-model:sbastmoutfc' and '-model:sbastmoutrrc' for these corrections.\n";
        }
    } else if (MessageType==24) {
        if (type==0) {
            *warningString += "Message type '24' (in parameter '" + option + "') are mixed fast and long term correction messages. Use parameters '-model:sbastmoutfcpa', '-model:sbastmoutrrcpa' and '-model:sbastmoutpa 25' for these corrections.\n";
        } else if (type==1) {
            *warningString += "Message type '24' (in parameter '" + option + "') are mixed fast and long term correction messages. Use parameters '-model:sbastmoutfcnpa', '-model:sbastmoutrrcnpa' and '-model:sbastmoutnpa 25' for these corrections.\n";
        } else {
            *warningString += "Message type '24' (in parameter '" + option + "') are mixed fast and long term correction messages. Use parameters '-model:sbastmoutfc', '-model:sbastmoutrrc' and '-model:sbastmout 25' for these corrections.\n";
        }
    } else if (timeout<0) {
        *warningString += "SBAS message timeout in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
    } else if (timeout>9999999) {
        *warningString += "SBAS message timeout in parameter '" + option + "' must be below 9999999, or 9999999 for no timeout. It was skipped.\n";
    } else {
        //Valid message type and timeout. Apply timeout
        this->on_groupBoxMessageTimeOuts_clicked(true);
        switch (MessageType) {
        case 0:
            if (type==0) {
                ui->lineEditDoNotUseForSafetyAppPA->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditDoNotUseForSafetyAppNPA->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditDoNotUseForSafetyAppPA->setText(QString("%1").arg(timeout));
                ui->lineEditDoNotUseForSafetyAppNPA->setText(QString("%1").arg(timeout));
            }
            break;
        case 1:
            if (type==0) {
                ui->lineEditPRNmaskPA->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditPRNmaskNPA->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditPRNmaskPA->setText(QString("%1").arg(timeout));
                ui->lineEditPRNmaskNPA->setText(QString("%1").arg(timeout));
            }
            break;
        case 6:
            if (type==0) {
                ui->lineEditIntegrityInfoPA->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditIntegrityInfoNPA->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditIntegrityInfoPA->setText(QString("%1").arg(timeout));
                ui->lineEditIntegrityInfoNPA->setText(QString("%1").arg(timeout));
            }
            break;
        case 7:
            if (type==0) {
                ui->lineEditFastCorrectionDegradationFactorPA->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditFastCorrectionDegradationFactorNPA->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditFastCorrectionDegradationFactorPA->setText(QString("%1").arg(timeout));
                ui->lineEditFastCorrectionDegradationFactorNPA->setText(QString("%1").arg(timeout));
            }
            break;
        case 9:
            if (type==0) {
                ui->lineEditGeoNavigationMessagePA->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditGeoNavigationMessageNPA->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditGeoNavigationMessagePA->setText(QString("%1").arg(timeout));
                ui->lineEditGeoNavigationMessageNPA->setText(QString("%1").arg(timeout));
            }
            break;
        case 10:
            if (type==0) {
                ui->lineEditDegradationParametersPA->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditDegradationParametersNPA->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditDegradationParametersPA->setText(QString("%1").arg(timeout));
                ui->lineEditDegradationParametersNPA->setText(QString("%1").arg(timeout));
            }
            break;
        case 12:
            if (type==0) {
                ui->lineEditNetworkTimeParametersPA->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditNetworkTimeParametersNPA->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditNetworkTimeParametersPA->setText(QString("%1").arg(timeout));
                ui->lineEditNetworkTimeParametersNPA->setText(QString("%1").arg(timeout));
            }
            break;
        case 17:
            if (type==0) {
                ui->lineEditGeoSatelliteAlmanacsPA->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditGeoSatelliteAlmanacsNPA->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditGeoSatelliteAlmanacsPA->setText(QString("%1").arg(timeout));
                ui->lineEditGeoSatelliteAlmanacsNPA->setText(QString("%1").arg(timeout));
            }
            break;
        case 18:
            if (type==0) {
                ui->lineEditIonosphericGridPointsMaskPA->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditIonosphericGridPointsMaskNPA->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditIonosphericGridPointsMaskPA->setText(QString("%1").arg(timeout));
                ui->lineEditIonosphericGridPointsMaskNPA->setText(QString("%1").arg(timeout));
            }
            break;
        case 25:
            if (type==0) {
                ui->lineEditLongTermSatelliteCorrectionsPA->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditLongTermSatelliteCorrectionsNPA->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditLongTermSatelliteCorrectionsPA->setText(QString("%1").arg(timeout));
                ui->lineEditLongTermSatelliteCorrectionsNPA->setText(QString("%1").arg(timeout));
            }
            break;
        case 26:
            if (type==0) {
                ui->lineEditIonosphericDelayCorrectionsPA->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditIonosphericDelayCorrectionsNPA->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditIonosphericDelayCorrectionsPA->setText(QString("%1").arg(timeout));
                ui->lineEditIonosphericDelayCorrectionsNPA->setText(QString("%1").arg(timeout));
            }
            break;
        case 27:
            if (type==0) {
                ui->lineEditServiceMessagePA->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditServiceMessageNPA->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditServiceMessagePA->setText(QString("%1").arg(timeout));
                ui->lineEditServiceMessageNPA->setText(QString("%1").arg(timeout));
            }
            break;
        case 28:
            if (type==0) {
                ui->lineEditClockEphemerisCovarianceMatrixPA->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditClockEphemerisCovarianceMatrixNPA->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditClockEphemerisCovarianceMatrixPA->setText(QString("%1").arg(timeout));
                ui->lineEditClockEphemerisCovarianceMatrixNPA->setText(QString("%1").arg(timeout));
            }
            break;
        default:
            break;
        }

    }
}
void gLAB_GUI::readSBASDFMCMTandTimeout(int MessageType, int timeout, int type, QString option, QString *warningString){
    //NOTE: type: 0-> Applies to PA messages 1->Applies to NPA messages 2->Applies to PA and NPA messages
    //Fast corrections and RRC corrections timeout are not applied here
    if (MessageType<0 || MessageType>63 || (MessageType>0 && MessageType<30 )) {
        *warningString += "'" + QString("%1").arg(MessageType) + "' is not a valid SBAS message type number for parameter '" + option + "'. It was skipped.\n";
    } else if (MessageType==8 || MessageType==11 ||MessageType==13 ||MessageType==14 ||MessageType==15 ||MessageType==16 ||MessageType==19 ||MessageType==20 || MessageType==21 ||MessageType==22 ||MessageType==23 ) {
        *warningString += "'" + QString("%1").arg(MessageType) + "' is a reserved SBAS message type (in parameter '" + option + "'). It was skipped.\n";
    } else if (MessageType==62 || MessageType==63) {
        *warningString += "'" + QString("%1").arg(MessageType) + "' is a internal test SBAS message type (in parameter '" + option + "'). It was skipped.\n";
    } else if (MessageType==2 || MessageType==3 || MessageType==4 || MessageType==5) {
        if (type==0) {
            *warningString += "Message type '" + QString("%1").arg(MessageType) + "' (in parameter '" + option + "') are fast correction messages. Use parameters '-model:sbastmoutfcpa' and '-model:sbastmoutrrcpa' for these corrections.\n";
        } else if (type==1) {
            *warningString += "Message type '" + QString("%1").arg(MessageType) + "' (in parameter '" + option + "') are fast correction messages. Use parameters '-model:sbastmoutfcnpa' and '-model:sbastmoutrrcnpa' for these corrections.\n";
        } else {
            *warningString += "Message type '" + QString("%1").arg(MessageType) + "' (in parameter '" + option + "') are fast correction messages. Use parameters '-model:sbastmoutfc' and '-model:sbastmoutrrc' for these corrections.\n";
        }
    } else if (MessageType==24) {
        if (type==0) {
            *warningString += "Message type '24' (in parameter '" + option + "') are mixed fast and long term correction messages. Use parameters '-model:sbastmoutfcpa', '-model:sbastmoutrrcpa' and '-model:sbastmoutpa 25' for these corrections.\n";
        } else if (type==1) {
            *warningString += "Message type '24' (in parameter '" + option + "') are mixed fast and long term correction messages. Use parameters '-model:sbastmoutfcnpa', '-model:sbastmoutrrcnpa' and '-model:sbastmoutnpa 25' for these corrections.\n";
        } else {
            *warningString += "Message type '24' (in parameter '" + option + "') are mixed fast and long term correction messages. Use parameters '-model:sbastmoutfc', '-model:sbastmoutrrc' and '-model:sbastmout 25' for these corrections.\n";
        }
    } else if (timeout<0) {
        *warningString += "SBAS message timeout in parameter '" + option + "' must be equal or greater than 0. It was skipped.\n";
    } else if (timeout>9999999) {
        *warningString += "SBAS message timeout in parameter '" + option + "' must be below 9999999, or 9999999 for no timeout. It was skipped.\n";
    } else {
        //Valid message type and timeout. Apply timeout
        this->on_groupBoxMessageTimeOuts_clicked(true);
        switch (MessageType) {
        case 0:
            if (type==0) {
                ui->lineEditDoNotUseForSafetyAppPA_DFMC->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditDoNotUseForSafetyAppNPA_DFMC->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditDoNotUseForSafetyAppPA_DFMC->setText(QString("%1").arg(timeout));
                ui->lineEditDoNotUseForSafetyAppNPA_DFMC->setText(QString("%1").arg(timeout));
            }
            break;
        case 31:
            if (type==0) {
                ui->lineEditSatMaskPA_DFMC->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditSatMaskNPA_DFMC->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditSatMaskPA_DFMC->setText(QString("%1").arg(timeout));
                ui->lineEditSatMaskNPA_DFMC->setText(QString("%1").arg(timeout));
            }
            break;
        case 32:
            if (type==0) {
                ui->lineEditClkCovarianceMatrixPA_DFMC->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditClkCovarianceMatrixNPA_DFMC->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditClkCovarianceMatrixPA_DFMC->setText(QString("%1").arg(timeout));
                ui->lineEditClkCovarianceMatrixNPA_DFMC->setText(QString("%1").arg(timeout));
            }
            break;
        case 34:
        case 35:
        case 36:
            if (type==0) {
                ui->lineEditIntegrityPA_DFMC->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditIntegrityNPA_DFMC->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditIntegrityPA_DFMC->setText(QString("%1").arg(timeout));
                ui->lineEditIntegrityNPA_DFMC->setText(QString("%1").arg(timeout));
            }
            break;
        case 37:
            if (type==0) {
                ui->lineEditOBADParDFREITablePA_DFMC->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditOBADParDFREITableNPA_DFMC->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditOBADParDFREITablePA_DFMC->setText(QString("%1").arg(timeout));
                ui->lineEditOBADParDFREITableNPA_DFMC->setText(QString("%1").arg(timeout));
            }
            break;
        case 39:
        case 40:
            if (type==0) {
                ui->lineEditSatCovarianceMatrixPA_DFMC->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditSatCovarianceMatrixNPA_DFMC->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditSatCovarianceMatrixPA_DFMC->setText(QString("%1").arg(timeout));
                ui->lineEditSatCovarianceMatrixNPA_DFMC->setText(QString("%1").arg(timeout));
            }
            break;
        case 42:
            if (type==0) {
                ui->lineEditTimeOffsetsPA_DFMC->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditTimeOffsetsNPA_DFMC->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditTimeOffsetsPA_DFMC->setText(QString("%1").arg(timeout));
                ui->lineEditTimeOffsetsNPA_DFMC->setText(QString("%1").arg(timeout));
            }
            break;
        case 47:
            if (type==0) {
                ui->lineEditSBASSatAlmanacsPA_DFMC->setText(QString("%1").arg(timeout));
            } else if (type==1) {
                ui->lineEditSBASSatAlmanacsNPA_DFMC->setText(QString("%1").arg(timeout));
            } else {
                ui->lineEditSBASSatAlmanacsPA_DFMC->setText(QString("%1").arg(timeout));
                ui->lineEditSBASSatAlmanacsNPA_DFMC->setText(QString("%1").arg(timeout));
            }
            break;
        default:
            break;
        }

    }
}

// Function to get the MODELLING options and errors
void gLAB_GUI::getModellingOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString) {

    SBASmaritime=0;

    *warningString = *warningString + ""; //This is to avoid the unused parameter warning
    // Header of the Modelling section
    *saveString += "\n";
    *saveString += "###################################################\n";
    *saveString += "#     MODELLING section\n";
    *saveString += "###################################################\n\n";
    // Preprocess - Satellite Options

    //Unhealthy flag
    if ( ui->checkBoxDiscardUnhealthy->isChecked() == true) {
        //It is enabled on SPP and DGNSS modes by default.
         if (ui->groupBoxSbas->isChecked()==true || WriteAllParameters==1 || (mode==1 && WriteAllParameters==1 ) ) {
             //In PPP, it is not necessary to add this parameter as the '-input:navhealth' is already provided
            *saveString += "-model:satellitehealth\n";
            *runString << "-model:satellitehealth";
         }
    } else if ((mode==0 && ui->groupBoxSbas->isChecked()==false) || ui->groupBoxReferenceStation->isChecked()==true || WriteAllParameters==1  ){
        //It is disabled by default in SBAS and PPP
        *saveString += "--model:satellitehealth\n";
        *runString << "--model:satellitehealth";
    }
    //Marginal flag (only used if discard unhealthy is not enabled
    if ( ui->checkBoxDiscardUnhealthy->isChecked() == false) {
        if ( ui->checkBoxDiscardMarginal->isChecked() == true) {
            //It is enabled on SPP and DGNSS modes by default.
             if ( ui->groupBoxSbas->isChecked()==true  || mode==1 || WriteAllParameters==1 ) {
                 //In PPP, it is not necessary to add this parameter as the '-input:navhealth' is already provided
                *saveString += "--model:allowmarginal\n";
                *runString << "--model:allowmarginal";
             }
        } else if (((mode==0 && ui->groupBoxSbas->isChecked()==false)) || (ui->groupBoxSbas->isChecked()==true && WriteAllParameters==1) || ui->groupBoxReferenceStation->isChecked()==true || WriteAllParameters==1  ){
            //It is disabled by default in SBAS and PPP
            *saveString += "-model:allowmarginal\n";
            *runString << "-model:allowmarginal";
        }
    } else if (WriteAllParameters==1) {
        *saveString += "--model:allowmarginal\n";
        *runString << "--model:allowmarginal";
    }
    // Satellite clock offset correction
    if ( ui->checkBoxSatClockOffset->isChecked() == true ) {
        //It is enabled on all modes by default. No need to set the option
        if (WriteAllParameters==1 ) {
            *saveString += "-model:satclocks\n";
            *runString << "-model:satclocks";
        }
    } else {
        *saveString += "--model:satclocks\n";
        *runString << "--model:satclocks";
    }
    // Check broadcast transmission time
    if ( ui->checkBoxCheckBroadcastTransmissionTime->isChecked() == true ) {
        if (mode==1 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true || WriteAllParameters==1) {
            //BRDC transmission time is disabled by default in all modes except SPP
            *saveString += "-model:brdctranstime\n";
            *runString << "-model:brdctranstime";
        }
    } else {
        if ((mode==0 && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) || WriteAllParameters==1) {
            //BRDC transmission time is disabled by default in all modes except SPP
            *saveString += "--model:brdctranstime\n";
            *runString << "--model:brdctranstime";
        }
    }
    // Satellite movement during signal flight time
    if ( ui->checkBoxSatMovement->isChecked() == true) {
        //It is enabled on all modes by default. No need to set the option
        if (WriteAllParameters==1 ) {
            *saveString += "-model:satmovinflight\n";
            *runString << "-model:satmovinflight";
        }
    } else {
        *saveString += "--model:satmovinflight\n";
        *runString << "--model:satmovinflight";
    }
    // Consider Earth rotation during signal signal flight time
    if ( ui->checkBoxEarthRotation->isChecked() == true ) {
        //It is enabled on all modes by default. No need to set the option
         if (WriteAllParameters==1 ) {
            *saveString += "-model:earthrotinflight\n";
            *runString << "-model:earthrotinflight";
         }
    } else {
        *saveString += "--model:earthrotinflight\n";
        *runString << "--model:earthrotinflight";
    }
    // Satellite mass centre to antenna phase centre correction (in SBAS and DGNSS this is automatically disabled)
    if ( ui->checkBoxSatMassCentre->isChecked() == true ) {
        if (mode==0 || WriteAllParameters==1) {
            //Disabled in all modes except PPP
            *saveString += "-model:satphasecenter\n";
            *runString << "-model:satphasecenter";
        }
        if (ui->checkBoxSatAntex->isChecked()==false || ui->lineEditSatAntex->text()=="") {
            *errorString += "MODEL: Satellite phase center correction enabled, but no ANTEX file is given.\n";
        }
        if ( ui->checkBoxSatelliteAntennaPhaseCentreVariation->isChecked() == true ) {
            if (mode==0|| WriteAllParameters==1) {
                //In PPP is by default enabled
                *saveString += "-model:satphasevar\n";
                *runString << "-model:satphasevar";
            }
        } else {
            if (mode==1|| WriteAllParameters==1) {
                //In PPP is by default enabled
                *saveString += "--model:satphasevar\n";
                *runString << "--model:satphasevar";
            }
        }
    } else {
        if (mode==1|| WriteAllParameters==1) {
            //In PPP is by default enabled
            *saveString += "--model:satphasecenter\n";
            *runString << "--model:satphasecenter";
        }
    }
    // Receiver antenna phase centre correction
    if ( ui->checkBoxAntennaPhase->isChecked() == true ) {
        if ( ui->radioButtonAPCread->isChecked() == true ) {
            if (mode==0 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true || WriteAllParameters==1) {
                //It is disabled in all modes except PPP
                *saveString += "-model:recphasecenter ANTEX\n";
                *runString << "-model:recphasecenter" << "ANTEX";
            }
            if ( ui->checkBoxReceiverAntennaPhaseCentreVariation->isChecked() == true ) {
                if (mode==0 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true || WriteAllParameters==1) {
                    //It is disabled in all modes except PPP
                    *saveString += "-model:recphasevar\n";
                    *runString << "-model:recphasevar";
                }
            } else {
                if ((mode==1  && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) ||WriteAllParameters==1) {
                    //It is disabled in all modes except PPP
                    *saveString += "--model:recphasevar\n";
                    *runString << "--model:recphasevar";
                }
            }
            //Strict radome. Disabled in all modes by default
            if (ui->checkBoxStrictRadome->isChecked()==true) {
                *saveString += "-model:strictradome\n";
                *runString << "-model:strictradome";
            } else if (WriteAllParameters==1) {
                *saveString += "--model:strictradome\n";
                *runString << "--model:strictradome";
            }
        } else if ( ui->radioButtonAPCspecify->isChecked() == true ) {
            APCAdvanced->getgLABOptions(errorString,warningString,saveString,runString);
        }
    } else {
        if ((mode==1  && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) || WriteAllParameters==1) {
            //In PPP is by default enabled
            *saveString += "--model:recphasecenter\n";
            *runString << "--model:recphasecenter";
        }
    }
    // Receiver antenna reference point correction
    if ( ui->checkBoxAntennaReference->isChecked() == true ) {
        if ( ui->radioButtonARPread->isChecked() == true ) {
            if ((mode==0 && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) ||WriteAllParameters==1) {
                //It is enabled in all modes except SPP
                *saveString += "-model:arp RINEX\n";
                *runString << "-model:arp" << "RINEX";
            }
        } else if ( ui->radioButtonARPspecify->isChecked() == true ) {
            //This is not the default of any mode
            if ( ui->lineEditARPnorth->text() == "" || ui->lineEditARPeast->text() == "" || ui->lineEditARPup->text() == "" ) *errorString += "MODEL: Receiver Antenna Reference Point values cannot be empty.\n";
            else {
                *saveString += "-model:arp " + ui->lineEditARPnorth->text() + " " + ui->lineEditARPeast->text() + " " + ui->lineEditARPup->text() + "\n";
                *runString << "-model:arp" << ui->lineEditARPnorth->text() << ui->lineEditARPeast->text() << ui->lineEditARPup->text();
            }
        }
    } else {
        if ((mode==1 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true) || WriteAllParameters==1) {
            //In PPP, SBAS and DGNSS is by default enabled
            *saveString += "--model:arp\n";
            *runString << "--model:arp";
        }
    }
    // Relativistic clock correction (orbit eccentricity)
    if ( ui->checkBoxRelativisticClock->isChecked() == true ) {
        //It is enabled on all modes by default. No need to set the option
        if (WriteAllParameters==1 ) {
            *saveString += "-model:relclock\n";
            *runString << "-model:relclock";
        }
    } else {
        *saveString += "--model:relclock\n";
        *runString << "--model:relclock";
    }
    // Ionospheric correction
    if ( ui->checkBoxIonoCorrection->isChecked() == true ) {
        switch ( ui->comboBoxIonoCorrection->currentIndex() ) {
            case 0 : {
                if ( (mode==1 || ui->groupBoxSbas->isChecked()==true) && ui->groupBoxReferenceStation->isChecked()==false) {
                    //Klobuchar is default in SPP and DGNSS

                    if (mode==1 && ui->groupBoxSbas->isChecked()==false) {
                        //PPP mode, check if a Klobuchar iono was given
                        if ( ui->groupBoxIonoSource->isChecked() == false ||  ui->radioButtonIonoSourceBrdc->isChecked() == false  ) {
                            *errorString += "MODEL: Klobuchar iono selected in PPP mode, but no external navigation file given.\n";
                        }
                    } else {
                        //SBAS mode forced to Klobuchar
                        if ( ui->groupBoxIonoSource->isChecked() == false ||  ui->radioButtonIonoSourceBrdc->isChecked() == false || ui->comboBoxIonoSourceBrdc->currentIndex() != 1 ) {
                            //No external navigation file entered for Klobuchar, set Klobuchar iono then
                            *saveString += "-model:iono Klobuchar\n";
                            *runString << "-model:iono" << "Klobuchar";
                        }
                    }
                } else if (WriteAllParameters==1) {
                    *saveString += "-model:iono Klobuchar\n";
                    *runString << "-model:iono" << "Klobuchar";
                }
                break;
            }
            case 1 : {
                if (WriteAllParameters==1) {
                    *saveString += "-model:iono NeQuick\n";
                    *runString << "-model:iono" << "NeQuick";
                } else if (mode==1 && ui->groupBoxSbas->isChecked()==false) {
                        //PPP mode, check if a NeQuick iono was given
                        if ( ui->groupBoxIonoSource->isChecked() == false ||  ui->radioButtonIonoSourceBrdc->isChecked() == false ) {
                            *errorString += "MODEL: NeQuick iono selected in PPP mode, but no external navigation file given.\n";
                        }
                } else {
                    //Other modes
                    if ( ui->groupBoxIonoSource->isChecked() == false ||  ui->radioButtonIonoSourceBrdc->isChecked() == false || ui->comboBoxIonoSourceBrdc->currentIndex() != 1 ) {
                         //No external navigation file entered for NeQuick, set NeQuick iono then
                        *saveString += "-model:iono NeQuick\n";
                        *runString << "-model:iono" << "NeQuick";
                    }
                }
                break;
            }
            case 2 : {
                if (WriteAllParameters==1) {
                    *saveString += "-model:iono BeiDou\n";
                    *runString << "-model:iono" << "BeiDou";
                } else if (mode==1 && ui->groupBoxSbas->isChecked()==false) {
                        //PPP mode, check if a BeiDou iono was given
                        if ( ui->groupBoxIonoSource->isChecked() == false ||  ui->radioButtonIonoSourceBrdc->isChecked() == false ) {
                            *errorString += "MODEL: BeiDou iono selected in PPP mode, but no external navigation file given.\n";
                        }
                } else {
                    //Other modes
                    if ( ui->groupBoxIonoSource->isChecked() == false ||  ui->radioButtonIonoSourceBrdc->isChecked() == false || ui->comboBoxIonoSourceBrdc->currentIndex() != 1 ) {
                         //No external navigation file entered for BeiDou, set BeiDou iono then
                        *saveString += "-model:iono BeiDou\n";
                        *runString << "-model:iono" << "BeiDou";
                    }
                }
                break;
            }
            case 3 : {
                //IONEX model is automatically set if a IONEX is provided
                 if (WriteAllParameters==1) {
                    *saveString += "-model:iono IONEX\n";
                    *runString << "-model:iono" << "IONEX";
                }
                if (ui->radioButtonIonoSourceIonex->isChecked()==false ) {
                    *errorString += "MODEL: IONEX iono model selected, but no IONEX file provided\n";
                }
                break;
            }
            case 4 : {
                if (ui->groupBoxSbas->isChecked()==false || WriteAllParameters==1) {
                    //Default only in SBAS. This iono model is automatically set if a SBAS iono file is given
                    *saveString += "-model:iono SBAS\n";
                    *runString << "-model:iono" << "SBAS";
                }
                if (ui->groupBoxSbas->isChecked()==false && ui->radioButtonIonoSourceSbas->isChecked()==false ) {
                    *errorString += "MODEL: SBAS iono model selected, but no SBAS file provided\n";
                }
                break;
            }
        }
    } else {
        if ( (mode==0 && ( ui->groupBoxSbas->isChecked()==false || (ui->groupBoxSbas->isChecked()==true && ui->comboBoxSbasInput->currentIndex()==0 ) ) )
              || ui->groupBoxReferenceStation->isChecked()==true || WriteAllParameters==1) {
            //It is enabled by default in all modes except PPP and SBAS DFMC
            *saveString += "--model:iono\n";
            *runString << "--model:iono";
        }
    }
    // Tropospheric correction
    if ( ui->checkBoxTropoCorrection->isChecked() == true ) {
        if ( ui->comboBoxTropoCorrection->currentIndex() == 2 && ui->comboBoxTropoCorrectionMapping->currentIndex() == 0 ) {
            //*errorString += "MODEL: Galileo's tropospheric modelling only accepts Niell mapping, but Simple mapping is selected. Please select Niell mapping.\n";
        } else {
            //Not necessary as tropo model is enabled by default in all modes
            if (WriteAllParameters==1) {
                *saveString += "-model:trop\n";
                *runString << "-model:trop";
            }
            switch ( ui->comboBoxTropoCorrection->currentIndex() ) {
                case 0 : {
                    if ((mode==1  && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) || WriteAllParameters==1) {
                        //UNB3 is the default in all modes except in PPP
                        *saveString += "-model:trop:nominal UNB3\n";
                        *runString << "-model:trop:nominal" << "UNB3";
                    }
                    break;
                }
                case 1 : {
                    if ((mode==0 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true) || WriteAllParameters==1) {
                        //Simple Nominal is enabled by default only in PPP
                        *saveString += "-model:trop:nominal Simple\n";
                        *runString << "-model:trop:nominal" << "Simple";
                    }
                    break;
                }
                /*case 2 : {
                    *saveString += "-model:trop:nominal TropoGal\n";
                    *runString << "-model:trop:nominal" << "TropoGal";
                    break;
                }*/
            }
            switch ( ui->comboBoxTropoCorrectionMapping->currentIndex() ) {
                case 0 : {
                    if ((mode==1  && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) || WriteAllParameters==1) {
                        //Simple Mapping is the default in all modes except in PPP
                        *saveString += "-model:trop:mapping Simple\n";
                        *runString << "-model:trop:mapping" << "Simple";
                    }
                    break;
                }
                case 1 : {
                    if ( (mode==0 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true) || WriteAllParameters==1) {
                        //Niell Mapping is enabled by default only in PPP
                        *saveString += "-model:trop:mapping Niell\n";
                        *runString << "-model:trop:mapping" << "Niell";
                    }
                    break;
                }
            }
        }
    } else {
        //Tropo is enabled by default in all modes
        *saveString += "--model:trop\n";
        *runString << "--model:trop";
    }
    //DCB for all constellations
    //Single Frequency
    int noISCAll=0;
    int noDCBAll=0;
    int noISC=0,RISC=0; //for G,J
    int noDCB=0,RDCB=0; //for G,E,R,C,J,I
    QString DCBopt[6][4],ISCopt[6][4];
    QString DCBAllopt="",ISCAllopt="";

    //GPS
    if (ui->comboBoxDCBsfP1C1GPS->currentIndex()==0){ //p1c1
        noDCB+=1;
        if ( WriteAllParameters==1 ) DCBopt[0][0] = "-model:dcb:sf:gps:p1c1 no";
    } else {
        DCBopt[0][0] = "-model:dcb:sf:gps:p1c1 strict";
    }
    if (ui->comboBoxDCBsfP1P2GPS->currentIndex()==0){ //p1p2
        noDCB+=1;
        if ( (ui->labelCurrentTemplate->text()!="PPP" && ui->labelCurrentTemplate->text()!="SBAS DFMC") || WriteAllParameters==1 ) DCBopt[0][1] = "-model:dcb:sf:gps:p1p2 no";
    } else if (ui->comboBoxDCBsfP1P2GPS->currentIndex()==1){
        RDCB+=1;
        if ( ui->labelCurrentTemplate->text()=="PPP" || WriteAllParameters==1 ) DCBopt[0][1] = "-model:dcb:sf:gps:p1p2 RINEX";
        if ( ui->labelCurrentTemplate->text()=="PPP" ){
            if (ui->stackedWidgetComboBoxDcbSource->currentIndex()==1 && (ui->groupBoxP1P2correction->isChecked() == false || ui->groupBoxAuxFiles->isChecked() == false) ) {
               *errorString += "MODEL: RINEX P1-P2 correction selected, but no RINEX navigation file given.\n";
            } else if (ui->stackedWidgetComboBoxDcbSource->currentIndex()==1 && ui->comboBoxDcbSourcePPP->currentIndex()>0) {
                *errorString += "MODEL: RINEX P1-P2 correction selected, but no RINEX navigation file given.\n";
            } else if (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0 && ui->comboBoxDcbSource->currentIndex()==1 && ui->groupBoxP1P2correction->isChecked() == false) {
                *errorString += "MODEL: RINEX P1-P2 correction selected, but no RINEX navigation file given.\n";
            } else if (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0 && ui->comboBoxDcbSource->currentIndex()>1) {
                *errorString += "MODEL: RINEX P1-P2 correction selected, but no RINEX navigation file given.\n";
            } else if(ui->groupBoxP1P2correction->isChecked() == false || (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0 && ui->comboBoxDcbSource->currentIndex() !=1) ) {
                *errorString += "MODEL: RINEX P1-P2 correction selected, but no RINEX navigation file given.\n";
            }
        }
    } else if (ui->comboBoxDCBsfP1P2GPS->currentIndex()==2){
        DCBopt[0][1] = "-model:dcb:sf:gps:p1p2 DCBFILE";
        if (ui->groupBoxP1P2correction->isChecked() == false || (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0 && ui->comboBoxDcbSource->currentIndex() != 2) || (ui->stackedWidgetComboBoxDcbSource->currentIndex()==1 && ui->comboBoxDcbSourcePPP->currentIndex() != 1)   ) {
            *errorString += "MODEL: DCB P1-P2 correction selected, but no DCB file given.\n";
        }
    } else if (ui->comboBoxDCBsfP1P2GPS->currentIndex()==3){
        DCBopt[0][1] = "-model:dcb:sf:gps:p1p2 IONEX";
        if (ui->groupBoxP1P2correction->isChecked() == false ||  (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0 && ui->comboBoxDcbSource->currentIndex() < 3 ) || (ui->stackedWidgetComboBoxDcbSource->currentIndex()==1 && ui->comboBoxDcbSourcePPP->currentIndex() <2) ) {
            *errorString += "MODEL: IONEX P1-P2 correction selected, but no IONEX P1-P2 correction selected in the INPUT section\n";
        } else if ( (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0 && ui->comboBoxDcbSource->currentIndex() ==3 && ui->radioButtonIonoSourceIonex->isChecked()==false) || (ui->stackedWidgetComboBoxDcbSource->currentIndex()==1 && ui->comboBoxDcbSource->currentIndex() ==2 && ui->radioButtonIonoSourceIonex->isChecked()==false)  ) {
             *errorString += "MODEL: IONEX P1-P2 correction from  ionosphere file selected, but no IONEX file for ionosphere given.\n";
        }
    } else if (ui->comboBoxDCBsfP1P2GPS->currentIndex()==4){
        DCBopt[0][1] = "-model:dcb:sf:gps:p1p2 FPPP";
    }
    if (ui->comboBoxISCsfL1CAGPS->currentIndex()==0){ //l1ca
        noISC+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) ISCopt[0][0] = "-model:dcb:sf:gps:isc:l1ca no";
    } else {
        RISC+=1;
        if ( !(ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) ISCopt[0][0] = "-model:dcb:sf:gps:isc:l1ca RINEX";
    }
    if (ui->comboBoxISCsfL2CGPS->currentIndex()==0){ //l2c
        noISC+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) ISCopt[0][1] = "-model:dcb:sf:gps:isc:l2c no";
    } else {
        RISC+=1;
        if ( !(ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) ISCopt[0][1] = "-model:dcb:sf:gps:isc:l2c RINEX";
    }
    if (ui->comboBoxISCsfL5I5GPS->currentIndex()==0){ //l5i5
        noISC+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) ISCopt[0][2] = "-model:dcb:sf:gps:isc:l5i5 no";
    } else {
        RISC+=1;
        if ( !(ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) ISCopt[0][2] = "-model:dcb:sf:gps:isc:l5i5 RINEX";
    }
    if (ui->comboBoxISCsfL5Q5GPS->currentIndex()==0){ //l5q5
        noISC+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) ISCopt[0][3] = "-model:dcb:sf:gps:isc:l5q5 no";
    } else {
        RISC+=1;
        if ( !(ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) ISCopt[0][3] = "-model:dcb:sf:gps:isc:l5q5 RINEX";
    }
    if (noISC==4){ //ISC
        noISCAll+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) {
            ISCopt[0][0] = "-model:dcb:sf:gps:isc:all no";
            ISCopt[0][1] = ISCopt[0][2] = ISCopt[0][3] = "";
        }
        if ( noDCB==2 ){ //DCB
            noDCBAll+=1;
            if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) {
                ISCopt[0][0] = ISCopt[0][1] = ISCopt[0][2] = ISCopt[0][3] = "";
                DCBopt[0][0] = "-model:dcb:sf:gps:all no";
                DCBopt[0][1] = DCBopt[0][2] = DCBopt[0][3] = "";
            }
        }
    } else if (RISC==4){ //ISC
        if ( ui->labelCurrentTemplate->text()=="PPP" || WriteAllParameters==1 ) {
            ISCopt[0][0] = "-model:dcb:sf:gps:isc:all RINEX";
            ISCopt[0][1] = ISCopt[0][2] = ISCopt[0][3] = "";
        }
        if ( RDCB==1 ){ //DCB
            if ( ui->labelCurrentTemplate->text()=="PPP" || WriteAllParameters==1 ) {
                ISCopt[0][0] = ISCopt[0][1] = ISCopt[0][2] = ISCopt[0][3] = "";
                DCBopt[0][1] = "-model:dcb:sf:gps:all RINEX";
            }
        }
    }

    //Galileo
    noDCB=RDCB=0; //for G,E,R,C,J,I
    if (ui->comboBoxDCBsfE1E5aGalileo->currentIndex()==0){ //e1e5a
        noDCB+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) DCBopt[1][0] = "-model:dcb:sf:gal:e1e5a no";
    } else {
        RDCB+=1;
        if ( !(ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) DCBopt[1][0] = "-model:dcb:sf:gal:e1e5a RINEX";
    }
    if (ui->comboBoxDCBsfE1E5bGalileo->currentIndex()==0){ //e1e5b
        noDCB+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) DCBopt[1][1] = "-model:dcb:sf:gal:e1e5b no";
    } else {
        RDCB+=1;
        if ( !(ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) DCBopt[1][1] = "-model:dcb:sf:gal:e1e5b RINEX";
    }
    if (noDCB==2){
        noDCBAll+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) {
            DCBopt[1][0] = "-model:dcb:sf:gal:all no";
            DCBopt[1][1] = DCBopt[1][2] = DCBopt[1][3] = "";
        }
    } else if (RDCB==2){
        if ( ui->labelCurrentTemplate->text()=="PPP" || WriteAllParameters==1 ) {
            DCBopt[1][0] = "-model:dcb:sf:gal:all RINEX";
            DCBopt[1][1] = DCBopt[1][2] = DCBopt[1][3] = "";
        }
    }

    //GLONASS
    noDCB=RDCB=0; //for G,E,R,C,J,I
    if (ui->comboBoxDCBsfP1P2GLONASS->currentIndex()==0){ //p1p2
        noDCB+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) DCBopt[2][0] = "-model:dcb:sf:glo:p1p2 no";
    } else if (ui->comboBoxDCBsfP1P2GLONASS->currentIndex()==1){
        RDCB+=1;
        if ( !(ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) DCBopt[2][0] = "-model:dcb:sf:glo:p1p2 RINEX";
    } else if (ui->comboBoxDCBsfP1P2GLONASS->currentIndex()==2){
        DCBopt[2][0] = "-model:dcb:sf:glo:p1p2 DCBFILE";
    } else if (ui->comboBoxDCBsfP1P2GLONASS->currentIndex()==3){
        DCBopt[2][0] = "-model:dcb:sf:glo:p1p2 IONEX";
    }
    if (noDCB==1){
        noDCBAll+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) {
            DCBopt[2][0] = "-model:dcb:sf:glo:all no";
            DCBopt[2][1] = DCBopt[2][2] = DCBopt[2][3] = "";
        }
    } else if (RDCB==1){
        if ( ui->labelCurrentTemplate->text()=="PPP" || WriteAllParameters==1 ) {
            DCBopt[2][0] = "-model:dcb:sf:glo:all RINEX";
            DCBopt[2][1] = DCBopt[2][2] = DCBopt[2][3] = "";
        }
    }

    //BDS
    noDCB=RDCB=0; //for G,E,R,C,J,I
    if (ui->comboBoxDCBsfB2B6BDS->currentIndex()==0){ //b2b6
        noDCB+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) DCBopt[3][0] = "-model:dcb:sf:bds:b2b6 no";
    } else {
        RDCB+=1;
        if ( !(ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) DCBopt[3][0] = "-model:dcb:sf:bds:b2b6 RINEX";
    }
    if (ui->comboBoxDCBsfB7B6BDS->currentIndex()==0){ //b7b6
        noDCB+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) DCBopt[3][1] = "-model:dcb:sf:bds:b7b6 no";
    } else {
        RDCB+=1;
        if ( !(ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) DCBopt[3][1] = "-model:dcb:sf:bds:b7b6 RINEX";
    }
    if (ui->comboBoxDCBsfSP3BDS->currentIndex()==0){ //sp3
        noDCB+=1;
        if ( ui->labelCurrentTemplate->text()=="PPP" || WriteAllParameters==1 ) DCBopt[3][2] = "-model:dcb:sf:bds:sp3 no";
    } else {
        RDCB+=1;
        if ( ui->labelCurrentTemplate->text()!="PPP" || WriteAllParameters==1 ) DCBopt[3][2] = "-model:dcb:sf:bds:sp3 RINEX";
    }
    if (noDCB==3){
        noDCBAll+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) {
            DCBopt[3][0] = "-model:dcb:sf:bds:all no";
            DCBopt[3][1] = DCBopt[3][2] = DCBopt[3][3] = "";
        }
    } else if (RDCB==3){
        if ( ui->labelCurrentTemplate->text()=="PPP" || WriteAllParameters==1 ) {
            DCBopt[3][0] = "-model:dcb:sf:bds:all RINEX";
            DCBopt[3][1] = DCBopt[3][2] = DCBopt[3][3] = "";
        }
    }

    //QZSS
    noISC=RISC=0; //for G,J
    noDCB=RDCB=0; //for G,E,R,C,J,I
    if (ui->comboBoxDCBsfC1CQZSS->currentIndex()==0){ //c1c
        noDCB+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) DCBopt[4][0] = "-model:dcb:sf:qzs:c1c no";
    } else {
        RDCB+=1;
        if ( !(ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) DCBopt[4][0] = "-model:dcb:sf:qzs:c1c RINEX";
    }
    if (ui->comboBoxISCsfL2CQZSS->currentIndex()==0){ //l2c
        noISC+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) ISCopt[4][1] = "-model:dcb:sf:qzs:isc:l2c no";
    } else {
        RISC+=1;
        if ( !(ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) ISCopt[4][1] = "-model:dcb:sf:qzs:isc:l2c RINEX";
    }
    if (ui->comboBoxISCsfL5I5QZSS->currentIndex()==0){ //l5i5
        noISC+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) ISCopt[4][2] = "-model:dcb:sf:qzs:isc:l5i5 no";
    } else {
        RISC+=1;
        if ( !(ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) ISCopt[4][2] = "-model:dcb:sf:qzs:isc:l5i5 RINEX";
    }
    if (ui->comboBoxISCsfL5Q5QZSS->currentIndex()==0){ //l5q5
        noISC+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) ISCopt[4][3] = "-model:dcb:sf:qzs:isc:l5q5 no";
    } else {
        RISC+=1;
        if ( !(ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) ISCopt[4][3] = "-model:dcb:sf:qzs:isc:l5q5 RINEX";
    }
    if (noISC==3){ //ISC
        noISCAll+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) {
            ISCopt[4][0] = "-model:dcb:sf:qzs:isc:all no";
            ISCopt[4][1] = ISCopt[4][2] = ISCopt[4][3] = "";
        }
        if ( noDCB==1 ){ //DCB
            noDCBAll+=1;
            if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) {
                ISCopt[4][0] = ISCopt[4][1] = ISCopt[4][2] = ISCopt[4][3] = "";
                DCBopt[4][0] = "-model:dcb:sf:qzs:all no";
            }
        }
    } else if (RISC==3){ //ISC
        if ( ui->labelCurrentTemplate->text()=="PPP" || WriteAllParameters==1 ) {
            ISCopt[4][0] = "-model:dcb:sf:qzs:isc:all RINEX";
            ISCopt[4][1] = ISCopt[4][2] = ISCopt[4][3] = "";
        }
        if ( RDCB==1 ){ //DCB
            if ( ui->labelCurrentTemplate->text()=="PPP" || WriteAllParameters==1 ) {
                ISCopt[4][0] = ISCopt[4][1] = ISCopt[4][2] = ISCopt[4][3] = "";
                DCBopt[4][0] = "-model:dcb:sf:qzs:all RINEX";
            }
        }
    }

    //IRNSS
    noDCB=RDCB=0; //for G,E,R,C,J,I
    if (ui->comboBoxDCBsfC9C5IRNSS->currentIndex()==0){ //c9c5
        noDCB+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) DCBopt[5][1] = "-model:dcb:sf:irn:c9c5 no";
    } else {
        RDCB+=1;
        if ( !(ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) DCBopt[5][1] = "-model:dcb:sf:irn:c9c5 RINEX";
    }
    if (noDCB==1){
        noDCBAll+=1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="DGNSS") || WriteAllParameters==1 ) {
            DCBopt[5][0] = "-model:dcb:sf:irn:all no";
            DCBopt[5][1] = DCBopt[5][2] = DCBopt[5][3] = "";
        }
    } else if (RDCB==1){
        if ( ui->labelCurrentTemplate->text()=="PPP" || WriteAllParameters==1 ) {
            DCBopt[5][0] = "-model:dcb:sf:irn:all RINEX";
            DCBopt[5][1] = DCBopt[5][2] = DCBopt[5][3] = "";
        }
    }

    if (noDCBAll==6){ //ISC for G,J
        if ( ui->labelCurrentTemplate->text()=="SPP" || WriteAllParameters==1 ) {
            *saveString += "--model:dcb:sf:all\n";
            *runString << "--model:dcb:sf:all";
            for (int i=0; i<6; i++) {
                for (int j=0; j<4; j++){
                    ISCopt[i][j]=DCBopt[i][j]="";
                }
            }
        }
    } else if (noISCAll==2) {
        if ( ui->labelCurrentTemplate->text()=="SPP" || WriteAllParameters==1 ) {
            *saveString += "--model:dcb:sf:isc:all\n";
            *runString << "--model:dcb:sf:isc:all";
            for (int i=0; i<6; i++) {
                for (int j=0; j<4; j++){
                    ISCopt[i][j]="";
                }
            }
        }
    }
    for (int i=0; i<6; i++) {
        for (int j=0; j<4; j++) {
            if (DCBopt[i][j].size()>9) {
                *saveString += DCBopt[i][j] + "\n";
                QStringList tmpString = DCBopt[i][j].split(QRegularExpression("\\s+"));
                for(int k=0;k<tmpString.size();k++) {
                    *runString << tmpString[k];
                }
            }
        }
        for (int j=0; j<4; j++) {
            if (ISCopt[i][j].size()>9) {
                *saveString += ISCopt[i][j] + "\n";
                QStringList tmpString = ISCopt[i][j].split(QRegularExpression("\\s+"));
                for(int k=0;k<tmpString.size();k++) {
                    *runString << tmpString[k];
                }
            }
        }
    }

    //Dual Frequency (ionosphere combination)
    int noDF=0;
    QString DFopt[3]={""};
    QString DCBdfGPS=""; //String for "-model:dcb:df:gps RINEX" when SBAS DFMC and Australian messages enabled, so it is applied after Australian messages option.
    //GPS
    if ( ui->comboBoxDCBdfGPS->currentIndex()==0 ){
        noDF += 1;
        if ( (ui->labelCurrentTemplate->text()=="SPP" || (ui->labelCurrentTemplate->text()=="SBAS DFMC" && ui->checkBoxProcessAustralianTestBedMessages->isChecked()==false) )  || WriteAllParameters==1 ) {
            DFopt[0] = "-model:dcb:df:gps no";
        }
    } else {
        if ( (!(ui->labelCurrentTemplate->text()=="SPP" || ui->labelCurrentTemplate->text()=="SBAS DFMC" )
              || (ui->labelCurrentTemplate->text()=="SBAS DFMC" && ui->checkBoxProcessAustralianTestBedMessages->isChecked()==true)  ) || WriteAllParameters==1 ) {

            if (ui->labelCurrentTemplate->text()=="SBAS DFMC" && ui->checkBoxProcessAustralianTestBedMessages->isChecked()==true) {
                //To be added after Australian messages option
                DCBdfGPS = "-model:dcb:df:gps RINEX";
            } else {
                DFopt[0] = "-model:dcb:df:gps RINEX";
            }
        }
    }
    //BDS
    if ( ui->comboBoxDCBdfBDS->currentIndex()==0 ){
        noDF += 1;
        if ( ui->labelCurrentTemplate->text()=="SPP" || WriteAllParameters==1 ) DFopt[1] = "-model:dcb:df:bds no";
    } else {
        if ( ui->labelCurrentTemplate->text()!="SPP" || WriteAllParameters==1 ) DFopt[1] = "-model:dcb:df:bds RINEX";
    }
    //QZSS
    if ( ui->comboBoxDCBdfQZSS->currentIndex()==0 ){
        noDF += 1;
        if ( ui->labelCurrentTemplate->text()=="SPP" || WriteAllParameters==1 ) DFopt[2] = "-model:dcb:df:qzs no";
    } else {
        if ( ui->labelCurrentTemplate->text()!="SPP" || WriteAllParameters==1 ) DFopt[2] = "-model:dcb:df:qzs RINEX";
    }
    //All
    if ( noDF==3 && ( (!(ui->labelCurrentTemplate->text()=="PPP" || ui->labelCurrentTemplate->text()=="DGNSS" || ui->labelCurrentTemplate->text()=="SBAS 1F")
                       && (ui->labelCurrentTemplate->text()=="SBAS DFMC" && ui->checkBoxProcessAustralianTestBedMessages->isChecked()==false) ) || WriteAllParameters==1)) {
        *saveString += "--model:dcb:df:all\n";
        *runString << "--model:dcb:df:all";
    } else {
        for (int i=0; i<3; i++){
            if (DFopt[i].size()>9){
                *saveString += DFopt[i] + "\n";
                QStringList tmpString = DFopt[i].split(QRegularExpression("\\s+"));
                for(int k=0;k<tmpString.size();k++) {
                    *runString << tmpString[k];
                }
            }
        }
    }


    //Navigation message types
    if (ui->radioButtonOrbitBrdc->isChecked()){
        this->userNavMessageTypes_2_Command(saveString,runString,errorString);
        if (ui->groupBoxSbas->isChecked()==false) {
            if ( ui->lineEditNavFreshTime->text() == "" ) {
                *errorString += "MODEL: Preferred age time in [Broadcast Navigation Message Types] cannot be empty.\n";
            } else if (ui->lineEditNavFreshTime->text().toInt() <= 0. ) {
                *errorString += "MODEL: Preferred age time in [Broadcast Navigation Message Types] must be greater than 0.\n";
            } else if (ui->lineEditNavFreshTime->text().toInt() != 3600 || WriteAllParameters==1 ) {
                *saveString += "-model:brdcpreferagetime " + ui->lineEditNavFreshTime->text() + "\n";
                *runString << "-model:brdcpreferagetime" << ui->lineEditNavFreshTime->text();
            }
        }
    }

    //Preferred age time for navigation messages (it does not apply on SBAS modes)
    if (ui->groupBoxSbas->isChecked()==false) {
        if (ui->lineEditNavFreshTime->text()=="") {
            *errorString += "MODEL: Preferred age time cannot be empty.\n";
        } else if (ui->lineEditNavFreshTime->text().toInt() == 0 ) {
            *errorString += "MODEL: Preferred age time cannot 0.\n";
        } else if (ui->lineEditNavFreshTime->text().toInt() != 3600 || WriteAllParameters==1 ) {
            //Default is 3600 in all modes
            *saveString += "-model:brdcpreferagetime " + ui->lineEditNavFreshTime->text() + "\n";
            *runString << "-model:brdcpreferagetime" << ui->lineEditNavFreshTime->text();
        }
    }

    // Wind up
    if ( ui->checkBoxWindUp->isChecked() == true ) {
        if ((mode==0 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true) || WriteAllParameters==1) {
            //Enabled only by default in PPP
            *saveString += "-model:windup\n";
            *runString << "-model:windup";
        }
    } else {
        if  ((mode==1  && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) || WriteAllParameters==1) {
             //Enabled only by default in PPP
            *saveString += "--model:windup\n";
            *runString << "--model:windup";
        }
    }
    // Solid tides
    if ( ui->checkBoxTides->isChecked() == true ) {
        if ((mode==0 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true) || WriteAllParameters==1) {
            //Enabled only by default in PPP
            *saveString += "-model:solidtides\n";
            *runString << "-model:solidtides";
        }
    } else {
        if ( (mode==1  && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) || WriteAllParameters==1) {
             //Enabled only by default in PPP
            *saveString += "--model:solidtides\n";
            *runString << "--model:solidtides";
        }
    }
    // Relativistic path range correction
    if ( ui->checkBoxRelativisticPath->isChecked() == true ) {
        if (mode==0 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true || WriteAllParameters==1) {
            //Enabled only by default in PPP
            *saveString += "-model:relpath\n";
            *runString << "-model:relpath";
        }
    } else {
        if ((mode==1  && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) || WriteAllParameters==1) {
             //Enabled only by default in PPP
            *saveString += "--model:relpath\n";
            *runString << "--model:relpath";
        }
    }
    // Precise products interpolation data (only for PPP)
    if ( ui->radioButtonOrbitPrecise1file->isChecked() == true || ui->radioButtonOrbitPrecise2files->isChecked() == true ) {
        if ( ui->lineEditOrbitInterpolationDegree->text() == "" ) {
            *errorString += "MODEL: Orbit interpolation degree cannot be empty.\n";
        } else if (ui->lineEditOrbitInterpolationDegree->text().toInt() == 0 ) {
            *errorString += "MODEL: Orbit interpolation degree cannot 0.\n";
        } else if ( ui->lineEditOrbitConsecutiveGaps->text() == "" ) {
            *errorString += "MODEL: Number of consecutive gaps in orbit interpolation cannot be empty.\n";
        } else if ( ui->lineEditOrbitMaxGaps->text() == "" ) {
            *errorString += "MODEL: Number of maximum gaps in orbit interpolation cannot be empty.\n";
        } else if ( ui->lineEditClockInterpolationDegree->text() == "" ) {
            *errorString += "MODEL: Clock interpolation degree cannot be empty.\n";
        } else if ( ui->lineEditClockConsecutiveGaps->text() == "" ) {
            *errorString += "MODEL: Number of consecutive gaps in clock interpolation cannot be empty.\n";
        } else if ( ui->lineEditClockMaxGaps->text() == "" ) {
            *errorString += "MODEL: Number of maximum gaps in clock interpolation cannot be empty.\n";
        } else if ( ui->lineEditOrbitMaxGaps->text().toInt()< ui->lineEditOrbitConsecutiveGaps->text().toInt()) {
            *errorString += "MODEL: Number of maximum gaps in orbit interpolation must be equal or greater than then number of consecutive gaps.\n";
        } else if ( ui->lineEditClockMaxGaps->text().toInt()< ui->lineEditClockConsecutiveGaps->text().toInt()) {
            *errorString += "MODEL: Number of maximum gaps in clock interpolation must be equal or greater than then number of consecutive gaps.\n";
        } else {
            if ( ui->lineEditOrbitInterpolationDegree->text().toInt() !=10  || WriteAllParameters==1) {
                *saveString += "-model:orbit:deg " + ui->lineEditOrbitInterpolationDegree->text() + "\n";
                *runString << "-model:orbit:deg" << ui->lineEditOrbitInterpolationDegree->text();
            }
            if (ui->lineEditOrbitConsecutiveGaps->text().toInt()!=8  || WriteAllParameters==1) {
                *saveString += "-model:orbmaxgaps " + ui->lineEditOrbitConsecutiveGaps->text() + "\n";
                *runString << "-model:orbmaxgaps" << ui->lineEditOrbitConsecutiveGaps->text();
            }
            if (ui->lineEditOrbitMaxGaps->text().toInt() != 16  || WriteAllParameters==1) {
                *saveString += "-model:orbtotmaxgaps " + ui->lineEditOrbitMaxGaps->text() + "\n";
                *runString << "-model:orbtotmaxgaps" << ui->lineEditOrbitMaxGaps->text();
            }
            if ( ui->lineEditClockInterpolationDegree->text().toInt()!=1  || WriteAllParameters==1) {
                *saveString += "-model:clock:deg " + ui->lineEditClockInterpolationDegree->text() + "\n";
                *runString << "-model:clock:deg" << ui->lineEditClockInterpolationDegree->text();
            }
            if (ui->lineEditClockConsecutiveGaps->text().toInt()!=2  || WriteAllParameters==1) {
                *saveString += "-model:clkmaxgaps " + ui->lineEditClockConsecutiveGaps->text() + "\n";
                *runString << "-model:clkmaxgaps" << ui->lineEditClockConsecutiveGaps->text();
            }
            if (ui->lineEditClockMaxGaps->text().toInt()!=4  || WriteAllParameters==1) {
                *saveString += "-model:clktotmaxgaps " + ui->lineEditClockMaxGaps->text() + "\n";
                *runString << "-model:clktotmaxgaps" << ui->lineEditClockMaxGaps->text();
            }
        }
        //Current or Previous sample interpolation option for concatenated orbit files
        if (ui->radioButtonOrbitCurrentDay->isChecked()==true) {
            //This is not the default option
            *saveString += "-model:orbprevsample\n";
            *runString << "-model:orbprevsample";
        } else if (ui->radioButtonOrbitCurrentDay->isChecked()==false) {
            if (WriteAllParameters==1 ) {
                *saveString += "--model:orbprevsample\n";
                *runString << "--model:orbprevsample";
            }
        }
        if (ui->radioButtonClockCurrentDay->isChecked()==true) {
            //This is not the default option
            *saveString += "-model:clkprevsample\n";
            *runString << "-model:clkprevsample";
        } else if (ui->radioButtonClockCurrentDay->isChecked()==false) {
            if (WriteAllParameters==1 ) {
            //This is not the default option
                *saveString += "--model:clkprevsample\n";
                *runString << "--model:clkprevsample";
            }
        }
    }
    // SBAS Options
    if ( ui->labelCurrentTemplate->text() == "SBAS 1F" ||  ui->groupBoxSbas->isChecked()==true ) {
        //Maritime mode
        if (ui->comboBoxSBASApplication->currentIndex()==1) {
            //Set shortcut parameter "-maritime" if all the options for maritime mode are set
            if ( ui->checkBoxDisableMT10->isChecked()==true && ui->checkBoxDisableMT2728->isChecked()==true && ui->checkBoxGEOswitching->isChecked()==true
                 && ui->checkBoxMaxHDOP->isChecked()==true && ui->lineEditMaxHDOP->text().toDouble()==4.
                 && ui->checkBoxMaxPDOP->isChecked()==true && ui->lineEditMaxPDOP->text().toDouble()==6.
                 && ui->checkBoxHDOPorPDOP->isChecked()==true
                 && ui->lineEditHorizontalAlarmLimitSBAS->text().toDouble()==100000. && ui->lineEditVerticalAlarmLimitSBAS->text().toDouble()==100000.
                 && ui->lineEditSlidingWindowSBAS->text().toInt()==900 && ui->lineEditMaritimeWindowSBAS->text().toInt()==900 ) {
                if (WriteAllParameters==0) {
                    SBASmaritime=1;
                }
                *saveString += "-model:sbasmaritime\n";
                *runString << "-model:sbasmaritime";
            }
            //If all maritime options are not set, they will be set later
        }
        // Navigation mode
        if ( ui->comboBoxSbasNavigationMode->currentIndex() == 0 ) {
            //This is the default navigation mode. No need to set the option
            if (WriteAllParameters==1 ) {
                *saveString += "-model:sbasmode PA\n";
                *runString << "-model:sbasmode" << "PA";
            }
        } else if ( ui->comboBoxSbasNavigationMode->currentIndex() == 1 ) {
            *saveString += "-model:sbasmode NPA\n";
            *runString << "-model:sbasmode" << "NPA";
        }
        // Allow mixed GEO data
        if ( ui->checkBoxAllowMixedGEOdata->isChecked() == true ) {
            *saveString += "-model:mixedgeo\n";
            *runString << "-model:mixedgeo";
        } else if (WriteAllParameters==1){
            //Mixed GEO are disabled by default. No need to set the option
            *saveString += "--model:mixedgeo\n";
            *runString << "--model:mixedgeo";
        }
        // GEO switching
        if (SBASmaritime==0) {
            if ( ui->checkBoxGEOswitching->isChecked() == true ) {
                if (ui->checkBoxSelectBestGEO->isChecked()==false||WriteAllParameters==1) {
                    //If Select Best GEO option is enabled, this automatically enables GEO switching
                    *saveString += "-model:geoswitch\n";
                    *runString << "-model:geoswitch";
                }
            } else if (WriteAllParameters==1){
                //GEO switching is disabled by default. No need to set the option
                *saveString += "--model:geoswitch\n";
                *runString << "--model:geoswitch";
            }
        }
        //Select Best GEO
        if (ui->checkBoxSelectBestGEO->isChecked()==true) {
            if (ui->lineEditSwitchinCooltime->text().toInt()!=0) {
                //Switching cooltime must be 0 seconds
                *errorString += "MODEL: 'Switching Cooltime' must have a value of 0 if option 'Select Best GEO' is set in [SBAS Options].\n";
            } else {
                *saveString += "-model:selectbestgeo\n";
                *runString << "-model:selectbestgeo";
            }
        } else if (WriteAllParameters==1) {
            //Select Best GEO is disabled by default in all modes
            *saveString += "--model:selectbestgeo\n";
            *runString << "--model:selectbestgeo";
        }
        // Navigation mode switching
        if ( ui->checkBoxNavigationModeSwitching->isChecked() == true ) {
            *saveString += "-model:sbasmodeswitch\n";
            *runString << "-model:sbasmodeswitch";
        } else if (WriteAllParameters==1){
             //Mode switching is disabled by default. No need to set the option
            *saveString += "--model:sbasmodeswitch\n";
            *runString << "--model:sbasmodeswitch";
        }
        // Airbone Receiver type (Class 2,3,4 is the default SBAS receiver model)
        if ( ui->comboBoxAirboneReceiverType->currentIndex() < 2 ) {
            //If user defined model selected, check if any specific option for user receiver is enabled. If any is enabled, is not necessary to pas the parameter of user defined sbas receiver
            if ( ui->comboBoxAirboneReceiverType->currentIndex() == 0) {
                if (ui->checkBoxUserDefinedReceiverSigmaMultipathModel->isChecked()==false && ui->checkBoxUserDefinedReceiverSigmaMultipath->isChecked()==false
                        && ui->checkBoxUserDefinedReceiverSigmaDivergence->isChecked()==false && ui->checkBoxUserDefinedReceiverSigmaNoise->isChecked()==false) {
                    *saveString += "-model:sbasreceiver " + QString::number(ui->comboBoxAirboneReceiverType->currentIndex()) + "\n";
                    *runString << "-model:sbasreceiver" <<  QString::number(ui->comboBoxAirboneReceiverType->currentIndex());
                }
            } else {
                //Class 1 receiver type
                *saveString += "-model:sbasreceiver " + QString::number(ui->comboBoxAirboneReceiverType->currentIndex()) + "\n";
                *runString << "-model:sbasreceiver" <<  QString::number(ui->comboBoxAirboneReceiverType->currentIndex());
            }
        } else if (ui->comboBoxAirboneReceiverType->currentIndex()==2) {
            if (WriteAllParameters==1) {
                *saveString += "-model:sbasreceiver " + QString::number(ui->comboBoxAirboneReceiverType->currentIndex()) + "\n";
                *runString << "-model:sbasreceiver" <<  QString::number(ui->comboBoxAirboneReceiverType->currentIndex());
            }
        }
        // Fixed sigma multipath
        if ( ui->comboBoxAirboneReceiverType->currentIndex() == 0 ) {
            if (ui->checkBoxUserDefinedReceiverSigmaMultipathModel->isChecked()==true) {
                 //No option needed here, as with the opton -input:sigmpath this option is set
           } else if (ui->checkBoxUserDefinedReceiverSigmaMultipath->isChecked()==true) {
                if ( ui->lineEditSbasSigmaMultipathA->text() == "" || ui->lineEditSbasSigmaMultipathB->text() == "" || ui->lineEditSbasSigmaMultipathC->text() == "" ) {
                    // Parameters a, b and c
                    *errorString += "MODEL: Parameters a, b and c for Fixed sigma multipath in [SBAS Options] cannot be empty.\n";
                } else if (ui->lineEditSbasSigmaMultipathC->text().toDouble()==0.) {
                    *errorString += "MODEL: Parameter c for Fixed sigma multipath in [SBAS Options] cannot be 0.\n";
                } else {
                    *saveString += "-model:sigmpath "+ ui->lineEditSbasSigmaMultipathA->text() + " " + ui->lineEditSbasSigmaMultipathB->text()
                        + " " + ui->lineEditSbasSigmaMultipathC->text() + "\n";
                    *runString << "-model:sigmpath" << ui->lineEditSbasSigmaMultipathA->text() << ui->lineEditSbasSigmaMultipathB->text() << ui->lineEditSbasSigmaMultipathC->text();
                }
            }
            // sigma multipath factor
            if ( ui->checkBoxSigmaMultiPathFactor->isChecked()==true && (ui->lineEditSigmaMultiPathFactor->text()!="2.59" || WriteAllParameters==1) ){
                *saveString += "-model:sbasdfmc:sigmpathfactor " + ui->lineEditSigmaMultiPathFactor->text() + "\n";
                *runString << "-model:sbasdfmc:sigmpathfactor" << ui->lineEditSigmaMultiPathFactor->text();
            }
            // Sigma divergence
            if (ui->checkBoxUserDefinedReceiverSigmaDivergence->isChecked()==true) {
                if ( ui->lineEditSbasSigmaDivergence->text() == "" ) {
                    *errorString += "MODEL: Sigma divergence for Fixed sigma multipath in [SBAS Options] cannot be empty.\n";
                } else {
                    *saveString += "-model:sigdiv "+ ui->lineEditSbasSigmaDivergence->text() + "\n";
                    *runString << "-model:sigdiv" << ui->lineEditSbasSigmaDivergence->text();
                }
            }
            // Sigma noise
            if (ui->checkBoxUserDefinedReceiverSigmaNoise->isChecked()==true) {
                if ( ui->lineEditSbasSigmaNoise->text() == "" ) {
                    *errorString += "MODEL: Sigma noise for Fixed sigma multipath in [SBAS Options] cannot be empty.\n";
                } else {
                    *saveString += "-model:signoise "+ ui->lineEditSbasSigmaNoise->text() + "\n";
                    *runString << "-model:signoise" << ui->lineEditSbasSigmaNoise->text();
                }
            }
        }

        // Time-outs for SBAS 1F
        // PRN mask assignments
        if ( ui->lineEditPRNmaskPA->text() == "" || ui->lineEditPRNmaskNPA->text() == "" ) {
            *errorString += "MODEL: PRN mask assignment in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditPRNmaskPA->text().toInt() != 600 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutpa 1 " + ui->lineEditPRNmaskPA->text() + "\n";
                *runString << "-model:sbastmoutpa" << "1" << ui->lineEditPRNmaskPA->text();
            }
            // NPA
            if ( ui->lineEditPRNmaskNPA->text().toInt() != 600  || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutnpa 1 " + ui->lineEditPRNmaskNPA->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "1" << ui->lineEditPRNmaskNPA->text();
            }
        }
        // Fast corrections PA & NPA
        if ( ui->lineEditFastCorrectionsPA->text() != "" && ui->lineEditFastCorrectionsPA->text() == ui->lineEditFastCorrectionsNPA->text() ) {
            *saveString += "-model:sbastmoutfc " + ui->lineEditFastCorrectionsPA->text() + "\n";
            *runString << "-model:sbastmoutfc" << ui->lineEditFastCorrectionsPA->text();
        }
        // Fast corrections PA
        else if ( ui->lineEditFastCorrectionsPA->text() != "" ) {
            *saveString += "-model:sbastmoutfcpa " + ui->lineEditFastCorrectionsPA->text() + "\n";
            *runString << "-model:sbastmoutfcpa" << ui->lineEditFastCorrectionsPA->text();
        }
        // Fast corrections NPA
        else if ( ui->lineEditFastCorrectionsNPA->text() != "" ) {
            *saveString += "-model:sbastmoutfcnpa " + ui->lineEditFastCorrectionsNPA->text() + "\n";
            *runString << "-model:sbastmoutfcnpa" << ui->lineEditFastCorrectionsNPA->text();
        }
        // RRC corrections PA & NPA
        if ( ui->lineEditRRCcorrectionsPA->text() != "" && ui->lineEditRRCcorrectionsPA->text() == ui->lineEditRRCcorrectionsNPA->text() ) {
            *saveString += "-model:sbastmoutfc " + ui->lineEditRRCcorrectionsPA->text() + "\n";
            *runString << "-model:sbastmoutfc" << ui->lineEditRRCcorrectionsPA->text();
        }
        // RRC corrections PA
        else if ( ui->lineEditRRCcorrectionsPA->text() != "" ) {
            *saveString += "-model:sbastmoutrrcpa " + ui->lineEditRRCcorrectionsPA->text() + "\n";
            *runString << "-model:sbastmoutrrcpa" << ui->lineEditRRCcorrectionsPA->text();
        }
        // RRC corrections NPA
        else if ( ui->lineEditRRCcorrectionsNPA->text() != "" ) {
            *saveString += "-model:sbastmoutrrcnpa " + ui->lineEditRRCcorrectionsNPA->text() + "\n";
            *runString << "-model:sbastmoutrrcnpa" << ui->lineEditRRCcorrectionsNPA->text();
        }
        // Integrity info
        if ( ui->lineEditIntegrityInfoPA->text() == "" || ui->lineEditIntegrityInfoNPA->text() == "" ) {
            *errorString += "MODEL: Integrity info in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditIntegrityInfoPA->text().toInt() != 12 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutpa 6 " + ui->lineEditIntegrityInfoPA->text() + "\n";
                *runString << "-model:sbastmoutpa" << "6" << ui->lineEditIntegrityInfoPA->text();
            }
            // NPA
            if ( ui->lineEditIntegrityInfoNPA->text().toInt() != 18 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutnpa 6 " + ui->lineEditIntegrityInfoNPA->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "6" << ui->lineEditIntegrityInfoNPA->text();
            }
        }
        // Fast correction degradation factor
        if ( ui->lineEditFastCorrectionDegradationFactorPA->text() == "" || ui->lineEditFastCorrectionDegradationFactorNPA->text() == "" ) {
            *errorString += "MODEL: Fast correction degradation factor in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditFastCorrectionDegradationFactorPA->text().toInt() != 240 ) {
                *saveString += "-model:sbastmoutpa 7 " + ui->lineEditFastCorrectionDegradationFactorPA->text() + "\n";
                *runString << "-model:sbastmoutpa" << "7" << ui->lineEditFastCorrectionDegradationFactorPA->text();
            }
            // NPA
            if ( ui->lineEditFastCorrectionDegradationFactorNPA->text().toInt() != 360 ) {
                *saveString += "-model:sbastmoutnpa 7 " + ui->lineEditFastCorrectionDegradationFactorNPA->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "7" << ui->lineEditFastCorrectionDegradationFactorNPA->text();
            }
        }
        // Degradation parameters
        if ( ui->lineEditDegradationParametersPA->text() == "" || ui->lineEditDegradationParametersNPA->text() == "" ) {
            *errorString += "MODEL: Degradation parameters in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditDegradationParametersPA->text().toInt() != 240  || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutpa 10 " + ui->lineEditDegradationParametersPA->text() + "\n";
                *runString << "-model:sbastmoutpa" << "10" << ui->lineEditDegradationParametersPA->text();
            }
            // NPA
            if ( ui->lineEditDegradationParametersNPA->text().toInt() != 360 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutnpa 10 " + ui->lineEditDegradationParametersNPA->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "10" << ui->lineEditDegradationParametersNPA->text();
            }
        }
        // Long term satellite corrections
        if ( ui->lineEditLongTermSatelliteCorrectionsPA->text() == "" || ui->lineEditLongTermSatelliteCorrectionsNPA->text() == "" ) {
            *errorString += "MODEL: Long term satellite corrections in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditLongTermSatelliteCorrectionsPA->text().toInt() != 240 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutpa 25 " + ui->lineEditLongTermSatelliteCorrectionsPA->text() + "\n";
                *runString << "-model:sbastmoutpa" << "25" << ui->lineEditLongTermSatelliteCorrectionsPA->text();
            }
            // NPA
            if ( ui->lineEditLongTermSatelliteCorrectionsNPA->text().toInt() != 360 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutnpa 25 " + ui->lineEditLongTermSatelliteCorrectionsNPA->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "25" << ui->lineEditLongTermSatelliteCorrectionsNPA->text();
            }
        }
        // Ionospheric grid points mask
        if ( ui->lineEditIonosphericGridPointsMaskPA->text() == "" || ui->lineEditIonosphericGridPointsMaskNPA->text() == "" ) {
            *errorString += "MODEL: Ionospheric grid points mask in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditIonosphericGridPointsMaskPA->text().toInt() != 1200 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutpa 18 " + ui->lineEditIonosphericGridPointsMaskPA->text() + "\n";
                *runString << "-model:sbastmoutpa" << "18" << ui->lineEditIonosphericGridPointsMaskPA->text();
            }
            // NPA
            if ( ui->lineEditIonosphericGridPointsMaskNPA->text().toInt() != 1200 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutnpa 18 " + ui->lineEditIonosphericGridPointsMaskNPA->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "18" << ui->lineEditIonosphericGridPointsMaskNPA->text();
            }
        }
        // Ionospheric delay corrections
        if ( ui->lineEditIonosphericDelayCorrectionsPA->text() == "" || ui->lineEditIonosphericDelayCorrectionsNPA->text() == "" ) {
            *errorString += "MODEL: Ionospheric delay corrections in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditIonosphericDelayCorrectionsPA->text().toInt() != 600 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutpa 26 " + ui->lineEditIonosphericDelayCorrectionsPA->text() + "\n";
                *runString << "-model:sbastmoutpa" << "26" << ui->lineEditIonosphericDelayCorrectionsPA->text();
            }
            // NPA
            if ( ui->lineEditIonosphericDelayCorrectionsNPA->text().toInt() != 600 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutnpa 26 " + ui->lineEditIonosphericDelayCorrectionsNPA->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "26" << ui->lineEditIonosphericDelayCorrectionsNPA->text();
            }
        }
        // Service message
        if ( ui->lineEditServiceMessagePA->text() == "" || ui->lineEditServiceMessageNPA->text() == "" ) {
            *errorString += "MODEL: Service message in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditServiceMessagePA->text().toInt() != 86400  || WriteAllParameters==1) {
                *saveString += "-model:sbastmoutpa 27 " + ui->lineEditServiceMessagePA->text() + "\n";
                *runString << "-model:sbastmoutpa" << "27" << ui->lineEditServiceMessagePA->text();
            }
            // NPA
            if ( ui->lineEditServiceMessageNPA->text().toInt() != 86400  || WriteAllParameters==1) {
                *saveString += "-model:sbastmoutnpa 27 " + ui->lineEditServiceMessageNPA->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "27" << ui->lineEditServiceMessageNPA->text();
            }
        }
        // Clock ephemeris covariance matrix
        if ( ui->lineEditClockEphemerisCovarianceMatrixPA->text() == "" || ui->lineEditClockEphemerisCovarianceMatrixNPA->text() == "" ) {
            *errorString += "MODEL: Clock ephemeris covariance matrix in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditClockEphemerisCovarianceMatrixPA->text().toInt() != 240 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutpa 28 " + ui->lineEditClockEphemerisCovarianceMatrixPA->text() + "\n";
                *runString << "-model:sbastmoutpa" << "28" << ui->lineEditClockEphemerisCovarianceMatrixPA->text();
            }
            // NPA
            if ( ui->lineEditClockEphemerisCovarianceMatrixNPA->text().toInt() != 360  || WriteAllParameters==1) {
                *saveString += "-model:sbastmoutnpa 28 " + ui->lineEditClockEphemerisCovarianceMatrixNPA->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "28" << ui->lineEditClockEphemerisCovarianceMatrixNPA->text();
            }
        }
        // GEO navigation message
        if ( ui->lineEditGeoNavigationMessagePA->text() == "" || ui->lineEditGeoNavigationMessageNPA->text() == "" ) {
            *errorString += "MODEL: GEO navigation message in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditGeoNavigationMessagePA->text().toInt() != 240  || WriteAllParameters==1) {
                *saveString += "-model:sbastmoutpa 9 " + ui->lineEditGeoNavigationMessagePA->text() + "\n";
                *runString << "-model:sbastmoutpa" << "9" << ui->lineEditGeoNavigationMessagePA->text();
            }
            // NPA
            if ( ui->lineEditGeoNavigationMessageNPA->text().toInt() != 360  || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutnpa 9 " + ui->lineEditGeoNavigationMessageNPA->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "9" << ui->lineEditGeoNavigationMessageNPA->text();
            }
        }
        // GEO satellites almanacs
        if ( ui->lineEditGeoSatelliteAlmanacsPA->text() == "" || ui->lineEditGeoSatelliteAlmanacsNPA->text() == "" ) {
            *errorString += "MODEL: GEO satellites almanacs in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditGeoSatelliteAlmanacsPA->text().toInt() != 9999999 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutpa 17 " + ui->lineEditGeoSatelliteAlmanacsPA->text() + "\n";
                *runString << "-model:sbastmoutpa" << "17" << ui->lineEditGeoSatelliteAlmanacsPA->text();
            }
            // NPA
            if ( ui->lineEditGeoSatelliteAlmanacsNPA->text().toInt() != 9999999 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutnpa 17 " + ui->lineEditGeoSatelliteAlmanacsNPA->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "17" << ui->lineEditGeoSatelliteAlmanacsNPA->text();
            }
        }
        // Network time parameters
        if ( ui->lineEditNetworkTimeParametersPA->text() == "" || ui->lineEditNetworkTimeParametersNPA->text() == "" ) {
            *errorString += "MODEL: Network time parameters in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditNetworkTimeParametersPA->text().toInt() != 86400 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutpa 12 " + ui->lineEditNetworkTimeParametersPA->text() + "\n";
                *runString << "-model:sbastmoutpa" << "12" << ui->lineEditNetworkTimeParametersPA->text();
            }
            // NPA
            if ( ui->lineEditNetworkTimeParametersNPA->text().toInt() != 86400 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutnpa 12 " + ui->lineEditNetworkTimeParametersNPA->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "12" << ui->lineEditNetworkTimeParametersNPA->text();
            }
        }
        // Do not use for safety applications
        if ( ui->lineEditDoNotUseForSafetyAppPA->text() == "" || ui->lineEditDoNotUseForSafetyAppNPA->text() == "" ) {
            *errorString += "MODEL: Do not use for safety applications in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditDoNotUseForSafetyAppPA->text().toInt() != 9999999 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutpa 0 " + ui->lineEditDoNotUseForSafetyAppPA->text() + "\n";
                *runString << "-model:sbastmoutpa" << "0" << ui->lineEditDoNotUseForSafetyAppPA->text();
            }
            // NPA
            if ( ui->lineEditDoNotUseForSafetyAppNPA->text().toInt() != 9999999 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutnpa 0 " + ui->lineEditDoNotUseForSafetyAppNPA->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "0" << ui->lineEditDoNotUseForSafetyAppNPA->text();
            }
        }
    }


    // SBAS Advanced Options
    if ( ui->labelCurrentTemplate->text() == "SBAS 1F" || ui->labelCurrentTemplate->text() == "SBAS DFMC" || ui->groupBoxSbas->isChecked()==true ) {

        if ( ui->checkBoxParseAlarmSBAS1F->isChecked() == true && ui->labelCurrentTemplate->text() == "SBAS 1F") {
            *saveString += "-model:usealarmmsgcorr\n";
            *runString << "-model:usealarmmsgcorr";
        } else if ( ui->checkBoxParseAlarmSBAS1F->isChecked() == false) {
            //This is the default in SBAS 1F
            if (WriteAllParameters==1) {
                *saveString += "--model:usealarmmsgcorr\n";
                *runString << "--model:usealarmmsgcorr";
            }
        }

        if ( ui->checkBoxParseAlarmSBASDFMC->isChecked() == true && ui->labelCurrentTemplate->text() == "SBAS DFMC"
             && ui->checkBoxProcessAustralianTestBedMessages->isChecked()==false) {
            *saveString += "-model:usealarmmsgcorr\n";
            *runString << "-model:usealarmmsgcorr";
        } else if ( ui->checkBoxParseAlarmSBASDFMC->isChecked() == false) {
            //This is the default in SBAS DFMC
            if (WriteAllParameters==1) {
                *saveString += "--model:usealarmmsgcorr\n";
                *runString << "--model:usealarmmsgcorr";
            }
        }

        if ( ui->checkBoxIgnoreAllAlarm->isChecked() == true ) {
            *saveString += "-model:ignoretype0\n";
            *runString << "-model:ignoretype0";
        } else if ( ui->checkBoxIgnoreAllAlarm->isChecked() == false) {
            //This is the default in SBAS
            if (WriteAllParameters==1) {
                *saveString += "--model:ignoretype0\n";
                *runString << "--model:ignoretype0";
            }
        }

        if ( ui->labelCurrentTemplate->text() == "SBAS 1F") {
            if ( ui->checkBoxAllowKlobucharIono->isChecked() == true) {
                //This is the default in SBAS 1F
                if (WriteAllParameters==1) {
                    *saveString += "-model:initcoordnpa\n";
                    *runString << "-model:initcoordnpa";
                }
            } else if ( ui->checkBoxAllowKlobucharIono->isChecked() == false ) {
                *saveString += "--model:initcoordnpa\n";
                *runString << "--model:initcoordnpa";
            }
        }

        if ( ui->labelCurrentTemplate->text() == "SBAS DFMC") {
            if (ui->checkBoxAllowUseNoneMOPSMeas->isChecked() == true ){
                *saveString += "-model:sbasdfmc:anymeas\n";
                *runString << "-model:sbasdfmc:anymeas";
            } else if (ui->checkBoxAllowUseNoneMOPSMeas->isChecked() == false ){
                //This is the default in SBAS
                if (WriteAllParameters==1) {
                    *saveString += "--model:sbasdfmc:anymeas\n";
                    *runString << "--model:sbasdfmc:anymeas";
                }
            }
        }

        if ( ui->checkBoxDiscardUDREIThreshold->isChecked() == true) {
            *saveString += "-model:udreithreshold " + ui->comboBoxUDREIThresholds->currentText() + "\n";
            *runString << "-model:udreithreshold" << ui->comboBoxUDREIThresholds->currentText();
        } else if ( ui->checkBoxDiscardUDREIThreshold->isChecked() == false ) {
            //This is the default in SBAS
            if (WriteAllParameters==1) {
                *saveString += "--model:udreithreshold\n";
                *runString << "--model:udreithreshold";
            }
        }

        if ( ui->labelCurrentTemplate->text() == "SBAS 1F") {
            if(ui->lineEditOffsetFastCorrNoMT10->text()=="") {
                *errorString += "MODEL: Parameter in 'Sigma offset if MT10 is not used' option in [SBAS Options] cannot be empty.\n";
            } else if (ui->lineEditOffsetFastCorrNoMT10->text().toDouble()!=8. || WriteAllParameters==1) {
                *saveString += "-model:sigfltnomt10offset " + ui->lineEditOffsetFastCorrNoMT10->text() + "\n";
                *runString << "-model:sigfltnomt10offset" << ui->lineEditOffsetFastCorrNoMT10->text();
            }
        }

        if (ui->lineEditSBASSignalFlightTime->text()==""){
            *errorString += "MODEL: Parameter in 'SBAS Signal Flight Time' option in [SBAS Options] cannot be empty.\n";
        } else if (ui->lineEditSBASSignalFlightTime->text().toDouble()!=0.12 || WriteAllParameters==1) {
            *saveString += "-model:sbassignalflighttime " + ui->lineEditSBASSignalFlightTime->text() + "\n";
            *runString << "-model:sbassignalflighttime" << ui->lineEditSBASSignalFlightTime->text();
        }

        //// Geo & Mode Switch Options
       if ( ui->checkBoxMaintainCurrentGEOafterGEOswitch->isChecked() == true) {
           //This is the default in SBAS
           if (WriteAllParameters==1) {
            *saveString += "-model:maintaingeo\n";
            *runString << "-model:maintaingeo";
           }
        } else  if ( ui->checkBoxMaintainCurrentGEOafterGEOswitch->isChecked() == false ) {
            *saveString += "--model:maintaingeo\n";
            *runString << "--model:maintaingeo";
        }

        if ( ui->checkBoxReturnToInitialGEO->isChecked() == true ) {
            *saveString += "-model:geofallback\n";
            *runString << "-model:geofallback";
        } else if ( ui->checkBoxReturnToInitialGEO->isChecked() == false) {
            //This is the default in SBAS
            if (WriteAllParameters==1) {
                *saveString += "--model:geofallback\n";
                *runString << "--model:geofallback";
            }
        }
        if ( ui->lineEditGEOadquisitionTime->text() == "" ) {
            *errorString += "MODEL: GEO adquisition time in [SBAS Advanced Options] cannot be empty.\n";
        } else {
            if ( ui->lineEditGEOadquisitionTime->text().toInt() != 300 || WriteAllParameters==1 ) {
                *saveString += "-model:geoacqtime " + ui->lineEditGEOadquisitionTime->text() + "\n";
                *runString << "-model:geoacqtime" << ui->lineEditGEOadquisitionTime->text();
            }
        }
        if ( ui->lineEditSwitchinCooltime->text() == "" ) {
            *errorString += "MODEL: Switching cooltime in [SBAS Advanced Options] cannot be empty.\n";
        } else {
            if (ui->checkBoxSelectBestGEO->isChecked()==true) {
                //If option Select Best GEO is enabled, switchtime is forced to be 0, and is automatically set
                if (WriteAllParameters==1) {
                    *saveString += "-model:switchtime " + ui->lineEditSwitchinCooltime->text() + "\n";
                    *runString << "-model:switchtime" << ui->lineEditSwitchinCooltime->text();
                }
            } else if ( ui->lineEditSwitchinCooltime->text().toInt() != 0 || WriteAllParameters==1 ) {
                *saveString += "-model:switchtime " + ui->lineEditSwitchinCooltime->text() + "\n";
                *runString << "-model:switchtime" << ui->lineEditSwitchinCooltime->text();
            }
        }

        //// Show K factor values
        //KH PA
        if (ui->lineEditkhpa->text()=="") {
            *errorString += "MODEL: KH PA in [SBAS Advanced Options] cannot be empty.\n";
        } else if (ui->lineEditkhpa->text().toDouble()==0.) {
            *errorString += "MODEL: KH PA in [SBAS Advanced Options] cannot be 0.\n";
        } else {
            if (ui->lineEditkhpa->text().toDouble()!=6. || WriteAllParameters==1) {
                *saveString += "-model:khpa " + ui->lineEditkhpa->text() + "\n";
                *runString << "-model:khpa" << ui->lineEditkhpa->text();
            }
        }
        //KV PA
        if (ui->lineEditkvpa->text()=="") {
            *errorString += "MODEL: KV PA in [SBAS Advanced Options] cannot be empty.\n";
        } else if (ui->lineEditkvpa->text().toDouble()==0.) {
            *errorString += "MODEL: KV PA in [SBAS Advanced Options] cannot be 0.\n";
        } else {
            if (ui->lineEditkvpa->text().toDouble()!=5.33 || WriteAllParameters==1) {
                *saveString += "-model:kvpa " + ui->lineEditkvpa->text() + "\n";
                *runString << "-model:kvpa" << ui->lineEditkvpa->text();
            }
        }
        //KH NPA
        if (ui->lineEditkhnpa->text()=="") {
            *errorString += "MODEL: KH NPA in [SBAS Advanced Options] cannot be empty.\n";
        } else if (ui->lineEditkhnpa->text().toDouble()==0.) {
            *errorString += "MODEL: KH NPA in [SBAS Advanced Options] cannot be 0.\n";
        } else {
            if (ui->lineEditkhnpa->text().toDouble()!=6.18 || WriteAllParameters==1) {
                *saveString += "-model:khnpa " + ui->lineEditkhnpa->text() + "\n";
                *runString << "-model:khnpa" << ui->lineEditkhnpa->text();
            }
        }
        //KV NPA
        if (ui->lineEditkvnpa->text()=="") {
            *errorString += "MODEL: KV NPA in [SBAS Advanced Options] cannot be empty.\n";
        } else if (ui->lineEditkvnpa->text().toDouble()==0.) {
            *errorString += "MODEL: KV NPA in [SBAS Advanced Options] cannot be 0.\n";
        } else {
            if (ui->lineEditkvnpa->text().toDouble()!=5.33 || WriteAllParameters==1) {
                *saveString += "-model:kvnpa " + ui->lineEditkvnpa->text() + "\n";
                *runString << "-model:kvnpa" << ui->lineEditkvnpa->text();
            }
        }

        //// Show Disable Specific messages
        if ( ui->labelCurrentTemplate->text() == "SBAS 1F") {
            if (SBASmaritime==0) {
                //SBAS Maritime shortcut parameter not applied, check if these options have to be applied
                if (ui->checkBoxDisableMT10->isChecked()==true) {
                    *saveString += "-model:nomt10\n";
                    *runString << "-model:nomt10";
                }
                if (ui->checkBoxDisableMT2728->isChecked()==true) {
                    *saveString += "-model:nomt2728\n";
                    *runString << "-model:nomt2728";
                }
            }


            //// Show Disable Specific Corrections
            // Disable fast corrections
            if ( ui->checkBoxDisableFastCorrections->isChecked() == true ) {
                *saveString += "-model:nofastcor\n";
                *runString << "-model:nofastcor";
            }
            // Disable RRC corrections
            if ( ui->checkBoxDisableRRCcorrections->isChecked() == true ) {
                *saveString += "-model:norrccor\n";
                *runString << "-model:norrccor";
            }
            // Disable slow corrections
            if ( ui->checkBoxDisableSlowCorrections->isChecked() == true ) {
                *saveString += "-model:noslowcor\n";
                *runString << "-model:noslowcor";
            }
            // Disable ionosphere corrections
            if ( ui->checkBoxDisableIonosphereCorrections->isChecked() == true ) {
                *saveString += "-model:noionocor\n";
                *runString << "-model:noionocor";
            }

            //// Show Disable Specific Sigmas
            // Disable fast corrections sigmas
            if ( ui->checkBoxDisableFastCorrectionsSigma->isChecked() == true ) {
                *saveString += "-model:nofastsigma\n";
                *runString << "-model:nofastsigma";
            }
            // Disable fast degradation sigmas
            if ( ui->checkBoxDisableFastDegradationSigma->isChecked() == true ) {
                *saveString += "-model:nofastdeg\n";
                *runString << "-model:nofastdeg";
            }
            // Disable RRC sigma
            if ( ui->checkBoxDisableRRCsigma->isChecked() == true ) {
                *saveString += "-model:norrcsigma\n";
                *runString << "-model:norrcsigma";
            }
            // Disable slow corrections sigma
            if ( ui->checkBoxDisableSlowCorrectionsSigma->isChecked() == true ) {
                *saveString += "-model:noslowsigma\n";
                *runString << "-model:noslowsigma";
            }
            // Disable ionosphere sigma
            if ( ui->checkBoxDisableIonosphereSigma->isChecked() == true ) {
                *saveString += "-model:noionosigma\n";
                *runString << "-model:noionosigma";
            }
            // Disable troposphere sigma
            if ( ui->checkBoxDisableTroposphereSigma->isChecked() == true ) {
                *saveString += "-model:notroposigma\n";
                *runString << "-model:notroposigma";
            }
            // Disable En-route through NPA degradation term
            if ( ui->checkBoxDisableEnRoute->isChecked() == true ) {
                *saveString += "-model:noenroutesigma\n";
                *runString << "-model:noenroutesigma";
            }
        }
    }

    if ( ui->labelCurrentTemplate->text() == "SBAS DFMC" ){
        // Time-outs for SBAS DFMC
        if ( ui->lineEditDoNotUseForSafetyAppPA_DFMC->text() == "" || ui->lineEditDoNotUseForSafetyAppNPA_DFMC->text() == "" ) {
            *errorString += "MODEL: Do not use for safety applications in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditDoNotUseForSafetyAppPA_DFMC->text().toInt() != 9999999 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutpa 0 " + ui->lineEditDoNotUseForSafetyAppPA_DFMC->text() + "\n";
                *runString << "-model:sbastmoutpa" << "0" << ui->lineEditDoNotUseForSafetyAppPA_DFMC->text();
            }
            // NPA
            if ( ui->lineEditDoNotUseForSafetyAppNPA_DFMC->text().toInt() != 9999999 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutnpa 0 " + ui->lineEditDoNotUseForSafetyAppNPA_DFMC->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "0" << ui->lineEditDoNotUseForSafetyAppNPA_DFMC->text();
            }
        }
        if ( ui->lineEditSatMaskPA_DFMC->text() == "" || ui->lineEditSatMaskNPA_DFMC->text() == "" ) {
            *errorString += "MODEL: Satellite Mask in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditSatMaskPA_DFMC->text().toInt() != 600 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutpa 31 " + ui->lineEditSatMaskPA_DFMC->text() + "\n";
                *runString << "-model:sbastmoutpa" << "31" << ui->lineEditSatMaskPA_DFMC->text();
            }
            // NPA
            if ( ui->lineEditSatMaskNPA_DFMC->text().toInt() != 600 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutnpa 31 " + ui->lineEditSatMaskNPA_DFMC->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "31" << ui->lineEditSatMaskNPA_DFMC->text();
            }
        }

        // PA
        if ( ui->lineEditClkCovarianceMatrixPA_DFMC->text() != "" ) {
            *saveString += "-model:sbastmoutpa 32 " + ui->lineEditClkCovarianceMatrixPA_DFMC->text() + "\n";
            *runString << "-model:sbastmoutpa" << "32" << ui->lineEditClkCovarianceMatrixPA_DFMC->text();
        }
        // NPA
        if ( ui->lineEditClkCovarianceMatrixNPA_DFMC->text() != "" ) {
            *saveString += "-model:sbastmoutnpa 32 " + ui->lineEditClkCovarianceMatrixNPA_DFMC->text() + "\n";
            *runString << "-model:sbastmoutnpa" << "32" << ui->lineEditClkCovarianceMatrixNPA_DFMC->text();
        }

        if ( ui->lineEditIntegrityPA_DFMC->text() == "" || ui->lineEditIntegrityNPA_DFMC->text() == "" ) {
            *errorString += "MODEL: Integrity Messages in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditIntegrityPA_DFMC->text().toInt() != 12 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutpa 34 " + ui->lineEditIntegrityPA_DFMC->text() + "\n";
                *runString << "-model:sbastmoutpa" << "34" << ui->lineEditIntegrityPA_DFMC->text();
            }
            // NPA
            if ( ui->lineEditIntegrityNPA_DFMC->text().toInt() != 18 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutnpa 34 " + ui->lineEditIntegrityNPA_DFMC->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "34" << ui->lineEditIntegrityNPA_DFMC->text();
            }
        }
        if ( ui->lineEditOBADParDFREITablePA_DFMC->text() == "" || ui->lineEditOBADParDFREITableNPA_DFMC->text() == "" ) {
            *errorString += "MODEL: OBAD Parameters and DFREI Scale Table in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditOBADParDFREITablePA_DFMC->text().toInt() != 240 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutpa 37 " + ui->lineEditOBADParDFREITablePA_DFMC->text() + "\n";
                *runString << "-model:sbastmoutpa" << "37" << ui->lineEditOBADParDFREITablePA_DFMC->text();
            }
            // NPA
            if ( ui->lineEditOBADParDFREITableNPA_DFMC->text().toInt() != 360 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutnpa 37 " + ui->lineEditOBADParDFREITableNPA_DFMC->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "37" << ui->lineEditOBADParDFREITableNPA_DFMC->text();
            }
        }

        // PA
        if ( ui->lineEditSatCovarianceMatrixPA_DFMC->text() != "" ) {
            *saveString += "-model:sbastmoutpa 39 " + ui->lineEditSatCovarianceMatrixPA_DFMC->text() + "\n";
            *runString << "-model:sbastmoutpa" << "39" << ui->lineEditSatCovarianceMatrixPA_DFMC->text();
        }
        // NPA
        if ( ui->lineEditSatCovarianceMatrixNPA_DFMC->text() != "" ) {
            *saveString += "-model:sbastmoutnpa 39 " + ui->lineEditSatCovarianceMatrixNPA_DFMC->text() + "\n";
            *runString << "-model:sbastmoutnpa" << "39" << ui->lineEditSatCovarianceMatrixNPA_DFMC->text();
        }

        if ( ui->lineEditTimeOffsetsPA_DFMC->text() == "" || ui->lineEditTimeOffsetsNPA_DFMC->text() == "" ) {
            *errorString += "MODEL: GNSS Time Offsets in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditTimeOffsetsPA_DFMC->text().toInt() != 86400 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutpa 42 " + ui->lineEditTimeOffsetsPA_DFMC->text() + "\n";
                *runString << "-model:sbastmoutpa" << "42" << ui->lineEditTimeOffsetsPA_DFMC->text();
            }
            // NPA
            if ( ui->lineEditTimeOffsetsNPA_DFMC->text().toInt() != 86400 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutnpa 42 " + ui->lineEditTimeOffsetsNPA_DFMC->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "42" << ui->lineEditTimeOffsetsNPA_DFMC->text();
            }
        }
        if ( ui->lineEditSBASSatAlmanacsPA_DFMC->text() == "" || ui->lineEditSBASSatAlmanacsNPA_DFMC->text() == "" ) {
            *errorString += "MODEL: SBAS Satellites Almanacs in [SBAS Options] cannot be empty.\n";
        } else {
            // PA
            if ( ui->lineEditSBASSatAlmanacsPA_DFMC->text().toInt() != 240 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutpa 47 " + ui->lineEditSBASSatAlmanacsPA_DFMC->text() + "\n";
                *runString << "-model:sbastmoutpa" << "47" << ui->lineEditSBASSatAlmanacsPA_DFMC->text();
            }
            // NPA
            if ( ui->lineEditSBASSatAlmanacsNPA_DFMC->text().toInt() != 360 || WriteAllParameters==1 ) {
                *saveString += "-model:sbastmoutnpa 47 " + ui->lineEditSBASSatAlmanacsNPA_DFMC->text() + "\n";
                *runString << "-model:sbastmoutnpa" << "47" << ui->lineEditSBASSatAlmanacsNPA_DFMC->text();
            }
        }

        //Set OBAD parameter
        if ( ui->groupBoxSetOBADParameters->isChecked()==true ){
            //Set Cer OBAD Parameter from MT 37
            if ( ui->checkBoxSetCerOBADParameterMT37->isChecked()==true ){
                if ( ui->lineEditCerOBADParameterMT37->text()=="" ){
                    *errorString += "MODEL: Parameter in 'Set Cer OBAD Parameter from MT 37' in [SBAS Advanced Options] cannot be empty.\n";
                } else {
                    *saveString += "-model:sbasdfmc:cer " + ui->lineEditCerOBADParameterMT37->text() + "\n";
                    *runString << "-model:sbasdfmc:cer" << ui->lineEditCerOBADParameterMT37->text();
                }
            }
            //Set Ccovariance OBAD Parameter from MT 37
            if ( ui->checkBoxSetCcovarianceOBADParameterMT37->isChecked()==true ){
                if ( ui->lineEditCcovarianceOBADParameterMT37->text()=="" ){
                    *errorString += "MODEL: Parameter in 'Set Ccovariance OBAD Parameter from MT 37' in [SBAS Advanced Options] cannot be empty.\n";
                } else {
                    *saveString += "-model:sbasdfmc:ccovariance " + ui->lineEditCcovarianceOBADParameterMT37->text() + "\n";
                    *runString << "-model:sbasdfmc:ccovariance" << ui->lineEditCcovarianceOBADParameterMT37->text();
                }
            }
            //Set Icorr OBAD Parameter from MT 37
            if ( ui->checkBoxSetIcorrOBADParameterMT37->isChecked()==true ){
                if ( ui->checkBoxSetIcorrOBADParameterMT37Advanced->isChecked()==false ){
                    if ( ui->lineEditSetIcorrOBADParameterMT37->text()=="" ){
                        *errorString += "MODEL: Parameter in 'Set Icorr OBAD Parameter from MT 37' in [SBAS Advanced Options] cannot be empty.\n";
                    } else {
                        *saveString += "-model:sbasdfmc:icorr 0-" + ui->lineEditSetIcorrOBADParameterMT37->text() + "\n";
                        *runString << "-model:sbasdfmc:icorr 0-" << ui->lineEditSetIcorrOBADParameterMT37->text();
                    }
                }
                else SBASOBADSet->getgLABOptions(1,errorString,warningString,saveString,runString);
            }
            //Set Ccorr OBAD Parameter from MT 37
            if ( ui->checkBoxSetCcorrOBADParameterMT37->isChecked()==true ){
                if ( ui->checkBoxSetCcorrOBADParameterMT37Advanced->isChecked()==false ){
                    if ( ui->lineEditSetCcorrOBADParameterMT37->text()=="" ){
                        *errorString += "MODEL: Parameter in 'Set Ccorr OBAD Parameter from MT 37' in [SBAS Advanced Options] cannot be empty.\n";
                    } else {
                        *saveString += "-model:sbasdfmc:ccorr 0-" + ui->lineEditSetCcorrOBADParameterMT37->text() + "\n";
                        *runString << "-model:sbasdfmc:ccorr 0-" << ui->lineEditSetCcorrOBADParameterMT37->text();
                    }
                }
                else SBASOBADSet->getgLABOptions(2,errorString,warningString,saveString,runString);
            }
            //Set Rcorr OBAD Parameter from MT 37
            if ( ui->checkBoxSetRcorrOBADParameterMT37->isChecked()==true ){
                if ( ui->checkBoxSetRcorrOBADParameterMT37Advanced->isChecked()==false ){
                    if ( ui->lineEditSetRcorrOBADParameterMT37->text()=="" ){
                        *errorString += "MODEL: Parameter in 'Set Rcorr OBAD Parameter from MT 37' in [SBAS Advanced Options] cannot be empty.\n";
                    } else {
                        *saveString += "-model:sbasdfmc:rcorr 0-" + ui->lineEditSetRcorrOBADParameterMT37->text() + "\n";
                        *runString << "-model:sbasdfmc:rcorr 0-" << ui->lineEditSetRcorrOBADParameterMT37->text();
                    }
                }
                else SBASOBADSet->getgLABOptions(3,errorString,warningString,saveString,runString);
            }
        }
        //Set DFREI parameter
        if ( ui->groupBoxSetDFREICorrections->isChecked()==true ){
            //Set one DFREI Sigma Conversion Value
            if ( ui->checkBoxSetOneDFREISigmaConversionValue->isChecked()==true ){
                if ( ui->comboBoxSetDFREIN->currentText()=="" || ui->lineEditSetDFREIValue->text()=="" ){
                    *errorString += "MODEL: Parameters in 'Set one DFREI Sigma Conversion Value' in [SBAS Advanced Options] cannot be empty.\n";
                } else {
                    *saveString += "-model:sbasdfmc:dfrei " + ui->comboBoxSetDFREIN->currentText() + " " + ui->lineEditSetDFREIValue->text() + "\n";
                    *runString << "-model:sbasdfmc:dfrei" << ui->comboBoxSetDFREIN->currentText() << ui->lineEditSetDFREIValue->text();
                }
            }
            //Set All DFREI Conversion Values
            if ( ui->checkBoxSetAllDFREIConversionValues->isChecked()==true || ui->lineEditSetValueDFREI0->text()!="0.625" || ui->lineEditSetValueDFREI1->text()!="1.25"
                  || ui->lineEditSetValueDFREI2->text()!="1.375" || ui->lineEditSetValueDFREI3->text()!="1.5" || ui->lineEditSetValueDFREI4->text()!="1.625"
                  || ui->lineEditSetValueDFREI5->text()!="2.75" || ui->lineEditSetValueDFREI6->text()!="3" || ui->lineEditSetValueDFREI7->text()!="3.25"
                  || ui->lineEditSetValueDFREI8->text()!="3.5" || ui->lineEditSetValueDFREI9->text()!="3.75" || ui->lineEditSetValueDFREI10->text()!="6"
                  || ui->lineEditSetValueDFREI11->text()!="6.5" || ui->lineEditSetValueDFREI12->text()!="11" || ui->lineEditSetValueDFREI13->text()!="28"
                  || ui->lineEditSetValueDFREI14->text()!="58"){
                if ( ui->lineEditSetValueDFREI0->text()=="" || ui->lineEditSetValueDFREI1->text()=="" || ui->lineEditSetValueDFREI2->text()==""
                      || ui->lineEditSetValueDFREI3->text()=="" || ui->lineEditSetValueDFREI4->text()=="" || ui->lineEditSetValueDFREI5->text()==""
                      || ui->lineEditSetValueDFREI6->text()=="" || ui->lineEditSetValueDFREI7->text()=="" || ui->lineEditSetValueDFREI8->text()==""
                      || ui->lineEditSetValueDFREI9->text()=="" || ui->lineEditSetValueDFREI10->text()=="" || ui->lineEditSetValueDFREI11->text()==""
                      || ui->lineEditSetValueDFREI12->text()=="" || ui->lineEditSetValueDFREI13->text()=="" || ui->lineEditSetValueDFREI14->text()==""){
                    *errorString += "MODEL: Parameters in 'Set All DFREI Conversion Values' in [SBAS Advanced Options] cannot be empty.\n";
                } else {
                    *saveString += "-model:sbasdfmc:dfreilist " + ui->lineEditSetValueDFREI0->text() + "," + ui->lineEditSetValueDFREI1->text() + "," + ui->lineEditSetValueDFREI2->text()
                            + "," + ui->lineEditSetValueDFREI3->text() + "," + ui->lineEditSetValueDFREI4->text() + "," + ui->lineEditSetValueDFREI5->text()
                            + "," + ui->lineEditSetValueDFREI6->text() + "," + ui->lineEditSetValueDFREI7->text() + "," + ui->lineEditSetValueDFREI8->text()
                            + "," + ui->lineEditSetValueDFREI9->text() + "," + ui->lineEditSetValueDFREI10->text() + "," + ui->lineEditSetValueDFREI11->text()
                            + "," + ui->lineEditSetValueDFREI12->text() + "," + ui->lineEditSetValueDFREI13->text() + "," + ui->lineEditSetValueDFREI14->text() + "\n";
                    *runString << "-model:sbasdfmc:dfreilist" << ( ui->lineEditSetValueDFREI0->text() + "," + ui->lineEditSetValueDFREI1->text() + "," + ui->lineEditSetValueDFREI2->text()
                                  + "," + ui->lineEditSetValueDFREI3->text() + "," + ui->lineEditSetValueDFREI4->text() + "," + ui->lineEditSetValueDFREI5->text()
                                  + "," + ui->lineEditSetValueDFREI6->text() + "," + ui->lineEditSetValueDFREI7->text() + "," + ui->lineEditSetValueDFREI8->text()
                                  + "," + ui->lineEditSetValueDFREI9->text() + "," + ui->lineEditSetValueDFREI10->text() + "," + ui->lineEditSetValueDFREI11->text()
                                  + "," + ui->lineEditSetValueDFREI12->text() + "," + ui->lineEditSetValueDFREI13->text() + "," + ui->lineEditSetValueDFREI14->text() );
                }
            }
        }
        //Set specific Sigmas
        if ( ui->groupBoxSetSepcificSigmas->isChecked()==true ){
            //Set Delta Rcorr Parameter
            if ( ui->checkBoxSetDeltaRcorrParameter->isChecked()==true ){
                if ( ui->lineEditSetDeltaRcorrParameter->text()=="" ){
                    *errorString += "MODEL: Parameter in 'Set Delta Rcorr Parameter' in [SBAS Advanced Options] cannot be empty.\n";
                } else {
                    *saveString += "-model:sbasdfmc:deltarcorr " + ui->lineEditSetDeltaRcorrParameter->text() + "\n";
                    *runString << "-model:sbasdfmc:deltarcorr" << ui->lineEditSetDeltaRcorrParameter->text();
                }
            }
            //Set Delta DFRE Factor
            if ( ui->checkBoxSetDeltaDFREFactor->isChecked()==true ){
                if ( ui->lineEditSetDeltaDFREFactor->text()=="" ){
                    *errorString += "MODEL: Parameter in 'Set Delta DFRE Factor' in [SBAS Advanced Options] cannot be empty.\n";
                } else {
                    *saveString += "-model:sbasdfmc:deltadfre " + ui->lineEditSetDeltaDFREFactor->text() + "\n";
                    *runString << "-model:sbasdfmc:deltadfre" << ui->lineEditSetDeltaDFREFactor->text();
                }
            }
            //Set UIRE Sigma Value
            if ( ui->checkBoxSetUIRESigmaValue->isChecked()==true ){
                if ( ui->lineEditSetUIRESigmaValue->text()=="" ){
                    *errorString += "MODEL: Parameter in 'Set UIRE Sigma Value' in [SBAS Advanced Options] cannot be empty.\n";
                } else {
                    *saveString += "-model:sbasdfmc:sigmauire " + ui->lineEditSetUIRESigmaValue->text() + "\n";
                    *runString << "-model:sbasdfmc:sigmauire" << ui->lineEditSetUIRESigmaValue->text();
                }
            }
            //Set Tropospheric Sigma
            if ( ui->checkBoxSetTroposphericSigma->isChecked()==true ){
                if ( ui->lineEditSetTroposphericSigma->text()=="" ){
                    *errorString += "MODEL: Parameter in 'Set Tropospheric Sigma' in [SBAS Advanced Options] cannot be empty.\n";
                } else {
                    *saveString += "-model:sbasdfmc:sigmatropo " + ui->lineEditSetTroposphericSigma->text() + "\n";
                    *runString << "-model:sbasdfmc:sigmatropo" << ui->lineEditSetTroposphericSigma->text();
                }
            }
        }
        //Show old messages
        if ( ui->groupBoxShowOldMessages->isChecked()==true ){
            if (ui->checkBoxProcessAustralianTestBedMessages->isChecked()==true){
                *saveString += "-model:sbasdfmc:austestbed\n";
                *runString << "-model:sbasdfmc:austestbed";
                if (DCBdfGPS!="") {
                    *saveString += DCBdfGPS + "\n";
                    QStringList tmpString = DCBdfGPS.split(QRegularExpression("\\s+"));
                    for(int k=0;k<tmpString.size();k++) {
                        *runString << tmpString[k];
                    }
                }
            } else {
                if (ui->checkBoxDecodeMT37->isChecked()==true){
                    *saveString += "-model:sbasdfmc:mt37v04\n";
                    *runString << "-model:sbasdfmc:mt37v04";
                }
                if (ui->checkBoxDecodeMT3940->isChecked()==true){
                    *saveString += "-model:sbasdfmc:mt3940v04\n";
                    *runString << "-model:sbasdfmc:mt3940v04";
                }
                if (ui->checkBoxDecodeMT42->isChecked()==true){
                    *saveString += "-model:sbasdfmc:mt42v07\n";
                    *runString << "-model:sbasdfmc:mt42v07";
                }
                if (ui->checkBoxDecodeMT47->isChecked()==true){
                    *saveString += "-model:sbasdfmc:mt47v04\n";
                    *runString << "-model:sbasdfmc:mt47v04";
                }
            }
        }
    }

    // DGNSS Options
    if ( ui->labelCurrentTemplate->text() == "DGNSS" || ui->groupBoxReferenceStation->isChecked()==true ) {
        // Inflate sigma during the smoother convergence
        if ( ui->checkBoxDgnssInflateSigma->isChecked() == true ) {
            //This is the default for GNSS. No need to set the option
            if (WriteAllParameters==1 ) {
                *saveString += "-model:dgnss:sigmainflation\n";
                *runString << "-model:dgnss:sigmainflation";
            }
        } else {
            *saveString += "--model:dgnss:sigmainflation\n";
            *runString << "--model:dgnss:sigmainflation";
        }
        // Maximum age for corrections
        if ( ui->lineEditMaxAgeDgnss->text() == "" ) {
            *errorString += "MODEL: Maximum age for corrections in DGNSS Options cannot be empty.\n";
        } else {
            if ( ui->lineEditMaxAgeDgnss->text().toDouble() != 31. || WriteAllParameters==1) {
                *saveString += "-model:dgnss:maxage " + ui->lineEditMaxAgeDgnss->text() + "\n";
                *runString << "-model:dgnss:maxage" << ui->lineEditMaxAgeDgnss->text();
            }
        }
        // Maximum value for corrections
        if ( ui->lineEditMaxValueDGNSS->text() == "" ) {
            *errorString += "MODEL: Maximum value for corrections in DGNSS Options cannot be empty.\n";
        } else {
            if ( ui->lineEditMaxValueDGNSS->text().toDouble() != 500. || WriteAllParameters==1 ) {
                *saveString += "-model:dgnss:maxcorrval " + ui->lineEditMaxValueDGNSS->text() + "\n";
                *runString << "-model:dgnss:maxcorrval" << ui->lineEditMaxValueDGNSS->text();
            }
        }
    }
}
