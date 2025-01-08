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
 * File: dataHandling.h
 * Code Management Tool File Version: 6.0  Revision: 0
 * Date: 2024/11/22
 ***************************************************************************/

/****************************************************************************
 * MODULE DESCRIPTION
 *
 * Name: dataHandling
 * Language: C
 *
 * Purpose:
 *  The purpose of this module is to centralize all the data structures of the 
 *  modules and allow an easy interface to them.
 *
 * Function:
 *  This class is in charge of declaring all the data structures used in all the
 *  modules. It defines all the required functions to access the information 
 *  inside the data structures, and a group of general functions.
 *
 * Dependencies:
 *  None
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
 * Change Log: Inertial/Non-inertial velocity switch included
 *             Included DCB data sources
 *             Included SINEX, DCBs and GPS_Receiver_Type data files
 *             Included strict radome option to enable/disable a relaxed matching
 *                  on ANTEX files
 *             Forward/Backward processing included
 * -------------
 *          gLAB v1.4.0
 * Release: 2010/06/21
 * Change Log: C1/P1 flexibility option is added to allow flexible handling of C1 and P1
 *             Included usable measurement index in TMeasOrder structure to select/deselect
 *                  individual measurements
 *             Included prealignCP option to set/unset carrier-phase prealignment 
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
 * Change Log: Maximum number of filter iterations added.
 * 	       Improved DCB Management.
 * -------------
 *          gLAB v1.4.4
 * Release: 2010/09/22
 * Change Log: Included new DCB management.
 * -------------
 *          gLAB v1.4.5
 * Release: 2010/10/31
 * Change Log: Tropospheric correction option is extended to select independently the nominal and mapping used.
 *             Dilution Of Precision extension: (GDOP, PDOP, TDOP, VDOP, HDOP) new variables.
 * 	       Default precise orbit interpolation degree changed from 9 to 10.
 *   	       SIGMA_INF splitted into different SIGMA_INF_DR and SIGMA_INF_DT: receiver coordinates and clock.
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
 * Change Log: Modified structure definitions (by adding new variables) for handling RINEX 3.02 files.
 *             Added new constants.
 *             Added new structures for handling IONEX and F-PPP data
 *             Added functions for initialising IONEX and F-PPP structures (both for ionosphere and DCB data).
 *             Added functions for handling IONEX and F-PPP structures (both for ionosphere and DCB data).
 *             Added function for computing the ionosphere mapping value.
 *             Added function for computing the pierce point value.
 *             Added functions for initialising ESA's troposphere model structures.
 *             Added functions for handling ESA's troposphere model structures.
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
 * Change Log: Added variables in TConstellationElement, TAntenna and TOptions structs for processing phase variatons in satellites and receivers.
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
 *             Added user-defined error struct.
 *             Deleted satWas function.
 *             Added satIs function. It returns the index of the satellite in its dictionary.
 *             Added tsec function. It returns the MJDN + SoD in seconds.
 *             Modified structure definitions for handling Cycle Slip variables.
 *             Added QZSS and IRNSS constellations.
 * -----------
 *          gLAB v3.1.0
 * Release: 2016/09/26
 * Change Log: Erased some unncessary variables for GLONASS broadcast ephemerides.
 * -----------
 *          gLAB v3.1.1
 * Release: 2016/10/21
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v4.0.0
 * Release: 2017/03/03
 * Change Log: Added DGNSS structure.
 *             Added several structures for RTCM converter.
 *             Added several options for DGNSS.
 *             Added functions to initialise the RTCM structures.
 *             Added functions to initialise SBASplots structures.
 *             Added function date2doy.
 *             Added function doy2date.
 *             Added function SolutionModeNum2SolutionModeChar.
 *             Added parameters for SBAS summary.
 *             Added ConcatenateSP3 function.
 *             Added comparison functions for qsort function.
 *             Changed constant name MAX_SATELLITES_IN_VIEW to MAX_SATELLITES_VIEWED.
 *             Changed constant name c to c0. Single letter constants made compilation fail in Windows.
 *             Fixed p1p2dcbModel variable definition in TTGDdata structure. It was defined as
 *               'enum P1C1DCBModel' when the correct type is 'enum P1P2DCBModel' (it didn't affect
 *                the code as all enum types behave as integer values when compiled).
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
 * Change Log:   Changed MAXSWITCHPEREPOCH from 2 to 50 to allow more GEO changes in one epoch.
 *               Added functions 'ConvertCalendarDate', 'ConvertDoYDate', 'ConvertGPSWeekDate'
 *                 and 'ConvertMJDNDate' for date conversion.
 *               Added 'ConvertCartesianCoord', 'ConvertGeodeticCoord' and 'ConvertSphericalCoord'
 *                 for coordinate conversion.
 * -----------
 *          gLAB v5.1.1
 * Release: 2017/12/22
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.1.2
 * Release: 2018/01/12
 * Change Log:   Added 'numthreads' variable in 'TOptions' structure.
 * -----------
 *          gLAB v5.1.3
 * Release: 2018/01/19
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.2.0
 * Release: 2018/03/09
 * Change Log: Added functions 'InitRangeList', 'freeRangeList', 'AddRangeList' and 'ExtendRangeList' for
 *               computing ranges of satellites grouped by a property (e.g. weight type).
 *             Added function 'SatRangeList2String' for transforming a range list to a string.
 *             Added function 'WeightType2String' to transform from weight type to string.
 *             Added function 'SNRCombModeNum2String' to transform from SNR combination type to string.
 * -----------
 *          gLAB v5.3.0
 * Release: 2018/06/08
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.4.0
 * Release: 2018/11/16
 * Change Log: Added variables for new options and for data buffering when option select best GEO is enabled.
 *             Added functions 'qsort_compare_float', 'SBASGEOselection', 'SBASGEOAlarmCheck',
 *               'SaveDataforGEOselection' and 'SelectBestGEO'.
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
 * Change Log:   Fixed wrong value of constant MAXAPROXPOSERROR. It had '1E-5', when
 *                 the correct value should be '1E5'. This error in the constant 
 *                 value made not to discard any satellite by its elevation, as this
 *                 constant set the threshold for considering the solution converged
 *                 enough for accepting the satellite elevation values as correct.
 *                 This bug affected all modes except SBAS plots modes, and ocurred
 *                 only in version 5.4.2.
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
 *          gLAB v6.0.0
 * Release: 2024/11/22
 * Change Log:   Added multi-constellation support (Galileo, GLONASS, GEO, BDS, QZSS and IRNSS).
 *               Added multi-frequency support (all RINEX frequencies).
 *               Added SBAS DFMC processing.
 *               Global variables are now declared in this file (as "extern"), as correct C requires
 *                 that global variables shared between files need to be declared in a header file
 *                 and defined only once in a .c file.
 * -----------
 *       END_RELEASE_HISTORY
 *****************************/

#ifndef DATAHANDLING_H_
#define DATAHANDLING_H_

#if defined __WIN32__
 	//This is to allow %lld, %llu and %n format specifiers in printf with MinGW
	#define __USE_MINGW_ANSI_STDIO  1
#endif

/* System modules */
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

//If user sets at compiling time the variable "READNOLOCK", use the
//unlocked version of fgetc, feof, ferror and fflush functions. Unlocked
//version of these functions do not execute the code for gathering 
//or checking for exclusive access (file locking) to file each time 
//they are executed. Exclusive access is only necessary when
//file is accessed concurrently, which is not the case in gLAB
//Mac has no fgetc_unlocked function, so leave the standard versions. 
#if (defined READNOLOCK) && (!defined __APPLE__)
	#define READNOLOCKENABLED 1
	#if defined __WIN32__ || defined _WIN32
		#define fgetc_function	_fgetc_nolock
		#define feof_function 	feof
		#define ferror_function	ferror
		#define fflush_function	fflush
 	#else
		#define fgetc_function 	fgetc_unlocked
		#define feof_function 	feof_unlocked
		#define ferror_function	ferror_unlocked
		#define fflush_function	fflush_unlocked
	#endif 
#else
	#define fgetc_function 	fgetc
	#define feof_function 	feof
	#define ferror_function	ferror
	#define fflush_function	fflush
#endif

/* Internal types, constants and data */
#define MAX_SATELLITES_VIEWED					171
#define	MAX_SATELLITES_IN_VIEW					50	//This limit is just for the maximum number of ambiguities supported by the filter
#define MAX_GNSS								7
#define MAX_SATELLITES_PER_GNSS					64 //Worst case is for BDS, which may have up to PRN 63
#define MAX_FREQUENCIES_PER_GNSS				10
#define MAX_MEASUREMENTS_PER_SATELLITE			96 	//Worst case: All BDS measurements with codes, phases, SNR and Doppler in RINEX 3.04 (this variable is only for printing MEAS message)
#define MAX_MEAS_TYPES_PER_FREQUENCY            16 	//Maximum different letter signal types defined in list of signals
#define MAX_MEAS_TYPES_PER_FREQUENCY_PER_GNSS   16 	//Maximum different letter signal types defined in list of signals for one constellation
#define MAX_SLIDING_WINDOW						610
#define MAX_INTERPOLATION_DEGREE				19
#define MAX_RECEIVER_NAME						64
#define MAX_ANTENNA_NAME						60
#define MAX_MEASUREMENTS						3112
#define MAX_MEASUREMENTS_NO_COMBINATIONS		661
#define MAX_CODE_MEASUREMENTS_NO_COMBINATIONS	MAX_MEASUREMENTS_NO_COMBINATIONS/4
#define MAX_PHASE_MEASUREMENTS_NO_COMBINATIONS	MAX_MEASUREMENTS_NO_COMBINATIONS/4
#define MAX_MEASUREMENTS_NO_COMBINATIONS_NO_SNR	3*MAX_MEASUREMENTS_NO_COMBINATIONS/4
#define MAX_MEASKIND_PRINT_MEASUREMENTS			3	//Code, smoothed code and phase
#define MAX_TRIPLE_FREQUENCIES_COMBINATIONS		359
#define	MAX_DIFF_DUALFREQDCB					6
#define	NUM_COMB_IGF_MIN_NOISE					3
#define MAX_CS_MEMORY							20
#define MAX_CS_LIST								10 //Note: If this value increases a bit, sizeof TEpoch struct increases a lot!
#define MAX_FILTER_MEASUREMENTS_SAT				MAX_MEAS_TYPES_PER_FREQUENCY	//If this value increases, TEpoch struct increases noticeably
#define MAX_FILTER_SATELLITE_DCB				MAX_SATELLITES_IN_VIEW*MAX_FILTER_MEASUREMENTS_SAT/2	//When estimating DCBs, we must have paired measurements, and satellite DCBs are shared by code and phase	
#define MAX_FILTER_RECEIVER_DCB					MAX_GNSS*MAX_FILTER_MEASUREMENTS_SAT/2	//When estimating DCBs, we must have paired measurements, and receiver  DCBs are shared by code and phase	
#define MAX_FILTER_MEASUREMENTS					MAX_SATELLITES_IN_VIEW*MAX_FILTER_MEASUREMENTS_SAT
#define	MAX_FILTER_MEASTYPE						18
#define MAX_MEASUREMENTS_INDEX_ALL_SAT			MAX_MEAS_TYPES_PER_FREQUENCY*4
#define	MAX_BRDC_TYPES							6
#define MAX_BRDC_SELECTION_TYPES				12
#define MAX_HEALTH_TYPES						3
#define MAX_AMBIGUITIES_FILTER					MAX_SATELLITES_IN_VIEW*MAX_FILTER_MEASUREMENTS_SAT/2
#define MAX_UNK									(3+MAX_GNSS+MAX_AMBIGUITIES_FILTER+1+1+1+MAX_SATELLITES_IN_VIEW+MAX_AMBIGUITIES_FILTER+MAX_FILTER_RECEIVER_DCB)	//Coordinates + clocks + Ambiguities + Tropo + WindUp +  GLO IFB + Iono + DCB Receiver + DCB Satellite
#define MAX_VECTOR_UNK							((MAX_UNK)*(MAX_UNK+1)/2)
#define MAX_UNK_STFDESA							(3+MAX_GNSS)
#define MAX_VECTOR_UNK_STFDESA					((MAX_UNK_STFDESA)*(MAX_UNK_STFDESA+1)/2)
#define MAX_PAR									10
#define MAX_SBAS_PRN							211
#define	MAX_SBASDFMC_MASK_PRN					38
#define	MAX_SBASDFMC_MASKSLOTNUMBER				215
#define MAX_NUM_SBAS							50
#define MAX_FILTER_MEAS_TYPES					18	//Number of different measurement types in filter set in enum FilterMeasType
#define MAX_LINES_BUFFERED						10
#define MAX_LINES_BUFFEREDPREFIT				40
#define MAX_LINES_BUFFEREDCS					MAX_CS_LIST*4	//Maximum number of enabled cycle-slip detectors (4) plus number of iteration per each detector
#define MAX_MEAS_PRINT_LENGTH					25
#define MAX_SOLUTION_MODES						8
#define	MAX_TIME_SYSTEM_CORRECTION				12
#define MAX_SATELLITES_BLOCK					37
#define SIGMA_INF								1e7
#define SIGMA_INF_DR							1e4
#define SIGMA_RANDOMWALK_DR						8.3666	//8.366 m equals to sqrt(70 m^2). This value is for a speed of 30Km/h
#define SIGMA_INF_DT							3e5
#define SIGMA_RANDOMWALK_DT						3.	// 3 m/d equal to sqrt(9m^2/d)
#define SIGMA_RANDOMWALK_IONO					1.4142	// 1.4142 TECU/h equal  to sqrt(2) TECU^2/h
#define SIGMA_RANDOMWALK_SATDCB					1.4142	// 1.4142 TECU/h equal  to sqrt(2) TECU^2/h
#define SIGMA_RANDOMWALK_RECDCB					1.4142	// 1.4142 TECU/h equal  to sqrt(2) TECU^2/h
#define SIGMA_INF_IONO							1E4	// 1E4 TECU
#define SIGMA_INF_SATDCB						1E4	// 1E4 TECU
#define SIGMA_INF_RECDCB						1E4	// 1E4 TECU
#define SIGMA_INF_REC_WIND_UP					10	// 10 m/s
#define MAX_INPUT_LINE							4096
#define MAX_PRINT_LINE							600
#define MAX_PRINT_LINE_MODEL					800
#define MAX_PRINT_LINE_FILTER					1024
#define MAX_PRINT_LINE_TEPOCH					200
#define MAX_WORDS								MAX_INPUT_LINE/2+1 //This is the maximum number of words possible in MAX_INPUT_LINE
#define MAX_MESSAGE_STR							3*MAX_INPUT_LINE
#define MAX_OUTPUT_FILENAME						2*MAX_INPUT_LINE //This to avoid potential buffer overflow in output filename if filename+extension is large enough
#define MAX_STATION_NAME						200
#define MAX_DEPRECATED_MSG_SIZE					160
#define	MAX_LINES_BUFFERED_SBAS_MESSAGES		10
#define INVALID_CLOCK							999999.999999
#define MAX_DCB_FILE_SOURCES					4
#define MAX_NAV_FILES							MAX_GNSS	//One for each constellation, as typically navigation data is saved separately
#define MAX_SP3_FILES							2
#define MAX_RECV_ANTEX_FILES					2			//Two additional ANTEX files for the rover receiver and the reference station receiver
#define MAX_LEAP_SECONDS_SIZE					19
#define MAX_NO_AS_PERIODS						5
#define	MAX_IODE_VALUE							1024		//Galileo IODE has 10 bits
#define MAX_SAT_GPS								32
#define MAX_SAT_GAL								36
#define MAX_SAT_GLO								32
#define MAX_SAT_GEO								58
#define MAX_SAT_BDS								63
#define MAX_SAT_QZS								10
#define MAX_SAT_IRN								14

#define PRINT_ORDER_CODE						0
#define PRINT_ORDER_CODE_SMOOTHED				1
#define PRINT_ORDER_PHASE						2
#define PRINT_ORDER_DOPPLER						3

#define	FIRST_POS_IS_CLK						4	//The first position of an inter-system clock bias will be at position 4, after X,Y,Z and dt


//NOTE: Single letter constants may cause problems when compiling in Windows!!
//For this reason, the constant 'c' (speed of light) was changed to 'c0'
#define c0										299792458.0
#define MU										3.986005e14
#define f0										10.23e6
#define cf0										(c0/f0)
#define EARTH_ROTATION							7.2921151467e-5
#define MAX_CLOCK_DISTANCE						0.3
#define MAXEXTRAPOLATIONTIME					1.
#define AU										1.49597870e8
#define Pi										3.14159265358979
#define d2r										(Pi/180.)
#define r2d										(180./Pi)
#define EARTH_RADIUS							6378137.
#define MIN_EARTH_RADIUS						6356752.
#define MIN_LEO_ORBIT_RADIUS					MIN_EARTH_RADIUS+1.E5	//Min LEO orbit radius is set to MIN_EARTH_RADIUS +100Km
#define SBAS_EARTH_RADIUS						6378136.3
#define KLOBUCHAR_HEIGHT						350000.
#define BEIDOU_HEIGHT							375000.
#define SBAS_HEIGHT								350000.
#define GEOMAGNETIC_POLE_LAT					78.3*d2r
#define GEOMAGNETIC_POLE_LON					291.*d2r
#define NUMBERSECONDSPERDAY						86400
#define NUMBERSECONDSPERHOUR					3600
#define NUMBERFPPPMAPS							2
#define TECU2MLI								0.105045952848732
#define DIFFGAL2GPSWEEK							1024
#define MIN_ELEVATION_WEIGHT					1*d2r	//Satellites under this elevation value are automatically discarded for weights involving 1/sin(elev)^2.
#define MAXAPROXPOSERROR						1E5		//Max uncertainty error in the receiver position for not checking the elevation of satellites
#define DIFFEQTHRESHOLD							1E-4	//When comparing two values, if difference is below this threshold, values will be considered equal
#define	FIRSTMJDNGPS							44244	//First day of GPS (6/1/1980)

#define GPSmf1									154.
#define GPSmf2									120.
#define GPSmf5									115.
#define GPSmfw									(GPSmf1-GPSmf2)
#define GALmf1									154.
#define GALmf5a									115.
#define GALmf5b									118.
#define GALmf5									116.5
#define GALmf6									125.
#define GLOmf1									121.798631476051 //Glonass f1 is FDMA and not a multiple of f0!
#define GLOmf2									156.598240469208 //Glonass f2 is FDMA and not a multiple of f0!
#define GLOmf3									117.5
#define GLOmf1a									156.5
#define GLOmf2a									122.
#define SBASmf1									154.
#define SBASmf5									115.
#define BDSmf1									154.
#define BDSmf1_2								152.6 
#define BDSmf2a									115.
#define BDSmf2b									118. 
#define BDSmf2									116.5 
#define BDSmf3									124. 
#define QZSmf1									154. 
#define QZSmf2									120. 
#define QZSmf5									115. 
#define QZSmf6									125.
#define IRNmf5									115. 
#define IRNmf9									243.6 

#define GPSf1									(GPSmf1*f0)
#define GPSf2									(GPSmf2*f0) 
#define GPSf5									(GPSmf5*f0)
#define GPSfw									(GPSmfw*f0)
#define GALf1									(GALmf1*f0)
#define GALf5a									(GALmf5a*f0)
#define GALf5b									(GALmf5b*f0)
#define GALf5									(GALmf5*f0)
#define GALf6									(GALmf6*f0)
#define GLOf1									1602e6 		//This is the base frequency of f1. Add frequency bias of k*9/16 (k=-7..+12)
#define GLOf2									1246e6		//This is the base frequency of f2. Add frequency bias of k*7/16 (k=-7..+12)
#define GLOf3									(GLOmf3*f0)
#define GLOf1a									(GLOmf1a*f0)
#define GLOf2a									(GLOmf2a*f0)
#define SBASf1									(SBASmf1*f0)
#define SBASf5									(SBASmf5*f0)
#define BDSf1 									(BDSmf1*f0)
#define BDSf1_2									(BDSmf1_2*f0)
#define BDSf2a									(BDSmf2a*f0)
#define BDSf2b									(BDSmf2b*f0)
#define BDSf2									(BDSmf2*f0)
#define BDSf3									(BDSmf3*f0)
#define QZSf1									(QZSmf1*f0) 
#define QZSf2									(QZSmf2*f0) 
#define QZSf5									(QZSmf5*f0) 
#define QZSf6									(QZSmf6*f0)
#define IRNf5									(IRNmf5*f0) 
#define IRNf9									(IRNmf9*f0) 

#define GPSl1									(cf0/GPSmf1)
#define GPSl2									(cf0/GPSmf2)
#define GPSl5									(cf0/GPSmf5)
#define GPSlw									(cf0/GPSmfw)
#define GALl1									(cf0/GALmf1)
#define GALl5a									(cf0/GALmf5a)
#define GALl5b									(cf0/GALmf5b)
#define GALl5									(cf0/GALmf5)
#define GALl6									(cf0/GALmf6)
#define GLOl1									(cf0/GLOmf1) 	//This is the base conversion factor of f1 (it will change depending on the frequency offset). 
#define GLOl2									(cf0/GLOmf2)	//This is the base conversion factor of f2 (it will change depending on the frequency offset). 
#define GLOl3									(cf0/GLOmf3)
#define GLOl1a									(cf0/GLOmf1a)
#define GLOl2a									(cf0/GLOmf2a)
#define SBASl1									(cf0/SBASmf1)
#define SBASl5									(cf0/SBASmf5)
#define BDSl1 									(cf0/BDSmf1)
#define BDSl1_2 								(cf0/BDSmf1_2)
#define BDSl2a									(cf0/BDSmf2a)
#define BDSl2b									(cf0/BDSmf2b)
#define BDSl2									(cf0/BDSmf2)
#define BDSl3									(cf0/BDSmf3)
#define QZSl1									(cf0/QZSmf1) 
#define QZSl2									(cf0/QZSmf2) 
#define QZSl5									(cf0/QZSmf5) 
#define QZSl6									(cf0/QZSmf6)
#define IRNl5									(cf0/IRNmf5) 
#define IRNl9									(cf0/IRNmf9) 

#define GAMMAGPS12								((GPSf1*GPSf1)/(GPSf2*GPSf2))
#define ALPHAGPS12								(1/(GAMMAGPS12-1))
#define GAMMAGPS15								((GPSf1*GPSf1)/(GPSf5*GPSf5))
#define ALPHAGPS15								(1/(GAMMAGPS15-1))
#define GAMMAGPS25								((GPSf2*GPSf2)/(GPSf5*GPSf5))
#define ALPHAGPS25								(1/(GAMMAGPS25-1))

#define GAMMAGAL15								((GALf1*GALf1)/(GALf5a*GALf5a))
#define ALPHAGAL15								(1/(GAMMAGAL15-1))
#define GAMMAGAL16								((GALf1*GALf1)/(GALf6*GALf6))
#define ALPHAGAL16								(1/(GAMMAGAL16-1))
#define GAMMAGAL17								((GALf1*GALf1)/(GALf5b*GALf5b))
#define ALPHAGAL17								(1/(GAMMAGAL17-1))
#define GAMMAGAL18								((GALf1*GALf1)/(GALf5*GALf5))
#define ALPHAGAL18								(1/(GAMMAGAL18-1))
#define GAMMAGAL56								((GALf5a*GALf5a)/(GALf6*GALf6))
#define ALPHAGAL56								(1/(GAMMAGAL56-1))
#define GAMMAGAL57								((GALf5a*GALf5a)/(GALf5b*GALf5b))
#define ALPHAGAL57								(1/(GAMMAGAL57-1))
#define GAMMAGAL58								((GALf5a*GALf5a)/(GALf5*GALf5))
#define ALPHAGAL58								(1/(GAMMAGAL58-1))
#define GAMMAGAL67								((GALf6*GALf6)/(GALf5b*GALf5b))
#define ALPHAGAL67								(1/(GAMMAGAL67-1))
#define GAMMAGAL68								((GALf6*GALf6)/(GALf5*GALf5))
#define ALPHAGAL68								(1/(GAMMAGAL68-1))
#define GAMMAGAL78								((GALf5b*GALf5b)/(GALf5*GALf5))
#define ALPHAGAL78								(1/(GAMMAGAL78-1))

#define GAMMAGLO34								((GLOf3*GLOf3)/(GLOf1a*GLOf1a))
#define ALPHAGLO34								(1/(GAMMAGLO34-1))
#define GAMMAGLO36								((GLOf3*GLOf3)/(GLOf2a*GLOf2a))
#define ALPHAGLO36								(1/(GAMMAGLO36-1))
#define GAMMAGLO46								((GLOf1a*GLOf1a)/(GLOf2a*GLOf2a))
#define ALPHAGLO46								(1/(GAMMAGLO46-1))

#define GAMMAGEO15								((SBASf1*SBASf1)/(SBASf5*SBASf5))
#define ALPHAGEO15								(1/(GAMMAGEO15-1))

#define GAMMABDS12								((BDSf1*BDSf1)/(BDSf1_2*BDSf1_2))
#define ALPHABDS12								(1/(GAMMABDS12-1))
#define GAMMABDS15								((BDSf1*BDSf1)/(BDSf2a*BDSf2a))
#define ALPHABDS15								(1/(GAMMABDS15-1))
#define GAMMABDS16								((BDSf1*BDSf1)/(BDSf3*BDSf3))
#define ALPHABDS16								(1/(GAMMABDS16-1))
#define GAMMABDS17								((BDSf1*BDSf1)/(BDSf2b*BDSf2b))
#define ALPHABDS17								(1/(GAMMABDS17-1))
#define GAMMABDS18								((BDSf1*BDSf1)/(BDSf2*BDSf2))
#define ALPHABDS18								(1/(GAMMABDS18-1))
#define GAMMABDS25								((BDSf1_2*BDSf1_2)/(BDSf2a*BDSf2a))
#define ALPHABDS25								(1/(GAMMABDS25-1))
#define GAMMABDS26								((BDSf1_2*BDSf1_2)/(BDSf3*BDSf3))
#define ALPHABDS26								(1/(GAMMABDS26-1))
#define GAMMABDS27								((BDSf1_2*BDSf1_2)/(BDSf2b*BDSf2b))
#define ALPHABDS27								(1/(GAMMABDS27-1))
#define GAMMABDS28								((BDSf1_2*BDSf1_2)/(BDSf2*BDSf2))
#define ALPHABDS28								(1/(GAMMABDS28-1))
#define GAMMABDS56								((BDSf2a*BDSf2a)/(BDSf3*BDSf3))
#define ALPHABDS56								(1/(GAMMABDS56-1))
#define GAMMABDS57								((BDSf2a*BDSf2a)/(BDSf2b*BDSf2b))
#define ALPHABDS57								(1/(GAMMABDS57-1))
#define GAMMABDS58								((BDSf2a*BDSf2a)/(BDSf2*BDSf2))
#define ALPHABDS58								(1/(GAMMABDS58-1))
#define GAMMABDS67								((BDSf3*BDSf3)/(BDSf2b*BDSf2b))
#define ALPHABDS67								(1/(GAMMABDS67-1))
#define GAMMABDS68								((BDSf3*BDSf3)/(BDSf2*BDSf2))
#define ALPHABDS68								(1/(GAMMABDS68-1))
#define GAMMABDS78								((BDSf2b*BDSf2b)/(BDSf2*BDSf2))
#define ALPHABDS78								(1/(GAMMABDS78-1))

#define GAMMAQZS12								((QZSf1*QZSf1)/(QZSf2*QZSf2))
#define ALPHAQZS12								(1/(GAMMAQZS12-1))
#define GAMMAQZS15								((QZSf1*QZSf1)/(QZSf5*QZSf5))
#define ALPHAQZS15								(1/(GAMMAQZS15-1))
#define GAMMAQZS16								((QZSf1*QZSf1)/(QZSf6*QZSf6))
#define ALPHAQZS16								(1/(GAMMAQZS16-1))
#define GAMMAQZS25								((QZSf2*QZSf2)/(QZSf5*QZSf5))
#define ALPHAQZS25								(1/(GAMMAQZS25-1))
#define GAMMAQZS26								((QZSf2*QZSf2)/(QZSf6*QZSf6))
#define ALPHAQZS26								(1/(GAMMAQZS26-1))
#define GAMMAQZS56								((QZSf5*QZSf5)/(QZSf6*QZSf6))
#define ALPHAQZS56								(1/(GAMMAQZS56-1))

#define GAMMAIRN59								((IRNf5*IRNf5)/(IRNf9*IRNf9))
#define ALPHAIRN59								(1/(GAMMAIRN59-1))

#define JULIANDAYDIFF							2400000.5

#define DEFAULTMARKERNAME						"----"

#define MAXLETTERSDICTIONARY					26

#define FLAG_CYCLESLIP							1
#define FLAG_FAIL								2

#define NUMTIMESYSTEMCORRECTIONTYPES			12

#define	GALILEOBRDCMSGMASK						775 //Binary mask 1100000111 (Bits 0,1,2,8,9 to check message type)

#define QZSSSBASPRNOFFSET						82	//QZSS SBAS compatible signals PRN are in range 183-187, in RINEX<=3.03 are (S83-S87) (RINEX>=3.04 are J01,J02,...)
#define QZSSOBSPRNOFFSET						192	//QZSS GPS compatible signals PRN are in range 193-201, but in RINEX are PRN-192 (1-9)
#define MINQZSSOBSPRN							193 //Minimum QZSS GPS compatible signals PRN
#define MAXQZSSOBSPRN                           201 //Maximum QZSS GPS compatible signals PRN

#define GLONASSMINSATOFFSETREAD					15 //Minimum K frequency offsets read from observation file "GLONASS SLOT / FRQ ". If smaller, navigation file will be read for more k (if available)

#define DIFFBDS2GPSTIME							14.	//Add this offset to convert from BeiDou time to GPS time

#define	CODEMEAS								0	//Position of code measurements in table of measurement preferences
#define	PHASEMEAS								1	//Position of phase measurements in table of measurement preferences
#define	DOPPLERMEAS								2	//Position of doppler measurements in table of measurement preferences
#define MEASTYPELISTS							3	//Number of measurements type list (one for codes, one for carrier phases and one for Doppler)

#define ROVERPOS								0
#define REFSTAPOS								1
#define	NUM_OBSRINEX							2  	//At most we will have two RINEX observation files, one for the rover and another for the reference station

#define MEASUNSELECTED							0
#define MEASSELECTED							1
#define MEASNOTAVAIL							2

#define	NUMMEASCSSF								2
#define	NUMMEASCSMW								4
#define	NUMMEASCSLI								2
#define	NUMMEASCSIGF							4

#define UNCHECKFREQ                             0
#define ADDEDFREQ                               1

#define	NONSMOOTHED								0
#define	SMOOTHED								1

#define SAMEDAYNAV								0
#define NEWDAYNAV								1

#define FREEPREVNAV								0
#define	FREEALLNAV								1

#define	ORBNAVPOS								0
#define	TGDNAVPOS								1
#define	HEALTHNAVPOS							2
#define IONONAVPOS								3
#define	MAXNAVSOURCES							3
#define	MAXNAVSOURCESWITHIONO					4

#define SBASOUTPUTPATH							"."
#define MAXSBASFASTCORR							50
#define UDRETHRESHOLDPA							12
#define URAMAXTHRESHOLD							15
#define MINGEOPRN								120
#define MAXGEOPRN								210
#define GEOACQUISIONTIME						300
#define MINIMUMSWITCHTIME						20
#define MAXSWITCHPEREPOCH						50
#define MAXSWITCHPERITERATIONSBASPLOT			MAX_NUM_SBAS
#define NPAMODE									0
#define PAMODE									1
#define KHORPOS									0
#define KVERPOS									1
#define KHPA									6.0
#define KHNPA									6.18
#define KV										5.33
#define SIGMA60PROPORTIONTHRESHOLD				0.5

#define	NUMPOSFREQSBASMSG						3
#define	SBAS1FFREQPOS							0
#define	SBASDFMCFREQPOS							1
#define	UNKNOWNFREQPOS							2


#define	NUMSBASMODEPOS							2
#define SBAS1FMODEPOS							0
#define SBASDFMCMODEPOS							1


#define	SBASMSGDURATION							1.
#define	SBASMSGFLIGHTTIME						.12


#define NUMBLOCKSWITHALLMEAS					20
#define	NUMGPSBLOCKSI_TO_IIRB					6	
#define	NUMGLONASSBLOCKSM2_TO_K1				2
#define	NUMBDSBLOCKS_TYPE2						3

// If observation file start at hour HOURSPREVDAYCONVERGENCE or later,
//  gLAB will consider that from this hour to the following day is just
//  epochs to make SBAS data, smoothing and filter values to converge
#define HOURSPREVDAYCONVERGENCE					22

// Definition for getLback (input.c)
#define BACKWARD_READ_BATCH						600

// Constants for SBAS MESSAGES
#define DONTUSE									0 	//SBAS 1F and DFMC
#define PRNMASKASSIGNMENTS						1	//SBAS 1F
#define FASTCORRECTIONS2						2	//SBAS 1F
#define FASTCORRECTIONS3						3	//SBAS 1F
#define FASTCORRECTIONS4						4   //SBAS 1F
#define FASTCORRECTIONS5						5   //SBAS 1F
#define INTEGRITYINFO							6   //SBAS 1F
#define FASTCORRECTIONSDEGRADATIONFACTOR		7   //SBAS 1F
#define RESERVED8								8
#define GEONAVIGATIONMESSAGE					9   //SBAS 1F
#define DEGRADATIONPARAMETERS					10	//SBAS 1F
#define RESERVED11								11
#define SBASNETWORKTIMEPARAMETERS				12  //SBAS 1F
#define RESERVED13								13
#define RESERVED14								14
#define RESERVED15								15
#define RESERVED16								16
#define GEOSATELLITEALMANACS					17  //SBAS 1F
#define IONOSPHERICGRIDPOINTSMASKS				18  //SBAS 1F
#define RESERVED19								19
#define RESERVED20								20
#define RESERVED21								21
#define RESERVED22								22
#define RESERVED23								23
#define MIXEDFASTLONGTERMCORRECTIONS			24  //SBAS 1F
#define LONGTERMSATELLITECORRECTIONS			25  //SBAS 1F
#define IONOSPHERICDELAYCORRECTIONS				26  //SBAS 1F
#define SBASSERVICEMESSAGE						27  //SBAS 1F
#define CLOCKEPHEMERISCOVARIANCEMATRIX			28  //SBAS 1F
#define	SATMASKASIGNMENTS						31	//SBAS DFMC
#define	CLOCKEPHEMERISCOVARIANCEMATRIXDFMC		32	//SBAS DFMC
#define	INTEGRITYINFODFMC34						34	//SBAS DFMC							
#define	INTEGRITYINFODFMC35						35	//SBAS DFMC							
#define	INTEGRITYINFODFMC36						36	//SBAS DFMC							
#define	OBADDFREIPARAMETERS						37	//SBAS DFMC
#define	SBASEPHEMERISDFMC						39	//SBAS DFMC
#define	SBASEPHEMERISCOVARIANCEDFMC				40	//SBAS DFMC
#define	SBASNETWORKTIMEPARAMETERSDFMC			42	//SBAS DFMC
#define	SBASALMANACSDFMC						47	//SBAS DFMC
#define	SERVICEAREADFMC							48	//SBAS DFMC
#define	SERVICEAREADFMCTESTBED					50	//SBAS DFMC
#define INTERNALTESTMESSAGE						62	//SBAS 1F and DFMC
#define NULLMESSAGE								63	//SBAS 1F and DFMC

// Constants for SBAS degradation factors in message 10
#define BRRC									0
#define CLTCLSB									1
#define CLTCV1									2
#define ILTCV1									3
#define CLTCV0									4
#define ILTCV0									5
#define CGEOLSB									6
#define CGEOV									7
#define IGEO									8
#define CER										9
#define CIONOSTEP								10
#define IIONO									11
#define CIONORAMP								12
#define RSSUDRE									13
#define RSSIONO									14
#define CCOVARIANCE								15

// Constants for SBAS long term satellite error corrections
#define VELOCITYCODE							0
#define PRNMASKNUMBER							1
#define ISSUEOFDATA								2
#define DELTAX									3
#define DELTAY									4
#define DELTAZ									5
#define DELTAAF0								6
#define DELTAXRATEOFCHANGE						7
#define DELTAYRATEOFCHANGE						8
#define DELTAZRATEOFCHANGE						9
#define DELTAAF1								10
#define TIMEOFDAYAPPLICABILITY					11
#define IODPPOSITION							12
#define	GLODELAYTIME							13
#define	GLOOPERATIONTIME						14

// Constants for SBAS GEO Navigation message
#define T0NAV									0
#define URAINDEX								1
#define XG										2
#define YG										3
#define ZG										4
#define XGRATEOFCHANGE							5
#define YGRATEOFCHANGE							6
#define ZGRATEOFCHANGE							7
#define XGACCELERATION							8
#define YGACCELERATION							9
#define ZGACCELERATION							10
#define AGF0									11
#define AGF1									12
#define IODNPOS									13
#define URAMINRANGE								14
#define URAMAXRANGE								15
#define URANOMINALVALUE							16

// Constants for SBAS GEO Almanacs message
#define DATAID									0
#define PRNNUMBER								1
#define HEALTHSTATUS							2
#define XGALMANAC								3
#define YGALMANAC								4
#define ZGALMANAC								5
#define XGALMANACRATEOFCHANGE					6
#define YGALMANACRATEOFCHANGE					7
#define ZGALMANACRATEOFCHANGE					8
#define T0ALMANAC								9
#define SERVICEPROVIDER							10
#define HEALTHPROVIDER							11

// Constants for SBAS Service message
#define IODSPOS									0
#define NUMBERSERVICEMESSAGES					1
#define SERVICEMESSAGENUMBER					2
#define NUMBEROFREGIONS							3
#define PRIORITYCODE							4
#define UDREINSIDEIND							5
#define UDREINSIDEVALUE							6
#define UDREOUTSIDEIND							7
#define UDREOUTSIDEVALUE						8

// Constants for SBAS Service message Region coordinate points
#define COORD1LAT								0
//#define NUMBERSERVICEMESSAGES					1	//Defined in previous list
#define COORD1LON								2
#define COORD2LAT								3
#define COORD2LON								4
#define COORD3LAT								5
//#define UDREINSIDEVALUE						6	//Defined in previous list
#define COORD3LON								7
//#define UDREOUTSIDEVALUE						8	//Defined in previous list
#define COORD4LAT								9
#define COORD4LON								10
#define REGIONSHAPE								11

// Constants for SBAS Network time parameters
#define A1SNT									0
#define A0SNT									1
#define T0T										2
#define WNT										3
#define DELTATLS								4
#define WNLSF									5
#define DNDAY									6
#define DELTATLSF								7
#define UTCIDENTIFIER							8
#define GPSTOW									9
#define GPSWEEKNUMBER							10
#define GLONASSINDICATOR						11
#define GLONASSAIOFFSSET						12

// Constants for SBAS Clock-Ephemeris Covariance Matrix parameters
#define SCALEEXPONENT							0
//#define PRNMASKNUMBER							1	//It is already defined in "Constants for SBAS long term satellite error corrections", we use the same one
#define E11										2
#define E22										3
#define E33										4
#define E44										5
#define E12										6
#define E13										7
#define E14										8
#define E23										9
#define E24										10
#define E34										11
//#define IODPPOSITION							12	//It is already defined in "Constants for SBAS long term satellite error corrections", we use the same one
#define SCALEFACTOR								13

// Constants for SBAS IGP Mask Message
#define NUMBEROFBANDS							0
#define BANDNUMBER								1
#define IODIPOS									2

// Constants for SBAS Ionospheric Delay parameters
#define BLOCKID									0
//#define BANDNUMBER							1	//It is already defined in "Constants for SBAS IGP Mask Message", we use the same one
//#define IODIPOS								2	//It is already defined in "Constants for SBAS IGP Mask Message", we use the same one
#define IGPVERTICALDELAY						3
#define GIVEI									4
#define GIVEVALUE								5
#define GIVEVARIANCE							6

// Constants for SBAS DFMC Clock-Ephemeris Covariance Matrix parameters
//#define SCALEEXPONENT							0	//It is already defined in "Constants for SBAS Clock-Ephemeris Covariance Matrix parameters", we use the same one
#define SATSLOTNUMBER							1	
//#define E11									2	//It is already defined in "Constants for SBAS Clock-Ephemeris Covariance Matrix parameters", we use the same one
//#define E22									3	//It is already defined in "Constants for SBAS Clock-Ephemeris Covariance Matrix parameters", we use the same one
//#define E33									4   //It is already defined in "Constants for SBAS Clock-Ephemeris Covariance Matrix parameters", we use the same one
//#define E44									5   //It is already defined in "Constants for SBAS Clock-Ephemeris Covariance Matrix parameters", we use the same one
//#define E12									6   //It is already defined in "Constants for SBAS Clock-Ephemeris Covariance Matrix parameters", we use the same one
//#define E13									7   //It is already defined in "Constants for SBAS Clock-Ephemeris Covariance Matrix parameters", we use the same one
//#define E14									8   //It is already defined in "Constants for SBAS Clock-Ephemeris Covariance Matrix parameters", we use the same one
//#define E23									9   //It is already defined in "Constants for SBAS Clock-Ephemeris Covariance Matrix parameters", we use the same one
//#define E24									10  //It is already defined in "Constants for SBAS Clock-Ephemeris Covariance Matrix parameters", we use the same one
//#define E34									11  //It is already defined in "Constants for SBAS Clock-Ephemeris Covariance Matrix parameters", we use the same one
#define IODNPOSITION							12	
#define	IODGPOSITIONNAVSBAS						12 	//Same as IODNPOSITION, but it will only be used for message type 40, as in this message IODG is sent instead of IODN
//#define SCALEFACTOR                           13	//It is already defined in "Constants for SBAS Clock-Ephemeris Covariance Matrix parameters", we use the same one

// Constants for SBAS DFMC orbit parameters
//position 0 is unused so constants can be reused
//define SATSLOTNUMBER							1	//It is already defined in "Constants for SBAS DFMC Clock-Ephemeris Covariance Matrix parameters", we use the same one
//position 2 is unused so constants can be reused
//#define DELTAX								3	//It is already defined in "Constants for SBAS long term satellite error corrections", we use the same one
//#define DELTAY								4	//It is already defined in "Constants for SBAS long term satellite error corrections", we use the same one
//#define DELTAZ								5	//It is already defined in "Constants for SBAS long term satellite error corrections", we use the same one
#define DELTAB									6  
//#define DELTAXRATEOFCHANGE					7   //It is already defined in "Constants for SBAS long term satellite error corrections", we use the same one
//#define DELTAYRATEOFCHANGE					8   //It is already defined in "Constants for SBAS long term satellite error corrections", we use the same one
//#define DELTAZRATEOFCHANGE					9   //It is already defined in "Constants for SBAS long term satellite error corrections", we use the same one
#define DELTABRATEOFCHANGE						10 
//#define TIMEOFDAYAPPLICABILITY				11  //It is already defined in "Constants for SBAS long term satellite error corrections", we use the same one
//#define IODNPOSITION							12	//It is already defined in "Constants for SBAS DFMC Clock-Ephemeris Covariance Matrix parameters", we use the same one
#define DFREIPOS                                13
#define RCORRMULT								14

// Constants for SBAS DFMC common OBAD parameters
#define IVALIDMT32								0
#define IVALIDMT3940							1
#define	CERMT37									2
#define CCOVARIANCEMT37							3
#define	TIMEREFID								4

// Constants for SBAS DFMC OBAD parameters
#define	ICORR									0
#define	CCORR									1
#define	RCORR									2

// Constants for SBAS DFMC DFREI parameters
#define DFREI0									0
#define DFREI1									1
#define DFREI2									2
#define DFREI3									3
#define DFREI4									4
#define DFREI5									5
#define DFREI6									6
#define DFREI7									7
#define DFREI8									8
#define DFREI9									9
#define DFREI10									10
#define DFREI11									11
#define DFREI12									12
#define DFREI13									13
#define DFREI14									14

// Constants for SBAS DFMC navigation message (part 1)
#define IODGNAVSBAS                             0
//define SATSLOTNUMBER                          1   //It is already defined in "Constants for SBAS DFMC Clock-Ephemeris Covariance Matrix parameters", we use the same one
#define	SBASPROVIDERID							2
#define	CUCNAVSBAS								3
#define	CUSNAVSBAS								4
#define	IDOTNAVSBAS								5
#define	PERIGREENAVSBAS							6
#define	ASCENDINGNAVSBAS						7
#define	ANOMALYNAVSBAS							8
#define	AXISNAVSBASV044							9	//When decoding MT39/40 with v<=0.4.4., semi-major axis is provided. In v>=0.5, it nod provided
#define	AGF0NAVSBAS								9	//Provided only when decoding with v>=0.5
#define AGF1NAVSBAS								10	//Provided only when decoding with v>=0.5

// Constants for SBAS DFMC navigation message (part 2)
//#define IODGNAVSBAS							0 //It is already defined in "Constants for SBAS DFMC navigation message (part 1)", we use the same one
#define	INCNAVSBAS								1
#define	ECCNAVSBAS								2
#define	AXISNAVSBAS								3
#define	EPHTIMENAVSBAS							4
#define	DFREINAVSBAS							5
#define	RCORRMULTNAVSBAS						6
#define	AGF0NAVSBASV044							7	//Provided only when decoding with v<=0.4.4
#define AGF1NAVSBASV044							8	//Provided only when decoding with v<=0.4.4

// Constants for SBAS DFMC GNSS Time offsets (common parameters)
//#define A1SNT									0	//It is already defined in "Constants for SBAS Network time parameters", we use the same one
//#define A0SNT									1	//It is already defined in "Constants for SBAS Network time parameters", we use the same one
//#define T0T									2	//It is already defined in "Constants for SBAS Network time parameters", we use the same one
//#define WNT									3	//It is already defined in "Constants for SBAS Network time parameters", we use the same one
//#define DELTATLS								4	//It is already defined in "Constants for SBAS Network time parameters", we use the same one
//#define WNLSF									5	//It is already defined in "Constants for SBAS Network time parameters", we use the same one
//#define DNDAY									6	//It is already defined in "Constants for SBAS Network time parameters", we use the same one
//#define DELTATLSF								7	//It is already defined in "Constants for SBAS Network time parameters", we use the same one
//#define UTCIDENTIFIER							8	//It is already defined in "Constants for SBAS Network time parameters", we use the same one

// Constants for SBAS DFMC GNSS Time offsets (constellation based parameters)
#define	VALIDITYIND								0
#define	TIMEOFFSETWRTSBAS						1

//Constants for SBAS DFMC message type version to decode
#define	MT37V044								0
#define	MT37V1									1

#define	MT3940V044								0
#define	MT3940V1								1

#define	MT42V071								0
#define	MT42V1									1

#define MT47V044								0
#define	MT47V1									1	

//Constants for SBAS DFMC GEO navigation message type
#define	NOSBASDFMCGEODATA						0
#define	SBASDFMCGEONAVIGATIONDATA				1
#define	SBASDFMCGEOALMANACDATA					2

// Constants for SBAS DFMC GEO almanacs
#define	BROADCASTIND							0
//#define SATSLOTNUMBER							1	//It is already defined in "Constants for SBAS DFMC Clock-Ephemeris Covariance Matrix parameters", we use the same one
//#define SBASPROVIDERID						2	//It is already defined in "Constants for SBAS DFMC navigation message (part 1)", we use the same one
#define	AXISALMANAC								3
#define	ECCALMANAC								4
#define	INCALMANAC								5
#define	PERIGREEALMANAC							6
#define	ASCENDINGAALMANAC						7
#define	ASCENSIONAALMANAC						8
#define	ANOMALYAALMANAC							9
#define	REFEPOCHALMANAC							10
#define	WNR0COUNTALMANAC						11


// Constants for file descriptor positions for SBAS files
#define fdRINEXB								0
#define fdEMS									1
#define fdMESSAGESEQUENCE						2
#define fdALARMMESSAGE							3
#define fdPRNMASK								4
#define fdFASTCORRECTIONS						5
#define fdINTEGRITY								6
#define fdFASTDEGRADATION						7
#define fdDEGRADATION							8
#define fdIONOSPHERICGRID						9
#define fdSLOWCORRECTIONS						10
#define fdIONOSPHERICCORRECTIONS				11
#define fdSERVICEREGION27						12
#define fdSERVICEREGION28						13
#define fdALMANAC								14
#define fdEPHEMERIS								15
#define fdLOGFILE								16
#define fdEPHEMERISPREVDAY						17

// Constants for user added errors parameters
#define NUMERRORFUNCTIONS						4
#define NUMWORDSSTEP							4
#define NUMWORDSRAMP							4
#define NUMWORDSSINUSOIDAL						6
#define NUMWORDSAWGN							4
#define STEP									0
#define RAMP									1
#define SINUSOIDAL								2
#define AWGN									3
#define NUMPARAMERRORS							3
#define AMPLITUDE								0
#define PERIOD									1
#define OFFSET									2
#define STDAWGN									0

// Constants for user added errors values
#define USRNUMPOS								17
#define USRGNSSPOS								0
#define USRPRNPOS								1
#define USRMEASPOS								2
#define USRFREQPOS								3
#define USRMEASRAWPOS							4
#define USRMEASTOTPOS							5
#define USRNUMTOTERRPOS							6
#define USRTOTERRPOS							7
#define USRNUMSTEPPOS							8
#define USRSTEPERRPOS							9
#define USRNUMRAMPPOS							10
#define USRRAMPERRPOS							11
#define USRNUMSINUPOS							12
#define USRSINUERRPOS							13
#define USRNUMAWGNPOS							14
#define USRAWGNERRPOS							15
#define USREPOCHPOS								16

// Definitions for DGNSS
#define BYTEBITS								8
#define READWORDSNO								10000
#define LEFTLIMIT								200
#define BYTEFORMATBIT							6
#define CONTENTBIT								24
#define PARITYBIT								6
#define WORDBIT									30
#define PREAMBLEBIT								8
#define MSGTYPEBIT								6
#define STATIONIDBIT							10
#define ZCOUNTBIT								13
#define SEQUENCENOBIT							3
#define DATAWORDNOBIT							5
#define STATIONHEALTHBIT						3
#define SATELLITEBIT							40


#define OPENMP_VERSION_4						201307 	//OpenMP 4.0 was released in July 2013 (07/2013), hence, OPENMP v4.0 is number 201307
 														//For a match between OpenMP version from Year/Month to their version number, see https://en.wikipedia.org/wiki/OpenMP#History


//Import max satellite PRN value variable

/****************************************************************
 * Declarations of enumerators
 ***************************************************************/

// Enumerator for measurment text parsing modes
enum parseMeasType {
	parsePrintMeasList=0,
	parseMeasTableList=1,
	parsecsSFmeas=2,
	parsecsMWmeas=3,
	parsecsLImeas=4,
	parsecsIGFmeas=5,
	parsecsSFfreq=6,
	parsecsMWfreq=7,
	parsecsLIfreq=8,
	parsecsIGFfreq=9,
	parseFiltermeas=10,
	parseSmoothFiltermeas=11,
	parseDopplermeas=12,
	parseWeightFiltermeas=13,
	parseWeightCombFiltermeas=14,
	parseWeightModeFiltermeas=15
};


// Enumerator for file types
enum fileType {
	ftINVALID,
	ftUNKNOWN,
	ftRINEXobservation,
	ftRINEXbroadcast,
	ftRINEXclocks,
	ftSINEX,
	ftIONEX,
	ftFPPP,
	ftConstellation,
	ftSP3,
	ftANTEX,
	ftGENDCB,
	ftP1C1DCB,
	ftP1P2DCB,
	ftRECEIVERTYPE,
	ftRINEXB,
	ftSBASEMSMESSAGE,
	ftSINEXBIASOSB,
	ftSINEXBIASDSB
};

// Enumerator for different GNSS systems
enum GNSSystem {
	Other = -1, //To force enum to be signed int, therefore avoiding warnings for comparing int with unsigned int
	GPS = 0,
	Galileo = 1,
	GLONASS = 2,
	GEO = 3,
	BDS = 4,
	QZSS = 5,
	IRNSS = 6
};

// Enumerator for different GNSS products type
enum ProductsType {
	UnknownProductType=-1,
	BRDC=0,
	SP3=1
};

//Enumeration for the different Broadcast messages type for GPS
enum BRDCtypeGPS {
	GPSLNAV  = 0,
	GPSCNAV = 1,
	GPSCNAV2 = 2,
	GPSCNAVANY = 3, //Any CNAV message type
	GPSANY   = 4	//Any type or user defined order
};

//Enumeration for the different Broadcast messages type for Galileo
enum BRDCtypeGal {
	GalFNAV = 0,
	GalINAVE1 = 1,
	GalINAVE5b = 2,
	GalINAVE1E5b = 3,
	GalCNAV = 4,		//Commercial service navigation message
	GalGNAV = 5,		//Public regulated service navigation message
	GalINAVANY = 6,		//Any type of Galileo GALINAVE1, GALINAVE5 and GALINAVE1E5
	GalANY = 7			//Any type or user defined order
};

//Enumeration for the different Broadcast messages type for GLONASS
enum BRDCtypeGLO {
	GLOFDMA = 0,
	GLOCDMA = 1,		//Future new message type for GLONASS with CDMA signals
	GLOANY = 2			//Any type or user defined order
};

//Enumeration for the different Broadcast messages type for BeiDou
enum BRDCtypeBDS {
	BDSD1 = 0,
	BDSD2 = 1,
	BDSCNAV1 = 2,
	BDSCNAV2 = 3,
	BDSDANY = 4,
	BDSCNAVANY =5,
	BDSANY = 6			//Any type or user defined order
};

//Enumeration for the different Broadcast messages type for QZSS
enum BRDCtypeQZS {
	QZSLNAV = 0,	
	QZSCNAV = 1,
	QZSCNAV2 = 2,
	QZSCNAVANY = 3,		//Any CNAV message type
	QZSANY = 4			//Any type or user defined order
};

//Enumeration for the different Broadcast messages type for IRNSS
enum BRDCtypeIRN {
	IRNCNAV = 0,
	IRNCNAVANY = 1,
	IRNANY = 2
};

//Enumeration for the different Broadcast messages type for IRNSS
enum BRDCtypeGEO {
	GEOCNAV = 0,
	GEOCNAVANY = 1,
	GEOANY = 2			//Any type or user defined order
};

enum GPSBrdcOptions {
	UnknownGPSBRDCPref = -1,
	PreferGPSLNAV = 0,
	PreferGPSCNAV = 1,
	PreferGPSCNAV2 = 2,
	GPSLNAVOnly = 3,
	GPSCNAVOnly = 4,
	GPSCNAV2Only = 5,
	GPSAnyCNAVOnly = 6,
	GPSUserDefined = 7,
	GPSLNAVvsCNAV = 8,
	GPSCNAVvsLNAV = 9,
	GPSLNAVvsCNAV2 = 10,
	GPSCNAV2vsLNAV = 11,
	GPSCNAVvsCNAV2 = 12,
	GPSCNAV2vsCNAV = 13
};

enum GALBrdcOptions {
	UnknownGalBRDCPref = -1,
	PreferGalINAV = 0,
	PreferGalFNAV = 1,
	PreferGalCNAV = 2,
	PreferGalGNAV = 3,
	GalINAVOnly = 4,
	GalINAVE1Only = 5,
	GalINAVE5bOnly = 6,
	GalINAVE1E5bOnly = 7,
	GalFNAVOnly = 8,
	GalCNAVOnly = 9,
	GalGNAVOnly = 10,
	GalUserDefined = 11,

	GalINAVvsFNAV = 12,
	GalFNAVvsINAV = 13,

	GalINAVvsCNAV = 14,
	GalCNAVvsINAV = 15,

	GalINAVvsGNAV = 16,
	GalGNAVvsINAV = 17,

	GalFNAVvsCNAV = 18,
	GalCNAVvsFNAV = 19,

	GalFNAVvsGNAV = 20,
	GalGNAVvsFNAV = 21,

	GalCNAVvsGNAV = 22,
	GalGNAVvsCNAV = 23
};

enum GLOBrdcOptions {
	UnknownGLOBRDCPref = -1,
	PreferGLOFDMA = 0,
	PreferGLOCDMA = 1,
	GLOFDMAOnly = 2,
	GLOCDMAOnly = 3,
	GLOUserDefined = 4,
	GLOFDMAvsCDMA = 5,
	GLOCDMAvsFDMA = 6
};

enum BDSBrdcOptions {
	UnknownBDSBRDCPref = -1,
	PreferBDSD1 = 0,
	PreferBDSD2 = 1,
	PreferBDSCNAV1 = 2,
	PreferBDSCNAV2 = 3,
	BDSD1Only = 4,
	BDSD2Only = 5,
	BDSCNAV1Only = 6,
	BDSCNAV2Only = 7,
	BDSUserDefined = 8,

	BDSD1vsD2 = 9,
	BDSD2vsD1 = 10,

	BDSD1vsCNAV1 = 11,
	BDSCNAV1vsD1 = 12,

	BDSD1vsCNAV2 = 13,
	BDSCNAV2vsD1 = 14,

	BDSD2vsCNAV1 = 15,
	BDSCNAV1vsD2 = 16,

	BDSD2vsCNAV2 = 17,
	BDSCNAV2vsD2 = 18,

	BDSCNAV1vsCNAV2 = 19,
	BDSCNAV2vsCNAV1 = 20
};

enum QZSSBrdcOptions {
	UnknownQZSSBRDCPref = -1,
	PreferQZSLNAV = 0,
	PreferQZSCNAV = 1,
	PreferQZSCNAV2 = 2,
	QZSLNAVOnly = 3,
	QZSCNAVOnly = 4,
	QZSCNAV2Only = 5,
	QZSAnyCNAVOnly = 6,
	QZSUserDefined = 7,
	QZSLNAVvsCNAV = 8,
	QZSCNAVvsLNAV = 9,
	QZSCNAV2vsLNAV = 10,
	QZSLNAVvsCNAV2 = 11,
	QZSCNAVvsCNAV2 = 12,
	QZSCNAV2vsCNAV = 13
};

enum IRNSSBrdcOptions {
	UnknownIRNSSBRDCPref = -1,
	IRNCNAVOnly = 0,
	IRNUserDefined = 1
};

enum GEOBrdcOptions {
	//SBAS 1F GEO navigation message and Almanac and SBAS DFMC GEO navigation message and Almanac
	//are not accounted here as they are used in SBAS 1F or SBAS DFMC mode respectively, ignoring
	//this options
	UnknownGEOBRDCPref = -1,
	GEOCNAVOnly = 0,
	GEOUserDefined = 1
};

//Enumeratior for health status in broadcast message
enum BRDCHealth {
	BRDCHealthy=0,
	BRDCMarginal=1,
	BRDCUnhealthy=2
};

//Enumerator for broadcast health selection modes
enum BRDCHealthSelModes {
	BRDCUseUndefined=-1,
	BRDCUseHealthyOnly=0,
	BRDCUseHealthyMarginal=1,
	BRDCUseAnyHealth=2
};

// Enumerator for different data sources
enum Source {
	UNKNOWN_SOURCE,
	RINEX2,
	RINEX3,
	RTCM3
};

//Enumerator for different time system corrections (Rinex Nav v3 header data)
enum TimeSystemCorrection {
	GPUT = 0,
	GAUT = 1,
	GLUT = 2,
	SBUT = 3,
	BDUT = 4,
	QZUT = 5,
	IRUT = 6,
	GAGP = 7,
	GLGP = 8,
	QZGP = 9,
	IRGP = 10,
	UNKNOWN_TIME_CORR = 11
};

// Enumerator for different satellite blocks
enum SatelliteBlock {
	UNKNOWN_BLOCK=0,
	GPS_BLOCK_I=1,
	GPS_BLOCK_II=2,
	GPS_BLOCK_IIA=3,
	GPS_BLOCK_IIR=4,
	GPS_BLOCK_IIRA=5,
	GPS_BLOCK_IIRB=6,
	GPS_BLOCK_IIRM=7,
	GPS_BLOCK_IIF=8,
	GPS_BLOCK_IIIA=9,
	GPS_BLOCK_IIIF=10,
	GLONASS_BLOCK=11,
	GLONASS_BLOCK_M=12,
	GLONASS_BLOCK_M2=13,//It is GLONASS_BLOCK_M+, but the + at the end confuses the compiler with "+="
	GLONASS_BLOCK_K1=14,
	GLONASS_BLOCK_K2=15,
	GLONASS_BLOCK_V=16,
	GALILEO_BLOCK_0A=17,
	GALILEO_BLOCK_0B=18,
	GALILEO_BLOCK_1=19,
	GALILEO_BLOCK_2=20,
	BEIDOU_BLOCK_2M=21,
	BEIDOU_BLOCK_2I=22,
	BEIDOU_BLOCK_2G=23,
	BEIDOU_BLOCK_3SI_CAST=24,
	BEIDOU_BLOCK_3SI_SECM=25,
	BEIDOU_BLOCK_3SM_CAST=26,
	BEIDOU_BLOCK_3SM_SECM=27,
	BEIDOU_BLOCK_3M_CAST=28,
	BEIDOU_BLOCK_3M_SECM=29,
	BEIDOU_BLOCK_3G_CAST=30,
	BEIDOU_BLOCK_3I=31,
	QZSS_BLOCK=32,
	QZSS_BLOCK_2G=33,
	QZSS_BLOCK_2I=34,
	IRNSS_BLOCK_1IGSO=35,
	IRNSS_BLOCK_1GEO=36
};

// Enumerator for ionospheric model
enum IonoModel {
	UNKNOWN_IM,
	NoIonoModel,
	KlobucharIonoModel,
	IONEXIonoModel,
	FPPPIonoModel,
	neQuickIonoModel,
	BeiDouIonoModel,
	SBASIonoModel
};

// Enumerators for troposheric model and mapping
enum TropModelNominal {
	UNKNOWN_TMNominal,
	SimpleNominal,
	UNB3Nominal,
	TropoGalileo
};
enum TropModelMapping {
	UNKNOWN_TMMapping,
	SimpleMapping,
	NiellMapping
};


// Enumerator for P1C1 DCB model
enum GPSP1C1DCBModel {
	GPSp1c1UNKNOWN,
	GPSp1c1NONE,
	GPSp1c1FLEXIBLE,
	GPSp1c1STRICT
};

// Enumerator for Generic DCB (any DCB type) model
enum GenericDCBModel {
	DCBUNKNOWN,
	DCBNONE,
	DCBRINEX,
	DCBFILE,
	DCBIONEX,
	DCBFPPP,
};

// Enumerator for Absolute DCB model
enum OSBDCBModel {
	OSBUNKNOWN,
	OSBNONE,
	OSBRINEX,
	OSBSINEXBIAS
};

// Enumerator for MultiConstellation DCB measurement conversion
enum DSBDCBModel {
	DSBUNKNOWN,
	DSBNONE,
	DSBSINEXBIAS
};

enum SINEXBIASDataType {
	SINEXBIASUNKNOWN,
	SINEXBIASOSB,
	SINEXBIASDSB
};
		

// Enumerator for receiver type
enum ReceiverType {
	rtNA = 0,
	rtUNKNOWN = 1,
	rtCROSS = 2,
	rtNOP1 = 3,
	rtNOMINAL = 4
};

// Enumerator for SNR check types
enum SNRCheckType {
	NoSNRCheck,
	SNRCheckMin,
	SNRCheckMax,
	SNRCheckMinMax
};

//Enumerator for SBAS data modes
enum SBASdataModes {
	NoSBASdata = 0,
	SBASionoOnly = 1,
	SBAS1Fused = 2,
	SBASDFMCused = 3,
	SBASMaps1freqUsed = 4,
	SBASMapsDFMCused = 5
};

//Enumerator for cycle-slip data gap set modes
enum csDataGapSizeModes {
	csDataGapSizeDefault,
	csDataGapSizeUser,
	csDataGapSizeAuto	
};
	

// Enumerator for different measurements
enum MeasurementType {
	NA = 0,					// N/A
	C1A =  1, L1A =  2, D1A =  3, S1A =  4, // GAL/BDS           A PRS | B1A                        @ E1/B1
	C1B =  5, L1B =  6, D1B =  7, S1B =  8, // GAL/QZSS          B I/NAV OS/CS/SoL | L1Sb           @ E1/L1
	C1C =  9, L1C = 10, D1C = 11, S1C = 12, // GP/GL/GA/SB/QZ    C/A | C no data                    @ L1/G1/E1 (Glonass signal is FDMA)
	C1D = 13, L1D = 14, D1D = 15, S1D = 16, // BDS               Data                               @ B1
	C1E = 17, L1E = 18, D1E = 19, S1E = 20, // Inexistent, left space in case in the future this signal is added
	C1S = 21, L1S = 22, D1S = 23, S1S = 24, // GP/QZ             L1C (D)                            @ L1/Q1
	C1L = 25, L1L = 26, D1L = 27, S1L = 28, // GP/QZ             L1P (D)                            @ L1/Q1
	C1I = 29, L1I = 30, D1I = 31, S1I = 32, // BD                I                                  @ B1
	C1Q = 33, L1Q = 34, D1Q = 35, S1Q = 36, // BD                Q                                  @ B1
	C1X = 37, L1X = 38, D1X = 39, S1X = 40, // GP/GA/BD/QZSS     L1C (D+P)| B+C | Data+Pilot        @ L1/E1/B1
	C1P = 41, L1P = 42, D1P = 43, S1P = 44, // GP/GL/BDS         P (AS off) | P | Pilot             @ L1/G1/B1 (Glonass signal is FDMA)
	C1W = 45, L1W = 46, D1W = 47, S1W = 48, // GPS               Z-tracking (AS on)                 @ L1
	C1Y = 49, L1Y = 50, D1Y = 51, S1Y = 52, // GPS               Y                                  @ L1
	C1Z = 53, L1Z = 54, D1Z = 55, S1Z = 56, // GAL/QZSS          A+B+C | L1S/L1-SAIF                @ E1/L1
	C1M = 57, L1M = 58, D1M = 59, S1M = 60, // GPS               M                                  @ L1
			  L1N = 62, D1N = 63, S1N = 64, // GPS/BDS           Codeless                           @ L1/B1

	C2A = 65, L2A = 66, D2A = 67, S2A = 68, // Inexistent, left space in case in the future this signal is added
	C2B = 69, L2B = 70, D2B = 71, S2B = 72, // Inexistent, left space in case in the future this signal is added
	C2C = 73, L2C = 74, D2C = 75, S2C = 76, // GP/GL             C/A | C/A (GLONASS M)              @ L2/G2 (Glonass signal is FDMA)
	C2D = 77, L2D = 78, D2D = 79, S2D = 80, // GPS               L1(C/A)+(P2-P1)                    @ L2
	C2E = 81, L2E = 82, D2E = 83, S2E = 84, // Inexistent, left space in case in the future this signal is added
	C2S = 85, L2S = 86, D2S = 87, S2S = 88, // GPS/QZSS          L2C (M)                            @ L2
	C2L = 89, L2L = 90, D2L = 91, S2L = 92, // GPS/QZSS          L2C (L)                            @ L2
	C2I = 93, L2I = 94, D2I = 95, S2I = 96, // BDS               I                                  @ B1-2 
	C2Q = 97, L2Q = 98, D2Q = 99, S2Q =100, // BDS               I+Q                                @ B1-2  
	C2X =101, L2X =102, D2X =103, S2X =104, // GPS/BDS/QZS       L2C (M+L) | I+Q                    @ L2/B1-2
	C2P =105, L2P =106, D2P =107, S2P =108, // GP/GL             P (AS off) | P                     @ L2/G2 (Glonass signal is FDMA)
	C2W =109, L2W =110, D2W =111, S2W =112, // GPS               Z (AS on)                          @ L2
	C2Y =113, L2Y =114, D2Y =115, S2Y =116, // GPS               Y                                  @ L2
	C2Z =117, L2Z =118, D2Z =119, S2Z =120, // Inexistent, left space in case in the future this signal is added
	C2M =121, L2M =122, D2M =123, S2M =124, // GPS               M                                  @ L2
			  L2N =126, D2N =127, S2N =128, // GPS               codeless                           @ L2

	C3A =129, L3A =130, D3A =131, S3A =132, // Inexistent, left space in case in the future this signal is added
	C3B =133, L3B =134, D3B =135, S3B =136, // Inexistent, left space in case in the future this signal is added
	C3C =137, L3C =138, D3C =139, S3C =140, // Inexistent, left space in case in the future this signal is added
	C3D =141, L3D =142, D3D =143, S3D =144, // Inexistent, left space in case in the future this signal is added
	C3E =145, L3E =146, D3E =147, S3E =148, // Inexistent, left space in case in the future this signal is added
	C3S =149, L3S =150, D3S =151, S3S =152, // Inexistent, left space in case in the future this signal is added
	C3L =153, L3L =154, D3L =155, S3L =156, // Inexistent, left space in case in the future this signal is added
	C3I =157, L3I =158, D3I =159, S3I =160, // Glonass           I                                  @ G3 (Glonass signal is CDMA) 
	C3Q =161, L3Q =162, D3Q =163, S3Q =164, // Glonass           Q                                  @ G3 (Glonass signal is CDMA) 
	C3X =165, L3X =166, D3X =167, S3X =168, // Glonass           I+Q                                @ G3 (Glonass signal is CDMA)
	C3P =169, L3P =170, D3P =171, S3P =172, // Inexistent, left space in case in the future this signal is added
	C3W =173, L3W =174, D3W =175, S3W =176, // Inexistent, left space in case in the future this signal is added
	C3Y =177, L3Y =178, D3Y =179, S3Y =180, // Inexistent, left space in case in the future this signal is added
	C3Z =181, L3Z =182, D3Z =183, S3Z =184, // Inexistent, left space in case in the future this signal is added
	C3M =185, L3M =186, D3M =187, S3M =188, // Inexistent, left space in case in the future this signal is added
			  L3N =190, D3N =191, S3N =192, // Inexistent, left space in case in the future this signal is added

	C4A =193, L4A =194, D4A =195, S4A =196, // GLONASS           L1OCd                              @ G1a (Glonass signal is CDMA)
	C4B =197, L4B =198, D4B =199, S4B =200, // GLONASS           L1OCp                              @ G1a (Glonass signal is CDMA)
	C4C =201, L4C =202, D4C =203, S4C =204, // Inexistent, left space in case in the future this signal is added
	C4D =205, L4D =206, D4D =207, S4D =208, // Inexistent, left space in case in the future this signal is added
	C4E =209, L4E =210, D4E =211, S4E =212, // Inexistent, left space in case in the future this signal is added
	C4S =213, L4S =214, D4S =215, S4S =216, // Inexistent, left space in case in the future this signal is added
	C4L =217, L4L =218, D4L =219, S4L =220, // Inexistent, left space in case in the future this signal is added
	C4I =221, L4I =222, D4I =223, S4I =224, // Inexistent, left space in case in the future this signal is added
	C4Q =225, L4Q =226, D4Q =227, S4Q =228, // Inexistent, left space in case in the future this signal is added
	C4X =229, L4X =230, D4X =231, S4X =232, // GLONASS           L1OCd+L1OCp                        @ G1a (Glonass signal is CDMA)
	C4P =233, L4P =234, D4P =235, S4P =236, // Inexistent, left space in case in the future this signal is added
	C4W =237, L4W =238, D4W =239, S4W =240, // Inexistent, left space in case in the future this signal is added
	C4Y =241, L4Y =242, D4Y =243, S4Y =244, // Inexistent, left space in case in the future this signal is added
	C4Z =245, L4Z =246, D4Z =247, S4Z =248, // Inexistent, left space in case in the future this signal is added
	C4M =249, L4M =250, D4M =251, S4M =252, // Inexistent, left space in case in the future this signal is added
			  L4N =254, D4N =255, S4N =256, // Inexistent, left space in case in the future this signal is added

	C5A =257, L5A =258, D5A =259, S5A =260, // IRNSS             A SPS                              @ L5    
	C5B =261, L5B =262, D5B =263, S5B =264, // IRNSS             B RS (D)                           @ L5
	C5C =265, L5C =266, D5C =267, S5C =268, // IRNSS             C RS (P)                           @ L5
	C5D =269, L5D =270, D5D =271, S5D =272, // BDS/QZSS          Data | L5S(I) (Block II L5S)       @ L5/B2a
	C5E =273, L5E =274, D5E =275, S5E =276, // Inexistent, left space in case in the future this signal is added
	C5S =277, L5S =278, D5S =279, S5S =280, // Inexistent, left space in case in the future this signal is added
	C5L =281, L5L =282, D5L =283, S5L =284, // Inexistent, left space in case in the future this signal is added
	C5I =285, L5I =286, D5I =287, S5I =288, // GP/GA/SB/QZ       I | I F/NAV OS | I (Block I)       @ L5/E5a
	C5Q =289, L5Q =290, D5Q =291, S5Q =292, // GP/GA/SB/QZ       Q | Q no data | Q (Block I)        @ L5/E5a
	C5X =293, L5X =294, D5X =295, S5X =296, // GP/GA/SB/BD/QZ/IR I+Q | Data + Pilot | B+C           @ L5/E5a/B2a
	C5P =297, L5P =298, D5P =299, S5P =300, // BDS/QZSS          L5S(Q) (Block II) | Pilot           @ L5/B2a 
	C5W =301, L5W =302, D5W =303, S5W =304, // Inexistent, left space in case in the future this signal is added
	C5Y =305, L5Y =306, D5Y =307, S5Y =308, // Inexistent, left space in case in the future this signal is added
	C5Z =309, L5Z =310, D5Z =311, S5Z =312, // QZSS              L5S(I+Q) (Block II)                @ L5 
	C5M =313, L5M =314, D5M =315, S5M =316, // Inexistent, left space in case in the future this signal is added
			  L5N =318, D5N =319, S5N =320, // Inexistent, left space in case in the future this signal is added

	C6A =321, L6A =322, D6A =323, S6A =324, // GLO/GAL/BDS       L2CSI | A PRS | B3A                @ G2a/E6/B3 (Glonass signal is CDMA)
	C6B =325, L6B =326, D6B =327, S6B =328, // GLO/GAL           L2OCp | B C/NAV CS                 @ G2a/E6/B3 (Glonass signal is CDMA)
	C6C =329, L6C =330, D6C =331, S6C =332, // GAL               C no data                          @ E6
	C6D =333, L6D =334, D6D =335, S6D =336, // Inexistent, left space in case in the future this signal is added
	C6E =337, L6E =338, D6E =339, S6E =340, // QZSS              L6E (Block II)                     @ L6
	C6S =341, L6S =342, D6S =343, S6S =344, // QZSS              L6D (Block I LEX/Block II)         @ L6
	C6L =345, L6L =346, D6L =347, S6L =348, // QZSS              L6P (Block I LEX)                  @ L6
	C6I =349, L6I =350, D6I =351, S6I =352, // BDS               I                                  @ B3
	C6Q =353, L6Q =354, D6Q =355, S6Q =356, // BDS               Q                                  @ B3
	C6X =357, L6X =358, D6X =359, S6X =360, // GLO/GAL/QZS/BDS   L2CSI+L2OCp | B+C | L5(D+P) | I+Q  @ G2a/E6/L6/B3 (Glonass signal is CDMA)
	C6P =361, L6P =362, D6P =363, S6P =364, // Inexistent, left space in case in the future this signal is added
	C6W =365, L6W =366, D6W =367, S6W =368, // Inexistent, left space in case in the future this signal is added
	C6Y =369, L6Y =370, D6Y =371, S6Y =372, // Inexistent, left space in case in the future this signal is added
	C6Z =373, L6Z =374, D6Z =375, S6Z =376, // GAL/QZSS          A+B+C | L6(D+E) (Block II)         @ E6/L6
	C6M =377, L6M =378, D6M =379, S6M =380, // Inexistent, left space in case in the future this signal is added
			  L6N =382, D6N =383, S6N =384, // Inexistent, left space in case in the future this signal is added

	C7A =385, L7A =386, D7A =387, S7A =388, // Inexistent, left space in case in the future this signal is added
	C7B =389, L7B =390, D7B =391, S7B =392, // Inexistent, left space in case in the future this signal is added
	C7C =393, L7C =394, D7C =395, S7C =396, // Inexistent, left space in case in the future this signal is added
	C7D =397, L7D =398, D7D =399, S7D =400, // BDS               Data                               @ B2b 
	C7E =401, L7E =402, D7E =403, S7E =404, // Inexistent, left space in case in the future this signal is added
	C7S =405, L7S =406, D7S =407, S7S =408, // Inexistent, left space in case in the future this signal is added
	C7L =409, L7L =410, D7L =411, S7L =412, // Inexistent, left space in case in the future this signal is added
	C7I =413, L7I =414, D7I =415, S7I =416, // GAL/BDS           I I/NAV OS/CS/SoL | I              @ E5b/B2b
	C7Q =417, L7Q =418, D7Q =419, S7Q =420, // GAL/BDS           Q no data | Q                      @ E5b/B2b
	C7X =421, L7X =422, D7X =423, S7X =424, // GAL/BDS           I+Q                                @ E5b/B2b
	C7P =425, L7P =426, D7P =427, S7P =428, // BDS               Pilot                              @ B2b
	C7W =429, L7W =430, D7W =431, S7W =432, // Inexistent, left space in case in the future this signal is added
	C7Y =433, L7Y =434, D7Y =435, S7Y =436, // Inexistent, left space in case in the future this signal is added
	C7Z =437, L7Z =438, D7Z =439, S7Z =440, // BDS               Data + Pilot                       @ B2b
	C7M =441, L7M =442, D7M =443, S7M =444, // Inexistent, left space in case in the future this signal is added
			  L7N =446, D7N =447, S7N =448, // Inexistent, left space in case in the future this signal is added

	C8A =449, L8A =450, D8A =451, S8A =452, // Inexistent, left space in case in the future this signal is added
	C8B =453, L8B =454, D8B =455, S8B =456, // Inexistent, left space in case in the future this signal is added
	C8C =457, L8C =458, D8C =459, S8C =460, // Inexistent, left space in case in the future this signal is added
	C8D =461, L8D =462, D8D =463, S8D =464, // BDS               Data                               @ B2 (B2a+B2b)
	C8E =465, L8E =466, D8E =467, S8E =468, // Inexistent, left space in case in the future this signal is added
	C8S =469, L8S =470, D8S =471, S8S =472, // Inexistent, left space in case in the future this signal is added
	C8L =473, L8L =474, D8L =475, S8L =476, // Inexistent, left space in case in the future this signal is added
	C8I =477, L8I =478, D8I =479, S8I =480, // GAL               I                                  @ E5 (E5a+E5b)
	C8Q =481, L8Q =482, D8Q =483, S8Q =484, // GAL               Q                                  @ E5 (E5a+E5b)
	C8X =485, L8X =486, D8X =487, S8X =488, // GAL/BDS           I+Q  | Data + Pilot                @ E5 (E5a+E5b)/B2 (B2a+B2b)
	C8P =489, L8P =490, D8P =491, S8P =492, // BDS               Pilot                              @ B2 (B2a+B2b)
	C8W =493, L8W =494, D8W =495, S8W =496, // Inexistent, left space in case in the future this signal is added
	C8Y =497, L8Y =498, D8Y =499, S8Y =500, // Inexistent, left space in case in the future this signal is added
	C8Z =501, L8Z =502, D8Z =503, S8Z =504, // Inexistent, left space in case in the future this signal is added
	C8M =505, L8M =506, D8M =507, S8M =508, // Inexistent, left space in case in the future this signal is added
			  L8N =510, D8N =511, S8N =512, // Inexistent, left space in case in the future this signal is added

	C9A =513, L9A =514, D9A =515, S9A =516, // IRNSS             A SPS                              @ S
	C9B =517, L9B =518, D9B =519, S9B =520, // IRNSS             B RS (D)                           @ S
	C9C =521, L9C =522, D9C =523, S9C =524, // IRNSS             C RS (P)                           @ S
	C9D =525, L9D =526, D9D =527, S9D =528, // Inexistent, left space in case in the future this signal is added
	C9E =529, L9E =530, D9E =531, S9E =532, // Inexistent, left space in case in the future this signal is added
	C9S =533, L9S =534, D9S =535, S9S =536, // Inexistent, left space in case in the future this signal is added
	C9L =537, L9L =538, D9L =539, S9L =540, // Inexistent, left space in case in the future this signal is added
	C9I =541, L9I =542, D9I =543, S9I =544, // Inexistent, left space in case in the future this signal is added
	C9Q =545, L9Q =546, D9Q =547, S9Q =548, // Inexistent, left space in case in the future this signal is added
	C9X =549, L9X =550, D9X =551, S9X =552, // IRNSS             B+C                                @ S
	C9P =553, L9P =554, D9P =555, S9P =556, // Inexistent, left space in case in the future this signal is added
	C9W =557, L9W =558, D9W =559, S9W =560, // Inexistent, left space in case in the future this signal is added
	C9Y =561, L9Y =562, D9Y =563, S9Y =564, // Inexistent, left space in case in the future this signal is added
	C9Z =565, L9Z =566, D9Z =567, S9Z =568, // Inexistent, left space in case in the future this signal is added
	C9M =569, L9M =570, D9M =571, S9M =572, // Inexistent, left space in case in the future this signal is added
			  L9N =574, D9N =575, S9N =576, // Inexistent, left space in case in the future this signal is added

	C0A =577, L0A =578, D0A =579, S0A =580, // Inexistent, left space in case in the future this signal is added
	C0B =581, L0B =582, D0B =583, S0B =584, // Inexistent, left space in case in the future this signal is added
	C0C =585, L0C =586, D0C =587, S0C =588, // Inexistent, left space in case in the future this signal is added
	C0D =589, L0D =590, D0D =591, S0D =592, // Inexistent, left space in case in the future this signal is added
	C0E =593, L0E =594, D0E =595, S0E =596, // Inexistent, left space in case in the future this signal is added
	C0S =597, L0S =598, D0S =599, S0S =600, // Inexistent, left space in case in the future this signal is added
	C0L =601, L0L =602, D0L =603, S0L =604, // Inexistent, left space in case in the future this signal is added
	C0I =605, L0I =606, D0I =607, S0I =608, // Inexistent, left space in case in the future this signal is added
	C0Q =609, L0Q =610, D0Q =611, S0Q =612, // Inexistent, left space in case in the future this signal is added
	C0X =613, L0X =614, D0X =615, S0X =616, // Inexistent, left space in case in the future this signal is added
	C0P =617, L0P =618, D0P =619, S0P =620, // Inexistent, left space in case in the future this signal is added
	C0W =621, L0W =622, D0W =623, S0W =624, // Inexistent, left space in case in the future this signal is added
	C0Y =625, L0Y =626, D0Y =627, S0Y =628, // Inexistent, left space in case in the future this signal is added
	C0Z =629, L0Z =630, D0Z =631, S0Z =632, // Inexistent, left space in case in the future this signal is added
	C0M =633, L0M =634, D0M =635, S0M =636, // Inexistent, left space in case in the future this signal is added
			  L0N =638, D0N =639, S0N =640, // Inexistent, left space in case in the future this signal is added

	//Ionosphere measurements (they are given in carrier phase cycles)
	I1 =641,
	I2 =642,
	I3 =643,
	I4 =644,
	I5 =645,
	I6 =646,
	I7 =647,
	I8 =648,
	I9 =649,
	I0 =650,

	//Receiver channel numbers
	X1 =651,
	X2 =652,
	X3 =653,
	X4 =654,
	X5 =655,
	X6 =656,
	X7 =657,
	X8 =658,
	X9 =659,
	X0 =660,
	
	//Old combinations format for GPS (for maintaining compatibility with previous versions). 
	//If these are set, after reading, it will change to the combination with frequencies 1 and 2 (for instance PC->PC12)
	ENDMEAS = 661,		// Internal marker for combinations
	PN  = 662,			// GPS         Narrow-lane pseudorange combination (f1*P1+f2*P2)/(f1+f2)
	PI  = 663,			// GPS         Ionospheric pseudorange combination (P2-P1)
	PC  = 664,			// GPS         Ionospheric-free pseudorange combination (f1^2*P1-f2^2*P2)/(f1^2-f2^2)
	PCC = 665,			// GPS         Ionospheric-free pseudorange combination (f1^2*C1-f2^2*P2)/(f1^2-f2^2)
	LW  = 666,			// GPS         Wide-lane carrier-phase combination (f1*L1-f2*L2)/(f1-f2)
	LI  = 667,			// GPS         Ionospheric carrier-phase combination (L1-L2)
	LC  = 668,			// GPS         Ionospheric-free carrier-phase combination (f1^2*L1-f2^2*L2)/(f1^2-f2^2)
	MW  = 669,			// GPS         Melbourne-Wübbena combination (LW-PN)
	IF  = 670,			// GPS         Ionospheric-free combination 
	DF  = 671,			// GPS         Divergence Free L1 + 2/((f1/f2)^2-1) * (L1-L2)

	//GRAPHIC combinations between Code and Phase (C1+L1)/2
	G1 = 672,
	G2 = 673,
	G3 = 674,
	G4 = 675,
	G5 = 676,
	G6 = 677,
	G7 = 678,
	G8 = 679,
	G9 = 680,
	G0 = 681,

	// All possible combinations (frequencies cannot be combined with themselves, and order is not important)
	// Blank spaces are left in not possible combinations, so when reading number or converting back to text it is easy to detect which frequencies are used
	//Narrow-lane pseudorange combination (f1*P1+f2*P2)/(f1+f2)
	PN12 = 682,		PN13 = 683,		PN14 = 684,     PN15 = 685,     PN16 = 686,     PN17 = 687,     PN18 = 688,     PN19 = 689,     PN10 = 690,
					PN23 = 691,		PN24 = 692,     PN25 = 693,     PN26 = 694,     PN27 = 695,     PN28 = 696,     PN29 = 697,		PN20 = 698,
									PN34 = 699,     PN35 = 700,     PN36 = 701,     PN37 = 702,     PN38 = 703,     PN39 = 704,     PN30 = 705,
													PN45 = 706,     PN46 = 707,     PN47 = 708,     PN48 = 709,     PN49 = 710,     PN40 = 711,
																	PN56 = 712,     PN57 = 713,     PN58 = 714,     PN59 = 715,     PN50 = 716,
																					PN67 = 717,     PN68 = 718,     PN69 = 719,     PN60 = 720,
																									PN78 = 721,     PN79 = 722,		PN70 = 723,
																													PN89 = 724,		PN80 = 725,
																																	PN90 = 726,

	//Ionospheric pseudorange combination (P2-P1)
	PI12 = 727,		PI13 = 728,		PI14 = 729,     PI15 = 730,     PI16 = 731,     PI17 = 732,     PI18 = 733,     PI19 = 734,     PI10 = 735,
					PI23 = 736,		PI24 = 737,     PI25 = 738,     PI26 = 739,     PI27 = 740,     PI28 = 741,     PI29 = 742,		PI20 = 743,
									PI34 = 744,     PI35 = 745,     PI36 = 746,     PI37 = 747,     PI38 = 748,     PI39 = 749,     PI30 = 750,
													PI45 = 751,     PI46 = 752,     PI47 = 753,     PI48 = 754,     PI49 = 755,     PI40 = 756,
																	PI56 = 757,     PI57 = 758,     PI58 = 759,     PI59 = 760,     PI50 = 761,
																					PI67 = 762,     PI68 = 763,     PI69 = 764,     PI60 = 765,
																									PI78 = 766,     PI79 = 767,		PI70 = 768,
																													PI89 = 769,		PI80 = 770,
																																	PI90 = 771,

	//Ionospheric-free pseudorange combination (f1^2*P1-f2^2*P2)/(f1^2-f2^2)
	PC12 = 772,		PC13 = 773,		PC14 = 774,     PC15 = 775,     PC16 = 776,     PC17 = 777,     PC18 = 778,     PC19 = 779,     PC10 = 780,
					PC23 = 781,		PC24 = 782,     PC25 = 783,     PC26 = 784,     PC27 = 785,     PC28 = 786,     PC29 = 787,		PC20 = 788,
									PC34 = 789,     PC35 = 790,     PC36 = 791,     PC37 = 792,     PC38 = 793,     PC39 = 794,     PC30 = 795,
													PC45 = 796,     PC46 = 797,     PC47 = 798,     PC48 = 799,     PC49 = 800,     PC40 = 801,
																	PC56 = 802,     PC57 = 803,     PC58 = 804,     PC59 = 805,     PC50 = 806,
																					PC67 = 807,     PC68 = 808,     PC69 = 809,     PC60 = 810,
																									PC78 = 811,     PC79 = 812,		PC70 = 813,
																													PC89 = 814,		PC80 = 815,
																																	PC90 = 816,

	//Wide-lane carrier-phase combination (f1*L1-f2*L2)/(f1-f2)
	LW12 = 817,		LW13 = 818,		LW14 = 819,     LW15 = 820,     LW16 = 821,     LW17 = 822,     LW18 = 823,     LW19 = 824,     LW10 = 825,
					LW23 = 826,		LW24 = 827,     LW25 = 828,     LW26 = 829,     LW27 = 830,     LW28 = 831,     LW29 = 832,		LW20 = 833,
									LW34 = 834,     LW35 = 835,     LW36 = 836,     LW37 = 837,     LW38 = 838,     LW39 = 839,     LW30 = 840,
													LW45 = 841,     LW46 = 842,     LW47 = 843,     LW48 = 844,     LW49 = 845,     LW40 = 846,
																	LW56 = 847,     LW57 = 848,     LW58 = 849,     LW59 = 850,     LW50 = 851,
																					LW67 = 852,     LW68 = 853,     LW69 = 854,     LW60 = 855,
																									LW78 = 856,     LW79 = 857,		LW70 = 858,
																													LW89 = 859,		LW80 = 860,
																																	LW90 = 861,

	//Geometry-free carrier-phase combination (L1-L2)
	LI12 = 862,		LI13 = 863,		LI14 = 864,     LI15 = 865,     LI16 = 866,     LI17 = 867,     LI18 = 868,     LI19 = 869,     LI10 = 870,
					LI23 = 871,		LI24 = 872,     LI25 = 873,     LI26 = 874,     LI27 = 875,     LI28 = 876,     LI29 = 877,		LI20 = 878,
									LI34 = 879,     LI35 = 880,     LI36 = 881,     LI37 = 882,     LI38 = 883,     LI39 = 884,     LI30 = 885,
													LI45 = 886,     LI46 = 887,     LI47 = 888,     LI48 = 889,     LI49 = 890,     LI40 = 891,
																	LI56 = 892,     LI57 = 893,     LI58 = 894,     LI59 = 895,     LI50 = 896,
																					LI67 = 897,     LI68 = 898,     LI69 = 899,     LI60 = 900,
																									LI78 = 901,     LI79 = 902,		LI70 = 903,
																													LI89 = 904,		LI80 = 905,
																																	LI90 = 906,

	//Ionospheric-free carrier-phase combination (f1^2*L1-f2^2*L2)/(f1^2-f2^2)
	LC12 = 907,		LC13 = 908,		LC14 = 909,     LC15 = 910,     LC16 = 911,     LC17 = 912,     LC18 = 913,     LC19 = 914,     LC10 = 915,
					LC23 = 916,		LC24 = 917,     LC25 = 918,     LC26 = 919,     LC27 = 920,     LC28 = 921,     LC29 = 922,		LC20 = 923,
									LC34 = 924,     LC35 = 925,     LC36 = 926,     LC37 = 927,     LC38 = 928,     LC39 = 929,     LC30 = 930,
													LC45 = 931,     LC46 = 932,     LC47 = 933,     LC48 = 934,     LC49 = 935,     LC40 = 936,
																	LC56 = 937,     LC57 = 938,     LC58 = 939,     LC59 = 940,     LC50 = 941,
																					LC67 = 942,     LC68 = 943,     LC69 = 944,     LC60 = 945,
																									LC78 = 946,     LC79 = 947,		LC70 = 948,
																													LC89 = 949,		LC80 = 950,
																																	LC90 = 951,

	//Melbourne-Wübbena combination (LW-PN)
	MW12 = 952,		MW13 = 953,		MW14 = 954,     MW15 = 955,     MW16 = 956,     MW17 = 957,     MW18 = 958,     MW19 = 959,     MW10 = 960,
					MW23 = 961,		MW24 = 962,     MW25 = 963,     MW26 = 964,     MW27 = 965,     MW28 = 966,     MW29 = 967,		MW20 = 968,
									MW34 = 969,     MW35 = 970,     MW36 = 971,     MW37 = 972,     MW38 = 973,     MW39 = 974,     MW30 = 975,
													MW45 = 976,     MW46 = 977,     MW47 = 978,     MW48 = 979,     MW49 = 980,     MW40 = 981,
																	MW56 = 982,     MW57 = 983,     MW58 = 984,     MW59 = 985,     MW50 = 986,
																					MW67 = 987,     MW68 = 988,     MW69 = 989,     MW60 = 990,
																									MW78 = 991,     MW79 = 992,		MW70 = 993,
																													MW89 = 994,		MW80 = 995,
																																	MW90 = 996,

	//Ionosphere Free for pseudorange, carrier phase or Doppler (f1^2*L1-f2^2*L2)/(f1^2-f2^2)
	IF12 = 997,		IF13 = 998,		IF14 = 999,     IF15 =1000,     IF16 =1001,     IF17 =1002,     IF18 =1003,     IF19 =1004,     IF10 =1005,
					IF23 =1006,		IF24 =1007,     IF25 =1008,     IF26 =1009,     IF27 =1010,     IF28 =1011,     IF29 =1012,		IF20 =1013,
									IF34 =1014,     IF35 =1015,     IF36 =1016,     IF37 =1017,     IF38 =1018,     IF39 =1019,     IF30 =1020,
													IF45 =1021,     IF46 =1022,     IF47 =1023,     IF48 =1024,     IF49 =1025,     IF40 =1026,
																	IF56 =1027,     IF57 =1028,     IF58 =1029,     IF59 =1030,     IF50 =1031,
																					IF67 =1032,     IF68 =1033,     IF69 =1034,     IF60 =1035,
																									IF78 =1036,     IF79 =1037,		IF70 =1038,
																													IF89 =1039,		IF80 =1040,
																																	IF90 =1041,
	//Divergence Free L1 + 2/((f1/f2)^2-1) * (L1-L2)
	DF12 =1042,		DF13 =1043,		DF14 =1044,     DF15 =1045,     DF16 =1046,     DF17 =1047,     DF18 =1048,     DF19 =1049,     DF10 =1050,
					DF23 =1051,		DF24 =1052,     DF25 =1053,     DF26 =1054,     DF27 =1055,     DF28 =1056,     DF29 =1057,		DF20 =1058,
									DF34 =1059,     DF35 =1060,     DF36 =1061,     DF37 =1062,     DF38 =1063,     DF39 =1064,     DF30 =1065,
													DF45 =1066,     DF46 =1067,     DF47 =1068,     DF48 =1069,     DF49 =1070,     DF40 =1071,
																	DF56 =1072,     DF57 =1073,     DF58 =1074,     DF59 =1075,     DF50 =1076,
																					DF67 =1077,     DF68 =1078,     DF69 =1079,     DF60 =1080,
																									DF78 =1081,     DF79 =1082,		DF70 =1083,
																													DF89 =1084,		DF80 =1085,
																																	DF90 =1086,
	//Divergence Free L2 + 2/((f2/f1)^2-1) * (L2-L1). Note that DF12 is different than DF21
	DF21 =1087,		DF31 =1088,		DF41 =1089,     DF51 =1090,     DF61 =1091,     DF71 =1092,     DF81 =1093,     DF91 =1094,     DF01 =1095,
					DF32 =1096,		DF42 =1097,     DF52 =1098,     DF62 =1099,     DF72 =1100,     DF82 =1101,     DF92 =1102,		DF02 =1103,
									DF43 =1104,     DF53 =1105,     DF63 =1106,     DF73 =1107,     DF83 =1108,     DF93 =1109,     DF03 =1110,
													DF54 =1111,     DF64 =1112,     DF74 =1113,     DF84 =1114,     DF94 =1115,     DF04 =1116,
																	DF65 =1117,     DF75 =1118,     DF85 =1119,     DF95 =1120,     DF05 =1121,
																					DF76 =1122,     DF86 =1123,     DF96 =1124,     DF06 =1125,
																									DF87 =1126,     DF97 =1127,		DF07 =1128,
																													DF98 =1129,		DF08 =1130,
																																	DF09 =1131,



	//Triple frequency combination
	//Ionospheric (1st term) and Geometry free combination
	//With triple frequency combinations, you can combine f1,f2 and f1,f3 or f1,f2 and f2,f3 (two possibilities)
	IGF1012 = 1132,	IGF1013 = 1133,	IGF1014 = 1134,	IGF1015 = 1135,	IGF1016 = 1136,	IGF1017 = 1137,	IGF1018 = 1138,	IGF1019 = 1139,
	IGF1020 = 1140,	IGF1030 = 1141,	IGF1040 = 1142,	IGF1050 = 1143,	IGF1060 = 1144,	IGF1070 = 1145,	IGF1080 = 1146,	IGF1090 = 1147,
	IGF1213 = 1148,	IGF1214 = 1149,	IGF1215 = 1150,	IGF1216 = 1151,	IGF1217 = 1152,	IGF1218 = 1153,	IGF1219 = 1154,	IGF1220 = 1155,
	IGF1223 = 1156,	IGF1224 = 1157,	IGF1225 = 1158,	IGF1226 = 1159,	IGF1227 = 1160,	IGF1228 = 1161,	IGF1229 = 1162,	IGF1314 = 1163,
	IGF1315 = 1164,	IGF1316 = 1165,	IGF1317 = 1166,	IGF1318 = 1167,	IGF1319 = 1168,	IGF1323 = 1169,	IGF1330 = 1170,	IGF1334 = 1171,
	IGF1335 = 1172,	IGF1336 = 1173,	IGF1337 = 1174,	IGF1338 = 1175,	IGF1339 = 1176,	IGF1415 = 1177,	IGF1416 = 1178,	IGF1417 = 1179,
	IGF1418 = 1180,	IGF1419 = 1181,	IGF1424 = 1182,	IGF1434 = 1183,	IGF1440 = 1184,	IGF1445 = 1185,	IGF1446 = 1186,	IGF1447 = 1187,
	IGF1448 = 1188,	IGF1449 = 1189,	IGF1516 = 1190,	IGF1517 = 1191,	IGF1518 = 1192,	IGF1519 = 1193,	IGF1525 = 1194,	IGF1535 = 1195,
	IGF1545 = 1196,	IGF1550 = 1197,	IGF1556 = 1198,	IGF1557 = 1199,	IGF1558 = 1200,	IGF1559 = 1201,	IGF1617 = 1202,	IGF1618 = 1203,
	IGF1619 = 1204,	IGF1626 = 1205,	IGF1636 = 1206,	IGF1646 = 1207,	IGF1656 = 1208,	IGF1660 = 1209,	IGF1667 = 1210,	IGF1668 = 1211,
	IGF1669 = 1212,	IGF1718 = 1213,	IGF1719 = 1214,	IGF1727 = 1215,	IGF1737 = 1216,	IGF1747 = 1217,	IGF1757 = 1218,	IGF1767 = 1219,
	IGF1770 = 1220,	IGF1778 = 1221,	IGF1779 = 1222,	IGF1819 = 1223,	IGF1828 = 1224,	IGF1838 = 1225,	IGF1848 = 1226,	IGF1858 = 1227,
	IGF1868 = 1228,	IGF1878 = 1229,	IGF1880 = 1230,	IGF1889 = 1231,	IGF1929 = 1232,	IGF1939 = 1233,	IGF1949 = 1234,	IGF1959 = 1235,
	IGF1969 = 1236,	IGF1979 = 1237,	IGF1989 = 1238,	IGF1990 = 1239,	IGF2023 = 1240,	IGF2024 = 1241,	IGF2025 = 1242,	IGF2026 = 1243,
	IGF2027 = 1244,	IGF2028 = 1245,	IGF2029 = 1246,	IGF2030 = 1247,	IGF2040 = 1248,	IGF2050 = 1249,	IGF2060 = 1250,	IGF2070 = 1251,
	IGF2080 = 1252,	IGF2090 = 1253,	IGF2324 = 1254,	IGF2325 = 1255,	IGF2326 = 1256,	IGF2327 = 1257,	IGF2328 = 1258,	IGF2329 = 1259,
	IGF2330 = 1260,	IGF2334 = 1261,	IGF2335 = 1262,	IGF2336 = 1263,	IGF2337 = 1264,	IGF2338 = 1265,	IGF2339 = 1266,	IGF2425 = 1267,
	IGF2426 = 1268,	IGF2427 = 1269,	IGF2428 = 1270,	IGF2429 = 1271,	IGF2434 = 1272,	IGF2440 = 1273,	IGF2445 = 1274,	IGF2446 = 1275,
	IGF2447 = 1276,	IGF2448 = 1277,	IGF2449 = 1278,	IGF2526 = 1279,	IGF2527 = 1280,	IGF2528 = 1281,	IGF2529 = 1282,	IGF2535 = 1283,
	IGF2545 = 1284,	IGF2550 = 1285,	IGF2556 = 1286,	IGF2557 = 1287,	IGF2558 = 1288,	IGF2559 = 1289,	IGF2627 = 1290,	IGF2628 = 1291,
	IGF2629 = 1292,	IGF2636 = 1293,	IGF2646 = 1294,	IGF2656 = 1295,	IGF2660 = 1296,	IGF2667 = 1297,	IGF2668 = 1298,	IGF2669 = 1299,
	IGF2728 = 1300,	IGF2729 = 1301,	IGF2737 = 1302,	IGF2747 = 1303,	IGF2757 = 1304,	IGF2767 = 1305,	IGF2770 = 1306,	IGF2778 = 1307,
	IGF2779 = 1308,	IGF2829 = 1309,	IGF2838 = 1310,	IGF2848 = 1311,	IGF2858 = 1312,	IGF2868 = 1313,	IGF2878 = 1314,	IGF2880 = 1315,
	IGF2889 = 1316,	IGF2939 = 1317,	IGF2949 = 1318,	IGF2959 = 1319,	IGF2969 = 1320,	IGF2979 = 1321,	IGF2989 = 1322,	IGF2990 = 1323,
	IGF3034 = 1324,	IGF3035 = 1325,	IGF3036 = 1326,	IGF3037 = 1327,	IGF3038 = 1328,	IGF3039 = 1329,	IGF3040 = 1330,	IGF3050 = 1331,
	IGF3060 = 1332,	IGF3070 = 1333,	IGF3080 = 1334,	IGF3090 = 1335,	IGF3435 = 1336,	IGF3436 = 1337,	IGF3437 = 1338,	IGF3438 = 1339,
	IGF3439 = 1340,	IGF3440 = 1341,	IGF3445 = 1342,	IGF3446 = 1343,	IGF3447 = 1344,	IGF3448 = 1345,	IGF3449 = 1346,	IGF3536 = 1347,
	IGF3537 = 1348,	IGF3538 = 1349,	IGF3539 = 1350,	IGF3545 = 1351,	IGF3550 = 1352,	IGF3556 = 1353,	IGF3557 = 1354,	IGF3558 = 1355,
	IGF3559 = 1356,	IGF3637 = 1357,	IGF3638 = 1358,	IGF3639 = 1359,	IGF3646 = 1360,	IGF3656 = 1361,	IGF3660 = 1362,	IGF3667 = 1363,
	IGF3668 = 1364,	IGF3669 = 1365,	IGF3738 = 1366,	IGF3739 = 1367,	IGF3747 = 1368,	IGF3757 = 1369,	IGF3767 = 1370,	IGF3770 = 1371,
	IGF3778 = 1372,	IGF3779 = 1373,	IGF3839 = 1374,	IGF3848 = 1375,	IGF3858 = 1376,	IGF3868 = 1377,	IGF3878 = 1378,	IGF3880 = 1379,
	IGF3889 = 1380,	IGF3949 = 1381,	IGF3959 = 1382,	IGF3969 = 1383,	IGF3979 = 1384,	IGF3989 = 1385,	IGF3990 = 1386,	IGF4045 = 1387,
	IGF4046 = 1388,	IGF4047 = 1389,	IGF4048 = 1390,	IGF4049 = 1391,	IGF4050 = 1392,	IGF4060 = 1393,	IGF4070 = 1394,	IGF4080 = 1395,
	IGF4090 = 1396,	IGF4546 = 1397,	IGF4547 = 1398,	IGF4548 = 1399,	IGF4549 = 1400,	IGF4550 = 1401,	IGF4556 = 1402,	IGF4557 = 1403,
	IGF4558 = 1404,	IGF4559 = 1405,	IGF4647 = 1406,	IGF4648 = 1407,	IGF4649 = 1408,	IGF4656 = 1409,	IGF4660 = 1410,	IGF4667 = 1411,
	IGF4668 = 1412,	IGF4669 = 1413,	IGF4748 = 1414,	IGF4749 = 1415,	IGF4757 = 1416,	IGF4767 = 1417,	IGF4770 = 1418,	IGF4778 = 1419,
	IGF4779 = 1420,	IGF4849 = 1421,	IGF4858 = 1422,	IGF4868 = 1423,	IGF4878 = 1424,	IGF4880 = 1425,	IGF4889 = 1426,	IGF4959 = 1427,
	IGF4969 = 1428,	IGF4979 = 1429,	IGF4989 = 1430,	IGF4990 = 1431,	IGF5056 = 1432,	IGF5057 = 1433,	IGF5058 = 1434,	IGF5059 = 1435,
	IGF5060 = 1436,	IGF5070 = 1437,	IGF5080 = 1438,	IGF5090 = 1439,	IGF5657 = 1440,	IGF5658 = 1441,	IGF5659 = 1442,	IGF5660 = 1443,
	IGF5667 = 1444,	IGF5668 = 1445,	IGF5669 = 1446,	IGF5758 = 1447,	IGF5759 = 1448,	IGF5767 = 1449,	IGF5770 = 1450,	IGF5778 = 1451,
	IGF5779 = 1452,	IGF5859 = 1453,	IGF5868 = 1454,	IGF5878 = 1455,	IGF5880 = 1456,	IGF5889 = 1457,	IGF5969 = 1458,	IGF5979 = 1459,
	IGF5989 = 1460,	IGF5990 = 1461,	IGF6067 = 1462,	IGF6068 = 1463,	IGF6069 = 1464,	IGF6070 = 1465,	IGF6080 = 1466,	IGF6090 = 1467,
	IGF6768 = 1468,	IGF6769 = 1469,	IGF6770 = 1470,	IGF6778 = 1471,	IGF6779 = 1472,	IGF6869 = 1473,	IGF6878 = 1474,	IGF6880 = 1475,
	IGF6889 = 1476,	IGF6979 = 1477,	IGF6989 = 1478,	IGF6990 = 1479,	IGF7078 = 1480,	IGF7079 = 1481,	IGF7080 = 1482,	IGF7090 = 1483,
	IGF7879 = 1484,	IGF7880 = 1485,	IGF7889 = 1486,	IGF7989 = 1487,	IGF7990 = 1488,	IGF8089 = 1489,	IGF8090 = 1490,	IGF8990 = 1491,
	//Triple frequency combination
	//Ionospheric (1st and 2nd term) free combination
	//With triple frequency combinations, you can combine f1,f2 and f1,f3 or f1,f2 and f2,f3 (two possibilities)
	SIF1012 = 1492,	SIF1013 = 1493,	SIF1014 = 1494,	SIF1015 = 1495,	SIF1016 = 1496,	SIF1017 = 1497,	SIF1018 = 1498,	SIF1019 = 1499,
	SIF1020 = 1500,	SIF1030 = 1501,	SIF1040 = 1502,	SIF1050 = 1503,	SIF1060 = 1504,	SIF1070 = 1505,	SIF1080 = 1506,	SIF1090 = 1507,
	SIF1213 = 1508,	SIF1214 = 1509,	SIF1215 = 1510,	SIF1216 = 1511,	SIF1217 = 1512,	SIF1218 = 1513,	SIF1219 = 1514,	SIF1220 = 1515,
	SIF1223 = 1516,	SIF1224 = 1517,	SIF1225 = 1518,	SIF1226 = 1519,	SIF1227 = 1520,	SIF1228 = 1521,	SIF1229 = 1522,	SIF1314 = 1523,
	SIF1315 = 1524,	SIF1316 = 1525,	SIF1317 = 1526,	SIF1318 = 1527,	SIF1319 = 1528,	SIF1323 = 1529,	SIF1330 = 1530,	SIF1334 = 1531,
	SIF1335 = 1532,	SIF1336 = 1533,	SIF1337 = 1534,	SIF1338 = 1535,	SIF1339 = 1536,	SIF1415 = 1537,	SIF1416 = 1538,	SIF1417 = 1539,
	SIF1418 = 1540,	SIF1419 = 1541,	SIF1424 = 1542,	SIF1434 = 1543,	SIF1440 = 1544,	SIF1445 = 1545,	SIF1446 = 1546,	SIF1447 = 1547,
	SIF1448 = 1548,	SIF1449 = 1549,	SIF1516 = 1550,	SIF1517 = 1551,	SIF1518 = 1552,	SIF1519 = 1553,	SIF1525 = 1554,	SIF1535 = 1555,
	SIF1545 = 1556,	SIF1550 = 1557,	SIF1556 = 1558,	SIF1557 = 1559,	SIF1558 = 1560,	SIF1559 = 1561,	SIF1617 = 1562,	SIF1618 = 1563,
	SIF1619 = 1564,	SIF1626 = 1565,	SIF1636 = 1566,	SIF1646 = 1567,	SIF1656 = 1568,	SIF1660 = 1569,	SIF1667 = 1570,	SIF1668 = 1571,
	SIF1669 = 1572,	SIF1718 = 1573,	SIF1719 = 1574,	SIF1727 = 1575,	SIF1737 = 1576,	SIF1747 = 1577,	SIF1757 = 1578,	SIF1767 = 1579,
	SIF1770 = 1580,	SIF1778 = 1581,	SIF1779 = 1582,	SIF1819 = 1583,	SIF1828 = 1584,	SIF1838 = 1585,	SIF1848 = 1586,	SIF1858 = 1587,
	SIF1868 = 1588,	SIF1878 = 1589,	SIF1880 = 1590,	SIF1889 = 1591,	SIF1929 = 1592,	SIF1939 = 1593,	SIF1949 = 1594,	SIF1959 = 1595,
	SIF1969 = 1596,	SIF1979 = 1597,	SIF1989 = 1598,	SIF1990 = 1599,	SIF2023 = 1600,	SIF2024 = 1601,	SIF2025 = 1602,	SIF2026 = 1603,
	SIF2027 = 1604,	SIF2028 = 1605,	SIF2029 = 1606,	SIF2030 = 1607,	SIF2040 = 1608,	SIF2050 = 1609,	SIF2060 = 1610,	SIF2070 = 1611,
	SIF2080 = 1612,	SIF2090 = 1613,	SIF2324 = 1614,	SIF2325 = 1615,	SIF2326 = 1616,	SIF2327 = 1617,	SIF2328 = 1618,	SIF2329 = 1619,
	SIF2330 = 1620,	SIF2334 = 1621,	SIF2335 = 1622,	SIF2336 = 1623,	SIF2337 = 1624,	SIF2338 = 1625,	SIF2339 = 1626,	SIF2425 = 1627,
	SIF2426 = 1628,	SIF2427 = 1629,	SIF2428 = 1630,	SIF2429 = 1631,	SIF2434 = 1632,	SIF2440 = 1633,	SIF2445 = 1634,	SIF2446 = 1635,
	SIF2447 = 1636,	SIF2448 = 1637,	SIF2449 = 1638,	SIF2526 = 1639,	SIF2527 = 1640,	SIF2528 = 1641,	SIF2529 = 1642,	SIF2535 = 1643,
	SIF2545 = 1644,	SIF2550 = 1645,	SIF2556 = 1646,	SIF2557 = 1647,	SIF2558 = 1648,	SIF2559 = 1649,	SIF2627 = 1650,	SIF2628 = 1651,
	SIF2629 = 1652,	SIF2636 = 1653,	SIF2646 = 1654,	SIF2656 = 1655,	SIF2660 = 1656,	SIF2667 = 1657,	SIF2668 = 1658,	SIF2669 = 1659,
	SIF2728 = 1660,	SIF2729 = 1661,	SIF2737 = 1662,	SIF2747 = 1663,	SIF2757 = 1664,	SIF2767 = 1665,	SIF2770 = 1666,	SIF2778 = 1667,
	SIF2779 = 1668,	SIF2829 = 1669,	SIF2838 = 1670,	SIF2848 = 1671,	SIF2858 = 1672,	SIF2868 = 1673,	SIF2878 = 1674,	SIF2880 = 1675,
	SIF2889 = 1676,	SIF2939 = 1677,	SIF2949 = 1678,	SIF2959 = 1679,	SIF2969 = 1680,	SIF2979 = 1681,	SIF2989 = 1682,	SIF2990 = 1683,
	SIF3034 = 1684,	SIF3035 = 1685,	SIF3036 = 1686,	SIF3037 = 1687,	SIF3038 = 1688,	SIF3039 = 1689,	SIF3040 = 1690,	SIF3050 = 1691,
	SIF3060 = 1692,	SIF3070 = 1693,	SIF3080 = 1694,	SIF3090 = 1695,	SIF3435 = 1696,	SIF3436 = 1697,	SIF3437 = 1698,	SIF3438 = 1699,
	SIF3439 = 1700,	SIF3440 = 1701,	SIF3445 = 1702,	SIF3446 = 1703,	SIF3447 = 1704,	SIF3448 = 1705,	SIF3449 = 1706,	SIF3536 = 1707,
	SIF3537 = 1708,	SIF3538 = 1709,	SIF3539 = 1710,	SIF3545 = 1711,	SIF3550 = 1712,	SIF3556 = 1713,	SIF3557 = 1714,	SIF3558 = 1715,
	SIF3559 = 1716,	SIF3637 = 1717,	SIF3638 = 1718,	SIF3639 = 1719,	SIF3646 = 1720,	SIF3656 = 1721,	SIF3660 = 1722,	SIF3667 = 1723,
	SIF3668 = 1724,	SIF3669 = 1725,	SIF3738 = 1726,	SIF3739 = 1727,	SIF3747 = 1728,	SIF3757 = 1729,	SIF3767 = 1730,	SIF3770 = 1731,
	SIF3778 = 1732,	SIF3779 = 1733,	SIF3839 = 1734,	SIF3848 = 1735,	SIF3858 = 1736,	SIF3868 = 1737,	SIF3878 = 1738,	SIF3880 = 1739,
	SIF3889 = 1740,	SIF3949 = 1741,	SIF3959 = 1742,	SIF3969 = 1743,	SIF3979 = 1744,	SIF3989 = 1745,	SIF3990 = 1746,	SIF4045 = 1747,
	SIF4046 = 1748,	SIF4047 = 1749,	SIF4048 = 1750,	SIF4049 = 1751,	SIF4050 = 1752,	SIF4060 = 1753,	SIF4070 = 1754,	SIF4080 = 1755,
	SIF4090 = 1756,	SIF4546 = 1757,	SIF4547 = 1758,	SIF4548 = 1759,	SIF4549 = 1760,	SIF4550 = 1761,	SIF4556 = 1762,	SIF4557 = 1763,
	SIF4558 = 1764,	SIF4559 = 1765,	SIF4647 = 1766,	SIF4648 = 1767,	SIF4649 = 1768,	SIF4656 = 1769,	SIF4660 = 1770,	SIF4667 = 1771,
	SIF4668 = 1772,	SIF4669 = 1773,	SIF4748 = 1774,	SIF4749 = 1775,	SIF4757 = 1776,	SIF4767 = 1777,	SIF4770 = 1778,	SIF4778 = 1779,
	SIF4779 = 1780,	SIF4849 = 1781,	SIF4858 = 1782,	SIF4868 = 1783,	SIF4878 = 1784,	SIF4880 = 1785,	SIF4889 = 1786,	SIF4959 = 1787,
	SIF4969 = 1788,	SIF4979 = 1789,	SIF4989 = 1790,	SIF4990 = 1791,	SIF5056 = 1792,	SIF5057 = 1793,	SIF5058 = 1794,	SIF5059 = 1795,
	SIF5060 = 1796,	SIF5070 = 1797,	SIF5080 = 1798,	SIF5090 = 1799,	SIF5657 = 1800,	SIF5658 = 1801,	SIF5659 = 1802,	SIF5660 = 1803,
	SIF5667 = 1804,	SIF5668 = 1805,	SIF5669 = 1806,	SIF5758 = 1807,	SIF5759 = 1808,	SIF5767 = 1809,	SIF5770 = 1810,	SIF5778 = 1811,
	SIF5779 = 1812,	SIF5859 = 1813,	SIF5868 = 1814,	SIF5878 = 1815,	SIF5880 = 1816,	SIF5889 = 1817,	SIF5969 = 1818,	SIF5979 = 1819,
	SIF5989 = 1820,	SIF5990 = 1821,	SIF6067 = 1822,	SIF6068 = 1823,	SIF6069 = 1824,	SIF6070 = 1825,	SIF6080 = 1826,	SIF6090 = 1827,
	SIF6768 = 1828,	SIF6769 = 1829,	SIF6770 = 1830,	SIF6778 = 1831,	SIF6779 = 1832,	SIF6869 = 1833,	SIF6878 = 1834,	SIF6880 = 1835,
	SIF6889 = 1836,	SIF6979 = 1837,	SIF6989 = 1838,	SIF6990 = 1839,	SIF7078 = 1840,	SIF7079 = 1841,	SIF7080 = 1842,	SIF7090 = 1843,
	SIF7879 = 1844,	SIF7880 = 1845,	SIF7889 = 1846,	SIF7989 = 1847,	SIF7990 = 1848,	SIF8089 = 1849,	SIF8090 = 1850,	SIF8990 = 1851,
	//Quadruple frequency combination (as triple frequency combination but using four frequencies instead of three)
	//Ionospheric (1st and 2nd term) free combination
	//With quadruple frequency combinations, you can combine f1,f2 and f3,f4 or f1,f3 and f2,f4 or f1,f4 and f2,f3 (three possibilites)
	IGF1234 = 1852, IGF1235 = 1853, IGF1236 = 1854, IGF1237 = 1855, IGF1238 = 1856, IGF1239 = 1857, IGF1245 = 1858, IGF1246 = 1859, 
	IGF1247 = 1860, IGF1248 = 1861, IGF1249 = 1862, IGF1256 = 1863, IGF1257 = 1864, IGF1258 = 1865, IGF1259 = 1866, IGF1267 = 1867, 
	IGF1268 = 1868, IGF1269 = 1869, IGF1278 = 1870, IGF1279 = 1871, IGF1289 = 1872, IGF1345 = 1873, IGF1346 = 1874, IGF1347 = 1875, 
	IGF1348 = 1876, IGF1349 = 1877, IGF1356 = 1878, IGF1357 = 1879, IGF1358 = 1880, IGF1359 = 1881, IGF1367 = 1882, IGF1368 = 1883, 
	IGF1369 = 1884, IGF1378 = 1885, IGF1379 = 1886, IGF1389 = 1887, IGF1456 = 1888, IGF1457 = 1889, IGF1458 = 1890, IGF1459 = 1891, 
	IGF1467 = 1892, IGF1468 = 1893, IGF1469 = 1894, IGF1478 = 1895, IGF1479 = 1896, IGF1489 = 1897, IGF1567 = 1898, IGF1568 = 1899, 
	IGF1569 = 1900, IGF1578 = 1901, IGF1579 = 1902, IGF1589 = 1903, IGF1678 = 1904, IGF1679 = 1905, IGF1689 = 1906, IGF1789 = 1907, 
	IGF2345 = 1908, IGF2346 = 1909, IGF2347 = 1910, IGF2348 = 1911, IGF2349 = 1912, IGF2356 = 1913, IGF2357 = 1914, IGF2358 = 1915, 
	IGF2359 = 1916, IGF2367 = 1917, IGF2368 = 1918, IGF2369 = 1919, IGF2378 = 1920, IGF2379 = 1921, IGF2389 = 1922, IGF2456 = 1923, 
	IGF2457 = 1924, IGF2458 = 1925, IGF2459 = 1926, IGF2467 = 1927, IGF2468 = 1928, IGF2469 = 1929, IGF2478 = 1930, IGF2479 = 1931, 
	IGF2489 = 1932, IGF2567 = 1933, IGF2568 = 1934, IGF2569 = 1935, IGF2578 = 1936, IGF2579 = 1937, IGF2589 = 1938, IGF2678 = 1939, 
	IGF2679 = 1940, IGF2689 = 1941, IGF2789 = 1942, IGF3120 = 1943, IGF3456 = 1944, IGF3457 = 1945, IGF3458 = 1946, IGF3459 = 1947, 
	IGF3467 = 1948, IGF3468 = 1949, IGF3469 = 1950, IGF3478 = 1951, IGF3479 = 1952, IGF3489 = 1953, IGF3567 = 1954, IGF3568 = 1955, 
	IGF3569 = 1956, IGF3578 = 1957, IGF3579 = 1958, IGF3589 = 1959, IGF3678 = 1960, IGF3679 = 1961, IGF3689 = 1962, IGF3789 = 1963, 
	IGF4120 = 1964, IGF4130 = 1965, IGF4230 = 1966, IGF4567 = 1967, IGF4568 = 1968, IGF4569 = 1969, IGF4578 = 1970, IGF4579 = 1971, 
	IGF4589 = 1972, IGF4678 = 1973, IGF4679 = 1974, IGF4689 = 1975, IGF4789 = 1976, IGF5120 = 1977, IGF5130 = 1978, IGF5140 = 1979, 
	IGF5230 = 1980, IGF5240 = 1981, IGF5340 = 1982, IGF5678 = 1983, IGF5679 = 1984, IGF5689 = 1985, IGF5789 = 1986, IGF6120 = 1987, 
	IGF6130 = 1988, IGF6140 = 1989, IGF6150 = 1990, IGF6230 = 1991, IGF6240 = 1992, IGF6250 = 1993, IGF6340 = 1994, IGF6350 = 1995, 
	IGF6450 = 1996, IGF6789 = 1997, IGF7120 = 1998, IGF7130 = 1999, IGF7140 = 2000, IGF7150 = 2001, IGF7160 = 2002, IGF7230 = 2003, 
	IGF7240 = 2004, IGF7250 = 2005, IGF7260 = 2006, IGF7340 = 2007, IGF7350 = 2008, IGF7360 = 2009, IGF7450 = 2010, IGF7460 = 2011, 
	IGF7560 = 2012, IGF8120 = 2013, IGF8130 = 2014, IGF8140 = 2015, IGF8150 = 2016, IGF8160 = 2017, IGF8170 = 2018, IGF8230 = 2019, 
	IGF8240 = 2020, IGF8250 = 2021, IGF8260 = 2022, IGF8270 = 2023, IGF8340 = 2024, IGF8350 = 2025, IGF8360 = 2026, IGF8370 = 2027, 
	IGF8450 = 2028, IGF8460 = 2029, IGF8470 = 2030, IGF8560 = 2031, IGF8570 = 2032, IGF8670 = 2033, IGF9120 = 2034, IGF9130 = 2035, 
	IGF9140 = 2036, IGF9150 = 2037, IGF9160 = 2038, IGF9170 = 2039, IGF9180 = 2040, IGF9230 = 2041, IGF9240 = 2042, IGF9250 = 2043, 
	IGF9260 = 2044, IGF9270 = 2045, IGF9280 = 2046, IGF9340 = 2047, IGF9350 = 2048, IGF9360 = 2049, IGF9370 = 2050, IGF9380 = 2051, 
	IGF9450 = 2052, IGF9460 = 2053, IGF9470 = 2054, IGF9480 = 2055, IGF9560 = 2056, IGF9570 = 2057, IGF9580 = 2058, IGF9670 = 2059, 
	IGF9680 = 2060, IGF9780 = 2061, 

	IGF1324 = 2062, IGF1325 = 2063, IGF1326 = 2064, IGF1327 = 2065, IGF1328 = 2066, IGF1329 = 2067, IGF1425 = 2068, IGF1426 = 2069, 
	IGF1427 = 2070, IGF1428 = 2071, IGF1429 = 2072, IGF1526 = 2073, IGF1527 = 2074, IGF1528 = 2075, IGF1529 = 2076, IGF1627 = 2077, 
	IGF1628 = 2078, IGF1629 = 2079, IGF1728 = 2080, IGF1729 = 2081, IGF1829 = 2082, IGF1435 = 2083, IGF1436 = 2084, IGF1437 = 2085, 
	IGF1438 = 2086, IGF1439 = 2087, IGF1536 = 2088, IGF1537 = 2089, IGF1538 = 2090, IGF1539 = 2091, IGF1637 = 2092, IGF1638 = 2093, 
	IGF1639 = 2094, IGF1738 = 2095, IGF1739 = 2096, IGF1839 = 2097, IGF1546 = 2098, IGF1547 = 2099, IGF1548 = 2100, IGF1549 = 2101, 
	IGF1647 = 2102, IGF1648 = 2103, IGF1649 = 2104, IGF1748 = 2105, IGF1749 = 2106, IGF1849 = 2107, IGF1657 = 2108, IGF1658 = 2109, 
	IGF1659 = 2110, IGF1758 = 2111, IGF1759 = 2112, IGF1859 = 2113, IGF1768 = 2114, IGF1769 = 2115, IGF1869 = 2116, IGF1879 = 2117, 
	IGF2435 = 2118, IGF2436 = 2119, IGF2437 = 2120, IGF2438 = 2121, IGF2439 = 2122, IGF2536 = 2123, IGF2537 = 2124, IGF2538 = 2125, 
	IGF2539 = 2126, IGF2637 = 2127, IGF2638 = 2128, IGF2639 = 2129, IGF2738 = 2130, IGF2739 = 2131, IGF2839 = 2132, IGF2546 = 2133, 
	IGF2547 = 2134, IGF2548 = 2135, IGF2549 = 2136, IGF2647 = 2137, IGF2648 = 2138, IGF2649 = 2139, IGF2748 = 2140, IGF2749 = 2141, 
	IGF2849 = 2142, IGF2657 = 2143, IGF2658 = 2144, IGF2659 = 2145, IGF2758 = 2146, IGF2759 = 2147, IGF2859 = 2148, IGF2768 = 2149, 
	IGF2769 = 2150, IGF2869 = 2151, IGF2879 = 2152, IGF3210 = 2153, IGF3546 = 2154, IGF3547 = 2155, IGF3548 = 2156, IGF3549 = 2157, 
	IGF3647 = 2158, IGF3648 = 2159, IGF3649 = 2160, IGF3748 = 2161, IGF3749 = 2162, IGF3849 = 2163, IGF3657 = 2164, IGF3658 = 2165, 
	IGF3659 = 2166, IGF3758 = 2167, IGF3759 = 2168, IGF3859 = 2169, IGF3768 = 2170, IGF3769 = 2171, IGF3869 = 2172, IGF3879 = 2173, 
	IGF4210 = 2174, IGF4310 = 2175, IGF4320 = 2176, IGF4657 = 2177, IGF4658 = 2178, IGF4659 = 2179, IGF4758 = 2180, IGF4759 = 2181, 
	IGF4859 = 2182, IGF4768 = 2183, IGF4769 = 2184, IGF4869 = 2185, IGF4879 = 2186, IGF5210 = 2187, IGF5310 = 2188, IGF5410 = 2189, 
	IGF5320 = 2190, IGF5420 = 2191, IGF5430 = 2192, IGF5768 = 2193, IGF5769 = 2194, IGF5869 = 2195, IGF5879 = 2196, IGF6210 = 2197, 
	IGF6310 = 2198, IGF6410 = 2199, IGF6510 = 2200, IGF6320 = 2201, IGF6420 = 2202, IGF6520 = 2203, IGF6430 = 2204, IGF6530 = 2205, 
	IGF6540 = 2206, IGF6879 = 2207, IGF7210 = 2208, IGF7310 = 2209, IGF7410 = 2210, IGF7510 = 2211, IGF7610 = 2212, IGF7320 = 2213, 
	IGF7420 = 2214, IGF7520 = 2215, IGF7620 = 2216, IGF7430 = 2217, IGF7530 = 2218, IGF7630 = 2219, IGF7540 = 2220, IGF7640 = 2221, 
	IGF7650 = 2222, IGF8210 = 2223, IGF8310 = 2224, IGF8410 = 2225, IGF8510 = 2226, IGF8610 = 2227, IGF8710 = 2228, IGF8320 = 2229, 
	IGF8420 = 2230, IGF8520 = 2231, IGF8620 = 2232, IGF8720 = 2233, IGF8430 = 2234, IGF8530 = 2235, IGF8630 = 2236, IGF8730 = 2237, 
	IGF8540 = 2238, IGF8640 = 2239, IGF8740 = 2240, IGF8650 = 2241, IGF8750 = 2242, IGF8760 = 2243, IGF9210 = 2244, IGF9310 = 2245, 
	IGF9410 = 2246, IGF9510 = 2247, IGF9610 = 2248, IGF9710 = 2249, IGF9810 = 2250, IGF9320 = 2251, IGF9420 = 2252, IGF9520 = 2253, 
	IGF9620 = 2254, IGF9720 = 2255, IGF9820 = 2256, IGF9430 = 2257, IGF9530 = 2258, IGF9630 = 2259, IGF9730 = 2260, IGF9830 = 2261, 
	IGF9540 = 2262, IGF9640 = 2263, IGF9740 = 2264, IGF9840 = 2265, IGF9650 = 2266, IGF9750 = 2267, IGF9850 = 2268, IGF9760 = 2269, 
	IGF9860 = 2270, IGF9870 = 2271, 

	IGF1423 = 2272, IGF1523 = 2273, IGF1623 = 2274, IGF1723 = 2275, IGF1823 = 2276, IGF1923 = 2277, IGF1524 = 2278, IGF1624 = 2279, 
	IGF1724 = 2280, IGF1824 = 2281, IGF1924 = 2282, IGF1625 = 2283, IGF1725 = 2284, IGF1825 = 2285, IGF1925 = 2286, IGF1726 = 2287, 
	IGF1826 = 2288, IGF1926 = 2289, IGF1827 = 2290, IGF1927 = 2291, IGF1928 = 2292, IGF1534 = 2293, IGF1634 = 2294, IGF1734 = 2295, 
	IGF1834 = 2296, IGF1934 = 2297, IGF1635 = 2298, IGF1735 = 2299, IGF1835 = 2300, IGF1935 = 2301, IGF1736 = 2302, IGF1836 = 2303, 
	IGF1936 = 2304, IGF1837 = 2305, IGF1937 = 2306, IGF1938 = 2307, IGF1645 = 2308, IGF1745 = 2309, IGF1845 = 2310, IGF1945 = 2311, 
	IGF1746 = 2312, IGF1846 = 2313, IGF1946 = 2314, IGF1847 = 2315, IGF1947 = 2316, IGF1948 = 2317, IGF1756 = 2318, IGF1856 = 2319, 
	IGF1956 = 2320, IGF1857 = 2321, IGF1957 = 2322, IGF1958 = 2323, IGF1867 = 2324, IGF1967 = 2325, IGF1968 = 2326, IGF1978 = 2327, 
	IGF2534 = 2328, IGF2634 = 2329, IGF2734 = 2330, IGF2834 = 2331, IGF2934 = 2332, IGF2635 = 2333, IGF2735 = 2334, IGF2835 = 2335, 
	IGF2935 = 2336, IGF2736 = 2337, IGF2836 = 2338, IGF2936 = 2339, IGF2837 = 2340, IGF2937 = 2341, IGF2938 = 2342, IGF2645 = 2343, 
	IGF2745 = 2344, IGF2845 = 2345, IGF2945 = 2346, IGF2746 = 2347, IGF2846 = 2348, IGF2946 = 2349, IGF2847 = 2350, IGF2947 = 2351, 
	IGF2948 = 2352, IGF2756 = 2353, IGF2856 = 2354, IGF2956 = 2355, IGF2857 = 2356, IGF2957 = 2357, IGF2958 = 2358, IGF2867 = 2359, 
	IGF2967 = 2360, IGF2968 = 2361, IGF2978 = 2362, IGF3012 = 2363, IGF3645 = 2364, IGF3745 = 2365, IGF3845 = 2366, IGF3945 = 2367, 
	IGF3746 = 2368, IGF3846 = 2369, IGF3946 = 2370, IGF3847 = 2371, IGF3947 = 2372, IGF3948 = 2373, IGF3756 = 2374, IGF3856 = 2375, 
	IGF3956 = 2376, IGF3857 = 2377, IGF3957 = 2378, IGF3958 = 2379, IGF3867 = 2380, IGF3967 = 2381, IGF3968 = 2382, IGF3978 = 2383, 
	IGF4012 = 2384, IGF4013 = 2385, IGF4023 = 2386, IGF4756 = 2387, IGF4856 = 2388, IGF4956 = 2389, IGF4857 = 2390, IGF4957 = 2391, 
	IGF4958 = 2392, IGF4867 = 2393, IGF4967 = 2394, IGF4968 = 2395, IGF4978 = 2396, IGF5012 = 2397, IGF5013 = 2398, IGF5014 = 2399, 
	IGF5023 = 2400, IGF5024 = 2401, IGF5034 = 2402, IGF5867 = 2403, IGF5967 = 2404, IGF5968 = 2405, IGF5978 = 2406, IGF6012 = 2407, 
	IGF6013 = 2408, IGF6014 = 2409, IGF6015 = 2410, IGF6023 = 2411, IGF6024 = 2412, IGF6025 = 2413, IGF6034 = 2414, IGF6035 = 2415, 
	IGF6045 = 2416, IGF6978 = 2417, IGF7012 = 2418, IGF7013 = 2419, IGF7014 = 2420, IGF7015 = 2421, IGF7016 = 2422, IGF7023 = 2423, 
	IGF7024 = 2424, IGF7025 = 2425, IGF7026 = 2426, IGF7034 = 2427, IGF7035 = 2428, IGF7036 = 2429, IGF7045 = 2430, IGF7046 = 2431, 
	IGF7056 = 2432, IGF8012 = 2433, IGF8013 = 2434, IGF8014 = 2435, IGF8015 = 2436, IGF8016 = 2437, IGF8017 = 2438, IGF8023 = 2439, 
	IGF8024 = 2440, IGF8025 = 2441, IGF8026 = 2442, IGF8027 = 2443, IGF8034 = 2444, IGF8035 = 2445, IGF8036 = 2446, IGF8037 = 2447, 
	IGF8045 = 2448, IGF8046 = 2449, IGF8047 = 2450, IGF8056 = 2451, IGF8057 = 2452, IGF8067 = 2453, IGF9012 = 2454, IGF9013 = 2455, 
	IGF9014 = 2456, IGF9015 = 2457, IGF9016 = 2458, IGF9017 = 2459, IGF9018 = 2460, IGF9023 = 2461, IGF9024 = 2462, IGF9025 = 2463, 
	IGF9026 = 2464, IGF9027 = 2465, IGF9028 = 2466, IGF9034 = 2467, IGF9035 = 2468, IGF9036 = 2469, IGF9037 = 2470, IGF9038 = 2471, 
	IGF9045 = 2472, IGF9046 = 2473, IGF9047 = 2474, IGF9048 = 2475, IGF9056 = 2476, IGF9057 = 2477, IGF9058 = 2478, IGF9067 = 2479, 
	IGF9068 = 2480, IGF9078 = 2481, 

	//Quadruple frequency combination (as triple frequency combination but using four frequencies instead of three)
	//Ionospheric (1st and 2nd term) free combination
	//With quadruple frequency combinations, you can combine f1,f2 and f3,f4 or f1,f3 and f2,f4 or f1,f4 and f2,f3 (three possibilites)
	SIF1234 = 2482, SIF1235 = 2483, SIF1236 = 2484, SIF1237 = 2485, SIF1238 = 2486, SIF1239 = 2487, SIF1245 = 2488, SIF1246 = 2489, 
	SIF1247 = 2490, SIF1248 = 2491, SIF1249 = 2492, SIF1256 = 2493, SIF1257 = 2494, SIF1258 = 2495, SIF1259 = 2496, SIF1267 = 2497, 
	SIF1268 = 2498, SIF1269 = 2499, SIF1278 = 2500, SIF1279 = 2501, SIF1289 = 2502, SIF1345 = 2503, SIF1346 = 2504, SIF1347 = 2505, 
	SIF1348 = 2506, SIF1349 = 2507, SIF1356 = 2508, SIF1357 = 2509, SIF1358 = 2510, SIF1359 = 2511, SIF1367 = 2512, SIF1368 = 2513, 
	SIF1369 = 2514, SIF1378 = 2515, SIF1379 = 2516, SIF1389 = 2517, SIF1456 = 2518, SIF1457 = 2519, SIF1458 = 2520, SIF1459 = 2521, 
	SIF1467 = 2522, SIF1468 = 2523, SIF1469 = 2524, SIF1478 = 2525, SIF1479 = 2526, SIF1489 = 2527, SIF1567 = 2528, SIF1568 = 2529, 
	SIF1569 = 2530, SIF1578 = 2531, SIF1579 = 2532, SIF1589 = 2533, SIF1678 = 2534, SIF1679 = 2535, SIF1689 = 2536, SIF1789 = 2537, 
	SIF2345 = 2538, SIF2346 = 2539, SIF2347 = 2540, SIF2348 = 2541, SIF2349 = 2542, SIF2356 = 2543, SIF2357 = 2544, SIF2358 = 2545, 
	SIF2359 = 2546, SIF2367 = 2547, SIF2368 = 2548, SIF2369 = 2549, SIF2378 = 2550, SIF2379 = 2551, SIF2389 = 2552, SIF2456 = 2553, 
	SIF2457 = 2554, SIF2458 = 2555, SIF2459 = 2556, SIF2467 = 2557, SIF2468 = 2558, SIF2469 = 2559, SIF2478 = 2560, SIF2479 = 2561, 
	SIF2489 = 2562, SIF2567 = 2563, SIF2568 = 2564, SIF2569 = 2565, SIF2578 = 2566, SIF2579 = 2567, SIF2589 = 2568, SIF2678 = 2569, 
	SIF2679 = 2570, SIF2689 = 2571, SIF2789 = 2572, SIF3120 = 2573, SIF3456 = 2574, SIF3457 = 2575, SIF3458 = 2576, SIF3459 = 2577, 
	SIF3467 = 2578, SIF3468 = 2579, SIF3469 = 2580, SIF3478 = 2581, SIF3479 = 2582, SIF3489 = 2583, SIF3567 = 2584, SIF3568 = 2585, 
	SIF3569 = 2586, SIF3578 = 2587, SIF3579 = 2588, SIF3589 = 2589, SIF3678 = 2590, SIF3679 = 2591, SIF3689 = 2592, SIF3789 = 2593, 
	SIF4120 = 2594, SIF4130 = 2595, SIF4230 = 2596, SIF4567 = 2597, SIF4568 = 2598, SIF4569 = 2599, SIF4578 = 2600, SIF4579 = 2601, 
	SIF4589 = 2602, SIF4678 = 2603, SIF4679 = 2604, SIF4689 = 2605, SIF4789 = 2606, SIF5120 = 2607, SIF5130 = 2608, SIF5140 = 2609, 
	SIF5230 = 2610, SIF5240 = 2611, SIF5340 = 2612, SIF5678 = 2613, SIF5679 = 2614, SIF5689 = 2615, SIF5789 = 2616, SIF6120 = 2617, 
	SIF6130 = 2618, SIF6140 = 2619, SIF6150 = 2620, SIF6230 = 2621, SIF6240 = 2622, SIF6250 = 2623, SIF6340 = 2624, SIF6350 = 2625, 
	SIF6450 = 2626, SIF6789 = 2627, SIF7120 = 2628, SIF7130 = 2629, SIF7140 = 2630, SIF7150 = 2631, SIF7160 = 2632, SIF7230 = 2633, 
	SIF7240 = 2634, SIF7250 = 2635, SIF7260 = 2636, SIF7340 = 2637, SIF7350 = 2638, SIF7360 = 2639, SIF7450 = 2640, SIF7460 = 2641, 
	SIF7560 = 2642, SIF8120 = 2643, SIF8130 = 2644, SIF8140 = 2645, SIF8150 = 2646, SIF8160 = 2647, SIF8170 = 2648, SIF8230 = 2649, 
	SIF8240 = 2650, SIF8250 = 2651, SIF8260 = 2652, SIF8270 = 2653, SIF8340 = 2654, SIF8350 = 2655, SIF8360 = 2656, SIF8370 = 2657, 
	SIF8450 = 2658, SIF8460 = 2659, SIF8470 = 2660, SIF8560 = 2661, SIF8570 = 2662, SIF8670 = 2663, SIF9120 = 2664, SIF9130 = 2665, 
	SIF9140 = 2666, SIF9150 = 2667, SIF9160 = 2668, SIF9170 = 2669, SIF9180 = 2670, SIF9230 = 2671, SIF9240 = 2672, SIF9250 = 2673, 
	SIF9260 = 2674, SIF9270 = 2675, SIF9280 = 2676, SIF9340 = 2677, SIF9350 = 2678, SIF9360 = 2679, SIF9370 = 2680, SIF9380 = 2681, 
	SIF9450 = 2682, SIF9460 = 2683, SIF9470 = 2684, SIF9480 = 2685, SIF9560 = 2686, SIF9570 = 2687, SIF9580 = 2688, SIF9670 = 2689, 
	SIF9680 = 2690, SIF9780 = 2691, 

	SIF1324 = 2692, SIF1325 = 2693, SIF1326 = 2694, SIF1327 = 2695, SIF1328 = 2696, SIF1329 = 2697, SIF1425 = 2698, SIF1426 = 2699, 
	SIF1427 = 2700, SIF1428 = 2701, SIF1429 = 2702, SIF1526 = 2703, SIF1527 = 2704, SIF1528 = 2705, SIF1529 = 2706, SIF1627 = 2707, 
	SIF1628 = 2708, SIF1629 = 2709, SIF1728 = 2710, SIF1729 = 2711, SIF1829 = 2712, SIF1435 = 2713, SIF1436 = 2714, SIF1437 = 2715, 
	SIF1438 = 2716, SIF1439 = 2717, SIF1536 = 2718, SIF1537 = 2719, SIF1538 = 2720, SIF1539 = 2721, SIF1637 = 2722, SIF1638 = 2723, 
	SIF1639 = 2724, SIF1738 = 2725, SIF1739 = 2726, SIF1839 = 2727, SIF1546 = 2728, SIF1547 = 2729, SIF1548 = 2730, SIF1549 = 2731, 
	SIF1647 = 2732, SIF1648 = 2733, SIF1649 = 2734, SIF1748 = 2735, SIF1749 = 2736, SIF1849 = 2737, SIF1657 = 2738, SIF1658 = 2739, 
	SIF1659 = 2740, SIF1758 = 2741, SIF1759 = 2742, SIF1859 = 2743, SIF1768 = 2744, SIF1769 = 2745, SIF1869 = 2746, SIF1879 = 2747, 
	SIF2435 = 2748, SIF2436 = 2749, SIF2437 = 2750, SIF2438 = 2751, SIF2439 = 2752, SIF2536 = 2753, SIF2537 = 2754, SIF2538 = 2755, 
	SIF2539 = 2756, SIF2637 = 2757, SIF2638 = 2758, SIF2639 = 2759, SIF2738 = 2760, SIF2739 = 2761, SIF2839 = 2762, SIF2546 = 2763, 
	SIF2547 = 2764, SIF2548 = 2765, SIF2549 = 2766, SIF2647 = 2767, SIF2648 = 2768, SIF2649 = 2769, SIF2748 = 2770, SIF2749 = 2771, 
	SIF2849 = 2772, SIF2657 = 2773, SIF2658 = 2774, SIF2659 = 2775, SIF2758 = 2776, SIF2759 = 2777, SIF2859 = 2778, SIF2768 = 2779, 
	SIF2769 = 2780, SIF2869 = 2781, SIF2879 = 2782, SIF3210 = 2783, SIF3546 = 2784, SIF3547 = 2785, SIF3548 = 2786, SIF3549 = 2787, 
	SIF3647 = 2788, SIF3648 = 2789, SIF3649 = 2790, SIF3748 = 2791, SIF3749 = 2792, SIF3849 = 2793, SIF3657 = 2794, SIF3658 = 2795, 
	SIF3659 = 2796, SIF3758 = 2797, SIF3759 = 2798, SIF3859 = 2799, SIF3768 = 2800, SIF3769 = 2801, SIF3869 = 2802, SIF3879 = 2803, 
	SIF4210 = 2804, SIF4310 = 2805, SIF4320 = 2806, SIF4657 = 2807, SIF4658 = 2808, SIF4659 = 2809, SIF4758 = 2810, SIF4759 = 2811, 
	SIF4859 = 2812, SIF4768 = 2813, SIF4769 = 2814, SIF4869 = 2815, SIF4879 = 2816, SIF5210 = 2817, SIF5310 = 2818, SIF5410 = 2819, 
	SIF5320 = 2820, SIF5420 = 2821, SIF5430 = 2822, SIF5768 = 2823, SIF5769 = 2824, SIF5869 = 2825, SIF5879 = 2826, SIF6210 = 2827, 
	SIF6310 = 2828, SIF6410 = 2829, SIF6510 = 2830, SIF6320 = 2831, SIF6420 = 2832, SIF6520 = 2833, SIF6430 = 2834, SIF6530 = 2835, 
	SIF6540 = 2836, SIF6879 = 2837, SIF7210 = 2838, SIF7310 = 2839, SIF7410 = 2840, SIF7510 = 2841, SIF7610 = 2842, SIF7320 = 2843, 
	SIF7420 = 2844, SIF7520 = 2845, SIF7620 = 2846, SIF7430 = 2847, SIF7530 = 2848, SIF7630 = 2849, SIF7540 = 2850, SIF7640 = 2851, 
	SIF7650 = 2852, SIF8210 = 2853, SIF8310 = 2854, SIF8410 = 2855, SIF8510 = 2856, SIF8610 = 2857, SIF8710 = 2858, SIF8320 = 2859, 
	SIF8420 = 2860, SIF8520 = 2861, SIF8620 = 2862, SIF8720 = 2863, SIF8430 = 2864, SIF8530 = 2865, SIF8630 = 2866, SIF8730 = 2867, 
	SIF8540 = 2868, SIF8640 = 2869, SIF8740 = 2870, SIF8650 = 2871, SIF8750 = 2872, SIF8760 = 2873, SIF9210 = 2874, SIF9310 = 2875, 
	SIF9410 = 2876, SIF9510 = 2877, SIF9610 = 2878, SIF9710 = 2879, SIF9810 = 2880, SIF9320 = 2881, SIF9420 = 2882, SIF9520 = 2883, 
	SIF9620 = 2884, SIF9720 = 2885, SIF9820 = 2886, SIF9430 = 2887, SIF9530 = 2888, SIF9630 = 2889, SIF9730 = 2890, SIF9830 = 2891, 
	SIF9540 = 2892, SIF9640 = 2893, SIF9740 = 2894, SIF9840 = 2895, SIF9650 = 2896, SIF9750 = 2897, SIF9850 = 2898, SIF9760 = 2899, 
	SIF9860 = 2900, SIF9870 = 2901, 

	SIF1423 = 2902, SIF1523 = 2903, SIF1623 = 2904, SIF1723 = 2905, SIF1823 = 2906, SIF1923 = 2907, SIF1524 = 2908, SIF1624 = 2909, 
	SIF1724 = 2910, SIF1824 = 2911, SIF1924 = 2912, SIF1625 = 2913, SIF1725 = 2914, SIF1825 = 2915, SIF1925 = 2916, SIF1726 = 2917, 
	SIF1826 = 2918, SIF1926 = 2919, SIF1827 = 2920, SIF1927 = 2921, SIF1928 = 2922, SIF1534 = 2923, SIF1634 = 2924, SIF1734 = 2925, 
	SIF1834 = 2926, SIF1934 = 2927, SIF1635 = 2928, SIF1735 = 2929, SIF1835 = 2930, SIF1935 = 2931, SIF1736 = 2932, SIF1836 = 2933, 
	SIF1936 = 2934, SIF1837 = 2935, SIF1937 = 2936, SIF1938 = 2937, SIF1645 = 2938, SIF1745 = 2939, SIF1845 = 2940, SIF1945 = 2941, 
	SIF1746 = 2942, SIF1846 = 2943, SIF1946 = 2944, SIF1847 = 2945, SIF1947 = 2946, SIF1948 = 2947, SIF1756 = 2948, SIF1856 = 2949, 
	SIF1956 = 2950, SIF1857 = 2951, SIF1957 = 2952, SIF1958 = 2953, SIF1867 = 2954, SIF1967 = 2955, SIF1968 = 2956, SIF1978 = 2957, 
	SIF2534 = 2958, SIF2634 = 2959, SIF2734 = 2960, SIF2834 = 2961, SIF2934 = 2962, SIF2635 = 2963, SIF2735 = 2964, SIF2835 = 2965, 
	SIF2935 = 2966, SIF2736 = 2967, SIF2836 = 2968, SIF2936 = 2969, SIF2837 = 2970, SIF2937 = 2971, SIF2938 = 2972, SIF2645 = 2973, 
	SIF2745 = 2974, SIF2845 = 2975, SIF2945 = 2976, SIF2746 = 2977, SIF2846 = 2978, SIF2946 = 2979, SIF2847 = 2980, SIF2947 = 2981, 
	SIF2948 = 2982, SIF2756 = 2983, SIF2856 = 2984, SIF2956 = 2985, SIF2857 = 2986, SIF2957 = 2987, SIF2958 = 2988, SIF2867 = 2989, 
	SIF2967 = 2990, SIF2968 = 2991, SIF2978 = 2992, SIF3012 = 2993, SIF3645 = 2994, SIF3745 = 2995, SIF3845 = 2996, SIF3945 = 2997, 
	SIF3746 = 2998, SIF3846 = 2999, SIF3946 = 3000, SIF3847 = 3001, SIF3947 = 3002, SIF3948 = 3003, SIF3756 = 3004, SIF3856 = 3005, 
	SIF3956 = 3006, SIF3857 = 3007, SIF3957 = 3008, SIF3958 = 3009, SIF3867 = 3010, SIF3967 = 3011, SIF3968 = 3012, SIF3978 = 3013, 
	SIF4012 = 3014, SIF4013 = 3015, SIF4023 = 3016, SIF4756 = 3017, SIF4856 = 3018, SIF4956 = 3019, SIF4857 = 3020, SIF4957 = 3021, 
	SIF4958 = 3022, SIF4867 = 3023, SIF4967 = 3024, SIF4968 = 3025, SIF4978 = 3026, SIF5012 = 3027, SIF5013 = 3028, SIF5014 = 3029, 
	SIF5023 = 3030, SIF5024 = 3031, SIF5034 = 3032, SIF5867 = 3033, SIF5967 = 3034, SIF5968 = 3035, SIF5978 = 3036, SIF6012 = 3037, 
	SIF6013 = 3038, SIF6014 = 3039, SIF6015 = 3040, SIF6023 = 3041, SIF6024 = 3042, SIF6025 = 3043, SIF6034 = 3044, SIF6035 = 3045, 
	SIF6045 = 3046, SIF6978 = 3047, SIF7012 = 3048, SIF7013 = 3049, SIF7014 = 3050, SIF7015 = 3051, SIF7016 = 3052, SIF7023 = 3053, 
	SIF7024 = 3054, SIF7025 = 3055, SIF7026 = 3056, SIF7034 = 3057, SIF7035 = 3058, SIF7036 = 3059, SIF7045 = 3060, SIF7046 = 3061, 
	SIF7056 = 3062, SIF8012 = 3063, SIF8013 = 3064, SIF8014 = 3065, SIF8015 = 3066, SIF8016 = 3067, SIF8017 = 3068, SIF8023 = 3069, 
	SIF8024 = 3070, SIF8025 = 3071, SIF8026 = 3072, SIF8027 = 3073, SIF8034 = 3074, SIF8035 = 3075, SIF8036 = 3076, SIF8037 = 3077, 
	SIF8045 = 3078, SIF8046 = 3079, SIF8047 = 3080, SIF8056 = 3081, SIF8057 = 3082, SIF8067 = 3083, SIF9012 = 3084, SIF9013 = 3085, 
	SIF9014 = 3086, SIF9015 = 3087, SIF9016 = 3088, SIF9017 = 3089, SIF9018 = 3090, SIF9023 = 3091, SIF9024 = 3092, SIF9025 = 3093, 
	SIF9026 = 3094, SIF9027 = 3095, SIF9028 = 3096, SIF9034 = 3097, SIF9035 = 3098, SIF9036 = 3099, SIF9037 = 3100, SIF9038 = 3101, 
	SIF9045 = 3102, SIF9046 = 3103, SIF9047 = 3104, SIF9048 = 3105, SIF9056 = 3106, SIF9057 = 3107, SIF9058 = 3108, SIF9067 = 3109, 
	SIF9068 = 3110, SIF9078 = 3111 

};

// Enumerator for the different kind of measurements
enum MeasurementKind {
	UNKNOWN_MEAS=-1,
	Pseudorange=0,
	CarrierPhase=1,
	Doppler=2,
	SNR=3,
	Ionosphere=4,
	Channels=5
};

// Enumerator for the type of measurement given to the filter
enum FilterMeasType {
	OTHER_MEAS = 0,
	SinglePseudorange = 1,
	SinglePseudorangeSmoothed = 2,
	IonoFreeCombCode = 3,
	IonoFreeCombCodeSmoothed = 4,
	SecondIonoFreeCode = 5,
	SecondIonoFreeCodeSmoothed = 6,
	DivergenceFreeCode = 7,
	DivergenceFreeCodeSmoothed = 8,
	SingleCarrierPhase = 9,
	GraphicComb = 10,
	IonoFreeCombPhase = 11,
	DivergenceFreePhase = 12,
	SecondIonoFreePhase = 13,
	SingleDoppler = 14,
	IonoFreeCombDoppler = 15,
	SecondIonoFreeDoppler = 16,
	DivergenceFreeDoppler = 17
};

// Enumerator for the different filter parameters
enum FilterParameter {
	PHI_PAR = 0,
	Q_PAR = 1,
	P0_PAR = 2
};

// Enumerator for the different filter unknowns
enum FilterUnknown {
	DR_UNK = 0,		//Coordinates
	DT_UNK = 1,		//Receiver Clock offset
	DT_IS_UNK = 2,	//Inter system clock biases
	TROP_UNK = 3,	//Tropospheric wet residual
	IONO_UNK = 4,	//Ionosphere estimation
	SATDCB_UNK = 5,	//Satellite DCB estimation
	RECDCB_UNK = 6,	//Receiver DCB estimation
	GLOIFB_UNK = 7, //Inter frequency bias in GLONASS FDMA
	WUP_UNK = 8,	//Receiver Wind Up
	BIAS_UNK = 9	//Ambiguities
};

//Enumerator for GNSS clock estimation source
enum GNSSClockSource {
	ClkSrcCalculate = 0,
	ClkSrcRINEX = 1,
	ClkSrcUser = 2
};

// Enumerator for the different receiver position sources
enum ReceiverPositionSrc {
	rpUNKNOWN = 0,
	rpRINEX = 1,				//Fixed user position read from RINEX observation file
	rpSINEX = 2, 				//Fixed user position read from SINEX file
	rpSET = 3,					//Fixed position provided by user
	rpSETREF = 4,				//Mobile receivers. Reference rover position is read from file for each epoch and it used for modelling and for computing the NEU error
	rpCALCULATE = 5,			//Mobile receivers. Position computed each epoch starting from the Earth Surface. Output NEU error is 0
	rpCALCULATERINEX = 6,		//Mobile receivers. Position computed each epoch starting from the RINEX observation coordinates. Output NEU error is 0 
	rpCALCULATEUSER = 7,		//Mobile receivers. Position computed each epoch starting from the position provided by user. Output NEU error is 0
	rpCALCULATEREF = 8,			//Mobile receivers. Position computed each epoch starting from the Earth Surface, but the NEU error is computed with position from file
	rpCALCULATERINEXREF = 9,	//Mobile receivers. Position computed each epoch starting from the RINEX observation coordinates, but computes the NEU error with position from file
	rpCALCULATEUSERREF = 10,	//Mobile receivers. Position computed each epoch starting from the position provided by user, but computes the NEU error with position from file
	rpRTCMbaseline = 11,		//DGNSS. Reference station position from reference station RINEX, output NEU error is compared with reference station coordinates
	rpRTCMRINEXROVER = 12,		//DGNSS. Reference station position from reference station RINEX, output NEU error is compared with rover RINEX coordinates
	rpRTCMRoverUSER = 13,		//DGNSS. Reference station position from reference station RINEX, output NEU error is compared with fixed user provided coordinates
	rpRTCMRoverUSERREF = 14,	//DGNSS. Reference station position from reference station RINEX, output NEU error is compared with position from file
	rpRTCMUserbaseline = 15,	//DGNSS. Reference station position provided by user, output NEU error is compared with reference station coordinates
	rpRTCMUserRINEXROVER = 16,	//DGNSS. Reference station position provided by user, output NEU error is compared with rover RINEX coordinates
	rpRTCMRefRoverUSER = 17,	//DGNSS. Reference station position provided by user, output NEU error is compared with fixed user provided coordinates
	rpRTCMRefUSERRoverREF = 18	//DGNSS. Reference station position provided by user, output NEU error is compared with position from file	
};

// Enumerator for the different antenna data sources 
// These values can have any value smaller than 100, as values gretear than 100 will be used to point to a specific constellation and frequency
enum AntennaData {
	adUNKNOWN=-1,
	adNONE=0,
	adSET=1,
	adANTEX=2,
	adDummy=1000		//To avoid warning, as some variables with enum AntennaData may have temporary values greater than 100
};

// Enumerator for ARP
enum ARP {
	arpUNKNOWN,
	arpNONE,
	arpSET,
	arpRINEX
}; 

// Enumerator for the program work modes
enum WorkMode {
	wmUNKNOWN,
	wmDOPROCESSING,
	wmSHOWINPUT,
	wmCOMPAREORBITS,
	wmSHOWPRODUCT,
	wmSBASPLOTS,
	wmUSERERROR2RINEX
};

// Enumerator for satellite velocity
enum SatelliteVelocity {
	svUNKNOWN,
	svINERTIAL,
	svITRF
};

// Enumerator for processing direction
enum ProcessingDirection {
	pFORWARD = 0,
	pBACKWARD = 1
};

// Enumerator for binary data read
enum BinaryDataRead {
	bdrANTENNA,
	bdrCORRECTIONSmsg1,
	bdrCORRECTIONSmsg2,
	brdrOther
};

// Enumerator for DGNSS mode
enum RTCMMode {
	RTCMUNKNOWN = -1,
	RTCMCheckVersion = 0,
	ConvertRTCM2 = 1,
	ConvertRTCM3 = 2,
	ProcessRTCM2 = 3,
	ProcessRTCM3 = 4,
	ProcessRINEX = 5
};

//Enumerator for weight modes
//NOTE: IONEX and Clocks sigmas will be added to the sigma (according to input parameters and data) independently of the option selected for Weight Mode
enum WeightMode {
	UnknownWeight= -1,
	FixedWeight = 0,
	ElevationWeight = 1,
	Elevation2Weight = 2,
	SNRWeight = 3,
	SNRElevWeight = 4,

	SBASOnlyWeight = 5,
	DGNSSOnlyWeight = 6,

	SBASFixedWeight = 8,
	SBASElevWeight = 9,
	SBASElev2Weight = 10,
	SBASSNRWeight = 11,
	SBASSNRElevWeight = 12,

	DGNSSFixedWeight = 13,
	DGNSSElevWeight = 14,
	DGNSSElev2Weight = 15,
	DGNSSSNRWeight = 16,
	DGNSSSNRElevWeight = 17
};	

//Enumerator for SNR weights combinations
enum SNRWeightComb {
	SNRWeightUnknown = -1,
	SNRWeightCombi = 0,
	SNRWeightCombj = 1,
	SNRWeightCombk = 2,
	SNRWeightCombl = 3,
	SNRWeightCombMax = 4,
	SNRWeightCombMin = 5,
	SNRWeightCombMean = 6,
	SNRWeightCombUser = 7
};

//Enumerator for combining user weights with SBAS or DGNSS weights
enum CombineWeightsMode {
	CombineWeightUnknown = -1,
	ComputedOnly = 0,
	ComputedPlusUser = 1,
	UserOnly = 2
};


// Enumerator for solution mode
enum SolutionMode {
	SPPMode=0,
	PPPMode=1,
	PPPFixAmbMode=2,
	FPPPModeFloatAmb=3,
	FPPPModeFixAmb=4,
	SBAS1FMode=5,
	SBASDFMCMode=6,
	DGNSSMode=7
};

//Enumerator for differential OUTPUT fields computation mode
enum OUTDiffField {
	FromAPriori,
	RTCMBaseline,
	RTCMNoBaseline,
	CalculateWithRefFile
};

//Enumerator for HDOP/PDOP to be computed in SBAS plots
enum SBASPlotsDOP {
	SBASplotsNoDOP,
	SBASplotsHDOPOnly,
	SBASplotsPDOPOnly,
	SBASplotsGDOPOnly,
	SBASplotsHDOPandPDOP,
	SBASplotsHDOPandGDOP,
	SBASplotsPDOPandGDOP,
	SBASplotsHDOPPDOPGDOP
};

//Enumerator for cycle-slip types and the print modes
enum CSType {
	CSTypeOther=-1, //To force signed int
	CSTypeDataGap=1,
	CSTypeDataGapOldFormat=2,
	CSTypeLLI=3,
	CSTypeLLIOldFormat=4,
	CSTypeSF=5,
	CSTypeSFOldFormat=6,
	CSTypeMW=7,
	CSTypeMWOldFormat=8,
	CSTypeLIEst=9,
	CSTypeLIEstOldFormat=10,
	CSTypeLINoEst=11,
	CSTypeLINoEstOldFormat=12,
	CSTypeIGFEst=13,
	CSTypeIGFNoEst=14
};

//Enumerator for date conversion mode
enum DateConversionModes {
	DateConversionModeNone,
	DateConversionModeCalendar,
	DateConversionModeDoY,
	DateConversionModeGPSWeek,
	DateConversionModeMJDN
};

//Enumerator for coordinate conversion mode
enum CoordConversionModes {
	CoordConversionModeNone,
	CoordConversionModeXYZ,
	CoordConversionModeGeod,
	CoordConversionModeSph
};

//Enumerator for mapping function type
enum MappingFunctionTypes {
	MappingFunctionUnknown=0,
	MappingFunctionCOSZ=1,
	MappingFunctionQFAC=2
};

//Enumerator for type of measurement combination in gLAB autoselection
enum CombTypeAutoSelectionTypes {
	CombTypeAutoSelectionAutomatic=0,
	CombTypeAutoSelectionSingleFreq=1,
	CombTypeAutoSelectionDualFreq=2,
	CombTypeAutoSelectionGraphic=3
};


//Structure for creating a string of satellite ranges (grouped by
//constellations) according to a certain conditions (for example, weight mode)
//This struct is mainly used in printParameters function in output.c file
typedef struct {
	int				size;
	int				*numJumpslist;
	int				***listSatPRN;
	enum GNSSystem	***listSatGNSS;

} TRangeList;

// Measurements structure
typedef struct {
	double		value;
	double		rawvalue;									//Raw value without user added noise
	double		totalnoise;									//Total user added noise to the measurement
	double		model;										//Modelled value with without DCBs
	double		modelAll[MAX_FILTER_MEASUREMENTS_SAT];		//Modelled value per each measurement in the filter
	double		SNRvalue;									//SNR value. It can set by either the non-quantized or the quantized value. If both available, the non-quantized prevails
	int			LLI;
	int			hasSNRflag;									//Flag to indicate if SNR flag is given
	int			SNRflag;									//SNR flag from RINEX (if not given, flag equals to -1 and SNRflagdbHz value is maximum)
	int			SNRflagdBHz;								//SNR flag in dBHz
	int			dataFlag;								   	//see FLAG #defines
} TMeasurement;

// Time handling structure
typedef struct {
	int			MJDN;
	double		SoD;
} TTime;

// Satellite structure
typedef struct {
	enum GNSSystem	 		GNSS;
	int						SVN;
	int						PRN;
	int						block;
	TMeasurement			meas[MAX_MEASUREMENTS_PER_SATELLITE];
	TTime					transTime;
	double					position[3];
	double					velocity[3];
	double					ITRFvel[3];
	double					LoS[3];
	double					clockCorrection;
	double					orientation[3][3];
	double					elevation;
	double					azimuth;
	double					ionoCorr;		//in TECUs
	double					ionoSigma;		//in TECUs
	double					DCBSigma;
	double					tropWetMap;
	double					measurementWeights[MAX_FILTER_MEASUREMENTS_SAT];
	double					geometricDistance;
	int						validIono;
	int						hasOrbitsAndClocks;
	int						hasSatPhaseCenterCor;
	int						hasDCBs;
	int						hasDCBsofC1P1;
	int						hasCNAVforDCB;
	int						usedCNAVfirst;
	int						hasSBAScor;
	int						hasDGNSScor;
	int						hasSNR;
	int						hasAnyCodeMeas;
	enum MeasurementType	NoSNRforWeightMeas;
	double					lowSNR;
	double					URAValue;
	int						available;
	char					hasHealthStr[30];
	char					badSNRText[MAX_PRINT_LINE_TEPOCH];
	char					MissingMeasText[MAX_PRINT_LINE_TEPOCH];
	char					SFUnconsistencyText[MAX_PRINT_LINE_TEPOCH];
} TSatellite;

// Antenna structure
typedef struct {
	char			type[MAX_ANTENNA_NAME];
	char			type_ant[MAX_ANTENNA_NAME];
	char			type_radome[MAX_ANTENNA_NAME];
	double			PCO[MAX_GNSS][MAX_FREQUENCIES_PER_GNSS][3];	// Antenna Phase Center Offset [PCO]  (North - East - Up)

	double			azi1;	//Stored in degrees
	double			azi2;	//Stored in degrees
	double			dazi;	//Stored in degrees
	int				numazi;

	double			zen1;	//Stored in degrees
	double			zen2;	//Stored in degrees
	double			dzen;	//Stored in degrees
	int				nzen;

	double			***noazi;	//Non-azimuth-dependent pattern values (dependent on constellation and frequency)
	double			****azi;	//Azimuth-dependent pattern values (dependent on constellation,frequency and azimuth)
} TAntenna;

// Receiver structure
typedef struct {
	char 				name[MAX_RECEIVER_NAME];
	char				type[MAX_RECEIVER_NAME];
	double				aproxPosition[3];		// X - Y - Z
	double				aproxPositionError;
	double				aproxPositionNEU[3];		// Latitude - Longitude - Height
	double				aproxPositionRover[3];		// X - Y - Z (for DGNSS using ROVER position from user or RINEX when printing error)
	double				aproxPositionNEURover[3];		// X - Y - Z (for DGNSS using ROVER position from user or RINEX when printing error)
	double				aproxPositionRef[3];		// X - Y - Z (for Rover, read from reference file for printing error)
	double				aproxPositionNEURef[3];		// X - Y - Z (for Rover, read from reference file for printing error)
	double				orientationRover[3][3];
	double				orientationRef[3][3];		//Orientation of position from reference file
	double				interval;
	double				intervalEstimate;		//Estimation of interval by substracting Second epoch time minus first epoch
	double				orientation[3][3];
	double				ARP[3];				// Antenna Reference Point
	enum ReceiverType	recType;
	TAntenna			antenna;
	int					receiverSolConverged;
	int					numRecStation;			//Number of Receiver stations read
	double				**RecStationCoord;		//Coordinates of the receiver stations (X Y Z)
	TTime				*ChangedStaEpoch;		//Epoch where new station coordinates arrive
	int					look4interval;
	int					intervalDecimalsFactor;	//Factor for which to know how much decimals to consider for receiver intervals greaters than 1Hz
	long long int		DecimateVal;			//Decimation value for receiver intervals greaters than 1Hz. It is saved here as it is computed when interval is computed or read
	int					RefPositionAvail;		//Set if position from reference file is available
	enum OUTDiffField	OUTPUTDiffFieldsMode;
} TReceiver;

// Measurement order structure
typedef struct {
	enum GNSSystem			GNSS;
	int						nDiffMeasurements;				//This value may differ 1 from the RINEX header if GPS C1 or P1 is not present and C1==P1[+DCB]
	int						nDiffMeasurementsRINEXHeader;
	int						meas2Ind[MAX_MEASUREMENTS_NO_COMBINATIONS];
	int						meas2SNRInd[MAX_MEASUREMENTS_NO_COMBINATIONS]; //This index saves in what measurement it has to look for the SNR value
	int						availFreq[MAX_FREQUENCIES_PER_GNSS];
	enum MeasurementType	ind2Meas[MAX_MEASUREMENTS_PER_SATELLITE];
	double					conversionFactor[MAX_MEASUREMENTS_NO_COMBINATIONS]; // This factor is to allow changing from carrier-phase cycles to metres.
	double					lambdaMeas[MAX_FREQUENCIES_PER_GNSS][MAX_SATELLITES_PER_GNSS]; // This factor is to store the lambda per satellite
	double					freqMeas[MAX_FREQUENCIES_PER_GNSS][MAX_SATELLITES_PER_GNSS]; // This factor is to store the frequency per satellite
	double					mfreqMeas[MAX_FREQUENCIES_PER_GNSS][MAX_SATELLITES_PER_GNSS]; // This factor is to store the mfrequency factor per satellite
	double					TECU2metres[MAX_FREQUENCIES_PER_GNSS][MAX_SATELLITES_PER_GNSS]; // This factor is to store the conversion factor fro TECU to metres per satellite
	double					filterMeaslambda[MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT];	//Lambda of the measurements in the filter (including combinations)
	int						hasGlonassSlotsFreq; //0 -> not available 1-> Read from RINEX observation file 2-> Read from RINEX navigation file
	int						numFreqOffsetRead; 	//Number of frequency offsets read from RINEX observation file
	int						SNRmeaspos[MAX_FREQUENCIES_PER_GNSS];
	double					IGFcombFactors[MAX_SATELLITES_PER_GNSS][MAX_TRIPLE_FREQUENCIES_COMBINATIONS][NUM_COMB_IGF_MIN_NOISE];

	//Measurement lists
	int						numMeasToCopy; //Number of measurements needed to be copied
	enum MeasurementType	measListToCopy[MAX_CODE_MEASUREMENTS_NO_COMBINATIONS];	//List of measurements that need data copied into them							
	int						meas2SourceInd[MAX_CODE_MEASUREMENTS_NO_COMBINATIONS]; //Index of the source meas to copy from

	int						numMeasListToCheckSNR[MAX_SATELLITES_PER_GNSS];	//Number of measurements to be checked its SNR
	enum MeasurementType	measListToCheckSNR[MAX_SATELLITES_PER_GNSS][MAX_PHASE_MEASUREMENTS_NO_COMBINATIONS];	//List of measurements to be checked its SNR (CS + Filter)

	int						numMeasListDataGap[MAX_SATELLITES_PER_GNSS];   //Number of measurements to check data gap
	int						measIndListDataGap[MAX_SATELLITES_PER_GNSS][MAX_MEASUREMENTS_NO_COMBINATIONS_NO_SNR];    //List of measurement positions to check data gap
	enum MeasurementType    measListDataGap[MAX_SATELLITES_PER_GNSS][MAX_MEASUREMENTS_NO_COMBINATIONS_NO_SNR];    //List of measurements to check data gap

	int						numMeasListToCheckLLI[MAX_SATELLITES_PER_GNSS];	//Number of measurements to be checked by LLI cs detector
	int						measIndListToCheckLLI[MAX_SATELLITES_PER_GNSS][MAX_PHASE_MEASUREMENTS_NO_COMBINATIONS];	//List of measurement positions to be checked by LLI cs detector
	enum MeasurementType	measListToCheckLLI[MAX_SATELLITES_PER_GNSS][MAX_PHASE_MEASUREMENTS_NO_COMBINATIONS];	//List of measurements to be checked by LLI cs detector

	int						numMeasListToBeModelled[MAX_SATELLITES_PER_GNSS];	//Number of measurements to be modelled
	enum MeasurementType	measListToBeModelled[MAX_SATELLITES_PER_GNSS][MAX_MEASUREMENTS_NO_COMBINATIONS_NO_SNR];	//List of measurements to be modelled
	char					measListToBeModelledStr[MAX_SATELLITES_PER_GNSS][MAX_MEASUREMENTS_NO_COMBINATIONS_NO_SNR][4];	//List of measurements to be modelled


	int						numPhaseMeasListToBeModelled[MAX_SATELLITES_PER_GNSS];	//Number of carrier phase measurements to be modelled (to be used only for computing transmision time when carrier phases are absolute)
	enum MeasurementType	phaseMeasListToBeModelled[MAX_SATELLITES_PER_GNSS][MAX_MEASUREMENTS_NO_COMBINATIONS_NO_SNR];	//List of carrier phase measurements to be modelled

	int						numDualFreqDCBFreqList[MAX_SATELLITES_PER_GNSS];	//Number of dual frequency DCBs to be computed
	int						DualFreqDCBFreqList[MAX_SATELLITES_PER_GNSS][MAX_DIFF_DUALFREQDCB];	//Frequencies of the combination in a single number
	int						DualFreqDCBFilterMeasPos[MAX_SATELLITES_PER_GNSS][MAX_DIFF_DUALFREQDCB]; //Meas Position in Filter list where to apply the DCB

	int						numMeasPosToFilterPos[MAX_SATELLITES_PER_GNSS][MAX_MEASUREMENTS_NO_COMBINATIONS_NO_SNR];	
												//Number of times the modelled measurement appears in the filter measurements
	int						MeasPosToFilterPos[MAX_SATELLITES_PER_GNSS][MAX_MEASUREMENTS_NO_COMBINATIONS_NO_SNR][MAX_FILTER_MEASUREMENTS_SAT];
												//Meas modelled to the position it appears in the filter

	int						numMeasPosToFilterPosSingleFreq[MAX_SATELLITES_PER_GNSS][MAX_MEASUREMENTS_NO_COMBINATIONS_NO_SNR];	
												//Number of times the modelled measurement appears in the filter measurements for single frequency measurements
	int						MeasPosToFilterPosSingleFreq[MAX_SATELLITES_PER_GNSS][MAX_MEASUREMENTS_NO_COMBINATIONS_NO_SNR][MAX_FILTER_MEASUREMENTS_SAT];
												//Meas modelled to the position it appears in the filter for single frequency measurements

	int						numPhaseMeasFilterToCSSF[MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS];   
								//Number of phase measurements (by frequency) set in the filter by user that must be checked by cycle-slip detectors
	enum MeasurementType	PhaseMeasFilterToCSSF[MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS][MAX_PHASE_MEASUREMENTS_NO_COMBINATIONS];	
								//List of phase measurements (by frequency) set in the filter by user that must be checked by cycle-slip detectors

	int						numPhaseMeasFilterToCSMW[MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS];   
								//Number of phase measurements (by frequency) set in the filter by user that must be checked by cycle-slip detectors
	enum MeasurementType	PhaseMeasFilterToCSMW[MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS][MAX_PHASE_MEASUREMENTS_NO_COMBINATIONS];	
								//List of phase measurements (by frequency) set in the filter by user that must be checked by cyle-slip detectors

	int						numPhaseMeasFilterToCSLI[MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS];   
								//Number of phase measurements (by frequency) set in the filter by user that must be checked by cycle-slip detectors
	enum MeasurementType	PhaseMeasFilterToCSLI[MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS][MAX_PHASE_MEASUREMENTS_NO_COMBINATIONS];	
								//List of phase measurements (by frequency) set in the filter by user that must be checked by cycle-slip detectors

	int						numPhaseMeasFilterToCSIGF[MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS];   
								//Number of phase measurements (by frequency) set in the filter by user that must be checked by cyle-slip detectors
	enum MeasurementType	PhaseMeasFilterToCSIGF[MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS][MAX_PHASE_MEASUREMENTS_NO_COMBINATIONS];	
								//List of phase measurements (by frequency) set in the filter by user that must be checked by cycle-slip detectors

	int						numCodeMeasurements;	//Number of pseudorange measurements in RINEX per constellation (all frequencies)
	enum MeasurementType	CodeMeasurements[MAX_PHASE_MEASUREMENTS_NO_COMBINATIONS]; //List of pseudorange measurements in RINEX per constellation (all frequencies)

	int						numCarrierPhaseMeasurements;	//Number of carrier phase measurements in RINEX per constellation (all frequencies)
	enum MeasurementType	CarrierPhaseMeasurements[MAX_PHASE_MEASUREMENTS_NO_COMBINATIONS]; //List of carrier phase measurements in RINEX per constellation (all frequencies)

	//Index for printing order for PREFIT and POSTFIT messages (so output is printed sorted by constellation and measurement type)
	int						numMeasIndexed[MAX_MEASKIND_PRINT_MEASUREMENTS];	//Number of measurements indexed (all types)
	int						numMeasSmoothIndexed[MAX_FILTER_MEASUREMENTS_SAT];	//Intermidiate counter for number of smoothed measurements (a smoothed measurements can be smoothed with several measurements types)
	long long int			MeasCodeIndexed[MAX_MEASKIND_PRINT_MEASUREMENTS][MAX_FILTER_MEASUREMENTS_SAT]; //Unique code of the measurement by measurement kind
	long long int			SmoothMeasCodeIndexed[MAX_FILTER_MEASUREMENTS_SAT][MAX_FILTER_MEASUREMENTS_SAT]; //Unique code of the measurement for smoothed measurements
	int						PosSmoothCode2Index[MAX_FILTER_MEASUREMENTS_SAT][MAX_FILTER_MEASUREMENTS_SAT];	//For a certain code smoothed, save position for each different smoothing measurement used for the same code
	int						MeasPos2PrintPos[MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT];	//Filter position to print position
} TMeasOrder;

// Cycle slip data structure
typedef struct {
	TTime		tPrevLI[MAX_SATELLITES_VIEWED][MAX_CS_LIST][MAX_CS_MEMORY];
	TTime		tPrevIGF[MAX_SATELLITES_VIEWED][MAX_CS_LIST][MAX_CS_MEMORY];
	TTime		tPrevMW[MAX_SATELLITES_VIEWED][MAX_CS_LIST][MAX_CS_MEMORY];
	TTime		previousEpoch[MAX_SATELLITES_VIEWED];
	TTime		previousEpochNconsecutive[MAX_SATELLITES_VIEWED];
	TTime		lastModelledEpoch[MAX_SATELLITES_VIEWED];
	double		LIPrev[MAX_SATELLITES_VIEWED][MAX_CS_LIST][MAX_CS_MEMORY];
	double		IGFPrev[MAX_SATELLITES_VIEWED][MAX_CS_LIST][MAX_CS_MEMORY];
	double		MWPrev[MAX_SATELLITES_VIEWED][MAX_CS_LIST][MAX_CS_MEMORY];
	int			outlierLI[MAX_SATELLITES_VIEWED];
	int			outlierIGF[MAX_SATELLITES_VIEWED];
	int			outlierMW[MAX_SATELLITES_VIEWED];
	int			anyOutlier[MAX_SATELLITES_VIEWED];
	int			preCheck[MAX_SATELLITES_VIEWED];
	int			CS[MAX_SATELLITES_VIEWED];
	int			CSPrealignFlag[MAX_SATELLITES_VIEWED];
	int			consistency[MAX_SATELLITES_VIEWED];
	int			narc[MAX_SATELLITES_VIEWED];
	int			arcLength[MAX_SATELLITES_VIEWED];
	int			hasBeenCycleslip[MAX_SATELLITES_VIEWED];
	int			use4smooth[MAX_SATELLITES_VIEWED];
	int			Nconsecutive[MAX_SATELLITES_VIEWED];
	double		MWsigma[MAX_SATELLITES_VIEWED][MAX_CS_LIST];
	double		initialLI[MAX_SATELLITES_VIEWED][MAX_CS_LIST];
	double		initialIGF[MAX_SATELLITES_VIEWED][MAX_CS_LIST];
	double		MWmean[MAX_SATELLITES_VIEWED][MAX_CS_LIST];
	double		MWmean300[MAX_SATELLITES_VIEWED][MAX_CS_LIST];
	double		windowMW[MAX_SATELLITES_VIEWED][MAX_CS_LIST][MAX_SLIDING_WINDOW];
	double		windowMWtime[MAX_SATELLITES_VIEWED][MAX_CS_LIST][MAX_SLIDING_WINDOW];
	double		windowSF[MAX_SATELLITES_VIEWED][MAX_CS_LIST][MAX_SLIDING_WINDOW];
	double		windowSFtime[MAX_SATELLITES_VIEWED][MAX_CS_LIST][MAX_SLIDING_WINDOW];
	double		preAlign[MAX_SATELLITES_VIEWED][MAX_MEASUREMENTS_PER_SATELLITE];
	double		windUpRadAccumReceiver[MAX_SATELLITES_VIEWED];
	double		windUpRadAccumReceiverPrev[MAX_SATELLITES_VIEWED];
	double		windUpRadAccumSatellite[MAX_SATELLITES_VIEWED];
	double		windUpRadAccumSatellitePrev[MAX_SATELLITES_VIEWED];
	double		smoothedMeas[MAX_SATELLITES_VIEWED][MAX_FILTER_MEASUREMENTS_SAT];
	double		SFmean[MAX_SATELLITES_VIEWED][MAX_CS_LIST];
	double		SFsigma[MAX_SATELLITES_VIEWED][MAX_CS_LIST];
	double		SFPhasePrev[MAX_SATELLITES_VIEWED][MAX_CS_LIST];
	double		SFCodePrev[MAX_SATELLITES_VIEWED][MAX_CS_LIST];
} TCS;

// DGNSS data structure
typedef struct {
	int			Nref;
	int			msg[MAX_SATELLITES_VIEWED];
	int			UDRE[MAX_SATELLITES_VIEWED];
	int			health[MAX_SATELLITES_VIEWED];
	int			IODmsg1[MAX_SATELLITES_VIEWED];
	int			IODmsg2[MAX_SATELLITES_VIEWED];
	double		CLKref;
	double		epsURA;
	double		PRC[MAX_SATELLITES_VIEWED];
	double		deltaPRC[MAX_SATELLITES_VIEWED];
	double		PRCp[MAX_SATELLITES_VIEWED];
	double		RRC[MAX_SATELLITES_VIEWED];
	double		deltaRRC[MAX_SATELLITES_VIEWED];
	double		sigmaInflation[MAX_SATELLITES_VIEWED];
	double		sigmaURA3[MAX_SATELLITES_VIEWED];
	double		sigmaURA3p[MAX_SATELLITES_VIEWED];
	double		C1[MAX_SATELLITES_VIEWED];
	double		C1s[MAX_SATELLITES_VIEWED];
	TTime		tPRC[MAX_SATELLITES_VIEWED];
	TTime		tdeltaPRC[MAX_SATELLITES_VIEWED];
	TTime		tPRCp[MAX_SATELLITES_VIEWED];
} TDGNSS;

// SatInfo structure
typedef struct {
	TTime		lastEclipse;
} TSatInfo;


typedef struct {
	int				Buffer_numsatdiscardedSBAS;					//Number of satellites discarded by SBAS in each iteration
	int				Buffer_usableSatellites;					//Number of available satellites in each iteration
	int				Buffer_usableSatellitesGNSS[MAX_GNSS];		//Number of available satellites per GNSS in each iteration
	int				Buffer_discardedSatellites;					//Number of discarded satellites in each iteration
	int				Buffer_discardedSatellitesGNSS[MAX_GNSS];	//Number of discarded satellites per GNSS in each iteration
	int				Buffer_numConstellationsUsed;				//Number of constellations used in each iteration
	int				Buffer_numConstellationsNotUsed;			//Number of constellations not used in each iteration
	int				Buffer_constellationUsed[MAX_GNSS];			//Constellations used in each iteration
	int				Buffer_constellationNotUsed[MAX_GNSS];		//Constellations not used in each iteration
	int				Buffer_totalNumAmbiguitiesEpoch;			//Total number of ambiguities in each iteration
	int				Buffer_numInterSystemClocksFilter;			//Number of Inter system clock bias in Filter in each iteration
	enum GNSSystem	Buffer_ReferenceGNSSClock;					//Reference GNSS clock used in each iteration
	enum GNSSystem	Buffer_InterSystemClocksUnk2GNSS[MAX_GNSS+FIRST_POS_IS_CLK];	//Inter-system clock bias position to GNSS in each iteration
	enum GNSSystem	Buffer_constellationUsedList[MAX_GNSS];		//List of constellations used in each iteration 
	enum GNSSystem	Buffer_constellationNotUsedList[MAX_GNSS];	//List of constellations not used in each iteration 
	int				Buffer_InterSystemClocksPosDOP[MAX_GNSS+FIRST_POS_IS_CLK];		//Inter system clock bias position for DOP in each iteration
	int				Buffer_InterSystemClocksUnk[MAX_GNSS];		//GNSS to Inter-system clock bias position in filter in each iteration
	int				Buffer_hasInterSystemClocksUnk[MAX_GNSS];	//Flag to indicate if GNSS has inter-system clock bias in each iteration
	int				Buffer_usedSat2DataPos[MAX_SATELLITES_VIEWED];		//Get the position of Nth used satellite in 'epoch->sat[]' array
	double			Buffer_HPL;									//Horizontal Protection Level in each iteration 
	double			Buffer_VPL;									//Vertical Protection Level in each iteration
	double			Buffer_HDOP;								//Horizontal Dilution of Precision in each iteration
	double			Buffer_VDOP;								//Vertical   Dilution of Precision in each iteration
	double			Buffer_PDOP;								//Position   Dilution of Precision in each iteration
	double			Buffer_GDOP;								//Geometric  Dilution of Precision in each iteration
	double			Buffer_TDOP;								//Time       Dilution of Precision in each iteration
	char			****Buffer_printMODEL;						//Output MODEL print for each satellite in each iteration
	char			**Buffer_printSBASIONO;						//Output SBASIONO print for each satellite in each iteration
	char			**Buffer_printSBASCORR;						//Output SBASCORR print for each satellite in each iteration
	char			**Buffer_printSBASVAR;						//Output SBASVAR print for each satellite in each iteration
	char			**Buffer_printSBASUNSEL;					//Output SBASUNSEL prints for each satellite in each iteration
	char			***Buffer_printSBASDFMCCORR;				//Output SBASDFMCCORR print for each satellite in each iteration
	char			***Buffer_printSBASDFMCVAR;					//Output SBASDFMCCVAR print for each satellite in each iteration
	char			***Buffer_printSBASDFMCUNSEL;				//Output SBASDFMCUNSEL prints for each satellite in each iteration
	char			****Buffer_printSATSEL;						//Output SATSEL prints for each satellite and discard reason in each iteration
	int				**Buffer_NumMODEL;							//Number of MODEL lines printed for each satellite in each iteration
	int				**Buffer_NumSatSel;							//Number of SATSEL lines printed for each satellite in each iteration
	int				Buffer_SBASMode;							//SBAS solution mode (PA or NPA) in each iteration
	int				Buffer_GEOindex;							//GEO index in SBASdata structure in each iteration
	int				Buffer_GEOPRN;								//GEO PRN list in SBASdata structure in each iteration
	TSatellite		*Buffer_sat;								//Satellite data (including modelled values) in each iteration
} TBufferBestGEO;


// Epoch structure
typedef struct {
	TTime			FirstEpochHeader;											//First epoch in file read in "TIME OF FIRST OBS" header line, otherwise first epoch in file
	enum GNSSystem	SystemTime;													//Constellation used as reference time in the observation file
	double			ObsTimeToGPSTime; 											//If RINEX Observation file is not in GPS time, set the time diff to convert to GPS
	TTime			t;															//Current GPS epoch in TTime structure (MJDN + SoD)
	char			tStr[30]; 													//Current epoch in string format (Year Doy SoD) for printing
	char			tSoDHourStr[50]; 											//Current epoch in string format (Year Doy SoD HH:MM:SS.zz) for printing
	int				GPSweek;													//Current epoch GPS week number
	double			SoW;														//Current epoch Second of Week
	TTime			PreviousEpoch;												//Previous epoch
	TTime			firstEpochFile;												//First  epoch read in observation file
	TTime			secondEpochFile;											//Second epoch read in observation file
	int				numSatellites;												//Number of satellites in current epoch in observation file
	int				numSatellitesGNSS[MAX_GNSS];								//Number of satellites per constellation in current epoch in observation file
	int				numGNSSinEpoch;												//Number of constellations in current epoch in observation file
	int				GNSSinEpoch[MAX_GNSS];										//Constellations available in current epoch in observation file	(0 -> Not Available, 1 -> Available)
	int				constellationUsed[MAX_GNSS];								//Constellations used in the filter solution of current epoch  (0 -> Not used, 1 -> Used)
	int				constellationNotUsed[MAX_GNSS];								//Constellations not used in the filter solution of current epoch  (0 -> Used, 1 -> Not Used)
	int				prevNumInterSystemClocksFilter;								//Number of Inter-system clock bias estimated in filter in previous epoch
	int				numInterSystemClocksFilter;									//Number of Inter-system clock bias estimated in filter in current epoch
	int				numConstellationsUsed;										//Number of constellations used in filter solution in current epoch
	int				numConstellationsNotUsed;									//Number of constellations not used in filter solution in current epoch
	int				InterSystemClocksPosDOP[MAX_GNSS+FIRST_POS_IS_CLK];			//Position of the inter-system clock bias estimates in filter for each GNSS. Also, the reference constellation will have its value set to 3
	int				InterSystemClocksUnk[MAX_GNSS];								//Position of the inter-system clock bias estimates in filter for each GNSS. The reference constellation will have its value set to -1 (-1 means not used)
	int				hasInterSystemClocksUnk[MAX_GNSS];							//Flag to indicate if in current epoch a constellation has its inter-system clock bias estimated in filter (it does not include the reference constellation)
	int				prevInterSystemClocksUnk[MAX_GNSS+FIRST_POS_IS_CLK];		//Same as 'hasInterSystemClocksUnk' but for the previous epoch
	int				usedSat2DataPos[MAX_SATELLITES_VIEWED];						//Get the position of Nth used satellite in 'epoch->sat[]' array
	double			lastRecWindUpEstimated;										//Receiver WindUp estimated value in last iteration of the filter
	double			lastRecWindUpAutoCorrel;									//Receiver WindUp estimated autocorrelation value in last iteration of the filter
	enum GNSSystem	constellationUsedList[MAX_GNSS];							//List of constellations used in navigation solution (in order of inclusion in the filter)
	enum GNSSystem	constellationNotUsedList[MAX_GNSS];							//List of constellations not used in navigation solution (in order of exclusion in the filter)
	enum GNSSystem	InterSystemClocksUnk2GNSS[MAX_GNSS+FIRST_POS_IS_CLK];		//Position in filter of the inter-system clock bias to constellation
	enum GNSSystem	prevInterSystemClocksUnk2GNSS[MAX_GNSS+FIRST_POS_IS_CLK];	//Same as 'InterSystemClocksUnk2GNSS' but for previous epoch
	enum GNSSystem	ReferenceGNSSClock;											//Constellation used as reference clock in current epoch
	enum GNSSystem	prevReferenceGNSSClock;										//Constellation used as reference clock in previous epoch
	int				numSBASsatellites; 											//This variable is mirroring the value of SBASdatabox.SBASdata[0]->numSBASsatellites
	int				lastSBASindex[MAX_SAT_GEO]; 								//The slots for GEO in first dimension are set in the same order as in SBASdata structure (0 for mixed GEO, 1 for first GEO read, ...)
	int				usableSatellites;											//Number of usable satellites in navigation solution in current epoch
	int				usableSatellitesGNSS[MAX_GNSS];								//Number of usable satellites per constellation in navigation solution in current epoch
	int				discardedSatellites;										//Number of discarded satellites in navigation solution in current epoch and can at any epoch enter in the filter 
																					//(this list of discarded satellites for the summary, so satellites excluded by user or with no available measurement in observation file
																					// will never be included in the list, so the summary only prints satellites discarded but they could have been added to the filter)
	int				discardedSatellitesGNSS[MAX_GNSS];							//Number of discarded satellites per constellation in navigation solution in current epoch (same criteria as in 'discardedSatellites')
	int				totalNumAmbiguitiesEpoch;									//Number of carrier phase ambiguities estimated in the filter in current epoch
	int				numSatDCBEpoch[MAX_GNSS][MAX_SATELLITES_PER_GNSS];			//Number of satellite DCBs estimated in the filter in current epoch ()for each satellite)
	int				totalNumSatDCBEpoch;										//Number of satellite DCBs estimated in the filter in current epoch (total number estimated in filter)
	int				totalNumRecDCBEpoch;										//Number of receiver  DCBs estimated in the filter in current epoch
	int				IterationInSameEpoch;										//Flag to indicate if the filter is running again in the same epoch (it occurs when the a priori solution is very far from the real solution)
	TSatellite		sat[MAX_SATELLITES_VIEWED];									//Array with information for each satellite, in the same order as it is read in each epoch of the observation file
	TReceiver		receiver;													//Structure with information of the receiver
	int				satIndex[MAX_GNSS][MAX_SATELLITES_PER_GNSS];				//Dictionary to convert from GNSS and PRN to position in 'epoch->sat[]' array
	int				satCSIndex[MAX_GNSS][MAX_SATELLITES_PER_GNSS];				//Dictionary to convert from GNSS and PRN to position in 'epoch->cycleslip' array elements
	int				numGNSSHeader;												//Number of constellation found in header of RINEX observation file							
	TMeasOrder		measOrder[MAX_GNSS];										//Structure to save the order of measurements read in observation file
	int				flag;														//Flag read in each epoch of the observation flag to check if the epoch is flagged as event epoch
	enum Source		source;														//Type of RINEX observation file read (RINEX2 or RINEX3)
	double			RINEXobsVersion;											//RINEX observation file version
	TCS				cycleslip;													//Structure to save data for computing cycle-slips
	TDGNSS			dgnss;														//Structure to save data for DGNSS
	int				DGNSSstruct;												//Flag to indicate if current epoch structure if rover (flag equals 0) or for the reference station (flag equals 1)
	int				prealign;													//Flag to indicate if a global satellite phase prealignment has been done (otherwise skip single satellite prealignement after cycle-slip)
	double			solidTideDisplacement[3];									//Solid Tides deplacement for the station before projection to any satellite
	TSatInfo		satInfo[MAX_GNSS][MAX_SATELLITES_PER_GNSS];					//Structure with the information of epoch of last eclipse for each satellite
	double			ZTD;														//Zenith tropospheric delay (vertical dry and wet nomimal components). It does not include the residual troposphere estimated in the filter
	int				numAproxPosRead;											//Number of "APPROX POSITION XYZ" lines read for the observation file (in the header or in event epochs)
	double			IPPlat;														//Ionospheric pierce point latitude  between -90 and -90º
	double			IPPlon;														//Ionospheric pierce point longitude between -180º and 180º
	int				numSatSolutionGNSS[MAX_GNSS];								//Number of satellites per constellation included in the navigation solution in current epoch
	int				numSatnotUsedGNSS[MAX_GNSS];								//Number of satellites per constellation not used in the navigation solution in current epoch (for any reason, including satellites excluded by user)
	int				numSatSolutionFilter;										//Number of satellites included in the navigation solution in current epoch
	int				numSatNotUsedFilter;										//Number of satellites not used in the navigation solution in current epoch (for any reason, including satellites excluded by user)
	int				listPRNSatSolution[MAX_SATELLITES_VIEWED];					//List of PRNs used in navigation solution in current epoch
	int				listPRNSatnotUsed[MAX_SATELLITES_VIEWED];					//List of PRNs not used in navigation solution in current epoch
	int				listGNSSsatSolution[MAX_SATELLITES_VIEWED];					//List of constellation (saved with its ascii character number) of each satellite used in navigation solution in current epoch
	enum GNSSystem	listGNSSsatSolutionEnum[MAX_SATELLITES_VIEWED];				//List of constellation (saved with the enumerator value) of each satellite used in navigation solution in current epoch
	int				listGNSSsatnotUsed[MAX_SATELLITES_VIEWED];					//List of constellation (saved with its ascii character number) of each satellite not used in navigation solution in current epoch
	enum GNSSystem	listGNSSsatnotUsedEnum[MAX_SATELLITES_VIEWED];				//List of constellation (saved with the enumerator value) of each satellite not used in navigation solution in current epoch
	int				listPRNSatSolutionConst[MAX_GNSS][MAX_SATELLITES_PER_GNSS];	//List of PRN by constellation (in order of addition to filter) used in navigation solution in current epoch
	int				listPRNSatnotUsedConst[MAX_GNSS][MAX_SATELLITES_PER_GNSS];	//List of PRN by constellation (in order of unselection to filter) not used in navigation solution in current epoch

	int				numsatdiscardedSBAS;										//Number of satellites discarded by SBAS reasons

	int				SwitchPossible;												//0 => GEO or mode switch is not possible in current epoch
																				//1 => GEO or mode switch is possible in current epoch

	int				SBASUsedGEO;												//SBAS GEO used  in current epoch
	int				SBASUsedGEOindex;											//SBAS GEO index in SBASdata structure used  in current epoch
	int				SBASUsedMode;												//SBAS mode used in current epoch

	int				overMaxHDOP;												//0 => Epoch under HDOP threshold or HDOP threshold disabled
																				//1 => Epoch over HDOP threshold

	int				overMaxPDOP;												//0 => Epoch under PDOP threshold or PDOP threshold disabled
																				//1 => Epoch over PDOP threshold

	int				overMaxGDOP;												//0 => Epoch under GDOP threshold or GDOP threshold disabled
																				//1 => Epoch over GDOP threshold

	int				overMaxHDOPorPDOP;											//0 => Epoch under HDOP or PDOP threshold or HDOP or PDOP threshold disable
																				//1 => Epoch over HDOP or PDOP threshold

	int				TryGEOChange;												//0 => Do not try to switch GEO
																				//1 => Try to switch GEO, even if there is a solution available

	int				ResetNumSwitch;												//If 1, reset num GEO and mode switch attempts (for SBAS plots mode)
	int				currentGEOPRN;												//Current GEO selected in SBAS (this variable is for printing the GEO PRN)
	
	int				numKMLData;													//Number of slots for KMLData and KMLTime
	double			**KMLData;													//Coordinates for printing KML points with timestamps
	TTime			*KMLTime;													//Timestamps for KML file

	double			numEpochsfile;												//Number of epochs to be processed. It is computed as (LastEpoch-FirstEpoch)/RINEXobsInterval. Does not account for data gaps
																				//If backwards processing is enabled, this number is doubled if no user defined start time, otherwise it is the
																				//the total number of epochs plus the number of epochs from user defined start epoch until the end of file
																				//In SBAS plots mode, it is accounted as 86400 or (86400 - Initial epoch of SBAS data file) if SBAS data starts after 0h

	double			numEpochsfileNoBackwards;									//Number of epochs in file, without taking into account if backwards processing is enabled o

	double			numEpochsprocessed;											//Number of epochs processed in the observation file (without decimation). It is for printing progress percentage
	double			CurrentPercentage;											//Current percentage of total data processed
	double			PreviousPercentage;											//Previous value of percentage of total data processed
	int				NewPercentage;												//Flag to indicate that a new percentage has been computed and can be shown (it can occur that a new epoch is read, but still it is not the first to be processed)

	int				BRDCAnyType[MAX_GNSS];										//Vector with the position of 'Any Broadcast message' type for each GNSS

	int				MeasToBeDuplicated;											//Flag to indicate if any measurement has to be duplicated (e.g. C1C to C1P for NoP1 receivers)

	int				IGFminNoise;												//Flag to indicate if IGF is built with minimum noise instead of two LC (copied from Toptions structure)

	int				GLOfreqnumber[MAX_SATELLITES_PER_GNSS];						//GLONASS frequency number (k) for each satellite
	int				leapSeconds;												//Leap seconds for converting GLONASS to GPS time
	int				leapSecondsAvail;											//Flag to indicate if leap seconds are available from RINEX file


	//Variables to check if two single frequencies for different frequencies have been selected (only when estimating Iono, satellite DCB or receiver DCB)
	int				dualFreqSingleMeasUnavail[MAX_GNSS][MAX_SATELLITES_PER_GNSS];	//Flag to indicate if the satellite did not have selected at least two single measurements from different frequencies.
	char			dualFreqSingleMeasUnavailText[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_PRINT_LINE_TEPOCH]; //Text showing the selected and unavailable frequencies when satellite is unselected

	//Variable to check if the iono-free reference measurements are available (necessary only for Fast-PPP)
	int				dualFreqIFRefMeasUnavail[MAX_GNSS][MAX_SATELLITES_PER_GNSS]; //Flag to indicate if the satellite did not have selected the iono-free reference measurements
	char			dualFreqIFRefMeasUnavailText[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_PRINT_LINE_TEPOCH]; //Text showing the unavailable measurement and the required measurements when satellite is unselected

	//Variables to save ambiguities and satellite DCBs from the filter, so they can be restored after a satellite dissappears during few epochs without cycle-slip
	int				satHasBeenUsedInFilter[MAX_GNSS][MAX_SATELLITES_PER_GNSS]; // 0-> Satellite not used in filter since the last cycle-slip	
																			// 1-> Satellite     used in filter since the last cycle-slip 
	double			lastAmbValEstimatedNotInFilter[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_AMBIGUITIES_FILTER];	//When an ambiguity is removed from the filter, its last value is saved, only reseted after a cycle-slip
	double			lastAmbCorEstimatedNotInFilter[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_AMBIGUITIES_FILTER];	//When an ambiguity is removed from the filter, its last auto-correlation is saved, only reseted after a cycle-slip
	double			lastSatDCBValEstimatedNotInFilter[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_AMBIGUITIES_FILTER];	//When a satellite DCB is removed from the filter, its last value is saved
	double			lastSatDCBEstimatedNotInFilter[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_AMBIGUITIES_FILTER];		//When a  satellite DCB is removed from the filter, its last auto-correlation is saved


	//Variables to save satellite DCB position
	int 			satDCBlist[MAX_FILTER_SATELLITE_DCB];	//List of of receiver DCBs in current epoch in the filter (for phase measurements, it will be assigned to its paired pseudorange)
	int				satDCBpos2usableSatPos[MAX_FILTER_SATELLITE_DCB];	//Transform from position of satellite DCB to the position in usable satellites list
	int				filterMeasPosToSatDCBlistPos[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT];   //Filter position to unknown number in the filter relative to the start of sat DCB unknowns

	//Variables to save receiver DCB position
	int 			recDCBlist[MAX_FILTER_RECEIVER_DCB];	//List of of receiver DCBs in current epoch in the filter (for phase measurements, it will be assigned to its paired pseudorange)
	int				filterMeasPosToRecDCBlistPos[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT];	//Filter position to position in recDCBlist (unknown number in the filter relative to the start of rec DCB unknowns)
	int				RecDCBPosToLink[MAX_GNSS][2];			//Position in the list of filter unknowns of the two receiver DCBs to be linked toguether by constellation

	//Processing direction
	enum ProcessingDirection	direction;				//Current processing direction, Forward or Backward

	//Variables to save file position at the start of each valid epoch (non event epoch)
	off_t			*epochReadFilePos;			//Positions in file (provided by ftell) of each valid epoch read
	int				numEpochReadFilePos;		//Number of positions saved. When in backwards mode, it will decreasing to point to the current epoch to rollback
	int				maxNumEpochReadFilePos;		//Maximum number of epochs that fit in epochReadFilePos, When full, buffer size will be enlarged by a factor 2

	//Variables for buffering output solution (variables to be used after printOutput function is called)
	double			SolErrorXYZ[3];				//Solution error in XYZ
	double			SolErrorNEU[3];				//Solution error in NEU
	double			SolHError;					//Horizontal solution error
	double			SolVError;					//Vertical solution error (absolute value of error of up component)
	double			SolError3DNEU;				//3D error from NEU components error
	double			FormalErrorNEU[3];          //Formal error in NEU
	double			FormalErrorHor;  	 	    //Horizontal Formal error
	double			FormalErrorVer;  	 	    //Vertical Formal error
	double			FormalError3DNEU;  	 	    //3D Formal error in NEU

	//Variables for buffering first line of header found when more than one header is in the observation file
	char			bufferHeaderLine[MAX_INPUT_LINE];
	int				bufferHeaderLineLen;
	
	//Variables for printing order
	int				printIndex2satIndex[MAX_SATELLITES_VIEWED];
	int				sat2Printpos[MAX_SATELLITES_VIEWED];
	int				numPrintGNSS;
	int				GNSS2PrintPos[MAX_GNSS];
	enum GNSSystem	PrintPos2GNSS[MAX_GNSS];

	//Variables for grouping satellites of all constellations by measurements (for EPOCHSAT print)
	int				numMeasAllGNSSIndexed;			//Number of measurements indexed for all satellites
	int				*numMeasSmoothAllGNSSIndexed;	//Intermidiate counter for number of smoothed measurements (a smoothed measurements can be smoothed with several measurements types) for all satellites
	long long int	*MeasCodeAllGNSSIndexed;		//Unique code of the measurement for all satellites
	long long int	**SmoothMeasCodeAllGNSSIndexed; //Unique code of the measurement for smoothed measurements for all satellites
	int				**PosSmoothCodeAllGNSS2Index;	//For a certain code smoothed, save position for each different smoothing measurement used for the same code for all satellites
	int				MeasPosAllGNSS2PrintPos[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT];	//Filter position to print position for all satellites
	char			**MeasStrAllGNSSIndexed;		//String with the measurement name (it will a pointer to filterMeasText variable)
	char			**MeasStrSmoothAllGNSSIndexed;	//String with the measurement name (it will a pointer to filterSmoothMeasText variable)
	int				*printTypeAllGNSSAllIndexed;


	//Variables for backing up data when selecting the GEO with smallest protection levels
	int				Buffer_NumDataStoredAlloc;					//Number of iterations allocated in memory
	int				Buffer_numSatellitesAlloc;					//Number of satellites allocated in memory (will be always the largest of each iteration)
	int				Buffer_numSatellitesGNSSAlloc;				//Number of satellites per GNSS allocated in memory (will be always the largest of each iteration)
	int				Buffer_numPrintGNSSAlloc;					//Number of print lines allocated in memory (will be always the largest of each iteration)
	int				Buffer_linesstoredMODELAlloc;				//Number of MODEL print lines allocated in memory (will be always the largest of each iteration)
	int				Buffer_linesstoredSATSELAlloc;				//Number of SATSEL print lines allocated in memory (will be always the largest of each iteration)
	int				Buffer_NumDataStored;						//Total number of iterations saved
	int				Buffer_NumDataStoredUnderAlarmLimitsPA; 	//Number of iterations saved in PA mode and under alarm limits
	int				Buffer_NumDataStoredPA;						//Number of iterations saved in PA mode
	int				Buffer_NumDataStoredNPA;					//Number of iterations saved in NPA mode
	int				*Buffer_PosDataStoredUnderAlarmLimitsPA;	//Index position of iterations saved in PA mode and under alarm limits
	int				*Buffer_PosDataStoredPA;					//Index position of iterations saved in PA mode
	int				*Buffer_PosDataStoredNPA;					//Index position of iterations saved in NPA mode
	TBufferBestGEO	*BufferBestGEO;								//Block of buffered data for each model iteration
	
	//Data for summary
	int				TotalEpochs;									//Total epochs processed in summary period
	int				TotalEpochsForward;								//Total epochs processed in summary period in forward direction only
	int				TotalEpochsDecimated;							//Total epochs decimated in summary period
	int				TotalEpochsDecimatedForward;					//Total epochs decimated in summary period in forward direction only
	int				TotalEpochsFile;								//Total epochs in observation file
	int				TotalEpochsSol;									//Total epochs processed with solution in SPP/PPP modes
	int				TotalEpochsDGNSS;								//Total epochs processed with solution in DGNSS mode
	int				TotalEpochsSPP;									//Total epochs processed with solution in SPP when using DGNSS mode
	int				TotalEpochsRef;									//Total epochs processed with solution and position from reference file
	int       	 	NumNoRefSumSkipped;								//Number of epochs skipped in the summary due to no position from reference file
	int        		NumNoRefSolSkipped;								//Number of epochs skipped due to no position from reference file
	int				NumNoRefGNSSSkipped;							//Number of epochs skipped due to the reference constellation is not available
	int				NumDOPSkipped;									//Number of epochs skipped due to bad DOP (any DOP)
	int				NumHDOPSkipped;									//Number of epochs skipped due to bad HDOP
	int				NumPDOPSkipped;									//Number of epochs skipped due to bad PDOP
	int				NumGDOPSkipped;									//Number of epochs skipped due to bad GDOP
	int				NumHDOPorPDOPSkipped;							//Number of epochs skipped due to bad HDOPorPDOP
	int				NumSingularMatrixSkipped;						//Number of epochs skipped due to singular geometry matrix
	int				NumNoSatSkipped;								//Number of epochs skipped due to lack of satellites
	int				CurrentDataGapSize;								//Data gap size of the last detected data gap
	int				NumDataGapsSum;									//Number of data gaps during summary
	int				NumDataGapsTotal;								//Number of data gaps in whole file
	int				MaxDataGapSizeSum;								//Maximum data gap size during summary
	int				MaxDataGapSizeTotal;							//Maximum data gap size in whole file
	int				NumEpochsMissingSum;							//Number of epochs missing in summary (used for refernce station)
	int				NumEpochsMissingTotal;							//Number of epochs missing in whole file (used for refernce station)
	int				*NumSatUsed;									//Array with number of satellites used in each epoch
	int				*NumSatUsedGNSS[MAX_GNSS];						//Array with number of satellites used in each epoch per constellation
	int				*NumSatNotUsed;									//Array with number of satellites not used (and not manually unselected) in each epoch
	int				*NumSatNotUsedGNSS[MAX_GNSS];					//Array with number of satellites not used (and not manually unselected) in each epoch per constellation
	int				MinNumSatUsed;									//Minimum number of satellites used
	int				MinNumSatUsedGNSS[MAX_GNSS];					//Minimum number of satellites used per constellation (for each constellation independently)
	int				MinNumAllSatUsedGNSS[MAX_GNSS];					//Minimum number of satellites used per constellation (for the epoch with max number of satellites used)
	int				MaxNumSatUsed;									//Maximum number of satellites used
	int				MaxNumSatUsedGNSS[MAX_GNSS];					//Maximum number of satellites used per constellation (for each constellation independently)
	int				MaxNumAllSatUsedGNSS[MAX_GNSS];					//Maximum number of satellites used per constellation (for the epoch with max number of satellites used)
	int				MinNumSatNotUsed;								//Minimum number of satellites not used and not manually unselected
	int				MinNumSatNotUsedGNSS[MAX_GNSS];					//Minimum number of satellites not used per constellation and not manually unselected (for each constellation independently)
	int				MinNumAllSatNotUsedGNSS[MAX_GNSS];				//Minimum number of satellites not used per constellation and not manually unselected (for the epoch with max number of satellites used)
	int				MaxNumSatNotUsed;								//Maximum number of satellites not used and not manually unselected
	int				MaxNumSatNotUsedGNSS[MAX_GNSS];					//Maximum number of satellites not used per constellation and not manually unselected (for each constellation independently)
	int				MaxNumAllSatNotUsedGNSS[MAX_GNSS];				//Maximum number of satellites not used per constellation and not manually unselected (for the epoch with max number of satellites used)
	int				NumSatUsedPercentSamples;						//95th of number of satellites used
	int				NumSatUsedPercentSamplesGNSS[MAX_GNSS];			//95th of number of satellites used per constellation
	int				NumSatNotUsedPercentSamples;					//95th of number of satellites not used and not manually unselected
	int				NumSatNotUsedPercentSamplesGNSS[MAX_GNSS];		//95th of number of satellites not used per constellation and not manually unselected
	int				NumSatUsed50PercentSamples;						//50th of number of satellites used
	int				NumSatUsed50PercentSamplesGNSS[MAX_GNSS];		//50th of number of satellites used per constellation
	int				NumSatNotUsed50PercentSamples;					//50th of number of satellites not used and not manually unselected
	int				NumSatNotUsed50PercentSamplesGNSS[MAX_GNSS];	//50th of number of satellites not used per constellation and not manually unselected
	int				NumSatMaxHDOP;									//Number of satellites used in the epoch with maximum HDOP
	int				NumSatMaxHDOPGNSS[MAX_GNSS];					//Number of satellites used per constellation in the epoch with maximum HDOP
	int				NumSatMinHDOP;									//Number of satellites used in the epoch with minimum HDOP
	int				NumSatMinHDOPGNSS[MAX_GNSS];					//Number of satellites used per constellation in the epoch with minimum HDOP
	int				NumSatMaxPDOP;									//Number of satellites used in the epoch with maximum PDOP
	int				NumSatMaxPDOPGNSS[MAX_GNSS];					//Number of satellites used per constellation in the epoch with maximum PDOP
	int				NumSatMinPDOP;									//Number of satellites used in the epoch with minimum PDOP
	int				NumSatMinPDOPGNSS[MAX_GNSS];					//Number of satellites used per constellation in the epoch with minimum PDOP
	int				NumSatMaxGDOP;									//Number of satellites used in the epoch with maximum GDOP
	int				NumSatMaxGDOPGNSS[MAX_GNSS];					//Number of satellites used per constellation in the epoch with maximum GDOP
	int				NumSatMinGDOP;									//Number of satellites used in the epoch with minimum GDOP
	int				NumSatMinGDOPGNSS[MAX_GNSS];					//Number of satellites used per constellation in the epoch with minimum GDOP
	int				NumSatMaxVDOP;									//Number of satellites used in the epoch with maximum VDOP
	int				NumSatMaxVDOPGNSS[MAX_GNSS];					//Number of satellites used per constellation in the epoch with maximum VDOP
	int				NumSatMinVDOP;									//Number of satellites used in the epoch with minimum VDOP
	int				NumSatMinVDOPGNSS[MAX_GNSS];					//Number of satellites used per constellation in the epoch with minimum VDOP
	int				NumSatMaxTDOP;									//Number of satellites used in the epoch with maximum TDOP
	int				NumSatMaxTDOPGNSS[MAX_GNSS];					//Number of satellites used per constellation in the epoch with maximum TDOP
	int				NumSatMinTDOP;									//Number of satellites used in the epoch with minimum TDOP
	int				NumSatMinTDOPGNSS[MAX_GNSS];					//Number of satellites used per constellation in the epoch with minimum TDOP
	int				NumSatMaxNError;								//Number of satellites used in the epoch with maximum North Error
	int				NumSatMaxNErrorGNSS[MAX_GNSS];					//Number of satellites used per constellation in the epoch with maximum North Error
	int				NumSatMaxEError;								//Number of satellites used in the epoch with maximum East Error
	int				NumSatMaxEErrorGNSS[MAX_GNSS];					//Number of satellites used per constellation in the epoch with maximum East Error
	int				NumSatMaxHError;								//Number of satellites used in the epoch with maximum Horizontal Error
	int				NumSatMaxHErrorGNSS[MAX_GNSS];					//Number of satellites used per constellation in the epoch with maximum Horizontal Error
	int				NumSatMaxVError;								//Number of satellites used in the epoch with maximum Vertical Error
	int				NumSatMaxVErrorGNSS[MAX_GNSS];					//Number of satellites used per constellation in the epoch with maximum Vertical Error
	int				NumSatMax3DError;								//Number of satellites used in the epoch with maximum 3D Error
	int				NumSatMax3DErrorGNSS[MAX_GNSS];					//Number of satellites used per constellation in the epoch with maximum 3D Error
	int				NumSatHWIR;										//Number of satellites used in the epoch with worst horizontal integrity ratio
	int				NumSatHWIRGNSS[MAX_GNSS];						//Number of satellites used per constellation in the epoch with worst horizontal integrity ratio
	int				NumSatHBIR;										//Number of satellites used in the epoch with best horizontal integrity ratio
	int				NumSatHBIRGNSS[MAX_GNSS];						//Number of satellites used per constellation in the epoch with best horizontal integrity ratio
	int				NumSatVWIR;										//Number of satellites used in the epoch with worst vertical integrity ratio
	int				NumSatVWIRGNSS[MAX_GNSS];						//Number of satellites used per constellation in the epoch with worst vertical integrity ratio
	int				NumSatVBIR;										//Number of satellites used in the epoch with best vertical integrity ratio
	int				NumSatVBIRGNSS[MAX_GNSS];						//Number of satellites used per constellation in the epoch with best vertical integrity ratio
	int				NumSatMaxHPL;									//Number of satellites used in the epoch with maximum horizontal protection level
	int				NumSatMaxHPLGNSS[MAX_GNSS];						//Number of satellites used per constellation in the epoch with maximum horizontal protection level
	int				NumSatMinHPL;									//Number of satellites used in the epoch with minimum horizontal protection level
	int				NumSatMinHPLGNSS[MAX_GNSS];						//Number of satellites used per constellation in the epoch with minimum horizontal protection level
	int				NumSatMaxVPL;									//Number of satellites used in the epoch with maximum vertical protection level
	int				NumSatMaxVPLGNSS[MAX_GNSS];						//Number of satellites used per constellation in the epoch with maximum vertical protection level
	int				NumSatMinVPL;									//Number of satellites used in the epoch with minimum vertical protection level
	int				NumSatMinVPLGNSS[MAX_GNSS];						//Number of satellites used per constellation in the epoch with minimum vertical protection level
	int				*NumConstUsed;									//Vector with number of constellations used in each epoch
	int				*NumConstNotUsed;								//Vector with number of constellations not used (and not manually unselected) in each epoch
	int				MinNumConstUsed;								//Minimum number of constellations used
	int				MaxNumConstUsed;								//Maximum number of constellations used
	int				MinNumConstNotUsed;								//Minimum number of constellations used not used (and not manually unselected)
	int				MaxNumConstNotUsed;								//Maximum number of constellations used not used (and not manually unselected)
	int				MinNumConstUsedListPos;							//Index number to epoch->constNotUsedCombinationText array for minimum GNSS used
	int				MaxNumConstUsedListPos;							//Index number to epoch->constNotUsedCombinationText array for maximum GNSS used
	int				MinNumConstNotUsedListPos;						//Index number to epoch->constNotUsedCombinationText array for minimum GNSS not used
	int				MaxNumConstNotUsedListPos;						//Index number to epoch->constNotUsedCombinationText array for maximum GNSS not used
	int				NumConstUsedPercentSamples;						//95th of number of constellations used
	int				NumConstUsed50PercentSamples;					//50th of number of constellations used
	int				NumConstNotUsedPercentSamples;					//95th of number of constellations not used
	int				NumConstNotUsed50PercentSamples;				//50th of number of constellations not used
	
	
	double			*NError;										//Vector with all North errors
	double			*EError;										//Vector with all East errors
	double			*HError;										//Vector with all horizontal errors
	double			*VError;										//Vector with all vertical (Up) errors
	double			*Error3D;										//Vector with all 3D errors
	double			*HDOP;											//Vector with all HDOP values
	double			*PDOP;											//Vector with all PDOP values
	double			*GDOP;											//Vector with all GDOP values
	double			*VDOP;											//Vector with all VDOP values
	double			*TDOP;											//Vector with all TDOP values
	double			MaxNError;										//Maximum North error
	double			MaxEError;										//Maximum East error
	double			MaxHError;										//Maximum horizontal error
	double			MaxVError;										//Maximum vertical error
	double			Max3DError;										//Maximum 3D error
	double			MaxHDOP;										//Maximum HDOP
	double			MaxPDOP;										//Maximum PDOP
	double			MaxGDOP;										//Maximum GDOP
	double			MaxVDOP;										//Maximum TDOP
	double			MaxTDOP;										//Maximum VDOP
	double			MinHDOP;										//Minimum HDOP
	double			MinPDOP;										//Minimum PDOP
	double			MinGDOP;										//Minimum GDOP
	double			MinVDOP;										//Minimum TDOP
	double			MinTDOP;										//Minimum VDOP
	double			NPEPercentileSamples;							//95th North error percentile of the samples
	double			EPEPercentileSamples;							//95th East error percentile of the samples
	double			HPEPercentileSamples;							//95th horizontal error percentile of the samples
	double			VPEPercentileSamples;							//95th vertical error percentile of the samples
	double			PE3DPercentileSamples;							//95th 3D error percentile of the samples
	double			HDOPPercentileSamples;							//95th HDOP of the samples
	double			PDOPPercentileSamples;							//95th PDOP of the samples
	double			GDOPPercentileSamples;							//95th GDOP of the samples
	double			TDOPPercentileSamples;							//95th TDOP of the samples
	double			VDOPPercentileSamples;							//95th VDOP of the samples

	double			MeanNumSatUsed;									//Mean number of satellites used
	double			MeanNumSatUsedGNSS[MAX_GNSS];					//Mean number of satellites used per constellation
	double			MeanNumSatNotUsed;								//Mean number of satellites not used
	double			MeanNumSatNotUsedGNSS[MAX_GNSS];				//Mean number of satellites not used per constellation
	double			MeanNumConstUsed;								//Mean number of constellations used
	double			MeanNumConstNotUsed;							//Mean number of constellations not used

	unsigned int	*constCombination;								//Hash of the constellation combinations
	unsigned int	*constNotUsedCombination;						//Hash of the not used constellation combinations
	unsigned int	*numEpochsconstCombination;						//Number of epochs where each constellation combination was used
	unsigned int	*numEpochsconstNotUsedCombination;				//Number of epochs where each not used constellation combination was used
	unsigned int	numconstCombUsed;								//Number of constellation combinations
	unsigned int	numconstCombNotUsed;							//Number of not used constellation combinations
	char			**constCombinationText;							//Constellation combination in text format
	char			**constNotUsedCombinationText;					//Not used constellation combination in text format

	int				numEpochsRefClock[MAX_GNSS];					//Number of epochs where each constellation was used as the reference clock
	
	TTime			StartSummaryEpoch;								//Timestamp of the first epoch used in the summary
	TTime			LastSummaryEpoch;								//Timestamp of the last epoch used in the summary
	TTime			StartSummaryPercentileEpoch;					//Timestamp of the first epoch used in the summary for computing percentiles
	TTime			LastSummaryPercentileEpoch;						//Timestamp of the last epoch used in the summary for computing percentiles

	TTime			MaxNerrorEpoch;									//Timestamp of the epoch with maximum North error
	TTime			MaxEerrorEpoch;									//Timestamp of the epoch with maximum East error
	TTime			MaxHerrorEpoch;									//Timestamp of the epoch with maximum horizontal error
	TTime			MaxVerrorEpoch;									//Timestamp of the epoch with maximum vertical error
	TTime			Max3DerrorEpoch;								//Timestamp of the epoch with maximum 3D error
	TTime			MaxHDOPEpoch;									//Timestamp of the epoch with maximum HDOP
	TTime			MaxPDOPEpoch;									//Timestamp of the epoch with maximum PDOP
	TTime			MaxGDOPEpoch;									//Timestamp of the epoch with maximum GDOP
	TTime			MaxVDOPEpoch;									//Timestamp of the epoch with maximum VDOP
	TTime			MaxTDOPEpoch;									//Timestamp of the epoch with maximum TDOP
	TTime			MaxSatUsedEpoch;								//Timestamp of the epoch with maximum number of satellites used
	TTime			MaxSatUsedEpochGNSS[MAX_GNSS];					//Timestamp of the epoch with maximum number of satellites used per constellation
	TTime			MaxSatNotUsedEpoch;								//Timestamp of the epoch with maximum number of satellites not used
	TTime			MaxSatNotUsedEpochGNSS[MAX_GNSS];				//Timestamp of the epoch with maximum number of satellites not used per constellation
	TTime			MaxGNSSUsedEpoch;								//Timestamp of the epoch with maximum number of constellations used
	TTime			MaxGNSSNotUsedEpoch;							//Timestamp of the epoch with maximum number of constellations not used

	TTime			MinHDOPEpoch;									//Timestamp of the epoch with minimum HDOP
	TTime			MinPDOPEpoch;									//Timestamp of the epoch with minimum PDOP
	TTime			MinGDOPEpoch;									//Timestamp of the epoch with minimum GDOP
	TTime			MinVDOPEpoch;									//Timestamp of the epoch with minimum VDOP
	TTime			MinTDOPEpoch;									//Timestamp of the epoch with minimum TDOP
	TTime			MinSatUsedEpoch;								//Timestamp of the epoch with minimum number of satellites used
	TTime			MinSatUsedEpochGNSS[MAX_GNSS];					//Timestamp of the epoch with minimum number of satellites used per constellation
	TTime			MinSatNotUsedEpoch;								//Timestamp of the epoch with minimum number of satellites not used
	TTime			MinSatNotUsedEpochGNSS[MAX_GNSS];				//Timestamp of the epoch with minimum number of satellites not used per constellation
	TTime			MinGNSSUsedEpoch;								//Timestamp of the epoch with minimum number of constellations used
	TTime			MinGNSSNotUsedEpoch;							//Timestamp of the epoch with minimum number of constellations not used
	
	TTime			DataGapSum;										//Timestamp of the epoch with biggest DataGap during summary
	TTime			DataGapTotal;									//Timestamp of the epoch with biggest DataGap in whole file
	
	TTime			BackwardTurningEpoch;							//Epoch where forward processing ended		

	TTime			FirstEpochSolution;								//First epoch with solution

	TTime			FirstEpochConvergedFormalErrHor;				//First epoch where the horizontal position formal error was below the threshold

	TTime			FirstEpochConvergedFormalErrVer;				//First epoch where the vertical position formal error was below the threshold

	TTime			FirstEpochConvergedFormalErr3D;					//First epoch where the 3D position formal error was below the threshold

	TTime			FirstEpochConvergedPosErrHor;					//First epoch where the horizontal position error was below the threshold

	TTime			FirstEpochConvergedPosErrVer;					//First epoch where the vertical position error was below the threshold

	TTime			FirstEpochConvergedPosErr3D;					//First epoch where the 3D position error was below the threshold

	TTime			FirstEpochConvergedPeriodFormalErrHor;			//First epoch where the horizontal position formal error was below the threshold and it lasted at least options->minTimeConvergedFormalErr continuous seconds 

	TTime			FirstEpochConvergedPeriodFormalErrVer;			//First epoch where the vertical position formal error was below the threshold and it lasted at least options->minTimeConvergedFormalErr continuous seconds 

	TTime			FirstEpochConvergedPeriodFormalErr3D;			//First epoch where the 3D position formal error was below the threshold and it lasted at least options->minTimeConvergedFormalErr continuous seconds 

	TTime			FirstEpochConvergedPeriodPosErrHor;				//First epoch where the horizontal position error was below the threshold and it lasted at least options->minTimeConvergedPosErr continuous seconds 

	TTime			FirstEpochConvergedPeriodPosErrVer;				//First epoch where the vertical position error was below the threshold and it lasted at least options->minTimeConvergedPosErr continuous seconds 

	TTime			FirstEpochConvergedPeriodPosErr3D;				//First epoch where the 3D position error was below the threshold and it lasted at least options->minTimeConvergedPosErr continuous seconds 

	//Variables for EPOCHSAT print
	int			maxNumMeasAllGNSSIndexed;	//Maximum number of measurements indexed for all constellations (in all epochs)
	int			**numSatsMeasUsed;			//Number of satellites used in solution and has all measurements selected (sorted by measurement and constellation)
	int			**numSatsMeasUnused;		//Number of satellites unused in solution and has all measurements selected (sorted by measurement and constellation)
	int			***PRNMeasUsed;				//PRN of each satellite used (sorted by measurement and constellation)	
	int			***PRNMeasUnused;			//PRN of each satellite unused (sorted by measurement and constellation)
	

	///////Hardcoded data (See function 'initEpoch' in dataHandling.c file for their values)
	//First epoch with S/A turned off
	TTime			FirstEpochSAoff;

	//Epochs with GPS AS off (Anti-Spoofing off)
	TTime			EpochsWithoutAS[MAX_NO_AS_PERIODS][2];

	//UTC leap seconds (Epochs were leap seconds were added)
	TTime			LeapSecondsTimeList[MAX_LEAP_SECONDS_SIZE];
	int				LeapSecondsNumList[MAX_LEAP_SECONDS_SIZE];

	//Time references (Start time of constellations)
	TTime			GNSSTimeReferences[MAX_GNSS];

} TEpoch;

// SP3 orbits block
typedef struct {
	TTime		t;
	double		x[3];
	double		v[3];
	double		xsigma[3];
	char        orbitflags[3];
	int			validSample;
} TSP3orbitblock;

// SP3 clocks block
typedef struct {
	TTime		t;
	double		clock;
	double		clockrate;
	double		clockdriftrate;
	double		clocksigma;
	char        clockflags[3];
	int			validSample;
} TSP3clockblock;

// Satellite orbits structure
typedef struct {
	TTime			startTime;
	TTime			endTime;
	TTime			startTimeConcat;
	TTime			endTimeConcat;
	int				numSatellites;
	int				numSatellitesRead;
	int				numRecords;
	int				velocityAvailable;
	int				index[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	TSP3orbitblock	**block;		// Satellite (from index) & Block
	TSP3orbitblock	*Concatblock[MAX_GNSS*MAX_SATELLITES_PER_GNSS];	// Satellite (from index) & Block. These blocks are concatenated from previous and next day
	int				numblocsConcat[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int				numblocsValidConcat[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int				hasSigmaPerEpoch;
	double			*accuracy;	// Satellite (from index)
	double			interval;
	double			intervalConcat;
} TSP3orbits;

// Satellite orbits structure
typedef struct {
	TTime			startTime;
	TTime			endTime;
	TTime			startTimeConcat;
	TTime			endTimeConcat;
	int				numSatellites;
	int				numSatellitesRead;
	int				numRecords;
	int				index[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	TSP3clockblock	**block;		// Satellite (from index) & Block
	TSP3clockblock	*Concatblock[MAX_GNSS*MAX_SATELLITES_PER_GNSS];	// Satellite (from index) & Block. These blocks are concatenated from previous and next day
	int				numblocsConcat[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int				numblocsValidConcat[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int				hasSigmaPerEpoch;
	double			interval;
	double			intervalConcat;
} TSP3clocks;

// Satellite orbits and clocks SP3 structure
typedef struct {
	TSP3orbits	orbits;
	TSP3clocks	clocks;
} TSP3products;

// Time System Correction block (for Rinex Nav v3)
typedef struct {
	double          acoff[2];               //a0, a1 coefficients pf 1-deg polynomial
	int             timeref;                //Reference time for polynomial (Seconds in GPS/GAL week)
	int             weekref;                //Reference week number (GPS/GAL week)  
} TTimeSystemCorrection;

// Broadcast block
typedef struct {
	TTime			Ttoc,TtocUTC;							// Ttoc in GPS time, TtocUTC in UTC
	TTime			Ttoe,TtoeUTC;							// Ttoe in GPS time, TtoeUTC in UTC
	TTime			TtransTime;								// TtransTime in GPS time
	TTime			TframeTime;								// GLONASS frame time (in GPS time)
	int				BRDCtype;								// Broadcast block type
	enum GNSSystem	GNSS;
	int				PRN;
	double			clockbias, clockdrift, clockdriftrate;	// First block row
	int				IODE;									// Second block row
	int				IODEGLONASS;							// Fake IODE computed for GLONASS for fast package selection
	double			crs, deltan, M0;
	double			cuc, e, cus, sqrta;						// Third block row
	double			toe, cic, OMEGA, cis;					// Forth block row
	double			i0, crc, omega, OMEGADOT;				// Fifth block row
	double			IDOT;									// Sixth block row
	int				codesOnL2, GPSweek, L2Pdataflag;
	double			SVaccuracy;								// Seventh block row (5th for GLONASS since RINEX 3.05)
	int				SVhealth;	
	double			TGD;
	int				IODC;	
	double			transTime;								// Eight block row
	double			fitInterval;
	enum BRDCHealth	GlobalHealth;							// Health for all frequencies (the worst health status is the dominant)
	enum BRDCHealth	FreqHealth[MAX_FREQUENCIES_PER_GNSS];	// Health by each frequency

	//GPS/QZSS CNAV data
	double			aDot,nDot;
	double			top;
	double			ISCL1CA,ISCL2C,ISCL5I5,ISCL5Q5;
	double			ISCL1CP,ISCL1CD;
	int				URANED0,URANED1,URANED2,URAIndexED;
	TTime			Ttop;									//Time of ephemeris prediction
	

	//Galileo data
	double			SISASignal;								// Galileo Seventh block row
	double			BGDE5a,BGDE5b;
	double			transTimeGAL;							// Galileo Eigth block row
	int				dataSources,GALweek;					// Galileo Sixth block row

	//GLONASS data 
	double			satPos[3];								// Satellite postion X,Y,Z (in m)
	double			satVel[3];								// Satellite velocity X,Y,Z (in m/s)
	double			satAcc[3];								// Satellite acceleration X,Y,Z (in m/s^2)
	int				freqnumber;
	int				ageofoperation;	
	int				GLOfifthLineAvail;						// To indicate if the fifth line of data available (since RINEX 3.05)
	int				GLOstatusflags;							// Status flags provided since RINEX 3.05
	int				GLOextraHealthFlags;					// Additional health flags (provided since RINEX 3.05)
	double			URAI;									// GLONASS URAI for M/K satellites only (rovided since RINEX 3.05)

	//GEO data
	int				IODNGEO;
	int				URAGEO;
	int				IODG;									// IODG is only set if navigation data is from SBAS DFMC MT39/40 message
	int				SBASDFMCdatatype;						// SBASDFMCdatatype => 0 (NOSBASDFMCGEODATA) if not from SBAS DFMC messages,
															//					=> 1 (SBASDFMCGEONAVIGATIONDATA) if from SBAS DFMC MT 39/40 (navigation message)	
															//					=> 2 (SBASDFMCGEOALMANACDATA) if from SBAS DFMC MT 47 (almanac message)	

	//BeiDou data
	int				BDSweek;								// BeiDou Sixth block row
	int				AODE;									// Age of Data Ephemeris
	int				AODC;									// Age of Data Clock
	double			TGD26;									// TGD for B1_2-6
	double			TGD76;									// TGD for B2b-6
	double			TGD56;									// TGD for B2a-6
	double			TGD16;									// TGD for B1-6
	double			ISCB1Cd,ISCB2ad;

	//IRNSS data
	double			IRNURA;

} TBRDCblock;

// Satellite orbits and clocks broadcast structure
typedef struct {
	//Rinex Nav v2
	double					ionA[4];			//GPS ionospheric correction
	double					ionB[4];			//GPS ionospheric correction
	//Rinex Nav v3
	double					ai[4];				//Galileo ionospheric correction
	double					bdsA[4];			//BeiDou ionospheric correction
	double 					bdsB[4];			//BeiDou ionospheric correction	
	double					qzsA[4];			//QZSS ionospheric correction
	double 					qzsB[4];			//QZSS ionospheric correction	
	double					irnA[4];			//IRNSS ionospheric correction
	double 					irnB[4];			//IRNSS ionospheric correction	
	TTimeSystemCorrection 	timeSysCorr[NUMTIMESYSTEMCORRECTIONTYPES];	//12 positions, one for each correction type	
	int						AT_LSpast;			//Number of leap seconds for previous day read from RINEX Nav header
	int						AT_LSFpast;			//Future or past leap seconds for previous day
	int						WN_LSFpast;			//Respective week number for previous day
	int						AT_LS;				//Number of leap seconds read from RINEX Nav header
	int						AT_LSF;				//Future or past leap seconds
	int						WN_LSF;				//Respective week number
	int						leapSecondsPast;	//Number of leap seconds for previous day used (either read from header or obtained from hardcoded value)
	int						leapSeconds;		//Number of leap seconds for previous day used (either read from header or obtained from hardcoded value)
	int						DN;					//Respective day number
	double					GLOintStep;			//GLONASS integration time (default 30 sec)
	
	//Common blocks
	TBRDCblock				***blockPast;			// Satellite & Block & message type from previous day
	TBRDCblock				***block;				// Satellite & Block & message type
	TBRDCblock				****blockPastPointer;	// Satellite & Block & message type from previous day (array of pointers only)
	TBRDCblock				****blockPointer;		// Satellite & Block & message type (array of pointers only)
	TBRDCblock				*****blockPastIOD;		// Satellite & Block & message type & IOD from previous day (array of pointers only)
	TBRDCblock				*****blockIOD;			// Satellite & Block & message type & IOD (array of pointers only)
	int						**numblocks;			// Per satellite and message type
	int						**numblocksPast;		// Per satellite and message type (from previous day)
	int						***numblocksIOD;		// Per satellite, message type and IOD
	int						***numblocksPastIOD;	// Per satellite, message type and IOD (from previous day)
	int						numsats;
	int						numsatsPast;
	int						index[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int						indexPast[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int						LeapSecondsAvailPast;
	int						LeapSecondsAvail;
	int						AvailBRDCTypePast[MAX_GNSS][MAX_BRDC_TYPES]; 	// Flag to indicate which BRDC are available in the navigation data from previous day
	int						AvailBRDCType[MAX_GNSS][MAX_BRDC_TYPES]; 		// Flag to indicate which BRDC are available in the navigation data

	int						NavDataPosition;	// Flag to indicate from where is the data read from. To be used as first index in options->BRDCAvailSelOrder 
												// NavDataPosition = ORBNAVPOS 		=> Data from orbit and clock navigation file
												// NavDataPosition = TGDNAVPOS 		=> Data from TGD source (different from orbit and clock navigation file)
												// NavDataPosition = HEALTHNAVPOS	=> Data from Health Nav source (different from orbit and TGD)

	//GLONASS saved data (last position computed, to be used for next iteration)
	int						lastPosIODE[MAX_SAT_GLO+1];		//Last IODE (fake IODE, its computation is done in the final part of readRinexNav function) used in GLONASS for each PRN
	TTime					lastEpoch[MAX_SAT_GLO+1];		//Last epoch used in GLONASS interpolation for each PRN (in UTC time)
	double					lastPosXYZ[MAX_SAT_GLO+1][3];	//Last coordinates  computed (in fixed step) in GLONASS interpolation for each PRN (in metres of PZ-90)
	double					lastVelXYZ[MAX_SAT_GLO+1][3];	//Last velocity     computed (in fixed step) in GLONASS interpolation for each PRN (in metres of PZ-90)
	double					lastAccXYZ[MAX_SAT_GLO+1][3];	//Last acceleration computed (in fixed step) in GLONASS interpolation for each PRN (in metres of PZ-90)
	double					lastSid[MAX_SAT_GLO+1];			//Last sid computed (in fixed step) in GLONASS interpolation for each PRN (in radians)

	///////Hardcoded data (See function 'initBRDCproducts' in dataHandling.c file for their values)
	//Note that leap seconds are repeated, as they are need for broadcast products function were the 'epoch' struct is not available
	//UTC leap seconds (Epochs were leap seconds were added)
	TTime			LeapSecondsTimeList[MAX_LEAP_SECONDS_SIZE];
	int				LeapSecondsNumList[MAX_LEAP_SECONDS_SIZE];

} TBRDCproducts;

// Satellite orbits and clocks generic structure
typedef struct {
	enum ProductsType	type;
	TSP3products		*SP3;
	TBRDCproducts		*BRDC;
} TGNSSproducts;

// Satellite DCB block
typedef struct {
	TTime					startTime;
	TTime					endTime;
	int						available[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	double 					dcb[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	enum MeasurementType	measFrom;
	enum MeasurementType	measTo;
} TDCBblock;

// Satellite DCBs
typedef struct {
	TDCBblock	block[MAX_DCB_FILE_SOURCES];
	int		n;
} TDCBdata;

// Ionex DCB
typedef struct {
	int			DCBavailable;
	double		DCB[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	double		DCBRMS[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
} TIonexDCB;

// FPPP DCB structure
typedef struct {
	int			DCBavailable;
	//PRN  FRAC_1 FRAC_W IFB(P1-P2)
	double		frac1[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	double 		fracw[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	double		IFB[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
} TFPPPDCB;

// SINEX-BIAS DCB structure
typedef struct {

	TTime		*EpochStart;	//Start epoch for each block read
	TTime		*EpochEnd;		//End epoch for each block read
	double		*DCBVal; 		//OSB or DSB (in metres) for each block read
	double		*DCBSigma; 		//Sigma (in metres) for each block read

	int			numTimeBlocks;	//Number of blocks with same Bias type and measurements but different epoch

} TSINEXBiasBlock;

typedef struct {

	TSINEXBiasBlock ***SNXBiasBlockOSB;	//Block for each GNSS and PRN and type of OSB
	TSINEXBiasBlock ***SNXBiasBlockDSB;	//Block for each GNSS and PRN and type of DSB

	int	numMeasBlocksOSB[MAX_GNSS];	//Number of OSB blocks saved per constellation
	int	numMeasBlocksDSB[MAX_GNSS];	//Number of DSB blocks saved per constellation

	int	**OSBindex;		//From GNSS, PRN, MEAS1 to position for OSB
	int ***DSBindex;	//From GNSS, PRN, MEAS1, MEAS2 to position for DSB

} TSINEXBiasData;

// TGD generic structure
typedef struct {
	enum GPSP1C1DCBModel	GPSp1c1DCBModel;
	enum GenericDCBModel	GPSp1p2DCBModel;
	enum GenericDCBModel	GPSISCl1caDCBModel;
	enum GenericDCBModel	GPSISCl1cpDCBModel;
	enum GenericDCBModel	GPSISCl1cdDCBModel;
	enum GenericDCBModel	GPSISCl2cDCBModel;
	enum GenericDCBModel	GPSISCl5i5DCBModel;
	enum GenericDCBModel	GPSISCl5q5DCBModel;
	enum GenericDCBModel	GALe1e5aDCBModel;
	enum GenericDCBModel	GALe1e5bDCBModel;
	enum GenericDCBModel	GLOp1p2DCBModel;
	enum GenericDCBModel	BDSb1b6DCBModel;
	enum GenericDCBModel	BDSb2b6DCBModel;
	enum GenericDCBModel	BDSb5b6DCBModel;
	enum GenericDCBModel	BDSb7b6DCBModel;
	enum GenericDCBModel	BDSSP3DCBModel;
	enum GenericDCBModel	BDSISCb1cdDCBModel;
	enum GenericDCBModel	BDSISCb2adDCBModel;
	enum GenericDCBModel	QZSc1cDCBModel;
	enum GenericDCBModel	QZSISCl1cpDCBModel;
	enum GenericDCBModel	QZSISCl1cdDCBModel;
	enum GenericDCBModel	QZSISCl2cDCBModel;
	enum GenericDCBModel	QZSISCl5i5DCBModel;
	enum GenericDCBModel	QZSISCl5q5DCBModel;
	enum GenericDCBModel	IRNc9c5DCBModel;
	enum OSBDCBModel   		OSBdcbModel;
	enum DSBDCBModel		DSBdcbModel;
	enum GenericDCBModel	DualFreqDCBModel[MAX_GNSS];
	enum GenericDCBModel	FPPPDCBModel;

	TBRDCproducts			*BRDC;
	TDCBdata				*DCB;
	TIonexDCB				ionexDCB;	
	TFPPPDCB				fpppDCB;
	TSINEXBiasData			SNXBias;
} TTGDdata;

// Receiver data about the code biases management
typedef struct {
	char 				name[MAX_RECEIVER_NAME];
	enum ReceiverType	type;
} TReceiverData;

// Receiver list structure
typedef struct {
	TReceiverData	*rec;
	int				n;
} TReceiverList;

// Station position
typedef struct {
	double		pos[3];
	char		name[5];
} TStation;

// Station list structure
typedef struct {
	TStation	*station;
	int			n;
} TStationList;

//Ionex Station / PRN / BIAS structure
typedef struct {
	char		stationInitials [5];
	char		stationcode [11];
	double		stationBias;
	double		stationRMS;
} TIonexStation;

// Ionospheric map structure
typedef struct {
	double		hgt1;	//Stored in Km
	double		hgt2;	//Stored in Km
	double		dhgt;	//Stored in Km
	int			nhgt;
	
	double		lat1;  //Stored in degrees
	double		lat2;  //Stored in degrees
	double		dlat;  //Stored in degrees
	int			nlat;
	
	double		lon1;  //Stored in degrees
	double		lon2;  //Stored in degrees
	double		dlon;  //Stored in degrees
	int			nlon;
	
	double		*TEC;   // Stored in TECU
	double		*RMS;	// Stored in TECU^2
	double		*HGT;	// Stored in Km
	TTime		t;
} TIonoMap;

// IONEX structure
typedef struct {
	int							numMaps;
	int							RMSavailable;
	int							HGTavailable;
	TIonoMap					*map;
	TTime						startTime;
	TTime						endTime;
	int							interval;
	int							exponent;
	int							satNumber;
	int							stationNumber;
	int							mapDimension;
	int 						numStationData;
	double						conversionFactor;
	double						elevationCutoff;
	double						baseRadius;
	TIonexDCB					ionexDCB;
	enum MappingFunctionTypes 	mappingFunctionType;
	char						observablesUsed[61];
	TIonexStation				*ionexStation;
} TIONEX;

// FPPP map structure
typedef struct {
	double		hgt1;   //Stored in Km
	double		hgt2;   //Stored in Km
	double		dhgt;   //Stored in Km (difference between both maps)

	double		lat1;	//Stored in degrees
	double		lat2;	//Stored in degrees
	double		dlat;	//Stored in degrees
	double		nlat;

	double		lt1;	//Stored in degrees
	double		lt2;	//Stored in degrees
	double		dlt;	//Stored in degrees
	double		nlt;

	double		*TEC;   // Stored in TECU
	double		*SIGMA; // Stored in TECU^2
	TTime		t;
} TFPPPMap;


// FPPPIONEX structure
typedef struct {
	int							numMaps;
	int							numMapsAlloc;
	TFPPPMap					*map;
	TTime						startTime;
	TTime						endTime;
	int							interval;
	double						baseRadius; 
	enum MappingFunctionTypes 	mappingFunctionType;
	TFPPPDCB					fpppDCB;
} TFPPPIONEX;

// PiercePoint structure
typedef struct {
	//Coordinates in X,Y,Z
	double 			x;
	double			y;
	double 			z;
	//Coordinates in espheric phi,lambda,h
	double 			fi;			//Stored in degrees
	double 			longitude;	//Stored in degrees
	double 			elevation;	//Stored in degrees
	//Localtime position for FPPP maps
	double 			localtime;	//Stored in degrees
	//Mapping function for current height
	double 			mappingFunction;
} TPiercePoint;

//TROPOESA structure
typedef struct {
	int 			lat_pix_positions;	//Number of elements for latitude plus 1 (the beginning is the same as the end)
	int 			lon_pix_positions;	//Number of elements for longitude plus 1 (the beginning is the same as the end)
	double			delta_lat_pix;		//Latitude increase in each position
	double 			delta_lon_pix;		//Longitude increase in each position
	double 			lat_pix_init;		//Lowest latitude position in map
	double 			lat_pix_end;		//Highest latitude position in map
	double 			lon_pix_init;		//Lowest longitude position in map
	double 			lon_pix_end;		//Highest longitude position in map
	double 			am_a_size[3];		//Size of each dimension for am_a
	double 			es_a_size[3];		//Size of each dimension for es_a
	double 			ld_a_size[3];		//Size of each dimension for ld_a
	double 			ps_a_size[3];		//Size of each dimension for ps_a
	double 			tm_a_size[3];		//Size of each dimension for tm_a
	double 			es_b_size[4];		//Size of each dimension for es_b
	double 			ld_b_size[4];		//Size of each dimension for ld_b
	double 			tm_b_size[4];		//Size of each dimension for tm_b

	double 			**hgt_pix_values;	//Height values in grid
	double 			**lnd_values;		//Land values in grid
	double 			***am_a_values;		//am_a values in grid
	double 			***es_a_values;		//es_a values in grid
	double 			***ld_a_values;		//ld_a values in grid
	double 			***ps_a_values;		//ps_a values in grid
	double 			***tm_a_values;		//tm_a values in grid
	double 			****es_b_values;	//es_b values in grid
	double 			****ld_b_values;	//ld_b values in grid
	double 			****tm_b_values;	//tm_b values in grid
} TTROPOGal;

//TROPOESAParameters Structure
typedef struct {
	//Final parameters
	double 			gm[4];			//Gravity acceleration in map points [m/s^2]
	double 			ph[4];			//Water Vapour Pressure in map points [hPa]
	double 			eh[4];			//Water Vapour Pressure in map points [hPa]
	double 			tmh[4];			//Average temperature of moist air [K]
	double 			zwd_map[4];		//Zenith wet delay
	double 			zhd_map[4];		//Zenith hydrostatic delay
	double 			ztd_map[4];		//Zenith wet delay + zenith hydrostatic delay

	//Specific time format variables
	double 			DoY;			//Day of the year [0..364.25] UT
	double 			hour_minute;	//Hour of the day [0..23.59] [UTC]

	//Variables for data calculation
	double 			g0[4];			//Acceleration in map points
	double 			ps[4];			//Air pressure in map points
	double 			tm[4];			//Mean temperature in map points  
	double 			am[4];			//Lapse rate of mean temperature in map points
	double 			es[4];			//Vapou pressure decresase factor in map points
	double 			ld[4];			//Values of harmonic model for seasonal fluctuations in map points
	double 			*a;				//Vector for retrieving data from ps_a,tm_a,am_a,es_a,ld_a matrix
	double 			*b;				//Vector for retrieving data from tm_b,es_b,ld_b
	//Auxiliary variable
	double 			validpoint[4];	//1->Valid map point 0-> Not a valid point
} TTROPOGalParameters;

// Individual element in constellation structure
typedef struct {
	TTime				tLaunch;
	TTime				tDecommissioned;
	int					PRN;
	int					SVN;
	enum SatelliteBlock	block;
	enum GNSSystem		GNSS;
	//double			phaseCenter[3];
	double				PCO[MAX_FREQUENCIES_PER_GNSS][3];	// Antenna Phase Center Offset [PCO]  (North - East - Up)

	double				azi1;  			//Stored in degrees
	double				azi2;  			//Stored in degrees
	double				dazi;  			//Stored in degrees
	int   				numazi;

	double				zen1;  			//Stored in degrees
	double				zen2;  			//Stored in degrees
	double				dzen; 			//Stored in degrees
	int   				nzen;

	double				***noazi;		//Non-azimuth-dependent pattern values (dependent on constellation and frequency)
	double				****azi;		//Azimuth-dependent pattern values (dependent on constellation,frequency and azimuth)
} TConstellationElement;

//Data for Galileo special APC corrections
typedef struct {

	int		svn;
	double	Corr[3];	//Stored in metres (N - E - U)

} TGalCorrections;

// Data on unknowns for the filter
typedef struct {
	int					par2unk[MAX_PAR];
	int					GNSS2ISCBunk[MAX_GNSS];	//For getting the position of the inter-system clock bias for each constellation (for GPS always refers to receiver clock)
	int 				nunk;
	int 				nunkvector;
	enum FilterUnknown	pos2unktype[MAX_UNK];	//To save to what unknown type corresponds each position
	double 				qnoise[MAX_UNK];
	double 				phi[MAX_UNK];
} TUnkinfo;

// Filter solution structure
typedef struct {
	double		x[MAX_UNK];
	double		parameters[MAX_UNK];
	double		correlations[MAX_VECTOR_UNK];
	double		dop,GDOP,PDOP,TDOP,HDOP,VDOP,HPL,VPL;
	int			prevNumSatellites;
	int			satDCBlist[MAX_FILTER_SATELLITE_DCB];
	int			recDCBlist[MAX_FILTER_RECEIVER_DCB];
	int			totalNumSatDCBEpoch;
	int			totalNumRecDCBEpoch;
} TFilterSolution;

// GNSS Constellation data
typedef struct {
	TConstellationElement	*sat[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	TConstellationElement	*satLastUsed[MAX_GNSS][MAX_SATELLITES_PER_GNSS]; //This pointer saves the pointer to the last block used per satellite
	int						numSatellites[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
} TConstellation;

// List of antennas
typedef struct {
	TAntenna	*ant;
	int			numAnt;
} TAntennaList;

// Statistics structure
typedef struct {
	double		mean;
	double		mean2;
	int 		n;
} TStat;

// SBAS block
typedef struct {
	//Fields only on RINEXB
	int		frequency;					// 1 => Frequency L1    5 => Frequency L5
	int		frequencyPos;				// Position in array 0 => Frequency L1	1 => Frequency L5
	int		halfdatalength;				//Half length of data message or number of byte pairs
	int		datalength;					//Length of data message (in bytes)
	int		receiverindex;				//Receiver index given in the RINEX file (0 is an unclassified receiver)
	char	bandflag;					//Band flag identifier
	char	sourceidentifier[4];		//Transmission system identifier (SBA for a SBAS satellite, SNT for SiSNET, CDG for CDGPS)

	//Common fields
	int		messagetype;				
	int		dontuse;			//Flag that will activate when a type 0 message is received
	int		problems;			//Flag that will activate when a type 0 message is received and the message is filled with 0
	int		msg0type;			//Message type embedded in type 0 message (for SBAS DFMC)
	int		PRN;				//PRN number
	TTime	t;					//In time of applicability (reception of last bit), not time of reception of first bit
	int		messageslost;		//Number of messages lost (detected by the preamble) from the previous message received

	int		IODF[4];			//IODF (Issue Of Data Fast correction) Identifies the current fast corrections
	int		IODP;				//IODP (Issue Of Data PRN mask) Identifies the current PRN mask
	int		numsatellites;		//Number of satellites monitored

	//PRN Mask assignments (used for SBAS 1F and SBAS DFMC)
	int				PRNactive[MAX_GNSS][MAX_SBAS_PRN];		//Given a PRN number of a GNSS system, check if that satellite has corrections or not
	int				pos2PRN[92];			//Given one position in the list of 51/92 satellites with corrections, return its PRN (in the same order as messages type 2-5,6,7,25,25,28/32,34,35,36)
	enum GNSSystem	pos2GNSS[92];			//Given one position in the list of 51/92 satellites with corrections, return its GNSS system (in the same order as messages type 2-5,6,7,25,25,28/32,34,35,36)
	int				PRN2pos[MAX_GNSS][MAX_SBAS_PRN];			//Given a GNSS and a PRN, return its position in the mask (in the same order as messages type 2-5,6,7,25,25,28)
	int				Slot2pos[215];			//Given one slot in the mask, return the position in mask

	//Fast corrections data
	double	PRC[13];				//PRC (Pseudo Range Correction). These are fast corrections applied to the pseudorange (0.125m resolution,stored in meters)
	int		UDREI[13];				//UDREI (User Differential Range Error Indicator) Indicates accuracy of combined fast and long corrections (except ionosphere)
	double	UDRE[13];				//UDRE (User Differential Range Error) Accuracy value of combined fast and long corrections (except ionosphere) (in meters)
	double	UDREsigma[13];			//UDRE (User Differential Range Error) Accuracy variance of combined fast and long corrections (except ionosphere) (in meters^2)

	//Fast corrections degradation data
	int		tlat;								//System latency (in seconds). Only in message type 7
	int		aiind[51];								//Fast Correction Degradation Indicator. Only in message type 7
	double	aifactor[51];							//Fast Correction Degradation Factor. (in meters/seconds^2)
	int		timeoutintervalnonprecise[51];			//User Time-Out Interval for fast corrections (seconds). En Route through Nonprecision approach
	int		timeoutintervalprecise[51];			//User Time-Out Interval for fast corrections (seconds). Precision approach mode
	int		fastcorrupdateinterval[51];			//Maximum fast correction update interval (seconds)
	
	//Integrity information
	int		UDREIacu[51];							//UDREI (User Differential Range Error Indicator) Indicates the accuracy of fast and long-term error corrections factor
	double	UDREacu[51];							//UDRE (User Differential Range Error) Accuracy of fast and long-term error corrections value
	double	UDREacusigma[51];						//UDRE (User Differential Range Error) Accuracy variance of combined fast and long corrections (except ionosphere) (in meters^2)

	//Degradation factors
	double	degradationfactors[16];				//Degradation factors only in message type 10. It consists of 16 factors (maybe in the future more are added)

	//Long term satellite error corrections
	double	longtermsaterrcorrections[4][15];		//Long term satellite error correction. Only for messages type 25 and type 24
	int		numlongtermsaterrcorrections;		//Number of satellites with corrections in the current messages. Only for messages type 25 and type 24

	//Mixed fast corrections/long term satellite error corrections
	int		BlockID;							//Indicates if type 24 message fast corrections contains data from type 2, 3, 4 or 5

	//GEO Navigation message
	double	geonavigationmessage[17];				//GEO Navigation Message data from message type 9

	//GEO Almanacs message
	double	geoalmanacsmessage[3][12];			//GEO Almanacs Message from message type 17
	int		numgeoalmanacs;						//Number of almanacs given in the current message

	//Service message
	double	servicemessage[9];					//Service message parameters from message type 27
	int		regioncoordinates[5][12];				//Contains the coordinates for all the regions given in the service message
	int		numregioncoordinates;				//Number of region coordinates in the service message

	//Network Time/UTC Parameters
	double	networktimemessage[13];				//Network time/UTC Parameters from message type 12

	//Clock-Ephemeris Covariance Matrix
	double	clockephemeriscovariance[2][14];			//Clock-Ephemeris Covariance Matrix from message type 28
	int		numclockephemeriscovariance;		//Number of satellite with Clock-Ephemeris Covariance Matrix in message type 28 (1 or 2)

	//IGP Mask Message
	int		igpmaskmessage[204];					//IGP (Ionospheric Grid Points) Mask from message type 18

	//Ionospheric delay parameters
	double	ionodelayparameters[15][7];				//Ionospheric delay parameters from message type 26

	//Constellations monitored
	int constMonitored[MAX_GNSS];				//Constellation monitored after decoding MT1 or MT31

	////SBAS DFMC messages
	int		GPSfrequenciesUsed;					//Flag to indicate which frequencies in SBAS DFMC are used for GPS (L1/L5 or L1/L2)
	int		IODM;								//IODM (Issue of Data Mask), identifies current PRN mask
	int		DFRECI[92];							//DFRECI (Dual Frequency Residual Error Control Indicator) from message type 34
	int		DFREI[53];								//DFRECI (Dual Frequency Residual Error Indicator) from message type 34, 35 and 36

	int		satSlotNumber;						//Satellite slot number in PRN mask
	int		IODNSat;							//IODN for non-SBAS satellites in message type 32
	int		DFREISat;							//DFREI in message type 32
	int		RcorrMultiplier;					//Rcorr multiplier in message type 32

	double	covariancematrixdata[14];				//Covariance matrix data in message type 32
	double	orbitclockcorrection[15];				//Orbit and clock correction in message type 32

	double	commonOBAD[5];						//Common OBAD parameters in message type 37
	double	OBAD[MAX_GNSS][3];								//OBAD parameters per constellation in message type 37
	double	DFREITable[15];						//DFREI table values in message type 37

	double	geoalmanacsDFMC[2][12];					//GEO Almanacs Message from message type 47
	int		numgeoalmanacsDFMC;					//Number of almanacs given in the message type 47

	double	sbasepehemeris1[11];					//GEO Navigation message (part 1) in message type 39
	double	sbasepehemeris2[9];					//GEO Navigation message (part 2) in message type 40

	double	GNSSTimeOffsetsCommon[9];				//GNSS time offsets common parameters in message type 42 (old format)
	double	GNSSTimeOffsetsConst[MAX_GNSS][2];				//GNSS time offsets constellation based parameters in message type 42 (old format)

} TSBASblock;

// SBAS block reduced for buffering iono only
typedef struct {
	TTime	t;					//In time of applicability (reception of last bit), not time of reception of first bit
	//Ionospheric delay parameters
	double	ionodelayparameters[15][7];				//Ionospheric delay parameters from message type 26
} TSBASblockIono;


// SBAS structure
typedef struct {
	//Time-outs values
	int		timeoutmessages[NUMPOSFREQSBASMSG][2][64];		//Time-out per frequency for non precision approach (position 0) and precision approach (position 1) per message (seconds)
	int		msgupdateinterval[NUMPOSFREQSBASMSG][64];		//Maximum update interval per frequency for message types (seconds)
	int		oldmaskdiscarded[NUMPOSFREQSBASMSG][64];		//Variable to check if data from old masks have been discarded if the old mask has timed-out (per frequency)

	//Last messages received
	TTime	lastfastcorrections[5][MAXSBASFASTCORR][51];	//Time since last fast corrections data received, by PRN mask
	TTime	lastintegrityinfo[51];							//Time since last integrity information data received, by PRN mask
	TTime	lastfastdegfactor[5][51];						//Time since last fast corrections degradation factor data received, by PRN mask
	TTime	lastlongtermdata[5][51];						//Time since last long term satellite error correction data received, by IODP and PRN mask
	TTime	prevlastlongtermdata[5][51];					//Time since previous last long term satellite error correction data received, by IODP and PRN mask
	TTime	lastcovmatrix[5][51];							//Time since last clock-ephemeris convariance matrix data received, by IODP and PRN mask
	TTime	lastmsgreceived[NUMPOSFREQSBASMSG][64];			//Time since last message received per frequency (ordered by frequency and message type) and that do not depend on PRN number (except ionosphere delay)
	TTime	alarmtime[NUMPOSFREQSBASMSG];					//Time of the last type 0 message per frequency (used only for priting SBASUNSEL message)
	TTime	firstmessage[NUMPOSFREQSBASMSG];				//Time of the first message received per frequency (from start of file or after a reset from a type 0 message)

	//Previous messages received
	TTime		oldlastintegrityinfo[51];
	TTime		oldlastmsgreceived[NUMPOSFREQSBASMSG][64];

	//Basic info
	int		PRN;							//PRN number. -1 for messages from more than one PRN
	int		GEOPRN2pos[MAX_SBAS_PRN];		//For a given GEO PRN, get the position of the TSBASdata struct vector its data is being stored
	int		failedmessages[NUMPOSFREQSBASMSG][MAX_SBAS_PRN];	//For a given frequency and GEO PRN (position 0 is for all PRN), save the number of messages with error at decoding since the last message correctly decoded in a per frequency basis
	int		missed4msg[NUMPOSFREQSBASMSG][MAX_SBAS_PRN];		//For a given frequency and GEO PRN (position 0 is for all PRN), this is a flag to indicate if 4 or more consecutive messages are lost (not received) in a per frequency basis
	int		numreceivers;					//Number of receivers (given by the number of "REC INDEX/TYPE/VERS" lines). Only in RINEXB file
	int		numSBASsatellites;				//Number of SBAS satellites

	//Alarm message
	int		dontuse[NUMPOSFREQSBASMSG];						//Flag that will activate when a type 0 message is received (per freqeuncy)
	int		problems[NUMPOSFREQSBASMSG];					//Flag that will activate when a type 0 message is received and the message is filled with 0 (per freqeuncy)
	int		cleared[NUMPOSFREQSBASMSG];						//Flag to indicate if the data from a GEO PRN has been cleared (after receiving a type 2 message)
	int		alarmGEOPRN[NUMPOSFREQSBASMSG][MAX_SBAS_PRN];	//List of GEO PRN from which we have received an alarm message
	int		alarmTimeRemaining[NUMPOSFREQSBASMSG];			//Time remaining to be able to use the data from each GEO with alarm from which we received the alarm
	int		alarmGEOindex[NUMPOSFREQSBASMSG][MAX_SBAS_PRN];	//Index of GEO satellites with alarm, ordered in order of alarm reception. Returns the position of SBASdata struct GEO index
	int		numAlarmGEO[NUMPOSFREQSBASMSG];					//Number of satellites with alarm

	//PRN Mask (current)
	int				PRNactive[NUMPOSFREQSBASMSG][5][MAX_GNSS][MAX_SBAS_PRN]; 	//Given a IODP or IODM, a GNSS system and a PRN number, check if that satellite has corrections or not
	int				PRN2pos[NUMPOSFREQSBASMSG][5][MAX_GNSS][MAX_SBAS_PRN];		//Given a IODP or IODM, a GNSS system and a PRN, return the position in the mask (in the same order as messages type 2-5,6,7,25,25,28)
	int				pos2PRN[NUMPOSFREQSBASMSG][5][92];							//Given a IODP or IODM and a position in the list of 51/92 satellites with corrections, return its PRN (in the same order as messages type 2-5,6,7,25,25,28)
	enum GNSSystem	pos2GNSS[NUMPOSFREQSBASMSG][5][92];							//Given a IODP or IODM and a position in the list of 51/92 satellites with corrections, return its GNSS system (in the same order as messages type 2-5,6,7,25,25,28)
	int				Slot2pos[NUMPOSFREQSBASMSG][5][215];						//Given a IODM and a position in the satellite slot number, return the position in mask
	int				IODPmask;													//IODP (Issue Of Data PRN mask) Identifies the current PRN mask (for SBAS 1 Frequency)
	int				IODMmask;													//IODM (Issue Of Data Mask) Identifies the current PRN mask (for SBAS DFMC)
	int				numsatellites[NUMPOSFREQSBASMSG][5];						//Number of satellites monitored (sorted by IODP or IODM)

	//PRN Mask (previous)
	int		oldIODPmask;
	int		oldIODMmask;

	//Fast corrections
	int		lastfastmessage[51];					//Saves the last message type number received for fast corrections (2,3,4,5,6,24), sorted by position in mask
	int		poslastFC[5][51];						//Index of the last fast correction received, sorted by IODP and PRN position in mask
	int		numFC[5][51];							//Number of fast correction received, sorted by IODP and PRN position in mask
	int		useforbidden[MAX_GNSS][MAX_SBAS_PRN];	//Flag to indicate if UDREI=14 or UDREI=15 has been received, cleared when an UDREI<=13 is received

	//The next variables are sorted by IODP, received message and PRN position in mask. 
	//NOTE:the last message position will be always saved in poslastFC, and from that position, we will have to search backwards. 
	//For example, if poslastFC[0][35]=10, the previous messages (in order of arrival) will be from 9 to 0, and then from MAXSBASFASTCORR-1 to 11
	int		IODF[5][MAXSBASFASTCORR][51];	    //IODF (Issue Of Data Fast correction) Identifies the current fast corrections (from messages type 2,3,4,5,24)
	double	PRC[5][MAXSBASFASTCORR][51];	    //PRC (Pseudo Range Correction). These are fast corrections applied to the pseudorange (0.125m resolution,stored in meters)
	double	RRC[5][MAXSBASFASTCORR][51];	    //RRC (Range Rate Correction). These are fast corrections applied to the pseudorange (not broadcasted)
	double	UDREI[5][MAXSBASFASTCORR][51];	    //UDREI (User Differential Range Error Indicator) of combined fast and long corrections 
	double	UDRE[5][MAXSBASFASTCORR][51];	    //UDRE (User Differential Range Error) Accuracy value of combined fast and long corrections (except ionosphere) (in meters)
	double	UDREsigma[5][MAXSBASFASTCORR][51];  //UDRE (User Differential Range Error) Accuracy variance of combined fast and long corrections (in meters^2)
	int		IODPfastcorr;			   			//IODP (Issue Of Data PRN mask) Identifies the PRN mask of the fast corrections

	double	UDREI6[51];						    //UDREI received in type 6 message
	double	UDRE6[51];			   			 	//UDRE received in type 6 message (in meters)
	double	UDREsigma6[51];					    //UDRE received in type 6 message (in meters^2)
	int		IODFintegrity[51];				    //IODF (Issue Of Data Fast correction) Identifies the integrity information (from message type 6)

	//Fast corrections (previous)
	int		oldIODPfastcorr;
	double	oldUDREI6[51];	
	double	oldUDRE6[51];	
	double	oldUDREsigma6[51];
	int		oldIODFintegrity[51];	
	

	//Fast corrections degradation data
	int		IODPdegcorr;						//IODP (Issue Of Data PRN mask) Identifies the PRN mask of the degradation corrections
	//The following terms are sorted by IODP and PRN position in mask
	int		tlat[5];							//System latency (in seconds). Only in message type 7. Sorted by IODP.
	double	aifactor[5][51];					//Fast Correction Degradation Factor. (in meters/seconds^2). Sorted by IODP and PRN position.
	int		fastcorrtimeout[2][5][51];			//Time-out for fast corrections (seconds). These depend in degradation factor. Sorted by navigation mode, IODP and PRN position.
	int		fastcorrupdateinterval[5][51];		//Maximum update interval for fast corrections. These depend in degradation factor. Sorted by IODP and PRN position.

	//Fast corrections degradation data(previous)
	int		oldIODPdegcorr;

	//Degradation factors
	double	degradationfactors[16];			//Degradation factors only in message type 10. It consists of 16 factors (maybe in the future more are added)
	
	//Degradation factors (previous)
	double	olddegradationfactors[16];	

	//Long term satellite error corrections
	double	longtermsaterrcorrections[5][51][15];		//Long term satellite error correction. Only for messages type 25 and type 24. Sorted by IODP, satellite and parameter position
	int		IODPlongterm;								//IODP for long term satellite corrections

	//Long term satellite error corrections (previous)
	double	prevlongtermsaterrcorrections[5][51][15];	//This previous data is only to save messages with a different IOD from the last one received.
														//This is useful when a new IOD arrives, but we don't have the ephemeris broadcast block for that satellite
														//in the navigation message, so we can keep using the previous one until it times out
	int		oldIODPlongterm;
	
	//GEO Navigation message
	double	geonavigationmessage[17];		//GEO Navigation Message data from message type 9

	//GEO Navigation message (previous)
	double	oldgeonavigationmessage[17];	

	//GEO Almanacs message
	int		numgeoalmanacs;					//Number of GEO almanacs saved in current message
	double	geoalmanacsmessage[3][12];		//GEO Almanacs Message from message type 17
	
	//GEO Almanacs message (previous)
	int		oldnumgeoalmanacs;	
	double	oldgeoalmanacsmessage[3][12];	

	//Service message
	int		servicemessagesreceived[9][8];			//Save which message numbers have been received (sorted by IODS)
	int		numberofregions[9][4];					//Number of regions received grouped by IODS and priority code
	double	regioncoordinates[9][4][40][12];		//Contains the coordinates for all the regions by IODS (There can be a maximum of 40 regions)
	int		maxprioritycode[9];						//Highest priority code received (sorted by IODS)
	int		totalservicemessagesreceived[9];		//Total number of servicemessagesreceived (sorted by IODS)
	int		IODS;									//Issue of Data Service. Only for Service message. It will change when any parameter in Service message is changed

	//Service message (previous)
	int		oldIODS;		

	//Network Time/UTC Parameters
	double	networktimemessage[13];					//Network time/UTC Parameters from message type 12

	//Clock-Ephemeris Covariance Matrix
	double	clockephemeriscovariance[5][51][14];	//Clock-Ephemeris Covariance Matrix from message type 28 (sorted by IODP and satellite)
	int		IODPcovariance;							//Number of satellite with Clock-Ephemeris Covariance Matrix in message type 28 (1 or 2)

	//Clock-Ephemeris Covariance Matrix (previous)
	int		oldIODPcovariance;			


	//Iono messages
	int		IGPbandreceived[11];			//IGP Mask bands received
	int		numIGPbandbroadcast;			//Number of IGP Mask bands that are being broadcast
	int		numIGPbandreceived;				//Number of IGP Mask bands received
	int		IODImask;						//IODI (Issue of Data Ionosphere) for the ionosphere mask
	int		IODIcorr;						//IODI (Issue of Data Ionosphere) for the ionosphere delay corrections
	int		BlockIDPlace2Grid[11][14][15];	//For a given position in message type 26, get the position in the iono mask (for that band). 
												//The order is Band Number, Block ID and position. The returned value is the position in the mask
	int		IGPinMask[5][11][202];			//For a given Band Number, indicates wheter this IGP is monitored or not in any iono mask received. 
												//The order is IODI, Band Number and position in mask.
	int		IGP2Mask[11][202];				//Saves to which IODI corresponds the last iono delay data received for the given band nubmer and IGP.
	double	Ionodelay[11][202];				//Vertical delay for each IGP in mask (meters) for each band number.
	double	IonoGIVE[11][202];				//Ionospheric vertical error GIVE (meters) for each band number.
	double	Ionosigma[11][202];				//Ionospheric vertical error GIVE sigma (meters^2) for each band number.
	TTime	lastiono[11][202];				//Time since last iono data received (for each IGP in mask) for each band number.

	//Iono messages (previous)
	int		oldIGPbandreceived[11];		
	int		oldnumIGPbandbroadcast;
	int		oldnumIGPbandreceived;
	int		oldIODImask;
	int		oldIODIcorr;
	int		oldBlockIDPlace2Grid[11][14][15];

	////SBAS DFMC messages
	//PRN Mask constant values
	int				PRN2SlotNumber[NUMPOSFREQSBASMSG][MAX_GNSS][MAX_SBAS_PRN];			//Given a GNSS system and a PRN, return the slot number
	int				SlotNumber2PRN[NUMPOSFREQSBASMSG][MAX_SBASDFMC_MASKSLOTNUMBER];		//Given a slot number, return its PRN. This value is fixed and does not depend on IODM
	enum GNSSystem	SlotNumber2GNSS[NUMPOSFREQSBASMSG][MAX_SBASDFMC_MASKSLOTNUMBER];	//Given a slot number, return its GNSS. This value is fixed and does not depend on IODM

	//DFREI and DFRECI data
	//int		DFRECI[5][92];				//SBAS DFMC DFRECI (Dual Frequency Error Change Indicator) by IODM and satellite in mask
	int		DFREI[5][92];				//SBAS DFMC DFREI (Dual Frequency Error Indicator) by IODM and satellite in mask 
	int		DFRECI2bumped[5][92];		//To indicate if DFREI has been increased by 1 after receiver a DFRECI=2 (it only has to be increased once)
	TTime	lastDFREIreceived[5][92];	//SBAS DFMC last refresh of DFREI data (either my MT34 or MT35 or MT36 or MT32 or MT40)

	//Clock-Ephemeris Covariance Matrix
	double	covarianceMatrixDFMC[215][14];		//Clock-Ephemeris Covariance Matrix from message type 32 (sorted by satellite position in mask)
	double	clockephemerisDFMC[215][15];		//Orbit correction from message type 32 (sorted by satellite position in mask)
	TTime	clockephemerisDFMCTime[215];		//Time of last message type 32 for each satellite

	//OBAD and DFREI data
	double	OBAD[MAX_GNSS][3];
	double	commonOBAD[5];
	double	DFREITable[15];

	//SBAS satellites ephemerides
	double  	covarianceMatrixSBASDFMC[14];			//Clock-Ephemeris Covariance Matrix from message type 40 for SBAS satellites only (positions 120 to 158 in mask), sorted by IODG
	TBRDCblock	navSBASmessage;							//Navigation message for SBAS satellites
	int			SBASproviderID;
	int			DFREISBASMT3940;
	double 		RCORRSBASMT3940;
	TTime		lastMT3940received;						//Time of the last MT39 or MT40 received (the last one received with current IODG) for counting for the timeout

	//DFMC Network time parameters
	double	GNSSTimeOffsetsConst[MAX_GNSS][2];
	double	GNSSTimeOffsetsCommon[9];

	//DFMC GEO almanacs 
	TBRDCblock	DFMCalmanac[39];					//Almanac for DFMC GEOs. The position is GEOPRN-120 (0 to 38 or PRNs 120 to 158)
	TTime		DFMCalmanacTime[39];				//Last received almanac per each GEO. The position is GEOPRN-120 (0 to 38 or PRNs 120 to 158)
	int			posWithDataDFMCalmanac[39];			//Index with the position with data (position 0 with first almanac from a GEO received, position 2 with second almanac received,...)
	int			numDFMCalmanac;						//Number of DFMC almanac received
	int			DFMCSBASProvider[39];				//SBAS provided ID for each GEO in almanac
	int			WNROcount;							//Week Number Roll Overs count

	//Time-out multiplier factor for IvalidMT32 and IvalidMT39/40
	double	tmoutFactor[2];


	///Other data

	//GPS frequencies used flag in SBAS DFMC
	int		GPSfrequenciesUsed;		//Flag GPS frequencies used for testbed in Australia
									// 0 -> Not set (default to GPS L1/L5)
									// 1 -> Using GPS L1/L2
									// 2 -> Using GPS L1/L5

	//Data for user model sigma multipath
	int		sigmamultipathtype;		//0 => The user sigma multipath depends on elevation
									//1 => The user sigma multipath depends on SNR

	int		numsigmamultipath;		//Stores the number of ranges given in the user sigma multipath model (0 means no data)

	double	**sigmamultipathdata;	//Stores the data of the user sigma multipath model

	//Counter for number of satellites with sigma of 60 metres
	int		numSat60;
} TSBASdata;

//Struct for saving SBASdata for each GEO and the summary data
typedef struct {
	TSBASdata *SBASdata;

	//Buffer for saving lines of readed messages 
	char	*bufferlines[MAX_LINES_BUFFERED_SBAS_MESSAGES];
	int		bufferlineslen[MAX_LINES_BUFFERED_SBAS_MESSAGES];

	//Buffer for saving lines missing
	int		*numlinesmissing;
	int		*missingmessagesvector;

	//Buffer for MT26 messages
	TSBASblockIono	***ionobuffer;	

	//Buffer for decoding messages
	TSBASblock *sbasblock;

	//Data for SBAS summary (these are specific to SBAS, it complements the normal summary)
	double	HBIR;							//Horizontal best integrity ratio
	double	VBIR;							//Vertical best integrity ratio
	double	HWIR;							//Horizontal worst integrity ratio
	double	VWIR;							//Vertical worst integrity ratio
	double	HIRPercentileSamples;			//95th horizontal integrity ratio percentile of the samples
	double	VIRPercentileSamples;			//95th vertical integrity ratio percentile of the samples
	double	HPLPercentileSamples;			//95th horizontal protection level percentile of the samples
	double	VPLPercentileSamples;			//95th vertical protection level percentile of the samples
	double	*HPL;							//Vector with all horizontal protection levels
	double	*VPL;							//Vector with all vertical protection levels
	double	*HIR;							//Vector with all horizontal integrity ratios 
	double	*VIR;							//Vector with all vertical integrity ratios
	double	MaxHPL;							//Maximum horizontal protection level
	double	MaxVPL;							//Maximum vertical protection level
	double	MinHPL;							//Minimum horizontal protection level
	double	MinVPL;							//Minimum vertical protection level
	double	decimation;						//Decimation step (saved here for the case options->decimate=0, put a value of 1)
	
	int		TotalPAEpochs;					//Total epochs with PA solution (this value also is the size of HError and VError vectors)
	int		TotalPAEpochsAvail;				//Total epochs with PA solution and under HAL and VAL
	int		TotalNPAEpochs;					//Total epochs with NPA solution (only when PA is preferred mode)
	int		NumEpochsRisk;					//Number of epochs affected by discontinuity
	int		NumEpochsRiskMar;				//Number of epochs affected by discontinuity (maritime computation mode)
	int		NumMI;							//Number of epochs with misleading information
	int		NumHMI;							//Number of epochs with horizontal misleading information
	int		NumVMI;							//Number of epochs with vertical misleading information

	TTime	MaxHPLEpoch;					//Timestamp of the epoch with maximum horizontal protection level
	TTime	MaxVPLEpoch;					//Timestamp of the epoch with maximum vertical protection level
	TTime	MinHPLEpoch;					//Timestamp of the epoch with minimum horizontal protection level
	TTime	MinVPLEpoch;					//Timestamp of the epoch with minimum vertical protection level

	TTime	HBIREpoch;						//Timestamp of the epoch with horizontal best integrity ratio
	TTime	VBIREpoch;						//Timestamp of the epoch with vertical best integrity ratio
	TTime	HWIREpoch;						//Timestamp of the epoch with horizontal worst integrity ratio
	TTime	VWIREpoch;						//Timestamp of the epoch with vertical worst integrity ratio
	
	TTime	LastEpochAvailPrevCurrDisc;		//Last epoch available before the current disconinuity for continuity risk computation
	TTime	FirstEpochAvailAfterPrevDisc;	//First epoch available after the previous discontinuity for continuity risk computation

} TSBASdatabox;



// Structure which contains the corrections for a satellite in a single epoch
typedef struct {
	double 			SatCoord[3];			//Satellite coordinates (X-Y-Z) after applying SBAS corrections
	double 			SatCoordbrdc[3];		//Satellite coordinates from broadcast (X-Y-Z)
	double 			SatCoordCor[3];			//Long term correction to apply in the satellite coordinates (X-Y-Z)
	double			Clock;					//Clock correction from broadcast
	double			Clockbrdc;				//Long term correction to apply in the clock
	double			ClockCor;				//Clock correction after applying SBAS corrections
	int				IOD;					//IOD used (which must match the navigation IODE)
	int				IODnoSBAS;				//IOD used when there is no mathc with the IODE of SBAS (only in NPA)
	double			ionocorrection;			//Ionosphere correction
	int				uraindex;				//URA index value (in message type 9)
	double			PRC;					//PRC value (fast correction)
	double			RRC;					//RRC value (fast correction)
	double			RRCtime;				//RRC value multiplied by the difference between current time and time of applicabily of last fast correction
	int				UDREI;					//UDRE indicator of the fast correction
	double			UDREsigma;				//UDRE sigma of the fast correction (in meters^2)
	double			fastcorrdegfactor;		//Fast correction degradation factor (in meters/seconds^2)
	double			fastcorrtmout;			//Time out for current satellite
	double			fastcorrsmallertmout;	//Smallest time out for all satellites (used for RRC)
	double			tPRC;					//Time used for computing PRC timeout
	double			tudre;					//Time used for computing UDRE sigma timeout
	double			tu;						//Time used for computing fast correction degradation

	double			longtermdegradation;	//Long term degradation parameter
	double			geonavdegradation;		//GEO navigation degradation
	double			enroutedegradation;		//En route through NPA degradation parameter
	double			GLOclkdegradation;		//GLONASS clock conversion to GPS time degradation
	double			fastcorrdeg;			//Fast correction degradation
	double			RRCdeg;					//Range-rate correction degradation
	double			deltaudre;				//Delta UDRE (factor that multiplies sigma UDRE)
	int				deltaudresource;		//Indicates the data source for Delta UDRE(27 or 28 for their respective message type,-27 or -28 if received any of these
												//message types but there was missing data or was timed out, 0 if no message type received)
	int				mt10avail;				//Indicates if message type 10 is available


	double			sigma2flt;			//Sigma flt (sigma of fast and long term corrections) (in meters^2)
	double			sigma2iono;			//Sigma of the ionosphere (in meters^2)
	double			sigma2tropo;		//Sigma of the troposphere (in meters^2)
	double			sigma2noise;		//Sigma of the airborne receiver noise (in meters^2)
	double			sigma2divergence;	//Sigma of the airborne receiver divergence (in meters^2)
	double			sigma2multipath;	//Sigma of the airborne receiver multipath (in meters^2)
	double			sigma2air;			//Total sigma of the airborne receiver (in meters^2)
	double			SBASsatsigma2;		//Total SBAS sigma for current satellite (in meters^2)

	int				fastcorIODP;		//IODP used for fast corrections
	int				fastcorIODF;		//IODF used for fast corrections
	int				fastcorPRNpos;		//PRN position in the fast correction mask (1..51)
	int				longtermIODP;		//IODP used for long term corrections
	int				longtermPRNpos;		//PRN position in the long term correction mask (1..51)
	int				serviceIODS;		//IODS used in service message (message type 27)
	int				covarianceIODP;		//IODP used in Clock ephemeris covariance matrix (message type 28)
	int				covariancePRNpos;	//PRN position in the covariance mask (1..51)
	int				ionomodelflag;		//Flag that indicates which iono model is used (-1->no model, 0->SBASiono, 1->Klobuchar, 2->Other model)

	int				SBASplotIonoAvail;	//Flag to indicate that we are computing the SBAS iono corrections availability. No processing is done

	double			GEOURA;					//GEO URA value from message type 9 (in metres)


	int				IODM;					//IODM of the used mask
	int				DFREI;					//DFREI value used for the current satellite
	int				DFRECIbumped;			//Flag to indicate if DREI has been bumped by 1
	int				IODN;					//IODN in MT32 or IODG in MT39/40 (IODG and IODN must match if both messages are used)
	double			DFRE;					//DFRE value after converting from DFREI (metres)
	double			sigma2DFC;				//Computed DFC for the satellite (metres^2)
	double			sigma2ionoresidual;		//Computed sigma of the residual ionospheric error
	double			tDFREI;					//Time of the last DFREI received (seconds of day)
	double			lastMT32;				//Time of the last MT32 received (seconds of day)
	double			lastMT3940;				//Time of the last MT39/40 received (seconds of day)
	double			ValidTimeMT32;			//Validity time of MT32 (including multiplication factor of PA/NPA modes) (seconds)
	double			ValidTimeMT3940;		//Validity time of MT39/40 (including multiplication factor of PA/NPA modes) (seconds)
	double			deltaDFRE;				//Computed Delta DFRE from SBAS DFMC (adimensional)
	double			ccovariance;			//Ccovariance   from MT37 or from parameter (metres)
	double			cer;					//Cer  			from MT37 or from parameter (metres)
	double			ccorr;					//Ccorr 		from MT37 or from parameter (metres)
	double			icorr;					//Icorr 		from MT37 or from parameter (seconds)
	double			rcorr;					//Rcorr 		from MT37 or from parameter (metres/seconds)
	double			deltarcorr;				//Rcorr multiplier from MT32 or MT39/40 or from parameter (adimensional)
	double			rcorrSV;				//Computed RcorrSV (metres/seconds)
	double			tCorrTime;				//Time of last received bit of MT32 or MT39/40 (seconds of day)
	double			Ecorr;					//Ecorr computed degradation term (metres)
	double			Eer;					//Eer   computed degradation term (metres)
} TSBAScorr;

//Structure which contains the active user defined errors
typedef struct {
	TTime					*activeErrorsStart[NUMERRORFUNCTIONS];	//Saves time when the active error functions start, sorted by error function type
	TTime					*activeErrorsEnd[NUMERRORFUNCTIONS];	//Saves time when the active error functions end, sorted by error function type
	double					**ErrorParam[NUMERRORFUNCTIONS];		//Saves the parameters for each active error functions, sorted by error function type
	int						numactiveErrors[NUMERRORFUNCTIONS];		//Saves the number of active errors, sorted by error function type
	int						totalactiveErrors;						//Saves the total number of active errors
	int						numcolumnstime;							//Saves the number of columns needed to give the time duration (depends if SoD or Tow is chosen, and how length is given)
	int						timetype;								//Saves if we are using SoD or Tow time format (0 for SoD, 1 for ToW) in user input
	int						lengthtype;								//Saves if we are using lenght or end time for error function duration (0->length, 1->end time)
	unsigned int			seed;									//Saves the inital seed for AWGN error function 
	int						*measFreq[NUMERRORFUNCTIONS];			//Saves the frequency of the measurement where the user defined error is applied
	enum MeasurementType	*measType[NUMERRORFUNCTIONS];			//Saves the meas type where the user defined error is applied
	enum GNSSystem			*System[NUMERRORFUNCTIONS];				//Saves the satellite constellation where the user defined error is applied
	int						*PRN[NUMERRORFUNCTIONS];				//Saves the PRN where the user defined error is applied
} TUserError;

//Structure which contains data for Stanford-ESA plots
typedef struct {
	double						xstep;						//Size of pixel in horizontal axis (error axis, in meters)
	double						ystep;						//Size of pixel in vertical axis (protection level axis, in meters)
	double						xmax;						//Maximum value in horizontal axis
	double						ymax;						//Maximum value in vertical axis
	double						HWIR;						//Horizontal worst integrity ratio
	double						VWIR;						//Vertical worst integrity ratio
	double						**G;						//Geometry matrix in NEU for Stanford-ESA computation
	int							*k;							//Vector indicating the current combination number for a given depth
	int							*kmask;						//Vector indicating if a satellite (a row of data) is selected (1) or not (0) for current combination
	int							numUsablesSatellites;		//Size of first dimension of G matrix (number of usable satellites)
	int							numSatSolutionFilter;		//Size of k and kmask arrays (maximum number of satellites included in any navigation solution)
	unsigned long long int		numpixelhor;				//Number of pixels in horizontal axis
	unsigned long long int		numpixelver;				//Number of pixels in vertical axis
	unsigned long long int		numsamplesProcessed;		//Total number of samples (geometries) processed
	unsigned long long int		numsamplesComputed;			//Total number of samples (geometries) computed
	unsigned long long int		numsamplesSingular;			//Total number of samples with singular geometry matrix
	unsigned long long int		numsamplesMI;				//Total number of samples with MIs
	unsigned long long int		numsamplesHMI;				//Total number of samples with horizontal MIs
	unsigned long long int		numsamplesVMI;				//Total number of samples with vertical MIs
	unsigned long long int		**counthor;					//Number of ocurrences for each pixel in horizontal error
	unsigned long long int		**countver;					//Number of ocurrences for each pixel in vertical error
} TStdESA;

//Structure for SBAS plots
typedef struct {
	int						AvailabilityMemFactor; 		//Memory size will be fit according to Availability map resolution (1º, .1º, .01º)
	int						IonoMemFactor;				//Memory size will be fit according to Iono map resolution (1º, .1º, .01º)
	int						IonoLatSize;				//Number of latitude positions to put in IonoNumEpochsAvail matrix
	int						IonoLonSize;				//Number of longitude positions to put in IonoNumEpochsAvail matrix
	int						AvailabilityLatSize;		//Number of latitude positions to put in SBASNumEpochsAvail matrix
	int						AvailabilityLonSize;		//Number of longitude positions to put in SBASNumEpochsAvail matrix
	int						offsetLatAvail;				//Offset value to convert the first position in latitude to position 0 in SBASNumEpochsAvail matrix
	int						offsetLonAvail;				//Offset value to convert the first position in longitude to position 0 in SBASNumEpochsAvail matrix
	int						offsetLatIono;				//Offset value to convert the first position in latitude to position 0 in IonoNumEpochsAvail matrix
	int						offsetLonIono;				//Offset value to convert the first position in longitude to position 0 in IonoNumEpochsAvail matrix

	//Daily maps
	int						**SBASNumEpochsAvail;		//Matrix to save the number of available epoch in each position [latitude][longitude] for Availability maps
	int						**IonoNumEpochsAvail;		//Matrix to save the number of available epochs with ionosphere corrections in each position [latitude][longitude] for Ionosphere maps
	int						**SBASNumEpochsRisk;		//Matrix to save the number of epochs affected by a discontiniuty [latitude][longitude] for continuity risk maps
	int						**SBASNumEpochsRiskMar;		//Matrix to save the number of epochs affected by a discontiniuty [latitude][longitude] for continuity risk maps (maritime mode)
	int						**SBASNumEpochsDOP;			//Matrix to save the number of epochs where DOP (both HDOP or PDOP) could be computed [latitude][longitude] for HDOP/PDOP maps
	double					**LastEpochAvailPrevCurrDisc;	//Matrix to save the last epoch available before the current discontinuity (in seconds of day) [latitude][longitude] for continuity risk maps
	double					**FirstEpochAvailAfterPrevDisc;	//Matrix to save the first epoch available after the previous discontinuity (in seconds of day) [latitude][longitude] for continuity risk maps
	float 					***HDOPValues;				//Matrix to save the values of HDOP in each position [latitude][longitude][86400] (In "float" type to save space)
	float 					***PDOPValues;				//Matrix to save the values of HDOP in each position [latitude][longitude][86400] (In "float" type to save space)
	float 					***GDOPValues;				//Matrix to save the values of GDOP in each position [latitude][longitude][86400] (In "float" type to save space)
	double					**HDOPMean;					//Matrix to save the total value of HDOP in each position [latitude][longitude]
	double					**PDOPMean;					//Matrix to save the total value of HDOP in each position [latitude][longitude]
	double					**GDOPMean;					//Matrix to save the total value of GDOP in each position [latitude][longitude]

	//Hourly maps
	int						**SBASNumEpochsAvailHourly;		//Matrix to save the number of available epoch in each position [latitude][longitude] for Availability maps for the current hour
	int						**IonoNumEpochsAvailHourly;		//Matrix to save the number of available epochs with ionosphere corrections in each position [latitude][longitude] for Ionosphere maps for the current hour
	int						**SBASNumEpochsRiskHourly;		//Matrix to save the number of epochs affected by a discontiniuty [latitude][longitude] for continuity risk maps for the current hour
	int						**SBASNumEpochsRiskHourlyMar;	//Matrix to save the number of epochs affected by a discontiniuty [latitude][longitude] for continuity risk maps for the current hour (maritime mode)
	int						**SBASNumEpochsDOPHourly;			//Matrix to save the number of epochs where DOP (both HDOP or PDOP) could be computed [latitude][longitude] for HDOP/PDOP maps for the current hour
	double					**LastEpochAvailPrevCurrDiscHourly;	//Matrix to save the last epoch available before the current discontinuity (in seconds of day) [latitude][longitude] for continuity risk maps for the current hour
	double					**FirstEpochAvailAfterPrevDiscHourly;	//Matrix to save the first epoch available after the previous discontinuity (in seconds of day) [latitude][longitude] for continuity risk maps for the current hour
	float 					***HDOPValuesHourly;			//Matrix to save the values of HDOP in each position [latitude][longitude][3600] for the current hour ("float" type)
	float 					***PDOPValuesHourly;			//Matrix to save the values of HDOP in each position [latitude][longitude][3600] for the current hour ("float" type)
	float 					***GDOPValuesHourly;			//Matrix to save the values of GDOP in each position [latitude][longitude][3600] for the current hour ("float" type)
	double					**HDOPMeanHourly;				//Matrix to save the total value of HDOP in each position [latitude][longitude] for the current hour
	double					**PDOPMeanHourly;				//Matrix to save the total value of HDOP in each position [latitude][longitude] for the current hour
	double					**GDOPMeanHourly;				//Matrix to save the total value of GDOP in each position [latitude][longitude] for the current hour
	
	double					HPL;							//Horizontal protection level for a single epoch and position
	double					VPL;							//Vertical protection level for a single epoch and position

	//Elevation of GEO in each position in grid
	float					***GEOelevPos;					//Elevation of each GEO	in each position in map for Availability maps
	float					***GEOelevPosIono;				//Elevation of each GEO	in each position in map for Ionosphere maps
	int						numGEOelevPos;					//Number of GEOs allocated in GEOelevPos array
	int						GEOelevNullPos;					//0 if no GEO elevation filtering is done, 1 if it is used. 
																//This variable will multiply to the accessed position of GEOelevPos, so when no GEO elevation filtering is done, always 0,0,0 is accessed
	int						numGEOWithElevComputed;			//Number of GEOs which had their elevation in each position in the grid computed (we need to wait until their coordinates are received)
	int						GEOWithElevComputed[MAX_SBAS_PRN];	//GEOs which had their elevation in each position in the grid computed (in the same order as in SBASdata structure)

} TSBASPlots;

// Structure for time management of binary files RTCM3
typedef struct {
	unsigned int minimum;
	unsigned int range_lowerLimit;
	unsigned int range_upperLimit;
} TlockTime;

// Structure for header of binary files RTCM3
typedef struct {
	unsigned int		message_type;
	unsigned int		station_id;
	unsigned long int	epoch_time;
	char				synchronous;
	unsigned int		gps_no;
	char				smooth_indicator;
	int					smooth_interval;
} TRTCM3header;

// Structure for message 1004 of binary files RTCM3
typedef struct {
	unsigned int	satellite_id;
	unsigned int	l1_code_indicator;
	double			l1_pseudoR;
	float			l1_part_phaseR;
	unsigned int	l1_lock_indicator;
	double			l1_N_ambiguity;
	float			l1_cnr;
	unsigned int	l2_code_indicator;
	float			pseudoR_differ;
	float			l2Phase_l1Pseudo;
	unsigned int	l2_lock_indicator;
	float			l2_cnr;
} TMSG1004;

// Structure for message 1006 of binary files RTCM3
typedef struct {
	unsigned int	message_type;
	unsigned int	station_id;
	char			gps_indicator;
	char			glonass_indicator;
	char			referStation_indicator;
	double			ecef_x;
	char			oscillator_indicator;
	double			ecef_y;
	double			ecef_z;
	float			antenna_height;
} TMSG1006;

// Structure for message 1008 of binary files RTCM v3.x
typedef struct {
	unsigned int	message_type;
	unsigned int	station_id;
	unsigned int	descriptor_no;
	char			descriptor[32];
	unsigned int	setup_id;
	unsigned int	serialNum_no;
	char			serialNum[32];
} TMSG1008;

// RTCM v3.x structure
typedef struct {
	unsigned int	doWeHaveHeader;
	int				numObsHeaderRead;
	int				doWeHaveAntennaPos;
	int				doWeHaveAntennaName;
	int				counter;
	int				L1flagLLI[MAX_SATELLITES_PER_GNSS];
	int				L2flagLLI[MAX_SATELLITES_PER_GNSS];
	int				L1prevLLI[MAX_SATELLITES_PER_GNSS];
	int				L2prevLLI[MAX_SATELLITES_PER_GNSS];
	int				hour;
	int				previousHour;
	char			content_str[4100];
	TRTCM3header	header;
	TMSG1004		msg1004[64];
	TMSG1006		msg1006;
	TMSG1008		msg1008;
} TRTCM3;

// Enumerator for RTCM v2.x states
enum State {
	Initial,
	HeaderReading,
	BodyReading,
	EndOneMessage,
	EndOfString,
	EndOfFile
};

// RTCM v2.x data read structure
typedef struct {
	int			indicator_end;
	long int	offset;
	char		ch_str[READWORDSNO+1];
} TdataRead;

// RTCM v2.x header structure
typedef struct {
	int		message_type;
	int		station_id;
	float	modi_zcount;
	int		sequence_no;
	int		dataword_no;
	char	station_health[STATIONIDBIT+1];
} TRTCM2header;

// RTCM v2.x message type 1 structure
typedef struct {
	float	scale_factor;
//	float	udre_lowerlimit;
//	float	udre_upperlimit;
	int		udre;
	int		satellite_id;
	float	prc;
	float	rrc;
	int		iod;
} TMSG1;

// RTCM v2.x message type 2 structure
typedef struct {
	float	scale_factor;
//	float	udre_lowerlimit;
//	float	udre_upperlimit;
	int		udre;
	int		satellite_id;
	float	delta_prc;
	float	delta_rrc;
	int		iod;
} TMSG2;

// RTCM v2.x message type 3 structure
typedef struct {
	double	x_coord;
	double	y_coord;
	double	z_coord;
} TMSG3;

// RTCM x2.v message type 24 structure
typedef struct {
	double	x_coord;
	double	y_coord;
	double	z_coord;
	char	system_indicator;
	char	AH_indicator;
	float	antenna_height; 
} TMSG24;

// RTCM x2.v structure
typedef struct {
	int				i, k;
	int				firstPass;
	int				firstPass2;
	int				checkControl;
	int				doWeHaveHeaderAnt;
	int				doWeHaveHeaderCorr;
	int				antMSG3, antMSG24;
	int				last2bits[2];
	char			body_str[31*CONTENTBIT+1];
	char			allwords_str[READWORDSNO+LEFTLIMIT+1];
	char			leftwords_str[LEFTLIMIT+1];
	char			preamble[PREAMBLEBIT+1];
	char			header_str[2*CONTENTBIT+1];
	char			word_current[WORDBIT+1]; //The extra byte to leave space for a '\0' at end
	char			correctedWord[25];
	char			indicator_message;
	char			indicator_word;
	double			prevZcount;
	size_t			l, l1;
	enum State		my_state;
	TTime			t;
	TdataRead		dataRead;
	TRTCM2header	header;
} TRTCM2;

// Options structure
typedef struct {
	//KML file
	FILE 	*fdkml;
	FILE 	*fdkml0;
	int		KMLTimeStamps;		// KMLTimeStamps= 0 => Do not insert time stamps in KML (default)
								// KMLTimeStamps= 1 => Insert time stamps in KML

	int		KMLEGM96height;		// KMLEGM96height = 0 => Do not correct KML height with EGM96 geoid height
								// KMLEGM96height = 1 => Correct KML height with EGM96 geoid height (default)

	double	KMLTimeStampDec;	// Decimation for TimeStamps in seconds (default 30)
	int		numKMLTimeRanges;	// Number of time ranges for printing timestamps
	int		referenceStations;	// Add reference stations in KML file in DGNSS mode (default on)
	double	**KMLtimeranges;	// Time ranges for printing timestamps

	//Stanford-ESA LOI file
	FILE    *fdstdESALOI;

	//SP3 output file
	char	SP3Letter;
	int		SP3PRN;
	int		WriteSPPsolInDGNSSmodeSP3;		// 0 => For output SP3 file, in DGNSS mode do not write SPP solution to file (default)
											// 1 => For output SP3 file, in DGNSS mode write SPP solution to file

	//Reference output file
	int		YearSoDRefFile;					// 0 => Write timestamp in other format
											// 1 => Write timestamp in 'Year DoY SoD' (default)

	int		GPSWeekRefFile;					// 0 => Write timestamp in other format (default)
											// 1 => Write timestamp in 'GPSWeek SoW'

	int		CalendarTimeRefFile;			// 0 => Write timestamp in other format (default)
											// 1 => Write timestamp in 'Year/Month/Day HH:MM:SS.zzz'

	int		WriteSPPsolInDGNSSmodeRefFile;	// 0 => For output reference file, in DGNSS mode do not write SPP solution to file (default)
											// 1 => For output reference file, in DGNSS mode write SPP solution to file

	int		GeodeticCoordRefFile;			// 0 => For output reference file, write solution in cartesian coordinates (default)
	     									// 1 => For output reference file, write solution in geodetic coordinates

	// Pathes for ESA tropospheric model and Nequick model files
	char 	abs_exe_path[1000];
	char 	model_dir[100];
	char 	tropoGaldir[100];
	char 	NeQuickdir[100];

	// Verbose options
	int	printModel;			// printModel = 1				=> Print all the model values
							// printModel = 0				=> Do not print model values (default)

	int	printPrefit;		// printPrefit = 1				=> Print prefilter residuals of measurements
							// printPrefit = 0				=> Do not print prefilter residuals of measurements (default)

	int	printPrefitUnsel;	// printPrefitUnsel = 1			=> Print prefilter residuals for unselecteld measurements
							// printPrefitUnsel = 0			=> Do not print prefilter residuals of unselected measurements (default)

	int	printPostfit;		// printPostfit = 1				=> Print postfilter residuals of measurements
							// printPostfit = 0				=> Do not print postfilter residuals of measurements (default)

	int	printFilterSolution;	// printFilterSolution = 1	=> Print the estimation of the parameters of the filter
								// printFilterSolution = 0	=> Do not print the estimation of the parameters of the filter (default)

	int	printInfo;			// printInfo = 1				=> Print general information (default)
							// printInfo = 0				=> Do not print info messages 

	int printSFdata;		// printSFdata = 1				=> Print computed data for Single Frequency cycle-slip detector
							// printSFdata = 0              => Do not print computed data for Single Frequency cycle-slip detector (default)

	int printMWdata;		// printMWdata = 1				=> Print computed data for MW cycle-slip detector
							// printMWdata = 0              => Do not print computed data for MW cycle-slip detector (default)

	int printLIdata;		// printLIdata = 1				=> Print computed data for LI cycle-slip detector
							// printLIdata = 0              => Do not print computed data for LI cycle-slip detector (default)

	int printIGFdata;		// printIGFdata = 1				=> Print computed data for IGF cycle-slip detector
							// printIGFdata = 0             => Do not print computed data for IGF cycle-slip detector (default)

	int	printCycleslips;	// printCycleslips = 1			=> Print cycle slips
							// printCycleslips = 0			=> Do not print cycle slips (default)

	int	printSatellites;	// printSatellites = 1			=> Print satellites used for positioning for each epoch
							// printSatellites = 0			=> Do not print satellites used for positioning for each epoch (default)

	int	printInput;			// printInput = 1				=> Print information on measurements directly extracted from the RINEX
							// printInput = 0				=> Do not print information on measurements (default)

	int	printMeas;			// printMeas = 1				=> Print information on measurements and azimuth/elevation
							// printMeas = 0				=> Do not print information on measurements and azimuth/elevation (default)

	int	printMeasSNR;		// printMeasSNR = 1				=> Print SNR in MEAS message (default)
							// printMeasSNR = 0				=> Do not print SNR in MEAS message
	                            //This option is automatically disabled if printV5format option is enabled

	int	printMeasDoppler;	// printMeasDoppler = 1			=> Print Doppler in MEAS message
							// printMeasDoppler = 0			=> Do not print Doppler in MEAS message (default)
	                            //This option is automatically disabled if printV5format option is enabled

	int	printMeasLLI;		// printMeasLLI = 	1			=> Print LLI in MEAS message
							// printMeasLLI = 0				=> Do not print LLI in MEAS message (default)
	                            //This option is automatically disabled if printV5format option is enabled

	int printMeasDopplerCurrentHeader;	//Same as printMeasDoppler. If printMeasDoppler is 1, this option will auto enable/disable
										//depending if the current RINEX observation header has Doppler measurements


	int printMeasUserDefinedList[MAX_GNSS][MAX_SATELLITES_PER_GNSS]; 	// printMeasUserDefinedList = 0 -> No user defined measurements. Use defaults
																		// printMeasUserDefinedList = 1 -> User defined measurements

	int						printMeasMaxN;	//Max number of measurements printed for all GNSS and satellites  in MEAS message

	int						printMeasNumMeas[MAX_GNSS][MAX_SATELLITES_PER_GNSS];	
									//Number of measurements printed for each satellite in MEAS message

	int						printMeasLLIFlag[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_MEASUREMENTS_PER_SATELLITE]; 	
									//Flag to indicate if has to print LLI flag

	int						printMeasUserDefinedMeas[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
									//Flag to indicate if user set the measurements to print

	enum MeasurementType	printMeasListMeas[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_MEASUREMENTS_PER_SATELLITE];	
									//Measurement list to print for each satellite in MEAS message

	char					printMeasStr[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_MEASUREMENTS_PER_SATELLITE*3+1];	
									//Measurement string for each satellite in MEAS message

	int	printOutput;		// printOutput = 1				=> Print output information (default)
							// printOutput = 0				=> Do not print output information

	int	printSatSel;		// printSatSel = 1				=> Print satellite selection information
							// printSatSel = 0				=> Do not print satellite selection information (default)

	int	printSatDiff;		// printSatDiff = 1				=> Print satellite products difference in comparison mode (default)
							// printSatDiff = 0				=> Do not print satellite products difference in comparison mode

	int	printSatStat;		// printSatStat = 1				=> Print statistics for each satellite in comparison mode (default)
							// printSatStat = 0				=> Do not print statistics for each satellite in comparison mode

	int	printSatStatTot;	// printSatStatTot = 1			=> Print summary for all satellites in comparison mode (default)
							// printSatStatTot = 0			=> Do not print summary for all satellites in comparison mode

	int	printSatPvt;		// printSatPvt = 1				=> Print satellite info in show product mode (default)
							// printSatPvt = 0				=> Do not print satellite info in show product mode

	int	printV5format;		// printV5format = 0            => Print all messages in new format >=v6.0.0 (default)
							// printV5format = 1            => Print all messages in previous format <v6.0.0, before multiconstellation version

	double	ClktimeFactor;	// Factor for converting clock time unit. If option '-print:clkns' is set, this value is the conversion factor
							// from metres to nanoseconds. Otherwise, the value is 1 (default 1)
								
	//Prints for SBAS mode

	int	printSBASOUT;		// printSBASOUT = 1				=> Print global information related to the navigation solution computation
							//					   				(default in SBAS mode)
							// printSBASOUT = 0				=> Do not print global information related to the navigation solution computation
							//								   (default in non SBAS mode)

	int	printSBASCORR;		// printSBASCORR = 1			=> Print computed SBAS 1F corrections terms for each satellite
							// printSBASCORR = 0			=> Do not print computed SBAS 1F corrections terms for each satellite (default)

	int	printSBASVAR;		// printSBASVAR = 1				=> Print indiviudal variance contributions of each of the satellites used in the 
							//									   protection levels computation
							// printSBASVAR = 0				=> Do not print indiviudal variance contributions of each of the satellites used in the
							//					   					protection levels computation (default in SBAS mode)

	int	printSBASIONO;		// printSBASIONO = 1			=> Print detailed information of SBAS iono interpolation
							// printSBASIONO = 0			=> Do not print detailed information of SBAS iono interpolation (default in SBAS mode)
												   
	int	printSBASUNSEL;		// printSBASUNSEL = 1			=> Print info about why a satellite has been discarded for SBAS 1F
							// printSBASUNSEL = 0			=> Do not print info about why a satellite has been discarded (default in SBAS mode)

	int	printSBASDFMCCORR;	// printSBASDFMCCORR = 1		=> Print computed SBAS DFMC corrections terms for each satellite
							// printSBASDFMCCORR = 0		=> Do not print computed SBAS DFMC corrections terms for each satellite (default)

	int	printSBASDFMCVAR;	// printSBASDFMCVAR = 1			=> Print computed SBAS DFMC variance contributions for each satellite
							// printSBASDFMCVAR= 0			=> Do not print computed SBAS DFMC variance contributions for each satellite (default)

	int	printSBASDFMCUNSEL;	// printSBASDFMCUNSEL = 1		=> Print info about why a satellite has been discarded for SBAS DFMC
							// printSBASDFMCUNSEL = 0		=> Do not print info about why a satellite has been discarded (default in SBAS mode)

	int	printSBASUNUSED;	// printSBASUNUSED = 0			=> Do not print unused model computations discarded due to GEO switching (default)
							// printSBASUNUSED = 1			=> Print unused model computations discarded due to GEO switching

	int	printInBuffer;		// printInBuffer = 0			=> Print directly to stdout
							// printInBuffer = 1			=> Save prints to buffer
							// printInBuffer = 2			=> Empty buffers
							// printInBuffer = 3			=> Empty buffers, but put an * at the end of the first column (to indicate that it is an unused measurement)

	int	printUserError;		// printUserError = 0			=> Do not print user added error values
							// printUserError = 1			=> Print user added error values (default)

	int	printDGNSS;			// printDGNSS = 1    		 	=> Print global information related to the DGNSS (default)
							// printDGNSS = 0     			=> Do not print global information related to the DGNSS 

	int	printDGNSSUNUSED;	// printDGNSSUNSUED = 1    	 	=> Print global information related to the DGNSS for discarded epochs
							// printDGNSSUNUSED = 0     	=> Do not print global information related to the DGNSS for discarded epochs (default)

	int	printSummary;		// printSummary = 1				=> Print summary of the processing (default)
							// printSummary = 0				=> Do not print summary of the processing

	char ProgressEndCharac;	//Internal option for final character when printing progress

	enum	SatelliteVelocity satVel;		// satVel = svINERTIAL          => Print inertial velocities if satellites
											// satVel = svITRF              => Print ITRF (non-inertial) velocities of satellites 								

	// Processing and modeling options
	enum	WorkMode	    workMode;		// workMode = wmDOPROCESSING	=> Model and compute the navigation solution (default)
											// workMode = wmSHOWINPUT		=> Read and preprocess data only
											// workMode = wmCOMPAREORBITS	=> Compare two orbit files
											// workMode = wmSHOWPRODUCT	    => Read and compute satellite orbit from a product file
											// workMode = wmSBASPLOTS		=> Compute SBAS plots without doing navigation
											// workMode = wmUSERERROR2RINEX	=> Read RINEX Obs and create new RINEX with User added Error

	int	ConstellationUsed[MAX_GNSS];			//Internal flag to indicate if a constellation is used in a global basis (constellations available after applying options)

	int	numConstellationUsed;					//Number of constellations used in a global basis (constellations available after applying options)

	int	includeSatellite[MAX_GNSS][MAX_SATELLITES_PER_GNSS];	// Mask to select/deselect satellites, if =1 satellite selected, if =0 deselected (default, all selected)

	int	GLOsatFDMAdisabled[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS];	//GLONASS frequencies 1/2 forced to be disabled due to no frequency offset available

	int	defaultFreq[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS];		//Default frequencies to select for filling filter measurements

	int	availFreq[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS];		//Frequencies available per satellite (depending only satellite block type)

	int	usableFreq[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS];	
											// Mask to select/deselect frequencies, if =1 frequency selected, if =0 deselected (default, all selected)

	int	unselUnavailGNSSFreqCS[MAX_GNSS][MAX_FREQUENCIES_PER_GNSS];		
											// Flag to save which frequencies set by user for the CS where disabled due to they do not exist

	int	unselUnavailGNSSFreqFilter[MAX_GNSS][MAX_FREQUENCIES_PER_GNSS];		
											// Flag to save which frequencies set by user for the filter where disabled due to they do not exist

	enum	ReceiverPositionSrc	receiverPositionSource;			
												// receiverPositionSource = rpRINEX	=> Use the receiver position specified in the RINEX file for apriori position (default)
												// receiverPositionSource = rpSINEX 	=> Read the receiver position from the SINEX file
												// receiverPositionSource = rpSET		=> Specify the receiver apriori position (default)
												// receiverPositionSource = rpSETRef	=> Specify the receiver apriori position from reference file. A priori read from file will be used from modelling and for OUTPUT differential fields
												// receiverPositionSource = rpCALCULATE	=> Receiver position will be calculated, starting from (EARTH_SURFACE,0,0)
												// receiverPositionSource = rpCALCULATERINEX	=> Receiver position will be calculated, starting from RINEX file for apriori position
												// receiverPositionSource = rpCALCULATEUSER 	=> Receiver position will be calculated, starting from user defined coordinates
												// receiverPositionSource = rpCALCULATERef		=> Receiver position will be calculated, starting from (EARTH_SURFACE,0,0), but solution will be compared with coordinates from reference file
												// receiverPositionSource = rpCALCULATERINEXRef	=> Receiver position will be calculated, starting from RINEX file for apriori position, but solution will be compared with coordinates from reference file
												// receiverPositionSource = rpCALCULATEUSERRef 	=> Receiver position will be calculated, starting from user defined coordinates, but solution will be compared with coordinates from reference file
												// receiverPositionSource = rpRTCMbaseline 	=> (DGNSS) Receiver position will be calculated, solution will be compared with reference station coordinates
												// receiverPositionSource = rpRTCMRINEXROVER => (DGNSS) Receiver position will be calculated, solution will be compared with Rover Rinex a priori position
												// receiverPositionSource = rpRTCMRoverUSER => (DGNSS) Receiver position will be calculated, solution will be compared with user defined coordinates
												// receiverPositionSource = rpRTCMRoverUSERREF => (DGNSS) Receiver position will be calculated, solution will be compared with coordinates from reference file
												// receiverPositionSource = rpRTCMUserbaseline 	=> (DGNSS) Receiver position will be calculated, solution will be compared with reference station coordinates,
														//which are user defined
												// receiverPositionSource = rpRTCMUserRINEXROVER => (DGNSS) Receiver position will be calculated, solution will be compared with Rover Rinex a priori position.
														//Reference station coordinates are user defined coordinates
												// receiverPositionSource = rpRTCMRefRoverUSER => (DGNSS) Receiver position will be calculated, solution will be compared with user defined coordinates
														//Reference station coordinates are user defined coordinates
												// receiverPositionSource = rpRTCMRefUSERRoverREF => (DGNSS) Receiver position will be calculated, solution will be compared with coordinates from reference file

	double	aprioriReceiverPosition[3];		// 3D vector with the apriori position of the receiver in meters. This parameter is required when user provides receiver coordinates

	double	aprioriReceiverPositionGeod[3];	// 3D vector with the apriori position of the receiver in Lat/Lon/Height. This parameter is required when user provides receiver coordinates in geodesic form

	double	ReferenceStationPosition[3];	// 3D vector with the reference station position in meters. 
											//  This parameter is required when receiverPositionSource == RTCMUserbaseline, RTCMUserRinexRover, rpRTCMRefRoverUSER, rpRTCMRefUSERRoverREF

	double	ReferenceStationPositionGeod[3];	// 3D vector with the reference station position is given in geodetic coordinates

	int		UseReferenceFile;				// Internal variable to check if a reference position file has to be used 
											// 0 => Do not use reference file (default)
											// 1 => Use reference file

	enum	AntennaData	antennaData;		// antennaData = adNONE		=> Do not obtain nor use and receiver antenna information. For this mode, it is applied to all constellations and frequecies
											// antennaData = adSET		=> Specify the receiver antenna data (such as phase center). Only if all values are manually set.
											// antennaData = adANTEX	=> Try to read the characteristics of the antenna from the ANTEX file. This value will be set when any frequency is set to be read from ANTEX, even if some values are manually set

	enum	AntennaData	antennaDataGNSS[MAX_GNSS][MAX_FREQUENCIES_PER_GNSS];		// Same as antennaData but by constellation and frequency.
																					
	enum	AntennaData	antennaDataGNSSsource[MAX_GNSS][MAX_FREQUENCIES_PER_GNSS];	// Same as antennaDataGNSS but it will contain from which values do we have to copy data from
																					// When values are copied from other frequency/constellations, values are greater than 100
																					

	double	receiverPCO[MAX_GNSS][MAX_FREQUENCIES_PER_GNSS][3];	// 3D vector with the receiver antenna phase center [NEU] for each frequency. This parameter is required when antennaData == adSET

	int	strictradome;				// strictradome			=> When using ANTEX to correct the receiver phase center, this option will force a perfect
									//  match between the antenna name and radome reported in the receiver RINEX file and the ones in the ANTEX file. If this option
									//  is disabled (=0), and the radome is not found, the corrections will be used considering the radome "NONE" (default=0)


	enum	ARP	ARPData;			// ARPData = arpNONE		=> Do not apply any kind of Antenna Reference Point correction (default) 
									// ARPData = arpSET			=> Specify the ARP correction
									// ARPData = arpRINEX		=> Get the ARP from the RINEX header ('ANTENNA: DELTA H/E/N' field)

	double	receiverARP[3];			// 3D vector with the receiver Antenna Referece Point [NEU]. This parameter is required when ARPData == arpSET

	int	prealignCP;					// prealignCP = 1				=> Prealign carrier phase measurements with its corresponding pseudorange
									// prealignCP = 0				=> Take the carrier phase measurements "as is" without any kind of prealigment

	int	csLLI;						// csLLI = 1					=> Use the LLI detector
									// csLLI = 0					=> Do not use the LLI detector (default)

	int	csNcon;						// csNcon = 1					=> Use the N-consecutive
									// csNcon = 0					=> Do not use the N-consecutive (default)

	int	csNconAutoDisabled;			// csNconAutoDisabled = 0		=> Internal variable. N-consecutive was not automatically disabled while computing interval
									// csNconAutoDisabled = 1		=> Internal variable. N-consecutive was  automatically disabled while computing interval

	int	csNconMin;					// Number of epochs to be omitted (default 2)

	double	csDataGap;				// Data gap. Maximum period of time allowed (default 40)

	enum csDataGapSizeModes	csDataGapSizeMode;	// Internal variable to control how data gap has been set
												//		csDataGapSetMode = csDataGapSizeDefault		=> Data gap size set by default size (default mode)
												//		csDataGapSetMode = csDataGapSizeUser		=> Data gap size set by user
												//		csDataGapSetMode = csDataGapSizeAuto		=> Data gap automatically set to fit RINEX observation file interval

	int	csLI;						// csLI = 1					=> Use the geometric-free carrier-phase combination to detect cycle-slips (default)
									// csLI = 0					=> Do not use the geometric-free carrier-phase combination to detect cycle-slips

	double	csLImaxjump;			// Maximum jump threshold between two consecutive measured LI values (default 1)

	double	csLImax;				// Maximum threshold between estimated and measured LI values (default 0.08)

	double	csLIt;					// Time constant to set the threshold between maximum and minimum (default 60)

	int	csLIsamples;				// Minimum number of epochs needed to fit the second-degree polynomial for LI (default 7)

	double csLIThreshold;			// LI Threshold computed from LI parameters (options->csLIThreshold=options->csLImax/(1.0+exp(-options->csDataGap/options->csLIt)))

	int csLIenableOutlier;			// csLIenableOutlier = 0	=> Declare a CS when LI detects a cycle-slip (no outliers)
									// csLIenableOutlier = 1	=> Declare an outlier the fist time LI detects a cycle-slip, declare CS if next epoch LI also detects a cycle-slip (default)

	int	csMW;						// csMW = 1				=> Use the Melbourne-Wübbena combination to detect cycle-slips (default)
									// csMW = 0				=> Do not use the Melbourne-Wübbena combination to detect cycle-slips

	double	csMWInitStd;			// Initial Sigma for the Melbourne-Wübbena combination(default 2 metres)			

	double	csMWmin;				// Minimum threshold between estimated and measured MW values in relation to its standard deviation (default 0.8)

	int	csMWwindow;					// Number of seconds to compute the MW mean over the sliding window (default 300)

	double	csMWkfactor;			// Relation between estimated and measured MW values in relation to its standard deviation (default 5)

	int	csMWsamples;				// Minimum number of epochs needed to stabilize the sigma and mean in the MW cycle-slip detector (default 2)

	int csMWenableOutlier;			// csMWenableOutlier = 0	=> Declare a CS when MW detects a cycle-slip (no outliers)
									// csMWenableOutlier = 1	=> Declare an outlier the fist time MW detects a cycle-slip, declare CS if next epoch MW also detects a cycle-slip (default)

	int	csSF;						// csSF = 1				=> Use the Phase-Code difference to detect cycle-slips [mainly for single-frequency receivers]
									// csSF = 0				=> Do not use the Phase-Code difference to detect cycle-slips (default)

	int	csUnconsistencyCheck;		// csUnconsistencyCheck = 1		=> Use the unconsistency check in Phase-Code cycle-slips detector (default)
									// csUnconsistencyCheck = 0		=> Do not use the unconsistency check in Phase-Code cycle-slips detector

	double csUnconsistencyCheckThreshold;	// Threshold for SF Unconsistency check (default 20 metres)

	double	csSFkfactor;			// Relation between estimated and measured (Phase-Code) values in relation to its standard deviation (default 5)

	int	csSFwindow;					// Number of epochs to limit the SF ionosphere divergence using a sliding window (default 300)

	double  csSFinit;				// Initial standard deviation for the threshold calculation in the SF (default 3.0)

	int	csSFsamples;				// Minimum number of epochs needed to stabilize the sigma and mean in the SF cycle-slip detector (default 2)

	int	csIGF;						// csIGF = 0                    => Do not use triple frequency cycle-slip detector (default)
									// csIGF = 1                    => Use triple frequency cycle-slip detector

	int csIGFminNoise;				// csIGFminNoise = 0			=> Compute IGF using two LC combinations
	                    			// csIGFminNoise = 1			=> Compute IGF using the formula for minimum noise

	int	csIGFallowCodes;			// csIGFallowCodes = 0			=> Do not allow entering pseudoranges in manual IGF meas list (default)
	                    			// csIGFallowCodes = 1			=> Allow entering pseudoranges in manual IGF meas list

	double	csIGFmaxjump;			// Maximum jump threshold between two consecutive measured IGF values (default 1)

	double	csIGFmax;				// Maximum threshold between estimated and measured IGF values (default 0.08 with minimum noise or 2*0.08 with LC)

	double	csIGFt;					// Time constant to set the threshold between maximum and minimum (default 60)

	int	csIGFsamples;				// Minimum number of epochs needed to fit the second-degree polynomial for IGF (default 7)

	double csIGFThreshold;			// IGF Threshold computed from IGF parameters (options->csIGFThreshold=options->csIGFmax/(1.0+exp(-options->csDataGap/options->csIGFt)))

	int csIGFenableOutlier;			// csIGFenableOutlier = 0	=> Declare a CS when IGF detects a cycle-slip (no outliers)
									// csIGFenableOutlier = 1	=> Declare an outlier the fist time MW detects a cycle-slip, declare CS if next epoch IGF also detects a cycle-slip (default)

	int	autoFillcsSF;				// autoFillcsSF = 0				=> Do not auto fill measurements in cs SF
									// autoFillcsSF = 1             => Auto fill measurements in cs SF (default)

	int	autoFillcsMW;				// autoFillcsMW = 0				=> Do not auto fill measurements in cs MW
									// autoFillcsMW = 1             => Auto fill measurements in cs MW (default)

	int	autoFillcsLI;				// autoFillcsLI = 0				=> Do not auto fill measurements in cs LI
									// autoFillcsLI = 1             => Auto fill measurements in cs LI (default)

	int	autoFillcsIGF;				// autoFillcsIGF = 0			=> Do not auto fill measurements in cs IGF
									// autoFillcsIGF = 1            => Auto fill measurements in cs IGF (default)

	int	allCSDetectorsOff;			// Internal variable to check if all cycle-slip detectors are enabled or not 
									// 0 -> One or more cycle-slip detector enabled 
									// 1 -> All cycle-slip  detector disabled

	int	timeTrans;					// timeTrans = 1				=> Use transmission time for satellite positions (default)
									// timeTrans = 0				=> Use reception time for satellite positions

	int	earthRotation;				// earthRotation = 1			=> Correct the Earth rotation from travelTime (default 1)

	int	satellitePhaseCenter;		// satellitePhaseCenter = 1		=> Correct satellite phase centers in SP3 (default 1)

	int	satellitePhaseVar;			// 0 => Do not use zenital corrections for the antenna in the ANTEX file (default)
									// 1 => Use zenital corrections for the satellite in the ANTEX file

	int	receiverPhaseVar;			// 0 => Do not use zenital corrections for the antenna in the ANTEX file (default)
									// 1 => Use zenital corrections for the antenna in the ANTEX file, both azimut and non azimut corrections

	int	relativisticCorrection;		// relativisticCorrection = 1		=> Correct the relativisty effects on the signal (default 1)

	int	windUpCorrection;			// windUpCorrection = 1				=> Correct the windup from phase measurements (default 1)

	int	gravitationalCorrection;	// gravitationalCorrection = 1		=> Correct the gravitational delay from the general relativity (default 1) 

	int	solidTidesCorrection;		// solidTides = 1					=> Correct the solid tides effect (default 1)

	int	satelliteClockCorrection;	// satelliteClockCorrection = 1		=> Correct the satellite clock error from the clocks products file (default 1)

	int	troposphericCorrection;		// troposphericCorrection = 1		=> Correct the troposheric delay (default 1)

	enum	IonoModel   ionoModel;		// ionoModel = NoIono			=> Do not apply any ionospheric correction (default)
										// ionoModel = Klobuchar		=> Klobuchar standard model for ionospheric correction
										// ionoModel = NeQuick			=> NeQuick model for ionospheric correction
										// ionoModel = BeiDou			=> BeiDou model for ionospheric correction
										// ionoModel = IONEX			=> IONEX maps for ionospheric correction
										// ionoModel = FPPP				=> FPPP maps for ionospheric correction
										// ionoModel = SBASiono			=> SBAS ionospheric correction

	double	ionoRMS;					// Maximum error value for ionosphere model, only on FPPP (default 1)
	

	enum	TropModelNominal    tropNominal;	// tropNominal 					=> Tropospheric nominal computation
												// tropNominal = SimpleNominal	=> Simple tropospheric nominal correction
												// tropNominal = UNB3Nominal	=> UNB3 tropospheric nominal correction (default)
												// tropNominal = TropoGalileo	=> Galileo ESA tropospheric correction

	enum	TropModelMapping    tropMapping;	// tropMapping  				=> Tropospheric mapping
												// tropMapping = SimpleMapping	=> Simple tropospheric mapping 
												// tropMapping = NiellMapping	=> Niell tropospheric mapping (default)


	enum	GPSP1C1DCBModel   GPSp1c1DCBModel;		// GPSp1c1DCBModel = GPSp1c1NONE      => No correction of GPS C1-P1 DCBs, no identification of C1 and P1 (default)
													// GPSp1c1DCBModel = GPSp1c1FLEXIBLE  => No correction of GPS C1-P1 DCBs, identification of C1 and P1
													// GPSp1c1DCBModel = GPSp1c1STRICT    => Correction of GPS C1-P1 DCBs, identification of C1 and P1 obtained from precise DCB files

	enum	GenericDCBModel   GPSp1p2DCBModel;		// GPSp1p2DCBModel = DCBNONE   	   	=> No correction of GPS P1-P2 DCBs 
													// GPSp1p2DCBModel = DCBRINEX  	   	=> Correction of GPS P1-P2 DCBs, obtained from RINEX files 
													// GPSp1p2DCBModel = DCBFILE       	=> Correction of GPS P1-P2 DCBs, obtained from precise DCB files
													// GPSp1p2DCBModel = DCBSINEXDCB 	=> Correction of GPS P1-P2 DCBs, obtained from SINEX DCB files
													// GPSp1p2DCBModel = DCBIONEX    	=> Correction of GPS P1-P2 DCBs, obtained from IONEX files
													// GPSp1p2DCBModel = DCBFPPP  		=> Correction of GPS P1-P2 DCBs, obtained from FPPP files

	enum	GenericDCBModel   GPSISCl1caDCBModel;	// GPSISCl1caDCBModel = DCBNONE		=> No correction of GPS ISC L1 C/A DCBs 
													// GPSISCl1caDCBModel = DCBRINEX	=> Correction of GPS ISC L1 C/A DCBs, obtained from RINEX files (default)

	enum	GenericDCBModel   GPSISCl1cpDCBModel;	// GPSISCl1cpDCBModel = DCBNONE		=> No correction of GPS ISC l1cp DCBs 
													// GPSISCl1cpDCBModel = DCBRINEX	=> Correction of GPS ISC l1cp DCBs, obtained from RINEX files (default)

	enum	GenericDCBModel   GPSISCl1cdDCBModel;	// GPSISCl1cdDCBModel = DCBNONE		=> No correction of GPS ISC l1cd DCBs 
													// GPSISCl1cdDCBModel = DCBRINEX	=> Correction of GPS ISC l1cd DCBs, obtained from RINEX files (default)

	enum	GenericDCBModel   GPSISCl2cDCBModel;	// GPSISCl2cDCBModel = DCBNONE		=> No correction of GPS ISC l2c DCBs 
													// GPSISCl2cDCBModel = DCBRINEX		=> Correction of GPS ISC l2c DCBs, obtained from RINEX files (default)

	enum	GenericDCBModel   GPSISCl5i5DCBModel;	// GPSISCl5i5DCBModel = DCBNONE		=> No correction of GPS ISC l5i5 DCBs 
													// GPSISCl5i5DCBModel = DCBRINEX	=> Correction of GPS ISC l5i5 DCBs, obtained from RINEX files (default)

	enum	GenericDCBModel   GPSISCl5q5DCBModel;	// GPSISCl5q5DCBModel = DCBNONE		=> No correction of GPS ISC l5q5 DCBs 
													// GPSISCl5q5DCBModel = DCBRINEX	=> Correction of GPS ISC l5q5 DCBs, obtained from RINEX files (default)

	enum	GenericDCBModel   GLOp1p2DCBModel;		// GLOp1p2DCBModel = DCBNONE   	   	=> No correction of GLO P1-P2 DCBs 
													// GLOp1p2DCBModel = DCBRINEX  	   	=> Correction of GLO P1-P2 DCBs, obtained from RINEX files (only for versions >=3.05) 
													// GLOp1p2DCBModel = DCBIONEX  	   	=> Correction of GLO P1-P2 DCBs, obtained from IONEX files 

	enum	GenericDCBModel   GALe1e5aDCBModel;		// GALe1e5aDCBModel = DCBNONE		=> No correction of GAL E1-E5a DCBs 
													// GALe1e5aDCBModel = DCBRINEX		=> Correction of GAL E1-E5a DCBs, obtained from RINEX files 

	enum	GenericDCBModel   GALe1e5bDCBModel;		// GALe1e5bDCBModel = DCBNONE		=> No correction of GAL E1-E5b DCBs 
													// GALe1e5bDCBModel = DCBRINEX		=> Correction of GAL E1-E5b DCBs, obtained from RINEX files 

	enum	GenericDCBModel   BDSb2b6DCBModel;		// BDSb2b6DCBModel = DCBNONE		=> No correction of BDS B1_2-B3 DCBs 
													// BDSb2b6DCBModel = DCBRINEX		=> Correction of BDS B1_2-B3 DCBs, obtained from RINEX files 

	enum	GenericDCBModel   BDSb7b6DCBModel;		// BDSb7b6DCBModel = DCBNONE		=> No correction of BDS B2b-B3 DCBs 
													// BDSb7b6DCBModel = DCBRINEX		=> Correction of BDS B2b-B3 DCBs, obtained from RINEX files 

	enum	GenericDCBModel   BDSSP3DCBModel;		// BDSSP3DCBModel = DCBNONE			=> No correction of BDS SP3 single frequency DCBs 
													// BDSSP3DCBModel = DCBRINEX		=> Correction of BDS SP3 single frequency DCBs, obtained from RINEX files 

	enum	GenericDCBModel   BDSb1b6DCBModel;		// BDSb1b6DCBModel = DCBNONE		=> No correction of BDS B1-B3 DCBs 
													// BDSb1b6DCBModel = DCBRINEX		=> Correction of BDS B1-B3 DCBs, obtained from RINEX files 

	enum	GenericDCBModel   BDSb5b6DCBModel;		// BDSb5b6DCBModel = DCBNONE		=> No correction of BDS B2a-B3 DCBs 
													// BDSb5b6DCBModel = DCBRINEX		=> Correction of BDS B2a-B3 DCBs, obtained from RINEX files 

	enum	GenericDCBModel   BDSISCb1cdDCBModel;	// BDSISCb1cdDCBModel = DCBNONE		=> No correction of BDS ISC B1Cd DCBs 
													// BDSISCb1cdDCBModel = DCBRINEX	=> Correction of BDS ISC B1Cd DCBs, obtained from RINEX files (default)

	enum	GenericDCBModel   BDSISCb2adDCBModel;	// BDSISCb2adDCBModel = DCBNONE		=> No correction of BDS ISC B2ad DCBs 
													// BDSISCb2adDCBModel = DCBRINEX	=> Correction of BDS ISC B2ad DCBs, obtained from RINEX files (default)

	enum	GenericDCBModel   QZSc1cDCBModel;		// QZSc1cDCBModel = DCBNONE   	   	=> No correction of QZS C1C DCBs 
													// QZSc1cDCBModel = DCBRINEX  	   	=> Correction of QZS C1C DCBs, obtained from RINEX files 

	enum	GenericDCBModel   QZSISCl1cpDCBModel;	// QZSISCl1cpDCBModel = DCBNONE		=> No correction of QZS ISC l1cp DCBs 
													// QZSISCl1cpDCBModel = DCBRINEX	=> Correction of QZS ISC l1cp DCBs, obtained from RINEX files (default)

	enum	GenericDCBModel   QZSISCl1cdDCBModel;	// QZSISCl1cdDCBModel = DCBNONE		=> No correction of QZS ISC l1cd DCBs 
													// QZSISCl1cdDCBModel = DCBRINEX	=> Correction of QZS ISC l1cd DCBs, obtained from RINEX files (default)

	enum	GenericDCBModel   QZSISCl2cDCBModel;	// QZSISCl2cDCBModel = DCBNONE		=> No correction of QZS ISC l2c DCBs 
													// QZSISCl2cDCBModel = DCBRINEX		=> Correction of QZS ISC l2c DCBs, obtained from RINEX files (default)

	enum	GenericDCBModel   QZSISCl5i5DCBModel;	// QZSISCl5i5DCBModel = DCBNONE		=> No correction of QZS ISC l5i5 DCBs 
													// QZSISCl5i5DCBModel = DCBRINEX	=> Correction of QZS ISC l5i5 DCBs, obtained from RINEX files (default)

	enum	GenericDCBModel   QZSISCl5q5DCBModel;	// QZSISCl5q5DCBModel = DCBNONE		=> No correction of QZS ISC l5q5 DCBs 
													// QZSISCl5q5DCBModel = DCBRINEX	=> Correction of QZS ISC l5q5 DCBs, obtained from RINEX files (default)

	enum	GenericDCBModel   IRNc9c5DCBModel;		// IRNc9c5DCBModel = DCBNONE   	   	=> No correction of IRN C9-C5 DCBs 
													// IRNc9c5DCBModel = DCBRINEX  	   	=> Correction of IRN C9-C5 DCBs, obtained from RINEX files 

	enum OSBDCBModel	OSBdcbModel;			// OSBdcbModel = OSBNONE		=> No correction of differential code DCB biases (default in PPP)
												// OSBdcbModel = OSBRINEX		=> Correction of differential code DCB biases from RINEX files (default in SPP)
												// OSBdcbModel = OSBSINEXBIAS	=> Correction of differential code DCB biases from SINEX Bias files (observation-specific biases)
	
	enum DSBDCBModel	DSBdcbModel;			// DSBdcbModel = DSBNONE		=> No conversion of measurements (default)
												// DSBdcbModel = DSBSINEXBIAS	=> Conversion of measurements using SINEX BIAS (differential biases)

	enum GenericDCBModel	DualFreqDCBModel[MAX_GNSS];	// DualFreqDCBModel = DCBNONE		=> No correction for dual frequency DCBs
														// DualFreqDCBModel = DCBRINEX		=> Correction for dual frequency DCBs

	enum GenericDCBModel	FPPPDCBModel;	// Generic DCB for all frequencies and constellations. It will apply to the same measurements to be used in Fast-PPP
											// This DCB is internal and enabled automatically when Fast-PPP is enabled
											// FPPPDCBModel = DCBNONE		=> FPPP not enabled, normal DCBs used
											// FPPPDCBModel = DCBIONEX		=> DCBs for F-PPP read from IONEX header

	double	decimate;					//	Decimate the data to this interval (decimate = 0 do not decimate, default = 0)

    int integerRINEXObsSeconds;         // integerRINEXObsSeconds = 0   => Use decimals when reading the epoch timestamp in a RINEX observation file (default)
                                        // integerRINEXObsSeconds = 1   => Ignore decimals when reading the epoch timestamp in a RINEX observation file

	enum CombTypeAutoSelectionTypes CombTypeAutoSelection;	//Sets the measurement selection to use (single or dual frequency) when the user does not set any measurement

															//CombTypeAutoSelection = CombTypeAutoSelectionAutomatic  => Use default selection (single frequency for SPP, 
															//                                                           dual frequency for PPP) (default)
															//CombTypeAutoSelection = CombTypeAutoSelectionSingleFreq => Select single frequency combination in SPP and PPP 
															//CombTypeAutoSelection = CombTypeAutoSelectionDualFreq   => Select dual frequency combination in SPP and PPP

	
	int	numAutoMeasSatByUser;									//Number of satellites the user has set for automatic measurement selection with option '-filter:select'
	
	int	autoMeasSatByUser[MAX_GNSS][MAX_SATELLITES_PER_GNSS];	//To indicate if user has set a satellite for automatic measurement selection with option '-filter:select'

	int smoothAuto;						// 0 => Automatic smoothing selection disabled (default) 
										// 1 => Automatic smoothing selection enabled 


	int	numAutoMeasSmoothSatByUser;										//Number of satellites the user has set for automatic smoothing measurement selection with option '-pre:smoothmeas'
	
	int	autoMeasSmoothSatByUser[MAX_GNSS][MAX_SATELLITES_PER_GNSS];		//To indicate if user has set a satellite for automatic smoothingmeasurement selection with option '-pre:smoothmeas'

	int	smoothEpochs;					// Value to limit the memory of the smoothing (default: 0, which means no smoothing)

	int	orbitInterpolationDegree;		// Orbit interpolation degree for precise products (default 10)

	int	clockInterpolationDegree;		// Clock interpolation degree for precise products (default 1 - linear interpolation)

	enum BRDCHealthSelModes satHealthMode;	// BRDCUseHealthyOnly		=> Use only broadcast messages with healthy status (default)
											// BRDCUseHealthyMarginal	=> Use only broadcast messages with healthy and marginal
											// BRDCUseAnyHealth			=> Use  broadcast messages with any health status


	int	brdcHealthSkip[MAX_HEALTH_TYPES];	// Defines which broadcast messages will be skipped (i.e. not saved in buffer when read from navigation file)
											// This option is useful if you want to use the healthy message as much as possible even though un unhealthy flag was sent
											// A value of 1 means that message with the given health type is skipped, 0 for saving it. Default is all used (0,0,0)


	int	brdcBlockTransTime;				// brdcBlockTransTime = 1		=> Check broadcast block transmission time is before or equal to current time (default)
										// brdcBlockTransTime = 0       => Do not check broadcast block transmission time is before or equal to current time 

	double	MaxURABroadcast;			// Discard threshold for satellites when their URA (in metres) is (in the navigation message) is equal or greater than this value

	double	GLOintStep;					// Runge-Kutta interpolation step (in seconds) for computing GLONASS orbit with broadcast products (default 30)

	int	ModelAllMeas;					// ModelAllMeas = 0 	=> Only model measurements used in the filter (default)
										// ModelAllMeas = 1		=> Model all measurements available in rover RINEX observation file

	int	ForcedNoModelAllMeas;			// ForcedNoModelAllMeas = 0 => gLAB didn't force to disable option ModelAllMeas (parameter 'model:allfilemeas')
										// ForcedNoModelAllMeas = 1	=> gLAB forced to disable option ModelAllMeas (only occurs in SBAS and DGNSS modes)	

	// Filtering options
	int	totalFilterMeasurements;		// Maximum number of filter measurements per satellite in all satellite list

	int	maxDopplerMeasurements;			// Maximum number of doppler measurements per satellite in all satellite list

	enum	SNRWeightComb	SNRweightComb[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT]; // Vector containing how to get the SNR when a weight with SNR is used

	enum	WeightMode weightMode[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT];	// Vector containing the type of weight applied to each satellite and measurement

	double	WeightConstantsValues[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT][3];	// Vector containing the constants to compute the weights of the measurements

	double	SNRweightCombVal[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT][4]; //  Vector containing the factors for combining the SNR

	int	minArcLength;			// Minimum arc length to get the measure in the smoother, the cycle-slip detector and in the filter

	int	deprecatedMode;			// 0 => User is not running the ESA Book Vol II (default)
								// 1 => User is running the ESA Book Vol II

	double	maxdr2;				// Max distance (squared) from initial approximate position to estimated position (default 10000)

	int	CoordRandWalk;			// CoordRandWalk = 0 => Do not estimate user coordinates as a random walk (default)
	                  			// CoordRandWalk = 1 => Estimate user coordinates as a random walk

	int	ClkRandWalk;			// ClkRandWalk = 0 => Do not estimate receiver clock as a random walk (default)
	                			// ClkRandWalk = 1 => Estimate receiver clock as a random walk

	int	ISCBRandWalk;			// ISCBRandWalk = 0 => Do not estimate inter-system bias clock as a random walk (default)
	                 			// ISCBRandWalk = 1 => Estimate inter-system bias clock as a random walk

	int	IonoRandWalk;			// IonoRandWalk = 0 => Do not estimate ionosphere as a random walk (default in uncombined PPP)
	                			// IonoRandWalk = 1 => Estimate ionosphere as a random walk (default in Fast-PPP)

	int	SatDCBRandWalk;			// SatDCBRandWalk = 0 => Do not estimate satellite DCBs as a random walk (default in uncombined PPP)
	                			// SatDCBRandWalk = 1 => Estimate satellite DCBs as a random walk (default in Fast-PPP)

	int	RecDCBRandWalk;			// RecDCBRandWalk = 0 => Do not estimate receiver DCBs as a random walk (default in uncombined PPP)
	                			// RecDCBRandWalk = 1 => Estimate receiver DCBs as a random walk (default in Fast-PPP)

	int	estimateTroposphere;	// estimateTroposphere = 0	=> Do not estimate the troposphere in the filter (default in SPP/SBAS/DGNSS)
	                        	// estimateTroposphere = 1	=> Estimate the troposphere in the filter (default in PPP)

	int	estimateRecWindUp;		// estimateRecWindUp = 0	=> Do not estimate the receiver wind up in the filter (default)		//To be implemented
	                      		// estimateRecWindUp = 1	=> Estimate the receiver wind up in the filter						//To be implemented

	int estimateIono;			// estimateIono = 0	=> Do not estimate the ionosphere in the filter (default in SPP/PPP/SBAS/DGNSS)
	                 			// estimateIono = 1	=> Estimate the ionosphere in the filter (default in Fast-PPP)

	int estimateSatDCB;			// estimateSatDCB = 0	=> Do not estimate the satellite DCB in the filter (default in SPP/PPP/SBAS/DGNSS)
	                   			// estimateSatDCB = 1	=> Estimate the satellite DCB in the filter (default in Fast-PPP)

	int estimateRecDCB;			// estimateRecDCB = 0	=> Do not estimate the receiver DCB in the filter (default in SPP/PPP/SBAS/DGNSS)
	                      		// estimateRecDCB = 1	=> Estimate the receiver DCB in the filter (default in Fast-PPP)

	int estimateAnyDCB;			// Internal variable	estimateAnyDCB = 0	=> Options estimateSatDCB and estimateRecDCB are both disabled (default in SPP/PPP/SBAS/DGNSS)
	                      		// 						estimateAnyDCB = 1	=> One or both of the options estimateSatDCB or estimateRecDCB are enabled (default in Fast-PPP)

	int estimateGLOIFB;			// estimateGLOIFB = 0	=> Do not estimate the GLONASS Inter Frequency Bias in the filter (default)	//To be implemented
	                   			// estimateGLOIFB = 1	=> Estimate the GLONASS Inter Frequency Bias in the filter					//To be implemented

	int	useSigmaIono;			// useSigmaIono = 0		=> Do not use ionosphere Sigma values in filter when using IONEX or FPPP model
	                 			// useSigmaIono = 1		=> Use ionosphere Sigma values in filter when using IONEX or Fast-PPP ionosphere model (default)

	int	usePhase;				// Internal check. 	usePhase = 0 No carrier phase used in the filter (carrier phases used for smoothing are not accounted) (default in SPP/SBAS/DGNSS)
	             				// 					usePhase = 1 Any carrier phase is used in the filter (carrier phases used for smoothing are not accounted) (default in PPP/Fast-PPP)

	int	estimateAmbiguities;	// estimateAmbiguities = 0 => Do not estimate ambiguities for carrier phase measurements or no carrier phases used.
								//								If carrier phases are used in the filter (not for smoothing), then it is supposed that carrier phases are absolute
	                         	// estimateAmbiguities = 1 => Estimate ambiguities for carrier phase measurements (default when carrier phases are used in the filter)

	int	FastPPP;				// FastPPP = 0 	=> Fast-PPP mode disabled (default)
								// FastPPP = 1 	=> Fast-PPP mode enabled. Enabling this mode will enable estimateIono, estimateSatDCB and estimateRecDCB


	int	UncombinedPPP;			// UncombinedPPP = 0 => No PPP or classical PPP using iono-free measurements (default)
								// UncombinedPPP = 1 => Classical PPP using uncombined measurements

	int	filterIterations;		// This will set the number of forward/backward runs in the filter, being 1 only forward, 2 forward+backward (default 1)

	double	filterParams[3][MAX_PAR];	// filterParams stores the data of the Kalman filter. The first dimension is the parameter type of the
										// filter, the second is the specific unknown it is refering to:
										// To access the first dimension: PHI_PAR, Q_PAR and P0_PAR
										// Phi is the propagation of the uknown between epochs
										// Q is the process noise included in the propagation
										// P0 is the initial standard deviation of the parameter
										// To access the second dimension: DR_UNK, DT_UNK, TROP_UNK and BIAS_UNK
										// DR: Position unknowns
										// DT: Receiver clock unknown
										// DT_IS: Inter-system clock bias unknown (for each constellation)
										// IONO: Ionosphere unknown
										// SAT_DCB:  Satellite DCB Unknown
										// REC_DCB:  Receiver DCB Unknown
										// IFB:  GLONASS Inter-Frequency bias unknown
										// WUP:  Receiver wind-up unknown
										// TROP: Troposphere estimation unknown (if it is estimated)
										// BIAS: Carrierphase ambiguities (if carrierphase is used)
										// Default values are as follows:
										// PHI_DR:      1 [static/random walk positioning]      0 [kinematic positioning]
										// PHI_DT:      1 [random walk positioning]             0 [static/kinematic]
										// PHI_DT_IS:   1 [random walk positioning]             0 [static/kinematic]
										// PHI_TROP: 1	
										// PHI_IONO: 1     
										// PHI_SAT_DCB:  1  
										// PHI_REC_DCB:  1   
										// PHI_IFB:  1      //To be implemented
										// PHI_WUP:  1      //To be implemented
										// PHI_BIAS: 1
										// Q_DR:     0 [static positioning]   <variation per second> [random walk positioning]    inf [kinematic positioning]
										// Q_DT:     inf [static/[static/kinematic positioning]  <variation per second> [random walk positioning]
										// Q_DT_IS:  inf [static/[static/kinematic positioning]  <variation per second> [random walk positioning]
										// Q_TROP:   1e-4   (This value is the variation per hour)
										// Q_IONO: 1    
										// Q_SAT_DCB:  1    
										// Q_REC_DCB:  1    
										// Q_IFB:  1      //To be implemented
										// Q_WUP:  1      //To be implemented
										// Q_BIAS:   0
										// P0_DR:    inf
										// P0_DT:    inf
										// P0_DT_IS: inf
										// P0_TROP:  0.5^2
										// P0_IONO: 1    
										// P0_SAT_DCB:  1 
										// P0_REC_DCB:  1 
										// P0_IFB:  1      //To be implemented
										// P0_WUP:  1      //To be implemented
										// P0_BIAS:  20^2

	double	elevationMask;			// elevationMask => Satellites below this elevation mask (in radians) will be discarded (default 5º)

	int	discardEclipsedSatellites;	// discardEclipsedSatellites = 1	=> Discard satellites under Earth eclipes (default in PPP)	
									// discardEclipsedSatellites = 0	=> Do NOT discard satellites under Earth eclipes (default in SPP/SBAS/DGNSS)

	int	maxKalmanIterations;		// Maximum iterations of the filter trying to converge to a solution

	int	concatenSP3;				// 0 => There is no concatenated SP3 files (default)
									// 1 => There is concatenated SP3 files

	int numPreciseFiles;			// Number of precise files (default = 0)

	int	NextSP3;					// Internal variable, it is evaluated on each read of SP3 file
									// NextSP3 = 1	=> Take into account next products for compute the 10th-degree polynomial
									// NextSP3 = 0	=> Do NOT take into account next products due to the lack of them (default)

	int	LastSamplePrevDayOrb;		// When an SP3 is concatenated and the last epoch of previous day is the same as the first epoch of the current day and both samples are valid:
									// This typically occurs with the epoch at 0 hours 0 minutes 0 seconds
									// 0 => Use orbit sample of the current day (default)
									// 1 => Use orbit sample of the previous day

	int	LastSamplePrevDayClk;		// When an SP3 or CLK is concatenated and the last epoch of previous day is the same as the first epoch of the current day and both samples are valid:
									// This typically occurs with the epoch at 0 hours 0 minutes 0 seconds
									// 0 => Use clock sample of the current day (default)
									// 1 => Use clock sample of the previous day

	int		OrbitsMaxGaps;			// Maximum data gaps between samples in SP3 files used for orbit interpolation (default 8)
									// If 0 is set, then do not check data gaps

	int		ClocksMaxGaps;			// Maximum data gaps between samples used for clock interpolation (default 2)
									// If 0 is set, then do not check data gaps

	int		OrbitsToTMaxGaps;		// Maximum data gaps in all samples in SP3 files used for orbit interpolation (default 16)
									// If 0 is set, then do not check data gaps

	int		ClocksToTMaxGaps;		// Maximum data gaps between samples used for clock interpolation (default 4)
									// If 0 is set, then do not check data gaps

	double	OrbitsMaxDistance;		// Maximum time between samples in SP3 files used for orbit interpolation (to protect against data gaps) (default 7200 seconds)
									// If 0 is set, then do not check time

	double	ClocksMaxDistance;		// Maximum time between samples in precise clock files used for clock interpolation (to protect against data gaps) (default 1800 seconds)
									// If 0 is set, then do not check time

	double	OrbitsToTMaxDistance;	// Maximum time between first and last sample in SP3 files used for orbit interpolation (to protect against data gaps) (in seconds)
									// If 0 is set, then do not check time

	double	ClocksToTMaxDistance;	// Maximum time between first and last sample in precise clock files used for clock interpolation (to protect against data gaps) (in seconds)
									// If 0 is set, then do not check time

	int	SNRfilter;					// 0 => User has not defined a minimum or maximum SNR for any satellite and measurement
									// 1 => User has defined a minimum or maximum SNR for any satellite and measurement

	int	SNRminfilter;				// 0 => User has not defined a minimum SNR for any satellite and measurement
									// 1 => User has defined a minimum SNR for any satellite and measurement

	int	SNRmaxfilter;				// 0 => User has not defined a maximum SNR for any satellite and measurement
									// 1 => User has defined a maximum SNR for any satellite and measurement

	enum SNRCheckType SNRchecktype;	//Internal variable for selecting which SNR are being checked

	double	SNRminvalues[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_MEASUREMENTS_NO_COMBINATIONS];	//Minimum SNR values given by user

	double	SNRmaxvalues[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_MEASUREMENTS_NO_COMBINATIONS];	//Maximum SNR values given by user


	int	useraddednoise;				// 0 => User has not given a file with noise signals to be added to raw measurements
									// 1 => User has given a file with noise signals to be added to raw measurements

	int	useraddednoisepreprocess;	// 0 => Add user defined error immediately after reading the observation file
									// 1 => Add user defined error after preprocessing data

	int	checkPhaseCodeJumps;		// 0 => Do not check for pseudorange jumps in measurements
									// 1 => Check for pseudorange jumps in measurements (default)

	int	GDOPthreshold;		// 0 => Disables the GDOP threshold (default in SPP and SBAS)
							// 1 => Enables the GDOP threshold (default in PPP and DGNSS)

	int	HDOPthreshold;		// 0 => Disables the HDOP threshold (default in all modes except maritime SBAS)
							// 1 => Enables the HDOP threshold (default in maritime SBAS)

	int	PDOPthreshold;		// 0 => Disables the PDOP threshold (default in all modes except maritime SBAS)
							// 1 => Enables the PDOP threshold (default in maritime SBAS)

	int HDOPorPDOP;			// 0 => If both HDOP and PDOP filters are enabled, a valid epoch will have to fulfill both (default in all modes except maritime SBAS)
							// 1 => If both HDOP and PDOP filters are enabled, a valid epoch will have to fulfill only one of them (default in maritime SBAS)

	enum SBASPlotsDOP SBASplotsDOP;	// Enumerator for knowing in SBAS plots mode if HDOP, PDOP or GDOP need to be computed

	double	maxGDOP;		// Maximum GDOP allowed (default 30.0)

	double	maxHDOP;		// Maximum HDOP allowed (default 4)

	double	maxPDOP;		// Maximum PDOP allowed (default 6)

	int	computeVelocity;	// 0 -> Do not compute rover velocity (default)
							// 1 -> Compute rover velocity

	int	numClkRefPriorityList;						//Number of constellations reference clock list

	enum GNSSystem	ClkRefPriorityList[MAX_GNSS];	//Priority list for selecting the GNSS system used as the reference clock 

	int AllowChangeReferenceGNSSClk;		// 0 => If constellation with reference clock is not available, do not change to another constellation reference clock
											// 1 => If constellation with reference clock is not available, change to another constellation reference clock (default)

	//Options for the selection of the reference iono-free combinantion measurements
	enum MeasurementType IFRefMeas[MAX_GNSS][2];								//Measurements used in the ionosphere free combination to compute precise orbits and clocks for each constellation

	enum MeasurementType IFRefMeasUsed[MAX_GNSS][MAX_SATELLITES_PER_GNSS][2];	//Measurements used in the ionosphere free combination to compute precise orbits and clocks for each constellation and satellite
																				//In uncombined mode, the reference measurements may change if the measurememts in IFRefMeas are not available

	int	IFRefMeasFreq[MAX_GNSS][2];												//Frequencies of the measurements in "options->IFRefMeas" option
													
	int	IFRefMeasFreqUsed[MAX_GNSS][MAX_SATELLITES_PER_GNSS][2];				//Frequencies of the measurements in "options->IFRefMeas" for each constellation and satellite
																				//In uncombined mode, the reference frequencies may change if the measurememts in IFRefMeas are not available
													
	int	IFRefMeasPos[MAX_GNSS][MAX_SATELLITES_PER_GNSS][2];						//Position of each reference measurement in "options->filterMeasList" array per satellite

	//Options for Broadcast type selection
	int BrdcTypeSel[MAX_GNSS];	/*GPS*/		// PreferGPSLNAV    => Use LNAV, CNAV and CNAV2 navigation messages, but prefer LNAV (default)
											// PreferGPSCNAV    => Use LNAV, CNAV and CNAV2 navigation messages, but prefer CNAV
											// PreferGPSCNAV2   => Use LNAV, CNAV and CNAV2 navigation messages, but prefer CNAV2
											// GPSLNAVOnly      => Use only LNAV navigation messages
											// GPSCNAVOnly      => Use only CNAV navigation messages
											// GPSCNAV2Only     => Use only CNAV2 navigation messages
											// GPSAnyCNAVOnly   => Use only CNAV and CNAV2 navigation messages
											// GPSUserDefined   => User defined messages order and messages type to use
											// GPSLNAVvsCNAV    => For comparison mode only. Use only LNAV on first file and CNAV on second file
											// GPSCNAVvsLNAV    => For comparison mode only. Use only CNAV on first file and LNAV on second file
											// GPSLNAVvsCNAV2   => For comparison mode only. Use only LNAV on first file and CNAV2 on second file
											// GPSCNAV2vsLNAV   => For comparison mode only. Use only CNAV2 on first file and LNAV on second file
											// GPSCNAVvsCNAV2   => For comparison mode only. Use only CNAV on first file and CNAV2 on second file
											// GPSCNAV2vsCNAV   => For comparison mode only. Use only CNAV2 on first file and CNAV on second file

							/*Galileo*/		// PreferGalINAV    => Use INAV, FNAV, CNAV and GNAV broadcast messages, but use INAV whenever possible (default)
											// PreferGalFNAV    => Use INAV, FNAV, CNAV and GNAV broadcast messages, but use FNAV whenever possible
											// PreferGalCNAV    => Use INAV, FNAV, CNAV and GNAV broadcast messages, but use CNAV whenever possible
											// PreferGalGNAV    => Use INAV, FNAV, CNAV and GNAV broadcast messages, but use GNAV whenever possible
											// GalINAVOnly      => Use only INAV navigation messages (INAV with E1 and E5b, INAV only with E1 or INAV with E5b)
											// GalINAVE1Only    => Use only INAV navigation messages (with information only on E1)
											// GalINAVE5bOnly   => Use only INAV navigation messages (with information only on E5b)
											// GalINAVE1E5bOnly => Use only INAV navigation messages (with information only on E1 and E5b)
											// GalFNAVOnly      => Use only FNAV navigation messages
											// GalCNAVOnly      => Use only CNAV navigation messages
											// GalGNAVOnly      => Use only GNAV navigation messages
											// GalUserDefined   => User defined messages order and messages type to use
											// GalINAVvsFNAV    => For comparison mode only. Use only INAV on first file and FNAV on second file
											// GalFNAVvsINAV    => For comparison mode only. Use only FNAV on first file and INAV on second file
	                                        // GalINAVvsCNAV    => For comparison mode only. Use only INAV on first file and CNAV on second file  
	                                        // GalCNAVvsINAV    => For comparison mode only. Use only CNAV on first file and INAV on second file 
	                                        // GalINAVvsGNAV    => For comparison mode only. Use only INAV on first file and GNAV on second file
	                                        // GalGNAVvsINAV    => For comparison mode only. Use only GNAV on first file and INAV on second file 
	                                        // GalFNAVvsCNAV    => For comparison mode only. Use only FNAV on first file and CNAV on second file 
	                                        // GalCNAVvsFNAV    => For comparison mode only. Use only CNAV on first file and FNAV on second file 
	                                        // GalFNAVvsGNAV    => For comparison mode only. Use only FNAV on first file and GNAV on second file 
	                                        // GalGNAVvsFNAV    => For comparison mode only. Use only GNAV on first file and FNAV on second file 
	                                        // GalCNAVvsGNAV    => For comparison mode only. Use only CNAV on first file and GNAV on second file 
	                                        // GalGNAVvsCNAV    => For comparison mode only. Use only GNAV on first file and CNAV on second file 

							/*GLONASS*/		// PreferGLOFDMA    => Use FDMA and CDMA navigation messages, but prefer FDMA
											// PreferGLOCDMA    => Use CDMA and FDMA navigation messages, but prefer CDMA
											// GLOFDMAOnly      => Use only FDMA navigation messages (default)
											// GLOCDMAOnly      => Use only CDMA navigation messages
											// GLOUserDefined   => User defined messages order and messages type to use
											// GLOFDMAvsCDMA    => For comparison mode only. Use only FDMA on first file and CDMA on second file
											// GLOCDMAvsFDMA    => For comparison mode only. Use only CDMA on first file and FDMA on second file

						 	 /*BeiDou*/		// PreferBDSD1 		=> Use D1, CNAV1 and CNAV2 navigation messages, but prefer D1
						 	            	// PreferBDSCNAV1   => Use D1, CNAV1 and CNAV2 navigation messages, but prefer CNAV1
											// PreferBDSCNAV2   => Use D1, CNAV1 and CNAV2 navigation messages, but prefer CNAV2
											// BDSD1Only     	=> Use only D1 navigation messages (default)
											// BDSCNAV1Only     => Use only CNAV1 navigation messages
											// BDSCNAV2Only     => Use only CNAV2 navigation messages
											// BDSUserDefined   => User defined messages order and messages type to use
											// BDSD1vsCNAV1 	=> For comparison mode only. Use only D1 on first file and CNAV1 on second file
											// BDSCNAV1vsD1  	=> For comparison mode only. Use only CNAV1 on first file and D1 on second file
											// BDSD1vsCNAV2 	=> For comparison mode only. Use only D1 on first file and CNAV2 on second file
											// BDSCNAV2vsD1  	=> For comparison mode only. Use only CNAV2 on first file and D1 on second file
											// BDSCNAV1vsCNAV2  => For comparison mode only. Use only CNAV1 on first file and CNAV2 on second file
											// BDSCNAV2vsCNAV1  => For comparison mode only. Use only CNAV2 on first file and CNAV1 on second file

							   /*QZSS*/		// PreferQZSLNAV    => Use LNAV, CNAV and CNAV2 navigation messages, but prefer LNAV
											// PreferQZSCNAV    => Use LNAV, CNAV and CNAV2 navigation messages, but prefer CNAV
											// PreferQZSCNAV2   => Use LNAV, CNAV and CNAV2 navigation messages, but prefer CNAV2
											// QZSLNAVOnly      => Use only LNAV navigation messages (default)
											// QZSCNAVOnly      => Use only CNAV navigation messages
											// QZSCNAV2Only     => Use only CNAV2 navigation messages
											// QZSAnyCNAVOnly   => Use only CNAV and CNAV2 navigation messages
											// QZSUserDefined   => User defined messages order and messages type to use
											// QZSLNAVvsCNAV    => For comparison mode only. Use only LNAV on first file and CNAV on second file
											// QZSCNAVvsLNAV    => For comparison mode only. Use only CNAV on first file and LNAV on second file
											// QZSLNAVvsCNAV2   => For comparison mode only. Use only LNAV on first file and CNAV2 on second file
											// QZSCNAV2vsLNAV   => For comparison mode only. Use only CNAV2 on first file and LNAV on second file
											// QZSCNAVvsCNAV2   => For comparison mode only. Use only CNAV on first file and CNAV2 on second file
											// QZSCNAV2vsCNAV   => For comparison mode only. Use only CNAV2 on first file and CNAV on second file

								/*GEO*/		// GEOCNAVOnly      => Use only CNAV navigation messages		
											// GEOUserDefined   => User defined messages order and messages type to use

							  /*IRNSS*/		// IRNCNAVOnly      => Use only CNAV navigation messages		
											// IRNUserDefined   => User defined messages order and messages type to use

	int BRDCSelOrder[MAX_GNSS][MAX_BRDC_SELECTION_TYPES][MAX_BRDC_TYPES+1];		//Order for selecting Broadcast messages types set by user
																				//The +1 is due to to the last position will save the number of types set

	int BRDCAvailSelOrder[MAXNAVSOURCES][MAX_GNSS][MAX_BRDC_SELECTION_TYPES][MAX_BRDC_TYPES+1];	
												//Order for selecting Broadcast messages types (for each source type, for orbits, TGD or health)
												//after filtering by the available messages types in the navigation data


	double maxBRDCFreshTimeDiffToc;			//Maximum difference (in seconds) with respect to ToC to consider a valid message to select. If it is greater, gLAB will check for the
											//next navigation message type in the priority list (default 3600 seconds)


	// Options for measurement management
	int	DiscardUnpairedMeas[NUM_OBSRINEX];	// Do not use measurements that the code and phase pair measurements (C1C-L1C,C1W-L1W) are not both available
											// This option only has effect when auto selecting measurements to use
											// This option only has effect in RINEX 3, as RINEX 2 is not paired in measurements (for instance C1,P1,L1)
											// If file is a RINEX 2, this option will automatically be disabled
											// 0 -> Code and phase measurements not paired can be used (default)
											// 1 -> Code and phase measurements not paired will be discarded

	int	ForcedDiscardUnpairedMeas[NUM_OBSRINEX];	//Internal variable to indicate if DiscardUnpairedMeas was forced to off due to RINEX 2 file read

	int	SatBlockMeasDiscard;				// 1 -> ANTEX file is available and user has not disabled to autoremove measurements according to satellite block (default)
											// 0 -> ANTEX not available or user disabled autoremove measurements according to satellite block

	enum MeasurementType MeasOrder[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS][MEASTYPELISTS][MAX_MEAS_TYPES_PER_FREQUENCY];		
											//Order of measurements (code and phase) to be used after applying user order (or the default order if not set by user)
	enum MeasurementType MeasAvailOrder[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS][MEASTYPELISTS][MAX_MEAS_TYPES_PER_FREQUENCY]; 	
											//Available measurements (code and phase) with the order from 'MeasOrder' variable after reading RINEX observation header

	enum MeasurementType MeasNotAvailSatBlock[MAX_SATELLITES_BLOCK][MAX_FREQUENCIES_PER_GNSS][MEASTYPELISTS][MAX_MEAS_TYPES_PER_FREQUENCY];
											//List of not available measurements depending on the satellite block.
											//This list is manually hardcoded in order to take out from MeasAvailOrder priority list measurements that are in RINEX observation
											//header file but are not available to all satellites blocks or satellite generations (e.g. L5/L2C/L1C measurements in GPS)

	//Number of measurements available for each frequency, with the same type or with others of different type)
	int	numMeasOrder[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS][MEASTYPELISTS];
	int	numMeasAvailOrder[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS][MEASTYPELISTS];
	int numMeasNotAvailSatBlock[MAX_SATELLITES_BLOCK][MAX_FREQUENCIES_PER_GNSS][MEASTYPELISTS];


	//Frequencies available per each satellite (depending on the block type)
	int	FreqAvailSatBlock[MAX_SATELLITES_BLOCK][MAX_FREQUENCIES_PER_GNSS]; //List of frequencies available for each satellite block
	

	//The next variables the list of paired measurements to be passed to each cycle-slip detector. 
	enum MeasurementType csSFMeasList[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST][2]; //The '2' is for the two measurements to combine 
																							//(First the code and then phase)
	enum MeasurementType csMWMeasList[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST][7]; //For MW you need to specify how to do PN and LW combinations 
											//(MW combination + PN combination + two codes + LW combination + two phases)
	enum MeasurementType csLIMeasList[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST][3]; //The '3' is for the LI combiantion + two measurements to combine
	enum MeasurementType csIGFMeasList[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST][7]; //The IGF you need to specify how to do two LC combinations
											//(IGF combination + LC combination + two phases + LC combination + two phases)  

	//Frequencies of the measurements provided by the user for the CS detectors
	int	csSFMeasFreq[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST][2]; //The '2' is for the two measurements to combine
	int	csMWMeasFreq[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST][4]; //For MW you need to specify how to do PN and LW combinations (4 measurements)
	int	csLIMeasFreq[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST][2]; //The '2' is for the two measurements to combine
	int	csIGFMeasFreq[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST][4]; //The '4' is for the two dual-frequency measurements 

	//Number of paired measurements for each cycle-slip detector
	int	numcsSFMeasList[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int	numcsMWMeasList[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int	numcsLIMeasList[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int	numcsIGFMeasList[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS];

	//Flag to indicate if measurements are provided by the user or to be automatically set
	int csSFWithMeas[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST];
	int csMWWithMeas[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST];
	int csLIWithMeas[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST];
	int csIGFWithMeas[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST];

	//Flag to indicate if measurements have already been set
	int	csSFMeasSelected[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST];
	int	csMWMeasSelected[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST];
	int	csLIMeasSelected[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST];
	int	csIGFMeasSelected[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST];


	//Number of frequencies (or frequency combinations) where cycle-slip detectors have to run. 
	//Setting this values will make gLAB run the cycle-slip detector with the selected frequencies or combination of frequencies 
	int	csSFfreq[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS]; 	//One frequency, check if the frequency is used
	int	csMWfreq[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST][2];				//Two frequencies, check if these pair of frequencies is used
	int	csLIfreq[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST][2];				//Two frequencies, check if these pair of frequencies is used
	int	csIGFfreq[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST][4];			//Three/four frequencies, check if these two pair of frequencies are used

	//Number of frequencies for each cycle-slip detector
	int	numcsSFfreq[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int	numcsMWfreq[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int	numcsLIfreq[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int	numcsIGFfreq[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS];

	//Frequencies of carrier phases used in the filter not detected or automatically added in each cycle-slip detector
	//The '2' is for unchecked frequencies or automatically added frequencies
	int	csSFfreqAutoChecked[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS][2];
	int	csMWfreqAutoChecked[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS][2];
	int	csLIfreqAutoChecked[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS][2];
	int	csIGFfreqAutoChecked[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FREQUENCIES_PER_GNSS][2];

	//Buffers for measurements in text format for faster prints
	char	csSFMeasText[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST][MAX_MEAS_PRINT_LENGTH];
	char	csMWMeasText[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST][MAX_MEAS_PRINT_LENGTH];
	char	csLIMeasText[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST][MAX_MEAS_PRINT_LENGTH];
	char	csIGFMeasText[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_CS_LIST][MAX_MEAS_PRINT_LENGTH];


	//Measurements to be passed to the filter
	enum 	MeasurementType filterMeasList[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT][5];	
									//List of measurements to the filter. 
									//The 5 is because there may be up to 4 measurements to be set (plus the combination name itself)
	enum 	MeasurementType filterSmoothMeasList[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT][5];	
									//List of measurements to smooth measurements to the filter.

	char					filterMeasText[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT][MAX_MEAS_PRINT_LENGTH];
									//List of measurements in text format for printing in PREFIT and POSTFIT

	char					filterSmoothMeasText[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT][MAX_MEAS_PRINT_LENGTH];
									//List of smooth measurements in text format for printing in PREFIT and POSTFIT

	int						filterMeasfreq[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT][4]; 
									//List of frequencies per measurement	

	int						numfilterMeasList[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS]; 					
									//Number of measurements per satellite passed to the filter (selected or not)
	int						numfilterMeasSelected[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS];
									//Number of measurements per satellite selected
	int						numfilterCarrierPhaseMeas[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS]; 
									//Number of carrier phase measurements per satellite passed to the filter (to account for the number of ambiguities)
	int						numCombfilterMeas[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT]; 
									//Number of measurements each filter combination has
	int						filterListWithMeas[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT]; 	
									//To indicate if measurements are set by user (0->not set 1->set)
	int						filterListMeasSelected[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT]; 
									//To indicate if filter measurements have been selected
	int						filterListAllMeasSelected[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT]; 
									//To indicate if filter and smoothing measurements have been selected

	int						filterSmoothAutoMeasType[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT];
									//To indicate if automatic selection of how to smoooth is selected
	int						filterSmoothMeasfreq[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT][4]; 
									//List of frequency per smoothing measurement	
	int						filterSmoothListWithMeas[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT]; 	
									//To indicate if smooth measurements are set (0->not set 1->set)
	int						numCombfilterSmoothMeas[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT]; 
									//Number of measurements each smoothing combination has
	int						filterMeasSmoothed[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT]; 
									//Indicates if a measurement is smoothed (0->no smoothing 1->smoothed)
	int						filterSmoothListMeasSelected[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT]; 
									//To indicate if smoothed measurements have been selected

	int						numfilterMeasWithSmoothing[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS];
									//Number of measurements in the filter that have smoothing set
	int						filterIndListWithSmoothing[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT];
									//List of positions in list of measurements that have smoothing set	

	enum	MeasurementKind	filterMeasKind[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT];	
									//To check if measurement is pseudorange or carrier phase
	enum	FilterMeasType	filterMeasTypeList[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT];
									//Type of measurement in the filter (combination, smoothed,...)

	int						C1CfilterMeasPos[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS];	//Position of C1C measurement in filter measurement list (for Step Detector)

	int						filterMeasFreqMissng[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
									//Flag to indicate if any of the measurements in the filter cannot be used due to missing frequencies number (GLONASS only)
									//When this flag is enabled, the satellite will not be used

	//Doppler measurements for computing speed. They are separated from the filter measurement, as
	//speed may be computed or not, they are not smoothed and do not need a covariance matrix
	enum 	MeasurementType DopplerMeasList[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT][5];	
									//List of measurements for the speed computation. 
									//The 5 is because there may be up to 4 measurements to be set (plus the combination name itself)
	int						DopplerMeasfreq[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT][4]; 
									//List of frequencies per measurement	
	int						numDopplerMeasList[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS]; 					
									//Number of measurements per satellite passed to the speed computation
	int						numCombDopplerMeas[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT]; 
									//Number of measurements each doppler combination has
	int						DopplerListWithMeas[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT]; 	
									//To indicate if doppler measurements are set by user (0->not set 1->set)
	int						DopplerListMeasSelected[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT]; 
									//To indicate if doppler measurements have been selected
	enum	FilterMeasType	DopplerMeasTypeList[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS_SAT];
									//Type of measurement for the Doppler (single measurement or combination)

	enum 	GNSSClockSource	GNSSclockSource[MAX_GNSS][MAX_GNSS];

	double					GNSSclockValue[MAX_GNSS][MAX_GNSS];	//Inter system bias read in RINEX or set by user (in metres)

	//To indicate if a satellite has all its measurements been selected
	int		MeasSelected[NUM_OBSRINEX][MAX_GNSS][MAX_SATELLITES_PER_GNSS];	
	
	//Options for Converting SBAS files

	int	writeRinexBfile;			// 0 => Do not write a RINEX B file with SBAS data (default) 
									// 1 => Write a RINEX B file with SBAS data

	int	writeEMSfile;				// 0 => Do not write an SBAS EMS file with SBAS data (default) 
									// 1 => Write an SBAS EMS file with SBAS data
	
	int	writePegasusfile;			// 0 => Do not write a Pegasus file with SBAS data (default)
									// 1 => Write a Pegasus file with SBAS data

	int	onlyconvertSBAS;			// 0 => Do file conversion for SBAS messages and data processing (default)
									// 1 => Only do file conversion for SBAS messages

	int pegasuspurerinex;			// 0 => Write Rinex Navigation v2.11 for SBAS compliant with pegasus (default)
									// 1 => Write Rinex Navigation v2.11 for SBAS compliant with RINEX standard 

	int	pegasusaligned;				// 0 => Write Pegasus files without aligning data columns (default)
									// 1 => Write Pegasus files aligning data columns

	char	pegasusfs;				    //Field separator for pegasus files. By default a space " ", but can also be semicolon ";"

	char	sbasdir[MAX_INPUT_LINE];    //Folder where to write the converted SBAS files (by default "SBAS")

	//Options for SBAS processing

	int	autoDisabledSmoothed;			// In SBAS and DGNSS modes, if user inputs a RINEX observation file which is not at 1Hz or greater, if user did not set any smoothing options.
										//  gLAB will autodisable smoothing, smoothing convergence and single frequency cycle-slip detectors in order to be able to compute a solution properly

										// autoDisabledSmoothedSBAS = 0 	=> gLAB has not auto disabled smoothing, smoothing convergence and cycle-slip detectors in SBAS and DGNSS (default)
										// autoDisabledSmoothedSBAS = 1     => gLAB has disabled smoothing, smoothing convergence and cycle-slip detectors in SBAS and DGNSS	

	enum SBASdataModes	SBAScorrections;	//	SBAScorrections = NoSBASdata 		=> No SBAS data is used (default)
											//	SBAScorrections = SBASionoOnly 		=> Use SBAS data only for ionosphere corrections
											//	SBAScorrections = SBAS1Fused 		=> Compute SBAS 1 frequency solution 
											//	SBAScorrections = SBASDFMCused		=> Compute SBAS DFMC solution
											//	SBAScorrections = SBASMaps1freqUsed	=> Compute SBAS 1F availability maps
											//	SBAScorrections = SBASMapsDFMCUsed	=> Compute SBAS DFMC availability maps

	int	SBASmodePos;					// SBASmodePos = SBAS1FMODEPOS 		=> SBAS 1F (default)
	            						// SBASmodePos = SBASDFMCMODEPOS 	=> SBAS DFMC

	int SBASConstUsed[MAX_SAT_GEO][NUMSBASMODEPOS][MAX_GNSS]; 	//Flag to check which constellations per GEO are used by SBAS 1F and SBAS DFMC (default GPS only in SBAS 1F and GPS+Galileo in SBAS DFMC)
																//The slots for GEO in first dimension are set in the same order as in SBASdata structure (0 for mixed GEO, 1 for first GEO read, ...)

	enum GNSSystem SBASConstList[MAX_SAT_GEO][NUMSBASMODEPOS][MAX_GNSS]; //List of constellations monitored per each GEO in SBAS 1F and SBAS DFMC (default GPS only in SBAS 1F and GPS+Galileo in SBAS DFMC)
																		//The slots for GEO in first dimension are set in the same order as in SBASdata structure (0 for mixed GEO, 1 for first GEO read, ...)

	int numSBASConstList[MAX_SAT_GEO][NUMSBASMODEPOS];	//Number of constellations monitored per each GEO in SBAS 1F and SBAS DFMC (default 1 in SBAS 1F and 2 in SBAS DFMC)
														//The slots for GEO in first dimension are set in the same order as in SBASdata structure (0 for mixed GEO, 1 for first GEO read, ...)

	double	SBASmsgFlightTime;			// SBAS message flight time (default 0.12 seconds)

	double	SBASmsg1MinusFlightTime;	// SBAS message duration (1 second) minus flight time (options->SBASmsgFlightTime) (default 0.88)

	double	SBASmsg1PlusFlightTime;		// SBAS message duration (1 second) plus flight time (options->SBASmsgFlightTime) (default 1.12)

	int	SBASFreqPosToProcess;			// Frequency position to process. If the message read in EMS or RINEX-B is not from this frequency position,
										//   don't check for missing messages or save its data

	int	usetype0messages;				//0 => Ignore any alarm messages (type 0). Setting this value will leave option useAlarmmessageForCorrections with no effect
										//1 => Read alarm messages (type 0) (default).

	int	useAlarmmessageForCorrections;	//0 => Alarm messages (type 0) are treated as they are (default)
										//1 => Alarm messages (type 0) are treated as fast correction message type 2 for SBAS 1F and types 34,35,36 for SBAS DFMC
	
	int	precisionapproach;				//0 => Non-precision approach mode
										//1 => Precision approach mode (default)

	int	UserForcedNPA;					//0 => User has not forced NPA mode
										//1 => User has forced NPA mode

	int	switchmode;						//0 => Mode switching disabled (default)
										//1 => Mode switching enabled

	int	switchGEO;						//0 => GEO switching disabled (default)
										//1 => GEO switching enabled 

	int	selectBestGEO;					//0 => Get SBAS solution with the first GEO that provides a solution (default)
										//1 => Compute protection levels for all GEOs and select the one with lowest protection levels

	int	excludeSmoothingConvergence;	// Number of seconds (in continuous operation) in the smoothing in order to reach steady-state operation.
										// If the value is greater than 0, then. the satellite will not be used in the solution computation until
										// this number of seconds with continuous smoothing is reached. 
										// For non SBAS processing, default value is 0 (no convergence time)
										// For SBAS processing, default is 360 seconds.

	int	GEOfallback;					// 0 => Switch back to the first GEO used (default)
										// 1 => Do not switch back to the first GEO used

	int	MaintainGEO;					// 0 => gLAB will try to fallback to previous GEO
										// 1 => Maintain current GEO while possible independently from how it was selected (default)			

	int	adquisitiontime;				// Time (in seconds) for gathering data from a GEO (default 300 seconds)

	int	minimumswitchtime;				// Minimum time (in seconds) that have to pass before another GEO or mode change

	int	GEOPRN;							// 0 => Use data from all available GEO (default in non precision approach)
										// 1 => Use the GEO PRN from the first line of SBAS data read (default in precision approach)
										// 2 => Use the GEO PRN with highest elevation available when the first almanac data is read
										// MINGEOPRN<=GEOPRN<=MAXGEOPRN Use the given PRN
										// Once a GEO is selected, ot contains the GEO selected

	int GEOPRNSelected;					// To indicate if a GEO PRN has been selected. It will have the same initial value as GEOPRN
										// variable until a GEO is definitively selected, in whose case the value will be 2*MAXGEOPRN
										// (this value is not allowed as user defined value). In the case where the a priori position
										// is set to calculate, GEO selection with highest elevation must be done on several epochs
										// until the solution converges

	int	GEOindex;						// Indicates which GEO to be used in the SBAS structure vector.
										// 0  => 0 is the first position which has data from all GEO satellites 
										// >0 => The position with data only from one GEO satellite (default)

	int	GEOPRNunsel[MAX_SBAS_PRN];		//Stores the PRN of the GEO unselected for SBAS processing

	int	mixedGEOdata;					// -1/0 	=> Use of mixed GEO data is disabled (default)
										// 1    	=> Use of mixed GEO data is enabled 

	int	noMixedGEOdata;					// This option is the complementary of mixedGEOdata, to avoid having to do "1-mixedGEOdata" each time function readRinexObsEpoch is called
										// 1		=> Use of mixed GEO data is disabled (default)
										// 0    	=> Use of mixed GEO data is enabled 

	int	initcoordNPA;					// 0   	=> First epochs Klobuchar will not be used in PA if receiver coordinates is set to calculate
										// 1   	=> First epochs Klobuchar will be used in PA if receiver coordinates is set to calculate (default)

	int UDREIthreshold;					// Maximum UDREI threshold. Satellites with UDREI equal or higher than the threshold will be discarded (default 999999)

	double SigmaOffsetNoMT10;			// Offset to be applied when computing the sigma flt when Message type 10 is not available or disabled (default 8)

	int	airborneReceiverType;			// 0 => User defined. Sigma multipath values is given by the user
										// 1,2,3,4 => Type 1,2,3,4 receiver (default 2)

	int	stepdetector;					// 0 => Step detector disabled (default)
										// 1 => Step detector enabled

	int SBASmaritime;					// 0 => User has not provided SBAS maritime option (default)
										// 1 => User has provided SBAS maritime option

	int	prefitOutlierDetectorAbs;		// 0 => Absolute values prefit outlier detector disabled (default)
										// 1 => Absolute values prefit outlier enabled

	int	prefitOutlierDetectorMedian;	// 0 => Median prefit outlier detector disabled (default)
										// 1 => Median prefit outlier enabled

	double prefitOutlierDetectorAbsThreshold;		//Threshold for absolute prefit outlier detector

	double prefitOutlierDetectorMedianThreshold;	//Threshold for median prefit outlier detector

	int	usertmout[2][64];				// Stores the user time out values for SBAS messages (in seconds)

	int	FCtmout[2];						// Stores the user time out values for fast correction for SBAS messages (in seconds)

	int	RRCtmout[2];					// Stores the user time out values for range rate correction for SBAS messages (in seconds)

	int	usersigmamultipath;				// 0 => Use SBAS sigma multipath model (default)
										// 1 => Use user sigma multipath model given in file

	double	sigma2multipath[3];			// Stores parameters a,b,c for sigma multipath, being sigma=a+b*e^(-satelevation/c). Values saved in meters

	double	sigma2noise;				// Stores the user fixed value given for sigma noise. If value is -1, no value was given. Value saved in meters^2

	double	sigma2divergence;			// Stores the user fixed value given for sigma divergence. If value is -1, no value was given. Value saved in meters^2

	double	kfactor[2][2];				// K factor used when computing protection levels. First dimension is for mode (PA/NPA) and second dimension is for axis component

	int	stanfordesa;					// 0 => Do not compute values for stanford-esa plot (default)
										// 1 => Compute values for stanford-esa plot

	int stanfordesaLOI;					// 0 => Do not write LOIs over threshold to file when computing Stanford-ESA plot
										// 1 => Write LOIs over threshold to file when computing Stanford-ESA plot (default)

	int	stanfordesaMaxNumSat;			// Maximum number of satellites to be used in Stanford-ESA combination (default 999999 or all combinations selected) 
										// This thresholds makes Stanford-ESA skip combinations with many satellites, which are not of interest

	double	WIRHorThreshold;			// Horizontal Integrity Ratio threshold for writing in file information of the Stanford-ESA iteration (default 0.7)

	double	WIRVerThreshold;			// Vertical Integrity Ratio threshold for writing in file information of the Stanford-ESA iteration (default 0.7)

	int noRRCwith1PRC;                  // 0 => With only one PRC received, do not use the satellite as RRC cannot be computed (default)
                                        // 1 => With only one PRC received, set RRC and its degradation term to 0 and use the satellite

	//Options for SBAS DFMC

	int	useAnyMeasSBASDFMC;				// 0 => Do not use different measurement than C1C-L1C, C5Q,L5Q in SBAS DFMC (default)
										// 1 => Use any measurement different than C1C-L1C, C5Q,L5Q in SBAS DFMC if these are not available

	int	SBASDFMCuseGPSL2;				// 0 => Use SBAS DFMC corrections using GPS L1 and L5 frequencies  (default)
										// 1 => Use SBAS DFMC corrections using GPS L1 and L2 frequencies

	int	SBASDFMCMT37version;			// MT37V044 => When receiving a MT37 SBAS DFMC message, decode it using MOPS DFMC version <=0.4.4
										// MT37V1   => When receiving a MT37 SBAS DFMC message, decode it using MOPS DFMC version >=0.5	(default)

	int	SBASDFMCMT3940version;			// MT3940V044 => When receiving a MT39 or MT40 SBAS DFMC message, decode it using MOPS DFMC version <=0.4.4
										// MT3940V1   => When receiving a MT39 or MT40 SBAS DFMC message, decode it using MOPS DFMC version >=0.5 (default)	

	int	SBASDFMCMT42version;			// MT42V071 => When receiving a MT42 SBAS DFMC message, decode it using MOPS DFMC version <=0.7.1
										// MT42V1   => When receiving a MT42 SBAS DFMC message, decode it using MOPS DFMC version >=0.8 (default)

	int	SBASDFMCMT47version;			// MT47V044 => When receiving a MT42 SBAS DFMC message, decode it using MOPS DFMC version <=0.4.4
										// MT47V1   => When receiving a MT42 SBAS DFMC message, decode it using MOPS DFMC version >=0.5	(default)

	//Options for manually setting parameters. User may set a value of zero to disable a correction or sigma, but the conditions to apply 
	//the correction or sigma will have to be met

	double	SBASDFMCcer;				// If value is set by the user (not -1), use this Cer instead of the one transmitted in MT37 (in metres)

	double	SBASDFMCccovariance;		// If value is set by the user (not -1), use this Ccovariance instead of the one transmitted in MT37 (unitless)

	double	SBASDFMCicorr[MAX_GNSS];	// If value is set by the user (not -1), use this Icorr instead of the one transmitted in MT37 (in seconds)

	double	SBASDFMCccorr[MAX_GNSS];	// If value is set by the user (not -1), use this Ccorr instead of the one transmitted in MT37 (in metres)

	double	SBASDFMCrcorr[MAX_GNSS];	// If value is set by the user (not -1), use this Rcorr instead of the one transmitted in MT37 (in metres/second)

	double 	SBASDFMCdfreiTable[15];		// If value is set by the user (not -1), use this value for DFREI instead of the ones transmitted in MT37 (in metres)

	double	SBASDFMCdeltaRcorr;			// If value is set by the user (not -1), use this DeltaRcorr instead of the one transmitted in MT32 or MT39/40 (unitless)

	double	SBASDFMCdeltaDFRE;			// If value is set by the user (not -1), use this DeltaDFRE instead of computing it from covariance parameters transmitted in MT32 or MT39/40 (unitless)

	double	SBASDFMCsigmauire;			// If value is set by the user (not -1), use this value for the sigma of the iono resiudal error instead of the MOPS formula (in metres)

	double	SBASDFMCsigmatropo;			// If value is set by the user (not -1), use this value for the sigma of the tropo instead of the MOPS formula (in metres)

	double	SBASDFMCsigmaMultipathFactor;	//Conversion factor to convert the sigma multipath in one frequency to the dual frequency (default 2.59 metres)

	int 	DFREIthreshold;				// Maximum DFREI threshold. Satellites with DFREI equal or higher than the threshold will be discarded (default 999999)

	//Options for disabling SBAS corrections
	//Note that disabling corrections sets corrections to zero, but still has to meet the necessary conditions according to navigation model!
	//When disabling any correction, the result is equivalent as if the SBAS message gave a correction value equal to zero
	int	NoFastCorrection;				// 0 => Apply SBAS message fast correction value (default)
										// 1 => Set SBAS fast correction value to 0

	int	NoRRCCorrection;				// 0 => Apply SBAS RRC correction value (default)
										// 1 => Set SBAS RRC correction value to 0

	int	NoSlowCorrection;				// 0 => Apply SBAS Slow correction values (default)
										// 1 => Set SBAS Slow correction values to 0

	int	NoIonoCorrection;				// 0 => Apply SBAS Iono correction value (default)
										// 1 => Set SBAS Iono correction value to 0

	int	NoDeltaUDRE;					// 0 => Apply SBAS Delta UDRE value (default)
										// 1 => Set SBAS Delta UDRE value to 1 (1 is the neutral value for Delta UDRE)

	int	NoFastSigma;					// 0 => Apply SBAS message fast correction sigmas (default)
										// 1 => Set SBAS fast correction sigmas (UDREsigma, fast and RRC degradation) 0

	int	NoRRCSigma;						// 0 => Apply SBAS message RRC degradation sigma (default)
										// 1 => Set SBAS RRC degradation sigma 0

	int	NoFastDeg;						// 0 => Apply SBAS message fast degradation sigma (default)
										// 1 => Set SBAS fast degradation sigma 0

	int	NoSlowSigma;					// 0 => Apply SBAS message slow correction sigma (default)
										// 1 => Set SBAS slow correction sigmas (long term and geo navigation degradation sigma) to 0

	int	NoIonoSigma;					// 0 => Apply SBAS Iono sigma (default)
										// 1 => Set SBAS Iono sigma value to 0

	int	NoTropoSigma;					// 0 => Apply SBAS Tropo sigma (default)
										// 1 => Set SBAS Tropo sigma value to 0

	int	NoEnRouteSigma;					// 0 => Apply SBAS en route degradation sigma [NPA only] (default)
										// 1 => Set SBAS En Route degradation sigma [NPA only] to 0

	int NoMT10;							// 0 => Use MT10 SBAS message (degradation parameters)
										// 1 => Do not use MT10 SBAS message

	//Options for summary

	TTime firstEpochSummary;			//First epoch to use in the summary

	double	percentile;					//Percentile value for computing the error percentile (default 95)

	int recPosProvided;					//Flag to indicate if receiver position (from rover) is given (either fixed or with a reference file)

	char StationNetworkName[MAX_STATION_NAME];	//Station name for last line of summary

	int	waitForNextDay;					// If a file starts at the end of a day (at HOURSPREVDAYCONVERGENCE or later), wait until the next day to start computing summary and Stanford-ESA data
										// 0 => Do not wait for next day
										// 1 => Wait for next day (default)

	int	useDatasummary;					// This flag controls when using data is enabled or not (controlled by gLAB)
										// 0 => Do not use current epoch for computing Stanford-ESA and summary
										// 1 => Use current epoch for computing Stanford-ESA and summary

	int	computeConvergenceTime;			// This flag controls if convergence time has to be computed (only in PPP if summary is enabled) or 
										//  still the computation is active. (flag controlled by gLAB)
										// 0 => Do not compute convergence time (not necessary or already computed)
										// 1 => Compute convergence time

	int	computeConvTimeFormalErrHor;		// Compute convergence time using Horizontal formal error (can be used regardless there is reference position or not). Flag controlled by gLAB
											// 0 => Do not compute convergence time using Horizontal formal error (not necessary or already computed)
											// 1 => Compute convergence time using Horizontal formal error

	int	computeConvTimeFormalErrVer;		// Compute convergence time using Vertical formal error (can be used regardless there is reference position or not). Flag controlled by gLAB
											// 0 => Do not compute convergence time using Vertical formal error (not necessary or already computed)
											// 1 => Compute convergence time using Vertical formal error

	int	computeConvTimeFormalErr3D;			// Compute convergence time using 3D formal error (can be used regardless there is reference position or not). Flag controlled by gLAB
											// 0 => Do not compute convergence time using 3D formal error (not necessary or already computed)
											// 1 => Compute convergence time using 3D formal error

	int	computeConvTimePosErrHor;			// Compute convergence time using Horizontal positioning error (only available if reference position is available). Flag controlled by gLAB
											// 0 => Do not compute convergence time using Horizontal positioning error (not necessary or already computed)
											// 1 => Compute convergence time using Horizontal positioning error

	int	computeConvTimePosErrVer;			// Compute convergence time using Vertical positioning error (only available if reference position is available). Flag controlled by gLAB
											// 0 => Do not compute convergence time using Vertical positioning error (not necessary or already computed)
											// 1 => Compute convergence time using Vertical positioning error

	int	computeConvTimePosErr3D;			// Compute convergence time using 3D positioning error (only available if reference position is available). Flag controlled by gLAB
											// 0 => Do not compute convergence time using 3D positioning error (not necessary or already computed)
											// 1 => Compute convergence time using 3D positioning error

	int computeConvTimePeriodFormalErrHor;	// Compute convergence time using Horizontal formal error and the converged criteria has to keep minTimeConvergedFormalErr 
											//  seconds (can be used regardless there is reference position or not). Flag controlled by gLAB
											// 0 => Do not compute convergence time using Horizontal formal error (not necessary or already computed)
											// 1 => Compute convergence time using Horizontal formal error

	int computeConvTimePeriodFormalErrVer;	// Compute convergence time using Vertical formal error and the converged criteria has to keep minTimeConvergedFormalErr 
											//  seconds (can be used regardless there is reference position or not). Flag controlled by gLAB
											// 0 => Do not compute convergence time using Vertical formal error (not necessary or already computed)
											// 1 => Compute convergence time using Vertical formal error

	int computeConvTimePeriodFormalErr3D;	// Compute convergence time using 3D formal error and the converged criteria has to keep minTimeConvergedFormalErr 
											//  seconds (can be used regardless there is reference position or not). Flag controlled by gLAB
											// 0 => Do not compute convergence time using 3D formal error (not necessary or already computed)
											// 1 => Compute convergence time using 3D formal error

	int computeConvTimePeriodPosErrHor;		// Compute convergence time using Horizontal positioning error and the converged criteria has to keep minTimeConvergedPosErr 
											//  seconds (only available if reference position is available). Flag controlled by gLAB
											// 0 => Do not compute convergence time using Horizontal positioning error (not necessary or already computed)
											// 1 => Compute convergence time using Horizontal positioning error

	int computeConvTimePeriodPosErrVer;		// Compute convergence time using Vertical positioning error and the converged criteria has to keep minTimeConvergedPosErr 
											//  seconds (only available if reference position is available). Flag controlled by gLAB
											// 0 => Do not compute convergence time using Vertical positioning error (not necessary or already computed)
											// 1 => Compute convergence time using Vertical positioning error

	int computeConvTimePeriodPosErr3D;		// Compute convergence time using 3D positioning error and the converged criteria has to keep minTimeConvergedPosErr 
											//  seconds (only available if reference position is available). Flag controlled by gLAB
											// 0 => Do not compute convergence time using 3D positioning error (not necessary or already computed)
											// 1 => Compute convergence time using 3D positioning error

	double	formalErrorThresholdHor;		// Threshold for the horizontal position formal error (filter correlation) to consider the filter converged (in metres, default 0.2 metres)

	double	formalErrorThresholdVer;		// Threshold for the vertical position formal error (filter correlation) to consider the filter converged (in metres, default 0.4 metres)

	double	formalErrorThreshold3D;			// Threshold for the 3D position formal error (filter correlation) to consider the filter converged (in metres, default 0.4	metres)

	double	positionErrorThresholdHor;		// Threshold for the horizontal position error (using reference position) to consider the filter converged (in metres, default 0.2 metres)

	double	positionErrorThresholdVer;		// Threshold for the vertical position error (using reference position) to consider the filter converged (in metres, default 0.4 metres)

	double	positionErrorThreshold3D;		// Threshold for the 3D position error (using reference position) to consider the filter converged (in metres, default 0.4 metres)

	double	minTimeConvergedFormalErrHor;	// Minimum continous time that the horizontal position formal error has to be below the threshold to consider the filter converged (in seconds, default 300 seconds)

	double	minTimeConvergedFormalErrVer;	// Minimum continous time that the vertical position formal error has to be below the threshold to consider the filter converged (in seconds, default 300 seconds)

	double	minTimeConvergedFormalErr3D;	// Minimum continous time that the 3D position formal error has to be below the threshold to consider the filter converged (in seconds, default 300 seconds)

	double	minTimeConvergedPosErrHor;		// Minimum continous time that the horizontal position error has to be below the threshold to consider the filter converged (in seconds, default 300 seconds)

	double	minTimeConvergedPosErrVer;		// Minimum continous time that the vertical position error has to be below the threshold to consider the filter converged (in seconds, default 300 seconds)

	double	minTimeConvergedPosErr3D;		// Minimum continous time that the 3D position error has to be below the threshold to consider the filter converged (in seconds, default 300 seconds)


	//Options for SBAS plots mode
	int		SBASHourlyMaps;			//If enabled, print also hourly SBAS availability maps
	int		ContRiskWindowSize;		//Size of the sliding window for the continuity risk (default 15 epochs for aviation, 900 for maritime)
	int		ContRiskWindowSizeMar;	//Size of the sliding window for the continuity risk Maritime (default 15 epochs for aviation, 900 for maritime)
	int		NoAvailabilityPlot;		//Do not compute Availability and Continuity Risk plots
	int		NoContRiskPlot;			//Do not compute Continuity Risk plot
	int		NoContRiskMarPlot;		//Do not compute Continuity Risk Maritime plot
	int		ComputeRiskPlots;		//Internal variable to set if Continuity Risk plots are computed
	int		NoIonoPlot;				//Do not compute Ionosphere correction availability plot
	int		HDOPPlot;				//Do HDOP plot (default off)
	int		PDOPPlot;				//Do PDOP plot (default off)
	int		GDOPPlot;				//Do GDOP plot (default off)
	int		CombinedDOPPlot;		//Do combined DOP plot (default off)
	int		DOPPercentile;			//Compute DOP percentile (default off)
	int		AvailPlotTimeStep;		//Time step for availability and continuity plot (default 1)
	int		IonoPlotTimeStep;		//Time step for ionosphere plot (default 300)
	int		UseGEOsatsAvailsMaps;	//Use GEO SBAS satellites when computing availability maps
	double	AvailPlotTimeStepDec;	//Time step for availability and continuity plot in decimal (default 1.0)
	double	AvailPlotTimeStepCmp;	//Time step for availability and continuity plot in decimal plus 0.1 to avoid problems with decimals (default 1.1)
	double	minLatplots;        	//Minimum latitude when generating SBAS plots (default  25º)
	double	maxLatplots;       		//Maximum latitude when generating SBAS plots (default  75º)
	double	minLonplots;    	    //Minimum longitude when generating SBAS plots (default -30º)
	double	maxLonplots;	        //Maximum longitude when generating SBAS plots (default  40º)
	double	AvailabilityPlotStep;	//Step for Availability and Continuity Risk plots (default 1º)	
	double	IonoPlotStep;			//Step for Ionosphere plot (default 0.1º)
	double	VerAlarmLimit;          //Vertical alarm limit (default 40 metres)
	double	HorAlarmLimit;          //Vertical alarm limit (default 50 metres)
	double	SBASPlotsRecHeight;		//Up coordinate (in meters) where the receiver is located (default 0 -sea level-)
	float	SBASPlotsMinGEOElev;	//Minimum elevation for the GEO for using its corrections (default 5 degrees). It uses float because value will be compared against a float
	int		NumSBASPlotsInclusionArea;	//Number of inclusion areas
	double	**SBASPlotsInclusionAreaDelimeters;	//Vertex of the inclusion areas
	int		NumSBASPlotsExclusionArea;	//Number of exclusion areas
	double	**SBASPlotsExclusionAreaDelimeters;	//Vertex of the exclusion areas


	//Options for DGNSS
	int	DGNSS;						// 0 => There is no DGNSS (default)
									// 1 => There is DGNSS

	int	sigmaInflation;				// 0 => There is no sigma inflation (default)
									// 1 => There is sigma inflation

	double 	dgnssMaxEph;			// Maximum age for DGNSS ephemeris

	double 	dgnssSigma2noiseGPS;	// Receiver noise (metres)

	double 	dgnssSigma2multipath;	// Receiver multipath (metres)

	double 	epsURA3o;				// URA Degradation factor (metres)

	double 	maxAgeDGNSS;			// Maximum age for DGNSS corrections (seconds)

	double	maxDGNSSPRC;			// Maximum value for the PRC corrections (default 500 metres)

	int	excludeSmoothingConvergenceUser;	// 0 => Do not exclude satellites during the smoothing convergence in the user (default)
											// 1 => Exclude satellites during the smoothing convergence in the user

	int	excludeSmoothingConvergenceRef;		// 0 => Do not exclude satellites during the smoothing convergence in the reference station
											// 1 => Exclude satellites during the smoothing convergence in the reference station (default)

	int	excludeSmoothingConvergenceDGNSS;	// Number of seconds (in continuous operation) in the smoothing in order to reach steady-state operation (default 360)

	int	rtcmYear;			// The year when the record of the binary file RTCM began (4 digits)

	int	rtcmYearShort;		// The year when the record of the binary file RTCM began (2 digits)

	int	rtcmMonth;			// The month when the record of the binary file RTCM began (2 digits)

	int	rtcmDay;			// The day when the record of the binary file RTCM began (2 digits)

	int	rtcmDoy;			// The day of year (DoY) when the record of the binary file RTCM began (3 digits)

	int	rtcmHour;			// The hour when the record of the binary file RTCM began (2 digits 24-hour format)

	enum RTCMMode	RTCMmode;	// CheckVersion => Check what version of RTCM is the binary file (default)
								// ConvertRTCM2 => Convert the binary file RTCM v2.x
								// ConvertRTCM3 => Convert the binary file RTCM v3.x
								// ProcessRTCM2 => Process the binary file RTCM v2.x
								// ProcessRTCM3 => Process the binary file RTCM v3.x
								// ProcessRINEX => Process the RINEX  file

	int	rinexVersion;		// 2 => Generates a RINEX version 2.11 from the binary file RTCM v3.x
							// 3 => Generates a RINEX version 3.00 from the binary file RTCM v3.x (default)



	//Other options

	enum SolutionMode solutionMode;		// 0 => SPP (default)
										// 1 => PPP
										// 2 => Fast-PPP Floated Ambiguities
										// 3 => Fast-PPP Fixed Ambiguities
										// 4 => SBAS 1 Frequency
										// 5 => SBAS DFMC
										// 6 => DGNSS



	//Options for print current epoch to terminal 
	int	OutputToTerminal;	// 0 => stdout is not to a terminal
   							// 1 => stdout is to a terminal	

	FILE *outFileStream;	// File stream where stdout is redirected

	FILE *terminalStream;	// File stream for terminal

	//Time interval options
	TTime	StartEpoch;		//Start epoch set by user
	TTime	EndEpoch;		//End   epoch set by user

	//Reference file interpolation degree
	int	RefDegInterp;	

	#if defined _OPENMP
	//Number of threads used in processing
	int numthreads;
	#endif

	//Options for date conversion
	enum DateConversionModes dateConversionMode;	// DateConversionModeNone 		=> No date conversion selected (default)
													// DateConversionModeCalendar 	=> Convert Calendar     date to other date formats
													// DateConversionModeDoY 		=> Convert Year/DoY/SoD date to other date formats
													// DateConversionModeGPSWeek 	=> Convert GPSWeek/SoW  date to other date formats
													// DateConversionModeMJDN 		=> Convert MJDN/SoD     date to other date formats

	int	dateConversionYear;			// Year    for date conversion
	int	dateConversionMonth;		// Month   for date conversion
	int	dateConversionDay;			// Day     for date conversion
	int	dateConversionHour;			// Hour    for date conversion
	int	dateConversionMinute;		// Minute  for date conversion
	int	dateConversionDoY;			// DoY     for date conversion
	int	dateConversionGPSWeek;		// GPSWeek for date conversion
	int	dateConversionMJDN;			// MJDN    for date conversion
	double	dateConversionSoD;		// SoD     for date conversion
	double	dateConversionSoW;		// SoW     for date conversion
	double	dateConversionSeconds;	// Seconds of hour for date conversion
													
	//Options for coordinate conversion
	enum CoordConversionModes coordConversionMode;	// CoordConversionModeNone	=> No coordinate conversion (default)
													// CoordConversionModeXYZ	=> Convert XYZ       to other coordinates formats
													// CoordConversionModeGeod	=> Convert Geodetic  to other coordinates formats
													// CoordConversionModeSph	=> Convert Spherical to other coordinates formats

	double coordConversionX;		// X      component for coordinate conversion (metres)
	double coordConversionY;		// Y      component for coordinate conversion (metres)
	double coordConversionZ;		// Z      component for coordinate conversion (metres)
	double coordConversionLat;		// Lat    component for coordinate conversion ([-90..90] degrees)
	double coordConversionLon;		// Lon    component for coordinate conversion ([180..180] degrees)
	double coordConversionHgt;		// Height component for coordinate conversion (metres)
	double coordConversionRadius;	// Radius component for coordinate conversion (metres)

	


} TOptions;


/****************************************************************
 * Declarations of global variables
 * Since gcc 10, flag '-fno-common' is enabled by default,
 * which produces an error if a global variable is not 
 * declared with 'extern' and is only defined once in
 * all .c files used, unlike previous versions, where it was declared
 * without 'extern' in one file and then could be imported several
 * times with 'extern'. This produced multiples declaration of the
 * same variable, but gcc was able to resolve this multiple variable 
 * declaration.
 ***************************************************************/

//////////////////////////// dataHandling.c
extern int printProgress;		// 0 => Do not print current epoch being processed to terminal (auto disables if stdout is not a terminal)
								// 1 => Print current epoch being processed to terminal

extern int printProgressWasDisabled; //This variable is set to 1 if printProgress was set to 1 and then set to 0 due to process was moved to the background
extern int printProgressConvert;	//For file conversion mode only
									// 0 => Do not print current epoch being processed to terminal (auto disables if stdout is not a terminal)
									// 1 => Print current epoch being processed to terminal

extern char		messagestr[MAX_MESSAGE_STR];
extern char		messagestrSwitchGEO[MAX_MESSAGE_STR];
extern char		messagestrSwitchMode[MAX_MESSAGE_STR];

extern const double    EGM96grid[181][361];
extern const int       listMaxSatGNSS[MAX_GNSS];

extern const enum WeightMode		defaultWeightMode; //Default weight mode to use in gLAB if non set

extern const int					attrAvail[MAXLETTERSDICTIONARY]; //List of measurement letters available in gLAB

extern const int					availGNSSFreq[MAX_GNSS][MAX_FREQUENCIES_PER_GNSS]; //List of available frequencies in each constellation

extern const int					maxLenghtConstName; //Maximum size for constellation name (e.g. Galileo or GLONASS)

extern const char					Freqname[MAX_GNSS][MAX_FREQUENCIES_PER_GNSS][6];

extern const int					maxLengthFreqName; //Maximum size for frequency name

extern const int					GNSS3Freq[MAX_GNSS];	//Constellations that have 3 or more frequencies (GEO and IRNSS only have 2 frequencies)

extern const int					BRDCAnyValue[MAX_GNSS];

extern const int					SNRtable[10]; //SNR table conversion from flag to dBHz

extern const enum GNSSystem			DefaultClkRefOrder[MAX_GNSS];	//Default reference constellation order to use for receiver clock

extern const int					SBASfreqPos2freqNum[NUMPOSFREQSBASMSG]; //SBAS frequency position to frequency number. The last position is for any unknown frequency, so the frequency number may be any number different from 1 and 5

extern const int   	            	FilterMeasType2PrintType[MAX_FILTER_MEASTYPE];

// Global variables for printing USERADDEDERROR buffer
extern int		linesstoredUserError[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
extern char		**printbufferUserError[MAX_GNSS][MAX_SATELLITES_PER_GNSS];	//There max number of lines possible is very high, as each satellite may
																	//have multiple errors at the same time from the same or different types
// Global variables for printing CS buffer
extern int		linesstoredCS[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
extern char		printbufferCS[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_LINES_BUFFEREDCS][MAX_PRINT_LINE];

// Global variables for printing SFCSdata buffer
extern int		linesstoredSFCSdata[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
extern char		printbufferSFCSdata[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_LINES_BUFFEREDCS][MAX_PRINT_LINE];

// Global variables for printing MWCSdata buffer
extern int		linesstoredMWCSdata[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
extern char		printbufferMWCSdata[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_LINES_BUFFEREDCS][MAX_PRINT_LINE];

// Global variables for printing LICSdata buffer
extern int		linesstoredLICSdata[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
extern char		printbufferLICSdata[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_LINES_BUFFEREDCS][MAX_PRINT_LINE];
	
// Global variables for printing IGFCSdata buffer
extern int		linesstoredIGFCSdata[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
extern char		printbufferIGFCSdata[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_LINES_BUFFEREDCS][MAX_PRINT_LINE];

// Global variables for printing MODEL buffer
extern int		linesstoredMODEL[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
extern char		printbufferMODEL[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_LINES_BUFFERED][MAX_PRINT_LINE_MODEL];

// Global variables for printing SBASCORR buffer
extern char		printbufferSBASCORR[MAX_SATELLITES_VIEWED][MAX_PRINT_LINE];

// Global variables for printing SBASVAR buffer
extern char		printbufferSBASVAR[MAX_SATELLITES_VIEWED][MAX_PRINT_LINE];

// Global variables for printing SBASIONO buffer
extern char		printbufferSBASIONO[MAX_SATELLITES_VIEWED][MAX_PRINT_LINE];

// Global variables for printing SBASUNSEL buffer
extern char		printbufferSBASUNSEL[MAX_SATELLITES_VIEWED][MAX_PRINT_LINE];

// Global variables for printing SBASDFMCCORR buffer
extern char		printbufferSBASDFMCCORR[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_PRINT_LINE];

// Global variables for printing SBASDFMCVAR buffer
extern char		printbufferSBASDFMCVAR[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_PRINT_LINE];

// Global variables for printing SBASDFMCUNSEL buffer
extern char		printbufferSBASDFMCUNSEL[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_PRINT_LINE];

// Global variables for printing DGNSS buffer
extern char		printbufferDGNSS[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_PRINT_LINE];

//NOTE that SATSEL, PREFIT and POSTFIT buffers will not work well with multithreading, as thread with satellites 
//with the same constellation will share the index variable!

// Global variables for printing SATSEL buffer
extern int		linesstoredSATSEL[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
extern char		printbufferSATSEL[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_LINES_BUFFERED][MAX_PRINT_LINE];

// Global variables for printing PREFIT buffer
extern int		linesstoredPREFIT[MAX_GNSS][MAX_MEASKIND_PRINT_MEASUREMENTS][MAX_FILTER_MEASUREMENTS_SAT];
extern char		printbufferPREFIT[MAX_GNSS][MAX_MEASKIND_PRINT_MEASUREMENTS][MAX_FILTER_MEASUREMENTS_SAT][MAX_LINES_BUFFEREDPREFIT][MAX_PRINT_LINE];

// Global variables for printing POSTFIT buffer
extern int		linesstoredPOSTFIT[MAX_GNSS][MAX_MEASKIND_PRINT_MEASUREMENTS][MAX_FILTER_MEASUREMENTS_SAT];
extern char		printbufferPOSTFIT[MAX_GNSS][MAX_MEASKIND_PRINT_MEASUREMENTS][MAX_FILTER_MEASUREMENTS_SAT][MAX_LINES_BUFFEREDPREFIT][MAX_PRINT_LINE];

// Global variables for printing EPOCHSAT buffer
extern int		linesstoredEPOCHSAT[MAX_MEASKIND_PRINT_MEASUREMENTS];
extern char		printbufferEPOCHSAT[MAX_MEASKIND_PRINT_MEASUREMENTS][MAX_FILTER_MEASUREMENTS_SAT*MAX_GNSS][MAX_PRINT_LINE];

// Global variables for printing FILTER buffer
extern char		printbufferFILTER[MAX_PRINT_LINE_FILTER];

extern char		wordlst[MAX_WORDS][MAX_INPUT_LINE]; //Used only ion input.c Defined as a global variable it may be too big for the stack, and can be safely reused by each function reading from file

/**************************************
* NeQuick-G Global Variables
**************************************/

#define NEQUICK_G_JRC_MODIP_GRID_LAT_POINTS_COUNT (39)
#define NEQUICK_G_JRC_MODIP_GRID_LONG_POINTS_COUNT (39)

extern const double_t g_corrected_modip_degree
    [NEQUICK_G_JRC_MODIP_GRID_LAT_POINTS_COUNT]
    [NEQUICK_G_JRC_MODIP_GRID_LONG_POINTS_COUNT];

/** F2 coefficient max. degree. */
#define ITU_F2_COEFF_MAX_DEGREE (76)
/** F2 coefficient max. order. */
#define ITU_F2_COEFF_MAX_ORDER (13)

/** FM3 coefficient max. degree. */
#define ITU_FM3_COEFF_MAX_DEGREE (49)
/** FM3 coefficient max. order. */
#define ITU_FM3_COEFF_MAX_ORDER (9)


typedef double_t F2_coefficient_array_t
  [ITU_F2_COEFF_MAX_DEGREE][ITU_F2_COEFF_MAX_ORDER];

typedef double_t Fm3_coefficient_array_t
  [ITU_FM3_COEFF_MAX_DEGREE][ITU_FM3_COEFF_MAX_ORDER];

/** 2 solar activity conditions: low and high. */
#define ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT (2)
/** index for low solar activity condition. */
#define ITU_F2_LAYER_COEFF_LOW_SOLAR_ACTIVITY_IDX (0)
/** index for high solar activity condition. */
#define ITU_F2_LAYER_COEFF_HIGH_SOLAR_ACTIVITY_IDX (1)

extern const F2_coefficient_array_t g_NeQuickG_ccir11_F2[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const F2_coefficient_array_t g_NeQuickG_ccir12_F2[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const F2_coefficient_array_t g_NeQuickG_ccir13_F2[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const F2_coefficient_array_t g_NeQuickG_ccir14_F2[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const F2_coefficient_array_t g_NeQuickG_ccir15_F2[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const F2_coefficient_array_t g_NeQuickG_ccir16_F2[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const F2_coefficient_array_t g_NeQuickG_ccir17_F2[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const F2_coefficient_array_t g_NeQuickG_ccir18_F2[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const F2_coefficient_array_t g_NeQuickG_ccir19_F2[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const F2_coefficient_array_t g_NeQuickG_ccir20_F2[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const F2_coefficient_array_t g_NeQuickG_ccir21_F2[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const F2_coefficient_array_t g_NeQuickG_ccir22_F2[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];

extern const Fm3_coefficient_array_t g_NeQuickG_ccir11_Fm3[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const Fm3_coefficient_array_t g_NeQuickG_ccir12_Fm3[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const Fm3_coefficient_array_t g_NeQuickG_ccir13_Fm3[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const Fm3_coefficient_array_t g_NeQuickG_ccir14_Fm3[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const Fm3_coefficient_array_t g_NeQuickG_ccir15_Fm3[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const Fm3_coefficient_array_t g_NeQuickG_ccir16_Fm3[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const Fm3_coefficient_array_t g_NeQuickG_ccir17_Fm3[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const Fm3_coefficient_array_t g_NeQuickG_ccir18_Fm3[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const Fm3_coefficient_array_t g_NeQuickG_ccir19_Fm3[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const Fm3_coefficient_array_t g_NeQuickG_ccir20_Fm3[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const Fm3_coefficient_array_t g_NeQuickG_ccir21_Fm3[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];
extern const Fm3_coefficient_array_t g_NeQuickG_ccir22_Fm3[ITU_F2_LAYER_SOLAR_ACTIVITY_CONDITIONS_COUNT];

	
/**************************************
 * Declarations of internal operations
 **************************************/

// Initialisations and frees
void initOptions (TOptions *options);
void freeOptions(TOptions *options);
void initSatellite (TEpoch *epoch, int satIndex, int satCSindex, TOptions  *options);
void initEpoch (TEpoch *epoch, TOptions  *options);
void initGNSSproducts (TGNSSproducts *products);
void initBRDCproducts (TBRDCproducts *BRDC, double GLOintStep);
void initBRDCblock (TBRDCblock *BRDCblock);
void initSP3products (TSP3products *SP3);
void initSP3orbitblock (TSP3orbitblock *SP3orbitblock);
void initSP3clockblock (TSP3clockblock *SP3clockblock);
void initIONEXDCB (TIonexDCB *IonexDCB);
void initIONEX (TIONEX *IONEX);
void initIonoMap (TIonoMap *ionoMap);
void initIonexStation (TIonexStation *ionexStation);
void initFPPPDCB (TFPPPDCB *FPPPDCB);
void initFPPPIONEX (TFPPPIONEX *FPPP);
void initFPPPMap (TFPPPMap *FPPPMap);
void initFPPPMapData (TFPPPMap *FPPPMap);
void initPiercePoint (TPiercePoint *PiercePoint);
void initTropoGalData (TTROPOGal *TropoGal);
void initTropoGalParameters (TTROPOGal *TropoGal, TTROPOGalParameters *ESAParam);
void initFilterSolution (TFilterSolution *solution);
void init0Unkinfo (TUnkinfo  *unkinfo);
void initConstellation (TConstellation *constellation);
void initConstellationElement (TConstellationElement *sat);
void initAntennaList (TAntennaList *antennaList);
void initAntenna (TAntenna *antenna);
void freeANTEXdata (TConstellation  *constellation, TAntennaList  *antennaList);
void initStat (TStat *Stat);
void initTGD (TTGDdata *tgdData, TOptions *options, int mode);
void initDCB (TDCBdata *dcbData);
void initSINEXBiasData (TSINEXBiasData *SINEXBias);
void initSINEXBiasBlock (TSINEXBiasBlock *SINEXBiasBlock);
void freeSINEXBIASData (TSINEXBiasData *SINEXBias);
void initReceiverList (TReceiverList *recList);
void initStationList (TStationList *stationList);
void initSBASdatabox (TSBASdatabox *sbasdatabox);
void initSBASblock (TSBASblock *sbasblock);
void initSBASdata (TSBASdata *SBASdata, int pos);
void ClearSBASdata (TSBASdata *SBASdata, int pos, int frequencyPos);
void initSBAScorrections (TSBAScorr *SBAScorr);
void initStfdESA (TStdESA *StdESA, int StfdESAenabled);
void initSBASPlotsMode (TEpoch *epoch, TSBASPlots *SBASplots, TOptions *options, int *retvalue);
void SetSatellitesSBASPlotsMode (TEpoch *epoch, TSBASdata *SBASdata, TOptions  *options);
void freeSBASPlotsData(TSBASPlots *SBASplots, TOptions *options);
void initUserError (TUserError *UserError);
void initRTCM2 (TRTCM2 *rtcm2);
void initRTCM3 (TRTCM3 *rtcm3);
void initMSG1 (TMSG1 *sc, int n);
void initMSG2 (TMSG2 *sc, int n);
void initMSG3 (TMSG3 *sc);
void initMSG24 (TMSG24 *sc);

//Struct partial copying
void TUnkinfoPartialCopy (TUnkinfo  *prevUnkinfo, TUnkinfo *unkinfo);
void TFilterSolutionPartialCopy (TFilterSolution *prevsolution, TFilterSolution *solution, TUnkinfo *unkinfo);

// General
void changeBase (double base[3][3], double vector[3]);
double min (double a, double b);
double max (double a, double b);
double modulo (double a, double modNum);
int mod (int a, int N);
void unitary (double *vect);
void vectProd (double *a, double *b, double *res);
double scalarProd (double *a, double *b);
char *trim (char *line, int length);
char *getstr (char *out, char *line, int linelength, int ini, int length);
void getnumericalelements (char *line, int length, int *numelements, double *out);
int	checkConstellationChar(char charac);
int checkCodelessMeas (enum MeasurementType meas);

// Measurements
enum MeasurementKind whatIs (enum MeasurementType meas);
int getFrequencyInt (enum MeasurementType meas);
int getFrequencyIntCombinations(enum MeasurementType meas, int *freq);
enum MeasurementType measstr2meastype (char *str);
char *meastype2measstr (enum MeasurementType meas);
enum GNSSystem gnsschar2gnsstype (char GNSS);
enum GNSSystem gnssstr2gnsstype (char *GNSS);
char *gnsstype2gnssstr (enum GNSSystem GNSS);
char *gnsstype2gnssname (enum GNSSystem GNSS);
char gnsstype2char (enum GNSSystem GNSS);
enum SatelliteBlock satblockstr2satblock (char *str, enum GNSSystem GNSS);
char *satblock2satblockstr (enum SatelliteBlock satBlock);
enum TimeSystemCorrection timecorrstr2timecorrtype (char *str);
char *timecorrtype2timecorrstr (enum TimeSystemCorrection timecorr);
char *SolutionModeNum2SolutionModeChar(enum SolutionMode numsol);

//Weight modes
char *WeightModeNum2WeightModestr(enum WeightMode weightMode);

//Receiver types
char *GPSrecType2str(enum ReceiverType recType);


//GLONASS specific function
void getGLOFreqOffsets (TEpoch *epoch, char *NavFile, char *gloNavFile, FILE **fdRNXglonav, int *nextgloNav, TGNSSproducts *products, TGNSSproducts *productsGLO, TOptions *options);

// Epoch handling
int getMeasModelValue (TEpoch *epoch, enum GNSSystem GNSS, int PRN, const enum MeasurementType *measList, const int *freqList, double *measurement, double *model, int filterMeasPos);
double getModelValue (TEpoch *epoch, enum GNSSystem GNSS, int PRN, const enum MeasurementType *measList, const int *freqList, int filterMeasPos);
double getMeasurementValue (TEpoch *epoch, enum GNSSystem GNSS, int PRN, const enum MeasurementType *measList, const int *freqList);
void posRINEXHeaderDataUpdate(int stationType, enum ReceiverType, char *recFile, TReceiverList *recList, TAntennaList *antennaList, TConstellation *constellation, TEpoch  *epoch, TOptions  *options);
void FillMeasurements (enum GNSSystem GNSS, int  PRN, int  satIndex, TEpoch  *epoch, TOptions  *options);

//Triple frequency combination factor
void computeIGFfactors (TEpoch *epoch, enum GNSSystem GNSS, int PRN, enum MeasurementType IGFcomb, const int *freqList);

//Epoch data buffering for best GEO selection
void SaveDataforGEOselection (TEpoch *epoch, TFilterSolution *solution, int OverAlarmLimits, TOptions *options);
void SelectBestGEO (TEpoch *epoch, TFilterSolution *solution, TOptions *options);
void freeDataforGEOselection (TEpoch *epoch);
	

// OC Products handling
TTime getProductsFirstEpochBRDC (TGNSSproducts *products);
TTime getProductsFirstEpochSP3 (TGNSSproducts *products);
TTime getProductsFirstEpoch (TGNSSproducts *products);
TTime getProductsLastEpochBRDC (TGNSSproducts *products);
TTime getProductsLastEpochSP3 (TGNSSproducts *products);
TTime getProductsLastEpoch (TGNSSproducts *products);
void fillBroadcastHealth (TBRDCblock *block); 
TBRDCblock *selectBRDCblock (TBRDCproducts *products, TTime *t, enum GNSSystem GNSS, int PRN, int IOD, int BRDCtype, TOptions *options);
char *BRDCType2String (enum GNSSystem GNSS, int BRDCType);
char *BRDCHealthSel2String(enum BRDCHealthSelModes satHealthMode);
int CheckBRDCHealth (TBRDCblock *block, enum BRDCHealthSelModes satHealthMode, char *healthStr);
char *BRDCHealth2String (TBRDCblock *block);
void freeBRDCproducts (int type, TGNSSproducts *products);

// Time handling
int MJDN (struct tm *tm);
char *MonthName (int month);
void t2tm (TTime *t, struct tm *tm, double *seconds);
void t2tmnolocal (TTime *t, struct tm *tm, double *seconds);
void t2doy (TTime *t, int *year, double *doy);
int date2doy (int year, int month, int day);
void doy2date (int year, int doy, int *month, int *day);
char *t2doystr (TTime *t);
TTime gpsws2ttime (int GPSweek, double SoW);
void ttime2gpswsnoroll (TTime *t, int *GPSweek, double *SoW);
double yeardoy2MJDN (int year, int doy, int sod);
TTime cal2t (int year, int month, int day, int hour, int minute, double second);
void tday_of_month (TTime *t, int *day_of_month, int *month_days, int *month_number);
double tdiff (TTime *a, TTime *b);
double tsec (TTime *a);
void getcurrentsystemtime (struct tm *tm);
TTime tdadd (TTime *a, double b);
int Gal_loc_month (double doy, int *im, double *id);

// Coordinates conversion functions
double sqrt_inhouse (double x);
void XYZ2Spherical (double  *positionXYZ, double *positionSph);
void Spherical2XYZ (double  *positionSph, double *positionXYZ);
void XYZ2NEU (double *positionXYZ, double *positionNEU);
void NEU2XYZ (double *positionNEU, double *positionXYZ);

// Anti-Spoofing epoch check
int AntiSpoofingOff (TTime *t, TTime **EpochsNoAS);

// Get Leap Seconds
int	getLeapSeconds (TTime *t, TTime *LeapSecondsTimeList, int *LeapSecondsNumList);

// Date Conversion mode functions
void ConvertCalendarDate(int year, int month, int day, int hour, int minute, double seconds, TOptions  *options);
void ConvertDoYDate(int year, int doy, double sod, TOptions  *options);
void ConvertGPSWeekDate(int GPSWeek, double SoW, TOptions  *options);
void ConvertMJDNDate(int MJDN, double SoD, TOptions  *options);

// Coordinate conversion mode functions
void ConvertCartesianCoord(double x, double y, double z, TOptions  *options);
void ConvertGeodeticCoord(double lon, double lat, double height, TOptions  *options);
void ConvertSphericalCoord(double lon, double lat, double Radius, TOptions  *options);


// IONEX
enum MappingFunctionTypes mappingFunctionStr2Type (char *mappingFunctionStr);
int numSteps (double a1, double a2, double da);
void allocateIonoMap (TIonoMap *ionoMap);
double E (int exponent);
int	conv3Dto1D (int i, int j, int k, int ni, int nj);
int ionoConv3Dto1D (TIonoMap *ionoMap, int ihgt, int ilat, int ilon);
int ionoHLLto1D (TIonoMap *ionoMap, double hgt, double lat, double lon);
int setIonoValue (TIonoMap *ionoMap, int type, double hgt, double lat, double lon, double value);
double getIonoValue (TIonoMap *ionoMap, int type, double hgt, double lat, double lon);
int getIonoMapTotalSize (TIonoMap *ionoMap);
int FPPPConv3Dto1D (TFPPPMap *FPPPMap, int ihgt, int ilat, int ilt);
int FPPPHLLto1D (TFPPPMap *FPPPMap, double hgt, double lat, double lt);
int setFPPPValue (TFPPPMap *FPPPMap, int type, double hgt, double lat, double lt, double value);
double getFPPPValue (TFPPPMap *FPPPMap, int type, double hgt, double lat, double lt);
int getFPPPMapTotalSize (TFPPPMap *FPPPMap);
void getIonoPiercePoint (TEpoch *epoch, TPiercePoint *PiercePoint, int satIndex, double earthRadius, double altitude, int mode);
void getMappingFunction (TPiercePoint *PiercePoint, double earthRadius, double altitude, enum MappingFunctionTypes functionType);

// Constellation
TConstellationElement* getConstellationElement (enum GNSSystem GNSS, int PRN, TTime *t, TConstellation *constellation);

// Station
TStation *getStation (char *name, TStationList *stationList);

// Statistics
void addStat (TStat *Stat, double value);

//Concatenate SP3 and clocks
void ConcatenateSP3 (int RefData, TGNSSproducts *products, TGNSSproducts *pastSP3Prod, TGNSSproducts *nextSP3Prod, TOptions  *options);
void freeSP3data(TGNSSproducts  *products);

// SBAS
char *SBASnavmode2SBASnavstr (int mode);
void strbintostrhex (char *binary, int binarylen, char *hex, int capital);
void strhextostrbin (char *hex, int length, char *binary);
void strbintobinstr (char *binary,int binarylen, unsigned char *bitstr, int bitstrlen);
int twocomplementstrbintointeger (char *binary, int binarylen);
long long int twocomplementstrbintolonglonginteger (char *binary, int binarylen);
int checksumSBAS (unsigned char *msg);
int openSBASwritefiles (FILE **fdvector, char **filelist, char *fileread, int sourcefile, TOptions  *options);
void closefiles (FILE  **fdlist, int numfiles);
void SBASMissingMessageClearData (int GEOindex, int frequencyPos, TTime *currentepoch, TSBASdata  *SBASdata, TOptions  *options);
void SBASErrorMessageTimeoutFastCorr (int GEOindex, int frequencyPos, TTime *currentepoch, TSBASdata  *SBASdata, TOptions  *options);
void SBASGEOselection (TEpoch  *epoch, TSBASdata  *SBASdata, TOptions  *options);
void SBASGEOAlarmCheck (TEpoch  *epoch, TSBASdata  *SBASdata, TOptions  *options);
void SBAShandlespecialevents (TTime *currentepoch, TSBASdata  *SBASdata, TOptions  *options);
int IGP2latlon (int bandnumber, int IGP, int *IGPlat, int *IGPlon);
int IPP2Sqr (double IPPlat, double IPPlon, double *IGPlat, double *IGPlon, double *increment);
int IGPLatLon2BandNumberIGP (double IGPlat, double IGPlon, int *Bandnumber, int *IGP, int *IGP90);
void IGPsearch (TSBASdata *SBASdata, int GEOindex, double IPPlat, double IPPlon, double IGPlat, double IGPlon, double lat_inc, double lon_inc, int *InterpolationMode, int *IGPnumber, int *IGPBandNumber);
void SBASionoInterpolation (double IPPlat,double IPPlon,double IGPlat1,double IGPlon1,double IGPlat2,double IGPlon2,int *InterpolationMode,double IGPDelays[5],double IGPSigma2[5],double *VerticalDelay,double *Sigma2,double *IPP_Weight);
int InsideOutside (double latpos, double lonpos, double lat1, double lon1, double lat2, double lon2, double lat3, double lon3, double lat4, double lon4, int shape);
void FillGEOelevationGrid (TSBASdata *SBASdata, TEpoch *epoch, TSBASPlots *SBASplots, TOptions *options, int *retvalue);

// User added error functions
double AWGN_generator (double stddev);

//Compare functions for qsort
int qsort_compare_float(const void *a,const void *b);
int qsort_compare_double(const void *a,const void *b);
int qsort_compare_int(const void *a,const void *b);
int qsort_compare_int_reverse(const void *a,const void *b);
int	qsort_compare_transtime(const void *a,const void *b);

//Recursive directory creation
int mkdir_recursive(char *path);

//Functions for range list structure
void InitRangeList (enum GNSSystem GNSS, int PRN, TRangeList *List);
void freeRangeList (TRangeList *List);
void AddRangeList (enum GNSSystem GNSS, int PRN, TRangeList *List);
void ExtendRangeList (enum GNSSystem GNSS, int PRN, int pos, TRangeList *List);
void SatRangeList2String (int i, TRangeList *List,  char *auxstr);
void GroupSatRangeByMeas (int shortMeas, int numItems, enum MeasurementType *measList, double *ThresholdList, char **strList, int *outNumItems, char **outMeasGroup, char **outStrList, double *outThresholdList);
int AreFilterMeasurementsEqual (int checkSmooth, int RecType1, enum GNSSystem GNSS1, int PRN1, int Pos1, int RecType2, enum GNSSystem GNSS2, int PRN2, int Pos2, TOptions  *options);
int AreDopplerMeasurementsEqual (int RecType1, enum GNSSystem GNSS1, int PRN1, int Pos1, int RecType2, enum GNSSystem GNSS2, int PRN2, int Pos2, TOptions  *options);

//Function to convert weight modes to strings
void WeightType2String (enum GNSSystem GNSS, int PRN, int NumMeas, char *str, TOptions *options);
char *SNRCombModeNum2String(enum SNRWeightComb SNRweightComb, enum MeasurementType meas, double K1, double K2, double K3, double K4);

//Compute geoid height
double getEGM96Height (double *position);

#endif /*DATAHANDLING_H_*/

