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
    ui->groupBoxReceiverAntennaPhaseCentreCorrection->setHidden(!checked);
    this->on_radioButtonAPCread_clicked();    
    ui->checkBoxReceiverAntennaPhaseCentreVariation->setChecked(checked);
    if (checked==true) {
        this->on_checkBoxAntex_clicked(true);
    } else if (checked==false && ui->checkBoxSatMassCentre->isChecked()==false ) {
        this->on_checkBoxAntex_clicked(false);
    }
}

// Function to hide or show the satellite Antenna Phase Centre Correction box
void gLAB_GUI::on_checkBoxSatMassCentre_clicked(bool checked) {
    ui->checkBoxSatMassCentre->setChecked(checked);
    ui->frameSatellitePhaseCenterVariation->setHidden(!checked);
    ui->checkBoxSatelliteAntennaPhaseCentreVariation->setChecked(checked);
    if (checked==true) {
            this->on_checkBoxAntex_clicked(true);
    } else if (checked==false && ui->checkBoxAntennaPhase->isChecked()==false ) {
        this->on_checkBoxAntex_clicked(false);
    }
}

// Function to hide or show the Receiver Antenna Reference Point Correction box
void gLAB_GUI::on_checkBoxAntennaReference_clicked(bool checked) {
    ui->checkBoxAntennaReference->setChecked(checked);
    ui->groupBoxReceiverAntennaReferencePointCorrection->setHidden(!checked);
    this->on_radioButtonARPread_clicked();
}

// Function to hide or show the P1-P2 correction combo box
void gLAB_GUI::on_checkBoxP1P2correction_clicked(bool checked) {
    ui->checkBoxP1P2correction->setChecked(checked);
    ui->frameModellingP1P2correction->setHidden(!checked);
    if (checked==true && (ui->stackedWidgetComboBoxDcbSource->currentIndex()==1 || ui->comboBoxP1P2correction->currentIndex()>0)) {
        if (ui->groupBoxAuxFiles->isChecked()==false) {
            this->on_groupBoxAuxFiles_clicked(true);
        }
        this->on_groupBoxP1P2correction_clicked(true);
    } else if (checked==false) {
        this->on_groupBoxP1P2correction_clicked(false);
    }
    if (checked==true && ui->comboBoxP1P2correction->currentIndex()==0) {
        ui->checkBoxDiscardUnhealthy->setHidden(false);
    } else if (checked==false && ui->radioButtonOrbitBrdc->isChecked()==false) {
        ui->checkBoxDiscardUnhealthy->setHidden(true);
    }
}

// Function to hide or show the P1-C1 correction combo box
void gLAB_GUI::on_checkBoxP1C1correction_clicked(bool checked) {
    ui->checkBoxP1C1correction->setChecked(checked);
    ui->frameModellingP1C1correction->setHidden(!checked);
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
    ui->frameAPCcorrection->setHidden(true);
    ui->frameAPCantex->setHidden(false);
    this->on_checkBoxAntex_clicked(true);
}

// Function to set the correct stacked in APC
void gLAB_GUI::on_radioButtonAPCspecify_clicked() {
    ui->radioButtonAPCread->setChecked(false);
    ui->radioButtonAPCspecify->setChecked(true);
    ui->frameAPCcorrection->setHidden(false);
    ui->frameAPCantex->setHidden(true);
    this->on_checkBoxAntex_clicked(false);
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

// Function to set the correct stacked in APC for F1
void gLAB_GUI::on_radioButtonAPCspecifyF1_clicked() {
    ui->radioButtonAPCspecifyF1->setChecked(true);
    ui->radioButtonAPCspecifyF2->setChecked(false);
    ui->stackedWidgetAPCf1f2->setCurrentIndex(0);
}

// Function to set the correct stacked in APC for F2
void gLAB_GUI::on_radioButtonAPCspecifyF2_clicked() {
    ui->radioButtonAPCspecifyF1->setChecked(false);
    ui->radioButtonAPCspecifyF2->setChecked(true);
    ui->stackedWidgetAPCf1f2->setCurrentIndex(1);
}

// Function to modify the Input tab based on the modification done in Modelling tab
void gLAB_GUI::on_comboBoxP1P2correction_currentIndexChanged(int index) {
    if ( index == 0 ) { // Broadcast
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
    } else if ( index == 1 ) { // DCB file
        this->on_groupBoxAuxFiles_clicked(true);
        this->on_groupBoxP1P2correction_clicked(true);
        if (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0) {
            ui->comboBoxDcbSource->setCurrentIndex(2);
        } else {
            ui->comboBoxDcbSourcePPP->setCurrentIndex(1);
            ui->checkBoxDiscardUnhealthy->setHidden(true);
        }
    } else if ( index == 2 ) { // IONEX
        if ( ui->groupBoxIonoSource->isChecked() == true && ui->radioButtonIonoSourceIonex->isChecked() == true ) {
            if (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0) {
                if (ui->comboBoxDcbSource->currentIndex() < 3 ) {
                    ui->comboBoxDcbSource->setCurrentIndex(3);
                }
            } else {
                if (ui->comboBoxDcbSourcePPP->currentIndex() < 3) {
                    ui->comboBoxDcbSourcePPP->setCurrentIndex(2);
                }
                ui->checkBoxDiscardUnhealthy->setHidden(true);
            }
        } else {
            this->on_groupBoxAuxFiles_clicked(true);
            this->on_groupBoxP1P2correction_clicked(true);
            if (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0) {
                if (ui->comboBoxDcbSource->currentIndex() < 2 ) {
                    ui->comboBoxDcbSource->setCurrentIndex(4);
                }
            } else {
                if (ui->comboBoxDcbSourcePPP->currentIndex() < 2) {
                    ui->comboBoxDcbSourcePPP->setCurrentIndex(3);
                }
                ui->checkBoxDiscardUnhealthy->setHidden(true);
            }
        }
    }
}

// Function to modify the Input tab based on the modification done in Modelling tab
void gLAB_GUI::on_comboBoxP1C1correction_currentIndexChanged(int index) {
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
        this->on_groupBoxIonoSource_clicked(true);
        this->on_radioButtonIonoSourceIonex_clicked();
    } else if ( index == 4 ) { // SBAS
        ui->comboBoxP1P2correction->setCurrentIndex(0);
        this->on_groupBoxIonoSource_clicked(true);
        this->on_radioButtonIonoSourceSbas_clicked();
    } else { // Broadcast (Klobuchar or IONEX)
        ui->comboBoxP1P2correction->setCurrentIndex(0);
        if ( ui->comboBoxIonoSourceBrdc->currentIndex() == 1 ) {
            this->on_groupBoxIonoSource_clicked(true);
        } else if ( ui->comboBoxIonoSourceBrdc->currentIndex() == 0 ) {
            this->on_radioButtonIonoSourceBrdc_clicked();
            //this->on_groupBoxIonoSource_clicked(false);
        }
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
    ui->frameMessagesTimeOuts->setHidden(!checked);
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


//Function to show or hide PA timeouts
void gLAB_GUI::showHidePAtimeouts(bool hide) {
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
}

//Function to show or hide NPA timeouts
void gLAB_GUI::showHideNPAtimeouts(bool hide) {
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
}

//Function to read message type and timeout value and apply it in the GUI
void gLAB_GUI::readSBASMTandTimeout(int MessageType, int timeout, int type, QString option, QString *warningString) {
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

    if ( ui->checkBoxDiscardUnhealthy->isChecked() == true) {
        //It is enabled on all modes by default. No need to set the option
         if (WriteAllParameters==1 ) {
            *saveString += "-model:satellitehealth\n";
            *runString << "-model:satellitehealth";
         }
    } else {
        *saveString += "--model:satellitehealth\n";
        *runString << "--model:satellitehealth";
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
        if (ui->checkBoxAntex->isChecked()==false || ui->lineEditAntex->text()=="") {
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
            if (ui->checkBoxAntex->isChecked()==false || ui->lineEditAntex->text()=="") {
                *errorString += "MODEL: Receiver phase center correction from ANTEX enabled, but no ANTEX file is given.\n";
            }
        } else if ( ui->radioButtonAPCspecify->isChecked() == true ) {
            //This is not the default of any mode
            if ( ui->lineEditAPCf1north->text() == "" || ui->lineEditAPCf1east->text() == "" || ui->lineEditAPCf1up->text() == "" ) {
                *errorString += "MODEL: Receiver Antenna Phase Centre (F1) values cannot be empty.\n";
            } else if ( ui->lineEditAPCf2north->text() == "" || ui->lineEditAPCf2east->text() == "" || ui->lineEditAPCf2up->text() == "" ) {
                *errorString += "MODEL: Receiver Antenna Phase Centre (F2) values cannot be empty.\n";
            } else {
                *saveString += "-model:recphasecenter 1 " + ui->lineEditAPCf1north->text() + " " + ui->lineEditAPCf1east->text() + " " + ui->lineEditAPCf1up->text() + "\n";
                *runString << "-model:recphasecenter" << "1" << ui->lineEditAPCf1north->text() << ui->lineEditAPCf1east->text() << ui->lineEditAPCf1up->text();
                *saveString += "-model:recphasecenter 2 " + ui->lineEditAPCf2north->text() + " " + ui->lineEditAPCf2east->text() + " " + ui->lineEditAPCf2up->text() + "\n";
                *runString << "-model:recphasecenter" << "2" << ui->lineEditAPCf2north->text() << ui->lineEditAPCf2east->text() << ui->lineEditAPCf2up->text();
                if (WriteAllParameters==1) {
                    *saveString += "--model:recphasevar\n";
                    *runString << "--model:recphasevar";
                }
            }
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
        if ((mode==0 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true) || WriteAllParameters==1) {
            //It is enabled by default in all modes except PPP
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
    // P1 - P2 correction
    if ( ui->checkBoxP1P2correction->isChecked() == true ) {
        switch ( ui->comboBoxP1P2correction->currentIndex() ) {
            case 0 : {
                 if ((mode==1  && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) ) {
                     //P1-P2 correction from RINEX is enabled by default in all modes except PPP
                    *saveString += "-model:dcb:p1p2 RINEX\n";
                    *runString << "-model:dcb:p1p2" << "RINEX";
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
                 } else if (WriteAllParameters==1) {
                     *saveString += "-model:dcb:p1p2 RINEX\n";
                     *runString << "-model:dcb:p1p2" << "RINEX";
                 }
                break;
            }
            case 1 : {
                //Not a default in any mode
                *saveString += "-model:dcb:p1p2 DCB\n";
                *runString << "-model:dcb:p1p2" << "DCB";
                if (ui->groupBoxP1P2correction->isChecked() == false || (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0 && ui->comboBoxDcbSource->currentIndex() != 2) || (ui->stackedWidgetComboBoxDcbSource->currentIndex()==1 && ui->comboBoxDcbSourcePPP->currentIndex() != 1)   ) {
                    *errorString += "MODEL: DCB P1-P2 correction selected, but no DCB file given.\n";
                }
                break;
            }
            case 2 : {
                //Not a default in any mode
                *saveString += "-model:dcb:p1p2 IONEX\n";
                *runString << "-model:dcb:p1p2" << "IONEX";

                if (ui->groupBoxP1P2correction->isChecked() == false ||  (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0 && ui->comboBoxDcbSource->currentIndex() < 3 ) || (ui->stackedWidgetComboBoxDcbSource->currentIndex()==1 && ui->comboBoxDcbSourcePPP->currentIndex() <2) ) {
                    *errorString += "MODEL: IONEX P1-P2 correction selected, but no IONEX P1-P2 correction selected in the INPUT section\n";
                } else if ( (ui->stackedWidgetComboBoxDcbSource->currentIndex()==0 && ui->comboBoxDcbSource->currentIndex() ==3 && ui->radioButtonIonoSourceIonex->isChecked()==false) || (ui->stackedWidgetComboBoxDcbSource->currentIndex()==1 && ui->comboBoxDcbSource->currentIndex() ==2 && ui->radioButtonIonoSourceIonex->isChecked()==false)  ) {
                     *errorString += "MODEL: IONEX P1-P2 correction from  ionosphere file selected, but no IONEX file for ionosphere given.\n";
                }
                break;
            }
        }
    } else {
         if ((mode==0 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true) || WriteAllParameters==1) {
             //P1-P2 correction is disabled by default in PPP
            *saveString += "--model:dcb:p1p2\n";
            *runString << "--model:dcb:p1p2";
         }
    }
    // P1 - C1 correction
    if ( ui->checkBoxP1C1correction->isChecked() == true ) {
        switch ( ui->comboBoxP1C1correction->currentIndex() ) {
            case 0 : {
                if (ui->groupBoxSbas->isChecked()==true || WriteAllParameters==1) {
                    //Default in all modes except in SBAS
                    *saveString += "-model:dcb:p1c1 flexible\n";
                    *runString << "-model:dcb:p1c1" << "flexible";
                }
                break;
            }
            case 1 : {
                 if (ui->groupBoxSbas->isChecked()==false || WriteAllParameters==1) {
                     //P1-C1 can not be changed in SBAS
                     *saveString += "-model:dcb:p1c1 strict\n";
                     *runString << "-model:dcb:p1c1" << "strict";
                 }
                break;
            }
        }
    } else {
         if (ui->groupBoxSbas->isChecked()==false || WriteAllParameters==1) {
             //SBAS default, and cannot be changed
            *saveString += "--model:dcb:p1c1\n";
            *runString << "--model:dcb:p1c1";
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
            *errorString += "Number of maximum gaps in orbit interpolation must be equal or greater than then number of consecutive gaps.\n";
        } else if ( ui->lineEditClockMaxGaps->text().toInt()< ui->lineEditClockConsecutiveGaps->text().toInt()) {
            *errorString += "Number of maximum gaps in clock interpolation must be equal or greater than then number of consecutive gaps.\n";
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
            if ( ui->lineEditClockInterpolationDegree->text().toInt()!=0  || WriteAllParameters==1) {
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
    if ( ui->labelCurrentTemplate->text() == "SBAS" ||  ui->groupBoxSbas->isChecked()==true ) {
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
        // Time-outs

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
        // Fast corrections PA
        if ( ui->lineEditFastCorrectionsPA->text() != "" ) {
            *saveString += "-model:sbastmoutfcpa " + ui->lineEditFastCorrectionsPA->text() + "\n";
            *runString << "-model:sbastmoutfcpa" << ui->lineEditFastCorrectionsPA->text();
        }
        // Fast corrections NPA
        if ( ui->lineEditFastCorrectionsNPA->text() != "" ) {
            *saveString += "-model:sbastmoutfcnpa " + ui->lineEditFastCorrectionsNPA->text() + "\n";
            *runString << "-model:sbastmoutfcnpa" << ui->lineEditFastCorrectionsNPA->text();
        }
        // RRC corrections PA
        if ( ui->lineEditRRCcorrectionsPA->text() != "" ) {
            *saveString += "-model:sbastmoutrrcpa " + ui->lineEditRRCcorrectionsPA->text() + "\n";
            *runString << "-model:sbastmoutrrcpa" << ui->lineEditRRCcorrectionsPA->text();
        }
        // RRC corrections NPA
        if ( ui->lineEditRRCcorrectionsNPA->text() != "" ) {
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
    if ( ui->labelCurrentTemplate->text() == "SBAS" ||  ui->groupBoxSbas->isChecked()==true ) {
        if ( ui->checkBoxParseAlarm->isChecked() == true ) {            
            *saveString += "-model:alarmmsgtype2\n";
            *runString << "-model:alarmmsgtype2";
        } else if ( ui->checkBoxParseAlarm->isChecked() == false) {
            //This is the default in SBAS
            if (WriteAllParameters==1) {
                *saveString += "--model:alarmmsgtype2\n";
                *runString << "--model:alarmmsgtype2";
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
        if ( ui->checkBoxAllowKlobucharIono->isChecked() == true) {
            //This is the default in SBAS
            if (WriteAllParameters==1) {
                *saveString += "-model:initcoordnpa\n";
                *runString << "-model:initcoordnpa";
            }
        } else if ( ui->checkBoxAllowKlobucharIono->isChecked() == false ) {
            *saveString += "--model:initcoordnpa\n";
            *runString << "--model:initcoordnpa";
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

        if(ui->lineEditOffsetFastCorrNoMT10->text()=="") {
            *errorString += "MODEL: Parameter in 'Sigma offset if MT10 is not used' option in [SBAS Options] cannot be empty.\n";
        } else if (ui->lineEditOffsetFastCorrNoMT10->text().toDouble()!=8. || WriteAllParameters==1) {
            *saveString += "-model:sigfltnomt10offset " + ui->lineEditOffsetFastCorrNoMT10->text() + "\n";
            *runString << "-model:sigfltnomt10offset" << ui->lineEditOffsetFastCorrNoMT10->text();
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
                *saveString += "-model:geoadqtime " + ui->lineEditGEOadquisitionTime->text() + "\n";
                *runString << "-model:geoadqtime" << ui->lineEditGEOadquisitionTime->text();
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
