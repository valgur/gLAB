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
#include "cs_li_advanced.h"
#include "ui_cs_li_advanced.h"

GNSS_CS_LI_Advanced::GNSS_CS_LI_Advanced(QWidget *parent) :
    QDialog(parent),
    uiCSLI(new Ui::GNSS_CS_LI_Advanced)
{
    uiCSLI->setupUi(this);

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

    this->setWindowTitle("GF Cycle-Slip Detection Advanced Configuration");
    this->InitPushButtonGNSSPointers();
    this->InitPushButtonGNSSMinFuncPointers();
    this->InitCombinationPointers();
    this->setCSdefaults();

    uiCSLI->pushButtonCSLIAdvancedOk->setFocus();

    uiCSLI->pushButtonCSLIAdvancedCancel->setHidden(true); //Remove when Cancel buttons undo all changes made by the user
}

GNSS_CS_LI_Advanced::~GNSS_CS_LI_Advanced()
{
    delete uiCSLI;
}

//Function to initialize pointers to CheckBox widget pointers
void GNSS_CS_LI_Advanced::InitPushButtonGNSSPointers(){
    PushButtonGNSS[GPS]=uiCSLI->pushButtonGPS;
    PushButtonGNSS[Galileo]=uiCSLI->pushButtonGalileo;
    PushButtonGNSS[GLONASS]=uiCSLI->pushButtonGLONASS;
    PushButtonGNSS[GEO]=uiCSLI->pushButtonGEO;
    PushButtonGNSS[BDS]=uiCSLI->pushButtonBDS;
    PushButtonGNSS[QZSS]=uiCSLI->pushButtonQZSS;
    PushButtonGNSS[IRNSS]=uiCSLI->pushButtonIRNSS;
}

//Function to initialize pointers to pushButton GNSS Measurements _clicked() functions
void GNSS_CS_LI_Advanced::InitPushButtonGNSSMinFuncPointers(){
    PushButtonGNSSFunctions[GPS]=&GNSS_CS_LI_Advanced::on_pushButtonGPS_clicked;
    PushButtonGNSSFunctions[Galileo]=&GNSS_CS_LI_Advanced::on_pushButtonGalileo_clicked;
    PushButtonGNSSFunctions[GLONASS]=&GNSS_CS_LI_Advanced::on_pushButtonGLONASS_clicked;
    PushButtonGNSSFunctions[GEO]=&GNSS_CS_LI_Advanced::on_pushButtonGEO_clicked;
    PushButtonGNSSFunctions[BDS]=&GNSS_CS_LI_Advanced::on_pushButtonBDS_clicked;
    PushButtonGNSSFunctions[QZSS]=&GNSS_CS_LI_Advanced::on_pushButtonQZSS_clicked;
    PushButtonGNSSFunctions[IRNSS]=&GNSS_CS_LI_Advanced::on_pushButtonIRNSS_clicked;
}

void GNSS_CS_LI_Advanced::InitCombinationPointers(){
    //GPS
    //combination Frame
    FrameCombGNSS[GPS][0]=uiCSLI->frameLIComb1GPS;
    FrameCombGNSS[GPS][1]=uiCSLI->frameLIComb2GPS;
    FrameCombGNSS[GPS][2]=uiCSLI->frameLIComb3GPS;
    //frequency ComboBox
    ComboBoxFreqGNSS[GPS][0][0]=uiCSLI->comboBoxLIComb1Freq1GPS;
    ComboBoxFreqGNSS[GPS][1][0]=uiCSLI->comboBoxLIComb2Freq1GPS;
    ComboBoxFreqGNSS[GPS][2][0]=uiCSLI->comboBoxLIComb3Freq1GPS;
    ComboBoxFreqGNSS[GPS][0][1]=uiCSLI->comboBoxLIComb1Freq2GPS;
    ComboBoxFreqGNSS[GPS][1][1]=uiCSLI->comboBoxLIComb2Freq2GPS;
    ComboBoxFreqGNSS[GPS][2][1]=uiCSLI->comboBoxLIComb3Freq2GPS;
    //measurement ComboBox Comb1 Phase1
    ComboBoxMeasGNSS[GPS][0][0][0]=uiCSLI->comboBoxLIComb1Phase1F1MeasGPS;
    ComboBoxMeasGNSS[GPS][0][0][1]=uiCSLI->comboBoxLIComb1Phase1F2MeasGPS;
    ComboBoxMeasGNSS[GPS][0][0][2]=uiCSLI->comboBoxLIComb1Phase1F5MeasGPS;
    //measurement ComboBox Comb1 Phase2
    ComboBoxMeasGNSS[GPS][0][1][0]=uiCSLI->comboBoxLIComb1Phase2F1MeasGPS;
    ComboBoxMeasGNSS[GPS][0][1][1]=uiCSLI->comboBoxLIComb1Phase2F2MeasGPS;
    ComboBoxMeasGNSS[GPS][0][1][2]=uiCSLI->comboBoxLIComb1Phase2F5MeasGPS;
    //measurement ComboBox Comb2 Phase1
    ComboBoxMeasGNSS[GPS][1][0][0]=uiCSLI->comboBoxLIComb2Phase1F1MeasGPS;
    ComboBoxMeasGNSS[GPS][1][0][1]=uiCSLI->comboBoxLIComb2Phase1F2MeasGPS;
    ComboBoxMeasGNSS[GPS][1][0][2]=uiCSLI->comboBoxLIComb2Phase1F5MeasGPS;
    //measurement ComboBox Comb2 Phase2
    ComboBoxMeasGNSS[GPS][1][1][0]=uiCSLI->comboBoxLIComb2Phase2F1MeasGPS;
    ComboBoxMeasGNSS[GPS][1][1][1]=uiCSLI->comboBoxLIComb2Phase2F2MeasGPS;
    ComboBoxMeasGNSS[GPS][1][1][2]=uiCSLI->comboBoxLIComb2Phase2F5MeasGPS;
    //measurement ComboBox Comb3 Phase1
    ComboBoxMeasGNSS[GPS][2][0][0]=uiCSLI->comboBoxLIComb3Phase1F1MeasGPS;
    ComboBoxMeasGNSS[GPS][2][0][1]=uiCSLI->comboBoxLIComb3Phase1F2MeasGPS;
    ComboBoxMeasGNSS[GPS][2][0][2]=uiCSLI->comboBoxLIComb3Phase1F5MeasGPS;
    //measurement ComboBox Comb3 Phase2
    ComboBoxMeasGNSS[GPS][2][1][0]=uiCSLI->comboBoxLIComb3Phase2F1MeasGPS;
    ComboBoxMeasGNSS[GPS][2][1][1]=uiCSLI->comboBoxLIComb3Phase2F2MeasGPS;
    ComboBoxMeasGNSS[GPS][2][1][2]=uiCSLI->comboBoxLIComb3Phase2F5MeasGPS;

    //Galileo
    //combination Frame
    FrameCombGNSS[Galileo][0]=uiCSLI->frameLIComb1Galileo;
    FrameCombGNSS[Galileo][1]=uiCSLI->frameLIComb2Galileo;
    FrameCombGNSS[Galileo][2]=uiCSLI->frameLIComb3Galileo;
    //frequency ComboBox
    ComboBoxFreqGNSS[Galileo][0][0]=uiCSLI->comboBoxLIComb1Freq1Galileo;
    ComboBoxFreqGNSS[Galileo][1][0]=uiCSLI->comboBoxLIComb2Freq1Galileo;
    ComboBoxFreqGNSS[Galileo][2][0]=uiCSLI->comboBoxLIComb3Freq1Galileo;
    ComboBoxFreqGNSS[Galileo][0][1]=uiCSLI->comboBoxLIComb1Freq2Galileo;
    ComboBoxFreqGNSS[Galileo][1][1]=uiCSLI->comboBoxLIComb2Freq2Galileo;
    ComboBoxFreqGNSS[Galileo][2][1]=uiCSLI->comboBoxLIComb3Freq2Galileo;
    //measurement ComboBox Comb1 Phase1
    ComboBoxMeasGNSS[Galileo][0][0][0]=uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo;
    ComboBoxMeasGNSS[Galileo][0][0][1]=uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo;
    ComboBoxMeasGNSS[Galileo][0][0][2]=uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo;
    ComboBoxMeasGNSS[Galileo][0][0][3]=uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo;
    ComboBoxMeasGNSS[Galileo][0][0][4]=uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo;
    //measurement ComboBox Comb1 Phase2
    ComboBoxMeasGNSS[Galileo][0][1][0]=uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo;
    ComboBoxMeasGNSS[Galileo][0][1][1]=uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo;
    ComboBoxMeasGNSS[Galileo][0][1][2]=uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo;
    ComboBoxMeasGNSS[Galileo][0][1][3]=uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo;
    ComboBoxMeasGNSS[Galileo][0][1][4]=uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo;
    //measurement ComboBox Comb2 Phase1
    ComboBoxMeasGNSS[Galileo][1][0][0]=uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo;
    ComboBoxMeasGNSS[Galileo][1][0][1]=uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo;
    ComboBoxMeasGNSS[Galileo][1][0][2]=uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo;
    ComboBoxMeasGNSS[Galileo][1][0][3]=uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo;
    ComboBoxMeasGNSS[Galileo][1][0][4]=uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo;
    //measurement ComboBox Comb2 Phase2
    ComboBoxMeasGNSS[Galileo][1][1][0]=uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo;
    ComboBoxMeasGNSS[Galileo][1][1][1]=uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo;
    ComboBoxMeasGNSS[Galileo][1][1][2]=uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo;
    ComboBoxMeasGNSS[Galileo][1][1][3]=uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo;
    ComboBoxMeasGNSS[Galileo][1][1][4]=uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo;
    //measurement ComboBox Comb3 Phase1
    ComboBoxMeasGNSS[Galileo][2][0][0]=uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo;
    ComboBoxMeasGNSS[Galileo][2][0][1]=uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo;
    ComboBoxMeasGNSS[Galileo][2][0][2]=uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo;
    ComboBoxMeasGNSS[Galileo][2][0][3]=uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo;
    ComboBoxMeasGNSS[Galileo][2][0][4]=uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo;
    //measurement ComboBox Comb3 Phase2
    ComboBoxMeasGNSS[Galileo][2][1][0]=uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo;
    ComboBoxMeasGNSS[Galileo][2][1][1]=uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo;
    ComboBoxMeasGNSS[Galileo][2][1][2]=uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo;
    ComboBoxMeasGNSS[Galileo][2][1][3]=uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo;
    ComboBoxMeasGNSS[Galileo][2][1][4]=uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo;

    //GLONASS
    //combination Frame
    FrameCombGNSS[GLONASS][0]=uiCSLI->frameLIComb1GLONASS;
    FrameCombGNSS[GLONASS][1]=uiCSLI->frameLIComb2GLONASS;
    FrameCombGNSS[GLONASS][2]=uiCSLI->frameLIComb3GLONASS;
    //frequency ComboBox
    ComboBoxFreqGNSS[GLONASS][0][0]=uiCSLI->comboBoxLIComb1Freq1GLONASS;
    ComboBoxFreqGNSS[GLONASS][1][0]=uiCSLI->comboBoxLIComb2Freq1GLONASS;
    ComboBoxFreqGNSS[GLONASS][2][0]=uiCSLI->comboBoxLIComb3Freq1GLONASS;
    ComboBoxFreqGNSS[GLONASS][0][1]=uiCSLI->comboBoxLIComb1Freq2GLONASS;
    ComboBoxFreqGNSS[GLONASS][1][1]=uiCSLI->comboBoxLIComb2Freq2GLONASS;
    ComboBoxFreqGNSS[GLONASS][2][1]=uiCSLI->comboBoxLIComb3Freq2GLONASS;
    //measurement ComboBox Comb1 Phase1
    ComboBoxMeasGNSS[GLONASS][0][0][0]=uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][0][0][1]=uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][0][0][2]=uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][0][0][3]=uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][0][0][4]=uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS;
    //measurement ComboBox Comb1 Phase2
    ComboBoxMeasGNSS[GLONASS][0][1][0]=uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][0][1][1]=uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][0][1][2]=uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][0][1][3]=uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][0][1][4]=uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS;
    //measurement ComboBox Comb2 Phase1
    ComboBoxMeasGNSS[GLONASS][1][0][0]=uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][1][0][1]=uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][1][0][2]=uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][1][0][3]=uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][1][0][4]=uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS;
    //measurement ComboBox Comb2 Phase2
    ComboBoxMeasGNSS[GLONASS][1][1][0]=uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][1][1][1]=uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][1][1][2]=uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][1][1][3]=uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][1][1][4]=uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS;
    //measurement ComboBox Comb3 Phase1
    ComboBoxMeasGNSS[GLONASS][2][0][0]=uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][2][0][1]=uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][2][0][2]=uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][2][0][3]=uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][2][0][4]=uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS;
    //measurement ComboBox Comb3 Phase2
    ComboBoxMeasGNSS[GLONASS][2][1][0]=uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][2][1][1]=uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][2][1][2]=uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][2][1][3]=uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS;
    ComboBoxMeasGNSS[GLONASS][2][1][4]=uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS;

    //GEO
    //combination Frame
    FrameCombGNSS[GEO][0]=uiCSLI->frameLIComb1GEO;
    FrameCombGNSS[GEO][1]=uiCSLI->frameLIComb2GEO;
    FrameCombGNSS[GEO][2]=uiCSLI->frameLIComb3GEO;
    //frequency ComboBox
    ComboBoxFreqGNSS[GEO][0][0]=uiCSLI->comboBoxLIComb1Freq1GEO;
    ComboBoxFreqGNSS[GEO][1][0]=uiCSLI->comboBoxLIComb2Freq1GEO;
    ComboBoxFreqGNSS[GEO][2][0]=uiCSLI->comboBoxLIComb3Freq1GEO;
    ComboBoxFreqGNSS[GEO][0][1]=uiCSLI->comboBoxLIComb1Freq2GEO;
    ComboBoxFreqGNSS[GEO][1][1]=uiCSLI->comboBoxLIComb2Freq2GEO;
    ComboBoxFreqGNSS[GEO][2][1]=uiCSLI->comboBoxLIComb3Freq2GEO;
    //measurement ComboBox Comb1 Phase1
    ComboBoxMeasGNSS[GEO][0][0][0]=uiCSLI->comboBoxLIComb1Phase1F1MeasGEO;
    ComboBoxMeasGNSS[GEO][0][0][1]=uiCSLI->comboBoxLIComb1Phase1F5MeasGEO;
    //measurement ComboBox Comb1 Phase2
    ComboBoxMeasGNSS[GEO][0][1][0]=uiCSLI->comboBoxLIComb1Phase2F1MeasGEO;
    ComboBoxMeasGNSS[GEO][0][1][1]=uiCSLI->comboBoxLIComb1Phase2F5MeasGEO;
    //measurement ComboBox Comb2 Phase1
    ComboBoxMeasGNSS[GEO][1][0][0]=uiCSLI->comboBoxLIComb2Phase1F1MeasGEO;
    ComboBoxMeasGNSS[GEO][1][0][1]=uiCSLI->comboBoxLIComb2Phase1F5MeasGEO;
    //measurement ComboBox Comb2 Phase2
    ComboBoxMeasGNSS[GEO][1][1][0]=uiCSLI->comboBoxLIComb2Phase2F1MeasGEO;
    ComboBoxMeasGNSS[GEO][1][1][1]=uiCSLI->comboBoxLIComb2Phase2F5MeasGEO;
    //measurement ComboBox Comb3 Phase1
    ComboBoxMeasGNSS[GEO][2][0][0]=uiCSLI->comboBoxLIComb3Phase1F1MeasGEO;
    ComboBoxMeasGNSS[GEO][2][0][1]=uiCSLI->comboBoxLIComb3Phase1F5MeasGEO;
    //measurement ComboBox Comb3 Phase2
    ComboBoxMeasGNSS[GEO][2][1][0]=uiCSLI->comboBoxLIComb3Phase2F1MeasGEO;
    ComboBoxMeasGNSS[GEO][2][1][1]=uiCSLI->comboBoxLIComb3Phase2F5MeasGEO;

    //BDS
    //combination Frame
    FrameCombGNSS[BDS][0]=uiCSLI->frameLIComb1BDS;
    FrameCombGNSS[BDS][1]=uiCSLI->frameLIComb2BDS;
    FrameCombGNSS[BDS][2]=uiCSLI->frameLIComb3BDS;
    //frequency ComboBox
    ComboBoxFreqGNSS[BDS][0][0]=uiCSLI->comboBoxLIComb1Freq1BDS;
    ComboBoxFreqGNSS[BDS][1][0]=uiCSLI->comboBoxLIComb2Freq1BDS;
    ComboBoxFreqGNSS[BDS][2][0]=uiCSLI->comboBoxLIComb3Freq1BDS;
    ComboBoxFreqGNSS[BDS][0][1]=uiCSLI->comboBoxLIComb1Freq2BDS;
    ComboBoxFreqGNSS[BDS][1][1]=uiCSLI->comboBoxLIComb2Freq2BDS;
    ComboBoxFreqGNSS[BDS][2][1]=uiCSLI->comboBoxLIComb3Freq2BDS;
    //measurement ComboBox Comb1 Phase1
    ComboBoxMeasGNSS[BDS][0][0][0]=uiCSLI->comboBoxLIComb1Phase1F1MeasBDS;
    ComboBoxMeasGNSS[BDS][0][0][1]=uiCSLI->comboBoxLIComb1Phase1F2MeasBDS;
    ComboBoxMeasGNSS[BDS][0][0][2]=uiCSLI->comboBoxLIComb1Phase1F5MeasBDS;
    ComboBoxMeasGNSS[BDS][0][0][3]=uiCSLI->comboBoxLIComb1Phase1F6MeasBDS;
    ComboBoxMeasGNSS[BDS][0][0][4]=uiCSLI->comboBoxLIComb1Phase1F7MeasBDS;
    ComboBoxMeasGNSS[BDS][0][0][5]=uiCSLI->comboBoxLIComb1Phase1F8MeasBDS;
    //measurement ComboBox Comb1 Phase2
    ComboBoxMeasGNSS[BDS][0][1][0]=uiCSLI->comboBoxLIComb1Phase2F1MeasBDS;
    ComboBoxMeasGNSS[BDS][0][1][1]=uiCSLI->comboBoxLIComb1Phase2F2MeasBDS;
    ComboBoxMeasGNSS[BDS][0][1][2]=uiCSLI->comboBoxLIComb1Phase2F5MeasBDS;
    ComboBoxMeasGNSS[BDS][0][1][3]=uiCSLI->comboBoxLIComb1Phase2F6MeasBDS;
    ComboBoxMeasGNSS[BDS][0][1][4]=uiCSLI->comboBoxLIComb1Phase2F7MeasBDS;
    ComboBoxMeasGNSS[BDS][0][1][5]=uiCSLI->comboBoxLIComb1Phase2F8MeasBDS;
    //measurement ComboBox Comb2 Phase1
    ComboBoxMeasGNSS[BDS][1][0][0]=uiCSLI->comboBoxLIComb2Phase1F1MeasBDS;
    ComboBoxMeasGNSS[BDS][1][0][1]=uiCSLI->comboBoxLIComb2Phase1F2MeasBDS;
    ComboBoxMeasGNSS[BDS][1][0][2]=uiCSLI->comboBoxLIComb2Phase1F5MeasBDS;
    ComboBoxMeasGNSS[BDS][1][0][3]=uiCSLI->comboBoxLIComb2Phase1F6MeasBDS;
    ComboBoxMeasGNSS[BDS][1][0][4]=uiCSLI->comboBoxLIComb2Phase1F7MeasBDS;
    ComboBoxMeasGNSS[BDS][1][0][5]=uiCSLI->comboBoxLIComb2Phase1F8MeasBDS;
    //measurement ComboBox Comb2 Phase2
    ComboBoxMeasGNSS[BDS][1][1][0]=uiCSLI->comboBoxLIComb2Phase2F1MeasBDS;
    ComboBoxMeasGNSS[BDS][1][1][1]=uiCSLI->comboBoxLIComb2Phase2F2MeasBDS;
    ComboBoxMeasGNSS[BDS][1][1][2]=uiCSLI->comboBoxLIComb2Phase2F5MeasBDS;
    ComboBoxMeasGNSS[BDS][1][1][3]=uiCSLI->comboBoxLIComb2Phase2F6MeasBDS;
    ComboBoxMeasGNSS[BDS][1][1][4]=uiCSLI->comboBoxLIComb2Phase2F7MeasBDS;
    ComboBoxMeasGNSS[BDS][1][1][5]=uiCSLI->comboBoxLIComb2Phase2F8MeasBDS;
    //measurement ComboBox Comb3 Phase1
    ComboBoxMeasGNSS[BDS][2][0][0]=uiCSLI->comboBoxLIComb3Phase1F1MeasBDS;
    ComboBoxMeasGNSS[BDS][2][0][1]=uiCSLI->comboBoxLIComb3Phase1F2MeasBDS;
    ComboBoxMeasGNSS[BDS][2][0][2]=uiCSLI->comboBoxLIComb3Phase1F5MeasBDS;
    ComboBoxMeasGNSS[BDS][2][0][3]=uiCSLI->comboBoxLIComb3Phase1F6MeasBDS;
    ComboBoxMeasGNSS[BDS][2][0][4]=uiCSLI->comboBoxLIComb3Phase1F7MeasBDS;
    ComboBoxMeasGNSS[BDS][2][0][5]=uiCSLI->comboBoxLIComb3Phase1F8MeasBDS;
    //measurement ComboBox Comb3 Phase2
    ComboBoxMeasGNSS[BDS][2][1][0]=uiCSLI->comboBoxLIComb3Phase2F1MeasBDS;
    ComboBoxMeasGNSS[BDS][2][1][1]=uiCSLI->comboBoxLIComb3Phase2F2MeasBDS;
    ComboBoxMeasGNSS[BDS][2][1][2]=uiCSLI->comboBoxLIComb3Phase2F5MeasBDS;
    ComboBoxMeasGNSS[BDS][2][1][3]=uiCSLI->comboBoxLIComb3Phase2F6MeasBDS;
    ComboBoxMeasGNSS[BDS][2][1][4]=uiCSLI->comboBoxLIComb3Phase2F7MeasBDS;
    ComboBoxMeasGNSS[BDS][2][1][5]=uiCSLI->comboBoxLIComb3Phase2F8MeasBDS;

    //QZSS
    //combination Frame
    FrameCombGNSS[QZSS][0]=uiCSLI->frameLIComb1QZSS;
    FrameCombGNSS[QZSS][1]=uiCSLI->frameLIComb2QZSS;
    FrameCombGNSS[QZSS][2]=uiCSLI->frameLIComb3QZSS;
    //frequency ComboBox
    ComboBoxFreqGNSS[QZSS][0][0]=uiCSLI->comboBoxLIComb1Freq1QZSS;
    ComboBoxFreqGNSS[QZSS][1][0]=uiCSLI->comboBoxLIComb2Freq1QZSS;
    ComboBoxFreqGNSS[QZSS][2][0]=uiCSLI->comboBoxLIComb3Freq1QZSS;
    ComboBoxFreqGNSS[QZSS][0][1]=uiCSLI->comboBoxLIComb1Freq2QZSS;
    ComboBoxFreqGNSS[QZSS][1][1]=uiCSLI->comboBoxLIComb2Freq2QZSS;
    ComboBoxFreqGNSS[QZSS][2][1]=uiCSLI->comboBoxLIComb3Freq2QZSS;
    //measurement ComboBox Comb1 Phase1
    ComboBoxMeasGNSS[QZSS][0][0][0]=uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS;
    ComboBoxMeasGNSS[QZSS][0][0][1]=uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS;
    ComboBoxMeasGNSS[QZSS][0][0][2]=uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS;
    ComboBoxMeasGNSS[QZSS][0][0][3]=uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS;
    //measurement ComboBox Comb1 Phase2
    ComboBoxMeasGNSS[QZSS][0][1][0]=uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS;
    ComboBoxMeasGNSS[QZSS][0][1][1]=uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS;
    ComboBoxMeasGNSS[QZSS][0][1][2]=uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS;
    ComboBoxMeasGNSS[QZSS][0][1][3]=uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS;
    //measurement ComboBox Comb2 Phase1
    ComboBoxMeasGNSS[QZSS][1][0][0]=uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS;
    ComboBoxMeasGNSS[QZSS][1][0][1]=uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS;
    ComboBoxMeasGNSS[QZSS][1][0][2]=uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS;
    ComboBoxMeasGNSS[QZSS][1][0][3]=uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS;
    //measurement ComboBox Comb2 Phase2
    ComboBoxMeasGNSS[QZSS][1][1][0]=uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS;
    ComboBoxMeasGNSS[QZSS][1][1][1]=uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS;
    ComboBoxMeasGNSS[QZSS][1][1][2]=uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS;
    ComboBoxMeasGNSS[QZSS][1][1][3]=uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS;
    //measurement ComboBox Comb3 Phase1
    ComboBoxMeasGNSS[QZSS][2][0][0]=uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS;
    ComboBoxMeasGNSS[QZSS][2][0][1]=uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS;
    ComboBoxMeasGNSS[QZSS][2][0][2]=uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS;
    ComboBoxMeasGNSS[QZSS][2][0][3]=uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS;
    //measurement ComboBox Comb3 Phase2
    ComboBoxMeasGNSS[QZSS][2][1][0]=uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS;
    ComboBoxMeasGNSS[QZSS][2][1][1]=uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS;
    ComboBoxMeasGNSS[QZSS][2][1][2]=uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS;
    ComboBoxMeasGNSS[QZSS][2][1][3]=uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS;

    //IRNSS
    //combination Frame
    FrameCombGNSS[IRNSS][0]=uiCSLI->frameLIComb1IRNSS;
    FrameCombGNSS[IRNSS][1]=uiCSLI->frameLIComb2IRNSS;
    FrameCombGNSS[IRNSS][2]=uiCSLI->frameLIComb3IRNSS;
    //frequency ComboBox
    ComboBoxFreqGNSS[IRNSS][0][0]=uiCSLI->comboBoxLIComb1Freq1IRNSS;
    ComboBoxFreqGNSS[IRNSS][1][0]=uiCSLI->comboBoxLIComb2Freq1IRNSS;
    ComboBoxFreqGNSS[IRNSS][2][0]=uiCSLI->comboBoxLIComb3Freq1IRNSS;
    ComboBoxFreqGNSS[IRNSS][0][1]=uiCSLI->comboBoxLIComb1Freq2IRNSS;
    ComboBoxFreqGNSS[IRNSS][1][1]=uiCSLI->comboBoxLIComb2Freq2IRNSS;
    ComboBoxFreqGNSS[IRNSS][2][1]=uiCSLI->comboBoxLIComb3Freq2IRNSS;
    //measurement ComboBox Comb1 Phase1
    ComboBoxMeasGNSS[IRNSS][0][0][0]=uiCSLI->comboBoxLIComb1Phase1F5MeasIRNSS;
    ComboBoxMeasGNSS[IRNSS][0][0][1]=uiCSLI->comboBoxLIComb1Phase1F9MeasIRNSS;
    //measurement ComboBox Comb1 Phase2
    ComboBoxMeasGNSS[IRNSS][0][1][0]=uiCSLI->comboBoxLIComb1Phase2F5MeasIRNSS;
    ComboBoxMeasGNSS[IRNSS][0][1][1]=uiCSLI->comboBoxLIComb1Phase2F9MeasIRNSS;
    //measurement ComboBox Comb2 Phase1
    ComboBoxMeasGNSS[IRNSS][1][0][0]=uiCSLI->comboBoxLIComb2Phase1F5MeasIRNSS;
    ComboBoxMeasGNSS[IRNSS][1][0][1]=uiCSLI->comboBoxLIComb2Phase1F9MeasIRNSS;
    //measurement ComboBox Comb2 Phase2
    ComboBoxMeasGNSS[IRNSS][1][1][0]=uiCSLI->comboBoxLIComb2Phase2F5MeasIRNSS;
    ComboBoxMeasGNSS[IRNSS][1][1][1]=uiCSLI->comboBoxLIComb2Phase2F9MeasIRNSS;
    //measurement ComboBox Comb3 Phase1
    ComboBoxMeasGNSS[IRNSS][2][0][0]=uiCSLI->comboBoxLIComb3Phase1F5MeasIRNSS;
    ComboBoxMeasGNSS[IRNSS][2][0][1]=uiCSLI->comboBoxLIComb3Phase1F9MeasIRNSS;
    //measurement ComboBox Comb3 Phase2
    ComboBoxMeasGNSS[IRNSS][2][1][0]=uiCSLI->comboBoxLIComb3Phase2F5MeasIRNSS;
    ComboBoxMeasGNSS[IRNSS][2][1][1]=uiCSLI->comboBoxLIComb3Phase2F9MeasIRNSS;
}
//turn to specified constellation page when click the corresponding pushButton
void GNSS_CS_LI_Advanced::on_pushButtonGPS_clicked(){
    uiCSLI->stackedWidgetLIConfigurationGNSS->setCurrentIndex(GPS);
    uiCSLI->labelSelectPRNFor->setText("GPS:");
    uiCSLI->pushButtonGalileo->setChecked(false);
    uiCSLI->pushButtonGLONASS->setChecked(false);
    uiCSLI->pushButtonGEO->setChecked(false);
    uiCSLI->pushButtonBDS->setChecked(false);
    uiCSLI->pushButtonQZSS->setChecked(false);
    uiCSLI->pushButtonIRNSS->setChecked(false);
    uiCSLI->pushButtonGPS->setChecked(true);
    if (FrameCombGNSS[GPS][2]->isHidden()==false) {
        uiCSLI->pushButtonLIGPSAdd->setEnabled(false);
        uiCSLI->pushButtonLIGPSDel->setEnabled(true);
    } else if (FrameCombGNSS[GPS][1]->isHidden()==false) {
        uiCSLI->pushButtonLIGPSAdd->setEnabled(true);
        uiCSLI->pushButtonLIGPSDel->setEnabled(true);
    } else {
        uiCSLI->pushButtonLIGPSAdd->setEnabled(true);
        uiCSLI->pushButtonLIGPSDel->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_pushButtonGalileo_clicked(){
    uiCSLI->stackedWidgetLIConfigurationGNSS->setCurrentIndex(Galileo);
    uiCSLI->labelSelectPRNFor->setText("Galileo:");
    uiCSLI->pushButtonGPS->setChecked(false);
    uiCSLI->pushButtonGLONASS->setChecked(false);
    uiCSLI->pushButtonGEO->setChecked(false);
    uiCSLI->pushButtonBDS->setChecked(false);
    uiCSLI->pushButtonQZSS->setChecked(false);
    uiCSLI->pushButtonIRNSS->setChecked(false);
    uiCSLI->pushButtonGalileo->setChecked(true);
    if (FrameCombGNSS[Galileo][2]->isHidden()==false) {
        uiCSLI->pushButtonLIGalileoAdd->setEnabled(false);
        uiCSLI->pushButtonLIGalileoDel->setEnabled(true);
    } else if (FrameCombGNSS[Galileo][1]->isHidden()==false) {
        uiCSLI->pushButtonLIGalileoAdd->setEnabled(true);
        uiCSLI->pushButtonLIGalileoDel->setEnabled(true);
    } else {
        uiCSLI->pushButtonLIGalileoAdd->setEnabled(true);
        uiCSLI->pushButtonLIGalileoDel->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_pushButtonGLONASS_clicked(){
    uiCSLI->stackedWidgetLIConfigurationGNSS->setCurrentIndex(GLONASS);
    uiCSLI->labelSelectPRNFor->setText("GLONASS:");
    uiCSLI->pushButtonGPS->setChecked(false);
    uiCSLI->pushButtonGalileo->setChecked(false);
    uiCSLI->pushButtonGEO->setChecked(false);
    uiCSLI->pushButtonBDS->setChecked(false);
    uiCSLI->pushButtonQZSS->setChecked(false);
    uiCSLI->pushButtonIRNSS->setChecked(false);
    uiCSLI->pushButtonGLONASS->setChecked(true);
    if (FrameCombGNSS[GLONASS][2]->isHidden()==false) {
        uiCSLI->pushButtonLIGLONASSAdd->setEnabled(false);
        uiCSLI->pushButtonLIGLONASSDel->setEnabled(true);
    } else if (FrameCombGNSS[GLONASS][1]->isHidden()==false) {
        uiCSLI->pushButtonLIGLONASSAdd->setEnabled(true);
        uiCSLI->pushButtonLIGLONASSDel->setEnabled(true);
    } else {
        uiCSLI->pushButtonLIGLONASSAdd->setEnabled(true);
        uiCSLI->pushButtonLIGLONASSDel->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_pushButtonGEO_clicked(){
    uiCSLI->stackedWidgetLIConfigurationGNSS->setCurrentIndex(GEO);
    uiCSLI->labelSelectPRNFor->setText("GEO:");
    uiCSLI->pushButtonGPS->setChecked(false);
    uiCSLI->pushButtonGalileo->setChecked(false);
    uiCSLI->pushButtonGLONASS->setChecked(false);
    uiCSLI->pushButtonBDS->setChecked(false);
    uiCSLI->pushButtonQZSS->setChecked(false);
    uiCSLI->pushButtonIRNSS->setChecked(false);
    uiCSLI->pushButtonGEO->setChecked(true);
    if (FrameCombGNSS[GEO][2]->isHidden()==false) {
        uiCSLI->pushButtonLIGEOAdd->setEnabled(false);
        uiCSLI->pushButtonLIGEODel->setEnabled(true);
    } else if (FrameCombGNSS[GEO][1]->isHidden()==false) {
        uiCSLI->pushButtonLIGEOAdd->setEnabled(true);
        uiCSLI->pushButtonLIGEODel->setEnabled(true);
    } else {
        uiCSLI->pushButtonLIGEOAdd->setEnabled(true);
        uiCSLI->pushButtonLIGEODel->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_pushButtonBDS_clicked(){
    uiCSLI->stackedWidgetLIConfigurationGNSS->setCurrentIndex(BDS);
    uiCSLI->labelSelectPRNFor->setText("BDS:");
    uiCSLI->pushButtonGPS->setChecked(false);
    uiCSLI->pushButtonGalileo->setChecked(false);
    uiCSLI->pushButtonGLONASS->setChecked(false);
    uiCSLI->pushButtonGEO->setChecked(false);
    uiCSLI->pushButtonQZSS->setChecked(false);
    uiCSLI->pushButtonIRNSS->setChecked(false);
    uiCSLI->pushButtonBDS->setChecked(true);
    if (FrameCombGNSS[BDS][2]->isHidden()==false) {
        uiCSLI->pushButtonLIBDSAdd->setEnabled(false);
        uiCSLI->pushButtonLIBDSDel->setEnabled(true);
    } else if (FrameCombGNSS[BDS][1]->isHidden()==false) {
        uiCSLI->pushButtonLIBDSAdd->setEnabled(true);
        uiCSLI->pushButtonLIBDSDel->setEnabled(true);
    } else {
        uiCSLI->pushButtonLIBDSAdd->setEnabled(true);
        uiCSLI->pushButtonLIBDSDel->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_pushButtonQZSS_clicked(){
    uiCSLI->stackedWidgetLIConfigurationGNSS->setCurrentIndex(QZSS);
    uiCSLI->labelSelectPRNFor->setText("QZSS:");
    uiCSLI->pushButtonGPS->setChecked(false);
    uiCSLI->pushButtonGalileo->setChecked(false);
    uiCSLI->pushButtonGLONASS->setChecked(false);
    uiCSLI->pushButtonGEO->setChecked(false);
    uiCSLI->pushButtonBDS->setChecked(false);
    uiCSLI->pushButtonIRNSS->setChecked(false);
    uiCSLI->pushButtonQZSS->setChecked(true);
    if (FrameCombGNSS[QZSS][2]->isHidden()==false) {
        uiCSLI->pushButtonLIQZSSAdd->setEnabled(false);
        uiCSLI->pushButtonLIQZSSDel->setEnabled(true);
    } else if (FrameCombGNSS[QZSS][1]->isHidden()==false) {
        uiCSLI->pushButtonLIQZSSAdd->setEnabled(true);
        uiCSLI->pushButtonLIQZSSDel->setEnabled(true);
    } else {
        uiCSLI->pushButtonLIQZSSAdd->setEnabled(true);
        uiCSLI->pushButtonLIQZSSDel->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_pushButtonIRNSS_clicked(){
    uiCSLI->stackedWidgetLIConfigurationGNSS->setCurrentIndex(IRNSS);
    uiCSLI->labelSelectPRNFor->setText("IRNSS:");
    uiCSLI->pushButtonGPS->setChecked(false);
    uiCSLI->pushButtonGalileo->setChecked(false);
    uiCSLI->pushButtonGLONASS->setChecked(false);
    uiCSLI->pushButtonGEO->setChecked(false);
    uiCSLI->pushButtonBDS->setChecked(false);
    uiCSLI->pushButtonQZSS->setChecked(false);
    uiCSLI->pushButtonIRNSS->setChecked(true);
    if (FrameCombGNSS[IRNSS][2]->isHidden()==false) {
        uiCSLI->pushButtonLIIRNSSAdd->setEnabled(false);
        uiCSLI->pushButtonLIIRNSSDel->setEnabled(true);
    } else if (FrameCombGNSS[IRNSS][1]->isHidden()==false) {
        uiCSLI->pushButtonLIIRNSSAdd->setEnabled(true);
        uiCSLI->pushButtonLIIRNSSDel->setEnabled(true);
    } else {
        uiCSLI->pushButtonLIIRNSSAdd->setEnabled(true);
        uiCSLI->pushButtonLIIRNSSDel->setEnabled(false);
    }
}

// Set all defaults
void GNSS_CS_LI_Advanced::setCSdefaults(){
    this->SetDefaultGPS();
    this->SetDefaultGalileo();
    this->SetDefaultGLONASS();
    this->SetDefaultGEO();
    this->SetDefaultBDS();
    this->SetDefaultQZSS();
    this->SetDefaultIRNSS();
}

// GPS
void GNSS_CS_LI_Advanced::SetDefaultGPS(){
    uiCSLI->frameLIComb2GPS->setHidden(true);
    uiCSLI->frameLIComb3GPS->setHidden(true);
    uiCSLI->pushButtonLIGPSAdd->setEnabled(true);
    uiCSLI->pushButtonLIGPSDel->setEnabled(false);
    this->on_comboBoxLIComb1Freq1GPS_currentIndexChanged(0);
    this->on_comboBoxLIComb2Freq1GPS_currentIndexChanged(0);
    this->on_comboBoxLIComb3Freq1GPS_currentIndexChanged(0);
}
void GNSS_CS_LI_Advanced::on_pushButtonLIGPSAdd_clicked(){
    if (uiCSLI->frameLIComb2GPS->isHidden()==true){
        uiCSLI->pushButtonLIGPSDel->setEnabled(true);
        uiCSLI->frameLIComb2GPS->setHidden(false);
    } else if (uiCSLI->frameLIComb3GPS->isHidden()==true){
        uiCSLI->frameLIComb3GPS->setHidden(false);
        uiCSLI->pushButtonLIGPSAdd->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_pushButtonLIGPSDel_clicked(){
    if (uiCSLI->frameLIComb3GPS->isHidden()==false){
        uiCSLI->frameLIComb3GPS->setHidden(true);
        uiCSLI->pushButtonLIGPSAdd->setEnabled(true);
    } else if (uiCSLI->frameLIComb2GPS->isHidden()==false){
        uiCSLI->frameLIComb2GPS->setHidden(true);
        uiCSLI->pushButtonLIGPSDel->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Freq1GPS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb1Freq1GPS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb1Freq2GPS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb1Phase1MeasGPS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb1Phase2MeasGPS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GPS]){
        uiCSLI->stackedWidgetLIComb1Phase1MeasGPS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase1MeasGPS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq2GPS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq2GPS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb1Phase2MeasGPS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase2MeasGPS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GPS]){
        uiCSLI->stackedWidgetLIComb1Phase1MeasGPS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase1MeasGPS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq2GPS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq2GPS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb1Phase2MeasGPS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase2MeasGPS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Freq2GPS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb1Freq2GPS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb1Freq1GPS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb1Phase2MeasGPS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb1Phase1MeasGPS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GPS]){
        uiCSLI->stackedWidgetLIComb1Phase2MeasGPS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase2MeasGPS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq1GPS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq1GPS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb1Phase1MeasGPS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase1MeasGPS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GPS]){
        uiCSLI->stackedWidgetLIComb1Phase2MeasGPS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase2MeasGPS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq1GPS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq1GPS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb1Phase1MeasGPS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase1MeasGPS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F1MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F2MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F5MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F1MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F2MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F5MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F5MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasGPS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Freq1GPS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb2Freq1GPS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb2Freq2GPS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb2Phase1MeasGPS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb2Phase2MeasGPS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GPS]){
        uiCSLI->stackedWidgetLIComb2Phase1MeasGPS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase1MeasGPS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq2GPS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq2GPS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb2Phase2MeasGPS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase2MeasGPS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GPS]){
        uiCSLI->stackedWidgetLIComb2Phase1MeasGPS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase1MeasGPS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq2GPS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq2GPS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb2Phase2MeasGPS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase2MeasGPS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Freq2GPS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb2Freq2GPS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb2Freq1GPS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb2Phase2MeasGPS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb2Phase1MeasGPS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GPS]){
        uiCSLI->stackedWidgetLIComb2Phase2MeasGPS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase2MeasGPS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq1GPS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq1GPS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb2Phase1MeasGPS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase1MeasGPS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GPS]){
        uiCSLI->stackedWidgetLIComb2Phase2MeasGPS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase2MeasGPS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq1GPS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq1GPS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb2Phase1MeasGPS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase1MeasGPS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F1MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F2MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F5MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F1MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F2MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F5MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F5MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasGPS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Freq1GPS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb3Freq1GPS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb3Freq2GPS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb3Phase1MeasGPS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb3Phase2MeasGPS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GPS]){
        uiCSLI->stackedWidgetLIComb3Phase1MeasGPS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase1MeasGPS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq2GPS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq2GPS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb3Phase2MeasGPS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase2MeasGPS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GPS]){
        uiCSLI->stackedWidgetLIComb3Phase1MeasGPS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase1MeasGPS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq2GPS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq2GPS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb3Phase2MeasGPS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase2MeasGPS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Freq2GPS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb3Freq2GPS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb3Freq1GPS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb3Phase2MeasGPS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb3Phase1MeasGPS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GPS]){
        uiCSLI->stackedWidgetLIComb3Phase2MeasGPS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase2MeasGPS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq1GPS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq1GPS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb3Phase1MeasGPS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase1MeasGPS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GPS]){
        uiCSLI->stackedWidgetLIComb3Phase2MeasGPS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase2MeasGPS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq1GPS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq1GPS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb3Phase1MeasGPS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase1MeasGPS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F1MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F2MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F5MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F1MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F2MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F5MeasGPS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F5MeasGPS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGPS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasGPS->setCurrentIndex(1);
    }
}

//Galileo
void GNSS_CS_LI_Advanced::SetDefaultGalileo(){
    uiCSLI->frameLIComb2Galileo->setHidden(true);
    uiCSLI->frameLIComb3Galileo->setHidden(true);
    uiCSLI->pushButtonLIGalileoAdd->setEnabled(true);
    uiCSLI->pushButtonLIGalileoDel->setEnabled(false);
    this->on_comboBoxLIComb1Freq1Galileo_currentIndexChanged(0);
    this->on_comboBoxLIComb2Freq1Galileo_currentIndexChanged(0);
    this->on_comboBoxLIComb3Freq1Galileo_currentIndexChanged(0);
}
void GNSS_CS_LI_Advanced::on_pushButtonLIGalileoAdd_clicked(){
    if (uiCSLI->frameLIComb2Galileo->isHidden()==true){
        uiCSLI->pushButtonLIGalileoDel->setEnabled(true);
        uiCSLI->frameLIComb2Galileo->setHidden(false);
    } else if (uiCSLI->frameLIComb3Galileo->isHidden()==true){
        uiCSLI->frameLIComb3Galileo->setHidden(false);
        uiCSLI->pushButtonLIGalileoAdd->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_pushButtonLIGalileoDel_clicked(){
    if (uiCSLI->frameLIComb3Galileo->isHidden()==false){
        uiCSLI->frameLIComb3Galileo->setHidden(true);
        uiCSLI->pushButtonLIGalileoAdd->setEnabled(true);
    } else if (uiCSLI->frameLIComb2Galileo->isHidden()==false){
        uiCSLI->frameLIComb2Galileo->setHidden(true);
        uiCSLI->pushButtonLIGalileoDel->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Freq1Galileo_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb1Freq1Galileo->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb1Freq2Galileo->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb1Phase1MeasGalileo->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb1Phase2MeasGalileo->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[Galileo]){
        uiCSLI->stackedWidgetLIComb1Phase1MeasGalileo->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase1MeasGalileo->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq2Galileo->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq2Galileo->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb1Phase2MeasGalileo->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase2MeasGalileo->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[Galileo]){
        uiCSLI->stackedWidgetLIComb1Phase1MeasGalileo->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase1MeasGalileo->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq2Galileo->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq2Galileo->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb1Phase2MeasGalileo->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase2MeasGalileo->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Freq2Galileo_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb1Freq2Galileo->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb1Freq1Galileo->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb1Phase2MeasGalileo->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb1Phase1MeasGalileo->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[Galileo]){
        uiCSLI->stackedWidgetLIComb1Phase2MeasGalileo->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase2MeasGalileo->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq1Galileo->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq1Galileo->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb1Phase1MeasGalileo->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase1MeasGalileo->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[Galileo]){
        uiCSLI->stackedWidgetLIComb1Phase2MeasGalileo->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase2MeasGalileo->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq1Galileo->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq1Galileo->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb1Phase1MeasGalileo->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase1MeasGalileo->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F1MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F5MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F6MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F7MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F8MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F1MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F5MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F6MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F7MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F8MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F8MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Freq1Galileo_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb2Freq1Galileo->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb2Freq2Galileo->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb2Phase1MeasGalileo->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb2Phase2MeasGalileo->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[Galileo]){
        uiCSLI->stackedWidgetLIComb2Phase1MeasGalileo->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase1MeasGalileo->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq2Galileo->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq2Galileo->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb2Phase2MeasGalileo->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase2MeasGalileo->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[Galileo]){
        uiCSLI->stackedWidgetLIComb2Phase1MeasGalileo->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase1MeasGalileo->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq2Galileo->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq2Galileo->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb2Phase2MeasGalileo->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase2MeasGalileo->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Freq2Galileo_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb2Freq2Galileo->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb2Freq1Galileo->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb2Phase2MeasGalileo->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb2Phase1MeasGalileo->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[Galileo]){
        uiCSLI->stackedWidgetLIComb2Phase2MeasGalileo->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase2MeasGalileo->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq1Galileo->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq1Galileo->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb2Phase1MeasGalileo->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase1MeasGalileo->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[Galileo]){
        uiCSLI->stackedWidgetLIComb2Phase2MeasGalileo->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase2MeasGalileo->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq1Galileo->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq1Galileo->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb2Phase1MeasGalileo->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase1MeasGalileo->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F1MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F5MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F6MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F7MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F8MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F1MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F5MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F6MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F7MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F8MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F8MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Freq1Galileo_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb3Freq1Galileo->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb3Freq2Galileo->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb3Phase1MeasGalileo->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb3Phase2MeasGalileo->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[Galileo]){
        uiCSLI->stackedWidgetLIComb3Phase1MeasGalileo->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase1MeasGalileo->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq2Galileo->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq2Galileo->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb3Phase2MeasGalileo->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase2MeasGalileo->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[Galileo]){
        uiCSLI->stackedWidgetLIComb3Phase1MeasGalileo->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase1MeasGalileo->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq2Galileo->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq2Galileo->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb3Phase2MeasGalileo->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase2MeasGalileo->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Freq2Galileo_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb3Freq2Galileo->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb3Freq1Galileo->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb3Phase2MeasGalileo->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb3Phase1MeasGalileo->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[Galileo]){
        uiCSLI->stackedWidgetLIComb3Phase2MeasGalileo->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase2MeasGalileo->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq1Galileo->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq1Galileo->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb3Phase1MeasGalileo->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase1MeasGalileo->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[Galileo]){
        uiCSLI->stackedWidgetLIComb3Phase2MeasGalileo->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase2MeasGalileo->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq1Galileo->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq1Galileo->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb3Phase1MeasGalileo->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase1MeasGalileo->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F1MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F5MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F6MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F7MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F8MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F1MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F5MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F6MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F7MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F8MeasGalileo_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F8MeasGalileo->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGalileo->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasGalileo->setCurrentIndex(1);
    }
}

//GLONASS
void GNSS_CS_LI_Advanced::SetDefaultGLONASS(){
    uiCSLI->frameLIComb2GLONASS->setHidden(true);
    uiCSLI->frameLIComb3GLONASS->setHidden(true);
    uiCSLI->pushButtonLIGLONASSAdd->setEnabled(true);
    uiCSLI->pushButtonLIGLONASSDel->setEnabled(false);
    this->on_comboBoxLIComb1Freq1GLONASS_currentIndexChanged(0);
    this->on_comboBoxLIComb2Freq1GLONASS_currentIndexChanged(0);
    this->on_comboBoxLIComb3Freq1GLONASS_currentIndexChanged(0);
}
void GNSS_CS_LI_Advanced::on_pushButtonLIGLONASSAdd_clicked(){
    if (uiCSLI->frameLIComb2GLONASS->isHidden()==true){
        uiCSLI->pushButtonLIGLONASSDel->setEnabled(true);
        uiCSLI->frameLIComb2GLONASS->setHidden(false);
    } else if (uiCSLI->frameLIComb3GLONASS->isHidden()==true){
        uiCSLI->frameLIComb3GLONASS->setHidden(false);
        uiCSLI->pushButtonLIGLONASSAdd->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_pushButtonLIGLONASSDel_clicked(){
    if (uiCSLI->frameLIComb3GLONASS->isHidden()==false){
        uiCSLI->frameLIComb3GLONASS->setHidden(true);
        uiCSLI->pushButtonLIGLONASSAdd->setEnabled(true);
    } else if (uiCSLI->frameLIComb2GLONASS->isHidden()==false){
        uiCSLI->frameLIComb2GLONASS->setHidden(true);
        uiCSLI->pushButtonLIGLONASSDel->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Freq1GLONASS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb1Freq1GLONASS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb1Freq2GLONASS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb1Phase1MeasGLONASS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb1Phase2MeasGLONASS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GLONASS]){
        uiCSLI->stackedWidgetLIComb1Phase1MeasGLONASS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase1MeasGLONASS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq2GLONASS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq2GLONASS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb1Phase2MeasGLONASS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase2MeasGLONASS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GLONASS]){
        uiCSLI->stackedWidgetLIComb1Phase1MeasGLONASS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase1MeasGLONASS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq2GLONASS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq2GLONASS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb1Phase2MeasGLONASS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase2MeasGLONASS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Freq2GLONASS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb1Freq2GLONASS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb1Freq1GLONASS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb1Phase2MeasGLONASS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb1Phase1MeasGLONASS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GLONASS]){
        uiCSLI->stackedWidgetLIComb1Phase2MeasGLONASS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase2MeasGLONASS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq1GLONASS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq1GLONASS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb1Phase1MeasGLONASS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase1MeasGLONASS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GLONASS]){
        uiCSLI->stackedWidgetLIComb1Phase2MeasGLONASS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase2MeasGLONASS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq1GLONASS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq1GLONASS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb1Phase1MeasGLONASS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase1MeasGLONASS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F1MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F2MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F3MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F4MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F6MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F1MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F2MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F3MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F4MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F6MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F6MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F4MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Freq1GLONASS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb2Freq1GLONASS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb2Freq2GLONASS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb2Phase1MeasGLONASS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb2Phase2MeasGLONASS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GLONASS]){
        uiCSLI->stackedWidgetLIComb2Phase1MeasGLONASS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase1MeasGLONASS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq2GLONASS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq2GLONASS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb2Phase2MeasGLONASS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase2MeasGLONASS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GLONASS]){
        uiCSLI->stackedWidgetLIComb2Phase1MeasGLONASS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase1MeasGLONASS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq2GLONASS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq2GLONASS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb2Phase2MeasGLONASS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase2MeasGLONASS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Freq2GLONASS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb2Freq2GLONASS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb2Freq1GLONASS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb2Phase2MeasGLONASS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb2Phase1MeasGLONASS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GLONASS]){
        uiCSLI->stackedWidgetLIComb2Phase2MeasGLONASS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase2MeasGLONASS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq1GLONASS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq1GLONASS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb2Phase1MeasGLONASS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase1MeasGLONASS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GLONASS]){
        uiCSLI->stackedWidgetLIComb2Phase2MeasGLONASS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase2MeasGLONASS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq1GLONASS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq1GLONASS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb2Phase1MeasGLONASS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase1MeasGLONASS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F1MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F2MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F3MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F4MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F6MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F1MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F2MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F3MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F4MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F6MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F6MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F4MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Freq1GLONASS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb3Freq1GLONASS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb3Freq2GLONASS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb3Phase1MeasGLONASS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb3Phase2MeasGLONASS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GLONASS]){
        uiCSLI->stackedWidgetLIComb3Phase1MeasGLONASS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase1MeasGLONASS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq2GLONASS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq2GLONASS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb3Phase2MeasGLONASS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase2MeasGLONASS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GLONASS]){
        uiCSLI->stackedWidgetLIComb3Phase1MeasGLONASS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase1MeasGLONASS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq2GLONASS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq2GLONASS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb3Phase2MeasGLONASS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase2MeasGLONASS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Freq2GLONASS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb3Freq2GLONASS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb3Freq1GLONASS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb3Phase2MeasGLONASS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb3Phase1MeasGLONASS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GLONASS]){
        uiCSLI->stackedWidgetLIComb3Phase2MeasGLONASS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase2MeasGLONASS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq1GLONASS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq1GLONASS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb3Phase1MeasGLONASS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase1MeasGLONASS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GLONASS]){
        uiCSLI->stackedWidgetLIComb3Phase2MeasGLONASS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase2MeasGLONASS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq1GLONASS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq1GLONASS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb3Phase1MeasGLONASS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase1MeasGLONASS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F1MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F2MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F3MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F4MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F6MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F1MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F2MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F3MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F4MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F6MeasGLONASS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F6MeasGLONASS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F4MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F3MeasGLONASS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F4MeasGLONASS->setCurrentIndex(1);
    }
}

//GEO
void GNSS_CS_LI_Advanced::SetDefaultGEO(){
    uiCSLI->frameLIComb2GEO->setHidden(true);
    uiCSLI->frameLIComb3GEO->setHidden(true);
    uiCSLI->pushButtonLIGEOAdd->setEnabled(true);
    uiCSLI->pushButtonLIGEODel->setEnabled(false);
    this->on_comboBoxLIComb1Freq1GEO_currentIndexChanged(0);
    this->on_comboBoxLIComb2Freq1GEO_currentIndexChanged(0);
    this->on_comboBoxLIComb3Freq1GEO_currentIndexChanged(0);
}
void GNSS_CS_LI_Advanced::on_pushButtonLIGEOAdd_clicked(){
    if (uiCSLI->frameLIComb2GEO->isHidden()==true){
        uiCSLI->pushButtonLIGEODel->setEnabled(true);
        uiCSLI->frameLIComb2GEO->setHidden(false);
    } else if (uiCSLI->frameLIComb3GEO->isHidden()==true){
        uiCSLI->frameLIComb3GEO->setHidden(false);
        uiCSLI->pushButtonLIGEOAdd->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_pushButtonLIGEODel_clicked(){
    if (uiCSLI->frameLIComb3GEO->isHidden()==false){
        uiCSLI->frameLIComb3GEO->setHidden(true);
        uiCSLI->pushButtonLIGEOAdd->setEnabled(true);
    } else if (uiCSLI->frameLIComb2GEO->isHidden()==false){
        uiCSLI->frameLIComb2GEO->setHidden(true);
        uiCSLI->pushButtonLIGEODel->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Freq1GEO_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb1Freq1GEO->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb1Freq2GEO->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb1Phase1MeasGEO->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGEO->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb1Phase2MeasGEO->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGEO->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GEO]){
        uiCSLI->stackedWidgetLIComb1Phase1MeasGEO->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase1MeasGEO->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq2GEO->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq2GEO->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb1Phase2MeasGEO->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase2MeasGEO->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GEO]){
        uiCSLI->stackedWidgetLIComb1Phase1MeasGEO->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase1MeasGEO->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq2GEO->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq2GEO->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb1Phase2MeasGEO->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase2MeasGEO->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Freq2GEO_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb1Freq2GEO->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb1Freq1GEO->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb1Phase2MeasGEO->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGEO->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb1Phase1MeasGEO->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGEO->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GEO]){
        uiCSLI->stackedWidgetLIComb1Phase2MeasGEO->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase2MeasGEO->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq1GEO->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq1GEO->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb1Phase1MeasGEO->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase1MeasGEO->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GEO]){
        uiCSLI->stackedWidgetLIComb1Phase2MeasGEO->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase2MeasGEO->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq1GEO->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq1GEO->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb1Phase1MeasGEO->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase1MeasGEO->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F1MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGEO->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasGEO->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F5MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F5MeasGEO->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasGEO->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F1MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F1MeasGEO->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasGEO->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F5MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F5MeasGEO->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasGEO->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Freq1GEO_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb2Freq1GEO->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb2Freq2GEO->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb2Phase1MeasGEO->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGEO->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb2Phase2MeasGEO->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGEO->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GEO]){
        uiCSLI->stackedWidgetLIComb2Phase1MeasGEO->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase1MeasGEO->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq2GEO->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq2GEO->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb2Phase2MeasGEO->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase2MeasGEO->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GEO]){
        uiCSLI->stackedWidgetLIComb2Phase1MeasGEO->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase1MeasGEO->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq2GEO->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq2GEO->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb2Phase2MeasGEO->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase2MeasGEO->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Freq2GEO_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb2Freq2GEO->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb2Freq1GEO->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb2Phase2MeasGEO->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGEO->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb2Phase1MeasGEO->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGEO->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GEO]){
        uiCSLI->stackedWidgetLIComb2Phase2MeasGEO->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase2MeasGEO->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq1GEO->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq1GEO->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb2Phase1MeasGEO->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase1MeasGEO->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GEO]){
        uiCSLI->stackedWidgetLIComb2Phase2MeasGEO->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase2MeasGEO->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq1GEO->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq1GEO->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb2Phase1MeasGEO->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase1MeasGEO->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F1MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGEO->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasGEO->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F5MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F5MeasGEO->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasGEO->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F1MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F1MeasGEO->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasGEO->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F5MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F5MeasGEO->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasGEO->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Freq1GEO_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb3Freq1GEO->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb3Freq2GEO->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb3Phase1MeasGEO->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGEO->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb3Phase2MeasGEO->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGEO->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GEO]){
        uiCSLI->stackedWidgetLIComb3Phase1MeasGEO->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase1MeasGEO->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq2GEO->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq2GEO->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb3Phase2MeasGEO->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase2MeasGEO->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GEO]){
        uiCSLI->stackedWidgetLIComb3Phase1MeasGEO->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase1MeasGEO->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq2GEO->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq2GEO->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb3Phase2MeasGEO->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase2MeasGEO->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Freq2GEO_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb3Freq2GEO->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb3Freq1GEO->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb3Phase2MeasGEO->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGEO->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb3Phase1MeasGEO->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGEO->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[GEO]){
        uiCSLI->stackedWidgetLIComb3Phase2MeasGEO->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase2MeasGEO->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq1GEO->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq1GEO->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb3Phase1MeasGEO->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase1MeasGEO->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[GEO]){
        uiCSLI->stackedWidgetLIComb3Phase2MeasGEO->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase2MeasGEO->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq1GEO->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq1GEO->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb3Phase1MeasGEO->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase1MeasGEO->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F1MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGEO->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasGEO->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F5MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F5MeasGEO->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasGEO->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F1MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F1MeasGEO->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasGEO->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F5MeasGEO_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasGEO->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasGEO->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F5MeasGEO->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasGEO->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasGEO->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasGEO->setCurrentIndex(1);
    }
}

//BDS
void GNSS_CS_LI_Advanced::SetDefaultBDS(){
    uiCSLI->frameLIComb2BDS->setHidden(true);
    uiCSLI->frameLIComb3BDS->setHidden(true);
    uiCSLI->pushButtonLIBDSAdd->setEnabled(true);
    uiCSLI->pushButtonLIBDSDel->setEnabled(false);
    this->on_comboBoxLIComb1Freq1BDS_currentIndexChanged(0);
    this->on_comboBoxLIComb2Freq1BDS_currentIndexChanged(0);
    this->on_comboBoxLIComb3Freq1BDS_currentIndexChanged(0);
}
void GNSS_CS_LI_Advanced::on_pushButtonLIBDSAdd_clicked(){
    if (uiCSLI->frameLIComb2BDS->isHidden()==true){
        uiCSLI->pushButtonLIBDSDel->setEnabled(true);
        uiCSLI->frameLIComb2BDS->setHidden(false);
    } else if (uiCSLI->frameLIComb3BDS->isHidden()==true){
        uiCSLI->frameLIComb3BDS->setHidden(false);
        uiCSLI->pushButtonLIBDSAdd->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_pushButtonLIBDSDel_clicked(){
    if (uiCSLI->frameLIComb3BDS->isHidden()==false){
        uiCSLI->frameLIComb3BDS->setHidden(true);
        uiCSLI->pushButtonLIBDSAdd->setEnabled(true);
    } else if (uiCSLI->frameLIComb2BDS->isHidden()==false){
        uiCSLI->frameLIComb2BDS->setHidden(true);
        uiCSLI->pushButtonLIBDSDel->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Freq1BDS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb1Freq1BDS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb1Freq2BDS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb1Phase1MeasBDS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb1Phase2MeasBDS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[BDS]){
        uiCSLI->stackedWidgetLIComb1Phase1MeasBDS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase1MeasBDS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq2BDS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq2BDS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb1Phase2MeasBDS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase2MeasBDS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[BDS]){
        uiCSLI->stackedWidgetLIComb1Phase1MeasBDS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase1MeasBDS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq2BDS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq2BDS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb1Phase2MeasBDS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase2MeasBDS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Freq2BDS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb1Freq2BDS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb1Freq1BDS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb1Phase2MeasBDS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb1Phase1MeasBDS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[BDS]){
        uiCSLI->stackedWidgetLIComb1Phase2MeasBDS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase2MeasBDS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq1BDS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq1BDS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb1Phase1MeasBDS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase1MeasBDS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[BDS]){
        uiCSLI->stackedWidgetLIComb1Phase2MeasBDS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase2MeasBDS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq1BDS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq1BDS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb1Phase1MeasBDS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase1MeasBDS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F2MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F7MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F6MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F5MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F1MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F8MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F2MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F7MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F6MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F5MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F1MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F8MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F8MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Freq1BDS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb2Freq1BDS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb2Freq2BDS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb2Phase1MeasBDS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb2Phase2MeasBDS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[BDS]){
        uiCSLI->stackedWidgetLIComb2Phase1MeasBDS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase1MeasBDS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq2BDS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq2BDS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb2Phase2MeasBDS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase2MeasBDS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[BDS]){
        uiCSLI->stackedWidgetLIComb2Phase1MeasBDS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase1MeasBDS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq2BDS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq2BDS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb2Phase2MeasBDS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase2MeasBDS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Freq2BDS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb2Freq2BDS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb2Freq1BDS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb2Phase2MeasBDS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb2Phase1MeasBDS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[BDS]){
        uiCSLI->stackedWidgetLIComb2Phase2MeasBDS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase2MeasBDS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq1BDS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq1BDS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb2Phase1MeasBDS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase1MeasBDS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[BDS]){
        uiCSLI->stackedWidgetLIComb2Phase2MeasBDS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase2MeasBDS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq1BDS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq1BDS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb2Phase1MeasBDS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase1MeasBDS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F2MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F7MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F6MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F5MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F1MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F8MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F2MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F7MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F6MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F5MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F1MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F8MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F8MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Freq1BDS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb3Freq1BDS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb3Freq2BDS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb3Phase1MeasBDS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb3Phase2MeasBDS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[BDS]){
        uiCSLI->stackedWidgetLIComb3Phase1MeasBDS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase1MeasBDS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq2BDS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq2BDS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb3Phase2MeasBDS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase2MeasBDS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[BDS]){
        uiCSLI->stackedWidgetLIComb3Phase1MeasBDS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase1MeasBDS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq2BDS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq2BDS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb3Phase2MeasBDS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase2MeasBDS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Freq2BDS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb3Freq2BDS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb3Freq1BDS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb3Phase2MeasBDS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb3Phase1MeasBDS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[BDS]){
        uiCSLI->stackedWidgetLIComb3Phase2MeasBDS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase2MeasBDS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq1BDS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq1BDS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb3Phase1MeasBDS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase1MeasBDS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[BDS]){
        uiCSLI->stackedWidgetLIComb3Phase2MeasBDS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase2MeasBDS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq1BDS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq1BDS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb3Phase1MeasBDS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase1MeasBDS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F2MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F7MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F6MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F5MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F1MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F8MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F2MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F7MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F6MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F5MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F1MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F8MeasBDS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F8MeasBDS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F8MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F7MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasBDS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasBDS->setCurrentIndex(1);
    }
}

//QZSS
void GNSS_CS_LI_Advanced::SetDefaultQZSS(){
    uiCSLI->frameLIComb2QZSS->setHidden(true);
    uiCSLI->frameLIComb3QZSS->setHidden(true);
    uiCSLI->pushButtonLIQZSSAdd->setEnabled(true);
    uiCSLI->pushButtonLIQZSSDel->setEnabled(false);
    this->on_comboBoxLIComb1Freq1QZSS_currentIndexChanged(0);
    this->on_comboBoxLIComb2Freq1QZSS_currentIndexChanged(0);
    this->on_comboBoxLIComb3Freq1QZSS_currentIndexChanged(0);
}
void GNSS_CS_LI_Advanced::on_pushButtonLIQZSSAdd_clicked(){
    if (uiCSLI->frameLIComb2QZSS->isHidden()==true){
        uiCSLI->pushButtonLIQZSSDel->setEnabled(true);
        uiCSLI->frameLIComb2QZSS->setHidden(false);
    } else if (uiCSLI->frameLIComb3QZSS->isHidden()==true){
        uiCSLI->frameLIComb3QZSS->setHidden(false);
        uiCSLI->pushButtonLIQZSSAdd->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_pushButtonLIQZSSDel_clicked(){
    if (uiCSLI->frameLIComb3QZSS->isHidden()==false){
        uiCSLI->frameLIComb3QZSS->setHidden(true);
        uiCSLI->pushButtonLIQZSSAdd->setEnabled(true);
    } else if (uiCSLI->frameLIComb2QZSS->isHidden()==false){
        uiCSLI->frameLIComb2QZSS->setHidden(true);
        uiCSLI->pushButtonLIQZSSDel->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Freq1QZSS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb1Freq1QZSS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb1Freq2QZSS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb1Phase1MeasQZSS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb1Phase2MeasQZSS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[QZSS]){
        uiCSLI->stackedWidgetLIComb1Phase1MeasQZSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase1MeasQZSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq2QZSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq2QZSS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb1Phase2MeasQZSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase2MeasQZSS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[QZSS]){
        uiCSLI->stackedWidgetLIComb1Phase1MeasQZSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase1MeasQZSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq2QZSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq2QZSS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb1Phase2MeasQZSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase2MeasQZSS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Freq2QZSS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb1Freq2QZSS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb1Freq1QZSS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb1Phase2MeasQZSS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb1Phase1MeasQZSS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[QZSS]){
        uiCSLI->stackedWidgetLIComb1Phase2MeasQZSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase2MeasQZSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq1QZSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq1QZSS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb1Phase1MeasQZSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase1MeasQZSS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[QZSS]){
        uiCSLI->stackedWidgetLIComb1Phase2MeasQZSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase2MeasQZSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq1QZSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq1QZSS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb1Phase1MeasQZSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase1MeasQZSS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F1MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F2MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F5MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F6MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F1MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F2MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F5MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F6MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F6MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Freq1QZSS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb2Freq1QZSS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb2Freq2QZSS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb2Phase1MeasQZSS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb2Phase2MeasQZSS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[QZSS]){
        uiCSLI->stackedWidgetLIComb2Phase1MeasQZSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase1MeasQZSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq2QZSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq2QZSS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb2Phase2MeasQZSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase2MeasQZSS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[QZSS]){
        uiCSLI->stackedWidgetLIComb2Phase1MeasQZSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase1MeasQZSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq2QZSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq2QZSS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb2Phase2MeasQZSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase2MeasQZSS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Freq2QZSS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb2Freq2QZSS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb2Freq1QZSS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb2Phase2MeasQZSS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb2Phase1MeasQZSS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[QZSS]){
        uiCSLI->stackedWidgetLIComb2Phase2MeasQZSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase2MeasQZSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq1QZSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq1QZSS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb2Phase1MeasQZSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase1MeasQZSS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[QZSS]){
        uiCSLI->stackedWidgetLIComb2Phase2MeasQZSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase2MeasQZSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq1QZSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq1QZSS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb2Phase1MeasQZSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase1MeasQZSS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F1MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F2MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F5MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F6MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F1MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F2MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F5MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F6MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F6MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Freq1QZSS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb3Freq1QZSS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb3Freq2QZSS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb3Phase1MeasQZSS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb3Phase2MeasQZSS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[QZSS]){
        uiCSLI->stackedWidgetLIComb3Phase1MeasQZSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase1MeasQZSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq2QZSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq2QZSS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb3Phase2MeasQZSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase2MeasQZSS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[QZSS]){
        uiCSLI->stackedWidgetLIComb3Phase1MeasQZSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase1MeasQZSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq2QZSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq2QZSS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb3Phase2MeasQZSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase2MeasQZSS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Freq2QZSS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb3Freq2QZSS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb3Freq1QZSS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb3Phase2MeasQZSS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb3Phase1MeasQZSS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[QZSS]){
        uiCSLI->stackedWidgetLIComb3Phase2MeasQZSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase2MeasQZSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq1QZSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq1QZSS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb3Phase1MeasQZSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase1MeasQZSS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[QZSS]){
        uiCSLI->stackedWidgetLIComb3Phase2MeasQZSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase2MeasQZSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq1QZSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq1QZSS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb3Phase1MeasQZSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase1MeasQZSS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F1MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F2MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F5MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F6MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F1MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F2MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F5MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F6MeasQZSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F6MeasQZSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F6MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F1MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F2MeasQZSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasQZSS->setCurrentIndex(1);
    }
}

//IRNSS
void GNSS_CS_LI_Advanced::SetDefaultIRNSS(){
    uiCSLI->frameLIComb2IRNSS->setHidden(true);
    uiCSLI->frameLIComb3IRNSS->setHidden(true);
    uiCSLI->pushButtonLIIRNSSAdd->setEnabled(true);
    uiCSLI->pushButtonLIIRNSSDel->setEnabled(false);
    this->on_comboBoxLIComb1Freq1IRNSS_currentIndexChanged(0);
    this->on_comboBoxLIComb2Freq1IRNSS_currentIndexChanged(0);
    this->on_comboBoxLIComb3Freq1IRNSS_currentIndexChanged(0);
}
void GNSS_CS_LI_Advanced::on_pushButtonLIIRNSSAdd_clicked(){
    if (uiCSLI->frameLIComb2IRNSS->isHidden()==true){
        uiCSLI->pushButtonLIIRNSSDel->setEnabled(true);
        uiCSLI->frameLIComb2IRNSS->setHidden(false);
    } else if (uiCSLI->frameLIComb3IRNSS->isHidden()==true){
        uiCSLI->frameLIComb3IRNSS->setHidden(false);
        uiCSLI->pushButtonLIIRNSSAdd->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_pushButtonLIIRNSSDel_clicked(){
    if (uiCSLI->frameLIComb3IRNSS->isHidden()==false){
        uiCSLI->frameLIComb3IRNSS->setHidden(true);
        uiCSLI->pushButtonLIIRNSSAdd->setEnabled(true);
    } else if (uiCSLI->frameLIComb2IRNSS->isHidden()==false){
        uiCSLI->frameLIComb2IRNSS->setHidden(true);
        uiCSLI->pushButtonLIIRNSSDel->setEnabled(false);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Freq1IRNSS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb1Freq1IRNSS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb1Freq2IRNSS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb1Phase1MeasIRNSS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb1Phase2MeasIRNSS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F9MeasIRNSS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[IRNSS]){
        uiCSLI->stackedWidgetLIComb1Phase1MeasIRNSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase1MeasIRNSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq2IRNSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq2IRNSS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb1Phase2MeasIRNSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase2MeasIRNSS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[IRNSS]){
        uiCSLI->stackedWidgetLIComb1Phase1MeasIRNSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase1MeasIRNSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq2IRNSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq2IRNSS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb1Phase2MeasIRNSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase2MeasIRNSS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Freq2IRNSS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb1Freq2IRNSS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb1Freq1IRNSS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb1Phase2MeasIRNSS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb1Phase1MeasIRNSS->setEnabled(false);
        uiCSLI->comboBoxLIComb1Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[IRNSS]){
        uiCSLI->stackedWidgetLIComb1Phase2MeasIRNSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase2MeasIRNSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq1IRNSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq1IRNSS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb1Phase1MeasIRNSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase1MeasIRNSS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[IRNSS]){
        uiCSLI->stackedWidgetLIComb1Phase2MeasIRNSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb1Phase2MeasIRNSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb1Freq1IRNSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb1Freq1IRNSS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb1Phase1MeasIRNSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb1Phase1MeasIRNSS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F5MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F5MeasIRNSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F9MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F9MeasIRNSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase1F9MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase1F9MeasIRNSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F9MeasIRNSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F5MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F5MeasIRNSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F9MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F9MeasIRNSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb1Phase2F9MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb1Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase1F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb1Phase2F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb1Phase2F9MeasIRNSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb1Phase1F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F5MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase1F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase1F9MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb1Phase2F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb1Phase2F5MeasIRNSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Freq1IRNSS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb2Freq1IRNSS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb2Freq2IRNSS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb2Phase1MeasIRNSS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb2Phase2MeasIRNSS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F9MeasIRNSS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[IRNSS]){
        uiCSLI->stackedWidgetLIComb2Phase1MeasIRNSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase1MeasIRNSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq2IRNSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq2IRNSS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb2Phase2MeasIRNSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase2MeasIRNSS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[IRNSS]){
        uiCSLI->stackedWidgetLIComb2Phase1MeasIRNSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase1MeasIRNSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq2IRNSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq2IRNSS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb2Phase2MeasIRNSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase2MeasIRNSS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Freq2IRNSS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb2Freq2IRNSS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb2Freq1IRNSS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb2Phase2MeasIRNSS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb2Phase1MeasIRNSS->setEnabled(false);
        uiCSLI->comboBoxLIComb2Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[IRNSS]){
        uiCSLI->stackedWidgetLIComb2Phase2MeasIRNSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase2MeasIRNSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq1IRNSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq1IRNSS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb2Phase1MeasIRNSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase1MeasIRNSS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[IRNSS]){
        uiCSLI->stackedWidgetLIComb2Phase2MeasIRNSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb2Phase2MeasIRNSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb2Freq1IRNSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb2Freq1IRNSS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb2Phase1MeasIRNSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb2Phase1MeasIRNSS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F5MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F5MeasIRNSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F9MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F9MeasIRNSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase1F9MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase1F9MeasIRNSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F9MeasIRNSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F5MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F5MeasIRNSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F9MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F9MeasIRNSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb2Phase2F9MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb2Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase1F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb2Phase2F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb2Phase2F9MeasIRNSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb2Phase1F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F5MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase1F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase1F9MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb2Phase2F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb2Phase2F5MeasIRNSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Freq1IRNSS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb3Freq1IRNSS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb3Freq2IRNSS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb3Phase1MeasIRNSS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb3Phase2MeasIRNSS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F9MeasIRNSS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[IRNSS]){
        uiCSLI->stackedWidgetLIComb3Phase1MeasIRNSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase1MeasIRNSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq2IRNSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq2IRNSS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb3Phase2MeasIRNSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase2MeasIRNSS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[IRNSS]){
        uiCSLI->stackedWidgetLIComb3Phase1MeasIRNSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase1MeasIRNSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq2IRNSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq2IRNSS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb3Phase2MeasIRNSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase2MeasIRNSS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Freq2IRNSS_currentIndexChanged(int index){
    uiCSLI->comboBoxLIComb3Freq2IRNSS->setCurrentIndex(index);
    if (index==0){
        uiCSLI->comboBoxLIComb3Freq1IRNSS->setCurrentIndex(index);
        uiCSLI->stackedWidgetLIComb3Phase2MeasIRNSS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->stackedWidgetLIComb3Phase1MeasIRNSS->setEnabled(false);
        uiCSLI->comboBoxLIComb3Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F9MeasIRNSS->setCurrentIndex(0);
    } else if (index>0&&index<nFreqGNSS[IRNSS]){
        uiCSLI->stackedWidgetLIComb3Phase2MeasIRNSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase2MeasIRNSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq1IRNSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq1IRNSS->setCurrentIndex(index+1);
            uiCSLI->stackedWidgetLIComb3Phase1MeasIRNSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase1MeasIRNSS->setCurrentIndex(index);
        }
    } else if (index==nFreqGNSS[IRNSS]){
        uiCSLI->stackedWidgetLIComb3Phase2MeasIRNSS->setEnabled(true);
        uiCSLI->stackedWidgetLIComb3Phase2MeasIRNSS->setCurrentIndex(index-1);
        if (uiCSLI->comboBoxLIComb3Freq1IRNSS->currentIndex()==0){
            uiCSLI->comboBoxLIComb3Freq1IRNSS->setCurrentIndex(1);
            uiCSLI->stackedWidgetLIComb3Phase1MeasIRNSS->setEnabled(true);
            uiCSLI->stackedWidgetLIComb3Phase1MeasIRNSS->setCurrentIndex(0);
        }
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F5MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F5MeasIRNSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F9MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F9MeasIRNSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase1F9MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase1F9MeasIRNSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F9MeasIRNSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F5MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F5MeasIRNSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F9MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F9MeasIRNSS->setCurrentIndex(1);
    }
}
void GNSS_CS_LI_Advanced::on_comboBoxLIComb3Phase2F9MeasIRNSS_currentIndexChanged(int index){
    if (index==0) {
        uiCSLI->comboBoxLIComb3Phase1F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase1F9MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F5MeasIRNSS->setCurrentIndex(0);
        uiCSLI->comboBoxLIComb3Phase2F9MeasIRNSS->setCurrentIndex(0);
    } else {
        uiCSLI->comboBoxLIComb3Phase2F9MeasIRNSS->setCurrentIndex(index);
        if (uiCSLI->comboBoxLIComb3Phase1F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F5MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase1F9MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase1F9MeasIRNSS->setCurrentIndex(1);
        if (uiCSLI->comboBoxLIComb3Phase2F5MeasIRNSS->currentIndex()==0) uiCSLI->comboBoxLIComb3Phase2F5MeasIRNSS->setCurrentIndex(1);
    }
}

// Function to select GPS satellites
void GNSS_CS_LI_Advanced::changePushButtonGPS(bool checked){
    uiCSLI->pushButtonGPS->setEnabled(checked);
    this->SetDefaultGPS();
}
// Function to select Galileo satellites
void GNSS_CS_LI_Advanced::changePushButtonGalileo(bool checked){
    uiCSLI->pushButtonGalileo->setEnabled(checked);
    this->SetDefaultGalileo();
}
// Function to select GLONASS satellites
void GNSS_CS_LI_Advanced::changePushButtonGLONASS(bool checked){
    uiCSLI->pushButtonGLONASS->setEnabled(checked);
    this->SetDefaultGLONASS();
}
// Function to select GEO satellites
void GNSS_CS_LI_Advanced::changePushButtonGEO(bool checked){
    uiCSLI->pushButtonGEO->setEnabled(checked);
    this->SetDefaultGEO();
}
// Function to select BDS satellites
void GNSS_CS_LI_Advanced::changePushButtonBDS(bool checked){
    uiCSLI->pushButtonBDS->setEnabled(checked);
    this->SetDefaultBDS();
}
// Function to select QZSS satellites
void GNSS_CS_LI_Advanced::changePushButtonQZSS(bool checked){
    uiCSLI->pushButtonQZSS->setEnabled(checked);
    this->SetDefaultQZSS();
}
// Function to select IRNSS satellites
void GNSS_CS_LI_Advanced::changePushButtonIRNSS(bool checked){
    uiCSLI->pushButtonIRNSS->setEnabled(checked);
    this->SetDefaultIRNSS();
}

// Function to configure GPS satellites
void GNSS_CS_LI_Advanced::on_pushButtonPublicGPS_clicked(){
    this->on_pushButtonGPS_clicked();
}
// Function to configure Galileo satellites
void GNSS_CS_LI_Advanced::on_pushButtonPublicGalileo_clicked(){
    this->on_pushButtonGalileo_clicked();
}
// Function to configure GLONASS satellites
void GNSS_CS_LI_Advanced::on_pushButtonPublicGLONASS_clicked(){
    this->on_pushButtonGLONASS_clicked();
}
// Function to configure GEO satellites
void GNSS_CS_LI_Advanced::on_pushButtonPublicGEO_clicked(){
    this->on_pushButtonGEO_clicked();
}
// Function to configure BDS satellites
void GNSS_CS_LI_Advanced::on_pushButtonPublicBDS_clicked(){
    this->on_pushButtonBDS_clicked();
}
// Function to configure QZSS satellites
void GNSS_CS_LI_Advanced::on_pushButtonPublicQZSS_clicked(){
    this->on_pushButtonQZSS_clicked();
}
// Function to configure IRNSS satellites
void GNSS_CS_LI_Advanced::on_pushButtonPublicIRNSS_clicked(){
    this->on_pushButtonIRNSS_clicked();
}

void GNSS_CS_LI_Advanced::changeCurrentPage(){
    for (int i=0; i<MAX_GNSS; i++){
        if (PushButtonGNSS[i]->isEnabled()){
            (this->*PushButtonGNSSFunctions[i])();
            break;
        }
    }
}

//Function to get LI command options
int GNSS_CS_LI_Advanced::getgLABOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString){
    QString freqOption="",measOption="";
    QStringList freqOptionList, measOptionList;
    int paramCount=0;
    int numFreqOptionList=0, numMeasOptionList=0;
    int skipIteration[MAX_GNSS][3]={{0}};
    int multipleAuto[MAX_GNSS]={0};
    //loop of constellations
    for (int gnssi=0; gnssi<MAX_GNSS; gnssi++){
        //Look for repeated combinations in iteration 2
        if (FrameCombGNSS[gnssi][1]->isHidden()==false) {
            if ( ComboBoxFreqGNSS[gnssi][1][0]->currentIndex()==0 && ComboBoxFreqGNSS[gnssi][0][0]->currentIndex()==0){
                *warningString += "PREPROCESS: " + GNSSName[gnssi] + " constellation in Geometry-Free cycle-slip detector has multiple 'Auto' iterations, but only one will be applied. Set only one 'Auto' iteration.\n";
                skipIteration[gnssi][1]=1;
                multipleAuto[gnssi]=1;
            } else if (ComboBoxFreqGNSS[gnssi][1][0]->currentIndex()!=0 && ComboBoxFreqGNSS[gnssi][0][0]->currentIndex()!=0) {
                int freq1=ComboBoxFreqGNSS[gnssi][1][0]->currentIndex()-1;
                int freq0=ComboBoxFreqGNSS[gnssi][0][0]->currentIndex()-1;

                if (freq1==freq0) {
                    if (ComboBoxMeasGNSS[gnssi][1][0][freq1]->currentIndex()==ComboBoxMeasGNSS[gnssi][0][0][freq0]->currentIndex()
                            && ComboBoxMeasGNSS[gnssi][1][1][freq1]->currentIndex()==ComboBoxMeasGNSS[gnssi][0][1][freq0]->currentIndex()) {
                        *warningString += "PREPROCESS: " + GNSSName[gnssi] + " constellation in Geometry-Free cycle-slip detector has iterations 1 and 2 repeated. They will be used only once.\n";
                        skipIteration[gnssi][1]=1;
                    }
                }
            }
            if (FrameCombGNSS[gnssi][2]->isHidden()==false) {
                if ( ComboBoxFreqGNSS[gnssi][1][0]->currentIndex()==0 && ComboBoxFreqGNSS[gnssi][2][0]->currentIndex()==0 ) {
                    if (multipleAuto[gnssi]==0) {
                        *warningString += "PREPROCESS: " + GNSSName[gnssi] + " constellation in Geometry-Free cycle-slip detector has multiple 'Auto' iterations, but only one will be applied. Set only one 'Auto' iteration.\n";
                    }
                    skipIteration[gnssi][2]=1;
                    multipleAuto[gnssi]=1;
                } else if (ComboBoxFreqGNSS[gnssi][1][0]->currentIndex()!=0 && ComboBoxFreqGNSS[gnssi][2][0]->currentIndex()!=0) {
                    int freq1=ComboBoxFreqGNSS[gnssi][1][0]->currentIndex()-1;
                    int freq0=ComboBoxFreqGNSS[gnssi][2][0]->currentIndex()-1;
                    if (freq1==freq0) {
                        if (ComboBoxMeasGNSS[gnssi][1][0][freq1]->currentIndex()==ComboBoxMeasGNSS[gnssi][2][0][freq0]->currentIndex()
                                && ComboBoxMeasGNSS[gnssi][1][1][freq1]->currentIndex()==ComboBoxMeasGNSS[gnssi][2][1][freq0]->currentIndex()) {
                            *warningString += "PREPROCESS: " + GNSSName[gnssi] + " constellation in Geometry-Free cycle-slip detector has iterations 2 and 3 repeated. They will be used only once.\n";
                            skipIteration[gnssi][2]=1;
                        }
                    }
                }
            }
        }
        //Look for repeated combinations in iteration 3
        if (FrameCombGNSS[gnssi][2]->isHidden()==false && skipIteration[gnssi][2]==0) {
            if ( ComboBoxFreqGNSS[gnssi][2][0]->currentIndex()==0 && ComboBoxFreqGNSS[gnssi][0][0]->currentIndex()==0) {
                if (multipleAuto[gnssi]==0) {
                    *warningString += "PREPROCESS: " + GNSSName[gnssi] + " constellation in Geometry-Free cycle-slip detector has multiple 'Auto' iterations, but only one will be applied. Set only one 'Auto' iteration.\n";
                }
                skipIteration[gnssi][2]=1;
                multipleAuto[gnssi]=1;
            } else if (ComboBoxFreqGNSS[gnssi][2][0]->currentIndex()!=0 && ComboBoxFreqGNSS[gnssi][0][0]->currentIndex()!=0) {
                int freq1=ComboBoxFreqGNSS[gnssi][2][0]->currentIndex()-1;
                int freq0=ComboBoxFreqGNSS[gnssi][0][0]->currentIndex()-1;
                if (freq1==freq0) {
                    if (ComboBoxMeasGNSS[gnssi][2][0][freq1]->currentIndex()==ComboBoxMeasGNSS[gnssi][0][0][freq0]->currentIndex()
                            && ComboBoxMeasGNSS[gnssi][2][1][freq1]->currentIndex()==ComboBoxMeasGNSS[gnssi][0][1][freq0]->currentIndex()) {
                        *warningString += "PREPROCESS: " + GNSSName[gnssi] + " constellation in Geometry-Free cycle-slip detector has iterations 1 and 3 repeated. They will be used only once.\n";
                        skipIteration[gnssi][2]=1;
                    }
                }
            }
        }
       int freqflag=0;
       //loop of combinations
        for (int combi=0; combi<3; combi++){
            if (skipIteration[gnssi][combi]==1) continue; //Skip repetead combinations
            //get options if not hidden and frequency is specified
            if (FrameCombGNSS[gnssi][combi]->isHidden()==false && ComboBoxFreqGNSS[gnssi][combi][0]->currentIndex()!=0) {
                int freq1=ComboBoxFreqGNSS[gnssi][combi][0]->currentIndex()-1;
                int freq2=ComboBoxFreqGNSS[gnssi][combi][1]->currentIndex()-1;
                //only specify frequency
                if (ComboBoxMeasGNSS[gnssi][combi][0][freq1]->currentIndex()==0) {
                    if (freq1==freq2) {
                        *errorString += "PREPROCESS: " + GNSSName[gnssi] + " constellation in Geometry-Free cycle-slip detector has iteration " + QString::number(combi+1) + " with both frequencies equal, which is only allowed if both measurements are specified.\n";
                    }
                    if (freqflag==0){
                        freqOption += " " + indentifierGNSS[gnssi] + "0-" + FreqGNSSList[gnssi][freq1] + FreqGNSSList[gnssi][freq2];
                        freqflag=1;
                    } else {
                        freqOption += "." + FreqGNSSList[gnssi][freq1] + FreqGNSSList[gnssi][freq2];
                    }
                }
                //specify both frequency and measurement
                else {
                    if (freq1==freq2 && ComboBoxMeasGNSS[gnssi][combi][0][freq1]->currentText()==ComboBoxMeasGNSS[gnssi][combi][1][freq2]->currentText() ) {
                       *errorString += "PREPROCESS: " + GNSSName[gnssi] + " constellation in Geometry-Free cycle-slip detector has iteration " + QString::number(combi+1) + " with both frequencies and measurements equal.\n";
                    }
                    measOption += " " + indentifierGNSS[gnssi] + "0-" +
                            ComboBoxMeasGNSS[gnssi][combi][0][freq1]->currentText() + "-" + ComboBoxMeasGNSS[gnssi][combi][1][freq2]->currentText();
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

    //-pre:cs:li:freq
    int firstArg=1;
    for(int Param=0;Param<numFreqOptionList;Param++) {
        if (freqOptionList[Param]=="") continue;
        if (firstArg==1) {
            firstArg=0;
            *saveString += "-pre:cs:li:freq";
            *runString << "-pre:cs:li:freq";
        }
        *saveString += " " + freqOptionList[Param];
        *runString << freqOptionList[Param];
        paramCount++;
    }
    if (firstArg==0) *saveString += "\n";

    //-pre:cs:li:meas
    firstArg=1;
    for(int Param=0;Param<numMeasOptionList;Param++) {
        if (measOptionList[Param]=="") continue;
        if (firstArg==1) {
            firstArg=0;
            *saveString += "-pre:cs:li:meas";
            *runString << "-pre:cs:li:meas";
        }
        *saveString += " " + measOptionList[Param];
        *runString << measOptionList[Param];
        paramCount++;
    }
    if (firstArg==0) *saveString += "\n";

    return paramCount;
}
//Function to convert LI command options to GUI configuration
void GNSS_CS_LI_Advanced::loadgLABOptions(QString *warningString, QStringList *ParametersList, const int freqMeas){
    int setCount[MAX_GNSS]={0};
    int nPar=ParametersList->count();
    if (warningString->length()<0) *warningString=""; //only to avoid the warning of unused "warningString"
    //get former set
    for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++){
        for (int icomb=0; icomb<3; icomb++){
            if (ComboBoxFreqGNSS[iGNSS][icomb][0]->currentIndex()>0) setCount[iGNSS]=icomb+1;
        }
    }
    //frequency
    if (freqMeas==1){
        //loop parameters
        for (int iPar=0; iPar<nPar; iPar++){
            int iGNSS=-1;
            //Check parameter
            if (checkUserInputCycleSlipMeasurement(warningString,ParametersList->at(iPar),CStypeLI,CStypeParamFreq,nullptr)) continue;
            //find frequency list
            QStringList FreqParList = ParametersList->at(iPar).split("-", QString::SkipEmptyParts);
            //get constellation
            for (iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
                if (!FreqParList[0].toUpper().contains(indentifierGNSS[iGNSS]) && FreqParList[0]!="0" ) continue;
                QStringList freqComb = FreqParList.last().split(".",QString::SkipEmptyParts);
                //loop frequency
                for (int iCom=0; iCom<freqComb.count(); iCom++){
                    if (setCount[iGNSS]>2) {
                        *warningString += "PREPROCESS: Maximum number of iterations for " + GNSSName[iGNSS] + " GF cycle-slip detector is 3. Argument '" + ParametersList->at(iPar) + "' was skipped for " + GNSSName[iGNSS] + " as limit has been surpassed.\n";
                        break;
                    }
                    if (freqComb[iCom].size()!=2) continue;
                    int freq1=-1,freq2=-1;
                    //get 2 frequencies
                    for (int ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                        if (freqComb[iCom].mid(0,1)==FreqGNSSList[iGNSS][ifreq]) freq1=ifreq;
                        if (freqComb[iCom].mid(1,1)==FreqGNSSList[iGNSS][ifreq]) freq2=ifreq;
                    }
                    if ( freq1<0 ) {
                        *warningString += "PREPROCESS: MW cycle-slip frequency '" + freqComb[iCom].mid(0,1) + "' in argument '" + ParametersList->at(iPar) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if ( freq2<0 ) {
                        *warningString += "PREPROCESS: MW cycle-slip frequency '" + freqComb[iCom].mid(1,1) + "' in argument '" + ParametersList->at(iPar) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        continue;
                    } else if (freq1==freq2 ) continue; //Already checked  in checkUserInputCycleSlipMeasurement
                    FrameCombGNSS[iGNSS][setCount[iGNSS]]->setHidden(false);
                    ComboBoxFreqGNSS[iGNSS][setCount[iGNSS]][0]->setCurrentIndex(freq1+1);
                    ComboBoxFreqGNSS[iGNSS][setCount[iGNSS]][1]->setCurrentIndex(freq2+1);
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
            if (checkUserInputCycleSlipMeasurement(warningString,ParametersList->at(iPar),CStypeLI,CStypeParamMeas,nullptr)) continue;
            //find measurement list
            QStringList MeasParList = ParametersList->at(iPar).split("-", QString::SkipEmptyParts);
            measStart=MeasParList.count()-2;
            if (measStart<1) continue;
            //get constellation
            for (iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
                if (!MeasParList[0].toUpper().contains(indentifierGNSS[iGNSS]) && MeasParList[0]!="0" ) continue;
                if ( setCount[iGNSS]>2 ) {
                    *warningString += "PREPROCESS: Maximum number of iterations for " + GNSSName[iGNSS] + " GF cycle-slip detector is 3. Argument '" + ParametersList->at(iPar) + "' was skipped for " + GNSSName[iGNSS] + " as limit has been surpassed.\n";
                    continue;
                }
                //get freqeuncy & measurement
                int freq12[2]={-1,-1},meas12[2]={-1,-1};
                for (int iFM=0; iFM<2; iFM++){
                    if ( MeasParList[measStart+iFM].mid(0,1)!="L" || MeasParList[measStart+iFM].size()!=3 ) {
                        break;
                    }
                    for (int ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                        if (MeasParList[measStart+iFM].mid(1,1)==FreqGNSSList[iGNSS][ifreq]) {
                            freq12[iFM]=ifreq;
                        }
                    }
                    if ( freq12[iFM]<0) {
                        *warningString += "PREPROCESS: Frequency '" + MeasParList[measStart+iFM].mid(1,1) + "' in measurement '" + MeasParList[measStart+iFM] + "' in argument '" + ParametersList->at(iPar) + "' for GF cycle-slip detector does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                        break;
                    }
                    for (int imeas=0; imeas<MeasGNSSOrder[iGNSS][freq12[iFM]].size(); imeas++){
                        if (MeasParList[measStart+iFM].toUpper().mid(2,1)==MeasGNSSOrder[iGNSS][freq12[iFM]].mid(imeas,1)) {
                            meas12[iFM]=imeas;
                        }
                    }
                    if (meas12[iFM]<0) {
                        *warningString += "PREPROCESS: Measurement '" + MeasParList[measStart+iFM] + "' in argument '" + ParametersList->at(iPar) + "' for GF cycle-slip detector does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                    }
                }
                if ( freq12[0]<0 || freq12[1]<0 || meas12[0]<0 || meas12[1]<0 ) continue;
                FrameCombGNSS[iGNSS][setCount[iGNSS]]->setHidden(false);
                ComboBoxFreqGNSS[iGNSS][setCount[iGNSS]][0]->setCurrentIndex(freq12[0]+1);
                ComboBoxFreqGNSS[iGNSS][setCount[iGNSS]][1]->setCurrentIndex(freq12[1]+1);
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

void GNSS_CS_LI_Advanced::on_pushButtonCSLIAdvancedDefault_clicked(){
    setCSdefaults();
}
void GNSS_CS_LI_Advanced::on_pushButtonCSLIAdvancedOk_clicked(){
    this->OkFlag=1;
    this->close();
}
void GNSS_CS_LI_Advanced::on_pushButtonCSLIAdvancedCancel_clicked(){
    this->OkFlag=0;
    this->close();
}
