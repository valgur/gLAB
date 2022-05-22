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

#ifndef GLAB_GUI_H
#define GLAB_GUI_H

#include <QMainWindow>
#include <QApplication>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QDesktopServices>
#include <QListWidget>
#include <QDoubleValidator>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QDir>
#include <QLoggingCategory>
#include <QFileDialog>
#include <QFile>
#include <QToolTip>
#include <QProcess>
#include <QDateTime>
#include <QFileInfo>
#include <QLatin1String>
#include <QComboBox>
#include <QDebug>
#include <QTime>
#include <QTextStream>
#include <QHelpEvent>
#include <QSysInfo>
#include <iostream>
#include <fstream>
#include "date_converter.h"
#include "coord_converter.h"

#define MIN_EARTH_RADIUS            6356752.
#define MAX_GNSS                    7
#define MAX_SATELLITES_PER_GNSS     50
#define MAX_SAT_GPS                 32
#define MAX_SAT_GAL                 32
#define MAX_SAT_GLO                 32
#define MAX_SAT_GEO                 32
#define MAX_SAT_BDS                 34
#define MAX_SAT_QZS                 10
#define MAX_SAT_IRN                 10
#define KMLOPTIONSREDUCETHRESHOLD   1094


// Enumerator for different GNSS systems
enum GNSSystem {
    GNSSSystemUnknown = -1,
    GPS = 0,
    Galileo = 1,
    GLONASS = 2,
    GEO = 3,
    BDS = 4,
    QZSS = 5,
    IRNSS = 6,
};

//NOTE:
// Original size when designing:    1017*670
// New size for fitting SBAS plots: 1017*692

// Namespace
namespace Ui {
    class gLAB_GUI;
}

// On resize events, reapply the expanding tabs style sheet
class ResizeFilter : public QObject {
    QTabWidget *target;
public:
    ResizeFilter(QTabWidget *target) : QObject(target), target(target) {}

    bool eventFilter(QObject *object, QEvent *event) {       
        if (event->type() == QEvent::Resize) {
            // The width of each tab is the width of the tab widget / # of tabs
        #ifdef Q_OS_MAC
            //In Mac. the tabs get resized too big (having to scroll horizontally).
            //This forces the tabs to be resized smaller, so they fit in the window
            target->setStyleSheet(QString("QTabBar::tab{height: 25px;width: %1px;}\
/*QTabBar::tab:selected{background-color:rgb(239, 235, 231);}\
QTabBar::tab:!selected{background-color:rgb(255, 255, 255);}*/").arg(0.85*target->size().width()/target->count()));
        #else
            target->setStyleSheet(QString("QTabBar::tab{height: 25px;width: %1px;}\
/*QTabBar::tab:selected{background-color:rgb(239, 235, 231);}\
QTabBar::tab:!selected{background-color:rgb(255, 255, 255);}*/").arg(target->size().width()/target->count()));
        #endif


        }
        target->setTabShape(QTabWidget::Rounded);
        (void)object; // Just to avoid the compilation warning due to unused variable
        return false;
    }

};

extern int DateConverterWindow;

// Main class of the GUI
class gLAB_GUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit gLAB_GUI(QWidget *parent = 0);
    ~gLAB_GUI();
    double version;
    int revision;
    int StanfordPlotSelected;
    int StanfordESAPlotSelected;
    int mode; //0->SPP //1->PPP
    int WriteAllParameters;    
    int abort;
    int SBASmaritime;
    QStringList configFileName;
    QStringList outputFileName;
    QString RedColor;
    QString GreenColor;
    //This is a definition of a variable with a pointer to a function type "void" with no parameters for class gLAB_GUI
    typedef void (gLAB_GUI::*VoidNoParamFuncPointer)();
    //Declare array of pointer to on_pushButtonG1-32_clicked() functions
    VoidNoParamFuncPointer PushButtonSatFunctions[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
    //Declare array of pointers to pushButtonG1-32 widgets
    QWidget *PushButtonSatWidgets[MAX_GNSS][MAX_SATELLITES_PER_GNSS];

private slots:
    // Piece of header for glab_gui.cpp
    void setInitialPositioningValues();
    void setInitialConverterValues();
    void setInitialCompareOrbitValues();
    void setInitialShowOrbitValues();
    void setInitialAddUserErrorValues();
    void on_actionSPP_triggered();
    void on_actionPPP_triggered();
    void on_actionSBAS_triggered();
    void on_actionDGNSS_triggered();
    void on_actionAnalysis_triggered();
    void on_actionPositioning_triggered();
    void on_actionConverter_triggered();
    void on_actionCompare_Orbits_triggered();
    void on_actionShow_Orbits_triggered();
    void on_actionAdd_User_Error_to_RINEX_triggered();
    void on_actionExit_triggered();
    bool fileExists(QString path);
    bool directoryExists(QString path);
    void getLastLineOfFile(QString path, QString *lastLine);
    void extraParametersToWarningStr(int startPos, QString *warningString, QString option, QStringList ParametersList);
    void checkConfigurationFileInputFilePaths (QString FileDescription, QString *warningString, QString *errorString, QString userInput);
    int  GetPRNRangeParam(QString *userInputSingleSpace, QString *option, enum GNSSystem *System, int *StartPRN, int *EndPRN, QString *warningString);
    int  checkDCBFileType(QString filepath);
    int  checknonASCIIcharacters(QString str);
    void resizeEvent(QResizeEvent* event);
    void closeEvent(QCloseEvent *bar);
    void tabClicked();
    void on_actionVisit_gAGE_website_triggered();
    void on_actionRelease_notes_triggered();
    void on_actionExplained_Formats_triggered();
    void on_actionGNSS_Calendar_triggered();
    void on_actionGNSS_Date_Converter_triggered();
    void on_actionGNSS_Coordinate_Converter_triggered();
    void on_actionManual_triggered();
    void on_actionSBAS_Manual_triggered();
    void on_actionDGNSS_Manual_triggered();
    void on_actionUser_Added_Error_File_Manual_triggered();
    void on_actionUser_defined_Sigma_Multipath_File_Manual_triggered();
    void on_actionReference_Position_File_Manual_triggered();
    void on_actiongLAB_command_line_help_triggered();
    void on_actiongLAB_command_line_messages_description_triggered();
    void on_actionGLAB_command_line_SBAS_maps_description_triggered();
    void on_actionGraph_plot_tool_command_line_help_triggered();
    void on_actionAboutgLAB_triggered();
    void on_actionContact_Us_triggered();
    void on_actionCredits_triggered();
    void on_actionLicense_triggered();
    void on_actionTeqc_triggered();
    void on_actionHatanaka_compressor_triggered();
    void on_actionGFZ_RINEX_version_converter_triggered();
    void on_actionRINEX_file_extension_types_triggered();
    void on_actionIGS_Standards_Website_triggered();
    void on_actionRINEX_SP3_files_triggered();
    void on_actionSINEX_files_triggered();
    void on_actionSINEX_Bias_files_triggered();
    void on_actionIonosphere_IONEX_and_Troposphere_files_triggered();
    void on_actionANTEX_files_triggered();
    void on_actionGNSS_Tutorial_Book_triggered();
    void on_actionMaster_triggered();
    void on_actionCheck_for_updates_triggered();
    void on_actionHeader_triggered();
    void on_actionRINEXObsVersion_2_triggered();
    void on_actionRINEXObsVersion_3_triggered();    
    void on_actionRINEXNavVersion_2_triggered();
    void on_actionRINEXNavVersion_3_triggered();
    void on_actionPrecise_Files_triggered();
    void on_actionSBAS_Files_triggered();
    void on_actionOther_Files_triggered();
    void on_actionRefStations_Spain_triggered();
    void on_actionRefStaions_Coastal_Services_triggered();
    void on_actionLists_of_NTRIP_servers_triggered();
    void on_actionUNAVCO_Database_RINEX_Searcher_triggered();
    void on_actionAdd_your_link_triggered();
    void on_actionReference_gLAB_triggered();
    void on_actionShow_triggered();
    void on_actionShow_command_line_instruction_triggered();
    void sleep(int millisecondsToWait);
    void on_pushButtonAbort_clicked();
    void on_pushButtonRunGlab_clicked();
    void on_pushButtonShowOutput_clicked();
    void on_pushButtonPlot_clicked();
    void on_pushButtonConvert_clicked();
    void on_pushButtonConvertShowOutput_clicked();
    void on_pushButtonCompare_clicked();
    void on_pushButtonCompareShowOutput_clicked();
    void on_pushButtonShowOrbit_clicked();
    void on_pushButtonShowOrbitShowOutput_clicked();
    void on_pushButtonAddError2Rinex_clicked();
    void on_pushButtonAddErrorShowOutput_clicked();
    void on_actionGenerate_minimum_configuration_triggered(bool checked) ;
    void setCorrectSizes();
    void setSBASmodellingDefaults();
    void setModellingDefaults();
    void setFilterDefaults();
    void setOutputDefaults();
    void on_actionSave_triggered();
    void on_actionLoad_triggered();
    void doy2date (int year, int doy, QDate *date);
    void SoD2time (int SoD,QTime *time);
    void GPSTime2DateTime(int GPSWeek, int SoW, QDate *date, QTime *time);
    enum GNSSystem ConsString2ConsEnum(QString Constellation);

    // Header for input.cpp    
    void on_checkBoxStartTime_clicked(bool checked);
    void on_checkBoxEndTime_clicked(bool checked);
    void on_checkBoxAntex_clicked(bool checked);
    void on_checkBoxReferencePositionFileCalculate_clicked(bool checked);
    void on_comboBoxRefStation_currentIndexChanged(int index);
    void on_comboBoxDcbSource_currentIndexChanged(int index);
    void on_comboBoxDcbSourcePPP_currentIndexChanged(int index);
    void on_comboBoxIonoSourceBrdc_currentIndexChanged(int index);
    void on_groupBoxIonoSource_clicked(bool checked);
    void on_groupBoxAuxFiles_clicked(bool checked);
    void on_groupBoxP1C1correction_clicked(bool checked);
    void on_groupBoxP1P2correction_clicked(bool checked);
    void on_groupBoxUserAddedError_clicked(bool checked);
    void on_groupBoxUserDefinedSbasSigmaMultipath_clicked(bool checked);
    void on_groupBoxSbas_clicked(bool checked);
    void on_groupBoxReferenceStation_clicked(bool checked);
    void on_pushButtonRinexObs_clicked();
    void on_pushButtonRinexNav_clicked();
    void on_pushButtonPrecise1File_clicked();
    void on_pushButtonPrecise2Files_clicked();
    void on_pushButtonPreciseClk_clicked();
    void on_pushButtonAntex_clicked();
    void on_pushButtonSinex_clicked();
    void on_pushButtonReferencePositionFileCalculate_clicked();
    void on_pushButtonReferenceFileSpecify_clicked();
    void on_pushButtonReferenceFileRtcm_clicked();
    void on_pushButtonSbas_clicked();
    void on_pushButtonSigmaMultipath_clicked();
    void on_pushButtonUserAddedError_clicked();
    void on_pushButtonRefStaRinex_clicked();
    void on_pushButtonRefStaRtcmAuto_clicked();
    void on_pushButtonRefStaRtcm2_clicked();
    void on_pushButtonRefStaRtcm3_clicked();
    void on_pushButtonDcbFile_clicked();
    void on_pushButtonGPSRecType_clicked();
    void on_pushButtonDcbSourceRinexNav_clicked();
    void on_pushButtonDcbSourceDcb_clicked();
    void on_pushButtonDcbSourceIonex_clicked();
    void on_pushButtonIonoSourceRinexNav_clicked();
    void on_pushButtonIonoSourceIonex_clicked();
    void on_pushButtonIonoSourceSbasSpecify_clicked();
    void on_radioButtonSinex_clicked();
    void on_radioButtonCalculate_clicked();
    void on_radioButtonRinex_clicked();
    void on_radioButtonSpecify_clicked();
    void on_radioButtonSpecifyUserDefined_clicked();
    void on_radioButtonSpecifyReferenceFile_clicked();
    void on_radioButtonSpecifyUserCartesian_clicked();
    void on_radioButtonSpecifyUserGeodetic_clicked();
    void on_radioButtonRtcm_clicked();
    void on_radioButtonCalculateRinex_clicked();
    void on_radioButtonCalculateSpecify_clicked();
    void on_radioButtonCalculateSpecifyCartesian_clicked();
    void on_radioButtonCalculateSpecifyGeodetic_clicked();
    void on_radioButtonOrbitPrecise2files_clicked();
    void on_radioButtonOrbitPrecise1file_clicked();
    void on_radioButtonOrbitBrdc_clicked();
    void on_radioButtonIonoSourceBrdc_clicked();
    void on_radioButtonIonoSourceIonex_clicked();
    void on_radioButtonIonoSourceSbas_clicked();
    void on_radioButtonCalculateEarthCentre_clicked();
    void on_radioButtonRtcmBaseline_clicked();
    void on_radioButtonRtcmRinexRover_clicked();
    void on_radioButtonRtcmSpecify_clicked();
    void on_radioButtonRtcmUserBaseline_clicked();
    void on_radioButtonRtcmUserRinexRover_clicked();
    void on_radioButtonRtcmUserSpecify_clicked();   
    void on_radioButtonRtcmUserDefined_clicked();
    void on_radioButtonRtcmReferenceFile_clicked();
    void on_radioButtonRtcmRecCartesian_clicked();
    void on_radioButtonRtcmRecGeodeticCoord_clicked();
    void on_radioButtonRtcmRefCartesian_clicked();
    void on_radioButtonRtcmRefGeodetic_clicked();
    void on_radioButtonGPSReceiverTypeFile_clicked();
    void on_radioButtonGPSReceiverTypeUserSelection_clicked();
    void labelInputRinexObsFileMenu(const QPoint& pos);
    void checkBoxInputANTEXFileMenu(const QPoint& pos);
    void labelInputRinexNavFileMenu(const QPoint& pos);
    void labelInputSP3OrbitsClocksFileMenu(const QPoint& pos);
    void labelInputSP3OrbitsFileMenu(const QPoint& pos);
    void labelInputClocksFileMenu(const QPoint& pos);
    void labelInputSINEXFileMenu(const QPoint& pos);
    void labelInputSBASFileMenu(const QPoint& pos);
    void comboBoxRefStationFileMenu(const QPoint& pos);
    void labelInputRinexNavIonoFileMenu(const QPoint& pos);
    void labelInputIonexIonoFileMenu(const QPoint& pos);
    void labelInputSbasIonoFileMenu(const QPoint& pos);
    void labelInputDCBP1C1FileMenu(const QPoint& pos);
    void labelInputGPSRecFileMenu(const QPoint& pos);
    void labelInputRinexNavDCBFileMenu(const QPoint& pos);
    void labelInputDCBP1P2FileMenu(const QPoint& pos);
    void labelInputIonexDCBFileMenu(const QPoint& pos);
    void labelInputUserAddedErrorFileMenu(const QPoint& pos);
    void labelInputSigmaMultipathFileMenu(const QPoint& pos);
    void labelReferenceFileRtcmFileMenu(const QPoint& pos);
    void labelReferenceFileSpecifyFileMenu(const QPoint& pos);
    void checkBoxReferencePositionFileCalculateFileMenu(const QPoint& pos);
    void getInputOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);

    // Header for preprocess.cpp
    void InitPushButtonsFuncPointers();
    void InitPushButtonsWidgetPointers();
    void on_checkBoxDataDecimator_clicked(bool checked);
    void on_pushButtonGPSSatSelAll_clicked();
    void on_pushButtonGPSSatSelNone_clicked();
    void on_pushButtonG1_clicked();
    void on_pushButtonG2_clicked();
    void on_pushButtonG3_clicked();
    void on_pushButtonG4_clicked();
    void on_pushButtonG5_clicked();
    void on_pushButtonG6_clicked();
    void on_pushButtonG7_clicked();
    void on_pushButtonG8_clicked();
    void on_pushButtonG9_clicked();
    void on_pushButtonG10_clicked();
    void on_pushButtonG11_clicked();
    void on_pushButtonG12_clicked();
    void on_pushButtonG13_clicked();
    void on_pushButtonG14_clicked();
    void on_pushButtonG15_clicked();
    void on_pushButtonG16_clicked();
    void on_pushButtonG17_clicked();
    void on_pushButtonG18_clicked();
    void on_pushButtonG19_clicked();
    void on_pushButtonG20_clicked();
    void on_pushButtonG21_clicked();
    void on_pushButtonG22_clicked();
    void on_pushButtonG23_clicked();
    void on_pushButtonG24_clicked();
    void on_pushButtonG25_clicked();
    void on_pushButtonG26_clicked();
    void on_pushButtonG27_clicked();
    void on_pushButtonG28_clicked();
    void on_pushButtonG29_clicked();
    void on_pushButtonG30_clicked();
    void on_pushButtonG31_clicked();
    void on_pushButtonG32_clicked();
    void callSatellitePushButtonFunction(enum GNSSystem System, int PRN, QString Sign);
    void on_checkBoxNcon_clicked(bool checked);
    void on_checkBoxDiscardSNRThreshold_clicked(bool checked);
    void on_comboBoxSNRThresholds_currentIndexChanged(int index);
    void on_pushButtonConfigureL1C1_clicked();
    void on_checkBoxL1C1ConsistencyCheck_clicked(bool checked);
    void on_pushButtonConfigureMW_clicked();
    void on_pushButtonConfigureLI_clicked();
    void setCSdefaults();
    void getPreprocessOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);

    // Header for modelling.cpp
    void on_checkBoxIonoCorrection_clicked(bool checked);
    void on_checkBoxTropoCorrection_clicked(bool checked);
    void on_checkBoxAntennaPhase_clicked(bool checked);
    void on_checkBoxSatMassCentre_clicked(bool checked);
    void on_checkBoxAntennaReference_clicked(bool checked);
    void on_checkBoxP1P2correction_clicked(bool checked);
    void on_checkBoxP1C1correction_clicked(bool checked);
    void on_groupBoxConcatenedPreciseFiles_clicked(bool checked);
    void on_radioButtonAPCread_clicked();
    void on_radioButtonAPCspecify_clicked();
    void on_radioButtonARPread_clicked();
    void on_radioButtonARPspecify_clicked();
    void on_radioButtonAPCspecifyF1_clicked();
    void on_radioButtonAPCspecifyF2_clicked();
    void on_comboBoxP1P2correction_currentIndexChanged(int index);
    void on_comboBoxP1C1correction_currentIndexChanged(int index);
    void on_comboBoxIonoCorrection_currentIndexChanged(int index);
    void on_comboBoxSBASApplication_currentIndexChanged(int index);
    void on_comboBoxSbasNavigationMode_currentIndexChanged(int index);
    void on_checkBoxNavigationModeSwitching_clicked(bool checked);
    void on_comboBoxGEOselection_currentIndexChanged(int index);
    void on_groupBoxSbasAdvancedOptions_clicked(bool checked);
    void on_checkBoxGEOexclusion_clicked(bool checked);
    void on_comboBoxGEOexclusion_currentIndexChanged(int index);
    void on_checkBoxGEOswitching_clicked(bool checked);
    void on_checkBoxSelectBestGEO_clicked(bool checked);
    void on_checkBoxUserDefinedReceiverSigmaMultipathModel_clicked(bool checked);
    void on_groupBoxUserDefinedReceiverSigma_clicked(bool checked);
    void on_checkBoxUserDefinedReceiverSigmaMultipath_clicked(bool checked);
    void on_checkBoxUserDefinedReceiverSigmaDivergence_clicked(bool checked);
    void on_checkBoxUserDefinedReceiverSigmaNoise_clicked(bool checked);
    void on_comboBoxAirboneReceiverType_currentIndexChanged(int index);
    void on_checkBoxDiscardUDREIThreshold_clicked(bool checked);
    void on_checkBoxMaintainCurrentGEOafterGEOswitch_clicked(bool checked);
    void on_checkBoxReturnToInitialGEO_clicked(bool checked);
    void on_groupBoxMessageTimeOuts_clicked(bool checked);
    void on_groupBoxSBASKFactor_clicked(bool checked);
    void on_groupBoxDisableSBASMessages_clicked(bool checked);
    void on_groupBoxDisableSpecificCorrections_clicked(bool checked);
    void on_groupBoxDisableSpecificSigmas_clicked(bool checked);
    void on_comboBoxTropoCorrection_currentIndexChanged(int index);
    void on_checkBoxDisableFastCorrections_clicked(bool checked);
    void on_checkBoxDisableFastCorrectionsSigma_clicked(bool checked);
    void showHidePAtimeouts(bool hide);
    void showHideNPAtimeouts(bool hide);
    void readSBASMTandTimeout(int MT, int timeout, int type, QString option, QString *warningString);    
    void getModellingOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);

    // Header for filter.cpp
    void on_checkBoxSmoothing_clicked(bool checked);
    void on_checkBoxExcludeDuringSmoothingConvergenceUser_clicked(bool checked);
    void on_checkBoxExcludeDuringSmoothingConvergenceRef_clicked(bool checked);
    void on_radioButtonSingleFreq_clicked();
    void on_radioButtonDualFreq_clicked();
    void on_radioButtonSelectionPseudorange_clicked();
    void on_radioButtonSelectionPseudorangeCarrierPhase_clicked();
    void on_radioButtonFixedStdDevSingleCode_clicked();
    void on_radioButtonFixedStdDevSingleCarrier_clicked();
    void on_radioButtonElevationStdDevSingleCode_clicked();
    void on_radioButtonElevationStdDevSingleCarrier_clicked();
    void on_radioButtonFixedStdDevDualCode_clicked();
    void on_radioButtonFixedStdDevDualCarrier_clicked();
    void on_radioButtonElevationStdDevDualCode_clicked();
    void on_radioButtonElevationStdDevDualCarrier_clicked();
    void on_radioButtonStatic_clicked();
    void on_radioButtonKinematic_clicked();
    void on_radioButtonStdDevSBAS_clicked();
    void on_radioButtonStdDevDGNSS_clicked();
    void on_checkBoxEstimateTroposphere_clicked(bool checked);
    void on_checkBoxMaxHDOP_clicked(bool checked);
    void on_checkBoxMaxPDOP_clicked(bool checked);
    void on_checkBoxMaxGDOP_clicked(bool checked);
    void on_checkBoxPrefitOutliers_clicked(bool checked);
    void getFilterOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);

    // Header for output.cpp
    void on_checkBoxKML_clicked(bool checked);
    void on_checkBoxKML0_clicked(bool checked);
    void on_checkBox_KML_TimeStamps_clicked(bool checked);
    void on_checkBox_KML_Range_clicked(bool checked);
    void on_checkBoxOutputSP3_clicked(bool checked);
    void on_checkBoxOutRefFile_clicked(bool checked);
    void on_pushButtonOutputDestination_clicked();
    void on_pushButtonOutputKML_clicked();
    void on_pushButtonOutputKML0_clicked();
    void on_pushButtonOutputSP3_clicked();
    void on_pushButtonOutRefFile_clicked();
    void on_pushButtonOutputStanfordEsaPlot_clicked();
    void on_pushButtonOutputframeStanfordESAallGeometries_clicked();
    void labelOutputFileMenu(const QPoint& pos);
    void checkBoxKMLMenu(const QPoint& pos);
    void checkBoxKML0Menu(const QPoint& pos);
    void checkBoxOutputSP3Menu(const QPoint& pos);
    void checkBoxOutRefFileMenu(const QPoint& pos);
    void labelStfdESAPlotFileMenu(const QPoint& pos);
    void labelStfdESADataFileMenu(const QPoint& pos);
    void on_pushButtonCommonNavigationMessagesAll_clicked();
    void on_pushButtonCommonNavigationMessagesNone_clicked();
    void on_pushButtonOrbitsComparisonMessagesAll_clicked();
    void on_pushButtonOrbitsComparisonMessagesNone_clicked();
    void on_pushButtonSbasMessagesAll_clicked();
    void on_pushButtonSbasMessagesNone_clicked();
    void on_pushButtonDgnssMessagesAll_clicked();
    void on_pushButtonDgnssMessagesNone_clicked();
    void on_groupBoxStanfordESA_clicked(bool checked);
    void on_checkBoxStanfordESAallGeometries_clicked(bool checked);
    void on_checkBoxPrintSummary_clicked(bool checked);
    void on_checkBoxWaitforDayStart_clicked(bool checked);
    void on_checkBoxStartTimeSummary_clicked(bool checked);
    void getOutputOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);

    // Header for analysis.cpp
    void set_conditionsComboBoxPlot1_OutputMessagesTooltips();
    void set_conditionsComboBoxPlot2_OutputMessagesTooltips();
    void set_conditionsComboBoxPlot3_OutputMessagesTooltips();
    void set_conditionsComboBoxPlot4_OutputMessagesTooltips();
    void on_pushButtonPlotClear_clicked();
    void on_checkBoxAutoLimits_clicked(bool checked);
    void on_checkBoxAutoTicks_clicked(bool checked);
    void on_radioButtonPlotNr1_clicked();
    void on_radioButtonPlotNr2_clicked();
    void on_radioButtonPlotNr3_clicked();
    void on_radioButtonPlotNr4_clicked();
    void labelPlot1SourceFileMenu(const QPoint& pos);
    void labelPlot2SourceFileMenu(const QPoint& pos);
    void labelPlot3SourceFileMenu(const QPoint& pos);
    void labelPlot4SourceFileMenu(const QPoint& pos);
    void getAnalysisOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);    

    // Plot Nr 1
    void on_comboBoxPlot1Condition_currentIndexChanged(int index);
    void on_comboBoxPlot1ConditionPrn_currentIndexChanged(int index);
    void on_comboBoxPlot1ConditionOutput_currentIndexChanged(int index);
    void on_pushButtonPlot1SourceFile_clicked();
    void on_lineEditPlot1SourceFile_textChanged();
    void on_lineEditPlot1Xcolumn_textChanged();
    void on_comboBoxPlot1Xinput_currentIndexChanged(int index);
    void on_comboBoxPlot1Xcs_currentIndexChanged(int index);
    void on_comboBoxPlot1Xmodel_currentIndexChanged(int index);
    void on_comboBoxPlot1Xepochsat_currentIndexChanged(int index);
    void on_comboBoxPlot1Xprefit_currentIndexChanged(int index);
    void on_comboBoxPlot1Xpostfit_currentIndexChanged(int index);
    void on_comboBoxPlot1Xfilter_currentIndexChanged(int index);
    void on_comboBoxPlot1Xoutput_currentIndexChanged(int index);
    void on_comboBoxPlot1Xsatdiff_currentIndexChanged(int index);
    void on_comboBoxPlot1Xsatstat_currentIndexChanged(int index);
    void on_comboBoxPlot1Xsatstattot_currentIndexChanged(int index);
    void on_comboBoxPlot1Xsatpvt_currentIndexChanged(int index);
    void on_comboBoxPlot1Xsbascorr_currentIndexChanged(int index);
    void on_comboBoxPlot1Xsbasvar_currentIndexChanged(int index);
    void on_comboBoxPlot1Xsbasiono_currentIndexChanged(int index);
    void on_comboBoxPlot1Xsbasunsel_currentIndexChanged(int index);
    void on_comboBoxPlot1Xsbasout_currentIndexChanged(int index);
    void on_comboBoxPlot1Xdgnss_currentIndexChanged(int index);
    void on_comboBoxPlot1Xuseraddederror_currentIndexChanged(int index);
    void on_lineEditPlot1Ycolumn_textChanged();
    void on_comboBoxPlot1Yinput_currentIndexChanged(int index);
    void on_comboBoxPlot1Ycs_currentIndexChanged(int index);
    void on_comboBoxPlot1Ymodel_currentIndexChanged(int index);
    void on_comboBoxPlot1Yepochsat_currentIndexChanged(int index);
    void on_comboBoxPlot1Yprefit_currentIndexChanged(int index);
    void on_comboBoxPlot1Ypostfit_currentIndexChanged(int index);
    void on_comboBoxPlot1Yfilter_currentIndexChanged(int index);
    void on_comboBoxPlot1Youtput_currentIndexChanged(int index);
    void on_comboBoxPlot1Ysatdiff_currentIndexChanged(int index);
    void on_comboBoxPlot1Ysatstat_currentIndexChanged(int index);
    void on_comboBoxPlot1Ysatstattot_currentIndexChanged(int index);
    void on_comboBoxPlot1Ysatpvt_currentIndexChanged(int index);
    void on_comboBoxPlot1Ysbascorr_currentIndexChanged(int index);
    void on_comboBoxPlot1Ysbasvar_currentIndexChanged(int index);
    void on_comboBoxPlot1Ysbasiono_currentIndexChanged(int index);
    void on_comboBoxPlot1Ysbasunsel_currentIndexChanged(int index);
    void on_comboBoxPlot1Ysbasout_currentIndexChanged(int index);
    void on_comboBoxPlot1Ydgnss_currentIndexChanged(int index);
    void on_comboBoxPlot1Yuseraddederror_currentIndexChanged(int index);
    // Plot Nr 2
    void on_comboBoxPlot2Condition_currentIndexChanged(int index);
    void on_comboBoxPlot2ConditionPrn_currentIndexChanged(int index);
    void on_comboBoxPlot2ConditionOutput_currentIndexChanged(int index);
    void on_pushButtonPlot2SourceFile_clicked();
    void on_lineEditPlot2SourceFile_textChanged();
    void on_lineEditPlot2Xcolumn_textChanged();
    void on_comboBoxPlot2Xinput_currentIndexChanged(int index);
    void on_comboBoxPlot2Xcs_currentIndexChanged(int index);
    void on_comboBoxPlot2Xmodel_currentIndexChanged(int index);
    void on_comboBoxPlot2Xepochsat_currentIndexChanged(int index);
    void on_comboBoxPlot2Xprefit_currentIndexChanged(int index);
    void on_comboBoxPlot2Xpostfit_currentIndexChanged(int index);
    void on_comboBoxPlot2Xfilter_currentIndexChanged(int index);
    void on_comboBoxPlot2Xoutput_currentIndexChanged(int index);
    void on_comboBoxPlot2Xsatdiff_currentIndexChanged(int index);
    void on_comboBoxPlot2Xsatstat_currentIndexChanged(int index);
    void on_comboBoxPlot2Xsatstattot_currentIndexChanged(int index);
    void on_comboBoxPlot2Xsatpvt_currentIndexChanged(int index);
    void on_comboBoxPlot2Xsbascorr_currentIndexChanged(int index);
    void on_comboBoxPlot2Xsbasvar_currentIndexChanged(int index);
    void on_comboBoxPlot2Xsbasiono_currentIndexChanged(int index);
    void on_comboBoxPlot2Xsbasunsel_currentIndexChanged(int index);
    void on_comboBoxPlot2Xsbasout_currentIndexChanged(int index);
    void on_comboBoxPlot2Xdgnss_currentIndexChanged(int index);
    void on_comboBoxPlot2Xuseraddederror_currentIndexChanged(int index);
    void on_lineEditPlot2Ycolumn_textChanged();
    void on_comboBoxPlot2Yinput_currentIndexChanged(int index);
    void on_comboBoxPlot2Ycs_currentIndexChanged(int index);
    void on_comboBoxPlot2Ymodel_currentIndexChanged(int index);
    void on_comboBoxPlot2Yepochsat_currentIndexChanged(int index);
    void on_comboBoxPlot2Yprefit_currentIndexChanged(int index);
    void on_comboBoxPlot2Ypostfit_currentIndexChanged(int index);
    void on_comboBoxPlot2Yfilter_currentIndexChanged(int index);
    void on_comboBoxPlot2Youtput_currentIndexChanged(int index);
    void on_comboBoxPlot2Ysatdiff_currentIndexChanged(int index);
    void on_comboBoxPlot2Ysatstat_currentIndexChanged(int index);
    void on_comboBoxPlot2Ysatstattot_currentIndexChanged(int index);
    void on_comboBoxPlot2Ysatpvt_currentIndexChanged(int index);
    void on_comboBoxPlot2Ysbascorr_currentIndexChanged(int index);
    void on_comboBoxPlot2Ysbasvar_currentIndexChanged(int index);
    void on_comboBoxPlot2Ysbasiono_currentIndexChanged(int index);
    void on_comboBoxPlot2Ysbasunsel_currentIndexChanged(int index);
    void on_comboBoxPlot2Ysbasout_currentIndexChanged(int index);
    void on_comboBoxPlot2Ydgnss_currentIndexChanged(int index);
    void on_comboBoxPlot2Yuseraddederror_currentIndexChanged(int index);
    // Plot Nr 3
    void on_comboBoxPlot3Condition_currentIndexChanged(int index);
    void on_comboBoxPlot3ConditionPrn_currentIndexChanged(int index);
    void on_comboBoxPlot3ConditionOutput_currentIndexChanged(int index);
    void on_pushButtonPlot3SourceFile_clicked();
    void on_lineEditPlot3SourceFile_textChanged();
    void on_lineEditPlot3Xcolumn_textChanged();
    void on_comboBoxPlot3Xinput_currentIndexChanged(int index);
    void on_comboBoxPlot3Xcs_currentIndexChanged(int index);
    void on_comboBoxPlot3Xmodel_currentIndexChanged(int index);
    void on_comboBoxPlot3Xepochsat_currentIndexChanged(int index);
    void on_comboBoxPlot3Xprefit_currentIndexChanged(int index);
    void on_comboBoxPlot3Xpostfit_currentIndexChanged(int index);
    void on_comboBoxPlot3Xfilter_currentIndexChanged(int index);
    void on_comboBoxPlot3Xoutput_currentIndexChanged(int index);
    void on_comboBoxPlot3Xsatdiff_currentIndexChanged(int index);
    void on_comboBoxPlot3Xsatstat_currentIndexChanged(int index);
    void on_comboBoxPlot3Xsatstattot_currentIndexChanged(int index);
    void on_comboBoxPlot3Xsatpvt_currentIndexChanged(int index);
    void on_comboBoxPlot3Xsbascorr_currentIndexChanged(int index);
    void on_comboBoxPlot3Xsbasvar_currentIndexChanged(int index);
    void on_comboBoxPlot3Xsbasiono_currentIndexChanged(int index);
    void on_comboBoxPlot3Xsbasunsel_currentIndexChanged(int index);
    void on_comboBoxPlot3Xsbasout_currentIndexChanged(int index);
    void on_comboBoxPlot3Xdgnss_currentIndexChanged(int index);
    void on_comboBoxPlot3Xuseraddederror_currentIndexChanged(int index);
    void on_lineEditPlot3Ycolumn_textChanged();
    void on_comboBoxPlot3Yinput_currentIndexChanged(int index);
    void on_comboBoxPlot3Ycs_currentIndexChanged(int index);
    void on_comboBoxPlot3Ymodel_currentIndexChanged(int index);
    void on_comboBoxPlot3Yepochsat_currentIndexChanged(int index);
    void on_comboBoxPlot3Yprefit_currentIndexChanged(int index);
    void on_comboBoxPlot3Ypostfit_currentIndexChanged(int index);
    void on_comboBoxPlot3Yfilter_currentIndexChanged(int index);
    void on_comboBoxPlot3Youtput_currentIndexChanged(int index);
    void on_comboBoxPlot3Ysatdiff_currentIndexChanged(int index);
    void on_comboBoxPlot3Ysatstat_currentIndexChanged(int index);
    void on_comboBoxPlot3Ysatstattot_currentIndexChanged(int index);
    void on_comboBoxPlot3Ysatpvt_currentIndexChanged(int index);
    void on_comboBoxPlot3Ysbascorr_currentIndexChanged(int index);
    void on_comboBoxPlot3Ysbasvar_currentIndexChanged(int index);
    void on_comboBoxPlot3Ysbasiono_currentIndexChanged(int index);
    void on_comboBoxPlot3Ysbasunsel_currentIndexChanged(int index);
    void on_comboBoxPlot3Ysbasout_currentIndexChanged(int index);
    void on_comboBoxPlot3Ydgnss_currentIndexChanged(int index);
    void on_comboBoxPlot3Yuseraddederror_currentIndexChanged(int index);
    // Plot Nr 4
    void on_comboBoxPlot4Condition_currentIndexChanged(int index);
    void on_comboBoxPlot4ConditionPrn_currentIndexChanged(int index);
    void on_comboBoxPlot4ConditionOutput_currentIndexChanged(int index);
    void on_pushButtonPlot4SourceFile_clicked();
    void on_lineEditPlot4SourceFile_textChanged();
    void on_lineEditPlot4Xcolumn_textChanged();
    void on_comboBoxPlot4Xinput_currentIndexChanged(int index);
    void on_comboBoxPlot4Xcs_currentIndexChanged(int index);
    void on_comboBoxPlot4Xmodel_currentIndexChanged(int index);
    void on_comboBoxPlot4Xepochsat_currentIndexChanged(int index);
    void on_comboBoxPlot4Xprefit_currentIndexChanged(int index);
    void on_comboBoxPlot4Xpostfit_currentIndexChanged(int index);
    void on_comboBoxPlot4Xfilter_currentIndexChanged(int index);
    void on_comboBoxPlot4Xoutput_currentIndexChanged(int index);
    void on_comboBoxPlot4Xsatdiff_currentIndexChanged(int index);
    void on_comboBoxPlot4Xsatstat_currentIndexChanged(int index);
    void on_comboBoxPlot4Xsatstattot_currentIndexChanged(int index);
    void on_comboBoxPlot4Xsatpvt_currentIndexChanged(int index);
    void on_comboBoxPlot4Xsbascorr_currentIndexChanged(int index);
    void on_comboBoxPlot4Xsbasvar_currentIndexChanged(int index);
    void on_comboBoxPlot4Xsbasiono_currentIndexChanged(int index);
    void on_comboBoxPlot4Xsbasunsel_currentIndexChanged(int index);
    void on_comboBoxPlot4Xsbasout_currentIndexChanged(int index);
    void on_comboBoxPlot4Xdgnss_currentIndexChanged(int index);
    void on_comboBoxPlot4Xuseraddederror_currentIndexChanged(int index);
    void on_lineEditPlot4Ycolumn_textChanged();
    void on_comboBoxPlot4Yinput_currentIndexChanged(int index);
    void on_comboBoxPlot4Ycs_currentIndexChanged(int index);
    void on_comboBoxPlot4Ymodel_currentIndexChanged(int index);
    void on_comboBoxPlot4Yepochsat_currentIndexChanged(int index);
    void on_comboBoxPlot4Yprefit_currentIndexChanged(int index);
    void on_comboBoxPlot4Ypostfit_currentIndexChanged(int index);
    void on_comboBoxPlot4Yfilter_currentIndexChanged(int index);
    void on_comboBoxPlot4Youtput_currentIndexChanged(int index);
    void on_comboBoxPlot4Ysatdiff_currentIndexChanged(int index);
    void on_comboBoxPlot4Ysatstat_currentIndexChanged(int index);
    void on_comboBoxPlot4Ysatstattot_currentIndexChanged(int index);
    void on_comboBoxPlot4Ysatpvt_currentIndexChanged(int index);
    void on_comboBoxPlot4Ysbascorr_currentIndexChanged(int index);
    void on_comboBoxPlot4Ysbasvar_currentIndexChanged(int index);
    void on_comboBoxPlot4Ysbasiono_currentIndexChanged(int index);
    void on_comboBoxPlot4Ysbasunsel_currentIndexChanged(int index);
    void on_comboBoxPlot4Ysbasout_currentIndexChanged(int index);
    void on_comboBoxPlot4Ydgnss_currentIndexChanged(int index);
    void on_comboBoxPlot4Yuseraddederror_currentIndexChanged(int index);
    // Analysis Templates
    void on_pushButtonTemplateNeuPositioningError_clicked();
    void on_pushButtonTemplateHorizontalError_clicked();
    void on_pushButtonTemplateZenithTroposphericDelay_clicked();
    void on_pushButtonTemplateIonosphericCombinations_clicked();
    void on_pushButtonTemplateDOP_clicked();
    void on_pushButtonTemplateSatelliteSkyplot_clicked();
    void on_pushButtonTemplateCarrierPhaseAmbiguities_clicked();
    void on_pushButtonTemplateMeasurementMultipath_clicked();
    void on_pushButtonTemplateModelComponents_clicked();
    void on_pushButtonTemplatePrefitResiduals_clicked();
    void on_pushButtonTemplatePostfitResiduals_clicked();
    void on_pushButtonTemplateOrbitAndClockComparison_clicked();
    void on_pushButtonTemplateDifferentialCorrections_clicked();
    void on_pushButtonTemplateSigmaPRC_clicked();
    void on_pushButtonTemplateHplHpeSat_clicked();
    void on_pushButtonTemplateVplVpeSat_clicked();
    void on_pushButtonHorStanfordPlot_clicked();
    void on_pushButtonVerStanfordPlot_clicked();
    void on_pushButtonStanfordESAPlot_clicked();
    void on_pushButtonTemplateSBASModelComponents_clicked();
    void on_pushButtonTemplateSBASSigmaComponents_clicked();
    void on_pushButtonTemplateSBASIonoComponents_clicked();

    // Header for converter.cpp
    void on_groupBoxConverterSBAS_clicked(bool checked);
    void on_groupBoxConverterDgnss_clicked(bool checked);
	void on_checkBox_pegasus_clicked(bool checked);
	void on_pushButton_convert_sbas_clicked();
	void on_pushButton_output_path_sbas_clicked();
    void on_pushButtonConverterDgnssInput_clicked();
    void on_pushButtonConverterDgnssOutputRinex_clicked();
    void on_pushButtonConverterDgnssOutputAsciiCorrections_clicked();
    void on_pushButtonConverterDgnssOutputAsciiAntenna_clicked();
    void on_lineEditConverterDgnssInput_textChanged();
    void on_dateEdit4_dateChanged();
    void on_comboBoxConverterDgnssInput_currentIndexChanged(int index);
    void labelConvSbasFileMenu(const QPoint& pos);
    void labelConvOutputPathMenu(const QPoint& pos);
    void comboBoxConverterDgnssInputMenu(const QPoint& pos);
    void comboBoxConverterDgnssOutputRinexMenu(const QPoint& pos);
    void labelConvCorrectionsFileMenu(const QPoint& pos);
    void labelConvAntennaFileMenu(const QPoint& pos);
    int getConverterOptions(int ShowCommandline, QString *errorString, QString *warningString, QString *saveString, QStringList *runString);
    void converterLoadParameters(QFile *file);

    //Header for compareOrbits.cpp
    void on_checkBoxAntexCompareOrbitsFile2_clicked(bool checked);
    void on_radioButtonOrbitNavCompareFile1_clicked();
    void on_radioButtonOrbitPrecise1filesCompareFile1_clicked();
    void on_radioButtonOrbitPrecise2filesCompareFile1_clicked();
    void on_radioButtonOrbitNavCompareFile2_clicked();
    void on_radioButtonOrbitPrecise1filesCompareFile2_clicked();
    void on_radioButtonOrbitPrecise2filesCompareFile2_clicked();
    void on_pushButtonRinexNavCompareFile1_clicked();
    void on_pushButtonPrecise1FileCompareFile1_clicked();
    void on_pushButtonPrecise2FilesCompareFile1_clicked();
    void on_pushButtonPreciseClkCompareFile1_clicked();
    void on_pushButtonRinexNavCompareFile2_clicked();
    void on_pushButtonPrecise1FileCompareFile2_clicked();
    void on_pushButtonPrecise2FilesCompareFile2_clicked();
    void on_pushButtonPreciseClkCompareFile2_clicked();
    void on_pushButtonAntexCompareOrbitsFile2_clicked();
    void on_pushButtonOutputFileCompare_clicked();
    void on_pushButtonOrbitsCompareMessagesAll_clicked();
    void on_pushButtonOrbitsCompareMessagesNone_clicked();
    void on_groupBoxConcatenedPreciseFilesCompare_clicked(bool checked);
    void labelCompareRinexNavFile1Menu(const QPoint& pos);
    void labelCompareSP3OrbitsClocksFile1Menu(const QPoint& pos);
    void labelCompareSP3OrbitsFile1Menu(const QPoint& pos);
    void labelCompareClockFile1Menu(const QPoint& pos);
    void labelCompareRinexNavFile2Menu(const QPoint& pos);
    void labelCompareSP3OrbitsClocksFile2Menu(const QPoint& pos);
    void labelCompareSP3OrbitsFile2Menu(const QPoint& pos);
    void labelCompareClockFile2Menu(const QPoint& pos);
    void checkBoxAntexCompareOrbitsFile2Menu(const QPoint& pos);
    void labelCompareOutputFileMenu(const QPoint& pos);
    void getCompareOrbitOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);
    void compareOrbitsLoadParameters(QFile *file);

    //Header for showOrbits.cpp
    void on_checkBoxAntexShowOrbitFile_clicked(bool checked);
    void on_radioButtonOrbitNavShowOrbitFile_clicked() ;
    void on_radioButtonOrbitPrecise1filesShowOrbitFile_clicked() ;
    void on_radioButtonOrbitPrecise2filesShowOrbitFile_clicked();
    void on_pushButtonRinexNavShowOrbitFile_clicked();
    void on_pushButtonPrecise1FileShowOrbitFile_clicked();
    void on_pushButtonPrecise2FilesShowOrbitFile_clicked();
    void on_pushButtonPreciseClkShowOrbitFile_clicked();
    void on_pushButtonAntexShowOrbitFile_clicked();
    void on_pushButtonOutputFileShowOrbit_clicked();
    void on_pushButtonShowOrbitMessagesAll_clicked();
    void on_pushButtonShowOrbitMessagesNone_clicked();
    void on_groupBoxConcatenedPreciseFilesShowOrbit_clicked(bool checked);
    void labelShowOrbitRinexNavFileMenu(const QPoint& pos);
    void labelShowOrbitSP3OrbitsClocksFileMenu(const QPoint& pos);
    void labelShowOrbitSP3OrbitsFileMenu(const QPoint& pos);
    void labelShowOrbitClocksFileMenu(const QPoint& pos);
    void checkBoxAntexShowOrbitFileMenu(const QPoint& pos);
    void labelShowOrbitOutputFileMenu(const QPoint& pos);
    void getshowOrbitOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);
    void showOrbitsLoadParameters(QFile *file);

    //Header for adderror_rinex.cpp
    void on_pushButtonRinexObsAddError_clicked();
    void on_pushButtonUserAddedErrorAddError_clicked();
    void on_pushButtonRinexOutputFileAddError_clicked();
    void on_pushButtonOutputFileAddError_clicked();
    void on_pushButtonAddErrorMessagesAll_clicked();
    void on_pushButtonAddErrorMessagesNone_clicked();
    void labelAddErrorObservationFileMenu(const QPoint& pos);
    void labelAddErrorUserAddedErrorFileMenu(const QPoint& pos);
    void labelAddErrorRinexOutputFileMenu(const QPoint& pos);
    void labelAddErrorOutputFileMenu(const QPoint& pos);
    void getAddErrorOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);
    void AddErrorLoadParameters(QFile *file);



private:
    Ui::gLAB_GUI *ui;
    GNSS_Date_Converter      *DateConvWin;
    GNSS_Coord_converter     *CoordConvWin;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};


#endif // GLAB_GUI_H

