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

#include "snr_advanced.h"
#include "ui_snr_advanced.h"

GNSS_SNR_Advanced::GNSS_SNR_Advanced(QWidget *parent) :
    QDialog(parent),
    uiSNR(new Ui::GNSS_SNR_Advanced)
{
    uiSNR->setupUi(this);
    OkFlag=0;

    // Set StyleSheet
    #if (defined Q_OS_WIN32)
        QFile qss(":/data/WinStyle.qss");
        qss.open(QFile::ReadOnly);
        this->setStyleSheet("QPushButton{border-radius: 2px; padding: 3px; width: 70px;}\
                             QPushButton:enabled{background-color:rgb(235,235,245); color:black;border: 1px solid rgb(124,124,124);}\
                             QPushButton:disabled{background-color:rgb(203,203,203); color:rgb(156,156,156);border: 1px solid rgb(185,185,185);}\
                             QPushButton:checked{background-color:rgb(173,216,230); color:black;border: 1px solid rgb(124,124,124);}"+qss.readAll());
        qss.close();
    #elif (defined Q_OS_MAC)
        QFile qss(":/data/MacStyle.qss");
        qss.open(QFile::ReadOnly);
        this->setStyleSheet(qss.readAll());
        qss.close();
    #else
        QFile qss(":/data/LinuxStyle.qss");
        qss.open(QFile::ReadOnly);
        this->setStyleSheet(qss.readAll());
        qss.close();
    #endif

    QLocale qlocale(QLocale::C);
    qlocale.setNumberOptions(QLocale::RejectGroupSeparator);
    auto lSNR = new QDoubleValidator(1, 99, 1,this);
    lSNR->setLocale(qlocale); // lineEdit validation for SNR

    //Min SNR Advanced Mode
    if (MinorMax==MINSNRTYPE){
        uiSNR->stackedWidgetSNRGNSS->setCurrentIndex(0);
        this->setWindowTitle("Minimum SNR Advanced Configuration");
    } else if (MinorMax==MAXSNRTYPE){
        uiSNR->stackedWidgetSNRGNSS->setCurrentIndex(1);
        this->setWindowTitle("Maximum SNR Advanced Configuration");
    }

    //Init variable with pointers to PushButtons pointers
    this->InitPushButtonGNSSPointers();
    //Init variable with pointers to ComboBox of default min/max SNR of GERSCJI
    this->InitComboBoxGNSSDefaultSNRPointers();
    //Init variable with pointers to LineEdit of default min/max SNR of GERSCJI
    this->InitLineEditGNSSDefaultSNRPointers();
    //Init variable with pointers to masurement ComboBox pointers
    this->InitComboBoxGNSSMeasPointers();
    //Init variable with pointers to SNR ComboBox pointers
    this->InitComboBoxGNSSSNRPointers();
    //Init variable with pointers to SNR LineEdit pointers
    this->InitLineEditGNSSSNRPointers();
    //Init variable with pointers to PushButtons function pointers
    this->InitPushButtonGNSSMinFuncPointers();

    //GPS
    uiSNR->lineEditUserDefinedSNRMinGPS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMinGPS_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinGPS->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGPS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeGPS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGPS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeGPS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeGPS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF2CodeGPS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeGPS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF2CodeGPS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGPS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeGPS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGPS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeGPS_2->setText("");

    uiSNR->lineEditUserDefinedSNRMaxGPS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMaxGPS_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxGPS->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGPS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeGPS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGPS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeGPS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeGPS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF2CodeGPS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeGPS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF2CodeGPS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGPS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeGPS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGPS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeGPS_2->setText("");

    //Galileo
    uiSNR->lineEditUserDefinedSNRMinGalileo->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMinGalileo_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinGalileo->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF6CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF6CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMinSpecificF7CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF7CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMinSpecificF7CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF7CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMinSpecificF8CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF8CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMinSpecificF8CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF8CodeGalileo_2->setText("");

    uiSNR->lineEditUserDefinedSNRMaxGalileo->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMaxGalileo_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxGalileo->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF6CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF6CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF7CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF7CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF7CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF7CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF8CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF8CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF8CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF8CodeGalileo_2->setText("");

    //GLONASS
    uiSNR->lineEditUserDefinedSNRMinGLONASS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMinGLONASS_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinGLONASS->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF2CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF2CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF3CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF3CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF3CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF3CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF4CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF4CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF4CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF4CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF6CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF6CodeGLONASS_2->setText("");

    uiSNR->lineEditUserDefinedSNRMaxGLONASS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMaxGLONASS_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxGLONASS->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF2CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF2CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF3CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF3CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF3CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF3CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF4CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF4CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF4CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF4CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF6CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF6CodeGLONASS_2->setText("");

    //GEO
    uiSNR->lineEditUserDefinedSNRMinGEO->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMinGEO_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinGEO->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGEO_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeGEO_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGEO_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeGEO_2->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGEO_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeGEO_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGEO_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeGEO_2->setText("");

    uiSNR->lineEditUserDefinedSNRMaxGEO->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMaxGEO_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxGEO->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGEO_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeGEO_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGEO_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeGEO_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGEO_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeGEO_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGEO_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeGEO_2->setText("");

    //BDS
    uiSNR->lineEditUserDefinedSNRMinBDS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMinBDS_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinBDS->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF2CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF2CodeBDS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF7CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF7CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF7CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF7CodeBDS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF6CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF6CodeBDS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeBDS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeBDS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF8CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF8CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF8CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF8CodeBDS_2->setText("");

    uiSNR->lineEditUserDefinedSNRMaxBDS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMaxBDS_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxBDS->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF2CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF2CodeBDS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF7CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF7CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF7CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF7CodeBDS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF6CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF6CodeBDS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeBDS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeBDS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF8CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF8CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF8CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF8CodeBDS_2->setText("");

    //QZSS
    uiSNR->lineEditUserDefinedSNRMinQZSS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMinQZSS_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinQZSS->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeQZSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeQZSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeQZSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF2CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeQZSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF2CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeQZSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeQZSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeQZSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF6CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeQZSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF6CodeQZSS_2->setText("");

    uiSNR->lineEditUserDefinedSNRMaxQZSS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMaxQZSS_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxQZSS->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeQZSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeQZSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeQZSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF2CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeQZSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF2CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeQZSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeQZSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeQZSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF6CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeQZSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF6CodeQZSS_2->setText("");

    //IRNSS
    uiSNR->lineEditUserDefinedSNRMinIRNSS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMinIRNSS_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinIRNSS->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeIRNSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeIRNSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeIRNSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeIRNSS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF9CodeIRNSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF9CodeIRNSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF9CodeIRNSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF9CodeIRNSS_2->setText("");

    uiSNR->lineEditUserDefinedSNRMaxIRNSS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMaxIRNSS_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxIRNSS->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeIRNSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeIRNSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeIRNSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeIRNSS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF9CodeIRNSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF9CodeIRNSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF9CodeIRNSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF9CodeIRNSS_2->setText("");

    uiSNR->pushButtonSNRAdvancedOk->setFocus();

}

GNSS_SNR_Advanced::GNSS_SNR_Advanced(QWidget *parent,int setMinorMax) :
    QDialog(parent),
    uiSNR(new Ui::GNSS_SNR_Advanced)
{
    uiSNR->setupUi(this);
    OkFlag=0;
    MinorMax=setMinorMax;

    // Set StyleSheet
    #if (defined Q_OS_WIN32)
        QFile qss(":/data/WinStyle.qss");
        qss.open(QFile::ReadOnly);this->setStyleSheet("QPushButton{border-radius: 2px; padding: 3px; width: 70px;}\
                                                      QPushButton:enabled{background-color:rgb(235,235,245); color:black;border: 1px solid rgb(124,124,124);}\
                                                      QPushButton:disabled{background-color:rgb(203,203,203); color:rgb(156,156,156);border: 1px solid rgb(185,185,185);}\
                                                      QPushButton:checked{background-color:rgb(173,216,230); color:black;border: 1px solid rgb(124,124,124);}"+qss.readAll());
        qss.close();
    #elif (defined Q_OS_MAC)
        QFile qss(":/data/MacStyle.qss");
        qss.open(QFile::ReadOnly);
        this->setStyleSheet(qss.readAll());
        qss.close();
    #else
        QFile qss(":/data/LinuxStyle.qss");
        qss.open(QFile::ReadOnly);
        this->setStyleSheet(qss.readAll());
        qss.close();
    #endif

    QLocale qlocale(QLocale::C);
    qlocale.setNumberOptions(QLocale::RejectGroupSeparator);
    auto lSNR = new QDoubleValidator(1, 99, 1,this);
    lSNR->setLocale(qlocale); // lineEdit validation for SNR

    //Init variable with pointers to PushButtons pointers
    this->InitPushButtonGNSSPointers();
    //Init variable with pointers to ComboBox of default min/max SNR of GERSCJI
    this->InitComboBoxGNSSDefaultSNRPointers();
    //Init variable with pointers to LineEdit of default min/max SNR of GERSCJI
    this->InitLineEditGNSSDefaultSNRPointers();
    //Init variable with pointers to masurement ComboBox pointers
    this->InitComboBoxGNSSMeasPointers();
    //Init variable with pointers to SNR ComboBox pointers
    this->InitComboBoxGNSSSNRPointers();
    //Init variable with pointers to SNR LineEdit pointers
    this->InitLineEditGNSSSNRPointers();
    //Init variable with pointers to PushButtons function pointers
    this->InitPushButtonGNSSMinFuncPointers();

    //Min SNR Advanced Mode
    if (MinorMax==MINSNRTYPE){
        uiSNR->stackedWidgetSNRGNSS->setCurrentIndex(0);
        this->setWindowTitle("Minimum SNR Advanced Configuration");
    } else if (MinorMax==MAXSNRTYPE){
        uiSNR->stackedWidgetSNRGNSS->setCurrentIndex(1);
        this->setWindowTitle("Maximum SNR Advanced Configuration");
    }

    //GPS
    uiSNR->lineEditUserDefinedSNRMinGPS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMinGPS_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinGPS->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGPS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeGPS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGPS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeGPS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeGPS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF2CodeGPS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeGPS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF2CodeGPS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGPS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeGPS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGPS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeGPS_2->setText("");

    uiSNR->lineEditUserDefinedSNRMaxGPS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMaxGPS_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxGPS->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGPS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeGPS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGPS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeGPS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeGPS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF2CodeGPS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeGPS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF2CodeGPS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGPS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeGPS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGPS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeGPS_2->setText("");

    //Galileo
    uiSNR->lineEditUserDefinedSNRMinGalileo->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMinGalileo_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinGalileo->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF6CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF6CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMinSpecificF7CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF7CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMinSpecificF7CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF7CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMinSpecificF8CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF8CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMinSpecificF8CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF8CodeGalileo_2->setText("");

    uiSNR->lineEditUserDefinedSNRMaxGalileo->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMaxGalileo_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxGalileo->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF6CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF6CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF7CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF7CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF7CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF7CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF8CodeGalileo_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF8CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF8CodeGalileo_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF8CodeGalileo_2->setText("");

    //GLONASS
    uiSNR->lineEditUserDefinedSNRMinGLONASS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMinGLONASS_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinGLONASS->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF2CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF2CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF3CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF3CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF3CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF3CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF4CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF4CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF4CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF4CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF6CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF6CodeGLONASS_2->setText("");

    uiSNR->lineEditUserDefinedSNRMaxGLONASS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMaxGLONASS_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxGLONASS->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF2CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF2CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF3CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF3CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF3CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF3CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF4CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF4CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF4CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF4CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeGLONASS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF6CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeGLONASS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF6CodeGLONASS_2->setText("");

    //GEO
    uiSNR->lineEditUserDefinedSNRMinGEO->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMinGEO_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinGEO->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGEO_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeGEO_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGEO_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeGEO_2->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGEO_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeGEO_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGEO_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeGEO_2->setText("");

    uiSNR->lineEditUserDefinedSNRMaxGEO->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMaxGEO_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxGEO->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGEO_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeGEO_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGEO_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeGEO_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGEO_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeGEO_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGEO_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeGEO_2->setText("");

    //BDS
    uiSNR->lineEditUserDefinedSNRMinBDS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMinBDS_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinBDS->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF2CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF2CodeBDS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF7CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF7CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF7CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF7CodeBDS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF6CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF6CodeBDS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeBDS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeBDS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF8CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF8CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF8CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF8CodeBDS_2->setText("");

    uiSNR->lineEditUserDefinedSNRMaxBDS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMaxBDS_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxBDS->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF2CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF2CodeBDS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF7CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF7CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF7CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF7CodeBDS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF6CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF6CodeBDS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeBDS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeBDS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF8CodeBDS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF8CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF8CodeBDS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF8CodeBDS_2->setText("");

    //QZSS
    uiSNR->lineEditUserDefinedSNRMinQZSS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMinQZSS_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinQZSS->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeQZSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeQZSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF1CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeQZSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF2CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeQZSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF2CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeQZSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeQZSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeQZSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF6CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeQZSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF6CodeQZSS_2->setText("");

    uiSNR->lineEditUserDefinedSNRMaxQZSS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMaxQZSS_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxQZSS->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeQZSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeQZSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF1CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeQZSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF2CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeQZSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF2CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeQZSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeQZSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeQZSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF6CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeQZSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF6CodeQZSS_2->setText("");

    //IRNSS
    uiSNR->lineEditUserDefinedSNRMinIRNSS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMinIRNSS_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinIRNSS->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeIRNSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeIRNSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeIRNSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF5CodeIRNSS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF9CodeIRNSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF9CodeIRNSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF9CodeIRNSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMinSpecificF9CodeIRNSS_2->setText("");

    uiSNR->lineEditUserDefinedSNRMaxIRNSS->setValidator(lSNR);
    this->on_comboBoxSNRThresholdsMaxIRNSS_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxIRNSS->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeIRNSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeIRNSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeIRNSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF5CodeIRNSS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF9CodeIRNSS_1->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF9CodeIRNSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF9CodeIRNSS_2->setValidator(lSNR);
    uiSNR->lineEditSNRMaxSpecificF9CodeIRNSS_2->setText("");

    uiSNR->pushButtonSNRAdvancedOk->setFocus();

    uiSNR->pushButtonSNRAdvancedCancel->setHidden(true); //Remove when Cancel buttons undo all changes made by the user
}

GNSS_SNR_Advanced::~GNSS_SNR_Advanced()
{
    delete uiSNR;
}

//Function to initialize pointers to CheckBox widget pointers
void GNSS_SNR_Advanced::InitPushButtonGNSSPointers(){
    PushButtonGNSS[GPS]=uiSNR->pushButtonGPS;
    PushButtonGNSS[Galileo]=uiSNR->pushButtonGalileo;
    PushButtonGNSS[GLONASS]=uiSNR->pushButtonGLONASS;
    PushButtonGNSS[GEO]=uiSNR->pushButtonGEO;
    PushButtonGNSS[BDS]=uiSNR->pushButtonBDS;
    PushButtonGNSS[QZSS]=uiSNR->pushButtonQZSS;
    PushButtonGNSS[IRNSS]=uiSNR->pushButtonIRNSS;
}
//Function to initialize pointers to Default SNR ComboBox widget pointers
void GNSS_SNR_Advanced::InitComboBoxGNSSDefaultSNRPointers(){
    //GPS Min
    ComboBoxGNSSDefaultSNR[0][GPS]=uiSNR->comboBoxSNRThresholdsMinGPS;
    //Galileo Min
    ComboBoxGNSSDefaultSNR[0][Galileo]=uiSNR->comboBoxSNRThresholdsMinGalileo;
    //GLONASS Min
    ComboBoxGNSSDefaultSNR[0][GLONASS]=uiSNR->comboBoxSNRThresholdsMinGLONASS;
    //GEO Min
    ComboBoxGNSSDefaultSNR[0][GEO]=uiSNR->comboBoxSNRThresholdsMinGEO;
    //BDS Min
    ComboBoxGNSSDefaultSNR[0][BDS]=uiSNR->comboBoxSNRThresholdsMinBDS;
    //QZSS Min
    ComboBoxGNSSDefaultSNR[0][QZSS]=uiSNR->comboBoxSNRThresholdsMinQZSS;
    //IRNSS Min
    ComboBoxGNSSDefaultSNR[0][IRNSS]=uiSNR->comboBoxSNRThresholdsMinIRNSS;
    //GPS Max
    ComboBoxGNSSDefaultSNR[1][GPS]=uiSNR->comboBoxSNRThresholdsMaxGPS;
    //Galileo Max
    ComboBoxGNSSDefaultSNR[1][Galileo]=uiSNR->comboBoxSNRThresholdsMaxGalileo;
    //GLONASS Max
    ComboBoxGNSSDefaultSNR[1][GLONASS]=uiSNR->comboBoxSNRThresholdsMaxGLONASS;
    //GEO Max
    ComboBoxGNSSDefaultSNR[1][GEO]=uiSNR->comboBoxSNRThresholdsMaxGEO;
    //BDS Max
    ComboBoxGNSSDefaultSNR[1][BDS]=uiSNR->comboBoxSNRThresholdsMaxBDS;
    //QZSS Max
    ComboBoxGNSSDefaultSNR[1][QZSS]=uiSNR->comboBoxSNRThresholdsMaxQZSS;
    //IRNSS Max
    ComboBoxGNSSDefaultSNR[1][IRNSS]=uiSNR->comboBoxSNRThresholdsMaxIRNSS;
}
//Function to initialize pointers to Default SNR LineEdit widget pointers
void GNSS_SNR_Advanced::InitLineEditGNSSDefaultSNRPointers(){
    //GPS Min
    LineEditGNSSDefaultSNR[0][GPS]=uiSNR->lineEditUserDefinedSNRMinGPS;
    //Galileo Min
    LineEditGNSSDefaultSNR[0][Galileo]=uiSNR->lineEditUserDefinedSNRMinGalileo;
    //GLONASS Min
    LineEditGNSSDefaultSNR[0][GLONASS]=uiSNR->lineEditUserDefinedSNRMinGLONASS;
    //GEO Min
    LineEditGNSSDefaultSNR[0][GEO]=uiSNR->lineEditUserDefinedSNRMinGEO;
    //BDS Min
    LineEditGNSSDefaultSNR[0][BDS]=uiSNR->lineEditUserDefinedSNRMinBDS;
    //QZSS Min
    LineEditGNSSDefaultSNR[0][QZSS]=uiSNR->lineEditUserDefinedSNRMinQZSS;
    //IRNSS Min
    LineEditGNSSDefaultSNR[0][IRNSS]=uiSNR->lineEditUserDefinedSNRMinIRNSS;
    //GPS Max
    LineEditGNSSDefaultSNR[1][GPS]=uiSNR->lineEditUserDefinedSNRMaxGPS;
    //Galileo Max
    LineEditGNSSDefaultSNR[1][Galileo]=uiSNR->lineEditUserDefinedSNRMaxGalileo;
    //GLONASS Max
    LineEditGNSSDefaultSNR[1][GLONASS]=uiSNR->lineEditUserDefinedSNRMaxGLONASS;
    //GEO Max
    LineEditGNSSDefaultSNR[1][GEO]=uiSNR->lineEditUserDefinedSNRMaxGEO;
    //BDS Max
    LineEditGNSSDefaultSNR[1][BDS]=uiSNR->lineEditUserDefinedSNRMaxBDS;
    //QZSS Max
    LineEditGNSSDefaultSNR[1][QZSS]=uiSNR->lineEditUserDefinedSNRMaxQZSS;
    //IRNSS Max
    LineEditGNSSDefaultSNR[1][IRNSS]=uiSNR->lineEditUserDefinedSNRMaxIRNSS;
}
//Function to initialize pointers to measurement ComboBox widget pointers
void GNSS_SNR_Advanced::InitComboBoxGNSSMeasPointers(){
    //GPS Min
    ComboBoxGNSSMeas[0][GPS][0][0]=uiSNR->comboBoxSNRMinMeasF1CodeGPS_1;
    ComboBoxGNSSMeas[0][GPS][0][1]=uiSNR->comboBoxSNRMinMeasF1CodeGPS_2;
    ComboBoxGNSSMeas[0][GPS][1][0]=uiSNR->comboBoxSNRMinMeasF2CodeGPS_1;
    ComboBoxGNSSMeas[0][GPS][1][1]=uiSNR->comboBoxSNRMinMeasF2CodeGPS_2;
    ComboBoxGNSSMeas[0][GPS][2][0]=uiSNR->comboBoxSNRMinMeasF5CodeGPS_1;
    ComboBoxGNSSMeas[0][GPS][2][1]=uiSNR->comboBoxSNRMinMeasF5CodeGPS_2;
    //Galileo Min
    ComboBoxGNSSMeas[0][Galileo][0][0]=uiSNR->comboBoxSNRMinMeasF1CodeGalileo_1;
    ComboBoxGNSSMeas[0][Galileo][0][1]=uiSNR->comboBoxSNRMinMeasF1CodeGalileo_2;
    ComboBoxGNSSMeas[0][Galileo][1][0]=uiSNR->comboBoxSNRMinMeasF5CodeGalileo_1;
    ComboBoxGNSSMeas[0][Galileo][1][1]=uiSNR->comboBoxSNRMinMeasF5CodeGalileo_2;
    ComboBoxGNSSMeas[0][Galileo][2][0]=uiSNR->comboBoxSNRMinMeasF6CodeGalileo_1;
    ComboBoxGNSSMeas[0][Galileo][2][1]=uiSNR->comboBoxSNRMinMeasF6CodeGalileo_2;
    ComboBoxGNSSMeas[0][Galileo][3][0]=uiSNR->comboBoxSNRMinMeasF7CodeGalileo_1;
    ComboBoxGNSSMeas[0][Galileo][3][1]=uiSNR->comboBoxSNRMinMeasF7CodeGalileo_2;
    ComboBoxGNSSMeas[0][Galileo][4][0]=uiSNR->comboBoxSNRMinMeasF8CodeGalileo_1;
    ComboBoxGNSSMeas[0][Galileo][4][1]=uiSNR->comboBoxSNRMinMeasF8CodeGalileo_2;
    //GLONASS Min
    ComboBoxGNSSMeas[0][GLONASS][0][0]=uiSNR->comboBoxSNRMinMeasF1CodeGLONASS_1;
    ComboBoxGNSSMeas[0][GLONASS][0][1]=uiSNR->comboBoxSNRMinMeasF1CodeGLONASS_2;
    ComboBoxGNSSMeas[0][GLONASS][1][0]=uiSNR->comboBoxSNRMinMeasF2CodeGLONASS_1;
    ComboBoxGNSSMeas[0][GLONASS][1][1]=uiSNR->comboBoxSNRMinMeasF2CodeGLONASS_2;
    ComboBoxGNSSMeas[0][GLONASS][2][0]=uiSNR->comboBoxSNRMinMeasF3CodeGLONASS_1;
    ComboBoxGNSSMeas[0][GLONASS][2][1]=uiSNR->comboBoxSNRMinMeasF3CodeGLONASS_2;
    ComboBoxGNSSMeas[0][GLONASS][3][0]=uiSNR->comboBoxSNRMinMeasF4CodeGLONASS_1;
    ComboBoxGNSSMeas[0][GLONASS][3][1]=uiSNR->comboBoxSNRMinMeasF4CodeGLONASS_2;
    ComboBoxGNSSMeas[0][GLONASS][4][0]=uiSNR->comboBoxSNRMinMeasF6CodeGLONASS_1;
    ComboBoxGNSSMeas[0][GLONASS][4][1]=uiSNR->comboBoxSNRMinMeasF6CodeGLONASS_2;
    //GEO Min
    ComboBoxGNSSMeas[0][GEO][0][0]=uiSNR->comboBoxSNRMinMeasF1CodeGEO_1;
    ComboBoxGNSSMeas[0][GEO][0][1]=uiSNR->comboBoxSNRMinMeasF1CodeGEO_2;
    ComboBoxGNSSMeas[0][GEO][1][0]=uiSNR->comboBoxSNRMinMeasF5CodeGEO_1;
    ComboBoxGNSSMeas[0][GEO][1][1]=uiSNR->comboBoxSNRMinMeasF5CodeGEO_2;
    //BDS Min
    ComboBoxGNSSMeas[0][BDS][0][0]=uiSNR->comboBoxSNRMinMeasF1CodeBDS_1;
    ComboBoxGNSSMeas[0][BDS][0][1]=uiSNR->comboBoxSNRMinMeasF1CodeBDS_2;
    ComboBoxGNSSMeas[0][BDS][1][0]=uiSNR->comboBoxSNRMinMeasF2CodeBDS_1;
    ComboBoxGNSSMeas[0][BDS][1][1]=uiSNR->comboBoxSNRMinMeasF2CodeBDS_2;
    ComboBoxGNSSMeas[0][BDS][2][0]=uiSNR->comboBoxSNRMinMeasF5CodeBDS_1;
    ComboBoxGNSSMeas[0][BDS][2][1]=uiSNR->comboBoxSNRMinMeasF5CodeBDS_2;
    ComboBoxGNSSMeas[0][BDS][3][0]=uiSNR->comboBoxSNRMinMeasF6CodeBDS_1;
    ComboBoxGNSSMeas[0][BDS][3][1]=uiSNR->comboBoxSNRMinMeasF6CodeBDS_2;
    ComboBoxGNSSMeas[0][BDS][4][0]=uiSNR->comboBoxSNRMinMeasF7CodeBDS_1;
    ComboBoxGNSSMeas[0][BDS][4][1]=uiSNR->comboBoxSNRMinMeasF7CodeBDS_2;
    ComboBoxGNSSMeas[0][BDS][5][0]=uiSNR->comboBoxSNRMinMeasF8CodeBDS_1;
    ComboBoxGNSSMeas[0][BDS][5][1]=uiSNR->comboBoxSNRMinMeasF8CodeBDS_2;
    //QZSS Min
    ComboBoxGNSSMeas[0][QZSS][0][0]=uiSNR->comboBoxSNRMinMeasF1CodeQZSS_1;
    ComboBoxGNSSMeas[0][QZSS][0][1]=uiSNR->comboBoxSNRMinMeasF1CodeQZSS_2;
    ComboBoxGNSSMeas[0][QZSS][1][0]=uiSNR->comboBoxSNRMinMeasF2CodeQZSS_1;
    ComboBoxGNSSMeas[0][QZSS][1][1]=uiSNR->comboBoxSNRMinMeasF2CodeQZSS_2;
    ComboBoxGNSSMeas[0][QZSS][2][0]=uiSNR->comboBoxSNRMinMeasF5CodeQZSS_1;
    ComboBoxGNSSMeas[0][QZSS][2][1]=uiSNR->comboBoxSNRMinMeasF5CodeQZSS_2;
    ComboBoxGNSSMeas[0][QZSS][3][0]=uiSNR->comboBoxSNRMinMeasF6CodeQZSS_1;
    ComboBoxGNSSMeas[0][QZSS][3][1]=uiSNR->comboBoxSNRMinMeasF6CodeQZSS_2;
    //IRNSS Min
    ComboBoxGNSSMeas[0][IRNSS][0][0]=uiSNR->comboBoxSNRMinMeasF5CodeIRNSS_1;
    ComboBoxGNSSMeas[0][IRNSS][0][1]=uiSNR->comboBoxSNRMinMeasF5CodeIRNSS_2;
    ComboBoxGNSSMeas[0][IRNSS][1][0]=uiSNR->comboBoxSNRMinMeasF9CodeIRNSS_1;
    ComboBoxGNSSMeas[0][IRNSS][1][1]=uiSNR->comboBoxSNRMinMeasF9CodeIRNSS_2;

    //GPS Max
    ComboBoxGNSSMeas[1][GPS][0][0]=uiSNR->comboBoxSNRMaxMeasF1CodeGPS_1;
    ComboBoxGNSSMeas[1][GPS][0][1]=uiSNR->comboBoxSNRMaxMeasF1CodeGPS_2;
    ComboBoxGNSSMeas[1][GPS][1][0]=uiSNR->comboBoxSNRMaxMeasF2CodeGPS_1;
    ComboBoxGNSSMeas[1][GPS][1][1]=uiSNR->comboBoxSNRMaxMeasF2CodeGPS_2;
    ComboBoxGNSSMeas[1][GPS][2][0]=uiSNR->comboBoxSNRMaxMeasF5CodeGPS_1;
    ComboBoxGNSSMeas[1][GPS][2][1]=uiSNR->comboBoxSNRMaxMeasF5CodeGPS_2;
    //Galileo Max
    ComboBoxGNSSMeas[1][Galileo][0][0]=uiSNR->comboBoxSNRMaxMeasF1CodeGalileo_1;
    ComboBoxGNSSMeas[1][Galileo][0][1]=uiSNR->comboBoxSNRMaxMeasF1CodeGalileo_2;
    ComboBoxGNSSMeas[1][Galileo][1][0]=uiSNR->comboBoxSNRMaxMeasF5CodeGalileo_1;
    ComboBoxGNSSMeas[1][Galileo][1][1]=uiSNR->comboBoxSNRMaxMeasF5CodeGalileo_2;
    ComboBoxGNSSMeas[1][Galileo][2][0]=uiSNR->comboBoxSNRMaxMeasF6CodeGalileo_1;
    ComboBoxGNSSMeas[1][Galileo][2][1]=uiSNR->comboBoxSNRMaxMeasF6CodeGalileo_2;
    ComboBoxGNSSMeas[1][Galileo][3][0]=uiSNR->comboBoxSNRMaxMeasF7CodeGalileo_1;
    ComboBoxGNSSMeas[1][Galileo][3][1]=uiSNR->comboBoxSNRMaxMeasF7CodeGalileo_2;
    ComboBoxGNSSMeas[1][Galileo][4][0]=uiSNR->comboBoxSNRMaxMeasF8CodeGalileo_1;
    ComboBoxGNSSMeas[1][Galileo][4][1]=uiSNR->comboBoxSNRMaxMeasF8CodeGalileo_2;
    //GLONASS Max
    ComboBoxGNSSMeas[1][GLONASS][0][0]=uiSNR->comboBoxSNRMaxMeasF1CodeGLONASS_1;
    ComboBoxGNSSMeas[1][GLONASS][0][1]=uiSNR->comboBoxSNRMaxMeasF1CodeGLONASS_2;
    ComboBoxGNSSMeas[1][GLONASS][1][0]=uiSNR->comboBoxSNRMaxMeasF2CodeGLONASS_1;
    ComboBoxGNSSMeas[1][GLONASS][1][1]=uiSNR->comboBoxSNRMaxMeasF2CodeGLONASS_2;
    ComboBoxGNSSMeas[1][GLONASS][2][0]=uiSNR->comboBoxSNRMaxMeasF3CodeGLONASS_1;
    ComboBoxGNSSMeas[1][GLONASS][2][1]=uiSNR->comboBoxSNRMaxMeasF3CodeGLONASS_2;
    ComboBoxGNSSMeas[1][GLONASS][3][0]=uiSNR->comboBoxSNRMaxMeasF4CodeGLONASS_1;
    ComboBoxGNSSMeas[1][GLONASS][3][1]=uiSNR->comboBoxSNRMaxMeasF4CodeGLONASS_2;
    ComboBoxGNSSMeas[1][GLONASS][4][0]=uiSNR->comboBoxSNRMaxMeasF6CodeGLONASS_1;
    ComboBoxGNSSMeas[1][GLONASS][4][1]=uiSNR->comboBoxSNRMaxMeasF6CodeGLONASS_2;
    //GEO Max
    ComboBoxGNSSMeas[1][GEO][0][0]=uiSNR->comboBoxSNRMaxMeasF1CodeGEO_1;
    ComboBoxGNSSMeas[1][GEO][0][1]=uiSNR->comboBoxSNRMaxMeasF1CodeGEO_2;
    ComboBoxGNSSMeas[1][GEO][1][0]=uiSNR->comboBoxSNRMaxMeasF5CodeGEO_1;
    ComboBoxGNSSMeas[1][GEO][1][1]=uiSNR->comboBoxSNRMaxMeasF5CodeGEO_2;
    //BDS Max
    ComboBoxGNSSMeas[1][BDS][0][0]=uiSNR->comboBoxSNRMaxMeasF1CodeBDS_1;
    ComboBoxGNSSMeas[1][BDS][0][1]=uiSNR->comboBoxSNRMaxMeasF1CodeBDS_2;
    ComboBoxGNSSMeas[1][BDS][1][0]=uiSNR->comboBoxSNRMaxMeasF2CodeBDS_1;
    ComboBoxGNSSMeas[1][BDS][1][1]=uiSNR->comboBoxSNRMaxMeasF2CodeBDS_2;
    ComboBoxGNSSMeas[1][BDS][2][0]=uiSNR->comboBoxSNRMaxMeasF5CodeBDS_1;
    ComboBoxGNSSMeas[1][BDS][2][1]=uiSNR->comboBoxSNRMaxMeasF5CodeBDS_2;
    ComboBoxGNSSMeas[1][BDS][3][0]=uiSNR->comboBoxSNRMaxMeasF6CodeBDS_1;
    ComboBoxGNSSMeas[1][BDS][3][1]=uiSNR->comboBoxSNRMaxMeasF6CodeBDS_2;
    ComboBoxGNSSMeas[1][BDS][4][0]=uiSNR->comboBoxSNRMaxMeasF7CodeBDS_1;
    ComboBoxGNSSMeas[1][BDS][4][1]=uiSNR->comboBoxSNRMaxMeasF7CodeBDS_2;
    ComboBoxGNSSMeas[1][BDS][5][0]=uiSNR->comboBoxSNRMaxMeasF8CodeBDS_1;
    ComboBoxGNSSMeas[1][BDS][5][1]=uiSNR->comboBoxSNRMaxMeasF8CodeBDS_2;
    //QZSS Max
    ComboBoxGNSSMeas[1][QZSS][0][0]=uiSNR->comboBoxSNRMaxMeasF1CodeQZSS_1;
    ComboBoxGNSSMeas[1][QZSS][0][1]=uiSNR->comboBoxSNRMaxMeasF1CodeQZSS_2;
    ComboBoxGNSSMeas[1][QZSS][1][0]=uiSNR->comboBoxSNRMaxMeasF2CodeQZSS_1;
    ComboBoxGNSSMeas[1][QZSS][1][1]=uiSNR->comboBoxSNRMaxMeasF2CodeQZSS_2;
    ComboBoxGNSSMeas[1][QZSS][2][0]=uiSNR->comboBoxSNRMaxMeasF5CodeQZSS_1;
    ComboBoxGNSSMeas[1][QZSS][2][1]=uiSNR->comboBoxSNRMaxMeasF5CodeQZSS_2;
    ComboBoxGNSSMeas[1][QZSS][3][0]=uiSNR->comboBoxSNRMaxMeasF6CodeQZSS_1;
    ComboBoxGNSSMeas[1][QZSS][3][1]=uiSNR->comboBoxSNRMaxMeasF6CodeQZSS_2;
    //IRNSS Max
    ComboBoxGNSSMeas[1][IRNSS][0][0]=uiSNR->comboBoxSNRMaxMeasF5CodeIRNSS_1;
    ComboBoxGNSSMeas[1][IRNSS][0][1]=uiSNR->comboBoxSNRMaxMeasF5CodeIRNSS_2;
    ComboBoxGNSSMeas[1][IRNSS][1][0]=uiSNR->comboBoxSNRMaxMeasF9CodeIRNSS_1;
    ComboBoxGNSSMeas[1][IRNSS][1][1]=uiSNR->comboBoxSNRMaxMeasF9CodeIRNSS_2;
}
//Function to initialize pointers to SNR ComboBox widget pointers
void GNSS_SNR_Advanced::InitComboBoxGNSSSNRPointers(){
    //GPS Min
    ComboBoxGNSSSNR[0][GPS][0][0]=uiSNR->comboBoxSNRMinSelectF1CodeGPS_1;
    ComboBoxGNSSSNR[0][GPS][0][1]=uiSNR->comboBoxSNRMinSelectF1CodeGPS_2;
    ComboBoxGNSSSNR[0][GPS][1][0]=uiSNR->comboBoxSNRMinSelectF2CodeGPS_1;
    ComboBoxGNSSSNR[0][GPS][1][1]=uiSNR->comboBoxSNRMinSelectF2CodeGPS_2;
    ComboBoxGNSSSNR[0][GPS][2][0]=uiSNR->comboBoxSNRMinSelectF5CodeGPS_1;
    ComboBoxGNSSSNR[0][GPS][2][1]=uiSNR->comboBoxSNRMinSelectF5CodeGPS_2;
    //Galileo Min
    ComboBoxGNSSSNR[0][Galileo][0][0]=uiSNR->comboBoxSNRMinSelectF1CodeGalileo_1;
    ComboBoxGNSSSNR[0][Galileo][0][1]=uiSNR->comboBoxSNRMinSelectF1CodeGalileo_2;
    ComboBoxGNSSSNR[0][Galileo][1][0]=uiSNR->comboBoxSNRMinSelectF5CodeGalileo_1;
    ComboBoxGNSSSNR[0][Galileo][1][1]=uiSNR->comboBoxSNRMinSelectF5CodeGalileo_2;
    ComboBoxGNSSSNR[0][Galileo][2][0]=uiSNR->comboBoxSNRMinSelectF6CodeGalileo_1;
    ComboBoxGNSSSNR[0][Galileo][2][1]=uiSNR->comboBoxSNRMinSelectF6CodeGalileo_2;
    ComboBoxGNSSSNR[0][Galileo][3][0]=uiSNR->comboBoxSNRMinSelectF7CodeGalileo_1;
    ComboBoxGNSSSNR[0][Galileo][3][1]=uiSNR->comboBoxSNRMinSelectF7CodeGalileo_2;
    ComboBoxGNSSSNR[0][Galileo][4][0]=uiSNR->comboBoxSNRMinSelectF8CodeGalileo_1;
    ComboBoxGNSSSNR[0][Galileo][4][1]=uiSNR->comboBoxSNRMinSelectF8CodeGalileo_2;
    //GLONASS Min
    ComboBoxGNSSSNR[0][GLONASS][0][0]=uiSNR->comboBoxSNRMinSelectF1CodeGLONASS_1;
    ComboBoxGNSSSNR[0][GLONASS][0][1]=uiSNR->comboBoxSNRMinSelectF1CodeGLONASS_2;
    ComboBoxGNSSSNR[0][GLONASS][1][0]=uiSNR->comboBoxSNRMinSelectF2CodeGLONASS_1;
    ComboBoxGNSSSNR[0][GLONASS][1][1]=uiSNR->comboBoxSNRMinSelectF2CodeGLONASS_2;
    ComboBoxGNSSSNR[0][GLONASS][2][0]=uiSNR->comboBoxSNRMinSelectF3CodeGLONASS_1;
    ComboBoxGNSSSNR[0][GLONASS][2][1]=uiSNR->comboBoxSNRMinSelectF3CodeGLONASS_2;
    ComboBoxGNSSSNR[0][GLONASS][3][0]=uiSNR->comboBoxSNRMinSelectF4CodeGLONASS_1;
    ComboBoxGNSSSNR[0][GLONASS][3][1]=uiSNR->comboBoxSNRMinSelectF4CodeGLONASS_2;
    ComboBoxGNSSSNR[0][GLONASS][4][0]=uiSNR->comboBoxSNRMinSelectF6CodeGLONASS_1;
    ComboBoxGNSSSNR[0][GLONASS][4][1]=uiSNR->comboBoxSNRMinSelectF6CodeGLONASS_2;
    //GEO Min
    ComboBoxGNSSSNR[0][GEO][0][0]=uiSNR->comboBoxSNRMinSelectF1CodeGEO_1;
    ComboBoxGNSSSNR[0][GEO][0][1]=uiSNR->comboBoxSNRMinSelectF1CodeGEO_2;
    ComboBoxGNSSSNR[0][GEO][1][0]=uiSNR->comboBoxSNRMinSelectF5CodeGEO_1;
    ComboBoxGNSSSNR[0][GEO][1][1]=uiSNR->comboBoxSNRMinSelectF5CodeGEO_2;
    //BDS Min
    ComboBoxGNSSSNR[0][BDS][0][0]=uiSNR->comboBoxSNRMinSelectF1CodeBDS_1;
    ComboBoxGNSSSNR[0][BDS][0][1]=uiSNR->comboBoxSNRMinSelectF1CodeBDS_2;
    ComboBoxGNSSSNR[0][BDS][1][0]=uiSNR->comboBoxSNRMinSelectF2CodeBDS_1;
    ComboBoxGNSSSNR[0][BDS][1][1]=uiSNR->comboBoxSNRMinSelectF2CodeBDS_2;
    ComboBoxGNSSSNR[0][BDS][2][0]=uiSNR->comboBoxSNRMinSelectF5CodeBDS_1;
    ComboBoxGNSSSNR[0][BDS][2][1]=uiSNR->comboBoxSNRMinSelectF5CodeBDS_2;
    ComboBoxGNSSSNR[0][BDS][3][0]=uiSNR->comboBoxSNRMinSelectF6CodeBDS_1;
    ComboBoxGNSSSNR[0][BDS][3][1]=uiSNR->comboBoxSNRMinSelectF6CodeBDS_2;
    ComboBoxGNSSSNR[0][BDS][4][0]=uiSNR->comboBoxSNRMinSelectF7CodeBDS_1;
    ComboBoxGNSSSNR[0][BDS][4][1]=uiSNR->comboBoxSNRMinSelectF7CodeBDS_2;
    ComboBoxGNSSSNR[0][BDS][5][0]=uiSNR->comboBoxSNRMinSelectF8CodeBDS_1;
    ComboBoxGNSSSNR[0][BDS][5][1]=uiSNR->comboBoxSNRMinSelectF8CodeBDS_2;
    //QZSS Min
    ComboBoxGNSSSNR[0][QZSS][0][0]=uiSNR->comboBoxSNRMinSelectF1CodeQZSS_1;
    ComboBoxGNSSSNR[0][QZSS][0][1]=uiSNR->comboBoxSNRMinSelectF1CodeQZSS_2;
    ComboBoxGNSSSNR[0][QZSS][1][0]=uiSNR->comboBoxSNRMinSelectF2CodeQZSS_1;
    ComboBoxGNSSSNR[0][QZSS][1][1]=uiSNR->comboBoxSNRMinSelectF2CodeQZSS_2;
    ComboBoxGNSSSNR[0][QZSS][2][0]=uiSNR->comboBoxSNRMinSelectF5CodeQZSS_1;
    ComboBoxGNSSSNR[0][QZSS][2][1]=uiSNR->comboBoxSNRMinSelectF5CodeQZSS_2;
    ComboBoxGNSSSNR[0][QZSS][3][0]=uiSNR->comboBoxSNRMinSelectF6CodeQZSS_1;
    ComboBoxGNSSSNR[0][QZSS][3][1]=uiSNR->comboBoxSNRMinSelectF6CodeQZSS_2;
    //IRNSS Min
    ComboBoxGNSSSNR[0][IRNSS][0][0]=uiSNR->comboBoxSNRMinSelectF5CodeIRNSS_1;
    ComboBoxGNSSSNR[0][IRNSS][0][1]=uiSNR->comboBoxSNRMinSelectF5CodeIRNSS_2;
    ComboBoxGNSSSNR[0][IRNSS][1][0]=uiSNR->comboBoxSNRMinSelectF9CodeIRNSS_1;
    ComboBoxGNSSSNR[0][IRNSS][1][1]=uiSNR->comboBoxSNRMinSelectF9CodeIRNSS_2;

    //GPS Max
    ComboBoxGNSSSNR[1][GPS][0][0]=uiSNR->comboBoxSNRMaxSelectF1CodeGPS_1;
    ComboBoxGNSSSNR[1][GPS][0][1]=uiSNR->comboBoxSNRMaxSelectF1CodeGPS_2;
    ComboBoxGNSSSNR[1][GPS][1][0]=uiSNR->comboBoxSNRMaxSelectF2CodeGPS_1;
    ComboBoxGNSSSNR[1][GPS][1][1]=uiSNR->comboBoxSNRMaxSelectF2CodeGPS_2;
    ComboBoxGNSSSNR[1][GPS][2][0]=uiSNR->comboBoxSNRMaxSelectF5CodeGPS_1;
    ComboBoxGNSSSNR[1][GPS][2][1]=uiSNR->comboBoxSNRMaxSelectF5CodeGPS_2;
    //Galileo Max
    ComboBoxGNSSSNR[1][Galileo][0][0]=uiSNR->comboBoxSNRMaxSelectF1CodeGalileo_1;
    ComboBoxGNSSSNR[1][Galileo][0][1]=uiSNR->comboBoxSNRMaxSelectF1CodeGalileo_2;
    ComboBoxGNSSSNR[1][Galileo][1][0]=uiSNR->comboBoxSNRMaxSelectF5CodeGalileo_1;
    ComboBoxGNSSSNR[1][Galileo][1][1]=uiSNR->comboBoxSNRMaxSelectF5CodeGalileo_2;
    ComboBoxGNSSSNR[1][Galileo][2][0]=uiSNR->comboBoxSNRMaxSelectF6CodeGalileo_1;
    ComboBoxGNSSSNR[1][Galileo][2][1]=uiSNR->comboBoxSNRMaxSelectF6CodeGalileo_2;
    ComboBoxGNSSSNR[1][Galileo][3][0]=uiSNR->comboBoxSNRMaxSelectF7CodeGalileo_1;
    ComboBoxGNSSSNR[1][Galileo][3][1]=uiSNR->comboBoxSNRMaxSelectF7CodeGalileo_2;
    ComboBoxGNSSSNR[1][Galileo][4][0]=uiSNR->comboBoxSNRMaxSelectF8CodeGalileo_1;
    ComboBoxGNSSSNR[1][Galileo][4][1]=uiSNR->comboBoxSNRMaxSelectF8CodeGalileo_2;
    //GLONASS Max
    ComboBoxGNSSSNR[1][GLONASS][0][0]=uiSNR->comboBoxSNRMaxSelectF1CodeGLONASS_1;
    ComboBoxGNSSSNR[1][GLONASS][0][1]=uiSNR->comboBoxSNRMaxSelectF1CodeGLONASS_2;
    ComboBoxGNSSSNR[1][GLONASS][1][0]=uiSNR->comboBoxSNRMaxSelectF2CodeGLONASS_1;
    ComboBoxGNSSSNR[1][GLONASS][1][1]=uiSNR->comboBoxSNRMaxSelectF2CodeGLONASS_2;
    ComboBoxGNSSSNR[1][GLONASS][2][0]=uiSNR->comboBoxSNRMaxSelectF3CodeGLONASS_1;
    ComboBoxGNSSSNR[1][GLONASS][2][1]=uiSNR->comboBoxSNRMaxSelectF3CodeGLONASS_2;
    ComboBoxGNSSSNR[1][GLONASS][3][0]=uiSNR->comboBoxSNRMaxSelectF4CodeGLONASS_1;
    ComboBoxGNSSSNR[1][GLONASS][3][1]=uiSNR->comboBoxSNRMaxSelectF4CodeGLONASS_2;
    ComboBoxGNSSSNR[1][GLONASS][4][0]=uiSNR->comboBoxSNRMaxSelectF6CodeGLONASS_1;
    ComboBoxGNSSSNR[1][GLONASS][4][1]=uiSNR->comboBoxSNRMaxSelectF6CodeGLONASS_2;
    //GEO Max
    ComboBoxGNSSSNR[1][GEO][0][0]=uiSNR->comboBoxSNRMaxSelectF1CodeGEO_1;
    ComboBoxGNSSSNR[1][GEO][0][1]=uiSNR->comboBoxSNRMaxSelectF1CodeGEO_2;
    ComboBoxGNSSSNR[1][GEO][1][0]=uiSNR->comboBoxSNRMaxSelectF5CodeGEO_1;
    ComboBoxGNSSSNR[1][GEO][1][1]=uiSNR->comboBoxSNRMaxSelectF5CodeGEO_2;
    //BDS Max
    ComboBoxGNSSSNR[1][BDS][0][0]=uiSNR->comboBoxSNRMaxSelectF1CodeBDS_1;
    ComboBoxGNSSSNR[1][BDS][0][1]=uiSNR->comboBoxSNRMaxSelectF1CodeBDS_2;
    ComboBoxGNSSSNR[1][BDS][1][0]=uiSNR->comboBoxSNRMaxSelectF2CodeBDS_1;
    ComboBoxGNSSSNR[1][BDS][1][1]=uiSNR->comboBoxSNRMaxSelectF2CodeBDS_2;
    ComboBoxGNSSSNR[1][BDS][2][0]=uiSNR->comboBoxSNRMaxSelectF5CodeBDS_1;
    ComboBoxGNSSSNR[1][BDS][2][1]=uiSNR->comboBoxSNRMaxSelectF5CodeBDS_2;
    ComboBoxGNSSSNR[1][BDS][3][0]=uiSNR->comboBoxSNRMaxSelectF6CodeBDS_1;
    ComboBoxGNSSSNR[1][BDS][3][1]=uiSNR->comboBoxSNRMaxSelectF6CodeBDS_2;
    ComboBoxGNSSSNR[1][BDS][4][0]=uiSNR->comboBoxSNRMaxSelectF7CodeBDS_1;
    ComboBoxGNSSSNR[1][BDS][4][1]=uiSNR->comboBoxSNRMaxSelectF7CodeBDS_2;
    ComboBoxGNSSSNR[1][BDS][5][0]=uiSNR->comboBoxSNRMaxSelectF8CodeBDS_1;
    ComboBoxGNSSSNR[1][BDS][5][1]=uiSNR->comboBoxSNRMaxSelectF8CodeBDS_2;
    //QZSS Max
    ComboBoxGNSSSNR[1][QZSS][0][0]=uiSNR->comboBoxSNRMaxSelectF1CodeQZSS_1;
    ComboBoxGNSSSNR[1][QZSS][0][1]=uiSNR->comboBoxSNRMaxSelectF1CodeQZSS_2;
    ComboBoxGNSSSNR[1][QZSS][1][0]=uiSNR->comboBoxSNRMaxSelectF2CodeQZSS_1;
    ComboBoxGNSSSNR[1][QZSS][1][1]=uiSNR->comboBoxSNRMaxSelectF2CodeQZSS_2;
    ComboBoxGNSSSNR[1][QZSS][2][0]=uiSNR->comboBoxSNRMaxSelectF5CodeQZSS_1;
    ComboBoxGNSSSNR[1][QZSS][2][1]=uiSNR->comboBoxSNRMaxSelectF5CodeQZSS_2;
    ComboBoxGNSSSNR[1][QZSS][3][0]=uiSNR->comboBoxSNRMaxSelectF6CodeQZSS_1;
    ComboBoxGNSSSNR[1][QZSS][3][1]=uiSNR->comboBoxSNRMaxSelectF6CodeQZSS_2;
    //IRNSS Max
    ComboBoxGNSSSNR[1][IRNSS][0][0]=uiSNR->comboBoxSNRMaxSelectF5CodeIRNSS_1;
    ComboBoxGNSSSNR[1][IRNSS][0][1]=uiSNR->comboBoxSNRMaxSelectF5CodeIRNSS_2;
    ComboBoxGNSSSNR[1][IRNSS][1][0]=uiSNR->comboBoxSNRMaxSelectF9CodeIRNSS_1;
    ComboBoxGNSSSNR[1][IRNSS][1][1]=uiSNR->comboBoxSNRMaxSelectF9CodeIRNSS_2;
}
//Function to initialize pointers to SNR LineEdit widget pointers
void GNSS_SNR_Advanced::InitLineEditGNSSSNRPointers(){
    //GPS Min
    LineEditGNSSSNR[0][GPS][0][0]=uiSNR->lineEditSNRMinSpecificF1CodeGPS_1;
    LineEditGNSSSNR[0][GPS][0][1]=uiSNR->lineEditSNRMinSpecificF1CodeGPS_2;
    LineEditGNSSSNR[0][GPS][1][0]=uiSNR->lineEditSNRMinSpecificF2CodeGPS_1;
    LineEditGNSSSNR[0][GPS][1][1]=uiSNR->lineEditSNRMinSpecificF2CodeGPS_2;
    LineEditGNSSSNR[0][GPS][2][0]=uiSNR->lineEditSNRMinSpecificF5CodeGPS_1;
    LineEditGNSSSNR[0][GPS][2][1]=uiSNR->lineEditSNRMinSpecificF5CodeGPS_2;
    //Galileo Min
    LineEditGNSSSNR[0][Galileo][0][0]=uiSNR->lineEditSNRMinSpecificF1CodeGalileo_1;
    LineEditGNSSSNR[0][Galileo][0][1]=uiSNR->lineEditSNRMinSpecificF1CodeGalileo_2;
    LineEditGNSSSNR[0][Galileo][1][0]=uiSNR->lineEditSNRMinSpecificF5CodeGalileo_1;
    LineEditGNSSSNR[0][Galileo][1][1]=uiSNR->lineEditSNRMinSpecificF5CodeGalileo_2;
    LineEditGNSSSNR[0][Galileo][2][0]=uiSNR->lineEditSNRMinSpecificF6CodeGalileo_1;
    LineEditGNSSSNR[0][Galileo][2][1]=uiSNR->lineEditSNRMinSpecificF6CodeGalileo_2;
    LineEditGNSSSNR[0][Galileo][3][0]=uiSNR->lineEditSNRMinSpecificF7CodeGalileo_1;
    LineEditGNSSSNR[0][Galileo][3][1]=uiSNR->lineEditSNRMinSpecificF7CodeGalileo_2;
    LineEditGNSSSNR[0][Galileo][4][0]=uiSNR->lineEditSNRMinSpecificF8CodeGalileo_1;
    LineEditGNSSSNR[0][Galileo][4][1]=uiSNR->lineEditSNRMinSpecificF8CodeGalileo_2;
    //GLONASS Min
    LineEditGNSSSNR[0][GLONASS][0][0]=uiSNR->lineEditSNRMinSpecificF1CodeGLONASS_1;
    LineEditGNSSSNR[0][GLONASS][0][1]=uiSNR->lineEditSNRMinSpecificF1CodeGLONASS_2;
    LineEditGNSSSNR[0][GLONASS][1][0]=uiSNR->lineEditSNRMinSpecificF2CodeGLONASS_1;
    LineEditGNSSSNR[0][GLONASS][1][1]=uiSNR->lineEditSNRMinSpecificF2CodeGLONASS_2;
    LineEditGNSSSNR[0][GLONASS][2][0]=uiSNR->lineEditSNRMinSpecificF3CodeGLONASS_1;
    LineEditGNSSSNR[0][GLONASS][2][1]=uiSNR->lineEditSNRMinSpecificF3CodeGLONASS_2;
    LineEditGNSSSNR[0][GLONASS][3][0]=uiSNR->lineEditSNRMinSpecificF4CodeGLONASS_1;
    LineEditGNSSSNR[0][GLONASS][3][1]=uiSNR->lineEditSNRMinSpecificF4CodeGLONASS_2;
    LineEditGNSSSNR[0][GLONASS][4][0]=uiSNR->lineEditSNRMinSpecificF6CodeGLONASS_1;
    LineEditGNSSSNR[0][GLONASS][4][1]=uiSNR->lineEditSNRMinSpecificF6CodeGLONASS_2;
    //GEO Min
    LineEditGNSSSNR[0][GEO][0][0]=uiSNR->lineEditSNRMinSpecificF1CodeGEO_1;
    LineEditGNSSSNR[0][GEO][0][1]=uiSNR->lineEditSNRMinSpecificF1CodeGEO_2;
    LineEditGNSSSNR[0][GEO][1][0]=uiSNR->lineEditSNRMinSpecificF5CodeGEO_1;
    LineEditGNSSSNR[0][GEO][1][1]=uiSNR->lineEditSNRMinSpecificF5CodeGEO_2;
    //BDS Min
    LineEditGNSSSNR[0][BDS][0][0]=uiSNR->lineEditSNRMinSpecificF1CodeBDS_1;
    LineEditGNSSSNR[0][BDS][0][1]=uiSNR->lineEditSNRMinSpecificF1CodeBDS_2;
    LineEditGNSSSNR[0][BDS][1][0]=uiSNR->lineEditSNRMinSpecificF2CodeBDS_1;
    LineEditGNSSSNR[0][BDS][1][1]=uiSNR->lineEditSNRMinSpecificF2CodeBDS_2;
    LineEditGNSSSNR[0][BDS][2][0]=uiSNR->lineEditSNRMinSpecificF5CodeBDS_1;
    LineEditGNSSSNR[0][BDS][2][1]=uiSNR->lineEditSNRMinSpecificF5CodeBDS_2;
    LineEditGNSSSNR[0][BDS][3][0]=uiSNR->lineEditSNRMinSpecificF6CodeBDS_1;
    LineEditGNSSSNR[0][BDS][3][1]=uiSNR->lineEditSNRMinSpecificF6CodeBDS_2;
    LineEditGNSSSNR[0][BDS][4][0]=uiSNR->lineEditSNRMinSpecificF7CodeBDS_1;
    LineEditGNSSSNR[0][BDS][4][1]=uiSNR->lineEditSNRMinSpecificF7CodeBDS_2;
    LineEditGNSSSNR[0][BDS][5][0]=uiSNR->lineEditSNRMinSpecificF8CodeBDS_1;
    LineEditGNSSSNR[0][BDS][5][1]=uiSNR->lineEditSNRMinSpecificF8CodeBDS_2;
    //QZSS Min
    LineEditGNSSSNR[0][QZSS][0][0]=uiSNR->lineEditSNRMinSpecificF1CodeQZSS_1;
    LineEditGNSSSNR[0][QZSS][0][1]=uiSNR->lineEditSNRMinSpecificF1CodeQZSS_2;
    LineEditGNSSSNR[0][QZSS][1][0]=uiSNR->lineEditSNRMinSpecificF2CodeQZSS_1;
    LineEditGNSSSNR[0][QZSS][1][1]=uiSNR->lineEditSNRMinSpecificF2CodeQZSS_2;
    LineEditGNSSSNR[0][QZSS][2][0]=uiSNR->lineEditSNRMinSpecificF5CodeQZSS_1;
    LineEditGNSSSNR[0][QZSS][2][1]=uiSNR->lineEditSNRMinSpecificF5CodeQZSS_2;
    LineEditGNSSSNR[0][QZSS][3][0]=uiSNR->lineEditSNRMinSpecificF6CodeQZSS_1;
    LineEditGNSSSNR[0][QZSS][3][1]=uiSNR->lineEditSNRMinSpecificF6CodeQZSS_2;
    //IRNSS Min
    LineEditGNSSSNR[0][IRNSS][0][0]=uiSNR->lineEditSNRMinSpecificF5CodeIRNSS_1;
    LineEditGNSSSNR[0][IRNSS][0][1]=uiSNR->lineEditSNRMinSpecificF5CodeIRNSS_2;
    LineEditGNSSSNR[0][IRNSS][1][0]=uiSNR->lineEditSNRMinSpecificF9CodeIRNSS_1;
    LineEditGNSSSNR[0][IRNSS][1][1]=uiSNR->lineEditSNRMinSpecificF9CodeIRNSS_2;

    //GPS Max
    LineEditGNSSSNR[1][GPS][0][0]=uiSNR->lineEditSNRMaxSpecificF1CodeGPS_1;
    LineEditGNSSSNR[1][GPS][0][1]=uiSNR->lineEditSNRMaxSpecificF1CodeGPS_2;
    LineEditGNSSSNR[1][GPS][1][0]=uiSNR->lineEditSNRMaxSpecificF2CodeGPS_1;
    LineEditGNSSSNR[1][GPS][1][1]=uiSNR->lineEditSNRMaxSpecificF2CodeGPS_2;
    LineEditGNSSSNR[1][GPS][2][0]=uiSNR->lineEditSNRMaxSpecificF5CodeGPS_1;
    LineEditGNSSSNR[1][GPS][2][1]=uiSNR->lineEditSNRMaxSpecificF5CodeGPS_2;
    //Galileo Max
    LineEditGNSSSNR[1][Galileo][0][0]=uiSNR->lineEditSNRMaxSpecificF1CodeGalileo_1;
    LineEditGNSSSNR[1][Galileo][0][1]=uiSNR->lineEditSNRMaxSpecificF1CodeGalileo_2;
    LineEditGNSSSNR[1][Galileo][1][0]=uiSNR->lineEditSNRMaxSpecificF5CodeGalileo_1;
    LineEditGNSSSNR[1][Galileo][1][1]=uiSNR->lineEditSNRMaxSpecificF5CodeGalileo_2;
    LineEditGNSSSNR[1][Galileo][2][0]=uiSNR->lineEditSNRMaxSpecificF6CodeGalileo_1;
    LineEditGNSSSNR[1][Galileo][2][1]=uiSNR->lineEditSNRMaxSpecificF6CodeGalileo_2;
    LineEditGNSSSNR[1][Galileo][3][0]=uiSNR->lineEditSNRMaxSpecificF7CodeGalileo_1;
    LineEditGNSSSNR[1][Galileo][3][1]=uiSNR->lineEditSNRMaxSpecificF7CodeGalileo_2;
    LineEditGNSSSNR[1][Galileo][4][0]=uiSNR->lineEditSNRMaxSpecificF8CodeGalileo_1;
    LineEditGNSSSNR[1][Galileo][4][1]=uiSNR->lineEditSNRMaxSpecificF8CodeGalileo_2;
    //GLONASS Max
    LineEditGNSSSNR[1][GLONASS][0][0]=uiSNR->lineEditSNRMaxSpecificF1CodeGLONASS_1;
    LineEditGNSSSNR[1][GLONASS][0][1]=uiSNR->lineEditSNRMaxSpecificF1CodeGLONASS_2;
    LineEditGNSSSNR[1][GLONASS][1][0]=uiSNR->lineEditSNRMaxSpecificF2CodeGLONASS_1;
    LineEditGNSSSNR[1][GLONASS][1][1]=uiSNR->lineEditSNRMaxSpecificF2CodeGLONASS_2;
    LineEditGNSSSNR[1][GLONASS][2][0]=uiSNR->lineEditSNRMaxSpecificF3CodeGLONASS_1;
    LineEditGNSSSNR[1][GLONASS][2][1]=uiSNR->lineEditSNRMaxSpecificF3CodeGLONASS_2;
    LineEditGNSSSNR[1][GLONASS][3][0]=uiSNR->lineEditSNRMaxSpecificF4CodeGLONASS_1;
    LineEditGNSSSNR[1][GLONASS][3][1]=uiSNR->lineEditSNRMaxSpecificF4CodeGLONASS_2;
    LineEditGNSSSNR[1][GLONASS][4][0]=uiSNR->lineEditSNRMaxSpecificF6CodeGLONASS_1;
    LineEditGNSSSNR[1][GLONASS][4][1]=uiSNR->lineEditSNRMaxSpecificF6CodeGLONASS_2;
    //GEO Max
    LineEditGNSSSNR[1][GEO][0][0]=uiSNR->lineEditSNRMaxSpecificF1CodeGEO_1;
    LineEditGNSSSNR[1][GEO][0][1]=uiSNR->lineEditSNRMaxSpecificF1CodeGEO_2;
    LineEditGNSSSNR[1][GEO][1][0]=uiSNR->lineEditSNRMaxSpecificF5CodeGEO_1;
    LineEditGNSSSNR[1][GEO][1][1]=uiSNR->lineEditSNRMaxSpecificF5CodeGEO_2;
    //BDS Max
    LineEditGNSSSNR[1][BDS][0][0]=uiSNR->lineEditSNRMaxSpecificF1CodeBDS_1;
    LineEditGNSSSNR[1][BDS][0][1]=uiSNR->lineEditSNRMaxSpecificF1CodeBDS_2;
    LineEditGNSSSNR[1][BDS][1][0]=uiSNR->lineEditSNRMaxSpecificF2CodeBDS_1;
    LineEditGNSSSNR[1][BDS][1][1]=uiSNR->lineEditSNRMaxSpecificF2CodeBDS_2;
    LineEditGNSSSNR[1][BDS][2][0]=uiSNR->lineEditSNRMaxSpecificF5CodeBDS_1;
    LineEditGNSSSNR[1][BDS][2][1]=uiSNR->lineEditSNRMaxSpecificF5CodeBDS_2;
    LineEditGNSSSNR[1][BDS][3][0]=uiSNR->lineEditSNRMaxSpecificF6CodeBDS_1;
    LineEditGNSSSNR[1][BDS][3][1]=uiSNR->lineEditSNRMaxSpecificF6CodeBDS_2;
    LineEditGNSSSNR[1][BDS][4][0]=uiSNR->lineEditSNRMaxSpecificF7CodeBDS_1;
    LineEditGNSSSNR[1][BDS][4][1]=uiSNR->lineEditSNRMaxSpecificF7CodeBDS_2;
    LineEditGNSSSNR[1][BDS][5][0]=uiSNR->lineEditSNRMaxSpecificF8CodeBDS_1;
    LineEditGNSSSNR[1][BDS][5][1]=uiSNR->lineEditSNRMaxSpecificF8CodeBDS_2;
    //QZSS Max
    LineEditGNSSSNR[1][QZSS][0][0]=uiSNR->lineEditSNRMaxSpecificF1CodeQZSS_1;
    LineEditGNSSSNR[1][QZSS][0][1]=uiSNR->lineEditSNRMaxSpecificF1CodeQZSS_2;
    LineEditGNSSSNR[1][QZSS][1][0]=uiSNR->lineEditSNRMaxSpecificF2CodeQZSS_1;
    LineEditGNSSSNR[1][QZSS][1][1]=uiSNR->lineEditSNRMaxSpecificF2CodeQZSS_2;
    LineEditGNSSSNR[1][QZSS][2][0]=uiSNR->lineEditSNRMaxSpecificF5CodeQZSS_1;
    LineEditGNSSSNR[1][QZSS][2][1]=uiSNR->lineEditSNRMaxSpecificF5CodeQZSS_2;
    LineEditGNSSSNR[1][QZSS][3][0]=uiSNR->lineEditSNRMaxSpecificF6CodeQZSS_1;
    LineEditGNSSSNR[1][QZSS][3][1]=uiSNR->lineEditSNRMaxSpecificF6CodeQZSS_2;
    //IRNSS Max
    LineEditGNSSSNR[1][IRNSS][0][0]=uiSNR->lineEditSNRMaxSpecificF5CodeIRNSS_1;
    LineEditGNSSSNR[1][IRNSS][0][1]=uiSNR->lineEditSNRMaxSpecificF5CodeIRNSS_2;
    LineEditGNSSSNR[1][IRNSS][1][0]=uiSNR->lineEditSNRMaxSpecificF9CodeIRNSS_1;
    LineEditGNSSSNR[1][IRNSS][1][1]=uiSNR->lineEditSNRMaxSpecificF9CodeIRNSS_2;
}
//Function to initialize pointers to pushButton GNSS Measurements _clicked() functions
void GNSS_SNR_Advanced::InitPushButtonGNSSMinFuncPointers(){
    PushButtonGNSSFunctions[GPS]=&GNSS_SNR_Advanced::on_pushButtonGPS_clicked;
    PushButtonGNSSFunctions[Galileo]=&GNSS_SNR_Advanced::on_pushButtonGalileo_clicked;
    PushButtonGNSSFunctions[GLONASS]=&GNSS_SNR_Advanced::on_pushButtonGLONASS_clicked;
    PushButtonGNSSFunctions[GEO]=&GNSS_SNR_Advanced::on_pushButtonGEO_clicked;
    PushButtonGNSSFunctions[BDS]=&GNSS_SNR_Advanced::on_pushButtonBDS_clicked;
    PushButtonGNSSFunctions[QZSS]=&GNSS_SNR_Advanced::on_pushButtonQZSS_clicked;
    PushButtonGNSSFunctions[IRNSS]=&GNSS_SNR_Advanced::on_pushButtonIRNSS_clicked;
}

void GNSS_SNR_Advanced::setSNRdefaults(){
    if (MinorMax==MINSNRTYPE) {
        this->SetDefaultSNRThresholdMinGPS();
        this->SetDefaultSNRThresholdMinGalileo();
        this->SetDefaultSNRThresholdMinGLONASS();
        this->SetDefaultSNRThresholdMinGEO();
        this->SetDefaultSNRThresholdMinBDS();
        this->SetDefaultSNRThresholdMinQZSS();
        this->SetDefaultSNRThresholdMinIRNSS();
    }
    if (MinorMax==MAXSNRTYPE) {
        this->SetDefaultSNRThresholdMaxGPS();
        this->SetDefaultSNRThresholdMaxGalileo();
        this->SetDefaultSNRThresholdMaxGLONASS();
        this->SetDefaultSNRThresholdMaxGEO();
        this->SetDefaultSNRThresholdMaxBDS();
        this->SetDefaultSNRThresholdMaxQZSS();
        this->SetDefaultSNRThresholdMaxIRNSS();
    }
}

// Function to configure GPS satellites
void GNSS_SNR_Advanced::on_pushButtonGPS_clicked(){
    if (MinorMax==MINSNRTYPE){ //Min SNR
        uiSNR->stackedWidgetSNRMinGNSS->setCurrentIndex(GPS);
    } else if (MinorMax==MAXSNRTYPE){ //Max SNR
        uiSNR->stackedWidgetSNRMaxGNSS->setCurrentIndex(GPS);
    }
    uiSNR->labelSelectPRNFor->setText("GPS:");
    uiSNR->pushButtonGalileo->setChecked(false);
    uiSNR->pushButtonGLONASS->setChecked(false);
    uiSNR->pushButtonGEO->setChecked(false);
    uiSNR->pushButtonBDS->setChecked(false);
    uiSNR->pushButtonQZSS->setChecked(false);
    uiSNR->pushButtonIRNSS->setChecked(false);
    uiSNR->pushButtonGPS->setChecked(true);
}
// Function to configure Galileo satellites
void GNSS_SNR_Advanced::on_pushButtonGalileo_clicked(){
    if (MinorMax==MINSNRTYPE){ //Min SNR
        uiSNR->stackedWidgetSNRMinGNSS->setCurrentIndex(Galileo);
    } else if (MinorMax==MAXSNRTYPE){ //Max SNR
        uiSNR->stackedWidgetSNRMaxGNSS->setCurrentIndex(Galileo);
    }
    uiSNR->labelSelectPRNFor->setText("Galileo:");
    uiSNR->pushButtonGPS->setChecked(false);
    uiSNR->pushButtonGLONASS->setChecked(false);
    uiSNR->pushButtonGEO->setChecked(false);
    uiSNR->pushButtonBDS->setChecked(false);
    uiSNR->pushButtonQZSS->setChecked(false);
    uiSNR->pushButtonIRNSS->setChecked(false);
    uiSNR->pushButtonGalileo->setChecked(true);
}
// Function to configure GLONASS satellites
void GNSS_SNR_Advanced::on_pushButtonGLONASS_clicked(){
    if (MinorMax==MINSNRTYPE){ //Min SNR
        uiSNR->stackedWidgetSNRMinGNSS->setCurrentIndex(GLONASS);
    } else if (MinorMax==MAXSNRTYPE){ //Max SNR
        uiSNR->stackedWidgetSNRMaxGNSS->setCurrentIndex(GLONASS);
    }
    uiSNR->labelSelectPRNFor->setText("GLONASS:");
    uiSNR->pushButtonGPS->setChecked(false);
    uiSNR->pushButtonGalileo->setChecked(false);
    uiSNR->pushButtonGEO->setChecked(false);
    uiSNR->pushButtonBDS->setChecked(false);
    uiSNR->pushButtonQZSS->setChecked(false);
    uiSNR->pushButtonIRNSS->setChecked(false);
    uiSNR->pushButtonGLONASS->setChecked(true);
}
// Function to configure GEO satellites
void GNSS_SNR_Advanced::on_pushButtonGEO_clicked(){
    if (MinorMax==MINSNRTYPE){ //Min SNR
        uiSNR->stackedWidgetSNRMinGNSS->setCurrentIndex(GEO);
    } else if (MinorMax==MAXSNRTYPE){ //Max SNR
        uiSNR->stackedWidgetSNRMaxGNSS->setCurrentIndex(GEO);
    }
    uiSNR->labelSelectPRNFor->setText("GEO:");
    uiSNR->pushButtonGPS->setChecked(false);
    uiSNR->pushButtonGalileo->setChecked(false);
    uiSNR->pushButtonGLONASS->setChecked(false);
    uiSNR->pushButtonBDS->setChecked(false);
    uiSNR->pushButtonQZSS->setChecked(false);
    uiSNR->pushButtonIRNSS->setChecked(false);
    uiSNR->pushButtonGEO->setChecked(true);
}
// Function to configure BDS satellites
void GNSS_SNR_Advanced::on_pushButtonBDS_clicked(){
    if (MinorMax==MINSNRTYPE){ //Min SNR
        uiSNR->stackedWidgetSNRMinGNSS->setCurrentIndex(BDS);
    } else if (MinorMax==MAXSNRTYPE){ //Max SNR
        uiSNR->stackedWidgetSNRMaxGNSS->setCurrentIndex(BDS);
    }
    uiSNR->labelSelectPRNFor->setText("BDS:");
    uiSNR->pushButtonGPS->setChecked(false);
    uiSNR->pushButtonGalileo->setChecked(false);
    uiSNR->pushButtonGLONASS->setChecked(false);
    uiSNR->pushButtonGEO->setChecked(false);
    uiSNR->pushButtonQZSS->setChecked(false);
    uiSNR->pushButtonIRNSS->setChecked(false);
    uiSNR->pushButtonBDS->setChecked(true);
}
// Function to configure QZSS satellites
void GNSS_SNR_Advanced::on_pushButtonQZSS_clicked(){
    if (MinorMax==MINSNRTYPE){ //Min SNR
        uiSNR->stackedWidgetSNRMinGNSS->setCurrentIndex(QZSS);
    } else if (MinorMax==MAXSNRTYPE){ //Max SNR
        uiSNR->stackedWidgetSNRMaxGNSS->setCurrentIndex(QZSS);
    }
    uiSNR->labelSelectPRNFor->setText("QZSS:");
    uiSNR->pushButtonGPS->setChecked(false);
    uiSNR->pushButtonGalileo->setChecked(false);
    uiSNR->pushButtonGLONASS->setChecked(false);
    uiSNR->pushButtonGEO->setChecked(false);
    uiSNR->pushButtonBDS->setChecked(false);
    uiSNR->pushButtonIRNSS->setChecked(false);
    uiSNR->pushButtonQZSS->setChecked(true);
}
// Function to configure IRNSS satellites
void GNSS_SNR_Advanced::on_pushButtonIRNSS_clicked(){
    if (MinorMax==MINSNRTYPE){ //Min SNR
        uiSNR->stackedWidgetSNRMinGNSS->setCurrentIndex(IRNSS);
    } else if (MinorMax==MAXSNRTYPE){ //Max SNR
        uiSNR->stackedWidgetSNRMaxGNSS->setCurrentIndex(IRNSS);
    }
    uiSNR->labelSelectPRNFor->setText("IRNSS:");
    uiSNR->pushButtonGPS->setChecked(false);
    uiSNR->pushButtonGalileo->setChecked(false);
    uiSNR->pushButtonGLONASS->setChecked(false);
    uiSNR->pushButtonGEO->setChecked(false);
    uiSNR->pushButtonBDS->setChecked(false);
    uiSNR->pushButtonQZSS->setChecked(false);
    uiSNR->pushButtonIRNSS->setChecked(true);
}

//GPS
// Function to show or hide Min SNR threshold
void GNSS_SNR_Advanced::SetDefaultSNRThresholdMinGPS() {
    this->on_comboBoxSNRThresholdsMinGPS_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinGPS->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGPS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGPS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeGPS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeGPS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGPS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGPS_2->setText("");
    this->on_comboBoxSNRMinMeasF1CodeGPS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF1CodeGPS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF1CodeGPS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF2CodeGPS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF2CodeGPS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF2CodeGPS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF5CodeGPS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF5CodeGPS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF5CodeGPS_2_currentIndexChanged(0);
}
//Function to show or hide text box for user defined Min SNR threshold when SNR combo box changes
void GNSS_SNR_Advanced::on_comboBoxSNRThresholdsMinGPS_currentIndexChanged(int index) {
    uiSNR->comboBoxSNRThresholdsMinGPS->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRThresholdsMinGPS->currentText()=="Specify") {
        uiSNR->lineEditUserDefinedSNRMinGPS->setHidden(false);
    } else {
        uiSNR->lineEditUserDefinedSNRMinGPS->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF1CodeGPS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF1CodeGPS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF1CodeGPS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF1CodeGPS_2->isHidden()==true) {
        uiSNR->frameSNRMinF1CodeGPS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF1CodeGPS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF1CodeGPS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF1CodeGPS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF1CodeGPS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF1CodeGPS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF1CodeGPS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF1CodeGPS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF1CodeGPS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF1CodeGPS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF1CodeGPS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF1CodeGPS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF2CodeGPS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF2CodeGPS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF2CodeGPS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF2CodeGPS_2->isHidden()==true) {
        uiSNR->frameSNRMinF2CodeGPS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF2CodeGPS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF2CodeGPS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF2CodeGPS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF2CodeGPS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF2CodeGPS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF2CodeGPS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF2CodeGPS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF2CodeGPS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF2CodeGPS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF2CodeGPS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF2CodeGPS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF5CodeGPS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF5CodeGPS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF5CodeGPS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF5CodeGPS_2->isHidden()==true) {
        uiSNR->frameSNRMinF5CodeGPS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF5CodeGPS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF5CodeGPS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF5CodeGPS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF5CodeGPS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF5CodeGPS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF5CodeGPS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF5CodeGPS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF5CodeGPS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF5CodeGPS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF5CodeGPS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF5CodeGPS_2->setHidden(true);
    }
}
// Function to show or hide Max SNR threshold
void GNSS_SNR_Advanced::SetDefaultSNRThresholdMaxGPS() {
    this->on_comboBoxSNRThresholdsMaxGPS_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxGPS->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGPS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGPS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeGPS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeGPS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGPS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGPS_2->setText("");
    this->on_comboBoxSNRMaxMeasF1CodeGPS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF1CodeGPS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF1CodeGPS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF2CodeGPS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF2CodeGPS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF2CodeGPS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF5CodeGPS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF5CodeGPS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF5CodeGPS_2_currentIndexChanged(0);
}
//Function to show or hide text box for user defined Max SNR threshold when SNR combo box changes
void GNSS_SNR_Advanced::on_comboBoxSNRThresholdsMaxGPS_currentIndexChanged(int index) {
    uiSNR->comboBoxSNRThresholdsMaxGPS->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRThresholdsMaxGPS->currentText()=="Specify") {
        uiSNR->lineEditUserDefinedSNRMaxGPS->setHidden(false);
    } else {
        uiSNR->lineEditUserDefinedSNRMaxGPS->setHidden(true);
    }
}
//Function to configure GPS Max SNR by frequencies and measurements
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF1CodeGPS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF1CodeGPS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF1CodeGPS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF1CodeGPS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF1CodeGPS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF1CodeGPS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF1CodeGPS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF1CodeGPS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF1CodeGPS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF1CodeGPS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF1CodeGPS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF1CodeGPS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF1CodeGPS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF1CodeGPS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF1CodeGPS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF1CodeGPS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF2CodeGPS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF2CodeGPS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF2CodeGPS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF2CodeGPS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF2CodeGPS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF2CodeGPS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF2CodeGPS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF2CodeGPS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF2CodeGPS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF2CodeGPS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF2CodeGPS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF2CodeGPS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF2CodeGPS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF2CodeGPS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF2CodeGPS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF2CodeGPS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF5CodeGPS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF5CodeGPS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF5CodeGPS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF5CodeGPS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF5CodeGPS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF5CodeGPS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF5CodeGPS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF5CodeGPS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF5CodeGPS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF5CodeGPS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF5CodeGPS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF5CodeGPS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF5CodeGPS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF5CodeGPS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF5CodeGPS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF5CodeGPS_2->setHidden(true);
    }
}
//Galileo
// Function to show or hide Min SNR threshold
void GNSS_SNR_Advanced::SetDefaultSNRThresholdMinGalileo() {
    //Galileo
    this->on_comboBoxSNRThresholdsMinGalileo_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinGalileo->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMinSpecificF7CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMinSpecificF7CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMinSpecificF8CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMinSpecificF8CodeGalileo_2->setText("");
    this->on_comboBoxSNRMinMeasF1CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF1CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF1CodeGalileo_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF5CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF5CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF5CodeGalileo_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF6CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF6CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF6CodeGalileo_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF7CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF7CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF7CodeGalileo_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF8CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF8CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF8CodeGalileo_2_currentIndexChanged(0);
}
//Function to show or hide text box for user defined Min SNR threshold when SNR combo box changes
void GNSS_SNR_Advanced::on_comboBoxSNRThresholdsMinGalileo_currentIndexChanged(int index) {
    uiSNR->comboBoxSNRThresholdsMinGalileo->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRThresholdsMinGalileo->currentText()=="Specify") {
        uiSNR->lineEditUserDefinedSNRMinGalileo->setHidden(false);
    } else {
        uiSNR->lineEditUserDefinedSNRMinGalileo->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF1CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF1CodeGalileo_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF1CodeGalileo_2->setHidden(true);
    else if (uiSNR->frameSNRMinF1CodeGalileo_2->isHidden()==true) {
        uiSNR->frameSNRMinF1CodeGalileo_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF1CodeGalileo_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF1CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF1CodeGalileo_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF1CodeGalileo_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF1CodeGalileo_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF1CodeGalileo_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF1CodeGalileo_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF1CodeGalileo_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF1CodeGalileo_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF1CodeGalileo_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF1CodeGalileo_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF5CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF5CodeGalileo_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF5CodeGalileo_2->setHidden(true);
    else if (uiSNR->frameSNRMinF5CodeGalileo_2->isHidden()==true) {
        uiSNR->frameSNRMinF5CodeGalileo_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF5CodeGalileo_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF5CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF5CodeGalileo_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF5CodeGalileo_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF5CodeGalileo_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF5CodeGalileo_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF5CodeGalileo_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF5CodeGalileo_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF5CodeGalileo_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF5CodeGalileo_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF5CodeGalileo_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF6CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF6CodeGalileo_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF6CodeGalileo_2->setHidden(true);
    else if (uiSNR->frameSNRMinF6CodeGalileo_2->isHidden()==true) {
        uiSNR->frameSNRMinF6CodeGalileo_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF6CodeGalileo_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF6CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF6CodeGalileo_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF6CodeGalileo_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF6CodeGalileo_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF6CodeGalileo_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF6CodeGalileo_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF6CodeGalileo_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF6CodeGalileo_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF6CodeGalileo_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF6CodeGalileo_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF7CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF7CodeGalileo_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF7CodeGalileo_2->setHidden(true);
    else if (uiSNR->frameSNRMinF7CodeGalileo_2->isHidden()==true) {
        uiSNR->frameSNRMinF7CodeGalileo_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF7CodeGalileo_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF7CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF7CodeGalileo_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF7CodeGalileo_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF7CodeGalileo_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF7CodeGalileo_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF7CodeGalileo_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF7CodeGalileo_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF7CodeGalileo_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF7CodeGalileo_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF7CodeGalileo_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF8CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF8CodeGalileo_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF8CodeGalileo_2->setHidden(true);
    else if (uiSNR->frameSNRMinF8CodeGalileo_2->isHidden()==true) {
        uiSNR->frameSNRMinF8CodeGalileo_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF8CodeGalileo_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF8CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF8CodeGalileo_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF8CodeGalileo_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF8CodeGalileo_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF8CodeGalileo_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF8CodeGalileo_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF8CodeGalileo_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF8CodeGalileo_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF8CodeGalileo_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF8CodeGalileo_2->setHidden(true);
    }
}
// Function to show or hide Max SNR threshold
void GNSS_SNR_Advanced::SetDefaultSNRThresholdMaxGalileo() {
    this->on_comboBoxSNRThresholdsMaxGalileo_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxGalileo->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF7CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF7CodeGalileo_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF8CodeGalileo_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF8CodeGalileo_2->setText("");
    this->on_comboBoxSNRMaxMeasF1CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF1CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF1CodeGalileo_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF5CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF5CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF5CodeGalileo_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF6CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF6CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF6CodeGalileo_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF7CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF7CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF7CodeGalileo_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF8CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF8CodeGalileo_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF8CodeGalileo_2_currentIndexChanged(0);
}
//Function to show or hide text box for user defined Max SNR threshold when SNR combo box changes
void GNSS_SNR_Advanced::on_comboBoxSNRThresholdsMaxGalileo_currentIndexChanged(int index) {
    uiSNR->comboBoxSNRThresholdsMaxGalileo->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRThresholdsMaxGalileo->currentText()=="Specify") {
        uiSNR->lineEditUserDefinedSNRMaxGalileo->setHidden(false);
    } else {
        uiSNR->lineEditUserDefinedSNRMaxGalileo->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF1CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF1CodeGalileo_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF1CodeGalileo_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF1CodeGalileo_2->isHidden()==true) {
        uiSNR->frameSNRMaxF1CodeGalileo_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF1CodeGalileo_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF1CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF1CodeGalileo_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF1CodeGalileo_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF1CodeGalileo_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF1CodeGalileo_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF1CodeGalileo_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF1CodeGalileo_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF1CodeGalileo_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF1CodeGalileo_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF1CodeGalileo_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF5CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF5CodeGalileo_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF5CodeGalileo_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF5CodeGalileo_2->isHidden()==true) {
        uiSNR->frameSNRMaxF5CodeGalileo_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF5CodeGalileo_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF5CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF5CodeGalileo_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF5CodeGalileo_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF5CodeGalileo_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF5CodeGalileo_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF5CodeGalileo_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF5CodeGalileo_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF5CodeGalileo_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF5CodeGalileo_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF5CodeGalileo_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF6CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF6CodeGalileo_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF6CodeGalileo_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF6CodeGalileo_2->isHidden()==true) {
        uiSNR->frameSNRMaxF6CodeGalileo_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF6CodeGalileo_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF6CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF6CodeGalileo_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF6CodeGalileo_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF6CodeGalileo_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF6CodeGalileo_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF6CodeGalileo_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF6CodeGalileo_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF6CodeGalileo_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF6CodeGalileo_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF6CodeGalileo_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF7CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF7CodeGalileo_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF7CodeGalileo_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF7CodeGalileo_2->isHidden()==true) {
        uiSNR->frameSNRMaxF7CodeGalileo_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF7CodeGalileo_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF7CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF7CodeGalileo_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF7CodeGalileo_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF7CodeGalileo_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF7CodeGalileo_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF7CodeGalileo_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF7CodeGalileo_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF7CodeGalileo_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF7CodeGalileo_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF7CodeGalileo_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF8CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF8CodeGalileo_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF8CodeGalileo_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF8CodeGalileo_2->isHidden()==true) {
        uiSNR->frameSNRMaxF8CodeGalileo_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF8CodeGalileo_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF8CodeGalileo_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF8CodeGalileo_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF8CodeGalileo_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF8CodeGalileo_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF8CodeGalileo_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF8CodeGalileo_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF8CodeGalileo_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF8CodeGalileo_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF8CodeGalileo_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF8CodeGalileo_2->setHidden(true);
    }
}
//GLONASS
// Function to show or hide Min SNR threshold
void GNSS_SNR_Advanced::SetDefaultSNRThresholdMinGLONASS() {
    this->on_comboBoxSNRThresholdsMinGLONASS_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinGLONASS->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF3CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF3CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF4CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF4CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeGLONASS_2->setText("");
    this->on_comboBoxSNRMinMeasF1CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF1CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF1CodeGLONASS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF2CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF2CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF2CodeGLONASS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF3CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF3CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF3CodeGLONASS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF4CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF4CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF4CodeGLONASS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF6CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF6CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF6CodeGLONASS_2_currentIndexChanged(0);
}
//Function to show or hide text box for user defined Min SNR threshold when SNR combo box changes
void GNSS_SNR_Advanced::on_comboBoxSNRThresholdsMinGLONASS_currentIndexChanged(int index) {
    uiSNR->comboBoxSNRThresholdsMinGLONASS->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRThresholdsMinGLONASS->currentText()=="Specify") {
        uiSNR->lineEditUserDefinedSNRMinGLONASS->setHidden(false);
    } else {
        uiSNR->lineEditUserDefinedSNRMinGLONASS->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF1CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF1CodeGLONASS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF1CodeGLONASS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF1CodeGLONASS_2->isHidden()==true) {
        uiSNR->frameSNRMinF1CodeGLONASS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF1CodeGLONASS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF1CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF1CodeGLONASS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF1CodeGLONASS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF1CodeGLONASS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF1CodeGLONASS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF1CodeGLONASS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF1CodeGLONASS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF1CodeGLONASS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF1CodeGLONASS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF1CodeGLONASS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF2CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF2CodeGLONASS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF2CodeGLONASS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF2CodeGLONASS_2->isHidden()==true) {
        uiSNR->frameSNRMinF2CodeGLONASS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF2CodeGLONASS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF2CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF2CodeGLONASS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF2CodeGLONASS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF2CodeGLONASS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF2CodeGLONASS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF2CodeGLONASS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF2CodeGLONASS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF2CodeGLONASS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF2CodeGLONASS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF2CodeGLONASS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF3CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF3CodeGLONASS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF3CodeGLONASS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF3CodeGLONASS_2->isHidden()==true) {
        uiSNR->frameSNRMinF3CodeGLONASS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF3CodeGLONASS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF3CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF3CodeGLONASS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF3CodeGLONASS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF3CodeGLONASS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF3CodeGLONASS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF3CodeGLONASS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF3CodeGLONASS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF3CodeGLONASS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF3CodeGLONASS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF3CodeGLONASS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF4CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF4CodeGLONASS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF4CodeGLONASS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF4CodeGLONASS_2->isHidden()==true) {
        uiSNR->frameSNRMinF4CodeGLONASS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF4CodeGLONASS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF4CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF4CodeGLONASS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF4CodeGLONASS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF4CodeGLONASS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF4CodeGLONASS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF4CodeGLONASS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF4CodeGLONASS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF4CodeGLONASS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF4CodeGLONASS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF4CodeGLONASS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF6CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF6CodeGLONASS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF6CodeGLONASS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF6CodeGLONASS_2->isHidden()==true) {
        uiSNR->frameSNRMinF6CodeGLONASS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF6CodeGLONASS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF6CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF6CodeGLONASS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF6CodeGLONASS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF6CodeGLONASS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF6CodeGLONASS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF6CodeGLONASS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF6CodeGLONASS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF6CodeGLONASS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF6CodeGLONASS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF6CodeGLONASS_2->setHidden(true);
    }
}
// Function to show or hide Max SNR threshold
void GNSS_SNR_Advanced::SetDefaultSNRThresholdMaxGLONASS() {
    this->on_comboBoxSNRThresholdsMaxGLONASS_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxGLONASS->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF3CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF3CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF4CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF4CodeGLONASS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeGLONASS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeGLONASS_2->setText("");
    this->on_comboBoxSNRMaxMeasF1CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF1CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF1CodeGLONASS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF2CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF2CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF2CodeGLONASS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF3CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF3CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF3CodeGLONASS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF4CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF4CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF4CodeGLONASS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF6CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF6CodeGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF6CodeGLONASS_2_currentIndexChanged(0);
}
//Function to show or hide text box for user defined Max SNR threshold when SNR combo box changes
void GNSS_SNR_Advanced::on_comboBoxSNRThresholdsMaxGLONASS_currentIndexChanged(int index) {
    uiSNR->comboBoxSNRThresholdsMaxGLONASS->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRThresholdsMaxGLONASS->currentText()=="Specify") {
        uiSNR->lineEditUserDefinedSNRMaxGLONASS->setHidden(false);
    } else {
        uiSNR->lineEditUserDefinedSNRMaxGLONASS->setHidden(true);
    }
}
//Function to configure GLONASS Max SNR by frequencies and measurements
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF1CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF1CodeGLONASS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF1CodeGLONASS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF1CodeGLONASS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF1CodeGLONASS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF1CodeGLONASS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF1CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF1CodeGLONASS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF1CodeGLONASS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF1CodeGLONASS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF1CodeGLONASS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF1CodeGLONASS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF1CodeGLONASS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF1CodeGLONASS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF1CodeGLONASS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF1CodeGLONASS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF2CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF2CodeGLONASS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF2CodeGLONASS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF2CodeGLONASS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF2CodeGLONASS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF2CodeGLONASS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF2CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF2CodeGLONASS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF2CodeGLONASS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF2CodeGLONASS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF2CodeGLONASS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF2CodeGLONASS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF2CodeGLONASS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF2CodeGLONASS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF2CodeGLONASS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF2CodeGLONASS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF3CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF3CodeGLONASS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF3CodeGLONASS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF3CodeGLONASS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF3CodeGLONASS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF3CodeGLONASS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF3CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF3CodeGLONASS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF3CodeGLONASS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF3CodeGLONASS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF3CodeGLONASS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF3CodeGLONASS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF3CodeGLONASS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF3CodeGLONASS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF3CodeGLONASS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF3CodeGLONASS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF4CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF4CodeGLONASS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF4CodeGLONASS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF4CodeGLONASS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF4CodeGLONASS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF4CodeGLONASS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF4CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF4CodeGLONASS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF4CodeGLONASS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF4CodeGLONASS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF4CodeGLONASS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF4CodeGLONASS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF4CodeGLONASS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF4CodeGLONASS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF4CodeGLONASS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF4CodeGLONASS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF6CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF6CodeGLONASS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF6CodeGLONASS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF6CodeGLONASS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF6CodeGLONASS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF6CodeGLONASS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF6CodeGLONASS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF6CodeGLONASS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF6CodeGLONASS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF6CodeGLONASS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF6CodeGLONASS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF6CodeGLONASS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF6CodeGLONASS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF6CodeGLONASS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF6CodeGLONASS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF6CodeGLONASS_2->setHidden(true);
    }
}
//GEO
// Function to show or hide Min SNR threshold
void GNSS_SNR_Advanced::SetDefaultSNRThresholdMinGEO() {
    this->on_comboBoxSNRThresholdsMinGEO_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinGEO->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGEO_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeGEO_2->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGEO_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeGEO_2->setText("");
    this->on_comboBoxSNRMinMeasF1CodeGEO_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF1CodeGEO_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF1CodeGEO_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF5CodeGEO_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF5CodeGEO_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF5CodeGEO_2_currentIndexChanged(0);
}
//Function to show or hide text box for user defined Min SNR threshold when SNR combo box changes
void GNSS_SNR_Advanced::on_comboBoxSNRThresholdsMinGEO_currentIndexChanged(int index) {
    uiSNR->comboBoxSNRThresholdsMinGEO->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRThresholdsMinGEO->currentText()=="Specify") {
        uiSNR->lineEditUserDefinedSNRMinGEO->setHidden(false);
    } else {
        uiSNR->lineEditUserDefinedSNRMinGEO->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF1CodeGEO_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF1CodeGEO_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF1CodeGEO_2->setHidden(true);
    else if (uiSNR->frameSNRMinF1CodeGEO_2->isHidden()==true) {
        uiSNR->frameSNRMinF1CodeGEO_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF1CodeGEO_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF1CodeGEO_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF1CodeGEO_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF1CodeGEO_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF1CodeGEO_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF1CodeGEO_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF1CodeGEO_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF1CodeGEO_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF1CodeGEO_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF1CodeGEO_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF1CodeGEO_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF5CodeGEO_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF5CodeGEO_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF5CodeGEO_2->setHidden(true);
    else if (uiSNR->frameSNRMinF5CodeGEO_2->isHidden()==true) {
        uiSNR->frameSNRMinF5CodeGEO_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF5CodeGEO_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF5CodeGEO_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF5CodeGEO_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF5CodeGEO_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF5CodeGEO_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF5CodeGEO_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF5CodeGEO_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF5CodeGEO_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF5CodeGEO_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF5CodeGEO_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF5CodeGEO_2->setHidden(true);
    }
}
// Function to show or hide Max SNR threshold
void GNSS_SNR_Advanced::SetDefaultSNRThresholdMaxGEO() {
    this->on_comboBoxSNRThresholdsMaxGEO_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxGEO->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGEO_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeGEO_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGEO_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeGEO_2->setText("");
    this->on_comboBoxSNRMaxMeasF1CodeGEO_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF1CodeGEO_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF1CodeGEO_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF5CodeGEO_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF5CodeGEO_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF5CodeGEO_2_currentIndexChanged(0);
}
//Function to show or hide text box for user defined Max SNR threshold when SNR combo box changes
void GNSS_SNR_Advanced::on_comboBoxSNRThresholdsMaxGEO_currentIndexChanged(int index) {
    uiSNR->comboBoxSNRThresholdsMaxGEO->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRThresholdsMaxGEO->currentText()=="Specify") {
        uiSNR->lineEditUserDefinedSNRMaxGEO->setHidden(false);
    } else {
        uiSNR->lineEditUserDefinedSNRMaxGEO->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF1CodeGEO_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF1CodeGEO_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF1CodeGEO_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF1CodeGEO_2->isHidden()==true) {
        uiSNR->frameSNRMaxF1CodeGEO_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF1CodeGEO_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF1CodeGEO_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF1CodeGEO_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF1CodeGEO_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF1CodeGEO_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF1CodeGEO_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF1CodeGEO_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF1CodeGEO_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF1CodeGEO_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF1CodeGEO_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF1CodeGEO_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF5CodeGEO_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF5CodeGEO_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF5CodeGEO_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF5CodeGEO_2->isHidden()==true) {
        uiSNR->frameSNRMaxF5CodeGEO_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF5CodeGEO_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF5CodeGEO_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF5CodeGEO_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF5CodeGEO_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF5CodeGEO_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF5CodeGEO_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF5CodeGEO_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF5CodeGEO_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF5CodeGEO_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF5CodeGEO_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF5CodeGEO_2->setHidden(true);
    }
}

//BDS
// Function to show or hide Min SNR threshold
void GNSS_SNR_Advanced::SetDefaultSNRThresholdMinBDS() {
    this->on_comboBoxSNRThresholdsMinBDS_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinBDS->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeBDS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF7CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF7CodeBDS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeBDS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeBDS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeBDS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF8CodeBDS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF8CodeBDS_2->setText("");
    this->on_comboBoxSNRMinMeasF2CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF2CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF2CodeBDS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF7CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF7CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF7CodeBDS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF6CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF6CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF6CodeBDS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF5CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF5CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF5CodeBDS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF1CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF1CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF1CodeBDS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF8CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF8CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF8CodeBDS_2_currentIndexChanged(0);
}
//Function to show or hide text box for user defined Min SNR threshold when SNR combo box changes
void GNSS_SNR_Advanced::on_comboBoxSNRThresholdsMinBDS_currentIndexChanged(int index) {
    uiSNR->comboBoxSNRThresholdsMinBDS->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRThresholdsMinBDS->currentText()=="Specify") {
        uiSNR->lineEditUserDefinedSNRMinBDS->setHidden(false);
    } else {
        uiSNR->lineEditUserDefinedSNRMinBDS->setHidden(true);
    }
}
//Function to configure BDS Min SNR by frequencies and measurements
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF2CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF2CodeBDS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF2CodeBDS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF2CodeBDS_2->isHidden()==true) {
        uiSNR->frameSNRMinF2CodeBDS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF2CodeBDS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF2CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF2CodeBDS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF2CodeBDS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF2CodeBDS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF2CodeBDS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF2CodeBDS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF2CodeBDS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF2CodeBDS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF2CodeBDS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF2CodeBDS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF7CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF7CodeBDS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF7CodeBDS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF7CodeBDS_2->isHidden()==true) {
        uiSNR->frameSNRMinF7CodeBDS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF7CodeBDS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF7CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF7CodeBDS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF7CodeBDS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF7CodeBDS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF7CodeBDS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF7CodeBDS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF7CodeBDS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF7CodeBDS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF7CodeBDS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF7CodeBDS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF6CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF6CodeBDS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF6CodeBDS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF6CodeBDS_2->isHidden()==true) {
        uiSNR->frameSNRMinF6CodeBDS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF6CodeBDS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF6CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF6CodeBDS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF6CodeBDS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF6CodeBDS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF6CodeBDS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF6CodeBDS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF6CodeBDS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF6CodeBDS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF6CodeBDS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF6CodeBDS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF5CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF5CodeBDS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF5CodeBDS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF5CodeBDS_2->isHidden()==true) {
        uiSNR->frameSNRMinF5CodeBDS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF5CodeBDS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF5CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF5CodeBDS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF5CodeBDS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF5CodeBDS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF5CodeBDS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF5CodeBDS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF5CodeBDS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF5CodeBDS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF5CodeBDS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF5CodeBDS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF1CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF1CodeBDS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF1CodeBDS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF1CodeBDS_2->isHidden()==true) {
        uiSNR->frameSNRMinF1CodeBDS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF1CodeBDS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF1CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF1CodeBDS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF1CodeBDS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF1CodeBDS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF1CodeBDS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF1CodeBDS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF1CodeBDS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF1CodeBDS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF1CodeBDS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF1CodeBDS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF8CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF8CodeBDS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF8CodeBDS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF8CodeBDS_2->isHidden()==true) {
        uiSNR->frameSNRMinF8CodeBDS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF8CodeBDS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF8CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF8CodeBDS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF8CodeBDS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF8CodeBDS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF8CodeBDS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF8CodeBDS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF8CodeBDS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF8CodeBDS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF8CodeBDS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF8CodeBDS_2->setHidden(true);
    }
}
// Function to show or hide Max SNR threshold
void GNSS_SNR_Advanced::SetDefaultSNRThresholdMaxBDS() {
    this->on_comboBoxSNRThresholdsMaxBDS_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxBDS->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeBDS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF7CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF7CodeBDS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeBDS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeBDS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeBDS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF8CodeBDS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF8CodeBDS_2->setText("");
    this->on_comboBoxSNRMaxMeasF2CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF2CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF2CodeBDS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF7CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF7CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF7CodeBDS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF6CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF6CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF6CodeBDS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF5CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF5CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF5CodeBDS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF1CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF1CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF1CodeBDS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF8CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF8CodeBDS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF8CodeBDS_2_currentIndexChanged(0);
}
//Function to show or hide text box for user defined Max SNR threshold when SNR combo box changes
void GNSS_SNR_Advanced::on_comboBoxSNRThresholdsMaxBDS_currentIndexChanged(int index) {
    uiSNR->comboBoxSNRThresholdsMaxBDS->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRThresholdsMaxBDS->currentText()=="Specify") {
        uiSNR->lineEditUserDefinedSNRMaxBDS->setHidden(false);
    } else {
        uiSNR->lineEditUserDefinedSNRMaxBDS->setHidden(true);
    }
}
//Function to configure BDS Max SNR by frequencies and measurements
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF2CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF2CodeBDS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF2CodeBDS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF2CodeBDS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF2CodeBDS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF2CodeBDS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF2CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF2CodeBDS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF2CodeBDS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF2CodeBDS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF2CodeBDS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF2CodeBDS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF2CodeBDS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF2CodeBDS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF2CodeBDS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF2CodeBDS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF7CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF7CodeBDS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF7CodeBDS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF7CodeBDS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF7CodeBDS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF7CodeBDS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF7CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF7CodeBDS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF7CodeBDS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF7CodeBDS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF7CodeBDS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF7CodeBDS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF7CodeBDS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF7CodeBDS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF7CodeBDS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF7CodeBDS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF6CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF6CodeBDS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF6CodeBDS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF6CodeBDS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF6CodeBDS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF6CodeBDS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF6CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF6CodeBDS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF6CodeBDS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF6CodeBDS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF6CodeBDS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF6CodeBDS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF6CodeBDS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF6CodeBDS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF6CodeBDS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF6CodeBDS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF5CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF5CodeBDS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF5CodeBDS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF5CodeBDS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF5CodeBDS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF5CodeBDS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF5CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF5CodeBDS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF5CodeBDS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF5CodeBDS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF5CodeBDS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF5CodeBDS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF5CodeBDS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF5CodeBDS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF5CodeBDS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF5CodeBDS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF1CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF1CodeBDS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF1CodeBDS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF1CodeBDS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF1CodeBDS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF1CodeBDS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF1CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF1CodeBDS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF1CodeBDS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF1CodeBDS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF1CodeBDS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF1CodeBDS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF1CodeBDS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF1CodeBDS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF1CodeBDS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF1CodeBDS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF8CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF8CodeBDS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF8CodeBDS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF8CodeBDS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF8CodeBDS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF8CodeBDS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF8CodeBDS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF8CodeBDS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF8CodeBDS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF8CodeBDS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF8CodeBDS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF8CodeBDS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF8CodeBDS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF8CodeBDS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF8CodeBDS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF8CodeBDS_2->setHidden(true);
    }
}
//QZSS
// Function to show or hide Min SNR threshold
void GNSS_SNR_Advanced::SetDefaultSNRThresholdMinQZSS() {
    this->on_comboBoxSNRThresholdsMinQZSS_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinQZSS->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF1CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF2CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF6CodeQZSS_2->setText("");
    this->on_comboBoxSNRMinMeasF1CodeQZSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF1CodeQZSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF1CodeQZSS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF2CodeQZSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF2CodeQZSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF2CodeQZSS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF5CodeQZSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF5CodeQZSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF5CodeQZSS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF6CodeQZSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF6CodeQZSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF6CodeQZSS_2_currentIndexChanged(0);
}
//Function to show or hide text box for user defined Min SNR threshold when SNR combo box changes
void GNSS_SNR_Advanced::on_comboBoxSNRThresholdsMinQZSS_currentIndexChanged(int index) {
    uiSNR->comboBoxSNRThresholdsMinQZSS->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRThresholdsMinQZSS->currentText()=="Specify") {
        uiSNR->lineEditUserDefinedSNRMinQZSS->setHidden(false);
    } else {
        uiSNR->lineEditUserDefinedSNRMinQZSS->setHidden(true);
    }
}
//Function to configure QZSS Min SNR by frequencies and measurements
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF1CodeQZSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF1CodeQZSS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF1CodeQZSS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF1CodeQZSS_2->isHidden()==true) {
        uiSNR->frameSNRMinF1CodeQZSS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF1CodeQZSS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF1CodeQZSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF1CodeQZSS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF1CodeQZSS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF1CodeQZSS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF1CodeQZSS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF1CodeQZSS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF1CodeQZSS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF1CodeQZSS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF1CodeQZSS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF1CodeQZSS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF2CodeQZSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF2CodeQZSS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF2CodeQZSS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF2CodeQZSS_2->isHidden()==true) {
        uiSNR->frameSNRMinF2CodeQZSS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF2CodeQZSS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF2CodeQZSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF2CodeQZSS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF2CodeQZSS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF2CodeQZSS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF2CodeQZSS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF2CodeQZSS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF2CodeQZSS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF2CodeQZSS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF2CodeQZSS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF2CodeQZSS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF5CodeQZSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF5CodeQZSS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF5CodeQZSS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF5CodeQZSS_2->isHidden()==true) {
        uiSNR->frameSNRMinF5CodeQZSS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF5CodeQZSS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF5CodeQZSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF5CodeQZSS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF5CodeQZSS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF5CodeQZSS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF5CodeQZSS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF5CodeQZSS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF5CodeQZSS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF5CodeQZSS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF5CodeQZSS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF5CodeQZSS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF6CodeQZSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF6CodeQZSS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF6CodeQZSS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF6CodeQZSS_2->isHidden()==true) {
        uiSNR->frameSNRMinF6CodeQZSS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF6CodeQZSS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF6CodeQZSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF6CodeQZSS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF6CodeQZSS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF6CodeQZSS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF6CodeQZSS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF6CodeQZSS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF6CodeQZSS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF6CodeQZSS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF6CodeQZSS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF6CodeQZSS_2->setHidden(true);
    }
}
// Function to show or hide Max SNR threshold
void GNSS_SNR_Advanced::SetDefaultSNRThresholdMaxQZSS() {
    this->on_comboBoxSNRThresholdsMaxQZSS_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxQZSS->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF1CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF2CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeQZSS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeQZSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF6CodeQZSS_2->setText("");
    this->on_comboBoxSNRMaxMeasF1CodeQZSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF1CodeQZSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF1CodeQZSS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF2CodeQZSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF2CodeQZSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF2CodeQZSS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF5CodeQZSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF5CodeQZSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF5CodeQZSS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF6CodeQZSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF6CodeQZSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF6CodeQZSS_2_currentIndexChanged(0);
}
//Function to show or hide text box for user defined Max SNR threshold when SNR combo box changes
void GNSS_SNR_Advanced::on_comboBoxSNRThresholdsMaxQZSS_currentIndexChanged(int index) {
    uiSNR->comboBoxSNRThresholdsMaxQZSS->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRThresholdsMaxQZSS->currentText()=="Specify") {
        uiSNR->lineEditUserDefinedSNRMaxQZSS->setHidden(false);
    } else {
        uiSNR->lineEditUserDefinedSNRMaxQZSS->setHidden(true);
    }
}
//Function to configure QZSS Max SNR by frequencies and measurements
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF1CodeQZSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF1CodeQZSS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF1CodeQZSS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF1CodeQZSS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF1CodeQZSS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF1CodeQZSS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF1CodeQZSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF1CodeQZSS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF1CodeQZSS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF1CodeQZSS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF1CodeQZSS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF1CodeQZSS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF1CodeQZSS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF1CodeQZSS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF1CodeQZSS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF1CodeQZSS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF2CodeQZSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF2CodeQZSS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF2CodeQZSS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF2CodeQZSS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF2CodeQZSS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF2CodeQZSS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF2CodeQZSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF2CodeQZSS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF2CodeQZSS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF2CodeQZSS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF2CodeQZSS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF2CodeQZSS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF2CodeQZSS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF2CodeQZSS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF2CodeQZSS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF2CodeQZSS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF5CodeQZSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF5CodeQZSS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF5CodeQZSS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF5CodeQZSS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF5CodeQZSS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF5CodeQZSS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF5CodeQZSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF5CodeQZSS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF5CodeQZSS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF5CodeQZSS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF5CodeQZSS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF5CodeQZSS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF5CodeQZSS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF5CodeQZSS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF5CodeQZSS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF5CodeQZSS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF6CodeQZSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF6CodeQZSS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF6CodeQZSS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF6CodeQZSS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF6CodeQZSS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF6CodeQZSS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF6CodeQZSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF6CodeQZSS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF6CodeQZSS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF6CodeQZSS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF6CodeQZSS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF6CodeQZSS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF6CodeQZSS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF6CodeQZSS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF6CodeQZSS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF6CodeQZSS_2->setHidden(true);
    }
}
//IRNSS
// Function to show or hide Min SNR threshold
void GNSS_SNR_Advanced::SetDefaultSNRThresholdMinIRNSS() {
    this->on_comboBoxSNRThresholdsMinIRNSS_currentIndexChanged(4);
    uiSNR->lineEditUserDefinedSNRMinIRNSS->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeIRNSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF5CodeIRNSS_2->setText("");
    uiSNR->lineEditSNRMinSpecificF9CodeIRNSS_1->setText("");
    uiSNR->lineEditSNRMinSpecificF9CodeIRNSS_2->setText("");
    this->on_comboBoxSNRMinMeasF5CodeIRNSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF5CodeIRNSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF5CodeIRNSS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMinMeasF9CodeIRNSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF9CodeIRNSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMinSelectF9CodeIRNSS_2_currentIndexChanged(0);
}
//Function to show or hide text box for user defined Min SNR threshold when SNR combo box changes
void GNSS_SNR_Advanced::on_comboBoxSNRThresholdsMinIRNSS_currentIndexChanged(int index) {
    uiSNR->comboBoxSNRThresholdsMinIRNSS->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRThresholdsMinIRNSS->currentText()=="Specify") {
        uiSNR->lineEditUserDefinedSNRMinIRNSS->setHidden(false);
    } else {
        uiSNR->lineEditUserDefinedSNRMinIRNSS->setHidden(true);
    }
}
//Function to configure IRNSS Min SNR by frequencies and measurements
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF5CodeIRNSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF5CodeIRNSS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF5CodeIRNSS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF5CodeIRNSS_2->isHidden()==true) {
        uiSNR->frameSNRMinF5CodeIRNSS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF5CodeIRNSS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF5CodeIRNSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF5CodeIRNSS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF5CodeIRNSS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF5CodeIRNSS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF5CodeIRNSS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF5CodeIRNSS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF5CodeIRNSS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF5CodeIRNSS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF5CodeIRNSS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF5CodeIRNSS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinMeasF9CodeIRNSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinMeasF9CodeIRNSS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMinF9CodeIRNSS_2->setHidden(true);
    else if (uiSNR->frameSNRMinF9CodeIRNSS_2->isHidden()==true) {
        uiSNR->frameSNRMinF9CodeIRNSS_2->setHidden(false);
        uiSNR->comboBoxSNRMinMeasF9CodeIRNSS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF9CodeIRNSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF9CodeIRNSS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF9CodeIRNSS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF9CodeIRNSS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF9CodeIRNSS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMinSelectF9CodeIRNSS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMinSelectF9CodeIRNSS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMinSelectF9CodeIRNSS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMinSpecificF9CodeIRNSS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMinSpecificF9CodeIRNSS_2->setHidden(true);
    }
}
// Function to show or hide Max SNR threshold
void GNSS_SNR_Advanced::SetDefaultSNRThresholdMaxIRNSS() {
    this->on_comboBoxSNRThresholdsMaxIRNSS_currentIndexChanged(8);
    uiSNR->lineEditUserDefinedSNRMaxIRNSS->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeIRNSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF5CodeIRNSS_2->setText("");
    uiSNR->lineEditSNRMaxSpecificF9CodeIRNSS_1->setText("");
    uiSNR->lineEditSNRMaxSpecificF9CodeIRNSS_2->setText("");
    this->on_comboBoxSNRMaxMeasF5CodeIRNSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF5CodeIRNSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF5CodeIRNSS_2_currentIndexChanged(0);
    this->on_comboBoxSNRMaxMeasF9CodeIRNSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF9CodeIRNSS_1_currentIndexChanged(0);
    this->on_comboBoxSNRMaxSelectF9CodeIRNSS_2_currentIndexChanged(0);
}
//Function to show or hide text box for user defined Max SNR threshold when SNR combo box changes
void GNSS_SNR_Advanced::on_comboBoxSNRThresholdsMaxIRNSS_currentIndexChanged(int index) {
    uiSNR->comboBoxSNRThresholdsMaxIRNSS->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRThresholdsMaxIRNSS->currentText()=="Specify") {
        uiSNR->lineEditUserDefinedSNRMaxIRNSS->setHidden(false);
    } else {
        uiSNR->lineEditUserDefinedSNRMaxIRNSS->setHidden(true);
    }
}
//Function to configure IRNSS Max SNR by frequencies and measurements
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF5CodeIRNSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF5CodeIRNSS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF5CodeIRNSS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF5CodeIRNSS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF5CodeIRNSS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF5CodeIRNSS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF5CodeIRNSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF5CodeIRNSS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF5CodeIRNSS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF5CodeIRNSS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF5CodeIRNSS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF5CodeIRNSS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF5CodeIRNSS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF5CodeIRNSS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF5CodeIRNSS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF5CodeIRNSS_2->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxMeasF9CodeIRNSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxMeasF9CodeIRNSS_1->setCurrentIndex(index);
    if (index==0) uiSNR->frameSNRMaxF9CodeIRNSS_2->setHidden(true);
    else if (uiSNR->frameSNRMaxF9CodeIRNSS_2->isHidden()==true) {
        uiSNR->frameSNRMaxF9CodeIRNSS_2->setHidden(false);
        uiSNR->comboBoxSNRMaxMeasF9CodeIRNSS_2->setCurrentIndex(0);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF9CodeIRNSS_1_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF9CodeIRNSS_1->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF9CodeIRNSS_1->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF9CodeIRNSS_1->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF9CodeIRNSS_1->setHidden(true);
    }
}
void GNSS_SNR_Advanced::on_comboBoxSNRMaxSelectF9CodeIRNSS_2_currentIndexChanged(int index){
    uiSNR->comboBoxSNRMaxSelectF9CodeIRNSS_2->setCurrentIndex(index);
    if(uiSNR->comboBoxSNRMaxSelectF9CodeIRNSS_2->currentText()=="Specify") {
        uiSNR->lineEditSNRMaxSpecificF9CodeIRNSS_2->setHidden(false);
    } else {
        uiSNR->lineEditSNRMaxSpecificF9CodeIRNSS_2->setHidden(true);
    }
}

// Function to select GPS satellites
void GNSS_SNR_Advanced::changePushButtonGPS(bool checked){
    uiSNR->pushButtonGPS->setEnabled(checked);
    if (MinorMax==MINSNRTYPE){ //Min SNR
        this->SetDefaultSNRThresholdMinGPS();
    } else if (MinorMax==MAXSNRTYPE){ //Max SNR
        this->SetDefaultSNRThresholdMaxGPS();
    }
}
// Function to select Galileo satellites
void GNSS_SNR_Advanced::changePushButtonGalileo(bool checked){
    uiSNR->pushButtonGalileo->setEnabled(checked);
    if (MinorMax==MINSNRTYPE){ //Min SNR
        this->SetDefaultSNRThresholdMinGalileo();
    } else if (MinorMax==MAXSNRTYPE){ //Max SNR
        this->SetDefaultSNRThresholdMaxGalileo();
    }
}
// Function to select GLONASS satellites
void GNSS_SNR_Advanced::changePushButtonGLONASS(bool checked){
    uiSNR->pushButtonGLONASS->setEnabled(checked);
    if (MinorMax==MINSNRTYPE){ //Min SNR
        this->SetDefaultSNRThresholdMinGLONASS();
    } else if (MinorMax==MAXSNRTYPE){ //Max SNR
        this->SetDefaultSNRThresholdMaxGLONASS();
    }
}
// Function to select GEO satellites
void GNSS_SNR_Advanced::changePushButtonGEO(bool checked){
    uiSNR->pushButtonGEO->setEnabled(checked);
    if (MinorMax==MINSNRTYPE){ //Min SNR
        this->SetDefaultSNRThresholdMinGEO();
    } else if (MinorMax==MAXSNRTYPE){ //Max SNR
        this->SetDefaultSNRThresholdMaxGEO();
    }
}
// Function to select BDS satellites
void GNSS_SNR_Advanced::changePushButtonBDS(bool checked){
    uiSNR->pushButtonBDS->setEnabled(checked);
    if (MinorMax==MINSNRTYPE){ //Min SNR
        this->SetDefaultSNRThresholdMinBDS();
    } else if (MinorMax==MAXSNRTYPE){ //Max SNR
        this->SetDefaultSNRThresholdMaxBDS();
    }
}
// Function to select QZSS satellites
void GNSS_SNR_Advanced::changePushButtonQZSS(bool checked){
    uiSNR->pushButtonQZSS->setEnabled(checked);
    if (MinorMax==MINSNRTYPE){ //Min SNR
        this->SetDefaultSNRThresholdMinQZSS();
    } else if (MinorMax==MAXSNRTYPE){ //Max SNR
        this->SetDefaultSNRThresholdMaxQZSS();
    }
}
// Function to select IRNSS satellites
void GNSS_SNR_Advanced::changePushButtonIRNSS(bool checked){
    uiSNR->pushButtonIRNSS->setEnabled(checked);
    if (MinorMax==MINSNRTYPE){ //Min SNR
        this->SetDefaultSNRThresholdMinIRNSS();
    } else if (MinorMax==MAXSNRTYPE){ //Max SNR
        this->SetDefaultSNRThresholdMaxIRNSS();
    }
}

// Function to configure GPS satellites
void GNSS_SNR_Advanced::on_pushButtonPublicGPS_clicked(){
    this->on_pushButtonGPS_clicked();
}
// Function to configure Galileo satellites
void GNSS_SNR_Advanced::on_pushButtonPublicGalileo_clicked(){
    this->on_pushButtonGalileo_clicked();
}
// Function to configure GLONASS satellites
void GNSS_SNR_Advanced::on_pushButtonPublicGLONASS_clicked(){
    this->on_pushButtonGLONASS_clicked();
}
// Function to configure GEO satellites
void GNSS_SNR_Advanced::on_pushButtonPublicGEO_clicked(){
    this->on_pushButtonGEO_clicked();
}
// Function to configure BDS satellites
void GNSS_SNR_Advanced::on_pushButtonPublicBDS_clicked(){
    this->on_pushButtonBDS_clicked();
}
// Function to configure QZSS satellites
void GNSS_SNR_Advanced::on_pushButtonPublicQZSS_clicked(){
    this->on_pushButtonQZSS_clicked();
}
// Function to configure IRNSS satellites
void GNSS_SNR_Advanced::on_pushButtonPublicIRNSS_clicked(){
    this->on_pushButtonIRNSS_clicked();
}

void GNSS_SNR_Advanced::changeCurrentPage(){
    for (int i=0; i<MAX_GNSS; i++){
        if (PushButtonGNSS[i]->isEnabled()){
            (this->*PushButtonGNSSFunctions[i])();
            break;
        }
    }
}

//Function to get command line options. Returns 0 if no error, 1 if an error was encountered
int GNSS_SNR_Advanced::getgLABOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString){
    QString DefaultOptions[MAX_GNSS]={""};
    QString SNRType=MinorMax==MINSNRTYPE?"Min":"Max";
    QString SNRDefault=MinorMax==MINSNRTYPE?"33":"54";
    QString commandStr=MinorMax==MINSNRTYPE?"-pre:minsnrsel":"-pre:maxsnrsel";
    QStringList SNRArgList[MAX_GNSS];
    int numArgList[MAX_GNSS]={0};
    int firstArg=1;
    int errorflag=0;
    for (int i=0; i<MAX_GNSS; i++) {
        //check if this constellation is selected
        if (this->PushButtonGNSS[i]->isEnabled()!=true) continue;
        //get default SNR
        switch(this->ComboBoxGNSSDefaultSNR[MinorMax][i]->currentIndex()) {
            case 0:
                DefaultOptions[i]="12";
                break;
            case 1:
                DefaultOptions[i]="18";
                break;
            case 2:
                DefaultOptions[i]="24";
                break;
            case 3:
                DefaultOptions[i]="30";
                break;
            case 4:
                DefaultOptions[i]="33";
                break;
            case 5:
                DefaultOptions[i]="36";
                break;
            case 6:
                DefaultOptions[i]="42";
                break;
            case 7:
                DefaultOptions[i]="48";
                break;
            case 8:
                DefaultOptions[i]="54";
                break;
            case 9:
                if(this->LineEditGNSSDefaultSNR[MinorMax][i]->text()=="") {
                    *errorString += "PREPROCESS: A numerical value is required for Default " + SNRType + " SNR Mask for " + GNSSName[i] + " in the " + SNRType + " SNR Advanced Dialog.\n";
                    errorflag=1;
                } else if (this->LineEditGNSSDefaultSNR[MinorMax][i]->text().toDouble()<=0) {
                    *errorString += "PREPROCESS: Default " + SNRType + " SNR Mask must be greater than 0 for " + GNSSName[i] + " in the " + SNRType + " SNR Advanced Dialog.\n";
                    errorflag=1;
                } else {
                    DefaultOptions[i]= this->LineEditGNSSDefaultSNR[MinorMax][i]->text();
                }
                break;
        }

        //Some not set as default
        for (int j=0; j<nFreqGNSS[i]; j++) {
            QString measOption2[2]={""};
            for (int k=0; k<2; k++) {
                if ( k==0 || this->ComboBoxGNSSMeas[MinorMax][i][j][0]->currentIndex()!=0 ) {
                    if (this->ComboBoxGNSSSNR[MinorMax][i][j][k]->currentIndex()!=0) {
                        if (k==1) {
                            if (this->ComboBoxGNSSMeas[MinorMax][i][j][0]->currentIndex()==this->ComboBoxGNSSMeas[MinorMax][i][j][1]->currentIndex()) {
                                if (this->ComboBoxGNSSSNR[MinorMax][i][j][0]->currentIndex()==this->ComboBoxGNSSSNR[MinorMax][i][j][1]->currentIndex()) {
                                    if (this->ComboBoxGNSSSNR[MinorMax][i][j][0]->currentIndex()<10
                                            || (this->ComboBoxGNSSSNR[MinorMax][i][j][0]->currentIndex()==10
                                                  && this->LineEditGNSSSNR[MinorMax][i][j][0]->text()==this->LineEditGNSSSNR[MinorMax][i][j][1]->text()
                                                  && this->LineEditGNSSSNR[MinorMax][i][j][0]->text()!="" )) {
                                        //SNR in one frequency and signal repetead and equal
                                        *warningString += "PREPROCESS: " + SNRType + " SNR Mask is repeated for " + GNSSName[i] + " F" + FreqGNSSList[i][j] + " in the " + SNRType + " SNR Advanced Dialog. It will be used only once.\n";
                                        continue;
                                    } else {
                                        if (!(this->ComboBoxGNSSSNR[MinorMax][i][j][0]->currentIndex()==10 && (this->LineEditGNSSSNR[MinorMax][i][j][0]->text()==""
                                              || this->LineEditGNSSSNR[MinorMax][i][j][1]->text()=="")) ) {
                                            *errorString += "PREPROCESS: " + SNRType + " SNR Mask is set twice for " + GNSSName[i] + " F" + FreqGNSSList[i][j] + " with different values in the " + SNRType + " SNR Advanced Dialog. Set it only once.\n";
                                            errorflag=1;
                                        }
                                    }
                                } else if ( (this->ComboBoxGNSSSNR[MinorMax][i][j][0]->currentIndex()==10 && this->ComboBoxGNSSSNR[MinorMax][i][j][1]->currentIndex()!=10
                                           && this->LineEditGNSSSNR[MinorMax][i][j][0]->text()==this->ComboBoxGNSSSNR[MinorMax][i][j][1]->currentText() ) ||
                                            (this->ComboBoxGNSSSNR[MinorMax][i][j][1]->currentIndex()==10 && this->ComboBoxGNSSSNR[MinorMax][i][j][0]->currentIndex()!=10
                                           && this->LineEditGNSSSNR[MinorMax][i][j][1]->text()==this->ComboBoxGNSSSNR[MinorMax][i][j][0]->currentText() )) {
                                    *warningString += "PREPROCESS: " + SNRType + " SNR Mask is repeated for " + GNSSName[i] + " F" + FreqGNSSList[i][j] + " in the " + SNRType + " SNR Advanced Dialog. It will be used only once.\n";
                                    continue;
                                } else {
                                    *errorString += "PREPROCESS: " + SNRType + " SNR Mask is set twice for " + GNSSName[i] + " F" + FreqGNSSList[i][j] + " with different values in the " + SNRType + " SNR Advanced Dialog. Set it only once.\n";
                                    errorflag=1;
                                }
                            }
                        }
                        QString SNRvalue="";
                        switch(this->ComboBoxGNSSSNR[MinorMax][i][j][k]->currentIndex()) {
                            case 1:
                                SNRvalue= "12";
                                break;
                            case 2:
                                SNRvalue= "18";
                                break;
                            case 3:
                                SNRvalue= "24";
                                break;
                            case 4:
                                SNRvalue= "30";
                                break;
                            case 5:
                                SNRvalue= "33";
                                break;
                            case 6:
                                SNRvalue= "36";
                                break;
                            case 7:
                                SNRvalue= "42";
                                break;
                            case 8:
                                SNRvalue= "48";
                                break;
                            case 9:
                                SNRvalue= "54";
                                break;
                            case 10:
                                if(this->LineEditGNSSSNR[MinorMax][i][j][k]->text()=="") {
                                    *errorString += "PREPROCESS: A numerical value is required for " + SNRType + " SNR Mask for " + GNSSName[i] + " F" + FreqGNSSList[i][j] + " Meas " + QString::number(k+1) + " in the " + SNRType + " SNR Advanced Dialog.\n";
                                    errorflag=1;
                                } else if (this->LineEditGNSSSNR[MinorMax][i][j][k]->text().toDouble()<=0) {
                                    *errorString += "PREPROCESS: Default " + SNRType + " SNR Mask must be greater than 0 for " + GNSSName[i] + " F" + FreqGNSSList[i][j] + " Meas " + QString::number(k+1) + " in the " + SNRType + " SNR Advanced Dialog.\n";
                                    errorflag=1;
                                } else {
                                    SNRvalue= this->LineEditGNSSSNR[MinorMax][i][j][k]->text();
                                }
                                break;
                        }
                        if ( SNRvalue!=SNRDefault && SNRvalue!=DefaultOptions[i] ) {
                            measOption2[k] = indentifierGNSS[i] + "0 " + SNRvalue + " " +
                                    ( this->ComboBoxGNSSMeas[MinorMax][i][j][k]->currentIndex()==0?
                                          FreqGNSSList[i][j] : ("L"+this->ComboBoxGNSSMeas[MinorMax][i][j][k]->currentText()) );
                        }
                    } else if (k==1) {
                        if (this->ComboBoxGNSSMeas[MinorMax][i][j][0]->currentIndex()==this->ComboBoxGNSSMeas[MinorMax][i][j][1]->currentIndex()
                                && this->ComboBoxGNSSSNR[MinorMax][i][j][0]->currentIndex()==this->ComboBoxGNSSSNR[MinorMax][i][j][1]->currentIndex()) {
                            //SNR in one frequency and signal repetead and equal
                            *warningString += "PREPROCESS: " + SNRType + " SNR Mask is repeated for " + GNSSName[i] + " F" + FreqGNSSList[i][j] + " in the " + SNRType + " SNR Advanced Dialog. It will be used only once.\n";
                            continue;
                        }
                    }
                }
            }
            if (measOption2[0]!="" || measOption2[1]!="") {
                if ( this->ComboBoxGNSSMeas[MinorMax][i][j][0]->currentIndex()!=0 && this->ComboBoxGNSSMeas[MinorMax][i][j][1]->currentIndex()==0 ) {
                    if (measOption2[0]!="") {
                        SNRArgList[i].append(measOption2[1]);
                        numArgList[i]++;
                    }
                    if (measOption2[1]!="") {
                        SNRArgList[i].append(measOption2[0]);
                        numArgList[i]++;
                    }
                } else {
                    if (measOption2[0]!="") {
                        SNRArgList[i].append(measOption2[0]);
                        numArgList[i]++;
                    }
                    if (measOption2[1]!="") {
                        SNRArgList[i].append(measOption2[1]);
                        numArgList[i]++;
                    }
                }
            }

        }
    }

    //get options
    if (errorflag!=0){
        return errorflag;
    }

    //Add constellation letter in Default options
    for (int i=0; i<MAX_GNSS; i++) {
        if (DefaultOptions[i]=="") continue;
        DefaultOptions[i] = indentifierGNSS[i] + "0 " + DefaultOptions[i];
    }

    //Merge default SNR options
    for (int i=0; i<MAX_GNSS; i++) {
        for (int j=0; j<MAX_GNSS; j++) {
            if (i==j) continue;
            if (DefaultOptions[i]=="" || DefaultOptions[j]=="") continue;
            int pos1,pos2;
            pos1=DefaultOptions[i].indexOf(" ")+1;
            pos2=DefaultOptions[j].indexOf(" ")+1;
            if (QString::compare(DefaultOptions[i].mid(pos1),DefaultOptions[j].mid(pos2))==0 ) {
                DefaultOptions[i].insert(pos1-2,indentifierGNSS[j]);
                DefaultOptions[j]="";
            }
        }
    }

    //Save default options
    firstArg=1;
    for (int i=0; i<MAX_GNSS; i++){
        if (DefaultOptions[i]=="") continue;
        int pos1;
        pos1=DefaultOptions[i].indexOf(" ")+1;
        if (DefaultOptions[i].mid(pos1)!=SNRDefault){
            if (firstArg==1) {
                firstArg=0;
                *saveString += commandStr;
                *runString << commandStr;
            }
            *saveString += " " + DefaultOptions[i];
            QStringList tmpString = DefaultOptions[i].split(QRegularExpression("\\s+"));
            for(int k=0;k<tmpString.size();k++) {
                *runString << tmpString[k];
            }
        }
    }
    if (firstArg==0) *saveString += "\n";

    //Merge non default options
    for (int i=0; i<MAX_GNSS; i++) {
        for (int j=0; j<numArgList[i]; j++) {
            for (int i2=0; i2<MAX_GNSS; i2++) {
                if (i==i2) continue;
                for (int j2=0; j2<numArgList[i2]; j2++) {
                    if (SNRArgList[i].at(j)=="" || SNRArgList[i2].at(j2)=="") continue;
                    int pos1,pos2;
                    pos1=SNRArgList[i].at(j).indexOf(" ")+1;
                    pos2=SNRArgList[i2].at(j2).indexOf(" ")+1;
                    if (QString::compare(SNRArgList[i].at(j).mid(pos1),SNRArgList[i2].at(j2).mid(pos2))==0 ) {
                        QString tmpParam = SNRArgList[i].at(j);
                        tmpParam.insert(pos1-2,indentifierGNSS[i2]);
                        SNRArgList[i].replace(j,tmpParam);
                        SNRArgList[i2].replace(j2,"");
                    }
                }
            }
        }
    }

    //Save non default options
    firstArg=1;
    for (int i=0; i<MAX_GNSS; i++) {
        for (int j=0; j<numArgList[i]; j++) {
            if (SNRArgList[i].at(j)=="") continue;
            if (firstArg==1) {
                firstArg=0;
                *saveString += commandStr;
                *runString << commandStr;
            }
            *saveString += " " + SNRArgList[i].at(j);
            QStringList tmpString = SNRArgList[i].at(j).split(QRegularExpression("\\s+"));
            for(int k=0;k<tmpString.size();k++) {
                *runString << tmpString[k];
            }

        }
    }
    if (firstArg==0) *saveString += "\n";

    return 0;
}

void GNSS_SNR_Advanced::loadgLABOptions(QString *warningString, QStringList *ParametersList){
    QString SNRvalue="",SNRType=MinorMax==MINSNRTYPE?"Min":"Max";
    QString currentParams="";
    int SNRIndex=-1,SNRDefault=MinorMax==MINSNRTYPE?4:8;
    int setFreq[MAX_GNSS][MAX_GNSS_FREQ]={{0}},setMeas[MAX_GNSS][MAX_GNSS_FREQ][MAX_GNSS_CODE]={{{0}}};
    int gnssDef[MAX_GNSS]={0},setCount[MAX_GNSS][MAX_GNSS_FREQ]={{0}};
    int optionIndex=0,setGUI=0,nPar=ParametersList->count(),GNSSFlag[MAX_GNSS]={0};
    int SNRintVal;
    double  SNRdoubleVal;
    bool SNROK=false,SNROKint=false,SNROKdouble=false;
    for (int iPar=0; iPar<nPar; iPar++){
        optionIndex++;
        //if this is constellation
        if (optionIndex==1){
            if (ParametersList->at(iPar)=="0" || ParametersList->at(iPar)=="+0" || ParametersList->at(iPar)=="-0" ) {
                int tmpFlag=1;
                if (ParametersList->at(iPar)=="-0") tmpFlag=0;
                //All constellations. Set only the default value
                for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
                    GNSSFlag[iGNSS]=tmpFlag;
                    //reset freq and meas
                    for (int iF=0; iF<MAX_GNSS_FREQ; iF++){
                        setFreq[iGNSS][iF]=0;
                        for (int iM=0; iM<MAX_GNSS_CODE; iM++) setMeas[iGNSS][iF][iM]=0;
                    }
                }
            } else {
                currentParams=ParametersList->at(iPar);
                QStringList MeasOpt=ParametersList->at(iPar).split("-", QString::SkipEmptyParts);
                bool ParamSatRanges=ParametersList->at(iPar).contains(QRegularExpression(regExpSatWithRanges));
                bool ParamSatNoRanges=MeasOpt[0].contains(QRegularExpression(regExpSatNoRanges));
                if(!ParamSatNoRanges && !ParamSatRanges ) {
                   *warningString += "FILTER: Invalid SNR measurement '" + ParametersList->at(iPar) + "'. It was skipped.\n";
                    iPar++;
                   continue;
                } else if (ParamSatRanges) {
                   *warningString += "FILTER: The GUI cannot read parameters with satellite ranges (except '-pre:sat'), as options are constellations wise. Parameter '" + ParametersList->at(iPar) + "' was skipped.\n";
                    iPar++;
                   continue;
                }
                //get constellation list
                for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
                    if (ParametersList->at(iPar).contains(indentifierGNSS[iGNSS],Qt::CaseInsensitive)) GNSSFlag[iGNSS]=1;
                    else GNSSFlag[iGNSS]=0;
                    //reset freq and meas
                    for (int iF=0; iF<MAX_GNSS_FREQ; iF++){
                        setFreq[iGNSS][iF]=0;
                        for (int iM=0; iM<MAX_GNSS_CODE; iM++) setMeas[iGNSS][iF][iM]=0;
                    }
                }
            }
        }
        //if this is SNR value, determine if the next parameter is constellation
        else if ( optionIndex==2 ){
            currentParams+=" " + ParametersList->at(iPar);
            //get SNR index
            SNRIndex=-1;
            SNRvalue=ParametersList->at(iPar);
            SNRintVal=SNRvalue.toInt(&SNROKint);
            SNRdoubleVal=SNRvalue.toDouble(&SNROKdouble);
            if (SNROKint) {
                if (SNRintVal<=0) {
                    *warningString += SNRType + " SNR ratio in parameter '" + SNRvalue + "' must greater than 0.\n";
                }
                SNROK=true;
                for (int iSNR=0; iSNR<nSNRDef; iSNR++){
                    if (SNRvalue==SNRDefValue[iSNR]) SNRIndex=iSNR;
                }
            } else if (SNROKdouble) {
                if (SNRdoubleVal<=0.) {
                    *warningString += SNRType + " SNR ratio in parameter '" + SNRvalue + "' must greater than 0.\n";
                }
                SNROK=true;
            } else {
                *warningString += SNRType + " SNR ratio in parameter '" + SNRvalue + "' must be greater than 0.\n";
            }
            if (SNRIndex<0) SNRIndex=nSNRDef;
            //determine if the next parameter is constellation
            if (iPar+1<nPar){
                int foundGNSS=0;
                for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++){
                    if (ParametersList->at(iPar+1).toUpper().mid(0,1) == indentifierGNSS[iGNSS]) {
                        //determine if the next parameter is constellation
                        if (iGNSS!=4) {
                            foundGNSS=1;
                        } else {
                            if ( ParametersList->at(iPar+1).size()>=3 ) {
                                if ( !( (ParametersList->at(iPar+1).mid(1,1).contains(QRegularExpression("[1-9]"))) && (ParametersList->at(iPar+1).mid(2,1).contains(QRegularExpression("[a-zA-Z]"))) ) ) {
                                    foundGNSS=1;
                                }
                            } else {
                                foundGNSS=1;
                            }
                        }
                    }
                }

                if (foundGNSS==1) {
                    setGUI=1;
                    optionIndex=0;
                }

                if (optionIndex>0) {
                    setGUI=2;
                    //next parameter should be constellation
                    optionIndex=0;
                    iPar++;
                    currentParams+=" " + ParametersList->at(iPar);
                    //get frequency and measurement
                    QStringList FreqMeasList = ParametersList->at(iPar).split("-", QString::SkipEmptyParts);
                    for (int iFM=0; iFM<FreqMeasList.count(); iFM++) {
                        //if frequency
                        if (FreqMeasList[iFM].size()>0 && FreqMeasList[iFM][0]>'0' && FreqMeasList[iFM][0]<='9') {
                            for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
                                if (GNSSFlag[iGNSS]) {
                                    int foundFrequency=0;
                                    for (int iF=0; iF<nFreqGNSS[iGNSS]; iF++) {
                                        if (FreqMeasList[iFM].contains(FreqGNSSList[iGNSS][iF])) {
                                            setFreq[iGNSS][iF]=1;
                                            foundFrequency=1;
                                            break;
                                        }
                                    }
                                    if (foundFrequency!=1) {
                                        *warningString += "PREPROCESS: " + SNRType + " SNR frequency '" + FreqMeasList[iFM] + "' in argument '" + currentParams + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                                        continue;
                                    }
                                }
                            }
                        }
                        //if measurement
                        else {
                            for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
                                if (GNSSFlag[iGNSS]) {
                                    int foundMeasurement=0,freqFound=0;
                                    for (int iF=0; iF<nFreqGNSS[iGNSS]; iF++){
                                        if (FreqMeasList[iFM].contains(FreqGNSSList[iGNSS][iF])) {
                                            freqFound=1;
                                            for (int iM=0; iM<MeasGNSSOrder[iGNSS][iF].size(); iM++){
                                                if (MeasGNSSOrder[iGNSS][iF][iM]==FreqMeasList[iFM][2].toUpper()) {
                                                    setMeas[iGNSS][iF][iM]=1;
                                                    foundMeasurement=1;
                                                    break;
                                                }
                                            }
                                            if (foundMeasurement!=1) {
                                                *warningString += "PREPROCESS: " + SNRType + " SNR measuremement '" + FreqMeasList[iFM] + "' in argument '" + currentParams + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                                                continue;
                                            }
                                        }
                                    }
                                    if (freqFound==0) {
                                        *warningString += "PREPROCESS: " + SNRType + " SNR frequency in measurement '" + FreqMeasList[iFM] + "' in argument '" + currentParams + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                                        continue;
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                setGUI=1;
            }
        }
        //if this is frequency or measurement

        if ( SNROK && SNRIndex!=SNRDefault ) {
            //config GUI : SNR for all
            if (setGUI==1){
                for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
                    if ( GNSSFlag[iGNSS] && gnssDef[iGNSS]<1 ) {
                        this->ComboBoxGNSSDefaultSNR[MinorMax][iGNSS]->setCurrentIndex(SNRIndex);
                        if ( SNRIndex==nSNRDef ) this->LineEditGNSSDefaultSNR[MinorMax][iGNSS]->setText(SNRvalue);
                        gnssDef[iGNSS]=1;
                    }
                }
            }
            //config GUI : SNR for specified Freq and Meas
            else if (setGUI==2){
                for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
                    if (GNSSFlag[iGNSS]!=1) continue;
                    for (int iF=0; iF<nFreqGNSS[iGNSS]; iF++) {
                        //frequency
                        if ( setFreq[iGNSS][iF]>0 && setCount[iGNSS][iF]<2 ) {
                            this->ComboBoxGNSSSNR[MinorMax][iGNSS][iF][setCount[iGNSS][iF]]->setCurrentIndex(SNRIndex+1);
                            if ( SNRIndex==nSNRDef ) this->LineEditGNSSSNR[MinorMax][iGNSS][iF][setCount[iGNSS][iF]]->setText(SNRvalue);
                            setCount[iGNSS][iF]++;
                        } else if (setFreq[iGNSS][iF]>0 && setCount[iGNSS][iF]>=2 ) {
                            *warningString += "PREPROCESS: Maximum number of " + SNRType + " SNR measurements per constellation and frequency is 2. Arguments '" + currentParams + "' were skipped for " + GNSSName[iGNSS] + " frequency " + FreqGNSSList[iGNSS][iF] + " as limit has been surpassed.\n";
                            continue;
                        }
                        //measurement
                        for (int iM=0; iM<MeasGNSSOrder[iGNSS][iF].size(); iM++){
                            if ( setMeas[iGNSS][iF][iM]>0 && setCount[iGNSS][iF]<2 ) {
                                if ( setCount[iGNSS][iF]==0 || this->ComboBoxGNSSMeas[MinorMax][iGNSS][iF][0]->currentIndex()!=0 ){
                                    this->ComboBoxGNSSSNR[MinorMax][iGNSS][iF][setCount[iGNSS][iF]]->setCurrentIndex(SNRIndex+1);
                                    if ( SNRIndex==nSNRDef ) this->LineEditGNSSSNR[MinorMax][iGNSS][iF][setCount[iGNSS][iF]]->setText(SNRvalue);
                                    this->ComboBoxGNSSMeas[MinorMax][iGNSS][iF][setCount[iGNSS][iF]]->setCurrentIndex(iM+1);
                                }
                                //if already set SNR for all measurement of this frequency
                                else {
                                    //set the 2nd measurement of this frequency using the 1st one
                                    this->ComboBoxGNSSSNR[MinorMax][iGNSS][iF][1]->setCurrentIndex(this->ComboBoxGNSSSNR[MinorMax][iGNSS][iF][0]->currentIndex());
                                    this->LineEditGNSSSNR[MinorMax][iGNSS][iF][1]->setText(this->LineEditGNSSSNR[MinorMax][iGNSS][iF][0]->text());
                                    this->ComboBoxGNSSMeas[MinorMax][iGNSS][iF][1]->setCurrentIndex(0);
                                    //set the 1st measurement of this frequency using the new SNR
                                    this->ComboBoxGNSSSNR[MinorMax][iGNSS][iF][0]->setCurrentIndex(SNRIndex+1);
                                    if ( SNRIndex==nSNRDef ) this->LineEditGNSSSNR[MinorMax][iGNSS][iF][0]->setText(SNRvalue);
                                    this->ComboBoxGNSSMeas[MinorMax][iGNSS][iF][0]->setCurrentIndex(iM+1);
                                }
                                setCount[iGNSS][iF]++;
                            } else if (setMeas[iGNSS][iF][iM]>0 && setCount[iGNSS][iF]>=2 ) {
                                *warningString += "PREPROCESS: Maximum number of " + SNRType + " SNR measurements per constellation and frequency is 2. Arguments '" + currentParams + "' were skipped for " + GNSSName[iGNSS] + " frequency " + FreqGNSSList[iGNSS][iF] + " as limit has been surpassed.\n";
                                continue;
                            }
                        }
                    }
                }
            }
            SNROK=false;
            setGUI=0;
        }
    }
}

void GNSS_SNR_Advanced::on_pushButtonSNRAdvancedDefault_clicked(){
    this->setSNRdefaults();
}
void GNSS_SNR_Advanced::on_pushButtonSNRAdvancedOk_clicked(){
    this->OkFlag=1;
    this->close();
}
void GNSS_SNR_Advanced::on_pushButtonSNRAdvancedCancel_clicked(){
    this->OkFlag=0;
    this->close();
}
