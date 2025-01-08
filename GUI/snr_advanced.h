#ifndef SNR_ADVANCED_H
#define SNR_ADVANCED_H

#include <QDialog>
#include <QFile>
#include <QCloseEvent>
//#include <QDebug>
#include <QCheckBox>
#include <QComboBox>
#include "glab_const.h"

namespace Ui {
    class GNSS_SNR_Advanced;
}

class GNSS_SNR_Advanced : public QDialog
{
    Q_OBJECT

public:
    explicit GNSS_SNR_Advanced(QWidget *parent = nullptr);
    explicit GNSS_SNR_Advanced(QWidget *parent = nullptr,int setMinorMax=0);
    ~GNSS_SNR_Advanced();

public:
    //This is a definition of a variable with a pointer to a function type "void" with no parameters for class gLAB_GUI
    typedef void (GNSS_SNR_Advanced::*VoidNoParamFuncPointer)();
    //Declare array of pointers to pushButton of GERSCJI
    QPushButton *PushButtonGNSS[MAX_GNSS];
    //Declare array of pointer to pushButton GNSS SNR _clicked() functions
    VoidNoParamFuncPointer PushButtonGNSSFunctions[MAX_GNSS];
    //Declare array of pointers to ComboBox of defualt min/max SNR of GERSCJI
    QComboBox *ComboBoxGNSSDefaultSNR[2][MAX_GNSS];
    //Declare array of pointers to LineEdit of defualt min/max SNR of GERSCJI
    QLineEdit *LineEditGNSSDefaultSNR[2][MAX_GNSS];
    //Declare array of pointers to ComboBox of measurements of GERSCJI
    QComboBox *ComboBoxGNSSMeas[2][MAX_GNSS][MAX_GNSS_FREQ][2];
    //Declare array of pointers to ComboBox of min/max SNR of GERSCJI
    QComboBox *ComboBoxGNSSSNR[2][MAX_GNSS][MAX_GNSS_FREQ][2];
    //Declare array of pointers to LineEdit of min/max SNR of GERSCJI
    QLineEdit *LineEditGNSSSNR[2][MAX_GNSS][MAX_GNSS_FREQ][2];

    int OkFlag;
    int MinorMax; //MinSNR=0, MaxSNR=1

private slots:
    void InitPushButtonGNSSPointers();
    void InitPushButtonGNSSMinFuncPointers();
    void InitComboBoxGNSSDefaultSNRPointers();
    void InitLineEditGNSSDefaultSNRPointers();
    void InitComboBoxGNSSMeasPointers();
    void InitComboBoxGNSSSNRPointers();
    void InitLineEditGNSSSNRPointers();


    void on_pushButtonGPS_clicked();
    void on_pushButtonGalileo_clicked();
    void on_pushButtonGLONASS_clicked();
    void on_pushButtonGEO_clicked();
    void on_pushButtonBDS_clicked();
    void on_pushButtonQZSS_clicked();
    void on_pushButtonIRNSS_clicked();

    //GPS
    //GPS Min
    void SetDefaultSNRThresholdMinGPS();
    void on_comboBoxSNRThresholdsMinGPS_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF1CodeGPS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF1CodeGPS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF1CodeGPS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF2CodeGPS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF2CodeGPS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF2CodeGPS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF5CodeGPS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF5CodeGPS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF5CodeGPS_2_currentIndexChanged(int index);
    //GPS Max
    void SetDefaultSNRThresholdMaxGPS();
    void on_comboBoxSNRThresholdsMaxGPS_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF1CodeGPS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF1CodeGPS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF1CodeGPS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF2CodeGPS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF2CodeGPS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF2CodeGPS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF5CodeGPS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF5CodeGPS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF5CodeGPS_2_currentIndexChanged(int index);
    //Galileo
    //Galileo Min
    void SetDefaultSNRThresholdMinGalileo();
    void on_comboBoxSNRThresholdsMinGalileo_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF1CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF1CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF1CodeGalileo_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF5CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF5CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF5CodeGalileo_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF6CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF6CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF6CodeGalileo_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF7CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF7CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF7CodeGalileo_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF8CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF8CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF8CodeGalileo_2_currentIndexChanged(int index);
    //Galileo Max
    void SetDefaultSNRThresholdMaxGalileo();
    void on_comboBoxSNRThresholdsMaxGalileo_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF1CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF1CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF1CodeGalileo_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF5CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF5CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF5CodeGalileo_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF6CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF6CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF6CodeGalileo_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF7CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF7CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF7CodeGalileo_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF8CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF8CodeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF8CodeGalileo_2_currentIndexChanged(int index);
    //GLONASS
    //GLONASS Min
    void SetDefaultSNRThresholdMinGLONASS();
    void on_comboBoxSNRThresholdsMinGLONASS_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF1CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF1CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF1CodeGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF2CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF2CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF2CodeGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF3CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF3CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF3CodeGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF4CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF4CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF4CodeGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF6CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF6CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF6CodeGLONASS_2_currentIndexChanged(int index);
    //GLONASS Max
    void SetDefaultSNRThresholdMaxGLONASS();
    void on_comboBoxSNRThresholdsMaxGLONASS_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF1CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF1CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF1CodeGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF2CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF2CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF2CodeGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF3CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF3CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF3CodeGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF4CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF4CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF4CodeGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF6CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF6CodeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF6CodeGLONASS_2_currentIndexChanged(int index);
    //GEO
    //GEO Min
    void SetDefaultSNRThresholdMinGEO();
    void on_comboBoxSNRThresholdsMinGEO_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF1CodeGEO_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF1CodeGEO_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF1CodeGEO_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF5CodeGEO_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF5CodeGEO_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF5CodeGEO_2_currentIndexChanged(int index);
    //GEO Max
    void SetDefaultSNRThresholdMaxGEO();
    void on_comboBoxSNRThresholdsMaxGEO_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF1CodeGEO_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF1CodeGEO_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF1CodeGEO_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF5CodeGEO_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF5CodeGEO_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF5CodeGEO_2_currentIndexChanged(int index);
    //BDS
    //BDS Min
    void SetDefaultSNRThresholdMinBDS();
    void on_comboBoxSNRThresholdsMinBDS_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF2CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF2CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF2CodeBDS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF7CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF7CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF7CodeBDS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF6CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF6CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF6CodeBDS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF5CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF5CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF5CodeBDS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF1CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF1CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF1CodeBDS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF8CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF8CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF8CodeBDS_2_currentIndexChanged(int index);
    //BDS Max
    void SetDefaultSNRThresholdMaxBDS();
    void on_comboBoxSNRThresholdsMaxBDS_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF2CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF2CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF2CodeBDS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF7CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF7CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF7CodeBDS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF6CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF6CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF6CodeBDS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF5CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF5CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF5CodeBDS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF1CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF1CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF1CodeBDS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF8CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF8CodeBDS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF8CodeBDS_2_currentIndexChanged(int index);
    //QZSS
    //QZSS Min
    void SetDefaultSNRThresholdMinQZSS();
    void on_comboBoxSNRThresholdsMinQZSS_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF1CodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF1CodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF1CodeQZSS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF2CodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF2CodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF2CodeQZSS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF5CodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF5CodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF5CodeQZSS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF6CodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF6CodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF6CodeQZSS_2_currentIndexChanged(int index);
    //QZSS Max
    void SetDefaultSNRThresholdMaxQZSS();
    void on_comboBoxSNRThresholdsMaxQZSS_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF1CodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF1CodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF1CodeQZSS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF2CodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF2CodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF2CodeQZSS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF5CodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF5CodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF5CodeQZSS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF6CodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF6CodeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF6CodeQZSS_2_currentIndexChanged(int index);
    //IRNSS
    //IRNSS Min
    void SetDefaultSNRThresholdMinIRNSS();
    void on_comboBoxSNRThresholdsMinIRNSS_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF5CodeIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF5CodeIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF5CodeIRNSS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMinMeasF9CodeIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF9CodeIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMinSelectF9CodeIRNSS_2_currentIndexChanged(int index);
    //IRNSS Max
    void SetDefaultSNRThresholdMaxIRNSS();
    void on_comboBoxSNRThresholdsMaxIRNSS_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF5CodeIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF5CodeIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF5CodeIRNSS_2_currentIndexChanged(int index);
    void on_comboBoxSNRMaxMeasF9CodeIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF9CodeIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxSNRMaxSelectF9CodeIRNSS_2_currentIndexChanged(int index);

    void on_pushButtonSNRAdvancedDefault_clicked();
    void on_pushButtonSNRAdvancedOk_clicked();
    void on_pushButtonSNRAdvancedCancel_clicked();

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

    void setSNRdefaults();

    void changeCurrentPage();

    int  getgLABOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);
    void loadgLABOptions(QString *warningString, QStringList *ParametersList);

private:
    Ui::GNSS_SNR_Advanced *uiSNR;

};

#endif // SNR_ADVANCED_H
