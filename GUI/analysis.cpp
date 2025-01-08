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

//Items for Message comboBoxes
const QStringList EmptyMessage = (QStringList() << "");
const QStringList USERADDEDERRORMessage = (QStringList() << "" << "USERADDEDERROR" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GPSWeek" << "TimeofDay" << "GNSS" << "PRN" << "MeasurementID" << "RawMeasurement" << "ModifiedMeasurement" << "ActiveUserErrorFunctions" << "TotalUserErrorFunctions"
                                     << "ActiveStepFunctionError" << "StepFunctionErrorValue" << "ActiveRampFunction" << "RampFunctionErrorValue" << "ActiveSinusoidalFunctionError" << "SinusoidalFunctionErrorValue" << "ActiveAWGNFunctionError" << "AWGNFunctionErrorValue");
const QStringList INPUTMessage = (QStringList() << "" << "INPUT" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSS" << "PRN" << "ArcNumber" << "ArcLength" << "C1[C1C]" << "P1[C1P]" << "P2[C2P]" << "L1[L1P]" << "L2[L2P]");
const QStringList CSMessage = (QStringList() << "" << "CS" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSS" << "PRN");
const QStringList SFCSMessage = (QStringList() << "" << "SFCS" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSS" << "PRN" << "ArcNumber" << "ArcLength" << "SFMeasurements" << "SFCodeMeas" << "SFPhaseMeas" << "DeltaCode" << "DeltaPhase" << "AbsoluteDiff" << "MeanDiff" << "SigmaDiff"
                           << "Difference" << "Threshold" << "MaxThreshold" << "UnconsistFlag" << "SFCSFlag");
const QStringList MWCSMessage = (QStringList() << "" << "MWCS" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSS" << "PRN" << "ArcNumber" << "ArcLength" << "MWMeasurements" << "MWCode1Meas" << "MWCode2Meas" << "MWPhase1Meas" << "MWPhase2Meas" << "MWValue" << "MWMean1" << "MWMean2"
                           << "MWArcSigma" << "Difference1" << "Difference2" << "Threshold1" << "Threshold2" << "OutlierFlag" << "MWCSFlag");
const QStringList LICSMessage = (QStringList() << "" << "LICS" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSS" << "PRN" << "ArcNumber" << "ArcLength" << "GFMeasurements" << "GFPhase1Meas" << "GFPhase2Meas" << "GFInitialValue" << "GFCurrentValue" << "Difference1" << "EstGFValue"
                           << "Difference2" << "PostfitResidual" << "Threshold1" << "Threshold2" << "OutlierFlag" << "LICSFlag");
const QStringList IGFCSMessage = (QStringList() << "" << "IGFCS" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSS" << "PRN" << "ArcNumber" << "ArcLength" << "IGFMeasurements" << "IGFPhase1Meas" << "IGFPhase2Meas" << "IGFPhase3Meas" << "IGFPhase4Meas" << "IGFInitialValue" << "IGFCurrentValue"
                            << "Difference1" << "IGFPrediction" << "Difference2" << "PostfitResidual" << "Threshold1" << "Threshold2" << "OutlierFlag" << "IGFCSFlag");
const QStringList MEASMessage = (QStringList() << "" << "MEAS" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSS" << "PRN" << "Block" << "SVN" << "ArcNumber" << "ArcLength" << "SatElevation" << "SatAzimuth" << "MeasNumber" << "MeasList" << "MeasValue1" << "MeasValue2" << "MeasValue3" << "MeasValue4"
                           << "MeasValue5" << "MeasValue6" << "MeasValue7" << "MeasValue8" << "MeasValue9" << "MeasValue10" << "MeasValue11" << "MeasValue12" << "MeasValue13" << "MeasValue14" << "MeasValue15" << "MeasValue16");
const QStringList MODELMessage = (QStringList() << "" << "MODEL" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSS" << "PRN" << "Block" << "SVN" << "ArcNumber" << "ArcLength" << "SatElevation" << "SatAzimuth" << "MeasurementID" << "OrbitType" << "IOD" << "GLOFrequencyNumber" << "GNSSTimeOffsets"
                            << "MeasValue" << "SignalFlightTime" << "SatPositionX" << "SatPositionY" << "SatPositionZ" << "SatVelocityX" << "SatVelocityY" << "SatVelocityZ" << "Sat-RecRange" << "SatClockOffset" << "SatPhaseCentreProjection" << "SatPhaseCentreVariation" << "RecPhaseCentreProjection"
                            << "RecPhaseCentreVariation" << "RecAntennaOffset" << "Relativity" << "Wind-up" << "SlantTroposphere" << "SlantIonosphere" << "GravitationalDelay" << "SolidTides" << "" << "" << "" << "InterSystemClockBias" << "P1-C1DCB(GPS)" << "TGD" << "InterSignalCorrection"
                            << "DCBforBDS" << "DCBSum" << "SNR" << "ModeValue");
const QStringList SATSELMessage = (QStringList() << "" << "SATSEL" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSS" << "PRN" << "ErrorCode" << "Status");
const QStringList PREFITMessage = (QStringList() << "" << "PREFIT" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSS" << "PRN" << "Block" << "SVN" << "ArcNumber" << "ArcLength" << "SatElevation" << "SatAzimuth" << "MeasurementID" << "SmoothMeasID" << "PrefitValue" << "MeasValue" << "SmoothMeasValue"
                             << "ModelValue" << "XPartialDerivative" << "YPartialDerivative" << "ZPartialDerivative" << "TPartialDerivative" << "WeightInverse" << "Mapping" << "MeasWavelength" << "GLOFrequencyNumber");
const QStringList EPOCHSATMessage = (QStringList() << "" << "EPOCHSAT" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "MeasurementID" << "SmoothMeasID" << "ObservedSatNumber" << "SelectedSatNumber" << "GPSIdentifier(G)" << "SelectedGPSsNumber" << "GALIdentifier(E)" << "SelectedGALsNumber"
                               << "GLOIdentifier(R)" << "SelectedGLOsNumber" << "GEOIdentifier(S)" << "SelectedSBASsNumber" << "BDSIdentifier(C)" << "SelectedBDSsNumber" << "QZSSIdentifier(J)" << "SelectedQZSSsNumber" << "IRNSSIdentifier(I)" << "SelectedIRNSSsNumber" << "UnselectedSatNumber"
                               << "GPSIdentifier(G)" << "UnselectedGPSsNumber" << "GALIdentifier(E)" << "UnselectedGALsNumber" << "GLOIdentifier(R)" << "UnselectedGLOsNumber" << "GEOIdentifier(S)" << "UnselectedSBASsNumber" << "BDSIdentifier(C)" << "UnselectedBDSsNumber" << "QZSSIdentifier(J)"
                               << "UnselectedQZSSsNumber" << "IRNSSIdentifier(I)" << "UnselectedIRNSSsNumber" << "Sat1" << "Sat2" << "Sat3" << "Sat4" << "Sat5" << "Sat6" << "Sat7" << "Sat8" << "Sat9" << "Sat10" << "Sat11" << "Sat12" << "Sat13" << "Sat14" << "Sat15" << "Sat16" << "Sat17" << "Sat18"
                               << "Sat19" << "Sat20" << "Sat21" << "Sat22" << "Sat23" << "Sat24" << "Sat25" << "Sat26" << "Sat27" << "Sat28" << "Sat29" << "Sat30");
const QStringList POSTFITMessage = (QStringList() << "" << "POSTFIT" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSS" << "PRN" << "Block" << "SVN" << "ArcNumber" << "ArcLength" << "SatElevation" << "SatAzimuth" << "MeasurementID" << "SmoothMeasID" << "PostfitValue" << "MeasValue"
                              << "SmoothMeasValue" << "FittedMeasValue" << "Ambiguities" << "");
const QStringList FILTERMessage = (QStringList() << "" << "FILTER" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSSReference" << "ISCBNumber" << "UnknownsNumber" << "RecPositionX" << "RecPositionY" << "RecPositionZ" << "RecClockOffset" << "GPS-ISCB" << "GAL-ISCB" << "GLO-ISCB" << "GEO-ISCB"
                             << "BDS-ISCB" << "QZSS-ISCB" << "IRNSS-ISCB" << "TropoZTD");
const QStringList OUTPUTMessage = (QStringList() << "" << "OUTPUT" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "NavigationMode" << "DirectionMode" << "TotalSatNumber" << "TotalGNSSNumber" << "GNSSsUsed" << "FormalErrorRecXYZ" << "RecPositionX" << "RecPositionY" << "RecPositionZ" << "DeltaRecX"
                             << "DeltaRecY" << "DeltaRecZ" << "FormalErrorRecX" << "FormalErrorRecY" << "FormalErrorRecZ" << "RecLatitude" << "RecLongitude" << "RecHeight" << "DeltaRecN" << "DeltaRecE" << "DeltaRecU" << "FormalErrorRecN" << "FormalErrorRecE" << "FormalErrorRecU" << "DeltaRecH"
                             << "DeltaRecV" << "DeltaRec3D" << "GNSSReference" << "RecClockOffset" << "FormalErrorRecClock" << "GDOP" << "PDOP" << "TDOP" << "HDOP" << "VDOP" << "ZTD(IncludingNominalValue)" << "ZTD(ExcludingNominalValue)" << "FormalErrorZTD");
const QStringList SBASCORRMessage = (QStringList() << "" << "SBASCORR" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSS" << "PRN" << "Block" << "SVN" << "ArcNumber" << "ArcLength" << "SatElevation" << "SatAzimuth" << "SBASMode" << "GEOPRN" << "PrefitResidual" << "MeasurementID" << "SmoothMeasID"
                               << "GeomatricRange" << "RelativityCorrection" << "SatClockOffset" << "TGDCorrection" << "IPPLatitude" << "IPPLongitude" << "IonoCorrection" << "TropoCorrection" << "PRC" << "RRC" << "FastCorrDegFactor" << "PRCTime-out" << "RRCTime-out" << "PRCTimeReference"
                               << "UDRETimeReference" << "FastCorrDegTimeRef" << "SatPositionX" << "SatPositionY" << "SatPositionZ" << "LTC-SatX" << "LTC-SatY" << "LTC-SatZ" << "LTC-SatClock" << "IODPFastCorrection" << "IODF" << "FastCorrSatSlot" << "IODPLongTermCorr" << "LongTermCorrSatSlot"
                               << "IODE" << "IODS" << "IODPClk-ephCovMatrix" << "Clk-ephCovMatrixSlot" << "IonoModelFlag");
const QStringList SBASVARMessage = (QStringList() << "" << "SBASVAR" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSS" << "PRN" << "Block" << "SVN" << "ArcNumber" << "ArcLength" << "SatElevation" << "SatAzimuth" << "SBASMode" << "GEOPRN" << "SigmaTotal" << "SigmaFast&LongTerm" << "SigmaUDRE"
                              << "DeltaUDRE" << "DeltaUDREDataSource" << "DegradationFastCorr" << "DegradationRRC" << "DegradationLongTerm&Fast" << "DegradationEnRouteNPA" << "RSSUFlag" << "UIVESigma" << "SigmaTropo" << "SigmaAirborne" << "SigmaNoise" << "SigmaMultiPath" << "SigmaDivergence");
const QStringList SBASIONOMessage = (QStringList() << "" << "SBASIONO" << "Year" << "DoY" << "SecondsofDoy" << "TimeofDay" << "GNSS" << "PRN" << "SatElevation" << "SatAzimuth" << "SBASMode" << "GEOPRN" << "IPPLatitude" << "IPPLongitude" << "InterpolationMode" << "Vertex1IODI" << "Vertex1BandNumber"
                               << "Vertex1IGP" << "Vertex1IGPReceptionTime" << "Vertex1IGPLatitude" << "Vertex1IGPLongitude" << "Vertex1Delay" << "Vertex1Variance" << "Vertex1Degradation" << "Vertex1InterpolatedDelay" << "Vertex1InterpolatedVariance" << "Vertex1Weight" << "Vertex2IODI"
                               << "Vertex2BandNumber" << "Vertex2IGP" << "Vertex2IGPReceptionTime" << "Vertex2IGPLatitude" << "Vertex2IGPLongitude" << "Vertex2Delay" << "Vertex2Variance" << "Vertex2Degradation" << "Vertex2InterpolatedDelay" << "Vertex2InterpolatedVariance" << "Vertex2Weight"
                               << "Vertex3IODI" << "Vertex3BandNumber" << "Vertex3IGP" << "Vertex3IGPReceptionTime" << "Vertex3IGPLatitude" << "Vertex3IGPLongitude" << "Vertex3Delay" << "Vertex3Variance" << "Vertex3Degradation" << "Vertex3InterpolatedDelay" << "Vertex3InterpolatedVariance"
                               << "Vertex3Weight" << "Vertex4IODI" << "Vertex4BandNumber" << "Vertex4IGP" << "Vertex4IGPReceptionTime" << "Vertex4IGPLatitude" << "Vertex4IGPLongitude" << "Vertex4Delay" << "Vertex4Variance" << "Vertex4Degradation" << "Vertex4InterpolatedDelay"
                               << "Vertex4InterpolatedVariance" << "Vertex4Weight" << "MappingFunction" << "SlantDelay" << "SlantSigma");
const QStringList SBASUNSELMessage = (QStringList() << "" << "SBASUNSEL" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSS" << "PRN" << "SBASMode" << "GEOPRN" << "ErrorCode" << "ErrorMessage");
const QStringList SBASDFMCCORRMessage = (QStringList() << "" << "SBASDFMCCORR" << "Year" << "DoY" << "SecondofDay" << "TimeofDay" << "GNSS" << "PRN" << "Block" << "SVN" << "ArcNumber" << "ArcLength" << "SatElevation" << "SatAzimuth" << "SBASMode" << "GEOPRN" << "MeasurementID" << "SmoothMeasID"
                                   << "PrefitValue" << "MeasValue" << "SmoothMeasValue" << "ModelledRange" << "Relativity" << "ClockOffset" << "TGD" << "Troposphere" << "SatPositionX" << "SatPositionY" << "SatPositionZ" << "SatCorrectionX" << "SatCorrectionY" << "SatCorrectionZ"
                                   << "SatCorrectionClock" << "DFREI" << "DFREITime" << "MT32Time" << "MT39/40Time" << "MT32Validity" << "MT39/40Validity" << "IODM" << "IODN" << "SlotNumber");
const QStringList SBASDFMCCVARMessage = (QStringList() << "" << "SBASDFMCCVAR" << "Year" << "DoY" << "SecondofDay" << "TimeofDay" << "GNSS" << "PRN" << "Block" << "SVN" << "ArcNumber" << "ArcLength" << "SatElevation" << "SatAzimuth" << "SBASMode" << "GEOPRN" << "SigmaTotal" << "DFC" << "DFREI"
                                   << "DFREIFlag" << "DFRE" << "DeltaDFRE" << "DegradationCorrection" << "DegradationEnRouteNPA" << "SigmaIono" << "SigmaTropo" << "SigmaTotal" << "SigmaNoise" << "SigmaMultipath" << "SigmaDivergence" << "Ccorr" << "Icorr" << "Rcorr" << "DeltaRcorrFactor" << "RcorrSV"
                                   << "Cer" << "Ccovariance");
const QStringList SBASDFMCUNSELMessage = (QStringList() << "" << "SBASDFMCUNSEL" << "Year" << "DoY" << "SecondofDay" << "TimeofDay" << "GNSS" << "PRN" << "SBASMode" << "GEOPRN" << "ErrorCode" << "ErrorMessage");
const QStringList SBASOUTMessage = (QStringList() << "" << "SBASOUT" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GPSWeek" << "TimeofWeek" << "ReceiverID" << "ModeID" << "SBASMode" << "GEOPRN" << "DeltaN" << "DeltaE" << "DeltaU" << "HPE" << "HPL" << "HAL" << "VPE" << "VPL" << "VAL" << "3DPositioningError"
                              << "RecClockOffset" << "SatellitesInView" << "SatellitesUsed" << "Sat1" << "Sat2" << "Sat3" << "Sat4" << "Sat5" << "Sat6" << "Sat7" << "Sat8" << "Sat9" << "Sat10" << "Sat11" << "Sat12" << "Sat13" << "Sat14" << "Sat15" << "Sat16" << "Sat17" << "Sat18" << "Sat19" << "Sat20");
const QStringList DGNSSMessage = (QStringList() << "" << "DGNSS" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSS" << "PRN" << "PRC" << "RRC" << "RRCTime" << "DeltaPRC" << "DeltaRRC" << "DeltaRRCTime" << "SigmaTotal" << "SigmaUDRE" << "SigmaDegradation" << "SigmaAir" << "SigmaMultipath" << "SigmaInflation");
const QStringList SATSTATMessage = (QStringList() << "" << "SATSTAT" << "GNSS" << "PRN" << "TotalEpochs" << "SISREMean" << "SISRERMS" << "SISREStdDev" << "SISREOrbitMean" << "SISREOrbitRMS" << "SISREOrbitStdDev" << "3DOrbitMean" << "3DOrbitRMS" << "3DOrbitStdDev" << "ClockMean" << "ClockRMS" << "ClockStdDev"
                              << "DCBMean" << "DCBRMS" << "DCBStdDev" << "RadialMean" << "RadialRMS" << "RadialStdDev" << "AlongTrackMean" << "AlongTrackRMS" << "AlongTrackStdDev" << "CrossTrackMean" << "CrossTrackRMS" << "CrossTrackStdDev");
const QStringList SATSTATTOTMessage = (QStringList() << "" << "SATSTATTOT" << "SamplesNumber" << "SISREMean" << "SISRERMS" << "SISREStdDev" << "SISREOrbitMean" << "SISREOrbitRMS" << "SISREOrbitStdDev" << "3DOrbitMean" << "3DOrbitRMS" << "3DOrbitStdDev" << "ClockMean" << "ClockRMS" << "ClockStdDev" << "DCBMean"
                                 << "DCBRMS" << "DCBStdDev" << "RadialMean" << "RadialRMS" << "RadialStdDev" << "AlongTrackMean" << "AlongTrackRMS" << "AlongTrackStdDev" << "CrossTrackMean" << "CrossTrackRMS" << "CrossTrackStdDev");
const QStringList SATDIFFMessage = (QStringList() << "" << "SATDIFF" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSS" << "PRN" << "SISREDifference" << "SISREOrbitDifference" << "3DOrbitDifference" << "ClockDifference" << "DCBDifference" << "RadialDifference" << "AlongTrackDifference"
                              << "CrossTrackDifference" << "XDifference" << "YDifference" << "ZDifference" << "OrbitType" << "IODEFirstSource" << "IODESecondSource" << "HealthFirstSource" << "HealthSecondSource");
const QStringList SATPVTMessage = (QStringList() << "" << "SATPVT" << "Year" << "DoY" << "SecondsofDay" << "TimeofDay" << "GNSS" << "PRN" << "Block" << "SVN" << "SatElevation" << "SatAzimuth" << "SatPositionX" << "SatPositionY" << "SatPositionZ" << "SatVelocityX" << "SatVelocityY" << "SatVelocityZ" << "SatLatitude" << "SatLongitude" << "SatHeight" << "SatClockOffset" << "OrbitType" << "IODE"
                               << "HealthStatus");
const QStringList AllMessages[]={EmptyMessage,USERADDEDERRORMessage,INPUTMessage,CSMessage,SFCSMessage,MWCSMessage,LICSMessage,IGFCSMessage,MEASMessage,MODELMessage,SATSELMessage,PREFITMessage,
                          EPOCHSATMessage,POSTFITMessage,FILTERMessage,OUTPUTMessage,SBASCORRMessage,SBASVARMessage,SBASIONOMessage,SBASUNSELMessage,SBASDFMCCORRMessage,SBASDFMCCVARMessage,
                          SBASDFMCUNSELMessage,SBASOUTMessage,DGNSSMessage,SATSTATMessage,SATSTATTOTMessage,SATDIFFMessage,SATPVTMessage};

//Set tooltips for each item in the Conditions combo box for plot 1
void gLAB_GUI::set_conditionsComboBoxPlot1_OutputMessagesTooltips() {
    ui->comboBoxPlot1Condition->setItemData(0,ui->comboBoxPlot1Condition->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(1,ui->checkBoxPrintUsererror->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(2,ui->checkBoxPrintInput->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(3,ui->checkBoxPrintCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(4,ui->checkBoxPrintSFCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(5,ui->checkBoxPrintMWCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(6,ui->checkBoxPrintLICS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(7,ui->checkBoxPrintIGFCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(8,ui->checkBoxPrintMeas->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(9,ui->checkBoxPrintModel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(10,ui->checkBoxPrintSatsel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(11,ui->checkBoxPrintPrefit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(12,ui->checkBoxPrintEpochsat->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(13,ui->checkBoxPrintPostfit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(14,ui->checkBoxPrintFilter->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(15,ui->checkBoxPrintOutput->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(16,ui->checkBoxPrintSbascor->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(17,ui->checkBoxPrintSbasvar->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(18,ui->checkBoxPrintSbasiono->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(19,ui->checkBoxPrintSbasunsel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(20,ui->checkBoxPrintSbasDFMCCor->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(21,ui->checkBoxPrintSbasDFMCVar->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(22,ui->checkBoxPrintSbasDFMCUnsel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(23,ui->checkBoxPrintSbasout->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(24,ui->checkBoxPrintDgnss->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(25,ui->checkBoxPrintSatstat->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(26,ui->checkBoxPrintSatstattot->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(27,ui->checkBoxPrintSatdiff->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(28,ui->checkBoxPrintSatpvt->toolTip(),Qt::ToolTipRole);
}

//Set tooltips for each item in the Conditions combo box for plot 2
void gLAB_GUI::set_conditionsComboBoxPlot2_OutputMessagesTooltips() {
    ui->comboBoxPlot2Condition->setItemData(0,ui->comboBoxPlot2Condition->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(1,ui->checkBoxPrintUsererror->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(2,ui->checkBoxPrintInput->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(3,ui->checkBoxPrintCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(4,ui->checkBoxPrintSFCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(5,ui->checkBoxPrintMWCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(6,ui->checkBoxPrintLICS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(7,ui->checkBoxPrintIGFCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(8,ui->checkBoxPrintMeas->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(9,ui->checkBoxPrintModel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(10,ui->checkBoxPrintSatsel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(11,ui->checkBoxPrintPrefit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(12,ui->checkBoxPrintEpochsat->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(13,ui->checkBoxPrintPostfit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(14,ui->checkBoxPrintFilter->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(15,ui->checkBoxPrintOutput->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(16,ui->checkBoxPrintSbascor->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(17,ui->checkBoxPrintSbasvar->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(18,ui->checkBoxPrintSbasiono->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(19,ui->checkBoxPrintSbasunsel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(20,ui->checkBoxPrintSbasDFMCCor->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(21,ui->checkBoxPrintSbasDFMCVar->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(22,ui->checkBoxPrintSbasDFMCUnsel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(23,ui->checkBoxPrintSbasout->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(24,ui->checkBoxPrintDgnss->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(25,ui->checkBoxPrintSatstat->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(26,ui->checkBoxPrintSatstattot->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(27,ui->checkBoxPrintSatdiff->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(28,ui->checkBoxPrintSatpvt->toolTip(),Qt::ToolTipRole);
}

//Set tooltips for each item in the Conditions combo box for plot 3
void gLAB_GUI::set_conditionsComboBoxPlot3_OutputMessagesTooltips() {
    ui->comboBoxPlot3Condition->setItemData(0,ui->comboBoxPlot3Condition->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(1,ui->checkBoxPrintUsererror->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(2,ui->checkBoxPrintInput->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(3,ui->checkBoxPrintCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(4,ui->checkBoxPrintSFCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(5,ui->checkBoxPrintMWCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(6,ui->checkBoxPrintLICS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(7,ui->checkBoxPrintIGFCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(8,ui->checkBoxPrintMeas->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(9,ui->checkBoxPrintModel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(10,ui->checkBoxPrintSatsel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(11,ui->checkBoxPrintPrefit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(12,ui->checkBoxPrintEpochsat->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(13,ui->checkBoxPrintPostfit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(14,ui->checkBoxPrintFilter->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(15,ui->checkBoxPrintOutput->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(16,ui->checkBoxPrintSbascor->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(17,ui->checkBoxPrintSbasvar->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(18,ui->checkBoxPrintSbasiono->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(19,ui->checkBoxPrintSbasunsel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(20,ui->checkBoxPrintSbasDFMCCor->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(21,ui->checkBoxPrintSbasDFMCVar->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(22,ui->checkBoxPrintSbasDFMCUnsel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(23,ui->checkBoxPrintSbasout->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(24,ui->checkBoxPrintDgnss->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(25,ui->checkBoxPrintSatstat->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(26,ui->checkBoxPrintSatstattot->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(27,ui->checkBoxPrintSatdiff->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(28,ui->checkBoxPrintSatpvt->toolTip(),Qt::ToolTipRole);
}

//Set tooltips for each item in the Conditions combo box for plot 4
void gLAB_GUI::set_conditionsComboBoxPlot4_OutputMessagesTooltips() {
    ui->comboBoxPlot4Condition->setItemData(0,ui->comboBoxPlot4Condition->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(1,ui->checkBoxPrintUsererror->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(2,ui->checkBoxPrintInput->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(3,ui->checkBoxPrintCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(4,ui->checkBoxPrintSFCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(5,ui->checkBoxPrintMWCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(6,ui->checkBoxPrintLICS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(7,ui->checkBoxPrintIGFCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(8,ui->checkBoxPrintMeas->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(9,ui->checkBoxPrintModel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(10,ui->checkBoxPrintSatsel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(11,ui->checkBoxPrintPrefit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(12,ui->checkBoxPrintEpochsat->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(13,ui->checkBoxPrintPostfit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(14,ui->checkBoxPrintFilter->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(15,ui->checkBoxPrintOutput->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(16,ui->checkBoxPrintSbascor->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(17,ui->checkBoxPrintSbasvar->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(18,ui->checkBoxPrintSbasiono->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(19,ui->checkBoxPrintSbasunsel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(20,ui->checkBoxPrintSbasDFMCCor->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(21,ui->checkBoxPrintSbasDFMCVar->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(22,ui->checkBoxPrintSbasDFMCUnsel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(23,ui->checkBoxPrintSbasout->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(24,ui->checkBoxPrintDgnss->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(25,ui->checkBoxPrintSatstat->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(26,ui->checkBoxPrintSatstattot->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(27,ui->checkBoxPrintSatdiff->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(28,ui->checkBoxPrintSatpvt->toolTip(),Qt::ToolTipRole);
}

// Function to Clear the Plots configurations
void gLAB_GUI::on_pushButtonPlotClear_clicked() {
    this->on_checkBoxAutoLimits_clicked(true);
    this->on_checkBoxAutoTicks_clicked(true);
    this->on_radioButtonPlotNr1_clicked();
    ui->comboBoxLabelPosition->setCurrentIndex(0);
    ui->checkBoxExpandFigureToMargin->setChecked(false);
    ui->lineEditPlotTitle->setText("");
    ui->lineEditPlotXLabel->setText("");
    ui->lineEditPlotYLabel->setText("");
    ui->lineEditFractionalText->setText("");
    ui->lineEditWaterMark->setText("");
    ui->lineEditPlotXmin->setText("");
    ui->lineEditPlotXmax->setText("");
    ui->lineEditPlotYmin->setText("");
    ui->lineEditPlotYmax->setText("");
    ui->lineEditXTickNum->setText("");
    ui->lineEditYTickNum->setText("");
    ui->pushButtonPlot->setEnabled(false);
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    ui->checkBoxPEPercentiles->setChecked(false);
    ui->checkBoxPLPercentiles->setChecked(false);

    //Enable all options disabled by Stanford or Stanford-ESA templates
    StanfordPlotSelected = 0;
    StanfordESAPlotSelected = 0;
    ui->radioButtonPlotNr2->setDisabled(false);
    ui->radioButtonPlotNr3->setDisabled(false);
    ui->radioButtonPlotNr4->setDisabled(false);
    ui->comboBoxPlot1Condition->setDisabled(false);
    ui->comboBoxPlot1ConditionOutput->setDisabled(false);
    ui->lineEditPlot1Condition->setDisabled(false);
    ui->comboBoxPlot1TypeLine->setDisabled(false);
    ui->comboBoxPlot1ColorLine->setDisabled(false);
    ui->lineEditPlot1Xcolumn->setDisabled(false);
    ui->lineEditPlot1Ycolumn->setDisabled(false);
    ui->lineEditPlot1LegendLabel->setDisabled(false);

    ui->lineEditFractionalText->setDisabled(false);
    ui->comboBoxLabelPosition->setDisabled(false);
    ui->checkBoxAutoLimits->setDisabled(false);
    ui->checkBoxAutoTicks->setDisabled(false);
    ui->lineEditPlotXmin->setDisabled(false);
    ui->lineEditPlotYmin->setDisabled(false);
    ui->lineEditPlotXmax->setDisabled(false);
    ui->lineEditPlotYmax->setDisabled(false);


    // Plot Nr 1
    ui->lineEditPlot1SourceFile->setText("");
    ui->comboBoxPlot1TypeLine->setCurrentIndex(0);
    ui->comboBoxPlot1ConditionOutput->setCurrentIndex(0);
    this->on_comboBoxPlot1Condition_currentIndexChanged(0);
    ui->comboBoxPlot1ColorLine->setCurrentIndex(0);
    ui->lineEditPlot1Xcolumn->setText("");
    ui->lineEditPlot1Ycolumn->setText("");
    ui->lineEditPlot1LegendLabel->setText("");
    // Plot Nr 2
    ui->lineEditPlot2SourceFile->setText("");
    ui->comboBoxPlot2TypeLine->setCurrentIndex(0);
    ui->comboBoxPlot2ConditionOutput->setCurrentIndex(0);
    this->on_comboBoxPlot2Condition_currentIndexChanged(0);
    ui->comboBoxPlot2ColorLine->setCurrentIndex(1);
    ui->lineEditPlot2Xcolumn->setText("");
    ui->lineEditPlot2Ycolumn->setText("");
    ui->lineEditPlot2LegendLabel->setText("");
    // Plot Nr 3
    ui->lineEditPlot3SourceFile->setText("");
    ui->comboBoxPlot3TypeLine->setCurrentIndex(0);
    ui->comboBoxPlot3ConditionOutput->setCurrentIndex(0);
    this->on_comboBoxPlot3Condition_currentIndexChanged(0);
    ui->comboBoxPlot3ColorLine->setCurrentIndex(2);
    ui->lineEditPlot3Xcolumn->setText("");
    ui->lineEditPlot3Ycolumn->setText("");
    ui->lineEditPlot3LegendLabel->setText("");
    // Plot Nr 4
    ui->lineEditPlot4SourceFile->setText("");
    ui->comboBoxPlot4TypeLine->setCurrentIndex(0);
    ui->comboBoxPlot4ConditionOutput->setCurrentIndex(0);
    this->on_comboBoxPlot4Condition_currentIndexChanged(0);
    ui->comboBoxPlot4ColorLine->setCurrentIndex(3);
    ui->lineEditPlot4Xcolumn->setText("");
    ui->lineEditPlot4Ycolumn->setText("");
    ui->lineEditPlot4LegendLabel->setText("");
}

// Function to show or hide the plot limits
void gLAB_GUI::on_checkBoxAutoLimits_clicked(bool checked) {
    ui->checkBoxAutoLimits->setChecked(checked);
    ui->frameAutoLimits->setHidden(checked);
}

// Function to show or hide the tick limits
void gLAB_GUI::on_checkBoxAutoTicks_clicked(bool checked) {
    ui->checkBoxAutoTicks->setChecked(checked);
    ui->frameAutoTicks->setHidden(checked);
}


// Function to set the correct stacked widget in Analysis mode
void gLAB_GUI::on_radioButtonPlotNr1_clicked() {
    ui->radioButtonPlotNr1->setChecked(true);
    ui->stackedWidgetPlotNr->setCurrentIndex(0);
}

// Function to set the correct stacked widget in Analysis mode
void gLAB_GUI::on_radioButtonPlotNr2_clicked() {
    ui->radioButtonPlotNr2->setChecked(true);
    ui->stackedWidgetPlotNr->setCurrentIndex(1);
}

// Function to set the correct stacked widget in Analysis mode
void gLAB_GUI::on_radioButtonPlotNr3_clicked() {
    ui->radioButtonPlotNr3->setChecked(true);
    ui->stackedWidgetPlotNr->setCurrentIndex(2);
}

// Function to set the correct stacked widget in Analysis mode
void gLAB_GUI::on_radioButtonPlotNr4_clicked() {
    ui->radioButtonPlotNr4->setChecked(true);
    ui->stackedWidgetPlotNr->setCurrentIndex(3);
}

////////////////// Plot Nr 1 //////////////////
///////////////////////////////////////////////
// Function to set the correct stacked window in the condition of the Plot Nr 1
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot1Condition_currentIndexChanged(int index) {
    ui->comboBoxPlot1Condition->setCurrentIndex(index);
    this->change_comboBoxPlot1Xcolumn_message(index);
    this->change_comboBoxPlot1Ycolumn_message(index);
    this->on_comboBoxPlot1ConditionGNSS_currentIndexChanged(0);
    ui->lineEditPlot1Xcolumn->setText("1"); // To make the change to "empty" effective
    ui->lineEditPlot1Ycolumn->setText("1"); // To make the change to "empty" effective
    ui->lineEditPlot1Xcolumn->setText("");
    ui->lineEditPlot1Ycolumn->setText("");
    /*if ( index == 0 ) {
        ui->lineEditPlot1Xcolumn->setHidden(true);
        ui->lineEditPlot1Ycolumn->setHidden(true);
    } else {
        ui->lineEditPlot1Xcolumn->setHidden(false);
        ui->lineEditPlot1Ycolumn->setHidden(false);
    }*/
    switch ( index ) {
        case 0 : { // Nothing
            ui->stackedWidgetPlot1Condition->setCurrentIndex(0);
            ui->lineEditPlot1Condition->setText("");
            break;
        }
        case 1 : { // USERADDEDERROR
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"USERADDEDERROR\")");
            break;
        }
        case 2 : { // Input
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"INPUT\")");
            break;
        }
        case 3 : { // Cycle slips
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"CS\")");
            break;
        }
        case 4 : { // SF Cycle slips
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"SFCSDATA\")");
            break;
        }
        case 5 : { // MW Cycle slips
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"MWCSDATA\")");
            break;
        }
        case 6 : { // LI Cycle slips
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"LICSDATA\")");
            break;
        }
        case 7 : { // IGF Cycle slips
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"IGFCSDATA\")");
            break;
        }
        case 8 : { // Meas
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"MEAS\")");
            break;
        }
        case 9 : { // Model
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"MODEL\")");
            break;
        }
        case 10 : { // Satsel
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"SATSEL\")");
            break;
        }
        case 11 : { // Prefit
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"PREFIT\")");
            break;
        }
        case 12: { // Epochsat
            ui->stackedWidgetPlot1Condition->setCurrentIndex(0);
            ui->lineEditPlot1Condition->setText("($1==\"EPOCHSAT\")");
            break;
        }
        case 13 : { // Postfit
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"POSTFIT\")");
            break;
        }
        case 14 : { // Filter
            ui->stackedWidgetPlot1Condition->setCurrentIndex(0);
            ui->lineEditPlot1Condition->setText("($1==\"FILTER\")");
            break;
        }
        case 15 : { // Output
            ui->stackedWidgetPlot1Condition->setCurrentIndex(2);
            ui->lineEditPlot1Condition->setText("($1==\"OUTPUT\")");
            break;
        }
        case 16 : { // SBASCORR
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"SBASCORR\")");
            break;
        }
        case 17 : { // SBASVAR
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"SBASVAR\")");
            break;
        }
        case 18 : { // SBASIONO
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"SBASIONO\")");
            break;
        }
        case 19 : { // SBASUNSEL
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"SBASUNSEL\")");
            break;
        }
        case 20 : { // SBASDFMCCORR
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"SBASDFMCCORR\")");
            break;
        }
        case 21 : { // SBASDFMCVAR
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"SBASDFMCVAR\")");
            break;
        }
        case 22 : { // SBASDFMCUNSEL
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"SBASDFMCUNSEL\")");
            break;
        }
        case 23 : { // SBASOUT
            ui->stackedWidgetPlot1Condition->setCurrentIndex(2);
            ui->lineEditPlot1Condition->setText("($1==\"SBASOUT\")");
            break;
        }
        case 24 : { // DGNSS
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"DGNSS\")");
            break;
        }
        case 25 : { // Satstat
            ui->stackedWidgetPlot1Condition->setCurrentIndex(0);
            ui->lineEditPlot1Condition->setText("($1==\"SATSTAT\")");
            break;
        }
        case 26 : { // Satstattot
            ui->stackedWidgetPlot1Condition->setCurrentIndex(0);
            ui->lineEditPlot1Condition->setText("($1==\"SATSTATTOT\")");
            break;
        }
        case 27 : { // Satdiff
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"SATDIFF\")");
            break;
        }
        case 28 : { // Satpvt
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"SATPVT\")");
            break;
        }
    }
}

// Function to set the correct stacked window in the condition of the Plot Nr 1
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot1ConditionGNSS_currentIndexChanged(int index){
    ui->comboBoxPlot1ConditionGNSS->setCurrentIndex(index);
    if (index==0){
        ui->stackedWidgetPlot1ConditionGNSS->setCurrentIndex(0);
        this->on_comboBoxPlot1ConditionGPS_currentIndexChanged(0);
        ui->stackedWidgetPlot1ConditionGNSS->setEnabled(false);
        // Delete previous second condition (from ampersand to the end)
        QString text = ui->lineEditPlot1Condition->text();
        int end = text.indexOf("&", 0, Qt::CaseInsensitive);
        if ( end != -1 ) text = text.mid(0, end-1);
        ui->lineEditPlot1Condition->setText(text);
    } else if ( index>0 && index<=MAX_GNSS ) {
        ui->stackedWidgetPlot1ConditionGNSS->setEnabled(true);
        ui->stackedWidgetPlot1ConditionGNSS->setCurrentIndex(index-1);
        if (index==1) this->on_comboBoxPlot1ConditionGPS_currentIndexChanged(0);
        else if (index==2) this->on_comboBoxPlot1ConditionGalileo_currentIndexChanged(0);
        else if (index==3) this->on_comboBoxPlot1ConditionGLONASS_currentIndexChanged(0);
        else if (index==4) this->on_comboBoxPlot1ConditionBDS_currentIndexChanged(0);
        else if (index==5) this->on_comboBoxPlot1ConditionGEO_currentIndexChanged(0);
        else if (index==6) this->on_comboBoxPlot1ConditionQZSS_currentIndexChanged(0);
        else if (index==7) this->on_comboBoxPlot1ConditionIRNSS_currentIndexChanged(0);
    }
}
void gLAB_GUI::on_comboBoxPlot1ConditionGPS_currentIndexChanged(int index) {
    ui->comboBoxPlot1ConditionGPS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot1Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot1Condition->currentIndex()!=19) text = (text + " & ($6==\"GPS\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"GPS\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot1Condition->currentIndex()!=19) text = (text + " & ($6==\"GPS\")");
        else text = (text + " & (&8==\"GPS\")");
    }
    ui->lineEditPlot1Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot1ConditionGalileo_currentIndexChanged(int index){
    ui->comboBoxPlot1ConditionGalileo->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot1Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot1Condition->currentIndex()!=1) text = (text + " & ($6==\"GAL\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"GAL\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot1Condition->currentIndex()!=1) text = (text + " & ($6==\"GAL\")");
        else text = (text + " & (&8==\"GAL\")");
    }
    ui->lineEditPlot1Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot1ConditionGLONASS_currentIndexChanged(int index){
    ui->comboBoxPlot1ConditionGLONASS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot1Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot1Condition->currentIndex()!=1) text = (text + " & ($6==\"GLO\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"GLO\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot1Condition->currentIndex()!=1) text = (text + " & ($6==\"GLO\")");
        else text = (text + " & (&8==\"GLO\")");
    }
    ui->lineEditPlot1Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot1ConditionGEO_currentIndexChanged(int index){
    ui->comboBoxPlot1ConditionGEO->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot1Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot1Condition->currentIndex()!=1) text = (text + " & ($6==\"GEO\") & ($7==%1)").arg(index+119);
        else text = (text + " & (&8==\"GEO\") & ($9==%1)").arg(index+119);
    } else {
        if (ui->comboBoxPlot1Condition->currentIndex()!=1) text = (text + " & ($6==\"GEO\")");
        else text = (text + " & (&8==\"GEO\")");
    }
    ui->lineEditPlot1Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot1ConditionBDS_currentIndexChanged(int index){
    ui->comboBoxPlot1ConditionBDS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot1Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot1Condition->currentIndex()!=1) text = (text + " & ($6==\"BDS\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"BDS\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot1Condition->currentIndex()!=1) text = (text + " & ($6==\"BDS\")");
        else text = (text + " & (&8==\"BDS\")");
    }
    ui->lineEditPlot1Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot1ConditionQZSS_currentIndexChanged(int index){
    ui->comboBoxPlot1ConditionQZSS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot1Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot1Condition->currentIndex()!=1) text = (text + " & ($6==\"QZS\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"QZS\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot1Condition->currentIndex()!=1) text = (text + " & ($6==\"QZS\")");
        else text = (text + " & (&8==\"QZS\")");
    }
    ui->lineEditPlot1Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot1ConditionIRNSS_currentIndexChanged(int index){
    ui->comboBoxPlot1ConditionIRNSS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot1Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot1Condition->currentIndex()!=1) text = (text + " & ($6==\"IRN\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"IRN\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot1Condition->currentIndex()!=1) text = (text + " & ($6==\"IRN\")");
        else text = (text + " & (&8==\"IRN\")");
    }
    ui->lineEditPlot1Condition->setText(text);
}

// Function to set the correct stacked window in the condition of the Plot Nr 1
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot1ConditionOutput_currentIndexChanged(int index) {
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot1Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        text = (text + " & ($6==%1)").arg(index-1);
    }
    ui->lineEditPlot1Condition->setText(text);
}

// Open dialog to set the plot source filename and path
void gLAB_GUI::on_pushButtonPlot1SourceFile_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("gLAB Output Files (*.out *.txt);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
    if ( this->fileExists( ui->lineEditPlot1SourceFile->text() ) == true ) ui->pushButtonPlot->setEnabled(true);
    else ui->pushButtonPlot->setEnabled(false);
}

//This is to enable Plot button when the user manually sets a text file name
void gLAB_GUI::on_lineEditPlot1SourceFile_textChanged() {
    if ( this->fileExists( ui->lineEditPlot1SourceFile->text() ) == true ) {
        ui->pushButtonPlot->setEnabled(true);
    } else {
        if ( ui->lineEditPlot1SourceFile->text().isEmpty()==false) {
            ui->pushButtonPlot->setEnabled(false);
        } else {
           if ( this->fileExists( ui->lineEditPlot2SourceFile->text() ) == true ||
                this->fileExists( ui->lineEditPlot3SourceFile->text() ) == true ||
                this->fileExists( ui->lineEditPlot4SourceFile->text() ) == true  ) {
               ui->pushButtonPlot->setEnabled(true);
           }
        }
    }
}

// Function to set the correct value of the combo box X column from line edit
void gLAB_GUI::on_lineEditPlot1Xcolumn_textChanged() {
    int index;
    if (ui->lineEditPlot1Xcolumn->text().contains(QRegularExpression("[^0-9]"))==true) {
        index=-1;
    } else {
        index = ui->lineEditPlot1Xcolumn->text().toInt();
    }
    ui->comboBoxPlot1Xcolumn->setCurrentIndex(index);
}
// Function to change the message items
void gLAB_GUI::change_comboBoxPlot1Xcolumn_message(int messageType){
    // clean all the items
    for (int i=ui->comboBoxPlot1Xcolumn->count()-1; i>=0; i--) ui->comboBoxPlot1Xcolumn->removeItem(i);
    // add new items
    for (int i=0; i<AllMessages[messageType].size(); i++) ui->comboBoxPlot1Xcolumn->addItem(AllMessages[messageType][i]);
}
// Functions to set the correct number in the X column line edit
void gLAB_GUI::on_comboBoxPlot1Xcolumn_currentIndexChanged(int index){
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}

// Function to set the correct value of the combo box Y column from line edit
void gLAB_GUI::on_lineEditPlot1Ycolumn_textChanged() {
    int index;
    if (ui->lineEditPlot1Ycolumn->text().contains(QRegularExpression("[^0-9]"))==true) {
        index=-1;
    } else {
        index = ui->lineEditPlot1Ycolumn->text().toInt();
    }
    ui->comboBoxPlot1Ycolumn->setCurrentIndex(index);
}
// Function to change the message items
void gLAB_GUI::change_comboBoxPlot1Ycolumn_message(int messageType){
    // clean all the items
    for (int i=ui->comboBoxPlot1Ycolumn->count()-1; i>=0; i--) ui->comboBoxPlot1Ycolumn->removeItem(i);
    // add new items
    for (int i=0; i<AllMessages[messageType].size(); i++) ui->comboBoxPlot1Ycolumn->addItem(AllMessages[messageType][i]);
}
// Functions to set the correct number in the X column line edit
void gLAB_GUI::on_comboBoxPlot1Ycolumn_currentIndexChanged(int index){
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}


////////////////// Plot Nr 2 //////////////////
///////////////////////////////////////////////
// Function to set the correct stacked window in the condition of the Plot Nr 2
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot2Condition_currentIndexChanged(int index) {
    ui->comboBoxPlot2Condition->setCurrentIndex(index);
    this->change_comboBoxPlot2Xcolumn_message(index);
    this->change_comboBoxPlot2Ycolumn_message(index);
    this->on_comboBoxPlot2ConditionGNSS_currentIndexChanged(0);
    ui->lineEditPlot2Xcolumn->setText("1"); // To make the change to "empty" effective
    ui->lineEditPlot2Ycolumn->setText("1"); // To make the change to "empty" effective
    ui->lineEditPlot2Xcolumn->setText("");
    ui->lineEditPlot2Ycolumn->setText("");
    /*if ( index == 0 ) {
        ui->lineEditPlot2Xcolumn->setHidden(true);
        ui->lineEditPlot2Ycolumn->setHidden(true);
    } else {
        ui->lineEditPlot2Xcolumn->setHidden(false);
        ui->lineEditPlot2Ycolumn->setHidden(false);
    }*/
    switch ( index ) {
        case 0 : { // Nothing
            ui->stackedWidgetPlot2Condition->setCurrentIndex(0);
            ui->lineEditPlot2Condition->setText("");
            break;
        }
        case 1 : { // USERADDEDERROR
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"USERADDEDERROR\")");
            break;
        }
        case 2 : { // Input
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"INPUT\")");
            break;
        }
        case 3 : { // Cycle slips
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"CS\")");
            break;
        }
        case 4 : { // SF Cycle slips
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"SFCSDATA\")");
            break;
        }
        case 5 : { // MW Cycle slips
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"MWCSDATA\")");
            break;
        }
        case 6 : { // LI Cycle slips
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"LICSDATA\")");
            break;
        }
        case 7 : { // IGF Cycle slips
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"IGFCSDATA\")");
            break;
        }
        case 8 : { // Meas
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"MEAS\")");
            break;
        }
        case 9 : { // Model
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"MODEL\")");
            break;
        }
        case 10 : { // Satsel
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"SATSEL\")");
            break;
        }
        case 11 : { // Prefit
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"PREFIT\")");
            break;
        }
        case 12: { // Epochsat
            ui->stackedWidgetPlot2Condition->setCurrentIndex(0);
            ui->lineEditPlot2Condition->setText("($1==\"EPOCHSAT\")");
            break;
        }
        case 13 : { // Postfit
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"POSTFIT\")");
            break;
        }
        case 14 : { // Filter
            ui->stackedWidgetPlot2Condition->setCurrentIndex(0);
            ui->lineEditPlot2Condition->setText("($1==\"FILTER\")");
            break;
        }
        case 15 : { // Output
            ui->stackedWidgetPlot2Condition->setCurrentIndex(2);
            ui->lineEditPlot2Condition->setText("($1==\"OUTPUT\")");
            break;
        }
        case 16 : { // SBASCORR
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"SBASCORR\")");
            break;
        }
        case 17 : { // SBASVAR
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"SBASVAR\")");
            break;
        }
        case 18 : { // SBASIONO
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"SBASIONO\")");
            break;
        }
        case 19 : { // SBASUNSEL
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"SBASUNSEL\")");
            break;
        }
        case 20 : { // SBASDFMCCORR
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"SBASDFMCCORR\")");
            break;
        }
        case 21 : { // SBASDFMCVAR
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"SBASDFMCVAR\")");
            break;
        }
        case 22 : { // SBASDFMCUNSEL
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"SBASDFMCUNSEL\")");
            break;
        }
        case 23 : { // SBASOUT
            ui->stackedWidgetPlot2Condition->setCurrentIndex(2);
            ui->lineEditPlot2Condition->setText("($1==\"SBASOUT\")");
            break;
        }
        case 24 : { // DGNSS
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"DGNSS\")");
            break;
        }
        case 25 : { // Satstat
            ui->stackedWidgetPlot2Condition->setCurrentIndex(0);
            ui->lineEditPlot2Condition->setText("($1==\"SATSTAT\")");
            break;
        }
        case 26 : { // Satstattot
            ui->stackedWidgetPlot2Condition->setCurrentIndex(0);
            ui->lineEditPlot2Condition->setText("($1==\"SATSTATTOT\")");
            break;
        }
        case 27 : { // Satdiff
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"SATDIFF\")");
            break;
        }
        case 28 : { // Satpvt
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"SATPVT\")");
            break;
        }
    }
}

// Function to set the correct stacked window in the condition of the Plot Nr 1
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot2ConditionGNSS_currentIndexChanged(int index){
    ui->comboBoxPlot2ConditionGNSS->setCurrentIndex(index);
    if (index==0){
        ui->stackedWidgetPlot2ConditionGNSS->setCurrentIndex(0);
        this->on_comboBoxPlot2ConditionGPS_currentIndexChanged(0);
        ui->stackedWidgetPlot2ConditionGNSS->setEnabled(false);
        // Delete previous second condition (from ampersand to the end)
        QString text = ui->lineEditPlot2Condition->text();
        int end = text.indexOf("&", 0, Qt::CaseInsensitive);
        if ( end != -1 ) text = text.mid(0, end-1);
        ui->lineEditPlot2Condition->setText(text);
    } else if ( index>0 && index<=MAX_GNSS ) {
        ui->stackedWidgetPlot2ConditionGNSS->setEnabled(true);
        ui->stackedWidgetPlot2ConditionGNSS->setCurrentIndex(index-1);
        if (index==1) this->on_comboBoxPlot2ConditionGPS_currentIndexChanged(0);
        else if (index==2) this->on_comboBoxPlot2ConditionGalileo_currentIndexChanged(0);
        else if (index==3) this->on_comboBoxPlot2ConditionGLONASS_currentIndexChanged(0);
        else if (index==4) this->on_comboBoxPlot2ConditionBDS_currentIndexChanged(0);
        else if (index==5) this->on_comboBoxPlot2ConditionGEO_currentIndexChanged(0);
        else if (index==6) this->on_comboBoxPlot2ConditionQZSS_currentIndexChanged(0);
        else if (index==7) this->on_comboBoxPlot2ConditionIRNSS_currentIndexChanged(0);
    }
}
void gLAB_GUI::on_comboBoxPlot2ConditionGPS_currentIndexChanged(int index) {
    ui->comboBoxPlot2ConditionGPS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot2Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot2Condition->currentIndex()!=19) text = (text + " & ($6==\"GPS\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"GPS\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot2Condition->currentIndex()!=19) text = (text + " & ($6==\"GPS\")");
        else text = (text + " & (&8==\"GPS\")");
    }
    ui->lineEditPlot2Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot2ConditionGalileo_currentIndexChanged(int index){
    ui->comboBoxPlot2ConditionGalileo->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot2Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot2Condition->currentIndex()!=1) text = (text + " & ($6==\"GAL\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"GAL\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot2Condition->currentIndex()!=1) text = (text + " & ($6==\"GAL\")");
        else text = (text + " & (&8==\"GAL\")");
    }
    ui->lineEditPlot2Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot2ConditionGLONASS_currentIndexChanged(int index){
    ui->comboBoxPlot2ConditionGLONASS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot2Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot2Condition->currentIndex()!=1) text = (text + " & ($6==\"GLO\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"GLO\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot2Condition->currentIndex()!=1) text = (text + " & ($6==\"GLO\")");
        else text = (text + " & (&8==\"GLO\")");
    }
    ui->lineEditPlot2Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot2ConditionGEO_currentIndexChanged(int index){
    ui->comboBoxPlot2ConditionGEO->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot2Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot2Condition->currentIndex()!=1) text = (text + " & ($6==\"GEO\") & ($7==%1)").arg(index+119);
        else text = (text + " & (&8==\"GEO\") & ($9==%1)").arg(index+119);
    } else {
        if (ui->comboBoxPlot2Condition->currentIndex()!=1) text = (text + " & ($6==\"GEO\")");
        else text = (text + " & (&8==\"GEO\")");
    }
    ui->lineEditPlot2Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot2ConditionBDS_currentIndexChanged(int index){
    ui->comboBoxPlot2ConditionBDS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot2Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot2Condition->currentIndex()!=1) text = (text + " & ($6==\"BDS\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"BDS\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot2Condition->currentIndex()!=1) text = (text + " & ($6==\"BDS\")");
        else text = (text + " & (&8==\"BDS\")");
    }
    ui->lineEditPlot2Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot2ConditionQZSS_currentIndexChanged(int index){
    ui->comboBoxPlot2ConditionQZSS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot2Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot2Condition->currentIndex()!=1) text = (text + " & ($6==\"QZS\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"QZS\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot2Condition->currentIndex()!=1) text = (text + " & ($6==\"QZS\")");
        else text = (text + " & (&8==\"QZS\")");
    }
    ui->lineEditPlot2Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot2ConditionIRNSS_currentIndexChanged(int index){
    ui->comboBoxPlot2ConditionIRNSS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot2Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot2Condition->currentIndex()!=1) text = (text + " & ($6==\"IRN\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"IRN\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot2Condition->currentIndex()!=1) text = (text + " & ($6==\"IRN\")");
        else text = (text + " & (&8==\"IRN\")");
    }
    ui->lineEditPlot2Condition->setText(text);
}

// Function to set the correct stacked window in the condition of the Plot Nr 1
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot2ConditionOutput_currentIndexChanged(int index) {
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot2Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        text = (text + " & ($6==%1)").arg(index-1);
    }
    ui->lineEditPlot2Condition->setText(text);
}

// Open dialog to set the plot source filename and path
void gLAB_GUI::on_pushButtonPlot2SourceFile_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("gLAB Output Files (*.out *.txt);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
    if ( this->fileExists( ui->lineEditPlot2SourceFile->text() ) == true ) ui->pushButtonPlot->setEnabled(true);
    else ui->pushButtonPlot->setEnabled(false);
}

//This is to enable Plot button when the user manually sets a text file name
void gLAB_GUI::on_lineEditPlot2SourceFile_textChanged() {
    if ( this->fileExists( ui->lineEditPlot2SourceFile->text() ) == true ) {
        ui->pushButtonPlot->setEnabled(true);
    } else {
        if ( ui->lineEditPlot2SourceFile->text().isEmpty()==false) {
            ui->pushButtonPlot->setEnabled(false);
        } else {
           if ( this->fileExists( ui->lineEditPlot1SourceFile->text() ) == true ||
                this->fileExists( ui->lineEditPlot3SourceFile->text() ) == true ||
                this->fileExists( ui->lineEditPlot4SourceFile->text() ) == true  ) {
               ui->pushButtonPlot->setEnabled(true);
           }
        }
    }
}

// Function to set the correct value of the combo box X column from line edit
void gLAB_GUI::on_lineEditPlot2Xcolumn_textChanged() {
    int index;
    if (ui->lineEditPlot2Xcolumn->text().contains(QRegularExpression("[^0-9]"))==true) {
        index=-1;
    } else {
        index = ui->lineEditPlot2Xcolumn->text().toInt();
    }
    ui->comboBoxPlot2Xcolumn->setCurrentIndex(index);
}
// Function to change the message items
void gLAB_GUI::change_comboBoxPlot2Xcolumn_message(int messageType){
    // clean all the items
    for (int i=ui->comboBoxPlot2Xcolumn->count()-1; i>=0; i--) ui->comboBoxPlot2Xcolumn->removeItem(i);
    // add new items
    for (int i=0; i<AllMessages[messageType].size(); i++) ui->comboBoxPlot2Xcolumn->addItem(AllMessages[messageType][i]);
}
// Functions to set the correct number in the X column line edit
void gLAB_GUI::on_comboBoxPlot2Xcolumn_currentIndexChanged(int index){
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}

// Function to set the correct value of the combo box Y column from line edit
void gLAB_GUI::on_lineEditPlot2Ycolumn_textChanged() {
    int index;
    if (ui->lineEditPlot2Ycolumn->text().contains(QRegularExpression("[^0-9]"))==true) {
        index=-1;
    } else {
        index = ui->lineEditPlot2Ycolumn->text().toInt();
    }
    ui->comboBoxPlot2Ycolumn->setCurrentIndex(index);
}
// Function to change the message items
void gLAB_GUI::change_comboBoxPlot2Ycolumn_message(int messageType){
    // clean all the items
    for (int i=ui->comboBoxPlot2Ycolumn->count()-1; i>=0; i--) ui->comboBoxPlot2Ycolumn->removeItem(i);
    // add new items
    for (int i=0; i<AllMessages[messageType].size(); i++) ui->comboBoxPlot2Ycolumn->addItem(AllMessages[messageType][i]);
}
// Functions to set the correct number in the X column line edit
void gLAB_GUI::on_comboBoxPlot2Ycolumn_currentIndexChanged(int index){
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}


////////////////// Plot Nr 3 //////////////////
///////////////////////////////////////////////
// Function to set the correct stacked window in the condition of the Plot Nr 3
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot3Condition_currentIndexChanged(int index) {
    ui->comboBoxPlot3Condition->setCurrentIndex(index);
    this->change_comboBoxPlot3Xcolumn_message(index);
    this->change_comboBoxPlot3Ycolumn_message(index);
    this->on_comboBoxPlot3ConditionGNSS_currentIndexChanged(0);
    ui->lineEditPlot3Xcolumn->setText("1"); // To make the change to "empty" effective
    ui->lineEditPlot3Ycolumn->setText("1"); // To make the change to "empty" effective
    ui->lineEditPlot3Xcolumn->setText("");
    ui->lineEditPlot3Ycolumn->setText("");
    /*if ( index == 0 ) {
        ui->lineEditPlot3Xcolumn->setHidden(true);
        ui->lineEditPlot3Ycolumn->setHidden(true);
    } else {
        ui->lineEditPlot3Xcolumn->setHidden(false);
        ui->lineEditPlot3Ycolumn->setHidden(false);
    }*/
    switch ( index ) {
        case 0 : { // Nothing
            ui->stackedWidgetPlot3Condition->setCurrentIndex(0);
            ui->lineEditPlot3Condition->setText("");
            break;
        }
        case 1 : { // USERADDEDERROR
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"USERADDEDERROR\")");
            break;
        }
        case 2 : { // Input
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"INPUT\")");
            break;
        }
        case 3 : { // Cycle slips
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"CS\")");
            break;
        }
        case 4 : { // SF Cycle slips
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"SFCSDATA\")");
            break;
        }
        case 5 : { // MW Cycle slips
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"MWCSDATA\")");
            break;
        }
        case 6 : { // LI Cycle slips
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"LICSDATA\")");
            break;
        }
        case 7 : { // IGF Cycle slips
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"IGFCSDATA\")");
            break;
        }
        case 8 : { // Meas
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"MEAS\")");
            break;
        }
        case 9 : { // Model
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"MODEL\")");
            break;
        }
        case 10 : { // Satsel
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"SATSEL\")");
            break;
        }
        case 11 : { // Prefit
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"PREFIT\")");
            break;
        }
        case 12: { // Epochsat
            ui->stackedWidgetPlot3Condition->setCurrentIndex(0);
            ui->lineEditPlot3Condition->setText("($1==\"EPOCHSAT\")");
            break;
        }
        case 13 : { // Postfit
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"POSTFIT\")");
            break;
        }
        case 14 : { // Filter
            ui->stackedWidgetPlot3Condition->setCurrentIndex(0);
            ui->lineEditPlot3Condition->setText("($1==\"FILTER\")");
            break;
        }
        case 15 : { // Output
            ui->stackedWidgetPlot3Condition->setCurrentIndex(2);
            ui->lineEditPlot3Condition->setText("($1==\"OUTPUT\")");
            break;
        }
        case 16 : { // SBASCORR
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"SBASCORR\")");
            break;
        }
        case 17 : { // SBASVAR
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"SBASVAR\")");
            break;
        }
        case 18 : { // SBASIONO
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"SBASIONO\")");
            break;
        }
        case 19 : { // SBASUNSEL
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"SBASUNSEL\")");
            break;
        }
        case 20 : { // SBASDFMCCORR
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"SBASDFMCCORR\")");
            break;
        }
        case 21 : { // SBASDFMCVAR
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"SBASDFMCVAR\")");
            break;
        }
        case 22 : { // SBASDFMCUNSEL
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"SBASDFMCUNSEL\")");
            break;
        }
        case 23 : { // SBASOUT
            ui->stackedWidgetPlot3Condition->setCurrentIndex(2);
            ui->lineEditPlot3Condition->setText("($1==\"SBASOUT\")");
            break;
        }
        case 24 : { // DGNSS
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"DGNSS\")");
            break;
        }
        case 25 : { // Satstat
            ui->stackedWidgetPlot3Condition->setCurrentIndex(0);
            ui->lineEditPlot3Condition->setText("($1==\"SATSTAT\")");
            break;
        }
        case 26 : { // Satstattot
            ui->stackedWidgetPlot3Condition->setCurrentIndex(0);
            ui->lineEditPlot3Condition->setText("($1==\"SATSTATTOT\")");
            break;
        }
        case 27 : { // Satdiff
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"SATDIFF\")");
            break;
        }
        case 28 : { // Satpvt
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"SATPVT\")");
            break;
        }
    }
}

// Function to set the correct stacked window in the condition of the Plot Nr 1
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot3ConditionGNSS_currentIndexChanged(int index){
    ui->comboBoxPlot3ConditionGNSS->setCurrentIndex(index);
    if (index==0){
        ui->stackedWidgetPlot3ConditionGNSS->setCurrentIndex(0);
        this->on_comboBoxPlot3ConditionGPS_currentIndexChanged(0);
        ui->stackedWidgetPlot3ConditionGNSS->setEnabled(false);
        // Delete previous second condition (from ampersand to the end)
        QString text = ui->lineEditPlot3Condition->text();
        int end = text.indexOf("&", 0, Qt::CaseInsensitive);
        if ( end != -1 ) text = text.mid(0, end-1);
        ui->lineEditPlot3Condition->setText(text);
    } else if ( index>0 && index<=MAX_GNSS ) {
        ui->stackedWidgetPlot3ConditionGNSS->setEnabled(true);
        ui->stackedWidgetPlot3ConditionGNSS->setCurrentIndex(index-1);
        if (index==1) this->on_comboBoxPlot3ConditionGPS_currentIndexChanged(0);
        else if (index==2) this->on_comboBoxPlot3ConditionGalileo_currentIndexChanged(0);
        else if (index==3) this->on_comboBoxPlot3ConditionGLONASS_currentIndexChanged(0);
        else if (index==4) this->on_comboBoxPlot3ConditionBDS_currentIndexChanged(0);
        else if (index==5) this->on_comboBoxPlot3ConditionGEO_currentIndexChanged(0);
        else if (index==6) this->on_comboBoxPlot3ConditionQZSS_currentIndexChanged(0);
        else if (index==7) this->on_comboBoxPlot3ConditionIRNSS_currentIndexChanged(0);
    }
}
void gLAB_GUI::on_comboBoxPlot3ConditionGPS_currentIndexChanged(int index) {
    ui->comboBoxPlot3ConditionGPS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot3Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot3Condition->currentIndex()!=19) text = (text + " & ($6==\"GPS\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"GPS\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot3Condition->currentIndex()!=19) text = (text + " & ($6==\"GPS\")");
        else text = (text + " & (&8==\"GPS\")");
    }
    ui->lineEditPlot3Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot3ConditionGalileo_currentIndexChanged(int index){
    ui->comboBoxPlot3ConditionGalileo->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot3Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot3Condition->currentIndex()!=1) text = (text + " & ($6==\"GAL\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"GAL\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot3Condition->currentIndex()!=1) text = (text + " & ($6==\"GAL\")");
        else text = (text + " & (&8==\"GAL\")");
    }
    ui->lineEditPlot3Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot3ConditionGLONASS_currentIndexChanged(int index){
    ui->comboBoxPlot3ConditionGLONASS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot3Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot3Condition->currentIndex()!=1) text = (text + " & ($6==\"GLO\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"GLO\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot3Condition->currentIndex()!=1) text = (text + " & ($6==\"GLO\")");
        else text = (text + " & (&8==\"GLO\")");
    }
    ui->lineEditPlot3Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot3ConditionGEO_currentIndexChanged(int index){
    ui->comboBoxPlot3ConditionGEO->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot3Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot3Condition->currentIndex()!=1) text = (text + " & ($6==\"GEO\") & ($7==%1)").arg(index+119);
        else text = (text + " & (&8==\"GEO\") & ($9==%1)").arg(index+119);
    } else {
        if (ui->comboBoxPlot3Condition->currentIndex()!=1) text = (text + " & ($6==\"GEO\")");
        else text = (text + " & (&8==\"GEO\")");
    }
    ui->lineEditPlot3Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot3ConditionBDS_currentIndexChanged(int index){
    ui->comboBoxPlot3ConditionBDS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot3Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot3Condition->currentIndex()!=1) text = (text + " & ($6==\"BDS\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"BDS\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot3Condition->currentIndex()!=1) text = (text + " & ($6==\"BDS\")");
        else text = (text + " & (&8==\"BDS\")");
    }
    ui->lineEditPlot3Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot3ConditionQZSS_currentIndexChanged(int index){
    ui->comboBoxPlot3ConditionQZSS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot3Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot3Condition->currentIndex()!=1) text = (text + " & ($6==\"QZS\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"QZS\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot3Condition->currentIndex()!=1) text = (text + " & ($6==\"QZS\")");
        else text = (text + " & (&8==\"QZS\")");
    }
    ui->lineEditPlot3Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot3ConditionIRNSS_currentIndexChanged(int index){
    ui->comboBoxPlot3ConditionIRNSS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot3Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot3Condition->currentIndex()!=1) text = (text + " & ($6==\"IRN\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"IRN\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot3Condition->currentIndex()!=1) text = (text + " & ($6==\"IRN\")");
        else text = (text + " & (&8==\"IRN\")");
    }
    ui->lineEditPlot3Condition->setText(text);
}

// Function to set the correct stacked window in the condition of the Plot Nr 1
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot3ConditionOutput_currentIndexChanged(int index) {
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot3Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        text = (text + " & ($6==%1)").arg(index-1);
    }
    ui->lineEditPlot3Condition->setText(text);
}

// Open dialog to set the plot source filename and path
void gLAB_GUI::on_pushButtonPlot3SourceFile_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("gLAB Output Files (*.out *.txt);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPlot3SourceFile->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
    if ( this->fileExists( ui->lineEditPlot3SourceFile->text() ) == true ) ui->pushButtonPlot->setEnabled(true);
    else ui->pushButtonPlot->setEnabled(false);
}

//This is to enable Plot button when the user manually sets a text file name
void gLAB_GUI::on_lineEditPlot3SourceFile_textChanged() {
    if ( this->fileExists( ui->lineEditPlot3SourceFile->text() ) == true ) {
        ui->pushButtonPlot->setEnabled(true);
    } else {
        if ( ui->lineEditPlot3SourceFile->text().isEmpty()==false) {
            ui->pushButtonPlot->setEnabled(false);
        } else {
           if ( this->fileExists( ui->lineEditPlot1SourceFile->text() ) == true ||
                this->fileExists( ui->lineEditPlot2SourceFile->text() ) == true ||
                this->fileExists( ui->lineEditPlot4SourceFile->text() ) == true  ) {
               ui->pushButtonPlot->setEnabled(true);
           }
        }
    }
}

// Function to set the correct value of the combo box X column from line edit
void gLAB_GUI::on_lineEditPlot3Xcolumn_textChanged() {
    int index;
    if (ui->lineEditPlot3Xcolumn->text().contains(QRegularExpression("[^0-9]"))==true) {
        index=-1;
    } else {
        index = ui->lineEditPlot3Xcolumn->text().toInt();
    }
    ui->comboBoxPlot3Xcolumn->setCurrentIndex(index);
}
// Function to change the message items
void gLAB_GUI::change_comboBoxPlot3Xcolumn_message(int messageType){
    // clean all the items
    for (int i=ui->comboBoxPlot3Xcolumn->count()-1; i>=0; i--) ui->comboBoxPlot3Xcolumn->removeItem(i);
    // add new items
    for (int i=0; i<AllMessages[messageType].size(); i++) ui->comboBoxPlot3Xcolumn->addItem(AllMessages[messageType][i]);
}
// Functions to set the correct number in the X column line edit
void gLAB_GUI::on_comboBoxPlot3Xcolumn_currentIndexChanged(int index){
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}

// Function to set the correct value of the combo box Y column from line edit
void gLAB_GUI::on_lineEditPlot3Ycolumn_textChanged() {
    int index;
    if (ui->lineEditPlot3Ycolumn->text().contains(QRegularExpression("[^0-9]"))==true) {
        index=-1;
    } else {
        index = ui->lineEditPlot3Ycolumn->text().toInt();
    }
    ui->comboBoxPlot3Ycolumn->setCurrentIndex(index);
}
// Function to change the message items
void gLAB_GUI::change_comboBoxPlot3Ycolumn_message(int messageType){
    // clean all the items
    for (int i=ui->comboBoxPlot3Ycolumn->count()-1; i>=0; i--) ui->comboBoxPlot3Ycolumn->removeItem(i);
    // add new items
    for (int i=0; i<AllMessages[messageType].size(); i++) ui->comboBoxPlot3Ycolumn->addItem(AllMessages[messageType][i]);
}
// Functions to set the correct number in the X column line edit
void gLAB_GUI::on_comboBoxPlot3Ycolumn_currentIndexChanged(int index){
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}


////////////////// Plot Nr 4 //////////////////
///////////////////////////////////////////////
// Function to set the correct stacked window in the condition of the Plot Nr 4
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot4Condition_currentIndexChanged(int index) {
    ui->comboBoxPlot4Condition->setCurrentIndex(index);
    this->change_comboBoxPlot4Xcolumn_message(index);
    this->change_comboBoxPlot4Ycolumn_message(index);
    this->on_comboBoxPlot4ConditionGNSS_currentIndexChanged(0);
    ui->lineEditPlot4Xcolumn->setText("1"); // To make the change to "empty" effective
    ui->lineEditPlot4Ycolumn->setText("1"); // To make the change to "empty" effective
    ui->lineEditPlot4Xcolumn->setText("");
    ui->lineEditPlot4Ycolumn->setText("");
    /*if ( index == 0 ) {
        ui->lineEditPlot4Xcolumn->setHidden(true);
        ui->lineEditPlot4Ycolumn->setHidden(true);
    } else {
        ui->lineEditPlot4Xcolumn->setHidden(false);
        ui->lineEditPlot4Ycolumn->setHidden(false);
    }*/
    switch ( index ) {
        case 0 : { // Nothing
            ui->stackedWidgetPlot4Condition->setCurrentIndex(0);
            ui->lineEditPlot4Condition->setText("");
            break;
        }
        case 1 : { // USERADDEDERROR
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"USERADDEDERROR\")");
            break;
        }
        case 2 : { // Input
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"INPUT\")");
            break;
        }
        case 3 : { // Cycle slips
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"CS\")");
            break;
        }
        case 4 : { // SF Cycle slips
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"SFCSDATA\")");
            break;
        }
        case 5 : { // MW Cycle slips
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"MWCSDATA\")");
            break;
        }
        case 6 : { // LI Cycle slips
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"LICSDATA\")");
            break;
        }
        case 7 : { // IGF Cycle slips
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"IGFCSDATA\")");
            break;
        }
        case 8 : { // Meas
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"MEAS\")");
            break;
        }
        case 9 : { // Model
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"MODEL\")");
            break;
        }
        case 10 : { // Satsel
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"SATSEL\")");
            break;
        }
        case 11 : { // Prefit
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"PREFIT\")");
            break;
        }
        case 12: { // Epochsat
            ui->stackedWidgetPlot4Condition->setCurrentIndex(0);
            ui->lineEditPlot4Condition->setText("($1==\"EPOCHSAT\")");
            break;
        }
        case 13 : { // Postfit
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"POSTFIT\")");
            break;
        }
        case 14 : { // Filter
            ui->stackedWidgetPlot4Condition->setCurrentIndex(0);
            ui->lineEditPlot4Condition->setText("($1==\"FILTER\")");
            break;
        }
        case 15 : { // Output
            ui->stackedWidgetPlot4Condition->setCurrentIndex(2);
            ui->lineEditPlot4Condition->setText("($1==\"OUTPUT\")");
            break;
        }
        case 16 : { // SBASCORR
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"SBASCORR\")");
            break;
        }
        case 17 : { // SBASVAR
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"SBASVAR\")");
            break;
        }
        case 18 : { // SBASIONO
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"SBASIONO\")");
            break;
        }
        case 19 : { // SBASUNSEL
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"SBASUNSEL\")");
            break;
        }
        case 20 : { // SBASDFMCCORR
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"SBASDFMCCORR\")");
            break;
        }
        case 21 : { // SBASDFMCVAR
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"SBASDFMCVAR\")");
            break;
        }
        case 22 : { // SBASDFMCUNSEL
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"SBASDFMCUNSEL\")");
            break;
        }
        case 23 : { // SBASOUT
            ui->stackedWidgetPlot4Condition->setCurrentIndex(2);
            ui->lineEditPlot4Condition->setText("($1==\"SBASOUT\")");
            break;
        }
        case 24 : { // DGNSS
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"DGNSS\")");
            break;
        }
        case 25 : { // Satstat
            ui->stackedWidgetPlot4Condition->setCurrentIndex(0);
            ui->lineEditPlot4Condition->setText("($1==\"SATSTAT\")");
            break;
        }
        case 26 : { // Satstattot
            ui->stackedWidgetPlot4Condition->setCurrentIndex(0);
            ui->lineEditPlot4Condition->setText("($1==\"SATSTATTOT\")");
            break;
        }
        case 27 : { // Satdiff
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"SATDIFF\")");
            break;
        }
        case 28 : { // Satpvt
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"SATPVT\")");
            break;
        }
    }
}

// Function to set the correct stacked window in the condition of the Plot Nr 1
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot4ConditionGNSS_currentIndexChanged(int index){
    ui->comboBoxPlot4ConditionGNSS->setCurrentIndex(index);
    if (index==0){
        ui->stackedWidgetPlot4ConditionGNSS->setCurrentIndex(0);
        this->on_comboBoxPlot4ConditionGPS_currentIndexChanged(0);
        ui->stackedWidgetPlot4ConditionGNSS->setEnabled(false);
        // Delete previous second condition (from ampersand to the end)
        QString text = ui->lineEditPlot4Condition->text();
        int end = text.indexOf("&", 0, Qt::CaseInsensitive);
        if ( end != -1 ) text = text.mid(0, end-1);
        ui->lineEditPlot4Condition->setText(text);
    } else if ( index>0 && index<=MAX_GNSS ) {
        ui->stackedWidgetPlot4ConditionGNSS->setEnabled(true);
        ui->stackedWidgetPlot4ConditionGNSS->setCurrentIndex(index-1);
        if (index==1) this->on_comboBoxPlot4ConditionGPS_currentIndexChanged(0);
        else if (index==2) this->on_comboBoxPlot4ConditionGalileo_currentIndexChanged(0);
        else if (index==3) this->on_comboBoxPlot4ConditionGLONASS_currentIndexChanged(0);
        else if (index==4) this->on_comboBoxPlot4ConditionBDS_currentIndexChanged(0);
        else if (index==5) this->on_comboBoxPlot4ConditionGEO_currentIndexChanged(0);
        else if (index==6) this->on_comboBoxPlot4ConditionQZSS_currentIndexChanged(0);
        else if (index==7) this->on_comboBoxPlot4ConditionIRNSS_currentIndexChanged(0);
    }
}
void gLAB_GUI::on_comboBoxPlot4ConditionGPS_currentIndexChanged(int index) {
    ui->comboBoxPlot4ConditionGPS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot4Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot4Condition->currentIndex()!=19) text = (text + " & ($6==\"GPS\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"GPS\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot4Condition->currentIndex()!=19) text = (text + " & ($6==\"GPS\")");
        else text = (text + " & (&8==\"GPS\")");
    }
    ui->lineEditPlot4Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot4ConditionGalileo_currentIndexChanged(int index){
    ui->comboBoxPlot4ConditionGalileo->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot4Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot4Condition->currentIndex()!=1) text = (text + " & ($6==\"GAL\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"GAL\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot4Condition->currentIndex()!=1) text = (text + " & ($6==\"GAL\")");
        else text = (text + " & (&8==\"GAL\")");
    }
    ui->lineEditPlot4Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot4ConditionGLONASS_currentIndexChanged(int index){
    ui->comboBoxPlot4ConditionGLONASS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot4Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot4Condition->currentIndex()!=1) text = (text + " & ($6==\"GLO\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"GLO\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot4Condition->currentIndex()!=1) text = (text + " & ($6==\"GLO\")");
        else text = (text + " & (&8==\"GLO\")");
    }
    ui->lineEditPlot4Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot4ConditionGEO_currentIndexChanged(int index){
    ui->comboBoxPlot4ConditionGEO->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot4Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot4Condition->currentIndex()!=1) text = (text + " & ($6==\"GEO\") & ($7==%1)").arg(index+119);
        else text = (text + " & (&8==\"GEO\") & ($9==%1)").arg(index+119);
    } else {
        if (ui->comboBoxPlot4Condition->currentIndex()!=1) text = (text + " & ($6==\"GEO\")");
        else text = (text + " & (&8==\"GEO\")");
    }
    ui->lineEditPlot4Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot4ConditionBDS_currentIndexChanged(int index){
    ui->comboBoxPlot4ConditionBDS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot4Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot4Condition->currentIndex()!=1) text = (text + " & ($6==\"BDS\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"BDS\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot4Condition->currentIndex()!=1) text = (text + " & ($6==\"BDS\")");
        else text = (text + " & (&8==\"BDS\")");
    }
    ui->lineEditPlot4Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot4ConditionQZSS_currentIndexChanged(int index){
    ui->comboBoxPlot4ConditionQZSS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot4Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot4Condition->currentIndex()!=1) text = (text + " & ($6==\"QZS\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"QZS\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot4Condition->currentIndex()!=1) text = (text + " & ($6==\"QZS\")");
        else text = (text + " & (&8==\"QZS\")");
    }
    ui->lineEditPlot4Condition->setText(text);
}
void gLAB_GUI::on_comboBoxPlot4ConditionIRNSS_currentIndexChanged(int index){
    ui->comboBoxPlot4ConditionIRNSS->setCurrentIndex(index);
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot4Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        if (ui->comboBoxPlot4Condition->currentIndex()!=1) text = (text + " & ($6==\"IRN\") & ($7==%1)").arg(index);
        else text = (text + " & (&8==\"IRN\") & ($9==%1)").arg(index);
    } else {
        if (ui->comboBoxPlot4Condition->currentIndex()!=1) text = (text + " & ($6==\"IRN\")");
        else text = (text + " & (&8==\"IRN\")");
    }
    ui->lineEditPlot4Condition->setText(text);
}

// Function to set the correct stacked window in the condition of the Plot Nr 1
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot4ConditionOutput_currentIndexChanged(int index) {
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot4Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        text = (text + " & ($6==%1)").arg(index-1);
    }
    ui->lineEditPlot4Condition->setText(text);
}

// Open dialog to set the plot source filename and path
void gLAB_GUI::on_pushButtonPlot4SourceFile_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("gLAB Output Files (*.out *.txt);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPlot4SourceFile->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
    if ( this->fileExists( ui->lineEditPlot4SourceFile->text() ) == true ) ui->pushButtonPlot->setEnabled(true);
    else ui->pushButtonPlot->setEnabled(false);
}

//This is to enable Plot button when the user manually sets a text file name
void gLAB_GUI::on_lineEditPlot4SourceFile_textChanged() {
    if ( this->fileExists( ui->lineEditPlot4SourceFile->text() ) == true ) {
        ui->pushButtonPlot->setEnabled(true);
    } else {
        if ( ui->lineEditPlot4SourceFile->text().isEmpty()==false) {
            ui->pushButtonPlot->setEnabled(false);
        } else {
           if ( this->fileExists( ui->lineEditPlot1SourceFile->text() ) == true ||
                this->fileExists( ui->lineEditPlot2SourceFile->text() ) == true ||
                this->fileExists( ui->lineEditPlot3SourceFile->text() ) == true  ) {
               ui->pushButtonPlot->setEnabled(true);
           }
        }
    }
}

// Function to set the correct value of the combo box X column from line edit
void gLAB_GUI::on_lineEditPlot4Xcolumn_textChanged() {
    int index;
    if (ui->lineEditPlot4Xcolumn->text().contains(QRegularExpression("[^0-9]"))==true) {
        index=-1;
    } else {
        index = ui->lineEditPlot4Xcolumn->text().toInt();
    }
    ui->comboBoxPlot4Xcolumn->setCurrentIndex(index);
}
// Function to change the message items
void gLAB_GUI::change_comboBoxPlot4Xcolumn_message(int messageType){
    // clean all the items
    for (int i=ui->comboBoxPlot4Xcolumn->count()-1; i>=0; i--) ui->comboBoxPlot4Xcolumn->removeItem(i);
    // add new items
    for (int i=0; i<AllMessages[messageType].size(); i++) ui->comboBoxPlot4Xcolumn->addItem(AllMessages[messageType][i]);
}
// Functions to set the correct number in the X column line edit
void gLAB_GUI::on_comboBoxPlot4Xcolumn_currentIndexChanged(int index){
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}

// Function to set the correct value of the combo box Y column from line edit
void gLAB_GUI::on_lineEditPlot4Ycolumn_textChanged() {
    int index;
    if (ui->lineEditPlot4Ycolumn->text().contains(QRegularExpression("[^0-9]"))==true) {
        index=-1;
    } else {
        index = ui->lineEditPlot4Ycolumn->text().toInt();
    }
    ui->comboBoxPlot4Ycolumn->setCurrentIndex(index);
}
// Function to change the message items
void gLAB_GUI::change_comboBoxPlot4Ycolumn_message(int messageType){
    // clean all the items
    for (int i=ui->comboBoxPlot4Ycolumn->count()-1; i>=0; i--) ui->comboBoxPlot4Ycolumn->removeItem(i);
    // add new items
    for (int i=0; i<AllMessages[messageType].size(); i++) ui->comboBoxPlot4Ycolumn->addItem(AllMessages[messageType][i]);
}
// Functions to set the correct number in the X column line edit
void gLAB_GUI::on_comboBoxPlot4Ycolumn_currentIndexChanged(int index){
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}

// Template for NEU Positioning Error
void gLAB_GUI::on_pushButtonTemplateNeuPositioningError_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("NEU Positioning Error");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Error (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(15);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("24");
    ui->lineEditPlot1LegendLabel->setText("North error");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot2Condition->setCurrentIndex(15);
    ui->lineEditPlot2Xcolumn->setText("4");
    ui->lineEditPlot2Ycolumn->setText("25");
    ui->lineEditPlot2LegendLabel->setText("East error");
    // Plot Nr. 3
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot3SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot3SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot3TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot3Condition->setCurrentIndex(15);
    ui->lineEditPlot3Xcolumn->setText("4");
    ui->lineEditPlot3Ycolumn->setText("26");
    ui->lineEditPlot3LegendLabel->setText("Up error");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Horizontal Positioning Error
void gLAB_GUI::on_pushButtonTemplateHorizontalError_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Horizontal Positioning Error");
    ui->lineEditPlotXLabel->setText("East error (m)");
    ui->lineEditPlotYLabel->setText("North error (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(15);
    ui->lineEditPlot1Xcolumn->setText("25");
    ui->lineEditPlot1Ycolumn->setText("24");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Zenith Tropospheric Delay
void gLAB_GUI::on_pushButtonTemplateZenithTroposphericDelay_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Zenith Tropospheric Delay");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Troposphere (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(14);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("20");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Ionospheric Combinations
void gLAB_GUI::on_pushButtonTemplateIonosphericCombinations_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Ionospheric Combinations");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Metres of L1-L2 delay (m)");
    this->on_checkBoxAutoLimits_clicked(false);
    ui->lineEditPlotYmin->setText("-10");
    ui->lineEditPlotYmax->setText("10");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(3);
    ui->comboBoxPlot1Condition->setCurrentIndex(2);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("($12-$11)");
    ui->lineEditPlot1LegendLabel->setText("All PRN : PI=(P2-P1)");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(3);
    ui->comboBoxPlot2ColorLine->setCurrentIndex(2);
    ui->comboBoxPlot2Condition->setCurrentIndex(2);
    this->on_comboBoxPlot2ConditionGNSS_currentIndexChanged(1);
    ui->comboBoxPlot2ConditionGPS->setCurrentIndex(13);
    ui->lineEditPlot2Xcolumn->setText("4");
    ui->lineEditPlot2Ycolumn->setText("($12-$11)");
    ui->lineEditPlot2LegendLabel->setText("PRN 13 : PI=(P2-P1)");
    // Plot Nr. 3
    ui->comboBoxPlot3ColorLine->setCurrentIndex(1);
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Dilution Of Precision
void gLAB_GUI::on_pushButtonTemplateDOP_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Dilution Of Precision");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("DOP (adimensional)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(15);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("36");
    ui->lineEditPlot1LegendLabel->setText("Geometric DOP");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot2Condition->setCurrentIndex(15);
    ui->lineEditPlot2Xcolumn->setText("4");
    ui->lineEditPlot2Ycolumn->setText("39");
    ui->lineEditPlot2LegendLabel->setText("Horizontal DOP");
    // Plot Nr. 3
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot3SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot3SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot3TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot3Condition->setCurrentIndex(15);
    ui->lineEditPlot3Xcolumn->setText("4");
    ui->lineEditPlot3Ycolumn->setText("40");
    ui->lineEditPlot3LegendLabel->setText("Vertical DOP");
    // Plot Nr. 4
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot4SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot4SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot4TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot4Condition->setCurrentIndex(15);
    ui->lineEditPlot4Xcolumn->setText("4");
    ui->lineEditPlot4Ycolumn->setText("38");
    ui->lineEditPlot4LegendLabel->setText("Time DOP");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Satellite Skyplot
void gLAB_GUI::on_pushButtonTemplateSatelliteSkyplot_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Satellite Skyplot");
    this->on_checkBoxAutoLimits_clicked(false);
    ui->lineEditPlotXmin->setText("-1");
    ui->lineEditPlotXmax->setText("1");
    ui->lineEditPlotYmin->setText("-1");
    ui->lineEditPlotYmax->setText("1");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(3);
    ui->comboBoxPlot1Condition->setCurrentIndex(11);
    ui->lineEditPlot1Xcolumn->setText("(math.sin($13*math.pi/180)*(90-$12)/90)");
    ui->lineEditPlot1Ycolumn->setText("(math.cos($13*math.pi/180)*(90-$12)/90)");
    ui->lineEditPlot1LegendLabel->setText("All PRN");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(3);
    ui->comboBoxPlot2ColorLine->setCurrentIndex(2);
    ui->comboBoxPlot2Condition->setCurrentIndex(11);
    this->on_comboBoxPlot2ConditionGNSS_currentIndexChanged(1);
    ui->comboBoxPlot2ConditionGPS->setCurrentIndex(3);
    ui->lineEditPlot2Xcolumn->setText("(math.sin($13*math.pi/180)*(90-$12)/90)");
    ui->lineEditPlot2Ycolumn->setText("(math.cos($13*math.pi/180)*(90-$12)/90)");
    ui->lineEditPlot2LegendLabel->setText("PRN 3");
    // Plot Nr. 3
    ui->comboBoxPlot3ColorLine->setCurrentIndex(1);
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Carrier Phase Ambiguities Estimations
void gLAB_GUI::on_pushButtonTemplateCarrierPhaseAmbiguities_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Carrier Phase Ambiguities Estimations");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Ambiguities (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(13);
    ui->lineEditPlot1Condition->setText("($1==\"POSTFIT\") & ($14[0]==\"L\")");
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("21");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Measurement Multipath - Noise
void gLAB_GUI::on_pushButtonTemplateMeasurementMultipath_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Measurement Multipath - Noise");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Multipath");
    this->on_checkBoxAutoLimits_clicked(false);
    ui->lineEditPlotYmin->setText("-200");
    ui->lineEditPlotYmax->setText("200");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(2);
    this->on_comboBoxPlot1ConditionGNSS_currentIndexChanged(1);
    ui->comboBoxPlot1ConditionGPS->setCurrentIndex(31);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("($10-$13-3.09*($13-$14))");
    ui->lineEditPlot1LegendLabel->setText("C1 Multipath");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot2Condition->setCurrentIndex(2);
    this->on_comboBoxPlot2ConditionGNSS_currentIndexChanged(1);
    ui->comboBoxPlot2ConditionGPS->setCurrentIndex(31);
    ui->lineEditPlot2Xcolumn->setText("4");
    ui->lineEditPlot2Ycolumn->setText("( ( 154*154 ) * $11  - ( 120*120 )*$12 ) / ( ( 154*154 ) - ( 120*120 ) ) - ( ( 154*154 ) * $13 - ( 120*120 )*$14 ) / ( ( 154*154 ) - ( 120*120 ) )");
    ui->lineEditPlot2LegendLabel->setText("PC Multipath");
    // Plot Nr. 3
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot3SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot3SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot3TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot3Condition->setCurrentIndex(2);
    this->on_comboBoxPlot3ConditionGNSS_currentIndexChanged(1);
    ui->comboBoxPlot3ConditionGPS->setCurrentIndex(31);
    ui->lineEditPlot3Xcolumn->setText("4");
    ui->lineEditPlot3Ycolumn->setText("( 154 * $11 + 120 * $12 ) / ( 154 + 120 ) - ( 154 * $13  - 120 * $14 ) / ( 154 - 120 )");
    ui->lineEditPlot3LegendLabel->setText("MW Multipath");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Model Components
void gLAB_GUI::on_pushButtonTemplateModelComponents_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Model Components");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Model (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(9);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("34");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Measurement Prefits vs Elevation
void gLAB_GUI::on_pushButtonTemplatePrefitResiduals_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Measurement Prefits vs Elevation");
    ui->lineEditPlotXLabel->setText("Elevation (degrees)");
    ui->lineEditPlotYLabel->setText("Prefits (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(11);
    ui->lineEditPlot1Condition->setText("($1==\"PREFIT\") & ($14[0]==\"C\")");
    ui->lineEditPlot1Xcolumn->setText("12");
    ui->lineEditPlot1Ycolumn->setText("16");
    ui->lineEditPlot1LegendLabel->setText("Pseudorange Prefit Residuals");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot2Condition->setCurrentIndex(11);
    ui->lineEditPlot2Condition->setText("($1==\"PREFIT\") & ($14[0]==\"L\")");
    ui->lineEditPlot2Xcolumn->setText("12");
    ui->lineEditPlot2Ycolumn->setText("16");
    ui->lineEditPlot2LegendLabel->setText("Carrier Phase Prefit Residuals");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Measurement Postfits vs Elevation
void gLAB_GUI::on_pushButtonTemplatePostfitResiduals_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Measurement Prefits vs Elevation");
    ui->lineEditPlotXLabel->setText("Elevation (degrees)");
    ui->lineEditPlotYLabel->setText("Postfits (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(13);
    ui->lineEditPlot1Condition->setText("($1==\"POSTFIT\") & ($14[0]==\"C\")");
    ui->lineEditPlot1Xcolumn->setText("12");
    ui->lineEditPlot1Ycolumn->setText("16");
    ui->lineEditPlot1LegendLabel->setText("Pseudorange Postfit Residuals");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot2Condition->setCurrentIndex(13);
    ui->lineEditPlot2Condition->setText("($1==\"POSTFIT\") & ($14[0]==\"L\")");
    ui->lineEditPlot2Xcolumn->setText("12");
    ui->lineEditPlot2Ycolumn->setText("16");
    ui->lineEditPlot2LegendLabel->setText("Carrier Phase Postfit Residuals");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Orbits and Clock Comparison
void gLAB_GUI::on_pushButtonTemplateOrbitAndClockComparison_clicked() {
    QFileInfo OutputFile(ui->lineEditOutputDestination->text());
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Orbits and Clock Comparison");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Discrepancy (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputFileCompare->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators((OutputFile.filePath() + "/diff.out")));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputFileCompare->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(27);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("13");
    ui->lineEditPlot1LegendLabel->setText("Radial");
    // Plot Nr. 2
    if ( ui->lineEditOutputFileCompare->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators((OutputFile.filePath() + "/diff.out")));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputFileCompare->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot2Condition->setCurrentIndex(27);
    ui->lineEditPlot2Xcolumn->setText("4");
    ui->lineEditPlot2Ycolumn->setText("14");
    ui->lineEditPlot2LegendLabel->setText("Along-Track");
    // Plot Nr. 3
    if ( ui->lineEditOutputFileCompare->text() == "" ) ui->lineEditPlot3SourceFile->setText(QDir::toNativeSeparators((OutputFile.filePath() + "/diff.out")));
    else ui->lineEditPlot3SourceFile->setText(ui->lineEditOutputFileCompare->text());
    ui->comboBoxPlot3TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot3Condition->setCurrentIndex(27);
    ui->lineEditPlot3Xcolumn->setText("4");
    ui->lineEditPlot3Ycolumn->setText("15");
    ui->lineEditPlot3LegendLabel->setText("Cross-Track");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for DGNSS - Pseudorange Corrections
void gLAB_GUI::on_pushButtonTemplateDifferentialCorrections_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("DGNSS - Pseudorange Corrections");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("PRC (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(24);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("8");
    ui->lineEditPlot1LegendLabel->setText("All PRN");
    // Plot Nr. 2
    ui->comboBoxPlot2ColorLine->setCurrentIndex(1);    // Plot Nr. 3
    ui->comboBoxPlot3ColorLine->setCurrentIndex(1);
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for DGNSS - Sigma of the PRC
void gLAB_GUI::on_pushButtonTemplateSigmaPRC_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("DGNSS - Sigma of the PRC");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Sigma of PRC (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(24);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("14");
    ui->lineEditPlot1LegendLabel->setText("All PRN");
    // Plot Nr. 2
    ui->comboBoxPlot2ColorLine->setCurrentIndex(2);
    // Plot Nr. 3
    ui->comboBoxPlot3ColorLine->setCurrentIndex(1);
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for HPE and HPL
void gLAB_GUI::on_pushButtonTemplateHplHpeSat_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("HPE vs HPL #Sat");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("HPE/HPL (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(23);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("15");
    ui->lineEditPlot1LegendLabel->setText("HPE");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot2Condition->setCurrentIndex(23);
    ui->lineEditPlot2Xcolumn->setText("4");
    ui->lineEditPlot2Ycolumn->setText("16");
    ui->lineEditPlot2LegendLabel->setText("HPL");
    // Plot Nr. 3
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot3SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot3SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot3TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot3Condition->setCurrentIndex(23);
    ui->lineEditPlot3Xcolumn->setText("4");
    ui->lineEditPlot3Ycolumn->setText("24");
    ui->lineEditPlot3LegendLabel->setText("NSAT");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for VPE and VPL
void gLAB_GUI::on_pushButtonTemplateVplVpeSat_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("VPE vs VPL #Sat");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("VPE/VPL (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(23);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("18");
    ui->lineEditPlot1LegendLabel->setText("VPE");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot2Condition->setCurrentIndex(23);
    ui->lineEditPlot2Xcolumn->setText("4");
    ui->lineEditPlot2Ycolumn->setText("19");
    ui->lineEditPlot2LegendLabel->setText("VPL");
    // Plot Nr. 3
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot3SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot3SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot3TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot3Condition->setCurrentIndex(23);
    ui->lineEditPlot3Xcolumn->setText("4");
    ui->lineEditPlot3Ycolumn->setText("24");
    ui->lineEditPlot3LegendLabel->setText("NSAT");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Horizontal Stanford Plot
void gLAB_GUI::on_pushButtonHorStanfordPlot_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Horizontal Stanford Plot");
    ui->lineEditPlotXLabel->setText("Horizontal Positioning Error (m)");
    ui->lineEditPlotYLabel->setText("Horizontal Protection Level (m)");
    //Show options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(false);

    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(23);
    ui->lineEditPlot1Xcolumn->setText("15");
    ui->lineEditPlot1Ycolumn->setText("16");

    //Disable options not available for Stanford-Plot
    ui->radioButtonPlotNr2->setDisabled(true);
    ui->radioButtonPlotNr3->setDisabled(true);
    ui->radioButtonPlotNr4->setDisabled(true);
    ui->comboBoxPlot1Condition->setDisabled(true);
    ui->comboBoxPlot1ConditionOutput->setDisabled(true);
    ui->lineEditPlot1Condition->setDisabled(true);
    ui->comboBoxPlot1TypeLine->setDisabled(true);
    ui->comboBoxPlot1ColorLine->setDisabled(true);
    ui->lineEditPlot1Xcolumn->setDisabled(true);
    ui->lineEditPlot1Ycolumn->setDisabled(true);
    ui->lineEditPlot1LegendLabel->setDisabled(true);

    ui->lineEditFractionalText->setDisabled(true);
    ui->comboBoxLabelPosition->setDisabled(true);
    ui->lineEditPlotXmin->setDisabled(true);
    ui->lineEditPlotYmin->setDisabled(true);

    StanfordPlotSelected = 1;
    StanfordESAPlotSelected = 0;

    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Vertical Stanford Plot
void gLAB_GUI::on_pushButtonVerStanfordPlot_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Vertical Stanford Plot");
    ui->lineEditPlotXLabel->setText("Vertical Positioning Error (m)");
    ui->lineEditPlotYLabel->setText("Vertical Protection Level (m)");
    //Show options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(false);

    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(23);
    ui->lineEditPlot1Xcolumn->setText("18");
    ui->lineEditPlot1Ycolumn->setText("19");

    //Disable options not available for Stanford-Plot
    ui->radioButtonPlotNr2->setDisabled(true);
    ui->radioButtonPlotNr3->setDisabled(true);
    ui->radioButtonPlotNr4->setDisabled(true);
    ui->comboBoxPlot1Condition->setDisabled(true);
    ui->comboBoxPlot1ConditionOutput->setDisabled(true);
    ui->lineEditPlot1Condition->setDisabled(true);
    ui->comboBoxPlot1TypeLine->setDisabled(true);
    ui->comboBoxPlot1ColorLine->setDisabled(true);
    ui->lineEditPlot1Xcolumn->setDisabled(true);
    ui->lineEditPlot1Ycolumn->setDisabled(true);
    ui->lineEditPlot1LegendLabel->setDisabled(true);

    ui->lineEditFractionalText->setDisabled(true);
    ui->comboBoxLabelPosition->setDisabled(true);
    ui->lineEditPlotXmin->setDisabled(true);
    ui->lineEditPlotYmin->setDisabled(true);
    ui->lineEditPlot1SourceFile->setDisabled(false);

    StanfordPlotSelected = 1;
    StanfordESAPlotSelected = 0;

    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Stanford-ESA Plot
void gLAB_GUI::on_pushButtonStanfordESAPlot_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Stanford-ESA Plot");
    ui->lineEditPlotXLabel->setText("Positioning Error (m)");
    ui->lineEditPlotYLabel->setText("Protection Level (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputStanfordEsaPlot->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB_stfd-ESA_plot.txt"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputStanfordEsaPlot->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(0);
    ui->lineEditPlot1Xcolumn->setText("");
    ui->lineEditPlot1Ycolumn->setText("");

    //Disable options not available for Stanford-Plot
    ui->radioButtonPlotNr2->setDisabled(true);
    ui->radioButtonPlotNr3->setDisabled(true);
    ui->radioButtonPlotNr4->setDisabled(true);
    ui->comboBoxPlot1Condition->setDisabled(true);
    ui->comboBoxPlot1ConditionOutput->setDisabled(true);
    ui->lineEditPlot1Condition->setDisabled(true);
    ui->comboBoxPlot1TypeLine->setDisabled(true);
    ui->comboBoxPlot1ColorLine->setDisabled(true);
    ui->lineEditPlot1Xcolumn->setDisabled(true);
    ui->lineEditPlot1Ycolumn->setDisabled(true);
    ui->lineEditPlot1LegendLabel->setDisabled(true);

    ui->lineEditFractionalText->setDisabled(true);
    ui->comboBoxLabelPosition->setDisabled(true);
    ui->checkBoxAutoLimits->setDisabled(true);
    ui->lineEditPlotXmin->setDisabled(true);
    ui->lineEditPlotYmin->setDisabled(true);
    ui->lineEditPlotXmax->setDisabled(true);
    ui->lineEditPlotYmax->setDisabled(true);
    ui->lineEditPlot1SourceFile->setDisabled(false);

    StanfordPlotSelected = 0;
    StanfordESAPlotSelected = 1;

    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for SBAS Model Components
void gLAB_GUI::on_pushButtonTemplateSBASModelComponents_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Model (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());

    if (ui->labelCurrentTemplate->text()=="SBAS 1F") {
        ui->lineEditPlotTitle->setText("SBAS 1F Model Components");
        ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
        ui->comboBoxPlot1Condition->setCurrentIndex(16);
        ui->lineEditPlot1Xcolumn->setText("4");
        ui->lineEditPlot1Ycolumn->setText("27");
    } else if (ui->labelCurrentTemplate->text()=="SBAS DFMC") {
        ui->lineEditPlotTitle->setText("SBAS DFMC Model Components");
        ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
        ui->comboBoxPlot1Condition->setCurrentIndex(20);
        ui->lineEditPlot1Xcolumn->setText("4");
        ui->lineEditPlot1Ycolumn->setText("27");
    }
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for SBAS Sigma Components
void gLAB_GUI::on_pushButtonTemplateSBASSigmaComponents_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Sigma (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    if (ui->labelCurrentTemplate->text()=="SBAS 1F") {
        ui->lineEditPlotTitle->setText("SBAS 1F Sigma Components");
        ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
        ui->comboBoxPlot1Condition->setCurrentIndex(17);
        ui->lineEditPlot1Xcolumn->setText("4");
        ui->lineEditPlot1Ycolumn->setText("16");
    } else if (ui->labelCurrentTemplate->text()=="SBAS DFMC") {
        ui->lineEditPlotTitle->setText("SBAS DFMC Sigma Components");
        ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
        ui->comboBoxPlot1Condition->setCurrentIndex(21);
        ui->lineEditPlot1Xcolumn->setText("4");
        ui->lineEditPlot1Ycolumn->setText("16");
    }
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for SBAS Iono Components
void gLAB_GUI::on_pushButtonTemplateSBASIonoComponents_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("SBAS Iono Components");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Value (L1 m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(18);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("64");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

///////////////// Start of Context menus (right-click menus) //////////////////
void gLAB_GUI::labelPlot1SourceFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelPlot1SourceFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open Plot 1 Source File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPlot1SourceFile->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPlot1SourceFile->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPlot1SourceFile->text();
        #endif

        // Execute the program
        if (ui->lineEditPlot1SourceFile->text() == "") {
            messageBox.warning(nullptr, "Error","Plot 1 file is empty\n");
        } else if (this->fileExists(ui->lineEditPlot1SourceFile->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPlot1SourceFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPlot1SourceFile->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelPlot2SourceFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelPlot2SourceFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open Plot 2 Source File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPlot2SourceFile->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPlot2SourceFile->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPlot2SourceFile->text();
        #endif

        // Execute the program
        if (ui->lineEditPlot2SourceFile->text() == "") {
            messageBox.warning(nullptr, "Error","Plot 2 file is empty\n");
        } else if (this->fileExists(ui->lineEditPlot2SourceFile->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPlot2SourceFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPlot2SourceFile->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelPlot3SourceFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelPlot3SourceFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open Plot 3 Source File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPlot3SourceFile->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPlot3SourceFile->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPlot3SourceFile->text();
        #endif

        // Execute the program
        if (ui->lineEditPlot3SourceFile->text() == "") {
            messageBox.warning(nullptr, "Error","Plot 3 file is empty\n");
        } else if (this->fileExists(ui->lineEditPlot3SourceFile->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPlot3SourceFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPlot3SourceFile->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelPlot4SourceFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelPlot4SourceFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open Plot 4 Source File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPlot4SourceFile->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPlot4SourceFile->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPlot4SourceFile->text();
        #endif

        // Execute the program
        if (ui->lineEditPlot4SourceFile->text() == "") {
            messageBox.warning(nullptr, "Error","Plot 4 file is empty\n");
        } else if (this->fileExists(ui->lineEditPlot4SourceFile->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPlot4SourceFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPlot4SourceFile->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}
///////////////// End of Context menus (right-click menus) //////////////////

void gLAB_GUI::getAnalysisOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString) {

    QString auxstring;

    int labelAdded=0;
    *errorString = "";
    *warningString="";
    *saveString = "";
    //// Global Graphic Parameters
    // Check if we have a stanford Plot
    if ( StanfordPlotSelected == 1 ) {
        *saveString += "--sf\n";
        *runString << "--sf";
    } else if ( StanfordESAPlotSelected == 1 ) {
        *saveString += "--sfesa\n";
        *runString << "--sfesa";
    }

    // Title
    if ( ui->lineEditPlotTitle->text() != "" ) {
        auxstring = ui->lineEditPlotTitle->text().replace("\\n","\n");
        *saveString += "-t \"" + ui->lineEditPlotTitle->text() + "\"\n";
        *runString << "-t" <<auxstring;
    }
    // X-label
    if ( ui->lineEditPlotXLabel->text() != "" ) {
        auxstring = ui->lineEditPlotXLabel->text().replace("\\n","\n");
        *saveString += "--xl \"" + ui->lineEditPlotXLabel->text() + "\"\n";
        *runString << "--xl" << auxstring;
    }
    // Y-label
    if ( ui->lineEditPlotYLabel->text() != "" ) {
        auxstring = ui->lineEditPlotYLabel->text().replace("\\n","\n");
        *saveString += "--yl \"" + ui->lineEditPlotYLabel->text() + "\"\n";
        *runString << "--yl" << auxstring;
    }
    // Axis limits
    if ( ui->checkBoxAutoLimits->isChecked() == false ) {
        if ( ui->lineEditPlotXmin->text() != "" && ui->lineEditPlotXmax->text() != "" ) {
            if ( ui->lineEditPlotXmin->text().toDouble()>=ui->lineEditPlotXmax->text().toDouble()) {
                *errorString += "X maximum value must be greater than the X minimum value\n";
            }
        }
        if ( ui->lineEditPlotYmin->text() != "" && ui->lineEditPlotYmax->text() != "" ) {
            if ( ui->lineEditPlotYmin->text().toDouble()>=ui->lineEditPlotYmax->text().toDouble()) {
                *errorString += "Y maximum value must be greater than the Y minimum value\n";
            }
        }
        if ( ui->lineEditPlotXmin->text() != "" ) {
            *saveString += "--xn " + ui->lineEditPlotXmin->text() + "\n";
            *runString << "--xn" << ui->lineEditPlotXmin->text();
        }
        if ( ui->lineEditPlotXmax->text() != "" ) {
            *saveString += "--xx " + ui->lineEditPlotXmax->text() + "\n";
            *runString << "--xx" << ui->lineEditPlotXmax->text();
        }
        if ( ui->lineEditPlotYmin->text() != "" ) {
            *saveString += "--yn " + ui->lineEditPlotYmin->text() + "\n";
            *runString << "--yn" << ui->lineEditPlotYmin->text();
        }
        if ( ui->lineEditPlotYmax->text() != "" ) {
            *saveString += "--yx " + ui->lineEditPlotYmax->text() + "\n";
            *runString << "--yx" << ui->lineEditPlotYmax->text();
        }
    }
    //Ticks limits
    if ( ui->checkBoxAutoTicks->isChecked() == false ) {
        if ( ui->lineEditXTickNum->text() != "" ) {
            if (ui->lineEditXTickNum->text().toDouble()==0) {
                *errorString += "X Ticks Step cannot be 0\n";
            }
            *saveString += "--xts " + ui->lineEditXTickNum->text() + "\n";
            *runString << "--xts" << ui->lineEditXTickNum->text();
        }
        if ( ui->lineEditYTickNum->text() != "" ) {
            if (ui->lineEditYTickNum->text().toDouble()==0) {
                *errorString += "Y Ticks Step cannot be 0\n";
            }
            *saveString += "--yts " + ui->lineEditYTickNum->text() + "\n";
            *runString << "--yts" << ui->lineEditYTickNum->text();
        }
    }
    //Positioning Error and Protection Level Percentiles for Stanford Plot
    if ( StanfordPlotSelected == 1 ) {
        if (ui->checkBoxPEPercentiles->isChecked()==true) {
            *saveString += "--percentileX\n";
            *runString << "--percentileX";
        }
        if (ui->checkBoxPLPercentiles->isChecked()==true) {
            *saveString += "--percentileY\n";
            *runString << "--percentileY";
        }
    }
    //Adjust to margin option
    if ( ui->checkBoxExpandFigureToMargin->isChecked()==true) {
        *saveString += "--atm\n";
        *runString << "--atm";
    }
    //Fractional text
    if ( ui->lineEditFractionalText->text() != "" ) {
        auxstring = ui->lineEditFractionalText->text().replace("\\n","\n");
        *saveString += "--ft \"" +  ui->lineEditFractionalText->text() +"\"\n";
        *runString << "--ft" << auxstring;
    }
    //WaterMark
    if ( ui->lineEditWaterMark->text() != "") {
         auxstring = ui->lineEditWaterMark->text().replace("\\n","\n");
         *saveString += "--wm  \"" +  ui->lineEditWaterMark->text() +"\"\n";
         *runString << "--wm" << auxstring;
    }


    //// End of Global Graphic Parameters

    // Plot Nr 1
    if ( ui->lineEditPlot1SourceFile->text() != "" ) {
        // Source File
        if ( this->fileExists( ui->lineEditPlot1SourceFile->text() ) == false )
            *errorString += "PLOT 1: Source File does not exist.\n";
        else {
            *saveString += "-f " + ui->lineEditPlot1SourceFile->text() +"\n";
            *runString << "-f" << ui->lineEditPlot1SourceFile->text();
        }
        // Condition(s)
        if ( ui->lineEditPlot1Condition->text() != "" ) {
            #ifdef Q_OS_WIN32
            *saveString += "-c \"" + ui->lineEditPlot1Condition->text().replace(QString("\""), QString("'")) +"\"\n";
            *runString << "-c" << ui->lineEditPlot1Condition->text().replace(QString("\""), QString("'"));
            #else
            *saveString += "-c '" + ui->lineEditPlot1Condition->text() +"'\n";
            *runString << "-c" << ui->lineEditPlot1Condition->text();
            #endif
        }
        // X Column
        if ( ui->lineEditPlot1Xcolumn->text() == "" && StanfordESAPlotSelected == 0 )
            *errorString += "PLOT 1: X Column empty.\n";
        else if ( StanfordESAPlotSelected == 0 ) {
            *saveString += "-x " + ui->lineEditPlot1Xcolumn->text() +"\n";
            *runString << "-x" << ui->lineEditPlot1Xcolumn->text();
        }
        // Y Column
        if ( ui->lineEditPlot1Ycolumn->text() == "" && StanfordESAPlotSelected == 0 )
            *errorString += "PLOT 1: Y Column empty.\n";
        else if ( StanfordESAPlotSelected == 0 ) {
            *saveString += "-y " + ui->lineEditPlot1Ycolumn->text() +"\n";
            *runString << "-y" << ui->lineEditPlot1Ycolumn->text();
        }
        // Legend-label
        if ( ui->lineEditPlot1LegendLabel->text() != "" ) {
            *saveString += "-l \"" + ui->lineEditPlot1LegendLabel->text() + "\"\n";
            *runString << "-l" << ui->lineEditPlot1LegendLabel->text();
            labelAdded=1;
        }
        // Type
        if (StanfordPlotSelected==0 && StanfordESAPlotSelected==0) {
            //Only set linetype and color line if Stanford/Stanford-ESA are not enabled
            switch ( ui->comboBoxPlot1TypeLine->currentIndex() ) {
                case 0 : {
                    *saveString += "-s -\n";
                    *runString << "-s" << "-";
                    break;
                }
                case 1 : {
                    *saveString += "-s .\n";
                    *runString << "-s" << ".";
                    break;
                }
                case 2 : {
                    *saveString += "-s --\n";
                    *runString << "-s" << "--";
                    break;
                }
                case 3 : {
                    *saveString += "-s o\n";
                    *runString << "-s" << "o";
                    break;
                }
                case 4 : {
                    *saveString += "-s s\n";
                    *runString << "-s" << "s";
                    break;
                }
                case 5 : {
                    *saveString += "-s p\n";
                    *runString << "-s" << "p";
                    break;
                }
                case 6 : {
                    *saveString += "-s +\n";
                    *runString << "-s" << "+";
                    break;
                }
                case 7 : {
                    *saveString += "-s x\n";
                    *runString << "-s" << "x";
                    break;
                }
                case 8 : {
                    *saveString += "-s .-\n";
                    *runString << "-s" << ".-";
                    break;
                }
            }
            // Color
            switch ( ui->comboBoxPlot1ColorLine->currentIndex() ) {
                case 0 : {
                    *saveString += "--cl b\n";
                    *runString << "--cl" << "b";
                    break;
                }
                case 1 : {
                    *saveString += "--cl g\n";
                    *runString << "--cl" << "g";
                    break;
                }
                case 2 : {
                    *saveString += "--cl r\n";
                    *runString << "--cl" << "r";
                    break;
                }
                case 3 : {
                    *saveString += "--cl c\n";
                    *runString << "--cl" << "c";
                    break;
                }
                case 4 : {
                    *saveString += "--cl m\n";
                    *runString << "--cl" << "m";
                    break;
                }
                case 5 : {
                    *saveString += "--cl y\n";
                    *runString << "--cl" << "y";
                    break;
                }
                case 6 : {
                    *saveString += "--cl y\n";
                    *runString << "--cl" << "y";
                    break;
                }
            }
        }

    }

    // Plot Nr 2
    if ( ui->lineEditPlot2SourceFile->text() != "" ) {
        // Source File
        if ( this->fileExists( ui->lineEditPlot2SourceFile->text() ) == false )
            *errorString += "PLOT 2: Source File does not exist.\n";
        else {
            *saveString += "-f " + ui->lineEditPlot2SourceFile->text() +"\n";
            *runString << "-f" << ui->lineEditPlot2SourceFile->text();
        }
        // Condition(s)
        if ( ui->lineEditPlot2Condition->text() != "" ) {
            #ifdef Q_OS_WIN32
            *saveString += "-c \"" + ui->lineEditPlot2Condition->text().replace(QString("\""), QString("'")) +"\"\n";
            *runString << "-c" << ui->lineEditPlot2Condition->text().replace(QString("\""), QString("'"));
            #else
            *saveString += "-c '" + ui->lineEditPlot2Condition->text() +"'\n";
            *runString << "-c" << ui->lineEditPlot2Condition->text();
            #endif
        }
        // X Column
        if ( ui->lineEditPlot2Xcolumn->text() == "" && StanfordESAPlotSelected == 0 )
            *errorString += "PLOT 2: X Column empty.\n";
        else if ( StanfordESAPlotSelected == 0 ) {
            *saveString += "-x " + ui->lineEditPlot2Xcolumn->text() +"\n";
            *runString << "-x" << ui->lineEditPlot2Xcolumn->text();
        }
        // Y Column
        if ( ui->lineEditPlot2Ycolumn->text() == "" && StanfordESAPlotSelected == 0 )
            *errorString += "PLOT 2: Y Column empty.\n";
        else if ( StanfordESAPlotSelected == 0 ) {
            *saveString += "-y " + ui->lineEditPlot2Ycolumn->text() +"\n";
            *runString << "-y" << ui->lineEditPlot2Ycolumn->text();
        }
        // Legend-label
        if ( ui->lineEditPlot2LegendLabel->text() != "" ) {
            *saveString += "-l \"" + ui->lineEditPlot2LegendLabel->text() + "\"\n";
            *runString << "-l" << ui->lineEditPlot2LegendLabel->text();
            labelAdded=1;
        }
        // Type
        if (StanfordPlotSelected==0 && StanfordESAPlotSelected==0) {
            //Only set linetype and color line if Stanford/Stanford-ESA are not enabled
            switch ( ui->comboBoxPlot2TypeLine->currentIndex() ) {
                case 0 : {
                    *saveString += "-s -\n";
                    *runString << "-s" << "-";
                    break;
                }
                case 1 : {
                    *saveString += "-s .\n";
                    *runString << "-s" << ".";
                    break;
                }
                case 2 : {
                    *saveString += "-s --\n";
                    *runString << "-s" << "--";
                    break;
                }
                case 3 : {
                    *saveString += "-s o\n";
                    *runString << "-s" << "o";
                    break;
                }
                case 4 : {
                    *saveString += "-s s\n";
                    *runString << "-s" << "s";
                    break;
                }
                case 5 : {
                    *saveString += "-s p\n";
                    *runString << "-s" << "p";
                    break;
                }
                case 6 : {
                    *saveString += "-s +\n";
                    *runString << "-s" << "+";
                    break;
                }
                case 7 : {
                    *saveString += "-s x\n";
                    *runString << "-s" << "x";
                    break;
                }
                case 8 : {
                    *saveString += "-s .-\n";
                    *runString << "-s" << ".-";
                    break;
                }
            }
            // Color
            switch ( ui->comboBoxPlot2ColorLine->currentIndex() ) {
                case 0 : {
                    *saveString += "--cl b\n";
                    *runString << "--cl" << "b";
                    break;
                }
                case 1 : {
                    *saveString += "--cl g\n";
                    *runString << "--cl" << "g";
                    break;
                }
                case 2 : {
                    *saveString += "--cl r\n";
                    *runString << "--cl" << "r";
                    break;
                }
                case 3 : {
                    *saveString += "--cl c\n";
                    *runString << "--cl" << "c";
                    break;
                }
                case 4 : {
                    *saveString += "--cl m\n";
                    *runString << "--cl" << "m";
                    break;
                }
                case 5 : {
                    *saveString += "--cl y\n";
                    *runString << "--cl" << "y";
                    break;
                }
                case 6 : {
                    *saveString += "--cl y\n";
                    *runString << "--cl" << "y";
                    break;
                }
            }
        }

    }

    // Plot Nr 3
    if ( ui->lineEditPlot3SourceFile->text() != "" ) {
        // Source File
        if ( this->fileExists( ui->lineEditPlot3SourceFile->text() ) == false )
            *errorString += "PLOT 3: Source File does not exist.\n";
        else {
            *saveString += "-f " + ui->lineEditPlot3SourceFile->text() +"\n";
            *runString << "-f" << ui->lineEditPlot3SourceFile->text();
        }
        // Condition(s)
        if ( ui->lineEditPlot3Condition->text() != "" ) {
            #ifdef Q_OS_WIN32
            *saveString += "-c \"" + ui->lineEditPlot3Condition->text().replace(QString("\""), QString("'")) +"\"\n";
            *runString << "-c" << ui->lineEditPlot3Condition->text().replace(QString("\""), QString("'"));
            #else
            *saveString += "-c '" + ui->lineEditPlot3Condition->text() +"'\n";
            *runString << "-c" << ui->lineEditPlot3Condition->text();
            #endif
        }
        // X Column
        if ( ui->lineEditPlot3Xcolumn->text() == "" && StanfordESAPlotSelected == 0 )
            *errorString += "PLOT 3: X Column empty.\n";
        else if ( StanfordESAPlotSelected == 0 ) {
            *saveString += "-x " + ui->lineEditPlot3Xcolumn->text() +"\n";
            *runString << "-x" << ui->lineEditPlot3Xcolumn->text();
        }
        // Y Column
        if ( ui->lineEditPlot3Ycolumn->text() == "" && StanfordESAPlotSelected == 0 )
            *errorString += "PLOT 3: Y Column empty.\n";
        else if ( StanfordESAPlotSelected == 0 ) {
            *saveString += "-y " + ui->lineEditPlot3Ycolumn->text() +"\n";
            *runString << "-y" << ui->lineEditPlot3Ycolumn->text();
        }
        // Legend-label
        if ( ui->lineEditPlot3LegendLabel->text() != "" ) {
            *saveString += "-l \"" + ui->lineEditPlot3LegendLabel->text() + "\"\n";
            *runString << "-l" << ui->lineEditPlot3LegendLabel->text();
            labelAdded=1;
        }
        // Type
        if (StanfordPlotSelected==0 && StanfordESAPlotSelected==0) {
            //Only set linetype and color line if Stanford/Stanford-ESA are not enabled
            switch ( ui->comboBoxPlot3TypeLine->currentIndex() ) {
                case 0 : {
                    *saveString += "-s -\n";
                    *runString << "-s" << "-";
                    break;
                }
                case 1 : {
                    *saveString += "-s .\n";
                    *runString << "-s" << ".";
                    break;
                }
                case 2 : {
                    *saveString += "-s --\n";
                    *runString << "-s" << "--";
                    break;
                }
                case 3 : {
                    *saveString += "-s o\n";
                    *runString << "-s" << "o";
                    break;
                }
                case 4 : {
                    *saveString += "-s s\n";
                    *runString << "-s" << "s";
                    break;
                }
                case 5 : {
                    *saveString += "-s p\n";
                    *runString << "-s" << "p";
                    break;
                }
                case 6 : {
                    *saveString += "-s +\n";
                    *runString << "-s" << "+";
                    break;
                }
                case 7 : {
                    *saveString += "-s x\n";
                    *runString << "-s" << "x";
                    break;
                }
                case 8 : {
                    *saveString += "-s .-\n";
                    *runString << "-s" << ".-";
                    break;
                }
            }
            // Color
            switch ( ui->comboBoxPlot3ColorLine->currentIndex() ) {
                case 0 : {
                    *saveString += "--cl b\n";
                    *runString << "--cl" << "b";
                    break;
                }
                case 1 : {
                    *saveString += "--cl g\n";
                    *runString << "--cl" << "g";
                    break;
                }
                case 2 : {
                    *saveString += "--cl r\n";
                    *runString << "--cl" << "r";
                    break;
                }
                case 3 : {
                    *saveString += "--cl c\n";
                    *runString << "--cl" << "c";
                    break;
                }
                case 4 : {
                    *saveString += "--cl m\n";
                    *runString << "--cl" << "m";
                    break;
                }
                case 5 : {
                    *saveString += "--cl y\n";
                    *runString << "--cl" << "y";
                    break;
                }
                case 6 : {
                    *saveString += "--cl y\n";
                    *runString << "--cl" << "y";
                    break;
                }
            }
        }

    }

    // Plot Nr 4
    if ( ui->lineEditPlot4SourceFile->text() != "" ) {
        // Source File
        if ( this->fileExists( ui->lineEditPlot4SourceFile->text() ) == false )
            *errorString += "PLOT 4: Source File does not exist.\n";
        else {
            *saveString += "-f " + ui->lineEditPlot4SourceFile->text() +"\n";
            *runString << "-f" << ui->lineEditPlot4SourceFile->text();
        }
        // Condition(s)
        if ( ui->lineEditPlot4Condition->text() != "" ) {
            #ifdef Q_OS_WIN32
            *saveString += "-c \"" + ui->lineEditPlot4Condition->text().replace(QString("\""), QString("'")) +"\"\n";
            *runString << "-c" << ui->lineEditPlot4Condition->text().replace(QString("\""), QString("'"));
            #else
            *saveString += "-c '" + ui->lineEditPlot4Condition->text() +"'\n";
            *runString << "-c" << ui->lineEditPlot4Condition->text();
            #endif
        }
        // X Column
        if ( ui->lineEditPlot4Xcolumn->text() == "" && StanfordESAPlotSelected == 0 )
            *errorString += "PLOT 4: X Column empty.\n";
        else if ( StanfordESAPlotSelected == 0 ) {
            *saveString += "-x " + ui->lineEditPlot4Xcolumn->text() +"\n";
            *runString << "-x" << ui->lineEditPlot4Xcolumn->text();
        }
        // Y Column
        if ( ui->lineEditPlot4Ycolumn->text() == "" && StanfordESAPlotSelected == 0 )
            *errorString += "PLOT 4: Y Column empty.\n";
        else if ( StanfordESAPlotSelected == 0 ) {
            *saveString += "-y " + ui->lineEditPlot4Ycolumn->text() +"\n";
            *runString << "-y" << ui->lineEditPlot4Ycolumn->text();
        }
        // Legend-label
        if ( ui->lineEditPlot4LegendLabel->text() != "" ) {
            *saveString += "-l \"" + ui->lineEditPlot4LegendLabel->text() + "\"\n";
            *runString << "-l" << ui->lineEditPlot4LegendLabel->text();
            labelAdded=1;
        }
        // Type
        if (StanfordPlotSelected==0 && StanfordESAPlotSelected==0) {
            //Only set linetype and color line if Stanford/Stanford-ESA are not enabled
            switch ( ui->comboBoxPlot4TypeLine->currentIndex() ) {
                case 0 : {
                    *saveString += "-s -\n";
                    *runString << "-s" << "-";
                    break;
                }
                case 1 : {
                    *saveString += "-s .\n";
                    *runString << "-s" << ".";
                    break;
                }
                case 2 : {
                    *saveString += "-s --\n";
                    *runString << "-s" << "--";
                    break;
                }
                case 3 : {
                    *saveString += "-s o\n";
                    *runString << "-s" << "o";
                    break;
                }
                case 4 : {
                    *saveString += "-s s\n";
                    *runString << "-s" << "s";
                    break;
                }
                case 5 : {
                    *saveString += "-s p\n";
                    *runString << "-s" << "p";
                    break;
                }
                case 6 : {
                    *saveString += "-s +\n";
                    *runString << "-s" << "+";
                    break;
                }
                case 7 : {
                    *saveString += "-s x\n";
                    *runString << "-s" << "x";
                    break;
                }
                case 8 : {
                    *saveString += "-s .-\n";
                    *runString << "-s" << ".-";
                    break;
                }
            }
            // Color
            switch ( ui->comboBoxPlot4ColorLine->currentIndex() ) {
                case 0 : {
                    *saveString += "--cl b\n";
                    *runString << "--cl" << "b";
                    break;
                }
                case 1 : {
                    *saveString += "--cl g\n";
                    *runString << "--cl" << "g";
                    break;
                }
                case 2 : {
                    *saveString += "--cl r\n";
                    *runString << "--cl" << "r";
                    break;
                }
                case 3 : {
                    *saveString += "--cl c\n";
                    *runString << "--cl" << "c";
                    break;
                }
                case 4 : {
                    *saveString += "--cl m\n";
                    *runString << "--cl" << "m";
                    break;
                }
                case 5 : {
                    *saveString += "--cl y\n";
                    *runString << "--cl" << "y";
                    break;
                }
                case 6 : {
                    *saveString += "--cl y\n";
                    *runString << "--cl" << "y";
                    break;
                }
            }
        }
    }

    // Set label position. This a global option, but only to be set if a label is given
    if ( labelAdded==1 ) {
        switch ( ui->comboBoxLabelPosition->currentIndex() ) {
            case 0: {
                *saveString += "--lp tr\n";
                *runString << "--lp" << "tr";
                break;
            }
            case 1: {
                *saveString += "--lp tc\n";
                *runString << "--lp" << "tc";
                break;
            }
            case 2: {
                *saveString += "--lp tl\n";
                *runString << "--lp" << "tl";
                break;
            }
            case 3: {
                *saveString += "--lp cr\n";
                *runString << "--lp" << "cr";
                break;
            }
            case 4: {
                *saveString += "--lp c\n";
                *runString << "--lp" << "c";
                break;
            }
            case 5: {
                *saveString += "--lp cl\n";
                *runString << "--lp" << "cl";
                break;
            }
            case 6: {
                *saveString += "--lp br\n";
                *runString << "--lp" << "br";
                break;
            }
            case 7: {
                *saveString += "--lp bc\n";
                *runString << "--lp" << "bc";
                break;
            }
            case 8: {
                *saveString += "--lp bl\n";
                *runString << "--lp" << "bl";
                break;
            }
        }
    }
}
