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
#include "glab_const.h"
#include "sbas_obad_set.h"
#include "ui_sbas_obad_set.h"

GNSS_SBAS_OBAD_Set::GNSS_SBAS_OBAD_Set(QWidget *parent) :
    QDialog(parent),
    uiSBASOBAD(new Ui::GNSS_SBAS_OBAD_Set)
{
    uiSBASOBAD->setupUi(this);

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

    this->setWindowTitle("Set OBAD Parameter from MT 37");
    this->InitOBADPointers();

    // Set the locale to avoid comma as decimator and reject the group separator
    QLocale qlocale(QLocale::C);
    qlocale.setNumberOptions(QLocale::RejectGroupSeparator);
    auto ldouble = new QDoubleValidator(-100000000, 100000000,6, this);
    ldouble->setLocale(qlocale);
    //GPS
    uiSBASOBAD->lineEditIcorrOBADGPS->setValidator(ldouble);
    uiSBASOBAD->lineEditCcorrOBADGPS->setValidator(ldouble);
    uiSBASOBAD->lineEditRcorrOBADGPS->setValidator(ldouble);
    //Galileo
    uiSBASOBAD->lineEditIcorrOBADGalileo->setValidator(ldouble);
    uiSBASOBAD->lineEditCcorrOBADGalileo->setValidator(ldouble);
    uiSBASOBAD->lineEditRcorrOBADGalileo->setValidator(ldouble);
    //GLONASS
    uiSBASOBAD->lineEditIcorrOBADGLONASS->setValidator(ldouble);
    uiSBASOBAD->lineEditCcorrOBADGLONASS->setValidator(ldouble);
    uiSBASOBAD->lineEditRcorrOBADGLONASS->setValidator(ldouble);
    //GEO
    uiSBASOBAD->lineEditIcorrOBADGEO->setValidator(ldouble);
    uiSBASOBAD->lineEditCcorrOBADGEO->setValidator(ldouble);
    uiSBASOBAD->lineEditRcorrOBADGEO->setValidator(ldouble);
    //BDS
    uiSBASOBAD->lineEditIcorrOBADBDS->setValidator(ldouble);
    uiSBASOBAD->lineEditCcorrOBADBDS->setValidator(ldouble);
    uiSBASOBAD->lineEditRcorrOBADBDS->setValidator(ldouble);
    //QZSS
    uiSBASOBAD->lineEditIcorrOBADQZSS->setValidator(ldouble);
    uiSBASOBAD->lineEditCcorrOBADQZSS->setValidator(ldouble);
    uiSBASOBAD->lineEditRcorrOBADQZSS->setValidator(ldouble);
    //IRNSS
    uiSBASOBAD->lineEditIcorrOBADIRNSS->setValidator(ldouble);
    uiSBASOBAD->lineEditCcorrOBADIRNSS->setValidator(ldouble);
    uiSBASOBAD->lineEditRcorrOBADIRNSS->setValidator(ldouble);

    uiSBASOBAD->pushButtonSBASOBADAdvancedOk->setFocus();

}

GNSS_SBAS_OBAD_Set::~GNSS_SBAS_OBAD_Set()
{
    delete uiSBASOBAD;
}

//initialize OBAD pointers
void GNSS_SBAS_OBAD_Set::InitOBADPointers(){
    //GPS
    RadioButtonGNSSOBAD[GPS][0]=uiSBASOBAD->radioButtonIcorrOBADReadMT37GPS;
    RadioButtonGNSSOBAD[GPS][1]=uiSBASOBAD->radioButtonIcorrOBADUserDefinedGPS;
    RadioButtonGNSSOBAD[GPS][2]=uiSBASOBAD->radioButtonCcorrOBADReadMT37GPS;
    RadioButtonGNSSOBAD[GPS][3]=uiSBASOBAD->radioButtonCcorrOBADUserDefinedGPS;
    RadioButtonGNSSOBAD[GPS][4]=uiSBASOBAD->radioButtonRcorrOBADReadMT37GPS;
    RadioButtonGNSSOBAD[GPS][5]=uiSBASOBAD->radioButtonRcorrOBADUserDefinedGPS;
    LineEditGNSSOBAD[GPS][0]=uiSBASOBAD->lineEditIcorrOBADGPS;
    LineEditGNSSOBAD[GPS][1]=uiSBASOBAD->lineEditCcorrOBADGPS;
    LineEditGNSSOBAD[GPS][2]=uiSBASOBAD->lineEditRcorrOBADGPS;
    //Galileo
    RadioButtonGNSSOBAD[Galileo][0]=uiSBASOBAD->radioButtonIcorrOBADReadMT37Galileo;
    RadioButtonGNSSOBAD[Galileo][1]=uiSBASOBAD->radioButtonIcorrOBADUserDefinedGalileo;
    RadioButtonGNSSOBAD[Galileo][2]=uiSBASOBAD->radioButtonCcorrOBADReadMT37Galileo;
    RadioButtonGNSSOBAD[Galileo][3]=uiSBASOBAD->radioButtonCcorrOBADUserDefinedGalileo;
    RadioButtonGNSSOBAD[Galileo][4]=uiSBASOBAD->radioButtonRcorrOBADReadMT37Galileo;
    RadioButtonGNSSOBAD[Galileo][5]=uiSBASOBAD->radioButtonRcorrOBADUserDefinedGalileo;
    LineEditGNSSOBAD[Galileo][0]=uiSBASOBAD->lineEditIcorrOBADGalileo;
    LineEditGNSSOBAD[Galileo][1]=uiSBASOBAD->lineEditCcorrOBADGalileo;
    LineEditGNSSOBAD[Galileo][2]=uiSBASOBAD->lineEditRcorrOBADGalileo;
    //GLONASS
    RadioButtonGNSSOBAD[GLONASS][0]=uiSBASOBAD->radioButtonIcorrOBADReadMT37GLONASS;
    RadioButtonGNSSOBAD[GLONASS][1]=uiSBASOBAD->radioButtonIcorrOBADUserDefinedGLONASS;
    RadioButtonGNSSOBAD[GLONASS][2]=uiSBASOBAD->radioButtonCcorrOBADReadMT37GLONASS;
    RadioButtonGNSSOBAD[GLONASS][3]=uiSBASOBAD->radioButtonCcorrOBADUserDefinedGLONASS;
    RadioButtonGNSSOBAD[GLONASS][4]=uiSBASOBAD->radioButtonRcorrOBADReadMT37GLONASS;
    RadioButtonGNSSOBAD[GLONASS][5]=uiSBASOBAD->radioButtonRcorrOBADUserDefinedGLONASS;
    LineEditGNSSOBAD[GLONASS][0]=uiSBASOBAD->lineEditIcorrOBADGLONASS;
    LineEditGNSSOBAD[GLONASS][1]=uiSBASOBAD->lineEditCcorrOBADGLONASS;
    LineEditGNSSOBAD[GLONASS][2]=uiSBASOBAD->lineEditRcorrOBADGLONASS;
    //GEO
    RadioButtonGNSSOBAD[GEO][0]=uiSBASOBAD->radioButtonIcorrOBADReadMT37GEO;
    RadioButtonGNSSOBAD[GEO][1]=uiSBASOBAD->radioButtonIcorrOBADUserDefinedGEO;
    RadioButtonGNSSOBAD[GEO][2]=uiSBASOBAD->radioButtonCcorrOBADReadMT37GEO;
    RadioButtonGNSSOBAD[GEO][3]=uiSBASOBAD->radioButtonCcorrOBADUserDefinedGEO;
    RadioButtonGNSSOBAD[GEO][4]=uiSBASOBAD->radioButtonRcorrOBADReadMT37GEO;
    RadioButtonGNSSOBAD[GEO][5]=uiSBASOBAD->radioButtonRcorrOBADUserDefinedGEO;
    LineEditGNSSOBAD[GEO][0]=uiSBASOBAD->lineEditIcorrOBADGEO;
    LineEditGNSSOBAD[GEO][1]=uiSBASOBAD->lineEditCcorrOBADGEO;
    LineEditGNSSOBAD[GEO][2]=uiSBASOBAD->lineEditRcorrOBADGEO;
    //BDS
    RadioButtonGNSSOBAD[BDS][0]=uiSBASOBAD->radioButtonIcorrOBADReadMT37BDS;
    RadioButtonGNSSOBAD[BDS][1]=uiSBASOBAD->radioButtonIcorrOBADUserDefinedBDS;
    RadioButtonGNSSOBAD[BDS][2]=uiSBASOBAD->radioButtonCcorrOBADReadMT37BDS;
    RadioButtonGNSSOBAD[BDS][3]=uiSBASOBAD->radioButtonCcorrOBADUserDefinedBDS;
    RadioButtonGNSSOBAD[BDS][4]=uiSBASOBAD->radioButtonRcorrOBADReadMT37BDS;
    RadioButtonGNSSOBAD[BDS][5]=uiSBASOBAD->radioButtonRcorrOBADUserDefinedBDS;
    LineEditGNSSOBAD[BDS][0]=uiSBASOBAD->lineEditIcorrOBADBDS;
    LineEditGNSSOBAD[BDS][1]=uiSBASOBAD->lineEditCcorrOBADBDS;
    LineEditGNSSOBAD[BDS][2]=uiSBASOBAD->lineEditRcorrOBADBDS;
    //QZSS
    RadioButtonGNSSOBAD[QZSS][0]=uiSBASOBAD->radioButtonIcorrOBADReadMT37QZSS;
    RadioButtonGNSSOBAD[QZSS][1]=uiSBASOBAD->radioButtonIcorrOBADUserDefinedQZSS;
    RadioButtonGNSSOBAD[QZSS][2]=uiSBASOBAD->radioButtonCcorrOBADReadMT37QZSS;
    RadioButtonGNSSOBAD[QZSS][3]=uiSBASOBAD->radioButtonCcorrOBADUserDefinedQZSS;
    RadioButtonGNSSOBAD[QZSS][4]=uiSBASOBAD->radioButtonRcorrOBADReadMT37QZSS;
    RadioButtonGNSSOBAD[QZSS][5]=uiSBASOBAD->radioButtonRcorrOBADUserDefinedQZSS;
    LineEditGNSSOBAD[QZSS][0]=uiSBASOBAD->lineEditIcorrOBADQZSS;
    LineEditGNSSOBAD[QZSS][1]=uiSBASOBAD->lineEditCcorrOBADQZSS;
    LineEditGNSSOBAD[QZSS][2]=uiSBASOBAD->lineEditRcorrOBADQZSS;
    //IRNSS
    RadioButtonGNSSOBAD[IRNSS][0]=uiSBASOBAD->radioButtonIcorrOBADReadMT37IRNSS;
    RadioButtonGNSSOBAD[IRNSS][1]=uiSBASOBAD->radioButtonIcorrOBADUserDefinedIRNSS;
    RadioButtonGNSSOBAD[IRNSS][2]=uiSBASOBAD->radioButtonCcorrOBADReadMT37IRNSS;
    RadioButtonGNSSOBAD[IRNSS][3]=uiSBASOBAD->radioButtonCcorrOBADUserDefinedIRNSS;
    RadioButtonGNSSOBAD[IRNSS][4]=uiSBASOBAD->radioButtonRcorrOBADReadMT37IRNSS;
    RadioButtonGNSSOBAD[IRNSS][5]=uiSBASOBAD->radioButtonRcorrOBADUserDefinedIRNSS;
    LineEditGNSSOBAD[IRNSS][0]=uiSBASOBAD->lineEditIcorrOBADIRNSS;
    LineEditGNSSOBAD[IRNSS][1]=uiSBASOBAD->lineEditCcorrOBADIRNSS;
    LineEditGNSSOBAD[IRNSS][2]=uiSBASOBAD->lineEditRcorrOBADIRNSS;

    uiSBASOBAD->pushButtonSBASOBADAdvancedOk->setFocus();
}

void GNSS_SBAS_OBAD_Set::setOBADDefaults() {
    for(int i=0;i<MAX_GNSS;i++) {
        for(int j=0;j<5;j+=2) {
            RadioButtonGNSSOBAD[i][j]->click();
        }
        for(int j=0;j<3;j++) {
          LineEditGNSSOBAD[i][j]->setText("");
        }
    }
}

void GNSS_SBAS_OBAD_Set::setCurrentOBADPageDefaults() {
    int currentPage=uiSBASOBAD->stackedWidgetOBADParameter->currentIndex();
    for(int i=0;i<MAX_GNSS;i++) {
        RadioButtonGNSSOBAD[i][currentPage*2]->click();
        LineEditGNSSOBAD[i][currentPage]->setText("");
    }
}

//GPS
//Function to configure Icorr by reading MT 37 for GPS
void GNSS_SBAS_OBAD_Set::on_radioButtonIcorrOBADReadMT37GPS_clicked(){
    uiSBASOBAD->radioButtonIcorrOBADReadMT37GPS->setChecked(true);
    uiSBASOBAD->radioButtonIcorrOBADUserDefinedGPS->setChecked(false);
    uiSBASOBAD->frameIcorrOBADUserDefinedGPS->setEnabled(false);
}
//Function to configure Icorr by user defined for GPS
void GNSS_SBAS_OBAD_Set::on_radioButtonIcorrOBADUserDefinedGPS_clicked(){
    uiSBASOBAD->radioButtonIcorrOBADUserDefinedGPS->setChecked(true);
    uiSBASOBAD->radioButtonIcorrOBADReadMT37GPS->setChecked(false);
    uiSBASOBAD->frameIcorrOBADUserDefinedGPS->setEnabled(true);
}
//Function to configure Ccorr by reading MT 37 for GPS
void GNSS_SBAS_OBAD_Set::on_radioButtonCcorrOBADReadMT37GPS_clicked(){
    uiSBASOBAD->radioButtonCcorrOBADReadMT37GPS->setChecked(true);
    uiSBASOBAD->radioButtonCcorrOBADUserDefinedGPS->setChecked(false);
    uiSBASOBAD->frameCcorrOBADUserDefinedGPS->setEnabled(false);
}
//Function to configure Ccorr by user defined for GPS
void GNSS_SBAS_OBAD_Set::on_radioButtonCcorrOBADUserDefinedGPS_clicked(){
    uiSBASOBAD->radioButtonCcorrOBADUserDefinedGPS->setChecked(true);
    uiSBASOBAD->radioButtonCcorrOBADReadMT37GPS->setChecked(false);
    uiSBASOBAD->frameCcorrOBADUserDefinedGPS->setEnabled(true);
}
//Function to configure Rcorr by reading MT 37 for GPS
void GNSS_SBAS_OBAD_Set::on_radioButtonRcorrOBADReadMT37GPS_clicked(){
    uiSBASOBAD->radioButtonRcorrOBADReadMT37GPS->setChecked(true);
    uiSBASOBAD->radioButtonRcorrOBADUserDefinedGPS->setChecked(false);
    uiSBASOBAD->frameRcorrOBADUserDefinedGPS->setEnabled(false);
}
//Function to configure Rcorr by user defined for GPS
void GNSS_SBAS_OBAD_Set::on_radioButtonRcorrOBADUserDefinedGPS_clicked(){
    uiSBASOBAD->radioButtonRcorrOBADUserDefinedGPS->setChecked(true);
    uiSBASOBAD->radioButtonRcorrOBADReadMT37GPS->setChecked(false);
    uiSBASOBAD->frameRcorrOBADUserDefinedGPS->setEnabled(true);
}
//Galileo
//Function to configure Icorr by reading MT 37 for Galileo
void GNSS_SBAS_OBAD_Set::on_radioButtonIcorrOBADReadMT37Galileo_clicked(){
    uiSBASOBAD->radioButtonIcorrOBADReadMT37Galileo->setChecked(true);
    uiSBASOBAD->radioButtonIcorrOBADUserDefinedGalileo->setChecked(false);
    uiSBASOBAD->frameIcorrOBADUserDefinedGalileo->setEnabled(false);
}
//Function to configure Icorr by user defined for Galileo
void GNSS_SBAS_OBAD_Set::on_radioButtonIcorrOBADUserDefinedGalileo_clicked(){
    uiSBASOBAD->radioButtonIcorrOBADUserDefinedGalileo->setChecked(true);
    uiSBASOBAD->radioButtonIcorrOBADReadMT37Galileo->setChecked(false);
    uiSBASOBAD->frameIcorrOBADUserDefinedGalileo->setEnabled(true);
}
//Function to configure Ccorr by reading MT 37 for Galileo
void GNSS_SBAS_OBAD_Set::on_radioButtonCcorrOBADReadMT37Galileo_clicked(){
    uiSBASOBAD->radioButtonCcorrOBADReadMT37Galileo->setChecked(true);
    uiSBASOBAD->radioButtonCcorrOBADUserDefinedGalileo->setChecked(false);
    uiSBASOBAD->frameCcorrOBADUserDefinedGalileo->setEnabled(false);
}
//Function to configure Ccorr by user defined for Galileo
void GNSS_SBAS_OBAD_Set::on_radioButtonCcorrOBADUserDefinedGalileo_clicked(){
    uiSBASOBAD->radioButtonCcorrOBADUserDefinedGalileo->setChecked(true);
    uiSBASOBAD->radioButtonCcorrOBADReadMT37Galileo->setChecked(false);
    uiSBASOBAD->frameCcorrOBADUserDefinedGalileo->setEnabled(true);
}
//Function to configure Rcorr by reading MT 37 for Galileo
void GNSS_SBAS_OBAD_Set::on_radioButtonRcorrOBADReadMT37Galileo_clicked(){
    uiSBASOBAD->radioButtonRcorrOBADReadMT37Galileo->setChecked(true);
    uiSBASOBAD->radioButtonRcorrOBADUserDefinedGalileo->setChecked(false);
    uiSBASOBAD->frameRcorrOBADUserDefinedGalileo->setEnabled(false);
}
//Function to configure Rcorr by user defined for Galileo
void GNSS_SBAS_OBAD_Set::on_radioButtonRcorrOBADUserDefinedGalileo_clicked(){
    uiSBASOBAD->radioButtonRcorrOBADUserDefinedGalileo->setChecked(true);
    uiSBASOBAD->radioButtonRcorrOBADReadMT37Galileo->setChecked(false);
    uiSBASOBAD->frameRcorrOBADUserDefinedGalileo->setEnabled(true);
}
//GLONASS
//Function to configure Icorr by reading MT 37 for GLONASS
void GNSS_SBAS_OBAD_Set::on_radioButtonIcorrOBADReadMT37GLONASS_clicked(){
    uiSBASOBAD->radioButtonIcorrOBADReadMT37GLONASS->setChecked(true);
    uiSBASOBAD->radioButtonIcorrOBADUserDefinedGLONASS->setChecked(false);
    uiSBASOBAD->frameIcorrOBADUserDefinedGLONASS->setEnabled(false);
}
//Function to configure Icorr by user defined for GLONASS
void GNSS_SBAS_OBAD_Set::on_radioButtonIcorrOBADUserDefinedGLONASS_clicked(){
    uiSBASOBAD->radioButtonIcorrOBADUserDefinedGLONASS->setChecked(true);
    uiSBASOBAD->radioButtonIcorrOBADReadMT37GLONASS->setChecked(false);
    uiSBASOBAD->frameIcorrOBADUserDefinedGLONASS->setEnabled(true);
}
//Function to configure Ccorr by reading MT 37 for GLONASS
void GNSS_SBAS_OBAD_Set::on_radioButtonCcorrOBADReadMT37GLONASS_clicked(){
    uiSBASOBAD->radioButtonCcorrOBADReadMT37GLONASS->setChecked(true);
    uiSBASOBAD->radioButtonCcorrOBADUserDefinedGLONASS->setChecked(false);
    uiSBASOBAD->frameCcorrOBADUserDefinedGLONASS->setEnabled(false);
}
//Function to configure Ccorr by user defined for GLONASS
void GNSS_SBAS_OBAD_Set::on_radioButtonCcorrOBADUserDefinedGLONASS_clicked(){
    uiSBASOBAD->radioButtonCcorrOBADUserDefinedGLONASS->setChecked(true);
    uiSBASOBAD->radioButtonCcorrOBADReadMT37GLONASS->setChecked(false);
    uiSBASOBAD->frameCcorrOBADUserDefinedGLONASS->setEnabled(true);
}
//Function to configure Rcorr by reading MT 37 for GLONASS
void GNSS_SBAS_OBAD_Set::on_radioButtonRcorrOBADReadMT37GLONASS_clicked(){
    uiSBASOBAD->radioButtonRcorrOBADReadMT37GLONASS->setChecked(true);
    uiSBASOBAD->radioButtonRcorrOBADUserDefinedGLONASS->setChecked(false);
    uiSBASOBAD->frameRcorrOBADUserDefinedGLONASS->setEnabled(false);
}
//Function to configure Rcorr by user defined for GLONASS
void GNSS_SBAS_OBAD_Set::on_radioButtonRcorrOBADUserDefinedGLONASS_clicked(){
    uiSBASOBAD->radioButtonRcorrOBADUserDefinedGLONASS->setChecked(true);
    uiSBASOBAD->radioButtonRcorrOBADReadMT37GLONASS->setChecked(false);
    uiSBASOBAD->frameRcorrOBADUserDefinedGLONASS->setEnabled(true);
}
//GEO
//Function to configure Icorr by reading MT 37 for GEO
void GNSS_SBAS_OBAD_Set::on_radioButtonIcorrOBADReadMT37GEO_clicked(){
    uiSBASOBAD->radioButtonIcorrOBADReadMT37GEO->setChecked(true);
    uiSBASOBAD->radioButtonIcorrOBADUserDefinedGEO->setChecked(false);
    uiSBASOBAD->frameIcorrOBADUserDefinedGEO->setEnabled(false);
}
//Function to configure Icorr by user defined for GEO
void GNSS_SBAS_OBAD_Set::on_radioButtonIcorrOBADUserDefinedGEO_clicked(){
    uiSBASOBAD->radioButtonIcorrOBADUserDefinedGEO->setChecked(true);
    uiSBASOBAD->radioButtonIcorrOBADReadMT37GEO->setChecked(false);
    uiSBASOBAD->frameIcorrOBADUserDefinedGEO->setEnabled(true);
}
//Function to configure Ccorr by reading MT 37 for GEO
void GNSS_SBAS_OBAD_Set::on_radioButtonCcorrOBADReadMT37GEO_clicked(){
    uiSBASOBAD->radioButtonCcorrOBADReadMT37GEO->setChecked(true);
    uiSBASOBAD->radioButtonCcorrOBADUserDefinedGEO->setChecked(false);
    uiSBASOBAD->frameCcorrOBADUserDefinedGEO->setEnabled(false);
}
//Function to configure Ccorr by user defined for GEO
void GNSS_SBAS_OBAD_Set::on_radioButtonCcorrOBADUserDefinedGEO_clicked(){
    uiSBASOBAD->radioButtonCcorrOBADUserDefinedGEO->setChecked(true);
    uiSBASOBAD->radioButtonCcorrOBADReadMT37GEO->setChecked(false);
    uiSBASOBAD->frameCcorrOBADUserDefinedGEO->setEnabled(true);
}
//Function to configure Rcorr by reading MT 37 for GEO
void GNSS_SBAS_OBAD_Set::on_radioButtonRcorrOBADReadMT37GEO_clicked(){
    uiSBASOBAD->radioButtonRcorrOBADReadMT37GEO->setChecked(true);
    uiSBASOBAD->radioButtonRcorrOBADUserDefinedGEO->setChecked(false);
    uiSBASOBAD->frameRcorrOBADUserDefinedGEO->setEnabled(false);
}
//Function to configure Rcorr by user defined for GEO
void GNSS_SBAS_OBAD_Set::on_radioButtonRcorrOBADUserDefinedGEO_clicked(){
    uiSBASOBAD->radioButtonRcorrOBADUserDefinedGEO->setChecked(true);
    uiSBASOBAD->radioButtonRcorrOBADReadMT37GEO->setChecked(false);
    uiSBASOBAD->frameRcorrOBADUserDefinedGEO->setEnabled(true);
}
//BDS
//Function to configure Icorr by reading MT 37 for BDS
void GNSS_SBAS_OBAD_Set::on_radioButtonIcorrOBADReadMT37BDS_clicked(){
    uiSBASOBAD->radioButtonIcorrOBADReadMT37BDS->setChecked(true);
    uiSBASOBAD->radioButtonIcorrOBADUserDefinedBDS->setChecked(false);
    uiSBASOBAD->frameIcorrOBADUserDefinedBDS->setEnabled(false);
}
//Function to configure Icorr by user defined for BDS
void GNSS_SBAS_OBAD_Set::on_radioButtonIcorrOBADUserDefinedBDS_clicked(){
    uiSBASOBAD->radioButtonIcorrOBADUserDefinedBDS->setChecked(true);
    uiSBASOBAD->radioButtonIcorrOBADReadMT37BDS->setChecked(false);
    uiSBASOBAD->frameIcorrOBADUserDefinedBDS->setEnabled(true);
}
//Function to configure Ccorr by reading MT 37 for BDS
void GNSS_SBAS_OBAD_Set::on_radioButtonCcorrOBADReadMT37BDS_clicked(){
    uiSBASOBAD->radioButtonCcorrOBADReadMT37BDS->setChecked(true);
    uiSBASOBAD->radioButtonCcorrOBADUserDefinedBDS->setChecked(false);
    uiSBASOBAD->frameCcorrOBADUserDefinedBDS->setEnabled(false);
}
//Function to configure Ccorr by user defined for BDS
void GNSS_SBAS_OBAD_Set::on_radioButtonCcorrOBADUserDefinedBDS_clicked(){
    uiSBASOBAD->radioButtonCcorrOBADUserDefinedBDS->setChecked(true);
    uiSBASOBAD->radioButtonCcorrOBADReadMT37BDS->setChecked(false);
    uiSBASOBAD->frameCcorrOBADUserDefinedBDS->setEnabled(true);
}
//Function to configure Rcorr by reading MT 37 for BDS
void GNSS_SBAS_OBAD_Set::on_radioButtonRcorrOBADReadMT37BDS_clicked(){
    uiSBASOBAD->radioButtonRcorrOBADReadMT37BDS->setChecked(true);
    uiSBASOBAD->radioButtonRcorrOBADUserDefinedBDS->setChecked(false);
    uiSBASOBAD->frameRcorrOBADUserDefinedBDS->setEnabled(false);
}
//Function to configure Rcorr by user defined for BDS
void GNSS_SBAS_OBAD_Set::on_radioButtonRcorrOBADUserDefinedBDS_clicked(){
    uiSBASOBAD->radioButtonRcorrOBADUserDefinedBDS->setChecked(true);
    uiSBASOBAD->radioButtonRcorrOBADReadMT37BDS->setChecked(false);
    uiSBASOBAD->frameRcorrOBADUserDefinedBDS->setEnabled(true);
}
//QZSS
//Function to configure Icorr by reading MT 37 for QZSS
void GNSS_SBAS_OBAD_Set::on_radioButtonIcorrOBADReadMT37QZSS_clicked(){
    uiSBASOBAD->radioButtonIcorrOBADReadMT37QZSS->setChecked(true);
    uiSBASOBAD->radioButtonIcorrOBADUserDefinedQZSS->setChecked(false);
    uiSBASOBAD->frameIcorrOBADUserDefinedQZSS->setEnabled(false);
}
//Function to configure Icorr by user defined for QZSS
void GNSS_SBAS_OBAD_Set::on_radioButtonIcorrOBADUserDefinedQZSS_clicked(){
    uiSBASOBAD->radioButtonIcorrOBADUserDefinedQZSS->setChecked(true);
    uiSBASOBAD->radioButtonIcorrOBADReadMT37QZSS->setChecked(false);
    uiSBASOBAD->frameIcorrOBADUserDefinedQZSS->setEnabled(true);
}
//Function to configure Ccorr by reading MT 37 for QZSS
void GNSS_SBAS_OBAD_Set::on_radioButtonCcorrOBADReadMT37QZSS_clicked(){
    uiSBASOBAD->radioButtonCcorrOBADReadMT37QZSS->setChecked(true);
    uiSBASOBAD->radioButtonCcorrOBADUserDefinedQZSS->setChecked(false);
    uiSBASOBAD->frameCcorrOBADUserDefinedQZSS->setEnabled(false);
}
//Function to configure Ccorr by user defined for QZSS
void GNSS_SBAS_OBAD_Set::on_radioButtonCcorrOBADUserDefinedQZSS_clicked(){
    uiSBASOBAD->radioButtonCcorrOBADUserDefinedQZSS->setChecked(true);
    uiSBASOBAD->radioButtonCcorrOBADReadMT37QZSS->setChecked(false);
    uiSBASOBAD->frameCcorrOBADUserDefinedQZSS->setEnabled(true);
}
//Function to configure Rcorr by reading MT 37 for QZSS
void GNSS_SBAS_OBAD_Set::on_radioButtonRcorrOBADReadMT37QZSS_clicked(){
    uiSBASOBAD->radioButtonRcorrOBADReadMT37QZSS->setChecked(true);
    uiSBASOBAD->radioButtonRcorrOBADUserDefinedQZSS->setChecked(false);
    uiSBASOBAD->frameRcorrOBADUserDefinedQZSS->setEnabled(false);
}
//Function to configure Rcorr by user defined for QZSS
void GNSS_SBAS_OBAD_Set::on_radioButtonRcorrOBADUserDefinedQZSS_clicked(){
    uiSBASOBAD->radioButtonRcorrOBADUserDefinedQZSS->setChecked(true);
    uiSBASOBAD->radioButtonRcorrOBADReadMT37QZSS->setChecked(false);
    uiSBASOBAD->frameRcorrOBADUserDefinedQZSS->setEnabled(true);
}
//IRNSS
//Function to configure Icorr by reading MT 37 for IRNSS
void GNSS_SBAS_OBAD_Set::on_radioButtonIcorrOBADReadMT37IRNSS_clicked(){
    uiSBASOBAD->radioButtonIcorrOBADReadMT37IRNSS->setChecked(true);
    uiSBASOBAD->radioButtonIcorrOBADUserDefinedIRNSS->setChecked(false);
    uiSBASOBAD->frameIcorrOBADUserDefinedIRNSS->setEnabled(false);
}
//Function to configure Icorr by user defined for IRNSS
void GNSS_SBAS_OBAD_Set::on_radioButtonIcorrOBADUserDefinedIRNSS_clicked(){
    uiSBASOBAD->radioButtonIcorrOBADUserDefinedIRNSS->setChecked(true);
    uiSBASOBAD->radioButtonIcorrOBADReadMT37IRNSS->setChecked(false);
    uiSBASOBAD->frameIcorrOBADUserDefinedIRNSS->setEnabled(true);
}
//Function to configure Ccorr by reading MT 37 for IRNSS
void GNSS_SBAS_OBAD_Set::on_radioButtonCcorrOBADReadMT37IRNSS_clicked(){
    uiSBASOBAD->radioButtonCcorrOBADReadMT37IRNSS->setChecked(true);
    uiSBASOBAD->radioButtonCcorrOBADUserDefinedIRNSS->setChecked(false);
    uiSBASOBAD->frameCcorrOBADUserDefinedIRNSS->setEnabled(false);
}
//Function to configure Ccorr by user defined for IRNSS
void GNSS_SBAS_OBAD_Set::on_radioButtonCcorrOBADUserDefinedIRNSS_clicked(){
    uiSBASOBAD->radioButtonCcorrOBADUserDefinedIRNSS->setChecked(true);
    uiSBASOBAD->radioButtonCcorrOBADReadMT37IRNSS->setChecked(false);
    uiSBASOBAD->frameCcorrOBADUserDefinedIRNSS->setEnabled(true);
}
//Function to configure Rcorr by reading MT 37 for IRNSS
void GNSS_SBAS_OBAD_Set::on_radioButtonRcorrOBADReadMT37IRNSS_clicked(){
    uiSBASOBAD->radioButtonRcorrOBADReadMT37IRNSS->setChecked(true);
    uiSBASOBAD->radioButtonRcorrOBADUserDefinedIRNSS->setChecked(false);
    uiSBASOBAD->frameRcorrOBADUserDefinedIRNSS->setEnabled(false);
}
//Function to configure Rcorr by user defined for IRNSS
void GNSS_SBAS_OBAD_Set::on_radioButtonRcorrOBADUserDefinedIRNSS_clicked(){
    uiSBASOBAD->radioButtonRcorrOBADUserDefinedIRNSS->setChecked(true);
    uiSBASOBAD->radioButtonRcorrOBADReadMT37IRNSS->setChecked(false);
    uiSBASOBAD->frameRcorrOBADUserDefinedIRNSS->setEnabled(true);
}

//Function to make options enabled for GPS
void GNSS_SBAS_OBAD_Set::setGPS(bool checked){
    uiSBASOBAD->frameIcorrOBADGPS->setEnabled(checked);
    uiSBASOBAD->frameCcorrOBADGPS->setEnabled(checked);
    uiSBASOBAD->frameRcorrOBADGPS->setEnabled(checked);

    this->on_radioButtonIcorrOBADReadMT37GPS_clicked();
    this->on_radioButtonCcorrOBADReadMT37GPS_clicked();
    this->on_radioButtonRcorrOBADReadMT37GPS_clicked();
}
//Function to make options enabled for Galileo
void GNSS_SBAS_OBAD_Set::setGalileo(bool checked){
    uiSBASOBAD->frameIcorrOBADGalileo->setEnabled(checked);
    uiSBASOBAD->frameCcorrOBADGalileo->setEnabled(checked);
    uiSBASOBAD->frameRcorrOBADGalileo->setEnabled(checked);

    this->on_radioButtonIcorrOBADReadMT37Galileo_clicked();
    this->on_radioButtonCcorrOBADReadMT37Galileo_clicked();
    this->on_radioButtonRcorrOBADReadMT37Galileo_clicked();
}
//Function to make options enabled for GLONASS
void GNSS_SBAS_OBAD_Set::setGLONASS(bool checked){
    uiSBASOBAD->frameIcorrOBADGLONASS->setEnabled(checked);
    uiSBASOBAD->frameCcorrOBADGLONASS->setEnabled(checked);
    uiSBASOBAD->frameRcorrOBADGLONASS->setEnabled(checked);

    this->on_radioButtonIcorrOBADReadMT37GLONASS_clicked();
    this->on_radioButtonCcorrOBADReadMT37GLONASS_clicked();
    this->on_radioButtonRcorrOBADReadMT37GLONASS_clicked();
}
//Function to make options enabled for GEO
void GNSS_SBAS_OBAD_Set::setGEO(bool checked){
    uiSBASOBAD->frameIcorrOBADGEO->setEnabled(checked);
    uiSBASOBAD->frameCcorrOBADGEO->setEnabled(checked);
    uiSBASOBAD->frameRcorrOBADGEO->setEnabled(checked);

    this->on_radioButtonIcorrOBADReadMT37GEO_clicked();
    this->on_radioButtonCcorrOBADReadMT37GEO_clicked();
    this->on_radioButtonRcorrOBADReadMT37GEO_clicked();
}
//Function to make options enabled for BDS
void GNSS_SBAS_OBAD_Set::setBDS(bool checked){
    uiSBASOBAD->frameIcorrOBADBDS->setEnabled(checked);
    uiSBASOBAD->frameCcorrOBADBDS->setEnabled(checked);
    uiSBASOBAD->frameRcorrOBADBDS->setEnabled(checked);

    this->on_radioButtonIcorrOBADReadMT37BDS_clicked();
    this->on_radioButtonCcorrOBADReadMT37BDS_clicked();
    this->on_radioButtonRcorrOBADReadMT37BDS_clicked();
}
//Function to make options enabled for QZSS
void GNSS_SBAS_OBAD_Set::setQZSS(bool checked){
    uiSBASOBAD->frameIcorrOBADQZSS->setEnabled(checked);
    uiSBASOBAD->frameCcorrOBADQZSS->setEnabled(checked);
    uiSBASOBAD->frameRcorrOBADQZSS->setEnabled(checked);

    this->on_radioButtonIcorrOBADReadMT37QZSS_clicked();
    this->on_radioButtonCcorrOBADReadMT37QZSS_clicked();
    this->on_radioButtonRcorrOBADReadMT37QZSS_clicked();
}
//Function to make options enabled for IRNSS
void GNSS_SBAS_OBAD_Set::setIRNSS(bool checked){
    uiSBASOBAD->frameIcorrOBADIRNSS->setEnabled(checked);
    uiSBASOBAD->frameCcorrOBADIRNSS->setEnabled(checked);
    uiSBASOBAD->frameRcorrOBADIRNSS->setEnabled(checked);

    this->on_radioButtonIcorrOBADReadMT37IRNSS_clicked();
    this->on_radioButtonCcorrOBADReadMT37IRNSS_clicked();
    this->on_radioButtonRcorrOBADReadMT37IRNSS_clicked();
}
//Function to change current page to Icorr/Ccorr/Rcorr
void GNSS_SBAS_OBAD_Set::changePage(int iPage){
    if      (iPage==0) this->setWindowTitle("Set Icorr OBAD Parameter from MT 37");
    else if (iPage==1) this->setWindowTitle("Set Ccorr OBAD Parameter from MT 37");
    else if (iPage==2) this->setWindowTitle("Set Rcorr OBAD Parameter from MT 37");
    uiSBASOBAD->stackedWidgetOBADParameter->setCurrentIndex(iPage);
}

//Function to get the SBAS OBAD options and errors
void GNSS_SBAS_OBAD_Set::getgLABOptions(const int optionType, QString *errorString, QString *warningString, QString *saveString, QStringList *runString) {
    //Icorr options
    if (optionType==1){
        OBADOK[0]=0;
        for (int i=0; i<MAX_GNSS; i++) OBADOptions[0][i]="";
        //GPS
        if ( uiSBASOBAD->radioButtonIcorrOBADUserDefinedGPS->isChecked()==true ){
            if ( uiSBASOBAD->lineEditIcorrOBADGPS->text()=="" ){
                *errorString += "MODEL: Icorr of GPS in the Dialog of 'Set Icorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[0]++;
                OBADOptions[0][GPS] += "G-" + uiSBASOBAD->lineEditIcorrOBADGPS->text();
            }
        }
        //Galileo
        if ( uiSBASOBAD->radioButtonIcorrOBADUserDefinedGalileo->isChecked()==true ){
            if ( uiSBASOBAD->lineEditIcorrOBADGalileo->text()=="" ){
                *errorString += "MODEL: Icorr of Galileo in the Dialog of 'Set Icorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[0]++;
                OBADOptions[0][Galileo] += "E-" + uiSBASOBAD->lineEditIcorrOBADGalileo->text();
            }
        }
        //GLONASS
        if ( uiSBASOBAD->radioButtonIcorrOBADUserDefinedGLONASS->isChecked()==true ){
            if ( uiSBASOBAD->lineEditIcorrOBADGLONASS->text()=="" ){
                *errorString += "MODEL: Icorr of GLONASS in the Dialog of 'Set Icorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[0]++;
                OBADOptions[0][GLONASS] += "R-" + uiSBASOBAD->lineEditIcorrOBADGLONASS->text();
            }
        }
        //GEO
        if ( uiSBASOBAD->radioButtonIcorrOBADUserDefinedGEO->isChecked()==true ){
            if ( uiSBASOBAD->lineEditIcorrOBADGEO->text()=="" ){
                *errorString += "MODEL: Icorr of GEO in the Dialog of 'Set Icorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[0]++;
                OBADOptions[0][GEO] += "S-" + uiSBASOBAD->lineEditIcorrOBADGEO->text();
            }
        }
        //BDS
        if ( uiSBASOBAD->radioButtonIcorrOBADUserDefinedBDS->isChecked()==true ){
            if ( uiSBASOBAD->lineEditIcorrOBADBDS->text()=="" ){
                *errorString += "MODEL: Icorr of BDS in the Dialog of 'Set Icorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[0]++;
                OBADOptions[0][BDS] += "C-" + uiSBASOBAD->lineEditIcorrOBADBDS->text();
            }
        }
        //QZSS
        if ( uiSBASOBAD->radioButtonIcorrOBADUserDefinedQZSS->isChecked()==true ){
            if ( uiSBASOBAD->lineEditIcorrOBADQZSS->text()=="" ){
                *errorString += "MODEL: Icorr of QZSS in the Dialog of 'Set Icorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[0]++;
                OBADOptions[0][QZSS] += "J-" + uiSBASOBAD->lineEditIcorrOBADQZSS->text();
            }
        }
        //IRNSS
        if ( uiSBASOBAD->radioButtonIcorrOBADUserDefinedIRNSS->isChecked()==true ){
            if ( uiSBASOBAD->lineEditIcorrOBADIRNSS->text()=="" ){
                *errorString += "MODEL: Icorr of IRNSS in the Dialog of 'Set Icorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[0]++;
                OBADOptions[0][IRNSS] += "I-" + uiSBASOBAD->lineEditIcorrOBADIRNSS->text();
            }
        }
        if ( OBADOK[0]==0 ){
            *warningString += "MODEL: NONE of Icorr parameter in the Dialog of 'Set Icorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] is defined.\n";
        } else {
            *saveString += "-model:sbasdfmc:icorr";
            *runString << "-model:sbasdfmc:icorr";
            for (int i=0;i<MAX_GNSS;i++){ //-model:sbasdfmc:icorr
                if (OBADOptions[0][i]!=""){
                    *saveString += " "+OBADOptions[0][i];
                    *runString << OBADOptions[0][i];
                }
            }
            *saveString += "\n";
        }
    }
    //Ccorr options
    else if (optionType==2){
        OBADOK[1]=0;
        for (int i=0; i<MAX_GNSS; i++) OBADOptions[1][i]="";
        //GPS
        if ( uiSBASOBAD->radioButtonCcorrOBADUserDefinedGPS->isChecked()==true ){
            if ( uiSBASOBAD->lineEditCcorrOBADGPS->text()=="" ){
                *errorString += "MODEL: Ccorr of GPS in the Dialog of 'Set Ccorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[1]++;
                OBADOptions[1][GPS] += "G-" + uiSBASOBAD->lineEditCcorrOBADGPS->text();
            }
        }
        //Galileo
        if ( uiSBASOBAD->radioButtonCcorrOBADUserDefinedGalileo->isChecked()==true ){
            if ( uiSBASOBAD->lineEditCcorrOBADGalileo->text()=="" ){
                *errorString += "MODEL: Ccorr of Galileo in the Dialog of 'Set Ccorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[1]++;
                OBADOptions[1][Galileo] += "E-" + uiSBASOBAD->lineEditCcorrOBADGalileo->text();
            }
        }
        //GLONASS
        if ( uiSBASOBAD->radioButtonCcorrOBADUserDefinedGLONASS->isChecked()==true ){
            if ( uiSBASOBAD->lineEditCcorrOBADGLONASS->text()=="" ){
                *errorString += "MODEL: Ccorr of GLONASS in the Dialog of 'Set Ccorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[1]++;
                OBADOptions[1][GLONASS] += "R-" + uiSBASOBAD->lineEditCcorrOBADGLONASS->text();
            }
        }
        //GEO
        if ( uiSBASOBAD->radioButtonCcorrOBADUserDefinedGEO->isChecked()==true ){
            if ( uiSBASOBAD->lineEditCcorrOBADGEO->text()=="" ){
                *errorString += "MODEL: Ccorr of GEO in the Dialog of 'Set Ccorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[1]++;
                OBADOptions[1][GEO] += "S-" + uiSBASOBAD->lineEditCcorrOBADGEO->text();
            }
        }
        //BDS
        if ( uiSBASOBAD->radioButtonCcorrOBADUserDefinedBDS->isChecked()==true ){
            if ( uiSBASOBAD->lineEditCcorrOBADBDS->text()=="" ){
                *errorString += "MODEL: Ccorr of BDS in the Dialog of 'Set Ccorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[1]++;
                OBADOptions[1][BDS] += "C-" + uiSBASOBAD->lineEditCcorrOBADBDS->text();
            }
        }
        //QZSS
        if ( uiSBASOBAD->radioButtonCcorrOBADUserDefinedQZSS->isChecked()==true ){
            if ( uiSBASOBAD->lineEditCcorrOBADQZSS->text()=="" ){
                *errorString += "MODEL: Ccorr of QZSS in the Dialog of 'Set Ccorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[1]++;
                OBADOptions[1][QZSS] += "J-" + uiSBASOBAD->lineEditCcorrOBADQZSS->text();
            }
        }
        //IRNSS
        if ( uiSBASOBAD->radioButtonCcorrOBADUserDefinedIRNSS->isChecked()==true ){
            if ( uiSBASOBAD->lineEditCcorrOBADIRNSS->text()=="" ){
                *errorString += "MODEL: Ccorr of IRNSS in the Dialog of 'Set Ccorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[1]++;
                OBADOptions[1][IRNSS] += "I-" + uiSBASOBAD->lineEditCcorrOBADIRNSS->text();
            }
        }
        if ( OBADOK[1]==0 ){
            *warningString += "MODEL: NONE of Ccorr parameter in the Dialog of 'Set Ccorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] is defined.\n";
        } else {
            *saveString += "-model:sbasdfmc:ccorr";
            *runString << "-model:sbasdfmc:ccorr";
            for (int i=0;i<MAX_GNSS;i++){ //-model:sbasdfmc:ccorr
                if (OBADOptions[1][i]!=""){
                    *saveString += " "+OBADOptions[1][i];
                    *runString << OBADOptions[1][i];
                }
            }
            *saveString += "\n";
        }
    }
    //Rcorr options
    else if (optionType==3){
        OBADOK[2]=0;
        for (int i=0; i<MAX_GNSS; i++) OBADOptions[2][i]="";
        //GPS
        if ( uiSBASOBAD->radioButtonRcorrOBADUserDefinedGPS->isChecked()==true ){
            if ( uiSBASOBAD->lineEditRcorrOBADGPS->text()=="" ){
                *errorString += "MODEL: Rcorr of GPS in the Dialog of 'Set Rcorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[2]++;
                OBADOptions[2][GPS] += "G-" + uiSBASOBAD->lineEditRcorrOBADGPS->text();
            }
        }
        //Galileo
        if ( uiSBASOBAD->radioButtonRcorrOBADUserDefinedGalileo->isChecked()==true ){
            if ( uiSBASOBAD->lineEditRcorrOBADGalileo->text()=="" ){
                *errorString += "MODEL: Rcorr of Galileo in the Dialog of 'Set Rcorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[2]++;
                OBADOptions[2][Galileo] += "E-" + uiSBASOBAD->lineEditRcorrOBADGalileo->text();
            }
        }
        //GLONASS
        if ( uiSBASOBAD->radioButtonRcorrOBADUserDefinedGLONASS->isChecked()==true ){
            if ( uiSBASOBAD->lineEditRcorrOBADGLONASS->text()=="" ){
                *errorString += "MODEL: Rcorr of GLONASS in the Dialog of 'Set Rcorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[2]++;
                OBADOptions[2][GLONASS] += "R-" + uiSBASOBAD->lineEditRcorrOBADGLONASS->text();
            }
        }
        //GEO
        if ( uiSBASOBAD->radioButtonRcorrOBADUserDefinedGEO->isChecked()==true ){
            if ( uiSBASOBAD->lineEditRcorrOBADGEO->text()=="" ){
                *errorString += "MODEL: Rcorr of GEO in the Dialog of 'Set Rcorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[2]++;
                OBADOptions[2][GEO] += "S-" + uiSBASOBAD->lineEditRcorrOBADGEO->text();
            }
        }
        //BDS
        if ( uiSBASOBAD->radioButtonRcorrOBADUserDefinedBDS->isChecked()==true ){
            if ( uiSBASOBAD->lineEditRcorrOBADBDS->text()=="" ){
                *errorString += "MODEL: Rcorr of BDS in the Dialog of 'Set Rcorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[2]++;
                OBADOptions[2][BDS] += "C-" + uiSBASOBAD->lineEditRcorrOBADBDS->text();
            }
        }
        //QZSS
        if ( uiSBASOBAD->radioButtonRcorrOBADUserDefinedQZSS->isChecked()==true ){
            if ( uiSBASOBAD->lineEditRcorrOBADQZSS->text()=="" ){
                *errorString += "MODEL: Rcorr of QZSS in the Dialog of 'Set Rcorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[2]++;
                OBADOptions[2][QZSS] += "J-" + uiSBASOBAD->lineEditRcorrOBADQZSS->text();
            }
        }
        //IRNSS
        if ( uiSBASOBAD->radioButtonRcorrOBADUserDefinedIRNSS->isChecked()==true ){
            if ( uiSBASOBAD->lineEditRcorrOBADIRNSS->text()=="" ){
                *errorString += "MODEL: Rcorr of IRNSS in the Dialog of 'Set Rcorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] cannot be empty if 'User Defined' is checked.\n";
            } else {
                OBADOK[2]++;
                OBADOptions[2][IRNSS] += "I-" + uiSBASOBAD->lineEditRcorrOBADIRNSS->text();
            }
        }
        if ( OBADOK[2]==0 ){
            *warningString += "MODEL: NONE of Rcorr parameter in the Dialog of 'Set Rcorr OBAD Parameter from MT 37' in 'Show Set OBAD Parameters' of [SBAS Advanced Options] is defined.\n";
        } else {
            *saveString += "-model:sbasdfmc:rcorr";
            *runString << "-model:sbasdfmc:rcorr";
            for (int i=0;i<MAX_GNSS;i++){ //-model:sbasdfmc:rcorr
                if (OBADOptions[2][i]!=""){
                    *saveString += " "+OBADOptions[2][i];
                    *runString << OBADOptions[2][i];
                }
            }
            *saveString += "\n";
        }
    }
}

//Function to load the SBAS OBAD options
void GNSS_SBAS_OBAD_Set::loadgLABOptions(const int optionType, QString *warningString, QStringList *ParametersList) {
    //optionType = 0:Icorr,1:Ccorr,2:Rcorr
    int nPar=ParametersList->count();
    if (warningString->length()<0) *warningString=""; //only to avoid the warning of unused "warningString"
    for (int iPar=0; iPar<nPar; iPar++){
        int iGNSS=-1;
        //find frequency list
        QStringList valueList = ParametersList->at(iPar).split("-", QString::SkipEmptyParts);
        if (valueList.count()!=2) continue;
        if (!(valueList[0].contains(QRegularExpression("^" + regExpConstOnly + "{1,7}$")))) {
            *warningString += "MODEL: Invalid constellations '" + valueList[0] + "' for SBAS OBAD in argument '" + ParametersList->at(iPar) + "'. It was skipped.\n";
            continue;
        }
        bool OBADOK=false;
        valueList[1].toDouble(&OBADOK);
        if (!OBADOK) {
            *warningString += "MODEL: Invalid value '" + valueList[1] + "' for SBAS OBAD in argument '" + ParametersList->at(iPar) + "'. It was skipped.\n";
            continue;
        }
        //loop constellation for frequency order
        for (iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
            if ( valueList[0].contains(indentifierGNSS[iGNSS],Qt::CaseInsensitive) ){
                RadioButtonGNSSOBAD[iGNSS][optionType*2]->click();
                LineEditGNSSOBAD[iGNSS][optionType]->setText(valueList[1]);
            }
        }
    }
}

//Function to set the defaults of current page with push button
void GNSS_SBAS_OBAD_Set::on_pushButtonSBASOBADAdvancedDefault_clicked() {
    this->setCurrentOBADPageDefaults();
}

void GNSS_SBAS_OBAD_Set::on_pushButtonSBASOBADAdvancedOk_clicked() {
    this->OkFlag=1;
    this->close();
}
