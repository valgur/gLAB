/****************************************************************************
   Copyright & License:
   ====================
   
   Copyright 2009 - 2020 gAGE/UPC & ESA
   
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
   
   http://www.apache.org/licenses/LICENSE-2.0
   
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 ***************************************************************************/

/****************************************************************************
 * Copyright: gAGE/UPC & ESA
 * Project: EDUNAV GNSS Lab Tool 
 * Supervisor: Jaume Sanz Subirana (group of Astronomy and GEomatics - gAGE/UPC)
 * Author: Pere Ramos-Bosch (group of Astronomy and GEomatics - gAGE/UPC)
 * Curator: Adria Rovira-Garcia ( gAGE/UPC )
 * Developers: Deimos Ibanez Segura ( gAGE/UPC )
 *             Jesus Romero Sanchez ( gAGE/UPC )
 *          glab.gage @ upc.edu
 * File: input.h
 * Code Management Tool File Version: 5.5  Revision: 1
 * Date: 2020/12/11
 ***************************************************************************/

/****************************************************************************
 * MODULE DESCRIPTION
 *
 * Name: input
 * Language: C
 *
 * Purpose:
 *  The purpose of this module is to serve as "driver" from the different ways
 *  that the data can be stored in the form of files and the rest of the program
 *
 * Function:
 *  This class is in charge of reading the different data formats in which the 
 *  data can be stored, and save it to the internal data structures.
 *
 * Dependencies:
 *  dataHandling
 *
 * Files modified:
 *  None
 *
 * Files read:
 *  Depending on function
 *
 * Resources usage:
 *  See Design Document
 ****************************************************************************/

/****************************
 *       RELEASE_HISTORY
 * -------------
 *          gLAB v1.3.1
 * Release: 2010/01/22
 * Change Log: First public version.
 * -------------
 *          gLAB v1.3.2
 * Release: 2010/02/23
 * Change Log: Included input files: SINEX, DCB and GPS_Receiver_Type.
 *             Forward/Backward processing included.
 * -------------
 *          gLAB v1.4.0
 * Release: 2010/06/21
 * Change Log: No changes in this file.
 * -------------
 *          gLAB v1.4.1
 * Release: 2010/07/09
 * Change Log: No changes in this file.
 * -------------
 *          gLAB v1.4.2
 * Release: 2010/07/31
 * Change Log: No changes in this file.
 * -------------
 *          gLAB v1.4.3
 * Release: 2010/08/31
 * Change Log: No changes in this file.
 * -------------
 *          gLAB v1.4.4
 * Release: 2010/09/22
 * Change Log: No changes in this file.
 * -------------
 *          gLAB v1.4.5
 * Release: 2010/10/31
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.0.0
 * Release: 2012/12/31
 * Change Log: gLAB version released together with the Educational Book:
 *             "GNSS Data Processing" (Vol. 1 and Vol. 2). ESA TM-23.
 *             Authors: J. Sanz Subirana, J.M. Juan Zornoza and M. Hernandez-Pajares
 *             ISBN: 978-92-9221-885-0 (two volumes)
 *             ISSN: 1013-7076
 *             December 2012.
 * -----------
 *          gLAB v2.2.0
 * Release: 2014/09/22
 * Change Log: Added function for reading Fast-PPP columnar files.
 *             Added function for reading files for Galileo tropospheric model.
 * -----------
 *          gLAB v2.2.1
 * Release: 2014/12/23
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.2.2
 * Release: 2015/03/02
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.2.3
 * Release: 2015/05/28
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.2.4
 * Release: 2015/07/01
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.2.5
 * Release: 2015/10/20
 * Change Log: No changes in this file
 * -----------
 *          gLAB v2.2.6
 * Release: 2015/11/25
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.2.7
 * Release: 2016/03/01
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.2.8
 * Release: 2016/04/12
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v3.0.0
 * Release: 2016/09/05 
 * Change Log: Added SBAS processing.
 *             Added addUserError function for reading user-defined error from text file.
 *             Deleted function beforeReadEpochUpdate.
 *             Deleted function afterReadEpochUpdate.
 *             Added function dictionaryUpdate.
 * -----------
 *          gLAB v3.1.0
 * Release: 2016/09/26
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v3.1.1
 * Release: 2016/10/21
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v4.0.0
 * Release: 2017/03/03
 * Change Log: Added functions to decode RTCM binary files.
 * -----------
 *          gLAB v4.1.0
 * Release: 2017/04/07
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v4.2.0
 * Release: 2017/05/22
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.0.0
 * Release: 2017/06/30
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.1.0
 * Release: 2017/11/24
 * Change Log:   Added functions 'readReferenceFile' and 'readPosFile' for reading a reference 
 *                 position file.
 * -----------
 *          gLAB v5.1.1
 * Release: 2017/12/22
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.1.2
 * Release: 2018/01/12
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.1.3
 * Release: 2018/01/19
 * Change Log:   Removed 'readIONEXFile' function because it is no longer used.
 *               Removed 'readRinexNavFile' function because it is no longer used.
 * -----------
 *          gLAB v5.2.0
 * Release: 2018/03/09
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.3.0
 * Release: 2018/06/08
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.4.0
 * Release: 2018/11/16
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.4.1
 * Release: 2019/02/15
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.4.2
 * Release: 2019/03/08
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.4.3
 * Release: 2019/03/20
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.4.4
 * Release: 2019/05/10
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.5.0
 * Release: 2020/11/13
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.5.1
 * Release: 2020/12/11
 * Change Log: No changes in this file.
 * -----------
 *       END_RELEASE_HISTORY
 *****************************/

#ifndef INPUT_H_
#define INPUT_H_

/* System modules */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <errno.h>

/* External classes */
#include "dataHandling.h"
#include "output.h"

// Input functions
int getL (char *lineptr, int *n, FILE *stream);
int getLNoComments (char *lineptr, int *n, FILE *stream);
int getLback (char *lineptr, int *n, FILE *stream);

// File management
enum fileType whatFileTypeIs (char *filename);

// RINEX Observation
int readRinexObsHeader (FILE *fd, FILE *fdout, TEpoch *epoch, TOptions *options);
int readRinexObsEpoch (FILE *fd, TEpoch *epoch, TConstellation *constellation, enum ProcessingDirection direction, char *Epochstr, TOptions *options);
int rewindEpochRinexObs (FILE *fd, enum Source src);
int getEpochFromObsFile (FILE *fd, enum Source src, TTime *t);

// RINEX Navigation message
int readRinexNav (FILE *fd, TGNSSproducts *products, double *rinexNavVersion);
int readRinexNavLastEpoch (FILE *fd, TTime *lastEpoch);

// SP3 files
int readSP3 (FILE *fd, TGNSSproducts *products, int readOrbits, int readClocks, int readingRefFile, TOptions *options);
int readSP3LastEpoch (FILE *fd, TTime *lastEpoch);

// RINEX Clocks
int readRinexClocks (FILE *fd, TGNSSproducts *products);
int readRinexClocksFile (char *filename, TGNSSproducts *products);

// Troposphere
int readGalileoTroposphericData (TTROPOGal *TropoGal, char *filename, TOptions *options);

// IONEX
int readIONEX (FILE *fd, TIONEX *IONEX, double *ionexVersion);
int readIONEXFile (char *filename, TIONEX *IONEX, double *ionexVersion);
int readFPPP (FILE *fd, TFPPPIONEX *FPPP, double *FPPPVersion);
int readFPPPFile (char *filename, TFPPPIONEX *FPPP, double *FPPPVersion);

// Satellite constellation
int readConstellation (FILE *fd, TConstellation *constellation);
int readConstellationFile (char *filename, TConstellation *constellation);

// ANTEX
int readAntex (FILE *fd, TConstellation *constellation, TAntennaList *antennaList);
int readAntexFile (char *filename, TConstellation *constellation, TAntennaList *antennaList);

// DCB
int readDCB (FILE *fd, TDCBdata *DCB);
int readDCBFile (char *filename, TDCBdata *DCB);

// GPS Receiver types
int readRecType (FILE *fd, TReceiverList *recList);
int readRecTypeFile (char *filename, TReceiverList *recList);

// SINEX
int readSINEX (FILE *fd, TStationList *stationList);
int readSINEXFile (char *filename, TStationList *stationList);

// SBAS
int readSBASFile (char *filename, TSBASdatabox *SBASdatabox, double *rinexVersion, TTime *currentepoch, TOptions  *options);
int readRINEXB (FILE *fd, FILE **fdlist, char **filelist, TSBASdatabox *SBASdatabox, double *rinexVersion, int *prevday, TTime *currentepoch, TOptions  *options);
int readEMS (FILE *fd, FILE **fdlist, char **filelist, TSBASdatabox *SBASdatabox, int *prevday, TTime *currentepoch, TOptions  *options);
int readSBASmessage (char *binarystring, int messagetype, int *decodedmessagetype, TSBASblock *sbasblock, int *messageslost, TOptions  *options);
void updateSBASdata (TSBASdata  *SBASdata, TSBASblock  *sbasblock, TTime currentepoch, int messagesmissing, TOptions  *options);
int readsigmamultipathFile (char *filename,  TSBASdata  *SBASdata, TOptions  *options);
int readsigmamultipath (FILE *fd, char  *filename, TSBASdata  *SBASdata, TOptions *options);

// DGNSS RTCM v2.x
TdataRead *readFile (FILE *fp, TdataRead *data, int *checkControl);
char decodeWords (char *out_arr, char *in_arr, int n);
char *parityCheck (char *msg, char *cw, int *last2bits);
int *getLast2bits (char *msg, int *last2bits);
TRTCM2header *decodeHeader (TRTCM2header *head, char *header_str);
TMSG1 *readMSG1 (TMSG1 *sc, int ns, char *body_str);
TMSG2 *readMSG2 (TMSG2 *sc, int ns, char *body_str);
TMSG3 *readMSG3 (TMSG3 *sc, char *body_str);
TMSG24 *readMSG24 (TMSG24 *sc, char *body_str);
int converterRTCM2 (FILE *fd, TRTCM2 *rtcm2, char *fileASCIIcorrections, char *fileASCIIantenna, TEpoch *epoch, TEpoch *epochDGNSS, TOptions *options);

// DGNSS RTCM v3.x
int bitInt (char bt, int bp);
char bitChar (char bt, int bp);
char *getBitStr (char *out_str,unsigned char *in_arr, int n);
long long int twoComplement (unsigned long long int orig, int n);
int crc24q (unsigned char *frame, int len);
int getMSGtype (unsigned char *msg);
TRTCM3header *getRTCMheader (TRTCM3header *head, unsigned char *msg);
TlockTime *getLockT (TlockTime *lt, int indicator);
TMSG1004 *readMSG1004 (TMSG1004 *sc, int ns, char *body_str);
TMSG1006 *readMSG1005 (TMSG1006 *sc, unsigned char *msg);
TMSG1006 *readMSG1006 (TMSG1006 *sc, unsigned char *msg);
TMSG1008 *readMSG1008 (TMSG1008 *sc, unsigned char *msg);
void readRTCM3header (TEpoch *epoch, TEpoch *epochDGNSS, TRTCM3 *rtcm3, TOptions *options);
int readRTCM3obs (TEpoch *epochDGNSS, TRTCM3 *rtcm3, TOptions *options);
int converterRTCM3 (FILE *fd, TRTCM3 *rtcm3, char *fileRINEXpointer, TEpoch *epoch, TEpoch *epochDGNSS, TOptions *options);

//	User defined error
void addUserError (FILE *fd, char *filename, TEpoch *epoch, TUserError *UserError, TOptions *options);

// Reference position file
int readReferenceFile (char  *filename, TGNSSproducts *RefPosition, TOptions  *options);
void readPosFile (FILE  *fd, char  *filename, TGNSSproducts *RefPosition, TOptions  *options);

#endif /*INPUT_H_*/
