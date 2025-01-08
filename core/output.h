/****************************************************************************
   Copyright & License:
   ====================
   
   Copyright 2009 - 2024 gAGE/UPC & ESA
   
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
 * Developers: Deimos Ibáñez Segura ( gAGE/UPC )
 *             Jesus Romero Sanchez ( gAGE/UPC )
 *          glab.gage @ upc.edu
 * File: output.h
 * Code Management Tool File Version: 6.0  Revision: 0
 * Date: 2024/11/22
 ***************************************************************************/

/****************************************************************************
 * MODULE DESCRIPTION
 *
 * Name: output
 * Language: C
 *
 * Purpose:
 *  The purpose of this module is to act as output for the solution of the filter
 *
 * Function:
 *  This class is in charge of outputting the results of the Kalman filter done 
 *  by the filter module
 *
 * Dependencies:
 *  dataHandling, filter, model
 *
 * Files modified:
 *  None
 *
 * Files read:
 *  None
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
 * Change Log: Imported SATDIFF, SATSTAT and SATSTATTOT printing from gLAB.c
 *             Added satellite SATPVT message.
 *             Change in SATDIFF to show the GNSS system that the satellite belongs to.
 *             PREFIT message now includes the weight that will be applied to the filter.
 *             ZTD and estimated residual tropospheric delay is now printed in the FILTER message .
 *             SATSTAT message will now provide the GNSS system it refers to.
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
 * Change Log: Satellite elevation and azimuth addition in the print MODEL message.
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
 * Change Log: No changes in this file.
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
 * Change Log: No changes in this file.
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
 *             Added printUserError function for printing user-defined error
 *             Modified printSatSel function (now prints epoch and constellation)
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
 * Change Log: Added functions to convert RTCM binary files.
 *             Added printDGNSS message.
 *             Added functions for SBAS plots mode.
 *             Added function to print KML file.
 *             Added function to print SP3 file.
 *             Added function to print SBAS summary.
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
 * Change Log:   Added 'printDates' and 'printCoordinates' functions for printing the results
 *                 of date or coordinates conversion (for conversion mode only).
 *               Added 'writeReffile' function for writing a reference position file.
 * -----------
 *          gLAB v5.1.1
 * Release: 2017/12/22
 * Change Log:   Added function 'writeObsRinexEpochUserAddedError' for writing RINEX observation file
 *                 with user added error.
 * -----------
 *          gLAB v5.1.2
 * Release: 2018/01/12
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.1.3
 * Release: 2018/01/19
 * Change Log: No changes in this file.
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
 *          gLAB v6.0.0
 * Release: 2024/11/22
 * Change Log:   Added multi-constellation support (Galileo, GLONASS, GEO, BDS, QZSS and IRNSS).
 *               Added multi-frequency support (all RINEX frequencies).
 *               Added SBAS DFMC processing.
 * -----------
 *       END_RELEASE_HISTORY
 *****************************/

#ifndef OUTPUT_H_
#define OUTPUT_H_

#if defined __WIN32__
 	//This is to allow %lld, %llu and %n format specifiers in printf with MinGW
	#define __USE_MINGW_ANSI_STDIO  1
#endif

/* System modules */
#include <stdio.h>
#if defined _MSC_VER
	#include <io.h>
#else
	#include <unistd.h>
#endif

/* External classes */
#include "dataHandling.h"
#include "filter.h"
#include "model.h"

/* Internal types, constants and data */
void printDisabledGLONASS(TOptions *options);
void printConstFreqDisabled(TOptions *options);
void printFilterMeas(TOptions *options, int NavMode);
void printParameters (TOptions *options, TEpoch *epoch, TGNSSproducts *products, TTGDdata *tgdData, int NavMode, char *stdesaFile, char *stdesaFileLOI, char *kmlFile, char *kml0File, char *sp3File, char *RefFile, int navFilesVersion[MAXNAVSOURCESWITHIONO][MAX_GNSS], int numNavFilesVersion[MAXNAVSOURCESWITHIONO]);
void printError (char *message, TOptions *options);
void printInfo (char *message, TOptions *options);
void printInput (TEpoch *epoch, TTGDdata *tgdData, TOptions *options);
void printMeas (TEpoch *epoch, TTGDdata *tgdData, TConstellation *constellation, TOptions *options);
void printCS (TEpoch *epoch, enum GNSSystem GNSS, int PRN, int satIndex, enum CSType csType, int mode, char *measStr, double maxDataGap, double timeDiff, char *LLImeasText, double LIestDiff, double LIThreshold, double nMWdiff, double nMWdiffThreshold, double SFdiff, double SFThreshold, double IGFestDiff, double IGFThreshold, TOptions *options);
void printSFCSdata (TEpoch *epoch, enum GNSSystem GNSS, int PRN, int satIndex, int satCSIndex, int mode, char *measStr, double CodeValue, double PhaseValue, double SFMean, double SFsigma, double deltaSFCode, double deltaSFPhase, double deltaSF, double SFdiff, double SFThreshold, int Unconsistency, int Cycleslip, TOptions *options);
void printMWCSdata (TEpoch *epoch, enum GNSSystem GNSS, int PRN, int satIndex, int satCSIndex, int mode, char *measStr, enum MeasurementType *measList, int *freqList, double MWMean, double MWMean300, double MWsigma, double MWVal, double nMWdiff, double nMW300diff, double nMWdiffThreshold, int Outlier, int Cycleslip, TOptions *options);
void printLICSdata (TEpoch *epoch, enum GNSSystem GNSS, int PRN, int satIndex, int satCSIndex, int mode, char *measStr, enum MeasurementType *measList, int *freqList, double InitialLI, double LIVal, double LIDiffAbs, double LIEst, double LIDiffEstAbs, double resThreshold, int Outlier, int Cycleslip, TOptions *options);
void printIGFCSdata (TEpoch *epoch, enum GNSSystem GNSS, int PRN, int satIndex, int satCSIndex, int mode, char *measStr, enum MeasurementType *measList, int *freqList, double InitialIGF, double IGF, double IGFDiffAbs, double IGFEst, double IGFDiffEstAbs, double resThreshold, int Outlier, int Cycleslip, TOptions *options);
void printModel (TEpoch *epoch, int satIndex, int measIndex, enum MeasurementType meas, char *measStr, TBRDCblock *blockOrbit, double measurement, double flightTime, double geometricDistance, double satelliteClockModel, double GNSSClkOffset, double satellitePhaseCenterProjection, double satellitePhaseCenterVarProjection, double receiverPhaseCenterProjection, double  receiverPhaseCenterVarProjection, double receiverARPProjection, double relativityModel, double windUpMetModel, double troposphereModel, double ionosphereModel, double gravitationalDelayModel, double solidTidesModel, double TGDModel, double GPSp1c1DCB, double differentialDCB, double ISCDCB, double preciseDCB, double *DCBmodel, TConstellation *constellation, TOptions *options);
void printSatSel(TEpoch *epoch, int selected, int errorcode, char *message, int satIndex, TOptions *options);
void printPrefit (TEpoch  *epoch, int satIndex, int measIndex, int csIndex, int freq, double prefit, double measurement, double smoothWith, double lambda, double model, double stdDev, TConstellation *constellation, TOptions *options);
void printEpochsat (TEpoch *epoch, int measKindPrint, char *measStr, char *measStrSmooth, int *numUsedSat, int **satUsedList, int *numUnusedSat, int **satUnusedList, TOptions *options);
void printEpochsatAllSat (TEpoch *epoch);
void printFilter (TEpoch  *epoch, int nunk, TFilterSolution *solution, TOptions *options);
void printPostfit (TEpoch  *epoch, int satIndex, int measIndex, int csIndex, double postfit, double measurement, double smoothWith, double model, double estimatedParameters, double InterSystemClock, double ambiguity, double Iono, double satDCB, double recDCB, TConstellation *constellation, TOptions *options);
void printOutput (TEpoch *epoch, TEpoch *epochDGNSS, TFilterSolution *solution, TOptions *options, TUnkinfo *unkinfo, char *Obsfilename, char *version);
void printSatDiff (char **tStr, enum GNSSystem GNSS, int PRN, double SISREDiff, double OrbDiff, double Orb3DDiff, double ClkDiff, double DCBDiff, double *posDiff, double *posDiffXYZ, TBRDCblock *block[2], TOptions *options);
void printSatStat (enum GNSSystem GNSS, int PRN, TStat statSISRE, TStat statOrb, TStat stat3D, TStat statClk, TStat statDCB, TStat statRadOrb, TStat statAloOrb, TStat statCroOrb, TOptions *options);
void printSatStatTot (TStat statSISRETot, TStat statOrbTot, TStat stat3DTot, TStat statClkTot, TStat statDCBTot, TStat statRadOrbTot, TStat statAloOrbTot, TStat statCroOrbTot, TOptions *options);
void printSatPvt (TTime *t, char **tStr, enum GNSSystem GNSS, int PRN, double *position, double *velocity, double *positionNEU, double clockCorr, double elevation, double azimuth, TBRDCblock *block, TConstellation *constellation, TOptions *options);

// SBAS
void writeSBASfiles (FILE  **fdlist, FILE  *readfd, char **filelist, char **line, int *linelen, int numlines, int header, int sourcefile, int decoderesult, int decodedmessagetype, int *prevday, TSBASblock  *sbasblock, TOptions  *options);
void writeRinexBfile (FILE **fdlist, FILE  *readfd, char *filename, char **line, int *linelen, int numlines, int header, int sourcefile, TSBASblock  *sbasblock, TOptions  *options);
void writeEMSfile (FILE **fdlist, FILE  *readfd, char *filename, char **line, int *linelen, int numlines, int header, int sourcefile, TSBASblock  *sbasblock, TOptions  *optionGs);
void writeLogfile (FILE **fdlist, FILE  *readfd, char *filename, char **line, int *linelen, int numlines, int sourcefile, int decoderesult, TSBASblock  *sbasblock, TOptions  *options);
void writeSBASdecodesummary (FILE  **fdlist,FILE  *readfd, char *filename, int  numberofbadmessages, int  totalmessagesmissing, int  msgmissingdetected, int  *linesmissing, int  *listmissing, TOptions  *options);
void writePegasusheaders (FILE **fdlist, FILE *readfd, char **filelist, TOptions  *options);
void writePegasusfiles (FILE **fdlist, FILE *readfd, char **filelist, char **line, int *linelen, int numlines, int sourcefile, int header, int decoderesult, int decodedmessagetype, int *prevday, TSBASblock  *sbasblock, TOptions  *options);
void printSBASCORR (TEpoch *epoch, TSBASdata *SBASdata, TSBAScorr *SBAScorr, int satIndex, int measIndex, double geometricDistance, double satelliteClockModel, double relativityModel, double troposphereModel, double ionosphereModel, double TGDModel, TConstellation *constellation, TOptions *options);
void printSBASVAR (TEpoch *epoch, TSBASdata *SBASdata, TSBAScorr *SBAScorr, int satIndex, TConstellation *constellation, TOptions *options);
void printSBASIONO (TEpoch  *epoch, TSBASdata *SBASdata, int  satIndex, int  InterpolationMode, int  IGP1, int  BandNumber1, double IGPlat1, double IGPlon1, int  IGP2, int  BandNumber2, double IGPlat2, double IGPlon2, int  IGP3, int  BandNumber3, double IGPlat3, double IGPlon3, int  IGP4, int  BandNumber4, double IGPlat4, double IGPlon4, double  eps_iono[5], double  IGPDelays[5], double  IGPSigma2[5], double  IPPWeight[5], double  Fpp, double  SlantDelay, double  SlantSigma, double elevation, double azimuth, TOptions  *options);
void printSBASUNSEL (TEpoch  *epoch, int  satIndex, int errorcode, TSBASdata *SBASdata, TSBAScorr *SBAScorr, TOptions  *options);
void printSBASDFMCCORR (TEpoch *epoch, TSBASdata *SBASdata, TSBAScorr *SBAScorr, int satIndex, double geometricDistance, double satelliteClockModel, double relativityModel, double troposphereModel, double TGDModel, TConstellation *constellation, TOptions *options);
void printSBASDFMCVAR (TEpoch *epoch, TSBASdata *SBASdata, TSBAScorr *SBAScorr, int satIndex, TConstellation *constellation, TOptions *options);
void printSBASDFMCUNSEL (TEpoch  *epoch, int  satIndex, int errorcode, TSBASdata *SBASdata, TSBAScorr *SBAScorr, TOptions  *options);
void printSBASOUT (TEpoch *epoch, TFilterSolution *solution, TOptions *options, TUnkinfo *unkinfo);
void printBuffers (TEpoch *epoch, TOptions *options);
void printBuffersKalman (TEpoch *epoch, TOptions *options);
void printBuffersBestGEO (TEpoch *epoch, int selected, int prevGEOPRN, TOptions *options);

// DGNSS
void writeHeaderRINEXo (FILE *fd, TRTCM3 *rtcm3, TOptions *options);
void writeRINEXo (FILE *fd, TRTCM3 *rtcm3, TOptions *options);
int writeRTCM2ascii (FILE *fd_antenna, FILE *fd_corrections, TRTCM2 *rtcm2, TEpoch *epochDGNSS, TOptions *options);
void printDGNSS (TEpoch *epoch, TEpoch *epochDGNSS, int satIndex, double dt, double deltaPRC, double deltaRRC, double dt2, double *sigmas, TOptions *options);

// User added error functions
void printUserError (TEpoch *epoch, double **SatMeasError, int numpos, TOptions *options);

// Stanford-ESA plot
void writeStdESA (FILE *fd, TStdESA *StdESA);

// Output Rinex Observation file with user added error
void writeRinexObsHeaderUserAddedError (FILE *fd, char **headerlines, int numheaderlines);
void writeObsRinexEpochUserAddedError (FILE *outfd, TEpoch *epoch);

// KML output file
void writeKMLtags(FILE *fd, TEpoch  *epoch, char *filename, int mode, int heightmode, char *version, TOptions  *options);

// SP3 output file
void writeSP3file(FILE *fd, TEpoch  *epoch, TFilterSolution  *solution, TUnkinfo  *unkinfo, int EndofFile, char *version, TOptions  *options);

// Reference output file
void writeReffile(FILE *fd, TEpoch  *epoch, TFilterSolution  *solution, TUnkinfo  *unkinfo, TOptions  *options);

// SBAS output files
void writeSBASAvailFile (FILE *fdAvail, FILE *fdRisk, FILE *fdRiskMar, FILE *fdDiscont, FILE *fdHDOP, FILE *fdPDOP, FILE *fdGDOP, FILE *fdCombDOP, TEpoch  *epoch, TSBASPlots *SBASplots, int totalAvailabilityEpochs, int hour, TOptions *options);
void writeSBASIonoAvailFile (FILE *fd, TEpoch  *epoch, TSBASPlots *SBASplots, int totalIonoEpochs, int hour, TOptions *options);

// Summary print
void printSBASSummary (long long unsigned int StartTimeRealPCTime, int *ProcTimeLength, int *PosProcTime, TEpoch  *epoch, TSBASdatabox *SBASdatabox, TStdESA *StdESA, TOptions *options);
void printDGNSSSummary (long long unsigned int StartTimeRealPCTime, int *ProcTimeLength, int *PosProcTime, TEpoch *epoch, TEpoch *epochDGNSS, TStdESA *StdESA, TOptions *options);
void printSummary (long long unsigned int StartTimeRealPCTime, int *ProcTimeLength, int *PosProcTime, TEpoch *epoch, TStdESA *StdESA, TOptions *options);

//Date format print
void printDates(int year, int month, int day, int hour, int minute, double seconds, int DoY, double SoD, int GPSweek, int DoW, double SoW, int MJDNVal, TOptions  *options);

//Coordinate system print
void printCoordinates(double *positionXYZ, double *positionNEU, double *positionSph, TOptions  *options);

//Compute processing time
void computeProcessingTime (long long unsigned int StartTimeRealPCTime, long long unsigned int *totalprocessingTime, int printProcTime, TOptions *options);

#endif /*OUTPUT_H_*/
