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
 * File: model.h
 * Code Management Tool File Version: 5.5  Revision: 1
 * Date: 2020/12/11
 ***************************************************************************/

/****************************************************************************
 * MODULE DESCRIPTION
 *
 * Name: model
 * Language: C
 *
 * Purpose:
 *  The purpose of this module is to fully model an epoch of data
 *
 * Function:
 *  This class is in charge of modeling an epoch of data. This module is fully
 *  configurable through a Toptions structure, being able to connect or disconnect
 *  each model separately.
 *
 * Dependencies:
 *  dataHandling, preprocessing
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
 * Release: 2010/02/23
 * Change Log: Inertial/non-inertial velocity switch included
 *             TGDs from DCB files
 * -------------
 *          gLAB v1.4.0
 * Release: 2010/06/21
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
 * Change Log: Added functions for BeiDou, IONEX, Fast-PPP and NeQuick ionosphere models.
 *             Added functions for using Fast-PPP and IONEX DCBs.
 *             Added functions for ESA's troposphere model.
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
 * Change Log: Added satellitePhaseCenterVarCorrection and receiverPhaseCenterVarCorrection functions for phase variation correction.
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
 * Change Log: Fixed iono sigma not being transformed from TECUs to meters of the frequency of the measurement in the filter
 * -----------
 *          gLAB v2.2.8
 * Release: 2016/04/12
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v3.0.0
 * Release: 2016/09/05 
 * Change Log: Added SBAS processing.
 *             Concatenated RINEX and SP3 files can be read now.
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
 * Change Log: Added DGNSS processing.
 *             Added function NEU2XYZ.
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
 * Change Log:   Added functions for 'XYZ2Spherical' and 'Spherical2XYZ' for coordinate conversion.
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
 * Change Log:   Added NeQuick code from JRC.
 * -----------
 *          gLAB v5.5.1
 * Release: 2020/12/11
 * Change Log: No changes in this file.
 * -----------
 *       END_RELEASE_HISTORY
 *****************************/

#ifndef MODEL_H_
#define MODEL_H_

/* System modules */
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* External classes */
#include "dataHandling.h"
#include "preprocessing.h"

/* Internal types, constants and data */

// Orientation routines
void getSatelliteOrientationACR (double *position, double *velocity, double orientation[3][3]);
void getSatelliteOrientation (TTime *t, double *position, double orientation[3][3]);
void fillSatelliteOrientation (TEpoch *epoch, int satIndex);
void fillGroundStationNEU (TEpoch *epoch);
void getGroundStationOrientation (double *position, double orientation[3][3]);
void fillGroundStationOrientation (TEpoch *epoch);
void getAzimuthElevation (double orientation[3][3], double *receiverPosition, double *satellitePosition, double *azimuth, double *elevation);
void fillAzimuthElevation (TEpoch *epoch, int satIndex);
void rotate (double *v, double angle, int axis);

// Transmission time estimation
int fillTransmissionTimeSat (TEpoch *epoch, TGNSSproducts *products, int ind, TSBAScorr *SBAScorr, TOptions *options);
void fillTransmissionTime (TEpoch *epoch, TGNSSproducts *products, TSBAScorr *SBAScorr, TOptions *options);
double computeFlightTime (TEpoch *epoch, TGNSSproducts *products, int satIndex, TSBAScorr *SBAScorr, TOptions *options);
void correctEarthRotation (double *x, double flightTime);

// Orbits and clocks products
double nsteffensen (double Mk, double e);
int satellitePhaseCenterCorrection3D (TTime *t, enum GNSSystem GNSS, int PRN, enum MeasurementType meas, double orientation[3][3], TConstellation *constellation, double *dr);
int satellitePhaseCenterCorrection (TTime *t, enum GNSSystem GNSS, int PRN, enum MeasurementType meas, double orientation[3][3], double *LoS, TConstellation *constellation, double *pc);
int satellitePhaseCenterVarCorrection (TTime *t, enum GNSSystem GNSS, int PRN, enum MeasurementType meas, double satearthdistance, double elevation, TConstellation *constellation, double *pvc);
double getClockBRDC (TBRDCblock *block,TTime *t);
void getPositionBRDC (TBRDCproducts *products, TBRDCblock *block, TTime *t, enum GNSSystem GNSS,double *position);
void getVelocityBRDC (TBRDCproducts *products, TBRDCblock *block, TTime *t,double *position, double *velocity, enum SatelliteVelocity satVel, enum GNSSystem GNSS);
double getClockSP3 (TGNSSproducts *products, TTime *t,enum GNSSystem GNSS,int PRN, TOptions *options);
int getPositionSP3 (TGNSSproducts *products, TTime *t,enum GNSSystem GNSS,int PRN, double *position, TOptions *options);
int getVelocitySP3 (TGNSSproducts *products, TTime *t,enum GNSSystem GNSS,int PRN, double *position, double *velocity, enum SatelliteVelocity satVel, TOptions *options);
int getSatellitePVTBRDCraw (TGNSSproducts *products, TTime *t, enum GNSSystem GNSS, int PRN, double *position, double *velocity, double *ITRFvel, double *clock, int SBASIOD, TOptions *options);
int getSatellitePVTSP3raw (TGNSSproducts *products, TTime *t, enum GNSSystem GNSS, int PRN, double *position, double *velocity, double *ITRFvel, double *clock, TOptions *options);
int getSatellitePVT (TGNSSproducts *products, TTime *t, double flightTime, enum GNSSystem GNSS, int PRN, double *position, double *velocity, double *ITRFvel, double *clock, int SBASIOD, TOptions *options);
int fillSatellitePVT (TEpoch *epoch, TGNSSproducts *products, TTime *t, double flightTime, int satIndex, int position, int velocity, int clock, int SBASIOD, TConstellation *constellation, TOptions *options);
void getLineOfSight (double *satPos, double *recPos, double *LoS);
void fillLineOfSight (TEpoch *epoch, int satIndex);
void findMoon (TTime *t, double* moonPosition);
void findSun (TTime *t, double* sunPosition);
void GSDtime_sun (TTime *t,double *gstr, double *slong, double *sra, double *sdec);

// Receiver antenna corrections
double receiverPhaseCenterCorrection (TAntenna *antenna, enum GNSSystem GNSS, enum MeasurementType meas, double orientation[3][3], double *LoS);
double receiverPhaseCenterVarCorrection (TAntenna *antenna, enum GNSSystem GNSS, enum MeasurementType meas, double elevation);
double receiverARPCorrection (double *ARP, double orientation[3][3], double *LoS);

// Relativistic correction
double relativisticCorrection (double *position, double *velocity);

// Wind up correction
double windUpCorrection (TEpoch *epoch, int satIndex);

// Tropospheric correction
double interpolateNiell (double x, double v[3][5], int i);
double xmNiell (double elevation, double vector[3]);
void tropNiell (TTime *t,double *positionNEU,double elevation,double *tropDryMap,double *tropWetMap);
double troposphericCorrection (TTime *t, double *positionNEU, double elevation, TTROPOGal *TropoGal, double *tropWetMap, double *ZTD, TOptions *options);
void troposphericCorrectionMOPS (TTime *t, double *positionNEU, double elevation,double *tropWetMOPS_Nominal,double *tropDryMOPS_Nominal);
void troposphericCorrectionGal (TTime *t, double *positionNEU, double elevation, TTROPOGal *TropoGal, double *tropWetESA_Nominal, double *tropDryESA_Nominal);
void troposphericGalparameters (TTime  *t, int ilat, int ilon, double latitude, double longitude, double  *positionNEU, double  elevation, double MapPoints[4][3], double *hgt_pix, TTROPOGal *TropoGal, TTROPOGalParameters *parameters); 

// Ionospheric correction
double klobucharModel (TEpoch *epoch,TGNSSproducts *products, int satIndex);
double beiDouKlobucharModel (TEpoch *epoch, TGNSSproducts *products, int satIndex);
double ionexModel (TEpoch *epoch, int satIndex, TIONEX *ionex, TOptions *options);
double FPPPModel (TEpoch *epoch, int satIndex, TFPPPIONEX *fppp, TOptions *options);
double NeQuickfunctionCall (TEpoch *epoch, int satIndex,TGNSSproducts *products, TOptions *options);

// Gravitational delay correction
double gravitationalDelayCorrection (double *receiverPosition, double *satellitePosition);

// TGD correction
void getTGDfromDCB (TTGDdata *tgdData, TReceiver *rec, enum GNSSystem GNSS, int PRN, TTime *t, enum MeasurementType measFrom, enum MeasurementType measTo, double *dcb, int *retDCB, int *retDCBC1P1);
double TGDCorrectionBRDC (TEpoch *epoch, int satIndex, int SBASIOD, TTime *t, TBRDCproducts *products, TOptions *options);
double TGDCorrectionIONEX (TEpoch *epoch, int satIndex,TIonexDCB *ionexDCB,TOptions *options);
double TGDCorrectionFPPP (TEpoch *epoch, int satIndex,TFPPPDCB *fpppDCB,TOptions *options);
double TGDCorrection (TEpoch *epoch, int satIndex, TTime *t, enum MeasurementType meas, int SBASIOD, TTGDdata *tgdData, TOptions *options);

// Solid tides
void fillSolidTideDisplacement (TEpoch *epoch);
double solidTidesCorrection (TEpoch *epoch, int satIndex);

// General
void fillGeometricDistance (TEpoch *epoch,int satIndex);
int fillMeasurementWeights (TEpoch *epoch, int satIndex, double SBASsigma, double DGNSSsigma, TOptions *options);

// ANTEX
TAntenna *getAntenna (char *name, TAntennaList *antennaList, TOptions *options);

// GPS Receiver type
TReceiverData *getReceiverType (char *name, TReceiverList *recList);

// General modeling
int modelEpoch (TEpoch *epoch, TOptions *options);
int modelSatellite (TEpoch *epoch, TEpoch *epochDGNSS, int satIndex, TGNSSproducts *products, TGNSSproducts *klbProd, TGNSSproducts  *beiProd, TGNSSproducts *neqProd, TIONEX *Ionex, TFPPPIONEX *Fppp, TTROPOGal *TropoGal, TTGDdata *tgdData, TConstellation *constellation, TSBASdata *SBASdata, TOptions *options);

// SBAS processing
int computeSBAS (TEpoch *epoch, TGNSSproducts  *products, TGNSSproducts *klbProd, TGNSSproducts  *beiProd, TGNSSproducts *neqProd, TIONEX *Ionex, TFPPPIONEX *Fppp, int satIndex, enum MeasurementType meas, int measIndex, TSBASdata *SBASdata, TSBAScorr *SBAScorr, TOptions *options);
double SBASIonoModel (TEpoch *epoch, TGNSSproducts *products, int satIndex, int *errorvalue, TSBAScorr *SBAScorr, TSBASdata *SBASdata, TOptions *options);
int SwitchSBASGEOMode (TEpoch  *epoch, int  numsatellites, int  numsatdiscardedSBAS, TSBASdata *SBASdata, TOptions  *options);

// DGNSS processing
void prepareDGNSScorrections (TEpoch *epoch, TEpoch *epochDGNSS, TGNSSproducts *products, TOptions *options);
void computeDGNSScorrections (TEpoch *epoch, TEpoch *epochDGNSS, TGNSSproducts *products, TOptions *options);
void preFillUsableSatellites (TEpoch *epoch, TEpoch *epochDGNSS, TGNSSproducts *products, TOptions *options);


// NeQuick-G JRC. Implementation begin

#define max_(a, b) ((a) >= (b) ? (a) : (b))

/** Invalid handle */
#define NEQUICKG_INVALID_HANDLE (NULL)

/** Effective Ionisation Level uses 3rd order parameter. */
#define NEQUICKG_AZ_COEFFICIENTS_COUNT (3)

/** Number of WGS-84 ellipsoidal coordinates:
 * latitude, longitude and height
 */
#define NEQUICKG_WGS_84_ELLIPSOIDAL_COORDINATES_COUNT (3)

/** Number of time parameters:
 * month and UTC
 */
#define NEQUICKG_TIME_PARAMETERS_COUNT (2)

/** NeQuick success */
#define NEQUICK_OK 0

#define ITU_R_P_371_8_LOWER_SOLAR_FLUX_IN_SFU (63.7)

#define NEQUICK_G_JRC_HEIGHT_UNITS_METERS (0)
#define NEQUICK_G_JRC_HEIGHT_UNITS_KM (1)

/* Minimum latitude in degrees. */
#define NEQUICK_G_JRC_LAT_MIN_VALUE_DEGREE (-90.0)
/* Maximum latitude in degrees */
#define NEQUICK_G_JRC_LAT_MAX_VALUE_DEGREE (90.0)
/* Maximum longitude in degrees */
#define NEQUICK_G_JRC_LONG_MAX_VALUE_DEGREE  (180.0)

/** Value of mathematical constant PI*2 */
#define NEQUICK_G_JRC_TWO_PI (6.283185307179586476925287)

/** Value of mathematical constant PI */
#define NEQUICK_G_JRC_PI (NEQUICK_G_JRC_TWO_PI / 2.0)

/** Circle degrees*/
#define NEQUICK_G_JRC_CIRCLE_DEGREES (360.0)

/** Degrees to radians */
#define NEQUICK_G_JRC_DEGREE_TO_RADIAN (NEQUICK_G_JRC_PI / 180.0)

/** Radians to degrees. */
#define NEQUICK_G_JRC_RADIAN_TO_DEGREE (180.0 / NEQUICK_G_JRC_PI)

#define NEQUICKG_JRC_DEGREE_TO_RAD(_degree) \
  ((_degree) * NEQUICK_G_JRC_DEGREE_TO_RADIAN)

#define NEQUICKG_JRC_RAD_TO_DEGREE(_rad) \
  ((_rad) * NEQUICK_G_JRC_RADIAN_TO_DEGREE)

#define NEQUICK_G_JRC_ELE_DENSITY_TOP_CONST_1 (0.125)
#define NEQUICK_G_JRC_ELE_DENSITY_TOP_CONST_2 (100.0)
#define NEQUICK_G_JRC_ELE_DENSITY_TOP_APROXIMATION_EPSILON (1.0e11)
#define NEQUICK_G_JRC_ELE_DENSITY_BOTTOM_CORRECTION_ANCHOR_POINT (100.0)
#define NEQUICK_G_JRC_ELE_DENSITY_BOTTOM_CONST_1 (10.0)
#define NEQUICK_G_JRC_ELE_DENSITY_BOTTOM_CONST_2 (1.0)
#define NEQUICK_G_JRC_ELE_DENSITY_BOTTOM_SCALE (10.0)
#define NEQUICK_G_JRC_ELE_DENSITY_BOTTOM_EPSILON (25.0)

#define NEQUICK_G_JRC_ELE_DENSITY_TO_ELECTRON_DENSITY(_N) (1.0e11*_N)

/* Num of K15 pts for Kronrod integration */
#define NEQUICK_G_JRC_KRONROD_K15_POINT_COUNT (15)
/* Num of G7 pts for Kronrod integration */
#define NEQUICK_G_JRC_KRONROD_G7_POINT_COUNT (7)

/* Constants for where samples are taken in the Kronrod integration
 * (i.e. how far from the midpoint).
 */
#define NEQUICK_G_JRC_KRONROD_POINT_1 (0.207784955007898467600689403773245)
#define NEQUICK_G_JRC_KRONROD_POINT_2 (0.405845151377397166906606412076961)
#define NEQUICK_G_JRC_KRONROD_POINT_3 (0.586087235467691130294144838258730)
#define NEQUICK_G_JRC_KRONROD_POINT_4 (0.741531185599394439863864773280788)
#define NEQUICK_G_JRC_KRONROD_POINT_5 (0.864864423359769072789712788640926)
#define NEQUICK_G_JRC_KRONROD_POINT_6 (0.949107912342758524526189684047851)
#define NEQUICK_G_JRC_KRONROD_POINT_7 (0.991455371120812639206854697526329)

/** Constants for weights for K15 sample points in Kronrod integration */
#define NEQUICK_G_JRC_KRONROD_K15_WEIGHT_1 (0.022935322010529224963732008058970)
#define NEQUICK_G_JRC_KRONROD_K15_WEIGHT_2 (0.063092092629978553290700663189204)
#define NEQUICK_G_JRC_KRONROD_K15_WEIGHT_3 (0.104790010322250183839876322541518)
#define NEQUICK_G_JRC_KRONROD_K15_WEIGHT_4 (0.140653259715525918745189590510238)
#define NEQUICK_G_JRC_KRONROD_K15_WEIGHT_5 (0.169004726639267902826583426598550)
#define NEQUICK_G_JRC_KRONROD_K15_WEIGHT_6 (0.190350578064785409913256402421014)
#define NEQUICK_G_JRC_KRONROD_K15_WEIGHT_7 (0.204432940075298892414161999234649)
#define NEQUICK_G_JRC_KRONROD_K15_WEIGHT_8 (0.209482141084727828012999174891714)

#define NEQUICK_G_JRC_KRONROD_G7_WEIGHT_1 (0.129484966168869693270611432679082)
#define NEQUICK_G_JRC_KRONROD_G7_WEIGHT_2 (0.279705391489276667901467771423780)
#define NEQUICK_G_JRC_KRONROD_G7_WEIGHT_3 (0.381830050505118944950369775488975)
#define NEQUICK_G_JRC_KRONROD_G7_WEIGHT_4 (0.417959183673469387755102040816327)

#define NEQUICK_G_INPUT_DATA_RECORD_FORMAT \
  "%hhu %2.2f %7.2f %6.2f %7.2f %7.2f %6.2f %9.2f"

/** 2.5.7.1. Threshold for interpolation */
#define NEQUICK_G_JRC_INTERPOL_EPSILON (5.0e-11)

/** Index for interpolation point 0 */
#define NEQUICK_G_JRC_INTERPOL_POINT_0_INDEX (0)
/** Index for interpolation point 1 */
#define NEQUICK_G_JRC_INTERPOL_POINT_1_INDEX (1)
/** Index for interpolation point 2 */
#define NEQUICK_G_JRC_INTERPOL_POINT_2_INDEX (2)
/** Index for interpolation point 3 */
#define NEQUICK_G_JRC_INTERPOL_POINT_3_INDEX (3)

/** First Constant used in interpolation_third_order */
#define NEQUICK_G_JRC_INTERPOL_FIRST_CONST (9.0)
/** Second Constant used in interpolation_third_order */
#define NEQUICK_G_JRC_INTERPOL_SECOND_CONST (16.0)

/** Number of points used in interpolate */
#define NEQUICK_G_JRC_INTERPOLATE_POINT_COUNT (4)

#define NEQUICK_G_JRC_IONO_E_LAYER_LAT_FACTOR (0.3)
#define NEQUICK_G_JRC_IONO_E_LAYER_CONSTANT_1 (1.112)
#define NEQUICK_G_JRC_IONO_E_LAYER_CONSTANT_2 (0.019)
#define NEQUICK_G_JRC_IONO_E_LAYER_CONSTANT_3 (0.3)
#define NEQUICK_G_JRC_IONO_E_LAYER_CONSTANT_4 (0.49)
/**The E layer maximum density height hmE [km] is defined as a constant */
#define NEQUICK_G_JRC_IONO_E_LAYER_MAX_e_DENSITY_HEIGHT_KM (120)
#define NEQUICK_G_JRC_IONO_E_LAYER_BOTTOM_KM (5.0)
#define NEQUICK_G_JRC_IONO_E_LAYER_MIN_TOP_KM (7.0)

#define NEQUICK_G_JRC_IONO_E_LAYER_CRITICAL_FREQUENCY_NEGLIGIBLE (1.0e-30)

#define NEQUICK_G_JRC_IONO_E_LAYER_INFLUENCES_F2_PEAK_HEIGHT(_crit_freq_MHz) \
(_crit_freq_MHz >=  \
  NEQUICK_G_JRC_IONO_E_LAYER_CRITICAL_FREQUENCY_NEGLIGIBLE)

#define NEQUICK_G_JRC_IONO_E_LAYER_AMPLITUDE_CONSTANT_1 (5.0e-2)
#define NEQUICK_G_JRC_IONO_E_LAYER_AMPLITUDE_WITH_TRANSITION_REGION (60.0)
#define NEQUICK_G_JRC_IONO_E_LAYER_AMPLITUDE_CONSTANT_2 (5.0e-3)

#define NEQUICK_G_JRC_IONO_F1_LAYER_TITHERIDGE_FACTOR (1.4)
#define NEQUICK_G_JRC_IONO_F1_LAYER_JOIN_FRACTIONAL_1 (1000.0)
#define NEQUICK_G_JRC_IONO_F1_LAYER_JOIN_FRACTIONAL_2 (60.0)
#define NEQUICK_G_JRC_IONO_F1_LAYER_HEIGHT_CONSTANT (0.85)
#define NEQUICK_G_JRC_IONO_F1_FREQUENCY_LOWER_LIMIT_MHZ (1.0e-6)

#define NEQUICK_G_JRC_IONO_F1_LAYER_THICKNESS_TOP_FACTOR (0.3)
#define NEQUICK_G_JRC_IONO_F1_LAYER_THICKNESS_BOTTOM_FACTOR (0.5)

#define NEQUICK_G_JRC_IONO_F1_LAYER_AMPLITUDE_CONSTANT (0.8)

/** The F1 layer critical frequency foF1 (MHz)
 *
 * the initial formulation of the model was:
 *  foF1 is taken to be 1.4 × foE
 *  (Titheridge’s Formula, Leitinger et al., 1999) during
 *  daytime and is set zero during nighttime.
 * but in some cases strong gradients and strange structures appeared
 * in E and F1-layer heights.
 * so the formulation of f0F1 was changed to:
 *
 *        | 0            if foE < 2
 * foF1 = | 1.4f0E       if foE >= 2 and 1.4foE <= 0.85 foF2
 *        | 0.85*1.4foE  if 1.4 foE > 0.85*foF2
 *
 * if foF1 < 10-6 then foF1 = 0
 *
 * the original formulation was 1.4f0E for all daytime conditions,
 * now 0.85*1.4foE if 1.4 foE > 0.85*foF2.
 *
 * See Leitinger et al.
 * "An improved bottomside for the ionospheric electron density model NeQuick",
 * Annals of Geophysics, 48(3), p. 525-534, 2005.
 *
 * The implementation takes into account the need to ensure continuity
 * and derivability over the full range of f0F1,
 * by making use of NeQuickG_func_join
 *
 * @param critical_freq_E_layer_MHz E layer critical frequency foE (MHz)
 * @param critical_freq_F2_layer_MHz F2 layer critical frequency foF2 (MHz)
 *
 * @return The F1 layer critical frequency foF1 (MHz)
 *
 */

#define NEQUICK_G_F1_LAYER_IS_PEAK_PRESENT(_F1) \
 (_F1.critical_frequency_MHz >= 0.5)

#define NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_0_LEGRENDE_GRADE (12)
#define NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_1_LEGRENDE_GRADE (12)
#define NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_2_LEGRENDE_GRADE (9)
#define NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_3_LEGRENDE_GRADE (5)
#define NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_4_LEGRENDE_GRADE (2)
#define NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_5_LEGRENDE_GRADE (1)
#define NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_6_LEGRENDE_GRADE (1)
#define NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_7_LEGRENDE_GRADE (1)
#define NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_8_LEGRENDE_GRADE (1)
#define NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_COUNT (9)

#define NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_0_LEGRENDE_GRADE (7)
#define NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_1_LEGRENDE_GRADE (8)
#define NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_2_LEGRENDE_GRADE (6)
#define NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_3_LEGRENDE_GRADE (3)
#define NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_4_LEGRENDE_GRADE (2)
#define NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_5_LEGRENDE_GRADE (1)
#define NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_6_LEGRENDE_GRADE (1)
#define NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_COUNT (7)

#define NEQUICKG_JRC_IONO_F2_LAYER_MODIP_COEFF_COUNT \
  (max_(NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_0_LEGRENDE_GRADE, \
    max_(NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_1_LEGRENDE_GRADE, \
      max_(NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_2_LEGRENDE_GRADE, \
        max_(NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_3_LEGRENDE_GRADE, \
          max_(NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_4_LEGRENDE_GRADE, \
            max_(NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_5_LEGRENDE_GRADE, \
              max_(NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_6_LEGRENDE_GRADE, \
                max_(NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_7_LEGRENDE_GRADE, \
                  max_(NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_8_LEGRENDE_GRADE, \
                    max_(NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_0_LEGRENDE_GRADE, \
                      max_(NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_1_LEGRENDE_GRADE, \
                        max_(NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_2_LEGRENDE_GRADE, \
                          max_(NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_3_LEGRENDE_GRADE, \
                            max_(NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_4_LEGRENDE_GRADE, \
                              max_(NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_5_LEGRENDE_GRADE, \
                                NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_6_LEGRENDE_GRADE \
                              ) \
                            ) \
                          ) \
                        ) \
                      ) \
                    ) \
                  ) \
                ) \
              ) \
            ) \
          ) \
        ) \
      ) \
    ) \
  ))

#define NEQUICKG_JRC_IONO_F2_LAYER_LONG_COEFF_COUNT \
  (max_(NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_COUNT, \
    NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_COUNT) - 1)

#if ((NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_0_LEGRENDE_GRADE + \
    2 * ( \
      NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_1_LEGRENDE_GRADE + \
      NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_2_LEGRENDE_GRADE + \
      NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_3_LEGRENDE_GRADE + \
      NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_4_LEGRENDE_GRADE + \
      NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_5_LEGRENDE_GRADE + \
      NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_6_LEGRENDE_GRADE + \
      NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_7_LEGRENDE_GRADE + \
      NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_8_LEGRENDE_GRADE )) \
    != ITU_F2_COEFF_MAX_DEGREE)
  #error "Please, review  \
NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_N_LEGRENDE_GRADE array"
#endif

#if ((NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_0_LEGRENDE_GRADE + \
    2 * ( \
      NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_1_LEGRENDE_GRADE + \
      NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_2_LEGRENDE_GRADE + \
      NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_3_LEGRENDE_GRADE + \
      NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_4_LEGRENDE_GRADE + \
      NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_5_LEGRENDE_GRADE + \
      NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_6_LEGRENDE_GRADE)) \
    != ITU_FM3_COEFF_MAX_DEGREE)
  #error "Please, review  \
NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_N_LEGRENDE_GRADE array"
#endif

/** Modip legendre coefficients are set to zero
 * if their absolute value is found to be 1.0e-30
 *
 */
#define NEQUICKG_JRC_IONO_F2_LAYER_MODIP_COEFF_NEGLIGIBLE_VALUE (1.0e-30)

/** Transmission factor must be at least 1.0
 * otherwise a square root could be calculated
 * with a negative operand.
 * TBD. (undocumented feature and value)
 */
#define NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_MINIMUM_VALUE (1.0)

#define NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_CONST_1 (1490.0)
#define NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_CONST_2 (0.0196)
#define NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_CONST_3 (1.2967)
#define NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_CONST_4 (-0.012)
#define NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_CONST_5 (0.253)
#define NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_CONST_6 (1.215)
#define NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_CONST_7 (-176.0)
#define NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_JOIN_CONST (20.0)
#define NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_JOIN_CLIP_CONST (1.75)

#define NEQUICK_G_JRC_IONO_F2_LAYER_THICKNESS_BOTTOM_FACTOR (0.385)

#define NEQUICKG_JRC_IONO_F2_e_DENSITY_GRAD_CONST_1 (0.01)
#define NEQUICKG_JRC_IONO_F2_e_DENSITY_GRAD_CONST_2 (-3.467)
#define NEQUICKG_JRC_IONO_F2_e_DENSITY_GRAD_CONST_3 (0.857)
#define NEQUICKG_JRC_IONO_F2_e_DENSITY_GRAD_CONST_4 (2.02)

#define NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_1 (6.705)
#define NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_2 (-0.014)
#define NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_3 (-0.008)
#define NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_4 (-7.77)
#define NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_5 (0.097)
#define NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_6 (0.153)
#define NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_7 (2.0)
#define NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_8 (8.0)
#define NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_TRANSITION_REGION (1.0)

/* Constants used to calculate the F2 topside thickness */
#define NEQUICKG_JRC_IONO_F2_THICKNESS_TOP_CONST_1 (150.0)
#define NEQUICKG_JRC_IONO_F2_THICKNESS_TOP_CONST_2 (100.0)
#define NEQUICKG_JRC_IONO_F2_THICKNESS_TOP_CONST_3 (0.041163)
#define NEQUICKG_JRC_IONO_F2_THICKNESS_TOP_CONST_4 (0.183981)
#define NEQUICKG_JRC_IONO_F2_THICKNESS_TOP_CONST_5 (1.424472)

#define NEQUICK_G_JRC_IONO_PEAK_AMPLITUDE_ITERATION_COUNT (5)

/** TBD: reference for value*/
#define NEQUICK_G_JRC_FREQ_TO_NE_FACTOR_D (0.124)

/** From critical frequency, calculates the associated electron density, using
 *  N[m-3] = 0.124 * f[MHz]^2
 *
 * @param The peak plasma frequency for the layer
 * @return The calculated electron density (in 10^11 m^-3)
 */
#define NEQUICK_G_JRC_IONO_GET_e_DENSITY(_crit_freq_MHz) \
  (NEQUICK_G_JRC_FREQ_TO_NE_FACTOR_D * _crit_freq_MHz * _crit_freq_MHz)

/** In 10^11 m^-3*/
#define NEQUICKG_IONO_LAYER_GET_PEAK_AMPLITUDE(_e_density) \
 (_e_density * 4.0)

/** Maximum exponent */
#define NEQUICKG_EXP_MAX_ABS (80.0)
/** Maximum value for exponential ie. exp( > 80) */
#define NEQUICKG_EXP_MAX_VALUE (5.5406e34)
/** Minimum value for exponential ie. exp( < -80) */
#define NEQUICKG_EXP_MIN_VALUE  (1.8049e-35)

#define IS_ODD(_i) ((_i % 2) == 1)

/** See F.2.4.1.
 *  In the pseudocode this correction offset is present
 *  But ESA, in its public version, do not use it
 *  and adds an explanation in the code.
 *  we follow the pseudo-code.
 */
#define NEQUICK_G_JRC_MODIP_GRID_LAT_OFFSET_CORRECTION (1.0e-6)

/* Size of longitude step in Modip grid. */
#define NEQUICK_G_JRC_MODIP_GRID_LONG_STEP_DEGREE (10)

/* Size of latitude step in Modip grid. */
#define NEQUICK_G_JRC_MODIP_GRID_LAT_STEP_DEGREE (5)

#define NEQUICK_G_JRC_MODIP_GRID_LONG_UNIQUE_COUNT \
  (360/NEQUICK_G_JRC_MODIP_GRID_LONG_STEP_DEGREE)

/** See F.2.4.1.
 *  In the pseudocode this correction offset is present
 *  But ESA, in its public version, do not use it
 *  and adds an explanation in the code.
 *  we follow the pseudo-code.
 */
#define NEQUICK_G_JRC_MODIP_GRID_LAT_OFFSET_CORRECTION (1.0e-6)

#define NEQUICKG_JRC_RAY_ZENITH_ANGLE_MAX_DEGREE (90.0)
#define NEQUICKG_JRC_RAY_IS_VERTICAL_PERIGEE_EPSILON_KM (0.1)
#define NEQUICKG_JRC_RAY_IS_AT_POLE_EPSILON (1.0e-10)

#define NEQUICK_G_JRC_SOLAR_MEAN_ANOMALY_DEGREE_PER_DAY (0.9856)
#define NEQUICK_G_JRC_SOLAR_MEAN_ANOMALY_OFFSET_DEGREE (-3.289)

#define NEQUICK_G_JRC_SOLAR_ECLIPTIC_ZERO_COEFF_DEGREE \
  (NEQUICKG_JRC_DEGREE_TO_RAD(282.634))
#define NEQUICK_G_JRC_SOLAR_ECLIPTIC_FIRST_COEFF_DEGREE \
  (NEQUICKG_JRC_DEGREE_TO_RAD(1.916))
#define NEQUICK_G_JRC_SOLAR_ECLIPTIC_SECOND_COEFF_DEGREE \
  (NEQUICKG_JRC_DEGREE_TO_RAD(0.02))

#define NEQUICK_G_JRC_SOLAR_SIN_EARTH_AXIAL_TILT (0.39782)

/** Zenith angle of sun at day night transition (degress). */
#define NEQUICK_G_JRC_SOLAR_ZENITH_ANGLE_AT_DAY_NIGHT_TRANSITION_DEGREE \
  (86.23292796211615)

#define NEQUICK_G_JRC_SOLAR_EFFECTIVE_ZENITH_CONST1 (90.0)
#define NEQUICK_G_JRC_SOLAR_EFFECTIVE_ZENITH_CONST2 (0.24)
#define NEQUICK_G_JRC_SOLAR_EFFECTIVE_ZENITH_CONST3 (20.0)
#define NEQUICK_G_JRC_SOLAR_EFFECTIVE_ZENITH_CONST4 (0.2)
#define NEQUICK_G_JRC_SOLAR_EFFECTIVE_ZENITH_CONST5 (12.0)

#define NEQUICK_G_IONO_COEFF_IS_ZERO(_coeff) (IS_NUMBER_CLOSE_TO_ZERO(_coeff, 1.0e-7))
#define NEQUICK_G_AZ_EQUALITY_EPSILON (1.0e-10)

/** 3.1. This default value represents the lowest Solar Flux value in average
 *  conditions that NeQuick is expected to operate on.
 *  In terms of the analytical expression relating 12-month running Sun
 *  Spot Number and Solar Flux, it corresponds to a Sun Spot Number of 0.
 *  This value is considered adequate when no other solution is available,
 *  while still being able to correct for a significant contribution of
 *  the ionospheric delay error.
 */
#define NEQUICK_G_AZ_DEFAULT_VALUE_SFU (ITU_R_P_371_8_LOWER_SOLAR_FLUX_IN_SFU)

/** 3.3 The operational range for the Effective Ionisation Parameter is between 0
 * and 400 sfu
 */
#define NEQUICK_G_AZ_MIN_VALUE_SFU (0.0)

/** 3.3 The operational range for the Effective Ionisation Parameter is between 0
 * and 400 sfu
 */
#define NEQUICK_G_AZ_MAX_VALUE_SFU (400.0)

#define NEQUICK_G_JRC_INTEGRATION_FIRST_POINT_KM (1000.0)
#define NEQUICK_G_JRC_INTEGRATION_SECOND_POINT_KM (2000.0)

#define NEQUICK_G_JRC_INTEGRATION_KRONROD_TOLERANCE_BELOW_FIRST_POINT (0.001)
#define NEQUICK_G_JRC_INTEGRATION_KRONROD_TOLERANCE_ABOVE_FIRST_POINT (0.01)

#define IS_SATELLITE_BELOW_FIRST_POINT(_p) \
  (_p->ray.satellite_position.height <= \
  NEQUICK_G_JRC_INTEGRATION_FIRST_POINT_KM)

#define IS_SATELLITE_BELOW_SECOND_POINT(_p) \
  (_p->ray.satellite_position.height <= \
  NEQUICK_G_JRC_INTEGRATION_SECOND_POINT_KM)

#define IS_RECEIVER_ABOVE_FIRST_POINT(_p) \
  (_p->ray.receiver_position.height >= \
   NEQUICK_G_JRC_INTEGRATION_FIRST_POINT_KM)

#define IS_RECEIVER_ABOVE_SECOND_POINT(_p) \
  (_p->ray.receiver_position.height >= \
   NEQUICK_G_JRC_INTEGRATION_SECOND_POINT_KM)

#define NEQUICK_G_JRC_RECURSION_LIMIT_MAX (50)

/* Average number of days in a month.*/
#define NEQUICK_G_JRC_TIME_AVG_MONTH_IN_DAYS (30.5)
/* Typical mid-month point in days. */
#define NEQUICK_G_JRC_TIME_MID_MONTH_POINT_IN_DAYS (15.0)
/* Number of hours in a day */
#define NEQUICK_G_JRC_TIME_DAY_IN_HOURS (24.0)

#define NEQUICK_G_JRC_TIME_CONSTANT_TO_COMPUTE_DAY (18.0)

#define NEQUICK_G_JRC_TIME_UTC_EPSILON (1.0e-20)

#define NEQUICK_G_JRC_TIME_HALF_DAY_IN_HOURS (12.0)

/* Number of degrees per hour, */
#define NEQUICK_G_JRC_TIME_DEGREE_PER_HOUR (15.0)

#define NEQUICK_G_JRC_MONTH_JANUARY 1
#define NEQUICK_G_JRC_MONTH_FEBRUARY 2
#define NEQUICK_G_JRC_MONTH_MARCH 3
#define NEQUICK_G_JRC_MONTH_APRIL 4
#define NEQUICK_G_JRC_MONTH_MAY 5
#define NEQUICK_G_JRC_MONTH_JUNE 6
#define NEQUICK_G_JRC_MONTH_JULY 7
#define NEQUICK_G_JRC_MONTH_AUGUST 8
#define NEQUICK_G_JRC_MONTH_SEPTEMBER 9
#define NEQUICK_G_JRC_MONTH_OCTOBER 10
#define NEQUICK_G_JRC_MONTH_NOVEMBER 11
#define NEQUICK_G_JRC_MONTH_DECEMBER 12

#define NEQUICK_G_TIME_MONTH_EQUAL(op1, op2) \
  (op1 == op2)

#define NEQUICK_G_POSITION_METERS_TO_KM(h)(h*1e-3)
#define NEQUICK_G_POSITION_KM_TO_METERS(h)(h*1e3)
#define NEQUICK_G_EARTH_RADIUS_IN_KM (6371.2)
#define NEQUICK_G_POSITION_HORIZONTAL_COORD_EPSILON (1.0e-5)

#define ITU_F2_LAYER_MAX_HARMONICS_CF2 ((ITU_F2_COEFF_MAX_ORDER - 1)/2)
#define ITU_F2_LAYER_MAX_HARMONICS_CM3 ((ITU_FM3_COEFF_MAX_ORDER - 1)/2)
#define ITU_F2_LAYER_MAX_HARMONICS_COEFF \
  (max_(ITU_F2_LAYER_MAX_HARMONICS_CF2, ITU_F2_LAYER_MAX_HARMONICS_CM3))

#define NEQUICK_EXCEPTION_NONE NEQUICK_OK
#define NEQUICK_MEMORY_EXPECTION -1
#define NEQUICK_INPUT_DATA_EXCEPTION -2
#define NEQUICK_MODIP_EXCEPTION -3
#define NEQUICK_E_EXCEPTION -4
#define NEQUICK_F2_EXCEPTION -5
#define NEQUICK_SOLAR_ACTIVITY_EXCEPTION -6
#define NEQUICK_RAY_EXCEPTION -7
#define NEQUICK_TEC_EXCEPTION -8
#define NEQUICK_USAGE_EXCEPTION -9
#ifdef FTR_UNIT_TEST
#define NEQUICK_UNIT_TEST_EXCEPTION -10
#endif
#define NEQUICK_FATAL_EXCEPTION -11

#define NEQUICK_NO_RESOURCES 1

#define NEQUICK_INPUT_DATA_FILE_REASON 1
#define NEQUICK_INPUT_DATA_BAD_COEFF 2
#define NEQUICK_INPUT_DATA_BAD_DATA 3
#define NEQUICK_INPUT_DATA_BAD_MONTH 4
#define NEQUICK_INPUT_DATA_BAD_UTC 5
#define NEQUICK_INPUT_DATA_BAD_LATITUDE 6

#define NEQUICK_MODIP_GRID_FILE_REASON 1
#define NEQUICK_MODIP_GRID_BAD_FILE_REASON 2

#define NEQUICK_E_BAD_MONTH 1

#define NEQUICK_F2_COEFF_BAD_MONTH 1
#define NEQUICK_F2_CCIR_FILE_REASON 2
#define NEQUICK_F2_INTERNAL 3

#define NEQUICK_SOLAR_ACTIVITY_BAD_COEFF 1

#define NEQUICK_RAY_BAD 1

#define NEQUICK_USAGE_BAD_FORMAT 1
#define NEQUICK_USAGE_BAD_COUNT 2

#define NEQUICK_HANDLE_NULL 1

#define NEQUICK_ERROR_LOG(error_type, error_detail, ...)

//lint -emacro(717, NEQUICK_ERROR_RETURN) while (0) intentional to force ';'
#define NEQUICK_ERROR_RETURN(error_type, error_detail, ...) \
do { \
  NEQUICK_ERROR_LOG(error_type, error_detail, __VA_ARGS__); \
  return (error_type); \
} while (false)

#define IS_NUMBER_CLOSE_TO(d1, d2, threshold) \
  (fabs(d1-d2) < threshold)

#define IS_NUMBER_CLOSE_TO_ZERO(d1, threshold) \
  (fabs(d1) < threshold)

/** NequickG JRC handle */
typedef void* NeQuickG_handle;

/** NequickG JRC constant handle */
typedef const void* const NeQuickG_chandle;

typedef struct thickness_st {
  double_t top_km;
  double_t bottom_km;
} thickness_t;

typedef struct peak_st {
  /** Amplitude for the Epstein function */
  double_t amplitude;
  /** Height of the electron density peak (km)*/
  double_t height_km;
  /** Thickness parameters */
  thickness_t thickness;
  double_t electron_density;
} peak_t;

typedef struct layer_st {
  double_t critical_frequency_MHz;
  peak_t peak;
} layer_t;

typedef struct NeQuickG_time_st {
  double_t utc;
  uint8_t month;
} NeQuickG_time_t;

/** AZ coefficients */
typedef struct AZ_coefficients_st {
  double_t a_sfu[NEQUICKG_AZ_COEFFICIENTS_COUNT];
} AZ_coefficients_t;

typedef struct solar_activity_st {
  AZ_coefficients_t effective_ionisation_level_coeff;
  double_t effective_ionisation_level_sfu;
  double_t effective_sun_spot_count;
} solar_activity_t;

typedef struct NeQuickG_angle_st {
  double_t degree;
  double_t rad;
  double_t sin;
  double_t cos;
} angle_t;

typedef struct NeQuickG_angle_restricted_st {
  double_t sin;
  double_t cos;
} angle_restricted_t;

/** WGS-84 ellipsoidal coordinates:
 * geodetic latitude
 * geodetic longitude
 * ellipsoidal height
 */
typedef struct NeQuickG_position_st {
  angle_t longitude;
  angle_t latitude;
  double_t height;
  uint8_t height_units;
  double_t radius_km;
  double_t longitude_org;
} position_t;

typedef struct bottom_side_st {
  double_t B_param;
  double_t exponential_arg;
  double_t s;
  bool is_exponential_arg_above_threshold;
} bottom_side_t;

typedef struct bottom_side_info_st {
  bottom_side_t F2;
  bottom_side_t F1;
  bottom_side_t E;
} bottom_side_info_t;

typedef struct NeQuickG_gauss_kronrod_context_st {
  double_t tolerance;
  size_t recursion_level;
  size_t recursion_max;
} gauss_kronrod_context_t;

typedef struct input_data_st {
  NeQuickG_time_t time;
  position_t station_position;
  position_t satellite_position;
} input_data_t;

typedef struct E_layer_st {
  angle_restricted_t solar_declination;
  layer_t layer;
  bool is_solar_declination_valid;
} E_layer_t;

typedef double_t F2_fourier_coefficient_array_t
  [ITU_F2_COEFF_MAX_DEGREE];

typedef double_t Fm3_fourier_coefficient_array_t
  [ITU_FM3_COEFF_MAX_DEGREE];

/** Interpolated/extrapolated coefficients for the foF2 and M(3000)F2. */
typedef struct F2_layer_interpolated_coefficients_st {
  F2_coefficient_array_t F2;
  Fm3_coefficient_array_t Fm3;
  double_t effective_sun_spot_count;
  bool valid;
} F2_layer_interpolated_coefficients_t;

typedef struct F2_fourier_coefficients_st {
  F2_fourier_coefficient_array_t CF2;
  Fm3_fourier_coefficient_array_t Cm3;
  bool valid;
} F2_fourier_coefficients_t;

typedef struct F2_layer_fourier_coeff_context_st {
  NeQuickG_time_t time;
  F2_layer_interpolated_coefficients_t interpolated;
  F2_fourier_coefficients_t fourier;
} F2_layer_fourier_coeff_context_t;

typedef struct F2_layer_st {
  F2_layer_fourier_coeff_context_t coef;
  layer_t layer;
  double_t trans_factor;
} F2_layer_t;

typedef struct iono_profile_st {
  E_layer_t E;
  layer_t F1;
  F2_layer_t F2;
} iono_profile_t;

typedef struct modip_context_st {
  double_t modip_degree;
} modip_context_t;

typedef struct grid_position_st {
  uint8_t index;
  double_t offset;
} grid_position_t;

typedef struct NeQuickG_ray_slant_info_st {
  angle_restricted_t azimuth;
  double_t perigee_radius_km;
  double_t receiver_distance_km;
  double_t satellite_distance_km;
} NeQuickG_ray_slant_info_t;

typedef struct NeQuickG_ray_context_st {
  position_t receiver_position;
  position_t satellite_position;
  angle_t longitude;
  angle_t latitude;
  bool is_vertical;
  NeQuickG_ray_slant_info_t slant;
} ray_context_t;

typedef struct NeQuickG_context_st {
  modip_context_t modip;
  solar_activity_t solar_activity;
  iono_profile_t profile;
  ray_context_t ray;
  input_data_t input_data;
} NeQuickG_context_t;

/** NequickG JRC API */
struct NeQuickG_library {
  /** NequickG JRC library initialization
   *
   * @param a file with the table grid of MODIP values
   *  versus geographical location provided together with the NeQuick G.
   *
   * @param directory where the coefficients for the foF2 and M(3000)F2 models
   * recommended by the Comit� Consultatif International des Radiocommunications (CCIR)
   * can be found.
   * These coefficients are the spherical harmonic coefficients representing the
   * development of monthly median foF2 and M(3000)F2 all over the world.
   * The coefficients correspond to low (R12 = 0) and high (R12 = 100) solar
   * activity conditions.
   * Each file ccirXX.asc contains 2858 values sequentially organized as follows:
   * {f2 1,1,1, f2 1,1,2, ..., f2 1,1,13,
   *  f2 1,2,1, f2 1,2,2, ..., f2 1,2,13,
   *  ...,
   *  f2 1,76,1, f2 1,76,2, ..., f2 1,76,13,
   *  f2 2,1,1, f2 2,1,2, ..., f2 2,1,13,
   *  f2 2,2,1, f2 2,2,2, ..., f2 2,2,13,
   *  ...,
   *  f2 2,76,1, f2 2,76,2, ..., f2 2,76,13,
   *
   *  fm3 1,1,1, fm3 1,1,2, ..., fm3 1,1,9,
   *  fm3 1,2,1, fm3 1,2,2, ..., fm3 1,2,9,
   *  ...,
   *  fm3 1,49,1, fm3 1,49,2, ..., fm3 1,49,9,
   *  fm3 2,1,1,  fm3 2,1,2, ..., fm3 2,1,9,
   *  fm3 2,2,1, fm3 2,2,2, ..., fm3 2,2,9,
   *  ...,
   *  fm3 2,49,1, fm3 2,49,2, ..., fm3 2,49,9}
   *
   * The coefficients of a ccirXX.asc file have to be stored in two 3-D arrays,
   *  F2 and Fm3,
   *
   * @return on success, a valid NequickG JRC handle
   *         on error, NEQUICKG_INVALID_HANDLE
   */
   int32_t (*init)(NeQuickG_handle* const pHandle);

  /** NequickG JRC library uninitialization
   *  Free resources allocated by init.
   *
   * @param NequickG JRC handle
   */
  void (*NeQuickG_close)(const NeQuickG_handle);

  /** Sets solar activity coefficients
   *  The three coefficients, ai0, ai1 and ai2 are transmitted to the users in
   *  the Galileo navigation broadcast message.
   *  They are used to calculate the Effective Ionisation Level (Az):
   *  an index that represents solar activity.
   *  The Az parameter is a continuous function
   *  of MODIP at the receiver location and Az is expressed by the three coefficients as
   *   Az = ai0 + ai1*MODIP + ai2*(MODIP)^2
   *  units used:
   *  ai0 : sfu, ai1 : sfu/degree and ai2 : sfu/deg^2
   *   sfu (solar flux unit) is not a SI unit but can be converted as:
   *   1 sfu = 10e-22 W/(m^2*Hz)
   *
   * @param NequickG JRC handle
   * @param array with the solar activity coefficients
   *         ai0 Effective Ionisation Level 1st order parameter
   *         ai1 Effective Ionisation Level 2nd order parameter
   *         ai2 Effective Ionisation Level 3rd order parameter
   *
   * return true on success, false otherwise
   */
  int32_t (*set_solar_activity_coefficients)(
    const NeQuickG_handle,
    const double_t* const,
    size_t);

  /** Sets time
   *
   * @param NequickG JRC handle
   * @param month, numerical value January = 1, ..., December = 12
   * @param UT time (hours) range accepted [0, 24]
   *
   * return true on success, false otherwise
   */
  int32_t (*set_time)(
    const NeQuickG_handle,
    const uint8_t month,
    const double_t UTC);

  /** Sets the receiver position using WGS-84 ellipsoidal coordinates
   *
   * @param NequickG JRC handle
   * @param Geodetic longitude from receiver (degrees)
   * @param Geodetic latitude from receiver (degrees) range accepted [-90, +90]
   * @param Geodetic height from receiver (m)
   *
   * return true on success, false otherwise
   */
  int32_t (*set_receiver_position)(
    const NeQuickG_handle,
    const double_t longitude_degree,
    const double_t latitude_degree,
    const double_t height_meters);

  /** Sets the satellite position using WGS-84 ellipsoidal coordinates
   *
   * @param NequickG JRC handle
   * @param Geodetic longitude from receiver (degrees)
   * @param Geodetic latitude from receiver (degrees) range accepted [-90, +90]
   * @param Geodetic height from receiver (m)
   *
   * return true on success, false otherwise
   */
  int32_t (*set_satellite_position)(
    const NeQuickG_handle,
    const double_t longitude_degree,
    const double_t latitude_degree,
    const double_t height_meters);

  /** Get the receiver MODIP
   * Needs a previous call to set_receiver_position.
   *
   * @param NequickG JRC handle
   *
   * return MODIP in degrees
   */
  double_t (*get_modip)(const NeQuickG_handle);

  /** Gets the Slant Total Electron Content in TECU
   *  1 TECU equals 10e16 electrons/m2
   *
   * @param NequickG JRC handle
   * @param total electron content
   *
   * return true on success, false otherwise
   */
  int32_t (*get_total_electron_content)(
    const NeQuickG_handle,
    double_t* const);
};

#define GLAB_TEC_VALUE_NOT_VALID (9999.)

double_t get_solar_mean_spot_number
  (double_t solar_12_month_running_mean_of_2800_MHZ_noise_flux);

double_t position_get_radius_km (
  const position_t* const p);

int32_t position_set(
  position_t* const p,
  double_t longitude_degree,
  double_t latitude_degree,
  double_t height, uint_fast8_t height_units);

void position_to_km(position_t* const p);

bool position_is_above(
  const position_t* const p1, const position_t* const p2);

bool position_is_exterior(const double_t height_km);

double_t get_radius_from_height(const double_t height_km);

double_t get_height_from_radius(const double_t radius_km);

void bottom_side_get_B_params(
  bottom_side_info_t* const pBottom_side_info,
  const iono_profile_t* const pProfile,
  const double_t height_km);

bool is_exponential_arg_above_threshold(double_t exponential_arg);

void bottom_side_get_exp_params(
  bottom_side_info_t* const pBottom_side_info,
  const iono_profile_t* const pProfile,
  const double_t height_km);

double_t get_s_param(
  const double_t peak_amplitude,
  const bottom_side_t* const pInfo);

double_t get_ds_param(const bottom_side_t* const pInfo);

void bottom_side_get_s_params(
  bottom_side_info_t* const pBottom_side_info,
  const iono_profile_t* const pProfile);

double_t bottom_side_low(
  const bottom_side_info_t* const pBottom_side_info,
  const double_t height_km);

double_t bottom_side_high(
  const bottom_side_info_t* const pBottom_side_info);

double_t bottom_side(
  const iono_profile_t* const pProfile,
  const double_t height_km);

double_t top_side(
  iono_profile_t* const pProfile,
  const double_t height_km);

double_t electron_density_get(
  iono_profile_t* const pProfile,
  const double_t height_km);

bool is_error_within_tolerance(
  const gauss_kronrod_context_t* const pContext,
  double_t K15_integration,
  double_t G7_integration);

int32_t Gauss_Kronrod_integrate(
  gauss_kronrod_context_t* const pContext,
  NeQuickG_context_t* const pNequick_Context,
  const double_t point_1_height_km,
  const double_t point_2_height_km,
  double_t* const pResult);

void angle_set(angle_t* const pAngle, double_t angle_degree);

void angle_set_rad(angle_t* const pAngle, double_t angle_rad);

void angle_set_fom_sin(angle_t* const pAngle);

void angle_set_fom_cos(angle_t* const pAngle);

void angle_restricted_set(
  angle_restricted_t* const pAngle, double_t rad);

void input_data_to_km(
  input_data_t* const pInputData);

double_t interpolation_third_order(
  const double_t interpol_points[NEQUICK_G_JRC_INTERPOLATE_POINT_COUNT],
  double_t offset);

double_t get_seasonal_parameter(
  const NeQuickG_time_t * const pTime);

double_t get_lat_parameter(
  const position_t * const pPosition,
  const NeQuickG_time_t * const pTime);

void E_layer_get_critical_freq_MHz(
  E_layer_t* const pLayer,
  const NeQuickG_time_t* const pTime,
  const solar_activity_t* const pSolar_activity,
  const position_t* const pPosition);

void E_layer_get_peak_height(E_layer_t* const pLayer);

void E_layer_get_peak_thickness(
  E_layer_t* const pE,
  const double_t F1_peak_thickness_bottom_km);

void E_layer_init(E_layer_t* const pE);

void F1_layer_get_critical_freq_MHz(
  layer_t* const pLayer,
  const double_t critical_freq_E_layer_MHz,
  const double_t critical_freq_F2_layer_MHz);

void F1_layer_get_peak_height(
  layer_t* const pLayer,
  const double_t E_peak_height_km,
  const double_t F2_peak_height_km);

void F1_layer_get_peak_thickness(
  layer_t* const pF1,
  const double_t E_peak_height_km,
  const double_t F2_peak_height_km);

void get_legrende_coeff_for_modip(
  const double_t modip_degree,
  double_t* const pCoeff);

void get_legrende_coeff_for_longitude(
  const angle_t* const pLongitude,
  double_t* const pCoeff_sinus,
  double_t* const pCoeff_cosinus);

double_t legendre_expansion(
  const double_t* const pFourier_coeff,
  const size_t* const pLegendre_degrees_per_order,
  size_t legendre_degrees_per_order_size,
  const double_t* const pModip_coeff,
  const double_t* const pLong_coeff_sinus,
  const double_t* const pLong_coeff_cosinus,
  double_t cos_lat);

double_t get_transmission_factor(
  const Fm3_fourier_coefficient_array_t Cm3,
  const double_t* const pModip_coeff,
  const double_t* const pLong_coeff_sinus,
  const double_t* const pLong_coeff_cosinus,
  double_t cos_lat);

int32_t F2_layer_init(
  F2_layer_t* const pLayer);

int32_t F2_layer_get_critical_freq_MHz(
  F2_layer_t * const pF2,
  const NeQuickG_time_t* const pTime,
  const modip_context_t* const pModip,
  const solar_activity_t* const pSolar_activity,
  const position_t * const pCurrent_position);

double_t get_E_Term_for_peak_height(
  const double_t critical_freq_F2_layer_MHz,
  const double_t critical_freq_E_layer_MHz);

void F2_layer_get_peak_height(
  F2_layer_t* const pF2,
  const double_t critical_freq_E_layer_MHz);

void F2_layer_get_peak_thickness(F2_layer_t* const pF2);

void F2_layer_get_peak_amplitude(F2_layer_t* const pF2);

double_t F2_layer_get_shape_factor(
  const F2_layer_t* const pF2,
  const NeQuickG_time_t* const pTime,
  const solar_activity_t* const pSolar_activity);

void F2_layer_exosphere_adjust(
  F2_layer_t* const pF2,
  const NeQuickG_time_t* const pTime,
  const solar_activity_t* const pSolar_activity);

int32_t iono_profile_init(iono_profile_t * const pProfile);

double_t iono_profile_get_amplitude_of_peak(
  const peak_t* const pPeak,
  double_t height_km);

int32_t iono_profile_get_critical_freqs(
  iono_profile_t * const pProfile,
  const NeQuickG_time_t* const pTime,
  const modip_context_t* const pModip,
  const solar_activity_t* const pSolar_activity,
  const position_t * const pCurrent_position);

void iono_profile_get_peak_heights(
  iono_profile_t * const pProfile);

void iono_profile_get_peak_thicknesses(
  iono_profile_t * const pProfile);

double_t iono_profile_get_peak_amp_substracting_layer(
  const peak_t * const pPeak,
  const peak_t * const pOther_layer_peak);

void iono_profile_get_peak_amplitudes(
  iono_profile_t * const pProfile);

void iono_profile_get_peaks(iono_profile_t * const pProfile);

void iono_profile_get_exosphere_contribution(
  iono_profile_t * const pProfile,
  const NeQuickG_time_t* const pTime,
  const solar_activity_t* const pSolar_activity);

int32_t iono_profile_get(
  iono_profile_t * const pProfile,
  const NeQuickG_time_t* const pTime,
  modip_context_t* const pModip,
  const solar_activity_t* const pSolar_activity,
  const position_t * const pCurrent_position);

double_t NeQuickG_exp(double_t power);

double_t NeQuickG_func_join(
  double_t func1,
  double_t func2,
  double_t alpha,
  double_t x);

void NeQuickG_get_power_array(
  size_t grade,
  double_t first_term,
  double_t negligible_value,
  double_t* const p);

double_t NeQuickG_square(double_t val);

double_t get_cos_from_sin(const double_t sin_rad);

double_t get_sin_from_cos(const double_t cos_rad);

bool handle_special_lat_cases(
  modip_context_t* const pContext,
  const position_t* const pPosition);

void modip_get(
  modip_context_t* const pContext,
  const position_t* const pPosition);

void grid_long_fix_index(
  grid_position_t * const pGrid_position, int8_t index);

void grid_get_long_position(
  double_t longitude_degree,
  grid_position_t * const pGrid_position);

void grid_get_lat_position(
  double_t latitude_degree,
  grid_position_t * const pGrid_position);

double_t grid_get_lon_interpol_point(
  const grid_position_t* const pLatitude,
  uint_fast8_t longitude_grid_index);

double_t grid_2D_interpolation(
  grid_position_t* pLongitude,
  const grid_position_t* const pLatitude);

void modip_grid_interpolate(
  const position_t* const pPosition,
  double_t *pModip_degree);

angle_restricted_t get_longitude_delta_angle(
  const position_t* const pStation_position,
  const position_t* const pSatellite_position);

angle_restricted_t get_delta_angle(
  const position_t* const pStation_position,
  const position_t* const pSatellite_position,
  const angle_restricted_t* const pLongitude_delta);

angle_restricted_t get_sigma_angle(
  const position_t* const pStation_position,
  const position_t* const pSatellite_position,
  const angle_restricted_t* const pLongitude_delta,
  const angle_restricted_t* const pDelta);

angle_t get_zenith_angle(
  const position_t* const pStation_position,
  const position_t* const pSatellite_position,
  const angle_restricted_t* const pDelta);

angle_restricted_t get_delta_p_angle(const angle_t* const pZenith);

angle_t get_ray_latitude(
  const position_t* const pStation_position,
  const angle_restricted_t* const pSigma,
  const angle_restricted_t* const pDelta_p);

angle_t get_ray_longitude(
  const position_t* const pStation_position,
  const angle_restricted_t* const pSigma,
  const angle_restricted_t* const pDelta_p,
  const angle_t* const pRay_latitude);

int32_t ray_get_radius(
  ray_context_t* const pRay,
  const position_t* const pStation_position,
  const angle_t* const pZenith_angle);

bool is_at_poles(const ray_context_t* const pRay);

void get_azimuth(ray_context_t* const pRay);

void on_vertical_ray(ray_context_t* const pRay);

int32_t on_slant_ray(ray_context_t* const pRay);

double_t get_slant_distance(
  const ray_context_t* const pRay,
  double_t radius_km);

int32_t ray_get(
  ray_context_t* const pRay,
  const position_t * const pStation_position,
  const position_t * const pSatellite_position);

angle_restricted_t ray_get_delta_angle(
  const ray_context_t* const pRay,
  const double_t height_km);

angle_t get_lambda_s_p_angle(
  const ray_context_t* const pRay,
  const angle_restricted_t* pDelta,
  const angle_t* pCurrent_position_latitude);

position_t get_current_position(
  const ray_context_t* const pRay,
  const double_t height_km);

int32_t ray_slant_get_electron_density(
  NeQuickG_context_t* const pContext,
  const double_t height_km,
  double_t* const pElectron_density);

position_t ray_vertical_get_current_position(const ray_context_t* const pRay);

int32_t ray_vertical_get_profile(NeQuickG_context_t* const pContext);

double_t ray_vertical_get_electron_density(
  NeQuickG_context_t* const pContext,
  const double_t height_km);

double_t get_mean_anomaly(
  double_t time_days);

double_t get_ecliptic_longitude(
  double_t time_days);

angle_restricted_t
solar_get_declination(const NeQuickG_time_t * const pTime);

double_t get_cosinus_hour_angle(
  const NeQuickG_time_t * const pTime,
  const position_t* const pPosition);

angle_t solar_get_zenith_angle(
  const position_t* const pPosition,
  const NeQuickG_time_t* const pTime,
  const angle_restricted_t* const pSolar_declination);

double_t solar_get_effective_zenith_angle(
  const position_t* const pPosition,
  const NeQuickG_time_t * const pTime,
  const angle_restricted_t* const pSolar_declination);

double_t solar_get_longitude(
  const NeQuickG_time_t* const pTime);

bool are_valid(const AZ_coefficients_t* const pCoeff);

void check_boundaries(double_t* const pAz);

double_t Az_calc(
  const AZ_coefficients_t* const pCoeff,
  double_t modip);

double_t solar_activity_get_effective_ionisation_level_in_sfu(
  const AZ_coefficients_t* const pCoeff,
  double_t modip);

bool solar_activity_is_effective_ionisation_level_equal(
  double_t op1,
  double_t op2);

int32_t solar_activity_coefficients_set (
  solar_activity_t* const pContext,
  const double_t * const pCoeff,
  size_t coeff_count);

void solar_activity_get(
  solar_activity_t* const pContext,
  double_t modip_degree);

int32_t Gauss_Kronrod_integrate_impl(
  gauss_kronrod_context_t* const pContext,
  NeQuickG_context_t* const pNequick_Context,
  const double_t point_1_height_km,
  const double_t point_2_height_km,
  double_t* const pTEC);

int32_t both_below_first_integration_point(
  NeQuickG_context_t* const pContext,
  double_t* const pTEC);

int32_t between_integration_points(
  NeQuickG_context_t* const pContext,
  double_t* const pTEC);

int32_t path_crosses_first_integration_point(
  NeQuickG_context_t* const pContext,
  double_t* const pTEC);

int32_t path_crosses_second_integration_point(
  NeQuickG_context_t* const pContext,
  double_t* const pTEC);

int32_t both_above_second_integration_point(
  NeQuickG_context_t* const pContext,
  double_t* const pTEC);

int32_t path_crosses_both_integration_points(
  NeQuickG_context_t* const pContext,
  double_t* const pTEC);

int32_t NeQuickG_integrate(
  NeQuickG_context_t* const pContext,
  double_t* const pTEC);

void NeQuickG_time_init(
  NeQuickG_time_t * const pTime);

int32_t NeQuickG_time_set(
  NeQuickG_time_t * const pTime,
  const uint_fast8_t month,
  const double_t utc);

bool NeQuickG_time_utc_is_equal(
  double_t op1,
  double_t op2);

double_t NeQuickG_time_get_day_of_year(
  const NeQuickG_time_t * const pTime);

double_t NeQuickG_time_get_local(
  const NeQuickG_time_t * const pTime,
  double_t longitude_degree);

/** Compute the Effective Sunspot Number Azr as a function of the
 *  Effective Ionisation Level Az.
 *
 * @param Az_in_sfu Effective Ionisation Level Az in sfu
 *
 * @return Effective Sunspot Number Azr
 *
 */
#define NeQuickG_Az_solar_activity_get_sun_spot_effective_count(Az_in_sfu) \
    get_solar_mean_spot_number(Az_in_sfu)

double_t get_point_height(
  const NeQuickG_context_t* const pContext,
  double_t height_km);

double_t get_point_zero_height(
  const NeQuickG_context_t* const pContext);

void get_modip_impl(
  NeQuickG_context_t* const pContext);

double_t get_modip_interface(NeQuickG_handle handle);

void get_solar_activity(NeQuickG_context_t* const pContext);

int32_t check_handle(NeQuickG_chandle handle);

int32_t init(NeQuickG_handle* const pHandle);

void NeQuickG_close(NeQuickG_handle handle);

int32_t set_solar_activity_coefficients(
  const NeQuickG_handle handle,
  const double_t * const pCoeff, size_t coeff_count);

int32_t get_total_electron_content_impl2(
  const NeQuickG_handle handle,
  double_t* const pTotal_electron_content);

int32_t set_time(
  const NeQuickG_handle handle,
  const uint8_t month,
  const double_t UTC);

int32_t set_station_position(
  const NeQuickG_handle handle,
  const double_t longitude_degree,
  const double_t latitude_degree,
  const double_t height_meters);

int32_t set_satellite_position(
  const NeQuickG_handle handle,
  const double_t longitude_degree,
  const double_t latitude_degree,
  const double_t height_meters);

int32_t CCIR_get_ionosonde_F2(
  uint_fast8_t month,
  F2_coefficient_array_t** pF2);

int32_t CCIR_get_ionosonde_Fm3(
  uint_fast8_t month,
  Fm3_coefficient_array_t** pFm3);

int32_t F2_layer_fourier_coefficients_init(
  F2_layer_fourier_coeff_context_t* const pContext);

int32_t set_parameters(
  F2_layer_fourier_coeff_context_t* const pContext,
  const NeQuickG_time_t* const pTime,
  const double_t Azr);

int32_t interpolate_F2(
  F2_layer_fourier_coeff_context_t* const pContext);

int32_t interpolate_Fm3(
  F2_layer_fourier_coeff_context_t* const pContext);
  
int32_t F2_layer_fourier_coefficients_interpolate(
  F2_layer_fourier_coeff_context_t* const pContext,
  const NeQuickG_time_t * const pTime,
  const double_t Azr);
  
void get_harmonics(
  const NeQuickG_time_t * const pTime,
  double_t * const pSin,
  double_t * const pCos);
  
void get_fourier_coefficients_CF2(
  const F2_layer_fourier_coeff_context_t* const pContext,
  const double_t * const pSin,
  const double_t * const pCos,
  F2_fourier_coefficient_array_t CF2);
  
void get_fourier_coefficients_Cm3(
  const F2_layer_fourier_coeff_context_t* const pContext,
  const double_t * const pSin,
  const double_t * const pCos,
  Fm3_fourier_coefficient_array_t Cm3);
  
void F2_layer_fourier_coefficients_get_impl(
  F2_layer_fourier_coeff_context_t* const pContext);
  
int32_t F2_layer_fourier_coefficients_get(
  F2_layer_fourier_coeff_context_t* const pContext,
  const NeQuickG_time_t * const pTime,
  const solar_activity_t* const pSolar_activity);


// NeQuick-G JRC. Implementation end
#endif /*MODEL_H_*/

