#ifndef CS_IGF_ADVANCED_H
#define CS_IGF_ADVANCED_H

#include <QDialog>
#include <QFile>
//#include <QDebug>
#include <QComboBox>
#include "glab_const.h"

namespace Ui {
class GNSS_CS_IGF_Advanced;
}

class GNSS_CS_IGF_Advanced : public QDialog
{
    Q_OBJECT

public:
    explicit GNSS_CS_IGF_Advanced(QWidget *parent = nullptr);
    ~GNSS_CS_IGF_Advanced();

public:
    //This is a definition of a variable with a pointer to a function type "void" with no parameters for class gLAB_GUI
    typedef void (GNSS_CS_IGF_Advanced::*VoidNoParamFuncPointer)();
    //Declare array of pointers to pushButton of GERSCJI
    QPushButton *PushButtonGNSS[MAX_GNSS];
    //Declare array of pointer to pushButton GNSS _clicked() functions
    VoidNoParamFuncPointer PushButtonGNSSFunctions[MAX_GNSS];
    //Declare array of pointers to Frame of combinations of GERSCJI
    QWidget *FrameCombGNSS[MAX_GNSS][3];
    //Declare array of pointers to ComboBox of frequencies (1: freq1, 2: freq2, 3: freq3, 4: freq4) of GERSCJI
    QComboBox *ComboBoxFreqGNSS[MAX_GNSS][3][4];
    //Declare array of pointers to ComboBox of measurements (1: phase1, 2: phase2, 3: phase3, 4: phase4) of GERSCJI
    QComboBox *ComboBoxMeasGNSS[MAX_GNSS][3][4][MAX_GNSS_FREQ];

    int TripleQuadruple; //0:Triple-frenquency,1:Quadruple-frenquency
    int OkFlag;

private slots:
    void InitPushButtonGNSSPointers();
    void InitPushButtonGNSSMinFuncPointers();
    void InitCombinationPointers();

    void on_pushButtonGPS_clicked();
    void on_pushButtonGalileo_clicked();
    void on_pushButtonGLONASS_clicked();
    void on_pushButtonGEO_clicked();
    void on_pushButtonBDS_clicked();
    void on_pushButtonQZSS_clicked();
    void on_pushButtonIRNSS_clicked();

    int checkFreqRepeat(int iPhase1,int iPhase2,int iPhase3,int iPhase4);

    //GPS
    void SetDefaultGPS();
    void on_pushButtonIGFGPSAdd_clicked();
    void on_pushButtonIGFGPSDel_clicked();
    void on_comboBoxIGFComb1Freq1GPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq2GPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq3GPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq4GPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq1GPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq2GPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq3GPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq4GPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq1GPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq2GPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq3GPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq4GPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F5MeasGPS_currentIndexChanged(int index);

    //Galileo
    void SetDefaultGalileo();
    void on_pushButtonIGFGalileoAdd_clicked();
    void on_pushButtonIGFGalileoDel_clicked();
    void on_comboBoxIGFComb1Freq1Galileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq2Galileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq3Galileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq4Galileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq1Galileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq2Galileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq3Galileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq4Galileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq1Galileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq2Galileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq3Galileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq4Galileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F8MeasGalileo_currentIndexChanged(int index);

    //GLONASS
    void SetDefaultGLONASS();
    void on_pushButtonIGFGLONASSAdd_clicked();
    void on_pushButtonIGFGLONASSDel_clicked();
    void on_comboBoxIGFComb1Freq1GLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq2GLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq3GLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq4GLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq1GLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq2GLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq3GLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq4GLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq1GLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq2GLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq3GLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq4GLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F6MeasGLONASS_currentIndexChanged(int index);

    //GEO
    void SetDefaultGEO();
    void on_pushButtonIGFGEOAdd_clicked();
    void on_pushButtonIGFGEODel_clicked();
    void on_comboBoxIGFComb1Freq1GEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq2GEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq3GEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq4GEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq1GEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq2GEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq3GEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq4GEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq1GEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq2GEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq3GEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq4GEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F5MeasGEO_currentIndexChanged(int index);

    //BDS
    void SetDefaultBDS();
    void on_pushButtonIGFBDSAdd_clicked();
    void on_pushButtonIGFBDSDel_clicked();
    void on_comboBoxIGFComb1Freq1BDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq2BDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq3BDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq4BDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq1BDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq2BDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq3BDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq4BDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq1BDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq2BDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq3BDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq4BDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F8MeasBDS_currentIndexChanged(int index);

    //QZSS
    void SetDefaultQZSS();
    void on_pushButtonIGFQZSSAdd_clicked();
    void on_pushButtonIGFQZSSDel_clicked();
    void on_comboBoxIGFComb1Freq1QZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq2QZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq3QZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq4QZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq1QZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq2QZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq3QZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq4QZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq1QZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq2QZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq3QZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq4QZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F6MeasQZSS_currentIndexChanged(int index);

    //IRNSS
    void SetDefaultIRNSS();
    void on_pushButtonIGFIRNSSAdd_clicked();
    void on_pushButtonIGFIRNSSDel_clicked();
    void on_comboBoxIGFComb1Freq1IRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq2IRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq3IRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Freq4IRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase1F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase2F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase3F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb1Phase4F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq1IRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq2IRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq3IRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Freq4IRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase1F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase2F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase3F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb2Phase4F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq1IRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq2IRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq3IRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Freq4IRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase1F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase2F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase3F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxIGFComb3Phase4F9MeasIRNSS_currentIndexChanged(int index);


    void on_pushButtonCSIGFAdvancedDefault_clicked();
    void on_pushButtonCSIGFAdvancedOk_clicked();
    void on_pushButtonCSIGFAdvancedCancel_clicked();

public:
    void changePushButtonGPS(bool checked);
    void changePushButtonGalileo(bool checked);
    void changePushButtonGLONASS(bool checked);
    void changePushButtonGEO(bool checked);
    void changePushButtonBDS(bool checked);
    void changePushButtonQZSS(bool checked);
    void changePushButtonIRNSS(bool checked);
    void on_pushButtonPublicGPS_clicked();
    void on_pushButtonPublicGalileo_clicked();
    void on_pushButtonPublicGLONASS_clicked();
    void on_pushButtonPublicGEO_clicked();
    void on_pushButtonPublicBDS_clicked();
    void on_pushButtonPublicQZSS_clicked();
    void on_pushButtonPublicIRNSS_clicked();

    void setCSdefaults();

    void changeCurrentPage();

    void changeToMinimumNoiseMode();
    void changeToTwoIonoFreeMode();

    int  getgLABOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);
    void loadgLABOptions(QString *warningString, QStringList *ParametersList, const int freqMeas, const QRadioButton *MinNoiseButton);

private:
    Ui::GNSS_CS_IGF_Advanced *uiCSIGF;
};

#endif // CS_IGF_ADVANCED_H
