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
 * File: dataHandling.h
 * Code Management Tool File Version: 5.5  Revision: 1
 * Date: 2020/12/11
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
 *       END_RELEASE_HISTORY
 *****************************/

#ifndef DATAHANDLING_H_
#define DATAHANDLING_H_

/* System modules */
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>


/* Internal types, constants and data */
#define MAX_SATELLITES_VIEWED					200
#define MAX_GNSS								7
#define MAX_SATELLITES_PER_GNSS					50
#define MAX_FREQUENCIES_PER_GNSS				10
#define MAX_MEASUREMENTS_PER_SATELLITE			50
#define MAX_SLIDING_WINDOW						610
#define MAX_INTERPOLATION_DEGREE				19
#define MAX_RECEIVER_NAME						60
#define MAX_ANTENNA_NAME						60
#define MAX_MEASUREMENTS						151

#define MAX_CS_MEMORY							20
#define MAX_FILTER_MEASUREMENTS					4
#define MAX_UNK									(4+MAX_SATELLITES_VIEWED+1)
#define MAX_VECTOR_UNK							((MAX_UNK)*(MAX_UNK+1)/2)
#define MAX_PAR									4
#define MAX_SBAS_PRN							211
#define MAX_NUM_SBAS							50
#define MAX_WORDS								200
#define MAX_LINES_BUFFERED						10
#define SIGMA_INF								1e7
#define SIGMA_INF_DR							1e4
#define SIGMA_INF_DT							3e5
#define MAX_INPUT_LINE							4096
#define MAX_MESSAGE_STR							2*MAX_INPUT_LINE
#define MAX_OUTPUT_FILENAME						2*MAX_INPUT_LINE //This to avoid potential buffer overflow in output filename if filename+extension is large enough
#define MAX_STATION_NAME						200
#define MAX_DEPRECATED_MSG_SIZE					160
#define INVALID_CLOCK							999999.999999
#define MAX_DCB_TYPES							4
#define MAX_SAT_GPS								32
#define MAX_SAT_GAL								36
#define MAX_SAT_GLO								32
#define MAX_SAT_GEO								32
#define MAX_SAT_BDS								63
#define MAX_SAT_QZS								10
#define MAX_SAT_IRN								14

//NOTE: Single letter constant may cause problems compiling in Windows!!
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
#define MAXAPROXPOSERROR						1E5

#define GPSmf1									154
#define GPSmf2									120
#define GPSmf5									115
#define GPSmfw									(GPSmf1-GPSmf2)
#define GALmf1									154
#define GALmf5a									115
#define GALmf5b									118
#define GALmf5									116.5
#define GALmf6									125
#define SBASmf1									154
#define SBASmf5									115

#define GPSf1									(GPSmf1*f0)
#define GPSf2									(GPSmf2*f0) 
#define GPSf5									(GPSmf5*f0)
#define GPSfw									(GPSmfw*f0)
#define GALf1									(GALmf1*f0)
#define GALf5a									(GALmf5a*f0)
#define GALf5b									(GALmf5b*f0)
#define GALf5									(GALmf5*f0)
#define GALf6									(GALmf6*f0)
#define SBASf1									(SBASmf1*f0)
#define SBASf5									(SBASmf5*f0)

#define GPSl1									(cf0/GPSmf1)
#define GPSl2									(cf0/GPSmf2)
#define GPSl5									(cf0/GPSmf5)
#define GPSlw									(cf0/GPSmfw)
#define GALl1									(cf0/GALmf1)
#define GALl5a									(cf0/GALmf5a)
#define GALl5b									(cf0/GALmf5b)
#define GALl5									(cf0/GALmf5)
#define GALl6									(cf0/GALmf6)
#define SBASl1									(cf0/SBASmf1)
#define SBASl5									(cf0/SBASmf5)

#define GAMMAGPS12								((GPSf1*GPSf1)/(GPSf2*GPSf2))
#define ALPHAGPS12								(1/(GAMMAGPS12-1))
#define JULIANDAYDIFF							2400000.5

#define DEFAULTMARKERNAME						"----"

#define FLAG_CYCLESLIP							1
#define FLAG_FAIL								2

#define SBASOUTPUTPATH							"SBAS"
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

// If observation file start at hour HOURSPREVDAYCONVERGENCE or later,
//  gLAB will consider that from this hour to the following day is just
//  epochs to make SBAS data, smoothing and filter values to converge
#define HOURSPREVDAYCONVERGENCE					22

// Definition for getLback (input.c)
#define BACKWARD_READ_BATCH						450

// Constants for SBAS MESSAGES
#define DONTUSE									0
#define PRNMASKASSIGNMENTS						1
#define FASTCORRECTIONS2						2
#define FASTCORRECTIONS3						3
#define FASTCORRECTIONS4						4
#define FASTCORRECTIONS5						5
#define INTEGRITYINFO							6
#define FASTCORRECTIONSDEGRADATIONFACTOR		7
#define RESERVED8								8
#define GEONAVIGATIONMESSAGE					9
#define DEGRADATIONPARAMETERS					10
#define RESERVED11								11
#define SBASNETWORKTIMEPARAMETERS				12
#define RESERVED13								13
#define RESERVED14								14
#define RESERVED15								15
#define RESERVED16								16
#define GEOSATELLITEALMANACS					17
#define IONOSPHERICGRIDPOINTSMASKS				18
#define RESERVED19								19
#define RESERVED20								20
#define RESERVED21								21
#define RESERVED22								22
#define RESERVED23								23
#define MIXEDFASTLONGTERMCORRECTIONS			24
#define LONGTERMSATELLITECORRECTIONS			25
#define IONOSPHERICDELAYCORRECTIONS				26
#define SBASSERVICEMESSAGE						27
#define CLOCKEPHEMERISCOVARIANCEMATRIX			28
#define INTERNALTESTMESSAGE						62
#define NULLMESSAGE								63

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
#define IODN									13
#define URAMINRANGE								14
#define URAMAXRANGE								15
#define URANOMINALVALUE							16

// Constants for SBAS URA values

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
#define A1WNT									0
#define A0WNT									1
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
#define USRNUMPOS								16
#define USRGNSSPOS								0
#define USRPRNPOS								1
#define USRMEASPOS								2
#define USRMEASRAWPOS							3
#define USRMEASTOTPOS							4
#define USRNUMTOTERRPOS							5
#define USRTOTERRPOS							6
#define USRNUMSTEPPOS							7
#define USRSTEPERRPOS							8
#define USRNUMRAMPPOS							9
#define USRRAMPERRPOS							10
#define USRNUMSINUPOS							11
#define USRSINUERRPOS							12
#define USRNUMAWGNPOS							13
#define USRAWGNERRPOS							14
#define USREPOCHPOS								15

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
	ftSBASEMSMESSAGE
};

// Enumerator for different GNSS systems
enum GNSSystem {
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
	BRDC,
	SP3
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
	GAUT = 0,
	GPUT = 1,
	SBUT = 2,
	GLUT = 3,
	GPGA = 4,
	GLGP = 5,
	QZGP = 6,
	QZUT = 7,
	BDUT = 8,
	IRUT = 9,
	IRGP = 10,
	UNKNOWN_TIME_CORR = 11
};

// Enumerator for different satellite blocks
enum SatelliteBlock {
	UNKNOWN_BLOCK,
	GPS_BLOCK_I,
	GPS_BLOCK_II,
	GPS_BLOCK_IIA,
	GPS_BLOCK_IIR,
	GPS_BLOCK_IIRM,
	GLONASS_BLOCK,
	GLONASS_BLOCK_M
};

// Enumerator for ionospheric model
enum IonoModel {
	UNKNOWN_IM,
	NoIono,
	Klobuchar,
	IONEX,
	FPPP,
	neQuick,
	BeiDou,
	SBASiono
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
enum P1C1DCBModel {
	p1c1UNKNOWN,
	p1c1NONE,
	p1c1FLEXIBLE,
	p1c1STRICT
};

// Enumerator for P1P2 DCB model
enum P1P2DCBModel {
	p1p2UNKNOWN,
	p1p2NONE,
	p1p2RINEX,
	p1p2DCB,
	p1p2IONEX,
	p1p2FPPP
};

// Enumerator for receiver type
enum ReceiverType {
	rtNA,
	rtUNKNOWN,
	rtCROSS,
	rtNOP1,
	rtNOMINAL
};

// Enumerator for different measurements
enum MeasurementType {
	NA = 0,					// N/A
	C1A =  1, L1A =  2, D1A =  3, S1A =  4, // GAL         A PRS     @ E1
	C1B =  5, L1B =  6, D1B =  7, S1B =  8, // GAL         B I/NAV   @ E1
	C1C =  9, L1C = 10, D1C = 11, S1C = 12, // GP/GL/GA/SB C/A       @ L1/G1/E1
	C1P = 13, L1P = 14, D1P = 15, S1P = 16, // GP/GL       P         @ L1/G1
	C1W = 17, L1W = 18, D1W = 19, S1W = 20, // GPS         Z         @ L1
	C1X = 21, L1X = 22, D1X = 23, S1X = 24, // GAL         B+C       @ E1
	C1Y = 25, L1Y = 26, D1Y = 27, S1Y = 28, // GPS         Y         @ L1
	C1Z = 29, L1Z = 30, D1Z = 31, S1Z = 32, // GAL         A+B+C     @ E1
	C1M = 33, L1M = 34, D1M = 35, S1M = 36, // GPS         M         @ L1
			  L1N = 38, D1N = 39, S1N = 40, // GPS         codeless  @ L1
	C2C = 41, L2C = 42, D2C = 43, S2C = 44, // GP/GL       C/A       @ L2/G2
	C2D = 45, L2D = 46, D2D = 47, S2D = 48, // GPS         L1(C/A)+(P2-P1) @ L2
	C2S = 49, L2S = 50, D2S = 51, S2S = 52, // GPS         L2C (M)   @ L2frequency
	C2L = 53, L2L = 54, D2L = 55, S2L = 56, // GPS         L2C (L)   @ L2
	C2X = 57, L2X = 58, D2X = 59, S2X = 60, // GPS         L2C (M+L) @ L2
	C2P = 61, L2P = 62, D2P = 63, S2P = 64, // GP/GL       P         @ L2/G2
	C2W = 65, L2W = 66, D2W = 67, S2W = 68, // GPS         Z         @ L2
	C2Y = 69, L2Y = 70, D2Y = 71, S2Y = 72, // GPS         Y         @ L2
	C2M = 73, L2M = 74, D2M = 75, S2M = 76, // GPS         M         @ L2
			  L2N = 78, D2N = 79, S2N = 80, // GPS         codeless  @ L2
	C5I = 81, L5I = 82, D5I = 83, S5I = 84, // GP/GA/SB    I         @ L5/E5a
	C5Q = 85, L5Q = 86, D5Q = 87, S5Q = 88, // GP/GA/SB    Q         @ L5/E5a
	C5X = 89, L5X = 90, D5X = 91, S5X = 92, // GP/GA/SB    I+Q       @ L5/E5a 
	C7I = 93, L7I = 94, D7I = 95, S7I = 96, // GAL         I         @ E5b
	C7Q = 97, L7Q = 98, D7Q = 99, S7Q =100, // GAL         Q         @ E5b
	C7X =101, L7X =102, D7X =103, S7X =104, // GAL         I+Q       @ E5b
	C8I =105, L8I =106, D8I =107, S8I =108, // GAL         I         @ E5 (E5a+E5b)
	C8Q =109, L8Q =110, D8Q =111, S8Q =112, // GAL         Q         @ E5 (E5a+E5b)
	C8X =113, L8X =114, D8X =115, S8X =116, // GAL         I+Q       @ E5 (E5a+E5b)
	C6A =117, L6A =118, D6A =119, S6A =120, // GAL         A PRS     @ E6
	C6B =121, L6B =122, D6B =123, S6B =124, // GAL         B         @ E6
	C6C =125, L6C =126, D6C =127, S6C =128, // GAL         C         @ E6
	C6X =129, L6X =130, D6X =131, S6X =132, // GAL         B+C       @ E6
	C6Z =133, L6Z =134, D6Z =135, S6Z =136, // GAL         A+B+C     @ E6
	
	// Combinations
	ENDMEAS = 137,		// Internal marker for combinations
	LW = 138,			// GPS         Wide-lane carrier-phase combination (f1*P1+f2*P2)/(f1+f2)
	PW = 139,			// GPS         Short-lane pseudorange combination (f1*L1-f2*L2)/(f1-f2)
	BW = 140,			// GPS         Melbourne-Wübbena combination (Lw-Pw)
	LI = 141,			// GPS         Ionospheric carrier-phase combination (L1-L2)
	PI = 142,			// GPS         Ionospheric pseudorange combination (P2-P1)
	LC = 143,			// GPS         Ionospheric-free carrier-phase combination (f1^2*L1-f2^2*L2)/(f1^2-f2^2)
	PC = 144,			// GPS         Ionospheric-free pseudorange combination (f1^2*P1-f2^2*P2)/(f1^2-f2^2)
	PCC = 145,			// GPS         Ionospheric-free pseudorange combination (f1^2*C1-f2^2*P2)/(f1^2-f2^2)
	G1C = 146,			// GPS         GRAPHIC combination between C1 and L1 (C1+L1)/2
	G1P = 147,			// GPS         GRAPHIC combination between P1 and L1 (P1+L1)/2
	G2C = 148,			// GPS         GRAPHIC combination between C2 and L2 (C2+L2)/2
	G2P = 149,			// GPS         GRAPHIC combination between P2 and L2 (P2+L2)/2
	DF = 150			// GPS         Divergence Free L1 + 2/((f1/f2)^2-1) * (L1-L2)
};

// Enumerator for different kind of measurements
enum MeasurementKind {
	UNKNOWN_MEAS,
	CarrierPhase,
	Pseudorange,
	SNR,
	Doppler
};

// Enumerator for the different filter parameters
enum FilterParameter {
	PHI_PAR = 0,
	Q_PAR = 1,
	P0_PAR = 2
};

// Enumerator for the different filter unknowns
enum FilterUnknown {
	DR_UNK = 0,
	DT_UNK = 1,
	TROP_UNK = 2,
	BIAS_UNK = 3
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
enum AntennaData {
	adUNKNOWN,
	adNONE,
	adSET,
	adANTEX
};

// Enumerator for ARP
enum ARP {
	arpUNKNOWN,
	arpNONE,
	arpSET,
	arpRINEX
}; 

// Enumerator for the program work mode
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
	pFORWARD,
	pBACKWARD
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
	SNRWeightCombMax = 2,
	SNRWeightCombMin = 3,
	SNRWeightCombMean = 4,
	SNRWeightCombUser = 5
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
	SBASMode=2,
	DGNSSMode=3
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


//Structure for creating a string of satellite ranges (grouped by
//constellations) according to a certain conditions (for example, weight mode)
//This struct is mainli used in printParameters function in output.c file
typedef struct {
	int				size;
	int				*numJumpslist;
	int				***listSatPRN;
	enum GNSSystem	***listSatGNSS;

} TRangeList;

// Measurements structure
typedef struct {
//	enum MeasurementType	type;
	double		value;
	double		rawvalue;	//Raw value without user added noise
	double		totalnoise;	//Total user added noise to the measurement
	double		model;
	int			LLI;
	int			hasSNRflag;	//Flag to indicate is SNR flag is given
	int			SNR;		//SNR flag from RINEX (if not given, SNR value is maximum)
	int			SNRdBHz;	//SRN in dBHz
	int			dataFlag;   // see FLAG #defines
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
	double					ionoSigma;		//in TECUs
	double					tropWetMap;
	double					measurementWeights[MAX_FILTER_MEASUREMENTS];
	double					geometricDistance;
	int						validIono;
	int						hasOrbitsAndClocks;
	int						hasSatPhaseCenterCor;
	int						hasDCBs;
	int						hasDCBsofC1P1;
	int						hasSBAScor;
	int						hasDGNSScor;
	int						hasSNR;
	int						hasC1C;
	enum MeasurementType	NoSNRforWeightMeas;
	double					lowSNR;
	double					URAValue;
	int						available;
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
	int					equivalentC1P1;
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
	int						nDiffMeasurements;
	int						meas2Ind[MAX_MEASUREMENTS];
	enum MeasurementType	ind2Meas[MAX_MEASUREMENTS_PER_SATELLITE];
	double					conversionFactor[MAX_MEASUREMENTS]; // This factor is to allow changing from carrier-phase cycles to meters.
	int						usable[MAX_MEASUREMENTS];
	int						hasSNRmeas;
	int						SNRmeaspos[MAX_FREQUENCIES_PER_GNSS];
} TMeasOrder;

// Cycle slip data structure
typedef struct {
	TTime		tPrevLI[MAX_SATELLITES_VIEWED][MAX_CS_MEMORY];
	TTime		tPrevBw[MAX_SATELLITES_VIEWED][MAX_CS_MEMORY];
	TTime		previousEpoch[MAX_SATELLITES_VIEWED];
	TTime		previousEpochNconsecutive[MAX_SATELLITES_VIEWED];
	TTime		lastModelledEpoch[MAX_SATELLITES_VIEWED];
	double		LiPrev[MAX_SATELLITES_VIEWED][MAX_CS_MEMORY];
	double		BwPrev[MAX_SATELLITES_VIEWED][MAX_CS_MEMORY];
	int			outlierLI[MAX_SATELLITES_VIEWED];
	int			outlierBw[MAX_SATELLITES_VIEWED];
	int			preCheck[MAX_SATELLITES_VIEWED];
	int			CS[MAX_SATELLITES_VIEWED];
	int			CSPrealignFlag[MAX_SATELLITES_VIEWED];
	int			consistency[MAX_SATELLITES_VIEWED];
	int			narc[MAX_SATELLITES_VIEWED];
	int			arcLength[MAX_SATELLITES_VIEWED];
	int			hasBeenCycleslip[MAX_SATELLITES_VIEWED];
	int			use4smooth[MAX_SATELLITES_VIEWED];
	int			Nconsecutive[MAX_SATELLITES_VIEWED];
	double		BWsigma[MAX_SATELLITES_VIEWED];
	double		initialLi[MAX_SATELLITES_VIEWED];
	double		BWmean[MAX_SATELLITES_VIEWED];
	double		BWmean300[MAX_SATELLITES_VIEWED];
	double		windowMW[MAX_SATELLITES_VIEWED][MAX_SLIDING_WINDOW];
	double		windowMWtime[MAX_SATELLITES_VIEWED][MAX_SLIDING_WINDOW];
	double		windowL1C1[MAX_SATELLITES_VIEWED][MAX_SLIDING_WINDOW];
	double		windowL1C1time[MAX_SATELLITES_VIEWED][MAX_SLIDING_WINDOW];
	double		preAlign[MAX_SATELLITES_VIEWED][MAX_MEASUREMENTS_PER_SATELLITE];
	double		windUpRadAccumReceiver[MAX_SATELLITES_VIEWED];
	double		windUpRadAccumReceiverPrev[MAX_SATELLITES_VIEWED];
	double		windUpRadAccumSatellite[MAX_SATELLITES_VIEWED];
	double		windUpRadAccumSatellitePrev[MAX_SATELLITES_VIEWED];
	double		smoothedMeas[MAX_SATELLITES_VIEWED][MAX_FILTER_MEASUREMENTS];
	double		L1C1mean[MAX_SATELLITES_VIEWED];
	double		L1C1sigma[MAX_SATELLITES_VIEWED];
	double		L1Prev[MAX_SATELLITES_VIEWED];
	double		C1Prev[MAX_SATELLITES_VIEWED];
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

// Epoch structure
typedef struct {
	int			initialhour;
	TTime		t;
	TTime		PreviousEpoch;
	TTime		firstepoch;
	TTime		secondepoch;
	int			numSatellites;
	int			lastSBASindex;
	int			prevNumSatellites;
	int			usableSatellites;
	TSatellite	sat[MAX_SATELLITES_VIEWED];
	TSatellite	prevSat[MAX_SATELLITES_VIEWED];
	TReceiver	receiver;
	int			satIndex[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int			satCSIndex[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int			numGNSS;
	TMeasOrder	measOrder[MAX_GNSS];
	int			flag;
	enum Source	source;
	TCS			cycleslip;
	TDGNSS		dgnss;
	int			DGNSSstruct;
	int			prealign;
	double		solidTideDisplacement[3];
	TSatInfo	satInfo[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	double		ZTD;
	int			satsviewed[MAX_SATELLITES_VIEWED];
	int			numAproxPosRead;
	double		IPPlat;	// Ionospheric pierce point latitude  between -90 and -90º
	double		IPPlon;	// Ionospheric pierce point longitude between -180º and 180º
	int			numSatSolutionSBAS;
	int			numSatnotUsedSBAS;
	int			numSatSolutionFilter;
	int			listPRNSatSolutionSBAS[MAX_SATELLITES_VIEWED];
	char		listConsSatSolutionSBAS[MAX_SATELLITES_VIEWED];
	int			listPRNSatnotUsedSBAS[MAX_SATELLITES_VIEWED];
	char		listConsSatnotUsedSBAS[MAX_SATELLITES_VIEWED];
	int			numsatdiscardedSBAS;
	int			SwitchPossible;			//0 => GEO or mode switch is not possible in current epoch
										//1 => GEO or mode switch is possible in current epoch
	int			SBASUsedGEO;			//SBAS GEO used  in current epoch
	int			SBASUsedMode;			//SBAS mode used in current epoch
	int			overMaxHDOP;			//0 => Epoch under HDOP threshold or HDOP threshold disabled
										//1 => Epoch over HDOP threshold
	int			overMaxPDOP;			//0 => Epoch under PDOP threshold or PDOP threshold disabled
										//1 => Epoch over PDOP threshold
	int			overMaxGDOP;			//0 => Epoch under GDOP threshold or GDOP threshold disabled
										//1 => Epoch over GDOP threshold
	int			overMaxHDOPorPDOP;		//0 => Epoch under HDOP or PDOP threshold or HDOP or PDOP threshold disable
										//1 => Epoch over HDOP or PDOP threshold
	int			TryGEOChange;			//0 => Do not try to switch GEO
										//1 => Try to switch GEO, even if there is a solution available
	int			ResetNumSwitch;			//If 1, reset num GEO and mode switch attempts (for SBAS plots mode)
	int			currentGEOPRN;			//Current GEO selected in SBAS (this variable is for printing the GEO PRN)

	int			numKMLData;				//Number of slots for KMLData and KMLTime
	double		**KMLData;				//Coordinates for printing KML points with timestamps
	TTime		*KMLTime;				//Timestamps for KML file

	double		numEpochsfile;
	double		numEpochsprocessed;
	double		CurrentPercentage;
	double		PreviousPercentage;
	int			NewPercentage;

	//Variables for backing up data when selecting the GEO with smallest protection levels
	int			Buffer_NumDataStored;						//Total number of iterations saved
	int			Buffer_NumDataStoredUnderAlarmLimitsPA; 	//Number of iterations saved in PA mode and under alarm limits
	int			Buffer_NumDataStoredPA;						//Number of iterations saved in PA mode
	int			Buffer_NumDataStoredNPA;					//Number of iterations saved in NPA mode
	int			*Buffer_PosDataStoredUnderAlarmLimitsPA;	//Index position of iterations saved in PA mode and under alarm limits
	int			*Buffer_PosDataStoredPA;					//Index position of iterations saved in PA mode
	int			*Buffer_PosDataStoredNPA;					//Index position of iterations saved in NPA mode
	int			*Buffer_numsatdiscardedSBAS;				//Number of satellites discarded by SBAS in each iteration
	int			*Buffer_usableSatellites;					//Number of available satellites in each iteration
	double		*Buffer_HPL;								//Horizontal Protection Level in each iteration 
	double		*Buffer_VPL;								//Vertical Protection Level in each iteration
	double		*Buffer_HDOP;								//Horizontal Dilution of Precision in each iteration
	double		*Buffer_VDOP;								//Vertical   Dilution of Precision in each iteration
	double		*Buffer_PDOP;								//Position   Dilution of Precision in each iteration
	double		*Buffer_GDOP;								//Geometric  Dilution of Precision in each iteration
	double		*Buffer_TDOP;								//Time       Dilution of Precision in each iteration
	char		***Buffer_printMODEL;						//Output MODEL print for each satellite in each iteration
	char		***Buffer_printSBASIONO;					//Output SBASIONO print for each satellite in each iteration
	char		***Buffer_printSBASCORR;					//Output SBASCORR print for each satellite in each iteration
	char		***Buffer_printSBASVAR;						//Output SBASVAR print for each satellite in each iteration
	char		***Buffer_printSBASUNSEL;					//Output SBASUNSEL prints for each satellite in each iteration
	char		****Buffer_printSATSEL;						//Output SATSEL prints for each satellite and discard reason in each iteration
	int			**Buffer_NumSatSel;							//Number of SATSEL lines printed for each satellite in each iteration
	int			*Buffer_SBASMode;							//SBAS solution mode (PA or NPA) in each iteration
	int			*Buffer_GEOindex;							//GEO index in SBASdata structure in each iteration
	int			*Buffer_GEOPRN;								//GEO PRN list in SBASdata structure in each iteration
	TSatellite	**Buffer_sat;								//Satellite data (including modelled values) in each iteration

	//Data for summary
	int			TotalEpochs;				//Total epochs processed in summary period
	int			TotalEpochsForward;			//Total epochs processed in summary period in forward direction only
	int			TotalEpochsDecimated;		//Total epochs decimated in summary period
	int			TotalEpochsDecimatedForward;//Total epochs decimated in summary period in forward direction only
	int			TotalEpochsFile;			//Total epochs in observation file
	int			TotalEpochsSol;				//Total epochs processed with solution in SPP/PPP modes
	int			TotalEpochsDGNSS;			//Total epochs processed with solution in DGNSS mode
	int			TotalEpochsSPP;				//Total epochs processed with solution in SPP when using DGNSS mode
	int			TotalEpochsRef;				//Total epochs processed with solution and position from reference file
	int         NumNoRefSumSkipped;			//Number of epochs skipped in the summary due to no position from reference file
	int         NumNoRefSolSkipped;			//Number of epochs skipped due to no position from reference file
	int			NumDOPSkipped;				//Number of epochs skipped due to bad DOP (any DOP)
	int			NumHDOPSkipped;				//Number of epochs skipped due to bad HDOP
	int			NumPDOPSkipped;				//Number of epochs skipped due to bad PDOP
	int			NumGDOPSkipped;				//Number of epochs skipped due to bad GDOP
	int			NumHDOPorPDOPSkipped;		//Number of epochs skipped due to bad HDOPorPDOP
	int			NumSingularMatrixSkipped;	//Number of epochs skipped due to singular geometry matrix
	int			NumNoSatSkipped;			//Number of epochs skipped due to lack of satellites
	int			CurrentDataGapSize;			//Data gap size of the last detected data gap
	int			NumDataGapsSum;				//Number of data gaps during summary
	int			NumDataGapsTotal;			//Number of data gaps in whole file
	int			MaxDataGapSizeSum;			//Maximum data gap size during summary
	int			MaxDataGapSizeTotal;		//Maximum data gap size in whole file
	int			NumEpochsMissingSum;		//Number of epochs missing in summary (used for refernce station)
	int			NumEpochsMissingTotal;		//Number of epochs missing in whole file (used for refernce station)

	double		*HError;					//Vector with all horizontal errors
	double		*VError;					//Vector with all vertical errors
	double		*HDOP;						//Vector with all HDOP values
	double		*PDOP;						//Vector with all PDOP values
	double		*GDOP;						//Vector with all GDOP values
	double		*VDOP;						//Vector with all VDOP values
	double		*TDOP;						//Vector with all TDOP values
	double		MaxHError;					//Maximum horizontal error
	double		MaxVError;					//Maximum vertical error
	double		MaxHDOP;					//Maximum HDOP
	double		MaxPDOP;					//Maximum PDOP
	double		MaxGDOP;					//Maximum GDOP
	double		MaxVDOP;					//Maximum TDOP
	double		MaxTDOP;					//Maximum VDOP
	double		HPEPercentileSamples;		//95th horizontal error percentile of the samples
	double		VPEPercentileSamples;		//95th vertical error percentile of the samples
	double		HDOPPercentileSamples;		//95th HDOP of the samples
	double		PDOPPercentileSamples;		//95th PDOP of the samples
	double		GDOPPercentileSamples;		//95th GDOP of the samples
	double		TDOPPercentileSamples;		//95th TDOP of the samples
	double		VDOPPercentileSamples;		//95th VDOP of the samples

	TTime		StartSummaryEpoch;			//Timestamp of the first epoch used in the summary
	TTime		LastSummaryEpoch;			//Timestamp of the last epoch used in the summary
	TTime		StartSummaryPercentileEpoch;//Timestamp of the first epoch used in the summary for computing percentiles
	TTime		LastSummaryPercentileEpoch;	//Timestamp of the last epoch used in the summary for computing percentiles

	TTime		HerrorEpoch;				//Timestamp of the epoch with highest horizontal error
	TTime		VerrorEpoch;				//Timestamp of the epoch with highest vertical error
	TTime		HDOPEpoch;					//Timestamp of the epoch with highest HDOP
	TTime		PDOPEpoch;					//Timestamp of the epoch with highest PDOP
	TTime		GDOPEpoch;					//Timestamp of the epoch with highest GDOP
	TTime		VDOPEpoch;					//Timestamp of the epoch with highest VDOP
	TTime		TDOPEpoch;					//Timestamp of the epoch with highest TDOP

	TTime		DataGapSum;					//Timestamp of the epoch with biggest DataGap during summary
	TTime		DataGapTotal;				//Timestamp of the epoch with biggest DataGap in whole file

	TTime		BackwardTurningEpoch;		//Epoch were forward processing ended		
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
	int				vsizeblock;
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
	TTime		Ttoc;
	TTime		Ttoe;
	TTime		TtransTime;
	int			PRN;
	double		clockbias, clockdrift, clockdriftrate;	// First block row
	int			IODE, IODNav;							// Second block row (IODNav for Galileo)
	double		crs, deltan, M0;
	double		cuc, e, cus, sqrta;						// Third block row
	double		toe, cic, OMEGA, cis;					// Forth block row
	double		i0, crc, omega, OMEGADOT;				// Fifth block row
	double		IDOT;									// Sixth block row
	int			codesOnL2, GPSweek, L2Pdataflag;
	int			dataSources,GALweek;					// Galileo Sixth block row
	int			BDSweek;								// BeiDou Sixth block row
	double		SVaccuracy;								// Seventh block row
	int			SVhealth;	
	double		TGD;
	double		TGD2;									//TGD for BeiDou
	int			IODC;	
	double		SISASignal;								// Galileo Seventh block row
	double		BGDE5a,BGDE5b;
	double		transTime;								// Eigth block row
	int			fitInterval;
	double		transTimeGAL;							// Galileo Eigth block row

	//GLONASS data (RINEX v3)
	double		satposX,satvelX,sataccX;				// Second block row
	double		satposY,satvelY,sataccY;	        	// Third block row
	int			freqnumber;
	double		satposZ,satvelZ,sataccZ;	        	// Fourth block row
	int			ageofoperation;	

	//GEO data
	int			IODNGEO;
	int			URAGEO;
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
	TTimeSystemCorrection 	timeSysCorr[12];	//12 positions, one for each correction type	
	int						AT_LS;				//Number of leap seconds
	int						AT_LSF;				//Future or past leap seconds
	int						WN_LSF;				//Respective week number
	int						DN;					//Respective day number
	
	//Common blocks
	TBRDCblock				**blockPast;		// Satellite & Block from previous day
	TBRDCblock				**block;			// Satellite & Block
	int						*numblocks;			// Per satellite
	int						*numblocksPast;		// Per satellite (from previous day)
	int						numsats;
	int						numsatsPast;
	int						index[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int						indexPast[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int						LeapSecondsAvail;
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
	TDCBblock	block[MAX_DCB_TYPES];
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

// TGD generic structure
typedef struct {
	enum P1C1DCBModel	p1c1dcbModel;
	enum P1P2DCBModel	p1p2dcbModel;
	TBRDCproducts		*BRDC;
	TDCBdata			*DCB;
	TIonexDCB			ionexDCB;	
	TFPPPDCB			fpppDCB;
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
	double		*RMS;	// Stored in TECU
	double		*HGT;	// Stored in Km
	TTime		t;
} TIonoMap;

// IONEX structure
typedef struct {
	int				numMaps;
	int				RMSavailable;
	int				HGTavailable;
	TIonoMap		*map;
	TTime			startTime;
	TTime			endTime;
	int				interval;
	int				exponent;
	int				satNumber;
	int				stationNumber;
	int				mapDimension;
	int 			numStationData;
	double			conversionFactor;
	double			elevationCutoff;
	double			baseRadius;	//Stored in Km
	TIonexDCB		ionexDCB;
	char			mappingFunction[5];
	char			observablesUsed[61];
	TIonexStation	*ionexStation;
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

	double		lt1;	//Stored in degrees (always 0)
	double		lt2;	//Stored in degrees (always 360)
	double		dlt;	//Stored in degrees
	double		nlt;

	double		*TEC;   // Stored in TECU
	double		*SIGMA; // Stored in TECU
	TTime		t;
} TFPPPMap;


// FPPPIONEX structure
typedef struct {
	int		numMaps;
	TFPPPMap	*map;
	TTime		startTime;
	TTime		endTime;
	int			interval;
	double		baseRadius;     //Stored in Km
	char		mappingFunction[5];
	TFPPPDCB	fpppDCB;
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

// Data on unknowns for the filter
typedef struct {
	int 		unk2par[MAX_UNK];
	int			par2unk[MAX_PAR];
	int 		nunk;
	int 		nunkvector;
	double 		qnoise[MAX_UNK];
	double 		phi[MAX_UNK];
} TUnkinfo;

// Filter solution structure
typedef struct {
	double		x[MAX_UNK];
	double		parameters[MAX_UNK];
	double		correlations[MAX_VECTOR_UNK];
	double		dop,GDOP,PDOP,TDOP,HDOP,VDOP,HPL,VPL;
	int			prevNumSatellites;
	int			prevNumSatellitesGPS;
} TFilterSolution;

// GNSS Constellation data
typedef struct {
	TConstellationElement	*sat;
	int						numSatellites;
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
	int		datalength;					//Length of data message
	int		receiverindex;				//Receiver index given in the RINEX file (0 is an unclassified receiver)
	char	sourceidentifier[4];		//Transmission system identifier (SBA for a SBAS satellite, SNT for SiSNET, CDG for CDGPS)

	//Common fields
	int		messagetype;				
	int		dontuse;			//Flag that will activate when a type 0 message is received
	int		problems;			//Flag that will activate when a type 0 message is received and the message is filled with 0
	int		PRN;				//PRN number
	TTime	t;					//In time of applicability (reception of last bit), not time of reception of first bit
	int		messageslost;		//Number of messages lost (detected by the preamble) from the previous message received

	int		*IODF;				//IODF (Issue Of Data Fast correction) Identifies the current fast corrections
	int		IODP;				//IODP (Issue Of Data PRN mask) Identifies the current PRN mask
	int		numsatellites;		//Number of satellites monitored

	//PRN Mask assignments
	int		**PRNactive;		//Given a PRN number of a GNSS system, check if that satellite has corrections or not
	int		*pos2PRN;			//Given one position in the list of 51 satellites with corrections, return its PRN (in the same order as messages type 2-5,6,7,25,25,28)
	int		*pos2GNSS;			//Given one position in the list of 51 satellites with corrections, return its GNSS system (in the same order as messages type 2-5,6,7,25,25,28)
	int		**PRN2pos;			//Given a GNSS and a PRN, return its position in the mask (in the same order as messages type 2-5,6,7,25,25,28)

	//Fast corrections data
	double	*PRC;				//PRC (Pseudo Range Correction). These are fast corrections applied to the pseudorange (0.125m resolution,stored in meters)
	double	*RRC;				//RRC (Range Rate Correction). These are fast corrections applied to the pseudorange (not broadcasted)
	int		*UDREI;				//UDREI (User Differential Range Error Indicator) Indicates accuracy of combined fast and long corrections (except ionosphere)
	double	*UDRE;				//UDRE (User Differential Range Error) Accuracy value of combined fast and long corrections (except ionosphere) (in meters)
	double	*UDREsigma;			//UDRE (User Differential Range Error) Accuracy variance of combined fast and long corrections (except ionosphere) (in meters^2)

	//Fast corrections degradation data
	int		tlat;								//System latency (in seconds). Only in message type 7
	int		*aiind;								//Fast Correction Degradation Indicator. Only in message type 7
	double	*aifactor;							//Fast Correction Degradation Factor. (in meters/seconds^2)
	int		*timeoutintervalnonprecise;			//User Time-Out Interval for fast corrections (seconds). En Route through Nonprecision approach
	int		*timeoutintervalprecise;			//User Time-Out Interval for fast corrections (seconds). Precision approach mode
	int		*fastcorrupdateinterval;			//Maximum fast correction update interval (seconds)
	


	//Integrity information
	int		*UDREIacu;							//UDREI (User Differential Range Error Indicator) Indicates the accuracy of fast and long-term error corrections factor
	double	*UDREacu;							//UDRE (User Differential Range Error) Accuracy of fast and long-term error corrections value
	double	*UDREacusigma;						//UDRE (User Differential Range Error) Accuracy variance of combined fast and long corrections (except ionosphere) (in meters^2)

	//Degradation factors
	double		*degradationfactors;			//Degradation factors only in message type 10. It consists of 16 factors (maybe in the future more are added)

	//Long term satellite error corrections
	double	**longtermsaterrcorrections;		//Long term satellite error correction. Only for messages type 25 and type 24
	int		numlongtermsaterrcorrections;		//Number of satellites with corrections in the current messages. Only for messages type 25 and type 24

	//Mixed fast corrections/long term satellite error corrections
	int		BlockID;							//Indicates if type 24 message fast corrections contains data from type 2, 3, 4 or 5

	//GEO Navigation message
	double	*geonavigationmessage;				//GEO Navigation Message data from message type 9

	//GEO Almanacs message
	double	**geoalmanacsmessage;				//GEO Almanacs Message from message type 17
	int		numgeoalmanacs;						//Number of almanacs given in the current message

	//Service message
	double	*servicemessage;					//Service message parameters from message type 27
	int		**regioncoordinates;				//Contains the coordinates for all the regions given in the service message
	int		numregioncoordinates;				//Number of region coordinates in the service message

	//Network Time/UTC Parameters
	double	*networktimemessage;				//Network time/UTC Parameters from message type 12

	//Clock-Ephemeris Covariance Matrix
	int		**clockephemeriscovariance;			//Clock-Ephemeris Covariance Matrix from message type 28
	int		numclockephemeriscovariance;		//Number of satellite with Clock-Ephemeris Covariance Matrix in message type 28 (1 or 2)

	//IGP Mask Message
	int		*igpmaskmessage;					//IGP (Ionospheric Grid Points) Mask from message type 18

	//Ionospheric delay parameters
	double	**ionodelayparameters;				//Ionospheric delay parameters from message type 26
} TSBASblock;

// SBAS structure
typedef struct {
	//Time-outs values
	int		timeoutmessages[2][64];		//Time-out for non precision approach (position 0) and precision approach (position 1) per message (seconds)
	int		msgupdateinterval[64];		//Maximum update interval for message types (seconds)
	int		oldmaskdiscarded[64];		//Variable to check if data from old masks have been discarded if the old mask has timed-out

	//Last messages received
	TTime	lastfastcorrections[5][MAXSBASFASTCORR][51];	//Time since last fast corrections data received, by PRN mask
	TTime	lastintegrityinfo[51];							//Time since last integrity information data received, by PRN mask
	TTime	lastfastdegfactor[5][51];						//Time since last fast corrections degradation factor data received, by PRN mask
	TTime	lastlongtermdata[5][51];						//Time since last long term satellite error correction data received, by IODP and PRN mask
	TTime	prevlastlongtermdata[5][51];					//Time since previous last long term satellite error correction data received, by IODP and PRN mask
	TTime	lastcovmatrix[5][51];							//Time since last clock-ephemeris convariance matrix data received, by IODP and PRN mask
	TTime	lastmsgreceived[64];							//Time since last message received (ordered by message type) and that do not depend on PRN number (except ionosphere delay)
	TTime	alarmtime;										//Time of the last type 2 message (used only for priting SBASUNSEL message)
	TTime	firstmessage;									//Time of the first message received (from start of file or after a reset from a type00 message)

	//Previous messages received
	TTime		oldlastintegrityinfo[51];
	TTime		oldlastmsgreceived[64];

	//Basic info
	int		PRN;							//PRN number. -1 for messages from more than one PRN
	int		GEOPRN2pos[MAX_SBAS_PRN];		//For a given GEO PRN, get the position of the TSBASdata struct vector its data is being stored
	int		failedmessages[MAX_SBAS_PRN];	//For a given GEO PRN (position 0 is for all PRN), save the number of messaged with error at decoding since the last message correctly decoded
	int		missed4msg[MAX_SBAS_PRN];		//For a given GEO PRN (position 0 is for all PRN), this is a flag to indicate if 4 or more consecutive messages are lost (not received)
	int		numreceivers;					//Number of receivers (given by the number of "REC INDEX/TYPE/VERS" lines). Only in RINEXB file
	int		numSBASsatellites;				//Number of SBAS satellites

	//Alarm message
	int		dontuse;						//Flag that will activate when a type 0 message is received
	int		problems;						//Flag that will activate when a type 0 message is received and the message is filled with 0
	int		cleared;						//Flag to indicate if the data from a GEO PRN has been cleared (after receiving a type 2 message)
	int		alarmGEOPRN[MAX_SBAS_PRN];		//List of GEO PRN from which we have received an alarm message
	int		alarmTimeRemaining;				//Time remaining to be able to use the data from each GEO with alarm from which we received the alarm
	int		alarmGEOindex[MAX_SBAS_PRN];	//Index of GEO satellites with alarm, ordered in order of alarm reception. Returns the position of SBASdata struct GEO index
	int		numAlarmGEO;					//Number of satellites with alarm

	//PRN Mask (current)
	int		PRNactive[5][MAX_GNSS][MAX_SBAS_PRN]; 	//Given a IODP, a GNSS system and a PRN number, check if that satellite has corrections or not
	int		PRN2pos[5][MAX_GNSS][MAX_SBAS_PRN];		//Given a IODP, a GNSS system and a PRN, return the position in the mask (in the same order as messages type 2-5,6,7,25,25,28)
	int		pos2PRN[5][51];							//Given a IODP and a position in the list of 51 satellites with corrections, return its PRN (in the same order as messages type 2-5,6,7,25,25,28)
	int		pos2GNSS[5][51];						//Given a IODP and a position in the list of 51 satellites with corrections, return its GNSS system (in the same order as messages type 2-5,6,7,25,25,28)
	int		IODPmask;								//IODP (Issue Of Data PRN mask) Identifies the current PRN mask
	int		numsatellites[5];						//Number of satellites monitored (sorted by IODP)

	//PRN Mask (previous)
	int		oldIODPmask;
	int		oldnumsatellites;

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
	double	longtermsaterrcorrections[5][51][13];		//Long term satellite error correction. Only for messages type 25 and type 24. Sorted by IODP, satellite and parameter position
	int		IODPlongterm;								//IODP for long term satellite corrections

	//Long term satellite error corrections (previous)
	double	prevlongtermsaterrcorrections[5][51][13];	//This previous data is only to save messages with a different IOD from the last one received.
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
	double	networktimemessage[12];					//Network time/UTC Parameters from message type 12

	//Clock-Ephemeris Covariance Matrix
	int		clockephemeriscovariance[5][51][13];	//Clock-Ephemeris Covariance Matrix from message type 28 (sorted by IODP and satellite)
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

	//Data for SBAS summary (these are specific to SBAS, it complements the normal summary)
	double	HWIR;							//Horizontal worst integrity ratio
	double	VWIR;							//Vertical worst integrity ratio
	double	HPLPercentileSamples;			//95th horizontal protection level percentile of the samples
	double	VPLPercentileSamples;			//95th vertical protection level percentile of the samples
	double	*HPL;							//Vector with all horizontal protection levels
	double	*VPL;							//Vector with all vertical protection levels
	double	MaxHPL;							//Maximum horizontal protection level
	double	MaxVPL;							//Maximum vertical protection level
	double	decimation;						//Decimation step (saved here for the case options->decimate=0, put a value of 1)
	
	int		TotalPAEpochs;					//Total epochs with PA solution (this value also is the size of HError and VError vectors)
	int		TotalPAEpochsAvail;				//Total epochs with PA solution and under HAL and VAL
	int		TotalNPAEpochs;					//Total epochs with NPA solution (only when PA is preferred mode)
	int		NumEpochsRisk;					//Number of epochs affected by discontinuity
	int		NumEpochsRiskMar;				//Number of epochs affected by discontinuity (maritime computation mode)
	int		NumMI;							//Number of epochs with misleading information
	int		NumHMI;							//Number of epochs with horizontal misleading information
	int		NumVMI;							//Number of epochs with vertical misleading information

	TTime	MaxHPLEpoch;					//Timestamp of the epoch with highest horizontal protection level
	TTime	MaxVPLEpoch;					//Timestamp of the epoch with highest vertical protection level
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
	double			SBASsatsigma2;		//Total SBAS sigma for current satellite

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
	enum MeasurementType	*measType[NUMERRORFUNCTIONS];			//Saves the meas type where the user defined error is applied
	enum GNSSystem			*System[NUMERRORFUNCTIONS];				//Saves the satellite constellation where the user defined error is applied
	int						*PRN[NUMERRORFUNCTIONS];				//Saves the PRN where the user defined error is applied
} TUserError;

//Structure which contains data for Stanford-ESA plots
typedef struct {
	double			xstep;					//Size of pixel in horizontal axis (error axis, in meters)
	double			ystep;					//Size of pixel in vertical axis (protection level axis, in meters)
	double			xmax;					//Maximum value in horizontal axis
	double			ymax;					//Maximum value in vertical axis
	double			HWIR;					//Horizontal worst integrity ratio
	double			VWIR;					//Vertical worst integrity ratio
	unsigned int	numpixelhor;			//Number of pixels in horizontal axis
	unsigned int	numpixelver;			//Number of pixels in vertical axis
	int				numsamplesProcessed;	//Total number of samples (geometries) processed
	int				numsamplesComputed;		//Total number of samples (geometries) computed
	int				numsamplesSingular;		//Total number of samples with singular geometry matrix
	int				numsamplesMI;			//Total number of samples with MIs
	int				numsamplesHMI;			//Total number of samples with horizontal MIs
	int				numsamplesVMI;			//Total number of samples with vertical MIs
	int				**counthor;				//Number of ocurrences for each pixel in horizontal error
	int				**countver;				//Number of ocurrences for each pixel in vertical error
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
	
	double					HPL;						//Horizontal protection level for a single epoch and position
	double					VPL;						//Vertical protection level for a single epoch and position

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
	int				*hour;
	int				*previousHour;
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
	char			word_current[WORDBIT];
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
	int	printModel;			// printModel = 1				=> Print all the model values (default)
							// printModel = 0				=> Do not print model values

	int	printPrefit;		// printPrefit = 1				=> Print prefilter residuals of measurements (default)
							// printPrefit = 0				=> Do not print prefilter residuals of measurements

	int	printPostfit;		// printPostfit = 1				=> Print postfilter residuals of measurements (default)
							// printPostfit = 0				=> Do not print postfilter residuals of measurements

	int	printFilterSolution;	// printFilterSolution = 1	=> Print the estimation of the parameters of the filter (default)
								// printFilterSolution = 0	=> Do not print the estimation of the parameters of the filter

	int	printInfo;			// printInfo = 1				=> Print general information (default)
							// printInfo = 0				=> Do not print info messages 

	int	printCycleslips;	// printCycleslips = 1			=> Print cycle slips (default)
							// printCycleslips = 0			=> Do not print cycle slips

	int	printSatellites;	// printSatellites = 1			=> Print satellites used for positioning for each epoch (default)
							// printSatellites = 0			=> Do not print satellites used for positioning for each epoch

	int	printInput;			// printInput = 1				=> Print information on measurements directly extracted from the RINEX (default)
							// printInput = 0				=> Do not print information on measurements

	int	printMeas;			// printMeas = 1				=> Print information on measurements and azimuth/elevation
							// printMeas = 0				=> Do not print information on measurements and azimuth/elevation (default)

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
								
	//Prints for SBAS mode

	int	printSBASOUT;		// printSBASOUT = 1				=> Print global information related to the navigation solution computation
							//					   				(default in SBAS mode)
							// printSBASOUT = 0				=> Do not print global information related to the navigation solution computation
							//								   (default in non SBAS mode)

	int	printSBASCORR;		// printSBASCORR = 1			=> Print prefit residual contributions of each of the satellites used in the navigation solution
							//					   				(default in SBAS mode)
							// printSBASCORR = 0			=> Do not print residual contributions of each of the satellites used in the navigation solution
							//					   				(default in non SBAS mode)

	int	printSBASVAR;		// printSBASVAR = 1				=> Print indiviudal variance contributions of each of the satellites used in the 
							//									   protection levels computation (default in SBAS mode)
							// printSBASVAR = 0				=> Do not print indiviudal variance contributions of each of the satellites used in the
							//					   					protection levels computation (default in non SBAS mode)

	int	printSBASIONO;		// printSBASIONO = 1			=> Print detailed information of SBAS iono interpolation
							// printSBASIONO = 0			=> Do not print detailed information of SBAS iono interpolation (default in SBAS mode)
												   
	int	printSBASUNSEL;		// printSBASUNSEL = 1			=> Print info about why a satellite has been discarded 
							// printSBASUNSEL = 0			=> Do not print info about why a satellite has been discarded (default in SBAS mode)

	int	printSBASUNUSED;	// printSBASUNUSED = 0			=> Do not print unused model computations discarded due to GEO switching
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

	int	includeSatellite[MAX_GNSS][MAX_SATELLITES_PER_GNSS];	// Mask to select/deselect satellites, if =1 satellite selected, if =0 deselected (default, all selected)

	int	usableFreq[MAX_GNSS][MAX_FREQUENCIES_PER_GNSS];			// Mask to select/deselect frequencies, if =1 frequency selected, if =0 deselected (default, all selected)

	enum	ReceiverPositionSrc	receiverPositionSource;			// receiverPositionSource = rpRINEX	=> Use the receiver position specified in the RINEX file for apriori position (default)
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

	enum	AntennaData	antennaData;		// antennaData = adNONE		=> Do not obtain nor use and receiver antenna information (default)
											// antennaData = adSET		=> Specify the receiver antenna data (such as phase center)
											// antennaData = adANTEX	=> Try to read the characteristics of the antenna from the ANTEX file

	double	receiverPCO[MAX_FREQUENCIES_PER_GNSS][3];	// 3D vector with the receiver antenna phase center [NEU] for each frequency. This parameter is required when antennaData == adSET

	int	strictradome;				// strictradome			=> When using ANTEX to correct the receiver phase center, this option will force a perfect
									//  match between the antenna name and radome reported in the receiver RINEX file and the ones in the ANTEX file. If this option
									//  is disabled (=0), and the radome is not found, the corrections will be used considering the radome "NONE" (default=0)


	enum	ARP	ARPData;			// ARPData = arpNONE		=> Do not apply any kind of Antenna Reference Point correction (default) 
									// ARPData = arpSET		=> Specify the ARP correction
									// ARPData = arpRINEX		=> Get the ARP from the RINEX header ('ANTENNA: DELTA H/E/N' field)

	double	receiverARP[3];			// 3D vector with the receiver Antenna Referece Point [NEU]. This parameter is required when ARPData == arpSET

	int	flexibleC1P1;				// flexibleC1P1 = 1				=> Allows a flexible handling of C1/P1 (C1C/C1P), i.e. providing one, one the RINEX observation file does not provide the other (default)
									// flexibleC1P1 = 0				=> Does not allow a flexible handling of C1/P1 (C1C/C1P)

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

	int	csLI;						// csLI = 1					=> Use the geometric-free carrier-phase combination to detect cycle-slips (default)
									// csLI = 0					=> Do not use the geometric-free carrier-phase combination to detect cycle-slips

	double	csLImaxjump;			// Maximum jump threshold between two consecutive measured LI values (default 1)

	double	csLImax;				// Maximum threshold between estimated and measured LI values (default 0.08)

	double	csLIt;					// Time constant to set the threshold between maximum and minimum (default 60)

	int	csLIsamples;				// Minimum number of epochs needed to fit the second-degree polynomial for LI (default 7)

	int	csBW;						// csBW = 1				=> Use the Melbourne-Wübbena combination to detect cycle-slips (default)
									// csBW = 0				=> Do not use the Melbourne-Wübbena combination to detect cycle-slips

	double	csBWInitStd;			// Initial Sigma for the Melbourne-Wübbena combination(default 2 metres)			

	double	csBWmin;				// Minimum threshold between estimated and measured BW values in relation to its standard deviation (default 0.8)

	int	csBWwindow;					// Number of seconds to compute the BW mean over the sliding window (default 300)

	double	csBWkfactor;			// Relation between estimated and measured BW values in relation to its standard deviation (default 5)

	int	csBWsamples;				// Minimum number of epochs needed to stabilize the sigma and mean in the BW cycle-slip detector (default 2)

	int	csL1C1;						// csL1C1 = 1				=> Use the L1-C1 difference to detect cycle-slips [mainly for single-frequency receivers]
									// csL1C1 = 0				=> Do not use the L1-C1 difference to detect cycle-slips (default)

	int	csUnconsistencyCheck;		// csUnconsistencyCheck = 1		=> Use the unconsistency check in L1-C1 cycle-slips detector (default)
									// csUnconsistencyCheck = 0		=> Do not use the unconsistency check in L1-C1 cycle-slips detector

	double csUnconsistencyCheckThreshold;	// Threshold for L1-C1 Unconsistency check (default 20 metres)

	double	csL1C1kfactor;			// Relation between estimated and measured (L1-C1) values in relation to its standard deviation (default 5)

	int	csL1C1window;				// Number of epochs to limit the L1-C1 ionosphere divergence using a sliding window (default 300)

	double  csL1C1init;				// Initial standard deviation for the threshold calculation in the L1-C1 (default 3.0)

	int	csL1C1samples;				// Minimum number of epochs needed to stabilize the sigma and mean in the L1C1 cycle-slip detector (default 2)

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


	enum	P1C1DCBModel   p1c1dcbModel;	// p1c1dcbModel = p1c1NONE      => No correction of C1-P1 DCBs, no identification of C1 and P1 (default)
											// p1c1dcbModel = p1c1FLEXIBLE  => No correction of C1-P1 DCBs, identification of C1 and P1
											// p1c1dcbModel = p1c1STRICT    => Correction of C1-P1 DCBs, identification of C1 and P1 obtained from precise DCB files

	enum	P1P2DCBModel   p1p2dcbModel;	// p1p2dcbModel = p1p2NONE      => No correction of P1-P2 DCBs 
											// p1p2dcbModel = p1p2RINEX     => Correction of P1-P2 DCBs, obtained from RINEX files
											// p1p2dcbModel = p1p2DCB       => Correction of P1-P2 DCBs, obtained from precise DCB files
											// p1p2dcbModel = p1p2IONEX     => Correction of P1-P2 DCBs, obtained from IONEX files
											// p1p2dcbModel = p1p2FPPP      => Correction of P1-P2 DCBs, obtained from FPPP files

	int	SBAScorrections;					// SBAScorrections = 1 	=> Use SBAS corrections	
											// SBAScorrections = 0 	=> Do not use SBAS corrections	(default)

	double	decimate;						//	=> Decimate the data to this interval (decimate = 0 do not decimate, default = 300)

	enum	MeasurementType	smoothMeas[MAX_FILTER_MEASUREMENTS];	// Vector containing the measurements used to smooth each of the filter measurements (default: NA and NA)

	int	smoothEpochs;					// Value to limit the memory of the smoothing (default: 0, which means no smoothing)

	int	orbitInterpolationDegree;		// Orbit interpolation degree for precise products (default 10)

	int	clockInterpolationDegree;		// Clock interpolation degree for precise products (default 1 - linear interpolation)

	int	satelliteHealth;   	    		// satelliteHealth = 1          => Use the satellite healthy flag of the navigation message (default)
										// satelliteHealth = 0          => Ignore the satellite healthy flag of the navigation message

	int	brdcBlockTransTime;				// brdcBlockTransTime = 1	=> Check broadcast block transmission time is before or equal to current time (default)
										// brdcBlockTransTime = 0       => Do not check broadcast block transmission time is before or equal to current time 

	double	MaxURABroadcast;			// Discard threshold for satellites when their URA (in metres) is (in the navigation message) is equal or greater than this value

	// Filtering options
	int	totalFilterMeasurements;		// Total number of measurements per station that will be provided to the filter (default 2)

	enum	MeasurementType	measurement[MAX_FILTER_MEASUREMENTS];		// Vector containing the measurements given to the filter (default: PC and LC)

	enum	SNRWeightComb	SNRweightComb[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS]; // Vector containing how to get the SNR when a weight with SNR is used

	enum	WeightMode weightMode[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS];	// Vector containing the type of weight applied to each satellite and measurement

	double	WeightConstantsValues[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS][3];	// Vector containing the constants to compute the weights of the measurements

	double	SNRweightCombVal[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS][2]; //  Vector containing the factors for combining the SNR

	int	minArcLength;			// Minimum arc length to get the measure in the smoother, the cycle-slip detector and in the filter

	int	deprecatedMode;			// 0 => User is not running the ESA Book Vol II (default)
								// 1 => User is running the ESA Book Vol II

	double	maxdr2;				// Max distance (squared) from initial approximate position to estimated position (default 10000)

	int	estimateTroposphere;	// estimateTroposphere = 1	=> Estimate the troposphere in the filter (default 1)

	int	useSigmaIono;			// useSigmaIono = 1			=> Use ionosphere Sigma values in filter when using IONEX or FPPP model (default 1)

	int	usePhase;				// Internal check. usePhase = 1 if any measurement is of carrier-phase type (default 1)

	int	filterIterations;		// This will set the number of forward/backward runs in the filter, being 1 only forward (default 1)

	double	filterParams[3][MAX_PAR];	// filterParams stores the data of the Kalman filter. The first dimension is the parameter type of the
										// filter, the second is the specific unknown it is refering to:
										// To access the first dimension: PHI_PAR, Q_PAR and P0_PAR
										// Phi is the propagation of the uknown between epochs
										// Q is the process noise included in the propagation
										// P0 is the initial standard deviation of the parameter
										// To access the second dimension: DR_UNK, DT_UNK, TROP_UNK and BIAS_UNK
										// DR: Position unknowns
										// DT: Receiver clock unknown
										// TROP: Troposphere estimation unknown (if it is estimated)
										// BIAS: Carrierphase ambiguities (if carrierphase is used)
										// Default values are as follows:
										// PHI_DR:   1 [static positioning]       0 [kinematic positioning]
										// PHI_DT:   0
										// PHI_TROP: 1
										// PHI_BIAS: 1
										// Q_DR:     0 [static positioning]       inf [kinematic positioning]
										// Q_DT:     inf
										// Q_TROP:   1e-4   (This value is the variation per hour)
										// Q_BIAS:   0
										// P0_DR:    inf
										// P0_DT:    inf
										// P0_TROP:  0.5^2
										// P0_BIAS:  20^2

	double	elevationMask;			// => Satellites below this elevation mask (in radians) will be discarded (default 5º)

	int	discardEclipsedSatellites;	// discardEclipsedSatellites = 1	=> Discard satellites under Earth eclipes (default in PPP)	
									// discardEclipsedSatellites = 0	=> Do NOT discard satellites under Earth eclipes (default in Standalone)

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

	int	SNRfilter;					// 0 => User has not defined a minimum SNR for any satellite and measurement
									// 1 => User has defined a minimum SNR for any satellite and measurement

	double	SNRvalues[MAX_GNSS][MAX_SATELLITES_PER_GNSS];	//SNR values given by user

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

	double	maxHDOP;		// Maximum HDOP allowed (default 4 )

	double	maxPDOP;		// Maximum PDOP allowed (default 6 )
	//Options for Converting SBAS files

	int	writeRinexBfile;			// 0 => Do not write a RINEX B file with SBAS data (default) 
									// 1 => Write a RINEX B file with SBAS data

	int	writeEMSfile;				// 0 => Do not write an SBAS EMS file with SBAS data (default) 
									// 1 => Write an SBAS EMS file with SBAS data
	
	int	writePegasusfile;			// 0 => Do not write a Pegasus file with SBAS data (default)
									// 1 => Write a Pegasus file with SBAS data

	int	onlyconvertSBAS;			// 0 => Do file conversion for SBAS messages and data processing (default)
									// 1 => Only do file conversion for SBAS messages

	int	onlySBASplots;				// 0 -> Do not do SBAS plots (default)
									// 1 -> Only do SBAS plots (no processing)

	int pegasuspurerinex;			// 0 => Write Rinex Navigation v2.11 for SBAS compliant with pegasus (default)
									// 1 => Write Rinex Navigation v2.11 for SBAS compliant with RINEX standard 

	int	pegasusaligned;				// 0 => Write Pegasus files without aligning data columns (default)
									// 1 => Write Pegasus files aligning data columns

	char	pegasusfs;				    //Field separator for pegasus files. By default a space " ", but can also be semicolon ";"

	char	sbasdir[MAX_INPUT_LINE];    //Folder where to write the converted SBAS files (by default "SBAS")

	//Options for SBAS processing

	int	usetype0messages;				//0 => Ignore any alarm messages (type 0). Setting this value will leave option alarmmessageastype2 with no effect
										//1 => Read alarm messages (type 0) (default).

	int	alarmmessageastype2;			//0 => Alarm messages (type 0) are treated as they are (default)
										//1 => Alarm messages (type 0) are treated as fast correction message type 2

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

	int	mixedGEOdata;					//-1/0 => Use of mixed GEO data is disabled (default)
										//1    => Use of mixed GEO data is enabled 

	int	initcoordNPA;					// 0   => First epochs Klobuchar will not be used in PA if receiver coordinates is set to calculate
										// 1   => First epochs Klobuchar will be used in PA if receiver coordinates is set to calculate (default)

	int UDREIthreshold;					// Maximum UDREI threshold. Satellites with UDREI equal or higher than the threshold will be discarded (default 999999)

	double SigmaOffsetNoMT10;			// Offset to be applied when computing the sigma flt when Message type 10 is not available or disabled (default 8)

	int	onlySBASiono;					// 0 => Process SBAS iono and SBAS data
										// 1 => Process SBAS iono but no SBAS data

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

	int	usersigmamultipath;				//0 => Use SBAS sigma multipath model (default)
										//1 => Use user sigma multipath model given in file

	double	sigma2multipath[3];			// Stores parameters a,b,c for sigma multipath, being sigma=a+b*e^(-satelevation*c). Values saved in meters (a,b) and degrees (c)

	double	sigma2noise;				// Stores the user fixed value given for sigma noise. If value is -1, no value was given. Value saved in meters^2

	double	sigma2divergence;			// Stores the user fixed value given for sigma divergence. If value is -1, no value was given. Value saved in meters^2

	double	kfactor[2][2];				// K factor used when computing protection levels. First dimension is for mode (PA/NPA) and second dimension is for axis component

	int	stanfordesa;					//0 => Do not compute values for stanford-esa plot (default)
										//1 => Compute values for stanford-esa plot

	int stanfordesaLOI;					//0 => Do not write LOIs over threshold to file when computing Stanford-ESA plot
										//1 => Write LOIs over threshold to file when computing Stanford-ESA plot (default)

	double	WIRHorThreshold;			// Horizontal Integrity Ratio threshold for writing in file information of the Stanford-ESA iteration (default 0.7)
	double	WIRVerThreshold;			// Vertical Integrity Ratio threshold for writing in file information of the Stanford-ESA iteration (default 0.7)

	//Options for disabling SBAS corrections
	//Note that disabling corrections sets corrections to zero, but still has to meet the necessary conditions according to navigation mode!
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
	int	waitForNextDay;					// If a file starts at the end of a day (at HOURSPREVDAYCONVERGENCE or later), wait until the next day to start computing summary and Stanford-ESA data
										// 0 => Do not wait for next day
										// 1 => Wait for next day (default)

	int	useDatasummary;					// This flag controls when using data is enabled or not (controlled by gLAB)
										// 0 => Do not use current epoch for computing Stanford-ESA and summary
										// 1 => Use current epoch for computing Stanford-ESA and summary

	TTime firstEpochSummary;			//First epoch to use in the summary

	double	percentile;					//Percentile value for computing the error percentile (default 95)

	int recPosProvided;					//Flag to indicate if receiver position (from rover) is given (either fixed or with a reference file)

	char StationNetworkName[MAX_STATION_NAME];	//Station name for last line of summary
	

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
	int		IonoPlotTimeStep;		//Time step for ionosphere plot (default 300)
	double	minLatplots;        	//Minimum latitude when generating SBAS plots (default  25º)
	double	maxLatplots;       		//Maximum latitude when generating SBAS plots (default  75º)
	double	minLonplots;    	    //Minimum longitude when generating SBAS plots (default -30º)
	double	maxLonplots;	        //Maximum longitude when generating SBAS plots (default  40º)
	double	AvailabilityPlotStep;	//Step for Availability and Continuity Risk plots (default 1º)	
	double	IonoPlotStep;			//Step for Ionosphere plot (default 0.1º)
	double	VerAlarmLimit;          //Vertical alarm limit (default 35 metres)
	double	HorAlarmLimit;          //Vertical alarm limit (default 35 metres)
	double	SBASPlotsRecHeight;		//Up coordinate (in meters) where the receiver is located (default 0 -sea level-)
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

	int	excludeSmoothingConvergenceTime;	// Number of seconds (in continuous operation) in the smoothing in order to reach steady-state operation (default 360)

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

	int	DF;					// Internal variable to control if divergence-free is activated or not
							// 0 => Divergence-free is deactivated (default)
							// 1 => Divergence-free is activated
	//Other options

	enum SolutionMode solutionMode;		// 0 => SPP (default)
										// 1 => PPP
										// 2 => SBAS
										// 3 => DGNSS



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

} TOptions;


char	messagestr[MAX_MESSAGE_STR];
char	messagestrSwitchGEO[MAX_MESSAGE_STR];
char	messagestrSwitchMode[MAX_MESSAGE_STR];


/**************************************
* NeQuick-G Variables
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

// Initialisations
void initOptions (TOptions *options);
void initSatellite (TEpoch *epoch, int satIndex, int satCSindex);
void initEpoch (TEpoch *epoch, TOptions  *options);
void initGNSSproducts (TGNSSproducts *products);
void initBRDCproducts (TBRDCproducts *BRDC);
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
void initConstellation (TConstellation *constellation);
void initConstellationElement (TConstellationElement *sat);
void initAntennaList (TAntennaList *antennaList);
void initAntenna (TAntenna *antenna);
void initStat (TStat *stat);
void initTGD (TTGDdata *tgdData, enum P1C1DCBModel p1c1dcbModel, enum P1P2DCBModel p1p2dcbModel);
void initDCB (TDCBdata *dcbData);
void initReceiverList (TReceiverList *recList);
void initStationList (TStationList *stationList);
void initSBASdatabox (TSBASdatabox *sbasdatabox);
void initSBASblock (TSBASblock *sbasblock);
void initSBASdata (TSBASdata *SBASdata, int pos);
void ClearSBASdata (TSBASdata *SBASdata, int pos);
void initSBAScorrections (TSBAScorr *SBAScorr);
void initStfdESA (TStdESA *StdESA);
void initSBASPlotsMode (TEpoch *epoch, TSBASPlots *SBASplots, TOptions *options, int *retvalue);
void freeSBASPlotsData(TSBASPlots *SBASplots, TOptions *options);
void initUserError (TUserError *UserError);
void initMSG1 (TMSG1 *sc, int n);
void initMSG2 (TMSG2 *sc, int n);
void initMSG3 (TMSG3 *sc);
void initMSG24 (TMSG24 *sc);
void initRTCM2 (TRTCM2 *rtcm2);
void initRTCM3 (TRTCM3 *rtcm3);


// General
void changeBase (double base[3][3], double vector[3]);
double min (double a, double b);
double max (double a, double b);
double modulo (double a, double mod);
int mod (int a, int N);
void unitary (double *vect);
void vectProd (double *a, double *b, double *res);
double scalarProd (double *a, double *b);
char *trim (char *line);
char *getstr (char *out,char *line,int ini, int length);
void getnumericalelements (char *line, int *numelements, double *out);
int	checkConstellationChar(char c);

// Measurements
enum MeasurementKind whatIs (enum MeasurementType meas);
double getLambda (enum GNSSystem GNSS, enum MeasurementType meas);
double getFrequency (enum GNSSystem GNSS, enum MeasurementType meas);
int getFrequencyInt (enum MeasurementType meas);
enum MeasurementType measstr2meastype (char *str);
char *meastype2measstr (enum MeasurementType meas);
enum GNSSystem gnsschar2gnsstype (char system);
char *gnsstype2gnssstr (enum GNSSystem GNSS);
char *gnsstype2gnssname (enum GNSSystem GNSS);
char gnsstype2char (enum GNSSystem GNSS);
enum SatelliteBlock satblockstr2satblock (char *str);
char *satblock2satblockstr (enum SatelliteBlock satBlock);
enum TimeSystemCorrection timecorrstr2timecorrtype (char *str);
char *timecorrtype2timecorrstr (enum TimeSystemCorrection timecorr);
char *SolutionModeNum2SolutionModeChar(enum SolutionMode numsol);

//Weight modes
char *WeightModeNum2WeightModestr(enum WeightMode weightMode);

// Epoch handling
int getMeasModelValue (TEpoch *epoch, enum GNSSystem system, int PRN, enum MeasurementType measType, double *measurement, double *model);
double getModelValue (TEpoch *epoch, enum GNSSystem system, int PRN, enum MeasurementType measType);
double getMeasurementValue (TEpoch *epoch, enum GNSSystem system, int PRN, enum MeasurementType measType);

//Epoch data buffering for best GEO selection
void SaveDataforGEOselection (TEpoch *epoch, TFilterSolution *solution, int OverAlarmLimits, TOptions *options);
void SelectBestGEO (TEpoch *epoch, TFilterSolution *solution, TOptions *options);
	

// OC Products handling
TTime getProductsFirstEpochBRDC (TGNSSproducts *products);
TTime getProductsFirstEpochSP3 (TGNSSproducts *products);
TTime getProductsFirstEpoch (TGNSSproducts *products);
TTime getProductsLastEpochBRDC (TGNSSproducts *products);
TTime getProductsLastEpochSP3 (TGNSSproducts *products);
TTime getProductsLastEpoch (TGNSSproducts *products);
TBRDCblock *selectBRDCblock (TBRDCproducts *products, TTime *t, enum GNSSystem GNSS, int PRN, int SBASIOD, TOptions *options);

// Time handling
int MJDN (struct tm *tm);
void MonthName (int month, char *monthname);
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
void XYZ2Spherical (double  *positionXYZ, double *positionSph);
void Spherical2XYZ (double  *positionSph, double *positionXYZ);
void XYZ2NEU (double *positionXYZ, double *positionNEU);
void NEU2XYZ (double *positionNEU, double *positionXYZ);

// Date Conversion mode functions
void ConvertCalendarDate(int year, int month, int day, int hour, int minute, double seconds);
void ConvertDoYDate(int year, int doy, double sod);
void ConvertGPSWeekDate(int GPSWeek, double SoW);
void ConvertMJDNDate(int MJDN, double SoD);

// Coordinate conversion mode functions
void ConvertCartesianCoord(double x, double y, double z);
void ConvertGeodeticCoord(double lon, double lat, double height);
void ConvertSphericalCoord(double lon, double lat, double Radius);


// IONEX
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
void getMappingFunction (TPiercePoint *PiercePoint, double earthRadius, double altitude, char functionType[5], TOptions *options);

// Constellation
TConstellationElement* getConstellationElement (enum GNSSystem GNSS, int PRN, TTime *t, TConstellation *constellation);

// Station
TStation *getStation (char *name, TStationList *stationList);

// Statistics
void addStat (TStat *stat, double value);

//Concatenate SP3 and clocks
void ConcatenateSP3 (int RefData, TGNSSproducts *products, TGNSSproducts *pastSP3Prod, TGNSSproducts *nextSP3Prod, TOptions  *options);
void freeSP3data(TGNSSproducts  *products);

// SBAS
char *SBASnavmode2SBASnavstr (int mode);
void strbintostrhex (char *binary, char *hex, int capital);
void strhextostrbin (char *hex,char *binary);
void strbintobinstr (char *binary,int binarylen, unsigned char *bitstr, int bitstrlen);
int twocomplementstrbintointeger (char *binary, int binarylen);
int checksumSBAS (unsigned char *msg);
int openSBASwritefiles (FILE **fdvector, char **filelist, char *fileread, int sourcefile, TOptions  *options);
void closefiles (FILE  **fdlist, int numfiles);
void freeSBASblock (int messagetype,TSBASblock *sbasblock,TOptions  *options);
void SBASMissingMessageClearData (int GEOindex, TSBASdata  *SBASdata);
void SBASErrorMessageTimeoutFastCorr (int GEOindex, TTime *currentepoch, TSBASdata  *SBASdata, TOptions  *options);
void SBASGEOselection (TEpoch  *epoch, TSBASdata  *SBASdata, TOptions  *options);
void SBASGEOAlarmCheck (TEpoch  *epoch, TSBASdata  *SBASdata, TOptions  *options);
void SBAShandlespecialevents (TTime currentepoch, TSBASdata  *SBASdata, TOptions  *options);
int IGP2latlon (int bandnumber, int IGP, int *IGPlat, int *IGPlon);
int IPP2Sqr (double IPPlat, double IPPlon, double *IGPlat, double *IGPlon, double *increment);
int IGPLatLon2BandNumberIGP (double IGPlat, double IGPlon, int *Bandnumber, int *IGP, int *IGP90);
void IGPsearch (double IPPlat, double IPPlon, double IGPlat, double IGPlon, double lat_inc, double lon_inc, int IGPinMask[5][11][202], int IGP2Mask[11][202], int *InterpolationMode, int *IGPnumber, int *IGPBandNumber);
void SBASionoInterpolation (double IPPlat,double IPPlon,double IGPlat1,double IGPlon1,double IGPlat2,double IGPlon2,int *InterpolationMode,double IGPDelays[5],double IGPSigma2[5],double *VerticalDelay,double *Sigma2,double *IPP_Weight);
int InsideOutside (double latpos, double lonpos, double lat1, double lon1, double lat2, double lon2, double lat3, double lon3, double lat4, double lon4, int shape);

// User added error functions
double AWGN_generator (double stddev);

//Compare functions for qsort
int qsort_compare_float(const void *a,const void *b);
int qsort_compare_double(const void *a,const void *b);
int qsort_compare_int(const void *a,const void *b);

//Recursive directory creation
int mkdir_recursive(char *path);

//Functions for range list structure
void InitRangeList (TRangeList *List);
void freeRangeList (TRangeList *List);
void AddRangeList (enum GNSSystem GNSS, int PRN, TRangeList *List);
void ExtendRangeList (enum GNSSystem GNSS, int PRN, int pos, TRangeList *List);
void SatRangeList2String (int i, TRangeList *List,  char *auxstr);

//Function to convert weight modes to strings
void WeightType2String (enum GNSSystem GNSS, int PRN, int NumMeas, int *SNRWeightused, char *str, TOptions *options);
char *SNRCombModeNum2String(enum SNRWeightComb SNRweightComb, double K1, double K2);

//Compute geoid height
double getEGM96Height (double *position);

#endif /*DATAHANDLING_H_*/
