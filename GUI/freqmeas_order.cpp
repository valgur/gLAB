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
#include "freqmeas_order.h"
#include "ui_freqmeas_order.h"

//constant
//const QString ObsType[4]={"LCD","C","L","D"}; //Uncomment when Doppler is enabled again
const QString ObsType[4]={"LC","C","L","D"}; //Remove when Doppler is enabled again

GNSS_FreqMeas_Order::GNSS_FreqMeas_Order(QWidget *parent) :
    QDialog(parent),
    uiFreqMeas(new Ui::GNSS_FreqMeas_Order)
{
    uiFreqMeas->setupUi(this);
    OkFlag=0;
    FreqBackGroundColor="#eeeeec";
    MeasBackGroundColor="#ffffff";

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

    //Title
    this->setFreqMeasdefaults();
    uiFreqMeas->stackedWidgetFreqMeasGNSS->setCurrentIndex(0);
    this->setWindowTitle("Frequencies and Measurements Order Configuration");

    gnssUnSelected.setStyle(Qt::SolidPattern); gnssUnSelected.setColor(QColor(RedColor));
    FreqSelected.setStyle(Qt::SolidPattern); FreqSelected.setColor(QColor(FreqBackGroundColor));
    MeasSelected.setStyle(Qt::SolidPattern); MeasSelected.setColor(QColor(MeasBackGroundColor));

    //Init variable with pointers to PushButtons pointers
    this->InitPushButtonGNSSPointers();
    //Init variable with pointers to PushButtons function pointers
    this->InitPushButtonGNSSMinFuncPointers();
    //Function to initialize pointers to all checkBox and tableWidget
    this->InitFreqMeasPointers();

    //Set the first column width of all tables to 65 to fit E5a+b or B2a+b
    uiFreqMeas->tableWidgetOrderFreqMeasGPS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasGalileo->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasGLONASS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasGEO->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasBDS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasQZSS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasIRNSS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS->setColumnWidth(0,65);
    uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS->setColumnWidth(0,65);

    //connect functions
    //GPS
    connect(uiFreqMeas->tableWidgetOrderFreqMeasGPS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasGPS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasGPS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    //Galileo
    connect(uiFreqMeas->tableWidgetOrderFreqMeasGalileo,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasGalileo,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasGalileo->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    //GLONASS
    connect(uiFreqMeas->tableWidgetOrderFreqMeasGLONASS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasGLONASS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasGLONASS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    //GEO
    connect(uiFreqMeas->tableWidgetOrderFreqMeasGEO,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasGEO,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasGEO->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    //BDS
    connect(uiFreqMeas->tableWidgetOrderFreqMeasBDS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasBDS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasBDS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    //QZSS
    connect(uiFreqMeas->tableWidgetOrderFreqMeasQZSS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasQZSS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasQZSS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    //IRNSS
    connect(uiFreqMeas->tableWidgetOrderFreqMeasIRNSS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasIRNSS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasIRNSS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");
    connect(uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(Item_clicked(QTableWidgetItem *)));
    connect(uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(Item_doubleClicked(QTableWidgetItem *)));
    uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS->setStyleSheet("QTableWidget{selection-background-color:rgb(65,105,225); selection-color:white;}");


    uiFreqMeas->pushButtonFreqMeasOrderOk->setFocus();

    uiFreqMeas->pushButtonFreqMeasOrderCancel->setHidden(true); //Remove when Cancel buttons undo all changes made by the user

    //This is to hide the Doppler tab, as it is not used (it is disabled and set to no width and height in the stylesheet so it is not shown.
    //If Qt is updated to 5.15, a new option setTabVisible(index, visible) has been added (so it can replace the lines below)
    uiFreqMeas->tabWidgetGPS->setTabEnabled(2,false);
    uiFreqMeas->tabWidgetGPS->setStyleSheet("QTabBar::tab::disabled {width: 0; height: 0; margin: 0; padding: 0; border: none;} ");
    uiFreqMeas->tabWidgetGalileo->setTabEnabled(2,false);
    uiFreqMeas->tabWidgetGalileo->setStyleSheet("QTabBar::tab::disabled {width: 0; height: 0; margin: 0; padding: 0; border: none;} ");
    uiFreqMeas->tabWidgetGLONASS->setTabEnabled(2,false);
    uiFreqMeas->tabWidgetGLONASS->setStyleSheet("QTabBar::tab::disabled {width: 0; height: 0; margin: 0; padding: 0; border: none;} ");
    uiFreqMeas->tabWidgetGEO->setTabEnabled(2,false);
    uiFreqMeas->tabWidgetGEO->setStyleSheet("QTabBar::tab::disabled {width: 0; height: 0; margin: 0; padding: 0; border: none;} ");
    uiFreqMeas->tabWidgetBDS->setTabEnabled(2,false);
    uiFreqMeas->tabWidgetBDS->setStyleSheet("QTabBar::tab::disabled {width: 0; height: 0; margin: 0; padding: 0; border: none;} ");
    uiFreqMeas->tabWidgetQZSS->setTabEnabled(2,false);
    uiFreqMeas->tabWidgetQZSS->setStyleSheet("QTabBar::tab::disabled {width: 0; height: 0; margin: 0; padding: 0; border: none;} ");
    uiFreqMeas->tabWidgetIRNSS->setTabEnabled(2,false);
    uiFreqMeas->tabWidgetIRNSS->setStyleSheet("QTabBar::tab::disabled {width: 0; height: 0; margin: 0; padding: 0; border: none;} ");
}

GNSS_FreqMeas_Order::~GNSS_FreqMeas_Order()
{
    delete uiFreqMeas;
}

//Function to initialize pointers to CheckBox widget pointers
void GNSS_FreqMeas_Order::InitPushButtonGNSSPointers(){
    PushButtonGNSS[GPS]=uiFreqMeas->pushButtonGPS;
    PushButtonGNSS[Galileo]=uiFreqMeas->pushButtonGalileo;
    PushButtonGNSS[GLONASS]=uiFreqMeas->pushButtonGLONASS;
    PushButtonGNSS[GEO]=uiFreqMeas->pushButtonGEO;
    PushButtonGNSS[BDS]=uiFreqMeas->pushButtonBDS;
    PushButtonGNSS[QZSS]=uiFreqMeas->pushButtonQZSS;
    PushButtonGNSS[IRNSS]=uiFreqMeas->pushButtonIRNSS;
}

//Function to initialize pointers to pushButton GNSS Measurements _clicked() functions
void GNSS_FreqMeas_Order::InitPushButtonGNSSMinFuncPointers(){
    PushButtonGNSSFunctions[GPS]=&GNSS_FreqMeas_Order::on_pushButtonGPS_clicked;
    PushButtonGNSSFunctions[Galileo]=&GNSS_FreqMeas_Order::on_pushButtonGalileo_clicked;
    PushButtonGNSSFunctions[GLONASS]=&GNSS_FreqMeas_Order::on_pushButtonGLONASS_clicked;
    PushButtonGNSSFunctions[GEO]=&GNSS_FreqMeas_Order::on_pushButtonGEO_clicked;
    PushButtonGNSSFunctions[BDS]=&GNSS_FreqMeas_Order::on_pushButtonBDS_clicked;
    PushButtonGNSSFunctions[QZSS]=&GNSS_FreqMeas_Order::on_pushButtonQZSS_clicked;
    PushButtonGNSSFunctions[IRNSS]=&GNSS_FreqMeas_Order::on_pushButtonIRNSS_clicked;
}

//Function to initialize pointers to all checkBox and tableWidget
void GNSS_FreqMeas_Order::InitFreqMeasPointers(){
    //GPS
    CheckBoxGNSSOrder[GPS]=uiFreqMeas->checkBoxOrderFreqMeasGPS;
    GroupBoxGNSSOrder[GPS]=&GNSS_FreqMeas_Order::on_checkBoxOrderFreqMeasGPS_clicked;
    TableGNSS[GPS][0]=uiFreqMeas->tableWidgetOrderFreqMeasGPS;
    TableGNSS[GPS][1]=uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS;
    TableGNSS[GPS][2]=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS;
    TableGNSS[GPS][3]=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS;
    //Galileo
    CheckBoxGNSSOrder[Galileo]=uiFreqMeas->checkBoxOrderFreqMeasGalileo;
    GroupBoxGNSSOrder[Galileo]=&GNSS_FreqMeas_Order::on_checkBoxOrderFreqMeasGalileo_clicked;
    TableGNSS[Galileo][0]=uiFreqMeas->tableWidgetOrderFreqMeasGalileo;
    TableGNSS[Galileo][1]=uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo;
    TableGNSS[Galileo][2]=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo;
    TableGNSS[Galileo][3]=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo;
    //GLONASS
    CheckBoxGNSSOrder[GLONASS]=uiFreqMeas->checkBoxOrderFreqMeasGLONASS;
    GroupBoxGNSSOrder[GLONASS]=&GNSS_FreqMeas_Order::on_checkBoxOrderFreqMeasGLONASS_clicked;
    TableGNSS[GLONASS][0]=uiFreqMeas->tableWidgetOrderFreqMeasGLONASS;
    TableGNSS[GLONASS][1]=uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS;
    TableGNSS[GLONASS][2]=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS;
    TableGNSS[GLONASS][3]=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS;
    //GEO
    CheckBoxGNSSOrder[GEO]=uiFreqMeas->checkBoxOrderFreqMeasGEO;
    GroupBoxGNSSOrder[GEO]=&GNSS_FreqMeas_Order::on_checkBoxOrderFreqMeasGEO_clicked;
    TableGNSS[GEO][0]=uiFreqMeas->tableWidgetOrderFreqMeasGEO;
    TableGNSS[GEO][1]=uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO;
    TableGNSS[GEO][2]=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO;
    TableGNSS[GEO][3]=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO;
    //BDS
    CheckBoxGNSSOrder[BDS]=uiFreqMeas->checkBoxOrderFreqMeasBDS;
    GroupBoxGNSSOrder[BDS]=&GNSS_FreqMeas_Order::on_checkBoxOrderFreqMeasBDS_clicked;
    TableGNSS[BDS][0]=uiFreqMeas->tableWidgetOrderFreqMeasBDS;
    TableGNSS[BDS][1]=uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS;
    TableGNSS[BDS][2]=uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS;
    TableGNSS[BDS][3]=uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS;
    //QZSS
    CheckBoxGNSSOrder[QZSS]=uiFreqMeas->checkBoxOrderFreqMeasQZSS;
    GroupBoxGNSSOrder[QZSS]=&GNSS_FreqMeas_Order::on_checkBoxOrderFreqMeasQZSS_clicked;
    TableGNSS[QZSS][0]=uiFreqMeas->tableWidgetOrderFreqMeasQZSS;
    TableGNSS[QZSS][1]=uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS;
    TableGNSS[QZSS][2]=uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS;
    TableGNSS[QZSS][3]=uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS;
    //IRNSS
    CheckBoxGNSSOrder[IRNSS]=uiFreqMeas->checkBoxOrderFreqMeasIRNSS;
    GroupBoxGNSSOrder[IRNSS]=&GNSS_FreqMeas_Order::on_checkBoxOrderFreqMeasIRNSS_clicked;
    TableGNSS[IRNSS][0]=uiFreqMeas->tableWidgetOrderFreqMeasIRNSS;
    TableGNSS[IRNSS][1]=uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS;
    TableGNSS[IRNSS][2]=uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS;
    TableGNSS[IRNSS][3]=uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS;
}
//set frequency or measurement as selected/unselected by double-clicked
void GNSS_FreqMeas_Order::Item_doubleClicked(QTableWidgetItem *tableItem){
    if (tableItem->text()=="") return;
    QTableWidget *pTable=tableItem->tableWidget();
    int irow=tableItem->row(), icolumn=tableItem->column(), nRowcount=pTable->rowCount(), nColumnCount=pTable->columnCount();
    //frequency items for all measurements
    if (irow>0&&icolumn==0){
        //unselected to selected
        if (tableItem->background().color().name()==RedColor){
            for (int i=0; i<nRowcount; i++){
                if (pTable->item(i,0)->background().color().name()==RedColor) {
                    this->moveFreqRow(pTable,irow,i,1);
                    for (int j=0; j<nColumnCount;j++){
                        if (j==0) pTable->item(i,j)->setBackground(FreqSelected);
                        else pTable->item(i,j)->setBackground(MeasSelected);
                    }
                    pTable->clearSelection();
                    break;
                }
            }
        } else {//selected to unselected
            for (int i=nRowcount-1; i>0; i--){
                if (pTable->item(i,0)->background().color().name()!=RedColor) {
                    this->moveFreqRow(pTable,irow,i,1);
                    for (int j=0; j<nColumnCount;j++){
                        pTable->item(i,j)->setBackground(gnssUnSelected);
                    }
                    pTable->clearSelection();
                    break;
                }
            }
        }
        //set frequency in followed table
        //loop GNSS
        for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++){
            if (CheckBoxGNSSOrder[iGNSS]->isChecked()) {
                int ctable=-1;
                //get current table
                for (ctable=0;ctable<3; ctable++){
                    if ( pTable==TableGNSS[iGNSS][ctable+1] ) break;
                }
                //set followed table
                if (ctable>=3) continue;
                for (int itable=0; itable<3; itable++){
                    if (itable!=ctable) freqDoubleClicked(TableGNSS[iGNSS][itable+1]->item(irow,icolumn));
                }
            }
        }

    } else if (irow>0&&icolumn>0){ //measurement item
        if (pTable->item(irow,0)->background().color().name()==RedColor) return;
        //unselected to selected
        if (tableItem->background().color().name()==RedColor){
            for (int i=0; i<nColumnCount; i++){
                if (pTable->item(irow,i)->background().color().name()==RedColor){
                    pTable->setCurrentCell(irow,icolumn);
                    this->moveMeasColumn(pTable,icolumn,i,1);
                    pTable->item(irow,i)->setBackground(MeasSelected);
                    pTable->clearSelection();
                    break;
                }
            }
        } else {//selected to unselected
            for (int i=nColumnCount-1; i>0; i--){
                if ((pTable->item(irow,i)->background().color().name()!=RedColor && pTable->item(irow,i)->text()!="")){
                    pTable->setCurrentCell(irow,icolumn);
                    this->moveMeasColumn(pTable,icolumn,i,1);
                    pTable->item(irow,i)->setBackground(gnssUnSelected);
                    break;
                }
            }
            pTable->clearSelection();
        }
    }
}
//set frequency selected/unselected by double-clicked
void GNSS_FreqMeas_Order::freqDoubleClicked(QTableWidgetItem *tableItem){
    if (tableItem->text()=="") return;
    QTableWidget *pTable=tableItem->tableWidget();
    int irow=tableItem->row(), icolumn=tableItem->column(), nRowcount=pTable->rowCount(), nColumnCount=pTable->columnCount();
    //frequency items for all measurements
    if (irow>0&&icolumn==0){
        //unselected to selected
        if (tableItem->background().color().name()==RedColor){
            for (int i=0; i<nRowcount; i++){
                if (pTable->item(i,0)->background().color().name()==RedColor) {
                    this->moveFreqRow(pTable,irow,i,1);
                    for (int j=0; j<nColumnCount;j++){
                        if (j==0) pTable->item(i,j)->setBackground(FreqSelected);
                        else pTable->item(i,j)->setBackground(MeasSelected);
                    }
                    pTable->clearSelection();
                    break;
                }
            }
        } else {//selected to unselected
            for (int i=nRowcount-1; i>0; i--){
                if (pTable->item(i,0)->background().color().name()!=RedColor) {
                    this->moveFreqRow(pTable,irow,i,1);
                    for (int j=0; j<nColumnCount;j++){
                        pTable->item(i,j)->setBackground(gnssUnSelected);
                    }
                    pTable->clearSelection();
                    break;
                }
            }
        }
    }
}

//select the whole frequency row when click the item of frequency
void GNSS_FreqMeas_Order::Item_clicked(QTableWidgetItem *tableItem){
    QTableWidget *pTable=tableItem->tableWidget();
    int irow=tableItem->row(), icolumn=tableItem->column();
    if (irow>0&&icolumn==0){ //clicked frequency
        pTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        pTable->selectRow(irow);
        pTable->setSelectionBehavior(QAbstractItemView::SelectItems);
    } else if (irow>0&&icolumn>0) {//clicked measurement
        pTable->setCurrentCell(irow,icolumn);
    }
}
//exchange between two frequency rows
void GNSS_FreqMeas_Order::moveFreqRow(QTableWidget *pTable, int currentRow, int toRow, int doubleClickFlag)
{
    int nRowCount = pTable->rowCount();
    int nColumnCount = pTable->columnCount();

    if (currentRow<0 || toRow<0 || currentRow>=nRowCount || toRow>=nRowCount) return;
    //return if it's not the frequency column
    if (currentRow==0) return;
    //return if it's the first frequency and "Up" is clicked
    if (currentRow==1&&toRow<currentRow) return;
    //return if currentRow frequency or toRow frequency is unselected
    if (!doubleClickFlag&&(pTable->item(currentRow,0)->background().color().name()==RedColor||pTable->item(toRow,0)->background().color().name()==RedColor)) return;
    if (pTable == nullptr)
        return;

    if (currentRow == toRow) return;

    int insertRow=toRow;
    if (toRow < currentRow) currentRow++;
    else insertRow++;

    pTable->insertRow(insertRow);

    for (int i = 0; i <nColumnCount;i++) {
        pTable->setItem(insertRow,i,pTable->takeItem(currentRow,i));
    }

    pTable->removeRow(currentRow);
    pTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    pTable->selectRow(toRow);
    pTable->setSelectionBehavior(QAbstractItemView::SelectItems);
}
//exchange between two Measurements Columns
void GNSS_FreqMeas_Order::moveMeasColumn(QTableWidget *pTable, int currentColumn, int toColumn, int doubleClickFlag)
{
    int iRow=pTable->currentRow();
    int nColumnCount = pTable->columnCount();

    if (currentColumn<0 || toColumn <0 || currentColumn>=nColumnCount || toColumn>=nColumnCount) return;
    //return if it's not the measurement
    if (currentColumn==0||iRow==0) return;
    //return if it's the first measurement and "<<" is clicked
    if (currentColumn==1&&toColumn<currentColumn) return;
    //return if currentRow measurement or toRow measurement is unselected
    if (!doubleClickFlag&&(pTable->item(iRow,currentColumn)->background().color().name()==RedColor||pTable->item(iRow,toColumn)->background().color().name()==RedColor)) return;
    if (pTable == nullptr)
        return;

    if (currentColumn == toColumn) return;

    if (pTable->item(iRow,currentColumn)->text()==""||pTable->item(iRow,toColumn)->text()=="") return;

    QString Meas1,Meas2;
    int moveStep=currentColumn<toColumn?1:-1;
    for (int i=0; abs(i)<abs(currentColumn-toColumn); i+=moveStep){
        Meas1=pTable->item(iRow,currentColumn+i)->text();
        Meas2=pTable->item(iRow,currentColumn+i+moveStep)->text();
        pTable->item(iRow,currentColumn+i)->setText(Meas2);
        pTable->item(iRow,currentColumn+i+moveStep)->setText(Meas1);
    }

    pTable->setCurrentCell(iRow,toColumn);
}

void GNSS_FreqMeas_Order::setFreqMeasdefaults(){
    this->SetDefaultGPS();
    this->SetDefaultGalileo();
    this->SetDefaultGLONASS();
    this->SetDefaultGEO();
    this->SetDefaultBDS();
    this->SetDefaultQZSS();
    this->SetDefaultIRNSS();
}

//turn to specified constellation page when click the corresponding pushButton
void GNSS_FreqMeas_Order::on_pushButtonGPS_clicked(){
    uiFreqMeas->stackedWidgetFreqMeasGNSS->setCurrentIndex(GPS);
    uiFreqMeas->labelSelectPRNFor->setText("GPS:");
    uiFreqMeas->pushButtonGalileo->setChecked(false);
    uiFreqMeas->pushButtonGLONASS->setChecked(false);
    uiFreqMeas->pushButtonGEO->setChecked(false);
    uiFreqMeas->pushButtonBDS->setChecked(false);
    uiFreqMeas->pushButtonQZSS->setChecked(false);
    uiFreqMeas->pushButtonIRNSS->setChecked(false);
    uiFreqMeas->pushButtonGPS->setChecked(true);
}
void GNSS_FreqMeas_Order::on_pushButtonGalileo_clicked(){
    uiFreqMeas->stackedWidgetFreqMeasGNSS->setCurrentIndex(Galileo);
    uiFreqMeas->labelSelectPRNFor->setText("Galileo:");
    uiFreqMeas->pushButtonGPS->setChecked(false);
    uiFreqMeas->pushButtonGLONASS->setChecked(false);
    uiFreqMeas->pushButtonGEO->setChecked(false);
    uiFreqMeas->pushButtonBDS->setChecked(false);
    uiFreqMeas->pushButtonQZSS->setChecked(false);
    uiFreqMeas->pushButtonIRNSS->setChecked(false);
    uiFreqMeas->pushButtonGalileo->setChecked(true);
}
void GNSS_FreqMeas_Order::on_pushButtonGLONASS_clicked(){
    uiFreqMeas->stackedWidgetFreqMeasGNSS->setCurrentIndex(GLONASS);
    uiFreqMeas->labelSelectPRNFor->setText("GLONASS:");
    uiFreqMeas->pushButtonGPS->setChecked(false);
    uiFreqMeas->pushButtonGalileo->setChecked(false);
    uiFreqMeas->pushButtonGEO->setChecked(false);
    uiFreqMeas->pushButtonBDS->setChecked(false);
    uiFreqMeas->pushButtonQZSS->setChecked(false);
    uiFreqMeas->pushButtonIRNSS->setChecked(false);
    uiFreqMeas->pushButtonGLONASS->setChecked(true);
}
void GNSS_FreqMeas_Order::on_pushButtonGEO_clicked(){
    uiFreqMeas->stackedWidgetFreqMeasGNSS->setCurrentIndex(GEO);
    uiFreqMeas->labelSelectPRNFor->setText("GEO:");
    uiFreqMeas->pushButtonGPS->setChecked(false);
    uiFreqMeas->pushButtonGalileo->setChecked(false);
    uiFreqMeas->pushButtonGLONASS->setChecked(false);
    uiFreqMeas->pushButtonBDS->setChecked(false);
    uiFreqMeas->pushButtonQZSS->setChecked(false);
    uiFreqMeas->pushButtonIRNSS->setChecked(false);
    uiFreqMeas->pushButtonGEO->setChecked(true);
}
void GNSS_FreqMeas_Order::on_pushButtonBDS_clicked(){
    uiFreqMeas->stackedWidgetFreqMeasGNSS->setCurrentIndex(BDS);
    uiFreqMeas->labelSelectPRNFor->setText("BDS:");
    uiFreqMeas->pushButtonGPS->setChecked(false);
    uiFreqMeas->pushButtonGalileo->setChecked(false);
    uiFreqMeas->pushButtonGLONASS->setChecked(false);
    uiFreqMeas->pushButtonGEO->setChecked(false);
    uiFreqMeas->pushButtonQZSS->setChecked(false);
    uiFreqMeas->pushButtonIRNSS->setChecked(false);
    uiFreqMeas->pushButtonBDS->setChecked(true);
}
void GNSS_FreqMeas_Order::on_pushButtonQZSS_clicked(){
    uiFreqMeas->stackedWidgetFreqMeasGNSS->setCurrentIndex(QZSS);
    uiFreqMeas->labelSelectPRNFor->setText("QZSS:");
    uiFreqMeas->pushButtonGPS->setChecked(false);
    uiFreqMeas->pushButtonGalileo->setChecked(false);
    uiFreqMeas->pushButtonGLONASS->setChecked(false);
    uiFreqMeas->pushButtonGEO->setChecked(false);
    uiFreqMeas->pushButtonBDS->setChecked(false);
    uiFreqMeas->pushButtonIRNSS->setChecked(false);
    uiFreqMeas->pushButtonQZSS->setChecked(true);
}
void GNSS_FreqMeas_Order::on_pushButtonIRNSS_clicked(){
    uiFreqMeas->stackedWidgetFreqMeasGNSS->setCurrentIndex(IRNSS);
    uiFreqMeas->labelSelectPRNFor->setText("IRNSS:");
    uiFreqMeas->pushButtonGPS->setChecked(false);
    uiFreqMeas->pushButtonGalileo->setChecked(false);
    uiFreqMeas->pushButtonGLONASS->setChecked(false);
    uiFreqMeas->pushButtonGEO->setChecked(false);
    uiFreqMeas->pushButtonBDS->setChecked(false);
    uiFreqMeas->pushButtonQZSS->setChecked(false);
    uiFreqMeas->pushButtonIRNSS->setChecked(true);
}

//GPS
void GNSS_FreqMeas_Order::SetDefaultGPS(){
    this->on_checkBoxOrderFreqMeasGPS_clicked(false);
    uiFreqMeas->tabWidgetGPS->setCurrentIndex(0);
    //All
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasGPS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasGPS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasGPS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasGPSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasGPS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasGPS->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Code
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasCodeGPSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Phase
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Doppler
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS->item(i,j)->setBackground(MeasSelected);
        }
    }
}
void GNSS_FreqMeas_Order::on_checkBoxOrderFreqMeasGPS_clicked(bool checked){
    uiFreqMeas->checkBoxOrderFreqMeasGPS->setChecked(checked);
    if (!checked) {
        uiFreqMeas->stackedWidgetGPS->setCurrentIndex(0);
    } else {
        uiFreqMeas->stackedWidgetGPS->setCurrentIndex(1);
    }
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqBoostGPS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasGPS->currentColumn()!=0) return;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasGPS,uiFreqMeas->tableWidgetOrderFreqMeasGPS->currentRow(),uiFreqMeas->tableWidgetOrderFreqMeasGPS->currentRow()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqLowerGPS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasGPS->currentColumn()!=0) return;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasGPS,uiFreqMeas->tableWidgetOrderFreqMeasGPS->currentRow(),uiFreqMeas->tableWidgetOrderFreqMeasGPS->currentRow()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasBoostGPS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasGPS,uiFreqMeas->tableWidgetOrderFreqMeasGPS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasGPS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasLowerGPS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasGPS,uiFreqMeas->tableWidgetOrderFreqMeasGPS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasGPS->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqCodeBoostGPS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqCodeLowerGPS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasCodeBoostGPS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS,uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasCodeLowerGPS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS,uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqPhaseBoostGPS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqPhaseLowerGPS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasPhaseBoostGPS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS,uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasPhaseLowerGPS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS,uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqDopplerBoostGPS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqDopplerLowerGPS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGPS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGPS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasDopplerBoostGPS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS,uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasDopplerLowerGPS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS,uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasDopplerGPS->currentColumn()+1,0);
}
//Galileo
void GNSS_FreqMeas_Order::SetDefaultGalileo(){
    this->on_checkBoxOrderFreqMeasGalileo_clicked(false);
    uiFreqMeas->tabWidgetGalileo->setCurrentIndex(0);
    //All
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasGalileo->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasGalileo->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasGalileo->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasGalileoBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasGalileo->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasGalileo->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Code
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileoBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Phase
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileoBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Doppler
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileoBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo->item(i,j)->setBackground(MeasSelected);
        }
    }
}
void GNSS_FreqMeas_Order::on_checkBoxOrderFreqMeasGalileo_clicked(bool checked){
    uiFreqMeas->checkBoxOrderFreqMeasGalileo->setChecked(checked);
    if (!checked) {
        uiFreqMeas->stackedWidgetGalileo->setCurrentIndex(0);
    } else {
        uiFreqMeas->stackedWidgetGalileo->setCurrentIndex(1);
    }
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqBoostGalileo_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasGalileo->currentColumn()!=0) return;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasGalileo,uiFreqMeas->tableWidgetOrderFreqMeasGalileo->currentRow(),uiFreqMeas->tableWidgetOrderFreqMeasGalileo->currentRow()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqLowerGalileo_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasGalileo->currentColumn()!=0) return;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasGalileo,uiFreqMeas->tableWidgetOrderFreqMeasGalileo->currentRow(),uiFreqMeas->tableWidgetOrderFreqMeasGalileo->currentRow()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasBoostGalileo_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasGalileo,uiFreqMeas->tableWidgetOrderFreqMeasGalileo->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasGalileo->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasLowerGalileo_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasGalileo,uiFreqMeas->tableWidgetOrderFreqMeasGalileo->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasGalileo->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqCodeBoostGalileo_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqCodeLowerGalileo_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasCodeBoostGalileo_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo,uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasCodeLowerGalileo_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo,uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqPhaseBoostGalileo_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqPhaseLowerGalileo_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasPhaseBoostGalileo_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo,uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasPhaseLowerGalileo_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo,uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqDopplerBoostGalileo_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqDopplerLowerGalileo_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGalileo,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGalileo,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasDopplerBoostGalileo_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo,uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasDopplerLowerGalileo_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo,uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasDopplerGalileo->currentColumn()+1,0);
}
//GLONASS
void GNSS_FreqMeas_Order::SetDefaultGLONASS(){
    this->on_checkBoxOrderFreqMeasGLONASS_clicked(false);
    uiFreqMeas->tabWidgetGLONASS->setCurrentIndex(0);
    //All
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasGLONASS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasGLONASS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasGLONASS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasGLONASSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasGLONASS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasGLONASS->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Code
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Phase
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Doppler
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS->item(i,j)->setBackground(MeasSelected);
        }
    }
}
void GNSS_FreqMeas_Order::on_checkBoxOrderFreqMeasGLONASS_clicked(bool checked){
    uiFreqMeas->checkBoxOrderFreqMeasGLONASS->setChecked(checked);
    if (!checked) {
        uiFreqMeas->stackedWidgetGLONASS->setCurrentIndex(0);
    } else {
        uiFreqMeas->stackedWidgetGLONASS->setCurrentIndex(1);
    }
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqBoostGLONASS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasGLONASS->currentColumn()!=0) return;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasGLONASS,uiFreqMeas->tableWidgetOrderFreqMeasGLONASS->currentRow(),uiFreqMeas->tableWidgetOrderFreqMeasGLONASS->currentRow()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqLowerGLONASS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasGLONASS->currentColumn()!=0) return;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasGLONASS,uiFreqMeas->tableWidgetOrderFreqMeasGLONASS->currentRow(),uiFreqMeas->tableWidgetOrderFreqMeasGLONASS->currentRow()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasBoostGLONASS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasGLONASS,uiFreqMeas->tableWidgetOrderFreqMeasGLONASS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasGLONASS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasLowerGLONASS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasGLONASS,uiFreqMeas->tableWidgetOrderFreqMeasGLONASS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasGLONASS->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqCodeBoostGLONASS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqCodeLowerGLONASS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasCodeBoostGLONASS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS,uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasCodeLowerGLONASS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS,uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqPhaseBoostGLONASS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqPhaseLowerGLONASS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasPhaseBoostGLONASS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS,uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasPhaseLowerGLONASS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS,uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqDopplerBoostGLONASS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqDopplerLowerGLONASS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGLONASS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGLONASS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasDopplerBoostGLONASS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS,uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasDopplerLowerGLONASS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS,uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasDopplerGLONASS->currentColumn()+1,0);
}
//GEO
void GNSS_FreqMeas_Order::SetDefaultGEO(){
    this->on_checkBoxOrderFreqMeasGEO_clicked(false);
    uiFreqMeas->tabWidgetGEO->setCurrentIndex(0);
    //All
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasGEO->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasGEO->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasGEO->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasGEOBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasGEO->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasGEO->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Code
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasCodeGEOBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Phase
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEOBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Doppler
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEOBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO->item(i,j)->setBackground(MeasSelected);
        }
    }
}
void GNSS_FreqMeas_Order::on_checkBoxOrderFreqMeasGEO_clicked(bool checked){
    uiFreqMeas->checkBoxOrderFreqMeasGEO->setChecked(checked);
    if (!checked) {
        uiFreqMeas->stackedWidgetGEO->setCurrentIndex(0);
    } else {
        uiFreqMeas->stackedWidgetGEO->setCurrentIndex(1);
    }
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqBoostGEO_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasGEO->currentColumn()!=0) return;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasGEO,uiFreqMeas->tableWidgetOrderFreqMeasGEO->currentRow(),uiFreqMeas->tableWidgetOrderFreqMeasGEO->currentRow()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqLowerGEO_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasGEO->currentColumn()!=0) return;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasGEO,uiFreqMeas->tableWidgetOrderFreqMeasGEO->currentRow(),uiFreqMeas->tableWidgetOrderFreqMeasGEO->currentRow()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasBoostGEO_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasGEO,uiFreqMeas->tableWidgetOrderFreqMeasGEO->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasGEO->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasLowerGEO_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasGEO,uiFreqMeas->tableWidgetOrderFreqMeasGEO->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasGEO->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqCodeBoostGEO_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqCodeLowerGEO_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasCodeBoostGEO_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO,uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasCodeLowerGEO_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO,uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqPhaseBoostGEO_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqPhaseLowerGEO_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasPhaseBoostGEO_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO,uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasPhaseLowerGEO_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO,uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqDopplerBoostGEO_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqDopplerLowerGEO_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeGEO,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseGEO,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasDopplerBoostGEO_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO,uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasDopplerLowerGEO_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO,uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasDopplerGEO->currentColumn()+1,0);
}
//BDS
void GNSS_FreqMeas_Order::SetDefaultBDS(){
    this->on_checkBoxOrderFreqMeasBDS_clicked(false);
    uiFreqMeas->tabWidgetBDS->setCurrentIndex(0);
    //All
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasBDS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasBDS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasBDS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasBDSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasBDS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasBDS->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Code
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasCodeBDSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Phase
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Doppler
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS->item(i,j)->setBackground(MeasSelected);
        }
    }
}
void GNSS_FreqMeas_Order::on_checkBoxOrderFreqMeasBDS_clicked(bool checked){
    uiFreqMeas->checkBoxOrderFreqMeasBDS->setChecked(checked);
    if (!checked) {
        uiFreqMeas->stackedWidgetBDS->setCurrentIndex(0);
    } else {
        uiFreqMeas->stackedWidgetBDS->setCurrentIndex(1);
    }
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqBoostBDS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasBDS->currentColumn()!=0) return;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasBDS,uiFreqMeas->tableWidgetOrderFreqMeasBDS->currentRow(),uiFreqMeas->tableWidgetOrderFreqMeasBDS->currentRow()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqLowerBDS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasBDS->currentColumn()!=0) return;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasBDS,uiFreqMeas->tableWidgetOrderFreqMeasBDS->currentRow(),uiFreqMeas->tableWidgetOrderFreqMeasBDS->currentRow()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasBoostBDS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasBDS,uiFreqMeas->tableWidgetOrderFreqMeasBDS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasBDS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasLowerBDS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasBDS,uiFreqMeas->tableWidgetOrderFreqMeasBDS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasBDS->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqCodeBoostBDS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqCodeLowerBDS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasCodeBoostBDS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS,uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasCodeLowerBDS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS,uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqPhaseBoostBDS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqPhaseLowerBDS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasPhaseBoostBDS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS,uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasPhaseLowerBDS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS,uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqDopplerBoostBDS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqDopplerLowerBDS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeBDS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseBDS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasDopplerBoostBDS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS,uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasDopplerLowerBDS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS,uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasDopplerBDS->currentColumn()+1,0);
}
//QZSS
void GNSS_FreqMeas_Order::SetDefaultQZSS(){
    this->on_checkBoxOrderFreqMeasQZSS_clicked(false);
    uiFreqMeas->tabWidgetQZSS->setCurrentIndex(0);
    //All
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasQZSS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasQZSS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasQZSS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasQZSSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasQZSS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasQZSS->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Code
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Phase
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Doppler
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS->item(i,j)->setBackground(MeasSelected);
        }
    }
}
void GNSS_FreqMeas_Order::on_checkBoxOrderFreqMeasQZSS_clicked(bool checked){
    uiFreqMeas->checkBoxOrderFreqMeasQZSS->setChecked(checked);
    if (!checked) {
        uiFreqMeas->stackedWidgetQZSS->setCurrentIndex(0);
    } else {
        uiFreqMeas->stackedWidgetQZSS->setCurrentIndex(1);
    }
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqBoostQZSS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasQZSS->currentColumn()!=0) return;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasQZSS,uiFreqMeas->tableWidgetOrderFreqMeasQZSS->currentRow(),uiFreqMeas->tableWidgetOrderFreqMeasQZSS->currentRow()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqLowerQZSS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasQZSS->currentColumn()!=0) return;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasQZSS,uiFreqMeas->tableWidgetOrderFreqMeasQZSS->currentRow(),uiFreqMeas->tableWidgetOrderFreqMeasQZSS->currentRow()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasBoostQZSS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasQZSS,uiFreqMeas->tableWidgetOrderFreqMeasQZSS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasQZSS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasLowerQZSS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasQZSS,uiFreqMeas->tableWidgetOrderFreqMeasQZSS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasQZSS->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqCodeBoostQZSS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqCodeLowerQZSS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasCodeBoostQZSS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS,uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasCodeLowerQZSS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS,uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqPhaseBoostQZSS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqPhaseLowerQZSS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasPhaseBoostQZSS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS,uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasPhaseLowerQZSS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS,uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqDopplerBoostQZSS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqDopplerLowerQZSS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeQZSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseQZSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasDopplerBoostQZSS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS,uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasDopplerLowerQZSS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS,uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasDopplerQZSS->currentColumn()+1,0);
}
//IRNSS
void GNSS_FreqMeas_Order::SetDefaultIRNSS(){
    this->on_checkBoxOrderFreqMeasIRNSS_clicked(false);
    uiFreqMeas->tabWidgetIRNSS->setCurrentIndex(0);
    //All
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasIRNSS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasIRNSS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasIRNSS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasIRNSSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasIRNSS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasIRNSS->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Code
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Phase
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS->item(i,j)->setBackground(MeasSelected);
        }
    }
    //Doppler
    for (int i=1; i<uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS->rowCount(); i++){
        for (int j=0; j<uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS->columnCount(); j++) {
            uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS->item(i,j)->setText(uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSSBackUp->item(i,j)->text());
            if (j==0) uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS->item(i,j)->setBackground(FreqSelected);
            else uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS->item(i,j)->setBackground(MeasSelected);
        }
    }
}
void GNSS_FreqMeas_Order::on_checkBoxOrderFreqMeasIRNSS_clicked(bool checked){
    uiFreqMeas->checkBoxOrderFreqMeasIRNSS->setChecked(checked);
    if (!checked) {
        uiFreqMeas->stackedWidgetIRNSS->setCurrentIndex(0);
    } else {
        uiFreqMeas->stackedWidgetIRNSS->setCurrentIndex(1);
    }
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqBoostIRNSS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasIRNSS->currentColumn()!=0) return;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasIRNSS,uiFreqMeas->tableWidgetOrderFreqMeasIRNSS->currentRow(),uiFreqMeas->tableWidgetOrderFreqMeasIRNSS->currentRow()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqLowerIRNSS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasIRNSS->currentColumn()!=0) return;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasIRNSS,uiFreqMeas->tableWidgetOrderFreqMeasIRNSS->currentRow(),uiFreqMeas->tableWidgetOrderFreqMeasIRNSS->currentRow()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasBoostIRNSS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasIRNSS,uiFreqMeas->tableWidgetOrderFreqMeasIRNSS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasIRNSS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasLowerIRNSS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasIRNSS,uiFreqMeas->tableWidgetOrderFreqMeasIRNSS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasIRNSS->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqCodeBoostIRNSS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqCodeLowerIRNSS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasCodeBoostIRNSS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS,uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasCodeLowerIRNSS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS,uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqPhaseBoostIRNSS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqPhaseLowerIRNSS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasPhaseBoostIRNSS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS,uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasPhaseLowerIRNSS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS,uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS->currentColumn()+1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqDopplerBoostIRNSS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS->currentRow()-1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderFreqDopplerLowerIRNSS_clicked(){
    if (uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS->currentColumn()!=0) return;
    int cRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS->currentRow(),tRow=uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS->currentRow()+1;
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasCodeIRNSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasPhaseIRNSS,cRow,tRow,0);
    this->moveFreqRow(uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS,cRow,tRow,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasDopplerBoostIRNSS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS,uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS->currentColumn()-1,0);
}
void GNSS_FreqMeas_Order::on_pushButtonOrderMeasDopplerLowerIRNSS_clicked(){
    this->moveMeasColumn(uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS,uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS->currentColumn(),uiFreqMeas->tableWidgetOrderFreqMeasDopplerIRNSS->currentColumn()+1,0);
}

// Function to select GPS satellites
void GNSS_FreqMeas_Order::changePushButtonGPS(bool checked){
    uiFreqMeas->pushButtonGPS->setEnabled(checked);
    this->SetDefaultGPS();
}
// Function to select Galileo satellites
void GNSS_FreqMeas_Order::changePushButtonGalileo(bool checked){
    uiFreqMeas->pushButtonGalileo->setEnabled(checked);
    this->SetDefaultGalileo();
}
// Function to select GLONASS satellites
void GNSS_FreqMeas_Order::changePushButtonGLONASS(bool checked){
    uiFreqMeas->pushButtonGLONASS->setEnabled(checked);
    this->SetDefaultGLONASS();
}
// Function to select GEO satellites
void GNSS_FreqMeas_Order::changePushButtonGEO(bool checked){
    uiFreqMeas->pushButtonGEO->setEnabled(checked);
    this->SetDefaultGEO();
}
// Function to select BDS satellites
void GNSS_FreqMeas_Order::changePushButtonBDS(bool checked){
    uiFreqMeas->pushButtonBDS->setEnabled(checked);
    this->SetDefaultBDS();
}
// Function to select QZSS satellites
void GNSS_FreqMeas_Order::changePushButtonQZSS(bool checked){
    uiFreqMeas->pushButtonQZSS->setEnabled(checked);
    this->SetDefaultQZSS();
}
// Function to select IRNSS satellites
void GNSS_FreqMeas_Order::changePushButtonIRNSS(bool checked){
    uiFreqMeas->pushButtonIRNSS->setEnabled(checked);
    this->SetDefaultIRNSS();
}

// Function to configure GPS satellites
void GNSS_FreqMeas_Order::on_pushButtonPublicGPS_clicked(){
    this->on_pushButtonGPS_clicked();
}
// Function to configure Galileo satellites
void GNSS_FreqMeas_Order::on_pushButtonPublicGalileo_clicked(){
    this->on_pushButtonGalileo_clicked();
}
// Function to configure GLONASS satellites
void GNSS_FreqMeas_Order::on_pushButtonPublicGLONASS_clicked(){
    this->on_pushButtonGLONASS_clicked();
}
// Function to configure GEO satellites
void GNSS_FreqMeas_Order::on_pushButtonPublicGEO_clicked(){
    this->on_pushButtonGEO_clicked();
}
// Function to configure BDS satellites
void GNSS_FreqMeas_Order::on_pushButtonPublicBDS_clicked(){
    this->on_pushButtonBDS_clicked();
}
// Function to configure QZSS satellites
void GNSS_FreqMeas_Order::on_pushButtonPublicQZSS_clicked(){
    this->on_pushButtonQZSS_clicked();
}
// Function to configure IRNSS satellites
void GNSS_FreqMeas_Order::on_pushButtonPublicIRNSS_clicked(){
    this->on_pushButtonIRNSS_clicked();
}

void GNSS_FreqMeas_Order::changeCurrentPage(){
    for (int i=0; i<MAX_GNSS; i++){
        if (PushButtonGNSS[i]->isEnabled()){
            (this->*PushButtonGNSSFunctions[i])();
            break;
        }
    }
}

//Function to get command line options
void GNSS_FreqMeas_Order::getgLABOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString) {
    QString FreqOptions="",MeasOptions="";
    if (warningString->length()<0) *warningString=""; //only to avoid the warning of unused "warningString"
    if (errorString->length()<0) *errorString=""; //only to avoid the warning of unused "warningString"
    //loop of constellations
    for (int gnssi=0; gnssi<MAX_GNSS; gnssi++){
        int forAllMeas = ( CheckBoxGNSSOrder[gnssi]->isChecked()? 0 : 1 );
        for (int tablei=0; tablei<4; tablei++){
            if ( forAllMeas==1 && tablei>0 ) break;
            else if ( forAllMeas==0 && tablei==0 ) continue;
            else if ( forAllMeas==0 && tablei==3 ) continue; //Remove this line when Doppler is used again!!!
            //rowNum = nFreqGNSS[gnssi]+1, colNum = number of measurements
            int rowNum=TableGNSS[gnssi][tablei]->rowCount(),colNum=TableGNSS[gnssi][tablei]->columnCount();
            //Frequency
            QString freqSelect="",freqUnselect="";
            //loop of rows (frequencies)
            for (int rowi=1; rowi<rowNum; rowi++){
                QString freqN=TableGNSS[gnssi][tablei]->item(rowi,0)->text().mid(1,1);
                int freqIndex=0;
                //get freqIndex
                for (int freqi=0; freqi<nFreqGNSS[gnssi]; freqi++){
                    if (freqN==FreqGNSSList[gnssi][freqi]){
                        freqIndex=freqi;
                        break;
                    }
                }
                //unselected frequency
                if (TableGNSS[gnssi][tablei]->item(rowi,0)->background().color().name()==RedColor) {
                    freqUnselect += freqN;
                }
                //selected frequency
                else {
                    freqSelect += freqN;
                    //Measurement
                    QString measSelect="",measUnselect="";
                    //loop of columns (measurements)
                    for (int coli=1; coli<colNum; coli++){
                        //unselected measurement
                        if (TableGNSS[gnssi][tablei]->item(rowi,coli)->background().color().name()==RedColor) {
                            measUnselect+=TableGNSS[gnssi][tablei]->item(rowi,coli)->text().mid(2-forAllMeas,1);
                        }
                        //selected measurement
                        else measSelect+=TableGNSS[gnssi][tablei]->item(rowi,coli)->text().mid(2-forAllMeas,1);
                    }
                    //check if the selected measurements are in the same of order of default and then save to MeasOptions
                    if (measSelect.size()>0 && MeasGNSSOrder[gnssi][freqIndex].contains(measSelect,Qt::CaseInsensitive)==false ){
                        MeasOptions+= " " + indentifierGNSS[gnssi] + "0-" + ObsType[tablei] + freqN + "-" + measSelect;
                    }
                    //save unselected measurements to MeasOptions
                    if (measUnselect.size()>0){
                        MeasOptions+= " -" + indentifierGNSS[gnssi] + "0-" + ObsType[tablei] + freqN + "-" + measUnselect;
                    }
                }
            }
            //check if the selected frequencies are in the same of order of default and then save to MeasOptions
            if ( tablei<2 && freqSelect.size()>0 && FreqGNSSOrder[gnssi].contains(freqSelect)==false ){
                FreqOptions+= " " + indentifierGNSS[gnssi] + "0-" + freqSelect;
            }
            //save unselected frequencies to MeasOptions
            if ( tablei<2 && freqUnselect.size()>0){
                FreqOptions+= " -" + indentifierGNSS[gnssi] + "0-" + freqUnselect;
            }
        }
    }
    //-pre:freqorder
    if (FreqOptions.length()>1){
        FreqOptions = "-pre:freqorder" + FreqOptions;
        *saveString += FreqOptions + "\n";
        QStringList tmpString = FreqOptions.split(QRegularExpression("\\s+"));
        for(int k=0;k<tmpString.size();k++) {
            *runString << tmpString[k];
        }
    }
    //-pre:measorder
    if (MeasOptions.length()>1){
        MeasOptions = "-pre:measorder" + MeasOptions;
        *saveString += MeasOptions + "\n";
        QStringList tmpString = MeasOptions.split(QRegularExpression("\\s+"));
        for(int k=0;k<tmpString.size();k++) {
            *runString << tmpString[k];
        }
    }
}
//Function to convert command line options to GUI configuration
void GNSS_FreqMeas_Order::loadgLABOptions(QString *warningString, QStringList *ParametersList, const int freqMeas){
    int nPar=ParametersList->count();
    /* set frequency */
    if (freqMeas==1) {
        //loop parameters
        for (int iPar=0; iPar<nPar; iPar++){
            int iGNSS=-1;
            QStringList FreqParList = ParametersList->at(iPar).split("-", QString::SkipEmptyParts);

            bool ParamSatRanges=ParametersList->at(iPar).contains(QRegularExpression(regExpSatWithRanges));
            bool ParamSatNoRanges=FreqParList[0].contains(QRegularExpression(regExpSatNoRanges));
            if(!ParamSatNoRanges && !ParamSatRanges ) {
               *warningString += "FILTER: Invalid argument '" + ParametersList->at(iPar) + "' for parameter '-pre:freqorder'. It was skipped.\n";
               continue;
            } else if (ParamSatRanges) {
               *warningString += "FILTER: The GUI cannot read arguments with satellite ranges (except '-pre:sat'), as options are constellations wise. Measurement '" + ParametersList->at(iPar) + "' was skipped and not validated (it must be validated in command line).\n";
               continue;
            }

            //find frequency list
            if (FreqParList.count()<2) {
                *warningString += "FILTER: Argument '" + ParametersList->at(iPar) + "' to parameter '-pre:freqorder' is missing the frequency list. It was skipped.\n";
                continue;
            }
            //select or unselect
            int selFlag = ParametersList->at(iPar).mid(0,1)=="-"?0:1;
            //loop constellation for frequency order
            if (selFlag==1) {
                for (iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
                    if ( FreqParList[0].contains(indentifierGNSS[iGNSS],Qt::CaseInsensitive) || FreqParList[0].mid(0,1)=="0" ) {
                        //loop table
                        int badFreqFound=0;
                        for (int itable=0; itable<4; itable++){
                            int rowNum=TableGNSS[iGNSS][itable]->rowCount();
                            //loop frequency from low priority to high
                            QString wrongFreq="";
                            for (int iF=FreqParList.last().size()-1; iF>=0; iF--){
                                //loop row
                                int foundRow=0;
                                for (int irow=1; irow<rowNum; irow++){
                                    if ( TableGNSS[iGNSS][itable]->item(irow,0)->text().mid(1,1) == FreqParList.last().mid(iF,1) ) {
                                        if (TableGNSS[iGNSS][itable]->item(irow,0)->background().color().name()==RedColor) {
                                            freqDoubleClicked(TableGNSS[iGNSS][itable]->item(irow,0));
                                        }
                                        moveFreqRow(TableGNSS[iGNSS][itable],irow,1,0);
                                        TableGNSS[iGNSS][itable]->clearSelection();
                                        foundRow=1;
                                        break;
                                    }
                                }
                                if (foundRow==0) {
                                    if (badFreqFound==0) {
                                        wrongFreq+=", " + FreqParList.last().mid(iF,1);
                                    }
                                }
                            }
                            if (wrongFreq!="") {
                                wrongFreq=wrongFreq.mid(2); //To remove leading comma and space
                                QString pluralAttrib=wrongFreq.length()>1?"ies":"y";
                                QString pluralDoes=wrongFreq.length()>1?"":"es";
                                int lastCommaIndex=wrongFreq.lastIndexOf(",");
                                if (lastCommaIndex>=0) {
                                    wrongFreq.replace(lastCommaIndex,1," and ");
                                }
                                *warningString += "FILTER: Frequenc" + pluralAttrib + " " + wrongFreq + " in argument '" + ParametersList->at(iPar) + "' do" + pluralDoes + " not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                                badFreqFound=1;
                            }
                        }
                    }
                }
            //loop constellation for unselect frequency
            } else if (selFlag==0) {
                for (iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
                    if (FreqParList[0].contains(indentifierGNSS[iGNSS],Qt::CaseInsensitive)) {
                        //loop table
                        int badFreqFound=0;
                        for (int itable=0; itable<4; itable++){
                            int rowNum=TableGNSS[iGNSS][itable]->rowCount();
                            //loop frequency from low priority to high
                            QString wrongFreq="";
                            for (int iF=FreqParList.last().size()-1; iF>=0; iF--){
                                //loop row
                                int foundRow=0;
                                for (int irow=1; irow<rowNum; irow++){
                                    if ( TableGNSS[iGNSS][itable]->item(irow,0)->text().mid(1,1) == FreqParList.last().mid(iF,1) ) {
                                        if (TableGNSS[iGNSS][itable]->item(irow,0)->background().color().name()!=RedColor) {
                                            freqDoubleClicked(TableGNSS[iGNSS][itable]->item(irow,0));
                                            TableGNSS[iGNSS][itable]->clearSelection();
                                            foundRow=1;
                                            break;
                                        }
                                    }
                                }
                                if (foundRow==0) {
                                    if (badFreqFound==0) {
                                        wrongFreq+=", " + FreqParList.last().mid(iF,1);
                                    }
                                }
                            }
                            if (wrongFreq!="") {
                                wrongFreq=wrongFreq.mid(2); //To remove leading comma and space
                                QString pluralAttrib=wrongFreq.length()>1?"ies":"y";
                                QString pluralDoes=wrongFreq.length()>1?"":"es";
                                int lastCommaIndex=wrongFreq.lastIndexOf(",");
                                if (lastCommaIndex>=0) {
                                    wrongFreq.replace(lastCommaIndex,1," and ");
                                }
                                *warningString += "FILTER: Frequenc" + pluralAttrib + " " + wrongFreq + " in argument '" + ParametersList->at(iPar) + "' do" + pluralDoes + " not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                                badFreqFound=1;
                            }
                        }
                    }
                }
            }
        }
    }
    /* set measurement */
    else {
        //loop parameters
        for (int iPar=0; iPar<nPar; iPar++){
            int iGNSS=-1;
            //find frequency & measurement list
            QStringList FMParList = ParametersList->at(iPar).split("-", QString::SkipEmptyParts);
            QString     wrongAttrib="";
            bool ParamSatRanges=ParametersList->at(iPar).contains(QRegularExpression(regExpSatWithRanges));
            bool ParamSatNoRanges=FMParList[0].contains(QRegularExpression(regExpSatNoRanges));
            if(!ParamSatNoRanges && !ParamSatRanges ) {
               *warningString += "FILTER: Invalid argument '" + ParametersList->at(iPar) + "' for parameter '-pre:measorder'. It was skipped.\n";
               continue;
            } else if (ParamSatRanges) {
               *warningString += "FILTER: The GUI cannot read arguments with satellite ranges (except '-pre:sat'), as options are constellations wise. Measurement '" + ParametersList->at(iPar) + "' was skipped and not validated (it must be validated in command line).\n";
               continue;
            }
            if (FMParList.count()<3) {
                *warningString += "FILTER: Argument '" + ParametersList->at(iPar) + "' to parameter '-pre:measorder' is missing the measurements types or frequencies or attributes. It was skipped.\n";
                continue;
            }
            //select or unselect
            int selFlag = ParametersList->at(iPar).mid(0,1)=="-"?0:1;
            //get frequency option and measurement option
            QString freqBuff=FMParList[1].toUpper();
            QString measOpt=FMParList.last().toUpper();
            QString freqOpt="";
            //get measurement type (all, code, phase, doppler)
            int measType[4]={0};
            int skipMeas=0;
            for (int iF=0; iF<freqBuff.size(); iF++){
                if (freqBuff.mid(iF,1)=="C") measType[1]=1;
                else if (freqBuff.mid(iF,1)=="L") measType[2]=1;
                else if (freqBuff.mid(iF,1)=="D") measType[3]=1;
                else if ( freqBuff[iF]>='0' && freqBuff[iF]<='9') freqOpt += freqBuff[iF];
                else {
                    *warningString += "FILTER: Invalid frequency or measurement type '" + FMParList[1].mid(iF,1) + "'  in argument '" + ParametersList->at(iPar) + "' to parameter '-pre:measorder'. It was skipped.\n";
                    skipMeas=1;
                    break;
                }
            }
            if (skipMeas==1) continue;
            if (freqOpt=="") {
                *warningString += "FILTER: Missing frequency in argument '" + ParametersList->at(iPar) + "' to parameter '-pre:measorder'. It was skipped.\n";
                continue;
            } else if (measType[1]==0 && measType[2]==0 && measType[3]==0 ) {
                *warningString += "FILTER: Missing measurement type in argument '" + ParametersList->at(iPar) + "' to parameter '-pre:measorder'. It was skipped.\n";
                continue;
            }
            //set for all measurement?
            if ( measType[1]==1 && measType[2]==1 && measType[3]==1 ) {
                measType[0]=1;
                measType[1]=measType[2]=measType[3]=0;
            }
            //loop constellation for measurement order
            if (selFlag==1) {
                for (iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
                    if ( FMParList[0].contains(indentifierGNSS[iGNSS],Qt::CaseInsensitive) || FMParList[0].mid(0,1)=="0" ) {
                        //Check frequencies exist in constellation
                        for (int iF=0;iF<freqOpt.size();iF++) {
                            int iM;
                            for (iM=0;iM<nFreqGNSS[iGNSS];iM++) {
                                if(freqOpt.mid(iF,1)==FreqGNSSList[iGNSS][iM]) break;
                            }
                            if (iM==nFreqGNSS[iGNSS]) {
                                *warningString += "FILTER: Frequency " + freqOpt[iF] + " in argument '" + ParametersList->at(iPar) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                            }
                        }
                        if (measType[0]) (this->*GroupBoxGNSSOrder[iGNSS])(false);
                        else (this->*GroupBoxGNSSOrder[iGNSS])(true);
                        //loop table
                        int lastType=-1,badAttribFound=0;
                        for (int itable=0; itable<4; itable++){
                            if (measType[itable]==0) continue;
                            int rowNum=TableGNSS[iGNSS][itable]->rowCount(),colNum=TableGNSS[iGNSS][itable]->columnCount();
                            //loop table row
                            for (int irow=1; irow<rowNum; irow++){
                                QString wrongAttrib="";
                                if ( freqOpt.contains(TableGNSS[iGNSS][itable]->item(irow,0)->text().mid(1,1)) ) {
                                    //loop measurement
                                    for (int iM=measOpt.size()-1;iM>=0;iM--){
                                        int foundMeas=0;
                                        for (int icol=1; icol<colNum; icol++){
                                            //Check for empty cell, otherwise "back()" functions crashes program if it is empty
                                            if (TableGNSS[iGNSS][itable]->item(irow,icol)->text()=="") continue;
                                            int stringSize=TableGNSS[iGNSS][itable]->item(irow,icol)->text().size();
                                            if ( TableGNSS[iGNSS][itable]->item(irow,icol)->text().at(stringSize-1)==measOpt[iM] ){
                                                if (TableGNSS[iGNSS][itable]->item(irow,0)->background().color().name()!=RedColor) {
                                                    if (TableGNSS[iGNSS][itable]->item(irow,icol)->background().color().name()==RedColor) {
                                                        Item_doubleClicked(TableGNSS[iGNSS][itable]->item(irow,icol));
                                                        TableGNSS[iGNSS][itable]->clearSelection();
                                                    }
                                                    TableGNSS[iGNSS][itable]->setCurrentCell(irow,icol);
                                                    moveMeasColumn(TableGNSS[iGNSS][itable],icol,1,0);
                                                    TableGNSS[iGNSS][itable]->clearSelection();
                                                }
                                                foundMeas=1;
                                                break;
                                            }
                                        }
                                        if (foundMeas==0) {
                                            if (badAttribFound==0) {
                                                wrongAttrib=FMParList.last()[iM] + wrongAttrib;
                                            }
                                        }
                                    }
                                }
                                if (wrongAttrib!="") {
                                    QString pluralAttrib=wrongAttrib.length()>1?"s":"";
                                    QString pluralDoes=wrongAttrib.length()>1?"":"es";
                                    *warningString += "FILTER: Attribute" + pluralAttrib + " '" + wrongAttrib + "' in argument '" + ParametersList->at(iPar) + "' do" + pluralDoes + " not exist for " + GNSSName[iGNSS] + " in frequency " + TableGNSS[iGNSS][itable]->item(irow,0)->text().mid(1,1) + ". It was skipped.\n";
                                    lastType=itable;
                                }
                            }
                            if (lastType!=-1) {
                               badAttribFound=1;
                            }
                        }
                    }
                }
            }
            //loop constellation for unselect measurement
            else if (selFlag==0) {
                for (iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
                    if ( FMParList[0].contains(indentifierGNSS[iGNSS],Qt::CaseInsensitive) || FMParList[0].mid(0,1)=="0" ) {
                        //Check frequencies exist in constellation
                        for (int iF=0;iF<freqOpt.size();iF++) {
                            int iM;
                            for (iM=0;iM<nFreqGNSS[iGNSS];iM++) {
                                if(freqOpt.mid(iF,1)==FreqGNSSList[iGNSS][iM]) break;
                            }
                            if (iM==nFreqGNSS[iGNSS]) {
                                *warningString += "FILTER: Frequency " + freqOpt[iF] + " in argument '" + ParametersList->at(iPar) + "' does not exist for " + GNSSName[iGNSS] + ". It was skipped.\n";
                            }
                        }
                        if (measType[0]) (this->*GroupBoxGNSSOrder[iGNSS])(false);
                        else (this->*GroupBoxGNSSOrder[iGNSS])(true);
                        //loop table
                        int lastType=-1,badAttribFound=0;
                        for (int itable=0; itable<4; itable++) {

                            if (measType[itable]==0) continue;
                            int rowNum=TableGNSS[iGNSS][itable]->rowCount(),colNum=TableGNSS[iGNSS][itable]->columnCount();
                            //loop table row
                            for (int irow=1; irow<rowNum; irow++) {
                                QString wrongAttrib="";
                                if ( freqOpt.contains(TableGNSS[iGNSS][itable]->item(irow,0)->text().mid(1,1)) ) {
                                    //loop measurement
                                    for (int iM=measOpt.size()-1;iM>=0;iM--){
                                        int foundMeas=0;
                                        for (int icol=1; icol<colNum; icol++){
                                            if (TableGNSS[iGNSS][itable]->item(irow,icol)->text()=="") continue;
                                            int stringSize=TableGNSS[iGNSS][itable]->item(irow,icol)->text().size();
                                            if ( TableGNSS[iGNSS][itable]->item(irow,icol)->text().at(stringSize-1)==measOpt[iM] ){
                                                if (TableGNSS[iGNSS][itable]->item(irow,0)->background().color().name()!=RedColor) {
                                                    if (TableGNSS[iGNSS][itable]->item(irow,icol)->background().color().name()!=RedColor) {
                                                        Item_doubleClicked(TableGNSS[iGNSS][itable]->item(irow,icol));
                                                        TableGNSS[iGNSS][itable]->clearSelection();
                                                    }
                                                }
                                                foundMeas=1;
                                                break;
                                            }
                                        }
                                        if (foundMeas==0) {
                                            if (badAttribFound==0) {
                                                wrongAttrib=FMParList.last()[iM] + wrongAttrib;
                                            }
                                        }
                                    }
                                }
                                if (wrongAttrib!="") {
                                    QString pluralAttrib=wrongAttrib.length()>1?"s":"";
                                    QString pluralDoes=wrongAttrib.length()>1?"":"es";
                                    *warningString += "FILTER: Attribute" + pluralAttrib + " '" + wrongAttrib + "' in argument '" + ParametersList->at(iPar) + "' do" + pluralDoes + " not exist for " + GNSSName[iGNSS] + " in frequency " + TableGNSS[iGNSS][itable]->item(irow,0)->text().mid(1,1) + ". It was skipped.\n";
                                    lastType=itable;
                                }
                            }
                            if (lastType!=-1) {
                               badAttribFound=1;
                            }
                        }
                    }
                }
            }
        }
    }
}

void GNSS_FreqMeas_Order::on_pushButtonFreqMeasOrderDefault_clicked(){
    this->setFreqMeasdefaults();
}
void GNSS_FreqMeas_Order::on_pushButtonFreqMeasOrderOk_clicked(){
    this->OkFlag=1;
    this->close();
}
void GNSS_FreqMeas_Order::on_pushButtonFreqMeasOrderCancel_clicked(){
    this->OkFlag=0;
    this->close();
}
