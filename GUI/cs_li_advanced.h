#ifndef CS_LI_ADVANCED_H
#define CS_LI_ADVANCED_H

#include <QDialog>
#include <QFile>
#include <QComboBox>
#include "glab_const.h"

namespace Ui {
class GNSS_CS_LI_Advanced;
}

class GNSS_CS_LI_Advanced : public QDialog
{
    Q_OBJECT

public:
    explicit GNSS_CS_LI_Advanced(QWidget *parent = nullptr);
    ~GNSS_CS_LI_Advanced();

public:
    //This is a definition of a variable with a pointer to a function type "void" with no parameters for class gLAB_GUI
    typedef void (GNSS_CS_LI_Advanced::*VoidNoParamFuncPointer)();
    //Declare array of pointers to pushButton of GERSCJI
    QPushButton *PushButtonGNSS[MAX_GNSS];
    //Declare array of pointer to pushButton GNSS _clicked() functions
    VoidNoParamFuncPointer PushButtonGNSSFunctions[MAX_GNSS];
    //Declare array of pointers to Frame of combinations of GERSCJI
    QWidget *FrameCombGNSS[MAX_GNSS][3];
    //Declare array of pointers to ComboBox of frequencies (1: freq1, 2: freq2) of GERSCJI
    QComboBox *ComboBoxFreqGNSS[MAX_GNSS][3][2];
    //Declare array of pointers to ComboBox of measurements (1: phase1, 2: phase2) of GERSCJI
    QComboBox *ComboBoxMeasGNSS[MAX_GNSS][3][2][MAX_GNSS_FREQ];

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


    //GPS
    void SetDefaultGPS();
    void on_pushButtonLIGPSAdd_clicked();
    void on_pushButtonLIGPSDel_clicked();
    void on_comboBoxLIComb1Freq1GPS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Freq2GPS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Freq1GPS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Freq2GPS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Freq1GPS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Freq2GPS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F5MeasGPS_currentIndexChanged(int index);

    //Galileo
    void SetDefaultGalileo();
    void on_pushButtonLIGalileoAdd_clicked();
    void on_pushButtonLIGalileoDel_clicked();
    void on_comboBoxLIComb1Freq1Galileo_currentIndexChanged(int index);
    void on_comboBoxLIComb1Freq2Galileo_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb2Freq1Galileo_currentIndexChanged(int index);
    void on_comboBoxLIComb2Freq2Galileo_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb3Freq1Galileo_currentIndexChanged(int index);
    void on_comboBoxLIComb3Freq2Galileo_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F8MeasGalileo_currentIndexChanged(int index);

    //GLONASS
    void SetDefaultGLONASS();
    void on_pushButtonLIGLONASSAdd_clicked();
    void on_pushButtonLIGLONASSDel_clicked();
    void on_comboBoxLIComb1Freq1GLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Freq2GLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Freq1GLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Freq2GLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Freq1GLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Freq2GLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F6MeasGLONASS_currentIndexChanged(int index);

    //GEO
    void SetDefaultGEO();
    void on_pushButtonLIGEOAdd_clicked();
    void on_pushButtonLIGEODel_clicked();
    void on_comboBoxLIComb1Freq1GEO_currentIndexChanged(int index);
    void on_comboBoxLIComb1Freq2GEO_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxLIComb2Freq1GEO_currentIndexChanged(int index);
    void on_comboBoxLIComb2Freq2GEO_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxLIComb3Freq1GEO_currentIndexChanged(int index);
    void on_comboBoxLIComb3Freq2GEO_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F5MeasGEO_currentIndexChanged(int index);

    //BDS
    void SetDefaultBDS();
    void on_pushButtonLIBDSAdd_clicked();
    void on_pushButtonLIBDSDel_clicked();
    void on_comboBoxLIComb1Freq1BDS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Freq2BDS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Freq1BDS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Freq2BDS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Freq1BDS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Freq2BDS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F8MeasBDS_currentIndexChanged(int index);

    //QZSS
    void SetDefaultQZSS();
    void on_pushButtonLIQZSSAdd_clicked();
    void on_pushButtonLIQZSSDel_clicked();
    void on_comboBoxLIComb1Freq1QZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Freq2QZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Freq1QZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Freq2QZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Freq1QZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Freq2QZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F6MeasQZSS_currentIndexChanged(int index);

    //IRNSS
    void SetDefaultIRNSS();
    void on_pushButtonLIIRNSSAdd_clicked();
    void on_pushButtonLIIRNSSDel_clicked();
    void on_comboBoxLIComb1Freq1IRNSS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Freq2IRNSS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase1F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxLIComb1Phase2F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Freq1IRNSS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Freq2IRNSS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase1F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxLIComb2Phase2F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Freq1IRNSS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Freq2IRNSS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase1F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxLIComb3Phase2F9MeasIRNSS_currentIndexChanged(int index);

    void on_pushButtonCSLIAdvancedDefault_clicked();
    void on_pushButtonCSLIAdvancedOk_clicked();
    void on_pushButtonCSLIAdvancedCancel_clicked();

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

    int getgLABOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);
    void loadgLABOptions(QString *warningString, QStringList *ParametersList, const int freqMeas);

private:
    Ui::GNSS_CS_LI_Advanced *uiCSLI;
};

#endif // CS_LI_ADVANCED_H
