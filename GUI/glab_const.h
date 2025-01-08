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
#ifndef GLAB_CONST_H
#define GLAB_CONST_H

#include <QString>
#include <QStringList>
#include <QRadioButton>

#define MIN_EARTH_RADIUS            6356752.
#define MAX_INPUT_PATH              7
#define MAX_GNSS                    7
#define MAX_SATELLITES_PER_GNSS     70
#define MAX_SAT_GPS                 32
#define MAX_SAT_GAL                 36
#define MAX_SAT_GLO                 32
#define MAX_SAT_GEO                 39
#define MAX_SAT_BDS                 63
#define MAX_SAT_QZS                 10
#define MAX_SAT_IRN                 14
#define MAX_GNSS_FREQ               6
#define MAX_GNSS_FREQ_SLOTS         10  //GNSS Freq number are from 1 to 9, so we need 10 slots to access up to position 9
#define MAX_GNSS_DUALFREQ           15
#define MAX_GNSS_CODE               16
#define KMLOPTIONSREDUCETHRESHOLD   1094
#define MAXNAVIGATIONMODES          5 //SPP, PPP, SBAS 1F, SBAS DFMC, DGNSS
#define SPPNAVMODE                  0
#define PPPNAVMODE                  1
#define SBAS1FNAVMODE               2
#define SBASDFMCNAVMODE             3
#define DGNSSNAVMODE                4

#define DIFFEQTHRESHOLD             1E-4 //When comparing two floating points, if difference is below this threshold, values will be considered equal

//measurement mode
#define MEAS_MODE_SINGLE            0x01
#define MEAS_MODE_DUAL              0x02
#define MEAS_MODE_CODE              0x01
#define MEAS_MODE_SMOOTH            0x02
#define MEAS_MODE_CODEPHASE         0x04
#define GEOMINPRN                   20  //Minimum GEO PRN is 120
#define GEOMINPRNOFFSET             19  //Minimum GEO PRN is 120, so the offset from 1 to 20 is 19

#define FIRSTMEASARRAYPOS           0
#define SECONDMEASARRAYPOS          1
#define THIRDMEASARRAYPOS           2
#define COMBMEAS1ARRAYPOS           0
#define COMBMEAS2ARRAYPOS           1
#define CODEARRAYPOS                0
#define PHASEARRAYPOS               1
#define GCARRAYPOS                  2
#define MAXMEASTOFILTER             3
#define MAXMEASTYPE                 3
#define MEASANDPHASENUMSLOTS        2
#define CONSTWEIGHTARRAYPOS         0
#define MAXWEIGHTTYPES              5

#define MINSNRTYPE                  0
#define MAXSNRTYPE                  1

#define NUMGPSVSNAVTYPES            2
#define NUMGALVSNAVTYPES            2


#define DEFAULT_PREFERRED_NAV_TIME  "3600"    //Preferred time frame for navigation message (seconds)

//Enumerator for different GNSS systems
enum GNSSystem {
    GNSSSystemUnknown = -1,
    GPS = 0,
    Galileo = 1,
    GLONASS = 2,
    GEO = 3,
    BDS = 4,
    QZSS = 5,
    IRNSS = 6,
};

//Enumerator for cycle-slip type
enum CycleSlipType {
    CStypeUnknown = -1,
    CStypeSF = 0,
    CStypeMW = 1,
    CStypeLI = 2,
    CStypeIGF = 3
};

//Enumerator for cycle-slip parameter type
enum CycleSlipParamType {
    CStypeParamUnknown = -1,
    CStypeParamFreq = 0,
    CStypeParamMeas= 1
};

//Enumerator for measurement target usage
enum MeasTargetUsage {
    MeasTargetUnkown = -1,
    MeasTargetFilter = 0,
    MeasTargetSmooth = 1
};

//GNSS measurement selection types
const QString MeasSelectTypeGNSS[2]={"Code-","Phase-"};
//Satellite System indentifier for different GNSS systems
const QString indentifierGNSS[MAX_GNSS]={"G","E","R","S","C","J","I"};
//GNSS System name
const QString GNSSName[MAX_GNSS]={"GPS","Galileo","GLONASS","GEO","BDS","QZSS","IRNSS"};
//GNSS enum list
const enum GNSSystem GNSSenums[MAX_GNSS]={GPS,Galileo,GLONASS,GEO,BDS,QZSS,IRNSS};
//Default Reference constellation clock priority
const QString RefGNSSClockPriority[MAX_GNSS]={"GPS","Galileo","GLONASS","BDS","QZSS","IRNSS","GEO"};
//Default Reference constellation clock priority
const QString ISCBGNSSOrder[MAX_GNSS]={"G","E","R","C","J","I","S"};
//Maximum PRN number of each constellations
const int listMaxSatGNSS[MAX_GNSS]={MAX_SAT_GPS,MAX_SAT_GAL,MAX_SAT_GLO,MAX_SAT_GEO,MAX_SAT_BDS,MAX_SAT_QZS,MAX_SAT_IRN};
//Frequency number for different GNSS systems
const int nFreqGNSS[MAX_GNSS]={3,5,5,2,6,4,2};
//Dual Frequency number for different GNSS systems
const int nDualFreqGNSS[MAX_GNSS]={3,10,10,1,15,6,1};
//Frequency list for different GNSS systems
const QStringList FreqBandGNSSList[MAX_GNSS]={ {"L1","L2","L5"},
                                               {"E1","E5a","E6","E5b","E5"},
                                               {"G1","G2","G3","G1a","G2a"},
                                               {"L1","L5"},
                                               {"B1","B1CA","B2a","B3","B2b","B2"},
                                               {"L1","L2","L5","L6"},
                                               {"L5","S"} };
const QStringList FreqNameGNSSList[MAX_GNSS]={ {"F1 (L1)","F2 (L2)","F5 (L5)"},
                                               {"F1 (E1)","F5 (E5a)","F6 (E6)","F7 (E5b)","F8 (E5)"},
                                               {"F1 (G1)","F2 (G2)","F3 (G3)","F4 (G1a)","F6 (G2a)"},
                                               {"F1 (L1)","F5 (L5)"},
                                               {"F1 (B1)","F2 (B1CA)","F5 (B2a)","F6 (B3)","F7 (B2b)","F8 (B2)"},
                                               {"F1 (L1)","F2 (L2)","F5 (L5)","F6 (L6)"},
                                               {"F5 (L5)","F9 (S)"} };
const QString FreqGNSSList[MAX_GNSS][MAX_GNSS_FREQ]={ {"1","2","5"},
                                                      {"1","5","6","7","8"},
                                                      {"1","2","3","4","6"},
                                                      {"1","5"},
                                                      {"1","2","5","6","7","8"},
                                                      {"1","2","5","6"},
                                                      {"5","9"} };
const QStringList FreqDualGNSSList[MAX_GNSS]={ {"12","15","25"},
                                               {"15","16","17","18","56","57","58","67","68","78"},
                                               {"12","13","14","16","23","24","26","34","36","46"},
                                               {"15"},
                                               {"12","15","16","17","18","25","26","27","28","56","57","58","67","68","78"},
                                               {"12","15","16","25","26","56"},
                                               {"59"} };
const QStringList FreqCodeDualGNSSList[MAX_GNSS]={ {"PC12","PC15","PC25"},
                                                   {"PC15","PC16","PC17","PC18","PC56","PC57","PC58","PC67","PC68","PC78"},
                                                   {"PC12","PC13","PC14","PC16","PC23","PC24","PC26","PC34","PC36","PC46"},
                                                   {"PC15"},
                                                   {"PC12","PC15","PC16","PC17","PC18","PC25","PC26","PC27","PC28","PC56","PC57","PC58","PC67","PC68","PC78"},
                                                   {"PC12","PC15","PC16","PC25","PC26","PC56"},
                                                   {"PC59"} };
const QStringList FreqPhaseDualGNSSList[MAX_GNSS]={ {"LC12","LC15","LC25"},
                                                    {"LC15","LC16","LC17","LC18","LC56","LC57","LC58","LC67","LC68","LC78"},
                                                    {"LC12","LC13","LC14","LC16","LC23","LC24","LC26","LC34","LC36","LC46"},
                                                    {"LC15"},
                                                    {"LC12","LC15","LC16","LC17","LC18","LC25","LC26","LC27","LC28","LC56","LC57","LC58","LC67","LC68","LC78"},
                                                    {"LC12","LC15","LC16","LC25","LC26","LC56"},
                                                    {"LC59"} };
const QStringList FreqIFDualGNSSList[MAX_GNSS]={ {"IF12","IF15","IF25"},
                                                    {"IF15","IF16","IF17","IF18","IF56","IF57","IF58","IF67","IF68","IF78"},
                                                    {"IF12","IF13","IF14","IF16","IF23","IF24","IF26","IF34","IF36","IF46"},
                                                    {"IF15"},
                                                    {"IF12","IF15","IF16","IF17","IF18","IF25","IF26","IF27","IF28","IF56","IF57","IF58","IF67","IF68","IF78"},
                                                    {"IF12","IF15","IF16","IF25","IF26","IF56"},
                                                    {"IF59"} };

const int iFreqDualGNSS[MAX_GNSS][MAX_GNSS_DUALFREQ][2]={ { {0,1},{0,2},{1,2} },
                                                          { {0,1},{0,2},{0,3},{0,4},{1,2},{1,3},{1,4},{2,3},{2,4},{3,4} },
                                                          { {0,1},{0,2},{0,3},{0,4},{1,2},{1,3},{1,4},{2,3},{2,4},{3,4} },
                                                          { {0,1} },
                                                          { {0,1},{0,2},{0,3},{0,4},{0,5},{1,2},{1,3},{1,4},{1,5},{2,3},{2,4},{2,5},{3,4},{3,5},{4,5} },
                                                          { {0,1},{0,2},{0,3},{1,2},{1,3},{2,3} },
                                                          { {0,1} } };
//Frequency & Measurement order list for different GNSS systems
const QString FreqGNSSOrder[MAX_GNSS]={"125","15678","12346","15","152768","1256","59"};
const QString MeasGNSSOrder[MAX_GNSS][MAX_GNSS_FREQ]={ {"PWCYLSXMN","PWCYLSXDMN","QIX"},
                                                       {"CXZBA","QIX","CXZBA","QIX","QIX"},
                                                       {"PC","PC","QIX","ABX","ABX"},
                                                       {"C","QIX"},
                                                       {"PDLSXZ","QIX","PDX","QIPDXZ","QIPDXZ","PDX"},
                                                       {"CLSEXZB","LSX","QIPDXZ","LSXEZ"},
                                                       {"ACBX","ACBX"} };
const QString MeasCodeGNSSOrder[MAX_GNSS][MAX_GNSS_FREQ]={ {"PWCYLSXM","PWCYLSXDM","QIX"},
                                                           {"CXZBA","QIX","CXZBA","QIX","QIX"},
                                                           {"PC","PC","QIX","ABX","ABX"},
                                                           {"C","QIX"},
                                                           {"PDLSXZ","QIX","PDX","QIPDXZ","QIPDXZ","PDX"},
                                                           {"CLSEXZB","LSX","QIPDXZ","LSXEZ"},
                                                           {"ACBX","ACBX"} };

//SNR default value
const int nSNRDef=9;
const QString SNRDefValue[9]={"12","18","24","30","33","36","42","48","54"};
//GNSS measurement noise mode
const QString GNSSNoiseMode[5] = { "-filter:fixedweight", "-filter:elevweight", "-filter:sinelevweight", "-filter:snrweight", "-filter:snrelevweight" };
//Navigation Messages Types
const QStringList NavMessageTypes[MAX_GNSS][2]={ { {"LNAV", "CNAV"}, {"LNAV", "CNAV", "LNAVvsCNAV", "CNAVvsLNAV"} }, //GPS
                                               { {"INAVE1E5b", "INAVE1", "INAVE5b", "FNAV"}, {"INAVE1E5b", "INAVE1", "INAVE5b", "FNAV", "INAVvsFNAV", "FNAVvsINAV"} }, //Galileo
                                               { {"FDMA"}, {"FDMA"} }, //GLONASS
                                               { {"CNAV"}, {"CNAV"} }, //GEO
                                               { {"D1"}, {"D1"} }, //BDS
                                               { {"LNAV"}, {"LNAV"} }, //QZSS
                                               { {"CNAV"}, {"CNAV"} } //IRNSS
                                             };
//Navigation Messages Types comparison (same as NavMessageTypes but with spaces to allow line breaking)
const QStringList CompareNavMT[MAX_GNSS][2]={  { {"LNAV", "CNAV"}, {"LNAV", "CNAV", "LNAV vsCNAV", "CNAV vsLNAV"} }, //GPS
                                               { {"INAVE1E5b", "INAVE1", "INAVE5b", "FNAV"}, {"INAV E1E5b", "INAVE1", "INAVE5b", "FNAV", "INAV vsFNAV", "FNAV vsINAV"} }, //Galileo
                                               { {"FDMA"}, {"FDMA"} }, //GLONASS
                                               { {"CNAV"}, {"CNAV"} }, //GEO
                                               { {"D1"}, {"D1"} }, //BDS
                                               { {"LNAV"}, {"LNAV"} }, //QZSS
                                               { {"CNAV"}, {"CNAV"} } //IRNSS
                                             };
//INAV default order
const QString GPSNAVDefaultOrder=NavMessageTypes[GPS][0][0]+","+NavMessageTypes[GPS][0][1];
const QString GalINAVDefaultOrder=NavMessageTypes[Galileo][0][0]+","+NavMessageTypes[Galileo][0][1]+","+NavMessageTypes[Galileo][0][2];

//Default weights
const QString SingleFreqDefaultFixedWeight[MAXMEASTYPE]={"1","0.01","0.5"};         //Code, phase and Graphic combination (in metres)
const QString SingleFreqDefaultFixedWeightSquared[MAXMEASTYPE]={"1","1E-4","0.25"}; //Code, phase and Graphic combination (in metres^2)
const QString DualFreqDefaultFixedWeight[MAXMEASTYPE]  ={"3","0.03",""};            //Code and phase                      (in metres)
const QString DualFreqDefaultFixedWeightSquared[MAXMEASTYPE]  ={"9","9E-4",""};     //Code and phase                      (in metres^2)
const QString WeightTypeDefaultBandCValues[MAXWEIGHTTYPES][2]={ {"",""},            //Fixed weight                        (B and c slots not used)
                                                                {"0.53","10"},      //Elevation Weight                    (m, degrees)
                                                                {"2.5E-3",""},      //sin(elevation)                      (m^2, C slot not used)
                                                                {"4",""},           //SNR                                 (m^2·Hz, C slot not used)
                                                                {"4",""}            //SNR+sin(elevation)                  (m^2·Hz, C slot not used)
                                                              };
//QT GUI default value
const QString ButtonEnabledStyle="background-color:236,236,236; color:black;";
const QString ButtonDisabledStyle="background-color:200,200,200; color:216,216,216;";

const QString GreenColor = "#00ff00";
const QString RedColor = "#ff0000";
const QString pushColor = "#ebebf5"; //same as pushButton background-color "rgb(235,235,245)" defined in ***Style.qss file
const QString pushClickedColor = "#ebf9eb";

//Default constellations enabled or disabled in each navigation mode
const int   defaultConstEnabled[MAXNAVIGATIONMODES][MAX_GNSS]= {
    //SPP
    {1,1,1,0,1,1,1},
    //PPP
    {1,1,1,0,1,1,1},
    //SBAS 1F
    {1,0,0,0,0,0,0},
    //SBAS DFMC
    {1,1,0,0,0,0,0},
    //DGNSS
    {1,0,0,0,0,0,0}
};

//Frequencies available per constellation
const int   availGNSSFreq[MAX_GNSS][MAX_GNSS_FREQ_SLOTS]={ //List of available frequencies in each constellation
                               //0,1,2,3,4,5,6,7,8,9
                        /*GPS*/ {0,1,1,0,0,1,0,0,0,0},
                        /*GAL*/ {0,1,0,0,0,1,1,1,1,0},
                        /*GLO*/ {0,1,1,1,1,0,1,0,0,0},
                        /*GEO*/ {0,1,0,0,0,1,0,0,0,0},
                        /*BDS*/ {0,1,1,0,0,1,1,1,1,0},
                        /*QZS*/ {0,1,1,0,0,1,1,0,0,0},
                        /*IRN*/ {0,0,0,0,0,1,0,0,0,1}};


//Regular expressions for satellite ranges check. Set here so if more constellations are added, they only have to be changed once
const QString regExpConstOnly="[GERSCJIgerscji]";
const QString regExpSatWithRanges="^[+-]{0,1}"+ regExpConstOnly + "{1,7}([1-6]{0,1}[0-9]-[1-6]{0,1}[0-9]|[0-9][0-9]|[1-9])(\\.([1-6]{0,1}[0-9]-[1-6]{0,1}[0-9]|[1-6]{0,1}[0-9])){0,}-";
const QString regExpSatNoRanges="(^[+-]{0,1}0$|^[+-]{0,1}" + regExpConstOnly + "{1,7}0)$";
const QString regExpStartWithConst="(^[+-]{0,1}0|^[+-]{0,1}" + regExpConstOnly + "{1,7}0)"; //Same as regExpSatNoRanges but without "$" at the end
const QString attributes="ABCDESLIQXPWYZMN";
const QString regExpValidAttributes="[" + attributes + "]";

//Declaration of free functions (functions which does not belong to a class and can be called by any class)
//This functions will be defined in glab_gui.cpp
int checkConstellationQChar(QChar charac);
enum GNSSystem gnssQchar2gnsstype(QChar GNSS);

//This function is not assigned to any class so it can be called by any of the cycle-slip functions. It is defined in preprocessing.c
int checkUserInputCycleSlipMeasurement (QString *warningString, QString param, const enum CycleSlipType CStype, const enum CycleSlipParamType paramType, const QRadioButton *MinNoiseButton);

#endif // GLAB_CONST_H
