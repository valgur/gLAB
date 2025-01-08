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

#include "glab_gui.h"
#include "ui_glab_gui.h"

//Function to initialize pointers to pushButton "clicked function" pointers
void gLAB_GUI::InitPushButtonsFuncPointers() {
    //GPS
    PushButtonSelectFunctions[GPS]=&gLAB_GUI::on_pushButtonGPSSelect_clicked;
    PushButtonSatFunctions[GPS][1]=&gLAB_GUI::on_pushButtonG1_clicked;
    PushButtonSatFunctions[GPS][2]=&gLAB_GUI::on_pushButtonG2_clicked;
    PushButtonSatFunctions[GPS][3]=&gLAB_GUI::on_pushButtonG3_clicked;
    PushButtonSatFunctions[GPS][4]=&gLAB_GUI::on_pushButtonG4_clicked;
    PushButtonSatFunctions[GPS][5]=&gLAB_GUI::on_pushButtonG5_clicked;
    PushButtonSatFunctions[GPS][6]=&gLAB_GUI::on_pushButtonG6_clicked;
    PushButtonSatFunctions[GPS][7]=&gLAB_GUI::on_pushButtonG7_clicked;
    PushButtonSatFunctions[GPS][8]=&gLAB_GUI::on_pushButtonG8_clicked;
    PushButtonSatFunctions[GPS][9]=&gLAB_GUI::on_pushButtonG9_clicked;
    PushButtonSatFunctions[GPS][10]=&gLAB_GUI::on_pushButtonG10_clicked;
    PushButtonSatFunctions[GPS][11]=&gLAB_GUI::on_pushButtonG11_clicked;
    PushButtonSatFunctions[GPS][12]=&gLAB_GUI::on_pushButtonG12_clicked;
    PushButtonSatFunctions[GPS][13]=&gLAB_GUI::on_pushButtonG13_clicked;
    PushButtonSatFunctions[GPS][14]=&gLAB_GUI::on_pushButtonG14_clicked;
    PushButtonSatFunctions[GPS][15]=&gLAB_GUI::on_pushButtonG15_clicked;
    PushButtonSatFunctions[GPS][16]=&gLAB_GUI::on_pushButtonG16_clicked;
    PushButtonSatFunctions[GPS][17]=&gLAB_GUI::on_pushButtonG17_clicked;
    PushButtonSatFunctions[GPS][18]=&gLAB_GUI::on_pushButtonG18_clicked;
    PushButtonSatFunctions[GPS][19]=&gLAB_GUI::on_pushButtonG19_clicked;
    PushButtonSatFunctions[GPS][20]=&gLAB_GUI::on_pushButtonG20_clicked;
    PushButtonSatFunctions[GPS][21]=&gLAB_GUI::on_pushButtonG21_clicked;
    PushButtonSatFunctions[GPS][22]=&gLAB_GUI::on_pushButtonG22_clicked;
    PushButtonSatFunctions[GPS][23]=&gLAB_GUI::on_pushButtonG23_clicked;
    PushButtonSatFunctions[GPS][24]=&gLAB_GUI::on_pushButtonG24_clicked;
    PushButtonSatFunctions[GPS][25]=&gLAB_GUI::on_pushButtonG25_clicked;
    PushButtonSatFunctions[GPS][26]=&gLAB_GUI::on_pushButtonG26_clicked;
    PushButtonSatFunctions[GPS][27]=&gLAB_GUI::on_pushButtonG27_clicked;
    PushButtonSatFunctions[GPS][28]=&gLAB_GUI::on_pushButtonG28_clicked;
    PushButtonSatFunctions[GPS][29]=&gLAB_GUI::on_pushButtonG29_clicked;
    PushButtonSatFunctions[GPS][30]=&gLAB_GUI::on_pushButtonG30_clicked;
    PushButtonSatFunctions[GPS][31]=&gLAB_GUI::on_pushButtonG31_clicked;
    PushButtonSatFunctions[GPS][32]=&gLAB_GUI::on_pushButtonG32_clicked;

    //Galileo
    PushButtonSelectFunctions[Galileo]=&gLAB_GUI::on_pushButtonGalileoSelect_clicked;
    PushButtonSatFunctions[Galileo][1]=&gLAB_GUI::on_pushButtonE1_clicked;
    PushButtonSatFunctions[Galileo][2]=&gLAB_GUI::on_pushButtonE2_clicked;
    PushButtonSatFunctions[Galileo][3]=&gLAB_GUI::on_pushButtonE3_clicked;
    PushButtonSatFunctions[Galileo][4]=&gLAB_GUI::on_pushButtonE4_clicked;
    PushButtonSatFunctions[Galileo][5]=&gLAB_GUI::on_pushButtonE5_clicked;
    PushButtonSatFunctions[Galileo][6]=&gLAB_GUI::on_pushButtonE6_clicked;
    PushButtonSatFunctions[Galileo][7]=&gLAB_GUI::on_pushButtonE7_clicked;
    PushButtonSatFunctions[Galileo][8]=&gLAB_GUI::on_pushButtonE8_clicked;
    PushButtonSatFunctions[Galileo][9]=&gLAB_GUI::on_pushButtonE9_clicked;
    PushButtonSatFunctions[Galileo][10]=&gLAB_GUI::on_pushButtonE10_clicked;
    PushButtonSatFunctions[Galileo][11]=&gLAB_GUI::on_pushButtonE11_clicked;
    PushButtonSatFunctions[Galileo][12]=&gLAB_GUI::on_pushButtonE12_clicked;
    PushButtonSatFunctions[Galileo][13]=&gLAB_GUI::on_pushButtonE13_clicked;
    PushButtonSatFunctions[Galileo][14]=&gLAB_GUI::on_pushButtonE14_clicked;
    PushButtonSatFunctions[Galileo][15]=&gLAB_GUI::on_pushButtonE15_clicked;
    PushButtonSatFunctions[Galileo][16]=&gLAB_GUI::on_pushButtonE16_clicked;
    PushButtonSatFunctions[Galileo][17]=&gLAB_GUI::on_pushButtonE17_clicked;
    PushButtonSatFunctions[Galileo][18]=&gLAB_GUI::on_pushButtonE18_clicked;
    PushButtonSatFunctions[Galileo][19]=&gLAB_GUI::on_pushButtonE19_clicked;
    PushButtonSatFunctions[Galileo][20]=&gLAB_GUI::on_pushButtonE20_clicked;
    PushButtonSatFunctions[Galileo][21]=&gLAB_GUI::on_pushButtonE21_clicked;
    PushButtonSatFunctions[Galileo][22]=&gLAB_GUI::on_pushButtonE22_clicked;
    PushButtonSatFunctions[Galileo][23]=&gLAB_GUI::on_pushButtonE23_clicked;
    PushButtonSatFunctions[Galileo][24]=&gLAB_GUI::on_pushButtonE24_clicked;
    PushButtonSatFunctions[Galileo][25]=&gLAB_GUI::on_pushButtonE25_clicked;
    PushButtonSatFunctions[Galileo][26]=&gLAB_GUI::on_pushButtonE26_clicked;
    PushButtonSatFunctions[Galileo][27]=&gLAB_GUI::on_pushButtonE27_clicked;
    PushButtonSatFunctions[Galileo][28]=&gLAB_GUI::on_pushButtonE28_clicked;
    PushButtonSatFunctions[Galileo][29]=&gLAB_GUI::on_pushButtonE29_clicked;
    PushButtonSatFunctions[Galileo][30]=&gLAB_GUI::on_pushButtonE30_clicked;
    PushButtonSatFunctions[Galileo][31]=&gLAB_GUI::on_pushButtonE31_clicked;
    PushButtonSatFunctions[Galileo][32]=&gLAB_GUI::on_pushButtonE32_clicked;
    PushButtonSatFunctions[Galileo][33]=&gLAB_GUI::on_pushButtonE33_clicked;
    PushButtonSatFunctions[Galileo][34]=&gLAB_GUI::on_pushButtonE34_clicked;
    PushButtonSatFunctions[Galileo][35]=&gLAB_GUI::on_pushButtonE35_clicked;
    PushButtonSatFunctions[Galileo][36]=&gLAB_GUI::on_pushButtonE36_clicked;
    //GLONASS
    PushButtonSelectFunctions[GLONASS]=&gLAB_GUI::on_pushButtonGLONASSSelect_clicked;
    PushButtonSatFunctions[GLONASS][1]=&gLAB_GUI::on_pushButtonR1_clicked;
    PushButtonSatFunctions[GLONASS][2]=&gLAB_GUI::on_pushButtonR2_clicked;
    PushButtonSatFunctions[GLONASS][3]=&gLAB_GUI::on_pushButtonR3_clicked;
    PushButtonSatFunctions[GLONASS][4]=&gLAB_GUI::on_pushButtonR4_clicked;
    PushButtonSatFunctions[GLONASS][5]=&gLAB_GUI::on_pushButtonR5_clicked;
    PushButtonSatFunctions[GLONASS][6]=&gLAB_GUI::on_pushButtonR6_clicked;
    PushButtonSatFunctions[GLONASS][7]=&gLAB_GUI::on_pushButtonR7_clicked;
    PushButtonSatFunctions[GLONASS][8]=&gLAB_GUI::on_pushButtonR8_clicked;
    PushButtonSatFunctions[GLONASS][9]=&gLAB_GUI::on_pushButtonR9_clicked;
    PushButtonSatFunctions[GLONASS][10]=&gLAB_GUI::on_pushButtonR10_clicked;
    PushButtonSatFunctions[GLONASS][11]=&gLAB_GUI::on_pushButtonR11_clicked;
    PushButtonSatFunctions[GLONASS][12]=&gLAB_GUI::on_pushButtonR12_clicked;
    PushButtonSatFunctions[GLONASS][13]=&gLAB_GUI::on_pushButtonR13_clicked;
    PushButtonSatFunctions[GLONASS][14]=&gLAB_GUI::on_pushButtonR14_clicked;
    PushButtonSatFunctions[GLONASS][15]=&gLAB_GUI::on_pushButtonR15_clicked;
    PushButtonSatFunctions[GLONASS][16]=&gLAB_GUI::on_pushButtonR16_clicked;
    PushButtonSatFunctions[GLONASS][17]=&gLAB_GUI::on_pushButtonR17_clicked;
    PushButtonSatFunctions[GLONASS][18]=&gLAB_GUI::on_pushButtonR18_clicked;
    PushButtonSatFunctions[GLONASS][19]=&gLAB_GUI::on_pushButtonR19_clicked;
    PushButtonSatFunctions[GLONASS][20]=&gLAB_GUI::on_pushButtonR20_clicked;
    PushButtonSatFunctions[GLONASS][21]=&gLAB_GUI::on_pushButtonR21_clicked;
    PushButtonSatFunctions[GLONASS][22]=&gLAB_GUI::on_pushButtonR22_clicked;
    PushButtonSatFunctions[GLONASS][23]=&gLAB_GUI::on_pushButtonR23_clicked;
    PushButtonSatFunctions[GLONASS][24]=&gLAB_GUI::on_pushButtonR24_clicked;
    PushButtonSatFunctions[GLONASS][25]=&gLAB_GUI::on_pushButtonR25_clicked;
    PushButtonSatFunctions[GLONASS][26]=&gLAB_GUI::on_pushButtonR26_clicked;
    PushButtonSatFunctions[GLONASS][27]=&gLAB_GUI::on_pushButtonR27_clicked;
    PushButtonSatFunctions[GLONASS][28]=&gLAB_GUI::on_pushButtonR28_clicked;
    PushButtonSatFunctions[GLONASS][29]=&gLAB_GUI::on_pushButtonR29_clicked;
    PushButtonSatFunctions[GLONASS][30]=&gLAB_GUI::on_pushButtonR30_clicked;
    PushButtonSatFunctions[GLONASS][31]=&gLAB_GUI::on_pushButtonR31_clicked;
    PushButtonSatFunctions[GLONASS][32]=&gLAB_GUI::on_pushButtonR32_clicked;
    //GEO
    PushButtonSelectFunctions[GEO]=&gLAB_GUI::on_pushButtonGEOSelect_clicked;
    PushButtonSatFunctions[GEO][1]=&gLAB_GUI::on_pushButtonS120_clicked;
    PushButtonSatFunctions[GEO][2]=&gLAB_GUI::on_pushButtonS121_clicked;
    PushButtonSatFunctions[GEO][3]=&gLAB_GUI::on_pushButtonS122_clicked;
    PushButtonSatFunctions[GEO][4]=&gLAB_GUI::on_pushButtonS123_clicked;
    PushButtonSatFunctions[GEO][5]=&gLAB_GUI::on_pushButtonS124_clicked;
    PushButtonSatFunctions[GEO][6]=&gLAB_GUI::on_pushButtonS125_clicked;
    PushButtonSatFunctions[GEO][7]=&gLAB_GUI::on_pushButtonS126_clicked;
    PushButtonSatFunctions[GEO][8]=&gLAB_GUI::on_pushButtonS127_clicked;
    PushButtonSatFunctions[GEO][9]=&gLAB_GUI::on_pushButtonS128_clicked;
    PushButtonSatFunctions[GEO][10]=&gLAB_GUI::on_pushButtonS129_clicked;
    PushButtonSatFunctions[GEO][11]=&gLAB_GUI::on_pushButtonS130_clicked;
    PushButtonSatFunctions[GEO][12]=&gLAB_GUI::on_pushButtonS131_clicked;
    PushButtonSatFunctions[GEO][13]=&gLAB_GUI::on_pushButtonS132_clicked;
    PushButtonSatFunctions[GEO][14]=&gLAB_GUI::on_pushButtonS133_clicked;
    PushButtonSatFunctions[GEO][15]=&gLAB_GUI::on_pushButtonS134_clicked;
    PushButtonSatFunctions[GEO][16]=&gLAB_GUI::on_pushButtonS135_clicked;
    PushButtonSatFunctions[GEO][17]=&gLAB_GUI::on_pushButtonS136_clicked;
    PushButtonSatFunctions[GEO][18]=&gLAB_GUI::on_pushButtonS137_clicked;
    PushButtonSatFunctions[GEO][19]=&gLAB_GUI::on_pushButtonS138_clicked;
    PushButtonSatFunctions[GEO][20]=&gLAB_GUI::on_pushButtonS139_clicked;
    PushButtonSatFunctions[GEO][21]=&gLAB_GUI::on_pushButtonS140_clicked;
    PushButtonSatFunctions[GEO][22]=&gLAB_GUI::on_pushButtonS141_clicked;
    PushButtonSatFunctions[GEO][23]=&gLAB_GUI::on_pushButtonS142_clicked;
    PushButtonSatFunctions[GEO][24]=&gLAB_GUI::on_pushButtonS143_clicked;
    PushButtonSatFunctions[GEO][25]=&gLAB_GUI::on_pushButtonS144_clicked;
    PushButtonSatFunctions[GEO][26]=&gLAB_GUI::on_pushButtonS145_clicked;
    PushButtonSatFunctions[GEO][27]=&gLAB_GUI::on_pushButtonS146_clicked;
    PushButtonSatFunctions[GEO][28]=&gLAB_GUI::on_pushButtonS147_clicked;
    PushButtonSatFunctions[GEO][29]=&gLAB_GUI::on_pushButtonS148_clicked;
    PushButtonSatFunctions[GEO][30]=&gLAB_GUI::on_pushButtonS149_clicked;
    PushButtonSatFunctions[GEO][31]=&gLAB_GUI::on_pushButtonS150_clicked;
    PushButtonSatFunctions[GEO][32]=&gLAB_GUI::on_pushButtonS151_clicked;
    PushButtonSatFunctions[GEO][33]=&gLAB_GUI::on_pushButtonS152_clicked;
    PushButtonSatFunctions[GEO][34]=&gLAB_GUI::on_pushButtonS153_clicked;
    PushButtonSatFunctions[GEO][35]=&gLAB_GUI::on_pushButtonS154_clicked;
    PushButtonSatFunctions[GEO][36]=&gLAB_GUI::on_pushButtonS155_clicked;
    PushButtonSatFunctions[GEO][37]=&gLAB_GUI::on_pushButtonS156_clicked;
    PushButtonSatFunctions[GEO][38]=&gLAB_GUI::on_pushButtonS157_clicked;
    PushButtonSatFunctions[GEO][39]=&gLAB_GUI::on_pushButtonS158_clicked;
    //BDS
    PushButtonSelectFunctions[BDS]=&gLAB_GUI::on_pushButtonBDSSelect_clicked;
    PushButtonSatFunctions[BDS][1]=&gLAB_GUI::on_pushButtonC1_clicked;
    PushButtonSatFunctions[BDS][2]=&gLAB_GUI::on_pushButtonC2_clicked;
    PushButtonSatFunctions[BDS][3]=&gLAB_GUI::on_pushButtonC3_clicked;
    PushButtonSatFunctions[BDS][4]=&gLAB_GUI::on_pushButtonC4_clicked;
    PushButtonSatFunctions[BDS][5]=&gLAB_GUI::on_pushButtonC5_clicked;
    PushButtonSatFunctions[BDS][6]=&gLAB_GUI::on_pushButtonC6_clicked;
    PushButtonSatFunctions[BDS][7]=&gLAB_GUI::on_pushButtonC7_clicked;
    PushButtonSatFunctions[BDS][8]=&gLAB_GUI::on_pushButtonC8_clicked;
    PushButtonSatFunctions[BDS][9]=&gLAB_GUI::on_pushButtonC9_clicked;
    PushButtonSatFunctions[BDS][10]=&gLAB_GUI::on_pushButtonC10_clicked;
    PushButtonSatFunctions[BDS][11]=&gLAB_GUI::on_pushButtonC11_clicked;
    PushButtonSatFunctions[BDS][12]=&gLAB_GUI::on_pushButtonC12_clicked;
    PushButtonSatFunctions[BDS][13]=&gLAB_GUI::on_pushButtonC13_clicked;
    PushButtonSatFunctions[BDS][14]=&gLAB_GUI::on_pushButtonC14_clicked;
    PushButtonSatFunctions[BDS][15]=&gLAB_GUI::on_pushButtonC15_clicked;
    PushButtonSatFunctions[BDS][16]=&gLAB_GUI::on_pushButtonC16_clicked;
    PushButtonSatFunctions[BDS][17]=&gLAB_GUI::on_pushButtonC17_clicked;
    PushButtonSatFunctions[BDS][18]=&gLAB_GUI::on_pushButtonC18_clicked;
    PushButtonSatFunctions[BDS][19]=&gLAB_GUI::on_pushButtonC19_clicked;
    PushButtonSatFunctions[BDS][20]=&gLAB_GUI::on_pushButtonC20_clicked;
    PushButtonSatFunctions[BDS][21]=&gLAB_GUI::on_pushButtonC21_clicked;
    PushButtonSatFunctions[BDS][22]=&gLAB_GUI::on_pushButtonC22_clicked;
    PushButtonSatFunctions[BDS][23]=&gLAB_GUI::on_pushButtonC23_clicked;
    PushButtonSatFunctions[BDS][24]=&gLAB_GUI::on_pushButtonC24_clicked;
    PushButtonSatFunctions[BDS][25]=&gLAB_GUI::on_pushButtonC25_clicked;
    PushButtonSatFunctions[BDS][26]=&gLAB_GUI::on_pushButtonC26_clicked;
    PushButtonSatFunctions[BDS][27]=&gLAB_GUI::on_pushButtonC27_clicked;
    PushButtonSatFunctions[BDS][28]=&gLAB_GUI::on_pushButtonC28_clicked;
    PushButtonSatFunctions[BDS][29]=&gLAB_GUI::on_pushButtonC29_clicked;
    PushButtonSatFunctions[BDS][30]=&gLAB_GUI::on_pushButtonC30_clicked;
    PushButtonSatFunctions[BDS][31]=&gLAB_GUI::on_pushButtonC31_clicked;
    PushButtonSatFunctions[BDS][32]=&gLAB_GUI::on_pushButtonC32_clicked;
    PushButtonSatFunctions[BDS][33]=&gLAB_GUI::on_pushButtonC33_clicked;
    PushButtonSatFunctions[BDS][34]=&gLAB_GUI::on_pushButtonC34_clicked;
    PushButtonSatFunctions[BDS][35]=&gLAB_GUI::on_pushButtonC35_clicked;
    PushButtonSatFunctions[BDS][36]=&gLAB_GUI::on_pushButtonC36_clicked;
    PushButtonSatFunctions[BDS][37]=&gLAB_GUI::on_pushButtonC37_clicked;
    PushButtonSatFunctions[BDS][38]=&gLAB_GUI::on_pushButtonC38_clicked;
    PushButtonSatFunctions[BDS][39]=&gLAB_GUI::on_pushButtonC39_clicked;
    PushButtonSatFunctions[BDS][40]=&gLAB_GUI::on_pushButtonC40_clicked;
    PushButtonSatFunctions[BDS][41]=&gLAB_GUI::on_pushButtonC41_clicked;
    PushButtonSatFunctions[BDS][42]=&gLAB_GUI::on_pushButtonC42_clicked;
    PushButtonSatFunctions[BDS][43]=&gLAB_GUI::on_pushButtonC43_clicked;
    PushButtonSatFunctions[BDS][44]=&gLAB_GUI::on_pushButtonC44_clicked;
    PushButtonSatFunctions[BDS][45]=&gLAB_GUI::on_pushButtonC45_clicked;
    PushButtonSatFunctions[BDS][46]=&gLAB_GUI::on_pushButtonC46_clicked;
    PushButtonSatFunctions[BDS][47]=&gLAB_GUI::on_pushButtonC47_clicked;
    PushButtonSatFunctions[BDS][48]=&gLAB_GUI::on_pushButtonC48_clicked;
    PushButtonSatFunctions[BDS][49]=&gLAB_GUI::on_pushButtonC49_clicked;
    PushButtonSatFunctions[BDS][50]=&gLAB_GUI::on_pushButtonC50_clicked;
    PushButtonSatFunctions[BDS][51]=&gLAB_GUI::on_pushButtonC51_clicked;
    PushButtonSatFunctions[BDS][52]=&gLAB_GUI::on_pushButtonC52_clicked;
    PushButtonSatFunctions[BDS][53]=&gLAB_GUI::on_pushButtonC53_clicked;
    PushButtonSatFunctions[BDS][54]=&gLAB_GUI::on_pushButtonC54_clicked;
    PushButtonSatFunctions[BDS][55]=&gLAB_GUI::on_pushButtonC55_clicked;
    PushButtonSatFunctions[BDS][56]=&gLAB_GUI::on_pushButtonC56_clicked;
    PushButtonSatFunctions[BDS][57]=&gLAB_GUI::on_pushButtonC57_clicked;
    PushButtonSatFunctions[BDS][58]=&gLAB_GUI::on_pushButtonC58_clicked;
    PushButtonSatFunctions[BDS][59]=&gLAB_GUI::on_pushButtonC59_clicked;
    PushButtonSatFunctions[BDS][60]=&gLAB_GUI::on_pushButtonC60_clicked;
    PushButtonSatFunctions[BDS][61]=&gLAB_GUI::on_pushButtonC61_clicked;
    PushButtonSatFunctions[BDS][62]=&gLAB_GUI::on_pushButtonC62_clicked;
    PushButtonSatFunctions[BDS][63]=&gLAB_GUI::on_pushButtonC63_clicked;
    //QZSS
    PushButtonSelectFunctions[QZSS]=&gLAB_GUI::on_pushButtonQZSSSelect_clicked;
    PushButtonSatFunctions[QZSS][1]=&gLAB_GUI::on_pushButtonJ1_clicked;
    PushButtonSatFunctions[QZSS][2]=&gLAB_GUI::on_pushButtonJ2_clicked;
    PushButtonSatFunctions[QZSS][3]=&gLAB_GUI::on_pushButtonJ3_clicked;
    PushButtonSatFunctions[QZSS][4]=&gLAB_GUI::on_pushButtonJ4_clicked;
    PushButtonSatFunctions[QZSS][5]=&gLAB_GUI::on_pushButtonJ5_clicked;
    PushButtonSatFunctions[QZSS][6]=&gLAB_GUI::on_pushButtonJ6_clicked;
    PushButtonSatFunctions[QZSS][7]=&gLAB_GUI::on_pushButtonJ7_clicked;
    PushButtonSatFunctions[QZSS][8]=&gLAB_GUI::on_pushButtonJ8_clicked;
    PushButtonSatFunctions[QZSS][9]=&gLAB_GUI::on_pushButtonJ9_clicked;
    PushButtonSatFunctions[QZSS][10]=&gLAB_GUI::on_pushButtonJ10_clicked;
    //IRNSS
    PushButtonSelectFunctions[IRNSS]=&gLAB_GUI::on_pushButtonIRNSSSelect_clicked;
    PushButtonSatFunctions[IRNSS][1]=&gLAB_GUI::on_pushButtonI1_clicked;
    PushButtonSatFunctions[IRNSS][2]=&gLAB_GUI::on_pushButtonI2_clicked;
    PushButtonSatFunctions[IRNSS][3]=&gLAB_GUI::on_pushButtonI3_clicked;
    PushButtonSatFunctions[IRNSS][4]=&gLAB_GUI::on_pushButtonI4_clicked;
    PushButtonSatFunctions[IRNSS][5]=&gLAB_GUI::on_pushButtonI5_clicked;
    PushButtonSatFunctions[IRNSS][6]=&gLAB_GUI::on_pushButtonI6_clicked;
    PushButtonSatFunctions[IRNSS][7]=&gLAB_GUI::on_pushButtonI7_clicked;
    PushButtonSatFunctions[IRNSS][8]=&gLAB_GUI::on_pushButtonI8_clicked;
    PushButtonSatFunctions[IRNSS][9]=&gLAB_GUI::on_pushButtonI9_clicked;
    PushButtonSatFunctions[IRNSS][10]=&gLAB_GUI::on_pushButtonI10_clicked;
    PushButtonSatFunctions[IRNSS][11]=&gLAB_GUI::on_pushButtonI11_clicked;
    PushButtonSatFunctions[IRNSS][12]=&gLAB_GUI::on_pushButtonI12_clicked;
    PushButtonSatFunctions[IRNSS][13]=&gLAB_GUI::on_pushButtonI13_clicked;
    PushButtonSatFunctions[IRNSS][14]=&gLAB_GUI::on_pushButtonI14_clicked;

    //To be completed with further constellations
}

//Function to initialize pointers to pushButton widget pointers
void gLAB_GUI::InitPushButtonsWidgetPointers() {
    //GPS
    PushButtonConstWidgets[GPS] = ui->pushButtonGPSSelect;
    PushButtonSatWidgets[GPS][1] = ui->pushButtonG1;
    PushButtonSatWidgets[GPS][2] = ui->pushButtonG2;
    PushButtonSatWidgets[GPS][3] = ui->pushButtonG3;
    PushButtonSatWidgets[GPS][4] = ui->pushButtonG4;
    PushButtonSatWidgets[GPS][5] = ui->pushButtonG5;
    PushButtonSatWidgets[GPS][6] = ui->pushButtonG6;
    PushButtonSatWidgets[GPS][7] = ui->pushButtonG7;
    PushButtonSatWidgets[GPS][8] = ui->pushButtonG8;
    PushButtonSatWidgets[GPS][9] = ui->pushButtonG9;
    PushButtonSatWidgets[GPS][10] = ui->pushButtonG10;
    PushButtonSatWidgets[GPS][11] = ui->pushButtonG11;
    PushButtonSatWidgets[GPS][12] = ui->pushButtonG12;
    PushButtonSatWidgets[GPS][13] = ui->pushButtonG13;
    PushButtonSatWidgets[GPS][14] = ui->pushButtonG14;
    PushButtonSatWidgets[GPS][15] = ui->pushButtonG15;
    PushButtonSatWidgets[GPS][16] = ui->pushButtonG16;
    PushButtonSatWidgets[GPS][17] = ui->pushButtonG17;
    PushButtonSatWidgets[GPS][18] = ui->pushButtonG18;
    PushButtonSatWidgets[GPS][19] = ui->pushButtonG19;
    PushButtonSatWidgets[GPS][20] = ui->pushButtonG20;
    PushButtonSatWidgets[GPS][21] = ui->pushButtonG21;
    PushButtonSatWidgets[GPS][22] = ui->pushButtonG22;
    PushButtonSatWidgets[GPS][23] = ui->pushButtonG23;
    PushButtonSatWidgets[GPS][24] = ui->pushButtonG24;
    PushButtonSatWidgets[GPS][25] = ui->pushButtonG25;
    PushButtonSatWidgets[GPS][26] = ui->pushButtonG26;
    PushButtonSatWidgets[GPS][27] = ui->pushButtonG27;
    PushButtonSatWidgets[GPS][28] = ui->pushButtonG28;
    PushButtonSatWidgets[GPS][29] = ui->pushButtonG29;
    PushButtonSatWidgets[GPS][30] = ui->pushButtonG30;
    PushButtonSatWidgets[GPS][31] = ui->pushButtonG31;
    PushButtonSatWidgets[GPS][32] = ui->pushButtonG32;

    //Galileo
    PushButtonConstWidgets[Galileo] = ui->pushButtonGalileoSelect;
    PushButtonSatWidgets[Galileo][1] = ui->pushButtonE1;
    PushButtonSatWidgets[Galileo][2] = ui->pushButtonE2;
    PushButtonSatWidgets[Galileo][3] = ui->pushButtonE3;
    PushButtonSatWidgets[Galileo][4] = ui->pushButtonE4;
    PushButtonSatWidgets[Galileo][5] = ui->pushButtonE5;
    PushButtonSatWidgets[Galileo][6] = ui->pushButtonE6;
    PushButtonSatWidgets[Galileo][7] = ui->pushButtonE7;
    PushButtonSatWidgets[Galileo][8] = ui->pushButtonE8;
    PushButtonSatWidgets[Galileo][9] = ui->pushButtonE9;
    PushButtonSatWidgets[Galileo][10] = ui->pushButtonE10;
    PushButtonSatWidgets[Galileo][11] = ui->pushButtonE11;
    PushButtonSatWidgets[Galileo][12] = ui->pushButtonE12;
    PushButtonSatWidgets[Galileo][13] = ui->pushButtonE13;
    PushButtonSatWidgets[Galileo][14] = ui->pushButtonE14;
    PushButtonSatWidgets[Galileo][15] = ui->pushButtonE15;
    PushButtonSatWidgets[Galileo][16] = ui->pushButtonE16;
    PushButtonSatWidgets[Galileo][17] = ui->pushButtonE17;
    PushButtonSatWidgets[Galileo][18] = ui->pushButtonE18;
    PushButtonSatWidgets[Galileo][19] = ui->pushButtonE19;
    PushButtonSatWidgets[Galileo][20] = ui->pushButtonE20;
    PushButtonSatWidgets[Galileo][21] = ui->pushButtonE21;
    PushButtonSatWidgets[Galileo][22] = ui->pushButtonE22;
    PushButtonSatWidgets[Galileo][23] = ui->pushButtonE23;
    PushButtonSatWidgets[Galileo][24] = ui->pushButtonE24;
    PushButtonSatWidgets[Galileo][25] = ui->pushButtonE25;
    PushButtonSatWidgets[Galileo][26] = ui->pushButtonE26;
    PushButtonSatWidgets[Galileo][27] = ui->pushButtonE27;
    PushButtonSatWidgets[Galileo][28] = ui->pushButtonE28;
    PushButtonSatWidgets[Galileo][29] = ui->pushButtonE29;
    PushButtonSatWidgets[Galileo][30] = ui->pushButtonE30;
    PushButtonSatWidgets[Galileo][31] = ui->pushButtonE31;
    PushButtonSatWidgets[Galileo][32] = ui->pushButtonE32;
    PushButtonSatWidgets[Galileo][33] = ui->pushButtonE33;
    PushButtonSatWidgets[Galileo][34] = ui->pushButtonE34;
    PushButtonSatWidgets[Galileo][35] = ui->pushButtonE35;
    PushButtonSatWidgets[Galileo][36] = ui->pushButtonE36;

    //GLONASS
    PushButtonConstWidgets[GLONASS] = ui->pushButtonGLONASSSelect;
    PushButtonSatWidgets[GLONASS][1] = ui->pushButtonR1;
    PushButtonSatWidgets[GLONASS][2] = ui->pushButtonR2;
    PushButtonSatWidgets[GLONASS][3] = ui->pushButtonR3;
    PushButtonSatWidgets[GLONASS][4] = ui->pushButtonR4;
    PushButtonSatWidgets[GLONASS][5] = ui->pushButtonR5;
    PushButtonSatWidgets[GLONASS][6] = ui->pushButtonR6;
    PushButtonSatWidgets[GLONASS][7] = ui->pushButtonR7;
    PushButtonSatWidgets[GLONASS][8] = ui->pushButtonR8;
    PushButtonSatWidgets[GLONASS][9] = ui->pushButtonR9;
    PushButtonSatWidgets[GLONASS][10] = ui->pushButtonR10;
    PushButtonSatWidgets[GLONASS][11] = ui->pushButtonR11;
    PushButtonSatWidgets[GLONASS][12] = ui->pushButtonR12;
    PushButtonSatWidgets[GLONASS][13] = ui->pushButtonR13;
    PushButtonSatWidgets[GLONASS][14] = ui->pushButtonR14;
    PushButtonSatWidgets[GLONASS][15] = ui->pushButtonR15;
    PushButtonSatWidgets[GLONASS][16] = ui->pushButtonR16;
    PushButtonSatWidgets[GLONASS][17] = ui->pushButtonR17;
    PushButtonSatWidgets[GLONASS][18] = ui->pushButtonR18;
    PushButtonSatWidgets[GLONASS][19] = ui->pushButtonR19;
    PushButtonSatWidgets[GLONASS][20] = ui->pushButtonR20;
    PushButtonSatWidgets[GLONASS][21] = ui->pushButtonR21;
    PushButtonSatWidgets[GLONASS][22] = ui->pushButtonR22;
    PushButtonSatWidgets[GLONASS][23] = ui->pushButtonR23;
    PushButtonSatWidgets[GLONASS][24] = ui->pushButtonR24;
    PushButtonSatWidgets[GLONASS][25] = ui->pushButtonR25;
    PushButtonSatWidgets[GLONASS][26] = ui->pushButtonR26;
    PushButtonSatWidgets[GLONASS][27] = ui->pushButtonR27;
    PushButtonSatWidgets[GLONASS][28] = ui->pushButtonR28;
    PushButtonSatWidgets[GLONASS][29] = ui->pushButtonR29;
    PushButtonSatWidgets[GLONASS][30] = ui->pushButtonR30;
    PushButtonSatWidgets[GLONASS][31] = ui->pushButtonR31;
    PushButtonSatWidgets[GLONASS][32] = ui->pushButtonR32;

    //GEO
    PushButtonConstWidgets[GEO] = ui->pushButtonGEOSelect;
    PushButtonSatWidgets[GEO][1] = ui->pushButtonS120;
    PushButtonSatWidgets[GEO][2] = ui->pushButtonS121;
    PushButtonSatWidgets[GEO][3] = ui->pushButtonS122;
    PushButtonSatWidgets[GEO][4] = ui->pushButtonS123;
    PushButtonSatWidgets[GEO][5] = ui->pushButtonS124;
    PushButtonSatWidgets[GEO][6] = ui->pushButtonS125;
    PushButtonSatWidgets[GEO][7] = ui->pushButtonS126;
    PushButtonSatWidgets[GEO][8] = ui->pushButtonS127;
    PushButtonSatWidgets[GEO][9] = ui->pushButtonS128;
    PushButtonSatWidgets[GEO][10] = ui->pushButtonS129;
    PushButtonSatWidgets[GEO][11] = ui->pushButtonS130;
    PushButtonSatWidgets[GEO][12] = ui->pushButtonS131;
    PushButtonSatWidgets[GEO][13] = ui->pushButtonS132;
    PushButtonSatWidgets[GEO][14] = ui->pushButtonS133;
    PushButtonSatWidgets[GEO][15] = ui->pushButtonS134;
    PushButtonSatWidgets[GEO][16] = ui->pushButtonS135;
    PushButtonSatWidgets[GEO][17] = ui->pushButtonS136;
    PushButtonSatWidgets[GEO][18] = ui->pushButtonS137;
    PushButtonSatWidgets[GEO][19] = ui->pushButtonS138;
    PushButtonSatWidgets[GEO][20] = ui->pushButtonS139;
    PushButtonSatWidgets[GEO][21] = ui->pushButtonS140;
    PushButtonSatWidgets[GEO][22] = ui->pushButtonS141;
    PushButtonSatWidgets[GEO][23] = ui->pushButtonS142;
    PushButtonSatWidgets[GEO][24] = ui->pushButtonS143;
    PushButtonSatWidgets[GEO][25] = ui->pushButtonS144;
    PushButtonSatWidgets[GEO][26] = ui->pushButtonS145;
    PushButtonSatWidgets[GEO][27] = ui->pushButtonS146;
    PushButtonSatWidgets[GEO][28] = ui->pushButtonS147;
    PushButtonSatWidgets[GEO][29] = ui->pushButtonS148;
    PushButtonSatWidgets[GEO][30] = ui->pushButtonS149;
    PushButtonSatWidgets[GEO][31] = ui->pushButtonS150;
    PushButtonSatWidgets[GEO][32] = ui->pushButtonS151;
    PushButtonSatWidgets[GEO][33] = ui->pushButtonS152;
    PushButtonSatWidgets[GEO][34] = ui->pushButtonS153;
    PushButtonSatWidgets[GEO][35] = ui->pushButtonS154;
    PushButtonSatWidgets[GEO][36] = ui->pushButtonS155;
    PushButtonSatWidgets[GEO][37] = ui->pushButtonS156;
    PushButtonSatWidgets[GEO][38] = ui->pushButtonS157;
    PushButtonSatWidgets[GEO][39] = ui->pushButtonS158;

    //BDS
    PushButtonConstWidgets[BDS] = ui->pushButtonBDSSelect;
    PushButtonSatWidgets[BDS][1] = ui->pushButtonC1;
    PushButtonSatWidgets[BDS][2] = ui->pushButtonC2;
    PushButtonSatWidgets[BDS][3] = ui->pushButtonC3;
    PushButtonSatWidgets[BDS][4] = ui->pushButtonC4;
    PushButtonSatWidgets[BDS][5] = ui->pushButtonC5;
    PushButtonSatWidgets[BDS][6] = ui->pushButtonC6;
    PushButtonSatWidgets[BDS][7] = ui->pushButtonC7;
    PushButtonSatWidgets[BDS][8] = ui->pushButtonC8;
    PushButtonSatWidgets[BDS][9] = ui->pushButtonC9;
    PushButtonSatWidgets[BDS][10] = ui->pushButtonC10;
    PushButtonSatWidgets[BDS][11] = ui->pushButtonC11;
    PushButtonSatWidgets[BDS][12] = ui->pushButtonC12;
    PushButtonSatWidgets[BDS][13] = ui->pushButtonC13;
    PushButtonSatWidgets[BDS][14] = ui->pushButtonC14;
    PushButtonSatWidgets[BDS][15] = ui->pushButtonC15;
    PushButtonSatWidgets[BDS][16] = ui->pushButtonC16;
    PushButtonSatWidgets[BDS][17] = ui->pushButtonC17;
    PushButtonSatWidgets[BDS][18] = ui->pushButtonC18;
    PushButtonSatWidgets[BDS][19] = ui->pushButtonC19;
    PushButtonSatWidgets[BDS][20] = ui->pushButtonC20;
    PushButtonSatWidgets[BDS][21] = ui->pushButtonC21;
    PushButtonSatWidgets[BDS][22] = ui->pushButtonC22;
    PushButtonSatWidgets[BDS][23] = ui->pushButtonC23;
    PushButtonSatWidgets[BDS][24] = ui->pushButtonC24;
    PushButtonSatWidgets[BDS][25] = ui->pushButtonC25;
    PushButtonSatWidgets[BDS][26] = ui->pushButtonC26;
    PushButtonSatWidgets[BDS][27] = ui->pushButtonC27;
    PushButtonSatWidgets[BDS][28] = ui->pushButtonC28;
    PushButtonSatWidgets[BDS][29] = ui->pushButtonC29;
    PushButtonSatWidgets[BDS][30] = ui->pushButtonC30;
    PushButtonSatWidgets[BDS][31] = ui->pushButtonC31;
    PushButtonSatWidgets[BDS][32] = ui->pushButtonC32;
    PushButtonSatWidgets[BDS][33] = ui->pushButtonC33;
    PushButtonSatWidgets[BDS][34] = ui->pushButtonC34;
    PushButtonSatWidgets[BDS][35] = ui->pushButtonC35;
    PushButtonSatWidgets[BDS][36] = ui->pushButtonC36;
    PushButtonSatWidgets[BDS][37] = ui->pushButtonC37;
    PushButtonSatWidgets[BDS][38] = ui->pushButtonC38;
    PushButtonSatWidgets[BDS][39] = ui->pushButtonC39;
    PushButtonSatWidgets[BDS][40] = ui->pushButtonC40;
    PushButtonSatWidgets[BDS][41] = ui->pushButtonC41;
    PushButtonSatWidgets[BDS][42] = ui->pushButtonC42;
    PushButtonSatWidgets[BDS][43] = ui->pushButtonC43;
    PushButtonSatWidgets[BDS][44] = ui->pushButtonC44;
    PushButtonSatWidgets[BDS][45] = ui->pushButtonC45;
    PushButtonSatWidgets[BDS][46] = ui->pushButtonC46;
    PushButtonSatWidgets[BDS][47] = ui->pushButtonC47;
    PushButtonSatWidgets[BDS][48] = ui->pushButtonC48;
    PushButtonSatWidgets[BDS][49] = ui->pushButtonC49;
    PushButtonSatWidgets[BDS][50] = ui->pushButtonC50;
    PushButtonSatWidgets[BDS][51] = ui->pushButtonC51;
    PushButtonSatWidgets[BDS][52] = ui->pushButtonC52;
    PushButtonSatWidgets[BDS][53] = ui->pushButtonC53;
    PushButtonSatWidgets[BDS][54] = ui->pushButtonC54;
    PushButtonSatWidgets[BDS][55] = ui->pushButtonC55;
    PushButtonSatWidgets[BDS][56] = ui->pushButtonC56;
    PushButtonSatWidgets[BDS][57] = ui->pushButtonC57;
    PushButtonSatWidgets[BDS][58] = ui->pushButtonC58;
    PushButtonSatWidgets[BDS][59] = ui->pushButtonC59;
    PushButtonSatWidgets[BDS][60] = ui->pushButtonC60;
    PushButtonSatWidgets[BDS][61] = ui->pushButtonC61;
    PushButtonSatWidgets[BDS][62] = ui->pushButtonC62;
    PushButtonSatWidgets[BDS][63] = ui->pushButtonC63;

    //QZSS
    PushButtonConstWidgets[QZSS] = ui->pushButtonQZSSSelect;
    PushButtonSatWidgets[QZSS][1] = ui->pushButtonJ1;
    PushButtonSatWidgets[QZSS][2] = ui->pushButtonJ2;
    PushButtonSatWidgets[QZSS][3] = ui->pushButtonJ3;
    PushButtonSatWidgets[QZSS][4] = ui->pushButtonJ4;
    PushButtonSatWidgets[QZSS][5] = ui->pushButtonJ5;
    PushButtonSatWidgets[QZSS][6] = ui->pushButtonJ6;
    PushButtonSatWidgets[QZSS][7] = ui->pushButtonJ7;
    PushButtonSatWidgets[QZSS][8] = ui->pushButtonJ8;
    PushButtonSatWidgets[QZSS][9] = ui->pushButtonJ9;
    PushButtonSatWidgets[QZSS][10] = ui->pushButtonJ10;

    //IRNSS
    PushButtonConstWidgets[IRNSS] = ui->pushButtonIRNSSSelect;
    PushButtonSatWidgets[IRNSS][1] = ui->pushButtonI1;
    PushButtonSatWidgets[IRNSS][2] = ui->pushButtonI2;
    PushButtonSatWidgets[IRNSS][3] = ui->pushButtonI3;
    PushButtonSatWidgets[IRNSS][4] = ui->pushButtonI4;
    PushButtonSatWidgets[IRNSS][5] = ui->pushButtonI5;
    PushButtonSatWidgets[IRNSS][6] = ui->pushButtonI6;
    PushButtonSatWidgets[IRNSS][7] = ui->pushButtonI7;
    PushButtonSatWidgets[IRNSS][8] = ui->pushButtonI8;
    PushButtonSatWidgets[IRNSS][9] = ui->pushButtonI9;
    PushButtonSatWidgets[IRNSS][10] = ui->pushButtonI10;
    PushButtonSatWidgets[IRNSS][11] = ui->pushButtonI11;
    PushButtonSatWidgets[IRNSS][12] = ui->pushButtonI12;
    PushButtonSatWidgets[IRNSS][13] = ui->pushButtonI13;
    PushButtonSatWidgets[IRNSS][14] = ui->pushButtonI14;

    //To be completed with further constellations
}

//Function to initialize pointers to CheckBox "clicked function" pointers
void gLAB_GUI::InitCheckBoxGNSSFuncPointers(){
    CheckBoxGNSSFunctions[GPS]=&gLAB_GUI::on_checkBoxGPS_clicked;
    CheckBoxGNSSFunctions[Galileo]=&gLAB_GUI::on_checkBoxGalileo_clicked;
    CheckBoxGNSSFunctions[GLONASS]=&gLAB_GUI::on_checkBoxGLONASS_clicked;
    CheckBoxGNSSFunctions[GEO]=&gLAB_GUI::on_checkBoxGEO_clicked;
    CheckBoxGNSSFunctions[BDS]=&gLAB_GUI::on_checkBoxBDS_clicked;
    CheckBoxGNSSFunctions[QZSS]=&gLAB_GUI::on_checkBoxQZSS_clicked;
    CheckBoxGNSSFunctions[IRNSS]=&gLAB_GUI::on_checkBoxIRNSS_clicked;
}

//Function to initialize pointers to CheckBox widget pointers
void gLAB_GUI::InitCheckBoxGNSSPointers(){
    CheckBoxGNSS[GPS]=ui->checkBoxGPS;
    CheckBoxGNSS[Galileo]=ui->checkBoxGalileo;
    CheckBoxGNSS[GLONASS]=ui->checkBoxGLONASS;
    CheckBoxGNSS[GEO]=ui->checkBoxGEO;
    CheckBoxGNSS[BDS]=ui->checkBoxBDS;
    CheckBoxGNSS[QZSS]=ui->checkBoxQZSS;
    CheckBoxGNSS[IRNSS]=ui->checkBoxIRNSS;

    //For reference GNSS clock
    CheckBoxGNSS4RefClock[0]=ui->checkBoxGPS;
    CheckBoxGNSS4RefClock[1]=ui->checkBoxGalileo;
    CheckBoxGNSS4RefClock[2]=ui->checkBoxGLONASS;
    CheckBoxGNSS4RefClock[3]=ui->checkBoxBDS;
    CheckBoxGNSS4RefClock[4]=ui->checkBoxQZSS;
    CheckBoxGNSS4RefClock[5]=ui->checkBoxIRNSS;
    CheckBoxGNSS4RefClock[6]=ui->checkBoxGEO;
}

// Function to show or hide the line edit for data decimator
void gLAB_GUI::on_checkBoxDataDecimator_clicked(bool checked) {
    ui->checkBoxDataDecimator->setChecked(checked);
    ui->frameDataDecimator->setHidden(!checked);
}

// Function to select GPS satellites
void gLAB_GUI::on_checkBoxGPS_clicked(bool checked){
    ui->checkBoxGPS->setChecked(checked);
    ui->pushButtonGPSSelect->setEnabled(checked);
    ui->tableWidgetNavMessageTypeGPS->setHidden(!checked);
    ui->tableWidgetNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->labelNavTypeGPS->setHidden(!checked);
    this->on_pushButtonGPSSelect_clicked();
    if (checked){
        on_pushButtonSatSelAll_clicked();
        if (ui->groupBoxSbas->isChecked()==false) ui->frameOptionButtonNavTypes->setHidden(false);
    } else {
        on_pushButtonSatSelNone_clicked();
        int numEnabled=0;
        for(int i=0;i<MAX_GNSS;i++) {
            if (CheckBoxGNSS[i]->isChecked()) numEnabled++;
        }
        if (numEnabled==0) ui->frameOptionButtonNavTypes->setHidden(true);
    }
    ui->frameBDSPRN->setHidden(true);
}
// Function to select Galileo satellites
void gLAB_GUI::on_checkBoxGalileo_clicked(bool checked){
    ui->checkBoxGalileo->setChecked(checked);
    ui->pushButtonGalileoSelect->setEnabled(checked);
    ui->tableWidgetNavMessageTypeGalileo->setHidden(!checked);
    ui->tableWidgetNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->labelNavTypeGalileo->setHidden(!checked);
    this->on_pushButtonGalileoSelect_clicked();
    if (checked){
        on_pushButtonSatSelAll_clicked();
        if (ui->groupBoxSbas->isChecked()==false) ui->frameOptionButtonNavTypes->setHidden(false);
    } else {
        on_pushButtonSatSelNone_clicked();
        int numEnabled=0;
        for(int i=0;i<MAX_GNSS;i++) {
            if (CheckBoxGNSS[i]->isChecked()) numEnabled++;
        }
        if (numEnabled==0) ui->frameOptionButtonNavTypes->setHidden(true);
    }
    ui->frameBDSPRN->setHidden(true);
}
// Function to select GLONASS satellites
void gLAB_GUI::on_checkBoxGLONASS_clicked(bool checked){
    ui->checkBoxGLONASS->setChecked(checked);
    ui->pushButtonGLONASSSelect->setEnabled(checked);
    ui->tableWidgetNavMessageTypeGLONASS->setHidden(!checked);
    ui->tableWidgetNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->labelNavTypeGLONASS->setHidden(!checked);
    this->on_pushButtonGLONASSSelect_clicked();
    if (checked){
        on_pushButtonSatSelAll_clicked();
        if (ui->groupBoxSbas->isChecked()==false) ui->frameOptionButtonNavTypes->setHidden(false);
    } else {
        on_pushButtonSatSelNone_clicked();
        int numEnabled=0;
        for(int i=0;i<MAX_GNSS;i++) {
            if (CheckBoxGNSS[i]->isChecked()) numEnabled++;
        }
        if (numEnabled==0) ui->frameOptionButtonNavTypes->setHidden(true);
    }
    ui->frameBDSPRN->setHidden(true);
}
// Function to select GEO satellites
void gLAB_GUI::on_checkBoxGEO_clicked(bool checked){
    ui->checkBoxGEO->setChecked(checked);
    ui->pushButtonGEOSelect->setEnabled(checked);
    ui->tableWidgetNavMessageTypeGEO->setHidden(!checked);
    ui->tableWidgetNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->labelNavTypeGEO->setHidden(!checked);
    this->on_pushButtonGEOSelect_clicked();
    if (checked){
        on_pushButtonSatSelAll_clicked();
        if (ui->groupBoxSbas->isChecked()==false) ui->frameOptionButtonNavTypes->setHidden(false);
    } else {
        on_pushButtonSatSelNone_clicked();
        int numEnabled=0;
        for(int i=0;i<MAX_GNSS;i++) {
            if (CheckBoxGNSS[i]->isChecked()) numEnabled++;
        }
        if (numEnabled==0) ui->frameOptionButtonNavTypes->setHidden(true);
    }
    ui->frameBDSPRN->setHidden(true);
}
// Function to select BDS satellites
void gLAB_GUI::on_checkBoxBDS_clicked(bool checked){
    ui->frameBDSPRN->setHidden(false);
    ui->checkBoxBDS->setChecked(checked);
    ui->pushButtonBDSSelect->setEnabled(checked);
    ui->tableWidgetNavMessageTypeBDS->setHidden(!checked);
    ui->tableWidgetNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->labelNavTypeBDS->setHidden(!checked);
    this->on_pushButtonBDSSelect_clicked();
    if (checked){
        on_pushButtonSatSelAll_clicked();
        if (ui->groupBoxSbas->isChecked()==false) ui->frameOptionButtonNavTypes->setHidden(false);
    } else {
        on_pushButtonSatSelNone_clicked();
        int numEnabled=0;
        for(int i=0;i<MAX_GNSS;i++) {
            if (CheckBoxGNSS[i]->isChecked()) numEnabled++;
        }
        if (numEnabled==0) ui->frameOptionButtonNavTypes->setHidden(true);
    }
}
// Function to select QZSS satellites
void gLAB_GUI::on_checkBoxQZSS_clicked(bool checked){
    ui->checkBoxQZSS->setChecked(checked);
    ui->pushButtonQZSSSelect->setEnabled(checked);
    ui->tableWidgetNavMessageTypeQZSS->setHidden(!checked);
    ui->tableWidgetNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->labelNavTypeQZSS->setHidden(!checked);
    this->on_pushButtonQZSSSelect_clicked();
    if (checked){
        on_pushButtonSatSelAll_clicked();
        if (ui->groupBoxSbas->isChecked()==false) ui->frameOptionButtonNavTypes->setHidden(false);
    } else {
        on_pushButtonSatSelNone_clicked();
        int numEnabled=0;
        for(int i=0;i<MAX_GNSS;i++) {
            if (CheckBoxGNSS[i]->isChecked()) numEnabled++;
        }
        if (numEnabled==0) ui->frameOptionButtonNavTypes->setHidden(true);
    }
    ui->frameBDSPRN->setHidden(true);
}
// Function to select IRNSS satellites
void gLAB_GUI::on_checkBoxIRNSS_clicked(bool checked){
    ui->checkBoxIRNSS->setChecked(checked);
    ui->pushButtonIRNSSSelect->setEnabled(checked);
    ui->tableWidgetNavMessageTypeIRNSS->setHidden(!checked);
    ui->tableWidgetNavMessageTypeIRNSS->setCurrentItem(nullptr);
    ui->labelNavTypeIRNSS->setHidden(!checked);
    this->on_pushButtonIRNSSSelect_clicked();
    if (checked){
        on_pushButtonSatSelAll_clicked();
        if (ui->groupBoxSbas->isChecked()==false) ui->frameOptionButtonNavTypes->setHidden(false);
    } else {
        on_pushButtonSatSelNone_clicked();
        int numEnabled=0;
        for(int i=0;i<MAX_GNSS;i++) {
            if (CheckBoxGNSS[i]->isChecked()) numEnabled++;
        }
        if (numEnabled==0) ui->frameOptionButtonNavTypes->setHidden(true);
    }
    ui->frameBDSPRN->setHidden(true);
}
// Function to select GPS constellation when the only one satellite was selected for GPS
void gLAB_GUI::checkBoxGPS_ForOneSat(){
    ui->checkBoxGPS->setChecked(true);
    ui->stackedWidgetPRNButtons->setCurrentIndex(GPS);
    ui->pushButtonGPSSelect->setEnabled(true);
    ui->pushButtonGPSMeasurements->setEnabled(true);
    ui->frameOptionButtonNavTypes->setHidden(false);
    ui->tableWidgetNavMessageTypeGPS->setHidden(false);
    ui->labelNavTypeGPS->setHidden(false);
    this->on_pushButtonGPSMeasurements_clicked();
    this->FreqMeasGNSS->changePushButtonGPS(true);
    this->FreqMeasGNSS->on_pushButtonPublicGPS_clicked();
    this->MeasSelectGNSS->changePushButtonGPS(true);
    this->MeasSelectGNSS->on_pushButtonPublicGPS_clicked();
    this->doubleClick_RefGNSSClock(1,"GPS");
    this->select_ISCBGNSS(1,"GPS");
    this->SnrAdvancedMinWin->changePushButtonGPS(true);
    this->SnrAdvancedMinWin->on_pushButtonPublicGPS_clicked();
    this->SnrAdvancedMaxWin->changePushButtonGPS(true);
    this->SnrAdvancedMaxWin->on_pushButtonPublicGPS_clicked();
    this->CSAdvancedSF->changePushButtonGPS(true);
    this->CSAdvancedSF->on_pushButtonPublicGPS_clicked();
    this->CSAdvancedMW->changePushButtonGPS(true);
    this->CSAdvancedMW->on_pushButtonPublicGPS_clicked();
    this->CSAdvancedLI->changePushButtonGPS(true);
    this->CSAdvancedLI->on_pushButtonPublicGPS_clicked();
    this->CSAdvancedIGF->changePushButtonGPS(true);
    this->CSAdvancedIGF->on_pushButtonPublicGPS_clicked();
    this->APCAdvanced->changePushButtonGPS(true);
    this->APCAdvanced->on_pushButtonPublicGPS_clicked();
    this->SBASOBADSet->setGPS(true);
    ui->labelSelectPRNFor->setText("GPS:");
}
// Function to select Galileo constellation when the only one satellite was selected for Galileo
void gLAB_GUI::checkBoxGalileo_ForOneSat(){
    ui->checkBoxGalileo->setChecked(true);
    ui->stackedWidgetPRNButtons->setCurrentIndex(Galileo);
    ui->pushButtonGalileoSelect->setEnabled(true);
    ui->pushButtonGalileoMeasurements->setEnabled(true);
    ui->frameOptionButtonNavTypes->setHidden(false);
    ui->tableWidgetNavMessageTypeGalileo->setHidden(false);
    ui->labelNavTypeGalileo->setHidden(false);
    this->on_pushButtonGalileoMeasurements_clicked();
    this->FreqMeasGNSS->changePushButtonGalileo(true);
    this->FreqMeasGNSS->on_pushButtonPublicGalileo_clicked();
    this->MeasSelectGNSS->changePushButtonGalileo(true);
    this->MeasSelectGNSS->on_pushButtonPublicGalileo_clicked();
    this->doubleClick_RefGNSSClock(1,"Galileo");
    this->select_ISCBGNSS(1,"Galileo");
    this->SnrAdvancedMinWin->changePushButtonGalileo(true);
    this->SnrAdvancedMinWin->on_pushButtonPublicGalileo_clicked();
    this->SnrAdvancedMaxWin->changePushButtonGalileo(true);
    this->SnrAdvancedMaxWin->on_pushButtonPublicGalileo_clicked();
    this->CSAdvancedSF->changePushButtonGalileo(true);
    this->CSAdvancedSF->on_pushButtonPublicGalileo_clicked();
    this->CSAdvancedMW->changePushButtonGalileo(true);
    this->CSAdvancedMW->on_pushButtonPublicGalileo_clicked();
    this->CSAdvancedLI->changePushButtonGalileo(true);
    this->CSAdvancedLI->on_pushButtonPublicGalileo_clicked();
    this->CSAdvancedIGF->changePushButtonGalileo(true);
    this->CSAdvancedIGF->on_pushButtonPublicGalileo_clicked();
    this->APCAdvanced->changePushButtonGalileo(true);
    this->APCAdvanced->on_pushButtonPublicGalileo_clicked();
    this->SBASOBADSet->setGalileo(true);
    ui->labelSelectPRNFor->setText("Galileo:");
}
// Function to select GLONASS constellation when the only one satellite was selected for GLONASS
void gLAB_GUI::checkBoxGLONASS_ForOneSat(){
    ui->checkBoxRinexNavFileGLO1->setHidden(false);
    if (ui->checkBoxRinexNavFileGLO1->isChecked()==true) {
        ui->lineEditRinexNavFileGLO1->setHidden(false);
        ui->pushButtonRinexNavFileGLO1->setHidden(false);
    }
    ui->checkBoxRinexNavFileGLO2->setHidden(false);
    if (ui->checkBoxRinexNavFileGLO2->isChecked()==true) {
        ui->lineEditRinexNavFileGLO2->setHidden(false);
        ui->pushButtonRinexNavFileGLO2->setHidden(false);
    }
    ui->checkBoxGLONASS->setChecked(true);
    ui->stackedWidgetPRNButtons->setCurrentIndex(GLONASS);
    ui->pushButtonGLONASSSelect->setEnabled(true);
    ui->pushButtonGLONASSMeasurements->setEnabled(true);
    ui->frameOptionButtonNavTypes->setHidden(false);
    ui->tableWidgetNavMessageTypeGLONASS->setHidden(false);
    ui->labelNavTypeGLONASS->setHidden(false);
    this->on_pushButtonGLONASSMeasurements_clicked();
    this->FreqMeasGNSS->changePushButtonGLONASS(true);
    this->FreqMeasGNSS->on_pushButtonPublicGLONASS_clicked();
    this->MeasSelectGNSS->changePushButtonGLONASS(true);
    this->MeasSelectGNSS->on_pushButtonPublicGLONASS_clicked();
    this->doubleClick_RefGNSSClock(1,"GLONASS");
    this->select_ISCBGNSS(1,"GLONASS");
    this->SnrAdvancedMinWin->changePushButtonGLONASS(true);
    this->SnrAdvancedMinWin->on_pushButtonPublicGLONASS_clicked();
    this->SnrAdvancedMaxWin->changePushButtonGLONASS(true);
    this->SnrAdvancedMaxWin->on_pushButtonPublicGLONASS_clicked();
    this->CSAdvancedSF->changePushButtonGLONASS(true);
    this->CSAdvancedSF->on_pushButtonPublicGLONASS_clicked();
    this->CSAdvancedMW->changePushButtonGLONASS(true);
    this->CSAdvancedMW->on_pushButtonPublicGLONASS_clicked();
    this->CSAdvancedLI->changePushButtonGLONASS(true);
    this->CSAdvancedLI->on_pushButtonPublicGLONASS_clicked();
    this->CSAdvancedIGF->changePushButtonGLONASS(true);
    this->CSAdvancedIGF->on_pushButtonPublicGLONASS_clicked();
    this->APCAdvanced->changePushButtonGLONASS(true);
    this->APCAdvanced->on_pushButtonPublicGLONASS_clicked();
    this->SBASOBADSet->setGLONASS(true);
    ui->labelSelectPRNFor->setText("GLONASS:");
}
// Function to select GEO constellation when the only one satellite was selected for GEO
void gLAB_GUI::checkBoxGEO_ForOneSat(){
    ui->checkBoxGEO->setChecked(true);
    ui->stackedWidgetPRNButtons->setCurrentIndex(GEO);
    ui->pushButtonGEOSelect->setEnabled(true);
    ui->pushButtonGEOMeasurements->setEnabled(true);
    ui->frameOptionButtonNavTypes->setHidden(false);
    ui->tableWidgetNavMessageTypeGEO->setHidden(false);
    ui->labelNavTypeGEO->setHidden(false);
    this->on_pushButtonGEOMeasurements_clicked();
    this->FreqMeasGNSS->changePushButtonGEO(true);
    this->FreqMeasGNSS->on_pushButtonPublicGEO_clicked();
    this->MeasSelectGNSS->changePushButtonGEO(true);
    this->MeasSelectGNSS->on_pushButtonPublicGEO_clicked();
    this->doubleClick_RefGNSSClock(1,"GEO");
    this->select_ISCBGNSS(1,"GEO");
    this->SnrAdvancedMinWin->changePushButtonGEO(true);
    this->SnrAdvancedMinWin->on_pushButtonPublicGEO_clicked();
    this->SnrAdvancedMaxWin->changePushButtonGEO(true);
    this->SnrAdvancedMaxWin->on_pushButtonPublicGEO_clicked();
    this->CSAdvancedSF->changePushButtonGEO(true);
    this->CSAdvancedSF->on_pushButtonPublicGEO_clicked();
    this->CSAdvancedMW->changePushButtonGEO(true);
    this->CSAdvancedMW->on_pushButtonPublicGEO_clicked();
    this->CSAdvancedLI->changePushButtonGEO(true);
    this->CSAdvancedLI->on_pushButtonPublicGEO_clicked();
    //this->CSAdvancedIGF->changePushButtonGEO(true); //GEO does not have triple frequency, it cannot use IGF
    //this->CSAdvancedIGF->on_pushButtonPublicGEO_clicked(); //GEO does not have triple frequency, it cannot use IGF
    this->APCAdvanced->changePushButtonGEO(true);
    this->APCAdvanced->on_pushButtonPublicGEO_clicked();
    this->SBASOBADSet->setGEO(true);
    ui->labelSelectPRNFor->setText("GEO:");
}
// Function to select BDS constellation when the only one satellite was selected for BDS
void gLAB_GUI::checkBoxBDS_ForOneSat(){
    ui->checkBoxBDS->setChecked(true);
    ui->stackedWidgetPRNButtons->setCurrentIndex(BDS);
    ui->pushButtonBDSSelect->setEnabled(true);
    ui->pushButtonBDSMeasurements->setEnabled(true);
    ui->frameOptionButtonNavTypes->setHidden(false);
    ui->tableWidgetNavMessageTypeBDS->setHidden(false);
    ui->labelNavTypeBDS->setHidden(false);
    this->on_pushButtonBDSMeasurements_clicked();
    this->FreqMeasGNSS->changePushButtonBDS(true);
    this->FreqMeasGNSS->on_pushButtonPublicBDS_clicked();
    this->MeasSelectGNSS->changePushButtonBDS(true);
    this->MeasSelectGNSS->on_pushButtonPublicBDS_clicked();
    this->doubleClick_RefGNSSClock(1,"BDS");
    this->select_ISCBGNSS(1,"BDS");
    this->SnrAdvancedMinWin->changePushButtonBDS(true);
    this->SnrAdvancedMinWin->on_pushButtonPublicBDS_clicked();
    this->SnrAdvancedMaxWin->changePushButtonBDS(true);
    this->SnrAdvancedMaxWin->on_pushButtonPublicBDS_clicked();
    this->CSAdvancedSF->changePushButtonBDS(true);
    this->CSAdvancedSF->on_pushButtonPublicBDS_clicked();
    this->CSAdvancedMW->changePushButtonBDS(true);
    this->CSAdvancedMW->on_pushButtonPublicBDS_clicked();
    this->CSAdvancedLI->changePushButtonBDS(true);
    this->CSAdvancedLI->on_pushButtonPublicBDS_clicked();
    this->CSAdvancedIGF->changePushButtonBDS(true);
    this->CSAdvancedIGF->on_pushButtonPublicBDS_clicked();
    this->APCAdvanced->changePushButtonBDS(true);
    this->APCAdvanced->on_pushButtonPublicBDS_clicked();
    this->SBASOBADSet->setBDS(true);
    ui->labelSelectPRNFor->setText("BDS:");
}
// Function to select QZSS constellation when the only one satellite was selected for QZSS
void gLAB_GUI::checkBoxQZSS_ForOneSat(){
    ui->checkBoxQZSS->setChecked(true);
    ui->stackedWidgetPRNButtons->setCurrentIndex(QZSS);
    ui->pushButtonQZSSSelect->setEnabled(true);
    ui->pushButtonQZSSMeasurements->setEnabled(true);
    ui->frameOptionButtonNavTypes->setHidden(false);
    ui->tableWidgetNavMessageTypeQZSS->setHidden(false);
    ui->labelNavTypeQZSS->setHidden(false);
    this->on_pushButtonQZSSMeasurements_clicked();
    this->FreqMeasGNSS->changePushButtonQZSS(true);
    this->FreqMeasGNSS->on_pushButtonPublicQZSS_clicked();
    this->MeasSelectGNSS->changePushButtonQZSS(true);
    this->MeasSelectGNSS->on_pushButtonPublicQZSS_clicked();
    this->doubleClick_RefGNSSClock(1,"QZSS");
    this->select_ISCBGNSS(1,"QZSS");
    this->SnrAdvancedMinWin->changePushButtonQZSS(true);
    this->SnrAdvancedMinWin->on_pushButtonPublicQZSS_clicked();
    this->SnrAdvancedMaxWin->changePushButtonQZSS(true);
    this->SnrAdvancedMaxWin->on_pushButtonPublicQZSS_clicked();
    this->CSAdvancedSF->changePushButtonQZSS(true);
    this->CSAdvancedSF->on_pushButtonPublicQZSS_clicked();
    this->CSAdvancedMW->changePushButtonQZSS(true);
    this->CSAdvancedMW->on_pushButtonPublicQZSS_clicked();
    this->CSAdvancedLI->changePushButtonQZSS(true);
    this->CSAdvancedLI->on_pushButtonPublicQZSS_clicked();
    this->CSAdvancedIGF->changePushButtonQZSS(true);
    this->CSAdvancedIGF->on_pushButtonPublicQZSS_clicked();
    this->APCAdvanced->changePushButtonQZSS(true);
    this->APCAdvanced->on_pushButtonPublicQZSS_clicked();
    this->SBASOBADSet->setQZSS(true);
    ui->labelSelectPRNFor->setText("QZSS:");
}
// Function to select IRNSS constellation when the only one satellite was selected for IRNSS
void gLAB_GUI::checkBoxIRNSS_ForOneSat(){
    ui->checkBoxIRNSS->setChecked(true);
    ui->stackedWidgetPRNButtons->setCurrentIndex(IRNSS);
    ui->pushButtonIRNSSSelect->setEnabled(true);
    ui->pushButtonIRNSSMeasurements->setEnabled(true);
    ui->frameOptionButtonNavTypes->setHidden(false);
    ui->tableWidgetNavMessageTypeIRNSS->setHidden(false);
    ui->labelNavTypeIRNSS->setHidden(false);
    this->on_pushButtonIRNSSMeasurements_clicked();
    this->FreqMeasGNSS->changePushButtonIRNSS(true);
    this->FreqMeasGNSS->on_pushButtonPublicIRNSS_clicked();
    this->MeasSelectGNSS->changePushButtonIRNSS(true);
    this->MeasSelectGNSS->on_pushButtonPublicIRNSS_clicked();
    this->doubleClick_RefGNSSClock(1,"IRNSS");
    this->select_ISCBGNSS(1,"IRNSS");
    this->SnrAdvancedMinWin->changePushButtonIRNSS(true);
    this->SnrAdvancedMinWin->on_pushButtonPublicIRNSS_clicked();
    this->SnrAdvancedMaxWin->changePushButtonIRNSS(true);
    this->SnrAdvancedMaxWin->on_pushButtonPublicIRNSS_clicked();
    this->CSAdvancedSF->changePushButtonIRNSS(true);
    this->CSAdvancedSF->on_pushButtonPublicIRNSS_clicked();
    this->CSAdvancedMW->changePushButtonIRNSS(true);
    this->CSAdvancedMW->on_pushButtonPublicIRNSS_clicked();
    this->CSAdvancedLI->changePushButtonIRNSS(true);
    this->CSAdvancedLI->on_pushButtonPublicIRNSS_clicked();
    //this->CSAdvancedIGF->changePushButtonIRNSS(true); //IRNSS does not have triple frequency, it cannot use IGF
    //this->CSAdvancedIGF->on_pushButtonPublicIRNSS_clicked(); //IRNSS does not have triple frequency, it cannot use IGF
    this->APCAdvanced->changePushButtonIRNSS(true);
    this->APCAdvanced->on_pushButtonPublicIRNSS_clicked();
    this->SBASOBADSet->setIRNSS(true);
    ui->labelSelectPRNFor->setText("IRNSS:");
}
void gLAB_GUI::on_pushButtonGPSSelect_clicked(){
    ui->pushButtonGPSSelect->setChecked(true);
    ui->stackedWidgetPRNButtons->setCurrentIndex(GPS);
    ui->labelSelectPRNFor->setText("GPS:");
    ui->pushButtonGalileoSelect->setChecked(false);
    ui->pushButtonGLONASSSelect->setChecked(false);
    ui->pushButtonGEOSelect->setChecked(false);
    ui->pushButtonBDSSelect->setChecked(false);
    ui->pushButtonQZSSSelect->setChecked(false);
    ui->pushButtonIRNSSSelect->setChecked(false);
    ui->frameBDSPRN->setHidden(true);
}
void gLAB_GUI::on_pushButtonGalileoSelect_clicked(){
    ui->pushButtonGalileoSelect->setChecked(true);
    ui->stackedWidgetPRNButtons->setCurrentIndex(Galileo);
    ui->labelSelectPRNFor->setText("Galileo:");
    ui->pushButtonGPSSelect->setChecked(false);
    ui->pushButtonGLONASSSelect->setChecked(false);
    ui->pushButtonGEOSelect->setChecked(false);
    ui->pushButtonBDSSelect->setChecked(false);
    ui->pushButtonQZSSSelect->setChecked(false);
    ui->pushButtonIRNSSSelect->setChecked(false);
    ui->frameBDSPRN->setHidden(true);
}
void gLAB_GUI::on_pushButtonGLONASSSelect_clicked(){
    ui->pushButtonGLONASSSelect->setChecked(true);
    ui->stackedWidgetPRNButtons->setCurrentIndex(GLONASS);
    ui->labelSelectPRNFor->setText("GLONASS:");
    ui->pushButtonGPSSelect->setChecked(false);
    ui->pushButtonGalileoSelect->setChecked(false);
    ui->pushButtonGEOSelect->setChecked(false);
    ui->pushButtonBDSSelect->setChecked(false);
    ui->pushButtonQZSSSelect->setChecked(false);
    ui->pushButtonIRNSSSelect->setChecked(false);
    ui->frameBDSPRN->setHidden(true);
}
void gLAB_GUI::on_pushButtonGEOSelect_clicked(){
    ui->pushButtonGEOSelect->setChecked(true);
    ui->stackedWidgetPRNButtons->setCurrentIndex(GEO);
    ui->labelSelectPRNFor->setText("GEO:");
    ui->pushButtonGPSSelect->setChecked(false);
    ui->pushButtonGalileoSelect->setChecked(false);
    ui->pushButtonGLONASSSelect->setChecked(false);
    ui->pushButtonBDSSelect->setChecked(false);
    ui->pushButtonQZSSSelect->setChecked(false);
    ui->pushButtonIRNSSSelect->setChecked(false);
    ui->frameBDSPRN->setHidden(true);
}
void gLAB_GUI::on_pushButtonBDSSelect_clicked(){
    ui->pushButtonBDSSelect->setChecked(true);
    ui->stackedWidgetPRNButtons->setCurrentIndex(BDS);
    ui->labelSelectPRNFor->setText("BDS:");
    ui->pushButtonGPSSelect->setChecked(false);
    ui->pushButtonGalileoSelect->setChecked(false);
    ui->pushButtonGLONASSSelect->setChecked(false);
    ui->pushButtonGEOSelect->setChecked(false);
    ui->pushButtonQZSSSelect->setChecked(false);
    ui->pushButtonIRNSSSelect->setChecked(false);
    ui->frameBDSPRN->setHidden(false);
}
void gLAB_GUI::on_pushButtonQZSSSelect_clicked(){
    ui->pushButtonQZSSSelect->setChecked(true);
    ui->stackedWidgetPRNButtons->setCurrentIndex(QZSS);
    ui->labelSelectPRNFor->setText("QZSS:");
    ui->pushButtonGPSSelect->setChecked(false);
    ui->pushButtonGalileoSelect->setChecked(false);
    ui->pushButtonGLONASSSelect->setChecked(false);
    ui->pushButtonGEOSelect->setChecked(false);
    ui->pushButtonBDSSelect->setChecked(false);
    ui->pushButtonIRNSSSelect->setChecked(false);
    ui->frameBDSPRN->setHidden(true);
}
void gLAB_GUI::on_pushButtonIRNSSSelect_clicked(){
    ui->pushButtonIRNSSSelect->setChecked(true);
    ui->stackedWidgetPRNButtons->setCurrentIndex(IRNSS);
    ui->labelSelectPRNFor->setText("IRNSS:");
    ui->pushButtonGPSSelect->setChecked(false);
    ui->pushButtonGalileoSelect->setChecked(false);
    ui->pushButtonGLONASSSelect->setChecked(false);
    ui->pushButtonGEOSelect->setChecked(false);
    ui->pushButtonBDSSelect->setChecked(false);
    ui->pushButtonQZSSSelect->setChecked(false);
    ui->frameBDSPRN->setHidden(true);
}

// Function to set all GPS satellites available
void gLAB_GUI::on_pushButtonSatSelAll_clicked() {
    int i,nowGnss=ui->stackedWidgetPRNButtons->currentIndex();
    if (nowGnss==GPS){
        ui->checkBoxGPS->setChecked(true);
        ui->pushButtonGPSSelect->setEnabled(true);
        //Measurements
        ui->pushButtonGPSMeasurements->setEnabled(true);
        this->on_pushButtonGPSMeasurements_clicked();
        this->FreqMeasGNSS->changePushButtonGPS(true);
        this->FreqMeasGNSS->on_pushButtonPublicGPS_clicked();
        this->MeasSelectGNSS->changePushButtonGPS(true);
        this->MeasSelectGNSS->on_pushButtonPublicGPS_clicked();
        this->doubleClick_RefGNSSClock(1,"GPS");
        this->select_ISCBGNSS(1,"GPS");
        this->SnrAdvancedMinWin->changePushButtonGPS(true);
        this->SnrAdvancedMinWin->on_pushButtonPublicGPS_clicked();
        this->SnrAdvancedMaxWin->changePushButtonGPS(true);
        this->SnrAdvancedMaxWin->on_pushButtonPublicGPS_clicked();
        this->CSAdvancedSF->changePushButtonGPS(true);
        this->CSAdvancedSF->on_pushButtonPublicGPS_clicked();
        this->CSAdvancedMW->changePushButtonGPS(true);
        this->CSAdvancedMW->on_pushButtonPublicGPS_clicked();
        this->CSAdvancedLI->changePushButtonGPS(true);
        this->CSAdvancedLI->on_pushButtonPublicGPS_clicked();
        this->CSAdvancedIGF->changePushButtonGPS(true);
        this->CSAdvancedIGF->on_pushButtonPublicGPS_clicked();
        this->APCAdvanced->changePushButtonGPS(true);
        this->APCAdvanced->on_pushButtonPublicGPS_clicked();
        this->SBASOBADSet->setGPS(true);
        for(i=1;i<=MAX_SAT_GPS;i++) {
            PushButtonSatWidgets[GPS][i]->setStyleSheet(QString("background-color:%1; color:black;").arg(GreenColor));
        }
    }
    if (nowGnss==Galileo){
        ui->checkBoxGalileo->setChecked(true);
        ui->pushButtonGalileoSelect->setEnabled(true);
        //Measurements
        ui->pushButtonGalileoMeasurements->setEnabled(true);
        this->on_pushButtonGalileoMeasurements_clicked();
        this->FreqMeasGNSS->changePushButtonGalileo(true);
        this->FreqMeasGNSS->on_pushButtonPublicGalileo_clicked();
        this->MeasSelectGNSS->changePushButtonGalileo(true);
        this->MeasSelectGNSS->on_pushButtonPublicGalileo_clicked();
        this->doubleClick_RefGNSSClock(1,"Galileo");
        this->select_ISCBGNSS(1,"Galileo");
        this->SnrAdvancedMinWin->changePushButtonGalileo(true);
        this->SnrAdvancedMinWin->on_pushButtonPublicGalileo_clicked();
        this->SnrAdvancedMaxWin->changePushButtonGalileo(true);
        this->SnrAdvancedMaxWin->on_pushButtonPublicGalileo_clicked();
        this->CSAdvancedSF->changePushButtonGalileo(true);
        this->CSAdvancedSF->on_pushButtonPublicGalileo_clicked();
        this->CSAdvancedMW->changePushButtonGalileo(true);
        this->CSAdvancedMW->on_pushButtonPublicGalileo_clicked();
        this->CSAdvancedLI->changePushButtonGalileo(true);
        this->CSAdvancedLI->on_pushButtonPublicGalileo_clicked();
        this->CSAdvancedIGF->changePushButtonGalileo(true);
        this->CSAdvancedIGF->on_pushButtonPublicGalileo_clicked();
        this->APCAdvanced->changePushButtonGalileo(true);
        this->APCAdvanced->on_pushButtonPublicGalileo_clicked();
        this->SBASOBADSet->setGalileo(true);
        for(i=1;i<=MAX_SAT_GAL;i++) {
            PushButtonSatWidgets[Galileo][i]->setStyleSheet(QString("background-color:%1; color:black;").arg(GreenColor));
        }
    }
    if (nowGnss==GLONASS){
        ui->checkBoxRinexNavFileGLO1->setHidden(false);
        if (ui->checkBoxRinexNavFileGLO1->isChecked()==true) {
            ui->lineEditRinexNavFileGLO1->setHidden(false);
            ui->pushButtonRinexNavFileGLO1->setHidden(false);
        }
        ui->checkBoxRinexNavFileGLO2->setHidden(false);
        if (ui->checkBoxRinexNavFileGLO1->isChecked()==true) {
            ui->lineEditRinexNavFileGLO2->setHidden(false);
            ui->pushButtonRinexNavFileGLO2->setHidden(false);
        }
        ui->checkBoxGLONASS->setChecked(true);
        ui->pushButtonGLONASSSelect->setEnabled(true);
        //Measurements
        ui->pushButtonGLONASSMeasurements->setEnabled(true);
        this->on_pushButtonGLONASSMeasurements_clicked();
        this->FreqMeasGNSS->changePushButtonGLONASS(true);
        this->FreqMeasGNSS->on_pushButtonPublicGLONASS_clicked();
        this->MeasSelectGNSS->changePushButtonGLONASS(true);
        this->MeasSelectGNSS->on_pushButtonPublicGLONASS_clicked();
        this->doubleClick_RefGNSSClock(1,"GLONASS");
        this->select_ISCBGNSS(1,"GLONASS");
        this->SnrAdvancedMinWin->changePushButtonGLONASS(true);
        this->SnrAdvancedMinWin->on_pushButtonPublicGLONASS_clicked();
        this->SnrAdvancedMaxWin->changePushButtonGLONASS(true);
        this->SnrAdvancedMaxWin->on_pushButtonPublicGLONASS_clicked();
        this->CSAdvancedSF->changePushButtonGLONASS(true);
        this->CSAdvancedSF->on_pushButtonPublicGLONASS_clicked();
        this->CSAdvancedMW->changePushButtonGLONASS(true);
        this->CSAdvancedMW->on_pushButtonPublicGLONASS_clicked();
        this->CSAdvancedLI->changePushButtonGLONASS(true);
        this->CSAdvancedLI->on_pushButtonPublicGLONASS_clicked();
        this->CSAdvancedIGF->changePushButtonGLONASS(true);
        this->CSAdvancedIGF->on_pushButtonPublicGLONASS_clicked();
        this->APCAdvanced->changePushButtonGLONASS(true);
        this->APCAdvanced->on_pushButtonPublicGLONASS_clicked();
        this->SBASOBADSet->setGLONASS(true);
        for(i=1;i<=MAX_SAT_GLO;i++) {
            PushButtonSatWidgets[GLONASS][i]->setStyleSheet(QString("background-color:%1; color:black;").arg(GreenColor));
        }
    }
    if (nowGnss==GEO){
        ui->checkBoxGEO->setChecked(true);
        ui->pushButtonGEOSelect->setEnabled(true);
        //Measurements
        ui->pushButtonGEOMeasurements->setEnabled(true);
        this->on_pushButtonGEOMeasurements_clicked();
        this->FreqMeasGNSS->changePushButtonGEO(true);
        this->FreqMeasGNSS->on_pushButtonPublicGEO_clicked();
        this->MeasSelectGNSS->changePushButtonGEO(true);
        this->MeasSelectGNSS->on_pushButtonPublicGEO_clicked();
        this->doubleClick_RefGNSSClock(1,"GEO");
        this->select_ISCBGNSS(1,"GEO");
        this->SnrAdvancedMinWin->changePushButtonGEO(true);
        this->SnrAdvancedMinWin->on_pushButtonPublicGEO_clicked();
        this->SnrAdvancedMaxWin->changePushButtonGEO(true);
        this->SnrAdvancedMaxWin->on_pushButtonPublicGEO_clicked();
        this->CSAdvancedSF->changePushButtonGEO(true);
        this->CSAdvancedSF->on_pushButtonPublicGEO_clicked();
        this->CSAdvancedMW->changePushButtonGEO(true);
        this->CSAdvancedMW->on_pushButtonPublicGEO_clicked();
        this->CSAdvancedLI->changePushButtonGEO(true);
        this->CSAdvancedLI->on_pushButtonPublicGEO_clicked();
        //this->CSAdvancedIGF->changePushButtonGEO(true); //GEO does not have triple frequency, it cannot use IGF
        //this->CSAdvancedIGF->on_pushButtonPublicGEO_clicked(); //GEO does not have triple frequency, it cannot use IGF
        this->APCAdvanced->changePushButtonGEO(true);
        this->APCAdvanced->on_pushButtonPublicGEO_clicked();
        this->SBASOBADSet->setGEO(true);
        for(i=1;i<=MAX_SAT_GEO;i++) {
            PushButtonSatWidgets[GEO][i]->setStyleSheet(QString("background-color:%1; color:black;").arg(GreenColor));
        }
    }
    if (nowGnss==BDS){
        ui->checkBoxBDS->setChecked(true);
        ui->pushButtonBDSSelect->setEnabled(true);
        //Measurements
        ui->pushButtonBDSMeasurements->setEnabled(true);
        this->on_pushButtonBDSMeasurements_clicked();
        this->FreqMeasGNSS->changePushButtonBDS(true);
        this->FreqMeasGNSS->on_pushButtonPublicBDS_clicked();
        this->MeasSelectGNSS->changePushButtonBDS(true);
        this->MeasSelectGNSS->on_pushButtonPublicBDS_clicked();
        this->doubleClick_RefGNSSClock(1,"BDS");
        this->select_ISCBGNSS(1,"BDS");
        this->SnrAdvancedMinWin->changePushButtonBDS(true);
        this->SnrAdvancedMinWin->on_pushButtonPublicBDS_clicked();
        this->SnrAdvancedMaxWin->changePushButtonBDS(true);
        this->SnrAdvancedMaxWin->on_pushButtonPublicBDS_clicked();
        this->CSAdvancedSF->changePushButtonBDS(true);
        this->CSAdvancedSF->on_pushButtonPublicBDS_clicked();
        this->CSAdvancedMW->changePushButtonBDS(true);
        this->CSAdvancedMW->on_pushButtonPublicBDS_clicked();
        this->CSAdvancedLI->changePushButtonBDS(true);
        this->CSAdvancedLI->on_pushButtonPublicBDS_clicked();
        this->CSAdvancedIGF->changePushButtonBDS(true);
        this->CSAdvancedIGF->on_pushButtonPublicBDS_clicked();
        this->APCAdvanced->changePushButtonBDS(true);
        this->APCAdvanced->on_pushButtonPublicBDS_clicked();
        this->SBASOBADSet->setBDS(true);
        for(i=1;i<=MAX_SAT_BDS;i++) {
            PushButtonSatWidgets[BDS][i]->setStyleSheet(QString("background-color:%1; color:black;").arg(GreenColor));
        }
    }
    if (nowGnss==QZSS){
        ui->checkBoxQZSS->setChecked(true);
        ui->pushButtonQZSSSelect->setEnabled(true);
        //Measurements
        ui->pushButtonQZSSMeasurements->setEnabled(true);
        this->on_pushButtonQZSSMeasurements_clicked();
        this->FreqMeasGNSS->changePushButtonQZSS(true);
        this->FreqMeasGNSS->on_pushButtonPublicQZSS_clicked();
        this->MeasSelectGNSS->changePushButtonQZSS(true);
        this->MeasSelectGNSS->on_pushButtonPublicQZSS_clicked();
        this->doubleClick_RefGNSSClock(1,"QZSS");
        this->select_ISCBGNSS(1,"QZSS");
        this->SnrAdvancedMinWin->changePushButtonQZSS(true);
        this->SnrAdvancedMinWin->on_pushButtonPublicQZSS_clicked();
        this->SnrAdvancedMaxWin->changePushButtonQZSS(true);
        this->SnrAdvancedMaxWin->on_pushButtonPublicQZSS_clicked();
        this->CSAdvancedSF->changePushButtonQZSS(true);
        this->CSAdvancedSF->on_pushButtonPublicQZSS_clicked();
        this->CSAdvancedMW->changePushButtonQZSS(true);
        this->CSAdvancedMW->on_pushButtonPublicQZSS_clicked();
        this->CSAdvancedLI->changePushButtonQZSS(true);
        this->CSAdvancedLI->on_pushButtonPublicQZSS_clicked();
        this->CSAdvancedIGF->changePushButtonQZSS(true);
        this->CSAdvancedIGF->on_pushButtonPublicQZSS_clicked();
        this->APCAdvanced->changePushButtonQZSS(true);
        this->APCAdvanced->on_pushButtonPublicQZSS_clicked();
        this->SBASOBADSet->setQZSS(true);
        for(i=1;i<=MAX_SAT_QZS;i++) {
            PushButtonSatWidgets[QZSS][i]->setStyleSheet(QString("background-color:%1; color:black;").arg(GreenColor));
        }
    }
    if (nowGnss==IRNSS){
        ui->checkBoxIRNSS->setChecked(true);
        ui->pushButtonIRNSSSelect->setEnabled(true);
        //Measurements
        ui->pushButtonIRNSSMeasurements->setEnabled(true);
        this->on_pushButtonIRNSSMeasurements_clicked();
        this->FreqMeasGNSS->changePushButtonIRNSS(true);
        this->FreqMeasGNSS->on_pushButtonPublicIRNSS_clicked();
        this->MeasSelectGNSS->changePushButtonIRNSS(true);
        this->MeasSelectGNSS->on_pushButtonPublicIRNSS_clicked();
        this->doubleClick_RefGNSSClock(1,"IRNSS");
        this->select_ISCBGNSS(1,"IRNSS");
        this->SnrAdvancedMinWin->changePushButtonIRNSS(true);
        this->SnrAdvancedMinWin->on_pushButtonPublicIRNSS_clicked();
        this->SnrAdvancedMaxWin->changePushButtonIRNSS(true);
        this->SnrAdvancedMaxWin->on_pushButtonPublicIRNSS_clicked();
        this->CSAdvancedSF->changePushButtonIRNSS(true);
        this->CSAdvancedSF->on_pushButtonPublicIRNSS_clicked();
        this->CSAdvancedMW->changePushButtonIRNSS(true);
        this->CSAdvancedMW->on_pushButtonPublicIRNSS_clicked();
        this->CSAdvancedLI->changePushButtonIRNSS(true);
        this->CSAdvancedLI->on_pushButtonPublicIRNSS_clicked();
        //this->CSAdvancedIGF->changePushButtonIRNSS(true); //IRNSS does not have triple frequency, it cannot use IGF
        //this->CSAdvancedIGF->on_pushButtonPublicIRNSS_clicked(); //IRNSS does not have triple frequency, it cannot use IGF
        this->APCAdvanced->changePushButtonIRNSS(true);
        this->APCAdvanced->on_pushButtonPublicIRNSS_clicked();
        this->SBASOBADSet->setIRNSS(true);
        for(i=1;i<=MAX_SAT_IRN;i++) {
            PushButtonSatWidgets[IRNSS][i]->setStyleSheet(QString("background-color:%1; color:black;").arg(GreenColor));
        }
    }
}

// Function to set all GPS satellites unavailable
void gLAB_GUI::on_pushButtonSatSelNone_clicked() {
    int i,nowGnss=ui->stackedWidgetPRNButtons->currentIndex();
    if (nowGnss==GPS){
        ui->checkBoxGPS->setChecked(false);
        ui->pushButtonGPSSelect->setEnabled(false);
        //Measurements
        ui->pushButtonGPSMeasurements->setEnabled(false);
        this->FreqMeasGNSS->changePushButtonGPS(false);
        this->MeasSelectGNSS->changePushButtonGPS(false);
        this->doubleClick_RefGNSSClock(0,"GPS");
        this->select_ISCBGNSS(0,"GPS");
        this->SnrAdvancedMinWin->changePushButtonGPS(false);
        this->SnrAdvancedMaxWin->changePushButtonGPS(false);
        this->CSAdvancedSF->changePushButtonGPS(false);
        this->CSAdvancedMW->changePushButtonGPS(false);
        this->CSAdvancedLI->changePushButtonGPS(false);
        this->CSAdvancedIGF->changePushButtonGPS(false);
        this->APCAdvanced->changePushButtonGPS(false);
        this->SBASOBADSet->setGPS(false);
        for(i=1;i<=MAX_SAT_GPS;i++) {
            PushButtonSatWidgets[GPS][i]->setStyleSheet(QString("background-color:%1; color:black;").arg(RedColor));
        }
    }
    if (nowGnss==Galileo){
        ui->checkBoxGalileo->setChecked(false);
        ui->pushButtonGalileoSelect->setEnabled(false);
        //Measurements
        ui->pushButtonGalileoMeasurements->setEnabled(false);
        this->FreqMeasGNSS->changePushButtonGalileo(false);
        this->MeasSelectGNSS->changePushButtonGalileo(false);
        this->doubleClick_RefGNSSClock(0,"Galileo");
        this->select_ISCBGNSS(0,"Galileo");
        this->SnrAdvancedMinWin->changePushButtonGalileo(false);
        this->SnrAdvancedMaxWin->changePushButtonGalileo(false);
        this->CSAdvancedSF->changePushButtonGalileo(false);
        this->CSAdvancedMW->changePushButtonGalileo(false);
        this->CSAdvancedLI->changePushButtonGalileo(false);
        this->CSAdvancedIGF->changePushButtonGalileo(false);
        this->APCAdvanced->changePushButtonGalileo(false);
        this->SBASOBADSet->setGalileo(false);
        for(i=1;i<=MAX_SAT_GAL;i++) {
            PushButtonSatWidgets[Galileo][i]->setStyleSheet(QString("background-color:%1; color:black;").arg(RedColor));
        }
    }
    if (nowGnss==GLONASS){
        ui->checkBoxRinexNavFileGLO1->setHidden(true);
        if (ui->checkBoxRinexNavFileGLO1->isChecked()==true) {
            ui->lineEditRinexNavFileGLO1->setHidden(true);
            ui->pushButtonRinexNavFileGLO1->setHidden(true);
        }
        ui->checkBoxRinexNavFileGLO2->setHidden(true);
        if (ui->checkBoxRinexNavFileGLO2->isChecked()==true) {
            ui->lineEditRinexNavFileGLO2->setHidden(true);
            ui->pushButtonRinexNavFileGLO2->setHidden(true);
        }
        ui->checkBoxGLONASS->setChecked(false);
        ui->pushButtonGLONASSSelect->setEnabled(false);
        //Measurements
        ui->pushButtonGLONASSMeasurements->setEnabled(false);
        this->FreqMeasGNSS->changePushButtonGLONASS(false);
        this->MeasSelectGNSS->changePushButtonGLONASS(false);
        this->doubleClick_RefGNSSClock(0,"GLONASS");
        this->select_ISCBGNSS(0,"GLONASS");
        this->SnrAdvancedMinWin->changePushButtonGLONASS(false);
        this->SnrAdvancedMaxWin->changePushButtonGLONASS(false);
        this->CSAdvancedSF->changePushButtonGLONASS(false);
        this->CSAdvancedMW->changePushButtonGLONASS(false);
        this->CSAdvancedLI->changePushButtonGLONASS(false);
        this->CSAdvancedIGF->changePushButtonGLONASS(false);
        this->APCAdvanced->changePushButtonGLONASS(false);
        this->SBASOBADSet->setGLONASS(false);
        for(i=1;i<=MAX_SAT_GLO;i++) {
            PushButtonSatWidgets[GLONASS][i]->setStyleSheet(QString("background-color:%1; color:black;").arg(RedColor));
        }
    }
    if (nowGnss==GEO){
        ui->checkBoxGEO->setChecked(false);
        ui->pushButtonGEOSelect->setEnabled(false);
        //Measurements
        ui->pushButtonGEOMeasurements->setEnabled(false);
        this->FreqMeasGNSS->changePushButtonGEO(false);
        this->MeasSelectGNSS->changePushButtonGEO(false);
        this->doubleClick_RefGNSSClock(0,"GEO");
        this->select_ISCBGNSS(0,"GEO");
        this->SnrAdvancedMinWin->changePushButtonGEO(false);
        this->SnrAdvancedMaxWin->changePushButtonGEO(false);
        this->CSAdvancedSF->changePushButtonGEO(false);
        this->CSAdvancedMW->changePushButtonGEO(false);
        this->CSAdvancedLI->changePushButtonGEO(false);
        this->CSAdvancedIGF->changePushButtonGEO(false);
        this->APCAdvanced->changePushButtonGEO(false);
        this->SBASOBADSet->setGEO(false);
        for(i=1;i<=MAX_SAT_GEO;i++) {
            PushButtonSatWidgets[GEO][i]->setStyleSheet(QString("background-color:%1; color:black;").arg(RedColor));
        }
    }
    if (nowGnss==BDS){
        ui->checkBoxBDS->setChecked(false);
        ui->pushButtonBDSSelect->setEnabled(false);
        //Measurements
        ui->pushButtonBDSMeasurements->setEnabled(false);
        this->FreqMeasGNSS->changePushButtonBDS(false);
        this->MeasSelectGNSS->changePushButtonBDS(false);
        this->doubleClick_RefGNSSClock(0,"BDS");
        this->select_ISCBGNSS(0,"BDS");
        this->SnrAdvancedMinWin->changePushButtonBDS(false);
        this->SnrAdvancedMaxWin->changePushButtonBDS(false);
        this->CSAdvancedSF->changePushButtonBDS(false);
        this->CSAdvancedMW->changePushButtonBDS(false);
        this->CSAdvancedLI->changePushButtonBDS(false);
        this->CSAdvancedIGF->changePushButtonBDS(false);
        this->APCAdvanced->changePushButtonBDS(false);
        this->SBASOBADSet->setBDS(false);
        for(i=1;i<=MAX_SAT_BDS;i++) {
            PushButtonSatWidgets[BDS][i]->setStyleSheet(QString("background-color:%1; color:black;").arg(RedColor));
        }
    }
    if (nowGnss==QZSS){
        ui->checkBoxQZSS->setChecked(false);
        ui->pushButtonQZSSSelect->setEnabled(false);
        //Measurements
        ui->pushButtonQZSSMeasurements->setEnabled(false);
        this->FreqMeasGNSS->changePushButtonQZSS(false);
        this->MeasSelectGNSS->changePushButtonQZSS(false);
        this->doubleClick_RefGNSSClock(0,"QZSS");
        this->select_ISCBGNSS(0,"QZSS");
        this->SnrAdvancedMinWin->changePushButtonQZSS(false);
        this->SnrAdvancedMaxWin->changePushButtonQZSS(false);
        this->CSAdvancedSF->changePushButtonQZSS(false);
        this->CSAdvancedMW->changePushButtonQZSS(false);
        this->CSAdvancedLI->changePushButtonQZSS(false);
        this->CSAdvancedIGF->changePushButtonQZSS(false);
        this->APCAdvanced->changePushButtonQZSS(false);
        this->SBASOBADSet->setQZSS(false);
        for(i=1;i<=MAX_SAT_QZS;i++) {
            PushButtonSatWidgets[QZSS][i]->setStyleSheet(QString("background-color:%1; color:black;").arg(RedColor));
        }
    }
    if (nowGnss==IRNSS){
        ui->checkBoxIRNSS->setChecked(false);
        ui->pushButtonIRNSSSelect->setEnabled(false);
        //Measurements
        ui->pushButtonIRNSSMeasurements->setEnabled(false);
        this->FreqMeasGNSS->changePushButtonIRNSS(false);
        this->MeasSelectGNSS->changePushButtonIRNSS(false);
        this->doubleClick_RefGNSSClock(0,"IRNSS");
        this->select_ISCBGNSS(0,"IRNSS");
        this->SnrAdvancedMinWin->changePushButtonIRNSS(false);
        this->SnrAdvancedMaxWin->changePushButtonIRNSS(false);
        this->CSAdvancedSF->changePushButtonIRNSS(false);
        this->CSAdvancedMW->changePushButtonIRNSS(false);
        this->CSAdvancedLI->changePushButtonIRNSS(false);
        this->CSAdvancedIGF->changePushButtonIRNSS(false);
        this->APCAdvanced->changePushButtonIRNSS(false);
        this->SBASOBADSet->setIRNSS(false);
        for(i=1;i<=MAX_SAT_IRN;i++) {
            PushButtonSatWidgets[IRNSS][i]->setStyleSheet(QString("background-color:%1; color:black;").arg(RedColor));
        }
    }

    for (int i=0; i<MAX_GNSS; i++){
        if (CheckBoxGNSS[i]->isChecked()){
            (this->*PushButtonGNSSMeasurementFunctions[i])();
            break;
        }
    }
    this->FreqMeasGNSS->changeCurrentPage();
    this->MeasSelectGNSS->changeCurrentPage();
    this->SnrAdvancedMinWin->changeCurrentPage();
    this->SnrAdvancedMaxWin->changeCurrentPage();
    this->CSAdvancedSF->changeCurrentPage();
    this->CSAdvancedMW->changeCurrentPage();
    this->CSAdvancedLI->changeCurrentPage();
    this->CSAdvancedIGF->changeCurrentPage();
    this->APCAdvanced->changeCurrentPage();
}

//GPS
// Button for GPS PRN 1
void gLAB_GUI::on_pushButtonG1_clicked() {
    QColor col = ui->pushButtonG1->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG1->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG1->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 2
void gLAB_GUI::on_pushButtonG2_clicked() {
    QColor col = ui->pushButtonG2->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG2->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG2->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 3
void gLAB_GUI::on_pushButtonG3_clicked() {
    QColor col = ui->pushButtonG3->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG3->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG3->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 4
void gLAB_GUI::on_pushButtonG4_clicked() {
    QColor col = ui->pushButtonG4->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG4->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG4->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 5
void gLAB_GUI::on_pushButtonG5_clicked() {
    QColor col = ui->pushButtonG5->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG5->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG5->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 6
void gLAB_GUI::on_pushButtonG6_clicked() {
    QColor col = ui->pushButtonG6->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG6->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG6->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 7
void gLAB_GUI::on_pushButtonG7_clicked() {
    QColor col = ui->pushButtonG7->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG7->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG7->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 8
void gLAB_GUI::on_pushButtonG8_clicked() {
    QColor col = ui->pushButtonG8->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG8->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG8->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 9
void gLAB_GUI::on_pushButtonG9_clicked() {
    QColor col = ui->pushButtonG9->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG9->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG9->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 10
void gLAB_GUI::on_pushButtonG10_clicked() {
    QColor col = ui->pushButtonG10->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG10->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG10->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 11
void gLAB_GUI::on_pushButtonG11_clicked() {
    QColor col = ui->pushButtonG11->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG11->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG11->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 12
void gLAB_GUI::on_pushButtonG12_clicked() {
    QColor col = ui->pushButtonG12->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG12->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG12->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 13
void gLAB_GUI::on_pushButtonG13_clicked() {
    QColor col = ui->pushButtonG13->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG13->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG13->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 14
void gLAB_GUI::on_pushButtonG14_clicked() {
    QColor col = ui->pushButtonG14->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG14->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG14->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 15
void gLAB_GUI::on_pushButtonG15_clicked() {
    QColor col = ui->pushButtonG15->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG15->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG15->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 16
void gLAB_GUI::on_pushButtonG16_clicked() {
    QColor col = ui->pushButtonG16->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG16->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG16->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 17
void gLAB_GUI::on_pushButtonG17_clicked() {
    QColor col = ui->pushButtonG17->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG17->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG17->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 18
void gLAB_GUI::on_pushButtonG18_clicked() {
    QColor col = ui->pushButtonG18->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG18->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG18->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 19
void gLAB_GUI::on_pushButtonG19_clicked() {
    QColor col = ui->pushButtonG19->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG19->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG19->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 20
void gLAB_GUI::on_pushButtonG20_clicked() {
    QColor col = ui->pushButtonG20->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG20->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG20->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 21
void gLAB_GUI::on_pushButtonG21_clicked() {
    QColor col = ui->pushButtonG21->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG21->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG21->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 22
void gLAB_GUI::on_pushButtonG22_clicked() {
    QColor col = ui->pushButtonG22->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG22->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG22->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 23
void gLAB_GUI::on_pushButtonG23_clicked() {
    QColor col = ui->pushButtonG23->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG23->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG23->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 24
void gLAB_GUI::on_pushButtonG24_clicked() {
    QColor col = ui->pushButtonG24->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG24->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG24->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 25
void gLAB_GUI::on_pushButtonG25_clicked() {
    QColor col = ui->pushButtonG25->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG25->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG25->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 26
void gLAB_GUI::on_pushButtonG26_clicked() {
    QColor col = ui->pushButtonG26->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG26->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG26->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 27
void gLAB_GUI::on_pushButtonG27_clicked() {
    QColor col = ui->pushButtonG27->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG27->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG27->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 28
void gLAB_GUI::on_pushButtonG28_clicked() {
    QColor col = ui->pushButtonG28->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG28->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG28->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 29
void gLAB_GUI::on_pushButtonG29_clicked() {
    QColor col = ui->pushButtonG29->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG29->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG29->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 30
void gLAB_GUI::on_pushButtonG30_clicked() {
    QColor col = ui->pushButtonG30->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG30->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG30->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 31
void gLAB_GUI::on_pushButtonG31_clicked() {
    QColor col = ui->pushButtonG31->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG31->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG31->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

// Button for GPS PRN 32
void gLAB_GUI::on_pushButtonG32_clicked() {
    QColor col = ui->pushButtonG32->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonG32->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonG32->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GPS; numRed++){
            if (PushButtonSatWidgets[GPS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GPS) this->on_checkBoxGPS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GPS && ui->checkBoxGPS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGPS_ForOneSat();
    }
}

//Galileo
void gLAB_GUI::on_pushButtonE1_clicked(){
    QColor col = ui->pushButtonE1->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE1->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE1->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE2_clicked(){
    QColor col = ui->pushButtonE2->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE2->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE2->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE3_clicked(){
    QColor col = ui->pushButtonE3->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE3->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE3->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE4_clicked(){
    QColor col = ui->pushButtonE4->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE4->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE4->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE5_clicked(){
    QColor col = ui->pushButtonE5->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE5->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE5->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE6_clicked(){
    QColor col = ui->pushButtonE6->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE6->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE6->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE7_clicked(){
    QColor col = ui->pushButtonE7->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE7->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE7->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE8_clicked(){
    QColor col = ui->pushButtonE8->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE8->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE8->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE9_clicked(){
    QColor col = ui->pushButtonE9->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE9->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE9->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE10_clicked(){
    QColor col = ui->pushButtonE10->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE10->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE10->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE11_clicked(){
    QColor col = ui->pushButtonE11->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE11->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE11->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE12_clicked(){
    QColor col = ui->pushButtonE12->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE12->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE12->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE13_clicked(){
    QColor col = ui->pushButtonE13->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE13->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE13->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE14_clicked(){
    QColor col = ui->pushButtonE14->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE14->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE14->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE15_clicked(){
    QColor col = ui->pushButtonE15->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE15->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE15->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE16_clicked(){
    QColor col = ui->pushButtonE16->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE16->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE16->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE17_clicked(){
    QColor col = ui->pushButtonE17->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE17->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE17->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE18_clicked(){
    QColor col = ui->pushButtonE18->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE18->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE18->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE19_clicked(){
    QColor col = ui->pushButtonE19->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE19->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE19->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE20_clicked(){
    QColor col = ui->pushButtonE20->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE20->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE20->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE21_clicked(){
    QColor col = ui->pushButtonE21->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE21->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE21->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE22_clicked(){
    QColor col = ui->pushButtonE22->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE22->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE22->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE23_clicked(){
    QColor col = ui->pushButtonE23->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE23->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE23->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE24_clicked(){
    QColor col = ui->pushButtonE24->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE24->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE24->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE25_clicked(){
    QColor col = ui->pushButtonE25->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE25->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE25->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE26_clicked(){
    QColor col = ui->pushButtonE26->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE26->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE26->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE27_clicked(){
    QColor col = ui->pushButtonE27->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE27->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE27->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE28_clicked(){
    QColor col = ui->pushButtonE28->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE28->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE28->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE29_clicked(){
    QColor col = ui->pushButtonE29->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE29->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE29->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE30_clicked(){
    QColor col = ui->pushButtonE30->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE30->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE30->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE31_clicked(){
    QColor col = ui->pushButtonE31->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE31->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE31->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE32_clicked(){
    QColor col = ui->pushButtonE32->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE32->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE32->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE33_clicked(){
    QColor col = ui->pushButtonE33->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE33->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE33->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE34_clicked(){
    QColor col = ui->pushButtonE34->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE34->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE34->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE35_clicked(){
    QColor col = ui->pushButtonE35->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE35->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE35->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonE36_clicked(){
    QColor col = ui->pushButtonE36->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonE36->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonE36->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GAL; numRed++){
            if (PushButtonSatWidgets[Galileo][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GAL) this->on_checkBoxGalileo_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==Galileo && ui->checkBoxGalileo->isChecked()==false ) { //checked if not-checked
        this->checkBoxGalileo_ForOneSat();
    }
}
//GLONASS
void gLAB_GUI::on_pushButtonR1_clicked(){
    QColor col = ui->pushButtonR1->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR1->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR1->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR2_clicked(){
    QColor col = ui->pushButtonR2->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR2->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR2->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR3_clicked(){
    QColor col = ui->pushButtonR3->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR3->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR3->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR4_clicked(){
    QColor col = ui->pushButtonR4->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR4->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR4->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR5_clicked(){
    QColor col = ui->pushButtonR5->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR5->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR5->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR6_clicked(){
    QColor col = ui->pushButtonR6->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR6->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR6->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR7_clicked(){
    QColor col = ui->pushButtonR7->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR7->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR7->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR8_clicked(){
    QColor col = ui->pushButtonR8->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR8->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR8->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR9_clicked(){
    QColor col = ui->pushButtonR9->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR9->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR9->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR10_clicked(){
    QColor col = ui->pushButtonR10->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR10->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR10->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR11_clicked(){
    QColor col = ui->pushButtonR11->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR11->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR11->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR12_clicked(){
    QColor col = ui->pushButtonR12->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR12->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR12->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR13_clicked(){
    QColor col = ui->pushButtonR13->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR13->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR13->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR14_clicked(){
    QColor col = ui->pushButtonR14->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR14->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR14->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR15_clicked(){
    QColor col = ui->pushButtonR15->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR15->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR15->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR16_clicked(){
    QColor col = ui->pushButtonR16->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR16->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR16->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR17_clicked(){
    QColor col = ui->pushButtonR17->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR17->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR17->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR18_clicked(){
    QColor col = ui->pushButtonR18->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR18->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR18->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR19_clicked(){
    QColor col = ui->pushButtonR19->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR19->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR19->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR20_clicked(){
    QColor col = ui->pushButtonR20->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR20->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR20->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR21_clicked(){
    QColor col = ui->pushButtonR21->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR21->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR21->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR22_clicked(){
    QColor col = ui->pushButtonR22->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR22->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR22->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR23_clicked(){
    QColor col = ui->pushButtonR23->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR23->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR23->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR24_clicked(){
    QColor col = ui->pushButtonR24->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR24->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR24->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR25_clicked(){
    QColor col = ui->pushButtonR25->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR25->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR25->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR26_clicked(){
    QColor col = ui->pushButtonR26->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR26->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR26->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR27_clicked(){
    QColor col = ui->pushButtonR27->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR27->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR27->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR28_clicked(){
    QColor col = ui->pushButtonR28->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR28->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR28->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR29_clicked(){
    QColor col = ui->pushButtonR29->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR29->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR29->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR30_clicked(){
    QColor col = ui->pushButtonR30->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR30->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR30->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR31_clicked(){
    QColor col = ui->pushButtonR31->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR31->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR31->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonR32_clicked(){
    QColor col = ui->pushButtonR32->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonR32->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonR32->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GLO; numRed++){
            if (PushButtonSatWidgets[GLONASS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GLO) this->on_checkBoxGLONASS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GLONASS && ui->checkBoxGLONASS->isChecked()==false ) { //checked if not-checked
        this->checkBoxGLONASS_ForOneSat();
    }
}
//GEO
void gLAB_GUI::on_pushButtonS120_clicked(){
    QColor col = ui->pushButtonS120->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS120->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS120->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS121_clicked(){
    QColor col = ui->pushButtonS121->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS121->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS121->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS122_clicked(){
    QColor col = ui->pushButtonS122->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS122->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS122->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS123_clicked(){
    QColor col = ui->pushButtonS123->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS123->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS123->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS124_clicked(){
    QColor col = ui->pushButtonS124->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS124->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS124->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS125_clicked(){
    QColor col = ui->pushButtonS125->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS125->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS125->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS126_clicked(){
    QColor col = ui->pushButtonS126->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS126->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS126->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS127_clicked(){
    QColor col = ui->pushButtonS127->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS127->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS127->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS128_clicked(){
    QColor col = ui->pushButtonS128->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS128->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS128->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS129_clicked(){
    QColor col = ui->pushButtonS129->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS129->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS129->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS130_clicked(){
    QColor col = ui->pushButtonS130->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS130->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS130->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS131_clicked(){
    QColor col = ui->pushButtonS131->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS131->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS131->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS132_clicked(){
    QColor col = ui->pushButtonS132->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS132->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS132->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS133_clicked(){
    QColor col = ui->pushButtonS133->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS133->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS133->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS134_clicked(){
    QColor col = ui->pushButtonS134->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS134->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS134->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS135_clicked(){
    QColor col = ui->pushButtonS135->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS135->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS135->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS136_clicked(){
    QColor col = ui->pushButtonS136->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS136->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS136->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS137_clicked(){
    QColor col = ui->pushButtonS137->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS137->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS137->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS138_clicked(){
    QColor col = ui->pushButtonS138->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS138->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS138->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS139_clicked(){
    QColor col = ui->pushButtonS139->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS139->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS139->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS140_clicked(){
    QColor col = ui->pushButtonS140->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS140->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS140->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS141_clicked(){
    QColor col = ui->pushButtonS141->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS141->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS141->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS142_clicked(){
    QColor col = ui->pushButtonS142->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS142->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS142->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS143_clicked(){
    QColor col = ui->pushButtonS143->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS143->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS143->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS144_clicked(){
    QColor col = ui->pushButtonS144->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS144->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS144->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS145_clicked(){
    QColor col = ui->pushButtonS145->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS145->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS145->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS146_clicked(){
    QColor col = ui->pushButtonS146->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS146->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS146->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS147_clicked(){
    QColor col = ui->pushButtonS147->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS147->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS147->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS148_clicked(){
    QColor col = ui->pushButtonS148->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS148->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS148->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS149_clicked(){
    QColor col = ui->pushButtonS149->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS149->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS149->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS150_clicked(){
    QColor col = ui->pushButtonS150->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS150->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS150->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS151_clicked(){
    QColor col = ui->pushButtonS151->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS151->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS151->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS152_clicked(){
    QColor col = ui->pushButtonS152->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS152->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS152->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS153_clicked(){
    QColor col = ui->pushButtonS153->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS153->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS153->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS154_clicked(){
    QColor col = ui->pushButtonS154->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS154->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS154->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS155_clicked(){
    QColor col = ui->pushButtonS155->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS155->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS155->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS156_clicked(){
    QColor col = ui->pushButtonS156->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS156->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS156->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS157_clicked(){
    QColor col = ui->pushButtonS157->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS157->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS157->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonS158_clicked(){
    QColor col = ui->pushButtonS158->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonS158->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonS158->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_GEO; numRed++){
            if (PushButtonSatWidgets[GEO][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_GEO) this->on_checkBoxGEO_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==GEO && ui->checkBoxGEO->isChecked()==false ) { //checked if not-checked
        this->checkBoxGEO_ForOneSat();
    }
}
//BDS
void gLAB_GUI::on_pushButtonC1_clicked(){
    QColor col = ui->pushButtonC1->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC1->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC1->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC2_clicked(){
    QColor col = ui->pushButtonC2->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC2->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC2->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC3_clicked(){
    QColor col = ui->pushButtonC3->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC3->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC3->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC4_clicked(){
    QColor col = ui->pushButtonC4->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC4->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC4->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC5_clicked(){
    QColor col = ui->pushButtonC5->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC5->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC5->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC6_clicked(){
    QColor col = ui->pushButtonC6->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC6->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC6->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC7_clicked(){
    QColor col = ui->pushButtonC7->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC7->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC7->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC8_clicked(){
    QColor col = ui->pushButtonC8->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC8->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC8->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC9_clicked(){
    QColor col = ui->pushButtonC9->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC9->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC9->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC10_clicked(){
    QColor col = ui->pushButtonC10->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC10->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC10->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC11_clicked(){
    QColor col = ui->pushButtonC11->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC11->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC11->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC12_clicked(){
    QColor col = ui->pushButtonC12->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC12->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC12->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC13_clicked(){
    QColor col = ui->pushButtonC13->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC13->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC13->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC14_clicked(){
    QColor col = ui->pushButtonC14->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC14->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC14->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC15_clicked(){
    QColor col = ui->pushButtonC15->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC15->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC15->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC16_clicked(){
    QColor col = ui->pushButtonC16->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC16->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC16->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC17_clicked(){
    QColor col = ui->pushButtonC17->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC17->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC17->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC18_clicked(){
    QColor col = ui->pushButtonC18->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC18->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC18->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC19_clicked(){
    QColor col = ui->pushButtonC19->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC19->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC19->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC20_clicked(){
    QColor col = ui->pushButtonC20->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC20->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC20->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC21_clicked(){
    QColor col = ui->pushButtonC21->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC21->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC21->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC22_clicked(){
    QColor col = ui->pushButtonC22->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC22->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC22->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC23_clicked(){
    QColor col = ui->pushButtonC23->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC23->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC23->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC24_clicked(){
    QColor col = ui->pushButtonC24->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC24->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC24->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC25_clicked(){
    QColor col = ui->pushButtonC25->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC25->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC25->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC26_clicked(){
    QColor col = ui->pushButtonC26->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC26->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC26->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC27_clicked(){
    QColor col = ui->pushButtonC27->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC27->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC27->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC28_clicked(){
    QColor col = ui->pushButtonC28->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC28->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC28->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC29_clicked(){
    QColor col = ui->pushButtonC29->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC29->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC29->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC30_clicked(){
    QColor col = ui->pushButtonC30->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC30->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC30->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC31_clicked(){
    QColor col = ui->pushButtonC31->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC31->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC31->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC32_clicked(){
    QColor col = ui->pushButtonC32->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC32->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC32->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC33_clicked(){
    QColor col = ui->pushButtonC33->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC33->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC33->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC34_clicked(){
    QColor col = ui->pushButtonC34->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC34->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC34->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC35_clicked(){
    QColor col = ui->pushButtonC35->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC35->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC35->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC36_clicked(){
    QColor col = ui->pushButtonC36->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC36->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC36->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC37_clicked(){
    QColor col = ui->pushButtonC37->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC37->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC37->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC38_clicked(){
    QColor col = ui->pushButtonC38->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC38->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC38->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC39_clicked(){
    QColor col = ui->pushButtonC39->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC39->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC39->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC40_clicked(){
    QColor col = ui->pushButtonC40->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC40->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC40->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC41_clicked(){
    QColor col = ui->pushButtonC41->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC41->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC41->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC42_clicked(){
    QColor col = ui->pushButtonC42->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC42->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC42->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC43_clicked(){
    QColor col = ui->pushButtonC43->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC43->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC43->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC44_clicked(){
    QColor col = ui->pushButtonC44->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC44->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC44->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC45_clicked(){
    QColor col = ui->pushButtonC45->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC45->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC45->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC46_clicked(){
    QColor col = ui->pushButtonC46->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC46->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC46->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC47_clicked(){
    QColor col = ui->pushButtonC47->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC47->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC47->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC48_clicked(){
    QColor col = ui->pushButtonC48->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC48->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC48->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC49_clicked(){
    QColor col = ui->pushButtonC49->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC49->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC49->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC50_clicked(){
    QColor col = ui->pushButtonC50->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC50->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC50->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC51_clicked(){
    QColor col = ui->pushButtonC51->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC51->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC51->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC52_clicked(){
    QColor col = ui->pushButtonC52->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC52->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC52->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC53_clicked(){
    QColor col = ui->pushButtonC53->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC53->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC53->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC54_clicked(){
    QColor col = ui->pushButtonC54->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC54->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC54->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC55_clicked(){
    QColor col = ui->pushButtonC55->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC55->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC55->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC56_clicked(){
    QColor col = ui->pushButtonC56->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC56->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC56->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC57_clicked(){
    QColor col = ui->pushButtonC57->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC57->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC57->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC58_clicked(){
    QColor col = ui->pushButtonC58->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC58->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC58->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC59_clicked(){
    QColor col = ui->pushButtonC59->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC59->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC59->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC60_clicked(){
    QColor col = ui->pushButtonC60->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC60->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC60->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC61_clicked(){
    QColor col = ui->pushButtonC61->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC61->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC61->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC62_clicked(){
    QColor col = ui->pushButtonC62->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC62->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC62->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonC63_clicked(){
    QColor col = ui->pushButtonC63->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonC63->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonC63->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_BDS; numRed++){
            if (PushButtonSatWidgets[BDS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_BDS) this->on_checkBoxBDS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==BDS && ui->checkBoxBDS->isChecked()==false ) { //checked if not-checked
        this->checkBoxBDS_ForOneSat();
    }
}
//QZSS
void gLAB_GUI::on_pushButtonJ1_clicked(){
    QColor col = ui->pushButtonJ1->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonJ1->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonJ1->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_QZS; numRed++){
            if (PushButtonSatWidgets[QZSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_QZS) this->on_checkBoxQZSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxQZSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonJ2_clicked(){
    QColor col = ui->pushButtonJ2->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonJ2->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonJ2->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_QZS; numRed++){
            if (PushButtonSatWidgets[QZSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_QZS) this->on_checkBoxQZSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxQZSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonJ3_clicked(){
    QColor col = ui->pushButtonJ3->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonJ3->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonJ3->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_QZS; numRed++){
            if (PushButtonSatWidgets[QZSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_QZS) this->on_checkBoxQZSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxQZSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonJ4_clicked(){
    QColor col = ui->pushButtonJ4->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonJ4->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonJ4->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_QZS; numRed++){
            if (PushButtonSatWidgets[QZSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_QZS) this->on_checkBoxQZSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxQZSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonJ5_clicked(){
    QColor col = ui->pushButtonJ5->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonJ5->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonJ5->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_QZS; numRed++){
            if (PushButtonSatWidgets[QZSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_QZS) this->on_checkBoxQZSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxQZSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonJ6_clicked(){
    QColor col = ui->pushButtonJ6->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonJ6->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonJ6->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_QZS; numRed++){
            if (PushButtonSatWidgets[QZSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_QZS) this->on_checkBoxQZSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxQZSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonJ7_clicked(){
    QColor col = ui->pushButtonJ7->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonJ7->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonJ7->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_QZS; numRed++){
            if (PushButtonSatWidgets[QZSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_QZS) this->on_checkBoxQZSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxQZSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonJ8_clicked(){
    QColor col = ui->pushButtonJ8->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonJ8->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonJ8->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_QZS; numRed++){
            if (PushButtonSatWidgets[QZSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_QZS) this->on_checkBoxQZSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxQZSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonJ9_clicked(){
    QColor col = ui->pushButtonJ9->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonJ9->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonJ9->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_QZS; numRed++){
            if (PushButtonSatWidgets[QZSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_QZS) this->on_checkBoxQZSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxQZSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonJ10_clicked(){
    QColor col = ui->pushButtonJ10->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonJ10->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonJ10->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_QZS; numRed++){
            if (PushButtonSatWidgets[QZSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_QZS) this->on_checkBoxQZSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==QZSS && ui->checkBoxQZSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxQZSS_ForOneSat();
    }
}
//IRNSS
void gLAB_GUI::on_pushButtonI1_clicked(){
    QColor col = ui->pushButtonI1->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonI1->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonI1->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_IRN; numRed++){
            if (PushButtonSatWidgets[IRNSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_IRN) this->on_checkBoxIRNSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxIRNSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonI2_clicked(){
    QColor col = ui->pushButtonI2->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonI2->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonI2->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_IRN; numRed++){
            if (PushButtonSatWidgets[IRNSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_IRN) this->on_checkBoxIRNSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxIRNSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonI3_clicked(){
    QColor col = ui->pushButtonI3->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonI3->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonI3->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_IRN; numRed++){
            if (PushButtonSatWidgets[IRNSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_IRN) this->on_checkBoxIRNSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxIRNSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonI4_clicked(){
    QColor col = ui->pushButtonI4->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonI4->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonI4->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_IRN; numRed++){
            if (PushButtonSatWidgets[IRNSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_IRN) this->on_checkBoxIRNSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxIRNSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonI5_clicked(){
    QColor col = ui->pushButtonI5->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonI5->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonI5->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_IRN; numRed++){
            if (PushButtonSatWidgets[IRNSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_IRN) this->on_checkBoxIRNSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxIRNSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonI6_clicked(){
    QColor col = ui->pushButtonI6->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonI6->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonI6->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_IRN; numRed++){
            if (PushButtonSatWidgets[IRNSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_IRN) this->on_checkBoxIRNSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxIRNSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonI7_clicked(){
    QColor col = ui->pushButtonI7->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonI7->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonI7->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_IRN; numRed++){
            if (PushButtonSatWidgets[IRNSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_IRN) this->on_checkBoxIRNSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxIRNSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonI8_clicked(){
    QColor col = ui->pushButtonI8->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonI8->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonI8->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_IRN; numRed++){
            if (PushButtonSatWidgets[IRNSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_IRN) this->on_checkBoxIRNSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxIRNSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonI9_clicked(){
    QColor col = ui->pushButtonI9->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonI9->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonI9->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_IRN; numRed++){
            if (PushButtonSatWidgets[IRNSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_IRN) this->on_checkBoxIRNSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxIRNSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonI10_clicked(){
    QColor col = ui->pushButtonI10->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonI10->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonI10->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_IRN; numRed++){
            if (PushButtonSatWidgets[IRNSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_IRN) this->on_checkBoxIRNSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxIRNSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonI11_clicked(){
    QColor col = ui->pushButtonI11->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonI11->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonI11->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_IRN; numRed++){
            if (PushButtonSatWidgets[IRNSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_IRN) this->on_checkBoxIRNSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxIRNSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonI12_clicked(){
    QColor col = ui->pushButtonI12->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonI12->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonI12->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_IRN; numRed++){
            if (PushButtonSatWidgets[IRNSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_IRN) this->on_checkBoxIRNSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxIRNSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonI13_clicked(){
    QColor col = ui->pushButtonI13->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonI13->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonI13->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_IRN; numRed++){
            if (PushButtonSatWidgets[IRNSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_IRN) this->on_checkBoxIRNSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxIRNSS_ForOneSat();
    }
}
void gLAB_GUI::on_pushButtonI14_clicked(){
    QColor col = ui->pushButtonI14->palette().window().color();
    if ( col.name() == GreenColor ) ui->pushButtonI14->setStyleSheet(QString(" background-color:%1; color:black;").arg(RedColor));
    else ui->pushButtonI14->setStyleSheet(QString(" background-color:%1; color:black;").arg(GreenColor));
    if ( col.name() == GreenColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==true ){ //unchecked if is this is the last Green Button
        int numRed=1;
        for (numRed=1; numRed<=MAX_SAT_IRN; numRed++){
            if (PushButtonSatWidgets[IRNSS][numRed]->palette().window().color().name()==GreenColor){
                break;
            }
        }
        if (numRed>MAX_SAT_IRN) this->on_checkBoxIRNSS_clicked(false);
    }
    else if ( col.name() == RedColor && ui->stackedWidgetPRNButtons->currentIndex()==IRNSS && ui->checkBoxIRNSS->isChecked()==false ) { //checked if not-checked
        this->checkBoxIRNSS_ForOneSat();
    }
}

//Given satellite PRN and constellation, function to call its corresponding pushbutton function
void gLAB_GUI::callSatellitePushButtonFunction(enum GNSSystem System, int PRN, QString Sign) {
    if (PushButtonSatWidgets[System][PRN]->palette().window().color().name()!=Sign) {
        //Only change colour if is not in the correct colour
        (this->*PushButtonSatFunctions[System][PRN])();
    }
}

// Function to show or hide Ncon number of samples
void gLAB_GUI::on_checkBoxNcon_clicked(bool checked) {
    ui->checkBoxNcon->setChecked(checked);
    ui->frameNcon->setHidden(!checked);
}

//Function to enable SNR Min/Max advanced mode
void gLAB_GUI::on_checkBoxSNRMinAdvancedMode_clicked(bool checked){
    ui->checkBoxSNRMinAdvancedMode->setChecked(checked);
    if (checked){
        ui->pushButtonSNRMinAdvancedMode->setEnabled(true);
        ui->comboBoxSNRThresholdsMin->setEnabled(false);
        ui->lineEditUserDefinedSNRMin->setEnabled(false);
    }
    else {
        ui->pushButtonSNRMinAdvancedMode->setEnabled(false);
        ui->comboBoxSNRThresholdsMin->setEnabled(true);
        ui->lineEditUserDefinedSNRMin->setEnabled(true);
    }
}
void gLAB_GUI::on_checkBoxSNRMaxAdvancedMode_clicked(bool checked){
    ui->checkBoxSNRMaxAdvancedMode->setChecked(checked);
    if (checked){
        ui->pushButtonSNRMaxAdvancedMode->setEnabled(true);
        ui->comboBoxSNRThresholdsMax->setEnabled(false);
        ui->lineEditUserDefinedSNRMax->setEnabled(false);
    }
    else {
        ui->pushButtonSNRMaxAdvancedMode->setEnabled(false);
        ui->comboBoxSNRThresholdsMax->setEnabled(true);
        ui->lineEditUserDefinedSNRMax->setEnabled(true);
    }
}
void gLAB_GUI::on_pushButtonSNRMinAdvancedMode_clicked(){
    SnrAdvancedMinWin->setModal(true);
    SnrAdvancedMinWin->show();
}
void gLAB_GUI::on_pushButtonSNRMaxAdvancedMode_clicked(){
    SnrAdvancedMaxWin->setModal(true);
    SnrAdvancedMaxWin->show();
}

// Function to show or hide Min SNR threshold
void gLAB_GUI::on_checkBoxSNRThresholdMin_clicked(bool checked) {
    ui->checkBoxSNRThresholdMin->setChecked(checked);
    ui->frameSNRThresholdMin->setHidden(!checked);
}
// Function to show or hide Max SNR threshold
void gLAB_GUI::on_checkBoxSNRThresholdMax_clicked(bool checked) {
    ui->checkBoxSNRThresholdMax->setChecked(checked);
    ui->frameSNRThresholdMax->setHidden(!checked);
}
//Function to show or hide text box for user defined Min SNR threshold when SNR combo box changes
void gLAB_GUI::on_comboBoxSNRThresholdsMin_currentIndexChanged(int index) {
    ui->comboBoxSNRThresholdsMin->setCurrentIndex(index);
    if(ui->comboBoxSNRThresholdsMin->currentText()=="Specify") {
        ui->lineEditUserDefinedSNRMin->setHidden(false);
    } else {
        ui->lineEditUserDefinedSNRMin->setHidden(true);
    }
}
//Function to show or hide text box for user defined Max SNR threshold when SNR combo box changes
void gLAB_GUI::on_comboBoxSNRThresholdsMax_currentIndexChanged(int index) {
    ui->comboBoxSNRThresholdsMax->setCurrentIndex(index);
    if(ui->comboBoxSNRThresholdsMax->currentText()=="Specify") {
        ui->lineEditUserDefinedSNRMax->setHidden(false);
    } else {
        ui->lineEditUserDefinedSNRMax->setHidden(true);
    }
}

void gLAB_GUI::on_checkBoxDiscardUnhealthy_clicked(bool checked){
    ui->checkBoxDiscardUnhealthy->setChecked(checked);
    ui->frameDiscardMarginalSatellites->setHidden(checked);
    //Note: in this function we don't call on_checkBoxRinexNavFileHealth1_clicked or
    //on_checkBoxRinexNavFileHealth2_clicked to avoid an infinite loop, so we put the commands directly here
    if (checked==true || (checked==false && ui->checkBoxDiscardMarginal->isChecked()==false)) {
        ui->checkBoxRinexNavFileHealth1->setHidden(!checked);
        ui->checkBoxRinexNavFileHealth1->setChecked(checked);
        ui->lineEditRinexNavFileHealth1->setHidden(!checked);
        ui->pushButtonRinexNavFileHealth1->setHidden(!checked);
        ui->checkBoxRinexNavFileHealth2->setHidden(!checked);
        ui->checkBoxRinexNavFileHealth2->setChecked(checked);
        ui->lineEditRinexNavFileHealth2->setHidden(!checked);
        ui->pushButtonRinexNavFileHealth2->setHidden(!checked);
    }
}

void gLAB_GUI::on_checkBoxDiscardMarginal_clicked(bool checked){
    ui->checkBoxDiscardMarginal->setChecked(checked);
    //Note: in this function we don't call on_checkBoxRinexNavFileHealth1_clicked or
    //on_checkBoxRinexNavFileHealth2_clicked to avoid an infinite loop, so we put the commands directly here
    if (checked==true || (checked==false && ui->checkBoxDiscardUnhealthy->isChecked()==false)) {
        ui->checkBoxRinexNavFileHealth1->setHidden(!checked);
        ui->checkBoxRinexNavFileHealth1->setChecked(checked);
        ui->lineEditRinexNavFileHealth1->setHidden(!checked);
        ui->pushButtonRinexNavFileHealth1->setHidden(!checked);
        ui->checkBoxRinexNavFileHealth2->setHidden(!checked);
        ui->checkBoxRinexNavFileHealth2->setChecked(checked);
        ui->lineEditRinexNavFileHealth2->setHidden(!checked);
        ui->pushButtonRinexNavFileHealth2->setHidden(!checked);
    }
}

// Function to configure the Phase-Code cycle-slip detector parameters
void gLAB_GUI::on_pushButtonConfigureSF_clicked() {
    if (ui->stackedWidgetCSdetectionParameters->currentIndex() == 1) {
        ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
        ui->pushButtonConfigureSF->setChecked(false);
    }
    else {
        ui->stackedWidgetCSdetectionParameters->setCurrentIndex(1);
        ui->pushButtonConfigureSF->setChecked(true);
        ui->pushButtonConfigureMW->setChecked(false);
        ui->pushButtonConfigureLI->setChecked(false);
        ui->pushButtonConfigureIGF->setChecked(false);
    }
}

// Function to show Phase-Code Consistency check threshold
void gLAB_GUI::on_checkBoxSFConsistencyCheck_clicked(bool checked) {
    ui->checkBoxSFConsistencyCheck->setChecked(checked);
    ui->frameSFConsCheckValue->setHidden(!checked);
}
void gLAB_GUI::on_radioButtonSFAutoSelection_clicked(){
    ui->radioButtonSFAutoSelection->setChecked(true);
    ui->radioButtonSFManualSelection->setChecked(false);
    ui->pushButtonSFSelectMeasurements->setEnabled(false);
}
void gLAB_GUI::on_radioButtonSFManualSelection_clicked(){
    ui->radioButtonSFManualSelection->setChecked(true);
    ui->radioButtonSFAutoSelection->setChecked(false);
    ui->pushButtonSFSelectMeasurements->setEnabled(true);
}
void gLAB_GUI::on_pushButtonSFSelectMeasurements_clicked(){
    CSAdvancedSF->setModal(true);
    CSAdvancedSF->show();
}

// Function to configure the Melbourne-Wübbena cycle-slip detector parameters
void gLAB_GUI::on_pushButtonConfigureMW_clicked() {
    if (ui->stackedWidgetCSdetectionParameters->currentIndex() == 2) {
        ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
        ui->pushButtonConfigureMW->setChecked(false);
    }
    else {
        ui->stackedWidgetCSdetectionParameters->setCurrentIndex(2);
        ui->pushButtonConfigureSF->setChecked(false);
        ui->pushButtonConfigureMW->setChecked(true);
        ui->pushButtonConfigureLI->setChecked(false);
        ui->pushButtonConfigureIGF->setChecked(false);
    }
}
void gLAB_GUI::on_radioButtonMWAutoSelection_clicked(){
    ui->radioButtonMWAutoSelection->setChecked(true);
    ui->radioButtonMWManualSelection->setChecked(false);
    ui->pushButtonMWSelectMeasurements->setEnabled(false);
}
void gLAB_GUI::on_radioButtonMWManualSelection_clicked(){
    ui->radioButtonMWManualSelection->setChecked(true);
    ui->radioButtonMWAutoSelection->setChecked(false);
    ui->pushButtonMWSelectMeasurements->setEnabled(true);
}
void gLAB_GUI::on_pushButtonMWSelectMeasurements_clicked(){
    CSAdvancedMW->setModal(true);
    CSAdvancedMW->show();
}

// Function to configure the Geometry-free cycle-slip detector parameters
void gLAB_GUI::on_pushButtonConfigureLI_clicked() {
    if (ui->stackedWidgetCSdetectionParameters->currentIndex() == 3) {
        ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
        ui->pushButtonConfigureLI->setChecked(false);
    }
    else {
        ui->stackedWidgetCSdetectionParameters->setCurrentIndex(3);
        ui->pushButtonConfigureSF->setChecked(false);
        ui->pushButtonConfigureMW->setChecked(false);
        ui->pushButtonConfigureLI->setChecked(true);
        ui->pushButtonConfigureIGF->setChecked(false);
    }
}
void gLAB_GUI::on_radioButtonLIAutoSelection_clicked(){
    ui->radioButtonLIAutoSelection->setChecked(true);
    ui->radioButtonLIManualSelection->setChecked(false);
    ui->pushButtonLISelectMeasurements->setEnabled(false);
}
void gLAB_GUI::on_radioButtonLIManualSelection_clicked(){
    ui->radioButtonLIManualSelection->setChecked(true);
    ui->radioButtonLIAutoSelection->setChecked(false);
    ui->pushButtonLISelectMeasurements->setEnabled(true);
}
void gLAB_GUI::on_pushButtonLISelectMeasurements_clicked(){
    CSAdvancedLI->setModal(true);
    CSAdvancedLI->show();
}

// Function to configure the IGF cycle-slip detector parameters
void gLAB_GUI::on_pushButtonConfigureIGF_clicked() {
    if (ui->stackedWidgetCSdetectionParameters->currentIndex() == 4) {
        ui->stackedWidgetCSdetectionParameters->setCurrentIndex(0);
        ui->pushButtonConfigureIGF->setChecked(false);
    }
    else {
        ui->stackedWidgetCSdetectionParameters->setCurrentIndex(4);
        ui->pushButtonConfigureSF->setChecked(false);
        ui->pushButtonConfigureMW->setChecked(false);
        ui->pushButtonConfigureLI->setChecked(false);
        ui->pushButtonConfigureIGF->setChecked(true);
    }
}
void gLAB_GUI::on_radioButtonIGFMinimumNoise_clicked(){
    ui->radioButtonIGFMinimumNoise->setChecked(true);
    ui->radioButtonIGFTwoIonoFree->setChecked(false);
    this->CSAdvancedIGF->changeToMinimumNoiseMode();
}
void gLAB_GUI::on_radioButtonIGFTwoIonoFree_clicked(){
    ui->radioButtonIGFTwoIonoFree->setChecked(true);
    ui->radioButtonIGFMinimumNoise->setChecked(false);
    this->CSAdvancedIGF->changeToTwoIonoFreeMode();
}
void gLAB_GUI::on_radioButtonIGFAutoSelection_clicked(){
    ui->radioButtonIGFAutoSelection->setChecked(true);
    ui->radioButtonIGFManualSelection->setChecked(false);
    ui->pushButtonIGFSelectMeasurements->setEnabled(false);
}
void gLAB_GUI::on_radioButtonIGFManualSelection_clicked(){
    ui->radioButtonIGFManualSelection->setChecked(true);
    ui->radioButtonIGFAutoSelection->setChecked(false);
    ui->pushButtonIGFSelectMeasurements->setEnabled(true);
}
void gLAB_GUI::on_pushButtonIGFSelectMeasurements_clicked(){
    CSAdvancedIGF->setModal(true);
    CSAdvancedIGF->show();
}


// Function to set the cycle-slip defaults
void gLAB_GUI::setCSdefaults() {
    //N-con
    ui->lineEditNcon->setText("3");
    // Phase-Code
    this->on_checkBoxSFConsistencyCheck_clicked(true);
    ui->lineEditSFConsCheckValue->setText("20");
    ui->lineEditSFiniStd->setText("3");
    ui->lineEditSFwindow->setText("300");
    ui->lineEditSFkFactor->setText("5");
    ui->lineEditSFnSample->setText("2");
    this->on_radioButtonSFAutoSelection_clicked();
    CSAdvancedSF->setCSdefaults();
    // Melbourne-Wübbena
    ui->lineEditIntialStdDevMW->setText("2");
    ui->lineEditMWminStd->setText("0.8");
    ui->lineEditMWwindow->setText("300");
    ui->lineEditMWkFactor->setText("5");
    ui->lineEditMWnSample->setText("2");
    this->on_radioButtonMWAutoSelection_clicked();
    CSAdvancedMW->setCSdefaults();
    // Geometry-free
    ui->lineEditLImaxJumpThreshold->setText("1");
    ui->lineEditLImaxThreshold->setText("0.08");
    ui->lineEditLItimeConstant->setText("60");
    ui->lineEditLInSamples->setText("7");
    this->on_radioButtonLIAutoSelection_clicked();
    CSAdvancedLI->setCSdefaults();
    // IGf
    ui->lineEditIGFmaxJumpThreshold->setText("1");
    ui->lineEditIGFmaxThreshold->setText("0.16");
    ui->lineEditIGFtimeConstant->setText("60");
    ui->lineEditIGFnSamples->setText("7");
    this->on_radioButtonIGFAutoSelection_clicked();
    CSAdvancedIGF->setCSdefaults();
}

//Check if user input cycle-slip measurements is valid. Returns 0 if valid, 1 if invalid.
//Function is not assigned to any class so it can be called by all cycle-slip classes
int checkUserInputCycleSlipMeasurement (QString *warningString, QString param, const enum CycleSlipType CStype,const enum CycleSlipParamType paramType, const QRadioButton *MinNoiseButton) {

    QString     csTypeStr[4]={"SF","MW","GF","IGF"};
    QString     complementaryString="used";
    QStringList ParamOpt=param.split("-", QString::SkipEmptyParts);
    QString     measTypeLetter[4][4]={{"C","L","",""},{"C","L","C","L"},{"L","L","",""},{"L","L","L","L"}};
    QString     measTypeLetter2[4][4]={{"L","C","",""},{"L","C","L","C"},{"L","L","",""},{"L","L","L","L"}};
    QString     repeatFreqText[4]={"only one","only one","none","only one"};
    QString     repeatFreqIGFcomplementary="none";
    QString     auxRepeatText[4]={"",""," -except if measurements are provided-",""};
    QString     measTypeTextNeeded[4]={"a code and carrier phase","two codes and two carrier phases","two carrier phases","four carrier phases"};
    QString     measTypeTextNeededIGFcomplementary="three carrier phases";
    int numParam[4][2]={{2,3},{2,5},{2,3},{2,5}};
    int numParamIGFcomplementary[2]={2,4};
    int numFreq[4]={1,2,2,4};
    int numFreqIGFcomplementary=3;
    int maxRepeatedFreq[4]={1,0,0,1};
    int maxRepeatedFreqIGFcomplementary=0;
    int numMeasFreqIGF=2;
    int numMeasFreqIGFcomplementary=1;
    int nOpt=ParamOpt.count();
    int retValue=0;
    int numIter=1;

    if (MinNoiseButton!=nullptr) {
        if (MinNoiseButton->isChecked()) {
            numParam[CStypeIGF][CStypeParamMeas]=4;
            numParamIGFcomplementary[CStypeParamMeas]=5;
            numFreq[CStypeIGF]=3;
            numFreqIGFcomplementary=4;
            maxRepeatedFreq[CStypeIGF]=1;
            maxRepeatedFreqIGFcomplementary=2;
            numMeasFreqIGF=1;
            numMeasFreqIGFcomplementary=2;
            complementaryString="not used";
            repeatFreqText[CStypeIGF]=repeatFreqIGFcomplementary;
            repeatFreqIGFcomplementary="only one";
            measTypeTextNeeded[CStypeIGF]=measTypeTextNeededIGFcomplementary;
            measTypeTextNeededIGFcomplementary="four carrier phases";
        }
    }

    bool ParamSatRanges=param.contains(QRegularExpression(regExpSatWithRanges));
    bool ParamSatNoRanges=ParamOpt[0].contains(QRegularExpression(regExpSatNoRanges));
    if(!ParamSatNoRanges && !ParamSatRanges ) {
       *warningString += "PREPROCESS: Invalid " + csTypeStr[CStype] + " cycle-slip argument '" + param + "'. It was skipped.\n";
       return 1;
    } else if (ParamSatRanges) {
       *warningString += "PREPROCESS: The GUI cannot read arguments with satellite ranges (except '-pre:sat'), as options are constellations wise. Argument '" + param + "' was skipped and not validated (it must be validated in command line).\n";
       return 1;
    }

    for(int iter=0;iter<2;iter++) {
        if (iter==1 && CStype==CStypeIGF) {
            if (retValue==0) break;
            numParam[CStypeIGF][CStypeParamMeas]=numParamIGFcomplementary[CStypeParamMeas];
            numFreq[CStypeIGF]=numFreqIGFcomplementary;
            maxRepeatedFreq[CStypeIGF]=maxRepeatedFreqIGFcomplementary;
            numMeasFreqIGF=numMeasFreqIGFcomplementary;
            repeatFreqText[CStypeIGF]=repeatFreqIGFcomplementary;
            measTypeTextNeeded[CStypeIGF]=measTypeTextNeededIGFcomplementary;
            numIter=2;
            retValue=0;
        } else if (iter==1) break;

        if (numParam[CStype][paramType]!=nOpt) {
            if (CStype!=CStypeIGF || (CStype==CStypeIGF && numIter==2 )) {
                *warningString += "PREPROCESS: " + csTypeStr[CStype] + " cycle-slip argument '" + param + "' has missing frequencies or measurements. It was skipped.\n";
            }
            retValue=1;
            continue;
        }

        QString currPartLower=ParamOpt[1].toLower();
        QString currPartUpper=ParamOpt[1].toUpper();

        if (paramType==CStypeParamFreq) {
            QStringList currPartLowerList=currPartLower.split(".",QString::SkipEmptyParts);
            for(int numfreqList=0;numfreqList<currPartLowerList.count();numfreqList++) {
                QString currPartLowerIter=currPartLowerList.at(numfreqList);
                if (currPartLowerIter.length()!=numFreq[CStype]) {
                    if (CStype!=CStypeIGF || (CStype==CStypeIGF && numIter==2 )) {
                        *warningString += "PREPROCESS: " + csTypeStr[CStype] + " cycle-slip argument '" + param + "' does not have the right number of frequencies. It was skipped.\n";
                    }
                    retValue=1;
                    continue;
                } else if (!currPartLowerIter.contains(QRegularExpression("^[1-9]{" + QString::number(numFreq[CStype]) + "}$"))) {
                    if (CStype!=CStypeIGF || (CStype==CStypeIGF && numIter==2 )) {
                        *warningString += "PREPROCESS: " + csTypeStr[CStype] + " cycle-slip argument '" + param + "' does not have valid frequencies. It was skipped.\n";
                    }
                    retValue=1;
                    continue;
                } else {
                    //Check for repeated frequencies
                    int numRepeated[4]={0};
                    for(int i=0;i<numFreq[CStype];i++) {
                        for(int j=0;j<numFreq[CStype];j++) {
                            if (i==j) continue;
                            if (currPartLowerIter.mid(i,1)==currPartLowerIter.mid(j,1)) {
                                numRepeated[i]++;
                            }
                        }
                    }
                    for(int i=0;i<numFreq[CStype];i++) {
                        if (numRepeated[i]>maxRepeatedFreq[CStype]) {
                            if (CStype!=CStypeIGF || (CStype==CStypeIGF && numIter==2 )) {
                                *warningString += "PREPROCESS: " + csTypeStr[CStype] + " cycle-slip argument '" + param + "' has too many repeated frequencies (" + repeatFreqText[CStype] + " can be repeated" + auxRepeatText[CStype] + "). It was skipped.\n";
                            }
                            retValue=1;
                            break;
                        }
                    }
                    if (retValue==1) continue;
                    if (CStype==CStypeIGF && numFreq[CStypeIGF]==4) {
                        //With IGF and 4 measurements, two frequencies may be repeated (only one may be repeated), which is not allowed
                        int numDoubleRepeated=0;
                        for(int i=0;i<numFreq[CStype];i++) {
                            if (numRepeated[i]==maxRepeatedFreq[CStype]) numDoubleRepeated++;
                        }
                        if (numDoubleRepeated>1) {
                            if (CStype!=CStypeIGF || (CStype==CStypeIGF && numIter==2 )) {
                                *warningString += "PREPROCESS: " + csTypeStr[CStype] + " cycle-slip argument '" + param + "' has too many repeated frequencies (" + repeatFreqText[CStype] + " can be repeated). It was skipped.\n";
                            }
                            retValue=1;
                            continue;
                        }
                    }
                }
            }
        } else {
            int freqMeas[4]={0};
            int numFreq[10]={0};
            int errortype=0;
            //Loop to check the right type of measurements (code or phase) are provided
            for (int iMeas=0;iMeas<numParam[CStype][paramType]-1;iMeas++) {
                freqMeas[iMeas]=ParamOpt[iMeas+1].mid(1,1).toInt();
                if (freqMeas[iMeas]<=0 || freqMeas[iMeas]>9) {
                    retValue=1;
                    break;
                }
                numFreq[freqMeas[iMeas]]++;
                if (measTypeLetter[CStype][iMeas]!=ParamOpt[iMeas+1].toUpper().mid(0,1) ) {
                    retValue=1;
                    errortype=1;
                    break;
                }
            }
            if (retValue==1 && (CStype==CStypeSF || CStype==CStypeMW)) {
                //Loop again and check with the other meas order
                retValue=0;
                for(int k=0;k<10;k++) numFreq[k]=0;
                for(int k=0;k<4;k++) freqMeas[k]=0;
                for (int iMeas=0;iMeas<numParam[CStype][paramType]-1;iMeas++) {
                    freqMeas[iMeas]=ParamOpt[iMeas+1].mid(1,1).toInt();
                    if (freqMeas[iMeas]<=0 || freqMeas[iMeas]>9) {
                        *warningString += "PREPROCESS: " + csTypeStr[CStype] + " cycle-slip argument '" + param + "' has invalid frequencies. It was skipped.\n";
                        retValue=1;
                        break;
                    }
                    numFreq[freqMeas[iMeas]]++;
                    if (measTypeLetter2[CStype][iMeas]!=ParamOpt[iMeas+1].toUpper().mid(0,1) ) {
                        *warningString += "PREPROCESS: " + csTypeStr[CStype] + " cycle-slip argument '" + param + "' does not have " + measTypeTextNeeded[CStype] +". It was skipped.\n";
                        retValue=1;
                        break;
                    }
                }
                if (retValue==1) continue;
            } else if (retValue==1) {
                if (CStype!=CStypeIGF || (CStype==CStypeIGF && numIter==2 )) {
                    if (errortype==0) {
                        *warningString += "PREPROCESS: " + csTypeStr[CStype] + " cycle-slip argument '" + param + "' has invalid frequencies. It was skipped.\n";
                    } else {
                        *warningString += "PREPROCESS: " + csTypeStr[CStype] + " cycle-slip argument '" + param + "' does not have " + measTypeTextNeeded[CStype] +". It was skipped.\n";
                    }
                }
                continue;
            }
            //Check frequencies
            switch(CStype) {
                case CStypeSF:
                    if (numFreq[freqMeas[0]]!=2) {
                        *warningString += "PREPROCESS: " + csTypeStr[CStype] + " cycle-slip argument '" + param + "' does not have both frequencies equal. It was skipped.\n";
                        retValue=1;
                    }
                    break;
                case CStypeMW:
                    if (numFreq[freqMeas[0]]!=2 || freqMeas[0]!=freqMeas[1] || numFreq[freqMeas[2]]!=2 || freqMeas[2]!=freqMeas[3]) {
                        *warningString += "PREPROCESS: " + csTypeStr[CStype] + " cycle-slip argument '" + param + "' does not have two pairs of code and carrier phase measurements with the same frequencies. It was skipped.\n";
                        retValue=1;
                    }
                    break;
                case CStypeLI:
                    if (numFreq[freqMeas[0]]!=1 || numFreq[freqMeas[1]]!=1) {
                        if (ParamOpt[1]==ParamOpt[2]) {
                            *warningString += "PREPROCESS: " + csTypeStr[CStype] + " cycle-slip argument '" + param + "' cannot have the two measurements repeated. It was skipped.\n";
                            retValue=1;
                        }
                    }
                    break;
                case CStypeIGF:
                    //IGF is different as when using 4 frequencies one frequency may be repeated or not
                    if (numMeasFreqIGF==1) {
                        for (int iMeas=0;iMeas<numParam[CStype][paramType]-1;iMeas++) {
                            if (numFreq[freqMeas[iMeas]]!=1) {
                                if (numIter==2) {
                                    *warningString += "PREPROCESS: " + csTypeStr[CStype] + " cycle-slip argument '" + param + " does not have three different frequencies'. It was skipped.\n";
                                }
                                retValue=1;
                                break;
                            }
                        }
                    } else {
                        int numFreqRepeatedTwice=0;
                        for (int iMeas=0;iMeas<numParam[CStype][paramType]-1;iMeas++) {
                            if (numFreq[freqMeas[iMeas]]==2) {
                                numFreqRepeatedTwice++;
                            } else if (numFreq[freqMeas[iMeas]]>2) {
                                if (numIter==2) {
                                    *warningString += "PREPROCESS: " + csTypeStr[CStype] + " cycle-slip argument '" + param + "' does not have or either 4 different frequencies or only repeats one frequency. It was skipped.\n";
                                }
                                retValue=1;
                                break;
                            }
                        }
                        if (retValue==0) {
                            if (numFreqRepeatedTwice>2) {
                                if (numIter==2) {
                                    *warningString += "PREPROCESS: " + csTypeStr[CStype] + " cycle-slip argument '" + param + "' does not have or either 4 different frequencies or only repeats one frequency. It was skipped.\n";
                                }
                                retValue=1;
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if (retValue==0 && numIter==2) {
        *warningString += "PREPROCESS: " + csTypeStr[CStype] + " cycle-slip argument '" + param + "' is invalid for current IGF configuration, but is valid if parameter '-pre:cs:igf:minnoise' is " + complementaryString + ". It was skipped.\n";
        return 1;
    }

    return retValue;
}

//Function to load the SNR value when it is applied in the preprocess tab instead of the SNR "Advanced Mode"
void gLAB_GUI::loadSNRvalue(QString *warningString, QStringList *ParametersList, int SNRtype) {
    QString SNRvalue="",SNRType=SNRtype==MINSNRTYPE?"Min":"Max";
    int SNRIndex=-1,SNRDefault=SNRtype==MINSNRTYPE?4:8;
    int SNRintVal;
    double  SNRdoubleVal;
    bool SNROK=false,SNROKint=false,SNROKdouble=false;
    //get SNR index
    SNRIndex=-1;
    SNRvalue=ParametersList->at(1);
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

    if ( SNROK && SNRIndex!=SNRDefault ) {
        if (SNRtype==MINSNRTYPE) {
            this->on_comboBoxSNRThresholdsMin_currentIndexChanged(SNRIndex);
        } else {
            this->on_comboBoxSNRThresholdsMax_currentIndexChanged(SNRIndex);
        }
        if (SNRIndex==nSNRDef) {
            if (SNRtype==MINSNRTYPE) {
                ui->lineEditUserDefinedSNRMin->setText(SNRvalue);
            } else {
                ui->lineEditUserDefinedSNRMax->setText(SNRvalue);
            }
        }
    }
}

//Function to read '-pre:sat' arguments
void gLAB_GUI::loadgLABSatelliteList (QString option,QString *warningString, QStringList *ParametersList) {
    int LetterPos,StartPRN,EndPRN,HyphenPos;
    int i;
    QString Sign;
    for (int iParam=0; iParam<ParametersList->count(); iParam++) {
        int GNSSFound=0;
        int GNSSselected[MAX_GNSS]={0};
        int allSatAndConst=0;
        QString Param=ParametersList->at(iParam).section(" ", 0,0);
        int currentCharPos;
        LetterPos=0;
        Sign=RedColor;
        if (Param.at(0)=='+') {
            LetterPos=1;
            Sign=GreenColor;
        } else if (Param.at(0)=='-' ) {
            LetterPos=1;
            Sign=RedColor;
        }
        //Get constellations
        if (Param.at(LetterPos)=='0') {
            for (int iGNSS=0;iGNSS<MAX_GNSS;iGNSS++) GNSSselected[iGNSS]=1;
            GNSSFound=1;
            allSatAndConst=1;
            currentCharPos=LetterPos+1;
            if (Param.count()>currentCharPos) {
                *warningString += "PREPROCESS: Parameter '" + option + "' cannot have constellation or PRN numbers if a single '0' is used for all constellations and PRNs in argument '" + Param + "'. It was skipped.\n";
                continue;
            }
        } else {
            for (currentCharPos=LetterPos;currentCharPos<Param.count();currentCharPos++) {
                if (checkConstellationQChar(Param.at(currentCharPos))==1) {
                    enum GNSSystem system = gnssQchar2gnsstype(Param.at(currentCharPos));
                    GNSSselected[system]=1;
                    GNSSFound=1;
                } else {
                    if (!Param.mid(currentCharPos,1).contains(QRegularExpression("[0-9]"))) {
                        *warningString += "PREPROCESS: Parameter '" + option + "' does not have a valid constellation in argument '" + Param + "'. It was skipped.\n";
                    } else {
                        break;
                    }
                }
            }
        }
        if (GNSSFound==0) continue;

        for (int iGNSS=0;iGNSS<MAX_GNSS;iGNSS++) {
            enum GNSSystem system = GNSSenums[iGNSS];
            QStringList ParamDots;
            if (GNSSselected[iGNSS]==0) continue;
            if (currentCharPos>=Param.count()) {
                if (Param!="+0" && Param!="-0" && Param!="0") {
                   *warningString += "PREPROCESS: Parameter '" + option + "' does not have PRN numbers in argument '" + Param + "'. It was skipped.\n";
                   break;
                } else {
                    ParamDots.append(Param);
                }
            } else {
                ParamDots=Param.mid(currentCharPos).split(".",QString::SkipEmptyParts);
            }
            for(int PRNrangeNum=0;PRNrangeNum<ParamDots.size();PRNrangeNum++) {
                HyphenPos=ParamDots.at(PRNrangeNum).indexOf("-",1);
                if (HyphenPos!=-1) {
                    StartPRN=ParamDots.at(PRNrangeNum).mid(0, HyphenPos).toInt();
                    EndPRN=ParamDots.at(PRNrangeNum).mid(HyphenPos+1).toInt();
                    if (iGNSS!=GEO && (StartPRN<0 || StartPRN>listMaxSatGNSS[iGNSS])) {
                        *warningString += "PREPROCESS: Parameter '" + option + "' only admits PRN numbers from 0 to " + QString("%1").arg(listMaxSatGNSS[iGNSS]) + " for " + GNSSName[iGNSS] + ". It was skipped.\n";
                    } else if (iGNSS==GEO && (StartPRN<0 || (StartPRN>0 && StartPRN<GEOMINPRN) || StartPRN>(listMaxSatGNSS[iGNSS]+GEOMINPRNOFFSET))) {
                        *warningString += "PREPROCESS: Parameter '" + option + "' only admits PRN number 0 and numbers from 20 to 58 for GEO. It was skipped.\n";
                    } else if (iGNSS!=GEO && (EndPRN<=0 || EndPRN>listMaxSatGNSS[iGNSS])) {
                        *warningString += "PREPROCESS: Parameter '" + option + "' only admits PRN numbers from 0 to " + QString("%1").arg(listMaxSatGNSS[iGNSS]) + " for " + GNSSName[iGNSS] + ". It was skipped.\n";
                    } else if (iGNSS==GEO && (EndPRN<0 || (EndPRN>0 && EndPRN<GEOMINPRN) || EndPRN>(listMaxSatGNSS[iGNSS]+GEOMINPRNOFFSET))) {
                        *warningString += "PREPROCESS: Parameter '" + option + "' only admits PRN number 0 and numbers from 20 to 58 for GEO. It was skipped.\n";
                    } else {
                        if (StartPRN==0) {
                            StartPRN=1;
                            EndPRN=listMaxSatGNSS[iGNSS];
                        } else if (iGNSS==GEO) {
                            StartPRN-=GEOMINPRNOFFSET;
                            EndPRN-=GEOMINPRNOFFSET;
                        }
                        if (Sign==GreenColor) {
                            (this->*PushButtonSelectFunctions[iGNSS])();
                            PushButtonConstWidgets[iGNSS]->setEnabled(true);
                        }
                        for(i=StartPRN;i<=EndPRN;i++) {
                            callSatellitePushButtonFunction(system,i,Sign);
                        }
                        if (Sign==RedColor && StartPRN==1 && EndPRN==listMaxSatGNSS[iGNSS]) {
                            (this->*CheckBoxGNSSFunctions[iGNSS])(false);
                        } else {
                            (this->*PushButtonSelectFunctions[iGNSS])();
                        }
                    }
                } else {
                    if (allSatAndConst==1) {
                        StartPRN=0;
                    } else {
                        StartPRN=ParamDots.at(PRNrangeNum).mid(0).toInt();
                    }
                    if (iGNSS!=GEO && (StartPRN<0 || StartPRN>listMaxSatGNSS[iGNSS])) {
                        *warningString += "PREPROCESS: Parameter '" + option + "' only admits PRN numbers from 0 to " + QString("%1").arg(listMaxSatGNSS[iGNSS]) + " for " + GNSSName[iGNSS] + ". It was skipped.\n";
                    } else if (iGNSS==GEO && (StartPRN<0 || (StartPRN>0 && StartPRN<GEOMINPRN) || StartPRN>(listMaxSatGNSS[iGNSS]+GEOMINPRNOFFSET))) {
                        *warningString += "PREPROCESS: Parameter '" + option + "' only admits PRN number 0 and numbers from 20 to 58 for GEO. It was skipped.\n";
                    } else {
                        if (StartPRN==0) {
                            StartPRN=1;
                            EndPRN=listMaxSatGNSS[iGNSS];
                        } else if (iGNSS==GEO) {
                            StartPRN-=GEOMINPRNOFFSET;
                            EndPRN=StartPRN;
                        } else {
                            EndPRN=StartPRN;
                        }
                        if (Sign==GreenColor) {
                            (this->*PushButtonSelectFunctions[iGNSS])();
                            PushButtonConstWidgets[iGNSS]->setEnabled(true);
                        }
                        for(i=StartPRN;i<=EndPRN;i++) {
                            callSatellitePushButtonFunction(system,i,Sign);
                        }
                        if (Sign==RedColor && StartPRN==1 && EndPRN==listMaxSatGNSS[iGNSS]) {
                            (this->*CheckBoxGNSSFunctions[iGNSS])(false);
                        } else {
                            (this->*PushButtonSelectFunctions[iGNSS])();
                        }
                    }
                }
            }
        }
    }
}

//Function to check minimum and maximum SNR thresholds
void gLAB_GUI::checkMinMaxSNRThresholds(QString *errorString) {

    double minSNR,maxSNR;

    if ( ui->checkBoxSNRMinAdvancedMode->isChecked()==false && ui->checkBoxSNRMaxAdvancedMode->isChecked()==false ) {
        if (ui->comboBoxSNRThresholdsMin->currentIndex()==9) {
            minSNR=ui->lineEditUserDefinedSNRMin->text().toDouble();
        } else {
            minSNR=ui->comboBoxSNRThresholdsMin->currentText().toDouble();
        }
        if (ui->comboBoxSNRThresholdsMax->currentIndex()==9) {
            maxSNR=ui->lineEditUserDefinedSNRMax->text().toDouble();
        } else {
            maxSNR=ui->comboBoxSNRThresholdsMax->currentText().toDouble();
        }

        if (minSNR>=maxSNR) {
            *errorString += "PREPROCESS: Global minimum SNR (" + QString::number(minSNR) + ") is equal or greater than the global maximum SNR (" + QString::number(maxSNR) + ").\n";
        }
    } else if ( ui->checkBoxSNRMinAdvancedMode->isChecked()==true && ui->checkBoxSNRMaxAdvancedMode->isChecked()==false ) {
        if (ui->comboBoxSNRThresholdsMax->currentIndex()==9) {
            maxSNR=ui->lineEditUserDefinedSNRMax->text().toDouble();
        } else {
            maxSNR=ui->comboBoxSNRThresholdsMax->currentText().toDouble();
        }
        for (int i=0; i<MAX_GNSS; i++) {
            //check if this constellation is selected
            if (CheckBoxGNSS[i]->isChecked()==false) continue;
            //Check default constellation SNR
            if (SnrAdvancedMinWin->ComboBoxGNSSDefaultSNR[0][i]->currentIndex()<9) {
                minSNR=SnrAdvancedMinWin->ComboBoxGNSSDefaultSNR[0][i]->currentText().toDouble();
            } else {
                minSNR=SnrAdvancedMinWin->LineEditGNSSDefaultSNR[0][i]->text().toDouble();
            }
            if(minSNR>=maxSNR) {
                *errorString += "PREPROCESS: " + GNSSName[i] + " default minimum SNR (" + QString::number(minSNR) + ") is equal or greater than the global maximum SNR (" + QString::number(maxSNR) + ").\n";
            }
            //Check per frequency SNR
            for (int j=0; j<nFreqGNSS[i]; j++) {
                for (int k=0; k<2; k++) {
                    if ( k==0 || SnrAdvancedMinWin->ComboBoxGNSSMeas[0][i][j][0]->currentIndex()!=0 ) {
                        if (SnrAdvancedMinWin->ComboBoxGNSSSNR[0][i][j][k]->currentIndex()!=0) {
                            if (SnrAdvancedMinWin->ComboBoxGNSSSNR[0][i][j][k]->currentIndex()<10) {
                                minSNR=SnrAdvancedMinWin->ComboBoxGNSSSNR[0][i][j][k]->currentText().toDouble();
                            } else {
                                minSNR=SnrAdvancedMinWin->LineEditGNSSSNR[0][i][j][k]->text().toDouble();
                            }
                            if (minSNR>=maxSNR) {
                                *errorString += "PREPROCESS: " + GNSSName[i] + " " + " F" + FreqGNSSList[i][j] + " Meas " + QString::number(k+1) + " minimum SNR (" + QString::number(minSNR) + ") is equal or greater than the global maximum SNR (" + QString::number(maxSNR) + ").\n";
                            }
                        }

                    }
                }
            }
        }
    } else if (ui->checkBoxSNRMinAdvancedMode->isChecked()==false && ui->checkBoxSNRMaxAdvancedMode->isChecked()==true ) {
        if (ui->comboBoxSNRThresholdsMin->currentIndex()==9) {
            minSNR=ui->lineEditUserDefinedSNRMin->text().toDouble();
        } else {
            minSNR=ui->comboBoxSNRThresholdsMin->currentText().toDouble();
        }
        for (int i=0; i<MAX_GNSS; i++) {
            //check if this constellation is selected
            if (CheckBoxGNSS[i]->isChecked()==false) continue;
            //Check default constellation SNR
            if (SnrAdvancedMaxWin->ComboBoxGNSSDefaultSNR[1][i]->currentIndex()<9) {
                maxSNR=SnrAdvancedMaxWin->ComboBoxGNSSDefaultSNR[1][i]->currentText().toDouble();
            } else {
                maxSNR=SnrAdvancedMaxWin->LineEditGNSSDefaultSNR[1][i]->text().toDouble();
            }
            if(minSNR>=maxSNR) {
                *errorString += "PREPROCESS: Global minimum SNR (" + QString::number(minSNR) + ") is equal or greater than the " + GNSSName[i] + " default maximum SNR (" + QString::number(maxSNR) + ").\n";
            }
            //Check per frequency SNR
            for (int j=0; j<nFreqGNSS[i]; j++) {
                for (int k=0; k<2; k++) {
                    if ( k==0 || SnrAdvancedMaxWin->ComboBoxGNSSMeas[1][i][j][0]->currentIndex()!=0 ) {
                        if (SnrAdvancedMaxWin->ComboBoxGNSSSNR[1][i][j][k]->currentIndex()!=0) {
                            if (SnrAdvancedMaxWin->ComboBoxGNSSSNR[1][i][j][k]->currentIndex()<10) {
                                maxSNR=SnrAdvancedMaxWin->ComboBoxGNSSSNR[1][i][j][k]->currentText().toDouble();
                            } else {
                                maxSNR=SnrAdvancedMaxWin->LineEditGNSSSNR[1][i][j][k]->text().toDouble();
                            }
                            if (minSNR>=maxSNR) {
                                *errorString += "PREPROCESS: Global minimum SNR (" + QString::number(minSNR) + ") is equal or greater than the " + GNSSName[i] + " F" + FreqGNSSList[i][j] + " Meas " + QString::number(k+1) + " maximum SNR (" + QString::number(maxSNR) + ").\n";
                            }
                        }

                    }
                }
            }
        }
    } else {
        GNSS_SNR_Advanced *SNRclasses[2] = {SnrAdvancedMinWin,SnrAdvancedMaxWin};
        double  *SNRthresholds[2]= {&minSNR,&maxSNR};
        for (int i=0; i<MAX_GNSS; i++) {
            if (CheckBoxGNSS[i]->isChecked()==false) continue;
            for(int SNRtype=0;SNRtype<2;SNRtype++) {
                //check if this constellation is selected
                if (CheckBoxGNSS[i]->isChecked()==false) continue;
                //Check default constellation SNR
                if (SNRclasses[SNRtype]->ComboBoxGNSSDefaultSNR[SNRtype][i]->currentIndex()<9) {
                    *SNRthresholds[SNRtype]=SNRclasses[SNRtype]->ComboBoxGNSSDefaultSNR[SNRtype][i]->currentText().toDouble();
                } else {
                    *SNRthresholds[SNRtype]=SNRclasses[SNRtype]->LineEditGNSSDefaultSNR[SNRtype][i]->text().toDouble();
                }
            }
            if(minSNR>=maxSNR) {
                *errorString += "PREPROCESS: " + GNSSName[i] + " default minimum SNR (" + QString::number(minSNR) + ") is equal or greater than its default maximum SNR (" + QString::number(maxSNR) + ").\n";
            }
            //Check per frequency SNR
            for (int j=0; j<nFreqGNSS[i]; j++) {
                for (int k=0; k<2; k++) {
                    minSNR=maxSNR=-1;
                    for(int SNRtype=0;SNRtype<2;SNRtype++) {
                        if ( k==0 || SNRclasses[SNRtype]->ComboBoxGNSSMeas[SNRtype][i][j][0]->currentIndex()!=0 ) {
                            if (SNRclasses[SNRtype]->ComboBoxGNSSSNR[SNRtype][i][j][k]->currentIndex()!=0) {
                                if (SNRclasses[SNRtype]->ComboBoxGNSSSNR[SNRtype][i][j][k]->currentIndex()<10) {
                                    *SNRthresholds[SNRtype]=SNRclasses[SNRtype]->ComboBoxGNSSSNR[SNRtype][i][j][k]->currentText().toDouble();
                                } else {
                                    *SNRthresholds[SNRtype]=SNRclasses[SNRtype]->LineEditGNSSSNR[SNRtype][i][j][k]->text().toDouble();
                                }
                            }
                        }
                    }
                    if (minSNR<0 && maxSNR>0) {
                        //If maximum SNR is set for a measurement but not its minimum, use the default minimum SNR value
                        if (SnrAdvancedMinWin->ComboBoxGNSSDefaultSNR[0][i]->currentIndex()<9) {
                            minSNR=SnrAdvancedMinWin->ComboBoxGNSSDefaultSNR[0][i]->currentText().toDouble();
                        } else {
                            minSNR=SnrAdvancedMinWin->LineEditGNSSDefaultSNR[0][i]->text().toDouble();
                        }
                        if (minSNR>=maxSNR) {
                            *errorString += "PREPROCESS: " + GNSSName[i] + " default minimum SNR (" + QString::number(minSNR) + ") is equal or greater than the F" + FreqGNSSList[i][j] + " Meas " + QString::number(k+1) + " maximum SNR (" + QString::number(maxSNR) + ").\n";
                        }
                    } else if (minSNR>0 && maxSNR<0) {
                        //If minimum SNR is set for a measurement but not its maximum, use the default maximum SNR value
                        if (SnrAdvancedMinWin->ComboBoxGNSSDefaultSNR[1][i]->currentIndex()<9) {
                            maxSNR=SnrAdvancedMaxWin->ComboBoxGNSSDefaultSNR[1][i]->currentText().toDouble();
                        } else {
                            maxSNR=SnrAdvancedMaxWin->LineEditGNSSDefaultSNR[1][i]->text().toDouble();
                        }
                        if (minSNR>=maxSNR) {
                            *errorString += "PREPROCESS: " + GNSSName[i] + " F" + FreqGNSSList[i][j] + " Meas " + QString::number(k+1) + " minimum SNR (" + QString::number(minSNR) + ") is equal or greater than the default maximum SNR (" + QString::number(maxSNR) + ").\n";
                        }
                    } else if (minSNR>=maxSNR && minSNR>0 && maxSNR>0) {
                        *errorString += "PREPROCESS: " + GNSSName[i] + " F" + FreqGNSSList[i][j] + " Meas " + QString::number(k+1) + " minimum SNR (" + QString::number(minSNR) + ") is equal or greater than its maximum SNR (" + QString::number(maxSNR) + ").\n";
                    }
                }
            }
        }
    }
}

// Function to get the PREPROCESS options and errors
void gLAB_GUI::getPreprocessOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString) {
    int         i,j;
    int         conditionsmet;
    int         badDate=0;
    int         FirstSat,lastSat,StartedGroup;
    int         listConstFullEnabled[MAX_GNSS]={0,0,0,0,0,0,0};
    int         listConstFullDisabled[MAX_GNSS]={0,0,0,0,0,0,0};
    int         listConstPartiallyEnabled[MAX_GNSS]={0,0,0,0,0,0,0};
    int         numListConstFullEnabled=0;
    int         numListConstFullDisabled=0;
    int         numListConstPartiallyEnabled=0;
    int         numSatEnabled=0;
    int         numSatDisabled=0;
    int         currentMode=0;  //Current processing mode
    int         FirstRange=1;
    int         PRNoffset;
    int         anyCSparam=0;
    int         SmoothAuto=0;
    int         SNRerror=0;
    QDate       date;
    QTime       time;
    QString     RtcmNavMode;
    const int   listMaxSatGNSS[MAX_GNSS]={MAX_SAT_GPS,MAX_SAT_GAL,MAX_SAT_GLO,MAX_SAT_GEO,MAX_SAT_BDS,MAX_SAT_QZS,MAX_SAT_IRN};

    //Get positioning mode
    if (ui->groupBoxSbas->isChecked()==true) {
        if (ui->comboBoxSbasInput->currentIndex()==0) {
            currentMode=SBAS1FNAVMODE;
        } else {
            currentMode=SBASDFMCNAVMODE;
        }
    } else if (ui->groupBoxReferenceStation->isChecked()==true) {
        currentMode=DGNSSNAVMODE;
    } else if (mode==1) {
        currentMode=PPPNAVMODE;
    } else {
        currentMode=SPPNAVMODE;
    }

    if (mode==0 && ui->groupBoxSbas->isChecked()==false)

    *warningString = *warningString + ""; //This is to avoid the unused parameter warning
    // Header of the Preprocess section
    *saveString += "\n";
    *saveString += "###################################################\n";
    *saveString += "#     PREPROCESS section\n";
    *saveString += "###################################################\n\n";
    // A priori Receiver Position From:
    if ( ui->radioButtonRinex->isChecked() == true ) {
        //RINEX position is the default in gLAB, no need to set the argument
        if (WriteAllParameters==1) {
            *saveString += "-pre:setrecpos RINEX\n";
            *runString << "-pre:setrecpos" << "RINEX";
        }
    } else if ( ui->radioButtonCalculate->isChecked() == true ) {
        if (ui->checkBoxReferencePositionFileCalculate->isChecked()==true) {
            if (ui->lineEditInterpolationDegreeRefFileCalculate->text()=="") {
                *errorString += "INPUT: Reference position interpolation degree is a required input if 'Reference Position File:' is set in 'Calculate' mode [In the Input Section - A Priori Receiver Position From] .\n";
            } else {
                if (ui->lineEditInterpolationDegreeRefFileCalculate->text().toInt()==0) {
                    //Default interpolation value is 0
                    if (WriteAllParameters==1) {
                        *saveString += "-pre:refpos:deg " + ui->lineEditInterpolationDegreeRefFileCalculate->text() + "\n";
                        *runString << "-pre:refpos:deg" << ui->lineEditInterpolationDegreeRefFileCalculate->text();
                    }
                } else {
                    *saveString += "-pre:refpos:deg " + ui->lineEditInterpolationDegreeRefFileCalculate->text() + "\n";
                    *runString << "-pre:refpos:deg" << ui->lineEditInterpolationDegreeRefFileCalculate->text();
                }
            }
        }
        if ( ui->radioButtonCalculateEarthCentre->isChecked() == true ) {
            if (ui->checkBoxReferencePositionFileCalculate->isChecked()==true) {
                if (WriteAllParameters==1) {
                    //calculateRef mode is the default when an input ref file is set
                    *saveString += "-pre:setrecpos calculateRef\n";
                    *runString << "-pre:setrecpos" << "calculateRef";
                }
            } else {
                *saveString += "-pre:setrecpos calculate\n";
                *runString << "-pre:setrecpos" << "calculate";
            }

        } else if ( ui->radioButtonCalculateRinex->isChecked() == true ) {
            if (ui->checkBoxReferencePositionFileCalculate->isChecked()==true) {
                *saveString += "-pre:setrecpos calculateRINEXRef\n";
                *runString << "-pre:setrecpos" << "calculateRINEXRef";
            } else {
                *saveString += "-pre:setrecpos calculateRINEX\n";
                *runString << "-pre:setrecpos" << "calculateRINEX";
            }
        } else if ( ui->radioButtonCalculateSpecify->isChecked() == true ) {
            if (ui->radioButtonCalculateSpecifyCartesian->isChecked()==true) {
                if ( ui->lineEditCalculateSpecifyX->text() == "" || ui->lineEditCalculateSpecifyY->text() == "" || ui->lineEditCalculateSpecifyZ->text() == "" ) {
                    *errorString += "INPUT: X Y and Z coordinates are required inputs if 'Calculate - User defined' is set [In the Input Section - A Priori Receiver Position From].\n";
                } else if ( ui->lineEditCalculateSpecifyX->text().toDouble() == 0. || ui->lineEditCalculateSpecifyY->text().toDouble() == 0. || ui->lineEditCalculateSpecifyZ->text().toDouble() == 0. ) {
                        *errorString += "INPUT: X Y and Z coordinates cannot be 0,0,0.\n";
                } else {
                    if (ui->checkBoxReferencePositionFileCalculate->isChecked()==true) {
                        *saveString += "-pre:setrecpos calculateUSERRef " + ui->lineEditCalculateSpecifyX->text() + " " + ui->lineEditCalculateSpecifyY->text() + " " + ui->lineEditCalculateSpecifyZ->text() + "\n";
                        *runString << "-pre:setrecpos" << "calculateUSERRef" << ui->lineEditCalculateSpecifyX->text() << ui->lineEditCalculateSpecifyY->text() << ui->lineEditCalculateSpecifyZ->text();
                    } else {
                        *saveString += "-pre:setrecpos calculateUSER " + ui->lineEditCalculateSpecifyX->text() + " " + ui->lineEditCalculateSpecifyY->text() + " " + ui->lineEditCalculateSpecifyZ->text() + "\n";
                        *runString << "-pre:setrecpos" << "calculateUSER" << ui->lineEditCalculateSpecifyX->text() << ui->lineEditCalculateSpecifyY->text() << ui->lineEditCalculateSpecifyZ->text();
                    }
                }
            } else {
                if ( ui->lineEditCalculateSpecifyLon->text() == "" || ui->lineEditCalculateSpecifyLat->text() == "" || ui->lineEditCalculateSpecifyHeight->text() == "" ) {
                    *errorString += "INPUT: Longitude, latitude and height coordinates are required inputs if 'Calculate - User defined' is set [In the Input Section - A Priori Receiver Position From].\n";
                } else if  (ui->lineEditCalculateSpecifyLon->text().toDouble()<-180. || ui->lineEditCalculateSpecifyLon->text().toDouble()>180) {
                        *errorString += "INPUT: Longitude coordinate must be in the range [-180..180] degrees.\n";
                } else if  (ui->lineEditCalculateSpecifyLat->text().toDouble()<-90. || ui->lineEditCalculateSpecifyLat->text().toDouble()>90) {
                        *errorString += "INPUT: Latitude coordinate must be in the range [-90..90] degrees.\n";
                } else if ( ui->lineEditCalculateSpecifyHeight->text().toDouble() < -10000. ) {
                        *errorString += "INPUT: Height coordinate cannot be lower than -10 kilometres.\n";
                } else {
                    if (ui->checkBoxReferencePositionFileCalculate->isChecked()==true) {
                        *saveString += "-pre:setrecpos calculateUSERGeodRef " + ui->lineEditCalculateSpecifyLon->text() + " " + ui->lineEditCalculateSpecifyLat->text() + " " + ui->lineEditCalculateSpecifyHeight->text() + "\n";
                        *runString << "-pre:setrecpos" << "calculateUSERGeodRef" << ui->lineEditCalculateSpecifyLon->text() << ui->lineEditCalculateSpecifyLat->text() << ui->lineEditCalculateSpecifyHeight->text();
                    } else {
                        *saveString += "-pre:setrecpos calculateUSERGeod " + ui->lineEditCalculateSpecifyLon->text() + " " + ui->lineEditCalculateSpecifyLat->text() + " " + ui->lineEditCalculateSpecifyHeight->text() + "\n";
                        *runString << "-pre:setrecpos" << "calculateUSERGeod" << ui->lineEditCalculateSpecifyLon->text() << ui->lineEditCalculateSpecifyLat->text() << ui->lineEditCalculateSpecifyHeight->text();
                    }
                }
            }
        }
    } else if ( ui->radioButtonSinex->isChecked() == true ) {
        *saveString += "-pre:setrecpos SINEX\n";
        *runString << "-pre:setrecpos" << "SINEX";
    } else if ( ui->radioButtonRtcm->isChecked() == true ) {
        if ((ui->radioButtonRtcmSpecify->isChecked()==true || ui->radioButtonRtcmUserSpecify->isChecked()==true) && ui->radioButtonRtcmReferenceFile->isChecked()==true) {
            if (ui->radioButtonRtcmSpecify->isChecked()==true) {
                RtcmNavMode="Specify Rover";
            } else {
                RtcmNavMode="User Ref. & Rover";
            }
            if (ui->lineEditInterpolationDegreeRefFileRtcm->text()=="") {
                *errorString += "INPUT: Reference position interpolation degree is a required input if 'Reference file:' is set in '" + RtcmNavMode + "' mode [In the Input Section - A Priori Receiver Position From] .\n";
            } else {
                if (ui->lineEditInterpolationDegreeRefFileRtcm->text().toInt()==0) {
                    //Default interpolation value is 0
                    if (WriteAllParameters==1) {
                        *saveString += "-pre:refpos:deg " + ui->lineEditInterpolationDegreeRefFileRtcm->text() + "\n";
                        *runString << "-pre:refpos:deg" << ui->lineEditInterpolationDegreeRefFileRtcm->text();
                    }
                } else {
                    *saveString += "-pre:refpos:deg " + ui->lineEditInterpolationDegreeRefFileRtcm->text() + "\n";
                    *runString << "-pre:refpos:deg" << ui->lineEditInterpolationDegreeRefFileRtcm->text();
                }
            }
        }
        if ( ui->radioButtonRtcmBaseline->isChecked() == true ) {
            //DGNSS Baseline is the default for DGNSS, no need to set the argument
             if (WriteAllParameters==1) {
                *saveString += "-pre:setrecpos DGNSSbaseline\n";
                *runString << "-pre:setrecpos" << "DGNSSbaseline";
             }
        } else if ( ui->radioButtonRtcmRinexRover->isChecked() == true ) {
            *saveString += "-pre:setrecpos DGNSSRinexRover\n";
            *runString << "-pre:setrecpos" << "DGNSSRinexRover";
        } else if ( ui->radioButtonRtcmSpecify->isChecked() == true ) {
                if ( ui->radioButtonRtcmUserDefined->isChecked()==true ) {
                    if (ui->radioButtonRtcmRecCartesian->isChecked()==true) {
                        if ( ui->lineEditAprioriRecPosRtcmSpecifyX->text() == "" || ui->lineEditAprioriRecPosRtcmSpecifyY->text() == "" || ui->lineEditAprioriRecPosRtcmSpecifyZ->text() == "" ) {
                            *errorString += "INPUT: Rover X Y and Z coordinates are required inputs if 'DGNSS - Specify Rover - User defined' is set [In the Input Section - A Priori Receiver Position From].\n";
                        } else if ( ui->lineEditAprioriRecPosRtcmSpecifyX->text().toDouble() == 0. || ui->lineEditAprioriRecPosRtcmSpecifyY->text().toDouble() == 0. || ui->lineEditAprioriRecPosRtcmSpecifyZ->text().toDouble() == 0. ) {
                            *errorString += "INPUT: Rover X Y and Z coordinates cannot be 0,0,0.\n";
                        } else {
                            *saveString += "-pre:setrecpos DGNSSRoverUSER " + ui->lineEditAprioriRecPosRtcmSpecifyX->text() + " " + ui->lineEditAprioriRecPosRtcmSpecifyY->text() + " " + ui->lineEditAprioriRecPosRtcmSpecifyZ->text() + "\n";
                            *runString << "-pre:setrecpos" << "DGNSSRoverUSER" << ui->lineEditAprioriRecPosRtcmSpecifyX->text() << ui->lineEditAprioriRecPosRtcmSpecifyY->text() << ui->lineEditAprioriRecPosRtcmSpecifyZ->text();
                        }
                    } else {
                        if ( ui->lineEditAprioriRecPosRtcmSpecifyLon->text() == "" || ui->lineEditAprioriRecPosRtcmSpecifyLat->text() == "" || ui->lineEditAprioriRecPosRtcmSpecifyHeight->text() == "" ) {
                            *errorString += "INPUT: Longitude, latitude and height coordinates are required inputs if 'DGNSS - Specify Rover - User defined' is set [In the Input Section - A Priori Receiver Position From].\n";
                        } else if  (ui->lineEditAprioriRecPosRtcmSpecifyLon->text().toDouble()<-180. || ui->lineEditAprioriRecPosRtcmSpecifyLon->text().toDouble()>180) {
                                *errorString += "INPUT: Longitude coordinate must be in the range [-180..180] degrees.\n";
                        } else if  (ui->lineEditAprioriRecPosRtcmSpecifyLat->text().toDouble()<-90. || ui->lineEditAprioriRecPosRtcmSpecifyLat->text().toDouble()>90) {
                                *errorString += "INPUT: Latitude coordinate must be in the range [-90..90] degrees.\n";
                        } else if ( ui->lineEditAprioriRecPosRtcmSpecifyHeight->text().toDouble() < -10000. ) {
                                *errorString += "INPUT: Height coordinate cannot be lower than -10 kilometres.\n";
                        } else {
                                *saveString += "-pre:setrecpos DGNSSRoverUSERGeod " + ui->lineEditAprioriRecPosRtcmSpecifyLon->text() + " " + ui->lineEditAprioriRecPosRtcmSpecifyLat->text() + " " + ui->lineEditAprioriRecPosRtcmSpecifyHeight->text() + "\n";
                                *runString << "-pre:setrecpos" << "DGNSSRoverUSERGeod" << ui->lineEditAprioriRecPosRtcmSpecifyLon->text() << ui->lineEditAprioriRecPosRtcmSpecifyLat->text() << ui->lineEditCalculateSpecifyHeight->text();
                        }
                    }
                } else {
                    *saveString += "-pre:setrecpos DGNSSRoverUSERRef\n";
                    *runString << "-pre:setrecpos" << "DGNSSRoverUSERRef";
                }
        } else if ( ui->radioButtonRtcmUserBaseline->isChecked() == true ) {
            if (ui->radioButtonRtcmRefCartesian->isChecked()==true) {
                if ( ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() == "" ) {
                    *errorString += "INPUT: Reference Station X Y and Z coordinates are required inputs if 'DGNSS - User Baseline' is set [In the Input Section - A Priori Receiver Position From].\n";
                } else if (ui->lineEditAprioriRefRecPosRtcmSpecifyX->text().toDouble() == 0. || ui->lineEditAprioriRefRecPosRtcmSpecifyY->text().toDouble() == 0. || ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text().toDouble() == 0.) {
                    *errorString += "INPUT: Reference Station X Y and Z coordinates cannot be 0,0,0.\n";
                } else {
                    *saveString += "-pre:setrecpos DGNSSUserbaseline " + ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() + "\n";
                    *runString << "-pre:setrecpos" << "DGNSSUserbaseline" << ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text();
                }
            } else {
                if ( ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() == "" ) {
                    *errorString += "INPUT: Longitude, latitude and height coordinates are required inputs if 'DGNSS - User Baseline' is set [In the Input Section - A Priori Receiver Position From].\n";
                } else if  (ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text().toDouble()<-180. || ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text().toDouble()>180) {
                        *errorString += "INPUT: Longitude coordinate must be in the range [-180..180] degrees.\n";
                } else if  (ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text().toDouble()<-90. || ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text().toDouble()>90) {
                        *errorString += "INPUT: Latitude coordinate must be in the range [-90..90] degrees.\n";
                } else if ( ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text().toDouble() < -10000. ) {
                        *errorString += "INPUT: Height coordinate cannot be lower than -10 kilometres.\n";
                } else {
                        *saveString += "-pre:setrecpos DGNSSUserGeodbaseline " + ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() + "\n";
                        *runString << "-pre:setrecpos" << "DGNSSUserGeodbaseline" << ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text();
                }
            }
        } else if ( ui->radioButtonRtcmUserRinexRover->isChecked() == true ) {
            if (ui->radioButtonRtcmRefCartesian->isChecked()==true) {
                if ( ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() == "" ) {
                    *errorString += "INPUT: Reference Station X Y and Z coordinates are required inputs if 'DGNSS - User RINEX Rover' is set [In the Input Section - A Priori Receiver Position From].\n";
                } else if (ui->lineEditAprioriRefRecPosRtcmSpecifyX->text().toDouble() == 0. || ui->lineEditAprioriRefRecPosRtcmSpecifyY->text().toDouble() == 0. || ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text().toDouble() == 0.) {
                    *errorString += "INPUT: Reference Station X Y and Z coordinates cannot be 0,0,0.\n";
                } else {
                    *saveString += "-pre:setrecpos DGNSSUserRinexRover " + ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() + "\n";
                    *runString << "-pre:setrecpos" << "DGNSSUserRinexRover" << ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text();
                }
            } else {
                if ( ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() == "" ) {
                    *errorString += "INPUT: Longitude, latitude and height coordinates are required inputs if 'DGNSS - User RINEX Rover' is set [In the Input Section - A Priori Receiver Position From].\n";
                } else if  (ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text().toDouble()<-180. || ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text().toDouble()>180) {
                        *errorString += "INPUT: Longitude coordinate must be in the range [-180..180] degrees.\n";
                } else if  (ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text().toDouble()<-90. || ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text().toDouble()>90) {
                        *errorString += "INPUT: Latitude coordinate must be in the range [-90..90] degrees.\n";
                } else if ( ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text().toDouble() < -10000. ) {
                        *errorString += "INPUT: Height coordinate cannot be lower than -10 kilometres.\n";
                } else {
                        *saveString += "-pre:setrecpos DGNSSUserGeodRinexRover " + ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() + "\n";
                        *runString << "-pre:setrecpos" << "DGNSSUserGeodRinexRover" << ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text();
                }
            }
        } else if ( ui->radioButtonRtcmUserSpecify->isChecked() == true ) {
            conditionsmet=1;
            if (ui->radioButtonRtcmRefCartesian->isChecked()==true) {
                if ( ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() == "" ) {
                    *errorString += "INPUT: Reference Station X Y and Z coordinates are required inputs if 'DGNSS - User Ref. & Rover' is set [In the Input Section - A Priori Receiver Position From].\n";
                    conditionsmet=0;
                } else if (ui->lineEditAprioriRefRecPosRtcmSpecifyX->text().toDouble() == 0. || ui->lineEditAprioriRefRecPosRtcmSpecifyY->text().toDouble() == 0. || ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text().toDouble() == 0.) {
                    *errorString += "INPUT: Reference Station X Y and Z coordinates cannot be 0,0,0.\n";
                    conditionsmet=0;
                }
            } else {
                if ( ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() == "" || ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() == "" ) {
                    *errorString += "INPUT: Longitude, latitude and height coordinates are required inputs if 'DGNSS - User Ref. & Rover' is set [In the Input Section - A Priori Receiver Position From].\n";
                    conditionsmet=0;
                } else if  (ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text().toDouble()<-180. || ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text().toDouble()>180) {
                    *errorString += "INPUT: Longitude coordinate must be in the range [-180..180] degrees.\n";
                    conditionsmet=0;
                } else if  (ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text().toDouble()<-90. || ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text().toDouble()>90) {
                    *errorString += "INPUT: Latitude coordinate must be in the range [-90..90] degrees.\n";
                    conditionsmet=0;
                } else if ( ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text().toDouble() < -10000. ) {
                    *errorString += "INPUT: Height coordinate cannot be lower than -10 kilometres.\n";
                    conditionsmet=0;
                }
            }
            if (ui->radioButtonRtcmUserDefined->isChecked()==true ) {
                if (ui->radioButtonRtcmRecCartesian->isChecked()==true) {
                    if ( ui->lineEditAprioriRecPosRtcmSpecifyX->text() == "" || ui->lineEditAprioriRecPosRtcmSpecifyY->text() == "" || ui->lineEditAprioriRecPosRtcmSpecifyZ->text() == "" ) {
                        *errorString += "INPUT: Rover X Y and Z coordinates are required inputs if 'DGNSS - User Ref. & Rover' is set [In the Input Section - A Priori Receiver Position From].\n";
                        conditionsmet=0;
                    } else if ( ui->lineEditAprioriRecPosRtcmSpecifyX->text().toDouble() == 0. || ui->lineEditAprioriRecPosRtcmSpecifyY->text().toDouble() == 0. || ui->lineEditAprioriRecPosRtcmSpecifyZ->text().toDouble() == 0. ) {
                        *errorString += "INPUT: Rover X Y and Z coordinates cannot be 0,0,0.\n";
                        conditionsmet=0;
                    }
                } else {
                    if ( ui->lineEditAprioriRecPosRtcmSpecifyLon->text() == "" || ui->lineEditAprioriRecPosRtcmSpecifyLat->text() == "" || ui->lineEditAprioriRecPosRtcmSpecifyHeight->text() == "" ) {
                        *errorString += "INPUT: Longitude, latitude and height coordinates are required inputs if 'DGNSS - User Ref. & Rover' is set [In the Input Section - A Priori Receiver Position From].\n";
                        conditionsmet=0;
                    } else if  (ui->lineEditAprioriRecPosRtcmSpecifyLon->text().toDouble()<-180. || ui->lineEditAprioriRecPosRtcmSpecifyLon->text().toDouble()>180) {
                        *errorString += "INPUT: Longitude coordinate must be in the range [-180..180] degrees.\n";
                        conditionsmet=0;
                    } else if  (ui->lineEditAprioriRecPosRtcmSpecifyLat->text().toDouble()<-90. || ui->lineEditAprioriRecPosRtcmSpecifyLat->text().toDouble()>90) {
                        *errorString += "INPUT: Latitude coordinate must be in the range [-90..90] degrees.\n";
                        conditionsmet=0;
                    } else if ( ui->lineEditAprioriRecPosRtcmSpecifyHeight->text().toDouble() < -10000. ) {
                        *errorString += "INPUT: Height coordinate cannot be lower than -10 kilometres.\n";
                        conditionsmet=0;
                    }
                }
            }
            if (conditionsmet==1) {
                if (ui->radioButtonRtcmUserDefined->isChecked()==true ) {
                    if (ui->radioButtonRtcmRefCartesian->isChecked()==true) {
                        if(ui->radioButtonRtcmRecCartesian->isChecked()==true) {
                            //Both in cartesian format
                            *saveString += "-pre:setrecpos DGNSSRefRoverUSER " + ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyX->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyY->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyZ->text() +"\n";
                            *runString << "-pre:setrecpos" << "DGNSSRefRoverUSER" << ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() << ui->lineEditAprioriRecPosRtcmSpecifyX->text() <<  ui->lineEditAprioriRecPosRtcmSpecifyY->text() <<  ui->lineEditAprioriRecPosRtcmSpecifyZ->text();
                        } else {
                            //Reference in cartesian, Rover in Geodetic
                            *saveString += "-pre:setrecpos DGNSSRefCarRoverUSERGeod " + ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyLon->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyLat->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyHeight->text() +"\n";
                            *runString << "-pre:setrecpos" << "DGNSSRefCarRoverUSERGeod" << ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() << ui->lineEditAprioriRecPosRtcmSpecifyLon->text() <<  ui->lineEditAprioriRecPosRtcmSpecifyLat->text() <<  ui->lineEditAprioriRecPosRtcmSpecifyHeight->text();
                        }
                    } else {
                        if(ui->radioButtonRtcmRecCartesian->isChecked()==true) {
                            //Reference in geodetic, Rover in cartesian
                            *saveString += "-pre:setrecpos DGNSSRefGeodRoverUSERCar " + ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyX->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyY->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyZ->text() +"\n";
                            *runString << "-pre:setrecpos" << "DGNSSRefGeodRoverUSERCar" << ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() << ui->lineEditAprioriRecPosRtcmSpecifyX->text() <<  ui->lineEditAprioriRecPosRtcmSpecifyY->text() <<  ui->lineEditAprioriRecPosRtcmSpecifyZ->text();
                        } else {
                            //Both in Geodetic
                            *saveString += "-pre:setrecpos DGNSSRefGeodRoverUSERGeod " + ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyLon->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyLat->text() + " " +  ui->lineEditAprioriRecPosRtcmSpecifyHeight->text() +"\n";
                            *runString << "-pre:setrecpos" << "DGNSSRefGeodRoverUSERGeod" << ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() << ui->lineEditAprioriRecPosRtcmSpecifyLon->text() <<  ui->lineEditAprioriRecPosRtcmSpecifyLat->text() <<  ui->lineEditAprioriRecPosRtcmSpecifyHeight->text();
                        }

                    }
                } else {
                    if(ui->radioButtonRtcmRefCartesian->isChecked()==true) {
                        *saveString += "-pre:setrecpos DGNSSUserRoverRef " + ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text() + "\n";
                        *runString << "-pre:setrecpos" << "DGNSSUserRoverRef" << ui->lineEditAprioriRefRecPosRtcmSpecifyX->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyY->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyZ->text();
                    } else {
                        *saveString += "-pre:setrecpos DGNSSUserGeodRoverRef " + ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() + " " + ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text() + "\n";
                        *runString << "-pre:setrecpos" << "DGNSSUserGeodRoverRef" << ui->lineEditAprioriRefRecPosRtcmSpecifyLon->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyLat->text() << ui->lineEditAprioriRefRecPosRtcmSpecifyHeight->text();
                    }
                }
            }
        }
    } else if ( ui->radioButtonSpecify->isChecked() == true ) {
        if (ui->radioButtonSpecifyReferenceFile->isChecked()==true) {
            if (ui->lineEditInterpolationDegreeRefFileSpecify->text()=="") {
                *errorString += "INPUT: Reference position interpolation degree is a required input if 'Reference file:' is set in 'Specify' mode [In the Input Section - A Priori Receiver Position From] .\n";
            } else {
                if (ui->lineEditInterpolationDegreeRefFileSpecify->text().toInt()==0) {
                    //Default interpolation value is 0
                    if (WriteAllParameters==1) {
                        *saveString += "-pre:refpos:deg " + ui->lineEditInterpolationDegreeRefFileSpecify->text() + "\n";
                        *runString << "-pre:refpos:deg" << ui->lineEditInterpolationDegreeRefFileSpecify->text();
                    }
                } else {
                    *saveString += "-pre:refpos:deg " + ui->lineEditInterpolationDegreeRefFileSpecify->text() + "\n";
                    *runString << "-pre:refpos:deg" << ui->lineEditInterpolationDegreeRefFileSpecify->text();
                }
            }
            *saveString += "-pre:setrecpos SetRef\n";
            *runString << "-pre:setrecpos" << "SetRef";
        } else {
            if (ui->radioButtonSpecifyUserCartesian->isChecked()==true) {
                if ( ui->lineEditSpecifyX->text() == "" || ui->lineEditSpecifyY->text() == "" || ui->lineEditSpecifyZ->text() == "" ) {
                    *errorString += "INPUT: X Y and Z coordinates are required inputs if 'Specify - User defined' is set [In the Input Section - A Priori Receiver Position From].\n";
                } else if (ui->lineEditSpecifyX->text().toDouble() == 0. || ui->lineEditSpecifyY->text().toDouble() == 0. || ui->lineEditSpecifyZ->text().toDouble() == 0.) {
                    *errorString += "INPUT: X Y and Z coordinates cannot be 0,0,0.\n";
                } else {
                    *saveString += "-pre:setrecpos Set " + ui->lineEditSpecifyX->text() + " " + ui->lineEditSpecifyY->text() + " " + ui->lineEditSpecifyZ->text() + "\n";
                    *runString << "-pre:setrecpos" << "Set"<< ui->lineEditSpecifyX->text() << ui->lineEditSpecifyY->text() << ui->lineEditSpecifyZ->text();
                }
            } else {
                if ( ui->lineEditSpecifyLon->text() == "" || ui->lineEditSpecifyLat->text() == "" || ui->lineEditSpecifyHeight->text() == "" ) {
                    *errorString += "INPUT: Longitude, latitude and height coordinates are required inputs if 'Specify - User defined' is set [In the Input Section - A Priori Receiver Position From].\n";
                } else if  (ui->lineEditSpecifyLon->text().toDouble()<-180. || ui->lineEditSpecifyLon->text().toDouble()>180) {
                        *errorString += "INPUT: Longitude coordinate must be in the range [-180..180] degrees.\n";
                } else if  (ui->lineEditSpecifyLat->text().toDouble()<-90. || ui->lineEditSpecifyLat->text().toDouble()>90) {
                        *errorString += "INPUT: Latitude coordinate must be in the range [-90..90] degrees.\n";
                } else if ( ui->lineEditSpecifyHeight->text().toDouble() < -10000. ) {
                        *errorString += "INPUT: Height coordinate cannot be lower than -10 kilometres.\n";
                } else {
                    if (ui->checkBoxReferencePositionFileCalculate->isChecked()==true) {
                        *saveString += "-pre:setrecpos SetGeod " + ui->lineEditSpecifyLon->text() + " " + ui->lineEditSpecifyLat->text() + " " + ui->lineEditSpecifyHeight->text() + "\n";
                        *runString << "-pre:setrecpos" << "SetGeod" << ui->lineEditSpecifyLon->text() << ui->lineEditSpecifyLat->text() << ui->lineEditSpecifyHeight->text();
                    } else {
                        *saveString += "-pre:setrecpos SetGeod " + ui->lineEditSpecifyLon->text() + " " + ui->lineEditSpecifyLat->text() + " " + ui->lineEditSpecifyHeight->text() + "\n";
                        *runString << "-pre:setrecpos" << "SetGeod" << ui->lineEditSpecifyLon->text() << ui->lineEditSpecifyLat->text() << ui->lineEditSpecifyHeight->text();
                    }
                }
            }
        }
    }

    //Check start time is greater than end time (if both are enabled)
    if ( ui->checkBoxStartTime->isChecked()==true && ui->checkBoxEndTime->isChecked()==true) {
        date = ui->dateTimeEditStartTime->date();
        time = ui->dateTimeEditStartTime->time();
        if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && time.hour() == 0 && time.minute()==0 && time.second()==0) {
            *errorString += "INPUT: Date (DD/MM/YYYY) and GPS Time (HH:MM:SS) are a required input if 'Start Time' is set [In the Input Section - Rover].\n";
            badDate=1;
        }
        date = ui->dateTimeEditEndTime->date();
        time = ui->dateTimeEditEndTime->time();
        if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && time.hour() == 0 && time.minute()==0 && time.second()==0) {
            *errorString += "INPUT: Date (DD/MM/YYYY) and GPS Time (HH:MM:SS) are a required input if 'End Time' is set [In the Input Section - Rover].\n";
            badDate=1;
        }
        if (badDate==0) {
            if (ui->dateTimeEditStartTime->date().operator >(ui->dateTimeEditEndTime->date()) ) {
                *errorString += "INPUT: 'End Time' must be greater than the 'Start Time' if both are set [In the Input Section - Rover].\n";
                badDate=1;
            } else if (ui->dateTimeEditStartTime->date().operator ==(ui->dateTimeEditEndTime->date()) ) {
                if (ui->dateTimeEditStartTime->time().operator >(ui->dateTimeEditEndTime->time()) ) {
                    *errorString += "INPUT: 'End Time' must be greater than the 'Start Time' if both are set [In the Input Section - Rover].\n";
                    badDate=1;
                }
            }
        }
    }

    //Start time
    if (ui->checkBoxStartTime->isChecked()==true) {
        date = ui->dateTimeEditStartTime->date();
        time = ui->dateTimeEditStartTime->time();
        if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && time.hour() == 0 && time.minute()==0 && time.second()==0) {
            if (badDate==0) {
                *errorString += "INPUT: Date (DD/MM/YYYY) and GPS Time (HH:MM:SS) are a required input if 'Start Time' is set [In the Input Section - Rover].\n";
            }
        } else {
                *saveString += "-pre:starttime " + date.toString("yyyy/MM/dd") + " " + time.toString("HH:mm:ss") + "\n";
                *runString << "-pre:starttime" << date.toString("yyyy/MM/dd") << time.toString("HH:mm:ss");
        }
    }

    //End time
    if (ui->checkBoxEndTime->isChecked()==true) {
        date = ui->dateTimeEditEndTime->date();
        time = ui->dateTimeEditEndTime->time();
        if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && time.hour() == 0 && time.minute()==0 && time.second()==0) {
            if (badDate==0) {
                *errorString += "INPUT: Date (DD/MM/YYYY) and GPS Time (HH:MM:SS) are a required input if 'End time' is set [In the Input Section - Rover].\n";
            }
        } else {
            *saveString += "-pre:endtime " + date.toString("yyyy/MM/dd") + " " + time.toString("HH:mm:ss") + "\n";
            *runString << "-pre:endtime" << date.toString("yyyy/MM/dd") << time.toString("HH:mm:ss");
        }
    }

    ////Receiver type
    if ( ui->groupBoxAuxFiles->isChecked() == true ) {
        if ( ui->groupBoxP1C1correction->isChecked() == true ) {
            if (ui->radioButtonGPSReceiverTypeFile->isChecked()==true ) {
                //We have selected a GPS Receiver type file
                if (WriteAllParameters==1) {
                    if (ui->lineEditGPSRecType->text()=="") {
                        //This is the default receiver type when no GPS receiver type file is given
                        *saveString += "-pre:setrectype 0\n";
                        *runString << "-pre:setrectype" << "0";
                    } else {
                        //This is the default option when a GPS receiver type file is given
                        *saveString += "-pre:setrectype gpsrt\n";
                        *runString << "-pre:setrectype" << "gpsrt";
                    }
                }
            } else if (ui->radioButtonGPSReceiverTypeUserSelection->isChecked()==true) {
                if (ui->comboBoxGPSReceiverTypeSelection->currentIndex()==0) {
                    //This is the default receiver type when no GPS receiver type file is given
                    if (WriteAllParameters==1) {
                        *saveString += "-pre:setrectype 0\n";
                        *runString << "-pre:setrectype" << "0";
                    }
                } else if (ui->comboBoxGPSReceiverTypeSelection->currentIndex()==1) {
                    *saveString += "-pre:setrectype 1\n";
                    *runString << "-pre:setrectype" << "1";
                } else if (ui->comboBoxGPSReceiverTypeSelection->currentIndex()==2) {
                    *saveString += "-pre:setrectype 2\n";
                    *runString << "-pre:setrectype" << "2";
                } else if (ui->comboBoxGPSReceiverTypeSelection->currentIndex()==3) {
                    *saveString += "-pre:setrectype 3\n";
                    *runString << "-pre:setrectype" << "3";
                }
            }
        } else {
            //No P1-C1 correction and no GPS receiver type file given. Default receiver type is 0 (Unknown type)
            if (WriteAllParameters==1) {
                *saveString += "-pre:setrectype 0\n";
                *runString << "-pre:setrectype" << "0";
            }
        }
    } else {
        //No P1-C1 correction and no GPS receiver type file given (Auxiliary groupbox disabled). Default receiver type is 0 (Unknown type)
        if (WriteAllParameters==1) {
            *saveString += "-pre:setrectype 0\n";
            *runString << "-pre:setrectype" << "0";
        }
    }

    //// Station Data
    //Decimation
    if ( ui->checkBoxDataDecimator->isChecked() == true ) {
        if ( ui->lineEditDataDecimator->text() == "" )
            *errorString += "PREPROCESS: A numerical value is required if 'Data Decimation' is set [In the Preprocess Section - Station Data].\n";
        else {
            if (ui->groupBoxSbas->isChecked()==true) {
                if ( ui->lineEditDataDecimator->text().toDouble() != 1.|| WriteAllParameters==1 ) {
                    //For SBAS set decimation if is different than 1
                    *saveString += "-pre:dec " + ui->lineEditDataDecimator->text() + "\n";
                    *runString << "-pre:dec" << ui->lineEditDataDecimator->text();
                }
            } else if ( ui->lineEditDataDecimator->text().toDouble() != 0. || WriteAllParameters==1 ) {
                //For SPP,PPP, set decimation if is different than 0
                *saveString += "-pre:dec " + ui->lineEditDataDecimator->text() + "\n";
                *runString << "-pre:dec" << ui->lineEditDataDecimator->text();
            }
        }
    } else if (ui->groupBoxSbas->isChecked()==true || WriteAllParameters==1){
        //Only add decimation to 0 if SBAS is set
        *saveString += "-pre:dec 0\n";
        *runString << "-pre:dec" << "0";
    }
    //Code jumps. Enabled by default in all modes
    if (ui->checkBoxReceiverCodeJumps->isChecked()==true) {
        if (WriteAllParameters==1) {
            *saveString += "-pre:checkcodejumps\n";
            *runString << "-pre:checkcodejumps";
        }
    } else  if (ui->checkBoxReceiverCodeJumps->isChecked()==false) {
        *saveString += "--pre:checkcodejumps\n";
        *runString << "--pre:checkcodejumps";
    }


    // Satellite Options
    if ( ui->lineEditElevMask->text() == "" )
        *errorString += "PREPROCESS: A numerical value is required for Elevation Mask [In the Preprocess Section - Satellite Options].\n";
    else if ( ui->lineEditElevMask->text().toDouble() != 5. || WriteAllParameters==1 ) {
        //Default mask for all modes is 5º
        *saveString += "-pre:elevation " + ui->lineEditElevMask->text() + "\n";
        *runString << "-pre:elevation" << ui->lineEditElevMask->text();
    }
    if ( ui->checkBoxDiscardEclipse->isChecked() == true ) {
        if (mode==0 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true || WriteAllParameters==1 ) {
            //Discard satellites on eclipse is only set by default in PPP
            *saveString += "-pre:eclipse\n";
            *runString << "-pre:eclipse";
        }
    } else if ( (mode==1 && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) || WriteAllParameters==1 ) {
        //No SBAS or DGNSS and we are in PPP
        *saveString += "--pre:eclipse\n";
        *runString << "--pre:eclipse";
    }

    //Carrier phase alignment is enabled by default on all modes
    if ( ui->checkBoxPrealignPhase->isChecked()==true) {
        if (WriteAllParameters==1 ) {
            *saveString += "-pre:prealign\n";
            *runString << "-pre:prealign";
        }
    } else  if ( ui->checkBoxPrealignPhase->isChecked()==false) {
        *saveString += "--pre:prealign\n";
        *runString << "--pre:prealign";
    }

    //Min SNR is disabled by default in all modes
    if ( ui->checkBoxSNRThresholdMin->isChecked()==true ) {
        if (ui->checkBoxSNRMinAdvancedMode->isChecked()==false){
            switch(ui->comboBoxSNRThresholdsMin->currentIndex()) {
                case 0:
                    *saveString += "-pre:minsnrsel 0 12\n";
                    *runString << "-pre:minsnrsel" << "0" << "12";
                    break;
                case 1:
                    *saveString += "-pre:minsnrsel 0 18\n";
                    *runString << "-pre:minsnrsel" << "0" << "18";
                    break;
                case 2:
                    *saveString += "-pre:minsnrsel 0 24\n";
                    *runString << "-pre:minsnrsel" << "0" << "24";
                    break;
                case 3:
                    *saveString += "-pre:minsnrsel 0 30\n";
                    *runString << "-pre:minsnrsel" << "0" << "30";
                    break;
                case 4:
                    //Default threshold in gLAB is 33
                    if(WriteAllParameters==1) {
                        *saveString += "-pre:minsnrsel 0 33\n";
                        *runString << "-pre:minsnrsel" << "0" << "33";
                    } else {
                        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
                            //In SPP or PPP SNR is disabled by default
                            *saveString += " -pre:minsnr\n";
                            *runString << "-pre:minsnr";
                        }
                    }
                    break;
                case 5:
                    *saveString += "-pre:minsnrsel 0 36\n";
                    *runString << "-pre:minsnrsel" << "0" << "36";
                    break;
                case 6:
                    *saveString += "-pre:minsnrsel 0 42\n";
                    *runString << "-pre:minsnrsel" << "0" << "42";
                    break;
                case 7:
                    *saveString += "-pre:minsnrsel 0 48\n";
                    *runString << "-pre:minsnrsel" << "0" << "48";
                    break;
                case 8:
                    *saveString += "-pre:minsnrsel 0 54\n";
                    *runString << "-pre:minsnrsel" << "0" << "54";
                    break;
                case 9:
                    if(ui->lineEditUserDefinedSNRMin->text()=="") {
                        *errorString += "PREPROCESS: A numerical value is required for Min SNR Mask [In the Preprocess Section - Satellite Options].\n";
                        SNRerror=1;
                    } else if (ui->lineEditUserDefinedSNRMin->text().toDouble()<=0) {
                        *errorString += "PREPROCESS: Min SNR Mask must be greater than 0 [In the Preprocess Section - Satellite Options].\n";
                        SNRerror=1;
                    } else {
                        if (ui->lineEditUserDefinedSNRMin->text().toDouble() != 33) {
                            if(WriteAllParameters==1) {
                                *saveString += "-pre:minsnrsel 0 " + ui->lineEditUserDefinedSNRMin->text() +"\n";
                                *runString << "-pre:minsnrsel" << "0" << ui->lineEditUserDefinedSNRMin->text();
                            } else {
                                if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
                                    //In SPP or PPP SNR is disabled by default
                                    *saveString += " -pre:minsnr\n";
                                    *runString << "-pre:minsnr";
                                }
                            }
                        } else {
                            *saveString += "-pre:minsnrsel 0 " + ui->lineEditUserDefinedSNRMin->text() +"\n";
                            *runString << "-pre:minsnrsel" << "0" << ui->lineEditUserDefinedSNRMin->text();
                        }
                    }
                    break;
            }
        } else {
            SNRerror+=this->SnrAdvancedMinWin->getgLABOptions(errorString,warningString,saveString,runString);
        }
    } else if (WriteAllParameters==1 || (ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true)) {
        //SNR is enabled by default in SBAS and DGNSS
        *saveString += "--pre:minsnr\n";
        *runString << "--pre:minsnr";
    }
    //Max SNR is disabled by default in all modes
    if ( ui->checkBoxSNRThresholdMax->isChecked()==true ) {
        if (ui->checkBoxSNRMaxAdvancedMode->isChecked()==false){
            switch(ui->comboBoxSNRThresholdsMax->currentIndex()) {
                case 0:
                    *saveString += "-pre:maxsnrsel 0 12\n";
                    *runString << "-pre:maxsnrsel" << "0" << "12";
                    break;
                case 1:
                    *saveString += "-pre:maxsnrsel 0 18\n";
                    *runString << "-pre:maxsnrsel" << "0" << "18";
                    break;
                case 2:
                    *saveString += "-pre:maxsnrsel 0 24\n";
                    *runString << "-pre:maxsnrsel" << "0" << "24";
                    break;
                case 3:
                    *saveString += "-pre:maxsnrsel 0 30\n";
                    *runString << "-pre:maxsnrsel" << "0" << "30";
                    break;
                case 4:
                    *saveString += "-pre:maxsnrsel 0 33\n";
                    *runString << "-pre:maxsnrsel" << "0" << "33";
                    break;
                case 5:
                    *saveString += "-pre:maxsnrsel 0 36\n";
                    *runString << "-pre:maxsnrsel" << "0" << "36";
                    break;
                case 6:
                    *saveString += "-pre:maxsnrsel 0 42\n";
                    *runString << "-pre:maxsnrsel" << "0" << "42";
                    break;
                case 7:
                    *saveString += "-pre:maxsnrsel 0 48\n";
                    *runString << "-pre:maxsnrsel" << "0" << "48";
                    break;
                case 8:
                    //Default threshold in gLAB is 54
                    if(WriteAllParameters==1) {
                        *saveString += "-pre:maxsnrsel 0 54\n";
                        *runString << "-pre:maxsnrsel" << "0" << "54";
                    } else {
                        if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
                            //In SPP or PPP SNR is disabled by default
                            *saveString += " -pre:maxsnr\n";
                            *runString << "-pre:maxsnr";
                        }
                    }
                    break;
                case 9:
                    if(ui->lineEditUserDefinedSNRMax->text()=="") {
                        *errorString += "PREPROCESS: A numerical value is required for Max SNR Mask [In the Preprocess Section - Satellite Options].\n";
                        SNRerror=1;
                    } else if (ui->lineEditUserDefinedSNRMax->text().toDouble()<=0) {
                        *errorString += "PREPROCESS: Max SNR Mask must be greater than 0 [In the Preprocess Section - Satellite Options].\n";
                        SNRerror=1;
                    } else {
                        if (ui->lineEditUserDefinedSNRMax->text().toDouble()==54.) {
                            if(WriteAllParameters==1) {
                                *saveString += "-pre:maxsnrsel 0 " + ui->lineEditUserDefinedSNRMax->text() +"\n";
                                *runString << "-pre:maxsnrsel" << "0" << ui->lineEditUserDefinedSNRMax->text();
                            } else {
                                if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) {
                                    //In SPP or PPP SNR is disabled by default
                                    *saveString += " -pre:maxsnr\n";
                                    *runString << "-pre:maxsnr";
                                }
                            }
                        } else {
                            *saveString += "-pre:maxsnrsel 0 " + ui->lineEditUserDefinedSNRMax->text() +"\n";
                            *runString << "-pre:maxsnrsel" << "0" << ui->lineEditUserDefinedSNRMax->text();
                        }
                    }
                    break;
            }
        } else {
            SNRerror+=this->SnrAdvancedMaxWin->getgLABOptions(errorString,warningString,saveString,runString);
        }
    } else if (WriteAllParameters==1|| (ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true)) {
        //SNR is enabled by default in SBAS and DGNSS
        *saveString += "--pre:maxsnr\n";
        *runString << "--pre:maxsnr";
    }

    //Check minimum and maximum SNR values. It is done after so all provided values have been checked
    if ( ui->checkBoxSNRThresholdMin->isChecked()==true && ui->checkBoxSNRThresholdMax->isChecked()==true && SNRerror==0 ) {
        this->checkMinMaxSNRThresholds(errorString);
    }


    // Cycle-slip Detection
    if ( ui->lineEditDataGap->text() == "" ) {
        *errorString += "PREPROCESS: A numerical value is required for Data Gap [In the Preprocess Section - Cycle-slip Detection].\n";
    } else if (WriteAllParameters==1) {
        *saveString += "-pre:cs:datagap " + ui->lineEditDataGap->text() + "\n";
        *runString << "-pre:cs:datagap" << ui->lineEditDataGap->text();
    } else {
        if (ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true) {
            //In SBAS and DGNSS default data gap is 10
            if ( ui->lineEditDataGap->text().toInt() != 10 ) {
                *saveString += "-pre:cs:datagap " + ui->lineEditDataGap->text() + "\n";
                *runString << "-pre:cs:datagap" << ui->lineEditDataGap->text();
            }
        } else {
            //In SPP and PPP default data gap is 40
            if ( ui->lineEditDataGap->text().toInt() != 40 ) {
                *saveString += "-pre:cs:datagap " + ui->lineEditDataGap->text() + "\n";
                *runString << "-pre:cs:datagap" << ui->lineEditDataGap->text();
            }
        }
    }
    if ( ui->checkBoxLLI->isChecked() == true ) {
        //Only in PPP LLI is active by default
        if (mode==0 || ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true || WriteAllParameters==1 ) {
             *saveString += "-pre:cs:lli\n";
             *runString << "-pre:cs:lli";
        }
    } else {
        if ( (mode==1 && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) || WriteAllParameters==1 ) {
            *saveString += "--pre:cs:lli\n";
            *runString << "--pre:cs:lli";
        }
    }
    if (ui->checkBoxNcon->isChecked() == true ) {
        if (ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true || WriteAllParameters==1) {
             //N-con is enabled by default only on SPP or PPP
            *saveString += "-pre:cs:ncon:min " + ui->lineEditNcon->text() + "\n";
            *runString << "-pre:cs:ncon:min" << ui->lineEditNcon->text();
        } else {
            if (ui->lineEditNcon->text()!="3") {
                *saveString += "-pre:cs:ncon:min " + ui->lineEditNcon->text() + "\n";
                *runString << "-pre:cs:ncon:min" << ui->lineEditNcon->text();
            }
        }
    } else {
        if ((ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) || WriteAllParameters==1) {
            *saveString += "--pre:cs:ncon\n";
            *runString << "--pre:cs:ncon" ;
        }
    }
    anyCSparam=0;
    if ( ui->checkBoxSF->isChecked() == true ) {

        //Consistency check is by default enabled in all modes
        if (ui->checkBoxSFConsistencyCheck->isChecked()==true) {
            if (WriteAllParameters==1 ) {
                *saveString += "-pre:cs:sf:unconcheck\n";
                *runString << "-pre:cs:sf:unconcheck";
                anyCSparam++;
            }
            if (ui->lineEditSFConsCheckValue->text()=="") {
               *errorString += "PREPROCESS: A numerical value is required for Consistency Check Threshold [In the Preprocess Section - Phase-Code Cycle-slip Detection].\n";
            } else if (ui->lineEditSFConsCheckValue->text().toDouble()==0.) {
                *errorString += "PREPROCESS: Consistency Check Threshold cannot be 0 [In the Preprocess Section - Phase-Code Cycle-slip Detection].\n";
            } else if (ui->lineEditSFConsCheckValue->text().toDouble()!= 20. || WriteAllParameters==1) {
                *saveString += "-pre:cs:sf:unconcheck:th " + ui->lineEditSFConsCheckValue->text() + "\n";
                *runString << "-pre:cs:sf:unconcheck:th" << ui->lineEditSFConsCheckValue->text();
                anyCSparam++;
            }
        } else  if (ui->checkBoxSFConsistencyCheck->isChecked()==false) {
            *saveString += "--pre:cs:sf:unconcheck\n";
            *runString << "--pre:cs:sf:unconcheck";
            anyCSparam++;
        }
        if ( ui->lineEditSFiniStd->text() == "" ) {
            *errorString += "PREPROCESS: A numerical value is required for Initial stdDev [In the Preprocess Section - Phase-Code Cycle-slip Detection].\n";
        } else if ( ui->lineEditSFiniStd->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: Initial stdDev cannot be 0 [In the Preprocess Section - Phase-Code Cycle-slip Detection].\n";
        } else if (ui->lineEditSFiniStd->text().toDouble() != 3. || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:sf:init " + ui->lineEditSFiniStd->text() + "\n";
            *runString << "-pre:cs:sf:init" << ui->lineEditSFiniStd->text();
            anyCSparam++;
        }
        if ( ui->lineEditSFwindow->text() == "" ) {
            *errorString += "PREPROCESS: A numerical value is required for Window [In the Preprocess Section - Phase-Code Cycle-slip Detection].\n";
        } else if ( ui->lineEditSFwindow->text().toInt() == 0 ) {
            *errorString += "PREPROCESS: Window cannot be 0 [In the Preprocess Section - Phase-Code Cycle-slip Detection].\n";
        } else if ( ui->lineEditSFwindow->text().toInt() >= 600 ) {
            *errorString += "PREPROCESS: Window size must be under 600 [In the Preprocess Section - Phase-Code Cycle-slip Detection].\n";
        } else if ( ui->lineEditSFwindow->text().toInt() != 300 || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:sf:timewindow " + ui->lineEditSFwindow->text() + "\n";
            *runString << "-pre:cs:sf:timewindow" << ui->lineEditSFwindow->text();
            anyCSparam++;
        }
        if ( ui->lineEditSFkFactor->text() == "" ) {
            *errorString += "PREPROCESS: A numerical value is required for k-factor [In the Preprocess Section - Phase-Code Cycle-slip Detection].\n";
        } else if ( ui->lineEditSFkFactor->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: K-factor cannot be 0 [In the Preprocess Section - Phase-Code Cycle-slip Detection].\n";
        } else if ( ui->lineEditSFkFactor->text().toDouble() != 5.|| WriteAllParameters==1 ) {
            *saveString += "-pre:cs:sf:kfactor " + ui->lineEditSFkFactor->text() + "\n";
            *runString << "-pre:cs:sf:kfactor" << ui->lineEditSFkFactor->text();
            anyCSparam++;
        }
        if ( ui->lineEditSFnSample->text() == "" ) {
            *errorString += "PREPROCESS: A numerical value is required for N-sample [In the Preprocess Section - Phase-Code Cycle-slip Detection].\n";
        } else if ( ui->lineEditSFnSample->text().toInt() == 0 ) {
            *errorString += "PREPROCESS: N-sample cannot be 0 [In the Preprocess Section - Phase-Code Cycle-slip Detection].\n";
        } else if ( ui->lineEditSFnSample->text().toInt() < 2 ) {
            *errorString += "PREPROCESS: N-sample cannot be less than 2 [In the Preprocess Section - Phase-Code Cycle-slip Detection].\n";
        } else if ( ui->lineEditSFnSample->text().toInt() != 2 || WriteAllParameters==1) {
            *saveString += "-pre:cs:sf:samples " + ui->lineEditSFnSample->text() + "\n";
            *runString << "-pre:cs:sf:samples" << ui->lineEditSFnSample->text();
            anyCSparam++;
        }
        if (ui->radioButtonSFManualSelection->isChecked()) {
            anyCSparam+=CSAdvancedSF->getgLABOptions(errorString,warningString,saveString,runString);
        }
        if (anyCSparam==0 || WriteAllParameters==1) {
            //Phase-Code is enabled by default only in SBAS 1F and DGNSS
            if  ((ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) ||
                 (mode==0 && ui->groupBoxSbas->isChecked()==true && ui->comboBoxSbasInput->currentIndex()==1 ) ||  WriteAllParameters==1)  {
                *saveString += "-pre:cs:sf\n";
                *runString << "-pre:cs:sf";
            }
        }
    } else if ( (mode==0 && ui->groupBoxSbas->isChecked()==true && ui->comboBoxSbasInput->currentIndex()==0)  || ui->groupBoxReferenceStation->isChecked()==true|| WriteAllParameters==1){
        *saveString += "--pre:cs:sf\n";
        *runString << "--pre:cs:sf";
    }
    //parameters for nooutliers
    anyCSparam=0;
    if ( ui->checkBoxMW->isChecked() == true ) {
        if (ui->checkBoxMWNoOutliers->isChecked()==true){
            *saveString += "-pre:cs:mw:nooutliers\n";
            *runString << "-pre:cs:mw:nooutliers";
            anyCSparam++;
        } else if (WriteAllParameters==1){
            *saveString += "--pre:cs:mw:nooutliers\n";
            *runString << "--pre:cs:mw:nooutliers";
            anyCSparam++;
        }
        if ( ui->lineEditIntialStdDevMW->text() == "" ) {
            *errorString += "PREPROCESS: A numerical value is required for Initial stdDev [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
         } else if ( ui->lineEditIntialStdDevMW->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: Initial stdDev cannot be 0 [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
         } else if ( ui->lineEditIntialStdDevMW->text().toDouble() != 2. || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:mw:siginit " + ui->lineEditIntialStdDevMW->text() + "\n";
            *runString << "-pre:cs:mw:siginit" << ui->lineEditIntialStdDevMW->text();
            anyCSparam++;
        }
        if ( ui->lineEditMWminStd->text() == "" ) {
            *errorString += "PREPROCESS: A numerical value is required for Minimum stdDev [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
         } else if ( ui->lineEditMWminStd->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: Minimum stdDev cannot be 0 [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
         } else if ( ui->lineEditMWminStd->text().toDouble() != 0.8 || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:mw:sigmin " + ui->lineEditMWminStd->text() + "\n";
            *runString << "-pre:cs:mw:sigmin" << ui->lineEditMWminStd->text();
            anyCSparam++;
        }
        if ( ui->lineEditMWwindow->text() == "" ) {
            *errorString += "PREPROCESS: A numerical value is required for Window [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
        } else if ( ui->lineEditMWwindow->text().toInt() == 0 ) {
            *errorString += "PREPROCESS: Window cannot be 0 [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
        } else if ( ui->lineEditMWwindow->text().toInt() >= 600 ) {
            *errorString += "PREPROCESS: Window size must be under 600 [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
        } else if ( ui->lineEditMWwindow->text().toInt() != 300 || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:mw:timewindow " + ui->lineEditMWwindow->text() + "\n";
            *runString << "-pre:cs:mw:timewindow" << ui->lineEditMWwindow->text();
            anyCSparam++;
        }
        if ( ui->lineEditMWkFactor->text() == "" ) {
            *errorString += "PREPROCESS: A numerical value is required for k-factor [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
        } else if ( ui->lineEditMWkFactor->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: K-factor cannot be 0 [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
        } else if ( ui->lineEditMWkFactor->text().toDouble() != 5. || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:mw:kfactor " + ui->lineEditMWkFactor->text() + "\n";
            *runString << "-pre:cs:mw:kfactor" << ui->lineEditMWkFactor->text();
            anyCSparam++;
        }
        if ( ui->lineEditMWnSample->text() == "" ) {
            *errorString += "PREPROCESS: A numerical value is required for N-sample [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
        } else if ( ui->lineEditMWnSample->text().toInt() == 0 ) {
            *errorString += "PREPROCESS: N-sample cannot be 0 [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
        } else if ( ui->lineEditMWnSample->text().toInt() < 2 ) {
            *errorString += "PREPROCESS: N-sample cannot be less than 2 [In the Preprocess Section - Melbourne-Wübbena Cycle-slip Detection].\n";
        } else if ( ui->lineEditMWnSample->text().toInt() != 2 || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:mw:samples " + ui->lineEditMWnSample->text() + "\n";
            *runString << "-pre:cs:mw:samples" << ui->lineEditMWnSample->text();
            anyCSparam++;
        }
        if (ui->radioButtonMWManualSelection->isChecked()) {
            anyCSparam+=CSAdvancedMW->getgLABOptions(errorString,warningString,saveString,runString);
        }
        if (anyCSparam==0 || WriteAllParameters==1) {
            if ( (ui->groupBoxSbas->isChecked()==true && ui->comboBoxSbasInput->currentIndex()==0) || ui->groupBoxReferenceStation->isChecked()==true
                  || (mode==0 && ui->groupBoxSbas->isChecked()==false)  || WriteAllParameters==1){
                //MW detector is enabled by default in PPP and SBAS DFMC
                *saveString += "-pre:cs:mw\n";
                *runString << "-pre:cs:mw";
            }
        }
    } else if ((mode==1 && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false)
               || (mode==0 && ui->groupBoxSbas->isChecked()==true && ui->comboBoxSbasInput->currentIndex()==1) || WriteAllParameters==1){
        *saveString += "--pre:cs:mw\n";
        *runString << "--pre:cs:mw";
    }
    anyCSparam=0;
    if ( ui->checkBoxLI->isChecked() == true ) {
        if (ui->checkBoxLINoOutliers->isChecked()==true){
            *saveString += "-pre:cs:li:nooutliers\n";
            *runString << "-pre:cs:li:nooutliers";
            anyCSparam++;
        } else if (WriteAllParameters==1){
            *saveString += "--pre:cs:li:nooutliers\n";
            *runString << "--pre:cs:li:nooutliers";
            anyCSparam++;
        }
        if ( ui->lineEditLImaxJumpThreshold->text() == "" ) {
            *errorString += "PREPROCESS: A numerical value is required for Maximum Jump Threshold [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLImaxJumpThreshold->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: Maximum Jump Threshold cannot be 0 [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLImaxJumpThreshold->text().toDouble() != 1. || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:li:maxjump " + ui->lineEditLImaxJumpThreshold->text() + "\n";
            *runString << "-pre:cs:li:maxjump" << ui->lineEditLImaxJumpThreshold->text();
            anyCSparam++;
        }
        if ( ui->lineEditLImaxThreshold->text() == "" ) {
            *errorString += "PREPROCESS: A numerical value is required for Maximum Threshold [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLImaxThreshold->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: Maximum Threshold cannot be 0 [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLImaxThreshold->text().toDouble() != 0.08 || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:li:max " + ui->lineEditLImaxThreshold->text() + "\n";
            *runString << "-pre:cs:li:max" << ui->lineEditLImaxThreshold->text();
            anyCSparam++;
        }
        if ( ui->lineEditLItimeConstant->text() == "" ) {
            *errorString += "PREPROCESS: A numerical value is required for Time Constant [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLItimeConstant->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: Time Constant cannot be 0 [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLItimeConstant->text().toDouble() != 60. || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:li:t0 " + ui->lineEditLItimeConstant->text() + "\n";
            *runString << "-pre:cs:li:t0" << ui->lineEditLItimeConstant->text();
            anyCSparam++;
        }
        if ( ui->lineEditLInSamples->text() == "" ) {
            *errorString += "PREPROCESS: A numerical value is required for N-sample [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLInSamples->text().toInt() == 0 ) {
            *errorString += "PREPROCESS:N-sample cannot be 0 [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLInSamples->text().toInt() < 2 ) {
            *errorString += "PREPROCESS:N-sample cannot be less than 2 [In the Preprocess Section - Geometry-free Cycle-slip Detection].\n";
        } else if ( ui->lineEditLInSamples->text().toInt() != 7 || WriteAllParameters==1) {
            *saveString += "-pre:cs:li:samples " + ui->lineEditLInSamples->text() + "\n";
            *runString << "-pre:cs:li:samples" << ui->lineEditLInSamples->text();
            anyCSparam++;
        }
        if (ui->radioButtonLIManualSelection->isChecked()) {
            anyCSparam+=CSAdvancedLI->getgLABOptions(errorString,warningString,saveString,runString);
        }
        if (anyCSparam==0 || WriteAllParameters==1) {
            if ( (ui->groupBoxSbas->isChecked()==true && ui->comboBoxSbasInput->currentIndex()==0) || ui->groupBoxReferenceStation->isChecked()==true
                    || (mode==0 && ui->groupBoxSbas->isChecked()==false) || WriteAllParameters==1){
                //MW detector is enabled by default in PPP and SBAS DFMC
                *saveString += "-pre:cs:li\n";
                *runString << "-pre:cs:li";
            }
        }
    } else if ((mode==1 && ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false)
               || (mode==0 && ui->groupBoxSbas->isChecked()==true && ui->comboBoxSbasInput->currentIndex()==1) || WriteAllParameters==1){
        *saveString += "--pre:cs:li\n";
        *runString << "--pre:cs:li";
    }
    anyCSparam=0;
    if ( ui->checkBoxIGF->isChecked() == true ) {

        if (ui->checkBoxIGFNoOutliers->isChecked()==true){
            *saveString += "-pre:cs:igf:nooutliers\n";
            *runString << "-pre:cs:igf:nooutliers";
            anyCSparam++;
        } else if (WriteAllParameters==1){
            *saveString += "--pre:cs:igf:nooutliers\n";
            *runString << "--pre:cs:igf:nooutliers";
            anyCSparam++;
        }

        if (ui->radioButtonIGFMinimumNoise->isChecked()){
            *saveString += "-pre:cs:igf:minnoise\n";
            *runString << "-pre:cs:igf:minnoise";
            anyCSparam++;
        } else if (WriteAllParameters==1){
            *saveString += "--pre:cs:igf:minnoise\n";
            *runString << "--pre:cs:igf:minnoise";
            anyCSparam++;
        }
        if ( ui->lineEditIGFmaxJumpThreshold->text() == "" ) {
            *errorString += "PREPROCESS: A numerical value is required for Maximum Jump Threshold [In the Preprocess Section - IGF Cycle-slip Detection].\n";
        } else if ( ui->lineEditIGFmaxJumpThreshold->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: Maximum Jump Threshold cannot be 0 [In the Preprocess Section - IGF Cycle-slip Detection].\n";
        } else if ( ui->lineEditIGFmaxJumpThreshold->text().toDouble() != 1. || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:igf:maxjump " + ui->lineEditIGFmaxJumpThreshold->text() + "\n";
            *runString << "-pre:cs:igf:maxjump" << ui->lineEditIGFmaxJumpThreshold->text();
            anyCSparam++;
        }
        if ( ui->lineEditIGFmaxThreshold->text() == "" ) {
            *errorString += "PREPROCESS: A numerical value is required for Maximum Threshold [In the Preprocess Section - IGF Cycle-slip Detection].\n";
        } else if ( ui->lineEditIGFmaxThreshold->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: Maximum Threshold cannot be 0 [In the Preprocess Section - IGF Cycle-slip Detection].\n";
        } else if ( ui->lineEditIGFmaxThreshold->text().toDouble() != 0.16 || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:igf:max " + ui->lineEditIGFmaxThreshold->text() + "\n";
            *runString << "-pre:cs:igf:max" << ui->lineEditIGFmaxThreshold->text();
            anyCSparam++;
        }
        if ( ui->lineEditIGFtimeConstant->text() == "" ) {
            *errorString += "PREPROCESS: A numerical value is required for Time Constant [In the Preprocess Section - IGF Cycle-slip Detection].\n";
        } else if ( ui->lineEditIGFtimeConstant->text().toDouble() == 0. ) {
            *errorString += "PREPROCESS: Time Constant cannot be 0 [In the Preprocess Section - IGF Cycle-slip Detection].\n";
        } else if ( ui->lineEditIGFtimeConstant->text().toDouble() != 60. || WriteAllParameters==1 ) {
            *saveString += "-pre:cs:igf:t0 " + ui->lineEditIGFtimeConstant->text() + "\n";
            *runString << "-pre:cs:igf:t0" << ui->lineEditIGFtimeConstant->text();
            anyCSparam++;
        }
        if ( ui->lineEditIGFnSamples->text() == "" ) {
            *errorString += "PREPROCESS: A numerical value is required for N-sample [In the Preprocess Section - IGF Cycle-slip Detection].\n";
        } else if ( ui->lineEditIGFnSamples->text().toInt() == 0 ) {
            *errorString += "PREPROCESS:N-sample cannot be 0 [In the Preprocess Section - IGF Cycle-slip Detection].\n";
        } else if ( ui->lineEditIGFnSamples->text().toInt() < 2 ) {
            *errorString += "PREPROCESS:N-sample cannot be less than 2 [In the Preprocess Section - IGF Cycle-slip Detection].\n";
        } else if ( ui->lineEditIGFnSamples->text().toInt() != 7 || WriteAllParameters==1) {
            *saveString += "-pre:cs:igf:samples " + ui->lineEditIGFnSamples->text() + "\n";
            *runString << "-pre:cs:igf:samples" << ui->lineEditIGFnSamples->text();
            anyCSparam++;
        }
        if (ui->radioButtonIGFManualSelection->isChecked()) {
            anyCSparam+=CSAdvancedIGF->getgLABOptions(errorString,warningString,saveString,runString);
        }
        if (anyCSparam==0 || WriteAllParameters==1) {
            //IGF is disabled by default in all modes
            *saveString += "-pre:cs:igf\n";
            *runString << "-pre:cs:igf";
        }
    } else if (WriteAllParameters==1) {
        *saveString += "--pre:cs:igf\n";
        *runString << "--pre:cs:igf";
    }

    // GNSS Satellite Selection
    StartedGroup=0;
    FirstSat=0;

    QString GNSSSaveString="",StringGNSSRunString="", GNSSAddString="", GNSSRemoveString="", GNSSPartiallyRemoveString="" ;
    if (!ui->checkBoxGPS->isChecked()&&!ui->checkBoxGalileo->isChecked()&&!ui->checkBoxGLONASS->isChecked()&&!ui->checkBoxBDS->isChecked()
            &&!ui->checkBoxGEO->isChecked()&&!ui->checkBoxQZSS->isChecked()&&!ui->checkBoxIRNSS->isChecked()){
        *errorString += "PREPROCESS: No satellite or constellation was selected.\n";
    }
    //Loop first to get fully selected, partially selected of fully unselected constellations
    for(i=0;i<MAX_GNSS;i++) {
        numSatEnabled=0;
        numSatDisabled=0;
        for(j=1;j<=listMaxSatGNSS[i];j++) {
            if(PushButtonSatWidgets[i][j]->palette().window().color().name()==GreenColor) {
                numSatEnabled++;
            } else {
                numSatDisabled++;
            }
        }
        if (numSatEnabled==listMaxSatGNSS[i]) {
            listConstFullEnabled[i]=1;
            numListConstFullEnabled++;
        } else if (numSatDisabled==listMaxSatGNSS[i]) {
            listConstFullDisabled[i]=1;
            numListConstFullDisabled++;
        } else {
            listConstPartiallyEnabled[i]=1;
            numListConstPartiallyEnabled++;
        }
    }

    if (WriteAllParameters==1) {
        //All constellation to be written in the parameter
        for(i=0;i<MAX_GNSS;i++) {
            if (listConstFullEnabled[i]==1 || listConstPartiallyEnabled[i]==1) {
                if (GNSSAddString=="") {
                    GNSSAddString += "+";
                }
                GNSSAddString += indentifierGNSS[i];
            } else {
                if (GNSSRemoveString=="") {
                    GNSSRemoveString += "-";
                }
                GNSSRemoveString += indentifierGNSS[i];
            }
        }
        if (GNSSAddString!="") {
            GNSSAddString += "0";
        }
        if (GNSSRemoveString!="") {
            GNSSRemoveString += "0";
        }
        //Loop again to fill partially enabled constellations
        for(i=0;i<MAX_GNSS;i++) {
           if (listConstPartiallyEnabled[i]==1) {
               FirstSat=0;
               lastSat=0;
               StartedGroup=0;
               FirstRange=1;
               if (GNSSPartiallyRemoveString == "") {
                   GNSSPartiallyRemoveString += "-" + indentifierGNSS[i];
               } else {
                   GNSSPartiallyRemoveString += " -" + indentifierGNSS[i];
               }
               for(j=1;j<=listMaxSatGNSS[i];j++) {
                   if (PushButtonSatWidgets[i][j]->palette().window().color().name()==GreenColor && FirstSat>0 ) {
                       if (lastSat==FirstSat) {
                           //Number of continuous red satellites until current selected satellites were only one
                           if (FirstRange==1) {
                               FirstRange=0;
                           } else {
                               GNSSPartiallyRemoveString += ".";
                           }
                           GNSSPartiallyRemoveString += QString("%1").arg(lastSat);
                       } else {
                           //Number of continuous red satellites until current selected satellites were more than one. Create a range of satellites
                           if (FirstRange==1) {
                               FirstRange=0;
                           } else {
                               GNSSPartiallyRemoveString += ".";
                           }
                           GNSSPartiallyRemoveString += QString("%1").arg(FirstSat) + "-" + QString("%1").arg(lastSat);
                       }
                       StartedGroup=0;
                       FirstSat=0;
                       lastSat=0;
                   } else if (PushButtonSatWidgets[i][j]->palette().window().color().name()==RedColor) {
                       if (j==listMaxSatGNSS[i]) {
                           if ((j-FirstSat)==0 || FirstSat==0) {
                               //Number of continuous red satellites until current selected satellites were only one
                               if (FirstRange==1) {
                                   FirstRange=0;
                               } else {
                                   GNSSPartiallyRemoveString += ".";
                               }
                               GNSSPartiallyRemoveString += QString("%1").arg(j);
                           } else {
                               //Number of continuous red satellites until current selected satellites were more than one. Create a range of satellites
                               if (FirstRange==1) {
                                   FirstRange=0;
                               } else {
                                   GNSSPartiallyRemoveString += ".";
                               }
                               GNSSPartiallyRemoveString += QString("%1").arg(FirstSat) + "-" + QString("%1").arg(j);
                           }
                       } else {
                           if (StartedGroup==0) {
                            FirstSat=j;
                            StartedGroup=1;
                           }
                           lastSat=j;
                       }
                   }
               }

           }
        }
    } else {
        //Add or remove only the non default enabled or disabled constellations
        for(i=0;i<MAX_GNSS;i++) {
            if ( (listConstFullEnabled[i]==1 || listConstPartiallyEnabled[i]==1 ) && defaultConstEnabled[currentMode][i]==0) {
                if (GNSSAddString == "") {
                    GNSSAddString += "+";
                }
                GNSSAddString += indentifierGNSS[i];
            } else if ( (listConstFullDisabled[i]==1 && defaultConstEnabled[currentMode][i]==1)  ) {
                if (GNSSRemoveString == "") {
                    GNSSRemoveString += "-";
                }
                GNSSRemoveString += indentifierGNSS[i];
            }
        }
        if (GNSSAddString!="") {
            GNSSAddString += "0";
        }
        if (GNSSRemoveString!="") {
            GNSSRemoveString += "0";
        }
        //Loop again to fill partially enabled constellations
        for(i=0;i<MAX_GNSS;i++) {
           if (listConstPartiallyEnabled[i]==1) {
               FirstSat=0;
               lastSat=0;
               StartedGroup=0;
               FirstRange=1;
               if (GNSSPartiallyRemoveString == "") {
                   GNSSPartiallyRemoveString += "-" + indentifierGNSS[i];
               } else {
                   GNSSPartiallyRemoveString += " -" + indentifierGNSS[i];
               }
               for(j=1;j<=listMaxSatGNSS[i];j++) {
                   if (i==GEO) {
                       PRNoffset=GEOMINPRNOFFSET;
                   } else {
                       PRNoffset=0;
                   }
                   if (PushButtonSatWidgets[i][j]->palette().window().color().name()==GreenColor && FirstSat>0 ) {
                       if (lastSat==FirstSat) {
                           //Number of continuous red satellites until current selected satellites were only one
                           if (FirstRange==1) {
                               FirstRange=0;
                           } else {
                               GNSSPartiallyRemoveString += ".";
                           }
                           GNSSPartiallyRemoveString += QString("%1").arg(lastSat+PRNoffset);
                       } else {
                           //Number of continuous red satellites until current selected satellites were more than one. Create a range of satellites
                           if (FirstRange==1) {
                               FirstRange=0;
                           } else {
                               GNSSPartiallyRemoveString += ".";
                           }
                           GNSSPartiallyRemoveString += QString("%1").arg(FirstSat+PRNoffset) + "-" + QString("%1").arg(lastSat+PRNoffset);
                       }
                       StartedGroup=0;
                       FirstSat=0;
                       lastSat=0;
                   } else if (PushButtonSatWidgets[i][j]->palette().window().color().name()==RedColor) {
                       if (j==listMaxSatGNSS[i]) {
                           if ((j-FirstSat)==0 || FirstSat==0) {
                               //Number of continuous red satellites until current selected satellites were only one
                               if (FirstRange==1) {
                                   FirstRange=0;
                               } else {
                                   GNSSPartiallyRemoveString += ".";
                               }
                               GNSSPartiallyRemoveString += QString("%1").arg(j+PRNoffset);
                           } else {
                               //Number of continuous red satellites until current selected satellites were more than one. Create a range of satellites
                               if (FirstRange==1) {
                                   FirstRange=0;
                               } else {
                                   GNSSPartiallyRemoveString += ".";
                               }
                               GNSSPartiallyRemoveString += QString("%1").arg(FirstSat+PRNoffset) + "-" + QString("%1").arg(j+PRNoffset);
                           }
                       } else {
                           if (StartedGroup==0) {
                            FirstSat=j;
                            StartedGroup=1;
                           }
                           lastSat=j;
                       }
                   }
               }

           }
        }
    }

    //Add all satellite addition/removal strings to GNSSSaveString (with spaces as needed)
    if (GNSSAddString != "") {
        GNSSSaveString += GNSSAddString;
        if (GNSSRemoveString!= "" || GNSSPartiallyRemoveString!="") {
            GNSSSaveString += " ";
        }
    }
    if (GNSSRemoveString!="") {
        GNSSSaveString += GNSSRemoveString;
        if (GNSSPartiallyRemoveString!="") {
            GNSSSaveString += " ";
        }
    }
    if (GNSSPartiallyRemoveString!="") {
       GNSSSaveString += GNSSPartiallyRemoveString;
    }

    QStringList GNSSSaveStringList = GNSSSaveString.split(QRegularExpression("\\s+"));
    int numParamSatList=GNSSSaveStringList.count();

    for(int iParam=0;iParam<numParamSatList;iParam++) {
        for(int iParam2=0;iParam2<numParamSatList;iParam2++) {
            if (iParam==iParam2) continue;
            if (GNSSSaveStringList[iParam]=="" || GNSSSaveStringList[iParam2]=="") continue;
            int posConst1LetterPos=0,posConst2LetterPos=0;
            QString isys1="",isys2="";
            if (GNSSSaveStringList[iParam].left(1)=="-" ||GNSSSaveStringList[iParam].left(1)=="+" ) {
                posConst1LetterPos=1;
                isys1=GNSSSaveStringList[iParam].mid(posConst1LetterPos,1);
                GNSSSaveStringList[iParam].replace(posConst1LetterPos,1,"<"); //Replace with temporary character for comparing
            } else {
                isys1=GNSSSaveStringList[iParam].left(1);
                GNSSSaveStringList[iParam].replace(posConst1LetterPos,1,"<"); //Replace with temporary character for comparing
            }
            if (GNSSSaveStringList[iParam2].left(1)=="-" ||GNSSSaveStringList[iParam2].left(1)=="+" ) {
                posConst2LetterPos=1;
                isys2=GNSSSaveStringList[iParam2].mid(posConst2LetterPos,1);
                GNSSSaveStringList[iParam2].replace(posConst2LetterPos,1,"<"); //Replace with temporary character for comparing
            } else {
                isys2=GNSSSaveStringList[iParam2].left(1);
                GNSSSaveStringList[iParam].replace(posConst2LetterPos,1,"<"); //Replace with temporary character for comparing
            }
            if (QString::compare(GNSSSaveStringList[iParam],GNSSSaveStringList[iParam2])==0 ) {
                GNSSSaveStringList[iParam].replace(posConst1LetterPos,1,isys1); //Restore original constellation letter
                GNSSSaveStringList[iParam].insert(posConst1LetterPos+1,isys2);
                GNSSSaveStringList[iParam2]="";
            } else {
                GNSSSaveStringList[iParam].replace(posConst1LetterPos,1,isys1); //Restore original constellation letter
                GNSSSaveStringList[iParam2].replace(posConst2LetterPos,1,isys2); //Restore original constellation letter
            }
        }
    }

    int firstParamSatList=1;
    for(int iParam=0;iParam<numParamSatList;iParam++) {
        if (GNSSSaveStringList[iParam].length()>0) {
            if (firstParamSatList==1) {
                firstParamSatList=0;
                *saveString += "-pre:sat";
                *runString << "-pre:sat";
            }
            *saveString += " " + GNSSSaveStringList[iParam];
            QStringList tmpString = GNSSSaveStringList[iParam].split(QRegularExpression("\\s+"));
            for(int k=0;k<tmpString.size();k++) {
                *runString << tmpString[k];
            }
        }
    }
    *saveString += "\n";

    //Get measurement selection (filter) options in advance
    for (int isys=0;isys<MAX_GNSS;isys++) {
        GNSSMeasAll[isys][0][0]=GNSSMeasAll[isys][0][1]=GNSSMeasAll[isys][1][0]=GNSSMeasAll[isys][1][1]=GNSSMeasAll[isys][2][0]=GNSSMeasAll[isys][2][1]="";
        GNSSNoiseAll[isys][0][0]=GNSSNoiseAll[isys][0][1]=GNSSNoiseAll[isys][1][0]=GNSSNoiseAll[isys][1][1]=GNSSNoiseAll[isys][2][0]=GNSSNoiseAll[isys][2][1]="";
        GNSSSmoothWithAll[isys][0]=GNSSSmoothWithAll[isys][1]=GNSSSmoothWithAll[isys][2]="";
    }
    //SPP and PPP mode
    if (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false && ui->radioButtonSmoothing->isChecked()==false) {
        SmoothAuto=0;
        MeasOK=0;
        for (int isys=0;isys<MAX_GNSS;isys++) { //constellation
            if (!CheckBoxGNSS[isys]->isChecked()) continue;
            for (int icomb=0; icomb<MAXMEASTOFILTER; icomb++) { //combination
                if (FrameGNSSMeasComb[isys][icomb]->isHidden()) break;
                if (ui->radioButtonSelectionGraphic->isChecked()) {
                    if (FrameGNSSMeasFreq[isys][icomb][GCARRAYPOS]->isHidden()) break;
                    //GC measurements will be saved in code position, so most of the code can be reutilized
                    if (ComboBoxGNSSFreq[isys][icomb][GCARRAYPOS]->currentIndex()>0) {
                        GNSSMeasAll[isys][icomb][CODEARRAYPOS] = indentifierGNSS[isys]+ "0-G" + FreqGNSSList[isys][ ComboBoxGNSSFreq[isys][icomb][GCARRAYPOS]->currentIndex()-1 ];
                        if (ComboBoxGNSSMeas[isys][icomb][GCARRAYPOS][0]->currentIndex()>0) {
                            GNSSMeasAll[isys][icomb][CODEARRAYPOS] += "-" + ComboBoxGNSSMeas[isys][icomb][GCARRAYPOS][0]->currentText() + "-" +ComboBoxGNSSMeas[isys][icomb][GCARRAYPOS][1]->currentText();
                        }
                        MeasOK++;
                    }
                } else {
                    for (int iCP=0; iCP<MEASANDPHASENUMSLOTS; iCP++) { //code or phase
                        if (FrameGNSSMeasFreq[isys][icomb][iCP]->isHidden()) break;
                        if (ComboBoxGNSSFreq[isys][icomb][iCP]->currentIndex()>0){
                            if (ui->radioButtonSingleFreq->isChecked() == true ){ //Single Frequency
                                if (ComboBoxGNSSMeas[isys][icomb][iCP][0]->currentIndex()==0) {
                                    GNSSMeasAll[isys][icomb][iCP] = indentifierGNSS[isys]+"0-" + MeasSelectTypeGNSS[iCP]+FreqGNSSList[isys][ ComboBoxGNSSFreq[isys][icomb][iCP]->currentIndex()-1 ];
                                } else {
                                    GNSSMeasAll[isys][icomb][iCP] = indentifierGNSS[isys]+"0-" + ComboBoxGNSSMeas[isys][icomb][iCP][0]->currentText();
                                }
                                MeasOK++;
                            }
                            else if ( ui->radioButtonDualFreq->isChecked() == true ){ //Dual Frequency
                                GNSSMeasAll[isys][icomb][iCP] = indentifierGNSS[isys]+"0-" + ComboBoxGNSSFreq[isys][icomb][iCP]->currentText();
                                if (ComboBoxGNSSMeas[isys][icomb][iCP][0]->currentIndex()>0) {
                                    GNSSMeasAll[isys][icomb][iCP] += "-" + ComboBoxGNSSMeas[isys][icomb][iCP][0]->currentText() + "-" +ComboBoxGNSSMeas[isys][icomb][iCP][1]->currentText();
                                }
                                MeasOK++;
                            }
                        }
                    }
                }
            }
        }
    }
    /*
     *This code is commented as it shows the filter commands to put the default measurements in SBAS 1F, SBAS DFMC and DGNSS,
     *but command line does not support providing measurements in these modes (except for DGNSS, but it is currently not implemented)

     else if (ui->labelCurrentTemplate->text()!="SPP" && ui->labelCurrentTemplate->text()!="PPP"){
        SmoothAuto=0;
        MeasOK=0;
        //SBAS 1F or DGNSS
        if ( 0 && WriteAllParameters && (ui->labelCurrentTemplate->text()=="SBAS 1F" || ui->labelCurrentTemplate->text()=="DGNSS") ){
            GNSSMeasAll[GPS][0][0] = "G0-C1C";
            MeasOK++;
        }
        // SBAS DFMC
        else if ( 0 && WriteAllParameters && ui->labelCurrentTemplate->text()=="SBAS DFMC"){
            if (ui->checkBoxGPS->isChecked() && WriteAllParameters){ //GPS
                GNSSMeasAll[GPS][0][0] = "G0-IF15-C1C-C5Q";
                MeasOK++;
            }
            if (ui->checkBoxGalileo->isChecked() && WriteAllParameters){ //Galileo
                GNSSMeasAll[Galileo][0][0] = "E0-IF15-C1C-C5Q";
                MeasOK++;
            }
            if (ui->checkBoxBDS->isChecked() && WriteAllParameters){ //BDS
                GNSSMeasAll[BDS][0][0] = "C0-IF15-C1P-C5P";
                MeasOK++;
            }
        }
    }*/
    // Smoothing
    if ( ui->radioButtonSmoothing->isChecked() == true ) {
        QString measPositionNumeral[3]={"first", "second", "third"};
        if ( ui->lineEditSmoothing->text() == "" ) {
            *errorString += "FILTER: A numerical value is required for Pseudorange Smoothing (epochs) [In the Filter Section - Measurements - Selection].\n";
        } else if (ui->lineEditSmoothing->text().toInt() == 0 ) {
            *errorString += "FILTER: Pseudorange Smoothing (epochs) cannot be 0 [In the Filter Section - Measurements - Selection].\n";
        } else {
            if ( (( (ui->groupBoxSbas->isChecked()==true || ui->groupBoxReferenceStation->isChecked()==true) && ui->lineEditSmoothing->text().toInt() !=100) ||
                    (ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false) ) || WriteAllParameters==1) {
                *saveString += "-pre:smooth " + ui->lineEditSmoothing->text() + "\n";
                *runString << "-pre:smooth" << ui->lineEditSmoothing->text();
            }
        }
        /* smoothing measurements */
        if ( ui->groupBoxSbas->isChecked()==false && ui->groupBoxReferenceStation->isChecked()==false ){
            SmoothAuto=0;
            MeasOK=0;
            int SmoothWithOK=0;
            int numSmoothMeas=0;
            for (int isys=0;isys<MAX_GNSS;isys++) { //constellation
                if (!CheckBoxGNSS[isys]->isChecked()) {
                    SmoothAuto++;
                    numSmoothMeas++;
                    continue;
                }
                for (int icomb=0; icomb<3; icomb++) { //combination
                    if (FrameGNSSMeasComb[isys][icomb]->isHidden()) break;
                    //measurement
                    if (ui->radioButtonSingleFreq->isChecked() == true ){ //Single Frequency
                        if (ComboBoxGNSSMeas[isys][icomb][0][0]->currentIndex()==0)
                            GNSSMeasAll[isys][icomb][0] = indentifierGNSS[isys]+"0-" + MeasSelectTypeGNSS[0]+FreqGNSSList[isys][ ComboBoxGNSSFreq[isys][icomb][0]->currentIndex() ];
                        else GNSSMeasAll[isys][icomb][0] = indentifierGNSS[isys]+"0-" + ComboBoxGNSSMeas[isys][icomb][0][0]->currentText();
                        MeasOK++;
                    }
                    else if ( ui->radioButtonDualFreq->isChecked() == true ){ //Dual Frequency
                        GNSSMeasAll[isys][icomb][0] = indentifierGNSS[isys]+"0-" + ComboBoxGNSSFreq[isys][icomb][0]->currentText();
                        if (ComboBoxGNSSMeas[isys][icomb][0][0]->currentIndex()>0)
                            GNSSMeasAll[isys][icomb][0] += "-" + ComboBoxGNSSMeas[isys][icomb][0][0]->currentText() + "-" +ComboBoxGNSSMeas[isys][icomb][0][1]->currentText();
                        MeasOK++;
                    }
                    if (GNSSMeasAll[isys][icomb][0].size()<1) break;
                    //smoothed-with measurement
                    numSmoothMeas++;
                    if ( ComboBoxSmoothWithTypeAll[isys][icomb]->currentIndex()==0 ) {
                        SmoothAuto++;
                    } else if ( ComboBoxSmoothWithTypeAll[isys][icomb]->currentIndex()==1 ){ //SF
                        if (ComboBoxSmoothWithMeasAll[isys][icomb][1]->currentIndex()==0)
                            GNSSSmoothWithAll[isys][icomb] = MeasSelectTypeGNSS[1]+FreqGNSSList[isys][ ComboBoxSmoothWithFreqAll[isys][icomb][0]->currentIndex() ];
                        else GNSSSmoothWithAll[isys][icomb] = ComboBoxSmoothWithMeasAll[isys][icomb][1]->currentText();
                        SmoothWithOK=1;
                    } else if ( ComboBoxSmoothWithTypeAll[isys][icomb]->currentIndex()==2 ){ //GC
                        GNSSSmoothWithAll[isys][icomb] = "G"+FreqGNSSList[isys][ ComboBoxSmoothWithFreqAll[isys][icomb][0]->currentIndex() ];
                        if (ComboBoxSmoothWithMeasAll[isys][icomb][1]->currentIndex()>0)
                            GNSSSmoothWithAll[isys][icomb] += "-" + ComboBoxSmoothWithMeasAll[isys][icomb][0]->currentText() + "-" + ComboBoxSmoothWithMeasAll[isys][icomb][1]->currentText();
                        SmoothWithOK=1;
                    } else if ( ComboBoxSmoothWithTypeAll[isys][icomb]->currentIndex()==3 ){ //IF
                        if (FreqGNSSList[isys][ ComboBoxSmoothWithFreqAll[isys][icomb][0]->currentIndex() ]==FreqGNSSList[isys][ ComboBoxSmoothWithFreqAll[isys][icomb][1]->currentIndex() ]) {
                            *errorString += "FILTER: Ionosphere free (IF) combination for smoothing cannot have the two frequencies equal. Both are set to " + FreqGNSSList[isys][ ComboBoxSmoothWithFreqAll[isys][icomb][0]->currentIndex() ] + " for " + GNSSName[isys] + " " + measPositionNumeral[icomb] + " measurement.\n";
                        }
                        GNSSSmoothWithAll[isys][icomb] = "IF" + FreqGNSSList[isys][ ComboBoxSmoothWithFreqAll[isys][icomb][0]->currentIndex() ] + FreqGNSSList[isys][ ComboBoxSmoothWithFreqAll[isys][icomb][1]->currentIndex() ];
                            if (ComboBoxSmoothWithMeasAll[isys][icomb][1]->currentIndex()==0) GNSSSmoothWithAll[isys][icomb] += "-Phase";
                            else GNSSSmoothWithAll[isys][icomb] += "-" + ComboBoxSmoothWithMeasAll[isys][icomb][1]->currentText() + "-" + ComboBoxSmoothWithMeasAll[isys][icomb][2]->currentText();
                            SmoothWithOK=1;
                    } else if ( ComboBoxSmoothWithTypeAll[isys][icomb]->currentIndex()==4 ){ //DF
                            GNSSSmoothWithAll[isys][icomb] = "DF" + FreqGNSSList[isys][ ComboBoxSmoothWithFreqAll[isys][icomb][0]->currentIndex() ] + FreqGNSSList[isys][ ComboBoxSmoothWithFreqAll[isys][icomb][1]->currentIndex() ];
                            if (FreqGNSSList[isys][ ComboBoxSmoothWithFreqAll[isys][icomb][0]->currentIndex() ]==FreqGNSSList[isys][ ComboBoxSmoothWithFreqAll[isys][icomb][1]->currentIndex() ]) {
                                *errorString += "FILTER: Divergence free (DF) combination for smoothing cannot have the two frequencies equal. Both are set to " + FreqGNSSList[isys][ ComboBoxSmoothWithFreqAll[isys][icomb][0]->currentIndex() ] + " for " + GNSSName[isys] + " " + measPositionNumeral[icomb] + " measurement.\n";
                            }
                            if (ComboBoxSmoothWithMeasAll[isys][icomb][1]->currentIndex()==0) GNSSSmoothWithAll[isys][icomb] += "-Phase";
                            else GNSSSmoothWithAll[isys][icomb] += "-" + ComboBoxSmoothWithMeasAll[isys][icomb][1]->currentText() + "-" + ComboBoxSmoothWithMeasAll[isys][icomb][2]->currentText();
                            SmoothWithOK=1;
                    }

                }

            }

            if (SmoothAuto==numSmoothMeas){
                *saveString += "-pre:smoothauto\n";
                *runString << "-pre:smoothauto";
            }
            if (SmoothWithOK>0){
                *saveString += "-pre:smoothmeas";
                *runString << "-pre:smoothmeas";
                QString satString[MAX_GNSS][6]={{""}};
                int     numSatString[MAX_GNSS]={0};
                for (int isys=0;isys<MAX_GNSS;isys++) { //constellation
                    if (!CheckBoxGNSS[isys]->isChecked()) continue;
                    if ( GNSSMeasAll[isys][1][0].size()>0 ) {
                        //NOTE: For smoothing, only one measurement of a given type can be smoothed at a time, therefore we remove each repeated code measurement
                        //Check code measurement is not repeated. In that case, skip it
                        if (QString::compare(GNSSMeasAll[isys][1][0], GNSSMeasAll[isys][0][0], Qt::CaseInsensitive)==0 && FrameGNSSMeasComb[isys][1]->isHidden()==false) {

                            *warningString += "FILTER: Code measurements to be smoothed in positions 1 and 2 for constellation " + GNSSName[isys] + " are repeated. They will be used only once.\n";
                            GNSSMeasAll[isys][1][0]="";
                        } else if (QString::compare(GNSSMeasAll[isys][1][0], GNSSMeasAll[isys][2][0], Qt::CaseInsensitive)==0 && FrameGNSSMeasComb[isys][1]->isHidden()==false ) {
                            *warningString += "FILTER: Code measurements to be smoothed in positions 2 and 3 for constellation " + GNSSName[isys] + " are repeated. They will be used only once.\n";
                            GNSSMeasAll[isys][1][0]="";
                        }
                    }
                    if ( GNSSMeasAll[isys][2][0].size()>0) {
                        //Check code measurement is not repeated. In that case, skip it
                        if (QString::compare(GNSSMeasAll[isys][2][0], GNSSMeasAll[isys][0][0], Qt::CaseInsensitive)==0 && FrameGNSSMeasComb[isys][2]->isHidden()==false) {
                            *warningString += "FILTER: Code measurements to be smoothed in positions 1 and 3 for constellation " + GNSSName[isys] + " are repeated. They will be used only once.\n";
                            GNSSMeasAll[isys][2][0]="";
                        } else if (QString::compare(GNSSMeasAll[isys][2][0], GNSSMeasAll[isys][1][0], Qt::CaseInsensitive)==0 && FrameGNSSMeasComb[isys][2]->isHidden()==false ) {
                            *warningString += "FILTER: Code measurements to be smoothed in positions 2 and 3 for constellation " + GNSSName[isys] + " are repeated. They will be used only once.\n";
                            GNSSMeasAll[isys][2][0]="";
                         }
                    }

                    for (int icomb=0; icomb<3; icomb++) { //combination
                         if ( GNSSMeasAll[isys][icomb][0].size()>0 && ComboBoxSmoothWithTypeAll[isys][icomb]->currentIndex()>0 ) {
                             satString[isys][numSatString[isys]] = GNSSMeasAll[isys][icomb][0]+ " " + GNSSSmoothWithAll[isys][icomb];
                             numSatString[isys]++;

                         } else if (GNSSMeasAll[isys][icomb][0].size()>0) {
                             satString[isys][numSatString[isys]] = GNSSMeasAll[isys][icomb][0]+ " auto";
                             numSatString[isys]++;
                         }
                     }
                }

                //Loop to join same measurements from different constellations
                for (int isys=0;isys<MAX_GNSS;isys++) {
                    for (int istr=0; istr<numSatString[isys]; istr++) {
                        for (int isys2=0;isys2<MAX_GNSS;isys2++) {
                            for (int istr2=0; istr2<numSatString[isys2]; istr2++) {
                                if (isys==isys2 && istr==istr2) continue;
                                if (satString[isys][istr]=="" || satString[isys2][istr2]=="") continue;
                                int pos1,pos2;
                                pos1=satString[isys][istr].indexOf("-")+1;
                                pos2=satString[isys2][istr2].indexOf("-")+1;

                                if (QString::compare(satString[isys][istr].mid(pos1),satString[isys2][istr2].mid(pos2))==0 ) {
                                    satString[isys][istr].insert(pos1-2,indentifierGNSS[isys2]);
                                    satString[isys2][istr2]="";
                                }
                            }
                        }
                    }
                }
                for (int isys=0;isys<MAX_GNSS;isys++) {
                    for (int istr=0; istr<numSatString[isys]; istr++) {
                        if (satString[isys][istr]=="") continue;
                        *saveString += " " + satString[isys][istr];
                        QStringList tmpString = satString[isys][istr].split(QRegularExpression("\\s+"));
                        for(int k=0;k<tmpString.size();k++) {
                            *runString << tmpString[k];
                        }
                    }
                }
                *saveString += "\n";
            }
        }
    }

    //Noise Configuration for all GNSS
    QString codeErrorText="pseudorange";
    int codeMeasPos=CODEARRAYPOS;
    QString defaultFixedWeightCode=SingleFreqDefaultFixedWeight[CODEARRAYPOS];
    if (ui->radioButtonSelectionGraphic->isChecked()) {
        //When graphic combinaiton is used, the code slot will be used to reuse code
        codeErrorText="graphic combination";
        codeMeasPos=GCARRAYPOS;
        defaultFixedWeightCode=SingleFreqDefaultFixedWeight[GCARRAYPOS];
    }
    for (int isys=0;isys<MAX_GNSS;isys++) { //constellation
        if (!CheckBoxGNSS[isys]->isChecked()) continue;
        for (int icomb=0; icomb<MAXMEASTOFILTER; icomb++) { //combination
            if (FrameGNSSMeasComb[isys][icomb]->isHidden()) break;
            //code or GC
            if ( ComboBoxGNSSFreq[isys][icomb][codeMeasPos]->currentIndex()!=0 || ui->radioButtonSmoothing->isChecked() ){
                if ( ComboBoxstdDevType[isys][icomb][codeMeasPos]->currentIndex() == 0 ) { //fixed mode
                    if ( LineEditstdDevValue[isys][icomb][codeMeasPos][0]->text() == "" ) {
                        *errorString += "FILTER: Fixed standard deviation (" + codeErrorText + ") cannot be empty.\n";
                    } if ( LineEditstdDevValue[isys][icomb][codeMeasPos][0]->text().toDouble() == 0. ) {
                        *errorString += "FILTER: Fixed standard deviation (" + codeErrorText + ") cannot be 0.\n";
                    }
                    // In PPP is by default 3, In SPP is by default 1, in GC it is 0.5
                    else if ( (LineEditstdDevValue[isys][icomb][codeMeasPos][0]->text() != DualFreqDefaultFixedWeight[CODEARRAYPOS] && ui->radioButtonDualFreq->isChecked()==true) || (LineEditstdDevValue[isys][icomb][codeMeasPos][0]->text() != defaultFixedWeightCode && ui->radioButtonSingleFreq->isChecked()==true) ) {
                        GNSSNoiseModeAll[isys][icomb][CODEARRAYPOS] = GNSSNoiseMode[0];
                        GNSSNoiseAll[isys][icomb][CODEARRAYPOS] = LineEditstdDevValue[isys][icomb][codeMeasPos][0]->text();
                    }
                } else if ( ComboBoxstdDevType[isys][icomb][codeMeasPos]->currentIndex() == 1 ) { //elevation mode
                    //Elevation weight, not the default in any mode
                    if ( LineEditstdDevValue[isys][icomb][codeMeasPos][0]->text() == "" || LineEditstdDevValue[isys][icomb][codeMeasPos][1]->text() == "" || LineEditstdDevValue[isys][icomb][codeMeasPos][2]->text() == "" ) {
                        *errorString += "FILTER: Elevation-dependant standard deviation (" + codeErrorText + ") values cannot be empty.\n";
                    } else if ( LineEditstdDevValue[isys][icomb][codeMeasPos][0]->text().toDouble() == 0. && LineEditstdDevValue[isys][icomb][codeMeasPos][1]->text().toDouble() == 0.) {
                        *errorString += "FILTER: Elevation-dependant standard deviation (" + codeErrorText + ") a and b values cannot be both 0.\n";
                    } else if ( LineEditstdDevValue[isys][icomb][codeMeasPos][2]->text().toDouble() == 0. ) {
                        *errorString += "FILTER: Elevation-dependant standard deviation (" + codeErrorText + ") c value cannot be 0.\n";
                    } else {
                        GNSSNoiseModeAll[isys][icomb][CODEARRAYPOS] = GNSSNoiseMode[1];
                        GNSSNoiseAll[isys][icomb][CODEARRAYPOS] = LineEditstdDevValue[isys][icomb][codeMeasPos][0]->text() + " " + LineEditstdDevValue[isys][icomb][codeMeasPos][1]->text() + " " + LineEditstdDevValue[isys][icomb][codeMeasPos][2]->text();
                    }
                } else if ( ComboBoxstdDevType[isys][icomb][codeMeasPos]->currentIndex() > 1 ) { //sin(elevation), SNR, sin(SNR)
                    //Elevation weight, not the default in any mode
                    if ( LineEditstdDevValue[isys][icomb][codeMeasPos][0]->text() == "" || LineEditstdDevValue[isys][icomb][codeMeasPos][1]->text() == "") {
                        *errorString += "FILTER: Elevation-dependant standard deviation (" + codeErrorText + ") values cannot be empty.\n";
                    } else if ( LineEditstdDevValue[isys][icomb][codeMeasPos][0]->text().toDouble() == 0. && LineEditstdDevValue[isys][icomb][codeMeasPos][1]->text().toDouble() == 0.) {
                        *errorString += "FILTER: Elevation-dependant standard deviation (" + codeErrorText + ") a and b values cannot be both 0.\n";
                    } else {
                        if (ComboBoxstdDevType[isys][icomb][codeMeasPos]->currentIndex() == 2){ //sin(elevation)
                            GNSSNoiseModeAll[isys][icomb][CODEARRAYPOS] = GNSSNoiseMode[2];
                            GNSSNoiseAll[isys][icomb][CODEARRAYPOS] = LineEditstdDevValue[isys][icomb][codeMeasPos][0]->text() + " " + LineEditstdDevValue[isys][icomb][codeMeasPos][1]->text();
                        } else if (ComboBoxstdDevType[isys][icomb][codeMeasPos]->currentIndex() == 3){ //SNR
                            GNSSNoiseModeAll[isys][icomb][CODEARRAYPOS] = GNSSNoiseMode[3];
                            GNSSNoiseAll[isys][icomb][CODEARRAYPOS] = LineEditstdDevValue[isys][icomb][codeMeasPos][0]->text() + " " + LineEditstdDevValue[isys][icomb][codeMeasPos][1]->text();
                        } else if (ComboBoxstdDevType[isys][icomb][codeMeasPos]->currentIndex() == 4){ //SNR+Elevation
                            GNSSNoiseModeAll[isys][icomb][CODEARRAYPOS] = GNSSNoiseMode[4];
                            GNSSNoiseAll[isys][icomb][CODEARRAYPOS] = LineEditstdDevValue[isys][icomb][codeMeasPos][0]->text() + " " + LineEditstdDevValue[isys][icomb][codeMeasPos][1]->text();
                        }
                    }
                }
            }
            //phase
            if ( ComboBoxGNSSFreq[isys][icomb][PHASEARRAYPOS]->currentIndex()!=0 && !FrameGNSSMeasFreq[isys][icomb][PHASEARRAYPOS]->isHidden() && !ui->radioButtonSelectionGraphic->isChecked() ){
                if ( ComboBoxstdDevType[isys][icomb][PHASEARRAYPOS]->currentIndex() == 0 ) { //fixed mode
                    if ( LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][0]->text() == "" ) {
                        *errorString += "FILTER: Fixed standard deviation (carrier phase) cannot be empty.\n";
                    } if ( LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][0]->text().toDouble() == 0. ) {
                        *errorString += "FILTER: Fixed standard deviation (carrier phase) cannot be 0.\n";
                    }
                    // In PPP is by default 3, In SPP is by default 1
                    else if ( (LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][0]->text() != DualFreqDefaultFixedWeight[PHASEARRAYPOS] && ui->radioButtonDualFreq->isChecked()==true) || (LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][0]->text() != SingleFreqDefaultFixedWeight[PHASEARRAYPOS] && ui->radioButtonSingleFreq->isChecked()==true) ) {
                        GNSSNoiseModeAll[isys][icomb][PHASEARRAYPOS] = GNSSNoiseMode[0];
                        GNSSNoiseAll[isys][icomb][PHASEARRAYPOS] = LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][0]->text();
                    }
                } else if ( ComboBoxstdDevType[isys][icomb][PHASEARRAYPOS]->currentIndex() == 1 ) { //elevation mode
                    //Elevation weight, not the default in any mode
                    if ( LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][0]->text() == "" || LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][1]->text() == "" || LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][2]->text() == "" ) {
                        *errorString += "FILTER: Elevation-dependant standard deviation (carrier phase) values cannot be empty.\n";
                    } else if ( LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][0]->text().toDouble() == 0. && LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][1]->text().toDouble() == 0.) {
                        *errorString += "FILTER: Elevation-dependant standard deviation (carrier phase) a and b values cannot be both 0.\n";
                    } else if ( LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][2]->text().toDouble() == 0. ) {
                        *errorString += "FILTER: Elevation-dependant standard deviation (carrier phase) c value cannot be 0.\n";
                    } else {
                        GNSSNoiseModeAll[isys][icomb][PHASEARRAYPOS] = GNSSNoiseMode[1];
                        GNSSNoiseAll[isys][icomb][PHASEARRAYPOS] = LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][0]->text() + " " + LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][1]->text() + " " + LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][2]->text();
                    }
                } else if ( ComboBoxstdDevType[isys][icomb][PHASEARRAYPOS]->currentIndex() > 1 ) { //sin(elevation), SNR, sin(SNR)
                    //Elevation weight, not the default in any mode
                    if ( LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][0]->text() == "" || LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][1]->text() == "") {
                        *errorString += "FILTER: Elevation-dependant standard deviation (carrier phase) values cannot be empty.\n";
                    } else if ( LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][0]->text().toDouble() == 0. && LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][1]->text().toDouble() == 0.) {
                        *errorString += "FILTER: Elevation-dependant standard deviation (carrier phase) a and b values cannot be both 0.\n";
                    } else {
                        if (ComboBoxstdDevType[isys][icomb][PHASEARRAYPOS]->currentIndex() == 2){ //sin(elevation)
                            GNSSNoiseModeAll[isys][icomb][PHASEARRAYPOS] = GNSSNoiseMode[2];
                            GNSSNoiseAll[isys][icomb][PHASEARRAYPOS] = LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][0]->text() + " " + LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][1]->text();
                        } else if (ComboBoxstdDevType[isys][icomb][PHASEARRAYPOS]->currentIndex() == 3){ //SNR
                            GNSSNoiseModeAll[isys][icomb][PHASEARRAYPOS] = GNSSNoiseMode[3];
                            GNSSNoiseAll[isys][icomb][PHASEARRAYPOS] = LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][0]->text() + " " + LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][1]->text();
                        } else if (ComboBoxstdDevType[isys][icomb][PHASEARRAYPOS]->currentIndex() == 4){ //SNR+Elevation
                            GNSSNoiseModeAll[isys][icomb][PHASEARRAYPOS] = GNSSNoiseMode[4];
                            GNSSNoiseAll[isys][icomb][PHASEARRAYPOS] = LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][0]->text() + " " + LineEditstdDevValue[isys][icomb][PHASEARRAYPOS][1]->text();
                        }
                    }
                }
            }
        }
    }

    // SBAS Options
    if ( ui->labelCurrentTemplate->text() == "SBAS 1F" || ui->groupBoxSbas->isChecked()==true ) {
        // GEO selection
        switch ( ui->comboBoxGEOselection->currentIndex() ) {
            case 0 : {
                *saveString += "-pre:geosel 1\n";
                *runString << "-pre:geosel" << "1";
                break;
            }
            case 1 : {
                *saveString += "-pre:geosel 0\n";
                *runString << "-pre:geosel" << "0";
                break;
            }
            case 2 : {
                //Default in SBAS, no need to set the option
                if (WriteAllParameters==1) {
                    *saveString += "-pre:geosel 2\n";
                    *runString << "-pre:geosel" << "2";
                }
                break;
            }
            case 3 : {
                if ( ui->lineEditGEOselection->text() == "" ) {
                    *errorString += "MODEL: Selected PRN for GEO selection in [SBAS Options] cannot be empty.\n";
                } else if ( ui->lineEditGEOselection->text().toInt() < 120 ) {
                    *errorString += "MODEL: Selected PRN for GEO selection in [SBAS Options] must be between 120 and 210.\n";
                } else {
                    *saveString += "-pre:geosel " + ui->lineEditGEOselection->text() + "\n";
                    *runString << "-pre:geosel" << ui->lineEditGEOselection->text();
                }
                break;
            }
        }
        // GEO exclude
        if ( ui->checkBoxGEOexclusion->isChecked() == true ) {
            switch ( ui->comboBoxGEOexclusion->currentIndex() ) {
                case 0 : {
                    if ( ui->lineEditGEOexclusion1->text() == "" ) {
                         *errorString += "MODEL: GEO exclusion in [SBAS Options] cannot be empty.\n";
                     } else if ( ui->lineEditGEOexclusion1->text().toInt() < 120 ) {
                        *errorString += "MODEL: GEO exclusion in [SBAS Options] must be between 120 and 210.\n";
                    } else {
                        *saveString += "-pre:geoexclude " + ui->lineEditGEOexclusion1->text() + "\n";
                        *runString << "-pre:geoexclude" << ui->lineEditGEOexclusion1->text();
                    }
                    if(ui->comboBoxGEOselection->currentIndex()==3) {
                        //Check that GEO unselected is not the GEO selected
                        if (ui->lineEditGEOselection->text()==ui->lineEditGEOexclusion1->text()) {
                            *errorString += "MODEL: GEO " + ui->lineEditGEOselection->text() + " selected for processing cannot be excluded\n";
                        }
                    }
                    break;
                }
                case 1 : {
                    if ( ui->lineEditGEOexclusion1->text() == "" || ui->lineEditGEOexclusion2->text() == "" ) {
                        *errorString += "MODEL: GEO exclusion in [SBAS Options] cannot be empty.\n";
                    } else if ( ui->lineEditGEOexclusion1->text().toInt() < 120 || ui->lineEditGEOexclusion2->text().toInt() < 120 ) {
                        *errorString += "MODEL: GEO exclusion in [SBAS Options] must be between 120 and 210.\n";
                    } else {
                        *saveString += "-pre:geoexclude " + ui->lineEditGEOexclusion1->text() + "," + ui->lineEditGEOexclusion2->text() + "\n";
                        *runString << "-pre:geoexclude" << ui->lineEditGEOexclusion1->text() + "," + ui->lineEditGEOexclusion2->text();
                    }
                    if(ui->comboBoxGEOselection->currentIndex()==3) {
                        //Check that GEO unselected is not the GEO selected
                        if ( (ui->lineEditGEOselection->text()==ui->lineEditGEOexclusion1->text()) || (ui->lineEditGEOselection->text()==ui->lineEditGEOexclusion2->text())) {
                            *errorString += "MODEL: GEO " + ui->lineEditGEOselection->text() + " selected for processing cannot be excluded\n";
                        }
                    }
                    break;
                }
                case 2 : {
                    if ( ui->lineEditGEOexclusion1->text() == "" || ui->lineEditGEOexclusion2->text() == "" || ui->lineEditGEOexclusion3->text() == "" ) {
                        *errorString += "MODEL: GEO exclusion in [SBAS Options] cannot be empty.\n";
                    } else if ( ui->lineEditGEOexclusion1->text().toInt() < 120 || ui->lineEditGEOexclusion2->text().toInt() < 120 || ui->lineEditGEOexclusion3->text().toInt() < 120 ) {
                        *errorString += "MODEL: GEO exclusion in [SBAS Options] must be between 120 and 210.\n";
                    } else {
                        *saveString += "-pre:geoexclude " + ui->lineEditGEOexclusion1->text() + "," + ui->lineEditGEOexclusion2->text() + "," + ui->lineEditGEOexclusion3->text() + "\n";
                        *runString << "-pre:geoexclude" << ui->lineEditGEOexclusion1->text() + "," + ui->lineEditGEOexclusion2->text() + "," + ui->lineEditGEOexclusion3->text();
                    }
                    if(ui->comboBoxGEOselection->currentIndex()==3) {
                        //Check that GEO unselected is not the GEO selected
                        if ( (ui->lineEditGEOselection->text()==ui->lineEditGEOexclusion1->text()) || (ui->lineEditGEOselection->text()==ui->lineEditGEOexclusion2->text()) || (ui->lineEditGEOselection->text()==ui->lineEditGEOexclusion3->text())) {
                            *errorString += "MODEL: GEO " + ui->lineEditGEOselection->text() + " selected for processing cannot be excluded\n";
                        }
                    }
                    break;
                }
            }

        }
        // Smoothing
        if ( ui->radioButtonSmoothing->isChecked() == true ) {
            if ( ui->lineEditSmoothMinSbas->text() == "" ) {
                *errorString += "FILTER: Continuous code smoothing before steady-state operation cannot be empty.\n";
            } else {
                if ( ui->lineEditSmoothMinSbas->text().toInt() != 360 || WriteAllParameters==1 ) {
                    *saveString += "-pre:smoothmin " + ui->lineEditSmoothMinSbas->text() + "\n";
                    *runString << "-pre:smoothmin" << ui->lineEditSmoothMinSbas->text();
                }
            }
        } else {
            //Smoothing is enabled by default in SBAS
            *saveString += "-pre:smooth 0 -pre:smoothmin 0\n";
            *runString << "-pre:smooth" << "0" << "-pre:smoothmin" << "0";
        }
    }
    // DGNSS Options (within filter tab)
    if ( ui->labelCurrentTemplate->text() == "DGNSS" || ui->groupBoxReferenceStation->isChecked()==true ) {
        if ( ui->checkBoxExcludeDuringSmoothingConvergenceUser->isChecked() == true ) {
            *saveString += "-pre:dgnss:excludeSmoothingConvergenceUser\n";
            *runString << "-pre:dgnss:excludeSmoothingConvergenceUser";
        } else if ( ui->checkBoxExcludeDuringSmoothingConvergenceUser->isChecked() == false ) {
            if (WriteAllParameters==1 ) {
                *saveString += "--pre:dgnss:excludeSmoothingConvergenceUser\n";
                *runString << "--pre:dgnss:excludeSmoothingConvergenceUser";
            }
        }
        if ( ui->checkBoxExcludeDuringSmoothingConvergenceRef->isChecked() == true) {
            if (WriteAllParameters==1 ) {
                *saveString += "-pre:dgnss:excludeSmoothingConvergenceRef\n";
                *runString << "-pre:dgnss:excludeSmoothingConvergenceRef";
            }
        } else if ( ui->checkBoxExcludeDuringSmoothingConvergenceRef->isChecked() == false ) {
            *saveString += "--pre:dgnss:excludeSmoothingConvergenceRef\n";
            *runString << "--pre:dgnss:excludeSmoothingConvergenceRef";
        }
        if ( ui->radioButtonSmoothing->isChecked() == true ) {
            if (ui->checkBoxExcludeDuringSmoothingConvergenceUser->isChecked() == true ) {
                if ( ui->lineEditSmoothMinDgnss->text() == "" ) {
                    *errorString += "FILTER: Continuous code smoothing before steady-state operation cannot be empty.\n";
                }
                *saveString += "-pre:smoothmin " + ui->lineEditSmoothMinDgnss->text() + "\n";
                *runString << "-pre:smoothmin" << ui->lineEditSmoothMinDgnss->text();
            } else if (WriteAllParameters==1) {
                *saveString += "-pre:smoothmin 0\n";
                *runString << "-pre:smoothmin" << "0";
            }
            if (ui->checkBoxExcludeDuringSmoothingConvergenceRef->isChecked() == true) {
                if ( ui->lineEditSmoothMinDgnss->text() == "" ) {
                    *errorString += "FILTER: Continuous code smoothing before steady-state operation cannot be empty.\n";
                }
                if ( ui->lineEditSmoothMinDgnss->text().toInt() != 360 || WriteAllParameters==1 ) {
                    *saveString += "-pre:dgnss:smoothmin " + ui->lineEditSmoothMinDgnss->text() + "\n";
                    *runString << "-pre:dgnss:smoothmin" << ui->lineEditSmoothMinDgnss->text();
                }
            }
        } else {
            //No smoothmin
            *saveString += "-pre:smooth 0 -pre:dgnss:smoothmin 0\n";
            *runString << "-pre:smooth" << "0" << "-pre:dgnss:smoothmin" << "0";
        }
    }
}
