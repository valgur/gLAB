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
#include "cs_sf_advanced.h"
#include "ui_cs_sf_advanced.h"

GNSS_CS_SF_Advanced::GNSS_CS_SF_Advanced(QWidget *parent) :
    QDialog(parent),
    uiCSSF(new Ui::GNSS_CS_SF_Advanced)
{
    uiCSSF->setupUi(this);

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

    this->setWindowTitle("SF Cycle-Slip Detection Advanced Configuration");
    this->InitPushButtonGNSSPointers();
    this->InitPushButtonGNSSMinFuncPointers();
    this->InitCombinationPointers();
    this->setCSdefaults();
    uiCSSF->pushButtonCSSFAdvancedOk->setFocus();

    uiCSSF->pushButtonCSSFAdvancedCancel->setHidden(true); //Remove when Cancel buttons undo all changes made by the user
}

GNSS_CS_SF_Advanced::~GNSS_CS_SF_Advanced()
{
    delete uiCSSF;
}

//Function to initialize pointers to CheckBox widget pointers
void GNSS_CS_SF_Advanced::InitPushButtonGNSSPointers(){
    PushButtonGNSS[GPS]=uiCSSF->pushButtonGPS;
    PushButtonGNSS[Galileo]=uiCSSF->pushButtonGalileo;
    PushButtonGNSS[GLONASS]=uiCSSF->pushButtonGLONASS;
    PushButtonGNSS[GEO]=uiCSSF->pushButtonGEO;
    PushButtonGNSS[BDS]=uiCSSF->pushButtonBDS;
    PushButtonGNSS[QZSS]=uiCSSF->pushButtonQZSS;
    PushButtonGNSS[IRNSS]=uiCSSF->pushButtonIRNSS;
}

//Function to initialize pointers to pushButton GNSS Measurements _clicked() functions
void GNSS_CS_SF_Advanced::InitPushButtonGNSSMinFuncPointers(){
    PushButtonGNSSFunctions[GPS]=&GNSS_CS_SF_Advanced::on_pushButtonGPS_clicked;
    PushButtonGNSSFunctions[Galileo]=&GNSS_CS_SF_Advanced::on_pushButtonGalileo_clicked;
    PushButtonGNSSFunctions[GLONASS]=&GNSS_CS_SF_Advanced::on_pushButtonGLONASS_clicked;
    PushButtonGNSSFunctions[GEO]=&GNSS_CS_SF_Advanced::on_pushButtonGEO_clicked;
    PushButtonGNSSFunctions[BDS]=&GNSS_CS_SF_Advanced::on_pushButtonBDS_clicked;
    PushButtonGNSSFunctions[QZSS]=&GNSS_CS_SF_Advanced::on_pushButtonQZSS_clicked;
    PushButtonGNSSFunctions[IRNSS]=&GNSS_CS_SF_Advanced::on_pushButtonIRNSS_clicked;
}

//Function to initialize pointers to pointers for combination
void GNSS_CS_SF_Advanced::InitCombinationPointers(){
    //GPS
    //combination Frame
    FrameCombGNSS[GPS][0]=uiCSSF->frameSFComb1GPS;
    FrameCombGNSS[GPS][1]=uiCSSF->frameSFComb2GPS;
    FrameCombGNSS[GPS][2]=uiCSSF->frameSFComb3GPS;
    //frequency ComboBox
    ComboBoxFreqGNSS[GPS][0]=uiCSSF->comboBoxSFComb1Freq1GPS;
    ComboBoxFreqGNSS[GPS][1]=uiCSSF->comboBoxSFComb2Freq1GPS;
    ComboBoxFreqGNSS[GPS][2]=uiCSSF->comboBoxSFComb3Freq1GPS;
    //measurement ComboBox Comb1 Code1
    ComboBoxMeasGNSS[GPS][0][0][0]=uiCSSF->comboBoxSFComb1Code1F1MeasGPS;
    ComboBoxMeasGNSS[GPS][0][0][1]=uiCSSF->comboBoxSFComb1Code1F2MeasGPS;
    ComboBoxMeasGNSS[GPS][0][0][2]=uiCSSF->comboBoxSFComb1Code1F5MeasGPS;
    //measurement ComboBox Comb1 Phase1
    ComboBoxMeasGNSS[GPS][0][1][0]=uiCSSF->comboBoxSFComb1Phase1F1MeasGPS;
    ComboBoxMeasGNSS[GPS][0][1][1]=uiCSSF->comboBoxSFComb1Phase1F2MeasGPS;
    ComboBoxMeasGNSS[GPS][0][1][2]=uiCSSF->comboBoxSFComb1Phase1F5MeasGPS;
    //measurement ComboBox Comb2 Code1
    ComboBoxMeasGNSS[GPS][1][0][0]=uiCSSF->comboBoxSFComb2Code1F1MeasGPS;
    ComboBoxMeasGNSS[GPS][1][0][1]=uiCSSF->comboBoxSFComb2Code1F2MeasGPS;
    ComboBoxMeasGNSS[GPS][1][0][2]=uiCSSF->comboBoxSFComb2Code1F5MeasGPS;
    //measurement ComboBox Comb2 Phase1
    ComboBoxMeasGNSS[GPS][1][1][0]=uiCSSF->comboBoxSFComb2Phase1F1MeasGPS;
    ComboBoxMeasGNSS[GPS][1][1][1]=uiCSSF->comboBoxSFComb2Phase1F2MeasGPS;
    ComboBoxMeasGNSS[GPS][1][1][2]=uiCSSF->comboBoxSFComb2Phase1F5MeasGPS;
    //measurement ComboBox Comb3 Code1
    ComboBoxMeasGNSS[GPS][2][0][0]=uiCSSF->comboBoxSFComb3Code1F1MeasGPS;
    ComboBoxMeasGNSS[GPS][2][0][1]=uiCSSF->comboBoxSFComb3Code1F2MeasGPS;
    ComboBoxMeasGNSS[GPS][2][0][2]=uiCSSF->comboBoxSFComb3Code1F5MeasGPS;
    //measurement ComboBox Comb3 Phase1
    ComboBoxMeasGNSS[GPS][2][1][0]=uiCSSF->comboBoxSFComb3Phase1F1MeasGPS;
    ComboBoxMeasGNSS[GPS][2][1][1]=uiCSSF->comboBoxSFComb3Phase1F2MeasGPS;
    ComboBoxMeasGNSS[GPS][2][1][2]=uiCSSF->comboBoxSFComb3Phase1F5MeasGPS;
    //Galileo
    //combination Frame
    FrameCombGNSS[Galileo][0]=uiCSSF->frameSFComb1Galileo;
    FrameCombGNSS[Galileo][1]=uiCSSF->frameSFComb2Galileo;
    FrameCombGNSS[Galileo][2]=uiCSSF->frameSFComb3Galileo;
    //frequency ComboBox
    ComboBoxFreqGNSS[Galileo][0]=uiCSSF->comboBoxSFComb1Freq1Galileo;
    ComboBoxFreqGNSS[Galileo][1]=uiCSSF->comboBoxSFComb2Freq1Galileo;
    ComboBoxFreqGNSS[Galileo][2]=uiCSSF->comboBoxSFComb3Freq1Galileo;
    //measurement ComboBox Comb1 Code1
    ComboBoxMeasGNSS[Galileo][0][0][0]=uiCSSF->comboBoxSFComb1Code1F1MeasGalileo;
    ComboBoxMeasGNSS[Galileo][0][0][1]=uiCSSF->comboBoxSFComb1Code1F5MeasGalileo;
    ComboBoxMeasGNSS[Galileo][0][0][2]=uiCSSF->comboBoxSFComb1Code1F6MeasGalileo;
    ComboBoxMeasGNSS[Galileo][0][0][3]=uiCSSF->comboBoxSFComb1Code1F7MeasGalileo;
    ComboBoxMeasGNSS[Galileo][0][0][4]=uiCSSF->comboBoxSFComb1Code1F8MeasGalileo;
    //measurement ComboBox Comb1 Phase1
    ComboBoxMeasGNSS[Galileo][0][1][0]=uiCSSF->comboBoxSFComb1Phase1F1MeasGalileo;
    ComboBoxMeasGNSS[Galileo][0][1][1]=uiCSSF->comboBoxSFComb1Phase1F5MeasGalileo;
    ComboBoxMeasGNSS[Galileo][0][1][2]=uiCSSF->comboBoxSFComb1Phase1F6MeasGalileo;
    ComboBoxMeasGNSS[Galileo][0][1][3]=uiCSSF->comboBoxSFComb1Phase1F7MeasGalileo;
    ComboBoxMeasGNSS[Galileo][0][1][4]=uiCSSF->comboBoxSFComb1Phase1F8MeasGalileo;
    //measurement ComboBox Comb2 Code1
    ComboBoxMeasGNSS[Galileo][1][0][0]=uiCSSF->comboBoxSFComb2Code1F1MeasGalileo;
    ComboBoxMeasGNSS[Galileo][1][0][1]=uiCSSF->comboBoxSFComb2Code1F5MeasGalileo;
    ComboBoxMeasGNSS[Galileo][1][0][2]=uiCSSF->comboBoxSFComb2Code1F6MeasGalileo;
    ComboBoxMeasGNSS[Galileo][1][0][3]=uiCSSF->comboBoxSFComb2Code1F7MeasGalileo;
    ComboBoxMeasGNSS[Galileo][1][0][4]=uiCSSF->comboBoxSFComb2Code1F8MeasGalileo;
    //measurement ComboBox Comb2 Phase1
    ComboBoxMeasGNSS[Galileo][1][1][0]=uiCSSF->comboBoxSFComb2Phase1F1MeasGalileo;
    ComboBoxMeasGNSS[Galileo][1][1][1]=uiCSSF->comboBoxSFComb2Phase1F5MeasGalileo;
    ComboBoxMeasGNSS[Galileo][1][1][2]=uiCSSF->comboBoxSFComb2Phase1F6MeasGalileo;
    ComboBoxMeasGNSS[Galileo][1][1][3]=uiCSSF->comboBoxSFComb2Phase1F7MeasGalileo;
    ComboBoxMeasGNSS[Galileo][1][1][4]=uiCSSF->comboBoxSFComb2Phase1F8MeasGalileo;
    //measurement ComboBox Comb3 Code1
    ComboBoxMeasGNSS[Galileo][2][0][0]=uiCSSF->comboBoxSFComb3Code1F1MeasGalileo;
    ComboBoxMeasGNSS[Galileo][2][0][1]=uiCSSF->comboBoxSFComb3Code1F5MeasGalileo;
    ComboBoxMeasGNSS[Galileo][2][0][2]=uiCSSF->comboBoxSFComb3Code1F6MeasGalileo;
    ComboBoxMeasGNSS[Galileo][2][0][3]=uiCSSF->comboBoxSFComb3Code1F7MeasGalileo;
    ComboBoxMeasGNSS[Galileo][2][0][4]=uiCSSF->comboBoxSFComb3Code1F8MeasGalileo;
    //measurement ComboBox Comb3 Phase1
    ComboBoxMeasGNSS[Galileo][2][1][0]=uiCSSF->comboBoxSFComb3Phase1F1MeasGalileo;
    ComboBoxMeasGNSS[Galileo][2][1][1]=uiCSSF->comboBoxSFComb3Phase1F5MeasGalileo;
    ComboBoxMeasGNSS[Galileo][2][1][2]=uiCSSF->comboBoxSFComb3Phase1F6MeasGalileo;
    ComboBoxMeasGNSS[Galileo][2][1][3]=uiCSSF->comboBoxSFComb3Phase1F7MeasGalileo;
    ComboBoxMeasGNSS[Galileo][2][1][4]=uiCSSF->comboBoxSFComb3Phase1F8MeasGalileo;
    //GLONASS
    //combination Frame
    FrameCombGNSS[GLONASS][0]=uiCSSF->frameSFComb1GLONASS;
    FrameCombGNSS[GLONASS][1]=uiCSSF->frameSFComb2GLONASS;
    FrameCombGNSS[GLONASS][2]=uiCSSF->frameSFComb3GLONASS;
    //frequency ComboBox
    ComboBoxFreqGNSS[GLONASS][0]=uiCSSF->comboBoxSFComb1Freq1GLONASS;
    ComboBoxFreqGNSS[GLONASS][1]=uiCSSF->comboBoxSFComb2Freq1GLONASS;
    ComboBoxFreqGNSS[GLONASS][2]=uiCSSF->comboBoxSFComb3Freq1GLONASS;
    //measurement ComboBox Comb1 Code1
    ComboBoxMeasGNSS[GLONASS][0][0][0]=uiCSSF->comboBoxSFComb1Code1F1MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][0][0][1]=uiCSSF->comboBoxSFComb1Code1F2MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][0][0][2]=uiCSSF->comboBoxSFComb1Code1F3MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][0][0][3]=uiCSSF->comboBoxSFComb1Code1F4MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][0][0][4]=uiCSSF->comboBoxSFComb1Code1F6MeasGLONASS;
    //measurement ComboBox Comb1 Phase1
    ComboBoxMeasGNSS[GLONASS][0][1][0]=uiCSSF->comboBoxSFComb1Phase1F1MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][0][1][1]=uiCSSF->comboBoxSFComb1Phase1F2MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][0][1][2]=uiCSSF->comboBoxSFComb1Phase1F3MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][0][1][3]=uiCSSF->comboBoxSFComb1Phase1F4MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][0][1][4]=uiCSSF->comboBoxSFComb1Phase1F6MeasGLONASS;
    //measurement ComboBox Comb2 Code1
    ComboBoxMeasGNSS[GLONASS][1][0][0]=uiCSSF->comboBoxSFComb2Code1F1MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][1][0][1]=uiCSSF->comboBoxSFComb2Code1F2MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][1][0][2]=uiCSSF->comboBoxSFComb2Code1F3MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][1][0][3]=uiCSSF->comboBoxSFComb2Code1F4MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][1][0][4]=uiCSSF->comboBoxSFComb2Code1F6MeasGLONASS;
    //measurement ComboBox Comb2 Phase1
    ComboBoxMeasGNSS[GLONASS][1][1][0]=uiCSSF->comboBoxSFComb2Phase1F1MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][1][1][1]=uiCSSF->comboBoxSFComb2Phase1F2MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][1][1][2]=uiCSSF->comboBoxSFComb2Phase1F3MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][1][1][3]=uiCSSF->comboBoxSFComb2Phase1F4MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][1][1][4]=uiCSSF->comboBoxSFComb2Phase1F6MeasGLONASS;
    //measurement ComboBox Comb3 Code1
    ComboBoxMeasGNSS[GLONASS][2][0][0]=uiCSSF->comboBoxSFComb3Code1F1MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][2][0][1]=uiCSSF->comboBoxSFComb3Code1F2MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][2][0][2]=uiCSSF->comboBoxSFComb3Code1F3MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][2][0][3]=uiCSSF->comboBoxSFComb3Code1F4MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][2][0][4]=uiCSSF->comboBoxSFComb3Code1F6MeasGLONASS;
    //measurement ComboBox Comb3 Phase1
    ComboBoxMeasGNSS[GLONASS][2][1][0]=uiCSSF->comboBoxSFComb3Phase1F1MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][2][1][1]=uiCSSF->comboBoxSFComb3Phase1F2MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][2][1][2]=uiCSSF->comboBoxSFComb3Phase1F3MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][2][1][3]=uiCSSF->comboBoxSFComb3Phase1F4MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][2][1][4]=uiCSSF->comboBoxSFComb3Phase1F6MeasGLONASS;
    //GEO
    //combination Frame
    FrameCombGNSS[GEO][0]=uiCSSF->frameSFComb1GEO;
    FrameCombGNSS[GEO][1]=uiCSSF->frameSFComb2GEO;
    FrameCombGNSS[GEO][2]=uiCSSF->frameSFComb3GEO;
    //frequency ComboBox
    ComboBoxFreqGNSS[GEO][0]=uiCSSF->comboBoxSFComb1Freq1GEO;
    ComboBoxFreqGNSS[GEO][1]=uiCSSF->comboBoxSFComb2Freq1GEO;
    ComboBoxFreqGNSS[GEO][2]=uiCSSF->comboBoxSFComb3Freq1GEO;
    //measurement ComboBox Comb1 Code1
    ComboBoxMeasGNSS[GEO][0][0][0]=uiCSSF->comboBoxSFComb1Code1F1MeasGEO;
    ComboBoxMeasGNSS[GEO][0][0][1]=uiCSSF->comboBoxSFComb1Code1F5MeasGEO;
    //measurement ComboBox Comb1 Phase1
    ComboBoxMeasGNSS[GEO][0][1][0]=uiCSSF->comboBoxSFComb1Phase1F1MeasGEO;
    ComboBoxMeasGNSS[GEO][0][1][1]=uiCSSF->comboBoxSFComb1Phase1F5MeasGEO;
    //measurement ComboBox Comb2 Code1
    ComboBoxMeasGNSS[GEO][1][0][0]=uiCSSF->comboBoxSFComb2Code1F1MeasGEO;
    ComboBoxMeasGNSS[GEO][1][0][1]=uiCSSF->comboBoxSFComb2Code1F5MeasGEO;
    //measurement ComboBox Comb2 Phase1
    ComboBoxMeasGNSS[GEO][1][1][0]=uiCSSF->comboBoxSFComb2Phase1F1MeasGEO;
    ComboBoxMeasGNSS[GEO][1][1][1]=uiCSSF->comboBoxSFComb2Phase1F5MeasGEO;
    //measurement ComboBox Comb3 Code1
    ComboBoxMeasGNSS[GEO][2][0][0]=uiCSSF->comboBoxSFComb3Code1F1MeasGEO;
    ComboBoxMeasGNSS[GEO][2][0][1]=uiCSSF->comboBoxSFComb3Code1F5MeasGEO;
    //measurement ComboBox Comb3 Phase1
    ComboBoxMeasGNSS[GEO][2][1][0]=uiCSSF->comboBoxSFComb3Phase1F1MeasGEO;
    ComboBoxMeasGNSS[GEO][2][1][1]=uiCSSF->comboBoxSFComb3Phase1F5MeasGEO;
    //BDS
    //combination Frame
    FrameCombGNSS[BDS][0]=uiCSSF->frameSFComb1BDS;
    FrameCombGNSS[BDS][1]=uiCSSF->frameSFComb2BDS;
    FrameCombGNSS[BDS][2]=uiCSSF->frameSFComb3BDS;
    //frequency ComboBox
    ComboBoxFreqGNSS[BDS][0]=uiCSSF->comboBoxSFComb1Freq1BDS;
    ComboBoxFreqGNSS[BDS][1]=uiCSSF->comboBoxSFComb2Freq1BDS;
    ComboBoxFreqGNSS[BDS][2]=uiCSSF->comboBoxSFComb3Freq1BDS;
    //measurement ComboBox Comb1 Code1
    ComboBoxMeasGNSS[BDS][0][0][0]=uiCSSF->comboBoxSFComb1Code1F1MeasBDS;
    ComboBoxMeasGNSS[BDS][0][0][1]=uiCSSF->comboBoxSFComb1Code1F2MeasBDS;
    ComboBoxMeasGNSS[BDS][0][0][2]=uiCSSF->comboBoxSFComb1Code1F5MeasBDS;
    ComboBoxMeasGNSS[BDS][0][0][3]=uiCSSF->comboBoxSFComb1Code1F6MeasBDS;
    ComboBoxMeasGNSS[BDS][0][0][4]=uiCSSF->comboBoxSFComb1Code1F7MeasBDS;
    ComboBoxMeasGNSS[BDS][0][0][5]=uiCSSF->comboBoxSFComb1Code1F8MeasBDS;
    //measurement ComboBox Comb1 Phase1
    ComboBoxMeasGNSS[BDS][0][1][0]=uiCSSF->comboBoxSFComb1Phase1F1MeasBDS;
    ComboBoxMeasGNSS[BDS][0][1][1]=uiCSSF->comboBoxSFComb1Phase1F2MeasBDS;
    ComboBoxMeasGNSS[BDS][0][1][2]=uiCSSF->comboBoxSFComb1Phase1F5MeasBDS;
    ComboBoxMeasGNSS[BDS][0][1][3]=uiCSSF->comboBoxSFComb1Phase1F6MeasBDS;
    ComboBoxMeasGNSS[BDS][0][1][4]=uiCSSF->comboBoxSFComb1Phase1F7MeasBDS;
    ComboBoxMeasGNSS[BDS][0][1][5]=uiCSSF->comboBoxSFComb1Phase1F8MeasBDS;
    //measurement ComboBox Comb2 Code1
    ComboBoxMeasGNSS[BDS][1][0][0]=uiCSSF->comboBoxSFComb2Code1F1MeasBDS;
    ComboBoxMeasGNSS[BDS][1][0][1]=uiCSSF->comboBoxSFComb2Code1F2MeasBDS;
    ComboBoxMeasGNSS[BDS][1][0][2]=uiCSSF->comboBoxSFComb2Code1F5MeasBDS;
    ComboBoxMeasGNSS[BDS][1][0][3]=uiCSSF->comboBoxSFComb2Code1F6MeasBDS;
    ComboBoxMeasGNSS[BDS][1][0][4]=uiCSSF->comboBoxSFComb2Code1F7MeasBDS;
    ComboBoxMeasGNSS[BDS][1][0][5]=uiCSSF->comboBoxSFComb2Code1F8MeasBDS;
    //measurement ComboBox Comb2 Phase1
    ComboBoxMeasGNSS[BDS][1][1][0]=uiCSSF->comboBoxSFComb2Phase1F1MeasBDS;
    ComboBoxMeasGNSS[BDS][1][1][1]=uiCSSF->comboBoxSFComb2Phase1F2MeasBDS;
    ComboBoxMeasGNSS[BDS][1][1][2]=uiCSSF->comboBoxSFComb2Phase1F5MeasBDS;
    ComboBoxMeasGNSS[BDS][1][1][3]=uiCSSF->comboBoxSFComb2Phase1F6MeasBDS;
    ComboBoxMeasGNSS[BDS][1][1][4]=uiCSSF->comboBoxSFComb2Phase1F7MeasBDS;
    ComboBoxMeasGNSS[BDS][1][1][5]=uiCSSF->comboBoxSFComb2Phase1F8MeasBDS;
    //measurement ComboBox Comb3 Code1
    ComboBoxMeasGNSS[BDS][2][0][0]=uiCSSF->comboBoxSFComb3Code1F1MeasBDS;
    ComboBoxMeasGNSS[BDS][2][0][1]=uiCSSF->comboBoxSFComb3Code1F2MeasBDS;
    ComboBoxMeasGNSS[BDS][2][0][2]=uiCSSF->comboBoxSFComb3Code1F5MeasBDS;
    ComboBoxMeasGNSS[BDS][2][0][3]=uiCSSF->comboBoxSFComb3Code1F6MeasBDS;
    ComboBoxMeasGNSS[BDS][2][0][4]=uiCSSF->comboBoxSFComb3Code1F7MeasBDS;
    ComboBoxMeasGNSS[BDS][2][0][5]=uiCSSF->comboBoxSFComb3Code1F8MeasBDS;
    //measurement ComboBox Comb3 Phase1
    ComboBoxMeasGNSS[BDS][2][1][0]=uiCSSF->comboBoxSFComb3Phase1F1MeasBDS;
    ComboBoxMeasGNSS[BDS][2][1][1]=uiCSSF->comboBoxSFComb3Phase1F2MeasBDS;
    ComboBoxMeasGNSS[BDS][2][1][2]=uiCSSF->comboBoxSFComb3Phase1F5MeasBDS;
    ComboBoxMeasGNSS[BDS][2][1][3]=uiCSSF->comboBoxSFComb3Phase1F6MeasBDS;
    ComboBoxMeasGNSS[BDS][2][1][4]=uiCSSF->comboBoxSFComb3Phase1F7MeasBDS;
    ComboBoxMeasGNSS[BDS][2][1][5]=uiCSSF->comboBoxSFComb3Phase1F8MeasBDS;
    //QZSS
    //combination Frame
    FrameCombGNSS[QZSS][0]=uiCSSF->frameSFComb1QZSS;
    FrameCombGNSS[QZSS][1]=uiCSSF->frameSFComb2QZSS;
    FrameCombGNSS[QZSS][2]=uiCSSF->frameSFComb3QZSS;
    //frequency ComboBox
    ComboBoxFreqGNSS[QZSS][0]=uiCSSF->comboBoxSFComb1Freq1QZSS;
    ComboBoxFreqGNSS[QZSS][1]=uiCSSF->comboBoxSFComb2Freq1QZSS;
    ComboBoxFreqGNSS[QZSS][2]=uiCSSF->comboBoxSFComb3Freq1QZSS;
    //measurement ComboBox Comb1 Code1
    ComboBoxMeasGNSS[QZSS][0][0][0]=uiCSSF->comboBoxSFComb1Code1F1MeasQZSS;
    ComboBoxMeasGNSS[QZSS][0][0][1]=uiCSSF->comboBoxSFComb1Code1F2MeasQZSS;
    ComboBoxMeasGNSS[QZSS][0][0][2]=uiCSSF->comboBoxSFComb1Code1F5MeasQZSS;
    ComboBoxMeasGNSS[QZSS][0][0][3]=uiCSSF->comboBoxSFComb1Code1F6MeasQZSS;
    //measurement ComboBox Comb1 Phase1
    ComboBoxMeasGNSS[QZSS][0][1][0]=uiCSSF->comboBoxSFComb1Phase1F1MeasQZSS;
    ComboBoxMeasGNSS[QZSS][0][1][1]=uiCSSF->comboBoxSFComb1Phase1F2MeasQZSS;
    ComboBoxMeasGNSS[QZSS][0][1][2]=uiCSSF->comboBoxSFComb1Phase1F5MeasQZSS;
    ComboBoxMeasGNSS[QZSS][0][1][3]=uiCSSF->comboBoxSFComb1Phase1F6MeasQZSS;
    //measurement ComboBox Comb2 Code1
    ComboBoxMeasGNSS[QZSS][1][0][0]=uiCSSF->comboBoxSFComb2Code1F1MeasQZSS;
    ComboBoxMeasGNSS[QZSS][1][0][1]=uiCSSF->comboBoxSFComb2Code1F2MeasQZSS;
    ComboBoxMeasGNSS[QZSS][1][0][2]=uiCSSF->comboBoxSFComb2Code1F5MeasQZSS;
    ComboBoxMeasGNSS[QZSS][1][0][3]=uiCSSF->comboBoxSFComb2Code1F6MeasQZSS;
    //measurement ComboBox Comb2 Phase1
    ComboBoxMeasGNSS[QZSS][1][1][0]=uiCSSF->comboBoxSFComb2Phase1F1MeasQZSS;
    ComboBoxMeasGNSS[QZSS][1][1][1]=uiCSSF->comboBoxSFComb2Phase1F2MeasQZSS;
    ComboBoxMeasGNSS[QZSS][1][1][2]=uiCSSF->comboBoxSFComb2Phase1F5MeasQZSS;
    ComboBoxMeasGNSS[QZSS][1][1][3]=uiCSSF->comboBoxSFComb2Phase1F6MeasQZSS;
    //measurement ComboBox Comb3 Code1
    ComboBoxMeasGNSS[QZSS][2][0][0]=uiCSSF->comboBoxSFComb3Code1F1MeasQZSS;
    ComboBoxMeasGNSS[QZSS][2][0][1]=uiCSSF->comboBoxSFComb3Code1F2MeasQZSS;
    ComboBoxMeasGNSS[QZSS][2][0][2]=uiCSSF->comboBoxSFComb3Code1F5MeasQZSS;
    ComboBoxMeasGNSS[QZSS][2][0][3]=uiCSSF->comboBoxSFComb3Code1F6MeasQZSS;
    //measurement ComboBox Comb3 Phase1
    ComboBoxMeasGNSS[QZSS][2][1][0]=uiCSSF->comboBoxSFComb3Phase1F1MeasQZSS;
    ComboBoxMeasGNSS[QZSS][2][1][1]=uiCSSF->comboBoxSFComb3Phase1F2MeasQZSS;
    ComboBoxMeasGNSS[QZSS][2][1][2]=uiCSSF->comboBoxSFComb3Phase1F5MeasQZSS;
    ComboBoxMeasGNSS[QZSS][2][1][3]=uiCSSF->comboBoxSFComb3Phase1F6MeasQZSS;
    //IRNSS
    //combination Frame
    FrameCombGNSS[IRNSS][0]=uiCSSF->frameSFComb1IRNSS;
    FrameCombGNSS[IRNSS][1]=uiCSSF->frameSFComb2IRNSS;
    FrameCombGNSS[IRNSS][2]=uiCSSF->frameSFComb3IRNSS;
    //frequency ComboBox
    ComboBoxFreqGNSS[IRNSS][0]=uiCSSF->comboBoxSFComb1Freq1IRNSS;
    ComboBoxFreqGNSS[IRNSS][1]=uiCSSF->comboBoxSFComb2Freq1IRNSS;
    ComboBoxFreqGNSS[IRNSS][2]=uiCSSF->comboBoxSFComb3Freq1IRNSS;
    //measurement ComboBox Comb1 Code1
    ComboBoxMeasGNSS[IRNSS][0][0][0]=uiCSSF->comboBoxSFComb1Code1F5MeasIRNSS;
    ComboBoxMeasGNSS[IRNSS][0][0][1]=uiCSSF->comboBoxSFComb1Code1F9MeasIRNSS;
    //measurement ComboBox Comb1 Phase1
    ComboBoxMeasGNSS[IRNSS][0][1][0]=uiCSSF->comboBoxSFComb1Phase1F5MeasIRNSS;
    ComboBoxMeasGNSS[IRNSS][0][1][1]=uiCSSF->comboBoxSFComb1Phase1F9MeasIRNSS;
    //measurement ComboBox Comb2 Code1
    ComboBoxMeasGNSS[IRNSS][1][0][0]=uiCSSF->comboBoxSFComb2Code1F5MeasIRNSS;
    ComboBoxMeasGNSS[IRNSS][1][0][1]=uiCSSF->comboBoxSFComb2Code1F9MeasIRNSS;
    //measurement ComboBox Comb2 Phase1
    ComboBoxMeasGNSS[IRNSS][1][1][0]=uiCSSF->comboBoxSFComb2Phase1F5MeasIRNSS;
    ComboBoxMeasGNSS[IRNSS][1][1][1]=uiCSSF->comboBoxSFComb2Phase1F9MeasIRNSS;
    //measurement ComboBox Comb3 Code1
    ComboBoxMeasGNSS[IRNSS][2][0][0]=uiCSSF->comboBoxSFComb3Code1F5MeasIRNSS;
    ComboBoxMeasGNSS[IRNSS][2][0][1]=uiCSSF->comboBoxSFComb3Code1F9MeasIRNSS;
    //measurement ComboBox Comb3 Phase1
    ComboBoxMeasGNSS[IRNSS][2][1][0]=uiCSSF->comboBoxSFComb3Phase1F5MeasIRNSS;
    ComboBoxMeasGNSS[IRNSS][2][1][1]=uiCSSF->comboBoxSFComb3Phase1F9MeasIRNSS;
}

//turn to specified constellation page when click the corresponding pushButton
void GNSS_CS_SF_Advanced::on_pushButtonGPS_clicked(){
    uiCSSF->stackedWidgetSFConfigurationGNSS->setCurrentIndex(GPS);
    uiCSSF->labelSelectPRNFor->setText("GPS:");
    uiCSSF->pushButtonGalileo->setChecked(false);
    uiCSSF->pushButtonGLONASS->setChecked(false);
    uiCSSF->pushButtonGEO->setChecked(false);
    uiCSSF->pushButtonBDS->setChecked(false);
    uiCSSF->pushButtonQZSS->setChecked(false);
    uiCSSF->pushButtonIRNSS->setChecked(false);
    uiCSSF->pushButtonGPS->setChecked(true);
    if (FrameCombGNSS[GPS][2]->isHidden()==false) {
        uiCSSF->pushButtonSFGPSAdd->setEnabled(false);
        uiCSSF->pushButtonSFGPSDel->setEnabled(true);
    } else if (FrameCombGNSS[GPS][1]->isHidden()==false) {
        uiCSSF->pushButtonSFGPSAdd->setEnabled(true);
        uiCSSF->pushButtonSFGPSDel->setEnabled(true);
    } else {
        uiCSSF->pushButtonSFGPSAdd->setEnabled(true);
        uiCSSF->pushButtonSFGPSDel->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_pushButtonGalileo_clicked(){
    uiCSSF->stackedWidgetSFConfigurationGNSS->setCurrentIndex(Galileo);
    uiCSSF->labelSelectPRNFor->setText("Galileo:");
    uiCSSF->pushButtonGPS->setChecked(false);
    uiCSSF->pushButtonGLONASS->setChecked(false);
    uiCSSF->pushButtonGEO->setChecked(false);
    uiCSSF->pushButtonBDS->setChecked(false);
    uiCSSF->pushButtonQZSS->setChecked(false);
    uiCSSF->pushButtonIRNSS->setChecked(false);
    uiCSSF->pushButtonGalileo->setChecked(true);
    if (FrameCombGNSS[Galileo][2]->isHidden()==false) {
        uiCSSF->pushButtonSFGalileoAdd->setEnabled(false);
        uiCSSF->pushButtonSFGalileoDel->setEnabled(true);
    } else if (FrameCombGNSS[Galileo][1]->isHidden()==false) {
        uiCSSF->pushButtonSFGalileoAdd->setEnabled(true);
        uiCSSF->pushButtonSFGalileoDel->setEnabled(true);
    } else {
        uiCSSF->pushButtonSFGalileoAdd->setEnabled(true);
        uiCSSF->pushButtonSFGalileoDel->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_pushButtonGLONASS_clicked(){
    uiCSSF->stackedWidgetSFConfigurationGNSS->setCurrentIndex(GLONASS);
    uiCSSF->labelSelectPRNFor->setText("GLONASS:");
    uiCSSF->pushButtonGPS->setChecked(false);
    uiCSSF->pushButtonGalileo->setChecked(false);
    uiCSSF->pushButtonGEO->setChecked(false);
    uiCSSF->pushButtonBDS->setChecked(false);
    uiCSSF->pushButtonQZSS->setChecked(false);
    uiCSSF->pushButtonIRNSS->setChecked(false);
    uiCSSF->pushButtonGLONASS->setChecked(true);
    if (FrameCombGNSS[GLONASS][2]->isHidden()==false) {
        uiCSSF->pushButtonSFGLONASSAdd->setEnabled(false);
        uiCSSF->pushButtonSFGLONASSDel->setEnabled(true);
    } else if (FrameCombGNSS[GLONASS][1]->isHidden()==false) {
        uiCSSF->pushButtonSFGLONASSAdd->setEnabled(true);
        uiCSSF->pushButtonSFGLONASSDel->setEnabled(true);
    } else {
        uiCSSF->pushButtonSFGLONASSAdd->setEnabled(true);
        uiCSSF->pushButtonSFGLONASSDel->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_pushButtonGEO_clicked(){
    uiCSSF->stackedWidgetSFConfigurationGNSS->setCurrentIndex(GEO);
    uiCSSF->labelSelectPRNFor->setText("GEO:");
    uiCSSF->pushButtonGPS->setChecked(false);
    uiCSSF->pushButtonGalileo->setChecked(false);
    uiCSSF->pushButtonGLONASS->setChecked(false);
    uiCSSF->pushButtonBDS->setChecked(false);
    uiCSSF->pushButtonQZSS->setChecked(false);
    uiCSSF->pushButtonIRNSS->setChecked(false);
    uiCSSF->pushButtonGEO->setChecked(true);
    if (FrameCombGNSS[GEO][2]->isHidden()==false) {
        uiCSSF->pushButtonSFGEOAdd->setEnabled(false);
        uiCSSF->pushButtonSFGEODel->setEnabled(true);
    } else if (FrameCombGNSS[GEO][1]->isHidden()==false) {
        uiCSSF->pushButtonSFGEOAdd->setEnabled(true);
        uiCSSF->pushButtonSFGEODel->setEnabled(true);
    } else {
        uiCSSF->pushButtonSFGEOAdd->setEnabled(true);
        uiCSSF->pushButtonSFGEODel->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_pushButtonBDS_clicked(){
    uiCSSF->stackedWidgetSFConfigurationGNSS->setCurrentIndex(BDS);
    uiCSSF->labelSelectPRNFor->setText("BDS:");
    uiCSSF->pushButtonGPS->setChecked(false);
    uiCSSF->pushButtonGalileo->setChecked(false);
    uiCSSF->pushButtonGLONASS->setChecked(false);
    uiCSSF->pushButtonGEO->setChecked(false);
    uiCSSF->pushButtonQZSS->setChecked(false);
    uiCSSF->pushButtonIRNSS->setChecked(false);
    uiCSSF->pushButtonBDS->setChecked(true);
    if (FrameCombGNSS[BDS][2]->isHidden()==false) {
        uiCSSF->pushButtonSFBDSAdd->setEnabled(false);
        uiCSSF->pushButtonSFBDSDel->setEnabled(true);
    } else if (FrameCombGNSS[BDS][1]->isHidden()==false) {
        uiCSSF->pushButtonSFBDSAdd->setEnabled(true);
        uiCSSF->pushButtonSFBDSDel->setEnabled(true);
    } else {
        uiCSSF->pushButtonSFBDSAdd->setEnabled(true);
        uiCSSF->pushButtonSFBDSDel->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_pushButtonQZSS_clicked(){
    uiCSSF->stackedWidgetSFConfigurationGNSS->setCurrentIndex(QZSS);
    uiCSSF->labelSelectPRNFor->setText("QZSS:");
    uiCSSF->pushButtonGPS->setChecked(false);
    uiCSSF->pushButtonGalileo->setChecked(false);
    uiCSSF->pushButtonGLONASS->setChecked(false);
    uiCSSF->pushButtonGEO->setChecked(false);
    uiCSSF->pushButtonBDS->setChecked(false);
    uiCSSF->pushButtonIRNSS->setChecked(false);
    uiCSSF->pushButtonQZSS->setChecked(true);
    if (FrameCombGNSS[QZSS][2]->isHidden()==false) {
        uiCSSF->pushButtonSFQZSSAdd->setEnabled(false);
        uiCSSF->pushButtonSFQZSSDel->setEnabled(true);
    } else if (FrameCombGNSS[QZSS][1]->isHidden()==false) {
        uiCSSF->pushButtonSFQZSSAdd->setEnabled(true);
        uiCSSF->pushButtonSFQZSSDel->setEnabled(true);
    } else {
        uiCSSF->pushButtonSFQZSSAdd->setEnabled(true);
        uiCSSF->pushButtonSFQZSSDel->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_pushButtonIRNSS_clicked(){
    uiCSSF->stackedWidgetSFConfigurationGNSS->setCurrentIndex(IRNSS);
    uiCSSF->labelSelectPRNFor->setText("IRNSS:");
    uiCSSF->pushButtonGPS->setChecked(false);
    uiCSSF->pushButtonGalileo->setChecked(false);
    uiCSSF->pushButtonGLONASS->setChecked(false);
    uiCSSF->pushButtonGEO->setChecked(false);
    uiCSSF->pushButtonBDS->setChecked(false);
    uiCSSF->pushButtonQZSS->setChecked(false);
    uiCSSF->pushButtonIRNSS->setChecked(true);
    if (FrameCombGNSS[IRNSS][2]->isHidden()==false) {
        uiCSSF->pushButtonSFIRNSSAdd->setEnabled(false);
        uiCSSF->pushButtonSFIRNSSDel->setEnabled(true);
    } else if (FrameCombGNSS[IRNSS][1]->isHidden()==false) {
        uiCSSF->pushButtonSFIRNSSAdd->setEnabled(true);
        uiCSSF->pushButtonSFIRNSSDel->setEnabled(true);
    } else {
        uiCSSF->pushButtonSFIRNSSAdd->setEnabled(true);
        uiCSSF->pushButtonSFIRNSSDel->setEnabled(false);
    }
}

// Set all defaults
void GNSS_CS_SF_Advanced::setCSdefaults(){
    this->SetDefaultGPS();
    this->SetDefaultGalileo();
    this->SetDefaultGLONASS();
    this->SetDefaultGEO();
    this->SetDefaultBDS();
    this->SetDefaultQZSS();
    this->SetDefaultIRNSS();
}

// GPS
void GNSS_CS_SF_Advanced::SetDefaultGPS(){
    uiCSSF->frameSFComb2GPS->setHidden(true);
    uiCSSF->frameSFComb3GPS->setHidden(true);
    uiCSSF->pushButtonSFGPSAdd->setEnabled(true);
    uiCSSF->pushButtonSFGPSDel->setEnabled(false);
    this->on_comboBoxSFComb1Freq1GPS_currentIndexChanged(0);
    this->on_comboBoxSFComb2Freq1GPS_currentIndexChanged(0);
    this->on_comboBoxSFComb3Freq1GPS_currentIndexChanged(0);
}
void GNSS_CS_SF_Advanced::on_pushButtonSFGPSAdd_clicked(){
    if (uiCSSF->frameSFComb2GPS->isHidden()==true){
        uiCSSF->pushButtonSFGPSDel->setEnabled(true);
        uiCSSF->frameSFComb2GPS->setHidden(false);
    } else if (uiCSSF->frameSFComb3GPS->isHidden()==true){
        uiCSSF->frameSFComb3GPS->setHidden(false);
        uiCSSF->pushButtonSFGPSAdd->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_pushButtonSFGPSDel_clicked(){
    if (uiCSSF->frameSFComb3GPS->isHidden()==false){
        uiCSSF->frameSFComb3GPS->setHidden(true);
        uiCSSF->pushButtonSFGPSAdd->setEnabled(true);
    } else if (uiCSSF->frameSFComb2GPS->isHidden()==false){
        uiCSSF->frameSFComb2GPS->setHidden(true);
        uiCSSF->pushButtonSFGPSDel->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Freq1GPS_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb1Freq1GPS->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb1Code1MeasGPS->setEnabled(false);
        uiCSSF->comboBoxSFComb1Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb1Phase1MeasGPS->setEnabled(false);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb1Code1MeasGPS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb1Code1MeasGPS->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb1Phase1MeasGPS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb1Phase1MeasGPS->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F1MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F1MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F1MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F1MeasGPS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F2MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F2MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F2MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F2MeasGPS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F5MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F5MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F5MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F5MeasGPS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F1MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F1MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F1MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F1MeasGPS->setCurrentIndex(index==9?1:index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F2MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F2MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F2MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F2MeasGPS->setCurrentIndex(index==10?1:index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F5MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F5MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F5MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F5MeasGPS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Freq1GPS_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb2Freq1GPS->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb2Code1MeasGPS->setEnabled(false);
        uiCSSF->comboBoxSFComb2Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb2Phase1MeasGPS->setEnabled(false);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb2Code1MeasGPS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb2Code1MeasGPS->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb2Phase1MeasGPS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb2Phase1MeasGPS->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F1MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F1MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F1MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F1MeasGPS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F2MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F2MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F2MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F2MeasGPS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F5MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F5MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F5MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F5MeasGPS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F1MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F1MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F1MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F1MeasGPS->setCurrentIndex(index==9?1:index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F2MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F2MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F2MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F2MeasGPS->setCurrentIndex(index==10?1:index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F5MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F5MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F5MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F5MeasGPS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Freq1GPS_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb3Freq1GPS->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb3Code1MeasGPS->setEnabled(false);
        uiCSSF->comboBoxSFComb3Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb3Phase1MeasGPS->setEnabled(false);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb3Code1MeasGPS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb3Code1MeasGPS->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb3Phase1MeasGPS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb3Phase1MeasGPS->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F1MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F1MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F1MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F1MeasGPS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F2MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F2MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F2MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F2MeasGPS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F5MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F5MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F5MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F5MeasGPS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F1MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F1MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F1MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F1MeasGPS->setCurrentIndex(index==9?1:index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F2MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F2MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F2MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F2MeasGPS->setCurrentIndex(index==10?1:index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F5MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F5MeasGPS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F5MeasGPS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F5MeasGPS->setCurrentIndex(index);
    }
}

//Galileo
void GNSS_CS_SF_Advanced::SetDefaultGalileo(){
    uiCSSF->frameSFComb2Galileo->setHidden(true);
    uiCSSF->frameSFComb3Galileo->setHidden(true);
    uiCSSF->pushButtonSFGalileoAdd->setEnabled(true);
    uiCSSF->pushButtonSFGalileoDel->setEnabled(false);
    this->on_comboBoxSFComb1Freq1Galileo_currentIndexChanged(0);
    this->on_comboBoxSFComb2Freq1Galileo_currentIndexChanged(0);
    this->on_comboBoxSFComb3Freq1Galileo_currentIndexChanged(0);
}
void GNSS_CS_SF_Advanced::on_pushButtonSFGalileoAdd_clicked(){
    if (uiCSSF->frameSFComb2Galileo->isHidden()==true){
        uiCSSF->pushButtonSFGalileoDel->setEnabled(true);
        uiCSSF->frameSFComb2Galileo->setHidden(false);
    } else if (uiCSSF->frameSFComb3Galileo->isHidden()==true){
        uiCSSF->frameSFComb3Galileo->setHidden(false);
        uiCSSF->pushButtonSFGalileoAdd->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_pushButtonSFGalileoDel_clicked(){
    if (uiCSSF->frameSFComb3Galileo->isHidden()==false){
        uiCSSF->frameSFComb3Galileo->setHidden(true);
        uiCSSF->pushButtonSFGalileoAdd->setEnabled(true);
    } else if (uiCSSF->frameSFComb2Galileo->isHidden()==false){
        uiCSSF->frameSFComb2Galileo->setHidden(true);
        uiCSSF->pushButtonSFGalileoDel->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Freq1Galileo_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb1Freq1Galileo->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb1Code1MeasGalileo->setEnabled(false);
        uiCSSF->comboBoxSFComb1Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb1Phase1MeasGalileo->setEnabled(false);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb1Code1MeasGalileo->setEnabled(true);
        uiCSSF->stackedWidgetSFComb1Code1MeasGalileo->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb1Phase1MeasGalileo->setEnabled(true);
        uiCSSF->stackedWidgetSFComb1Phase1MeasGalileo->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F1MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F1MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F1MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F1MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F5MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F5MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F5MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F5MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F6MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F6MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F6MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F6MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F7MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F7MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F7MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F7MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F8MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F8MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F8MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F8MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F1MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F1MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F1MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F1MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F5MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F5MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F5MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F5MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F6MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F6MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F6MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F6MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F7MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F7MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F7MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F7MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F8MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F8MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F8MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F8MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Freq1Galileo_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb2Freq1Galileo->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb2Code1MeasGalileo->setEnabled(false);
        uiCSSF->comboBoxSFComb2Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb2Phase1MeasGalileo->setEnabled(false);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb2Code1MeasGalileo->setEnabled(true);
        uiCSSF->stackedWidgetSFComb2Code1MeasGalileo->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb2Phase1MeasGalileo->setEnabled(true);
        uiCSSF->stackedWidgetSFComb2Phase1MeasGalileo->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F1MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F1MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F1MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F1MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F5MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F5MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F5MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F5MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F6MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F6MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F6MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F6MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F7MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F7MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F7MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F7MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F8MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F8MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F8MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F8MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F1MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F1MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F1MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F1MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F5MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F5MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F5MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F5MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F6MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F6MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F6MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F6MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F7MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F7MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F7MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F7MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F8MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F8MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F8MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F8MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Freq1Galileo_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb3Freq1Galileo->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb3Code1MeasGalileo->setEnabled(false);
        uiCSSF->comboBoxSFComb3Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb3Phase1MeasGalileo->setEnabled(false);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb3Code1MeasGalileo->setEnabled(true);
        uiCSSF->stackedWidgetSFComb3Code1MeasGalileo->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb3Phase1MeasGalileo->setEnabled(true);
        uiCSSF->stackedWidgetSFComb3Phase1MeasGalileo->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F1MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F1MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F1MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F1MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F5MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F5MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F5MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F5MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F6MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F6MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F6MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F6MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F7MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F7MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F7MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F7MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F8MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F8MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F8MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F8MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F1MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F1MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F1MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F1MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F5MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F5MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F5MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F5MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F6MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F6MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F6MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F6MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F7MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F7MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F7MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F7MeasGalileo->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F8MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F8MeasGalileo->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F8MeasGalileo->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F8MeasGalileo->setCurrentIndex(index);
    }
}

//GLONASS
void GNSS_CS_SF_Advanced::SetDefaultGLONASS(){
    uiCSSF->frameSFComb2GLONASS->setHidden(true);
    uiCSSF->frameSFComb3GLONASS->setHidden(true);
    uiCSSF->pushButtonSFGLONASSAdd->setEnabled(true);
    uiCSSF->pushButtonSFGLONASSDel->setEnabled(false);
    this->on_comboBoxSFComb1Freq1GLONASS_currentIndexChanged(0);
    this->on_comboBoxSFComb2Freq1GLONASS_currentIndexChanged(0);
    this->on_comboBoxSFComb3Freq1GLONASS_currentIndexChanged(0);
}
void GNSS_CS_SF_Advanced::on_pushButtonSFGLONASSAdd_clicked(){
    if (uiCSSF->frameSFComb2GLONASS->isHidden()==true){
        uiCSSF->pushButtonSFGLONASSDel->setEnabled(true);
        uiCSSF->frameSFComb2GLONASS->setHidden(false);
    } else if (uiCSSF->frameSFComb3GLONASS->isHidden()==true){
        uiCSSF->frameSFComb3GLONASS->setHidden(false);
        uiCSSF->pushButtonSFGLONASSAdd->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_pushButtonSFGLONASSDel_clicked(){
    if (uiCSSF->frameSFComb3GLONASS->isHidden()==false){
        uiCSSF->frameSFComb3GLONASS->setHidden(true);
        uiCSSF->pushButtonSFGLONASSAdd->setEnabled(true);
    } else if (uiCSSF->frameSFComb2GLONASS->isHidden()==false){
        uiCSSF->frameSFComb2GLONASS->setHidden(true);
        uiCSSF->pushButtonSFGLONASSDel->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Freq1GLONASS_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb1Freq1GLONASS->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb1Code1MeasGLONASS->setEnabled(false);
        uiCSSF->comboBoxSFComb1Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb1Phase1MeasGLONASS->setEnabled(false);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb1Code1MeasGLONASS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb1Code1MeasGLONASS->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb1Phase1MeasGLONASS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb1Phase1MeasGLONASS->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F1MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F1MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F1MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F1MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F2MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F2MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F2MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F2MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F3MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F3MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F3MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F3MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F4MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F4MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F4MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F4MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F6MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F6MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F6MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F6MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F1MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F1MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F1MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F1MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F2MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F2MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F2MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F2MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F3MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F3MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F3MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F3MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F4MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F4MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F4MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F4MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F6MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F6MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F6MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F6MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Freq1GLONASS_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb2Freq1GLONASS->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb2Code1MeasGLONASS->setEnabled(false);
        uiCSSF->comboBoxSFComb2Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb2Phase1MeasGLONASS->setEnabled(false);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb2Code1MeasGLONASS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb2Code1MeasGLONASS->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb2Phase1MeasGLONASS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb2Phase1MeasGLONASS->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F1MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F1MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F1MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F1MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F2MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F2MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F2MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F2MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F3MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F3MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F3MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F3MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F4MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F4MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F4MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F4MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F6MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F6MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F6MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F6MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F1MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F1MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F1MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F1MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F2MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F2MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F2MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F2MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F3MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F3MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F3MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F3MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F4MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F4MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F4MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F4MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F6MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F6MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F6MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F6MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Freq1GLONASS_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb3Freq1GLONASS->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb3Code1MeasGLONASS->setEnabled(false);
        uiCSSF->comboBoxSFComb3Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb3Phase1MeasGLONASS->setEnabled(false);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb3Code1MeasGLONASS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb3Code1MeasGLONASS->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb3Phase1MeasGLONASS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb3Phase1MeasGLONASS->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F1MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F1MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F1MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F1MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F2MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F2MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F2MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F2MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F3MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F3MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F3MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F3MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F4MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F4MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F4MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F4MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F6MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F6MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F6MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F6MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F1MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F1MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F1MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F1MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F2MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F2MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F2MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F2MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F3MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F3MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F3MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F3MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F4MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F4MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F4MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F4MeasGLONASS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F6MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F6MeasGLONASS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F6MeasGLONASS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F6MeasGLONASS->setCurrentIndex(index);
    }
}

//GEO
void GNSS_CS_SF_Advanced::SetDefaultGEO(){
    uiCSSF->frameSFComb2GEO->setHidden(true);
    uiCSSF->frameSFComb3GEO->setHidden(true);
    uiCSSF->pushButtonSFGEOAdd->setEnabled(true);
    uiCSSF->pushButtonSFGEODel->setEnabled(false);
    this->on_comboBoxSFComb1Freq1GEO_currentIndexChanged(0);
    this->on_comboBoxSFComb2Freq1GEO_currentIndexChanged(0);
    this->on_comboBoxSFComb3Freq1GEO_currentIndexChanged(0);
}
void GNSS_CS_SF_Advanced::on_pushButtonSFGEOAdd_clicked(){
    if (uiCSSF->frameSFComb2GEO->isHidden()==true){
        uiCSSF->pushButtonSFGEODel->setEnabled(true);
        uiCSSF->frameSFComb2GEO->setHidden(false);
    } else if (uiCSSF->frameSFComb3GEO->isHidden()==true){
        uiCSSF->frameSFComb3GEO->setHidden(false);
        uiCSSF->pushButtonSFGEOAdd->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_pushButtonSFGEODel_clicked(){
    if (uiCSSF->frameSFComb3GEO->isHidden()==false){
        uiCSSF->frameSFComb3GEO->setHidden(true);
        uiCSSF->pushButtonSFGEOAdd->setEnabled(true);
    } else if (uiCSSF->frameSFComb2GEO->isHidden()==false){
        uiCSSF->frameSFComb2GEO->setHidden(true);
        uiCSSF->pushButtonSFGEODel->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Freq1GEO_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb1Freq1GEO->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb1Code1MeasGEO->setEnabled(false);
        uiCSSF->comboBoxSFComb1Code1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGEO->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb1Phase1MeasGEO->setEnabled(false);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb1Code1MeasGEO->setEnabled(true);
        uiCSSF->stackedWidgetSFComb1Code1MeasGEO->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb1Phase1MeasGEO->setEnabled(true);
        uiCSSF->stackedWidgetSFComb1Phase1MeasGEO->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F1MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F1MeasGEO->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F1MeasGEO->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F1MeasGEO->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F5MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F5MeasGEO->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F5MeasGEO->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F5MeasGEO->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F1MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F1MeasGEO->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F1MeasGEO->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F1MeasGEO->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F5MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F5MeasGEO->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F5MeasGEO->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F5MeasGEO->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Freq1GEO_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb2Freq1GEO->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb2Code1MeasGEO->setEnabled(false);
        uiCSSF->comboBoxSFComb2Code1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGEO->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb2Phase1MeasGEO->setEnabled(false);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb2Code1MeasGEO->setEnabled(true);
        uiCSSF->stackedWidgetSFComb2Code1MeasGEO->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb2Phase1MeasGEO->setEnabled(true);
        uiCSSF->stackedWidgetSFComb2Phase1MeasGEO->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F1MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F1MeasGEO->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F1MeasGEO->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F1MeasGEO->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F5MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F5MeasGEO->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F5MeasGEO->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F5MeasGEO->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F1MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F1MeasGEO->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F1MeasGEO->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F1MeasGEO->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F5MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F5MeasGEO->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F5MeasGEO->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F5MeasGEO->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Freq1GEO_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb3Freq1GEO->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb3Code1MeasGEO->setEnabled(false);
        uiCSSF->comboBoxSFComb3Code1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGEO->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb3Phase1MeasGEO->setEnabled(false);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb3Code1MeasGEO->setEnabled(true);
        uiCSSF->stackedWidgetSFComb3Code1MeasGEO->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb3Phase1MeasGEO->setEnabled(true);
        uiCSSF->stackedWidgetSFComb3Phase1MeasGEO->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F1MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F1MeasGEO->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F1MeasGEO->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F1MeasGEO->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F5MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F5MeasGEO->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F5MeasGEO->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F5MeasGEO->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F1MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F1MeasGEO->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F1MeasGEO->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F1MeasGEO->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F5MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F5MeasGEO->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F5MeasGEO->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F5MeasGEO->setCurrentIndex(index);
    }
}

//BDS
void GNSS_CS_SF_Advanced::SetDefaultBDS(){
    uiCSSF->frameSFComb2BDS->setHidden(true);
    uiCSSF->frameSFComb3BDS->setHidden(true);
    uiCSSF->pushButtonSFBDSAdd->setEnabled(true);
    uiCSSF->pushButtonSFBDSDel->setEnabled(false);
    this->on_comboBoxSFComb1Freq1BDS_currentIndexChanged(0);
    this->on_comboBoxSFComb2Freq1BDS_currentIndexChanged(0);
    this->on_comboBoxSFComb3Freq1BDS_currentIndexChanged(0);
}
void GNSS_CS_SF_Advanced::on_pushButtonSFBDSAdd_clicked(){
    if (uiCSSF->frameSFComb2BDS->isHidden()==true){
        uiCSSF->pushButtonSFBDSDel->setEnabled(true);
        uiCSSF->frameSFComb2BDS->setHidden(false);
    } else if (uiCSSF->frameSFComb3BDS->isHidden()==true){
        uiCSSF->frameSFComb3BDS->setHidden(false);
        uiCSSF->pushButtonSFBDSAdd->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_pushButtonSFBDSDel_clicked(){
    if (uiCSSF->frameSFComb3BDS->isHidden()==false){
        uiCSSF->frameSFComb3BDS->setHidden(true);
        uiCSSF->pushButtonSFBDSAdd->setEnabled(true);
    } else if (uiCSSF->frameSFComb2BDS->isHidden()==false){
        uiCSSF->frameSFComb2BDS->setHidden(true);
        uiCSSF->pushButtonSFBDSDel->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Freq1BDS_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb1Freq1BDS->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb1Code1MeasBDS->setEnabled(false);
        uiCSSF->comboBoxSFComb1Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb1Phase1MeasBDS->setEnabled(false);
        uiCSSF->comboBoxSFComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb1Code1MeasBDS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb1Code1MeasBDS->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb1Phase1MeasBDS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb1Phase1MeasBDS->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F2MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F2MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F2MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F2MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F7MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F7MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F7MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F7MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F6MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F6MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F6MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F6MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F5MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F5MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F5MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F5MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F1MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F1MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F1MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F1MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F8MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F8MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F8MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F8MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F2MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F2MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F2MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F2MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F7MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F7MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F7MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F7MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F6MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F6MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F6MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F6MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F5MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F5MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F5MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F5MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F1MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F1MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F1MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F1MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F8MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F8MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F8MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F8MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Freq1BDS_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb2Freq1BDS->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb2Code1MeasBDS->setEnabled(false);
        uiCSSF->comboBoxSFComb2Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb2Phase1MeasBDS->setEnabled(false);
        uiCSSF->comboBoxSFComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb2Code1MeasBDS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb2Code1MeasBDS->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb2Phase1MeasBDS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb2Phase1MeasBDS->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F2MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F2MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F2MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F2MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F7MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F7MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F7MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F7MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F6MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F6MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F6MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F6MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F5MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F5MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F5MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F5MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F1MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F1MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F1MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F1MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F8MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F8MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F8MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F8MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F2MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F2MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F2MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F2MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F7MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F7MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F7MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F7MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F6MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F6MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F6MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F6MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F5MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F5MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F5MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F5MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F1MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F1MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F1MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F1MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F8MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F8MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F8MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F8MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Freq1BDS_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb3Freq1BDS->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb3Code1MeasBDS->setEnabled(false);
        uiCSSF->comboBoxSFComb3Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb3Phase1MeasBDS->setEnabled(false);
        uiCSSF->comboBoxSFComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb3Code1MeasBDS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb3Code1MeasBDS->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb3Phase1MeasBDS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb3Phase1MeasBDS->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F2MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F2MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F2MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F2MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F7MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F7MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F7MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F7MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F6MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F6MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F6MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F6MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F5MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F5MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F5MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F5MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F1MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F1MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F1MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F1MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F8MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F8MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F8MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F8MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F2MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F2MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F2MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F2MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F7MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F7MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F7MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F7MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F6MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F6MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F6MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F6MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F5MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F5MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F5MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F5MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F1MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F1MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F1MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F1MeasBDS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F8MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F8MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F8MeasBDS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F8MeasBDS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F8MeasBDS->setCurrentIndex(index);
    }
}

//QZSS
void GNSS_CS_SF_Advanced::SetDefaultQZSS(){
    uiCSSF->frameSFComb2QZSS->setHidden(true);
    uiCSSF->frameSFComb3QZSS->setHidden(true);
    uiCSSF->pushButtonSFQZSSAdd->setEnabled(true);
    uiCSSF->pushButtonSFQZSSDel->setEnabled(false);
    this->on_comboBoxSFComb1Freq1QZSS_currentIndexChanged(0);
    this->on_comboBoxSFComb2Freq1QZSS_currentIndexChanged(0);
    this->on_comboBoxSFComb3Freq1QZSS_currentIndexChanged(0);
}
void GNSS_CS_SF_Advanced::on_pushButtonSFQZSSAdd_clicked(){
    if (uiCSSF->frameSFComb2QZSS->isHidden()==true){
        uiCSSF->pushButtonSFQZSSDel->setEnabled(true);
        uiCSSF->frameSFComb2QZSS->setHidden(false);
    } else if (uiCSSF->frameSFComb3QZSS->isHidden()==true){
        uiCSSF->frameSFComb3QZSS->setHidden(false);
        uiCSSF->pushButtonSFQZSSAdd->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_pushButtonSFQZSSDel_clicked(){
    if (uiCSSF->frameSFComb3QZSS->isHidden()==false){
        uiCSSF->frameSFComb3QZSS->setHidden(true);
        uiCSSF->pushButtonSFQZSSAdd->setEnabled(true);
    } else if (uiCSSF->frameSFComb2QZSS->isHidden()==false){
        uiCSSF->frameSFComb2QZSS->setHidden(true);
        uiCSSF->pushButtonSFQZSSDel->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Freq1QZSS_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb1Freq1QZSS->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb1Code1MeasQZSS->setEnabled(false);
        uiCSSF->comboBoxSFComb1Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb1Phase1MeasQZSS->setEnabled(false);
        uiCSSF->comboBoxSFComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb1Code1MeasQZSS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb1Code1MeasQZSS->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb1Phase1MeasQZSS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb1Phase1MeasQZSS->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F1MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F1MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F1MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F1MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F2MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F2MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F2MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F2MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F5MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F5MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F5MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F5MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F6MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F6MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F6MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F6MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F1MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F1MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F1MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F1MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F2MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F2MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F2MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F2MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F5MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F5MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F5MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F5MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F6MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F6MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F6MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F6MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Freq1QZSS_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb2Freq1QZSS->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb2Code1MeasQZSS->setEnabled(false);
        uiCSSF->comboBoxSFComb2Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb2Phase1MeasQZSS->setEnabled(false);
        uiCSSF->comboBoxSFComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb2Code1MeasQZSS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb2Code1MeasQZSS->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb2Phase1MeasQZSS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb2Phase1MeasQZSS->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F1MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F1MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F1MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F1MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F2MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F2MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F2MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F2MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F5MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F5MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F5MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F5MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F6MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F6MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F6MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F6MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F1MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F1MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F1MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F1MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F2MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F2MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F2MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F2MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F5MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F5MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F5MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F5MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F6MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F6MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F6MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F6MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Freq1QZSS_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb3Freq1QZSS->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb3Code1MeasQZSS->setEnabled(false);
        uiCSSF->comboBoxSFComb3Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb3Phase1MeasQZSS->setEnabled(false);
        uiCSSF->comboBoxSFComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb3Code1MeasQZSS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb3Code1MeasQZSS->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb3Phase1MeasQZSS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb3Phase1MeasQZSS->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F1MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F1MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F1MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F1MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F2MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F2MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F2MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F2MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F5MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F5MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F5MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F5MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F6MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F6MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F6MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F6MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F1MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F1MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F1MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F1MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F2MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F2MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F2MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F2MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F5MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F5MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F5MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F5MeasQZSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F6MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F6MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F6MeasQZSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F6MeasQZSS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F6MeasQZSS->setCurrentIndex(index);
    }
}

//IRNSS
void GNSS_CS_SF_Advanced::SetDefaultIRNSS(){
    uiCSSF->frameSFComb2IRNSS->setHidden(true);
    uiCSSF->frameSFComb3IRNSS->setHidden(true);
    uiCSSF->pushButtonSFIRNSSAdd->setEnabled(true);
    uiCSSF->pushButtonSFIRNSSDel->setEnabled(false);
    this->on_comboBoxSFComb1Freq1IRNSS_currentIndexChanged(0);
    this->on_comboBoxSFComb2Freq1IRNSS_currentIndexChanged(0);
    this->on_comboBoxSFComb3Freq1IRNSS_currentIndexChanged(0);
}
void GNSS_CS_SF_Advanced::on_pushButtonSFIRNSSAdd_clicked(){
    if (uiCSSF->frameSFComb2IRNSS->isHidden()==true){
        uiCSSF->pushButtonSFIRNSSDel->setEnabled(true);
        uiCSSF->frameSFComb2IRNSS->setHidden(false);
    } else if (uiCSSF->frameSFComb3IRNSS->isHidden()==true){
        uiCSSF->frameSFComb3IRNSS->setHidden(false);
        uiCSSF->pushButtonSFIRNSSAdd->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_pushButtonSFIRNSSDel_clicked(){
    if (uiCSSF->frameSFComb3IRNSS->isHidden()==false){
        uiCSSF->frameSFComb3IRNSS->setHidden(true);
        uiCSSF->pushButtonSFIRNSSAdd->setEnabled(true);
    } else if (uiCSSF->frameSFComb2IRNSS->isHidden()==false){
        uiCSSF->frameSFComb2IRNSS->setHidden(true);
        uiCSSF->pushButtonSFIRNSSDel->setEnabled(false);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Freq1IRNSS_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb1Freq1IRNSS->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb1Code1MeasIRNSS->setEnabled(false);
        uiCSSF->comboBoxSFComb1Code1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F9MeasIRNSS->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb1Phase1MeasIRNSS->setEnabled(false);
        uiCSSF->comboBoxSFComb1Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb1Code1MeasIRNSS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb1Code1MeasIRNSS->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb1Phase1MeasIRNSS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb1Phase1MeasIRNSS->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F5MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F9MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F5MeasIRNSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F5MeasIRNSS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F5MeasIRNSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Code1F9MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F9MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Code1F9MeasIRNSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Phase1F9MeasIRNSS->currentIndex()==0) uiCSSF->comboBoxSFComb1Phase1F9MeasIRNSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F5MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F9MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F5MeasIRNSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F5MeasIRNSS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F5MeasIRNSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb1Phase1F9MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb1Code1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Code1F9MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb1Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb1Phase1F9MeasIRNSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb1Code1F9MeasIRNSS->currentIndex()==0) uiCSSF->comboBoxSFComb1Code1F9MeasIRNSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Freq1IRNSS_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb2Freq1IRNSS->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb2Code1MeasIRNSS->setEnabled(false);
        uiCSSF->comboBoxSFComb2Code1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F9MeasIRNSS->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb2Phase1MeasIRNSS->setEnabled(false);
        uiCSSF->comboBoxSFComb2Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb2Code1MeasIRNSS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb2Code1MeasIRNSS->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb2Phase1MeasIRNSS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb2Phase1MeasIRNSS->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F5MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F9MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F5MeasIRNSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F5MeasIRNSS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F5MeasIRNSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Code1F9MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F9MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Code1F9MeasIRNSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Phase1F9MeasIRNSS->currentIndex()==0) uiCSSF->comboBoxSFComb2Phase1F9MeasIRNSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F5MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F9MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F5MeasIRNSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F5MeasIRNSS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F5MeasIRNSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb2Phase1F9MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb2Code1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Code1F9MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb2Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb2Phase1F9MeasIRNSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb2Code1F9MeasIRNSS->currentIndex()==0) uiCSSF->comboBoxSFComb2Code1F9MeasIRNSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Freq1IRNSS_currentIndexChanged(int index){
    uiCSSF->comboBoxSFComb3Freq1IRNSS->setCurrentIndex(index);
    if (index==0){
        uiCSSF->stackedWidgetSFComb3Code1MeasIRNSS->setEnabled(false);
        uiCSSF->comboBoxSFComb3Code1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F9MeasIRNSS->setCurrentIndex(0);
        uiCSSF->stackedWidgetSFComb3Phase1MeasIRNSS->setEnabled(false);
        uiCSSF->comboBoxSFComb3Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSSF->stackedWidgetSFComb3Code1MeasIRNSS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb3Code1MeasIRNSS->setCurrentIndex(index-1);
        uiCSSF->stackedWidgetSFComb3Phase1MeasIRNSS->setEnabled(true);
        uiCSSF->stackedWidgetSFComb3Phase1MeasIRNSS->setCurrentIndex(index-1);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F5MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F9MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F5MeasIRNSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F5MeasIRNSS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F5MeasIRNSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Code1F9MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F9MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Code1F9MeasIRNSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Phase1F9MeasIRNSS->currentIndex()==0) uiCSSF->comboBoxSFComb3Phase1F9MeasIRNSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F5MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F9MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F5MeasIRNSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F5MeasIRNSS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F5MeasIRNSS->setCurrentIndex(index);
    }
}
void GNSS_CS_SF_Advanced::on_comboBoxSFComb3Phase1F9MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSSF->comboBoxSFComb3Code1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Code1F9MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSSF->comboBoxSFComb3Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSSF->comboBoxSFComb3Phase1F9MeasIRNSS->setCurrentIndex(index);
        if (uiCSSF->comboBoxSFComb3Code1F9MeasIRNSS->currentIndex()==0) uiCSSF->comboBoxSFComb3Code1F9MeasIRNSS->setCurrentIndex(index);
    }
}

// Function to select GPS satellites
void GNSS_CS_SF_Advanced::changePushButtonGPS(bool checked){
    uiCSSF->pushButtonGPS->setEnabled(checked);
    this->SetDefaultGPS();
}
// Function to select Galileo satellites
void GNSS_CS_SF_Advanced::changePushButtonGalileo(bool checked){
    uiCSSF->pushButtonGalileo->setEnabled(checked);
    this->SetDefaultGalileo();
}
// Function to select GLONASS satellites
void GNSS_CS_SF_Advanced::changePushButtonGLONASS(bool checked){
    uiCSSF->pushButtonGLONASS->setEnabled(checked);
    this->SetDefaultGLONASS();
}
// Function to select GEO satellites
void GNSS_CS_SF_Advanced::changePushButtonGEO(bool checked){
    uiCSSF->pushButtonGEO->setEnabled(checked);
    this->SetDefaultGEO();
}
// Function to select BDS satellites
void GNSS_CS_SF_Advanced::changePushButtonBDS(bool checked){
    uiCSSF->pushButtonBDS->setEnabled(checked);
    this->SetDefaultBDS();
}
// Function to select QZSS satellites
void GNSS_CS_SF_Advanced::changePushButtonQZSS(bool checked){
    uiCSSF->pushButtonQZSS->setEnabled(checked);
    this->SetDefaultQZSS();
}
// Function to select IRNSS satellites
void GNSS_CS_SF_Advanced::changePushButtonIRNSS(bool checked){
    uiCSSF->pushButtonIRNSS->setEnabled(checked);
    this->SetDefaultIRNSS();
}

// Function to configure GPS satellites
void GNSS_CS_SF_Advanced::on_pushButtonPublicGPS_clicked(){
    this->on_pushButtonGPS_clicked();
}
// Function to configure Galileo satellites
void GNSS_CS_SF_Advanced::on_pushButtonPublicGalileo_clicked(){
    this->on_pushButtonGalileo_clicked();
}
// Function to configure GLONASS satellites
void GNSS_CS_SF_Advanced::on_pushButtonPublicGLONASS_clicked(){
    this->on_pushButtonGLONASS_clicked();
}
// Function to configure GEO satellites
void GNSS_CS_SF_Advanced::on_pushButtonPublicGEO_clicked(){
    this->on_pushButtonGEO_clicked();
}
// Function to configure BDS satellites
void GNSS_CS_SF_Advanced::on_pushButtonPublicBDS_clicked(){
    this->on_pushButtonBDS_clicked();
}
// Function to configure QZSS satellites
void GNSS_CS_SF_Advanced::on_pushButtonPublicQZSS_clicked(){
    this->on_pushButtonQZSS_clicked();
}
// Function to configure IRNSS satellites
void GNSS_CS_SF_Advanced::on_pushButtonPublicIRNSS_clicked(){
    this->on_pushButtonIRNSS_clicked();
}

void GNSS_CS_SF_Advanced::changeCurrentPage(){
    for (int i=0; i<MAX_GNSS; i++){
        if (PushButtonGNSS[i]->isEnabled()){
            (this->*PushButtonGNSSFunctions[i])();
            break;
        }
    }
}

//Function to get SF command options
int GNSS_CS_SF_Advanced::getgLABOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString){
    QString freqOption="",measOption="";
    QStringList freqOptionList, measOptionList;
    int paramCount=0;
    int numFreqOptionList=0, numMeasOptionList=0;
    int skipIteration[MAX_GNSS][3]={{0}};
    int multipleAuto[MAX_GNSS]={0};
    if (warningString->length()<0) *warningString=""; //only to avoid the warning of unused "warningString"
    if (errorString->length()<0) *errorString=""; //only to avoid the warning of unused "warningString"
    //loop of constellations
    for (int gnssi=0; gnssi<MAX_GNSS; gnssi++){

        //Look for repeated combinations in iteration 2
        if (FrameCombGNSS[gnssi][1]->isHidden()==false) {
            if ( ComboBoxFreqGNSS[gnssi][1]->currentIndex()==0 && ComboBoxFreqGNSS[gnssi][0]->currentIndex()==0){
                *warningString += "PREPROCESS: " + GNSSName[gnssi] + " constellation in Phase-Code cycle-slip detector has multiple 'Auto' iterations, but only one will be applied. Set only one 'Auto' iteration.\n";
                skipIteration[gnssi][1]=1;
                multipleAuto[gnssi]=1;
            } else if (ComboBoxFreqGNSS[gnssi][1]->currentIndex()!=0 && ComboBoxFreqGNSS[gnssi][0]->currentIndex()!=0) {
                int freq1=ComboBoxFreqGNSS[gnssi][1]->currentIndex()-1;
                int freq0=ComboBoxFreqGNSS[gnssi][0]->currentIndex()-1;
                if (freq1==freq0) {
                    if (ComboBoxMeasGNSS[gnssi][1][0][freq1]->currentIndex()==ComboBoxMeasGNSS[gnssi][0][0][freq0]->currentIndex()
                            && ComboBoxMeasGNSS[gnssi][1][1][freq1]->currentIndex()==ComboBoxMeasGNSS[gnssi][0][1][freq0]->currentIndex() ) {
                        *warningString += "PREPROCESS: " + GNSSName[gnssi] + " constellation in Phase-Code cycle-slip detector has iterations 1 and 2 repeated. They will be used only once.\n";
                        skipIteration[gnssi][1]=1;
                    }
                }
            }
            if (FrameCombGNSS[gnssi][2]->isHidden()==false) {
                if ( ComboBoxFreqGNSS[gnssi][1]->currentIndex()==0 && ComboBoxFreqGNSS[gnssi][2]->currentIndex()==0 ) {
                    if (multipleAuto[gnssi]==0) {
                        *warningString += "PREPROCESS: " + GNSSName[gnssi] + " constellation in Phase-Code cycle-slip detector has multiple 'Auto' iterations, but only one will be applied. Set only one 'Auto' iteration.\n";
                    }
                    skipIteration[gnssi][2]=1;
                    multipleAuto[gnssi]=1;
                } else if (ComboBoxFreqGNSS[gnssi][1]->currentIndex()!=0 && ComboBoxFreqGNSS[gnssi][2]->currentIndex()!=0) {
                    int freq1=ComboBoxFreqGNSS[gnssi][1]->currentIndex()-1;
                    int freq0=ComboBoxFreqGNSS[gnssi][2]->currentIndex()-1;
                    if (freq1==freq0) {
                        if (ComboBoxMeasGNSS[gnssi][1][0][freq1]->currentIndex()==ComboBoxMeasGNSS[gnssi][2][0][freq0]->currentIndex()
                                && ComboBoxMeasGNSS[gnssi][1][1][freq1]->currentIndex()==ComboBoxMeasGNSS[gnssi][2][1][freq0]->currentIndex() ) {
                            *warningString += "PREPROCESS: " + GNSSName[gnssi] + " constellation in Phase-Code cycle-slip detector has iterations 2 and 3 repeated. They will be used only once.\n";
                            skipIteration[gnssi][2]=1;
                        }
                    }
                }
            }
        }
        //Look for repeated combinations in iteration 3
        if (FrameCombGNSS[gnssi][2]->isHidden()==false && skipIteration[gnssi][2]==0 ) {
            if ( ComboBoxFreqGNSS[gnssi][2]->currentIndex()==0 && ComboBoxFreqGNSS[gnssi][0]->currentIndex()==0) {
                if (multipleAuto[gnssi]==0) {
                    *warningString += "PREPROCESS: " + GNSSName[gnssi] + " constellation in Phase-Code cycle-slip detector has multiple 'Auto' iterations, but only one will be applied. Set only one 'Auto' iteration.\n";
                }
                skipIteration[gnssi][2]=1;
                multipleAuto[gnssi]=1;
            } else if (ComboBoxFreqGNSS[gnssi][2]->currentIndex()!=0 && ComboBoxFreqGNSS[gnssi][0]->currentIndex()!=0) {
                int freq1=ComboBoxFreqGNSS[gnssi][2]->currentIndex()-1;
                int freq0=ComboBoxFreqGNSS[gnssi][0]->currentIndex()-1;
                if (freq1==freq0) {
                    if (ComboBoxMeasGNSS[gnssi][2][0][freq1]->currentIndex()==ComboBoxMeasGNSS[gnssi][0][0][freq0]->currentIndex()
                            && ComboBoxMeasGNSS[gnssi][2][1][freq1]->currentIndex()==ComboBoxMeasGNSS[gnssi][0][1][freq0]->currentIndex() ) {
                        *warningString += "PREPROCESS: " + GNSSName[gnssi] + " constellation in Phase-Code cycle-slip detector has iterations 1 and 3 repeated. They will be used only once.\n";
                        skipIteration[gnssi][2]=1;
                    }
                }
            }
        }
        //loop of combinations
        int freqflag=0;
        for (int combi=0; combi<3; combi++){
            if (skipIteration[gnssi][combi]==1) continue; //Skip repetead combinations
            //get options if not hidden and frequency is specified
            if (FrameCombGNSS[gnssi][combi]->isHidden()==false && ComboBoxFreqGNSS[gnssi][combi]->currentIndex()!=0){
                int freqi=ComboBoxFreqGNSS[gnssi][combi]->currentIndex()-1;
                //only specify frequency
                if (ComboBoxMeasGNSS[gnssi][combi][0][freqi]->currentIndex()==0){
                    if (freqflag==0){
                        freqOption += " " + indentifierGNSS[gnssi] + "0-" + FreqGNSSList[gnssi][freqi];
                        freqflag=1;
                    } else {
                        freqOption += "." + FreqGNSSList[gnssi][freqi];
                    }
                }
                //specify both frequency and measurement
                else {
                    measOption += " " + indentifierGNSS[gnssi] + "0-" + ComboBoxMeasGNSS[gnssi][combi][0][freqi]->currentText() + "-" + ComboBoxMeasGNSS[gnssi][combi][1][freqi]->currentText();
                }
            }
        }
    }

    //Merge by constellation frequency parameters
    freqOptionList = freqOption.split(QRegularExpression("\\s+"));
    numFreqOptionList = freqOptionList.count();
    for(int Param=0;Param<numFreqOptionList;Param++) {
        for(int Param2=0;Param2<numFreqOptionList;Param2++) {
            if (Param==Param2) continue;
            if (freqOptionList[Param]=="" || freqOptionList[Param2]=="") continue;
            int pos1,pos2;
            pos1=freqOptionList[Param].indexOf("-")+1;
            pos2=freqOptionList[Param2].indexOf("-")+1;

            if (QString::compare(freqOptionList[Param].mid(pos1),freqOptionList[Param2].mid(pos2))==0 ) {
                freqOptionList[Param].insert(pos1-2,freqOptionList[Param2].left(1));
                freqOptionList[Param2]="";
            }
        }
    }

    //Merge by constellation meas parameters
    measOptionList = measOption.split(QRegularExpression("\\s+"));
    numMeasOptionList = measOptionList.count();
    for(int Param=0;Param<numMeasOptionList;Param++) {
        for(int Param2=0;Param2<numMeasOptionList;Param2++) {
            if (Param==Param2) continue;
            if (measOptionList[Param]=="" || measOptionList[Param2]=="") continue;
            int pos1,pos2;
            pos1=measOptionList[Param].indexOf("-")+1;
            pos2=measOptionList[Param2].indexOf("-")+1;

            if (QString::compare(measOptionList[Param].mid(pos1),measOptionList[Param2].mid(pos2))==0 ) {
                measOptionList[Param].insert(pos1-2,measOptionList[Param2].left(1));
                measOptionList[Param2]="";
            }
        }
    }

    //-pre:cs:sf:freq
    int firstArg=1;
    for(int Param=0;Param<numFreqOptionList;Param++) {
        if (freqOptionList[Param]=="") continue;
        if (firstArg==1) {
            firstArg=0;
            *saveString += "-pre:cs:sf:freq";
            *runString << "-pre:cs:sf:freq";
        }
        *saveString += " " + freqOptionList[Param];
        *runString << freqOptionList[Param];
        paramCount++;
    }
    if (firstArg==0) *saveString += "\n";

    //-pre:cs:sf:meas
    firstArg=1;
    for(int Param=0;Param<numMeasOptionList;Param++) {
        if (measOptionList[Param]=="") continue;
        if (firstArg==1) {
            firstArg=0;
            *saveString += "-pre:cs:sf:meas";
            *runString << "-pre:cs:sf:meas";
        }
        *saveString += " " + measOptionList[Param];
        *runString << measOptionList[Param];
        paramCount++;
    }
    if (firstArg==0) *saveString += "\n";

    return paramCount;
}
//Function to convert SF command options to GUI configuration
void GNSS_CS_SF_Advanced::loadgLABOptions(QString *warningString, QStringList *ParametersList, const int freqMeas){
    int setCount[MAX_GNSS]={0};
    int nPar=ParametersList->count();
    if (warningString->length()<0) *warningString=""; //only to avoid the warning of unused "warningString"
    //get former set
    for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++){
        for (int icomb=0; icomb<3; icomb++){
            if (ComboBoxFreqGNSS[iGNSS][icomb]->currentIndex()>0) setCount[iGNSS]=icomb+1;
        }
    }
    //frequency
    if (freqMeas==1){
        //loop parameters
        for (int iPar=0; iPar<nPar; iPar++){
            int iGNSS=-1;
            //Check parameter
            if (checkUserInputCycleSlipMeasurement(warningString,ParametersList->at(iPar),CStypeSF,CStypeParamFreq,nullptr)) continue;
            //find frequency list
            QStringList FreqParList = ParametersList->at(iPar).split("-", QString::SkipEmptyParts);
            //get constellation
            for (iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
                if (!FreqParList[0].toUpper().contains(indentifierGNSS[iGNSS]) && FreqParList[0]!="0" ) continue;
                QStringList freqComb = FreqParList.last().split(".",QString::SkipEmptyParts);
                //loop frequency
                for (int iCom=0; iCom<freqComb.count(); iCom++){
                    if (setCount[iGNSS]>2) {
                        *warningString += "PREPROCESS: Maximum number of iterations for " + GNSSName[iGNSS] + " SF cycle-slip detector is 3. Argument '" + ParametersList->at(iPar) + "' was skipped for " + GNSSName[iGNSS] + " as limit has been surpassed.\n";
                        break;
                    }
                    if (freqComb[iCom].size()!=1) continue;
                    int freq1=-1;
                    //get 2 frequencies
                    for (int ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                        if (freqComb[iCom]==FreqGNSSList[iGNSS][ifreq]) {
                            freq1=ifreq;
                            break;
                        }
                    }
                    if ( freq1<0 ) {
                        *warningString += "PREPROCESS: SF cycle-slip frequency '" + freqComb[iCom] + "' in argument '" + ParametersList->at(iPar) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    }
                    FrameCombGNSS[iGNSS][setCount[iGNSS]]->setHidden(false);
                    ComboBoxFreqGNSS[iGNSS][setCount[iGNSS]]->setCurrentIndex(freq1+1);
                    setCount[iGNSS]++;
                }
            }
        }
    }
    //measurement
    else {
        //loop parameters
        for (int iPar=0; iPar<nPar; iPar++){
            int iGNSS=-1,measStart=0;
            //Check parameter
            if (checkUserInputCycleSlipMeasurement(warningString,ParametersList->at(iPar),CStypeSF,CStypeParamMeas,nullptr)) continue;
            //find measurement list
            QStringList MeasParList = ParametersList->at(iPar).split("-", QString::SkipEmptyParts);
            measStart=MeasParList.count()-2;
            if (measStart<1) continue;
            //get constellation
            for (iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
                if (!MeasParList[0].toUpper().contains(indentifierGNSS[iGNSS]) && MeasParList[0]!="0" ) continue;
                if ( setCount[iGNSS]>2 ) {
                    *warningString += "PREPROCESS: Maximum number of iterations for " + GNSSName[iGNSS] + " SF cycle-slip detector is 3. Argument '" + ParametersList->at(iPar) + "' was skipped for " + GNSSName[iGNSS] + " as limit has been surpassed.\n";
                    continue;
                }
                //get frequency & measurement
                int freq12[2]={-1,-1},meas12[2]={-1,-1};
                for (int iFM=0; iFM<2; iFM++){
                    int iPC=-1;
                    if (MeasParList[measStart+iFM].size()!=3) break;
                    if (MeasParList[measStart+iFM].toUpper().mid(0,1)=="C") iPC=0;
                    else if (MeasParList[measStart+iFM].toUpper().mid(0,1)=="L") iPC=1;
                    else break;
                    for (int ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                        if (MeasParList[measStart+iFM].mid(1,1)==FreqGNSSList[iGNSS][ifreq]) {
                            freq12[iPC]=ifreq;
                            break;
                        }
                    }
                    if ( freq12[iPC]<0 ) {
                        *warningString += "PREPROCESS: Frequency '" + MeasParList[measStart+iFM].mid(1,1) + "' in measurement '" + MeasParList[measStart+iFM] + "' in argument '" + ParametersList->at(iPar) + "' for SF cycle-slip detector does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        break;
                    }
                    for (int imeas=0; imeas<MeasGNSSOrder[iGNSS][freq12[iPC]].size(); imeas++){
                        if (MeasParList[measStart+iFM].toUpper().mid(2,1)==MeasGNSSOrder[iGNSS][freq12[iPC]].mid(imeas,1)) {
                            meas12[iPC]=imeas;
                            break;
                        }
                    }
                    if (meas12[iPC]<0) {
                        *warningString += "PREPROCESS: Measurement '" + MeasParList[measStart+iFM] + "' in argument '" + ParametersList->at(iPar) + "' for SF cycle-slip detector does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                    }
                }
                if ( freq12[0]<0 || freq12[1]<0 || meas12[0]<0 || meas12[1]<0 || freq12[0]!=freq12[1] ) continue;
                FrameCombGNSS[iGNSS][setCount[iGNSS]]->setHidden(false);
                ComboBoxFreqGNSS[iGNSS][setCount[iGNSS]]->setCurrentIndex(freq12[0]+1);
                ComboBoxMeasGNSS[iGNSS][setCount[iGNSS]][0][freq12[0]]->setCurrentIndex(meas12[0]+1);
                ComboBoxMeasGNSS[iGNSS][setCount[iGNSS]][1][freq12[1]]->setCurrentIndex(meas12[1]+1);
                setCount[iGNSS]++;
            }
        }
    }
    //Change to Galileo constellation and then back to GPS to make sure "+" and "-" are in consistent state
    this->on_pushButtonGalileo_clicked();
    this->on_pushButtonGPS_clicked();
}

void GNSS_CS_SF_Advanced::on_pushButtonCSSFAdvancedDefault_clicked(){
    setCSdefaults();
}
void GNSS_CS_SF_Advanced::on_pushButtonCSSFAdvancedOk_clicked(){
    this->OkFlag=1;
    this->close();
}
void GNSS_CS_SF_Advanced::on_pushButtonCSSFAdvancedCancel_clicked(){
    this->OkFlag=0;
    this->close();
}
