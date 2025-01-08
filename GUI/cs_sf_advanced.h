#ifndef CS_SF_ADVANCED_H
#define CS_SF_ADVANCED_H

#include <QDialog>
#include <QFile>
#include <QComboBox>
#include "glab_const.h"

namespace Ui {
class GNSS_CS_SF_Advanced;
}

class GNSS_CS_SF_Advanced : public QDialog
{
    Q_OBJECT

public:
    explicit GNSS_CS_SF_Advanced(QWidget *parent = nullptr);
    ~GNSS_CS_SF_Advanced();

public:
    //This is a definition of a variable with a pointer to a function type "void" with no parameters for class gLAB_GUI
    typedef void (GNSS_CS_SF_Advanced::*VoidNoParamFuncPointer)();
    //Declare array of pointers to pushButton of GERSCJI
    QPushButton *PushButtonGNSS[MAX_GNSS];
    //Declare array of pointer to pushButton GNSS _clicked() functions
    VoidNoParamFuncPointer PushButtonGNSSFunctions[MAX_GNSS];
    //Declare array of pointers to Frame of combinations of GERSCJI
    QWidget *FrameCombGNSS[MAX_GNSS][3];
    //Declare array of pointers to ComboBox of frequencies of GERSCJI
    QComboBox *ComboBoxFreqGNSS[MAX_GNSS][3];
    //Declare array of pointers to ComboBox of measurements (1: code1, 2: phase1) of GERSCJI
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
    void on_pushButtonSFGPSAdd_clicked();
    void on_pushButtonSFGPSDel_clicked();
    void on_comboBoxSFComb1Freq1GPS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Freq1GPS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Freq1GPS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F5MeasGPS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F1MeasGPS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F2MeasGPS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F5MeasGPS_currentIndexChanged(int index);

    //Galileo
    void SetDefaultGalileo();
    void on_pushButtonSFGalileoAdd_clicked();
    void on_pushButtonSFGalileoDel_clicked();
    void on_comboBoxSFComb1Freq1Galileo_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb2Freq1Galileo_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb3Freq1Galileo_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F8MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F1MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F5MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F6MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F7MeasGalileo_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F8MeasGalileo_currentIndexChanged(int index);

    //GLONASS
    void SetDefaultGLONASS();
    void on_pushButtonSFGLONASSAdd_clicked();
    void on_pushButtonSFGLONASSDel_clicked();
    void on_comboBoxSFComb1Freq1GLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Freq1GLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Freq1GLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F6MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F1MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F2MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F3MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F4MeasGLONASS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F6MeasGLONASS_currentIndexChanged(int index);

    //GEO
    void SetDefaultGEO();
    void on_pushButtonSFGEOAdd_clicked();
    void on_pushButtonSFGEODel_clicked();
    void on_comboBoxSFComb1Freq1GEO_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxSFComb2Freq1GEO_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxSFComb3Freq1GEO_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F5MeasGEO_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F1MeasGEO_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F5MeasGEO_currentIndexChanged(int index);

    //BDS
    void SetDefaultBDS();
    void on_pushButtonSFBDSAdd_clicked();
    void on_pushButtonSFBDSDel_clicked();
    void on_comboBoxSFComb1Freq1BDS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Freq1BDS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Freq1BDS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F8MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F2MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F7MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F6MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F5MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F1MeasBDS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F8MeasBDS_currentIndexChanged(int index);

    //QZSS
    void SetDefaultQZSS();
    void on_pushButtonSFQZSSAdd_clicked();
    void on_pushButtonSFQZSSDel_clicked();
    void on_comboBoxSFComb1Freq1QZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Freq1QZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Freq1QZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F6MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F1MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F2MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F5MeasQZSS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F6MeasQZSS_currentIndexChanged(int index);

    //IRNSS
    void SetDefaultIRNSS();
    void on_pushButtonSFIRNSSAdd_clicked();
    void on_pushButtonSFIRNSSDel_clicked();
    void on_comboBoxSFComb1Freq1IRNSS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Code1F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxSFComb1Phase1F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Freq1IRNSS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Code1F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxSFComb2Phase1F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Freq1IRNSS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Code1F9MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F5MeasIRNSS_currentIndexChanged(int index);
    void on_comboBoxSFComb3Phase1F9MeasIRNSS_currentIndexChanged(int index);

    void on_pushButtonCSSFAdvancedDefault_clicked();
    void on_pushButtonCSSFAdvancedOk_clicked();
    void on_pushButtonCSSFAdvancedCancel_clicked();

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

    int  getgLABOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);
    void loadgLABOptions(QString *warningString, QStringList *ParametersList, const int freqMeas);

private:
    Ui::GNSS_CS_SF_Advanced *uiCSSF;
};

#endif // CS_SF_ADVANCED_H
