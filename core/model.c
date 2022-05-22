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
 * File: model.c
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
 * Change Log: Enhanced parsing of antenna in ANTEX file, it is now able to 
 *                  separate the name from the dome
 *             Inertial/non-inertial velocity switch included
 * -------------
 *          gLAB v1.4.0
 * Release: 2010/06/21
 * Change Log: Changed the way rotation during signal flight time is done, it
 *                  is now possible to set/unset this rotation, and the reception/
 *                  transmission time separately
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
 * Change Log: Improved DCB Management. 
 * -------------
 *          gLAB v1.4.4
 * Release: 2010/09/22
 * Change Log: Included new DCB management.
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
 *             Added functions for Galileo troposphere model.
 *             Modified Klobuchar model function.
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
 * Change Log: Fixed iono sigma not being converted to meters.
 * 	       Corrected bug in troposphericCorrectionMOPS function where seconds of day where added twice.
 * -----------
 *          gLAB v2.2.5
 * Release: 2015/10/20
 * Change Log: Fixed iono sigma not being added to the total sigma weight.
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
 * Change Log: Fixed computation of Galileo elevation and azimuth.
 * -----------
 *          gLAB v3.0.0
 * Release: 2016/09/05 
 * Change Log: Added SBAS processing.
 *             Concatenated RINEX and SP3 files can be read now.
 *             Added computation of Galileo, Beidou and GEO satellite coordinates from broadcast files.
 * -----------
 *          gLAB v3.1.0
 * Release: 2016/09/26
 * Change Log: When computing SBAS model, if we are in PA, receiver position is set to 'calculate', 
 *               SBAS iono is not available and solution has not converged, Klobuchar model will
 *               be used until the solution has converged (it can disabled with '--model:initcoordnpa').
 *             GLONASS coordinates and velocity from broadcast products are set now to 0, as they cannot be computed.
 * -----------
 *          gLAB v3.1.1
 * Release: 2016/10/21
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v4.0.0
 * Release: 2017/03/03
 * Change Log: Added DGNSS processing.
 *             Added function NEU2XYZ.
 *             Added check for maximum data gap when using precise orbits and clocks.
 *             Added option to use the last sample from previous day or the first sample from the current day when
 *               both samples were repeated in concatenated files.
 *             Orbit and clock interpolation now skip correctly samples with invalid values.
 *             Fixed bugs when computing orbits and clocks with concatened SP3 files.
 *             Modified getPositionBRDC and getVelocityBRDC parameters to prepare them for GLONASS coordinate computation.
 *             When searching for antenna type in getReceiverType function, now it is not case sensitive.
 *             When doing standalone navigation using SBAS ionosphere, the ionosphere sigma will be used if 'useSigmaIono' is enabled.
 *             Switching back to previous GEO in SBAS mode will not be done if previous GEO is still in data adquisition time.
 *             In SBAS mode, now by default gLAB will try to keep the current GEO, unless '-model:maintaingeo' option is disabled.
 *             Improved and fixed several bugs in SwitchSBASGEOMode function.
 *             Modified TGDCorrection in order to unselect a satellite when there is no DCB available (independently if DCB is
 *               read from broadcast RINEX navigation file, a IONEX file or a F-PPP file) when using precise orbits.
 * -----------
 *          gLAB v4.1.0
 * Release: 2017/04/07
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v4.2.0
 * Release: 2017/05/22
 * Change Log:   SBAS processing now supports disabling message type 10 in PA mode.
 *               If SBAS iono is used but SBAS processing is not enabled, gLAB will allow to use Klobuchar during
 *                 the solution convergence if the receiver position is set to 'calculate', 'calculateRINEX' or
 *                 'calculateUSER'.
 *               Changed behaviour of SBAS processing when 4 conescutive messages were incorrect. Instead of
 *                 setting all satellites to "Do not use", now it will only change the current GEO to "Do not
 *                 use" only for ranging purposes.
 *               Fixed a bug handling SBAS alarm messages when two GEO are under alarm. This made
 *                 sometimes to discard satellites due to an alarm message even if the alarm was
 *                 from GEO not in use.
 *               Fixed bug that made to print "Ephemerides unavailable" in the SATSEL message when the condition
 *                 to unselect a satellite was met before reaching the function where ephemerides were checked.
 * -----------
 *          gLAB v5.0.0
 * Release: 2017/06/30
 * Change Log:   Improved GEO switching when there are many SBAS GEO available. Now gLAB will skip all previously used
 *                 SBAS GEOs when doing multiple switches in the same epoch (for example, when doing SBAS availability 
 *                 maps with several SBAS providers).
 *               Fixed bug that made not to unselect GPS satellites when data from mixed GEOs was used and
 *                 alarms from more than one GEO had been received.
 *               Fixed bug that prevented from changing GEO when an alarm was received and data from multiple
 *                 GEOs were used.
 *               Fixed incorrect GEO PRN number printed in INFO message stating that the GEO had changed when
 *                 the initial GEO was the one with mixed data.
 * -----------
 *          gLAB v5.1.0
 * Release: 2017/11/24
 * Change Log:   Added functions for 'XYZ2Spherical' and 'Spherical2XYZ' for coordinate conversion.
 *               Taken out broadcast message age check in DGNSS. This made sometimes to incorrectly
 *                 discard navigation messages (and therefore, the satellite).
 *               If GEO switching is enabled, gLAB will make a GEO switch if the current GEO
 *                 has 4 consecutive messages missing or 4 consecutive wrong messages (in both
 *                 PA and NPA modes).
 *               During a GEO switch, gLAB will not switch to a GEO which has 4 or more
 *                 consecutive messages missing.
 *               In NPA mode, if half of the satellites do not have fast or slow corrections,
 *                 gLAB will try to switch GEO if GEO switching is enabled.
 *               When gLAB switches back to previous GEO (option '-model:geofallback' enabled),
 *                 the INFO message showing the change of GEO will be printed after the 
 *                 OUTPUT or SBASOUT message, instead of before, to avoid user confusion.
 *               Fixed infinite loop when minimum switch time for SBAS was set to 0.
 *               Fixed incorrect computation of BeiDou satellite coordinates and clocks with
 *                 broadcast products.
 * -----------
 *          gLAB v5.1.1
 * Release: 2017/12/22
 * Change Log:   In DGNSS mode, receiver ARP correction was disabled independently of user options. If user now
 *                 enables this option, reference station ARP will be read from reference RINEX or RTCM file and
 *                 corrected, and rover ARP will be read from rover RINEX or user input (depending on user options).
 * -----------
 *          gLAB v5.1.2
 * Release: 2018/01/12
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.1.3
 * Release: 2018/01/19
 * Change Log:   Fixed applying wrong ARP correction in reference station in DGNSS mode.
 * -----------
 *          gLAB v5.2.0
 * Release: 2018/03/09
 * Change Log:   Added option for discarding satellites under an UDREI threshold.
 *               Added option to set the user defined sigma for each satellite and measurement.
 *               Added functions to compute the several weight modes added in gLAB.
 *               Fixed bug that made gLAB use incorrect data from IONEX file when the IONEX file did not
 *                 start at 0h and the time interval was not 0.
 * -----------
 *          gLAB v5.3.0
 * Release: 2018/06/08
 * Change Log:   Fixed bug in computation of RRC corrections under alarm conditions that made 
 *                 RRC corrections always timeout under alarm conditions.
 * -----------
 *          gLAB v5.4.0
 * Release: 2018/11/16
 * Change Log:   Modified 'getPositionSP3' and 'getClockSP3' functions for making them work with the new
 *                 internal format of saving SP3 data.
 *               Removed GEO selection and GEO alarm check from function 'computeSBAS' to avoid race
 *                 conditions in multithreading. This checks are now done in functions 'SBASGEOselection'
 *                 and 'SBASGEOAlarmCheck' (defined in 'dataHandling.c' file), which are called in 'gLAB.c'
 *                 file after the SBAS data is read. This fixes weird unavailability areas (such as a thin
 *                 horizontal line in SBAS maps with multithreading and more than two GEOs with alarm.
 *               Fixed bug that made to never select a GEO satellite when GEO satellite selection was set
 *                 the one with highest elevation and mixed GEO data was not enabled. This bug only
 *                 occured in version 5.3.0.
 * -----------
 *          gLAB v5.4.1
 * Release: 2019/02/15
 * Change Log:   Fixed windUp correction computation being accumulated more than once when the modelling
 *                 process was computed more than once in a single epoch (for instance, when the a
 *                 priori coordinates have to converge). This error barely had impact on the solution,
 *                 as in kinematic PPP the error was at the centimeter level, and in static PPP the
 *                 error was absorved by the ambiguities.
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
 * Change Log:   Fixed memory leak when computing IONEX ionosphere corrections.
 *               Fixed memory leak when computing F-PPP ionosphere corrections.
 * -----------
 *          gLAB v5.5.0
 * Release: 2020/11/13
 * Change Log:   Added NeQuick code from JRC.
 *               Fixed crash when there were available a full set of SBAS corrections during modelling phase 
 *                 for a GEO and the GEO was not unselected.
 * -----------
 *          gLAB v5.5.1
 * Release: 2020/12/11
 * Change Log: No changes in this file.
 * -----------
 *       END_RELEASE_HISTORY
 *****************************/

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/* External classes */
#include "model.h"
#if defined _OPENMP
	#include <omp.h>
#endif

// NeQuick-G JRC. Implementation begin

static const struct NeQuickG_library NeQuickG = {
  //lint -e{123} macro with arguments is intended
  .init = init,
  .NeQuickG_close = NeQuickG_close,
  .set_solar_activity_coefficients = set_solar_activity_coefficients,
  .set_time = set_time,
  .set_receiver_position = set_station_position,
  .set_satellite_position = set_satellite_position,
  .get_modip = get_modip_interface,
  .get_total_electron_content = get_total_electron_content_impl2,
};

// NeQuick-G JRC. Implementation end

/**************************************
 * Declarations of internal operations
 **************************************/
 
 /*****************************************************************************
 * Name        : getSatelliteOrientationACR
 * Description : Obtains the 3 vectors determining the reference frame of a GNSS 
 *               satellite in the reference system:
 *                  Z axis => Radial: Pointing to the opposite direction of Earth
 *                  X axis => Along-track: Perpendicular to Z in the plane 
 *                            Velocity-Satellite-Earth (similar to velocity)
 *                  Y axis => Cross-track: Completing the system
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *position               I  m    Satellite position
 * double  *velocity               I  m    Satellite velocity
 * double  orientation[3][3]       O  N/A  Vectors determining the attitude of 
 *                                         the satellite
 *****************************************************************************/
void getSatelliteOrientationACR (double *position, double *velocity, double orientation[3][3]) {
	double		posUni[3],velUni[3];
	int			i;
	
	memcpy(posUni,position,sizeof(double)*3);
	unitary(posUni);
	memcpy(velUni,velocity,sizeof(double)*3);
	unitary(velUni);
	
	for (i=0;i<3;i++)
		orientation[2][i] = posUni[i];

	vectProd(posUni,velUni,orientation[1]);
	vectProd(orientation[1],orientation[2],orientation[0]);
	
	unitary(orientation[0]);
	unitary(orientation[1]);
}
 
/*****************************************************************************
 * Name        : getSatelliteOrientation
 * Description : Obtains the 3 vectors determining the attitude of a GNSS satellite.
 *                  Z axis => Nadir (pointing to Earth)
 *                  X axis => Perpendicular to Z in the plane Sun-Satellite-Earh
 *                  Y axis => Completing the system (along the solar panel)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * double  *position               I  m    Satellite position
 * double  orientation[3][3]       O  N/A  Vectors determining the attitude of 
 *                                         the satellite
 *****************************************************************************/
void getSatelliteOrientation (TTime *t, double *position, double orientation[3][3]) {
	double		sunPos[3],relSunPos[3];
	double		posUni[3];
	int			i;
	
	findSun(t,sunPos);
	relSunPos[0] = sunPos[0] - position[0];
	relSunPos[1] = sunPos[1] - position[1];
	relSunPos[2] = sunPos[2] - position[2]; 
	unitary(relSunPos);
			
	memcpy(posUni,position,sizeof(double)*3);
	unitary(posUni);
	
	for (i=0;i<3;i++)
		orientation[2][i] = -posUni[i];

	vectProd(orientation[2],relSunPos,orientation[1]);
	vectProd(orientation[1],orientation[2],orientation[0]);
	
	unitary(orientation[0]);
	unitary(orientation[1]);
}

/*****************************************************************************
 * Name        : fillSatelliteOrientation
 * Description : Obtains the 3 vectors determining the attitude of a GNSS 
 *               satellite and fills it to TEpoch class. 
 *                  Z axis => Nadir (pointing to Earth)
 *                  X axis => Perpendicular to Z in the plane Sun-Satellite-Earh
 *                  Y axis => Completing the system (along the solar panel)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 * int  satIndex                   I  N/A  Index of the satellite
 *****************************************************************************/
void fillSatelliteOrientation (TEpoch *epoch, int satIndex) {
	double	orientation[3][3];
	
	getSatelliteOrientation (&epoch->t, epoch->sat[satIndex].position, orientation);
	
	memcpy(epoch->sat[satIndex].orientation,orientation,sizeof(double)*3*3);
}

/*****************************************************************************
 * Name        : fillGroundStationNEU
 * Description : Fills in a TEpoch structure the NEU of a station from its 
 *               XYZ position.
 *                  Z axis => Zenith (Up)  [m]
 *                  X axis => North                            - Latitude  [rad]
 *                  Y axis => Completing the system (East)     - Longitude [rad]
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 *****************************************************************************/
void fillGroundStationNEU (TEpoch *epoch) {
	XYZ2NEU(epoch->receiver.aproxPosition,epoch->receiver.aproxPositionNEU);
}

/*****************************************************************************
 * Name        : getGroundStationOrientation
 * Description : Obtains the 3 vectors determining the attitude of fixed ground
 *               station.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *positionNEU            I  N/A  Position of the station in NEU
 * double  orientation[3][3]       O  N/A  Vectors containing the attitude of
 *                                         the station
 *                                         0=>X(N)    1=>Y(E)    2=>Z(U) 
 *****************************************************************************/
void getGroundStationOrientation (double *positionNEU, double orientation[3][3]) {
	// Local coordinate frame
	
	// North
	orientation[0][0] = -sin(positionNEU[0])*cos(positionNEU[1]);
	orientation[0][1] = -sin(positionNEU[0])*sin(positionNEU[1]);
	orientation[0][2] =  cos(positionNEU[0]);
	
	// East
	orientation[1][0] = -sin(positionNEU[1]);
	orientation[1][1] =  cos(positionNEU[1]);
	orientation[1][2] =  0;
	
	// Up (Zenith)
	orientation[2][0] =  cos(positionNEU[0])*cos(positionNEU[1]);
	orientation[2][1] =  cos(positionNEU[0])*sin(positionNEU[1]);
	orientation[2][2] =  sin(positionNEU[0]);
}

/*****************************************************************************
 * Name        : fillGroundStationOrientation
 * Description : Fills the orientation of a station from its NEU position
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 *****************************************************************************/
void fillGroundStationOrientation (TEpoch *epoch) {
	getGroundStationOrientation(epoch->receiver.aproxPositionNEU, epoch->receiver.orientation);
}

/*****************************************************************************
 * Name        : getAzimuthElevation
 * Description : Get the azimuth/elevation in relation to WGS84 between a 
 *               pair satellite-receiver
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  orientation[3][3]       I  N/A  Orientation of the receiver
 * double  *receiverPosition       I  N/A  Position of the receiver
 * double  *satellitePosition      I  N/A  Position of the satellite
 * double  *azimuth                O  rad  Azimuth
 * double  *elevation              O  rad  Elevation
 *****************************************************************************/
void getAzimuthElevation (double orientation[3][3], double *receiverPosition, double *satellitePosition, double *azimuth, double *elevation) {
	int			i;
	double		relativeLoS[3];
	double		distance;
	
	distance = 0;

	for (i=0;i<3;i++) {
		distance += (satellitePosition[i]-receiverPosition[i])*(satellitePosition[i]-receiverPosition[i]);
	}
	
	distance = sqrt(distance);
	for (i=0;i<3;i++) {
		relativeLoS[i] = ((satellitePosition[0]-receiverPosition[0])*orientation[i][0] + 	
						  (satellitePosition[1]-receiverPosition[1])*orientation[i][1] + 	
						  (satellitePosition[2]-receiverPosition[2])*orientation[i][2]) / distance;
	}
	
	*azimuth = atan2(relativeLoS[1],relativeLoS[0]);
	
	//if (*azimuth!=0) {
//		*elevation = atan2(relativeLoS[1]/sin(*azimuth),relativeLoS[2]);
//	} else {
//		*elevation = asin(relativeLoS[0]);
//	}
	
//	*elevation = Pi/2-*elevation;
	*elevation = asin(relativeLoS[2]);
}

/*****************************************************************************
 * Name        : fillAzimuthElevation
 * Description : Fill the azimuth/elevation in relation to WGS84 between a 
 *               pair satellite-receiver
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 * int  satIndex                   I  N/A  Index of the satellite
 *****************************************************************************/
void fillAzimuthElevation (TEpoch *epoch, int satIndex) {
	getAzimuthElevation(epoch->receiver.orientation, epoch->receiver.aproxPosition, epoch->sat[satIndex].position, &epoch->sat[satIndex].azimuth, &epoch->sat[satIndex].elevation);
}

/*****************************************************************************
 * Name        : rotate
 * Description : Rotates a 3D vector an specified angle in an axis
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *v                      IO N/A  Vector to rotate. Result overwrittes
 *                                         this vector
 * double  angle                   I  rad  Angle to rotate
 * int  axis                       I  N/A  Rotation axis (1->x  2->y  3->z)
 *****************************************************************************/
void rotate (double *v, double angle, int axis) {
	double		vRes[3];
	
	if (axis==1) {
		vRes[0] =  v[0];
		vRes[1] =  v[1]*cos(angle) + v[2]*sin(angle);
		vRes[2] = -v[1]*sin(angle) + v[2]*cos(angle);
	} else if (axis==2) {
		vRes[0] =  v[0]*cos(angle) - v[2]*sin(angle);
		vRes[1] =  v[1];
		vRes[2] =  v[0]*sin(angle) + v[2]*cos(angle);
	} else if (axis==3) {
		vRes[0] =  v[0]*cos(angle) + v[1]*sin(angle);
		vRes[1] = -v[0]*sin(angle) + v[1]*cos(angle);
		vRes[2] =  v[2];
	}
	
	memcpy(v,vRes,sizeof(double)*3);
}

/*****************************************************************************
 * Name        : fillTransmissionTimeSat
 * Description : Obtains the transmission time for a specific satellite
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * int  ind                        I  N/A  Index position of the satellite in 
 *                                         the epoch struct
 * TSBAScorr *SBAScorr             I  N/A  Struct with the SBAS corrections to be applied
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Properly done
 *                                         0 => Not found
 *****************************************************************************/
int fillTransmissionTimeSat (TEpoch *epoch, TGNSSproducts *products, int ind, TSBAScorr *SBAScorr, TOptions *options) {
	TTime	t;
	double	satCorrection;
	int		res;
	double	meas;
	
	t.SoD = 0;
	t.MJDN = 0;

	if ( options->satelliteClockCorrection ) {
		if (options->SBAScorrections==1 && options->onlySBASiono==0 && epoch->sat[ind].GNSS==GEO) {
			satCorrection = SBAScorr->Clock;
			res = 1;
		} else {
			res = getSatellitePVT(products,&epoch->t,0.0,epoch->sat[ind].GNSS,epoch->sat[ind].PRN,NULL,NULL,NULL,&satCorrection,SBAScorr->IOD,options);
			satCorrection -= SBAScorr->ClockCor;
		}
	} else {
		res = 1;
		satCorrection = 0;
	}
	if (res!=0) {
		meas = getMeasurementValue(epoch,epoch->sat[ind].GNSS,epoch->sat[ind].PRN,C1C);
		// If C1P (P1) is not available, try to get C1C (C1)
		if (meas==-1) meas = getMeasurementValue(epoch,epoch->sat[ind].GNSS,epoch->sat[ind].PRN,C1P);
		if (meas!=-1) {
			t = tdadd(&epoch->t, (-meas-satCorrection)/c0);
			memcpy(&epoch->sat[ind].transTime,&t,sizeof(TTime));
		} else {
			//Mark satellite as no code measurements available
			epoch->sat[ind].hasC1C=0;
		}
	} else {
		epoch->sat[ind].hasOrbitsAndClocks = 0;
	}
	if (res==0 || meas==-1) return 0;

	else return 1;
}

/*****************************************************************************
 * Name        : fillTransmissionTime
 * Description : Obtains the transmission time for all satellites
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * TSBAScorr *SBAScorr             I  N/A  Struct with the SBAS corrections to be applied
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void fillTransmissionTime (TEpoch *epoch, TGNSSproducts* products, TSBAScorr *SBAScorr, TOptions *options) {
	int		i;
	
	for (i=0;i<epoch->numSatellites;i++) {
		fillTransmissionTimeSat(epoch,products,i,SBAScorr,options);
	}
}

/*****************************************************************************
 * Name        : computeFlightTime
 * Description : Computes the signal flight time from the GNSS satellite to 
 *               the receiver
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * int  satIndex                   I  N/A  Index of the satellite
 * TSBAScorr *SBAScorr             O  N/A  Struct with the SBAS corrections to be applied
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (double)         O  s    Signal flight time
 *****************************************************************************/
double computeFlightTime (TEpoch *epoch, TGNSSproducts *products, int satIndex, TSBAScorr *SBAScorr, TOptions *options) {
	double	position[3];
	int		res;
	double	dist;
	
	if(options->SBAScorrections==1 && options->onlySBASiono==0 && epoch->sat[satIndex].GNSS==GEO) {
		position[0]=SBAScorr->SatCoord[0];
		position[1]=SBAScorr->SatCoord[1];
		position[2]=SBAScorr->SatCoord[2];

	} else {
		res = getSatellitePVT(products,&epoch->sat[satIndex].transTime,0.0,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,position,NULL,NULL,NULL,SBAScorr->IOD,options);
		if (res==0) return 0;
	}

	position[0]=position[0]+SBAScorr->SatCoordCor[0];
	position[1]=position[1]+SBAScorr->SatCoordCor[1];
	position[2]=position[2]+SBAScorr->SatCoordCor[2];
	
	dist = sqrt((position[0]-epoch->receiver.aproxPosition[0])*(position[0]-epoch->receiver.aproxPosition[0]) +
				(position[1]-epoch->receiver.aproxPosition[1])*(position[1]-epoch->receiver.aproxPosition[1]) +
				(position[2]-epoch->receiver.aproxPosition[2])*(position[2]-epoch->receiver.aproxPosition[2]));
	return dist/c0;
}

/*****************************************************************************
 * Name        : correctEarthRotation
 * Description : Corrects the Earth rotation of a satellite position.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *x                      IO N/A  3 dimension vector (overwritten)
 * double  flightTime              I  N/A  Flight time of the signal (difference 
 *                                         between the reception time and transmission 
 *                                         time).
 *****************************************************************************/
void correctEarthRotation (double *x, double flightTime) {
	double angle;
	
	angle = EARTH_ROTATION * flightTime;
	rotate(x,angle,3);
}

/*****************************************************************************
 * Name        : nsteffensen
 * Description : Method to accelerate the Newton-Rapson convergence for
 *               equations like:  p=g(p)    (==> E=M+e*sin(E))
 *               It is required:  g'(p)<>1  (==> p simple root)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  Mk                      I  N/A  Mean Anomaly
 * double  e                       I  N/A  Excentricity
 * Returned value (double)         O  N/A  Excentric anomaly
 *****************************************************************************/
double nsteffensen (double Mk, double e) {
	const double	tol=1e-14;
	
	double			p,p0,p1,p2;
	double			dd;
	
	Mk = atan2(sin(Mk),cos(Mk));
	p = Mk;
	
	while(1) {
		p0 = p;
		p1 = Mk + e*sin(p0);
		p2 = Mk + e*sin(p1);
		
		dd = fabs(p2-2*p1+p0);
		if (dd<tol) break;
		p = p0-(p1-p0)*(p1-p0)/(p2-2*p1+p0);
		if (fabs(p-p0)<=tol) break;
	}
	
	return p;

}

/*****************************************************************************
 * Name        : satellitePhaseCenterCorrection3D
 * Description : Get the satellite phase center correction 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * GNSSystem  GNSS                 I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN identifier of the satellite
 * MeasurementType meas            I  N/A  Measurement type
 * double  orientation[3][3]       I  N/A  Satellite orientation
 * TConstellation  *constellation  I  N/A  TConstellation structure where 
 *                                         satellite data is stored
 * double  *dr                     O  m    3D phase center correction
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Phase center correction found
 *                                         0 => Satellite not found on TConstellation
 *****************************************************************************/
int satellitePhaseCenterCorrection3D (TTime *t, enum GNSSystem GNSS, int PRN, enum MeasurementType meas, double orientation[3][3], TConstellation *constellation, double *dr) {
	TConstellationElement	*el;
	int						ind;
	int						i;
	
	el = getConstellationElement(GNSS,PRN,t,constellation);
	ind = getFrequencyInt(meas);
	
	if (el!=NULL) {
		for (i=0;i<3;i++) {
			dr[i] = orientation[2][i]*el->PCO[ind][2] + orientation[1][i]*el->PCO[ind][1] + orientation[0][i]*el->PCO[ind][0];
		}
		return 1;
	}
	dr[0] = dr[1] = dr[2] = 0;
	return 0;
}

/*****************************************************************************
 * Name        : satellitePhaseCenterCorrection
 * Description : Get the satellite phase center correction 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * GNSSystem  GNSS                 I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN identifier of the satellite
 * MeasurementType meas            I  N/A  Measurement type
 * double  orientation[3][3]       I  N/A  Satellite orientation
 * double  *LoS                    I  N/A  Line of Sight satellite-receiver
 * TConstellation  *constellation  I  N/A  TConstellation structure where 
 *                                         satellite data is stored
 * double  *pc                     O  m    Phase center correction
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Phase center corrected
 *                                         0 => Satellite not found on TConstellation
 *****************************************************************************/
int satellitePhaseCenterCorrection (TTime *t, enum GNSSystem GNSS, int PRN, enum MeasurementType meas, double orientation[3][3], double *LoS, TConstellation *constellation, double *pc) {
	double					dr[3];
	
	if (satellitePhaseCenterCorrection3D(t,GNSS,PRN,meas,orientation,constellation,dr)==1) {
		*pc = scalarProd(LoS,dr);
		return 1;

	}
	*pc = 0;
	return 0;
}

/*****************************************************************************
 * Name        : satellitePhaseCenterVarCorrection
 * Description : Get the zenital satellite phase center correction 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * GNSSystem  GNSS                 I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN identifier of the satellite
 * MeasurementType meas            I  N/A  Measurement type
 * double  satearthcenterdistance  I  N/A  Distance of satellite to Earth centre
 * double  elevation               I  N/A  Elevation of the satellite in relation to the station (radians)
 * TConstellation  *constellation  I  N/A  TConstellation structure where 
 *                                         satellite data is stored
 * double  *zc                     O  m    Zenital phase center correction
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Zenital phase center corrected
 *                                         0 => Satellite not found on TConstellation
 *****************************************************************************/
int satellitePhaseCenterVarCorrection (TTime *t, enum GNSSystem GNSS, int PRN, enum MeasurementType meas, double satearthcenterdistance, double elevation, TConstellation *constellation, double *pvc) {

	TConstellationElement	*el;
	int			ind;
	int			pos;
	double			diff;
	double			nadir;
	
	el = getConstellationElement(GNSS,PRN,t,constellation);
	ind = getFrequencyInt(meas);


	if (el!=NULL) {

		//Only Non azimuth corrections implemented!!

		//Calculate nadir angle
		nadir=asin((EARTH_RADIUS/satearthcenterdistance)*cos(elevation));

			//Check if angle is above the maximum zenital angle in the ANTEX file (some antennas the data goes from 0 to 80º)
			if(nadir*r2d>el->zen2) {
			*pvc=0;
			return 0;
		}
			ind = getFrequencyInt(meas);
			pos=(int)((nadir*r2d-el->zen1)/el->dzen);

			//Check for the cases that are in the extreme
			if(pos==el->nzen-1) {
			*pvc=el->noazi[GNSS][ind][pos];
			return 1;
		}

			//Interpolate values
			diff=((nadir*r2d-el->zen1)/el->dzen)-pos;

			*pvc=el->noazi[GNSS][ind][pos]*(1-diff)+el->noazi[GNSS][ind][pos+1]*diff;

		return 1;

	}

	*pvc=0;
	return 0;
}

/*****************************************************************************
 * Name        : getClockBRDC
 * Description : Get the clock correction of the satellite from specified 
 *               ephemeris block
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TBRDCblock  *block              I  N/A  TBRDCblock structure
 * TTime  *t                       I  N/A  Reference time
 * Returned value (double)         O  s    Clock correction
 *                                         999999.999999 => Clock not available
 *****************************************************************************/
double getClockBRDC (TBRDCblock *block,TTime *t) {
	double diff;
	
	diff = tdiff(t,&block->Ttoc);
	return (block->clockbias + block->clockdrift*diff + block->clockdriftrate*diff*diff)*c0;
}

/*****************************************************************************
 * Name        : getPositionBRDC
 * Description : Get the position of the satellite from specified ephemeris block
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TBRDCproducts *products         I  N/A  Ephemerides products
 * TBRDCblock  *block              I  N/A  TBRDCblock structure
 * TTime  *t                       I  N/A  Reference time
 * enum GNSSystem  GNSS            I  N/A  GNSS enumerator of the satellite
 * double  *position               O  m    3D vector with the satellite position
 *****************************************************************************/
void getPositionBRDC (TBRDCproducts *products, TBRDCblock *block,TTime *t, enum GNSSystem GNSS, double *position) {
	//Constants for GPS
	const double	mu = 3.986005e+14;  // WGS-84 Earth Universal Gravitational parameter (m3/s2)
	const double	om_e = 7.2921151467e-5;  // WGS-84 Earth rotation rate (rad/s)
	
	//Constants for BeiDou
	const double    muB = 3.986004418e+14;  // CGCS2000 Earth Universal Gravitational parameter (m3/s2)   // GEO Orbit coordinate calculation
	const double	om_eB = 7.2921150e-5;  // CGCS2000 Earth rotation rate (rad/s)

	//Constants for Galileo
	const double	muGal = 3.986004418e+14;  // WGS-84 Earth Universal Gravitational parameter (m3/s2)


	double 			diff;
	double			Mk;			// Mean anomaly
	double			Ek;			// Excentric anomaly
	double			fk;			// True anomaly
	double			uk;			// Argument of latitude
	double			rk;			// Radial distance
	double			ik;			// Inclination
	double			xp, yp;
	double			OMk;		// Longitude of ascending node
	double			alpha, beta;
	double			X, Y, Z;
	
	diff = tdiff(t, &block->Ttoe);

	switch(GNSS) {
		case GEO:
			position[0] = block->satposX + block->satvelX * diff + 0.5 * block->sataccX * diff * diff;
			position[1] = block->satposY + block->satvelY * diff + 0.5 * block->sataccY * diff * diff;
			position[2] = block->satposZ + block->satvelZ * diff + 0.5 * block->sataccZ * diff * diff;
			return;
			break;
		case BDS:
			//BeiDou coordinates
			//diff-=14; //BeiDou time is 14 seconds ahead of GPS time
			Mk = block->M0 + (sqrt(muB)/(block->sqrta*block->sqrta*block->sqrta)+block->deltan)*diff; 
			OMk = block->OMEGA + (block->OMEGADOT-om_eB)*diff - om_eB*block->toe;
			break;
		case Galileo:	// True anomaly fk:
			//Galileo time is synchronized with GPS time in RINEX files!!!
			Mk = block->M0 + (sqrt(muGal)/(block->sqrta*block->sqrta*block->sqrta)+block->deltan)*diff; 
			OMk = block->OMEGA + (block->OMEGADOT-om_e)*diff - om_e*block->toe;
			break;
		case GLONASS:
			position[0] = 0.;
			position[1] = 0.;
			position[2] = 0.;
			return;
			break;
		default:	//GPS
			// True anomaly fk:
			Mk = block->M0 + (sqrt(mu)/(block->sqrta*block->sqrta*block->sqrta)+block->deltan)*diff; 
			OMk = block->OMEGA + (block->OMEGADOT-om_e)*diff - om_e*block->toe;
			break;
	}


	Ek = nsteffensen(Mk,block->e);
	if ( Ek < 0 ) Ek += 2 * Pi;
	if ( Ek > 2 * Pi ) Ek -= 2 * Pi;
	fk = atan2(sqrt(1-block->e*block->e)*sin(Ek),cos(Ek)-block->e);
	if ( fk < 0 ) fk += 2 * Pi;
	if ( fk > 2 * Pi ) fk -= 2 * Pi;
	
	// Arg. of Latitude uk,radius rk, inclination ik:
	uk = block->omega + fk + block->cuc*cos(2*(block->omega+fk)) + block->cus*sin(2*(block->omega+fk));
	rk = (block->sqrta*block->sqrta)*(1.0-block->e*cos(Ek)) + block->crc*cos(2.0*(block->omega+fk)) + block->crs*sin(2.0*(block->omega+fk));
	ik = block->i0 + block->IDOT*diff + block->cic*cos(2*(block->omega+fk)) + block->cis*sin(2*(block->omega+fk));
	
	// Positions in orbital plane
	xp = rk * cos(uk);
	yp = rk * sin(uk);
	
	if ( GNSS == BDS && block->PRN <= 5 ) {
	// if(block->sqrta>sqrt(40000000) && (-10*Pi/180)<block->i0 &&  block->i0<10*Pi/180){
		//Satellite is a BeiDou GEO (BeiDou GEO are from PRN 1 to 5)
		OMk = block->OMEGA + block->OMEGADOT*diff - om_eB * block->toe; 
		X = xp*cos(OMk) - yp*cos(ik)*sin(OMk);
		Y = xp*sin(OMk) + yp*cos(ik)*cos(OMk);
		Z = yp*sin(ik);
		alpha = -5 * Pi / 180;
		beta = om_eB * diff;
			
		position[0] = X * cos(beta) + Y * sin(beta) * cos(alpha) + Z * sin(beta) * sin(alpha);
		position[1] = X * (-sin(beta)) + Y * cos(beta) * cos(alpha) + Z * cos(beta) * sin(alpha);
		position[2] = Y * (-sin(alpha)) + Z * cos(alpha);
	} else {
		// CT-System coordinates
		position[0] = xp * cos(OMk) - yp * cos(ik) * sin(OMk);
		position[1] = xp * sin(OMk) + yp * cos(ik) * cos(OMk);
		position[2] = yp * sin(ik);
	}
}

/*****************************************************************************
 * Name        : getVelocityBRDC
 * Description : Get the velocity of the satellite from specified ephemeris block
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TBRDCproducts *products         I  N/A  Ephemerides products
 * TBRDCblock  *block              I  N/A  TBRDCblock structure
 * TTime  *t                       I  N/A  Reference time
 * double  *position               I  N/A  Satellite position (3D vector) at time t.
 *                                         It is used to avoid for optimisation
 *                                         purposes, to avoid recomputing it when
 *                                         obtaining satellite PVT. If this parameter
 *                                         is NULL, the position at t is computed.
 * double  *velocity               O  m/s  3D vector with the satellite velocity
 * enum SatelliteVelocity  sv      I  N/A  Chooses if svINERTIAL or svITRF velocity
 *                                         is computed 
 * enum GNSSystem  GNSS            I  N/A  GNSS enumerator of the satellite
 *****************************************************************************/
void getVelocityBRDC (TBRDCproducts *products, TBRDCblock *block, TTime *t, double *position, double *velocity, enum SatelliteVelocity satVel, enum GNSSystem GNSS) {
	const double	diffTime = 0.001;
	double			pos[3],posPrev[3];
	TTime			tPrev;
	int				i;
	
	// Position at t
	if ( position == NULL ) {
		getPositionBRDC(products,block,t,GNSS,pos);
	} else {
		memcpy(pos, position, sizeof(double) * 3);
	}
	
	// Position at t-diffTime
	memcpy(&tPrev, t, sizeof(TTime));
	tPrev.SoD -= diffTime;
	getPositionBRDC(products,block,&tPrev,GNSS,posPrev);
	
	// Earth rotation in diffTime
	if ( satVel == svINERTIAL ) {
		correctEarthRotation(posPrev, diffTime);
	}

	// Estimate velocity
	for ( i = 0; i < 3; i++ ) velocity[i] = (pos[i] - posPrev[i]) / diffTime;
}

/*****************************************************************************
 * Name        : getClockSP3
 * Description : Obtain the satellite clock correction for a specified 
 *               satellite in a given time from a specified SP3 structure
 *               By default does not use any kind of interpolation due to the
 *               stochastic nature of the clocks, but TOptions structure has a 
 *               field (clockInterpolationDegree) to allow doing an interpolation
 *               with a specified degree.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * TTime  *t                       I  N/A  Reference time
 * GNSSystem  GNSS                 I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN identifier of the satellite
 * TOptions  *options              I  N/A  TOptions structure to configure behaviour
 * Returned value (double)         O  s    Clock for time t and satellite PRN
 *****************************************************************************/
double getClockSP3 (TGNSSproducts *products, TTime *t, enum GNSSystem GNSS, int PRN, TOptions *options) {
	int				i, k=-1;
	int				ind;
	double			tInitDistance,tEndDistance;
	int				prevSample;
	int				pointsBelow = 0;
	int				pointsAbove=0;
	int				halfDeg;
	int				nearestSample;
	int				currentPos;
	int				FirstSampleNonMaxDistance=-1;
	const int		numSamples=options->clockInterpolationDegree+1;
	double			clk[2*(MAX_INTERPOLATION_DEGREE+1)];
	TTime			tPrev[2*(MAX_INTERPOLATION_DEGREE+1)];
	int				numblocs;
	int				startSample,samplesRemaining;
	TSP3clockblock	 *ClockFull;
	
	if (products->SP3->clocks.numblocsValidConcat[GNSS][PRN]<(options->clockInterpolationDegree+1)) {
		//Not enough samples for interpolation (or for no interpolation, there must be at least 1 sample)
		return INVALID_CLOCK;
	}

	tInitDistance=tdiff(t,&products->SP3->clocks.startTimeConcat);
	if (tInitDistance<-MAXEXTRAPOLATIONTIME) return INVALID_CLOCK; //Clocks are ahead of current time

	tEndDistance=tdiff(t,&products->SP3->clocks.endTimeConcat);
	if (tEndDistance>MAXEXTRAPOLATIONTIME) return INVALID_CLOCK; //Clocks are behind of current time

	ind=products->SP3->clocks.index[GNSS][PRN];
	ClockFull=products->SP3->clocks.Concatblock[ind];

	halfDeg = numSamples/2;
	//midSample = options->clockInterpolationDegree+1;
	numblocs=products->SP3->clocks.numblocsConcat[GNSS][PRN];

	if (options->clockInterpolationDegree==0) { // No clock interpolation (for the case of reference files)
		//Get the sample closest to the current time
		nearestSample=(int)(round(tInitDistance/products->SP3->clocks.intervalConcat));
		if (nearestSample<0) {
			//For the case for extrapolation back in time
			nearestSample=0; 
		} else if (nearestSample>=products->SP3->clocks.numblocsConcat[GNSS][PRN]) {
			//For the case for extrapolation forward in time
			nearestSample=products->SP3->clocks.numblocsConcat[GNSS][PRN]-1;
		}
		if (ClockFull[nearestSample].validSample==0) return INVALID_CLOCK; //Not a valid sample
		if (fabs(tdiff(&ClockFull[nearestSample].t,t))>MAX_CLOCK_DISTANCE) return INVALID_CLOCK; //too far to be used
		return ClockFull[nearestSample].clock;
	} else { //Clock interpolation
		//Get the closest sample previous to the current epoch
		nearestSample=(int)(tInitDistance/products->SP3->clocks.intervalConcat +.00005); //Add .00005 to avoid problems with decimals
		if (nearestSample<0) {
			//For the case for extrapolation back in time
			nearestSample=0; 
		} else if (nearestSample>=products->SP3->clocks.numblocsConcat[GNSS][PRN]) {
			//For the case for extrapolation forward in time
			nearestSample=products->SP3->clocks.numblocsConcat[GNSS][PRN]-1;
		} else if (ClockFull[nearestSample].validSample==1) {
			if (fabs(tdiff(t,&ClockFull[nearestSample].t))<1E-4) {
				//Epoch matches with a sample. No need to interpolate
				return ClockFull[nearestSample].clock;
			}
		}


		//Get the previous samples (the same number as clockInterpolationDegree, in case in the future there are no samples available)
		if(options->ClocksMaxDistance>0.) {
			//Check for data holes
			prevSample=nearestSample;
			//Look for samples before and in the current epoch (as we need to check if the closest sample is not empty)
			for(i=nearestSample;i>=0 && pointsBelow<=options->clockInterpolationDegree;i--) {
				if (ClockFull[i].validSample==0) continue; //Sample not valid
				if(tdiff(&ClockFull[prevSample].t,&ClockFull[i].t)>options->ClocksMaxDistance) {
					//Too much distance between clocks samples. Save the first position where this occurs, for the case we have to use it
					if (FirstSampleNonMaxDistance==-1) { 
						FirstSampleNonMaxDistance=numSamples-pointsBelow;
					}
				}
				if (k==-1) {
					if(prevSample==nearestSample) k=i;
				}
				currentPos=numSamples-pointsBelow;
				//Copy time and values of the samples to be used
				memcpy(&tPrev[currentPos],&ClockFull[i].t,sizeof(TTime));
				clk[currentPos]=ClockFull[i].clock;
				pointsBelow++;
				prevSample=i;
			}
			//if (ClockFull[prevSample].validSample==0) return INVALID_CLOCK; //The closes sample to the current epoch is not valid. No data for current day
			if (pointsBelow>halfDeg) {
				//More than half of the samples available. Check for the upper half samples
				samplesRemaining=halfDeg;
			} else {
				//Less than half of the samples available. Check for the upper half saamples nd the additional upper ones to cover for the ones missing below 
				samplesRemaining=numSamples-pointsBelow;
			}
			if(k==-1) {
				//The nearest sample is invalid and no valid samples found before the nearest sample
				 return INVALID_CLOCK;
			} else {
				prevSample=k;
			}
			//Look for samples after the current epoch
			for(i=nearestSample+1;i<numblocs && samplesRemaining>pointsAbove;i++) {
				if (ClockFull[i].validSample==0) continue; //Sample not valid
				if(tdiff(&ClockFull[i].t,&ClockFull[prevSample].t)>options->ClocksMaxDistance) return INVALID_CLOCK; //Too much distance between clocks
				currentPos=numSamples+1+pointsAbove;
				//Copy time and values of the samples to be used
				memcpy(&tPrev[currentPos],&ClockFull[i].t,sizeof(TTime));
				clk[currentPos]=ClockFull[i].clock;
				pointsAbove++;
				prevSample=i;
			}


			if ((pointsAbove+pointsBelow)<numSamples) return INVALID_CLOCK; //Not enough samples available

			startSample=numSamples-(options->clockInterpolationDegree-pointsAbove);


			if (startSample<=FirstSampleNonMaxDistance) return INVALID_CLOCK; //One of the samples is over the maximum time between samples
		} else {
			prevSample=nearestSample;
			//Look for samples before and in the current epoch (as we need to check if the closest sample is not empty)
			for(i=nearestSample;i>=0 && pointsBelow<=options->clockInterpolationDegree;i--) {
				if (ClockFull[i].validSample==0) continue; //Sample not valid
				if (k==-1) {
					if(prevSample==nearestSample) k=i;
				}
				currentPos=numSamples-pointsBelow;
				//Copy time and values of the samples to be used
				memcpy(&tPrev[currentPos],&ClockFull[i].t,sizeof(TTime));
				clk[currentPos]=ClockFull[i].clock;
				pointsBelow++;
				prevSample=i;
			}
			if (ClockFull[prevSample].validSample==0) return INVALID_CLOCK; //The closes sample to the current epoch is not valid. No data for current day
			if (pointsBelow>halfDeg) {
				//More than half of the samples available. Check for the upper half samples
				samplesRemaining=halfDeg;
			} else {
				//Less than half of the samples available. Check for the upper half saamples nd the additional upper ones to cover for the ones missing below 
				samplesRemaining=numSamples-pointsBelow;
			}
			if(k==-1) {
				//The nearest sample is invalid and no valid samples found before the nearest sample
				 return INVALID_CLOCK;
			} else {
				prevSample=k;
			}
			//Look for samples after the current epoch
			for(i=nearestSample+1;i<numblocs && samplesRemaining>pointsAbove;i++) {
				if (ClockFull[i].validSample==0) continue; //Sample not valid
				currentPos=numSamples+1+pointsAbove;
				//Copy time and values of the samples to be used
				memcpy(&tPrev[currentPos],&ClockFull[i].t,sizeof(TTime));
				clk[currentPos]=ClockFull[i].clock;
				pointsAbove++;
				prevSample=i;
			}

			if ((pointsAbove+pointsBelow)<numSamples) return INVALID_CLOCK; //Not enough samples available

			startSample=numSamples-(options->clockInterpolationDegree-pointsAbove);
		}

		if(options->ClocksToTMaxDistance>0.) {
			//Check that we do not go over the threshold of maximum number of data gaps
			if(tdiff(&tPrev[startSample+options->clockInterpolationDegree],&tPrev[startSample]) > options->ClocksToTMaxDistance) return INVALID_CLOCK;
		}

		if (pointsAbove==0) {
			//If no upper samples are found check that they are not too far for extrapolation
			if (tdiff(t,&tPrev[startSample+options->clockInterpolationDegree])>MAX_CLOCK_DISTANCE) return INVALID_CLOCK; 
		}

		return lagrangeInterpolation(options->clockInterpolationDegree,*t,&tPrev[startSample],&clk[startSample]);
		
	}

	return INVALID_CLOCK;  // This is the invalid data flag of SP3 files
	
}

/*****************************************************************************
 * Name        : getPositionSP3
 * Description : Obtain the satellite position estimation for a specified 
 *               satellite in a given time from a specified SP3 structure.
 *               By default uses a 9 degree interpolator (5 points before the epoch 
 *               and 5 points after). The TOptions structure has a field
 *               (orbitInterpolationDegree) to allow changing the degree.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * TTime  *t                       I  N/A  Reference time
 * GNSSystem  GNSS                 I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN identifier of the satellite
 * double  *position               O  m    3D vector with the satellite position
 * TOptions  *options              I  N/A  TOptions structure to configure behaviour
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Position computed
 *                                         0 => Error in the position computation
 *****************************************************************************/
int getPositionSP3 (TGNSSproducts *products,TTime *t,enum GNSSystem GNSS,int PRN,double *position,TOptions *options) {
	int				ind;
	int				i,k=-1;
	double			tInitDistance,tEndDistance;
	int				pointsBelow = 0;
	int				prevSample;
	int				pointsAbove=0;
	int				nearestSample;
	int				currentPos;
	int				FirstSampleNonMaxDistance=-1;
	const int		numSamples=options->orbitInterpolationDegree+1;
	double			pos[3][2*(MAX_INTERPOLATION_DEGREE+1)];
	TTime			tPrev[2*(MAX_INTERPOLATION_DEGREE+1)];
	int				halfDeg;
	int				numblocs;
	int				startSample,samplesRemaining;
	TSP3orbitblock	*OrbitFull;

	if (products->SP3->orbits.numblocsValidConcat[GNSS][PRN]<(options->orbitInterpolationDegree+1)) {
		//Not enough samples for interpolation (or for no interpolation, there must be at least 1 sample)
		return 0;
	}

	tInitDistance=tdiff(t,&products->SP3->orbits.startTimeConcat);
	if (tInitDistance<-MAXEXTRAPOLATIONTIME) return 0; //Orbits are ahead of current time

	tEndDistance=tdiff(t,&products->SP3->orbits.endTimeConcat);
	if (tEndDistance>MAXEXTRAPOLATIONTIME) return 0; //Orbits are behind of current time

	ind=products->SP3->orbits.index[GNSS][PRN];
	OrbitFull=products->SP3->orbits.Concatblock[ind];

	halfDeg = numSamples/2;
	//midSample = options->orbitInterpolationDegree+1;
	numblocs=products->SP3->orbits.numblocsConcat[GNSS][PRN];

	if (options->orbitInterpolationDegree==0) { // No orbit interpolation (for the case of reference files)
		//Get the sample closest to the current time
		nearestSample=(int)(round(tInitDistance/products->SP3->orbits.intervalConcat));
		if (nearestSample<0) {
			//For the case for extrapolation back in time
			nearestSample=0; 
		} else if (nearestSample>=products->SP3->orbits.numblocsConcat[GNSS][PRN]) {
			//For the case for extrapolation forward in time
			nearestSample=products->SP3->orbits.numblocsConcat[GNSS][PRN]-1;
		}
		if (OrbitFull[nearestSample].validSample==0) return 0; //Not a valid sample
		if (fabs(tdiff(&OrbitFull[nearestSample].t,t))>MAXEXTRAPOLATIONTIME) return 0; //too far to be used
		position[0]=OrbitFull[nearestSample].x[0];
		position[1]=OrbitFull[nearestSample].x[1];
		position[2]=OrbitFull[nearestSample].x[2];
		return 1;
	} else { //Orbit interpolation
		//Get the closest sample previous to the current epoch
		nearestSample=(int)(tInitDistance/products->SP3->orbits.intervalConcat +.00005); //Add .00005 to avoid problems with decimals
		if (nearestSample<0) {
			//For the case for extrapolation back in time
			nearestSample=0; 
		} else if (nearestSample>=products->SP3->orbits.numblocsConcat[GNSS][PRN]) {
			//For the case for extrapolation forward in time
			nearestSample=products->SP3->orbits.numblocsConcat[GNSS][PRN]-1;
		} else if (OrbitFull[nearestSample].validSample==1) {
			if (fabs(tdiff(t,&OrbitFull[nearestSample].t))<1E-4) {
				//Epoch matches with a sample. No need to interpolate
				position[0]=OrbitFull[nearestSample].x[0];
				position[1]=OrbitFull[nearestSample].x[1];
				position[2]=OrbitFull[nearestSample].x[2];
				return 1;
			}
		}

		//Get the previous samples (the same number as orbitInterpolationDegree, in case in the future there are no samples available)
		if(options->OrbitsMaxDistance>0.) {
			//Check for data holes
			prevSample=nearestSample;
			//Look for samples before and in the current epoch (as we need to check if the closest sample is not empty)
			for(i=nearestSample;i>=0 && pointsBelow<=options->orbitInterpolationDegree;i--) {
				if (OrbitFull[i].validSample==0) continue; //Sample not valid
				if(tdiff(&OrbitFull[prevSample].t,&OrbitFull[i].t)>options->OrbitsMaxDistance) {
					//Too much distance between orbit samples. Save the first position where this occurs, for the case we have to use it
					if (FirstSampleNonMaxDistance==-1) { 
						FirstSampleNonMaxDistance=numSamples-pointsBelow;
					}
				}
				if (k==-1) {
					if(prevSample==nearestSample) k=i;
				}
				currentPos=numSamples-pointsBelow;
				//Copy time and values of the samples to be used
				memcpy(&tPrev[currentPos],&OrbitFull[i].t,sizeof(TTime));
				pos[0][currentPos]=OrbitFull[i].x[0];
				pos[1][currentPos]=OrbitFull[i].x[1];
				pos[2][currentPos]=OrbitFull[i].x[2];
				pointsBelow++;
				prevSample=i;
			}
			if (OrbitFull[prevSample].validSample==0) return 0; //The closes sample to the current epoch is not valid. No data for current day
			if (pointsBelow>halfDeg) {
				//More than half of the samples available. Check for the upper half samples
				samplesRemaining=halfDeg;
			} else {
				//Less than half of the samples available. Check for the upper half saamples nd the additional upper ones to cover for the ones missing below 
				samplesRemaining=numSamples-pointsBelow;
			}
			if(k==-1) {
				//The nearest sample is invalid and no valid samples found before the nearest sample
				 return 0;
			} else {
				prevSample=k;
			}
			//Look for samples after the current epoch
			for(i=nearestSample+1;i<numblocs && samplesRemaining>pointsAbove;i++) {
				if (OrbitFull[i].validSample==0) continue; //Sample not valid
				if(tdiff(&OrbitFull[i].t,&OrbitFull[prevSample].t)>options->OrbitsMaxDistance) return 0; //Too much distance between orbits
				currentPos=numSamples+1+pointsAbove;
				//Copy time and values of the samples to be used
				memcpy(&tPrev[currentPos],&OrbitFull[i].t,sizeof(TTime));
				pos[0][currentPos]=OrbitFull[i].x[0];
				pos[1][currentPos]=OrbitFull[i].x[1];
				pos[2][currentPos]=OrbitFull[i].x[2];
				pointsAbove++;
				prevSample=i;
			}
			if ((pointsAbove+pointsBelow)<numSamples) return 0; //Not enough samples available

			startSample=numSamples-(options->orbitInterpolationDegree-pointsAbove);

			if (startSample<=FirstSampleNonMaxDistance) return 0; //One of the samples is over the maximum time between samples
		} else {
			prevSample=nearestSample;
			//Look for samples before and in the current epoch (as we need to check if the closest sample is not empty)
			for(i=nearestSample;i>=0 && pointsBelow<=options->orbitInterpolationDegree;i--) {
				if (OrbitFull[i].validSample==0) continue; //Sample not valid
				if (k==-1) {
					if(prevSample==nearestSample) k=i;
				}
				currentPos=numSamples-pointsBelow;
				//Copy time and values of the samples to be used
				memcpy(&tPrev[currentPos],&OrbitFull[i].t,sizeof(TTime));
				pos[0][currentPos]=OrbitFull[i].x[0];
				pos[1][currentPos]=OrbitFull[i].x[1];
				pos[2][currentPos]=OrbitFull[i].x[2];
				pointsBelow++;
				prevSample=i;
			}
			if (OrbitFull[prevSample].validSample==0) return 0; //The closes sample to the current epoch is not valid. No data for current day
			if (pointsBelow>halfDeg) {
				//More than half of the samples available. Check for the upper half samples
				samplesRemaining=halfDeg;
			} else {
				//Less than half of the samples available. Check for the upper half saamples nd the additional upper ones to cover for the ones missing below 
				samplesRemaining=numSamples-pointsBelow;
			}
			if(k==-1) {
				//The nearest sample is invalid and no valid samples found before the nearest sample
				 return 0;
			} else {
				prevSample=k;
			}
			//Look for samples after the current epoch
			for(i=nearestSample+1;i<numblocs && samplesRemaining>pointsAbove;i++) {
				if (OrbitFull[i].validSample==0) continue; //Sample not valid
				currentPos=numSamples+1+pointsAbove;
				//Copy time and values of the samples to be used
				memcpy(&tPrev[currentPos],&OrbitFull[i].t,sizeof(TTime));
				pos[0][currentPos]=OrbitFull[i].x[0];
				pos[1][currentPos]=OrbitFull[i].x[1];
				pos[2][currentPos]=OrbitFull[i].x[2];
				pointsAbove++;
				prevSample=i;
			}
			if ((pointsAbove+pointsBelow)<numSamples) return 0; //Not enough samples available

			startSample=numSamples-(options->orbitInterpolationDegree-pointsAbove);
		}

		if(options->OrbitsToTMaxDistance>0.) {
			//Check that we do not go over the threshold of maximum number of data gaps
			if(tdiff(&tPrev[startSample+options->orbitInterpolationDegree],&tPrev[startSample]) > options->OrbitsToTMaxDistance) return 0;
		}

		if (pointsAbove==0) {
			//If no upper samples are found check that they are not too far for extrapolation
			if (tdiff(t,&tPrev[startSample+options->orbitInterpolationDegree])>MAXEXTRAPOLATIONTIME) return 0;
		}
		for(i=0;i<3;i++) {
			position[i] = lagrangeInterpolation(options->orbitInterpolationDegree,*t,&tPrev[startSample],&pos[i][startSample]);
		}
		
		return 1;
	}

	return 0;
}

/*****************************************************************************
 * Name        : getVelocitySP3
 * Description : Obtain the satellite velocity estimation for a specified 
 *               satellite in a given time from a specified SP3 structure.
 *               By default uses a 10 degree interpolator (5 points before the epoch 
 *               and 5 points after). The TOptions structure has a field
 *               (orbitInterpolationDegree) to allow changing the degree.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * TTime  *t                       I  N/A  Reference time
 * GNSSystem  GNSS                 I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN identifier of the satellite
 * double  *position               O  N/A  Satellite position (3D vector) at time t.
 *                                         It is used to avoid for optimisation
 *                                         purposes, to avoid recomputing it when
 *                                         obtaining satellite PVT. If this parameter
 *                                         us NULL, the position at t is computed.
 * double  *velocity               O  m/s  3D vector with the satellite velocity
 * enum SatelliteVelocity  satVel  I  N/A  Chooses if svINERTIAL or svITRF velocity
 *                                         is computed 
 * TOptions  *options              I  N/A  TOptions structure to configure behaviour
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Velocity computed
 *                                         0 => Error in the velocity computation
 *****************************************************************************/
int getVelocitySP3 (TGNSSproducts *products,TTime *t,enum GNSSystem GNSS,int PRN, double *position, double *velocity, enum SatelliteVelocity satVel, TOptions *options) {
	const double	diffTime = 0.001;
	double			pos[3],posPrev[3];
	TTime			tPrev;
	int				i;
	int				res;
		
	// Position at t
	if (position==NULL) {
		res = getPositionSP3(products,t,GNSS,PRN,pos,options);
		if (res==0) return 0;
	} else {
		memcpy(pos,position,sizeof(double)*3);
	}
	
	// Position at t-diffTime
	memcpy(&tPrev,t,sizeof(TTime));
	tPrev.SoD -= diffTime;
	res = getPositionSP3(products,&tPrev,GNSS,PRN,posPrev,options);
	if (res==0) return 0;
	
	// Earth rotation in diffTime
	if (satVel == svINERTIAL) {
		correctEarthRotation(posPrev,diffTime);
	}
	
	// Estimate velocity
	for (i=0;i<3;i++) velocity[i] = (pos[i]-posPrev[i])/diffTime;
	
	return 1;
}

/*****************************************************************************
 * Name        : getSatellitePVTBRDCraw
 * Description : Obtains PVT information for a specific satellite from broadcast 
 *               products
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * TTime  *t                       I  N/A  Reference time
 * GNSSystem  GNSS                 I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN identifier of the satellite
 * double  *position               O  m    3D vector with the satellite position
 *                                         If the pointer was NULL this parameter
 *                                         is not computed
 * double  *velocity               O  m/s  3D vector with the satellite velocity
 *                                         If the pointer was NULL this parameter
 *                                         is not computed
 * double  *ITRFvel                O  m/s  3D vector with the ITRF satellite velocity
 *                                         If the pointer was NULL this parameter
 *                                         is not computed
 * double  *clock                  O  s    Satellite clock correction
 *                                         If the pointer was NULL this parameter
 *                                         is not computed
 * int SBASIOD                     I  N/A  SBAS IOD for long term corrections                                       
 * TOptions  *options              I  N/A  TOptions structure to configure behaviour
 * Returned value (int)            O  N/A  Status of the function
 *                                         0 => Information not available
 *                                         1 => OK
 *****************************************************************************/
int getSatellitePVTBRDCraw (TGNSSproducts *products, TTime *t, enum GNSSystem GNSS, int PRN, double *position, double *velocity, double *ITRFvel, double *clock, int SBASIOD, TOptions *options) {
	TBRDCblock		*block;
	
	if (products->type != BRDC) return 0;
	
	block = selectBRDCblock(products->BRDC,t,GNSS,PRN,SBASIOD,options);

	if (block==NULL) return 0;

	// Obtain satellite clock correction
	if (clock!=NULL) {
		*clock = getClockBRDC(block,t);
	}
	
	// Obtain satellite position
	if (position!=NULL) {
		getPositionBRDC(products->BRDC,block,t,GNSS,position);
	}
	
	// Obtain satellite velocity
	if (velocity!=NULL) {
		getVelocityBRDC(products->BRDC,block,t,position,velocity,svINERTIAL,GNSS);
	}
	if (ITRFvel!=NULL) {
		getVelocityBRDC(products->BRDC,block,t,position,ITRFvel,svITRF,GNSS);
	}
	
	return 1;
}

/*****************************************************************************
 * Name        : getSatellitePVTSP3raw
 * Description : Obtains PVT information for a specific satellite from SP3 products
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * TTime  *t                       I  N/A  Reference time
 * GNSSystem  GNSS                 I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN identifier of the satellite
 * double  *position               O  m    3D vector with the satellite position
 *                                         If the pointer was NULL this parameter
 *                                         is not computed
 * double  *velocity               O  m/s  3D vector with the satellite velocity
 *                                         If the pointer was NULL this parameter
 *                                         is not computed
 * double  *ITRFvel                O  m/s  3D vector with the ITRF satellite velocity
 *                                         If the pointer was NULL this parameter
 *                                         is not computed
 * double  *clock                  O  s    Satellite clock correction
 *                                         If the pointer was NULL this parameter
 *                                         is not computed
 * TOptions  *options              I  N/A  TOptions structure to configure behaviour
 * Returned value (int)            O  N/A  Status of the function
 *                                         0 => Information not available
 *                                         1 => OK
 *****************************************************************************/
int getSatellitePVTSP3raw (TGNSSproducts *products, TTime *t, enum GNSSystem GNSS, int PRN, double *position, double *velocity, double *ITRFvel, double *clock, TOptions *options) {
	int res;
	
	if (products->type != SP3) return 0;
	
	// Obtain satellite clock correction
	if (clock!=NULL) {
		*clock = getClockSP3(products,t,GNSS,PRN,options);
		if (*clock==INVALID_CLOCK) return 0;
	}
	
	// Obtain satellite position
	if (position!=NULL) {
		res = getPositionSP3(products,t,GNSS,PRN,position,options);
		if (res==0) return 0;
	}
	
	// Obtain satellite velocity
	if (velocity!=NULL) {
		res = getVelocitySP3(products,t,GNSS,PRN,position,velocity,svINERTIAL,options);
		if (res==0) return 0;
	}
	if (ITRFvel!=NULL) {
		res = getVelocitySP3(products,t,GNSS,PRN,position,ITRFvel,svITRF,options);
		if (res==0) return 0;
	}
	
	return 1;
}

/*****************************************************************************
 * Name        : getSatellitePVT
 * Description : Obtains PVT information for a specific satellite
 *               Important note: It does NOT take into account the phase center 
 *                               correction
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * TTime  *t                       I  N/A  Reference time
 * double  flightTime              I  s    Time of flight, in order to properly 
 *                                         rotate the position
 * GNSSystem  GNSS                 I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN identifier of the satellite
 * double  *position               O  m    3D vector with the satellite position
 *                                         If the pointer was NULL this parameter
 *                                         is not computed
 * double  *velocity               O  m/s  3D vector with the inertial satellite velocity
 *                                         If the pointer was NULL this parameter
 *                                         is not computed
 * double  *ITRFvel                O  m/s  3D vector with the ITRF satellite velocity
 *                                         If the pointer was NULL this parameter
 *                                         is not computed
 * double  *clock                  O  s    Satellite clock correction
 *                                         If the pointer was NULL this parameter
 *                                         is not computed
 * int SBASIOD                     I  N/A  SBAS IOD for long term corrections                                       
 * TOptions  *options              I  N/A  TOptions structure to configure behaviour
 * Returned value (int)            O  N/A  Status of the function
 *                                         0 => Information not available
 *                                         1 => OK
 *****************************************************************************/
int getSatellitePVT (TGNSSproducts *products, TTime *t, double flightTime, enum GNSSystem GNSS, int PRN, double *position, double *velocity, double *ITRFvel, double *clock, int SBASIOD, TOptions *options) {
	int res;
	
	if ( products->type == BRDC ) {
		res = getSatellitePVTBRDCraw(products,t,GNSS,PRN,position,velocity,ITRFvel,clock,SBASIOD,options);
	} else if ( products->type == SP3 ) {
		res = getSatellitePVTSP3raw(products,t,GNSS,PRN,position,velocity,ITRFvel,clock,options);
	} else {
		res = 0;
	}
	if ( res != 0 && options != NULL ) {
		if ( options->earthRotation ) {
			if ( position != NULL ) { 
				correctEarthRotation(position,flightTime);
			}
			if ( velocity != NULL ) {
				correctEarthRotation(velocity,flightTime);
			}
			if ( ITRFvel != NULL ) {
				correctEarthRotation(ITRFvel,flightTime);
			}
		}
	}
	
	return res;
}

/*****************************************************************************
 * Name        : fillSatellitePVT
 * Description : Obtains PVT information for a specific satellite and fills 
 *               it in TSatellite structure.
 *               It DOES take into account the phase center correction
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * TTime  *t                       I  N/A  Reference time
 * double  flightTime              I  s    Time of flight, in order to properly 
 *                                         rotate the position
 * int  satIndex                   I  N/A  Index of the satellite inside TEpoch structure
 * int  position                   I  N/A  Flag to compute position (0-> Do not)
 * int  velocity                   I  N/A  Flag to compute velocity (0-> Do not)
 * int  clock                      I  N/A  Flag to compute clock (0-> Do not)
 * int SBASIOD                     I  N/A  SBAS IOD for long term corrections                                       
 * TConstellation  *constellation  I  N/A  TConstellation structure
 * TOptions  *options              I  N/A  TOptions structure to configure the 
 *                                         satellite PVT
 * Returned value (int)            O  N/A  Status of the function
 *                                         0 => Information not available
 *                                         1 => OK
 *****************************************************************************/
int fillSatellitePVT (TEpoch *epoch, TGNSSproducts *products, TTime *t, double flightTime, int satIndex, int position, int velocity, int clock, int SBASIOD, TConstellation *constellation, TOptions *options) {
	int		res;
	double	*posPt;
	double	*velPt;
	double  *ITRFvelPt;
	double	*clkPt;
	double	posVal[3];
	double	velVal[3];
	double  ITRFvelVal[3];
	double	clkVal;
	
	if ( position ) posPt = posVal;
	else posPt = NULL;
	
	if ( velocity ) {
		velPt = velVal;
		ITRFvelPt = ITRFvelVal;
	} else {
		velPt = NULL;
		ITRFvelPt = NULL;
	}
	
	if ( clock ) clkPt = &clkVal;
	else clkPt = NULL;
	
	
	res = getSatellitePVT(products, t, flightTime, epoch->sat[satIndex].GNSS, epoch->sat[satIndex].PRN, posPt, velPt, ITRFvelPt, clkPt, SBASIOD, options);
	
	if (res!=0) {
		
		
	
		// Store it in TEpoch structure
		if ( position ) {
			memcpy(epoch->sat[satIndex].position,posPt,sizeof(double)*3);
		}
		if ( velocity ) {
			memcpy(epoch->sat[satIndex].velocity,velPt,sizeof(double)*3);
		}
		if ( velocity ) {
			memcpy(epoch->sat[satIndex].ITRFvel,ITRFvelPt,sizeof(double)*3);
		}
		if ( clock ) {
			epoch->sat[satIndex].clockCorrection = -*clkPt;
		}
		
		// Satellite orientation
		fillSatelliteOrientation(epoch,satIndex);
		
		// Flag the satellite as "orbit and clock" available
		epoch->sat[satIndex].hasOrbitsAndClocks = 1;
	} else {
		// Flag the satellite as "orbit and clock" unavailable
		epoch->sat[satIndex].hasOrbitsAndClocks = 0;
	}
	return res;
}

/*****************************************************************************
 * Name        : getLineOfSight
 * Description : Obtains the Line of Sight vector from receiver to satellite.
 *               LoS is an unitary vector.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *satPos                 I  N/A  Transmitter position
 * double  *recPos                 I  N/A  Receiver position
 * double  *LoS                    O  N/A  Line of Sight
 *****************************************************************************/
void getLineOfSight (double *satPos, double *recPos, double *LoS) {
	int			i;
	
	for (i=0;i<3;i++)
		LoS[i] = satPos[i] - recPos[i];
	
	unitary(LoS);
}

/*****************************************************************************
 * Name        : fillLineOfSight
 * Description : Obtains the Line of Sight vector from receiver to satellite.
 *               LoS is an unitary vector.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 * int  satIndex                   I  N/A  Index of the satellite inside TEpoch structure
 *****************************************************************************/
void fillLineOfSight (TEpoch *epoch, int satIndex) {
	TSatellite	*sat;
	
	sat = &epoch->sat[satIndex];
	
	getLineOfSight(sat->position,epoch->receiver.aproxPosition,sat->LoS);
}

/*****************************************************************************
 * Name        : findMoon
 * Description : Obtains the position vector of the Moon in relation to Earth 
 *               (in ECEF). Source: 
 *               O. Montenbruck and G. Eberhard, Satellite Orbits, pp. 70-73, Springer, 2000
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * double  *moonPosition           O  Km   Moon position at t
 *****************************************************************************/
void findMoon (TTime *t, double* moonPosition) {
	double	T;
	double	L0;
	double 	l;
	double	lp;
	double	F;
	double	D;
	double	longitude;
	double	latitude;
	double	distance;
	double	obliquity = 23.43929111*d2r;
	double	fday;
	double	JDN;
	double	gstr;
	
	fday = t->SoD/86400;
	JDN = t->MJDN-15019.5 + fday;
	
	T 	= (t->MJDN - 51544.5  + t->SoD/86400)/36525.0;
	L0	= (218.31617 + 481267.88088*T - 1.3972*T)*d2r;
	l 	= (134.96292 + 477198.86753*T)*d2r;
	lp	= (357.52543 +  35999.04944*T)*d2r;
	F	= (93.27283  + 483202.01873*T)*d2r;
	D	= (297.85027 + 445267.11135*T)*d2r;
	
	longitude = L0 + (22640*sin(l) + 769*sin(2*l)
					- 4586*sin(l-2*D) + 2370*sin(2*D)
					- 668*sin(lp) - 412*sin(2*F)
					- 212*sin(2*l-2*D) - 206*sin(l+lp-2*D)
					+ 192*sin(l+2*D) - 165*sin(lp-2*D)
					+ 148*sin(l-lp) - 125*sin(D)
					- 110*sin(l+lp) - 55*sin(2*F-2*D)
				)/3600*d2r;
				
	latitude = (18520*sin(F + longitude - L0 + (412*sin(2*F) + 541*sin(lp))/3600*d2r)
				- 526*sin(F-2*D) + 44*sin(l+F-2*D)
				- 31*sin(-l+F-2*D) - 25*sin(-2*l+F)
				- 23*sin(lp+F-2*D) + 21*sin(-l+F)
				+ 11*sin(-lp+F-2*D)
				)/3600*d2r;
				
	distance = (385000 - 20905*cos(l) - 3699*cos(2*D-l)
				- 2956*cos(2*D) - 570*cos(2*l) + 246*cos(2*l-2*D)
				- 205*cos(lp-2*D) -171*cos(l+2*D)
				- 152*cos(l+lp-2*D)
				)*1;
	
	longitude = modulo(longitude,Pi*2);
	latitude = modulo(latitude,Pi*2);
	
	moonPosition[0] = distance * cos(longitude) * cos(latitude);
	moonPosition[1] = distance * sin(longitude) * cos(latitude);
	moonPosition[2] = distance * sin(latitude);
	
	rotate(moonPosition,-obliquity,1);
	
	// Rotate from inertial to non inertial system (ECI to ECEF)
	gstr = modulo(279.690983 + 0.9856473354*JDN + 360*fday + 180,360)*d2r;
	rotate(moonPosition,gstr,3);
}

/*****************************************************************************
 * Name        : findSun
 * Description : Obtains the position vector of the Sun in relation to Earth
 *               (in ECEF).
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * double  *sunPosition            O  Km   Sun position at t
 *****************************************************************************/
void findSun (TTime *t, double* sunPosition) {
	double	gstr;
	double	slong;
	double	sra;
	double	sdec;
	
	GSDtime_sun(t,&gstr,&slong,&sra,&sdec);
	
	sunPosition[0] = cos(sdec*d2r) * cos((sra)*d2r) * AU;
	sunPosition[1] = cos(sdec*d2r) * sin((sra)*d2r) * AU;
	sunPosition[2] = sin(sdec*d2r) * AU;
	
	// Rotate from inertial to non inertial system (ECI to ECEF)
	rotate(sunPosition,gstr*d2r,3);
}

/*****************************************************************************
 * Name        : GSDtime_sun
 * Description : Positions the sun
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * double*  gstr                   O  rad  GMST0 (to go from ECEF to inertial)
 * double*  slong                  O  rad  Sun longitude
 * double*  sra                    O  rad  Sun right Ascension
 * double*  sdec                   O  rad  Sun declination
 *****************************************************************************/
void GSDtime_sun (TTime *t, double *gstr, double *slong, double *sra, double *sdec) {
	//Static variables are shared between threads (as they are saved in the data segment).
	//To avoid race conditions, we need to set the directive '#pragma omp threadprivate()'
	//directive to make OpenMP create a local (static) copy for each thread
	static int		first = 1;
	#pragma omp threadprivate(first)
	static TTime	lastTimeComputed;
	#pragma omp threadprivate(lastTimeComputed)
	static double	gstrRec,slongRec,sraRec,sdecRec;
	#pragma omp threadprivate(gstrRec,slongRec,sraRec,sdecRec)
	double			JDN;
	double			fday;
	double			vl;
	double			g;
	double			obliq;
	double			slp;
	double			sind;
	double			cosd;
	
	if (first) {
		first = 0;
		lastTimeComputed.MJDN = 0;
		lastTimeComputed.SoD = 0;
	}
	
	if (tdiff(t,&lastTimeComputed)==0) {
		*gstr = gstrRec;
		*slong = slongRec;
		*sra = sraRec;
		*sdec = sdecRec;
		return;
	}
	
	fday = t->SoD/86400;
	JDN = t->MJDN-15019.5 + fday;
	
	vl = modulo(279.696678 + 0.9856473354*JDN,360);
	*gstr = modulo(279.690983 + 0.9856473354*JDN + 360*fday + 180,360);
	g = modulo(358.475845 + 0.985600267*JDN,360)*d2r;
	
	*slong = vl + (1.91946-0.004789*JDN/36525)*sin(g) + 0.020094*sin(2*g);
	obliq = (23.45229-0.0130125*JDN/36525)*d2r;
	
	slp = (*slong-0.005686)*d2r;
	sind = sin(obliq)*sin(slp);
	cosd = sqrt(1-sind*sind);
	*sdec = atan2(sind,cosd)/d2r;
	
	*sra = 180 - atan2(sind/cosd/tan(obliq),-cos(slp)/cosd)/d2r;
	
	slongRec = *slong;
	sraRec = *sra;
	gstrRec = *gstr;
	sdecRec = *sdec;
	memcpy(&lastTimeComputed,t,sizeof(TTime));
}

/*****************************************************************************
 * Name        : receiverPhaseCenterCorrection
 * Description : Get the receiver phase center correction for a specific measurement 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TAntenna *antenna               I  N/A  Antenna information
 * GNSSystem  GNSS                 I  N/A  GNSS system of the satellite
 * MeasurementType meas            I  N/A  Measurement type
 * double  orientation[3][3]       I  N/A  Receiver orientation
 * double  *LoS                    I  N/A  Line of Sight satellite-receiver
 * Returned value (double)         O  N/A  Receiver antenna phase center projection
 *                                         into the LoS
 *****************************************************************************/
double receiverPhaseCenterCorrection (TAntenna *antenna, enum GNSSystem GNSS, enum MeasurementType meas, double orientation[3][3], double *LoS) {
	int		ind;
	double	dr[3];
	int		i,j;
	
	ind = getFrequencyInt(meas);
	for (j=0;j<3;j++) {
		dr[j] = 0;
		for (i=0;i<3;i++) {
			dr[j] += orientation[i][j]*antenna->PCO[GNSS][ind][i];
		}
	}

	return -scalarProd(dr,LoS);
}

/*****************************************************************************
 * Name        : receiverPhaseCenterVarCorrection
 * Description : Get the receiver phase center correction for a specific measurement 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TAntenna *antenna               I  N/A  Antenna information
 * GNSSystem  GNSS                 I  N/A  GNSS system of the satellite
 * MeasurementType meas            I  N/A  Measurement type
 * double  elevation               I  N/A  Elevation of the satellite in relation to the station (radians)
 * Returned value (double)         O  N/A  Receiver antenna phase center variation correction 
 *****************************************************************************/
double receiverPhaseCenterVarCorrection (TAntenna *antenna, enum GNSSystem GNSS, enum MeasurementType meas, double elevation){

	int	pos;
	int     ind;
	double	diff; 
	
	// Only non azimuth dependent corrections implemented!!!!!

	// Check if angle is above the maximum zenital angle in the ANTEX file (some antennas the data goes from 0 to 80º)
	if ( 90 - elevation*r2d > antenna->zen2 ) return 0;

	ind = getFrequencyInt(meas);
	pos = (int)((90 - elevation * r2d - antenna->zen1) / antenna->dzen);

	// Check for the cases that are in the extreme
	if ( pos == antenna->nzen-1 ) return antenna->noazi[GNSS][ind][pos];

	// Interpolate values
	diff = ((90 - elevation * r2d - antenna->zen1) / antenna->dzen) - pos;

	return antenna->noazi[GNSS][ind][pos]*(1-diff)+antenna->noazi[GNSS][ind][pos+1]*diff;
	

}


/*****************************************************************************
 * Name        : receiverARPCorrection
 * Description : Get the receiver Antenna Reference Point 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *ARP                    I  N/A  3D vector with dNEU data of the ARP
 * double  orientation[3][3]       I  N/A  Receiver orientation
 * double  *LoS                    I  N/A  Line of Sight satellite-receiver
 * Returned value (double)         O  N/A  Receiver ARP projection into the LoS
 *****************************************************************************/
double receiverARPCorrection (double *ARP, double orientation[3][3] , double *LoS) {
	int		i,j;
	double	dr[3];
	
	for (j=0;j<3;j++) {
		dr[j] = 0;
		for (i=0;i<3;i++) {
			dr[j] += orientation[i][j]*ARP[i];
		}
	}
	
	return -scalarProd(dr,LoS);
}

/*****************************************************************************
 * Name        : relativisticCorrection
 * Description : Returns the relativistic correction for the current satellite
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *position               I  m    Position of the GNSS satellite
 * double  *velocity               I  m/s  Velocity of the GNSS satellite
 * Returned value (double)         O  m    Relativistic correction
 *****************************************************************************/
double relativisticCorrection (double *position, double *velocity) {
	return scalarProd(position,velocity)*2/c0;
}

/*****************************************************************************
 * Name        : windUpCorrection
 * Description : Obtains the wind up correction for carrier-phase measurements
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * int  satIndex                   I  N/A  Index of the satellite to obtain the
 *                                         correction
 * Returned value (double)         O  rad  Wind up correction
 *****************************************************************************/
double windUpCorrection (TEpoch *epoch, int satIndex) {
	int				i;
	double			satelliteAzimuth;
	double			satelliteElevation;
	double			satelliteInc;
	double			receiverInc;


	i = epoch->satCSIndex[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];
	
	getAzimuthElevation(epoch->sat[satIndex].orientation,epoch->sat[satIndex].position,epoch->receiver.aproxPosition,&satelliteAzimuth,&satelliteElevation);

	if (epoch->t.MJDN!=epoch->cycleslip.lastModelledEpoch[satIndex].MJDN || (epoch->t.SoD-epoch->cycleslip.lastModelledEpoch[satIndex].SoD)>1E-4) {
		//Epoch changed
		epoch->cycleslip.lastModelledEpoch[satIndex].MJDN=epoch->t.MJDN;
		epoch->cycleslip.lastModelledEpoch[satIndex].SoD=epoch->t.SoD;
	
		satelliteInc = satelliteAzimuth - epoch->cycleslip.windUpRadAccumSatellite[i];
		receiverInc = epoch->sat[satIndex].azimuth - epoch->cycleslip.windUpRadAccumReceiver[i];

		epoch->cycleslip.windUpRadAccumSatellitePrev[i] = epoch->cycleslip.windUpRadAccumSatellite[i];
		epoch->cycleslip.windUpRadAccumReceiverPrev[i] = epoch->cycleslip.windUpRadAccumReceiver[i];

		epoch->cycleslip.windUpRadAccumSatellite[i] += atan2(sin(satelliteInc),cos(satelliteInc));
		epoch->cycleslip.windUpRadAccumReceiver[i] += atan2(sin(receiverInc),cos(receiverInc));
	} else {
		//Same epoch. We have to use the previous windUp accumulated, so the windUp correction is not added more than once in an epoch
		satelliteInc = satelliteAzimuth - epoch->cycleslip.windUpRadAccumSatellitePrev[i];
		receiverInc = epoch->sat[satIndex].azimuth - epoch->cycleslip.windUpRadAccumReceiverPrev[i];

		epoch->cycleslip.windUpRadAccumSatellite[i] = epoch->cycleslip.windUpRadAccumSatellitePrev[i] + atan2(sin(satelliteInc),cos(satelliteInc));
		epoch->cycleslip.windUpRadAccumReceiver[i] = epoch->cycleslip.windUpRadAccumReceiverPrev[i] + atan2(sin(receiverInc),cos(receiverInc));
	}

	return epoch->cycleslip.windUpRadAccumSatellite[i] - epoch->cycleslip.windUpRadAccumReceiver[i];
}

/*****************************************************************************
 * Name        : interpolateNiell
 * Description : Support function to interpolate values for the computation
 *               the Niell tropospheric correction
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  x                       I  deg  Station latitude
 * double  v[3][5]                 I  N/A  Matrix of vector to interpolate
 * int  i                          I  N/A  Selector of 'v' row
 * Returned value (double)         O  N/A  Interpolated value of v[i] in x
 *****************************************************************************/
double interpolateNiell (double x, double v[3][5], int i) {
  double x1,x2,y1,y2;
  int j;

  if (x<15) return v[i][0];
  if (x>75) return v[i][4];
  j = 1 + (int)(x/15-1);

  x1 = 15.*j;
  x2 = 15.*(j+1);
  y1 = v[i][j-1];
  y2 = v[i][j];

  return (x-x2)/(x1-x2)*y1 + (x-x1)/(x2-x1)*y2;
}

/*****************************************************************************
 * Name        : xmNiell
 * Description : Support function for the computation of the Niell tropospheric 
 *               mapping
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  elevation               I  rad  Elevation of the satellite in relation
 *                                         to the station
 * double  vector[3][5]            I  N/A  Mapping factors
 * Returned value (double)         O  N/A  Mapping
 *****************************************************************************/
double xmNiell (double elevation, double vector[3]) {
  double xn,xd,sinE;

  xn = 1. + vector[0]/(1. + vector[1]/(1. + vector[2]));
  sinE = sin(elevation);
  xd = sinE + vector[0]/(sinE+vector[1]/(sinE+vector[2]));

  return xn/xd;
}

/*****************************************************************************
 * Name        : tropNiell
 * Description : Obtains the Niell mappings
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * double  *positionNEU            I  rd/m 3D vector with latitude-longitude-height 
 *                                         of the station
 * double  elevation               I  rad  Elevation (from the station point of view) 
 *                                         of the pair station-satellite
 * double  *tropDryMap             O  N/A  Dry mapping factor (relates vertical delay 
 *                                         with slant delay)
 * double  *tropWetMap             O  N/A  Wet mapping factor (relates vertical delay
 *                                         with slant delay)
 *****************************************************************************/
void tropNiell (TTime *t,double *positionNEU,double elevation,double *tropDryMap,double *tropWetMap) {
	double	latitude;
	double	vector[3];
	int		i;
	double	DoY,d0;
	int 	year;
	
	//Static variables are shared between threads (as they are saved in the data segment).
	//To avoid race conditions, we need to set the directive '#pragma omp threadprivate()'
	//directive to make OpenMP create a local (static) copy for each thread

	// Coefficients of Hydrostatic Mapping function
	//   Average
	static double average[3][5] = {
		  {1.2769934e-3,1.2683230e-3,1.2465397e-3,1.2196049e-3,1.2045996e-3},
		  {2.9153695e-3,2.9152299e-3,2.9288445e-3,2.9022565e-3,2.9024912e-3},
		  {62.610505e-3,62.837393e-3,63.721774e-3,63.824265e-3,64.258455e-3}};
	#pragma omp threadprivate(average)
	
	//   Amplitude
	static double amplitude[3][5] = {
		  {0.e0,1.2709626e-5,2.6523662e-5,3.4000452e-5,4.1202191e-5},
		  {0.e0,2.1414979e-5,3.0160779e-5,7.2562722e-5,11.723375e-5},
		  {0.e0,9.0128400e-5,4.3497037e-5,84.795348e-5,170.37206e-5}};
	#pragma omp threadprivate(amplitude)
		  
	//   Height correction
	static double heightCorr[3] = {2.53e-5,5.49e-3,1.14e-3};
	#pragma omp threadprivate(heightCorr)

	// Coefficients of Wet Mapping Function
	static double awet[3][5] = {
		  {5.8021897e-4,5.6794847e-4,5.8118019e-4,5.9727542e-4,6.1641693e-4},
		  {1.4275268e-3,1.5138625e-3,1.4572752e-3,1.5007428e-3,1.7599082e-3},
		  {4.3472961e-2,4.6729510e-2,4.3908931e-2,4.4626982e-2,5.4736038e-2}};
	#pragma omp threadprivate(awet)
	
	latitude = fabs(positionNEU[0]/d2r);
	t2doy(t,&year,&DoY);

	if (positionNEU[0] >= 0) {
		d0=28;
	} else {
		d0=211;
	}
	
	//In Niell mapping, UT days are from 0 to 364.25. gLAB DoY go from 1 to 365.25
	DoY--;

	// Hydrostatic mapping...
	for (i=0;i<3;i++) {
		vector[i] = interpolateNiell(latitude,average,i) - interpolateNiell(latitude,amplitude,i)*cos(2*Pi*(DoY-d0)/365.25);
	}
	*tropDryMap = xmNiell(elevation,vector) + (1./sin(elevation) - xmNiell(elevation,heightCorr))*positionNEU[2]/1000.;
	
	// Wet mapping
	for (i=0;i<3;i++) {
		vector[i] = interpolateNiell(latitude,awet,i);
	}
	*tropWetMap = xmNiell (elevation,vector);
}

/*****************************************************************************
 * Name        : troposphericCorrection
 * Description : Computes the troposheric nominal values and the mapping used 
 *               to obtain the troposheric correction depending on the input
 *               options.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * double  *positionNEU            I  rd/m 3D vector with latitude-longitude-height 
 *                                         of the station
 * double  elevation               I  rad  Elevation (from the station point of view) 
 *                                         of the pair station-satellite
 * TTROPOGal *TropoGal             I  N/A  TTROPOGal structure with Galileo's tropospheric data
 * double  *tropWetMap             O  N/A  Wet mapping factor (relates vertical delay
 *                                         with slant delay)
 * double  *ZTD                    O  m    Zenith Troposphreic Delay (without mapping)
 * Returned value (double)         O  m    Tropospheric slant correction
 *****************************************************************************/
double troposphericCorrection (TTime *t, double *positionNEU, double elevation, TTROPOGal *TropoGal, double *tropWetMap, double *ZTD, TOptions *options) {
	double	tropDryMap=1.;
	double	tropDryNominal=0.,tropWetNominal=0.;

	// Sanity check
	if (positionNEU[2]<-200) {
		*tropWetMap = 0;
		*ZTD = 0;
		return 0;
	}

	// Compute Nominal Tropospheric values
	switch(options->tropNominal) {
		case SimpleNominal:
			tropDryNominal = 1.013*2.27*exp((-0.116e-03)*positionNEU[2]);
			tropWetNominal = 0.10;
			break;
		case UNB3Nominal:
			troposphericCorrectionMOPS (t,positionNEU,elevation,&tropDryNominal,&tropWetNominal);	
			break;
		case TropoGalileo:
			troposphericCorrectionGal (t, positionNEU, elevation, TropoGal, &tropWetNominal, &tropDryNominal);
			break;
		default:
			break;
	}

	// Compute Tropospheric Mapping
	if (options->tropMapping == NiellMapping) {
		tropNiell(t,positionNEU,elevation,&tropDryMap,tropWetMap);
	} else if (options->tropMapping == SimpleMapping) {
		*tropWetMap = 1.001/sqrt(0.002001+sin(elevation)*sin(elevation));
		tropDryMap = (*tropWetMap);
	}

	// Obtain Zenith Tropospheric Delay
	   *ZTD = tropDryNominal + tropWetNominal;


	// Return Tropospheric Slant Correction.
	return (tropDryNominal*tropDryMap + tropWetNominal*(*tropWetMap));
}


/*****************************************************************************
 * Name        : troposphericCorrectionMOPS
 * Description : Obtains, using the model described the RTCA "Minimum Operational 
 *               Performance Standards" (MOPS), version C (RTCA/DO-229C), in the
 *               Appendix A.4.2.4.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * double  *positionNEU            I  rd/m 3D vector with latitude-longitude-height 
 *                                         of the station
 * double  elevation               I  rad  Elevation (from the station point of view) 
 *                                         of the pair station-satellite
 * double  *tropWetMOPS_Nominal    O  m    Wet Nominal Value (part of vertical delay)                                        
 * double  *tropDryMOPS_Nominal    O  m    Dry Nominal Value (part of vertical delay) 
 *****************************************************************************/
void troposphericCorrectionMOPS (TTime *t, double *positionNEU, double elevation,double *tropWetMOPS_Nominal,double *tropDryMOPS_Nominal) {

	// Some MOPS specific constants
	const double MOPSgm = 9.784;
	const double MOPSg  = 9.80665;
	const double MOPSk1 = 77.604;
	const double MOPSk2 = 382000.0;
	const double MOPSRd = 287.054;


	const double MOPSzhydCT = ( 1E-6 * MOPSk1 * MOPSRd / MOPSgm );
	const double MOPSzwetCT = ( 1E-6 * MOPSk2 * MOPSRd );

	// MOPS Latitude Grid
	const double MOPSlat[5] = {   15.0,   30.0,   45.0,   60.0,   75.0};
	
		// Meteorological Average Parameters : Po, To, Eo, Betao, Lambdao
	const double MOPSaverages[5][5] = {
		{1013.25,1017.25,1015.75,1011.75,1013.00},
		{ 299.65, 294.15, 283.15, 272.15, 263.65},
		{  26.31,  21.79,  11.66,   6.78,   4.11},
	  	{6.30E-3,6.05E-3,5.58E-3,5.39E-3,4.53E-3},
		{   2.77,   3.15,   2.57,   1.81,   1.55}};
  
		// Meteorological Seasonal Variation : deltaP, deltaT, deltaE, deltaBeta, deltaLambda
	const double MOPSvariations[5][5] = {
	  {    0.0,  -3.75,  -2.25,  -1.75,  -0.50},
	  {    0.0,    7.0,   11.0,   15.0,   14.5},
	  {    0.0,   8.85,   7.24,   5.36,   3.39},
	  { 0.0E-3,0.25E-3,0.32E-3,0.81E-3,0.62E-3},
	  {    0.0,   0.33,   0.46,   0.74,   0.30}};

		// Year Fraction Constants
	const double DminNorth = 28.0;
	const double DminSouth = 211.0;
	const double MOPScosCT = ( 2.0 * Pi / 365.25 );


	// In-Function Constants
	double	latitude;
	double	vectorPTEBL[5],averagePTEBL[5],seasvarPTEBL[5];
	double  Tzo_dry,Tzo_wet,exp1,exp2,Tz_dry,Tz_wet;
	int		i,index;
	double	DoY, Dmin;
	int 	year;
	double  factor;
	
	// Latitude Quantimization
	latitude = positionNEU[0]/d2r;
	if ( latitude >=0.0 ){
		Dmin = DminNorth;
	}else {
		Dmin = DminSouth;
	}		
	latitude = fabs( latitude );
		if (  latitude <= 15.0 )                          index=0;
		if ( (latitude >  15.0 ) && (latitude <= 30.0)  ) index=1;
		if ( (latitude >  30.0 ) && (latitude <= 45.0)  ) index=2;
		if ( (latitude >  45.0 ) && (latitude <= 60.0)  ) index=3;
		if ( (latitude >  60.0 ) && (latitude <  75.0)  ) index=4;
		if (  latitude >= 75.0 )                          index=4;


	// Year Fraction
	t2doy(t,&year,&DoY);

	// Interpolate Metereological Parameters
	if ( latitude <= 15.0  || latitude >= 75.0 ) {
		latitude = MOPSlat[index];
		for (i=0; i<5; i++){ 
			averagePTEBL[i] = MOPSaverages[i][index];
			seasvarPTEBL[i] = MOPSvariations[i][index];
			}
	} else { 
		latitude = ( latitude - MOPSlat[index-1] ) / ( MOPSlat[index] - MOPSlat[index-1] ); 
		for (i=0; i<5; i++){ 
			averagePTEBL[i] = MOPSaverages[i][index-1]   + ( MOPSaverages[i][index]   - MOPSaverages[i][index-1]   ) * latitude;
			seasvarPTEBL[i] = MOPSvariations[i][index-1] + ( MOPSvariations[i][index] - MOPSvariations[i][index-1] ) * latitude;
			}
	}

	// Compute metereologial parameters, from the interpolated Average and Seasonal:
	for (i=0; i<5; i++){ 
		vectorPTEBL[i] = averagePTEBL[i] - seasvarPTEBL[i] * cos ( (DoY - Dmin)*MOPScosCT );
	}

	// Zero-altitude zenith delay terms:
		Tzo_dry = MOPSzhydCT * vectorPTEBL[0];	
		Tzo_wet = ( MOPSzwetCT /(MOPSgm*(vectorPTEBL[4]+1.0)-vectorPTEBL[3]*MOPSRd) ) * (vectorPTEBL[2]/vectorPTEBL[1]);

	factor=vectorPTEBL[3]*positionNEU[2]/vectorPTEBL[1];

	//Sanity check: The result of the calculus Beta*Height/Temperature must be under 1
	if (factor<1) {
		// zenith delay terms at H meters of height above mean-sea-level        
			exp1=MOPSg/(MOPSRd*vectorPTEBL[3]);
			Tz_dry=Tzo_dry*pow(1.0-factor,exp1);
	   
			exp2=((vectorPTEBL[4]+1.0)*MOPSg)/(MOPSRd*vectorPTEBL[3])-1.0 ;
			Tz_wet=Tzo_wet*pow(1.0-factor,exp2);
	} else {
		Tz_dry=0;
		Tz_wet=0;
	}

	// Return Nominals
	*tropWetMOPS_Nominal = Tz_dry;
	*tropDryMOPS_Nominal = Tz_wet;
	

}

/*****************************************************************************
 * Name        : troposphericCorrectionGal
 * Description : Obtains, using the Galileo's Matlab tropospheric model 
 *               (version 2.5, 07/09/2007) -translated to C by gAGE- the
 *               Wet and Dry Nominal Values delays
 * 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * double  *positionNEU            I  rd/m 3D vector with latitude-longitude-height 
 *                                         of the station
 * double  elevation               I  rad  Elevation (from the station point of view) 
 *                                         of the pair station-satellite
 * TTROPOGal *TropoGal             I  N/A  TTROPOGal structure with Galileo's trosposheric data
 * double  *tropWetGal_Nominal     O  m    Wet Nominal Value (part of vertical delay)                                        
 * double  *tropDryGal_Nominal     O  m    Dry Nominal Value (part of vertical delay) 
 *****************************************************************************/
void troposphericCorrectionGal (TTime *t, double *positionNEU, double elevation, TTROPOGal *TropoGal, double *tropWetGal_Nominal, double *tropDryGal_Nominal) {


}

/*****************************************************************************
 * Name        : troposphericGalparameters
 * Description : Calculates Galileo tropospheric model parameters
 *
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  Reference time
 * int ilat                        I  N/A  Position in latitude vector
 * int ilon                        I  N/A  Position in longitude vector
 * double latitude                 I  º    Latitude
 * double longitude                I  º    Longitude
 * double *positionNEU             I  rd/m 3D vector with latitude-longitude-height 
 *                                         of the station
 * double elevation                I  rad  Elevation (from the station point of view) 
 *                                         of the pair station-satellite
 * double MapPoints[4][3]          I  N/A  Latitude(degrees),Longitude (degrees),Altitude(meters) of the four points in the map
 * double *hgt_pix                 I  m    Height above mean sea level in the four map points
 * TTROPOGal *TropoGal             I  N/A  TTROPOGal structure with Galileo's tropospheric data
 * TTROPOGalParameters *parameters O  N/A  TTROPOGalParameters structure
 *****************************************************************************/
void troposphericGalparameters (TTime  *t, int ilat, int ilon, double latitude, double longitude, double  *positionNEU, double  elevation, double MapPoints[4][3], double *hgt_pix, TTROPOGal *TropoGal, TTROPOGalParameters *parameters) {

}



/*****************************************************************************
 * Name        : klobucharModel
 * Description : Obtains the ionospheric correction using the klobuchar model
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TGNSSproducts  *products        I  N/A  Ephemerides products to obtain the
 *                                         parameters for the model
 * int  satIndex                   I  N/A  Index of the satellite to obtain 
 *                                         the correction
 * Returned value (double)         O  TECU Klobuchar correction in STEC (in 
 *                                         electrons per area unit)
 *****************************************************************************/
double klobucharModel (TEpoch *epoch, TGNSSproducts *products, int satIndex) {
	double			fm;
	double			ilat;
	double			ilon;
	double			gmlat;
	double			tsub;
	double			slantFactor;
	double			alpha;
	double			beta;
	double			x;
	double			y;
	double			ionoDelay,ionoDelaymeters;
	double			tauvert,Fpp;
	const double	h = KLOBUCHAR_HEIGHT;

	
	if (products->type != BRDC) return 0;

		// Calculate the Earth-centered angle fm (in radians):
		fm = 0.5*Pi -1.0*epoch->sat[satIndex].elevation-asin(EARTH_RADIUS/(EARTH_RADIUS+h)*cos(epoch->sat[satIndex].elevation));

		// Compute the subionospheric latitude, ilat (in radians):
		ilat = asin(sin(epoch->receiver.aproxPositionNEU[0])*cos(fm) + cos(epoch->receiver.aproxPositionNEU[0])*sin(fm)*cos(epoch->sat[satIndex].azimuth));

		// Compute the subionospheric longitude, ilon (in radians):
		ilon = epoch->receiver.aproxPositionNEU[1] + fm*sin(epoch->sat[satIndex].azimuth)/cos(ilat);

		// Find the Geomagnetic latitude, gmlat (in radians):
		gmlat = asin(sin(ilat)*sin(GEOMAGNETIC_POLE_LAT) + cos(ilat)*cos(GEOMAGNETIC_POLE_LAT)*cos(ilon-GEOMAGNETIC_POLE_LON));

		// Find the local time at subionospheric point, tsub (in sec):
		tsub = 43200*ilon/Pi + epoch->t.SoD;
		if (tsub>86400) tsub -= 86400;
		else if (tsub<0) tsub += 86400;

		// Convert to slant time delay:
		slantFactor = 1.0/sqrt(1.0-pow(EARTH_RADIUS/(EARTH_RADIUS+h)*cos(epoch->sat[satIndex].elevation),2));



		// Compute the ionospheric delay STEC (in metres of delay):

		gmlat =gmlat/Pi;

	alpha = products->BRDC->ionA[0] + 
			products->BRDC->ionA[1] * gmlat +
			products->BRDC->ionA[2] * pow(gmlat,2) +
			products->BRDC->ionA[3] * pow(gmlat,3);
	beta =  products->BRDC->ionB[0] + 
			products->BRDC->ionB[1] * gmlat +
			products->BRDC->ionB[2] * pow(gmlat,2) +
			products->BRDC->ionB[3] * pow(gmlat,3);

	if (alpha<0) alpha = 0;
	if (beta<72000) beta = 72000;
	//else if (beta>144000) beta = 144000;  //Uncomment this line to fix Klobuchar excessive period

		x = 2.0*Pi*(tsub-50400)/beta;
		if (fabs(x)<=1.57) {
				y = alpha * cos(x);
		} else {
				y = 0.0;
		}


	ionoDelaymeters = slantFactor*(5e-9+y)*c0; // in L1 meters

	// Change from L1 meters to TECU 
	ionoDelay = ionoDelaymeters / 40.3 * GPSf1 * GPSf1 * pow(10,-16); // in TECUs

	////Compute Klobuchar sigma for SBAS
	//Compute tauvert (tau vertical)
	if (fabs(gmlat)<=20) tauvert=9;
	else if (fabs(gmlat)<=55) tauvert=4.5;
	if(fabs(gmlat)>55) tauvert=6;
	//Compute SBAS slant factor
	Fpp=1/sqrt(1-pow((SBAS_EARTH_RADIUS*cos(epoch->sat[satIndex].elevation))/(SBAS_EARTH_RADIUS+SBAS_HEIGHT),2));
	epoch->sat[satIndex].ionoSigma=max(pow(ionoDelaymeters/5,2),pow(Fpp*tauvert,2));	// In meters^2



	return ionoDelay;
}

/*****************************************************************************
 * Name        : beiDouKlobucharModel
 * Description : Obtains the ionospheric correction using the BeiDou 
 *                klobuchar model
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TGNSSproducts  *products        I  N/A  Ephemerides products to obtain the
 *                                         parameters for the model
 * int  satIndex                   I  N/A  Index of the satellite to obtain 
 *                                         the correction
 * Returned value (double)         O  TECU Klobuchar correction in STEC (in 
 *                                         electrons per area unit)
 *****************************************************************************/
double beiDouKlobucharModel (TEpoch *epoch, TGNSSproducts *products, int satIndex) {
	double			fm;
	double			ilat;
	double			ilon;
	double			gmlat;
	double			tsub;
	double			slantFactor;
	double			alpha;
	double			beta;
	double			x;
	double			y;
	double			ionoDelay;
	const double	h = BEIDOU_HEIGHT;
	
		if (products->type != BRDC) return 0;
																									   
		// Calculate the Earth-centered angle fm (in radians):                                         
		fm = 0.5*Pi -1.0*epoch->sat[satIndex].elevation-asin(EARTH_RADIUS/(EARTH_RADIUS+h)*cos(epoch->sat[satIndex].elevation));        

		// Compute the subionospheric latitude, ilat (in radians):                                     
		ilat = asin(sin(epoch->receiver.aproxPositionNEU[0])*cos(fm) + cos(epoch->receiver.aproxPositionNEU[0])*sin(fm)*cos(epoch->sat[satIndex].azimuth));                                                    
		
		// Compute the subionospheric longitude, ilon (in radians):                                    
		ilon = epoch->receiver.aproxPositionNEU[1] + fm*sin(epoch->sat[satIndex].azimuth)/cos(ilat);   
		
		// Find the Geomagnetic latitude, gmlat (in radians):
		gmlat = asin(sin(ilat)*sin(GEOMAGNETIC_POLE_LAT) + cos(ilat)*cos(GEOMAGNETIC_POLE_LAT)*cos(ilon-GEOMAGNETIC_POLE_LON));         
		
		// Find the local time at subionospheric point, tsub (in sec):
		tsub = 43200*ilon/Pi + epoch->t.SoD;                                                           
		if (tsub>86400) tsub -= 86400;                                                                 
		else if (tsub<0) tsub += 86400;
		
		// Convert to slant time delay:                                                                
		slantFactor = 1.0/sqrt(1.0-pow(EARTH_RADIUS/(EARTH_RADIUS+h)*cos(epoch->sat[satIndex].elevation),2));                                                                                                  
																									   
		
		
		// Compute the ionospheric delay STEC (in metres of delay):                                    
																									   
		gmlat =gmlat/Pi;                                                                               
																									   
		alpha = products->BRDC->bdsA[0] + 
						products->BRDC->bdsA[1] * gmlat +                                              
						products->BRDC->bdsA[2] * pow(gmlat,2) +                                       
						products->BRDC->bdsA[3] * pow(gmlat,3);                                        
		beta =  products->BRDC->bdsB[0] +                                                              
						products->BRDC->bdsB[1] * gmlat +                                              
						products->BRDC->bdsB[2] * pow(gmlat,2) +                                       
						products->BRDC->bdsB[3] * pow(gmlat,3);                                        
		
		if (alpha<0) alpha = 0;
		if (beta<72000) beta = 72000;
	//New condition for BeiDou. This condition does not restrict that the semiperiod shall not be greater than 10 hours.
	//The right condition should be overlap with the next day should be the following:
	//if (beta>144000) beta = 144000; (instead of "if (beta>172800) beta = 172800;" given by BeiDou ICD)
	if (beta>172800) beta = 172800;
						
		x = 2.0*Pi*(tsub-50400)/beta;                                                                  
		if (fabs(x)<=1.57) { 
				y = alpha * cos(x);
		} else {
				y = 0.0;
		}

		ionoDelay = slantFactor*(5e-9+y)*c0; // in L1 meters
	

		// Change from L1 meters to TECU 
		ionoDelay = ionoDelay / 40.3 * GPSf1 * GPSf1 * pow(10,-16); // in TECUs


	return ionoDelay;
}

/*****************************************************************************
 * Name        : ionexModel
 * Description : Obtains the ionospheric correction using IONEX file data 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * int  satIndex                   I  N/A  Index of the satellite to obtain 
 * TIONEX *ionex                   I  N/A  TIONEX structure
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (double)         O  TECU Ionex correction in STEC (in 
 *                                         electrons per area unit)
 *                                         9999 is returned when one of the
 *                                         points needed for the interpolation
 *                                         is not set in the IONEX file
 *****************************************************************************/
double ionexModel (TEpoch *epoch, int satIndex, TIONEX *ionex, TOptions *options) {
	int				i, j;
	int				diffEarlierMap;
	int				diffLaterMap;
	int				diffDaysIonex;
	int				diffDaysEpoch;
	int				diffSecIonex;
	int				diffSecEpoch;
	int				totalSecIonex;
	int				totalSecEpoch;
	int				mapTimePosition;
	int				mapType = 0; // 0->TEC 1->RMS 2->HGT
	int				ilat,ilon;
	int				onlyLastMapUsed = 0;
	double			ilonvalue;
	double			unitaryEarlierTimeDiff;
	double			currentHgtInterpolation;
	double			currentRMSInterpolation;
	double			TECfinalInterpolation;
	double			RMSfinalInterpolation;
	double			TEClowLeft,TECupLeft,TEClowRight,TECupRight;
	double			RMSlowLeft,RMSupLeft,RMSlowRight,RMSupRight;
	double			unitaryLonDiff, unitaryLatDiff;
	double			totalLongitude;
	double			currentMapAltitude[ionex->map[0].nhgt];
	double			lowLeftpoint[3]; //Phi,Longitude,Altitude
	double			upLeftpoint[3];
	double			lowRightpoint[3];
	double			upRightpoint[3];
	double			TECtimeInterpolation[2];
	double			RMStimeInterpolation[2];
	TPiercePoint	*ionexPiercePointvector = NULL;


	//Auxiliary variables to avoid repetitive calculus and make code more readable
	diffDaysIonex = ionex->endTime.MJDN - ionex->startTime.MJDN;
	diffSecIonex  = diffDaysIonex*NUMBERSECONDSPERDAY;
	totalSecIonex = diffSecIonex + (int)ionex->endTime.SoD ;

	diffDaysEpoch = (int) (epoch->t.MJDN - ionex->startTime.MJDN);
	diffSecEpoch  = diffDaysEpoch*NUMBERSECONDSPERDAY;
	totalSecEpoch = diffSecEpoch + (int)epoch->t.SoD;

	totalLongitude = fabs(ionex->map[0].lon1) + fabs(ionex->map[0].lon2);


	// Check that the IONO map day matches witch RINEX observation day
	if ( epoch->t.MJDN < ionex->startTime.MJDN || totalSecEpoch > totalSecIonex ) {
		// printError ("IONEX is of a different time than the observation RINEX", options); 
		epoch->sat[satIndex].validIono = 0;
		return 9999;
	}

	// Look for map with current time. If current time is between two maps, it will start using the earlier one
	// Also, it necessary to check if the interval value is 0. In that case, time interval is variable
	if ( ionex->interval == 0 )
	{
		mapTimePosition = 0;
		do {
			mapTimePosition++;
			if ( ( (mapTimePosition +1) == ionex->numMaps) && ( totalSecEpoch <= totalSecIonex) ) { break; }
			if ( mapTimePosition == ionex->numMaps ){
				// printError("No IONEX maps found between current time",options);
				epoch->sat[satIndex].validIono = 0;
				return 9999;
			}
		} while ( (diffSecIonex + (int)ionex->map[mapTimePosition].t.SoD) < totalSecEpoch );

		if ( totalSecEpoch == totalSecIonex ){  //Special case: Only using the last map
			mapTimePosition = ionex->numMaps -1;
			diffEarlierMap = 0;
			diffLaterMap   = 0;
			unitaryEarlierTimeDiff = 0;
			onlyLastMapUsed =1;
		} else {
			mapTimePosition--;
			diffEarlierMap = totalSecEpoch - (ionex->map[mapTimePosition].t.MJDN - ionex->startTime.MJDN)*NUMBERSECONDSPERDAY  - (int)ionex->map[mapTimePosition].t.SoD;
			diffLaterMap = (ionex->map[mapTimePosition+1].t.MJDN - ionex->startTime.MJDN)*NUMBERSECONDSPERDAY + (int)(ionex->map[mapTimePosition+1].t.SoD - totalSecEpoch);
			unitaryEarlierTimeDiff = (double)diffEarlierMap / ((double)(diffEarlierMap + diffLaterMap) );
		}
	} else {
		if ( totalSecEpoch == totalSecIonex ) {  //Special case: Only using the last map
			mapTimePosition = ionex->numMaps -1;
			diffEarlierMap = 0;
			diffLaterMap   = 0;
			unitaryEarlierTimeDiff = 0;
			onlyLastMapUsed =1;
		} else {
			diffEarlierMap = totalSecEpoch % ionex->interval;
			diffLaterMap = ionex->interval - diffEarlierMap;
			unitaryEarlierTimeDiff = (double) (diffEarlierMap)/(double)(ionex->interval);
			mapTimePosition = ( totalSecEpoch - diffEarlierMap ) / ionex->interval;
			//If IONEX does not start at 0h, we need to substract as positions as number of maps are missing
			mapTimePosition -= (int)(ionex->startTime.SoD/(double)(ionex->interval));
			if (mapTimePosition<0) {
				//Epoch before IONEX data starts
				epoch->sat[satIndex].validIono = 0;
				return 9999;
			}
		}
	}
	// It will be necessary to find a Pierce Point for each altitude,
	// therefore needing the initial and ending height, and the 
	// number of steps, which are available in any map, so the first 
	// map will be used to gather this data.
	// The interpolation will be done twice, one for each map time

	TECtimeInterpolation[0]=TECtimeInterpolation[1] = 0;
	RMStimeInterpolation[0]=RMStimeInterpolation[1] = 0;
	
	for ( j=0;j < 2 - onlyLastMapUsed;j++ ) {
		
		mapTimePosition += j;
		
		for ( i=0; i < ionex->map[0].nhgt; i++ ) {
			
			//ionexPiercePointvector = malloc(sizeof(TPiercePoint)*(i+1));
			ionexPiercePointvector = (TPiercePoint*) (realloc(ionexPiercePointvector,sizeof(TPiercePoint)*(i+1)));
			initPiercePoint(&ionexPiercePointvector[i]);
			currentMapAltitude[i] = ionex->map[0].hgt1 + ionex->map[0].dhgt*i; //Stored in Km 
			
			
			//Calculate the Iono Pierce Point at current height
			getIonoPiercePoint(epoch, &ionexPiercePointvector[i], satIndex, ionex->baseRadius, currentMapAltitude[i],0);

			//Check if latitude value is in range (some IONEX files, latitude start or end at a value smaller than 90º, thus not covering the poles or more. If this PiercePoint is in the pole and IONEX file has no data, this points must be discarded
			if (ionex->map[mapTimePosition].dlat > 0 ) {
				if ( (ionexPiercePointvector[i].fi < ionex->map[mapTimePosition].lat1) || (ionexPiercePointvector[i].fi > ionex->map[mapTimePosition].lat2) ) {
					epoch->sat[satIndex].validIono = 0;
					return 9999;
				}
			} else {
				if ( (ionexPiercePointvector[i].fi > ionex->map[mapTimePosition].lat1) || (ionexPiercePointvector[i].fi < ionex->map[mapTimePosition].lat2) ) {
					epoch->sat[satIndex].validIono = 0;
					return 9999;
				}
			}

			//Rotate maps adding longitude proportional to time difference between maps
			if (j==0) { ionexPiercePointvector[i].longitude = ionexPiercePointvector[i].longitude + (double)diffEarlierMap*(1/(double)NUMBERSECONDSPERHOUR)*(360.0/24.0) ; }
			else { ionexPiercePointvector[i].longitude = ionexPiercePointvector[i].longitude - (double)diffLaterMap*(1/(double)NUMBERSECONDSPERHOUR)*(360.0/24.0) ; }
			
			//In this operation, we add 180 to move the range to 0..360 (only if longitude range is negative) and then do the module to assure the value is in range
			if ( (ionex->map[mapTimePosition].lon1 < 0) || ( ionex->map[mapTimePosition].lon2 < 0 ) ) {
				ionexPiercePointvector[i].longitude = modulo (ionexPiercePointvector[i].longitude+180.0+360.0,360);
			} else {
				ionexPiercePointvector[i].longitude = modulo (ionexPiercePointvector[i].longitude+360.0,360);
			}


			//Check if any of the values lon1 or lon2 (the limits in the range) are negative. If any is negative, it means that the range is from -180 to 180 (or 180..-180), therefore having to substract 180
			if ( (ionex->map[mapTimePosition].lon1 < 0) || ( ionex->map[mapTimePosition].lon2 < 0 ) ) {
				ionexPiercePointvector[i].longitude -=180.0;
			}

			//Check if longitude value is within the data given in the IONEX file (in the case that the longitude range is not 360 or 360-dlon)
			if ( (totalLongitude != (360.0 - fabs(ionex->map[mapTimePosition].dlon))) && (totalLongitude != (360.0 + fabs(ionex->map[mapTimePosition].dlon))) && (totalLongitude != 360.0)  ) {
				if (ionex->map[mapTimePosition].dlon > 0 ) {
					if ( (ionexPiercePointvector[i].longitude < ionex->map[mapTimePosition].lon1) || (ionexPiercePointvector[i].longitude > ionex->map[mapTimePosition].lon2) ) {
						epoch->sat[satIndex].validIono = 0;
						return 9999;
					}
				} else {
					if ( (ionexPiercePointvector[i].longitude > ionex->map[mapTimePosition].lon1) || (ionexPiercePointvector[i].longitude < ionex->map[mapTimePosition].lon2) ) {
						epoch->sat[satIndex].validIono = 0;
						return 9999;
					}
				}
			}


			//Calculate latitude and longitude for the four TEC values surrounding current pierce point
			//Given one position, it is first calculated the point which is on the bottom left hand corner of the TEC values surrounding the pierce point
				if (ionex->map[mapTimePosition].nlat==1) {
					 ilat=0;
				} else {
					 ilat = (int)((ionexPiercePointvector[i].fi - ionex->map[mapTimePosition].lat1)/ionex->map[mapTimePosition].dlat);
				}

				if (ionex->map[mapTimePosition].nlon==1) {
					 ilon=0;
				} else {
					ilon = (int)((ionexPiercePointvector[i].longitude - ionex->map[mapTimePosition].lon1)/ionex->map[mapTimePosition].dlon);
					ilonvalue = (ionexPiercePointvector[i].longitude - ionex->map[mapTimePosition].lon1)/ionex->map[mapTimePosition].dlon;
				}

			lowLeftpoint[0] = ilat*ionex->map[mapTimePosition].dlat + ionex->map[mapTimePosition].lat1;
			lowLeftpoint[1] = ilon*ionex->map[mapTimePosition].dlon + ionex->map[mapTimePosition].lon1;
			lowLeftpoint[2] = currentMapAltitude[i];

			//Special case: If IONEX Range does not start at 0 or -180 (dlon positive) or at 180 or 360 (dlon positive) and total range = 360.0 - fabs(ionex->map[mapTimePosition].dlon and the pierce point is in range 0..dlon (ilonvalue<0) (or equivalent depending on range given), then lowLeftpoint[1] is lon2 (because position 0 is given at the end) and lowLeftpoint[1] is lon1
			if ( (totalLongitude == (360.0 - fabs(ionex->map[mapTimePosition].dlon))) && (ilonvalue < 0) ) {
				lowLeftpoint[1] = ionex->map[mapTimePosition].lon2;
			}
		
			
			if ( lowLeftpoint[0] != ionex->map[mapTimePosition].lat2 ){ //The point is not at the end of the map in latitude
				lowRightpoint[0] = lowLeftpoint[0] + ionex->map[mapTimePosition].dlat;
				lowRightpoint[1] = lowLeftpoint[1];
				lowRightpoint[2] = currentMapAltitude[i];

			}

			if ( (lowLeftpoint[1] == ionex->map[mapTimePosition].lon2) && (totalLongitude == (360.0 - fabs(ionex->map[mapTimePosition].dlon)) ) ) {
				//In this IONEX file, the maps are in range 0..375º (or -180..175). Instead of using value of lon=360º, use inital longitude
				upLeftpoint[0] = lowLeftpoint[0];
				upLeftpoint[1] = ionex->map[mapTimePosition].lon1;
				upLeftpoint[2] = currentMapAltitude[i];


			} else if ( lowLeftpoint[1] != ionex->map[mapTimePosition].lon2 ){ //The point is not at the end of the map in longitude
				upLeftpoint[0] = lowLeftpoint[0];
				upLeftpoint[1] = lowLeftpoint[1] + ionex->map[mapTimePosition].dlon;
				upLeftpoint[2] = currentMapAltitude[i];

			}

			if ( lowLeftpoint[0] != ionex->map[mapTimePosition].lat2 ) {
				if ( (lowLeftpoint[1] == ionex->map[mapTimePosition].lon2) && (totalLongitude == (360.0 - fabs(ionex->map[mapTimePosition].dlon)) ) ) { 
					upRightpoint[0] = lowLeftpoint[0] + ionex->map[mapTimePosition].dlat;
					upLeftpoint[1] = ionex->map[mapTimePosition].lon1;
					upRightpoint[2] = currentMapAltitude[i];
				} else if ( lowLeftpoint[1] != ionex->map[mapTimePosition].lon2 ) {
					upRightpoint[0] = lowLeftpoint[0] + ionex->map[mapTimePosition].dlat;
					upRightpoint[1] = lowLeftpoint[1] + ionex->map[mapTimePosition].dlon;
					upRightpoint[2] = currentMapAltitude[i];

				}
			}

			//Recover TEC data from the four points
			TEClowLeft = getIonoValue(&ionex->map[mapTimePosition], mapType, lowLeftpoint[2], lowLeftpoint[0], lowLeftpoint[1]);
			RMSlowLeft = getIonoValue(&ionex->map[mapTimePosition], 1+mapType, lowLeftpoint[2], lowLeftpoint[0], lowLeftpoint[1]);

			if ( lowLeftpoint[0] != ionex->map[mapTimePosition].lat2 ){	
				TEClowRight = getIonoValue(&ionex->map[mapTimePosition], mapType, lowRightpoint[2], lowRightpoint[0], lowRightpoint[1]); 
				RMSlowRight = getIonoValue(&ionex->map[mapTimePosition], 1+mapType, lowRightpoint[2], lowRightpoint[0], lowRightpoint[1]); 
			} else {
				TEClowRight = 0;
				RMSlowRight = 0;
			}

			if ( (lowLeftpoint[1] == ionex->map[mapTimePosition].lon2) && (totalLongitude == (360.0 - fabs(ionex->map[mapTimePosition].dlon)) ) ) {
				TECupLeft = getIonoValue(&ionex->map[mapTimePosition], mapType, upLeftpoint[2], upLeftpoint[0], upLeftpoint[1]);
				RMSupLeft = getIonoValue(&ionex->map[mapTimePosition], 1+mapType, upLeftpoint[2], upLeftpoint[0], upLeftpoint[1]);

			} else if ( lowLeftpoint[1] != ionex->map[mapTimePosition].lon2 ){
				TECupLeft = getIonoValue(&ionex->map[mapTimePosition], mapType, upLeftpoint[2], upLeftpoint[0], upLeftpoint[1]);
				RMSupLeft = getIonoValue(&ionex->map[mapTimePosition], 1+mapType, upLeftpoint[2], upLeftpoint[0], upLeftpoint[1]);
			} else {
				TECupLeft = 0;
				RMSupLeft = 0;
			}
			
			if ( lowLeftpoint[0] != ionex->map[mapTimePosition].lat2 ) {
				if ( (lowLeftpoint[1] == ionex->map[mapTimePosition].lon2) && (totalLongitude == (360.0 - fabs(ionex->map[mapTimePosition].dlon)) ) ) { 
					TECupRight = getIonoValue(&ionex->map[mapTimePosition], mapType, upRightpoint[2], upRightpoint[0], upRightpoint[1]);
					RMSupRight = getIonoValue(&ionex->map[mapTimePosition], 1+mapType, upRightpoint[2], upRightpoint[0], upRightpoint[1]);
				} else if ( lowLeftpoint[1] != ionex->map[mapTimePosition].lon2 ) {
					TECupRight = getIonoValue(&ionex->map[mapTimePosition], mapType, upRightpoint[2], upRightpoint[0], upRightpoint[1]);
					RMSupRight = getIonoValue(&ionex->map[mapTimePosition], 1+mapType, upRightpoint[2], upRightpoint[0], upRightpoint[1]);
				} else {		
					TECupRight = 0;
					RMSupRight = 0;
				}
			} else {		
				TECupRight = 0;
				RMSupRight = 0;
			}

			//Check if any value is 9999 (no data for that point)
			if ( TEClowLeft == 9999 || TEClowRight == 9999 || TECupLeft == 9999 || TECupRight == 9999 ) {
				epoch->sat[satIndex].validIono = 0;
				return 9999;
			}
			if ( (RMSlowLeft == 9999 || RMSlowRight == 9999 || RMSupLeft == 9999 || RMSupRight == 9999) && options->useSigmaIono == 1 ) {
				epoch->sat[satIndex].validIono = 0;
				return 9999;
			}
			
			
			//Calculate unitary distance between grid points
			unitaryLatDiff = fabs( (ionexPiercePointvector[i].fi - lowLeftpoint[0])/ionex->map[mapTimePosition].dlat );
			unitaryLonDiff = fabs( (ionexPiercePointvector[i].longitude - lowLeftpoint[1])/ionex->map[mapTimePosition].dlon );

			//Interpolate in 2D
			currentHgtInterpolation = TEClowLeft*(1-unitaryLonDiff)*(1-unitaryLatDiff) + TEClowRight*(1-unitaryLonDiff)*unitaryLatDiff + TECupLeft*unitaryLonDiff*(1-unitaryLatDiff) + TECupRight*unitaryLonDiff*unitaryLatDiff;
			currentRMSInterpolation = RMSlowLeft*(1-unitaryLonDiff)*(1-unitaryLatDiff) + RMSlowRight*(1-unitaryLonDiff)*unitaryLatDiff + RMSupLeft*unitaryLonDiff*(1-unitaryLatDiff) + RMSupRight*unitaryLonDiff*unitaryLatDiff;
			
			//Calculate mapping function
			getMappingFunction(&ionexPiercePointvector[i], ionex->baseRadius, currentMapAltitude[i], ionex->mappingFunction, options);

			//Add current height interpolation with previous interpolation
			TECtimeInterpolation[j] += currentHgtInterpolation*ionexPiercePointvector[i].mappingFunction;
			RMStimeInterpolation[j] += currentRMSInterpolation*ionexPiercePointvector[i].mappingFunction;

	
		} //End of height interpolation

		free(ionexPiercePointvector);
		ionexPiercePointvector=NULL;
		
	} //End of time interpolation

	if (onlyLastMapUsed == 1) {TECtimeInterpolation[1] = RMStimeInterpolation[1] = 0;} 
	TECfinalInterpolation = TECtimeInterpolation[0]*(1-unitaryEarlierTimeDiff) + TECtimeInterpolation[1]*unitaryEarlierTimeDiff;
	RMSfinalInterpolation = RMStimeInterpolation[0]*(1-unitaryEarlierTimeDiff) + RMStimeInterpolation[1]*unitaryEarlierTimeDiff;
		


	epoch->sat[satIndex].validIono = 1;
	epoch->sat[satIndex].ionoSigma = RMSfinalInterpolation;	
	//Interpolation is in TECUs

	return TECfinalInterpolation;
}

/*****************************************************************************
 * Name        : FPPPModel
 * Description : Obtains the ionospheric correction using FPPP file data 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * int  satIndex                   I  N/A  Index of the satellite to obtain 
 *                                         the parameters of the model
 * TFPPP *fppp                     I  N/A  Tfppp structure
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (double)         O  TECU Ionex correction in STEC (in 
 *                                         electrons per area unit)
 *                                         9999 is returned when one of the
 *                                         points needed for the interpolation
 *                                         is not set in the IONEX file
 *****************************************************************************/
double FPPPModel (TEpoch *epoch, int satIndex, TFPPPIONEX *fppp, TOptions *options) {
	
	int				i,j;
	int				diffEarlierMap;
	int				diffLaterMap;
	int				diffDaysIonex;
	int				diffDaysEpoch;
	int				diffSecIonex;
	int				diffSecEpoch;
	int				totalSecIonex;
	int				totalSecEpoch;
	int				mapTimePosition;
	int				mapType = 0; // 0->TEC 1->RMS 2->HGT	
	int				ilat,ilt;
	int				onlyLastMapUsed = 0;
	double			unitaryEarlierTimeDiff;
	double			currentHgtInterpolation;
	double			currentRMSInterpolation;
	double			TECfinalInterpolation;
	double			RMSfinalInterpolation;
	double			TEClowLeft,TECupLeft,TEClowRight,TECupRight;
	double			RMSlowLeft,RMSupLeft,RMSlowRight,RMSupRight;
	double			unitaryLtDiff, unitaryLatDiff;
	double			currentMapAltitude[NUMBERFPPPMAPS];
	double			lowLeftpoint[3]; //Phi,Longitude,Altitude
	double			upLeftpoint[3];
	double			lowRightpoint[3];
	double			upRightpoint[3];
	double			TECtimeInterpolation[2];
	double			RMStimeInterpolation[2];
	TPiercePoint	*ionexPiercePointvector = NULL;


	//Auxiliary variables to avoid repetitive calculus and make code more readable
	diffDaysIonex = fppp->endTime.MJDN - fppp->startTime.MJDN;
	diffSecIonex  = diffDaysIonex*NUMBERSECONDSPERDAY;
	totalSecIonex = diffSecIonex + (int)fppp->endTime.SoD ;

	diffDaysEpoch = (int) (epoch->t.MJDN - fppp->startTime.MJDN);
	diffSecEpoch  = diffDaysEpoch*NUMBERSECONDSPERDAY;
	totalSecEpoch = diffSecEpoch + (int)epoch->t.SoD;


	//Check that the IONO map day matches witch RINEX observation day

	if ( epoch->t.MJDN < fppp->startTime.MJDN || totalSecEpoch > totalSecIonex ) {

		//printError ("FPPP is of a different time than the observation RINEX", options);
		epoch->sat[satIndex].validIono = 0;
		return 9999;
	}

	//Look for map with current time. If current time is between two maps, it will start using the earlier one
	//Also, it necessary to check if the interval value is 0. In that case, time interval is variable	
	if (fppp->interval==0)
	{
		mapTimePosition=0;
		do {
			mapTimePosition++;
			if ( ( (mapTimePosition +1) == fppp->numMaps) && ( totalSecEpoch <= totalSecIonex) ) { break; }
			if (mapTimePosition == fppp->numMaps ){
				//printError("No FPPP maps found between current time",options);
				epoch->sat[satIndex].validIono = 0;
				return 9999;
			}
		}while ( (diffSecIonex + (int)fppp->map[mapTimePosition].t.SoD) < totalSecEpoch );

		if ( totalSecEpoch == totalSecIonex ){  //Special case: Only using the last map
			mapTimePosition = fppp->numMaps -1;
			diffEarlierMap = 0;
			diffLaterMap   = 0;
			unitaryEarlierTimeDiff = 0;
			onlyLastMapUsed =1;
		} else {
			mapTimePosition--;
			diffEarlierMap = totalSecEpoch - (fppp->map[mapTimePosition].t.MJDN - fppp->startTime.MJDN)*NUMBERSECONDSPERDAY  - (int)fppp->map[mapTimePosition].t.SoD;
			diffLaterMap = (fppp->map[mapTimePosition+1].t.MJDN - fppp->startTime.MJDN)*NUMBERSECONDSPERDAY + (int)(fppp->map[mapTimePosition+1].t.SoD - totalSecEpoch);
			unitaryEarlierTimeDiff = (double)diffEarlierMap / ((double)(diffEarlierMap + diffLaterMap) );
		}
	} else{

		if ( totalSecEpoch == totalSecIonex ){  //Special case: Only using the last map
			mapTimePosition = fppp->numMaps -1;
			diffEarlierMap = 0;
			diffLaterMap   = 0;
			unitaryEarlierTimeDiff = 0;
			onlyLastMapUsed =1;
		} else {
			diffEarlierMap = totalSecEpoch % fppp->interval;
			diffLaterMap = fppp->interval - diffEarlierMap;
			unitaryEarlierTimeDiff = (double) (diffEarlierMap)/(double)(fppp->interval);
			mapTimePosition = ( totalSecEpoch - diffEarlierMap ) / fppp->interval;
		}

	}
	//It will be necessary to find a Pierce Point for each altitude,
	//therefore needing the initial and ending height, and the 
	//number of steps, which are available in any map, so the first 
	//map will be used to gather this data.
	//The interpolation will be done twice, one for each map time

	TECtimeInterpolation[0]=TECtimeInterpolation[1] = 0;
	RMStimeInterpolation[0]=RMStimeInterpolation[1] = 0;
	
	for(j=0;j < 2 - onlyLastMapUsed;j++) {
		
		mapTimePosition += j;
		

		for(i=0;i < NUMBERFPPPMAPS; i++) {
			
			ionexPiercePointvector = (TPiercePoint*) (realloc(ionexPiercePointvector,sizeof(TPiercePoint)*(i+1)));
			initPiercePoint(&ionexPiercePointvector[i]);
			currentMapAltitude[i] = fppp->map[0].hgt1 + fppp->map[0].dhgt*i; //Stored in Km 


			//Calculate the Iono Pierce Point at current height
			getIonoPiercePoint(epoch, &ionexPiercePointvector[i], satIndex, fppp->baseRadius, currentMapAltitude[i],0);
			//Search for local time position
			ionexPiercePointvector[i].localtime = ionexPiercePointvector[i].longitude + epoch->t.SoD*(1/(double)NUMBERSECONDSPERHOUR)*15.0;
			//Move localtime value to range 0 360
			ionexPiercePointvector[i].localtime = modulo(ionexPiercePointvector[i].localtime+360.0,360);
			

			//Calculate latitude and local time for the four TEC values surrounding current pierce point
			//Given one position, it is first calculated the point which is on the bottom left hand corner of the TEC values surrounding the pierce point
			if (fppp->map[mapTimePosition].nlat==1) {
				ilat=0;
			} else {
				ilat = (int)((ionexPiercePointvector[i].fi - fppp->map[mapTimePosition].lat1)/fppp->map[mapTimePosition].dlat);
			}

			if (fppp->map[mapTimePosition].nlt==1) {
				ilt=0;
			} else if (ionexPiercePointvector[i].localtime >= fppp->map[mapTimePosition].lt2){
				ilt = (int)(fppp->map[mapTimePosition].lt2 /fppp->map[mapTimePosition].dlt);	
			} else {
				ilt = (int)((ionexPiercePointvector[i].localtime - fppp->map[mapTimePosition].lt1)/fppp->map[mapTimePosition].dlt);
			}

			lowLeftpoint[0] = ilat*fppp->map[mapTimePosition].dlat + fppp->map[mapTimePosition].lat1;
			lowLeftpoint[1] = ilt*fppp->map[mapTimePosition].dlt + fppp->map[mapTimePosition].lt1;
			lowLeftpoint[2] = currentMapAltitude[i];
		
			
			if ( lowLeftpoint[0] != fppp->map[mapTimePosition].lat2 ){ //The point is not at the end of the map in latitude
				lowRightpoint[0] = lowLeftpoint[0] + fppp->map[mapTimePosition].dlat;
				lowRightpoint[1] = lowLeftpoint[1];
				lowRightpoint[2] = currentMapAltitude[i];

			}

			if ( lowLeftpoint[1] == fppp->map[mapTimePosition].lt2 ){ //The point is at the end of the map in local time
				upLeftpoint[0] = lowLeftpoint[0];
				upLeftpoint[1] = fppp->map[mapTimePosition].lt1;
				upLeftpoint[2] = currentMapAltitude[i];
			} else {
				upLeftpoint[0] = lowLeftpoint[0];
				upLeftpoint[1] = lowLeftpoint[1] + fppp->map[mapTimePosition].dlt;
				upLeftpoint[2] = currentMapAltitude[i];
			}

			//if ( lowLeftpoint[0] != fppp->map[mapTimePosition].lat2 && lowLeftpoint[1] != fppp->map[mapTimePosition].lt2 ){ //The point is not at the end of the map in latitude and local time
			if ( lowLeftpoint[0] != fppp->map[mapTimePosition].lat2){ //The point is not at the end of the map in latitude and local time
				if ( lowLeftpoint[1] == fppp->map[mapTimePosition].lt2 ){ //The point is at the end of the map in local time
					upRightpoint[0] = lowLeftpoint[0] + fppp->map[mapTimePosition].dlat;
					upRightpoint[1] = fppp->map[mapTimePosition].lt1;
					upRightpoint[2] = currentMapAltitude[i];
				} else {
					upRightpoint[0] = lowLeftpoint[0] + fppp->map[mapTimePosition].dlat;
					upRightpoint[1] = lowLeftpoint[1] + fppp->map[mapTimePosition].dlt;
					upRightpoint[2] = currentMapAltitude[i];
				}			
			}

			//Recover TEC data from the four points
			if( ionexPiercePointvector[i].fi >= fppp->map[mapTimePosition].lat1 && ionexPiercePointvector[i].fi <= fppp->map[mapTimePosition].lat2){
				TEClowLeft = getFPPPValue(&fppp->map[mapTimePosition], mapType, lowLeftpoint[2], lowLeftpoint[0], lowLeftpoint[1]);
				RMSlowLeft = getFPPPValue(&fppp->map[mapTimePosition], 1-mapType, lowLeftpoint[2], lowLeftpoint[0], lowLeftpoint[1]);
			} else { //
				TEClowLeft = 9999;
				epoch->sat[satIndex].validIono = 0;
				return 9999;
			}

			if ( lowLeftpoint[0] != fppp->map[mapTimePosition].lat2 ){ 	
				TEClowRight = getFPPPValue(&fppp->map[mapTimePosition], mapType, lowRightpoint[2], lowRightpoint[0], lowRightpoint[1]); 
				RMSlowRight = getFPPPValue(&fppp->map[mapTimePosition], 1-mapType, lowRightpoint[2], lowRightpoint[0], lowRightpoint[1]); 
			} else {
				TEClowRight = 0;
				RMSlowRight = 0;
			}

			TECupLeft = getFPPPValue(&fppp->map[mapTimePosition], mapType, upLeftpoint[2], upLeftpoint[0], upLeftpoint[1]);
			RMSupLeft = getFPPPValue(&fppp->map[mapTimePosition], 1-mapType, upLeftpoint[2], upLeftpoint[0], upLeftpoint[1]);
			
			if ( lowLeftpoint[0] != fppp->map[mapTimePosition].lat2 ){
				TECupRight = getFPPPValue(&fppp->map[mapTimePosition], mapType, upRightpoint[2], upRightpoint[0], upRightpoint[1]);
				RMSupRight = getFPPPValue(&fppp->map[mapTimePosition], 1-mapType, upRightpoint[2], upRightpoint[0], upRightpoint[1]);
			} else {		
				TECupRight = 0;
				RMSupRight = 0;
			}

			//Check if any value is 9999 (no data for that point)
			if ( TEClowLeft == 9999 || TEClowRight == 9999 || TECupLeft == 9999 || TECupRight == 9999 ) {
				epoch->sat[satIndex].validIono = 0;
				return 9999;
			}

			if ( RMSlowLeft == 9999 || RMSlowRight == 9999 || RMSupLeft == 9999 || RMSupRight == 9999 ) {
				epoch->sat[satIndex].validIono = 0;
				return 9999;
			}
			

			//Calculate unitary distance between grid points
			unitaryLatDiff = fabs( (ionexPiercePointvector[i].fi - lowLeftpoint[0])/fppp->map[mapTimePosition].dlat );
			unitaryLtDiff = fabs( (ionexPiercePointvector[i].localtime - lowLeftpoint[1])/fppp->map[mapTimePosition].dlt );

			//Interpolate in 2D
			currentHgtInterpolation = TEClowLeft*(1-unitaryLtDiff)*(1-unitaryLatDiff) + TEClowRight*(1-unitaryLtDiff)*unitaryLatDiff + TECupLeft*unitaryLtDiff*(1-unitaryLatDiff) + TECupRight*unitaryLtDiff*unitaryLatDiff;
			currentRMSInterpolation = RMSlowLeft*(1-unitaryLtDiff)*(1-unitaryLatDiff) + RMSlowRight*(1-unitaryLtDiff)*unitaryLatDiff + RMSupLeft*unitaryLtDiff*(1-unitaryLatDiff) + RMSupRight*unitaryLtDiff*unitaryLatDiff;
			
			//Calculate mapping function
			getMappingFunction(&ionexPiercePointvector[i], fppp->baseRadius, currentMapAltitude[i], fppp->mappingFunction, options);

			//Add current height interpolation with previous interpolation
			TECtimeInterpolation[j] += currentHgtInterpolation*ionexPiercePointvector[i].mappingFunction;
			RMStimeInterpolation[j] += currentRMSInterpolation*ionexPiercePointvector[i].mappingFunction;

	
		} //End of height interpolation

		free(ionexPiercePointvector);
		ionexPiercePointvector=NULL;
		
	} //End of time interpolation

	if (onlyLastMapUsed == 1) {TECtimeInterpolation[1]=RMStimeInterpolation[1]= 0;} 
	TECfinalInterpolation = TECtimeInterpolation[0]*(1-unitaryEarlierTimeDiff) + TECtimeInterpolation[1]*unitaryEarlierTimeDiff;
	RMSfinalInterpolation = RMStimeInterpolation[0]*(1-unitaryEarlierTimeDiff) + RMStimeInterpolation[1]*unitaryEarlierTimeDiff;
	

	//Interpolation is in TECUs

	if (RMSfinalInterpolation > options->ionoRMS) {
		epoch->sat[satIndex].validIono = 0;
		TECfinalInterpolation = 9999;
	} else {
		epoch->sat[satIndex].validIono = 1;
		epoch->sat[satIndex].ionoSigma = RMSfinalInterpolation;
	}

	return TECfinalInterpolation;
}

/*****************************************************************************
 * Name        : NeQuickfunctionCall
 * Description : Obtains the ionospheric correction using NeQuick model.
 *               This function will call NeQuick's program
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TGNSSproducts  *products        I  N/A  Ephemerides products to obtain the
 *                                         parameters for the model
 * int  satIndex                   I  N/A  Index of the satellite to obtain
 *                                         the parameters of the model
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (double)         O  TECU NeQuick correction in STEC (in
 *                                         electrons per area unit)
 *****************************************************************************/
double NeQuickfunctionCall (TEpoch *epoch, int satIndex, TGNSSproducts *products, TOptions *options) {

	int32_t ret;
	NeQuickG_handle nequick = NEQUICKG_INVALID_HANDLE;

	ret = NeQuickG.init(&nequick);
	if (ret != NEQUICK_OK) {
		return GLAB_TEC_VALUE_NOT_VALID;
	}

	{
		double_t coeff[NEQUICKG_AZ_COEFFICIENTS_COUNT];
		coeff[0] = (double_t)products->BRDC->ai[0];
		coeff[1] = (double_t)products->BRDC->ai[1];
		coeff[2] = (double_t)products->BRDC->ai[2];
		if (NeQuickG.set_solar_activity_coefficients(
			nequick,
			coeff, NEQUICKG_AZ_COEFFICIENTS_COUNT) != NEQUICK_OK) {
				NeQuickG.NeQuickG_close(nequick);
				return GLAB_TEC_VALUE_NOT_VALID;
			}
	}

	{
		// static variables are shared between threads
		// (as they are saved in the data segment).
		// to avoid race conditions, we need to set the directive
		// '#pragma omp threadprivate()'
		// directive to make OpenMP create a local (static) copy for
		// each thread

		// month and prevDay initialized to different values to
		// force the first time to calculate month
		static uint8_t month = 0;
		#pragma omp threadprivate(month)
		static int prevDay = 1;
		#pragma omp threadprivate(prevDay)

		double_t UTC_hour = epoch->t.SoD / 3600;

		// Calculate month if day has changed
		if (prevDay != epoch->t.MJDN) {
			double auxa;
			double auxb;
			double auxc;
			double auxd;
			double auxe;
			prevDay = epoch->t.MJDN;
			auxa = (int) (epoch->t.MJDN + JULIANDAYDIFF + 0.5);
			auxb = auxa + 1537;
			auxc = (int)((auxb - 122.1) / 365.25);
			auxd = (int) (365.25 * auxc);
			auxe = (int) ((auxb-auxd)/30.6001);

			month = (uint8_t)(auxe - 1 - (12 * (int)(auxe / 14)));
		}

		if (NeQuickG.set_time(nequick, month, UTC_hour) != NEQUICK_OK) {
			NeQuickG.NeQuickG_close(nequick);
			return GLAB_TEC_VALUE_NOT_VALID;
		}
	}

	{
		double_t latitude_degree =
			(double_t)epoch->receiver.aproxPositionNEU[0]*r2d;
		double_t longitude_degree =
			(double_t)epoch->receiver.aproxPositionNEU[1]*r2d;
		double_t height_m = (double_t)epoch->receiver.aproxPositionNEU[2];
		if (NeQuickG.set_receiver_position(
			nequick, longitude_degree, latitude_degree, height_m) != NEQUICK_OK) {
			NeQuickG.NeQuickG_close(nequick);
			return GLAB_TEC_VALUE_NOT_VALID;
		}
	}

	{
		double pdSatLLHdeg[NEQUICKG_WGS_84_ELLIPSOIDAL_COORDINATES_COUNT];
		XYZ2NEU (epoch->sat[satIndex].position, pdSatLLHdeg);
		// XYZ2NEU returns position in order latitude,longitude,height,
		// the same as NeQuick, but in radians.
		// We need to transform to degrees
		double_t latitude_degree = (double_t)pdSatLLHdeg[0]*r2d;
		double_t longitude_degree = (double_t)pdSatLLHdeg[1]*r2d;
		double_t height_m = (double_t)pdSatLLHdeg[2];
		if (NeQuickG.set_satellite_position(
			nequick, longitude_degree, latitude_degree, height_m) != NEQUICK_OK) {
			NeQuickG.NeQuickG_close(nequick);
			return GLAB_TEC_VALUE_NOT_VALID;
		}
	}

	{
		double_t tec_value;
		if (NeQuickG.get_total_electron_content(nequick, &tec_value) != NEQUICK_OK) {
			tec_value = GLAB_TEC_VALUE_NOT_VALID;
		}
		NeQuickG.NeQuickG_close(nequick);
		return (double)tec_value;
	}
}
/*****************************************************************************
 * Name        : gravitationalDelayCorrection
 * Description : Obtains the gravitational delay correction for the effect of 
 *               general relativity (red shift) to the GPS signal
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *receiverPosition       I  m    Position of the receiver
 * double  *satellitePosition      I  m    Position of the satellite
 * Returned value (double)         O  m    Gravitational delay correction
 *****************************************************************************/
double gravitationalDelayCorrection (double *receiverPosition, double *satellitePosition) {
	double	receiverModule;
	double	satelliteModule;
	double	distance;
	
	receiverModule = sqrt(receiverPosition[0]*receiverPosition[0] + receiverPosition[1]*receiverPosition[1] + receiverPosition[2]*receiverPosition[2]);
	satelliteModule = sqrt(satellitePosition[0]*satellitePosition[0] + satellitePosition[1]*satellitePosition[1] + satellitePosition[2]*satellitePosition[2]);
	distance = sqrt((satellitePosition[0]-receiverPosition[0])*(satellitePosition[0]-receiverPosition[0]) +
					(satellitePosition[1]-receiverPosition[1])*(satellitePosition[1]-receiverPosition[1]) +
					(satellitePosition[2]-receiverPosition[2])*(satellitePosition[2]-receiverPosition[2]));
	
	return 2.0*MU/(c0*c0) * log((satelliteModule+receiverModule+distance)/(satelliteModule+receiverModule-distance));
}

/*****************************************************************************
 * Name        : getTGDfromDCB
 * Description : Returns the Total Group Delay from a DCB source. It allows
 *               specifying the source and final measurements (NA for absolute)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTGDdata  *tgdData              I  N/A  TTGDdata structure to extract the data
 * TReceiver  *rec                 I  N/A  Receiver data
 * GNSSystem  GNSS                 I  N/A  GNSS enumerator of the satellite
 * int  PRN                        I  N/A  PRN of the satellite
 * TTime  *t                       I  N/A  Reference time
 * enum MeasurementType  measFrom  I  N/A  Source measurement (from)
 * enum MeasurementType  measTo    I  N/A  Final measurement (to)
 * double  *dcb                    O    m  Total DCB
 * int  *retDCB                    O  N/A  Status of DCB seek
 *                                          0 => Failed to find proper DCBs
 *                                          1 => Fully OK (all DCBs found)
 * int  *retDCBC1P1                O  N/A  Status of DCB seek for C1-P1
 *                                         -1 => No info
 *                                          0 => Failed to find proper DCBs
 *                                          1 => OK
 *****************************************************************************/
void getTGDfromDCB (TTGDdata *tgdData, TReceiver *rec, enum GNSSystem GNSS, int PRN, TTime *t, enum MeasurementType measFrom, enum MeasurementType measTo, double *dcb, int *retDCB, int *retDCBC1P1) {
	int			i;
	int			check;
	double		factor;
	double		dcbAux[2];
	int			retDCB_aux;
	int			retDCBC1P1_aux;
	
//	if (tgdData->tgdSource!=tgdDCB) {
//    *retDCB = 0;
//    *retDCBC1P1 = -1;
//    return;
//  }
	
	if (measFrom==measTo) {
		*dcb = 0;
			*retDCB = 1;
		 *retDCBC1P1 = -1;
		return;
	}
	
	if (whatIs(measFrom)==CarrierPhase) {
		*dcb = 0;
			*retDCB = 1;
		*retDCBC1P1 = -1;
		return;
	}
	
	// This should be improved for anything that is not GPS
	// Usable measurements: C1C C1P C2P NA
	if (measFrom!=C1C && measFrom!=C1P && measFrom!=C2P && measFrom!=NA) {
			*retDCB = 0;
			*retDCBC1P1 = -1;
			return;
	}
	if (measTo!=C1C && measTo!=C1P && measTo!=C2P && measTo!=NA) {
		*retDCB = 0;
			*retDCBC1P1 = -1;
		return;
	}
	
	// Check if there is a direct path
	for (i=0;i<tgdData->DCB->n;i++) {
		check = 0;
		// Measurements checking
		if (tgdData->DCB->block[i].measFrom == measFrom && tgdData->DCB->block[i].measTo == measTo) {
			check = 1;
			factor = 1;
		} else if (tgdData->DCB->block[i].measFrom == measTo && tgdData->DCB->block[i].measTo == measFrom) {
			check = 1;
			factor = -1;
		}

		if (check) {
			// Time checking
			if (tdiff(t,&tgdData->DCB->block[i].startTime)>=0 && tdiff(t,&tgdData->DCB->block[i].endTime)<=0) {
				// Availability checking
				if (tgdData->DCB->block[i].available[GNSS][PRN]) {
					*dcb = -tgdData->DCB->block[i].dcb[GNSS][PRN] * factor;
					if (rec->recType == rtCROSS) { // Additional correction for Cross-correlation receivers
						if (measFrom == C2P || measTo == C2P) { 
							getTGDfromDCB(tgdData, rec ,GNSS, PRN, t, C1C, C1P, &dcbAux[0], &retDCB_aux, &retDCBC1P1_aux);
							if (retDCB_aux) {
								if (measFrom == C2P) *dcb += dcbAux[0];
								else *dcb -= dcbAux[0];
							} else {
								*retDCB = 0;
								*retDCBC1P1 = -1;
								return;
							}
						}
					}
					*retDCB = 1;
					*retDCBC1P1 = -1;
					return;
				}
			}
		}
	}
	
	// If no direct path was found [To be improved]
	if (measFrom==C1C && measTo==NA) {
		getTGDfromDCB(tgdData, rec, GNSS, PRN, t, C1C, C1P, &dcbAux[0], &retDCB_aux, &retDCBC1P1_aux);
		if (retDCB_aux)  {
			getTGDfromDCB(tgdData, rec, GNSS, PRN, t, C1P, NA, &dcbAux[1], &retDCB_aux, &retDCBC1P1_aux);
			if (retDCB_aux) {
				*dcb = dcbAux[0] + dcbAux[1];
				*retDCB = 1;
				*retDCBC1P1 = 1;
				return;
			} else {
				*dcb = dcbAux[0];
				*retDCB = 0;
				*retDCBC1P1 = 1;
				return;
			}
		  	*retDCB = 0;
			*retDCBC1P1 = 0;
		}
	} else if (measFrom==C2P && measTo==NA) {
		getTGDfromDCB (tgdData, rec, GNSS, PRN, t, C2P, C1P, &dcbAux[0], &retDCB_aux, &retDCBC1P1_aux);
		if (retDCB_aux)  {
			getTGDfromDCB (tgdData, rec, GNSS, PRN, t, C1P, NA, &dcbAux[1], &retDCB_aux, &retDCBC1P1_aux);
			if (retDCB_aux) {
				*dcb = dcbAux[0] + dcbAux[1];
				*retDCB = 1;
				*retDCBC1P1 = -1;
				return;
			} else {
				*dcb = dcbAux[0];
				*retDCB = 0;
				*retDCBC1P1 = -1;
				return;
			}
		}
	}
	*dcb = 0;
	*retDCB = 0;
	return;
}

/*****************************************************************************
 * Name        : TGDCorrectionBRDC
 * Description : Obtains the TGD correction (Total Group Delay biases) from a 
 *               RINEX navigation file
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * int  satIndex                   I  N/A  Index of the satellite to obtain 
 *                                         the correction
 * int SBASIOD                     I  N/A  SBAS IOD for long term corrections                                       
 * TTime  *t                       I  N/A  Reference time
 * TBRDCproducts  *products        I  N/A  Ephemerides products to obtain the 
 *                                         parameters for the model
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (double)         O  mHz2 TGD correction (to apply it to a 
 *                                         specific frequency it must be divided 
 *                                         by f^2)
 *****************************************************************************/
double TGDCorrectionBRDC (TEpoch *epoch, int satIndex, int SBASIOD, TTime *t, TBRDCproducts *prod, TOptions *options) {
	TBRDCblock		*block;
	double			correction;

	if (prod == NULL) return -999999.;

	block = selectBRDCblock(prod,t,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,SBASIOD,options);

	if (block==NULL) return -999999.;

	correction = block->TGD*c0*GPSf1*GPSf1;
	return correction;
}

/*****************************************************************************
 * Name        : TGDCorrectionIONEX
 * Description : Obtains the TGD correction (Total Group Delay biases) from a 
 *               IONEX file
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * int  satIndex                   I  N/A  Index of the satellite to obtain 
 *                                         the correction
 * TIonexDCB *ionexDCB             I  N/A  DCB data in IONEX file
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (double)         O  mHz2 DCB correction (to apply it to a 
 *                                         specific frequency it must be divided 
 *                                         by f^2)
 *****************************************************************************/
double TGDCorrectionIONEX (TEpoch *epoch, int satIndex,TIonexDCB *ionexDCB,TOptions *options) {
	double dcb;

	dcb = ionexDCB->DCB[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];

	if(dcb==-999999.) {
			return -999999.;
	} else if (epoch->sat[satIndex].GNSS==GPS) {
			return -1*dcb*ALPHAGPS12*GPSf1*GPSf1*c0*1E-9;
	} else {
	//Update for Galileo and other constellations !!
			return -999999.;
	}
}

/*****************************************************************************
 * Name        : TGDCorrectionFPPP
 * Description : Obtains the TGD correction (Total Group Delay biases) from a 
 *               FPPP file
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * int  satIndex                   I  N/A  Index of the satellite to obtain 
 *                                         the correction
 * TFPPPDCB *fpppDCB               I  N/A  DCB data in FPPP file
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (double)         O  mHz2 DCB correction (to apply it to a 
 *                                         specific frequency it must be divided 
 *                                         by f^2)
 *****************************************************************************/
double TGDCorrectionFPPP (TEpoch *epoch, int satIndex,TFPPPDCB *fpppDCB,TOptions *options) {
	double dcb;


	dcb = fpppDCB->IFB[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];

	if(dcb==-999999.) {
		return -999999.;
	} else if (epoch->sat[satIndex].GNSS==GPS) {
		return -1*dcb*ALPHAGPS12*GPSf1*GPSf1;
	} else {
	//Update for Galileo and other constellations !!
		return -999999.;
	}
}

/*****************************************************************************
 * Name        : TGDCorrection
 * Description : Obtains the TGD correction (Total Group Delay biases) from a 
 *               TTGDdata structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * int  satIndex                   I  N/A  Index of the satellite to obtain 
 *                                         the correction
 * TTime  *t                       I  N/A  Reference time
 * TTGDdata  *tgdData              I  N/A  Source of the TGD data
 * enum MeasurementType  meas      I  N/A  Measurement
 * int SBASIOD                     I  N/A  SBAS IOD for long term corrections                                       
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (double)         O  mHz2 TGD correction (to apply it to a 
 *                                         specific frequency it must be divided 
 *                                         by f^2)
 *****************************************************************************/
double TGDCorrection (TEpoch *epoch, int satIndex, TTime *t, enum MeasurementType meas, int SBASIOD, TTGDdata *tgdData,TOptions *options) {
	double	correction1,correction2=0.;
	double	lambda;
	int		retDCB, retDCBC1P1;
	
	if (whatIs(meas)==CarrierPhase) return 0;
	
	if (tgdData->p1p2dcbModel == p1p2RINEX) {
		correction2 = TGDCorrectionBRDC(epoch,satIndex,SBASIOD,t,tgdData->BRDC,options);
		if(correction2==-999999.) {
			//No DCB P1-P2 available
			correction2=0.;
			epoch->sat[satIndex].hasDCBs=0;
		}
		lambda = getLambda(epoch->sat[satIndex].GNSS,meas);
		correction2 = correction2 * lambda * lambda / (c0*c0);
	} else if (tgdData->p1p2dcbModel == p1p2DCB) {
		if (meas==C1P || meas==C2P || meas==C1C) {
			if (meas==C1C) {
				getTGDfromDCB(tgdData, &epoch->receiver, epoch->sat[satIndex].GNSS, epoch->sat[satIndex].PRN, t, C1P, NA, &correction2, &retDCB, &retDCBC1P1);
			} else {
				getTGDfromDCB(tgdData, &epoch->receiver, epoch->sat[satIndex].GNSS, epoch->sat[satIndex].PRN, t, meas, NA, &correction2, &retDCB, &retDCBC1P1);
			}
			if (retDCB==0) epoch->sat[satIndex].hasDCBs = 0;
			if (retDCBC1P1==0) epoch->sat[satIndex].hasDCBsofC1P1 = 0;
		}
	} else if (tgdData->p1p2dcbModel == p1p2IONEX) {
		correction2 = TGDCorrectionIONEX(epoch,satIndex,&tgdData->ionexDCB,options);
		if(correction2==-999999.) {
			//No DCB P1-P2 available
			correction2=0.;
			epoch->sat[satIndex].hasDCBs=0;
		}
		lambda = getLambda(epoch->sat[satIndex].GNSS,meas);
		correction2 = correction2 * lambda * lambda / (c0*c0);
	} else if (tgdData->p1p2dcbModel == p1p2FPPP) {
		correction2 = TGDCorrectionFPPP(epoch,satIndex,&tgdData->fpppDCB,options);
		if(correction2==-999999.) {
			//No DCB P1-P2 available
			correction2=0.;
			epoch->sat[satIndex].hasDCBs=0;
		}
		lambda = getLambda(epoch->sat[satIndex].GNSS,meas);
		correction2 = correction2 * lambda * lambda / (c0*c0);
	} else {
		correction2 = 0;
		epoch->sat[satIndex].hasDCBs = 1;
		epoch->sat[satIndex].hasDCBsofC1P1 = 1;
	}

	if (tgdData->p1c1dcbModel == p1c1STRICT) {
			if (meas==C1C) {
				getTGDfromDCB(tgdData, &epoch->receiver, epoch->sat[satIndex].GNSS, epoch->sat[satIndex].PRN, t, C1C, C1P, &correction1, &retDCB, &retDCBC1P1);
				if (retDCB==0) epoch->sat[satIndex].hasDCBs = 0;
				if (retDCBC1P1==0) epoch->sat[satIndex].hasDCBsofC1P1 = 0;
			} else {
				correction1 = 0;
			}
	} else {
			correction1 = 0;
	}

	return correction1 + correction2;
}

/*****************************************************************************
 * Name        : fillSolidTideDisplacement
 * Description : Fills the solid tide displacement of the receiver (XYZ) in the 
 *               TEpoch structure. Model extracted from IERS Conventions 2003, 
 *               Chapter 7 for solid tides of degree 2 and 3
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 *****************************************************************************/
void fillSolidTideDisplacement (TEpoch *epoch) {
	const double	h0 =  0.6078;	// Love number h0 of degree 2
	const double	h2 = -0.0006;	// Love number h2 of degree 2
	const double	h3 =  0.292;	// Love number of degree 3
	const double	l0 =  0.0847;	// Shida number l0 of degree 2
	const double	l2 =  0.0002;	// Shida number l0 of degree 2
	const double	l3 =  0.015;	// Shide number of degree 3 
	const double	MS2E = 332946.0;	// Ratio of mass Sun to Earth
	const double	MM2E = 0.01230002;	// Ratio of mass Moon to Earth
	double			RecPos2SunPos;
	double			RecPos2MoonPos;
	double			scalarSunRec;
	double			scalarMoonRec;
	double			auxSun[3];
	double			auxMoon[3];
	double			h;
	double			l;
	double			sunPosition[3];
	double			sunDistance;
	double			sunPosUni[3];
	double			moonPosition[3];
	double			moonDistance;
	double			moonPosUni[3];
	double			receiverDistance;
	double			receiverPosUni[3];
	int				i;
	
	
	h = h0 + h2*(3*sin(epoch->receiver.aproxPositionNEU[0])*sin(epoch->receiver.aproxPositionNEU[0]) - 1)/2;
	l = l0 + l2*(3*sin(epoch->receiver.aproxPositionNEU[0])*sin(epoch->receiver.aproxPositionNEU[0]) - 1)/2;

	// Find Sun position
	findSun (&epoch->t, sunPosition);
	
	// Find Moon position
	findMoon(&epoch->t, moonPosition);

	sunDistance = sqrt(sunPosition[0]*sunPosition[0] + sunPosition[1]*sunPosition[1] + sunPosition[2]*sunPosition[2]);
	moonDistance = sqrt(moonPosition[0]*moonPosition[0] + moonPosition[1]*moonPosition[1] + moonPosition[2]*moonPosition[2]);
	receiverDistance = sqrt(epoch->receiver.aproxPosition[0]*epoch->receiver.aproxPosition[0] + epoch->receiver.aproxPosition[1]*epoch->receiver.aproxPosition[1] + epoch->receiver.aproxPosition[2]*epoch->receiver.aproxPosition[2]);

	for (i=0;i<3;i++) {
		sunPosUni[i] = sunPosition[i] / sunDistance;
		moonPosUni[i] = moonPosition[i] / moonDistance;
		receiverPosUni[i] = epoch->receiver.aproxPosition[i] / receiverDistance;
	}
	receiverDistance /= 1000; // To transform from m to km
	
	// Computing scalar products
	scalarSunRec = scalarProd(sunPosUni,receiverPosUni);
	scalarMoonRec = scalarProd(moonPosUni,receiverPosUni);
	
	// Computing auxiliar vectors
	for (i=0;i<3;i++) {
		auxSun[i] = sunPosUni[i] - scalarSunRec*receiverPosUni[i];
		auxMoon[i] = moonPosUni[i] - scalarMoonRec*receiverPosUni[i];
	}
	
	// Distance relations	
	RecPos2SunPos = receiverDistance/sunDistance;
	RecPos2MoonPos = receiverDistance/moonDistance;
	
	// Computing displacements
	for (i=0;i<3;i++) {
		epoch->solidTideDisplacement[i] = 0;
		
		// Degree 2
		epoch->solidTideDisplacement[i] += (
				MS2E * RecPos2SunPos * RecPos2SunPos * RecPos2SunPos * receiverDistance *( 	// Sun
					h * receiverPosUni[i] * (3.0/2.0*scalarSunRec*scalarSunRec - 1.0/2.0) +
					3.0 * l * scalarSunRec * auxSun[i]) +
				MM2E * RecPos2MoonPos * RecPos2MoonPos * RecPos2MoonPos * receiverDistance *( 	// Moon
					h * receiverPosUni[i] * (3.0/2.0*scalarMoonRec*scalarMoonRec - 1.0/2.0) +
					3.0 * l * scalarMoonRec * auxMoon[i])
				) * 1000; // To transform from km to m
		
		// Degree 3
		epoch->solidTideDisplacement[i] += (
				MM2E * RecPos2MoonPos * RecPos2MoonPos * RecPos2MoonPos * RecPos2MoonPos * receiverDistance *(   // Only Moon 
					h3 * receiverPosUni[i] * (5.0/2.0*scalarMoonRec*scalarMoonRec*scalarMoonRec - 3.0/2.0*scalarMoonRec) +
					l3 * (15.0/2.0*scalarMoonRec*scalarMoonRec - 3.0/2.0) * auxMoon[i])
				) * 1000; // To transform from km to m
	}
}

/*****************************************************************************
 * Name        : solidTidesCorrection
 * Description : Obtains the solid tides correction from the solidTideDisplacement 
 *               at TEpoch structure. It projects the XYZ displacement into the
 *               Line-of-Sight of the specified satellite
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * int  satIndex                   I  N/A  Index of the satellite
 * Returned value (double)         O  m    Solid tides correction
 *****************************************************************************/
double solidTidesCorrection (TEpoch *epoch, int satIndex) {
	return -scalarProd(epoch->sat[satIndex].LoS,epoch->solidTideDisplacement);
}

/*****************************************************************************
 * Name        : fillGeometricDistance
 * Description : Fills the geometric distance in the TEpoch structure from 
 *               the receiver and satellite positions
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 * int  satIndex                   I  N/A  Index of the satellite
 *****************************************************************************/
void fillGeometricDistance (TEpoch *epoch,int satIndex) {
	epoch->sat[satIndex].geometricDistance = 
			sqrt((epoch->receiver.aproxPosition[0]-epoch->sat[satIndex].position[0])*(epoch->receiver.aproxPosition[0]-epoch->sat[satIndex].position[0]) +
				 (epoch->receiver.aproxPosition[1]-epoch->sat[satIndex].position[1])*(epoch->receiver.aproxPosition[1]-epoch->sat[satIndex].position[1]) +
				 (epoch->receiver.aproxPosition[2]-epoch->sat[satIndex].position[2])*(epoch->receiver.aproxPosition[2]-epoch->sat[satIndex].position[2]));
}

/*****************************************************************************
 * Name        : fillMeasurementWeights
 * Description : Fills the measurement weights in the TEpoch structure from 
 *               the options
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 * int  satIndex                   I  N/A  Index of the satellite
 * double SBASsigma                I  m^2  Sigma provided by SBAS corrections
 * double DGNSSsigma               I  m^2  Sigma computed with DGNSS corrections
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A   0 -> All weights computed
 *                                         <0 -> SNR was missing for a measurement
 *                                               The returned value is the measurement
 *                                               number (type enum MeasurementType)
 *                                               but with negative number
 *****************************************************************************/
int fillMeasurementWeights (TEpoch *epoch, int satIndex, double SBASsigma, double DGNSSsigma, TOptions *options) {
	int						i;
	int						PRN=epoch->sat[satIndex].PRN;
	int						ind,freq;
	enum GNSSystem			GNSS=epoch->sat[satIndex].GNSS;
	double					lambda;
	double					ionosigma=0.;
	double					SNR,SNRi,SNRj;
	double					Constantvalue;
	enum MeasurementType	meas;

	for (i=0;i<options->totalFilterMeasurements;i++) {
		
		if (options->weightMode[GNSS][PRN][i]<=SNRElevWeight) {
			//SBAS and DGNSS sigmas not used
			SBASsigma=DGNSSsigma=0.; 
			// Add IONEX or F-PPP ionosphere sigma in the measurement weight
			if ( (options->ionoModel == IONEX || options->ionoModel == FPPP || options->ionoModel == SBASiono) && options->useSigmaIono==1 ) {
				meas=options->measurement[i];
				if(meas>=ENDMEAS) lambda=0;
				else lambda = getLambda(GNSS,meas);
				ionosigma = pow(epoch->sat[satIndex].ionoSigma*40.3*(lambda*lambda)/(c0*c0)*pow(10,16),2);
			}	
		} else if (options->weightMode[GNSS][PRN][i]>=DGNSSFixedWeight) {
			//SBAS sigma not used
			SBASsigma=0.;
			// Add IONEX or F-PPP ionosphere sigma in the measurement weight  if it is not a pure DGNSS solution (in DGNSS iono model is not applied)
			if ( (options->ionoModel == IONEX || options->ionoModel == FPPP || options->ionoModel == SBASiono) && options->useSigmaIono==1 && options->solutionMode < DGNSSMode  ) {
				meas=options->measurement[i];
				if(meas>=ENDMEAS) lambda=0;
				else lambda = getLambda(GNSS,meas);
				ionosigma = pow(epoch->sat[satIndex].ionoSigma*40.3*(lambda*lambda)/(c0*c0)*pow(10,16),2);
			}
		} else if (options->weightMode[GNSS][PRN][i]>=SBASFixedWeight) {
			//DGNSS sigma not used
			DGNSSsigma=0.;
		}

		switch(options->weightMode[GNSS][PRN][i]) {
			case SBASOnlyWeight:
				epoch->sat[satIndex].measurementWeights[i] = sqrt(SBASsigma);
				break;
			case DGNSSOnlyWeight:
				// Add IONEX or F-PPP ionosphere sigma in the measurement weight if it is not a pure DGNSS solution (in DGNSS iono model is not applied)
				if ( (options->ionoModel == IONEX || options->ionoModel == FPPP || options->ionoModel == SBASiono) && options->useSigmaIono==1 && options->solutionMode < DGNSSMode  ) {
					meas=options->measurement[i];
					if(meas>=ENDMEAS) lambda=0;
					else lambda = getLambda(GNSS,meas);
					ionosigma = pow(epoch->sat[satIndex].ionoSigma*40.3*(lambda*lambda)/(c0*c0)*pow(10,16),2);
				} else {
					ionosigma=0;
				}
				epoch->sat[satIndex].measurementWeights[i] = sqrt(DGNSSsigma+ionosigma);
				break;
			case FixedWeight: case SBASFixedWeight: case DGNSSFixedWeight:
				if (options->WeightConstantsValues[GNSS][PRN][i][0]==-2) {
					//Use URA value
					Constantvalue=epoch->sat[satIndex].URAValue*epoch->sat[satIndex].URAValue;
				} else {
					Constantvalue=options->WeightConstantsValues[GNSS][PRN][i][0]*options->WeightConstantsValues[GNSS][PRN][i][0];
				}
				epoch->sat[satIndex].measurementWeights[i] = sqrt(Constantvalue+SBASsigma+DGNSSsigma+ionosigma);	
				break;
			case ElevationWeight: case SBASElevWeight: case DGNSSElevWeight:
				if (options->WeightConstantsValues[GNSS][PRN][i][0]==-2) {
					//Use URA value
					Constantvalue=epoch->sat[satIndex].URAValue;
				} else {
					Constantvalue=options->WeightConstantsValues[GNSS][PRN][i][0];
				}
				epoch->sat[satIndex].measurementWeights[i] = sqrt(pow(Constantvalue + options->WeightConstantsValues[GNSS][PRN][i][1]*exp(-epoch->sat[satIndex].elevation/options->WeightConstantsValues[GNSS][PRN][i][2]),2)+SBASsigma+DGNSSsigma+ionosigma);
				break;
			case Elevation2Weight: case SBASElev2Weight: case DGNSSElev2Weight:
				if (options->WeightConstantsValues[GNSS][PRN][i][0]==-2) {
					//Use URA value
					Constantvalue=epoch->sat[satIndex].URAValue*epoch->sat[satIndex].URAValue;
				} else {
					Constantvalue=options->WeightConstantsValues[GNSS][PRN][i][0];
				}
				if (fabs(epoch->sat[satIndex].elevation)<MIN_ELEVATION_WEIGHT) {
					//This to avoid dividing by 0 or by a value very close to 0
					epoch->sat[satIndex].measurementWeights[i] = SIGMA_INF;
				} else {
					epoch->sat[satIndex].measurementWeights[i] = sqrt(Constantvalue + options->WeightConstantsValues[GNSS][PRN][i][1]/(pow(sin(epoch->sat[satIndex].elevation),2))+SBASsigma+DGNSSsigma+ionosigma);
				}
				break;
			default:
				//All cases involving the SNR
				if (options->measurement[i]<ENDMEAS || options->measurement[i]==G1C || options->measurement[i]==G1P 
						|| options->measurement[i]==G2C || options->measurement[i]==G2P) {
					//It is a single measurement or a graphic combination
					if ( options->measurement[i]==G1C || options->measurement[i]==G1P) {
						freq=1;
					} else if (options->measurement[i]==G2C || options->measurement[i]==G2P) {
						freq=2;
					} else {
						freq = getFrequencyInt(options->measurement[i]);	
					}
					if (epoch->measOrder[GNSS].hasSNRmeas==1) {
						//SNR as a measurement is available
						SNR=epoch->sat[satIndex].meas[epoch->measOrder[GNSS].SNRmeaspos[freq]].value;
					} else {
						if (freq==1) {
							meas=L1P;
						} else {
							meas=L2P;
						}
						ind=epoch->measOrder[GNSS].meas2Ind[meas];

						if (epoch->sat[satIndex].meas[ind].hasSNRflag==1) {
							SNR=epoch->sat[satIndex].meas[ind].SNRdBHz;
						} else {
							//No SNR available for this measurement. Unselect satellite
							return -meas;
						}
					}
				} else if (options->measurement[i]>ENDMEAS) { 
					//Combination (excluding graphic combinations)
					//First get the SNR values
					if (epoch->measOrder[GNSS].hasSNRmeas==1) {
						//SNR as a measurement is available
						SNRi=epoch->sat[satIndex].meas[epoch->measOrder[GNSS].SNRmeaspos[1]].value;
						SNRj=epoch->sat[satIndex].meas[epoch->measOrder[GNSS].SNRmeaspos[2]].value;
					} else {
						ind=epoch->measOrder[GNSS].meas2Ind[L1P];
						if (epoch->sat[satIndex].meas[ind].hasSNRflag==1) {
							SNRi=epoch->sat[satIndex].meas[ind].SNRdBHz;
						} else if (options->SNRweightComb[GNSS][PRN][i]!=SNRWeightCombj){
							//No SNR available for this measurement. Unselect satellite
							//We avoid discarding the satellite in the only case we are not using this SNR (which is SNRWeightCombj)
							return -L1P;
						}
						ind=epoch->measOrder[GNSS].meas2Ind[L2P];
						if (epoch->sat[satIndex].meas[ind].hasSNRflag==1) {
							SNRj=epoch->sat[satIndex].meas[ind].SNRdBHz;
						} else if (options->SNRweightComb[GNSS][PRN][i]!=SNRWeightCombi) {
							//No SNR available for this measurement. Unselect satellite
							//We avoid discarding the satellite in the only case we are not using this SNR (which is SNRWeightCombi)
							return -L2P;
						}
					}

					switch(options->SNRweightComb[GNSS][PRN][i]) {
						case SNRWeightCombi:
							SNR=SNRi;
							break;
						case SNRWeightCombj:
							SNR=SNRj;
							break;
						case SNRWeightCombMax:
							if (SNRi>SNRj) SNR=SNRi;
							else SNR=SNRj;
							break;
						case SNRWeightCombMin:
							if (SNRi>SNRj) SNR=SNRj;
							else SNR=SNRi;
							break;
						case SNRWeightCombMean:
							SNR=0.5*(SNRi+SNRj);
							break;
						case SNRWeightCombUser:
							SNR=SNRi*options->SNRweightCombVal[GNSS][PRN][i][0]+SNRj*options->SNRweightCombVal[GNSS][PRN][i][1];
							break;
						default:
							break;
					}	
				}
				//This switch is nested in order to separate the cases involving the SNR
				switch(options->weightMode[GNSS][PRN][i]) {
					case SNRWeight: case SBASSNRWeight: case DGNSSSNRWeight:
						if (options->WeightConstantsValues[GNSS][PRN][i][0]==-2) {
							//Use URA value
							Constantvalue=epoch->sat[satIndex].URAValue*epoch->sat[satIndex].URAValue;
						} else {
							Constantvalue=options->WeightConstantsValues[GNSS][PRN][i][0];
						}
						epoch->sat[satIndex].measurementWeights[i] = sqrt(Constantvalue + options->WeightConstantsValues[GNSS][PRN][i][1]*pow(10,-0.1*SNR)+SBASsigma+DGNSSsigma+ionosigma);
						break;
					case SNRElevWeight: case SBASSNRElevWeight: case DGNSSSNRElevWeight:
						if (options->WeightConstantsValues[GNSS][PRN][i][0]==-2) {
							//Use URA value
							Constantvalue=epoch->sat[satIndex].URAValue*epoch->sat[satIndex].URAValue;
						} else {
							Constantvalue=options->WeightConstantsValues[GNSS][PRN][i][0];
						}
						//The absolute value is for computing sigmas for a LEO during convergence (elevation will be negative)
						if (fabs(epoch->sat[satIndex].elevation)<MIN_ELEVATION_WEIGHT) {
							//This to avoid dividing by 0 or by a value very close to 0
							epoch->sat[satIndex].measurementWeights[i] = SIGMA_INF;
						} else {
							epoch->sat[satIndex].measurementWeights[i] = sqrt(Constantvalue + options->WeightConstantsValues[GNSS][PRN][i][1]*pow(10,-0.1*SNR)/(pow(sin(epoch->sat[satIndex].elevation),2))+SBASsigma+DGNSSsigma+ionosigma);
						}
					default:
						break;
				}
				break;
		}

		if (epoch->sat[satIndex].measurementWeights[i]==0.) {
			//Set sigma to 1mm to avoid dividing by 0
			epoch->sat[satIndex].measurementWeights[i]=0.001;
		}
			   	
	}

	return NA;
}

/*****************************************************************************
 * Name        : getAntenna
 * Description : Get the antenna structure from its name (as a string)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *name                     I  N/A  Name of the antenna
 * TAntennaList  *antennaList      I  N/A  List of antennas to look for
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (*TAntenna)      O  N/A  Pointer to the antenna inside TAntennaList
 *                                         If it is NULL, the antenna has not been
 *                                         found
 *****************************************************************************/
TAntenna *getAntenna (char *name, TAntennaList *antennaList, TOptions *options) {
	int			i;
	char		*ca;
	char		ant_name[MAX_ANTENNA_NAME];
	char		ant_radome[MAX_ANTENNA_NAME];
	TAntenna	*aux;
	
	ant_radome[0]='\0';
	strcpy(ant_name,name);
	ca = strstr(ant_name," ");
	if (ca != NULL) {
		*ca = '\0';
		strcpy(ant_radome,&ca[1]);
		trim(ant_radome);
	}

	for (i=0;i<antennaList->numAnt;i++) {
		if (strcmp(name,antennaList->ant[i].type)==0) {
			return &antennaList->ant[i];
		} else if (strcmp(ant_name,antennaList->ant[i].type_ant)==0) {
			if (strcmp(ant_radome,antennaList->ant[i].type_radome)==0) {
				return &antennaList->ant[i];
			} else if (strcmp(ant_radome,"")==0 && strcmp(antennaList->ant[i].type_radome,"NONE")==0) {
				return &antennaList->ant[i];
			}
		}
	}
	
	// If the radome parsing is not strict, try to get the same antenna, but without radome
	if (!options->strictradome && ant_radome[0]!='\0') {
		aux = getAntenna(ant_name,antennaList,options);
		if (aux!=NULL) {
			sprintf(messagestr,"WARNING antenna '%s' not found... using '%s'. Enable radome strict option to avoid this behaviour",name,aux->type);
			printInfo(messagestr,options);
		}
		return aux;
	}
	
	return NULL;
}

/*****************************************************************************
 * Name        : getReceiverType
 * Description : Get the receiver structure from its name (as a string)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *name                     I  N/A  Name of the antenna
 * TReceiverList  *recList         I  N/A  List of receivers to look for
 * Returned value (*TReceiverData) O  N/A  Pointer to the receiver inside TReceiverList
 *                                         If it is NULL, the receiver has not been
 *                                         found
 *****************************************************************************/
TReceiverData *getReceiverType (char *name, TReceiverList *recList) {
	int 	i;
	
	for (i=0;i<recList->n;i++) {
		if (strcasecmp(name,recList->rec[i].name)==0) return &recList->rec[i];
	}
	
	return NULL;
}


/*****************************************************************************
 * Name        : modelEpoch
 * Description : Model the common part of all satellites for a specific epoch 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            I  N/A  Status of the function
 *                                         1 => No errors found
 *                                         Right now this function does not find
 *                                         any errors, thence always returns 1
 *****************************************************************************/
int modelEpoch (TEpoch *epoch, TOptions *options) {
	// Station NEU coordinates 
	fillGroundStationNEU(epoch);
	
	// Station orientation
	fillGroundStationOrientation(epoch);
	
	// Compute tides displacements
	// Solid tides
	if (options->solidTidesCorrection) {
		fillSolidTideDisplacement(epoch);
	}
	
	return 1;
}
 
/*****************************************************************************
 * Name        : modelSatellite
 * Description : Model the satellite-dependant corrections for a specific epoch
 *               and satellite
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 * int  satIndex                   I  N/A  Index of the satellite to model
 * TGNSSproducts  *products        I  N/A  Orbit and clock GNSS products to obtain the model
 * TGNSSproducts  *klbProd         I  N/A  Support products to use for Klobuchar modeling, when applicable
 * TGNSSproducts  *beiProd         I  N/A  Support products to use for BeiDou modeling, when applicable
 * TGNSSproducts  *neqProd         I  N/A  Support products to use for NeQuick modeling, when applicable
 * TIONEX *Ionex                   I  N/A  IONEX structure, when applicable
 * TFPPPIONEX *Fppp                I  N/A  FPPP structure, when applicable
 * TTROPOGal *TropoGal             I  N/A  TTROPOGal structure, when applicable
 * TTGDdata  *tgdData              I  N/A  Support products to use for TGD correction, when applicable
 * TConstellation  *constellation  I  N/A  Constellation information of the products
 * TSBASdata *SBASdata             I  N/A  Struct with SBAS data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            I  N/A  Status of the function
 *                                         0 => Any problem found in the modeling
 *                                              (something is missing)
 *                                         1 => Model properly computed
 *****************************************************************************/
int modelSatellite (TEpoch *epoch, TEpoch *epochDGNSS, int satIndex, TGNSSproducts *products, TGNSSproducts *klbProd, TGNSSproducts  *beiProd, TGNSSproducts *neqProd, TIONEX *Ionex, TFPPPIONEX *Fppp, TTROPOGal *TropoGal, TTGDdata *tgdData, TConstellation *constellation, TSBASdata *SBASdata, TOptions *options) {
	int			i, j, k;
	int			res1, res2;
	int			ionoerror;
	double		flightTime;
	double		tropWetMap;
	double		relativityModel;
	double		windUpRadModel;
	double		windUpMetModel;
	double		troposphereModel;
	double		ionosphereModel;
	double		ionosphereModelElectrons;
	double		gravitationalDelayModel;
	double		TGDModel;
	double		solidTidesModel;
	double		satelliteClockModel;
	double		satellitePhaseCenterProjection;
	double		satellitePhaseCenterVarProjection;
	double		receiverPhaseCenterProjection;
	double		receiverARPProjection;
	double		model;
	double		lambda;
	double		geometricDistance;
	double		satearthcentredistance;
	double		dt = 0.0, dt2 = 0.0;
	double		DGNSScorr;
	double		sigmas[6];
	double		sigmaTotal=0.;
	double 		sigmaMultipath, sigmaAir, sigmaDegradation;
	double 		deltaPRC,deltaRRC;
	enum		MeasurementType	meas;
	TTime		t;
	TSBAScorr	SBAScorr;
	TBRDCblock	*block=NULL;

	initSBAScorrections(&SBAScorr);
	epoch->sat[satIndex].hasSBAScor = 1;
	epoch->sat[satIndex].hasC1C = 1;
	epoch->sat[satIndex].hasDCBs = 1;
	epoch->sat[satIndex].hasDCBsofC1P1 = 1;
	epoch->sat[satIndex].hasOrbitsAndClocks = 1;
	epoch->sat[satIndex].hasSatPhaseCenterCor = 1;
	epoch->sat[satIndex].URAValue = 0.;
	epoch->sat[satIndex].validIono = 1;
	epoch->sat[satIndex].NoSNRforWeightMeas = NA;
	
	
	// Check if satellite has been deselected (do not compute any model)
	if (!options->includeSatellite[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN])
		return 0;

	//Check SNR. Note that hasSNR will only be set to 0 if SNR has been enabled
	if ( epoch->sat[satIndex].hasSNR==0) {
		//Satellite below SNR threshold
		return 0;
	}
	

	//Set if to print to Buffer or directly to file
	if ( options->SBAScorrections == 1 && options->onlySBASiono == 0 ) {
		options->printInBuffer = 1;
	} else if ( options->DGNSS == 1 ) {
		options->printInBuffer = 1;
	} else {
		options->printInBuffer = 0;
	}

	// Compute SBAS corrections
	if ( options->SBAScorrections == 1 && options->onlySBASiono == 0 ) {
	
		for ( i=0;i<epoch->measOrder[epoch->sat[satIndex].GNSS].nDiffMeasurements;i++ ) {
			// Check measurements (with SBAS we only use C1C)
			meas = epoch->measOrder[epoch->sat[satIndex].GNSS].ind2Meas[i];
			if ( meas != C1C ) {
				epoch->sat[satIndex].meas[i].model = 0;
				continue;
			}

			//Check we have valid measurement for C1C
			if(epoch->sat[satIndex].meas[i].value==-1) {
				epoch->sat[satIndex].meas[i].model = 0;
				epoch->sat[satIndex].hasOrbitsAndClocks = 1;
				epoch->sat[satIndex].hasC1C = 0;
				return 0;
			}


			// Model not available for non GPS satellites
			if ( epoch->sat[satIndex].GNSS != GPS && epoch->sat[satIndex].GNSS != GEO ) return 0;

			// Note on SBAS corrections:
			// When SBAS corrections are applied, the clock corrections changes, therefore transmission time. We need to compute
			// SBAS corrections before computing transmission time
			res1 = computeSBAS(epoch,products,klbProd,beiProd,neqProd,Ionex,Fppp,satIndex,meas,i,SBASdata,&SBAScorr,options);
			// If any SBAS data is missing, stop computing
			if ( res1 <= 0 ) {
				epoch->sat[satIndex].meas[i].model = 0;
				if ( res1 == -45 ) epoch->sat[satIndex].hasSBAScor=1; //If external ionosphere is missing, it is not an SBAS fault.
				else epoch->sat[satIndex].hasSBAScor=0;
				if ( options->printSBASUNSEL == 1 ) {
					printSBASUNSEL(epoch,satIndex,res1,SBASdata,&SBAScorr,options);
				}
				return 0;
			}
		}
	}


	// To fit IODEs when looking for the orbits' block
	if ( options->DGNSS ) {
		j = epochDGNSS->satCSIndex[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];
		if ( epochDGNSS->dgnss.msg[j] == 1 && options->solutionMode == DGNSSMode ) SBAScorr.IOD = epochDGNSS->dgnss.IODmsg1[j];
		else SBAScorr.IOD = -1;
	}

	// Transmission time
	res1 = fillTransmissionTimeSat(epoch,products,satIndex,&SBAScorr,options);

	// In case of DGNSS processing RTCM v2.x if block of orbits with same IODE as message type 1 is not found,
	// we try to look for the block of orbits with same IODE as message type 2
	if ( res1 == 0 && options->DGNSS && options->solutionMode == DGNSSMode ) {
		if ( epochDGNSS->dgnss.msg[j] == 1 ) {
			SBAScorr.IOD = epochDGNSS->dgnss.IODmsg2[j];
			res1 = fillTransmissionTimeSat(epoch,products,satIndex,&SBAScorr,options);
		}
	}
	if ( res1 == 0 ) return 0;
	
	if ( options->timeTrans ) {
		memcpy(&t,&epoch->sat[satIndex].transTime,sizeof(TTime));
	} else {
		memcpy(&t,&epoch->t,sizeof(TTime));
	}
	flightTime = computeFlightTime(epoch,products,satIndex,&SBAScorr,options);

	if ( options->SBAScorrections == 1 && options->onlySBASiono == 0 && epoch->sat[satIndex].GNSS == GEO ) {
		// When we are processing with SBAS, and we have a GEO satellite, broadcast data are retrieved from message type 9
		// We don't have to do nothing in this case
		res2 = 1;
	} else {
		// Compute satellite coordinates, velocity, and clocks
		res2 = fillSatellitePVT(epoch,products,&t,flightTime,satIndex,1,1,options->satelliteClockCorrection,SBAScorr.IOD,constellation,options);
	
		// Stop computing models if any problem had arisen to save computing time
		if ( res2 == 0 ) return 0;
	
		if ( options->SBAScorrections == 1 && options->onlySBASiono == 0 ) {
			// If we have SBAS long term corrections, use the satellite coordinates and clocks with these corrections
			// If there are no long term corrections available, this will leave the original broadcast values
			SBAScorr.SatCoordbrdc[0] = epoch->sat[satIndex].position[0];
			SBAScorr.SatCoordbrdc[1] = epoch->sat[satIndex].position[1];
			SBAScorr.SatCoordbrdc[2] = epoch->sat[satIndex].position[2];

			epoch->sat[satIndex].position[0] = epoch->sat[satIndex].position[0]+SBAScorr.SatCoordCor[0];
			epoch->sat[satIndex].position[1] = epoch->sat[satIndex].position[1]+SBAScorr.SatCoordCor[1];
			epoch->sat[satIndex].position[2] = epoch->sat[satIndex].position[2]+SBAScorr.SatCoordCor[2];

			SBAScorr.Clockbrdc = epoch->sat[satIndex].clockCorrection;
			// NOTE: SBAS clock correction has to be substracted to broadcast clock, because in fillSatellitePVT the sign of the clock correction is changed
			epoch->sat[satIndex].clockCorrection = epoch->sat[satIndex].clockCorrection - SBAScorr.ClockCor;
			SBAScorr.Clock = epoch->sat[satIndex].clockCorrection;
		}

		//Fill URA
		if (products->type==BRDC) {
			block=selectBRDCblock(products->BRDC,&t,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,SBAScorr.IOD,options);
			epoch->sat[satIndex].URAValue=block->SVaccuracy;
		}
	}

	// Line of Sight
	fillLineOfSight(epoch,satIndex);

	// Azimuth and elevation
	fillAzimuthElevation(epoch,satIndex);
	
	// Models	
	// Geometric distance
	fillGeometricDistance(epoch,satIndex);
	geometricDistance = epoch->sat[satIndex].geometricDistance;

	// Satellite clock correction
	if ( options->satelliteClockCorrection ) {
		satelliteClockModel = epoch->sat[satIndex].clockCorrection;
	} else {
		satelliteClockModel = 0;
	}
	
	// Relativistic correction. GEO satellites have the relativity effects removed by the earth station control
	if ( options->relativisticCorrection && epoch->sat[satIndex].GNSS != GEO ) {
		relativityModel = relativisticCorrection(epoch->sat[satIndex].position, epoch->sat[satIndex].velocity);
	} else {
		relativityModel = 0;
	}
	
	// Wind up correction
	if ( options->windUpCorrection ) {
		windUpRadModel = windUpCorrection(epoch,satIndex);
	} else {
		windUpRadModel = 0;
	}
	
	// Tropospheric correction
	if ( options->troposphericCorrection ) {
		troposphereModel = troposphericCorrection(&epoch->t, epoch->receiver.aproxPositionNEU, epoch->sat[satIndex].elevation, TropoGal, &tropWetMap, &epoch->ZTD,options);
		epoch->sat[satIndex].tropWetMap = tropWetMap;
	} else {
		troposphereModel = 0;
		epoch->sat[satIndex].tropWetMap = 0;
	}
	
	// Ionospheric correction
	if ( options->SBAScorrections == 0 || ( options->SBAScorrections == 1 && options->onlySBASiono == 1 ) ) {
		switch(options->ionoModel) {
			case Klobuchar:
				ionosphereModelElectrons = klobucharModel(epoch, klbProd, satIndex);
				epoch->sat[satIndex].ionoSigma=0;
				break;
			case BeiDou:
				ionosphereModelElectrons = beiDouKlobucharModel(epoch, beiProd, satIndex);
				break;
			case IONEX:
				ionosphereModelElectrons = ionexModel(epoch, satIndex, Ionex, options); 
				if ( ionosphereModelElectrons == 9999 ) return 0;
				break;
			case FPPP:
				ionosphereModelElectrons = FPPPModel(epoch, satIndex, Fppp, options);
				if ( ionosphereModelElectrons == 9999 ) return 0;	
				break;
			case neQuick:
				ionosphereModelElectrons = NeQuickfunctionCall(epoch, satIndex, neqProd,options);
				if ( ionosphereModelElectrons == 9999 ) {
					if (options->initcoordNPA==1 && epoch->receiver.receiverSolConverged==0) {
						//Iono set to 5 + PRN/100 (TECUs). The value is not important, as it is
						//just to allow position convergence. The "PRN/10" is to add a different value
						//to each satellite, so the iono modelling is not accounted as part of the 
						//receiver clock delay
						ionosphereModelElectrons = 5. + (double)(epoch->sat[satIndex].PRN)/10.;
					} else {
						epoch->sat[satIndex].validIono=0;
						return 0;
					}
				}
				break;
			case SBASiono:
				ionosphereModelElectrons = SBASIonoModel(epoch,products,satIndex,&ionoerror,&SBAScorr,SBASdata,options);
				if ( ionosphereModelElectrons == 9999 ) {
					if (options->initcoordNPA==1 && epoch->receiver.receiverSolConverged==0) {
	        	        //We are waiting for the receiver solution to converge, we can use Klobuchar model in the first epochs
	            	    ionosphereModelElectrons = klobucharModel(epoch, klbProd, satIndex);
	   		        } else {
						epoch->sat[satIndex].hasSBAScor = 0;
						if ( options->printSBASUNSEL == 1 ) {
							printSBASUNSEL(epoch,satIndex,ionoerror,SBASdata,&SBAScorr,options);
						}
						return 0;
					}
				}
				break;
			default:
				//No iono
				ionosphereModelElectrons = 0;
				break;
		}
	} else {
		ionosphereModelElectrons = SBAScorr.ionocorrection;
	}

	// Gravitational delay correction
	if ( options->gravitationalCorrection ) {
		gravitationalDelayModel = gravitationalDelayCorrection(epoch->receiver.aproxPosition,epoch->sat[satIndex].position);
	} else {
		gravitationalDelayModel = 0;
	}
	
	// Solid tides correction
	if ( options->solidTidesCorrection ) {
		solidTidesModel = solidTidesCorrection(epoch,satIndex);
	} else {
		solidTidesModel = 0;
	}

	// DGNSS
	if ( options->DGNSS == 1 && epoch->sat[satIndex].hasDGNSScor == 1 ) {
		deltaPRC = 0.0;
	   	deltaRRC = 0.0;

		j = epochDGNSS->satCSIndex[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];
		k = epoch->satCSIndex[epoch->sat[satIndex].GNSS][epoch->sat[satIndex].PRN];
		dt = tdiff(&epoch->t,&epochDGNSS->dgnss.tPRC[j]);

		// Corrections
		DGNSScorr = 0.0;
		if ( epochDGNSS->dgnss.msg[j] == 0 ) DGNSScorr = epochDGNSS->dgnss.PRC[j];

		// Apply the both deltas PRC and RRC
		if ( epochDGNSS->dgnss.msg[j] != 0 ) {
			block = selectBRDCblock(products->BRDC,&epoch->sat[satIndex].transTime,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,epochDGNSS->dgnss.IODmsg1[j],options);
			if ( block == NULL ) block = selectBRDCblock(products->BRDC,&epoch->sat[satIndex].transTime,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,epochDGNSS->dgnss.IODmsg2[j],options);
			if ( block != NULL ) {
				if ( block->IODE == epochDGNSS->dgnss.IODmsg1[j] ) DGNSScorr = epochDGNSS->dgnss.PRC[j] + epochDGNSS->dgnss.RRC[j] * dt;
				if ( block->IODE != epochDGNSS->dgnss.IODmsg1[j] && block->IODE == epochDGNSS->dgnss.IODmsg2[j] ) {
					DGNSScorr = epochDGNSS->dgnss.PRC[j] + epochDGNSS->dgnss.RRC[j] * dt;
					dt2 = tdiff(&epoch->t,&epochDGNSS->dgnss.tdeltaPRC[j]);
					if ( dt2 <= options->maxAgeDGNSS ) {
						deltaPRC = epochDGNSS->dgnss.deltaPRC[j];
						deltaRRC = epochDGNSS->dgnss.deltaRRC[j];
						// Sanity check
						if ( fabs(deltaPRC) > 500. ) { deltaPRC = 0.0; dt2 = 0.0; }
						if ( fabs(deltaRRC) > 500. ) { deltaRRC = 0.0; dt2 = 0.0; }

						// Apply deltas
						DGNSScorr = DGNSScorr + deltaPRC + deltaRRC * dt2;
					} else { // This is done here because to avoid delete information from the structure, it may be useful in the future
						deltaPRC = 0.0;
						deltaRRC = 0.0;
						dt2 = 0.0;
						epoch->sat[satIndex].hasDGNSScor = 5;
					}
				}
			}
		}

		// Weigths calculation
		sigmaMultipath = options->dgnssSigma2multipath / tan(epoch->sat[satIndex].elevation) / tan(epoch->sat[satIndex].elevation);
		sigmaAir = ( sigmaMultipath + options->dgnssSigma2noiseGPS ) * epoch->dgnss.sigmaInflation[k];
		// epochDGNSS->dgnss.msg[j] = 0 corresponds to RTCM v3.x
		if ( epochDGNSS->dgnss.msg[j] == 0 ) sigmaDegradation = (epochDGNSS->dgnss.epsURA * dt) / tan(epoch->sat[satIndex].elevation);
		else sigmaDegradation = 0.0;
		if ( epochDGNSS->dgnss.sigmaURA3[j] < 0.0 ) sigmaTotal = 0.0;
		else sigmaTotal = pow(epochDGNSS->dgnss.sigmaURA3[j],2.0) + pow(sigmaDegradation,2.0) + sigmaAir;
		
		// Fill the sigmas array to print the message DGNSS
		sigmas[0] = sqrt(sigmaTotal);
		sigmas[1] = epochDGNSS->dgnss.sigmaURA3[j];
		sigmas[2] = sigmaDegradation;
		sigmas[3] = sqrt(sigmaAir);
		sigmas[4] = sigmaMultipath;
		sigmas[5] = epoch->dgnss.sigmaInflation[k];
		

		// Print DGNSS information
		if ( options->printDGNSS == 1 && options->solutionMode == DGNSSMode && epoch->sat[satIndex].hasDGNSScor==1 ) {
			printDGNSS(epoch, epochDGNSS, satIndex, dt, deltaPRC, deltaRRC, dt2, sigmas, options);
		}
	} else if ( options->DGNSS == 1 && epoch->sat[satIndex].hasDGNSScor != 1 ) {
		DGNSScorr =  0.0;
	}
	
	// Fill measurement weights
	epoch->sat[satIndex].NoSNRforWeightMeas=fillMeasurementWeights(epoch, satIndex, SBAScorr.SBASsatsigma2, sigmaTotal, options);

	// Model not available for non GPS satellites
	if ( epoch->sat[satIndex].GNSS != GPS ) return 0;
	
	for (i=0;i<epoch->measOrder[epoch->sat[satIndex].GNSS].nDiffMeasurements;i++) {
		// Measurement dependant effects
		meas = epoch->measOrder[epoch->sat[satIndex].GNSS].ind2Meas[i];

		// If SBAS is activated, do not use any other measurement different from C1C
		if ( options->SBAScorrections == 1 && options->onlySBASiono == 0 ) {
			if ( meas != C1C ) {
				epoch->sat[satIndex].meas[i].model = 0;
				continue;
			}
		}

		// If DGNSS is activated, do not use any other measurement different from C1C
		if ( options->DGNSS == 1 ) {
			if ( meas != C1C ) {
				epoch->sat[satIndex].meas[i].model = 0;
				continue;
			}
		}

		// Ionosphere model
		lambda = getLambda(epoch->sat[satIndex].GNSS,meas);
		SBAScorr.ionocorrection = ionosphereModel = ionosphereModelElectrons * 40.3 * (lambda*lambda) / (c0*c0) * pow(10,16);

		// Satellite phase center correction for SP3 products (may depend in the frequency)
		if ( options->satellitePhaseCenter ) {
			if ( constellation!=NULL && products->type == SP3 ) {
				res1 = satellitePhaseCenterCorrection(&epoch->t, epoch->sat[satIndex].GNSS, epoch->sat[satIndex].PRN, meas, epoch->sat[satIndex].orientation, epoch->sat[satIndex].LoS, constellation, &satellitePhaseCenterProjection);
				
				if ( !res1 ) {
					epoch->sat[satIndex].hasSatPhaseCenterCor = 0;	// No constellation information
					return 0; 
				}

				if ( options->satellitePhaseVar == 1 ) {
					satearthcentredistance = sqrt(epoch->sat[satIndex].position[0]*epoch->sat[satIndex].position[0]+epoch->sat[satIndex].position[1]*epoch->sat[satIndex].position[1]+epoch->sat[satIndex].position[2]*epoch->sat[satIndex].position[2]);
					res1 = satellitePhaseCenterVarCorrection(&epoch->t,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,meas,satearthcentredistance,epoch->sat[satIndex].elevation,constellation, &satellitePhaseCenterVarProjection);
					if ( res1 ) {
						satellitePhaseCenterProjection+=satellitePhaseCenterVarProjection;
					}
				}
			} else {
				satellitePhaseCenterProjection = 0;
			}
		} else {
			satellitePhaseCenterProjection = 0;
		}
		
		// Receiver antenna phase center
		if ( options->antennaData == adSET || options->antennaData == adANTEX ) {
			receiverPhaseCenterProjection = receiverPhaseCenterCorrection(&epoch->receiver.antenna,epoch->sat[satIndex].GNSS,meas,epoch->receiver.orientation,epoch->sat[satIndex].LoS);
			if ( options->receiverPhaseVar == 1 && options->antennaData == adANTEX ) {
				receiverPhaseCenterProjection += receiverPhaseCenterVarCorrection(&epoch->receiver.antenna,epoch->sat[satIndex].GNSS,meas,epoch->sat[satIndex].elevation);
			}
		} else {
			receiverPhaseCenterProjection = 0;
		}
		
		// Receiver Antenna Reference Point (ARP)
		if ( options->ARPData >= arpSET ) {
			receiverARPProjection = receiverARPCorrection(epoch->receiver.ARP,epoch->receiver.orientation,epoch->sat[satIndex].LoS);
		} else {
			receiverARPProjection = 0;
		}
			
		// TGD Model
		epoch->sat[satIndex].hasDCBs = 1;
		epoch->sat[satIndex].hasDCBsofC1P1 = 1;
		TGDModel = TGDCorrection(epoch,satIndex,&t,meas,SBAScorr.IOD,tgdData,options);

		// Forcing configuration depending on the type of solution
		// Allowing the switch between DGNSS and SPP
		if ( options->solutionMode == DGNSSMode ) {
			troposphereModel = 0;
			ionosphereModel = 0;
			satellitePhaseCenterProjection = 0;
			receiverPhaseCenterProjection = 0;
			//receiverARPProjection = 0;
			solidTidesModel = 0;
		} else if ( options->solutionMode < DGNSSMode ) {
			DGNSScorr = 0;
		}
		
		// Modeling computing
		switch ( whatIs(meas) ) {
			case CarrierPhase:
				windUpMetModel = windUpRadModel / (2*Pi) * lambda;
				ionosphereModel = -ionosphereModel;
				model = geometricDistance + satelliteClockModel + satellitePhaseCenterProjection + receiverPhaseCenterProjection + receiverARPProjection + relativityModel + windUpMetModel + troposphereModel + ionosphereModel + gravitationalDelayModel + TGDModel + solidTidesModel;
				break;
			case Pseudorange:
				windUpMetModel = 0;
				model = geometricDistance + satelliteClockModel + satellitePhaseCenterProjection + receiverPhaseCenterProjection + receiverARPProjection + relativityModel + troposphereModel + ionosphereModel + gravitationalDelayModel + TGDModel + solidTidesModel - SBAScorr.PRC - SBAScorr.RRCtime - DGNSScorr;
				break;
			default:
				model = 0;
				continue;
				break;
		}
		epoch->sat[satIndex].meas[i].model = model;
		
		printModel(epoch, satIndex, i, flightTime, geometricDistance, satelliteClockModel, satellitePhaseCenterProjection, receiverPhaseCenterProjection, receiverARPProjection, relativityModel, windUpMetModel, troposphereModel, ionosphereModel, gravitationalDelayModel, TGDModel, solidTidesModel, options);

		if ( options->SBAScorrections == 1 && options->onlySBASiono == 0 ) {
			if ( options->printSBASCORR == 1 ) {
				printSBASCORR(epoch, SBASdata, &SBAScorr, satIndex, i, flightTime, geometricDistance, satelliteClockModel, satellitePhaseCenterProjection, receiverPhaseCenterProjection, receiverARPProjection, relativityModel, windUpMetModel, troposphereModel, ionosphereModel, gravitationalDelayModel, TGDModel, solidTidesModel, options);
			}
			if ( options->printSBASVAR == 1 ) {
				printSBASVAR(epoch, SBASdata, &SBAScorr, satIndex, i,options);
			}
		}
	}

	return 1;
}

/*****************************************************************************
 * Name        : computeSBAS
 * Description : Compute SBAS corrections
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * TGNSSproducts  *klbProd         I  N/A  Support products to use for Klobuchar modeling, when applicable
 * TGNSSproducts  *beiProd         I  N/A  Support products to use for BeiDou modeling, when applicable
 * TGNSSproducts  *neqProd         I  N/A  Support products to use for NeQuick modeling, when applicable
 * TIONEX *Ionex                   I  N/A  IONEX structure, when applicable
 * TFPPPIONEX *Fppp                I  N/A  FPPP structure, when applicable
 * int  satIndex                   I  N/A  Index of the satellite to obtain the correction
 * enum MeasurementType  meas      I  N/A  Measurement
 * int  measIndex                  I  N/A  Index of the measurement in which we will apply the correction
 * TSBASdata *SBASdata             I  N/A  Struct with SBAS data
 * TSBAScorr *SBAScorr             O  N/A  Struct with the SBAS corrections to be applied
 *                                          to the current satellite
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                        <0 => No correction for current measurement
 *                                               Check printSBASUNSEL function for return values
 *                                         0  => Satellite is not visible (only for SBAS plots mode)
 *                                         1  => SBAS corrections available
 *****************************************************************************/
int computeSBAS (TEpoch *epoch, TGNSSproducts *products, TGNSSproducts *klbProd, TGNSSproducts  *beiProd, TGNSSproducts *neqProd, TIONEX *Ionex, TFPPPIONEX *Fppp, int satIndex, enum MeasurementType meas, int measIndex, TSBASdata *SBASdata, TSBAScorr *SBAScorr, TOptions *options) {
	int				i,j,k,l;
	int				res1;
	int				IODP,PRN,PRNpos;
	int				IODS;
	int				ret,mt10available=1;
	int				nolongterm=0,nocovmatrix=0,nofastcorr=0,nodeltaudre=0;
	int				ionoerror;
	int				prevlongterm=0,velocitycode;
	int				GEOPRN;
	int				firstinside=1;
	int				posFC,prevposFC,tmoutFC,smallertmoutFC=9999,FCalarm=0,indexprevPRC=-1,prevUDREI14=0;
	enum GNSSystem	GNSS;
	double			ionosphereModelElectrons;
	double 			difftime,olddifftime;
	double			deltaoutside=1;
	double			R[4][4],RT[4][4],C[4][4],CI[4],I[4],scalefactor;
	double			lambda;
	double			currentvalue,unitarydistance;
	TBRDCblock		*block;
	TTime           t,tu,tudre,tPRC;

	///////////////////////////
	////Check if we have a GEO selected

	//If options->GEOindex is negative, it contains the negative number that states why we can't select a GEO
	if (options->GEOindex<0) return options->GEOindex;

	//First gather GEO PRN from which we are receiving the corrections
	//If we are using multiple GEO, GEOPRN value will be 0
	GEOPRN=SBASdata[options->GEOindex].PRN;

	///////////////////////////
	////Check if we have received a type 0 message

	//We only have to skip processing if the GEO we are using has received an alarm message (and it is not the mixed one)
	if(options->GEOindex>0) {
		//Case for not mixed GEO
		if ( SBASdata[0].alarmGEOPRN[GEOPRN]==GEOPRN && SBASdata[options->GEOindex].alarmTimeRemaining>0) return -4;
	} else {
		//Mixed GEO. Skip processing if alarm cooldown has not finished or there are still other GEOs with alarm
		if ( SBASdata[0].alarmTimeRemaining>0 ) return -4;
	}

	///////////////////////////
	////Check that we have not lost messages or received incorrect messages

	//Check that we have not had errors decoding the last 4 consecutive messages received
	if(SBASdata[0].failedmessages[GEOPRN]>=4) {
		if (epoch->sat[satIndex].GNSS==GEO && epoch->sat[satIndex].PRN==GEOPRN) return -5;
	}

	//Check that we have not lost four consecutive messages
	if(SBASdata[0].missed4msg[GEOPRN]>=4) {
		return -6;
	}

	///////////////////////////
	////Check if we have a valid PRN Mask

	difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].lastmsgreceived[PRNMASKASSIGNMENTS]);
	olddifftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].oldlastmsgreceived[PRNMASKASSIGNMENTS]);

	if(SBASdata[options->GEOindex].lastmsgreceived[PRNMASKASSIGNMENTS].MJDN==-1) {
		//No PRN mask received
		return -7;
	} else if(difftime>(double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][PRNMASKASSIGNMENTS]) ) {
		//The current mask has time out, so the old one (if we have one stored) will also have time out
		if(satIndex==epoch->lastSBASindex) {
			for(i=0;i<MAX_GNSS;i++) {
				for(j=0;j<MAX_SBAS_PRN;j++) {
					SBASdata[options->GEOindex].PRNactive[SBASdata[options->GEOindex].IODPmask][i][j]=0;
					SBASdata[options->GEOindex].PRN2pos[SBASdata[options->GEOindex].IODPmask][i][j]=-1;
				}
			}
			SBASdata[options->GEOindex].lastmsgreceived[PRNMASKASSIGNMENTS].MJDN=-1;
			SBASdata[options->GEOindex].lastmsgreceived[PRNMASKASSIGNMENTS].SoD=-1;
			SBASdata[options->GEOindex].numsatellites[SBASdata[options->GEOindex].IODPmask]=0;
			SBASdata[options->GEOindex].IODPmask=4;
		}
		return -8;
	} else if (olddifftime>(double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][PRNMASKASSIGNMENTS]) ) {
		//The old mask is timed out. If the values of the old mask have not been discarded, do it now
		if(SBASdata[options->GEOindex].oldmaskdiscarded[PRNMASKASSIGNMENTS]==0 && (SBASdata[options->GEOindex].oldlastmsgreceived[PRNMASKASSIGNMENTS].MJDN!=-1)) {
			if(satIndex==epoch->lastSBASindex) {
				for(i=0;i<MAX_GNSS;i++) {
					for(j=0;j<MAX_SBAS_PRN;j++) {
						SBASdata[options->GEOindex].PRNactive[SBASdata[options->GEOindex].oldIODPmask][i][j]=0;
						SBASdata[options->GEOindex].PRN2pos[SBASdata[options->GEOindex].oldIODPmask][i][j]=-1;
					}
				}
				SBASdata[options->GEOindex].oldmaskdiscarded[PRNMASKASSIGNMENTS]=1;
				SBASdata[options->GEOindex].oldlastmsgreceived[PRNMASKASSIGNMENTS].MJDN=-1;
				SBASdata[options->GEOindex].oldlastmsgreceived[PRNMASKASSIGNMENTS].SoD=-1;
				SBASdata[options->GEOindex].numsatellites[SBASdata[options->GEOindex].oldIODPmask]=0;
				SBASdata[options->GEOindex].oldIODPmask=4;
			}
		}
	}

	///////////////////////////
	////Check if current PRN is in the mask

	PRN=epoch->sat[satIndex].PRN;
	GNSS=epoch->sat[satIndex].GNSS;
	if(GNSS==GEO && PRN<100) PRN+=100;	//Add 100 because in RINEX files the GEO PRN comes with 2 digits
	if(SBASdata[options->GEOindex].PRNactive[SBASdata[options->GEOindex].IODPmask][GNSS][PRN]!=1 && SBASdata[options->GEOindex].PRNactive[SBASdata[options->GEOindex].oldIODPmask][GNSS][PRN]!=1) {
		return -9;
	}

	///////////////////////////
	////Check if we have Message Type 10 available. MT10 is necessary for computing degradation

	difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].lastmsgreceived[DEGRADATIONPARAMETERS]);
	if (options->NoMT10==1) {
		//Message Type 10 is not used, even in PA mode
		SBAScorr->mt10avail=mt10available=0;
	} else if(SBASdata[options->GEOindex].lastmsgreceived[DEGRADATIONPARAMETERS].MJDN==-1) {
		//Message Type 10 time out or without data
		SBAScorr->mt10avail=mt10available=0;
		if(options->precisionapproach==PAMODE) return -10; //MT10 is necesssary for precision approach
	} else if(difftime>(double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][DEGRADATIONPARAMETERS]) ) {
		//Message Type 10 time out or without data
		if(satIndex==epoch->lastSBASindex) {
			SBASdata[options->GEOindex].lastmsgreceived[DEGRADATIONPARAMETERS].MJDN=-1;
			SBASdata[options->GEOindex].degradationfactors[RSSUDRE]=-1;
		}
		SBAScorr->mt10avail=mt10available=0;
		if(options->precisionapproach==PAMODE) return -11; //MT10 is necesssary for precision approach
	} else {
		SBAScorr->mt10avail=mt10available=1;
	}


	///////////////////////////
	////Compute Fast corrections

	//Check that we have a valid IODP
	if(SBASdata[options->GEOindex].IODPfastcorr==4) {
		//No fast correction message received
		if(options->precisionapproach==PAMODE) return -12;
		else nofastcorr=1;
	} else {
		IODP=SBASdata[options->GEOindex].IODPfastcorr;
		PRNpos=SBASdata[options->GEOindex].PRN2pos[IODP][GNSS][PRN];
		if(PRNpos!=-1) {
			//Check that we have data for this PRN
			posFC=SBASdata[options->GEOindex].poslastFC[IODP][PRNpos];
			prevposFC=mod(posFC-1,MAXSBASFASTCORR);
			if (posFC==-1) {
				//No data received for this PRN with the current mask
				nofastcorr=1;
			}
		} else {
			nofastcorr=1;
		}


		if(nofastcorr==1) {
			//The satellite is not monitored in the current mask
			//Try previous mask
			IODP=SBASdata[options->GEOindex].oldIODPfastcorr;
			PRNpos=SBASdata[options->GEOindex].PRN2pos[IODP][GNSS][PRN];
			if(PRNpos!=-1) {
				//Check that we have data for this PRN
				posFC=SBASdata[options->GEOindex].poslastFC[IODP][PRNpos];
				prevposFC=mod(posFC-1,MAXSBASFASTCORR);
				if (posFC==-1) {
					//No data received for this PRN with the previous mask
					if(options->precisionapproach==PAMODE) {
						if(SBASdata[options->GEOindex].useforbidden[GNSS][PRN]==14) {
							return -14;
						} else if (SBASdata[options->GEOindex].useforbidden[GNSS][PRN]==15) {
							return -15;
						} else {
							return -12;
						}
					} else nofastcorr=1;
				} else {
					//Correction available
					nofastcorr=0;
				}
			} else {
				//The satellite is not monitored in the previous mask. No data available for this PRN
				if(options->precisionapproach==PAMODE) {
					if(SBASdata[options->GEOindex].useforbidden[GNSS][PRN]==14) {
						return -14;
					} else if (SBASdata[options->GEOindex].useforbidden[GNSS][PRN]==15) {
						return -15;
					} else {
						return -12;
					}
				} else nofastcorr=1;
			}
		}
	}

	if(nofastcorr==1) {
		//If we don't have data for this satellite, we have to check that we had not received UDREI=14 or UDREI=15 before
		//We will not to use this satellite until we receive an UDREI<=13
		if(SBASdata[options->GEOindex].useforbidden[GNSS][PRN]==14) {
			return -14;
		} else if (SBASdata[options->GEOindex].useforbidden[GNSS][PRN]==15) {
			return -15;
		}
	}


	if(nofastcorr==0) {
		//Save IODP and PRNpos in SBAScorr struct
		SBAScorr->fastcorIODP=IODP;
		SBAScorr->fastcorPRNpos=PRNpos;
		if(options->FCtmout[options->precisionapproach]!=-1) {
			//Select user time out for fast corrections
			tmoutFC=options->FCtmout[options->precisionapproach];
		} else {
			//Select time out value according to message type 7
			tmoutFC=SBASdata[options->GEOindex].fastcorrtimeout[options->precisionapproach][IODP][PRNpos];
		}
		//Save the value in SBAScorr struct, along with the degradation factor
		SBAScorr->fastcorrtmout=tmoutFC;
		SBAScorr->fastcorrdegfactor=SBASdata[options->GEOindex].aifactor[IODP][PRNpos];
		if(options->RRCtmout[options->precisionapproach]!=-1) {
			//Select user time out for range rate corrections
			smallertmoutFC=options->RRCtmout[options->precisionapproach];
		} else {
			//Look for shortest time out period in all satellites
			for(i=0;i<SBASdata[options->GEOindex].numsatellites[IODP];i++) {
				if(SBASdata[options->GEOindex].fastcorrtimeout[options->precisionapproach][IODP][i]<smallertmoutFC && SBASdata[options->GEOindex].fastcorrtimeout[options->precisionapproach][IODP][i] !=-1) {
					smallertmoutFC=SBASdata[options->GEOindex].fastcorrtimeout[options->precisionapproach][IODP][i];
				}
			}
		}
		//Save the value in SBAScorr struct
		SBAScorr->fastcorrsmallertmout=smallertmoutFC;

		//Check if the last data received is from message type 2-5,24 or type 6
		if(SBASdata[options->GEOindex].lastfastmessage[PRNpos]==INTEGRITYINFO) {
			//Last fast correction data received is from message type 6
			if(SBASdata[options->GEOindex].IODFintegrity[PRNpos]==3) {
				//We have received an alarm (IODF=3)
				FCalarm=1;
				//The UDRE sigma used will be the last one received in message type 6
				SBAScorr->UDREsigma=SBASdata[options->GEOindex].UDREsigma6[PRNpos];
				//Save also its UDREI
				SBAScorr->UDREI=SBASdata[options->GEOindex].UDREI6[PRNpos];
				//tudre will be the time of the last message type 6
				tudre=SBASdata[options->GEOindex].lastintegrityinfo[PRNpos];
				//PRC time will be the time of last message type 2-5,24 fast correction message
				tPRC=SBASdata[options->GEOindex].lastfastcorrections[IODP][posFC][PRNpos];
				//tu time will also be the the time of applicability of the last message type 2-5,24 fast correction message (the time of the first bit sent at the GEO)
				tu=tPRC;
				//Save IODF used
				SBAScorr->fastcorIODF=SBASdata[options->GEOindex].IODFintegrity[PRNpos];
			} else if (SBASdata[options->GEOindex].IODFintegrity[PRNpos]!=SBASdata[options->GEOindex].IODF[IODP][posFC][PRNpos]) {
				//IODF from message type 6 does not match the IODF from messages type 2-5,24 and IODF!=3
				//We cannot use the UDREsigma from message type 6, so we keep using the last one from messages type 2-5,24
				SBAScorr->UDREsigma=SBASdata[options->GEOindex].UDREsigma[IODP][posFC][PRNpos];
				//Save also its UDREI
				SBAScorr->UDREI=SBASdata[options->GEOindex].UDREI[IODP][posFC][PRNpos];
				//tudre will be the the time of applicability of the last type 6 fast correction message (the time of the first bit sent at the GEO) even though that IODFs do not match
				tudre=SBASdata[options->GEOindex].lastintegrityinfo[PRNpos];
				//PRC time will be the last message to be received with previous IODF (either type 6 or type 2-5,24)
				if(tdiff(&SBASdata[options->GEOindex].lastfastcorrections[IODP][posFC][PRNpos],&SBASdata[options->GEOindex].oldlastintegrityinfo[PRNpos])>=0) {
					//Last message received with previous IODF is from message type 2-5,24
					tPRC=SBASdata[options->GEOindex].lastfastcorrections[IODP][posFC][PRNpos];
				} else {
					//Last message received with previous IODF is from message type 6
					tPRC=SBASdata[options->GEOindex].oldlastintegrityinfo[PRNpos];
				}
				//tu time will also be the last message to be received with previous IODF (either type 6 or type 2-5,24)
				tu=tPRC;
				//Save IODF used
				SBAScorr->fastcorIODF=SBASdata[options->GEOindex].IODF[IODP][posFC][PRNpos];
			} else {
				//IODF from message type 6 matches the IODF from messages type 2-5,24 and IODF!=3
				//We can use the UDREsigma from message type 6
				SBAScorr->UDREsigma=SBASdata[options->GEOindex].UDREsigma6[PRNpos];
				//Save also its UDREI
				SBAScorr->UDREI=SBASdata[options->GEOindex].UDREI6[PRNpos];
				//tudre will be the the time of applicability of the last type 6 fast correction message
				tudre=SBASdata[options->GEOindex].lastintegrityinfo[PRNpos];
				//PRC time will also be the time of the last type 6 fast correction message
				tPRC=tudre;
				//tu time will  also be the time of the last type 6 fast correction message
				tu=tPRC;
				//Save IODF used
				SBAScorr->fastcorIODF=SBASdata[options->GEOindex].IODFintegrity[PRNpos];
			}
		} else {
			//Last fast correction data received is from message type 2-5,24
			//Use the last UDREsigma received in these messages
			if(SBASdata[options->GEOindex].IODF[IODP][posFC][PRNpos]==3) {
				//We have received an alarm (IODF=3)
				FCalarm=1;
			}
			SBAScorr->UDREsigma=SBASdata[options->GEOindex].UDREsigma[IODP][posFC][PRNpos];
			//Save also its UDREI
			SBAScorr->UDREI=SBASdata[options->GEOindex].UDREI[IODP][posFC][PRNpos];
			//tudre will be the the time of applicability of the last message type 2-5,25 received
			tudre=SBASdata[options->GEOindex].lastfastcorrections[IODP][posFC][PRNpos];
			//PRC time will also be the time of last message type 2-5,24 received
			tPRC=tudre;
			//tu time will also be the time of last message type 2-5,24 received
			tu=tPRC;
			//Save IODF used
			SBAScorr->fastcorIODF=SBASdata[options->GEOindex].IODF[IODP][posFC][PRNpos];
		}
		//Check that UDRE sigma values are not in time out
		difftime=tdiff(&epoch->t,&tudre);
		if(difftime>(double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][INTEGRITYINFO])) {
			if(options->precisionapproach==PAMODE) return -13;
			else nofastcorr=1;
		//} else {
		//	nosigmaudre=0;
		}
	}

	//NOTE: This condition is done several times to avoid too many nested if statements
	if(nofastcorr==0) {

		//Check if we have a "Not monitored" or "Don't use" value
		if(SBAScorr->UDREI>=14) {
			//We have a "Not monitored" or "Don't use" UDRE
			//Erase all fast correction data stored data from this satellite
			nofastcorr=1;
			for(i=0;i<5;i++) {
				SBASdata[options->GEOindex].poslastFC[i][PRNpos] = -1;
				SBASdata[options->GEOindex].numFC[i][PRNpos] = 0;
				for(j=0;j<MAXSBASFASTCORR;j++) {
					SBASdata[options->GEOindex].PRC[i][j][PRNpos] = 9999;
					SBASdata[options->GEOindex].RRC[i][j][PRNpos] = 9999;
					SBASdata[options->GEOindex].UDREI[i][j][PRNpos] = -1;
					SBASdata[options->GEOindex].UDRE[i][j][PRNpos] = -1;
					SBASdata[options->GEOindex].UDREsigma[i][j][PRNpos] = -1;
					SBASdata[options->GEOindex].IODF[i][j][PRNpos] = -1;
					SBASdata[options->GEOindex].lastfastcorrections[i][j][PRNpos].MJDN = -1;
					SBASdata[options->GEOindex].lastfastcorrections[i][j][PRNpos].SoD = -1;
				}
			}
			SBASdata[options->GEOindex].lastfastmessage[PRNpos]=-1;
			SBASdata[options->GEOindex].IODFintegrity[PRNpos]=-1;
			SBASdata[options->GEOindex].oldIODFintegrity[PRNpos]=-1;
			SBASdata[options->GEOindex].UDREI6[PRNpos]=-1;
			SBASdata[options->GEOindex].UDRE6[PRNpos]=-1;
			SBASdata[options->GEOindex].UDREsigma6[PRNpos]=-1;
			SBASdata[options->GEOindex].oldUDREI6[PRNpos]=-1;
			SBASdata[options->GEOindex].oldUDRE6[PRNpos]=-1;
			SBASdata[options->GEOindex].oldUDREsigma6[PRNpos]=-1;
			SBASdata[options->GEOindex].lastintegrityinfo[PRNpos].MJDN = -1;
			SBASdata[options->GEOindex].lastintegrityinfo[PRNpos].SoD = -1.;
			SBASdata[options->GEOindex].oldlastintegrityinfo[PRNpos].MJDN = -1;
			SBASdata[options->GEOindex].oldlastintegrityinfo[PRNpos].SoD = -1.;

			
			//Set do not use flag
			SBASdata[options->GEOindex].useforbidden[GNSS][PRN]=SBAScorr->UDREI;

			if(SBAScorr->UDREI==14) {
				//UDREsigma set to "Not monitored". We cannot use this satellite.
				return -14;
			} else { //SBAScorr->UDREI==15
				//UDREsigma set to "Don't use". We cannot use this satellite.
				return -15;
			}
		//Check that UDREI is not over the maximum threshold in precision approach
		} else if (SBAScorr->UDREI>=UDRETHRESHOLDPA && options->precisionapproach==PAMODE) {
			//We are in precision approach mode, so we cannot use satellites with UDRE>=12
			//Clear the use forbidden flag if it is active
			if(SBASdata[options->GEOindex].useforbidden[GNSS][PRN]>=14) {
				SBASdata[options->GEOindex].useforbidden[GNSS][PRN]=0;
			}
			return -16;
		} else {
			//We can also have the case to receive an UDRE=14 or 15 and in the next message, receive an UDRE=6.
			//If this happens and at the moment we received the UDRE=14 or 15 we didn't have any range data for this satellite,
			//we will not have entered this function (no ranging data, therefore the modelSatellite function is not called) and then we would
			//have not erased the data for this satellite
			//Now we will check that in the messages stored there are no UDREI=14 or 15 stored, and if any is found, data will be erased
			for (j=1;j<MAXSBASFASTCORR;j++) {
				k=mod(posFC-j,MAXSBASFASTCORR); //We will start looking from the previous position of the last corrections
				if (SBASdata[options->GEOindex].UDREI[IODP][k][PRNpos]>=14) {
					prevUDREI14=1;
					l=j;
					break;
				}
			}

			if (prevUDREI14==1) {
				//We received an UDREI=14 or 15. Erase this message and all the previous (the ones received with UDRE<14 after the UDREI>=14 do not have to be erased)
				for(i=0;i<5;i++) {
					if(i==IODP) {
						j=l;
						SBASdata[options->GEOindex].numFC[i][PRNpos] = l;
					} else {
						j=0;
						SBASdata[options->GEOindex].poslastFC[i][PRNpos] = -1;
						SBASdata[options->GEOindex].numFC[i][PRNpos] = 0;
					}
					for(;j<MAXSBASFASTCORR;j++) {
						k=mod(posFC-j,MAXSBASFASTCORR);
						SBASdata[options->GEOindex].PRC[i][k][PRNpos] = 9999;
						SBASdata[options->GEOindex].RRC[i][k][PRNpos] = 9999;
						SBASdata[options->GEOindex].UDREI[i][k][PRNpos] = -1;
						SBASdata[options->GEOindex].UDRE[i][k][PRNpos] = -1;
						SBASdata[options->GEOindex].UDREsigma[i][k][PRNpos] = -1;
						SBASdata[options->GEOindex].IODF[i][k][PRNpos] = -1;
						SBASdata[options->GEOindex].lastfastcorrections[i][k][PRNpos].MJDN = -1;
						SBASdata[options->GEOindex].lastfastcorrections[i][k][PRNpos].SoD = -1;
					}
				}
			}

			//Clear the use forbidden flag if it is active
			if(SBASdata[options->GEOindex].useforbidden[GNSS][PRN]>=14) {
				SBASdata[options->GEOindex].useforbidden[GNSS][PRN]=0;
			}
		}

		//Check that we have a valid message type 7 and is not in time out
		if(SBASdata[options->GEOindex].lastfastdegfactor[IODP][PRNpos].MJDN!=-1) {
			//We have message type 7 data, check that it has not timed out
			difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].lastfastdegfactor[IODP][PRNpos]);
			if(difftime>(double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][FASTCORRECTIONSDEGRADATIONFACTOR])) {
				//Message type 7 data timed out
				SBASdata[options->GEOindex].lastfastdegfactor[IODP][PRNpos].MJDN=-1;
				SBASdata[options->GEOindex].lastfastdegfactor[IODP][PRNpos].SoD=-1;
				if(options->precisionapproach==PAMODE) return -18;
				else nofastcorr=1;
			}
		} else {
			//No available message type 7
			if(options->precisionapproach==PAMODE) return -17;
			else nofastcorr=1;
		}

		//Discard satellites equal or over the user defined UDREI threshold
		if (SBAScorr->UDREI>=options->UDREIthreshold) {
			return -48;
		}
	}


	if(nofastcorr==0) {
		//Save tudre value in SBAScorr struct
		SBAScorr->tPRC=tPRC.SoD;
		SBAScorr->tudre=tudre.SoD;
		SBAScorr->tu=tu.SoD;
		//We have a UDRE which allows the satellite to be used (UDRE<12) or UDRE<14 and we are in non-precision approach
		//Check that the last PRC received is not timed out
		difftime=tdiff(&epoch->t,&tPRC);
		if(difftime>tmoutFC) {
			//Last PRC received timed out
			if(options->precisionapproach==PAMODE) return -19;
			else nofastcorr=1;
		} else {
			//We have a valid PRC
			SBAScorr->PRC=SBASdata[options->GEOindex].PRC[IODP][posFC][PRNpos];
			//Save values in SBAScorr structure
			SBAScorr->fastcorIODP=IODP;
			SBAScorr->fastcorPRNpos=PRNpos;

			//Check that we have two PRC samples for computing RRC
			if(SBASdata[options->GEOindex].numFC[IODP][PRNpos]<2) {
				if(options->precisionapproach==PAMODE) return -20;
				else {
					//We only have one fast correction available because we are initializating or reinitializating due to UDRE=14 or UDRE=15. 
					//During initializaton RRC will not be used until we have enough samples.
					//MOPS-D does not set any sigma flt value in this case!! (in MOPS-C a sigma flt of 60 meters was set)
					//We assume thence the values of zero both RRC and its degradation term
					SBAScorr->RRC=0;
					SBAScorr->RRCtime=0;
					SBAScorr->RRCdeg=0;
				}
			}

			//Compute fast correction degradation term
			//The 1.1 seconds added is to transform from time of reception of last bit to time of applicability
			SBAScorr->fastcorrdeg=SBASdata[options->GEOindex].aifactor[IODP][PRNpos]*pow(tdiff(&epoch->t,&tu)+1.1+SBASdata[options->GEOindex].tlat[IODP],2)/2;
		}
	}

	if(nofastcorr==0 && SBASdata[options->GEOindex].numFC[IODP][PRNpos]>=2) {
		//Compute RRC and its degradation if we have at least two PRC values
		if (SBASdata[options->GEOindex].aifactor[IODP][PRNpos]==0) {
			//Degradation factor for fast correction is zero. Thence, RRC and RRC degradation are 0
			SBAScorr->RRC=0;
			SBAScorr->RRCtime=0;
			SBAScorr->RRCdeg=0;
		} else {
			//Degradation factor for fast correction is not zero
			//Check if we have received an alarm condition in the last message or in the previous type 2-5,24 message
			if(FCalarm==1 || SBASdata[options->GEOindex].IODF[IODP][prevposFC][PRNpos]==3) {
				//We have received in current or previous message an alarm
				//In this case we need to find the previous PRC received closest to smallertmoutFC/2
				//First we find the closest one to smallertmoutFC/2, but before this time
				//As we are looking for the closest PRC before smallertmoutFC/2, the last one found will be the closest one
				for(i=0;i<SBASdata[options->GEOindex].numFC[IODP][PRNpos]-1;i++) {
					j=mod(prevposFC-i,MAXSBASFASTCORR);
					difftime=tdiff(&SBASdata[options->GEOindex].lastfastcorrections[IODP][posFC][PRNpos],&SBASdata[options->GEOindex].lastfastcorrections[IODP][j][PRNpos]);
					if(difftime<((double)(smallertmoutFC)/2.)) indexprevPRC=j;
				}
				if(indexprevPRC==-1) {
					//We have not found a suitable PRC measurement. We will now look for the closest one to smallertmoutFC/2, but after this time
					for(i=0;i<SBASdata[options->GEOindex].numFC[IODP][PRNpos]-1;i++) {
						j=mod(prevposFC-i,MAXSBASFASTCORR);
						difftime=tdiff(&SBASdata[options->GEOindex].lastfastcorrections[IODP][posFC][PRNpos],&SBASdata[options->GEOindex].lastfastcorrections[IODP][j][PRNpos]);
						//In this case we also have to check that PRC has not timed out
						if(difftime>=((double)(smallertmoutFC)/2.) && difftime<=(double)(smallertmoutFC)) {
							indexprevPRC=j;
							break;
						}
					}
					if(indexprevPRC==-1) {
						//We only have one valid fast correction available. We cannot compute RRC
						//RRC value will be zero, as well as its degradation term
						SBAScorr->RRC=0;
						SBAScorr->RRCtime=0;
						SBAScorr->RRCdeg=0;
					}
				}

				if(indexprevPRC!=-1) {
					//We have a valid previous PRC. Compute RRC
					difftime=tdiff(&SBASdata[options->GEOindex].lastfastcorrections[IODP][posFC][PRNpos],&SBASdata[options->GEOindex].lastfastcorrections[IODP][indexprevPRC][PRNpos]);
					SBAScorr->RRC=(SBASdata[options->GEOindex].PRC[IODP][posFC][PRNpos]-SBASdata[options->GEOindex].PRC[IODP][indexprevPRC][PRNpos])/difftime;
					//Check RRC time out
					//First check that time between PRC is not greater than time out
					if(difftime>(double)(smallertmoutFC)) {
						//RRC timed out
						if(options->precisionapproach==PAMODE) return -21;
						else nofastcorr=1;
					} else {
						//PRC measurement used for RRC cannot be propagated more than 8 times the time difference used for computing RRC
						//The 0.1 seconds is to convert from time of emission of first bit plus 1
						if(tdiff(&epoch->t,&SBASdata[options->GEOindex].lastfastcorrections[IODP][posFC][PRNpos])+0.1>8*difftime) {
							//RRC timed out
							if(options->precisionapproach==PAMODE) return -22;
							else nofastcorr=1;
						}
					}
					//Compute RRC degradation term
					if(fabs(difftime-((double)(smallertmoutFC)/2.))==0 || mt10available==0) {
						//Difference between measurements equal half the time out value or we don't have valid degradation terms
						SBAScorr->RRCdeg=0;
					} else {
						SBAScorr->RRCdeg=((SBASdata[options->GEOindex].aifactor[IODP][PRNpos]*fabs(difftime-((double)(smallertmoutFC)/2.)))/2.+SBASdata[options->GEOindex].degradationfactors[BRRC]/difftime)*(tdiff(&epoch->t,&SBASdata[options->GEOindex].lastfastcorrections[IODP][posFC][PRNpos])+1.1);
					}
				}


			} else {
				//No alarm received
				//To compute RRC, just take the current and previous PRC
				//difftime variable will have the difference between the time of applicability of the current and previous PRC
				//Note that in gLAB timestamp are saved in time of reception of last bit, which is 1.1 seconds after the time of applicability, but as this
				//is a substract between two times, this constant difference of 1.1 seconds is eliminated
				difftime=tdiff(&SBASdata[options->GEOindex].lastfastcorrections[IODP][posFC][PRNpos],&SBASdata[options->GEOindex].lastfastcorrections[IODP][prevposFC][PRNpos]);
				SBAScorr->RRC=(SBASdata[options->GEOindex].PRC[IODP][posFC][PRNpos]-SBASdata[options->GEOindex].PRC[IODP][prevposFC][PRNpos])/difftime;
				//Check RRC time out
				if(difftime>(double)(smallertmoutFC)) {
					//RRC timed out
					if(options->precisionapproach==PAMODE) return -23;
					else nofastcorr=1;
				} else {
					//PRC measurement used for RRC cannot be propagated more than 8 times the time difference used for computing RRC
					//The 0.1 seconds is to convert to time of emission of first bit plus 1
					if(tdiff(&epoch->t,&SBASdata[options->GEOindex].lastfastcorrections[IODP][posFC][PRNpos])+0.1>8*difftime) {
						//RRC timed out
						if(options->precisionapproach==PAMODE) return -24;
						else nofastcorr=1;
					}
				}
				//Compute RRC degradation term
				if(mod(SBASdata[options->GEOindex].IODF[IODP][posFC][PRNpos]-SBASdata[options->GEOindex].IODF[IODP][prevposFC][PRNpos],3)==1 || mt10available==0) {
					//IODF counter is in sequence or we don't have valid degradation terms
					SBAScorr->RRCdeg=0.;
				} else {
					SBAScorr->RRCdeg=((SBASdata[options->GEOindex].aifactor[IODP][PRNpos]*(double)(smallertmoutFC))/4.+SBASdata[options->GEOindex].degradationfactors[BRRC]/difftime)*(tdiff(&epoch->t,&SBASdata[options->GEOindex].lastfastcorrections[IODP][posFC][PRNpos])+1.1);
				}
			}

			//Compute RRC value multiplied by the difference between current time and time of applicabily of last fast correction
			//This will be the RRC value to be added to the pseudorange correction
			if(nofastcorr==0) {
				SBAScorr->RRCtime=SBAScorr->RRC*(tdiff(&epoch->t,&SBASdata[options->GEOindex].lastfastcorrections[IODP][posFC][PRNpos])+1.1);
			}
		}
	}

	//Check if user has disabled Fast corrections or RRC corrections. In that case, put the corrections to 0
	if(options->NoFastCorrection==1) {
		SBAScorr->PRC=0.;
		SBAScorr->RRCtime=0.;
	} else if (options->NoRRCCorrection==1) {
		SBAScorr->RRCtime=0.;
	}

	//Check if user has disabled Fast corrections or RRC sigmas. In that case, put the sigmas to 0
	if(options->NoFastSigma==1) {
		SBAScorr->fastcorrdeg=0.;
		SBAScorr->UDREsigma=0.;
		SBAScorr->RRCdeg=0.;
	} else if (options->NoRRCSigma==1) {
		SBAScorr->RRCdeg=0.;
	}

	if(options->NoFastDeg==1) {
		SBAScorr->fastcorrdeg=0.;
	}


	///////////////////////////
	////Compute Delta UDRE

	if(options->NoDeltaUDRE==1) {
		//User has disabled Delta UDRE value. We will set a value of 1
		//As Delta UDRE, if it is not available, it is just set to 1 and we can continue in PA mode, we don't have to check if it is really available
		SBAScorr->deltaudre=1;
		SBAScorr->deltaudresource=0;
	} else if(SBASdata[options->GEOindex].lastmsgreceived[SBASSERVICEMESSAGE].MJDN!=-1 && SBASdata[options->GEOindex].lastmsgreceived[CLOCKEPHEMERISCOVARIANCEMATRIX].MJDN!=-1) {
		//We have received both messages type 27 and type 28. MOPS says that they should send only one of them, and if we receive both, set delta UDRE=1
		//We could also have the case to be using data from all GEO and be receiving data from different service providers (WAAS and SBAS), in which case
		//we would have both messages type 27 and type 28. In this case we would not use either
		SBAScorr->deltaudre=1;
		SBAScorr->deltaudresource=0;
	} else if (SBASdata[options->GEOindex].lastmsgreceived[SBASSERVICEMESSAGE].MJDN==-1 && SBASdata[options->GEOindex].lastmsgreceived[CLOCKEPHEMERISCOVARIANCEMATRIX].MJDN==-1) {
		//We have not received type 27 or type 28 messages. Thus Delta UDRE =1
		SBAScorr->deltaudre=1;
		SBAScorr->deltaudresource=0;
	} else if (SBASdata[options->GEOindex].lastmsgreceived[SBASSERVICEMESSAGE].MJDN!=-1) {
		//Compute Delta UDRE using message type 27 (this is sent by EGNOS)
		//Check timeout
		difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].lastmsgreceived[SBASSERVICEMESSAGE]);
		if(difftime>(double)((SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][SBASSERVICEMESSAGE])) ) {
			//Message timed out
			SBASdata[options->GEOindex].lastmsgreceived[SBASSERVICEMESSAGE].MJDN=-1;
			SBASdata[options->GEOindex].lastmsgreceived[SBASSERVICEMESSAGE].SoD=-1;
			IODS=SBASdata[options->GEOindex].IODS;
			for(i=0;i<4;i++) {
				SBASdata[options->GEOindex].numberofregions[IODS][i]=0;
				for(j=0;j<40;j++) {
					for(k=0;k<12;k++) {
						SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][k]=9999;
					}
				}
			}
			for(i=0;i<8;i++) {
				SBASdata[options->GEOindex].servicemessagesreceived[IODS][i]=-1;
			}
			SBASdata[options->GEOindex].maxprioritycode[IODS]=0;
			SBASdata[options->GEOindex].totalservicemessagesreceived[IODS]=0;
			
			SBAScorr->deltaudre=1;
			SBAScorr->deltaudresource=-27;
			if(options->precisionapproach==PAMODE) return -25;
			else nodeltaudre=1;
		} else {
			//If we are in non precision approach, if corrections have timed out for precision approach but not for non precision, we need to add a degradation term
			if(options->precisionapproach==NPAMODE && difftime>(double)(SBASdata[options->GEOindex].timeoutmessages[1][SBASSERVICEMESSAGE]) && mt10available==1) {
				SBAScorr->enroutedegradation=SBASdata[options->GEOindex].degradationfactors[CER];
			}
			SBAScorr->deltaudresource=27;
			//To proceed, we must have received at least a complete set of messages with an IODS. 
			//So we need to check that if there are messages pending and if we already had a set of messages with previous IODS
			if(SBASdata[options->GEOindex].regioncoordinates[SBASdata[options->GEOindex].IODS][SBASdata[options->GEOindex].maxprioritycode[SBASdata[options->GEOindex].IODS]][0][NUMBERSERVICEMESSAGES]>SBASdata[options->GEOindex].totalservicemessagesreceived[SBASdata[options->GEOindex].IODS] && SBASdata[options->GEOindex].oldlastmsgreceived[SBASSERVICEMESSAGE].MJDN==-1) {
				//We have not received a complete set of messages
				SBAScorr->deltaudre=1;
				if(options->precisionapproach==PAMODE) return -26;
				else nodeltaudre=1;
			} else {
				for(k=0;k<2;k++) { //This loop is for checking current and previous service messages
					if(k==0) IODS=SBASdata[options->GEOindex].IODS;
					else IODS=SBASdata[options->GEOindex].oldIODS;
					SBAScorr->serviceIODS=IODS;
					for(i=SBASdata[options->GEOindex].maxprioritycode[IODS];i>=0;i--) { 
						//Check all regions, starting with the ones with higher priority code.
						//If more than one region with the same priority code is found, select the one with lowest UDRE factor
						//The regions are defined using geodetic coordinates
						SBAScorr->deltaudre=1;
						for(j=0;j<SBASdata[options->GEOindex].numberofregions[IODS][i];j++) {
							if((int)SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][REGIONSHAPE]==1 || (int)SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][REGIONSHAPE]==0) {
								//Square region or triangular region
								ret=InsideOutside(epoch->receiver.aproxPositionNEU[0]*r2d,epoch->receiver.aproxPositionNEU[1]*r2d,
											SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][COORD1LAT],
											SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][COORD1LON],
											SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][COORD2LAT],
											SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][COORD2LON],
											SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][COORD3LAT],
											SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][COORD3LON],
											SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][COORD4LAT],
											SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][COORD4LON],
											SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][REGIONSHAPE]);
								if(ret==1) {
									//Region inside
									if(firstinside==1) {
										//This is the first region we are inside. Set this as the Deltra UDRE value
										firstinside=0;
										SBAScorr->deltaudre=SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][UDREINSIDEVALUE];
									} else {
										if (k==0) {
											//Using newer IODS
											if(SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][UDREINSIDEVALUE]<SBAScorr->deltaudre) {
												//This is not the first region we are inside, and the Delta Udre has a lower value than the previous region
												SBAScorr->deltaudre=SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][UDREINSIDEVALUE];
											}
										} else { //k==1
											//Using old IODS
											if(SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][UDREINSIDEVALUE]>SBAScorr->deltaudre) {
												//A Delta Udre from the new IODS lower than the applicable from the previous IODS will not be used
												//until we have received all the messages for the newer IODS
												SBAScorr->deltaudre=SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][UDREINSIDEVALUE];
											}
										}
									}
								} else if (ret==0) {
									//Region outside. Save the Deltra UDRE outside (which will be the same in all regions) in case we don't find any region
									//A Delta Udre from the new IODS lower than the applicable from the previous IODS will not be use 
									//until we have received all the messages for the newer IODS
									if(k==0) {
										deltaoutside=SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][UDREOUTSIDEVALUE];
									} else { //k==1
										if(SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][UDREOUTSIDEVALUE]>deltaoutside) {
											deltaoutside=SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][UDREOUTSIDEVALUE];
										}
									}
								} else {
									//Not able to determine if inside or outside the region. Consider it an invalid region
									continue;
								}

							} else {
								//Not a valid region
								continue;
							}
						}
						//When we have checked all the regions with a given priority code and there is at least one region inside,
						//do not look at the regions with lower priority codes
						if(firstinside==0) {
							break; //Escape the for(i..) loop if we have found a region
						}
					}
					if (k==0) { //Only enter if this is the first loop (searched in current service message)
						if(SBASdata[options->GEOindex].oldlastmsgreceived[SBASSERVICEMESSAGE].MJDN==-1) {
							//No previous message, escape the for(k..) loop
							break;
						} else if (SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][NUMBERSERVICEMESSAGES]>SBASdata[options->GEOindex].totalservicemessagesreceived[IODS]) {
							//If we have not received all the service messages of the current IODS, we can try to check the areas of the previous IODS if it has not timed out
							//(this is done in order to cover the transition between IODS)
							difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].oldlastmsgreceived[SBASSERVICEMESSAGE]);
							if(difftime>(double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][SBASSERVICEMESSAGE]) ) {
								IODS=SBASdata[options->GEOindex].oldIODS;
								SBASdata[options->GEOindex].oldlastmsgreceived[SBASSERVICEMESSAGE].MJDN=-1;
								SBASdata[options->GEOindex].oldlastmsgreceived[SBASSERVICEMESSAGE].SoD=-1;
								for(i=0;i<4;i++) {
									SBASdata[options->GEOindex].numberofregions[IODS][i]=0;
									for(j=0;j<40;j++) {
										for(k=0;k<12;k++) {
											SBASdata[options->GEOindex].regioncoordinates[IODS][i][j][k]=9999;
										}
									}
								}
								for(i=0;i<8;i++) {
									SBASdata[options->GEOindex].servicemessagesreceived[IODS][i]=-1;
								}
								SBASdata[options->GEOindex].maxprioritycode[IODS]=0;
								SBASdata[options->GEOindex].totalservicemessagesreceived[IODS]=0;
								break; //Escape for(k..) loop
							}
						} else {
							//We have received all the messages for the current IODS, do not check the previous IODS
							break;
						}
					}
				} //end for

				//Check if we have not found any region in which we are inside. In this case, use the Delta Outside value. 
				//In the case we didn't have any region because there were no messages, the Delta outside value will have the default value of 1
				if(firstinside==1) {
					SBAScorr->deltaudre=deltaoutside;
				}
			}
		}
	} else if (SBASdata[options->GEOindex].lastmsgreceived[CLOCKEPHEMERISCOVARIANCEMATRIX].MJDN!=-1) {
		//We have received type 28 messages (this is sent by WAAS). Check if we have data for the current satellite 
		SBAScorr->deltaudresource=28;
		IODP=SBASdata[options->GEOindex].IODPcovariance;
		PRNpos=SBASdata[options->GEOindex].PRN2pos[IODP][GNSS][PRN];
		if(PRNpos!=-1) {
			if(SBASdata[options->GEOindex].lastcovmatrix[IODP][PRNpos].MJDN!=-1) {
				//PRN monitorized in the current mask or previous mask and we have received data for this satellite
				difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].lastcovmatrix[IODP][PRNpos]);
				if(difftime>(double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][CLOCKEPHEMERISCOVARIANCEMATRIX]) ) {
					//Data timed out. No correction available
					SBASdata[options->GEOindex].lastcovmatrix[IODP][PRNpos].MJDN=-1;
					SBASdata[options->GEOindex].lastcovmatrix[IODP][PRNpos].SoD=-1;
					SBAScorr->deltaudresource=-28;
					nocovmatrix=1;
					SBAScorr->deltaudre=1;
					if(options->precisionapproach==PAMODE) return -28;
					else nodeltaudre=1;
				}

				//If we are in non precision approach, if corrections have timed out for precision approach but not for non precision, we need to add a degradation term
				if(options->precisionapproach==NPAMODE && difftime>(double)(SBASdata[options->GEOindex].timeoutmessages[1][LONGTERMSATELLITECORRECTIONS]) && mt10available==1 && nocovmatrix==0) {
					SBAScorr->enroutedegradation=SBASdata[options->GEOindex].degradationfactors[CER];
				}
			} else {
				//No data available for this PRN in the current mask. No correction available
				SBAScorr->deltaudresource=-28;
				nocovmatrix=2;
				SBAScorr->deltaudre=1;
				nodeltaudre=1;
			}
		} else {
			SBAScorr->deltaudresource=-28;
			nocovmatrix=2;
			nodeltaudre=1;
		}

		if(nodeltaudre==1) {
			//Check previous clock ephemeris covariance matrix with old IODP
			IODP=SBASdata[options->GEOindex].oldIODPcovariance;
			PRNpos=SBASdata[options->GEOindex].PRN2pos[IODP][GNSS][PRN];
			if(PRNpos!=-1) { 
				if(SBASdata[options->GEOindex].lastcovmatrix[IODP][PRNpos].MJDN!=-1) {
					//PRN monitorized in the previous mask and a we have got data for this PRN
					difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].lastcovmatrix[IODP][PRNpos]);
					if(difftime>(double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][CLOCKEPHEMERISCOVARIANCEMATRIX]) ) {
						//Data timed out. No correction available
						SBASdata[options->GEOindex].lastcovmatrix[IODP][PRNpos].MJDN=-1;
						SBASdata[options->GEOindex].lastcovmatrix[IODP][PRNpos].SoD=-1;
						SBAScorr->deltaudresource=-28;
						nocovmatrix=1;
						SBAScorr->deltaudre=1;
						if(options->precisionapproach==PAMODE) return -28;
						else nodeltaudre=1;
					} else {
						//Correction available
						nocovmatrix=0;
						nodeltaudre=0;
						SBAScorr->deltaudresource=28;
					}

					//If we are in non precision approach, if corrections have timed out for precision approach but not for non precision, we need to add a degradation term
					if(options->precisionapproach==NPAMODE && difftime>(double)(SBASdata[options->GEOindex].timeoutmessages[1][LONGTERMSATELLITECORRECTIONS]) && mt10available==1 && nocovmatrix==0) {
						SBAScorr->enroutedegradation=SBASdata[options->GEOindex].degradationfactors[CER];
					}
				} else {
					//No data available for this PRN in the previous mask. No correction available
					SBAScorr->deltaudresource=-28;
					nocovmatrix=2;
					SBAScorr->deltaudre=1;
					if(options->precisionapproach==PAMODE) return -27;
					else nodeltaudre=1;
				}
			} else {
				//PRN not monitorized in the previous mask. No correction available
				SBAScorr->deltaudresource=-28;
				nocovmatrix=2;
				SBAScorr->deltaudre=1;
				if(options->precisionapproach==PAMODE) return -27;
				else nodeltaudre=1;
			}
		}

		if(nocovmatrix==0) {
			SBAScorr->covarianceIODP=IODP;
			SBAScorr->covariancePRNpos=PRNpos;
			//We have got valid type 28 message data
			scalefactor=pow(2,(int)SBASdata[options->GEOindex].clockephemeriscovariance[IODP][PRNpos][SCALEEXPONENT]-5);
			//Construct R and RT (R transposed) matrixes
			R[0][0]=RT[0][0]=scalefactor*SBASdata[options->GEOindex].clockephemeriscovariance[IODP][PRNpos][E11];
			R[0][1]=RT[1][0]=scalefactor*SBASdata[options->GEOindex].clockephemeriscovariance[IODP][PRNpos][E12];
			R[0][2]=RT[2][0]=scalefactor*SBASdata[options->GEOindex].clockephemeriscovariance[IODP][PRNpos][E13];
			R[0][3]=RT[3][0]=scalefactor*SBASdata[options->GEOindex].clockephemeriscovariance[IODP][PRNpos][E14];
			R[1][0]=RT[0][1]=0;
			R[1][1]=RT[1][1]=scalefactor*SBASdata[options->GEOindex].clockephemeriscovariance[IODP][PRNpos][E22];
			R[1][2]=RT[2][1]=scalefactor*SBASdata[options->GEOindex].clockephemeriscovariance[IODP][PRNpos][E23];
			R[1][3]=RT[3][1]=scalefactor*SBASdata[options->GEOindex].clockephemeriscovariance[IODP][PRNpos][E24];
			R[2][0]=RT[0][2]=0;
			R[2][1]=RT[1][2]=0;
			R[2][2]=RT[2][2]=scalefactor*SBASdata[options->GEOindex].clockephemeriscovariance[IODP][PRNpos][E33];
			R[2][3]=RT[3][2]=scalefactor*SBASdata[options->GEOindex].clockephemeriscovariance[IODP][PRNpos][E34];
			R[3][0]=RT[0][3]=0;
			R[3][1]=RT[1][3]=0;
			R[3][2]=RT[2][3]=0;
			R[3][3]=RT[3][3]=scalefactor*SBASdata[options->GEOindex].clockephemeriscovariance[IODP][PRNpos][E44];

			//Compute Covariance matrix (RT·R)
			for(i=0;i<4;i++) {
				for(j=0;j<4;j++) {
					C[i][j]=0;
					for(k=0;k<4;k++) {
						C[i][j]+=RT[i][k]*R[k][j];
					}
				}
			}

			//NOTE: The following part of the computation requires satellites coordinates, but still we do not have the corrections. 
			//We will leave this computations for later, after long term corrections have been computed
		}
	}

	///////////////////////////
	////Compute Long term corrections

	if(GNSS==GEO) { //GEO satellite coordinates are broadcast in message type 9 
		//GEO satellite coordinates are broadcast in message type 9, so they already have the long term corrections
		//The GEO satellite coordinates message is not bound to a PRN Mask, but the GEO must be in the current mask
		IODP=SBASdata[options->GEOindex].IODPmask;
		PRNpos=SBASdata[options->GEOindex].PRN2pos[IODP][GNSS][PRN];
		i=SBASdata[0].GEOPRN2pos[PRN];
		if(i==-1) {
			//No navigation data for this GEO
			return -29;
		} else {
			if(i!=options->GEOindex && options->precisionapproach==PAMODE) {
				//If we are in precision approach, we can only use data from one GEO.
				//Thus, we will only have navigation data for the GEO broadcasting corrections
				//In this case, we are computing corrections for a GEO different from the one we gather SBAS data
				return -29;
			}
		}

		//Check if we have navigation message
		if(SBASdata[i].lastmsgreceived[GEONAVIGATIONMESSAGE].MJDN==-1) {
			//No GEO navigation message available
			return -29;
		}
		difftime=tdiff(&epoch->t,&SBASdata[i].lastmsgreceived[GEONAVIGATIONMESSAGE]);
		if(difftime>(double)(SBASdata[i].timeoutmessages[options->precisionapproach][GEONAVIGATIONMESSAGE]) ) {
			SBASdata[i].lastmsgreceived[GEONAVIGATIONMESSAGE].MJDN=-1;
			//Data timed out. No correction available
			return -30;
		}

		SBAScorr->uraindex=SBASdata[i].geonavigationmessage[URAINDEX];
		if(SBASdata[i].geonavigationmessage[URAINDEX]>=URAMAXTHRESHOLD) {
			//MOPS-D URA index greater equal to URAMAXTHRESHOLD, satellite not usable for solution computation
			return -31;
		}
		//If we are in non precision approach, if corrections have timed out for precision approach but not for non precision, we need to add a degradation term
		if(options->precisionapproach==NPAMODE && difftime>(double)(SBASdata[i].timeoutmessages[1][GEONAVIGATIONMESSAGE]) && mt10available==1) {
			SBAScorr->enroutedegradation=SBASdata[options->GEOindex].degradationfactors[CER];	
		}

		//Compute transmission time
		if(options->onlySBASplots==1) {
			//In SBAS plot mode we don't have measurements, so we can't compute TransmissionTime
			//We set the transmission time as the current time
			memcpy(&epoch->sat[satIndex].transTime,&epoch->t,sizeof(TTime));	
			res1=1;
		} else {
			res1 = fillTransmissionTimeSat(epoch,products,satIndex,SBAScorr,options);
		}
		if (res1==0) return -36;

		difftime=epoch->sat[satIndex].transTime.SoD-SBASdata[i].geonavigationmessage[T0NAV];
		//Check for day rollover in time difference. As a threshold, we use the second at half of the day (86400/2=43200)
		if(difftime>43200) difftime-=86400; 	//This occurs when we are at the end of the day and the time of applicability is in the next day
		if(difftime<-43200) difftime+=86400;	//This occurs when we are at the beginning of the day and the time of applicability is in the previous day (because we have missed the previous message)
		SBAScorr->Clock=SBAScorr->ClockCor=SBASdata[i].geonavigationmessage[AGF0]+SBASdata[i].geonavigationmessage[AGF1]*difftime;
		SBAScorr->SatCoord[0]=SBASdata[i].geonavigationmessage[XG]+SBASdata[i].geonavigationmessage[XGRATEOFCHANGE]*difftime+0.5*SBASdata[i].geonavigationmessage[XGACCELERATION]*difftime*difftime;
		SBAScorr->SatCoord[1]=SBASdata[i].geonavigationmessage[YG]+SBASdata[i].geonavigationmessage[YGRATEOFCHANGE]*difftime+0.5*SBASdata[i].geonavigationmessage[YGACCELERATION]*difftime*difftime;
		SBAScorr->SatCoord[2]=SBASdata[i].geonavigationmessage[ZG]+SBASdata[i].geonavigationmessage[ZGRATEOFCHANGE]*difftime+0.5*SBASdata[i].geonavigationmessage[ZGACCELERATION]*difftime*difftime;

		SBAScorr->SatCoordCor[0]=SBAScorr->SatCoord[0];
		SBAScorr->SatCoordCor[1]=SBAScorr->SatCoord[1];
		SBAScorr->SatCoordCor[2]=SBAScorr->SatCoord[2];

		//Save broadcast satellite position
		SBAScorr->SatCoordbrdc[0]=0;
		SBAScorr->SatCoordbrdc[1]=0;
		SBAScorr->SatCoordbrdc[2]=0;

		//Save corrected coordinates
		epoch->sat[satIndex].position[0]=SBAScorr->SatCoord[0];
		epoch->sat[satIndex].position[1]=SBAScorr->SatCoord[1];
		epoch->sat[satIndex].position[2]=SBAScorr->SatCoord[2];

		//Transform clock correction to meters
		SBAScorr->ClockCor=SBAScorr->ClockCor*c0;
		SBAScorr->Clock=SBAScorr->ClockCor;
		SBAScorr->Clockbrdc=0;


		if(mt10available==1) {
			if(difftime>0  && difftime<SBASdata[options->GEOindex].degradationfactors[IGEO]) {
				SBAScorr->geonavdegradation=0;
			} else {
				difftime=max(-difftime,difftime-SBASdata[options->GEOindex].degradationfactors[IGEO]);
				difftime=max(0,difftime);
				SBAScorr->geonavdegradation=SBASdata[options->GEOindex].degradationfactors[CGEOLSB]+SBASdata[options->GEOindex].degradationfactors[CGEOV]*difftime;
			}

		}

	} else {
		//It is not a GEO satellite
		//First we need to check if the IODP of the last message matches any of the available masks
		//The last message matches the current mask. Check if the message is timed out
		IODP=SBASdata[options->GEOindex].IODPlongterm;
		PRNpos=SBASdata[options->GEOindex].PRN2pos[IODP][GNSS][PRN];
		if(PRNpos!=-1) { 
			if(SBASdata[options->GEOindex].lastlongtermdata[IODP][PRNpos].MJDN!=-1) {
				//PRN monitorized in the current mask or previous mask in the last long term message received
				difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].lastlongtermdata[IODP][PRNpos]);
				if(difftime>(double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][LONGTERMSATELLITECORRECTIONS]) ) {
					//Data timed out. No correction available
					SBASdata[options->GEOindex].lastlongtermdata[IODP][PRNpos].MJDN=-1;
					SBASdata[options->GEOindex].lastlongtermdata[IODP][PRNpos].SoD=-1;
					if(options->precisionapproach==PAMODE) return -33;
					else nolongterm=1;
				}
			} else {
				//No data for this PRN
				nolongterm=1;
			}

		} else {
			nolongterm=1;
		}

		if(nolongterm==1) {
			//Check previous long term correction with old IODP
			IODP=SBASdata[options->GEOindex].oldIODPlongterm;
			PRNpos=SBASdata[options->GEOindex].PRN2pos[IODP][GNSS][PRN];
			if(PRNpos!=-1) { 
				if(SBASdata[options->GEOindex].lastlongtermdata[IODP][PRNpos].MJDN!=-1) {
					//PRN monitorized in the previous mask and a we have got data for this PRN
					difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].lastlongtermdata[IODP][PRNpos]);
					if(difftime>(double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][LONGTERMSATELLITECORRECTIONS]) ) {
						//Data timed out. No correction available
						SBASdata[options->GEOindex].lastlongtermdata[IODP][PRNpos].MJDN=-1;
						SBASdata[options->GEOindex].lastlongtermdata[IODP][PRNpos].SoD=-1;
						if(options->precisionapproach==PAMODE) return -33;
						else nolongterm=1;
					} else {
						//Correction available
						nolongterm=0;
					}

				} else {
					//No data for this PRN
					if(options->precisionapproach==PAMODE) return -32;
					else nolongterm=1;
				}
			} else {
				//PRN not monitorized in the previous mask or no data available. No correction available
				if(options->precisionapproach==PAMODE) return -32;
				else nolongterm=1;
			}

		} 

		//First check if we have the broadcast block for the IOD given
		if(nolongterm==0) {
			SBAScorr->IOD=(int)SBASdata[options->GEOindex].longtermsaterrcorrections[IODP][PRNpos][ISSUEOFDATA];
			block = selectBRDCblock(products->BRDC,&epoch->t,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,SBAScorr->IOD,options);
			if(block==NULL) {
				//Block IOD not available in broadcast file
				//Check if we can use data with previous IOD
				if(SBASdata[options->GEOindex].prevlastlongtermdata[IODP][PRNpos].MJDN!=-1) {
					//We got one message stored, check it is not timed out
					difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].prevlastlongtermdata[IODP][PRNpos]);
					if(difftime>(double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][LONGTERMSATELLITECORRECTIONS]) ) {
						//Data timed out. No correction available
						SBASdata[options->GEOindex].prevlastlongtermdata[IODP][PRNpos].MJDN=-1;
						SBASdata[options->GEOindex].prevlastlongtermdata[IODP][PRNpos].SoD=-1;
						if(options->precisionapproach==PAMODE) {
							epoch->sat[satIndex].hasOrbitsAndClocks=0;
							return -34;
						}
						else nolongterm=1;
					} else {
						//We can use the previous IOD
						SBAScorr->IOD=(int)SBASdata[options->GEOindex].prevlongtermsaterrcorrections[IODP][PRNpos][ISSUEOFDATA];
						//Check if we have the broadcast block for the IOD given
						block = selectBRDCblock(products->BRDC,&epoch->t,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,SBAScorr->IOD,options);
						if(block==NULL) {
							//No broadcast block available
							if(options->precisionapproach==PAMODE) {
								epoch->sat[satIndex].hasOrbitsAndClocks=0;
								return -34;
							}
							else nolongterm=1;
						} else {
							//Broadcast block available with previous IOD
							prevlongterm=1;

							//If we are in non precision approach, if corrections have timed out for precision approach but not for non precision, we need to add a degradation term
							if(options->precisionapproach==NPAMODE && difftime>(double)(SBASdata[options->GEOindex].timeoutmessages[1][LONGTERMSATELLITECORRECTIONS]) && mt10available==1) {
								SBAScorr->enroutedegradation=SBASdata[options->GEOindex].degradationfactors[CER];
							}
						}
					}
				} else {
					if(options->precisionapproach==PAMODE) {
						epoch->sat[satIndex].hasOrbitsAndClocks=0;
						return -34;
					}
					else nolongterm=1;
				}

				//Check that we have at least a valid broadcast block regardless the IOD if we do not have any blocking matching SBAS IOD
				if(nolongterm==1) {
					SBAScorr->IOD=-1;
					block = selectBRDCblock(products->BRDC,&epoch->t,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,SBAScorr->IOD,options);
					if(block==NULL) {
						epoch->sat[satIndex].hasOrbitsAndClocks=0;
						return -35;
					}
					SBAScorr->IODnoSBAS=block->IODE;
				}
			} else {
				//If we are in non precision approach, if corrections have timed out for precision approach but not for non precision, we need to add a degradation term
				if(options->precisionapproach==NPAMODE && difftime>(double)(SBASdata[options->GEOindex].timeoutmessages[1][LONGTERMSATELLITECORRECTIONS]) && mt10available==1 ) {
					SBAScorr->enroutedegradation=SBASdata[options->GEOindex].degradationfactors[CER];
				}

			}
		}
		
		if(nolongterm==0) {
			//Save IODP of long term corrections
			SBAScorr->longtermIODP=IODP;
			SBAScorr->longtermPRNpos=PRNpos;

			//We have long term correction available, compute the values
			if(prevlongterm==1) {
				SBAScorr->ClockCor=SBASdata[options->GEOindex].prevlongtermsaterrcorrections[IODP][PRNpos][DELTAAF0];
				SBAScorr->SatCoordCor[0]=SBASdata[options->GEOindex].prevlongtermsaterrcorrections[IODP][PRNpos][DELTAX];
				SBAScorr->SatCoordCor[1]=SBASdata[options->GEOindex].prevlongtermsaterrcorrections[IODP][PRNpos][DELTAY];
				SBAScorr->SatCoordCor[2]=SBASdata[options->GEOindex].prevlongtermsaterrcorrections[IODP][PRNpos][DELTAZ];
				velocitycode=SBASdata[options->GEOindex].prevlongtermsaterrcorrections[IODP][PRNpos][VELOCITYCODE];
			} else {
				SBAScorr->ClockCor=SBASdata[options->GEOindex].longtermsaterrcorrections[IODP][PRNpos][DELTAAF0];
				SBAScorr->SatCoordCor[0]=SBASdata[options->GEOindex].longtermsaterrcorrections[IODP][PRNpos][DELTAX];
				SBAScorr->SatCoordCor[1]=SBASdata[options->GEOindex].longtermsaterrcorrections[IODP][PRNpos][DELTAY];
				SBAScorr->SatCoordCor[2]=SBASdata[options->GEOindex].longtermsaterrcorrections[IODP][PRNpos][DELTAZ];
				velocitycode=SBASdata[options->GEOindex].longtermsaterrcorrections[IODP][PRNpos][VELOCITYCODE];
			}

			//Compute transmission time with SBAS clock correction
			if(options->onlySBASplots==1) {
				//In SBAS plot mode we don't have measurements, so we can't compute TransmissionTime
				//We set the transmission time as the current time
				memcpy(&epoch->sat[satIndex].transTime,&epoch->t,sizeof(TTime));	
				res1=1;
			} else {
				res1 = fillTransmissionTimeSat(epoch,products,satIndex,SBAScorr,options);
			}
			if (res1==0) return -36;

			if(velocitycode==1) {
				if(prevlongterm==1) {
					//Add clock corrections only available when VELOCITYCODE=1
					difftime=epoch->sat[satIndex].transTime.SoD-SBASdata[options->GEOindex].prevlongtermsaterrcorrections[IODP][PRNpos][TIMEOFDAYAPPLICABILITY];
					//Check for day rollover in time difference. As a threshold, we use the second at half of the day (86400/2=43200)
					if(difftime>43200) difftime-=86400; 	//This occurs when we are at the end of the day and the time of applicability is in the next day
					if(difftime<-43200) difftime+=86400;	//This occurs when we are at the beginning of the day and the time of applicability is in the previous day (because we have missed the previous message)
					SBAScorr->ClockCor=SBAScorr->ClockCor+SBASdata[options->GEOindex].prevlongtermsaterrcorrections[IODP][PRNpos][DELTAAF1]*difftime;


					SBAScorr->SatCoordCor[0]=SBAScorr->SatCoordCor[0]+SBASdata[options->GEOindex].prevlongtermsaterrcorrections[IODP][PRNpos][DELTAXRATEOFCHANGE]*difftime;
					SBAScorr->SatCoordCor[1]=SBAScorr->SatCoordCor[1]+SBASdata[options->GEOindex].prevlongtermsaterrcorrections[IODP][PRNpos][DELTAYRATEOFCHANGE]*difftime;
					SBAScorr->SatCoordCor[2]=SBAScorr->SatCoordCor[2]+SBASdata[options->GEOindex].prevlongtermsaterrcorrections[IODP][PRNpos][DELTAZRATEOFCHANGE]*difftime;
				} else {
					difftime=epoch->sat[satIndex].transTime.SoD-SBASdata[options->GEOindex].longtermsaterrcorrections[IODP][PRNpos][TIMEOFDAYAPPLICABILITY];
					//Check for day rollover in time difference. As a threshold, we use the second at half of the day (86400/2=43200)
					if(difftime>43200) difftime-=86400; 	//This occurs when we are at the end of the day and the time of applicability is in the next day
					if(difftime<-43200) difftime+=86400;	//This occurs when we are at the beginning of the day and the time of applicability is in the previous day (because we have missed the previous message)
					SBAScorr->ClockCor=SBAScorr->ClockCor+SBASdata[options->GEOindex].longtermsaterrcorrections[IODP][PRNpos][DELTAAF1]*difftime;


					SBAScorr->SatCoordCor[0]=SBAScorr->SatCoordCor[0]+SBASdata[options->GEOindex].longtermsaterrcorrections[IODP][PRNpos][DELTAXRATEOFCHANGE]*difftime;
					SBAScorr->SatCoordCor[1]=SBAScorr->SatCoordCor[1]+SBASdata[options->GEOindex].longtermsaterrcorrections[IODP][PRNpos][DELTAYRATEOFCHANGE]*difftime;
					SBAScorr->SatCoordCor[2]=SBAScorr->SatCoordCor[2]+SBASdata[options->GEOindex].longtermsaterrcorrections[IODP][PRNpos][DELTAZRATEOFCHANGE]*difftime;
				}
			}
			if(GNSS==GLONASS && SBASdata[options->GEOindex].networktimemessage[GLONASSINDICATOR]==1) {
				//Add additional correction in clock for GLONASS satellites
				//GLONASS corrections still to be done in SBAS
			}

			//Transform clock correction to meters
			SBAScorr->ClockCor=SBAScorr->ClockCor*c0;

			//Compute long term degradation factor
			if(mt10available==1) {
				if(velocitycode==1) {
					//Velocity code=1
					if(difftime>0  && difftime<SBASdata[options->GEOindex].degradationfactors[ILTCV1]) {
						SBAScorr->longtermdegradation=0;
					} else {
						difftime=max(-difftime,difftime-SBASdata[options->GEOindex].degradationfactors[ILTCV1]);
						difftime=max(0,difftime);
						SBAScorr->longtermdegradation=SBASdata[options->GEOindex].degradationfactors[CLTCLSB]+SBASdata[options->GEOindex].degradationfactors[CLTCV1]*difftime;
					}
				} else {
					//Velocity code=0
					if(prevlongterm==1) {
						difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].prevlastlongtermdata[IODP][PRNpos])+1.1;
					} else {
						difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].lastlongtermdata[IODP][PRNpos])+1.1;
					}
					if((1-(difftime-(int)difftime))<1E-4) difftime=(int)difftime+1; //This is to account for problems when converting to integer, when a number is 1.99999998
					SBAScorr->longtermdegradation=SBASdata[options->GEOindex].degradationfactors[CLTCV0]*((int)(difftime/SBASdata[options->GEOindex].degradationfactors[ILTCV0]));
				}
			}
		}

	}

	//Check if user has disabled Slow corrections. In that case, put the corrections to 0
	if(options->NoSlowCorrection==1) {
		//Only take them out if it is not a GEO, as we obtain GEO coordinates from the SBAS message.
		if(GNSS!=GEO) {
			SBAScorr->SatCoordCor[0]=0.;
			SBAScorr->SatCoordCor[1]=0.;
			SBAScorr->SatCoordCor[2]=0.;
			SBAScorr->ClockCor=0.;
		}
	}
	
	//Check if user has disabled Slow corrections sigma. In that case, put the sigma to 0
	if(options->NoSlowSigma==1) {
		SBAScorr->longtermdegradation=0.;
	}

	//Check if user has disabled En Route degradation sigma. In that case, put the sigma to 0
	if(options->NoEnRouteSigma==1) {
		SBAScorr->enroutedegradation=0.;
	}

	////For ionosphere and MT-28, we need satellite coordinates to compute elevation and azimuth, so we need to check we have them (in NPA it is not guaranteed)

	//Get satellite elevation
	if(epoch->sat[satIndex].GNSS!=GEO) {
		block = selectBRDCblock(products->BRDC,&epoch->t,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,SBAScorr->IOD,options);
		if(block==NULL) {
			if(options->precisionapproach==PAMODE) {
				epoch->sat[satIndex].hasOrbitsAndClocks=0;
				return -34;
			}
			SBAScorr->IOD=-1;
			block = selectBRDCblock(products->BRDC,&epoch->t,epoch->sat[satIndex].GNSS,epoch->sat[satIndex].PRN,SBAScorr->IOD,options);
			//Check that we have at least a valid broadcast block regardless the IOD
			if(block==NULL) {
				epoch->sat[satIndex].hasOrbitsAndClocks=0;
				return -35;
			}
			SBAScorr->IODnoSBAS=block->IODE;
		}
		if(nolongterm==1) {
			//Compute transmission time with SBAS clock correction if it had not been done before
			if(options->onlySBASplots==1) {
				//In SBAS plot mode we don't have measurements, so we can't compute TransmissionTime
				//We set the transmission time as the current time
				memcpy(&epoch->sat[satIndex].transTime,&epoch->t,sizeof(TTime));	
				res1=1;
			} else {
				res1 = fillTransmissionTimeSat(epoch,products,satIndex,SBAScorr,options);
			}
			if (res1==0) return -36;
		}

		if (options->timeTrans) {
			memcpy(&t,&epoch->sat[satIndex].transTime,sizeof(TTime));
		} else {
			memcpy(&t,&epoch->t,sizeof(TTime));
		}

		getPositionBRDC(products->BRDC,block,&t,GNSS,SBAScorr->SatCoordbrdc);
		SBAScorr->SatCoord[0]=SBAScorr->SatCoordCor[0]+SBAScorr->SatCoordbrdc[0];
		SBAScorr->SatCoord[1]=SBAScorr->SatCoordCor[1]+SBAScorr->SatCoordbrdc[1];
		SBAScorr->SatCoord[2]=SBAScorr->SatCoordCor[2]+SBAScorr->SatCoordbrdc[2];
		memcpy(epoch->sat[satIndex].position,SBAScorr->SatCoord,sizeof(double)*3);
	}
	getAzimuthElevation(epoch->receiver.orientation,epoch->receiver.aproxPosition,SBAScorr->SatCoord,&epoch->sat[satIndex].azimuth,&epoch->sat[satIndex].elevation);

	//In SBAS plots mode, we compute SBAS sigma for all PRNs in the constellation, and by the elevation (mainly if it is positive)
	// gLAB determines if the satellite is in view from the current position or not.
	if(options->onlySBASplots==1 && epoch->sat[satIndex].elevation<options->elevationMask) {
		if(epoch->sat[satIndex].elevation<0.) {
			//Satellite is not in view
			return -46;
		} else {
			//Satellite is under the minimum elevation
			return -47;
		}
	}


	///////////////////////////
	//// Finish Clock ephemeris covariance computations (if we need to)

	if ( SBAScorr->deltaudresource == 28 ) {
		// Now we have satellite coordinates with SBAS corrections (if available)
		// Get satellite Line of Sight 
		getLineOfSight(SBAScorr->SatCoord,epoch->receiver.aproxPosition,I);
		I[3] = 1;

		// Multipliy C·I  (Being I equal to LoS)
		for ( i=0;i<4;i++ ) {
			CI[i] = 0;
			for ( j=0;j<4;j++ ) {
				CI[i] += C[i][j] * I[j];
			}
		}
		// Multipliy IT·CI(C·I) (IT=I transposed)
		SBAScorr->deltaudre=0;
		for ( i=0;i<4;i++ ) {
			SBAScorr->deltaudre = SBAScorr->deltaudre + I[i] * CI[i];
		}
		SBAScorr->deltaudre=sqrt(SBAScorr->deltaudre);
		//Add Ec degradation term if message type 10 is available
		if ( mt10available == 1 ) {
			SBAScorr->deltaudre=SBAScorr->deltaudre+SBASdata[options->GEOindex].degradationfactors[CCOVARIANCE]*scalefactor;
		}
	}

	///////////////////////////
	////Compute ionosphere

	switch(options->ionoModel) {
		case SBASiono:
			ionosphereModelElectrons = SBASIonoModel(epoch,products,satIndex,&ionoerror,SBAScorr,SBASdata,options);
			if(ionosphereModelElectrons==9999 ) {
				if (options->precisionapproach==PAMODE) {
					if (options->initcoordNPA==1 && epoch->receiver.receiverSolConverged==0) {
						//We are waiting for the receiver solution to converge, we can use Klobuchar model in the first epochs
						ionosphereModelElectrons = klobucharModel(epoch, klbProd, satIndex);
						SBAScorr->ionomodelflag=1;
					} else {
						return ionoerror;						
					}
				} else { //NPA mode
					//Compute with Klobuchar model
					ionosphereModelElectrons = klobucharModel(epoch, klbProd, satIndex);
					SBAScorr->ionomodelflag=1;
				}
			}
			break;
		case Klobuchar:
			//Compute Klobuchar sigma
			ionosphereModelElectrons = klobucharModel(epoch, klbProd, satIndex);
			SBAScorr->ionomodelflag=1;
			break;
		case BeiDou:
			ionosphereModelElectrons = beiDouKlobucharModel(epoch, beiProd, satIndex);
			SBAScorr->ionomodelflag=2;
			break;
		case IONEX:
			ionosphereModelElectrons = ionexModel(epoch, satIndex, Ionex, options); 
			SBAScorr->ionomodelflag=2;
			if (ionosphereModelElectrons == 9999 ) return -45;
			break;
		case FPPP:
			ionosphereModelElectrons = FPPPModel(epoch, satIndex, Fppp, options);
			SBAScorr->ionomodelflag=2;
			if (ionosphereModelElectrons == 9999 ) return -45;	
			break;
		case neQuick:
			ionosphereModelElectrons = NeQuickfunctionCall(epoch, satIndex, neqProd,options);
			SBAScorr->ionomodelflag=2;
			if (ionosphereModelElectrons == 9999 ) return -45;
			break;
		default:
			ionosphereModelElectrons = 0;
			SBAScorr->ionomodelflag=-1;
			break;
	}

	SBAScorr->ionocorrection=ionosphereModelElectrons; //in TECUs

	//Check if user has disabled Ionosphere corrections. In that case, put the value to 0
	if(options->NoIonoCorrection==1) {
		SBAScorr->ionocorrection=0.;
	}

	///////////////////////////
	////Compute sigma flt

	if(nolongterm==0 && nofastcorr==0 && mt10available==1) {
		//We have all necessary corrections for nominal sigma flt computation
		//Delta UDRE is optional for this sigma, if we can compute its value we will use, otherwise we will have a value of 1
		if(SBASdata[options->GEOindex].degradationfactors[RSSUDRE]==0) {
			//RSSUDRE=0
			SBAScorr->sigma2flt=pow(sqrt(SBAScorr->UDREsigma)*SBAScorr->deltaudre+SBAScorr->fastcorrdeg+SBAScorr->RRCdeg+SBAScorr->longtermdegradation+SBAScorr->geonavdegradation+SBAScorr->enroutedegradation,2);
		} else {
			//RSSUDRE=1
			SBAScorr->sigma2flt=pow(sqrt(SBAScorr->UDREsigma)*SBAScorr->deltaudre,2)+pow(SBAScorr->fastcorrdeg,2)+pow(SBAScorr->RRCdeg,2)+pow(SBAScorr->longtermdegradation,2)+pow(SBAScorr->geonavdegradation,2)+pow(SBAScorr->enroutedegradation,2);
		}
	} else if (nolongterm==0 && nofastcorr==0 && mt10available==0) {
		SBAScorr->sigma2flt=pow(sqrt(SBAScorr->UDREsigma)*SBAScorr->deltaudre+options->SigmaOffsetNoMT10,2);
	} else {
		//In non-precision approach if we don't have fast corrections or long term corrections
		//In MOPS-D there is no sigma defined for this case!!!!!!
		//We will use the sigma defined in MOPS-C, 60 meters (which is very high).
		//Setting this sigma will not create any MI (Misleading Information). A MI occurs when we use information which is over the protection level
		SBAScorr->sigma2flt=3600;	//3600=60^2 meters^2
		//Add 1 to the counter of satellites with sigma of 60 metres
		SBASdata[options->GEOindex].numSat60++;

	}


	///////////////////////////
	////Compute sigma of the troposphere

	if(options->NoTropoSigma==1) {
		//User has disabled Troposphere sigma
		SBAScorr->sigma2tropo=0.;
	} else {
		SBAScorr->sigma2tropo=0.12*(1.001/sqrt(0.002001+pow(sin(epoch->sat[satIndex].elevation),2)));	//This computation is in meters
		SBAScorr->sigma2tropo=SBAScorr->sigma2tropo*SBAScorr->sigma2tropo;	//Save the sigma in meters^2
	}

	///////////////////////////
	////Compute sigma of the ionosphere

	if(options->NoIonoSigma==1) {
		//User has disabled Ionosphere sigma
		SBAScorr->sigma2iono=0.;
		epoch->sat[satIndex].ionoSigma=0;
	} else if(SBAScorr->ionomodelflag==1) {
		//We are using klobuchar model
		SBAScorr->sigma2iono=epoch->sat[satIndex].ionoSigma;
	} else if (options->ionoModel == SBASiono) {
		//Ionosphere sigma is already computed in SBASiono function
	} else if (options->ionoModel == IONEX || options->ionoModel == FPPP) {
		//Convert sigma from TECU to meters^2
		lambda = getLambda(epoch->sat[satIndex].GNSS,meas);
		SBAScorr->sigma2iono=epoch->sat[satIndex].ionoSigma*40.3*(lambda*lambda)/(c0*c0)*pow(10,16); //TECU to meters
		SBAScorr->sigma2iono=SBAScorr->sigma2iono*SBAScorr->sigma2iono; //Save in meters^2
	} else {
		//BeiDou and NeQuick does not have sigma or we don't use any ionosphere model
		SBAScorr->sigma2iono=0;
		epoch->sat[satIndex].ionoSigma=0;
	}


	///////////////////////////
	////Compute sigma of the airborne receiver

	if(options->airborneReceiverType==1) {
		//For class receiver the sigma air is 25 meters^2
		SBAScorr->sigma2air=25;
	} else if (options->airborneReceiverType>1) {
		//Sigma noise and sigma divergence have an upperbound limit of 1.8^2 meters^2 for SBAS and 0.36^2 meters^2 for non SBAS
		//We will use the worst case, which is using this upperbound limit.
		//Thence, sigma divergence will be 0 and sigma noise will be 1.8^2 meters^2 for SBAS and 0.36^2 meters^2 for non SBAS
		SBAScorr->sigma2divergence=0;
		if(GNSS==GEO) {			
			SBAScorr->sigma2noise=3.24;	//3.24=1.8^2
		} else {
			SBAScorr->sigma2noise=0.1296;  //0.1296=0.36^2
		}
		SBAScorr->sigma2multipath=pow(0.13+0.53*exp(-epoch->sat[satIndex].elevation*r2d*0.1),2);
		SBAScorr->sigma2air=SBAScorr->sigma2divergence+SBAScorr->sigma2noise+SBAScorr->sigma2multipath;
	} else { //options->airborneReceiverType==0
		//User defined airborne receiver.
		if(options->sigma2divergence!=-1) {
			//User has given a value for sigma divergence
			SBAScorr->sigma2divergence=options->sigma2divergence;
		} else {
			SBAScorr->sigma2divergence=0;
		}

		if(options->sigma2noise!=-1) {
			//User has given a value for sigma noise
			SBAScorr->sigma2noise=options->sigma2noise;
		} else {
			if(GNSS==GEO) {			
				SBAScorr->sigma2noise=3.24;	//3.24=1.8^2
			} else {
				SBAScorr->sigma2noise=0.1296;  //0.1296=0.36^2
			}
		}

		if(options->usersigmamultipath==1) {
			//user has given a sigma multipath model through a file
			if(SBASdata[0].sigmamultipathtype==0) {
				//Model is elevation dependent
				currentvalue=epoch->sat[satIndex].elevation*r2d;  //In degrees
			} else {
				//Model is SNR dependent
				if(options->onlySBASplots==1) {
					currentvalue=999;
				} else {
					if(epoch->measOrder[GNSS].hasSNRmeas==1) {
						currentvalue=epoch->sat[satIndex].meas[epoch->measOrder[GNSS].SNRmeaspos[1]].value;
					} else {
						currentvalue=epoch->sat[satIndex].meas[measIndex].SNRdBHz;
						if (currentvalue==999) {
							if (epoch->measOrder[GNSS].meas2Ind[L1P]!=-1) {
								currentvalue=epoch->sat[satIndex].meas[epoch->measOrder[GNSS].meas2Ind[L1P]].SNRdBHz;
							}
						}
					}
				}
			}
			if(currentvalue<=SBASdata[0].sigmamultipathdata[0][0]) {
				//Value is lower or equal than the minimum range. Use the value of this minimum range
				SBAScorr->sigma2multipath=SBASdata[0].sigmamultipathdata[1][0]*SBASdata[0].sigmamultipathdata[1][0]; //In meters^2
			} else if (currentvalue>=SBASdata[0].sigmamultipathdata[0][SBASdata[0].numsigmamultipath-1]) {
				//Value is greater or equal than the maximum range. Use the value of this maximum range
				SBAScorr->sigma2multipath=SBASdata[0].sigmamultipathdata[1][SBASdata[0].numsigmamultipath-1]*SBASdata[0].sigmamultipathdata[1][SBASdata[0].numsigmamultipath-1];
			} else {
				//We have to search in what range we are and then interpolate
				for(i=0;i<SBASdata[0].numsigmamultipath-1;i++) {
					if(currentvalue>=SBASdata[0].sigmamultipathdata[0][i] && currentvalue<=SBASdata[0].sigmamultipathdata[0][i+1]) {
						//We are inside the range
						unitarydistance=(currentvalue-SBASdata[0].sigmamultipathdata[0][i])/(SBASdata[0].sigmamultipathdata[0][i+1]-SBASdata[0].sigmamultipathdata[0][i]);
						SBAScorr->sigma2multipath=SBASdata[0].sigmamultipathdata[1][i]*(1-unitarydistance)+SBASdata[0].sigmamultipathdata[1][i+1]*unitarydistance;
						SBAScorr->sigma2multipath*=SBAScorr->sigma2multipath; //In meters^2
						break;
					}
				}
			}
		} else if (options->sigma2multipath[0]!=-99999.) {
			//User has given a value for sigma multipath
			SBAScorr->sigma2multipath=pow(options->sigma2multipath[0]+options->sigma2multipath[1]*exp(-epoch->sat[satIndex].elevation*r2d*options->sigma2multipath[2]),2); //In meters^2
		} else {
			//Use default model for sigma multipath
			SBAScorr->sigma2multipath=pow(0.13+0.53*exp(-epoch->sat[satIndex].elevation*r2d*0.1),2); //In meters^2
		}
		SBAScorr->sigma2air=SBAScorr->sigma2divergence+SBAScorr->sigma2noise+SBAScorr->sigma2multipath;
	}

	
	///////////////////////////
	////Compute total SBAS sigma for current satellite

	SBAScorr->SBASsatsigma2=SBAScorr->sigma2flt+SBAScorr->sigma2iono+SBAScorr->sigma2tropo+SBAScorr->sigma2air;

	return 1;

}

/*****************************************************************************
 * Name        : SBASIonoModel
 * Description : Obtains the ionospheric correction from SBAS data
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * int  satIndex                   I  N/A  Index of the satellite to obtain 
 * int *errorvalue                 O  N/A  Error code
 * TSBAScorr *SBAScorr             IO N/A  Struct with the SBAS corrections to be applied
 *                                          to the current satellite
 * TSBASdata *SBASdata             I  N/A  Struct with SBAS data
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (double)         O  m    SBAS Iono correction (in TECUs)  
 *                                         9999 is returned when interpolation 
 *                                         is not possible (no data or timeout)
 *****************************************************************************/
double SBASIonoModel (TEpoch *epoch, TGNSSproducts *products, int satIndex, int *errorvalue, TSBAScorr *SBAScorr, TSBASdata *SBASdata, TOptions *options) {

	int				i,j;
	int 			InterpolationMode=0,InterpolationMode1,InterpolationMode2;
	int				InterpolationMode_aux1,InterpolationMode_aux2,InterpolationMode_aux3,InterpolationMode_aux4;
	int				IGP1,IGP2,IGP3,IGP4,IGP90;
	int				BandNumber1,BandNumber2,BandNumber3,BandNumber4;
	int				numIGP90=0,IGPretrieved=0;
	//int				ret1,ret2,ret3,ret4;
	int				IGPnumber[5],IGPBandNumber[5],IGPcheck[5];
	int				IGPnumber_aux1[5],IGPnumber_aux2[5],IGPnumber_aux3[5],IGPnumber_aux4[5];
	int				IGPBandNumber_aux1[5],IGPBandNumber_aux2[5],IGPBandNumber_aux3[5],IGPBandNumber_aux4[5];
	int				mt10available;
	double			difftime,olddifftime;
	double			increment,check;
	double			IPPlat,IPPlon;
	double			IGPlat,IGPlat_aux1,IGPlat_aux2,IGPlat_aux3;
	double			IGPlon1,IGPlon2,IGPlon3,IGPlon4,IGPlon_auxleft,IGPlon_auxright,IGPlon_aux3;
	double			IGPfinal_lon1,IGPfinal_lon2,IGPfinal_lon3,IGPfinal_lon4;
	double			IGPfinal_lat1,IGPfinal_lat2,IGPfinal_lat3,IGPfinal_lat4;
	//double			IGP3_corner_lat,IGP3_corner_lon;
	double			VM1,VM2,VM3,VM4,SI1,SI2,SI3,SI4;
	double			IGPDelays[5],IGPSigma2[5];
	double			VerticalDelay,eps_iono[5],Sigma2,IPP_Weight[5];
	double			SlantDelay,Fpp;
	double			XIpp,xct=0;
	double			elevation,azimuth;
	TPiercePoint    PiercePointvector;

	mt10available=SBAScorr->mt10avail;
	eps_iono[0]=eps_iono[1]=eps_iono[2]=eps_iono[3]=eps_iono[4]=0;
	*errorvalue=1;


	//If we are only using SBAS iono but no SBAS corrections, we need to check if we have a GEO satellite selected
	if(options->GEOindex<0) {
		if(SBASdata[0].numSBASsatellites==0) {
			//No GEO available. Leave options->GEOindex negative to keep checking this condition
			*errorvalue=-1;
			return 9999;
		} else if (options->GEOPRN==0) {
			//Use data from all GEO
			options->GEOindex=0;
			options->GEOPRN=SBASdata[options->GEOindex].PRN;
		} else if (options->GEOPRN==1) {
			//Use the GEO PRN from the first SBAS data read, which will be in position one of the SBASdata vector
			options->GEOindex=1;
			options->GEOPRN=SBASdata[options->GEOindex].PRN;
		} else { //MINGEOPRN<=options->GEOPRN<=MAXGEOPRN
			//The user has given the GEO PRN
			options->GEOindex=SBASdata[0].GEOPRN2pos[options->GEOPRN];
			if(options->GEOindex==-1) {
				//We have no data from this satellite. Maybe in future epochs we receive data
				*errorvalue=-2;
				return 9999;
			}
		}
	}

	/*
	//Calculate the Iono Pierce Point at 350Km 
	getIonoPiercePoint(epoch, &PiercePointvector, satIndex, SBAS_EARTH_RADIUS/1000, SBAS_HEIGHT/1000,1);

	//Convert longitude to 0..360º
		IPPlon=modulo(PiercePointvector.longitude+360,360);
		IPPlat=PiercePointvector.fi;

	*/

	if(SBAScorr->SBASplotIonoAvail==0) {
		//We are not computing SBAS iono plots availability

		initPiercePoint(&PiercePointvector);

		elevation=epoch->sat[satIndex].elevation;
		azimuth=epoch->sat[satIndex].azimuth;

		//Compute the (MOPS) pierce point
		XIpp=Pi/2-elevation-asin((SBAS_EARTH_RADIUS)/(SBAS_EARTH_RADIUS+SBAS_HEIGHT)*cos(elevation));
		PiercePointvector.fi=r2d*asin(sin(epoch->receiver.aproxPositionNEU[0])*cos(XIpp)+cos(epoch->receiver.aproxPositionNEU[0])*sin(XIpp)*cos(azimuth));
		PiercePointvector.longitude=r2d*(epoch->receiver.aproxPositionNEU[1]+asin(sin(XIpp)*sin(azimuth)/cos(PiercePointvector.fi*d2r)));

		//--- MOPS C aclaration  (Ap. A, pp A-36) --------
		if (PiercePointvector.fi>70) {
				xct= tan(XIpp)*cos(azimuth)-tan(Pi/2-PiercePointvector.fi*d2r);
				if (xct>0) PiercePointvector.longitude=(epoch->receiver.aproxPositionNEU[1]+Pi-(PiercePointvector.longitude*d2r-epoch->receiver.aproxPositionNEU[1]))*r2d;
		}

		if (PiercePointvector.fi<-70) {
				xct= -tan(XIpp)*cos(azimuth)-tan(Pi/2-PiercePointvector.fi*d2r);
				if (xct>0) PiercePointvector.longitude=(epoch->receiver.aproxPositionNEU[1]+Pi-(PiercePointvector.longitude*d2r-epoch->receiver.aproxPositionNEU[1]))*r2d;
		}

		if(PiercePointvector.fi>0) {
			//This is to account for problems when number is X.99999998, rounding it to the next integer (when PiercePointvector.fi is positive
			if((1-(PiercePointvector.fi-(int)PiercePointvector.fi))<1E-4) PiercePointvector.fi=(int)PiercePointvector.fi+1; 
		} else if (PiercePointvector.fi<0){
			//This is to account for problems when number is X.99999998, rounding it to the next integer (when PiercePointvector.fi is negative
			if((1+(PiercePointvector.fi-(int)PiercePointvector.fi))<1E-4) PiercePointvector.fi=(int)PiercePointvector.fi-1; 
		}

		//Convert longitude to 0..360º
		IPPlon=modulo(PiercePointvector.longitude+360.,360);
		IPPlat=PiercePointvector.fi;
		
		//Save IPP coordinates in epoch structure
		epoch->IPPlat=PiercePointvector.fi;	//-90..90º
		epoch->IPPlon=PiercePointvector.longitude;	//-180..180º

	} else {
		//We are computing SBAS iono plots availability. We will make the assumption we have vertical rays, as we only need the vertical TEC
		elevation=epoch->sat[satIndex].elevation=-90.*d2r; //We will set to -90º so when printing SBASIONO messages so we know it is from the iono availability computation
		azimuth=epoch->sat[satIndex].azimuth=0; //The azimuth is an arbitrary value, as we are not going to use it

		IPPlat=epoch->IPPlat;
		IPPlon=modulo(epoch->IPPlon+360.,360);

	}


	//Check that the current Iono mask has no time out
	difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].lastmsgreceived[IONOSPHERICGRIDPOINTSMASKS]);
	olddifftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].oldlastmsgreceived[IONOSPHERICGRIDPOINTSMASKS]);
	if(SBASdata[options->GEOindex].lastmsgreceived[IONOSPHERICGRIDPOINTSMASKS].MJDN==-1) {
		//No Iono mask arrived
		InterpolationMode=-1;
		*errorvalue=-37;
		return 9999;
	} else if(difftime>(double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][IONOSPHERICGRIDPOINTSMASKS])) {
		//The current mask has time out, so the old one (if we have one stored) will also have time out
		if(satIndex==epoch->lastSBASindex) {
			SBASdata[options->GEOindex].lastmsgreceived[IONOSPHERICGRIDPOINTSMASKS].MJDN=-1;
			SBASdata[options->GEOindex].lastmsgreceived[IONOSPHERICGRIDPOINTSMASKS].SoD=-1;
			for(i=0;i<11;i++) {
				for(j=0;j<202;j++) {
					if(SBASdata[options->GEOindex].IGP2Mask[i][j]==SBASdata[options->GEOindex].IODImask) {
						SBASdata[options->GEOindex].IGP2Mask[i][j]=4;
					}
				}
			}
			SBASdata[options->GEOindex].IODImask=4;
		}
		InterpolationMode=-1;
		*errorvalue=-38;
		return 9999;
	} else if ((olddifftime>(double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][IONOSPHERICGRIDPOINTSMASKS])) && (SBASdata[options->GEOindex].oldlastmsgreceived[IONOSPHERICGRIDPOINTSMASKS].MJDN!=-1)) {
		//The old mask is timed out. Discard values
		if(satIndex==epoch->lastSBASindex) {
			for(i=0;i<11;i++) {
				for(j=0;j<202;j++) {
					if(SBASdata[options->GEOindex].IGP2Mask[i][j]==SBASdata[options->GEOindex].oldIODImask) {
						SBASdata[options->GEOindex].IGP2Mask[i][j]=4;
					}
				}
			}
			SBASdata[options->GEOindex].oldmaskdiscarded[IONOSPHERICGRIDPOINTSMASKS]=1;
			SBASdata[options->GEOindex].oldlastmsgreceived[IONOSPHERICGRIDPOINTSMASKS].MJDN=-1;
			SBASdata[options->GEOindex].oldlastmsgreceived[IONOSPHERICGRIDPOINTSMASKS].SoD=-1;
			SBASdata[options->GEOindex].oldIODImask=4;
		}
	}

	if(mt10available==-1) {
		//Availability of message type 10 has not been done (due to we are using SBAS iono but not SBAS corrections). Check it now
		difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].lastmsgreceived[DEGRADATIONPARAMETERS]);
		if(SBASdata[options->GEOindex].lastmsgreceived[DEGRADATIONPARAMETERS].MJDN==-1) {
			//Message Type 10 time out or without data
			mt10available=0;
		} else if(difftime>(double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][DEGRADATIONPARAMETERS]) ) {
			//Message Type 10 time out or without data
			SBASdata[options->GEOindex].lastmsgreceived[DEGRADATIONPARAMETERS].MJDN=-1;
			SBASdata[options->GEOindex].degradationfactors[RSSUDRE]=-1;

			mt10available=0;
		} else {
			mt10available=1;
		}
	}


	if (IPPlat>85.) {
		//Pierce point greater than 85º
		IPP2Sqr(IPPlat,IPPlon,&IGPlat,&IGPlon3,&increment);

		IGPlon1=modulo(IGPlon3+180,360);
		IGPlon2=modulo(IGPlon3+270,360);
		IGPlon4=modulo(IGPlon3+90,360);
		//--- Looking the band 9  ------------
		IGPLatLon2BandNumberIGP(IGPlat,IGPlon1,&BandNumber1,&IGP1,&IGP90);
		IGP1=IGP90;
		BandNumber1=9;
		IGPLatLon2BandNumberIGP(IGPlat,IGPlon2,&BandNumber2,&IGP2,&IGP90);
		IGP2=IGP90;
		BandNumber2=9;
		IGPLatLon2BandNumberIGP(IGPlat,IGPlon3,&BandNumber3,&IGP3,&IGP90);
		IGP3=IGP90;
		BandNumber3=9;
		IGPLatLon2BandNumberIGP(IGPlat,IGPlon4,&BandNumber4,&IGP4,&IGP90);
		IGP4=IGP90;
		BandNumber4=9;
		if (IGP1*IGP2*IGP3*IGP4>0) {
			numIGP90=SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber1][IGP1]][BandNumber1][IGP1]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber2][IGP2]][BandNumber2][IGP2]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber3][IGP3]][BandNumber3][IGP3]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber4][IGP4]][BandNumber4][IGP4];
			//All IGPs must bet set as "1" in the Mask.
			if(numIGP90<4) {
				*errorvalue=-40;
				InterpolationMode=-1;
				return 9999;
			}
		}

		//--- Looking the other bands ------
		IGPLatLon2BandNumberIGP(IGPlat,IGPlon1,&BandNumber1,&IGP1,&IGP90);
		IGPLatLon2BandNumberIGP(IGPlat,IGPlon2,&BandNumber2,&IGP2,&IGP90);
		IGPLatLon2BandNumberIGP(IGPlat,IGPlon3,&BandNumber3,&IGP3,&IGP90);
		IGPLatLon2BandNumberIGP(IGPlat,IGPlon4,&BandNumber4,&IGP4,&IGP90);
		if (IGP1*IGP2*IGP3*IGP4>0) {
			numIGP90=SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber1][IGP1]][BandNumber1][IGP1]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber2][IGP2]][BandNumber2][IGP2]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber3][IGP3]][BandNumber3][IGP3]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber4][IGP4]][BandNumber4][IGP4];
			//All IGPs must bet set as "1" in the Mask.
			if(numIGP90<4) {
				*errorvalue=-40;
				InterpolationMode=-1;
				return 9999;
			}
		} else {
			*errorvalue=-39;
			InterpolationMode=-1;
			return 9999;
		}

		IGPretrieved=1;

	} else if (IPPlat<-85.) {
				//Pierce point less than -85º
				IPP2Sqr(IPPlat,IPPlon,&IGPlat,&IGPlon3,&increment);

				IGPlon1=modulo(IGPlon3+180,360);
				IGPlon2=modulo(IGPlon3+270,360);
				IGPlon4=modulo(IGPlon3+90,360);
				//--- Looking the band 10 ------------
				IGPLatLon2BandNumberIGP(IGPlat,IGPlon1,&BandNumber1,&IGP1,&IGP90);
				IGP1=IGP90;
				BandNumber1=10;
				IGPLatLon2BandNumberIGP(IGPlat,IGPlon2,&BandNumber2,&IGP2,&IGP90);
				IGP2=IGP90;
				BandNumber2=10;
				IGPLatLon2BandNumberIGP(IGPlat,IGPlon3,&BandNumber3,&IGP3,&IGP90);
				IGP3=IGP90;
				BandNumber3=10;
				IGPLatLon2BandNumberIGP(IGPlat,IGPlon4,&BandNumber4,&IGP4,&IGP90);
				IGP4=IGP90;
				BandNumber4=10;
				if (IGP1*IGP2*IGP3*IGP4>0) {
						numIGP90=SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber1][IGP1]][BandNumber1][IGP1]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber2][IGP2]][BandNumber2][IGP2]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber3][IGP3]][BandNumber3][IGP3]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber4][IGP4]][BandNumber4][IGP4];
						//All IGPs must bet set as "1" in the Mask.
						if(numIGP90<4) {
				*errorvalue=-40;
								InterpolationMode=-1;
								return 9999;
						}
				}

				//--- Looking the other bands ------
				IGPLatLon2BandNumberIGP(IGPlat,IGPlon1,&BandNumber1,&IGP1,&IGP90);
				IGPLatLon2BandNumberIGP(IGPlat,IGPlon2,&BandNumber2,&IGP2,&IGP90);
				IGPLatLon2BandNumberIGP(IGPlat,IGPlon3,&BandNumber3,&IGP3,&IGP90);
				IGPLatLon2BandNumberIGP(IGPlat,IGPlon4,&BandNumber4,&IGP4,&IGP90);
				if (IGP1*IGP2*IGP3*IGP4>0) {
						numIGP90=SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber1][IGP1]][BandNumber1][IGP1]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber2][IGP2]][BandNumber2][IGP2]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber3][IGP3]][BandNumber3][IGP3]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber4][IGP4]][BandNumber4][IGP4];
						//All IGPs must bet set as "1" in the Mask.
						if(numIGP90<4) {
				*errorvalue=-40;
								InterpolationMode=-1;
								return 9999;
						}
				} else {
			*errorvalue=-39;
						InterpolationMode=-1;
						return 9999;
				}

				IGPretrieved=1;

	} else if ((IPPlat>=75.)&&(IPPlat<=85.)) {
		IPP2Sqr(IPPlat,IPPlon,&IGPlat_aux1,&IGPlon1,&increment);

		if (IGPlon1<0) {
			//Longitude for IGP is negative when it should be from 0..360º
			*errorvalue=-39;
			InterpolationMode=-1;
			return 9999;
		}

		IGPlat_aux2=IGPlat_aux1+increment;
		IGPlon2=IGPlon1+increment;

		IGPLatLon2BandNumberIGP(IGPlat_aux1,IGPlon1,&BandNumber3,&IGP3,&IGP90);
		IGP3=IGP90;
		BandNumber3=9;
		IGPLatLon2BandNumberIGP(IGPlat_aux1,IGPlon2,&BandNumber4,&IGP4,&IGP90);
		IGP4=IGP90;
		BandNumber4=9;
		

		if (IGP3+IGP4>0) { //One of the IGPs at 75º can be not set because we can interpolate in a triangle
			numIGP90=SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber3][IGP3]][BandNumber3][IGP3]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber4][IGP4]][BandNumber4][IGP4];
			//Both IGPs must bet set as "1" in the Mask to do the virtual interpolation.
			if((numIGP90!=2 && (IGP3*IGP4>0)) || (numIGP90<1 && (IGP3+IGP4>0))) {
				//Points at Band 9 are not available, look in vertical bands
				IGPLatLon2BandNumberIGP(IGPlat_aux1,IGPlon1,&BandNumber3,&IGP3,&IGP90);
				IGPLatLon2BandNumberIGP(IGPlat_aux1,IGPlon2,&BandNumber4,&IGP4,&IGP90);
				if (IGP3+IGP4>0) { //One if the IGPs at 75º can be not set because we can interpolate in a triangle
					numIGP90=SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber3][IGP3]][BandNumber3][IGP3]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber4][IGP4]][BandNumber4][IGP4];
					if((numIGP90!=2 && (IGP3*IGP4>0)) || (numIGP90<1 && (IGP3+IGP4>0))) {
						//The two nearest IGPs are not available
						*errorvalue=-40;
						InterpolationMode=-1;
						return 9999;
					}
				}
			}
		} else {
			//Points at Band 9 are not available, look in vertical bands
			IGPLatLon2BandNumberIGP(IGPlat_aux1,IGPlon1,&BandNumber3,&IGP3,&IGP90);
			IGPLatLon2BandNumberIGP(IGPlat_aux1,IGPlon2,&BandNumber4,&IGP4,&IGP90);
			if (IGP3+IGP4>0) { //One if the IGPs at 75º can be not set because we can interpolate in a triangle
				numIGP90=SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber3][IGP3]][BandNumber3][IGP3]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber4][IGP4]][BandNumber4][IGP4];
				if((numIGP90!=2 && (IGP3*IGP4>0)) || (numIGP90<1 && (IGP3+IGP4>0))) {
					//The two nearest IGPs are not available
					*errorvalue=-40;
					InterpolationMode=-1;
					return 9999;
				}
			}
		}

		//We select the IGPs for the latitude band of 85º

		if(BandNumber3==9) {
			//--- Looking the band 9  ------------
			IGPlon_auxleft=(int)(IGPlon1/30)*30;
			IGPlon_auxright=IGPlon_auxleft+30;
			IGPLatLon2BandNumberIGP(IGPlat_aux2,IGPlon_auxright,&BandNumber1,&IGP1,&IGP90);
			BandNumber1=9;
			IGP1=IGP90;
			IGPLatLon2BandNumberIGP(IGPlat_aux2,IGPlon_auxleft,&BandNumber2,&IGP2,&IGP90);
			BandNumber2=9;
			IGP2=IGP90;
		  
			if (IGP1*IGP2>0) {
				numIGP90=SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber1][IGP1]][BandNumber1][IGP1]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber2][IGP2]][BandNumber2][IGP2];
				//Both IGPs must bet set as "1" in the Mask to do the virtual interpolation.
				if(numIGP90==2) IGPretrieved=1;
			}
		}
		if(IGPretrieved!=1 && BandNumber3!=9) {
			//-----------------------------------
			//--- Looking the other bands ------
			IGPlon_auxleft=(int)(IGPlon1/90)*90;
			IGPlon_auxright=IGPlon_auxleft+90;
			IGPLatLon2BandNumberIGP(IGPlat_aux2,IGPlon_auxright,&BandNumber1,&IGP1,&IGP90);
			IGPLatLon2BandNumberIGP(IGPlat_aux2,IGPlon_auxleft,&BandNumber2,&IGP2,&IGP90);

			if (IGP1*IGP2>0) {
				numIGP90=SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber1][IGP1]][BandNumber1][IGP1]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber2][IGP2]][BandNumber2][IGP2];
				if (numIGP90==2) {
					//Both IGPs must to bet set as "1" in the Mask to do the virtual interpolation.
					IGPretrieved=1;
				} else {
					//The two nearest IGPs are not available
					*errorvalue=-40;
					InterpolationMode=-1;
					return 9999;
				}
			} else {
				//At least one IGP is not in the MOPS grid for bands 0 to 8
				*errorvalue=-39;
				InterpolationMode=-10;
				return 9999;
			}
		} else if (IGPretrieved!=1 && BandNumber3==9) {
			//The two nearest IGPs in Band 9 are not available
			*errorvalue=-40;
			InterpolationMode=-1;
			return 9999;
		}

	} else if ((IPPlat<-75)&&(IPPlat>=-85)) {
		IPP2Sqr(IPPlat,IPPlon,&IGPlat_aux1,&IGPlon1,&increment);

		if (IGPlon1<0) {
			//Longitude for IGP is negative when it should be from 0..360º
			*errorvalue=-39;
			InterpolationMode=-1;
			return 9999;
		}

		IGPlat_aux2=IGPlat_aux1+increment;
		IGPlon2=IGPlon1+increment;

		IGPLatLon2BandNumberIGP(IGPlat_aux2,IGPlon2,&BandNumber1,&IGP1,&IGP90);
		IGP1=IGP90;
		BandNumber1=10;
		IGPLatLon2BandNumberIGP(IGPlat_aux2,IGPlon1,&BandNumber2,&IGP2,&IGP90);
		IGP2=IGP90;
		BandNumber2=10;

		if (IGP1+IGP2>0) { //One of the IGPs at -75º can be not set because we can interpolate in a triangle
			numIGP90=SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber1][IGP1]][BandNumber1][IGP1]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber2][IGP2]][BandNumber2][IGP2];
			//Both IGPs must bet set as "1" in the Mask to do the virtual interpolation.
			if((numIGP90!=2 && (IGP1*IGP2>0)) || (numIGP90<1 && (IGP1+IGP2>0))) {
				//Points at Band 10 are not available, look in vertical bands
				IGPLatLon2BandNumberIGP(IGPlat_aux1,IGPlon1,&BandNumber1,&IGP1,&IGP90);
				IGPLatLon2BandNumberIGP(IGPlat_aux1,IGPlon2,&BandNumber2,&IGP2,&IGP90);
				if (IGP1+IGP2>0) { //One if the IGPs at -75º can be not set because we can interpolate in a triangle
					numIGP90=SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber1][IGP1]][BandNumber1][IGP1]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber2][IGP2]][BandNumber2][IGP2];
					if((numIGP90!=2 && (IGP1*IGP2>0)) || (numIGP90<1 && (IGP1+IGP2>0))) {
						//The two nearest IGPs are not available
						*errorvalue=-40;
						InterpolationMode=-1;
						return 9999;
					}
				}
			}
		} else {
			//Points at Band 10 are not available, look in vertical bands
			IGPLatLon2BandNumberIGP(IGPlat_aux1,IGPlon1,&BandNumber1,&IGP1,&IGP90);
			IGPLatLon2BandNumberIGP(IGPlat_aux1,IGPlon2,&BandNumber2,&IGP2,&IGP90);
			if (IGP1+IGP2>0) { //One if the IGPs at -75º can be not set because we can interpolate in a triangle
				numIGP90=SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber1][IGP1]][BandNumber1][IGP1]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber2][IGP2]][BandNumber2][IGP2];
				if((numIGP90!=2 && (IGP1*IGP2>0)) || (numIGP90<1 && (IGP1+IGP2>0))) {
					//The two nearest IGPs are not available
					*errorvalue=-40;
					InterpolationMode=-1;
					return 9999;
				}
			}
		}


		//We select the IGPs for the latitude band of -85º

		if(BandNumber1==10) {
			//--- Looking the band 10  ------------
			IGPlon_auxleft=(int)((IGPlon1-10)/30)*30+10;
			IGPlon_auxright=IGPlon_auxleft+30;
			IGPLatLon2BandNumberIGP(IGPlat_aux1,IGPlon_auxleft,&BandNumber3,&IGP3,&IGP90);
			BandNumber3=10;
			IGP3=IGP90;
			IGPLatLon2BandNumberIGP(IGPlat_aux1,IGPlon_auxright,&BandNumber4,&IGP4,&IGP90);
			BandNumber4=10;
			IGP4=IGP90;

			if (IGP3*IGP4>0) {
				numIGP90=SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber3][IGP3]][BandNumber3][IGP3]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber4][IGP4]][BandNumber4][IGP4];
				//Both IGPs must to bet set as "1" in the Mask to do the virtual interpolation.
				if (numIGP90==2) IGPretrieved=1;
			}
		}

		if(IGPretrieved!=1 && BandNumber1!=10) {
			//--- Looking the other bands ------
			IGPlon_auxleft=(int)((IGPlon1-40)/90)*90+40;
			IGPlon_auxright=IGPlon_auxleft+90;
			IGPLatLon2BandNumberIGP(IGPlat_aux1,IGPlon_auxleft,&BandNumber3,&IGP3,&IGP90);
			IGPLatLon2BandNumberIGP(IGPlat_aux1,IGPlon_auxright,&BandNumber4,&IGP4,&IGP90);

			if (IGP3*IGP4>0) {
				numIGP90=SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber3][IGP3]][BandNumber3][IGP3]+SBASdata[options->GEOindex].IGPinMask[SBASdata[options->GEOindex].IGP2Mask[BandNumber4][IGP4]][BandNumber4][IGP4];
				if (numIGP90==2) {
					//Both IGPs must to bet set as "1" in the Mask to do the virtual interpolation.
					IGPretrieved=1;
				} else {
					//The two nearest IGPs are not available
					*errorvalue=-40;
					InterpolationMode=-1;
					return 9999;
				}
			} else {
				//At least one IGP is not in the MOPS grid for bands 0 to 8
				*errorvalue=-39;
				InterpolationMode=-10;
				return 9999;
			}
		} else if (IGPretrieved!=1 && BandNumber1==10) {
			//The two nearest IGPs in Band 10 are not available
			*errorvalue=-39;
			InterpolationMode=-1;
			return 9999;
		}
	} else if ((IPPlat>=60)||(IPPlat<-60)) {

		//::::::::::  |Lat|<= 75 deg. :::::::::::::::::::::::::::::::::::     
		//------------ 60 < |LAT| < 75 ------------------------------ 

		IPP2Sqr(IPPlat,IPPlon,&IGPlat_aux1,&IGPlon1,&increment);


		//... RECTANGLE or TRIANGLES : 5x10: ...............
		//Note: For 60<|LAT|, the "IPP2Sqr" looks for the 10x10 square with the IPP inside.               

	
		if (IPPlat-IGPlat_aux1<5) {
			//The closest IGP in the left-down corner is less than 5º away in latitude, so the IGPs above can be only 5º away
			IGPsearch(IPPlat,IPPlon,IGPlat_aux1,IGPlon1,5,increment,SBASdata[options->GEOindex].IGPinMask,SBASdata[options->GEOindex].IGP2Mask,&InterpolationMode,IGPnumber,IGPBandNumber);
		} else {
			//The closest IGP in the left-down corner is more han 5º away in latitude, so we need to add 5º to the latitude so the distance remains under 5º from the upper IGPs
			IGPlat_aux1=IGPlat_aux1+5;
			IGPsearch(IPPlat,IPPlon,IGPlat_aux1,IGPlon1,5,increment,SBASdata[options->GEOindex].IGPinMask,SBASdata[options->GEOindex].IGP2Mask,&InterpolationMode,IGPnumber,IGPBandNumber);
		}

		IGPlon2=IGPlon1+10;
		IGPlat_aux2=IGPlat_aux1+5;
	
		if(InterpolationMode<0) {
			//++++++++ SQUARES or TRIANGLES 10x10 ++++++++++++++++++++++++++++

			//SQUARE 1: 10x10 when no 5x10 rectangle is available

			InterpolationMode1=-30;
			InterpolationMode2=-30;

			if (IPPlat<70.) {
				IGPsearch(IPPlat,IPPlon,IGPlat_aux1,IGPlon1,increment,increment,SBASdata[options->GEOindex].IGPinMask,SBASdata[options->GEOindex].IGP2Mask,&InterpolationMode1,IGPnumber_aux1,IGPBandNumber_aux1);


				if (InterpolationMode1==0) {
					InterpolationMode=0;
					IGPlon2=IGPlon1+increment;
					IGPlat_aux2=IGPlat_aux1+increment;
					for(i=1;i<=4;i++) {
						IGPBandNumber[i]=IGPBandNumber_aux1[i];
						IGPnumber[i]=IGPnumber_aux1[i];
					}
				}
			}

			//SQUARE 2: 10x10 when no 5x10 rectangle is available, moving IGP latitude -5º

			if (IPPlat>=-70. && InterpolationMode1!=0) {

				IGPlat_aux3=IGPlat_aux1-5;
				IGPsearch(IPPlat,IPPlon,IGPlat_aux3,IGPlon1,increment,increment,SBASdata[options->GEOindex].IGPinMask,SBASdata[options->GEOindex].IGP2Mask,&InterpolationMode2,IGPnumber_aux2,IGPBandNumber_aux2);


				if (InterpolationMode2==0) {
					InterpolationMode=0;
					IGPlat_aux1=IGPlat_aux1-5;
					IGPlon2=IGPlon1+increment;
					IGPlat_aux2=IGPlat_aux1+increment;
					for(i=1;i<=4;i++) {
						IGPBandNumber[i]=IGPBandNumber_aux2[i];
						IGPnumber[i]=IGPnumber_aux2[i];
					}
				}
			}

			if(InterpolationMode1!=0 && InterpolationMode2!=0) {
				//If not 10x10 squares are available, try with 10x10 triangles:
			
				if (InterpolationMode1>=1) {
					InterpolationMode=InterpolationMode1;
					IGPlon2=IGPlon1+increment;
					IGPlat_aux2=IGPlat_aux1+increment;
					for(i=1;i<=4;i++) {
						IGPBandNumber[i]=IGPBandNumber_aux1[i];
						IGPnumber[i]=IGPnumber_aux1[i];
					}
				} else if (InterpolationMode2>=1) {
					InterpolationMode=InterpolationMode2;
					IGPlat_aux1=IGPlat_aux1-5;
					IGPlon2=IGPlon1+increment;
					IGPlat_aux2=IGPlat_aux1+increment;
					for(i=1;i<=4;i++) {
						IGPBandNumber[i]=IGPBandNumber_aux2[i];
						IGPnumber[i]=IGPnumber_aux2[i];
					}
				} else {
					//No 5x10 nor 10x10 rectangle or square available in Mask.
					//Thence, No interpolation can be done.
					*errorvalue=-40;
					InterpolationMode=-1;
					return 9999;

				}
			}
		}

	} else {

		//------------ |LAT| < 60 ------------------------------------
		IPP2Sqr(IPPlat,IPPlon,&IGPlat_aux1,&IGPlon1,&increment);
		IGPlon2=IGPlon1+increment;
		IGPlat_aux2=IGPlat_aux1+increment;

		//.... 5x5 SQUARES .........................................
		IGPsearch(IPPlat,IPPlon,IGPlat_aux1,IGPlon1,increment,increment,SBASdata[options->GEOindex].IGPinMask,SBASdata[options->GEOindex].IGP2Mask,&InterpolationMode,IGPnumber,IGPBandNumber);

		if (InterpolationMode<0) {

			/*10x10 squares, when no 5x5 square available
			As the IGP are at a distance of 5º in latitude and longitude, we can try different squares:
			Square1: IGPs in 10x10 around the IPP	          Square2: IGPs in 10x10 around the IPP moved -5º in longitude
			o   o   X   o   X                          		  o   X   o   X   o
																				  
			o   o   o   o   o                         		  o   o   o   o   o
					  .                                                 .
			o   o   X   o   X 		                          o   X   o   X   o

			o   o   o   o   o                          		  o   o   o   o   o
														   
			o   o   o   o   o			      				  o   o   o   o   o
							  

			Square3: IGPs in 10x10 around the IPP	          Square4: IGPs in 10x10 around the IPP moved -5º in latitude
			moved -5º in latitude and longitude
			o   o   o   o   o                          		  o   o   o   o   o
																				  
			o   X   o   X   o                         		  o   o   X   o   X
					  .                                                 .
			o   o   o   o   o 		                          o   o   o   o   o

			o   X   o   X   o                          		  o   o   X   o   X
															   
			o   o   o   o   o			      				  o   o   o   o   o

			*/


			increment=10;

			InterpolationMode_aux1=-30;
			InterpolationMode_aux2=-30;
			InterpolationMode_aux3=-30;
			InterpolationMode_aux4=-30;

			//SQUARE 1:
			IGPlon_aux3=IGPlon1;
			IGPlat_aux3=IGPlat_aux1;

			check=(int)(IGPlon_aux3/10)*10-IGPlon_aux3;
			check=fabs(check);
			//Variable "check" looks if the longitude is a multiple of 10. Instead of comparing with zero, compares with 1E-4 (nearly 0) to avoid problems with decimals
			if ((IPPlat<55.)||(check<1E-4)) {

				IGPsearch(IPPlat,IPPlon,IGPlat_aux3,IGPlon_aux3,increment,increment,SBASdata[options->GEOindex].IGPinMask,SBASdata[options->GEOindex].IGP2Mask,&InterpolationMode_aux1,IGPnumber_aux1,IGPBandNumber_aux1);


				if (InterpolationMode_aux1==0) {
					InterpolationMode=0;
					IGPlon1=IGPlon_aux3;
					IGPlat_aux1=IGPlat_aux3;
					IGPlon2=IGPlon1+increment;
					IGPlat_aux2=IGPlat_aux1+increment;
					for(i=1;i<=4;i++) {
						IGPBandNumber[i]=IGPBandNumber_aux1[i];
						IGPnumber[i]=IGPnumber_aux1[i];
					}
				}
			}

			if(InterpolationMode_aux1!=0) {
				//SQUARE 2:
				IGPlon_aux3=IGPlon1-5;
				IGPlat_aux3=IGPlat_aux1;

				check=(int)(IGPlon_aux3/10)*10-IGPlon_aux3;
				check=fabs(check);
				//Variable "check" looks if the longitude is a multiple of 10. Instead of comparing with zero, compares with 1E-4 (nearly 0) to avoid problems with decimals
				if ((IPPlat<55.)||(check<1E-4)) {

					IGPsearch(IPPlat,IPPlon,IGPlat_aux3,IGPlon_aux3,increment,increment,SBASdata[options->GEOindex].IGPinMask,SBASdata[options->GEOindex].IGP2Mask,&InterpolationMode_aux2,IGPnumber_aux2,IGPBandNumber_aux2);


					if (InterpolationMode_aux2==0) {
						InterpolationMode=0;
						IGPlon1=IGPlon_aux3;
						IGPlat_aux1=IGPlat_aux3;
						IGPlon2=IGPlon1+increment;
						IGPlat_aux2=IGPlat_aux1+increment;
						for(i=1;i<=4;i++) {
							IGPBandNumber[i]=IGPBandNumber_aux2[i];
							IGPnumber[i]=IGPnumber_aux2[i];
						}
					}
				}
				if (InterpolationMode_aux2!=0) {
						
					//SQUARE 3:
					IGPlon_aux3=IGPlon1-5;
					IGPlat_aux3=IGPlat_aux1-5;

					check=(int)(IGPlon_aux3/10)*10-IGPlon_aux3;
					check=fabs(check);
					//Variable "check" looks if the longitude is a multiple of 10. Instead of comparing with zero, compares with 1E-4 (nearly 0) to avoid problems with decimals
					if ((IPPlat>=-55.)||(check<1E-4)) {

						IGPsearch(IPPlat,IPPlon,IGPlat_aux3,IGPlon_aux3,increment,increment,SBASdata[options->GEOindex].IGPinMask,SBASdata[options->GEOindex].IGP2Mask,&InterpolationMode_aux3,IGPnumber_aux3,IGPBandNumber_aux3);

					 
						if (InterpolationMode_aux3==0) {
							InterpolationMode=0;
							IGPlon1=IGPlon_aux3;
							IGPlat_aux1=IGPlat_aux3;
							IGPlon2=IGPlon1+increment;
							IGPlat_aux2=IGPlat_aux1+increment;
							for(i=1;i<=4;i++) {
								IGPBandNumber[i]=IGPBandNumber_aux3[i];
								IGPnumber[i]=IGPnumber_aux3[i];
							}
						}
					}

					if (InterpolationMode_aux3!=0) {

						//SQUARE 4:
						IGPlon_aux3=IGPlon1;
						IGPlat_aux3=IGPlat_aux1-5;

						check=(int)(IGPlon_aux3/10)*10-IGPlon_aux3;
						check=fabs(check);
						//Variable "check" looks if the longitude is a multiple of 10. Instead of comparing with zero, compares with 1E-4 (nearly 0) to avoid problems with decimals
						if ((IPPlat>=-55.)||(check<1E-4)) {
						 
							IGPsearch(IPPlat,IPPlon,IGPlat_aux3,IGPlon_aux3,increment,increment,SBASdata[options->GEOindex].IGPinMask,SBASdata[options->GEOindex].IGP2Mask,&InterpolationMode_aux4,IGPnumber_aux4,IGPBandNumber_aux4);


							if (InterpolationMode_aux4==0) {
								InterpolationMode=0;
								IGPlon1=IGPlon_aux3;
								IGPlat_aux1=IGPlat_aux3;
								IGPlon2=IGPlon1+increment;
								IGPlat_aux2=IGPlat_aux1+increment;
								for(i=1;i<=4;i++) {
									IGPBandNumber[i]=IGPBandNumber_aux4[i];
									IGPnumber[i]=IGPnumber_aux4[i];
								}
							}
						}

						if (InterpolationMode_aux4!=0) {

							//If not 10x10 squares are available, try with 10x10 triangles:
							if (InterpolationMode_aux1>=0) {
								InterpolationMode=InterpolationMode_aux1;
								IGPlon2=IGPlon1+increment;
								IGPlat_aux2=IGPlat_aux1+increment;
								for(i=1;i<=4;i++) {
									IGPBandNumber[i]=IGPBandNumber_aux1[i];
									IGPnumber[i]=IGPnumber_aux1[i];
								}
							} else if (InterpolationMode_aux2>=0) {
								InterpolationMode=InterpolationMode_aux2;
								IGPlon1=IGPlon1-5;
								IGPlon2=IGPlon1+increment;
								IGPlat_aux2=IGPlat_aux1+increment;
								for(i=1;i<=4;i++) {
									IGPBandNumber[i]=IGPBandNumber_aux2[i];
									IGPnumber[i]=IGPnumber_aux2[i];
								}
							} else if (InterpolationMode_aux3>=0) {   
								InterpolationMode=InterpolationMode_aux3;
								IGPlon1=IGPlon1-5;
								IGPlon2=IGPlon1+increment;
								IGPlat_aux1=IGPlat_aux1-5;
								IGPlat_aux2=IGPlat_aux1+increment;
								for(i=1;i<=4;i++) {
									IGPBandNumber[i]=IGPBandNumber_aux3[i];
									IGPnumber[i]=IGPnumber_aux3[i];
								}
							} else if (InterpolationMode_aux4>=0) {
								InterpolationMode=InterpolationMode_aux4;
								IGPlon2=IGPlon1+increment;
								IGPlat_aux1=IGPlat_aux1-5;
								IGPlat_aux2=IGPlat_aux1+increment;
								for(i=1;i<=4;i++) {
									IGPBandNumber[i]=IGPBandNumber_aux4[i];
									IGPnumber[i]=IGPnumber_aux4[i];
								}
							} else {
								//NO 10x10 square or triangle available. Thence, NO INTERPOLATION
								*errorvalue=-40;
								InterpolationMode=-1;
								return 9999;
							}
						}
					}
				}
			}
		}
	}

	if(IGPretrieved==0) {
		IGP1=IGPnumber[1];
		IGP2=IGPnumber[2];
		IGP3=IGPnumber[3];
		IGP4=IGPnumber[4];
		BandNumber1=IGPBandNumber[1];
		BandNumber2=IGPBandNumber[2];
		BandNumber3=IGPBandNumber[3];
		BandNumber4=IGPBandNumber[4];
	}


	if ((BandNumber1<0)||(BandNumber2<0)||(BandNumber3<0)||(BandNumber4<0)) {
		*errorvalue=-39;
		InterpolationMode=-1;
		return 9999;
	}
	if ((BandNumber1>10)||(BandNumber2>10)||(BandNumber3>10)||(BandNumber4>10)) {
		*errorvalue=-39;
		InterpolationMode=-1;
		return 9999;
	}


	if (InterpolationMode==0) {
		if ((IGP1==0)||(IGP2==0)||(IGP3==0)|| (IGP4==0)) {
			*errorvalue=-39;
			InterpolationMode=-1;
			return 9999;
		}
	} else if (InterpolationMode==1) {
		if ((IGP2==0)||(IGP3==0)||(IGP4==0)) {
			*errorvalue=-39;
			InterpolationMode=-1;
			return 9999;
		}
	} else if (InterpolationMode==2) {
		if ((IGP1==0)||(IGP3==0)||(IGP4==0)) {
			*errorvalue=-39;
			InterpolationMode=-1;
			return 9999;
		}
	} else if (InterpolationMode==3) {
		if ((IGP1==0)||(IGP2==0)||(IGP4==0)) {
			*errorvalue=-39;
			InterpolationMode=-1;
			return 9999;
		}
	} else if (InterpolationMode==4) {
		if ((IGP1==0)||(IGP2==0)||(IGP3==0)) {
			*errorvalue=-39;
			InterpolationMode=-1;
			return 9999;
		}
	}

	if ((IGP1>201)||(IGP2>201)||(IGP3>201)|| (IGP4>201)) {
		*errorvalue=-39;
		InterpolationMode=-1;
		return 9999;
	}


	
	//IGPDelays[1:4]= Vertical delays in the four grid points [1-4] from MT 26 (position 0 is not used) (in meters)
	//IGPSigma2[1:4]= Sigma^2 in the four grid points [1-4] after applying formula A-58 in MOPS-C (position 0 is not used) (in meters^2)

	//Check IGP1
	if (IGP1>0) {
		IGPDelays[1]=SBASdata[options->GEOindex].Ionodelay[BandNumber1][IGP1];
		IGPSigma2[1]=SBASdata[options->GEOindex].Ionosigma[BandNumber1][IGP1]; //Ionosigma values are in Meters^2
		if(IGPSigma2[1]==-1) {
			IGPcheck[1]=0;
		} else {
			IGPcheck[1]=1;
		}
	} else {
		IGPcheck[1]=0;
	}
	if(IGPcheck[1]==1) {
		//The difference in time is done with time of transmission of the first bit (this is the time for computing eps_iono)
		difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].lastiono[BandNumber1][IGP1])+1.1;
		if((1-(difftime-(int)difftime))<1E-4) difftime=(int)difftime+1; //This is to account for problems when converting to integer, when a number is 1.99999998
		if(difftime<=((double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][IONOSPHERICDELAYCORRECTIONS])+1.1) && SBASdata[options->GEOindex].lastiono[BandNumber1][IGP1].MJDN!=-1) {
			//In precision approach, if we don't have MT10 we won't enter the SBAS iono function.
			//In non precision approach, or we are using SBAS iono but not any SBAS corrections, if we don't have MT10 we will just set the degradation term to 0
			if(mt10available==1) { 
				eps_iono[1]=SBASdata[options->GEOindex].degradationfactors[CIONOSTEP]*(int)(difftime/SBASdata[options->GEOindex].degradationfactors[IIONO])+SBASdata[options->GEOindex].degradationfactors[CIONORAMP]*difftime;
				if (SBASdata[options->GEOindex].degradationfactors[RSSIONO]==0) {
					IGPSigma2[1]=(sqrt(IGPSigma2[1])+eps_iono[1])*(sqrt(IGPSigma2[1])+eps_iono[1]);
				} else {
					IGPSigma2[1]=IGPSigma2[1]+eps_iono[1]*eps_iono[1];
				}
			}
		} else {
			IGPcheck[1]=0;
		}
	}

	//Check IGP2
	if (IGP2>0) {
		IGPDelays[2]=SBASdata[options->GEOindex].Ionodelay[BandNumber2][IGP2];
		IGPSigma2[2]=SBASdata[options->GEOindex].Ionosigma[BandNumber2][IGP2]; //Ionosigma values are in Meters^2
		if(IGPSigma2[2]==-1) {
			IGPcheck[2]=0;
		} else {
			IGPcheck[2]=1;
		}
	} else {
		IGPcheck[2]=0;
	}
	if(IGPcheck[2]==1) {
		//The difference in time is done with time of transmission of the first bit (this is the time for computing eps_iono)
		difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].lastiono[BandNumber2][IGP2])+1.1;
		if((1-(difftime-(int)difftime))<1E-4) difftime=(int)difftime+1; //This is to account for problems when converting to integer, when a number is 1.99999998
		if(difftime<=((double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][IONOSPHERICDELAYCORRECTIONS])+1.1) && SBASdata[options->GEOindex].lastiono[BandNumber2][IGP2].MJDN!=-1) {
			//In precision approach, if we don't have MT10 we won't enter the SBAS iono function.
			//In non precision approach, or we are using SBAS iono but not any SBAS corrections, if we don't have MT10 we will just set the degradation term to 0
			if(mt10available==1) { 
				eps_iono[2]=SBASdata[options->GEOindex].degradationfactors[CIONOSTEP]*(int)(difftime/SBASdata[options->GEOindex].degradationfactors[IIONO])+SBASdata[options->GEOindex].degradationfactors[CIONORAMP]*difftime;
				if (SBASdata[options->GEOindex].degradationfactors[RSSIONO]==0) {
					IGPSigma2[2]=(sqrt(IGPSigma2[2])+eps_iono[2])*(sqrt(IGPSigma2[2])+eps_iono[2]);
				} else {
					IGPSigma2[2]=IGPSigma2[2]+eps_iono[2]*eps_iono[2];
				}
			}
		} else {
			IGPcheck[2]=0;
		}
	}



	//Check IGP3
	if (IGP3>0) {
		IGPDelays[3]=SBASdata[options->GEOindex].Ionodelay[BandNumber3][IGP3];
		IGPSigma2[3]=SBASdata[options->GEOindex].Ionosigma[BandNumber3][IGP3]; //Ionosigma values are in Meters^2
		IGPcheck[3]=1;
		if(IGPSigma2[3]==-1) {
			IGPcheck[3]=0;
		} else {
			IGPcheck[3]=1;
		}
	} else {
		IGPcheck[3]=0;
	}
	if(IGPcheck[3]==1) {
		//The difference in time is done with time of transmission of the first bit (this is the time for computing eps_iono)
		difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].lastiono[BandNumber3][IGP3])+1.1;
		if((1-(difftime-(int)difftime))<1E-4) difftime=(int)difftime+1; //This is to account for problems when converting to integer, when a number is 1.99999998
		if(difftime<=((double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][IONOSPHERICDELAYCORRECTIONS])+1.1) && SBASdata[options->GEOindex].lastiono[BandNumber3][IGP3].MJDN!=-1) {
			//In precision approach, if we don't have MT10 we won't enter the SBAS iono function.
			//In non precision approach, or we are using SBAS iono but not any SBAS corrections, if we don't have MT10 we will just set the degradation term to 0
			if(mt10available==1) { 
				eps_iono[3]=SBASdata[options->GEOindex].degradationfactors[CIONOSTEP]*(int)(difftime/SBASdata[options->GEOindex].degradationfactors[IIONO])+SBASdata[options->GEOindex].degradationfactors[CIONORAMP]*difftime;
				if (SBASdata[options->GEOindex].degradationfactors[RSSIONO]==0) {
					IGPSigma2[3]=(sqrt(IGPSigma2[3])+eps_iono[3])*(sqrt(IGPSigma2[3])+eps_iono[3]);
				} else {
					IGPSigma2[3]=IGPSigma2[3]+eps_iono[3]*eps_iono[3];
				}
			}
		} else {
			IGPcheck[3]=0;
		}
	}



	//Check IGP4
	if (IGP4>0) {
		IGPDelays[4]=SBASdata[options->GEOindex].Ionodelay[BandNumber4][IGP4];
		IGPSigma2[4]=SBASdata[options->GEOindex].Ionosigma[BandNumber4][IGP4]; //Ionosigma values are in Meters^2
		if(IGPSigma2[4]==-1) {
			IGPcheck[4]=0;
		} else {
			IGPcheck[4]=1;
		}
	} else {
		IGPcheck[4]=0;
	}
	if(IGPcheck[4]==1) {
		//The difference in time is done with time of transmission of the first bit (this is the time for computing eps_iono)
		difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].lastiono[BandNumber4][IGP4])+1.1;
		if((1-(difftime-(int)difftime))<1E-4) difftime=(int)difftime+1; //This is to account for problems when converting to integer, when a number is 1.99999998
		if(difftime<=((double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][IONOSPHERICDELAYCORRECTIONS])+1.1) && SBASdata[options->GEOindex].lastiono[BandNumber4][IGP4].MJDN!=-1) {
			//In precision approach, if we don't have MT10 we won't enter the SBAS iono function.
			//In non precision approach, or we are using SBAS iono but not any SBAS corrections, if we don't have MT10 we will just set the degradation term to 0
			if(mt10available==1) { 
				eps_iono[4]=SBASdata[options->GEOindex].degradationfactors[CIONOSTEP]*(int)(difftime/SBASdata[options->GEOindex].degradationfactors[IIONO])+SBASdata[options->GEOindex].degradationfactors[CIONORAMP]*difftime;
				if (SBASdata[options->GEOindex].degradationfactors[RSSIONO]==0) {
					IGPSigma2[4]=(sqrt(IGPSigma2[4])+eps_iono[4])*(sqrt(IGPSigma2[4])+eps_iono[4]);
				} else {
					IGPSigma2[4]=IGPSigma2[4]+eps_iono[4]*eps_iono[4];
				}
			}
		} else {
			IGPcheck[4]=0;
		}
	}

	//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	//INTERPOLING the VIRTUAL IGPs at a latitude 85deg::::::::::::::::: 
	//[This do not applies for |fi|>85deg]. It only applies for the latitude bands:  75<fi<=85 o -75>fi>=85]        
	//Computing the VD and GIVEs at the virtual IGPs at xfi=85deg

	if ((IPPlat>=75.)&&(IPPlat<85.)) {

		//The interpolation is allowed only when none of the IGP is set to don't use
		if ((IGPDelays[1]==-1)||(IGPDelays[2]==-1)) {
			*errorvalue=-43;
			InterpolationMode=-1;
			return 9999;
		}

		//The Linear interpolation between IGPs at 85º can be done only if both IPPs are monitored and not time-out.

		if ((IGPcheck[1]==0)||(IGPcheck[2]==0)) {
			*errorvalue=-42;
			InterpolationMode=-1;
			return 9999;
		}


		/*
		Interpolated Vertical delay at upper-right corner        2 -- 1
		(IGPlat_aux2,IGPlon2)[VM1] and at upper-left corner      3 -- 4
		(IGPlat_aux2,IGPlon1)[VM2] 


		[2] IGPlon_auxleft       [1]    IGPlon_auxright
		(IGPlat_aux2,IGPlon1)    ----   (IGPlat_aux2,IGPlon2)
		[VM2][SI2]                      [VM1][SI1]	
		|                         |
		|                         |
		[3]                      [4]
		(IGPlat_aux1,IGPlon1)    ----   (IGPlat_aux1,IGPlon2)
		*/



		//Vertical delay Interpolation:

		VM1=(IGPDelays[1]-IGPDelays[2])/(IGPlon_auxright-IGPlon_auxleft)*(IGPlon2-IGPlon_auxleft)+IGPDelays[2]; 

		VM2=(IGPDelays[1]-IGPDelays[2])/(IGPlon_auxright-IGPlon_auxleft)*(IGPlon1-IGPlon_auxleft)+IGPDelays[2]; 

		IGPDelays[1]=VM1;
		IGPDelays[2]=VM2;


		//Sigma Interpolation:  

		//NOTE: when interpolating IGPSigma2 with degradation parameters, we interpolate over the sigma ionogrid.

		SI1=IGPSigma2[1]+(IGPSigma2[2]-IGPSigma2[1])*(IGPlon_auxright-IGPlon2)/(IGPlon_auxright-IGPlon_auxleft); 
		SI2=IGPSigma2[2]+(IGPSigma2[1]-IGPSigma2[2])*(IGPlon1-IGPlon_auxleft)/(IGPlon_auxright-IGPlon_auxleft); 

		IGPSigma2[1]=SI1;
		IGPSigma2[2]=SI2;
	}



	if ((IPPlat<-75)&&(IPPlat>=-85)) {

		//The interpolation is only possible when any IGP be set as don't use. 
		if ((IGPDelays[3]==-1)||(IGPDelays[4]==-1)) {
			*errorvalue=-43;
			InterpolationMode=-1;
			return 9999;
		}

		//The Linear interpolation between IGPs at -85º can be done only if both IPPs are monitored and not time-out.   
	 
		if ((IGPcheck[3]==0)||(IGPcheck[4]==0)) {
			*errorvalue=-42;
			InterpolationMode=-1;
			return 9999;
		}
	 
	 
		/*
		//...Interpolated Vertical delay at lower-right corner    2 -- 1
		//(IGPlat_aux1,IGPlon1)[VM3] and at lower-left corner     3 -- 4
		//(IGPlat_aux1,IGPlon2)[VM4] 


		[2]                      [1]      
		(IGPlat_aux2,IGPlon1)  ----   (IGPlat_aux2,IGPlon2)

		|                         |
		|                         |
		[3] IGPlon_auxleft       [4]  IGPlon_auxright
		(IGPlat_aux1,IGPlon1)  ----   (IGPlat_aux1,IGPlon2)
		[VM3][SI3]                    [VM4][SI4]             
		*/

	 

		//Vertical delay Interpolation:    
	 
		VM3=(IGPDelays[4]-IGPDelays[3])/(IGPlon_auxright-IGPlon_auxleft)*(IGPlon1-IGPlon_auxleft)+IGPDelays[3];
		VM4=(IGPDelays[4]-IGPDelays[3])/(IGPlon_auxright-IGPlon_auxleft)*(IGPlon2-IGPlon_auxleft)+IGPDelays[3];
	 
		IGPDelays[3]=VM3;
		IGPDelays[4]=VM4;
	 
	 

		//NOTE: when interpolating IGPSigma2 with degradation parameters, we interpolate over the sigma ionogrid. 
	 
		SI3=(IGPSigma2[4]-IGPSigma2[3])/(IGPlon_auxright-IGPlon_auxleft)*(IGPlon1-IGPlon_auxleft)+IGPSigma2[3];
		SI4=(IGPSigma2[4]-IGPSigma2[3])/(IGPlon_auxright-IGPlon_auxleft)*(IGPlon2-IGPlon_auxleft)+IGPSigma2[3];
	 
		IGPSigma2[3]=SI3;
		IGPSigma2[4]=SI4;
	 
	 
	}                                                                                   

	//Finding the square or triangle for interpolation: (see SBASionoInterpolation code)
	InterpolationMode=0;
	for(i=1;i<=4;i++) {
		//NOTE: IGPcheck[i]==0 ==> NOT available or time-out
		if (IGPcheck[i]==0) { 
			if (InterpolationMode==0) {
				InterpolationMode=i;
			} else {
				InterpolationMode=-1;
				*errorvalue=-42;
			}
		}
		//NOTE: IGPDelays[i]==-1 ==> One of the IGPs is set as don't use
		//When any of the IGPs selected is set as don't use, there is no ionosphere correction
		if (IGPDelays[i]==63.875) { 
			InterpolationMode=-1;
			*errorvalue=-41;
		}
	}
					


	//... Interpolation .......................................

	if ((IPPlat>=85.)||(IPPlat<-85.)) {
		SBASionoInterpolation(IPPlat,IPPlon,IGPlat,IGPlon3,IGPlat,IGPlon3,&InterpolationMode,IGPDelays,IGPSigma2,&VerticalDelay,&Sigma2,IPP_Weight);
	 
	 
		IGPfinal_lon1=IGPlon1;
		IGPfinal_lon2=IGPlon2;
		IGPfinal_lon3=IGPlon3;
		IGPfinal_lon4=IGPlon4;
	 
		IGPfinal_lat1=IGPlat;
		IGPfinal_lat2=IGPlat;
		IGPfinal_lat3=IGPlat;
		IGPfinal_lat4=IGPlat;
	 
		//Vertex from IGP3
		//IGP3_corner_lon=IGPlon3;
		//IGP3_corner_lat=IGPlat;
	 
		//Note: We use always the same formula when interpolating over circles. Nevertheless, the labels of vertex changes.
		//The IGP3 is always, the IGP closest to IPP from west. 
		

	} else { 
		SBASionoInterpolation(IPPlat,IPPlon,IGPlat_aux1,IGPlon1,IGPlat_aux2,IGPlon2,&InterpolationMode,IGPDelays,IGPSigma2,&VerticalDelay,&Sigma2,IPP_Weight);

		IGPfinal_lon1=IGPlon2;
		IGPfinal_lon2=IGPlon1;
		IGPfinal_lon3=IGPlon1;
		IGPfinal_lon4=IGPlon2;

		IGPfinal_lat1=IGPlat_aux2;
		IGPfinal_lat2=IGPlat_aux2;
		IGPfinal_lat3=IGPlat_aux1;
		IGPfinal_lat4=IGPlat_aux1;

		//IGP3 corner:        2   1
		//                   [3]  4
		//Note: in the square or triangle interpolation, the equations has been modified 
		//in order to reffer always the "x" and "y" to the low-left corner (IGP3).

		//IGP3_corner_lon=IGPlon1;
		//IGP3_corner_lat=IGPlat_aux1;
	}     

	if (InterpolationMode==-1) { 
		 
		if(*errorvalue==1) *errorvalue=-39;
		return 9999;
	}

	if(InterpolationMode<-1) {
		//No interpolation due to IPP is outside the triangle
		*errorvalue=-44;
		return 9999;
	}



	//SLANT DELAYS:


	//Fpp -> Obliquity factor (formula A-41 MOPS-C)
	Fpp=1/sqrt(1-pow((SBAS_EARTH_RADIUS*cos(elevation))/(SBAS_EARTH_RADIUS+SBAS_HEIGHT),2));

	SlantDelay=VerticalDelay*Fpp;
	epoch->sat[satIndex].ionoSigma=sqrt(Sigma2*Fpp*Fpp);
	SBAScorr->sigma2iono=Sigma2*Fpp*Fpp; //In meters^2
 
	
	// Change from L1 meters to TECU 

	if(options->printSBASIONO==1) {
		printSBASIONO(epoch,SBASdata,SBAScorr,satIndex,InterpolationMode,IGP1,BandNumber1,IGPfinal_lat1,IGPfinal_lon1,IGP2,BandNumber2,IGPfinal_lat2,IGPfinal_lon2,IGP3,BandNumber3,IGPfinal_lat3,IGPfinal_lon3,IGP4,BandNumber4,IGPfinal_lat4,IGPfinal_lon4,eps_iono,IGPDelays,IGPSigma2,IPP_Weight,Fpp,SlantDelay,epoch->sat[satIndex].ionoSigma,elevation,azimuth,options);
	}

	SlantDelay = SlantDelay / 40.3 * GPSf1 * GPSf1 * pow(10,-16); // in TECUs
	epoch->sat[satIndex].ionoSigma=epoch->sat[satIndex].ionoSigma / 40.3 * GPSf1 * GPSf1 * pow(10,-16); // in TECUs

	return SlantDelay;

}


/*****************************************************************************
 * Name        : SwitchSBASGEOMode
 * Description : If we have less than 4 satellites in an epoch, check if we 
 *               have to switch the GEO.
 *               This function is called by a single thread
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * int  numsatellites              I  N/A  Number of satellites in the current epoch
 * int  numsatdiscardedSBAS        I  N/A  Number of satellites discarded due to SBAS corrections
 * TSBASdata *SBASdata             I  N/A  Struct with SBAS data
 * TOptions  *options              IO N/A  TOptions structure
 * Returned value (int)            I  N/A  Status of the function
 *                                         0 => GEO/Mode not changed
 *                                         1 => GEO changed
 *                                         2 => Mode changed
 *****************************************************************************/
int SwitchSBASGEOMode (TEpoch  *epoch, int  numsatellites, int  numsatdiscardedSBAS, TSBASdata *SBASdata, TOptions  *options) {

	static int		initialized=0;
	static int		initialmode;
	static int		initialPRN;
	static int		initialPRNpos;
	static int		switchedGEO=0;
	static int		prevmode=-1;
	static int		prevGEOPRN=-1;
	static int		prevGEOPRNList[MAX_NUM_SBAS];
	static int		lastprevGEOIndinList;
	static int		switchedmode=0;
	static int		numswitchcurrentepoch=1;
	static int		lastswitchMJDN=-1;
	static double	lastswitchSoD=-1.;
	TTime			tlastswitch;
	
	int				i,j,k;
	int				start;
	int 			initialPRNavail=0;
	int				GEOchanged=0;
	int				foundpreviousPRN;
	double			difftime,difftimelastSwitch;
	double			SatOver60;
	
	
	//No GEO selected
	if(options->GEOindex<0) {
		//Set possible switch to 0 to avoid infinite loops
		epoch->SwitchPossible=0;
		//Print modelling data
		options->printInBuffer=2;
		printBuffers(epoch,options);
		return 0;
	}
	
	if(initialized==0) {
		initialized=1;
		initialmode=options->precisionapproach;
		initialPRN=SBASdata[options->GEOindex].PRN;
		initialPRNpos=options->GEOindex;
		for(i=0;i<MAX_NUM_SBAS;i++) {
			prevGEOPRNList[i]=-1;
		}
		lastprevGEOIndinList=-1;
	}

	//messagestrSwitchGEO and sagestrSwitchMode are global variable which will be used only for saving a GEO or mode fallback printINFO string.
	//This is to make the print after showing the OUTPUT message, so the user is not confused (if the print is done in
	//this function, it is done before the OUTPUT message, which looks like is as gLAB had switched mode or GEO before
	//computing the solution)
	messagestrSwitchGEO[0]='\0';
	messagestrSwitchMode[0]='\0';

	//Compute proportion of satellites that have a sigma of 60 metres
	SatOver60=(double)(SBASdata[options->GEOindex].numSat60)/((double)(numsatellites));
	//Clear counter of satellites that have a sigma of 60 metres
	SBASdata[options->GEOindex].numSat60=0;

	if(numsatellites>=4 && epoch->TryGEOChange==0 && SatOver60<SIGMA60PROPORTIONTHRESHOLD && options->workMode != wmSBASPLOTS) {
		//4 or more satellites available and we are under DOP threshold. We can compute a solution

		//Clear counter with number of satellites with sigma greater than 60
		SBASdata[options->GEOindex].numSat60=0;

		//We need to check if we had a change of mode or GEO, because we need to fall back to previous mode or GEO
		if(switchedmode==1 || switchedGEO==1) {
			//This is some common code for both cases
			//Check time from previous change
			tlastswitch.MJDN=lastswitchMJDN;
			tlastswitch.SoD=lastswitchSoD;
			difftimelastSwitch=tdiff(&epoch->t,&tlastswitch);
			if(difftimelastSwitch<(double)options->minimumswitchtime) {
				//Not enough time between changes. In case minimumswitchtime is 0, wait for next epoch to make a switch again
				return 0;
			}

			//We want to check if the original GEO is available
			if(options->GEOfallback==1) {
				initialPRNavail=1;
				//Check that the GEO is not under alarm or that it does not have 4 or more missing messages
				if(SBASdata[0].alarmGEOPRN[initialPRN]==initialPRN  || (SBASdata[0].numAlarmGEO>0 && initialPRNpos==0)) {
					//Satellite is under alarm
					initialPRNavail=0;
				} else if (SBASdata[0].missed4msg[initialPRN]>=4) {
					//Satellite has 4 or more missing messages
					initialPRNavail=0;
				}

				//Check that initial adquisition time has finished
				i=SBASdata[0].GEOPRN2pos[initialPRN];
				difftime=tdiff(&epoch->t,&SBASdata[i].firstmessage);
				if(difftime<(double)options->adquisitiontime || SBASdata[i].firstmessage.MJDN==-1) {
					//We are still in adquisition time. No GEO or mode change
					initialPRNavail=0;
				}
			}
		}

		if(switchedmode==1) {
			//A mode switch occurred
			//If fallback to initial GEO is active, we will try to fallback to it. Otherwise, we will leave the current GEO
			if(options->GEOfallback==1 && initialPRNavail==1 && options->GEOindex!=initialPRNpos) {
				if(initialPRNpos==0) sprintf(messagestrSwitchGEO,"Switched from GEO %3d to mixed GEO at epoch %17s",SBASdata[options->GEOindex].PRN,t2doystr(&epoch->t));
				else if (options->GEOindex==0) sprintf(messagestrSwitchGEO,"Switched from mixed GEO to GEO %3d at epoch %17s",initialPRN,t2doystr(&epoch->t));
				else sprintf(messagestrSwitchGEO,"Switched from GEO %3d to GEO %3d at epoch %17s",SBASdata[options->GEOindex].PRN,initialPRN,t2doystr(&epoch->t));
				options->GEOindex=initialPRNpos;
				epoch->currentGEOPRN=SBASdata[options->GEOindex].PRN;
			}
			options->precisionapproach=initialmode;
			sprintf(messagestrSwitchMode,"Switched from NPA to PA mode at epoch %17s",t2doystr(&epoch->t));

		} else if(switchedGEO==1) {
			//A GEO switch ocurred
			//If fallback to initial GEO is active, we will try to fallback to it. Otherwise, fallback to previous GEO
			if(options->GEOfallback==1 && initialPRNavail==1) {
				GEOchanged=1;
				if(initialPRNpos==0) sprintf(messagestrSwitchGEO,"Switched from GEO %3d to mixed GEO at epoch %17s",SBASdata[options->GEOindex].PRN,t2doystr(&epoch->t));
				else if (options->GEOindex==0) sprintf(messagestrSwitchGEO,"Switched from mixed GEO to GEO %3d at epoch %17s",initialPRN,t2doystr(&epoch->t));
				else sprintf(messagestrSwitchGEO,"Switched from GEO %3d to GEO %3d at epoch %17s",SBASdata[options->GEOindex].PRN,initialPRN,t2doystr(&epoch->t));
				options->GEOindex=initialPRNpos;
				epoch->currentGEOPRN=SBASdata[options->GEOindex].PRN;
			} else {
				if(options->MaintainGEO==0) {
					//We go to previous GEO because the option to maintain current GEO is disabled
					//Check that the previous GEO has not received an alarm  or that it does not have 4 or more missing messages
					if(SBASdata[0].alarmGEOPRN[prevGEOPRN]==prevGEOPRN || (SBASdata[0].numAlarmGEO>0 && SBASdata[0].GEOPRN2pos[prevGEOPRN]==0)) {
						//Satellite is under alarm
						GEOchanged=0;
					} else if (SBASdata[0].missed4msg[prevGEOPRN]>=4) {
						//Satellite has 4 or more missing messages
						GEOchanged=0;
					} else {
						//Check that the previous GEO is not in adquisition time
						i=SBASdata[0].GEOPRN2pos[prevGEOPRN];
						difftime=tdiff(&epoch->t,&SBASdata[i].firstmessage);
						if(difftime<(double)options->adquisitiontime || SBASdata[i].firstmessage.MJDN==-1 ) {
							//We are still in adquisition time. No GEO or mode change
							GEOchanged=0;
						} else {
							GEOchanged=1;
							if(i==0) sprintf(messagestrSwitchGEO,"Switched from GEO %3d to mixed GEO at epoch %17s",SBASdata[options->GEOindex].PRN,t2doystr(&epoch->t));
							else if (options->GEOindex==0) sprintf(messagestrSwitchGEO,"Switched from mixed GEO to GEO %3d at epoch %17s",prevGEOPRN,t2doystr(&epoch->t));
							else sprintf(messagestrSwitchGEO,"Switched from GEO %3d to GEO %3d at epoch %17s",SBASdata[options->GEOindex].PRN,prevGEOPRN,t2doystr(&epoch->t));
							options->GEOindex=i;
							epoch->currentGEOPRN=SBASdata[options->GEOindex].PRN;
						}
					}
				}
			}
		}

		if(switchedmode==1 || (switchedGEO==1 && GEOchanged==1) ) {
			if(options->GEOfallback==1 && options->GEOindex!=initialPRNpos) {
				//We still have to fallback to original GEO. Save last change
				lastswitchMJDN=epoch->t.MJDN;
				lastswitchSoD=epoch->t.SoD;
				switchedmode=switchedGEO=-1;
			} else {
				//Clear change conditions. As this is a fallback, we will be like in the beginning
				if (difftimelastSwitch>0.) {
					prevGEOPRN=prevmode=-1;
					lastswitchMJDN=lastswitchSoD=-1;
					switchedmode=switchedGEO=-1;
					//Reset previous GEO list
					for(i=0;i<=lastprevGEOIndinList;i++) {
						prevGEOPRNList[i]=-1;
					}
					lastprevGEOIndinList=-1;
				}
			}
		} else if ( switchedGEO==1 && options->MaintainGEO==1 ) {
			//We had changed GEO, but we will maintain it while we can. Clear switch conditions
			if (difftimelastSwitch>0.) {
				prevGEOPRN=prevmode=-1; 
				lastswitchMJDN=lastswitchSoD=-1;
				switchedmode=switchedGEO=-1;
				//Reset previous GEO list
				for(i=0;i<=lastprevGEOIndinList;i++) {
					prevGEOPRNList[i]=-1;
				}
				lastprevGEOIndinList=-1;
			}
		} else if (options->GEOfallback==1 && options->GEOindex!=initialPRNpos) {
			//We have done a fallback, but we still need to fallback to the original GEO. Try to do it
			//Check time from previous change
			tlastswitch.MJDN=lastswitchMJDN;
			tlastswitch.SoD=lastswitchSoD;
			difftime=tdiff(&epoch->t,&tlastswitch);
			if(difftime<(double)options->minimumswitchtime) {
				//Not enough time between changes
				return 0;
			}
			//We want to check if the original GEO is available
			if(SBASdata[0].alarmGEOPRN[initialPRN]==initialPRN || (SBASdata[0].numAlarmGEO>0 && initialPRNpos==0)) {
				//Satellite is under alarm
				return 0;
			}
			//Check that initial adquisition time has finished
			i=SBASdata[0].GEOPRN2pos[initialPRN];
			difftime=tdiff(&epoch->t,&SBASdata[i].firstmessage);
			if(difftime<(double)options->adquisitiontime || SBASdata[i].firstmessage.MJDN==-1) {
				//We are still in adquisition time. No GEO or mode change
				return 0;
			} else if (SBASdata[0].missed4msg[initialPRN]>=4) {
				//Satellite has 4 or more missing messages
				return 0;
			}
			//Clear change conditions. As this is a fallback, we will be like in the beginning
			prevGEOPRN=prevmode=-1;
			lastswitchMJDN=lastswitchSoD=-1;
			switchedmode=switchedGEO=-1;
			//Reset previous GEO list
			for(i=0;i<=lastprevGEOIndinList;i++) {
				prevGEOPRNList[i]=-1;
			}
			lastprevGEOIndinList=-1;

			if(initialPRNpos==0) sprintf(messagestrSwitchGEO,"Switched from GEO %3d to mixed GEO at epoch %17s",SBASdata[options->GEOindex].PRN,t2doystr(&epoch->t));
			else if (options->GEOindex==0) sprintf(messagestrSwitchGEO,"Switched from mixed GEO to GEO %3d at epoch %17s",initialPRN,t2doystr(&epoch->t));
			else sprintf(messagestrSwitchGEO,"Switched from GEO %3d to GEO %3d at epoch %17s",SBASdata[options->GEOindex].PRN,initialPRN,t2doystr(&epoch->t));

			//Switch to original GEO
			options->GEOindex=initialPRNpos;
			epoch->currentGEOPRN=SBASdata[options->GEOindex].PRN;
		}

		//We will return a value of 0 even though we may have made a fallback in mode or GEO. 
		//This is to avoid doing a new loop of model computations when it is not necessary

		return 0;
	} else {
		//Less than 4 satellites or over GDOP threshold or half of satellites have a sigma of 60 metres. 
		//We need to check if we can change the GEO or mode

		//Check that the discarded satellites due to SBAS measurements plus the available satellites make at least 4 satellites.
		if(numsatdiscardedSBAS+numsatellites<4) {
			//It is useless to change GEO or mode because we would continue having less than 4 satellites
			//Set possible switch to 0 to avoid infinite loops
			epoch->SwitchPossible=0;
			return 0;
		}

		//First check that if in current epoch we have not done more than MAXSWITCHPEREPOCH switches
		//We have to put this condition for the case when the switch time is set to 0, because in this case if there were no
		//limit of number of switches per epoch, we could end in an infinite loop of switches
		//In SBAS plots mode, we permit much more GEO switches change per iteration, as it can create a map for the whole world
		if(epoch->t.MJDN==lastswitchMJDN && epoch->t.SoD==lastswitchSoD) {
			numswitchcurrentepoch++;
			if(epoch->ResetNumSwitch==1) {
				numswitchcurrentepoch=0;
				epoch->ResetNumSwitch=0;
				//Reset previous GEO list
				for(i=0;i<=lastprevGEOIndinList;i++) {
					prevGEOPRNList[i]=-1;
				}
				lastprevGEOIndinList=-1;
			} else if (options->workMode == wmSBASPLOTS) { //Enter here if we are computing SBAS Availability plots
				if (numswitchcurrentepoch>MAXSWITCHPERITERATIONSBASPLOT) {
					//We have surpassed the limit for SBAS Availability plot.
					numswitchcurrentepoch=1;
					//Set possible switch to 0 to avoid infinite loops
					epoch->SwitchPossible=0;
					return 0;
				}
			} else if(numswitchcurrentepoch>MAXSWITCHPEREPOCH) {
				//We have surpassed the limit.
				numswitchcurrentepoch=1;
				//Set possible switch to 0 to avoid infinite loops
				epoch->SwitchPossible=0;
				return 0;
			}
		} else {
			numswitchcurrentepoch=1;
			epoch->ResetNumSwitch=0;
			//Reset previous GEO list
			for(i=0;i<=lastprevGEOIndinList;i++) {
				prevGEOPRNList[i]=-1;
			}
			lastprevGEOIndinList=-1;
		}

		//Check if we have received an alarm for current GEO or we are using Mixed GEO and an alarm was received 
		//or we have four or more invalid or missing messages 
		if(SBASdata[0].alarmGEOPRN[SBASdata[options->GEOindex].PRN]==SBASdata[options->GEOindex].PRN || (options->GEOindex==0 && SBASdata[0].numAlarmGEO>0) 
				|| (SBASdata[0].missed4msg[SBASdata[options->GEOindex].PRN]>=4) || (SBASdata[0].failedmessages[SBASdata[options->GEOindex].PRN]>=4) ) {
			//Received an alarm
			//Try to change GEO
			if(options->switchGEO<=0) {
				//GEO switching disabled. Nothing to be done
				//Set possible switch to 0 to avoid infinite loops
				epoch->SwitchPossible=0;
				return 0;
			} else {
				//With an alarm condition, we cannot switch to the mixed data, because it will be also have been cleared
				//Look for other GEO without alarm

				j=0;
				while(j<2) {
					for(i=1;i<=SBASdata[0].numSBASsatellites;i++) {
						if(i==options->GEOindex) continue; //Skip current satellite
						if(SBASdata[0].alarmGEOPRN[SBASdata[i].PRN]==SBASdata[i].PRN) continue; //Skip other satellite with alarm
						//Check GEO has not 4 or more missing messages
						if (SBASdata[0].missed4msg[SBASdata[i].PRN]>=4) continue;
						//Check previous GEOs used
						if (lastprevGEOIndinList!=-1) {
							//If there are many different GEOs, skip all the previous one used before in the same epoch
							foundpreviousPRN=0;
							for(k=0;k<=lastprevGEOIndinList;k++) {
								if(prevGEOPRNList[k]==SBASdata[i].PRN) {
									foundpreviousPRN=1;
									break;
								}
							}
							if (foundpreviousPRN==1) continue;
						}
						//Check that the GEO is not in acquisition time. We will only do it on the first loop, so if we do not
						//have any other GEO available, we will use anyone even if it is in acquisition time
						if(j==0) {
							difftime=tdiff(&epoch->t,&SBASdata[i].firstmessage);
							if(difftime<(double)options->adquisitiontime || SBASdata[i].firstmessage.MJDN==-1) continue;
						}

						//Print modelling data
						options->printInBuffer=3;
						printBuffers(epoch,options);
						if (options->workMode != wmSBASPLOTS) {
							//Do not print GEO switch when doing SBAS availability plots
							if (options->GEOindex==0) sprintf(messagestr,"Switched from mixed GEO to GEO %3d at epoch %17s",SBASdata[i].PRN,t2doystr(&epoch->t));
							else sprintf(messagestr,"Switched from GEO %3d to GEO %3d at epoch %17s",SBASdata[options->GEOindex].PRN,SBASdata[i].PRN,t2doystr(&epoch->t));
							printInfo(messagestr,options);
						}
						//Save values
						prevGEOPRN=SBASdata[options->GEOindex].PRN;
						lastprevGEOIndinList++;
						prevGEOPRNList[lastprevGEOIndinList]=SBASdata[options->GEOindex].PRN;
						switchedGEO=1;
						options->GEOindex=i;
						epoch->currentGEOPRN=SBASdata[options->GEOindex].PRN;
						lastswitchMJDN=epoch->t.MJDN;
						lastswitchSoD=epoch->t.SoD;
						return 1;
					}
					j++;
				}
				//If we are still here, means that there are no GEO available without alarm. Do not change GEO
				//Set possible switch to 0 to avoid infinite loops
				epoch->SwitchPossible=0;
				return 0;
			}
		}

		//Check that the lack of data is not due because we still didn't have enough time to receive messages
		difftime=tdiff(&epoch->t,&SBASdata[options->GEOindex].firstmessage);
		if(difftime<(double)options->adquisitiontime || SBASdata[options->GEOindex].firstmessage.MJDN==-1) {
			//We are still in acquisition time. No GEO or mode change
			//Set possible switch to 0 to avoid infinite loops
			epoch->SwitchPossible=0;
			return 0;
		}

		//Check time from previous change
		if(lastswitchMJDN!=-1 && options->workMode != wmSBASPLOTS) {
			tlastswitch.MJDN=lastswitchMJDN;
			tlastswitch.SoD=lastswitchSoD;
			difftime=tdiff(&epoch->t,&tlastswitch);
			if(difftime<(double)options->minimumswitchtime) {
				//Not enough time between changes
				//Set possible switch to 0 to avoid infinite loops
				epoch->SwitchPossible=0;
				return 0;
			}
		}

		if(options->switchGEO<=0) {
			//Switching GEO is disabled
			//Check if we can switch mode
			if(options->switchmode<=0 || options->precisionapproach==NPAMODE) {
				//Switching mode forbidden or we are already at non-precision mode
				//Set possible switch to 0 to avoid infinite loops
				epoch->SwitchPossible=0;
				return 0;
			} else {
				//Save previous state
				prevmode=options->precisionapproach;
				lastswitchMJDN=epoch->t.MJDN;
				lastswitchSoD=epoch->t.SoD;
				//Print modelling data
				options->printInBuffer=3;
				printBuffers(epoch,options);
				sprintf(messagestr,"Switched from PA to NPA mode at epoch %17s",t2doystr(&epoch->t));
				printInfo(messagestr,options);
				//Switch to non precision approach mode
				options->precisionapproach=NPAMODE;
				switchedmode=1;
				return 2;
			}
		} else if (options->switchmode<=0) {
			//Switching mode is disabled
			//Check if we can switch GEO
			if(options->switchGEO<=0) {
				//Switching GEO disabled
				//Set possible switch to 0 to avoid infinite loops
				epoch->SwitchPossible=0;
				return 0;
			} else if (options->GEOindex==0) {
				//If we are using mixed data, changing to a single GEO will be useless, as the mixed one will always have the more recent messages from all GEO
				//Set possible switch to 0 to avoid infinite loops
				epoch->SwitchPossible=0;
				return 0;
			}

			//Look for another GEO
			//Check first if we can use mixed data
			if(options->precisionapproach==PAMODE || options->mixedGEOdata<=0) start=1;
			else start=0;
			for(i=start;i<=SBASdata[0].numSBASsatellites;i++) {
				if(i==options->GEOindex) continue; //Skip current satellite
				//Check GEO has not received an alarm
				if(SBASdata[0].alarmGEOPRN[SBASdata[i].PRN]==SBASdata[i].PRN) continue;
				//Check GEO has not 4 or more missing messages
				if (SBASdata[0].missed4msg[SBASdata[i].PRN]>=4) continue;
				//Check that the GEO is not in adquisition time 
				difftime=tdiff(&epoch->t,&SBASdata[i].firstmessage);
				if(difftime<(double)options->adquisitiontime || SBASdata[i].firstmessage.MJDN==-1) continue;
				//Check previous GEOs used
				if (lastprevGEOIndinList!=-1) {
					//If there are many different GEOs, skip all the previous one used before in the same epoch
					foundpreviousPRN=0;
					for(j=0;j<=lastprevGEOIndinList;j++) {
						if(prevGEOPRNList[j]==SBASdata[i].PRN) {
							foundpreviousPRN=1;
							break;
						}
					}
					if (foundpreviousPRN==1) continue;
				}
				//Print modelling data
				if (options->selectBestGEO==0) {
					options->printInBuffer=3;
					printBuffers(epoch,options);
				}
				if (options->workMode != wmSBASPLOTS) {
					//Do not print GEO switch when doing SBAS availability plots
					if(i==0) sprintf(messagestr,"Switched from GEO %3d to mixed GEO at epoch %17s",SBASdata[options->GEOindex].PRN,t2doystr(&epoch->t));
					else if (options->GEOindex==0) sprintf(messagestr,"Switched from mixed GEO to GEO %3d at epoch %17s",SBASdata[i].PRN,t2doystr(&epoch->t));
					else sprintf(messagestr,"Switched from GEO %3d to GEO %3d at epoch %17s",SBASdata[options->GEOindex].PRN,SBASdata[i].PRN,t2doystr(&epoch->t));
					printInfo(messagestr,options);
				}
				//Save values
				prevGEOPRN=SBASdata[options->GEOindex].PRN;
				switchedGEO=1;
				lastprevGEOIndinList++;
				prevGEOPRNList[lastprevGEOIndinList]=SBASdata[options->GEOindex].PRN;
				options->GEOindex=i;
				epoch->currentGEOPRN=SBASdata[options->GEOindex].PRN;
				lastswitchMJDN=epoch->t.MJDN;
				lastswitchSoD=epoch->t.SoD;
				return 1;
			}
			//If we are still here, means that there are no other GEO available. Do not change GEO
			//Set possible switch to 0 to avoid infinite loops
			epoch->SwitchPossible=0;
			return 0;
		} else {
			//GEO and mode switching enabled
			//Try first to switch GEO
			if (options->GEOindex>0) {
				//We are not using mixed data, as changing to a single GEO will be useless, as the mixed one will always have the more recent messages from all GEO
				//Check first if we can use mixed data
				if(options->precisionapproach==PAMODE || options->mixedGEOdata<=0) start=1;
				else start=0;
				for(i=start;i<=SBASdata[0].numSBASsatellites;i++) {
					if(i==options->GEOindex) continue; //Skip current satellite
					//Check that the GEO is not in adquisition time 
					difftime=tdiff(&epoch->t,&SBASdata[i].firstmessage);
					if(difftime<(double)options->adquisitiontime || SBASdata[i].firstmessage.MJDN==-1) continue;
					//Check GEO has not received an alarm
					if(SBASdata[0].alarmGEOPRN[SBASdata[i].PRN]==SBASdata[i].PRN) continue;
					//Check GEO has not 4 or more missing messages
					if (SBASdata[0].missed4msg[SBASdata[i].PRN]>=4) continue;
					//Check previous GEOs used
					if (lastprevGEOIndinList!=-1) {
						//If there are many different GEOs, skip all the previous one used before in the same epoch
						foundpreviousPRN=0;
						for(j=0;j<=lastprevGEOIndinList;j++) {
							if(prevGEOPRNList[j]==SBASdata[i].PRN) {
								foundpreviousPRN=1;
								break;
							}
						}
						if (foundpreviousPRN==1) continue;
					}
					//Print modelling data
					if (options->selectBestGEO==0) {
						options->printInBuffer=3;
						printBuffers(epoch,options);
					}
					if (options->workMode != wmSBASPLOTS) {
						//Do not print GEO switch when doing SBAS availability plots
						if(i==0) sprintf(messagestr,"Switched from GEO %3d to mixed GEO at epoch %17s",SBASdata[options->GEOindex].PRN,t2doystr(&epoch->t));
						else if (options->GEOindex==0) sprintf(messagestr,"Switched from mixed GEO to GEO %3d at epoch %17s",SBASdata[i].PRN,t2doystr(&epoch->t));
						else sprintf(messagestr,"Switched from GEO %3d to GEO %3d at epoch %17s",SBASdata[options->GEOindex].PRN,SBASdata[i].PRN,t2doystr(&epoch->t));
						printInfo(messagestr,options);
					}
					//Save values
					prevGEOPRN=SBASdata[options->GEOindex].PRN;
					lastprevGEOIndinList++;
					prevGEOPRNList[lastprevGEOIndinList]=SBASdata[options->GEOindex].PRN;
					options->GEOindex=i;
					epoch->currentGEOPRN=SBASdata[options->GEOindex].PRN;
					switchedGEO=1;
					lastswitchMJDN=epoch->t.MJDN;
					lastswitchSoD=epoch->t.SoD;
					return 1;
				}
			}

			//If option to select best GEO is enabled, if there are already solutions in PA, don't try to switch to NPA
			if ( options->selectBestGEO==1 && epoch->Buffer_NumDataStoredPA>0) {
				//Disable switching
				epoch->SwitchPossible=0;
				return 0;
			}

			//If we are still here, means that there are no other GEO available or we were using mixed data. Try to change mode
			if(options->precisionapproach==PAMODE) {
				//We are in precision approach, so we can change to non-precision approach
				//Print modelling data
				options->printInBuffer=3;
				printBuffers(epoch,options);
				//Save previous state
				prevmode=options->precisionapproach;
				lastswitchMJDN=epoch->t.MJDN;
				lastswitchSoD=epoch->t.SoD;
				sprintf(messagestr,"Switched from PA to NPA mode at epoch %17s",t2doystr(&epoch->t));
				printInfo(messagestr,options);
				//Switch to non precision approach mode
				options->precisionapproach=NPAMODE;
				switchedmode=1;
				return 2;
			} else {
				//We are already in non-precision approach. No mode change
				//Set possible switch to 0 to avoid infinite loops
				epoch->SwitchPossible=0;
				return 0;
			}
		}
	}
}

/*****************************************************************************
 * Name        : prepareDGNSScorrections
 * Description : Prepare the DGNSS corrections
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  O  N/A  TEpoch structure
 * TEpoch  *epochDGNSS             O  N/A  TEpoch structure
 * TGNSSproducts  *products        I  N/A  Orbit and clock GNSS products to obtain the model
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void prepareDGNSScorrections (TEpoch *epoch, TEpoch *epochDGNSS, TGNSSproducts *products, TOptions *options) {
	int		ii, i;
	// Reference Station Health Status Indicator: Table 4-2
	// health2float[7] = -2.0 indicates that the reference station is not working properly
	// health2float[6] = -1.0 indicates that the transmission is not monitored
	const double	health2float[8] = { 1.0, 0.75, 0.5, 0.3, 0.2, 0.1, -1.0, -2.0 };
	// User Differential Range Error (metres): Table 4-6
	const double	UDRElimit2float[8] = { 1.0, 4.0, 8.0, 10.0 };
	

	// The sigmaURA3 controls the satellites with monitored PseudoRange Correction (PRC), i.e. sigmaURA3 == 0 means not monitored
	// Note: At least 4 satellites are required in the Reference Station to calculate PRCs
	if ( epochDGNSS->numSatellites >= 4 ) {
		for ( ii = 0; ii < epochDGNSS->numSatellites; ii++ ) {
			// Index of the satellite in the dictionary
			i = epochDGNSS->satCSIndex[epochDGNSS->sat[ii].GNSS][epochDGNSS->sat[ii].PRN];
			if ( epochDGNSS->dgnss.msg[i] == 1 || epochDGNSS->dgnss.msg[i] == 2 ) {
				epochDGNSS->dgnss.sigmaURA3[i] = health2float[epochDGNSS->dgnss.health[i]] * UDRElimit2float[epochDGNSS->dgnss.UDRE[i]];
			}
		}
	} else {
		for ( i = 0; i < MAX_SATELLITES_VIEWED; i++ ) epochDGNSS->dgnss.sigmaURA3[i] = 0.0;
	}
}

/*****************************************************************************
 * Name        : computeDGNSScorrections
 * Description : Compute the DGNSS corrections
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  O  N/A  TEpoch structure
 * TEpoch  *epochDGNSS             O  N/A  TEpoch structure
 * TGNSSproducts  *products        I  N/A  Orbit and clock GNSS products to obtain the model
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void computeDGNSScorrections (TEpoch *epoch, TEpoch *epochDGNSS, TGNSSproducts *products, TOptions *options) {
	int			ii, i, j, res;
	int 		nPRC;
	double		TGD, dtClock, rel, flightTime;
	double		C1, C1s, smoothWith;
	double		sigmaMultipath, sigmaAir;
	double		elevation, lambda, distance;
	double		ARPProjection=0;
	//double		azimuth;
	double		velocity[3], relativeLoS[3];
	TTime		t;
	TBRDCblock	*block;
	TSBAScorr	SBAScorr;


	// IMPORTANT ***************************************************************
	// We assume that the S/A is disabled. Under these conditions, there is no need for Range Rate Corrections in DGNSS. 
	// See the paper: 
	//    Park, Byungwoon, Kim, Jeonghan, Jun, Sanghoon, Kee, Changdon, Kalafus, Rudolph, "The Need for Range Rate
	//    Corrections in DGPS Correction Messages," Proceedings of the 17th International Technical Meeting of the Satellite
	//    Division of The Institute of Navigation (ION GNSS 2004), Long Beach, CA, September 2004, pp. 1266-1276.
	//
	// In case of processing data files with S/A, then the PRCs max age must be set to 1 second.
	// *************************************************************************

	// Initialise SBAS corrections and DGNSS epoch
	initSBAScorrections(&SBAScorr);
	modelEpoch(epochDGNSS,options);
	if (options->receiverPositionSource >= rpRTCMRINEXROVER && options->receiverPositionSource != rpRTCMUserbaseline) {
		XYZ2NEU(epoch->receiver.aproxPositionRover,epoch->receiver.aproxPositionNEURover);
		getGroundStationOrientation(epoch->receiver.aproxPositionNEURover, epoch->receiver.orientationRover);			
	}

	

	// Reset receiver clock parameters
	epochDGNSS->dgnss.Nref = 0;
	epochDGNSS->dgnss.CLKref = 0.0;


	// The sigmaURA3 controls the satellites with monitored PseudoRange Correction (PRC), i.e. sigmaURA3 == 0 means not monitored
	// Note: At least 4 satellites are required in the Reference Station to calculate PRCs

	if ( epochDGNSS->numSatellites >= 4 ) {
		for ( i=0;i<MAX_SATELLITES_VIEWED;i++ ) {
			memcpy(&epochDGNSS->dgnss.tPRCp[i],&epochDGNSS->dgnss.tPRC[i],sizeof(TTime));
			epochDGNSS->dgnss.PRCp[i] = epochDGNSS->dgnss.PRC[i];
			epochDGNSS->dgnss.sigmaURA3p[i] = epochDGNSS->dgnss.sigmaURA3[i];
			// Only the PRCs of satellites in view in the last processed epoch from the Reference Station will be used
			epochDGNSS->dgnss.sigmaURA3[i] = 0.0;
		}
	} else return;

	for ( ii = 0; ii < epochDGNSS->numSatellites; ii++ ) {
		// Index of the satellite in the dictionary
		i = epochDGNSS->satCSIndex[epochDGNSS->sat[ii].GNSS][epochDGNSS->sat[ii].PRN];

		// Remove previous excluded satellites
		if ( epochDGNSS->cycleslip.use4smooth[i] == 0 ) continue;

		// Exclude "not converged" differential corrections
		if ( options->excludeSmoothingConvergenceRef && epochDGNSS->cycleslip.arcLength[i] < options->smoothEpochs ) continue;

		// Get block of orbits 
		block = selectBRDCblock(products->BRDC,&epochDGNSS->t,epochDGNSS->sat[ii].GNSS,epochDGNSS->sat[ii].PRN,-1,options);
		if ( block == NULL ) continue;

		// Get and store C1
		C1 = getMeasurementValue(epochDGNSS,epochDGNSS->sat[ii].GNSS,epochDGNSS->sat[ii].PRN,C1P);
		if ( C1 == -1 ) continue;
		else epochDGNSS->dgnss.C1[i] = C1;

		// Get the smoothed C1
		res = getMeasModelValue(epochDGNSS,epochDGNSS->sat[ii].GNSS,epochDGNSS->sat[ii].PRN,options->smoothMeas[0],&smoothWith,NULL);
		if ( res == 0 ) {
			C1s = C1;
			epochDGNSS->dgnss.C1s[i] = C1;
		} else {
			C1s = epochDGNSS->cycleslip.smoothedMeas[i][0] + smoothWith;
			epochDGNSS->dgnss.C1s[i] = C1s;
		}

		// Get geometric range for reference station
		res = fillTransmissionTimeSat(epochDGNSS,products,ii,&SBAScorr,options);
		if ( res == 0 ) continue;
		if ( options->timeTrans ) {
			memcpy(&t,&epochDGNSS->sat[ii].transTime,sizeof(TTime));
		} else {
			memcpy(&t,&epochDGNSS->t,sizeof(TTime));
		}

		// Get block of orbits again. Just for symmetry with Rover (user)
		block = selectBRDCblock(products->BRDC,&t,epochDGNSS->sat[ii].GNSS,epochDGNSS->sat[ii].PRN,-1,options);
		if ( block == NULL ) continue;

		// Compute the satellite position, flight time and satellite velocity
		getPositionBRDC(products->BRDC,block,&t,epochDGNSS->sat[ii].GNSS,epochDGNSS->sat[ii].position);
		flightTime =
		sqrt((epochDGNSS->sat[ii].position[0]-epochDGNSS->receiver.aproxPosition[0])*(epochDGNSS->sat[ii].position[0]-epochDGNSS->receiver.aproxPosition[0]) +
			 (epochDGNSS->sat[ii].position[1]-epochDGNSS->receiver.aproxPosition[1])*(epochDGNSS->sat[ii].position[1]-epochDGNSS->receiver.aproxPosition[1]) +
			 (epochDGNSS->sat[ii].position[2]-epochDGNSS->receiver.aproxPosition[2])*(epochDGNSS->sat[ii].position[2]-epochDGNSS->receiver.aproxPosition[2]))/c0;
		getVelocityBRDC(products->BRDC,block,&t,epochDGNSS->sat[ii].position,velocity,svINERTIAL,epochDGNSS->sat[ii].GNSS);

		// Relativistic correction
		if ( options->earthRotation ) {
			correctEarthRotation(epochDGNSS->sat[ii].position,flightTime);
			correctEarthRotation(velocity,flightTime);
		}

		// Geometric distance
		epochDGNSS->sat[ii].geometricDistance = 
		sqrt((epochDGNSS->receiver.aproxPosition[0]-epochDGNSS->sat[ii].position[0])*(epochDGNSS->receiver.aproxPosition[0]-epochDGNSS->sat[ii].position[0]) +
			 (epochDGNSS->receiver.aproxPosition[1]-epochDGNSS->sat[ii].position[1])*(epochDGNSS->receiver.aproxPosition[1]-epochDGNSS->sat[ii].position[1]) +
			 (epochDGNSS->receiver.aproxPosition[2]-epochDGNSS->sat[ii].position[2])*(epochDGNSS->receiver.aproxPosition[2]-epochDGNSS->sat[ii].position[2]));

		// Total Group Delay (TGD)
		TGD = block->TGD * c0 * pow(GPSf1,2.0);
		lambda = getLambda(epochDGNSS->sat[ii].GNSS,C1C);
		TGD = TGD * pow(lambda,2.0) / pow(c0,2.0);

		// Clock correction
		if ( options->satelliteClockCorrection ) {
			dtClock = -1*getClockBRDC(block,&epochDGNSS->t);
		} else {
			dtClock = 0.0;
		}

		// Relativistic correction
		if ( options->relativisticCorrection ) {
			rel = scalarProd(epochDGNSS->sat[ii].position,velocity) * 2 / c0;
		} else {
			rel = 0.0;
		}

		// Satellite azimuth and elevation
		distance = 0;
		for (j=0;j<3;j++) {
			distance += (epochDGNSS->sat[ii].position[j]-epochDGNSS->receiver.aproxPosition[j])*(epochDGNSS->sat[ii].position[j]-epochDGNSS->receiver.aproxPosition[j]);
		}
		distance = sqrt(distance);
		for (j=0;j<3;j++) {
			relativeLoS[j] =
			((epochDGNSS->sat[ii].position[0]-epochDGNSS->receiver.aproxPosition[0])*epochDGNSS->receiver.orientation[j][0] + 	
			(epochDGNSS->sat[ii].position[1]-epochDGNSS->receiver.aproxPosition[1])*epochDGNSS->receiver.orientation[j][1] + 	
			(epochDGNSS->sat[ii].position[2]-epochDGNSS->receiver.aproxPosition[2])*epochDGNSS->receiver.orientation[j][2]) / distance;
		}
		//azimuth = atan2(relativeLoS[1],relativeLoS[0]);
		elevation = asin(relativeLoS[2]);

		// Receiver Antenna Reference Point (ARP)
        if ( options->ARPData >= arpSET ) {
			fillLineOfSight(epochDGNSS,ii);
            ARPProjection = receiverARPCorrection(epochDGNSS->receiver.ARP,epochDGNSS->receiver.orientation,epochDGNSS->sat[ii].LoS);
        }

		// PRC computation
		if ( C1s > 300.0 ) {
			epochDGNSS->dgnss.PRC[i] = epochDGNSS->sat[ii].geometricDistance + dtClock + rel + TGD + ARPProjection - C1s;
			epochDGNSS->dgnss.CLKref += epochDGNSS->dgnss.PRC[i];
			epochDGNSS->dgnss.Nref += 1;
		}

		// UDRE or PRC
		// Receiver noise: MOPS (It is assumed only Reference Receiver noise as "sigmaURA")
		sigmaMultipath = options->dgnssSigma2multipath / tan(elevation) / tan(elevation);
		sigmaAir = ( sigmaMultipath + options->dgnssSigma2noiseGPS ) * epochDGNSS->dgnss.sigmaInflation[i];
		epochDGNSS->dgnss.sigmaURA3[i] = sqrt(sigmaAir);
	}

	// Since the satellite clock is removed from the corrections, it must be also removed from the user modelling.
	// The receiver clock is common for all satellite, and thence it does not affect the positioning.
	// Therefore, the PRC corrections are relative to the broadcast orbits and clocks.
	// The clocks are removed from the corrections to smooth the corrections, only for plotting purposes.
	// Actually, it is not necessary to subtract the "satellite clock" nor the "receiver clock".
	// It would be enough to compute the PRC as: geometric distance - smoothed pseudorange
	nPRC = 0;
	if ( epochDGNSS->dgnss.Nref >= 4 ) {
		for ( ii=0;ii<epochDGNSS->numSatellites;ii++ ) {
			// Index of the satellite in the dictionary
			i = epochDGNSS->satCSIndex[epochDGNSS->sat[ii].GNSS][epochDGNSS->sat[ii].PRN];
			epochDGNSS->dgnss.PRC[i] = epochDGNSS->dgnss.PRC[i] - epochDGNSS->dgnss.CLKref / ((double)(epochDGNSS->dgnss.Nref));
			memcpy(&epochDGNSS->dgnss.tPRC[i],&epochDGNSS->t,sizeof(TTime));
			nPRC++;
		}
	}

	// If the number of valid corrections is less than 4, we keep the previous computed ones
	if ( nPRC < 4 ) {
		for ( i=0;i<MAX_SATELLITES_VIEWED;i++ ) {
			memcpy(&epochDGNSS->dgnss.tPRC[i],&epochDGNSS->dgnss.tPRCp[i],sizeof(TTime));
			epochDGNSS->dgnss.PRC[i] = epochDGNSS->dgnss.PRCp[i];
			epochDGNSS->dgnss.sigmaURA3[i] = epochDGNSS->dgnss.sigmaURA3p[i];
		}
	}
}

/*****************************************************************************
 * Name        : preFillUsableSatellites
 * Description : Check if there are DGNSS corrections
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch structure
 * TEpoch  *epochDGNSS             I  N/A  TEpoch structure
 * TGNSSproducts  *products        I  N/A  Orbit and clock GNSS products to obtain the model
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void preFillUsableSatellites (TEpoch *epoch, TEpoch *epochDGNSS, TGNSSproducts *products, TOptions *options) {
	int			i, j, numUsedSat = 0;
	TBRDCblock	*block = NULL;

	options->solutionMode = DGNSSMode;

	for ( i=0; i<epoch->numSatellites; i++ ) {
		// Get index of the satellite in epochDGNSS
		j = epochDGNSS->satCSIndex[epoch->sat[i].GNSS][epoch->sat[i].PRN];
		if(j==-1) {
			//Satellite not seen at any epoch in the reference station
			//This can occur if rover is advanced to the reference station
			epoch->sat[i].hasDGNSScor = 0;
			continue; 
		}

		// DGNSS corrections available
		epoch->sat[i].hasDGNSScor = 1;
		// Get block of orbits and compare IODs from BRDC and RTCM
		if ( epochDGNSS->dgnss.msg[j] == 1 ) {
			block = selectBRDCblock(products->BRDC,&epoch->sat[i].transTime,epoch->sat[i].GNSS,epoch->sat[i].PRN,epochDGNSS->dgnss.IODmsg1[j],options);
			if ( block == NULL ) block = selectBRDCblock(products->BRDC,&epoch->sat[i].transTime,epoch->sat[i].GNSS,epoch->sat[i].PRN,epochDGNSS->dgnss.IODmsg2[j],options);
			if ( block != NULL ) {
				if ( block->IODE != epochDGNSS->dgnss.IODmsg1[j] && block->IODE != epochDGNSS->dgnss.IODmsg2[j] ) {
					epoch->sat[i].hasDGNSScor = 5;
				}
				if ( block->IODE != epochDGNSS->dgnss.IODmsg1[j] && block->IODE == epochDGNSS->dgnss.IODmsg2[j] ) {
					if ( tdiff(&epoch->t,&epochDGNSS->dgnss.tdeltaPRC[j]) > options->maxAgeDGNSS && epochDGNSS->cycleslip.arcLength[j] > 0 ) {
						epoch->sat[i].hasDGNSScor = 3;
					}
				}
			} else epoch->sat[i].hasDGNSScor = 0;
			if ( block == NULL ) block = selectBRDCblock(products->BRDC,&epoch->sat[i].transTime,epoch->sat[i].GNSS,epoch->sat[i].PRN,-1,options);
			if ( block == NULL ) {
				epoch->sat[i].hasOrbitsAndClocks = 0;
			}
		}
	
		// Filter check large corrections
		if ( fabs(epochDGNSS->dgnss.PRC[j]) > options->maxDGNSSPRC ) epoch->sat[i].hasDGNSScor = 6;


		if ( epochDGNSS->dgnss.sigmaURA3[j] <= 0.0 ) {
			// No DGNSS corrections
			epoch->sat[i].hasDGNSScor = 0;
		}
		if ( tdiff(&epoch->t,&epochDGNSS->dgnss.tPRC[j]) > options->maxAgeDGNSS && epochDGNSS->dgnss.tPRC[j].MJDN != 0 ) {
			// DGNSS corrections time-out
			epoch->sat[i].hasDGNSScor = 2;
		}
		if ( options->csL1C1 == 1 || options->csBW == 1 || options->csLI == 1 || options->csLLI == 1 ) {
			if ( epochDGNSS->dgnss.msg[j] == 0 ) { // It is not possible to smooth with RTCM v2.x
				if ( ( epochDGNSS->cycleslip.arcLength[j] < options->excludeSmoothingConvergenceTime && epochDGNSS->dgnss.tPRC[j].MJDN != 0 )
					&& options->excludeSmoothingConvergenceRef == 1 ) {
					// No DGNSS corrections during the smoothing in the Reference Station
					epoch->sat[i].hasDGNSScor = 3;
				}
			}
			if ( ( epoch->cycleslip.arcLength[i] < options->excludeSmoothingConvergenceTime && epoch->cycleslip.arcLength[i] > 0 )
				&& options->excludeSmoothingConvergenceUser == 1 ) {
				// No DGNSS corrections during the smoothing in the User Station
				epoch->sat[i].hasDGNSScor = 4;
			}
		}

		// Increase the number of satellites in use
		if ( epoch->sat[i].hasDGNSScor == 1 ) numUsedSat++;
	}

	// If there is not enough satellites, gLAB moves from DGNSS to SPP
	if ( numUsedSat < 4 ) {
		if (options->printDGNSSUNUSED==0) {
			for ( i=0; i<epoch->numSatellites; i++ ) epoch->sat[i].hasDGNSScor = 1;
			options->solutionMode = SPPMode;
			if (options->stanfordesa==1) {
				//Disable temporary Stanford-ESA when solution moves to SPP
				options->stanfordesa=3;
			}

			sprintf(messagestr, "Solution moved from DGNSS to SPP at %17s due to lack of satellites (%d available)", t2doystr(&epoch->t), numUsedSat);
			printInfo(messagestr, options);
		}	
	}
}

// NeQuick-G JRC. Implementation begin
double_t get_solar_mean_spot_number
  (double_t solar_12_month_running_mean_of_2800_MHZ_noise_flux) {
  return (sqrt(167273.0 +
      (solar_12_month_running_mean_of_2800_MHZ_noise_flux -
      ITU_R_P_371_8_LOWER_SOLAR_FLUX_IN_SFU)*1123.6
    ) - 408.99);
}

double_t position_get_radius_km (
  const position_t* const p) {
  double_t height = NEQUICK_G_EARTH_RADIUS_IN_KM;
  if (p->height_units == NEQUICK_G_JRC_HEIGHT_UNITS_METERS) {
    height += NEQUICK_G_POSITION_METERS_TO_KM(p->height);
  } else {
    height += p->height;
  }
  return height;
}

int32_t position_set(
  position_t* const p,
  double_t longitude_degree,
  double_t latitude_degree,
  double_t height, uint_fast8_t height_units) {

  {
    if ((latitude_degree < NEQUICK_G_JRC_LAT_MIN_VALUE_DEGREE) ||
        (latitude_degree > NEQUICK_G_JRC_LAT_MAX_VALUE_DEGREE)) {
      NEQUICK_ERROR_RETURN(
        NEQUICK_INPUT_DATA_EXCEPTION,
        NEQUICK_INPUT_DATA_BAD_LATITUDE,
        "latitude out of range: %lf (degrees), must be between -90.0 and 90.0",
        latitude_degree);
    }

    angle_set(&p->latitude, latitude_degree);
  }

  {
    p->longitude_org = longitude_degree;
    /* Longitude must be between 0.0 and 360.0 */
    longitude_degree =
      fmod(longitude_degree + NEQUICK_G_JRC_CIRCLE_DEGREES,
          NEQUICK_G_JRC_CIRCLE_DEGREES);

    angle_set(&p->longitude, longitude_degree);
  }

  {
    p->height = height;
    p->height_units = height_units;
    p->radius_km = position_get_radius_km(p);
  }
  return NEQUICK_OK;
}

void position_to_km(position_t* const p) {
  if (p->height_units == NEQUICK_G_JRC_HEIGHT_UNITS_METERS) {
    p->height = NEQUICK_G_POSITION_METERS_TO_KM(p->height);
    p->height_units =
      NEQUICK_G_JRC_HEIGHT_UNITS_KM;
  }
}

bool position_is_above(
  const position_t* const p1, const position_t* const p2) {
  return (
    (fabs(p2->latitude.degree - p1->latitude.degree) <
      NEQUICK_G_POSITION_HORIZONTAL_COORD_EPSILON) &&
    (fabs(p2->longitude.degree - p1->longitude.degree) <
      NEQUICK_G_POSITION_HORIZONTAL_COORD_EPSILON));
}

bool position_is_exterior(
  const double_t height_km) {
  return (height_km >= NEQUICK_G_EARTH_RADIUS_IN_KM);
}

double_t get_radius_from_height(const double_t height_km) {
  return (height_km + NEQUICK_G_EARTH_RADIUS_IN_KM);
}

double_t get_height_from_radius(const double_t radius_km) {
  return (radius_km - NEQUICK_G_EARTH_RADIUS_IN_KM);
}

void bottom_side_get_B_params(
  bottom_side_info_t* const pBottom_side_info,
  const iono_profile_t* const pProfile,
  const double_t height_km) {

  pBottom_side_info->F2.B_param =
    pProfile->F2.layer.peak.thickness.bottom_km;

  pBottom_side_info->F1.B_param =
    (height_km > pProfile->F1.peak.height_km) ?
    pProfile->F1.peak.thickness.top_km :
    pProfile->F1.peak.thickness.bottom_km;

  pBottom_side_info->E.B_param =
    (height_km > pProfile->E.layer.peak.height_km) ?
    pProfile->E.layer.peak.thickness.top_km :
    pProfile->E.layer.peak.thickness.bottom_km;
}

bool is_exponential_arg_above_threshold(double_t exponential_arg) {
  return (
    fabs(exponential_arg) >
    NEQUICK_G_JRC_ELE_DENSITY_BOTTOM_EPSILON);
}

void bottom_side_get_exp_params(
  bottom_side_info_t* const pBottom_side_info,
  const iono_profile_t* const pProfile,
  const double_t height_km) {

 double_t height_above_F2_peak_km =
    height_km - pProfile->F2.layer.peak.height_km;

 pBottom_side_info->F2.exponential_arg =
   height_above_F2_peak_km / pBottom_side_info->F2.B_param;

 pBottom_side_info->F1.exponential_arg =
   (height_km - pProfile->F1.peak.height_km) / pBottom_side_info->F1.B_param;

 pBottom_side_info->E.exponential_arg =
   (height_km - pProfile->E.layer.peak.height_km) / pBottom_side_info->E.B_param;

 double_t temp =
   exp(NEQUICK_G_JRC_ELE_DENSITY_BOTTOM_CONST_1 /
   ((NEQUICK_G_JRC_ELE_DENSITY_BOTTOM_CONST_2 *
     fabs(height_above_F2_peak_km) + 1.0)));

  pBottom_side_info->F1.exponential_arg *= temp;
  pBottom_side_info->E.exponential_arg *= temp;

  pBottom_side_info->F2.is_exponential_arg_above_threshold =
    is_exponential_arg_above_threshold(pBottom_side_info->F2.exponential_arg);

  pBottom_side_info->F1.is_exponential_arg_above_threshold =
    is_exponential_arg_above_threshold(pBottom_side_info->F1.exponential_arg);

  pBottom_side_info->E.is_exponential_arg_above_threshold =
    is_exponential_arg_above_threshold(pBottom_side_info->E.exponential_arg);

  pBottom_side_info->F2.exponential_arg =
    exp(pBottom_side_info->F2.exponential_arg);

  pBottom_side_info->F1.exponential_arg =
    exp(pBottom_side_info->F1.exponential_arg);

  pBottom_side_info->E.exponential_arg =
    exp(pBottom_side_info->E.exponential_arg);
}

double_t get_s_param(
  const double_t peak_amplitude,
  const bottom_side_t* const pInfo) {
  if (pInfo->is_exponential_arg_above_threshold) {
    return 0.0;
  } else {
    return (peak_amplitude * pInfo->exponential_arg /
            NeQuickG_square(pInfo->exponential_arg + 1.0));
  }
}

double_t get_ds_param(const bottom_side_t* const pInfo) {
  if (pInfo->is_exponential_arg_above_threshold) {
    return 0.0;
  } else {
    return ((1.0 - pInfo->exponential_arg) /
       (1.0 + pInfo->exponential_arg)) /
          pInfo->B_param;
  }
}

void bottom_side_get_s_params(
  bottom_side_info_t* const pBottom_side_info,
  const iono_profile_t* const pProfile) {

  pBottom_side_info->F2.s =
    get_s_param(
      pProfile->F2.layer.peak.amplitude,
      &pBottom_side_info->F2);

  pBottom_side_info->F1.s =
    get_s_param(
      pProfile->F1.peak.amplitude,
      &pBottom_side_info->F1);

  pBottom_side_info->E.s =
    get_s_param(
      pProfile->E.layer.peak.amplitude,
      &pBottom_side_info->E);
}

double_t bottom_side_low(
  const bottom_side_info_t* const pBottom_side_info,
  const double_t height_km) {

  double_t F2_ds_param = get_ds_param(&pBottom_side_info->F2);
  double_t F1_ds_param = get_ds_param(&pBottom_side_info->F1);
  double_t E_ds_param = get_ds_param(&pBottom_side_info->E);

  double_t s_sum =
    pBottom_side_info->F2.s +
    pBottom_side_info->F1.s +
    pBottom_side_info->E.s;

  double_t s_ds_sum =
    (pBottom_side_info->F2.s * F2_ds_param) +
    (pBottom_side_info->F1.s * F1_ds_param) +
    (pBottom_side_info->E.s * E_ds_param);

  // chapman parameters BC and Z
  double_t BC = 1.0 -
    ((s_ds_sum / s_sum) * NEQUICK_G_JRC_ELE_DENSITY_BOTTOM_SCALE);

  double_t Z =
    (height_km - NEQUICK_G_JRC_ELE_DENSITY_BOTTOM_CORRECTION_ANCHOR_POINT) /
    NEQUICK_G_JRC_ELE_DENSITY_BOTTOM_SCALE;

  return (s_sum * NeQuickG_exp(1 - ((BC * Z) + NeQuickG_exp(-Z))));
}

double_t bottom_side_high(
  const bottom_side_info_t* const pBottom_side_info) {
  return (
    pBottom_side_info->F2.s +
    pBottom_side_info->F1.s +
    pBottom_side_info->E.s);
}

/** This function calculates electron content at the specified height,
 * in the bottom part of the ionosphere below the F2 peak height.
 * The function sums semi-Epstein Layers with a modification to reduce
 * excessive Ne around F2 peak and 100km.
 *
 * @return electron content at the specified height.
 */
double_t bottom_side(
  const iono_profile_t* const pProfile,
  const double_t height_km) {

  bottom_side_info_t bottom_side_info;

  bottom_side_get_B_params(&bottom_side_info, pProfile, height_km);

  bottom_side_get_exp_params(
    &bottom_side_info, pProfile,
    max(NEQUICK_G_JRC_ELE_DENSITY_BOTTOM_CORRECTION_ANCHOR_POINT, height_km));

  bottom_side_get_s_params(&bottom_side_info, pProfile);

  double_t electron_density =
    (height_km < NEQUICK_G_JRC_ELE_DENSITY_BOTTOM_CORRECTION_ANCHOR_POINT) ?
      bottom_side_low(&bottom_side_info, height_km):
      bottom_side_high(&bottom_side_info);

  return NEQUICK_G_JRC_ELE_DENSITY_TO_ELECTRON_DENSITY(electron_density);
}

/** This function calculates electron content at the specified height,
 * in the top part of the ionosphere above the F2 electron density peak point.
 * The function uses topside expression derived from [Annex A [15]],
 * although the expression in the paper has an error with the brackets.
 *
 * @param ionosphere profile
 *         maximum Ne (F2 peak)
 *
 * @param The height at which the electron density is required
 *
 * @return electron content at the specified height.
 */
double_t top_side(
  iono_profile_t* const pProfile,
  const double_t height_km) {

  double_t height_above_F2_peak_km =
    height_km - pProfile->F2.layer.peak.height_km;

  double_t delta_height =
    NEQUICK_G_JRC_ELE_DENSITY_TOP_CONST_1 *
    height_above_F2_peak_km;

  double_t temp =
    NeQuickG_exp(
      height_above_F2_peak_km /
       (pProfile->F2.layer.peak.thickness.top_km *
         (1.0 +
           ((NEQUICK_G_JRC_ELE_DENSITY_TOP_CONST_2 * delta_height) /
              ((NEQUICK_G_JRC_ELE_DENSITY_TOP_CONST_2 *
                pProfile->F2.layer.peak.thickness.top_km) +
                delta_height)))));

  if (temp > NEQUICK_G_JRC_ELE_DENSITY_TOP_APROXIMATION_EPSILON) {
    temp = 1.0 / temp;
  } else {
    temp /= NeQuickG_square(1.0 + temp);
  }

  if (isnan(pProfile->F2.layer.peak.electron_density)) {
    pProfile->F2.layer.peak.electron_density =
      bottom_side(pProfile, pProfile->F2.layer.peak.height_km);
  }
  return (NEQUICKG_IONO_LAYER_GET_PEAK_AMPLITUDE(temp) *
          pProfile->F2.layer.peak.electron_density);
}

double_t electron_density_get(
  iono_profile_t* const pProfile,
  const double_t height_km) {

  if (height_km > pProfile->F2.layer.peak.height_km) {
    return top_side(pProfile, height_km);
  } else {
    return bottom_side(pProfile, height_km);
  }
}

/** Set at what points the samples are used in integration process */
const double_t xi[NEQUICK_G_JRC_KRONROD_K15_POINT_COUNT] = {
  -NEQUICK_G_JRC_KRONROD_POINT_7,
  -NEQUICK_G_JRC_KRONROD_POINT_6,
  -NEQUICK_G_JRC_KRONROD_POINT_5,
  -NEQUICK_G_JRC_KRONROD_POINT_4,
  -NEQUICK_G_JRC_KRONROD_POINT_3,
  -NEQUICK_G_JRC_KRONROD_POINT_2,
  -NEQUICK_G_JRC_KRONROD_POINT_1,
  0,
  NEQUICK_G_JRC_KRONROD_POINT_1,
  NEQUICK_G_JRC_KRONROD_POINT_2,
  NEQUICK_G_JRC_KRONROD_POINT_3,
  NEQUICK_G_JRC_KRONROD_POINT_4,
  NEQUICK_G_JRC_KRONROD_POINT_5,
  NEQUICK_G_JRC_KRONROD_POINT_6,
  NEQUICK_G_JRC_KRONROD_POINT_7
};

/** Set weights for K15 sample points */
const double_t wi[NEQUICK_G_JRC_KRONROD_K15_POINT_COUNT] = {
  NEQUICK_G_JRC_KRONROD_K15_WEIGHT_1,
  NEQUICK_G_JRC_KRONROD_K15_WEIGHT_2,
  NEQUICK_G_JRC_KRONROD_K15_WEIGHT_3,
  NEQUICK_G_JRC_KRONROD_K15_WEIGHT_4,
  NEQUICK_G_JRC_KRONROD_K15_WEIGHT_5,
  NEQUICK_G_JRC_KRONROD_K15_WEIGHT_6,
  NEQUICK_G_JRC_KRONROD_K15_WEIGHT_7,
  NEQUICK_G_JRC_KRONROD_K15_WEIGHT_8,
  NEQUICK_G_JRC_KRONROD_K15_WEIGHT_7,
  NEQUICK_G_JRC_KRONROD_K15_WEIGHT_6,
  NEQUICK_G_JRC_KRONROD_K15_WEIGHT_5,
  NEQUICK_G_JRC_KRONROD_K15_WEIGHT_4,
  NEQUICK_G_JRC_KRONROD_K15_WEIGHT_3,
  NEQUICK_G_JRC_KRONROD_K15_WEIGHT_2,
  NEQUICK_G_JRC_KRONROD_K15_WEIGHT_1
};

/** Set weights for G7 sample points */
const double_t wig[NEQUICK_G_JRC_KRONROD_G7_POINT_COUNT] = {
  NEQUICK_G_JRC_KRONROD_G7_WEIGHT_1,
  NEQUICK_G_JRC_KRONROD_G7_WEIGHT_2,
  NEQUICK_G_JRC_KRONROD_G7_WEIGHT_3,
  NEQUICK_G_JRC_KRONROD_G7_WEIGHT_4,
  NEQUICK_G_JRC_KRONROD_G7_WEIGHT_3,
  NEQUICK_G_JRC_KRONROD_G7_WEIGHT_2,
  NEQUICK_G_JRC_KRONROD_G7_WEIGHT_1
};

bool is_error_within_tolerance(
  const gauss_kronrod_context_t* const pContext,
  double_t K15_integration,
  double_t G7_integration) {

  return (
    (fabs((K15_integration - G7_integration) / K15_integration) <=
      pContext->tolerance) ||
    (fabs(K15_integration - G7_integration) <=
      pContext->tolerance));
}

int32_t get_total_electron_content_impl(
  NeQuickG_context_t* const pNequick_Context,
  double_t height_km,
  double_t* const pTotal_electron_content) {

  if (pNequick_Context->ray.is_vertical) {
    *pTotal_electron_content = ray_vertical_get_electron_density(
      pNequick_Context, height_km);
    return NEQUICK_OK;
  } else {
    return ray_slant_get_electron_density(
      pNequick_Context, height_km, pTotal_electron_content);
  }
}

int32_t Gauss_Kronrod_integrate(
  gauss_kronrod_context_t* const pContext,
  NeQuickG_context_t* const pNequick_Context,
  const double_t point_1_height_km,
  const double_t point_2_height_km,
  double_t* const pResult) {

  *pResult = 0.0;

  double_t mid_point = (point_1_height_km + point_2_height_km) / 2.0;
  double_t half_diff = (point_2_height_km - point_1_height_km) / 2.0;

  double_t K15_integration = 0.0;
  double_t G7_integration = 0.0;
  size_t G7_index = 0;

  size_t i;
  for (i = 0; i < NEQUICK_G_JRC_KRONROD_K15_POINT_COUNT; i++) {

    double_t height_km = mid_point + (half_diff * xi[i]);

    double_t total_electron_content;
    int32_t ret =
      get_total_electron_content_impl(
        pNequick_Context, height_km, &total_electron_content);
    if (ret != NEQUICK_OK) {
      return ret;
    }

    K15_integration += (total_electron_content * wi[i]);

    if (IS_ODD(i)) {
      G7_integration += (total_electron_content * wig[G7_index]);
      G7_index++;
    }
  }

  K15_integration *= half_diff;
  G7_integration *= half_diff;

  if (is_error_within_tolerance(
    pContext,
    K15_integration,
    G7_integration)) {

    *pResult = K15_integration;
    return NEQUICK_OK;

  } else if (pContext->recursion_level == pContext->recursion_max) {

    *pResult = K15_integration;
    return NEQUICK_OK;

  } else {

    // Error not acceptable
    // split into two parts to improve accuracy
    // and try again.
    pContext->recursion_level++;

    double_t result;

    int32_t ret;

    ret = Gauss_Kronrod_integrate(
      pContext,
      pNequick_Context,
      point_1_height_km,
      point_1_height_km + half_diff,
      pResult);
    if (ret != NEQUICK_OK) {
      return ret;
    }

    ret = Gauss_Kronrod_integrate(
      pContext,
      pNequick_Context,
      point_1_height_km + half_diff,
      point_2_height_km,
      &result);

    *pResult += result;

    pContext->recursion_level--;

    return ret;
  }
}

void angle_set(angle_t* const pAngle, double_t angle_degree) {

  pAngle->degree = angle_degree;
  pAngle->rad = NEQUICKG_JRC_DEGREE_TO_RAD(angle_degree);
  pAngle->sin = sin(pAngle->rad);
  pAngle->cos = cos(pAngle->rad);
}

void angle_set_rad(angle_t* const pAngle, double_t angle_rad) {
  pAngle->degree = NEQUICKG_JRC_RAD_TO_DEGREE(angle_rad);
  pAngle->rad = angle_rad;
  pAngle->sin = sin(pAngle->rad);
  pAngle->cos = cos(pAngle->rad);
}

void angle_set_fom_sin(angle_t* const pAngle) {
  pAngle->cos = get_cos_from_sin(pAngle->sin);
  pAngle->rad = atan2(pAngle->sin, pAngle->cos);
  pAngle->degree = NEQUICKG_JRC_RAD_TO_DEGREE(pAngle->rad);
}

void angle_set_fom_cos(angle_t* const pAngle) {
  pAngle->sin = get_sin_from_cos(pAngle->cos);
  pAngle->rad = atan2(pAngle->sin, pAngle->cos);
  pAngle->degree = NEQUICKG_JRC_RAD_TO_DEGREE(pAngle->rad);
}

void angle_restricted_set(
  angle_restricted_t* const pAngle, double_t rad) {
  pAngle->sin = sin(rad);
  pAngle->cos = cos(rad);
}

void input_data_to_km(
  input_data_t* const pInputData) {
  position_to_km(&pInputData->station_position);
  position_to_km(&pInputData->satellite_position);
}

double_t interpolation_third_order(
  const double_t interpol_points[NEQUICK_G_JRC_INTERPOLATE_POINT_COUNT],
  double_t offset) {
  double_t result = 0.0;

  if (fabs(offset) < NEQUICK_G_JRC_INTERPOL_EPSILON) {
    return interpol_points[NEQUICK_G_JRC_INTERPOL_POINT_1_INDEX];
  }

  double_t sum_1_2 = interpol_points[NEQUICK_G_JRC_INTERPOL_POINT_2_INDEX] +
                   interpol_points[NEQUICK_G_JRC_INTERPOL_POINT_1_INDEX];
  double_t grad_2_1 = interpol_points[NEQUICK_G_JRC_INTERPOL_POINT_2_INDEX] -
                    interpol_points[NEQUICK_G_JRC_INTERPOL_POINT_1_INDEX];

  double_t sum_3_0 = interpol_points[NEQUICK_G_JRC_INTERPOL_POINT_3_INDEX] +
                   interpol_points[NEQUICK_G_JRC_INTERPOL_POINT_0_INDEX];
  double_t grad_3_0 = (interpol_points[NEQUICK_G_JRC_INTERPOL_POINT_3_INDEX] -
                     interpol_points[NEQUICK_G_JRC_INTERPOL_POINT_0_INDEX])/
                     (double_t)((double_t)NEQUICK_G_JRC_INTERPOLATE_POINT_COUNT - 1.0);

  double_t coefficients[NEQUICK_G_JRC_INTERPOLATE_POINT_COUNT];
  {
     size_t i = 0;
     coefficients[i++] =
      (NEQUICK_G_JRC_INTERPOL_FIRST_CONST*sum_1_2) - sum_3_0;
     coefficients[i++] =
      (NEQUICK_G_JRC_INTERPOL_FIRST_CONST*grad_2_1) - grad_3_0;
     coefficients[i++] = (sum_3_0 - sum_1_2);
     coefficients[i] = (grad_3_0 - grad_2_1);
  }
  double_t delta = (2.0 * offset) - 1.0;
  for (int_fast8_t i = NEQUICK_G_JRC_INTERPOLATE_POINT_COUNT - 1;
       i >= 0x00 ; i--) {
    result = (result * delta) + coefficients[i];
  }
  return (result / NEQUICK_G_JRC_INTERPOL_SECOND_CONST);
}

/**
 * Define the seas parameter as a function of the month of the year as follows:
 * If mth = 1,2,11,12 then seas = -1
 * If mth = 3,4,9,10 then seas = 0
 * If mth = 5,6,7,8 then seas = 1
*/
//lint -esym(533, get_seasonal_parameter) should return a value
// there is an exception in the default case
// but lint cannot handle it
double_t get_seasonal_parameter(
  const NeQuickG_time_t * const pTime) {
  switch (pTime->month) {
  case NEQUICK_G_JRC_MONTH_JANUARY:
  case NEQUICK_G_JRC_MONTH_FEBRUARY:
  case NEQUICK_G_JRC_MONTH_NOVEMBER:
  case NEQUICK_G_JRC_MONTH_DECEMBER:
    return -1.0;
  case NEQUICK_G_JRC_MONTH_MARCH:
  case NEQUICK_G_JRC_MONTH_APRIL:
  case NEQUICK_G_JRC_MONTH_SEPTEMBER:
  case NEQUICK_G_JRC_MONTH_OCTOBER:
    return 0.0;
  case NEQUICK_G_JRC_MONTH_MAY:
  case NEQUICK_G_JRC_MONTH_JUNE:
  case NEQUICK_G_JRC_MONTH_JULY:
  case NEQUICK_G_JRC_MONTH_AUGUST:
    return 1.0;
  default:
    // This was validated in set_time
    //lint -e{506} this is intententionally a constant value boolean
    assert(false);
    //lint -e{527} unreachable code is ok
    return 0.0;
  }
}

double_t get_lat_parameter(
  const position_t * const pPosition,
  const NeQuickG_time_t * const pTime) {

  // To compute the E layer critical frequency foE [MHz]
  // at a given location,
  // in addition to the effective solar zenith angle
  // a season dependent parameter has to be computed.
  double_t season_parameter = get_seasonal_parameter(pTime);

  // Introduce the latitudinal dependence.
  double_t ee =
    NeQuickG_exp(NEQUICK_G_JRC_IONO_E_LAYER_LAT_FACTOR *
                 pPosition->latitude.degree);

  return ((season_parameter*(ee - 1.0)) / (ee + 1.0));
}

void E_layer_get_critical_freq_MHz(
  E_layer_t* const pLayer,
  const NeQuickG_time_t* const pTime,
  const solar_activity_t* const pSolar_activity,
  const position_t* const pPosition) {

  double_t solar_effective_angle_degree;
  {
    if (!pLayer->is_solar_declination_valid) {
      pLayer->solar_declination = solar_get_declination(pTime);
    }

    solar_effective_angle_degree =
      solar_get_effective_zenith_angle(
        pPosition, pTime, &pLayer->solar_declination);
  }

  double_t parameter = get_lat_parameter(pPosition, pTime);

  double_t critical_freq =
    (NEQUICK_G_JRC_IONO_E_LAYER_CONSTANT_1 -
     NEQUICK_G_JRC_IONO_E_LAYER_CONSTANT_2*parameter) *
     sqrt(sqrt(pSolar_activity->effective_ionisation_level_sfu));

  critical_freq *=
    NeQuickG_exp(
      log(
        cos(NEQUICKG_JRC_DEGREE_TO_RAD(solar_effective_angle_degree)))
          *NEQUICK_G_JRC_IONO_E_LAYER_CONSTANT_3);

  pLayer->layer.critical_frequency_MHz =
    sqrt(critical_freq*critical_freq + NEQUICK_G_JRC_IONO_E_LAYER_CONSTANT_4);

  pLayer->layer.peak.electron_density =
    NEQUICK_G_JRC_IONO_GET_e_DENSITY(pLayer->layer.critical_frequency_MHz);
}

void E_layer_get_peak_height(E_layer_t* const pLayer) {
  pLayer->layer.peak.height_km =
    NEQUICK_G_JRC_IONO_E_LAYER_MAX_e_DENSITY_HEIGHT_KM;
}

void E_layer_get_peak_thickness(
  E_layer_t* const pE,
  const double_t F1_peak_thickness_bottom_km) {

  pE->layer.peak.thickness.top_km =
    max(F1_peak_thickness_bottom_km, NEQUICK_G_JRC_IONO_E_LAYER_MIN_TOP_KM);

  pE->layer.peak.thickness.bottom_km = NEQUICK_G_JRC_IONO_E_LAYER_BOTTOM_KM;
}

void E_layer_init(E_layer_t* const pE) {
  pE->is_solar_declination_valid = false;
}

void F1_layer_get_critical_freq_MHz(
  layer_t* const pLayer,
  const double_t critical_freq_E_layer_MHz,
  const double_t critical_freq_F2_layer_MHz) {

  double_t critical_freq_F1_layer_MHz =
    NeQuickG_func_join(
      NEQUICK_G_JRC_IONO_F1_LAYER_TITHERIDGE_FACTOR *
       critical_freq_E_layer_MHz,
      0.0,
      NEQUICK_G_JRC_IONO_F1_LAYER_JOIN_FRACTIONAL_1,
      critical_freq_E_layer_MHz - 2);

  critical_freq_F1_layer_MHz =
    NeQuickG_func_join(
      0.0,
      critical_freq_F1_layer_MHz,
      NEQUICK_G_JRC_IONO_F1_LAYER_JOIN_FRACTIONAL_1,
      critical_freq_E_layer_MHz - critical_freq_F1_layer_MHz);

  critical_freq_F1_layer_MHz =
    NeQuickG_func_join(
      critical_freq_F1_layer_MHz,
      NEQUICK_G_JRC_IONO_F1_LAYER_HEIGHT_CONSTANT *
        critical_freq_F1_layer_MHz,
      NEQUICK_G_JRC_IONO_F1_LAYER_JOIN_FRACTIONAL_2,
      (NEQUICK_G_JRC_IONO_F1_LAYER_HEIGHT_CONSTANT *
        critical_freq_F2_layer_MHz) -
      critical_freq_F1_layer_MHz);

  pLayer->critical_frequency_MHz =
    (critical_freq_F1_layer_MHz <
      NEQUICK_G_JRC_IONO_F1_FREQUENCY_LOWER_LIMIT_MHZ) ?
    0x00 :
    critical_freq_F1_layer_MHz;

  pLayer->peak.electron_density =
    NEQUICK_G_JRC_IONO_GET_e_DENSITY(pLayer->critical_frequency_MHz);
}

void F1_layer_get_peak_height(
  layer_t* const pLayer,
  const double_t E_peak_height_km,
  const double_t F2_peak_height_km) {
  pLayer->peak.height_km =
    (E_peak_height_km + F2_peak_height_km) / 2.0;
}

void F1_layer_get_peak_thickness(
  layer_t* const pF1,
  const double_t E_peak_height_km,
  const double_t F2_peak_height_km) {

  pF1->peak.thickness.top_km =
    NEQUICK_G_JRC_IONO_F1_LAYER_THICKNESS_TOP_FACTOR *
    (F2_peak_height_km - pF1->peak.height_km);

  pF1->peak.thickness.bottom_km =
    NEQUICK_G_JRC_IONO_F1_LAYER_THICKNESS_BOTTOM_FACTOR *
    (pF1->peak.height_km - E_peak_height_km);
}

const size_t NeQuickG_iono_F2_layer_crit_f_legrendre_grades
  [NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_COUNT] = {
  NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_0_LEGRENDE_GRADE,
  NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_1_LEGRENDE_GRADE,
  NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_2_LEGRENDE_GRADE,
  NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_3_LEGRENDE_GRADE,
  NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_4_LEGRENDE_GRADE,
  NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_5_LEGRENDE_GRADE,
  NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_6_LEGRENDE_GRADE,
  NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_7_LEGRENDE_GRADE,
  NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_8_LEGRENDE_GRADE};

const size_t NeQuickG_iono_F2_layer_trans_factor_grades[
  NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_COUNT] = {
  NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_0_LEGRENDE_GRADE,
  NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_1_LEGRENDE_GRADE,
  NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_2_LEGRENDE_GRADE,
  NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_3_LEGRENDE_GRADE,
  NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_4_LEGRENDE_GRADE,
  NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_5_LEGRENDE_GRADE,
  NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_6_LEGRENDE_GRADE};

void get_legrende_coeff_for_modip(
  const double_t modip_degree,
  double_t* const pCoeff) {

  pCoeff[0] = 1.0;
  // to satisfy lint
  size_t grade = (NEQUICKG_JRC_IONO_F2_LAYER_MODIP_COEFF_COUNT - 1);
  NeQuickG_get_power_array(
    grade,
    sin(NEQUICKG_JRC_DEGREE_TO_RAD(modip_degree)),
    NEQUICKG_JRC_IONO_F2_LAYER_MODIP_COEFF_NEGLIGIBLE_VALUE,
    &pCoeff[1]);
}

void get_legrende_coeff_for_longitude(
  const angle_t* const pLongitude,
  double_t* const pCoeff_sinus,
  double_t* const pCoeff_cosinus) {

  pCoeff_sinus[0] = pLongitude->sin;
  pCoeff_cosinus[0] = pLongitude->cos;

  double_t n_long = 2.0 * pLongitude->rad;

  // to satisfy lint
  size_t coeff_count = NEQUICKG_JRC_IONO_F2_LAYER_LONG_COEFF_COUNT;
  for (
    size_t i = 1;
    i < coeff_count;
    i++) {
    pCoeff_sinus[i] = sin(n_long);
    pCoeff_cosinus[i] = cos(n_long);
    n_long += pLongitude->rad;
  }
}

double_t legendre_expansion(
  const double_t* const pFourier_coeff,
  const size_t* const pLegendre_degrees_per_order,
  size_t legendre_degrees_per_order_size,
  const double_t* const pModip_coeff,
  const double_t* const pLong_coeff_sinus,
  const double_t* const pLong_coeff_cosinus,
  double_t cos_lat) {

  double_t parameter = 0.0;

  size_t degree_index;

  // Order 0 term
  for (
    degree_index = 0;
    degree_index < pLegendre_degrees_per_order[0];
    degree_index++) {
    parameter +=
      pFourier_coeff[degree_index]*
      pModip_coeff[degree_index];
  }

  double_t lat_coeff = cos_lat;

  // Order i + 1 term
  for (
    size_t i = 1;
    i < legendre_degrees_per_order_size;
    i++) {

    for (
      size_t j = 0;
      j < pLegendre_degrees_per_order[i];
      j++) {
      parameter +=
        (pModip_coeff[j] * lat_coeff *
        ((pFourier_coeff[degree_index] * pLong_coeff_cosinus[i - 1]) +
        (pFourier_coeff[degree_index + 1] * pLong_coeff_sinus[i - 1])));
      degree_index += 2;
    }

    lat_coeff *= cos_lat;
  }
  return parameter;
}

double_t get_transmission_factor(
  const Fm3_fourier_coefficient_array_t Cm3,
  const double_t* const pModip_coeff,
  const double_t* const pLong_coeff_sinus,
  const double_t* const pLong_coeff_cosinus,
  double_t cos_lat) {

  // to satisfy lint
  size_t order_count = NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_ORDER_COUNT;
  double_t transmission_factor = legendre_expansion(
    Cm3,
    NeQuickG_iono_F2_layer_trans_factor_grades,
    order_count,
    pModip_coeff,
    pLong_coeff_sinus,
    pLong_coeff_cosinus,
    cos_lat);

  return max(
    transmission_factor,
    NEQUICKG_JRC_IONO_F2_TRANS_FACTOR_MINIMUM_VALUE);
}

int32_t F2_layer_init(
  F2_layer_t* const pLayer) {

  return F2_layer_fourier_coefficients_init(&pLayer->coef);
}

int32_t F2_layer_get_critical_freq_MHz(
  F2_layer_t * const pF2,
  const NeQuickG_time_t* const pTime,
  const modip_context_t* const pModip,
  const solar_activity_t* const pSolar_activity,
  const position_t * const pCurrent_position) {

  int32_t ret = F2_layer_fourier_coefficients_get(
    &pF2->coef,
    pTime,
    pSolar_activity);
  if (ret != NEQUICK_OK) {
    return ret;
  }

  //lint -e{506} NEQUICKG_JRC_IONO_F2_LAYER_MODIP_COEFF_COUNT is not constant, as lint means
  double_t modip_coeff[NEQUICKG_JRC_IONO_F2_LAYER_MODIP_COEFF_COUNT];
  get_legrende_coeff_for_modip(pModip->modip_degree, modip_coeff);

  //lint -e{506} NEQUICKG_JRC_IONO_F2_LAYER_LONG_COEFF_COUNT is not constant, as lint means
  double_t long_coeff_sinus[NEQUICKG_JRC_IONO_F2_LAYER_LONG_COEFF_COUNT];

  //lint -e{506} NEQUICKG_JRC_IONO_F2_LAYER_LONG_COEFF_COUNT is not constant, as lint means
  double_t long_coeff_cosinus[NEQUICKG_JRC_IONO_F2_LAYER_LONG_COEFF_COUNT];

  get_legrende_coeff_for_longitude(
    &pCurrent_position->longitude,
    long_coeff_sinus,
    long_coeff_cosinus);

  // to satisfy lint
  size_t order_count = NEQUICKG_JRC_IONO_F2_CRITICAL_FREQ_ORDER_COUNT;
  pF2->layer.critical_frequency_MHz = legendre_expansion(
    pF2->coef.fourier.CF2,
    NeQuickG_iono_F2_layer_crit_f_legrendre_grades,
    order_count,
    modip_coeff,
    long_coeff_sinus,
    long_coeff_cosinus,
    pCurrent_position->latitude.cos);

  pF2->layer.peak.electron_density =
    NEQUICK_G_JRC_IONO_GET_e_DENSITY(
      pF2->layer.critical_frequency_MHz);

  pF2->trans_factor = get_transmission_factor(
    pF2->coef.fourier.Cm3,
    modip_coeff,
    long_coeff_sinus,
    long_coeff_cosinus,
    pCurrent_position->latitude.cos);

  return NEQUICK_OK;
}

double_t get_E_Term_for_peak_height(
  const double_t critical_freq_F2_layer_MHz,
  const double_t critical_freq_E_layer_MHz) {

  // soft clipped for r < 1.75, using NeQuickG_func_join
  double_t E_term =
    critical_freq_F2_layer_MHz /
    critical_freq_E_layer_MHz;

  E_term = NeQuickG_func_join(
    E_term, NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_JOIN_CLIP_CONST,
    NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_JOIN_CONST,
    E_term - NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_JOIN_CLIP_CONST);

  // no divide by zero check needed as r2 > ~1.75
  assert(E_term > NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_CONST_6);

  return (NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_CONST_5 /
           (E_term - NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_CONST_6));
}

void F2_layer_get_peak_height(
  F2_layer_t* const pF2,
  const double_t critical_freq_E_layer_MHz) {

  double_t transmission_factor_squared =
    pF2->trans_factor * pF2->trans_factor;

  // no divide by zero check needed as previous clipping
  // ensures M3000 >= 1
  assert(transmission_factor_squared >= 1.0);

  double_t numerator =
    NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_CONST_1 *
    pF2->trans_factor *
    sqrt(
      ((NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_CONST_2 *
        transmission_factor_squared) + 1.0) /
      ((NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_CONST_3 *
        transmission_factor_squared) - 1.0));

  double_t denominator =
    pF2->trans_factor +
    NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_CONST_4;

  if (NEQUICK_G_JRC_IONO_E_LAYER_INFLUENCES_F2_PEAK_HEIGHT(
        critical_freq_E_layer_MHz)) {

    denominator += get_E_Term_for_peak_height(
      pF2->layer.critical_frequency_MHz,
      critical_freq_E_layer_MHz);
  }

  pF2->layer.peak.height_km =
    (numerator / denominator) +
    NEQUICKG_JRC_IONO_F2_MAX_e_DENSITY_DUDENEY_CONST_7;
}

void F2_layer_get_peak_thickness(F2_layer_t* const pF2) {
  pF2->layer.peak.thickness.top_km = INFINITY;
  pF2->layer.peak.thickness.bottom_km =
    NEQUICK_G_JRC_IONO_F2_LAYER_THICKNESS_BOTTOM_FACTOR *
    pF2->layer.peak.electron_density;

  /* Calculate gradient of rho(e) at base of F2 layer (10^9 m^-3 km^-1)
   * re: Mosert de Gonzalez and Radicella, 1990, Adv. Space. Res., 10, 17 */
  double_t grad =
    NEQUICKG_JRC_IONO_F2_e_DENSITY_GRAD_CONST_1 *
    exp(NEQUICKG_JRC_IONO_F2_e_DENSITY_GRAD_CONST_2 +
       (NEQUICKG_JRC_IONO_F2_e_DENSITY_GRAD_CONST_3 *
         log(pF2->layer.critical_frequency_MHz *
             pF2->layer.critical_frequency_MHz)) +
       (NEQUICKG_JRC_IONO_F2_e_DENSITY_GRAD_CONST_4 *
         log(pF2->trans_factor))
       );

  pF2->layer.peak.thickness.bottom_km /= grad;
}

void F2_layer_get_peak_amplitude(F2_layer_t* const pF2) {
  pF2->layer.peak.amplitude =
    NEQUICKG_IONO_LAYER_GET_PEAK_AMPLITUDE(
      pF2->layer.peak.electron_density);
}

double_t F2_layer_get_shape_factor(
  const F2_layer_t* const pF2,
  const NeQuickG_time_t* const pTime,
  const solar_activity_t* const pSolar_activity) {

  double_t shape_factor;

  if ((pTime->month > NEQUICK_G_JRC_MONTH_MARCH) &&
      (pTime->month < NEQUICK_G_JRC_MONTH_OCTOBER)) {

    shape_factor =
      NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_1 +
      (NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_2 *
       pSolar_activity->effective_sun_spot_count) +
      (NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_3 *
       pF2->layer.peak.height_km);

  } else {

    shape_factor =
      NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_4 +
      (NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_5 *
        NeQuickG_square(pF2->layer.peak.height_km /
                        pF2->layer.peak.thickness.bottom_km)) +
      (NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_6 *
       pF2->layer.peak.electron_density);
  }

  shape_factor =
    NeQuickG_func_join(
      shape_factor,
      NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_7,
      NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_TRANSITION_REGION,
      shape_factor - NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_7);

  shape_factor =
    NeQuickG_func_join(
      NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_8,
      shape_factor,
      NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_TRANSITION_REGION,
      shape_factor - NEQUICKG_JRC_IONO_F2_SHAPE_FACTOR_CONST_8);

  return shape_factor;
}

void F2_layer_exosphere_adjust(
  F2_layer_t* const pF2,
  const NeQuickG_time_t* const pTime,
  const solar_activity_t* const pSolar_activity) {

  double_t shape_factor =
    F2_layer_get_shape_factor(pF2, pTime, pSolar_activity);

  pF2->layer.peak.thickness.top_km =
    shape_factor * pF2->layer.peak.thickness.bottom_km;

  double_t auxiliary_param_x =
    (pF2->layer.peak.thickness.top_km -
     NEQUICKG_JRC_IONO_F2_THICKNESS_TOP_CONST_1) /
      NEQUICKG_JRC_IONO_F2_THICKNESS_TOP_CONST_2;

  double_t auxiliary_param_v =
    (((NEQUICKG_JRC_IONO_F2_THICKNESS_TOP_CONST_3 * auxiliary_param_x) -
       NEQUICKG_JRC_IONO_F2_THICKNESS_TOP_CONST_4) * auxiliary_param_x) +
       NEQUICKG_JRC_IONO_F2_THICKNESS_TOP_CONST_5;

  pF2->layer.peak.thickness.top_km /= auxiliary_param_v;

  // Set to Not a Number.
  // It must be recalculated using the
  // electron density module
  pF2->layer.peak.electron_density = NAN;
}

int32_t iono_profile_init(iono_profile_t * const pProfile) {

  E_layer_init(&pProfile->E);

  return F2_layer_init(&pProfile->F2);
}

double_t iono_profile_get_amplitude_of_peak(
  const peak_t* const pPeak,
  double_t height_km) {

  double_t thickness_param =
    (pPeak->height_km > height_km) ?
    pPeak->thickness.bottom_km :
    pPeak->thickness.top_km;

  double_t electron_density =
    NeQuickG_exp((height_km - pPeak->height_km) /
                  thickness_param);

  electron_density =
    (pPeak->amplitude * electron_density /
      NeQuickG_square(electron_density + 1.0));

  return NEQUICKG_IONO_LAYER_GET_PEAK_AMPLITUDE(electron_density);
}

int32_t iono_profile_get_critical_freqs(
  iono_profile_t * const pProfile,
  const NeQuickG_time_t* const pTime,
  const modip_context_t* const pModip,
  const solar_activity_t* const pSolar_activity,
  const position_t * const pCurrent_position) {

  E_layer_get_critical_freq_MHz(
    &pProfile->E,
    pTime,
    pSolar_activity,
    pCurrent_position);

  int32_t ret = F2_layer_get_critical_freq_MHz(
    &pProfile->F2,
    pTime,
    pModip,
    pSolar_activity,
    pCurrent_position);
  if (ret != NEQUICK_OK) {
    return ret;
  }

  F1_layer_get_critical_freq_MHz(
    &pProfile->F1,
    pProfile->E.layer.critical_frequency_MHz,
    pProfile->F2.layer.critical_frequency_MHz);

  return NEQUICK_OK;
}

void iono_profile_get_peak_heights(
  iono_profile_t * const pProfile) {

  E_layer_get_peak_height(&pProfile->E);

  F2_layer_get_peak_height(
    &pProfile->F2,
    pProfile->E.layer.critical_frequency_MHz);

  F1_layer_get_peak_height(
    &pProfile->F1,
    pProfile->E.layer.peak.height_km,
    pProfile->F2.layer.peak.height_km);
}

void iono_profile_get_peak_thicknesses(
  iono_profile_t * const pProfile) {

  F2_layer_get_peak_thickness(
    &pProfile->F2);

  F1_layer_get_peak_thickness(
    &pProfile->F1,
    pProfile->E.layer.peak.height_km,
    pProfile->F2.layer.peak.height_km);

  E_layer_get_peak_thickness(
    &pProfile->E,
    pProfile->F1.peak.thickness.bottom_km);
}

double_t iono_profile_get_peak_amp_substracting_layer(
  const peak_t * const pPeak,
  const peak_t * const pOther_layer_peak) {
  double_t other_layer_contribution =
    iono_profile_get_amplitude_of_peak(pOther_layer_peak, pPeak->height_km);

  return (
    NEQUICKG_IONO_LAYER_GET_PEAK_AMPLITUDE(pPeak->electron_density) -
    other_layer_contribution);
}

void iono_profile_get_peak_amplitudes(
  iono_profile_t * const pProfile) {

  F2_layer_get_peak_amplitude(&pProfile->F2);

  peak_t* const pE_peak = &pProfile->E.layer.peak;
  peak_t* const pF1_peak = &pProfile->F1.peak;
  peak_t* const pF2_peak = &pProfile->F2.layer.peak;

  double_t E_peak_amplitude_substracting_F2 =
    iono_profile_get_peak_amp_substracting_layer(pE_peak, pF2_peak);

  if (NEQUICK_G_F1_LAYER_IS_PEAK_PRESENT(pProfile->F1)) {

    double_t F1_peak_amplitude_substracting_F2 =
      iono_profile_get_peak_amp_substracting_layer(pF1_peak, pF2_peak);

    pE_peak->amplitude =
        NEQUICKG_IONO_LAYER_GET_PEAK_AMPLITUDE(pE_peak->electron_density);

    for (
      size_t i = 0; i < NEQUICK_G_JRC_IONO_PEAK_AMPLITUDE_ITERATION_COUNT; i++) {

      // F1
      {
        double_t amplitude_E_at_F1_height =
        iono_profile_get_amplitude_of_peak(pE_peak, pF1_peak->height_km);

        pF1_peak->amplitude =
          F1_peak_amplitude_substracting_F2 -
          amplitude_E_at_F1_height;

        pF1_peak->amplitude =
          NeQuickG_func_join(
            pF1_peak->amplitude,
            NEQUICK_G_JRC_IONO_F1_LAYER_AMPLITUDE_CONSTANT *
            pF1_peak->electron_density,
            1.0,
            pF1_peak->amplitude -
            (NEQUICK_G_JRC_IONO_F1_LAYER_AMPLITUDE_CONSTANT *
             pF1_peak->electron_density));
      }

      // E
      pE_peak->amplitude =
        E_peak_amplitude_substracting_F2 -
        iono_profile_get_amplitude_of_peak(pF1_peak, pE_peak->height_km);
    }
  } else {
    pF1_peak->amplitude = 0.0;
    pE_peak->amplitude = E_peak_amplitude_substracting_F2;
  }

  pE_peak->amplitude =
    NeQuickG_func_join(
      pE_peak->amplitude,
      NEQUICK_G_JRC_IONO_E_LAYER_AMPLITUDE_CONSTANT_1,
      NEQUICK_G_JRC_IONO_E_LAYER_AMPLITUDE_WITH_TRANSITION_REGION,
      pE_peak->amplitude -
      NEQUICK_G_JRC_IONO_E_LAYER_AMPLITUDE_CONSTANT_2);
}

void iono_profile_get_peaks(iono_profile_t * const pProfile) {

  iono_profile_get_peak_heights(pProfile);

  iono_profile_get_peak_thicknesses(pProfile);

  iono_profile_get_peak_amplitudes(pProfile);
}

void iono_profile_get_exosphere_contribution(
  iono_profile_t * const pProfile,
  const NeQuickG_time_t* const pTime,
  const solar_activity_t* const pSolar_activity) {

  F2_layer_exosphere_adjust(
    &pProfile->F2,
    pTime,
    pSolar_activity);
}

int32_t iono_profile_get(
  iono_profile_t * const pProfile,
  const NeQuickG_time_t* const pTime,
  modip_context_t* const pModip,
  const solar_activity_t* const pSolar_activity,
  const position_t * const pCurrent_position) {

  modip_get(pModip, pCurrent_position);

  int32_t ret = iono_profile_get_critical_freqs(
    pProfile,
    pTime,
    pModip,
    pSolar_activity,
    pCurrent_position);
  if (ret != NEQUICK_OK) {
    return ret;
  }

  iono_profile_get_peaks(pProfile);

  iono_profile_get_exosphere_contribution(
    pProfile,
    pTime,
    pSolar_activity);

  return NEQUICK_OK;
}

double_t NeQuickG_exp(double_t power) {

  double_t result;

  if (power > NEQUICKG_EXP_MAX_ABS) {
    result = NEQUICKG_EXP_MAX_VALUE;
  } else if (power < -NEQUICKG_EXP_MAX_ABS) {
    result = NEQUICKG_EXP_MIN_VALUE;
  } else {
    result = exp(power);
  }
  return result;
}

double_t NeQuickG_func_join(
  double_t func1,
  double_t func2,
  double_t alpha,
  double_t x) {

  double_t temp = NeQuickG_exp(alpha * x);
  return(((func1 * temp) + func2) /
          (temp + 1.0));
}

void NeQuickG_get_power_array(
  size_t grade,
  double_t first_term,
  double_t negligible_value,
  double_t* const p) {
  p[0] = first_term;
  for (size_t i = 1; i < grade; i++) {
    double_t term = p[i - 1] * p[0];
    if (fabs(term) <= negligible_value) {
      term = 0.0;
    }
    p[i] = term;
  }
}

double_t NeQuickG_square(double_t val) {
  return (val * val);
}

double_t get_cos_from_sin(const double_t sin_rad) {
  return sqrt(1.0 - sin_rad * sin_rad);
}

double_t get_sin_from_cos(const double_t cos_rad) {
  return sqrt(1.0 - cos_rad * cos_rad);
}

/**
 * Note that the latitude should be between +- 90 degrees.
 * The extreme cases where the latitude is 90 degrees or -90
 * degrees are processed seperately as follows:
 * If latitude is 90 degrees, modip = 90
 * If latitude is -90 degrees, modip = -90
*/
bool handle_special_lat_cases(
  modip_context_t* const pContext,
  const position_t* const pPosition) {
  if (pPosition->latitude.degree <=
      NEQUICK_G_JRC_LAT_MIN_VALUE_DEGREE) {
    pContext->modip_degree = NEQUICK_G_JRC_LAT_MIN_VALUE_DEGREE;
    return true;
  } else if (pPosition->latitude.degree >=
      NEQUICK_G_JRC_LAT_MAX_VALUE_DEGREE) {
    pContext->modip_degree = NEQUICK_G_JRC_LAT_MAX_VALUE_DEGREE;
    return true;
  } else {
    return false;
  }
}

void modip_get(
  modip_context_t* const pContext,
  const position_t* const pPosition) {

  // Special cases: set modip and return.
  if (handle_special_lat_cases(pContext, pPosition)) {
    return;
  }

  // otherwise interpolate using the grid
  modip_grid_interpolate(pPosition, &pContext->modip_degree);
}


/** TBD: in the ESA version this uses a while
 * so any value is finally corrected.
 */
void grid_long_fix_index(
  grid_position_t * const pGrid_position, int8_t index) {
  if (index < 0) {
    assert(index > NEQUICK_G_JRC_MODIP_GRID_LONG_UNIQUE_COUNT);
    pGrid_position->index = (uint8_t)(index +
      NEQUICK_G_JRC_MODIP_GRID_LONG_UNIQUE_COUNT);
  } else if (index >=
      NEQUICK_G_JRC_MODIP_GRID_LONG_UNIQUE_COUNT) {
    pGrid_position->index = (uint8_t)(index -
      NEQUICK_G_JRC_MODIP_GRID_LONG_UNIQUE_COUNT);
  } else {
    pGrid_position->index = (uint8_t)index;
  }
}

void grid_get_long_position(
  double_t longitude_degree,
  grid_position_t * const pGrid_position) {

  double_t index_with_offset =
    (longitude_degree + NEQUICK_G_JRC_LONG_MAX_VALUE_DEGREE) /
    NEQUICK_G_JRC_MODIP_GRID_LONG_STEP_DEGREE;

  double_t _index = floor(index_with_offset);
  pGrid_position->offset = (index_with_offset - _index);

  // and, if required, adjust for sign and wrap to grid
  grid_long_fix_index(pGrid_position, (int8_t)_index);
}

void grid_get_lat_position(
  double_t latitude_degree,
  grid_position_t * const pGrid_position) {

  double_t index_with_offset =
    (latitude_degree + NEQUICK_G_JRC_LAT_MAX_VALUE_DEGREE) /
    NEQUICK_G_JRC_MODIP_GRID_LAT_STEP_DEGREE;

  assert(index_with_offset > 0.0);
  double_t _index =
    floor(index_with_offset -
                   NEQUICK_G_JRC_MODIP_GRID_LAT_OFFSET_CORRECTION);
  pGrid_position->index = (uint8_t)_index;
  pGrid_position->offset = (index_with_offset - pGrid_position->index);
}

/**
 * Interpolate across lat grid
 */
double_t grid_get_lon_interpol_point(
  const grid_position_t* const pLatitude,
  uint_fast8_t longitude_grid_index) {
  double_t
    lat_interpol_points[NEQUICK_G_JRC_INTERPOLATE_POINT_COUNT];
  size_t lat_grid_index = pLatitude->index;
  for (size_t i = 0;
        i < NEQUICK_G_JRC_INTERPOLATE_POINT_COUNT; i++) {
    lat_interpol_points[i] =
      g_corrected_modip_degree
        [lat_grid_index++]
        [longitude_grid_index];
  }
  return interpolation_third_order(
    lat_interpol_points,
    pLatitude->offset);
}

double_t grid_2D_interpolation(
  grid_position_t* pLongitude,
  const grid_position_t* const pLatitude) {

  double_t
    lon_interpol_points[NEQUICK_G_JRC_INTERPOLATE_POINT_COUNT];

  for (size_t i = 0;
        i < NEQUICK_G_JRC_INTERPOLATE_POINT_COUNT; i++) {
    lon_interpol_points[i] = grid_get_lon_interpol_point(
                              pLatitude, pLongitude->index++);
  }
  return interpolation_third_order(
    lon_interpol_points,
    pLongitude->offset);
}

void modip_grid_interpolate(
  const position_t* const pPosition,
  double_t *pModip_degree) {

  *pModip_degree = 0;

  // Obtain grid <index, offset> for longitude
  grid_position_t longitude;
  grid_get_long_position(pPosition->longitude.degree, &longitude);

  // Obtain grid <index, offset> for latitude
  grid_position_t latitude;
  grid_get_lat_position(pPosition->latitude.degree, &latitude);

  *pModip_degree = grid_2D_interpolation(&longitude, &latitude);
}

angle_restricted_t get_longitude_delta_angle(
  const position_t* const pStation_position,
  const position_t* const pSatellite_position) {

  double_t longitude_delta_rad =
    (pSatellite_position->longitude.rad -
     pStation_position->longitude.rad);

  angle_restricted_t longitude_delta;
  angle_restricted_set(&longitude_delta, longitude_delta_rad);
  return longitude_delta;
}

angle_restricted_t get_delta_angle(
  const position_t* const pStation_position,
  const position_t* const pSatellite_position,
  const angle_restricted_t* const pLongitude_delta) {

  angle_restricted_t delta;

  delta.cos =
    (pStation_position->latitude.sin *
     pSatellite_position->latitude.sin) +
    (pStation_position->latitude.cos *
      pSatellite_position->latitude.cos *
      pLongitude_delta->cos);

  delta.sin = get_sin_from_cos(delta.cos);

  return delta;
}

angle_restricted_t get_sigma_angle(
  const position_t* const pStation_position,
  const position_t* const pSatellite_position,
  const angle_restricted_t* const pLongitude_delta,
  const angle_restricted_t* const pDelta) {

  angle_restricted_t sigma;
  sigma.sin =
    (pLongitude_delta->sin * pSatellite_position->latitude.cos) /
    pDelta->sin;

  sigma.cos =
    ((pSatellite_position->latitude.sin -
     (pDelta->cos * pStation_position->latitude.sin)) / pDelta->sin) /
    pStation_position->latitude.cos;

  return sigma;
}

angle_t get_zenith_angle(
  const position_t* const pStation_position,
  const position_t* const pSatellite_position,
  const angle_restricted_t* const pDelta) {

  angle_t zenith;

  zenith.rad = atan2(pDelta->sin, pDelta->cos - (
    pStation_position->radius_km /
    pSatellite_position->radius_km));

  zenith.sin = sin(zenith.rad);
  zenith.degree = NEQUICKG_JRC_RAD_TO_DEGREE(zenith.rad);

  return zenith;
}

angle_restricted_t get_delta_p_angle(const angle_t* const pZenith) {

  double_t delta_p_angle_rad =
    NEQUICKG_JRC_DEGREE_TO_RAD(90.0) - pZenith->rad;

  angle_restricted_t delta_p;
  angle_restricted_set(&delta_p, delta_p_angle_rad);
  return delta_p;
}

/** Calculate ray perigee latitude */
angle_t get_ray_latitude(
  const position_t* const pStation_position,
  const angle_restricted_t* const pSigma,
  const angle_restricted_t* const pDelta_p) {

  angle_t latitude;
  latitude.sin =
    (pStation_position->latitude.sin * pDelta_p->cos) -
    (pStation_position->latitude.cos * pDelta_p->sin * pSigma->cos);

  angle_set_fom_sin(&latitude);
  return latitude;
}

/** Calculate ray perigee longitude */
angle_t get_ray_longitude(
  const position_t* const pStation_position,
  const angle_restricted_t* const pSigma,
  const angle_restricted_t* const pDelta_p,
  const angle_t* const pRay_latitude) {

  angle_t longitude;

  double_t sin_lamp = (-pSigma->sin * pDelta_p->sin) / pRay_latitude->cos;

  double_t cos_lamp = (
    (pDelta_p->cos - (pStation_position->latitude.sin * pRay_latitude->sin)) /
     pStation_position->latitude.cos) / pRay_latitude->cos;

  longitude.rad =
    atan2(sin_lamp, cos_lamp) + pStation_position->longitude.rad;
  longitude.degree = NEQUICKG_JRC_RAD_TO_DEGREE(longitude.rad);

  return longitude;
}

int32_t ray_get_radius(
  ray_context_t* const pRay,
  const position_t* const pStation_position,
  const angle_t* const pZenith_angle) {

  pRay->slant.perigee_radius_km = pStation_position->radius_km * pZenith_angle->sin;

  if ((fabs(pZenith_angle->rad) >
      NEQUICKG_JRC_DEGREE_TO_RAD(NEQUICKG_JRC_RAY_ZENITH_ANGLE_MAX_DEGREE))
      &&
      !position_is_exterior(pRay->slant.perigee_radius_km)) {
    NEQUICK_ERROR_RETURN(
      NEQUICK_RAY_EXCEPTION,
      NEQUICK_RAY_BAD,
      "the ray is not correct, angle(rad) = %lf, slant perigee radius (km) = %lf",
       pZenith_angle->rad, pRay->slant.perigee_radius_km);
  }

  pRay->is_vertical =
    (pRay->slant.perigee_radius_km <
      NEQUICKG_JRC_RAY_IS_VERTICAL_PERIGEE_EPSILON_KM);

  return NEQUICK_OK;
}

bool is_at_poles(const ray_context_t* const pRay) {
  return (
    fabs(
      fabs(pRay->latitude.degree) - NEQUICK_G_JRC_LAT_MAX_VALUE_DEGREE) <
        NEQUICKG_JRC_RAY_IS_AT_POLE_EPSILON);
}

void get_azimuth(ray_context_t* const pRay) {

  // Check if latitude of lower end point is +-90 degrees.
  // it would cause divide by zero error later on
  if (is_at_poles(pRay)) {
    pRay->slant.azimuth.sin = 0.0;
    pRay->slant.azimuth.cos =
      (pRay->latitude.degree > 0) ?
      -1.0 : 1.0;
  } else {
    // Calculate difference in longitude of ray end points
    double_t delta_rad =
      (pRay->satellite_position.longitude.rad -
       pRay->longitude.rad);

    // Calculate sine and cosine of angular distance between ends of ray (psi)
    angle_restricted_t psi_angle;
    {
      psi_angle.cos =
         (pRay->latitude.sin * pRay->satellite_position.latitude.sin) +
         pRay->latitude.cos * pRay->satellite_position.latitude.cos *
         cos(delta_rad);
      psi_angle.sin = get_sin_from_cos(psi_angle.cos);
    }

    pRay->slant.azimuth.sin =
      (pRay->satellite_position.latitude.cos * sin(delta_rad)) /
      psi_angle.sin;

    pRay->slant.azimuth.cos =
      (pRay->satellite_position.latitude.sin -
      (pRay->latitude.sin * psi_angle.cos)) /
        (psi_angle.sin * pRay->latitude.cos);
  }
}

/** Set the ray latitude and longitude to be the same as receiver
 *  Set satellite longitude to be exactly the same as station longitude
 */
void on_vertical_ray(ray_context_t* const pRay) {

  pRay->satellite_position.longitude = pRay->receiver_position.longitude;

  pRay->latitude = pRay->receiver_position.latitude;
  pRay->longitude = pRay->receiver_position.longitude;
}

int32_t on_slant_ray(ray_context_t* const pRay) {

  int32_t ret;

  angle_restricted_t longitude_delta =
    get_longitude_delta_angle(
      &pRay->receiver_position,
      &pRay->satellite_position);

  angle_restricted_t delta =
    get_delta_angle(
      &pRay->receiver_position,
      &pRay->satellite_position,
      &longitude_delta);

  // zenith angle of satellite, seen from receiver
  angle_t zenith_angle =
    get_zenith_angle(
      &pRay->receiver_position,
      &pRay->satellite_position,
      &delta);

  ret = ray_get_radius(pRay, &pRay->receiver_position, &zenith_angle);
  if (ret != NEQUICK_OK) {
    return ret;
  }

  angle_restricted_t sigma =
    get_sigma_angle(
      &pRay->receiver_position,
      &pRay->satellite_position,
      &longitude_delta,
      &delta);

  angle_restricted_t delta_p = get_delta_p_angle(&zenith_angle);

  pRay->latitude = get_ray_latitude
    (&pRay->receiver_position, &sigma, &delta_p);

  pRay->longitude = get_ray_longitude
    (&pRay->receiver_position, &sigma, &delta_p, &pRay->latitude);

  if (!pRay->is_vertical) {
    {
      // Replace sine and cosine of receiver end point
      // using ray perigee latitude for receiver
      pRay->receiver_position.latitude.sin = pRay->latitude.sin;
      pRay->receiver_position.latitude.cos = pRay->latitude.cos;
    }
    get_azimuth(pRay);

    pRay->slant.receiver_distance_km =
    get_slant_distance(pRay, pRay->receiver_position.radius_km);

    pRay->slant.satellite_distance_km =
      get_slant_distance(pRay, pRay->satellite_position.radius_km);
  }
  return NEQUICK_OK;
}

double_t get_slant_distance(
  const ray_context_t* const pRay,
  double_t radius_km) {
  double_t temp =
    NeQuickG_square(radius_km) -
    NeQuickG_square(pRay->slant.perigee_radius_km);
  return sqrt(fabs(temp));
}

int32_t ray_get(
  ray_context_t* const pRay,
  const position_t * const pStation_position,
  const position_t * const pSatellite_position) {

  pRay->receiver_position = *pStation_position;
  pRay->satellite_position = *pSatellite_position;

  pRay->is_vertical =
    position_is_above(pStation_position, pSatellite_position);

  // Check if ray is vertical
  if (pRay->is_vertical) {

    on_vertical_ray(pRay);
    return NEQUICK_OK;

  } else {

    return on_slant_ray(pRay);

  }
}


angle_restricted_t ray_get_delta_angle(
  const ray_context_t* const pRay,
  const double_t height_km) {

  angle_restricted_t delta;

  double_t tangent_delta = height_km / pRay->slant.perigee_radius_km;
  delta.cos = 1.0 / sqrt(1.0 + NeQuickG_square(tangent_delta));
  delta.sin = tangent_delta * delta.cos;

  return delta;
}

angle_t get_lambda_s_p_angle(
  const ray_context_t* const pRay,
  const angle_restricted_t* pDelta,
  const angle_t* pCurrent_position_latitude) {

  angle_t delta_lambda_s_p;

  delta_lambda_s_p.sin =
      pDelta->sin *
      pRay->slant.azimuth.sin *
      pRay->receiver_position.latitude.cos;

  delta_lambda_s_p.cos =
    pDelta->cos -
    (pRay->receiver_position.latitude.sin *
     pCurrent_position_latitude->sin);

  delta_lambda_s_p.rad =
    atan2(delta_lambda_s_p.sin,
          delta_lambda_s_p.cos);

  return delta_lambda_s_p;
}

position_t get_current_position(
  const ray_context_t* const pRay,
  const double_t height_km) {
  position_t current_position;

  current_position.radius_km =
    sqrt(NeQuickG_square(height_km) + NeQuickG_square(pRay->slant.perigee_radius_km));

  current_position.height =
    get_height_from_radius(current_position.radius_km);

  angle_restricted_t delta = ray_get_delta_angle(pRay, height_km);

  // latitude
  {
    current_position.latitude.sin =
      (pRay->receiver_position.latitude.sin * delta.cos) +
      (pRay->receiver_position.latitude.cos * delta.sin * pRay->slant.azimuth.cos);

    angle_set_fom_sin(&current_position.latitude);
  }

  // longitude
  {
    angle_t delta_lambda_s_p =
      get_lambda_s_p_angle(
        pRay,
        &delta,
        &current_position.latitude);

    angle_set_rad(
      &current_position.longitude,
      delta_lambda_s_p.rad + pRay->longitude.rad);
  }

  return current_position;
}

int32_t ray_slant_get_electron_density(
  NeQuickG_context_t* const pContext,
  const double_t height_km,
  double_t* const pElectron_density) {

  position_t current_position =
    get_current_position(&pContext->ray, height_km);

  int32_t ret = iono_profile_get(
    &pContext->profile,
    &pContext->input_data.time,
    &pContext->modip,
    &pContext->solar_activity,
    &current_position);

  if (ret != NEQUICK_OK) {
    return ret;
  }

  *pElectron_density = electron_density_get(
    &pContext->profile,
    current_position.height);

  return NEQUICK_OK;
}

position_t ray_vertical_get_current_position(const ray_context_t* const pRay) {
  position_t current_position;

  current_position.latitude = pRay->receiver_position.latitude;
  current_position.longitude = pRay->receiver_position.longitude;

  // not used for profile...
  current_position.height = pRay->satellite_position.height;
  current_position.height_units = pRay->satellite_position.height_units;

  return current_position;
}

int32_t ray_vertical_get_profile(NeQuickG_context_t* const pContext) {

  position_t current_position = ray_vertical_get_current_position(&pContext->ray);

  return iono_profile_get(
    &pContext->profile,
    &pContext->input_data.time,
    &pContext->modip,
    &pContext->solar_activity,
    &current_position);
}

double_t ray_vertical_get_electron_density(
  NeQuickG_context_t* const pContext,
  const double_t height_km) {
  return electron_density_get(&pContext->profile, height_km);
}

double_t get_mean_anomaly(
  double_t time_days) {
  return NEQUICKG_JRC_DEGREE_TO_RAD(
           NEQUICK_G_JRC_SOLAR_MEAN_ANOMALY_DEGREE_PER_DAY * time_days +
            NEQUICK_G_JRC_SOLAR_MEAN_ANOMALY_OFFSET_DEGREE);
}

/** The ecliptic longitude of the Sun is:
 *  L + 1.916sin(g) + 0.020sin(2g) where
 *   L is the mean longitude of the Sun
 *   L = 280.460 + 0.9856*n
 * and g is the mean anomaly of the Sun
 *   g = 357.528 + 0.9856*n
 *
 *   where n is the number of days (positive or negative)
 *    since Greenwich noon, Terrestrial Time,
 *    on 1 January 2000 (J2000.0).
 *
 */
double_t get_ecliptic_longitude(
  double_t time_days) {

  double_t mean_anomaly_rad = get_mean_anomaly(time_days);

  double_t ecliptic_longitude_rad =
   (mean_anomaly_rad +
    NEQUICK_G_JRC_SOLAR_ECLIPTIC_ZERO_COEFF_DEGREE);

  ecliptic_longitude_rad +=
    NEQUICK_G_JRC_SOLAR_ECLIPTIC_FIRST_COEFF_DEGREE *
       sin(mean_anomaly_rad);

  ecliptic_longitude_rad +=
    NEQUICK_G_JRC_SOLAR_ECLIPTIC_SECOND_COEFF_DEGREE *
       sin(2 * mean_anomaly_rad);

  return ecliptic_longitude_rad;
}

/** The Sun's declination at any given moment is calculated by:
 * sin(declination_sun) = sin(-23.44)sin(ecliptic_long)
 * where ecliptic_long is the ecliptic longitude.
 */
angle_restricted_t
solar_get_declination(const NeQuickG_time_t * const pTime) {

  double_t day_of_year = NeQuickG_time_get_day_of_year(pTime);

  double_t ecliptic_longitude_rad = get_ecliptic_longitude(day_of_year);

  angle_restricted_t solar_declination;
  {
    solar_declination.sin = NEQUICK_G_JRC_SOLAR_SIN_EARTH_AXIAL_TILT *
                              sin(ecliptic_longitude_rad);
    solar_declination.cos = get_cos_from_sin(solar_declination.sin);
  }
  return solar_declination;
}

/** The solar hour angle is an expression of time,
 *  expressed in angular measurement,
 *  from solar noon.
 *  At solar noon the hour angle is 0 degree,
 *  with the time before solar noon expressed as negative degrees,
 *  and the local time after solar noon expressed as positive degrees.
 */
double_t get_cosinus_hour_angle(
  const NeQuickG_time_t * const pTime,
  const position_t* const pPosition) {

  double_t local_time =
    NeQuickG_time_get_local(pTime, pPosition->longitude.degree);

  return cos((NEQUICK_G_JRC_PI *
     (NEQUICK_G_JRC_TIME_HALF_DAY_IN_HOURS - local_time)) /
      NEQUICK_G_JRC_TIME_HALF_DAY_IN_HOURS);
}

/** Compute solar zenith angle chi [deg] for the given location.
 * The solar zenith angle is the angle between the zenith and the centre
 * of the Sun's disc
 * cosinus_angle = sin(local_latitude)*sin(declination_sun) +
 *                 cos(local_latitude)*cos(declination_sun)*cos(hour_angle)
 */
angle_t solar_get_zenith_angle(
  const position_t* const pPosition,
  const NeQuickG_time_t* const pTime,
  const angle_restricted_t* const pSolar_declination) {

  angle_t zenith;
  zenith.cos =
    (pPosition->latitude.sin * pSolar_declination->sin) +
      (pPosition->latitude.cos * pSolar_declination->cos *
        get_cosinus_hour_angle(pTime, pPosition));

  angle_set_fom_cos(&zenith);
  return zenith;
}

double_t solar_get_effective_zenith_angle(
  const position_t* const pPosition,
  const NeQuickG_time_t * const pTime,
  const angle_restricted_t* const pSolar_declination) {

  angle_t zenith_angle =
    solar_get_zenith_angle(pPosition, pTime, pSolar_declination);

  double_t func1 =
    NEQUICK_G_JRC_SOLAR_EFFECTIVE_ZENITH_CONST1 -
    NEQUICK_G_JRC_SOLAR_EFFECTIVE_ZENITH_CONST2 *
    NeQuickG_exp(NEQUICK_G_JRC_SOLAR_EFFECTIVE_ZENITH_CONST3 -
                (NEQUICK_G_JRC_SOLAR_EFFECTIVE_ZENITH_CONST4 *
                 zenith_angle.degree));

  return NeQuickG_func_join(
    func1,
    zenith_angle.degree,
    NEQUICK_G_JRC_SOLAR_EFFECTIVE_ZENITH_CONST5,
    zenith_angle.degree -
      NEQUICK_G_JRC_SOLAR_ZENITH_ANGLE_AT_DAY_NIGHT_TRANSITION_DEGREE);
}

double_t solar_get_longitude(
  const NeQuickG_time_t* const pTime) {
  return (
    NEQUICKG_JRC_DEGREE_TO_RAD(
      NEQUICK_G_JRC_TIME_DEGREE_PER_HOUR*pTime->utc -
      NEQUICK_G_JRC_LONG_MAX_VALUE_DEGREE));
}


/**
 * 3.1. Zero-valued coefficients and default Effective Ionisation Level
 *   When all the Effective Ionisation Level ionospheric broadcast
 *   coefficients are set to zero:
 *    ai0 = ai1 = ai2 = 0
 *   the coefficients shall NOT be used for single-frequency ionospheric
 *   correction.
 */
bool are_valid(const AZ_coefficients_t* const pCoeff) {
  for (size_t i = 0; i < NEQUICKG_AZ_COEFFICIENTS_COUNT; i++) {
    if (!NEQUICK_G_IONO_COEFF_IS_ZERO(pCoeff->a_sfu[i])) {
      return true;
    }
  }
  return false;
}

/**
 * 3.3 Effective Ionisation Level boundaries:
 * Due to the fact that the Effective Ionisation Level is represented simply
 * by a second-order degree polynomial as a function of MODIP, it may
 * exceptionally happen that for some MODIP values, the Effective Ionisation
 * Parameter becomes out of range.
 * The operational range for the Effective Ionisation Parameter is between 0
 * and 400 sfu and the following condition for out of range values should be
 * used:
 * if AZ < 0 ==> Az = 0
 * if AZ > 400 ==> Az = 400
 */
void check_boundaries(
  double_t* const pAz) {
  if (*pAz < NEQUICK_G_AZ_MIN_VALUE_SFU) {
    *pAz = NEQUICK_G_AZ_MIN_VALUE_SFU;
  } else if (*pAz > NEQUICK_G_AZ_MAX_VALUE_SFU) {
    *pAz = NEQUICK_G_AZ_MAX_VALUE_SFU;
  }
}

/**
 * Calculate Effective Ionisation Level:
 * Az = ai0 + ai1.mu + ai2*mu^2
 */
double_t Az_calc(
  const AZ_coefficients_t* const pCoeff,
  double_t modip) {
  double_t Az = 0.0;
  double_t term = 1.0;
  for (size_t i = 0; i < NEQUICKG_AZ_COEFFICIENTS_COUNT; i++) {
    Az += pCoeff->a_sfu[i]*term;
    term *= modip;
  }
  return Az;
}

double_t solar_activity_get_effective_ionisation_level_in_sfu(
  const AZ_coefficients_t* const pCoeff,
  double_t modip) {
  if (!are_valid(pCoeff)) {
    /**
     *   In those cases, a default value shall be used for correction in
     *   the receiver:
     *   ai0 = NEQUICK_G_AZ_DEFAULT_VALUE; ai1 = ai2 = 0
     */
    return NEQUICK_G_AZ_DEFAULT_VALUE_SFU;
  }

  {
    double_t Az = Az_calc(pCoeff, modip);
    check_boundaries(&Az);
    return Az;
  }
}

bool solar_activity_is_effective_ionisation_level_equal(
  double_t op1,
  double_t op2) {
  return IS_NUMBER_CLOSE_TO(op1, op2,
          NEQUICK_G_AZ_EQUALITY_EPSILON);
}

int32_t solar_activity_coefficients_set (
  solar_activity_t* const pContext,
  const double_t * const pCoeff,
  size_t coeff_count) {
  if ((pCoeff == NULL) ||
      (coeff_count < NEQUICKG_AZ_COEFFICIENTS_COUNT)) {
    NEQUICK_ERROR_RETURN(
      NEQUICK_SOLAR_ACTIVITY_EXCEPTION,
      NEQUICK_SOLAR_ACTIVITY_BAD_COEFF,
      "Az coefficients not valid (null pointer or fewer than 3 coefficients)");
  }
  // to satisfy lint
  assert(pCoeff);
  pContext->effective_ionisation_level_coeff.a_sfu[0] = pCoeff[0];
  pContext->effective_ionisation_level_coeff.a_sfu[1] = pCoeff[1];
  pContext->effective_ionisation_level_coeff.a_sfu[2] = pCoeff[2];
  return NEQUICK_OK;
}

void solar_activity_get(
  solar_activity_t* const pContext,
  double_t modip_degree) {

  pContext->effective_ionisation_level_sfu =
    solar_activity_get_effective_ionisation_level_in_sfu(
    &pContext->effective_ionisation_level_coeff,
    modip_degree);

  pContext->effective_sun_spot_count =
    NeQuickG_Az_solar_activity_get_sun_spot_effective_count(
      pContext->effective_ionisation_level_sfu);
}

double_t get_point_height(
  const NeQuickG_context_t* const pContext,
  double_t height_km) {
  if (pContext->ray.is_vertical) {
    return height_km;
  } else {
     return get_slant_distance(
      &pContext->ray,
      get_radius_from_height(height_km));
  }
}

double_t get_point_zero_height(
  const NeQuickG_context_t* const pContext) {
  double_t temp = max(0.0, pContext->input_data.station_position.height);
  return get_point_height(pContext, temp);
}

int32_t Gauss_Kronrod_integrate_impl(
  gauss_kronrod_context_t* const pContext,
  NeQuickG_context_t* const pNequick_Context,
  const double_t point_1_height_km,
  const double_t point_2_height_km,
  double_t* const pTEC) {

  pContext->recursion_level = 0;
  pContext->recursion_max = NEQUICK_G_JRC_RECURSION_LIMIT_MAX;

  return Gauss_Kronrod_integrate(
    pContext,
    pNequick_Context,
    point_1_height_km,
    point_2_height_km,
    pTEC);
}

int32_t both_below_first_integration_point(
  NeQuickG_context_t* const pContext,
  double_t* const pTEC) {

  gauss_kronrod_context_t gauss_kronrod_context;
  gauss_kronrod_context.tolerance =
   NEQUICK_G_JRC_INTEGRATION_KRONROD_TOLERANCE_BELOW_FIRST_POINT;

  double_t zero_point_height_km = get_point_zero_height(pContext);

  double_t second_point_height_km =
    pContext->ray.is_vertical ?
      pContext->ray.satellite_position.height :
      pContext->ray.slant.satellite_distance_km;

  // integrate straight between P0 and P2 for TEC.
  // P0 is used because P1 could be less than zero
  return Gauss_Kronrod_integrate_impl(
    &gauss_kronrod_context,
    pContext,
    zero_point_height_km,
    second_point_height_km,
    pTEC);
}

int32_t between_integration_points(
  NeQuickG_context_t* const pContext,
  double_t* const pTEC) {

  gauss_kronrod_context_t gauss_kronrod_context;
  gauss_kronrod_context.tolerance =
   NEQUICK_G_JRC_INTEGRATION_KRONROD_TOLERANCE_BELOW_FIRST_POINT;

  double_t first_point_height_km =
    pContext->ray.is_vertical ?
      pContext->ray.receiver_position.height :
      pContext->ray.slant.receiver_distance_km;

  double_t second_point_height_km =
    pContext->ray.is_vertical ?
      pContext->ray.satellite_position.height :
      pContext->ray.slant.satellite_distance_km;

  // P1 and P2 are between the two integration breakpoints
  // integrate straight between P1 and P2
  return Gauss_Kronrod_integrate_impl(
    &gauss_kronrod_context,
    pContext,
    first_point_height_km,
    second_point_height_km,
    pTEC);
}

int32_t path_crosses_first_integration_point(
  NeQuickG_context_t* const pContext,
  double_t* const pTEC) {

  int32_t ret;
  // Path between P1 and P2 crosses the first integration breakpoint
  // integrate between P0 and the first breakpoint and from the
  // first breakpoint to P2.
  // P0 is used because P1 could be less than zero.

  double_t total_electron_content;

  gauss_kronrod_context_t gauss_kronrod_context;

  double_t first_integration_point_height_km =
    get_point_height(pContext, NEQUICK_G_JRC_INTEGRATION_FIRST_POINT_KM);

  {
    double_t zero_point_height_km = get_point_zero_height(pContext);

    gauss_kronrod_context.tolerance =
      NEQUICK_G_JRC_INTEGRATION_KRONROD_TOLERANCE_BELOW_FIRST_POINT;

     ret =
      Gauss_Kronrod_integrate_impl(
        &gauss_kronrod_context,
        pContext,
        zero_point_height_km,
        first_integration_point_height_km,
        &total_electron_content);
     if (ret != NEQUICK_OK) {
       return ret;
     }
  }

  {
    double_t second_point_height_km =
    pContext->ray.is_vertical ?
      pContext->ray.satellite_position.height :
      pContext->ray.slant.satellite_distance_km;

    gauss_kronrod_context.tolerance =
      NEQUICK_G_JRC_INTEGRATION_KRONROD_TOLERANCE_ABOVE_FIRST_POINT;

      double_t total_electron_content_;
      ret =
        Gauss_Kronrod_integrate_impl(
          &gauss_kronrod_context,
          pContext,
          first_integration_point_height_km,
          second_point_height_km,
          &total_electron_content_);
      if (ret != NEQUICK_OK) {
        return ret;
      }

      total_electron_content += total_electron_content_;
  }

  *pTEC = total_electron_content;
  return NEQUICK_OK;
}

int32_t path_crosses_second_integration_point(
  NeQuickG_context_t* const pContext,
  double_t* const pTEC) {

  int32_t ret;

  // Path between P1 and P2 crosses the second integration
  // breakpoint so integrate between P1 and the second breakpoint
  // and from the second breakpoint to P2

  double_t total_electron_content;

  gauss_kronrod_context_t gauss_kronrod_context;
  gauss_kronrod_context.tolerance =
      NEQUICK_G_JRC_INTEGRATION_KRONROD_TOLERANCE_ABOVE_FIRST_POINT;

  double_t second_integration_point_height_km =
    get_point_height(pContext, NEQUICK_G_JRC_INTEGRATION_SECOND_POINT_KM);

  {
    double_t first_point_height_km =
    pContext->ray.is_vertical ?
      pContext->ray.receiver_position.height :
      pContext->ray.slant.receiver_distance_km;

     ret =
      Gauss_Kronrod_integrate_impl(
        &gauss_kronrod_context,
        pContext,
        first_point_height_km,
        second_integration_point_height_km,
        &total_electron_content);
      if (ret != NEQUICK_OK) {
        return ret;
      }
  }

  {
    double_t second_point_height_km =
    pContext->ray.is_vertical ?
      pContext->ray.satellite_position.height :
      pContext->ray.slant.satellite_distance_km;

      double_t total_electron_content_;
      ret =
        Gauss_Kronrod_integrate_impl(
          &gauss_kronrod_context,
          pContext,
          second_integration_point_height_km,
          second_point_height_km,
          &total_electron_content_);
      if (ret != NEQUICK_OK) {
        return ret;
      }
      total_electron_content += total_electron_content_;
   }

  *pTEC = total_electron_content;
  return NEQUICK_OK;
}

int32_t both_above_second_integration_point(
  NeQuickG_context_t* const pContext,
  double_t* const pTEC) {

  // P1 and P2 are both above the second integration breakpoint so
  // integrate straight between P1 and P2

  double_t first_point_height_km =
    pContext->ray.is_vertical ?
      pContext->ray.receiver_position.height :
      pContext->ray.slant.receiver_distance_km;

  double_t second_point_height_km =
    pContext->ray.is_vertical ?
      pContext->ray.satellite_position.height :
      pContext->ray.slant.satellite_distance_km;

  gauss_kronrod_context_t gauss_kronrod_context;
  gauss_kronrod_context.tolerance =
   NEQUICK_G_JRC_INTEGRATION_KRONROD_TOLERANCE_ABOVE_FIRST_POINT;

  return Gauss_Kronrod_integrate_impl(
    &gauss_kronrod_context,
    pContext,
    first_point_height_km,
    second_point_height_km,
    pTEC);
}

int32_t path_crosses_both_integration_points(
  NeQuickG_context_t* const pContext,
  double_t* const pTEC) {

  int32_t ret;

  // Path between P1 and P2 crosses both integration breakpoints
  // so integrate between P0 and the first breakpoint, between the
  // two breakpoints and from the second breakpoint to P2.
  // P0 is used because P1 could be less than zero.

  gauss_kronrod_context_t gauss_kronrod_context;
  double_t total_electron_content;

  double_t first_integration_point_height_km =
      get_point_height(pContext, NEQUICK_G_JRC_INTEGRATION_FIRST_POINT_KM);
  {
    double_t zero_point_height_km = get_point_zero_height(pContext);

    gauss_kronrod_context.tolerance =
      NEQUICK_G_JRC_INTEGRATION_KRONROD_TOLERANCE_BELOW_FIRST_POINT;

     ret =
      Gauss_Kronrod_integrate_impl(
        &gauss_kronrod_context,
        pContext,
        zero_point_height_km,
        first_integration_point_height_km,
        &total_electron_content);
     if (ret != NEQUICK_OK) {
        return ret;
     }
  }

  gauss_kronrod_context.tolerance =
      NEQUICK_G_JRC_INTEGRATION_KRONROD_TOLERANCE_ABOVE_FIRST_POINT;

  double_t second_integration_point_height_km =
   get_point_height(pContext, NEQUICK_G_JRC_INTEGRATION_SECOND_POINT_KM);

  {
    double_t total_electron_content_;
     ret =
      Gauss_Kronrod_integrate_impl(
        &gauss_kronrod_context,
        pContext,
        first_integration_point_height_km,
        second_integration_point_height_km,
        &total_electron_content_);
     if (ret != NEQUICK_OK) {
        return ret;
     }
     total_electron_content += total_electron_content_;
  }

  {
    double_t second_point_height_km =
    pContext->ray.is_vertical ?
      pContext->ray.satellite_position.height :
      pContext->ray.slant.satellite_distance_km;

    double_t total_electron_content_;
    ret =
      Gauss_Kronrod_integrate_impl(
        &gauss_kronrod_context,
        pContext,
        second_integration_point_height_km,
        second_point_height_km,
        &total_electron_content_);
    if (ret != NEQUICK_OK) {
        return ret;
    }
    total_electron_content += total_electron_content_;
  }

  *pTEC = total_electron_content;
  return NEQUICK_OK;
}

int32_t NeQuickG_integrate(
  NeQuickG_context_t* const pContext,
  double_t* const pTEC) {

  int32_t ret;
  *pTEC = 0.0;

  if (pContext->ray.is_vertical) {
    ret = ray_vertical_get_profile(pContext);
    if (ret != NEQUICK_OK) {
      return ret;
    }
  }

  if (IS_SATELLITE_BELOW_FIRST_POINT(pContext)) {
    return both_below_first_integration_point(pContext, pTEC);
  }

  if (IS_SATELLITE_BELOW_SECOND_POINT(pContext)) {
    return IS_RECEIVER_ABOVE_FIRST_POINT(pContext) ?
      between_integration_points(pContext, pTEC) :
      path_crosses_first_integration_point(pContext, pTEC);
  }

  if (IS_RECEIVER_ABOVE_SECOND_POINT(pContext)) {
    return both_above_second_integration_point(pContext, pTEC);
  }

  if (IS_RECEIVER_ABOVE_FIRST_POINT(pContext)) {
    return path_crosses_second_integration_point(pContext, pTEC);
  }

  return path_crosses_both_integration_points(pContext, pTEC);
}

void NeQuickG_time_init(
  NeQuickG_time_t * const pTime) {
  pTime->month = 0;
  pTime->utc = 0x00;
}

int32_t NeQuickG_time_set(
  NeQuickG_time_t * const pTime,
  const uint_fast8_t month,
  const double_t utc) {

  if ((month < NEQUICK_G_JRC_MONTH_JANUARY) ||
      (month > NEQUICK_G_JRC_MONTH_DECEMBER)) {
    NEQUICK_ERROR_RETURN(
      NEQUICK_INPUT_DATA_EXCEPTION,
      NEQUICK_INPUT_DATA_BAD_MONTH,
      "Invalid month %u", month);
  }

  if ((utc < 0.0) ||
      (utc > NEQUICK_G_JRC_TIME_DAY_IN_HOURS)) {
    NEQUICK_ERROR_RETURN(
      NEQUICK_INPUT_DATA_EXCEPTION,
      NEQUICK_INPUT_DATA_BAD_UTC,
       "Invalid UTC %lf, must be between 0 and 24", utc);
  }

  pTime->month = month;
  pTime->utc = utc;
  return NEQUICK_OK;
}

bool NeQuickG_time_utc_is_equal(
  double_t op1,
  double_t op2) {
  return IS_NUMBER_CLOSE_TO(op1, op2, NEQUICK_G_JRC_TIME_UTC_EPSILON);
}

double_t NeQuickG_time_get_day_of_year(
  const NeQuickG_time_t * const pTime) {

  // compute day of year at the middle of the month.
  double_t day_of_year_at_middle_of_month =
    NEQUICK_G_JRC_TIME_AVG_MONTH_IN_DAYS*(double_t)pTime->month -
    NEQUICK_G_JRC_TIME_MID_MONTH_POINT_IN_DAYS;

  // compute time [days].
  double_t time_days = day_of_year_at_middle_of_month;
  time_days += (NEQUICK_G_JRC_TIME_CONSTANT_TO_COMPUTE_DAY - pTime->utc)
               / NEQUICK_G_JRC_TIME_DAY_IN_HOURS;
  return time_days;
}

double_t NeQuickG_time_get_local(
  const NeQuickG_time_t * const pTime,
  double_t longitude_degree) {
  double_t local_time = pTime->utc +
    (longitude_degree / NEQUICK_G_JRC_TIME_DEGREE_PER_HOUR);

  if (local_time < 0.0) {
    local_time += NEQUICK_G_JRC_TIME_DAY_IN_HOURS;
  } else if (local_time >= NEQUICK_G_JRC_TIME_DAY_IN_HOURS) {
    local_time -= NEQUICK_G_JRC_TIME_DAY_IN_HOURS;
  }
  return local_time;
}

void get_modip_impl(
  NeQuickG_context_t* const pContext) {

  input_data_to_km(&pContext->input_data);
  modip_get(&pContext->modip, &pContext->input_data.station_position);
}

double_t get_modip_interface(NeQuickG_handle handle) {
  NeQuickG_context_t* pContext = (NeQuickG_context_t*)(handle);
  get_modip_impl(pContext);
  return pContext->modip.modip_degree;
}

void get_solar_activity(
  NeQuickG_context_t* const pContext) {

  get_modip_impl(pContext);
  solar_activity_get(&pContext->solar_activity, pContext->modip.modip_degree);
}

int32_t check_handle(NeQuickG_chandle handle) {
  if (handle == NEQUICKG_INVALID_HANDLE) {
    NEQUICK_ERROR_RETURN(
      NEQUICK_FATAL_EXCEPTION,
      NEQUICK_HANDLE_NULL,
      "NULL handle");
  }
  return NEQUICK_OK;
}

int32_t init(NeQuickG_handle* const pHandle) {

  *pHandle = NEQUICKG_INVALID_HANDLE;

  *pHandle = malloc(sizeof(NeQuickG_context_t));
  if (*pHandle == NEQUICKG_INVALID_HANDLE) {
    NEQUICK_ERROR_RETURN(
      NEQUICK_MEMORY_EXPECTION,
      NEQUICK_NO_RESOURCES,
      "Not enough resources to allocate NeQuick context on the heap");
  }

  NeQuickG_context_t* pContext = (NeQuickG_context_t*)(*pHandle);
  assert(pContext);

  int32_t ret;

  ret = iono_profile_init(&pContext->profile);
  if (ret != NEQUICK_OK) {
    free(*pHandle);
    *pHandle = NEQUICKG_INVALID_HANDLE;
    return ret;
  }

  return NEQUICK_OK;
}

void NeQuickG_close(NeQuickG_handle handle) {
  if (handle != NEQUICKG_INVALID_HANDLE) {
    free(handle);
  }
}

int32_t set_solar_activity_coefficients(
  const NeQuickG_handle handle,
  const double_t * const pCoeff, size_t coeff_count) {

  int32_t ret = check_handle(handle);
  if (ret != NEQUICK_OK) {
    return ret;
  }

  return solar_activity_coefficients_set(
    &((NeQuickG_context_t*)handle)->solar_activity,
    pCoeff, coeff_count);
}

int32_t get_total_electron_content_impl2(
  const NeQuickG_handle handle,
  double_t* const pTotal_electron_content) {

  *pTotal_electron_content = 0.0;

  int32_t ret = check_handle(handle);
  if (ret != NEQUICK_OK) {
    return ret;
  }

  NeQuickG_context_t* pContext = (NeQuickG_context_t*)(handle);

  get_solar_activity(pContext);

  ret = ray_get(
    &pContext->ray,
    &pContext->input_data.station_position,
    &pContext->input_data.satellite_position);
  if (ret != NEQUICK_OK) {
    return ret;
  }

  ret = NeQuickG_integrate(pContext, pTotal_electron_content);
  if (ret == NEQUICK_OK) {
    *pTotal_electron_content = (*pTotal_electron_content / 1.0E13);
  }
  return ret;
}

int32_t set_time(
  const NeQuickG_handle handle,
  const uint8_t month,
  const double_t UTC) {

  int32_t ret = check_handle(handle);
  if (ret != NEQUICK_OK) {
    return ret;
  }

  NeQuickG_context_t* pContext = (NeQuickG_context_t*)(handle);
  ret = NeQuickG_time_set(&pContext->input_data.time, month, UTC);

  pContext->profile.E.is_solar_declination_valid = false;

  return ret;
}

int32_t set_station_position(
  const NeQuickG_handle handle,
  const double_t longitude_degree,
  const double_t latitude_degree,
  const double_t height_meters) {

  int32_t ret = check_handle(handle);
  if (ret != NEQUICK_OK) {
    return ret;
  }

  NeQuickG_context_t* pContext = (NeQuickG_context_t*)(handle);
  return position_set(
    &pContext->input_data.station_position,
    longitude_degree,
    latitude_degree,
    height_meters,
    NEQUICK_G_JRC_HEIGHT_UNITS_METERS);
}

int32_t set_satellite_position(
  const NeQuickG_handle handle,
  const double_t longitude_degree,
  const double_t latitude_degree,
  const double_t height_meters) {

  int32_t ret = check_handle(handle);
  if (ret != NEQUICK_OK) {
    return ret;
  }

  NeQuickG_context_t* pContext = (NeQuickG_context_t*)(handle);
  return position_set(
    &pContext->input_data.satellite_position,
    longitude_degree,
    latitude_degree,
    height_meters,
    NEQUICK_G_JRC_HEIGHT_UNITS_METERS);
}

int32_t CCIR_get_ionosonde_F2(
  uint_fast8_t month,
  F2_coefficient_array_t** pF2) {

  switch (month) {
  case NEQUICK_G_JRC_MONTH_JANUARY:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pF2 = (F2_coefficient_array_t*)&g_NeQuickG_ccir11_F2;
    break;
  case NEQUICK_G_JRC_MONTH_FEBRUARY:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pF2 = (F2_coefficient_array_t*)&g_NeQuickG_ccir12_F2;
    break;
  case NEQUICK_G_JRC_MONTH_MARCH:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pF2 = (F2_coefficient_array_t*)&g_NeQuickG_ccir13_F2;
    break;
  case NEQUICK_G_JRC_MONTH_APRIL:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pF2 = (F2_coefficient_array_t*)&g_NeQuickG_ccir14_F2;
    break;
  case NEQUICK_G_JRC_MONTH_MAY:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pF2 = (F2_coefficient_array_t*)&g_NeQuickG_ccir15_F2;
    break;
  case NEQUICK_G_JRC_MONTH_JUNE:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pF2 = (F2_coefficient_array_t*)&g_NeQuickG_ccir16_F2;
    break;
  case NEQUICK_G_JRC_MONTH_JULY:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pF2 = (F2_coefficient_array_t*)&g_NeQuickG_ccir17_F2;
    break;
  case NEQUICK_G_JRC_MONTH_AUGUST:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pF2 = (F2_coefficient_array_t*)&g_NeQuickG_ccir18_F2;
    break;
  case NEQUICK_G_JRC_MONTH_SEPTEMBER:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pF2 = (F2_coefficient_array_t*)&g_NeQuickG_ccir19_F2;
    break;
  case NEQUICK_G_JRC_MONTH_OCTOBER:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pF2 = (F2_coefficient_array_t*)&g_NeQuickG_ccir20_F2;
    break;
  case NEQUICK_G_JRC_MONTH_NOVEMBER:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pF2 = (F2_coefficient_array_t*)&g_NeQuickG_ccir21_F2;
    break;
  case NEQUICK_G_JRC_MONTH_DECEMBER:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pF2 = (F2_coefficient_array_t*)&g_NeQuickG_ccir22_F2;
    break;
  default:
    *pF2 = NULL;
    NEQUICK_ERROR_RETURN(
      NEQUICK_INPUT_DATA_EXCEPTION,
      NEQUICK_INPUT_DATA_BAD_MONTH,
      "Invalid month %u", month);
  }

  return NEQUICK_OK;
}

int32_t CCIR_get_ionosonde_Fm3(
  uint_fast8_t month,
  Fm3_coefficient_array_t** pFm3) {

  switch (month) {
  case NEQUICK_G_JRC_MONTH_JANUARY:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pFm3 = (Fm3_coefficient_array_t*)&g_NeQuickG_ccir11_Fm3;
    break;
  case NEQUICK_G_JRC_MONTH_FEBRUARY:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pFm3 = (Fm3_coefficient_array_t*)&g_NeQuickG_ccir12_Fm3;
    break;
  case NEQUICK_G_JRC_MONTH_MARCH:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pFm3 = (Fm3_coefficient_array_t*)&g_NeQuickG_ccir13_Fm3;
    break;
  case NEQUICK_G_JRC_MONTH_APRIL:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pFm3 = (Fm3_coefficient_array_t*)&g_NeQuickG_ccir14_Fm3;
    break;
  case NEQUICK_G_JRC_MONTH_MAY:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pFm3 = (Fm3_coefficient_array_t*)&g_NeQuickG_ccir15_Fm3;
    break;
  case NEQUICK_G_JRC_MONTH_JUNE:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pFm3 = (Fm3_coefficient_array_t*)&g_NeQuickG_ccir16_Fm3;
    break;
  case NEQUICK_G_JRC_MONTH_JULY:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pFm3 = (Fm3_coefficient_array_t*)&g_NeQuickG_ccir17_Fm3;
    break;
  case NEQUICK_G_JRC_MONTH_AUGUST:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pFm3 = (Fm3_coefficient_array_t*)&g_NeQuickG_ccir18_Fm3;
    break;
  case NEQUICK_G_JRC_MONTH_SEPTEMBER:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pFm3 = (Fm3_coefficient_array_t*)&g_NeQuickG_ccir19_Fm3;
    break;
  case NEQUICK_G_JRC_MONTH_OCTOBER:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pFm3 = (Fm3_coefficient_array_t*)&g_NeQuickG_ccir20_Fm3;
    break;
  case NEQUICK_G_JRC_MONTH_NOVEMBER:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pFm3 = (Fm3_coefficient_array_t*)&g_NeQuickG_ccir21_Fm3;
    break;
  case NEQUICK_G_JRC_MONTH_DECEMBER:
    //lint -e{545, 740} & is suspicious to lint because g_NeQuickG_ccir11_F2 is an array, but that's okay.
    *pFm3 = (Fm3_coefficient_array_t*)&g_NeQuickG_ccir22_Fm3;
    break;
  default:
    *pFm3 = NULL;
    NEQUICK_ERROR_RETURN(
      NEQUICK_INPUT_DATA_EXCEPTION,
      NEQUICK_INPUT_DATA_BAD_MONTH,
      "Invalid month %u", month);
  }

  return NEQUICK_OK;
}

int32_t F2_layer_fourier_coefficients_init(
  F2_layer_fourier_coeff_context_t* const pContext) {

  NeQuickG_time_init(&pContext->time);

  {
    pContext->interpolated.effective_sun_spot_count = 0.0;
    pContext->interpolated.valid = false;
    pContext->fourier.valid = false;
  }
  return NEQUICK_OK;
}

int32_t set_parameters(
  F2_layer_fourier_coeff_context_t* const pContext,
  const NeQuickG_time_t* const pTime,
  const double_t Azr) {

  bool ionosonde_coeff_valid =
    NEQUICK_G_TIME_MONTH_EQUAL(
      pTime->month,
      pContext->time.month);

  if (ionosonde_coeff_valid) {
    pContext->interpolated.valid =
      solar_activity_is_effective_ionisation_level_equal(
        Azr,
        pContext->interpolated.effective_sun_spot_count*100.0);
    if (pContext->interpolated.valid) {
      pContext->fourier.valid =
        NeQuickG_time_utc_is_equal(
          pTime->utc,
          pContext->time.utc);
    } else {
      pContext->interpolated.effective_sun_spot_count = Azr / 100.0;
      pContext->fourier.valid = false;
    }
    if (!pContext->fourier.valid) {
      pContext->time.utc = pTime->utc;
    }
  } else {
    pContext->time = *pTime;
    pContext->interpolated.effective_sun_spot_count = Azr / 100.0;
    pContext->interpolated.valid = false;
    pContext->fourier.valid = false;
  }
  return NEQUICK_OK;
}

/**
 * AF2 elements are calculated by linear combination of the elements of F2.
 */
int32_t interpolate_F2(
  F2_layer_fourier_coeff_context_t* const pContext) {

  int32_t ret;

  F2_coefficient_array_t* pF2;
  ret = CCIR_get_ionosonde_F2(pContext->time.month, &pF2);
  if (ret != NEQUICK_OK) {
    return ret;
  }

  size_t degree;
  size_t order;
  for (degree = 0; degree < ITU_F2_COEFF_MAX_DEGREE; degree++) {
    for (order = 0; order < ITU_F2_COEFF_MAX_ORDER; order++) {
      pContext->interpolated.F2[degree][order] =
        pF2[ITU_F2_LAYER_COEFF_LOW_SOLAR_ACTIVITY_IDX]
          [degree][order] * (1.0 - pContext->interpolated.effective_sun_spot_count) +
        pF2[ITU_F2_LAYER_COEFF_HIGH_SOLAR_ACTIVITY_IDX]
          [degree][order] * pContext->interpolated.effective_sun_spot_count;
    }
  }
  return ret;
}

/**
 * Am3 elements are calculated by linear combination of the elements of Fm3:
 */
int32_t interpolate_Fm3(
  F2_layer_fourier_coeff_context_t* const pContext) {

  int32_t ret;

  Fm3_coefficient_array_t* pFm3;
  ret = CCIR_get_ionosonde_Fm3(pContext->time.month, &pFm3);
  if (ret != NEQUICK_OK) {
    return ret;
  }

  size_t degree;
  size_t order;
  for (degree = 0; degree < ITU_FM3_COEFF_MAX_DEGREE; degree++) {
    for (order = 0; order < ITU_FM3_COEFF_MAX_ORDER; order++) {
      pContext->interpolated.Fm3[degree][order] =
        pFm3[ITU_F2_LAYER_COEFF_LOW_SOLAR_ACTIVITY_IDX]
          [degree][order] * (1.0 - pContext->interpolated.effective_sun_spot_count) +
        pFm3[ITU_F2_LAYER_COEFF_HIGH_SOLAR_ACTIVITY_IDX]
          [degree][order] * pContext->interpolated.effective_sun_spot_count;
    }
  }
  return ret;
}

int32_t F2_layer_fourier_coefficients_interpolate(
  F2_layer_fourier_coeff_context_t* const pContext,
  const NeQuickG_time_t * const pTime,
  const double_t Azr) {

  int32_t ret = set_parameters(pContext, pTime, Azr);
  if (ret != NEQUICK_OK) {
    return ret;
  }

  if (!pContext->interpolated.valid) {

    ret = interpolate_F2(pContext);
    if (ret != NEQUICK_OK) {
      return ret;
    }

    ret = interpolate_Fm3(pContext);
    if (ret != NEQUICK_OK) {
      return ret;
    }

    pContext->interpolated.valid = true;
  }
  return NEQUICK_OK;
}

void get_harmonics(
  const NeQuickG_time_t * const pTime,
  double_t * const pSin,
  double_t * const pCos) {
  double_t solar_longitude_rad =
    solar_get_longitude(pTime);

  //sin(nA) = sin[(n-1)A + A] with sin(A + B) = sin(A)cos(B) + cos(A)sin(B),
  //cos(nA) = cos[(n-1)A + A] with cos(A + B) = cos(A)cos(B) - sin(A)sin(B).
  size_t i = 0;
  {
    pSin[i] = sin(solar_longitude_rad);
    pCos[i] = cos(solar_longitude_rad);
    i++;
  }
  //lint -e{506} ITU_F2_LAYER_MAX_HARMONICS_COEFF is not constant, as lint means
  while (i < ITU_F2_LAYER_MAX_HARMONICS_COEFF) {
    size_t prev_index = i - 1;
    pSin[i] = pSin[prev_index] * pCos[0] + pCos[prev_index] * pSin[0];
    pCos[i] = pCos[prev_index] * pCos[0] - pSin[prev_index] * pSin[0];
    i++;
  }
}

void get_fourier_coefficients_CF2(
  const F2_layer_fourier_coeff_context_t* const pContext,
  const double_t * const pSin,
  const double_t * const pCos,
  F2_fourier_coefficient_array_t CF2) {
  for (size_t i = 0x00; i < ITU_F2_COEFF_MAX_DEGREE; i++) {
    CF2[i] = pContext->interpolated.F2[i][0];
    for (size_t j = 0x00; j < ITU_F2_LAYER_MAX_HARMONICS_CF2; j++) {
      size_t order = 2 * (j + 1);
      CF2[i] +=
        (pSin[j] * pContext->interpolated.F2[i][order - 1]) +
        (pCos[j] * pContext->interpolated.F2[i][order]);
    }
  }
}

void get_fourier_coefficients_Cm3(
  const F2_layer_fourier_coeff_context_t* const pContext,
  const double_t * const pSin,
  const double_t * const pCos,
  Fm3_fourier_coefficient_array_t Cm3) {
  for (size_t i = 0x00; i < ITU_FM3_COEFF_MAX_DEGREE; i++) {
    Cm3[i] = pContext->interpolated.Fm3[i][0];
    for (size_t j = 0x00; j < ITU_F2_LAYER_MAX_HARMONICS_CM3; j++) {
      size_t order = 2 * (j + 1);
      Cm3[i] +=
        (pSin[j] * pContext->interpolated.Fm3[i][order - 1]) +
        (pCos[j] * pContext->interpolated.Fm3[i][order]);
    }
  }
}

void F2_layer_fourier_coefficients_get_impl(
  F2_layer_fourier_coeff_context_t* const pContext) {

  //lint -e{506} ITU_F2_LAYER_MAX_HARMONICS_COEFF is not constant, as lint means
  double_t sinus_terms[ITU_F2_LAYER_MAX_HARMONICS_COEFF];
  //lint -e{506} ITU_F2_LAYER_MAX_HARMONICS_COEFF is not constant, as lint means
  double_t cosinus_terms[ITU_F2_LAYER_MAX_HARMONICS_COEFF];

  get_harmonics(&pContext->time, sinus_terms, cosinus_terms);

  get_fourier_coefficients_CF2(
    pContext,
    sinus_terms, cosinus_terms,
    pContext->fourier.CF2);

  get_fourier_coefficients_Cm3(
    pContext,
    sinus_terms, cosinus_terms,
    pContext->fourier.Cm3);
}

int32_t F2_layer_fourier_coefficients_get(
  F2_layer_fourier_coeff_context_t* const pContext,
  const NeQuickG_time_t * const pTime,
  const solar_activity_t* const pSolar_activity) {

  int32_t ret = F2_layer_fourier_coefficients_interpolate(
    pContext, pTime, pSolar_activity->effective_sun_spot_count);
  if (ret != NEQUICK_OK) {
    return ret;
  }

  if (!pContext->fourier.valid) {
    F2_layer_fourier_coefficients_get_impl(pContext);
    pContext->fourier.valid = true;
  }

  return NEQUICK_OK;
}

// NeQuick-G JRC. Implementation end
