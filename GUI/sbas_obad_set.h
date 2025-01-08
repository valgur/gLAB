#ifndef SBAS_OBAD_SET_H
#define SBAS_OBAD_SET_H

#include <QDialog>
#include <QFile>
#include <QRadioButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include "glab_const.h"

namespace Ui {
class GNSS_SBAS_OBAD_Set;
}

class GNSS_SBAS_OBAD_Set : public QDialog
{
    Q_OBJECT

public:
    explicit GNSS_SBAS_OBAD_Set(QWidget *parent = nullptr);
    ~GNSS_SBAS_OBAD_Set();

public:
    //Declare array of pointers to LineEdit of OBAD of GERSCJI
    QRadioButton *RadioButtonGNSSOBAD[MAX_GNSS][6];
    //Declare array of pointers to LineEdit of OBAD of GERSCJI
    QLineEdit *LineEditGNSSOBAD[MAX_GNSS][3];

    int OkFlag;

private slots:
    void InitOBADPointers();

    //GPS
    void on_radioButtonIcorrOBADReadMT37GPS_clicked();
    void on_radioButtonIcorrOBADUserDefinedGPS_clicked();
    void on_radioButtonCcorrOBADReadMT37GPS_clicked();
    void on_radioButtonCcorrOBADUserDefinedGPS_clicked();
    void on_radioButtonRcorrOBADReadMT37GPS_clicked();
    void on_radioButtonRcorrOBADUserDefinedGPS_clicked();
    //Galileo
    void on_radioButtonIcorrOBADReadMT37Galileo_clicked();
    void on_radioButtonIcorrOBADUserDefinedGalileo_clicked();
    void on_radioButtonCcorrOBADReadMT37Galileo_clicked();
    void on_radioButtonCcorrOBADUserDefinedGalileo_clicked();
    void on_radioButtonRcorrOBADReadMT37Galileo_clicked();
    void on_radioButtonRcorrOBADUserDefinedGalileo_clicked();
    //GLONASS
    void on_radioButtonIcorrOBADReadMT37GLONASS_clicked();
    void on_radioButtonIcorrOBADUserDefinedGLONASS_clicked();
    void on_radioButtonCcorrOBADReadMT37GLONASS_clicked();
    void on_radioButtonCcorrOBADUserDefinedGLONASS_clicked();
    void on_radioButtonRcorrOBADReadMT37GLONASS_clicked();
    void on_radioButtonRcorrOBADUserDefinedGLONASS_clicked();
    //GEO
    void on_radioButtonIcorrOBADReadMT37GEO_clicked();
    void on_radioButtonIcorrOBADUserDefinedGEO_clicked();
    void on_radioButtonCcorrOBADReadMT37GEO_clicked();
    void on_radioButtonCcorrOBADUserDefinedGEO_clicked();
    void on_radioButtonRcorrOBADReadMT37GEO_clicked();
    void on_radioButtonRcorrOBADUserDefinedGEO_clicked();
    //BDS
    void on_radioButtonIcorrOBADReadMT37BDS_clicked();
    void on_radioButtonIcorrOBADUserDefinedBDS_clicked();
    void on_radioButtonCcorrOBADReadMT37BDS_clicked();
    void on_radioButtonCcorrOBADUserDefinedBDS_clicked();
    void on_radioButtonRcorrOBADReadMT37BDS_clicked();
    void on_radioButtonRcorrOBADUserDefinedBDS_clicked();
    //QZSS
    void on_radioButtonIcorrOBADReadMT37QZSS_clicked();
    void on_radioButtonIcorrOBADUserDefinedQZSS_clicked();
    void on_radioButtonCcorrOBADReadMT37QZSS_clicked();
    void on_radioButtonCcorrOBADUserDefinedQZSS_clicked();
    void on_radioButtonRcorrOBADReadMT37QZSS_clicked();
    void on_radioButtonRcorrOBADUserDefinedQZSS_clicked();
    //IRNSS
    void on_radioButtonIcorrOBADReadMT37IRNSS_clicked();
    void on_radioButtonIcorrOBADUserDefinedIRNSS_clicked();
    void on_radioButtonCcorrOBADReadMT37IRNSS_clicked();
    void on_radioButtonCcorrOBADUserDefinedIRNSS_clicked();
    void on_radioButtonRcorrOBADReadMT37IRNSS_clicked();
    void on_radioButtonRcorrOBADUserDefinedIRNSS_clicked();

    void on_pushButtonSBASOBADAdvancedDefault_clicked();
    void on_pushButtonSBASOBADAdvancedOk_clicked();

public:
    void setGPS(bool checked);
    void setGalileo(bool checked);
    void setGLONASS(bool checked);
    void setGEO(bool checked);
    void setBDS(bool checked);
    void setQZSS(bool checked);
    void setIRNSS(bool checked);

    void setOBADDefaults();
    void setCurrentOBADPageDefaults();

    void changePage(int iPage);

    void getgLABOptions(const int optionType, QString *errorString, QString *warningString, QString *saveString, QStringList *runString);
    void loadgLABOptions(const int optionType, QString *warningString, QStringList *ParametersList);

private:
    Ui::GNSS_SBAS_OBAD_Set *uiSBASOBAD;

    int OBADOK[3];
    QString OBADOptions[3][MAX_GNSS];
};

#endif // SBAS_OBAD_SET_H
