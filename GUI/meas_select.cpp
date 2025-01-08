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
#include "meas_select.h"
#include "ui_meas_select.h"

QStringList EmptyMeas = (QStringList() << "");
QStringList GNSSFreqTypeMeas[MAX_GNSS][MAX_GNSS_FREQ][5] = {
    //GPS
    {
        //F1
        {
            //C
            QStringList() << "C1P" << "C1W" << "C1C" << "C1Y" << "C1L" << "C1S" << "C1X" << "C1M",
            //L
            QStringList() << "L1P" << "L1W" << "L1C" << "L1Y" << "L1L" << "L1S" << "L1X" << "L1M" << "L1N",
            //S
            QStringList() << "S1P" << "S1W" << "S1C" << "S1Y" << "S1L" << "S1S" << "S1X" << "S1M" << "S1N",
            //D
            QStringList() << "D1P" << "D1W" << "D1C" << "D1Y" << "D1L" << "D1S" << "D1X" << "D1M" << "D1N",
            //LLI
            QStringList() << "LLI1P" << "LLI1W" << "LLI1C" << "LLI1Y" << "LLI1L" << "LLI1S" << "LLI1X" << "LLI1M" << "LLI1N"
        },
        //F2
        {
            //C
            QStringList() << "C2P" << "C2W" << "C2C" << "C2Y" << "C2L" << "C2S" << "C2X" << "C2D" << "C2M",
            //L
            QStringList() << "L2P" << "L2W" << "L2C" << "L2Y" << "L2L" << "L2S" << "L2X" << "L2D" << "L2M" << "L2N",
            //S
            QStringList() << "S2P" << "S2W" << "S2C" << "S2Y" << "S2L" << "S2S" << "S2X" << "S2D" << "S2M" << "S2N",
            //D
            QStringList() << "D2P" << "D2W" << "D2C" << "D2Y" << "D2L" << "D2S" << "D2X" << "D2D" << "D2M" << "D2N",
            //LLI
            QStringList() << "LLI2P" << "LLI2W" << "LLI2C" << "LLI2Y" << "LLI2L" << "LLI2S" << "LLI2X" << "LLI2D" << "LLI2M" << "LLI2N"
        },
        //F3
        {
            //C
            QStringList() << "C5Q" << "C5I" << "C5X",
            //L
            QStringList() << "L5Q" << "L5I" << "L5X",
            //S
            QStringList() << "S5Q" << "S5I" << "S5X",
            //D
            QStringList() << "D5Q" << "D5I" << "D5X",
            //LLI
            QStringList() << "LLI5Q" << "LLI5I" << "LLI5X"
        }
    },
    //Galileo
    {
        //F1
        {
            //C
            QStringList() << "C1C" << "C1X" << "C1Z" << "C1B" << "C1A",
            //L
            QStringList() << "L1C" << "L1X" << "L1Z" << "L1B" << "L1A",
            //S
            QStringList() << "S1C" << "S1X" << "S1Z" << "S1B" << "S1A",
            //D
            QStringList() << "D1C" << "D1X" << "D1Z" << "D1B" << "D1A",
            //LLI
            QStringList() << "LLI1C" << "LLI1X" << "LLI1Z" << "LLI1B" << "LLI1A"
        },
        //F5
        {
            //C
            QStringList() << "C5Q" << "C5I" << "C5X",
            //L
            QStringList() << "L5Q" << "L5I" << "L5X",
            //S
            QStringList() << "S5Q" << "S5I" << "S5X",
            //D
            QStringList() << "D5Q" << "D5I" << "D5X",
            //LLI
            QStringList() << "LLI5Q" << "LLI5I" << "LLI5X"
        },
        //F6
        {
            //C
            QStringList() << "C6C" << "C6X" << "C6Z" << "C6B" << "C6A",
            //L
            QStringList() << "L6C" << "L6X" << "L6Z" << "L6B" << "L6A",
            //S
            QStringList() << "S6C" << "S6X" << "S6Z" << "S6B" << "S6A",
            //D
            QStringList() << "D6C" << "D6X" << "D6Z" << "D6B" << "D6A",
            //LLI
            QStringList() << "LLI6C" << "LLI6X" << "LLI6Z" << "LLI6B" << "LLI6A"
        },
        //F7
        {
            //C
            QStringList() << "C7Q" << "C7I" << "C7X",
            //L
            QStringList() << "L7Q" << "L7I" << "L7X",
            //S
            QStringList() << "S7Q" << "S7I" << "S7X",
            //D
            QStringList() << "D7Q" << "D7I" << "D7X",
            //LLI
            QStringList() << "LLI7Q" << "LLI7I" << "LLI7X"
        },
        //F8
        {
            //C
            QStringList() << "C8Q" << "C8I" << "C8X",
            //L
            QStringList() << "L8Q" << "L8I" << "L8X",
            //S
            QStringList() << "S8Q" << "S8I" << "S8X",
            //D
            QStringList() << "D8Q" << "D8I" << "D8X",
            //LLI
            QStringList() << "LLI8Q" << "LLI8I" << "LLI8X"
        }
    },
    //GLONASS
    {
        //F1
        {
            //C
            QStringList() << "C1P" << "C1C",
            //L
            QStringList() << "L1P" << "L1C",
            //S
            QStringList() << "S1P" << "S1C",
            //D
            QStringList() << "D1P" << "D1C",
            //LLI
            QStringList() << "LLI1P" << "LLI1C"
        },
        //F2
        {
            //C
            QStringList() << "C2P" << "C2C",
            //L
            QStringList() << "L2P" << "L2C",
            //S
            QStringList() << "S2P" << "S2C",
            //D
            QStringList() << "D2P" << "D2C",
            //LLI
            QStringList() << "LLI2P" << "LLI2C"
        },
        //F3
        {
            //C
            QStringList() << "C3Q" << "C3I" << "C3X",
            //L
            QStringList() << "L3Q" << "L3I" << "L3X",
            //S
            QStringList() << "S3Q" << "S3I" << "S3X",
            //D
            QStringList() << "D3Q" << "D3I" << "D3X",
            //LLI
            QStringList() << "LLI3Q" << "LLI3I" << "LLI3X"
        },
        //F4
        {
            //C
            QStringList() << "C4A" << "C4B" << "C4X",
            //L
            QStringList() << "L4A" << "L4B" << "L4X",
            //S
            QStringList() << "S4A" << "S4B" << "S4X",
            //D
            QStringList() << "D4A" << "D4B" << "D4X",
            //LLI
            QStringList() << "LLI4A" << "LLI4B" << "LLI4X"
        },
        //F6
        {
            //C
            QStringList() << "C6A" << "C6B" << "C6X",
            //L
            QStringList() << "L6A" << "L6B" << "L6X",
            //S
            QStringList() << "S6A" << "S6B" << "S6X",
            //D
            QStringList() << "D6A" << "D6B" << "D6X",
            //LLI
            QStringList() << "LLI6A" << "LLI6B" << "LLI6X"
        }
    },
    //GEO
    {
        //F1
        {
            //C
            QStringList() << "C1C",
            //L
            QStringList() << "L1C",
            //S
            QStringList() << "S1C",
            //D
            QStringList() << "D1C",
            //LLI
            QStringList() << "LLI1C"
        },
        //F5
        {
            //C
            QStringList() << "C5Q" << "C5I" << "C5X",
            //L
            QStringList() << "L5Q" << "L5I" << "L5X",
            //S
            QStringList() << "S5Q" << "S5I" << "S5X",
            //D
            QStringList() << "D5Q" << "D5I" << "D5X",
            //LLI
            QStringList() << "LLI5Q" << "LLI5I" << "LLI5X"
        }
    },
    //BDS
    {
        //F1
        {
            //C
            QStringList() << "C1P" << "C1D" << "C1L" << "C1S" << "C1X" << "C1Z",
            //L
            QStringList() << "L1P" << "L1D" << "L1L" << "L1S" << "L1X" << "L1Z",
            //S
            QStringList() << "S1P" << "S1D" << "S1L" << "S1S" << "S1X" << "S1Z",
            //D
            QStringList() << "D1P" << "D1D" << "D1L" << "D1S" << "D1X" << "D1Z",
            //LLI
            QStringList() << "LLI1P" << "LLI1D" << "LLI1L" << "LLI1S" << "LLI1X" << "LLI1Z"
        },
        //F2
        {
            //C
            QStringList() << "C2Q" << "C2I" << "C2X",
            //L
            QStringList() << "L2Q" << "L2I" << "L2X",
            //S
            QStringList() << "S2Q" << "S2I" << "S2X",
            //D
            QStringList() << "D2Q" << "D2I" << "D2X",
            //LLI
            QStringList() << "LLI2Q" << "LLI2I" << "LLI2X"
        },
        //F5
        {
            //C
            QStringList() << "C5P" << "C5D" << "C5X",
            //L
            QStringList() << "L5P" << "L5D" << "L5X",
            //S
            QStringList() << "S5P" << "S5D" << "S5X",
            //D
            QStringList() << "D5P" << "D5D" << "D5X",
            //LLI
            QStringList() << "LLI5P" << "LLI5D" << "LLI5X"
        },
        //F6
        {
            //C
            QStringList() << "C6Q" << "C6I" << "C6P" << "C6D" << "C6X" << "C6Z",
            //L
            QStringList() << "L6Q" << "L6I" << "L6P" << "L6D" << "L6X" << "L6Z",
            //S
            QStringList() << "S6Q" << "S6I" << "S6P" << "S6D" << "S6X" << "S6Z",
            //D
            QStringList() << "D6Q" << "D6I" << "D6P" << "D6D" << "D6X" << "D6Z",
            //LLI
            QStringList() << "LLI6Q" << "LLI6I" << "LLI6P" << "LLI6D" << "LLI6X" << "LLI6Z"
        },
        //F7
        {
            //C
            QStringList() << "C7Q" << "C7I" << "C7P" << "C7D" << "C7X" << "C7Z",
            //L
            QStringList() << "L7Q" << "L7I" << "L7P" << "L7D" << "L7X" << "L7Z",
            //S
            QStringList() << "S7Q" << "S7I" << "S7P" << "S7D" << "S7X" << "S7Z",
            //D
            QStringList() << "D7Q" << "D7I" << "D7P" << "D7D" << "D7X" << "D7Z",
            //LLI
            QStringList() << "LLI7Q" << "LLI7I" << "LLI7P" << "LLI7D" << "LLI7X" << "LLI7Z"
        },
        //F8
        {
            //C
            QStringList() << "C8P" << "C8D" << "C8X",
            //L
            QStringList() << "L8P" << "L8D" << "L8X",
            //S
            QStringList() << "S8P" << "S8D" << "S8X",
            //D
            QStringList() << "D8P" << "D8D" << "D8X",
            //LLI
            QStringList() << "LLI8P" << "LLI8D" << "LLI8X"
        }
    },
    //QZSS
    {
        //F1
        {
            //C
            QStringList() << "C1C" << "C1L" << "C1S" << "C1E" << "C1X" << "C1Z" << "C1B",
            //L
            QStringList() << "L1C" << "L1L" << "L1S" << "L1E" << "L1X" << "L1Z" << "L1B",
            //S
            QStringList() << "S1C" << "S1L" << "S1S" << "S1E" << "S1X" << "S1Z" << "S1B",
            //D
            QStringList() << "D1C" << "D1L" << "D1S" << "D1E" << "D1X" << "D1Z" << "D1B",
            //LLI
            QStringList() << "LLI1C" << "LLI1L" << "LLI1S" << "LLI1E" << "LLI1X" << "LLI1Z" << "LLI1B"
        },
        //F2
        {
            //C
            QStringList() << "C2L" << "C2S" << "C2X",
            //L
            QStringList() << "L2L" << "L2S" << "L2X",
            //S
            QStringList() << "S2L" << "S2S" << "S2X",
            //D
            QStringList() << "D2L" << "D2S" << "D2X",
            //LLI
            QStringList() << "LLI2L" << "LLI2S" << "LLI2X"
        },
        //F5
        {
            //C
            QStringList() << "C5Q" << "C5I" << "C5P" << "C5D" << "C5X" << "C5Z",
            //L
            QStringList() << "L5Q" << "L5I" << "L5P" << "L5D" << "L5X" << "L5Z",
            //S
            QStringList() << "S5Q" << "S5I" << "S5P" << "S5D" << "S5X" << "S5Z",
            //D
            QStringList() << "D5Q" << "D5I" << "D5P" << "D5D" << "D5X" << "D5Z",
            //LLI
            QStringList() << "LLI5Q" << "LLI5I" << "LLI5P" << "LLI5D" << "LLI5X" << "LLI5Z"
        },
        //F6
        {
            //C
            QStringList() << "C6L" << "C6S" << "C6X" << "C6E" << "C6Z",
            //L
            QStringList() << "L6L" << "L6S" << "L6X" << "L6E" << "L6Z",
            //S
            QStringList() << "S6L" << "S6S" << "S6X" << "S6E" << "S6Z",
            //D
            QStringList() << "D6L" << "D6S" << "D6X" << "D6E" << "D6Z",
            //LLI
            QStringList() << "LLI6L" << "LLI6S" << "LLI6X" << "LLI6E" << "LLI6Z"
        }
    },
    //IRNSS
    {
        //F5
        {
            //C
            QStringList() << "C5A" << "C5C" << "C5B" << "C5X",
            //L
            QStringList() << "L5A" << "L5C" << "L5B" << "L5X",
            //S
            QStringList() << "S5A" << "S5C" << "S5B" << "S5X",
            //D
            QStringList() << "D5A" << "D5C" << "D5B" << "D5X",
            //LLI
            QStringList() << "LLI5A" << "LLI5C" << "LLI5B" << "LLI5X"
        },
        //F9
        {
            //C
            QStringList() << "C9A" << "C9C" << "C9B" << "C9X",
            //L
            QStringList() << "L9A" << "L9C" << "L9B" << "L9X",
            //S
            QStringList() << "S9A" << "S9C" << "S9B" << "S9X",
            //D
            QStringList() << "D9A" << "D9C" << "D9B" << "D9X",
            //LLI
            QStringList() << "LLI9A" << "LLI9C" << "LLI9B" << "LLI9X"
        }
    }
};

GNSS_Meas_Select::GNSS_Meas_Select(QWidget *parent) :
    QDialog(parent),
    uiMeas(new Ui::GNSS_Meas_Select)
{
    uiMeas->setupUi(this);

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

    for (int i=0; i<MAX_GNSS; i++) nPrint[i]=0;

    OkFlag=0;
    MeasFlag=0;
    this->setWindowTitle("Select the Measurements to Print in MEAS Message");

    //Init variable with pointers to PushButtons pointers
    this->InitPushButtonGNSSPointers();
    //Init variable with pointers to PushButtons function pointers
    this->InitPushButtonGNSSMinFuncPointers();
    //Init variable with pointers to weights
    this->InitMeasPointers();

    this->setMeasdefaults();

    uiMeas->pushButtonMeasSelectOk->setFocus();

    uiMeas->pushButtonMeasSelectCancel->setHidden(true); //Remove when Cancel buttons undo all changes made by the user
}

GNSS_Meas_Select::~GNSS_Meas_Select()
{
    delete uiMeas;
}

//Function to initialize pointers to CheckBox widget pointers
void GNSS_Meas_Select::InitPushButtonGNSSPointers(){
    PushButtonGNSS[GPS]=uiMeas->pushButtonGPS;
    PushButtonGNSS[Galileo]=uiMeas->pushButtonGalileo;
    PushButtonGNSS[GLONASS]=uiMeas->pushButtonGLONASS;
    PushButtonGNSS[GEO]=uiMeas->pushButtonGEO;
    PushButtonGNSS[BDS]=uiMeas->pushButtonBDS;
    PushButtonGNSS[QZSS]=uiMeas->pushButtonQZSS;
    PushButtonGNSS[IRNSS]=uiMeas->pushButtonIRNSS;
}
//Function to initialize pointers to pushButton GNSS Measurements _clicked() functions
void GNSS_Meas_Select::InitPushButtonGNSSMinFuncPointers(){
    PushButtonGNSSFunctions[GPS]=&GNSS_Meas_Select::on_pushButtonGPS_clicked;
    PushButtonGNSSFunctions[Galileo]=&GNSS_Meas_Select::on_pushButtonGalileo_clicked;
    PushButtonGNSSFunctions[GLONASS]=&GNSS_Meas_Select::on_pushButtonGLONASS_clicked;
    PushButtonGNSSFunctions[GEO]=&GNSS_Meas_Select::on_pushButtonGEO_clicked;
    PushButtonGNSSFunctions[BDS]=&GNSS_Meas_Select::on_pushButtonBDS_clicked;
    PushButtonGNSSFunctions[QZSS]=&GNSS_Meas_Select::on_pushButtonQZSS_clicked;
    PushButtonGNSSFunctions[IRNSS]=&GNSS_Meas_Select::on_pushButtonIRNSS_clicked;
}
//Function to initialize pointers to RadioButton and LineEdit of Specify of GERSCJI
void GNSS_Meas_Select::InitMeasPointers(){
    //GPS
    FrameGNSSLabel[GPS][0]=uiMeas->frameLabelGPS1;
    FrameGNSSLabel[GPS][1]=uiMeas->frameLabelGPS2;
    FrameGNSSPrint[GPS][0]=uiMeas->frameMeasGPS_1;
    FrameGNSSPrint[GPS][1]=uiMeas->frameMeasGPS_2;
    FrameGNSSPrint[GPS][2]=uiMeas->frameMeasGPS_3;
    FrameGNSSPrint[GPS][3]=uiMeas->frameMeasGPS_4;
    FrameGNSSPrint[GPS][4]=uiMeas->frameMeasGPS_5;
    FrameGNSSPrint[GPS][5]=uiMeas->frameMeasGPS_6;
    FrameGNSSPrint[GPS][6]=uiMeas->frameMeasGPS_7;
    FrameGNSSPrint[GPS][7]=uiMeas->frameMeasGPS_8;
    FrameGNSSPrint[GPS][8]=uiMeas->frameMeasGPS_9;
    FrameGNSSPrint[GPS][9]=uiMeas->frameMeasGPS_10;
    ComBoBoxGNSSFreq[GPS][0]=uiMeas->comboBoxFreqGPS_1;
    ComBoBoxGNSSFreq[GPS][1]=uiMeas->comboBoxFreqGPS_2;
    ComBoBoxGNSSFreq[GPS][2]=uiMeas->comboBoxFreqGPS_3;
    ComBoBoxGNSSFreq[GPS][3]=uiMeas->comboBoxFreqGPS_4;
    ComBoBoxGNSSFreq[GPS][4]=uiMeas->comboBoxFreqGPS_5;
    ComBoBoxGNSSFreq[GPS][5]=uiMeas->comboBoxFreqGPS_6;
    ComBoBoxGNSSFreq[GPS][6]=uiMeas->comboBoxFreqGPS_7;
    ComBoBoxGNSSFreq[GPS][7]=uiMeas->comboBoxFreqGPS_8;
    ComBoBoxGNSSFreq[GPS][8]=uiMeas->comboBoxFreqGPS_9;
    ComBoBoxGNSSFreq[GPS][9]=uiMeas->comboBoxFreqGPS_10;
    ComBoBoxGNSSType[GPS][0]=uiMeas->comboBoxTypeGPS_1;
    ComBoBoxGNSSType[GPS][1]=uiMeas->comboBoxTypeGPS_2;
    ComBoBoxGNSSType[GPS][2]=uiMeas->comboBoxTypeGPS_3;
    ComBoBoxGNSSType[GPS][3]=uiMeas->comboBoxTypeGPS_4;
    ComBoBoxGNSSType[GPS][4]=uiMeas->comboBoxTypeGPS_5;
    ComBoBoxGNSSType[GPS][5]=uiMeas->comboBoxTypeGPS_6;
    ComBoBoxGNSSType[GPS][6]=uiMeas->comboBoxTypeGPS_7;
    ComBoBoxGNSSType[GPS][7]=uiMeas->comboBoxTypeGPS_8;
    ComBoBoxGNSSType[GPS][8]=uiMeas->comboBoxTypeGPS_9;
    ComBoBoxGNSSType[GPS][9]=uiMeas->comboBoxTypeGPS_10;
    ComBoBoxGNSSMeas[GPS][0]=uiMeas->comboBoxMeasGPS_1;
    ComBoBoxGNSSMeas[GPS][1]=uiMeas->comboBoxMeasGPS_2;
    ComBoBoxGNSSMeas[GPS][2]=uiMeas->comboBoxMeasGPS_3;
    ComBoBoxGNSSMeas[GPS][3]=uiMeas->comboBoxMeasGPS_4;
    ComBoBoxGNSSMeas[GPS][4]=uiMeas->comboBoxMeasGPS_5;
    ComBoBoxGNSSMeas[GPS][5]=uiMeas->comboBoxMeasGPS_6;
    ComBoBoxGNSSMeas[GPS][6]=uiMeas->comboBoxMeasGPS_7;
    ComBoBoxGNSSMeas[GPS][7]=uiMeas->comboBoxMeasGPS_8;
    ComBoBoxGNSSMeas[GPS][8]=uiMeas->comboBoxMeasGPS_9;
    ComBoBoxGNSSMeas[GPS][9]=uiMeas->comboBoxMeasGPS_10;
    //Galileo
    FrameGNSSLabel[Galileo][0]=uiMeas->frameLabelGalileo1;
    FrameGNSSLabel[Galileo][1]=uiMeas->frameLabelGalileo2;
    FrameGNSSPrint[Galileo][0]=uiMeas->frameMeasGalileo_1;
    FrameGNSSPrint[Galileo][1]=uiMeas->frameMeasGalileo_2;
    FrameGNSSPrint[Galileo][2]=uiMeas->frameMeasGalileo_3;
    FrameGNSSPrint[Galileo][3]=uiMeas->frameMeasGalileo_4;
    FrameGNSSPrint[Galileo][4]=uiMeas->frameMeasGalileo_5;
    FrameGNSSPrint[Galileo][5]=uiMeas->frameMeasGalileo_6;
    FrameGNSSPrint[Galileo][6]=uiMeas->frameMeasGalileo_7;
    FrameGNSSPrint[Galileo][7]=uiMeas->frameMeasGalileo_8;
    FrameGNSSPrint[Galileo][8]=uiMeas->frameMeasGalileo_9;
    FrameGNSSPrint[Galileo][9]=uiMeas->frameMeasGalileo_10;
    ComBoBoxGNSSFreq[Galileo][0]=uiMeas->comboBoxFreqGalileo_1;
    ComBoBoxGNSSFreq[Galileo][1]=uiMeas->comboBoxFreqGalileo_2;
    ComBoBoxGNSSFreq[Galileo][2]=uiMeas->comboBoxFreqGalileo_3;
    ComBoBoxGNSSFreq[Galileo][3]=uiMeas->comboBoxFreqGalileo_4;
    ComBoBoxGNSSFreq[Galileo][4]=uiMeas->comboBoxFreqGalileo_5;
    ComBoBoxGNSSFreq[Galileo][5]=uiMeas->comboBoxFreqGalileo_6;
    ComBoBoxGNSSFreq[Galileo][6]=uiMeas->comboBoxFreqGalileo_7;
    ComBoBoxGNSSFreq[Galileo][7]=uiMeas->comboBoxFreqGalileo_8;
    ComBoBoxGNSSFreq[Galileo][8]=uiMeas->comboBoxFreqGalileo_9;
    ComBoBoxGNSSFreq[Galileo][9]=uiMeas->comboBoxFreqGalileo_10;
    ComBoBoxGNSSType[Galileo][0]=uiMeas->comboBoxTypeGalileo_1;
    ComBoBoxGNSSType[Galileo][1]=uiMeas->comboBoxTypeGalileo_2;
    ComBoBoxGNSSType[Galileo][2]=uiMeas->comboBoxTypeGalileo_3;
    ComBoBoxGNSSType[Galileo][3]=uiMeas->comboBoxTypeGalileo_4;
    ComBoBoxGNSSType[Galileo][4]=uiMeas->comboBoxTypeGalileo_5;
    ComBoBoxGNSSType[Galileo][5]=uiMeas->comboBoxTypeGalileo_6;
    ComBoBoxGNSSType[Galileo][6]=uiMeas->comboBoxTypeGalileo_7;
    ComBoBoxGNSSType[Galileo][7]=uiMeas->comboBoxTypeGalileo_8;
    ComBoBoxGNSSType[Galileo][8]=uiMeas->comboBoxTypeGalileo_9;
    ComBoBoxGNSSType[Galileo][9]=uiMeas->comboBoxTypeGalileo_10;
    ComBoBoxGNSSMeas[Galileo][0]=uiMeas->comboBoxMeasGalileo_1;
    ComBoBoxGNSSMeas[Galileo][1]=uiMeas->comboBoxMeasGalileo_2;
    ComBoBoxGNSSMeas[Galileo][2]=uiMeas->comboBoxMeasGalileo_3;
    ComBoBoxGNSSMeas[Galileo][3]=uiMeas->comboBoxMeasGalileo_4;
    ComBoBoxGNSSMeas[Galileo][4]=uiMeas->comboBoxMeasGalileo_5;
    ComBoBoxGNSSMeas[Galileo][5]=uiMeas->comboBoxMeasGalileo_6;
    ComBoBoxGNSSMeas[Galileo][6]=uiMeas->comboBoxMeasGalileo_7;
    ComBoBoxGNSSMeas[Galileo][7]=uiMeas->comboBoxMeasGalileo_8;
    ComBoBoxGNSSMeas[Galileo][8]=uiMeas->comboBoxMeasGalileo_9;
    ComBoBoxGNSSMeas[Galileo][9]=uiMeas->comboBoxMeasGalileo_10;
    //GLONASS
    FrameGNSSLabel[GLONASS][0]=uiMeas->frameLabelGLONASS1;
    FrameGNSSLabel[GLONASS][1]=uiMeas->frameLabelGLONASS2;
    FrameGNSSPrint[GLONASS][0]=uiMeas->frameMeasGLONASS_1;
    FrameGNSSPrint[GLONASS][1]=uiMeas->frameMeasGLONASS_2;
    FrameGNSSPrint[GLONASS][2]=uiMeas->frameMeasGLONASS_3;
    FrameGNSSPrint[GLONASS][3]=uiMeas->frameMeasGLONASS_4;
    FrameGNSSPrint[GLONASS][4]=uiMeas->frameMeasGLONASS_5;
    FrameGNSSPrint[GLONASS][5]=uiMeas->frameMeasGLONASS_6;
    FrameGNSSPrint[GLONASS][6]=uiMeas->frameMeasGLONASS_7;
    FrameGNSSPrint[GLONASS][7]=uiMeas->frameMeasGLONASS_8;
    FrameGNSSPrint[GLONASS][8]=uiMeas->frameMeasGLONASS_9;
    FrameGNSSPrint[GLONASS][9]=uiMeas->frameMeasGLONASS_10;
    ComBoBoxGNSSFreq[GLONASS][0]=uiMeas->comboBoxFreqGLONASS_1;
    ComBoBoxGNSSFreq[GLONASS][1]=uiMeas->comboBoxFreqGLONASS_2;
    ComBoBoxGNSSFreq[GLONASS][2]=uiMeas->comboBoxFreqGLONASS_3;
    ComBoBoxGNSSFreq[GLONASS][3]=uiMeas->comboBoxFreqGLONASS_4;
    ComBoBoxGNSSFreq[GLONASS][4]=uiMeas->comboBoxFreqGLONASS_5;
    ComBoBoxGNSSFreq[GLONASS][5]=uiMeas->comboBoxFreqGLONASS_6;
    ComBoBoxGNSSFreq[GLONASS][6]=uiMeas->comboBoxFreqGLONASS_7;
    ComBoBoxGNSSFreq[GLONASS][7]=uiMeas->comboBoxFreqGLONASS_8;
    ComBoBoxGNSSFreq[GLONASS][8]=uiMeas->comboBoxFreqGLONASS_9;
    ComBoBoxGNSSFreq[GLONASS][9]=uiMeas->comboBoxFreqGLONASS_10;
    ComBoBoxGNSSType[GLONASS][0]=uiMeas->comboBoxTypeGLONASS_1;
    ComBoBoxGNSSType[GLONASS][1]=uiMeas->comboBoxTypeGLONASS_2;
    ComBoBoxGNSSType[GLONASS][2]=uiMeas->comboBoxTypeGLONASS_3;
    ComBoBoxGNSSType[GLONASS][3]=uiMeas->comboBoxTypeGLONASS_4;
    ComBoBoxGNSSType[GLONASS][4]=uiMeas->comboBoxTypeGLONASS_5;
    ComBoBoxGNSSType[GLONASS][5]=uiMeas->comboBoxTypeGLONASS_6;
    ComBoBoxGNSSType[GLONASS][6]=uiMeas->comboBoxTypeGLONASS_7;
    ComBoBoxGNSSType[GLONASS][7]=uiMeas->comboBoxTypeGLONASS_8;
    ComBoBoxGNSSType[GLONASS][8]=uiMeas->comboBoxTypeGLONASS_9;
    ComBoBoxGNSSType[GLONASS][9]=uiMeas->comboBoxTypeGLONASS_10;
    ComBoBoxGNSSMeas[GLONASS][0]=uiMeas->comboBoxMeasGLONASS_1;
    ComBoBoxGNSSMeas[GLONASS][1]=uiMeas->comboBoxMeasGLONASS_2;
    ComBoBoxGNSSMeas[GLONASS][2]=uiMeas->comboBoxMeasGLONASS_3;
    ComBoBoxGNSSMeas[GLONASS][3]=uiMeas->comboBoxMeasGLONASS_4;
    ComBoBoxGNSSMeas[GLONASS][4]=uiMeas->comboBoxMeasGLONASS_5;
    ComBoBoxGNSSMeas[GLONASS][5]=uiMeas->comboBoxMeasGLONASS_6;
    ComBoBoxGNSSMeas[GLONASS][6]=uiMeas->comboBoxMeasGLONASS_7;
    ComBoBoxGNSSMeas[GLONASS][7]=uiMeas->comboBoxMeasGLONASS_8;
    ComBoBoxGNSSMeas[GLONASS][8]=uiMeas->comboBoxMeasGLONASS_9;
    ComBoBoxGNSSMeas[GLONASS][9]=uiMeas->comboBoxMeasGLONASS_10;
    //GEO
    FrameGNSSLabel[GEO][0]=uiMeas->frameLabelGEO1;
    FrameGNSSLabel[GEO][1]=uiMeas->frameLabelGEO2;
    FrameGNSSPrint[GEO][0]=uiMeas->frameMeasGEO_1;
    FrameGNSSPrint[GEO][1]=uiMeas->frameMeasGEO_2;
    FrameGNSSPrint[GEO][2]=uiMeas->frameMeasGEO_3;
    FrameGNSSPrint[GEO][3]=uiMeas->frameMeasGEO_4;
    FrameGNSSPrint[GEO][4]=uiMeas->frameMeasGEO_5;
    FrameGNSSPrint[GEO][5]=uiMeas->frameMeasGEO_6;
    FrameGNSSPrint[GEO][6]=uiMeas->frameMeasGEO_7;
    FrameGNSSPrint[GEO][7]=uiMeas->frameMeasGEO_8;
    FrameGNSSPrint[GEO][8]=uiMeas->frameMeasGEO_9;
    FrameGNSSPrint[GEO][9]=uiMeas->frameMeasGEO_10;
    ComBoBoxGNSSFreq[GEO][0]=uiMeas->comboBoxFreqGEO_1;
    ComBoBoxGNSSFreq[GEO][1]=uiMeas->comboBoxFreqGEO_2;
    ComBoBoxGNSSFreq[GEO][2]=uiMeas->comboBoxFreqGEO_3;
    ComBoBoxGNSSFreq[GEO][3]=uiMeas->comboBoxFreqGEO_4;
    ComBoBoxGNSSFreq[GEO][4]=uiMeas->comboBoxFreqGEO_5;
    ComBoBoxGNSSFreq[GEO][5]=uiMeas->comboBoxFreqGEO_6;
    ComBoBoxGNSSFreq[GEO][6]=uiMeas->comboBoxFreqGEO_7;
    ComBoBoxGNSSFreq[GEO][7]=uiMeas->comboBoxFreqGEO_8;
    ComBoBoxGNSSFreq[GEO][8]=uiMeas->comboBoxFreqGEO_9;
    ComBoBoxGNSSFreq[GEO][9]=uiMeas->comboBoxFreqGEO_10;
    ComBoBoxGNSSType[GEO][0]=uiMeas->comboBoxTypeGEO_1;
    ComBoBoxGNSSType[GEO][1]=uiMeas->comboBoxTypeGEO_2;
    ComBoBoxGNSSType[GEO][2]=uiMeas->comboBoxTypeGEO_3;
    ComBoBoxGNSSType[GEO][3]=uiMeas->comboBoxTypeGEO_4;
    ComBoBoxGNSSType[GEO][4]=uiMeas->comboBoxTypeGEO_5;
    ComBoBoxGNSSType[GEO][5]=uiMeas->comboBoxTypeGEO_6;
    ComBoBoxGNSSType[GEO][6]=uiMeas->comboBoxTypeGEO_7;
    ComBoBoxGNSSType[GEO][7]=uiMeas->comboBoxTypeGEO_8;
    ComBoBoxGNSSType[GEO][8]=uiMeas->comboBoxTypeGEO_9;
    ComBoBoxGNSSType[GEO][9]=uiMeas->comboBoxTypeGEO_10;
    ComBoBoxGNSSMeas[GEO][0]=uiMeas->comboBoxMeasGEO_1;
    ComBoBoxGNSSMeas[GEO][1]=uiMeas->comboBoxMeasGEO_2;
    ComBoBoxGNSSMeas[GEO][2]=uiMeas->comboBoxMeasGEO_3;
    ComBoBoxGNSSMeas[GEO][3]=uiMeas->comboBoxMeasGEO_4;
    ComBoBoxGNSSMeas[GEO][4]=uiMeas->comboBoxMeasGEO_5;
    ComBoBoxGNSSMeas[GEO][5]=uiMeas->comboBoxMeasGEO_6;
    ComBoBoxGNSSMeas[GEO][6]=uiMeas->comboBoxMeasGEO_7;
    ComBoBoxGNSSMeas[GEO][7]=uiMeas->comboBoxMeasGEO_8;
    ComBoBoxGNSSMeas[GEO][8]=uiMeas->comboBoxMeasGEO_9;
    ComBoBoxGNSSMeas[GEO][9]=uiMeas->comboBoxMeasGEO_10;
    //BDS
    FrameGNSSLabel[BDS][0]=uiMeas->frameLabelBDS1;
    FrameGNSSLabel[BDS][1]=uiMeas->frameLabelBDS2;
    FrameGNSSPrint[BDS][0]=uiMeas->frameMeasBDS_1;
    FrameGNSSPrint[BDS][1]=uiMeas->frameMeasBDS_2;
    FrameGNSSPrint[BDS][2]=uiMeas->frameMeasBDS_3;
    FrameGNSSPrint[BDS][3]=uiMeas->frameMeasBDS_4;
    FrameGNSSPrint[BDS][4]=uiMeas->frameMeasBDS_5;
    FrameGNSSPrint[BDS][5]=uiMeas->frameMeasBDS_6;
    FrameGNSSPrint[BDS][6]=uiMeas->frameMeasBDS_7;
    FrameGNSSPrint[BDS][7]=uiMeas->frameMeasBDS_8;
    FrameGNSSPrint[BDS][8]=uiMeas->frameMeasBDS_9;
    FrameGNSSPrint[BDS][9]=uiMeas->frameMeasBDS_10;
    ComBoBoxGNSSFreq[BDS][0]=uiMeas->comboBoxFreqBDS_1;
    ComBoBoxGNSSFreq[BDS][1]=uiMeas->comboBoxFreqBDS_2;
    ComBoBoxGNSSFreq[BDS][2]=uiMeas->comboBoxFreqBDS_3;
    ComBoBoxGNSSFreq[BDS][3]=uiMeas->comboBoxFreqBDS_4;
    ComBoBoxGNSSFreq[BDS][4]=uiMeas->comboBoxFreqBDS_5;
    ComBoBoxGNSSFreq[BDS][5]=uiMeas->comboBoxFreqBDS_6;
    ComBoBoxGNSSFreq[BDS][6]=uiMeas->comboBoxFreqBDS_7;
    ComBoBoxGNSSFreq[BDS][7]=uiMeas->comboBoxFreqBDS_8;
    ComBoBoxGNSSFreq[BDS][8]=uiMeas->comboBoxFreqBDS_9;
    ComBoBoxGNSSFreq[BDS][9]=uiMeas->comboBoxFreqBDS_10;
    ComBoBoxGNSSType[BDS][0]=uiMeas->comboBoxTypeBDS_1;
    ComBoBoxGNSSType[BDS][1]=uiMeas->comboBoxTypeBDS_2;
    ComBoBoxGNSSType[BDS][2]=uiMeas->comboBoxTypeBDS_3;
    ComBoBoxGNSSType[BDS][3]=uiMeas->comboBoxTypeBDS_4;
    ComBoBoxGNSSType[BDS][4]=uiMeas->comboBoxTypeBDS_5;
    ComBoBoxGNSSType[BDS][5]=uiMeas->comboBoxTypeBDS_6;
    ComBoBoxGNSSType[BDS][6]=uiMeas->comboBoxTypeBDS_7;
    ComBoBoxGNSSType[BDS][7]=uiMeas->comboBoxTypeBDS_8;
    ComBoBoxGNSSType[BDS][8]=uiMeas->comboBoxTypeBDS_9;
    ComBoBoxGNSSType[BDS][9]=uiMeas->comboBoxTypeBDS_10;
    ComBoBoxGNSSMeas[BDS][0]=uiMeas->comboBoxMeasBDS_1;
    ComBoBoxGNSSMeas[BDS][1]=uiMeas->comboBoxMeasBDS_2;
    ComBoBoxGNSSMeas[BDS][2]=uiMeas->comboBoxMeasBDS_3;
    ComBoBoxGNSSMeas[BDS][3]=uiMeas->comboBoxMeasBDS_4;
    ComBoBoxGNSSMeas[BDS][4]=uiMeas->comboBoxMeasBDS_5;
    ComBoBoxGNSSMeas[BDS][5]=uiMeas->comboBoxMeasBDS_6;
    ComBoBoxGNSSMeas[BDS][6]=uiMeas->comboBoxMeasBDS_7;
    ComBoBoxGNSSMeas[BDS][7]=uiMeas->comboBoxMeasBDS_8;
    ComBoBoxGNSSMeas[BDS][8]=uiMeas->comboBoxMeasBDS_9;
    ComBoBoxGNSSMeas[BDS][9]=uiMeas->comboBoxMeasBDS_10;
    //QZSS
    FrameGNSSLabel[QZSS][0]=uiMeas->frameLabelQZSS1;
    FrameGNSSLabel[QZSS][1]=uiMeas->frameLabelQZSS2;
    FrameGNSSPrint[QZSS][0]=uiMeas->frameMeasQZSS_1;
    FrameGNSSPrint[QZSS][1]=uiMeas->frameMeasQZSS_2;
    FrameGNSSPrint[QZSS][2]=uiMeas->frameMeasQZSS_3;
    FrameGNSSPrint[QZSS][3]=uiMeas->frameMeasQZSS_4;
    FrameGNSSPrint[QZSS][4]=uiMeas->frameMeasQZSS_5;
    FrameGNSSPrint[QZSS][5]=uiMeas->frameMeasQZSS_6;
    FrameGNSSPrint[QZSS][6]=uiMeas->frameMeasQZSS_7;
    FrameGNSSPrint[QZSS][7]=uiMeas->frameMeasQZSS_8;
    FrameGNSSPrint[QZSS][8]=uiMeas->frameMeasQZSS_9;
    FrameGNSSPrint[QZSS][9]=uiMeas->frameMeasQZSS_10;
    ComBoBoxGNSSFreq[QZSS][0]=uiMeas->comboBoxFreqQZSS_1;
    ComBoBoxGNSSFreq[QZSS][1]=uiMeas->comboBoxFreqQZSS_2;
    ComBoBoxGNSSFreq[QZSS][2]=uiMeas->comboBoxFreqQZSS_3;
    ComBoBoxGNSSFreq[QZSS][3]=uiMeas->comboBoxFreqQZSS_4;
    ComBoBoxGNSSFreq[QZSS][4]=uiMeas->comboBoxFreqQZSS_5;
    ComBoBoxGNSSFreq[QZSS][5]=uiMeas->comboBoxFreqQZSS_6;
    ComBoBoxGNSSFreq[QZSS][6]=uiMeas->comboBoxFreqQZSS_7;
    ComBoBoxGNSSFreq[QZSS][7]=uiMeas->comboBoxFreqQZSS_8;
    ComBoBoxGNSSFreq[QZSS][8]=uiMeas->comboBoxFreqQZSS_9;
    ComBoBoxGNSSFreq[QZSS][9]=uiMeas->comboBoxFreqQZSS_10;
    ComBoBoxGNSSType[QZSS][0]=uiMeas->comboBoxTypeQZSS_1;
    ComBoBoxGNSSType[QZSS][1]=uiMeas->comboBoxTypeQZSS_2;
    ComBoBoxGNSSType[QZSS][2]=uiMeas->comboBoxTypeQZSS_3;
    ComBoBoxGNSSType[QZSS][3]=uiMeas->comboBoxTypeQZSS_4;
    ComBoBoxGNSSType[QZSS][4]=uiMeas->comboBoxTypeQZSS_5;
    ComBoBoxGNSSType[QZSS][5]=uiMeas->comboBoxTypeQZSS_6;
    ComBoBoxGNSSType[QZSS][6]=uiMeas->comboBoxTypeQZSS_7;
    ComBoBoxGNSSType[QZSS][7]=uiMeas->comboBoxTypeQZSS_8;
    ComBoBoxGNSSType[QZSS][8]=uiMeas->comboBoxTypeQZSS_9;
    ComBoBoxGNSSType[QZSS][9]=uiMeas->comboBoxTypeQZSS_10;
    ComBoBoxGNSSMeas[QZSS][0]=uiMeas->comboBoxMeasQZSS_1;
    ComBoBoxGNSSMeas[QZSS][1]=uiMeas->comboBoxMeasQZSS_2;
    ComBoBoxGNSSMeas[QZSS][2]=uiMeas->comboBoxMeasQZSS_3;
    ComBoBoxGNSSMeas[QZSS][3]=uiMeas->comboBoxMeasQZSS_4;
    ComBoBoxGNSSMeas[QZSS][4]=uiMeas->comboBoxMeasQZSS_5;
    ComBoBoxGNSSMeas[QZSS][5]=uiMeas->comboBoxMeasQZSS_6;
    ComBoBoxGNSSMeas[QZSS][6]=uiMeas->comboBoxMeasQZSS_7;
    ComBoBoxGNSSMeas[QZSS][7]=uiMeas->comboBoxMeasQZSS_8;
    ComBoBoxGNSSMeas[QZSS][8]=uiMeas->comboBoxMeasQZSS_9;
    ComBoBoxGNSSMeas[QZSS][9]=uiMeas->comboBoxMeasQZSS_10;
    //IRNSS
    FrameGNSSLabel[IRNSS][0]=uiMeas->frameLabelIRNSS1;
    FrameGNSSLabel[IRNSS][1]=uiMeas->frameLabelIRNSS2;
    FrameGNSSPrint[IRNSS][0]=uiMeas->frameMeasIRNSS_1;
    FrameGNSSPrint[IRNSS][1]=uiMeas->frameMeasIRNSS_2;
    FrameGNSSPrint[IRNSS][2]=uiMeas->frameMeasIRNSS_3;
    FrameGNSSPrint[IRNSS][3]=uiMeas->frameMeasIRNSS_4;
    FrameGNSSPrint[IRNSS][4]=uiMeas->frameMeasIRNSS_5;
    FrameGNSSPrint[IRNSS][5]=uiMeas->frameMeasIRNSS_6;
    FrameGNSSPrint[IRNSS][6]=uiMeas->frameMeasIRNSS_7;
    FrameGNSSPrint[IRNSS][7]=uiMeas->frameMeasIRNSS_8;
    FrameGNSSPrint[IRNSS][8]=uiMeas->frameMeasIRNSS_9;
    FrameGNSSPrint[IRNSS][9]=uiMeas->frameMeasIRNSS_10;
    ComBoBoxGNSSFreq[IRNSS][0]=uiMeas->comboBoxFreqIRNSS_1;
    ComBoBoxGNSSFreq[IRNSS][1]=uiMeas->comboBoxFreqIRNSS_2;
    ComBoBoxGNSSFreq[IRNSS][2]=uiMeas->comboBoxFreqIRNSS_3;
    ComBoBoxGNSSFreq[IRNSS][3]=uiMeas->comboBoxFreqIRNSS_4;
    ComBoBoxGNSSFreq[IRNSS][4]=uiMeas->comboBoxFreqIRNSS_5;
    ComBoBoxGNSSFreq[IRNSS][5]=uiMeas->comboBoxFreqIRNSS_6;
    ComBoBoxGNSSFreq[IRNSS][6]=uiMeas->comboBoxFreqIRNSS_7;
    ComBoBoxGNSSFreq[IRNSS][7]=uiMeas->comboBoxFreqIRNSS_8;
    ComBoBoxGNSSFreq[IRNSS][8]=uiMeas->comboBoxFreqIRNSS_9;
    ComBoBoxGNSSFreq[IRNSS][9]=uiMeas->comboBoxFreqIRNSS_10;
    ComBoBoxGNSSType[IRNSS][0]=uiMeas->comboBoxTypeIRNSS_1;
    ComBoBoxGNSSType[IRNSS][1]=uiMeas->comboBoxTypeIRNSS_2;
    ComBoBoxGNSSType[IRNSS][2]=uiMeas->comboBoxTypeIRNSS_3;
    ComBoBoxGNSSType[IRNSS][3]=uiMeas->comboBoxTypeIRNSS_4;
    ComBoBoxGNSSType[IRNSS][4]=uiMeas->comboBoxTypeIRNSS_5;
    ComBoBoxGNSSType[IRNSS][5]=uiMeas->comboBoxTypeIRNSS_6;
    ComBoBoxGNSSType[IRNSS][6]=uiMeas->comboBoxTypeIRNSS_7;
    ComBoBoxGNSSType[IRNSS][7]=uiMeas->comboBoxTypeIRNSS_8;
    ComBoBoxGNSSType[IRNSS][8]=uiMeas->comboBoxTypeIRNSS_9;
    ComBoBoxGNSSType[IRNSS][9]=uiMeas->comboBoxTypeIRNSS_10;
    ComBoBoxGNSSMeas[IRNSS][0]=uiMeas->comboBoxMeasIRNSS_1;
    ComBoBoxGNSSMeas[IRNSS][1]=uiMeas->comboBoxMeasIRNSS_2;
    ComBoBoxGNSSMeas[IRNSS][2]=uiMeas->comboBoxMeasIRNSS_3;
    ComBoBoxGNSSMeas[IRNSS][3]=uiMeas->comboBoxMeasIRNSS_4;
    ComBoBoxGNSSMeas[IRNSS][4]=uiMeas->comboBoxMeasIRNSS_5;
    ComBoBoxGNSSMeas[IRNSS][5]=uiMeas->comboBoxMeasIRNSS_6;
    ComBoBoxGNSSMeas[IRNSS][6]=uiMeas->comboBoxMeasIRNSS_7;
    ComBoBoxGNSSMeas[IRNSS][7]=uiMeas->comboBoxMeasIRNSS_8;
    ComBoBoxGNSSMeas[IRNSS][8]=uiMeas->comboBoxMeasIRNSS_9;
    ComBoBoxGNSSMeas[IRNSS][9]=uiMeas->comboBoxMeasIRNSS_10;
}

// Function to clean measurement comboBox
void GNSS_Meas_Select::cleanPrintMeas(int iGNSS,int iMeas){
    if (iGNSS<0 || iGNSS>=MAX_GNSS || iMeas<0 || iMeas>9 ) return;
    //clean old items
    for (int i=ComBoBoxGNSSMeas[iGNSS][iMeas]->count()-1; i>=0; i--) ComBoBoxGNSSMeas[iGNSS][iMeas]->removeItem(i);
}

// Function to change measurements for print
void GNSS_Meas_Select::changePrintMeas(int iGNSS,int iFreq,int iType,int iMeas){
    if (iGNSS<0 || iGNSS>=MAX_GNSS || iFreq<0 || iFreq>=nFreqGNSS[iGNSS] || iType<0 || iType>4 || iMeas<0 || iMeas>9 ) return;
    //clean old items
    for (int i=ComBoBoxGNSSMeas[iGNSS][iMeas]->count()-1; i>=0; i--) ComBoBoxGNSSMeas[iGNSS][iMeas]->removeItem(i);
    //assign new items
    for (int i=0; i<GNSSFreqTypeMeas[iGNSS][iFreq][iType].size(); i++) ComBoBoxGNSSMeas[iGNSS][iMeas]->addItem(GNSSFreqTypeMeas[iGNSS][iFreq][iType][i]);
}

void GNSS_Meas_Select::on_pushButtonAddPrint_clicked(){
    int iGNSS=uiMeas->stackedWidgetMeasSelect->currentIndex();
    if (iGNSS<0 || iGNSS>MAX_GNSS || nPrint[iGNSS]>9 ) return;
    FrameGNSSPrint[iGNSS][ nPrint[iGNSS] ]->setHidden(false);
    ComBoBoxGNSSFreq[iGNSS][ nPrint[iGNSS] ]->currentIndexChanged(0);
    nPrint[iGNSS]++;
    if (nPrint[iGNSS]>5) FrameGNSSLabel[iGNSS][1]->setHidden(false);
    if (nPrint[iGNSS]>1) uiMeas->pushButtonDelPrint->setEnabled(true);
    if (nPrint[iGNSS]==10) uiMeas->pushButtonAddPrint->setEnabled(false);

}
void GNSS_Meas_Select::on_pushButtonDelPrint_clicked(){
    int iGNSS=uiMeas->stackedWidgetMeasSelect->currentIndex();
    if (iGNSS<0 || iGNSS>MAX_GNSS || nPrint[iGNSS]<2 ) return;
    FrameGNSSPrint[iGNSS][ nPrint[iGNSS]-1 ]->setHidden(true);
    ComBoBoxGNSSFreq[iGNSS][ nPrint[iGNSS]-1 ]->currentIndexChanged(0);
    nPrint[iGNSS]--;
    if (nPrint[iGNSS]<6) FrameGNSSLabel[iGNSS][1]->setHidden(true);
    if (nPrint[iGNSS]<10) uiMeas->pushButtonAddPrint->setEnabled(true);
    if (nPrint[iGNSS]==1) uiMeas->pushButtonDelPrint->setEnabled(false);
}

// Function to set everything default
void GNSS_Meas_Select::setMeasdefaults(){
    this->SetDefaultMeasGPS();
    this->SetDefaultMeasGalileo();
    this->SetDefaultMeasGLONASS();
    this->SetDefaultMeasGEO();
    this->SetDefaultMeasBDS();
    this->SetDefaultMeasQZSS();
    this->SetDefaultMeasIRNSS();
}

//GPS
// Function to set GPS default
void GNSS_Meas_Select::SetDefaultMeasGPS(){
    nPrint[GPS]=1;
    FrameGNSSLabel[GPS][1]->setHidden(true);
    uiMeas->frameMeasGPS_1->setHidden(false);
    uiMeas->frameMeasGPS_2->setHidden(true);
    uiMeas->frameMeasGPS_3->setHidden(true);
    uiMeas->frameMeasGPS_4->setHidden(true);
    uiMeas->frameMeasGPS_5->setHidden(true);
    uiMeas->frameMeasGPS_6->setHidden(true);
    uiMeas->frameMeasGPS_7->setHidden(true);
    uiMeas->frameMeasGPS_8->setHidden(true);
    uiMeas->frameMeasGPS_9->setHidden(true);
    uiMeas->frameMeasGPS_10->setHidden(true);
    this->on_comboBoxFreqGPS_1_currentIndexChanged(0);
    this->on_comboBoxFreqGPS_2_currentIndexChanged(0);
    this->on_comboBoxFreqGPS_3_currentIndexChanged(0);
    this->on_comboBoxFreqGPS_4_currentIndexChanged(0);
    this->on_comboBoxFreqGPS_5_currentIndexChanged(0);
    this->on_comboBoxFreqGPS_6_currentIndexChanged(0);
    this->on_comboBoxFreqGPS_7_currentIndexChanged(0);
    this->on_comboBoxFreqGPS_8_currentIndexChanged(0);
    this->on_comboBoxFreqGPS_9_currentIndexChanged(0);
    this->on_comboBoxFreqGPS_10_currentIndexChanged(0);
}
// Function to change GPS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGPS_1_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGPS_1->setCurrentIndex(index);
    this->on_comboBoxTypeGPS_1_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGPS_1->setEnabled(false);
        uiMeas->comboBoxMeasGPS_1->setEnabled(false);
        this->cleanPrintMeas(GPS,0);
    } else {
        uiMeas->comboBoxTypeGPS_1->setEnabled(true);
        uiMeas->comboBoxMeasGPS_1->setEnabled(true);
    }
}
// Function to change GPS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGPS_2_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGPS_2->setCurrentIndex(index);
    this->on_comboBoxTypeGPS_2_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGPS_2->setEnabled(false);
        uiMeas->comboBoxMeasGPS_2->setEnabled(false);
        this->cleanPrintMeas(GPS,1);
    } else {
        uiMeas->comboBoxTypeGPS_2->setEnabled(true);
        uiMeas->comboBoxMeasGPS_2->setEnabled(true);
    }
}
// Function to change GPS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGPS_3_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGPS_3->setCurrentIndex(index);
    this->on_comboBoxTypeGPS_3_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGPS_3->setEnabled(false);
        uiMeas->comboBoxMeasGPS_3->setEnabled(false);
        this->cleanPrintMeas(GPS,2);
    } else {
        uiMeas->comboBoxTypeGPS_3->setEnabled(true);
        uiMeas->comboBoxMeasGPS_3->setEnabled(true);
    }
}
// Function to change GPS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGPS_4_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGPS_4->setCurrentIndex(index);
    this->on_comboBoxTypeGPS_4_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGPS_4->setEnabled(false);
        uiMeas->comboBoxMeasGPS_4->setEnabled(false);
        this->cleanPrintMeas(GPS,3);
    } else {
        uiMeas->comboBoxTypeGPS_4->setEnabled(true);
        uiMeas->comboBoxMeasGPS_4->setEnabled(true);
    }
}
// Function to change GPS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGPS_5_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGPS_5->setCurrentIndex(index);
    this->on_comboBoxTypeGPS_5_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGPS_5->setEnabled(false);
        uiMeas->comboBoxMeasGPS_5->setEnabled(false);
        this->cleanPrintMeas(GPS,4);
    } else {
        uiMeas->comboBoxTypeGPS_5->setEnabled(true);
        uiMeas->comboBoxMeasGPS_5->setEnabled(true);
    }
}
// Function to change GPS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGPS_6_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGPS_6->setCurrentIndex(index);
    this->on_comboBoxTypeGPS_6_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGPS_6->setEnabled(false);
        uiMeas->comboBoxMeasGPS_6->setEnabled(false);
        this->cleanPrintMeas(GPS,5);
    } else {
        uiMeas->comboBoxTypeGPS_6->setEnabled(true);
        uiMeas->comboBoxMeasGPS_6->setEnabled(true);
    }
}
// Function to change GPS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGPS_7_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGPS_7->setCurrentIndex(index);
    this->on_comboBoxTypeGPS_7_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGPS_7->setEnabled(false);
        uiMeas->comboBoxMeasGPS_7->setEnabled(false);
        this->cleanPrintMeas(GPS,6);
    } else {
        uiMeas->comboBoxTypeGPS_7->setEnabled(true);
        uiMeas->comboBoxMeasGPS_7->setEnabled(true);
    }
}
// Function to change GPS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGPS_8_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGPS_8->setCurrentIndex(index);
    this->on_comboBoxTypeGPS_8_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGPS_8->setEnabled(false);
        uiMeas->comboBoxMeasGPS_8->setEnabled(false);
        this->cleanPrintMeas(GPS,7);
    } else {
        uiMeas->comboBoxTypeGPS_8->setEnabled(true);
        uiMeas->comboBoxMeasGPS_8->setEnabled(true);
    }
}
// Function to change GPS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGPS_9_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGPS_9->setCurrentIndex(index);
    this->on_comboBoxTypeGPS_9_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGPS_9->setEnabled(false);
        uiMeas->comboBoxMeasGPS_9->setEnabled(false);
        this->cleanPrintMeas(GPS,8);
    } else {
        uiMeas->comboBoxTypeGPS_9->setEnabled(true);
        uiMeas->comboBoxMeasGPS_9->setEnabled(true);
    }
}
// Function to change GPS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGPS_10_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGPS_10->setCurrentIndex(index);
    this->on_comboBoxTypeGPS_10_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGPS_10->setEnabled(false);
        uiMeas->comboBoxMeasGPS_10->setEnabled(false);
        this->cleanPrintMeas(GPS,9);
    } else {
        uiMeas->comboBoxTypeGPS_10->setEnabled(true);
        uiMeas->comboBoxMeasGPS_10->setEnabled(true);
    }
}
// Function to change GPS type comboBox
void GNSS_Meas_Select::on_comboBoxTypeGPS_1_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGPS_1->setCurrentIndex(index);
    this->changePrintMeas(GPS,uiMeas->comboBoxFreqGPS_1->currentIndex()-1,index,0);
}
void GNSS_Meas_Select::on_comboBoxTypeGPS_2_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGPS_2->setCurrentIndex(index);
    this->changePrintMeas(GPS,uiMeas->comboBoxFreqGPS_2->currentIndex()-1,index,1);
}
void GNSS_Meas_Select::on_comboBoxTypeGPS_3_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGPS_3->setCurrentIndex(index);
    this->changePrintMeas(GPS,uiMeas->comboBoxFreqGPS_3->currentIndex()-1,index,2);
}
void GNSS_Meas_Select::on_comboBoxTypeGPS_4_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGPS_4->setCurrentIndex(index);
    this->changePrintMeas(GPS,uiMeas->comboBoxFreqGPS_4->currentIndex()-1,index,3);
}
void GNSS_Meas_Select::on_comboBoxTypeGPS_5_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGPS_5->setCurrentIndex(index);
    this->changePrintMeas(GPS,uiMeas->comboBoxFreqGPS_5->currentIndex()-1,index,4);
}
void GNSS_Meas_Select::on_comboBoxTypeGPS_6_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGPS_6->setCurrentIndex(index);
    this->changePrintMeas(GPS,uiMeas->comboBoxFreqGPS_6->currentIndex()-1,index,5);
}
void GNSS_Meas_Select::on_comboBoxTypeGPS_7_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGPS_7->setCurrentIndex(index);
    this->changePrintMeas(GPS,uiMeas->comboBoxFreqGPS_7->currentIndex()-1,index,6);
}
void GNSS_Meas_Select::on_comboBoxTypeGPS_8_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGPS_8->setCurrentIndex(index);
    this->changePrintMeas(GPS,uiMeas->comboBoxFreqGPS_8->currentIndex()-1,index,7);
}
void GNSS_Meas_Select::on_comboBoxTypeGPS_9_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGPS_9->setCurrentIndex(index);
    this->changePrintMeas(GPS,uiMeas->comboBoxFreqGPS_9->currentIndex()-1,index,8);
}
void GNSS_Meas_Select::on_comboBoxTypeGPS_10_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGPS_10->setCurrentIndex(index);
    this->changePrintMeas(GPS,uiMeas->comboBoxFreqGPS_10->currentIndex()-1,index,9);
}

//Galileo
// Function to set Galileo default
void GNSS_Meas_Select::SetDefaultMeasGalileo(){
    nPrint[Galileo]=1;
    FrameGNSSLabel[Galileo][1]->setHidden(true);
    uiMeas->frameMeasGalileo_1->setHidden(false);
    uiMeas->frameMeasGalileo_2->setHidden(true);
    uiMeas->frameMeasGalileo_3->setHidden(true);
    uiMeas->frameMeasGalileo_4->setHidden(true);
    uiMeas->frameMeasGalileo_5->setHidden(true);
    uiMeas->frameMeasGalileo_6->setHidden(true);
    uiMeas->frameMeasGalileo_7->setHidden(true);
    uiMeas->frameMeasGalileo_8->setHidden(true);
    uiMeas->frameMeasGalileo_9->setHidden(true);
    uiMeas->frameMeasGalileo_10->setHidden(true);
    this->on_comboBoxFreqGalileo_1_currentIndexChanged(0);
    this->on_comboBoxFreqGalileo_2_currentIndexChanged(0);
    this->on_comboBoxFreqGalileo_3_currentIndexChanged(0);
    this->on_comboBoxFreqGalileo_4_currentIndexChanged(0);
    this->on_comboBoxFreqGalileo_5_currentIndexChanged(0);
    this->on_comboBoxFreqGalileo_6_currentIndexChanged(0);
    this->on_comboBoxFreqGalileo_7_currentIndexChanged(0);
    this->on_comboBoxFreqGalileo_8_currentIndexChanged(0);
    this->on_comboBoxFreqGalileo_9_currentIndexChanged(0);
    this->on_comboBoxFreqGalileo_10_currentIndexChanged(0);
}
// Function to change Galileo frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGalileo_1_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGalileo_1->setCurrentIndex(index);
    this->on_comboBoxTypeGalileo_1_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGalileo_1->setEnabled(false);
        uiMeas->comboBoxMeasGalileo_1->setEnabled(false);
        this->cleanPrintMeas(Galileo,0);
    } else {
        uiMeas->comboBoxTypeGalileo_1->setEnabled(true);
        uiMeas->comboBoxMeasGalileo_1->setEnabled(true);
    }
}
// Function to change Galileo frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGalileo_2_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGalileo_2->setCurrentIndex(index);
    this->on_comboBoxTypeGalileo_2_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGalileo_2->setEnabled(false);
        uiMeas->comboBoxMeasGalileo_2->setEnabled(false);
        this->cleanPrintMeas(Galileo,1);
    } else {
        uiMeas->comboBoxTypeGalileo_2->setEnabled(true);
        uiMeas->comboBoxMeasGalileo_2->setEnabled(true);
    }
}
// Function to change Galileo frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGalileo_3_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGalileo_3->setCurrentIndex(index);
    this->on_comboBoxTypeGalileo_3_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGalileo_3->setEnabled(false);
        uiMeas->comboBoxMeasGalileo_3->setEnabled(false);
        this->cleanPrintMeas(Galileo,2);
    } else {
        uiMeas->comboBoxTypeGalileo_3->setEnabled(true);
        uiMeas->comboBoxMeasGalileo_3->setEnabled(true);
    }
}
// Function to change Galileo frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGalileo_4_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGalileo_4->setCurrentIndex(index);
    this->on_comboBoxTypeGalileo_4_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGalileo_4->setEnabled(false);
        uiMeas->comboBoxMeasGalileo_4->setEnabled(false);
        this->cleanPrintMeas(Galileo,3);
    } else {
        uiMeas->comboBoxTypeGalileo_4->setEnabled(true);
        uiMeas->comboBoxMeasGalileo_4->setEnabled(true);
    }
}
// Function to change Galileo frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGalileo_5_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGalileo_5->setCurrentIndex(index);
    this->on_comboBoxTypeGalileo_5_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGalileo_5->setEnabled(false);
        uiMeas->comboBoxMeasGalileo_5->setEnabled(false);
        this->cleanPrintMeas(Galileo,4);
    } else {
        uiMeas->comboBoxTypeGalileo_5->setEnabled(true);
        uiMeas->comboBoxMeasGalileo_5->setEnabled(true);
    }
}
// Function to change Galileo frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGalileo_6_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGalileo_6->setCurrentIndex(index);
    this->on_comboBoxTypeGalileo_6_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGalileo_6->setEnabled(false);
        uiMeas->comboBoxMeasGalileo_6->setEnabled(false);
        this->cleanPrintMeas(Galileo,5);
    } else {
        uiMeas->comboBoxTypeGalileo_6->setEnabled(true);
        uiMeas->comboBoxMeasGalileo_6->setEnabled(true);
    }
}
// Function to change Galileo frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGalileo_7_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGalileo_7->setCurrentIndex(index);
    this->on_comboBoxTypeGalileo_7_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGalileo_7->setEnabled(false);
        uiMeas->comboBoxMeasGalileo_7->setEnabled(false);
        this->cleanPrintMeas(Galileo,6);
    } else {
        uiMeas->comboBoxTypeGalileo_7->setEnabled(true);
        uiMeas->comboBoxMeasGalileo_7->setEnabled(true);
    }
}
// Function to change Galileo frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGalileo_8_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGalileo_8->setCurrentIndex(index);
    this->on_comboBoxTypeGalileo_8_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGalileo_8->setEnabled(false);
        uiMeas->comboBoxMeasGalileo_8->setEnabled(false);
        this->cleanPrintMeas(Galileo,7);
    } else {
        uiMeas->comboBoxTypeGalileo_8->setEnabled(true);
        uiMeas->comboBoxMeasGalileo_8->setEnabled(true);
    }
}
// Function to change Galileo frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGalileo_9_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGalileo_9->setCurrentIndex(index);
    this->on_comboBoxTypeGalileo_9_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGalileo_9->setEnabled(false);
        uiMeas->comboBoxMeasGalileo_9->setEnabled(false);
        this->cleanPrintMeas(Galileo,8);
    } else {
        uiMeas->comboBoxTypeGalileo_9->setEnabled(true);
        uiMeas->comboBoxMeasGalileo_9->setEnabled(true);
    }
}
// Function to change Galileo frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGalileo_10_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGalileo_10->setCurrentIndex(index);
    this->on_comboBoxTypeGalileo_10_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGalileo_10->setEnabled(false);
        uiMeas->comboBoxMeasGalileo_10->setEnabled(false);
        this->cleanPrintMeas(Galileo,9);
    } else {
        uiMeas->comboBoxTypeGalileo_10->setEnabled(true);
        uiMeas->comboBoxMeasGalileo_10->setEnabled(true);
    }
}
// Function to change Galileo type comboBox
void GNSS_Meas_Select::on_comboBoxTypeGalileo_1_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGalileo_1->setCurrentIndex(index);
    this->changePrintMeas(Galileo,uiMeas->comboBoxFreqGalileo_1->currentIndex()-1,index,0);
}
void GNSS_Meas_Select::on_comboBoxTypeGalileo_2_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGalileo_2->setCurrentIndex(index);
    this->changePrintMeas(Galileo,uiMeas->comboBoxFreqGalileo_2->currentIndex()-1,index,1);
}
void GNSS_Meas_Select::on_comboBoxTypeGalileo_3_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGalileo_3->setCurrentIndex(index);
    this->changePrintMeas(Galileo,uiMeas->comboBoxFreqGalileo_3->currentIndex()-1,index,2);
}
void GNSS_Meas_Select::on_comboBoxTypeGalileo_4_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGalileo_4->setCurrentIndex(index);
    this->changePrintMeas(Galileo,uiMeas->comboBoxFreqGalileo_4->currentIndex()-1,index,3);
}
void GNSS_Meas_Select::on_comboBoxTypeGalileo_5_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGalileo_5->setCurrentIndex(index);
    this->changePrintMeas(Galileo,uiMeas->comboBoxFreqGalileo_5->currentIndex()-1,index,4);
}
void GNSS_Meas_Select::on_comboBoxTypeGalileo_6_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGalileo_6->setCurrentIndex(index);
    this->changePrintMeas(Galileo,uiMeas->comboBoxFreqGalileo_6->currentIndex()-1,index,5);
}
void GNSS_Meas_Select::on_comboBoxTypeGalileo_7_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGalileo_7->setCurrentIndex(index);
    this->changePrintMeas(Galileo,uiMeas->comboBoxFreqGalileo_7->currentIndex()-1,index,6);
}
void GNSS_Meas_Select::on_comboBoxTypeGalileo_8_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGalileo_8->setCurrentIndex(index);
    this->changePrintMeas(Galileo,uiMeas->comboBoxFreqGalileo_8->currentIndex()-1,index,7);
}
void GNSS_Meas_Select::on_comboBoxTypeGalileo_9_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGalileo_9->setCurrentIndex(index);
    this->changePrintMeas(Galileo,uiMeas->comboBoxFreqGalileo_9->currentIndex()-1,index,8);
}
void GNSS_Meas_Select::on_comboBoxTypeGalileo_10_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGalileo_10->setCurrentIndex(index);
    this->changePrintMeas(Galileo,uiMeas->comboBoxFreqGalileo_10->currentIndex()-1,index,9);
}

//GLONASS
// Function to set GLONASS default
void GNSS_Meas_Select::SetDefaultMeasGLONASS(){
    nPrint[GLONASS]=1;
    FrameGNSSLabel[GLONASS][1]->setHidden(true);
    uiMeas->frameMeasGLONASS_1->setHidden(false);
    uiMeas->frameMeasGLONASS_2->setHidden(true);
    uiMeas->frameMeasGLONASS_3->setHidden(true);
    uiMeas->frameMeasGLONASS_4->setHidden(true);
    uiMeas->frameMeasGLONASS_5->setHidden(true);
    uiMeas->frameMeasGLONASS_6->setHidden(true);
    uiMeas->frameMeasGLONASS_7->setHidden(true);
    uiMeas->frameMeasGLONASS_8->setHidden(true);
    uiMeas->frameMeasGLONASS_9->setHidden(true);
    uiMeas->frameMeasGLONASS_10->setHidden(true);
    this->on_comboBoxFreqGLONASS_1_currentIndexChanged(0);
    this->on_comboBoxFreqGLONASS_2_currentIndexChanged(0);
    this->on_comboBoxFreqGLONASS_3_currentIndexChanged(0);
    this->on_comboBoxFreqGLONASS_4_currentIndexChanged(0);
    this->on_comboBoxFreqGLONASS_5_currentIndexChanged(0);
    this->on_comboBoxFreqGLONASS_6_currentIndexChanged(0);
    this->on_comboBoxFreqGLONASS_7_currentIndexChanged(0);
    this->on_comboBoxFreqGLONASS_8_currentIndexChanged(0);
    this->on_comboBoxFreqGLONASS_9_currentIndexChanged(0);
    this->on_comboBoxFreqGLONASS_10_currentIndexChanged(0);
}
// Function to change GLONASS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGLONASS_1_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGLONASS_1->setCurrentIndex(index);
    this->on_comboBoxTypeGLONASS_1_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGLONASS_1->setEnabled(false);
        uiMeas->comboBoxMeasGLONASS_1->setEnabled(false);
        this->cleanPrintMeas(GLONASS,0);
    } else {
        uiMeas->comboBoxTypeGLONASS_1->setEnabled(true);
        uiMeas->comboBoxMeasGLONASS_1->setEnabled(true);
    }
}
// Function to change GLONASS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGLONASS_2_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGLONASS_2->setCurrentIndex(index);
    this->on_comboBoxTypeGLONASS_2_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGLONASS_2->setEnabled(false);
        uiMeas->comboBoxMeasGLONASS_2->setEnabled(false);
        this->cleanPrintMeas(GLONASS,1);
    } else {
        uiMeas->comboBoxTypeGLONASS_2->setEnabled(true);
        uiMeas->comboBoxMeasGLONASS_2->setEnabled(true);
    }
}
// Function to change GLONASS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGLONASS_3_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGLONASS_3->setCurrentIndex(index);
    this->on_comboBoxTypeGLONASS_3_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGLONASS_3->setEnabled(false);
        uiMeas->comboBoxMeasGLONASS_3->setEnabled(false);
        this->cleanPrintMeas(GLONASS,2);
    } else {
        uiMeas->comboBoxTypeGLONASS_3->setEnabled(true);
        uiMeas->comboBoxMeasGLONASS_3->setEnabled(true);
    }
}
// Function to change GLONASS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGLONASS_4_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGLONASS_4->setCurrentIndex(index);
    this->on_comboBoxTypeGLONASS_4_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGLONASS_4->setEnabled(false);
        uiMeas->comboBoxMeasGLONASS_4->setEnabled(false);
        this->cleanPrintMeas(GLONASS,3);
    } else {
        uiMeas->comboBoxTypeGLONASS_4->setEnabled(true);
        uiMeas->comboBoxMeasGLONASS_4->setEnabled(true);
    }
}
// Function to change GLONASS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGLONASS_5_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGLONASS_5->setCurrentIndex(index);
    this->on_comboBoxTypeGLONASS_5_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGLONASS_5->setEnabled(false);
        uiMeas->comboBoxMeasGLONASS_5->setEnabled(false);
        this->cleanPrintMeas(GLONASS,4);
    } else {
        uiMeas->comboBoxTypeGLONASS_5->setEnabled(true);
        uiMeas->comboBoxMeasGLONASS_5->setEnabled(true);
    }
}
// Function to change GLONASS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGLONASS_6_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGLONASS_6->setCurrentIndex(index);
    this->on_comboBoxTypeGLONASS_6_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGLONASS_6->setEnabled(false);
        uiMeas->comboBoxMeasGLONASS_6->setEnabled(false);
        this->cleanPrintMeas(GLONASS,5);
    } else {
        uiMeas->comboBoxTypeGLONASS_6->setEnabled(true);
        uiMeas->comboBoxMeasGLONASS_6->setEnabled(true);
    }
}
// Function to change GLONASS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGLONASS_7_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGLONASS_7->setCurrentIndex(index);
    this->on_comboBoxTypeGLONASS_7_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGLONASS_7->setEnabled(false);
        uiMeas->comboBoxMeasGLONASS_7->setEnabled(false);
        this->cleanPrintMeas(GLONASS,6);
    } else {
        uiMeas->comboBoxTypeGLONASS_7->setEnabled(true);
        uiMeas->comboBoxMeasGLONASS_7->setEnabled(true);
    }
}
// Function to change GLONASS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGLONASS_8_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGLONASS_8->setCurrentIndex(index);
    this->on_comboBoxTypeGLONASS_8_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGLONASS_8->setEnabled(false);
        uiMeas->comboBoxMeasGLONASS_8->setEnabled(false);
        this->cleanPrintMeas(GLONASS,7);
    } else {
        uiMeas->comboBoxTypeGLONASS_8->setEnabled(true);
        uiMeas->comboBoxMeasGLONASS_8->setEnabled(true);
    }
}
// Function to change GLONASS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGLONASS_9_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGLONASS_9->setCurrentIndex(index);
    this->on_comboBoxTypeGLONASS_9_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGLONASS_9->setEnabled(false);
        uiMeas->comboBoxMeasGLONASS_9->setEnabled(false);
        this->cleanPrintMeas(GLONASS,8);
    } else {
        uiMeas->comboBoxTypeGLONASS_9->setEnabled(true);
        uiMeas->comboBoxMeasGLONASS_9->setEnabled(true);
    }
}
// Function to change GLONASS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGLONASS_10_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGLONASS_10->setCurrentIndex(index);
    this->on_comboBoxTypeGLONASS_10_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGLONASS_10->setEnabled(false);
        uiMeas->comboBoxMeasGLONASS_10->setEnabled(false);
        this->cleanPrintMeas(GLONASS,9);
    } else {
        uiMeas->comboBoxTypeGLONASS_10->setEnabled(true);
        uiMeas->comboBoxMeasGLONASS_10->setEnabled(true);
    }
}
// Function to change GLONASS type comboBox
void GNSS_Meas_Select::on_comboBoxTypeGLONASS_1_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGLONASS_1->setCurrentIndex(index);
    this->changePrintMeas(GLONASS,uiMeas->comboBoxFreqGLONASS_1->currentIndex()-1,index,0);
}
void GNSS_Meas_Select::on_comboBoxTypeGLONASS_2_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGLONASS_2->setCurrentIndex(index);
    this->changePrintMeas(GLONASS,uiMeas->comboBoxFreqGLONASS_2->currentIndex()-1,index,1);
}
void GNSS_Meas_Select::on_comboBoxTypeGLONASS_3_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGLONASS_3->setCurrentIndex(index);
    this->changePrintMeas(GLONASS,uiMeas->comboBoxFreqGLONASS_3->currentIndex()-1,index,2);
}
void GNSS_Meas_Select::on_comboBoxTypeGLONASS_4_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGLONASS_4->setCurrentIndex(index);
    this->changePrintMeas(GLONASS,uiMeas->comboBoxFreqGLONASS_4->currentIndex()-1,index,3);
}
void GNSS_Meas_Select::on_comboBoxTypeGLONASS_5_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGLONASS_5->setCurrentIndex(index);
    this->changePrintMeas(GLONASS,uiMeas->comboBoxFreqGLONASS_5->currentIndex()-1,index,4);
}
void GNSS_Meas_Select::on_comboBoxTypeGLONASS_6_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGLONASS_6->setCurrentIndex(index);
    this->changePrintMeas(GLONASS,uiMeas->comboBoxFreqGLONASS_6->currentIndex()-1,index,5);
}
void GNSS_Meas_Select::on_comboBoxTypeGLONASS_7_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGLONASS_7->setCurrentIndex(index);
    this->changePrintMeas(GLONASS,uiMeas->comboBoxFreqGLONASS_7->currentIndex()-1,index,6);
}
void GNSS_Meas_Select::on_comboBoxTypeGLONASS_8_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGLONASS_8->setCurrentIndex(index);
    this->changePrintMeas(GLONASS,uiMeas->comboBoxFreqGLONASS_8->currentIndex()-1,index,7);
}
void GNSS_Meas_Select::on_comboBoxTypeGLONASS_9_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGLONASS_9->setCurrentIndex(index);
    this->changePrintMeas(GLONASS,uiMeas->comboBoxFreqGLONASS_9->currentIndex()-1,index,8);
}
void GNSS_Meas_Select::on_comboBoxTypeGLONASS_10_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGLONASS_10->setCurrentIndex(index);
    this->changePrintMeas(GLONASS,uiMeas->comboBoxFreqGLONASS_10->currentIndex()-1,index,9);
}

//GEO
// Function to set GEO default
void GNSS_Meas_Select::SetDefaultMeasGEO(){
    nPrint[GEO]=1;
    FrameGNSSLabel[GEO][1]->setHidden(true);
    uiMeas->frameMeasGEO_1->setHidden(false);
    uiMeas->frameMeasGEO_2->setHidden(true);
    uiMeas->frameMeasGEO_3->setHidden(true);
    uiMeas->frameMeasGEO_4->setHidden(true);
    uiMeas->frameMeasGEO_5->setHidden(true);
    uiMeas->frameMeasGEO_6->setHidden(true);
    uiMeas->frameMeasGEO_7->setHidden(true);
    uiMeas->frameMeasGEO_8->setHidden(true);
    uiMeas->frameMeasGEO_9->setHidden(true);
    uiMeas->frameMeasGEO_10->setHidden(true);
    this->on_comboBoxFreqGEO_1_currentIndexChanged(0);
    this->on_comboBoxFreqGEO_2_currentIndexChanged(0);
    this->on_comboBoxFreqGEO_3_currentIndexChanged(0);
    this->on_comboBoxFreqGEO_4_currentIndexChanged(0);
    this->on_comboBoxFreqGEO_5_currentIndexChanged(0);
    this->on_comboBoxFreqGEO_6_currentIndexChanged(0);
    this->on_comboBoxFreqGEO_7_currentIndexChanged(0);
    this->on_comboBoxFreqGEO_8_currentIndexChanged(0);
    this->on_comboBoxFreqGEO_9_currentIndexChanged(0);
    this->on_comboBoxFreqGEO_10_currentIndexChanged(0);
}
// Function to change GEO frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGEO_1_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGEO_1->setCurrentIndex(index);
    this->on_comboBoxTypeGEO_1_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGEO_1->setEnabled(false);
        uiMeas->comboBoxMeasGEO_1->setEnabled(false);
        this->cleanPrintMeas(GEO,0);
    } else {
        uiMeas->comboBoxTypeGEO_1->setEnabled(true);
        uiMeas->comboBoxMeasGEO_1->setEnabled(true);
    }
}
// Function to change GEO frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGEO_2_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGEO_2->setCurrentIndex(index);
    this->on_comboBoxTypeGEO_2_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGEO_2->setEnabled(false);
        uiMeas->comboBoxMeasGEO_2->setEnabled(false);
        this->cleanPrintMeas(GEO,1);
    } else {
        uiMeas->comboBoxTypeGEO_2->setEnabled(true);
        uiMeas->comboBoxMeasGEO_2->setEnabled(true);
    }
}
// Function to change GEO frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGEO_3_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGEO_3->setCurrentIndex(index);
    this->on_comboBoxTypeGEO_3_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGEO_3->setEnabled(false);
        uiMeas->comboBoxMeasGEO_3->setEnabled(false);
        this->cleanPrintMeas(GEO,2);
    } else {
        uiMeas->comboBoxTypeGEO_3->setEnabled(true);
        uiMeas->comboBoxMeasGEO_3->setEnabled(true);
    }
}
// Function to change GEO frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGEO_4_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGEO_4->setCurrentIndex(index);
    this->on_comboBoxTypeGEO_4_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGEO_4->setEnabled(false);
        uiMeas->comboBoxMeasGEO_4->setEnabled(false);
        this->cleanPrintMeas(GEO,3);
    } else {
        uiMeas->comboBoxTypeGEO_4->setEnabled(true);
        uiMeas->comboBoxMeasGEO_4->setEnabled(true);
    }
}
// Function to change GEO frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGEO_5_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGEO_5->setCurrentIndex(index);
    this->on_comboBoxTypeGEO_5_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGEO_5->setEnabled(false);
        uiMeas->comboBoxMeasGEO_5->setEnabled(false);
        this->cleanPrintMeas(GEO,4);
    } else {
        uiMeas->comboBoxTypeGEO_5->setEnabled(true);
        uiMeas->comboBoxMeasGEO_5->setEnabled(true);
    }
}
// Function to change GEO frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGEO_6_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGEO_6->setCurrentIndex(index);
    this->on_comboBoxTypeGEO_6_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGEO_6->setEnabled(false);
        uiMeas->comboBoxMeasGEO_6->setEnabled(false);
        this->cleanPrintMeas(GEO,5);
    } else {
        uiMeas->comboBoxTypeGEO_6->setEnabled(true);
        uiMeas->comboBoxMeasGEO_6->setEnabled(true);
    }
}
// Function to change GEO frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGEO_7_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGEO_7->setCurrentIndex(index);
    this->on_comboBoxTypeGEO_7_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGEO_7->setEnabled(false);
        uiMeas->comboBoxMeasGEO_7->setEnabled(false);
        this->cleanPrintMeas(GEO,6);
    } else {
        uiMeas->comboBoxTypeGEO_7->setEnabled(true);
        uiMeas->comboBoxMeasGEO_7->setEnabled(true);
    }
}
// Function to change GEO frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGEO_8_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGEO_8->setCurrentIndex(index);
    this->on_comboBoxTypeGEO_8_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGEO_8->setEnabled(false);
        uiMeas->comboBoxMeasGEO_8->setEnabled(false);
        this->cleanPrintMeas(GEO,7);
    } else {
        uiMeas->comboBoxTypeGEO_8->setEnabled(true);
        uiMeas->comboBoxMeasGEO_8->setEnabled(true);
    }
}
// Function to change GEO frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGEO_9_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGEO_9->setCurrentIndex(index);
    this->on_comboBoxTypeGEO_9_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGEO_9->setEnabled(false);
        uiMeas->comboBoxMeasGEO_9->setEnabled(false);
        this->cleanPrintMeas(GEO,8);
    } else {
        uiMeas->comboBoxTypeGEO_9->setEnabled(true);
        uiMeas->comboBoxMeasGEO_9->setEnabled(true);
    }
}
// Function to change GEO frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqGEO_10_currentIndexChanged(int index){
    uiMeas->comboBoxFreqGEO_10->setCurrentIndex(index);
    this->on_comboBoxTypeGEO_10_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeGEO_10->setEnabled(false);
        uiMeas->comboBoxMeasGEO_10->setEnabled(false);
        this->cleanPrintMeas(GEO,9);
    } else {
        uiMeas->comboBoxTypeGEO_10->setEnabled(true);
        uiMeas->comboBoxMeasGEO_10->setEnabled(true);
    }
}
// Function to change GEO type comboBox
void GNSS_Meas_Select::on_comboBoxTypeGEO_1_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGEO_1->setCurrentIndex(index);
    this->changePrintMeas(GEO,uiMeas->comboBoxFreqGEO_1->currentIndex()-1,index,0);
}
void GNSS_Meas_Select::on_comboBoxTypeGEO_2_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGEO_2->setCurrentIndex(index);
    this->changePrintMeas(GEO,uiMeas->comboBoxFreqGEO_2->currentIndex()-1,index,1);
}
void GNSS_Meas_Select::on_comboBoxTypeGEO_3_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGEO_3->setCurrentIndex(index);
    this->changePrintMeas(GEO,uiMeas->comboBoxFreqGEO_3->currentIndex()-1,index,2);
}
void GNSS_Meas_Select::on_comboBoxTypeGEO_4_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGEO_4->setCurrentIndex(index);
    this->changePrintMeas(GEO,uiMeas->comboBoxFreqGEO_4->currentIndex()-1,index,3);
}
void GNSS_Meas_Select::on_comboBoxTypeGEO_5_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGEO_5->setCurrentIndex(index);
    this->changePrintMeas(GEO,uiMeas->comboBoxFreqGEO_5->currentIndex()-1,index,4);
}
void GNSS_Meas_Select::on_comboBoxTypeGEO_6_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGEO_6->setCurrentIndex(index);
    this->changePrintMeas(GEO,uiMeas->comboBoxFreqGEO_6->currentIndex()-1,index,5);
}
void GNSS_Meas_Select::on_comboBoxTypeGEO_7_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGEO_7->setCurrentIndex(index);
    this->changePrintMeas(GEO,uiMeas->comboBoxFreqGEO_7->currentIndex()-1,index,6);
}
void GNSS_Meas_Select::on_comboBoxTypeGEO_8_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGEO_8->setCurrentIndex(index);
    this->changePrintMeas(GEO,uiMeas->comboBoxFreqGEO_8->currentIndex()-1,index,7);
}
void GNSS_Meas_Select::on_comboBoxTypeGEO_9_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGEO_9->setCurrentIndex(index);
    this->changePrintMeas(GEO,uiMeas->comboBoxFreqGEO_9->currentIndex()-1,index,8);
}
void GNSS_Meas_Select::on_comboBoxTypeGEO_10_currentIndexChanged(int index){
    uiMeas->comboBoxTypeGEO_10->setCurrentIndex(index);
    this->changePrintMeas(GEO,uiMeas->comboBoxFreqGEO_10->currentIndex()-1,index,9);
}

//BDS
// Function to set BDS default
void GNSS_Meas_Select::SetDefaultMeasBDS(){
    nPrint[BDS]=1;
    FrameGNSSLabel[BDS][1]->setHidden(true);
    uiMeas->frameMeasBDS_1->setHidden(false);
    uiMeas->frameMeasBDS_2->setHidden(true);
    uiMeas->frameMeasBDS_3->setHidden(true);
    uiMeas->frameMeasBDS_4->setHidden(true);
    uiMeas->frameMeasBDS_5->setHidden(true);
    uiMeas->frameMeasBDS_6->setHidden(true);
    uiMeas->frameMeasBDS_7->setHidden(true);
    uiMeas->frameMeasBDS_8->setHidden(true);
    uiMeas->frameMeasBDS_9->setHidden(true);
    uiMeas->frameMeasBDS_10->setHidden(true);
    this->on_comboBoxFreqBDS_1_currentIndexChanged(0);
    this->on_comboBoxFreqBDS_2_currentIndexChanged(0);
    this->on_comboBoxFreqBDS_3_currentIndexChanged(0);
    this->on_comboBoxFreqBDS_4_currentIndexChanged(0);
    this->on_comboBoxFreqBDS_5_currentIndexChanged(0);
    this->on_comboBoxFreqBDS_6_currentIndexChanged(0);
    this->on_comboBoxFreqBDS_7_currentIndexChanged(0);
    this->on_comboBoxFreqBDS_8_currentIndexChanged(0);
    this->on_comboBoxFreqBDS_9_currentIndexChanged(0);
    this->on_comboBoxFreqBDS_10_currentIndexChanged(0);
}
// Function to change BDS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqBDS_1_currentIndexChanged(int index){
    uiMeas->comboBoxFreqBDS_1->setCurrentIndex(index);
    this->on_comboBoxTypeBDS_1_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeBDS_1->setEnabled(false);
        uiMeas->comboBoxMeasBDS_1->setEnabled(false);
        this->cleanPrintMeas(BDS,0);
    } else {
        uiMeas->comboBoxTypeBDS_1->setEnabled(true);
        uiMeas->comboBoxMeasBDS_1->setEnabled(true);
    }
}
// Function to change BDS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqBDS_2_currentIndexChanged(int index){
    uiMeas->comboBoxFreqBDS_2->setCurrentIndex(index);
    this->on_comboBoxTypeBDS_2_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeBDS_2->setEnabled(false);
        uiMeas->comboBoxMeasBDS_2->setEnabled(false);
        this->cleanPrintMeas(BDS,1);
    } else {
        uiMeas->comboBoxTypeBDS_2->setEnabled(true);
        uiMeas->comboBoxMeasBDS_2->setEnabled(true);
    }
}
// Function to change BDS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqBDS_3_currentIndexChanged(int index){
    uiMeas->comboBoxFreqBDS_3->setCurrentIndex(index);
    this->on_comboBoxTypeBDS_3_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeBDS_3->setEnabled(false);
        uiMeas->comboBoxMeasBDS_3->setEnabled(false);
        this->cleanPrintMeas(BDS,2);
    } else {
        uiMeas->comboBoxTypeBDS_3->setEnabled(true);
        uiMeas->comboBoxMeasBDS_3->setEnabled(true);
    }
}
// Function to change BDS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqBDS_4_currentIndexChanged(int index){
    uiMeas->comboBoxFreqBDS_4->setCurrentIndex(index);
    this->on_comboBoxTypeBDS_4_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeBDS_4->setEnabled(false);
        uiMeas->comboBoxMeasBDS_4->setEnabled(false);
        this->cleanPrintMeas(BDS,3);
    } else {
        uiMeas->comboBoxTypeBDS_4->setEnabled(true);
        uiMeas->comboBoxMeasBDS_4->setEnabled(true);
    }
}
// Function to change BDS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqBDS_5_currentIndexChanged(int index){
    uiMeas->comboBoxFreqBDS_5->setCurrentIndex(index);
    this->on_comboBoxTypeBDS_5_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeBDS_5->setEnabled(false);
        uiMeas->comboBoxMeasBDS_5->setEnabled(false);
        this->cleanPrintMeas(BDS,4);
    } else {
        uiMeas->comboBoxTypeBDS_5->setEnabled(true);
        uiMeas->comboBoxMeasBDS_5->setEnabled(true);
    }
}
// Function to change BDS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqBDS_6_currentIndexChanged(int index){
    uiMeas->comboBoxFreqBDS_6->setCurrentIndex(index);
    this->on_comboBoxTypeBDS_6_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeBDS_6->setEnabled(false);
        uiMeas->comboBoxMeasBDS_6->setEnabled(false);
        this->cleanPrintMeas(BDS,5);
    } else {
        uiMeas->comboBoxTypeBDS_6->setEnabled(true);
        uiMeas->comboBoxMeasBDS_6->setEnabled(true);
    }
}
// Function to change BDS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqBDS_7_currentIndexChanged(int index){
    uiMeas->comboBoxFreqBDS_7->setCurrentIndex(index);
    this->on_comboBoxTypeBDS_7_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeBDS_7->setEnabled(false);
        uiMeas->comboBoxMeasBDS_7->setEnabled(false);
        this->cleanPrintMeas(BDS,6);
    } else {
        uiMeas->comboBoxTypeBDS_7->setEnabled(true);
        uiMeas->comboBoxMeasBDS_7->setEnabled(true);
    }
}
// Function to change BDS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqBDS_8_currentIndexChanged(int index){
    uiMeas->comboBoxFreqBDS_8->setCurrentIndex(index);
    this->on_comboBoxTypeBDS_8_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeBDS_8->setEnabled(false);
        uiMeas->comboBoxMeasBDS_8->setEnabled(false);
        this->cleanPrintMeas(BDS,7);
    } else {
        uiMeas->comboBoxTypeBDS_8->setEnabled(true);
        uiMeas->comboBoxMeasBDS_8->setEnabled(true);
    }
}
// Function to change BDS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqBDS_9_currentIndexChanged(int index){
    uiMeas->comboBoxFreqBDS_9->setCurrentIndex(index);
    this->on_comboBoxTypeBDS_9_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeBDS_9->setEnabled(false);
        uiMeas->comboBoxMeasBDS_9->setEnabled(false);
        this->cleanPrintMeas(BDS,8);
    } else {
        uiMeas->comboBoxTypeBDS_9->setEnabled(true);
        uiMeas->comboBoxMeasBDS_9->setEnabled(true);
    }
}
// Function to change BDS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqBDS_10_currentIndexChanged(int index){
    uiMeas->comboBoxFreqBDS_10->setCurrentIndex(index);
    this->on_comboBoxTypeBDS_10_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeBDS_10->setEnabled(false);
        uiMeas->comboBoxMeasBDS_10->setEnabled(false);
        this->cleanPrintMeas(BDS,9);
    } else {
        uiMeas->comboBoxTypeBDS_10->setEnabled(true);
        uiMeas->comboBoxMeasBDS_10->setEnabled(true);
    }
}
// Function to change BDS type comboBox
void GNSS_Meas_Select::on_comboBoxTypeBDS_1_currentIndexChanged(int index){
    uiMeas->comboBoxTypeBDS_1->setCurrentIndex(index);
    this->changePrintMeas(BDS,uiMeas->comboBoxFreqBDS_1->currentIndex()-1,index,0);
}
void GNSS_Meas_Select::on_comboBoxTypeBDS_2_currentIndexChanged(int index){
    uiMeas->comboBoxTypeBDS_2->setCurrentIndex(index);
    this->changePrintMeas(BDS,uiMeas->comboBoxFreqBDS_2->currentIndex()-1,index,1);
}
void GNSS_Meas_Select::on_comboBoxTypeBDS_3_currentIndexChanged(int index){
    uiMeas->comboBoxTypeBDS_3->setCurrentIndex(index);
    this->changePrintMeas(BDS,uiMeas->comboBoxFreqBDS_3->currentIndex()-1,index,2);
}
void GNSS_Meas_Select::on_comboBoxTypeBDS_4_currentIndexChanged(int index){
    uiMeas->comboBoxTypeBDS_4->setCurrentIndex(index);
    this->changePrintMeas(BDS,uiMeas->comboBoxFreqBDS_4->currentIndex()-1,index,3);
}
void GNSS_Meas_Select::on_comboBoxTypeBDS_5_currentIndexChanged(int index){
    uiMeas->comboBoxTypeBDS_5->setCurrentIndex(index);
    this->changePrintMeas(BDS,uiMeas->comboBoxFreqBDS_5->currentIndex()-1,index,4);
}
void GNSS_Meas_Select::on_comboBoxTypeBDS_6_currentIndexChanged(int index){
    uiMeas->comboBoxTypeBDS_6->setCurrentIndex(index);
    this->changePrintMeas(BDS,uiMeas->comboBoxFreqBDS_6->currentIndex()-1,index,5);
}
void GNSS_Meas_Select::on_comboBoxTypeBDS_7_currentIndexChanged(int index){
    uiMeas->comboBoxTypeBDS_7->setCurrentIndex(index);
    this->changePrintMeas(BDS,uiMeas->comboBoxFreqBDS_7->currentIndex()-1,index,6);
}
void GNSS_Meas_Select::on_comboBoxTypeBDS_8_currentIndexChanged(int index){
    uiMeas->comboBoxTypeBDS_8->setCurrentIndex(index);
    this->changePrintMeas(BDS,uiMeas->comboBoxFreqBDS_8->currentIndex()-1,index,7);
}
void GNSS_Meas_Select::on_comboBoxTypeBDS_9_currentIndexChanged(int index){
    uiMeas->comboBoxTypeBDS_9->setCurrentIndex(index);
    this->changePrintMeas(BDS,uiMeas->comboBoxFreqBDS_9->currentIndex()-1,index,8);
}
void GNSS_Meas_Select::on_comboBoxTypeBDS_10_currentIndexChanged(int index){
    uiMeas->comboBoxTypeBDS_10->setCurrentIndex(index);
    this->changePrintMeas(BDS,uiMeas->comboBoxFreqBDS_10->currentIndex()-1,index,9);
}

//QZSS
// Function to set QZSS default
void GNSS_Meas_Select::SetDefaultMeasQZSS(){
    nPrint[QZSS]=1;
    FrameGNSSLabel[QZSS][1]->setHidden(true);
    uiMeas->frameMeasQZSS_1->setHidden(false);
    uiMeas->frameMeasQZSS_2->setHidden(true);
    uiMeas->frameMeasQZSS_3->setHidden(true);
    uiMeas->frameMeasQZSS_4->setHidden(true);
    uiMeas->frameMeasQZSS_5->setHidden(true);
    uiMeas->frameMeasQZSS_6->setHidden(true);
    uiMeas->frameMeasQZSS_7->setHidden(true);
    uiMeas->frameMeasQZSS_8->setHidden(true);
    uiMeas->frameMeasQZSS_9->setHidden(true);
    uiMeas->frameMeasQZSS_10->setHidden(true);
    this->on_comboBoxFreqQZSS_1_currentIndexChanged(0);
    this->on_comboBoxFreqQZSS_2_currentIndexChanged(0);
    this->on_comboBoxFreqQZSS_3_currentIndexChanged(0);
    this->on_comboBoxFreqQZSS_4_currentIndexChanged(0);
    this->on_comboBoxFreqQZSS_5_currentIndexChanged(0);
    this->on_comboBoxFreqQZSS_6_currentIndexChanged(0);
    this->on_comboBoxFreqQZSS_7_currentIndexChanged(0);
    this->on_comboBoxFreqQZSS_8_currentIndexChanged(0);
    this->on_comboBoxFreqQZSS_9_currentIndexChanged(0);
    this->on_comboBoxFreqQZSS_10_currentIndexChanged(0);
}
// Function to change QZSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqQZSS_1_currentIndexChanged(int index){
    uiMeas->comboBoxFreqQZSS_1->setCurrentIndex(index);
    this->on_comboBoxTypeQZSS_1_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeQZSS_1->setEnabled(false);
        uiMeas->comboBoxMeasQZSS_1->setEnabled(false);
        this->cleanPrintMeas(QZSS,0);
    } else {
        uiMeas->comboBoxTypeQZSS_1->setEnabled(true);
        uiMeas->comboBoxMeasQZSS_1->setEnabled(true);
    }
}
// Function to change QZSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqQZSS_2_currentIndexChanged(int index){
    uiMeas->comboBoxFreqQZSS_2->setCurrentIndex(index);
    this->on_comboBoxTypeQZSS_2_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeQZSS_2->setEnabled(false);
        uiMeas->comboBoxMeasQZSS_2->setEnabled(false);
        this->cleanPrintMeas(QZSS,1);
    } else {
        uiMeas->comboBoxTypeQZSS_2->setEnabled(true);
        uiMeas->comboBoxMeasQZSS_2->setEnabled(true);
    }
}
// Function to change QZSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqQZSS_3_currentIndexChanged(int index){
    uiMeas->comboBoxFreqQZSS_3->setCurrentIndex(index);
    this->on_comboBoxTypeQZSS_3_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeQZSS_3->setEnabled(false);
        uiMeas->comboBoxMeasQZSS_3->setEnabled(false);
        this->cleanPrintMeas(QZSS,2);
    } else {
        uiMeas->comboBoxTypeQZSS_3->setEnabled(true);
        uiMeas->comboBoxMeasQZSS_3->setEnabled(true);
    }
}
// Function to change QZSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqQZSS_4_currentIndexChanged(int index){
    uiMeas->comboBoxFreqQZSS_4->setCurrentIndex(index);
    this->on_comboBoxTypeQZSS_4_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeQZSS_4->setEnabled(false);
        uiMeas->comboBoxMeasQZSS_4->setEnabled(false);
        this->cleanPrintMeas(QZSS,3);
    } else {
        uiMeas->comboBoxTypeQZSS_4->setEnabled(true);
        uiMeas->comboBoxMeasQZSS_4->setEnabled(true);
    }
}
// Function to change QZSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqQZSS_5_currentIndexChanged(int index){
    uiMeas->comboBoxFreqQZSS_5->setCurrentIndex(index);
    this->on_comboBoxTypeQZSS_5_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeQZSS_5->setEnabled(false);
        uiMeas->comboBoxMeasQZSS_5->setEnabled(false);
        this->cleanPrintMeas(QZSS,4);
    } else {
        uiMeas->comboBoxTypeQZSS_5->setEnabled(true);
        uiMeas->comboBoxMeasQZSS_5->setEnabled(true);
    }
}
// Function to change QZSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqQZSS_6_currentIndexChanged(int index){
    uiMeas->comboBoxFreqQZSS_6->setCurrentIndex(index);
    this->on_comboBoxTypeQZSS_6_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeQZSS_6->setEnabled(false);
        uiMeas->comboBoxMeasQZSS_6->setEnabled(false);
        this->cleanPrintMeas(QZSS,5);
    } else {
        uiMeas->comboBoxTypeQZSS_6->setEnabled(true);
        uiMeas->comboBoxMeasQZSS_6->setEnabled(true);
    }
}
// Function to change QZSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqQZSS_7_currentIndexChanged(int index){
    uiMeas->comboBoxFreqQZSS_7->setCurrentIndex(index);
    this->on_comboBoxTypeQZSS_7_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeQZSS_7->setEnabled(false);
        uiMeas->comboBoxMeasQZSS_7->setEnabled(false);
        this->cleanPrintMeas(QZSS,6);
    } else {
        uiMeas->comboBoxTypeQZSS_7->setEnabled(true);
        uiMeas->comboBoxMeasQZSS_7->setEnabled(true);
    }
}
// Function to change QZSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqQZSS_8_currentIndexChanged(int index){
    uiMeas->comboBoxFreqQZSS_8->setCurrentIndex(index);
    this->on_comboBoxTypeQZSS_8_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeQZSS_8->setEnabled(false);
        uiMeas->comboBoxMeasQZSS_8->setEnabled(false);
        this->cleanPrintMeas(QZSS,7);
    } else {
        uiMeas->comboBoxTypeQZSS_8->setEnabled(true);
        uiMeas->comboBoxMeasQZSS_8->setEnabled(true);
    }
}
// Function to change QZSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqQZSS_9_currentIndexChanged(int index){
    uiMeas->comboBoxFreqQZSS_9->setCurrentIndex(index);
    this->on_comboBoxTypeQZSS_9_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeQZSS_9->setEnabled(false);
        uiMeas->comboBoxMeasQZSS_9->setEnabled(false);
        this->cleanPrintMeas(QZSS,8);
    } else {
        uiMeas->comboBoxTypeQZSS_9->setEnabled(true);
        uiMeas->comboBoxMeasQZSS_9->setEnabled(true);
    }
}
// Function to change QZSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqQZSS_10_currentIndexChanged(int index){
    uiMeas->comboBoxFreqQZSS_10->setCurrentIndex(index);
    this->on_comboBoxTypeQZSS_10_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeQZSS_10->setEnabled(false);
        uiMeas->comboBoxMeasQZSS_10->setEnabled(false);
        this->cleanPrintMeas(QZSS,9);
    } else {
        uiMeas->comboBoxTypeQZSS_10->setEnabled(true);
        uiMeas->comboBoxMeasQZSS_10->setEnabled(true);
    }
}
// Function to change QZSS type comboBox
void GNSS_Meas_Select::on_comboBoxTypeQZSS_1_currentIndexChanged(int index){
    uiMeas->comboBoxTypeQZSS_1->setCurrentIndex(index);
    this->changePrintMeas(QZSS,uiMeas->comboBoxFreqQZSS_1->currentIndex()-1,index,0);
}
void GNSS_Meas_Select::on_comboBoxTypeQZSS_2_currentIndexChanged(int index){
    uiMeas->comboBoxTypeQZSS_2->setCurrentIndex(index);
    this->changePrintMeas(QZSS,uiMeas->comboBoxFreqQZSS_2->currentIndex()-1,index,1);
}
void GNSS_Meas_Select::on_comboBoxTypeQZSS_3_currentIndexChanged(int index){
    uiMeas->comboBoxTypeQZSS_3->setCurrentIndex(index);
    this->changePrintMeas(QZSS,uiMeas->comboBoxFreqQZSS_3->currentIndex()-1,index,2);
}
void GNSS_Meas_Select::on_comboBoxTypeQZSS_4_currentIndexChanged(int index){
    uiMeas->comboBoxTypeQZSS_4->setCurrentIndex(index);
    this->changePrintMeas(QZSS,uiMeas->comboBoxFreqQZSS_4->currentIndex()-1,index,3);
}
void GNSS_Meas_Select::on_comboBoxTypeQZSS_5_currentIndexChanged(int index){
    uiMeas->comboBoxTypeQZSS_5->setCurrentIndex(index);
    this->changePrintMeas(QZSS,uiMeas->comboBoxFreqQZSS_5->currentIndex()-1,index,4);
}
void GNSS_Meas_Select::on_comboBoxTypeQZSS_6_currentIndexChanged(int index){
    uiMeas->comboBoxTypeQZSS_6->setCurrentIndex(index);
    this->changePrintMeas(QZSS,uiMeas->comboBoxFreqQZSS_6->currentIndex()-1,index,5);
}
void GNSS_Meas_Select::on_comboBoxTypeQZSS_7_currentIndexChanged(int index){
    uiMeas->comboBoxTypeQZSS_7->setCurrentIndex(index);
    this->changePrintMeas(QZSS,uiMeas->comboBoxFreqQZSS_7->currentIndex()-1,index,6);
}
void GNSS_Meas_Select::on_comboBoxTypeQZSS_8_currentIndexChanged(int index){
    uiMeas->comboBoxTypeQZSS_8->setCurrentIndex(index);
    this->changePrintMeas(QZSS,uiMeas->comboBoxFreqQZSS_8->currentIndex()-1,index,7);
}
void GNSS_Meas_Select::on_comboBoxTypeQZSS_9_currentIndexChanged(int index){
    uiMeas->comboBoxTypeQZSS_9->setCurrentIndex(index);
    this->changePrintMeas(QZSS,uiMeas->comboBoxFreqQZSS_9->currentIndex()-1,index,8);
}
void GNSS_Meas_Select::on_comboBoxTypeQZSS_10_currentIndexChanged(int index){
    uiMeas->comboBoxTypeQZSS_10->setCurrentIndex(index);
    this->changePrintMeas(QZSS,uiMeas->comboBoxFreqQZSS_10->currentIndex()-1,index,9);
}

//IRNSS
// Function to set IRNSS default
void GNSS_Meas_Select::SetDefaultMeasIRNSS(){
    nPrint[IRNSS]=1;
    FrameGNSSLabel[IRNSS][1]->setHidden(true);
    uiMeas->frameMeasIRNSS_1->setHidden(false);
    uiMeas->frameMeasIRNSS_2->setHidden(true);
    uiMeas->frameMeasIRNSS_3->setHidden(true);
    uiMeas->frameMeasIRNSS_4->setHidden(true);
    uiMeas->frameMeasIRNSS_5->setHidden(true);
    uiMeas->frameMeasIRNSS_6->setHidden(true);
    uiMeas->frameMeasIRNSS_7->setHidden(true);
    uiMeas->frameMeasIRNSS_8->setHidden(true);
    uiMeas->frameMeasIRNSS_9->setHidden(true);
    uiMeas->frameMeasIRNSS_10->setHidden(true);
    this->on_comboBoxFreqIRNSS_1_currentIndexChanged(0);
    this->on_comboBoxFreqIRNSS_2_currentIndexChanged(0);
    this->on_comboBoxFreqIRNSS_3_currentIndexChanged(0);
    this->on_comboBoxFreqIRNSS_4_currentIndexChanged(0);
    this->on_comboBoxFreqIRNSS_5_currentIndexChanged(0);
    this->on_comboBoxFreqIRNSS_6_currentIndexChanged(0);
    this->on_comboBoxFreqIRNSS_7_currentIndexChanged(0);
    this->on_comboBoxFreqIRNSS_8_currentIndexChanged(0);
    this->on_comboBoxFreqIRNSS_9_currentIndexChanged(0);
    this->on_comboBoxFreqIRNSS_10_currentIndexChanged(0);
}
// Function to change IRNSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqIRNSS_1_currentIndexChanged(int index){
    uiMeas->comboBoxFreqIRNSS_1->setCurrentIndex(index);
    this->on_comboBoxTypeIRNSS_1_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeIRNSS_1->setEnabled(false);
        uiMeas->comboBoxMeasIRNSS_1->setEnabled(false);
        this->cleanPrintMeas(IRNSS,0);
    } else {
        uiMeas->comboBoxTypeIRNSS_1->setEnabled(true);
        uiMeas->comboBoxMeasIRNSS_1->setEnabled(true);
    }
}
// Function to change IRNSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqIRNSS_2_currentIndexChanged(int index){
    uiMeas->comboBoxFreqIRNSS_2->setCurrentIndex(index);
    this->on_comboBoxTypeIRNSS_2_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeIRNSS_2->setEnabled(false);
        uiMeas->comboBoxMeasIRNSS_2->setEnabled(false);
        this->cleanPrintMeas(IRNSS,1);
    } else {
        uiMeas->comboBoxTypeIRNSS_2->setEnabled(true);
        uiMeas->comboBoxMeasIRNSS_2->setEnabled(true);
    }
}
// Function to change IRNSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqIRNSS_3_currentIndexChanged(int index){
    uiMeas->comboBoxFreqIRNSS_3->setCurrentIndex(index);
    this->on_comboBoxTypeIRNSS_3_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeIRNSS_3->setEnabled(false);
        uiMeas->comboBoxMeasIRNSS_3->setEnabled(false);
        this->cleanPrintMeas(IRNSS,2);
    } else {
        uiMeas->comboBoxTypeIRNSS_3->setEnabled(true);
        uiMeas->comboBoxMeasIRNSS_3->setEnabled(true);
    }
}
// Function to change IRNSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqIRNSS_4_currentIndexChanged(int index){
    uiMeas->comboBoxFreqIRNSS_4->setCurrentIndex(index);
    this->on_comboBoxTypeIRNSS_4_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeIRNSS_4->setEnabled(false);
        uiMeas->comboBoxMeasIRNSS_4->setEnabled(false);
        this->cleanPrintMeas(IRNSS,3);
    } else {
        uiMeas->comboBoxTypeIRNSS_4->setEnabled(true);
        uiMeas->comboBoxMeasIRNSS_4->setEnabled(true);
    }
}
// Function to change IRNSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqIRNSS_5_currentIndexChanged(int index){
    uiMeas->comboBoxFreqIRNSS_5->setCurrentIndex(index);
    this->on_comboBoxTypeIRNSS_5_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeIRNSS_5->setEnabled(false);
        uiMeas->comboBoxMeasIRNSS_5->setEnabled(false);
        this->cleanPrintMeas(IRNSS,4);
    } else {
        uiMeas->comboBoxTypeIRNSS_5->setEnabled(true);
        uiMeas->comboBoxMeasIRNSS_5->setEnabled(true);
    }
}
// Function to change IRNSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqIRNSS_6_currentIndexChanged(int index){
    uiMeas->comboBoxFreqIRNSS_6->setCurrentIndex(index);
    this->on_comboBoxTypeIRNSS_6_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeIRNSS_6->setEnabled(false);
        uiMeas->comboBoxMeasIRNSS_6->setEnabled(false);
        this->cleanPrintMeas(IRNSS,5);
    } else {
        uiMeas->comboBoxTypeIRNSS_6->setEnabled(true);
        uiMeas->comboBoxMeasIRNSS_6->setEnabled(true);
    }
}
// Function to change IRNSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqIRNSS_7_currentIndexChanged(int index){
    uiMeas->comboBoxFreqIRNSS_7->setCurrentIndex(index);
    this->on_comboBoxTypeIRNSS_7_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeIRNSS_7->setEnabled(false);
        uiMeas->comboBoxMeasIRNSS_7->setEnabled(false);
        this->cleanPrintMeas(IRNSS,6);
    } else {
        uiMeas->comboBoxTypeIRNSS_7->setEnabled(true);
        uiMeas->comboBoxMeasIRNSS_7->setEnabled(true);
    }
}
// Function to change IRNSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqIRNSS_8_currentIndexChanged(int index){
    uiMeas->comboBoxFreqIRNSS_8->setCurrentIndex(index);
    this->on_comboBoxTypeIRNSS_8_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeIRNSS_8->setEnabled(false);
        uiMeas->comboBoxMeasIRNSS_8->setEnabled(false);
        this->cleanPrintMeas(IRNSS,7);
    } else {
        uiMeas->comboBoxTypeIRNSS_8->setEnabled(true);
        uiMeas->comboBoxMeasIRNSS_8->setEnabled(true);
    }
}
// Function to change IRNSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqIRNSS_9_currentIndexChanged(int index){
    uiMeas->comboBoxFreqIRNSS_9->setCurrentIndex(index);
    this->on_comboBoxTypeIRNSS_9_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeIRNSS_9->setEnabled(false);
        uiMeas->comboBoxMeasIRNSS_9->setEnabled(false);
        this->cleanPrintMeas(IRNSS,8);
    } else {
        uiMeas->comboBoxTypeIRNSS_9->setEnabled(true);
        uiMeas->comboBoxMeasIRNSS_9->setEnabled(true);
    }
}
// Function to change IRNSS frequency comboBox
void GNSS_Meas_Select::on_comboBoxFreqIRNSS_10_currentIndexChanged(int index){
    uiMeas->comboBoxFreqIRNSS_10->setCurrentIndex(index);
    this->on_comboBoxTypeIRNSS_10_currentIndexChanged(0);
    if (index==0){
        uiMeas->comboBoxTypeIRNSS_10->setEnabled(false);
        uiMeas->comboBoxMeasIRNSS_10->setEnabled(false);
        this->cleanPrintMeas(IRNSS,9);
    } else {
        uiMeas->comboBoxTypeIRNSS_10->setEnabled(true);
        uiMeas->comboBoxMeasIRNSS_10->setEnabled(true);
    }
}
// Function to change IRNSS type comboBox
void GNSS_Meas_Select::on_comboBoxTypeIRNSS_1_currentIndexChanged(int index){
    uiMeas->comboBoxTypeIRNSS_1->setCurrentIndex(index);
    this->changePrintMeas(IRNSS,uiMeas->comboBoxFreqIRNSS_1->currentIndex()-1,index,0);
}
void GNSS_Meas_Select::on_comboBoxTypeIRNSS_2_currentIndexChanged(int index){
    uiMeas->comboBoxTypeIRNSS_2->setCurrentIndex(index);
    this->changePrintMeas(IRNSS,uiMeas->comboBoxFreqIRNSS_2->currentIndex()-1,index,1);
}
void GNSS_Meas_Select::on_comboBoxTypeIRNSS_3_currentIndexChanged(int index){
    uiMeas->comboBoxTypeIRNSS_3->setCurrentIndex(index);
    this->changePrintMeas(IRNSS,uiMeas->comboBoxFreqIRNSS_3->currentIndex()-1,index,2);
}
void GNSS_Meas_Select::on_comboBoxTypeIRNSS_4_currentIndexChanged(int index){
    uiMeas->comboBoxTypeIRNSS_4->setCurrentIndex(index);
    this->changePrintMeas(IRNSS,uiMeas->comboBoxFreqIRNSS_4->currentIndex()-1,index,3);
}
void GNSS_Meas_Select::on_comboBoxTypeIRNSS_5_currentIndexChanged(int index){
    uiMeas->comboBoxTypeIRNSS_5->setCurrentIndex(index);
    this->changePrintMeas(IRNSS,uiMeas->comboBoxFreqIRNSS_5->currentIndex()-1,index,4);
}
void GNSS_Meas_Select::on_comboBoxTypeIRNSS_6_currentIndexChanged(int index){
    uiMeas->comboBoxTypeIRNSS_6->setCurrentIndex(index);
    this->changePrintMeas(IRNSS,uiMeas->comboBoxFreqIRNSS_6->currentIndex()-1,index,5);
}
void GNSS_Meas_Select::on_comboBoxTypeIRNSS_7_currentIndexChanged(int index){
    uiMeas->comboBoxTypeIRNSS_7->setCurrentIndex(index);
    this->changePrintMeas(IRNSS,uiMeas->comboBoxFreqIRNSS_7->currentIndex()-1,index,6);
}
void GNSS_Meas_Select::on_comboBoxTypeIRNSS_8_currentIndexChanged(int index){
    uiMeas->comboBoxTypeIRNSS_8->setCurrentIndex(index);
    this->changePrintMeas(IRNSS,uiMeas->comboBoxFreqIRNSS_8->currentIndex()-1,index,7);
}
void GNSS_Meas_Select::on_comboBoxTypeIRNSS_9_currentIndexChanged(int index){
    uiMeas->comboBoxTypeIRNSS_9->setCurrentIndex(index);
    this->changePrintMeas(IRNSS,uiMeas->comboBoxFreqIRNSS_9->currentIndex()-1,index,8);
}
void GNSS_Meas_Select::on_comboBoxTypeIRNSS_10_currentIndexChanged(int index){
    uiMeas->comboBoxTypeIRNSS_10->setCurrentIndex(index);
    this->changePrintMeas(IRNSS,uiMeas->comboBoxFreqIRNSS_10->currentIndex()-1,index,9);
}

// Function to configure GPS satellites
void GNSS_Meas_Select::on_pushButtonGPS_clicked(){
    uiMeas->stackedWidgetMeasSelect->setCurrentIndex(GPS);
    uiMeas->labelSelectPRNFor->setText("GPS:");
    uiMeas->pushButtonGalileo->setChecked(false);
    uiMeas->pushButtonGLONASS->setChecked(false);
    uiMeas->pushButtonGEO->setChecked(false);
    uiMeas->pushButtonBDS->setChecked(false);
    uiMeas->pushButtonQZSS->setChecked(false);
    uiMeas->pushButtonIRNSS->setChecked(false);
    uiMeas->pushButtonGPS->setChecked(true);
    if (nPrint[GPS]==1) {
        uiMeas->pushButtonAddPrint->setEnabled(true);
        uiMeas->pushButtonDelPrint->setEnabled(false);
    } else if (nPrint[GPS]==10) {
        uiMeas->pushButtonAddPrint->setEnabled(false);
        uiMeas->pushButtonDelPrint->setEnabled(true);
    } else {
        uiMeas->pushButtonAddPrint->setEnabled(true);
        uiMeas->pushButtonDelPrint->setEnabled(true);
    }
}
// Function to configure Galileo satellites
void GNSS_Meas_Select::on_pushButtonGalileo_clicked(){
    uiMeas->stackedWidgetMeasSelect->setCurrentIndex(Galileo);
    uiMeas->labelSelectPRNFor->setText("Galileo:");
    uiMeas->pushButtonGPS->setChecked(false);
    uiMeas->pushButtonGLONASS->setChecked(false);
    uiMeas->pushButtonGEO->setChecked(false);
    uiMeas->pushButtonBDS->setChecked(false);
    uiMeas->pushButtonQZSS->setChecked(false);
    uiMeas->pushButtonIRNSS->setChecked(false);
    uiMeas->pushButtonGalileo->setChecked(true);
    if (nPrint[Galileo]==1) {
        uiMeas->pushButtonAddPrint->setEnabled(true);
        uiMeas->pushButtonDelPrint->setEnabled(false);
    } else if (nPrint[Galileo]==10) {
        uiMeas->pushButtonAddPrint->setEnabled(false);
        uiMeas->pushButtonDelPrint->setEnabled(true);
    } else {
        uiMeas->pushButtonAddPrint->setEnabled(true);
        uiMeas->pushButtonDelPrint->setEnabled(true);
    }
}
// Function to configure GLONASS satellites
void GNSS_Meas_Select::on_pushButtonGLONASS_clicked(){
    uiMeas->stackedWidgetMeasSelect->setCurrentIndex(GLONASS);
    uiMeas->labelSelectPRNFor->setText("GLONASS:");
    uiMeas->pushButtonGPS->setChecked(false);
    uiMeas->pushButtonGalileo->setChecked(false);
    uiMeas->pushButtonGEO->setChecked(false);
    uiMeas->pushButtonBDS->setChecked(false);
    uiMeas->pushButtonQZSS->setChecked(false);
    uiMeas->pushButtonIRNSS->setChecked(false);
    uiMeas->pushButtonGLONASS->setChecked(true);
    if (nPrint[GLONASS]==1) {
        uiMeas->pushButtonAddPrint->setEnabled(true);
        uiMeas->pushButtonDelPrint->setEnabled(false);
    } else if (nPrint[GLONASS]==10) {
        uiMeas->pushButtonAddPrint->setEnabled(false);
        uiMeas->pushButtonDelPrint->setEnabled(true);
    } else {
        uiMeas->pushButtonAddPrint->setEnabled(true);
        uiMeas->pushButtonDelPrint->setEnabled(true);
    }
}
// Function to configure GEO satellites
void GNSS_Meas_Select::on_pushButtonGEO_clicked(){
    uiMeas->stackedWidgetMeasSelect->setCurrentIndex(GEO);
    uiMeas->labelSelectPRNFor->setText("GEO:");
    uiMeas->pushButtonGPS->setChecked(false);
    uiMeas->pushButtonGalileo->setChecked(false);
    uiMeas->pushButtonGLONASS->setChecked(false);
    uiMeas->pushButtonBDS->setChecked(false);
    uiMeas->pushButtonQZSS->setChecked(false);
    uiMeas->pushButtonIRNSS->setChecked(false);
    uiMeas->pushButtonGEO->setChecked(true);
    if (nPrint[GEO]==1) {
        uiMeas->pushButtonAddPrint->setEnabled(true);
        uiMeas->pushButtonDelPrint->setEnabled(false);
    } else if (nPrint[GEO]==10) {
        uiMeas->pushButtonAddPrint->setEnabled(false);
        uiMeas->pushButtonDelPrint->setEnabled(true);
    } else {
        uiMeas->pushButtonAddPrint->setEnabled(true);
        uiMeas->pushButtonDelPrint->setEnabled(true);
    }
}
// Function to configure BDS satellites
void GNSS_Meas_Select::on_pushButtonBDS_clicked(){
    uiMeas->stackedWidgetMeasSelect->setCurrentIndex(BDS);
    uiMeas->labelSelectPRNFor->setText("BDS:");
    uiMeas->pushButtonGPS->setChecked(false);
    uiMeas->pushButtonGalileo->setChecked(false);
    uiMeas->pushButtonGLONASS->setChecked(false);
    uiMeas->pushButtonGEO->setChecked(false);
    uiMeas->pushButtonQZSS->setChecked(false);
    uiMeas->pushButtonIRNSS->setChecked(false);
    uiMeas->pushButtonBDS->setChecked(true);
    if (nPrint[BDS]==1) {
        uiMeas->pushButtonAddPrint->setEnabled(true);
        uiMeas->pushButtonDelPrint->setEnabled(false);
    } else if (nPrint[BDS]==10) {
        uiMeas->pushButtonAddPrint->setEnabled(false);
        uiMeas->pushButtonDelPrint->setEnabled(true);
    } else {
        uiMeas->pushButtonAddPrint->setEnabled(true);
        uiMeas->pushButtonDelPrint->setEnabled(true);
    }
}
// Function to configure QZSS satellites
void GNSS_Meas_Select::on_pushButtonQZSS_clicked(){
    uiMeas->stackedWidgetMeasSelect->setCurrentIndex(QZSS);
    uiMeas->labelSelectPRNFor->setText("QZSS:");
    uiMeas->pushButtonGPS->setChecked(false);
    uiMeas->pushButtonGalileo->setChecked(false);
    uiMeas->pushButtonGLONASS->setChecked(false);
    uiMeas->pushButtonGEO->setChecked(false);
    uiMeas->pushButtonBDS->setChecked(false);
    uiMeas->pushButtonIRNSS->setChecked(false);
    uiMeas->pushButtonQZSS->setChecked(true);
    if (nPrint[QZSS]==1) {
        uiMeas->pushButtonAddPrint->setEnabled(true);
        uiMeas->pushButtonDelPrint->setEnabled(false);
    } else if (nPrint[QZSS]==10) {
        uiMeas->pushButtonAddPrint->setEnabled(false);
        uiMeas->pushButtonDelPrint->setEnabled(true);
    } else {
        uiMeas->pushButtonAddPrint->setEnabled(true);
        uiMeas->pushButtonDelPrint->setEnabled(true);
    }
}
// Function to configure IRNSS satellites
void GNSS_Meas_Select::on_pushButtonIRNSS_clicked(){
    uiMeas->stackedWidgetMeasSelect->setCurrentIndex(IRNSS);
    uiMeas->labelSelectPRNFor->setText("IRNSS:");
    uiMeas->pushButtonGPS->setChecked(false);
    uiMeas->pushButtonGalileo->setChecked(false);
    uiMeas->pushButtonGLONASS->setChecked(false);
    uiMeas->pushButtonGEO->setChecked(false);
    uiMeas->pushButtonBDS->setChecked(false);
    uiMeas->pushButtonQZSS->setChecked(false);
    uiMeas->pushButtonIRNSS->setChecked(true);
    if (nPrint[IRNSS]==1) {
        uiMeas->pushButtonAddPrint->setEnabled(true);
        uiMeas->pushButtonDelPrint->setEnabled(false);
    } else if (nPrint[IRNSS]==10) {
        uiMeas->pushButtonAddPrint->setEnabled(false);
        uiMeas->pushButtonDelPrint->setEnabled(true);
    } else {
        uiMeas->pushButtonAddPrint->setEnabled(true);
        uiMeas->pushButtonDelPrint->setEnabled(true);
    }
}

//GPS


// Function to select GPS satellites
void GNSS_Meas_Select::changePushButtonGPS(bool checked){
    uiMeas->pushButtonGPS->setEnabled(checked);
    this->SetDefaultMeasGPS();
}
// Function to select Galileo satellites
void GNSS_Meas_Select::changePushButtonGalileo(bool checked){
    uiMeas->pushButtonGalileo->setEnabled(checked);
    this->SetDefaultMeasGalileo();
}
// Function to select GLONASS satellites
void GNSS_Meas_Select::changePushButtonGLONASS(bool checked){
    uiMeas->pushButtonGLONASS->setEnabled(checked);
    this->SetDefaultMeasGLONASS();
}
// Function to select GEO satellites
void GNSS_Meas_Select::changePushButtonGEO(bool checked){
    uiMeas->pushButtonGEO->setEnabled(checked);
    this->SetDefaultMeasGEO();
}
// Function to select BDS satellites
void GNSS_Meas_Select::changePushButtonBDS(bool checked){
    uiMeas->pushButtonBDS->setEnabled(checked);
    this->SetDefaultMeasBDS();
}
// Function to select QZSS satellites
void GNSS_Meas_Select::changePushButtonQZSS(bool checked){
    uiMeas->pushButtonQZSS->setEnabled(checked);
    this->SetDefaultMeasQZSS();
}
// Function to select IRNSS satellites
void GNSS_Meas_Select::changePushButtonIRNSS(bool checked){
    uiMeas->pushButtonIRNSS->setEnabled(checked);
    this->SetDefaultMeasIRNSS();
}

// Function to configure GPS satellites
void GNSS_Meas_Select::on_pushButtonPublicGPS_clicked(){
    this->on_pushButtonGPS_clicked();
}
// Function to configure Galileo satellites
void GNSS_Meas_Select::on_pushButtonPublicGalileo_clicked(){
    this->on_pushButtonGalileo_clicked();
}
// Function to configure GLONASS satellites
void GNSS_Meas_Select::on_pushButtonPublicGLONASS_clicked(){
    this->on_pushButtonGLONASS_clicked();
}
// Function to configure GEO satellites
void GNSS_Meas_Select::on_pushButtonPublicGEO_clicked(){
    this->on_pushButtonGEO_clicked();
}
// Function to configure BDS satellites
void GNSS_Meas_Select::on_pushButtonPublicBDS_clicked(){
    this->on_pushButtonBDS_clicked();
}
// Function to configure QZSS satellites
void GNSS_Meas_Select::on_pushButtonPublicQZSS_clicked(){
    this->on_pushButtonQZSS_clicked();
}
// Function to configure IRNSS satellites
void GNSS_Meas_Select::on_pushButtonPublicIRNSS_clicked(){
    this->on_pushButtonIRNSS_clicked();
}

void GNSS_Meas_Select::on_pushButtonMeasSelectDefault_clicked(){
    this->setMeasdefaults();
}
void GNSS_Meas_Select::on_pushButtonMeasSelectOk_clicked(){
    this->OkFlag=1;

    this->close();
}
void GNSS_Meas_Select::on_pushButtonMeasSelectCancel_clicked(){
    this->OkFlag=0;

    this->close();
}
void GNSS_Meas_Select::closeEvent(QCloseEvent *event){
    this->MeasFlag=0;
    for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++){
        for (int iprint=0; iprint<10; iprint++){
            if ( FrameGNSSPrint[iGNSS][iprint]->isHidden()==false && ComBoBoxGNSSFreq[iGNSS][iprint]->currentIndex()>0 ) this->MeasFlag++;
        }
    }
    event->accept();
}

void GNSS_Meas_Select::changeCurrentPage(){
    for (int i=0; i<MAX_GNSS; i++){
        if (PushButtonGNSS[i]->isEnabled()){
            (this->*PushButtonGNSSFunctions[i])();
            break;
        }
    }
}

int GNSS_Meas_Select::getgLABOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString){
    QString usedOption,MeasOptions[MAX_GNSS];
    int repeatedTextPos[MAX_GNSS][10]={{0}};
    int numrepeatedTextPos[MAX_GNSS]={0};
    bool MeasOK=false;
    if (warningString->length()<0) *warningString=""; //only to avoid the warning of unused "warningString"
    if (errorString->length()<0) *errorString=""; //only to avoid the warning of unused "warningString"
    //loop of constellations
    for (int gnssi=0; gnssi<MAX_GNSS; gnssi++){
        MeasOptions[gnssi]="";
        //loop print
        for (int iprint=0; iprint<10; iprint++){
            if ( FrameGNSSPrint[gnssi][iprint]->isHidden()==false && ComBoBoxGNSSFreq[gnssi][iprint]->currentIndex()>0 ){
                //Only add measurement if it is not repeated
                if (!MeasOptions[gnssi].contains(ComBoBoxGNSSMeas[gnssi][iprint]->currentText())) {
                    MeasOptions[gnssi] += "-" + ComBoBoxGNSSMeas[gnssi][iprint]->currentText();
                } else {
                    repeatedTextPos[gnssi][numrepeatedTextPos[gnssi]]=iprint;
                    numrepeatedTextPos[gnssi]++;
                }
            }
        }
        if (MeasOptions[gnssi].size()>2) {
            MeasOK=true;
            MeasOptions[gnssi].insert(0,indentifierGNSS[gnssi] + "0");
        } else {
            MeasOptions[gnssi]="";
        }
    }
    //Loop to join by constellation
    for (int gnssi=0; gnssi<MAX_GNSS; gnssi++){
        for (int gnssi2=0; gnssi2<MAX_GNSS; gnssi2++){
            if (gnssi==gnssi2) continue;
            if (MeasOptions[gnssi]=="" || MeasOptions[gnssi2]=="") continue;
            int pos1,pos2;
            pos1=MeasOptions[gnssi].indexOf("-")+1;
            pos2=MeasOptions[gnssi2].indexOf("-")+1;

            if (QString::compare(MeasOptions[gnssi].mid(pos1),MeasOptions[gnssi2].mid(pos2))==0 ) {
                MeasOptions[gnssi].insert(pos1-2,MeasOptions[gnssi2].left(1));
                MeasOptions[gnssi2]="";
            }
        }
    }


    int firstArg=1;
    if (MeasOK){
        for (int gnssi=0; gnssi<MAX_GNSS; gnssi++){
            //Print warning for repeated measurements
            if (numrepeatedTextPos[gnssi]>0) {
                if (numrepeatedTextPos[gnssi]==1) {
                    *warningString += "OUTPUT: " + GNSSName[gnssi] + " constellation in MEAS print measurement selection has measurement in position " + QString("%1").arg(repeatedTextPos[gnssi][0]+1) + " repeated.\n";
                } else {
                    *warningString += "OUTPUT: " + GNSSName[gnssi] + " constellation in MEAS print measurement selection has measurements in positions " + QString("%1").arg(repeatedTextPos[gnssi][0]+1);
                    for(int i=1;i<numrepeatedTextPos[gnssi]-1;i++) {
                        *warningString += ", " + QString("%1").arg(repeatedTextPos[gnssi][i]+1);
                    }
                    *warningString += " and " + QString("%1").arg(repeatedTextPos[gnssi][numrepeatedTextPos[gnssi]-1]+1) + " repeated.\n";
                }
            }
            if (MeasOptions[gnssi]!=""){
                if (firstArg==1) {
                    firstArg=0;
                    *saveString += "-print:meas:select";
                    *runString << "-print:meas:select";
                }
                *saveString += " " + MeasOptions[gnssi];
                *runString << MeasOptions[gnssi];
            }
        }
        if (firstArg==0) *saveString += "\n";
    }
    return !firstArg;
}
void GNSS_Meas_Select::loadgLABOptions(QString *warningString, QStringList *ParametersList){
    //reset nPrint to 0
    int skipIteration;
    for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) nPrint[iGNSS]=0;
    int nPar=ParametersList->count();
    for (int iPar=0; iPar<nPar; iPar++){
        int iGNSS=-1;
        skipIteration=0;
        QStringList valueList = ParametersList->at(iPar).split("-", QString::SkipEmptyParts);
        bool ParamSatRanges=ParametersList->at(iPar).contains(QRegularExpression(regExpSatWithRanges));
        bool ParamSatNoRanges=valueList[0].contains(QRegularExpression(regExpSatNoRanges));
        if(!ParamSatNoRanges && !ParamSatRanges ) {
           *warningString += "FILTER: Invalid MEAS print measurement '" + ParametersList->at(iPar) + "'. It was skipped.\n";
           continue;
        } else if (ParamSatRanges) {
           *warningString += "FILTER: The GUI cannot read parameters with satellite ranges (except '-pre:sat'), as options are constellations wise. Parameter '" + ParametersList->at(iPar) + "' was skipped.\n";
           continue;
        }
        //find frequency list
        for(int i=0;i<valueList[0].size();i++) {
            if (valueList[0].at(i).isDigit()==true) break;
            else if (checkConstellationQChar(valueList[0].at(i))==0) {
                *warningString += "Parameter '-print:meas:select' has unknown constellation in argument '" + ParametersList->at(iPar) + "' It was skipped.\n";
                skipIteration=1;
            }
        }
        if (skipIteration==1) continue;
        if ( valueList[0].contains("0") ) {
            //loop constellation
            for (iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
                if ( valueList[0].contains(indentifierGNSS[iGNSS],Qt::CaseInsensitive) ){
                    for (int measi=1; measi<valueList.count(); measi++){
                        int iCLDSLLI=-1,fStart=1; // fStart = 1 for C, L, S, D, = 3 for LLI
                        //L
                        if ( valueList[measi].size()==3 && valueList[measi].left(1).toUpper()=="C" ){
                            iCLDSLLI=0;
                        }
                        //C
                        else if ( valueList[measi].size()==3 && valueList[measi].left(1).toUpper()=="L" ){
                            iCLDSLLI=1;
                        }
                        //S
                        else if ( valueList[measi].size()==3 && valueList[measi].left(1).toUpper()=="S" ){
                            iCLDSLLI=2;
                        }
                        //D
                        else if ( valueList[measi].size()==3 && valueList[measi].left(1).toUpper()=="D" ){
                            iCLDSLLI=3;
                        }
                        //LLI
                        else if ( valueList[measi].size()==5 && valueList[measi].left(3).toUpper()=="LLI" ){
                            iCLDSLLI=4;
                            fStart=3;
                        }
                        //unknown
                        else {
                            *warningString += "Parameter '-print:meas:select' has unknown measurement '"+ valueList[measi] +"' for " + GNSSName[iGNSS] + " It was skipped.\n";
                        }
                        if (iCLDSLLI>=0) {
                            int freq1=-1;
                            //frequency
                            for (int ifreq=0; ifreq<nFreqGNSS[iGNSS]; ifreq++){
                                if (valueList[measi].mid(fStart,1)==FreqGNSSList[iGNSS][ifreq]) {
                                    freq1=ifreq;
                                }
                            }
                            if (freq1<0){
                                *warningString += "Parameter '-print:meas:select' has unknown measurement '"+ valueList[measi] +"' for "+ GNSSName[iGNSS] +". It was skipped.\n";
                            } else {
                                int meas1=-1;
                                //measurement
                                for (int imeas=0; imeas<GNSSFreqTypeMeas[iGNSS][freq1][iCLDSLLI].size(); imeas++){
                                    if ( QString::compare(valueList[measi].toUpper(),GNSSFreqTypeMeas[iGNSS][freq1][iCLDSLLI][imeas],Qt::CaseSensitive)==0 ) {
                                        meas1=imeas;
                                        break;
                                    }
                                }
                                if (meas1<0){
                                    *warningString += "Parameter '-print:meas:select' has unknown measurement '"+ valueList[measi] +"' for "+ GNSSName[iGNSS] +". It was skipped.\n";
                                } else if ( nPrint[iGNSS]>9 ) {
                                    *warningString += "Parameter '-print:meas:select' has more than 10 values for "+ GNSSName[iGNSS] + " (" + valueList[measi] + "). It was skipped.\n";
                                } else {
                                    int iprint=nPrint[iGNSS]++;
                                    FrameGNSSPrint[iGNSS][iprint]->setHidden(false);
                                    ComBoBoxGNSSFreq[iGNSS][iprint]->currentIndexChanged(freq1+1);
                                    ComBoBoxGNSSType[iGNSS][iprint]->currentIndexChanged(iCLDSLLI);
                                    ComBoBoxGNSSMeas[iGNSS][iprint]->setCurrentIndex(meas1);
                                }
                            }
                        }
                    }
                }
            }
        } else {
            *warningString += "The GUI cannot load per satellite configuration for parameter '-print:meas:select' (only full constellation with PRN 0), as in argument '" + ParametersList->at(iPar) + "'. It was skipped.\n";
        }
    }
    //reset nPrint from 0 to 1
    for (int iGNSS=0; iGNSS<MAX_GNSS; iGNSS++) {
        if (nPrint[iGNSS]==0) nPrint[iGNSS]=1;
        else if (nPrint[iGNSS]>5) FrameGNSSLabel[iGNSS][1]->setHidden(false);
    }
    //Change to IRNSS and then back to GPS, to make sure "+" and "-" are in consistent state
    this->on_pushButtonGalileo_clicked();
    this->on_pushButtonGPS_clicked();
}
