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
#ifndef ANTENNA_ADVANCED_H
#define ANTENNA_ADVANCED_H

#include <QDialog>
#include <QFile>
#include <QCloseEvent>
//#include <QDebug>
#include <QRadioButton>
#include <QComboBox>
#include "glab_const.h"

namespace Ui {
class GNSS_Antenna_Advanced;
}

class GNSS_Antenna_Advanced : public QDialog
{
    Q_OBJECT

public:
    explicit GNSS_Antenna_Advanced(QWidget *parent = nullptr);
    ~GNSS_Antenna_Advanced();

public:
    //This is a definition of a variable with a pointer to a function type "void" with no parameters for class gLAB_GUI
    typedef void (GNSS_Antenna_Advanced::*VoidNoParamFuncPointer)();
    //Declare array of pointers to pushButton of GERSCJI
    QPushButton *PushButtonGNSS[MAX_GNSS];
    //Declare array of pointer to pushButton GNSS SNR _clicked() functions
    VoidNoParamFuncPointer PushButtonGNSSFunctions[MAX_GNSS];
    //Declare array of pointers to Specify RadioButton GERSCJI
    QRadioButton *RadioGNSSSpecify[MAX_GNSS][MAX_GNSS_FREQ];
    //Declare array of pointers to Copy RadioButton GERSCJI
    QRadioButton *RadioGNSSCopyFrom[MAX_GNSS][MAX_GNSS_FREQ];
    //Declare array of pointers to LineEdit of frequency's NEU of GERSCJI
    QLineEdit *LineEditGNSSNEU[MAX_GNSS][MAX_GNSS_FREQ][3];
    //Declare array of pointers to comboBox of constellations GERSCJI
    QComboBox *ComboBoxAPCSameAsConst[MAX_GNSS][MAX_GNSS_FREQ];
    //Declare array of pointers to comboBox of frequencies per constellation GERSCJI
    QComboBox *ComboBoxAPCSameAsFreq[MAX_GNSS][MAX_GNSS_FREQ][MAX_GNSS];

    int OkFlag;

private slots:
    void InitPushButtonGNSSPointers();
    void InitPushButtonGNSSMinFuncPointers();
    void InitAPCPointers();



    void on_pushButtonGPS_clicked();
    void on_pushButtonGalileo_clicked();
    void on_pushButtonGLONASS_clicked();
    void on_pushButtonGEO_clicked();
    void on_pushButtonBDS_clicked();
    void on_pushButtonQZSS_clicked();
    void on_pushButtonIRNSS_clicked();

    //GPS
    void SetDefaultAPCGPS();
    void on_radioButtonAPCReadF1GPS_clicked();
    void on_radioButtonAPCSpecifyF1GPS_clicked();
    void on_radioButtonAPCCopyF1GPS_clicked();
    void on_radioButtonAPCReadF2GPS_clicked();
    void on_radioButtonAPCCopyF2GPS_clicked();
    void on_radioButtonAPCSpecifyF2GPS_clicked();
    void on_radioButtonAPCReadF5GPS_clicked();
    void on_radioButtonAPCSpecifyF5GPS_clicked();
    void on_radioButtonAPCCopyF5GPS_clicked();
    void on_comboBoxAPCSameAsGPSF1Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsGPSF2Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsGPSF5Const_currentIndexChanged(int index);
    //Galileo
    void SetDefaultAPCGalileo();
    void on_radioButtonAPCReadF1Galileo_clicked();
    void on_radioButtonAPCSpecifyF1Galileo_clicked();
    void on_radioButtonAPCCopyF1Galileo_clicked();
    void on_radioButtonAPCReadF5Galileo_clicked();
    void on_radioButtonAPCSpecifyF5Galileo_clicked();
    void on_radioButtonAPCCopyF5Galileo_clicked();
    void on_radioButtonAPCReadF6Galileo_clicked();
    void on_radioButtonAPCSpecifyF6Galileo_clicked();
    void on_radioButtonAPCCopyF6Galileo_clicked();
    void on_radioButtonAPCReadF7Galileo_clicked();
    void on_radioButtonAPCSpecifyF7Galileo_clicked();
    void on_radioButtonAPCCopyF7Galileo_clicked();
    void on_radioButtonAPCReadF8Galileo_clicked();
    void on_radioButtonAPCSpecifyF8Galileo_clicked();
    void on_radioButtonAPCCopyF8Galileo_clicked();
    void on_comboBoxAPCSameAsGalileoF1Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsGalileoF5Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsGalileoF6Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsGalileoF7Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsGalileoF8Const_currentIndexChanged(int index);
    //GLONASS
    void SetDefaultAPCGLONASS();
    void on_radioButtonAPCReadF1GLONASS_clicked();
    void on_radioButtonAPCSpecifyF1GLONASS_clicked();
    void on_radioButtonAPCCopyF1GLONASS_clicked();
    void on_radioButtonAPCReadF2GLONASS_clicked();
    void on_radioButtonAPCSpecifyF2GLONASS_clicked();
    void on_radioButtonAPCCopyF2GLONASS_clicked();
    void on_radioButtonAPCReadF3GLONASS_clicked();
    void on_radioButtonAPCSpecifyF3GLONASS_clicked();
    void on_radioButtonAPCCopyF3GLONASS_clicked();
    void on_radioButtonAPCReadF4GLONASS_clicked();
    void on_radioButtonAPCSpecifyF4GLONASS_clicked();
    void on_radioButtonAPCCopyF4GLONASS_clicked();
    void on_radioButtonAPCReadF6GLONASS_clicked();
    void on_radioButtonAPCSpecifyF6GLONASS_clicked();
    void on_radioButtonAPCCopyF6GLONASS_clicked();
    void on_comboBoxAPCSameAsGLONASSF1Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsGLONASSF2Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsGLONASSF3Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsGLONASSF4Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsGLONASSF6Const_currentIndexChanged(int index);
    //GEO
    void SetDefaultAPCGEO();
    void on_radioButtonAPCReadF1GEO_clicked();
    void on_radioButtonAPCSpecifyF1GEO_clicked();
    void on_radioButtonAPCCopyF1GEO_clicked();
    void on_radioButtonAPCReadF5GEO_clicked();
    void on_radioButtonAPCCopyF5GEO_clicked();
    void on_radioButtonAPCSpecifyF5GEO_clicked();
    void on_comboBoxAPCSameAsGEOF1Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsGEOF5Const_currentIndexChanged(int index);
    //BDS
    void SetDefaultAPCBDS();
    void on_radioButtonAPCReadF1BDS_clicked();
    void on_radioButtonAPCSpecifyF1BDS_clicked();
    void on_radioButtonAPCCopyF1BDS_clicked();
    void on_radioButtonAPCReadF2BDS_clicked();
    void on_radioButtonAPCSpecifyF2BDS_clicked();
    void on_radioButtonAPCCopyF2BDS_clicked();
    void on_radioButtonAPCReadF5BDS_clicked();
    void on_radioButtonAPCSpecifyF5BDS_clicked();
    void on_radioButtonAPCCopyF5BDS_clicked();
    void on_radioButtonAPCReadF6BDS_clicked();
    void on_radioButtonAPCSpecifyF6BDS_clicked();
    void on_radioButtonAPCCopyF6BDS_clicked();
    void on_radioButtonAPCReadF7BDS_clicked();
    void on_radioButtonAPCSpecifyF7BDS_clicked();
    void on_radioButtonAPCCopyF7BDS_clicked();
    void on_radioButtonAPCReadF8BDS_clicked();
    void on_radioButtonAPCSpecifyF8BDS_clicked();
    void on_radioButtonAPCCopyF8BDS_clicked();
    void on_comboBoxAPCSameAsBDSF1Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsBDSF2Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsBDSF5Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsBDSF6Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsBDSF7Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsBDSF8Const_currentIndexChanged(int index);
    //QZSS
    void SetDefaultAPCQZSS();
    void on_radioButtonAPCReadF1QZSS_clicked();
    void on_radioButtonAPCSpecifyF1QZSS_clicked();
    void on_radioButtonAPCCopyF1QZSS_clicked();
    void on_radioButtonAPCReadF2QZSS_clicked();
    void on_radioButtonAPCSpecifyF2QZSS_clicked();
    void on_radioButtonAPCCopyF2QZSS_clicked();
    void on_radioButtonAPCReadF5QZSS_clicked();
    void on_radioButtonAPCSpecifyF5QZSS_clicked();
    void on_radioButtonAPCCopyF5QZSS_clicked();
    void on_radioButtonAPCReadF6QZSS_clicked();
    void on_radioButtonAPCSpecifyF6QZSS_clicked();
    void on_radioButtonAPCCopyF6QZSS_clicked();
    void on_comboBoxAPCSameAsQZSSF1Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsQZSSF2Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsQZSSF5Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsQZSSF6Const_currentIndexChanged(int index);
    //IRNSS
    void SetDefaultAPCIRNSS();
    void on_radioButtonAPCReadF5IRNSS_clicked();
    void on_radioButtonAPCSpecifyF5IRNSS_clicked();
    void on_radioButtonAPCCopyF5IRNSS_clicked();
    void on_radioButtonAPCReadF9IRNSS_clicked();
    void on_radioButtonAPCSpecifyF9IRNSS_clicked();
    void on_radioButtonAPCCopyF9IRNSS_clicked();
    void on_comboBoxAPCSameAsIRNSSF5Const_currentIndexChanged(int index);
    void on_comboBoxAPCSameAsIRNSSF9Const_currentIndexChanged(int index);

    void on_pushButtonAntAdvancedDefault_clicked();
    void on_pushButtonAntAdvancedOk_clicked();
    void on_pushButtonAntAdvancedCancel_clicked();

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

    void setAPCdefaults();

    void changeCurrentPage();

    void getgLABOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString);
    void loadgLABOptions(QString *warningString, QStringList *ParametersList);

private:
    Ui::GNSS_Antenna_Advanced *UiAntenna;
};

#endif // ANTENNA_ADVANCED_H
