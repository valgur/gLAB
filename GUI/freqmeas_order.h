#ifndef FREQMEAS_ORDER_H
#define FREQMEAS_ORDER_H

#include <QDialog>
#include <QFile>
#include <QCloseEvent>
//#include <QDebug>
#include <QCheckBox>
#include <QTableWidget>
#include "glab_const.h"

namespace Ui {
class GNSS_FreqMeas_Order;
}

class GNSS_FreqMeas_Order : public QDialog
{
    Q_OBJECT

public:
    explicit GNSS_FreqMeas_Order(QWidget *parent = nullptr);
    ~GNSS_FreqMeas_Order();

public:
    //This is a definition of a variable with a pointer to a function type "void" with no parameters for class gLAB_GUI
    typedef void (GNSS_FreqMeas_Order::*VoidNoParamFuncPointer)();
    //This is a definition of a variable with a pointer to a function type "void" with bool parameters for class gLAB_GUI
    typedef void (GNSS_FreqMeas_Order::*VoidBoolParamFuncPointer)(bool checked);
    //Declare array of pointers to pushButton of GERSCJI
    QPushButton *PushButtonGNSS[MAX_GNSS];
    //Declare array of pointer to pushButton GNSS _clicked() functions
    VoidNoParamFuncPointer PushButtonGNSSFunctions[MAX_GNSS];
    //Declare array of pointers to CheckBox of Freq/Meas Order of GERSCJI
    QCheckBox *CheckBoxGNSSOrder[MAX_GNSS];
    //Declare array of pointers to clicked CheckBox functions of Freq/Meas Order of GERSCJI
    VoidBoolParamFuncPointer GroupBoxGNSSOrder[MAX_GNSS];
    //Declare array of pointers to TableWidget of [0:freq, 1:code, 2:phase, 3:doppler] of GERSCJI
    QTableWidget *TableGNSS[MAX_GNSS][4];

    QString FreqBackGroundColor;
    QString MeasBackGroundColor;

    QBrush gnssUnSelected,FreqSelected,MeasSelected;

    int OkFlag;

private slots:
    void InitPushButtonGNSSPointers();
    void InitPushButtonGNSSMinFuncPointers();
    void InitFreqMeasPointers();

    void Item_clicked(QTableWidgetItem *tableItem);
    void Item_doubleClicked(QTableWidgetItem *tableItem);
    void freqDoubleClicked(QTableWidgetItem *tableItem);
    void moveFreqRow(QTableWidget *pTable, int currentRow, int toRow, int doubleClickFlag);
    void moveMeasColumn(QTableWidget *pTable, int currentColumn, int toColumn, int doubleClickFlag);

    void on_pushButtonGPS_clicked();
    void on_pushButtonGalileo_clicked();
    void on_pushButtonGLONASS_clicked();
    void on_pushButtonGEO_clicked();
    void on_pushButtonBDS_clicked();
    void on_pushButtonQZSS_clicked();
    void on_pushButtonIRNSS_clicked();

    //GPS
    void SetDefaultGPS();
    void on_checkBoxOrderFreqMeasGPS_clicked(bool checked);
    void on_pushButtonOrderFreqBoostGPS_clicked();
    void on_pushButtonOrderFreqLowerGPS_clicked();
    void on_pushButtonOrderMeasBoostGPS_clicked();
    void on_pushButtonOrderMeasLowerGPS_clicked();
    void on_pushButtonOrderFreqCodeBoostGPS_clicked();
    void on_pushButtonOrderFreqCodeLowerGPS_clicked();
    void on_pushButtonOrderMeasCodeBoostGPS_clicked();
    void on_pushButtonOrderMeasCodeLowerGPS_clicked();
    void on_pushButtonOrderFreqPhaseBoostGPS_clicked();
    void on_pushButtonOrderFreqPhaseLowerGPS_clicked();
    void on_pushButtonOrderMeasPhaseBoostGPS_clicked();
    void on_pushButtonOrderMeasPhaseLowerGPS_clicked();
    void on_pushButtonOrderFreqDopplerBoostGPS_clicked();
    void on_pushButtonOrderFreqDopplerLowerGPS_clicked();
    void on_pushButtonOrderMeasDopplerBoostGPS_clicked();
    void on_pushButtonOrderMeasDopplerLowerGPS_clicked();
    //Galileo
    void SetDefaultGalileo();
    void on_checkBoxOrderFreqMeasGalileo_clicked(bool checked);
    void on_pushButtonOrderFreqBoostGalileo_clicked();
    void on_pushButtonOrderFreqLowerGalileo_clicked();
    void on_pushButtonOrderMeasBoostGalileo_clicked();
    void on_pushButtonOrderMeasLowerGalileo_clicked();
    void on_pushButtonOrderFreqCodeBoostGalileo_clicked();
    void on_pushButtonOrderFreqCodeLowerGalileo_clicked();
    void on_pushButtonOrderMeasCodeBoostGalileo_clicked();
    void on_pushButtonOrderMeasCodeLowerGalileo_clicked();
    void on_pushButtonOrderFreqPhaseBoostGalileo_clicked();
    void on_pushButtonOrderFreqPhaseLowerGalileo_clicked();
    void on_pushButtonOrderMeasPhaseBoostGalileo_clicked();
    void on_pushButtonOrderMeasPhaseLowerGalileo_clicked();
    void on_pushButtonOrderFreqDopplerBoostGalileo_clicked();
    void on_pushButtonOrderFreqDopplerLowerGalileo_clicked();
    void on_pushButtonOrderMeasDopplerBoostGalileo_clicked();
    void on_pushButtonOrderMeasDopplerLowerGalileo_clicked();
    //GLONASS
    void SetDefaultGLONASS();
    void on_checkBoxOrderFreqMeasGLONASS_clicked(bool checked);
    void on_pushButtonOrderFreqBoostGLONASS_clicked();
    void on_pushButtonOrderFreqLowerGLONASS_clicked();
    void on_pushButtonOrderMeasBoostGLONASS_clicked();
    void on_pushButtonOrderMeasLowerGLONASS_clicked();
    void on_pushButtonOrderFreqCodeBoostGLONASS_clicked();
    void on_pushButtonOrderFreqCodeLowerGLONASS_clicked();
    void on_pushButtonOrderMeasCodeBoostGLONASS_clicked();
    void on_pushButtonOrderMeasCodeLowerGLONASS_clicked();
    void on_pushButtonOrderFreqPhaseBoostGLONASS_clicked();
    void on_pushButtonOrderFreqPhaseLowerGLONASS_clicked();
    void on_pushButtonOrderMeasPhaseBoostGLONASS_clicked();
    void on_pushButtonOrderMeasPhaseLowerGLONASS_clicked();
    void on_pushButtonOrderFreqDopplerBoostGLONASS_clicked();
    void on_pushButtonOrderFreqDopplerLowerGLONASS_clicked();
    void on_pushButtonOrderMeasDopplerBoostGLONASS_clicked();
    void on_pushButtonOrderMeasDopplerLowerGLONASS_clicked();
    //GEO
    void SetDefaultGEO();
    void on_checkBoxOrderFreqMeasGEO_clicked(bool checked);
    void on_pushButtonOrderFreqBoostGEO_clicked();
    void on_pushButtonOrderFreqLowerGEO_clicked();
    void on_pushButtonOrderMeasBoostGEO_clicked();
    void on_pushButtonOrderMeasLowerGEO_clicked();
    void on_pushButtonOrderFreqCodeBoostGEO_clicked();
    void on_pushButtonOrderFreqCodeLowerGEO_clicked();
    void on_pushButtonOrderMeasCodeBoostGEO_clicked();
    void on_pushButtonOrderMeasCodeLowerGEO_clicked();
    void on_pushButtonOrderFreqPhaseBoostGEO_clicked();
    void on_pushButtonOrderFreqPhaseLowerGEO_clicked();
    void on_pushButtonOrderMeasPhaseBoostGEO_clicked();
    void on_pushButtonOrderMeasPhaseLowerGEO_clicked();
    void on_pushButtonOrderFreqDopplerBoostGEO_clicked();
    void on_pushButtonOrderFreqDopplerLowerGEO_clicked();
    void on_pushButtonOrderMeasDopplerBoostGEO_clicked();
    void on_pushButtonOrderMeasDopplerLowerGEO_clicked();
    //BDS
    void SetDefaultBDS();
    void on_checkBoxOrderFreqMeasBDS_clicked(bool checked);
    void on_pushButtonOrderFreqBoostBDS_clicked();
    void on_pushButtonOrderFreqLowerBDS_clicked();
    void on_pushButtonOrderMeasBoostBDS_clicked();
    void on_pushButtonOrderMeasLowerBDS_clicked();
    void on_pushButtonOrderFreqCodeBoostBDS_clicked();
    void on_pushButtonOrderFreqCodeLowerBDS_clicked();
    void on_pushButtonOrderMeasCodeBoostBDS_clicked();
    void on_pushButtonOrderMeasCodeLowerBDS_clicked();
    void on_pushButtonOrderFreqPhaseBoostBDS_clicked();
    void on_pushButtonOrderFreqPhaseLowerBDS_clicked();
    void on_pushButtonOrderMeasPhaseBoostBDS_clicked();
    void on_pushButtonOrderMeasPhaseLowerBDS_clicked();
    void on_pushButtonOrderFreqDopplerBoostBDS_clicked();
    void on_pushButtonOrderFreqDopplerLowerBDS_clicked();
    void on_pushButtonOrderMeasDopplerBoostBDS_clicked();
    void on_pushButtonOrderMeasDopplerLowerBDS_clicked();
    //QZSS
    void SetDefaultQZSS();
    void on_checkBoxOrderFreqMeasQZSS_clicked(bool checked);
    void on_pushButtonOrderFreqBoostQZSS_clicked();
    void on_pushButtonOrderFreqLowerQZSS_clicked();
    void on_pushButtonOrderMeasBoostQZSS_clicked();
    void on_pushButtonOrderMeasLowerQZSS_clicked();
    void on_pushButtonOrderFreqCodeBoostQZSS_clicked();
    void on_pushButtonOrderFreqCodeLowerQZSS_clicked();
    void on_pushButtonOrderMeasCodeBoostQZSS_clicked();
    void on_pushButtonOrderMeasCodeLowerQZSS_clicked();
    void on_pushButtonOrderFreqPhaseBoostQZSS_clicked();
    void on_pushButtonOrderFreqPhaseLowerQZSS_clicked();
    void on_pushButtonOrderMeasPhaseBoostQZSS_clicked();
    void on_pushButtonOrderMeasPhaseLowerQZSS_clicked();
    void on_pushButtonOrderFreqDopplerBoostQZSS_clicked();
    void on_pushButtonOrderFreqDopplerLowerQZSS_clicked();
    void on_pushButtonOrderMeasDopplerBoostQZSS_clicked();
    void on_pushButtonOrderMeasDopplerLowerQZSS_clicked();
    //IRNSS
    void SetDefaultIRNSS();
    void on_checkBoxOrderFreqMeasIRNSS_clicked(bool checked);
    void on_pushButtonOrderFreqBoostIRNSS_clicked();
    void on_pushButtonOrderFreqLowerIRNSS_clicked();
    void on_pushButtonOrderMeasBoostIRNSS_clicked();
    void on_pushButtonOrderMeasLowerIRNSS_clicked();
    void on_pushButtonOrderFreqCodeBoostIRNSS_clicked();
    void on_pushButtonOrderFreqCodeLowerIRNSS_clicked();
    void on_pushButtonOrderMeasCodeBoostIRNSS_clicked();
    void on_pushButtonOrderMeasCodeLowerIRNSS_clicked();
    void on_pushButtonOrderFreqPhaseBoostIRNSS_clicked();
    void on_pushButtonOrderFreqPhaseLowerIRNSS_clicked();
    void on_pushButtonOrderMeasPhaseBoostIRNSS_clicked();
    void on_pushButtonOrderMeasPhaseLowerIRNSS_clicked();
    void on_pushButtonOrderFreqDopplerBoostIRNSS_clicked();
    void on_pushButtonOrderFreqDopplerLowerIRNSS_clicked();
    void on_pushButtonOrderMeasDopplerBoostIRNSS_clicked();
    void on_pushButtonOrderMeasDopplerLowerIRNSS_clicked();

    void on_pushButtonFreqMeasOrderDefault_clicked();
    void on_pushButtonFreqMeasOrderOk_clicked();
    void on_pushButtonFreqMeasOrderCancel_clicked();

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

    void setFreqMeasdefaults();

    void changeCurrentPage();

    void getgLABOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);
    void loadgLABOptions(QString *warningString, QStringList *ParametersList, const int freqMeas);

private:
    Ui::GNSS_FreqMeas_Order *uiFreqMeas;
};

#endif // FREQMEAS_ORDER_H
