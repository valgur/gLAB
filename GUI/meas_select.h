#ifndef MEAS_SELECT_H
#define MEAS_SELECT_H

#include <QDialog>
#include <QFile>
#include <QCloseEvent>
#include <QCheckBox>
#include <QComboBox>
#include <QFrame>
//#include <QDebug>
#include "glab_const.h"

extern QStringList EmptyMeas;
extern QStringList GNSSFreqTypeMeas[MAX_GNSS][MAX_GNSS_FREQ][5];

namespace Ui {
    class GNSS_Meas_Select;
}

class GNSS_Meas_Select : public QDialog
{
    Q_OBJECT

public:
    explicit GNSS_Meas_Select(QWidget *parent = nullptr);
    ~GNSS_Meas_Select();

public:
    //This is a definition of a variable with a pointer to a function type "void" with no parameters for class gLAB_GUI
    typedef void (GNSS_Meas_Select::*VoidNoParamFuncPointer)();
    typedef void (GNSS_Meas_Select::*Void1IntFuncPointer)(bool p1);
    //Declare array of pointers to pushButton of GERSCJI
    QPushButton *PushButtonGNSS[MAX_GNSS];
    //Declare array of pointer to pushButton GNSS SNR _clicked() functions
    VoidNoParamFuncPointer PushButtonGNSSFunctions[MAX_GNSS];

    //Declare array of pointers to Frame of Label of GERSCJI
    QFrame *FrameGNSSLabel[MAX_GNSS][2];
    //Declare array of pointers to Frame of print of GERSCJI
    QFrame *FrameGNSSPrint[MAX_GNSS][10];
    //Declare array of pointers to ComBoBox of frequency of GERSCJI
    QComboBox *ComBoBoxGNSSFreq[MAX_GNSS][10];
    //Declare array of pointers to ComBoBox of type of GERSCJI
    QComboBox *ComBoBoxGNSSType[MAX_GNSS][10];
    //Declare array of pointers to ComBoBox of measurement of GERSCJI
    QComboBox *ComBoBoxGNSSMeas[MAX_GNSS][10];

    int nPrint[MAX_GNSS];
    int OkFlag,MeasFlag;



private slots:
    void InitPushButtonGNSSPointers();
    void InitPushButtonGNSSMinFuncPointers();
    void InitMeasPointers();

    void cleanPrintMeas(int iGNSS,int iMeas);
    void changePrintMeas(int iGNSS,int iFreq,int iType,int iMeas);

    void on_pushButtonAddPrint_clicked();
    void on_pushButtonDelPrint_clicked();

    void on_pushButtonGPS_clicked();
    void on_pushButtonGalileo_clicked();
    void on_pushButtonGLONASS_clicked();
    void on_pushButtonGEO_clicked();
    void on_pushButtonBDS_clicked();
    void on_pushButtonQZSS_clicked();
    void on_pushButtonIRNSS_clicked();

    //GPS
    void SetDefaultMeasGPS();
    void on_comboBoxFreqGPS_1_currentIndexChanged(int index);
    void on_comboBoxFreqGPS_2_currentIndexChanged(int index);
    void on_comboBoxFreqGPS_3_currentIndexChanged(int index);
    void on_comboBoxFreqGPS_4_currentIndexChanged(int index);
    void on_comboBoxFreqGPS_5_currentIndexChanged(int index);
    void on_comboBoxFreqGPS_6_currentIndexChanged(int index);
    void on_comboBoxFreqGPS_7_currentIndexChanged(int index);
    void on_comboBoxFreqGPS_8_currentIndexChanged(int index);
    void on_comboBoxFreqGPS_9_currentIndexChanged(int index);
    void on_comboBoxFreqGPS_10_currentIndexChanged(int index);
    void on_comboBoxTypeGPS_1_currentIndexChanged(int index);
    void on_comboBoxTypeGPS_2_currentIndexChanged(int index);
    void on_comboBoxTypeGPS_3_currentIndexChanged(int index);
    void on_comboBoxTypeGPS_4_currentIndexChanged(int index);
    void on_comboBoxTypeGPS_5_currentIndexChanged(int index);
    void on_comboBoxTypeGPS_6_currentIndexChanged(int index);
    void on_comboBoxTypeGPS_7_currentIndexChanged(int index);
    void on_comboBoxTypeGPS_8_currentIndexChanged(int index);
    void on_comboBoxTypeGPS_9_currentIndexChanged(int index);
    void on_comboBoxTypeGPS_10_currentIndexChanged(int index);

    //Galileo
    void SetDefaultMeasGalileo();
    void on_comboBoxFreqGalileo_1_currentIndexChanged(int index);
    void on_comboBoxFreqGalileo_2_currentIndexChanged(int index);
    void on_comboBoxFreqGalileo_3_currentIndexChanged(int index);
    void on_comboBoxFreqGalileo_4_currentIndexChanged(int index);
    void on_comboBoxFreqGalileo_5_currentIndexChanged(int index);
    void on_comboBoxFreqGalileo_6_currentIndexChanged(int index);
    void on_comboBoxFreqGalileo_7_currentIndexChanged(int index);
    void on_comboBoxFreqGalileo_8_currentIndexChanged(int index);
    void on_comboBoxFreqGalileo_9_currentIndexChanged(int index);
    void on_comboBoxFreqGalileo_10_currentIndexChanged(int index);
    void on_comboBoxTypeGalileo_1_currentIndexChanged(int index);
    void on_comboBoxTypeGalileo_2_currentIndexChanged(int index);
    void on_comboBoxTypeGalileo_3_currentIndexChanged(int index);
    void on_comboBoxTypeGalileo_4_currentIndexChanged(int index);
    void on_comboBoxTypeGalileo_5_currentIndexChanged(int index);
    void on_comboBoxTypeGalileo_6_currentIndexChanged(int index);
    void on_comboBoxTypeGalileo_7_currentIndexChanged(int index);
    void on_comboBoxTypeGalileo_8_currentIndexChanged(int index);
    void on_comboBoxTypeGalileo_9_currentIndexChanged(int index);
    void on_comboBoxTypeGalileo_10_currentIndexChanged(int index);

    //GLONASS
    void SetDefaultMeasGLONASS();
    void on_comboBoxFreqGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxFreqGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxFreqGLONASS_3_currentIndexChanged(int index);
    void on_comboBoxFreqGLONASS_4_currentIndexChanged(int index);
    void on_comboBoxFreqGLONASS_5_currentIndexChanged(int index);
    void on_comboBoxFreqGLONASS_6_currentIndexChanged(int index);
    void on_comboBoxFreqGLONASS_7_currentIndexChanged(int index);
    void on_comboBoxFreqGLONASS_8_currentIndexChanged(int index);
    void on_comboBoxFreqGLONASS_9_currentIndexChanged(int index);
    void on_comboBoxFreqGLONASS_10_currentIndexChanged(int index);
    void on_comboBoxTypeGLONASS_1_currentIndexChanged(int index);
    void on_comboBoxTypeGLONASS_2_currentIndexChanged(int index);
    void on_comboBoxTypeGLONASS_3_currentIndexChanged(int index);
    void on_comboBoxTypeGLONASS_4_currentIndexChanged(int index);
    void on_comboBoxTypeGLONASS_5_currentIndexChanged(int index);
    void on_comboBoxTypeGLONASS_6_currentIndexChanged(int index);
    void on_comboBoxTypeGLONASS_7_currentIndexChanged(int index);
    void on_comboBoxTypeGLONASS_8_currentIndexChanged(int index);
    void on_comboBoxTypeGLONASS_9_currentIndexChanged(int index);
    void on_comboBoxTypeGLONASS_10_currentIndexChanged(int index);

    //GEO
    void SetDefaultMeasGEO();
    void on_comboBoxFreqGEO_1_currentIndexChanged(int index);
    void on_comboBoxFreqGEO_2_currentIndexChanged(int index);
    void on_comboBoxFreqGEO_3_currentIndexChanged(int index);
    void on_comboBoxFreqGEO_4_currentIndexChanged(int index);
    void on_comboBoxFreqGEO_5_currentIndexChanged(int index);
    void on_comboBoxFreqGEO_6_currentIndexChanged(int index);
    void on_comboBoxFreqGEO_7_currentIndexChanged(int index);
    void on_comboBoxFreqGEO_8_currentIndexChanged(int index);
    void on_comboBoxFreqGEO_9_currentIndexChanged(int index);
    void on_comboBoxFreqGEO_10_currentIndexChanged(int index);
    void on_comboBoxTypeGEO_1_currentIndexChanged(int index);
    void on_comboBoxTypeGEO_2_currentIndexChanged(int index);
    void on_comboBoxTypeGEO_3_currentIndexChanged(int index);
    void on_comboBoxTypeGEO_4_currentIndexChanged(int index);
    void on_comboBoxTypeGEO_5_currentIndexChanged(int index);
    void on_comboBoxTypeGEO_6_currentIndexChanged(int index);
    void on_comboBoxTypeGEO_7_currentIndexChanged(int index);
    void on_comboBoxTypeGEO_8_currentIndexChanged(int index);
    void on_comboBoxTypeGEO_9_currentIndexChanged(int index);
    void on_comboBoxTypeGEO_10_currentIndexChanged(int index);

    //BDS
    void SetDefaultMeasBDS();
    void on_comboBoxFreqBDS_1_currentIndexChanged(int index);
    void on_comboBoxFreqBDS_2_currentIndexChanged(int index);
    void on_comboBoxFreqBDS_3_currentIndexChanged(int index);
    void on_comboBoxFreqBDS_4_currentIndexChanged(int index);
    void on_comboBoxFreqBDS_5_currentIndexChanged(int index);
    void on_comboBoxFreqBDS_6_currentIndexChanged(int index);
    void on_comboBoxFreqBDS_7_currentIndexChanged(int index);
    void on_comboBoxFreqBDS_8_currentIndexChanged(int index);
    void on_comboBoxFreqBDS_9_currentIndexChanged(int index);
    void on_comboBoxFreqBDS_10_currentIndexChanged(int index);
    void on_comboBoxTypeBDS_1_currentIndexChanged(int index);
    void on_comboBoxTypeBDS_2_currentIndexChanged(int index);
    void on_comboBoxTypeBDS_3_currentIndexChanged(int index);
    void on_comboBoxTypeBDS_4_currentIndexChanged(int index);
    void on_comboBoxTypeBDS_5_currentIndexChanged(int index);
    void on_comboBoxTypeBDS_6_currentIndexChanged(int index);
    void on_comboBoxTypeBDS_7_currentIndexChanged(int index);
    void on_comboBoxTypeBDS_8_currentIndexChanged(int index);
    void on_comboBoxTypeBDS_9_currentIndexChanged(int index);
    void on_comboBoxTypeBDS_10_currentIndexChanged(int index);

    //QZSS
    void SetDefaultMeasQZSS();
    void on_comboBoxFreqQZSS_1_currentIndexChanged(int index);
    void on_comboBoxFreqQZSS_2_currentIndexChanged(int index);
    void on_comboBoxFreqQZSS_3_currentIndexChanged(int index);
    void on_comboBoxFreqQZSS_4_currentIndexChanged(int index);
    void on_comboBoxFreqQZSS_5_currentIndexChanged(int index);
    void on_comboBoxFreqQZSS_6_currentIndexChanged(int index);
    void on_comboBoxFreqQZSS_7_currentIndexChanged(int index);
    void on_comboBoxFreqQZSS_8_currentIndexChanged(int index);
    void on_comboBoxFreqQZSS_9_currentIndexChanged(int index);
    void on_comboBoxFreqQZSS_10_currentIndexChanged(int index);
    void on_comboBoxTypeQZSS_1_currentIndexChanged(int index);
    void on_comboBoxTypeQZSS_2_currentIndexChanged(int index);
    void on_comboBoxTypeQZSS_3_currentIndexChanged(int index);
    void on_comboBoxTypeQZSS_4_currentIndexChanged(int index);
    void on_comboBoxTypeQZSS_5_currentIndexChanged(int index);
    void on_comboBoxTypeQZSS_6_currentIndexChanged(int index);
    void on_comboBoxTypeQZSS_7_currentIndexChanged(int index);
    void on_comboBoxTypeQZSS_8_currentIndexChanged(int index);
    void on_comboBoxTypeQZSS_9_currentIndexChanged(int index);
    void on_comboBoxTypeQZSS_10_currentIndexChanged(int index);

    //IRNSS
    void SetDefaultMeasIRNSS();
    void on_comboBoxFreqIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxFreqIRNSS_2_currentIndexChanged(int index);
    void on_comboBoxFreqIRNSS_3_currentIndexChanged(int index);
    void on_comboBoxFreqIRNSS_4_currentIndexChanged(int index);
    void on_comboBoxFreqIRNSS_5_currentIndexChanged(int index);
    void on_comboBoxFreqIRNSS_6_currentIndexChanged(int index);
    void on_comboBoxFreqIRNSS_7_currentIndexChanged(int index);
    void on_comboBoxFreqIRNSS_8_currentIndexChanged(int index);
    void on_comboBoxFreqIRNSS_9_currentIndexChanged(int index);
    void on_comboBoxFreqIRNSS_10_currentIndexChanged(int index);
    void on_comboBoxTypeIRNSS_1_currentIndexChanged(int index);
    void on_comboBoxTypeIRNSS_2_currentIndexChanged(int index);
    void on_comboBoxTypeIRNSS_3_currentIndexChanged(int index);
    void on_comboBoxTypeIRNSS_4_currentIndexChanged(int index);
    void on_comboBoxTypeIRNSS_5_currentIndexChanged(int index);
    void on_comboBoxTypeIRNSS_6_currentIndexChanged(int index);
    void on_comboBoxTypeIRNSS_7_currentIndexChanged(int index);
    void on_comboBoxTypeIRNSS_8_currentIndexChanged(int index);
    void on_comboBoxTypeIRNSS_9_currentIndexChanged(int index);
    void on_comboBoxTypeIRNSS_10_currentIndexChanged(int index);


    void on_pushButtonMeasSelectDefault_clicked();
    void on_pushButtonMeasSelectOk_clicked();
    void on_pushButtonMeasSelectCancel_clicked();
    void closeEvent(QCloseEvent *bar);

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

    void setMeasdefaults();

    void changeCurrentPage();

    int getgLABOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);
    void loadgLABOptions(QString *warningString, QStringList *ParametersList);

private:
    Ui::GNSS_Meas_Select *uiMeas;
};

#endif // MEAS_SELECT_H
