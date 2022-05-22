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


// Function to hide or show the line edit for the smoothing
void gLAB_GUI::on_checkBoxSmoothing_clicked(bool checked) {
    ui->checkBoxSmoothing->setChecked(checked);
    ui->frameSmoothing->setHidden(!checked);

    if ( (ui->labelCurrentTemplate->text() == "SBAS" || ui->groupBoxSbas->isChecked()==true) && checked == true ) {
        ui->stackedWidgetSmoothing->setCurrentIndex(1);
    } else if ( (ui->labelCurrentTemplate->text() == "DGNSS" || ui->groupBoxReferenceStation->isChecked()==true) && checked == true ) {
        ui->stackedWidgetSmoothing->setCurrentIndex(2);
    } else {
        ui->stackedWidgetSmoothing->setCurrentIndex(0);
    }
    if (ui->radioButtonSelectionPseudorangeCarrierPhase->isChecked()==true && ui->checkBoxSmoothing->isChecked()==true) {
        this->on_radioButtonSelectionPseudorange_clicked();
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
    if (ui->groupBoxSbas->isChecked()==true) {
        ui->stackedWidgetMeasConfigAndNoise->setCurrentIndex(2);
    } else if (ui->groupBoxReferenceStation->isChecked()==true) {
        ui->stackedWidgetMeasConfigAndNoise->setCurrentIndex(3);
    } else {
        ui->stackedWidgetMeasConfigAndNoise->setCurrentIndex(0);
    }
    ui->comboBoxMeasConfSingleFqPhase->setCurrentIndex(0);
    if (ui->groupBoxSbas->isChecked()==true) {
        ui->stackedWidgetSmoothWith->setCurrentIndex(2);
    } else {
        ui->stackedWidgetSmoothWith->setCurrentIndex(0);
    }
    if (ui->labelCurrentTemplate->text() == "PPP") {
        ui->comboBoxMeasConfSingleFqPhase->setCurrentIndex(2);
    } else {
        ui->comboBoxMeasConfSingleFqPhase->setCurrentIndex(0);
    }
    //Set P1-P2 DCB if non set
    this->on_checkBoxP1P2correction_clicked(true);
}

// Function to set the correct stacked widget in Measurement Configuration and Noise
void gLAB_GUI::on_radioButtonDualFreq_clicked() {
    ui->radioButtonDualFreq->setChecked(true);
    ui->stackedWidgetMeasConfigAndNoise->setCurrentIndex(1);
    ui->stackedWidgetSmoothWith->setCurrentIndex(1);
    //Unset P1-P2 DCB if non set
    this->on_checkBoxP1P2correction_clicked(false);
}

// Function to hide the carrier phase combo box
void gLAB_GUI::on_radioButtonSelectionPseudorange_clicked() {    
    ui->radioButtonSelectionPseudorange->setChecked(true);
    ui->frameSinglePseudorangeCarrierPhase->setHidden(true);
    ui->frameDualPseudorangeCarrierPhase->setHidden(true);
    ui->framePhaseAmbiguitiesParameters->setHidden(true);
}

// Function to show the carrier phase combo box
void gLAB_GUI::on_radioButtonSelectionPseudorangeCarrierPhase_clicked() {    
    ui->radioButtonSelectionPseudorangeCarrierPhase->setChecked(true);
    ui->frameSinglePseudorangeCarrierPhase->setHidden(false);
    ui->frameDualPseudorangeCarrierPhase->setHidden(false);
    ui->framePhaseAmbiguitiesParameters->setHidden(false);
}

// Function to manage the Measurement Configuration and Noise
void gLAB_GUI::on_radioButtonFixedStdDevSingleCode_clicked() {
    ui->radioButtonFixedStdDevSingleCode->setChecked(true);
    ui->frameFixedStdDevSingleCode->setHidden(false);
    ui->frameSingleCode->setHidden(true);
}

// Function to manage the Measurement Configuration and Noise
void gLAB_GUI::on_radioButtonFixedStdDevSingleCarrier_clicked() {
    ui->radioButtonFixedStdDevSingleCarrier->setChecked(true);
    ui->frameFixedStdDevSingleCarrier->setHidden(false);
    ui->frameSingleCarrier->setHidden(true);
}

// Function to manage the Measurement Configuration and Noise
void gLAB_GUI::on_radioButtonElevationStdDevSingleCode_clicked() {
    ui->radioButtonElevationStdDevSingleCode->setChecked(true);
    ui->frameFixedStdDevSingleCode->setHidden(true);
    ui->frameSingleCode->setHidden(false);
}

// Function to manage the Measurement Configuration and Noise
void gLAB_GUI::on_radioButtonElevationStdDevSingleCarrier_clicked() {
    ui->radioButtonElevationStdDevSingleCarrier->setChecked(true);
    ui->frameFixedStdDevSingleCarrier->setHidden(true);
    ui->frameSingleCarrier->setHidden(false);
}

// Function to manage the Measurement Configuration and Noise
void gLAB_GUI::on_radioButtonFixedStdDevDualCode_clicked() {
    ui->radioButtonFixedStdDevDualCode->setChecked(true);
    ui->frameFixedStdDevDualCode->setHidden(false);
    ui->frameDualCode->setHidden(true);
}

// Function to manage the Measurement Configuration and Noise
void gLAB_GUI::on_radioButtonFixedStdDevDualCarrier_clicked() {
    ui->radioButtonFixedStdDevDualCarrier->setChecked(true);
    ui->frameFixedStdDevDualCarrier->setHidden(false);
    ui->frameDualCarrier->setHidden(true);
}

// Function to manage the Measurement Configuration and Noise
void gLAB_GUI::on_radioButtonElevationStdDevDualCode_clicked() {
    ui->radioButtonElevationStdDevDualCode->setChecked(true);
    ui->frameFixedStdDevDualCode->setHidden(true);
    ui->frameDualCode->setHidden(false);
}

// Function to manage the Measurement Configuration and Noise
void gLAB_GUI::on_radioButtonElevationStdDevDualCarrier_clicked() {
    ui->radioButtonElevationStdDevDualCarrier->setChecked(true);
    ui->frameFixedStdDevDualCarrier->setHidden(true);
    ui->frameDualCarrier->setHidden(false);
}

// Function to set the filter parameters for static positioning
void gLAB_GUI::on_radioButtonStatic_clicked() {
    ui->radioButtonStatic->setChecked(true);
    ui->lineEditPhiCoordinates->setText("1"); // Phi
    ui->lineEditQcoordinates->setText("0"); // Q
}

// Function to set the filter parameters for kinematic positioning
void gLAB_GUI::on_radioButtonKinematic_clicked() {
    ui->radioButtonKinematic->setChecked(true);
    ui->lineEditPhiCoordinates->setText("0"); // Phi
    ui->lineEditQcoordinates->setText("1e8"); // Q
}

// Function to fix radiobutton "radioButtonStdDevSBAS" always selected (if nothing set,
//when radiobutton is clicked it will change to selected or unselected
void gLAB_GUI::on_radioButtonStdDevSBAS_clicked() {
    ui->radioButtonStdDevSBAS->setChecked(true);
}

// Function to fix radiobutton "radioButtonStdDevDGNSS" always selected (if nothing set,
//when radiobutton is clicked it will change to selected or unselected
void gLAB_GUI::on_radioButtonStdDevDGNSS_clicked() {
    ui->radioButtonStdDevDGNSS->setChecked(true);
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
        //Show warnings if cycle-slip detectors are not enabled due to smoothing
        if (ui->checkBoxSmoothing->isChecked()==true) {
            //Smoothing with L1
            if (ui->comboBoxSmoothWithSPP->currentIndex()==0 || ui->comboBoxSmoothWithSPP->currentIndex()==4 || ui->comboBoxSmoothWithSPP->currentIndex()==5 || ui->groupBoxSbas->isChecked()==true ) {
                if (ui->checkBoxL1C1->isChecked()==false && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false && ui->checkBoxLLI->isChecked()==false) {
                    *warningString += "PREPROCESS/FILTER: L1 carrier phase measurement is used for smoothing, but no cycle-slip detectors are enabled.\n";
                } else if (ui->checkBoxL1C1->isChecked()==false && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false) {
                    *warningString += "PREPROCESS/FILTER: L1 carrier phase measurement is used for smoothing, but only LLI cycle-slip detector is enabled, which is not very reliable.\n";
                } else {
                    if ( ui->radioButtonSingleFreq->isChecked() == true ) {
                        if (ui->checkBoxL1C1->isChecked()==false) {
                            *warningString += "PREPROCESS/FILTER: L1 carrier phase measurement is used, but L1-C1 cycle slip detector is not enabled.\n";
                        }
                        if (ui->checkBoxMW->isChecked()==true) {
                            *warningString += "PREPROCESS/FILTER: L1 carrier phase measurement is used, but Melbourne-Wübbena cycle-slip detector is enabled, which uses dual frequency measurements.\n";
                        }
                        if (ui->checkBoxLI->isChecked()==true) {
                            *warningString += "PREPROCESS/FILTER: L1 carrier phase measurement is used, but Geometry-free cycle-slip detector is enabled, which uses dual frequency measurements.\n";
                        }
                    }
                }

            } else if (ui->comboBoxSmoothWithSPP->currentIndex()==1 || ui->comboBoxSmoothWithSPP->currentIndex()==6 || ui->comboBoxSmoothWithSPP->currentIndex()==7) {
                //Smoothing with L2
                if (ui->checkBoxL1C1->isChecked()==false && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false && ui->checkBoxLLI->isChecked()==false) {
                    *warningString += "PREPROCESS/FILTER: L2 carrier phase measurement is used for smoothing, but no cycle-slip detectors are enabled.\n";
                } else if (ui->checkBoxL1C1->isChecked()==false && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false) {
                    *warningString += "PREPROCESS/FILTER: L2 carrier phase measurement is used for smoothing, but only LLI cycle-slip detector is enabled, which is not very reliable.\n";
                } else {
                    if (ui->checkBoxL1C1->isChecked()==true ) {
                        *warningString += "PREPROCESS/FILTER: L1-C1 cycle slip detector does not work with L2 measurements.\n";
                    }
                    if (ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false) {
                        *warningString += "PREPROCESS/FILTER: L2 carrier phase measurement is used for smoothing, but no cycle-slip detectors for L2 is enabled.\n";
                    } else if ( ui->radioButtonSingleFreq->isChecked() == true ) {
                        *warningString += "PREPROCESS/FILTER: Single frequency measurements are used, but L2 cycle-slip detectors require dual frequency measurements.\n";
                    }
                }
            } else {
                //Smoothing with dual-frequency measurements
                if (ui->checkBoxL1C1->isChecked()==false && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false && ui->checkBoxLLI->isChecked()==false) {
                    *warningString += "PREPROCESS/FILTER: Dual frequency carrier phase measurements are used for smoothing, but no cycle-slip detectors are enabled.\n";
                } else if (ui->checkBoxL1C1->isChecked()==false && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false) {
                    *warningString += "PREPROCESS/FILTER: Dual frequency carrier phase measurements are used for smoothing, but only LLI cycle-slip detector is enabled, which is not very reliable.\n";
                } else {
                    if (ui->checkBoxL1C1->isChecked()==true && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false ) {
                        *warningString += "PREPROCESS/FILTER: L1-C1 cycle slip detector only works with L1 measurements.\n";
                    }
                }
            }
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
            if (ui->checkBoxL1C1->isChecked()==false && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false && ui->checkBoxLLI->isChecked()==false) {
                *warningString += "PREPROCESS/FILTER: Carrier phase measurements are used, but no cycle-slip detectors are enabled.\n";
            } else if (ui->checkBoxL1C1->isChecked()==false && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false) {
                *warningString += "PREPROCESS/FILTER: Carrier phase measurements are used, but only LLI cycle-slip detector is enabled, which is not very reliable.\n";
            } else {
                if (ui->checkBoxL1C1->isChecked()==false) {
                    *warningString += "PREPROCESS/FILTER: Single frequency carrier phase measurements are used, but L1-C1 cycle slip detector is not enabled.\n";
                }
                if (ui->checkBoxMW->isChecked()==true) {
                    *warningString += "PREPROCESS/FILTER: Single frequency carrier phase measurements are used, but Melbourne-Wübbena cycle-slip detector is enabled, which uses dual frequency measurements.\n";
                }
                if (ui->checkBoxLI->isChecked()==true) {
                    *warningString += "PREPROCESS/FILTER: Single frequency carrier phase measurements are used, but Geometry-free cycle-slip detector is enabled, which uses dual frequency measurements.\n";
                }
            }
        } else if (ui->radioButtonDualFreq->isChecked() == true ) {
            if (ui->checkBoxL1C1->isChecked()==false && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false && ui->checkBoxLLI->isChecked()==false) {
                *warningString += "PREPROCESS/FILTER: Carrier phase measurements are used, but no cycle-slip detectors are enabled.\n";
            } else if (ui->checkBoxL1C1->isChecked()==false && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false) {
                *warningString += "PREPROCESS/FILTER: Carrier phase measurements are used, but only LLI cycle-slip detector is enabled, which is not very reliable.\n";
            } else {
                if (ui->checkBoxL1C1->isChecked()==true && ui->checkBoxMW->isChecked()==false && ui->checkBoxLI->isChecked()==false) {
                    *warningString += "PREPROCESS/FILTER: Dual frequency carrier phase measurements are used, but only L1-C1 cycle slip detector is enabled, which is single frequency.\n";
                }
            }
        }
    }
    // Ionosphere
    if ( ui->checkBoxUseSigmaIonosphere->isChecked() == true)  {
        //By default enabled in all modes
        if (WriteAllParameters==1) {
            *saveString += "-filter:sigmaiono\n";
            *runString << "-filter:sigmaiono";
        }
    } else {
        *saveString += "--filter:sigmaiono\n";
        *runString << "--filter:sigmaiono";
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
    if ( ui->radioButtonKinematic->isChecked() == true ) {
        if ( ui->lineEditPhiCoordinates->text() == "" )
            *errorString += "FILTER: Filter Parameters: Coordinates Phi must be >= 0.\n";
        else {
            if ( ui->lineEditPhiCoordinates->text().toDouble() != 0. || WriteAllParameters==1) {
                *saveString += "-filter:phi:dr " + ui->lineEditPhiCoordinates->text() + "\n";
                *runString << "-filter:phi:dr" << ui->lineEditPhiCoordinates->text();
            }
        }
        if ( ui->lineEditQcoordinates->text() == "" )
            *errorString += "FILTER: Filter Parameters: Coordinates Noise must be >= 0.\n";
        else {
            if ( ui->lineEditQcoordinates->text().toDouble() != 1e8 || WriteAllParameters==1) {
                *saveString += "-filter:q:dr " + ui->lineEditQcoordinates->text() + "\n";
                *runString << "-filter:q:dr" << ui->lineEditQcoordinates->text();
            }
        }
    } else if ( ui->radioButtonStatic->isChecked() == true ) {
        if ( ui->lineEditPhiCoordinates->text() == "" )
            *errorString += "FILTER: Filter Parameters: Coordinates Phi must be >= 0.\n";
        else {
            if ( ui->lineEditPhiCoordinates->text().toDouble() != 1. || WriteAllParameters==1) {
                *saveString += "-filter:phi:dr " + ui->lineEditPhiCoordinates->text() + "\n";
                *runString << "-filter:phi:dr" << ui->lineEditPhiCoordinates->text();
            }
        }
        if ( ui->lineEditQcoordinates->text() == "" )
            *errorString += "FILTER: Filter Parameters: Coordinates Noise must be >= 0.\n";
        else {
            if ( ui->lineEditQcoordinates->text().toDouble() != 0. || WriteAllParameters==1) {
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
    if ( ui->lineEditPhiClock->text() == "" )
        *errorString += "FILTER: Filter Parameters: Receiver Clock Phi must be >= 0.\n";
    else {
        if ( ui->lineEditPhiClock->text().toDouble() != 0. || WriteAllParameters==1 ) {
            *saveString += "-filter:phi:clk " + ui->lineEditPhiClock->text() + "\n";
            *runString << "-filter:phi:clk" << ui->lineEditPhiClock->text();
        }
    }
    if ( ui->lineEditQclock->text() == "" )
        *errorString += "FILTER: Filter Parameters: Receiver Clock Noise must be >= 0.\n";
    else {
        if ( ui->lineEditQclock->text().toDouble() != 9e10 || WriteAllParameters==1 ) {
            *saveString += "-filter:q:clk " + ui->lineEditQclock->text() + "\n";
            *runString << "-filter:q:clk" << ui->lineEditQclock->text();
        }
    }
    if ( ui->lineEditPoClock->text() == "" )
        *errorString += "FILTER: Filter Parameters: Receiver Clock Po must be >= 0.\n";
    else {
        if ( ui->lineEditPoClock->text().toDouble() != 9e10 || WriteAllParameters==1 ) {
            *saveString += "-filter:p0:clk " + ui->lineEditPoClock->text() + "\n";
            *runString << "-filter:p0:clk" << ui->lineEditPoClock->text();
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
    // Measurement Selection
    if ( ui->radioButtonSelectionPseudorange->isChecked() == true ) {
        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
            //SBAS and DGNSS are forced to used only one measurement and C1C measurement
            if ( ui->radioButtonSingleFreq->isChecked() == true ) {
                if ( (mode==0 &&  ui->comboBoxMeasConfSingleFqPseudorange->currentText()!="C1C") || mode==1 || WriteAllParameters==1) {
                    //SPP has C1C measurement by default ,and PPP has PC dual frequency by default
                    *saveString += "-filter:select 1 " + ui->comboBoxMeasConfSingleFqPseudorange->currentText() + "\n";
                    *runString << "-filter:select" << "1" << ui->comboBoxMeasConfSingleFqPseudorange->currentText();
                }
            } else if (( ui->radioButtonDualFreq->isChecked() == true && mode==0 ) || WriteAllParameters==1 ) {
                //This is PC measurement only. Default in PPP if only pseudorange is used
                *saveString += "-filter:select 1 " + ui->comboBoxMeasConfDualFqPseudorange->currentText() + "\n";
                *runString << "-filter:select" << "1" << ui->comboBoxMeasConfDualFqPseudorange->currentText();
            }
        }
    } else if ( ui->radioButtonSelectionPseudorangeCarrierPhase->isChecked() == true ) {
        //SBAS and DGNSS modes will never enter here, as these modes are forced for smoothed code only
        if ( ui->radioButtonSingleFreq->isChecked() == true ) {
            if ((mode==0 && (ui->comboBoxMeasConfSingleFqPseudorange->currentText()!="C1C" || ui->comboBoxMeasConfSingleFqPhase->currentText()!="L1P" ))|| WriteAllParameters==1) {
            //Single frequency with code and phase measurement. In SPP C1C and L1P are used when pseudorange and carrierphase are selected
                *saveString += "-filter:select 2 " + ui->comboBoxMeasConfSingleFqPseudorange->currentText() + " " + ui->comboBoxMeasConfSingleFqPhase->currentText() + "\n";
                *runString << "-filter:select" << "2" << ui->comboBoxMeasConfSingleFqPseudorange->currentText() << ui->comboBoxMeasConfSingleFqPhase->currentText();
            } else if (mode==1|| WriteAllParameters==1) {
                //In PPP default measurements are PC and LC, and these are single frequency measurements
                *saveString += "-filter:select 2 " + ui->comboBoxMeasConfSingleFqPseudorange->currentText() + " " + ui->comboBoxMeasConfSingleFqPhase->currentText() + "\n";
                *runString << "-filter:select" << "2" << ui->comboBoxMeasConfSingleFqPseudorange->currentText() << ui->comboBoxMeasConfSingleFqPhase->currentText();
            }
        } else if ( ui->radioButtonDualFreq->isChecked() == true ) {
            //This is PC and LC measurements. Default in PPP
            if (mode==0|| WriteAllParameters==1) {
                *saveString += "-filter:select 2 " + ui->comboBoxMeasConfDualFqPseudorange->currentText() + " " + ui->comboBoxMeasConfDualFqPhase->currentText() + "\n";
                *runString << "-filter:select" << "2" << ui->comboBoxMeasConfDualFqPseudorange->currentText() << ui->comboBoxMeasConfDualFqPhase->currentText();
            }
        }
    }
    // Measurement Configuration and Noise
    if ( ui->radioButtonSingleFreq->isChecked() == true ) {
        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
            //SBAS and DGNSS are forced to use sigmas from their respective messages
            if ( ui->radioButtonFixedStdDevSingleCode->isChecked() == true ) {
                if ( ui->lineEditFixedStdDevSingleCode->text() == "" ) {
                    *errorString += "FILTER: Fixed standard deviation (pseudorange) cannot be empty.\n";
                } if ( ui->lineEditFixedStdDevSingleCode->text().toDouble() == 0. ) {
                    *errorString += "FILTER: Fixed standard deviation (pseudorange) cannot be 0.\n";
                } else {
                    if ( ui->labelCurrentTemplate->text() == "PPP" ) {
                        //In PPP mode in single frequency, we need to set the weight
                        *saveString += "-filter:fixedweight 1 " + ui->lineEditFixedStdDevSingleCode->text() + "\n";
                        *runString << "-filter:fixedweight" << "1" << ui->lineEditFixedStdDevSingleCode->text();
                    } else {
                        if ( ui->lineEditFixedStdDevSingleCode->text().toDouble() != 1. || WriteAllParameters==1) {
                            *saveString += "-filter:fixedweight 1 " + ui->lineEditFixedStdDevSingleCode->text() + "\n";
                            *runString << "-filter:fixedweight" << "1" << ui->lineEditFixedStdDevSingleCode->text();
                        }
                    }
                }
            } else if ( ui->radioButtonElevationStdDevSingleCode->isChecked() == true ) {
                //Elevation weight, not the default in any mode
                if ( ui->lineEditElevationStdDevSingleCodeA->text() == "" || ui->lineEditElevationStdDevSingleCodeB->text() == "" || ui->lineEditElevationStdDevSingleCodeC->text() == "" ) {
                    *errorString += "FILTER: Elevation-dependant standard deviation (pseudorange) values cannot be empty.\n";
                } else if ( ui->lineEditElevationStdDevSingleCodeA->text().toDouble() == 0. && ui->lineEditElevationStdDevSingleCodeB->text().toDouble() == 0.) {
                    *errorString += "FILTER: Elevation-dependant standard deviation (pseudorange) a and b values cannot be both 0.\n";
                } else if ( ui->lineEditElevationStdDevSingleCodeC->text().toDouble() == 0. ) {
                    *errorString += "FILTER: Elevation-dependant standard deviation (pseudorange) c value cannot be 0.\n";
                } else {
                    *saveString += "-filter:elevweight 1 " + ui->lineEditElevationStdDevSingleCodeA->text() + " " + ui->lineEditElevationStdDevSingleCodeB->text() + " " + ui->lineEditElevationStdDevSingleCodeC->text() + "\n";
                    *runString << "-filter:elevweight" << "1" << ui->lineEditElevationStdDevSingleCodeA->text() << ui->lineEditElevationStdDevSingleCodeB->text() << ui->lineEditElevationStdDevSingleCodeC->text();
                }
            }
        }
    } else if ( ui->radioButtonDualFreq->isChecked() == true ) {
        if ( ui->radioButtonFixedStdDevDualCode->isChecked() == true ) {
            if ( ui->lineEditFixedStdDevDualCode->text() == "" ) {
                *errorString += "FILTER: Fixed standard deviation (pseudorange) cannot be empty.\n";
            } else if ( ui->lineEditFixedStdDevDualCode->text().toDouble() == 0. ) {
                *errorString += "FILTER: Fixed standard deviation (pseudorange) cannot be 0.\n";
            } else {
                //Dual frequency is PC measurement. For SPP we need to set it. In PPP is by default 3
                if ( ui->lineEditFixedStdDevDualCode->text().toDouble() != 3. || mode==0 || WriteAllParameters==1) {
                    *saveString += "-filter:fixedweight 1 " + ui->lineEditFixedStdDevDualCode->text() + "\n";
                    *runString << "-filter:fixedweight" << "1" << ui->lineEditFixedStdDevDualCode->text();
                }
            }
        } else if ( ui->radioButtonElevationStdDevDualCode->isChecked() == true ) {
            //Elevation weight, not the default in any mode
            if ( ui->lineEditElevationStdDevDualCodeA->text() == "" || ui->lineEditElevationStdDevDualCodeB->text() == "" || ui->lineEditElevationStdDevDualCodeC->text() == "" ) {
                *errorString += "FILTER: Elevation-dependant standard deviation (pseudorange) values cannot be empty.\n";
            } else if ( ui->lineEditElevationStdDevDualCodeA->text().toDouble() == 0. && ui->lineEditElevationStdDevDualCodeB->text().toDouble() == 0.) {
                *errorString += "FILTER: Elevation-dependant standard deviation (pseudorange) a and b values cannot be both 0.\n";
            } else if ( ui->lineEditElevationStdDevDualCodeC->text().toDouble() == 0. ) {
                *errorString += "FILTER: Elevation-dependant standard deviation (pseudorange) c value cannot be 0.\n";
            } else {
                *saveString += "-filter:elevweight 1 " + ui->lineEditElevationStdDevDualCodeA->text() + " " + ui->lineEditElevationStdDevDualCodeB->text() + " " + ui->lineEditElevationStdDevDualCodeC->text() + "\n";
                *runString << "-filter:elevweight" << "1" << ui->lineEditElevationStdDevDualCodeA->text() << ui->lineEditElevationStdDevDualCodeB->text() << ui->lineEditElevationStdDevDualCodeC->text();
            }
        }
    }
    // If carrier phase selected, then write the configuration
    if ( ui->radioButtonSelectionPseudorangeCarrierPhase->isChecked() == true ) {
        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
            //SBAS and DGNSS are forced to use single frequency and sigmas from their respective messages
            if ( ui->radioButtonSingleFreq->isChecked() == true ) {
                if ( ui->radioButtonFixedStdDevSingleCarrier->isChecked() == true ) {
                    if ( ui->lineEditFixedStdDevSingleCarrier->text() == "" ) {
                        *errorString += "FILTER: Fixed standard deviation (carrier phase) cannot be empty.\n";
                    } else if ( ui->lineEditFixedStdDevSingleCarrier->text().toDouble() == 0. ) {
                        *errorString += "FILTER: Fixed standard deviation (carrier phase) cannot be 0.\n";
                    } else {
                        if ( ui->labelCurrentTemplate->text() == "PPP" ) {
                            //Single frequency in PPP mode uses G1C as phase measurements, which is not the default
                            *saveString += "-filter:fixedweight 2 " + ui->lineEditFixedStdDevSingleCarrier->text() + "\n";
                            *runString << "-filter:fixedweight" << "2" << ui->lineEditFixedStdDevSingleCarrier->text();
                        } else if ( ui->lineEditFixedStdDevSingleCarrier->text().toDouble() != 0.01 || WriteAllParameters==1 ) {
                            //In SPP mode, phase measurement is assigned 0.01 meters
                            *saveString += "-filter:fixedweight 2 " + ui->lineEditFixedStdDevSingleCarrier->text() + "\n";
                            *runString << "-filter:fixedweight" << "2" << ui->lineEditFixedStdDevSingleCarrier->text();
                        }
                    }
                } else if ( ui->radioButtonElevationStdDevSingleCarrier->isChecked() == true ) {
                    //Elevation weight is not the default in any mode
                    if ( ui->lineEditElevationStdDevSingleCarrierA->text() == "" || ui->lineEditElevationStdDevSingleCarrierB->text() == "" || ui->lineEditElevationStdDevSingleCarrierC->text() == "" ) {
                        *errorString += "FILTER: Elevation-dependant standard deviation (carrier phase) values cannot be empty.\n";
                    } else if ( ui->lineEditElevationStdDevSingleCarrierA->text().toDouble() == 0. && ui->lineEditElevationStdDevSingleCarrierB->text().toDouble() == 0.) {
                        *errorString += "FILTER: Elevation-dependant standard deviation (carrier phase) a and b values cannot be both 0.\n";
                    } else if ( ui->lineEditElevationStdDevSingleCarrierC->text().toDouble() == 0. ) {
                        *errorString += "FILTER: Elevation-dependant standard deviation (carrier phase) c value cannot be 0.\n";
                    } else {
                        *saveString += "-filter:elevweight 2 " + ui->lineEditElevationStdDevSingleCarrierA->text() + " " + ui->lineEditElevationStdDevSingleCarrierB->text() + " " + ui->lineEditElevationStdDevSingleCarrierC->text() + "\n";
                        *runString << "-filter:elevweight" << "2" << ui->lineEditElevationStdDevSingleCarrierA->text() << ui->lineEditElevationStdDevSingleCarrierB->text() << ui->lineEditElevationStdDevSingleCarrierC->text();
                    }
                }
            } else if ( ui->radioButtonDualFreq->isChecked() == true ) {
                if ( ui->radioButtonFixedStdDevDualCarrier->isChecked() == true ) {
                    if ( ui->lineEditFixedStdDevDualCarrier->text() == "" ) {
                        *errorString += "FILTER: Fixed standard deviation (carrier phase) cannot be empty.\n";
                    } else if ( ui->lineEditFixedStdDevDualCarrier->text().toDouble() == 0. ) {
                        *errorString += "FILTER: Fixed standard deviation (carrier phase) cannot be 0.\n";
                    } else {
                        if ( ui->lineEditFixedStdDevDualCarrier->text() != "0.03"|| mode==0|| WriteAllParameters==1 ) {
                            //This is LC measurement. Not the default in SPP
                            *saveString += "-filter:fixedweight 2 " + ui->lineEditFixedStdDevDualCarrier->text() + "\n";
                            *runString << "-filter:fixedweight" << "2" << ui->lineEditFixedStdDevDualCarrier->text();
                        }
                    }
                } else if ( ui->radioButtonElevationStdDevDualCarrier->isChecked() == true ) {
                    //Elevation weight is not the default in any mode
                    if ( ui->lineEditElevationStdDevDualCarrierA->text() == "" || ui->lineEditElevationStdDevDualCarrierB->text() == "" || ui->lineEditElevationStdDevDualCarrierC->text() == "" ) {
                        *errorString += "FILTER: Elevation-dependant standard deviation (carrier phase) values cannot be empty.\n";
                    } else if ( ui->lineEditElevationStdDevDualCarrierA->text().toDouble() == 0. && ui->lineEditElevationStdDevDualCarrierB->text().toDouble() == 0.) {
                        *errorString += "FILTER: Elevation-dependant standard deviation (carrier phase) a and b values cannot be both 0.\n";
                    } else if ( ui->lineEditElevationStdDevDualCarrierC->text().toDouble() == 0. ) {
                        *errorString += "FILTER: Elevation-dependant standard deviation (carrier phase) c value cannot be 0.\n";
                    } else {
                        *saveString += "-filter:elevweight 2 " + ui->lineEditElevationStdDevDualCarrierA->text() + " " + ui->lineEditElevationStdDevDualCarrierB->text() + " " + ui->lineEditElevationStdDevDualCarrierC->text() + "\n";
                        *runString << "-filter:elevweight" << "2" << ui->lineEditElevationStdDevDualCarrierA->text() << ui->lineEditElevationStdDevDualCarrierB->text() << ui->lineEditElevationStdDevDualCarrierC->text();
                    }
                }
            }
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
            //It is disabled by default in all modes
            *saveString += "-filter:prefitoutliers:median " + ui->lineEditPrefitOutliers->text() + "\n";
            *runString << "-filter:prefitoutliers:median" << ui->lineEditPrefitOutliers->text();
        }
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
        } else if (ui->lineEditStanfordEsaXmax->text().toDouble() == 0. ) {
            *errorString += "OUTPUT: Maximum X in [Stanford-ESA] cannot be 0.\n";
        }
        if ( ui->lineEditStanfordEsaYmax->text() == "" ) {
            *errorString += "OUTPUT: Maximum Y in [Stanford-ESA] cannot be empty.\n";
        } else if (ui->lineEditStanfordEsaYmax->text().toDouble() == 0. ) {
            *errorString += "OUTPUT: Maximum Y in [Stanford-ESA] cannot be 0.\n";
        }
        if ( ui->lineEditStanfordEsaXres->text() == "" ) {
            *errorString += "OUTPUT: Resolution X in [Stanford-ESA] cannot be empty.\n";
        } else if (ui->lineEditStanfordEsaXres->text().toDouble() == 0. ) {
            *errorString += "OUTPUT: Resolution X in [Stanford-ESA] cannot be 0.\n";
        }
        if ( ui->lineEditStanfordEsaYres->text() == "" ) {
            *errorString += "OUTPUT: Resolution Y in [Stanford-ESA] cannot be empty.\n";
        } else if (ui->lineEditStanfordEsaYres->text().toDouble() == 0. ) {
            *errorString += "OUTPUT: Resolution Y in [Stanford-ESA] cannot be 0.\n";
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
