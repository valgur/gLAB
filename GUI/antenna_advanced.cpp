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
#include "antenna_advanced.h"
#include "ui_antenna_advanced.h"

const int FreqNumToIndex[MAX_GNSS][MAX_GNSS_FREQ_SLOTS]={
    //This variable transforms from the frequency number of a constellation to the index position in the APC Advanced frequency list
    //Slots set to -1 are not to be used. Value is set -1 so if it is incorrectly used, the program should crash
    //GPS
    //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    {-1, 0, 1,-1,-1, 2,-1,-1,-1,-1},
    //Galileo
    //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    {-1, 0,-1,-1,-1, 1, 2, 3, 4,-1},
    //GLONASS
    //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    {-1, 0, 1, 2, 3,-1, 4,-1,-1,-1},
    //GEO
    //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    {-1, 0,-1,-1,-1, 1,-1,-1,-1,-1},
    //BDS
    //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    {-1, 0, 1,-1,-1, 2, 3, 4, 5,-1},
    //QZSS
    //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    {-1, 0, 1,-1,-1, 2, 3,-1,-1,-1},
    //IRNSS
    //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    {-1, 0,-1,-1,-1, 1,-1,-1,-1,-1}
};

GNSS_Antenna_Advanced::GNSS_Antenna_Advanced(QWidget *parent) :
    QDialog(parent),
    UiAntenna(new Ui::GNSS_Antenna_Advanced)
{
    UiAntenna->setupUi(this);

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

    this->setWindowTitle("Specify Receiver Antenna Phase Centre Correction");

    //Init variable with pointers to PushButtons pointers
    this->InitPushButtonGNSSPointers();
    //Init variable with pointers to PushButtons function pointers
    this->InitPushButtonGNSSMinFuncPointers();
    //Init variable with pointers to RadioButton and LineEdit of Specify of GERSCJI
    this->InitAPCPointers();

    // Set the locale to avoid comma as decimator and reject the group separator
    QLocale qlocale(QLocale::C);
    qlocale.setNumberOptions(QLocale::RejectGroupSeparator);
    auto ldouble = new QDoubleValidator(-100000000, 100000000,6, this);
    ldouble->setLocale(qlocale); // lineEdit validation

    //GPS
    UiAntenna->lineEditAPCNorthF1GPS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF1GPS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF1GPS->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF2GPS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF2GPS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF2GPS->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF5GPS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF5GPS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF5GPS->setValidator(ldouble);
    //Galileo
    UiAntenna->lineEditAPCNorthF1Galileo->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF1Galileo->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF1Galileo->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF5Galileo->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF5Galileo->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF5Galileo->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF6Galileo->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF6Galileo->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF6Galileo->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF7Galileo->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF7Galileo->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF7Galileo->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF8Galileo->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF8Galileo->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF8Galileo->setValidator(ldouble);
    //GLONASS
    UiAntenna->lineEditAPCNorthF1GLONASS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF1GLONASS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF1GLONASS->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF2GLONASS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF2GLONASS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF2GLONASS->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF3GLONASS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF3GLONASS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF3GLONASS->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF4GLONASS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF4GLONASS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF4GLONASS->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF6GLONASS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF6GLONASS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF6GLONASS->setValidator(ldouble);
    //GEO
    UiAntenna->lineEditAPCNorthF1GEO->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF1GEO->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF1GEO->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF5GEO->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF5GEO->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF5GEO->setValidator(ldouble);
    //BDS
    UiAntenna->lineEditAPCNorthF1BDS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF1BDS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF1BDS->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF2BDS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF2BDS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF2BDS->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF5BDS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF5BDS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF5BDS->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF6BDS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF6BDS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF6BDS->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF7BDS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF7BDS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF7BDS->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF8BDS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF8BDS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF8BDS->setValidator(ldouble);
    //QZSS
    UiAntenna->lineEditAPCNorthF1QZSS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF1QZSS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF1QZSS->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF2QZSS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF2QZSS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF2QZSS->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF5QZSS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF5QZSS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF5QZSS->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF6QZSS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF6QZSS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF6QZSS->setValidator(ldouble);
    //IRNSS
    UiAntenna->lineEditAPCNorthF5IRNSS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF5IRNSS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF5IRNSS->setValidator(ldouble);
    UiAntenna->lineEditAPCNorthF9IRNSS->setValidator(ldouble);
    UiAntenna->lineEditAPCEastF9IRNSS->setValidator(ldouble);
    UiAntenna->lineEditAPCUpF9IRNSS->setValidator(ldouble);

    this->setAPCdefaults();

    UiAntenna->pushButtonAntAdvancedOk->setFocus();

    UiAntenna->pushButtonAntAdvancedCancel->setHidden(true); //Remove when Cancel buttons undo all changes made by the user
}

GNSS_Antenna_Advanced::~GNSS_Antenna_Advanced()
{
    delete UiAntenna;
}

//Function to initialize pointers to CheckBox widget pointers
void GNSS_Antenna_Advanced::InitPushButtonGNSSPointers(){
    PushButtonGNSS[GPS]=UiAntenna->pushButtonGPS;
    PushButtonGNSS[Galileo]=UiAntenna->pushButtonGalileo;
    PushButtonGNSS[GLONASS]=UiAntenna->pushButtonGLONASS;
    PushButtonGNSS[GEO]=UiAntenna->pushButtonGEO;
    PushButtonGNSS[BDS]=UiAntenna->pushButtonBDS;
    PushButtonGNSS[QZSS]=UiAntenna->pushButtonQZSS;
    PushButtonGNSS[IRNSS]=UiAntenna->pushButtonIRNSS;
}
//Function to initialize pointers to pushButton GNSS Measurements _clicked() functions
void GNSS_Antenna_Advanced::InitPushButtonGNSSMinFuncPointers(){
    PushButtonGNSSFunctions[GPS]=&GNSS_Antenna_Advanced::on_pushButtonGPS_clicked;
    PushButtonGNSSFunctions[Galileo]=&GNSS_Antenna_Advanced::on_pushButtonGalileo_clicked;
    PushButtonGNSSFunctions[GLONASS]=&GNSS_Antenna_Advanced::on_pushButtonGLONASS_clicked;
    PushButtonGNSSFunctions[GEO]=&GNSS_Antenna_Advanced::on_pushButtonGEO_clicked;
    PushButtonGNSSFunctions[BDS]=&GNSS_Antenna_Advanced::on_pushButtonBDS_clicked;
    PushButtonGNSSFunctions[QZSS]=&GNSS_Antenna_Advanced::on_pushButtonQZSS_clicked;
    PushButtonGNSSFunctions[IRNSS]=&GNSS_Antenna_Advanced::on_pushButtonIRNSS_clicked;
}
//Function to initialize pointers to RadioButton and LineEdit of Specify of GERSCJI
void GNSS_Antenna_Advanced::InitAPCPointers(){
    //GPS
    RadioGNSSSpecify[GPS][0]=UiAntenna->radioButtonAPCSpecifyF1GPS;
    RadioGNSSSpecify[GPS][1]=UiAntenna->radioButtonAPCSpecifyF2GPS;
    RadioGNSSSpecify[GPS][2]=UiAntenna->radioButtonAPCSpecifyF5GPS;

    RadioGNSSCopyFrom[GPS][0]=UiAntenna->radioButtonAPCCopyF1GPS;
    RadioGNSSCopyFrom[GPS][1]=UiAntenna->radioButtonAPCCopyF2GPS;
    RadioGNSSCopyFrom[GPS][2]=UiAntenna->radioButtonAPCCopyF5GPS;

    //Galileo
    RadioGNSSSpecify[Galileo][0]=UiAntenna->radioButtonAPCSpecifyF1Galileo;
    RadioGNSSSpecify[Galileo][1]=UiAntenna->radioButtonAPCSpecifyF5Galileo;
    RadioGNSSSpecify[Galileo][2]=UiAntenna->radioButtonAPCSpecifyF6Galileo;
    RadioGNSSSpecify[Galileo][3]=UiAntenna->radioButtonAPCSpecifyF7Galileo;
    RadioGNSSSpecify[Galileo][4]=UiAntenna->radioButtonAPCSpecifyF8Galileo;

    RadioGNSSCopyFrom[Galileo][0]=UiAntenna->radioButtonAPCCopyF1Galileo;
    RadioGNSSCopyFrom[Galileo][1]=UiAntenna->radioButtonAPCCopyF5Galileo;
    RadioGNSSCopyFrom[Galileo][2]=UiAntenna->radioButtonAPCCopyF6Galileo;
    RadioGNSSCopyFrom[Galileo][3]=UiAntenna->radioButtonAPCCopyF7Galileo;
    RadioGNSSCopyFrom[Galileo][4]=UiAntenna->radioButtonAPCCopyF8Galileo;

    //GLONASS
    RadioGNSSSpecify[GLONASS][0]=UiAntenna->radioButtonAPCSpecifyF1GLONASS;
    RadioGNSSSpecify[GLONASS][1]=UiAntenna->radioButtonAPCSpecifyF2GLONASS;
    RadioGNSSSpecify[GLONASS][2]=UiAntenna->radioButtonAPCSpecifyF3GLONASS;
    RadioGNSSSpecify[GLONASS][3]=UiAntenna->radioButtonAPCSpecifyF4GLONASS;
    RadioGNSSSpecify[GLONASS][4]=UiAntenna->radioButtonAPCSpecifyF6GLONASS;

    RadioGNSSCopyFrom[GLONASS][0]=UiAntenna->radioButtonAPCCopyF1GLONASS;
    RadioGNSSCopyFrom[GLONASS][1]=UiAntenna->radioButtonAPCCopyF2GLONASS;
    RadioGNSSCopyFrom[GLONASS][2]=UiAntenna->radioButtonAPCCopyF3GLONASS;
    RadioGNSSCopyFrom[GLONASS][3]=UiAntenna->radioButtonAPCCopyF4GLONASS;
    RadioGNSSCopyFrom[GLONASS][4]=UiAntenna->radioButtonAPCCopyF6GLONASS;

    //GEO
    RadioGNSSSpecify[GEO][0]=UiAntenna->radioButtonAPCSpecifyF1GEO;
    RadioGNSSSpecify[GEO][1]=UiAntenna->radioButtonAPCSpecifyF5GEO;

    RadioGNSSCopyFrom[GEO][0]=UiAntenna->radioButtonAPCCopyF1GEO;
    RadioGNSSCopyFrom[GEO][1]=UiAntenna->radioButtonAPCCopyF5GEO;

    //BDS
    RadioGNSSSpecify[BDS][0]=UiAntenna->radioButtonAPCSpecifyF1BDS;
    RadioGNSSSpecify[BDS][1]=UiAntenna->radioButtonAPCSpecifyF2BDS;
    RadioGNSSSpecify[BDS][2]=UiAntenna->radioButtonAPCSpecifyF5BDS;
    RadioGNSSSpecify[BDS][3]=UiAntenna->radioButtonAPCSpecifyF6BDS;
    RadioGNSSSpecify[BDS][4]=UiAntenna->radioButtonAPCSpecifyF7BDS;
    RadioGNSSSpecify[BDS][5]=UiAntenna->radioButtonAPCSpecifyF8BDS;

    RadioGNSSCopyFrom[BDS][0]=UiAntenna->radioButtonAPCCopyF1BDS;
    RadioGNSSCopyFrom[BDS][1]=UiAntenna->radioButtonAPCCopyF2BDS;
    RadioGNSSCopyFrom[BDS][2]=UiAntenna->radioButtonAPCCopyF5BDS;
    RadioGNSSCopyFrom[BDS][3]=UiAntenna->radioButtonAPCCopyF6BDS;
    RadioGNSSCopyFrom[BDS][4]=UiAntenna->radioButtonAPCCopyF7BDS;
    RadioGNSSCopyFrom[BDS][5]=UiAntenna->radioButtonAPCCopyF8BDS;

    //QZSS
    RadioGNSSSpecify[QZSS][0]=UiAntenna->radioButtonAPCSpecifyF1QZSS;
    RadioGNSSSpecify[QZSS][1]=UiAntenna->radioButtonAPCSpecifyF2QZSS;
    RadioGNSSSpecify[QZSS][2]=UiAntenna->radioButtonAPCSpecifyF5QZSS;
    RadioGNSSSpecify[QZSS][3]=UiAntenna->radioButtonAPCSpecifyF6QZSS;

    RadioGNSSCopyFrom[QZSS][0]=UiAntenna->radioButtonAPCCopyF1QZSS;
    RadioGNSSCopyFrom[QZSS][1]=UiAntenna->radioButtonAPCCopyF2QZSS;
    RadioGNSSCopyFrom[QZSS][2]=UiAntenna->radioButtonAPCCopyF5QZSS;
    RadioGNSSCopyFrom[QZSS][3]=UiAntenna->radioButtonAPCCopyF6QZSS;

    //IRNSS
    RadioGNSSSpecify[IRNSS][0]=UiAntenna->radioButtonAPCSpecifyF5IRNSS;
    RadioGNSSSpecify[IRNSS][1]=UiAntenna->radioButtonAPCSpecifyF9IRNSS;

    RadioGNSSCopyFrom[IRNSS][0]=UiAntenna->radioButtonAPCCopyF5IRNSS;
    RadioGNSSCopyFrom[IRNSS][1]=UiAntenna->radioButtonAPCCopyF9IRNSS;


    //North
    //GPS
    LineEditGNSSNEU[GPS][0][0]=UiAntenna->lineEditAPCNorthF1GPS;
    LineEditGNSSNEU[GPS][1][0]=UiAntenna->lineEditAPCNorthF2GPS;
    LineEditGNSSNEU[GPS][2][0]=UiAntenna->lineEditAPCNorthF5GPS;
    //Galileo
    LineEditGNSSNEU[Galileo][0][0]=UiAntenna->lineEditAPCNorthF1Galileo;
    LineEditGNSSNEU[Galileo][1][0]=UiAntenna->lineEditAPCNorthF5Galileo;
    LineEditGNSSNEU[Galileo][2][0]=UiAntenna->lineEditAPCNorthF6Galileo;
    LineEditGNSSNEU[Galileo][3][0]=UiAntenna->lineEditAPCNorthF7Galileo;
    LineEditGNSSNEU[Galileo][4][0]=UiAntenna->lineEditAPCNorthF8Galileo;
    //GLONASS
    LineEditGNSSNEU[GLONASS][0][0]=UiAntenna->lineEditAPCNorthF1GLONASS;
    LineEditGNSSNEU[GLONASS][1][0]=UiAntenna->lineEditAPCNorthF2GLONASS;
    LineEditGNSSNEU[GLONASS][2][0]=UiAntenna->lineEditAPCNorthF3GLONASS;
    LineEditGNSSNEU[GLONASS][3][0]=UiAntenna->lineEditAPCNorthF4GLONASS;
    LineEditGNSSNEU[GLONASS][4][0]=UiAntenna->lineEditAPCNorthF6GLONASS;
    //GEO
    LineEditGNSSNEU[GEO][0][0]=UiAntenna->lineEditAPCNorthF1GEO;
    LineEditGNSSNEU[GEO][1][0]=UiAntenna->lineEditAPCNorthF5GEO;
    //BDS
    LineEditGNSSNEU[BDS][0][0]=UiAntenna->lineEditAPCNorthF1BDS;
    LineEditGNSSNEU[BDS][1][0]=UiAntenna->lineEditAPCNorthF2BDS;
    LineEditGNSSNEU[BDS][2][0]=UiAntenna->lineEditAPCNorthF5BDS;
    LineEditGNSSNEU[BDS][3][0]=UiAntenna->lineEditAPCNorthF6BDS;
    LineEditGNSSNEU[BDS][4][0]=UiAntenna->lineEditAPCNorthF7BDS;
    LineEditGNSSNEU[BDS][5][0]=UiAntenna->lineEditAPCNorthF8BDS;
    //QZSS
    LineEditGNSSNEU[QZSS][0][0]=UiAntenna->lineEditAPCNorthF1QZSS;
    LineEditGNSSNEU[QZSS][1][0]=UiAntenna->lineEditAPCNorthF2QZSS;
    LineEditGNSSNEU[QZSS][2][0]=UiAntenna->lineEditAPCNorthF5QZSS;
    LineEditGNSSNEU[QZSS][3][0]=UiAntenna->lineEditAPCNorthF6QZSS;
    //IRNSS
    LineEditGNSSNEU[IRNSS][0][0]=UiAntenna->lineEditAPCNorthF5IRNSS;
    LineEditGNSSNEU[IRNSS][1][0]=UiAntenna->lineEditAPCNorthF9IRNSS;
    //East
    //GPS
    LineEditGNSSNEU[GPS][0][1]=UiAntenna->lineEditAPCEastF1GPS;
    LineEditGNSSNEU[GPS][1][1]=UiAntenna->lineEditAPCEastF2GPS;
    LineEditGNSSNEU[GPS][2][1]=UiAntenna->lineEditAPCEastF5GPS;
    //Galileo
    LineEditGNSSNEU[Galileo][0][1]=UiAntenna->lineEditAPCEastF1Galileo;
    LineEditGNSSNEU[Galileo][1][1]=UiAntenna->lineEditAPCEastF5Galileo;
    LineEditGNSSNEU[Galileo][2][1]=UiAntenna->lineEditAPCEastF6Galileo;
    LineEditGNSSNEU[Galileo][3][1]=UiAntenna->lineEditAPCEastF7Galileo;
    LineEditGNSSNEU[Galileo][4][1]=UiAntenna->lineEditAPCEastF8Galileo;
    //GLONASS
    LineEditGNSSNEU[GLONASS][0][1]=UiAntenna->lineEditAPCEastF1GLONASS;
    LineEditGNSSNEU[GLONASS][1][1]=UiAntenna->lineEditAPCEastF2GLONASS;
    LineEditGNSSNEU[GLONASS][2][1]=UiAntenna->lineEditAPCEastF3GLONASS;
    LineEditGNSSNEU[GLONASS][3][1]=UiAntenna->lineEditAPCEastF4GLONASS;
    LineEditGNSSNEU[GLONASS][4][1]=UiAntenna->lineEditAPCEastF6GLONASS;
    //GEO
    LineEditGNSSNEU[GEO][0][1]=UiAntenna->lineEditAPCEastF1GEO;
    LineEditGNSSNEU[GEO][1][1]=UiAntenna->lineEditAPCEastF5GEO;
    //BDS
    LineEditGNSSNEU[BDS][0][1]=UiAntenna->lineEditAPCEastF1BDS;
    LineEditGNSSNEU[BDS][1][1]=UiAntenna->lineEditAPCEastF2BDS;
    LineEditGNSSNEU[BDS][2][1]=UiAntenna->lineEditAPCEastF5BDS;
    LineEditGNSSNEU[BDS][3][1]=UiAntenna->lineEditAPCEastF6BDS;
    LineEditGNSSNEU[BDS][4][1]=UiAntenna->lineEditAPCEastF7BDS;
    LineEditGNSSNEU[BDS][5][1]=UiAntenna->lineEditAPCEastF8BDS;
    //QZSS
    LineEditGNSSNEU[QZSS][0][1]=UiAntenna->lineEditAPCEastF1QZSS;
    LineEditGNSSNEU[QZSS][1][1]=UiAntenna->lineEditAPCEastF2QZSS;
    LineEditGNSSNEU[QZSS][2][1]=UiAntenna->lineEditAPCEastF5QZSS;
    LineEditGNSSNEU[QZSS][3][1]=UiAntenna->lineEditAPCEastF6QZSS;
    //IRNSS
    LineEditGNSSNEU[IRNSS][0][1]=UiAntenna->lineEditAPCEastF5IRNSS;
    LineEditGNSSNEU[IRNSS][1][1]=UiAntenna->lineEditAPCEastF9IRNSS;
    //Up
    //GPS
    LineEditGNSSNEU[GPS][0][2]=UiAntenna->lineEditAPCUpF1GPS;
    LineEditGNSSNEU[GPS][1][2]=UiAntenna->lineEditAPCUpF2GPS;
    LineEditGNSSNEU[GPS][2][2]=UiAntenna->lineEditAPCUpF5GPS;
    //Galileo
    LineEditGNSSNEU[Galileo][0][2]=UiAntenna->lineEditAPCUpF1Galileo;
    LineEditGNSSNEU[Galileo][1][2]=UiAntenna->lineEditAPCUpF5Galileo;
    LineEditGNSSNEU[Galileo][2][2]=UiAntenna->lineEditAPCUpF6Galileo;
    LineEditGNSSNEU[Galileo][3][2]=UiAntenna->lineEditAPCUpF7Galileo;
    LineEditGNSSNEU[Galileo][4][2]=UiAntenna->lineEditAPCUpF8Galileo;
    //GLONASS
    LineEditGNSSNEU[GLONASS][0][2]=UiAntenna->lineEditAPCUpF1GLONASS;
    LineEditGNSSNEU[GLONASS][1][2]=UiAntenna->lineEditAPCUpF2GLONASS;
    LineEditGNSSNEU[GLONASS][2][2]=UiAntenna->lineEditAPCUpF3GLONASS;
    LineEditGNSSNEU[GLONASS][3][2]=UiAntenna->lineEditAPCUpF4GLONASS;
    LineEditGNSSNEU[GLONASS][4][2]=UiAntenna->lineEditAPCUpF6GLONASS;
    //GEO
    LineEditGNSSNEU[GEO][0][2]=UiAntenna->lineEditAPCUpF1GEO;
    LineEditGNSSNEU[GEO][1][2]=UiAntenna->lineEditAPCUpF5GEO;
    //BDS
    LineEditGNSSNEU[BDS][0][2]=UiAntenna->lineEditAPCUpF1BDS;
    LineEditGNSSNEU[BDS][1][2]=UiAntenna->lineEditAPCUpF2BDS;
    LineEditGNSSNEU[BDS][2][2]=UiAntenna->lineEditAPCUpF5BDS;
    LineEditGNSSNEU[BDS][3][2]=UiAntenna->lineEditAPCUpF6BDS;
    LineEditGNSSNEU[BDS][4][2]=UiAntenna->lineEditAPCUpF7BDS;
    LineEditGNSSNEU[BDS][5][2]=UiAntenna->lineEditAPCUpF8BDS;
    //QZSS
    LineEditGNSSNEU[QZSS][0][2]=UiAntenna->lineEditAPCUpF1QZSS;
    LineEditGNSSNEU[QZSS][1][2]=UiAntenna->lineEditAPCUpF2QZSS;
    LineEditGNSSNEU[QZSS][2][2]=UiAntenna->lineEditAPCUpF5QZSS;
    LineEditGNSSNEU[QZSS][3][2]=UiAntenna->lineEditAPCUpF6QZSS;
    //IRNSS
    LineEditGNSSNEU[IRNSS][0][2]=UiAntenna->lineEditAPCUpF5IRNSS;
    LineEditGNSSNEU[IRNSS][1][2]=UiAntenna->lineEditAPCUpF9IRNSS;

    //ComboBox Copy from GPS
    ComboBoxAPCSameAsConst[GPS][0]=UiAntenna->comboBoxAPCSameAsGPSF1Const;
    ComboBoxAPCSameAsConst[GPS][1]=UiAntenna->comboBoxAPCSameAsGPSF2Const;
    ComboBoxAPCSameAsConst[GPS][2]=UiAntenna->comboBoxAPCSameAsGPSF5Const;

    //ComboBox Copy from GPS F1
    ComboBoxAPCSameAsFreq[GPS][0][GPS]=UiAntenna->comboBoxAPCSameAsGPSF1FreqGPS;
    ComboBoxAPCSameAsFreq[GPS][0][Galileo]=UiAntenna->comboBoxAPCSameAsGPSF1FreqGAL;
    ComboBoxAPCSameAsFreq[GPS][0][GLONASS]=UiAntenna->comboBoxAPCSameAsGPSF1FreqGLONASS;
    ComboBoxAPCSameAsFreq[GPS][0][GEO]=UiAntenna->comboBoxAPCSameAsGPSF1FreqGEO;
    ComboBoxAPCSameAsFreq[GPS][0][BDS]=UiAntenna->comboBoxAPCSameAsGPSF1FreqBDS;
    ComboBoxAPCSameAsFreq[GPS][0][QZSS]=UiAntenna->comboBoxAPCSameAsGPSF1FreqQZSS;
    ComboBoxAPCSameAsFreq[GPS][0][IRNSS]=UiAntenna->comboBoxAPCSameAsGPSF1FreqIRNSS;

    //ComboBox Copy from GPS F2
    ComboBoxAPCSameAsFreq[GPS][1][GPS]=UiAntenna->comboBoxAPCSameAsGPSF2FreqGPS;
    ComboBoxAPCSameAsFreq[GPS][1][Galileo]=UiAntenna->comboBoxAPCSameAsGPSF2FreqGAL;
    ComboBoxAPCSameAsFreq[GPS][1][GLONASS]=UiAntenna->comboBoxAPCSameAsGPSF2FreqGLONASS;
    ComboBoxAPCSameAsFreq[GPS][1][GEO]=UiAntenna->comboBoxAPCSameAsGPSF2FreqGEO;
    ComboBoxAPCSameAsFreq[GPS][1][BDS]=UiAntenna->comboBoxAPCSameAsGPSF2FreqBDS;
    ComboBoxAPCSameAsFreq[GPS][1][QZSS]=UiAntenna->comboBoxAPCSameAsGPSF2FreqQZSS;
    ComboBoxAPCSameAsFreq[GPS][1][IRNSS]=UiAntenna->comboBoxAPCSameAsGPSF2FreqIRNSS;

    //ComboBox Copy from GPS F5
    ComboBoxAPCSameAsFreq[GPS][2][GPS]=UiAntenna->comboBoxAPCSameAsGPSF5FreqGPS;
    ComboBoxAPCSameAsFreq[GPS][2][Galileo]=UiAntenna->comboBoxAPCSameAsGPSF5FreqGAL;
    ComboBoxAPCSameAsFreq[GPS][2][GLONASS]=UiAntenna->comboBoxAPCSameAsGPSF5FreqGLONASS;
    ComboBoxAPCSameAsFreq[GPS][2][GEO]=UiAntenna->comboBoxAPCSameAsGPSF5FreqGEO;
    ComboBoxAPCSameAsFreq[GPS][2][BDS]=UiAntenna->comboBoxAPCSameAsGPSF5FreqBDS;
    ComboBoxAPCSameAsFreq[GPS][2][QZSS]=UiAntenna->comboBoxAPCSameAsGPSF5FreqQZSS;
    ComboBoxAPCSameAsFreq[GPS][2][IRNSS]=UiAntenna->comboBoxAPCSameAsGPSF5FreqIRNSS;

    //ComboBox Copy from Galileo
    ComboBoxAPCSameAsConst[Galileo][0]=UiAntenna->comboBoxAPCSameAsGalileoF1Const;
    ComboBoxAPCSameAsConst[Galileo][1]=UiAntenna->comboBoxAPCSameAsGalileoF5Const;
    ComboBoxAPCSameAsConst[Galileo][2]=UiAntenna->comboBoxAPCSameAsGalileoF6Const;
    ComboBoxAPCSameAsConst[Galileo][3]=UiAntenna->comboBoxAPCSameAsGalileoF7Const;
    ComboBoxAPCSameAsConst[Galileo][4]=UiAntenna->comboBoxAPCSameAsGalileoF8Const;

    //ComboBox Copy from Galileo F1
    ComboBoxAPCSameAsFreq[Galileo][0][GPS]=UiAntenna->comboBoxAPCSameAsGalileoF1FreqGPS;
    ComboBoxAPCSameAsFreq[Galileo][0][Galileo]=UiAntenna->comboBoxAPCSameAsGalileoF1FreqGAL;
    ComboBoxAPCSameAsFreq[Galileo][0][GLONASS]=UiAntenna->comboBoxAPCSameAsGalileoF1FreqGLONASS;
    ComboBoxAPCSameAsFreq[Galileo][0][GEO]=UiAntenna->comboBoxAPCSameAsGalileoF1FreqGEO;
    ComboBoxAPCSameAsFreq[Galileo][0][BDS]=UiAntenna->comboBoxAPCSameAsGalileoF1FreqBDS;
    ComboBoxAPCSameAsFreq[Galileo][0][QZSS]=UiAntenna->comboBoxAPCSameAsGalileoF1FreqQZSS;
    ComboBoxAPCSameAsFreq[Galileo][0][IRNSS]=UiAntenna->comboBoxAPCSameAsGalileoF1FreqIRNSS;

    //ComboBox Copy from Galileo F5
    ComboBoxAPCSameAsFreq[Galileo][1][GPS]=UiAntenna->comboBoxAPCSameAsGalileoF5FreqGPS;
    ComboBoxAPCSameAsFreq[Galileo][1][Galileo]=UiAntenna->comboBoxAPCSameAsGalileoF5FreqGAL;
    ComboBoxAPCSameAsFreq[Galileo][1][GLONASS]=UiAntenna->comboBoxAPCSameAsGalileoF5FreqGLONASS;
    ComboBoxAPCSameAsFreq[Galileo][1][GEO]=UiAntenna->comboBoxAPCSameAsGalileoF5FreqGEO;
    ComboBoxAPCSameAsFreq[Galileo][1][BDS]=UiAntenna->comboBoxAPCSameAsGalileoF5FreqBDS;
    ComboBoxAPCSameAsFreq[Galileo][1][QZSS]=UiAntenna->comboBoxAPCSameAsGalileoF5FreqQZSS;
    ComboBoxAPCSameAsFreq[Galileo][1][IRNSS]=UiAntenna->comboBoxAPCSameAsGalileoF5FreqIRNSS;

    //ComboBox Copy from Galileo F6
    ComboBoxAPCSameAsFreq[Galileo][2][GPS]=UiAntenna->comboBoxAPCSameAsGalileoF6FreqGPS;
    ComboBoxAPCSameAsFreq[Galileo][2][Galileo]=UiAntenna->comboBoxAPCSameAsGalileoF6FreqGAL;
    ComboBoxAPCSameAsFreq[Galileo][2][GLONASS]=UiAntenna->comboBoxAPCSameAsGalileoF6FreqGLONASS;
    ComboBoxAPCSameAsFreq[Galileo][2][GEO]=UiAntenna->comboBoxAPCSameAsGalileoF6FreqGEO;
    ComboBoxAPCSameAsFreq[Galileo][2][BDS]=UiAntenna->comboBoxAPCSameAsGalileoF6FreqBDS;
    ComboBoxAPCSameAsFreq[Galileo][2][QZSS]=UiAntenna->comboBoxAPCSameAsGalileoF6FreqQZSS;
    ComboBoxAPCSameAsFreq[Galileo][2][IRNSS]=UiAntenna->comboBoxAPCSameAsGalileoF6FreqIRNSS;

    //ComboBox Copy from Galileo F7
    ComboBoxAPCSameAsFreq[Galileo][3][GPS]=UiAntenna->comboBoxAPCSameAsGalileoF7FreqGPS;
    ComboBoxAPCSameAsFreq[Galileo][3][Galileo]=UiAntenna->comboBoxAPCSameAsGalileoF7FreqGAL;
    ComboBoxAPCSameAsFreq[Galileo][3][GLONASS]=UiAntenna->comboBoxAPCSameAsGalileoF7FreqGLONASS;
    ComboBoxAPCSameAsFreq[Galileo][3][GEO]=UiAntenna->comboBoxAPCSameAsGalileoF7FreqGEO;
    ComboBoxAPCSameAsFreq[Galileo][3][BDS]=UiAntenna->comboBoxAPCSameAsGalileoF7FreqBDS;
    ComboBoxAPCSameAsFreq[Galileo][3][QZSS]=UiAntenna->comboBoxAPCSameAsGalileoF7FreqQZSS;
    ComboBoxAPCSameAsFreq[Galileo][3][IRNSS]=UiAntenna->comboBoxAPCSameAsGalileoF7FreqIRNSS;

    //ComboBox Copy from Galileo F8
    ComboBoxAPCSameAsFreq[Galileo][4][GPS]=UiAntenna->comboBoxAPCSameAsGalileoF8FreqGPS;
    ComboBoxAPCSameAsFreq[Galileo][4][Galileo]=UiAntenna->comboBoxAPCSameAsGalileoF8FreqGAL;
    ComboBoxAPCSameAsFreq[Galileo][4][GLONASS]=UiAntenna->comboBoxAPCSameAsGalileoF8FreqGLONASS;
    ComboBoxAPCSameAsFreq[Galileo][4][GEO]=UiAntenna->comboBoxAPCSameAsGalileoF8FreqGEO;
    ComboBoxAPCSameAsFreq[Galileo][4][BDS]=UiAntenna->comboBoxAPCSameAsGalileoF8FreqBDS;
    ComboBoxAPCSameAsFreq[Galileo][4][QZSS]=UiAntenna->comboBoxAPCSameAsGalileoF8FreqQZSS;
    ComboBoxAPCSameAsFreq[Galileo][4][IRNSS]=UiAntenna->comboBoxAPCSameAsGalileoF8FreqIRNSS;

    //ComboBox Copy from GLONASS
    ComboBoxAPCSameAsConst[GLONASS][0]=UiAntenna->comboBoxAPCSameAsGLONASSF1Const;
    ComboBoxAPCSameAsConst[GLONASS][1]=UiAntenna->comboBoxAPCSameAsGLONASSF2Const;
    ComboBoxAPCSameAsConst[GLONASS][2]=UiAntenna->comboBoxAPCSameAsGLONASSF3Const;
    ComboBoxAPCSameAsConst[GLONASS][3]=UiAntenna->comboBoxAPCSameAsGLONASSF4Const;
    ComboBoxAPCSameAsConst[GLONASS][4]=UiAntenna->comboBoxAPCSameAsGLONASSF6Const;

    //ComboBox Copy from GLONASS F1
    ComboBoxAPCSameAsFreq[GLONASS][0][GPS]=UiAntenna->comboBoxAPCSameAsGLONASSF1FreqGPS;
    ComboBoxAPCSameAsFreq[GLONASS][0][Galileo]=UiAntenna->comboBoxAPCSameAsGLONASSF1FreqGAL;
    ComboBoxAPCSameAsFreq[GLONASS][0][GLONASS]=UiAntenna->comboBoxAPCSameAsGLONASSF1FreqGLONASS;
    ComboBoxAPCSameAsFreq[GLONASS][0][GEO]=UiAntenna->comboBoxAPCSameAsGLONASSF1FreqGEO;
    ComboBoxAPCSameAsFreq[GLONASS][0][BDS]=UiAntenna->comboBoxAPCSameAsGLONASSF1FreqBDS;
    ComboBoxAPCSameAsFreq[GLONASS][0][QZSS]=UiAntenna->comboBoxAPCSameAsGLONASSF1FreqQZSS;
    ComboBoxAPCSameAsFreq[GLONASS][0][IRNSS]=UiAntenna->comboBoxAPCSameAsGLONASSF1FreqIRNSS;

    //ComboBox Copy from GLONASS F2
    ComboBoxAPCSameAsFreq[GLONASS][1][GPS]=UiAntenna->comboBoxAPCSameAsGLONASSF2FreqGPS;
    ComboBoxAPCSameAsFreq[GLONASS][1][Galileo]=UiAntenna->comboBoxAPCSameAsGLONASSF2FreqGAL;
    ComboBoxAPCSameAsFreq[GLONASS][1][GLONASS]=UiAntenna->comboBoxAPCSameAsGLONASSF2FreqGLONASS;
    ComboBoxAPCSameAsFreq[GLONASS][1][GEO]=UiAntenna->comboBoxAPCSameAsGLONASSF2FreqGEO;
    ComboBoxAPCSameAsFreq[GLONASS][1][BDS]=UiAntenna->comboBoxAPCSameAsGLONASSF2FreqBDS;
    ComboBoxAPCSameAsFreq[GLONASS][1][QZSS]=UiAntenna->comboBoxAPCSameAsGLONASSF2FreqQZSS;
    ComboBoxAPCSameAsFreq[GLONASS][1][IRNSS]=UiAntenna->comboBoxAPCSameAsGLONASSF2FreqIRNSS;

    //ComboBox Copy from GLONASS F3
    ComboBoxAPCSameAsFreq[GLONASS][2][GPS]=UiAntenna->comboBoxAPCSameAsGLONASSF3FreqGPS;
    ComboBoxAPCSameAsFreq[GLONASS][2][Galileo]=UiAntenna->comboBoxAPCSameAsGLONASSF3FreqGAL;
    ComboBoxAPCSameAsFreq[GLONASS][2][GLONASS]=UiAntenna->comboBoxAPCSameAsGLONASSF3FreqGLONASS;
    ComboBoxAPCSameAsFreq[GLONASS][2][GEO]=UiAntenna->comboBoxAPCSameAsGLONASSF3FreqGEO;
    ComboBoxAPCSameAsFreq[GLONASS][2][BDS]=UiAntenna->comboBoxAPCSameAsGLONASSF3FreqBDS;
    ComboBoxAPCSameAsFreq[GLONASS][2][QZSS]=UiAntenna->comboBoxAPCSameAsGLONASSF3FreqQZSS;
    ComboBoxAPCSameAsFreq[GLONASS][2][IRNSS]=UiAntenna->comboBoxAPCSameAsGLONASSF3FreqIRNSS;

    //ComboBox Copy from GLONASS F4
    ComboBoxAPCSameAsFreq[GLONASS][3][GPS]=UiAntenna->comboBoxAPCSameAsGLONASSF4FreqGPS;
    ComboBoxAPCSameAsFreq[GLONASS][3][Galileo]=UiAntenna->comboBoxAPCSameAsGLONASSF4FreqGAL;
    ComboBoxAPCSameAsFreq[GLONASS][3][GLONASS]=UiAntenna->comboBoxAPCSameAsGLONASSF4FreqGLONASS;
    ComboBoxAPCSameAsFreq[GLONASS][3][GEO]=UiAntenna->comboBoxAPCSameAsGLONASSF4FreqGEO;
    ComboBoxAPCSameAsFreq[GLONASS][3][BDS]=UiAntenna->comboBoxAPCSameAsGLONASSF4FreqBDS;
    ComboBoxAPCSameAsFreq[GLONASS][3][QZSS]=UiAntenna->comboBoxAPCSameAsGLONASSF4FreqQZSS;
    ComboBoxAPCSameAsFreq[GLONASS][3][IRNSS]=UiAntenna->comboBoxAPCSameAsGLONASSF4FreqIRNSS;

    //ComboBox Copy from GLONASS F6
    ComboBoxAPCSameAsFreq[GLONASS][4][GPS]=UiAntenna->comboBoxAPCSameAsGLONASSF6FreqGPS;
    ComboBoxAPCSameAsFreq[GLONASS][4][Galileo]=UiAntenna->comboBoxAPCSameAsGLONASSF6FreqGAL;
    ComboBoxAPCSameAsFreq[GLONASS][4][GLONASS]=UiAntenna->comboBoxAPCSameAsGLONASSF6FreqGLONASS;
    ComboBoxAPCSameAsFreq[GLONASS][4][GEO]=UiAntenna->comboBoxAPCSameAsGLONASSF6FreqGEO;
    ComboBoxAPCSameAsFreq[GLONASS][4][BDS]=UiAntenna->comboBoxAPCSameAsGLONASSF6FreqBDS;
    ComboBoxAPCSameAsFreq[GLONASS][4][QZSS]=UiAntenna->comboBoxAPCSameAsGLONASSF6FreqQZSS;
    ComboBoxAPCSameAsFreq[GLONASS][4][IRNSS]=UiAntenna->comboBoxAPCSameAsGLONASSF6FreqIRNSS;

    //ComboBox Copy from GEO
    ComboBoxAPCSameAsConst[GEO][0]=UiAntenna->comboBoxAPCSameAsGEOF1Const;
    ComboBoxAPCSameAsConst[GEO][1]=UiAntenna->comboBoxAPCSameAsGEOF5Const;

    //ComboBox Copy from GEO F1
    ComboBoxAPCSameAsFreq[GEO][0][GPS]=UiAntenna->comboBoxAPCSameAsGEOF1FreqGPS;
    ComboBoxAPCSameAsFreq[GEO][0][Galileo]=UiAntenna->comboBoxAPCSameAsGEOF1FreqGAL;
    ComboBoxAPCSameAsFreq[GEO][0][GLONASS]=UiAntenna->comboBoxAPCSameAsGEOF1FreqGLONASS;
    ComboBoxAPCSameAsFreq[GEO][0][GEO]=UiAntenna->comboBoxAPCSameAsGEOF1FreqGEO;
    ComboBoxAPCSameAsFreq[GEO][0][BDS]=UiAntenna->comboBoxAPCSameAsGEOF1FreqBDS;
    ComboBoxAPCSameAsFreq[GEO][0][QZSS]=UiAntenna->comboBoxAPCSameAsGEOF1FreqQZSS;
    ComboBoxAPCSameAsFreq[GEO][0][IRNSS]=UiAntenna->comboBoxAPCSameAsGEOF1FreqIRNSS;

    //ComboBox Copy from GEO F5
    ComboBoxAPCSameAsFreq[GEO][1][GPS]=UiAntenna->comboBoxAPCSameAsGEOF5FreqGPS;
    ComboBoxAPCSameAsFreq[GEO][1][Galileo]=UiAntenna->comboBoxAPCSameAsGEOF5FreqGAL;
    ComboBoxAPCSameAsFreq[GEO][1][GLONASS]=UiAntenna->comboBoxAPCSameAsGEOF5FreqGLONASS;
    ComboBoxAPCSameAsFreq[GEO][1][GEO]=UiAntenna->comboBoxAPCSameAsGEOF5FreqGEO;
    ComboBoxAPCSameAsFreq[GEO][1][BDS]=UiAntenna->comboBoxAPCSameAsGEOF5FreqBDS;
    ComboBoxAPCSameAsFreq[GEO][1][QZSS]=UiAntenna->comboBoxAPCSameAsGEOF5FreqQZSS;
    ComboBoxAPCSameAsFreq[GEO][1][IRNSS]=UiAntenna->comboBoxAPCSameAsGEOF5FreqIRNSS;

    //ComboBox Copy from BDS
    ComboBoxAPCSameAsConst[BDS][0]=UiAntenna->comboBoxAPCSameAsBDSF1Const;
    ComboBoxAPCSameAsConst[BDS][1]=UiAntenna->comboBoxAPCSameAsBDSF2Const;
    ComboBoxAPCSameAsConst[BDS][2]=UiAntenna->comboBoxAPCSameAsBDSF5Const;
    ComboBoxAPCSameAsConst[BDS][3]=UiAntenna->comboBoxAPCSameAsBDSF6Const;
    ComboBoxAPCSameAsConst[BDS][4]=UiAntenna->comboBoxAPCSameAsBDSF7Const;
    ComboBoxAPCSameAsConst[BDS][5]=UiAntenna->comboBoxAPCSameAsBDSF8Const;

    //ComboBox Copy from BDS F1
    ComboBoxAPCSameAsFreq[BDS][0][GPS]=UiAntenna->comboBoxAPCSameAsBDSF1FreqGPS;
    ComboBoxAPCSameAsFreq[BDS][0][Galileo]=UiAntenna->comboBoxAPCSameAsBDSF1FreqGAL;
    ComboBoxAPCSameAsFreq[BDS][0][GLONASS]=UiAntenna->comboBoxAPCSameAsBDSF1FreqGLONASS;
    ComboBoxAPCSameAsFreq[BDS][0][GEO]=UiAntenna->comboBoxAPCSameAsBDSF1FreqGEO;
    ComboBoxAPCSameAsFreq[BDS][0][BDS]=UiAntenna->comboBoxAPCSameAsBDSF1FreqBDS;
    ComboBoxAPCSameAsFreq[BDS][0][QZSS]=UiAntenna->comboBoxAPCSameAsBDSF1FreqQZSS;
    ComboBoxAPCSameAsFreq[BDS][0][IRNSS]=UiAntenna->comboBoxAPCSameAsBDSF1FreqIRNSS;

    //ComboBox Copy from BDS F2
    ComboBoxAPCSameAsFreq[BDS][1][GPS]=UiAntenna->comboBoxAPCSameAsBDSF2FreqGPS;
    ComboBoxAPCSameAsFreq[BDS][1][Galileo]=UiAntenna->comboBoxAPCSameAsBDSF2FreqGAL;
    ComboBoxAPCSameAsFreq[BDS][1][GLONASS]=UiAntenna->comboBoxAPCSameAsBDSF2FreqGLONASS;
    ComboBoxAPCSameAsFreq[BDS][1][GEO]=UiAntenna->comboBoxAPCSameAsBDSF2FreqGEO;
    ComboBoxAPCSameAsFreq[BDS][1][BDS]=UiAntenna->comboBoxAPCSameAsBDSF2FreqBDS;
    ComboBoxAPCSameAsFreq[BDS][1][QZSS]=UiAntenna->comboBoxAPCSameAsBDSF2FreqQZSS;
    ComboBoxAPCSameAsFreq[BDS][1][IRNSS]=UiAntenna->comboBoxAPCSameAsBDSF2FreqIRNSS;

    //ComboBox Copy from BDS F5
    ComboBoxAPCSameAsFreq[BDS][2][GPS]=UiAntenna->comboBoxAPCSameAsBDSF5FreqGPS;
    ComboBoxAPCSameAsFreq[BDS][2][Galileo]=UiAntenna->comboBoxAPCSameAsBDSF5FreqGAL;
    ComboBoxAPCSameAsFreq[BDS][2][GLONASS]=UiAntenna->comboBoxAPCSameAsBDSF5FreqGLONASS;
    ComboBoxAPCSameAsFreq[BDS][2][GEO]=UiAntenna->comboBoxAPCSameAsBDSF5FreqGEO;
    ComboBoxAPCSameAsFreq[BDS][2][BDS]=UiAntenna->comboBoxAPCSameAsBDSF5FreqBDS;
    ComboBoxAPCSameAsFreq[BDS][2][QZSS]=UiAntenna->comboBoxAPCSameAsBDSF5FreqQZSS;
    ComboBoxAPCSameAsFreq[BDS][2][IRNSS]=UiAntenna->comboBoxAPCSameAsBDSF5FreqIRNSS;

    //ComboBox Copy from BDS F6
    ComboBoxAPCSameAsFreq[BDS][3][GPS]=UiAntenna->comboBoxAPCSameAsBDSF6FreqGPS;
    ComboBoxAPCSameAsFreq[BDS][3][Galileo]=UiAntenna->comboBoxAPCSameAsBDSF6FreqGAL;
    ComboBoxAPCSameAsFreq[BDS][3][GLONASS]=UiAntenna->comboBoxAPCSameAsBDSF6FreqGLONASS;
    ComboBoxAPCSameAsFreq[BDS][3][GEO]=UiAntenna->comboBoxAPCSameAsBDSF6FreqGEO;
    ComboBoxAPCSameAsFreq[BDS][3][BDS]=UiAntenna->comboBoxAPCSameAsBDSF6FreqBDS;
    ComboBoxAPCSameAsFreq[BDS][3][QZSS]=UiAntenna->comboBoxAPCSameAsBDSF6FreqQZSS;
    ComboBoxAPCSameAsFreq[BDS][3][IRNSS]=UiAntenna->comboBoxAPCSameAsBDSF6FreqIRNSS;

    //ComboBox Copy from BDS F7
    ComboBoxAPCSameAsFreq[BDS][4][GPS]=UiAntenna->comboBoxAPCSameAsBDSF7FreqGPS;
    ComboBoxAPCSameAsFreq[BDS][4][Galileo]=UiAntenna->comboBoxAPCSameAsBDSF7FreqGAL;
    ComboBoxAPCSameAsFreq[BDS][4][GLONASS]=UiAntenna->comboBoxAPCSameAsBDSF7FreqGLONASS;
    ComboBoxAPCSameAsFreq[BDS][4][GEO]=UiAntenna->comboBoxAPCSameAsBDSF7FreqGEO;
    ComboBoxAPCSameAsFreq[BDS][4][BDS]=UiAntenna->comboBoxAPCSameAsBDSF7FreqBDS;
    ComboBoxAPCSameAsFreq[BDS][4][QZSS]=UiAntenna->comboBoxAPCSameAsBDSF7FreqQZSS;
    ComboBoxAPCSameAsFreq[BDS][4][IRNSS]=UiAntenna->comboBoxAPCSameAsBDSF7FreqIRNSS;

    //ComboBox Copy from BDS F8
    ComboBoxAPCSameAsFreq[BDS][5][GPS]=UiAntenna->comboBoxAPCSameAsBDSF8FreqGPS;
    ComboBoxAPCSameAsFreq[BDS][5][Galileo]=UiAntenna->comboBoxAPCSameAsBDSF8FreqGAL;
    ComboBoxAPCSameAsFreq[BDS][5][GLONASS]=UiAntenna->comboBoxAPCSameAsBDSF8FreqGLONASS;
    ComboBoxAPCSameAsFreq[BDS][5][GEO]=UiAntenna->comboBoxAPCSameAsBDSF8FreqGEO;
    ComboBoxAPCSameAsFreq[BDS][5][BDS]=UiAntenna->comboBoxAPCSameAsBDSF8FreqBDS;
    ComboBoxAPCSameAsFreq[BDS][5][QZSS]=UiAntenna->comboBoxAPCSameAsBDSF8FreqQZSS;
    ComboBoxAPCSameAsFreq[BDS][5][IRNSS]=UiAntenna->comboBoxAPCSameAsBDSF8FreqIRNSS;

    //ComboBox Copy from QZSS
    ComboBoxAPCSameAsConst[QZSS][0]=UiAntenna->comboBoxAPCSameAsQZSSF1Const;
    ComboBoxAPCSameAsConst[QZSS][1]=UiAntenna->comboBoxAPCSameAsQZSSF2Const;
    ComboBoxAPCSameAsConst[QZSS][2]=UiAntenna->comboBoxAPCSameAsQZSSF5Const;
    ComboBoxAPCSameAsConst[QZSS][3]=UiAntenna->comboBoxAPCSameAsQZSSF6Const;

    //ComboBox Copy from QZSS F1
    ComboBoxAPCSameAsFreq[QZSS][0][GPS]=UiAntenna->comboBoxAPCSameAsQZSSF1FreqGPS;
    ComboBoxAPCSameAsFreq[QZSS][0][Galileo]=UiAntenna->comboBoxAPCSameAsQZSSF1FreqGAL;
    ComboBoxAPCSameAsFreq[QZSS][0][GLONASS]=UiAntenna->comboBoxAPCSameAsQZSSF1FreqGLONASS;
    ComboBoxAPCSameAsFreq[QZSS][0][GEO]=UiAntenna->comboBoxAPCSameAsQZSSF1FreqGEO;
    ComboBoxAPCSameAsFreq[QZSS][0][BDS]=UiAntenna->comboBoxAPCSameAsQZSSF1FreqBDS;
    ComboBoxAPCSameAsFreq[QZSS][0][QZSS]=UiAntenna->comboBoxAPCSameAsQZSSF1FreqQZSS;
    ComboBoxAPCSameAsFreq[QZSS][0][IRNSS]=UiAntenna->comboBoxAPCSameAsQZSSF1FreqIRNSS;

    //ComboBox Copy from QZSS F3
    ComboBoxAPCSameAsFreq[QZSS][1][GPS]=UiAntenna->comboBoxAPCSameAsQZSSF2FreqGPS;
    ComboBoxAPCSameAsFreq[QZSS][1][Galileo]=UiAntenna->comboBoxAPCSameAsQZSSF2FreqGAL;
    ComboBoxAPCSameAsFreq[QZSS][1][GLONASS]=UiAntenna->comboBoxAPCSameAsQZSSF2FreqGLONASS;
    ComboBoxAPCSameAsFreq[QZSS][1][GEO]=UiAntenna->comboBoxAPCSameAsQZSSF2FreqGEO;
    ComboBoxAPCSameAsFreq[QZSS][1][BDS]=UiAntenna->comboBoxAPCSameAsQZSSF2FreqBDS;
    ComboBoxAPCSameAsFreq[QZSS][1][QZSS]=UiAntenna->comboBoxAPCSameAsQZSSF2FreqQZSS;
    ComboBoxAPCSameAsFreq[QZSS][1][IRNSS]=UiAntenna->comboBoxAPCSameAsQZSSF2FreqIRNSS;

    //ComboBox Copy from QZSS F5
    ComboBoxAPCSameAsFreq[QZSS][2][GPS]=UiAntenna->comboBoxAPCSameAsQZSSF5FreqGPS;
    ComboBoxAPCSameAsFreq[QZSS][2][Galileo]=UiAntenna->comboBoxAPCSameAsQZSSF5FreqGAL;
    ComboBoxAPCSameAsFreq[QZSS][2][GLONASS]=UiAntenna->comboBoxAPCSameAsQZSSF5FreqGLONASS;
    ComboBoxAPCSameAsFreq[QZSS][2][GEO]=UiAntenna->comboBoxAPCSameAsQZSSF5FreqGEO;
    ComboBoxAPCSameAsFreq[QZSS][2][BDS]=UiAntenna->comboBoxAPCSameAsQZSSF5FreqBDS;
    ComboBoxAPCSameAsFreq[QZSS][2][QZSS]=UiAntenna->comboBoxAPCSameAsQZSSF5FreqQZSS;
    ComboBoxAPCSameAsFreq[QZSS][2][IRNSS]=UiAntenna->comboBoxAPCSameAsQZSSF5FreqIRNSS;

    //ComboBox Copy from QZSS F6
    ComboBoxAPCSameAsFreq[QZSS][3][GPS]=UiAntenna->comboBoxAPCSameAsQZSSF6FreqGPS;
    ComboBoxAPCSameAsFreq[QZSS][3][Galileo]=UiAntenna->comboBoxAPCSameAsQZSSF6FreqGAL;
    ComboBoxAPCSameAsFreq[QZSS][3][GLONASS]=UiAntenna->comboBoxAPCSameAsQZSSF6FreqGLONASS;
    ComboBoxAPCSameAsFreq[QZSS][3][GEO]=UiAntenna->comboBoxAPCSameAsQZSSF6FreqGEO;
    ComboBoxAPCSameAsFreq[QZSS][3][BDS]=UiAntenna->comboBoxAPCSameAsQZSSF6FreqBDS;
    ComboBoxAPCSameAsFreq[QZSS][3][QZSS]=UiAntenna->comboBoxAPCSameAsQZSSF6FreqQZSS;
    ComboBoxAPCSameAsFreq[QZSS][3][IRNSS]=UiAntenna->comboBoxAPCSameAsQZSSF6FreqIRNSS;

    //ComboBox Copy from IRNSS
    ComboBoxAPCSameAsConst[IRNSS][0]=UiAntenna->comboBoxAPCSameAsIRNSSF5Const;
    ComboBoxAPCSameAsConst[IRNSS][1]=UiAntenna->comboBoxAPCSameAsIRNSSF9Const;

    //ComboBox Copy from IRNSS F5
    ComboBoxAPCSameAsFreq[IRNSS][0][GPS]=UiAntenna->comboBoxAPCSameAsIRNSSF5FreqGPS;
    ComboBoxAPCSameAsFreq[IRNSS][0][Galileo]=UiAntenna->comboBoxAPCSameAsIRNSSF5FreqGAL;
    ComboBoxAPCSameAsFreq[IRNSS][0][GLONASS]=UiAntenna->comboBoxAPCSameAsIRNSSF5FreqGLONASS;
    ComboBoxAPCSameAsFreq[IRNSS][0][GEO]=UiAntenna->comboBoxAPCSameAsIRNSSF5FreqGEO;
    ComboBoxAPCSameAsFreq[IRNSS][0][BDS]=UiAntenna->comboBoxAPCSameAsIRNSSF5FreqBDS;
    ComboBoxAPCSameAsFreq[IRNSS][0][QZSS]=UiAntenna->comboBoxAPCSameAsIRNSSF5FreqQZSS;
    ComboBoxAPCSameAsFreq[IRNSS][0][IRNSS]=UiAntenna->comboBoxAPCSameAsIRNSSF5FreqIRNSS;

    //ComboBox Copy from IRNSS F5
    ComboBoxAPCSameAsFreq[IRNSS][1][GPS]=UiAntenna->comboBoxAPCSameAsIRNSSF9FreqGPS;
    ComboBoxAPCSameAsFreq[IRNSS][1][Galileo]=UiAntenna->comboBoxAPCSameAsIRNSSF9FreqGAL;
    ComboBoxAPCSameAsFreq[IRNSS][1][GLONASS]=UiAntenna->comboBoxAPCSameAsIRNSSF9FreqGLONASS;
    ComboBoxAPCSameAsFreq[IRNSS][1][GEO]=UiAntenna->comboBoxAPCSameAsIRNSSF9FreqGEO;
    ComboBoxAPCSameAsFreq[IRNSS][1][BDS]=UiAntenna->comboBoxAPCSameAsIRNSSF9FreqBDS;
    ComboBoxAPCSameAsFreq[IRNSS][1][QZSS]=UiAntenna->comboBoxAPCSameAsIRNSSF9FreqQZSS;
    ComboBoxAPCSameAsFreq[IRNSS][1][IRNSS]=UiAntenna->comboBoxAPCSameAsIRNSSF9FreqIRNSS;
}

void GNSS_Antenna_Advanced::setAPCdefaults(){
    this->SetDefaultAPCGPS();
    this->SetDefaultAPCGalileo();
    this->SetDefaultAPCGLONASS();
    this->SetDefaultAPCGEO();
    this->SetDefaultAPCBDS();
    this->SetDefaultAPCQZSS();
    this->SetDefaultAPCIRNSS();
}

//GPS
//Function to set GPS Default
void GNSS_Antenna_Advanced::SetDefaultAPCGPS(){
    this->on_radioButtonAPCReadF1GPS_clicked();
    this->on_radioButtonAPCReadF2GPS_clicked();
    this->on_radioButtonAPCReadF5GPS_clicked();

    this->on_comboBoxAPCSameAsGPSF1Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsGPSF2Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsGPSF5Const_currentIndexChanged(0);
    for (int i=0; i<nFreqGNSS[GPS]; i++){
        for (int j=0; j<3; j++){
            LineEditGNSSNEU[GPS][i][j]->setText("0");
        }
        ComboBoxAPCSameAsConst[GPS][i]->setCurrentIndex(0);
        for (int j=0; j<MAX_GNSS; j++){
            ComboBoxAPCSameAsFreq[GPS][i][j]->setCurrentIndex(0);
        }
    }
}
//GPS F1
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF1GPS_clicked(){
    UiAntenna->radioButtonAPCReadF1GPS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF1GPS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF1GPS->setChecked(false);
    UiAntenna->frameAPCF1GPSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF1GPS->setHidden(true);

}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF1GPS_clicked(){
    UiAntenna->radioButtonAPCReadF1GPS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF1GPS->setChecked(true);
    UiAntenna->radioButtonAPCCopyF1GPS->setChecked(false);
    UiAntenna->frameAPCF1GPSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF1GPS->setHidden(false);

}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF1GPS_clicked(){
    UiAntenna->radioButtonAPCReadF1GPS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF1GPS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF1GPS->setChecked(true);
    UiAntenna->frameAPCF1GPS->setHidden(true);
    UiAntenna->frameAPCF1GPSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsGPSF1Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsGPSF1->setCurrentIndex(index);
}
//GPS F2
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF2GPS_clicked(){
    UiAntenna->radioButtonAPCReadF2GPS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF2GPS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF2GPS->setChecked(false);
    UiAntenna->frameAPCF2GPSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF2GPS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF2GPS_clicked(){
    UiAntenna->radioButtonAPCReadF2GPS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF2GPS->setChecked(true);
    UiAntenna->radioButtonAPCCopyF2GPS->setChecked(false);
    UiAntenna->frameAPCF2GPSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF2GPS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF2GPS_clicked(){
    UiAntenna->radioButtonAPCReadF2GPS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF2GPS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF2GPS->setChecked(true);
    UiAntenna->frameAPCF2GPS->setHidden(true);
    UiAntenna->frameAPCF2GPSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsGPSF2Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsGPSF2->setCurrentIndex(index);
}
//GPS F5
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF5GPS_clicked(){
    UiAntenna->radioButtonAPCReadF5GPS->setChecked(true);
    UiAntenna->radioButtonAPCCopyF5GPS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF5GPS->setChecked(false);
    UiAntenna->frameAPCF5GPSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF5GPS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF5GPS_clicked(){
    UiAntenna->radioButtonAPCReadF5GPS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF5GPS->setChecked(true);
    UiAntenna->radioButtonAPCCopyF5GPS->setChecked(false);
    UiAntenna->frameAPCF5GPSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF5GPS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF5GPS_clicked(){
    UiAntenna->radioButtonAPCSpecifyF5GPS->setChecked(false);
    UiAntenna->radioButtonAPCReadF5GPS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF5GPS->setChecked(true);
    UiAntenna->frameAPCF5GPS->setHidden(true);
    UiAntenna->frameAPCF5GPSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsGPSF5Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsGPSF5->setCurrentIndex(index);
}
//Galileo
//Function to set Galileo Default
void GNSS_Antenna_Advanced::SetDefaultAPCGalileo(){
    this->on_radioButtonAPCReadF1Galileo_clicked();
    this->on_radioButtonAPCReadF5Galileo_clicked();
    this->on_radioButtonAPCReadF6Galileo_clicked();
    this->on_radioButtonAPCReadF7Galileo_clicked();
    this->on_radioButtonAPCReadF8Galileo_clicked();

    this->on_comboBoxAPCSameAsGalileoF1Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsGalileoF5Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsGalileoF6Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsGalileoF7Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsGalileoF8Const_currentIndexChanged(0);
    for (int i=0; i<nFreqGNSS[Galileo]; i++){
        for (int j=0; j<3; j++){
            LineEditGNSSNEU[Galileo][i][j]->setText("0");
        }
        ComboBoxAPCSameAsConst[Galileo][i]->setCurrentIndex(0);
        for (int j=0; j<MAX_GNSS; j++){
            ComboBoxAPCSameAsFreq[Galileo][i][j]->setCurrentIndex(0);
        }
    }
}
//Galileo F1
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF1Galileo_clicked(){
    UiAntenna->radioButtonAPCReadF1Galileo->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF1Galileo->setChecked(false);
    UiAntenna->radioButtonAPCCopyF1Galileo->setChecked(false);
    UiAntenna->frameAPCF1GalileoCopyFrom->setHidden(true);
    UiAntenna->frameAPCF1Galileo->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF1Galileo_clicked(){
    UiAntenna->radioButtonAPCSpecifyF1Galileo->setChecked(true);
    UiAntenna->radioButtonAPCReadF1Galileo->setChecked(false);
    UiAntenna->radioButtonAPCCopyF1Galileo->setChecked(false);
    UiAntenna->frameAPCF1GalileoCopyFrom->setHidden(true);
    UiAntenna->frameAPCF1Galileo->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF1Galileo_clicked(){
    UiAntenna->radioButtonAPCSpecifyF1Galileo->setChecked(false);
    UiAntenna->radioButtonAPCReadF1Galileo->setChecked(false);
    UiAntenna->radioButtonAPCCopyF1Galileo->setChecked(true);
    UiAntenna->frameAPCF1Galileo->setHidden(true);
    UiAntenna->frameAPCF1GalileoCopyFrom->setHidden(false);

}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsGalileoF1Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsGalileoF1->setCurrentIndex(index);
}
//Galileo F5
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF5Galileo_clicked(){
    UiAntenna->radioButtonAPCReadF5Galileo->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF5Galileo->setChecked(false);
    UiAntenna->radioButtonAPCCopyF5Galileo->setChecked(false);
    UiAntenna->frameAPCF5GalileoCopyFrom->setHidden(true);
    UiAntenna->frameAPCF5Galileo->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF5Galileo_clicked(){
    UiAntenna->radioButtonAPCSpecifyF5Galileo->setChecked(true);
    UiAntenna->radioButtonAPCReadF5Galileo->setChecked(false);
    UiAntenna->radioButtonAPCCopyF5Galileo->setChecked(false);
    UiAntenna->frameAPCF5GalileoCopyFrom->setHidden(true);
    UiAntenna->frameAPCF5Galileo->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF5Galileo_clicked(){
    UiAntenna->radioButtonAPCSpecifyF5Galileo->setChecked(false);
    UiAntenna->radioButtonAPCReadF5Galileo->setChecked(false);
    UiAntenna->radioButtonAPCCopyF5Galileo->setChecked(true);
    UiAntenna->frameAPCF5Galileo->setHidden(true);
    UiAntenna->frameAPCF5GalileoCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsGalileoF5Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsGalileoF5->setCurrentIndex(index);
}
//Galileo F6
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF6Galileo_clicked(){
    UiAntenna->radioButtonAPCReadF6Galileo->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF6Galileo->setChecked(false);
    UiAntenna->radioButtonAPCCopyF6Galileo->setChecked(false);
    UiAntenna->frameAPCF6GalileoCopyFrom->setHidden(true);
    UiAntenna->frameAPCF6Galileo->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF6Galileo_clicked(){
    UiAntenna->radioButtonAPCSpecifyF6Galileo->setChecked(true);
    UiAntenna->radioButtonAPCReadF6Galileo->setChecked(false);
    UiAntenna->radioButtonAPCCopyF6Galileo->setChecked(false);
    UiAntenna->frameAPCF6GalileoCopyFrom->setHidden(true);
    UiAntenna->frameAPCF6Galileo->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF6Galileo_clicked(){
    UiAntenna->radioButtonAPCSpecifyF6Galileo->setChecked(false);
    UiAntenna->radioButtonAPCReadF6Galileo->setChecked(false);
    UiAntenna->radioButtonAPCCopyF6Galileo->setChecked(true);
    UiAntenna->frameAPCF6Galileo->setHidden(true);
    UiAntenna->frameAPCF6GalileoCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsGalileoF6Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsGalileoF6->setCurrentIndex(index);
}
//Galileo F7
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF7Galileo_clicked(){
    UiAntenna->radioButtonAPCReadF7Galileo->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF7Galileo->setChecked(false);
    UiAntenna->radioButtonAPCCopyF7Galileo->setChecked(false);
    UiAntenna->frameAPCF7GalileoCopyFrom->setHidden(true);
    UiAntenna->frameAPCF7Galileo->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF7Galileo_clicked(){
    UiAntenna->radioButtonAPCSpecifyF7Galileo->setChecked(true);
    UiAntenna->radioButtonAPCReadF7Galileo->setChecked(false);
    UiAntenna->radioButtonAPCCopyF7Galileo->setChecked(false);
    UiAntenna->frameAPCF7GalileoCopyFrom->setHidden(true);
    UiAntenna->frameAPCF7Galileo->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF7Galileo_clicked(){
    UiAntenna->radioButtonAPCSpecifyF7Galileo->setChecked(false);
    UiAntenna->radioButtonAPCReadF7Galileo->setChecked(false);
    UiAntenna->radioButtonAPCCopyF7Galileo->setChecked(true);
    UiAntenna->frameAPCF7Galileo->setHidden(true);
    UiAntenna->frameAPCF7GalileoCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsGalileoF7Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsGalileoF7->setCurrentIndex(index);
}
//Galileo F8
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF8Galileo_clicked(){
    UiAntenna->radioButtonAPCReadF8Galileo->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF8Galileo->setChecked(false);
    UiAntenna->radioButtonAPCCopyF8Galileo->setChecked(false);
    UiAntenna->frameAPCF8GalileoCopyFrom->setHidden(true);
    UiAntenna->frameAPCF8Galileo->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF8Galileo_clicked(){
    UiAntenna->radioButtonAPCSpecifyF8Galileo->setChecked(true);
    UiAntenna->radioButtonAPCReadF8Galileo->setChecked(false);
    UiAntenna->radioButtonAPCCopyF8Galileo->setChecked(false);
    UiAntenna->frameAPCF8GalileoCopyFrom->setHidden(true);
    UiAntenna->frameAPCF8Galileo->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF8Galileo_clicked(){
    UiAntenna->radioButtonAPCSpecifyF8Galileo->setChecked(false);
    UiAntenna->radioButtonAPCReadF8Galileo->setChecked(false);
    UiAntenna->radioButtonAPCCopyF8Galileo->setChecked(true);
    UiAntenna->frameAPCF8Galileo->setHidden(true);
    UiAntenna->frameAPCF8GalileoCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsGalileoF8Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsGalileoF8->setCurrentIndex(index);
}

//GLONASS
//Function to set GLONASS Default
void GNSS_Antenna_Advanced::SetDefaultAPCGLONASS(){
    this->on_radioButtonAPCReadF1GLONASS_clicked();
    this->on_radioButtonAPCReadF2GLONASS_clicked();
    this->on_radioButtonAPCReadF3GLONASS_clicked();
    this->on_radioButtonAPCReadF4GLONASS_clicked();
    this->on_radioButtonAPCReadF6GLONASS_clicked();

    this->on_comboBoxAPCSameAsGLONASSF1Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsGLONASSF2Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsGLONASSF3Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsGLONASSF4Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsGLONASSF6Const_currentIndexChanged(0);
    for (int i=0; i<nFreqGNSS[GLONASS]; i++){
        for (int j=0; j<3; j++){
            LineEditGNSSNEU[GLONASS][i][j]->setText("0");
        }
        ComboBoxAPCSameAsConst[GLONASS][i]->setCurrentIndex(0);
        for (int j=0; j<MAX_GNSS; j++){
            ComboBoxAPCSameAsFreq[GLONASS][i][j]->setCurrentIndex(0);
        }
    }
}
//GLONASS F1
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF1GLONASS_clicked(){
    UiAntenna->radioButtonAPCReadF1GLONASS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF1GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF1GLONASS->setChecked(false);
    UiAntenna->frameAPCF1GLONASSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF1GLONASS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF1GLONASS_clicked(){
    UiAntenna->radioButtonAPCSpecifyF1GLONASS->setChecked(true);
    UiAntenna->radioButtonAPCReadF1GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF1GLONASS->setChecked(false);
    UiAntenna->frameAPCF1GLONASSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF1GLONASS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF1GLONASS_clicked(){
    UiAntenna->radioButtonAPCSpecifyF1GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCReadF1GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF1GLONASS->setChecked(true);
    UiAntenna->frameAPCF1GLONASS->setHidden(true);
    UiAntenna->frameAPCF1GLONASSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsGLONASSF1Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsGLONASSF1->setCurrentIndex(index);
}
//GLONASS F2
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF2GLONASS_clicked(){
    UiAntenna->radioButtonAPCReadF2GLONASS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF2GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF2GLONASS->setChecked(false);
    UiAntenna->frameAPCF2GLONASSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF2GLONASS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF2GLONASS_clicked(){
    UiAntenna->radioButtonAPCSpecifyF2GLONASS->setChecked(true);
    UiAntenna->radioButtonAPCReadF2GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF2GLONASS->setChecked(false);
    UiAntenna->frameAPCF2GLONASSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF2GLONASS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF2GLONASS_clicked(){
    UiAntenna->radioButtonAPCSpecifyF2GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCReadF2GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF2GLONASS->setChecked(true);
    UiAntenna->frameAPCF2GLONASS->setHidden(true);
    UiAntenna->frameAPCF2GLONASSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsGLONASSF2Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsGLONASSF2->setCurrentIndex(index);
}
//GLONASS F3
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF3GLONASS_clicked(){
    UiAntenna->radioButtonAPCReadF3GLONASS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF3GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF3GLONASS->setChecked(false);
    UiAntenna->frameAPCF3GLONASSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF3GLONASS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF3GLONASS_clicked(){
    UiAntenna->radioButtonAPCSpecifyF3GLONASS->setChecked(true);
    UiAntenna->radioButtonAPCReadF3GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF3GLONASS->setChecked(false);
    UiAntenna->frameAPCF3GLONASSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF3GLONASS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF3GLONASS_clicked(){
    UiAntenna->radioButtonAPCSpecifyF3GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCReadF3GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF3GLONASS->setChecked(true);
    UiAntenna->frameAPCF3GLONASS->setHidden(true);
    UiAntenna->frameAPCF3GLONASSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsGLONASSF3Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsGLONASSF3->setCurrentIndex(index);
}
//GLONASS F4
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF4GLONASS_clicked(){
    UiAntenna->radioButtonAPCReadF4GLONASS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF4GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF4GLONASS->setChecked(false);
    UiAntenna->frameAPCF4GLONASSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF4GLONASS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF4GLONASS_clicked(){
    UiAntenna->radioButtonAPCSpecifyF4GLONASS->setChecked(true);
    UiAntenna->radioButtonAPCReadF4GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF4GLONASS->setChecked(false);
    UiAntenna->frameAPCF4GLONASSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF4GLONASS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF4GLONASS_clicked(){
    UiAntenna->radioButtonAPCSpecifyF4GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCReadF4GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF4GLONASS->setChecked(true);
    UiAntenna->frameAPCF4GLONASS->setHidden(true);
    UiAntenna->frameAPCF4GLONASSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsGLONASSF4Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsGLONASSF4->setCurrentIndex(index);
}
//GLONASS F6
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF6GLONASS_clicked(){
    UiAntenna->radioButtonAPCReadF6GLONASS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF6GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF6GLONASS->setChecked(false);
    UiAntenna->frameAPCF6GLONASSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF6GLONASS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF6GLONASS_clicked(){
    UiAntenna->radioButtonAPCSpecifyF6GLONASS->setChecked(true);
    UiAntenna->radioButtonAPCReadF6GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF6GLONASS->setChecked(false);
    UiAntenna->frameAPCF6GLONASSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF6GLONASS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF6GLONASS_clicked(){
    UiAntenna->radioButtonAPCSpecifyF6GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCReadF6GLONASS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF6GLONASS->setChecked(true);
    UiAntenna->frameAPCF6GLONASS->setHidden(true);
    UiAntenna->frameAPCF6GLONASSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsGLONASSF6Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsGLONASSF6->setCurrentIndex(index);
}
//GEO
//Function to set GEO Default
void GNSS_Antenna_Advanced::SetDefaultAPCGEO(){
    this->on_radioButtonAPCReadF1GEO_clicked();
    this->on_radioButtonAPCReadF5GEO_clicked();

    this->on_comboBoxAPCSameAsGEOF1Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsGEOF5Const_currentIndexChanged(0);
    for (int i=0; i<nFreqGNSS[GEO]; i++){
        for (int j=0; j<3; j++){
            LineEditGNSSNEU[GEO][i][j]->setText("0");
        }
        ComboBoxAPCSameAsConst[GEO][i]->setCurrentIndex(0);
        for (int j=0; j<MAX_GNSS; j++){
            ComboBoxAPCSameAsFreq[GEO][i][j]->setCurrentIndex(0);
        }
    }
}
//GEO F1
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF1GEO_clicked(){
    UiAntenna->radioButtonAPCReadF1GEO->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF1GEO->setChecked(false);
    UiAntenna->radioButtonAPCCopyF1GEO->setChecked(false);
    UiAntenna->frameAPCF1GEOCopyFrom->setHidden(true);
    UiAntenna->frameAPCF1GEO->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF1GEO_clicked(){
    UiAntenna->radioButtonAPCReadF1GEO->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF1GEO->setChecked(true);
    UiAntenna->radioButtonAPCCopyF1GEO->setChecked(false);
    UiAntenna->frameAPCF1GEOCopyFrom->setHidden(true);
    UiAntenna->frameAPCF1GEO->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF1GEO_clicked(){
    UiAntenna->radioButtonAPCSpecifyF1GEO->setChecked(false);
    UiAntenna->radioButtonAPCReadF1GEO->setChecked(false);
    UiAntenna->radioButtonAPCCopyF1GEO->setChecked(true);
    UiAntenna->frameAPCF1GEO->setHidden(true);
    UiAntenna->frameAPCF1GEOCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsGEOF1Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsGEOF1->setCurrentIndex(index);
}
//GEO F5
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF5GEO_clicked(){
    UiAntenna->radioButtonAPCReadF5GEO->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF5GEO->setChecked(false);
    UiAntenna->radioButtonAPCCopyF5GEO->setChecked(false);
    UiAntenna->frameAPCF5GEOCopyFrom->setHidden(true);
    UiAntenna->frameAPCF5GEO->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF5GEO_clicked(){
    UiAntenna->radioButtonAPCReadF5GEO->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF5GEO->setChecked(true);
    UiAntenna->radioButtonAPCCopyF5GEO->setChecked(false);
    UiAntenna->frameAPCF5GEOCopyFrom->setHidden(true);
    UiAntenna->frameAPCF5GEO->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF5GEO_clicked(){
    UiAntenna->radioButtonAPCReadF5GEO->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF5GEO->setChecked(false);
    UiAntenna->radioButtonAPCCopyF5GEO->setChecked(true);
    UiAntenna->frameAPCF5GEO->setHidden(true);
    UiAntenna->frameAPCF5GEOCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsGEOF5Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsGEOF5->setCurrentIndex(index);
}

//BDS
//Function to set BDS Default
void GNSS_Antenna_Advanced::SetDefaultAPCBDS(){
    this->on_radioButtonAPCReadF1BDS_clicked();
    this->on_radioButtonAPCReadF2BDS_clicked();
    this->on_radioButtonAPCReadF5BDS_clicked();
    this->on_radioButtonAPCReadF6BDS_clicked();
    this->on_radioButtonAPCReadF7BDS_clicked();
    this->on_radioButtonAPCReadF8BDS_clicked();

    this->on_comboBoxAPCSameAsBDSF1Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsBDSF2Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsBDSF5Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsBDSF6Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsBDSF7Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsBDSF8Const_currentIndexChanged(0);
    for (int i=0; i<nFreqGNSS[BDS]; i++){
        for (int j=0; j<3; j++){
            LineEditGNSSNEU[BDS][i][j]->setText("0");
        }
        ComboBoxAPCSameAsConst[BDS][i]->setCurrentIndex(0);
        for (int j=0; j<MAX_GNSS; j++){
            ComboBoxAPCSameAsFreq[BDS][i][j]->setCurrentIndex(0);
        }
    }
}
//BDS F1
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF1BDS_clicked(){
    UiAntenna->radioButtonAPCReadF1BDS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF1BDS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF1BDS->setChecked(false);
    UiAntenna->frameAPCF1BDSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF1BDS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF1BDS_clicked(){
    UiAntenna->radioButtonAPCReadF1BDS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF1BDS->setChecked(true);
    UiAntenna->radioButtonAPCCopyF1BDS->setChecked(false);
    UiAntenna->frameAPCF1BDSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF1BDS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF1BDS_clicked(){
    UiAntenna->radioButtonAPCSpecifyF1BDS->setChecked(false);
    UiAntenna->radioButtonAPCReadF1BDS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF1BDS->setChecked(true);
    UiAntenna->frameAPCF1BDS->setHidden(true);
    UiAntenna->frameAPCF1BDSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsBDSF1Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsBDSF1->setCurrentIndex(index);
}
//BDS F2
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF2BDS_clicked(){
    UiAntenna->radioButtonAPCReadF2BDS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF2BDS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF2BDS->setChecked(false);
    UiAntenna->frameAPCF2BDSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF2BDS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF2BDS_clicked(){
    UiAntenna->radioButtonAPCReadF2BDS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF2BDS->setChecked(true);
    UiAntenna->radioButtonAPCCopyF2BDS->setChecked(false);
    UiAntenna->frameAPCF2BDSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF2BDS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF2BDS_clicked(){
    UiAntenna->radioButtonAPCReadF2BDS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF2BDS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF2BDS->setChecked(true);
    UiAntenna->frameAPCF2BDS->setHidden(true);
    UiAntenna->frameAPCF2BDSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsBDSF2Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsBDSF2->setCurrentIndex(index);
}
//BDS F5
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF5BDS_clicked(){
    UiAntenna->radioButtonAPCReadF5BDS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF5BDS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF5BDS->setChecked(false);
    UiAntenna->frameAPCF5BDSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF5BDS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF5BDS_clicked(){
    UiAntenna->radioButtonAPCReadF5BDS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF5BDS->setChecked(true);
    UiAntenna->radioButtonAPCCopyF5BDS->setChecked(false);
    UiAntenna->frameAPCF5BDSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF5BDS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF5BDS_clicked(){
    UiAntenna->radioButtonAPCReadF5BDS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF5BDS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF5BDS->setChecked(true);
    UiAntenna->frameAPCF5BDS->setHidden(true);
    UiAntenna->frameAPCF5BDSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsBDSF5Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsBDSF5->setCurrentIndex(index);
}
//BDS F6
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF6BDS_clicked(){
    UiAntenna->radioButtonAPCReadF6BDS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF6BDS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF6BDS->setChecked(false);
    UiAntenna->frameAPCF6BDSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF6BDS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF6BDS_clicked(){
    UiAntenna->radioButtonAPCReadF6BDS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF6BDS->setChecked(true);
    UiAntenna->radioButtonAPCCopyF6BDS->setChecked(false);
    UiAntenna->frameAPCF6BDSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF6BDS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF6BDS_clicked(){
    UiAntenna->radioButtonAPCReadF6BDS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF6BDS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF6BDS->setChecked(true);
    UiAntenna->frameAPCF6BDS->setHidden(true);
    UiAntenna->frameAPCF6BDSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsBDSF6Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsBDSF6->setCurrentIndex(index);
}
//BDS F7
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF7BDS_clicked(){
    UiAntenna->radioButtonAPCReadF7BDS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF7BDS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF7BDS->setChecked(false);
    UiAntenna->frameAPCF7BDSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF7BDS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF7BDS_clicked(){
    UiAntenna->radioButtonAPCReadF7BDS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF7BDS->setChecked(true);
    UiAntenna->radioButtonAPCCopyF7BDS->setChecked(false);
    UiAntenna->frameAPCF7BDSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF7BDS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF7BDS_clicked(){
    UiAntenna->radioButtonAPCReadF7BDS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF7BDS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF7BDS->setChecked(true);
    UiAntenna->frameAPCF7BDS->setHidden(true);
    UiAntenna->frameAPCF7BDSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsBDSF7Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsBDSF7->setCurrentIndex(index);
}
//BDS F8
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF8BDS_clicked(){
    UiAntenna->radioButtonAPCReadF8BDS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF8BDS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF8BDS->setChecked(false);
    UiAntenna->frameAPCF8BDSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF8BDS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF8BDS_clicked(){
    UiAntenna->radioButtonAPCReadF8BDS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF8BDS->setChecked(true);
    UiAntenna->radioButtonAPCCopyF8BDS->setChecked(false);
    UiAntenna->frameAPCF8BDSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF8BDS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF8BDS_clicked(){
    UiAntenna->radioButtonAPCReadF8BDS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF8BDS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF8BDS->setChecked(true);
    UiAntenna->frameAPCF8BDS->setHidden(true);
    UiAntenna->frameAPCF8BDSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsBDSF8Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsBDSF8->setCurrentIndex(index);
}
//QZSS
//Function to set QZSS Default
void GNSS_Antenna_Advanced::SetDefaultAPCQZSS(){
    this->on_radioButtonAPCReadF1QZSS_clicked();
    this->on_radioButtonAPCReadF2QZSS_clicked();
    this->on_radioButtonAPCReadF5QZSS_clicked();
    this->on_radioButtonAPCReadF6QZSS_clicked();

    this->on_comboBoxAPCSameAsQZSSF1Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsQZSSF2Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsQZSSF5Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsQZSSF6Const_currentIndexChanged(0);

    for (int i=0; i<nFreqGNSS[QZSS]; i++){
        for (int j=0; j<3; j++){
            LineEditGNSSNEU[QZSS][i][j]->setText("0");
        }
        ComboBoxAPCSameAsConst[QZSS][i]->setCurrentIndex(0);
        for (int j=0; j<MAX_GNSS; j++){
            ComboBoxAPCSameAsFreq[QZSS][i][j]->setCurrentIndex(0);
        }
    }
}
//QZSS F1
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF1QZSS_clicked(){
    UiAntenna->radioButtonAPCReadF1QZSS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF1QZSS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF1QZSS->setChecked(false);
    UiAntenna->frameAPCF1QZSSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF1QZSS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF1QZSS_clicked(){
    UiAntenna->radioButtonAPCReadF1QZSS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF1QZSS->setChecked(true);
    UiAntenna->radioButtonAPCCopyF1QZSS->setChecked(false);
    UiAntenna->frameAPCF1QZSSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF1QZSS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF1QZSS_clicked(){
    UiAntenna->radioButtonAPCReadF1QZSS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF1QZSS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF1QZSS->setChecked(true);
    UiAntenna->frameAPCF1QZSS->setHidden(true);
    UiAntenna->frameAPCF1QZSSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsQZSSF1Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsQZSSF1->setCurrentIndex(index);
}
//QZSS F2
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF2QZSS_clicked(){
    UiAntenna->radioButtonAPCReadF2QZSS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF2QZSS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF2QZSS->setChecked(false);
    UiAntenna->frameAPCF2QZSSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF2QZSS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF2QZSS_clicked(){
    UiAntenna->radioButtonAPCReadF2QZSS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF2QZSS->setChecked(true);
    UiAntenna->radioButtonAPCCopyF2QZSS->setChecked(false);
    UiAntenna->frameAPCF2QZSSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF2QZSS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF2QZSS_clicked(){
    UiAntenna->radioButtonAPCReadF2QZSS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF2QZSS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF2QZSS->setChecked(true);
    UiAntenna->frameAPCF2QZSS->setHidden(true);
    UiAntenna->frameAPCF2QZSSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsQZSSF2Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsQZSSF2->setCurrentIndex(index);
}
//QZSS F5
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF5QZSS_clicked(){
    UiAntenna->radioButtonAPCReadF5QZSS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF5QZSS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF5QZSS->setChecked(false);
    UiAntenna->frameAPCF5QZSSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF5QZSS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF5QZSS_clicked(){
    UiAntenna->radioButtonAPCReadF5QZSS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF5QZSS->setChecked(true);
    UiAntenna->radioButtonAPCCopyF5QZSS->setChecked(false);
    UiAntenna->frameAPCF5QZSSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF5QZSS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF5QZSS_clicked(){
    UiAntenna->radioButtonAPCReadF5QZSS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF5QZSS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF5QZSS->setChecked(true);
    UiAntenna->frameAPCF5QZSS->setHidden(true);
    UiAntenna->frameAPCF5QZSSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsQZSSF5Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsQZSSF5->setCurrentIndex(index);
}
//QZSS F6
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF6QZSS_clicked(){
    UiAntenna->radioButtonAPCReadF6QZSS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF6QZSS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF6QZSS->setChecked(false);
    UiAntenna->frameAPCF6QZSSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF6QZSS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF6QZSS_clicked(){
    UiAntenna->radioButtonAPCReadF6QZSS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF6QZSS->setChecked(true);
    UiAntenna->radioButtonAPCCopyF6QZSS->setChecked(false);
    UiAntenna->frameAPCF6QZSSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF6QZSS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF6QZSS_clicked(){
    UiAntenna->radioButtonAPCReadF6QZSS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF6QZSS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF6QZSS->setChecked(true);
    UiAntenna->frameAPCF6QZSS->setHidden(true);
    UiAntenna->frameAPCF6QZSSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsQZSSF6Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsQZSSF6->setCurrentIndex(index);
}
//IRNSS
//Function to set IRNSS Default
void GNSS_Antenna_Advanced::SetDefaultAPCIRNSS(){
    this->on_radioButtonAPCReadF5IRNSS_clicked();
    this->on_radioButtonAPCReadF9IRNSS_clicked();

    this->on_comboBoxAPCSameAsIRNSSF5Const_currentIndexChanged(0);
    this->on_comboBoxAPCSameAsIRNSSF9Const_currentIndexChanged(0);
    for (int i=0; i<nFreqGNSS[IRNSS]; i++){
        for (int j=0; j<3; j++){
            LineEditGNSSNEU[IRNSS][i][j]->setText("0");
        }
        ComboBoxAPCSameAsConst[IRNSS][i]->setCurrentIndex(0);
        for (int j=0; j<MAX_GNSS; j++){
            ComboBoxAPCSameAsFreq[IRNSS][i][j]->setCurrentIndex(0);
        }
    }
}
//IRNSS F5
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF5IRNSS_clicked(){
    UiAntenna->radioButtonAPCReadF5IRNSS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF5IRNSS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF5IRNSS->setChecked(false);
    UiAntenna->frameAPCF5IRNSSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF5IRNSS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF5IRNSS_clicked(){
    UiAntenna->radioButtonAPCReadF5IRNSS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF5IRNSS->setChecked(true);
    UiAntenna->radioButtonAPCCopyF5IRNSS->setChecked(false);
    UiAntenna->frameAPCF5IRNSSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF5IRNSS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF5IRNSS_clicked(){
    UiAntenna->radioButtonAPCReadF5IRNSS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF5IRNSS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF5IRNSS->setChecked(true);
    UiAntenna->frameAPCF5IRNSS->setHidden(true);
    UiAntenna->frameAPCF5IRNSSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsIRNSSF5Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsIRNSSF5->setCurrentIndex(index);
}
//IRNSS F9
void GNSS_Antenna_Advanced::on_radioButtonAPCReadF9IRNSS_clicked(){
    UiAntenna->radioButtonAPCReadF9IRNSS->setChecked(true);
    UiAntenna->radioButtonAPCSpecifyF9IRNSS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF9IRNSS->setChecked(false);
    UiAntenna->frameAPCF9IRNSSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF9IRNSS->setHidden(true);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCSpecifyF9IRNSS_clicked(){
    UiAntenna->radioButtonAPCReadF9IRNSS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF9IRNSS->setChecked(true);
    UiAntenna->radioButtonAPCCopyF9IRNSS->setChecked(false);
    UiAntenna->frameAPCF9IRNSSCopyFrom->setHidden(true);
    UiAntenna->frameAPCF9IRNSS->setHidden(false);
}
void GNSS_Antenna_Advanced::on_radioButtonAPCCopyF9IRNSS_clicked(){
    UiAntenna->radioButtonAPCReadF9IRNSS->setChecked(false);
    UiAntenna->radioButtonAPCSpecifyF9IRNSS->setChecked(false);
    UiAntenna->radioButtonAPCCopyF9IRNSS->setChecked(true);
    UiAntenna->frameAPCF9IRNSS->setHidden(true);
    UiAntenna->frameAPCF9IRNSSCopyFrom->setHidden(false);
}
void GNSS_Antenna_Advanced::on_comboBoxAPCSameAsIRNSSF9Const_currentIndexChanged(int index) {
    UiAntenna->stackedWidgetAPCSameAsIRNSSF9->setCurrentIndex(index);
}

// Function to configure GPS satellites
void GNSS_Antenna_Advanced::on_pushButtonGPS_clicked(){
    UiAntenna->stackedWidgetAPCGNSS->setCurrentIndex(GPS);
    UiAntenna->labelSelectPRNFor->setText("GPS:");
    UiAntenna->pushButtonGalileo->setChecked(false);
    UiAntenna->pushButtonGLONASS->setChecked(false);
    UiAntenna->pushButtonGEO->setChecked(false);
    UiAntenna->pushButtonBDS->setChecked(false);
    UiAntenna->pushButtonQZSS->setChecked(false);
    UiAntenna->pushButtonIRNSS->setChecked(false);
    UiAntenna->pushButtonGPS->setChecked(true);
}
// Function to configure Galileo satellites
void GNSS_Antenna_Advanced::on_pushButtonGalileo_clicked(){
    UiAntenna->stackedWidgetAPCGNSS->setCurrentIndex(Galileo);
    UiAntenna->labelSelectPRNFor->setText("Galileo:");
    UiAntenna->pushButtonGPS->setChecked(false);
    UiAntenna->pushButtonGLONASS->setChecked(false);
    UiAntenna->pushButtonGEO->setChecked(false);
    UiAntenna->pushButtonBDS->setChecked(false);
    UiAntenna->pushButtonQZSS->setChecked(false);
    UiAntenna->pushButtonIRNSS->setChecked(false);
    UiAntenna->pushButtonGalileo->setChecked(true);
}
// Function to configure GLONASS satellites
void GNSS_Antenna_Advanced::on_pushButtonGLONASS_clicked(){
    UiAntenna->stackedWidgetAPCGNSS->setCurrentIndex(GLONASS);
    UiAntenna->labelSelectPRNFor->setText("GLONASS:");
    UiAntenna->pushButtonGPS->setChecked(false);
    UiAntenna->pushButtonGalileo->setChecked(false);
    UiAntenna->pushButtonGEO->setChecked(false);
    UiAntenna->pushButtonBDS->setChecked(false);
    UiAntenna->pushButtonQZSS->setChecked(false);
    UiAntenna->pushButtonIRNSS->setChecked(false);
    UiAntenna->pushButtonGLONASS->setChecked(true);
}
// Function to configure GEO satellites
void GNSS_Antenna_Advanced::on_pushButtonGEO_clicked(){
    UiAntenna->stackedWidgetAPCGNSS->setCurrentIndex(GEO);
    UiAntenna->labelSelectPRNFor->setText("GEO:");
    UiAntenna->pushButtonGPS->setChecked(false);
    UiAntenna->pushButtonGalileo->setChecked(false);
    UiAntenna->pushButtonGLONASS->setChecked(false);
    UiAntenna->pushButtonBDS->setChecked(false);
    UiAntenna->pushButtonQZSS->setChecked(false);
    UiAntenna->pushButtonIRNSS->setChecked(false);
    UiAntenna->pushButtonGEO->setChecked(true);
}
// Function to configure BDS satellites
void GNSS_Antenna_Advanced::on_pushButtonBDS_clicked(){
    UiAntenna->stackedWidgetAPCGNSS->setCurrentIndex(BDS);
    UiAntenna->labelSelectPRNFor->setText("BDS:");
    UiAntenna->pushButtonGPS->setChecked(false);
    UiAntenna->pushButtonGalileo->setChecked(false);
    UiAntenna->pushButtonGLONASS->setChecked(false);
    UiAntenna->pushButtonGEO->setChecked(false);
    UiAntenna->pushButtonQZSS->setChecked(false);
    UiAntenna->pushButtonIRNSS->setChecked(false);
    UiAntenna->pushButtonBDS->setChecked(true);
}
// Function to configure QZSS satellites
void GNSS_Antenna_Advanced::on_pushButtonQZSS_clicked(){
    UiAntenna->stackedWidgetAPCGNSS->setCurrentIndex(QZSS);
    UiAntenna->labelSelectPRNFor->setText("QZSS:");
    UiAntenna->pushButtonGPS->setChecked(false);
    UiAntenna->pushButtonGalileo->setChecked(false);
    UiAntenna->pushButtonGLONASS->setChecked(false);
    UiAntenna->pushButtonGEO->setChecked(false);
    UiAntenna->pushButtonBDS->setChecked(false);
    UiAntenna->pushButtonIRNSS->setChecked(false);
    UiAntenna->pushButtonQZSS->setChecked(true);
}
// Function to configure IRNSS satellites
void GNSS_Antenna_Advanced::on_pushButtonIRNSS_clicked(){
    UiAntenna->stackedWidgetAPCGNSS->setCurrentIndex(IRNSS);
    UiAntenna->labelSelectPRNFor->setText("IRNSS:");
    UiAntenna->pushButtonGPS->setChecked(false);
    UiAntenna->pushButtonGalileo->setChecked(false);
    UiAntenna->pushButtonGLONASS->setChecked(false);
    UiAntenna->pushButtonGEO->setChecked(false);
    UiAntenna->pushButtonBDS->setChecked(false);
    UiAntenna->pushButtonQZSS->setChecked(false);
    UiAntenna->pushButtonIRNSS->setChecked(true);
}
// Function to select GPS satellites
void GNSS_Antenna_Advanced::changePushButtonGPS(bool checked){
    UiAntenna->pushButtonGPS->setEnabled(checked);
    this->SetDefaultAPCGPS();
}
// Function to select Galileo satellites
void GNSS_Antenna_Advanced::changePushButtonGalileo(bool checked){
    UiAntenna->pushButtonGalileo->setEnabled(checked);
    this->SetDefaultAPCGalileo();
}
// Function to select GLONASS satellites
void GNSS_Antenna_Advanced::changePushButtonGLONASS(bool checked){
    UiAntenna->pushButtonGLONASS->setEnabled(checked);
    this->SetDefaultAPCGLONASS();
}
// Function to select GEO satellites
void GNSS_Antenna_Advanced::changePushButtonGEO(bool checked){
    UiAntenna->pushButtonGEO->setEnabled(checked);
    this->SetDefaultAPCGEO();
}
// Function to select BDS satellites
void GNSS_Antenna_Advanced::changePushButtonBDS(bool checked){
    UiAntenna->pushButtonBDS->setEnabled(checked);
    this->SetDefaultAPCBDS();
}
// Function to select QZSS satellites
void GNSS_Antenna_Advanced::changePushButtonQZSS(bool checked){
    UiAntenna->pushButtonQZSS->setEnabled(checked);
    this->SetDefaultAPCQZSS();
}
// Function to select IRNSS satellites
void GNSS_Antenna_Advanced::changePushButtonIRNSS(bool checked){
    UiAntenna->pushButtonIRNSS->setEnabled(checked);
    this->SetDefaultAPCIRNSS();
}

// Function to configure GPS satellites
void GNSS_Antenna_Advanced::on_pushButtonPublicGPS_clicked(){
    this->on_pushButtonGPS_clicked();
}
// Function to configure Galileo satellites
void GNSS_Antenna_Advanced::on_pushButtonPublicGalileo_clicked(){
    this->on_pushButtonGalileo_clicked();
}
// Function to configure GLONASS satellites
void GNSS_Antenna_Advanced::on_pushButtonPublicGLONASS_clicked(){
    this->on_pushButtonGLONASS_clicked();
}
// Function to configure GEO satellites
void GNSS_Antenna_Advanced::on_pushButtonPublicGEO_clicked(){
    this->on_pushButtonGEO_clicked();
}
// Function to configure BDS satellites
void GNSS_Antenna_Advanced::on_pushButtonPublicBDS_clicked(){
    this->on_pushButtonBDS_clicked();
}
// Function to configure QZSS satellites
void GNSS_Antenna_Advanced::on_pushButtonPublicQZSS_clicked(){
    this->on_pushButtonQZSS_clicked();
}
// Function to configure IRNSS satellites
void GNSS_Antenna_Advanced::on_pushButtonPublicIRNSS_clicked(){
    this->on_pushButtonIRNSS_clicked();
}

void GNSS_Antenna_Advanced::changeCurrentPage(){
    for (int i=0; i<MAX_GNSS; i++){
        if (PushButtonGNSS[i]->isEnabled()){
            (this->*PushButtonGNSSFunctions[i])();
            break;
        }
    }
}

//Function to get APC command options
void GNSS_Antenna_Advanced::getgLABOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString) {
    QString APCoptionsSpecify="";
    QString APCoptionsCopy="";
    int     GNSSCopyFrom,FreqCopyFrom,FreqCopyFromIndex;
    if (warningString->length()<0) *warningString=""; //only to avoid the warning of unused "warningString"
    //loop of constellations
    for (int gnssi=0; gnssi<MAX_GNSS; gnssi++){
        //Loop of frequencies
        if (!PushButtonGNSS[gnssi]->isEnabled()) continue; //Skip unselected frequencies
        for (int freqi=0; freqi<nFreqGNSS[gnssi]; freqi++){
            if (RadioGNSSSpecify[gnssi][freqi]->isChecked()){
                if ( LineEditGNSSNEU[gnssi][freqi][0]->text() == "" || LineEditGNSSNEU[gnssi][freqi][1]->text() == "" || LineEditGNSSNEU[gnssi][freqi][2]->text() == ""){
                    *errorString += "MODEL: Receiver Antenna Phase Centre Offset of " + GNSSName[gnssi] + " F" + FreqGNSSList[gnssi][freqi] + " cannot be empty.\n";
                } else {
                    APCoptionsSpecify += " " + indentifierGNSS[gnssi] + FreqGNSSList[gnssi][freqi] + " " + LineEditGNSSNEU[gnssi][freqi][0]->text()
                            + " " + LineEditGNSSNEU[gnssi][freqi][1]->text() + " " + LineEditGNSSNEU[gnssi][freqi][2]->text();
                }
            } else if (RadioGNSSCopyFrom[gnssi][freqi]->isChecked()){
                GNSSCopyFrom=ComboBoxAPCSameAsConst[gnssi][freqi]->currentIndex();
                FreqCopyFrom=ComboBoxAPCSameAsFreq[gnssi][freqi][GNSSCopyFrom]->currentText().mid(1,1).toInt();
                FreqCopyFromIndex=FreqNumToIndex[GNSSCopyFrom][FreqCopyFrom];
                if (RadioGNSSCopyFrom[GNSSCopyFrom][FreqCopyFromIndex]->isChecked()){
                    *errorString += "MODEL: Receiver Antenna Phase Centre Offset of " + GNSSName[gnssi] + " F" + FreqGNSSList[gnssi][freqi] + " is set to be copied from " +
                            GNSSName[GNSSCopyFrom] + " F" + QString::number(FreqCopyFrom) + ", but that frequency is also set to be copied.\n";
                } else {
                    APCoptionsCopy += " " + indentifierGNSS[gnssi] + FreqGNSSList[gnssi][freqi] + " " + indentifierGNSS[GNSSCopyFrom] + QString::number(FreqCopyFrom);
                }

            }
        }
    }
    //-model:recphasecenter
    if (APCoptionsSpecify.length()==0 && APCoptionsCopy.length()==0) {
        *saveString += "-model:recphasecenter ANTEX\n";
        *runString << "-model:recphasecenter" << "ANTEX";
    } else {
        if (APCoptionsSpecify.length()>1){
            APCoptionsSpecify = "-model:recphasecenter" + APCoptionsSpecify;
            *saveString += APCoptionsSpecify + "\n";
            QStringList tmpString = APCoptionsSpecify.split(QRegularExpression("\\s+"));
            for(int k=0;k<tmpString.size();k++) {
                *runString << tmpString[k];
            }
        }
        if (APCoptionsCopy.length()>1){
            APCoptionsCopy = "-model:recphasecenter" + APCoptionsCopy;
            *saveString += APCoptionsCopy + "\n";
            QStringList tmpString = APCoptionsCopy.split(QRegularExpression("\\s+"));
            for(int k=0;k<tmpString.size();k++) {
                *runString << tmpString[k];
            }
        }
    }

}
//Function to convert SF command options to GUI configuration
void GNSS_Antenna_Advanced::loadgLABOptions(QString *warningString, QStringList *ParametersList){
    int i,j,k,l=0;
    int aux1,aux2,aux3,aux4,aux5;
    int GNSSused[MAX_GNSS];
    int freqUsed[MAX_GNSS_FREQ_SLOTS];
    QString auxstr;
    //check if the parameter number is correct = n*4
    if (ParametersList->count()%4!=0 && ParametersList->count()%2!=0 ){
        *warningString += "MODEL: Parameter '-model:recphasecenter' has missing values. It was skipped.\n";
        return;
    }


    while(l<ParametersList->count()) {
        if ((ParametersList->count()-l)<2) {
            *warningString += "MODEL: Parameter '-model:recphasecenter' requires at least two arguments per each set of user manually sets receiver phase center values, but last set only has one argument left. It was skipped.\n";
            return;
        }
        for(i=0;i<MAX_GNSS;i++) {
            GNSSused[i]=0;
        }
        for(i=0;i<MAX_GNSS_FREQ_SLOTS;i++) {
            freqUsed[i]=0;
        }
        if (QString::compare(ParametersList->at(l),"0", Qt::CaseInsensitive)==0) {
            //Select all constellations and frequencies
            for(i=0;i<MAX_GNSS;i++) {
                GNSSused[i]=1;
            }
            for(i=0;i<MAX_GNSS_FREQ_SLOTS;i++) {
                freqUsed[i]=1;
            }
        } else {
            aux1=0;
            aux2=ParametersList->at(l).size();
            if(aux2<2) {
                //Missing frequencies
                *warningString += "MODEL: Missing frequencies in argument '" + ParametersList->at(l) + "' for parameter '-model:recphasecenter'. It was skipped.\n";
                return;
            }
            while(checkConstellationQChar(ParametersList->at(l).at(aux1))==1) {
                i=static_cast<int>(gnssQchar2gnsstype(ParametersList->at(l).at(aux1)));
                GNSSused[i]=1;
                aux1++;
            }

            if(aux1==0) {
                //If no constellation provided, default for GPS as in previous versions
                GNSSused[GPS]=1;
            }
            if(aux2<=aux1) {
                //Missing frequencies
                *warningString += "MODEL: Missing frequencies in argument '" + ParametersList->at(l) + "' for parameter '-model:recphasecenter'. It was skipped.\n";
                return;
            }
            for(i=aux1;i<aux2;i++) {
                if (ParametersList->at(l).at(i).isDigit()==false) {
                    *warningString += "MODEL: Frequency '" + ParametersList->at(l).mid(i,1) + "' in argument '" + ParametersList->at(l) + "' for parameter '-model:recphasecenter' is not a valid frequency. It was skipped.\n";
                    return;
                }
                freqUsed[ParametersList->at(l).mid(i,1).toInt()]=1;
            }
        }
        if (checkConstellationQChar(ParametersList->at(l+1).at(0))==1) {
            //Current combination of constellations and frequencies to be gathered from the given constellation.
            //If no frequency is provided, it will match the each source frequency with the destination frequency (e.g. QZS F1 and F2 will be matched to GPS F1 and F2)
            //To save the destination frequency and pointer, the value used will be the constellation
            aux1=static_cast<int>(gnssQchar2gnsstype(ParametersList->at(l+1).at(0)));
            aux2=ParametersList->at(l+1).size();
            if (aux2==1) {
                //No frequencies provided
                for(i=0;i<MAX_GNSS;i++) {
                    if(GNSSused[i]==0) continue;
                    for(j=0;j<MAX_GNSS_FREQ_SLOTS;j++) {
                        if(freqUsed[j]==0) continue;
                        if (availGNSSFreq[i][j]==0) continue; //Skip non existing frequencies in the destination constellation
                        if (availGNSSFreq[aux1][j]==0) continue; //Skip non existing frequencies in source constellation to copy from
                        //Check that the destination constellation and frequency does not point to the source constellation and frequency (to avoid a loop of each one correcting to each other)
                        aux4=FreqNumToIndex[aux1][j]; //Index of frequency where to copy data from
                        aux5=FreqNumToIndex[i][j]; //Index of frequency where data will be copied
                        if (RadioGNSSCopyFrom[aux1][aux4]->isChecked()==true) {
                            if (ComboBoxAPCSameAsConst[aux1][aux4]->currentIndex()==i && ComboBoxAPCSameAsFreq[aux1][aux4][aux1]->currentText().mid(1,1).toInt()==j) {
                                *warningString += "MODEL: Argument '" + ParametersList->at(l+1) + "' for parameter '-model:recphasecenter' is pointing to a destination constellation whose correction is pointing to the source constellation in argument '" + ParametersList->at(l) + "'. It was skipped.\n";
                                return;
                            } else  {
                                *warningString += "MODEL: Argument '" + ParametersList->at(l+1) + "' for parameter '-model:recphasecenter' is pointing to a destination constellation whose correction is also set to be copied in argument '" + ParametersList->at(l) + "'. It was skipped.\n";
                                return;
                            }
                        }
                        RadioGNSSCopyFrom[i][aux5]->clicked();
                        ComboBoxAPCSameAsConst[i][aux5]->setCurrentIndex(aux1);
                        //Look for the index for the destination frequency. As if source and destination constellation are the same, the number of frequencies will be one less
                        //as you cannot copy the data to itself
                        for(k=0;k<ComboBoxAPCSameAsFreq[i][aux5][aux1]->count();k++) {
                            if (ComboBoxAPCSameAsFreq[i][aux5][aux1]->itemText(k).mid(1,1).toInt()==j) {
                                ComboBoxAPCSameAsFreq[i][aux5][aux1]->setCurrentIndex(k);
                                break;
                            }
                        }
                    }
                }
            } else {
                //Frequency provided
                if (aux2>2) {
                    *warningString += "MODEL: Argument '" + ParametersList->at(l+1) + "' for parameter '-model:recphasecenter' can not contain more than one frequency or constellation when specifying the source. It was skipped.\n";
                    return;
                }
                if (checkConstellationQChar(ParametersList->at(l+1).at(1))==1) {
                    *warningString += "MODEL: Argument '" + ParametersList->at(l+1) + "' for parameter '-model:recphasecenter' can not contain more than one constellation when specifying the constellation to use as a source. It was skipped.\n";
                    return;
                }
                if (ParametersList->at(l+1).at(1).isDigit()==false) {
                    *warningString += "MODEL: Frequency '" + ParametersList->at(l+1).mid(1,1) + "' in argument '" + ParametersList->at(l+1) + "' for parameter '-model:recphasecenter' is not a valid frequency. It was skipped.\n";
                    return;
                }
                aux3=ParametersList->at(l+1).mid(1,1).toInt();
                for(i=0;i<MAX_GNSS;i++) {
                    if(GNSSused[i]==0) continue;
                    for(j=0;j<MAX_GNSS_FREQ_SLOTS;j++) {
                        if(freqUsed[j]==0) continue;
                        if (availGNSSFreq[i][j]==0) continue; //Skip non existing frequencies in the destination constellation
                        if (availGNSSFreq[aux1][aux3]==0) continue; //Skip non existing frequencies in source constellation to copy from
                        //Check that the destination constellation and frequency does not point to the source constellation and frequency (to avoid a loop of each one correcting to each other)
                        aux4=FreqNumToIndex[aux1][aux3]; //Index of frequency where to copy data from
                        aux5=FreqNumToIndex[i][j]; //Index of frequency where data will be copied
                        if (RadioGNSSCopyFrom[aux1][aux4]->isChecked()==true) {
                            if (ComboBoxAPCSameAsConst[aux1][aux4]->currentIndex()==i && ComboBoxAPCSameAsFreq[aux1][aux4][aux1]->currentText().mid(1,1).toInt()==aux3) {
                                *warningString += "MODEL: Argument '" + ParametersList->at(l+1) + "' for parameter '-model:recphasecenter' is pointing to a destination constellation whose correction is pointing to the source constellation in argument '" + ParametersList->at(l) + "'. It was skipped.\n";
                                return;
                            } else  {
                                *warningString += "MODEL: Argument '" + ParametersList->at(l+1) + "' for parameter '-model:recphasecenter' is pointing to a destination constellation whose correction is also set to be copied in argument '" + ParametersList->at(l) + "'. It was skipped.\n";
                                return;
                            }
                        }
                        RadioGNSSCopyFrom[i][aux5]->clicked();
                        ComboBoxAPCSameAsConst[i][aux5]->setCurrentIndex(aux1);
                        //Look for the index for the destination frequency. As if source and destination constellation are the same, the number of frequencies will be one less
                        //as you cannot copy the data to itself
                        for(k=0;k<ComboBoxAPCSameAsFreq[i][aux5][aux1]->count();k++) {
                            if (ComboBoxAPCSameAsFreq[i][aux5][aux1]->itemText(k).mid(1,1).toInt()==aux3) {
                                ComboBoxAPCSameAsFreq[i][aux5][aux1]->setCurrentIndex(k);
                                break;
                            }
                        }
                    }
                }
            }
            l+=2;
        } else {
            //User provides dN, dE and dUp
            if ((ParametersList->count()-l)<4) {
                *warningString += "MODEL: Parameter '-model:recphasecenter' requires at four arguments to manually sets receiver phase center values, but last set (starting in argument '" + ParametersList->at(l) + "') has less than four arguments left. It was skipped.\n";
                return;
            }
            //Get constellation
            if (checkConstellationQChar(ParametersList->at(l).at(0))!=1) {
                *warningString += "MODEL: Invalid constellation provided in argument '" + ParametersList->at(l) + "' in parameter '-model:recphasecenter'. It was skipped.\n";
                return;
            }
            aux1=static_cast<int>(gnssQchar2gnsstype(ParametersList->at(l).at(0)));
            //Process frequencies
            for(i=1;i<ParametersList->at(l).size();i++) {
                if (ParametersList->at(l).at(i).isDigit()==false) {
                    *warningString += "MODEL: Invalid frequency in argument '" + ParametersList->at(l) + "' in parameter '-model:recphasecenter'. It was skipped.\n";
                    return;
                }
                aux2=ParametersList->at(l).mid(i,1).toInt();
                //Skip non existing frequencies
                if (availGNSSFreq[aux1][aux2]==0) {
                    *warningString += "MODEL: Frequency '" + ParametersList->at(l).mid(i,1) + "' in argument '" + ParametersList->at(l) + "' in parameter '-model:recphasecenter' does not exist for " + GNSSName[aux1] + ". It was skipped.\n";
                    continue;
                }
                aux3=FreqNumToIndex[aux1][aux2];
                bool APCOK[3];
                double APCNEU[3]={0};
                APCNEU[0]=ParametersList->at(l+1).toDouble(APCOK);
                APCNEU[1]=ParametersList->at(l+2).toDouble(APCOK+1);
                APCNEU[2]=ParametersList->at(l+3).toDouble(APCOK+2);
                for(int j=0;j<3;j++) {
                    if (!APCOK[j]) {
                        *warningString += "MODEL: Invalid value '" + ParametersList->at(l+1+j) + "' in parameter '-model:recphasecenter'. It was skipped.\n";
                        continue;
                    }
                }
                if ( APCOK[0] && APCOK[1] && APCOK[2] ){
                    RadioGNSSSpecify[aux1][aux3]->click();
                    LineEditGNSSNEU[aux1][aux3][0]->setText(QString::number(APCNEU[0]));
                    LineEditGNSSNEU[aux1][aux3][1]->setText(QString::number(APCNEU[1]));
                    LineEditGNSSNEU[aux1][aux3][2]->setText(QString::number(APCNEU[2]));
                }
            }
            l+=4;
        }
    } //End while(l<ParametersList->count())
}


void GNSS_Antenna_Advanced::on_pushButtonAntAdvancedDefault_clicked(){
    this->setAPCdefaults();
}
void GNSS_Antenna_Advanced::on_pushButtonAntAdvancedOk_clicked(){
    this->OkFlag=1;
    this->close();
}
void GNSS_Antenna_Advanced::on_pushButtonAntAdvancedCancel_clicked(){
    this->OkFlag=0;
    this->close();
}
