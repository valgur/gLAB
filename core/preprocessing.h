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
 * Developers: Deimos Ibanez Segura ( gAGE/UPC )
 *             Jesus Romero Sanchez ( gAGE/UPC )
 *          glab.gage @ upc.edu
 * File: preprocessing.h
 * Code Management Tool File Version: 6.0  Revision: 0
 * Date: 2024/11/22
 ***************************************************************************/

/****************************************************************************
 * MODULE DESCRIPTION
 *
 * Name: preprocessing
 * Language: C
 *
 * Purpose:
 *  The purpose of this module is to preprocess the input data
 * 
 * Function:
 *  This class is in charge of preprocessing the input data by doing several
 *  steps:
 *     - Cycle-slip detection
 *     - Inconsistent pseudorange-carrierphase jump detection (for Septentrio receivers)
 *     - Epoch decimation
 *     - Carrier-phase prealignment
 *     - Pseudorange smoothing
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
 * Change Log: No changes in this file.
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
 * -----------
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
 * Change Log: Added polyfit function. It fits a polynomial and estimates the geometry-free (LI) prediction.
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
 * Change Log: Added sigmaInflation function, to inflate the sigma during the convergence of the smoother.
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
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.1.1
 * Release: 2017/12/22
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.1.2
 * Release: 2018/01/12
 * Change Log: 'checkCycleSlips' function is now of type 'void' instead of 'int'.
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
 * Release: 2018/10/23
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

#ifndef PREPROCESSING_H_
#define PREPROCESSING_H_

#if defined __WIN32__
 	//This is to allow %lld, %llu and %n format specifiers in printf with MinGW
	#define __USE_MINGW_ANSI_STDIO  1
#endif

/* System modules */
#include <stdio.h>
#include <math.h>

/* External classes */
#include "dataHandling.h"
#include "output.h"

/* Internal types, constants and data */

// General
void preprocess (TEpoch *epoch, TOptions *options, int mode);

// Decimation
int isEpochDecimated (TEpoch *epoch, TOptions *options);

// Eclipse
int isEclipsed (TTime *t, TSatellite *sat, TSatInfo *satInfo, double sunPos[3], double *tLast);

// Carrier phase prealignment
void prealignSat (TEpoch *epoch, int ind);
void prealignEpoch (TEpoch *epoch, TOptions  *options);

// Data checks and cycle-slip detection
double lagrangeInterpolation (int degree, TTime t, TTime *tPrev, double *yPrev);
int checkPseudorangeJumps (TEpoch *epoch, TOptions *options);
double polyfit (TTime *t, TTime *tSamples, double *Samples, int outlier, int numsamples, double *res);
void checkCycleSlips (TEpoch *epoch, TOptions *options, int mode);
void look4interval (TEpoch *epoch, TOptions  *options);

// Smoothing
void smoothEpoch (TEpoch *epoch, TOptions *options);

// Sigma inflation
void sigmaInflation (TEpoch *epoch, TOptions *options);

#endif /*PREPROCESSING_H_*/
