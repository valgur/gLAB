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
 * Developers: Deimos Ibáñez Segura ( gAGE/UPC )
 *             Jesus Romero Sanchez ( gAGE/UPC )
 *          glab.gage @ upc.edu
 * File: filter.h
 * Code Management Tool File Version: 5.5  Revision: 1
 * Date: 2020/12/11
 ***************************************************************************/

/****************************************************************************
 * MODULE DESCRIPTION
 *
 * Name: filter
 * Language: C
 *
 * Purpose:
 *  The purpose of this module is to contain all the necessary functions to
 *  do a Kalman filtering process.
 *
 * Function:
 *  This class is in charge of declaring providing all the necessary functions
 *  to do a Kalman filtering process. It has a high level function (Kalman) in
 *  which, given all necessary inputs, provides the estimated values for the
 *  parameters 
 *
 * Dependencies:
 *  dataHandling, model
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
 * Change Log: First public version
 * -------------
 *          gLAB v1.3.2
 * Release: 2010/01/22
 * Change Log: No changes in this file
 * -------------
 *          gLAB v1.4.0
 * Release: 2010/01/22
 * Change Log: No changes in this file
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
 * Change Log: Dilution Of Precision extension: (GDOP, PDOP, TDOP, VDOP, HDOP).
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
 * Change Log: Added step detector function.
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
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v4.1.0
 * Release: 2017/04/07
 * Change Log: Added functions PrefitOutlierDetectorMedian and PrefitOutlierDetectorAbsolute for prefit outlier detection.
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
 * Change Log: No changes in this file.
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
 *       END_RELEASE_HISTORY
 *****************************/

#ifndef FILTER_H_
#define FILTER_H_

/* System modules */
#include <stdio.h>
#include <string.h>

/* External classes */
#include "dataHandling.h"
#include "model.h"

/* Internal types, constants and data */

// Matrix handling
int m2v (int i, int j);
//static inline int m2v_opt (int i, int j); //Static functions must be declared only in the .c file where is going to be used
int cholinv (double *mat, int n);
int cholinv_opt (double *mat, int n);
void mxv (double *mat, double *vec, int n);

// Filtering
void StepDetector (TEpoch *epoch, TOptions *options);
void PrefitOutlierDetectorAbsolute (TEpoch *epoch, TOptions *options);
void PrefitOutlierDetectorMedian (TEpoch *epoch, TOptions *options);
void fillUsableSatellites (TEpoch *epoch, TOptions *options);
int isEpochComputable (TEpoch *epoch);
int calculateUnknowns (int obs, TOptions *options);
void initUnkinfo (TEpoch *epoch, TUnkinfo *unkinfo, int nunk, int observations, double t, TOptions *options);
void prepareCorrelation (TEpoch *epoch,TFilterSolution *solution,int *PRNlist, TUnkinfo *unkinfo, TUnkinfo *prevUnkinfo, TOptions *options);
void atwa_atwy_insertline (double *atwa, double *atwy, double *unk, double prefit, int nunk, double sigma2);
void atwa_atwy_insertLineWithCorrelation (double *atwa, double *atwy, double *corr, double apriorivalue, int nunk, double multiplier, int iniunk);
void designSystem (TEpoch *epoch, double *atwa, double *atwy, TUnkinfo *unkinfo, enum MeasurementType measType, int filterInd, double **G, double *prefits, double *weights, TOptions *options);
void designSystemIniValues (TEpoch *epoch, double *atwa, double *atwy, TUnkinfo *unkinfo, TFilterSolution *solution);
double calculatePostfits (TEpoch *epoch, double *solution, TUnkinfo *unkinfo, enum MeasurementType measType, int filterInd, TOptions *options);
int computeSolution (TEpoch *epoch,double *stddev2postfit, TFilterSolution *solution, double *newcorrelations, double *newparameterValues, TUnkinfo *unkinfo, TStdESA *StdESA, TOptions *options);
int calculateDOP (TEpoch *epoch, TFilterSolution *solution, char *errorstr, TOptions *options);
void StanfordESAComputationRecursive (TEpoch *epoch, char *epochString, int *k, int *kmask, int numsat, int depth, double **G, double *prefits, double *weights, TUnkinfo *unkinfo, TStdESA *StdESA, TOptions  *options);
void DGNSSSummaryDataUpdate (int UseReferenceFile, TEpoch *epoch, TFilterSolution *solution, TOptions *options, TUnkinfo *unkinfo);
void SBASSummaryDataUpdate (int UseReferenceFile, TEpoch *epoch, TFilterSolution *solution, TSBASdatabox *SBASdatabox, TOptions *options, TUnkinfo *unkinfo);
void SummaryDataUpdate (int UseReferenceFile, TEpoch *epoch, TFilterSolution *solution, TOptions *options, TUnkinfo *unkinfo);
int calculateSBASAvailability (FILE *fdDiscont, FILE *fdDiscontHour, int LatPos, int LonPos, double latitude, double longitude, TEpoch *epoch, TSBASPlots *SBASplots, TOptions *options);
void updatePRNlist (TEpoch *epoch, int *PRNlist, TFilterSolution *solution);
int Kalman (TEpoch *epoch, TFilterSolution *solution, int *PRNlist, TUnkinfo *prevUnkinfo, TStdESA *StdESA, TOptions *options);

#endif /*FILTER_H_*/
