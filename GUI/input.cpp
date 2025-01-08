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

// Function to show or hide Start time Date
void gLAB_GUI::on_checkBoxStartTime_clicked(bool checked) {
    ui->checkBoxStartTime->setChecked(checked);
    ui->dateTimeEditStartTime->setHidden(!checked);
}

// Function to show or hide End time Date
void gLAB_GUI::on_checkBoxEndTime_clicked(bool checked) {
    ui->checkBoxEndTime->setChecked(checked);
    ui->dateTimeEditEndTime->setHidden(!checked);
}

// Function to show or hide the ANTEX input
void gLAB_GUI::on_checkBoxSatAntex_clicked(bool checked) {
    ui->checkBoxSatAntex->setChecked(checked);
    ui->lineEditSatAntex->setHidden(!checked);
    ui->pushButtonSatAntex->setHidden(!checked);
    if (!checked){
        this->on_checkBoxRecAntex_clicked(false);
        ui->checkBoxRecAntex->setHidden(true);
    } else {
        ui->checkBoxRecAntex->setHidden(false);
    }
}
// Function to show or hide the ANTEX input
void gLAB_GUI::on_checkBoxRecAntex_clicked(bool checked) {
    ui->checkBoxRecAntex->setChecked(checked);
    ui->lineEditRecAntex->setHidden(!checked);
    ui->pushButtonRecAntex->setHidden(!checked);
}
// Function to select SBAS input file for SBAS 1F or SBAS DFMC
void gLAB_GUI::on_comboBoxSbasInput_currentIndexChanged(int index){
    ui->comboBoxSbasInput->setCurrentIndex(index);
    if (index==0) {//SBAS 1F
        this->on_groupBoxSbas_clicked(true);
    }
    else if (index==1) {//SBAS DFMC
        this->on_groupBoxSbas_clicked(true);
        ui->labelCurrentTemplate->setText("SBAS DFMC");
        ui->actionSBAS_DFMC->setChecked(true);
        this->setSBASDFMCDefault();
    }
}
// Function to show or hide Reference file input for Calculate
void gLAB_GUI::on_checkBoxReferencePositionFileCalculate_clicked(bool checked) {
    ui->checkBoxReferencePositionFileCalculate->setChecked(checked);
    ui->frameTextEditRefFileCalculate->setHidden(!checked);
}

// Function to set the correct stacked window in Reference station input
void gLAB_GUI::on_comboBoxRefStation_currentIndexChanged(int index) {
    ui->comboBoxRefStation->setCurrentIndex(index);
    ui->stackedWidgetRefStation->setCurrentIndex(index);
    if (index==0) {
        //RINEX file for reference selected, show options for user defined reference station
        ui->radioButtonRtcmUserBaseline->setHidden(false);
        ui->radioButtonRtcmUserRinexRover->setHidden(false);
        ui->radioButtonRtcmUserSpecify->setHidden(false);
    } else {
        //RTCM file for reference selected, hide options for user defined reference station
        if (ui->radioButtonRtcmUserBaseline->isChecked() == true || ui->radioButtonRtcmUserRinexRover->isChecked()==true || ui->radioButtonRtcmUserSpecify->isChecked()==true ) {
            this->on_radioButtonRtcm_clicked();
        }
        ui->radioButtonRtcmUserBaseline->setHidden(true);
        ui->radioButtonRtcmUserRinexRover->setHidden(true);
        ui->radioButtonRtcmUserSpecify->setHidden(true);
    }
}

// Function to set the correct stacked window in DCB source (in SPP, SBAS and DGNSS)
void gLAB_GUI::on_comboBoxDcbSource_currentIndexChanged(int index) {
    ui->comboBoxDcbSource->setCurrentIndex(index);
    ui->stackedWidgetDcbSource->setCurrentIndex(index);
    switch ( index ) {
        case 0 : {
            ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(1);
            break;
        }
        case 1 : {
            ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(1);
            ui->comboBoxDcbSourcePPP->setCurrentIndex(0);
            break;
        }
        case 2 : {
            ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(2);
            ui->comboBoxDcbSourcePPP->setCurrentIndex(1);
            break;
        }
        case 3 : {
            ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(3);
            ui->comboBoxDcbSourcePPP->setCurrentIndex(2);
            break;
        }
        case 4 : {
            ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(3);
            ui->comboBoxDcbSourcePPP->setCurrentIndex(3);
            break;
        }
    }
    if (index<=1 && ui->comboBoxDCBsfP1P2GPS->currentIndex()==1) {
        ui->checkBoxDiscardUnhealthy->setHidden(false);
    }
}

// Function to set the correct stacked window in DCB source in PPP
void gLAB_GUI::on_comboBoxDcbSourcePPP_currentIndexChanged(int index) {
    ui->comboBoxDcbSourcePPP->setCurrentIndex(index);
    ui->stackedWidgetDcbSource->setCurrentIndex(index+1);
    switch ( index ) {
        case 0 : {
            ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(1);
            ui->comboBoxDcbSource->setCurrentIndex(1);
            break;
        }
        case 1 : {
            ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(2);
            ui->comboBoxDcbSource->setCurrentIndex(2);
            break;
        }
        case 2 : {
            ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(3);
            ui->comboBoxDcbSource->setCurrentIndex(3);
            break;
        }
        case 3 : {
            ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(3);
            ui->comboBoxDcbSource->setCurrentIndex(4);
            break;
        }
    }
    if (index==0 && ui->comboBoxDCBsfP1P2GPS->currentIndex()==1) {
        ui->checkBoxDiscardUnhealthy->setHidden(false);
    }
}

// Function to set the correct stacked window in Ionosphere Source broadcast
void gLAB_GUI::on_comboBoxIonoSourceBrdc_currentIndexChanged(int index) {
    ui->comboBoxIonoSourceBrdc->setCurrentIndex(index);
    ui->stackedWidgetIonoSourceBrdc->setCurrentIndex(index);
}


/////////////////// Group Box buttons ///////////////////
void gLAB_GUI::on_groupBoxIonoSource_clicked(bool checked) {
    ui->groupBoxIonoSource->setChecked(checked);
    ui->frameIonoSource->setHidden(!checked);
}

void gLAB_GUI::on_groupBoxSbas_clicked(bool checked) {
    if ( checked == true ) {
        if ( ui->labelCurrentTemplate->text() != "SBAS 1F" && ui->labelCurrentTemplate->text() != "SBAS DFMC" ) {
            QMessageBox messageBox;
            messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
            messageBox.warning(nullptr, "Warning","SBAS template in the upper bar will setup the default configuration options.\n");
        }
        ui->labelCurrentTemplate->setText("SBAS 1F");
        ui->actionSBAS_1F->setChecked(true);
        this->on_groupBoxReferenceStation_clicked(false);
        ui->stackedWidgetOtherMessages->setCurrentIndex(1);
        ui->stackedWidgetOtherMessages->setHidden(false);
        ui->frameOutputSatVel->setContentsMargins(0,11,0,9);
        //Hide precise orbit file input
        ui->radioButtonOrbitPrecise1file->setHidden(true);
        ui->radioButtonOrbitPrecise2files->setHidden(true);
        on_radioButtonOrbitBrdc_clicked();
        //Hide "Preferred age time:" option
        ui->frameNavFreshTime->setHidden(true);
        //Hide input path for SBAS iono
        ui->stackedWidgetIonoSourceSbas->setCurrentIndex(0);
        //Disable P1-C1 correction
        this->on_groupBoxP1C1correction_clicked(false);
        this->on_comboBoxDCBsfP1C1GPS_currentIndexChanged(0);
        ui->groupBoxP1C1correction->setDisabled(true);
        ui->groupBoxP1C1correction->setHidden(true);
        //Set SBAS iono model
        this->on_comboBoxIonoCorrection_currentIndexChanged(4);
        //Show Step Detector option in Filter
        ui->checkBoxStepDetector->setHidden(false);
        //Set Single-frequency navigation and disable dual-frequency
        this->on_radioButtonSingleFreq_clicked();
        ui->radioButtonDualFreq->setHidden(true);
        //Hide graphic combination
        ui->radioButtonSelectionGraphic->setHidden(true);
        //Hide Backward filtering
        ui->checkBoxBackwardFiltering->setHidden(true);
        ui->checkBoxBackwardFiltering->setChecked(false);
        ui->radioButtonSelectionPseudorangeCarrierPhase->setHidden(true);
        //Disable satellite phase center correction
        this->on_checkBoxSatMassCentre_clicked(false);
        ui->checkBoxSatMassCentre->setEnabled(false);
        //Set stacked widget in filter for SBAS measurements and weights
        ui->stackedWidgetMeasurementGNSS->setCurrentIndex(0);
        //Show Stanford-ESA plot
        ui->groupBoxStanfordESA->setHidden(false);
        //Show options in Summary only for SBAS
        ui->groupBoxSbasAlarmLimits->setHidden(false);
        ui->labelSummarySlidingWindow->setHidden(false);
        ui->lineEditSlidingWindowSBAS->setHidden(false);
        ui->frameSummaryWindowSamples->setHidden(false);
        ui->groupBoxSbas->setChecked(true);
        ui->frameSbas->setHidden(false);
        ui->groupBoxUserDefinedSbasSigmaMultipath->setHidden(false);
        ui->groupBoxSbasOptions->setHidden(false);
        ui->groupBoxSbasAdvancedOptions->setHidden(false);
        this->setSBAS1FDefault();
    } else {
        ui->stackedWidgetOtherMessages->setCurrentIndex(0);
        ui->stackedWidgetOtherMessages->setHidden(true);
        ui->frameOutputSatVel->setContentsMargins(0,0,0,9);
        //Show precise orbit file input
        ui->radioButtonOrbitPrecise1file->setHidden(false);
        ui->radioButtonOrbitPrecise2files->setHidden(false);
        //Show "Preferred age time:" option
        ui->frameNavFreshTime->setHidden(false);
        //Hide input path for SBAS iono
        ui->stackedWidgetIonoSourceSbas->setCurrentIndex(1);
        //Enable P1-C1 correction
        ui->groupBoxP1C1correction->setDisabled(false);
        ui->groupBoxP1C1correction->setHidden(false);
        this->on_comboBoxDCBsfP1C1GPS_currentIndexChanged(0);
        //Unset SBAS iono model if it is set
        if (ui->comboBoxIonoCorrection->currentIndex()==4) {
             this->on_comboBoxIonoCorrection_currentIndexChanged(0);
        }
        //Hide Step Detector option in Filter
        ui->checkBoxStepDetector->setHidden(true);
        //Enable Dual frequency processing
        ui->radioButtonDualFreq->setHidden(false);
        //Show graphic combination
        ui->radioButtonSelectionGraphic->setHidden(false);
        //Show Backward filtering
        ui->checkBoxBackwardFiltering->setHidden(false);
        //Enable pseudorange +carrier phase in the filter
        ui->radioButtonSelectionPseudorangeCarrierPhase->setHidden(false);
        //Enable satellite phase center correction
        ui->checkBoxSatMassCentre->setEnabled(true);
        //Hide Stanford-ESA plot
        this->on_groupBoxStanfordESA_clicked(false);
        ui->groupBoxStanfordESA->setHidden(true);
        //Hide options in Summary only for SBAS
        ui->groupBoxSbasAlarmLimits->setHidden(true);
        ui->labelSummarySlidingWindow->setHidden(true);
        ui->lineEditSlidingWindowSBAS->setHidden(true);
        ui->frameSummaryWindowSamples->setHidden(true);
        ui->groupBoxSbas->setChecked(false);
        ui->frameSbas->setHidden(true);
        ui->groupBoxUserDefinedSbasSigmaMultipath->setHidden(true);
        ui->groupBoxSbasOptions->setHidden(true);
        ui->groupBoxSbasAdvancedOptions->setHidden(true);
        if ( ui->labelCurrentTemplate->text() == "SBAS 1F" || ui->labelCurrentTemplate->text() == "SBAS DFMC") {
            QMessageBox messageBox;
            messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
            messageBox.warning(nullptr, "Warning","SPP template in the upper bar will setup the default configuration options.\n");
            ui->labelCurrentTemplate->setText("SPP");
            ui->actionSPP->setChecked(true);
            this->setSPPDefault();
        }
    }
}

void gLAB_GUI::on_groupBoxReferenceStation_clicked(bool checked) {
    if ( checked == true ) {
        if ( ui->labelCurrentTemplate->text() != "DGNSS" ) {
            QMessageBox messageBox;
            messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
            messageBox.warning(nullptr, "Warning","DGNSS template in the upper bar will setup the default configuration options.\n");
        }
        ui->labelCurrentTemplate->setText("DGNSS");
        ui->actionDGNSS->setChecked(true);
        this->on_groupBoxSbas_clicked(false);
        ui->stackedWidgetOtherMessages->setCurrentIndex(2);
        ui->stackedWidgetOtherMessages->setHidden(false);
        ui->frameOutputSatVel->setContentsMargins(0,11,0,9);
        this->on_radioButtonRtcm_clicked();

        if (ui->checkBoxKML->isChecked() == true || ui->checkBoxKML0->isChecked() == true) {
            ui->checkBoxKMLRefStations->setHidden(false);
        }
        if (ui->checkBoxOutputSP3->isChecked()==true) {
            ui->checkBoxSP3OutFileWriteSPPSolutions->setHidden(false);
        }
        if (ui->checkBoxOutRefFile->isChecked()==true) {
            ui->frameOutReffileWriteSPPsolution->setHidden(false);
        }


        //Hide precise orbit file input
        ui->radioButtonOrbitPrecise1file->setHidden(true);
        ui->radioButtonOrbitPrecise2files->setHidden(true);
        on_radioButtonOrbitBrdc_clicked();
        //Set Single-frequency navigation and disable dual-frequency
        this->on_radioButtonSingleFreq_clicked();
        ui->radioButtonDualFreq->setHidden(true);
        //Hide Backward filtering
        ui->checkBoxBackwardFiltering->setHidden(true);
        ui->checkBoxBackwardFiltering->setChecked(false);
        ui->radioButtonSelectionPseudorangeCarrierPhase->setHidden(true);
        //Disable satellite phase center correction
        this->on_checkBoxSatMassCentre_clicked(false);
        ui->checkBoxSatMassCentre->setEnabled(false);
        //Hide Stanford-ESA plot
        this->on_groupBoxStanfordESA_clicked(false);
        ui->groupBoxStanfordESA->setHidden(true);
        //Hide positioning modes not available in DGNSS
        ui->frameAPrioriPositionFrom->setHidden(true);
        //RTCM button is always hidden
        ui->radioButtonRtcm->setHidden(false);
        ui->groupBoxReferenceStation->setChecked(true);
        ui->frameReferenceStation->setHidden(false);
        ui->groupBoxDgnssOptions->setHidden(false);
        ui->stackedWidgetIonoSourceSbas->setCurrentIndex(1);
        this->setDGNSSDefault();
    } else {
        ui->stackedWidgetOtherMessages->setCurrentIndex(0);
        ui->stackedWidgetOtherMessages->setHidden(true);
        ui->frameOutputSatVel->setContentsMargins(0,0,0,9);
        this->on_radioButtonRtcmBaseline_clicked();
        if(ui->radioButtonRtcm->isChecked()==true){
            this->on_radioButtonRinex_clicked();
        }
        ui->checkBoxKMLRefStations->setHidden(true);
        ui->checkBoxSP3OutFileWriteSPPSolutions->setHidden(true);
        ui->frameOutReffileWriteSPPsolution->setHidden(true);
        //Show precise orbit file input
        ui->radioButtonOrbitPrecise1file->setHidden(false);
        ui->radioButtonOrbitPrecise2files->setHidden(false);
        //Enable Dual frequency processing
        ui->radioButtonDualFreq->setHidden(false);
        //Show Backward filtering
        ui->checkBoxBackwardFiltering->setHidden(false);
        //Enable pseudorange +carrier phase in the filter
        ui->radioButtonSelectionPseudorangeCarrierPhase->setHidden(false);
        //Enable satellite phase center correction
        ui->checkBoxSatMassCentre->setEnabled(true);
        //Hide positioning modes not available in DGNSS
        ui->frameAPrioriPositionFrom->setHidden(false);
        //RTCM button is always hidden
        ui->radioButtonRtcm->setHidden(true);
        ui->groupBoxReferenceStation->setChecked(false);
        ui->frameReferenceStation->setHidden(true);
        ui->groupBoxDgnssOptions->setHidden(true);
        ui->stackedWidgetIonoSourceSbas->setCurrentIndex(1);
        if ( ui->labelCurrentTemplate->text() == "DGNSS" ) {
            QMessageBox messageBox;
            messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
            messageBox.warning(nullptr, "Warning","SPP template in the upper bar will setup the default configuration options.\n");
            ui->labelCurrentTemplate->setText("SPP");
            ui->actionSPP->setChecked(true);
            this->setSPPDefault();
        }
    }
}

void gLAB_GUI::on_groupBoxAuxFiles_clicked(bool checked) {
    ui->groupBoxAuxFiles->setChecked(checked);
    ui->frameAuxFiles->setHidden(!checked);
}

void gLAB_GUI::on_groupBoxP1C1correction_clicked(bool checked) {
    ui->groupBoxP1C1correction->setChecked(checked);
    ui->frameInputP1C1correction->setHidden(!checked);
    if ( ui->lineEditDcbFile->text().length()>0 && checked==true ) {
        // Set in Modelling to Strict
        ui->comboBoxDCBsfP1C1GPS->setCurrentIndex(1);
    }
}

void gLAB_GUI::on_groupBoxP1P2correction_clicked(bool checked) {
    ui->groupBoxP1P2correction->setChecked(checked);
    ui->frameInputP1P2correction->setHidden(!checked);
    if( checked==true && openP1P2>0 ) {
        ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(1);
    } else if (ui->radioButtonOrbitBrdc->isChecked()==false) {
        ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(0);
    }
    if (checked==true && ui->comboBoxDCBsfP1P2GPS->currentIndex()==1) {
        ui->checkBoxDiscardUnhealthy->setHidden(false);
    } else if (checked==false && ui->radioButtonOrbitBrdc->isChecked()==false) {
        //ui->checkBoxDiscardUnhealthy->setHidden(true);
    }
}

void gLAB_GUI::on_groupBoxUserAddedError_clicked(bool checked) {
    ui->groupBoxUserAddedError->setChecked(checked);
    ui->frameUserAddedError->setHidden(!checked);
}

void gLAB_GUI::on_groupBoxUserDefinedSbasSigmaMultipath_clicked(bool checked) {
    ui->groupBoxUserDefinedSbasSigmaMultipath->setChecked(checked);
    ui->frameUserDefinedSbasSigmaMultipath->setHidden(!checked);
    if (ui->groupBoxAuxFiles->isChecked()==false && ui->groupBoxUserDefinedSbasSigmaMultipath->isChecked()==true) {
        this->on_groupBoxAuxFiles_clicked(true);
    }
    if  (ui->groupBoxUserDefinedReceiverSigma->isChecked()==false && checked==true) {
            this->on_groupBoxUserDefinedReceiverSigma_clicked(true);
    }
    if (ui->checkBoxUserDefinedReceiverSigmaMultipathModel->isChecked()==false && checked==true) {
        this->on_checkBoxUserDefinedReceiverSigmaMultipathModel_clicked(true);
    } else if (ui->checkBoxUserDefinedReceiverSigmaMultipathModel->isChecked()==true && checked==false) {
         this->on_checkBoxUserDefinedReceiverSigmaMultipathModel_clicked(false);
    }
}
/////////////// End of Group Box buttons ////////////////


////////////////////// Push buttons /////////////////////
void gLAB_GUI::on_pushButtonRinexObs_clicked() {

    QString PlatformSlashType;
#ifdef Q_OS_WIN32
    PlatformSlashType= "\\";
#else
    PlatformSlashType= "/";
#endif

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("RINEX Files (*.??o *o.rnx);;All Files (*)"));
    QString RinexInput;
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRinexObs->setText(QDir::toNativeSeparators(fileName[0]));
            //set output path
            QString OutputPath;
            RinexInput=QDir::toNativeSeparators(fileName[0]);
            int SepOther=RinexInput.lastIndexOf(PlatformSlashType);
            OutputPath=RinexInput.mid(0,SepOther+1)+"gLAB.out";
            ui->lineEditOutputDestination->setText(OutputPath);
            //This code is to change the output filename path with the RINEX observation file path
            /*#ifdef Q_OS_WIN32
                ui->lineEditOutputDestination->setText(QDir::toNativeSeparators(fileName[0]).section("\\",0,-2)+"\\gLAB.out");
            #else
                ui->lineEditOutputDestination->setText(QDir::toNativeSeparators(fileName[0]).section("/",0,-2)+"/gLAB.out");
            #endif
            */
        }
    }
}
void gLAB_GUI::on_pushButtonAddRinexNav_clicked(){
    if (ui->frameInputRinexNavFile2->isHidden()==true) {
        ui->frameInputRinexNavFile2->setHidden(false);
        ui->lineEditRinexNav2->setText("");
        ui->pushButtonDelRinexNav->setEnabled(true);
        //ui->pushButtonDelRinexNav->setStyleSheet(ButtonEnabledStyle);
    } else if (ui->frameInputRinexNavFile3->isHidden()==true) {
        ui->frameInputRinexNavFile3->setHidden(false);
        ui->lineEditRinexNav3->setText("");
    } else if (ui->frameInputRinexNavFile4->isHidden()==true) {
        ui->frameInputRinexNavFile4->setHidden(false);
        ui->lineEditRinexNav4->setText("");
    } else if (ui->frameInputRinexNavFile5->isHidden()==true) {
        ui->frameInputRinexNavFile5->setHidden(false);
        ui->lineEditRinexNav5->setText("");
    } else if (ui->frameInputRinexNavFile6->isHidden()==true) {
        ui->frameInputRinexNavFile6->setHidden(false);
        ui->lineEditRinexNav6->setText("");
    } else if (ui->frameInputRinexNavFile7->isHidden()==true) {
        ui->frameInputRinexNavFile7->setHidden(false);
        ui->lineEditRinexNav7->setText("");
        ui->pushButtonAddRinexNav->setEnabled(false);
        //ui->pushButtonAddRinexNav->setStyleSheet(ButtonDisabledStyle);
    }
    return ;
}
void gLAB_GUI::on_pushButtonDelRinexNav_clicked(){
    if (ui->frameInputRinexNavFile7->isHidden()==false) {
        ui->frameInputRinexNavFile7->setHidden(true);
        ui->lineEditRinexNav7->setText("");
        ui->pushButtonAddRinexNav->setEnabled(true);
        //ui->pushButtonAddRinexNav->setStyleSheet(ButtonEnabledStyle);
    } else if (ui->frameInputRinexNavFile6->isHidden()==false) {
        ui->frameInputRinexNavFile6->setHidden(true);
        ui->lineEditRinexNav6->setText("");
    } else if (ui->frameInputRinexNavFile5->isHidden()==false) {
        ui->frameInputRinexNavFile5->setHidden(true);
        ui->lineEditRinexNav5->setText("");
    } else if (ui->frameInputRinexNavFile4->isHidden()==false) {
        ui->frameInputRinexNavFile4->setHidden(true);
        ui->lineEditRinexNav4->setText("");
    } else if (ui->frameInputRinexNavFile3->isHidden()==false) {
        ui->frameInputRinexNavFile3->setHidden(true);
        ui->lineEditRinexNav3->setText("");
    } else if (ui->frameInputRinexNavFile2->isHidden()==false) {
        ui->frameInputRinexNavFile2->setHidden(true);
        ui->lineEditRinexNav2->setText("");
        ui->pushButtonDelRinexNav->setEnabled(false);
        //ui->pushButtonDelRinexNav->setStyleSheet(ButtonDisabledStyle);
    }
    return ;
}
void gLAB_GUI::on_pushButtonRinexNav1_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.??n *.??g *.??l *.??p *.??h *n.rnx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRinexNav1->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}
void gLAB_GUI::on_pushButtonRinexNav2_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.??n *.??g *.??l *.??p *.??h *n.rnx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRinexNav2->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}
void gLAB_GUI::on_pushButtonRinexNav3_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.??n *.??g *.??l *.??p *.??h *n.rnx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRinexNav3->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}
void gLAB_GUI::on_pushButtonRinexNav4_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.??n *.??g *.??l *.??p *.??h *n.rnx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRinexNav4->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}
void gLAB_GUI::on_pushButtonRinexNav5_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.??n *.??g *.??l *.??p *.??h *n.rnx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRinexNav5->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}
void gLAB_GUI::on_pushButtonRinexNav6_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.??n *.??g *.??l *.??p *.??h *n.rnx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRinexNav6->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}
void gLAB_GUI::on_pushButtonRinexNav7_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.??n *.??g *.??l *.??p *.??h *n.rnx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRinexNav7->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonPrecise1File_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Precise Files (*.sp3 *.eph);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPrecise1File->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_checkBoxRinexNavFileGLO1_clicked(bool checked){
    ui->checkBoxRinexNavFileGLO1->setChecked(checked);
    ui->lineEditRinexNavFileGLO1->setHidden(!checked);
    ui->pushButtonRinexNavFileGLO1->setHidden(!checked);
}
void gLAB_GUI::on_pushButtonRinexNavFileGLO1_clicked(){
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.??n *.??g *.??l *.??p *.??h *n.rnx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRinexNavFileGLO1->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_checkBoxRinexNavFileHealth1_clicked(bool checked){
    ui->checkBoxRinexNavFileHealth1->setChecked(checked);
    ui->lineEditRinexNavFileHealth1->setHidden(!checked);
    ui->pushButtonRinexNavFileHealth1->setHidden(!checked);
    this->on_checkBoxDiscardUnhealthy_clicked(checked);
    if (!checked) {
        this->on_checkBoxDiscardMarginal_clicked(false);
    }
}
void gLAB_GUI::on_pushButtonRinexNavFileHealth1_clicked(){
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.??n *.??g *.??l *.??p *.??h *n.rnx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRinexNavFileHealth1->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonPrecise2Files_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Precise Files (*.sp3 *.eph);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPrecise2Files->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonPreciseClk_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Clock Files (*.clk *.clk_30s *.clk_05s);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPreciseClk->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_checkBoxRinexNavFileGLO2_clicked(bool checked){
    ui->checkBoxRinexNavFileGLO2->setChecked(checked);
    ui->lineEditRinexNavFileGLO2->setHidden(!checked);
    ui->pushButtonRinexNavFileGLO2->setHidden(!checked);
}

void gLAB_GUI::on_pushButtonRinexNavFileGLO2_clicked(){
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.??n *.??g *.??l *.??p *.??h *n.rnx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRinexNavFileGLO2->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_checkBoxRinexNavFileHealth2_clicked(bool checked){
    ui->checkBoxRinexNavFileHealth2->setChecked(checked);
    ui->lineEditRinexNavFileHealth2->setHidden(!checked);
    ui->pushButtonRinexNavFileHealth2->setHidden(!checked);
    this->on_checkBoxDiscardUnhealthy_clicked(checked);
    if (!checked) {
        this->on_checkBoxDiscardMarginal_clicked(false);
    }
}

void gLAB_GUI::on_pushButtonRinexNavFileHealth2_clicked(){
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.??n *.??g *.??l *.??p *.??h *n.rnx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRinexNavFileHealth2->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonSatAntex_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("ANTEX Files (*.atx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditSatAntex->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}
void gLAB_GUI::on_pushButtonRecAntex_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("ANTEX Files (*.atx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRecAntex->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonSinex_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("SINEX Files (*.snx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditSinex->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonReferencePositionFileCalculate_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Text or SP3 Files (*.txt *.sp3 *.eph);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditReferencePositionFileCalculate->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonReferenceFileSpecify_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Text or SP3 Files (*.txt *.sp3 *.eph);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditReferenceFileSpecify->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonReferenceFileRtcm_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Text or SP3 Files (*.txt *.sp3 *.eph);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditReferenceFileRtcm->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonSbas_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("SBAS Files (*.??b *.ems);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditSbas->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonSigmaMultipath_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Sigma Multipath Files (*.txt);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditSigmaMultipath->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonUserAddedError_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("User Added Error Files (*.txt);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditUserAddedError->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonRefStaRinex_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("RINEX Files (*.??o *o.rnx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRefStaRinex->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonRefStaRtcmAuto_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRefStaRtcmAuto->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonRefStaRtcm2_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("RTCM v2.x Files (*.??rtcm2);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRefStaRtcm2->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonRefStaRtcm3_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("RTCM v2.x Files (*.??rtcm3);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditRefStaRtcm3->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_lineEditDcbFile_textChanged(){
    if ( ui->lineEditDcbFile->text().isEmpty() ) {
        ui->comboBoxDCBsfP1C1GPS->setCurrentIndex(0);
    } else {
        ui->comboBoxDCBsfP1C1GPS->setCurrentIndex(1);
    }
}
void gLAB_GUI::on_pushButtonDcbFile_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("DCB Files (*.dcb);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditDcbFile->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonGPSRecType_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("GPS_Receiver_Types Files (*GPS_Receiver_Types*);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditGPSRecType->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonDcbSourceRinexNav_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.??n *.??p *n.rnx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditDcbSourceRinexNav->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonDcbSourceDcb_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("DCB Files (*.dcb);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditDcbSourceDcb->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonDcbSourceIonex_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("IONEX Files (*.??i);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditDcbSourceIonex->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonIonoSourceRinexNav_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.??n *.??p *n.rnx);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditIonoSourceRinexNav->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonIonoSourceIonex_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("IONEX Files (*.??i);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditIonoSourceIonex->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

void gLAB_GUI::on_pushButtonIonoSourceSbasSpecify_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("SBAS Files (*.??b *.ems);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditIonoSourceSbasSpecify->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}
////////////////// End of Push buttons //////////////////


///////////////////// Radio buttons /////////////////////
void gLAB_GUI::on_radioButtonSinex_clicked() {
    ui->stackedWidgetAprioriRecPos->setCurrentIndex(0);
    ui->frameCalculateCoord->setHidden(true);
    ui->stackedWidgetAprioriRecPos->setHidden(false);
    ui->radioButtonSinex->setChecked(true);

    ui->groupBoxSummaryConvergencePosition->setHidden(false);
}

void gLAB_GUI::on_radioButtonCalculate_clicked() {
    ui->radioButtonCalculate->setChecked(true);
    ui->stackedWidgetAprioriRecPos->setCurrentIndex(2);
    ui->stackedWidgetAprioriRecPos->setHidden(false);
    if ( ui->radioButtonCalculateSpecify->isChecked() == true ) {
        ui->frameCalculateCoord->setHidden(false);
    } else { ui->frameCalculateCoord->setHidden(true); }

    ui->groupBoxSummaryConvergencePosition->setHidden(true);
}

void gLAB_GUI::on_radioButtonRinex_clicked() {
    ui->radioButtonRinex->setChecked(true);
    ui->frameCalculateCoord->setHidden(true);
    ui->stackedWidgetAprioriRecPos->setHidden(true);

    ui->groupBoxSummaryConvergencePosition->setHidden(false);
}

void gLAB_GUI::on_radioButtonSpecify_clicked() {
    ui->radioButtonSpecify->setChecked(true);
    ui->stackedWidgetAprioriRecPos->setCurrentIndex(1);
    ui->frameCalculateCoord->setHidden(true);
    ui->stackedWidgetAprioriRecPos->setHidden(false);
    if (ui->radioButtonSpecifyReferenceFile->isChecked()==true) {
        this->on_radioButtonSpecifyReferenceFile_clicked();
    } else {
        this->on_radioButtonSpecifyUserDefined_clicked();
    }

    ui->groupBoxSummaryConvergencePosition->setHidden(false);
}

void gLAB_GUI::on_radioButtonSpecifyUserCartesian_clicked() {
    ui->radioButtonSpecifyUserCartesian->setChecked(true);
    ui->stackedWidgetSpecifyCoordinatesType->setCurrentIndex(0);
}

void gLAB_GUI::on_radioButtonSpecifyUserGeodetic_clicked() {
    ui->radioButtonSpecifyUserGeodetic->setChecked(true);
    ui->stackedWidgetSpecifyCoordinatesType->setCurrentIndex(1);
}

void gLAB_GUI::on_radioButtonSpecifyUserDefined_clicked() {
    ui->radioButtonSpecifyUserDefined->setChecked(true);
    ui->frameReferenceFileSpecify->setHidden(true);
    ui->frameSpecify->setHidden(false);

}

void gLAB_GUI::on_radioButtonSpecifyReferenceFile_clicked() {
    ui->radioButtonSpecifyReferenceFile->setChecked(true);
    ui->frameReferenceFileSpecify->setHidden(false);
    ui->frameSpecify->setHidden(true);
}

void gLAB_GUI::on_radioButtonRtcm_clicked() {
    ui->radioButtonRtcm->setChecked(true);
    ui->frameCalculateCoord->setHidden(true);
    ui->stackedWidgetAprioriRecPos->setCurrentIndex(3);
    ui->stackedWidgetAprioriRecPos->setHidden(false);

    ui->groupBoxSummaryConvergencePosition->setHidden(false);
}

void gLAB_GUI::on_radioButtonCalculateRinex_clicked() {
    ui->radioButtonCalculateRinex->setChecked(true);
    ui->frameCalculateCoord->setHidden(true);
}

void gLAB_GUI::on_radioButtonCalculateSpecify_clicked() {
    ui->radioButtonCalculateSpecify->setChecked(true);
    ui->frameCalculateCoord->setHidden(false);
}

void gLAB_GUI::on_radioButtonCalculateEarthCentre_clicked() {
    ui->radioButtonCalculateEarthCentre->setChecked(true);
    ui->frameCalculateCoord->setHidden(true);
}

void gLAB_GUI::on_radioButtonCalculateSpecifyCartesian_clicked() {
    ui->radioButtonCalculateSpecifyCartesian->setChecked(true);
    ui->stackedWidgetCalculateSpecifyCoordinatesType->setCurrentIndex(0);

}

void gLAB_GUI::on_radioButtonCalculateSpecifyGeodetic_clicked() {
    ui->radioButtonCalculateSpecifyGeodetic->setChecked(true);
    ui->stackedWidgetCalculateSpecifyCoordinatesType->setCurrentIndex(1);

}

void gLAB_GUI::on_radioButtonRtcmBaseline_clicked() {
    ui->radioButtonRtcmBaseline->setChecked(true);
    ui->frameAprioriRecPosRtcmSpecify->setHidden(true);
    ui->frameAprioriRecPosRtcmUserSpecify->setHidden(true);
    ui->frameRTCMRoverSpecifyOptions->setHidden(true);
    ui->frameReferenceFileSpecifyRtcm->setHidden(true);
}

void gLAB_GUI::on_radioButtonRtcmRinexRover_clicked() {
    ui->radioButtonRtcmRinexRover->setChecked(true);
    ui->frameAprioriRecPosRtcmSpecify->setHidden(true);
    ui->frameAprioriRecPosRtcmUserSpecify->setHidden(true);
    ui->frameRTCMRoverSpecifyOptions->setHidden(true);
    ui->frameReferenceFileSpecifyRtcm->setHidden(true);
}

void gLAB_GUI::on_radioButtonRtcmSpecify_clicked() {
    ui->radioButtonRtcmSpecify->setChecked(true);
    ui->frameAprioriRecPosRtcmSpecify->setHidden(false);
    ui->frameAprioriRecPosRtcmUserSpecify->setHidden(true);
    ui->frameRTCMRoverSpecifyOptions->setHidden(false);
    if (ui->radioButtonRtcmUserDefined->isChecked()==true) {
        this->on_radioButtonRtcmUserDefined_clicked();
    } else {
        this->on_radioButtonRtcmReferenceFile_clicked();
    }
}

void gLAB_GUI::on_radioButtonRtcmUserBaseline_clicked() {
    ui->radioButtonRtcmUserBaseline->setChecked(true);
    ui->frameAprioriRecPosRtcmSpecify->setHidden(true);
    ui->frameAprioriRecPosRtcmUserSpecify->setHidden(false);
    ui->frameRTCMRoverSpecifyOptions->setHidden(true);
    ui->frameReferenceFileSpecifyRtcm->setHidden(true);
}

void gLAB_GUI::on_radioButtonRtcmUserRinexRover_clicked() {
    ui->radioButtonRtcmUserRinexRover->setChecked(true);
    ui->frameAprioriRecPosRtcmSpecify->setHidden(true);
    ui->frameAprioriRecPosRtcmUserSpecify->setHidden(false);
    ui->frameRTCMRoverSpecifyOptions->setHidden(true);
    ui->frameReferenceFileSpecifyRtcm->setHidden(true);
}

void gLAB_GUI::on_radioButtonRtcmUserSpecify_clicked() {
    ui->radioButtonRtcmUserSpecify->setChecked(true);
    ui->frameAprioriRecPosRtcmSpecify->setHidden(false);
    ui->frameAprioriRecPosRtcmUserSpecify->setHidden(false);
    ui->frameRTCMRoverSpecifyOptions->setHidden(false);
    if (ui->radioButtonRtcmUserDefined->isChecked()==true) {
        this->on_radioButtonRtcmUserDefined_clicked();
    } else {
        this->on_radioButtonRtcmReferenceFile_clicked();
    }
}

void gLAB_GUI::on_radioButtonRtcmUserDefined_clicked() {
    ui->radioButtonRtcmUserDefined->setChecked(true);
    ui->frameReferenceFileSpecifyRtcm->setHidden(true);
    ui->frameAprioriRecPosRtcmSpecify->setHidden(false);
}

void gLAB_GUI::on_radioButtonRtcmReferenceFile_clicked() {
    ui->radioButtonRtcmReferenceFile->setChecked(true);
    ui->frameReferenceFileSpecifyRtcm->setHidden(false);
    ui->frameAprioriRecPosRtcmSpecify->setHidden(true);
}

void gLAB_GUI::on_radioButtonRtcmRecCartesian_clicked() {
    ui->radioButtonRtcmRecCartesian->setChecked(true);
    ui->stackedWidgetRtcmRecCoordinateType->setCurrentIndex(0);
}

void gLAB_GUI::on_radioButtonRtcmRecGeodeticCoord_clicked() {
    ui->radioButtonRtcmRecGeodeticCoord->setChecked(true);
    ui->stackedWidgetRtcmRecCoordinateType->setCurrentIndex(1);
}

void gLAB_GUI::on_radioButtonRtcmRefCartesian_clicked() {
    ui->radioButtonRtcmRefCartesian->setChecked(true);
    ui->stackedWidgetRtcmRefCoordinateType->setCurrentIndex(0);
}

void gLAB_GUI::on_radioButtonRtcmRefGeodetic_clicked() {
    ui->radioButtonRtcmRefGeodetic->setChecked(true);
    ui->stackedWidgetRtcmRefCoordinateType->setCurrentIndex(1);
}

void gLAB_GUI::on_radioButtonIonoSourceBrdc_clicked() {
    ui->stackedWidgetIonoSource->setCurrentIndex(0);
    ui->radioButtonIonoSourceBrdc->setChecked(true);
    ui->radioButtonIonoSourceIonex->setChecked(false);
    ui->radioButtonIonoSourceSbas->setChecked(false);
    //This is to make sure the BRDC specify LineEdit stays hidden
    if (ui->comboBoxIonoSourceBrdc->currentIndex()==0) {
        this->on_comboBoxIonoSourceBrdc_currentIndexChanged(0);
    }
}

void gLAB_GUI::on_radioButtonIonoSourceIonex_clicked() {
    ui->stackedWidgetIonoSource->setCurrentIndex(1);
    ui->radioButtonIonoSourceBrdc->setChecked(false);
    ui->radioButtonIonoSourceIonex->setChecked(true);
    ui->radioButtonIonoSourceSbas->setChecked(false);
    ui->comboBoxIonoCorrection->setCurrentIndex(3);
    if (ui->comboBoxDCBsfP1P2GPS->currentIndex()<3) ui->comboBoxDCBsfP1P2GPS->setCurrentIndex(3);
}

void gLAB_GUI::on_radioButtonIonoSourceSbas_clicked() {
    ui->stackedWidgetIonoSource->setCurrentIndex(2);
    ui->radioButtonIonoSourceBrdc->setChecked(false);
    ui->radioButtonIonoSourceIonex->setChecked(false);
    ui->radioButtonIonoSourceSbas->setChecked(true);
    ui->comboBoxIonoCorrection->setCurrentIndex(4);
}

void gLAB_GUI::on_radioButtonOrbitBrdc_clicked() {
    if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
        mode=0;
    }

    ui->stackedWidgetOrbitAndClock->setCurrentIndex(0);
    ui->radioButtonOrbitBrdc->setChecked(true);
    ui->radioButtonOrbitPrecise1file->setChecked(false);
    ui->radioButtonOrbitPrecise2files->setChecked(false);
    ui->frameAddDelRinexNav->setHidden(false);
    ui->groupBoxPreciseProductsDataInterpolation->setHidden(true);
    ui->stackedWidgetcomboBoxIonoSourceBrdc->setCurrentIndex(0);
    ui->stackedWidgetComboBoxDcbSource->setCurrentIndex(0);
    if(ui->comboBoxDcbSource->currentIndex()==0) {
        ui->stackedWidgetDcbSource->setCurrentIndex(0);
    } else if(ui->comboBoxDcbSource->currentIndex()==1) {
        ui->stackedWidgetDcbSource->setCurrentIndex(1);
    }
    if (ui->comboBoxIonoSourceBrdc->currentIndex()==0) {
        ui->stackedWidgetIonoSourceBrdc->setCurrentIndex(0);
    } else {
        ui->stackedWidgetIonoSourceBrdc->setCurrentIndex(1);
    }
    ui->checkBoxDiscardUnhealthy->setHidden(false);

    ui->frameInputRinexNavFile1->setHidden(false);
    //ui->lineEditRinexNav1->setText("");
    if (ui->frameInputRinexNavFile2->isHidden()) {
        ui->pushButtonAddRinexNav->setEnabled(true);
        ui->pushButtonDelRinexNav->setEnabled(false);
    }

    ui->groupBoxNavMessageTypes->setHidden(false);
    if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
        this->on_pushButtonNavMessageTypesSetDefault_clicked();
    }
}


void gLAB_GUI::on_radioButtonOrbitPrecise1file_clicked() {
    mode=1;

    ui->stackedWidgetOrbitAndClock->setCurrentIndex(1);
    ui->radioButtonOrbitPrecise1file->setChecked(true);
    ui->radioButtonOrbitBrdc->setChecked(false);
    ui->radioButtonOrbitPrecise2files->setChecked(false);
    ui->frameAddDelRinexNav->setHidden(true);
    ui->groupBoxPreciseProductsDataInterpolation->setHidden(false);
    ui->stackedWidgetcomboBoxIonoSourceBrdc->setCurrentIndex(1);
    ui->stackedWidgetIonoSourceBrdc->setCurrentIndex(1);
    ui->stackedWidgetComboBoxDcbSource->setCurrentIndex(1);
    if(ui->comboBoxDcbSourcePPP->currentIndex()==0) {
        ui->stackedWidgetDcbSource->setCurrentIndex(1);
    }
    /*if (ui->groupBoxP1P2correction->isChecked()==false || (ui->groupBoxP1P2correction->isChecked()==true && ui->comboBoxDcbSourcePPP->currentIndex()==0)) {
        ui->checkBoxDiscardUnhealthy->setHidden(true);
    }*/

    ui->groupBoxNavMessageTypes->setHidden(true);
}

void gLAB_GUI::on_radioButtonOrbitPrecise2files_clicked() {
    mode=1;
    ui->stackedWidgetOrbitAndClock->setCurrentIndex(2);
    ui->radioButtonOrbitPrecise2files->setChecked(true);
    ui->radioButtonOrbitBrdc->setChecked(false);
    ui->radioButtonOrbitPrecise1file->setChecked(false);
    ui->frameAddDelRinexNav->setHidden(true);
    ui->groupBoxPreciseProductsDataInterpolation->setHidden(false);
    ui->stackedWidgetcomboBoxIonoSourceBrdc->setCurrentIndex(1);
    ui->stackedWidgetIonoSourceBrdc->setCurrentIndex(1);
    ui->stackedWidgetComboBoxDcbSource->setCurrentIndex(1);
    if(ui->comboBoxDcbSourcePPP->currentIndex()==0) {
        ui->stackedWidgetDcbSource->setCurrentIndex(1);
    }
    /*if (ui->groupBoxP1P2correction->isChecked()==false || (ui->groupBoxP1P2correction->isChecked()==true && ui->comboBoxDcbSourcePPP->currentIndex()==0)) {
        ui->checkBoxDiscardUnhealthy->setHidden(true);
    }*/

    ui->groupBoxNavMessageTypes->setHidden(true);
}

void gLAB_GUI::on_radioButtonGPSReceiverTypeFile_clicked() {
    ui->radioButtonGPSReceiverTypeFile->setChecked(true);
    ui->stackedWidgetGPSReceiverType->setCurrentIndex(0);
}

void gLAB_GUI::on_radioButtonGPSReceiverTypeUserSelection_clicked() {
    ui->radioButtonGPSReceiverTypeUserSelection->setChecked(true);
    ui->stackedWidgetGPSReceiverType->setCurrentIndex(1);
}

///////////////// End of Radio buttons //////////////////

///////////////// Start of Context menus (right-click menus) //////////////////
//Right-click menu in Input RINEX observation File label
void gLAB_GUI::labelInputRinexObsFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputObservationFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
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
            arguments << ui->lineEditRinexObs->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditRinexObs->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditRinexObs->text();
        #endif

        // Execute the program
        if (ui->lineEditRinexObs->text() == "") {
            messageBox.warning(nullptr, "Error","RINEX Observation file is empty\n");
        } else if  (this->fileExists(ui->lineEditRinexObs->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexObs->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexObs->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::checkBoxInputSatANTEXFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->checkBoxSatAntex->mapToGlobal(pos);
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
            arguments << ui->lineEditSatAntex->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditSatAntex->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditSatAntex->text();
        #endif

        // Execute the program
        if (ui->lineEditSatAntex->text() == "") {
            messageBox.warning(nullptr, "Error","ANTEX file is empty\n");
        } else if (this->fileExists(ui->lineEditSatAntex->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditSatAntex->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditSatAntex->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::checkBoxInputRecANTEXFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->checkBoxRecAntex->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open Receiver ANTEX File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditRecAntex->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditRecAntex->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditRecAntex->text();
        #endif

        // Execute the program
        if (ui->lineEditRecAntex->text() == "") {
            messageBox.warning(nullptr, "Error","Receiver ANTEX file is empty\n");
        } else if (this->fileExists(ui->lineEditRecAntex->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRecAntex->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRecAntex->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelInputRinexNavFile1Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputRinexNavFile1->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
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
            arguments << ui->lineEditRinexNav1->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditRinexNav1->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditRinexNav1->text();
        #endif

        // Execute the program
        if (ui->lineEditRinexNav1->text() == "") {
            messageBox.warning(nullptr, "Error","RINEX Navigation file 1 is empty\n");
        } else if (this->fileExists(ui->lineEditRinexNav1->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNav1->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNav1->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}
void gLAB_GUI::labelInputRinexNavFile2Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputRinexNavFile2->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
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
            arguments << ui->lineEditRinexNav2->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditRinexNav2->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditRinexNav2->text();
        #endif

        // Execute the program
        if (ui->lineEditRinexNav2->text() == "") {
            messageBox.warning(nullptr, "Error","RINEX Navigation file 2 is empty\n");
        } else if (this->fileExists(ui->lineEditRinexNav2->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNav2->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNav2->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}
void gLAB_GUI::labelInputRinexNavFile3Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputRinexNavFile3->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open RINEX Navigation File 3");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditRinexNav3->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditRinexNav3->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditRinexNav3->text();
        #endif

        // Execute the program
        if (ui->lineEditRinexNav3->text() == "") {
            messageBox.warning(nullptr, "Error","RINEX Navigation file 3 is empty\n");
        } else if (this->fileExists(ui->lineEditRinexNav3->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNav3->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNav3->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}
void gLAB_GUI::labelInputRinexNavFile4Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputRinexNavFile4->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open RINEX Navigation File 4");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditRinexNav4->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditRinexNav4->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditRinexNav4->text();
        #endif

        // Execute the program
        if (ui->lineEditRinexNav4->text() == "") {
            messageBox.warning(nullptr, "Error","RINEX Navigation file 4 is empty\n");
        } else if (this->fileExists(ui->lineEditRinexNav4->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNav4->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNav4->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}
void gLAB_GUI::labelInputRinexNavFile5Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputRinexNavFile5->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open RINEX Navigation File 5");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditRinexNav5->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditRinexNav5->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditRinexNav5->text();
        #endif

        // Execute the program
        if (ui->lineEditRinexNav5->text() == "") {
            messageBox.warning(nullptr, "Error","RINEX Navigation file 5 is empty\n");
        } else if (this->fileExists(ui->lineEditRinexNav5->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNav5->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNav5->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}
void gLAB_GUI::labelInputRinexNavFile6Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputRinexNavFile6->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open RINEX Navigation File 6");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditRinexNav6->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditRinexNav6->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditRinexNav6->text();
        #endif

        // Execute the program
        if (ui->lineEditRinexNav6->text() == "") {
            messageBox.warning(nullptr, "Error","RINEX Navigation file 6 is empty\n");
        } else if (this->fileExists(ui->lineEditRinexNav6->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNav6->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNav6->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}
void gLAB_GUI::labelInputRinexNavFile7Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputRinexNavFile7->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open RINEX Navigation File 7");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditRinexNav7->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditRinexNav7->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditRinexNav7->text();
        #endif

        // Execute the program
        if (ui->lineEditRinexNav7->text() == "") {
            messageBox.warning(nullptr, "Error","RINEX Navigation file 7 is empty\n");
        } else if (this->fileExists(ui->lineEditRinexNav7->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNav7->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNav7->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelInputSP3OrbitsClocksFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputSP3OrbitsClocksFile->mapToGlobal(pos);
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
            arguments << ui->lineEditPrecise1File->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPrecise1File->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPrecise1File->text();
        #endif

        // Execute the program
        if (ui->lineEditPrecise1File->text() == "") {
            messageBox.warning(nullptr, "Error","SP3 file is empty\n");
        } else if (this->fileExists(ui->lineEditPrecise1File->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPrecise1File->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPrecise1File->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelInputSP3OrbitsFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputSP3OrbitsFile->mapToGlobal(pos);
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
            arguments << ui->lineEditPrecise2Files->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPrecise2Files->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPrecise2Files->text();
        #endif

        // Execute the program
        if (ui->lineEditPrecise2Files->text() == "") {
            messageBox.warning(nullptr, "Error","SP3 file is empty\n");
        } else if (this->fileExists(ui->lineEditPrecise2Files->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPrecise2Files->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPrecise2Files->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelInputClocksFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputClkFile->mapToGlobal(pos);
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
            arguments << ui->lineEditPreciseClk->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPreciseClk->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPreciseClk->text();
        #endif

        // Execute the program
        if (ui->lineEditPreciseClk->text() == "") {
            messageBox.warning(nullptr, "Error","Clock file is empty\n");
        } else if (this->fileExists(ui->lineEditPreciseClk->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseClk->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseClk->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::checkBoxRinexNavFileGLO1Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->checkBoxRinexNavFileGLO1->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open GLONASS RINEX Navigation File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditRinexNavFileGLO1->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditRinexNavFileGLO1->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditRinexNavFileGLO1->text();
        #endif

        // Execute the program
        if (ui->lineEditRinexNavFileGLO1->text() == "") {
            messageBox.warning(nullptr, "Error","GLONASS RINEX Navigation File is empty\n");
        } else if (this->fileExists(ui->lineEditRinexNavFileGLO1->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNavFileGLO1->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNavFileGLO1->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::checkBoxRinexNavFileHealth1Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->checkBoxRinexNavFileHealth1->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open RINEX Navigation File for Health Flags");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditRinexNavFileHealth1->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditRinexNavFileHealth1->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditRinexNavFileHealth1->text();
        #endif

        // Execute the program
        if (ui->lineEditRinexNavFileHealth1->text() == "") {
            messageBox.warning(nullptr, "Error","RINEX Navigation File for Health Flags is empty\n");
        } else if (this->fileExists(ui->lineEditRinexNavFileHealth1->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNavFileHealth1->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNavFileHealth1->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::checkBoxRinexNavFileGLO2Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->checkBoxRinexNavFileGLO2->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open GLONASS RINEX Navigation File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditRinexNavFileGLO2->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditRinexNavFileGLO2->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditRinexNavFileGLO2->text();
        #endif

        // Execute the program
        if (ui->lineEditRinexNavFileGLO2->text() == "") {
            messageBox.warning(nullptr, "Error","GLONASS RINEX Navigation File is empty\n");
        } else if (this->fileExists(ui->lineEditRinexNavFileGLO2->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNavFileGLO2->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNavFileGLO2->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::checkBoxRinexNavFileHealth2Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->checkBoxRinexNavFileHealth1->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open RINEX Navigation File for Health Flags");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditRinexNavFileHealth2->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditRinexNavFileHealth2->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditRinexNavFileHealth2->text();
        #endif

        // Execute the program
        if (ui->lineEditRinexNavFileHealth2->text() == "") {
            messageBox.warning(nullptr, "Error","RINEX Navigation File for Health Flags is empty\n");
        } else if (this->fileExists(ui->lineEditRinexNavFileHealth2->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNavFileHealth2->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditRinexNavFileHealth2->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelInputSINEXFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputSinexFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open SINEX File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditSinex->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditSinex->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditSinex->text();
        #endif

        // Execute the program
        if (ui->lineEditSinex->text() == "") {
            messageBox.warning(nullptr, "Error","SINEX file is empty\n");
        } else if (this->fileExists(ui->lineEditSinex->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditSinex->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditSinex->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelInputSBASFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->comboBoxSbasInput->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
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
            arguments << ui->lineEditSbas->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditSbas->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditSbas->text();
        #endif

        // Execute the program
        if (ui->lineEditSbas->text() == "") {
            messageBox.warning(nullptr, "Error","SBAS file is empty\n");
        } else if (this->fileExists(ui->lineEditSbas->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditSbas->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditSbas->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::comboBoxRefStationFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->comboBoxRefStation->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QString file;
    switch (ui->comboBoxRefStation->currentIndex()) {
    case 0:
        myMenu.addAction("Open RINEX Observation File");
        file = ui->lineEditRefStaRinex->text();
        break;
    case 1:
        myMenu.addAction("Open RTCM File");
        file = ui->lineEditRefStaRtcmAuto->text();
        break;
    case 2:
        myMenu.addAction("Open RTCM v2.x File");
        file = ui->lineEditRefStaRtcm2->text();
        break;
    case 3:
        myMenu.addAction("Open RTCM v3.x File");
        file = ui->lineEditRefStaRtcm3->text();
        break;
    default:
        break;
    }


    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QMessageBox messageBox;
        messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
        QMessageBox::StandardButton reply;

        //If file is a binary file
        if ( ui->comboBoxRefStation->currentIndex()>0 ) {
            reply = QMessageBox::warning(this, "Binary file",
                           QString("RTCM files are binary files. Opening a binary file with a text editor will probably corrupt it.\nAre you sure you want to continue?\n"),
                           QMessageBox::Yes|QMessageBox::No);
            if ( reply == QMessageBox::No ) {
                return;
            }
        }

        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << file;
        #elif defined(Q_OS_WIN32)
            if(ui->comboBoxRefStation->currentIndex()==0) {
                QString programFilesPath(getenv("PROGRAMFILES"));
                program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            } else {
                //Binary files may be better opened in notepad rather than wordpad
                program = QString("notepad");
            }
            arguments << file;
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << file;
        #endif

        // Execute the program
        if (file == "") {
            messageBox.warning(nullptr, "Error","DGNSS file is empty\n");
        } else if (this->fileExists(file)==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + file + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + file + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelInputRinexNavIonoFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputRinexNavIonoFile->mapToGlobal(pos);
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
            arguments << ui->lineEditIonoSourceRinexNav->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditIonoSourceRinexNav->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditIonoSourceRinexNav->text();
        #endif

        // Execute the program
        if (ui->lineEditIonoSourceRinexNav->text() == "") {
            messageBox.warning(nullptr, "Error","RINEX Navigation file is empty\n");
        } else if (this->fileExists(ui->lineEditIonoSourceRinexNav->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditIonoSourceRinexNav->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditIonoSourceRinexNav->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelInputIonexIonoFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputIonexIonoFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open IONEX File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditIonoSourceIonex->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditIonoSourceIonex->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditIonoSourceIonex->text();
        #endif

        // Execute the program
        if (ui->lineEditIonoSourceIonex->text() == "") {
            messageBox.warning(nullptr, "Error","IONEX file is empty\n");
        } else if (this->fileExists(ui->lineEditIonoSourceIonex->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditIonoSourceIonex->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditIonoSourceIonex->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelInputSbasIonoFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputSbasIonoFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
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
            arguments << ui->lineEditIonoSourceSbasSpecify->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditIonoSourceSbasSpecify->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditIonoSourceSbasSpecify->text();
        #endif

        // Execute the program
        if (ui->lineEditIonoSourceSbasSpecify->text() == "") {
            messageBox.warning(nullptr, "Error","SBAS file is empty\n");
        } else if (this->fileExists(ui->lineEditIonoSourceSbasSpecify->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditIonoSourceSbasSpecify->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditIonoSourceSbasSpecify->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelInputDCBP1C1FileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputDCBP1C1File->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open P1-C1 DCB File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditDcbFile->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditDcbFile->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditDcbFile->text();
        #endif

        // Execute the program
        if (ui->lineEditDcbFile->text() == "") {
            messageBox.warning(nullptr, "Error","P1-C1 DCB file is empty\n");
        } else if (this->fileExists(ui->lineEditDcbFile->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditDcbFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditDcbFile->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelInputGPSRecFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputGPSRecFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open GPS Receiver Types File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditGPSRecType->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditGPSRecType->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditGPSRecType->text();
        #endif

        // Execute the program
        if (ui->lineEditGPSRecType->text() == "") {
            messageBox.warning(nullptr, "Error","GPS Receiver Types file is empty\n");
        } else if (this->fileExists(ui->lineEditGPSRecType->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditGPSRecType->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditGPSRecType->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelInputRinexNavDCBFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputRinexNavDCBFile->mapToGlobal(pos);
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
            arguments << ui->lineEditDcbSourceRinexNav->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditDcbSourceRinexNav->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditDcbSourceRinexNav->text();
        #endif

        // Execute the program
        if (ui->lineEditDcbSourceRinexNav->text() == "") {
            messageBox.warning(nullptr, "Error","RINEX Navigation file is empty\n");
        } else if (this->fileExists(ui->lineEditDcbSourceRinexNav->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditDcbSourceRinexNav->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditDcbSourceRinexNav->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelInputDCBP1P2FileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputDCBP1P2File->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open P1-P2 DCB File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditDcbSourceDcb->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditDcbSourceDcb->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditDcbSourceDcb->text();
        #endif

        // Execute the program
        if (ui->lineEditDcbSourceDcb->text() == "") {
            messageBox.warning(nullptr, "Error","P1-P2 DCB file is empty\n");
        } else if (this->fileExists(ui->lineEditDcbSourceDcb->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditDcbSourceDcb->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditDcbSourceDcb->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelInputIonexDCBFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputIonexDCBFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open IONEX File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditDcbSourceIonex->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditDcbSourceIonex->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditDcbSourceIonex->text();
        #endif

        // Execute the program
        if (ui->lineEditDcbSourceIonex->text() == "") {
            messageBox.warning(nullptr, "Error","IONEX file is empty\n");
        } else if (this->fileExists(ui->lineEditDcbSourceIonex->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditDcbSourceIonex->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditDcbSourceIonex->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelInputUserAddedErrorFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputUserAddedErrorFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open User Added Error Text File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditUserAddedError->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditUserAddedError->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditUserAddedError->text();
        #endif

        // Execute the program
        if (ui->lineEditUserAddedError->text() == "") {
            messageBox.warning(nullptr, "Error","User Added Error Text file is empty\n");
        } else if (this->fileExists(ui->lineEditUserAddedError->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditUserAddedError->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditUserAddedError->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelInputSigmaMultipathFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelInputSigmaMultipathFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open Sigma Multipath Text File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditSigmaMultipath->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditSigmaMultipath->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditSigmaMultipath->text();
        #endif

        // Execute the program
        if (ui->lineEditSigmaMultipath->text() == "") {
            messageBox.warning(nullptr, "Error","Sigma Multipath Text file is empty\n");
        } else if (this->fileExists(ui->lineEditSigmaMultipath->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditSigmaMultipath->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditSigmaMultipath->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelReferenceFileRtcmFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelReferenceFileRtcm->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open Reference Position File for Rover");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditReferenceFileRtcm->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditReferenceFileRtcm->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditReferenceFileRtcm->text();
        #endif

        // Execute the program
        if (ui->lineEditReferenceFileRtcm->text() == "") {
            messageBox.warning(nullptr, "Error","Reference Position File for Rover is empty\n");
        } else if (this->fileExists(ui->lineEditReferenceFileRtcm->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditReferenceFileRtcm->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditReferenceFileRtcm->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelReferenceFileSpecifyFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelReferenceFileSpecify->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open Reference Position File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditReferenceFileSpecify->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditReferenceFileSpecify->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditReferenceFileSpecify->text();
        #endif

        // Execute the program
        if (ui->lineEditReferenceFileSpecify->text() == "") {
            messageBox.warning(nullptr, "Error","Reference Position file is empty\n");
        } else if (this->fileExists(ui->lineEditReferenceFileSpecify->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditReferenceFileSpecify->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditReferenceFileSpecify->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::checkBoxReferencePositionFileCalculateFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->checkBoxReferencePositionFileCalculate->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open Reference Position File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditReferencePositionFileCalculate->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditReferencePositionFileCalculate->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditReferencePositionFileCalculate->text();
        #endif

        // Execute the program
        if (ui->lineEditReferencePositionFileCalculate->text() == "") {
            messageBox.warning(nullptr, "Error","Reference Position file is empty\n");
        } else if (this->fileExists(ui->lineEditReferencePositionFileCalculate->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditReferencePositionFileCalculate->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditReferencePositionFileCalculate->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}
///////////////// End of Context menus (right-click menus) //////////////////


// Function to get the INPUT options and errors
void gLAB_GUI::getInputOptions(QString *errorString, QString *warningString, QString *saveString,QStringList *runString) {
    QString RtcmNavMode;
    QStringList NavPath;
    // Header of the Input section
    *errorString = "";
    *warningString="";
    *saveString = "###################################################\n";
    *saveString += "#     INPUT section\n";
    *saveString += "###################################################\n\n";
    // Rover (User)
    QString rinexObs = ui->lineEditRinexObs->text();
    if ( rinexObs == "" ) {
        *errorString += "INPUT: RINEX Observation file is a required input.\n";
    } else if (this->fileExists(ui->lineEditRinexObs->text())==false) {
        *errorString += "INPUT: RINEX Observation file does not exist.\n";
    } else if (this->checknonASCIIcharacters(ui->lineEditRinexObs->text())==1) {
        *errorString += "INPUT: RINEX Observation file has non ASCII characters\n";
    } else {
        *saveString += "-input:obs " + ui->lineEditRinexObs->text() + "\n";
        *runString << "-input:obs" << ui->lineEditRinexObs->text();
    }
    if ( ui->checkBoxSatAntex->isChecked() == true ) {
        if ( ui->lineEditSatAntex->text() == "" ) {
            *errorString += "INPUT: Satellite ANTEX file is a required input if 'ANTEX File' is specified.\n";
        } else if (this->fileExists(ui->lineEditSatAntex->text())==false) {
            *errorString += "INPUT: Satellite ANTEX file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditSatAntex->text())==1) {
            *errorString += "INPUT: Satellite ANTEX  file has non ASCII characters\n";
        } else {
            if (ui->checkBoxAntennaPhase->isChecked()==false && (ui->labelCurrentTemplate->text()=="SPP"||ui->labelCurrentTemplate->text()=="SBAS 1F"||ui->labelCurrentTemplate->text()=="SBAS DFMC"||ui->labelCurrentTemplate->text()=="DGNSS")){
                *saveString += "-input:antsatblock " + ui->lineEditSatAntex->text() + "\n";
                *runString << "-input:antsatblock" << ui->lineEditSatAntex->text();
            } else {
                *saveString += "-input:ant " + ui->lineEditSatAntex->text() + "\n";
                *runString << "-input:ant" << ui->lineEditSatAntex->text();
            }
        }
    }
    if ( ui->checkBoxRecAntex->isChecked() == true ) {
        if ( ui->lineEditRecAntex->text() == "" ) {
            *errorString += "INPUT: Receiver ANTEX file is a required input if 'ANTEX File' is specified.\n";
        } else if (this->fileExists(ui->lineEditRecAntex->text())==false) {
            *errorString += "INPUT: Receiver ANTEX file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditRecAntex->text())==1) {
            *errorString += "INPUT: Receiver ANTEX  file has non ASCII characters\n";
        } else {
            *saveString += "-input:antrec " + ui->lineEditRecAntex->text() + "\n";
            *runString << "-input:antrec" << ui->lineEditRecAntex->text();
        }
    }
    if ( ui->radioButtonOrbitBrdc->isChecked() == true ) {
        int noFileCount=0,okFileCount=0,nRepNavFile=0;
        QString repErrorBuff="",missBuff="";
        int NavRepetitionIndex[7]={7,6,5,4,3,2,1};
        NavPath.clear();
        NavPath.push_back(ui->lineEditRinexNav1->text());
        NavPath.push_back(ui->lineEditRinexNav2->text());
        NavPath.push_back(ui->lineEditRinexNav3->text());
        NavPath.push_back(ui->lineEditRinexNav4->text());
        NavPath.push_back(ui->lineEditRinexNav5->text());
        NavPath.push_back(ui->lineEditRinexNav6->text());
        NavPath.push_back(ui->lineEditRinexNav7->text());
        for (int i=0;i<7;i++){
            QString nNAV=QString::number(i+1);
            if ( NavPath[i] == "" ) {
                missBuff += "INPUT: RINEX Broadcast navigation file " + nNAV + " is missing.\n";
                noFileCount++;
            } else if (this->fileExists(NavPath[i])==false) {
                *errorString += "INPUT: RINEX Broadcast navigation file " + nNAV + " does not exist.\n";
            } else if (this->checknonASCIIcharacters(NavPath[i])==1) {
                *errorString += "INPUT: RINEX Broadcast navigation file " + nNAV + " has non ASCII characters\n";
            } else {
                for (int iNav=1;iNav<NavRepetitionIndex[i];iNav++){
                    if ( NavPath[i]!="" && NavPath[i]==NavPath[i+iNav] ){
                        QString nRepNav=QString::number(i+iNav+1);
                        nRepNavFile++;
                        repErrorBuff += (nRepNavFile==1? " file ":", file ") + nNAV + " is the same as file" + nRepNav;
                    }
                }
                if (okFileCount==0) {
                    *saveString += "-input:nav " + NavPath[i] + "\n";
                    *runString << "-input:nav" << NavPath[i];
                } else {
                    *saveString += "-input:nav " + NavPath[i] + "\n";
                    *runString << NavPath[i];
                }
                okFileCount++;
            }
        }
        if (noFileCount>=7) {
            *errorString += "INPUT: RINEX broadcast navigation file (none provided).\n";
        }
        if (nRepNavFile>0){
            *errorString += "INPUT: RINEX Broadcast navigation files are Repeated:" + repErrorBuff + "\n";
        }
    }
    if ( ui->radioButtonOrbitPrecise1file->isChecked() == true ) {
        if ( ui->lineEditPrecise1File->text() == "" ) {
            *errorString += "INPUT: SP3 file is a required input if 'Precise (1 file)' orbit and clock source is specified.\n";
        } else if (this->fileExists(ui->lineEditPrecise1File->text())==false) {
            *errorString += "INPUT: SP3 file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPrecise1File->text())==1) {
            *errorString += "INPUT: SP3 file has non ASCII characters\n";
        } else {
            *saveString += "-input:sp3 " + ui->lineEditPrecise1File->text() + "\n";
            *runString << "-input:sp3" << ui->lineEditPrecise1File->text();
        }
        if ( ui->checkBoxRinexNavFileGLO1->isHidden()==false && ui->checkBoxRinexNavFileGLO1->isChecked() ){
            if ( ui->lineEditRinexNavFileGLO1->text() == "" ) {
                *errorString += "INPUT: GLONASS RINEX navigation file is a required input in 'Precise (1 file)' if GLONASS is selected.\n";
            } else if (this->fileExists(ui->lineEditRinexNavFileGLO1->text())==false) {
                *errorString += "INPUT: GLONASS RINEX navigation file does not exist.\n";
            } else if (this->checknonASCIIcharacters(ui->lineEditRinexNavFileGLO1->text())==1) {
                *errorString += "INPUT: GLONASS RINEX navigation file has non ASCII characters\n";
            } else {
                *saveString += "-input:navglo " + ui->lineEditRinexNavFileGLO1->text() + "\n";
                *runString << "-input:navglo" << ui->lineEditRinexNavFileGLO1->text();
            }
        }
        if ( ui->checkBoxRinexNavFileHealth1->isHidden()==false && ui->checkBoxRinexNavFileHealth1->isChecked() ){
            if ( ui->lineEditRinexNavFileHealth1->text() == "" ) {
                *errorString += "INPUT: RINEX navigation File for Health flags is a required input in 'Precise (1 file)'.\n";
            } else if (this->fileExists(ui->lineEditRinexNavFileHealth1->text())==false) {
                *errorString += "INPUT: RINEX navigation File for Health flags does not exist.\n";
            } else if (this->checknonASCIIcharacters(ui->lineEditRinexNavFileHealth1->text())==1) {
                *errorString += "INPUT: RINEX navigation File for Health flags has non ASCII characters\n";
            } else {
                *saveString += "-input:navhealth " + ui->lineEditRinexNavFileHealth1->text() + "\n";
                *runString << "-input:navhealth" << ui->lineEditRinexNavFileHealth1->text();
            }
        }
    }
    if ( ui->radioButtonOrbitPrecise2files->isChecked() == true ) {
        if ( ui->lineEditPrecise2Files->text() == "" ) {
            *errorString += "INPUT: SP3 orbit file is a required input if 'Precise (2 files)' orbit and clock source is specified.\n";
        } else if (this->fileExists(ui->lineEditPrecise2Files->text())==false) {
            *errorString += "INPUT: SP3 orbit file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPrecise2Files->text())==1) {
            *errorString += "INPUT: SP3 orbit file has non ASCII characters\n";
        } else {
            *saveString += "-input:orb " + ui->lineEditPrecise2Files->text() + "\n";
            *runString << "-input:orb" << ui->lineEditPrecise2Files->text();
        }
        QString clkFile = ui->lineEditPreciseClk->text();
        if ( ui->lineEditPreciseClk->text() == "" ) {
            *errorString += "INPUT: RINEX clocks file is a required input if 'Precise (2 files)' orbit and clock source is specified.\n";
        } else if (this->fileExists(ui->lineEditPreciseClk->text())==false) {
            *errorString += "INPUT: RINEX clocks file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPreciseClk->text())==1) {
            *errorString += "INPUT: RINEX clocks file has non ASCII characters\n";
        } else {
            *saveString += "-input:clk " + ui->lineEditPreciseClk->text() + "\n";
            *runString << "-input:clk" << ui->lineEditPreciseClk->text();
        }
        if ( ui->checkBoxRinexNavFileGLO2->isHidden()==false && ui->checkBoxRinexNavFileGLO2->isChecked() ){
            if ( ui->lineEditRinexNavFileGLO2->text() == "" ) {
                *errorString += "INPUT: GLONASS RINEX navigation file is a required input in 'Precise (1 file)' if GLONASS is selected.\n";
            } else if (this->fileExists(ui->lineEditRinexNavFileGLO2->text())==false) {
                *errorString += "INPUT: GLONASS RINEX navigation file does not exist.\n";
            } else if (this->checknonASCIIcharacters(ui->lineEditRinexNavFileGLO2->text())==1) {
                *errorString += "INPUT: GLONASS RINEX navigation file has non ASCII characters\n";
            } else {
                *saveString += "-input:navglo " + ui->lineEditRinexNavFileGLO2->text() + "\n";
                *runString << "-input:navglo" << ui->lineEditRinexNavFileGLO2->text();
            }
        }
        if ( ui->checkBoxRinexNavFileHealth2->isHidden()==false && ui->checkBoxRinexNavFileHealth2->isChecked() ){
            if ( ui->lineEditRinexNavFileHealth2->text() == "" ) {
                *errorString += "INPUT: RINEX navigation File for Health flags is a required input in 'Precise (1 file)'.\n";
            } else if (this->fileExists(ui->lineEditRinexNavFileHealth2->text())==false) {
                *errorString += "INPUT: RINEX navigation File for Health flags does not exist.\n";
            } else if (this->checknonASCIIcharacters(ui->lineEditRinexNavFileHealth2->text())==1) {
                *errorString += "INPUT: RINEX navigation File for Health flags has non ASCII characters\n";
            } else {
                *saveString += "-input:navhealth " + ui->lineEditRinexNavFileHealth2->text() + "\n";
                *runString << "-input:navhealth" << ui->lineEditRinexNavFileHealth2->text();
            }
        }
    }
    // A Priori Receiver Position From
    if ( ui->radioButtonSinex->isChecked() == true ) {
        if ( ui->lineEditSinex->text() == "" ) {
            *errorString += "INPUT: SINEX file is a required input if 'SINEX' as 'A Priori Receiver Position From:' is specified.\n";
        } else if (this->fileExists(ui->lineEditSinex->text())==false) {
            *errorString += "INPUT: SINEX file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditSinex->text())==1) {
            *errorString += "INPUT: SINEX clocks file has non ASCII characters\n";
        } else {
            *saveString += "-input:snx " + ui->lineEditSinex->text() + "\n";
            *runString << "-input:snx" << ui->lineEditSinex->text();
        }
    } else if (ui->radioButtonCalculate->isChecked() == true && ui->checkBoxReferencePositionFileCalculate->isChecked()==true) {
        if (ui->lineEditReferencePositionFileCalculate->text()=="") {
            *errorString += "INPUT: Reference position file is a required input if 'Reference Position File:' is set in 'Calculate' mode [In the Input Section - A Priori Receiver Position From] .\n";
        } else if (this->fileExists(ui->lineEditReferencePositionFileCalculate->text())==false) {
            *errorString += "INPUT: Reference position file in 'Calculate' mode does not exist [In the Input Section - A Priori Receiver Position From].\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditReferencePositionFileCalculate->text())==1) {
            *errorString += "INPUT: Reference position file in 'Calculate' mode has non ASCII characters [In the Input Section - A Priori Receiver Position From].\n";
        } else {
            *saveString += "-input:refpos " + ui->lineEditReferencePositionFileCalculate->text() + "\n";
            *runString << "-input:refpos" << ui->lineEditReferencePositionFileCalculate->text();
        }
    } else if (ui->radioButtonSpecify->isChecked() == true && ui->radioButtonSpecifyReferenceFile->isChecked()==true) {
        if (ui->lineEditReferenceFileSpecify->text()=="") {
            *errorString += "INPUT: Reference position file is a required input if 'Reference file:' is set in 'Specify' mode [In the Input Section - A Priori Receiver Position From] .\n";
        } else if (this->fileExists(ui->lineEditReferenceFileSpecify->text())==false) {
            *errorString += "INPUT: Reference position file in 'Specify' mode does not exist [In the Input Section - A Priori Receiver Position From].\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditReferenceFileSpecify->text())==1) {
            *errorString += "INPUT: Reference position file in 'Specify' mode has non ASCII characters [In the Input Section - A Priori Receiver Position From].\n";
        } else {
            *saveString += "-input:refpos " + ui->lineEditReferenceFileSpecify->text() + "\n";
            *runString << "-input:refpos" << ui->lineEditReferenceFileSpecify->text();
        }
    } else if (ui->radioButtonRtcm->isChecked() == true && (ui->radioButtonRtcmSpecify->isChecked()==true || ui->radioButtonRtcmUserSpecify->isChecked()==true)
               && ui->radioButtonRtcmReferenceFile->isChecked()==true) {
        if (ui->radioButtonRtcmSpecify->isChecked()==true) {
            RtcmNavMode="Specify Rover";
        } else {
            RtcmNavMode="User Ref. & Rover";
        }
        if (ui->lineEditReferenceFileRtcm->text()=="") {
            *errorString += "INPUT: Reference position file is a required input if 'Reference file:' is set in '" + RtcmNavMode + "' mode [In the Input Section - A Priori Receiver Position From] .\n";
        } else if (this->fileExists(ui->lineEditReferenceFileRtcm->text())==false) {
            *errorString += "INPUT: Reference position file in '" + RtcmNavMode + "' mode does not exist [In the Input Section - A Priori Receiver Position From].\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditReferenceFileRtcm->text())==1) {
            *errorString += "INPUT: Reference position file in '" + RtcmNavMode + "' mode has non ASCII characters [In the Input Section - A Priori Receiver Position From].\n";
        } else {
            *saveString += "-input:refpos " + ui->lineEditReferenceFileRtcm->text() + "\n";
            *runString << "-input:refpos" << ui->lineEditReferenceFileRtcm->text();
        }
    }
    // Ionosphere Source
    if ( ui->groupBoxIonoSource->isChecked() == true ) {
        if ( ui->radioButtonIonoSourceBrdc->isChecked() == true ) {
            if ( ( ui->comboBoxIonoSourceBrdc->currentIndex() == 1 && ui->stackedWidgetcomboBoxIonoSourceBrdc->currentIndex()==0) || ui->stackedWidgetcomboBoxIonoSourceBrdc->currentIndex()==1 ) {
                if ( ui->lineEditIonoSourceRinexNav->text() == "" ) {
                    *errorString += "INPUT: RINEX Broadcast navigation file is a required input if 'Broadcast (specify)' Ionosphere Source is specified.\n";
                } else if (this->fileExists(ui->lineEditIonoSourceRinexNav->text())==false) {
                    *errorString += "INPUT: RINEX Broadcast navigation file for Ionosphere Source does not exist.\n";
                } else if (this->checknonASCIIcharacters(ui->lineEditIonoSourceRinexNav->text())==1) {
                    *errorString += "INPUT: RINEX Broadcast navigation file for Ionosphere Source has non ASCII characters\n";
                } else {
                    *saveString += "-input:klb " + ui->lineEditIonoSourceRinexNav->text() + "\n";
                    *runString << "-input:klb" << ui->lineEditIonoSourceRinexNav->text();
                }
            }
        }
        if ( ui->radioButtonIonoSourceIonex->isChecked() == true ) {
            if ( ui->lineEditIonoSourceIonex->text() == "" ) {
                *errorString += "INPUT: IONEX file is a required input if 'IONEX' Ionosphere Source is specified.\n";
            } else if (this->fileExists(ui->lineEditIonoSourceIonex->text())==false) {
                *errorString += "INPUT: IONEX file does not exist.\n";
            } else if (this->checknonASCIIcharacters(ui->lineEditIonoSourceIonex->text())==1) {
                *errorString += "INPUT: IONEX file has non ASCII characters\n";
            } else {
                *saveString += "-input:inx " + ui->lineEditIonoSourceIonex->text() + "\n";
                *runString << "-input:inx" << ui->lineEditIonoSourceIonex->text();
            }
        }
        if ( ui->radioButtonIonoSourceSbas->isChecked() == true ) {
            if ( ui->stackedWidgetIonoSourceSbas->currentIndex() == 1 ) {
                if ( ui->lineEditIonoSourceSbasSpecify->text() == "" ) {
                    *errorString += "INPUT: SBAS file is a required input if 'SBAS' Ionosphere Source is specified.\n";
                } else if (this->fileExists(ui->lineEditIonoSourceSbasSpecify->text())==false) {
                    *errorString += "INPUT: SBAS file for Ionosphere Source does not exist.\n";
                } else if (this->checknonASCIIcharacters(ui->lineEditIonoSourceSbasSpecify->text())==1) {
                    *errorString += "INPUT: SBAS file for Ionosphere Source has non ASCII characters\n";
                } else {
                    *saveString += "-input:sbasiono " + ui->lineEditIonoSourceSbasSpecify->text() + "\n";
                    *runString << "-input:sbasiono" << ui->lineEditIonoSourceSbasSpecify->text();
                }
            }
        }
    }
    // SBAS
    if ( ui->groupBoxSbas->isChecked() == true ) {
        if ( ui->lineEditSbas->text() == "" ) {
            *errorString += "INPUT: SBAS file is a required input if 'SBAS' is specified.\n";
        } else if (this->fileExists(ui->lineEditSbas->text())==false) {
            *errorString += "INPUT: SBAS file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditSbas->text())==1) {
            *errorString += "INPUT: SBAS file has non ASCII characters\n";
        } else {
            if (ui->comboBoxSbasInput->currentIndex()==0){
                *saveString += "-input:sbas1f " + ui->lineEditSbas->text() + "\n";
                *runString << "-input:sbas1f" << ui->lineEditSbas->text();
            } else {
                *saveString += "-input:sbasdfmc " + ui->lineEditSbas->text() + "\n";
                *runString << "-input:sbasdfmc" << ui->lineEditSbas->text();
            }
        }
    }
    // DGNSS
    if ( ui->groupBoxReferenceStation->isChecked() == true ) {
        QDate date;
        QTime hour;
        switch ( ui->comboBoxRefStation->currentIndex() ) {
            case 0 : {
                if ( ui->lineEditRefStaRinex->text() == "" ) {
                    *errorString += "INPUT: RINEX Observation file is a required input if 'RINEX Observation File:' in Reference Station (DGPS) is specified.\n";
                } else if (this->fileExists(ui->lineEditRefStaRinex->text())==false) {
                    *errorString += "INPUT: RINEX Observation file for DGNSS does not exist.\n";
                } else if (this->checknonASCIIcharacters(ui->lineEditRefStaRinex->text())==1) {
                    *errorString += "INPUT: RINEX Observation file for DGNSS has non ASCII characters\n";
                } else {
                    *saveString += "-input:dgnss " + ui->lineEditRefStaRinex->text() + "\n";
                    *runString << "-input:dgnss" << ui->lineEditRefStaRinex->text();
                }
                break;
            }
            case 1 : {
                if ( ui->lineEditRefStaRtcmAuto->text() == "" ) {
                    *errorString += "INPUT: RTCM file is a required input if 'RTCM Auto:' in Reference Station (DGPS) is specified.\n";
                } else if (this->fileExists(ui->lineEditRefStaRtcmAuto->text())==false) {
                    *errorString += "INPUT: RTCM file does not exist.\n";
                } else if (this->checknonASCIIcharacters(ui->lineEditRefStaRtcmAuto->text())==1) {
                    *errorString += "INPUT: RTCM file has non ASCII characters\n";
                } else {
                    *saveString += "-input:rtcm " + ui->lineEditRefStaRtcmAuto->text() + "\n";
                    *runString << "-input:rtcm" << ui->lineEditRefStaRtcmAuto->text();
                }
                date = ui->dateEdit1->date();
                hour = ui->timeEdit1->time();
                if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && hour.hour() == 0 ) *errorString += "INPUT: Date (DD/MM/YYYY) and GPS Time (HH) are a required input if 'RTCM Auto:' in Reference Station (DGPS) is specified.\n";
                else {
                    *saveString += "-input:rtcm:initdate " + date.toString("yyyyMMdd") + "\n";
                    *runString << "-input:rtcm:initdate" << date.toString("yyyyMMdd");
                    *saveString += "-input:rtcm:inithour " + hour.toString("HH") + "\n";
                    *runString << "-input:rtcm:inithour" << hour.toString("HH");
                }
                break;
            }
            case 2 : {
                if ( ui->lineEditRefStaRtcm2->text() == "" ) {
                    *errorString += "INPUT: RTCM v2.x file is a required input if 'RTCM v2.x:' in Reference Station (DGPS) is specified.\n";
                } else if (this->fileExists(ui->lineEditRefStaRtcm2->text())==false) {
                    *errorString += "INPUT: RTCM v2.x file does not exist.\n";
                } else if (this->checknonASCIIcharacters(ui->lineEditRefStaRtcm2->text())==1) {
                    *errorString += "INPUT: RTCM v2.x file has non ASCII characters\n";
                } else {
                    *saveString += "-input:rtcm2 " + ui->lineEditRefStaRtcm2->text() + "\n";
                    *runString << "-input:rtcm2" << ui->lineEditRefStaRtcm2->text();
                }
                date = ui->dateEdit2->date();
                hour = ui->timeEdit2->time();
                if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && hour.hour() == 0 ) *errorString += "INPUT: Date (DD/MM/YYYY) and GPS Time (HH) are a required input if 'RTCM v2.x:' in Reference Station (DGPS) is specified.\n";
                else {
                    *saveString += "-input:rtcm:initdate " + date.toString("yyyyMMdd") + "\n";
                    *runString << "-input:rtcm:initdate" << date.toString("yyyyMMdd");
                    *saveString += "-input:rtcm:inithour " + hour.toString("HH") + "\n";
                    *runString << "-input:rtcm:inithour" << hour.toString("HH");
                }
                break;
            }
            case 3 : {
                if ( ui->lineEditRefStaRtcm3->text() == "" ) {
                    *errorString += "INPUT: RTCM v3.x file is a required input if 'RTCM v3.x:' in Reference Station (DGPS) is specified.\n";
                } else if (this->fileExists(ui->lineEditRefStaRtcm3->text())==false) {
                    *errorString += "INPUT: RTCM v3.x file does not exist.\n";
                } else if (this->checknonASCIIcharacters(ui->lineEditRefStaRtcm3->text())==1) {
                    *errorString += "INPUT: RTCM v3.x file has non ASCII characters\n";
                } else {
                    *saveString += "-input:rtcm3 " + ui->lineEditRefStaRtcm3->text() + "\n";
                    *runString << "-input:rtcm3" << ui->lineEditRefStaRtcm3->text();
                }
                date = ui->dateEdit3->date();
                if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 ) *errorString += "INPUT: Date (DD/MM/YYYY) is a required input if 'RTCM v3.x:' in Reference Station (DGPS) is specified.\n";
                else {
                    *saveString += "-input:rtcm:initdate " + date.toString("yyyyMMdd") + "\n";
                    *runString << "-input:rtcm:initdate" << date.toString("yyyyMMdd");
                }
                break;
            }
        }
    }
    // Auxiliary Files
    if ( ui->groupBoxAuxFiles->isChecked() == true ) {
        // P1-C1 Correction
        if ( ui->groupBoxP1C1correction->isChecked() == true ) {
            if ( ui->lineEditDcbFile->text() == "" ) {
                if ( ui->comboBoxDCBsfP1C1GPS->currentIndex() == 1 ) {
                    //Show error if P1-C1 is enabled and set to "strict". Otherwise P1-C1 DCBs will not be applied
                    *errorString += "INPUT: DCB file is a required input if 'P1-C1 Correction' is set to 'strict' in the MODELLING tab.\n";
                }
            } else if (this->fileExists(ui->lineEditDcbFile->text())==false) {
                *errorString += "INPUT: DCB file does not exist.\n";
            } else if (this->checknonASCIIcharacters(ui->lineEditDcbFile->text())==1) {
                *errorString += "INPUT: DCB file has non ASCII characters\n";
            } else {
                *saveString += "-input:dcb " + ui->lineEditDcbFile->text() + "\n";
                *runString << "-input:dcb" << ui->lineEditDcbFile->text();
            }

            if (ui->radioButtonGPSReceiverTypeFile->isChecked()==true ) {
                //P1-C1 set to strict or we have selected a GPS Receiver type file
                if ( ui->lineEditGPSRecType->text() == "" ) {
                    if ( ui->comboBoxDCBsfP1C1GPS->currentIndex() == 1) {
                        *errorString += "INPUT: GPS Receiver Types file is a required input if 'GPS Receiver Type from File' is selected and 'P1-C1 correction' in the MODELLING tab is set to 'strict'.\n";
                    }
                } else if (this->fileExists(ui->lineEditGPSRecType->text())==false) {
                    *errorString += "INPUT: GPS Receiver Types file does not exist.\n";
                } else if (this->checknonASCIIcharacters(ui->lineEditGPSRecType->text())==1) {
                    *errorString += "INPUT: GPS Receiver Types file has non ASCII characters\n";
                } else {
                    *saveString += "-input:rec " + ui->lineEditGPSRecType->text() + "\n";
                    *runString << "-input:rec" << ui->lineEditGPSRecType->text();
                }
            }
        }

        // P1-P2 Correction
        if ( ui->groupBoxP1P2correction->isChecked() == true && (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0 && ui->comboBoxDcbSource->currentIndex()==0 ) ) {
            if ( ui->lineEditRinexNav1->text() == "" ) {
                *errorString += "INPUT: RINEX Broadcast navigation file used as (P1 - P2) DCB source not found.\n";
            //Check if file does not exist will be already done in the navigation file check (as this uses the same file)
            } else {
                *saveString += "-input:dcb " + ui->lineEditRinexNav1->text() + "\n";
                *runString << "-input:dcb" << ui->lineEditRinexNav1->text();
            }
        }
        if ( ui->groupBoxP1P2correction->isChecked() == true && ( (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0 && ui->comboBoxDcbSource->currentIndex()==1 ) || (ui->stackedWidgetComboBoxDcbSource->currentIndex()==1 && ui->comboBoxDcbSourcePPP->currentIndex()==0 ) ) ) {
            if ( ui->lineEditDcbSourceRinexNav->text() == "" ) {
                *errorString += "INPUT: RINEX Broadcast navigation file is a required input if P1 - P2 Correction [In the Modelling Section] is set and 'Broadcast (specify)' DCB source is specified [In the Input Section].\n";
            } else if (this->fileExists(ui->lineEditDcbSourceRinexNav->text())==false) {
                *errorString += "INPUT: RINEX Broadcast navigation file for (P1 - P2) DCB source does not exist.\n";
            } else if (this->checknonASCIIcharacters(ui->lineEditDcbSourceRinexNav->text())==1) {
                *errorString += "INPUT: RINEX Broadcast navigation file for (P1 - P2) DCB source has non ASCII characters\n";
            } else {
                *saveString += "-input:dcb " + ui->lineEditDcbSourceRinexNav->text() + "\n";
                *runString << "-input:dcb" << ui->lineEditDcbSourceRinexNav->text();
            }
        }
         if ( ui->groupBoxP1P2correction->isChecked() == true && ( (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0 && ui->comboBoxDcbSource->currentIndex()==2 ) || (ui->stackedWidgetComboBoxDcbSource->currentIndex()==1 && ui->comboBoxDcbSourcePPP->currentIndex()==1 ) )  ) {
             if ( ui->lineEditDcbSourceDcb->text() == "" ) {
                 *errorString += "INPUT: (P1 - P2) DCB file is a required input if P1 - P2 Correction [In the Modelling Section] is set and 'DCB File' is empty [In the Input Section - Auxiliary Files - P1 - P2 Correction].\n";
             } else if (this->fileExists(ui->lineEditDcbSourceDcb->text())==false) {
                 *errorString += "INPUT: (P1 - P2) DCB file does not exist.\n";
             } else if (this->checknonASCIIcharacters(ui->lineEditDcbSourceDcb->text())==1) {
                 *errorString += "INPUT: (P1 - P2) DCB file has non ASCII characters\n";
             } else {
                 *saveString += "-input:dcb " + ui->lineEditDcbSourceDcb->text() + "\n";
                 *runString << "-input:dcb" << ui->lineEditDcbSourceDcb->text();
             }
         }
         if ( ui->groupBoxP1P2correction->isChecked() == true && ( (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0 && ui->comboBoxDcbSource->currentIndex()==3 ) || (ui->stackedWidgetComboBoxDcbSource->currentIndex()==1 && ui->comboBoxDcbSourcePPP->currentIndex()==2 ) )  ) {
             if ( ui->lineEditIonoSourceIonex->text() == "" ) {
                 *errorString += "INPUT: IONEX file used as (P1 - P2) DCB source not found.\n";
             //Check if file does not exist will be already done in the IONEX file check (as this uses the same file)
             } else {
                 *saveString += "-input:dcb " + ui->lineEditIonoSourceIonex->text() + "\n";
                 *runString << "-input:dcb" << ui->lineEditIonoSourceIonex->text();
             }
         }
         if ( ui->groupBoxP1P2correction->isChecked() == true && ( (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0 && ui->comboBoxDcbSource->currentIndex()==4 ) || (ui->stackedWidgetComboBoxDcbSource->currentIndex()==1 && ui->comboBoxDcbSourcePPP->currentIndex()==3 ) )  ) {
             if ( ui->lineEditDcbSourceIonex->text() == "" ) {
                 *errorString += "INPUT: (P1 - P2) IONEX file is a required input if P1 - P2 Correction [In the Modelling Section] is set and 'IONEX (specify)' is specified [In the Input Section].\n";
             } else if (this->fileExists(ui->lineEditDcbSourceIonex->text())==false) {
                 *errorString += "INPUT: IONEX (P1 - P2) DCB file does not exist.\n";
             } else if (this->checknonASCIIcharacters(ui->lineEditDcbSourceIonex->text())==1) {
                 *errorString += "INPUT: IONEX (P1 - P2) DCB file has non ASCII characters\n";
             } else {
                 *saveString += "-input:dcb " + ui->lineEditDcbSourceIonex->text() + "\n";
                 *runString << "-input:dcb" << ui->lineEditDcbSourceIonex->text();
             }
         }

         // User Defined SBAS Sigma Multipath
         if ( ui->groupBoxSbas->isChecked() == true && ui->groupBoxUserDefinedSbasSigmaMultipath->isChecked() == true ) {
             if ( ui->lineEditSigmaMultipath->text() == "" ) {
                 *errorString += "INPUT: User Defined Sigma Multipath file for SBAS is a required input if 'User Defined SBAS Sigma Multipath' is set.\n";
             } else if (this->fileExists(ui->lineEditSigmaMultipath->text())==false) {
                 *errorString += "INPUT: User Defined Sigma Multipath file does not exist.\n";
             } else if (this->checknonASCIIcharacters(ui->lineEditSigmaMultipath->text())==1) {
                 *errorString += "INPUT: User Defined Sigma Multipath file has non ASCII characters\n";
             } else {
                 *saveString += "-input:sigmpath " + ui->lineEditSigmaMultipath->text() + "\n";
                 *runString << "-input:sigmpath" << ui->lineEditSigmaMultipath->text();
             }
         }

         // User Added Error
         if ( ui->groupBoxUserAddedError->isChecked() == true ) {
             if ( ui->lineEditUserAddedError->text() == "" ) {
                 *errorString += "INPUT: User Added Error file is a required input if 'User Added Error' is set.\n";
             } else if (this->fileExists(ui->lineEditUserAddedError->text())==false) {
                 *errorString += "INPUT: User Added Error file does not exist.\n";
             } else if (this->checknonASCIIcharacters(ui->lineEditUserAddedError->text())==1) {
                 *errorString += "INPUT: User Added Error file has non ASCII characters\n";
             } else {
                 *saveString += "-input:usererror " + ui->lineEditUserAddedError->text() + "\n";
                 *runString << "-input:usererror" << ui->lineEditUserAddedError->text();
             }
             if (ui->checkBoxUserAddedErrorAfterPrepocessing->isChecked() ) {
                 *saveString += "-pre:usererrorafter";
                 *runString << "-pre:usererrorafter";
             }
         }
    }
}
