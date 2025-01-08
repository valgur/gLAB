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
#include <QGuiApplication>
#include <QGroupBox>
#include <QScreen>
#include <QScrollBar>
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
//#include <QDebug>
#include <QSplashScreen>
#include <QTime>
#include <QTextStream>
#include <QHelpEvent>
#include <QSysInfo>
#include <iostream>
#include <fstream>
#include <cmath>
#include "glab_const.h"
#include "glab_tooltip.h"
#include "date_converter.h"
#include "coord_converter.h"
#include "snr_advanced.h"
#include "cs_sf_advanced.h"
#include "cs_mw_advanced.h"
#include "cs_li_advanced.h"
#include "cs_igf_advanced.h"
#include "antenna_advanced.h"
#include "sbas_obad_set.h"
#include "freqmeas_order.h"
#include "meas_select.h"
#include "multi_threading.h"

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
    ~ResizeFilter(); //Defined empty to avoid warning "'ResizeFilter' out-of-line virtual method definitions: its vtable will be emitted in every translation unit"
    bool eventFilter(QObject *object, QEvent *event) {
        if (event->type() == QEvent::Resize) {
            // The width of each tab is the width of the tab widget / # of tabs
        #ifdef Q_OS_MAC
            //In Mac. the tabs get resized too big (having to scroll horizontally).
            //This forces the tabs to be resized smaller, so they fit in the window
            target->setStyleSheet(QString("QTabBar::tab{height: 25px;width: %1px;}\
/*QTabBar::tab:selected{background-color:rgb(239, 235, 231);}\
QTabBar::tab:!selected{background-color:rgb(255, 255, 255);}*/").arg(target->size().width()/target->count()));
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
    explicit gLAB_GUI(QWidget *parent = nullptr);
    ~gLAB_GUI();
    double version;
    int revision;
    int StanfordPlotSelected;
    int StanfordESAPlotSelected;
    int mode; //0->SPP //1->PPP
    int v5Message;
    int WriteAllParameters;
    int abort;
    int SBASmaritime;
    int openP1P2;
    int lastRadioButtonClkFilterRandom=0, lastRadioButtonISCFilterRandom=0;
    QStringList configFileName;
    QStringList outputFileName;
    QString TitleColor;
    QString ISCBTrickColor;
    QString pushButtonOriColor;

    QBrush gnssUnSelected,gnssSelected,ISCBTitleSelected,ISCBTitleTrick,ISCBGNSSSelected;

    //global measurement option string
    int MeasOK=0; // flag of at least one measurement has been selected
    QString GNSSMeasAll[MAX_GNSS][3][2]; //GNSS measuerements of Code and Phase ( 0:comb1, 1:comb2, 2:comb3 ) (0: code, 1: phase)
    QString GNSSNoiseAll[MAX_GNSS][3][2]; //GNSS noise of Code and Phase ( 0:comb1, 1:comb2, 2:comb3 ) (0: code, 1: phase)
    QString GNSSNoiseModeAll[MAX_GNSS][3][2]; //GNSS noise mode of Code and Phase ( 0:comb1, 1:comb2, 2:comb3 ) (0: code, 1: phase)
    QString GNSSSmoothWithAll[MAX_GNSS][3]; //GNSS noise of Code and Phase ( 0:comb1, 1:comb2, 2:comb3 )
    QString GNSSMeasInAll[MAX_GNSS][3][3]; //GNSS measurements of Code and Phase inputted from config file ( 0:comb1, 1:comb2, 2:comb3 ) (0: code, 1: phase, 2: GC)
    int GNSSMeasCMD[MAX_GNSS][3]; //GNSS measurements command number of Code and Phase (0: code, 1: phase, 2: GC)
    int GNSSMeasNoiseCMD[MAX_GNSS][2]; //GNSS measurements noise command number of Code and Phase (0: code, 1: phase)
    int GNSSFreqCMDMode,GNSSMeasCMDMode,GNSSSmoothFlag;

    //This is a definition of a variable with a pointer to a function type "void" with no parameters for class gLAB_GUI
    typedef void (gLAB_GUI::*VoidNoParamFuncPointer)();
    typedef void (gLAB_GUI::*Void1IntFuncPointer)(int p1);
    //Declare array of pointers to on_pushButtons of PRN of GERSCJI _clicked() functions
    VoidNoParamFuncPointer PushButtonSatFunctions[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
    //Declare array of pointers to constellation on_pushButton functions
    VoidNoParamFuncPointer PushButtonSelectFunctions[MAX_GNSS];
    //Declare array of pointers to pushButtons of PRN of GERSCJI widgets
    QWidget *PushButtonSatWidgets[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
    //Declare array of pointers to pushButtons of constelations GERSCJI widgets
    QPushButton *PushButtonConstWidgets[MAX_GNSS];
    //This is a definition of a variable with a pointer to a function type "void" with bool parameters for class gLAB_GUI
    typedef void (gLAB_GUI::*VoidBoolParamFuncPointer)(bool checked);
    //Declare array of pointer to on_pushButtons of PRN of GERSCJI _clicked() functions
    VoidBoolParamFuncPointer CheckBoxGNSSFunctions[MAX_GNSS];
    //void (gLAB_GUI::*CheckBoxGNSSFunctions[MAX_GNSS])(bool);
    //Declare array of pointers to checkBox of GERSCJI widgets
    QCheckBox *CheckBoxGNSS[MAX_GNSS];
    //Declare array of pointers to checkBox of GERSCJI widgets for Reference GNSS Clock
    QCheckBox *CheckBoxGNSS4RefClock[MAX_GNSS];
    //Declare array of pointers to pushButton GNSS Measurements _clicked() functions
    VoidNoParamFuncPointer PushButtonGNSSMeasurementFunctions[MAX_GNSS];
    //Declare array of pointers to code and phase frequency labels ( 0:comb1, 1:comb2, 2:comb3 ) (0: code, 1: phase)
    QLabel *LabelCodePhaseFreq[MAX_GNSS][MAXMEASTOFILTER][MEASANDPHASENUMSLOTS];
    //Declare array of pointers to frame of GNSS frequency ( 0:comb1, 1:comb2, 2:comb3 )
    QFrame *FrameGNSSMeasComb[MAX_GNSS][MAXMEASTOFILTER];
    //Declare array of pointers to frame of GNSS frequency ( 0:comb1, 1:comb2, 2:comb3 ) (0: code, 1: phase, 2: GC)
    QFrame *FrameGNSSMeasFreq[MAX_GNSS][MAXMEASTOFILTER][MAXMEASTYPE];
    //Declare array of pointers to comboBox of GNSS frequency ( 0:comb1, 1:comb2, 2:comb3 ) (0: code, 1: phase, 2: GC)
    QComboBox *ComboBoxGNSSFreq[MAX_GNSS][MAXMEASTOFILTER][MAXMEASTYPE];
    //Declare array of pointers to comboBox of GNSS measurements ( 0:comb1, 1:comb2, 2:comb3 ) (0: code, 1: phase, 2: GC) ( 0:freq1, 1:freq2 )
    QComboBox *ComboBoxGNSSMeas[MAX_GNSS][MAXMEASTOFILTER][MAXMEASTYPE][MEASANDPHASENUMSLOTS];
    //Declare array of pointers to stdDev-type comboBox of GNSS ( 0:comb1, 1:comb2, 2:comb3 ) (0: code, 1: phase, 2: GC)
    QComboBox *ComboBoxstdDevType[MAX_GNSS][MAXMEASTOFILTER][MAXMEASTYPE];
    //Declare array of pointers to stdDev-value A&B&C of GNSS ( 0:comb1, 1:comb2, 2:comb3 ) (0: code, 1: phase, 2: GC) (weight terms: 0: A, 1:, B 2: C)
    QLineEdit *LineEditstdDevValue[MAX_GNSS][MAXMEASTOFILTER][MAXMEASTYPE][3];
    //Declare array of pointers to frame of GNSS smoothed-with measurement ( 0:comb1, 1:comb2, 2:comb3 ) (0: code, 1: phase)
    QFrame *FrameGNSSSmoothWith[MAX_GNSS][MAXMEASTOFILTER];
    //Declare array of pointers to comboBox of GNSS smoothed-with type ( 0:comb1, 1:comb2, 2:comb3 )
    QComboBox *ComboBoxSmoothWithTypeAll[MAX_GNSS][MAXMEASTOFILTER];
    //Delcare array of index of GNSS smoothed-with freq1 & freq2 ( 0:comb1, 1:comb2, 2:comb3 ) (0: freq1, 1: freq2)
    int smoothWithFreqIndexAll[MAX_GNSS][MAXMEASTOFILTER][2];
    //Declare array of pointers to comboBox of GNSS smoothed-with freq1 & freq2 ( 0:comb1, 1:comb2, 2:comb3 ) (0: freq1, 1: freq2)
    QComboBox *ComboBoxSmoothWithFreqAll[MAX_GNSS][MAXMEASTOFILTER][2];
    //Declare array of pointers to comboBox of GNSS smoothed-with measurements ( 0:comb1, 1:comb2, 2:comb3 ) (0: phase1, 1:code1, 2:phase2)
    QComboBox *ComboBoxSmoothWithMeasAll[MAX_GNSS][MAXMEASTOFILTER][3];
    //Declare array of pointers to clicked groupBox functions of GNSS DCB
    VoidBoolParamFuncPointer GroupBoxGNSSDCB[MAX_GNSS];
    //Declare array of pointers to comboBox of GNSS DCB
    QComboBox *ComboBoxGNSSDCB[MAX_GNSS][MAX_GNSS_FREQ];
    //Declare array of pointers to comboBox of GNSS ISC
    QComboBox *ComboBoxGNSSISC[MAX_GNSS][MAX_GNSS_FREQ];
    //Declare array of command line of GNSS DCB
    QString CommandGNSSDCB[MAX_GNSS][MAX_GNSS_FREQ];
    //Declare array of command line of GNSS ISC
    QString CommandGNSSISC[MAX_GNSS][MAX_GNSS_FREQ];

private slots:
    // Piece of header for common functions
    int showToolTipinQLineEdit(const QPoint &pos, const QString strTT, int tabflag);

    // Piece of header for glab_gui.cpp
    void setInitialPositioningValues();
    void setInitialConverterValues();
    void setInitialCompareOrbitValues();
    void setInitialShowOrbitValues();
    void setInitialAddUserErrorValues();
    void setInitialDCBISC();
    void setOSspecificObjectSizes();
    void setSPPDefault();
    void setPPPDefault();
    void setSBAS1FDefault();
    void setSBASDFMCDefault();
    void setDGNSSDefault();
    void on_actionSPP_triggered();
    void on_actionPPP_triggered();
    void on_actionSBAS_1F_triggered();
    void on_actionSBAS_DFMC_triggered();
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
    void extraArgumentsToWarningStr(int startPos, QString *warningString, QString option, QStringList ParametersList);
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
    void on_actionFAQ_triggered();
    void on_actionUser_Added_Error_File_Manual_triggered();
    void on_actionUser_defined_Sigma_Multipath_File_Manual_triggered();
    void on_actionReference_Position_File_Manual_triggered();
    void on_actiongLAB_command_line_help_triggered();
    void on_actiongLAB_command_line_messages_description_triggered();
    void on_actionGLAB_command_line_SBAS_maps_description_triggered();
    void on_actionGraph_plot_tool_command_line_help_triggered();
    void on_actionAboutgLAB_triggered();
    void on_actionContactUs_triggered();
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
    void on_actionEMS_files_triggered();
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
    void on_actionGeoscience_Australia_triggered();
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
    void on_actionGenerate_minimum_configuration_triggered(bool checked);
    void on_actionSet_Multi_threading_options_triggered();
    void on_actionPrint_messages_in_gLAB_v5_format_triggered(bool checked);
    void setCorrectSizes();
    void setSBASmodellingDefaults();
    void setCSdefaults();
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
    void on_checkBoxSatAntex_clicked(bool checked);
    void on_checkBoxRecAntex_clicked(bool checked);
    void on_comboBoxSbasInput_currentIndexChanged(int index);
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
    void on_pushButtonAddRinexNav_clicked();
    void on_pushButtonDelRinexNav_clicked();
    void on_pushButtonRinexNav1_clicked();
    void on_pushButtonRinexNav2_clicked();
    void on_pushButtonRinexNav3_clicked();
    void on_pushButtonRinexNav4_clicked();
    void on_pushButtonRinexNav5_clicked();
    void on_pushButtonRinexNav6_clicked();
    void on_pushButtonRinexNav7_clicked();
    void on_pushButtonPrecise1File_clicked();
    void on_checkBoxRinexNavFileGLO1_clicked(bool checked);
    void on_pushButtonRinexNavFileGLO1_clicked();
    void on_checkBoxRinexNavFileHealth1_clicked(bool checked);
    void on_pushButtonRinexNavFileHealth1_clicked();
    void on_pushButtonPrecise2Files_clicked();
    void on_pushButtonPreciseClk_clicked();
    void on_checkBoxRinexNavFileGLO2_clicked(bool checked);
    void on_pushButtonRinexNavFileGLO2_clicked();
    void on_checkBoxRinexNavFileHealth2_clicked(bool checked);
    void on_pushButtonRinexNavFileHealth2_clicked();
    void on_pushButtonSatAntex_clicked();
    void on_pushButtonRecAntex_clicked();
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
    void on_lineEditDcbFile_textChanged();
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
    void checkBoxInputSatANTEXFileMenu(const QPoint& pos);
    void checkBoxInputRecANTEXFileMenu(const QPoint& pos);
    void labelInputRinexNavFile1Menu(const QPoint& pos);
    void labelInputRinexNavFile2Menu(const QPoint& pos);
    void labelInputRinexNavFile3Menu(const QPoint& pos);
    void labelInputRinexNavFile4Menu(const QPoint& pos);
    void labelInputRinexNavFile5Menu(const QPoint& pos);
    void labelInputRinexNavFile6Menu(const QPoint& pos);
    void labelInputRinexNavFile7Menu(const QPoint& pos);
    void labelInputSP3OrbitsClocksFileMenu(const QPoint& pos);
    void labelInputSP3OrbitsFileMenu(const QPoint& pos);
    void labelInputClocksFileMenu(const QPoint& pos);
    void checkBoxRinexNavFileGLO1Menu(const QPoint& pos);
    void checkBoxRinexNavFileHealth1Menu(const QPoint& pos);
    void checkBoxRinexNavFileGLO2Menu(const QPoint& pos);
    void checkBoxRinexNavFileHealth2Menu(const QPoint& pos);
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
    void InitCheckBoxGNSSFuncPointers();
    void InitCheckBoxGNSSPointers();

    void on_checkBoxDataDecimator_clicked(bool checked);
    void on_checkBoxGPS_clicked(bool checked);
    void on_checkBoxGalileo_clicked(bool checked);
    void on_checkBoxGLONASS_clicked(bool checked);
    void on_checkBoxGEO_clicked(bool checked);
    void on_checkBoxBDS_clicked(bool checked);
    void on_checkBoxQZSS_clicked(bool checked);
    void on_checkBoxIRNSS_clicked(bool checked);
    void checkBoxGPS_ForOneSat();
    void checkBoxGalileo_ForOneSat();
    void checkBoxGLONASS_ForOneSat();
    void checkBoxGEO_ForOneSat();
    void checkBoxBDS_ForOneSat();
    void checkBoxQZSS_ForOneSat();
    void checkBoxIRNSS_ForOneSat();
    void on_pushButtonGPSSelect_clicked();
    void on_pushButtonGalileoSelect_clicked();
    void on_pushButtonGLONASSSelect_clicked();
    void on_pushButtonGEOSelect_clicked();
    void on_pushButtonBDSSelect_clicked();
    void on_pushButtonQZSSSelect_clicked();
    void on_pushButtonIRNSSSelect_clicked();
    void on_pushButtonSatSelAll_clicked();
    void on_pushButtonSatSelNone_clicked();
    //GPS
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
    //Galileo
    void on_pushButtonE1_clicked();
    void on_pushButtonE2_clicked();
    void on_pushButtonE3_clicked();
    void on_pushButtonE4_clicked();
    void on_pushButtonE5_clicked();
    void on_pushButtonE6_clicked();
    void on_pushButtonE7_clicked();
    void on_pushButtonE8_clicked();
    void on_pushButtonE9_clicked();
    void on_pushButtonE10_clicked();
    void on_pushButtonE11_clicked();
    void on_pushButtonE12_clicked();
    void on_pushButtonE13_clicked();
    void on_pushButtonE14_clicked();
    void on_pushButtonE15_clicked();
    void on_pushButtonE16_clicked();
    void on_pushButtonE17_clicked();
    void on_pushButtonE18_clicked();
    void on_pushButtonE19_clicked();
    void on_pushButtonE20_clicked();
    void on_pushButtonE21_clicked();
    void on_pushButtonE22_clicked();
    void on_pushButtonE23_clicked();
    void on_pushButtonE24_clicked();
    void on_pushButtonE25_clicked();
    void on_pushButtonE26_clicked();
    void on_pushButtonE27_clicked();
    void on_pushButtonE28_clicked();
    void on_pushButtonE29_clicked();
    void on_pushButtonE30_clicked();
    void on_pushButtonE31_clicked();
    void on_pushButtonE32_clicked();
    void on_pushButtonE33_clicked();
    void on_pushButtonE34_clicked();
    void on_pushButtonE35_clicked();
    void on_pushButtonE36_clicked();
    //GLONASS
    void on_pushButtonR1_clicked();
    void on_pushButtonR2_clicked();
    void on_pushButtonR3_clicked();
    void on_pushButtonR4_clicked();
    void on_pushButtonR5_clicked();
    void on_pushButtonR6_clicked();
    void on_pushButtonR7_clicked();
    void on_pushButtonR8_clicked();
    void on_pushButtonR9_clicked();
    void on_pushButtonR10_clicked();
    void on_pushButtonR11_clicked();
    void on_pushButtonR12_clicked();
    void on_pushButtonR13_clicked();
    void on_pushButtonR14_clicked();
    void on_pushButtonR15_clicked();
    void on_pushButtonR16_clicked();
    void on_pushButtonR17_clicked();
    void on_pushButtonR18_clicked();
    void on_pushButtonR19_clicked();
    void on_pushButtonR20_clicked();
    void on_pushButtonR21_clicked();
    void on_pushButtonR22_clicked();
    void on_pushButtonR23_clicked();
    void on_pushButtonR24_clicked();
    void on_pushButtonR25_clicked();
    void on_pushButtonR26_clicked();
    void on_pushButtonR27_clicked();
    void on_pushButtonR28_clicked();
    void on_pushButtonR29_clicked();
    void on_pushButtonR30_clicked();
    void on_pushButtonR31_clicked();
    void on_pushButtonR32_clicked();
    //GEO
    void on_pushButtonS120_clicked();
    void on_pushButtonS121_clicked();
    void on_pushButtonS122_clicked();
    void on_pushButtonS123_clicked();
    void on_pushButtonS124_clicked();
    void on_pushButtonS125_clicked();
    void on_pushButtonS126_clicked();
    void on_pushButtonS127_clicked();
    void on_pushButtonS128_clicked();
    void on_pushButtonS129_clicked();
    void on_pushButtonS130_clicked();
    void on_pushButtonS131_clicked();
    void on_pushButtonS132_clicked();
    void on_pushButtonS133_clicked();
    void on_pushButtonS134_clicked();
    void on_pushButtonS135_clicked();
    void on_pushButtonS136_clicked();
    void on_pushButtonS137_clicked();
    void on_pushButtonS138_clicked();
    void on_pushButtonS139_clicked();
    void on_pushButtonS140_clicked();
    void on_pushButtonS141_clicked();
    void on_pushButtonS142_clicked();
    void on_pushButtonS143_clicked();
    void on_pushButtonS144_clicked();
    void on_pushButtonS145_clicked();
    void on_pushButtonS146_clicked();
    void on_pushButtonS147_clicked();
    void on_pushButtonS148_clicked();
    void on_pushButtonS149_clicked();
    void on_pushButtonS150_clicked();
    void on_pushButtonS151_clicked();
    void on_pushButtonS152_clicked();
    void on_pushButtonS153_clicked();
    void on_pushButtonS154_clicked();
    void on_pushButtonS155_clicked();
    void on_pushButtonS156_clicked();
    void on_pushButtonS157_clicked();
    void on_pushButtonS158_clicked();
    //BDS
    void on_pushButtonC1_clicked();
    void on_pushButtonC2_clicked();
    void on_pushButtonC3_clicked();
    void on_pushButtonC4_clicked();
    void on_pushButtonC5_clicked();
    void on_pushButtonC6_clicked();
    void on_pushButtonC7_clicked();
    void on_pushButtonC8_clicked();
    void on_pushButtonC9_clicked();
    void on_pushButtonC10_clicked();
    void on_pushButtonC11_clicked();
    void on_pushButtonC12_clicked();
    void on_pushButtonC13_clicked();
    void on_pushButtonC14_clicked();
    void on_pushButtonC15_clicked();
    void on_pushButtonC16_clicked();
    void on_pushButtonC17_clicked();
    void on_pushButtonC18_clicked();
    void on_pushButtonC19_clicked();
    void on_pushButtonC20_clicked();
    void on_pushButtonC21_clicked();
    void on_pushButtonC22_clicked();
    void on_pushButtonC23_clicked();
    void on_pushButtonC24_clicked();
    void on_pushButtonC25_clicked();
    void on_pushButtonC26_clicked();
    void on_pushButtonC27_clicked();
    void on_pushButtonC28_clicked();
    void on_pushButtonC29_clicked();
    void on_pushButtonC30_clicked();
    void on_pushButtonC31_clicked();
    void on_pushButtonC32_clicked();
    void on_pushButtonC33_clicked();
    void on_pushButtonC34_clicked();
    void on_pushButtonC35_clicked();
    void on_pushButtonC36_clicked();
    void on_pushButtonC37_clicked();
    void on_pushButtonC38_clicked();
    void on_pushButtonC39_clicked();
    void on_pushButtonC40_clicked();
    void on_pushButtonC41_clicked();
    void on_pushButtonC42_clicked();
    void on_pushButtonC43_clicked();
    void on_pushButtonC44_clicked();
    void on_pushButtonC45_clicked();
    void on_pushButtonC46_clicked();
    void on_pushButtonC47_clicked();
    void on_pushButtonC48_clicked();
    void on_pushButtonC49_clicked();
    void on_pushButtonC50_clicked();
    void on_pushButtonC51_clicked();
    void on_pushButtonC52_clicked();
    void on_pushButtonC53_clicked();
    void on_pushButtonC54_clicked();
    void on_pushButtonC55_clicked();
    void on_pushButtonC56_clicked();
    void on_pushButtonC57_clicked();
    void on_pushButtonC58_clicked();
    void on_pushButtonC59_clicked();
    void on_pushButtonC60_clicked();
    void on_pushButtonC61_clicked();
    void on_pushButtonC62_clicked();
    void on_pushButtonC63_clicked();
    //QZSS
    void on_pushButtonJ1_clicked();
    void on_pushButtonJ2_clicked();
    void on_pushButtonJ3_clicked();
    void on_pushButtonJ4_clicked();
    void on_pushButtonJ5_clicked();
    void on_pushButtonJ6_clicked();
    void on_pushButtonJ7_clicked();
    void on_pushButtonJ8_clicked();
    void on_pushButtonJ9_clicked();
    void on_pushButtonJ10_clicked();
    //IRNSS
    void on_pushButtonI1_clicked();
    void on_pushButtonI2_clicked();
    void on_pushButtonI3_clicked();
    void on_pushButtonI4_clicked();
    void on_pushButtonI5_clicked();
    void on_pushButtonI6_clicked();
    void on_pushButtonI7_clicked();
    void on_pushButtonI8_clicked();
    void on_pushButtonI9_clicked();
    void on_pushButtonI10_clicked();
    void on_pushButtonI11_clicked();
    void on_pushButtonI12_clicked();
    void on_pushButtonI13_clicked();
    void on_pushButtonI14_clicked();
    void callSatellitePushButtonFunction(enum GNSSystem System, int PRN, QString Sign);
    void on_checkBoxNcon_clicked(bool checked);
    void on_checkBoxSNRMinAdvancedMode_clicked(bool checked);
    void on_checkBoxSNRMaxAdvancedMode_clicked(bool checked);
    void on_pushButtonSNRMinAdvancedMode_clicked();
    void on_pushButtonSNRMaxAdvancedMode_clicked();
    void on_checkBoxSNRThresholdMin_clicked(bool checked);
    void on_checkBoxSNRThresholdMax_clicked(bool checked);
    void on_comboBoxSNRThresholdsMin_currentIndexChanged(int index);
    void on_comboBoxSNRThresholdsMax_currentIndexChanged(int index);
    void on_checkBoxDiscardUnhealthy_clicked(bool checked);
    void on_checkBoxDiscardMarginal_clicked(bool checked);
    void on_pushButtonConfigureSF_clicked();
    void on_checkBoxSFConsistencyCheck_clicked(bool checked);
    void on_radioButtonSFAutoSelection_clicked();
    void on_radioButtonSFManualSelection_clicked();
    void on_pushButtonSFSelectMeasurements_clicked();
    void on_pushButtonConfigureMW_clicked();
    void on_radioButtonMWAutoSelection_clicked();
    void on_radioButtonMWManualSelection_clicked();
    void on_pushButtonMWSelectMeasurements_clicked();
    void on_pushButtonConfigureLI_clicked();
    void on_radioButtonLIAutoSelection_clicked();
    void on_radioButtonLIManualSelection_clicked();
    void on_pushButtonLISelectMeasurements_clicked();
    void on_pushButtonConfigureIGF_clicked();
    void on_radioButtonIGFMinimumNoise_clicked();
    void on_radioButtonIGFTwoIonoFree_clicked();
    void on_radioButtonIGFAutoSelection_clicked();
    void on_radioButtonIGFManualSelection_clicked();
    void on_pushButtonIGFSelectMeasurements_clicked();
    void loadSNRvalue(QString *warningString, QStringList *ParametersList, int SNRtype);
    void loadgLABSatelliteList(QString option, QString *warningString, QStringList *ParametersList);
    void checkMinMaxSNRThresholds(QString *errorString);
    void getPreprocessOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);

    // Header for modelling.cpp
    void on_checkBoxIonoCorrection_clicked(bool checked);
    void on_checkBoxTropoCorrection_clicked(bool checked);
    void on_checkBoxAntennaPhase_clicked(bool checked);
    void on_checkBoxSatMassCentre_clicked(bool checked);
    void on_checkBoxAntennaReference_clicked(bool checked);
    void on_groupBoxConcatenedPreciseFiles_clicked(bool checked);
    void on_radioButtonAPCread_clicked();
    void on_radioButtonAPCspecify_clicked();
    void on_pushButtonAPCAdvanced_clicked();
    void on_radioButtonARPread_clicked();
    void on_radioButtonARPspecify_clicked();
    void on_comboBoxIonoCorrection_currentIndexChanged(int index);
    void on_comboBoxDCBsfP1P2GPS_currentIndexChanged(int index);
    void on_comboBoxDCBsfP1C1GPS_currentIndexChanged(int index);

    void on_groupBoxShowDCBOptions_clicked(bool checked);
    void on_groupBoxShowDCBOptionsGPS_clicked(bool checked);
    void on_groupBoxShowDCBOptionsGalileo_clicked(bool checked);
    void on_groupBoxShowDCBOptionsGLONASS_clicked(bool checked);
    void on_groupBoxShowDCBOptionsBDS_clicked(bool checked);
    void on_groupBoxShowDCBOptionsQZSS_clicked(bool checked);
    void on_groupBoxShowDCBOptionsIRNSS_clicked(bool checked);

    void userNavMessageTypes_2_Command(QString *saveString, QStringList *runString, QString *errorString);
    void command_2_UserNavMessageTypes(QString const *navMessageTypesCmd,QString const *navMessageTypesOption,QString *warningString, int userCommand);
    void selectGNSS_NavMessageTypes(int selectFlag,int iGNSS);
    void navMessageTypesItem_doubleClicked(QTableWidgetItem *tableItem);
    void moveNavMessageTypesColumn(QTableWidget *pTable, int currentColumn, int toColumn, int doubleClickFlag);
    void on_pushButtonNavMessageTypesSetDefault_clicked();
    void on_pushButtonNavMessageTypesBoost_clicked();
    void on_pushButtonNavMessageTypesLower_clicked();
    void on_tableWidgetNavMessageTypeGPS_clicked();
    void on_tableWidgetNavMessageTypeGalileo_clicked();
    void on_tableWidgetNavMessageTypeGLONASS_clicked();
    void on_tableWidgetNavMessageTypeGEO_clicked();
    void on_tableWidgetNavMessageTypeBDS_clicked();
    void on_tableWidgetNavMessageTypeQZSS_clicked();
    void on_tableWidgetNavMessageTypeIRNSS_clicked();

    void change_comboBoxSBASApplication(int SBASFlag);
    void on_comboBoxSBASApplication_currentIndexChanged(int index);
    void on_comboBoxSbasNavigationMode_currentIndexChanged(int index);
    void on_checkBoxNavigationModeSwitching_clicked(bool checked);
    void on_comboBoxGEOselection_currentIndexChanged(int index);
    void on_groupBoxSbasAdvancedOptions_clicked(bool checked);
    void on_checkBoxParseAlarmSBAS1F_clicked(bool checked);
    void on_checkBoxParseAlarmSBASDFMC_clicked(bool checked);
    void on_checkBoxGEOexclusion_clicked(bool checked);
    void on_comboBoxGEOexclusion_currentIndexChanged(int index);
    void on_checkBoxGEOswitching_clicked(bool checked);
    void on_checkBoxSelectBestGEO_clicked(bool checked);
    void on_checkBoxUserDefinedReceiverSigmaMultipathModel_clicked(bool checked);
    void on_groupBoxUserDefinedReceiverSigma_clicked(bool checked);
    void on_checkBoxUserDefinedReceiverSigmaMultipath_clicked(bool checked);
    void on_checkBoxSigmaMultiPathFactor_clicked(bool checked);
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
    void on_groupBoxSetOBADParameters_clicked(bool checked);
    void on_groupBoxSetDFREICorrections_clicked(bool checked);
    void on_groupBoxSetSepcificSigmas_clicked(bool checked);
    void on_groupBoxShowOldMessages_clicked(bool checked);
    void on_comboBoxTropoCorrection_currentIndexChanged(int index);
    void on_checkBoxDisableFastCorrections_clicked(bool checked);
    void on_checkBoxDisableFastCorrectionsSigma_clicked(bool checked);
    void on_checkBoxSetCerOBADParameterMT37_clicked(bool checked);
    void on_checkBoxSetCcovarianceOBADParameterMT37_clicked(bool checked);
    void on_checkBoxSetIcorrOBADParameterMT37_clicked(bool checked);
    void on_checkBoxSetIcorrOBADParameterMT37Advanced_clicked(bool checked);
    void on_checkBoxSetCcorrOBADParameterMT37_clicked(bool checked);
    void on_checkBoxSetCcorrOBADParameterMT37Advanced_clicked(bool checked);
    void on_checkBoxSetRcorrOBADParameterMT37_clicked(bool checked);
    void on_checkBoxSetRcorrOBADParameterMT37Advanced_clicked(bool checked);
    void on_checkBoxSetOneDFREISigmaConversionValue_clicked(bool checked);
    void on_checkBoxSetAllDFREIConversionValues_clicked(bool checked);
    void on_checkBoxSetDeltaRcorrParameter_clicked(bool checked);
    void on_checkBoxSetDeltaDFREFactor_clicked(bool checked);
    void on_checkBoxSetUIRESigmaValue_clicked(bool checked);
    void on_checkBoxSetTroposphericSigma_clicked(bool checked);
    void on_pushButtonSetIcorrOBADParameterMT37Advanced_clicked();
    void on_pushButtonSetCcorrOBADParameterMT37Advanced_clicked();
    void on_pushButtonSetRcorrOBADParameterMT37Advanced_clicked();
    void on_checkBoxDecodeMT37_clicked(bool checked);
    void on_checkBoxDecodeMT3940_clicked(bool checked);
    void on_checkBoxDecodeMT42_clicked(bool checked);
    void on_checkBoxDecodeMT47_clicked(bool checked);
    void on_checkBoxProcessAustralianTestBedMessages_clicked(bool checked);
    void showHidePAtimeouts(bool hide);
    void showHideNPAtimeouts(bool hide);
    void readSBASM1FTandTimeout(int MT, int timeout, int type, QString option, QString *warningString);
    void readSBASDFMCMTandTimeout(int MT, int timeout, int type, QString option, QString *warningString);
    void getModellingOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);

    // Header for filter.cpp
    void InitFilterWeights();
    void setWeightTypeValues(enum GNSSystem GNSS, int comb, int measType, int index);
    void InitRefGNSSClock();
    void InitPushButtonGNSSMeasurementFuncPointers();
    void InitGNSSFreqLabels();
    void InitGNSSFreqMeasComboBoxPointers();
    void InitSmoothComboBoxPointers();
    void InitGNSSStdDevPointers();

    void on_radioButtonSmoothing_clicked();
    void on_checkBoxExcludeDuringSmoothingConvergenceUser_clicked(bool checked);
    void on_checkBoxExcludeDuringSmoothingConvergenceRef_clicked(bool checked);
    void on_radioButtonSingleFreq_clicked();
    void on_radioButtonDualFreq_clicked();
    void on_radioButtonSelectionPseudorange_clicked();
    void on_radioButtonSelectionPseudorangeCarrierPhase_clicked();
    void on_radioButtonSelectionGraphic_clicked();

    void on_pushButtonMeasGNSSAdd_clicked();
    void on_pushButtonMeasGNSSDelete_clicked();

    void on_pushButtonGPSMeasurements_clicked();
    void on_pushButtonGalileoMeasurements_clicked();
    void on_pushButtonGLONASSMeasurements_clicked();
    void on_pushButtonGEOMeasurements_clicked();
    void on_pushButtonBDSMeasurements_clicked();
    void on_pushButtonQZSSMeasurements_clicked();
    void on_pushButtonIRNSSMeasurements_clicked();

    void on_checkBoxSetFreqMeasOrderGNSS_clicked(bool checked);
    void on_pushButtonSetFreqMeasOrderGNSS_clicked();

    void initGNSSMeasAll();
    void setGNSSMeasurementFreqAll(int iGNSS,int icomb,int ifreq);
    void setGNSSMeasurementFreqCP(int iGNSS,int icomb,int iCP,int ifreq);
    void setGNSSMeasurementMeasAll(int iGNSS,int icomb,int iCP,int ifreq);
    void setSmoothWithFreqComboBoxValue(int iGNSS,int icomb,int ifreq1,int ifreq2);
    void setSmoothWithMeasComboBoxValue(int iGNSS,int icomb,int ifreq1,int ifreq2);
    void setSmoothWithFreqAll(int iGNSS,int icomb,int SmoothType);
    int  meas_has_code(QString meas);
    void checkSmoothFilterMeasInFilterMeas(QString *warningString, QStringList *ParametersList);
    int  checkUserInputFilterMeasurement (QString *warningString, QString param,enum MeasTargetUsage type);
    void readGNSSSmoothFreqMeas(QString *warningString, QStringList *ParametersList);
    void readGNSSFreqMeas(QString *warningString, QStringList *ParametersList);
    void readGNSSStdDev(QString *warningString, QStringList *ParametersList, const int stdDevType);

    //GPS
    //new
    void on_comboBoxFreqCodeGPS_1_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseGPS_1_currentIndexChanged(int index);
    void on_comboBoxFreqGCGPS_1_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1GPS_1_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2GPS_1_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1GPS_1_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2GPS_1_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeGPS_1_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseGPS_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeGPS_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseGPS_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCGPS_1_currentIndexChanged(int index);
    void on_comboBoxFreqCodeGPS_2_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseGPS_2_currentIndexChanged(int index);
    void on_comboBoxFreqGCGPS_2_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1GPS_2_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2GPS_2_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1GPS_2_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2GPS_2_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeGPS_2_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseGPS_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeGPS_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseGPS_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCGPS_2_currentIndexChanged(int index);
    void on_comboBoxFreqCodeGPS_3_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseGPS_3_currentIndexChanged(int index);
    void on_comboBoxFreqGCGPS_3_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1GPS_3_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2GPS_3_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1GPS_3_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2GPS_3_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeGPS_3_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseGPS_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeGPS_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseGPS_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCGPS_3_currentIndexChanged(int index);
    //Smooth
    void on_comboBoxSmoothWithGPS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothWithGPS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothWithGPS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1GPS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2GPS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1GPS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2GPS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1GPS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2GPS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1GPS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1GPS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2GPS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1GPS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1GPS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2GPS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1GPS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1GPS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2GPS_3_currentIndexChanged(int index);

    //Galileo
    //new
    void on_comboBoxFreqCodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseGalileo_1_currentIndexChanged(int index);
    void on_comboBoxFreqGCGalileo_1_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1Galileo_1_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2Galileo_1_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1Galileo_1_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2Galileo_1_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseGalileo_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseGalileo_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCGalileo_1_currentIndexChanged(int index);
    void on_comboBoxFreqCodeGalileo_2_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseGalileo_2_currentIndexChanged(int index);
    void on_comboBoxFreqGCGalileo_2_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1Galileo_2_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2Galileo_2_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1Galileo_2_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2Galileo_2_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeGalileo_2_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseGalileo_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeGalileo_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseGalileo_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCGalileo_2_currentIndexChanged(int index);
    void on_comboBoxFreqCodeGalileo_3_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseGalileo_3_currentIndexChanged(int index);
    void on_comboBoxFreqGCGalileo_3_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1Galileo_3_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2Galileo_3_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1Galileo_3_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2Galileo_3_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeGalileo_3_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseGalileo_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeGalileo_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseGalileo_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCGalileo_3_currentIndexChanged(int index);
    //Smooth
    void on_comboBoxSmoothWithGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSmoothWithGalileo_2_currentIndexChanged(int index);
    void on_comboBoxSmoothWithGalileo_3_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1Galileo_1_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2Galileo_1_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1Galileo_2_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2Galileo_2_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1Galileo_3_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2Galileo_3_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1Galileo_1_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1Galileo_1_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2Galileo_1_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1Galileo_2_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1Galileo_2_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2Galileo_2_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1Galileo_3_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1Galileo_3_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2Galileo_3_currentIndexChanged(int index);

    //GLONASS
    //new
    void on_comboBoxFreqCodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxFreqGCGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1GLONASS_1_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2GLONASS_1_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1GLONASS_1_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2GLONASS_1_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxFreqCodeGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxFreqGCGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1GLONASS_2_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2GLONASS_2_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1GLONASS_2_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2GLONASS_2_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxFreqCodeGLONASS_3_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseGLONASS_3_currentIndexChanged(int index);
    void on_comboBoxFreqGCGLONASS_3_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1GLONASS_3_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2GLONASS_3_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1GLONASS_3_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2GLONASS_3_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeGLONASS_3_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseGLONASS_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeGLONASS_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseGLONASS_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCGLONASS_3_currentIndexChanged(int index);
    //Smooth
    void on_comboBoxSmoothWithGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothWithGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothWithGLONASS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1GLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2GLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1GLONASS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2GLONASS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1GLONASS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2GLONASS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1GLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1GLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2GLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1GLONASS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1GLONASS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2GLONASS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1GLONASS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1GLONASS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2GLONASS_3_currentIndexChanged(int index);

    //GEO
    //new
    void on_comboBoxFreqCodeGEO_1_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseGEO_1_currentIndexChanged(int index);
    void on_comboBoxFreqGCGEO_1_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1GEO_1_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2GEO_1_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1GEO_1_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2GEO_1_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeGEO_1_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseGEO_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeGEO_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseGEO_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCGEO_1_currentIndexChanged(int index);
    void on_comboBoxFreqCodeGEO_2_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseGEO_2_currentIndexChanged(int index);
    void on_comboBoxFreqGCGEO_2_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1GEO_2_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2GEO_2_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1GEO_2_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2GEO_2_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeGEO_2_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseGEO_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeGEO_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseGEO_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCGEO_2_currentIndexChanged(int index);
    void on_comboBoxFreqCodeGEO_3_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseGEO_3_currentIndexChanged(int index);
    void on_comboBoxFreqGCGEO_3_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1GEO_3_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2GEO_3_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1GEO_3_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2GEO_3_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeGEO_3_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseGEO_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeGEO_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseGEO_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCGEO_3_currentIndexChanged(int index);
    //Smooth
    void on_comboBoxSmoothWithGEO_1_currentIndexChanged(int index);
    void on_comboBoxSmoothWithGEO_2_currentIndexChanged(int index);
    void on_comboBoxSmoothWithGEO_3_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1GEO_1_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2GEO_1_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1GEO_2_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2GEO_2_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1GEO_3_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2GEO_3_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1GEO_1_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1GEO_1_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2GEO_1_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1GEO_2_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1GEO_2_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2GEO_2_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1GEO_3_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1GEO_3_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2GEO_3_currentIndexChanged(int index);

    //BDS
    //new
    void on_comboBoxFreqCodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseBDS_1_currentIndexChanged(int index);
    void on_comboBoxFreqGCBDS_1_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1BDS_1_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2BDS_1_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1BDS_1_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2BDS_1_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseBDS_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseBDS_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCBDS_1_currentIndexChanged(int index);
    void on_comboBoxFreqCodeBDS_2_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseBDS_2_currentIndexChanged(int index);
    void on_comboBoxFreqGCBDS_2_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1BDS_2_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2BDS_2_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1BDS_2_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2BDS_2_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeBDS_2_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseBDS_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeBDS_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseBDS_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCBDS_2_currentIndexChanged(int index);
    void on_comboBoxFreqCodeBDS_3_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseBDS_3_currentIndexChanged(int index);
    void on_comboBoxFreqGCBDS_3_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1BDS_3_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2BDS_3_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1BDS_3_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2BDS_3_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeBDS_3_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseBDS_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeBDS_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseBDS_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCBDS_3_currentIndexChanged(int index);
    //Smooth
    void on_comboBoxSmoothWithBDS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothWithBDS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothWithBDS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1BDS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2BDS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1BDS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2BDS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1BDS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2BDS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1BDS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1BDS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2BDS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1BDS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1BDS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2BDS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1BDS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1BDS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2BDS_3_currentIndexChanged(int index);

    //QZSS
    //new
    void on_comboBoxFreqCodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseQZSS_1_currentIndexChanged(int index);
    void on_comboBoxFreqGCQZSS_1_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1QZSS_1_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2QZSS_1_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1QZSS_1_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2QZSS_1_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseQZSS_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseQZSS_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCQZSS_1_currentIndexChanged(int index);
    void on_comboBoxFreqCodeQZSS_2_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseQZSS_2_currentIndexChanged(int index);
    void on_comboBoxFreqGCQZSS_2_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1QZSS_2_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2QZSS_2_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1QZSS_2_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2QZSS_2_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeQZSS_2_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseQZSS_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeQZSS_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseQZSS_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCQZSS_2_currentIndexChanged(int index);
    void on_comboBoxFreqCodeQZSS_3_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseQZSS_3_currentIndexChanged(int index);
    void on_comboBoxFreqGCQZSS_3_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1QZSS_3_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2QZSS_3_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1QZSS_3_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2QZSS_3_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeQZSS_3_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseQZSS_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeQZSS_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseQZSS_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCQZSS_3_currentIndexChanged(int index);
    //Smooth
    void on_comboBoxSmoothWithQZSS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothWithQZSS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothWithQZSS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1QZSS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2QZSS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1QZSS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2QZSS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1QZSS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2QZSS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1QZSS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1QZSS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2QZSS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1QZSS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1QZSS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2QZSS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1QZSS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1QZSS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2QZSS_3_currentIndexChanged(int index);

    //IRNSS
    //new
    void on_comboBoxFreqCodeIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxFreqGCIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1IRNSS_1_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2IRNSS_1_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1IRNSS_1_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2IRNSS_1_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxFreqCodeIRNSS_2_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseIRNSS_2_currentIndexChanged(int index);
    void on_comboBoxFreqGCIRNSS_2_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1IRNSS_2_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2IRNSS_2_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1IRNSS_2_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2IRNSS_2_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeIRNSS_2_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseIRNSS_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeIRNSS_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseIRNSS_2_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCIRNSS_2_currentIndexChanged(int index);
    void on_comboBoxFreqCodeIRNSS_3_currentIndexChanged(int index);
    void on_comboBoxFreqPhaseIRNSS_3_currentIndexChanged(int index);
    void on_comboBoxFreqGCIRNSS_3_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq1IRNSS_3_currentIndexChanged(int index);
    void on_comboBoxMeasCodeFreq2IRNSS_3_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq1IRNSS_3_currentIndexChanged(int index);
    void on_comboBoxMeasPhaseFreq2IRNSS_3_currentIndexChanged(int index);
    void on_comboBoxMeasGCCodeIRNSS_3_currentIndexChanged(int index);
    void on_comboBoxMeasGCPhaseIRNSS_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModeCodeIRNSS_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModePhaseIRNSS_3_currentIndexChanged(int index);
    void on_comboBoxStdDevModeGCIRNSS_3_currentIndexChanged(int index);
    //Smooth
    void on_comboBoxSmoothWithIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothWithIRNSS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothWithIRNSS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1IRNSS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2IRNSS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1IRNSS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2IRNSS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq1IRNSS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothFreq2IRNSS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1IRNSS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1IRNSS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2IRNSS_1_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1IRNSS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1IRNSS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2IRNSS_2_currentIndexChanged(int index);
    void on_comboBoxSmoothCode1IRNSS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase1IRNSS_3_currentIndexChanged(int index);
    void on_comboBoxSmoothPhase2IRNSS_3_currentIndexChanged(int index);

    void on_checkBoxEstimateTroposphere_clicked(bool checked);
    void on_checkBoxMaxHDOP_clicked(bool checked);
    void on_checkBoxMaxPDOP_clicked(bool checked);
    void on_checkBoxMaxGDOP_clicked(bool checked);
    void on_checkBoxPrefitOutliers_clicked(bool checked);
    void getFilterOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);
    void on_radioButtonStatic_clicked();
    void on_radioButtonKinematic_clicked();
    void on_radioButtonRandomwalkCoordinates_clicked();
    void on_radioButtonConstantClock_clicked();
    void on_radioButtonWhiteNoiseClock_clicked();
    void on_radioButtonRandomwalkClock_clicked();
    void on_radioButtonConstantISCB_clicked();
    void on_radioButtonWhiteNoiseISCB_clicked();
    void on_radioButtonRandomwalkISCB_clicked();
    void on_comboBoxPoClockUnit_currentIndexChanged(int index);
    void on_comboBoxPoISCBUnit_currentIndexChanged(int index);
    void on_comboBoxQClockUnitNormal_currentIndexChanged(int index);
    void on_comboBoxQISCBUnitNormal_currentIndexChanged(int index);
    void on_comboBoxQClockUnitRandom_currentIndexChanged(int index);
    void on_comboBoxQISCBUnitRandom_currentIndexChanged(int index);

    void on_groupBoxRefGNSSClock_clicked(bool checked);
    void userRefGNSSClock_2_Command(QString const *userRefGNSSClock,QString *refGNSSClockCmd);
    void command_2_UserRefGNSSClock(QString const *refGNSSClockCmd,QString *userRefGNSSClock,int *nRefGNSSClockCount, QString *warningString);
    void doubleClick_RefGNSSClock(int selectFlag,QString sGNSS);
    void refClockItem_doubleClicked(QTableWidgetItem *tableItem);
    void moveReferenceGNSSColumn(QTableWidget *pTable, int currentColumn, int toColumn, int doubleClickFlag);
    void on_pushButtonRefGNSSClockSetDefault_clicked();
    void on_pushButtonRefGNSSClockBoost_clicked();
    void on_pushButtonRefGNSSClockLower_clicked();
    void on_pushButtonRefGNSSClockSelectAll_clicked();
    void on_pushButtonRefGNSSClockUnselectAll_clicked();
    void on_groupBoxISCB_clicked(bool checked);
    void ISCBItem_textChanged(QTableWidgetItem *tableItem);
    void on_pushButtonISCBEstimateSelected_clicked();
    void on_pushButtonISCBEstimateAll_clicked();
    void select_ISCBGNSS(int selectFlag,QString sGNSS);

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
    void on_checkBoxPrintMeas_clicked(bool checked);
    void on_radioButtonMeasSelectAuto_clicked();
    void on_radioButtonMeasSelectSpecify_clicked();
    void on_pushButtonMeasSelectSpecify_clicked();
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
    void on_comboBoxPlot1ConditionGNSS_currentIndexChanged(int index);
    void on_comboBoxPlot1ConditionGPS_currentIndexChanged(int index);
    void on_comboBoxPlot1ConditionGalileo_currentIndexChanged(int index);
    void on_comboBoxPlot1ConditionGLONASS_currentIndexChanged(int index);
    void on_comboBoxPlot1ConditionGEO_currentIndexChanged(int index);
    void on_comboBoxPlot1ConditionBDS_currentIndexChanged(int index);
    void on_comboBoxPlot1ConditionQZSS_currentIndexChanged(int index);
    void on_comboBoxPlot1ConditionIRNSS_currentIndexChanged(int index);
    void on_comboBoxPlot1ConditionOutput_currentIndexChanged(int index);
    void on_pushButtonPlot1SourceFile_clicked();
    void on_lineEditPlot1SourceFile_textChanged();
    void on_lineEditPlot1Xcolumn_textChanged();
    void change_comboBoxPlot1Xcolumn_message(int messageType);
    void on_comboBoxPlot1Xcolumn_currentIndexChanged(int index);
    void on_lineEditPlot1Ycolumn_textChanged();
    void change_comboBoxPlot1Ycolumn_message(int messageType);
    void on_comboBoxPlot1Ycolumn_currentIndexChanged(int index);
    // Plot Nr 2
    void on_comboBoxPlot2Condition_currentIndexChanged(int index);
    void on_comboBoxPlot2ConditionGNSS_currentIndexChanged(int index);
    void on_comboBoxPlot2ConditionGPS_currentIndexChanged(int index);
    void on_comboBoxPlot2ConditionGalileo_currentIndexChanged(int index);
    void on_comboBoxPlot2ConditionGLONASS_currentIndexChanged(int index);
    void on_comboBoxPlot2ConditionGEO_currentIndexChanged(int index);
    void on_comboBoxPlot2ConditionBDS_currentIndexChanged(int index);
    void on_comboBoxPlot2ConditionQZSS_currentIndexChanged(int index);
    void on_comboBoxPlot2ConditionIRNSS_currentIndexChanged(int index);
    void on_comboBoxPlot2ConditionOutput_currentIndexChanged(int index);
    void on_pushButtonPlot2SourceFile_clicked();
    void on_lineEditPlot2SourceFile_textChanged();
    void on_lineEditPlot2Xcolumn_textChanged();
    void change_comboBoxPlot2Xcolumn_message(int messageType);
    void on_comboBoxPlot2Xcolumn_currentIndexChanged(int index);
    void on_lineEditPlot2Ycolumn_textChanged();
    void change_comboBoxPlot2Ycolumn_message(int messageType);
    void on_comboBoxPlot2Ycolumn_currentIndexChanged(int index);
    // Plot Nr 3
    void on_comboBoxPlot3Condition_currentIndexChanged(int index);
    void on_comboBoxPlot3ConditionGNSS_currentIndexChanged(int index);
    void on_comboBoxPlot3ConditionGPS_currentIndexChanged(int index);
    void on_comboBoxPlot3ConditionGalileo_currentIndexChanged(int index);
    void on_comboBoxPlot3ConditionGLONASS_currentIndexChanged(int index);
    void on_comboBoxPlot3ConditionGEO_currentIndexChanged(int index);
    void on_comboBoxPlot3ConditionBDS_currentIndexChanged(int index);
    void on_comboBoxPlot3ConditionQZSS_currentIndexChanged(int index);
    void on_comboBoxPlot3ConditionIRNSS_currentIndexChanged(int index);
    void on_comboBoxPlot3ConditionOutput_currentIndexChanged(int index);
    void on_pushButtonPlot3SourceFile_clicked();
    void on_lineEditPlot3SourceFile_textChanged();
    void on_lineEditPlot3Xcolumn_textChanged();
    void change_comboBoxPlot3Xcolumn_message(int messageType);
    void on_comboBoxPlot3Xcolumn_currentIndexChanged(int index);
    void on_lineEditPlot3Ycolumn_textChanged();
    void change_comboBoxPlot3Ycolumn_message(int messageType);
    void on_comboBoxPlot3Ycolumn_currentIndexChanged(int index);
    // Plot Nr 4
    void on_comboBoxPlot4Condition_currentIndexChanged(int index);
    void on_comboBoxPlot4ConditionGNSS_currentIndexChanged(int index);
    void on_comboBoxPlot4ConditionGPS_currentIndexChanged(int index);
    void on_comboBoxPlot4ConditionGalileo_currentIndexChanged(int index);
    void on_comboBoxPlot4ConditionGLONASS_currentIndexChanged(int index);
    void on_comboBoxPlot4ConditionGEO_currentIndexChanged(int index);
    void on_comboBoxPlot4ConditionBDS_currentIndexChanged(int index);
    void on_comboBoxPlot4ConditionQZSS_currentIndexChanged(int index);
    void on_comboBoxPlot4ConditionIRNSS_currentIndexChanged(int index);
    void on_comboBoxPlot4ConditionOutput_currentIndexChanged(int index);
    void on_pushButtonPlot4SourceFile_clicked();
    void on_lineEditPlot4SourceFile_textChanged();
    void on_lineEditPlot4Xcolumn_textChanged();
    void change_comboBoxPlot4Xcolumn_message(int messageType);
    void on_comboBoxPlot4Xcolumn_currentIndexChanged(int index);
    void on_lineEditPlot4Ycolumn_textChanged();
    void change_comboBoxPlot4Ycolumn_message(int messageType);
    void on_comboBoxPlot4Ycolumn_currentIndexChanged(int index);
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
    void on_checkBoxStartTimeCompareOrbits_clicked(bool checked);
    void on_checkBoxEndTimeCompareOrbits_clicked(bool checked);
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
    void command_2_CompareNavMessageTypes(QString const *navMessageTypesCmd,QString const *navMessageTypesOption,QString *warningString);
    void selectGNSS_CompareNavMessageTypes(int selectFlag,int iGNSS);
    void on_pushButtonCompareNavMessageTypesSetDefault_clicked();
    void on_pushButtonCompareNavMessageTypesBoost_clicked();
    void on_pushButtonCompareNavMessageTypesLower_clicked();
    void on_checkBoxCompareNavMessageTypeGPS_clicked(bool checked);
    void on_checkBoxCompareNavMessageTypeGalileo_clicked(bool checked);
    void on_checkBoxCompareNavMessageTypeGLONASS_clicked(bool checked);
    void on_checkBoxCompareNavMessageTypeGEO_clicked(bool checked);
    void on_checkBoxCompareNavMessageTypeBDS_clicked(bool checked);
    void on_checkBoxCompareNavMessageTypeQZSS_clicked(bool checked);
    void on_checkBoxCompareNavMessageTypeIRNSS_clicked(bool checked);
    void on_checkBoxCompareNavMessageTypeGPS_2_clicked(bool checked);
    void on_checkBoxCompareNavMessageTypeGalileo_2_clicked(bool checked);
    void on_checkBoxCompareNavMessageTypeGLONASS_2_clicked(bool checked);
    void on_checkBoxCompareNavMessageTypeGEO_2_clicked(bool checked);
    void on_checkBoxCompareNavMessageTypeBDS_2_clicked(bool checked);
    void on_checkBoxCompareNavMessageTypeQZSS_2_clicked(bool checked);
    void on_checkBoxCompareNavMessageTypeIRNSS_2_clicked(bool checked);
    void on_tableWidgetCompareNavMessageTypeGPS_clicked();
    void on_tableWidgetCompareNavMessageTypeGalileo_clicked();
    void on_tableWidgetCompareNavMessageTypeGLONASS_clicked();
    void on_tableWidgetCompareNavMessageTypeGEO_clicked();
    void on_tableWidgetCompareNavMessageTypeBDS_clicked();
    void on_tableWidgetCompareNavMessageTypeQZSS_clicked();
    void on_tableWidgetCompareNavMessageTypeIRNSS_clicked();
    void on_tableWidgetCompareNavMessageTypeGPS_2_clicked();
    void on_tableWidgetCompareNavMessageTypeGalileo_2_clicked();
    void on_tableWidgetCompareNavMessageTypeGLONASS_2_clicked();
    void on_tableWidgetCompareNavMessageTypeGEO_2_clicked();
    void on_tableWidgetCompareNavMessageTypeBDS_2_clicked();
    void on_tableWidgetCompareNavMessageTypeQZSS_2_clicked();
    void on_tableWidgetCompareNavMessageTypeIRNSS_2_clicked();
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
    void on_checkBoxStartTimeShowOrbits_clicked(bool checked);
    void on_checkBoxEndTimeShowOrbits_clicked(bool checked);
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
    void on_groupBoxEleAziSpecify_clicked(bool checked);
    void on_radioButtonEleAziSpecifyUserCartesian_clicked();
    void on_radioButtonEleAziSpecifyUserGeodetic_clicked();
    void selectGNSS_ShowNavMessageTypes(int selectFlag,int iGNSS);
    void on_pushButtonShowNavMessageTypesSetDefault_clicked();
    void on_pushButtonShowNavMessageTypesBoost_clicked();
    void on_pushButtonShowNavMessageTypesLower_clicked();
    void on_checkBoxShowNavMessageTypeGPS_clicked(bool checked);
    void on_checkBoxShowNavMessageTypeGalileo_clicked(bool checked);
    void on_checkBoxShowNavMessageTypeGLONASS_clicked(bool checked);
    void on_checkBoxShowNavMessageTypeGEO_clicked(bool checked);
    void on_checkBoxShowNavMessageTypeBDS_clicked(bool checked);
    void on_checkBoxShowNavMessageTypeQZSS_clicked(bool checked);
    void on_checkBoxShowNavMessageTypeIRNSS_clicked(bool checked);
    void on_tableWidgetShowNavMessageTypeGPS_clicked();
    void on_tableWidgetShowNavMessageTypeGalileo_clicked();
    void on_tableWidgetShowNavMessageTypeGLONASS_clicked();
    void on_tableWidgetShowNavMessageTypeGEO_clicked();
    void on_tableWidgetShowNavMessageTypeBDS_clicked();
    void on_tableWidgetShowNavMessageTypeQZSS_clicked();
    void on_tableWidgetShowNavMessageTypeIRNSS_clicked();

    //Header for adderror_rinex.cpp
    void on_pushButtonRinexObsAddError_clicked();
    void on_pushButtonUserAddedErrorAddError_clicked();
    void on_groupBoxRinexNavFileGLOAddError_clicked(bool checked);
    void on_pushButtonRinexNavFileGLOAddError_clicked();
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
    gLAB_ToolTip             *gLABToolTipWin;
    GNSS_Date_Converter      *DateConvWin;
    GNSS_Coord_converter     *CoordConvWin;
    GNSS_SNR_Advanced        *SnrAdvancedMinWin;
    GNSS_SNR_Advanced        *SnrAdvancedMaxWin;
    GNSS_CS_SF_Advanced      *CSAdvancedSF;
    GNSS_CS_MW_Advanced      *CSAdvancedMW;
    GNSS_CS_LI_Advanced      *CSAdvancedLI;
    GNSS_CS_IGF_Advanced     *CSAdvancedIGF;
    GNSS_Antenna_Advanced    *APCAdvanced;
    GNSS_SBAS_OBAD_Set       *SBASOBADSet;
    GNSS_FreqMeas_Order      *FreqMeasGNSS;
    GNSS_Meas_Select         *MeasSelectGNSS;
    GNSS_Multi_Threading     *MultiThread;

protected:
    void mousePressEvent(QMouseEvent * event);
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // GLAB_GUI_H

